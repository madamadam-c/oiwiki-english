## Introduction

CLion is a feature-rich and powerful cross-platform C/C++ integrated development environment (IDE) developed by JetBrains.

![Clion](./images/clion.png)

## Official Tutorial

The official website provides a tutorial for [Learning CLion](https://www.jetbrains.com/clion/learn/).

## Installation

See [Download CLion](https://www.jetbrains.com/clion/download/).

## Configuration

### Toolchain Installation

CLion does not come with a compiler, build tools, or debugging tools by default. They need to be installed manually.

#### Windows

See [Tutorial: Configure CLion on Windows | CLion Documentation](https://www.jetbrains.com/help/clion/quick-tutorial-on-configuring-clion-on-windows.html).

It is worth noting that the Windows version of CLion comes with MinGW, so you don't need to install a MinGW toolchain separately.

#### Linux

##### Debian/Ubuntu and derivative distributions

```bash
sudo apt install make cmake # build tools
sudo apt install gcc g++ gdb # compiler and debugger
sudo apt install clang clang++ llvm lldb # you can also choose to use clang toolchain
```

##### Arch Linux and derivative distributions

```bash
sudo pacman -S make cmake # build tools
sudo pacman -S gcc g++ gdb # compiler and debugger
sudo pacman -S clang clang++ llvm lldb # you can also choose to use clang toolchain
```

##### Fedora/RHEL/CentOS/Rocky Linux

```bash
sudo dnf install make cmake # build tools
sudo dnf install gcc g++ gdb # compiler and debugger
sudo dnf install clang clang++ llvm lldb # you can also choose to use clang toolchain
```

#### macOS

See [Tutorial: Configure CLion on macOS | CLion Documentation](https://www.jetbrains.com/help/clion/quick-tutorial-on-configuring-clion-on-macos.html).

### Toolchain Settings

#### Manually Setting Toolchains

A newly installed CLion will automatically detect C/C++ development toolchains in the system. If installed toolchains cannot be automatically detected, you can manually configure them in `Settings` -> `Build, Execution, Deployment` > `Toolchains`.

![Config Toolchains](./images/clion-toolchain.png)

### Compiling, Running, and Debugging

Although CLion was originally created for multi-file complex C/C++ projects, and earlier CLion used [CMake](https://cmake.org/) as the build tool by default, since CLion version 2022.3, CLion has supported [C, C++ single file running](https://www.jetbrains.com/help/clion/run-single-file.html).

There are multiple ways to run a C++ program. A simple process is as follows:

1.  Create a C/C++ project: `New -> Project -> C++ Executable`, select a suitable address and language standard version, click `Create`.
2.  Open the project. The project directory should contain a `cmake-build-debug` directory, a `CMakeLists.txt` file, and a `main.cpp` file. Since we don't need to use CMake to manage the project, we can delete the `CMakeLists.txt` file and the `cmake-build-debug` directory and all its contents.
3.  Open the `main.cpp` file, and right-click in the editing area. You can see the `Run 'main.cpp'` option. After selecting this option, CLion can automatically create a run configuration and run the program.

![C++ Single File Execution](./images/clion-single-file-execution.png)

If you need to debug the program, set breakpoints in the editing area, right-click in the editing area, and select `Debug 'main.cpp'` option.

### Compiling, Running, and Debugging via CMake

#### Settings

CLion can also use [CMake](https://cmake.org/) as the build tool. CMake settings can be modified in `Build, Execution, Deployment -> Toolchains -> CMake`.

![CMake Settings](./images/clion-cmake.png)

#### Compile Options

CMake uses `CMakeList.txt` in the project root directory as the configuration file for building projects. You can use the `add_compile_options` command to add compile options, for example:

```cmake
add_compile_options(-std=c++17 -DDEBUG)
```

For other CMake features, please refer to [CMake Official Documentation](https://cmake.org/documentation/).

## Getting CLion IDE License for Free

CLion is a paid product, but you can apply for a special license through an educational email or open source project. After application, you can not only use the genuine CLion IDE for free, but also get free access to other paid products developed by JetBrains.

???+ note "Note"
    [Starting from May 2025, CLion is free for non-commercial use.](https://blog.jetbrains.com/clion/2025/05/clion-is-now-free-for-non-commercial-use)
    
    According to the definition in the Toolbox non-commercial subscription agreement, commercial products are those distributed or provided for compensation or used as part of your commercial activities. However, certain categories are explicitly excluded from this definition. Common non-commercial use cases include learning and self-education, any form of content creation, open source code, and hobby development.

### Using Educational Email

Go to the official website's [Free Educational Licenses page](https://www.jetbrains.com/community/education/#students), click the `Apply` button, fill in the relevant information to apply.

![Educational Licenses](./images/clion-edu.png)

Note: When registering, in the email option, please fill in an educational email with @edu.cn suffix. The special license can only be obtained after email verification.

You can go to your university's academic affairs center官网 to apply for an educational email. If you cannot apply and need to verify, you can use [Xuexin.cn](https://www.chsi.com.cn) for verification (only for Mainland China).

### Using Open Source Project

If you are a core developer or maintainer of an open source project, you can try to apply for an Open Source Development License. The application process is similar to the educational license, but you need to fill in the repository address of the open source project.

![Open Source Development License](./images/clion-oss.png)