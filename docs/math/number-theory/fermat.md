author: PeterlitsZo, Tiphereth-A

This article discusses Fermat's little theorem, Euler's theorem, and their extensions. These theorems solve the problem of computing powers with arbitrary exponents under any modulus.

## Fermat's Little Theorem

**Fermat's little theorem** is one of the most fundamental theorems in number theory. It is also the theoretical basis for [Fermat primality test](./prime.md#fermat-primality-test).

???+ note "Fermat's Little Theorem"
    Let $p$ be prime. For any integer $a$ with $p\nmid a$, we have $a^{p-1}\equiv 1\pmod p$.

???+ note "Theorem"
    Let $p$ be prime. For any integer $a$, we have $a^{p}\equiv a\pmod p$.

These two congruences are equivalent when $p\nmid a$; when $p\mid a$, $a^p\equiv 0\equiv a\pmod p$ holds trivially. Therefore, these two propositions are equivalent. Both of these propositions are often called Fermat's little theorem.

??? note "Proof One"
    Let $p$ be a prime with $p\nmid a$. First prove that for $i=1,2,\cdots,p-1$, the remainders $ia \bmod p$ are all different. Proof by contradiction. If $1\le i < j < p$ such that:
    
    $$
    ia \bmod p = ja \bmod p. \iff (j-i)a\equiv 0.\pmod p
    $$
    
    However, neither $(j-i)$ nor $a$ is a multiple of $p$, which is obviously a contradiction.
    
    In other words, these remainders are a permutation of $\{1,2,\cdots,p-1\}$. Therefore:
    
    $$
    \prod_{i=1}^{p-1}i = \prod_{i=1}^{p-1}(ia\bmod p) \equiv \prod_{i=1}^{p-1}ia = a^{p-1}\prod_{i=1}^{p-1}i.\pmod p
    $$
    
    This shows that:
    
    $$
    (a^{p-1}-1)\prod_{i=1}^{p-1}i \equiv 0. \pmod{p}
    $$
    
    That is, the left side is a multiple of $p$, but $i=1,2,\cdots, p-1$ are all not multiples of $p$, so $p\mid (a^{p-1}-1)$ must hold, i.e., Fermat's little theorem holds.

??? note "Proof Two"
    Note that the second form of Fermat's little theorem holds for all $a\in\mathbf N$, so mathematical induction can be used. The case of negative integers can be easily converted to non-negative integers.
    
    The induction base is $0^p\equiv 0\pmod p$, which obviously holds. Assuming it holds for $a\in\mathbf N$, we need to prove it also holds for $a+1$. By the binomial theorem:
    
    $$
    (a+1)^p=a^p+\binom{p}{1}a^{p-1}+\binom{p}{2}a^{p-2}+\cdots +\binom{p}{p-1}a+1.
    $$
    
    Except for the first and last terms, the binomial coefficients $\dbinom{p}{k} = \dfrac{p!}{k!(p-k)!}$ have $p$ in the numerator that can divide the denominator for $k\neq 0,p$, so these coefficients are all multiples of $p$ for $k\neq 0,p$. Therefore:
    
    $$
    (a+1)^p \equiv a^p + 1\equiv a + 1. \pmod{p}
    $$
    
    Here, the second step uses the induction hypothesis. Therefore, by mathematical induction, Fermat's little theorem holds.

The converse of Fermat's little theorem does not hold. Even if $a^{n-1}\equiv 1\pmod n$ holds for all $a$ coprime to $n$, $n$ is not necessarily prime. For detailed discussion, see the section [Fermat primality test](./prime.md#fermat-primality-test).

## Euler's Theorem

**Euler's theorem** generalizes Fermat's little theorem to the case of a general modulus, but still requires the base to be coprime to the exponent.

