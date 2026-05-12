Sometimes we need to do something many times. To avoid writing too much repeated code, we need loops.

Sometimes the number of iterations is not a constant, so we cannot simply repeat the code many times and must use a loop.

## `for` Statement

The following is the structure of a `for` statement:

```cpp
for (initialization; condition; update) {
  loop_body;
}
```

Execution order:

![](images/for-loop.svg)

For example, reading $n$ numbers:

```cpp
for (int i = 1; i <= n; ++i) {
  cin >> a[i];
}
```

Any of the three parts of a `for` statement can be omitted. If the condition is omitted, it is equivalent to the condition always being true.

## `while` Statement

The following is the structure of a `while` statement:

```cpp
while (condition) {
  loop_body;
}
```

Execution order:

![](images/while-loop.svg)

For example, verifying the $3x+1$ conjecture:

```cpp
while (x > 1) {
  if (x % 2 == 1) {
    x = 3 * x + 1;
  } else {
    x = x / 2;
  }
}
```

## `do...while` Statement

The following is the structure of a `do...while` statement:

```cpp
do {
  loop_body;
} while (condition);
```

Execution order:

![](images/do-while-loop.svg)

The difference from a `while` statement is that a `do...while` statement executes the loop body before checking the condition.

For example, enumerating permutations:

```cpp
do {
  // do someting...
} while (next_permutation(a + 1, a + n + 1));
```

## Relationship Between the Three Statements

```cpp
// for statement

for (statement1; statement2; statement3) {
  statement4;
}

// while statement

statement1;
while (statement2) {
  statement4;
  statement3;
}
```

They are equivalent when there is no `continue` statement in `statement4` (see below), but the latter form is rarely used.

```cpp
// while statement

statement1;
while (statement2) {
  statement1;
}

// do...while statement

do {
  statement1;
} while (statement2);
```

These two forms are also equivalent when there is no `continue` statement in `statement1`.

```cpp
while (1) {
  // do something...
}

for (;;) {
  // do something...
}
```

Both forms loop forever. You can use `break` (see below) to exit.

As you can see, the three statements can replace one another, but in general, choose among them according to these principles:

1.  Use a `for` statement when there is a fixed increment step during the loop, most commonly enumeration.
2.  Use a `while` statement when only the loop termination condition is known.
3.  When using a `while` statement, if you need to execute the loop body before checking the condition, use a `do...while` statement. It is generally used rarely; a common scenario is user input.

## `break` and `continue` Statements

The purpose of a `break` statement is to exit the loop.

The purpose of a `continue` statement is to skip the remaining part of the loop body. The following example shows the use of `continue` in a `do...while` statement:

```cpp
do {
  // do something...
  continue;  // Equivalent to goto END;
// do something...
END:;
} while (statement);

```

Both `break` and `continue` statements can be used in the loop body of all three loop statements.

In general, `break` and `continue` statements are used to make the code logic clearer. For example:

```cpp
// The logic is less clear, and the brace nesting is complex

for (int i = 1; i <= n; ++i) {
  if (i != x) {
    for (int j = 1; j <= n; ++j) {
      if (j != x) {
        // do something...
      }
    }
  }
}

// The logic is clearer, and the brace nesting is simple

for (int i = 1; i <= n; ++i) {
  if (i == x) continue;
  for (int j = 1; j <= n; ++j) {
    if (j == x) continue;
    // do something...
  }
}
```

```cpp
// The for-statement condition is complex and does not reflect the essence of enumeration

for (int i = l; i <= r && i % 10 != 0; ++i) {
  // do something...
}

// The for statement is used for enumeration, and break determines when to stop

for (int i = l; i <= r; ++i) {
  if (i % 10 == 0) break;
  // do something...
}
```

```cpp
// Statements are repeated, and the order is unnatural

statement1;
while (statement3) {
  statement2;
  statement1;
}

// No repeated statements, and the order is natural

while (1) {
  statement1;
  if (!statement3) break;
  statement2;
}
```
