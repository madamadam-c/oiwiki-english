author: tsagaanbar, Enter-tainer, Xeonacid

## Variable Addresses and Pointers

In a program, all of our data has an address where it is stored. During each actual run of a program, variables may be stored at different locations in physical memory. However, when programming, we can still obtain the address of data in memory with certain statements.

An address is also data. The variable type used to store addresses has a special name: a "pointer variable", often shortened to "pointer".

???+ note "Size of pointer variables"
    The size of a pointer variable differs across environments. On a 32-bit machine, addresses are represented by 32-bit binary integers, so a pointer is 4 bytes. On a 64-bit machine, addresses are represented by 64-bit binary integers, so a pointer is 8 bytes.

An address is just a scale-like piece of data. To target different types of data, "pointer variables" also have different types. For example, an `int` pointer variable stores an address (that is, the numeric value stored by the pointer variable) corresponding to the starting address of a 32-bit block of space; a `char` pointer variable stores an address corresponding to the starting address of an 8-bit block of space.

In fact, users can also declare pointer variables that point to pointer variables.

Suppose the user defines a structure:

```cpp
struct ThreeInt {
  int a;
  int b;
  int c;
};
```

Then a pointer variable of type `ThreeInt` corresponds to a block of space of size 3 × 32 = 96 bits.

## Declaring and Using Pointers

In C/C++, the type of a pointer variable is the type name followed by an asterisk `*`. For example, the type name of an `int` pointer variable is `int*`.

We can use the `&` symbol to obtain the address of a variable.

To access the space corresponding to the address stored in a pointer variable (also called the space the pointer **points to**), we need to **dereference** the pointer variable using the `*` symbol.

```cpp
int main() {
  int a = 123;  // a: 123
  int* pa = &a;
  *pa = 321;  // a: 321
}
```

The same applies to structure variables. To access a member of a structure pointed to by a pointer, first dereference the pointer and then use the `.` member access operator. However, the simpler arrow operator `->` is more recommended.

```cpp
struct ThreeInt {
  int a;
  int b;
  int c;
};

int main() {
  ThreeInt x{1, 2, 3}, y{6, 7, 8};
  ThreeInt* px = &x;
  (*px) = y;    // x: {6,7,8}
  (*px).a = 4;  // x: {4,7,8}
  px->b = 5;    // x: {4,5,8}
}
```

## Pointer Offsets

Pointer variables can also be added to and subtracted from **integers**. For an `int` pointer, adding 1 (incrementing by 1) offsets the address it points to by 32 bits (that is, 4 bytes). Adding 2 offsets the address by 2 × 32 = 64 bits. Similarly, for a `char` pointer, each increment offsets the address it points to by 8 bits (that is, 1 byte).

### Accessing Arrays with Pointer Offsets

As mentioned earlier, an array is a contiguous block of storage. In C/C++, directly using an array name gives the starting address of the array.

```cpp
int main() {
  int a[3] = {1, 2, 3};
  int* p = a;  // p points to a[0]
  *p = 4;      // a: [4, 2, 3]
  p = p + 1;   // p points to a[1]
  *p = 5;      // a: [4, 5, 3]
  p++;         // p points to a[2]
  *p = 6;      // a: [4, 5, 6]
}
```

When accessing elements in an array through a pointer, "pointer offset" is often used. In other words, an element is accessed by adding an offset to a base address (the starting address of the array).

We commonly use the `[]` operator to access the element at a specified offset in an array, such as `a[3]` or `p[4]`. This notation is equivalent to doing pointer arithmetic and then dereferencing; `p[4]` and `*(p + 4)` are equivalent.

## Null Pointers

Before C++11, C++ used the `NULL` macro as the null pointer constant, just like C. In C++, `NULL` was generally implemented as follows:

```cpp
// Before C++11
#define NULL 0
```

???+ note "The definition of `NULL` in C"
    Before C23, C had two definitions of `NULL`, differing only in type: one was an integer constant expression, and the other was a constant expression converted to `void *`. Both had value 0, and the compiler could choose either implementation.

Mixing null pointers and the integer `0` causes many problems in C++, for example:

```cpp
int f(int x);
int f(int* p);
```

When calling `f(NULL)`, the function actually called has type `int(int)`, not `int(int *)`.

???+ note "Problems caused by `NULL` in C"
    Compared with C++, `NULL` causes even more serious problems in C because of the two definitions: if a function with variable arguments expects a pointer, but the caller passes a `NULL` defined as an integer, undefined behavior occurs. This is because the variadic argument must be type-converted inside the function, and converting from an integer type to a pointer type is undefined behavior.[^note1]

To solve these problems, C++11 introduced the `nullptr` keyword as the null pointer constant.

C++ specifies that `nullptr` can be implicitly converted to any pointer type, and the result of this conversion is the null pointer value of that type.

The type of `nullptr` is `std::nullptr_t`, called the null pointer type. A possible implementation is:

```cpp
namespace std {
typedef decltype(nullptr) nullptr_t;
}
```

In addition, since C++11, the implementation of the `NULL` macro has also been changed to:

