author: 383494, CCXXXI, chunibyo-wly, Enter-tainer, Great-designer, megakite, Menci, shawlleyw, shuzhouliu, StudyingFather, Tiphereth-A, untitledunrevised, c-forrest

## Introduction

A continued fraction represents a real number as the limit of a sequence of convergent rational numbers. The rational numbers in this sequence are easy to compute and provide the best approximations to the real number, which is why continued fractions are often used in algorithm competitions. In addition, continued fractions are closely related to the Euclidean algorithm, and thus can be applied to a series of number theory problems.

???+ info "About the algorithm implementations for continued fractions"
    This article will provide several continued fraction algorithm implementations, some of which may not guarantee that all integers involved in the intermediate computation process fall within the range of 32-bit or 64-bit integer variables. For such cases, please refer to the corresponding Python implementation, or replace the integer variables in the C++ implementation with [high-precision integer types](../bignum.md). To highlight the key points, some code in this article may call functions implemented earlier without repeating the implementation.

## Continued Fractions

A **continued fraction** is itself merely a formal notation.

???+ abstract "Finite continued fraction"
    For a sequence $\{a_k\}_{i=0}^n$, the continued fraction $[a_0,a_1,\cdots,a_n]$ represents the expansion
    
    $$
    x = a_0+\dfrac{1}{a_1+\dfrac{1}{a_2+\dfrac{1}{\cdots+\dfrac{1}{a_n}}}}.
    $$
    
    The continued fraction is meaningful if and only if the corresponding expansion is meaningful. These $a_k$ are called the **terms** or **coefficients** of the continued fraction.

???+ info "Notation"
    More general continued fractions allow the numerators in the expansion not to be always 1, and the corresponding continued fraction notation also needs to be modified, which is beyond the scope of this article. Also, in some literature, the first comma "$,$" may be written as a semicolon "$;$", which does not differ in meaning from the notation in this article.

Of course, continued fractions can also be extended to the case of infinite sequences.

???+ abstract "Infinite continued fraction"
    For an infinite sequence $\{a_k\}_{i=0}^\infty$, the continued fraction $[a_0,a_1,\cdots]$ represents the limit
    
    $$
    x = \lim_{k\rightarrow\infty} x_k = \lim_{k\rightarrow\infty} [a_0,a_1,\cdots,a_k].
    $$
    
    The continued fraction is meaningful if and only if the corresponding limit is meaningful. Here, $x_k=[a_0,a_1,\cdots,a_k]$ is called the $k$-th **convergent** of $x$, and $r_k=[a_k,a_{k+1},\cdots]$ is called the $k$-th **remainder** or **complete quotient** of $x$. Accordingly, the term $a_k$ is sometimes also called the $k$-th **partial quotient**.

### Simple Continued Fractions

In number theory, we mainly consider continued fractions where all terms are integers.

???+ abstract "Simple continued fraction"
    For a continued fraction $[a_0,a_1,\cdots]$, if $a_0$ is an integer and $a_1,a_2,\cdots$ are all positive integers, then it is called a **simple continued fraction**, also simply called a **continued fraction**. If the sequence $\{a_i\}$ is finite, it is called a **finite (simple) continued fraction**; otherwise, it is called an **infinite (simple) continued fraction**. Moreover, $a_0$ is called its **integer part**.

Unless otherwise specified, continued fractions in this article refer to simple continued fractions. It can be proved that infinite simple continued fractions are necessarily convergent, and the remainders of simple continued fractions are also necessarily positive.

Continued fractions have the following basic properties:

???+ note "Properties"
    Let $x=[a_0,a_1,a_2,\cdots]$. Then the following properties hold:
    
    1.  For any $k\in\mathbf Z$, we have $x+k=[a_0+k,a_1,a_2,\cdots]$;
    2.  For a real number $x>1$, we have $a_0>0$, and its reciprocal $x^{-1}=[0,a_0,a_1,a_2,\cdots]$.

Finite continued fractions correspond to rational numbers. Every rational number can be represented as a continued fraction in exactly two ways, with lengths necessarily odd and even. The only difference between these two representations is whether the last term is $1$, i.e.,

$$
x = [a_0,a_1,\cdots,a_n] = [a_0,a_1,\cdots,a_n-1,1].
$$

These two continued fractions are called the **continued fraction representations** of the rational number $x$. Among them, the one with the last term not equal to $1$ is called the standard representation, and the one with the last term equal to $1$ is called the non-standard representation.[^one-representation]

??? example "Example"
    The continued fraction representation of the rational number $x=\dfrac{5}{3}$ is
    
    $$
    \begin{aligned}
    x = [1,1,1,1] &= 1+\dfrac{1}{1+\dfrac{1}{1+\dfrac{1}{1}}},\\
    x = [1,1,2] &= 1+\dfrac{1}{1+\dfrac{1}{2}}.
    \end{aligned}
    $$

Infinite continued fractions correspond to irrational numbers. Moreover, every irrational number can be represented as a continued fraction in exactly one way, which is called the continued fraction representation of the irrational number.

### Computing the Continued Fraction Representation

To find the continued fraction representation of a real number $x$, one only needs to note that if its remainder $r_k$ is not an integer, it must satisfy

$$
r_k = [a_k,a_{k+1},\cdots] = [a_k,r_{k+1}] = a_k + \dfrac{1}{r_{k+1}}.
$$

Moreover, $r_{k+1}>1$. Therefore, we can recursively compute starting from $r_0=x$

$$
a_k = \lfloor r_k\rfloor,\ r_{k+1} = \dfrac{1}{r_k-a_k}.
$$

The sequence $\{a_k\}$ generated by this process is always uniquely determined, unless some remainder $r_k$ becomes an integer. If $r_k$ becomes an integer, the process should terminate, and we can choose to output either the standard representation or the non-standard representation.

In algorithm competitions, we often deal with rational numbers $x=\dfrac{p}{q}$. In this case, each remainder $r_k$ is a rational number $\dfrac{p_k}{q_k}$, and for $k>0$, since $r_k>1$, we always have $p_k>q_k$. Computing the recurrence relation, we can discover that

$$
a_k = \left\lfloor\frac{p_k}{q_k}\right\rfloor,\ r_{k+1} = \dfrac{1}{r_k-a_k} = \dfrac{q_k}{p_k-a_kq_k} = \dfrac{q_k}{p_k\bmod q_k}.
$$

