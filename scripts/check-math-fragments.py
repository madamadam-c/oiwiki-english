#!/usr/bin/env python3
"""Compare Markdown math fragments against the original git HEAD version.

This is intended for translation work: translate prose, then verify that LaTeX
fragments were not dropped or accidentally rewritten.

Usage examples from the repository root:

    python scripts/check-math-fragments.py docs/topic/*.md
    python scripts/check-math-fragments.py --ordered docs/ds/hash.md
    python scripts/check-math-fragments.py --paragraph docs/topic/*.md

By default the script compares the multiset of math fragments outside fenced
code blocks. Use --ordered to require the same file-level order, and --paragraph
to require the same sequence within corresponding non-code paragraphs.
"""

from __future__ import annotations

import argparse
import collections
import pathlib
import re
import subprocess
import sys
from typing import Iterable


FENCE_PREFIXES = ("```", "~~~")
RAW_LATEX_PATTERN = re.compile(
    r"\\(?:frac|dfrac|tfrac|sqrt|sum|prod|int|lim|log|ln|sin|cos|tan|leq?|geq?|neq|"
    r"approx|times|div|cdot|pm|mp|alpha|beta|gamma|delta|epsilon|theta|lambda|mu|pi|"
    r"sigma|phi|omega|lfloor|rfloor|lceil|rceil|left|right|begin|end)\b"
)


def strip_fenced_code(text: str) -> str:
    lines: list[str] = []
    in_fence = False
    fence = ""
    for line in text.splitlines(True):
        stripped = line.lstrip()
        if stripped.startswith(FENCE_PREFIXES):
            marker = stripped[:3]
            if not in_fence:
                in_fence = True
                fence = marker
            elif marker == fence:
                in_fence = False
                fence = ""
            lines.append("\n")
        elif in_fence:
            lines.append("\n")
        else:
            lines.append(line)
    return "".join(lines)


def is_escaped(text: str, index: int) -> bool:
    backslashes = 0
    i = index - 1
    while i >= 0 and text[i] == "\\":
        backslashes += 1
        i -= 1
    return backslashes % 2 == 1


def looks_like_markdown_link_bracket(text: str, start: int, end: int) -> bool:
    """Return True for escaped problem-name brackets such as \[BJOI2014\]."""

    before = text[max(0, start - 80) : start]
    after = text[end + 2 : end + 80]
    content = text[start + 2 : end]
    if any("\u4e00" <= ch <= "\u9fff" for ch in content):
        return True
    if "](" in after:
        return True
    if "[" in before and "]" not in before.rsplit("[", 1)[-1]:
        return True
    return False


def math_fragments(text: str) -> list[str]:
    text = strip_fenced_code(text)
    tokens: list[str] = []
    i = 0
    n = len(text)
    while i < n:
        if text.startswith("$$", i):
            j = text.find("$$", i + 2)
            if j != -1:
                tokens.append(text[i : j + 2])
                i = j + 2
                continue

        if text[i] == "$" and not text.startswith("$$", i) and not is_escaped(text, i):
            j = i + 1
            while True:
                j = text.find("$", j)
                if j == -1:
                    break
                if is_escaped(text, j):
                    j += 1
                    continue
                if not text.startswith("$$", j):
                    tokens.append(text[i : j + 1])
                    i = j + 1
                    break
                j += 1
            if j != -1:
                continue

        if text.startswith("\\(", i):
            j = text.find("\\)", i + 2)
            if j != -1:
                tokens.append(text[i : j + 2])
                i = j + 2
                continue

        if text.startswith("\\[", i):
            j = text.find("\\]", i + 2)
            if j != -1:
                if looks_like_markdown_link_bracket(text, i, j):
                    i += 2
                else:
                    tokens.append(text[i : j + 2])
                    i = j + 2
                continue

        i += 1
    return tokens


def non_math_text(text: str) -> str:
    text = strip_fenced_code(text)
    chunks: list[str] = []
    i = 0
    n = len(text)
    while i < n:
        if text.startswith("$$", i):
            j = text.find("$$", i + 2)
            if j != -1:
                chunks.append("\n" * text[i : j + 2].count("\n"))
                i = j + 2
                continue

        if text[i] == "$" and not text.startswith("$$", i) and not is_escaped(text, i):
            j = i + 1
            while True:
                j = text.find("$", j)
                if j == -1:
                    break
                if is_escaped(text, j):
                    j += 1
                    continue
                if not text.startswith("$$", j):
                    chunks.append("\n" * text[i : j + 1].count("\n"))
                    i = j + 1
                    break
                j += 1
            if j != -1:
                continue

        if text.startswith("\\(", i):
            j = text.find("\\)", i + 2)
            if j != -1:
                chunks.append("\n" * text[i : j + 2].count("\n"))
                i = j + 2
                continue

        if text.startswith("\\[", i):
            j = text.find("\\]", i + 2)
            if j != -1:
                if looks_like_markdown_link_bracket(text, i, j):
                    chunks.append(text[i : i + 2])
                    i += 2
                    continue
                else:
                    chunks.append("\n" * text[i : j + 2].count("\n"))
                    i = j + 2
                    continue

        chunks.append(text[i])
        i += 1
    return "".join(chunks)


