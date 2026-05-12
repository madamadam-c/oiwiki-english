Prerequisites: [Factorial Modulo](./factorial.md)

## Introduction

This article discusses solving large binomial coefficients modulo a number. Binomial coefficients, also called binomial coefficients, refer to the expression:

$$
\binom{n}{k} = \dfrac{n!}{k!(n-k)!}.
$$

When the scale is small, binomial coefficients can be computed using recurrence relations with time complexity $O(nk)$; or, under a sufficiently large prime modulus $p>n$, they can be computed in $O(n)$ time by calculating the factorials of the numerator and denominator. But when the problem scale is very large ($n\sim 10^{18}$), these methods no longer apply.

Based on Lucas's theorem and its extensions, this article discusses a method for computing binomial coefficients when the modulus is not too large ($m \sim 10^6$). More precisely, this method can be used as long as the sum of all prime powers (i.e., $\sum p_i^{e_i}$) in the prime factorization $m=\prod p_i^{e_i}$ is around $10^6$, because the preprocessing of the algorithm is roughly of this scale.

## Lucas's Theorem

First, we discuss the case where the modulus is a prime $p$. Then we have Lucas's theorem:

???+ note "Lucas's Theorem"
    For a prime $p$,
    
    $$
    \binom{n}{k}\equiv \binom{\lfloor n/p\rfloor}{\lfloor k/p\rfloor}\binom{n\bmod p}{k\bmod p}\pmod p.
    $$
    
    Here, when $n<k$, the binomial coefficient $\dbinom{n}{k}$ is defined as $0$.

??? note "Proof Using Generating Functions"
    Consider the value of $\displaystyle\binom{p}{n} \bmod p$. Because
    
    $$
    \binom{p}{n} = \frac{p!}{n!(p-n)!},
    $$
    
    when $n\neq 0,p$, the denominator has no factor $p$, but the numerator has a factor $p$, so the fraction is a multiple of $p$ and the remainder modulo $p$ is $0$; when $n=0$ or $n=p$, the fraction equals $1$. Therefore,
    
    $$
    \binom{p}{n} \equiv [n=0\lor n=p] \pmod p.
    $$
    
    Let $f(x) = ax^n + bx^m$. In general, by the binomial expansion and Fermat's little theorem, we have
    
    $$
    \begin{aligned}
    (f(x))^p 
    &= \left(ax^n + bx^m\right)^p \\
    &= \sum_{k=0}^p\binom{p}{k}(ax^n)^k(bx^m)^{p-k}\\
    &\equiv a^px^{pn} + b^px^{pm} \\
    &\equiv a(x^p)^n+b(x^p)^m\\
    &= f(x^p) \pmod p.
    \end{aligned}
    $$
    
    The congruence in the third line uses the conclusion from the preceding discussion that the binomial coefficient is not a multiple of $p$ only when $k=0,p$.
    
    Using this conclusion, examine the binomial expansion:
    
    $$
    \begin{aligned}
    (1+x)^n &= (1+x)^{p\lfloor n/p\rfloor}(1+x)^{n\bmod p} \\
    &\equiv (1+x^p)^{\lfloor n/p\rfloor}(1+x)^{n\bmod p} \pmod p.
    \end{aligned}
    $$
    
    On the left side, the coefficient of the term $x^k$ is
    
    $$
    \binom{n}{k}\bmod p.
    $$
    
    Now compute the coefficient of $x^k$ on the right side. The exponent of each term in the first factor must be a multiple of $p$, while the exponent of each term in the second factor must be less than $p$. The way to decompose $k$ into the sum of these two parts is unique, namely the division algorithm: $k=p\lfloor k/p\rfloor +(k\bmod p)$. Therefore, the first factor can only contribute its $p\lfloor k/p\rfloor$-th power term, and the second factor can only contribute its $(k\bmod p)$-th power term. So the coefficient of $x^k$ on the right side is the product of the contributions from the two factors:
    
    $$
    \binom{\lfloor n/p\rfloor}{\lfloor k/p\rfloor}\binom{n\bmod p}{k\bmod p}\bmod p.
    $$
    
    Equating the coefficients on both sides yields Lucas's theorem.

