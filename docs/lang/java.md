## About Java

Java is a widely used computer programming language. It is **cross-platform**, **object-oriented**, and supports **generic programming**. It is widely used in enterprise Web application development and mobile application development.

## Environment Setup

See [JDK](../tools/compiler.md#jdk).

## Basic Syntax

### Main Function

Like C/C++, Java needs a function (called a method in object-oriented terminology) as the program entry point.

The form of Java's main function is fixed:

```java
class Test {
    public static void main(String[] args) {
        // Program code
    }
}
```

A packaged Java program (usually named `*.jar`) may contain many similar functions, but only one of them is run when the program starts. This is defined in the `Manifest` file of the `Jar`, and is generally not needed in OI contests.

### Comments

Like C/C++, Java uses `//` and `/* */` for single-line and multi-line comments, respectively.

### Basic Data Types

| Type name | Meaning |
| :---: | :---: |
| boolean | Boolean type |
| byte | Byte type |
| char | Character type |
| double | Double-precision floating point |
| float | Single-precision floating point |
| int | Integer type |
| long | Long integer type |
| short | Short integer type |
| null | Null |

### Declaring Variables

```java
int a = 12; // Set a to integer type and assign 12 to a
String str = "Hello, OI-wiki"; // Declare string variable str
char ch = 'W';
double PI = 3.1415926;
```

### The final Keyword

`final` means that this is the final, unchangeable result. A variable modified by `final` can only be assigned once and cannot be changed afterward.

```java
final double PI = 3.1415926;
```

### Arrays

```java
// An integer array with ten elements
// Syntax: data_type[] variable_name = new data_type[array_size]
int[] ary = new int[10];
```

### Strings

-   A string is a built-in Java class.

```java
// The simplest way to construct a string variable is as follows
String a = "Hello";

// You can also construct a string variable from a character array
char[] stringArray = { 'H', 'e', 'l', 'l', 'o' };
String s = new String(stringArray);
```

### Packages and Importing Packages

Classes (`Class`) in Java are placed in packages (`package`). A package cannot contain two classes with the same name. The first line of a class usually states which package the class belongs to. For example:

```java
package org.oi-wiki.tutorial;
```

The usual package naming convention is: `top-level domain of the project owner.second-level domain of the project owner.project name`.

Use the `import` keyword to import classes that are not under the package this class belongs to. For example, the `Scanner` used below:

```java
import java.util.Scanner;
```

If you want to import all classes under a package, simply replace the class name before the final semicolon in this statement with `*`.

### Input

Command-line input can be handled with the `Scanner` class.

```java
package org.oiwiki.tutorial;

import java.util.Scanner;

class Test {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in); // System.in is the input stream
        int a = scan.nextInt();
        double b = scan.nextDouble();
        String c = scan.nextLine();
    }
}
```

### Output

Variables can be printed with formatting.

| Symbol | Meaning |
| :--: | :---: |
| `%f` | Floating-point type |
| `%s` | String type |
| `%d` | Integer type |
| `%c` | Character type |

```java
class Test {
    public static void main(String[] args) {
        int a = 12;
        char b = 'A';
        double s = 3.14;
        String str = "Hello world";
        System.out.printf("%f\n", s);
        System.out.printf("%d\n", a);
        System.out.printf("%c\n", b);
        System.out.printf("%s\n", str);
    }
}
```

### Control Statements

Java's flow-control statements are basically the same as C++'s.

#### Selection

-   if

```java
class Test {
    public static void main(String[] args) {
        if ( /* condition */ ){
            // Code executed when the condition is true
        }
    }
}
```

-   if...else

```java
class Test {
    public static void main(String[] args) {
        if ( /* condition */ ) {
            // Code executed when the condition is true
        } else {
            // Code executed when the condition is false
        }
    }
}
```

-   if...else if...else

```java
class Test {
    public static void main(String[] args) {
        if ( /* condition */ ) {
            // Code executed when the condition is true
        } else if ( /* condition 2 */ ) {
            // Code executed when condition 2 is true
        } else {
          // Code executed when none of the above conditions are true
        }
    }
}
```

-   switch...case

```java
class Test {
    public static void main(String[] args) {
        switch ( /* expression */ ){
          case /* value 1 */:
              // Execute this code when the expression's value matches value 1
              break; // Without break, the program continues downward until break
          case /* value 2 */:
              // Execute this code when the expression's value matches value 2
              break;
          default:
              // Execute this code when the expression does not match the values above
        }
    }
}
```

#### Loops

-   for

The `for` keyword has two forms. The first is the ordinary `for` loop, as follows:

```java
class Test {
    public static void main(String[] args) {
        for ( /* initialization */; /* loop condition */; /* step after each iteration */ ) {
            // Execute the loop body when the loop condition is true
        }
    }
}
```

The second is similar to C++ `foreach`, and is used to loop over data in an array or collection. It is equivalent to hiding the loop variable from the previous form:

```java
class Test {
    public static void main(String[] args) {
        for ( /* element type X */ /* element name Y */ : /* collection Z */ ) {
            // In each iteration of this block, element Y is one element of collection Z.
        }
    }
}
```

-   while

```java
class Test {
    public static void main(String[] args) {
        while ( /* condition */ ) {
            // Execute the loop body when the condition is true
        }
    }
}
```

-   do...while

```java
class Test {
    public static void main(String[] args) {
        do {
          // Code to execute
        } while ( /* loop condition */ );
    }
}
```

## Notes

### Class Name and File Name Must Match

When creating a Java source program, the class name and file name must match for compilation to succeed; otherwise, the compiler will report that it cannot find the class. Usually, this file name is specified by the specific OJ.

Example:

`Add.java`

```java
class Add {
    public static void main(String[] args) {
        // ...
    }
}
```

In this file, the class name must be `Add` for compilation to succeed.
