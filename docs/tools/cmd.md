author: StudyingFather, ayalhw, qinyihao, CoderOJ, mcendu, Libaray

Although graphical interfaces can do more and more things, there are still many advanced operations that require the command line to solve.

This page will briefly introduce some usage methods of the command line.

## Basics

Windows has two built-in command line interfaces. "Command Prompt" (`cmd`) is the older one with relatively simple functions. PowerShell is a newer command line interface with rich built-in features but is relatively bloated. Both interfaces can be found in the Start menu.

Unix-like systems (including macOS and Linux, referred to as Unix below) are divided into two cases: with and without a graphical interface. If the system has a graphical interface (such as using macOS or having GNOME, KDE, etc. installed on Linux), the command line can generally be opened through a program called "Terminal" or "Console". For systems without a graphical interface, the command line is automatically entered after startup.

The command line on Windows looks like this:

```doscon
C:\Users\chtholly>
```

The instructions entered on the command line are displayed after `>`.

```doscon
C:\Users\chtholly>echo "Hello World!"
```

The command line on Unix looks like this (using Debian/Ubuntu as an example, other systems' command lines are similar):

```console
chtholly@seniorious:~$
```

The instructions entered on the command line are displayed after `$`.

```console
chtholly@seniorious:~$ echo "Hello World!"
```

If you log in to the command line as `root` on Unix, then `$` will be replaced by `#`:

```console
root@seniorious:~# apt-get install gcc
```

Before the `>`, `$`, or `#` on the command line, a path is displayed. This path is the working directory, or current directory. On Unix, the current directory is sometimes displayed in a form like `~/folder`, where the leading `~` is the home directory of the currently logged-in user. The home directory of user `chtholly` is different on different systems: on Linux, it is located at `/home/chtholly`, while on macOS, it is located at `/Users/chtholly`.

## Syntax and Common Commands[^1]

### File System Related

First, let's introduce two ways to describe positions in the file system: relative paths and absolute paths.

-   Relative path: Uses a position relationship relative to the current path. For example, if the current path is `~/folder`, then `./a.cpp` actually refers to the file `~/folder/a.cpp`. **As the current path changes, the position described by a relative path may also change**.

-   Absolute path: Uses a complete path to describe a position. For example, `~/folder/a.cpp` is an example of an absolute path. **The position described by an absolute path does not change with the current path**.

    Windows/Unix uses `.` to represent the current directory, and `..` to represent the parent directory of the current directory. Specifically, on Unix, `~` represents the user's home directory (note that `~` is expanded by the shell, so it may not work in other places).

On Unix, you can use the `pwd` command to print the current directory (this command also exists in Windows PowerShell, but not in Windows Command Prompt; see the note below for details). In Windows/Unix, the `cd <directory>` command can change the current directory. For example, `cd folder` will change to the `folder` subdirectory of the current directory; `cd ..` will change to the parent directory of the current directory.

???+ note "Special Note for Windows Command Prompt"
    There is no `pwd` command in Windows Command Prompt, but you can use the `cd` command without any parameters as an approximation.

    Also, note that when using the `cd` command to change directories in Windows Command Prompt, if **the drive letter of the directory to change to is different from the current directory's drive letter**, the current directory will not change. You can type the drive letter of the path you want to change to again, or you can use the `cd /d <directory>` command to change the drive letter at the same time. The command line interfaces for the two methods are as follows:
    
    ```doscon
    C:\Users\Libaray>cd D:\Codes
    C:\Users\Libaray>D:
    D:\Codes>
    ```
    
    ```doscon
    C:\Users\Libaray>cd /d D:\Codes
    D:\Codes>
    ```

On Windows, you can use the `dir` command to list the files in the current directory. On Unix, the command to list files is `ls`. Specifically, on PowerShell, you can use the same `ls` command as Unix.

On Windows, you can use `md <directory>` or `mkdir <directory>` to create a new directory, and use `rd <directory>` or `rmdir <directory>` to delete a directory. On Unix, these two commands are `mkdir` and `rmdir` respectively. Note that **before using `rd` or `rmdir` to delete a directory, the directory must be empty**. If you want to delete a non-empty directory (and all files under that directory), you can execute `rm -r <directory>` on Unix, and `rd /s <directory>` on Windows.

### Redirection Mechanism

> I compiled a program that reads from standard input and outputs to standard output. However, both the input file and output file are very large. Is there a way to redirect the input to a specified input file and redirect the output to a specified output file?

You can achieve this with the following command:

```console
$ command < input > output
```

For example, the command `./prog < 1.in > 1.out` will make `prog` read data from `1.in` in the current directory and overwrite the program output to `1.out`.

???+ warning "Warning"
    The original content of `1.out` will be overwritten. If you want to append to the original output file, use `>>`, i.e., use `./prog >> 1.out` for output redirection.

Note that PowerShell only supports output redirection, not input redirection.

In fact, most OJs use such a redirection mechanism. The program submitted by the contestants uses standard input/output. Through the redirection mechanism, the contestant's program can read from the given input file, output to the specified output file, and then file comparison can be used for evaluation.

### Executing Programs

For an executable program or batch script, you can simply enter its filename on the command line to execute it.

Of course, when executing a file, the command line does not search all files in every directory. The environment variable `PATH` describes the scope of the command line's search path, and the command line will look for the target file in the paths in `PATH`.

For Windows systems, **the current directory is also in the command line's default search scope**. For example, in Windows, entering the `hello` command can execute `hello.exe` in the current directory. However, in PowerShell, PowerShell by default does not look for executable files in the current directory (this is consistent with Unix behavior). Therefore, in PowerShell, you need to use a relative or absolute path to call executables in the current directory, for example `.\hello.exe`. Otherwise, you will see the following error:

```ps1con
PS> hello
hello: The term 'hello' is not recognized as a name of a cmdlet,
function, script file, or executable program.
Check the spelling of the name, or if a path was included, verify that
the path is correct and try again.

Suggestion [3,General]: The command hello was not found, but does exist
in the current location. PowerShell does not load commands from the
current location by default. If you trust this command, instead type:
".\hello". See "get-help about_Command_Precedence" for more details.
```

In Unix systems, **the current directory is not in the command line's default search scope**, so the command to execute the `hello` program in the current directory becomes `./hello`:

```console
$ hello
hello: command not found
$ ./hello
Hello World!
```

### Summary

The usage introduced above is only a small part of command line commands. There are many commands not covered. Enter the help command `help` on the command line to query all basic commands and their purposes.

Below is a comparison table of Windows and Unix commands for reference.

| Category   | Windows System | Unix System |
| ---- | ---------- | ------- |
| List files | `dir`      | `ls`    |
| Change directory | `cd`       | `cd`    |
| Create directory | `md`       | `mkdir` |
| Remove directory | `rd`       | `rmdir` |
| Compare files | `fc`       | `diff`  |
| Copy files | `copy`     | `cp`    |
| Move files | `move`     | `mv`    |
| Rename files | `ren`      | `mv`    |
| Delete files | `del`      | `rm`    |

## Compiling/Debugging from Command Line

See: [Command Line Compilation and Debugging](compile-debug.md).

## Command Line Tips

### Auto-completion

Completion is one of the basic features provided by Shell, mainly used to reduce the amount of input and probability of typos during command line usage.

Generally, the shortcut key for completion is <kbd>Tab</kbd>. After pressing it, Shell will complete the information based on the characters already entered.

Different Shells provide completion capabilities of varying quality.

Below is the completion capability of common Shells[^autocomplete]:

| Shell               | Completion Capability (Scope)                                            |
| ------------------- | -------------------------------------------------------- |
| cmd (Windows traditional console) | File paths                                             |
| PowerShell          | File paths, command names in PATH, built-in command names, function names, command parameters, supports fuzzy matching, auto-correction |
| Bash                | File paths, command names in PATH, built-in command names, function names, command parameters |
| Zsh                 | File paths, command names in PATH, built-in command names, function names, command parameters, supports fuzzy matching, auto-correction and suggestions |
| Fish                | File paths, command names in PATH, built-in command names, function names, command parameters, supports fuzzy matching, can display parameter functions during completion, auto-correction and suggestions |

???+ note "Note"
    Some PowerShell features require the PSReadline Module to be loaded or be in PowerShell ISE.  
    Bash's completion functionality generally requires a package named `bash-completions` to get full functionality. Completion files for some software are provided by the software package itself.  
    Zsh's complete completion functionality needs to work with user-defined files (generally installed with the Zsh package or corresponding software package).  
    Fish provides good and complete completion functionality in default configuration, but completion files for some software not covered by officials are provided by the software itself.

### Help Documentation

Generally, programs on the command line come with "help". On Windows, you can usually get it via `command /?` or `command -?`. On Unix-like (e.g., Linux), you can usually get it via `command --help` or `command -h` (but "help" under BSD is often too brief to be useful).

Additionally, on Unix-like systems, there is also a "manual" that can be obtained via `man command`, which is generally more detailed than "help".

### built-in time and GNU time

When testing program runtime, we can usually use the `time` command.

But this command actually corresponds to two commands in the system: one is a built-in command in some Shells (such as Bash), and the other is GNU time (a separate software). There are some differences between them.

Generally, using `time` directly in Bash calls the Bash built-in version. We can use the `TIMEFORMAT` environment variable to control its output format. For example, setting it to `%3lR` will output the actual running time with three-digit precision, and `%3lU` will output the user-space running time with three-digit precision.[^bash-time-format]

If you want to call the GNU version of time, you need to use `\time` or `/usr/bin/time`. However, its output format is not easy to read. We can add the `-p` parameter (i.e., `\time -p`) to get readable output.

## Pipes

Suppose we now have two programs A and B, both using standard input/output. How to redirect A's output to B's input?

We can use the redirection method mentioned above, first redirect A's output to a temporary file, then redirect B's input to this temporary file.

But this method is very inefficient. It not only requires creating new files, but disk IO operations may also become a bottleneck, and the two programs cannot run at the same time; B can only start after A finishes. Is there a better way?

Yes, that's **pipes**, which are also very simple to use, as follows:

```console
$ A | B
```

This creates a pipe in memory, and then both programs are started simultaneously. Each time program A's output is redirected to this pipe, and this pipe itself does not store data (there is actually a very small buffer). Before B reads the data, A's output operation will be blocked. After B reads the data, A's output can continue. This elegantly solves the above problem: no disk IO operations, both programs run simultaneously, and no extra memory consumption to store intermediate results.

### Named Pipes

Sometimes we don't just want to redirect one program's output to another's input. For example, when doing IO interaction problems, we often need to redirect A's output to B's input and B's output to A's input. In this case, the ordinary pipe mentioned above is helpless. And redirecting to files makes it impossible for the two programs to run at the same time. At this point, we need a pipe that looks like a file—named pipe.

On Unix systems, you can use the following command to create a named pipe (using `my_pipe` as the name):

```console
$ mkfifo my_pipe
```

At this time, using the `ls` command to list files in the current directory, you will find an additional file named `my_pipe|`. This creates a named pipe. The `|` after the filename indicates that this is a pipe file. Then you can read from and write to this pipe just like file redirection.

Through named pipes, we can make two programs interact in this way:

```console
$ mkfifo input output
$ ./checker > input < output # Here you must write > input first, otherwise the shell will open the output pipe first, and since this pipe has nothing in it now, it will block checker's execution.
$ ./my_code < input > output
```

After use, you can delete the named pipe with the `rm` command just like a regular file.

## References and Notes

[^1]: Liu Rujia "Introduction to Algorithms (2nd Edition)" Appendix A Development Environment and Methods

[^autocomplete]: [Comparison\_of\_command\_shells#Interactive\_features](https://en.wikipedia.org/wiki/Comparison_of_command_shells#Interactive_features)

[^bash-time-format]: <https://unix.stackexchange.com/a/70655>