author: iamtwz, Chrogeek, Enter-tainer, StudyingFather, aofall, CCXXXI, CoelacanthusHex, frank-xjh, Great-designer, greyqz, guodong2005, henrytbtrue, Ir1d, kZime, lihaoyu1234, Marcythm, MegaOwIer, Menci, nalemy, orzAtalod, ouuan, Persdre, segment-tree, ShaoChenHeng, shuzhouliu, sshwy, Struggler-q, Tiphereth-A, TrisolarisHD, Xeonacid, yuhuoji

## Definition

Euler's totient function, $\varphi(n)$, represents the number of integers less than or equal to $n$ that are coprime with $n$.

For example, $\varphi(1) = 1$.

When $n$ is prime, obviously $\varphi(n) = n - 1$.

## Properties

-   Euler's totient function is a [multiplicative function](./basic.md#multiplicative-function).

    That is, for any integers $a,b$ satisfying $\gcd(a, b) = 1$, we have $\varphi(ab) = \varphi(a)\varphi(b)$.

    In particular, when $n$ is odd, $\varphi(2n) = \varphi(n)$.

    The proof can be found in [Composition of Residue Systems](./basic.md#composition-of-residue-systems).

-   $n = \sum_{d \mid n}{\varphi(d)}$.

    ???+ note "Proof"
        This can be derived using knowledge of [Möbius inversion](./mobius.md).
        
        Alternatively, consider: if $\gcd(k, n) = d$, then $\gcd(\dfrac{k}{d},\dfrac{n}{d}) = 1, ( k < n )$.
        
        If we let $f(x)$ represent the number of integers where $\gcd(k, n) = x$, then $n = \sum_{i = 1}^n{f(i)}$.
        
        From the proof above, we find that $f(x) = \varphi(\dfrac{n}{x})$, thus $n = \sum_{d \mid n}\varphi(\dfrac{n}{d})$. Noting that the divisors $d$ and $\dfrac{n}{d}$ have symmetry, so the formula becomes $n = \sum_{d \mid n}\varphi(d)$.

-   If $n = p^k$, where $p$ is prime, then $\varphi(n) = p^k - p^{k - 1}$.
    (This follows from the definition)

-   By the unique factorization theorem, if $n = \prod_{i=1}^{s}p_i^{k_i}$, where $p_i$ are primes, then $\varphi(n) = n \times \prod_{i = 1}^s{\dfrac{p_i - 1}{p_i}}$.

    ???+ note "Proof"
        -   Lemma: Let $p$ be any prime, then $\varphi(p^k)=p^{k-1}\times(p-1)$.
        
            Proof: Obviously, among all numbers from $1$ to $p^k$, except for $p^{k-1}$ multiples of $p$, all other numbers are coprime with $p^k$. Therefore, $\varphi(p^k)=p^k-p^{k-1}=p^{k-1}\times(p-1)$. QED.
        
        Next, we prove $\varphi(n) = n \times \prod_{i = 1}^s{\dfrac{p_i - 1}{p_i}}$. By the unique factorization theorem and the multiplicativity of the $\varphi(x)$ function:
        
        $$
        \begin{aligned}
            \varphi(n) &= \prod_{i=1}^{s} \varphi(p_i^{k_i}) \\
            &= \prod_{i=1}^{s} (p_i-1)\times {p_i}^{k_i-1}\\
            &=\prod_{i=1}^{s} {p_i}^{k_i} \times(1 - \frac{1}{p_i})\\
            &=n~ \prod_{i=1}^{s} (1- \frac{1}{p_i})
            &\square
        \end{aligned}
        $$

-   For any non-zero integers $m,n$, $\varphi(mn)\varphi(\gcd(m,n))=\varphi(m)\varphi(n)\gcd(m,n)$.

    This can be directly derived from the previous property.

## Implementation

If we only need the Euler's totient function value for a single number, we can directly compute it by prime factorization. This process can be optimized using the [Pollard Rho](./pollard-rho.md) algorithm.

???+ note "Reference Implementation"
    === "C++"
        ```cpp
        #include <cmath>
        
        int euler_phi(int n) {
          int ans = n;
          for (int i = 2; i * i <= n; i++)
            if (n % i == 0) {
              ans = ans / i * (i - 1);
              while (n % i == 0) n /= i;
            }
          if (n > 1) ans = ans / n * (n - 1);
          return ans;
        }
        ```
    
    === "Python"
        ```python
        import math
        
        
        def euler_phi(n):
            ans = n
            for i in range(2, math.isqrt(n) + 1):
                if n % i == 0:
                    ans = ans // i * (i - 1)
                    while n % i == 0:
                        n = n // i
            if n > 1:
                ans = ans // n * (n - 1)
            return ans
        ```

If we need Euler's totient values for multiple numbers, we can use the linear sieve method to compute them.

See: [Sieve Method for Euler's Totient](./sieve.md#sieve-method-for-eulers-totient)

## Applications

Euler's totient function is often used to simplify a sum of greatest common divisors. Some domestic articles refer to it as **Euler Inversion**[^1].

In the conclusion:

$$
n=\sum_{d|n}\varphi(d)
$$

Substituting $n=\gcd(a,b)$, we have:

$$
\gcd(a,b) = \sum_{d|\gcd(a,b)}\varphi(d) = \sum_d [d|a][d|b]\varphi(d),
$$

where $[\cdot]$ is the Iverson bracket. Summing this equation gives:

$$
\sum_{i=1}^n\gcd(i,n)=\sum_{d}\sum_{i=1}^n[d|i][d|n]\varphi(d)=\sum_d\left\lfloor\frac{n}{d}\right\rfloor[d|n]\varphi(d)=\sum_{d|n}\left\lfloor\frac{n}{d}\right\rfloor\varphi(d).
$$

The key observation here is $\sum_{i=1}^n[d|i]=\lfloor\frac{n}{d}\rfloor$, i.e., the number of integers $i$ between $1$ and $n$ that are divisible by $d$ is $\lfloor\frac{n}{d}\rfloor$.

Using this formula, we can iterate over divisors to sum. When multiple queries are needed, we can preprocess the prefix sums of Euler's totient function and use number theoretic division for queries.

???+ note "[GCD SUM](https://www.luogu.com.cn/problem/P2398)"
    Given $n\le 100000$, find:
    
    $$
    \sum_{i=1}^n\sum_{j=1}^n\gcd(i,j).
    $$
    
    ??? note "Idea"
        Following the derivation above, we can derive:
        
        $$
        \sum_{i=1}^n\sum_{j=1}^n\gcd(i,j) = \sum_{d=1}^n\left\lfloor\frac{n}{d}\right\rfloor^2\varphi(d).
        $$
        
        At this point, we need to iterate from $1$ to $n$ to compute Euler's totient function, which can be done in $O(n)$ using the linear sieve.

## Euler's Theorem

A theorem closely related to Euler's totient function is Euler's theorem. Its description is as follows:

If $\gcd(a, m) = 1$, then $a^{\varphi(m)} \equiv 1 \pmod{m}$.

### Extended Euler's Theorem

Of course, there is also the extended Euler's theorem for handling general cases of $a$ and $m$:

$$
a^b\equiv
\begin{cases}
a^{b\bmod\varphi(m)},\,&\gcd(a,\,m)=1\\
a^b,&\gcd(a,\,m)\ne1,\,b<\varphi(m)\\
a^{b\bmod\varphi(m)+\varphi(m)},&\gcd(a,\,m)\ne1,\,b\ge\varphi(m)
\end{cases}
\pmod m
$$

The proof and practice problems can be found in [Euler's Theorem](./fermat.md).

## Practice Problems

-   [SPOJ ETF. Euler Totient Function](http://www.spoj.com/problems/ETF/)
-   [UVa 10179. Irreducible Basic Fractions](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1120)
-   [UVa 10299. Relatives](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1240)
-   [UVa 11327. Enumerating Rational Numbers](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2302)
-   [TIMUS 1673. Admission to Exam](http://acm.timus.ru/problem.aspx?space=1&num=1673)
-   [Luogu P1390 Sum of Divisors](https://www.luogu.com.cn/problem/P1390)
-   [Luogu P2155 [SDOI2008] Confusion of Princess](https://www.luogu.com.cn/problem/P2155)
-   [Luogu P2568 GCD](https://www.luogu.com.cn/problem/P2568)

## References and Notes

[^1]: This term is not found in academic journals or foreign forums, so it should be noted when using this term.