Value categories are a very important concept in C++. Although they may not be used much in algorithm competitions, understanding them can help us find and avoid unnecessary copies, improving code efficiency and performance.

The concept of value categories has evolved several times in C, C++98, C++11, and C++17, gradually becoming a relatively complex concept.

## Unnecessary Copies

Consider the process of inserting strings into a vector:

```cpp
int main() {
  std::vector<std::string> vec;
  vec.reserve(3);
  for (int i = 0; i < 3; ++i) {
    std::string str;
    std::cin >> str;
    vec.push_back(str);
  }
  return 0;
}
```

We can see that during the transfer process, one copy of the string is stored in `str` and another in `vec`, doubling memory usage.

If we insist on saving this memory, we can implement a crude move operation: define a custom `MyString` structure containing a pointer to our string. That is, we only need to copy the pointer over and carefully clear the pointer in the original object to prevent it from being destructed incorrectly.

```cpp
struct MyString {
  char *beg, *end;
  // ...
};

void move_to(MyString &src, MyString &dst) {
  dst.beg = src.beg;
  dst.end = src.end;
  src.beg = src.end = nullptr;
}
```

Because the need to transfer objects efficiently is common, and because it is difficult to make such transfers interact correctly with C++ operations such as construction and destruction, C++11 introduced move semantics into the core language.

## Value Categories in C

In the C standard, an object is a more general concept than a variable. It denotes a region of memory and has a memory address. The main properties of an object include size, effective type, value, and identifier. The identifier is the variable name, and the value is the meaning of that memory when interpreted as its type. For example, although `int` and `float` both occupy 4 bytes, the same block of memory is interpreted differently for the two types.

Every expression in C has a type and a value category. Value categories are mainly divided into three kinds:

-   lvalue: an expression that implicitly denotes an object. That is, we can take the address of the expression.
-   rvalue: an expression that does not denote an object, that is, a value without a storage location. We cannot take the address of this value.
-   function designator: an expression of function type.

Therefore, only modifiable lvalues (lvalues that are not `const`-qualified and are not arrays) can appear on the left side of an assignment expression.

For an operator that requires an rvalue as its operand, whenever an lvalue is used as the operand, lvalue-to-rvalue, array-to-pointer, or function-to-pointer standard conversion is applied to convert it to an rvalue.

Common misconceptions:

-   Further operations on an rvalue expression may produce an lvalue. For example, for `int *a`, the expression `a + 1` is an rvalue, but `*(a + 1)` is an lvalue.
-   Expressions have value categories; variables do not. For example, for `int *a`, it is incorrect to say that the variable `a` is an lvalue. It is correct to say that it is used as an lvalue in the expression `a`.

## Value Categories in C++98

C++98 is almost the same as C in terms of value categories, but adds some new rules:

-   Functions are lvalues because their addresses can be taken.
-   Lvalue references (`T&`) are lvalues because their addresses can be taken.
-   Only `const T&` can bind to rvalues.

### Copy Elision

C++ allows compilers to perform copy elision, which can reduce the creation and destruction of temporary objects.

For example, the following code triggers return value optimization (RVO), a form of copy elision. You will only see one construction and one copy construction, even if construction and destruction have side effects.

```cpp
struct X {
  X() { std::puts("X::X()"); }

  X(const X &) { std::puts("X::X(const X &)"); }

  ~X() { std::puts("X::~X()"); }
};

X get() {
  X x;
  return x;
}

int main() {
  X x = get();
  X y = X(X(X(X(x))));
  return 0;
}
```

## Value Categories in C++11

C++11 introduced move semantics and rvalue references (`T&&`), including move constructors and move assignment functions. This gives us a way to make use of temporary objects.

Our earlier `move_to` can be rewritten as follows:

```cpp
struct MyString {
  // ...
  MyString(MyString&& other) {
    beg = other.beg;
    end = other.end;
    other.beg = other.end = nullptr;
  }
};
```

