## Introduction

Code::Blocks is an open-source integrated development environment (IDE) developed using C++ and using wxWidgets as its GUI library. The project started in 2001 and is currently maintained by the official community. It is primarily used for development of programming languages such as C, C++, and Fortran.[^ref1]

Advantages:

-   **Lightweight and Efficient**: Code::Blocks has low resource usage and fast startup speed, suitable for resource-limited environments and developers who prefer lightweight IDEs. It is also suitable for beginner developers to learn and use.
-   **Cross-platform Compatibility**: Supports multiple operating systems such as Windows, Linux, and macOS, providing a consistent user experience, allowing developers to work seamlessly across different platforms.
-   **Wide Compiler Support**: Supports multiple compilers including GCC, MSVC (Microsoft Visual C++), Digital Mars, and Borland C++ 5.5, allowing developers to choose the most suitable compilation tool based on project needs.

Disadvantages:

-   **Limited Functionality**: Compared to IDEs like CLion or Eclipse, built-in functions and tools are relatively basic, which may not be sufficient for complex project needs.
-   **Weak Plugin Ecosystem**: Although it supports plugin extension functions, the number and quality of third-party plugins are limited, and the plugin ecosystem is relatively weak.

## Installation

See [Code::Blocks Official Website](https://www.codeblocks.org/downloads/), choose to download the binary installer (Binary Release), or download the source code to compile and install (Source Code). Then, according to your needs and operating system, choose the appropriate installer and complete the installation following the installation wizard.

???+ note "Download Installer with MinGW"
    For Windows users who do not want to manually configure the compiler, it is recommended to download the installer that includes MinGW, such as `codeblocks-xxxxmingw-setup.exe`. This version already includes the GCC compiler, so no additional installation and configuration is needed to start developing C and C++ projects.

![CodeBlocks DownLoad](./images/codeblocks-1.png)

## Configuration

If you chose an installer without MinGW during installation, or need to use another compiler, you need to manually install and configure the compiler, then set up Code::Blocks to use that compiler.

### Toolchain Installation

Refer to this site's [Compiler](../compiler.md) installation guide to download and install the compiler you need.

### Toolchain Settings

When you first start Code::Blocks, the software will automatically scan for installed compilers in the system. If no compiler is found, you can manually add one by following these steps:

1.  Open Code::Blocks, click `Settings -> Compiler` in the menu bar to open the compiler settings dialog (as shown in the figure below).![CodeBlocks Compiler Settings](./images/codeblocks-2.png)
2.  In the `Selected compiler` dropdown, select the compiler you need to configure, for example `GNU GCC Compiler`.
3.  In the `Toolchain executables` tab, click the `Auto-detect` button. Code::Blocks will automatically scan for installed compilers in the system.
4.  If automatic scanning fails, you can manually set the compiler path. In `Compiler's installation directory`, enter the compiler's installation path, for example `C:\MinGW\bin`.
5.  After completing the settings, click `OK` to save. Now you can use this compiler to compile and run projects.

## Usage

Code::Blocks has a built-in project manager that supports user-defined project building. You can set compile options in `Project -> Build options`, selecting compiler, compile options, link options, etc. You can also set project properties in `Project -> Properties`, such as project name, path, file list, etc.

??? note "Configuring Makefile"
    Code::Blocks does not require writing a Makefile by default. If you need to use a custom Makefile, you can check the `This is a custom Makefile` option in `Project -> Properties`, then set the Makefile path in `Project -> Build options`.

### Creating Projects

Code::Blocks supports programming languages including C, C++, and Fortran. When starting Code::Blocks, you can create a new project via `File -> New -> Project`. Choose the project type and template, then follow the wizard's instructions to set the project name, path, compiler, etc. Finally, click `Finish` to complete the project creation.

Code::Blocks also supports compiling and running single files. You can create a new file via `File -> New -> File`, write code and save it, then click the `Build and run` button on the toolbar, or press `F9`, to automatically compile and run the current file.

### Building and Running

Take a simple Console Application project as an example. Here's how to build and run the project:

1.  After the project is created, you will see a default `main.cpp` file. You can write code in this file and save it.
2.  After writing the code, click the `Build and run` button on the toolbar, or press `F9`. Code::Blocks will automatically compile and run the project.
3.  After compiling and running, the output window will display the program's output. You can view the output in the output window and adjust the code as needed.
4.  If you only need to compile the project without running, you can click the `Build` button on the toolbar, or press `Ctrl + F9`. Code::Blocks will only compile the project without running the program.

### Debugging

Code::Blocks has a built-in debugger. You can set and start the debugger in the `Debug` menu to help you locate and resolve errors in the program.

Similarly, take a simple Console Application project as an example. Here's how to debug the project:

1.  **Set Breakpoints**: Click the left side of the code line you need to debug to set a breakpoint. The program will stop executing at the breakpoint.
2.  **Start Debugger**: Click the `Debug` button on the toolbar, or press `F8`. Code::Blocks will automatically compile and start the debugger.
3.  **Debug Program**: In the debugger, you can step through the program, view variable values, call stack, etc., helping you locate and resolve errors in the program.
4.  **Stop Debugging**: After debugging is complete, click the `Stop` button on the toolbar, or press `Shift + F8`, to stop the debugger.

## Custom Settings

Code::Blocks provides rich setting options to help adjust the editor's behavior. Here are some commonly used settings:

### Interface Settings

1.  In `Settings -> Editor`, you can set the editor's font, color, indentation, auto-completion, etc.
2.  In `Settings -> Environment`, you can set Code::Blocks' global behavior, such as auto-save, auto-backup, auto-hints, etc.
3.  In the `View` menu, you can adjust the editor's layout, such as opening/closing the file browser, toolbar, status bar, output window, etc.

### Plugin Settings

Code::Blocks supports plugins to extend functionality. You can view and install available plugins via `Settings -> Plugins`, such as DoxyBlocks, wxSmith, etc. Here are some commonly used plugins:

-   **DoxyBlocks**: An integration plugin for the famous documentation generation tool Doxygen. You can directly generate project documentation in Code::Blocks.
-   **wxSmith**: A plugin for developing wxWidgets applications. It provides a visual interface design tool that allows quick creation and layout of GUI interfaces, simplifying the development process.
-   **Thread Search**: A plugin that supports multi-threaded searching. It can quickly search and replace symbols and text in projects, suitable for large project development.

For plugin installation and usage, refer to [Code::Blocks's Plugin Documentation](https://wiki.codeblocks.org/index.php/Code::Blocks_Plugins). Based on the plugin's requirements and functionality, choose the appropriate plugin to install and use.

???+ warning "Note"
    Code::Blocks' plugins are relatively simple and basic, and most plugins are already integrated into the software. The number and quality of third-party plugins are limited. It is recommended to choose appropriate plugins based on actual needs.

### Shortcut Settings

You can view and modify shortcut settings via `Settings -> Editor -> Keyboard shortcuts` tab, adjusting shortcuts according to your habits.

Here are some commonly used shortcuts:

| Function         | Shortcut                 |
| ---------- | ------------------- |
| New file       | `Ctrl + Shift + N`  |
| Open file       | `Ctrl + O`          |
| Save current file     | `Ctrl + S`          |
| Save all       | `Ctrl + Shift + S`  |
| Close current file     | `Ctrl + W`          |
| Close all files     | `Ctrl + Shift + W`  |
| Build and run current project  | `F9`                |
| Build current project    | `Ctrl + F9`         |
| Compile current project    | `Ctrl + Shift + F9` |
| Run current project     | `Ctrl + F10`        |
| Debug: Start/Continue   | `F8`                |
| Debug: Stop      | `Shift + F8`        |
| Debug: Step     | `F7`                |
| Debug: Step Into      | `Shift + F7`        |
| Debug: Step Out      | `Ctrl + F7`         |
| Debug: Toggle breakpoint    | `F5`                |
| Find         | `Ctrl + F`          |
| Find and replace      | `Ctrl + R`          |
| Go to specified line      | `Ctrl + G`          |
| Go to matching bracket    | `Ctrl + B`          |
| Toggle fullscreen       | `F11`               |
| Toggle all folds     | `Ctrl + Shift + -`  |
| Expand all folds     | `Ctrl + Shift + +`  |
| Select next match   | `Ctrl + E`          |
| Select and go to next match | `Ctrl + Shift + E`  |

## References and Notes

[^ref1]: [Code::Blocks - Wikipedia](https://en.wikipedia.org/wiki/Code::Blocks)