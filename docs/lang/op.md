author: aofall, greyqz, Ir1d, Link-cute, Marcythm, ouuan, Shen-Linwood, sshwy, StudyingFather

## Arithmetic Operators

| Operator | Function |
| --------- | --- |
| `+` (unary) | Positive |
| `-` (unary) | Negative |
| `*` (binary) | Multiplication |
| `/` | Division |
| `%` | Modulo |
| `+` (binary) | Addition |
| `-` (binary) | Subtraction |

??? note "Unary and binary operators"
    A unary operator, also called a monadic operator, has only one operand, while a binary operator has two operands. For example, the plus sign in `1 + 2` is a binary operator with operands `1` and `2`. C++ also has exactly one ternary operator, `?:`.

Arithmetic operators include two unary operators, positive and negative, and five binary operators: multiplication, division, modulo, addition, and subtraction. Unary operators have the highest precedence among them.

The modulo operator `%` means computing the remainder after dividing two integers.

When `-` is a binary operator, it performs subtraction, as in `2-1`; when it is a unary operator, it performs negation, as in `-1`.

Usage example:

 `op=x-y*z` 

The computed value of `op` follows the usual mathematical precedence of addition, subtraction, multiplication, and division. Higher-precedence operations are performed first; operations with the same precedence follow associativity; parentheses raise precedence.

### Type Conversions in Arithmetic Operations

