> TL;DR: Template available at the end...

## Definition

Arbitrary-Precision Arithmetic, also known as bignum computation, uses some algorithm structures to support operations between larger integers (numbers exceeding the built-in integer types of programming languages).

## Introduction

High-precision computation involves many small details, and there are many nuances in implementation.

So today, let's implement a simple calculator together.

???+ note "Task"
    Input: An expression in the form `a <op> b`.
    
    -   `a` and `b` are non-negative integers in decimal with length not exceeding $1000$;
    -   `<op>` is a character (`+`, `-`, `*`, or `/`), representing the operation.
    -   There is a space between the integer and the operator.
    
    Output: The result of the operation.
    
    -   For `+`, `-`, `*` operations, output one line representing the result;
    -   For `/` operation, output two lines representing the quotient and remainder, respectively.
    -   It is guaranteed that all results are non-negative integers.

## Storage

In normal implementations, high-precision numbers are represented using strings, where each character represents one decimal digit. Therefore, high-precision arithmetic is actually a special kind of string processing.

When reading a string, the most significant digit of the number is at the beginning of the string (small index position). However, by convention, the position with the smallest index stores the **least significant digit** of the number, i.e., the string is stored in reverse. The reason for doing this is that the length of the number may change, but we want digits of the same weight to remain aligned (for example, we want all units to be at index `[0]`, all tens at index `[1]`, etc.); at the same time, addition, subtraction, and multiplication operations generally start from the units digit (recalling elementary school vertical calculations), all of which give sufficient reason for "reversed storage".

From now on, we will follow this convention. Define a constant `LEN = 1004` to represent the maximum length the program can accommodate.

From this, it is not difficult to write the code for reading high-precision numbers:

```cpp
void clear(int a[]) {
  for (int i = 0; i < LEN; ++i) a[i] = 0;
}

void read(int a[]) {
  static char s[LEN + 1];
  scanf("%s", s);

  clear(a);

  int len = strlen(s);
  // As described above, reverse
  for (int i = 0; i < len; ++i) a[len - i - 1] = s[i] - '0';
  // s[i] - '0' is the digit represented by s[i]
  // Some students may prefer to understand it as ord(s[i]) - ord('0')
}
```

Output also follows the reverse order of storage. Since we don't want to output leading zeros, we start searching from the most significant digit downward to find the first non-zero digit, and start output from this position; the termination condition `i >= 1` instead of `i >= 0` is because when the entire number equals $0$, we still want to output a single character `0`.

```cpp
void print(int a[]) {
  int i;
  for (i = LEN - 1; i >= 1; --i)
    if (a[i] != 0) break;
  for (; i >= 0; --i) putchar(a[i] + '0');
  putchar('\n');
}
```

Putting it together, we get a complete echo program.

??? note "`copycat.cpp`"
    ```cpp
    #include <cstdio>
    #include <cstring>
    
    constexpr int LEN = 1004;
    
    int a[LEN];
    
    void clear(int a[]) {
      for (int i = 0; i < LEN; ++i) a[i] = 0;
    }
    
    void read(int a[]) {
      static char s[LEN + 1];
      scanf("%s", s);
    
      clear(a);
    
      int len = strlen(s);
      for (int i = 0; i < len; ++i) a[len - i - 1] = s[i] - '0';
    }
    
    void print(int a[]) {
      int i;
      for (i = LEN - 1; i >= 1; --i)
        if (a[i] != 0) break;
      for (; i >= 0; --i) putchar(a[i] + '0');
      putchar('\n');
    }
    
    int main() {
      read(a);
      print(a);
    
      return 0;
    }
    ```

## Arithmetic Operations

Among the four arithmetic operations, the difficulty varies. The simplest is high-precision addition and subtraction, followed by high-precision times single-precision (regular `int`) multiplication and high-precision times high-precision multiplication, and finally high-precision times high-precision division.

We will implement all required functions in this order.

### Addition

High-precision addition is actually vertical addition.

![](./images/plus.svg)

That is, starting from the least significant digit, add the digits at corresponding positions of the two addends, and check if the sum reaches or exceeds $10$. If it does, handle the carry: increase the result at the next higher position by $1$, and decrease the current position's result by $10$.

```cpp
void add(int a[], int b[], int c[]) {
  clear(c);

  // In high-precision implementations, we usually let the maximum array length LEN be slightly larger than possible inputs
  // Then we can skip a few iterations at the end, which saves a lot of boundary condition handling
  // Since the actual input won't exceed 1000 digits, iterating to LEN - 1 = 1003 is sufficient here
  for (int i = 0; i < LEN - 1; ++i) {
    // Add the digits at corresponding positions
    c[i] += a[i] + b[i];
    if (c[i] >= 10) {
      // Carry
      c[i + 1] += 1;
      c[i] -= 10;
    }
  }
}
```

