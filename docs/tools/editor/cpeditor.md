author: zarttic, xk2013

## Introduction

[CP Editor](https://github.com/cpeditor/cpeditor) is specifically designed for algorithmic competitions, unlike other IDEs which are mainly designed for development. It can help you automate compiling, running, and testing, allowing you to focus on algorithm design. It can even fetch test cases from various algorithmic competition websites and submit code to [Codeforces](https://codeforces.com/)!

## Download and Installation

See [Installation | CP Editor](https://cpeditor.org/zh/docs/installation/).

## Basic Configuration

> CP Editor does not have a built-in compiler. You need to install and configure a compiler yourself. If you need to, please refer to this site's articles on compiler installation[^compiler]. Of course, if you chose the installer with the `with-gcc-<GCC version>-llvm-<LLVM version>` suffix when downloading, you can use the compiler that comes with CP Editor. The path is `{installation directory}/mingw64/bin/`.

-   Set Default Language

    The default language of the editor is `C++`.

    ![cp-setting-lang-1](images/cp-setting-lang-1.png)

    ![cp-setting-lang-2](images/cp-setting-lang-2.png)

-   Set `C++` Command

    You need to set some necessary compile commands. This depends on your compiler.

    ![cp-setting-lang-3](images/cp-setting-lang-3.png)

-   Set Template

    This is a template that will be automatically initialized when creating a new file. Note that CP Editor needs a `xxx.cpp` file as the template file.

    ![cp-setting-lang-4](images/cp-setting-lang-4.png)

> After completing the above basic operations, you can use the most basic features.

## Basic Features

-   Shortcuts

    |                       Command                      |   Operation   |
    | :-------------------------------------------: | :-----: |
    | <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>C</kbd> |   Compile.   |
    | <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>R</kbd> |  Compile and run. |
    |          <kbd>Ctrl</kbd>+<kbd>R</kbd>         |   Run.   |
    |  <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>D</kbd>  | Run in terminal. |
    |          <kbd>Ctrl</kbd>+<kbd>K</kbd>         | Terminate all processes. |
    | <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>I</kbd> |  Format code. |

    For details, refer to [Official Documentation](https://cpeditor.org/zh/docs/preferences/key-bindings/).

-   Test Cases

    You can copy the test cases from the problem statement. CP Editor will automatically judge them, and you can also set time limits!

    ![cp-setting-limits](images/cp-setting-limits.png)

    ![cp-judge-1](images/cp-judge-1.png)

    ![cp-judge-2](images/cp-judge-2.png)

    ![cp-judge-3](images/cp-judge-3.png)

    ![cp-judge-4](images/cp-judge-4.png)

## References

[^compiler]: [Compiler - OI Wiki](../compiler.md)