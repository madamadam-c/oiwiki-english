## Code Framework

If you do not want to study the underlying principles in depth, beginners can simply memorize this "framework":

```cpp
#include <cstdio>
#include <iostream>

int main() {
  // do something...
  return 0;
}
```

??? note "What is include?"
    `#include` is actually a preprocessing command. It means to "place" a file at this statement, and the file being placed is called a header file. In other words, during compilation, the compiler "copies" the contents of the header file `iostream` and "pastes" them at the statement `#include <iostream>`. Then you can use objects provided by `iostream`, such as `std::cin`, `std::cout`, and `std::endl`.
    
    If you have learned C, you will notice that most C++ header files we currently encounter do not have the `.h` suffix, while C header files `xx.h` become `cxx`, such as `stdio.h` becoming `cstdio`. Because C++ uses C header files directly for compatibility with C, it uses the `c` prefix to distinguish C++ headers from C headers.
    
    In general, decide which headers to `#include` according to the needs of the C++ program you are writing. Including extra headers only increases compile time and has almost no effect on runtime. So far we have only encountered the two headers `iostream` and `cstdio`. If you only need `scanf` and `printf`, you do not need `#include <iostream>`.
    
    Can you `#include` a header file you wrote yourself? Yes.
    
    You can write a header file, such as `myheader.h`, put it in the same directory as your code, and then write `#include "myheader.h"`. Note that custom headers should use quotation marks rather than angle brackets. Of course, you can also use the compile command `-I <header_file_path>` to tell the compiler where to find headers, so the header file does not need to be in the same directory as the code.

??? note "What is `main()`?"
    You can understand it as the code inside `main()` being executed when the program runs.
    
    In fact, the `main` function is called by the system or an external program. For example, when you call your program from the command line, you are calling the `main` function in your program, after global [variables](./var.md) have been constructed.
    
    The final `return 0;` means the program ran successfully. By default, returning 0 when a program ends means everything is normal; otherwise, the return value represents an error code. On Windows, the hexadecimal form of this error code can be looked up on the [Windows Error Codes website](https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-erref/). Who receives this value? It is the system or external program that called your program; it receives this return value when your program ends. If no `return` statement is written, a normally ending program also returns 0 by default.
    
    In C or C++, a nonzero program return value causes a runtime error (RE).

## Comments

In C++ code, comments have two forms:

1.  Inline comments

    They start with `//`, and everything after it on the same line is a comment.

2.  Comment blocks

    They start with `/*` and end with `*/`; everything in between is a comment and may span multiple lines.

Comments do not affect program execution. They can explain the meaning of a program, and they can also prevent a piece of code from executing while still keeping it in the source file.

In engineering development, comments help future maintenance and make code easier for others to read.

In OI, few people write many comments, but comments can help clarify your thinking while writing code and help with later review. Also, if you write solutions or tutorials, an appropriate number of comments can help readers understand the intent of the code. We hope everyone develops a good habit of writing comments.

## Input and Output

### `cin` and `cout`

```cpp
#include <iostream>

int main() {
  int x, y;                          // Declare variables
  std::cin >> x >> y;                // Read x and y
  std::cout << y << std::endl << x;  // Output y, newline, then output x
  return 0;                          // End the main function
}
```

???+ note "What is a variable?"
    See the [variables](./var.md) page.

???+ note "What is `std`?"
    `std` is the **namespace** used by the C++ standard library. Namespaces are used to avoid duplicate names.
    
    For detailed knowledge about namespaces, see the [namespaces](./namespace.md) page.

### `scanf` and `printf`

`scanf` and `printf` are functions provided by C. In most cases, they are faster than `cin` and `cout`, and they can conveniently control input and output formats.

???+ note "Input/output optimization"
    For the specific differences between `cin`/`cout` and `scanf`/`printf`, and for input/output optimization, see the [input/output optimization](../contest/io.md) page.

```cpp
#include <cstdio>

int main() {
  int x, y;
  scanf("%d%d", &x, &y);   // Read x and y
  printf("%d\n%d", y, x);  // Output y, newline, then output x
  return 0;
}
```

Here, `%d` means the variable being read or output is a signed integer variable of type `int`.

Similarly:

1.  `%s` represents a string.
2.  `%c` represents a character.
3.  `%lf` represents a double-precision floating-point number (`double`).
4.  `%lld` represents a long long integer (`long long`). Depending on the system, it may also be `%I64d`.
5.  `%u` represents an unsigned integer (`unsigned int`).
6.  `%llu` represents an unsigned long long integer (`unsigned long long`), and may also be `%I64u`.

Besides type specifiers, there are also ways to control formatting. Many are rarely used; two common ones are listed below:

1.  `%1d` means an integer with width 1. When reading, digits can be read one by one even without spaces. When outputting, if the specified width is greater than the number of digits, spaces are padded before the number. If the specified width is smaller than the number of digits, it has no effect.
2.  `%.6lf` is used for output and keeps six digits after the decimal point.

Other numbers can be filled in the corresponding positions of these operators. For example, `%.3lf` keeps three digits after the decimal point.

??? note "What are \"double-precision floating-point numbers\" and \"long long integers\"?"
    These represent variable types. As above, they will be explained together in [variables](./var.md).