Try combining with the previous part, and we get an addition calculator.

??? note "`adder.cpp`"
    ```cpp
    #include <cstdio>
    #include <cstring>
    
    constexpr int LEN = 1004;
    
    int a[LEN], b[LEN], c[LEN];
    
    void clear(int a[]) {
      for (int i = 0; i < LEN; ++i) a[i] = 0;
    }
    
    void read(int a[]) {
      static char s[LEN + 1];
      scanf("%s", s);
    
      clear(a);
    
      int len = strlen(s);
      for (int i = 0; i < len; ++i) a[len - i - 1] = s[i] - '0';
    }
    
    void print(int a[]) {
      int i;
      for (i = LEN - 1; i >= 1; --i)
        if (a[i] != 0) break;
      for (; i >= 0; --i) putchar(a[i] + '0');
      putchar('\n');
    }
    
    void add(int a[], int b[], int c[]) {
      clear(c);
    
      for (int i = 0; i < LEN - 1; ++i) {
        c[i] += a[i] + b[i];
        if (c[i] >= 10) {
          c[i + 1] += 1;
          c[i] -= 10;
        }
      }
    }
    
    int main() {
      read(a);
      read(b);
    
      add(a, b, c);
      print(c);
    
      return 0;
    }
    ```

### Subtraction

High-precision subtraction is also vertical subtraction.

![](./images/subtraction.svg)

Subtract digit by digit starting from the units place, and when encountering a negative result, borrow $1$ from the next higher place. The overall idea is completely consistent with addition.

```cpp
void sub(int a[], int b[], int c[]) {
  clear(c);

  for (int i = 0; i < LEN - 1; ++i) {
    // Subtract digit by digit
    c[i] += a[i] - b[i];
    if (c[i] < 0) {
      // Borrow
      c[i + 1] -= 1;
      c[i] += 10;
    }
  }
}
```

Replace the `add()` in the previous program with `sub()`, and we have a subtraction calculator.

??? note "`subtractor.cpp`"
    ```cpp
    #include <cstdio>
    #include <cstring>
    
    constexpr int LEN = 1004;
    
    int a[LEN], b[LEN], c[LEN];
    
    void clear(int a[]) {
      for (int i = 0; i < LEN; ++i) a[i] = 0;
    }
    
    void read(int a[]) {
      static char s[LEN + 1];
      scanf("%s", s);
    
      clear(a);
    
      int len = strlen(s);
      for (int i = 0; i < len; ++i) a[len - i - 1] = s[i] - '0';
    }
    
    void print(int a[]) {
      int i;
      for (i = LEN - 1; i >= 1; --i)
        if (a[i] != 0) break;
      for (; i >= 0; --i) putchar(a[i] + '0');
      putchar('\n');
    }
    
    void sub(int a[], int b[], int c[]) {
      clear(c);
    
      for (int i = 0; i < LEN - 1; ++i) {
        c[i] += a[i] - b[i];
        if (c[i] < 0) {
          c[i + 1] -= 1;
          c[i] += 10;
        }
      }
    }
    
    int main() {
      read(a);
      read(b);
    
      sub(a, b, c);
      print(c);
    
      return 0;
    }
    ```

Try it, input `1 2`—output `/9999999`, hey, why did this **OI Wiki** give me a fake code...

In fact, the code above can only handle the case where the subtrahend $a$ is greater than or equal to the minuend $b$. Handling the case where the minuend is smaller than the subtrahend, i.e., $a<b$, is very simple.

$a-b=-(b-a)$

To compute $b-a$, since $b>a$, we can call the `sub` function in the code above, writing `sub(b,a,c)`. To get the value of $a-b$, just add a negative sign in front of the result.

### Multiplication

#### High-Precision Times Single-Precision

High-precision multiplication is also vertical... wait wait wait!

First consider a simple case: one of the multiplicands is a regular `int` type. Is there a simple handling method?

An intuitive approach is to directly multiply each digit of $a$ by $b$. Numerically, this method is correct, but it doesn't conform to decimal representation, so we need to reorganize it into normal form.

The reorganization method also processes carries digit by digit from the least significant digit upward. But here the carry can be very large, even far exceeding $9$, because after being multiplied, each digit can reach a magnitude of $9b$. Therefore, the carry here can no longer simply perform $-10$ operations, but must be calculated using the quotient and remainder of division by $10$. See the code comments for details, or refer to the figure below showing the process of calculating the high-precision number $1337$ multiplied by the single-precision number $42$.

![](./images/multiplication-short.png)

