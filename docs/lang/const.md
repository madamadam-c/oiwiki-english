C++ defines a complete set of ways to define read-only values. Variables modified by `const` are read-only values. The compiler checks for conflicts at compile time to prevent modifications to read-only values, and it may also perform some optimizations.

In general, use `const` to modify variables and parameters whenever possible to improve code robustness.

## The `const` Type Qualifier

### Constants

A variable modified by `const` cannot have its value changed after initialization.

```cpp
const int a = 0;  // The type of a is const int

// a = 1; // Cannot modify a constant
```

### References to Const and Pointers to Const

References to const and pointers to const both restrict modification of the pointed-to value.

```cpp
int a = 0;
const int b = 0;

int *p1 = &a;
*p1 = 1;
const int *p2 = &a;
// *p2 = 2; // Cannot modify a variable through a pointer to const
// int *p3 = &b; // Cannot point an int* to a const int variable
const int *p4 = &b;

int &r1 = a;
r1 = 1;
const int &r2 = a;
// r2 = 2; // Cannot modify a variable through a reference to const
// int &p3 = b; // Cannot bind an int& to a const int variable
const int &r4 = b;
```

Another distinction to make is between a pointer to const (`const t*`) and a const pointer (`t* const`), as in the following declarations:

```cpp
int* const p1;  // Const pointer: the pointed-to address cannot change after initialization, but the pointed-to value can change
const int* p2;  // Pointer to const: the dereferenced value cannot change, but it can point to another int variable
const int* const p3;  // Const pointer to const: the value cannot change, and the pointed-to address cannot change

// Using aliases can improve readability
using const_int = const int;
using ptr_to_const_int = const_int*;
using const_ptr_to_const_int = const ptr_to_const_int;
```

Using `const` to qualify parameter types in function parameters can prevent variables from being modified incorrectly and improve code readability.

```cpp
void sum(const std::vector<int> &data, int &total) {
  for (auto iter = data.begin(); iter != data.end(); ++iter)
    total += *iter;  // iter is an iterator, and the dereferenced type is const int
}
```

## `const` Member Functions

Member functions qualified with `const` in a type can restrict modifications to members.

```cpp
#include <iostream>

struct ConstMember {
  int s = 0;

  void func() { std::cout << "General Function" << std::endl; }

  void constFunc1() const { std::cout << "Const Function 1" << std::endl; }

  void constFunc2(int ss) const {
    // func(); // A const member function cannot call a non-const member function
    constFunc1();

    // s = ss; // A const member function cannot modify member variables
  }
};

int main() {
  int b = 1;
  ConstMember c{};
  const ConstMember d = c;
  // d.func(); // A const object cannot call a non-const member function
  d.constFunc2(b);
  return 0;
}
```

## Constant Expressions `constexpr` (C++11)

A constant expression is an expression whose result can be computed at compile time. `constexpr` requires the compiler to be able to compute the value of a function or variable at compile time.

Compile-time computation allows better optimization, such as hard-coding results into assembly and eliminating runtime computation costs. Unlike optimizations brought by `const`, when a variable modified by `constexpr` satisfies the conditions for a constant expression, the compiler is forced to compute the result at compile time rather than at runtime.

???+ note "A more intuitive understanding is to treat `const` as \"read-only\" and `constexpr` as \"immutable\""
    ```cpp
    constexpr int a = 10;  // Define a constant directly
    
    constexpr int FivePlus(int x) { return 5 + x; }
    
    void test(const int x) {
      std::array<int, x> c1;            // Error: x is not known at compile time
      std::array<int, FivePlus(6)> c2;  // OK: FivePlus is known at compile time
    }
    ```

The following example clearly illustrates the difference between `const` and `constexpr`. The code computes Fibonacci numbers recursively and outputs them using control flow.

???+ note "Implementation"
    ```cpp
    #include <iostream>
    
    using namespace std;
    
    constexpr unsigned fib0(unsigned n) {
      return n <= 1 ? 1 : (fib0(n - 1) + fib0(n - 2));
    }
    
    unsigned fib1(unsigned n) { return n <= 1 ? 1 : (fib1(n - 1) + fib1(n - 2)); }
    
    int main() {
      constexpr auto v0 = fib0(9);
      const auto v1 = fib1(9);
    
      cout << v0;
      cout << ' ';
      cout << v1;
    }
    ```