??? note "Proof Using Conclusions from Factorial Modulo"
    This provides a proof method based on the conclusions from factorial modulo, in order to establish a connection with the exLucas part discussed later. The binomial coefficient is
    
    $$
    \binom{n}{k} = \dfrac{n!}{k!(n-k)!}.
    $$
    
    Separating the power of $p$ from the other factors in the factorial $n!$, we get the decomposition:
    
    $$
    n! = p^{\nu_p(n!)}(n!)_p.
    $$
    
    This gives the expression for the binomial coefficient:
    
    $$
    \binom{n}{k} = p^{\nu_p(n!)-\nu_p(k!)-\nu_p((n-k)!)}\dfrac{(n!)_p}{(k!)_p((n-k)!)_p}.
    $$
    
    The power $\nu_p(n!)$ and the factorial remainder $(n!)_p\bmod p$ both have recurrence formulas:
    
    $$
    \begin{aligned}
    \nu_p(n!) &= \lfloor n/p\rfloor+\nu_p( \lfloor n/p\rfloor!),\\
    (n!)_p &\equiv (-1)^{\lfloor n/p\rfloor}\cdot (n\bmod p)!\cdot (\lfloor n/p\rfloor!)_p\pmod p.
    \end{aligned}
    $$
    
    The former is a corollary of Legendre's formula, and the latter is a corollary of Wilson's theorem.
    
    Substituting the recurrence formulas into the expression for the binomial coefficient and rearranging, we get:
    
    $$
    \begin{aligned}
    \binom{n}{k} &\equiv (-p)^{\lfloor n/p\rfloor-\lfloor k/p\rfloor-\lfloor(n-k)/p\rfloor}\cdot\dfrac{(n\bmod p)!}{(k\bmod p)!((n-k)\bmod p)!} \\
    &\quad \cdot p^{\nu_p(\lfloor n/p\rfloor!)-\nu_p(\lfloor k/p\rfloor!)-\nu_p(\lfloor(n-k)/p\rfloor!)}\dfrac{(\lfloor n/p\rfloor!)_p}{(\lfloor k/p\rfloor!)_p(\lfloor(n-k)/p\rfloor!)_p} \pmod p.
    \end{aligned}
    $$
    
    Now examine the value of $\lfloor n/p\rfloor-\lfloor k/p\rfloor-\lfloor(n-k)/p\rfloor$. Because we have
    
    $$
    \begin{aligned}
    n &= \lfloor n/p\rfloor p + (n\bmod p),\\
    k &= \lfloor k/p\rfloor p + (k\bmod p),\\
    n-k &= \lfloor (n-k)/p\rfloor p + ((n-k)\bmod p),\\
    \end{aligned}
    $$
    
    subtracting the latter two equations from the first gives
    
    $$
    (\lfloor n/p\rfloor-\lfloor k/p\rfloor-\lfloor(n-k)/p\rfloor)p = (k\bmod p)+((n-k)\bmod p)-(n\bmod p).
    $$
    
    On the right side, the sum of the first two terms is strictly less than $2p$, and the third term $n\bmod p$ is precisely the remainder of the first two terms' sum. Therefore, the right side is non-negative but less than $2p$, and must be a multiple of $p$, so it can only be $0$ or $p$. This means $\lfloor n/p\rfloor-\lfloor k/p\rfloor-\lfloor(n-k)/p\rfloor$ can only be $0$ or $1$:
    
    -   If it is $0$, then $(n\bmod p) = (k\bmod p)+((n-k)\bmod p)$ also holds. Therefore, the exponent of the first factor in the formula above is $0$, so the factor equals one; the second factor is $\dbinom{n\bmod p}{k\bmod p}$; and the third factor, by the earlier expansion, equals $\dbinom{\lfloor n/p\rfloor}{\lfloor k/p\rfloor}$. In this case, Lucas's formula holds;
    -   If it is $1$, then the exponent of the first factor is $1$, so the factor equals zero, and the remainder of the binomial coefficient is zero. At the same time, the $\dbinom{n\bmod p}{k\bmod p}$ on the right side of Lucas's theorem must also be zero, because at this point $(n\bmod p)<(k\bmod p)$ must hold; otherwise, we would have
    
        $$
        ((n-k)\bmod p) = p + (n\bmod p) - (k\bmod p) \ge p,
        $$
    
        which clearly contradicts the definition of a remainder.
    
    Combining the two cases yields Lucas's theorem, as required. This proof shows that when computing binomial coefficients under a prime modulus, the results obtained using Lucas's theorem and using the exLucas algorithm are equivalent.

Lucas's theorem shows that when the modulus is a prime $p$, the computation of large binomial coefficients can be reduced to computations of smaller binomial coefficients. In the right-hand side formula, the first binomial coefficient can be recursively reduced until $n, k < p$; the second binomial coefficient can be computed directly, or precomputed in advance. In code form:

