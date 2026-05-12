author: AtomAlpaca, billchenchina, caibyte, Chrogeek, Early0v0, EndlessCheng, Enter-tainer, Henry-ZHR, hly1204, hsfzLZH1, Ir1d, Ghastlcon, kenlig, Marcythm, megakite, Peanut-Tang, qwqAutomaton, qz-cqy, StudyingFather, swift-zym, swiftqwq, Tiphereth-A, TrisolarisHD, Watersail2005, x4Cx58x54, Xeonacid, xiaopangfeiyu, YanWQ-monad

## Introduction

Interpolation is a method for calculating new data points within a certain range based on known, discrete data points. Interpolation methods are commonly used in function fitting.

For example, for data points:

| $x$    | $0$ | $1$      | $2$      | $3$      | $4$       | $5$       | $6$       |
| ------ | --- | -------- | -------- | -------- | --------- | --------- | --------- |
| $f(x)$ | $0$ | $0.8415$ | $0.9093$ | $0.1411$ | $-0.7568$ | $-0.9589$ | $-0.2794$ |

![](../images/interp-1.svg)

Here $f(x)$ is unknown. Interpolation methods can estimate unknown data points by fitting $f(x)$ in a certain form.

For example, we can fit $f(x)$ with a piecewise linear function:

![](../images/interp-2.svg)

