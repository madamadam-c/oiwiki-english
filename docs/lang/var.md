## Data Types

The C++ type system consists of the following parts:

1.  Fundamental types (representative keywords/types are shown in parentheses)
    1.  No type/`void` type (`void`)
    2.  Null pointer type since C++11 (`std::nullptr_t`)
    3.  Arithmetic types
        1.  Integer types (`int`)
        2.  Boolean type/`bool` type (`bool`)
        3.  Character types (`char`)
        4.  Floating-point types (`float`,`double`)
2.  Compound types[^note11]

### Boolean Type

A variable of type `bool` can have only two values: `true` and `false`.

In general, a `bool` variable occupies $1$ byte of space. Usually, $1$ byte = $8$ bits.

???+ tip "Tip"
    The number of bits in a byte can be obtained through the macro constant `CHAR_BIT` in the header `<climits>` (C++) or `<limits.h>` (C).

???+ note "Boolean type in C"
    See also [Differences between C++ and other common languages - bool](./cpp-other-langs.md#bool).
    
    The C language originally had no Boolean type. `_Bool` was introduced as a Boolean type in C99 and is regarded as an unsigned integer type.
    
    ???+ note "Note"
        Since C23, C's `bool` type is no longer defined using integer zero and nonzero values. Instead, it is defined as a type capable of storing the two constants `true` and `false`.
    
    For convenience, `stdbool.h` provides the three macros `bool`, `true`, and `false`, defined as follows:
    
    ```c
    #define bool _Bool
    #define true 1
    #define false 0
    ```
    
    These macros were removed in C23. Since C23, `true`, `false`, and `bool` are introduced as keywords, while `_Bool` is retained as an alternative spelling[^note10].
    
    Since C23, the width of the Boolean type can also be obtained through the macro constant `BOOL_WIDTH` in `<limits.h>`.

### Integer Types

Integer types are used to store integers. The most basic integer type is `int`.

???+ warning "Note"
    For historical reasons, Boolean and character types are considered special integer types in C++.
    
    In almost all cases, character types other than `signed char` and `unsigned char` **should not** be used as integer types.

Integer types generally have five width levels: `char`,`short`,`int`,`long`,`long long`.

The C++ standard guarantees `1 == sizeof(char) <= sizeof(short) <= sizeof(int) <= sizeof(long) <= sizeof(long long)`.

For historical reasons, there are multiple popular models for integer type widths. To solve this problem, C99/C++11 introduced [fixed-width integer types](#fixed-width-integer-types).

???+ note "Size of the `int` type"
    The C++ standard specifies that `int` has **at least** $16$ bits.
    
    In fact, on most modern platforms, `int` has $32$ bits.

The `int` keyword can be modified by the following keywords:

Signedness:

-   `signed`: indicates a signed integer, the default.
-   `unsigned`: indicates an unsigned integer.

Size:

-   `short`: indicates an integer of **at least** $16$ bits.
-   `long`: indicates an integer of **at least** $32$ bits.
-   `long long` since C++11: indicates an integer of **at least** $64$ bits.

The following table gives the bit width and representable range size of each integer type **in general**. On a few platforms, some types may have ranges different from those shown below.

| Type name                                                               | Equivalent type           | Width (C++ standard) | Common width | Less common width                    |
| ----------------------------------------------------------------------- | ------------------------- | -------------------- | ------------ | ------------------------------------ |
| `signed char`                                                           | `signed char`             | $8$                  | -            | -                                    |
| `unsigned char`                                                         | `unsigned char`           | $8$                  | -            | -                                    |
| `short`,`short int`,`signed short`,`signed short int`                   | `short int`               | $\geq 16$           | $16$         | -                                    |
| `unsigned short`,`unsigned short int`                                   | `unsigned short int`      | $\geq 16$           | $16$         | -                                    |
| `int`,`signed`,`signed int`                                             | `int`                     | $\geq 16$           | $32$         | $16$ (common in Win16 API)           |
| `unsigned`,`unsigned int`                                               | `unsigned int`            | $\geq 16$           | $32$         | $16$ (common in Win16 API)           |
| `long`,`long int`,`signed long`,`signed long int`                       | `long int`                | $\geq 32$           | $32$         | $64$ (common on 64-bit Linux, macOS) |
| `unsigned long`,`unsigned long int`                                     | `unsigned long int`       | $\geq 32$           | $32$         | $64$ (common on 64-bit Linux, macOS) |
| `long long`,`long long int`,`signed long long`,`signed long long int`   | `long long int`           | $\geq 64$           | $64$         | -                                    |
| `unsigned long long`,`unsigned long long int`                           | `unsigned long long int`  | $\geq 64$           | $64$         | -                                    |

When the bit width is $x$, the representable range of a signed type is $-2^{x-1}\sim 2^{x-1}-1$[^note16], and the representable range of an unsigned type is $0 \sim 2^x-1$. Specifically:

| Width | Representable range                                                |
| ----- | ------------------------------------------------------------------ |
| $8$   | signed: $-2^{7}\sim 2^{7}-1$, unsigned: $0 \sim 2^{8}-1$          |
| $16$  | signed: $-2^{15}\sim 2^{15}-1$, unsigned: $0 \sim 2^{16}-1$       |
| $32$  | signed: $-2^{31}\sim 2^{31}-1$, unsigned: $0 \sim 2^{32}-1$       |
| $64$  | signed: $-2^{63}\sim 2^{63}-1$, unsigned: $0 \sim 2^{64}-1$       |

???+ note "Equivalent type spellings"
    When there is no ambiguity, some modifier keywords may be omitted, or their order may be changed. This means the same type may have multiple equivalent spellings.
    
    For example, `int`, `signed`, `int signed`, and `signed int` denote the same type, while `unsigned long` and `unsigned long int` denote the same type.

In addition, some compilers implement extended integer types. For example, GCC implements 128-bit integers: the signed `__int128_t` and the unsigned `__uint128_t`. If you want to use these types in a contest, **read the contest rules carefully** to determine whether extended integer types are allowed or supported.

???+ warning "Note"
    The STL may not provide sufficient support for extended integer types, so use them with extra care.
    
    ???+ note "Example code"
        ```cpp
        #include <cmath>
        #include <iostream>
        
        int f1(int n) {
          return abs(n);  // Good
        }
        
        int f2(int n) {
          return std::abs(n);  // Good
        }
        
        __int128_t f3(__int128_t n) {
          return abs(n);  // Bad
        }
        
        // Wrong
        // __int128_t f4(__int128_t n) {
        //   return std::abs(n);
        // }
        
        int main() {
          std::cout << "f1: " << f1(-42) << std::endl;
          std::cout << "f2: " << f2(-42) << std::endl;
          // std::cout << "f3: " << f3(-42) << std::endl; // Wrong
          // std::cout << "f4: " << f4(-42) << std::endl; // Wrong
          return 0;
        }
        ```
    
    The example code above has the following problems:
    
    1.  `__int128_t f3(__int128_t)` uses a C-style absolute value function whose signature is `int abs(int)`, so `n` is first cast to `int` before the `abs` function is called.
    2.  `__int128_t f4(__int128_t)` uses a C++-style absolute value function, but there is no overload with the signature `__int128_t std::abs(__int128_t)`, so it cannot compile.
    3.  C++ stream output does not support `__int128_t` or `__uint128_t`.
    
    One possible solution is:
    
    ??? note "Corrected code"
        ```cpp
        #include <cmath>
        #include <iostream>
        
        __int128_t abs(__int128_t n) { return n < 0 ? -n : n; }
        
        std::ostream &operator<<(std::ostream &os, __uint128_t n) {
          if (n > 9) os << n / 10;
          os << (int)(n % 10);
          return os;
        }
        
        std::ostream &operator<<(std::ostream &os, __int128_t n) {
          if (n < 0) {
            os << '-';
            n = -n;
          }
          return os << (__uint128_t)n;
        }
        
        int f1(int n) { return abs(n); }
        
        int f2(int n) { return std::abs(n); }
        
        __int128_t f3(__int128_t n) { return abs(n); }
        
        int main() {
          std::cout << "f1: " << f1(-42) << std::endl;
          std::cout << "f2: " << f2(-42) << std::endl;
          std::cout << "f3: " << f3(-42) << std::endl;
        }
        ```

### Character Types

Character types are divided into "narrow character types" and "wide character types". Since wide character types are almost never used in algorithm contests, only narrow character types are introduced here.

Narrow character types generally have $8$ bits. Their underlying storage is still integer-based, and [ASCII encoding](http://www.asciitable.com/) is usually used to map characters and integers one-to-one. There are three such types:

-   `signed char`: a signed character representation type, with a range of $-128 \sim 127$.
-   `unsigned char`: an unsigned character representation type, with a range of $0 \sim 255$.
-   `char` has the same representation and alignment as either `signed char` or `unsigned char`, but is always a distinct type.

    The signedness of `char` depends on the compiler and target platform. ARM and PowerPC defaults are usually unsigned, while x86 and x64 defaults are usually signed.

    GCC can use the compilation options `-fsigned-char` or `-funsigned-char` to specify whether `char` is treated as `signed char` or `unsigned char`. For other compilers, refer to their documentation. Note that specifying signedness different from the architecture default may break the ABI and cause the program to malfunction.

???+ warning "Note"
    Unlike other integer types, `char`, `signed char`, and `unsigned char` are **three distinct types**.
    
    In general, `signed char` and `unsigned char` should not be used to store characters. In most cases, these two types are treated as integer types.

### Floating-Point Types

Floating-point types are used to store "real numbers". Note that these are not real numbers in the strict mathematical sense, but approximations of real numbers under certain rules. They include the following three types:

-   `float`: single-precision floating-point type. If supported, it matches the IEEE-754 binary32 format.
-   `double`: double-precision floating-point type. If supported, it matches the IEEE-754 binary64 format.
-   `long double`: extended-precision floating-point type. If supported, it matches the IEEE-754 binary128 format; otherwise, if supported, it matches the IEEE-754 binary64 extended format; otherwise, it matches some non-IEEE-754 extended floating-point format with better precision than binary64 and at least as good a value range as binary64; otherwise, it matches the IEEE-754 binary64 format.

| Floating-point format           | Width     | Maximum positive value         | Precision digits |
| ------------------------------- | --------- | ------------------------------ | ---------------- |
| IEEE-754 binary32 format        | $32$      | $3.4\times 10^{38}$           | $6\sim 9$       |
| IEEE-754 binary64 format        | $64$      | $1.8\times 10^{308}$          | $15\sim 17$     |
| IEEE-754 binary64 extended form | $\geq 80$ | $\geq 1.2\times 10^{4932}$   | $\geq 18\sim 21$ |
| IEEE-754 binary128 format       | $128$     | $1.2\times 10^{4932}$         | $33\sim 36$     |

> The smallest negative number in an IEEE-754 floating-point format is the opposite of the largest positive number.

Because `float` has a relatively small range and low precision, `double` is commonly used for floating-point numbers in practice.

In addition, floating-point types can support some special values:

-   Infinity, positive or negative: `INFINITY`.
-   Negative zero: `-0.0`, for example `1.0 / 0.0 == INFINITY`,`1.0 / -0.0 == -INFINITY`.
-   Not-a-number (NaN): `std::nan`,`NAN`, usually produced by operations such as `0.0 / 0.0`. It compares unequal to any value, including itself. Since C++11, `std::isnan` can be used to test whether a floating-point number is NaN.

### No Type

The `void` type means no type. Unlike the types above, a variable cannot be declared as type `void`. However, a function may have return type `void`, meaning that the function returns no value.

### Null Pointer Type

See the [corresponding section](./pointer.md#null-pointers) on pointers.

## Fixed-Width Integer Types

Since C++11, fixed-width integer support is provided as follows:

-   `<cstdint>`: provides several fixed-width integer types and macro constants for their maximum values, minimum values, and so on.
-   `<cinttypes>`: provides format macro constants for fixed-width integer types used by the `std::fprintf` and `std::fscanf` family of functions.

There are several kinds of fixed-width integers:

-   `intN_t`: a signed integer type whose width is **exactly** $N$ bits, such as `int32_t`.
-   `int_fastN_t`: the **fastest** signed integer type with width **at least** $N$ bits, such as `int_fast32_t`.
-   `int_leastN_t`: the **smallest** signed integer type with width **at least** $N$ bits, such as `int_least32_t`.

For unsigned versions, just add the letter u before the signed version, such as `uint32_t`,`uint_least8_t`.

The standard requires the following 16 types to be implemented:

`int_fast8_t`,`int_fast16_t`,`int_fast32_t`,`int_fast64_t`,

`int_least8_t`,`int_least16_t`,`int_least32_t`,`int_least64_t`,

`uint_fast8_t`,`uint_fast16_t`,`uint_fast32_t`,`uint_fast64_t`,

`uint_least8_t`,`uint_least16_t`,`uint_least32_t`,`uint_least64_t`.

Most compilers also implement the following 8 types on this basis:

`int8_t`,`int16_t`,`int32_t`,`int64_t`,

`uint8_t`,`uint16_t`,`uint32_t`,`uint64_t`.

When the corresponding type is implemented, the C++ standard requires macro constants representing its maximum value, minimum value, and bit width. Their names are formed by removing the trailing `_t` from the type name, converting it to uppercase, and adding a suffix:

-   `_MAX` indicates the maximum value, such as `INT32_MAX` for the maximum value of `int32_t`.
-   `_MIN` indicates the minimum value, such as `INT32_MIN` for the minimum value of `int32_t`.

???+ warning "Note"
    Fixed-width integer types are essentially type aliases of ordinary integer types, so mixing fixed-width integer types and ordinary integer types may affect cross-platform compilation. For example:
    
    ???+ note "Example code"
        ```cpp
        #include <algorithm>
        #include <cstdint>
        #include <iostream>
        
        int main() {
          long long a;
          int64_t b;
          std::cin >> a >> b;
          std::cout << std::max(a, b) << std::endl;
          return 0;
        }
        ```
    
    On 64-bit Windows, `int64_t` is usually `long long int`, while on 64-bit Linux it is usually `long int`. Therefore, this code cannot compile with GCC on 64-bit Linux, but can compile with MSVC on 64-bit Windows, because `std::max` requires its two input parameters to have the same type.

In addition, since C++17, `<limits>` provides the `std::numeric_limits` class template for querying properties of various arithmetic types, such as maximum value, minimum value, whether the type is integer, and whether it is signed.

```cpp
#include <cstdint>
#include <limits>

std::numeric_limits<int32_t>::max();  // maximum value of int32_t, 2'147'483'647
std::numeric_limits<int32_t>::min();  // minimum value of int32_t, -2'147'483'648

std::numeric_limits<double>::min();  // minimum value of double, about 2.22507e-308
std::numeric_limits<double>::epsilon();  // difference between 1.0 and the next representable double,
                                         // about 2.22045e-16
```

## Type Conversions

Sometimes, for example when a function accepts an `int` parameter but a `double` variable is passed in, we need to convert one type into another.

C++ has a relatively complex type conversion mechanism. This section mainly introduces two conversions for fundamental data types: numeric promotion and numeric conversion.

### Numeric Promotion

During numeric promotion, the value itself remains unchanged.

???+ note "Note"
    C-style variadic argument lists perform default argument promotion when values are passed. For example:
    
    ???+ note "Example code"
        ```c
        #include <stdarg.h>
        #include <stdio.h>
        
        void test(int tot, ...) {
          va_list valist;
          int i;
        
          // Initialize the variadic argument list
          va_start(valist, tot);
        
          for (i = 0; i < tot; ++i) {
            // Get the value of the i-th variable
            double xx = va_arg(valist, double);  // Correct
            // float xx = va_arg(valist, float); // Wrong
        
            // Output the underlying storage contents of the i-th variable
            printf("i = %d, value = 0x%016llx\n", i, *(long long *)(&xx));
          }
        
          // Clean up the memory for the variadic argument list
          va_end(valist);
        }
        
        int main() {
          float f;
          double fd, d;
          f = 123.;   // 0x42f60000
          fd = 123.;  // 0x405ec00000000000
          d = 456.;   // 0x407c800000000000
          test(3, f, fd, d);
        }
        ```
    
    When calling `test`, `f` is promoted to `double`, so its underlying storage is the same as `fd`. The output is:
    
    ```text
    i = 0, value = 0x405ec00000000000
    i = 1, value = 0x405ec00000000000
    i = 2, value = 0x407c800000000000
    ```
    
    If `double xx = va_arg(valist, double);` is changed to `float xx = va_arg(valist, float);`, GCC should give a warning similar to the following:
    
    ```text
    In file included from test.c:2:
    test.c: In function 'test':
    test.c:14:35: warning: 'float' is promoted to 'double' when passed through '...'
      14 |         float xx = va_arg(valist, float);
         |                                   ^
    test.c:14:35: note: (so you should pass 'double' not 'float' to 'va_arg')
    test.c:14:35: note: if this code is reached, the program will abort
    ```
    
    At this point, the program will terminate before producing output.
    
    This also explains why `%f` in `printf` can match both `float` and `double`.

#### Integer Promotion

Prvalues of small integer types, such as `char`, can be converted to prvalues of larger integer types, such as `int`.

Specifically, arithmetic operators do not accept types smaller than `int` as their arguments. After lvalue-to-rvalue conversion, integer promotion is automatically performed if applicable.

The rules are as follows:

-   If the source type is `signed char`, `signed short`, or `short`, it can be promoted to `int`.
-   If the source type is `unsigned char` or `unsigned short`, and `int` can represent all values of the source type, it can be promoted to `int`; otherwise it can be promoted to `unsigned int`. Since `C++20`, `char8_t` also follows this rule.
-   The promotion rule for `char` depends on whether its underlying type is `signed char` or `unsigned char`.
-   `bool` can be converted to `int`: `false` becomes `0`, and `true` becomes `1`.
-   If the destination type's value range contains the source type's value range, and the source type's value range cannot be contained by `int` or `unsigned int`, the source type can be promoted to the destination type.[^note12]

???+ warning "Note"
    `char`->`short` is not numeric promotion, because `char` is first promoted to `int / unsigned int`, followed by `int / unsigned int`->`short`, which does not satisfy the conditions of numeric promotion.

For example, assuming `int` is 32 bits, `unsigned short` is 16 bits, `signed char` and `unsigned char` are 8 bits, and `bool` is 1 bit:

-   `(signed char)'\0' - (signed char)'\xff'` first promotes `(signed char)'\0'` to `(int)0` and `(signed char)'\xff'` to `(int)-1`, then performs the operation between `int`s, producing `(int)1`.
-   `(unsigned char)'\0' - (unsigned char)'\xff'` first promotes `(unsigned char)'\0'` to `(int)0` and `(unsigned char)'\xff'` to `(int)255`, then performs the operation between `int`s, producing `(int)-255`.
-   `false - (unsigned short)12` first promotes `false` to `(int)0` and `(unsigned short)12` to `(int)12`, then performs the operation between `int`s, producing `(int)-12`.

#### Floating-Point Promotion

A floating-point number with a smaller width can be promoted to a floating-point number with a larger width. For example, when a `float` variable and a `double` variable participate in arithmetic, the `float` variable is promoted to `double`. The value remains unchanged.

### Numeric Conversion

During numeric conversion, the value may change.

???+ warning "Note"
    Numeric promotion takes precedence over numeric conversion. For example, `bool`->`int` is numeric promotion rather than numeric conversion.

#### Integer Conversion

<!-- scripts.linter.preprocess.fix_details off -->

-   If the destination type is an unsigned integer type with bit width $x$, the conversion result is the original value modulo $2^x$.

    -   If the destination type has a greater width than the source type:

        -   If the source type is signed, sign extension is generally performed before conversion.

            For example:

            -   When converting `(short)-1` (`(short)0b1111'1111'1111'1111`) to `unsigned int`, sign extension is performed first, yielding `0b1111'1111'1111'1111'1111'1111'1111'1111`, then integer conversion is performed, producing `(unsigned int)4'294'967'295` (`(unsigned int)0b1111'1111'1111'1111'1111'1111'1111'1111`).
            -   When converting `(short)32'767` (`(short)0b0111'1111'1111'1111`) to `unsigned int`, sign extension is performed first, yielding `0b0000'0000'0000'0000'0111'1111'1111'1111`, then integer conversion is performed, producing `(unsigned int)32'767` (`(unsigned int)0b0000'0000'0000'0000'0111'1111'1111'1111`).

        -   If the source type is unsigned, zero extension is performed before conversion.

            For example, when converting `(unsigned short)65'535` (`(unsigned short)0b1111'1111'1111'1111`) to `unsigned int`, zero extension is performed first, yielding `0b0000'0000'0000'0000'1111'1111'1111'1111`, then integer conversion is performed, producing `(unsigned int)65'535` (`(unsigned int)0b0000'0000'0000'0000'1111'1111'1111'1111`).

    -   If the destination type's width is not greater than the source type's width, truncation is performed before conversion.

        For example, when converting `(unsigned int)4'294'967'295` (`(unsigned int)0b1111'1111'1111'1111'1111'1111'1111'1111`) to `unsigned short`, truncation is performed first, yielding `0b1111'1111'1111'1111`, then integer conversion is performed, producing `(unsigned short)65'535` (`(unsigned short)0b1111'1111'1111'1111`).

-   If the destination type is a signed integer type with bit width $x$, then **in general**, the conversion result can be regarded as the original value modulo $2^x$.[^note13]

    For example, when converting `(unsigned int)4'294'967'295` (`(unsigned int)0b1111'1111'1111'1111'1111'1111'1111'1111`) to `short`, the result is `(short)-1` (`(short)0b1111'1111'1111'1111`).

-   If the destination type is `bool`, this is a [Boolean conversion](#boolean-conversion).

-   If the source type is `bool`, `false` is converted to 0 of the corresponding type, and `true` is converted to 1 of the corresponding type.

<!-- scripts.linter.preprocess.fix_details on -->

#### Floating-Point Conversion

When a floating-point number with a larger width is converted to a floating-point number with a smaller width, it is rounded to the nearest value representable by the destination type.

#### Floating-Point-Integer Conversion

-   When a floating-point number is converted to an integer, all fractional parts of the floating-point number are discarded.

    If the destination type is `bool`, this is a [Boolean conversion](#boolean-conversion).

-   When an integer is converted to a floating-point number, it is rounded to the nearest value representable by the destination type.

    If the value cannot fit in the destination type, the behavior is undefined.

    If the source type is `bool`, `false` is converted to zero, and `true` is converted to one.

#### Boolean Conversion

When other types are converted to `bool`, zero values are converted to `false`, and nonzero values are converted to `true`.

## Defining Variables

Simply put[^note14], defining a variable requires a type specifier, which indicates the variable's type, and the name of the variable to be defined.

For example, each of the following statements defines a variable:

```cpp
int oi;
double wiki;
char org = 'c';
```

In the program fragments we have seen so far, variables defined inside braces are local variables, while variables defined outside any braces are global variables. There are exceptions in practice, but they are not necessary to understand now.

Global variables that are not initialized at definition are initialized to $0$. Local variables do not have this property and need to be initialized manually, otherwise hard-to-find bugs may occur.

## Variable Scope

A scope is the code block in which a variable can take effect.

The scope of a global variable starts at its definition[^note15] and continues to the end of the file.

The scope of a local variable starts at its definition and continues to the end of its code block.

A code block consists of several statements enclosed by a pair of braces.

```cpp
int g = 20;  // define a global variable

int main() {
  int g = 10;         // define a local variable
  printf("%d\n", g);  // output g
  return 0;
}
```

If a variable with the same name is defined in a nested block, the inner block cannot access the variable with the same name in the outer block.

In the code above, for example, the output value of $g$ is $10$. Therefore, to avoid unexpected errors, try not to use the same name for local and global variables.

## Constants

A constant is a fixed value that does not change during program execution.

The value of a constant cannot be modified after it is defined. Add the `const` keyword when defining it.

```cpp
const int a = 2;
a = 3;
```

If you modify the value of a constant, compilation reports an error: `error: assignment of read-only variable 'a'`.

## References and Notes

1.  [Working Draft, Standard for Programming Language C++](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/n4917.pdf)
2.  [Types - cppreference.com](https://en.cppreference.com/w/cpp/language/type)
3.  C language [Arithmetic types - cppreference.com](https://en.cppreference.com/w/c/language/arithmetic_types)
4.  [Fundamental types - cppreference.com](https://en.cppreference.com/w/cpp/language/types)
5.  [Fixed-width integer types (since C++11) - cppreference.com](https://en.cppreference.com/w/cpp/types/integer)
6.  William Kahan (1 October 1997). ["Lecture Notes on the Status of IEEE Standard 754 for Binary Floating-Point Arithmetic"](https://people.eecs.berkeley.edu/~wkahan/ieee754status/IEEE754.PDF).
7.  [Implicit conversions - cppreference.com](https://en.cppreference.com/w/cpp/language/implicit_conversion)
8.  [Declarations - cppreference](https://en.cppreference.com/w/cpp/language/declarations)
9.  [Scope - cppreference.com](https://en.cppreference.com/w/cpp/language/scope)

[^note10]: See <https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3054.pdf>.

[^note11]: Includes array types, reference types, pointer types, class types, function types, and so on. Since this article is intended for beginners, they are not introduced in detail here. See [Types - cppreference.com](https://en.cppreference.com/w/cpp/language/type) for details.

[^note12]: This does not include wide character types, bit-fields, or enumeration types. See [Integral conversions - cppreference](https://en.cppreference.com/w/cpp/language/implicit_conversion#Integral_conversions) for details.

[^note13]: This applies since C++20. Before C++20, the result was implementation-defined. See [Integral conversions - cppreference](https://en.cppreference.com/w/cpp/language/implicit_conversion#Integral_conversions) for details.

[^note14]: When defining a variable, other specifiers may be included in addition to the type specifier. See [Declarations - cppreference](https://en.cppreference.com/w/cpp/language/declarations) for details.

[^note15]: More precisely, the [point of declaration](https://en.cppreference.com/w/cpp/language/scope#Point_of_declaration).

[^note16]: Before C++20, signed integers were required to cover at least the representable range of [ones' complement](../math/bit.md#integers-and-bit-sequences), namely $-2^{x-1}+1\sim 2^{x-1}-1$, but in practice most implementations used [two's complement](../math/bit.md#integers-and-bit-sequences). Since C++20, signed integers are further required to use two's complement. See [Range of values - cppreference](https://en.cppreference.com/w/cpp/language/types.html#Range_of_values) for details.