The expression properties we now care about have increased slightly:

-   Whether it has identity: whether it denotes an object, that is, whether it has an address.
-   Whether it can be moved from: whether it has functions such as move construction and move assignment, giving us a way to use these temporary objects.

Therefore, we have three value categories:

-   Has identity, cannot be moved from: lvalue.
-   Has identity, can be moved from: xvalue.
-   Has no identity, can be moved from: prvalue.
-   Has no identity, cannot be moved from: expressions of this category cannot be used.

C++11 also introduced two compound categories:

-   Has identity: glvalue, namely lvalue and xvalue.
-   Can be moved from: rvalue, namely prvalue and xvalue.

### std::move

To support move semantics, C++11 also introduced a utility function, `std::move`. Its purpose is to force-convert an lvalue into an rvalue so that move semantics can be triggered.

```cpp
int main() {
  std::vector<int> a = {1, 2, 3};
  std::cout << "a: " << a.data() << std::endl;
  std::vector<int> b = a;
  std::cout << "b: " << b.data() << std::endl;
  std::vector<int> c = std::move(b);
  std::cout << "c: " << c.data() << std::endl;
}
```

Thus, we only need to change `push_back(str)` to `push_back(std::move(str))` to avoid copying.

```cpp
int main() {
  std::vector<std::string> vec;
  vec.reserve(3);
  for (int i = 0; i < 3; ++i) {
    std::string str;
    std::cin >> str;
    vec.push_back(std::move(str));
    // Another clever way, requires C++17
    // std::cin >> vec.emplace_back();
  }
  return 0;
}
```

> Because `std::string` has Small String Optimization (SSO), short strings are stored directly inside the structure. You may need to enter a longer string to observe that the `data` pointer remains unchanged.

## Value Categories in C++17

C++17 further simplified value categories:

-   lvalue: has identity and cannot be moved from.
-   xvalue: has identity and can be moved from.
-   prvalue: initialization of an object.

C++11 extended copy elision to moves. In the following code, `urvo` has no move when the compiler enables RVO.

C++17 requires prvalues not to be materialized unless necessary; they are constructed directly into the storage of their final destination, and the object does not exist before construction. Therefore, in C++17 there is no return step, and we no longer need to rely on RVO. This can also be understood as mandating URVO (Unnamed RVO), while NRVO (Named RVO) is still not mandatory.

```cpp
std::string urvo() { return std::string("123"); }

std::string nrvo() {
  std::string s;
  s = "123";
  std::cout << s;
  return s;
}

int main() {
  std::string str = urvo();  // Direct construction
  std::string str = nrvo();  // Not necessarily direct construction; depends on optimization
}
```

C++17 also introduced the mechanism of temporary materialization. When we need a glvalue, such as when accessing member variables or calling member functions, an implicit conversion to an xvalue can occur.

### Common Misconceptions

In the following examples:

-   Returning `std::move(x)` in `f1` is unnecessary. It does not improve performance and instead interferes with the compiler's NRVO optimization.
-   Returning `std::move(x)` in `f2` is dangerous. The function returns an rvalue reference pointing to the destroyed local variable `s`, causing a dangling reference.

```cpp
std::string f1() {
  std::string s = "123";
  // Equivalent to return std::string(std::move(s))
  return std::move(s);
}

std::string&& f2() {
  std::string s = "123";
  return std::move(s);
}
```

## References and Recommended Reading

1.  [Value categories](https://en.cppreference.com/w/cpp/language/value_category)
2.  [Wording for guaranteed copy elision through simplified value categories](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0135r1.html)
3.  [Value categories in C++](https://paul.pub/cpp-value-category/)
4.  [C++ rvalue references, move, and value category system: everything you need](https://zclll.com/index.php/cpp/value_category.html)
5.  [Copy elision](https://en.cppreference.com/w/cpp/language/copy_elision)