For binary arithmetic operators, if the two participating variables have the same type, no [type conversion](./var.md#类型转换) occurs, and the result is stored in the type of the participating variables. Otherwise, type conversion occurs so the two variables have the same type. See [type conversion](./var.md#类型转换) for the conversion rules.

For example, for an integer (`int`) variable $x$ and a double-precision floating-point (`double`) variable $y$:

-  The result of `x/3` is an integer.
-  The result of `x/3.0` is a double-precision floating-point value.
-  The result of `x/y` is a double-precision floating-point value.
-  The result of `x*1/3` is an integer.
-  The result of `x*1.0/3` is a double-precision floating-point value.

## Bitwise Operators

See also: [bit operations](../math/bit.md#位运算).

| Operator | Function |
| --------- | ---- |
| `~` | Bitwise NOT |
| `&` (binary) | Bitwise AND |
| `|` | Bitwise OR |
| `^` | Bitwise XOR |
| `<<` | Bitwise left shift |
| `>>` | Bitwise right shift |

For the meaning of bitwise operations, see the [bit operations](../math/bit.md) page. Note that bitwise operators have lower precedence than arithmetic operators except bitwise NOT, and bitwise AND, OR, and XOR have lower precedence than comparison operators. See the [complete C++ operator precedence table](#complete-c-operator-precedence-table), so add parentheses when necessary.

In shift operations, behavior is undefined in the following cases:

1.  The right operand, that is, the shift count, is negative.
2.  The right operand is greater than or equal to the number of bits in the left operand.

For example, for a variable `a` of type `int32_t`, both `a<<-1` and `a<<32` are undefined.

For left shifts of signed nonnegative numbers, ensure that the shifted result can be represented by the original type; otherwise the behavior is also undefined.[^note1] Left-shifting a negative number is also undefined.[^note2]

For right shifts, extra bits on the right are discarded. The left side is more complicated: for unsigned numbers, $0$ is filled on the left[^note3]; for signed numbers, the highest bit, which is the sign bit, is used for filling, with $0$ for nonnegative numbers and $1$ for negative numbers[^note4].

## Increment/Decrement Operators

Sometimes we need to increase a variable by 1 (increment) or decrease it by 1 (decrement). The increment operator `++` and decrement operator `--` are used for this.

Increment/decrement operators can be placed before or after a variable. Before the variable is called prefix, and after the variable is called postfix. When used alone, there is no need to distinguish prefix from postfix; if the expression value is used, pay attention to the difference. See the examples below. For details, see the examples in [references](./reference.md).

```cpp
i = 100;

op1 = i++;  // op1 = 100; first op1 = i, then i = i + 1

i = 100;

op2 = ++i;  // op2 = 101; first i = i + 1, then assign to op2

i = 100;

op3 = i--;  // op3 = 100; first assign to op3, then i = i - 1

i = 100;

op4 = --i;  // op4 = 99; first i = i - 1, then assign to op4
```

## Compound Assignment Operators

Compound assignment operators are shorthand forms of expressions. They include compound arithmetic operators `+=`, `-=`, `*=`, `/=`, `%=` and compound bitwise operators `&=`, `|=`, `^=`, `<<=`, `>>=`.

For example, `op = op + 2` can be written as `op += 2`, `op = op - 2` as `op -= 2`, and `op= op * 2` as `op *= 2`.

## Conditional Operator

The conditional operator can be viewed as shorthand for an `if` statement. In `a ? b : c`, if expression `a` is true, the result of this conditional expression is `b`; otherwise, the result is `c`.

## Comparison Operators

| Operator | Function |
| ------ | ---- |
| `>` | Greater than |
| `>=` | Greater than or equal to |
| `<` | Less than |
| `<=` | Less than or equal to |
| `==` | Equal to |
| `!=` | Not equal to |

Pay special attention to distinguishing the equality operator `==` from the assignment operator `=`, especially in conditional statements.

 `if (op=1)` and `if (op==1)` look similar, but their actual functions are very different. The first statement assigns to `op`; if the assigned value is nonzero, the condition is always satisfied, so it does not serve as a test. The second statement tests the value of `op`.

## Logical Operators

| Operator | Function |
| ------ | --- |
| `&&` | Logical AND |
| `||` | Logical OR |
| `!` | Logical NOT |

```cpp
Result = op1 && op2;  // Result is true when both op1 and op2 are true

Result = op1 || op2;  // Result is true when either op1 or op2 is true

Result = !op1;  // Result is true when op1 is false
```

The **built-in** operators `&&` and `||` perform short-circuit evaluation: if the result is already known after evaluating the first operand, the second operand is not evaluated. Overloaded operators do not have this property and always evaluate both operands.

## Comma Operator

The comma operator separates multiple expressions. The separated expressions are evaluated from left to right, and the value of the entire expression is the value of the last expression. The comma expression has the **lowest** precedence among all operators.

```cpp
exp1, exp2, exp3;  // The final value is the result of exp3.

Result = 1 + 2, 3 + 4, 5 + 6;
// Result is 3, not 11, because the assignment operator "=" has higher
// precedence than the comma operator, so assignment is performed before the comma operation.

Result = (1 + 2, 3 + 4, 5 + 6);

// To make Result obtain the result of the comma expression, enclose the entire
// expression in parentheses to raise precedence; then Result is 11.
```

## Member Access Operators

| Operator | Function |
| --------- | -------- |
| `[]` | Array subscript |
| `.` | Object member |
| `&` (unary) | Address-of/get reference |
| `*` (unary) | Indirection/dereference |
| `->` | Pointer member |

These operators are used to access object members or memory. Except for the last operator, all the operators above can be overloaded. For content related to `&`, `*`, and `->`, read the [pointers](./pointer.md) and [references](./reference.md) tutorials. Two rarely used operators, `.*` and `->*`, are omitted here; for their specific usage, see the [C++ language manual](https://en.cppreference.com/w/cpp/language/operator_member_access).

```cpp
auto result1 = v[1];  // Get the object in v with subscript 2
auto result2 = p.q;   // Get member q of object p
auto result3 = p -> q;  // Get member q of the object pointed to by p, equivalent to (*p).q
auto result4 = &v;      // Get a pointer to v
auto result5 = *v;      // Get the object pointed to by pointer v
```

## Complete C++ Operator Precedence Table

From [C++ operator precedence - cppreference](https://en.cppreference.com/w/cpp/language/operator_precedence), with modifications.

| Operator | Description | Example | Overloadable |
| :------------------: | :------: | :----------------------------------------------------------: | :--: |
| **Level 1** | | | |
| `::` | Scope resolution | `Class::age = 2;` | No |
| **Level 2** | | | |
| `++` | Post-increment | `for (int i = 0; i < 10; i++) cout << i;` | Yes |
| `--` | Post-decrement | `for (int i = 10; i > 0; i--) cout << i;` | Yes |
| `type()  type{}` | Functional cast | `unsigned int a = unsigned(3.14);` | Yes |
| `()` | Function call | `isdigit('1')` | Yes |
| `[]` | Array subscript | `array[4] = 2;` | Yes |
| `.` | Object member access | `obj.age = 34;` | No |
| `->` | Pointer member access | `ptr->age = 34;` | Yes |
| **Level 3** (right-to-left) | | | |
| `++` | Pre-increment | `for (i = 0; i < 10; ++i) cout << i;` | Yes |
| `--` | Pre-decrement | `for (i = 10; i > 0; --i) cout << i;` | Yes |
| `+` | Positive | `int i = +1;` | Yes |
| `-` | Negative | `int i = -1;` | Yes |
| `!` | Logical NOT | `if (!done) …` | Yes |
| `~` | Bitwise NOT | `flags = ~flags;` | Yes |
| `(type)` | C-style cast | `int i = (int) floatNum;` | Yes |
| `*` | Dereference | `int data = *intPtr;` | Yes |
| `&` | Address-of | `int *intPtr = &data;` | Yes |
| `sizeof` | Type memory size | `int size = sizeof floatNum; int size = sizeof(float);` | No |
| `new` | Dynamic object allocation | `long *pVar = new long; MyClass *ptr = new MyClass(args);` | Yes |
| `new []` | Dynamic array allocation | `long *array = new long[n];` | Yes |
| `delete` | Dynamic object deallocation | `delete pVar;` | Yes |
| `delete []` | Dynamic array deallocation | `delete [] array;` | Yes |
| **Level 4** | | | |
| `.*` | Object member pointer access | `obj.*var = 24;` | No |
| `->*` | Pointer member pointer access | `ptr->*var = 24;` | Yes |
| **Level 5** | | | |
| `*` | Multiplication | `int i = 2 * 4;` | Yes |
| `/` | Division | `float f = 10.0 / 3.0;` | Yes |
| `%` | Remainder (modulo) | `int rem = 4 % 3;` | Yes |
| **Level 6** | | | |
| `+` | Addition | `int i = 2 + 3;` | Yes |
| `-` | Subtraction | `int i = 5 - 1;` | Yes |
| **Level 7** | | | |
| `<<` | Bitwise left shift | `int flags = 33 << 1;` | Yes |
| `>>` | Bitwise right shift | `int flags = 33 >> 1;` | Yes |
| **Level 8** | | | |
| `<=>` | Three-way comparison operator | `if ((i <=> 42) < 0) ...` | Yes |
| **Level 9** | | | |
| `<` | Less than | `if (i < 42) ...` | Yes |
| `<=` | Less than or equal to | `if (i <= 42) ...` | Yes |
| `>` | Greater than | `if (i > 42) ...` | Yes |
| `>=` | Greater than or equal to | `if (i >= 42) ...` | Yes |
| **Level 10** | | | |
| `==` | Equal to | `if (i == 42) ...` | Yes |
| `!=` | Not equal to | `if (i != 42) ...` | Yes |
| **Level 11** | | | |
| `&` | Bitwise AND | `flags = flags & 42;` | Yes |
| **Level 12** | | | |
| `^` | Bitwise XOR | `flags = flags ^ 42;` | Yes |
| **Level 13** | | | |
| `|` | Bitwise OR | `flags = flags | 42;` | Yes |
| **Level 14** | | | |
| `&&` | Logical AND | `if (conditionA && conditionB) ...` | Yes |
| **Level 15** | | | |
| `||` | Logical OR | `if (conditionA || conditionB) ...` | Yes |
| **Level 16** (right-to-left) | | | |
| `? :` | Conditional operator | `int i = a > b ? a : b;` | No |
| `throw` | Throw exception | `throw EClass("Message");` | No |
| `=` | Assignment | `int a = b;` | Yes |
| `+=` | Addition assignment | `a += 3;` | Yes |
| `-=` | Subtraction assignment | `b -= 4;` | Yes |
| `*=` | Multiplication assignment | `a *= 5;` | Yes |
| `/=` | Division assignment | `a /= 2;` | Yes |
| `%=` | Modulo assignment | `a %= 3;` | Yes |
| `<<=` | Left-shift assignment | `flags <<= 2;` | Yes |
| `>>=` | Right-shift assignment | `flags >>= 2;` | Yes |
| `&=` | Bitwise AND assignment | `flags &= new_flags;` | Yes |
| `^=` | Bitwise XOR assignment | `flags ^= new_flags;` | Yes |
| `|=` | Bitwise OR assignment | `flags |= new_flags;` | Yes |
| **Level 17** | | | |
| `,` | Comma separator | `for (i = 0, j = 0; i < 10; i++, j++) ...` | Yes |

Note that the table does not list operators such as `const_cast`, `static_cast`, `dynamic_cast`, `reinterpret_cast`, `typeid`, `sizeof...`, `noexcept`, and `alignof`, because their usage forms are the same as function calls and do not create ambiguity.

## References and Notes

[^note1]: Before C++20, if the original value has a signed type and the shifted result can be represented by the unsigned version of the original type, the result is [converted](../lang/var.md#类型转换) to the corresponding signed value; otherwise the behavior is undefined. For unsigned left shifts, bits shifted out of the result type are discarded. Since C++20, `a << b` is specified as the value of $a\cdot 2^b$ modulo $2^N$, where $N$ is the bit width of the result type. That is, whether the number is signed or unsigned, left shifts directly discard bits shifted out of the result type, namely [arithmetic left shift/logical left shift](../math/bit.md#移位).

[^note2]: Before C++20. For behavior since C++20, see [^note1].

[^note3]: That is, [logical right shift](../math/bit.md#移位).

[^note4]: That is, [arithmetic right shift](../math/bit.md#移位). Before C++20, right shift of signed numbers was implementation-defined, and most implementations used arithmetic right shift. Since C++20, `a >> b` is specified as $\lfloor a/2^b\rfloor$, so right shift of signed numbers is arithmetic right shift.
