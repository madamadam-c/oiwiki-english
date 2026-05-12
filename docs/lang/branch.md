By default, a program executes in the order of the code. Sometimes we need to execute certain statements selectively; this is where branching is needed. Choosing appropriate branch statements can improve program efficiency.

## `if` Statement

### Basic `if` Statement

The following is the structure of a basic `if` statement.

```cpp
if (condition) {
  body;
}
```

An `if` statement evaluates the condition. If the result is true (nonzero), it executes the statement; otherwise, it does not.

If the body contains only a single statement, the braces may be omitted.

### `if...else` Statement

```cpp
if (condition) {
  body1;
} else {
  body2;
}
```

An `if...else` statement is similar to an `if` statement, and `else` does not need another condition. When the condition of the `if` statement is satisfied, the statements inside `if` are executed; when it is not satisfied, the statements inside `else` are executed. Similarly, if the body has only one statement, the braces may be omitted.

### `else if` Statement

```cpp
if (condition1) {
  body1;
} else if (condition2) {
  body2;
} else if (condition3) {
  body3;
} else {
  body4;
}
```

An `else if` statement is a combination of `if` and `else`. It checks multiple conditions and chooses different statement branches. The final `else` statement does not need a condition. For example, if condition 1 is true, body 1 is executed; if condition 3 is true while conditions 1 and 2 are both false, body 3 is executed; body 4 is executed only when all conditions are false.

In fact, this is equivalent to the `else` clause of the first `if` containing only one `if` statement, with the braces omitted and the statements placed together. If the conditions are parallel to each other, this style can make the code logic clearer.

Logically, it is roughly equivalent to the following description:

> When solving a quadratic equation in one variable, the relationship between the roots and the discriminant is:
>
> -   If ($\Delta<0$), the equation has no solution.
> -   Otherwise, if ($\Delta=0$), the equation has two equal real roots.
> -   Otherwise, the equation has two distinct real roots.

## `switch` Statement

```cpp
switch (selection_statement) {
  case label1:
    body1;
  case label2:
    body2;
  default:
    body3;
}
```

When a `switch` statement executes, it first evaluates the selection statement, then chooses the corresponding label based on that value and starts executing from that label. The selection statement must be an expression of integer type, and the labels must be constants of integer type. For example:

```cpp
int i = 1;  // Here i has integer type, satisfying the requirement for an integer expression

switch (i) {
  case 1:
    cout << "OI WIKI" << endl;
}
```

```cpp
char i = 'A';

// Here i has character type, but char is also an integer type,
// satisfying the requirement for an integer expression
switch (i) {
  case 'A':
    cout << "OI WIKI" << endl;
}
```

In a `switch` statement, add `break` statements as needed to interrupt execution. Otherwise, after the corresponding `case` is selected, all following `case` statements and the `default` statements will also run. See the example below.

```cpp
char i = 'B';

switch (i) {
  case 'A':
    cout << "OI" << endl;
    break;

  case 'B':
    cout << "WIKI" << endl;

  default:
    cout << "Hello World" << endl;
}
```

After the code above runs, it outputs `WIKI` and `Hello World`. If you do not want the statements in later branches to run, you need `break`. See the example below.

```cpp
char i = 'B';

switch (i) {
  case 'A':
    cout << "OI" << endl;
    break;

  case 'B':
    cout << "WIKI" << endl;
    break;

  default:
    cout << "Hello World" << endl;
}
```

After the code above runs, it outputs `WIKI`. Because of `break`, the following statements are not executed. The last statement does not need `break`, because there are no statements after it.

Case labels cannot be repeated, but their order can be rearranged. In other words, the order of labels does not matter. The order in which each `case` (including `default`) appears can be arbitrary. For example:

```cpp
char i = 'B';

switch (i) {
  case 'B':
    cout << "WIKI" << endl;
    break;

  default:
    cout << "Hello World" << endl;
    break;

  case 'A':
    cout << "OI" << endl;
}
```

Braces may optionally be added inside `case` clauses of a `switch`. However, note that if you need to define variables inside a `switch` statement, braces are required. For example:

```cpp
char i = 'B';

switch (i) {
  case 'A': {
    int i = 1, j = 2;
    cout << "OI" << endl;
    ans = i + j;
    break;
  }

  case 'B': {
    int qwq = 3;
    cout << "WIKI" << endl;
    ans = qwq * qwq;
    break;
  }

  default: {
    cout << "Hello World" << endl;
  }
}
```

??? note "How to understand switch"
    Terms such as "case clause" are used frequently above. In the low-level implementation, `switch` is essentially a set of jump statements. This is also why tricks such as Duff's Device exist; interested readers can learn about them on their own.
