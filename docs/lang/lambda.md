**Note**: Considering the practical needs of algorithm competitions, this article will not study the syntax comprehensively. It only discusses the parts that may be useful in algorithm competitions.

The syntax in this article follows the **C++11** standard. Syntax from later standards is mentioned as needed and is specially marked.

## Lambda Expressions

Lambda expressions are named after $\lambda$ calculus in mathematics and directly correspond to lambda abstraction. During compilation, the compiler generates an anonymous [**function object**](./new.md#function-objects) according to the syntax. Captured variables become its members, while the parameters and function body implement an `operator()` overload.

??? note "Function Object"
    A function object is a class object, generally implemented by overloading `operator()`, so it can be called like a function. Compared with ordinary functions, function objects have many advantages, such as being able to store state and be passed as arguments to other functions.

One possible lambda syntax is:

```text
[capture] (parameters) mutable -> return-type {statement}
```

A lambda expression itself is a class. Expanded, it looks like this:

<!-- scripts.linter.preprocess.fix_details off -->

```text
class Lambda_1 {
 private:
  Lambda_1() : capture-list(init-value) { }

 public:
  return-type operator()(parameters) const { statement }

 private:
  mutable capture-list
};
```

<!-- scripts.linter.preprocess.fix_details on -->

An empty capture can be implicitly converted to a function pointer. For example:

```cpp
void (*f)(int, int) = [](int, int) -> void {};
```

The following sections introduce each part of the syntax.

### statement Function Body

The function body is similar to that of an ordinary function. Besides accessing parameters and global variables, it can also access [captured](#capture-capture-clause) variables.

### capture Capture Clause

A lambda begins with a capture clause. It specifies which variables are captured. The capture list may be empty, or it may specify capture modes: variables prefixed with `&` are accessed by [reference](./reference.md), while variables without this prefix are accessed by value.

We can also use a default capture mode to capture all variables mentioned in the lambda: `&` means all captured variables are accessed by reference, and `=` means all captured variables are accessed by value.

After a default capture, you can still **explicitly** specify the capture mode for particular variables.

If you need to access the external variable `a` by reference and the external variable `b` by value, all of the following capture clauses work:

-   `[&a, b]`
-   `[b, &a]`
-   `[&, b]`
-   `[b, &]`
-   `[=, &a]`

The capture list can also be used to declare variables. Their types are deduced from their initializers, similarly to variables declared with `auto`.

Here are some common examples:

```cpp
int a = 0;
auto f0 = []() { return a * 9; };   // Error, cannot access 'a'
auto f1 = [a]() { return a * 9; };  // OK, 'a' is captured by value
auto f2 = [&a]() { return a++; };   // OK, 'a' is captured by reference
auto f3 = [v = a + 1]() {
  return v + 1;
};  // OK, declare variable v with an initializer; its type is the same as a's

// Note: when using reference capture, make sure a has not been destroyed when called
auto b = f2();  // f2 gets a from the capture list; a need not be passed as an argument
```

#### generalized capture: Capture with Initialization (C++14)

Since C++14, `capture` can not only capture external variables, but also declare and initialize new variables. For example:

```cpp
auto f1 = [val = 520]() {
  return val;
};  // OK, val has type int, initial value 520, and return type int

auto f2 = [val = 520LL]() {
  return val;
};  // OK, val has type long long, initial value 520, and return type long long

auto f3 = [val = "520"]() {
  return val;
};  // OK, val has type const char*, initial value "520", and return type const char*

auto f4 = [val = "520"s]() {
  return val;
};  // OK, since C++14, requires using namespace std; or using namespace std::literals;
    // val has type std::string, initial value std::string("520"), and return type
    // std::string

auto f5 = [val = std::string("520")]() {
  return val;
};  // OK, val has type std::string, initial value std::string("520"), and return type
    // std::string

auto f6 = [val = std::vector<int>(3, 6)]() {
  return val;
};  // OK, val has type std::vector<int>, size 3, filled with 6, and return type
    // std::vector<int>

auto f7 = [val = 520]() -> int {
  return val;
};  // OK, val has type int, initial value 520, and return type int

auto f8 = [val = 520]() -> long long {
  return val;
};  // OK, val has type int, initial value 520, and return type long long
```

When defining a new variable, the initial value cannot be omitted. The variable's type is determined by the type of the initial value, equivalent to:

```text
auto val = init-value;
```

The following is incorrect:

```cpp
auto f = [val]() { return val; };  // Error: 'val' was not declared in this
                                   // scope, identifier "val" is undefined
```

The initial value can also be an external variable. For example:

```cpp
int value = 520;
auto f = [val = value]() { return val; };
std::cout << f();  // Output: 520
```

`val` may also be a reference type that refers to an external variable. This can give an alias to an external variable captured by reference. For example:

```cpp
int value = 520;

auto f = [&val = value]() {
  return val;
};  // OK, val has type int&, return type int, equivalent to int& val = value;

std::cout << f() << '\n';  // Output: 520

value = 1314;

std::cout << f() << '\n';  // Output: 1314
```

Capturing external variables and defining new variables can be used at the same time.

If you want to modify a new variable defined in `capture` inside the lambda expression, you need the `mutable` keyword. This is not needed for references. For example:

```cpp
int value = 520;

{
  auto f = [val = value]() mutable -> int {
    return val = 1314;
  };  // mutable is required
  auto val_f = f();
  std::cout << value << ' ' << val_f << std::endl;  // Output: 520 1314
}

{
  auto f = [&val = value]() -> int { return val = 1314; };  // mutable is not required
  auto val_f = f();
  std::cout << value << ' ' << val_f << std::endl;  // Output: 1314 1314
}
```

See [mutable specifier](#mutable-mutable-specifier) for details.

The lifetime of a variable defined in `capture` follows the receiver of the lambda expression, which is the variable $f$ in the examples above. Since the lambda itself is actually a class, everything in `capture` is a `private` member variable of that class. For example:

```cpp
int main() {
  auto f = [val = 0]() mutable -> int { return ++val; };  // val is constructed and initialized

  std::cout << f() << '\n';  // Output: 1
  std::cout << f() << '\n';  // Output: 2
  std::cout << f() << '\n';  // Output: 3
}  // val is destroyed along with f
```

### parameters Parameter List

In most cases, this is similar to a function parameter list. For example:

```cpp
int x[] = {5, 1, 7, 6, 1, 4, 2};
std::sort(x, x + 7, [](int a, int b) { return (a > b); });
for (auto i : x) std::cout << i << " ";
```

This prints the result of sorting array `x` in descending order.

Because the **parameters parameter list** is optional, if no arguments are passed to the lambda, its declaration does not contain [mutable](#mutable-mutable-specifier), and there is no trailing return type, the empty parentheses can be omitted.

??? note "Parameters declared with `auto`"
    Since **C++14**, if a parameter is declared with type `auto`, a [generic lambda expression](#generic-lambda-c14) is constructed.

#### Explicit Object Parameter (C++23)

Since **C++23**, [explicit object parameters](https://en.cppreference.com/w/cpp/language/function#Parameter_list) can be used in lambda parameters.

```cpp
auto nth_fibonacci = [](this auto self, unsigned n) -> unsigned {
  return n < 2 ? n : self(n - 1) + self(n - 2);
};

cout << nth_fibonacci(10u);
```

### mutable Mutable Specifier

This allows the function body to modify variables captured by value.

```cpp
int a = 0;
auto by_value = [a]() mutable { ++a; };
auto by_ref = [&a] { ++a; };

by_value();
by_ref();
```

After executing `by_value()`, the captured member `a` of `by_value` is 1, but the external variable `a` is still 0.
After executing `by_ref()`, the value of external `a` becomes 1.

### return-type Return Type

This specifies the return type of the lambda expression. If it is omitted, the return type is deduced automatically (the behavior is the same as for a function whose return value is declared with `auto`).

If there are multiple `return` statements and their deduced types are inconsistent, a compilation error occurs.

```cpp
auto lam = [](int a, int b) -> int { return 0; };

auto x1 = [](int i) { return i; };

auto x2 = [](bool condition) {
  if (condition) return 1;
  return 1.0;
};  // Error, inconsistent deduced types
```

### Generic Lambda (C++14)

Using `auto` as a parameter type constructs a generic lambda.

```cpp
auto add = [](auto a, auto b) { return a + b; };
```

In [cpp insights](https://cppinsights.io), you can observe the `lambda` class definition generated by the compiler:

```cpp
class add_lambda {
 public:
  template <class T, class U>
  auto operator()(T a, U b) const {
    return a + b;
  }
};

add_lambda add{};
```

Both parameters of `add` are declared with `auto`, corresponding to the two template parameters `T` and `U` of the `operator()` function template in the `add_lambda` class.

### Recursion in Lambda

First, consider an example that fails to compile:

```cpp
int n = 10;

auto dfs = [&](int i) -> void {
  if (i == n)
    return;
  else
    dfs(i + 1);  // Error: a variable declared with an auto type specifier
                 // cannot appear in its own initializer
};
```

Here we try to capture $dfs$ in the capture list, but there is a problem: the type of $dfs$ is `auto`, so it cannot be deduced until the type on the right side of the equals sign has been deduced. However, for the lambda to capture $dfs$, it must know the type of $dfs$ before it can create a reference variable for it. This creates a recursive dependency.

How can this problem be solved?

1.  Explicitly specify the type of $dfs$, for example by using `std::function`.

    ???+ example "Modify the code above as follows:"
        ```cpp
        int n = 10;
        
        std::function<void(int)> dfs = [&](int i) -> void {
          if (i == n)
            return;
          else
            dfs(i + 1);  // OK
        };
        
        dfs(1);
        ```

    ??? warning "Using [`std::function`](./new.md#stdfunction) for recursion is not recommended"
        Type erasure in `std::function` usually requires extra memory allocation, and the indirection from indirect calls further reduces performance.
        
        In a [benchmark](https://quick-bench.com/q/U5qf_dHHKsSyVU83jmt0p_U541c) using the Clang 17 compiler and libc++ as the standard library, recursion implemented with `std::function` was about 2.5 times slower than recursion implemented with a lambda.
        
        ??? note "Benchmark code"
            ```cpp
            #include <algorithm>
            #include <functional>
            #include <numeric>
            #include <random>
            
            using namespace std;
            
            const auto& nums = [] {
              random_device rd;
              mt19937 gen{rd()};
              array<unsigned, 32> arr{};
            
              std::iota(arr.begin(), arr.end(), 0u);
              ranges::shuffle(arr, gen);
            
              return arr;
            }();
            
            static void std_function_fib(benchmark::State& state) {
              std::function<int(int)> fib;
            
              fib = [&](int n) { return n <= 2 ? 1 : fib(n - 1) + fib(n - 2); };
            
              unsigned i = 0;
            
              for (auto _ : state) {
                auto res = fib(nums[i]);
                benchmark::DoNotOptimize(res);
            
                ++i;
            
                if (i == nums.size()) i = 0;
              }
            }
            
            BENCHMARK(std_function_fib);
            
            static void template_lambda_fib(benchmark::State& state) {
              auto n_fibonacci = [](const auto& self, int n) -> int {
                return n <= 2 ? 1 : self(self, n - 1) + self(self, n - 2);
              };
            
              unsigned i = 0;
            
              for (auto _ : state) {
                auto res = n_fibonacci(n_fibonacci, nums[i]);
                benchmark::DoNotOptimize(res);
            
                ++i;
            
                if (i == nums.size()) i = 0;
              }
            }
            
            BENCHMARK(template_lambda_fib);
            ```
2.  Do not obtain $dfs$ by capturing it; pass it as a function argument instead.

    ???+ example "Modify the code above as follows:"
        ```cpp
        int n = 10;
        
        // If the parameter list contains a parameter whose type is auto, then operator()
        // in this Lambda class is defined as a function template, and the template
        // function can be instantiated later when it is called
        auto dfs = [&](auto& self,
                       int i) -> void  // [&] only captures variables that are used, so it does not capture auto dfs
        {
          if (i == n)
            return;
          else
            self(self, i + 1);  // OK
        };
        
        dfs(dfs, 1);
        ```

    ???+ note "Differences between `auto self`, `auto& self`, and `auto&& self`:"
        In theory, both `auto& self` and `auto&& self` use only $8$ bytes (the size of a pointer) for parameter passing, with no other copies. The details depend on how the compiler implements lambdas and the corresponding optimizations.
        Using `auto self` copies the object. The copy size depends on the elements in the capture list, since they are all private member variables of this lambda class.
3.  You can manually expand the lambda class, or use a similar form, so that the type of $dfs$ can be declared directly.

    ???+ example "Modify the code above as follows:"
        ```cpp
        int n = 10;
        
        class Lambda_1 {
         public:
          auto operator()(int i) const -> void {
            if (i == n)
              return;
            else
              (*this)(i + 1);  // OK
          }
        
          explicit Lambda_1(int& __n) : n(__n) {}
        
         private:
          int& n;
        } dfs(n);
        
        dfs(1);
        ```
4.  If the lambda captures no variables, we can also use a function pointer.

    If a lambda captures no variables, it can be implicitly converted to a function pointer. The lambda can also be declared `static`, and the function pointer type can also be declared `static`. In this way, the lambda can access the function pointer without capturing it, thereby implementing recursion.

    ???+ example "Example"
        ```cpp
        static unsigned (*fptr)(unsigned);
        
        static const auto lambda = [](const unsigned a) {
          return a < 2 ? a : (*fptr)(a - 2) + (*fptr)(a - 1);
        };
        
        static auto init = [] {
          fptr = +lambda;
          // Or
          // fptr = static_cast<unsigned (*)(unsigned)>(lambda);
          return 0;
        }();
        
        cout << lambda(10);
        ```

### Applications of Lambda Expressions

#### As Predicates for Standard Library Algorithms

Sort in descending order:

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
```

Use [std::find\_if](https://en.cppreference.com/w/cpp/algorithm/find) to find the first element greater than 3:

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
auto it = std::find_if(v.begin(), v.end(), [](int a) { return a > 3; });
```

#### Controlling the Lifetime of Intermediate Variables

In algorithm competitions, we may encounter this situation: initializing one variable requires previously declared variables, and the initialization process creates large intermediate objects.

We want to destruct these intermediate variables as soon as possible to reduce memory consumption. In this case, we can use a lambda to control their lifetime.

```cpp
void solution(const vector<int>& input) {
  int b = [&] {
    vector<int> large_objects(input.size());
    int c = 0;

    for (int i = 0; i < large_objects.size(); ++i)
      large_objects[i] = i + input[i];

    for (int i = 0; i < input.size(); ++i) c += large_objects[input[i]];

    return c;
  }();

  // ...
}
```

Compared with block scope, a lambda allows us to use a return value, making the code more concise. Compared with a function, we do not need to give an extra name or declare all captured parameters, making the code more compact.

## References

-   [cppreference-lambda](https://en.cppreference.com/w/cpp/language/lambda)
-   [Stackoverflow: Overhead with std::function](https://stackoverflow.com/a/33881130/11120338)
