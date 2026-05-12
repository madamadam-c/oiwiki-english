Before reading this article, the entire **OI Wiki** project team welcomes you to contribute to this project. It is because of hundreds of people like you that **OI Wiki** has achieved its current state!

This page lists the recommended style guidelines and editing policies for writing in **OI Wiki**. Please read the following carefully before writing or editing wiki pages to help produce higher quality content.

If you can't wait and want to get started quickly, it is recommended to first read the [TL;DR](#tl-dr) and [Image Examples](#image-examples) sections.

??? abstract "Changelog"
    **Note**: Only record changes related to writing, reviewing, etc., not format fixes.
    
    | Date         | Main Content                                                | Related Issue/PR Link                                                                                    |
    | ---------- | --------------------------------------------------- | ----------------------------------------------------------------------------------------------------------- |
    | 2026-02-22 | Improved quotation usage rules                                         | [#6793](https://github.com/OI-wiki/OI-wiki/pull/6793)                                                       |
    | 2026-01-07 | Required using full-width period instead of Chinese period                                      | [#6746](https://github.com/OI-wiki/OI-wiki/pull/6746)                                                       |
    | 2025-08-10 | Added format requirements for the format manual;<br>Code: Added requirements for code snippets                       | [#6412](https://github.com/OI-wiki/OI-wiki/pull/6412)                                                       |
    | 2025-08-10 | Added Changelog and TL;DR                                | [#6409](https://github.com/OI-wiki/OI-wiki/pull/6409)                                                       |
    | 2024-10-08 | Code: Improved format requirements for cross-platform testing                                  | [#5912](https://github.com/OI-wiki/OI-wiki/pull/5912)，[#5924](https://github.com/OI-wiki/OI-wiki/pull/5924) |
    | 2024-03-26 | When referencing OJ problem links, use the original link instead of mirror links                            | [#5482](https://github.com/OI-wiki/OI-wiki/pull/5482)                                                       |
    | 2023-10-09 | Theme plugin: Added format requirements for tabs[^note6]                             | [#5152](https://github.com/OI-wiki/OI-wiki/pull/5152)                                                       |
    | 2023-07-23 | For tool-related content like downloads and installation, required referencing official documentation                            | [#5023](https://github.com/OI-wiki/OI-wiki/pull/5023)                                                       |
    | 2023-04-15 | Added quotation usage rules                                           | [#4792](https://github.com/OI-wiki/OI-wiki/pull/4792)                                                       |
    | 2023-03-28 | LaTeX: Mathematical symbol table                                         | [#4587](https://github.com/OI-wiki/OI-wiki/pull/4587)                                                       |
    | 2023-03-02 | Added usage rules for full/half-width punctuation and dashes                                    | [#4726](https://github.com/OI-wiki/OI-wiki/pull/4726)                                                       |
    | 2022-12-13 | Theme plugin: Removed shadow style requirements for nested collapsible blocks                                 | [#4500](https://github.com/OI-wiki/OI-wiki/pull/4500)                                                       |
    | 2022-08-09 | When referencing a section of an internal link, use the Chinese title                                  | [#4057](https://github.com/OI-wiki/OI-wiki/pull/4057)                                                       |
    | 2022-06-12 | Improved requirements for directory changes[^note4]                                 | [#4043](https://github.com/OI-wiki/OI-wiki/pull/4043)                                                       |
    | 2021-09-09 | Theme plugin: Added requirements for collapsible blocks                                      | [#3517](https://github.com/OI-wiki/OI-wiki/pull/3517)                                                       |
    | 2021-09-03 | LaTeX: `\Leftrightarrow` $\to$ `\iff`                | [#3499](https://github.com/OI-wiki/OI-wiki/pull/3499)                                                       |
    | 2021-08-18 | Code: Added format requirements for example code                                      | [#3447](https://github.com/OI-wiki/OI-wiki/pull/3447)                                                       |
    | 2021-08-12 | Images: Prioritize APNG format for animated images                                   | [#3422](https://github.com/OI-wiki/OI-wiki/pull/3422)                                                       |
    | 2021-06-29 | Images: Recommended to submit source files together                                        | [#3255](https://github.com/OI-wiki/OI-wiki/pull/3255)                                                       |
    | 2021-05-29 | Code: Removed requirement for no line breaks in braces, added readability requirements                              | [#3197](https://github.com/OI-wiki/OI-wiki/pull/3197)                                                       |
    | 2021-03-15 | Site maintenance: Standardized Pull Request merge method[^note5]                  | [#3061](https://github.com/OI-wiki/OI-wiki/pull/3061)                                                       |
    | 2021-02-01 | LaTeX: `\lt` $\to$ `<`，`\gt` $\to$ `>`               | [#2950](https://github.com/OI-wiki/OI-wiki/pull/2950)                                                       |
    | 2021-01-27 | Recommended to save backup snapshots of external links on the Internet Archive       | [#2918](https://github.com/OI-wiki/OI-wiki/pull/2918)                                                       |
    | 2020-09-19 | Site maintenance: Requirements for Commit Message and Pull Request title format[^note4]  | [#2744](https://github.com/OI-wiki/OI-wiki/pull/2744)                                                       |
    | 2020-10-18 | Images: Prioritize SVG format                                      | [#2215](https://github.com/OI-wiki/OI-wiki/pull/2215)                                                       |
    | 2020-08-05 | LaTeX: Added format requirements for multi-letter variables                                  | [#2502](https://github.com/OI-wiki/OI-wiki/pull/2502)                                                       |
    | 2020-07-28 | LaTeX: `cases` environment must not have more than two columns                              | [#2466](https://github.com/OI-wiki/OI-wiki/pull/2466)                                                       |
    | 2020-07-24 | LaTeX: `{n \choose m}`$\to$ `\dbinom{n}{m}`          | [#2442](https://github.com/OI-wiki/OI-wiki/pull/2442)                                                       |
    | 2020-07-20 | Markdown: Disabled strikethrough syntax                                    | [#2422](https://github.com/OI-wiki/OI-wiki/pull/2422)                                                       |
    | 2020-07-19 | Theme plugin: Required to preserve indentation spaces in empty lines in collapsible blocks[^note3];<br>LaTeX: Added format requirements for math formulas | [#2412](https://github.com/OI-wiki/OI-wiki/pull/2412)                                                       |
    | 2020-07-11 | Initial version                                                | [#2350](https://github.com/OI-wiki/OI-wiki/pull/2350)                                                       |

## TL;DR

For the convenience of users reading this document for the first time, this section highlights several important points from the manual:

-   File Storage:

    -   Use lowercase file names, replace spaces with `-`. See [SAVE-1](#SAVE-1) for details.

    -   Do not insert externally linked images. See [SAVE-2](#SAVE-2) for details.

    -   Use SVG format for images whenever possible, only use SVG 1.1 standard. See [SAVE-3](#SAVE-3) for details.

    -   Animated images should use SVG or APNG format. See [SAVE-4](#SAVE-4) for details.

    -   For images with source files, recommended to submit the source file together. See [SAVE-5](#SAVE-5) for details.

    -   When inserting external links, recommended to also insert a snapshot link. See [SAVE-6](#SAVE-6) for details.

    -   Do not insert internal links by inserting external links. See [SAVE-7](#SAVE-7) for details.

-   Punctuation:

    -   Use punctuation correctly. Add **periods** at the end of every sentence. See [PUNC-1](#PUNC-1) through [PUNC-7](#PUNC-7) for details.

    -   Pay attention to distinguish between hyphens (hyphen, en dash, em dash). See [PUNC-8](#PUNC-8) for details.

-   Markdown Syntax and Theme Extended Syntax:

    -   Only use level 2, 3, and 4 headings. Do not use headings instead of bold. Do not write LaTeX formulas in headings. See [LINT-1](#LINT-1), [MDFM-1](#MDFM-1), [CONT-4](#CONT-4), [CONT-9](#CONT-9) for details.

    -   When using collapsible blocks[^note3] and tabs[^note6] syntax, maintain consistent internal indentation, **including empty lines**. **Do not omit** space indentation in empty lines. See [LINT-6](#LINT-6), [MDFM-6](#MDFM-6) for details.

    -   Do not use strikethrough `~~foo~~` syntax. See [LINT-3](#LINT-3) for details.

    -   Display formulas should be written as

        ```text
        $$
        a^{2}=b^{2}+c^{2}
        $$
        ```

        not `$$a^{2}=b^{2}+c^{2}$$`. See [LINT-5](#LINT-5) for details.

    -   Use collapsible blocks instead of blockquotes. See [MDFM-5](#MDFM-5) for details.

    -   Code blocks should only use ` ``` ` syntax, and must specify the language. See [LINT-7](#LINT-7), [MDFM-3](#MDFM-3) for details.

-   LaTeX Formulas:
    -   Should not conflict with the [Mathematical Symbol Table](./symbol.md). See [MATH-1.1](#MATH-1.1) for details.

    -   Pay attention to the use of fonts, see [MATH-1.2](#MATH-1.2), [MATH-1.15](#MATH-1.15), [MATH-2.6](#MATH-2.6), [MATH-2.7](#MATH-2.7) for details.

    -   Do not overuse LaTeX formulas. See [MATH-1.14](#MATH-1.14) for details.

    -   Do not use programming language notation in LaTeX formulas. (e.g., do not use $a==b$, $a<<1$, $a\%b$). Do not use bracket chaining ($a[i][j]$). See [MATH-1.9](#MATH-1.9), [MATH-1.10](#MATH-1.10) for details.

-   Code:

    -   Be as concise and clear as possible, avoid bad habits like excessive line compression. Prioritize readability and highlight the algorithm idea. See [CONT-10](#CONT-10) for details.

    -   Not recommended to directly insert code into Markdown documents. See [CODE-1.1](#CODE-1.1), [CODE-1.2](#CODE-1.2) for details.

## Format Requirements for This Document

-   <a id="FREQ-1"></a>FREQ-1: When revising entries in the format manual, a Changelog must also be added. If only fixing format, no Changelog is needed.
-   <a id="FREQ-2"></a>FREQ-2: Except for the [TL;DR](#tl-dr) section, all entries in the format manual must have unique IDs matching the regex `(?<category>[A-Z]{4})-(?<id>[1-9][0-9]*(?:\.[1-9][0-9]*)*)`, where `category` should be intuitive. Description text does not need an ID.
-   <a id="FREQ-3"></a>FREQ-3: Entries in [TL;DR](#tl-dr) must come from other sections of the format manual, and must reference the corresponding entry ID at the end.
-   <a id="FREQ-4"></a>FREQ-4: Entry IDs should not be changed once assigned. If changes are necessary (such as deleting or merging entries), note should be made with text like "Deprecated" or "Merged to XXXX-id".

## Document Contribution Requirements

When you plan to contribute content for a certain part, you should be familiar with the following three parts:

-   Document storage format
-   Document reasonableness
-   Remark-lint and $\rm{\LaTeX}$ formula format requirements

### Document Storage Format

-   <a id="SAVE-1"></a>SAVE-1: **File names must all be lowercase, separated by `-`.** For example: `file-name.md`.

-   <a id="SAVE-2"></a>SAVE-2: Please ensure that all **externally linked** images referenced in the document have been saved to the corresponding `images` folder in the **repository** (to prevent triggering hotlinking protection of some websites), it is recommended to name them in the form `MD document name + number` (can refer to how images in existing documents are handled). For example: if the file name of this document is `format`, then the first image referenced in the document should be named `format1.png`.

-   <a id="SAVE-3"></a>SAVE-3: SVG format images are recommended[^ref4] to obtain better clarity and zoom effects. Since different components of **OI Wiki** have different compatibility with SVG standards, your images should be based on the [SVG 1.1](http://www.w3.org/TR/SVG11/) standard.

-   <a id="SAVE-4"></a>SAVE-4: For animated images that cannot or are not made in SVG format, APNG format[^apng] files are recommended. Windows users can use [ScreenToGif](https://www.screentogif.com) to record, Linux users can use [Peek](https://github.com/phw/peek) to record, noting that they need to adjust to record APNG in settings. For other cases, it is recommended to first create as MP4 or other video files and then convert to APNG, if using ffmpeg you can use `ffmpeg -i filename.mp4 -f apng filename.apng -plays 0` to convert．[^intro-apng]

-   <a id="SAVE-5"></a>SAVE-5: For images that have both source files and exported images (e.g., JPG files with PSD files or SVG images with TikZ TeX source code), it is recommended to save the source file in the same directory with the same file name as the image.

-   <a id="SAVE-6"></a>SAVE-6: Please ensure the stability of referenced links in your document. **Not recommended** to reference resources from **self-hosted** services (such as problems from self-hosted OJs). Recommended to also save the external link to the Internet Archive[^webarchive] when adding, in case irreplaceable links become invalid.

-   <a id="SAVE-7"></a>SAVE-7: For internal links, remove the website domain name and use relative paths to the corresponding `.md` file. For example, in this page (`intro/format`), linking to the misc introduction (`misc`), should use `[Misc Introduction](../misc/index.md)`. You can add a hash to link to a certain section, for example [`[Pull Request Information Format Requirements](./htc.md#pull-request-information-format-requirements)`](./htc.md#pull-request-information-format-requirements), the hash value can be obtained from the button on the right side of each heading or from the link in the table of contents on the right side of the page.

### Document Reasonableness

**Reasonableness** refers to the following properties that the **content** must have:

-   <a id="STRC-1"></a>STRC-1: Progressive from easy to difficult, the difficulty of content should be progressive.
-   <a id="STRC-2"></a>STRC-2: Logicality.

    -   <a id="STRC-2.1"></a>STRC-2.1: When writing about algorithm or mathematical concept content, try to include the following:

        1.  Principle: explain the corresponding principle;
        2.  Examples: give 1\~2 typical examples;
        3.  Problems: under this heading, **only need to give the problem name and problem link**. For algorithm problems, the priority for OJ links is: original OJ (foreign OJs must be accessible from China) > UOJ > LOJ > Luogu.

        Example page: [IDA*](../search/idastar.md)

    -   <a id="STRC-2.2"></a>STRC-2.2: When writing about tool-related content, try to include the following:

        1.  Introduction: explain the background and purpose of the tool.
        2.  Configuration: give detailed process for configuring the environment and usage, download and installation methods are recommended to reference official documentation.

        Example page: [WSL (Windows 10)](../tools/wsl.md)

Except when existing content quality is low, it is recommended to contribute from a **supplement** perspective rather than directly overwriting. If unsure, you can refer to the [Communication Methods for This Project](./about.md#communication-methods) section to contact the **OI Wiki** project team.

### Basic Format Requirements for Documents

#### Remark-lint Format Requirements

[remark-lint](https://github.com/remarkjs/remark-lint) can automatically unify the style of files in the project. **OI Wiki**'s currently enabled configuration file is hosted in [.remarkrc](https://github.com/OI-wiki/OI-wiki/blob/master/.remarkrc).

During configuration, the **OI Wiki** project team also encountered some problems that remark-lint cannot handle well, so please strictly follow these requirements when editing documents:

-   <a id="LINT-1"></a>LINT-1: Do not use level 1 headings like `<h1>` or `# Heading`.

-   <a id="LINT-2"></a>LINT-2: Headings should have one English half-width space, for example: `## Introduction`.

-   <a id="LINT-3"></a>LINT-3: Since remark-lint cannot handle strikethrough well, please do not use strikethrough syntax (another reason not to use strikethrough is that content crossed out is mostly "smart-alecky" in nature and not very helpful for readers' understanding, which does not meet the "content expression requirements" below in [Content Expression Requirements](#CONT-5)).

-   <a id="LINT-4"></a>LINT-4: Lists:
    -   <a id="LINT-4.1"></a>LINT-4.1: There should be an empty line before lists, starting a new paragraph.
    -   <a id="LINT-4.2"></a>LINT-4.2: When using ordered lists (like `1. Example`), there should be a space after the period.

-   <a id="LINT-5"></a>LINT-5: There should be an empty line before and after display formulas, otherwise they will be treated as inline formulas.

-   <a id="LINT-6"></a>LINT-6: When using Details syntax starting with `???` or `!!!`, every line must be included in the text box of the Details syntax, the beginning must have at least 4 spaces.

    **Even empty lines must maintain the same indentation as other lines. Please do not use the editor's automatic trimming of trailing spaces feature.**

    ???+ success "Example"
        In the following code, `␣` represents space ` `.
        
        ```text
        ???+ warning
        ␣␣␣␣Remember to add 4 spaces before the text. Other syntax is the same as Markdown syntax.
        ␣␣␣␣
        ␣␣␣␣Without adding 4 spaces, the text will not appear in the Details text box.
        ␣␣␣␣
        ␣␣␣␣The question "What is this ???" will be answered [below](#MDFM-5).
        ```
        
        ???+ warning "Warning"
            Remember to add 4 spaces before the text. Other syntax is the same as Markdown syntax.
            
            Without adding 4 spaces, the text will not appear in the Details text box.
            
            The question "What is this ???" will be answered [below](#MDFM-5).

-   <a id="LINT-7"></a>LINT-7: For plain text blocks in code style, please use ` ```text`. Directly using ` ``` ` without specifying the language for plain text blocks may cause the content to be incorrectly indented.

#### Punctuation Usage

-   <a id="PUNC-1"></a>PUNC-1: Please add a **period** at the end of every sentence.

<!-- scripts.linter.postprocess.fix_full_stop off -->

-   <a id="PUNC-2"></a>PUNC-2: Please use **full-width** punctuation marks and **half-width** punctuation marks correctly. Use full-width marks for Chinese, half-width marks for English. When mixing English in Chinese, please refer to [Chinese Publication Editing Standards for Mixing English](https://www.nppa.gov.cn/xxgk/fdzdgknr/hybz/202210/t20221004_445147.html). Specifically, please use full-width period "．" instead of Chinese period "。"．

<!-- scripts.linter.postprocess.fix_full_stop on -->

<!-- scripts.linter.postprocess.fix_quotation off -->

-   <a id="PUNC-3"></a>PUNC-3: Since `“……”` and `‘……’` do not distinguish between full-width and half-width, please use `「……」` as full-width double quotes, `"..."` as half-width double quotes, `『……』` as full-width single quotes, and `'...'` as half-width single quotes.

<!-- scripts.linter.postprocess.fix_quotation on -->

-   <a id="PUNC-4"></a>PUNC-4: Pay attention to distinguish between the use of **enumeration comma** and **comma**.
-   <a id="PUNC-5"></a>PUNC-5: Pay attention to the position of **parentheses**. The position is different for parentheses inside and outside sentences.
-   <a id="PUNC-6"></a>PUNC-6: Usually use **semicolons** to indicate the relationship between multiple clauses in a list environment.
-   <a id="PUNC-7"></a>PUNC-7: For ordered lists, recommended to add a **semicolon** after each item, and add a **period** after the last item; for unordered lists, recommended to add a **period** after each item.
-   <a id="PUNC-8"></a>PUNC-8: Pay attention to distinguish between different types of dashes, such as hyphen (generally use U+002D hyphen-minus (-), which is the "minus" key on the keyboard), U+2013 en dash (–) and U+2014 em dash (—). (In English, when connecting multiple names, must use en dash, but it is often mistakenly used as hyphen. Other misuse is relatively rare, basically just remembering this point is enough.) See [Dash - Wikipedia](https://en.wikipedia.org/wiki/Dash) for details.

    ???+ success "Example"
        -   Middle school subject competitions mainly include informatics Olympiad, informatics Olympiad, informatics Olympiad, informatics Olympiad, and informatics Olympiad (who wrote this example, suggests removing it).
        -   "Have you eaten yet?" Li Si asked Zhang San.
        -   I want to tell you: "I really like you so much."
        -   "To achieve the nation's interests, I would not avoid any suffering or pursue any comfort!"
        -   Zhang San got into college; Li Ping went to technical school; I became a worker: we all have a bright future.[^note1]
        -   Following is the basic flow of this algorithm:
            1.  Initialize distances to all points to infinity, set all points as unvisited, initialize a queue;
            2.  Put the starting point into the queue, set the starting point as visited, update the distance to the starting point to $0$;
            3.  Take the first element from the queue, set that element as unvisited;
            4.  Traverse all edges connected to this element, if there is a shorter path to this point, perform relaxation;
            5.  If this point is unvisited, put this point into the queue, and set this point as visited;
            6.  Return to step 3 until the queue is empty.
        -   The KMP algorithm (Knuth–Morris–Pratt algorithm, KMP algorithm) was published by Knuth, Pratt, and Morris in 1977.[^note2]

#### Markdown Format and Theme Extended Format Requirements

-   <a id="MDFM-1"></a>MDFM-1: When indicating emphasis, please use `**SOMETHING**` and 「」, not a heading, because using headings will cause confusion in the article structure hierarchy and (or) table of contents problems.

-   <a id="MDFM-2"></a>MDFM-2: When referencing problem links, use the original OJ problem archive link whenever possible instead of mirror links.

-   <a id="MDFM-3"></a>MDFM-3: Please use Markdown's block function correctly. For inline code, use a pair of backticks to surround the code block; for display code, use a pair of ` ``` ` to surround the code block, where the backtick is the symbol below the tilde in the upper left corner of the keyboard, for display code add the language name after the first ` ``` ` (e.g., ` ```cpp`).

    ???+ success "Example"
        ````text
        ```cpp
        // #include<stdio.h>    //bad practice
        #include <cstdio>  //good practice
        ```
        ````
        
        ```cpp
        // #include<stdio.h>    //bad practice
        #include <cstdio>  //good practice
        ```

-   <a id="MDFM-4"></a>MDFM-4: "References and Notes" use Markdown's footnote feature. Format:

    ```markdown
    Text content.[^footnotename]
    [^footnotename]: Reference content. Note: the colon is an English colon, followed by a space.
    ```

    Footnote names can be either numbers or text. The position of footnote names follows the usage of parentheses. For aesthetics, it is recommended that footnote names on the same page follow a unified naming convention, such as: ref1, ref2, note1……

    All footnotes are placed under the `## References and Notes` heading.

    ???+ success "Example"
        ```markdown
        When `#include <cxxxx>` can replace `#include <xxxx.h>`, use the former.[^ref1]
        
        On January 21, 2020, CCF announced the restoration of NOIP.[^ref2]
        
        ## References and Notes
        
        [^ref1]: [cstdio stdio.h namespace](https://stackoverflow.com/questions/10460250/cstdio-stdio-h-namespace)
        
        [^ref2]: [CCF announcement on restoring NOIP competition - China Computer Federation](https://www.ccf.org.cn/c/2020-01-21/694716.shtml)
        ```
        
        When `#include <cxxxx>` can replace `#include <xxxx.h>`, use the former.[^ref1]
        
        On January 21, 2020, CCF announced the restoration of NOIP.[^ref2]

-   <a id="MDFM-5"></a>MDFM-5: It is recommended to use the theme extension's `???+note` format (i.e., [Collapsible Blocks](https://squidfunk.github.io/mkdocs-material/reference/admonitions/#collapsible-blocks)) to describe problem statements and reference code. This format can also be used to display other content that needs additional introduction.

    Example code (in the following code, `␣` represents space ` `):

    ```text
    ??? note "Title"
    ␣␣␣␣This text box will be collapsed by default.
    ␣␣␣␣
    ␣␣␣␣It is recommended to put **solution code** inside the collapsible text box.
    
    ???+note "[HDOJ's「A + B Problem」](https://acm.hdu.edu.cn/showproblem.php?pid=1000)"
    ␣␣␣␣The title can also use Markdown's hyperlink. The hyperlink here is HDOJ's「A + B Problem」.
    ␣␣␣␣
    ␣␣␣␣And it is recommended to mark the original problem link in this way.
    ␣␣␣␣
    ␣␣␣␣Note the position of the double quotes.
    ```

    Effect:

    ??? note "Title"
        This text box will be collapsed by default.
        
        It is recommended to put **solution code** inside the collapsible text box.

    ???+ note "[HDOJ's「A + B Problem」](https://acm.hdu.edu.cn/showproblem.php?pid=1000)"
        The title can also use Markdown's hyperlink. The hyperlink here is HDOJ's「A + B Problem」.
        
        And it is recommended to mark the original problem link in this way.
        
        Note the position of the double quotes.

    The difference between the two formats is that those with `+` stay expanded by default, while those without `+` stay collapsed by default.

    The title of the collapsible block, i.e., the content after `note` in `???+note`, should be wrapped with `"`. The content supports Markdown syntax. See [Admonition - Changing the title](https://squidfunk.github.io/mkdocs-material/reference/admonitions/#changing-the-title). (Those without collapsible function are regular Admonitions, see [Admonitions - Material for MkDocs](https://squidfunk.github.io/mkdocs-material/reference/admonitions))

-   <a id="MDFM-6"></a>MDFM-6: When needing to add code in different languages, it is recommended to use Content tabs, which can achieve switching between code in different languages. Content tabs have other usages, see [Content tabs](https://squidfunk.github.io/mkdocs-material/reference/content-tabs/#usage). Its usage and effect are as follows.

    ???+ success "Example"
        Note that 4 spaces need to be added before the text (represented by `␣` below). Other syntax is the same as Markdown syntax.
        
        ````text
        === "C"
        ␣␣␣␣```c
        ␣␣␣␣#include <stdio.h>
        ␣␣␣␣
        ␣␣␣␣int main(void) {
        ␣␣␣␣  printf("Hello world!\n");
        ␣␣␣␣  return 0;
        ␣␣␣␣}
        ␣␣␣␣```
        
        === "C++"
        ␣␣␣␣```cpp
        ␣␣␣␣#include <iostream>
        ␣␣␣␣
        ␣␣␣␣int main(void) {
        ␣␣␣␣  std::cout << "Hello world!" << std::endl;
        ␣␣␣␣  return 0;
        ␣␣␣␣}
        ␣␣␣␣```
        ````
        
        === "C"
            ```c
            #include <stdio.h>
            
            int main(void) {
              printf("Hello world!\n");
              return 0;
            }
            ```
        
        === "C++"
            ```cpp
            #include <iostream>
            
            int main(void) {
              std::cout << "Hello world!" << std::endl;
              return 0;
            }
            ```

If you have any other questions about mkdocs-material (the theme we use), you can also check the [MkDocs Usage Guide](https://github.com/ctf-wiki/ctf-wiki/wiki/Mkdocs-%E4%BD%BF%E7%94%A8%E8%AF%B4%E6%98%8E), which introduces the plugin usage of the mkdocs-material theme.

#### Text Content Format Requirements

-   <a id="CONT-1"></a>CONT-1: All **OI Wiki** text should be marked with bold.

-   <a id="CONT-2"></a>CONT-2: There should be a brief paragraph at the beginning of the page (such as "This page will introduce..."), used to summarize the page content.

    ???+ success "Example"
        This page lists the recommended style guidelines and editing policies for writing in **OI Wiki**.

-   <a id="CONT-3"></a>CONT-3: For pages involving "prerequisites", please add a line **Prerequisites: …** at the beginning, placed before the page summary. Format:

    `Prerequisites: [站内页面1](url1)、[站内页面2](url2)和[站内页面3](url3)`

    ???+ success "Example"
        Prerequisites: [Time Complexity](../basic/complexity.md)
        
        This page will introduce basic computational theory knowledge.

-   <a id="CONT-4"></a>CONT-4: Please pay attention to document structure. The document structure should be very organized with clear hierarchy. Please do not let things like "level 5 headings" happen again, a normal article does not need such a complex structural hierarchy.

-   <a id="CONT-5"></a>CONT-5: Please pay attention to content expression. As an encyclopedia website, the language used in **OI Wiki** should be written and objective. Content that is "smart-alecky" in nature and not very helpful for readers' understanding should not appear in **OI Wiki**.

-   <a id="CONT-6"></a>CONT-6: Please try to provide complete titles for links, or recognizable hints, avoid using bare addresses and vague descriptions like "this" or "here". Every hyperlink should have a clear description to help readers understand where the hyperlink points to.

    It is recommended to use the source article or tab title.

    ???+ failure "Not Recommended"
        ```markdown
        Please refer to [this page](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/syncing-a-fork)
        
        Please refer to <https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/syncing-a-fork>
        ```
        
        Please refer to [this page](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/syncing-a-fork)
        
        Please refer to <https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/syncing-a-fork>

    ???+ success "Recommended"
        ```markdown
        Please refer to GitHub's official help page [Syncing a fork - GitHub Docs](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/syncing-a-fork)
        ```
        
        Please refer to GitHub's official help page [Syncing a fork - GitHub Docs](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/syncing-a-fork)

-   <a id="CONT-7"></a>CONT-7: Due to Markdown format limitations, the `## References and Notes` level 2 heading must be placed at the end of the document.

-   <a id="CONT-8"></a>CONT-8: All numbers used as ordinals are recommended to be in Chinese. Example:
    -   The first term of the sequence.
    -   The first line of the input file.

-   <a id="CONT-9"></a>CONT-9: Please try to avoid using MathJax formulas in headings, regardless of heading level. Using formulas in headings may cause table of contents display errors.[^ref3]

-   <a id="CONT-10"></a>CONT-10: Please pay attention to code readability.

    -   <a id="CONT-10.1.1"></a>CONT-10.1.1: Code should have clear logic, be as concise and easy to understand as possible. Do not over-compress lines, do not introduce too much irrelevant code. Try to avoid content unrelated to the algorithm idea.
    -   <a id="CONT-10.1.2"></a>CONT-10.1.2: It is recommended to add appropriate comments in reference code to help readers understand.

    For C/C++ type languages:

    -   <a id="CONT-10.2.1"></a>CONT-10.2.1: Try to avoid preprocessor directives and macro definitions that affect readability.

    -   <a id="CONT-10.2.2"></a>CONT-10.2.2: Do not use `0` to represent `false`/`NULL`/`nullptr`, etc., do not use `1` to represent `true`, etc.

    -   <a id="CONT-10.2.3"></a>CONT-10.2.3: When declaring [type aliases](https://en.cppreference.com/w/cpp/language/type_alias), using `typedef` is not recommended, using `using` is recommended.

    -   <a id="CONT-10.2.4"></a>CONT-10.2.4: Using macros to define constants is not recommended, using `constexpr`/`const` and other keywords to define constants is recommended.

    -   <a id="CONT-10.2.5"></a>CONT-10.2.5: Using `inline` keyword for functions is not recommended, see [Code Optimization](../lang/optimizations.md#inline---inlining) for details.

    -   <a id="CONT-10.2.6"></a>CONT-10.2.6: Try to avoid complex template metaprogramming techniques like type traits and partial specialization. If needed, add comments to explain the meaning.

        ???+ failure "Not Recommended"
            ```cpp
            --8<-- "docs/intro/code/format/format_1.cpp:not-recommended"
            ```
            
            This code gives a complex implementation of [Greatest Common Divisor](../math/number-theory/gcd.md), where:
            
            -   The first `gcd` takes two unsigned integers `x`, `y`, returns the GCD of `x`, `y`, the return type range ensures it can contain both `x` and `y`.
            -   The second `gcd` takes two integers `x`, `y`, where at least one of `x`, `y` is signed, returns the GCD of `x`, `y`.
            -   The third `gcd` takes more than two integers, returns the GCD of these integers.
            -   The fourth `gcd` takes a container, returns the GCD of all numbers in the container.
            
            For **OI Wiki**, we only care about the algorithm idea of GCD, this code covers too many irrelevant and complex technical details, which should be avoided.

        ???+ success "Recommended"
            ```cpp
            --8<-- "docs/intro/code/format/format_1.cpp:recommended"
            ```
            
            Things like "adding type checking", "handling negative inputs", "making functions support multiple parameters" are more topics that engineering cares about, our focus has always been the algorithm idea.

#### LaTeX Formula Format Requirements

As LaTeX is the preferred typesetting for formulas, we should use it correctly. Therefore we have strict requirements for LaTeX usage. If you want to get started quickly, you can read the table at the end of this chapter.

-   <a id="MATH-1.1"></a>MATH-1.1: The symbols you use should not conflict with the symbols specified in the [Mathematical Symbol Table](./symbol.md).

-   <a id="MATH-1.2"></a>MATH-1.2: Use Roman font for numbers, constants, operators, and functions. Use Italic font for variables and subscripts. LaTeX has predefined some common constants, functions, operators, etc., which we can use directly, including but not limited to:

    ```latex
    \log, \ln, \lg, \sin, \cos, \tan, \sec, \csc, \cot, \gcd, \min, \max, \exp, \inf, \mod, \bmod, \pmod
    ```

    So when entering constants, function names, operators, etc., please first check if Roman font or other fonts should be used. For LaTeX symbol notation, you can refer to [KaTeX's Supported Functions page](https://katex.org/docs/supported.html) (not all), or search for solutions.

    Since writing Roman font lowercase Greek letters in LaTeX is relatively difficult, lowercase Greek letter constants, operators, and functions can use Italic font, such as $\pi$ and $\delta$ in $\delta x$.

    If a function name that is not predefined needs to use Roman font, we can use `$\operatorname{something}$` to produce it, for example we can use `$\operatorname{lcm}$` to produce the Roman font LCM (function) symbol. Similarly, to produce Roman font constants, use `$\mathrm{}$`; to produce Roman font bold symbols, use `$\mathbf{}$`; to produce Italic font bold symbols, use `$\boldsymbol{}$` (such as vector $\boldsymbol{a}$). For multi-letter variables, use `$\textit{}$`. Other non-mathematical content, including English, special symbols, etc., all use `$\text{}$`. For Chinese, we recommend not putting it in LaTeX formulas.

-   <a id="MATH-1.3"></a>MATH-1.3: If an expression needs to wrap to a new line (common in longer display formulas), the following line wrapping rules should be followed:

    -   <a id="MATH-1.3.1"></a>MATH-1.3.1: Place line breaks before $=$, $+$, $-$, $\pm$, $\mp$, if necessary, can also be before $\times$, $\cdot$, $/`:

        $$
        \begin{aligned}
            \mathrm{e}^x &= \sum\limits_{n=0}^{\infty} frac{x^n}{n!} \\
            &= \phantom{+} 1 + x + \frac{x^2}{2} \\
            & \phantom{=} + \frac{x^3}{6} + \frac{x^4}{24} + \dots \\
        \end{aligned}
        $$

    -   <a id="MATH-1.3.2"></a>MATH-1.3.2: The same operator should not appear both before and after a line break,

    -   <a id="MATH-1.3.3"></a>MATH-1.3.3: Line breaks should尽量 not appear in expressions inside parentheses.

-   <a id="MATH-1.4"></a>MATH-1.4: When using fractions in inline text, please use `$\dfrac{}{}$`. For example `$\dfrac{1}{2}$`, effect $\dfrac{1}{2}$, not `$\frac{1}{2}$`, effect $\frac{1}{2}$.

-   <a id="MATH-1.5"></a>MATH-1.5: For binomial coefficients, use `\dbinom{n}{m}`, effect $\dbinom{n}{m}$, instead of `{n \choose m}` (this notation is no longer recommended in LaTeX); similar to the fraction convention above, please do not use `\binom{n}{m}`, effect $\binom{n}{m}$.

-   <a id="MATH-1.6"></a>MATH-1.6: Try to avoid using large operators in inline text (such as $\sum$, $\prod$, $\int$, etc.).

-   <a id="MATH-1.7"></a>MATH-1.7: When no ambiguity will arise, please use `$\times$` instead of asterisk, cross multiply use `$\times$`, dot multiply use `$\cdot$`. For example $a\times b$, $a\cdot b$, not $a\ast b$.

-   <a id="MATH-1.8"></a>MATH-1.8: Please use `$\cdots$` (centered between baseline and topline), `$\ldots$` (at baseline position), `$\vdots$` (vertical ellipsis) instead of `$...$`. For example $a_1,a_2,\cdots a_n$, not $a_1,a_2,... a_n$.

-   <a id="MATH-1.9"></a>MATH-1.9: Please pay attention, do not use any programming language notation in non-code areas, use LaTeX formulas instead. For example, use `$=$` instead of `$==$` (e.g., $a=b$, not $a==b$), use `` `a<<1` `` or `$a\times 2$` instead of `$a<<1$`, use `$a\bmod b$` instead of `$a\%b$` (e.g., $a\bmod b$, not $a\%b$) etc.

-   <a id="MATH-1.10"></a>MATH-1.10: Do not use bracket chaining in formulas (i.e., the representation for C++ multi-dimensional arrays) but use more subscripts. That is $a_{i,j,k}$ instead of $a[i][j][k]$. When subscripts in formulas are complex, it is recommended to use multivariate functions ($f(i,j,k)$) or inline code format. For simple unary functions, `$f_i$`, `$f(i)$` or `$f[i]$` can all be used.

-   <a id="MATH-1.11"></a>MATH-1.11: For unity and convenience in complexity analysis, please use `$O()$` directly for the big O notation instead of `$\mathcal O()$`.

-   <a id="MATH-1.12"></a>MATH-1.12: When representing equivalence relations, please use `$\iff$`, effect $\iff$, instead of `$\Leftrightarrow$`, effect $\Leftrightarrow$.

-   <a id="MATH-1.13"></a>MATH-1.13: The `cases` environment for piecewise functions **can only have two columns** (i.e., one `&` separator).

-   <a id="MATH-1.14"></a>MATH-1.14: Please do not overuse LaTeX formulas. This will not only cause slow page loading (because MathJax's inefficiency is well-known), but also cause page layout confusion. We usually use LaTeX formula fonts to represent variable names. Our suggestion is that unless necessary, try to reduce the **massive** mixed use of formulas and normal text fonts, unless necessary, try not to use formulas, for example:

    ```LaTeX
    We will learn about SPFA minimum cost flow in $Network-flow$, which needs to use the Edmonds–Karp algorithm for augmentation.
    ```

    This is a typical example of **overusing formula fonts**. (To use italic in pages, use `*text*` for representation.)

-   <a id="MATH-1.15"></a>MATH-1.15: Please use the corresponding LaTeX symbols correctly, especially special symbols like Greek letters in formulas. For example, for Euler's totient function please use `$\varphi$`, for the diameter of a circle please use `$\Phi$`, for golden ratio please use `$\phi$`. Although these symbols all represent the Greek letter Phi, they have different meanings in different contexts. Remember **not to use the input method's insert special symbol** feature to insert such symbols.

    Also, due to LaTeX history, the symbol for empty set should be `$\varnothing$` not `$\emptyset$`; other symbols should follow the [Mathematical Symbol Table](./symbol.md) for notation.

We can use a table to summarize the above content. Note this table does not give examples for all symbol usages, only common mistakes. Similar cases can be analogized.

| Non-compliant Usage                     | Rendered Effect              | Compliant Usage                                  | Rendered Effect                                |
| ---------------------------- | ----------------- | ---------------------------------------- | ----------------------------------- |
| `$log, ln, lg$`              | $log, ln, lg$     | `$\log$, $\ln$, $\lg$`                   | $\log$，$\ln$，$\lg$                  |
| `$sin, cos, tan$`            | $sin, cos, tan$   | `$\sin$, $\cos$, $\tan$`                 | $\sin$，$\cos$，$\tan$                |
| `$gcd, lcm$`                 | $gcd, lcm$        | `$\gcd$, $\operatorname{lcm}$`           | $\gcd$，$\operatorname{lcm}$         |
| `$e$, $\text{e}$, e`（natural log base） | $e$，$\text{e}$, e | `$\mathrm{e}$`                           | $\mathrm{e}$                        |
| `$i$, $\text{i}`, i`（imaginary unit）   | $i$，$\text{i}$, i | `$\mathrm{i}$`                           | $\mathrm{i}$                        |
| `$ 小于 a 的质数 $`               | $小于 a 的质数$        | `less than $a$ prime                              | 小于 $a$ 的质数                          |
| `$...$`                      | $...$             | `$\cdots$, $\ldots$, $\vdots$, $\ddots$` | $\cdots$，$\ldots$，$\vdots$，$\ddots$ |
| `$a*b$`（product of two numbers）               | $a*b$             | `$a\times b$, $a\cdot b$`                | $a\times b$，$a\cdot b$              |
| `$SPFA$`（English name）               | $SPFA$            | `SPFA`                                   | SPFA                                |
| `$a==b$`                     | $a==b$            | `$a=b$`                                  | $a=b$                               |
| `$f[i][j][k]$`               | $f[i][j][k]$      | `$f_{i,j,k}$, $f(i,j,k)$`                | $f_{i,j,k}$，$f(i,j,k)$              |
| `$R,N^*$`（set）                | $R,N^*$           | `$\mathbf{R}$, $\mathbf{N}^*$`           | $\mathbf{R}$，$\mathbf{N}^*$         |
| `$\emptyset$`                | $\emptyset$       | `$\varnothing$`                          | $\varnothing$                       |
| `$size$`                     | $size$            | `$\textit{size}$`                        | $\textit{size}$                     |

#### Additional Format Requirements for Mathematical Formulas

Please note, although the syntax for entering formulas is very similar to the actual LaTeX typesetting system, **MathJax and LaTeX are two completely unrelated things**, MathJax only uses a syntax very similar to LaTeX. In fact, there are many subtle differences between the two, and these differences often cause formulas written to not be compatible between the two.

Since **OI Wiki** uses the LaTeX typesetting engine to develop the PDF export tool, it is necessary to emphasize the compatibility of formulas between MathJax and LaTeX. **Please pay attention to the following points when writing mathematical formulas in the wiki.**

These rules have been made as many compromises as possible towards MathJax. The export tool has compatible with some notations that could only output normally in MathJax.

-   <a id="MATH-2.1"></a>MATH-2.1: Please use `\begin{aligned} ... \end{aligned}` for multi-line aligned formulas;

-   <a id="MATH-2.2"></a>MATH-2.2: If these multi-line aligned formulas need **numbering**, use `align` or `equation` environment;

-   <a id="MATH-2.3"></a>MATH-2.3: Do not use `split`, `eqnarray` environment;

-   <a id="MATH-2.4"></a>MATH-2.4: Do not use `\lt`, `\gt` to represent greater than and less than, please use `<`, `>` directly;

-   <a id="MATH-2.5"></a>MATH-2.5: Do not use `\\` directly for line breaks (for formulas that need to wrap, wrap in `aligned` or other multi-line environments);

-   <a id="MATH-2.6"></a>MATH-2.6: To output the LaTeX symbol $\rm{\LaTeX}$, please use `$\rm{\LaTeX}$`, not `mathrm`; (`\LaTeX` in TeX typesetting system is a command that cannot be used in math mode, and `\mathrm` cannot be used in normal mode; also, although the `\text` command outputs normally on TeX, in MathJax the parameter of the `\text` command will be output as-is instead of being escaped);

-   <a id="MATH-2.7"></a>MATH-2.7: Chinese text in mathematical formulas **must be placed inside the `\text{}` command**, while variables, numbers, operators, and function names must be placed **outside** the `\text{}` command. **Please do not nest mathematical formulas inside the `\text{}` command**;

-   <a id="MATH-2.8"></a>MATH-2.8: When using the `array` environment, please pay attention to **keeping the actual number of columns consistent with the number of alignment symbols**. For example in the following formula, there are actually 3 columns (`&` is the column separator), so 3 alignment symbols are needed (`l`/`r`/`c` represent left, right, center alignment respectively).

    ```latex
    $$
    \begin{array}{lll}
    F_1=\{\frac{0}{1},&&\frac{1}{1}\}\\
    F_2=\{\frac{0}{1},&\frac{1}{2},&\frac{1}{1}\}\\
    \end{array}
    $$
    ```

#### Pseudocode Format

Pseudocode specific format has no strict requirements, please refer to Introduction to Algorithms or academic papers. Note do not write in Python.

<a id="PCOD-1"></a>PCOD-1: Use LaTeX in the wiki for writing pseudocode, overall in an array environment, indentation uses `$\qquad$`, text description uses `$\text$`, keywords use `$\textbf$`, multi-letter variables use `$\textit$`, assignment uses `$\gets$`.

Reference example:

$$
\begin{array}{l}
\textbf{Input. } \text{The edges of the graph } e , \text{ where each element in } e \text{ is } (u, v, w) \\
\text{ denoting that there is an edge between } u \text{ and } v \text{ weighted } w . \\
\textbf{Output. } \text{The edges of the MST of the input graph}. \\
\textbf{Method. } \\
\begin{array}{ll} 
1 &  \textit{result} \gets \varnothing \\
2 &  \text{sort } e \text{ into nondecreasing order by weight } w \\ 
3 &  \textbf{for} \text{ each } (u, v, w) \text{ in the sorted } e \\ 
4 &  \qquad \textbf{if } u \text{ and } v \text{ are not connected in the union-find set } \\
5 &  \qquad\qquad \text{connect } u \text{ and } v \text{ in the union-find set} \\
6 &  \qquad\qquad \textit{result} \gets \textit{result}\;\bigcup\ \{(u, v, w)\} \\
7 &  \textbf{return } \textit{result}
\end{array}
\end{array}
$$

```latex
$$
\begin{array}{l}
\textbf{Input. } \text{The edges of the graph } e , \text{ where each element in } e \text{ is } (u, v, w) \\
\text{ denoting that there is an edge between } u \text{ and } v \text{ weighted } w . \\
\textbf{Output. } \text{The edges of the MST of the input graph}. \\
\textbf{Method. } \\
\begin{array}{ll} 
1 &  \textit{result} \gets \varnothing \\
2 &  \text{sort } e \text{ into nondecreasing order by weight } w \\ 
3 &  \textbf{for} \text{ each } (u, v, w) \text{ in the sorted } e \\ 
4 &  \qquad \textbf{if } u \text{ and } v \text{ are not connected in the union-find set } \\
5 &  \qquad\qquad \text{connect } u \text{ and } v \text{ in the union-find set} \\
6 &  \qquad\qquad \textit{result} \gets \textit{result}\;\bigcup\ \{(u, v, w)\} \\
7 &  \textbf{return } \textit{result}
\end{array}
\end{array}
$$
```

#### Code Block Format Requirements

There are currently two types of code blocks: snippets and example problems.

Regarding snippet code:

-   <a id="CODE-1.1"></a>CODE-1.1: If the code snippet is short enough and unnecessary to test, it can be directly modified in the Markdown document.
-   <a id="CODE-1.2"></a>CODE-1.2: Since code embedded in Markdown documents is difficult to automate test, it is recommended to use the example code format to insert snippet code. You can choose the [multi-file compilation scheme](https://github.com/OI-wiki/OI-wiki/pull/5729) or [Snippet Sections](https://facelessuser.github.io/pymdown-extensions/extensions/snippets/#snippet-sections) syntax:

    Multi-file compilation example: [Bubble Sort](https://github.com/OI-wiki/OI-wiki/blob/c35defebff6cea072d6cfeb359642f6fd84e66c7/docs/basic/bubble-sort.md?plain=1#L48). The main text references [bubble-sort_1.cpp](https://github.com/OI-wiki/OI-wiki/blob/c35defebff6cea072d6cfeb359642f6fd84e66c7/docs/basic/code/bubble-sort/bubble-sort_1.cpp), test code is placed in [bubble-sort_1.aux1.cpp](https://github.com/OI-wiki/OI-wiki/blob/c35defebff6cea072d6cfeb359642f6fd84e66c7/docs/basic/code/bubble-sort/bubble-sort_1.aux1.cpp).

    Snippet Sections example: [Prefix Sum](https://github.com/OI-wiki/OI-wiki/blob/c7cf6d6de13b44757f1d0528e952349beb921f8a/docs/basic/prefix-sum.md?plain=1#L37). The test part in [prefix-sum_1.cpp](https://github.com/OI-wiki/OI-wiki/blob/c7cf6d6de13b44757f1d0528e952349beb921f8a/docs/basic/code/prefix-sum/prefix-sum_1.cpp) is not needed in the main text, so the main code snippet is inserted.

    **Note**: Do not use [Snippet Lines](https://facelessuser.github.io/pymdown-extensions/extensions/snippets/#snippet-lines) syntax.

    To improve code reusability, you can also split the code into header files, and reference them in different test codes. If the complete test code needs to appear in the main text as a reference implementation for an example problem, then in the main text should use Snippet Sections syntax to concatenate into a single file code for readers to read. Example: [Red-Black Tree](https://github.com/OI-wiki/OI-wiki/blob/3b721e22ea60d59a2687a9b10555263de7bdc2f0/docs/ds/rbtree.md?plain=1#L218-L231).

Regarding example problem code:

-   <a id="CODE-2.1"></a>CODE-2.1: The representation form of example problem code is `--8<-- "path"`, code is stored in `path`. The path is usually `docs/theme/code/content/content_number.cpp`.

-   <a id="CODE-2.2"></a>CODE-2.2: When modifying example problem code, please ensure your code is correct. Example problem code all have a set of test data, stored in `/docs/theme/examples/content/content_number.in/ans`.

If you need to add an example problem:

-   Please add your example problem code in `docs/theme/code/content` and number it. Usually, there is already one or more code files in that `content` folder. Example: if you need to modify the code for `dag.md`, then the path is `docs/dp/code/dag`, where `dp` is the theme and `dag` is the content.

-   If you need to add an example problem code at the end of all example problems, please continue the numbering. For example, if `code/prefix-sum/prefix-sum_3.cpp` already exists, if you need to add one after the last example problem, please name your code `prefix-sum_4.cpp` and add it to `docs/basic/code/prefix-sum`.

-   If you need to add an example problem code in the middle of the article, please insert and change the original numbering. For example, if `prefix-sum_2.cpp` and `prefix-sum_3.cpp` already exist, if you need to add another example between the second and third examples, please name your code `prefix-sum_3.cpp` and rename the original `prefix-sum_3.cpp` to `prefix-sum_4.cpp` while **synchronously modifying the numbering in both the Markdown document and the test data folder**.

-   **Don't forget, you also need to add a set of test data for your code to ensure this code can run successfully.** You need to add a set of test data in the `docs/theme/examples/content` folder, store the input data as `content_number.in`, and store the standard answer as `content_number.ans`.

-   Finally, you can add the code to the document. Please directly use the format for adding code blocks, and write the inside of the code block directly in the format `--8<-- "your code path"`.

**OI Wiki** will do cross-platform testing on example problem code. To ensure your code can pass testing, please follow these rules:

-   <a id="CODE-3.1"></a>CODE-3.1: Your code needs to compile and run under C++14, C++17, and C++20 standards simultaneously.
-   <a id="CODE-3.2"></a>CODE-3.2: Do not use non-standard header files like `<bits/stdc++.h>`, `<bits/extc++.h>`.
-   <a id="CODE-3.3"></a>CODE-3.3: The standard answer file should not have extra spaces.
-   <a id="CODE-3.4"></a>CODE-3.4: Do not use [alternative tokens](https://en.cppreference.com/w/cpp/language/operator_alternative#Alternative_tokens).
-   <a id="CODE-3.5"></a>CODE-3.5: When using [aggregate initialization](https://en.cppreference.com/w/cpp/language/aggregate_initialization), `object{args}` cannot be written as `(object){args}`.
-   <a id="CODE-3.6"></a>CODE-3.6: When using [operator overloading](https://en.cppreference.com/w/cpp/language/operators), pay attention to the format, for example when overloading comparison operators using member function syntax, do not omit the `const` qualifier.
-   <a id="CODE-3.7"></a>CODE-3.7: Do not use macro definitions like `#define int long long`.