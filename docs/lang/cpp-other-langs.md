This article introduces the differences between C++ and other commonly used languages, focusing on important or easily overlooked differences between C and C++. Although C++ is almost a superset of C, and mixing C/C++ code is usually not a problem, understanding the more important differences between C and C++ can help avoid strange bugs. If C is your main language as an OIer, this article can also help you get started with C++ more smoothly. For features unique to C++ compared with C, read the tutorials in [Advanced C++](./class.md). This article also briefly introduces the differences between Python, Java, and C++.

## Differences Between C and C++

### Macros and Templates

One original purpose of C++ templates was to replace macro definitions. Learning template programming is an important step from C to C++. Unlike textual substitution by macros, templates receive more comprehensive compiler checks at compile time, making it easier to write more robust code. Since C++11, templates have supported variadic template parameter lists, which can replace variadic functions in C while ensuring type safety.

### Pointers and References

In C++, you can still use C-style pointers, but for passing variables, it is more recommended to use C++ [references](./reference.md) to implement similar functionality. Since the object referred to by a reference cannot be null, references can avoid some null-address access problems. However, pointers are still useful because of their flexibility. It is worth mentioning that since C++11, the `NULL` null pointer in C has a type-safe alternative: `nullptr`. References and pointers can be converted to each other through the [`*` and `&` operators](./op.md).

### bool

See also [Boolean type](var.md#布尔类型).

Unlike C++, the C language originally did not have a Boolean type.

The C99 standard added the `_Bool` keyword, the equivalent `bool` macro, and the two macros `true` and `false`. If you need to use the three macros `bool`, `true`, and `false`, include the `stdbool.h` header in the program. Using `_Bool` does not require any additional header.

```c
bool x = true;  // Requires stdbool.h
_Bool x = 1;    // Does not require stdbool.h
```

Starting from C23, `true`, `false`, and `bool` became keywords in C, and using them no longer requires including `stdbool.h`. `_Bool` is retained as an alternative spelling of `bool`[^boolean-keyword].

The following table shows how support for the `bool` type changed across different C standards, with C++ support included for comparison:

| Language standard | `bool` | `true`/`false` | `_Bool` |
| ------------ | --------------------------------- | ----------------------------------------------------- | ------------------------- |
| C89 | / | / | Reserved[^reserved-identifiers] |
| C99 onward, before C23 | Macro, equivalent to `_Bool`, requires the `stdbool.h` header | Macros; `true` is equivalent to `1`, `false` is equivalent to `0`, requires the `stdbool.h` header | Keyword |
| C23 onward | Keyword | Keyword | Alternative spelling of the keyword `bool` |
| C++ | Keyword | Keyword | Reserved[^reserved-identifiers] |

### struct

Although both C and C++ have the concept of `struct`, what they represent cannot be mixed freely. A `struct` in C describes a fixed memory layout, while a `struct` in C++ is a kind of class. **The only difference from a class is that its members and inheritance are public by default**, while ordinary class members are private by default. This is especially dangerous when writing mixed C/C++ code.

Also, declaring a `struct` in C++ does not need to be as verbose as in C. C version:

```c
typedef struct Node_t {
  struct Node_t *next;
  int key;
} Node;
```

C++ version:

```cpp
struct Node {
  Node *next;
  int key;
};
```

### const

In C, `const` only restricts variables from being modified. In C++, because of many new features, `const` has been given more uses. The successor to C's `const` in C++ is `constexpr`; for C++ uses of `const`, see [constants](./const.md).

### Memory Allocation

C++ adds the `new` and `delete` keywords to allocate space in the "free store". This free store may be the heap or static storage, and these keywords were introduced to work with classes. `delete[]` can directly release the memory of a dynamic array, which is very convenient. The `new` and `delete` keywords call the type's constructor and destructor. Compared with C's `malloc()`, `realloc()`, and `free()`, they provide more complete support for types, but are less efficient than those C functions.

In short, if the objects for which you need dynamic memory allocation are basic types or arrays of basic types, you can use `malloc()` for more efficient memory allocation. But if the object you create is a non-basic type, it is recommended to use `new` for safety checks. Note that although both `new` and `malloc()` return pointers, pointers returned by `new` **must** be released with `delete`, while pointers returned by `malloc()` **must** be released with `free()`. Otherwise, there is a risk of memory leaks.

### Variable Declarations

Before C99, variable declarations in C had to appear at the beginning of a block. C++ and C99 onward do not have this restriction.

### Variable-Length Arrays

Since C99, C supports VLAs (variable-length arrays). C++ has never supported them.

### Struct Initialization

Since C99, C supports [designated initialization](https://en.cppreference.com/w/c/language/struct_initialization) of structs, although it is optional in C11. C++ did not support ordered designated initialization until C++20, and C++ does not support the C features of out-of-order designated initialization, nested designated initialization, mixing with ordinary initializers, or designated initialization for arrays[^cpp-designated-init].

### Comment Syntax

C++-style single-line comments `//` were not supported by C before C99.

## Differences Between Python and C++

Python is currently the most commonly used language in machine learning. Compared with C++, Python's advantages are that it is easy to learn and easy to practice. Python has simpler and more direct syntax; for example, when defining variables, you do not need to declare variable types in advance. However, this simplicity comes at a cost: Python sacrifices performance compared with C++. C++ is suitable for almost all platforms, including embedded systems, and has faster execution speed, while Python can only be used on platforms that support high-level languages. C++ is closer to the underlying system, so it can be used to write operating systems.

## Differences Between Java and C++

Java and C++ are both object-oriented languages and both use object-oriented ideas such as encapsulation, inheritance, and polymorphism. Because object-oriented programming has many useful features, such as inheritance and composition, both languages have good reusability. Therefore, compared with Python, Java is more similar to C++.

The biggest difference between them is that Java has the JVM mechanism. JVM stands for Java Virtual Machine. A very important feature of Java is platform independence, and the Java Virtual Machine is the key to achieving this feature. In general, if a high-level language needs to run on different platforms, it must at least be compiled into different object code. After introducing the Java Virtual Machine, Java programs do not need to be recompiled when running on different platforms. Java uses the Java Virtual Machine to hide platform-specific information, so the Java compiler only needs to generate object code (bytecode) that runs on the Java Virtual Machine, and the program can run on multiple platforms without modification.

Because of this feature, Java is often used to develop programs that need to be ported to different platforms. However, because Java programs start from bytecode during execution, Java's performance is not as good as C++.

## References

[^cpp-designated-init]: <https://en.cppreference.com/w/cpp/language/aggregate_initialization>

[^boolean-keyword]: <https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3054.pdf>.

[^reserved-identifiers]: Both C and C++ specify that identifiers beginning with an underscore followed by an uppercase letter are reserved. See <https://en.cppreference.com/w/c/language/identifier>.
