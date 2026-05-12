Operator overloading redefines operators so that they support operations on specific data types. Operator overloading is a special case of function overloading.

> When an operator appears in an expression, and at least one operand of the operator has a class or enumeration type, overload resolution is used to determine which user-defined function satisfying the corresponding declaration should be called.[^ref1]

Informally, if using an "operator" is viewed as calling a special function, such as treating `1+2` as a call to `add(1, 2)`, and at least one parameter (operand) of this function has type `class`, `struct`, or `enum`, then the compiler needs to decide which custom function to call based on the operand types.

In C++, almost all available operators can be overloaded.

???+ note "Some overloadable operators"
    Unary operators: `+` (positive); `-` (negative); `~` (bitwise NOT); `++`; `--`; `!` (logical NOT); `*` (dereference); `&` (address-of); `->` (class member access operator), and so on.
    
    Binary operators: `+`; `-`; `&` (bitwise AND); `[]` (subscript); `==`; `=` (assignment), and so on.
    
    Others: `()` (function call); `""` (suffix identifier[^ref1], since C++11); `new` (memory allocation); `,` (comma operator); `<=>` (three-way comparison[^ref2], since C++20), and so on.

## Restrictions

Operator overloading has the following restrictions:

-   Only existing operators can be overloaded; new operators cannot be defined.
-   The following operators cannot be overloaded: `::` (scope resolution), `.` (member access), `.*` (member access through pointer-to-member), and `?:` (ternary operator).
-   The precedence, number of operands, and associativity of an overloaded operator cannot be changed.
-   Overloading `&&` (logical AND) and `||` (logical OR) loses short-circuit evaluation.

## Implementation

Operator overloading has two cases: overloading as a member function or as a non-member function.

When overloaded as a member function, an implicit `this` pointer to the current object is used as a parameter, so the number of function parameters is one less than the number of operands.

When overloaded as a non-member function, the number of function parameters is the same as the number of operands.

The basic form is as follows, assuming the operator to overload is `@`:

```cpp
class Example {
  // Example of a member function
  return_type operator@(parameters_except_this) { /* ... */ }
};

// Example of a non-member function
return_type operator@(all_operands_as_parameters) { /* ... */ }
```

Several examples of overloaded operators are given below.

### Basic Arithmetic Operators

The following defines a two-dimensional vector struct `Vector2D` and implements overloads for addition and dot product.

??? note "Example of overloading arithmetic operators"
    ```cpp
    struct Vector2D {
      double x, y;
    
      Vector2D(double a = 0, double b = 0) : x(a), y(b) {}
    
      Vector2D operator+(Vector2D v) const { return Vector2D(x + v.x, y + v.y); }
    
      // Note that the return type does not have to be this class
      double operator*(Vector2D v) const { return x * v.x + y * v.y; }
    };
    ```

### Increment and Decrement Operators

Increment and decrement operators are divided into prefix (`++a`) and postfix (`a++`) forms. To distinguish prefix and postfix operators, an unused parameter of type `int` must be added when overloading the postfix operator.

Prefix increment can be understood as calling `operator++(a)` or `a.operator++()`, while postfix increment can be understood as calling `operator++(a, 0)` or `a.operator++(0)`.

??? note "Example of overloading prefix and postfix increment operators separately"
    ```cpp
    struct MyInt {
      int x;
    
      // Prefix, corresponding to ++a
      MyInt &operator++() {
        x++;
        return *this;
      }
    
      // Postfix, corresponding to a++
      MyInt operator++(int) {
        MyInt tmp;
        tmp.x = x;
        x++;
        return tmp;
      }
    };
    ```

Another point is that among built-in increment and decrement operators, prefix operators return references, while postfix operators return values. Although overloaded operators do not have to follow this restriction, semantically, overloaded operators are still expected to keep their return types consistent with the built-in operators.

For type T, typical definitions of overloaded increment operators are as follows:

| Overload definition (using `++` as an example) | Member function | Non-member function |
| --------------- | ----------------------- | -------------------------- |
| Prefix | `T& T::operator++();` | `T& operator++(T& a);` |
| Postfix | `T T::operator++(int);` | `T operator++(T& a, int);` |

