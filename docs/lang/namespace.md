## Overview

C++'s **namespace** mechanism can be used to solve name conflicts in complex projects.

For example, everything in the C++ standard library is defined in the `std` namespace. If you define a variable named `cin`, you can access your own `cin` variable with `cin` and the standard library's `cin` object with `std::cin`, without worrying about conflicts.

## Declaration

The following code declares a namespace named `A`:

```cpp
namespace A {
int cnt;

void f(int x) { cnt = x; }
}  // namespace A
```

After the declaration, outside this namespace, you can access the function `f` inside namespace `A` with `A::f(x)`, and the variable `cnt` inside namespace `A` with `A::cnt`.

Namespace declarations can be nested, so the following code is also allowed:

```cpp
namespace A {
namespace B {
void f() { ... }
}  // namespace B

void f() {
  B::f();  // This actually accesses A::B::f(). Since the current code is
           // inside namespace A, the preceding A:: can be omitted
}
}  // namespace A

void f()  // This defines function f in the global namespace, and it does
          // not conflict with A::f or A::B::f
{
  A::f();
  A::B::f();
}
```

## The `using` Directive

After declaring a namespace, to access members inside the namespace from outside it, you need to add `namespace::` before the member name.

Is there a more convenient way to access members inside a namespace directly by member name? Yes. We can use the `using` directive.

The `using` directive has the following two forms:

1.  `using namespace_name::member_name;`: this directive lets us omit the namespace before a specific member name and access the member directly by name, equivalent to importing that member into the current scope.
2.  `using namespace namespace_name;`: this directive lets us access **any** member in the namespace directly by member name, equivalent to importing all members of that namespace into the current scope.

Therefore, if `using namespace std;` is executed, all names in `std` are introduced into the current scope. This lets us use `cin` instead of `std::cin`, and `cout` instead of `std::cout`.

??? warning "The `using` directive may cause name conflicts!"
    Since `using namespace std;` introduces **all names** in `std`, declaring a variable or function with the same name as one in `std` may cause a compile error due to a name conflict.
    
    Therefore, in projects, using directives of the form `using namespace namespace_name;` are not recommended.

With the `using` directive, the code in [C++ Syntax Basics](./basic.md#cin-and-cout) can be written in either of these two equivalent ways:

```cpp
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {
  int x, y;
  cin >> x >> y;
  cout << y << endl << x;
  return 0;
}
```

```cpp
#include <iostream>

using namespace std;

int main() {
  int x, y;
  cin >> x >> y;
  cout << y << endl << x;
  return 0;
}
```

## Unnamed Namespaces

When we define only one namespace in a scope to prevent name conflicts, its definition and use can be made very concise. We can use an unnamed namespace.

A namespace defined in the form `namespace { /* something ... */ } `, with the namespace name omitted, is called an unnamed namespace. An unnamed namespace in a file is treated as having a unique name different from all other namespaces, but multiple unnamed namespaces in the same scope are treated as the same namespace. After an unnamed namespace is defined, the names inside it can be found from the surrounding scope when used, as if a `using namespace` directive had been added after the unnamed namespace definition.

## Applications

### Preventing Name Conflicts Between Subtasks

In some problems with multiple subtasks, we can define a namespace for each subtask and define the variables and functions needed to solve that subtask inside it. This way, even if two subtask implementations declare the same names, they do not conflict. This keeps the subtasks from interfering with each other, helps debugging to some extent, and improves readability.

### Preventing Conflicts with Names from the Standard Library and Environment

Namespaces can also prevent conflicts between names commonly used in algorithm competitions and standard or environment-provided names, as in the following example:

```cpp
#include <math.h>

#include <vector>

using namespace std;

namespace Sol {
int end;  // std::end is introduced by using namespace std;

int y1;  // y1 is a Bessel function of the second kind defined by POSIX

// Therefore, conflicts usually occur on Linux but not on Windows

void solve() {
  // Using our declared end and y1 without qualification (without ::) inside
  // Sol::solve() does not cause name conflicts. If the code above were in the
  // global namespace, it would cause conflicts: end would conflict with std::end
  // only during name lookup (that is, when compiling code that uses it), while y1
  // would conflict at declaration. Also, because the y1 conflict depends on the
  // environment, it might not be found on Windows but would cause a compile error
  // in the Linux judging environment.
}
}  // namespace Sol

int main() { Sol::solve(); }
```

## References

-   [Namespaces - cppreference.com](https://en.cppreference.com/w/cpp/language/namespace)
