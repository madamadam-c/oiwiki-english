author: ouuan, akakw1, Ir1d, partychicken, Xeonacid

This page is an introductory tutorial for Emacs.

> 15 minutes to get started with Emacs.

## Introduction

Emacs is a very easy-to-use editor. With just a few lines of configuration, you can use it, but it takes a certain amount of time to become very proficient in using Emacs for various tasks.

As an introductory tutorial, this only introduces the basic functions of Emacs and the methods to conveniently write and debug code with Emacs.

## Getting Started

### Commands

Commands play a big role in Emacs.

You can use the Application key[^note1] (on Windows systems Emacs doesn't have this key assigned, you need to set it manually) or the shortcut `M-x` (<kbd>Alt</kbd>+<kbd>x</kbd>) to open the command input. After inputting, press Enter to execute the command.

Usually, the commands `es` or `eshell` are used to open Eshell (similar to a terminal).

Input commands can usually be replaced with shortcuts.

### Buffers

Buffers are open files and processes. Without saving, modifications in the buffer will not modify the file.

You can switch buffers by clicking the buffer name at the bottom of the buffer area or using shortcuts.

### Compiling, Debugging, and Running

The entry point for compiling and debugging functions is in the Tools dropdown menu in the top menu bar. Users can also use commands or customize shortcuts to use the compiling and debugging functions.

You can use the terminal or Eshell to run programs.

After pressing Debug (gud-gdb) in Tools, input the program name (it is usually automatically filled, but if you save the program elsewhere midway or open two programs that need debugging, **the automatically filled filename may be wrong**) to start debugging.

### Split Windows

This function allows users to view the contents of various buffers at the same time without switching back and forth, which is convenient for testing and debugging code.

Split windows can display multiple windows at the same time. You can resize the windows by dragging the edges of the windows.

Some shortcuts:

-   Delete split "C-x 0": Delete this split
-   Split horizontally "C-x 3": Split this window horizontally into two
-   Split vertically "C-x 2": Split this window vertically into two

The recommended window layout is to divide the window into four parts: first split horizontally, adjust one part's width to about 3/4 of the screen as the editing window. Split the other part horizontally: one part as the window for debugging and compiling information display, and the other part split vertically: one part for opening the input file, one part for opening the output file.

![](./images/emacs.png)

### Shortcuts

Emacs has extremely rich shortcuts, which can greatly improve work efficiency. Users can customize shortcuts or set shortcut mappings in the configuration.

Because there are too many shortcuts, the use of Emacs shortcuts is different from operating systems.

For convenience, the following conventions are made:

| Character | Key               |
| -- | --------------- |
| C  | <kbd>Ctrl</kbd> |
| M  | <kbd>Alt</kbd>  |
| ?  | Any key            |

Generally there are three types:

-   `F?`, `ESC`: Directly press the corresponding function key.
-   `M-?`, `C-?`, `C-M-?`: Press <kbd>Alt</kbd> or <kbd>Ctrl</kbd> together with `?`.
-   `? ?`: First press the key represented by the first `?`, release, then press the key represented by the second `?`.

Below are some commonly used shortcuts:

-   `C-x h`: Select all
-   `C-x left`, `C-x right`: Switch to previous/next buffer
-   `C-x d`: Open a directory
-   `C-x C-f`: Open a file (if the file doesn't exist, create a new file)

## Customization

The freshly installed Emacs looks ugly and is not easy to use, so it needs to be customized.

Since configurations are hard to remember, it is recommended not to memorize the parts that can be set directly.

### Direct Settings

-   Options: `Highlight Matching Parentheses` highlight matching brackets
-   Options: `Blink Cursor` set cursor blinking
-   Options Show/Hide: `Tool Bar` show/hide toolbar (shown by default, recommended to hide)
-   Options: `Use CUA Keys` after checking, you can use Ctrl + C, Ctrl + V and other shortcuts for copy and paste
-   Options Customize-Emacs: `Custom Theme` select color scheme, after selection need to click save
-   Options: `Save Options` **save configuration**

### Configuration

Show hidden files in the home directory (on Windows systems in the **user directory** `AppData\Roaming` directory), ".emacs" is the configuration file (if it doesn't exist, it means it wasn't saved before), open and modify it. If Emacs is already open, you need to restart Emacs for the configuration to take effect.

The recommended configuration for exams is as follows:

```text
;;Set one-key compile can add parameters by yourself hard to memorize not recommended for exams don't rely on one-key compile
(defun compile-file ()(interactive)(compile (format "g++ -o %s %s -g -lm -Wall" (file-name-sans-extension (buffer-name))(buffer-name))))
(global-set-key [f9] 'compile-file)
;;;;Set compile shortcut (if one-key compile is set don't conflict with one-key compile)
;;(global-set-key [f9] 'compile)

(global-set-key (kbd "C-a") 'mark-whole-buffer) ;;Select all shortcut
(global-set-key (kbd "C-z") 'undo) ;;Undo shortcut
(global-set-key [f10] 'gud-gdb) ;;GDB debug shortcut
(global-set-key (kbd "RET") 'newline-and-indent) ;;Newline auto indent
(global-set-key (kbd "C-s") 'save-buffer) ;;Set save shortcut
(setq-default kill-ring-max 65535) ;;Expand undo records

;;C++ code style generally controls indent rules
;;;"bsd" all braces on new lines
;;;"java" all braces on same line. else follows right brace
;;;"awk" only braces next to namespace, class definition, function definition on new lines. else follows right brace
;;;"linux" only braces next to namespace, class definition, function definition on new lines. else follows right brace generally this style should have 8 space indent
(setq-default c-default-style "awk")
```

??? note "Full Configuration"
    ```text
    ;;Set one-key compile
    (defun compile-file ()(interactive)(compile (format "g++ -o %s %s -g -lm -Wall" (file-name-sans-extension (buffer-name))(buffer-name))))
    (global-set-key [f9] 'compile-file)
    ;;;;Set compile shortcut (if one-key compile is set don't conflict with one-key compile)
    ;;(global-set-key [f9] 'compile)
    
    ;;Exam essentials
    (global-set-key (kbd "C-a") 'mark-whole-buffer) ;;Select all shortcut
    (global-set-key (kbd "C-z") 'undo) ;;Undo shortcut
    (global-set-key [f10] 'gud-gdb) ;;GDB debug shortcut
    (global-set-key (kbd "RET") 'newline-and-indent) ;;Newline auto indent
    (global-set-key (kbd "C-s") 'save-buffer) ;;Set save shortcut
    (setq-default kill-ring-max 65535) ;;Expand undo records
    ;;(define-key key-translation-map [apps] (kbd "M-x")) ;;Set command shortcut on windows system
    
    ;;Set indent
    ;;;C++ code indent length
    (setq-default c-basic-offset 4)
    ;;;Use tab for indent
    (setq-default indent-tabs-mode t)
    ;;;tab length must be consistent with indent length
    (setq-default default-tab-width 4)
    (setq-default tab-width 4)
    
    ;;Set default encoding environment
    (set-language-environment "UTF-8")
    (set-default-coding-systems 'utf-8)
    
    ;;Don't show welcome page
    (setq-default inhibit-startup-screen t)
    
    ;;Set title
    (setq-default frame-title-format "")
    
    ;;Show line numbers
    (global-display-line-numbers-mode t)
    
    ;;Highlight
    (global-hl-line-mode 1);;Highlight current line
    (show-paren-mode t);;Highlight matching brackets
    (global-font-lock-mode t);;Syntax highlight
    
    ;;Allow emacs and external programs to paste seems allowed by default
    (setq-default x-select-enable-clipboard t)
    
    ;;Set font to Ubuntu Mono 16, will report error if font doesn't exist
    (set-face-attribute 'default nil :font "Ubuntu Mono-16")
    ;(set-face-attribute 'default nil :font "Consolas-16") ;;Use this for windows system
    
    ;;Mouse wheel support
    (mouse-wheel-mode t)
    
    ;;Set cursor shape to vertical line (default is block)
    (setq-default cursor-type 'bar')
    
    ;;Change yes/no to y/n
    (fset 'yes-or-no-p 'y-or-n-p)
    
    ;;Transparency
    (set-frame-parameter (selected-frame) 'alpha (list 85 60))
    (add-to-list 'default-frame-alist (cons 'alpha (list 85 60)))
    
    ;;Reduce page scroll lines to prevent whole page scrolling
    (setq-default scroll-margin 3 scroll-conservatively 10000)
    
    ;;Optimize file tree structure
    (ido-mode t)
    
    ;;Color scheme
    (setq default-frame-alist
             '((vertical-scroll-bars)
               (top . 25)
               (left . 45)
               (width . 120)
               (height . 40)
               (background-color . "grey15")
               (foreground-color . "grey")
               (cursor-color . "gold1")
               (mouse-color . "gold1")
               (tool-bar-lines . 0)
               (menu-bar-lines . 1)
               (scroll-bar-lines . 0)
               (right-fringe)
               (left-fringe)))
    
    (set-face-background 'highlight "gray5")
    (set-face-foreground 'region "cyan")
    (set-face-background 'region "blue")
    (set-face-foreground 'secondary-selection "skyblue")
    (set-face-background 'secondary-selection "darkblue")
    (set-cursor-color "wheat")
    (set-mouse-color "wheat")
    
    (custom-set-variables
     '(ansi-color-faces-vector
       [default default default italic underline success warning error])
    ;;Enable Ctrl-x Ctrl-c Ctrl-v = cut copy paste
     '(cua-mode t nil (cua-base))
     '(show-paren-mode t)
    ;;Hide toolbar
     '(tool-bar-mode nil))
    ;;Turn off cursor blinking
     '(blink-cursor-mode nil)
    (custom-set-faces)
    ```

### Extended Reading

To start Emacs in terminal mode, add the parameter `-nw` when starting. Emacs has multiple variants, such as [GCC Emacs](http://akrl.sdf.org/gccemacs.html) which uses native-comp to reduce latency and its pure GTK version variant, and Emacs Macport optimized for macOS.

Emacs has a centralized software repository. After configuration, you can install plugins via `M-x package-install`. Using [mirrors](https://mirrors.bfsu.edu.cn/help/elpa/) can speed up downloads.

Emacs can use the Language Server Protocol to improve the editing experience. The currently recommended C++ backend is [Clangd](https://clangd.llvm.org/). The frontend can use [Eglot](https://github.com/joaotavora/eglot) or [Emacs LSP](https://emacs-lsp.github.io/lsp-mode/). Refer to [this entry](https://github.com/joaotavora/eglot#historical-differences-to-lsp-modeel) which may help with choosing the frontend.

Org Mode documents with the `.org` extension can be converted to Markdown documents via [Pandoc](https://pandoc.org/).

## References and Notes

[^note1]: This key's function is to bring up the right-click menu, generally the first key to the left of the right <kbd>Ctrl</kbd>.