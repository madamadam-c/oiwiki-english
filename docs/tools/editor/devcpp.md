author: topdevst, ksyx, ouuan, Doveqise, hsfzLZH1, wangqingshiyu, sshwy, NanoApe, DawnMagnet, CamberLoid, royqh1979

## Introduction

Dev-C++ is a free integrated development environment (IDE) for developing C/C++ programs, distributed under GPL license, using MinGW and GDB as the compilation system and debugging system. Dev-C++ runs on Microsoft Windows.

The advantage of Dev-C++ is its simple and friendly interface, easy installation, and support for single-file compilation. Therefore, it has become the first choice for many beginner OI contestants and C++ language learners. In NOIP, provinces that provide Windows as the competition system generally have Dev-C++ pre-installed.

Dev-C++ originated from Bloodshed Dev-C++ written by Colin Laplace. This version stopped being updated on February 22, 2005. In 2006, Dev-C++'s main developer Colin Laplace explained the reason: "Busy with real-life affairs, no time to continue developing Dev-C++."

Orwell Dev-C++ is a derivative version of Dev-C++, developed and maintained by independent programmer Orwell (Johan Mes). It fixed errors in the original Dev-C++ and updated the compiler version. Generally speaking, Dev-C++ 5.x are all Orwell Dev-C++. Its last update was in 2015, version 5.11.

Embarcadero Dev-C++[^ref1] is the successor to Bloodshed Dev-C++ and Orwell Dev-C++. In 2020, Embarcadero sponsored and took over the original Dev-C++ project and continued development. Embarcadero Dev-C++ added support for high DPI, updated the compiler to include support for newer C++ standards, and added dark mode.

All the above Dev-C++ distributions are considered "official". Additionally, after Orwell Dev-C++ stopped being updated in 2015, a personal developer from China named [royqh1979](https://github.com/royqh1979) decided to continue developing his personal branch of Dev-C++ for teaching needs, naming it Little Panda Dev-C++[^ref2], integrating intelligent hints and higher version MinGW64, which is very convenient for domestic personal use and learning.

After Little Panda Dev-C++ version 6.7.5 was released, the author developed a brand new Little Panda C++[^ref3] using qt5, which can run natively on Windows, Linux, and macOS. Little Panda C++'s interface is similar to Dev-C++. In addition to providing similar but more complete single-file compilation, debugging, syntax highlighting, search/replace and other functions as Dev-C++, it also provides modern IDE common basic features such as **dark theme**, **code intelligent hints**, **variable/function renaming**, **switch/auto-recognize file encoding**. Furthermore, Little Panda C++ also has a test set function similar to CP Editor, which can **write or download test cases from common OJ competition websites**, **automatically run and test programs**.

## Tutorial

### Common Shortcuts

#### File Section

-   `Ctrl + N`: Create source code
-   `Ctrl + O`: Open file
-   `Ctrl + W`: Close file
-   `Ctrl + Shift + W`: Close all files
-   `Ctrl + P`: Print file

#### Formatting Section

-   `Ctrl + /`: Comment and uncomment
-   `Tab`: Indent
-   `Shift + Tab`: Un-indent

#### Line Operations

-   `Ctrl + E`: Copy line
-   `Ctrl + D`: Delete line
-   `Ctrl + Shift + Up`: Move up
-   `Ctrl + Shift + Down`: Move down

#### Navigation Section

-   `Ctrl + F`: Search
-   `Ctrl + R`: Replace
-   `F3`: Search next
-   `Shift + F3`: Search previous
-   `Ctrl + G`: Go to specified line
-   `Shift + Ctrl + G`: Go to specified function
-   `Ctrl + [1 ~ 9]`: Set bookmark
-   `Alt + [1 ~ 9]`: Jump to bookmark

#### Display Section

-   `Ctrl + Wheel`: Zoom in or out
-   `Ctrl + F11`: Fullscreen or restore

#### Run Section

-   `F9`: Compile only
-   `F10`: Run only
-   `F11`: Compile and run
-   `F12`: Rebuild all

#### Debug Section

-   `F2`: Go to breakpoint
-   `F4`: Set or remove breakpoint
-   `F5`: Debug run
-   `F6`: Stop
-   `F7`: Step debug

### Debugging Process

1.  Set compiler configuration to `TDM-GCC 4.9.2 64-bit Debug`
2.  Press `F4` to set or remove debug breakpoints
3.  Place cursor on variable, press `Alt + A` to add watch variable to debug window
4.  Press `F5` to start debugging
5.  Press `F7` or `Alt + N` to step debug
6.  Press `Alt + S` to jump to next debug breakpoint
7.  Press `F6` to stop debugging

## Extensions

### Adding Compile Options

Click Tools -> Compile Options, then select the "Code Generation/Optimization" tab. Below are some commonly used compile options I use.

#### Enabling Optimization

Optimize code runtime or space usage.

Select the "Optimization Level (-Ox)" option tag in the "Code Generation" sub-tab.

![](./images/Dev-C++-11.png)

#### Changing Language Standard

Use new language features or try to compile code under old standards.

Select the "Language Standard (-std)" option tag in the "Code Generation" sub-tab.

![](./images/Dev-C++-12.png)

#### Showing Maximum Warning Information

Helper for finding errors.

Select the "Show Maximum Warning Information (-Wall)" option tag in the "Code Warnings" sub-tab.

![](./images/Dev-C++-13.png)

#### Generating Debugging Information

When displaying "The project has no debugging information. Do you want to open project debugging options and regenerate?" and it flashes after clicking, or when you want to use debugging functions, you need to enable this function.

Select the "Generate Debugging Information" option tag in the "Linker" sub-tab.

![](./images/Dev-C++-14.png)

### Compile Tricks

Click Tools -> Compile Options, then select the "Compiler" tab. Below are some commonly used tricks.

#### Increasing Stack Size

Prevent situations like DFS overflowing system stack.

Add `-Wl,--stack=128000000` command in "Add the following commands to the linker command line".

This command sets the stack to about 128MB. You can increase it as needed.

![](./images/Dev-C++-15.png)

#### Defining Macros

Convenient for using file input/output for local testing or other purposes.

Add `-D[String]` command in "Add the following commands to the linker command line".

Change `[String]` to the macro name you need.

As shown in the figure, after enabling the compile option, the following code can read data from `test.in` file and output to `test.out` file.

![](./images/Dev-C++-16.png)

```cpp
#ifdef LOCAL
freopen("test.in", "r", stdin);
freopen("test.out", "w", stdout);
#endif
```

#### Code Formatting

Click Astyle-> Format Current File or press Ctrl+Shift+A for code formatting.

![](./images/Dev-C++-17.png)

### Customization

#### Font

Click Tools -> Editor Options, then select the "Display" tab.

![](./images/Dev-C++-9.png)

#### Theme

Click Tools -> Editor Options, then select the "Syntax" tab. You can use preset themes or adjust them yourself.

![](./images/Dev-C++-10.png)

## References

[^ref1]: Project source code hosted on [GitHub](https://github.com/Embarcadero/Dev-Cpp) and [SourceForge](https://sourceforge.net/projects/embarcadero-devcpp/).

[^ref2]: Source code hosted on [Github](https://github.com/royqh1979/Dev-Cpp)

[^3]: Project official website at [Little Panda C++](https://royqh1979.gitee.io/redpandacpp), source code hosted on [Github](https://github.com/royqh1979/RedPanda-CPP/)