Also, for this reason, this method requires special attention to the range of the multiplicand $b$. If it is of the same order of magnitude as $10^9$ (or the upper bound of the corresponding integer type), then high-precision times single-precision multiplication must be used with caution.

```cpp
void mul_short(int a[], int b, int c[]) {
  clear(c);

  for (int i = 0; i < LEN - 1; ++i) {
    // Directly multiply the i-th digit of a by the multiplicand and add to the result
    c[i] += a[i] * b;

    if (c[i] >= 10) {
      // Handle carry
      // c[i] / 10 becomes the increment value of the carry
      c[i + 1] += c[i] / 10;
      // c[i] % 10 becomes the value left at the current position
      c[i] %= 10;
    }
  }
}
```

#### High-Precision Times High-Precision

If both multiplicands are high-precision, then vertical multiplication can shine again.

Recalling each step of vertical multiplication, it actually computes the sum of several $a \times b_i \times 10^i$. For example, computing $1337 \times 42$ computes $1337 \times 2 \times 10^0 + 1337 \times 4 \times 10^1$.

Therefore, we can decompose $b$ into all its digits, where each digit is a single-precision number, multiply them with $a$ separately, then shift them left to their respective positions and add them to get the answer. Of course, we also need to handle carries at the end in the same way as in the previous example.

![](./images/multiplication-long.png)

Note that this process is not exactly the same as vertical multiplication. Our algorithm does not carry at each step of multiplication, but keeps all results in their corresponding positions and handles carries uniformly at the end. However, this does not affect the result.

```cpp
void mul(int a[], int b[], int c[]) {
  clear(c);

  for (int i = 0; i < LEN - 1; ++i) {
    // Here we directly calculate the i-th digit from low to high in the result, and handle carries together
    // The i-th iteration adds to c[i] the sum of products of all a[p] and b[q] where p + q = i
    // The effect of doing this is the same as directly performing the calculation in the figure above and summing, just a more concise implementation
    for (int j = 0; j <= i; ++j) c[i] += a[j] * b[i - j];

    if (c[i] >= 10) {
      c[i + 1] += c[i] / 10;
      c[i] %= 10;
    }
  }
}
```

### Division

One implementation of high-precision division is long division.

![](./images/division.svg)

Long division can actually be viewed as a successive subtraction process. For example, in the figure above, the calculation of the tens digit of the quotient can be understood as: subtract $12$ three times until it becomes less than $12$ and can no longer be subtracted, so this digit is $3$.

To reduce redundant operations, we first obtain the lengths $l_a$ of the dividend and $l_b$ of the divisor, and start from index $l_a - l_b$, computing the quotient from high to low digits. This is the same as the manual calculation method where the highest digit of the first multiplication is aligned with the highest digit of the dividend.

The reference program implements a function `greater_eq()` to determine whether, with the dividend starting from index `last_dg` as the lowest digit, we can subtract the divisor again while remaining non-negative. Then, for each digit of the quotient, we repeatedly call `greater_eq()`, and when it holds, we subtract the divisor from the remainder using high-precision subtraction, which simulates the process of vertical division.

```cpp
// For dividend a, starting from index last_dg as the lowest digit, can we subtract divisor b again while remaining non-negative
// len is the length of divisor b, to avoid repeated calculations
bool greater_eq(int a[], int b[], int last_dg, int len) {
  // It's possible that the remaining part of the dividend is longer than the divisor; in this case, it can be at most 1 digit longer, so this check is sufficient
  if (a[last_dg + len] != 0) return true;
  // From high to low, compare digit by digit
  for (int i = len - 1; i >= 0; --i) {
    if (a[last_dg + i] > b[i]) return true;
    if (a[last_dg + i] < b[i]) return false;
  }
  // In the case of equality, it's also feasible
  return true;
}

void div(int a[], int b[], int c[], int d[]) {
  clear(c);
  clear(d);

  int la, lb;
  for (la = LEN - 1; la > 0; --la)
    if (a[la - 1] != 0) break;
  for (lb = LEN - 1; lb > 0; --lb)
    if (b[lb - 1] != 0) break;
  if (lb == 0) {  // Divisor cannot be zero
    puts("> <");
    return;
  }

  // c is the quotient
  // d is the remaining part of the dividend, which naturally becomes the remainder after the algorithm ends
  for (int i = 0; i < la; ++i) d[i] = a[i];
  for (int i = la - lb; i >= 0; --i) {
    // Compute the i-th digit of the quotient
    while (greater_eq(d, b, i, lb)) {
      // If it can be subtracted, then subtract
      // This segment is a high-precision subtraction
      for (int j = 0; j < lb; ++j) {
        d[i + j] -= b[j];
        if (d[i + j] < 0) {
          d[i + j + 1] -= 1;
          d[i + j] += 10;
        }
      }
      // Increase this digit of the quotient by 1
      c[i] += 1;
      // Return to the beginning of the loop to check again
    }
  }
}
```

