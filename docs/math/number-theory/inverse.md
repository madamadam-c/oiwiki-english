This article introduces the modular multiplicative inverse and discusses common methods to compute it.

## Basic Concepts

The multiplicative inverse of a non-zero real number $a\in\mathbf R$ is its reciprocal $a^{-1}$. Similarly, in number theory, we can also define the inverse of an integer $a$ modulo $m$, simply denoted as $a^{-1}$. This is the **modular multiplicative inverse**, also called the **number-theoretic reciprocal**.

???+ abstract "Inverse"
    For non-zero integers $a,m$, if there exists $b$ such that $ab\equiv 1\pmod m$, then $b$ is called the **inverse** of $a$ modulo $m$.

This is equivalent to saying that $b$ is the solution to the linear congruence $ax\equiv 1\pmod m$. According to the properties of [linear congruence equations](./linear-equation.md), the inverse $a^{-1}\bmod m$ exists if and only if $\gcd(a,m)=1$, i.e., $a,m$ are coprime, and it is unique modulo $m$.

## Computing a Single Inverse

Using the extended Euclidean algorithm or fast exponentiation, we can compute the inverse of a single integer in $O(\log m)$ time.

### Extended Euclidean Algorithm

Solving for an inverse is equivalent to solving a linear congruence. Therefore, the [extended Euclidean algorithm](./gcd.md#extended-euclidean-algorithm) can be used to solve the inverse in $O(\log\min\{a,m\})$ time. Also, because the linear equation corresponding to the inverse is special, the corresponding steps can be appropriately simplified.

???+ example "Reference Implementation"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/inverse/inverse-1.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/inverse/inverse-1.py:core"
        ```

This algorithm applies to all cases where the inverse exists.

### Fast Exponentiation Method

This method primarily applies when the modulus is a prime $p$. At this time, by [Fermat's Little Theorem](./fermat.md#fermats-little-theorem), for any $a\perp p$:

$$
a\cdot a^{p-2} = a^{p-1} \equiv 1 \pmod p.
$$

By the uniqueness of the inverse, the inverse $a^{-1}\bmod p$ equals $a^{p-2}\bmod p$. Therefore, it can be directly computed using [fast exponentiation](../binary-exponentiation.md) in $O(\log p)$ time:

???+ example "Reference Implementation"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/inverse/inverse-2.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/inverse/inverse-2.py:core"
        ```

Theoretically, this method can be generalized to the general modulus $m$ using [Euler's Theorem](./fermat.md#eulers-theorem), i.e., using $a^{\varphi(m)-1}\bmod m$ to compute the inverse. However, computing [Euler's function](./euler-totient.md) $\varphi(m)$ for a single case is not easy, so this algorithm is generally not efficient.

## Computing Multiple Inverses

In some scenarios, we need to quickly compute the inverses of multiple integers $a_1,a_2,\cdots,a_n$ modulo $m$. At this time, solving for inverses one by one would take a total of $O(n\log m)$ time. In fact, if we process them together, we can compute the inverses of all integers in $O(n+\log m)$ time.

Consider the prefix products of the sequence $\{a_i\}$:

$$
S_0 = 1,~ S_i = a_iS_{i-1},~ i=1,2,\cdots,n.
$$

As long as each $a_i$ is coprime with $m$, their product $S_n$ is also coprime with $m$. Therefore, we can compute the value of $S_n^{-1}\bmod m$ using the algorithm described earlier. Because the inverse of a product is the product of inverses, starting from $S_n^{-1}$, we can traverse the sequence backwards to find the inverse of each $S_i$:

$$
S_{i-1}^{-1} = a_iS_i^{-1} \bmod m,~ i = n,n-1,\cdots,1.
$$

From this, the inverse of a single $a_i$ can be computed by:

$$
a_i^{-1} = S_{i-1}S_i^{-1} \bmod m,~ i = 1,2,\cdots,n.
$$

The reference implementation is as follows:

???+ example "Reference Implementation"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/inverse/inverse-3.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/inverse/inverse-3.py:core"
        ```

In this algorithm, only one single-element inverse is computed, so the total time complexity is $O(n+\log m)$.

## Linear Time Precomputation of Inverses

If we need to precompute the inverses of the first $n$ positive integers modulo a prime $p$, we can use the recurrence relation to be discussed in this section to compute them in $O(n)$ time. This method is often used in combinatorics to precompute the reciprocals of factorials of the first $n$ positive integers.

For positive integers $1< i < p$, examine the division with remainder:

$$
p = \left\lfloor \dfrac{p}{i} \right\rfloor i + (p\bmod i).
$$

Taking this equation modulo the prime $p$:

$$
0 \equiv \left\lfloor \dfrac{p}{i} \right\rfloor i + (p\bmod i) \pmod p.
$$

Multiplying both sides by $i^{-1}(p\bmod i)^{-1}$:

$$
i^{-1} \equiv - \left\lfloor \dfrac{p}{i} \right\rfloor (p\bmod i)^{-1} \pmod p.
$$

This is the formula for linear time recurrence to compute inverses. Since $p\bmod i < i$, this formula transforms the problem of computing $i^{-1}\bmod p$ into a smaller problem $(p\bmod i)^{-1}\bmod p$. Therefore, starting from $1^{-1}\bmod p=1$, applying this formula sequentially for each $i$, we can obtain the inverses of the first $n$ integers in $O(n)$ time.

The reference implementation is as follows:

???+ example "Reference Implementation"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/inverse/inverse-4.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/inverse/inverse-4.py:core"
        ```

This algorithm only applies when the modulus is a prime. For modulus $m$ that is not prime, we cannot guarantee that $m\bmod i$ in the recurrence formula is still coprime with $m$, so the $(m\bmod i)^{-1}$ required for the recurrence may not exist. An example of this is $m=8,i=3$. At this time, $m\bmod i = 2$, and the inverse modulo $m$ does not exist.

Additionally, after obtaining this recurrence formula, a natural idea is to recursively solve for the inverse of any number $a$. During each recursion, use the recurrence formula to transform it into the inverse of a smaller remainder $p\bmod a$, until the remainder becomes $1$. Currently, the complexity of doing so[^linear-recursion] is not clear, so the conventional method described earlier is recommended.

## Practice Problems

-   [LOJ 110 Multiplicative Inverse](https://loj.ac/problem/110)
-   [LOJ 161 Multiplicative Inverse 2](https://loj.ac/problem/161)
-   [LOJ 2605 [NOIP2012] Congruence Equation](https://loj.ac/problem/2605)
-   [Luogu P2054 [AHOI2005] Shuffle](https://www.luogu.com.cn/problem/P2054)
-   [LOJ 2034 [SDOI2016] Permutation Count](https://loj.ac/problem/2034)

## References and Notes

-   [Modular multiplicative inverse - Wikipedia](https://en.wikipedia.org/wiki/Modular_multiplicative_inverse)

[^linear-recursion]: [riteme's answer on Zhihu](https://www.zhihu.com/question/59033693/answer/323292359) points out that the theoretically known upper bound of the complexity is $O(p^{1/3+\varepsilon})$, while the actual performance on random data is close to $O(\log p)$.