This computation process is actually the [Euclidean algorithm](./gcd.md#欧几里得算法) performed on $p$ and $q$. This also shows that for a rational number $r=\dfrac{p}{q}$, the length of the continued fraction representation is $O(\log\min\{p, q\})$. The complexity of computing the continued fraction representation of $\dfrac{p}{q}$ is also $O(\log\min\{p, q\})$.

???+ example "Reference implementation"
    Given the numerator $p$ and denominator $q$ of a fraction, output the continued fraction coefficient sequence $[a_0,a_1,\cdots,a_n]$.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/diophantine.cpp:fraction"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/diophantine.py:fraction"
        ```

## Convergents

The concept of convergents was introduced in the definition of continued fractions. The convergents of a real number are the convergents of its continued fraction representation: in the continued fraction representation of a real number $x$, keeping only the first $k$ terms, the obtained continued fraction $x_k$ is called the $k$-th convergent of the real number $x$. The convergents $x_k$ of a real number $x$ are all rational numbers, and the sequence $\{x_k\}$ converges to the real number $x$.

??? example "Example: Convergents of the golden ratio"
    The first few convergents of the continued fraction $x=[1,1,1,1,\cdots]$ are
    
    $$
    \begin{aligned}
    x_0 &= [1]=1,\\
    x_1 &= [1,1]=2,\\
    x_2 &= [1,1,1]=\dfrac{3}{2},\\
    x_3 &= [1,1,1,1]=\dfrac{5}{3},\\
    x_4 &= [1,1,1,1,1]=\dfrac{8}{5}.
    \end{aligned}
    $$
    
    It can be proved by induction that
    
    $$
    x_k = \frac{F_{k+2}}{F_{k+1}},
    $$
    
    where $\{F_k\}$ is the [Fibonacci sequence](../combinatorics/fibonacci.md). According to its general term formula,
    
    $$
    x_k = \frac{\phi^{k+2}-(-\phi)^{-(k+2)}}{\phi^{k+1}-(-\phi)^{-(k+1)}},
    $$
    
    where $\phi=\dfrac{1+\sqrt{5}}{2}$ is the golden ratio. As $k$ tends to infinity,
    
    $$
    x=\lim_{k\rightarrow\infty}x_k=\phi.
    $$
    
    Therefore, the continued fraction $x=[1,1,1,1,\cdots]$ represents the golden ratio $\phi$.

These convergents approach the corresponding real numbers, so they can be used to approximate the real numbers. For this purpose, it is necessary to understand the properties of convergents.

### Recurrence Relations

First, we need to solve the computation problem of these convergents. Although convergents are always obtained by adding one term to the continued fraction, we do not need to recompute its value each time. In fact, convergents have the following recurrence relations:

???+ note "Recurrence formula"
    For the continued fraction $x=[a_0,a_1,a_2,\cdots]$, let its $k$-th convergent $x_k$ be written as the fraction $\dfrac{p_k}{q_k}$. Then we have
    
    $$
    \begin{aligned}
    p_k &= a_kp_{k-1}+p_{k-2},\\
    q_k &= a_kq_{k-1}+q_{k-2}.
    \end{aligned}
    $$
    
    The starting point of the recurrence is the (formal) fractions
    
    $$
    x_{-1}=\frac{p_{-1}}{q_{-1}}=\frac{1}{0},\ x_{-2}=\frac{p_{-2}}{q_{-2}}=\frac{0}{1}.
    $$

??? note "Proof"
    The numerator and denominator of the convergent $x_k$ can be regarded as multivariate polynomials in $a_0, a_1, \cdots, a_k$:
    
    $$
    r_k = \frac{P_k(a_0, a_1, \cdots, a_k)}{Q_k(a_0,a_1, \cdots, a_k)}.
    $$
    
    According to the definition of convergents,
    
    $$
    r_k = a_0 + \frac{1}{[a_1,a_2,\cdots, a_k]}= a_0 + \frac{Q_{k-1}(a_1, \cdots, a_k)}{P_{k-1}(a_1, \cdots, a_k)} = \frac{a_0 P_{k-1}(a_1, \dots, a_k) + Q_{k-1}(a_1, \cdots, a_k)}{P_{k-1}(a_1, \cdots, a_k)}.
    $$
    
    Comparing with the above equation, if we set $Q_k(a_0, \cdots, a_k) = P_{k-1}(a_1, \cdots, a_k)$, then the convergent can be written as
    
    $$
    r_k =  \frac{P_k(a_0, a_1, \cdots, a_k)}{P_{k-1}(a_1, \cdots, a_k)}
    $$
    
    and the polynomial $P_k$ satisfies the recurrence relation
    
    $$
    P_k(a_0, \cdots, a_k) = a_0 P_{k-1}(a_1, \cdots, a_k) + P_{k-2}(a_2, \cdots, a_k).
    $$
    
    Because
    
    $$
    r_0 = a_0,\ r_1 = a_0+\dfrac{1}{a_1} = \frac{a_0a_1+1}{a_1},
    $$
    
    the starting point of the recurrence is
    
    $$
    P_0(a_0) = a_0,\ P_1(a_0,a_1) = a_0a_1 + 1.
    $$
    
    If we set
    
    $$
    P_{-1} = 1,\ P_{-2} = 0,
    $$
    
    we can verify that the above recurrence relation also holds for $k=0,1$. This is equivalent to specifying the formal fractions $r_{-1}=\dfrac{1}{0}$ and $r_{-2}=\dfrac{0}{1}$.
    
    The sequence of polynomials $P_k$ satisfying the above recurrence relation is called the **continuant**[^continuant]. It can be written in the form of a determinant:
    
    $$
    P_k(a_0,\cdots,a_k)=\det
    \begin{pmatrix}
    a_0 & 1 & 0 & \cdots & 0 \\
    -1 & a_1 & 1 & \ddots & \vdots \\
    0 & -1 & a_2 & \ddots & 0 \\
    \vdots & \ddots & \ddots & \ddots & 1 \\
    0 & \cdots & 0 & -1 & a_k
    \end{pmatrix}.
    $$
    
    This is the determinant of a [tridiagonal matrix](https://en.wikipedia.org/wiki/Tridiagonal_matrix). Expanding from the upper left corner, we can verify that it has the above recurrence relation and initial conditions. Conversely, expanding from the lower right corner, we obtain the recurrence relation
    
    $$
    P_k(a_0, \cdots, a_k) = a_k P_{k-1}(a_0, \cdots, a_{k-1}) + P_{k-2}(a_0, \cdots, a_{k-2}),
    $$
    
    which is what we wanted to prove.

???+ info "Notation"
    When this article writes the convergent $x_k$ as $\dfrac{p_k}{q_k}$, it is always understood that the numerator $p_k$ and denominator $q_k$ are given by the above recurrence relation. Below, we will also show that this always gives the reduced form of the convergents.

This recurrence formula shows that

$$
x_k=\dfrac{a_kp_{k-1}+p_{k-2}}{a_kq_{k-1}+q_{k-2}}
$$

lies between $x_{k-1}$ and $x_{k-2}$.

As corollaries of the recurrence relation for convergents, the reverse order theorem and reciprocal theorem hold:

???+ note "Reverse order theorem"
    Let the $k$-th convergent of the real number $x=[a_0,a_1,a_2,\cdots]$ be $\dfrac{p_k}{q_k}$. Then the ratios of numerators and denominators of consecutive convergents are respectively
    
    $$
    \begin{aligned}
    \frac{p_k}{p_{k-1}}&=[a_k,a_{k-1},\cdots,a_1,a_0],\\
    \frac{q_k}{q_{k-1}}&=[a_k,a_{k-1},\cdots,a_1].
    \end{aligned}
    $$
    
    If $a_0=0$, then the first continued fraction should be understood as truncated at the second-to-last term, i.e., $[a_k,a_{k-1},\cdots,a_2]$.

??? note "Proof"
    In the recurrence relations for $p_k$ and $q_k$, dividing both sides by $p_{k-1}$ and $q_{k-1}$ respectively, we obtain
    
    $$
    \begin{aligned}
    \frac{p_k}{p_{k-1}} &= a_k + \frac{p_{k-2}}{p_{k-1}},\\
    \frac{q_k}{q_{k-1}} &= a_k + \frac{q_{k-2}}{q_{k-1}}.
    \end{aligned}
    $$
    
    Iterating these two equations, we obtain two continued fractions. Then substituting the initial values $\dfrac{p_0}{p_{-1}}=a_0$ and $\dfrac{q_1}{q_0}=a_1$. For the case $a_0=0$, if we understand the obtained continued fraction as a formal expression, then its remainder
    
    $$
    [a_2,a_1,0]=a_2+\dfrac{1}{a_1+\dfrac{1}{0}}=a_2+\dfrac{0}{0a_1+1}=a_2.
    $$
    
    Therefore, the last two terms can be omitted directly. For a strict proof, one only needs to note that this equation can be seen as the limit as $a_0\rightarrow 0$.

???+ note "Reciprocal theorem"
    The reciprocals of the convergents of a real number $x>0$ are the convergents of $x^{-1}$.

??? note "Proof"
    Let $x>1$ have the continued fraction representation $[a_0,a_1,a_2,\cdots]$, then the continued fraction representation of $x^{-1}$ is $[0,a_0,a_1,a_2,\cdots]$. Their convergents can be obtained from the recurrence relations. Moreover, for $x$, we have initial conditions $x_{-2}=\dfrac{0}{1}$ and $x_{-1}=\dfrac{1}{0}$; for $y=x^{-1}$, we have initial conditions $y_{-1}=\dfrac{1}{0}$ and $y_{0}=\dfrac{0}{1}$. Therefore, we have $x_{-2}=(y_{-1})^{-1}$ and $x_{-1}=(y_0)^{-1}$. From the recurrence relation, we obtain $x_k=y_{k+1}^{-1}$. This shows that the reciprocals of the convergents of $x$ are the convergents of $y=x^{-1}$. For the case $0<x\le 1$, a similar discussion can be made.

Using the recurrence relation obtained in this section, we can derive the following algorithm for computing convergents:

???+ example "Reference implementation"
    Given the continued fraction coefficients $a_0,a_1,\cdots,a_n$, find the sequences of numerators and denominators of convergents $(p_0,q_0),(p_1,q_1),\cdots,(p_n,q_n)$.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/diophantine.cpp:convergents"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/diophantine.py:convergents"
        ```

### Error Estimation

Using the recurrence formula for convergents, we can estimate the error generated when approximating a real number with convergents.

First, we can compute the difference between consecutive convergents:

???+ note "Difference of convergents"
    Let $x_k=\dfrac{p_k}{q_k}$ be the $k$-th convergent of the real number $x$. Then we have
    
    $$
    p_{k+1}q_k − p_kq_{k+1} = (−1)^k.
    $$
    
    Therefore, the difference between consecutive convergents is
    
    $$
    x_{k+1} - x_k = \dfrac{(-1)^k}{q_{k+1}q_k}.
    $$

??? note "Proof"
    According to the recurrence relation, we have
    
    $$
    \begin{aligned}
    \det\begin{pmatrix}
    p_{k+1} & p_k \\
    q_{k+1} & q_k 
    \end{pmatrix}
    &=
    \det\begin{pmatrix}
    a_{k+1}p_{k}+p_{k-1} & p_k \\
    a_{k+1}q_{k}+q_{k-1} & q_k 
    \end{pmatrix}
    =
    \det\begin{pmatrix}
    p_{k-1} & p_k\\
    q_{k-1} & q_k
    \end{pmatrix}
    \\
    &=
    -
    \det\begin{pmatrix}
    p_k & p_{k-1}\\
    q_k & q_{k-1}
    \end{pmatrix}
    =
    (-1)^{k+2}
    \det\begin{pmatrix}
    1 & 0\\
    0 & 1
    \end{pmatrix}
    =(-1)^k.
    \end{aligned}
    $$
    
    This is $p_{k+1}q_k − p_kq_{k+1} = (−1)^k$. Dividing both sides by $q_{k+1}q_k$, we obtain the conclusion about $x_{k+1}-x_k$.

Therefore, odd-indexed convergents are always greater than the adjacent terms, and even-indexed convergents are always less than the adjacent terms: convergents alternate.

If we only consider even-indexed (odd-indexed) convergents, the sequence is also monotonically increasing (decreasing). This is because

$$
x_{k+2}-x_k = \dfrac{(-1)^{k+1}}{q_{k+2}q_{k+1}}+\dfrac{(-1)^{k}}{q_{k+1}q_{k}} = \dfrac{(-1)^k(q_{k+2}-q_k)}{q_{k+2}q_{k+1}q_k} = \dfrac{(-1)^ka_{k+2}}{q_{k+2}q_k}
$$

which is positive (negative) when $k$ is even (odd). At the same time, because the recurrence relation $q_{k}=a_kq_{k-1}+q_{k-2}$ holds, the growth rate of denominators $q_k$ is no slower than that of the Fibonacci sequence. Therefore, the difference between consecutive terms must tend to zero. This shows that even-indexed and odd-indexed convergents approach the same limit from below and above respectively. This proves that infinite simple continued fractions must converge. The dynamics of convergents approaching the corresponding real number can be seen in the following figure:

![](./images/golden-ratio-convergents.svg)

???+ abstract "Upper (lower) convergent"
    For a real number $x$ and its convergent $x_k$, if $x_k>x$ ($x_k<x$), then $x_k$ is called the **upper (lower) convergent** of $x$.

As explained earlier, upper convergents are odd-indexed convergents, and lower convergents are even-indexed convergents.

Using the difference formula, we can express the real number $x$ as an alternating series:

$$
x = a_0+\sum_{k=0}^{\infty}\dfrac{(-1)^k}{q_{k+1}q_k}.
$$

The convergents and remainders in the continued fraction definition are respectively the partial sums and remainders of this series.

Using the difference formula, we can also directly estimate the error in approximating a real number with convergents:

???+ note "Error"
    Let $x_k=\dfrac{p_k}{q_k}\neq x$ be the $k$-th convergent of the real number $x$. Then we have
    
    $$
    x_k - x = \dfrac{(-1)^k}{q_k\left(r_{k+1}q_k+q_{k-1}\right)},
    $$
    
    where $r_{k+1}$ is the $(k+1)$-th remainder of the real number $x$. Furthermore, we have
    
    $$
    \dfrac{1}{2q_{k+1}^2} \le \dfrac{1}{q_k(q_k+q_{k+1})} \le \left|x-\frac{p_k}{q_k}\right| \le \dfrac{1}{q_kq_{k+1}} \le \dfrac{1}{q_k^2}.
    $$

??? note "Proof"
    Since $x=[a_0,a_1,\cdots,a_k,r_{k+1}]$, and the difference formula for convergents also holds for formal continued fractions, we have
    
    $$
    x-x_k = \dfrac{(-1)^k}{q_k\left(r_{k+1}q_k+q_{k-1}\right)},
    $$
    
    where $r_{k+1}q_k+q_{k-1}$ is the denominator of the $(k+1)$-th convergent of this formal continued fraction obtained according to the recurrence formula.
    
    To complete the inequality estimation, we only need to note that when $x_k\neq x$, we always have
    
    $$
    1\le a_{k+1}\le r_{k+1} \le a_{k+1}+1,
    $$
    
    so we have
    
    $$
    q_{k+1}=a_{k+1}q_k+q_{k-1}\le r_{k+1}q_k+q_{k-1} \le q_k+(a_{k+1}q_k+q_{k-1}) = q_k+q_{k+1}.
    $$
    
    Therefore, we have the inequality
    
    $$
    \dfrac{1}{q_k(q_k+q_{k+1})} \le \left|x-\frac{p_k}{q_k}\right| = \dfrac{1}{q_k\left(r_{k+1}q_k+q_{k-1}\right)} \le \dfrac{1}{q_kq_{k+1}}.
    $$
    
    To get the outer bounds, we only need to note that $q_k\le q_{k+1}$.

A simple corollary of the difference formula in this section is: all convergents $\dfrac{p_k}{q_k}$ are reduced.

???+ note "Corollary"
    For any real number $x$, and the convergent $x_k=\dfrac{p_k}{q_k}$ whose numerator and denominator are given by the recurrence formula, then $\dfrac{p_k}{q_k}$ is a reduced fraction, i.e., $\gcd(p_k,q_k)=1$.

??? note "Proof"
    Apply the [Bézout's theorem](./bezouts.md) to the difference formula.

In fact, solutions to linear Diophantine equations in two variables can be solved using continued fractions.

???+ example "Solving linear Diophantine equations in two variables"
    Given $A, B, C \in \mathbf Z$. Find $x, y \in \mathbf Z$ such that $Ax + By = C$ holds.

??? note "Solution"
    Although this problem is usually solved using the [extended Euclidean algorithm](./bezouts.md#两个变量的情形), it can also be solved using continued fractions.
    
    Let $\dfrac{A}{B}=[a_0, a_1, \cdots, a_k]$. Above, we proved $p_k q_{k-1} - p_{k-1} q_k = (-1)^{k-1}$. Substituting $p_k$ and $q_k$ with $A$ and $B$, we obtain
    
    $$
    Aq_{k-1} - Bp_{k-1} = (-1)^{k-1} g,
    $$
    
    where $g = \gcd(A, B)$. If $g$ divides $C$, then one solution is $x = (-1)^{k-1}\dfrac{C}{g} q_{k-1}$ and $y = (-1)^{k}\dfrac{C}{g} p_{k-1}$; otherwise there is no solution.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/diophantine.cpp:dio"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/diophantine.py:dio"
        ```

## Diophantine Approximation

An important application of continued fraction theory is Diophantine approximation theory. Diophantine approximation refers to approximating real numbers with rational numbers. Of course, due to the density of rational numbers, if there are no restrictions, we can obtain approximations with arbitrarily small errors. Therefore, restrictions need to be imposed on which rational numbers can be used, such as only allowing rational numbers with denominators less than some value. This section discusses the relationship between the best approximations under such restrictions and continued fractions.

### Approximating Real Numbers with Convergents

First, using the error estimation for convergents, we immediately obtain the following result:

???+ note "Theorem (Dirichlet)"
    For an irrational number $x$, there exist infinitely many reduced fractions $\dfrac{p}{q}$ such that
    
    $$
    \left|x-\dfrac{p}{q}\right| < \dfrac{1}{q^2} 
    $$
    
    holds.

??? note "Proof"
    According to the error estimation for convergents, for the $k$-th convergent $x_k=\dfrac{p_k}{q_k}$ of an irrational number $x$, we have
    
    $$
    \left|x-\dfrac{p_k}{q_k}\right|\le\frac{1}{q_k^2}.
    $$
    
    By examining the proof of the error formula, we know that the equality condition does not hold for any irrational number $x$. Therefore, all its convergents satisfy the requirement.

This theorem can also be seen as a corollary of [Dirichlet's approximation theorem](https://en.wikipedia.org/wiki/Dirichlet%27s_approximation_theorem). This is almost the best possible result. The exponent 2 in the denominator on the right-hand side cannot be improved, but the constant can be made better. Hurwitz's theorem shows that the right-hand side can be reduced to $\dfrac{1}{\sqrt{5}q^2}$, and this is the best bound.

???+ note "Hurwitz's theorem"
    For an irrational number $x$, there exist infinitely many reduced fractions $\dfrac{p}{q}$ such that
    
    $$
    \left|x-\dfrac{p}{q}\right| < \dfrac{1}{\sqrt{5}q^2} 
    $$
    
    holds, and the $\sqrt{5}$ on the right-hand side cannot be replaced by a larger real number.

??? note "Proof (Borel)"
    In fact, Borel proved that among every three consecutive convergents of an irrational number $x$, at least one satisfies the above condition. Since there are infinitely many convergents and they are all reduced fractions, the first part of Hurwitz's theorem must hold.
    
    Proof by contradiction. Suppose there exists an irrational number $x$ and its convergents $x_{k-1},x_k,x_{k+1}$ such that
    
    $$
    \left|x-\dfrac{p_{k-1}}{q_{k-1}}\right|\ge\dfrac{1}{\sqrt{5}q_{k-1}^2},\ 
    \left|x-\dfrac{p_{k}}{q_{k}}\right|\ge\dfrac{1}{\sqrt{5}q_{k}^2},\ 
    \left|x-\dfrac{p_{k+1}}{q_{k+1}}\right|\ge\dfrac{1}{\sqrt{5}q_{k+1}^2}
    $$
    
    hold. Since consecutive convergents are necessarily on both sides of $x$, by the difference formula we have
    
    $$
    \dfrac{1}{q_{k-1}q_{k}}=\left|\dfrac{p_{k-1}}{q_{k-1}}-\dfrac{p_{k}}{q_{k}}\right|=\left|x-\dfrac{p_{k-1}}{q_{k-1}}\right|+\left|x-\dfrac{p_{k}}{q_{k}}\right|\ge\dfrac{1}{\sqrt{5}q_{k-1}^2}+\dfrac{1}{\sqrt{5}q_{k}^2}.
    $$
    
    It can be rewritten as an inequality in terms of the ratio $\dfrac{q_{k}}{q_{k-1}}$
    
    $$
    \dfrac{q_k}{q_{k-1}}+\dfrac{q_{k-1}}{q_k}\le\sqrt 5.
    $$
    
    Since the left side is a rational number and the right side is an irrational number, the equality cannot hold. And since $q_k\ge q_{k-1}$, we can solve to get
    
    $$
    1\le \dfrac{q_{k}}{q_{k-1}} < \dfrac{\sqrt{5}+1}{2}.
    $$
    
    Similarly, we can prove
    
    $$
    1\le \dfrac{q_{k+1}}{q_{k}} < \dfrac{\sqrt{5}+1}{2}.
    $$
    
    However, according to the recurrence formula, combining the two equations, we have
    
    $$
    a_{k+1} = \frac{q_{k+1}}{q_k}-\frac{q_{k-1}}{q_k} < \dfrac{\sqrt{5}+1}{2}-\dfrac{\sqrt{5}-1}{2} = 1
    $$
    
    which contradicts the definition of simple continued fractions. Therefore, Borel's conclusion holds.
    
    To show that this bound is the best, we only need to find an $x$ such that for any $C>\sqrt{5}$, there are only finitely many reduced fractions $\dfrac{p}{q}$ satisfying
    
    $$
    \left|x-\dfrac{p}{q}\right| < \dfrac{1}{Cq^2} 
    $$
    
    holds. Below we prove that $\phi=\dfrac{\sqrt{5}+1}{2}$ is such an $x$.[^sqrt5]
    
    Let $\phi'=\dfrac{-\sqrt{5}+1}{2}$ be the conjugate root of $\phi$. They are both roots of the equation $x^2-x-1=0$. Therefore, for any real number $x$, we have
    
    $$
    x^2-x-1 = (x-\phi)(x-\phi').
    $$
    
    Substituting the reduced fraction $\dfrac{p}{q}$, we obtain
    
    $$
    \dfrac{1}{q^2}\le\frac{|p^2-pq-q^2|}{q^2}=\left|\dfrac{p}{q}-\phi\right|\left|\dfrac{p}{q}-\phi'\right|\le\left|\dfrac{p}{q}-\phi\right|\left(\left|\dfrac{p}{q}-\phi\right|+|\phi-\phi'|\right)<\dfrac{1}{Cq^2}\left(\dfrac{1}{Cq^2}+sqrt{5}\right).
    $$
    
    For $C>\sqrt{5}$, we can directly solve to get $q<\sqrt{C(C-\sqrt{5})}$, so it is impossible to have infinitely many solutions satisfying the above inequality.

The proofs of these theorems show that convergents provide quite good Diophantine approximations. However, these may not be the best approximations. To discuss best approximations, we need to explain the measure of approximation quality. There are often two choices.

???+ warning "Cases where the best approximation conclusions may not hold"
    The next two sections will describe some results about best approximations. These results may not hold for some uninteresting cases. For example, both definitions of best approximations require strict inequality, but for a half-integer $x=n+\dfrac12$ where $n\in\mathbf Z$, its continued fraction can be $[n,1,1]$. At this time, its first two convergents $x_0=n$ and $x_1=n+1$ both have denominator $1$, and their distances to $x$ are the same. This shows that neither is a best approximation. For the statements of conclusions in this section, readers should assume such cases are excluded. If readers do not care about the last few convergents, or only care about approximations of irrational numbers, then they do not need to worry about these extra complications.

### Best Approximations of the First Kind: Intermediate Fractions

Best approximations of the first kind use

$$
\left|x-\dfrac{p}{q}\right|
$$

to measure the quality of approximation.

???+ abstract "Best approximation of the first kind"
    For a real number $x$ and a rational number $\dfrac{p}{q}$, if for any $\dfrac{p'}{q'}\neq \dfrac{p}{q}$ with $0<q'\le q$, we have
    
    $$
    \left|x-\dfrac{p}{q}\right|<\left|x-\dfrac{p'}{q'}\right|,
    $$
    
    then $\dfrac{p}{q}$ is called a **best approximation of the first kind** of $x$.

Best approximations of the first kind are not necessarily convergents, but a broader class of fractions.

???+ abstract "Intermediate fraction"
    Let $x$ have convergents $x_{k+1}=[a_0,a_1,\cdots,a_k,a_{k+1}]$, and let the integer $t$ satisfy $0\le t\le a_{k+1}$[^semi-range], then the fraction $x_{k,t}=[a_0,a_1,\cdots,a_{k},t]$ is called an **intermediate fraction**, **semiconvergent**, or **secondary convergent** of $x$.[^semiconvergent]
    
    Similar to the case of convergents, intermediate fractions greater than (less than) $x$ are called **upper (lower) semiconvergents**.

According to the recurrence formula, intermediate fractions can be written as

$$
x_{k,t} = \frac{tp_{k}+p_{k-1}}{tq_{k}+q_{k-1}}.
$$

It must be a reduced fraction and lies between the convergents $x_{k-1}$ and $x_{k+1}$. As $t$ increases, it gradually approaches $x_{k+1}$: (taking the case where $k$ is even as an example)

$$
x_{k-1} = x_{k,0} < x_{k,1} < x_{k,2} < \cdots < x_{k,a_{k+1}} = x_{k+1}.
$$

Because the numerators and denominators of convergents are both increasing, the numerators and denominators of intermediate fractions $x_{k,t}$ ($t\neq 0$) lie between those of $x_k$ and $x_{k+1}$. If these fractions are arranged by denominator size, intermediate fractions are some fractions between consecutive convergents.

All best approximations of the first kind are intermediate fractions, but not all intermediate fractions are best approximations of the first kind.

???+ note "Theorem"
    All best approximations of the first kind are intermediate fractions.

??? note "Proof"
    Because $a_0\le x\le a_0+1$, best approximations of the first kind must lie between $x_{1,0}=a_0$ and $x_{0,1}=a_0+1$. All intermediate fractions in increasing order can be arranged as
    
    $$
    x_{1,0}<x_{1,1}< \cdots < x_{1,a_2}=x_{3,0}<\ldots<x<\ldots<x_{2,0}=x_{0,a_1}<\cdots<x_{0,1}.
    $$
    
    Intermediate fractions of the same order appear consecutively, and there are no gaps between intermediate fractions of different orders. This means that any rational number $\dfrac{p}{q}$ lying between $x_{1,0}=a_0$ and $x_{0,1}=a_0+1$ must lie between two intermediate fractions $x_{k,t}$ and $x_{k,t+1}$ of the same order. Suppose it is not an intermediate fraction and is less than $x$, then
    
    $$
    x_{k,t}<\dfrac{p}{q}<x_{k,t+1}<x.
    $$
    
    On one hand, we have
    
    $$
    \left|x_{k,t}-\dfrac{p}{q}\right| \le \left|x_{k,t}-x_{k,t+1}\right| = \dfrac{1}{((t+1)q_k+q_{k-1})(tq_k+q_{k-1})}.
    $$
    
    On the other hand, we have
    
    $$
    \left|x_{k,t}-\dfrac{p}{q}\right| = \dfrac{|q(tp_k+p_{k-1})-p((t+1)q_k+q_{k-1})|}{q(tq_k+q_{k-1})}\ge\dfrac{1}{q(tq_k+q_{k-1})}.
    $$
    
    Therefore, we must have
    
    $$
    q>(t+1)q_k+q_{k-1}.
    $$
    
    That is, the denominator of the rational number $\dfrac{p}{q}$ is necessarily larger than that of $x_{k,t+1}$, but it is not a better approximation:
    
    $$
    \left|x-\dfrac{p}{q}\right|>\left|x-x_{k,t+1}\right|
    $$
    
    Therefore, it cannot be a best approximation of the first kind. This shows that if it is not an intermediate fraction, it is not a best approximation of the first kind; that is, all best approximations of the first kind are intermediate fractions.

Conversely, not all intermediate fractions can be asserted to be best approximations of the first kind. However, we can indeed give conditions for intermediate fractions to be best approximations of the first kind.

???+ note "Theorem"
    All convergents are best approximations of the first kind. In addition, let $0<t<a_{k+1}$, then the intermediate fraction $x_{k,t}$ is a best approximation of the first kind if and only if $t>\dfrac{a_{k+1}}{2}$ or $t=\dfrac{a_{k+1}}{2}$ and $r_{k+2}>\dfrac{q_k}{q_{k-1}}$.

??? note "Proof"
    Below we will prove that convergents are all best approximations of the second kind, so they are necessarily best approximations of the first kind. The key is on those intermediate fractions that are not convergents.
    
    As mentioned earlier, the denominator of the intermediate fraction $x_{k,t}$ lies between $x_k$ and $x_{k+1}$, and as $t$ increases, it increases, but $x_{k,t}$ gets closer to $x_{k+1}$, thus getting closer to $x$. Taking $x_{k,t}<x$ as an example, its relative position with neighboring intermediate fractions satisfies:
    
    $$
    x_{k-1} < x_{k,t} < x_{k+1} < x < x_{k}.
    $$
    
    Because the denominator of $x_k$ is smaller than that of $x_{k,t}$, the necessary condition for $x_{k,t}$ to be a best approximation of the first kind is that it is closer to $x$ than $x_k$. This is also sufficient because, as a convergent, there is no closer one with a smaller denominator, and those intermediate fractions with larger denominators than $x_k$ must be of the same order as $x_{k,t}$, but with smaller denominators, they must be farther from $x$. For the errors of convergents and intermediate fractions, after calculation we have
    
    $$
    \begin{aligned}
    \left|x_k-x\right| &= \dfrac{1}{q_k(r_{k+1}q_k+q_{k-1})},\\
    \left|x_{k,t}-x\right| &= \left|\dfrac{tp_{k}+p_{k-1}}{tq_{k}+q_{k-1}}-\dfrac{r_{k+1}p_{k}+p_{k-1}}{r_{k+1}q_{k}+q_{k-1}}\right| \\
    &=\dfrac{r_{k+1}-t}{(tq_{k}+q_{k-1})(r_{k+1}q_{k}+q_{k-1})}.
    \end{aligned}
    $$
    
    Here we used $r_{k+1}\ge a_{k+1}>t$. Therefore, $x_{k,t}$ is closer to $x$ than $x_k$, becoming a best approximation of the first kind, if and only if
    
    $$
    \dfrac{r_{k+1}-t}{tq_{k}+q_{k-1}}<\dfrac{1}{q_k} \iff r_{k+1}<2t+\dfrac{q_{k-1}}{q_k}.
    $$
    
    At this time, there are three possible situations:
    
    1.  If $t<\dfrac{a_{k+1}}{2}$, then $2t<a_{k+1}$. Since both sides are integers, $2t\le a_{k+1}-1$, so $2t+\dfrac{q_{k-1}}{q_k}\le 2t+1\le a_{k+1}\le r_{k+1}$. At this time, $x_{k,t}$ is not a best approximation of the first kind;
    2.  If $t>\dfrac{a_{k+1}}{2}$, then $2t>a_{k+1}$. Since both sides are integers, $2t\ge a_{k+1}+1>r_{k+1}$. At this time, $x_{k,t}$ is a best approximation of the first kind;
    3.  If $a_{k+1}$ is even, there is a third case, i.e., $t=\dfrac{a_{k+1}}{2}$. The above condition is equivalent to $\dfrac{1}{r_{k+1}}=r_{k+1}-a_{k+1}<\dfrac{q_{k-1}}{q_k}$, that is, $r_{k+2}>\dfrac{q_k}{q_{k-1}}$.

Therefore, if all best approximations of the first kind of a real number $x$ are arranged in increasing order by denominator, they will be divided into several segments according to their relationship with $x$. Each segment consists of some (possibly zero) consecutive intermediate fractions of the same order, and always ends with a convergent. Within each segment, it stays on one side of the real number $x$, and segments alternate on both sides of $x$.

??? example "Example: Best approximations of the first kind for $\pi$"
    $\pi=[3,7,15,1,292,\cdots]$, so the first 15 best approximations of the first kind with smallest denominators are:
    
    $$
    \begin{aligned}
    &x_0 = \dfrac{3}{1},\
    x_{0,4} = \dfrac{13}{4},\
    x_{0,5} = \dfrac{16}{5},\
    x_{0,6} = \dfrac{19}{6},\
    x_1 = \dfrac{22}{7},\\
    &x_{1,8} = \dfrac{179}{57},\
    x_{1,9} = \dfrac{201}{64},\
    x_{1,10} = \dfrac{223}{71},\
    x_{1,11} = \dfrac{245}{78},\
    x_{1,12} = \dfrac{267}{85},\\
    &x_{1,13} = \dfrac{289}{92},\
    x_{1,14} = \dfrac{311}{99},\
    x_2 = \dfrac{333}{106},\
    x_3 = \dfrac{355}{113},\
    x_{3,146} = \dfrac{52163}{16604}.
    \end{aligned}
    $$

### Best Approximations of the Second Kind

Best approximations of the second kind use $|qx-p|$ to measure the quality of approximation.

???+ abstract "Best approximation of the second kind"
    For a real number $x$ and a rational number $\dfrac{p}{q}$, if for any $\dfrac{p'}{q'}\neq \dfrac{p}{q}$ with $0<q'\le q$, we have
    
    $$
    \left|qx-p\right|<\left|q'x-p'\right|,
    $$
    
    then $\dfrac{p}{q}$ is called a **best approximation of the second kind** of $x$.

The condition for best approximations of the second kind is equivalent to

$$
\left|x-\dfrac{p}{q}\right|<\dfrac{q'}{q}\left|x-\dfrac{p'}{q'}\right|.
$$

Since $q'\le q$, the condition for best approximations of the second kind is more stringent than that for best approximations of the first kind.

Best approximations of the second kind can and only can be convergents.

???+ note "Theorem"
    All best approximations of the second kind must be convergents, and all convergents must be best approximations of the second kind.

??? note "Proof"
    To prove the first part, since best approximations of the second kind must also be best approximations of the first kind, we only need to prove that intermediate fractions that are not convergents cannot be best approximations of the second kind. To do this, let $x_{k,t}=\dfrac{p}{q}$ be an intermediate fraction but not a convergent, and suppose $x_{k,t}<x$, then
    
    $$
    x_{k-1} < x_{k,t} < x_{k+1} < x < x_{k}.
    $$
    
    Since the error between $x_{k,t}$ and $x$
    
    $$
    |x_{k,t}-x|\ge |x_{k,t}-x_{k+1}|=\left|\dfrac{p}{q}-\dfrac{p_{k+1}}{q_{k+1}}\right|=\dfrac{|pq_{k+1}-p_{k+1}q|}{qq_{k+1}}\ge\dfrac{1}{qq_{k+1}},
    $$
    
    and using the error estimation for convergents, we always have
    
    $$
    |qx_{k,t}-p| \ge \dfrac{1}{q_{k+1}} \ge |q_kx_k-p_k|,
    $$
    
    so the approximation quality of $x_{k,t}$ is no better than that of $x_k$ with a smaller denominator, so it cannot be a best approximation of the second kind.
    
    Conversely, to prove the second part, i.e., that every convergent $x_k=\dfrac{p_k}{q_k}$ is a best approximation of the second kind. This means that for all fractions $\dfrac{p}{q}$ with $q\le q_k$, we have $|q_kx-p_k|<|qx-p|$. Without considering half-integers, we can assume $k>0$. First, according to the error estimation for convergents approximating real numbers,
    
    $$
    |q_{k-1} x-p_{k-1}| \ge \frac{1}{q_{k-1}+q_{k}} \ge \dfrac{1}{q_{k+1}}\ge |q_kx-p_k|.
    $$
    
    All inequalities hold with equality if and only if $a_{k+1}=1$ and it is the last term of the continued fraction. Without considering such cases, then $x_{k-1}=\dfrac{p_{k-1}}{q_{k-1}}$ is strictly worse than $x_k=\dfrac{p_k}{q_k}$.
    
    Take any fraction $\dfrac{p}{q}\neq x_k$ with $0<q\le q_k$. Since we have the difference formula $p_{k}q_{k-1} − p_{k-1}q_{k} = (−1)^{k-1}$, by Cramer's rule, the system of linear equations
    
    $$
    \begin{cases}
    \lambda p_k+\mu p_{k-1} = p,\\
    \lambda q_k+\mu q_{k-1} = q
    \end{cases}
    $$
    
    must have a unique integer solution $(\lambda,\mu)$. If $\lambda\mu>0$, then $q>|\lambda|q_k\ge q_k$, a contradiction. Otherwise, $\lambda\mu\le 0$, i.e., $\lambda$ and $\mu$ have opposite signs. Then since $q_{k-1}x-p_{k-1}$ and $q_kx-p_k$ also have opposite signs, we have $\lambda(q_{k-1}x-p_{k-1})$ and $\mu(q_kx-p_k)$ having the same sign, so
    
    $$
    |qx-p|=|\lambda||q_kx-p_k|+|\mu||q_{k-1}x-p_{k-1}|>|q_{k}x-p_{k}|.
    $$
    
    The last inequality is strict because $x_{k-1}$ is strictly worse than $x_k$, and $\dfrac{p}{q}\neq x_k$. This shows that $x_k$ is a best approximation of the second kind.

This property shows that convergents are indeed quite good Diophantine approximations.

### Determining Convergents

Best approximations of the second kind provide necessary and sufficient conditions for determining whether a fraction is a convergent. This shows that we can judge whether a fraction is a convergent by checking the relative quality of its approximation. Legendre's criterion provides a method to judge convergents based on the absolute quality of approximation. The original statement of Legendre's criterion provides necessary and sufficient conditions, but its form is not practical. This section provides a simplified version of Legendre's criterion and shows that it does not miss too many convergents.

???+ note "Theorem (Legendre)"
    For a real number $x$ and a fraction $\dfrac{p}{q}$, if
    
    $$
    \left|x−\dfrac{p}{q}\right|<\dfrac{1}{2q^2}
    $$
    
    then $\dfrac{p}{q}$ must be a convergent of $x$.

??? note "Proof"
    Let $\epsilon\in\{-1,1\}$ and $\theta\in(0,1/2)$ be the constants such that
    
    $$
    x−\dfrac{p}{q} = \dfrac{\epsilon\theta}{q^2}
    $$
    
    holds. Expand the rational number $\dfrac{p}{q}$ into the continued fraction $[a_0,a_1,\cdots,a_n]$. Here, a rational number has two continued fraction representations, and their $n$ differs by exactly one, so we can choose the continued fraction representation such that $(-1)^n=\epsilon$, and denote the convergent of this continued fraction representation as $\dfrac{p_k}{q_k}$. Let $\omega$ satisfy
    
    $$
    x = \dfrac{\omega p_n+p_{n-1}}{\omega q_n+q_{n-1}}.
    $$
    
    Then we must have
    
    $$
    \dfrac{\epsilon\theta}{q^2} = x−\dfrac{p}{q} = x-\dfrac{p_n}{q_n} = \dfrac{p_{n-1}q_n-p_nq_{n-1}}{(\omega q_n+q_{n-1})q_n} = \dfrac{(-1)^n}{(\omega q_n+q_{n-1})q_n}.
    $$
    
    Hence, we have
    
    $$
    \theta = \dfrac{q_n}{\omega q_n+q_{n-1}}.
    $$
    
    This shows that
    
    $$
    \omega=\dfrac{1}{\theta}-\dfrac{q_{n-1}}{q_n}>1.
    $$
    
    Expand $\omega$ into the continued fraction $[b_0,b_1,\cdots]$, then
    
    $$
    x = \dfrac{\omega p_n+p_{n-1}}{\omega q_n+q_{n-1}} = [a_0,a_1,\cdots,a_n,\omega] = [a_0,a_1,\cdots,a_n,b_0,b_1,\cdots].
    $$
    
    This is a valid simple continued fraction, so $\dfrac{p}{q}$ is a convergent of $x$.
    
    This proof actually shows that the necessary and sufficient condition for $\dfrac{p}{q}$ to be a convergent is that $\omega>1$ in the above proof, which is the original form of Legendre's criterion.

This criterion shows that as long as the quality of approximation is good enough, it must be a convergent. The next theorem shows that there are enough such good convergents: at least half of all convergents satisfy this condition.

???+ note "Theorem (Valhen)"
    Among every two consecutive convergents of a real number $x$, at least one satisfies
    
    $$
    \left|x−\dfrac{p}{q}\right|<\dfrac{1}{2q^2}.
    $$

??? note "Proof"
    Suppose not. There exists a real number $x$ with two consecutive convergents $x_{k-1}$ and $x_k$ satisfying
    
    $$
    \left|x-\dfrac{p_k}{q_k}\right|\ge \dfrac{1}{2q_{k}^2},\ \left|x-\dfrac{p_{k+1}}{q_{k+1}}\right|\ge \dfrac{1}{2q_{k+1}^2}.
    $$
    
    Since $x$ lies between $x_{k-1}$ and $x_k$,
    
    $$
    \dfrac{1}{2q_{k}^2} + \dfrac{1}{2q_{k+1}^2} \le \left|x-\dfrac{p_k}{q_k}\right| + \left|x-\dfrac{p_{k+1}}{q_{k+1}}\right| = \left|\dfrac{p_k}{q_k}-\dfrac{p_{k+1}}{q_{k+1}}\right| = \dfrac{1}{q_kq_{k+1}}.
    $$
    
    This shows $q_k=q_{k+1}$. Therefore, we must have $k=0$ and $a_1=1$. At this time, the first two convergents are $x_0=a_0$ and $x_1=a_0+1$. So the only counterexample is a half-integer, which according to the earlier explanation, is not considered in this article.

## Geometric Interpretation

Continued fraction theory has an elegant geometric interpretation.

![](./images/continued-convergents-geometry.svg)

As shown in the figure, for a real number $\xi>0$, the line $y=\xi x$ divides the lattice points in the first quadrant (including points on the $x$ and $y$ axes but excluding the origin, the same applies below) into upper and lower parts. For rational numbers $\xi$, points on the line $y=\xi x$ count as both upper and lower points. Consider the convex hulls of these two sets of points. Then odd-indexed convergents are vertices of the convex hull of the upper part, and even-indexed convergents are vertices of the convex hull of the lower part. Lattice points on the line segment between two adjacent vertices of the convex hull are intermediate fractions. The figure shows the convergents and intermediate fractions (gray points) for $\xi=\dfrac{9}{7}$.

Most conclusions about continued fractions in the earlier sections have corresponding geometric interpretations:

??? note "Geometric interpretation"
    -   Each fraction $\nu=\dfrac{p}{q}$ corresponds to a lattice point $\vec\nu=(q,p)$ in the first quadrant, and the size of the fraction corresponds to the slope of the line connecting it with the origin.
    -   The direction vector of the line $y=\xi x$ is $\vec\xi=(1,\xi)$. Using the concept of [cross product](../linear-algebra/product.md#二维向量的情形) $(x_1,y_1)\times(x_2,y_2)=x_1y_2-x_2y_1$, we can determine whether a point is above or below the line by the sign of $\vec\xi\times\vec\nu=p-q\xi$. Therefore, points above the line correspond to fractions greater than or equal to $\xi$, and points below the line correspond to fractions less than or equal to $\xi$. The absolute value $|\vec\xi\times\vec\nu|$ is proportional to the distance from the point $\vec\nu$ to the line $y=xi x$
        
        $$
        \dfrac{|p-qx|}{\sqrt{1+\xi^2}},
        $$
        
        which corresponds to the quality of approximation of the fraction $\nu$ to the real number $\xi$.
    -   Let the point corresponding to the convergent $\xi_k=\dfrac{p_k}{q_k}$ be $\vec\xi_k=(p_k,q_k)$, then the recurrence formula can be written as
        
        $$
        \vec\xi_k = a_k\vec\xi_{k-1} + \vec\xi_{k-2}.
        $$
        
        The starting points of the recurrence are $\xi_{-2} = (1,0)$ and $\xi_{-1} = (0,1)$.
    -   For an integer $t$, if $0\le t\le a_k$, then the point
        
        $$
        \vec\xi_{k-1,t} = t\vec\xi_{k-1} + \vec\xi_{k-2}
        $$
        
        lies on the line segment connecting $\vec\xi_{k-2}$ and $\vec\xi_k$. They correspond to the intermediate fraction $\xi_{k-1,t}$.
    -   Using geometric methods, we can construct all convergents and intermediate fractions. Starting from the points $\vec\xi_{-2}=(1,0)$ and $\vec\xi_{-1}=(0,1)$, these two points are on opposite sides of the line $y=\xi x$, which means $\vec\xi\times\vec\xi_{-2}$ and $\vec\xi\times\vec\xi_{-1}$ have opposite signs. Add $\vec\xi_{-1}$ to $\vec\xi_{-2}$ by vector addition until we cannot continue without crossing the line $y=xi x$, and denote the result as $\vec\xi_0$. At this time, it is still on a different side from $\vec\xi_{-1}$. Then add $\vec\xi_0$ to $\vec\xi_{-1}$ until we cannot continue without crossing the line $y=xi x$, and denote the result as $\vec\xi_1$. At this time, it is still on a different side from $\vec\xi_0$. This process can continue indefinitely, unless at some finite step a $\vec\xi_n$ exactly lies on the line $y=xi x$. The latter means the vectors $\vec\xi$ and $\vec\xi_n$ are collinear, i.e., $\xi=\dfrac{p_n}{q_n}$ is rational. This process produces the shapes shown in the earlier diagrams. Boris Delaunay vividly called this process the nose-stretching algorithm[^nose-streching].
    -   If we need to quickly calculate how many times to add $\vec\xi_{k-1}$ to $\vec\xi_{k-2}$ at each step, we can use the cross product. Because $\vec\xi\times\vec\xi_{k-1}$ and $\vec\xi\times\vec\xi_{k-2}$ have opposite signs, if we denote $\vec\xi_{k-1,t}=t\vec\xi_{k-1}+\vec\xi_{k-2}$ as the result of adding $\vec\xi_{k-1}$ to $\vec\xi_{k-2}$ $t$ times, then $\vec\xi\times\vec\xi_{k-1,t}=t(\vec\xi\times\vec\xi_{k-1})+(\vec\xi\times\vec\xi_{k-2})$ not changing sign means we have not crossed the line. Before the sign changes, the absolute value of $\vec\xi\times\vec\xi_{k-1,t}$ gradually decreases. Denote
        
        $$
        r_{k} = \left|\dfrac{\vec\xi\times\vec\xi_{k-2}}{\vec\xi\times\vec\xi_{k-1}}\right| = -\dfrac{\vec\xi\times\vec\xi_{k-2}}{\vec\xi\times\vec\xi_{k-1}}.
        $$
        
        Then the maximum number of times it can decrease is
        
        $$
        a_{k} = \lfloor r_{k}\rfloor = \left\lfloor\left|\dfrac{q_{k-1}\xi-p_{k-1}}{q_{k-2}\xi-p_{k-2}}\right|\right\rfloor.
        $$
        
        This is the $k$-th term of the continued fraction expansion. Moreover, $r_k$ is the remainder of the continued fraction expansion, which satisfies:
        
        $$
        r_k = -\dfrac{q_{k-1}\xi-p_{k-1}}{q_{k-2}\xi-p_{k-2}} \iff \xi = \dfrac{p_{k-1}r_k + p_{k-2}}{q_{k-1}r_k+q_{k-2}}.
        $$
        
        This is the continued fraction relation $\xi = [a_0,a_1,\cdots,a_{k-1},r_k]$.
    -   Because the change in $\vec\xi\times\vec\xi_{k-1,t}$ caused by each addition of vectors has step size $|\vec\xi\times\vec\xi_{k-1}|$, the final remaining distance $|\vec\xi\times\vec\xi_k|$ must be strictly less than $|\vec\xi\times\vec\xi_{k-1}|$. This shows that the approximation quality of convergents (measured by $|qx-p|$) strictly improves as $k$ increases.
    -   Using the properties of cross products, we have
        
        $$
        \vec\xi_{k}\times\vec\xi_{k+1} = \vec\xi_{k}\times(a_{k+1}\vec\xi_k+\vec\xi_{k-1}) = \vec\xi_{k}\times\vec\xi_{k-1} = -\vec\xi_{k-1}\times\vec\xi_{k}.
        $$
        
        By induction, we have
        
        $$
        \vec\xi_{k}\times\vec\xi_{k+1} = (-1)^{k+2}\vec\xi_{k-2}\times\vec\xi_{k-1} = (-1)^{k}.
        $$
        
        This is the difference formula for convergents $p_{k+1}q_k-p_kq_{k+1}=(-1)^k$.
    -   The area between the two convex hulls can be divided into several (possibly infinitely many) triangles, where each triangle's vertices are $\vec\xi_{k-2}$, $\vec\xi_k$, and $\vec 0$. The area of such a triangle is
        
        $$
        \dfrac12|\vec\xi_{k-2}\times\vec\xi_k| = \dfrac12|\vec\xi_{k-2}\times(a_k\vec\xi_{k-1}+\vec\xi_{k-2})| = \dfrac{a_k}{2}|\vec\xi_{k-2}\times\vec\xi_{k-1}| = \dfrac{a_k}{2}.
        $$
        
        According to [Pick's theorem](../../geometry/pick.md), this means that if we let $I$ and $B$ be the numbers of interior and boundary lattice points of the triangle respectively, then
        
        $$
        I + \dfrac{B}{2} - 1 = \dfrac{a_k}{2}.
        $$
        
        It is known that there are already $\{\vec 0\}\cup\{\vec\xi_{k-1,t}:0\le t\le a_k\}$ totaling $a_k+2$ lattice points on the boundary. This shows that $I=0$ and $B=a_k+2$. Therefore, there are no more lattice points on the edges of the triangle, and no interior lattice points either. That is, $q_k$ and $p_k$ are reduced, and intermediate fractions are all lattice points on the edge connecting $\vec\xi_{k-2}$ and $\vec\xi_k$, and all lattice points in the first quadrant are inside the two convex hulls.

The two convex hulls obtained in this way are called the Klein polygon. Similar definitions can be made in higher-dimensional spaces, yielding the [Klein polyhedron](https://en.wikipedia.org/wiki/Klein_polyhedron), which can extend the concept of continued fractions to higher-dimensional spaces.

## Continued Fraction Trees

Main article: [Stern–Brocot Tree and Farey Sequences](./stern-brocot.md)

The Stern–Brocot tree is a [binary search tree](../../ds/bst.md) storing all fractions in $[0,\infty]$. Finite continued fractions actually encode the path from the root of the Stern–Brocot tree to where a fraction is located. That is, the continued fraction representation of a rational number $x$ $[a_0,a_1,\cdots,a_{n-1},1]$ means that starting from the tree root $\dfrac{1}{1}$, we need to move to the right child node $a_0$ times, then to the left child node $a_1$ times, alternating directions, until we have moved $a_{n-1}$ times in some direction. Note that only continued fraction representations ending with $1$ can be used here.

Understanding continued fraction representations as paths on the Stern–Brocot tree allows us to obtain algorithms for comparing continued fractions.

???+ example "Comparing continued fractions"
    Given continued fractions $\alpha=[\alpha_0,\alpha_1,\cdots,\alpha_n]$ and $\beta=[\beta_0,\beta_1,\cdots,\beta_m]$, compare their sizes.

??? note "Solution"
    First, convert both continued fractions to the form ending with $1$. Let the given continued fractions already be in this form, i.e., $\alpha_n=\beta_m=1$. Since even positions (with indices starting from $0$) are the number of moves to the right, and odd positions are the number of moves to the left, we have $\alpha<\beta$ if and only if, when compared in [lexicographic order](../../string/basic.md#字典序),
    
    $$
    (\alpha_0,-\alpha_1,\alpha_2,\cdots,(-1)^{n-1}\alpha_{n-1},0,\cdots)<(\beta_0,-\beta_1,\beta_2,\cdots,(-1)^{m-1}\beta_{m-1},0,\cdots).
    $$
    
    Compared to the continued fraction representation, we alternately add positive and negative signs, delete the trailing $1$, and pad positions with insufficient length with $0$.

    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/compare.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/compare.py:core"
        ```

???+ example "Best interior point"
    For $\dfrac{0}{1}\le\dfrac{p_0}{q_0}<\dfrac{p_1}{q_1}\le\dfrac{1}{0}$, find the rational number $\dfrac{p}{q}$ satisfying $\dfrac{p_0}{q_0}<\dfrac{p}{q}<\dfrac{p_1}{q_1}$ with minimal $(q,p)$.

??? note "Solution"
    Since the Stern–Brocot tree is both a binary search tree for fractions in $[0,\infty]$ and a [Cartesian tree](../../ds/cartesian-tree.md) for pairs $(q,p)$, the problem can almost be transformed into finding the LCA (least common ancestor) of two points on the Stern–Brocot tree. However, LCA can only handle closed intervals, and the LCA may be one of the endpoints themselves. To avoid additional discussions, we can first construct $\dfrac{p_0}{q_0}+\varepsilon$ and $\dfrac{p_1}{q_1}-\varepsilon$, then compute the LCA. After the path from the root to the node has been computed through continued fractions, the LCA is simply the longest common path.
    
    To construct $x\pm\varepsilon$, we only need to first move right (left) once at node $x$, then move left (right) $\infty$ times. Converting to the language of continued fractions, for a fraction $x=[a_0,a_1,\cdots,a_{n-1},1]$, we know that $x\pm\varepsilon$ must be $[a_0,a_1,\cdots,a_{n-1}+1,\infty]$ and $[a_0,a_1,\cdots,a_{n-1},1,\infty]$, so we only need to compare these two continued fractions, and define the larger (smaller) one as $x\pm\varepsilon$.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/inner-point.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/inner-point.py:core"
        ```

???+ example "[GCJ 2019, Round 2 - New Elements: Part 2](https://github.com/google/coding-competitions-archive/blob/main/codejam/2019/round_2/new_elements_part_2/statement.pdf)"
    Given $N$ pairs of positive integers $(C_i,J_i)$, find a pair of positive integers $(x,y)$ such that $\{C_ix+J_iy\}$ is strictly increasing. Among all pairs satisfying the requirements, output the lexicographically smallest pair.

??? note "Solution"
    Let $A_i=C_i-C_{i-1}$ and $B_i=J_i-J_{i-1}$. The problem transforms into finding $(x,y)$ such that all $A_ix+B_iy$ are integers. These pairs can be divided into four cases:
    
    1.  The case $A_i,B_i>0$ can be ignored because we already assume $(x,y)>0$;
    2.  The case $A_i,B_i\le 0$ directly outputs "IMPOSSIBLE";
    3.  The case $A_i>0,B_i\le 0$ is equivalent to the constraint $\dfrac{y}{x}<\dfrac{A_i}{-B_i}$;
    4.  The case $A_i\le 0,B_i>0$ is equivalent to the constraint $\dfrac{y}{x}>\dfrac{-A_i}{B_i}$.
    
    Therefore, take $\dfrac{p_0}{q_0}$ as the largest $\dfrac{-A_i}{B_i}$ in the fourth case, and take $\dfrac{p_1}{q_1}$ as the smallest $\dfrac{A_i}{-B_i}$ in the third case. The original problem becomes finding $(q,p)$ in lexicographically smallest order such that $\dfrac{p_0}{q_0}<\dfrac{p}{q}<\dfrac{p_1}{q_1}$ holds.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/gcj-2019.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/gcj-2019.py:core"
        ```

For more information about the properties and applications of the Stern–Brocot tree, refer to its main article page.

## Linear Fractional Transformations

Another important concept related to continued fractions is the so-called linear fractional transformation.

???+ abstract "Linear fractional transformation"
    A **linear fractional transformation** (or Möbius transformation) is a function $L:\mathbf R\rightarrow\mathbf R$ such that
    
    $$
    L(x) = \dfrac{ax+b}{cx+d},
    $$
    
    where $a,b,c,d\in\mathbf R$ and $ad-bc\neq 0$.

???+ info "About the condition $ad-bc\neq 0$"
    It is easy to verify that when $ad-bc=0$, the function may be undefined or a constant function.

Linear fractional transformations have the following properties:

???+ note "Properties of linear fractional transformations"
    Let $L_1,L_2,L_3$ be linear fractional transformations, and denote the matrix formed by the coefficients of $L_i$ as
    
    $$
    M_i=\begin{pmatrix}a_i & b_i \\ c_i & d_i\end{pmatrix}
    $$
    
    then they have the following properties:[^pgl2]
    
    1.  The composition $L_1\circ L_2$ and inverse $L_1^{-1}$ of linear fractional transformations are still linear fractional transformations, i.e., all linear fractional transformations form a [group](../algebra/basic.md#群);
    2.  Linear fractional transformations remain unchanged when their coefficients are multiplied by a non-zero constant, i.e., for any $\lambda\neq 0$, if $M_2=\lambda M_1$, then $L_2=L_1$;
    3.  The coefficient matrix of the composition of linear fractional transformations corresponds to the product of the coefficient matrices, i.e., if $M_1M_2=M_3$, then $L_1\circ L_2=L_3$;
    4.  The coefficient matrix of the inverse of a linear fractional transformation corresponds to the inverse of the coefficient matrix, i.e., if $M_1^{-1}=M_2$, then $L_1^{-1}=L_2$.

??? note "Proof"
    This only provides the forms of the composition and inverse of linear fractional transformations. After obtaining these forms, all properties are easy to verify.
    
    The composition of linear fractional transformations $L_1$ and $L_2$:
    
    $$
    \begin{aligned}
    L_1\circ L_2 &= \dfrac{a_1\dfrac{a_2x+b_2}{c_2x+d_2}+b_1}{c_1\dfrac{a_2x+b_2}{c_2x+d_2}+d_1} = \dfrac{(a_1a_2+b_1c_2)x+(a_1b_2+b_1d_2)}{(c_1a_2+d_1c_2)x+(c_1b_2+d_1d_2)}.
    \end{aligned}
    $$
    
    The inverse of the linear fractional transformation $L_1(x)$:
    
    $$
    y = L_1(x) = \dfrac{a_1x+b_1}{c_1x+d_1} \iff x = L_1^{-1}(y) = \dfrac{d_1y - b_1}{-c_1y + a_1}.
    $$

The finite continued fraction $[a_0,a_1,\cdots,a_n]$ can be viewed as the result of composing a series of linear fractional transformations. Let

$$
L_i(x) = \dfrac{a_ix+1}{x} = [a_i,x]. 
$$

Then the finite continued fraction

$$
[a_0,a_1,\cdots,a_n] = L_0\circ L_1\circ \cdots L_n(\infty).
$$

Among them, the value of the linear fractional transformation $L(x)=\dfrac{ax+b}{cx+d}$ at $x=\infty$ is $\dfrac{a}{c}$, which is the limit of the function as $x\rightarrow\pm\infty$.

For a general continued fraction, let the remainder of a real number $x$ be $r_{k+1}$, i.e., $x=[a_0,\cdots,a_k,r_{k+1}]$, then we have

$$
x = L_0\circ L_1\circ \cdots L_k(r_{k+1}) = \dfrac{p_kr_{k+1}+p_{k-1}}{q_kr_{k+1}+q_{k-1}}.
$$

This also gives the form of the linear fractional transformation $L_0\circ L_1\circ\cdots\circ L_k$.

We can also verify this expression directly. Initially:

$$
x=\dfrac{x+0}{0x+1}=\dfrac{p_{-1}x+p_{-2}}{q_{-1}x+q_{-2}}.
$$

Subsequently, if $L_0\circ L_1\circ\cdots\circ L_{k-1}$ has the form

$$
\dfrac{p_{k-1}x+p_{k-2}}{q_{k-1}x+q_{k-2}}
$$

then according to the composition formula for linear fractional transformations,

$$
L_0\circ L_1\circ\cdots\circ L_{k-1}\circ L_k = \dfrac{(p_{k-1}a_k+p_{k-2})x+p_{k-1}}{(q_{k-1}a_k+q_{k-2})x+q_{k-1}} = \dfrac{p_kx+p_{k-1}}{q_kx+q_{k-1}}.
$$

This gives the above form by induction. Linear fractional transformations also provide another perspective on the recurrence formula and initial conditions.

???+ example "[DMOPC '19 Contest 7 P4 - Bob and Continued Fractions](https://dmoj.ca/problem/dmopc19c7p4)"
    Given an array of positive integers $a_1,\cdots,a_n$ and $m$ queries, each query gives $l\le r$, and requires computing the value of $[a_l,\cdots,a_r]$.

??? note "Solution"
    Understanding continued fractions as the evaluation of a composition of linear fractional transformations at $x=\infty$, we only need to be able to query the composition of a range of linear fractional transformations multiple times. Since each linear fractional transformation can be inverted, we can preprocess prefix sums and use the difference method for queries, with complexity $O(n+m)$; if modifications are needed, we can also use data structures like segment trees.

    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/flt-presum.cpp"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/flt-presum.py"
        ```

### Arithmetic Operations on Continued Fractions

Using linear fractional transformations, we can perform arithmetic operations on continued fractions. This algorithm was first proposed by Gosper.

The cornerstone of the algorithm is computing the linear fractional transformation of continued fractions. This section uses finite continued fractions as examples, but since the algorithm only needs to read in a finite number of continued fraction terms for each output digit, it is also applicable to infinite continued fractions and can be computed to any precision. Combined with the continued fraction comparison algorithm from earlier, we can precisely compare real numbers of arbitrary precision.

???+ example "Linear fractional transformation of continued fractions"
    Given a linear fractional transformation $L(x)=\dfrac{ax+b}{cx+d}$ and a continued fraction $\alpha=[\alpha_0,\alpha_1,\cdots,\alpha_n]$, find the continued fraction representation $[\beta_0,\beta_1,\cdots,\beta_m]$ of $\beta=L(\alpha)$.

??? note "Solution"
    The basic idea is to determine the values of $\beta_i$ one by one. Let
    
    $$
    L_\gamma(x) = \gamma+\dfrac{1}{x} = \dfrac{\gamma x+1}{x}.
    $$
    
    Since
    
    $$
    L(\alpha) = L\circ L_{\alpha_0}\circ L_{\alpha_1}\circ \cdots \circ L_{\alpha_n}(\infty),
    $$
    
    we can compute the value of $L(\alpha)$ by gradually composing $L_{\alpha_k}$ with $L$. However, if we want to get the continued fraction representation of $L(\alpha)$, we do not need to completely compute the value of $L(\alpha)$ first and then find its continued fraction representation. We can determine the values of $\beta_0,\beta_1,\cdots$ during the process of composing $L_{\alpha_i}$.
    
    For example, suppose currently we have computed
    
    $$
    L\circ L_{\alpha_0}\circ L_{\alpha_1}\circ \cdots \circ L_{\alpha_k}(x) = \dfrac{a_kx+b_k}{c_kx+d_k}
    $$
    
    and $c_k,d_k$ have the same sign. Then $L\circ L_{\alpha_0}\circ L_{\alpha_1}\circ \cdots \circ L_{\alpha_k}(x)$ is monotonic on $[0,\infty]$, and its value must lie between $\dfrac{a_k}{c_k}$ and $\dfrac{b_k}{d_k}$. So if
    
    $$
    \left\lfloor\dfrac{a_k}{c_k}\right\rfloor = \left\lfloor\dfrac{b_k}{d_k}\right\rfloor,
    $$
    
    we can determine that it is the integer part $\beta_0$ of $L\circ L_{\alpha_0}\circ L_{\alpha_1}\circ \cdots \circ L_{\alpha_k}(x)$. At this time, composing $L_{\beta_0}^{-1}$ on the left gives
    
    $$
    L_{\beta_0}^{-1}\circ L\circ L_{\alpha_0}\circ L_{\alpha_1}\circ \cdots \circ L_{\alpha_k}.
    $$
    
    Then we can continue adding $L_{\alpha_{k+1}},L_{\alpha_{k+2}},\cdots$ to determine the new integer part, i.e., $\beta_1$. Continue this process until all $\beta_j$ are determined.
    
    The algorithm requires $c$ and $d$ to have the same sign to ensure that the discontinuity point of the function is not in $[0,\infty]$. This is always possible because the definition of simple continued fractions requires that all coefficients (except $\alpha_0$) are positive integers. From this, it can be proved that $c$ and $d$ will eventually have the same sign in finite steps and will continue to have the same sign thereafter.
    
    In actual implementation, we only need to maintain the coefficient matrix $\begin{pmatrix}a&b\\c&d\end{pmatrix}$ of the current linear fractional transformation and check whether $c$ and $d$ have the same sign and whether $\dfrac{a}{c}$ and $\dfrac{b}{d}$ have the same integer part. When composing $L_{\alpha_i}$ on the right, we get $\begin{pmatrix}a\alpha_i+b&a\\ c\alpha_i+d&c\end{pmatrix}$. If both integer parts are the same as $\beta_j$, then we add $\beta_j$ to the continued fraction, and compose $L_{\beta_j}^{-1}$ on the left, which is equivalent to computing $\begin{pmatrix}c&d\\ a\bmod c & b \bmod d \end{pmatrix}$.

The linear fractional transformation of continued fractions can already be used to compute the arithmetic operations of fractions and continued fractions:

$$
\dfrac{p}{q}\pm x = \dfrac{\pm qx+p}{0x+q},\ \dfrac{p}{q}x = \dfrac{px+0}{0x+q},\ \frac{p}{q}/x = \dfrac{0x+p}{qx+0}.
$$

For general arithmetic operations between continued fractions, we need to use bilinear fractional transformations:

$$
x+y = \dfrac{0xy+x+y+0}{0xy+0x+0y+1},\ xy = \dfrac{1xy+0x+0y+0}{0xy+0x+0y+1},\ \dfrac{x}{y} = \dfrac{0xy+x+0y+0}{0xy+0x+y+0}.
$$

???+ example "Bilinear fractional transformation of continued fractions"
    Given a bilinear fractional transformation $L(x,y)=\dfrac{axy+bx+cy+d}{exy+fx+gy+h}$ and continued fractions $\alpha=[\alpha_0,\alpha_1,\cdots,\alpha_n]$ and $\beta=[\beta_0,\beta_1,\cdots,\beta_m]$, find the continued fraction representation $[\gamma_0,\gamma_1,\cdots,\gamma_\ell]$ of $\gamma=L(\alpha,\beta)$.

??? note "Solution"
    Similar to the case of single-variable linear fractional transformations, to determine the integer part, we only need to ensure that the integer part of the current bilinear fractional transformation remains unchanged in $(x,y)\in[0,\infty]\times[0,\infty]$, i.e., $e,f,g,h$ all have the same sign, and
    
    $$
    \left\lfloor\dfrac{a}{e}\right\rfloor = \left\lfloor\dfrac{b}{f}\right\rfloor = \left\lfloor\dfrac{c}{g}\right\rfloor = \left\lfloor\dfrac{d}{h}\right\rfloor.
    $$
    
    Right composition is replaced by computing $L(x,y)\mapsto L(L_{\alpha_i}(x),y)$ and $L(x,y)\mapsto L(x,L_{\beta_j}(y))$, which are also represented as linear transformations of coefficients. Left composition is completely consistent with the single-variable case, we only need to compute the modulo.
    
    Compared to the single-variable case, the two-variable case needs to decide whether to compose $L_{\alpha_i}$ or $L_{\beta_j}$ first. Since the order of composition does not affect the final result, we can freely choose the order of composition, such as alternately composing $L_{\alpha_i}$ and $L_{\beta_j}$. Or using the empirical rule, prioritize the dimension with the larger ratio difference: if $\left|\dfrac{b}{f}-\dfrac{d}{h}\right|>\left|\dfrac{c}{g}-\dfrac{d}{h}\right|$, then first compose $L_{\alpha_i}$; otherwise, first compose $L_{\beta_j}$.

## Periodic Continued Fractions

Similar to the concept of repeating decimals, if the coefficients of a continued fraction form a cycle, it is called a periodic continued fraction.

???+ abstract "Periodic continued fraction"
    Let the continued fraction $x=[a_0,a_1,a_2,\cdots]$, and there exist natural numbers $K$ and positive integer $L$ such that for any $k\ge K$, we have $a_k=a_{k+L}$, then $x$ is called a **periodic continued fraction**. The smallest $L$ satisfying this condition is called its minimal positive period, and the sequence $a_k,\cdots,a_{k+L-1}$ that repeats in the continued fraction is called its repeating block. Using the repeating block, the periodic continued fraction can be written as $x=[a_0,\cdots,a_{k-1},\overline{a_k,\cdots,a_{k+L-1}}]$. If $K$ can be taken as $0$, i.e., $x=[\overline{a_0,\cdots,a_{L-1}}]$, then it is called a **purely periodic continued fraction**, otherwise it is called a **mixed periodic continued fraction**.

### Quadratic Irrationals

The concept closely related to periodic continued fractions is the [(real) quadratic irrational](./quadratic.md), i.e., the irrational solutions of quadratic equations with integer coefficients. All quadratic irrationals can be expressed in the form

$$
a+b\sqrt D
$$

where $a,b$ are rational numbers and $D$ is a positive integer without square factors. The quadratic irrationals mentioned in this article are all assumed to be real numbers. Moreover, the conjugate of $a+b\sqrt D$ is $a-b\sqrt{D}$.

Euler's result shows that all periodic continued fractions are quadratic irrationals.

???+ note "Theorem (Euler)"
    Periodic continued fractions all represent quadratic irrationals.

??? note "Proof"
    For a general periodic continued fraction $x=[a_0,\cdots,a_{k-1},\overline{a_k,\cdots,a_{k+L-1}}]$, we can set $y=[\overline{a_k,\cdots,a_{k+L-1}}]$, then
    
    $$
    \begin{aligned}
    x&=[a_0,\cdots,a_{k-1},y] = L_0(y),\\
    y&=[a_k,\cdots,a_{k+L-1},y] = L_1(y),
    \end{aligned}
    $$
    
    where both $L_0(\cdot)$ and $L_1(\cdot)$ are linear fractional transformations. Thus, the equation satisfied by $x$ is
    
    $$
    x = L_0\circ L_1\circ L_0^{-1}(x). 
    $$
    
    Let the linear fractional transformation $L_0\circ L_1\circ L_0^{-1}(x) = \dfrac{ax+b}{cx+d}$, then we get the equation satisfied by $x$
    
    $$
    cx^2+(d-a)x-b=0.
    $$
    
    Therefore, periodic continued fractions are all solutions of quadratic equations with integer coefficients. Moreover, since infinite continued fractions are all irrational numbers, periodic continued fractions all represent quadratic irrationals.

Lagrange's result shows the converse also holds, so quadratic irrationals and periodic continued fractions are equivalent.

???+ note "Theorem (Lagrange)"
    Quadratic irrationals can be expressed as periodic continued fractions.

??? note "Proof"
    The idea is to prove that remainders repeat. Let a quadratic irrational $x$ be written in the form
    
    $$
    x = \dfrac{P_0+\sqrt{D}}{Q_0}
    $$
    
    where $P_0,Q_0,D$ are all integers and $Q_0\mid D-P_0^2$. This is always possible, for example, a quadratic irrational $x$ can always be written as
    
    $$
    a+b\sqrt{D'} = \dfrac{p_a}{q_a}+\dfrac{p_b}{q_b}\sqrt{D'} = \dfrac{p_aq_b+p_bq_a\sqrt{D'}}{q_aq_b} = \dfrac{p_ap_bq_aq_b+\sqrt{(q_aq_b)^2D'}}{(q_aq_b)^2}
    $$
    
    then let $P=p_ap_bq_aq_b$, $Q=(q_aq_b)^2$ and $D=QD'$.
    
    The benefit of writing it in this form is that we can prove all its remainders have a similar form:
    
    $$
    r_k=\dfrac{P_k+\sqrt D}{Q_k},
    $$
    
    where $P_k,Q_k$ are integers and $Q_k\mid D-P_k^2$. Here, the condition $Q_k\mid D-P_k^2$ ensures that the coefficient in front of $\sqrt{D}$ in the numerator of all remainders is $1$.
    
    To get the form of the remainder, we can use mathematical induction. When $k=0$, it is obvious. Assuming we have obtained the form of $r_k$, and let $a_k=\lfloor r_k\rfloor$, then
    
    $$
    r_k = a_k+\dfrac{1}{r_{k+1}}.
    $$
    
    Assume $r_{k+1}$ also has a similar form, and substitute together with $r_k$ into the above equation:
    
    $$
    \dfrac{P_k+\sqrt D}{Q_k} = a_k + \dfrac{Q_{k+1}}{P_{k+1}+\sqrt{D}} = a_k + \dfrac{Q_{k+1}P_{k+1}-Q_{k+1}\sqrt{D}}{P_{k+1}^2-D}.
    $$
    
    Since expressing quadratic irrationals as $a+b\sqrt{D}$ is unique, comparing coefficients on both sides, we get
    
    $$
    \dfrac{P_k}{Q_k} = a_k+\dfrac{Q_{k+1}P_{k+1}}{P_{k+1}^2-D},\ \dfrac{1}{Q_k}=-\dfrac{Q_{k+1}}{P_{k+1}^2-D}.
    $$
    
    Substituting the second equation into the first equation, we can solve for $P_{k+1}$:
    
    $$
    \dfrac{P_k}{Q_k} = a_k-\dfrac{P_{k+1}}{Q_k} \iff P_{k+1} = a_kQ_k-P_k.
    $$
    
    Substituting into the second equation, we can solve for $Q_{k+1}$:
    
    $$
    Q_{k+1} = \dfrac{D-P_{k+1}^2}{Q_k} = \dfrac{D-(a_kQ_k-P_k)^2}{Q_k} = -a_k^2Q_k+2a_kP_k+\dfrac{D-P_k^2}{Q_k}.
    $$
    
    According to the induction hypothesis, $Q_k\mid D-P_k^2$, so indeed both $P_{k+1}$ and $Q_{k+1}$ are integers, i.e., $r_{k+1}$ also has the required form.
    
    Finally, we prove that remainders can only take finitely many values, so they must repeat. We have obtained the remainder earlier
    
    $$
    \dfrac{P_k+\sqrt{D}}{Q_k} = r_k = -\dfrac{q_{k-2}x-p_{k-2}}{q_{k-1}x-p_{k-1}}
    $$
    
    and for irrational numbers, we always have $r_k>1$. At the same time, its conjugate
    
    $$
    \dfrac{P_k-\sqrt{D}}{Q_k} = r_k^* = -\dfrac{q_{k-2}x^*-p_{k-2}}{q_{k-1}x^*-p_{k-1}} = -\dfrac{q_{k-2}}{q_{k-1}}\dfrac{x^*-\dfrac{p_{k-2}}{q_{k-2}}}{x^*-\dfrac{p_{k-1}}{q_{k-1}}}
    $$
    
    must be less than $0$ for sufficiently large $k$, because
    
    $$
    \dfrac{q_{k-2}}{q_{k-1}}>0,\ \lim_{k\rightarrow\infty}\dfrac{x^*-\dfrac{p_{k-2}}{q_{k-2}}}{x^*-\dfrac{p_{k-1}}{q_{k-1}}}=\dfrac{x^*-x}{x^*-x}=1.
    $$
    
    This shows that
    
    $$
    \dfrac{2\sqrt{D}}{Q_k} = r_k-r_k^*>1 \iff 0<Q_k\le 2\sqrt{D}.
    $$
    
    Therefore, $Q_k$ can only take finitely many values. Furthermore,
    
    $$
    D-P_{k}^2=Q_kQ_{k-1}>0 \iff |P_k|<\sqrt{D},
    $$
    
    so $P_k$ can also only take finitely many values. Hence, the remainder $r_k$ has only finitely many possible values and must repeat within infinite terms.

The proof of this theorem also provides a recurrence formula for computing the remainders of quadratic irrationals:

???+ note "Recurrence formula for quadratic irrationals"
    A quadratic irrational can always be expressed in the form
    
    $$
    x=\dfrac{P_0+\sqrt{D}}{Q_0}
    $$
    
    with $Q_0\mid D-P^2_0$. Its remainder
    
    $$
    r_{k}=\dfrac{P_k+\sqrt{D}}{Q_k}
    $$
    
    where $P_k,Q_k$ are all integers, and satisfy the recurrence relations
    
    $$
    \begin{aligned}
    P_{k+1} &= a_kQ_k-P_k,\\
    Q_{k+1} &= \dfrac{D-P_{k+1}^2}{Q_k}.
    \end{aligned}
    $$

This recurrence formula can be directly used for the continued fraction computation of quadratic irrationals, and according to the proof of the theorem, $|P_k|<\sqrt{D}$ and $Q_k\le 2\sqrt{D}$. The complexity of this algorithm depends on the length of the repeating block, and the latter can be proved to be $O(\sqrt{D}\log D)$[^period-surd].

???+ example "Quadratic irrationals"
    Given a quadratic irrational $\alpha=\dfrac{x+y\sqrt{n}}{z}$, find its continued fraction representation. Here, $x,y,z,n\in\mathbf Z$ and $n>0$ is not a perfect square.

??? note "Solution"
    First express the quadratic irrational in the above form, then use the recurrence formula to compute it. The terms of the continued fraction are given by $a_k=\lfloor r_k\rfloor$. To find the repeating block, we need to store the indices where $(P_k,Q_k)$ first appear.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/quadratic-irrational.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/quadratic-irrational.py:core"
        ```

???+ example "[Tavrida NU Akai Contest - Continued Fraction](https://timus.online/problem.aspx?space=1&num=1814)"
    Given $x$ and $k$, where $x$ is not a perfect square, $0\le k\le 10^9$. Find the $k$-th convergent $x_k$ of $\sqrt{x}$.

??? note "Solution"
    First use the above algorithm to find the period of $\sqrt{x}$, express the repeating block as a linear fractional transformation, and then use [fast exponentiation](../binary-exponentiation.md) to obtain the value of $x_k$. Of course, for parts that have not entered the repeating block or are less than one repeating block, they need to be handled separately.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/surd-convergent.cpp"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/surd-convergent.py"
        ```

### Purely Periodic Continued Fractions

Quadratic irrationals have periodic continued fraction representations as a sufficient and necessary condition. The discussion in this section gives the sufficient and necessary conditions for real numbers to have purely periodic continued fraction representations.

First, since purely periodic continued fractions have a form similar to finite continued fractions, we can perform a "reverse order" operation. Similar to the reverse order theorem, there is a definite relationship between the continued fraction representation obtained in this way and the original continued fraction representation.

???+ note "Theorem (Galois)"
    For a purely periodic continued fraction
    
    $$
    x = \left[\overline{a_0,a_1,\cdots,a_{\ell}}\right],
    $$
    
    denote
    
    $$
    x' = \left[\overline{a_{\ell},\cdots,a_1,a_0}\right].
    $$
    
    Then $x$ and $x'$ are "reciprocal negative conjugates" of each other, i.e., the negative of the reciprocal of the conjugate of $x$ is $x'$.

??? note "Proof"
    Since we do not require $\ell+1$ to be the minimal positive period, we can assume $\ell>0$. Using the reverse order theorem, we know that
    
    $$
    \begin{aligned}
    \dfrac{p_\ell}{p_{\ell-1}} &= [a_\ell,\cdots,a_1,a_0] = \dfrac{p'_\ell}{q'_\ell},\\
    \dfrac{q_\ell}{q_{\ell-1}} &= [a_\ell,\cdots,a_1] = \dfrac{p'_{\ell-1}}{q'_{\ell-1}}.
    \end{aligned}
    $$
    
    Since both sides are reduced fractions,
    
    $$
    p'_\ell = p_\ell,\ q'_\ell = p_{\ell-1},\ p'_{\ell-1}=q_\ell,\ q'_{\ell-1} = q_{\ell-1}.
    $$
    
    For a purely periodic continued fraction $x$, its $(\ell+1)$-th remainder is $x$ itself, therefore,
    
    $$
    x = \dfrac{xp_\ell+p_{\ell-1}}{xq_\ell+q_{\ell-1}}.
    $$
    
    So it satisfies the quadratic equation
    
    $$
    q_\ell x^2+(q_{\ell-1}-p_\ell)x-p_{\ell-1} = 0.
    $$
    
    Similarly, $x'$ satisfies the quadratic equation
    
    $$
    q'_\ell(x')^2+(q'_{\ell-1}-p'_\ell)x'-p'_{\ell-1} = 0.
    $$
    
    Using the relationship between coefficients, this equation can be written as
    
    $$
    p_{\ell-1}(x')^2+(q_{\ell-1}-p_\ell)x'-q_\ell = 0.
    $$
    
    Let $y=-\dfrac{1}{x'}$, then $x$ and $y$ satisfy the same equation. However, $x>0>y$, so they are not the same root but satisfy the conjugate relationship, which proves the proposition.

Galois used this observation to further give the sufficient and necessary conditions for quadratic irrationals to have purely periodic continued fraction representations.

???+ note "Theorem (Galois)"
    A quadratic irrational $x$ can be expressed as a purely periodic continued fraction if and only if $x>1$ and its conjugate $-1<x^*<0$.

??? note "Proof"
    If $x$ is a purely periodic continued fraction, then using the notation from earlier, we have $a_0=a_{\ell+1}\ge 1$, so $x>1$. And since its reciprocal negative conjugate is also a periodic continued fraction, its conjugate $x^*$ satisfies $-\dfrac{1}{x^*}>1$, that is, $-1<x^*<0$. This proves that purely periodic continued fractions all satisfy this condition.
    
    Conversely, let a quadratic irrational $x>1$ and $-1<x^*<0$. For the remainder $r_k$ of $x$, we have the recurrence relation
    
    $$
    r_k = a_k+\dfrac{1}{r_{k+1}}.
    $$
    
    Both sides are quadratic irrationals. Taking conjugates, we know that
    
    $$
    r_{k}^* = a_k+\dfrac{1}{r_{k+1}^*}.
    $$
    
    Using this recurrence relation, we can prove that $-1<r_{k}^*<0$ holds for all $k\ge 0$.
    
    First, for $k=0$, we have $-1<r_0^*=x_0^*<0$, which is obvious. For $k\ge 0$, from the definition of simple continued fractions and $x>1$, we know $a_k\ge 1$. Therefore, assuming $-1<r_k^*<0$, we have
    
    $$
    -1<-\dfrac{1}{a_k}< r_{k+1}^* = \dfrac{1}{r_k^*-a_k} < -\dfrac{1}{1+a_k} < 0.
    $$
    
    This inductively proves that $-1<r_{k}^*<0$ holds for all $k\ge 0$. Therefore, we have
    
    $$
    a_k = -\dfrac{1}{r_{k+1}^*}+r_k^* = \left\lfloor-\dfrac{1}{r_{k+1}^*}\right\rfloor.
    $$
    
    Since quadratic irrationals must be periodic continued fractions, there exists a positive integer $L$ and at least some sufficiently large $k$ such that $r_{k}=r_{k+L}$. But at this time, we must also have
    
    $$
    a_{k-1} = \left\lfloor-\dfrac{1}{r_{k}^*}\right\rfloor = \left\lfloor-\dfrac{1}{r_{k+L}^*}\right\rfloor = a_{k+L-1}.
    $$
    
    Therefore,
    
    $$
    r_{k-1} = a_{k-1}+\dfrac{1}{r_k} = a_{k+L-1}+\dfrac{1}{r_{k+L}} = r_{k+L-1}.
    $$
    
    This means that the smallest $k$ that makes $r_{k}=r_{k+L}$ hold must be $0$. That is, $x$ can be expressed as a purely periodic continued fraction.

Galois's theorem reveals the pattern of continued fraction representations of pure quadratic surds—that is, quadratic irrationals of the form $\sqrt{r}$.

???+ note "Corollary"
    For a rational number $r>1$, if $\sqrt{r}$ is irrational, then
    
    $$
    \sqrt{r} = [\lfloor\sqrt{r}\rfloor,\overline{a_1,\cdots,a_{\ell},2\lfloor\sqrt{r}\rfloor}]
    $$
    
    and for any $1\le k\le\ell$, we have $a_k = a_{\ell+1-k}$.

??? note "Proof"
    For the quadratic irrational $\sqrt{r}$, since $\lfloor\sqrt{r}\rfloor+\sqrt{r}>1$ and $-1<\lfloor\sqrt{r}\rfloor-\sqrt{r}<0$, so $\lfloor\sqrt{r}\rfloor+\sqrt{r}$ is a purely periodic continued fraction:
    
    $$
    \lfloor\sqrt{r}\rfloor+\sqrt{r} = [\overline{2\lfloor\sqrt{r}\rfloor,a_1,\cdots,a_\ell}].
    $$
    
    According to the above theorem, its reciprocal negative conjugate has the form
    
    $$
    \dfrac{1}{\sqrt{r}-\lfloor\sqrt{r}\rfloor} = [\overline{a_\ell,\cdots,a_1,2\lfloor\sqrt{r}\rfloor}].
    $$
    
    Using the basic properties of continued fractions, we know that
    
    $$
    \sqrt{r}=\lfloor\sqrt{r}\rfloor+\dfrac{1}{\dfrac{1}{\sqrt{r}-\lfloor\sqrt{r}\rfloor}}=[\lfloor\sqrt{r}\rfloor,\overline{a_\ell,\cdots,a_1,2\lfloor\sqrt{r}\rfloor}].
    $$
    
    However, from the continued fraction representation of $\lfloor\sqrt{r}\rfloor+\sqrt{r}$, we also have
    
    $$
    \sqrt{r} = -\lfloor\sqrt{r}\rfloor+\left(\lfloor\sqrt{r}\rfloor+sqrt{r}\right) = [\lfloor\sqrt{r}\rfloor,\overline{a_1,\cdots,a_\ell,2\lfloor\sqrt{r}\rfloor}].
    $$
    
    Since the continued fraction representation of irrational numbers is unique, comparing the middle coefficients, we know that $a_k=a_{\ell+1-k}$ holds for all $1\le k\le\ell$.

??? example "Example: Continued fraction expansion of $\sqrt{74}$"
    The continued fraction of $\sqrt{74}$ can be computed as follows: (this is only for illustration; programming should use the recursive algorithm mentioned earlier)
    
    $$
    \begin{aligned}
    \sqrt{74}&=8+(-8)+\sqrt{74}=\left[8,\frac{8+\sqrt{74}}{10}\right]\\
    &=\left[8,1+\frac{-2+\sqrt{74}}{10}\right]=\left[8,1,\frac{2+\sqrt{74}}{7}\right]\\
    &=\left[8,1,1+\frac{-5+\sqrt{74}}{7}\right]=\left[8,1,1,\frac{5+\sqrt{74}}{7}\right]\\
    &=\left[8,1,1,1+\frac{-2+\sqrt{74}}{7}\right]=\left[8,1,1,1,\frac{2+\sqrt{74}}{10}\right]\\
    &=\left[8,1,1,1,1+\frac{-8+\sqrt{74}}{10}\right]=\left[8,1,1,1,1,8+\sqrt{74}\right]\\
    &=\left[8,1,1,1,1,16+(-8)+\sqrt{74}\right]=\left[8,\overline{1,1,1,1,16}\right]
    \end{aligned}
    $$
    
    The remainders are respectively:
    
    $$
    \begin{alignedat}{3}
    r_1&=\frac{8+\sqrt{74}}{10}&&=\left[\overline{1,1,1,1,16}\right]\\
    r_2&=\frac{2+\sqrt{74}}{7}&&=\left[\overline{1,1,1,16,1}\right]\\
    r_3&=\frac{5+\sqrt{74}}{7}&&=\left[\overline{1,1,16,1,1}\right]\\
    r_4&=\frac{2+\sqrt{74}}{10}&&=\left[\overline{1,16,1,1,1}\right]\\
    r_5&=8+\sqrt{74}&&=\left[\overline{16,1,1,1,1}\right]
    \end{alignedat}
    $$
    
    According to Galois's conclusion, the repeating parts of remainders $r_k$ and $r_{L+1-k}$ are exactly opposite, so they are reciprocal negative conjugates. If the length $L$ of the repeating block of $\sqrt{D}$ is odd, then the middle term is its own reciprocal negative conjugate; if the length $L$ of the repeating block is even, such a term does not exist. The discussion in the Pell equation section will show that the parity of the repeating block length determines whether the equation $x^2-Dy^2=-1$ has solutions.

The continued fraction expansion of quadratic irrationals $\sqrt{D}$ is mainly used in solving [Pell equations](./pell-equation.md).

## Example Problems

After mastering the basic concepts, we need to study some specific example problems to understand how to apply continued fraction methods in algorithm competitions.

???+ example "Lower convex hull"
    Given $r=[a_0,a_1,\cdots,a_n]$, find the convex hull of the set of lattice points $(x,y)$ satisfying $0\le x\le N$ and $0\le y\le rx$.

??? note "Solution"
    For an unbounded set $x\ge 0$, the upper convex hull is the line $y=rx$ itself. However, as shown in the figure, if we also require $x\le N$, then the upper convex hull will eventually deviate from the line.
    
    ![](./images/lattice-hull.svg)
    
    Starting from $(0,0)$, we can find all lattice points of the upper convex hull from left to right. Assume we have found the last lattice point of the upper convex hull as $(x,y)$. Now we need to find the next lattice point $(x',y')$. The vertex $(x',y')$ is to the right and above $(x,y)$. Let $(\Delta x,\Delta y)=(x'-x,y'-y)$ be the difference. Then we must have
    
    $$
    0<\Delta x\le N-x,\ 0\le \Delta y\le r\Delta x.
    $$
    
    The second inequality holds because the condition $\Delta y>r\Delta x$ would contradict that $(x,y)$ is already on the upper convex hull. Observing the conditions that $(\Delta x,\Delta y)$ need to satisfy, for different points $(x,y)$, only the upper bound of $\Delta x$ changes. So, as long as we can solve this subproblem, we can recursively find all lattice points of the original problem.
    
    Then consider the solution of the subproblem. Compared to the original problem, the subproblem modifies the upper bound of $x$ to $N'$, and finds the first lattice point adjacent to the origin in the upper convex hull. Let the solution of the subproblem be $(q,p)$. Then $p$ and $q$ must be coprime (otherwise not the first lattice point), and the slope of the line connecting it to the origin $\dfrac{p}{q}$ is the largest among all lattice points below the line $y=rx$ with abscissa not exceeding $N'$ (otherwise not on the convex hull). Combined with the [geometric interpretation](#几何解释) from earlier, such a point $(x,y)$ necessarily corresponds to a lower semiconvergent of $r$. Because lower semiconvergents with larger denominators are closer to $r$, the solution $(q,p)$ of the subproblem corresponds to the lower semiconvergent with the largest denominator among all lower semiconvergents with denominator not exceeding $N'$.
    
    Of course, in actual solution, there is no need to find such lower semiconvergents for each subproblem from scratch. We should first find all convergents, which essentially provides a way to traverse all lower semiconvergents. Then traverse lower semiconvergents from largest to smallest denominator, and try to add each to the previous lattice point $(x,y)$ until we cannot add it, then try the next lower semiconvergent.
    
    There are some obvious optimizations here. First, for a lower semiconvergent $(q,p)$, there must exist an odd $k$ and $0\le t<a_k$ such that $(q,p)=(q_{k-1},p_{k-1})+t(q_k,p_k)$. We only need to find the largest $t$ such that $q_{k-1}+tq_k+x\le N$ holds, that is, $t=\left\lfloor\dfrac{N-q_{k-1}-x}{q_k}\right\rfloor$. We do not need to worry about $t$ going out of bounds, because the larger lower convergent $(q_{k+2},p_{k+2})$ has already been added. And when determining the number of times to add, we can directly compute $\left\lfloor\dfrac{N-x}{q}\right\rfloor$ instead of trying one by one.
    
    The complexity of the optimized algorithm is $O(n)$. Although there may be many lattice points corresponding to lower semiconvergents, not many actually become increments. Below we will show that among lower semiconvergents $(q,p)=(q_{k-1},p_{k-1})+t(q_k,p_k)$ for all $0\le t<a_k$, at most two increments can appear. Assume these lower semiconvergents indeed have increments appearing. Then we must have $q_{k-1}\le N-x<q_{k+1}$. Let $t=\left\lfloor\dfrac{N-q_{k-1}-x}{q_k}\right\rfloor$. If $t=0$, then the increment is $\Delta x=q_{k-1}$, so after adding the increment, we have $N-x'<q_{k-1}$, and no new increments will appear in these lower semiconvergents; if $t>0$, then after adding the increment, we have $N-x'=(N-q_{k-1}-x)\bmod q_k<q_k$, even if new increments appear in the same segment of lower semiconvergents, next time we can only have $t'=0$. Therefore, in such a segment of lower semiconvergents, at most two increments can appear. This shows that the total time complexity is $O(n)$.

    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/hull-under-line.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/hull-under-line.py:core"
        ```

???+ example "[Timus - Crime and Punishment](https://timus.online/problem.aspx?space=1&num=1430)"
    Given positive integers $A,B,N \le 2\times 10^9$, find $x,y\ge 0$ such that $Ax+By\le N$ and $Ax+By$ is as large as possible.

??? note "Solution"
    This problem has a solution with complexity $O(\sqrt N)$: assume $A\ge B$, since $A(B+x)+By=Ax+B(A+y)$, we only need to search for answers in $x\le\min\{N/A, B\}$. This is enough to pass this problem. However, if we apply the continued fraction method, the time complexity can be reduced to $O(\log N)$.
    
    To facilitate discussion, first change the sign of $x$ by substituting $x\mapsto\left\lfloor N/A\right\rfloor-x$. Let $C=N\bmod A$ and $M=\left\lfloor N/A\right\rfloor$, then the problem transforms into finding the optimal $(x,y)$ that maximizes $By-Ax$ under the conditions $0\le x\le M$ and $By-Ax\le C$. For each fixed $x$, the optimal value of $y$ is $\left\lfloor\dfrac{Ax+C}{B}\right\rfloor$.
    
    What needs to be explained next is that this problem has a similar solution to the previous example. However, unlike the previous example which uses lower semiconvergents to deviate from the line, this problem needs to use upper semiconvergents to approach the line. Specifically, the value of $C-(By-Ax)$ is proportional to the distance between the point $(x,y)$ and the line $By-Ax=C$. To maximize $By-Ax$, it is equivalent to minimize this distance. The goal of the algorithm is to find the feasible lattice point closest to and below the line $By-Ax=C$. The algorithm's idea is to start from the leftmost point, search along the upper convex hull of these lattice points, gradually reduce the distance to the line until the optimal solution is obtained.
    
    In the $(x,y)$ coordinate system, the algorithm starts from $(0,\lfloor C/B\rfloor)$, recursively finds and adds the optimal increment $(\Delta x,\Delta y)$, and ensures that after adding, the point is closer to the line $By-Ax=C$ than before, but does not reach the other side of the line, nor does it let the abscissa exceed $M$. Let the point already obtained be $(x,y)$, then the increment $(\Delta x,\Delta y)$ satisfies the conditions
    
    $$
    0<B\Delta y-A\Delta x\le C-(By-Ax),\ 0<\Delta x\le M-x.
    $$
    
    Following the idea of searching along the lower convex hull, we only need to find the point with the smallest $\Delta x$ among those satisfying these conditions. Rewriting the first inequality as
    
    $$
    \Delta y \le \dfrac{A}{B}\Delta x+\dfrac{C-(By-Ax)}{B}.
    $$
    
    Combined with the [geometric interpretation](#几何解释) from earlier, as long as the subsequent constant term is less than $1$, then among the integer points $(\Delta x,\Delta y)$ satisfying this inequality, the one with the smallest abscissa must correspond to some upper semiconvergent. This is because it is the best approximator from above among all fractions with denominator not exceeding its denominator, which can only be an upper semiconvergent. And after each increment is added, the upper bound of $\Delta y$ becomes tighter, which means we must examine upper semiconvergents with larger denominators.
    
    Following the idea of the previous example. Examine all upper semiconvergents from smallest to largest denominator. If we find an upper semiconvergent whose abscissa and ordinate are both within bounds, we add it and update the corresponding upper bound. When all feasible upper semiconvergents have been added, we get the optimal solution. Compared to the previous problem, this problem needs to ensure that both abscissa and ordinate are within bounds, requiring special attention. Based on similar arguments as in the previous example, but using $B\Delta y-A\Delta x$ instead of $\Delta x$, we can show that the complexity of this algorithm is $O(\log\min\{A,B\})$.
    
    === "C++"
        ```py
        --8<-- "docs/math/code/continued-fraction/closest-dio.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/closest-dio.py:core"
        ```

???+ example "[June Challenge 2017 - Euler Sum](https://www.codechef.com/problems/ES)"
    Find the value of $\sum\limits_{x=1}^N \lfloor \mathrm{e}x \rfloor$, where $\mathrm{e}$ is the base of the natural logarithm.
    
    Hint: $e = [2,1,2,1,1,4,1,1,6,1,\cdots,1,2n,1, \cdots]$.[^continued-fraction-of-e]

??? note "Solution"
    This sum equals the number of lattice points in the set $\{(x,y):1\le x\le N,1\le y\le\mathrm{e}x\}$. After constructing the convex hull of lattice points below the line $y=\mathrm{e}x$, we can use [Pick's theorem](../../geometry/pick.md) to calculate the number of lattice points. The time complexity is $O(\log N)$.
    
    The original problem requires $N \le 10^{4000}$. The C++ code here is only for illustration and does not implement high-precision arithmetic.
    
    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/sum-floor.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/sum-floor.py:core"
        ```

???+ example "[NAIPC 2019 - It's a Mod, Mod, Mod, Mod World](https://open.kattis.com/problems/itsamodmodmodmodworld)"
    Given positive integers $p,q,n$, find the value of $\sum\limits_{i=1}^n [pi \bmod q]$.

??? note "Solution"
    Because the summation can be transformed as
    
    $$
    \sum_{i=1}^n [pi \bmod q] 
    =\sum_{i=1}^n\left(pi - q\left\lfloor\dfrac{pi}{q}\right\rfloor\right) = \dfrac{pn(n+1)}{2} - q\sum_{i=1}^n\left\lfloor\dfrac{p}{q}i\right\rfloor,
    $$
    
    this problem can be transformed into the previous problem by replacing $\mathrm{e}$ with $\dfrac{p}{q}$. The time complexity for a single query is $O(\log\min\{p,q\})$.

    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/mod-mod-mod.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/mod-mod-mod.py:core"
        ```

???+ example "[Library Checker - Sum of Floor of Linear](https://judge.yosupo.jp/problem/sum_of_floor_of_linear)"
    Given positive integers $N,M,A,B$, find $\displaystyle\sum_{i=0}^{N-1} \left\lfloor \frac{A \cdot i + B}{M} \right\rfloor$.

??? note "Solution"
    This is the most complex problem so far. It can be computed using the [Euclidean algorithm](./euclidean.md). The continued fraction-based algorithm is given here, with time complexity $O(\log\min\{A,B\})$.
    
    We can construct the convex hull of all lattice points below the line $y=\dfrac{Ax+B}{M}$ with $0\le x< N$, and use Pick's theorem to calculate the number of lattice points. The case $B=0$ has been solved earlier. For the general case, it can be divided into two steps. First, use upper semiconvergents to gradually approach the line (i.e., the second example) until the point closest to the line is found, then use lower semiconvergents to gradually move away from the line (i.e., the first example).

    === "C++"
        ```py
        --8<-- "docs/math/code/continued-fraction/sum-floor-axbc.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/sum-floor-axbc.py:core"
        ```

???+ example "[OKC 2 - From Modular to Rational](https://codeforces.com/gym/102354/problem/I)"
    There is an unknown rational number $\dfrac{p}{q}$ with $1\le p, q\le 10^9$. You can query the value of $pq^{-1}$ modulo some prime $m\in[10^9,10^{12}]$. Determine the values of $p$ and $q$ in no more than ten queries.
    
    This problem is equivalent to finding $x$ in $[1,N]$ that minimizes $Ax\bmod M$.

??? note "Solution"
    According to the [Chinese remainder theorem](./crt.md), querying results modulo multiple primes is equivalent to querying the result modulo the product of these primes. Therefore, this problem can be seen as querying the fraction modulo a sufficiently large modulus $m$, and requires determining the numerator and denominator of the fraction.
    
    For some modulus $m$, the pair $(p,q)$ that makes $qr\equiv p\pmod m$ hold may not be unique. Assume both $(p_1,q_1)$ and $(p_2,q_2)$ can make this equation hold, then we must have $(p_1q_2-p_2q_1)r\equiv 0\pmod m$. According to the construction of $r$, $r$ is coprime with $m$, so $p_1q_2-p_2q_1\equiv 0\pmod m$, i.e., $m\mid(p_1q_2-p_2q_1)$. If $p_1q_2-p_2q_1$ is not zero, then its absolute value is at least $m$. The problem restricts $p,q\in[1,10^9]$, which means this difference should not exceed $10^{18}$, so we only need to take $m>10^{18}$ to ensure that the obtained $(p,q)$ is unique.
    
    Now the problem reduces to, given a modulus $m$ and a remainder $r$, find positive integer pairs $(p,q)$ not exceeding $n$ such that $qr\equiv p\pmod m$. Knowing that such a solution is unique, we actually only need to find $q\in[1,n]$ that minimizes $qr\bmod m$, because at this time there is exactly one $q$ that makes the remainder not exceed $n$. This is exactly the equivalent statement mentioned earlier.
    
    In the $(q,k)$ coordinate system, this is equivalent to finding the lattice point closest to and below the line $qr-km=0$ when $q\in[1,n]$, because the remainder $qr\bmod m$ is proportional to the distance between the lattice point and the line. Combined with the [geometric interpretation](#几何解释) from earlier, such a lattice point must correspond to some lower semiconvergent of the rational fraction $\dfrac{r}{m}$. The algorithm complexity is $O(\log\min\{r,m\})$.

    === "C++"
        ```cpp
        --8<-- "docs/math/code/continued-fraction/recover-fraction.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/continued-fraction/recover-fraction.py:core"
        ```

## Exercises

-   [UVa OJ - Continued Fractions](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=775)
-   [ProjectEuler+ #64: Odd period square roots](https://www.hackerrank.com/contests/projecteuler/challenges/euler064/problem)
-   [「LibreOJ NOI Round #2」单枪匹马](https://loj.ac/p/573)
-   [Codeforces Round #184 (Div. 2) - Continued Fractions](https://codeforces.com/contest/305/problem/B)
-   [Codeforces Round #201 (Div. 1) - Doodle Jump](https://codeforces.com/contest/346/problem/E)
-   [Codeforces Round #325 (Div. 1) - Alice, Bob, Oranges and Apples](https://codeforces.com/contest/585/problem/C)
-   [POJ Founder Monthly Contest 2008.03.16 - A Modular Arithmetic Challenge](http://poj.org/problem?id=3530)
-   [2019 Multi-University Training Contest 5 - fraction](http://acm.hdu.edu.cn/showproblem.php?pid=6624)
-   [SnackDown 2019 Elimination Round - Election Bait](https://www.codechef.com/SNCKEL19/problems/EBAIT)
-   [Luogu P5179. Fraction](https://www.luogu.com.cn/problem/P5179)
-   [Luogu P7739. \[NOI2021\] 密码箱](https://www.luogu.com.cn/problem/P7739)

## References and Further Reading

-   Hardy, G. H., Wright, E. M., Heath-Brown, R., & Silverman, J. (2008). An Introduction to the Theory of Numbers. Oxford Mathematics.
-   朱尧辰，王连祥《丢番图逼近引论》
-   [FatFish's blog - Introduction to Continued Fractions](https://chaoli.club/index.php/2756)
-   [Simple continued fraction - Wikipedia](https://en.wikipedia.org/wiki/Simple_continued_fraction)
-   [Periodic continued fraction - Wikipedia](https://en.wikipedia.org/wiki/Periodic_continued_fraction)
-   [Gosper's original notes on continued fraction arithmetic algorithms](https://perl.plover.com/yak/cftalk/INFO/gosper.txt)
-   [Understanding Bill Gosper's continued fraction arithmetic (implemented in Python)](https://hsinhaoyu.github.io/cont_frac/)

**The main content of this page is translated from the blog post [Continued fractions](https://cp-algorithms.com/algebra/continued-fractions.html), with the copyright license CC-BY-SA 4.0, and some changes have been made.**

[^one-representation]: The natural number $1$ only has non-standard representations: $1=[1]=[0,1]$.

[^continuant]: The translation comes from Section 6.7 of "Concrete Mathematics" translated by Zhang Mingyao and Zhang Fan.

[^sqrt5]: At this time, we cannot assume that the reduced fraction $\dfrac{p}{q}$ must be a convergent, although Legendre's theorem shows that $\dfrac{p}{q}$ can only be some convergent. For the case of convergents, it can be proved from the error of convergents approximating real numbers.

[^semi-range]: Different literature may have different treatments for whether the range of $t$ here includes the endpoints.

[^semiconvergent]: When $t=0$, it should be understood as a formal continued fraction, equivalent to truncating to the second-to-last term of the continued fraction.

[^nose-streching]: This term is not a professional term. It may be a translation from Russian literature [ЦЕПНЫЕ ДРОБИ](https://old.mccme.ru/free-books/mmmf-lectures/book.14-full.pdf), in the section Алгоритм «вытягивания носов».

[^pgl2]: These properties show that the group of all linear fractional transformations is isomorphic to the [projective linear group](https://en.wikipedia.org/wiki/Projective_linear_group) $PGL_2(\mathbf R)$.

[^period-surd]: The proof can be found in the reference of the [Wikipedia page](https://en.wikipedia.org/wiki/Periodic_continued_fraction#Length_of_the_repeating_block).

[^continued-fraction-of-e]: The proof of the continued fraction expansion of the natural logarithm base $\mathrm{e}$ can be found [here](https://proofwiki.org/wiki/Continued_Fraction_Expansion_of_Euler%27s_Number).