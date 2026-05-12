author: Ir1d, cjsoft, Lans1ot, JasonkayZK

A class is an extension of a structure. It can have not only data members, but also member functions.

In object-oriented programming (OOP), an object is an instance of a class, that is, a variable.

In C++, the `struct` keyword also defines a class. The definition of **structure** above comes from C. For historical reasons, C++ kept and extended `struct`.

## Defining Classes

Classes are defined with the keyword `class` or `struct`. The following uses `class` as an example.

```cpp
class ClassName {
  ...
};

// Example:
class Object {
 public:
  int weight;
  int value;
} e[array_length];

const Object a;
Object b, B[array_length];
Object *c;
```

This is mostly the same as using `struct`. The example defines a class named `Object`. This class has two data members, `weight` and `value`; after `}`, it also defines an array `e` of this type.

Pointers to classes are defined in the same way as [`struct`](./struct.md).

### Access Specifiers

Unlike the example in [`struct`](./struct.md), this example contains `public`, which is an access specifier.

-   `public`: members after this access specifier can be accessed publicly. In short, they can be accessed both **inside the class** and **outside the class**.
-   `protected`: members after this access specifier can be accessed by members of the **class itself**, derived classes, or friends, but **cannot be accessed** from outside the class.
-   `private`: members after this access specifier can **only** be accessed by members of the **class itself** or friends. They **cannot** be accessed from outside the class or from derived classes.

For `struct`, all members are `public` by default. For `class`, all members are `private` by default.

??? note "Basic concepts of friends and derived classes"
    Friend (`friend`): a function or class modified with the `friend` keyword. This allows the **modified entity** to access private (`private`) or protected (`protected`) members of the class without becoming a member function or member class. In short, as long as something is marked as a `friend` of this class, it can access private or protected data members.
    
    Derived class (`derived class`): C++ allows one class to be used as a **base class**, and a **derived class** to be derived from it. The derived class inherits member variables and member functions from the base class according to specific rules. This can improve code reuse.
    
    Derivation is like an "is" relationship. For example, a cat (derived class) "is" a mammal (base class).
    
    For the difference between `private` and `protected` above, you can think of it as: a derived class can access `protected` elements of its base class (as with `public`), but cannot access `private` elements.

## Accessing and Modifying Data Members

The method is the same as for [`struct`](./struct.md).

-   For variables, use the `.` symbol.
-   For pointers, use the `->` symbol.

## Member Functions

A member function, as the name suggests, is a function contained in a class.

??? note "Common examples of member functions"
    ```cpp
    vector.push_back();
    set.insert();
    queue.empty();
    ```

```cpp
class Class_Name {
  ... type Function_Name(...) { ... }
};

// Example:
class Object {
 public:
  int weight;
  int value;

  void print() {
    cout << weight << endl;
    return;
  }

  void change_w(int);
};

void Object::change_w(int _weight) { weight = _weight; }

Object var;
```

This class has a function that prints a data member of `Object`, and a function that changes the data member `weight`.

As with functions, member functions can be declared first and defined later, as in line 14 (the declaration) and after line 17 (the definition).

To call the `print` member function of `var`, use `var.print()`.

### Operator Overloading

??? note "What is overloading?"
    C++ allows programmers to specify different definitions for functions or operators with the same name. This is called **overloading**.
    
    If one or more of the parameter types or counts of functions with the same name differ pairwise, these functions are considered different.
    
    Note: if two functions with the same name differ only in return type, they cannot be overloaded, and the compiler will reject the code.
    
    If there is no ambiguity during a call (meaning that when calling functions with the same name, the called function can be uniquely determined from the types and number of arguments; ambiguity often occurs with default parameters), the compiler determines which function should be called from the supplied arguments.
    
    This process is called overload resolution.

Operator overloading can partially replace functions and simplify code.

Here is an example of operator overloading.

```cpp
class Vector {
 public:
  int x, y;

  Vector() : x(0), y(0) {}

  Vector(int _x, int _y) : x(_x), y(_y) {}

  int operator*(const Vector& other) const { return x * other.x + y * other.y; }

  Vector operator+(const Vector&) const;
  Vector operator-(const Vector&) const;
};

Vector Vector::operator+(const Vector& other) const {
  return Vector(x + other.x, y + other.y);
}

Vector Vector::operator-(const Vector& other) const {
  return Vector(x - other.x, y - other.y);
}

// Lines 4 and 5 assign values to x and y; see below for details.
```

This example defines a vector class and overloads the `* + -` operators, representing vector dot product, vector addition, and vector subtraction respectively.

The template for overloading operators can roughly be divided into the following parts.

```text
/* Overload inside class definition */ return_type operator symbol(parameters){...}

/* Declare inside class definition and define outside */ return_type ClassName::operator symbol(parameters){...}
```

For custom classes, if certain operators are overloaded (usually only the comparison operator `<` is needed), the corresponding STL containers or algorithms, such as [`sort`](../basic/stl-sort.md), can be used.

For more information, see item 4 in "References".

??? note "Operators that can be overloaded"
    ```text
    +       -       *       /       %       ^       &
    |       ~       !       =       <       >       +=
    -=      *=      /=      %=      ^=      &=      |=
    <<      >>      >>=     <<=     ==      !=      <=
    >=      &&      ||      ++      --      ,       ->*
    ->      ()      []      new     new []  delete  delete []
    ```

### Setting Initial Values When Instantiating Variables

To do this, define a **default constructor**.

