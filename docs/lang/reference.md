> Declares a named variable as a reference, that is, an alias to an existing object or function.

A reference can be regarded as a non-null pointer encapsulated by C++. It can be used to pass the object it refers to, and it must refer to an object when declared.

A reference is not an object, so there are no arrays of references, pointers to references cannot be obtained, and references to references do not exist.

??? note "Reference types are not object types"
    If you want a reference-like value that can support ordinary copying and assignment, for example as a container element, use [`reference_wrapper`](https://en.cppreference.com/w/cpp/utility/functional/reference_wrapper), which is usually implemented by maintaining a non-null pointer.

References are mainly divided into two kinds: lvalue references and rvalue references.

??? note "Lvalues and rvalues"
    For an explanation of lvalues and rvalues, see the [value categories](./value-category.md) page.

## Lvalue References T&

The references we usually encounter are lvalue references, that is, references bound to lvalues. A `const`-qualified lvalue reference can also bind to an rvalue. The following is sample code from the [reference manual](https://en.cppreference.com/w/cpp/language/reference).

```cpp
#include <iostream>
#include <string>

int main() {
  std::string s = "Ex";
  std::string& r1 = s;
  const std::string& r2 = s;

  r1 += "ample";  // Modifies r1, which modifies s
  // r2 += "!"; // Error: cannot modify through a reference to const
  std::cout << r2 << '\n';  // Prints r2, accessing s, and outputs "Example"
}
```

The most common use of lvalue references is in function parameters, to avoid unnecessary copies.

```cpp
#include <iostream>
#include <string>

// s in the parameter list is a reference, so no copy occurs when the function is called
char& char_number(std::string& s, std::size_t n) {
  s += s;  // 's' and 'str' in main() are the same object;
           // this also shows that an lvalue can appear on the right side of =
  return s.at(n);  // string::at() returns a reference to char
}

int main() {
  std::string str = "Test";
  char_number(str, 1) = 'a';  // The function return value is an lvalue and can be assigned
  std::cout << str << '\n';   // Outputs "TastTest" here
}
```

## Rvalue References T&& (C++11)

An rvalue reference is a reference bound to an rvalue. It is used to move objects, and can also be used to **extend the lifetime of temporary objects**.

```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
  string s1 = "Test";
  // string&& r1 = s1; // Error: cannot bind to an lvalue; std::move or static_cast is needed

  const string& r2 = s1 + s1;  // OK: an lvalue reference to const extends the lifetime
  // r2 += "Test"; // Error: cannot modify through a reference to const
  cout << r2 << '\n';

  string&& r3 = s1 + s1;  // OK: an rvalue reference extends the lifetime
  r3 += "Test";
  cout << r3 << '\n';

  const string& r4 = r3;  // An rvalue reference can convert to a const-qualified lvalue
  cout << r4 << '\n';

  string& r5 = r3;  // An rvalue reference can convert to an lvalue
  cout << r5 << '\n';
}
```

## Dangling References

When the object referred to by a reference has been destroyed, the reference becomes a dangling reference. Accessing a dangling reference is undefined behavior and may cause the program to crash.

The following are common examples of dangling references:

-   Referencing a local variable

    ```cpp
    #include <iostream>

    int& foo() {
      int a = 1;
      return a;
    }

    int main() {
      int& b = foo();
      std::cout << b << std::endl;  // Undefined behavior
    }
    ```

-   Dangling reference caused by deallocation

    ```cpp
    #include <iostream>

    int main() {
      int* ptr = new int(10);
      int& ref = *ptr;
      delete ptr;

      std::cout << ref << std::endl;  // Undefined behavior
    }
    ```

-   Dangling reference caused by memory reallocation

    ```cpp
    #include <iostream>

    int main() {
      std::string str = "hello";

      const char& ref = str.front();

      str.append("world");  // May reallocate memory, causing the memory referred to by ref to be freed

      std::cout << ref << std::endl;  // Undefined behavior
    }
    ```

    Insertion operations on containers such as `std::vector` and `std::unordered_map` may all cause memory reallocation.

When using references, always pay attention to the lifetime of the object referred to by the reference to avoid dangling references.

Static analysis tools and good coding habits can usually help us avoid dangling-reference problems.

## Reference-Related Optimization Techniques

### Eliminating Copy Costs for Non-Lightweight Function Arguments

Common **non-lightweight objects** include:

-   Containers such as `vector`, `array`, and `map`
-   `string`
-   Other types that implement or inherit custom copy constructors, move constructors, and other special functions

Using references for **lightweight objects** does not provide any benefit. The space occupied by a reference parameter may even be larger than the type itself.

This may introduce some performance overhead and may also prevent compiler optimizations.

The following are **lightweight objects**:

-   Basic types such as `int` and `float`
-   Small [aggregate types](https://en.cppreference.com/w/cpp/language/aggregate_initialization)
-   Iterators of standard library containers

### Converting Lvalues to Rvalues

Use `std::move` to [transfer](./value-category.md#stdmove) ownership of an object. This is usually seen between local variables, or between parameters and local variables:

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string world(string str) { return std::move(str) += " world!"; }

int main() {
  // 1
  cout << world("hello") << '\n';

  vector<string> vec0;

  // 2
  {
    string&& size = to_string(vec0.size());

    size += ", " + to_string(size.size());

    vec0.emplace_back(std::move(size));
  }

  cout << vec0.front();
}
```

But this is not needed in all cases, such as with [return value optimization](./value-category.md#常见误区).

### Rvalues Extending the Lifetime of Temporaries

Semantically, temporaries may introduce extra copies or moves. Although in most cases the compiler can optimize them through [copy elision](./value-category.md#复制消除), references can force the compiler not to perform these redundant operations, avoiding uncertainty.

## References

1.  [C++ language documentation: reference declaration](https://en.cppreference.com/w/cpp/language/reference)
2.  [C++ language documentation: value categories](https://en.cppreference.com/w/cpp/language/value_category)
3.  [Does const ref lvalue to non-const func return value specifically reduce copies?](https://stackoverflow.com/questions/38909228/does-const-ref-lvalue-to-non-const-func-return-value-specifically-reduce-copies)
