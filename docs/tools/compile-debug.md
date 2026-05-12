author: CoelacanthusHex, qinyihao, StudyingFather, ksyx, NachtgeistW, CoderOJ, Enter-tainer, mcendu, Tiphereth-A, ayalhw, CCXXXI, Early0v0, HeRaNO, ouuan, swiftqwq, Xeonacid, xiaofu-15191

Before reading this section, please install GCC and gdb first. For specific methods, see the [Compiler](compiler.md) article.

## Using g++ to Compile cpp Files from Command Line

### Manual Compilation

To compile a file `a.cpp` from the command line, simply input `g++ a.cpp` (on Windows, you need to add the compiler's directory to `PATH` in advance).

You can add some compilation options during the compilation process:

-   `-o <filename>`: Specifies the output executable file name.
-   `-g`: Adds debugging information during compilation (required when using gdb for debugging).
-   `-Wall`: Displays all compilation warning messages.
-   `-O1`, `-O2`, `-O3`, `-Ofast`: Optimizes the compiled program. The higher the optimization level, the more optimization techniques are used (enabling optimization will affect debugging with gdb).
-   `-DDEBUG`: Defines the `DEBUG` symbol during compilation (the symbol can be changed arbitrarily, for example `-DONLINE_JUDGE` defines the `ONLINE_JUDGE` symbol).
-   `-UDEBUG`: Undefines the `DEBUG` symbol during compilation.
-   `-lm`, `-lgmp`: Links a library (here it is math and gmp, the specific names used should be checked in the library documentation, but generally they are the same as the library name).

???+ note "Note"
    On Unix, if you use the math library from the standard C library (`math.h`), you need to add the `-lm` parameter during compilation.[^have-to-link-libm-in-gcc]

???+ note "How to Increase Stack Size?"
    On Windows, you can use the compilation option `-Wl,--stack=536870912` to increase the stack size to 512 MB, where the number after the equals sign is the **byte count**.

    On Unix, use `ulimit -s [num]` to set the stack size of the **current terminal** to `[num]` **KiB**.

### Using GNU Make's Built-in Rules[^gnu-make-built-in-rules]

For C/C++ source code files named `qwq.c/cpp`, you can use `make qwq` to automatically compile into a program named `qwq`.

If you need to add extra compilation options, you can use `export CFLAGS="xxx"` (for C programs) or `export CXXFLAGS="xxx"` (for C++ programs). If you need to add extra preprocessor options, you can use `export CPPFLAGS="xxx"`. The above settings can also be written as `CFLAGS="xxx" CPPFLAGS="xxx" make qwq` to specify the environment variables used for a single command execution.

### Sanitizers

#### Introduction

Sanitizers are tools integrated into compilers for debugging C/C++ code. They check for memory access out-of-bounds, undefined behaviors, and other errors at runtime by inserting check code during the compilation process.

It includes the following types:

-   AddressSanitizer[^address-sanitizer]: Detects out-of-bounds access to heap, stack, and global variables, invalid memory freeing, memory leaks (experimental).
-   ThreadSanitizer[^thread-sanitizer]: Detects data races in multithreading.
-   MemorySanitizer[^memory-sanitizer]: Detects reading of uninitialized memory.
-   UndefinedBehaviorSanitizer[^ub-san]: Detects undefined behaviors.

#### Usage

The latest versions of clang++, g++, and MSVC (partially supported) have built-in sanitizers, but their functions and usage methods differ. Here we take clang++ as an example, and its usage is as follows:

```console
$ clang++ -fsanitize=<name> test.cc
```

Where `<name>` is the function to enable (a sanitizer can be understood as a collection of functions), for example:

```console
$ clang++ -fsanitize=memory test.cc # Enable MemorySanitizer
$ clang++ -fsanitize=signed-integer-overflow test.cc # Enable signed integer overflow detection
```

After that, just run the executable as usual. If the sanitizer detects an error, it will output to the `stderr` stream, for example:

```console
$ ./a.out
test.cc:3:5: runtime error: signed integer overflow: 2147483647 + 1 cannot be represented in type 'int'
```

???+ warning "Warning"
    g++ on Windows does not support sanitizers. You need to use [modified MinGW64](https://github.com/ssbssa/gcc/releases) or use other compilers.
    
    MSVC only supports AddressSanitizer from version 16.0 to version 17.14.

#### Time/Memory Overhead

Obviously, these debugging tools will severely slow down the program's runtime and increase memory usage. The following shows the time/memory overhead of using them:

| Name                         | Memory Multiplier | Time Multiplier |
| :------------------------- | :------ | :------ |
| AddressSanitizer           | N/A     | 2       |
| ThreadSanitizer            | 5~15    | 5~10    |
| MemorySanitizer            | N/A     | 3       |
| UndefinedBehaviorSanitizer | N/A     | N/A     |

## Using gdb for Debugging from Command Line

```console
$ g++ a.cpp -o a -g
$ gdb ./a
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04.2) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.
--Type <RET> for more, q to quit, c to continue without paging--
```

Press `c` to continue. Then it prompts `Reading symbols from [filename]...`. When the `(gdb)` prompt appears, you can input commands to debug.

The following are commonly used commands listed by category:

### Basic gdb Commands

| Command                | Description                              |
| ----------------- | ------------------------------------- |
| `help`            | Display help information              |
| `quit`            | Exit gdb                               |
| `file [filename]` | Load the program `[filename]` to debug |

### Run Control Commands

| Command                   | Description                                              |
| -------------------- | ------------------------------------------------------- |
| `run`                | Run the program until a breakpoint or program ends     |
| `continue`           | Continue running until a breakpoint or program ends    |
| `next`               | Step execution, enter function if function call occurs |
| `step`               | Step execution, enter function if function call occurs  |
| `finish`             | Run until current function returns, then stop          |
| `until [num]`        | Run until specified line number `[num]`, then stop     |
| `break [num]`        | Set breakpoint at line `[num]`, program stops there    |
| `condition [id] [p]` | Set condition for breakpoint `[id]`, breakpoint is enabled only when expression `[p]` is satisfied |
| `ignore [id] [num]`  | Ignore first `[num]` triggers of the breakpoint        |
| `delete [id]`        | Delete breakpoint with specified ID                    |
| `disable [id]`       | Disable breakpoint with specified ID                   |
| `enable [id]`        | Enable breakpoint with specified ID                    |
| `list`               | List source code, continue from last position, 10 lines at a time |
| `list [num]`         | List source code with line `[num]` as the middle line |
| `list [func-name]`   | List source code with function as the middle line      |
| `call [function]`    | Call function and print return value                   |

`break [num]` will output the breakpoint number. You can also use `break [func-name]` to set a function breakpoint.

You can also use `break [num] [p]` to achieve a similar effect to `condition [id] [p]` when setting a breakpoint.

### Stack Frame Commands

| Command          | Description                        |
| ----------- | ------------------------------- |
| `info args` | View function arguments         |
| `backtrace` | View all function calls and their arguments |
| `frame`     | Select a stack frame            |
| `up`        | Move up one stack frame         |
| `down`      | Move down one stack frame       |

### Variable Commands

| Command                 | Description                                              |
| ------------------ | ------------------------------------------------------- |
| `print [p]`        | Print the value of expression `[p], through which you can modify variable values |
| `display [p]`      | Print the value of expression `[p]` at each pause, but do not enter functions |
| `watch [var]`      | Watch variable `[var]`; when the variable is written to, it will automatically print and pause |
| `rwatch [var]`     | Watch variable `[var]`; when the variable is read, it will automatically print |
| `awatch [var]`     | When variable `[var]` is modified or written to, it will automatically print and pause |
| `set [assignment]` | Execute assignment statement                            |

Both `display` and `print` commands support controlling output format. The method is to follow the command with `/` and a format character, for example `print/display [var]` (prints variable `[var]` in decimal format). The supported format characters are:

| Format Character | Corresponding Format        |
| ---- | ---------------------- |
| `d`  | Display variable in decimal |
| `x`  | Display variable in hexadecimal |
| `a`  | Display variable in hexadecimal |
| `t`  | Display variable in binary    |
| `c`  | Display variable as character |
| `f`  | Display variable as floating point |
| `u`  | Display unsigned integer in decimal |
| `o`  | Display variable in octal     |

### Info Commands

| Command                 | Description                    |
| ------------------ | --------------------------- |
| `info breakpoints` | List all breakpoints        |
| `info locals`      | List local variables in current stack frame |
| `info args`        | List function arguments in current stack frame |
| `info threads`     | List all threads            |
| `info program`     | Show current status of program |
| `info registers`   | Show current register values |
| `info frame`       | Show current stack frame information |

### Other Commands

| Command                            | Description                                                |
| ----------------------------- | ------------------------------------------------------- |
| `enable pretty-printer`       | Enable pretty-printer, which can print STL containers in human-readable format |
| `checkpoint`[^checkpoint]     | Create a checkpoint, to which you can rollback          |
| `restart [num]`[^checkpoint]  | Rollback to checkpoint `[num]`                           |
| `save breakpoints [filename]` | Save breakpoints to file                                |
| `source [filename]`           | Import breakpoint file                                  |

???+ tip "Tip"
    Most gdb debugging commands can be abbreviated to uniquely identifying letter abbreviations. For example, `breakpoint` is abbreviated as `b`, `step` is abbreviated as `s`, `info args` is abbreviated as `i ar`. See the `help` command for details.

## References and Notes

[^have-to-link-libm-in-gcc]: [Why do you have to link the math library in C?](https://stackoverflow.com/questions/1033898/why-do-you-have-to-link-the-math-library-in-c)

[^address-sanitizer]: <https://clang.llvm.org/docs/AddressSanitizer.html>

[^thread-sanitizer]: <https://clang.llvm.org/docs/ThreadSanitizer.html>

[^memory-sanitizer]: <https://clang.llvm.org/docs/MemorySanitizer.html>

[^ub-san]: <https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html>

[^gnu-make-built-in-rules]: [Catalogue of Built-In Rules](https://www.gnu.org/software/make/manual/html_node/Catalogue-of-Rules.html)

[^checkpoint]: Commands related to checkpoints are only available on GNU/Linux platforms. See [GDB Manual](https://sourceware.org/gdb/current/onlinedocs/gdb#Checkpoint_002fRestart).