???+ example "Illustration"
    ```cpp
    long long Lucas(long long n, long long k, long long p) {
      if (k == 0) return 1;
      return (C(n % p, k % p, p) * Lucas(n / p, k / p, p)) % p;
    }
    ```

Here, `C(n, k, p)` is used to compute small-scale binomial coefficients.

The recursion proceeds at most $O(\log_p n)$ times, so the algorithm's complexity is $O(f(p)+g(p)\log_p n)$, where $f(p)$ is the complexity of preprocessing binomial coefficients, and $g(p)$ is the complexity of a single binomial coefficient computation.

### Reference Implementation

The reference implementation below precomputes factorials and their modular inverses for all numbers up to $p$ in $O(p)$ time, then computes a single binomial coefficient in $O(1)$ time:

??? example "Reference Implementation"
    ```cpp
    --8<-- "docs/math/code/lucas/lucas.cpp"
    ```

The time complexity of this implementation is $O(p+T\log_p n)$, where $T$ is the number of queries.

## exLucas Algorithm

Lucas's theorem requires the modulus $p$ to be prime. For cases where $p$ is not prime, we need the exLucas algorithm. Despite its name, this algorithm does not actually use Lucas's theorem in practice. Its key step is computing factorials modulo prime powers. The second proof above points out its connection to Lucas's theorem.

### Prime Power Modulus

First, consider the case where the modulus is a prime power $p^\alpha$. Separating the power of $p$ from the other factors in the factorial $n!$, we get the decomposition:

$$
n! = p^{\nu_p(n!)}(n!)_p.
$$

Here, $\nu_p(n!)$ is the power of $p$ in the prime factorization of $n!$, and $(n!)_p$ is clearly coprime with $p$. Therefore, the binomial coefficient can be written as:

$$
\binom{n}{k} = p^{\nu_p(n!)-\nu_p(k!)-\nu_p((n-k)!)}\dfrac{(n!)_p}{(k!)_p((n-k)!)_p}.
$$

The $\nu_p(n!)$, etc., can be computed using Legendre's formula, and $(n!)_p$, etc., can be computed using recurrence relations. Since the latter is coprime with $p^\alpha$, the modular inverse of the denominator's product can be computed using the extended Euclidean algorithm. The problem is thus solved.

Note that if the power $\nu_p(n!)-\nu_p(k!)-\nu_p((n-k)!)\ge\alpha$, the remainder must be zero, and no further computation is needed.

### General Modulus

For a general composite modulus $m$, we first perform prime factorization:

$$
m = p_1^{\alpha_1}p_2^{\alpha_2}\cdots p_s^{\alpha_s}.
$$

Then, compute the remainders of the binomial coefficient $\dbinom{n}{k}$ modulo $p_i^{\alpha_i}$ separately, obtaining $s$ congruence equations:

$$
\begin{cases}
\dbinom{n}{k} \equiv r_1, &\pmod{p_1^{\alpha_1}}, \\
\dbinom{n}{k} \equiv r_2, &\pmod{p_2^{\alpha_2}}, \\
\quad\quad\cdots\\
\dbinom{n}{k} \equiv r_s, &\pmod{p_s^{\alpha_s}}.
\end{cases}
$$

Finally, use the Chinese Remainder Theorem to find the remainder modulo $m$.

### Reference Implementation

Finally, here is a reference implementation for the template problem Binomial Coefficient.

??? example "Reference Implementation"
    ```cpp
    --8<-- "docs/math/code/lucas/exlucas.cpp"
    ```

This algorithm first factors the modulus $m$ into prime powers, then precomputes for all $p^\alpha$ the product of all natural numbers from $1$ to $p^\alpha$ that are not multiples of $p$, as well as the corresponding coefficients for merging answers in the Chinese Remainder Theorem. The preprocessing time complexity is $O(\sqrt{m}+\sum_ip_i^{\alpha_i})$. Each query has complexity $O(\log m+\sum_i\log_{p_i}n)$, where the two terms are respectively the complexity of computing modular inverses and the complexity of computing powers and factorial remainders.

## Exercises

-   [Luogu3807 Template Lucas's Theorem](https://www.luogu.com.cn/problem/P3807)
-   [SDOI2010 Ancient Pig Text Lucas's Theorem](https://loj.ac/problem/10229)
-   [Luogu4720 Template Extended Lucas](https://www.luogu.com.cn/problem/P4720)
-   [Ceizenpok's formula](http://codeforces.com/gym/100633/problem/J)
