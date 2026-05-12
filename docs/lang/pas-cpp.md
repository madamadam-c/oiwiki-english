author: kexplorning, Ir1d, lvneg1

## Quick C++ Installation And Environment Setup

The following steps are for Windows.

### Using An IDE

See the following pages:

-   [Dev-C++](../tools/editor/devcpp.md)
-   [Code::Blocks](../tools/editor/codeblocks.md)

### Using A Code Editor + Compiler + Debugger

See the [VS Code](../tools/editor/vscode.md) page. The official Visual Studio Code website also documents how to configure C++. In general, VS Code is more convenient when used with extensions; see the [official VS Code website](https://code.visualstudio.com/).

## Quick C++ Syntax Notes

C++ programs start running from the `main` part.

Braces mark the beginning and end of a block statement: `{` is equivalent to Pascal's `begin`, and `}` is equivalent to `end`.

As in Pascal, every C++ statement ends with a semicolon `;`, but a closing brace does not need a semicolon, and the program does not end with a period `.`.

For comments, `//` denotes a line comment, and `/* */` denotes a block comment.

By convention, let us look at Hello World.

### Hello World: The First C++ Program

```cpp
#include <iostream>  // Imports the iostream library

int main()  // main part
{
  std::cout << "Hello World!" << std::endl;

  return 0;
}
```

Compile and run it, then look at the result.

#### Brief Explanation

The first line, `#include <iostream>`, means importing the `iostream` library.

??? note "Pascal library files"
    Pascal actually has library files too, although many students have never used them.

See `main` on the third line? The program starts executing from `main`.

The most important statement is:

```cpp
std::cout << "Hello World!" << std::endl;
```

`std::cout` is the output command. You may have seen some C++ programs write just `cout`.

??? note "About the std:: prefix"
    For the `std::` prefix, see the note "What is std?" under [this section](basic.md#cin-与-cout).

The `<<` in the middle visually suggests flow; it describes how output "flows". This line means that `"Hello World!"` is first pushed into the output stream, and then `std::endl` is pushed into the output stream.

`std::endl` is the **output** newline command. It is similar to Pascal's `writeln`, but C++ has no `coutln`. The difference between Pascal and C++ is that `write('Hello World!')` is equivalent to `std::cout << "Hello World!"`, while `writeln('Hello World!')` is equivalent to `std::cout << "Hello World!" << std::endl`.

Here `"Hello World!"` is a string. Pascal strings use single quotes `'` and cannot use double quotes, while C++ strings must use double quotes. Characters enclosed in single quotes in C++ have another meaning, which will be mentioned later.

That is enough explanation for Hello World.

Some students may ask what the later `return 0` means, or what `int main()` means. **Ignore them for now**. When you first start programming, just treat them as a template. Because beginner programs usually do not use parameters in `main`, there is no need to write `int main(int argc, char const *argv[])`.

#### Simple Exercises

1.  Try outputting a different string.
2.  Try learning about escape characters.

### A+B Problem: The Second C++ Program

The classic A+B Problem.

```cpp
#include <iostream>

int main() {
  int a, b, c;

  std::cin >> a >> b;

  c = a + b;

  std::cout << c << std::endl;

  return 0;
}
```

Note: the code contains many blank lines; remove them if you are not used to this style.

#### Brief Explanation

`std::cin` reads input (`cin` means C-in), and `>>` is similar to the output syntax.

The most important new statements are two kinds of statements. One is the variable declaration statement.

```cpp
int a, b, c;
```

You may be used to declaring variables in Pascal like this:

```pas
var
a, b, c: integer;
```

C++ declarations start directly with the data type name. Here, `int` (integer type) means that the following names declare variables.

The other important statement is assignment.

```cpp
c = a + b;
```

This is a major syntax difference between Pascal and C++: Pascal assignment is `:=`, while C++ assignment is `=`; equality comparison in C++ is `==`.

C++ can also initialize variables directly in the declaration.

```cpp
int a = 0, b = 0, c = 0;
```

#### Simple Exercises

1.  Rewrite the code, submit it to an OJ, and get AC.
2.  For more input/output syntax, see [this section](basic.md#scanf-与-printf), and try learning C++ formatted output.

### Closing Remarks And Next Steps

At this point, you have learned some of the most basic things. The rest is to find the corresponding syntax and different features in Pascal and C++.

Before that, however, it is strongly recommended that you read [Variable Scope: Global Variables And Local Variables](#variable-scope-global-variables-and-local-variables).

Use <kbd>Alt</kbd>+<kbd>←</kbd> and <kbd>Alt</kbd>+<kbd>→</kbd> to navigate back and forward.

## Syntax

### Variables

#### Basic Data Types

C++ and Pascal are basically similar. Common types include:

-   `bool`: Boolean type
-   `int`: integer type
-   `float`: single-precision floating-point type
-   `double`: double-precision floating-point type
-   `char`: character type
-   `void`: no type

C++ single quotes are specifically used for single characters (character type), such as `'a'`; strings (character arrays) must use double quotes.

C++ has many other data types. See [Fundamental types - cppreference.com](https://en.cppreference.com/w/cpp/language/types).

#### Constant Declarations

```cpp
const double PI = 3.1415926;
```

If you are not familiar with macro expansion, use constants instead of macros.

### Operators

See [Operators](./op.md). The appendix also provides a Pascal/C++ syntax comparison table for operators and mathematical functions.

### Conditions

#### `if` Statements

```pas
if (a = b) and (a > 0) and (b > 0) then
    begin
        b := a;
    end
else
    begin
        a := b;
    end;
```

```cpp
if (a == b && a > 0 && b > 0) {
  b = a;
} else {
  a = b;
}
```

Boolean operations and comparisons:

-   `and -> &&`
-   `or -> ||`
-   `not -> !`
-   `= -> ==`
-   `<> -> !=`

Notes:

1.  Pascal's `and` and C++'s `&&` have different precedence. C++ does not need extra parentheses around every comparison.
2.  Pascal uses `=` for equality and `:=` for assignment; C++ uses `==` for equality and `=` for assignment.
3.  If you write `a = b` instead of `a == b` inside the parentheses of an `if` statement, the program will not report an error. It assigns `b` to `a`, and the assignment expression `a = b` as a whole has the value of `a` after assignment.
4.  In C++, you do not need to decide whether to add a semicolon after `end`.
5.  In C++ Boolean operations, non-Boolean values can be automatically converted to Boolean values.

???+ warning "Common pitfall"
    Pay special attention: **do not write `=` when you mean `==`!**
    
    Since C/C++ syntax is more flexible than Pascal syntax, writing `if (a=b)` in a condition lets the program keep running, because `a=b` has a return value in C++.

#### `case` And `switch`

They are not used very often, so they are not discussed in detail here.

Note that C++ has no `1..n`, and no chained inequalities such as `1 < x < 2`.

### Loops

The following three loop forms and six pieces of code implement the same behavior.

#### `while` Loops

`while` is very similar. The C++ snippets here are not complete programs; some framework/template code is omitted. The same applies below.

```pas
var i: integer;

begin
    i := 1;
    while i <= 10 do
        begin
            write(i,' ');
            inc(i); // or i := i + 1;
        end;
end.
```

```cpp
int i = 1;
while (i <= 10) {
  std::cout << i << " ";
  i++;
}
```

#### `for` Loops

C++ `for` statements are very different.

```pas
var i: integer;

begin
    for i:= 1 to 10 do
        begin
            write(i, ' ');
        end;
end.
```

```cpp
for (int i = 1; i <= 10; i++) {
  std::cout << i << " ";
}
```

Notes:

1.  The line `for (int i = 1; i <= 10; i++){` contains many parts: there are three statements inside `for`.
2.  The first statement, `int i = 1;`, declares a local variable `i` and initializes it. This design is much more reasonable than Pascal's.
3.  The second statement, `i <= 10;`, is the condition for whether the loop continues.
4.  The third statement, `i++`, is executed at the end of every iteration. It roughly means Pascal's `inc(i)`. Writing `++i` here is also the same. For the difference between `i++` and `++i`, see other materials.

#### `repeat until` And `do while` Loops

Note that `repeat until` and `do while` are different. Compare the following code:

```pas
var i: integer;

begin
    i := 1;
    repeat
        write(i, ' ');
        inc(i);
    until i = 11;
end.
```

```cpp
int i = 1;
do {
  std::cout << i << " ";
  i++;
} while (i <= 10);
```

#### Loop Control

In C++, `break` works the same as in Pascal: it exits the loop.

`continue` is also the same: it skips the current iteration and proceeds to the next one.

### Arrays And Strings

#### Variable-Length Arrays: The Standard Library Type `vector`

See the [sequence containers](csl/sequence-container.md) page.

The C++ standard library provides `vector`, which is equivalent to a variable-length array. You need to include its library header before using it.

```cpp
#include <iostream>
#include <vector>  // Imports the vector library

int main() {
  std::vector<int> a;  // Declares vector a and defines it as an empty vector object
  int n;

  std::cin >> n;
  // Reads a
  for (int i = 0; i < n; i++) {
    int t;
    std::cin >> t;
    a.push_back(t);  // Puts the read number t at the end of vector a; this operation is O(1)
    /* You cannot assign by subscript here, because when a is declared,
    its size is still empty. Using `a[i] = t;` here is wrong.
    */
  }

  // Prints all numbers read into a
  for (int i = 0; i < n; i++) {
    std::cout << a[i] << ", ";  // Note: the first number in a is a[0]
    // If the subscript is out of bounds, it returns an unknown value (overflow) instead of reporting an error
  }
  std::cout << std::endl;

  return 0;
}
```

C++ accesses array members similarly to Pascal, but with one important difference: the first item of an array is `a[0]`, while Pascal lets you specify this yourself.

#### Strings: The Standard Library Type `string`

See the [string](csl/string.md) page.

The C++ standard library provides `string`. Some operations are similar to those available for `vector`; you also need to include its library header.

```cpp
#include <iostream>
#include <string>

int main() {
  std::string s;  // Declares string s

  std::cin >> s;  // Reads s
  // Leading whitespace (spaces, newlines, tabs) is ignored; reading stops at the next whitespace character.

  std::cout << s << std::endl;

  return 0;
}
```

#### C-Style Arrays

See the [arrays](array.md) page.

If you need variable-length arrays, use `vector`; do not use C-style arrays.

C-style arrays are closely related to pointers, so they are not expanded on here.

## Important Differences

### Variable Scope: Global Variables And Local Variables

C++ can declare variables almost **anywhere**. See [variable scope](var.md#variable-scope).

When writing Pascal procedures/functions, it is easy to forget to declare local variables such as `i` or `j`. Since the main program usually contains loops, `i` and `j` are often global variables. In that case, operating on `i` inside a procedure/function can easily go wrong. Worse still, if you forget to declare such local variables, the compiler does not report an error, and the program can run. Many hard-to-find bugs come from this.

Therefore, when using C++, variables such as loop variable `i` **should not be global if they can be local**. If you do this, you do not need to worry about name conflicts in functions, such as conflicts involving `i`.

??? note "Additional note"
    Pascal can avoid this problem to some extent by imitating the C++ approach: let the main program only call procedures/functions, and do not declare easily conflicting global variables such as `i` and `j`. If a loop is needed, write another procedure and call it.

### C++ Can Automatically Convert Types

```cpp
int i = 2;
if (i) {  // i = 0 returns false; all other values return true
  std::cout << "true";
} else {
  std::cout << "false";
}
```

It is not only `int` to `bool`; `int` and `float` can also convert to each other. In Pascal, an integer can be assigned to a floating-point type, but not the other way around. C++ has no such problem.

```cpp
int a;
a = 3.2;      // Now a = 3
float b = a;  // Now b = 3.0
```

Whether `/` means integer division or floating-point division is determined by the types of the dividend and divisor.

```cpp
float a = 32 / 10;    // The result of 32/10 is 3 (integer division); a = 3.0
float b = 32.0 / 10;  // The result of 32.0/10 is 3.2; b = 3.2
```

`pow(a, b)` computes $a^b$. This function returns a floating-point value. If it is used directly to compute an integer power, automatic conversion prevents an error.

```cpp
int a = pow(2, 3);  // Computes 2^3
```

There are also conversions between `char` and `int`.

```cpp
char a = 48;              // ASCII 48 is '0'
int b = a + 1;            // b = 49
std::cout << (a == '0');  // true, outputs 1
```

In fact, `char` and `bool` are essentially integer types in C++.

For details, see [Implicit conversions - cppreference.com](https://en.cppreference.com/w/cpp/language/implicit_conversion).

### Many C++ Statements Have Return Values: Reading An Unknown Amount Of Data

Sometimes you need to read until the input ends. For example, to compute the sum of an unknown number of integers, possibly across multiple lines, until the end of file, use:

??? note "End of file (EOF)"
    EOF is the end-of-file marker. In a command line, enter it with <kbd>Ctrl</kbd>+<kbd>Z</kbd> on Windows (then press <kbd>Enter</kbd>) and with <kbd>Ctrl</kbd>+<kbd>D</kbd> on Unix-like systems.

```cpp
#include <iostream>

int main() {
  int sum = 0, a = 0;

  while (std::cin >> a) {
    sum += a;
  }
  std::cout << sum << std::endl;

  return 0;
}
```

Principle: in `while (std::cin >> a)`, `std::cin >> a` returns `false` if input has a problem or reaches the end of file, causing the loop to stop.

### Functions

C++ has functions but no procedures; it has `void`, no function-value variable, but it has `return`.

Pascal function and C++ function comparison:

```pas
function abs(x:integer):integer;
begin
    if x < 0 then
        begin
            abs := -x;
        end
    else
        begin
            abs := x;
        end;
end;
```

```cpp
int abs(int x) {
  if (x < 0) {
    return -x;
  } else {
    return x;
  }
}
```

In C++, the function declaration `int abs` defines the function `abs()` with return type `int` (integer). The function's return value is the value given by the `return` statement.

If you do not want a return value (that is, Pascal's "procedure"), use `void`. `void` means "empty" and returns nothing.

```pas
var ans: integer;

procedure printAns(ans:integer);
begin
    writeln(ans);
end;

begin
    ans := 10;
    printAns(ans);
end.
```

```cpp
#include <iostream>

void printAns(int ans) {
  std::cout << ans << std::endl;

  return;
}

int main() {
  int ans = 10;
  printAns(ans);

  return 0;
}
```

C++ `return` differs greatly from assigning to a Pascal function variable. In C++, `return` returns a value, and after this statement is executed, the function ends. In Pascal, assigning to the function variable does not exit the function; execution continues. Therefore, if Pascal needs to interrupt a function/procedure somewhere, it needs the extra command `exit`. C++ does not need this: if you need to interrupt somewhere, just use `return`. For example:

```cpp
#include <iostream>

void printWarning(int x) {
  if (x >= 0) {
    return;  // This statement is equivalent to Pascal's `exit;` here
  }
  std::cout << "Warning: input a negative number.";
}

int main() {
  int a;

  std::cin >> a;
  printWarning(a);

  return 0;
}
```

In a sense, the previous `abs` function is strictly equivalent to this Pascal version:

```pas
function abs(x:integer):integer;
begin
    if x < 0 then
        begin
            abs := -x; exit; // Note here
        end
    else
        begin
            abs := x;  exit; // Note here
        end;
end;
```

```cpp
int abs(int x) {
  if (x < 0) {
    return -x;
  } else {
    return x;
  }
}
```

???+ note "Special reminder"
    In C++, `exit` exits the program. Do not casually type `exit`; use `return`!

C++ treats functions and procedures uniformly as functions, and even `main` is no exception. For example, when you write `int main`, C++ treats `main` as a function returning an integer. The return value here is `0`, a convention meaning that the program exits normally.

You may already have guessed that the parameters in `main(int argc, char const *argv[])` are `int argc` and `char const *argv[]`, but see other materials for their meaning.

### Passing Parameters To Functions

C++ has no Pascal `var` keyword to modify passed parameters, but C++ can achieve the same effect with references and pointers.

```pas
var a, b: integer;

procedure swap(var x,y:integer);
var temp:integer;
begin
    temp := x;
    x := y;
    y := temp;
end;

begin
    a := 10; b:= 20;    
    swap(a, b);
    writeln(a, ' ', b);
end.
```

```cpp
// Code using pointers
#include <iostream>

void swap(int* x, int* y) {
  int temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

int main() {
  int a = 10, b = 20;
  swap(&a, &b);
  std::cout << a << " " << b;

  return 0;
}
```

Note that this C++ code **involves pointers**. Pointers are troublesome, so it is recommended that you read related materials.

```cpp
// Code using references
#include <iostream>

void swap(int& x, int& y) {
  int temp;
  temp = x;
  x = y;
  y = temp;
}

int main(int argc, char const* argv[]) {
  int a = 10, b = 20;
  swap(a, b);
  std::cout << a << " " << b;

  return 0;
}
```

Note that this C++ code involves **reference-related type issues**. When using references with some STL libraries or template libraries, you may encounter problems where you need to manually declare alias types. See *C++ Primer*, 5th edition, or online materials for details.

C++ has other ways to pass function parameters. One is **directly using global variables to pass parameters**. If you do not know how to use pointers, you can use this method first. Its defect is that no stack saves the data, so **parameters cannot be passed in recursive functions**. Unless you write a stack manually; note that a manually written stack is also a way to bypass system stack limits.

## C++ Standard Library And References

Never reinvent the wheel unless you are practicing. Before implementing a feature yourself, first check whether there is already such a function or data structure.

### C++ Standard Library

The C++ standard library's `<algorithm>` contains many useful functions, such as quicksort and binary search, which can be called directly. See the [STL algorithms](csl/algorithm.md) page.

There are also STL containers, such as arrays, vectors (variable-size arrays), queues, stacks, and many associated functions. See the [STL container introduction](csl/container.md) page.

For string operation functions, see:

-   [std::basic\_string - cppreference.com](https://en.cppreference.com/w/cpp/string/basic_string)
-   [`<string>`- C++ Reference](https://www.cplusplus.com/reference/string/)

C/C++ pointers are very flexible. See the [pointers](pointer.md) page. If you want to thoroughly understand pointers, find a book or reference manual and read it carefully.

### Debugging And Tips

-   [Common mistakes](../contest/common-mistakes.md)
-   [Common tricks](../contest/common-tricks.md)

### C++ Language Resources

-   [Learning resources](../contest/resources.md)
-   [cppreference.com](https://en.cppreference.com/): the most important C/C++ reference
-   [C++ Tutorial - GeeksforGeeks](https://www.geeksforgeeks.org/c-plus-plus/)
-   [C++ Language - C++ Tutorials](https://www.cplusplus.com/doc/tutorial/)
-   [Reference - C++ Reference](https://www.cplusplus.com/reference/)
-   [C++ Standard Library - Wikipedia](https://en.wikipedia.org/wiki/C%2B%2B_Standard_Library)
-   [The Ultimate Question of Programming, Refactoring, and Everything](https://www.gitbook.com/book/alexastva/the-ultimate-question-of-programming-refactoring-/details)
-   [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

## Postscript

After reading this far, many students may feel that this is not much of an emergency guide, because many things are missing. That cannot really be avoided.

Although this is intended as an emergency guide, topics such as converting strings to numbers and searching for characters in strings do not fit into a concise emergency post. If all of those were included, this would become a C++ beginner tutorial, so make full use of this Wiki, reference manuals, and search engines.

One thing to point out is that much of the C++ syntax above actually comes from C. A more accurate title would be "Emergency Guide For Pascal To C/C++".

Pascal was a very popular language in the second half of the previous century. It predates C, but with the spread of UNIX systems and Microsoft's use of C, Pascal has now become history. Pascal also had later development, such as the open-source Free Pascal compiler project, which added object-oriented features (the Delphi language). Today, besides use in informatics competitions, Pascal has one feature that other languages do not: compiler support for many old machines, such as the Game Boy, Nintendo's console from the previous century. It is also used as pseudocode (Pascal-style pseudocode) in various textbooks.

Finally, Pascal's community is small, while the C/C++ community is large, with many complete manuals and tutorials. Be sure to learn English well. There are many, many programming languages in the world, and computer science and technology are not only informatics competitions and programming languages.

### Pascal References For This Article

-   [Lazarus wiki](https://wiki.freepascal.org/)
-   [Free Pascal Reference guide](https://freepascal.org/docs-html/current/ref/ref.html)

## Appendix: Pascal And C++ Operator And Mathematical Function Syntax Comparison Table

Only the most commonly used operators and functions are included.

### Basic Arithmetic

|                  | Pascal    | C++     |
| ---------------- | --------- | ------- |
| Addition         | `a + b`   | `a + b` |
| Subtraction      | `a - b`   | `a - b` |
| Multiplication   | `a * b`   | `a * b` |
| Integer division | `a div b` | `a / b` |
| Floating division | `a / b`  | `a / b` |
| Modulo           | `a mod b` | `a % b` |

### Logic

|     | Pascal    | C++                   |
| --- | --------- | --------------------- |
| Not | `not(a)`  | `!a`                  |
| And | `a and b` | `a && b`              |
| Or  | `a or b`  | <code>a \|\| b</code> |

### Comparison

|                  | Pascal   | C++      |
| ---------------- | -------- | -------- |
| Equal            | `a = b`  | `a == b` |
| Not equal        | `a <> b` | `a != b` |
| Greater than     | `a > b`  | `a > b`  |
| Less than        | `a < b`  | `a < b`  |
| Greater or equal | `a >= b` | `a >= b` |
| Less or equal    | `a <= b` | `a <= b` |

### Assignment

| Pascal                         | C++      |
| ------------------------------ | -------- |
| `a := b`                       | `a = b`  |
| `a := a + b`                   | `a += b` |
| `a := a - b`                   | `a -= b` |
| `a := a * b`                   | `a *= b` |
| `a := a div b` or `a := a / b` | `a /= b` |
| `a := a mod b`                 | `a %= b` |

### Increment And Decrement

|           | Pascal   | C++   |
| --------- | -------- | ----- |
| Increment | `inc(a)` | `a++` |
| Increment | `inc(a)` | `++a` |
| Decrement | `dec(a)` | `a--` |
| Decrement | `dec(a)` | `--a` |

### Mathematical Functions

Include the `<cmath>` library before using them.

|             | Pascal     | C++                         |
| ----------- | ---------- | --------------------------- |
| Absolute value | `abs(a)` | `abs(a)` (integer)          |
| Absolute value | `abs(a)` | `fabs(a)` (floating-point)  |
| $a^b$       | N/A[^ref1] | `pow(a, b)`                 |
| Truncation  | `trunc(a)` | `trunc(a)`                  |
| Rounding    | `round(a)` | `round(a)`                  |

[^ref1]: Extended Pascal has `a**b`, but it requires importing the `Math` library.

For other functions, see:

-   [Common mathematical functions - cppreference.com](https://en.cppreference.com/w/cpp/numeric/math)
