## Definition

The greatest common divisor, often abbreviated as gcd.

A common divisor of a set of integers is a number that is simultaneously a divisor of each number in that set. $\pm 1$ is a common divisor of any set of integers.

The greatest common divisor of a set of integers is the largest among all common divisors.

For integers $a,b$ not both zero, we denote their greatest common divisor as $\gcd(a,b)$, which can be simply written as $(a,b)$ when there is no ambiguity.

For integers $a_1,\dots,a_n$ not all zero, we denote their greatest common divisor as $\gcd(a_1,\dots,a_n)$, which can be simply written as $(a_1,\dots,a_n)$ when there is no ambiguity.

The properties of greatest common divisor and least common multiple can be found in [Number Theory Basics](./basic.md#greatest-common-divisor-and-least-common-multiple).

So how do we find the greatest common divisor? Let's first consider the case of two numbers.

### Euclidean Algorithm

#### Process

If we have two numbers $a$ and $b$, how do we find their greatest common divisor?

Assume $a > b$.

We found that if $b$ is a divisor of $a$, then $b$ is the greatest common divisor.
Now let's discuss the case where division is not exact, i.e., $a = b \times q + r$, where $r < b$.

We can prove that $\gcd(a,b)=\gcd(b,a \bmod b)$ as follows:

???+ note "Proof"
    Let $a=bk+c$, obviously $c=a \bmod b$. Let $d \mid a,~d \mid b$, then $c=a-bk, \frac{c}{d}=\frac{a}{d}-\frac{b}{d}k$.
    
    From the right side, $\frac{c}{d}$ is an integer, i.e., $d \mid c$. So for a common divisor of $a,b$, it is also a common divisor of $b,a \bmod b$.
    
    The reverse also needs proof:
    
    Let $d \mid b,~d\mid (a \bmod b)$, as before we get $\frac{a\bmod b}{d}=\frac{a}{d}-\frac{b}{d}k,~\frac{a\bmod b}{d}+\frac{b}{d}k=\frac{a}{d}$.
    
    Since the left side is obviously an integer, $\frac{a}{d}$ is also an integer, i.e., $d \mid a$. So the common divisors of $b,a\bmod b$ are also common divisors of $a,b$.
    
    Since both equations have the same common divisors, the greatest common divisors are also the same.
    
    So we get $\gcd(a,b)=\gcd(b,a\bmod b)$

Since we have $\gcd(a, b) = \gcd(b, r)$, where the two numbers do not increase in size, we have a recursive method for finding the greatest common divisor of two numbers.

#### Implementation

=== "C++"
    ```cpp
    // Version 1
    int gcd(int a, int b) {
      if (b == 0) return a;
      return gcd(b, a % b);
    }
    
    // Version 2
    int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
    ```

=== "Java"
    ```java
    // Version 1
    public int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, a % b);
    }
    
    // Version 2
    public int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
    ```

=== "Python"
    ```python
    def gcd(a, b):
        if b == 0:
            return a
        return gcd(b, a % b)
    ```

Return when `b == 0` (that is, when `a % b == 0` in the previous step).

Based on this recursive method, we can also write an iterative method:

=== "C++"
    ```cpp
    int gcd(int a, int b) {
      while (b != 0) {
        int tmp = a;
        a = b;
        b = tmp % b;
      }
      return a;
    }
    ```

=== "Java"
    ```java
    public int gcd(int a, int b) {
        while(b != 0) {
            int tmp = a;
            a = b;
            b = tmp % b;
        }
        return a;
    }
    ```

=== "Python"
    ```python
    def gcd(a, b):
        while b != 0:
            a, b = b, a % b
        return a
    ```

The above algorithm can all be called the Euclidean algorithm.

Also, for C++17, we can use [`std::gcd`](https://en.cppreference.com/w/cpp/numeric/gcd) and [`std::lcm`](https://en.cppreference.com/w/cpp/numeric/lcm) in the header [`<numeric>`](https://en.cppreference.com/w/cpp/header/numeric) to compute the greatest common divisor and least common multiple.

???+ warning "Note"
    In some compilers, in C++14, you can use the function `std::__gcd(a,b)` to compute the greatest common divisor, but it is only used as a private auxiliary function for `std::rotate`.[^1] Using this function may lead to unexpected problems, so it is generally not recommended.

If two numbers $a$ and $b$ satisfy $\gcd(a, b) = 1$, we say $a$ and $b$ are coprime.

#### Properties

What is the time efficiency of the Euclidean algorithm? Let's prove that the time complexity of the Euclidean algorithm is $O(n)$ when the input is two binary integers of length $n$. (In other words, assuming $a, b$ are of the same order, the time complexity is $O(\log\max(a, b))$)

???+ note "Proof"
    When computing $\gcd(a,b)$, we encounter two cases:
    
    -   $a < b$, then $\gcd(a,b)=\gcd(b,a)$;
    -   $a \ge b$, then $\gcd(a,b)=\gcd(b,a \bmod b)$, and taking $a$ modulo $b$ at least halves $a$. This means this process happens at most $O(\log a) = O(n)$ times.
    
    The first case must be followed by the second case, so the number of occurrences of the first case is definitely **not more than** the number of occurrences of the second case.
    
    Therefore, we can get the result after at most $O(n)$ recursions.

In fact, if we try to use the Euclidean algorithm to find the greatest common divisor of [adjacent Fibonacci numbers](../combinatorics/fibonacci.md), this algorithm will reach the worst-case complexity.

### More Subtraction Method

The time complexity of modular arithmetic on large integers is relatively high, while addition and subtraction have lower time complexity. For large integers, we can use addition and subtraction instead of multiplication and division to find the greatest common divisor.

#### Process

Given two numbers $a$ and $b$, find $\gcd(a,b)$.

Assume $a \ge b$. If $a = b$, then $\gcd(a,b)=a=b$.
Otherwise, for all $d\mid a, d\mid b$, we can prove that $d\mid a-b$.

Therefore, all common divisors of $a$ and $b$ are also common divisors of $a-b$ and $b$, i.e., $\gcd(a,b) = \gcd(a-b, b)$.

#### Stein's Algorithm Optimization

If $a\gg b$, the $O(n)$ complexity of the More Subtraction Method will reach the worst case.

Consider an optimization: if $2\mid a,2\mid b$, then $\gcd(a,b) = 2\gcd\left(\dfrac a2, \dfrac b2\right)$.

Otherwise, if $2\mid a$ (similarly if $2\mid b$), since the case $2\mid b$ has been discussed, so $2 \nmid b$. Therefore, $\gcd(a,b)=\gcd\left(\dfrac a2,b\right)$.

The optimized algorithm (Stein's algorithm) has time complexity $O(\log n)$.

???+ note "Proof"
    If $2\mid a$ or $2\mid b$, each recursion at least halves one of $a,b$.
    
    Otherwise, $2\mid a-b$, falling back to the previous case.
    
    The algorithm recurs at most $O(\log n)$ times.

#### Implementation

For high-precision templates, see [High-Precision Computation](../bignum.md).

High-precision operations need to implement: subtraction, comparison, left shift, right shift (can be replaced by low-precision multiplication and division), the number of trailing zeros in binary (can be computed by brute force by judging odd/even).

??? note "C++"
    ```cpp
    Big gcd(Big a, Big b) {
      if (a == 0) return b;
      if (b == 0) return a;
      // record the number of 2 appearing in common divisors of a and b, countr_zero represents the number of trailing zeros in binary
      int atimes = countr_zero(a);
      int btimes = countr_zero(b);
      int mintimes = min(atimes, btimes);
      a >>= atimes;
      for (;;) {
        // 2 has already been calculated in the common divisors of a and b, so a cannot be even in the future
        b >>= btimes;
        // ensure a<=b
        if (a > b) swap(a, b);
        b -= a;
        if (b == 0) break;
        btimes = countr_zero(b);
      }
      return a << mintimes;
    }
    ```

The above code references the implementations of C++17 `std::gcd` in [libstdc++](https://github.com/gcc-mirror/gcc/blob/1667962ae755db27965778b8c8c684c6c0c4da21/libstdc%2B%2B-v3/include/std/numeric#L173) and [MSVC](https://github.com/microsoft/STL/blob/9aca22477df4eed3222b4974746ee79129eb44e7/stl/inc/numeric#L591). In the data range of `unsigned int` and `unsigned long long`, if `countr_zero` can be computed extremely fast, then Stein's algorithm is faster than the Euclidean algorithm; conversely, it may be slower than the Euclidean algorithm.

???+ note "About countr_zero"
    1.  gcc has built-in function `__builtin_ctz` (32-bit) or `__builtin_ctz64ll` (64-bit) to replace `countr_zero`;
    2.  Starting from C++20, the header `<bit>` contains [`std::countr_zero`](https://en.cppreference.com/w/cpp/numeric/countr_zero);
    3.  If not using standard library functions and C++20 is not available, the following code is an $O(1)$ implementation after preprocessing in the Word-RAM with multiplication model:
        
        ```cpp
        constexpr int loghash[64] = {0,  32, 48, 56, 60, 62, 63, 31, 47, 55, 59, 61, 30,
                                     15, 39, 51, 57, 28, 46, 23, 43, 53, 58, 29, 14, 7,
                                     35, 49, 24, 44, 54, 27, 45, 22, 11, 37, 50, 25, 12,
                                     38, 19, 41, 52, 26, 13, 6,  3,  33, 16, 40, 20, 42,
                                     21, 10, 5,  34, 17, 8,  36, 18, 9,  4,  2,  1};
        
        int countr_zero(unsigned long long x) {
          return loghash[(x & -x) * 0x9150D32D8EB9EFC0Ui64 >> 58];
        }
        ```
        
        For high-precision operations, if the implementation is similar to `bitset`, then combined with the above implementation of `countr_zero`, it can be completed in $O(n / w)$ time complexity. But if it is not convenient to split by binary bits, we can only judge the largest power of 2 by brute force, and the time complexity depends on the implementation. For example:
        
        ```cpp
        // Little-endian binary Big, requires enumerating each element
        int countr_zero(Big a) {
          int ans = 0;
          for (auto x : a) {
            if (x != 0) {
              ans += 32;  // bit length of each data type
            } else {
              return ans + countr_zero(x);
            }
          }
          return ans;
        }
        
        // Brute force calculation, if needed it is recommended to write directly into gcd to accelerate constants
        int countr_zero(Big a) {
          int ans = 0;
          while ((a & 1) == 0) {
            a >>= 1;
            ++ans;
          }
          return ans;
        }
        ```

For more discussions about the speed of `gcd` implementation, read [Fastest way to compute the greatest common divisor](https://lemire.me/blog/2013/12/26/fastest-way-to-compute-the-greatest-common-divisor/).

### Greatest Common Divisor of Multiple Numbers

So how do we find the greatest common divisor of multiple numbers? Obviously, the answer must be a divisor of each number, so it must also be a divisor of the gcd of each pair of adjacent numbers. Using mathematical induction, it can be proven that taking out two numbers to find the answer and putting them back will not affect the required answer.

## Least Common Multiple

Next, we introduce how to find the Least Common Multiple (LCM).

### Definition

A common multiple of a set of integers is a number that is simultaneously a multiple of each number in the set. $0$ is a common multiple of any set of integers.

The least common multiple of a set of integers is the smallest among all positive common multiples.

For integers $a,b$, we denote their least common multiple as $\operatorname{lcm}(a,b)$, which can be simply written as $[a,b]$ when there is no ambiguity.

For integers $a_1,\dots,a_n$, we denote their least common multiple as $\operatorname{lcm}(a_1,\dots,a_n)$, which can be simply written as $[a_1,\dots,a_n]$ when there is no ambiguity.

### Two Numbers

Let $a = p_1^{k_{a_1}}p_2^{k_{a_2}} \cdots p_s^{k_{a_s}}$, $b = p_1^{k_{b_1}}p_2^{k_{b_2}} \cdots p_s^{k_{b_s}}$

We found that for $a$ and $b$, their greatest common divisor equals:

$p_1^{\min(k_{a_1}, k_{b_1})}p_2^{\min(k_{a_2}, k_{b_2})} \cdots p_s^{\min(k_{a_s}, k_{b_s})}$

The least common multiple equals:

$p_1^{\max(k_{a_1}, k_{b_1})}p_2^{\max(k_{a_2}, k_{b_2})} \cdots p_s^{\max(k_{a_s}, k_{b_s})}$

Since $k_a + k_b = \max(k_a, k_b) + \min(k_a, k_b)$

So we get the conclusion: $\gcd(a, b) \times \operatorname{lcm}(a, b) = a \times b$

To find the least common multiple of two numbers, first find the greatest common divisor.

### Multiple Numbers

We can find that when we find $\gcd$ of two numbers, finding the least common multiple is $O(1)$ complexity. So for multiple numbers, we actually don't need to find the common greatest common divisor first. The most direct method is that when we calculate $\gcd$ of two numbers, perhaps when calculating the $\gcd$ of multiple numbers, we put it into the sequence to continue solving for the following numbers. Then, converting, we directly put the least common multiple into the sequence.

## Extended Euclidean Algorithm

The Extended Euclidean Algorithm (EXGCD) is commonly used to find a feasible solution to $ax+by=\gcd(a,b)$.

### Process

Let:

$ax_1+by_1=\gcd(a,b)$

$bx_2+(a\bmod b)y_2=\gcd(b,a\bmod b)$

From the Euclidean theorem, $\gcd(a,b)=\gcd(b,a\bmod b)$

So $ax_1+by_1=bx_2+(a\bmod b)y_2$

And since $a\bmod b=a-(\lfloor\frac{a}{b}\rfloor\times b)$

So $ax_1+by_1=bx_2+(a-(\lfloor\frac{a}{b}\rfloor\times b))y_2$

$ax_1+by_1=ay_2+bx_2-\lfloor\frac{a}{b}\rfloor\times by_2=ay_2+b(x_2-\lfloor\frac{a}{b}\rfloor y_2)$

Since $a=a,b=b$, so $x_1=y_2,y_1=x_2-\lfloor\frac{a}{b}\rfloor y_2$

Keep substituting $x_2,y_2$ into recursion until $b$ is $0$, recursively return $x=1,y=0$ to solve back.

### Implementation

=== "C++"
    ```cpp
    int Exgcd(int a, int b, int &x, int &y) {
      if (!b) {
        x = 1;
        y = 0;
        return a;
      }
      int d = Exgcd(b, a % b, x, y);
      int t = x;
      x = y;
      y = t - (a / b) * y;
      return d;
    }
    ```

=== "Python"
    ```python
    def Exgcd(a, b):
        if b == 0:
            return a, 1, 0
        d, x, y = Exgcd(b, a % b)
        return d, y, x - (a // b) * y
    ```

The function returns $\gcd$, during which $x,y$ are calculated.

### Value Range Analysis

$ax+by=\gcd(a,b)$ has infinitely many solutions, and obviously some solutions can overflow long long.
Fortunately, if $b\not= 0$, the feasible solution obtained by the Extended Euclidean Algorithm must satisfy $|x|\le b,|y|\le a$.
The proof is given below.

??? note "Proof"
    -   When $\gcd(a,b)=b$, $a\bmod b=0$, must terminate at the next layer.
        Get $x_1=0,y_1=1$. Obviously $a,b\ge 1\ge |x_1|,|y_1|$.
    -   When $\gcd(a,b)\not= b$, assume $|x_2|\le (a\bmod b),|y_2|\le b$.
        Since $x_1=y_2,y_1=x_2-{\left\lfloor\dfrac{a}{b}\right\rfloor}y_2$
        So $|x_1|=|y_2|\le b,|y_1|\le|x_2|+|{\left\lfloor\dfrac{a}{b}\right\rfloor}y_2|\le (a\bmod b)+{\left\lfloor\dfrac{a}{b}\right\rfloor}|y_2|$
        $\le a-{\left\lfloor\dfrac{a}{b}\right\rfloor}b+{\left\lfloor\dfrac{a}{b}\right\rfloor}|y_2|\le a-{\left\lfloor\dfrac{a}{b}\right\rfloor}(b-|y_2|)$
        $a\bmod b=a-{\left\lfloor\dfrac{a}{b}\right\rfloor}b\le a-{\left\lfloor\dfrac{a}{b}\right\rfloor}(b-|y_2|)\le a$
        So $|x_1|\le b,|y_1|\le a$ holds.

### Iterative Implementation of Extended Euclidean Algorithm

First, when $x = 1$, $y = 0$, $x_1 = 0$, $y_1 = 1$, obviously:

$$
\begin{cases}
    ax + by     & = a \\
    ax_1 + by_1 & = b
\end{cases}
$$

holds.

Given $a\bmod b = a - (\lfloor \frac{a}{b} \rfloor \times b)$, let $q = \lfloor \frac{a}{b} \rfloor$. Refer to the iterative method for gcd. Each iteration can be expressed as:

$$
(a, b) \rightarrow (b, a - qb)
$$

Replace $a$ in the iteration process with $ax + by = a$, and replace $b$ with $ax_1 + by_1 = b$:

$$
\begin{aligned}
                & \begin{cases}
                      ax + by     & = a \\
                      ax_1 + by_1 & = b
                  \end{cases}                    \\
    \rightarrow & \begin{cases}
                      ax_1 + by_1               & = b      \\
                      a(x - qx_1) + b(y - qy_1) & = a - qb
                  \end{cases}
\end{aligned}
$$

This gives the iterative method for exgcd.

Since the iterative method avoids recursion, the code runs slightly faster than recursive code.

```cpp
int gcd(int a, int b, int& x, int& y) {
  x = 1, y = 0;
  int x1 = 0, y1 = 1, a1 = a, b1 = b;
  while (b1) {
    int q = a1 / b1;
    tie(x, x1) = make_tuple(x1, x - q * x1);
    tie(y, y1) = make_tuple(y1, y - q * y1);
    tie(a1, b1) = make_tuple(b1, a1 - q * b1);
  }
  return a1;
}
```

If you observe $a_1$ and $b_1$, you will find that they take the same values in the iterative Euclidean algorithm, and the following formulas always hold (both before the while loop and at the end of each iteration): $x \cdot a + y \cdot b = a_1$ and $x_1 \cdot a + y_1 \cdot b = b_1$. Therefore, this algorithm can certainly correctly compute $\gcd$.

Finally, we know that $a_1$ is the required $\gcd$, and $x \cdot a + y \cdot b = g$.

#### Matrix Interpretation

The Euclidean algorithm for one iteration with two positive integers $a$ and $b$, i.e., $\gcd(a,b)=\gcd(b,a\bmod b)$ can be represented using a matrix:

$$
\begin{bmatrix}
b\\a\bmod b
\end{bmatrix}
=
\begin{bmatrix}
0&1\\1&-\lfloor a/b\rfloor
\end{bmatrix}
\begin{bmatrix}
a\\b
\end{bmatrix}
$$

The floor symbol $\lfloor c\rfloor$ represents the largest integer not exceeding $c$. We define the transformation $\begin{bmatrix}a\\b\end{bmatrix}\mapsto \begin{bmatrix}0&1\\1&-\lfloor a/b\rfloor\end{bmatrix}\begin{bmatrix}a\\b\end{bmatrix}$.

It is easy to find that the Euclidean algorithm applies this transformation continuously:

$$
\begin{bmatrix}
\gcd(a,b)\\0
\end{bmatrix}
=
\left(
\cdots 
\begin{bmatrix}
0&1\\1&-\lfloor a/b\rfloor
\end{bmatrix}
\begin{bmatrix}
1&0\\0&1
\end{bmatrix}
\right)
\begin{bmatrix}
a\\b
\end{bmatrix}
$$

Let:

$$
\begin{bmatrix}
x_1&x_2\\x_3&x_4
\end{bmatrix}
=
\cdots 
\begin{bmatrix}
0&1\\1&-\lfloor a/b\rfloor
\end{bmatrix}
\begin{bmatrix}
1&0\\0&1
\end{bmatrix}
$$

Then:

$$
\begin{bmatrix}
\gcd(a,b)\\0
\end{bmatrix}
=
\begin{bmatrix}
x_1&x_2\\x_3&x_4
\end{bmatrix}
\begin{bmatrix}
a\\b
\end{bmatrix}
$$

Satisfying $a\cdot x_1+b\cdot x_2=\gcd(a,b)$ is the Extended Euclidean Algorithm. Note that multiplying by an identity matrix at the end does not affect the result, which tells us that we can maintain a $2\times 2$ identity matrix at the beginning to write a simpler iterative method:

```cpp
int exgcd(int a, int b, int &x, int &y) {
  int x1 = 1, x2 = 0, x3 = 0, x4 = 1;
  while (b != 0) {
    int c = a / b;
    std::tie(x1, x2, x3, x4, a, b) =
        std::make_tuple(x3, x4, x1 - x3 * c, x2 - x4 * c, b, a - b * c);
  }
  x = x1, y = x2;
  return a;
}
```

This representation is simpler than recursion.

## Applications

-   [10104 - Euclid Problem](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1045)
-   [GYM - (J) once upon a time](http://codeforces.com/gym/100963)
-   [UVa - 12775 - Gift Dilemma](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4628)

## References and Links

[^1]: [libstdc++: std Namespace Reference](https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.4/a00978.html#a2686a128df5a576cb53a1ed5f674607)