### Function Call Operator

The function call operator `()` can only be overloaded as a member function. Overloading the `()` operator for a class allows objects of that class to be called like functions.

A common application of overloading `()` is to pass a struct with an overloaded `()` operator as a custom comparison function to STL containers such as priority queues.

Here is an example: given the names and scores of $n$ students, sort them in descending order by score, and for equal scores in ascending lexicographical order by name, then output the name and score of the top-ranked person.

The following defines a comparison struct to implement a custom ordering for a priority queue.

??? note "Example of overloading the function call operator"
    ```cpp
    struct student {
      string name;
      int score;
    };
    
    struct cmp {
      bool operator()(const student& a, const student& b) const {
        return a.score < b.score || (a.score == b.score && a.name > b.name);
      }
    };
    
    // Note that the template parameter is the struct name, not an instance
    priority_queue<student, vector<student>, cmp> pq;
    ```

### Comparison Operators

The `<` operator is needed in `std::sort` and some STL containers. When using custom types, we need to overload it manually.

The following example implements the same functionality as the previous section.

??? note "Example of overloading a comparison operator"
    ```cpp
    struct student {
      string name;
      int score;
    
      // Overload the < operator
      bool operator<(const student& a) const {
        return score < a.score || (score == a.score && name > a.name);
        // The this pointer is omitted above; the full expression is:
        // this->score<a.score||(this->score==a.score&&this->name>a.name);
      }
    };
    
    priority_queue<student> pq;
    ```

The code above overloads the less-than operator as a member function. Of course, it can also be overloaded as a non-member function.

??? note "Overloading as a non-member function"
    ```cpp
    struct student {
      string name;
      int score;
    };
    
    bool operator<(const student& a, const student& b) {
      return a.score < b.score || (a.score == b.score && a.name > b.name);
    }
    
    priority_queue<student> pq;
    ```

In fact, once the `<` operator is available, the other five comparison operators can also be implemented easily.

```cpp
/* clang-format off */

// The following implementations all overload the less-than operator as a non-member function

bool operator<(const T& lhs, const T& rhs) { /* overload the less-than operator here */ }
bool operator>(const T& lhs, const T& rhs) { return rhs < lhs; }
bool operator<=(const T& lhs, const T& rhs) { return !(lhs > rhs); }
bool operator>=(const T& lhs, const T& rhs) { return !(lhs < rhs); }
bool operator==(const T& lhs, const T& rhs) { return !(lhs < rhs) && !(lhs > rhs); }
bool operator!=(const T& lhs, const T& rhs) { return !(lhs == rhs); }
```

??? note "About the three-way comparison operator in C++20"
    If you use C++20 or later, you can directly use the default three-way comparison operator to simplify code.[^ref3]
    
    ```cpp
    auto operator<=>(const T &lhs, const T &rhs) = default;
    ```
    
    The default comparison order compares member variables one by one in the order in which they are declared.[^ref4]
    
    You can also use a custom three-way comparison. In this case, choose the ordering relation included in the comparison (`std::strong_ordering`, `std::weak_ordering`, or `std::partial_ordering`), or return an object such that:
    
    -   If `a < b`, then `(a <=> b) < 0`.
    -   If `a > b`, then `(a <=> b) > 0`.
    -   If `a` and `b` are equal or equivalent, then `(a <=> b) == 0`.
    
    For implementation details, see [comparison operators: three-way comparison - cppreference](https://en.cppreference.com/w/cpp/language/operator_comparison#Three-way_comparison).

References and notes:

[^ref1]: [Operator overloading - cppreference](https://en.cppreference.com/w/cpp/language/operators)

[^ref2]: [User-defined literals - cppreference](https://en.cppreference.com/w/cpp/language/user_literal)

[^ref3]: [Comparison operators: three-way comparison - cppreference](https://en.cppreference.com/w/cpp/language/operator_comparison#Three-way_comparison)

[^ref4]: [Default comparisons - cppreference](https://en.cppreference.com/w/cpp/language/default_comparisons)
