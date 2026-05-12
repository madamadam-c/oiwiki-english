???+ warning "Note"
    The following content is based on Java JDK 8. Some details may differ in later versions.

## Faster Input and Output

`Scanner` and `System.out.print` work well at first, but they become inefficient when processing larger input, so we need some methods to improve IO speed.

### Using Kattio + StringTokenizer for Input

One of the most common methods is to use [Kattio.java](https://github.com/Kattis/kattio/blob/master/Kattio.java) from Kattis to improve IO efficiency.[^ref1] This method wraps `StringTokenizer` and `PrintWriter` in one class for convenient use. When solving problems, you can use this template directly if the contest or organizer allows it.

The following is the IO template that should be included in the code. Since the original Kattio from Kattis contains some less commonly used features, the template below has been adjusted. The original Kattio uses the MIT license.

```java
class Kattio extends PrintWriter {
    private BufferedReader r;
    private StringTokenizer st;
    // Standard IO
    public Kattio() { this(System.in, System.out); }
    public Kattio(InputStream i, OutputStream o) {
        super(o);
        r = new BufferedReader(new InputStreamReader(i));
    }
    // File IO
    public Kattio(String intput, String output) throws IOException {
        super(output);
        r = new BufferedReader(new FileReader(intput));
    }
    // Return null when there is no more input
    public String next() {
        try {
            while (st == null || !st.hasMoreTokens())
                st = new StringTokenizer(r.readLine());
            return st.nextToken();
        } catch (Exception e) {}
        return null;
    }
    public int nextInt() { return Integer.parseInt(next()); }
    public double nextDouble() { return Double.parseDouble(next()); }
    public long nextLong() { return Long.parseLong(next()); }
}
```

The following code briefly demonstrates how to use Kattio:

```java
class Test {
    public static void main(String[] args) {
        Kattio io = new Kattio();
        // String input
        String str = io.next();
        // int input
        int num = io.nextInt();
        // Output
        io.println("Result");
        // Make sure to close the IO stream so the output is written correctly
        io.close();
    }
}
```

### Using StreamTokenizer for Input

In some cases, using `StringTokenizer` may cause MLE (Memory Limit Exceeded). In this case, we need to use `StreamTokenizer` for input.

```java
import java.io.*;
public class Main {
    // IO code
    public static StreamTokenizer in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in), 32768));
    public static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    public static double nextDouble() throws IOException { in.nextToken(); return in.nval; }
    public static float nextFloat() throws IOException { in.nextToken(); return (float)in.nval; }
    public static int nextInt() throws IOException { in.nextToken(); return (int)in.nval; }
    public static String next() throws IOException { in.nextToken(); return in.sval; }
    public static long nextLong() throws Exception { in.nextToken(); return (long)in.nval;}
    
    // Usage example
    public static void main(String[] args) throws Exception {
        int n = nextInt();
        out.println(n);
        out.close();
    }
}
```

### Analysis and Comparison Between Kattio + StringTokenizer and StreamTokenizer

1.  `StreamTokenizer` uses less memory than `StringTokenizer`. When a standard Java solution gets MLE, you can try `StreamTokenizer`, but `StreamTokenizer` may lose precision and can have issues when reading some data;
    -   The `StreamTokenizer` source has a `Type` that determines the token type based on the input. If the input is a string such as `123oi` that **starts with a digit**, it forcibly treats it as a `double`, so reading a `String` as a `double` will throw an exception;
    -   `StreamTokenizer` loses precision when reading numbers larger than `1e14`;
2.  When using `PrintWriter`, remember to call `close()` at the end of the program to close the output stream, or use `flush()` when output is needed to clear the buffer. Otherwise, the content will not be written to the console or file.
3.  `Kattio` extends `PrintWriter`, so its objects have `PrintWriter` functionality and can directly call `PrintWriter` methods for output. It also keeps `StringTokenizer` as a member variable. In the second `Main`, `StreamTokenizer` and `PrintWriter` are both member variables, so usage differs slightly.

In summary, `StringTokenizer` is preferable in most cases. You can try `StreamTokenizer` under extreme MLE conditions, but `StreamTokenizer` cannot properly handle data beyond the `int` range.

## BigInteger and Number Theory

`BigInteger` is Java's arbitrary-precision integer class, which conveniently solves high-precision problems.

### Initialization

There are two common ways to create a `BigInteger`:

```java
import java.io.PrintWriter;
import java.math.BigInteger;

class Main {
    static PrintWriter out = new PrintWriter(System.out);
    public static void main(String[] args) {
        BigInteger a = new BigInteger("12345678910");  // Create a BigInteger object from the string in decimal
        out.println(a);  // The value of a is 12345678910 
        BigInteger b = new BigInteger("1E", 16);  // Create a BigInteger object from the string in the specified radix
        out.println(b);  // The value of b is 30 
        out.close();
    }
}

```

### Basic Operations

The following use `this` to represent the current `BigInteger`:

|             Method             |               Function               |
| :-------------------------: | :----------------------------: |
|           `abs()`           |         Returns the absolute value of `this`         |
|          `negate()`         |         Returns the negation of `this`         |
|    `add(BigInteger val)`    |      Returns the sum of `this` and `val`      |
|  `subtract(BigInteger val)` |      Returns the difference of `this` and `val`      |
|  `multiply(BigInteger val)` |      Returns the product of `this` and `val`      |
|   `divide(BigInteger val)`  |      Returns the quotient of `this` divided by `val`      |
| `remainder(BigInteger val)` |     Returns the remainder of `this` divided by `val`     |
|    `mod(BigInteger val)`    |     Returns `this` modulo `val`     |
|        `pow(int val)`       |      Returns `this` raised to the `val`-th power      |
|    `and(BigInteger val)`    |     Returns the bitwise AND of `this` and `val`     |
|     `or(BigInteger val)`    |     Returns the bitwise OR of `this` and `val`     |
|           `not()`           |         Returns the bitwise complement of `this`        |
|    `xor(BigInteger val)`    |     Returns the bitwise XOR of `this` and `val`    |
|      `shiftLeft(int n)`     |       Returns `this` shifted left by `n` bits       |
|     `shiftRight(int n)`     |       Returns `this` shifted right by `n` bits       |
|    `max(BigInteger val)`    |     Returns the larger of `this` and `val`     |
|    `min(BigInteger val)`    |     Returns the smaller of `this` and `val`     |
|         `bitCount()`        | Returns the number of `1` bits in the binary representation of `this`, excluding the sign bit |
|        `bitLength()`        |    Returns the length of the binary representation of `this`, excluding the sign bit    |
|     `getLowestSetBit()`     |      Returns the position of the rightmost set bit in the binary representation of `this`     |
| `compareTo(BigInteger val)` |      Compares the values of `this` and `val`     |
|         `toString()`        |      Returns the decimal string representation of `this`     |
|    `toString(int radix)`    |  Returns the radix-`radix` string representation of `this` |

Example usage:

```java
import java.io.PrintWriter;
import java.math.BigInteger;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static BigInteger a, b;
    
    static void abs() {
        out.println("abs:");
        a = new BigInteger("-123");
        out.println(a.abs());  // Output 123 
        a = new BigInteger("123");
        out.println(a.abs());  // Output 123 
    }
    
    static void negate() {
        out.println("negate:");
        a = new BigInteger("-123");
        out.println(a.negate());  // Output 123 
        a = new BigInteger("123");
        out.println(a.negate());  // Output -123 
    }
    
    static void add() {
        out.println("add:");
        a = new BigInteger("123");
        b = new BigInteger("123");
        out.println(a.add(b));  // Output 246 
    }
    
    static void subtract() {
        out.println("subtract:");
        a = new BigInteger("123");
        b = new BigInteger("123");
        out.println(a.subtract(b));  // Output 0 
    }
    
    static void multiply() {
        out.println("multiply:");
        a = new BigInteger("12");
        b = new BigInteger("12");
        out.println(a.multiply(b));  // Output 144 
    }
    
    static void divide() {
        out.println("divide:");
        a = new BigInteger("12");
        b = new BigInteger("11");
        out.println(a.divide(b));  // Output 1 
    }
    
    static void remainder() {
        out.println("remainder:");
        a = new BigInteger("12");
        b = new BigInteger("10");
        out.println(a.remainder(b));  // Output 2 
        a = new BigInteger("-12");
        b = new BigInteger("10");
        out.println(a.remainder(b));  // Output -2 
    }
    
    static void mod() {
        out.println("mod:");
        a = new BigInteger("12");
        b = new BigInteger("10");
        out.println(a.mod(b));  // Output 2 
        a = new BigInteger("-12");
        b = new BigInteger("10");
        out.println(a.mod(b));  // Output 8 
    }
    
    static void pow() {
        out.println("pow:");
        a = new BigInteger("2");
        out.println(a.pow(10));  // Output 1024 
    }
    
    static void and() {
        out.println("and:");
        a = new BigInteger("3");  // 11 
        b = new BigInteger("5");  // 101 
        out.println(a.and(b));  // Output 1 
    }
    
    static void or() {
        out.println("or:");
        a = new BigInteger("2");  // 10 
        b = new BigInteger("5");  // 101 
        out.println(a.or(b));  // Output 7 
    }
    
    static void not() {
        out.println("not:");
        a = new BigInteger("2147483647");  // 01111111 11111111 11111111 11111111 
        out.println(a.not());  // Output -2147483648 binary is: 10000000 00000000 00000000 00000000 
    }
    
    static void xor() {
        out.println("xor:");
        a = new BigInteger("6");  // 110 
        b = new BigInteger("5");  // 101 
        out.println(a.xor(b));  // 011 prints 3 
    }
    
    static void shiftLeft() {
        out.println("shiftLeft:");
        a = new BigInteger("1");
        out.println(a.shiftLeft(10));  // Output 1024 
    }
    
    static void shiftRight() {
        out.println("shiftRight:");
        a = new BigInteger("1024");
        out.println(a.shiftRight(8));  // Output 4 
    }
    
    static void max() {
        out.println("max:");
        a = new BigInteger("6");
        b = new BigInteger("5");
        out.println(a.max(b));  // Output 6 
    }
    
    static void min() {
        out.println("min:");
        a = new BigInteger("6");
        b = new BigInteger("5");
        out.println(a.min(b));  // Output 5 
    }
    
    static void bitCount() {
        out.println("bitCount:");
        a = new BigInteger("6");  // 110 
        out.println(a.bitCount());  // Output 2 
    }
    
    static void bitLength() {
        out.println("bitLength:");
        a = new BigInteger("6");  // 110 
        out.println(a.bitLength());  // Output 3 
    }
    
    static void getLowestSetBit() {
        out.println("getLowestSetBit:");
        a = new BigInteger("8");  // 1000 
        out.println(a.getLowestSetBit());  // Output 3 
    }
    
    static void compareTo() {
        out.println("compareTo:");
        a = new BigInteger("8");
        b = new BigInteger("9");
        out.println(a.compareTo(b));  // Output -1 
        a = new BigInteger("8");
        b = new BigInteger("8");
        out.println(a.compareTo(b));  // Output 0 
        a = new BigInteger("8");
        b = new BigInteger("7");
        out.println(a.compareTo(b));  // Output 1 
    }
    
    static void toStringTest() {
        out.println("toString:");
        a = new BigInteger("15");
        out.println(a.toString());  // Output 15 
        out.println(a.toString(16));  // Output f 
    }
    
    public static void main(String[] args) {
        abs();
        negate();
        add();
        subtract();
        multiply();
        divide();
        remainder();
        mod();
        pow();
        and();
        or();
        not();
        xor();
        shiftLeft();
        shiftRight();
        max();
        min();
        bitCount();
        bitLength();
        getLowestSetBit();
        compareTo();
        toStringTest();
        out.close();
    }
}
```

### Mathematical Operations

The following use `this` to represent the current `BigInteger`:

|                  Method                 |                Function                |
| :----------------------------------: | :------------------------------: |
|         `gcd(BigInteger val)`        | Returns the greatest common divisor of the absolute values of `this` and `val` |
|      `isProbablePrime(int val)`      |      Returns a boolean indicating whether `this` is prime     |
|         `nextProbablePrime()`        |        Returns the first prime greater than `this`        |
| `modPow(BigInteger b, BigInteger p)` |    Returns `this` raised to the `b`-th power modulo `p`    |
|      `modInverse(BigInteger p)`      |     Returns the multiplicative inverse of `this` modulo `p`    |

Example usage:

```java
import java.io.PrintWriter;
import java.math.BigInteger;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static BigInteger a, b, p;
    
    static void gcd() {  // Greatest common divisor 
        a = new BigInteger("120032414321432144212100");
        b = new BigInteger("240231431243123412432140");
        out.println(String.format("gcd(%s,%s)=%s", a.toString(), b.toString(), a.gcd(b).toString()));  // gcd(120032414321432144212100,240231431243123412432140)=20 
    }
    
    static void isPrime() {  // Uses Miller-Rabin to determine whether the number is prime. A larger parameter gives higher accuracy and higher complexity. Accuracy is (1-1/(val*2)) 
        a = new BigInteger("1200324143214321442127");
        out.println("a:" + a.toString());
        out.println(a.isProbablePrime(10) ? "a is prime" : "a is not prime");  // a is not prime 
    }
    
    static void nextPrime() {  // Find the next prime after this number 
        a = new BigInteger("1200324143214321442127");
        out.println("a:" + a.toString());
        out.println(String.format("a nextPrime is %s", a.nextProbablePrime().toString()));  // a nextPrime is 1200324143214321442199 
    }
    
    static void modPow() {  // Fast exponentiation, faster than the normal version because it has internal mathematical optimizations 
        a = new BigInteger("2");
        b = new BigInteger("10");
        p = new BigInteger("1000");
        out.println(String.format("a:%s b:%s p:%s", a, b, p));
        out.println(String.format("a^b mod p:%s", a.modPow(b, p).toString()));//  24 
    }
    
    static void modInverse() {  // Inverse 
        a = new BigInteger("10");
        b = new BigInteger("3");
        out.println(a.modInverse(b));  // a ^ (p-2) mod p = 1 
    }
    
    public static void main(String[] args) {
        gcd();
        isPrime();
        nextPrime();
        modPow();
        modInverse();
        out.close();
    }
}
```

For related knowledge about Miller-Rabin, see [Miller-Rabin primality test](../math/number-theory/prime.md#millerrabin-素性测试).

## Primitive Types and Wrapper Types

### Introduction

Because primitive types do not have object-oriented features, Java provides corresponding wrapper classes for the eight primitive types so they can participate in object-oriented development: `Byte`, `Double`, `Float`, `Integer`, `Long`, `Short`, `Character`, and `Boolean`. Their correspondence is as follows:

|   Primitive type  |    Wrapper type   |
| :-------: | :---------: |
|   `byte`  |    `Byte`   |
|  `short`  |   `Short`   |
| `boolean` |  `Boolean`  |
|   `char`  | `Character` |
|   `int`   |  `Integer`  |
|   `long`  |    `Long`   |
|  `float`  |   `Float`   |
|  `double` |   `Double`  |

### Differences

Here, `int` and `Integer` are used as examples:

1.  `Integer` is the wrapper class of `int`, while `int` is a Java primitive data type.
2.  `Integer` can only be used after an instance exists, while `int` does not require this.
3.  `Integer` is actually a reference. When you `new` an `Integer`, an object is created, while `int` stores data directly.
4.  The default value of `Integer` is `null`; it can accept `null` and `int` data. The default value of `int` is 0, and it cannot accept `null`.
5.  Using `==` to determine whether two `Integer` variables are the same may produce incorrect results; use `equals()` instead. For `int`, `==` can be used directly.

### Boxing and Unboxing

Here, `int` and `Integer` are used as examples:

`Integer` is essentially an object, while `int` is a primitive type. The two types cannot be directly assigned to each other. When conversion is needed, converting a primitive type to a wrapper type is called boxing, and the reverse is called unboxing.

```java
// Primitive type
int value1 = 1;
// Boxing: convert to wrapper type
Integer integer = Integer.valueOf(value1);
// Unboxing: convert to primitive type
int value2 = integer.intValue();
```

Java 5 introduced automatic boxing and unboxing:

```java
Integer integer = 1;
int value = integer;
```

???+ warning "Note"
    Although the JDK added automatic boxing and unboxing, choose the appropriate type when declaring variables. The wrapper type `Integer` can accept `null`, while the primitive type `int` cannot. Therefore, unboxing a wrapper type whose value is `null` will throw an exception. The following code demonstrates this behavior.
    
    ```java
    Integer integer = Integer.valueOf(null);
    integer.intValue();  // Throws java.lang.NumberFormatException
    
    Integer integer = null;
    integer.intValue();  // Throws java.lang.NullPointerException
    ```

## Inheritance

Creating a new design based on an existing design is inheritance in object-oriented programming. In inheritance, a new class is not created from nothing; it is defined based on an existing class. Through inheritance, the new class automatically obtains all members of the base class, including member variables and methods, with all kinds of access modifiers, whether `public` or `private`. Obviously, defining a new class through inheritance is much simpler, faster, and more convenient than writing a new class from scratch. Inheritance is one of the important ways to support code reuse.

In Java, the keyword for inheritance is `extends`. Java only supports single inheritance, but a class can implement multiple interfaces.

In Java, all classes are subclasses of `Object`.

When a subclass inherits a superclass, all superclass members, including variables and methods, become members of the subclass except constructors. Constructors belong only to the superclass because their names are the class names, so superclass constructors do not exist in the subclass. Apart from this, the subclass inherits all members of the superclass.

Each member has a different access modifier. The subclass inherits all members of the superclass, but different access modifiers make their use in the subclass different: some superclass members directly become part of the subclass's external interface, while others are deeply hidden and cannot even be directly accessed by the subclass itself.

The following table lists how superclass members with different access modifiers are accessible in a subclass:

|    Superclass member access modifier   |      Meaning in the superclass      |                     Meaning in the subclass                    |
| :-----------: | :---------------: | :--------------------------------------------: |
|    `public`   |       Open to all classes      |                     Open to all classes                     |
|  `protected`  | Accessible only to other classes in the package, itself, and subclasses |                Accessible only to other classes in the package, itself, and subclasses               |
| Default (`default`) |    Accessible only to other classes in the package    | If the subclass and superclass are in the same package, it is accessible to other classes in the package; otherwise, it is equivalent to `private` and cannot be accessed |
|   `private`   |      Accessible only to itself     |                      Cannot be accessed                      |

## Polymorphism

In Java, when assigning an object to a variable, the object type must match the variable type. However, because Java has inheritance, this can be redefined as: **a variable can hold an object of its declared type or any subtype of that type**.

If a type implements an interface, it can also be called a subtype of that interface.

In Java, variables that hold object types are polymorphic variables. The term polymorphism, literally meaning many forms, means that one variable can hold objects of different types, namely its declared type or any subtype.

Polymorphic variables:

1.  Java object variables are polymorphic; they can hold objects of more than one type.
2.  They can hold objects of the declared type or objects of subclasses of the declared type.
3.  Upcasting occurs when an object of a subclass is assigned to a variable of its superclass.

## Generics

Generics mean that the concrete types of attributes or method parameters in a class are not set when the class is defined, but are specified when the class is used or an object is created. Generics are essentially parameterized types: the data type being operated on is specified as a parameter.

Generics provide compile-time type-safety checking, allowing illegal types to be detected during compilation.

## Interfaces

### Introduction

An interface in Java is an abstract type and a collection of abstract methods, usually declared with `interface`. A class inherits the abstract methods of an interface by implementing it.

An interface is not a class. Interfaces are written similarly to classes, but they are different concepts. A class describes the properties and methods of objects, while an interface contains methods that a class must implement.

Unless the class implementing an interface is abstract, it must define all methods in the interface.

Interfaces cannot be instantiated, but they can be implemented. A class that implements an interface must implement all methods described in the interface, otherwise it must be declared abstract. In Java, an interface type can also be used to declare a variable; it can be `null` or bound to an object that implements the interface.

### Differences from Classes

1.  Interfaces cannot be used to instantiate objects.
2.  Interfaces do not have constructors.
3.  All methods in an interface must be abstract methods. After Java 8, interfaces can contain non-abstract methods modified with the `default` keyword.
4.  Interfaces cannot contain member variables except `static` and `final` variables.
5.  Interfaces are not inherited by classes; they are implemented by classes.
6.  Interfaces support multiple inheritance, while classes do not.

### Declaration

```java
[visibility] interface InterfaceName [extends other interface names] {
        // Declare variables
        // Abstract methods
}
```

### Implementation

```java
...implements InterfaceName[, OtherInterfaceName, OtherInterfaceName..., ...] ...
```

## Lambda Expressions

### Introduction

A lambda expression can also be called a closure and is one of the most important new features of Java 8.

Lambda expressions allow functions to be passed as parameters to methods.

Using lambda expressions can make code more concise and compact.

### Syntax

-   Optional type declaration: parameter types do not need to be declared; the compiler can infer them.
-   Optional parentheses around parameters: parentheses are not required for one parameter, but are required for multiple parameters.
-   Optional braces: if the body contains one statement, braces are not required.
-   Optional `return` keyword: if the body has only one expression, the compiler automatically returns its value; braces require explicitly returning a value.

Lambda expressions can be declared as follows:

```java
// 1. No parameter, returns 5
() -> 5

// 2. Takes one parameter (numeric type) and returns twice its value
x -> 2 * x

// 3. Takes two parameters (numbers) and returns their difference
(x, y) -> x – y

// 4. Takes two int integers and returns their sum
(int x, int y) -> x + y

// 5. Takes a String object and prints it to the console, returning no value (appears to return void)
(String s) -> System.out.print(s)
```

For example, with a custom comparator that sorts a string array by length, a lambda expression can be used as follows.

```java
import java.util.Arrays;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    
    public static void main(String[] args) {
        String[] plants = {"Mercury", "venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};
        Arrays.sort(plants, (String first, String second) -> (first.length() - second.length()));
        for (String word : plants) {
            out.print(word + " ");
        }
        out.close();
    }
}
```

Multiple statements can also be used in a lambda expression, as in the following example.

```java
import java.io.PrintWriter;
import java.util.Arrays;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    
    public static void main(String[] args) {
        String[] plants = {"Mercury", "venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};
        Arrays.sort(plants, (first, second) ->
        {
            // Parameter types are omitted and inferred from context
            int result = first.length() - second.length();
            return result;
        });
        for (String word : plants) {
            out.print(word + " ");
        }
        out.close();
    }
}
```

Here, `->` is an inference symbol. It indicates that the preceding parentheses receive parameters and infer the return value after it; essentially, a method is being passed.

### Functional Interfaces

1.  It is an interface and follows Java interface definitions.
2.  It is an interface that contains only one abstract method.
3.  Because there is only one unimplemented method, a lambda expression can automatically fill it in.

Functional interfaces are used as follows:

???+ example "Output strings whose lengths are multiples of 2"
    ```java
    import java.io.PrintWriter;
    
    public class Main {
        static PrintWriter out = new PrintWriter(System.out);
        
        public static void main(String[] args) {
            String[] plants = {"Mercury", "venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};
            Test test = s -> {  // The lambda expression is an instance of the functional interface
                if (s.length() % 2 == 0) {
                    return true;
                }
                return false;
            };
            for (String word : plants) {
                if (test.check(word)) {
                    out.print(word + " ");
                }
            }
            out.close();
        }
    }
    
    interface Test {
        public boolean check(String s);
    }
    ```

???+ example "Implement addition, subtraction, multiplication, and division"
    ```java
    import java.io.PrintWriter;
    
    public class Main {
        static PrintWriter out = new PrintWriter(System.out);
        
        public static double calc(double a, double b, Calculator util) {
            return util.operation(a, b);
        }
        
        public static void main(String[] args) {
            Calculator util[] = new Calculator[4];  // Define an array of functional interfaces
            util[0] = (a, b) -> a + b;
            util[1] = (a, b) -> a - b;
            util[2] = (a, b) -> a * b;
            util[3] = (a, b) -> a / b;
            double a = 20, b = 15;
            for (Calculator c : util) {
                System.out.println(calc(a, b, c));
            }
            out.close();
        }
    }
    
    interface Calculator {
        public double operation(double a, double b);
    }
    ```

## Collection

`Collection` is an interface in Java and is implemented by multiple generic container interfaces. Here, `Collection` refers to data structures that store object types.

In Java, the element type of a `Collection` must be an object type, not a primitive type.

The following usage is based on polymorphism in Java and appears as implementations of interfaces.

Common interfaces include `List`, `Queue`, `Set`, and `Map`.

### Container Definitions

When defining a generic container class, specify the data type at definition time. If no data type is specified and data is added freely as `Object`, it can compile in Java 8, but it causes many warnings and risks.

For example, the following definition is safe because the container only accepts `Integer` values.

```java
List<Integer> list1 = new LinkedList<>();
```

The following definition will produce warnings.

```java
List list = new ArrayList<>();
list.add(1);
list.add(true);
list.add(1.01);
list.add(1L);
list.add("I am String");
```

Therefore, unless there is a special need, the second approach is not recommended. The compiler cannot help check whether stored data is safe. When using `list.get(index)`, the data type cannot be determined clearly because all retrieved values are `Object`; they must be manually cast back to the original type, and an incorrect cast can easily cause an exception.

If the type is explicitly specified, such as `List<Integer>`, the compiler checks the inserted data type and only integer data can be inserted. When declaring collection variables, use wrapper types such as `List<Integer>` or custom `Class` types, not primitive types such as `List<int>`.

### List

#### ArrayList

`ArrayList` is an array that can dynamically grow as needed. Its default initial length is 10. If the current length is exceeded, it expands by $\dfrac{3}{2}$.

##### Initialization

```java
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    
    public static void main(String[] args) {
        List<Integer> list1 = new ArrayList<>();  // Create a dynamically growing array named list1 with the default initial length (10)
        List<Integer> list2 = new ArrayList<>(30);  // Create a dynamically growing array named list2 with initial length 30
        List<Integer> list3 = new ArrayList<>(list2);  // Create a dynamically growing array named list3 using the elements and size of list2 as initial values
    }
}
```

#### LinkedList

`LinkedList` is a doubly linked list.

##### Initialization

```java
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.List;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    
    public static void main(String[] args) {
        List<Integer> list1 = new LinkedList<>();  // Create a doubly linked list named list1 
        List<Integer> list2 = new LinkedList<>(list1);  // Create a doubly linked list named list2 and add all elements from list1 
    }
}
```

#### Common Methods

The following use `this` to represent the current `List<Integer>`:

|            Method            |                Function                |
| :-----------------------: | :------------------------------: |
|          `size()`         |           Returns the length of `this`          |
|     `add(Integer val)`    |      Inserts element `val` at the end of `this`      |
| `add(int idx, Integer e)` |   Inserts element `e` at position `idx` of `this`   |
|       `get(int idx)`      | Returns the value at position `idx` in `this`; throws an exception if out of bounds |
| `set(int idx, Integer e)` |   Changes the value at position `idx` in `this` to `e`   |

Example usage and comparison:

```java
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static List<Integer> array = new ArrayList<>();
    static List<Integer> linked = new LinkedList<>();
    
    static void add() {
        array.add(1);  // time complexity is O(1) 
        linked.add(1);  // time complexity is O(1) 
    }
    
    static void get() {
        array.get(10);  // time complexity is O(1) 
        linked.get(10);  // time complexity is O(11) 
    }
    
    static void addIdx() {
        array.add(0, 2);  // worst-case time complexity is O(n)
        linked.add(0, 2);  // worst-case time complexity is O(n)
    }
    
    static void size() {
        array.size();  // time complexity is O(1)
        linked.size();  // time complexity is O(1)
    }
    
    static void set() {  // This method returns the original value at that position
        array.set(0, 1);  // time complexity is O(1)
        linked.set(0, 1);  // worst-case time complexity is O(n)
    }

}
```

#### Traversal

```java
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static List<Integer> array = new ArrayList<>();
    static List<Integer> linked = new LinkedList<>();
    
    static void function1() {  // Naive traversal
        for (int i = 0; i < array.size(); i++) {
            out.println(array.get(i));  // Traverse the dynamically growing array; complexity is O(n)
        }
        for (int i = 0; i < linked.size(); i++) {
            out.println(linked.get(i));  // Traverse the doubly linked list; complexity is O(n^2) because LinkedList get(i) has complexity O(i)
        }
    }
    
    static void function2() {  // Enhanced for-loop traversal 
        for (int e : array) {
            out.println(e);
        }
        for (int e : linked) {
            out.println(e);  // complexity is O(n) 
        }
    }
    
    static void function3() {  // Iterator traversal 
        Iterator<Integer> iterator1 = array.iterator();
        Iterator<Integer> iterator2 = linked.iterator();
        while (iterator1.hasNext()) {
            out.println(iterator1.next());
        }
        while (iterator2.hasNext()) {
            out.println(iterator2.next());
        }  // complexity is O(n) 
    }

}
```

???+ warning "Note"
    Do not delete elements from a `List` while traversing it with `for` or `foreach`; otherwise, an exception will be thrown.
    
    The reason is simple: `list.size()` changes, but the number of loop iterations already performed does not. Data originally expected at the next `index` becomes the data at the current `index` after deletion, and the next loop operates on data originally expected two positions later. This ultimately causes the operated data to differ from expectations.

### Queue

#### LinkedList

A normal queue can be implemented with `LinkedList`; internally, it simulates a queue with a linked list.

##### Initialization

```java
Queue<Integer> q = new LinkedList<>();
```

`LinkedList` implements the `List` and `Deque` interfaces internally, and `Deque` extends `Queue`, so `LinkedList` can implement both `List` and `Queue`.

#### ArrayDeque

A normal queue can be implemented with `ArrayDeque`; internally, it simulates a queue with an array.

##### Initialization

```java
Queue<Integer> q = new ArrayDeque<>();
```

`ArrayDeque` implements the `Deque` interface internally, and `Deque` extends `Queue`, so `ArrayDeque` can implement `Queue`.

#### Differences Between LinkedList and ArrayDeque When Implementing Queue

1.  Data structure: both `ArrayDeque` and `LinkedList` implement Java's `Deque` double-ended queue interface. However, `ArrayDeque` does not implement the Java `List` interface, so it does not support index-based operations.
2.  Thread safety: neither `ArrayDeque` nor `LinkedList` handles thread synchronization, so neither guarantees thread safety.
3.  Underlying implementation: `ArrayDeque` is based on a dynamic array, while `LinkedList` is based on a doubly linked list.
4.  Traversal speed: `ArrayDeque` uses contiguous memory, which can better hit CPU cache lines due to locality, while `LinkedList` uses scattered memory and is cache-unfriendly.
5.  Operation speed: stack and queue operations for both `ArrayDeque` and `LinkedList` are $O(1)$. Push and enqueue operations in `ArrayDeque` may trigger expansion, but amortized analysis still gives $O(1)$ time complexity.
6.  Extra memory usage: `ArrayDeque` has unused space outside the array head and tail pointers, while `LinkedList` adds predecessor and successor pointers to each node.

#### PriorityQueue

`PriorityQueue` is a priority queue. By default, it is a min-heap.

##### Initialization

```java
Queue<Integer> q1 = new PriorityQueue<>();  // Min-heap
Queue<Integer> q2 = new PriorityQueue<>((x, y) -> {return y - x;});  // Max-heap
```

#### Common Methods

In the following table, the queue is defined as `Queue<Integer>`.

|          Method         |                     Function                     |
| :------------------: | :----------------------------------------: |
|       `size()`       |                  Returns the current queue length                  |
|  `add(Integer val)`  |     Inserts `val` into the queue; throws an exception if insertion violates the queue capacity limit     |
| `offer(Integer val)` | Inserts `val` into the queue; if insertion violates the queue capacity limit, insertion fails but no exception is thrown |
|      `isEmpty()`     |            Determines whether the queue is empty; returns `true` if it is           |
|       `peek()`       |            Returns the front element; returns `null` if the queue is empty           |
|       `poll()`       |          Returns and removes the front element; returns `null` if the queue is empty          |

Example usage and comparison:

```java
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static Queue<Integer> q1 = new LinkedList<>();
    static Queue<Integer> q2 = new PriorityQueue<>();
    
    static void add() {  // add and offer have no functional difference; the difference is whether an exception is thrown 
        q1.add(1);  // time complexity is O(1) 
        q2.add(1);  // time complexity is O(logn) 
    }
    
    static void isEmpty() {
        q1.isEmpty();  // time complexity is O(1) 
        q2.isEmpty();  // space complexity is O(1) 
    }
    
    static void size() {
        q1.size();  // time complexity is O(1) 
        q2.size();  // Returns the length of q2 
    }
    
    static void peek() {
        q1.peek();  // time complexity is O(1) 
        q2.peek();  // time complexity is O(logn) 
    }
    
    static void poll() {
        q1.poll();  // time complexity is O(1) 
        q2.poll();  // time complexity is O(logn) 
    }
}
```

#### Traversal

```java
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static Queue<Integer> q1 = new LinkedList<>();
    static Queue<Integer> q2 = new PriorityQueue<>();
    
    static void test() {
        while (!q1.isEmpty()) {  // complexity is O(n) 
            out.println(q1.poll());
        }
        while (!q2.isEmpty()) {  // complexity is O(nlogn) 
            out.println(q2.poll());
        }
    }

}
```

### Deque

`Deque` is a double-ended queue in `Java`; it is usually used for queue operations and stack operations.

#### Main Methods

In the following table, the queue is defined as `Deque<Integer>`.

|            Method            |                     Function                     |
| :-----------------------: | :----------------------------------------: |
|  `addFirst(Integer val)`  |     Inserts `val` at the front; throws an exception if insertion violates the queue capacity limit     |
| `offerFirst(Integer val)` | Inserts `val` at the front; if insertion violates the queue capacity limit, insertion fails but no exception is thrown |
|      `removeFirst()`      |           Returns and removes the front element; throws an exception if the queue is empty           |
|       `pollFirst()`       |         Returns and removes the front element; returns `null` if the queue is empty        |
|       `peekFirst()`       |          Returns the front element; returns `null` if the queue is empty          |
|    `push(Integer val)`    |         Inserts `val` at the front; equivalent to `addFirst`        |
|          `pop()`          |         Returns and removes the front element; equivalent to `removeFirst`        |
|         `remove()`        |          Removes the front element; equivalent to `removeFirst`          |
|          `poll()`         |           Removes the front element; equivalent to `pollFirst`           |
|   `addLast(Integer val)`  |     Inserts `val` at the back; throws an exception if insertion violates the queue capacity limit     |
|  `offerLast(Integer val)` | Inserts `val` at the back; if insertion violates the queue capacity limit, insertion fails but no exception is thrown |
|       `removeLast()`      |           Returns and removes the back element; throws an exception if the queue is empty           |
|        `pollLast()`       |         Returns and removes the back element; returns `null` if the queue is empty        |
|        `peekLast()`       |          Returns the back element; returns `null` if the queue is empty          |
|     `add(Integer val)`    |         Inserts `val` at the back; equivalent to `addLast`         |
|    `offer(Integer val)`   |        Inserts `val` at the back; equivalent to `offerLast`        |

#### Stack Operations

```java
import java.util.ArrayDeque;
import java.util.Deque;

public class Main {
    static Deque<Integer> stack = new ArrayDeque<>();
    static int[] a = {1, 2, 3, 4, 5};
    
    public static void main(String[] args) {
        for (int v : a) {
            stack.push(v);
        }
        while (!stack.isEmpty()) { // prints 5 4 3 2 1
            System.out.println(stack.pop()); 
        }
    }
}

```

#### Deque Operations

```java
import java.util.ArrayDeque;
import java.util.Deque;

public class Main {
    static Deque<Integer> deque = new ArrayDeque<>();
    
    static void insert() {
        deque.addFirst(1);
        deque.addFirst(2);
        deque.addLast(3);
        deque.addLast(4);
    }
    
    public static void main(String[] args) {
        insert();
        while (!deque.isEmpty()) { // prints 2 1 3 4
            System.out.println(deque.poll());
        }
        insert();
        while (!deque.isEmpty()) { // prints 4 3 1 2
            System.out.println(deque.pollLast());
        }
    }
}
```

### Set

`Set` is a data structure that keeps elements in a container unique.

#### HashSet

A `Set` with insertion at arbitrary positions.

##### Initialization

```java
Set<Integer> s1 = new HashSet<>();
```

#### LinkedHashSet

A `Set` that preserves insertion order.

##### Initialization

```java
Set<Integer> s2 = new LinkedHashSet<>();
```

#### TreeSet

A `Set` that keeps the elements in the container ordered; the default is ascending order.

##### Initialization

```java
Set<Integer> s3 = new TreeSet<>();
Set<Integer> s4 = new TreeSet<>((x, y) -> {return y - x;});  // Descending order 
```

##### More TreeSet Usage

These methods are newly created and implemented by `TreeSet`. We cannot call the following methods through the `Set` interface, so we create it as follows:

```java
TreeSet<Integer> s3 = new TreeSet<>();
TreeSet<Integer> s4 = new TreeSet<>((x, y) -> {return y - x;});  // Descending order
```

In the following table, `this` represents the current `TreeSet<Integer>`.

|           Method          |                    Function                    |
| :--------------------: | :--------------------------------------: |
|        `first()`       |       Returns the first element in `this`; returns `null` if none exists       |
|        `last()`        |       Returns the last element in `this`; returns `null` if none exists      |
|  `floor(Integer val)`  | Returns the first element in `this` less than or equal to `val`; returns `null` if none exists |
| `ceiling(Integer val)` | Returns the first element in `this` greater than or equal to `val`; returns `null` if none exists |
|  `higher(Integer val)` |  Returns the first element in `this` greater than `val`; returns `null` if none exists  |
|  `lower(Integer val)`  |  Returns the first element in `this` less than `val`; returns `null` if none exists  |
|      `pollFirst()`     |      Returns and removes the first element in `this`; returns `null` if none exists     |
|      `pollLast()`      |     Returns and removes the last element in `this`; returns `null` if none exists     |

Code example:

```java
import java.util.TreeSet;

public class Main {
    static int[] a = {4,7,1,2,3,6};
    
    public static void main(String[] args) {
        TreeSet<Integer> set = new TreeSet<>();
        for(int v:a) {
            set.add(v);
        }
        Integer a2 = set.first();
        System.out.println(a2); // returns 1
        Integer a3 = set.last();
        System.out.println(a3); // returns 7
        Integer a4 = set.floor(5);
        System.out.println(a4); // returns 4
        Integer a5 = set.ceiling(6);
        System.out.println(a5); // returns 6
        Integer a6 = set.higher(7);
        System.out.println(a6); // returns null
        Integer a7 = set.lower(2);
        System.out.println(a7); // returns 1
        Integer a8 = set.pollFirst();
        System.out.println(a8); // returns 1
        Integer a9 = set.pollLast();
        System.out.println(a9); // returns 7
    }
}
```

#### Common Set Methods

|            Method            |                   Function                   |
| :-----------------------: | :------------------------------------: |
|          `size()`         |                Returns the current set size               |
|     `add(Integer val)`    |              Inserts `val` into the set              |
|  `contains(Integer val)`  |            Determines whether the set contains element `val`            |
|   `addAll(Collection e)`  |          Adds all elements in container `e` to the current set         |
| `retainAll(Collection e)` | Deletes elements in the current set that do not appear in container `e`, i.e., computes the intersection of the current set and `e` |
| `removeAll(Collection e)` |  Deletes elements in the current set that appear in container `e`, i.e., computes the difference of the current set and `e` |

```java
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.Set;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static Set<Integer> s1 = new HashSet<>();
    static Set<Integer> s2 = new LinkedHashSet<>();
    
    static void add() {
        s1.add(1);
    }
    
    static void contains() {  // Checks whether set contains an element with value 2; returns true if so, otherwise false 
        s1.contains(2);
    }
    
    static void test1() {  // Union of s1 and s2 
        Set<Integer> res = new HashSet<>();
        res.addAll(s1);
        res.addAll(s2);
    }
    
    static void test2() {  // Intersection of s1 and s2 
        Set<Integer> res = new HashSet<>();
        res.addAll(s1);
        res.retainAll(s2);
    }
    
    static void test3() {  // Difference: s1 - s2 
        Set<Integer> res = new HashSet<>();
        res.addAll(s1);
        res.removeAll(s2);
    }
}
```

#### Traversal

```java
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.Set;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static Set<Integer> s1 = new HashSet<>();
    static Set<Integer> s2 = new LinkedHashSet<>();
    
    static void test() {
        for (int key : s1) {
            out.println(key);
        }
        out.close();
    }
}
```

### Map

`Map` is a data structure that maintains key-value pairs `<Key, Value>`, where each `Key` is unique.

#### HashMap

A `Map` with insertion at arbitrary positions.

##### Initialization

```java
Map<Integer, Integer> map1 = new HashMap<>();
```

#### LinkedHashMap

A `Map` that preserves insertion order.

##### Initialization

```java
Map<Integer, Integer> map2 = new LinkedHashMap<>();
```

#### TreeMap

A `Map` that keeps `key` values ordered; the default is ascending order.

##### Initialization

```java
Map<Integer, Integer> map3 = new TreeMap<>();
Map<Integer, Integer> map4 = new TreeMap<>((x, y) -> {return y - x;});  // Descending order
```

#### Common Methods

The following use `this` to represent the current `Map<Integer, Integer>`:

|                Method                |               Function              |
| :-------------------------------: | :---------------------------: |
| `put(Integer key, Integer value)` |   Inserts `<key, value>` into `this`  |
|              `size()`             |         Returns the size of `this`         |
|     `containsKey(Integer key)`    | Determines whether `this` contains an element whose key is `key` |
|         `get(Integer key)`        |  Returns the value corresponding to the element whose key is `key` in `this`  |
|             `keySet()`            |     Returns the keys of all elements in `this` as a set    |

Example usage:

```java
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.TreeMap;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    
    static Map<Integer, Integer> map1 = new HashMap<>();
    static Map<Integer, Integer> map2 = new LinkedHashMap<>();
    static Map<Integer, Integer> map3 = new TreeMap<>();
    static Map<Integer, Integer> map4 = new TreeMap<>((x,y)->{return y-x;});
    
    static void put(){  // Inserts the element whose key is 1 and value is 1
        map1.put(1, 1);
    }
    static void get(){  // Returns the value whose key is 1
        map1.get(1);
    }
    static void containsKey(){  // Checks whether there is a key-value pair whose key is 1
        map1.containsKey(1);
    }
    static void KeySet(){
        map1.keySet();
    }
}
```

#### Traversal

```java
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    
    static Map<Integer, Integer> map1 = new HashMap<>();
    
    static void print() {
        for (int key : map1.keySet()) {
            out.println(key + " " + map1.get(key));
        }
    }
}
```

Of course, the key and value types can also be changed. For example, `Map` can also be defined as:

```java
Map<String, Set<Integer>> map = new HashMap<>();
```

## Arrays

`Arrays` is a utility class in `java.util` for array operations. Its methods are all static and can be called directly with the class name.

### Arrays.sort()

`Arrays.sort()` is a method for sorting arrays. Its main overloaded methods are as follows:

```java
import java.util.Arrays;
import java.util.Comparator;

public class Main {
    static int[] a = new int[10];
    static Integer[] b = new Integer[10];
    static int firstIdx, lastIdx;
    
    public static void main(String[] args) {
        Arrays.sort(a);  // 1 
        Arrays.sort(a, firstIdx, lastIdx);  // 2 
        Arrays.sort(b, new Comparator<Integer>() {  // 3 
            @Override
            public int compare(Integer o1, Integer o2) {
                return o2 - o1;
            }
        });
        Arrays.sort(b, firstIdx, lastIdx, new Comparator<Integer>() {  // 4 
            @Override
            public int compare(Integer o1, Integer o2) {
                return o2 - o1;
            }
        });
        // Since Java 8 supports lambda expressions, the third and fourth overloads can also be written as 
        Arrays.sort(b, (x, y) -> {  // 5 
            return y - x;
        });
        Arrays.sort(b, (x, y) -> {  // 6 
            return y - x;
        });
    }
}
```

Meanings of the numbered overloads:

1.  Sorts array `a` in ascending order by default.
2.  Sorts the specified range of array `a` in ascending order by default. The sorting interval is left-closed and right-open: `[firstIdx, lastIdx)`.
3.  Sorts array `a` with a custom order. The second parameter minus the first parameter gives descending order, and the first parameter minus the second parameter gives ascending order. When using a custom comparator, the array element type must be an object type.
4.  Sorts the specified range of array `a` with a custom order. The sorting interval is left-closed and right-open: `[firstIdx, lastIdx)`. When using a custom comparator, the array element type must be an object type.
5.  Same as 3, using a lambda expression to shorten the code.
6.  Same as 4, using a lambda expression to shorten the code.

???+ note "Underlying Function of `Arrays.sort()`"
    1.  When the array element type passed to `Arrays.sort` is a primitive type (`byte`, `short`, `char`, `int`, `long`, `double`, `float`), it uses `DualPivotQuicksort` by default, whose worst-case complexity can reach $O(n^2)$.
    2.  When the array element type passed to `Arrays.sort` is not a primitive type, it uses `legacyMergeSort` and `TimSort` (merge sort) by default, with complexity $O(n\log n)$.

This can be verified with the following code:

???+ example "[Codeforces 1646B - Quality vs Quantity](https://codeforces.com/problemset/problem/1646/B)"
    There are $n$ integers. You need to divide them into two groups and determine whether one group can have a smaller size than the other while having a larger sum.

??? note "Example Code"
    ```java
    import java.io.BufferedReader;
    import java.io.IOException;
    import java.io.InputStreamReader;
    import java.io.PrintWriter;
    import java.util.Arrays;
    import java.util.StringTokenizer;
    
    public class Main {
        static class FastReader {
            StringTokenizer st;
            BufferedReader br;
            
            public FastReader() {
                br = new BufferedReader(new InputStreamReader(System.in));
            }
            
            String next() {
                while (st == null || !st.hasMoreElements()) {
                    try {
                        st = new StringTokenizer(br.readLine());
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
                return st.nextToken();
            }
            
            int nextInt() {
                return Integer.parseInt(next());
            }
            
            long nextLong() {
                return Long.parseLong(next());
            }
            
            double nextDouble() {
                return Double.parseDouble(next());
            }
            
            String nextLine() {
                String str = "";
                try {
                    str = br.readLine();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                return str;
            }
        }
        
        static PrintWriter out = new PrintWriter(System.out);
        static FastReader in = new FastReader();
        
        static void solve() {
            int n = in.nextInt();
            // Changing the array type from Integer to int here will cause TLE
            Integer[] a = new Integer[n + 10];
            for (int i = 1; i <= n; i++) {
                a[i] = in.nextInt();
            }
            Arrays.sort(a, 1, n + 1);
            long left = a[1];
            long right = 0;
            int x = n;
            for (int i = 2; i < x; i++, x--) {
                left = left + a[i];
                right = right + a[x];
                if (right > left) {
                    out.println("YES");
                    return;
                }
            }
            out.println("NO");
        }
        
        public static void main(String[] args) {
            int t = in.nextInt();
            while (t-- > 0) {
                solve();
            }
            out.close();
        }
    }
    ```

### Arrays.binarySearch()

`Arrays.binarySearch()` performs binary search on a contiguous interval of an array. The array must be sorted first. Its time complexity is $O(\log_n)$. The main overloaded methods are as follows:

```java
import java.util.Arrays;

public class Main {
    static int[] a = new int[10];
    static Integer[] b = new Integer[10];
    static int firstIdx, lastIdx;
    static int key;
    
    public static void main(String[] args) {
        Arrays.binarySearch(a, key);  // 1 
        Arrays.binarySearch(a, firstIdx, lastIdx, key);  // 2 
    }
}
```

Source code:

```java
private static int binarySearch0(int[] a, int fromIndex, int toIndex, int key) {
    int low = fromIndex;
    int high = toIndex - 1;
    
    while (low <= high) {
        int mid = (low + high) >>> 1;
        int midVal = a[mid];
        
        if (midVal < key)
            low = mid + 1;
        else if (midVal > key)
            high = mid - 1;
        else
            return mid; // key found
    }
    return -(low + 1);  // key not found.
}
```

Meanings of the numbered overloads:

1.  Binary-searches array `a` for `key`. If it exists, returns its index; otherwise, returns a negative number.
2.  Binary-searches array `a` for `key`. If it exists, returns its index. The search interval is left-closed and right-open: `[firstIdx,lastIdx)`. If it does not exist, returns a negative number.

### Arrays.fill()

`Arrays.fill()` assigns the same value to elements in a contiguous range of an array. It accepts the array, `fromIndex`, `toIndex`, and the value to fill. After execution, all elements in the left-closed, right-open interval `[firstIdx,lastIdx)` have the filled value.

## Collections

`Collections` is a utility class in `java.util` for collection operations. Its methods are all static and can be called directly with the class name.

### Collections.sort()

The underlying principle of `Collections.sort()` is to convert all elements into an array, call `Arrays.sort()`, and then assign the sorted values back to the original collection. Because `Collection` element types in Java are object types, merge sort is always used.

This method cannot sort a specified interval of a collection.

Underlying source code:

```java
default void sort(Comparator<? super E> c) {
    Object[] a = this.toArray();
    Arrays.sort(a, (Comparator) c);
    ListIterator<E> i = this.listIterator();
    for (Object e : a) {
        i.next();
        i.set((E) e);
    }
}
```

### Collections.binarySearch()

`Collections.binarySearch()` performs binary search on a collection, with the same function as `Arrays.binarySearch()`.

```java
Collections.binarySearch(list, key);
```

This method cannot search a specified interval.

### Collections.swap()

`Collections.swap()` swaps the elements at two specified positions in a collection.

```java
 Collections.swap(list, i, j);
```

## Others

### Numeric Comparison Issue

In Java, for pure numeric types, `-0.0 = 0.0`. For object types, `-0.0 != 0.0`. If you try to use a `Set` to count the number of slopes, this issue can cause trouble. The provided solution is to add `0.0` to every slope before adding it to the `Set`.

```java
import java.io.PrintWriter;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    
    static void A() {
        Double a = 0.0;
        Double b = -0.0;
        out.println(a.equals(b));  // false 
    }
    
    static void B() {
        Double a = 0.0;
        Double b = -0.0 + 0.0;
        out.println(a.equals(b));  // true 
    }
    
    static void C() {
        double a = 0.0;
        double b = -0.0;
        out.println(a == b);  // true 
    }
    
    
    public static void main(String[] args) {
        A();
        B();
        C();
        out.close();
    }
}
```

## References

[^ref1]: [Input & Output - USACO Guide](https://usaco.guide/general/input-output?lang=java#method-3---io-template)