def raw_latex_messages(text: str) -> list[str]:
    messages: list[str] = []
    for line_no, line in enumerate(non_math_text(text).splitlines(), 1):
        if match := RAW_LATEX_PATTERN.search(line):
            messages.append(f"line {line_no}: raw LaTeX outside math delimiters near {match.group(0)!r}")
    return messages


def unwrap_math(fragment: str) -> str:
    if fragment.startswith("$$") and fragment.endswith("$$"):
        return fragment[2:-2]
    if fragment.startswith("$") and fragment.endswith("$"):
        return fragment[1:-1]
    if fragment.startswith("\\(") and fragment.endswith("\\)"):
        return fragment[2:-2]
    if fragment.startswith("\\[") and fragment.endswith("\\]"):
        return fragment[2:-2]
    return fragment


def added_delimiters_for_original_raw_math(fragment: str, original_non_math: str) -> bool:
    inner = unwrap_math(fragment).strip()
    return bool(inner and inner in original_non_math)


def paragraphs(text: str) -> list[str]:
    text = strip_fenced_code(text)
    out: list[str] = []
    current: list[str] = []
    for line in text.splitlines():
        if line.strip():
            current.append(line)
        elif current:
            out.append("\n".join(current))
            current = []
    if current:
        out.append("\n".join(current))
    return out


def git_head_text(path: pathlib.Path, repo_root: pathlib.Path) -> str:
    rel = path.relative_to(repo_root).as_posix()
    return subprocess.check_output(["git", "show", f"HEAD:{rel}"], cwd=repo_root, text=True)


def counter_diff(expected: Iterable[str], actual: Iterable[str]) -> tuple[list[str], list[str]]:
    expected_counter = collections.Counter(expected)
    actual_counter = collections.Counter(actual)
    missing = list((expected_counter - actual_counter).elements())
    extra = list((actual_counter - expected_counter).elements())
    return missing, extra


def check_file(path: pathlib.Path, repo_root: pathlib.Path, ordered: bool, paragraph: bool) -> list[str]:
    current = path.read_text()
    original = git_head_text(path, repo_root)
    messages: list[str] = []
    messages.extend(raw_latex_messages(current))

    if paragraph:
        original_paragraphs = paragraphs(original)
        current_paragraphs = paragraphs(current)
        for index, (orig_para, cur_para) in enumerate(zip(original_paragraphs, current_paragraphs), 1):
            orig_tokens = math_fragments(orig_para)
            cur_tokens = math_fragments(cur_para)
            if orig_tokens != cur_tokens:
                messages.append(
                    f"paragraph {index}: expected {orig_tokens!r}, got {cur_tokens!r}"
                )
        if len(original_paragraphs) != len(current_paragraphs):
            messages.append(
                f"paragraph count differs: expected {len(original_paragraphs)}, got {len(current_paragraphs)}"
            )
        return messages

    original_tokens = math_fragments(original)
    current_tokens = math_fragments(current)
    original_non_math = non_math_text(original)
    if ordered:
        if original_tokens != current_tokens:
            messages.append(f"ordered tokens differ: expected {original_tokens!r}, got {current_tokens!r}")
    else:
        missing, extra = counter_diff(original_tokens, current_tokens)
        extra = [
            fragment
            for fragment in extra
            if not added_delimiters_for_original_raw_math(fragment, original_non_math)
        ]
        if missing:
            messages.append(f"missing math fragments: {missing!r}")
        if extra:
            messages.append(f"extra math fragments: {extra!r}")
    return messages


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("paths", nargs="+", help="Markdown files or directories to check")
    parser.add_argument("--ordered", action="store_true", help="Require same file-level math order")
    parser.add_argument("--paragraph", action="store_true", help="Require same math sequence in corresponding paragraphs")
    args = parser.parse_args()

    repo_root = pathlib.Path.cwd().resolve()
    files: list[pathlib.Path] = []
    for raw_path in args.paths:
        path = pathlib.Path(raw_path)
        if path.is_dir():
            files.extend(sorted(path.rglob("*.md")))
        else:
            files.append(path)

    failed = False
    for path in files:
        path = path.resolve()
        try:
            messages = check_file(path, repo_root, args.ordered, args.paragraph)
        except subprocess.CalledProcessError:
            print(f"{path.relative_to(repo_root)}: no git HEAD version found", file=sys.stderr)
            failed = True
            continue
        if messages:
            failed = True
            print(f"{path.relative_to(repo_root)}:")
            for message in messages:
                print(f"  - {message}")

    if failed:
        return 1
    print(f"Math fragment check passed for {len(files)} file(s).")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