## Introduction Section Complete!

Combining the implementations of the four arithmetic operations described above, we can complete the calculator program mentioned at the beginning.

??? note "`calculator.cpp`"
    ```cpp
    #include <cstdio>
    #include <cstring>
    
    constexpr int LEN = 1004;
    
    int a[LEN], b[LEN], c[LEN], d[LEN];
    
    void clear(int a[]) {
      for (int i = 0; i < LEN; ++i) a[i] = 0;
    }
    
    void read(int a[]) {
      static char s[LEN + 1];
      scanf("%s", s);
    
      clear(a);
    
      int len = strlen(s);
      for (int i = 0; i < len; ++i) a[len - i - 1] = s[i] - '0';
    }
    
    void print(int a[]) {
      int i;
      for (i = LEN - 1; i >= 1; --i)
        if (a[i] != 0) break;
      for (; i >= 0; --i) putchar(a[i] + '0');
      putchar('\n');
    }
    
    void add(int a[], int b[], int c[]) {
      clear(c);
    
      for (int i = 0; i < LEN - 1; ++i) {
        c[i] += a[i] + b[i];
        if (c[i] >= 10) {
          c[i + 1] += 1;
          c[i] -= 10;
        }
      }
    }
    
    void sub(int a[], int b[], int c[]) {
      clear(c);
    
      for (int i = 0; i < LEN - 1; ++i) {
        c[i] += a[i] - b[i];
        if (c[i] < 0) {
          c[i + 1] -= 1;
          c[i] += 10;
        }
      }
    }
    
    void mul(int a[], int b[], int c[]) {
      clear(c);
    
      for (int i = 0; i < LEN - 1; ++i) {
        for (int j = 0; j <= i; ++j) c[i] += a[j] * b[i - j];
    
        if (c[i] >= 10) {
          c[i + 1] += c[i] / 10;
          c[i] %= 10;
        }
      }
    }
    
    bool greater_eq(int a[], int b[], int last_dg, int len) {
      if (a[last_dg + len] != 0) return true;
      for (int i = len - 1; i >= 0; --i) {
        if (a[last_dg + i] > b[i]) return true;
        if (a[last_dg + i] < b[i]) return false;
      }
      return true;
    }
    
    void div(int a[], int b[], int c[], int d[]) {
      clear(c);
      clear(d);
    
      int la, lb;
      for (la = LEN - 1; la > 0; --la)
        if (a[la - 1] != 0) break;
      for (lb = LEN - 1; lb > 0; --lb)
        if (b[lb - 1] != 0) break;
      if (lb == 0) {
        puts("> <");
        return;
      }
    
      for (int i = 0; i < la; ++i) d[i] = a[i];
      for (int i = la - lb; i >= 0; --i) {
        while (greater_eq(d, b, i, lb)) {
          for (int j = 0; j < lb; ++j) {
            d[i + j] -= b[j];
            if (d[i + j] < 0) {
              d[i + j + 1] -= 1;
              d[i + j] += 10;
            }
          }
          c[i] += 1;
        }
      }
    }
    
    int main() {
      read(a);
    
      char op[4];
      scanf("%s", op);
    
      read(b);
    
      switch (op[0]) {
        case '+':
          add(a, b, c);
          print(c);
          break;
        case '-':
          sub(a, b, c);
          print(c);
          break;
        case '*':
          mul(a, b, c);
          print(c);
          break;
        case '/':
          div(a, b, c, d);
          print(c);
          print(d);
          break;
        default:
          puts("> <");
      }
    
      return 0;
    }
    ```

## Compressed-Precision High-Precision

### Introduction

In general high-precision addition, subtraction, and multiplication operations, we split the numbers participating in operations into individual digits.

For example, when computing $8192\times 42$, using the high-precision times high-precision calculation method, we actually compute $(8000+100+90+2)\times(40+2)$.

When there are many digits, there are also many split numbers, and the efficiency of high-precision operations decreases.

Is there a way to make some optimizations?

Note that the way of splitting numbers does not affect the final result, so we can merge several digits.

### Process

Still using the example above, if we split one number every two digits, we can split it as $(8100+92)\times 42$.

Such splitting does not affect the final result, but because there are fewer split numbers, the calculation efficiency improves.

From the perspective of [radix](./numeral-sys/base.md), we understand this process as performing operations in a larger radix (splitting one number every two digits above can be considered as performing operations in base $100$), thereby reducing the number of digits participating in operations and improving operation efficiency.

