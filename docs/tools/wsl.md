author: GoodCoder666, Ir1d, H-J-Granger, NachtgeistW, StudyingFather, Enter-tainer, abc1763613206, Anti-Li, shenyouran, Chrogeek, SukkaW, Henry-ZHR, Early0v0, andylizf, tootal, Marcythm, CoelacanthusHex, indevn, qinyihao, peasoft

![Header](./images/wsl-header.png)

This chapter introduces how to run a Linux environment on Windows using Windows Subsystem for Linux.

## Introduction[^ref1]

Currently, most schools' competition practice environments are built on Windows operating systems. However, in NOI series competitions, NOI Linux (a modified version of Ubuntu) has been adopted.

The NOI competition (since September 1, 2021) environment requirements are as follows:[^ref2]

| Category          | Software or Module             | Version                 | Remarks                                             |
| :---------- | :------------------------ | :----------------- | :--------------------------------------------- |
| System          | Linux Kernel                  | `5.4.0-42-generic` | 64-bit x86 (AMD64)                               |
| Language Environment        | GCC (`gcc` and `g++`)        | `9.3.0`            | C and C++ Compiler                                    |
|             | FPC                       | `3.0.4`            | Pascal Compiler (Note: Pascal is no longer supported in NOI series competitions since 2022) |
|             | Python 2                  | `2.7`              | Non-competition Language                                          |
|             | Python 3                  | `3.8`              | Non-competition Language                                          |
| Debugging Tools        | GDB                       | `9.1`              |                                                |
|             | DDD                       | `3.3.12`           | GUI Frontend for GDB                                   |
| Integrated Development Environment (IDE) | Code::Blocks              | `20.03`            | C/C++ IDE                                      |
|             | Lazarus                   | `2.0.6`            | Pascal IDE                                     |
|             | Geany                     | `1.36`             | C/C++/Pascal Lightweight IDE                           |
| Text Editing Tools      | Visual Studio Code        | `1.54.3`           |                                                |
|             | GNU Emacs                 | `26.3`             |                                                |
|             | gedit                     | `3.36.2`           |                                                |
|             | Vim                       | `8.1`              |                                                |
|             | Joe                       | `4.6`              |                                                |
|             | nano                      | `4.8`              |                                                |
|             | Sublime Text              | `3.2.2`            |                                                |
| Other Software        | Firefox                   | `79.0`             | Browser                                            |
|             | Midnight Commander (`mc`) | `4.8.24`           | File Manager                                          |
|             | xterm (uxterm)            | `3.5.3`            | Terminal                                             |
|             | Arbiter-local             | `1.02`             | Single-machine Program Evaluation Tool                                      |

There are several differences between the competition environment and regular environments:

-   Operations on the command line differ from those in graphical interfaces.
-   Differences between Linux and Windows, such as case sensitivity.
-   Behavior differences between different compilers (MSVC and GCC) and different versions of compilers (GCC on Windows vs Linux, 32-bit vs 64-bit Linux GCC, GCC 7 vs GCC 8, etc.), such as variable initialization and array bounds checking.
-   Differences between different evaluation systems (Luogu and Arbiter) in timeout checking and memory limit checking.

This can lead to awkward situations:

-   Trying to copy with <kbd>Ctrl</kbd>+<kbd>C</kbd> but exiting the program instead.
-   A program template that always AC on the online judge fails with WA on Linux.

To prevent such awkward situations in the competition, we must familiarize ourselves with Linux system operations in advance.

Although NOI's official website has released the NOI Linux ISO image, configuring a virtual machine is cumbersome. Moreover, since NOI Linux comes with a graphical interface by default, it may not run smoothly on low-end systems.

Windows 10 introduced the Linux Subsystem (WSL) in its first anniversary update, and upgraded to WSL 2 in the May 2020 update. As of June 1, 2020, WSL supports installing mainstream Linux distributions such as Ubuntu, openSUSE Leap, Kali, and Debian. However, WSL does not support Arbiter used for NOI evaluation.

