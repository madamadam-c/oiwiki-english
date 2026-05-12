disqus:

## Environment Setup

To do good work, one must first sharpen one's tools.

### Integrated Development Environment

IDEs are relatively easy to use, so beginners usually choose an IDE to write code. The most common one in contests is [Dev-C++](../tools/editor/devcpp.md); if the exam environment is Windows, this IDE is usually provided.

### Compiler

#### Windows

The GNU compiler is recommended. Download and install MinGW from [MinGW Distro](https://nuwen.net/mingw.html). On Windows, you can also choose the [Microsoft Visual C++ compiler](https://learn.microsoft.com/en-us/cpp/build/projects-and-build-systems-cpp), which can be downloaded and installed from the [Visual Studio page](https://visualstudio.microsoft.com/downloads/).

#### macOS

Run this in the terminal:

```bash
xcode-select --install
```

#### Linux

Use `g++ -v` to check whether `g++` has been installed.

You can install it with the following command:

```bash
sudo apt update && sudo apt install g++
```

#### Compiling Code on the Command Line

After becoming familiar with programming, some contestants use the more flexible command line to compile code. This avoids dependence on an IDE and lets them write code with their preferred text editor.

```bash
g++ test.cpp -o test -lm
```

`g++` is the compiler for C++ (`gcc` is the compiler for C). `-o` specifies the name of the executable file. The compile option `-lm` links the math library `libm`, allowing code that uses `math.h` to compile and run correctly.

Note: C++ programs can compile and run normally without `-lm`. The C++ compile options for past NOI/NOIP problems included `-lm`, so it is included here as well.

## First Program

Begin your journey into C++ with this sample program.

Note: before writing code, make sure you are using an English input method.

C++ language

```cpp
#include <iostream>  // Include a header file

int main() {                     // Define the main function
  std::cout << "Hello, world!";  // Use cout from the standard namespace
  return 0;  // Return 0 and end main. The compiler usually adds this line automatically, so it can often be omitted
}
```

C language

```c
#include <stdio.h>  // Include a header file

int main() {                // Define the main function
  printf("Hello, world!");  // Output Hello, world!
  return 0;                 // Return 0 and end main
}
```

Note: C is shown here only for reference. C++ is largely compatible with C and has many new features that can help contestants work more efficiently during contests. For details, see [Differences Between C++ and Other Common Languages](./cpp-other-langs.md).
