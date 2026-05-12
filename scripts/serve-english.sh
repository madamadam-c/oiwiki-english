#!/usr/bin/env bash

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
HOST="${HOST:-0.0.0.0}"
PORT="${PORT:-8000}"
DEPS_MARKER=".venv/.oiwiki-preview-deps-installed"

cd "$REPO_ROOT"

if [[ ! -d .venv ]]; then
  printf 'Creating local Python environment in %s/.venv\n' "$REPO_ROOT"
  python3 -m venv .venv
fi

source .venv/bin/activate

if [[ ! -f "$DEPS_MARKER" ]]; then
  printf 'Installing MkDocs preview dependencies. This is only needed once.\n'
  python -m pip install --upgrade pip
  python -m pip install \
    mkdocs==1.5.3 \
    pymdown-extensions==10.16.1 \
    pygments==2.19.2 \
    beautifulsoup4 \
    requests \
    markdown==3.9 \
    python-markdown-document-offsets-injection-extension==0.5.16 \
    mkdocs-toggle-sidebar-plugin==0.0.8
  touch "$DEPS_MARKER"
fi

if [[ ! -d mkdocs-material/.git ]]; then
  git submodule update --init --recursive
fi

if [[ ! -d mkdocs-material/material/templates/assets/vendor/mathjax ]]; then
  printf 'Installing theme assets. This is only needed once unless assets are removed.\n'
  ./scripts/pre-build/install-theme.sh
fi

printf '\nStarting MkDocs. Wait until you see "Serving on" before opening the browser.\n'
printf 'Local browser URL: http://127.0.0.1:%s/\n' "$PORT"
printf 'Bound address: http://%s:%s/\n\n' "$HOST" "$PORT"
printf 'The first build can take 30-60 seconds. "Connection refused" before "Serving on" is expected.\n\n'
python -m mkdocs serve --dirtyreload -a "$HOST:$PORT"
