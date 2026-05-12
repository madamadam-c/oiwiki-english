This article discusses solving linear congruence equations.

## Basic Concepts

Let $a, b, n$ be integers and $x$ be the unknown. An equation of the form

$$
ax \equiv b \pmod n
$$

is called a **linear congruence equation**.

To solve a linear congruence equation, we need to find all solutions $x$ in the interval $[0, n-1]$. Of course, adding or subtracting any multiple of $n$ from them still yields a solution. Under modulo $n$, these are all the solutions to the equation.

This article presents two approaches to solving linear congruence equations, using modular inverses and Diophantine equations respectively. For the general case, both require the [extended Euclidean algorithm](./gcd.md#extended-euclidean-algorithm), so the two approaches are essentially equivalent.

## Solving Using Modular Inverses

First, consider the case where $a$ and $n$ are coprime, i.e., $\gcd(a, n) = 1$. In this case, we can compute the [modular inverse](./inverse.md) $a^{-1}$ of $a$, and multiply both sides of the equation by $a^{-1}$, giving the unique solution:

$$
x \equiv ba^{-1} \pmod n.
$$

Next, consider the case where $a$ and $n$ are not coprime, i.e., $\gcd(a, n) = d > 1$. In this case, the original equation may have no solution. For example, $2x \equiv 1 \pmod 4$ has no solution. Therefore, we need to consider two cases:

-   When $d$ does not divide $b$, the equation has no solution. For any $x$, the left side $ax$ is a multiple of $d$, but the right side $b$ is not a multiple of $d$. Therefore, they cannot differ by a multiple of $n$, since any multiple of $n$ is also a multiple of $d$. Hence, the equation has no solution.

-   When $d$ divides $b$, we can divide all parameters $a, b, n$ by $d$ to obtain a new equation:

    $$
    a'x \equiv b' \pmod{n'}.
    $$

    Here, $\gcd(a', n') = 1$, i.e., $a'$ and $n'$ are coprime. This case has already been solved above, so we can obtain a solution $x'$ to the equation using the modular inverse.

    Clearly, $x'$ is also a solution to the original equation. But this is not the only solution. Since the complete set of solutions to the transformed equation is

    $$
    \{x' + kn' : k \in \mathbf Z\},
    $$

    those among these solutions that lie in the interval $[0, n-1]$ are all the solutions to the original equation in that interval:

    $$
    x \equiv (x' + kn') \pmod{n}, \quad k = 0, 1, \cdots, d-1.
    $$

Summarizing these two cases, the **number of solutions** to a linear congruence equation equals $d = \gcd(a, n)$ or $0$.

## Solving Using Diophantine Equations

A linear congruence equation is equivalent to a [binary linear Diophantine equation](./bezouts.md#the-two-variable-case) in $x$ and $y$:

$$
ax + ny = b.
$$

Using the discussion from the referenced page, the equation has a solution if and only if $\gcd(a, n) \mid b$, and a general solution to this equation is

$$
\begin{aligned}
x & = x_0 + t\frac{n}{d},\\
y & = y_0 - t\frac{a}{d},
\end{aligned}
$$

where $d = \gcd(a, n)$ is their greatest common divisor and $t$ is any integer.

Consequently, the general solution to the linear congruence equation is

$$
x \equiv \left(x_0 + t\frac{n}{d}\right) \pmod{n}, \quad t \in \mathbf Z.
$$

Taking $x_0$ modulo $n/d$ yields the smallest non-negative integer solution to the congruence equation, which is $x'$ from above.

## Reference Implementation

This section provides a reference implementation that returns the smallest non-negative integer solution to a congruence equation. If no solution exists, it outputs $-1$.

???+ example "Reference Implementation"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/linear-equation/linear-equation.cpp:core"
        ```

    === "Python"
        ```python
        --8<-- "docs/math/code/linear-equation/linear-equation.py:core"
        ```

## Practice Problems

-   [「NOIP2012」同余方程](https://loj.ac/problem/2605)

**This page is mainly translated from the article [Модульное линейное уравнение первого порядка](http://e-maxx.ru/algo/diofant_1_equation) and its English translation [Linear Congruence Equation](https://cp-algorithms.com/algebra/linear_congruence_equation.html). The Russian version is in the public domain with a link requirement; the English version is under CC-BY-SA 4.0. Content has been modified.**