This is the idea of **compressed-precision high-precision**.

Below, we give the addition code for compressed-precision high-precision to further explain its implementation method:

??? note "Compressed-Precision High-Precision Addition Reference Implementation"
    ```cpp
    // Here, arrays a, b, c are numbers in base p
    // When outputting the final answer, we need to convert to decimal
    void add(int a[], int b[], int c[]) {
      clear(c);
    
      for (int i = 0; i < LEN - 1; ++i) {
        c[i] += a[i] + b[i];
        if (c[i] >= p) {  // In normal high-precision operations, p=10
          c[i + 1] += 1;
          c[i] -= p;
        }
      }
    }
    ```

### Efficient Long Division in Compressed-Precision

When using compressed-precision, if we still use the method introduced above for trial division, since there will be many trial divisions, the calculation constant will be very large. For example, in base 10000, on average, each digit requires 5000 trial divisions, which is an unacceptable huge constant. Therefore, we need a more efficient trial division method.

We can use double as an intermediary. Suppose the dividend has 4 digits: $a_4,a_3,a_2,a_1$, and the divisor has 3 digits: $b_3,b_2,b_1$, then we only need to trial one digit of the quotient: using base, use the formula $\dfrac{a_4 base + a_3}{b_3 + b_2 base^{-1} + (b_1+1)base^{-2}}$ to estimate the quotient. For the case of multiple digits, it's just adding a loop to the single-digit version. Since the divisor uses 3 digits of precision to participate in the estimation, it can guarantee that the estimated quotient q' satisfies $q-1 \le q' \le q$ in relation to the actual quotient q, so each digit requires at most two trial divisions in the worst case. However, this requires $base^3$ to be within the effective precision of double, i.e., $base^3 < 2^{53}$, so when using this method, it is recommended not to exceed base 32768, otherwise precision issues can easily cause errors.

Additionally, since the estimated quotient is always less than or equal to the actual quotient, there is room for further optimization. In most cases, each digit only needs to be estimated once. When estimating the next digit, although the quotient obtained may be greater than or equal to base due to the error of the previous digit, it doesn't matter as long as we do a unified carry at the end. For example, suppose base is 10, compute $395081/9876$, the trial division steps are as follows:

1.  First, trial division gives $3950/988=3$, so $395081-(9876 \times 3 \times 10^1) = 98801$, there is an error in this step, but we don't need to care, continue to the next step.
2.  Continue trial division on remainder 98801 to get $9880/988=10$, so $98801-(9876 \times 10 \times 10^0) = 41$, this is the final remainder.
3.  Add up the results of the trial division process and handle carries, i.e., $3 \times 10^1 + 10 \times 10^0 = 40$ is the accurate quotient.

Although the method looks simple, it is easy to fall into pitfalls in actual implementation. Therefore, below is an implementation that has been verified multiple times to be correct, with the details to note also written in the comments.

??? note "Compressed-Precision High-Precision Efficient Long Division Reference Implementation"
    ```cpp
    // Complete template and implementation: https://baobaobear.github.io/post/20210228-bigint1/
    // Subtract the result of multiplying b by mul and then shifting left by offset, serving division
    BigIntSimple &sub_mul(const BigIntSimple &b, int mul, int offset) {
      if (mul == 0) return *this;
      int borrow = 0;
      // Different from subtraction, borrow can be large, so we can't use the subtraction method
      for (size_t i = 0; i < b.v.size(); ++i) {
        borrow += v[i + offset] - b.v[i] * mul - BIGINT_BASE + 1;
        v[i + offset] = borrow % BIGINT_BASE + BIGINT_BASE - 1;
        borrow /= BIGINT_BASE;
      }
      // If there is still borrow, continue processing
      for (size_t i = b.v.size(); borrow; ++i) {
        borrow += v[i + offset] - BIGINT_BASE + 1;
        v[i + offset] = borrow % BIGINT_BASE + BIGINT_BASE - 1;
        borrow /= BIGINT_BASE;
      }
      return *this;
    }
    
    BigIntSimple div_mod(const BigIntSimple &b, BigIntSimple &r) const {
      BigIntSimple d;
      r = *this;
      if (absless(b)) return d;
      d.v.resize(v.size() - b.v.size() + 1);
      // Pre-calculate the reciprocal of the top three digits plus 1 of the divisor; if the top three digits are a3, a2, a1
      // then db is the reciprocal of a3 + a2/base + (a1+1)/base^2, finally use multiplication to estimate each digit
      // This method can be used within int32 range when BIGINT_BASE<=32768
      // But even with int64, it only works when BIGINT_BASE<=131072 (limited by double's precision)
      // It can guarantee that the estimated result q' satisfies q'<=q<=q'+1
      // So the average trial division for each digit only needs once, as long as we handle carries uniformly at the end
      // If you want to use a larger base, you need to change to other trial division schemes
      double t = (b.get((unsigned)b.v.size() - 2) +
                  (b.get((unsigned)b.v.size() - 3) + 1.0) / BIGINT_BASE);
      double db = 1.0 / (b.v.back() + t / BIGINT_BASE);
      for (size_t i = v.size() - 1, j = d.v.size() - 1; j <= v.size();) {
        int rm = r.get(i + 1) * BIGINT_BASE + r.get(i);
        int m = std::max((int)(db * rm), r.get(i + 1));
        r.sub_mul(b, m, j);
        d.v[j] += m;
        if (!r.get(i + 1))  // Check if the highest digit has become 0 to avoid extreme cases
          --i, --j;
      }
      r.trim();
      // Correct the units digit
      int carry = 0;
      while (!r.absless(b)) {
        r.subtract(b);
        ++carry;
      }
      // Correct the carry for each digit
      for (size_t i = 0; i < d.v.size(); ++i) {
        carry += d.v[i];
        d.v[i] = carry % BIGINT_BASE;
        carry /= BIGINT_BASE;
      }
      d.trim();
      d.sign = sign * b.sign;
      return d;
    }
    
    BigIntSimple operator/(const BigIntSimple &b) const {
      BigIntSimple r;
      return div_mod(b, r);
    }
    
    BigIntSimple operator%(const BigIntSimple &b) const {
      BigIntSimple r;
      div_mod(b, r);
      return r;
    }
    ```