???+ note "Possible assembly after compilation (using Compiler Explorer, Clang 19)"
    ```nasm
    fib1(unsigned int):
            push    r14
            push    rbx
            push    rax
            mov     ebx, 1
            cmp     edi, 2
            jb      .LBB0_4
            mov     r14d, edi
            xor     ebx, ebx
    .LBB0_2:
            lea     edi, [r14 - 1]
            call    fib1(unsigned int)
            add     r14d, -2
            add     ebx, eax
            cmp     r14d, 1
            ja      .LBB0_2
            inc     ebx
    .LBB0_4:
            mov     eax, ebx
            add     rsp, 8
            pop     rbx
            pop     r14
            ret
    
    main:
            push    r14
            push    rbx
            push    rax
            mov     edi, 9
            call    fib1(unsigned int) # Initialization of `v1` performs a function call
            mov     ebx, eax
            mov     r14, qword ptr [rip + std::__1::cout@GOTPCREL]
            mov     rdi, r14
            mov     esi, 55 # `v0` is replaced by the final computed result
            call    std::__1::basic_ostream<char, std::__1::char_traits<char>>::operator<<(unsigned int)@PLT
            mov     byte ptr [rsp + 7], 32
            lea     rsi, [rsp + 7]
            mov     edx, 1
            mov     rdi, r14
            call    std::__1::basic_ostream<char, std::__1::char_traits<char>>& std::__1::__put_character_sequence[abi:ne200000]<char, std::__1::char_traits<char>>(std::__1::basic_ostream<char, std::__1::char_traits<char>>&, char const*, unsigned long)
            mov     rdi, r14
            mov     esi, ebx # Reads the variable value
            call    std::__1::basic_ostream<char, std::__1::char_traits<char>>::operator<<(unsigned int)@PLT
            xor     eax, eax
            add     rsp, 8
            pop     rbx
            pop     r14
            ret
    ```

The `fib0` function modified by `constexpr` is called only with a constant argument, so the entire function runs only at compile time. Since the function has no runtime execution, the compiler determines that no assembly code needs to be generated for it.

Also note that in the assembly, `v0` has no initialization code. In the code that calls `cout` to output `v0`, `v0` has been replaced by the final computed result, showing that the variable value was computed at compile time and the runtime operation was optimized away. By contrast, the initialization of `v1` is still an ordinary recursive call to `fib1`.

Therefore, `constexpr` can be used to replace constants defined by macros and avoid the [risks of macro definitions](./basic.md#the-define-command).

In algorithm problems, `constexpr` can be used to store variables with small data sizes to eliminate corresponding runtime computation costs. It is especially common in the "[table lookup](../contest/dictionary.md)" technique, where arrays and other containers modified by `constexpr` store answers.

???+ note "Excessive compile-time computation can cause compile errors"
    The compiler limits the cost of compile-time computation. If the computation is too large, compilation may fail, and you should consider using `const`.
    
    ```cpp
    #include <iostream>
    
    using namespace std;
    
    constexpr unsigned long long fib(unsigned long long i) {
      return i <= 2 ? i : fib(i - 2) + fib(i - 1);
    }
    
    int main() {
      // constexpr auto v = fib(32); evaluation exceeded maximum depth
      const auto v = fib(32);
      cout << v;
      return 0;
    }
    ```

???+ note "Compile error reported by Clang when using constexpr"
    ```text
    <source>:10:20: error: constexpr variable 'v' must be initialized by a constant expression
        10 |     constexpr auto v = fib(32);
        |                    ^   ~~~~~~~~~~~~
    <source>:6:25: note: constexpr evaluation exceeded maximum depth of 512 calls
        6 |     return i <= 2 ? i : fib(i - 2) + fib(i - 1);
        |                         ^
    <source>:6:25: note: in call to 'fib(32)'
        6 |     return i <= 2 ? i : fib(i - 2) + fib(i - 1);
        |                         ^~~~~~~~~~
    <source>:6:25: note: in call to ...
    ```

## References

-   [C++ keyword: const](https://en.cppreference.com/w/cpp/keyword/const)
-   [C++ keyword: constexpr](https://en.cppreference.com/w/cpp/keyword/constexpr)
