## Statement

The Lifting the Exponent (LTE) lemma is a frequently used theorem in elementary number theory.

Define $\nu_p(n)$ as the exponent of the prime factor $p$ in the canonical prime factorization of integer $n$, i.e., $\nu_p(n)$ satisfies $p^{\nu_p(n)} \mid n$ and $p^{\nu_p(n)+1} \nmid n$.

Since the LTE lemma has substantial content, we divide it into three parts:

In all that follows, let $p$ be a prime, $x, y$ be integers satisfying $p \nmid x$ and $p \nmid y$, and $n$ be a positive integer.

### Part 1

For all primes $p$ and integers $n$ with $(n, p) = 1$:

1.  If $p \mid x - y$, then:

    $$
    \nu_p\left(x^n - y^n\right) = \nu_p(x - y)
    $$

2.  If $p \mid x + y$, then for odd $n$:

    $$
    \nu_p\left(x^n + y^n\right) = \nu_p(x + y)
    $$

???+ note "Proof"
    If $p \mid x - y$, then $p \mid x - y \iff x \equiv y \pmod p$, and it is easy to see that:

    $$
    \sum_{i=0}^{n-1} x^i y^{n-1-i} \equiv nx^{n-1} \not\equiv 0 \pmod p
    $$

    Then by $x^n - y^n = (x - y)\sum_{i=0}^{n-1} x^i y^{n-1-i}$, the proposition follows.

    The proof for the case $p \mid x + y$ is analogous.

### Part 2

If $p$ is an odd prime:

1.  If $p \mid x - y$, then:

    $$
    \nu_p\left(x^n - y^n\right) = \nu_p(x - y) + \nu_p(n)
    $$

2.  If $p \mid x + y$, then for odd $n$:

    $$
    \nu_p\left(x^n + y^n\right) = \nu_p(x + y) + \nu_p(n)
    $$

???+ note "Proof"
    If $p \mid x - y$, let $y = x + kp$. We only need to prove the case where $p \mid n$.

    -   If $n = p$, then by the binomial theorem:

        $$
        \begin{aligned}
            \sum_{i=0}^{p-1} x^{p-1-i} y^i
            & = \sum_{i=0}^{p-1} x^{p-1-i} \sum_{j=0}^i \binom{i}{j} x^j (kp)^{i-j} \\
            & \equiv px^{p-1} \pmod{p^2}
        \end{aligned}
        $$

        Hence,

        $$
        \nu_p\left(x^n - y^n\right) = \nu_p(x - y) + 1
        $$

    -   If $n = p^a$, then by mathematical induction,

        $$
        \nu_p\left(x^n - y^n\right) = \nu_p(x - y) + a
        $$

    Therefore, the proposition holds.

    The proof for the case $p \mid x + y$ is analogous.

### Part 3

If $p = 2$ and $p \mid x - y$:

1.  For odd $n$ (same as Part 1, case 1):

    $$
    \nu_p\left(x^n - y^n\right) = \nu_p(x - y)
    $$

2.  For even $n$:

    $$
    \nu_p\left(x^n - y^n\right) = \nu_p(x - y) + \nu_p(x + y) + \nu_p(n) - 1
    $$

Additionally, for the above $x, y, n$, we have:

If $4 \mid x - y$, then:

-   $\nu_2(x + y) = 1$
-   $\nu_2\left(x^n - y^n\right) = \nu_2(x - y) + \nu_2(n)$

???+ note "Proof"
    We only need to prove the case where $n$ is even. Since $p \nmid \binom{p}{2}$ in this case, we cannot use the method from Part 2.

    Let $n = 2^a b$, where $a = \nu_p(n)$ and $2 \nmid b$. Then

    $$
    \begin{aligned}
        \nu_p\left(x^n - y^n\right)
        & = \nu_p\left(x^{2^a} - y^{2^a}\right) \\
        & = \nu_p\left((x - y)(x + y)\prod_{i=1}^{a-1} \left(x^{2^i} + y^{2^i}\right)\right)
    \end{aligned}
    $$

    Note that $2 \mid x - y \implies 4 \mid x^2 - y^2$, so $(\forall i \geq 1),~~x^{2^i} + y^{2^i} \equiv 2 \pmod 4$. Hence the above becomes:

    $$
    \nu_p\left(x^n - y^n\right) = \nu_p(x - y) + \nu_p(x + y) + \nu_p(n) - 1
    $$

    Therefore, the proposition holds.

## References

1.  [Lifting-the-exponent lemma - Wikipedia](https://en.wikipedia.org/wiki/Lifting-the-exponent_lemma)