???+ note "Euler's Theorem"
    For integer $m>0$ and integer $a$, with $\gcd(a,m)=1$, we have $a^{\varphi(m)}\equiv 1\pmod{m}$, where $\varphi(\cdot)$ is [Euler's totient function](./euler-totient.md).

??? note "Proof"
    Similar to proof one of Fermat's little theorem, we still take a sequence coprime to $m$ and operate. Consider the set:
    
    $$
    R = \{r\in\mathbf N : 0 < r < m,~\gcd(r,m)=1\}.
    $$
    
    This is the [reduced residue system](./basic.md#congruence-classes-and-residue-systems) modulo $m$. By the definition of Euler's function, $|R|=\varphi(m)$. Similar to above, multiplying them by $a$ is equivalent to rearranging this set:
    
    $$
    R = \{ar\bmod m: r\in R\}.
    $$
    
    This is because it is easy to verify $\gcd(ar,m)=1$ and for different $r_1,r_2\in R$, $ar_1\bmod m$ and $ar_2\bmod m$ are also definitely different. Therefore:
    
    $$
    \prod_{r\in R}r \equiv \prod_{r\in R}ar = a^{\varphi(m)}\prod_{r\in R}r. \pmod{m}
    $$
    
    Repeating the previous argument, canceling $\prod_{r\in R}r$, we get $a^{\varphi(m)}\equiv 1\pmod m$.

For a prime $p$, we have $\varphi(p)=p-1$, so Fermat's little theorem is a special case of Euler's theorem. Also, the exponent $\varphi(m)$ in Euler's theorem is not generally the smallest exponent making the equation hold. It can be improved to $\lambda(m)$, where $\lambda(\cdot)$ is the [Carmichael function](./primitive-root.md#carmichael-function). For the algebraic background of these conclusions, refer to the section [Multiplicative Group of Integer Residue Classes](../algebra/ring-theory.md#application-multiplicative-group-of-integer-residue-classes).

## Extended Euler's Theorem

The extended Euler's theorem[^ex-euler] further generalizes the conclusion to the case where the base and exponent are not coprime. Thus, it completely solves the problem of computing powers with arbitrary bases under any modulus, transforming them into the case where the exponent is less than $2\varphi(m)$, which can then be computed using [fast exponentiation](../binary-exponentiation.md) in $O(\log\varphi(m))$ time.

???+ note "Extended Euler's Theorem"
    For any positive integer $m$, integer $a$, and non-negative integer $k$, we have:
    
    $$
    a^k \equiv \begin{cases}
    a^{k \bmod \varphi(m)},                &\gcd(a,m) =  1,                   \\
    a^k,                                   &\gcd(a,m)\ne 1, k <   \varphi(m), \\
    a^{(k \bmod \varphi(m)) + \varphi(m)}, &\gcd(a,m)\ne 1, k \ge  \varphi(m).
    \end{cases} \pmod m
    $$

The second case is saying that if $k < \varphi(m)$, then no exponent reduction is needed, just apply fast exponentiation directly; the main difference between the first and third cases is whether we need to add $\varphi(m)$ after modular exponentiation. Of course, merging the first case into the second and third cases is also correct.

### Intuitive Understanding

Before strictly proving the theorem, we can first intuitively understand its meaning.

![fermat1](./images/fermat.svg)

Consider how the remainder $a^k\bmod m$ changes as $b$ increases. Since the remainder must be in the range $[0,m)$, and there are infinitely many values of $k$. Viewing $a^k\bmod m \mapsto a^{k+1}\bmod m$ as directed edges between these remainder nodes. They will definitely form a cycle as shown in the figure.

The extended Euler's theorem states that these cycles can be either pure cycles (first case) or mixed cycles (second and third cases). In pure cycles, no node has two predecessors, while in mixed cycles, such nodes appear. Therefore, for general cases, we just need to be able to find the length of the cycle and the length before entering the cycle to use this property for exponent reduction.

### Strict Proof

This section gives the strict proof of the extended Euler's theorem.

??? note "Proof"
    First, there exists $k_0\in\mathbf N$ such that the integer $a$ and $m':=\dfrac{m}{\gcd(a^{k_0},m)}$ are coprime. For this, let $\nu_p(n)$ be the exponent of prime $p$ in the integer $n$. We can take:
    
    $$
    k_0 = \max\left\{\left\lceil\dfrac{\nu_p(m)}{\nu_p(a)}\right\rceil : \nu_p(a)>0\right\}.
    $$
    
    Since all common prime factors of $m$ and $a$ are already contained in $a^{k_0}$, $a$ is coprime with the remaining factor $m'=\dfrac{m}{\gcd(a^{k_0},m)}$.
    
    Then, for $k\ge k_0$, consider the congruence:
    
    $$
    b\equiv a^k. \pmod m
    $$
    
    Since $\gcd(a^{k_0},m)=\gcd(a^k,m)\mid b$, divide both sides of the equation (including the modulus) by $\gcd(a^{k_0},m)$:
    
    $$
    \dfrac{b}{\gcd(a^{k_0},m)} = \dfrac{a^{k_0}}{\gcd(a^{k_0},m)}\cdot a^{k-k_0}. \pmod{m'}
    $$
    
    At this time, since $a$ is coprime with modulus $m'$, we can directly apply Euler's theorem:
    
    $$
    \dfrac{b}{\gcd(a^{k_0},m)} \equiv \dfrac{a^{k_0}}{\gcd(a^{k_0},m)}\cdot a^{(k-k_0)\bmod\varphi(m')}. \pmod{m'}
    $$
    
    Therefore, multiplying back the factor $\gcd(a^{k_0},m)$:
    
    $$
    b \equiv a^{k_0}\cdot a^{(k-k_0)\bmod\varphi(m')} = a^{k_0 + (k-k_0)\bmod\varphi(m')}. \pmod{m}
    $$
    
    This gives the form of the extended Euler's theorem. The formula shows that the length of the cycle is $\varphi(m')$, and the length before entering the cycle is $k_0$.
    
    The parameters obtained here are tighter than those in the extended Euler's theorem. However, these parameters are relatively difficult to compute. These parameters can be relaxed to the cases in the extended Euler's theorem. First, using the [formula for Euler's function](./euler-totient.md), since $m'\mid m$, we have $\varphi(m')\mid\varphi(m)$. That is, $\varphi(m)$ is also a cycle length. Also, $k_0$ can also be relaxed to $\varphi(m)$. This is because for all $m\in\mathbf N_+$ and any $p\mid m$:
    
    $$
    \begin{aligned}
    \varphi(m) &\ge \varphi(p^{\nu_p(m)}) = (p-1)p^{\nu_p(m)-1} \ge p^{\nu_p(m)-1} \\
    &= (1+(p-1))^{\nu_p(m)-1} \ge 1 + (p-1)(\nu_p(m)-1) \\
    &\ge 1 + (\nu_p(m)-1) = \nu_p(m).
    \end{aligned}
    $$
    
    Here, the inequality in the second line uses binomial expansion, keeping only the constant term and the first-order term. Therefore:
    
    $$
    k_0 \le \max\{\nu_p(m):p\in\mathbf P\}\le \varphi(m).
    $$
    
    This completely proves the stated conclusion.

## Example Problems

This section demonstrates a classic application of the extended Euler's theorem—a power tower computation under arbitrary modulus. A **power tower** (power tower) refers to an expression in the form $A\uparrow(B\uparrow(C\uparrow(D\uparrow\cdots)))$, where $\uparrow$ is Knuth's arrow notation, and $A,B,C,D,\cdots$ are a series of non-negative integers.

???+ example "[Library Checker - Tetration Mod](https://judge.yosupo.jp/problem/tetration_mod)"
    $T$ test cases. In each test case, given $A,B,M$, find $(A\uparrow\uparrow B)\bmod M$. Here $A\uparrow\uparrow B$ represents a power tower of $B$ copies of $A$. Formally, define:
    
    $$
    A \uparrow \uparrow B =
    \begin{cases}
    1 , & B = 0,\\
    A\uparrow(A\uparrow\uparrow(B-1)), & B > 0.
    \end{cases}
    $$
    
    $0^0=1$ is defined.

??? note "Solution"
    Using the definition of $A\uparrow\uparrow B$, just compute recursively. To compute $(A\uparrow\uparrow B)\bmod M$, we only need to apply the extended Euler's theorem to compute $(A\uparrow\uparrow(B-1))\bmod\varphi(M)$. Since $\varphi(\varphi(n)) \le n/2$ holds for all $n\ge 2$, the recursive process will complete within $O(\log M)$ steps. Since we need to apply the extended Euler's theorem, we need to distinguish whether the current computation result is strictly less than the current modulus. For this, we only need to add one more judgment during modular reduction. Also, note the handling of boundary cases.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/math/code/fermat/tetration.cpp"
    ```

## Practice Problems

-   [Luogu P5091 Template: Extended Euler's Theorem](https://www.luogu.com.cn/problem/P5091)
-   [Codeforces 906 D. Power Tower](https://codeforces.com/problemset/problem/906/D)
-   [Luogu P3747 [Six Provinces联考 2017] Greetings](https://www.luogu.com.cn/problem/P3747)
-   [Luogu P4139 God's Correct Use of Collection](https://www.luogu.com.cn/problem/P4139)
-   [Luogu P3934 [Ynoi Easy Round 2016] Dragon Necklace I](https://www.luogu.com.cn/problem/P3934)
-   [Luogu P6736 "Wdsr-2" Bai Ze Education](https://www.luogu.com.cn/problem/P6736)

## References and Notes

-   [Fermat's little theorem - Wikipedia](https://en.wikipedia.org/wiki/Fermat%27s_little_theorem)
-   [Euler's theorem - Wikipedia](https://en.wikipedia.org/wiki/Euler%27s_theorem)
-   Hardy, Godfrey Harold, and Edward Maitland Wright. An introduction to the theory of numbers. Oxford university press, 1979.

[^ex-euler]: This name mainly appears in competitive programming circles, not the common name for this conclusion.
