author: CoelacanthusHex

## Software Introduction

Kate is a cross-platform text editor with many features. Kate also comes with multiple plugins, including an embedded terminal that allows you to launch console commands directly from Kate, a powerful search and replace plugin, and a preview plugin that can render MD, HTML, and even SVG files. It supports data recovery from system crashes via swap files, auto-completion with parameter hints, and also supports [LSP (Language Server Protocol)](https://microsoft.github.io/language-server-protocol/) for more powerful completion.

## Download and Installation

You can open [Kate Official Website](https://kate-editor.org/), then go to [Get It page](https://kate-editor.org/zh-cn/get-it/). Then, install according to your system and preferred installation method.

## Usage and Features

### Swap File to Prevent Data Loss

Similar to Vim, Kate writes unsaved changes to a swap file (generally the original filename with a dot and `.kate-swp` appended). If there is a power outage or program crash, the next time you start, you won't lose unsaved changes.

### Syntax Highlighting

Kate supports syntax highlighting for over 300 languages. Generally, Kate can automatically select the corresponding language for syntax highlighting, but occasionally there are errors. At this time, you can click the button at the very bottom right to select the correct language.

#### Writing Your Own Syntax Highlighting Files

Although Kate supports syntax highlighting for over 300 languages, some languages are still not covered. At this time, you can write your own syntax highlighting files.
The files that come with Kate are located at [Syntax Highlighting Powered by KSyntaxHighlighting Framework](https://kate-editor.org/syntax/). For syntax reference, see [Working with Syntax Highlighting](https://docs.kde.org/trunk5/en/kate/katepart/highlight.html). For where to place the completed files, see [Syntax definition files](https://github.com/KDE/syntax-highlighting#syntax-definition-files). [CoelacanthusHex/dotfiles@80a913c/pam_env.xml](https://github.com/CoelacanthusHex/dotfiles/blob/80a913cc5b90d7878eb0ed77b8df2d9b97926272/kate/.local/share/katepart5/syntax/pam_env.xml) has a configuration file written by the author for reference.

### Switching Language

Click `Settings` in the top toolbar, then click `Configure Language`, then select the language. Note that you can select alternative languages.

### Encoding and Line Endings

Kate can automatically detect what encoding the current file uses. If it detects incorrectly, you can click the second-to-last button at the bottom right to select the correct encoding.

At the same time, Kate can also automatically detect what line ending the current file uses. If it detects incorrectly, you can click `Tools` → `End of Line` to select the correct line ending.

### Find and Replace

Click `Edit` → `Find` (shortcut <kbd>Ctrl</kbd>+<kbd>F</kbd>) to open the "Find" page. Click `Edit` → `Replace` (shortcut <kbd>Ctrl</kbd>+<kbd>R</kbd>) to open the "Find and Replace" page. Also, clicking "Search & Replace" in the bottom left can open the "Find and Replace" page.

The specific operation is not much different from other editors, but it supports some additional features, such as:

1.  Case sensitivity
2.  Regular expression support (including capture groups)
3.  Range from current file to multiple files to current project
4.  Selective replacement of search results

### Language Server Protocol

Since version 19.12, Kate supports LSP Client. Initially, it only supported C/C++, D, Fortran, Go, Latex/BibTeX, OCaml, Python, Rust. Now it supports languages as shown in the table below:

|     Language     |                                       LSP Server                                      |
| :--------: | :-----------------------------------------------------------------------------------: |
|    Bash    |        [bash-language-server](https://github.com/bash-lsp/bash-language-server)       |
|    LaTeX   |                         [texlab](https://texlab.netlify.com/)                         |
|   BibTeX   |                         [texlab](https://texlab.netlify.com/)                         |
|      C     |                     [clangd](https://clang.llvm.org/extra/clangd/)                    |
|     C++    |                     [clangd](https://clang.llvm.org/extra/clangd/)                    |
|      D     |                      [serve-d](https://github.com/Pure-D/serve-d)                     |
|   Fortran  |              [fortls](https://github.com/hansec/fortran-language-server)              |
|     Go     |                       [gopls](https://golang.org/x/tools/gopls)                       |
|   Haskell  | [haskell-language-server-wrapper](https://github.com/haskell/haskell-language-server) |
| JavaScript | [typescript-language-server](https://github.com/theia-ide/typescript-language-server) |
|    OCaml   |                     [ocamllsp](https://github.com/ocaml/ocaml-lsp)                    |
|    Perl    |        [Perl-LanguageServer](https://github.com/richterger/Perl-LanguageServer)       |
|   Python   |               [pyls](https://github.com/palantir/python-language-server)              |
|    Rust    |                        [rls](https://github.com/rust-lang/rls)                        |
| TypeScript | [typescript-language-server](https://github.com/theia-ide/typescript-language-server) |
|      R     |          [RLanguageServer](https://github.com/REditorSupport/languageserver)          |
|     zig    |                         [zls](https://github.com/zigtools/zls)                        |

To enable LSP-related features, go to `Settings` → `Configure Kate` in the menu bar, then select `LSP Client` in `Plugins` to enable related features. When opening a file of the corresponding language, Kate will automatically pull up the corresponding LSP Server.

#### Adding Configuration

Additionally, users can manually write configuration. The specific format is:

```json
{
    "servers": {
        "bibtex": {
            "use": "latex",
            "highlightingModeRegex": "^BibTeX$"
        },
        "c": {
            "command": ["clangd", "-log=error", "--background-index"],
            "commandDebug": ["clangd", "-log=verbose", "--background-index"],
            "url": "https://clang.llvm.org/extra/clangd/",
            "highlightingModeRegex": "^(C|ANSI C89|Objective-C)$"
        },
        "cpp": {
            "use": "c",
            "highlightingModeRegex": "^(C\\+\\+|ISO C\\+\\+|Objective-C\\+\\+)$"
        },
        "haskell": {
            "command": ["haskell-language-server-wrapper", "--lsp"],
            "rootIndicationFileNames": ["*.cabal", "stack.yaml", "cabal.project", "package.yaml"],
            "url": "https://github.com/haskell/haskell-language-server",
            "highlightingModeRegex": "^Haskell$"
        },
        "latex": {
            "command": ["texlab"],
            "url": "https://texlab.netlify.com/",
            "highlightingModeRegex": "^LaTeX$"
        },
        "rust": {
            "command": ["rls"],
            "rootIndicationFileNames": ["Cargo.lock", "Cargo.toml"],
            "url": "https://github.com/rust-lang/rls",
            "highlightingModeRegex": "^Rust$"
        }
    }
}
```

Each item in `servers` represents a language. For this language, `command` represents the command used to start the LSP Server. `command` is an array, which is the result of splitting the required command by spaces; `url` is the LSP URL; `rootIndicationFileNames` is used to determine the project root directory files; `highlightingModeRegex` matches a certain syntax highlighting name to determine which LSP to use. If there is a `use` item, it means using the configuration of the language corresponding to the `use` item.

This configuration item is located in `Settings` → `Configure Kate` → `LSP Client` → `User Server Settings`. The `LSP Client` part is only visible after enabling the `LSP Client` plugin in `Plugins`.

### Built-in Terminal

???+ note "Note"
    The built-in terminal depends on KDE's Konsole[^ref1], and Konsole is a \*nix exclusive package. That is, this feature is not available on Windows.

Press <kbd>F4</kbd> to open or close the built-in terminal. You can also click the `Terminal` button in the bottom left to open it. The current directory of the built-in terminal will automatically stay the same as the current file, and change as you select files. Otherwise, it's not much different from a regular terminal.

### External Tools

Click `Tools` → `External Tools` to execute.

Click `Tools` → `External Tools` → `Configure` to configure external tools.

#### Adding External Tools

##### Adding from Preset Configuration

After entering the configuration page, click `Add` in the bottom left → `Add from Default Tools`, then click the corresponding tool.

##### Adding Manually Written Configuration

After entering the configuration page, click `Add` in the bottom left → `Add Tool`, then fill in according to the prompts. You can refer to [this document (English)](https://docs.kde.org/trunk5/en/kate/kate/kate-application-plugin-external-tools.html) to write your own external tool configuration. Note that you can click the following icon to see available variables.

![](images/kate-3-var.png)

#### Common External Tools

##### Compiling and Executing Single C++ File

On \*nix systems, open any C++ source file, find `Compile Run cpp` in external tools, and click it.

???+ note "For Windows Users"
    By default, because the executable of this tool is `sh`, this tool is not usable on Windows. However, users can modify this tool to make it usable on Windows.
    
    To modify, first ensure your system has a usable C++ compiler. Then add `Compile Run cpp` from default tools, change the executable from `sh` to `powershell`, and change the argument to `-ExecutionPolicy Bypass -Command "g++ %{Document:FilePath} -o %{Document:FileBaseName}.exe;./%{Document:FileBaseName}.exe"` [^note1][^note2].

##### Git Blame

Open any file, find `git blame` in external tools. After clicking, a window will open showing the git blame results.

##### Formatting

Formatting requires the corresponding package or application to be available. For example, C/C++ formatting requires `clang-format` to be available. For other languages, users can go to external tool configuration to see its default executable as reference.

Open any source file, find `Format with xxx` in external tools and click it. Additionally, for C/C++ source files, `clang-format` can format the selected text.

### Git Blame

To enable this feature, go to `Settings` → `Configure Kate` in the menu bar, then select `Git Blame` in `Plugins`.

After enabling this feature, Kate will display in a lighter font after each line when it was last modified by whom in Git. Hovering over the text will show a popup with specific commit information.

## Related External Links

-   [The Kate Handbook](https://docs.kde.org/stable5/en/kate/kate/kate.pdf)
-   [How to write your own LSP client configuration (English)](https://docs.kde.org/trunk5/en/kate/kate/kate-application-plugin-lspclient.html#Configuration)
-   [How to write your own external tools configuration (English)](https://docs.kde.org/trunk5/en/kate/kate/kate-application-plugin-external-tools.html)

## References and Footnotes

[^ref1]: In the description of this package in [Arch Linux](https://archlinux.org/packages/extra/x86_64/kate/), it optionally depends on `konsole`, described as `open a terminal in Kate`.

[^note1]: If `g++` is not in the `PATH` environment variable, change it to the compiler's absolute path

[^note2]: Or, if using Clang, change `g++` to `clang++`.