??? note "Why is there an `&` operator in `scanf`?"
    Here, `&` is actually the address-of operator, returning the address of a variable in memory. The parameters received by `scanf` are the addresses of variables. This may need [pointers](./pointer.md) for a complete explanation; for now, just remember it.

??? note "What is `\n`?"
    `\n` is an **escape character** representing a newline.
    
    Escape characters are used to represent characters that cannot be entered directly, such as newlines that cannot be entered directly inside string literals, quotation marks that have special meaning, and backslashes that are used to indicate escape characters.
    
    Common escape characters include:
    
    1.  `\t` represents a tab character.
    
    2.  `\\` represents `\`.
    
    3.  `\"` represents `"`.
    
    4.  `\0` represents the null character, used to mark the end of a C-style string.
    
    5.  `\r` represents carriage return. On Linux, the newline character is `\n`; on Windows, it is `\r\n`. In OI, if output needs a newline, use `\n`. But when reading character by character, newline characters may cause some issues. For example, `gets` treats `\n` as the end of the string; if the newline is `\r\n`, `\r` remains at the end of the string.
    
    6.  In particular, `%%` represents `%` and can only be used in `printf` or `scanf`; in other string literals, simply use `%`.
    
    ??? note "What is a literal?"
        A "literal" is a program fragment that appears directly as a value in code. For example, `3` is an `int` literal, and `'c'` is a `char` literal. The `"hello world"` in the program above is also a string literal.
        
        Unexplained literals without context are also called "magic numbers". If code needs to be read by others, this is strongly discouraged.

## Some Extended Content

### Whitespace in C++

In C++, all whitespace characters, including spaces, tabs, and newlines, whether multiple or single, are treated the same. Of course, this does not include characters inside quotation marks that are treated as part of a string.

Therefore, you can freely use any code style, except that inline comments, string literals, and preprocessing commands must be on a single line. For example:

```cpp
--8<-- "docs/lang/code/basic/basic_1.cpp:main"
```

Of course, doing this is not recommended.

Another code style that is widely used but differs from the style required by **OI Wiki**:

```cpp
--8<-- "docs/lang/code/basic/basic_2.cpp:main"
```

### The `#define` Command

`#define` is a preprocessing command used to define macros. It is essentially text substitution. For example:

```cpp
#include <iostream>
#define n 233

// n is not a variable. The compiler replaces all text n in the code with 233,
// but n as part of an identifier is not replaced, so fn is not replaced by f233;
// likewise, occurrences inside strings are not replaced

int main() {
  std::cout << n;  // Output 233
  return 0;
}
```

??? note "What is an identifier?"
    An identifier is a sequence of characters that can be used as a variable name. For example, `abcd` and `abc1` are valid identifiers, while `1a` and `c+b` are not.
    
    An identifier starts with an English letter or underscore, and may contain only English letters, underscores, and digits afterward. Note that keywords such as `int`, `for`, and `if` cannot be used as identifiers.

??? note "What is a preprocessing command?"
    A preprocessing command is a command accepted by the preprocessor, used for preliminary textual transformations of code, such as file inclusion with `#include` and macro processing with `#define`. For GCC, the output `.i` file of the preprocessing stage is not kept by default. You can use the `-E` option to keep the output file.

Macros can take parameters, and parameterized macros can be used like functions:

```cpp
#include <iostream>
#define sum(x, y) ((x) + (y))
#define square(x) ((x) * (x))

int main() {
  std::cout << sum(1, 2) << ' ' << 2 * sum(3, 5) << std::endl;  // Output 3 16
}
```

However, parameterized macros differ from functions. Because macros are text substitution, they can cause many problems. For example:

```cpp
#include <iostream>
#define sum(x, y) x + y
// This should be #define sum(x, y) ((x) + (y))
#define square(x) ((x) * (x))

int main() {
  std::cout << sum(1, 2) << ' ' << 2 * sum(3, 5) << std::endl;
  // The output is 3 11, because #define is text substitution and the later
  // statement is replaced by 2 * 3 + 5
  int i = 1;
  std::cout << square(++i) << ' ' << i;
  // The output is undefined, because ++i is executed twice
  // and modifying the same variable multiple times in one statement is undefined behavior (with exceptions)
}
```

Using `#define` is risky. Since the scope of `#define` is the entire program, it may cause text to be replaced unexpectedly, so `#undef` should be used promptly to cancel definitions. Therefore, use it carefully. A more recommended practice is to declare constants with the `const` qualifier and use functions instead of macros.

However, in OI, `#define` is still useful. The following two uses are not recommended because they reduce code standardization:

1.  `#define int long long` plus `signed main()`. This is usually used to avoid errors caused by forgetting to use `long long`, or to rule out such errors during debugging. It may also increase constants and even cause TLE, or cause MLE due to excessive memory usage.
2.  `#define For(i, l, r) for (int i = (l); i <= (r); ++i)`, `#define pb push_back`, and `#define mid ((l + r) / 2)`, used to shorten code length.

Still, `#define` also has advantages. For example, it works well with preprocessing directives such as `#ifdef`:

```cpp
#ifdef LINUX
// code for linux
#else
// code for other OS
#endif
```

You can control the compiled code with `-DLINUX` during compilation without modifying the source file. This has another advantage: the executable compiled with `-DLINUX` does not contain code for other operating systems, because that code has already been removed during preprocessing.

`#define` can also use the `#` and `##` operators, which are very helpful for debugging.