```cpp
// Since C++11
#define NULL nullptr
```

???+ note "Improvements to null pointer constants in C"
    For similar reasons, C23 also introduced `nullptr` as a null pointer constant and introduced `nullptr_t` as its type.[^note1]

## Advanced Uses of Pointers

Pointers allow programmers to manipulate data throughout a running program without being limited to scope.

### Using Pointer-Type Parameters

In C/C++, parameters used when calling a function (procedure) are passed into the subroutine by copy (except references, which will be introduced later). By default, a function can only return results to the call site through its return value. However, if a function wants to modify data outside itself, or if a structure/class contains a large amount of data and is not suitable for copying, the address of the external data can be passed in so that the function can access or even modify that external data.

The following `my_swap` method receives two `int` pointers and uses a temporary variable inside the function to swap the values of two `int` variables.

```cpp
void my_swap(int *a, int *b) {
  int t;
  t = *a;
  *a = *b;
  *b = t;
}

int main() {
  int a = 6, b = 10;
  my_swap(&a, &b);
  // After the call, a in main becomes 10, and b becomes 6
}
```

C++ introduced the concept of references, which are easier to use and safer than pointers. For details, see [C++: References](./reference.md) and [Differences between C and C++: pointers and references](./cpp-other-langs.md#指针与引用).

### Dynamic Instantiation

In addition, programs often involve dynamic memory allocation: at runtime, a program dynamically requests or returns memory needed to store data from the operating system. When a program calls an operating system interface to request memory, the operating system returns the address of the requested space. To use this space, we need to store its address in a pointer variable.

In C++, we use the `new` operator to obtain a block of memory, and the `delete` operator to release the space pointed to by a pointer.

```cpp
int* p = new int(1234);
/* ... */
delete p;
```

The statement above uses the `new` operator to request an `int`-sized block of space from the operating system, initializes its value to 1234, and declares an `int` pointer `p` pointing to this space.

Similarly, `new` can also be used to allocate new objects:

```cpp
class A {
  int a;

 public:
  A(int a_) : a(a_) {}
};

int main() {
  A* p = new A(1234);
  /* ... */
  delete p;
}
```

As above, a "`new` expression" attempts to allocate a block of space of the corresponding size, construct the object in that space, and return the address of the space.

```cpp
struct ThreeInt {
  int a;
  int b;
  int c;
};

int main() {
  ThreeInt* p = new ThreeInt{1, 2, 3};
  /* ... */
  delete p;
}
```

???+ note "List initialization"
    The `{}` operator can be used to initialize structures without constructors. In addition, using `{}` can unify the initialization form of variables. See [list initialization (since C++11)](https://en.cppreference.com/w/cpp/language/list_initialization) for details.

Note that when memory allocated with `new` is no longer used, `delete` must be used to release it. A block of memory must not be released twice or more. Using `delete` on a null pointer `nullptr` is legal.

### Dynamically Creating Arrays

The `new[]` operator can also be used to create arrays. In this case, `new[]` returns the first address of the array, that is, the address of the first element. We can store this address in a pointer of the corresponding type. When releasing it, use the `delete[]` operator.

```cpp
size_t element_cnt = 5;
int *p = new int[element_cnt];
delete[] p;
```

The elements in an array are stored contiguously, so `p + 1` points to the successor element of `p`.

### Two-Dimensional Arrays

When storing matrix-shaped data, a data type such as a "two-dimensional array" may be used. Semantically, a two-dimensional array is an array of arrays. Computer memory can be viewed as a very long one-dimensional array. When storing a two-dimensional array in computer memory, whether it is "contiguous" matters.

"Contiguous" means that the end of any row of the two-dimensional array and the beginning of the next row are adjacent in physical address. In other words, the entire two-dimensional array can be viewed as a one-dimensional array. Otherwise, they are not necessarily physically adjacent.

For a "contiguous" two-dimensional array, all data in the array can be traversed with just one loop by using a continuously incrementing pointer. For a non-contiguous two-dimensional array, since each row is not contiguous with the next, we must first obtain the address of the beginning of a row and then access the elements in that row.

???+ note "Storage methods for two-dimensional arrays"
    This method of storing data by "row" is called row-major storage. Conversely, data can also be stored by column. Due to the characteristics of computer memory access, accessing contiguous data is generally more efficient. Therefore, choose row-major or column-major storage according to how the data may be used.

### Dynamically Creating Two-Dimensional Arrays

In C/C++, we can use a statement like the following to declare a two-dimensional array with N rows and M columns. Its space is physically contiguous.

???+ note "Describing array dimensions"
    A more general way is to use the term nth dimension. For row-major storage, the length of the first dimension of the array is N, and the length of the second dimension is M.

```cpp
int a[N][M];
```

This declaration requires N and M to be constant expressions that can be determined at compile time.

In C/C++, the subscript of the first element of an array is 0. Therefore, an expression such as `a[r][c]` represents the element in row r + 1 and column c + 1 of the two-dimensional array `a`; we also call the subscript of this element `(r,c)`.

In practice, however, the size of a (two-dimensional) array may not be fixed and may require dynamic memory allocation.

A common method is to declare a **one-dimensional array** of length N × M and access the element with subscript `(r, c)` in the two-dimensional array using the subscript `r * M + c`.

```cpp
int* a = new int[N * M];
```

This method guarantees that the two-dimensional array is **contiguous**.

???+ note "Linear storage of arrays at the physical level"
    In fact, data in memory can all be viewed as linearly stored. Therefore, under certain rules, dynamically allocating the space of a one-dimensional array is enough to store an n-dimensional array on it.

In addition, memory can also be obtained and used according to the concept of an "array of arrays". An array storing several arrays is actually an array storing the first addresses of several arrays, that is, an array storing several pointer variables.

We need a variable to store the first address of this "array of arrays", that is, the address of a pointer. This variable is a "pointer to a pointer", sometimes called a "double pointer", such as:

```cpp
int** a = new int*[5];
```

Next, we need to allocate space for each array:

```cpp
for (int i = 0; i < 5; i++) {
  a[i] = new int[5];
}
```

At this point, memory allocation is complete. To release memory obtained this way, perform the reverse operation: first release each array, then release the array that stores the first addresses of those arrays, for example:

```cpp
for (int i = 0; i < 5; i++) {
  delete[] a[i];
}
delete[] a;
```

Note that a two-dimensional array obtained this way is not guaranteed to be contiguous.

There is another method that uses a "pointer to an array".

???+ note "Difference between an array name and the address of the first array element"
    We mentioned earlier that in C/C++, directly using an array name gives a value equal to the address of the first element of the array. However, the type of the variable represented by the array name is actually the entire array, not a single element.
    
    ```cpp
    int main() { int a[5] = {1, 2, 3, 4, 5}; }
    ```
    
    Conceptually, the type of identifier `a` in the code is `int[5]`; in practice, the address pointed to by `a + 1` is offset from the address pointed to by `a` by the length of 5 `int` variables.

```cpp
int main() {
  int(*a)[5] = new int[5][5];
  int* p = a[2];
  a[2][1] = 1;
  delete[] a;
}
```

This method also obtains contiguous memory, but it can directly obtain the first address of the n + 1-th row with the form `a[n]`. Therefore, elements with subscript `(r, c)` can be accessed using `a[r][c]`.

Because a pointer to an array is also a definite data type, the lengths of all dimensions except the first dimension of the array must be constants that can be determined by the compiler. Otherwise, the compiler cannot translate expressions such as `a[n]` where `a` is a pointer to an array.

## Pointers to Functions

For an introduction to functions, see [C++ Functions](./func.md).

Simply put, to call a function, you need to know its parameter types, number of parameters, and return type. These are collectively called the interface type.

Functions can be called through function pointers. Sometimes several functions have the same interface type. Function pointers allow the program to choose which function to call **dynamically** at runtime. In other words, without modifying a function, we can change its behavior only by modifying the argument passed to it (a function pointer).

Suppose we have several binary operation functions for the `int` type. The functions take two `int` parameters and also return `int`. Below is an example using a function pointer:

```cpp
#include <iostream>

int (*binary_int_op)(int, int);

int foo1(int a, int b) { return a * b + b; }

int foo2(int a, int b) { return (a + b) * b; }

int main() {
  int choice;
  std::cin >> choice;
  if (choice == 1) {
    binary_int_op = foo1;
  } else {
    binary_int_op = foo2;
  }

  int m, n;
  std::cin >> m >> n;
  std::cout << binary_int_op(m, n);
}
```

???+ note "`&`, `*`, and function pointers"
    In C, forms such as `void (*p)() = foo;`, `void (*p)() = &foo;`, `void (*p)() = *foo;`, and `void (*p)() = ***foo` all have the same result.
    
    Because a function (such as `foo`) can be implicitly converted to a pointer to that function, the form `void (*p)() = foo;` is valid.
    
    The `&` operator obtains the address of an object, and this also works for functions, so `void (*p)() = &foo;` is still valid.
    
    Applying the `*` operator to a function pointer obtains the function it points to. For a form such as `**foo`, `*foo` obtains the function `foo`, which is then immediately implicitly converted to a pointer to `foo`. By the same reasoning, the final result of `**foo` is still a function pointer pointing to `foo`; users may use any number of `*` operators and the result is the same.
    
    Similarly, when calling, statements such as `(*p)()` and `p()` are the same, so the `*` operator can be omitted.
    
    Reference: [Why do function pointer definitions work with any number of ampersands '&' or asterisks '\*'? - stackoverflow.com](https://stackoverflow.com/questions/6893285/why-do-function-pointer-definitions-work-with-any-number-of-ampersands-or-as)

The `typedef` keyword can be used to declare a function pointer type.

```cpp
typedef int (*p_bi_int_op)(int, int);
```

Then we can use `p_bi_int_op` as a type later, meaning a pointer to a function whose parameters are two `int`s and whose return value is also `int`.

Functions can be referenced more conveniently with `std::function`. (To be continued)

Function pointers can be used to implement "callback functions". (To be continued)

## References and Notes

[^note1]: See [Introduce the nullptr constant](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3042.htm)
