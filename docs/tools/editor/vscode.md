author: NachtgeistW, Ir1d, ouuan, Enter-tainer, Xeonacid, ChungZH, keepthethink, abc1763613206, partychicken, Chrogeek, xkww3n, HeliumOI, Pinghigh, xiaofu-15191, Sekakou, fuxianhu

## Introduction

Visual Studio Code (hereinafter VS Code) is a code editor developed by Microsoft that supports Windows, Linux, and macOS operating systems and is open source. It is written in TypeScript and uses the Electron architecture. It has built-in support for JavaScript, TypeScript and Node.js, and provides a rich extension ecosystem for other languages (such as C, C++, Java, Python, PHP, Go).

Official website: [Visual Studio Code - The open source AI code editor](https://code.visualstudio.com/)

Before reading the following content, it is recommended that you first briefly understand the basic usage of VS Code: [Get started](https://code.visualstudio.com/docs/getstarted/getting-started)

## Running Code Using C/C++ Compile Run Extension

C/C++ Compile Run is a plugin focused on compiling and running single C/C++ files. It eliminates the cumbersome configuration steps in traditional C/C++ plugins, making it very suitable for competitive programming needs, quick to get started, and simple to operate.

Open VS Code, click the "Extensions" icon on the left sidebar (or press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>X</kbd>), enter `C++` in the search box, find C/C++ Compile Run, and click "Install".

![](./images/vscode-14.png)

After installation, no additional configuration is needed. The plugin will automatically adapt to the configured MinGW compiler based on environment variables.

Open the file you need to run, click the triangle icon in the upper right corner to run the code.

Shortcuts:

-   <kbd>F6</kbd>- Compile and run in VS Code's built-in integrated terminal
-   <kbd>F7</kbd>- Compile with custom parameters and run in VS Code's built-in integrated terminal
-   <kbd>F8</kbd>- Compile and run in external terminal

## Running Code Using Code Runner Extension

VS Code can be configured with extensions to support C/C++, but the configuration process is relatively complex. A simple solution for compiling and running C++ programs is to install the Code Runner extension.

Code Runner is an extension that can run code with one click. It is generally used in projects to verify code snippets, supporting more than 40 languages such as Node.js, Python, C, C++, Java, PHP, Perl, Ruby, Go, etc.

The installation method is to search for Code Runner in the extension store and click Install; or go to [Marketplace](https://marketplace.visualstudio.com/items?itemName=formulahendry.code-runner) and click Install. The browser will automatically open VS Code and perform the installation.

![](./images/vscode-1.jpg)

After installation, open the file you need to run, click the small triangle icon in the upper right corner to run the code; you can also press <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>N</kbd> (on macOS it's <kbd>Control</kbd>+<kbd>Option</kbd>+<kbd>N</kbd>) to get the same result.

???+ warning "Warning"
    If after installing VS Code and Code Runner, the code still cannot run, it is very likely because the system has not installed the C/C++ runtime environment. Refer to the [Hello, World! page](../../lang/helloworld.md) to install.
    
    Remember to check the "Run In Terminal" option in settings, as shown in the figure:![](./images/vscode-7.png)

## Using C/C++ Extension to Compile and Debug/IntelliSense Code

### Installing Extensions

Open the extension store in VS Code, enter `C++` or `@category:"programming languages"` in the search bar, find C/C++, and click Install to install the extension.

![](./images/vscode-2.png)

???+ warning "Warning"
    Before configuration, make sure the system has installed G++ or Clang and has added it to the environment variable `PATH`. Please use CMD or PowerShell, not Git Bash as the integrated terminal.

### Configuring GDB/LLDB Debugger

#### GDB

Create a new C++ code file in VS Code, write some content according to C++ syntax (such as `int main(){}`), save it and press <kbd>F5</kbd> to enter debug mode.
If a "Select Debugger" prompt appears, select `C++ (GDB/LLDB)`. In "Select Configuration", G++ users choose `g++.exe - Build and debug active file`; Clang users choose `clang++ - Build and debug active file`.

???+ warning "Warning"
    The configuration name is not fixed but can be customized. Different operating systems may have different configuration names.

After completion, VS Code will automatically complete the initialization operation and start debugging in the integrated terminal below. So far, all configuration steps for GDB are complete.

#### LLDB

If you need to use LLDB, you need to install another extension[^ref1]——[CodeLLDB](https://github.com/vadimcn/vscode-lldb/). After downloading the .vsix file from the Release page of that project[^ref2], install it from the VS Code extension page.

![](images/vscode-9.png)

First follow the GDB configuration process above, then delete `.vscode/launch.json`, press <kbd>F5</kbd>, select `LLDB`, and then change `${workspaceFolder}/<executable file>` in `launch.json` to `${fileDirname}/${fileBasenameNoExtension}`.

Now LLDB configuration is complete. Press <kbd>F5</kbd> again to see the debugging information at the bottom of the software.

If you want to use VS Code to compile and debug code in the future, all source code needs to be saved in this folder. If you want to compile and debug code stored in other folders, you need to re-execute the above steps (or copy the `.vscode` subfolder from the old folder to the new folder).

### Starting to Debug Code

Open a code file with VS Code, hover over the blank area on the left side of the line numbers, and click the red dot that appears to set a breakpoint for that line of code. Click again to cancel setting a breakpoint.

![](images/vscode-5.apng)

Press <kbd>F5</kbd> to enter debug mode. A debug toolbar will appear at the top of the editor. The four blue buttons from left to right represent `continue`, `next`, `step` and `until` in GDB:

![](images/vscode-6.png)

If the editor doesn't automatically jump, click the "Debug" icon in the left toolbar to enter the debug window, where you can see the values of variables on the left.

In "Watch", you can input expressions, which will be re-evaluated and displayed each time you perform operations like `next` or `step`.

In "Call Stack", you can see the stack frames of the current function execution.

???+ note "Tip"
    You can refer to the [GDB official documentation](https://sourceware.org/gdb/current/onlinedocs/gdb.html/Arrays.html) to view the content of a certain range of an array.

In debug mode, the editor will display the next code to be executed with a yellow background.

### Configuring IntelliSense

Used to adjust VS Code's IntelliSense.

If you use the Clang compiler, select `clang-x64` instead of the default `msvc-x64` in "IntelliSense Mode"; if you use the G++ compiler, select `gcc-x64` to use auto-completion and other functions. Otherwise, you will get the error "IntelliSense Mode msvc-x64 is not compatible with the compiler path."

![](images/vscode-4.png)

## Configuring clangd

???+ warning "Warning"
    Due to functionality conflicts, after installing the clangd extension, the C/C++ extension's IntelliSense function will be disabled (debugging and other functions still use the C/C++ extension). If the clangd extension's functionality has problems, check whether the C/C++ extension's IntelliSense function is disabled.

### Introduction to clangd

LLVM's official website introduces clangd as follows:

> Clangd is an implementation of the Language Server Protocol leveraging Clang. Clangd's goal is to provide language "smartness" features like code completion, find references, etc. for clients such as C/C++ Editors.

In simple terms, clangd is Clang's implementation of the Language Server Protocol (LSP), providing some intelligent features such as whole-project indexing, code jumping, variable renaming, faster code completion, prompt information, code formatting, etc. It can also collaborate with editors like Vim, Emacs, VSCode through LSP. Although the official definition is an implementation of LSP, clangd's functionality is closer to a Language Server rather than just the protocol itself.

VS Code's C/C++ extension also has auto-completion and other functions, but it is slightly inferior to clangd in terms of readability and accuracy of prompt information. Therefore, we sometimes use clangd instead of the C/C++ extension to implement code auto-completion and other functions.

### Installation

See [Getting started](https://clangd.llvm.org/installation).

### VS Code Extension

Open the VS Code extension store, enter `clangd` in the search bar to find the clangd extension and install it.

![](images/vscode-8.png)

If a dialog pops up at the bottom asking clangd to close IntelliSense, click "Disable IntelliSense" and reload the workspace. You can then enjoy clangd's auto-completion and other features.

## Editing

### Syntax Settings

In the newly opened editor, click "Select Language" to open the corresponding syntax highlighting, as shown in the figure:

![](images/vscode-11.apng)

### Shortcuts

The official shortcuts PDF is as follows. You can also press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd> in VS Code to open the command palette and input the command `> Help: Keyboard Shortcuts Reference` to open it.[^ref3]

-   [Windows Shortcuts](https://code.visualstudio.com/shortcuts/keyboard-shortcuts-windows.pdf)
-   [Linux Shortcuts](https://code.visualstudio.com/shortcuts/keyboard-shortcuts-linux.pdf)
-   [Mac OS Shortcuts](https://code.visualstudio.com/shortcuts/keyboard-shortcuts-macos.pdf)

Some shortcuts:

| Key                                                          | Operation                        |
| ------------------------------------------------------------ | ------------------------- |
| <kbd>Ctrl</kbd>+<kbd>C</kbd>/<kbd>X</kbd>                     | Copy/Cut current line (when no content is selected)        |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>K</kbd>                 | Delete current line                     |
| <kbd>Alt</kbd>+<kbd>Up</kbd>/<kbd>Down</kbd>                  | Move line up/down                    |
| <kbd>Alt</kbd>+<kbd>Shift</kbd>+<kbd>Up</kbd>/<kbd>Down</kbd> | Copy line up/down                  |
| <kbd>Ctrl</kbd>+<kbd>/</kbd>                                  | Toggle line comment                     |
| <kbd>Ctrl</kbd>+<kbd>\[</kbd>/<kbd>]</kbd>                    | Indent/Unindent line                   |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>\[</kbd>/<kbd>]</kbd>   | Fold/Unfold line                    |
| <kbd>Ctrl</kbd>+<kbd>P</kbd>                                  | Open recently opened file                 |
| <kbd>Alt</kbd>+<kbd>Z</kbd>                                   | Toggle word wrap                    |
| <kbd>Alt</kbd>+<kbd>F12</kbd>                                 | Peek definition (like function definition)              |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>\\</kbd>                | Jump to matching bracket                   |
| <kbd>Ctrl</kbd>+<kbd>T</kbd>                                  | Find symbol in workspace (find function with specified name in folder) |

### Multiple Cursors

Hold <kbd>Alt</kbd> and click to add a cursor in the editor. Most editing operations can be done simultaneously; hold the middle mouse button and drag in the editor to also add multi-line cursors, as shown in the figure:

![](images/vscode-12.gif)

Press <kbd>Ctrl</kbd>+<kbd>F2</kbd> to simultaneously change all matching items in the editor. You can also find "Change All Occurrences" in the right-click menu, as shown in the figure:

![](images/vscode-13.gif)

Note that at this time there will be a toolbar in the upper right corner, where you can enable whether to match case, whole words, etc. when searching for matching items.

## References and Notes

[^ref1]: If VS Code's C/C++ extension chooses lldb as the debugger, it will use the lldb-mi program by default, but it has been separated from the LLVM development team by themselves and needs to be compiled. It has some bugs, and the usage experience and convenience are not as good as the CodeLLDB extension.

[^ref2]: After installing CodeLLDB from the extension store, it will download the main body from GitHub. The download speed is extremely slow, and sometimes the download fails. Therefore, it is best to directly download the main body and install it. Updates can also be directly downloaded and installed according to the above steps.

[^ref3]: [VS Code Official Documentation](https://code.visualstudio.com/docs/)