## Karatsuba Multiplication

Let the number of digits of a high-precision number be $n$. Then high-precision times high-precision vertical multiplication takes $O(n^2)$ time. This section introduces an algorithm with better time complexity, proposed by Soviet (Russian) mathematician Anatoly Karatsuba, which is a divide-and-conquer algorithm.

Consider two decimal integers $x$ and $y$, both containing $n$ digits (may have leading zeros). For any $0 < m < n$, denote

$$
\begin{aligned}
x &= x_1 \cdot 10^m + x_0, \\
y &= y_1 \cdot 10^m + y_0, \\
x \cdot y &= z_2 \cdot 10^{2m} + z_1 \cdot 10^m + z_0,
\end{aligned}
$$

where $x_0, y_0, z_0, z_1 < 10^m$. We can obtain

$$
\begin{aligned}
z_2 &= x_1 \cdot y_1, \\
z_1 &= x_1 \cdot y_0 + x_0 \cdot y_1, \\
z_0 &= x_0 \cdot y_0.
\end{aligned}
$$

Observing,

$$
z_1 = (x_1 + x_0) \cdot (y_1 + y_0) - z_2 - z_0,
$$

so to compute $z_1$, we only need to compute $(x_1 + x_0) \cdot (y_1 + y_0)$, then subtract $z_0$ and $z_2$.

The above formula is actually the core of the Karatsuba algorithm. It transforms a multiplication problem of length $n$ into $3$ smaller subproblems. Let $m = \left\lceil \dfrac n 2 \right\rceil$, and let $T(n)$ be the time for the Karatsuba algorithm to compute the product of two $n$-digit integers. Then $T(n) = 3 \cdot T \left(\left\lceil \dfrac n 2 \right\rceil\right) + O(n)$. By the master theorem, we get $T(n) = \Theta(n^{\log_2 3}) \approx \Theta(n^{1.585})$.

The entire process can be implemented recursively. For clarity, the code below implements polynomial multiplication using the Karatsuba algorithm, and then handles all carry issues.

??? note "karatsuba_mulc.cpp"
    ```cpp
    int *karatsuba_polymul(int n, int *a, int *b) {
      if (n <= 32) {
        // When the scale is small, compute directly to avoid efficiency loss from further recursion
        int *r = new int[n * 2 + 1]();
        for (int i = 0; i <= n; ++i)
          for (int j = 0; j <= n; ++j) r[i + j] += a[i] * b[j];
        return r;
      }
    
      int m = n / 2 + 1;
      int *r = new int[m * 4 + 1]();
      int *z0, *z1, *z2;
    
      z0 = karatsuba_polymul(m - 1, a, b);
      z2 = karatsuba_polymul(n - m, a + m, b + m);
    
      // Compute z1
      // Temporarily change, restore after completion
      for (int i = 0; i + m <= n; ++i) a[i] += a[i + m];
      for (int i = 0; i + m <= n; ++i) b[i] += b[i + m];
      z1 = karatsuba_polymul(m - 1, a, b);
      for (int i = 0; i + m <= n; ++i) a[i] -= a[i + m];
      for (int i = 0; i + m <= n; ++i) b[i] -= b[i + m];
      for (int i = 0; i <= (m - 1) * 2; ++i) z1[i] -= z0[i];
      for (int i = 0; i <= (n - m) * 2; ++i) z1[i] -= z2[i];
    
      // Combine z0, z1, z2 to get the result
      for (int i = 0; i <= (m - 1) * 2; ++i) r[i] += z0[i];
      for (int i = 0; i <= (m - 1) * 2; ++i) r[i + m] += z1[i];
      for (int i = 0; i <= (n - m) * 2; ++i) r[i + m * 2] += z2[i];
    
      delete[] z0;
      delete[] z1;
      delete[] z2;
      return r;
    }
    
    void karatsuba_mul(int a[], int b[], int c[]) {
      int *r = karatsuba_polymul(LEN - 1, a, b);
      memcpy(c, r, sizeof(int) * LEN);
      for (int i = 0; i < LEN - 1; ++i)
        if (c[i] >= 10) {
          c[i + 1] += c[i] / 10;
          c[i] %= 10;
        }
      delete[] r;
    }
    ```