???+ note "[What is Linux Subsystem (WSL)](https://en.wikipedia.org/wiki/Windows_Subsystem_for_Linux)"
    Windows Subsystem for Linux (WSL) is a compatibility layer for running Linux binary executables (in ELF format) natively on Windows 10, Windows 11, and Windows Server 2019.

    WSL allows developers to run a GNU/Linux environment as-is - including most command-line tools, utilities, and applications - without virtual machine overhead.

    WSL is only available on 64-bit Windows 10 version 1607 and above, Windows 11, and Windows Server 2019/2022.

## Enabling WSL[^ref3]

### Automatic Installation

???+ warning "Warning"
    This section applies to Windows 10 version 2004 and higher (build 19041 and higher) or Windows 11.

    If you are using a version below 2004 or your computer does not support virtualization, please read the manual installation section below.

    If you are using Windows 10 version below 1607, your system does not support WSL.

1.  Open Windows PowerShell as Administrator (right-click the "Start" button and select Windows PowerShell (Admin) or Windows Terminal (Admin))

2.  Enter `wsl --install` and wait for all components to be automatically installed. You may need to restart your computer to enable necessary Windows features during this process.

3.  After installation, you can find your installed distribution in the "Start" menu or in a tab of Windows Terminal.

4.  Next, please proceed to the "Configure Distribution" section below to complete other settings.

### Manual Installation[^ref4]

???+ warning "Warning"
    The following describes the steps for manual WSL installation. If you have completed the automatic installation, skip this section.

#### Enabling Windows Subsystem for Linux

Before installing any Linux distribution for WSL, you must choose one of the two methods below to ensure the "Windows Subsystem for Linux" optional feature is enabled:

Using command line:

1.  Open PowerShell as Administrator and run:

    ```powershell
    Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux
    # Skip this step if you only want to use WSL 1
    Enable-WindowsOptionalFeature -Online -FeatureName VirtualMachinePlatform
    ```

2.  When prompted, restart your computer.

Using GUI:

![Windows Features](./images/wsl-windows-features.png)

1.  Open "Control Panel"

2.  Go to "Programs and Features" > "Turn Windows features on or off"

3.  Select "Windows Subsystem for Linux" and "Virtual Machine Platform"

4.  Click OK

5.  Restart

#### Installing Kernel Update Package

If you want to use WSL 1, skip this step.

Download and install the [WSL2 Linux Kernel Update Package for x64 computers](https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_x64.msi).

#### Setting WSL Default Version