```cpp
class ClassName {
  ... ClassName(...)... { ... }
};

// Example:
class Object {
 public:
  int weight;
  int value;

  Object() {
    weight = 0;
    value = 0;
  }
};
```

This example defines the default constructor of `Object`, which initializes all data members to `0` when we instantiate a variable of type `Object`.

If there is no explicit constructor, the compiler considers the class to have an implicit default constructor. In other words, if no constructor is defined, the compiler automatically generates a default constructor and initializes members according to their types (the same as defining variables of built-in types).

In this case, the data members are uninitialized, and accessing uninitialized variables has undefined behavior (that is, it is unknown what value will be returned).

If custom initial values are needed, additional constructors can be defined or overloaded.

??? note "Defining or overloading constructors"
    Generally speaking, a default constructor takes no parameters; this distinguishes it from other constructors. The definitions of constructors and default constructors are mostly the same, differing only in the number of parameters.
    
    Constructors can be overloaded (the first one is of course called a definition). Note that if a constructor has already been defined, the compiler will no longer generate a parameterless default constructor. This may cause attempts to construct variables in the default way (without initialization arguments) to fail to compile.

When using C++11 or later, variables can be initialized with `{}`.

??? note "About `{}`"
    Initialization with `{}` uses the lightweight proxy object `std::initializer_list`.
    
    The initialization steps are roughly as follows:
    
    1.  Try to find a default constructor whose parameters include `std::initializer_list`; if one exists, call it (after the call, the following searches are not performed; same below).
    2.  Try to fill other constructor parameters with the elements in `{}`. If the parameters can be filled in order (default parameters count), call that default constructor.
    3.  If there are no `private` data members, try assigning values **outside the class** in the order of member definition or subscript order.
    
    *The process above is only a simplified version of the complete process. For details, see "Reference 9".*

```cpp
class Object {
 public:
  int weight;
  int value;

  Object() {
    weight = 0;
    value = 0;
  }

  Object(int _weight = 0, int _value = 0) {
    weight = _weight;
    value = _value;
  }

  // the same as
  // Object(int _weight,int _value):weight(_weight),value(_value) {}
};

// the same as
// Object::Object(int _weight,int _value){
//   weight = _weight;
//   value = _value;
// }
//}

Object A;        // ok
Object B(1, 2);  // ok
Object C{1, 2};  // ok,(C++11)
```

??? note "Implicit type conversion"
    Sometimes code like the following appears:
    
    ```cpp
    class Node {
     public:
      int var;
    
      Node(int _var) : var(_var) {}
    };
    
    Node a = 1;
    ```
    
    This looks very illogical: an `int` cannot be converted to a `node`. However, the compiler does not report an `error`.
    
    The reason is that during assignment, `1` is first used as an argument to call `node::node(int)`, and then the default copy function is called for assignment.
    
    In most cases, however, programmers want the compiler to report an error. In this case, add the `explicit` keyword before the constructor. This tells the compiler that the call must be explicit.
    
    ```cpp
    class Node {
     public:
      int var;
    
      explicit Node(int _var) : var(_var) {}
    };
    ```
    
    That is, `node a=1` will produce an error, but `node a=node(1)` will not, because the latter explicitly calls the constructor. Of course, most people would not write the latter code, but this example is enough to show the role of `explicit`.
    
    *In algorithm competitions, however, the common way to avoid such situations is to strengthen code style standards and prevent them at the source.*

### Destruction

This is unavoidable. Every variable is destroyed when its scope ends.

For a pointer that already points to dynamically allocated memory, however, destroying the pointer does not automatically release the memory it points to. The dynamic memory must be released manually.

If the data members of a structure contain pointers, the same problem occurs. A destructor is needed to release dynamic memory manually.

A **destructor** is called when the variable is destroyed. The way to overload it is similar to a constructor, but it must be prefixed with `~`.

*The default destructor is usually sufficient for algorithm competitions. Usually we only overload the destructor when data members contain pointers.*

```cpp
class Object {
 public:
  int weight;
  int value;
  int* ned;

  Object() {
    weight = 0;
    value = 0;
  }

  ~Object() { delete ned; }
};
```

### Assigning Values to Class Variables

By default, assignment follows the assignment rules for the corresponding data members. You can also use `ClassName()` or `ClassName{}` as a temporary variable for assignment.

The former only calls the copy constructor, while the latter calls the default constructor before calling the copy constructor.

Also by default, assignment between corresponding members performs a **shallow copy**. If data members contain pointers, then after assignment the member pointers of the two variables have the same address.

```cpp
// A, tmp1, tmp2, and tmp3 have type Object
tmp1 = A;
tmp2 = Object(...);
tmp3 = {...};
```

To solve pointer-related issues or perform more operations, overload the corresponding constructor.

*For more about constructors, see item 6 in "References".*

## References

1.  [cppreference class](https://en.cppreference.com/w/cpp/language/class)
2.  [cppreference access](https://en.cppreference.com/w/cpp/language/access)
3.  [cppreference default\_constructor](https://en.cppreference.com/w/cpp/language/default_constructor)
4.  [cppreference operator](https://en.cppreference.com/w/cpp/language/operators)
5.  [cplusplus Data structures](http://www.cplusplus.com/doc/tutorial/structures/)
6.  [cplusplus Special members](http://www.cplusplus.com/doc/tutorial/classes2/)
7.  [C++11 FAQ](http://www.stroustrup.com/C++11FAQ.html)
8.  [cppreference Friendship and inheritance](http://www.cplusplus.com/doc/tutorial/inheritance/)
9.  [cppreference value initialization](https://en.cppreference.com/w/cpp/language/value_initialization)
