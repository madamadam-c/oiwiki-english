author: Marcythm, iamtwz, nutshellfool, sshwy, allenanswerzq, countercurrent-time, Enter-tainer, H-J-Granger, hly1204, Ir1d, Menci, NachtgeistW, SukkaW, Tiphereth-A, Xeonacid

## Introduction

This article introduces how to use Newton's method (Newton's method for finding roots) to find approximate solutions to equations, a method proposed by Newton in the 17th century.

The specific task is, for a function $f(x)$ that is continuous and monotonic on $[a,b]$, find an approximate solution to the equation $f(x)=0$.

## Explanation

Initially, we start with a given $f(x)$ and an approximate solution $x_0$ (the initial value problem is related to Newton's fractal; see 3Blue1Brown's [Newton Fractal](https://www.bilibili.com/video/BV1HQ4y1q78v)).

Suppose our current approximate solution is $x_i$. We draw the line $l$ tangent to $f(x)$ at the point $(x_i, f(x_i))$, and let $x_{i+1}$ be the x-coordinate of the intersection of $l$ with the x-axis. This is a better approximate solution. Repeat this iterative process.
Based on the geometric meaning of the derivative, we can obtain the following relationship:

$$
f'(x_i) = \frac{f(x_i)}{x_{i} - x_{i+1}}
$$

Rearranging gives the following recurrence formula:

$$
x_{i+1} = x_i - \frac{f(x_i)}{f'(x_i)}
$$

Intuitively, if $f(x)$ is relatively smooth, then as the number of iterations increases, $x_i$ will get closer and closer to the solution of the equation.

The convergence rate of Newton's method is quadratic, meaning the number of accurate digits in the approximate solution roughly doubles after each iteration.
For a proof of the convergence of Newton's method, refer to [citizendium - Newton method Convergence analysis](http://en.citizendium.org/wiki/Newton%27s_method#Convergence_analysis)

Of course, Newton's method also has its drawbacks. For details, refer to [Xiaolin Wu - Roots of Equations pages 18-20](https://www.ece.mcmaster.ca/~xwu/part2.pdf)

## Computing Square Roots

We try to use Newton's method to compute square roots. Let $f(x) = x^2 - n$, and the approximate solution to this equation is an approximation of $\sqrt{n}$. Thus we get:

$$
x_{i+1}=x_i-\frac{x_i^2-n}{2x_i}=\frac{x_i+\frac{n}{x_i}}{2}
$$

When implementing, pay attention to set an appropriate precision. The code is as follows:

### Implementation

=== "C++"
    ```cpp
    double sqrt_newton(double n) {
      constexpr static double eps = 1E-15;
      double x = 1;
      while (true) {
        double nx = (x + n / x) / 2;
        if (abs(x - nx) < eps) break;
        x = nx;
      }
      return x;
    }
    ```

=== "Python"
    ```python
    def sqrt_newton(n):
        eps = 1e-15
        x = 1
        while True:
            nx = (x + n / x) / 2
            if abs(x - nx) < eps:
                break
            x = nx
        return x
    ```

## Computing Integer Square Roots

Although we can call the `sqrt()` function to get the square root value, here we still discuss a variant of Newton's method for finding the largest integer $x$ satisfying $x^2 \le n$. We still consider a process similar to Newton's method, but need to make slight modifications to the boundary conditions. If during iteration the approximate solution decreased in the previous iteration but increased in this iteration, we do not perform this iteration and exit the loop.

### Implementation

=== "C++"
    ```cpp
    int isqrt_newton(int n) {
      int x = 1;
      bool decreased = false;
      for (;;) {
        int nx = (x + n / x) >> 1;
        if (x == nx || (nx > x && decreased)) break;
        decreased = nx < x;
        x = nx;
      }
      return x;
    }
    ```

=== "Python"
    ```python
    def isqrt_newton(n):
        x = 1
        decreased = False
        while True:
            nx = (x + n // x) // 2
            if x == nx or (nx > x and decreased):
                break
            decreased = nx < x
            x = nx
        return x
    ```

## High-Precision Square Roots

Finally, consider high-precision Newton's method. The iteration method remains the same, but this time we need to pay attention to the initial approximate solution, i.e., the value of $x_0$. Since numbers requiring high precision are generally very large, different initial values have a significant impact on algorithm efficiency. A natural approach is to consider $x_0 = 2^{\left\lfloor\frac{1}{2}\log_2n\right\rfloor}$, which not only allows quick computation of $x_0$ but also gets reasonably close to the square root.

### Implementation

The Java implementation is given below:

```java
public static BigInteger isqrtNewton(BigInteger n) {
  BigInteger a = BigInteger.ONE.shiftLeft(n.bitLength() / 2);
  boolean p_dec = false;
  for (;;) {
    BigInteger b = n.divide(a).add(a).shiftRight(1);
    if (a.compareTo(b) == 0 || a.compareTo(b) < 0 && p_dec)
      break;
    p_dec = a.compareTo(b) > 0;
    a = b;
  }
  return a;
}
```

In practice: when $n = 10^{1000}$, the running time of this algorithm is 60 ms. If we don't optimize $x_0$ and start directly from $x_0 = 1$, the running time increases to 120 ms.

## Exercises

-   [UVa 10428 - The Roots](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1369)
-   [LeetCode 69. Sqrt(x)](https://leetcode-cn.com/problems/sqrtx/)

    **This page is mainly translated from the blog post [Метод Ньютона (касательных) для поиска корней](http://e-maxx.ru/algo/roots_newton) and its English translation [Newton's method for finding roots](https://cp-algorithms.com/num_methods/roots_newton.html). The Russian version is in the Public Domain with Leave a Link; the English version is under CC-BY-SA 4.0.**