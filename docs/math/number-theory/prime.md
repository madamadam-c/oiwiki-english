author: Ir1d, Tiphereth-A, c-forrest, Xeonacid, Enter-tainer, StudyingFather, iamtwz, ksyx, Marcythm, MegaOwIer, 383494, Alpacabla, HeRaNO, abc1763613206, alphagocc, Backl1ght, CCXXXI, drkelo, Early0v0, Great-designer, greyqz, GuanghaoYe, H-J-Granger, HHH2309, isdanni, kenlig, lazyasn, Menci, ouuan, r-value, shawlleyw, shopee-jin, shuzhouliu, Siger Young, TrisolarisHD, untitledunrevised, void-mian, Voileexperiments, weilycoder, xtlsoft, yusancky, YuzhenQin1, sun2snow

The definitions of prime numbers and composite numbers can be found in [Number Theory Basics](./basic.md).

The prime counting function: the number of prime numbers less than or equal to $x$, denoted as $\pi(x)$. As $x$ increases, there is the approximation: $\pi(x) \sim \dfrac{x}{\ln(x)}$.

## Primality Test

A **primality test** can be used to determine whether a given natural number is prime.

There are two types of primality tests:

1.  Deterministic test: Absolutely determines whether a number is prime. Common examples include trial division, Lucas-Lehmer test, and elliptic curve primality proof.
2.  Probabilistic test: Usually much faster than deterministic tests, but may (although with very small probability) incorrectly identify [composite numbers](../number-theory/basic.md#prime-numbers-and-composite-numbers) as primes (although the reverse never happens). Therefore, numbers that pass probabilistic primality tests are called **probable primes** until their primality can be proved deterministically. And numbers that pass the test but are actually composite are called **pseudoprimes**. There are many specific types of pseudoprimes, the most common being Fermat pseudoprimes, which are composite numbers that satisfy Fermat's little theorem. Common examples of probabilistic tests include Miller-Rabin test.

### Trial Division

The brute-force approach naturally enumerates each number from small to large to see if it can divide.

???+ example "Reference Implementation"
    === "C++"
        ```cpp
        bool isPrime(int a) {
          if (a < 2) return false;
          for (int i = 2; i < a; ++i)
            if (a % i == 0) return false;
          return true;
        }
        ```
    
    === "Python"
        ```python
        def isPrime(a):
            if a < 2:
                return False
            for i in range(2, a):
                if a % i == 0:
                    return False
            return True
        ```

This is very safe, but is it really necessary to check every number?

It is easy to discover this fact: if $x$ is a divisor of $a$, then $\frac{a}{x}$ is also a divisor of $a$.

This conclusion tells us that for each pair $(x, \frac{a}{x})$, checking only one is sufficient. For convenience, we only examine the smaller number in each pair. It is easy to see that all these smaller numbers are in the interval $[1, \sqrt{a}]$.

Since $1$ is always a divisor, we don't check it.

???+ example "Reference Implementation"
    === "C++"
        ```cpp
        bool isPrime(int a) {
          if (a < 2) return 0;
          for (int i = 2; (long long)i * i <= a; ++i)  // prevent overflow
            if (a % i == 0) return 0;
          return 1;
        }
        ```
    
    === "Python"
        ```python
        def isPrime(a):
            if a < 2:
                return False
            for i in range(2, int(sqrt(a)) + 1):
                if a % i == 0:
                    return False
            return True
        ```

### Fermat Primality Test

**Fermat primality test** is the simplest probabilistic primality test.

We can derive a method for testing primality using [Fermat's Little Theorem](./fermat.md#fermats-little-theorem):

The basic idea is to repeatedly select a base $a$ in $[2, n-1]$ and check if $a^{n-1} \equiv 1 \pmod n$ each time.

???+ example "Reference Implementation"
    === "C++"
        ```cpp
        bool fermat(int n) {
          if (n < 3) return n == 2;
          // test_time is the number of tests, recommended to be at least 8
          // to ensure correctness, but should not be too large, otherwise efficiency will be affected
          for (int i = 1; i <= test_time; ++i) {
            int a = rand() % (n - 2) + 2;
            if (quickPow(a, n - 1, n) != 1) return false;
          }
          return true;
        }
        ```
    
    === "Python"
        ```python
        def fermat(n):
            if n < 3:
                return n == 2
            # test_time is the number of tests, recommended to be at least 8
            # to ensure correctness, but should not be too large, otherwise efficiency will be affected
            for i in range(1, test_time + 1):
                a = random.randint(0, 32767) % (n - 2) + 2
                if quickPow(a, n - 1, n) != 1:
                    return False
            return True
        ```

If $a^{n-1} \equiv 1\pmod n$ but $n$ is not prime, then $n$ is called a **Fermat pseudoprime** to base $a$. In practice, we observe that if $a^{n-1} \equiv 1\pmod n$, then $n$ is usually prime. But there are counterexamples: for $n = 341$ and $a = 2$, although $2^{340}\equiv 1 {\pmod {341}}$, $341 = 11 \cdot 31$ is composite. In fact, for any fixed base $a$, there are infinitely many such counterexamples[^inf-fermat-pp].

Since for a single base, the Fermat primality test cannot guarantee correctness, a natural approach is to check several bases. However, even if we check all possible bases $a$ coprime with $n$, we still cannot guarantee that $n$ is prime. That is, the converse of Fermat's little theorem does not hold: even if $a^{n-1}\equiv 1\pmod n$ for all $a\perp n$, $n$ is not necessarily prime. Such numbers are called [Carmichael numbers](./primitive-root.md#carmichael-numbers). There are infinitely many of them as well. This forces us to look for more rigorous primality tests.

### Miller-Rabin Primality Test

The **Miller-Rabin primality test** is a better method for determining primes. It was optimized by Miller and Rabin based on the Fermat primality test. Like other probabilistic primality tests, it can only detect pseudoprimes. To ensure primality, we need to use much slower deterministic algorithms. However, in practice, there are no known numbers that pass advanced probabilistic tests like Miller-Rabin but are actually composite, so we can safely use it.

Not considering the complexity of multiplication, the time complexity of testing $k$ rounds for number $n$ is $O(k \log n)$. The Miller-Rabin primality test is often used for testing high-precision numbers, where the time complexity is $O(k \log^3 n)$, which can be optimized to $O(k \log^2 n \log \log n \log \log \log n)$ using FFT and other techniques.

To address the challenge posed by Carmichael numbers, the Miller-Rabin primality test further considers the following property of primes:

???+ note "Quadratic probing theorem"
    If $p$ is an odd prime, the solutions to $x^2 \equiv 1 \pmod p$ are $x \equiv 1 \pmod p$ or $x \equiv p - 1 \pmod p$.

??? note "Proof"
    It is easy to verify that when $p$ is an odd prime, both $x\equiv 1\pmod p$ and $x\equiv p-1\pmod p$ satisfy the equation. By [Lagrange's Theorem](./congruence-equation.md#theorem-3-lagranges-theorem), these are all the solutions to the equation.

Combining Fermat's little theorem and the quadratic probing theorem gives us the Miller-Rabin primality test:

1.  Decompose the exponent $n-1$ into $n-1=u \times 2^t$;
2.  In each round of testing, for the randomly selected $a$, first compute $v = a^{u} \bmod n$, then perform up to $t$ squaring operations on this value;
3.  Throughout the process, if a non-trivial square root of $1$ (i.e., roots other than $\pm 1$) is found, we can determine that the number is not prime;
4.  Otherwise, use the Fermat primality test to judge.

There are some implementation details:

-   In one round of testing, if at some point $a^{u \times 2^s} \equiv n-1 \pmod n$, then all subsequent squaring operations will result in $1$, and we can directly pass this round.
-   If a non-trivial square root $a^{u \times 2^s} \not\equiv n-1 \pmod n$ is found, then all subsequent squaring operations will result in $1$. We can choose to return `false` directly, or return `false` after $t$ squaring operations.

This gives us the more accurate Miller-Rabin (from fjzzq2002):

???+ example "Reference Implementation"
    === "C++"
        ```cpp
        bool millerRabin(int n) {
          if (n < 3 || n % 2 == 0) return n == 2;
          if (n % 3 == 0) return n == 3;
          int u = n - 1, t = 0;
          while (u % 2 == 0) u /= 2, ++t;
          // test_time is the number of tests, recommended to be at least 8
          // to ensure correctness, but should not be too large, otherwise efficiency will be affected
          for (int i = 0; i < test_time; ++i) {
            // 0, 1, n-1 can directly pass the test, a is in range [2, n-2]
            int a = rand() % (n - 3) + 2, v = quickPow(a, u, n);
            if (v == 1) continue;
            int s;
            for (s = 0; s < t; ++s) {
              if (v == n - 1) break;  // found trivial square root n-1, pass this round
              v = (long long)v * v % n;
            }
            // if a non-trivial square root is found, it will run to s == t because cannot break early
            // if Fermat primality test cannot pass, v will never equal -1 before running to s == t
            if (s == t) return 0;
          }
          return 1;
        }
        ```
    
    === "Python"
        ```python
        def millerRabin(n):
            if n < 3 or n % 2 == 0:
                return n == 2
            if n % 3 == 0:
                return n == 3
            u, t = n - 1, 0
            while u % 2 == 0:
                u = u // 2
                t = t + 1
            # test_time is the number of tests, recommended to be at least 8
            # to ensure correctness, but should not be too large, otherwise efficiency will be affected
            for i in range(test_time):
                # 0, 1, n-1 can directly pass the test, a is in range [2, n-2]
                a = random.randint(2, n - 2)
                v = pow(a, u, n)
                if v == 1:
                    continue
                s = 0
                while s < t:
                    if v == n - 1:
                        break
                    v = v * v % n
                    s = s + 1
                # if a non-trivial square root is found, it will run to s == t because cannot break early
                # if Fermat primality test cannot pass, v will never equal -1 before running to s == t
                if s == t:
                    return False
            return True
        ```

It can be proven[^millerrabinproof] that for an odd composite number $n > 9$, the probability of passing the Miller-Rabin primality test with a randomly selected base $a$ is at most one-fourth. Therefore, after randomly selecting $k$ bases, the probability of still misjudging a composite number as prime does not exceed $1/4^k$.

??? note "Proof"
    Let $n-1=u2^t$, where $u$ is odd and $t$ is a positive integer. Then, integer $n$ passing the Miller-Rabin primality test with base $a$ means:
    
    $$
    a^u\equiv 1{\textstyle\pmod n},\text{ or }a^{u2^i}\equiv -1{\textstyle\pmod n}\text{ for some }0\le i < t.
    $$
    
    Let the set of such $a$ (congruence classes) be $S$. What needs to be shown is:
    
    $$
    |S| \le \dfrac14\varphi(n).
    $$
    
    Here, $\varphi(n)$ is [Euler's totient function](./euler-totient.md). The proof is divided into three steps.
    
    **Step One**: Let $\ell$ be the largest positive integer such that $2^\ell \mid p-1$ for all prime factors $p$ of $n$. Then it can be proven that:
    
    $$
    S\subseteq S' = \{a\bmod n:a^{u2^{\ell-1}}\equiv\pm 1{\textstyle\pmod n}\}.
    $$
    
    There are only two possible types of elements $a$ in set $S$. If $a^u\equiv 1\pmod n$, then obviously $a^{u2^{\ell-1}}\equiv 1\pmod n$ also holds, i.e., $a\in S'$. If $a^{u2^i}\equiv -1\pmod n$ holds for $0\le i < t$, then for any prime factor $p\mid n$, we have $a^{u2^i}\equiv-1\pmod p$. Let $\delta_p(a)$ be the [order](./primitive-root.md#order) of $a$ modulo $p$. Then obviously $\delta_p(a)\mid u2^{i+1}$ but $\delta_p(a)\nmid u2^{i}$, which means that in the prime factorization of $\delta_p(a)$, the exponent of $2$ is exactly $i+1$, thus $2^{i+1}\mid\delta_p(a)$. By Fermat's little theorem, $\delta_p(a)\mid p-1$, so $2^{i+1}\mid p-1$. This holds for all prime factors $p$ of $n$. Therefore, $i+1\le\ell$. This shows $a^{u2^{\ell-1}} = (a^{u2^i})^{2^{\ell-1-i}} \equiv \pm 1 \pmod n$, and also $a\in S'$. Combining both possibilities gives $S\subseteq S'$.
    
    **Step Two**: Compute the size of $|S'|$.
    
    Suppose $n$ has prime factorization $n = p_1^{e_1}p_2^{e_2}\cdots p_k^{e_k}$. Then, by the [Chinese Remainder Theorem](./crt.md), the condition $a^{u2^{\ell - 1}}\equiv 1\pmod n$ is equivalent to $a^{u2^{\ell - 1}}\equiv 1\pmod{p_i^{e_i}}$ holding for all $p_i^{e_i}$. Since [primitive roots](./primitive-root.md#primitive-roots) always exist for odd prime powers $p_i^{e_i}$, the [number of solutions](./residue.md#properties) to the congruence $a^{u2^{\ell - 1}}\equiv 1\pmod{p_i^{e_i}}$ is:
    
    $$
    \gcd(u2^{\ell-1},p_i^{e_i-1}(p_i-1)) = \gcd(u2^{\ell-1},p_i-1) = 2^{\ell-1}\gcd(u,p_i-1).
    $$
    
    The first equality holds because $u$ is a factor of $n-1$ and cannot be a multiple of $p_i$; the second equality holds because of how $\ell$ is chosen. Therefore, by the Chinese Remainder Theorem, the number of solutions to $a^{u2^{\ell-1}}\equiv 1\pmod n$ is:
    
    $$
    \prod_{p\mid n}2^{\ell-1}\gcd(u,p-1).
    $$
    
    Similarly, the condition $a^{u2^{\ell - 1}}\equiv -1\pmod n$ is equivalent to $a^{u2^{\ell - 1}}\equiv -1\pmod{p_i^{e_i}}$ holding for all $p_i^{e_i}$. For any factor $p_i^{e_i}$, the condition $a^{u2^{\ell - 1}}\equiv -1\pmod{p_i^{e_i}}$ is equivalent to $a^{u2^{\ell - 1}}\not\equiv 1\pmod{p_i^{e_i}}$ and $a^{u2^{\ell}}\equiv 1\pmod{p_i^{e_i}}$ holding. Similar to above, the number of solutions to $a^{u2^{\ell}}\equiv 1\pmod{p_i^{e_i}}$ can be computed as $2^{\ell}\gcd(u,p_i-1)$, so the number of solutions to $a^{u2^{\ell - 1}}\equiv -1\pmod{p_i^{e_i}}$ is also:
    
    $$
    2^{\ell}\gcd(u,p_i-1) - 2^{\ell-1}\gcd(u,p_i-1) = 2^{\ell-1}\gcd(u,p_i-1).
    $$
    
    Applying the Chinese Remainder Theorem again, the number of solutions to $a^{u2^{\ell - 1}}\equiv -1\pmod n$ is equal to:
    
    $$
    \prod_{p\mid n}2^{\ell-1}\gcd(u,p-1).
    $$
    
    Therefore, combining both cases:
    
    $$
    |S'| = 2\prod_{p\mid n}2^{\ell-1}\gcd(u,p-1).
    $$
    
    **Step Three**: Prove $|S'|\le\varphi(n)/4$.
    
    Combined with the formula for Euler's function $\varphi(n)=\prod_ip_i^{e_i-1}(p_i-1)$:
    
    $$
    \dfrac{\varphi(n)}{|S'|} = \dfrac{1}{2}\prod_ip_i^{e_i-1}\dfrac{p_i-1}{2^{\ell-1}\gcd(u,p_i-1)}.
    $$
    
    For each $i$, the factor $p_i^{e_i-1}\dfrac{p_i-1}{2^{\ell-1}\gcd(u,p_i-1)}$ is an even number, so $\varphi(n)/|S'|$ is an integer. Assume $|S'|\le\varphi(n)/4$ does not hold. Then necessarily $\varphi(n)/|S'|=1,2,3$, i.e.:
    
    $$
    \prod_ip_i^{e_i-1}\dfrac{p_i-1}{2^{\ell-1}\gcd(u,p_i-1)} = 2,4,6.
    $$
    
    Since each factor in the product is an even number, this product either has only one factor equal to $2,4$, or has two factors both equal to $2$.
    
    First consider the case with two factors. Then both factors have no odd prime factors, so $p_i^{e_i-1}=1$, i.e., $n$ has no square factors. Let $n=p_1p_2$ with $p_1<p_2$ both prime numbers. Since both factors equal $2$, we always have $p_i-1=2^{\ell}\gcd(u,p_i-1)$. Therefore, $p_i=1+2^\ell m_i$, where $m_i$ is odd and $m_i\mid u$. Taking $p_1p_2=n=1+u2^t$ modulo $m_1$ gives $p_1p_2\equiv 1\pmod{m_1}$, so $p_2\equiv 1\pmod{m_1}$, which means $m_1\mid m_2$. The reverse also holds. This shows $m_1=m_2$, i.e., $p_1=p_2$. This contradicts $p_1<p_2$. This case does not hold.
    
    Finally, consider the case with only one factor, i.e., composite $n=p^e$ with $e>1$. At this time, we necessarily have $p^{e-1}\mid 2,4,6$. Therefore, the only case is $p=3,e=2$, i.e., $n=9$, which contradicts the assumption in the proposition. This case does not hold either.
    
    Combining all cases shows that $|S'|\le\varphi(n)/4$ holds.
    
    Combining the three steps above shows that $|S|\le |S'|\le \varphi(n)/4$ holds for all odd composite numbers $n>9$.

Additionally, assuming the [Generalized Riemann Hypothesis](https://en.wikipedia.org/wiki/Generalized_Riemann_hypothesis) (GRH) holds, then testing all integers in $[2, \min\{n-2, \lfloor 2\ln^2 n \rfloor\}]$ can **determine** the primality of $n$[^deterministic-proof].

And within the OI range, usually we test numbers in $[1, 2^{64})$. For numbers in $[1, 2^{32})$, selecting $\{2, 7, 61\}$ as bases for the Miller-Rabin primality test can determine primality; for numbers in $[1, 2^{64})$, selecting $\{2, 325, 9375, 28178, 450775, 9780504, 1795265022\}$ as bases for the Miller-Rabin primality test can determine primality[^witnesses].

We can also select $\{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37\}$ (the first $12$ prime numbers) to test primes in $[1, 2^{64})$.

Note that if we use the numbers in the above sequence as bases to judge the primality of $n$:

-   Take all numbers, not just those less than $n$;
-   Replace $a$ with $a \bmod n$;
-   If $a \equiv 0 \pmod n$ or $a \equiv \pm 1 \pmod n$, then directly pass this round of testing.

## Anti-Primes

As the name suggests, prime numbers are numbers with only two factors. Then anti-primes are numbers with the most factors (and when the number of factors is the same, the smallest value), so anti-primes are relative to a set.

An intuitive definition of anti-primes is: in a set of positive integers, the number with the most factors and the smallest value is the anti-prime.

???+ abstract "Anti-prime"
    For a positive integer $n$, if any positive integer less than $n$ has fewer divisors than $n$, then it is called an **anti-prime** (a.k.a., highly composite numbers).

???+ warning "Note"
    Note that we should distinguish from [emirp](https://en.wikipedia.org/wiki/Emirp), which represents a prime that becomes a different prime when its digits are reversed (e.g., 149 and 941 are both emirps, but 101 is not an emirp).

### Process

Then, how to solve anti-primes?

First, since we need the number of factors, the first thing to do is prime factorization. Let $n=p_{1}^{k_{1}}p_{2}^{k_{2}} \cdots p_{n}^{k_{n}}$, where $p$ is a prime and $k$ is its exponent. In this case, the total number of factors is $(k_1+1) \times (k_2+1) \times (k_3+1) \cdots \times (k_n+1)$.

But obviously the complexity of prime factorization is very high, and the result of the previous number cannot be used for the next. So we need to change the method.

Let's observe the characteristics of anti-primes.

1.  Anti-primes are definitely products of powers of consecutive primes starting from $2$.

2.  The exponent of a smaller prime is greater than or equal to the exponent of a larger prime, i.e., in $n=p_{1}^{k_{1}}p_{2}^{k_{2}} \cdots p_{n}^{k_{n}}$, we have $k_1 \geq k_2 \geq k_3 \geq \cdots \geq k_n$.

Explanation:

1.  If it is not starting from consecutive primes starting with $2$, then if the exponent remains unchanged and the prime is replaced with a smaller prime, the number of factors remains the same, but the value of $n$ becomes smaller. When switched to consecutive primes starting with $2$, the value of $n$ is minimized.

2.  If the exponent of a smaller prime is less than the exponent of a larger prime, then if these two primes are swapped (exponent unchanged), the number of factors of $n$ remains the same, but the value of $n$ becomes smaller.

There are also two more issues:

1.  For a given $n$, up to which prime should we enumerate?

    In the most extreme case, it's just $n=p_{1}p_{2} \cdots p_{n}$, so we just need to multiply consecutive primes until they are just less than or equal to $n$. If we enumerate to a larger prime, it means that the exponent of some previous prime is $0$, so it cannot become an anti-prime.

2.  To what power should we enumerate?

    We consider an extreme case: when the power of the smallest prime is already larger than the maximum given $n$, if expanded to other forms, the maximum power is definitely less than this power. In the extreme case, $n$ is decomposed into powers of $2$, so we enumerate to $\lfloor\log_2 n\rfloor$.

Now we have the details, how do we specifically implement it?

We can treat the point before each prime as the root node of a tree, then layer by layer to find. When to stop?

1.  The current number is already larger than the number we want;
2.  The currently enumerated factor is no longer needed;
3.  The current factor is larger than the factor we want;
4.  The current factor is exactly the factor we want (at this time, judge whether to update the minimum $\textit{ans}$).

Then in dfs, we can continue enumerating the power and iterate down layer by layer.

### Example Problems

???+ example "[Codeforces 27 E. A number with a given number of divisors](https://codeforces.com/problemset/problem/27/E)"
    Find the smallest natural number with a given number of divisors. The answer is guaranteed not to exceed $10^{18}$.

??? note "Solution Idea"
    For such problems, we just use the number of divisors as the return condition for dfs, and constantly update to find the smallest value.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/math/code/prime/prime_1.cpp"
    ```

???+ example "[ZOJ 2562 More Divisors](https://pintia.cn/problem-sets/91827364500/exam/problems/type/7?problemSetProblemId=91827366061)"
    Find the number with the most divisors not exceeding $n$.

??? note "Solution Idea"
    The idea is the same as above, just change the return condition of dfs. Note the data range of such problems, 32-bit integers may overflow.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/math/code/prime/prime_2.cpp"
    ```

## References and Notes

1.  Rui-Juan Jing, Marc Moreno-Maza, Delaram Talaashrafi, "[Complexity Estimates for Fourier-Motzkin Elimination](https://arxiv.org/abs/1811.01510)", Journal of Functional Programming 16:2 (2006) pp 197-217.
2.  [Number Theory Part I: Primes and Primality Tests](http://www.matrix67.com/blog/archives/234)
3.  [Miller–Rabin and Pollard–Rho Learning Notes - Bill Yang's Blog](https://blog.bill.moe/miller-rabin-notes/)
4.  [Primality test - Wikipedia](https://en.wikipedia.org/wiki/Primality_test)
5.  [Fermat pseudoprime - Wikipedia](https://en.wikipedia.org/wiki/Fermat_pseudoprime)
6.  [Peach's Algorithm Notes - Anti-Primes Explained (acm/OI)](https://zhuanlan.zhihu.com/p/41759808)
7.  [The Rabin-Miller Primality Test](http://home.sandiego.edu/~dhoffoss/teaching/cryptography/10-Rabin-Miller.pdf)
8.  [Highly composite number - Wikipedia](https://en.wikipedia.org/wiki/Highly_composite_number)

[^inf-fermat-pp]: Theorem 1 in Pomerance, Carl, John L. Selfridge, and Samuel S. Wagstaff. "The pseudoprimes to 25⋅ 10⁹." Mathematics of Computation 35, no. 151 (1980): 1003-1026 shows that for fixed bases, the composites that can pass stronger Miller-Rabin primality tests are also infinite.

[^millerrabinproof]: This conclusion and its proof refer to Crandall, Richard, and Carl Pomerance. Prime numbers: a computational perspective. New York, NY: Springer New York, 2005. Section 3.5.

[^deterministic-proof]: Bach, Eric, "[Explicit bounds for primality testing and related problems](https://doi.org/10.2307%2F2008811)", Mathematics of Computation, 55:191 (1990) pp 355–380.

[^witnesses]: More similar results can be found at [Deterministic variant of the Miller–Rabin primality test](https://miller-rabin.appspot.com/#).
