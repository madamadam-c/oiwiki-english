This page mainly introduces the installation steps of various compilers/interpreters under each system.

## GCC

### Windows

#### Manual download and installation

Visit the download page of [MinGW-w64](https://www.mingw-w64.org/downloads), there are multiple build versions. For convenience, we use the build version provided by WinLibs.

First go to [WinLibs](https://winlibs.com) to download the latest installer, choose the appropriate version, this article selects GCC 12.3.0 + LLVM/Clang/LLD/LLDB 16.0.4 + MinGW-w64 11.0.0 (UCRT):

By default it comes with LLVM Clang installed, if you don't want to install it, you can also choose the one on the right without LLVM/Clang/LLD/LLDB.

![](./images/compiler1.png)

After downloading, extract it to a location on your computer. In this tutorial, we extracted it to the root directory of C drive. It is best not to include non-English characters and spaces in the directory name, otherwise it may cause some problems later.

![](./images/compiler2.png)

Next we need to add the executable directory of the compiler to the system environment variables, so that we don't need to specify the compiler path during compilation, which is more convenient for use. Above we extracted MinGW to the `C:\mingw64` directory, so the directory where the executable files are located is `C:\mingw64\bin`.

Press the Windows logo + R key combination, input `rundll32.exe sysdm.cpl,EditEnvironmentVariables`, open the system environment variables settings window, and select the variable named "Path" in the "System variables" section, then click the "Edit" button:

![](./images/compiler3.png)

In the edit window, click the "New" button on the right to create a new entry for the "Path" variable, and fill in the directory where the executable files are located recorded above (in the tutorial it is `C:\mingw64\bin`).

![](./images/compiler4.png)

??? note "Hint for some older system versions"
    Some older systems can only manually modify the text value of the variable, so you need to insert a **half-width semicolon** at the end of the variable's value, then paste the directory where the executable files are located after this half-width semicolon, as shown in the figure:
    
    ![](./images/compiler5.png)

Once done, click the "OK" button repeatedly to exit.

Next, open the terminal, input `g++ --version` and press Enter, if the prompt shown in the figure appears, it means the installation was successful.

![](./images/compiler6.png)

#### Scoop installation

Open PowerShell and run the following script:

```powershell
Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
irm get.scoop.sh | iex
scoop install mingw-winlibs
```

### Linux

#### Debian/Ubuntu

First update the package list:

```bash
sudo apt update
```

Then use the command to install directly:

```bash
sudo apt install g++
```

#### Arch Linux

Use the command to install directly:

```bash
sudo pacman -Syu gcc
```

#### openSUSE

Use the command to install directly:

```bash
sudo zypper in gcc-c++
```

### macOS

First update the package manager:

```bash
brew upgrade
brew update
```

Then use the command to install directly:

```bash
brew install gcc
```

## JDK

There are many distributions of JDK, the following introduces two:

-   OpenJDK's [Eclipse Temurin](https://adoptium.net/)[^temurin]: See [Install Eclipse Temurin™ | Adoptium](https://adoptium.net/en/installation/).
-   Oracle JDK: See [JDK Installation Guide (JDK 17)](https://docs.oracle.com/en/java/javase/17/install/overview-jdk-installation.html).

## Python 3

There are also many implementations of Python[^pythonimpl], taking CPython 3 as an example, see [Download Python | Python.org](https://www.python.org/downloads/).

## LLVM

### Windows

??? note "Pitfalls of LLVM on Windows"
    Since LLVM lacks the standard library on Windows, you still need to install MSVC or GCC.

#### Direct installation

Visit the download page of [LLVM](https://github.com/llvm/llvm-project/releases/latest), select LLVM-*-win64.exe to download.

If your network quality is not good, you can also visit [Tsinghua University Open Source Software Mirror](https://mirrors.tuna.tsinghua.edu.cn/github-release/llvm/llvm-project/LatestRelease/) to download.

Open the .exe file, during installation check "Add LLVM to system PATH for current user", then keep clicking "Next" until the installation is complete.

Open the terminal, input `clang++ --version` and press Enter, if you see

```text
clang version 15.0.1
Target: x86_64-pc-windows-msvc
Thread model: posix
InstalledDir: <omitted>
```

similar output, it means success.

#### Scoop installation

Open PowerShell and run the following script:

```powershell
Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
irm get.scoop.sh | iex
scoop install llvm
```

### Linux

#### openSUSE

Use the command to install directly:

```bash
sudo zypper in llvm clang
```

## MSVC (Visual Studio)

Visit the [Download Visual Studio](https://visualstudio.microsoft.com/en-us/downloads/) page, find the "Community" section in the "Download" section, click "Free download". After downloading, open the installer and select "Community 2022 installation". In the subsequent window, only select "Desktop development with C++", then click install.

If you don't want to install the full Visual Studio, scroll down to the "All downloads" section, find "Visual Studio Build Tools" under "Tools for Visual Studio", click the "Download" button behind it. After downloading, open the installer and follow the prompts to select "Desktop development with C++" to install. You can also use the [PortableBuildTools](https://github.com/Data-Oriented-House/PortableBuildTools) tool to install only the MSVC compiler.

[^temurin]: [Eclipse Temurin](https://adoptium.net/) is the former [AdoptOpenJDK](https://adoptopenjdk.net/), the latter was transferred to the [Eclipse Foundation](https://www.eclipse.org/org/foundation/) in July 2021. See [this statement](https://blog.adoptopenjdk.net/2021/03/transition-to-eclipse-an-update/) for details.

[^pythonimpl]: [Alternative Python Implementations | Python.org](https://www.python.org/download/alternatives/)