In most cases, WSL 2 is recommended.
For the differences between WSL 1 and WSL 2, see [Compare WSL 2 and WSL 1](https://learn.microsoft.com/en-us/windows/wsl/compare-versions).

??? note "About systemd"
    WSL 1 does not fully support systemd (meaning some features requiring systemd cannot be implemented or need alternative solutions). WSL 2 has built-in support for systemd. If you need to use systemd and your current distribution is not configured to enable it, refer to [Advanced settings configuration in WSL](https://learn.microsoft.com/en-us/windows/wsl/wsl-config#systemd-support).

```powershell
# Set WSL default version to WSL 2
wsl --set-default-version 2
```

#### Installing WSL Distribution

![Search Page](./images/wsl-search-page.png)

Open Microsoft Store, search for "Ubuntu", then select "Ubuntu" and click "Install". You can also open the [Ubuntu store page](https://www.microsoft.com/store/pubuntu/9nblggh4msv6).

???+ warning "Warning"
    The Microsoft Store Ubuntu updates with Ubuntu releases, so content may change. If you want a stable Ubuntu LTS version, you can install Ubuntu LTS from Microsoft Store.

## Configure Distribution[^ref5]

This chapter uses Ubuntu automatically installed by Windows as an example.

### Running Ubuntu

Open the "Start" menu to find and launch Ubuntu, or use the `wsl` command from the Windows command line.

You can create an application tile for Ubuntu or pin it to the taskbar for easy access next time.

### Initialization

The first time you run Ubuntu, you need to complete initialization.

```console
    Installing, this may take a few minutes...
```

Wait a minute or two, and the system will prompt you to create a new user account.

```console
    Please create a default UNIX user account. The username does not need to match your Windows username.
    For more information visit: https://aka.ms/wslusers
    Enter new UNIX username: chtholly
```

After entering the username, you will be prompted to enter a password. In Linux, it's normal that no text appears on screen when entering a password.

```console
    Enter new UNIX password:
```

After setting the account name and password, WSL installation is complete.

```console
    Installation successful!
    To run a command as administrator (user "root"), use "sudo <command>".
    See "man sudo_root" for details.

    chtholly@SENIORIOUS:~$
```

## Basic Configuration

The freshly installed system does not include any C/C++ compilers, so you need to configure the environment manually.

```console
$ gcc
The program 'gcc' is currently not installed. You can install it by typing:
sudo apt install gcc
$ g++
The program 'g++' is currently not installed. You can install it by typing:
sudo apt install g++
```

### Changing to Domestic Software Mirrors

Ubuntu's default software mirrors are located abroad. You can switch to domestic mirrors to speed up downloads, such as [Tsinghua TUNA's software mirror](https://mirrors.tuna.tsinghua.edu.cn/help/ubuntu/).

???+ warning "Use mirrors that match your system version"
    Please find the mirror that matches your system version on the page (you can use `sudo lsb_release -a` to check the Ubuntu version).

    Unless you know what you are doing, do not use mirrors that do not match your system version!

Use the following commands to update software and mirrors:

```console
$ sudo su # After executing this line, the terminal prompt will change from $ to #, pay attention to the prompt before executing the commands below
[sudo] xxx's password:
# cp /etc/apt/sources.list /etc/apt/sources.list.bak
# vim /etc/apt/sources.list
...(Press i to enter insert mode, then paste the mirror content from above using right-click, press Esc after editing, then enter :wq and press Enter)
# apt update
# apt upgrade -y
# exit
exit
$
```

### Installing Chinese Environment

```console
# apt install language-pack-zh-hans -y
# apt install fontconfig -y
# apt install fonts-noto-cjk fonts-wqy-microhei fonts-wqy-zenhei -y # Chinese fonts
# dpkg-reconfigure locales
```

At this point, a setup menu will appear. Just press Enter without doing anything.

In the next menu, select `zh_CN.UTF-8` and press Enter.

<!-- scripts.linter.preprocess.fix_details off -->

```text
    Default locale for the system environment:

                 None
                 C.UTF-8
                 en_US.UTF-8
                [zh_CN.UTF-8]

            <Ok>            <Cancel>
```

<!-- scripts.linter.preprocess.fix_details on -->

After closing WSL and restarting, the system will be in Chinese.

Next, enter the following commands to replace the `man` help pages with Chinese versions.[^ref6]

```console
# apt install manpages-zh
# sed -i 's|/usr/share/man|/usr/share/man/zh_CN|g' /etc/manpath.config
```

You can test with `man help`.

### Installing Compilation Environment[^ref7]

```console
# apt install -y build-essential vim ddd gdb fpc emacs gedit anjuta lazarus
```

For GUIDE installation, please refer to [GUIDE installation on Debian or Ubuntu](./editor/guide.md#installing-guide-on-debian-or-ubuntu).

This installs the basic environment plus the NOI official requirements. If needed, you can install other packages using `sudo apt install <program name>`.
For other versions, you can refer to the Debian official [Package Management Manual](https://www.debian.org/doc/manuals/debian-reference/ch02.en.html).

Here is an example program:

```console
$ vim cpuid.cpp
...
$ g++ -Wall cpuid.cpp -o cpuid
$ ./cpuid
AMD Ryzen 5 1400 Quad-Core Processor
```

???+ note "Note"
    In Linux, executable files can be without extensions. See the command above for how to run them.

## Advanced Operations

### Running GUI Programs with WSLg

If you use Windows 10 19044 or higher, or Windows 11, you can use the integrated desktop experience provided by WSL 2. This feature allows you to directly install and launch Linux desktop programs without additional configuration.

See [Run Linux GUI apps on Windows Subsystem for Linux](https://learn.microsoft.com/en-us/windows/wsl/tutorials/gui-apps)

### Installing Graphical Environment and Using Remote Desktop Connection

If your version does not yet support WSLg, you can try the following guide to enable graphical interface functionality.

The following uses Xfce as an example.

If you only want to install Xfce, run:

```console
$ sudo apt install xfce4 tightvncserver -y
```

If you want more software besides Xfce, run:

```console
$ sudo apt install xubuntu-desktop -y
```

Graphical environment files are large, so downloading and extracting takes some time.

Configure xrdp:

```console
$ sudo apt install xrdp -y
$ echo "xfce4-session" >~/.xsession
$ sudo service xrdp restart
```

To prevent conflict with the original remote desktop on the computer, you need to change the default port.

![Result of not changing port](./images/wsl-result-of-not-changing-ports.png)

Run the command `sudo sed -i 's/port=[0-9]\{1,5\}/port=otherport/' /etc/xrdp/xrdp.ini`, where `otherport` is another port (such as `3390`).

    [globals]
    ...
    port=3390

Run `sudo service xrdp restart`, then go to the Start menu and access with `localhost:otherport`.

![](./images/wsl-login-using-non-root.png)

![](./images/wsl-first-login.png)

### Using Xming Connection

Enter the Ubuntu environment and install xterm:

```console
# apt install xterm -y
```

Exit Ubuntu.

Download the latest Xming Server from [Xming X Server download address](https://sourceforge.net/projects/xming/) and install it:

![](./images/wsl-xming-setup-wizard.png)

If you forgot to check "Launch Xming" after installation, open Xming from the Start menu:

![Don't forget!](./images/wsl-xming.png)

Then go back to Ubuntu and enter:

```console
$ DISPLAY=:0 xterm
```

![](./images/wsl-open-xterm.png)

If you used xfce4, you can use the following command in the popup window to activate xfce4:

```console
$ xfce4-session
```

![](./images/wsl-open-xfce4-session.png)

The result is shown in the figure. (You can exit this interface in Xming by using <kbd>Ctrl</kbd>+<kbd>C</kbd>.)

![](./images/wsl-xfce.png)

### WSL and Windows File Inter-access

Windows drives are automatically mounted to the `/mnt` folder in the Linux environment.
For example, the C drive path in WSL is `/mnt/c`

```console
PS C:\Users\chtholly> bash
/mnt/c/Users/chtholly$ echo "Hello world!" > hello
/mnt/c/Users/chtholly$ exit
PS C:\Users\chtholly> cat hello
Hello world!
PS C:\Users\chtholly> echo "Welcome!" > welcome
PS C:\Users\chtholly> bash
/mnt/c/Users/chtholly$ cat welcome
Welcome!
```

Alternatively, you can also access WSL directories from File Explorer. After installing WSL, you can find Linux in the sidebar of File Explorer, where you can access files from all installed distributions.

You can also directly enter `\\wsl$` in File Explorer's address bar or Run (Win+R) to go to WSL's directory.

You can also directly use paths like `\\wsl$\Ubuntu\home\` to access its subfolders.

### Using with Visual Studio Code for Editing

If you are used to using [Visual Studio Code](./editor/vscode.md) for code editing in the Windows environment, you can install the `Remote - WSL` plugin in VS Code to more conveniently edit files in the WSL system.

Through `Remote - WSL`, you can directly operate on the WSL subsystem in the Windows VS Code interface, more conveniently edit files in the subsystem directory, and more conveniently use the terminal for debugging.

By directly typing `code .` in WSL, you can directly open Visual Studio Code in that directory to edit files in that directory.

Similarly, you can use commands like `code filename` to edit specified files.

The `Remote - WSL` plugin's Getting Started page contains a detailed introduction to editing operations.

You can also refer to the Visual Studio Code official documentation about WSL ([Remote development in WSL](https://code.visualstudio.com/docs/remote/wsl-tutorial)), which contains more detailed instructions from WSL installation to using with plugins.

## Upgrading WSL1 to WSL2

???+ warning "Warning"
    Please confirm that you have completed the WSL1 installation steps above.

Running the command `wsl -l -v` shows that the WSL version is 1. You need to upgrade to version 2.

1.  Enable "Virtual Machine Platform"

    Run in PowerShell as Administrator:

    ```shell
    dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
    ```

    Then **restart your computer**.

2.  Download Linux Kernel Update Package

    -   Kernel update package for [x64](https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_x64.msi).
    -   Kernel update package for [ARM64/AArch64](https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_arm64.msi).

3.  Set Distribution Version

    Run the command: `wsl --set-version <distribution name> <version number>`

    For example: The command to set Ubuntu 18.04 to WSL 2 is `wsl --set-version Ubuntu-18.04 2`

    This step takes some time. After completion, check if the upgrade was successful by running `wsl -l -v`.

## FAQ

See: [Common Problems](https://learn.microsoft.com/en-us/windows/wsl/faq), [WSL 2 Common Questions](https://learn.microsoft.com/en-us/windows/wsl/wsl2-faq)

-   How to do xxx under the subsystem?

    You can use the built-in command line, or use a graphical interface.
    For example, vim, typing `man vim` in the command line gives detailed usage instructions.
    You can also use `vim --help`.

    For command line, you can read [Command Line](./cmd.md)

-   Resource usage?

    This system shares the Host with Windows 10, so theoretically it uses less memory than a virtual machine.

## External Links

-   [About Windows Subsystem for Linux](https://learn.microsoft.com/en-us/windows/wsl/about)
-   [Ubuntu Mirror Usage Help, Tsinghua TUNA](https://mirrors.tuna.tsinghua.edu.cn/help/ubuntu/)
-   [Dev on Windows with WSL](https://dowww.spencerwoo.com)
-   [Awesome-WSL on GitHub](https://github.com/sirredbeard/Awesome-WSL)
-   [Troubleshooting Windows Subsystem for Linux](https://learn.microsoft.com/en-us/windows/wsl/troubleshooting)
-   [Upgrading WSL1 to WSL2](https://www.cnblogs.com/stulzq/p/13926936.html)

## References and Notes

[^ref1]: [Luogu Daily #6](https://www.luogu.com.cn/blog/asfr/Run-Ubuntu-On-Windows10)

[^ref2]: [NOI Linux 2.0 Released, Will Officially Begin Use on September 1!](https://noi.cn/gynoi/jsgz/2021-07-16/732450.shtml)

[^ref3]: [Install WSL, Microsoft Docs](https://learn.microsoft.com/en-us/windows/wsl/install)

[^ref4]: [Manual Installation Steps for Old WSL](https://learn.microsoft.com/en-us/windows/wsl/install-manual)

[^ref5]: [WSL-Ubuntu Wiki, Ubuntu Wiki](https://wiki.ubuntu.com/WSL)

[^ref6]: [How to Set Ubuntu's man Command Help to Chinese Version, Frank Viewing Lushan, 2017-06-09](https://blog.csdn.net/qq_14989227/article/details/72954523)

[^ref7]: [Run Bash on Ubuntu on Windows, Mike Harsh, 2016-05-30, Windows Blog](https://blogs.windows.com/buildingapps/2016/03/30/run-bash-on-ubuntu-on-windows/#cie8WdR3uSjgR5Ru.97)