??? note "About `new` and `delete`"
    See [Memory Pool](../contest/common-tricks.md#memory-pool).

However, there is a problem with such an implementation: in base $b$, each coefficient of the polynomial can reach the level of $n \cdot b^2$, which may cause integer overflow in compressed-precision high-precision implementations; and if we handle carries during polynomial multiplication, the results of $x_1 + x_0$ and $y_1 + y_0$ can reach $2 \cdot b^m$, adding one digit (if using the calculation method of $x_1 - x_0$, we have to handle negative numbers specially). Therefore, we need to decide which implementation method to use based on the actual application scenario.

## Efficient Large Integer Multiplication Based on Polynomials

If the data scale reaches $10^{10^5}$ or larger, ordinary high-precision multiplication may time out. This section introduces methods to optimize such multiplication using polynomials.

For an $n$-digit decimal integer $a$, we can regard it as a polynomial where each coefficient is an integer not exceeding $10$: $A=a_{0} 10^0+a_{1} 10^1+\cdots+a_{n-1} 10^{n-1}$. In this way, we transform the multiplication of two integers into the multiplication of two polynomials.

The time complexity of ordinary polynomial multiplication is still $O(n^2)$, but it can be optimized using algorithms like [Fast Fourier Transform](poly/fft.md) and [Fast Number-Theoretic Transform](poly/ntt.md) from the polynomial section, with the optimized time complexity being $O(n\log n)$.

## Wrapper Class

[Here](https://paste.ubuntu.com/p/7VKYzpC7dn/) is a well-packaged high-precision integer class, and [here](https://github.com/Baobaobear/MiniBigInteger/blob/main/bigint_tiny.h) is an ultra-mini implementation class that supports dynamic length and four arithmetic operations.

??? note "Here's another template"
    ```cpp
    constexpr int MAXN = 9999;
    // MAXN is the largest digit in one "digit"
    constexpr int MAXSIZE = 10024;
    // MAXSIZE is the number of digits
    constexpr int DLEN = 4;
    
    // DLEN records how many digits are compressed
    struct Big {
      int a[MAXSIZE], len;
      bool flag;  // Mark for negative sign '-'
    
      Big() {
        len = 1;
        memset(a, 0, sizeof a);
        flag = false;
      }
    
      Big(const int);
      Big(const char*);
      Big(const Big&);
      Big& operator=(const Big&);
      Big operator+(const Big&) const;
      Big operator-(const Big&) const;
      Big operator*(const Big&) const;
      Big operator/(const int&) const;
      // TODO: Big / Big;
      Big operator^(const int&) const;
      // TODO: Big ^ Big;
    
      // TODO: Big bit operations;
    
      int operator%(const int&) const;
      // TODO: Big ^ Big;
      bool operator<(const Big&) const;
      bool operator<(const int& t) const;
      void print() const;
    };
    
    Big::Big(const int b) {
      int c, d = b;
      len = 0;
      // memset(a,0,sizeof a);
      CLR(a);
      while (d > MAXN) {
        c = d - (d / (MAXN + 1) * (MAXN + 1));
        d = d / (MAXN + 1);
        a[len++] = c;
      }
      a[len++] = d;
    }
    
    Big::Big(const char* s) {
      int t, k, index, l;
      CLR(a);
      l = strlen(s);
      len = l / DLEN;
      if (l % DLEN) ++len;
      index = 0;
      for (int i = l - 1; i >= 0; i -= DLEN) {
        t = 0;
        k = i - DLEN + 1;
        if (k < 0) k = 0;
        g(j, k, i) t = t * 10 + s[j] - '0';
        a[index++] = t;
      }
    }
    
    Big::Big(const Big& T) : len(T.len) {
      CLR(a);
      f(i, 0, len) a[i] = T.a[i];
      // TODO: overload here?
    }
    
    Big& Big::operator=(const Big& T) {
      CLR(a);
      len = T.len;
      f(i, 0, len) a[i] = T.a[i];
      return *this;
    }
    
    Big Big::operator+(const Big& T) const {
      Big t(*this);
      int big = len;
      if (T.len > len) big = T.len;
      f(i, 0, big) {
        t.a[i] += T.a[i];
        if (t.a[i] > MAXN) {
          ++t.a[i + 1];
          t.a[i] -= MAXN + 1;
        }
      }
      if (t.a[big])
        t.len = big + 1;
      else
        t.len = big;
      return t;
    }
    
    Big Big::operator-(const Big& T) const {
      int big;
      bool ctf;
      Big t1, t2;
      if (*this < T) {
        t1 = T;
        t2 = *this;
        ctf = true;
      } else {
        t1 = *this;
        t2 = T;
        ctf = false;
      }
      big = t1.len;
      int j = 0;
      f(i, 0, big) {
        if (t1.a[i] < t2.a[i]) {
          j = i + 1;
          while (t1.a[j] == 0) ++j;
          --t1.a[j--];
          // WTF?
          while (j > i) t1.a[j--] += MAXN;
          t1.a[i] += MAXN + 1 - t2.a[i];
        } else
          t1.a[i] -= t2.a[i];
      }
      t1.len = big;
      while (t1.len > 1 && t1.a[t1.len - 1] == 0) {
        --t1.len;
        --big;
      }
      if (ctf) t1.a[big - 1] = -t1.a[big - 1];
      return t1;
    }
    
    Big Big::operator*(const Big& T) const {
      Big res;
      int up;
      int te, tee;
      f(i, 0, len) {
        up = 0;
        f(j, 0, T.len) {
          te = a[i] * T.a[j] + res.a[i + j] + up;
          if (te > MAXN) {
            tee = te - te / (MAXN + 1) * (MAXN + 1);
            up = te / (MAXN + 1);
            res.a[i + j] = tee;
          } else {
            up = 0;
            res.a[i + j] = te;
          }
        }
        if (up) res.a[i + T.len] = up;
      }
      res.len = len + T.len;
      while (res.len > 1 && res.a[res.len - 1] == 0) --res.len;
      return res;
    }
    
    Big Big::operator/(const int& b) const {
      Big res;
      int down = 0;
      gd(i, len - 1, 0) {
        res.a[i] = (a[i] + down * (MAXN + 1)) / b;
        down = a[i] + down * (MAXN + 1) - res.a[i] * b;
      }
      res.len = len;
      while (res.len > 1 && res.a[res.len - 1] == 0) --res.len;
      return res;
    }
    
    int Big::operator%(const int& b) const {
      int d = 0;
      gd(i, len - 1, 0) d = (d * (MAXN + 1) % b + a[i]) % b;
      return d;
    }
    
    Big Big::operator^(const int& n) const {
      Big t(n), res(1);
      int y = n;
      while (y) {
        if (y & 1) res = res * t;
        t = t * t;
        y >>= 1;
      }
      return res;
    }
    
    bool Big::operator<(const Big& T) const {
      int ln;
      if (len < T.len) return true;
      if (len == T.len) {
        ln = len - 1;
        while (ln >= 0 && a[ln] == T.a[ln]) --ln;
        if (ln >= 0 && a[ln] < T.a[ln]) return true;
        return false;
      }
      return false;
    }
    
    bool Big::operator<(const int& t) const {
      Big tee(t);
      return *this < tee;
    }
    
    void Big::print() const {
      printf("%d", a[len - 1]);
      gd(i, len - 2, 0) { printf("%04d", a[i]); }
    }
    
    void print(const Big& s) {
      int len = s.len;
      printf("%d", s.a[len - 1]);
      gd(i, len - 2, 0) { printf("%04d", s.a[i]); }
    }
    
    char s[100024];
    ```

## Exercises

-   [NOIP 2012 King's Game](https://loj.ac/problem/2603)
-   [SPOJ - Fast Multiplication](http://www.spoj.com/problems/MUL/en/)
-   [SPOJ - GCD2](http://www.spoj.com/problems/GCD2/)
-   [UVa - Division](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1024)
-   [UVa - Fibonacci Freeze](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=436)
-   [Codeforces - Notepad](http://codeforces.com/contest/17/problem/D)

## References and Links

1.  [Karatsuba algorithm - Wikipedia](https://en.wikipedia.org/wiki/Karatsuba_algorithm)
