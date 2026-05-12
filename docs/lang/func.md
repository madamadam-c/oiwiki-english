author: Ir1d, tsagaanbar, yang-lile

## Function Declarations

A function in programming is generally a collection of several statements. It can also be called a **subroutine**. In programming, if there are repeated procedures, we can extract them into a function. A function can receive several values, called its parameters. A function can also return a value, called its return value.

To declare a function, we need the return type, the function name, and the parameter list.

```cpp
// Return type: int
// Function name: some_function
// Parameter list: int, int
int some_function(int, int);
```

As shown above, we declared a function named `some_function`. It receives two parameters of type `int`, and its return type is also `int`. You can think of this function as performing some operation on the two input integers and returning a result of the same type.

## Implementing a Function: Writing the Function Definition

A function declaration alone is not enough. It only lets us know the function's **interface** when calling it, namely what data it receives and what data it returns, but it lacks the concrete internal implementation, which is the function **definition**. We can write code **implementing** this function **somewhere after the declaration**. It may also be implemented in another file, but the separately compiled files must be provided together when linking.

If a function has a return value, it needs to return the value to the caller with a `return` statement. Once a function reaches a `return` statement, the current function ends immediately and subsequent statements are not executed.

```cpp
int some_function(int, int);  // Declaration

/* some other code here... */

int some_function(int x, int y) {  // Definition
  int result = 2 * x + y;
  return result;
  result = 3;  // This statement will not be executed
}
```

In the definition, we give names to the variables in the function's parameter list. This lets us use these variables in the function definition.

If the function is in the same file, we can also **combine the declaration and definition directly**; in other words, complete the definition when declaring it.

```cpp
int some_function(int x, int y) { return 2 * x + y; }
```

If a function does not need a return value, mark its return type as `void`. If a function does not need parameters, leave the parameter list empty. Similarly, when a function with no return value reaches a `return;` statement, it also ends execution.

```cpp
void say_hello() {
  cout << "hello!\n";
  cout << "hello!\n";
  cout << "hello!\n";
  return;
  cout << "hello!\n";  // This statement will not be executed
}
```

## Function Calls

Like variables, functions must be declared before they can be used. The act of using a function is called a **call**. We can call other functions inside any function, including the function itself. A function calling itself is called **recursion**.

In most languages, a function call is written as the **function name followed by a pair of parentheses** `()`, such as `foo()`. If the function needs arguments, write the required arguments in order inside the parentheses, separated by commas, such as `foo(1, 2)`. A function call is also an expression: the **function's return value** is the **value of the expression**.

The parameters written in a function declaration can be understood as variables available **inside the current call** of the function. These variables are initialized with the values passed at the call site. Consider this example:

```cpp
void foo(int, int);

/* ... */

void foo(int x, int y) {
  x = x * 2;
  y = y + 3;
}

/* ... */

a = 1;
b = 1;
// Before the call: a = 1, b = 1
foo(a, b);  // Call foo
            // After the call: a = 1, b = 1
```

In the example above, `foo(a, b)` is a call to `foo`. During the call, the variables `x` and `y` in `foo` are initialized with the values of `a` and `b` at the call site. Therefore, modifications to `x` and `y` inside `foo` **do not affect the values of the variables at the call site**.

If we need to modify the values of variables inside a function (subroutine), we need to pass them by reference.

```cpp
void foo(int& x, int& y) {
  x = x * 2;
  y = y + 3;
}

/* ... */

a = 1;
b = 1;
// Before the call: a = 1, b = 1
foo(a, b);  // Call foo
            // After the call: a = 2, b = 4
```

In the code above, an `&` (ampersand) is added after `int` in the function parameter list. This represents a **reference** to type `int`. When calling `foo`, the variables `a` and `b` at the call site initialize two references to `int`, `x` and `y`, inside `foo`. The `x` and `y` inside `foo` can be understood as aliases of the variables `a` and `b` at the call site; operations on `x` and `y` inside `foo` are operations on `a` and `b` at the call site.

## The `main` Function

In particular, every C/C++ program needs a function named `main`. Every program starts running from the `main` function.

> The `main` function can also have parameters. Through the parameters of `main`, we can obtain instructions passed to the program from outside, namely command-line arguments, and respond differently.

Here is a piece of code that calls a function (subroutine):

```cpp
// hello_subroutine.cpp

#include <iostream>

void say_hello() {
  std::cout << "hello!\n";
  std::cout << "hello!\n";
  std::cout << "hello!\n";
}

int main() {
  say_hello();
  say_hello();
}
```