This interpolation method is called [linear interpolation](https://en.wikipedia.org/wiki/Linear_interpolation).

We can also fit $f(x)$ with a polynomial:

![](../images/interp-3.svg)

This interpolation method is called [polynomial interpolation](https://en.wikipedia.org/wiki/Polynomial_interpolation).

The general form of polynomial interpolation is as follows:

???+ note "Polynomial Interpolation"
    Given known $n+1$ points $(x_0,y_0),(x_1,y_1),\dots,(x_n,y_n)$, find a polynomial $f(x)=\sum_{i=0}^n a_ix^i$ such that
    
    $$
    f(x_i)=y_i,\qquad\forall i=0,1,\dots,n
    $$
    
    is satisfied.

Below we introduce two methods in polynomial interpolation: Lagrange interpolation and Newton interpolation. It is easy to prove that these two methods yield the same result.

## Lagrange Interpolation

Since we need to construct a function $f(x)$ passing through points $P_1(x_1, y_1), P_2(x_2,y_2),\cdots,P_n(x_n,y_n)$. First, let the projection of the $i$-th point on the x-axis be $P_i^{\prime}(x_i,0)$.

Consider constructing $n$ functions $f_1(x), f_2(x), \cdots, f_n(x)$ such that for the $i$-th function $f_i(x)$, its graph passes through $\begin{cases}P_j^{\prime}(x_j,0),(j\neq i)\\P_i(x_i,y_i)\end{cases}$. Then we know that the function we seek is $f(x)=\sum\limits_{i=1}^nf_i(x)$.

We can set $f_i(x)=a\cdot\prod_{j\neq i}(x-x_j)$. Substituting point $P_i(x_i,y_i)$ gives $a=\dfrac{y_i}{\prod_{j\neq i} (x_i-x_j)}$. Therefore:

$$
f_i(x)=y_i\cdot\dfrac{\prod_{j\neq i} (x-x_j)}{\prod_{j\neq i} (x_i-x_j)}=y_i\cdot\prod_{j\neq i}\dfrac{x-x_j}{x_i-x_j}
$$

Thus, the form of Lagrange interpolation is:

$$
f(x)=\sum_{i=1}^ny_i\cdot\prod_{j\neq i}\dfrac{x-x_j}{x_i-x_j}
$$

The naive implementation has time complexity $O(n^2)$, which can be optimized to $O(n\log^2 n)$, see [Fast Polynomial Interpolation](../poly/multipoint-eval-interpolation.md#polynomial-fast-interpolation).

???+ note "[Luogu P4781【Template】Lagrange Interpolation](https://www.luogu.com.cn/problem/P4781)"
    Given $n$ point pairs $(x_i,y_i)$ and $k$, where $\forall i,j$, $i\neq j \iff x_i\neq x_j$, and $f(x_i)\equiv y_i\pmod{998244353}$ and $\deg(f(x)) < n$ (define $\deg(0)=-\infty$), find $f(k)\bmod{998244353}$.
    
    ??? note "Solution"
        In this problem, we only need to compute $f(k)$, so we can directly substitute $k$ into the above formula during calculation. Sometimes we need to perform more complex operations like multiple evaluations; in those cases we need to find all coefficients of $f$. The code provides an implementation for finding the coefficients.
        
        $$
        f(k)=\sum_{i=1}^{n}y_i\prod_{j\neq i }\frac{k-x_j}{x_i-x_j}
        $$
        
        In this problem, we also need to compute modular inverses. If we compute the numerators and denominators separately first, then multiply the numerator by the modular inverse of the denominator and add to the final answer, the bottleneck will not be in computing inverses, and the time complexity is $O(n^2)$.
        
        Since we are computing under a fixed modulus $998244353$, we can consider the time complexity of computing modular inverses to be constant time here.
    
    ??? note "Code Implementation"
        ```cpp
        --8<-- "docs/math/code/numerical/interp/interp_1.cpp"
        ```

### Lagrange Interpolation with Consecutive Integer x-coordinates

If the x-coordinates of the known points are consecutive integers, we can achieve $O(n)$ interpolation.

Let the polynomial we want be $f(x)$. We know $f(1),\cdots,f(n+1)$ ($1\le i\le n+1$). Substituting into the interpolation formula above:

$$
\begin{aligned}
f(x)&=\sum\limits_{i=1}^{n+1}y_i\prod\limits_{j\ne i}\frac{x-x_j}{x_i-x_j}\\
&=\sum\limits_{i=1}^{n+1}y_i\prod\limits_{j\ne i}\frac{x-j}{i-j}
\end{aligned}
$$

The product can be considered separately for numerator and denominator. The numerator is:

$$
\dfrac{\prod\limits_{j=1}^{n+1}(x-j)}{x-i}
$$

The denominator product $i-j$ can be split into two factorials:

$$
(-1)^{n+1-i}\cdot(i-1)!\cdot(n+1-i)!
$$

Thus the interpolation formula for x-coordinates $1,\cdots,n+1$:

$$
f(x)=\sum\limits_{i=1}^{n+1}(-1)^{n+1-i}y_i\cdot\frac{\prod\limits_{j=1}^{n+1}(x-j)}{(i-1)!(n+1-i)!(x-i)}
$$

Precompute prefix and suffix products of $(x-i)$ and factorial inverses, then substitute into this formula, achieving $O(n)$ complexity.

???+ note "Example Problem [CF622F The Sum of the k-th Powers](https://codeforces.com/contest/622/problem/F)"
    Given $n,k$, compute $\sum\limits_{i=1}^ni^k$ modulo $10^9+7$.
    
    ??? note "Solution"
        In this problem, the answer is a polynomial of degree $k+1$. So we can use a linear sieve to compute $1^i,\cdots,(k+2)^i$ and then perform $O(n)$ interpolation.
        
        It can also be derived from the formula of the difference method using combinatorial mathematics:
        
        $$
        f(x)=\sum_{i=1}^{n+1}\binom{x-1}{i-1}\sum_{j=1}^{i}(-1)^{i+j}\binom{i-1}{j-1}y_{j}=\sum\limits_{i=1}^{n+1}y_i\cdot\frac{\prod\limits_{j=1}^{n+1}(x-j)}{(x-i)\cdot(-1)^{n+1-i}\cdot(i-1)!\cdot(n+1-i)!}
        $$
    
    ??? note "Code Implementation"
        ```cpp
        --8<-- "docs/math/code/numerical/interp/interp_2.cpp"
        ```

## Newton Interpolation

Newton interpolation is a method based on higher-order divided differences, with the advantage of supporting $O(n)$ insertion of new data points.

To achieve $O(n)$ insertion of new data points, we let:

$$
f(x)=\sum_{j=0}^n a_jn_j(x)
$$

where $n_j(x):=\prod_{i=0}^{j-1}(x-x_i)$ is called the **Newton basis**.

If we solve for $a_j$, we obtain the interpolation polynomial of $f(x)$. We define **forward divided differences** as follows:

$$
\begin{aligned}
    \lbrack y_k\rbrack  & := y_k,                                                                & k=0,\dots,n, \\
    [y_k,\dots,y_{k+j}] & := \dfrac{[y_{k+1},\dots,y_{k+j}]-[y_k,\dots,y_{k+j-1}]}{x_{k+j}-x_k}, & k=0,\dots,n-j,~j=1,\dots,n.
\end{aligned}
$$

Then:

$$
\begin{aligned}
    f(x)&=[y_0]+[y_0,y_1](x-x_0)+\dots+[y_0,\dots,y_n](x-x_0)\dots(x-x_{n-1})\\
    &=\sum_{j=0}^n [y_0,\dots,y_j]n_j(x)
\end{aligned}
$$

This is the form of Newton interpolation. The naive implementation has time complexity $O(n^2)$.

If the sample points are equally spaced (i.e., $x_i=x_0+ih$, $i=1,\dots,n$), we can derive:

$$
[y_k,\dots,y_{k+j}]=\frac{1}{j!h^j}\Delta^{(j)}y_k,
$$

where $\Delta^{(j)}y_k$ is the **forward difference**, defined as:

$$
\begin{aligned}
    \Delta^{(0)}y_k & := y_k,                                       & k=0,\dots,n, \\
    \Delta^{(j)}y_k & := \Delta^{(j-1)} y_{k+1}-\Delta^{(j-1)} y_k, & k=0,\dots,n-j,~j=1,\dots,n.
\end{aligned}
$$

Let $x=x_0+sh$. Then Newton interpolation formula becomes:

$$
f(x)=\sum_{j=0}^n \binom{s}{j}j!h^j[y_0,\dots,y_j]=\sum_{j=0}^n \binom{s}{j}\Delta^{(j)}y_0.
$$

??? note "Code Implementation ([Luogu P4781【Template】Lagrange Interpolation](https://www.luogu.com.cn/problem/P4781))"
    ```cpp
    --8<-- "docs/math/code/numerical/interp/interp_3.cpp"
    ```

### Newton Interpolation with Consecutive Integer x-coordinates

For example: Find the coefficients of polynomial $f(x)=\sum_{i=0}^{3} a_ix^i$, given that values of $f(1)$ to $f(6)$ are $1, 5, 14, 30, 55, 91$ respectively.

$$
\begin{array}{cccccccccccc}
1 &    &  5 &    & 14 &    & 30 &    & 55 &    & 91 & \\
&  4 &    &  9 &    & 16 &    & 25  &    & 36 & \\
&    &  5 &    &  7 &    &  9 &    &  11 & \\
&    &    &  2 &    &  2 &    &  2 & \\
\end{array}
$$

The first row contains the first $n$ consecutive values of $f(x)$; each subsequent row contains the differences between corresponding adjacent terms in the previous row. It can be observed that if this operation is performed enough times (provided $f(x)$ is a polynomial), it will eventually return a constant value.

The first term of the $i-1$-th order difference is $\sum_{j=1}^{i}(-1)^{i+j}\binom{i-1}{j-1}f(j)$. The contribution of the first term of the $i-1$-th order difference to $f(k)$ is $\binom{k-1}{i-1}$.

$$
f(k)=\sum_{i=1}^n\binom{k-1}{i-1}\sum_{j=1}^{i}(-1)^{i+j}\binom{i-1}{j-1}f(j)
$$

The time complexity is $O(n^2)$.

## Implementation in C++

Since C++20, the standard library has added [`std::midpoint`](https://en.cppreference.com/w/cpp/numeric/midpoint) and [`std::lerp`](https://en.cppreference.com/w/cpp/numeric/lerp) functions, used for computing midpoints and linear interpolation respectively.

## Exercises

-   ["NOIP2020" WeChat Steps](https://loj.ac/p/3389)
-   ["United Provincial Selection 2022" Tree Filling](https://loj.ac/p/3701)
-   ["NOI2019" Robot](https://loj.ac/p/3157)

## References

1.  [Interpolation - Wikipedia](https://en.wikipedia.org/wiki/Interpolation)
2.  [Newton polynomial - Wikipedia](https://en.wikipedia.org/wiki/Newton_polynomial)