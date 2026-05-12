author: aofall, c-forrest, CoelacanthusHex, Early0v0, Enter-tainer, Great-designer, iamtwz, Marcythm, Persdre, shuzhouliu, Tiphereth-A, wsyhb, Xeonacid

## Introduction

This article discusses relevant conclusions about factorial computation under a certain modulus, and provides a method whose time complexity is linearly related to the size of the modulus. Therefore, this method is primarily applicable when the modulus is not too large ($\sim 10^6$). Besides the methods introduced in this article, according to different scenarios, [polynomial techniques](../poly/shift.md#factorials-modulo-prime-numbers) can also be applied for fast computation.

According to the [Chinese Remainder Theorem](./crt.md), the factorial modulo problem can be transformed into the case where the modulus is a prime power $p^\alpha$. When handling such problems, we often extract all factors $p$ from the factorial $n!$ to obtain the decomposition:

$$
n! = p^{\nu_p(n!)}(n!)_p.
$$

Here, $\nu_p(n!)$ represents the exponent of $p$ in the prime factorization of the factorial $n!$, and $(n!)_p$ represents the integer obtained after removing all powers of $p$ from the result of the factorial $n!$. This article will discuss the specific computation methods for the remainder $(n!)_p$ modulo a prime (power) and the exponent $\nu_p(n!)$.

This decomposition is particularly useful when factorials appear in both the numerator and denominator of the expression to be solved, such as [computing binomial coefficients modulo a certain modulus](./lucas.md). For such problems, the exponents of $p$ in the numerator and denominator can be directly subtracted, and the part $(n!)_p$ coprime with $p$ can be computed using [multiplicative inverses](./inverse.md).

This article also introduces Wilson's theorem and its generalization, Legendre's formula, and Kummer's theorem, which are related to the above problems.

## Wilson's Theorem

Wilson's theorem gives a necessary and sufficient condition to determine whether a natural number is a prime.

???+ note "Wilson's Theorem"
    For a natural number $n>1$, $n$ is a prime if and only if $(n-1)!\equiv -1\pmod n$.

??? note "Proof"
    First, prove for a prime $p$: $(p-1)!\equiv -1\pmod{p}$. For this, there are two concise proofs using either [congruence equations](./congruence-equation.md#corollary-2) or [primitive roots](./primitive-root.md), which are omitted here. A proof with fewer prerequisites is provided below:
    
    When $p=2$, the proposition obviously holds. Below, let $p\geq 3$. Then to prove that the product of all non-zero elements (i.e., congruence classes) in $\mathbf{Z}_p$ is $\overline{-1}$. Because all non-zero elements $\overline{a}$ in $\mathbf{Z}_p$ have inverses $\overline{a}^{-1}$, the product of mutually inverse elements in $\mathbf{Z}_p$ is $\overline{1}$. But note that $\overline{a}$ and $\overline{a}^{-1}$ might be equal: $\overline{a}=\overline{a}^{-1}$, which holds if and only if $a^2\equiv 1\pmod p$, i.e.,
    
    $$
    0\equiv a^2-1\equiv (a+1)(a-1),\pmod p
    $$
    
    Thus, $a\equiv 1\pmod p$ or $a\equiv -1\pmod p$. This shows that the product of all elements in $\mathbf{Z}_p\setminus\{\overline{0},\overline{1},\overline{-1}\}$ is $\overline{1}$. Furthermore, the product of all non-zero elements in $\mathbf{Z}_p$ is $\overline{-1}$.
    
    Conversely, for a composite number $n$, proving that $(n-1)!\not\equiv-1\pmod{n}$. Using proof by contradiction, suppose $(n-1)!\equiv -1\pmod{n}$, i.e., there exists an integer $k$ such that $(n-1)!=kn-1$ holds. Since $n$ is composite, there necessarily exists a prime $p<n$ such that $n=pm$, so $(n-1)!=kpm-1\equiv -1\pmod{p}$. However, $p$ necessarily appears in the product $(n-1)!$, so $(n-1)!\equiv 0\pmod{p}$. This contradiction shows that $(n-1)!\not\equiv-1\pmod{n}$.

Using the notation in this article, Wilson's theorem can be written as $(p!)_p\equiv -1\pmod{p}$.

### Generalization

Wilson's theorem can be generalized to the case of general moduli.

???+ note "Theorem (Gauss)"
    For a natural number $m>1$, we have:
    
    $$
    \prod_{1\le k<m,\ k\perp m} k \equiv \pm 1 \pmod{m}.
    $$
    
    Moreover, the $\pm 1$ in the remainder is $-1$ if and only if a [primitive root exists](./primitive-root.md#primitive-root-existence-theorem) modulo $m$, i.e., $m=2,4,p^\alpha,2p^\alpha$, where $p$ is an odd prime and $\alpha$ is a positive integer.

??? note "Proof"
    This theorem can be easily proven using the structure of the [multiplicative group of integers modulo $n$](../algebra/ring-theory.md#application-multiplicative-group-of-integer-residue-classes). The proof provided here has similar ideas but is more elementary.
    
    For $m=2$, we have $1!=1\equiv -1\pmod{2}$. For other cases where primitive roots exist, let the primitive root be $g$. Then all positive integers $k$ less than $m$ and coprime to it can be uniquely represented in the form $g^i\bmod m$, where $0\le i<\varphi(m)$ and $\varphi(m)$ is [Euler's totient function](./euler-totient.md). Direct verification shows that $\varphi(m)$ must be even. Because $g^i$ and $g^{\varphi(m)-i}$ are multiplicative inverses of each other, pairing them in the product gives:
    
    $$
    \prod_{1\le k<m,\ k\perp m} k \equiv \prod_{i=0}^{\varphi(m)-1}g^i = g^{\varphi(m)/2}\prod_{i=1}^{\varphi(m)/2-1}g^{i}g^{\varphi(m)-i} \equiv g^{\varphi(m)/2} \pmod{m}.
    $$
    
    Because $g^{\varphi(m)/2}\bmod m$ is the unique element not equal to $1\bmod{m}$ whose multiplicative inverse is itself, it equals $-1\bmod{m}$. This shows that the remainder equals $-1$ in this case.
    
    For cases where primitive roots do not exist modulo $m$, proving the remainder equals $1$. For this, first perform prime factorization $m=p_1^{e_1}p_2^{e_2}\cdots p_s^{e_s}$, then use the [Chinese Remainder Theorem](./crt.md). We only need to prove:
    
    $$
    \prod_{1\le k<m,\ k\perp m} k\equiv 1\pmod{p_j^{e_j}}
    $$
    
    holds for all factors $p_j^{e_j}$. The Chinese Remainder Theorem shows that each possible remainder combination $(r_1,r_2,\cdots,r_s)$, where $1\le r_j<p_j^{e_j}$ and $p_j\perp r_j$, uniquely corresponds to a $1\le k<m$ with $k\perp m$ such that $k\equiv r_j\pmod{p_j^{e_j}}$. Therefore, for some remainder $r_j$, there are exactly ${\varphi(m)}/{\varphi(p_j^{e_j})}$ values of $k$ such that $k\equiv r_j\pmod{p_j^{e_j}}$. Using this, we can group the product:
    
    $$
    \prod_{1\le k<m,\ k\perp m} k\equiv\left(\prod_{1\le r_j<p_j^{e_j},\ r_j\perp p_j} r_j\right)^{{\varphi(m)}/{\varphi(p_j^{e_j})}}\pmod{p_j^{e_j}}.
    $$
    
    Here, the exponent ${\varphi(m)}/{\varphi(p_j^{e_j})}=\varphi(m/p_j^{e_j})$ must be an odd number. For this to be odd, it is necessarily required that $m/p_j^{e_j}=1,2$, because Euler's function $\varphi(n)$ is even for all $n\ge 3$. If $p_j$ is an odd prime, because primitive roots do not exist modulo $m$, it necessarily follows that $m/p_j^{e_j}\neq 1,2$; if $p_j^{e_j}=2,4$, because primitive roots do not exist modulo $m$, it necessarily follows that $m/p_j^{e_j}$ contains some odd prime factor, hence greater than $2$: in both cases, the exponent ${\varphi(m)}/{\varphi(p_j^{e_j})}$ is even. And the term in brackets has been proven to be congruent to $-1$ modulo $p_j^{e_j}$. Therefore, this power is necessarily congruent to $1$ modulo $p_j^{e_j}$. The only remaining case is $p_j=2$ and $e_j>2$. For this case, it can be directly proven that:
    
    $$
    \prod_{1\le r_j<2^{e_j},\ r_j\perp 2}r_j \equiv 1\pmod{2^{e_j}}.
    $$
    
    Following the proof idea above, all odd numbers $r_j$ with $1\le r_j<2^{e_j}$ can be paired and canceled, and those that cannot be paired must satisfy the equation $x^2\equiv 1\pmod{2^{e_j}}$. This equation means $2^{e_j}\mid (x-1)(x+1)$. Let $x=2y+1$, which necessarily leads to $2^{e_j-2}\mid y(y+1)$. Since $y$ and $y+1$ are one odd and one even, we have $y=t2^{e_j-2}$ or $y=t2^{e_j-2}-1$. Thus, $x=t2^{e_j-1}\pm 1$ and $t$ is an integer. Among the remainders modulo $2^{e_j}$, only $\pm 1$ and $2^{e_j-1}\pm 1$ are four numbers. Therefore:
    
    $$
    \prod_{1\le r_j<2^{e_j},\ r_j\perp 2}r_j \equiv (-1)(2^{e_j-1}-1)(2^{e_j-1}+1) \equiv 1\pmod{2^{e_j}}.
    $$
    
    This completes the proof for all cases.

In computation, the most important case is when the modulus is a prime power:

???+ note "Corollary"
    For a prime $p$ and a positive integer $\alpha$, we have:
    
    $$
    \prod_{1\le k<p^\alpha,\ k\perp p}k \equiv 
    \begin{cases}
    1, & p=2\text{ and }\alpha\ge3,\\
    -1, &\text{otherwise}
    \end{cases}
    pmod{p^\alpha}.
    $$

Note that the left side is not $(p^\alpha!)_p$, because the latter also needs to count contributions from multiples of $p$.

## Computation of Factorial Remainders

This section discusses the computation of the remainder $(n!)_p\bmod p^{\alpha}$.

### Prime Modulus Case

The expression $(n!)_p$ has an obvious recursive structure. To notice this, first examine a specific example:

???+ example "Example"
    To compute $(32!)_5 \bmod{5}$, we can do the following recursive computation:
    
    $$
    \begin{aligned}
    (32!)_5 &= 1\times 2\times 3 \times 4\times\underbrace{1}_{5}\times 6 \times 7 \times 8\times 9 \times\underbrace{2}_{10} \\
    &\quad\times 11 \times 12 \times 13 \times 14\times\underbrace{3}_{15}\times 16 \times 17\times 18\times 19\times\underbrace{4}_{20} \\
    &\quad\times 21 \times 22 \times 23 \times 24\times\underbrace{1}_{25}\times 26 \times 27 \times 28 \times 29\times\underbrace{6}_{30} \times 31 \times 32 \\
    &\equiv 1\times 2\times 3 \times 4\times\underbrace{1}_{5}\times 1 \times 2 \times 3 \times 4 \times\underbrace{2}_{10} \\
    &\quad\times 1 \times 2 \times 3 \times 4\times\underbrace{3}_{15}\times 1 \times 2 \times 3 \times 4 \times\underbrace{4}_{20} \\
    &\quad\times 1 \times 2 \times 3 \times 4\times\underbrace{1}_{25}\times 1 \times 2 \times 3 \times 4 \times\underbrace{1}_{30}\times 1\times 2\\
    &= (1\times 2\times 3\times 4)^{6}\times(1\times 2)\times(\underbrace{1}_{5}\times\underbrace{2}_{10}\times\underbrace{3}_{15} \times \underbrace{4}_{20}\times\underbrace{1}_{25}\times\underbrace{1}_{30}) \pmod{5}
    \end{aligned}
    $$
    
    It can be seen that using the periodicity of remainders modulo $5$, this product can be divided into several blocks of length $5$, and the only difference of each block is the last element's remainder. Since the quotient obtained by dividing $32$ by $5$ is $6$ and the remainder is $2$, this product can be divided into $6$ complete blocks and the last incomplete block of length $2$. Therefore, we can extract the parts of the first $6$ blocks except the last element (this part is exactly what Wilson's theorem can solve), then multiply by the product of the last incomplete block, and finally multiply by the product of the last elements of the first $6$ blocks. The last element of each block is a multiple of $5$; after removing the powers of $5$, their product is exactly $(6!)_{5}\pmod{5}$. This transforms the original problem into a smaller one.

Generalizing the recursive structure in this example, we get the following recurrence formula:

???+ note "Recurrence Formula"
    For a prime $p$ and a positive integer $n$, we have:
    
    $$
    (n!)_p \equiv (-1)^{\left\lfloor n/p\right\rfloor}\cdot (n\bmod p)!\cdot\left(\left\lfloor n/p\right\rfloor!\right)_p\pmod{p}.
    $$

??? note "Proof"
    Let $(n)_p$ be the result of removing all powers of $p$ from the prime factorization of $n$. Then:
    
    $$
    \begin{aligned}
    (n!)_p &= \prod_{k=1}^n(k)_p = \left(\prod_{1\le k\le n,\ k\perp p}(k)_p\right)\left(\prod_{1\le k\le\lfloor n/p\rfloor}(pk)_p\right) \\
    &= \left(\prod_{i=0}^{\lfloor n/p\rfloor-1}\prod_{j=1}^{p-1}(ip+j)\right)\left(\prod_{j=1}^{n\bmod p}(\lfloor n/p\rfloor p+j)\right)\left(\prod_{1\le k\le\lfloor n/p\rfloor}(k)_p\right) \\
    &\equiv\left(\prod_{j=1}^{p-1}j\right)^{\lfloor n/p\rfloor}\left(\prod_{j=1}^{n\bmod p}j\right)(\lfloor n/p\rfloor!)_p \\
    &\equiv (-1)^{\lfloor n/p\rfloor}\cdot(n\bmod p)!\cdot(\lfloor n/p\rfloor!)_p \pmod p.
    \end{aligned}
    $$
    
    This completes the proof. A concrete explanation is provided below for this formula.
    
    To compute $(n!)_p\bmod p$. Following the example above:
    
    $$
    \begin{aligned}
    (n!)_p &= 1 \cdot 2 \cdot 3 \cdot \ldots \cdot (p-2) \cdot (p-1) \cdot \underbrace{1}_{p} \cdot (p+1) \cdot (p+2) \cdot \ldots \cdot (2p-1) \cdot \underbrace{2}_{2p} \\
    &\quad \cdot (2p+1) \cdot \ldots \cdot (p^2-1) \cdot \underbrace{1}_{p^2} \cdot (p^2 +1) \cdot \ldots \cdot n pmod{p} \\
    &= 1 \cdot 2 \cdot 3 \cdot \ldots \cdot (p-2) \cdot (p-1) \cdot \underbrace{1}_{p} \cdot 1 \cdot 2 \cdot \ldots \cdot (p-1) \cdot \underbrace{2}_{2p} \cdot 1 \cdot 2 \\
    &\quad \cdot \ldots \cdot (p-1) \cdot \underbrace{1}_{p^2} \cdot 1 \cdot 2 \cdot \ldots \cdot (n \bmod p) pmod{p}.
    \end{aligned}
    $$
    
    It can be clearly seen that, except for the last block, the factorial is divided into several complete blocks of the same length.
    
    $$
    \begin{aligned}
    (n!)_p&= \underbrace{1 \cdot 2 \cdot 3 \cdot \ldots \cdot (p-2) \cdot (p-1) \cdot 1}_{1\text{st}} \cdot \underbrace{1 \cdot 2 \cdot 3 \cdot \ldots \cdot (p-2) \cdot (p-1) \cdot 2}_{2\text{nd}} \cdot \ldots \\
    &\quad \cdot \underbrace{1 \cdot 2 \cdot 3 \cdot \ldots \cdot (p-2) \cdot (p-1) \cdot 1}_{p\text{th}} \cdot \ldots \cdot \quad \underbrace{1 \cdot 2 \cdot \cdot \ldots \cdot (n \bmod p)}_{\text{tail}} \pmod{p}.
    \end{aligned}
    $$
    
    Except for the last element of each block, the main part of the complete block $(p-1)! \mathrm{mod}\ p$ can be easily computed, and we can apply Wilson's theorem:
    
    $$
    (p-1)!\equiv -1\pmod p.
    $$
    
    There are $\left\lfloor \dfrac{n}{p} \right\rfloor$ complete blocks in total, so we need to put $\left\lfloor \dfrac{n}{p} \right\rfloor$ on the exponent of $-1$.
    
    The value of the last partial block is $(n\bmod p)!\bmod p$, which can be computed separately.
    
    What remains are the last elements of each block. Hiding the processed elements, we can see the following pattern:
    
    $$
    (n!)_p = \underbrace{ \ldots \cdot 1 } \cdot \underbrace{ \ldots \cdot 2} \cdot \ldots \cdot \underbrace{ \ldots \cdot (p-1)} \cdot \underbrace{ \ldots \cdot 1 } \cdot \underbrace{ \ldots \cdot 1} \cdot \underbrace{ \ldots \cdot 2} \cdots
    $$
    
    This is also a modified factorial, just much shorter. It is:
    
    $$
    \left(\left\lfloor \frac{n}{p} \right\rfloor !\right)_p.
    $$
    
    Multiplying all parts together gives the recurrence formula above.

Using this recurrence formula for computation, the recursion depth is $O(\log_p n)$. If we recompute the middle term each time, then each level has a complexity of $O(p)$, and the total time complexity is $O(p\log_p n)$; if we precompute $n!\bmod p$ for all $n=1,2,\cdots,p-1$, then the preprocessing complexity is $O(p)$, and each level has a complexity of $O(1)$, so the total time complexity is $O(p+\log_p n)$.

In implementation, since it is tail recursion, we can use iteration. The implementation below precomputes the first $p-1$ factorials. If the function needs to be called multiple times, the precomputation can be done outside the function.

??? example "Reference Implementation"
    ```cpp
    --8<-- "docs/math/code/factorial/fact-mod-p.cpp:core"
    ```

If space is limited and storing all factorials is not possible, we can also compute all factorials $n!\bmod p$ that are actually used in the function call, then sort them, so that we can compute these factorials at once at the end and sum them to the final result, while avoiding storing all factorials.

### Prime Power Modulus Case

For the prime power modulus case, it can be solved similar to the prime modulus case, only replacing Wilson's theorem with its generalized form. In the two conclusions in this section, $\pm 1$ specifically refers to: when the modulus $p=2$ and $\alpha\ge 3$, take $1$; in other cases, take $-1$.

???+ note "Recurrence Formula"
    For a prime $p$ and positive integers $\alpha,n$, we have:
    
    $$
    (n!)_{p} \equiv (\pm 1)^{\lfloor n/p^\alpha\rfloor}\cdot\left(\prod_{1\le j\le (n\bmod p^\alpha),\ j\perp p}j\right)\cdot(\lfloor n/p\rfloor!)_p\pmod{p^\alpha}.
    $$

    Here, the value of $\pm 1$ is as specified in the [generalization of Wilson's theorem](#generalization).

??? note "Proof"
    The proof idea is completely consistent with the prime modulus case. Let $(k)_p$ be the result of removing all powers of $p$ from the prime factorization of $k$. Then:
    
    $$
    \begin{aligned}
    (n!)_p
    &= \prod_{1\le k\le n}(k)_p = \left(\prod_{1\le k\le n,\ k\perp p}(k)_p\right)\left(\prod_{1\le k\le\lfloor n/p\rfloor}(pk)_p\right) \\
    &= \left(\prod_{i=0}^{\lfloor n/p^\alpha\rfloor-1}\prod_{1\le j\le p^\alpha,\ j\perp p}(ip^\alpha+j)_p\right)\left(\prod_{1\le j\le (n\bmod p^\alpha),\ j\perp p}(\lfloor n/p^\alpha\rfloor p^\alpha+j)_p\right)\left(\prod_{1\le k\le\lfloor n/p\rfloor}(k)_p\right)\\
    &\equiv \left(\prod_{1\le j\le p^\alpha,\ j\perp p}j\right)^{\lfloor n/p^\alpha\rfloor}\cdot\left(\prod_{1\le j\le (n\bmod p^\alpha),\ j\perp p}j\right)\cdot(\lfloor n/p\rfloor!)_p\\
    &\equiv (\pm 1)^{\lfloor n/p^\alpha\rfloor}\cdot\left(\prod_{1\le j\le (n\bmod p^\alpha),\ j\perp p}j\right)\cdot(\lfloor n/p\rfloor!)_p \pmod{p^\alpha}.
    \end{aligned}
    $$

Different from the prime modulus case, in addition to possibly replacing $-1$ with $\pm 1$, we also need to note the difference in preprocessed data. For the prime power modulus case, we need to preprocess for all positive integers $n$ not exceeding $p^\alpha$ the product of all integers from $1$ to $n$ that are not multiples of $p$, i.e.:

$$
\prod_{1\le k\le n,\ k\perp p} k\bmod{p^\alpha}.
$$

In the prime modulus case, it degenerates to $n!\bmod p$, but this expression is no longer applicable in the general prime power case.

An example of computing factorial remainders in the prime power modulus case is provided below to understand the above method:

???+ example "Example"
    To compute $(32!)_3\bmod 9$, we can do the following recursive computation:
    
    $$
    \begin{aligned}
    (32!)_3 
    &= 1\times 2\times\underbrace{1}_{3} \times 4\times 5\times\underbrace{2}_{6}\times 7\times 8\times\underbrace{1}_{9}\\
    &\quad\times 10\times 11\times\underbrace{4}_{12}\times 13\times 14\times\underbrace{5}_{15}\times 16\times 17\times\underbrace{2}_{18}\\
    &\quad\times 19\times 20\times\underbrace{7}_{21}\times 22\times 23\times\underbrace{8}_{24}\times 25\times 26\times\underbrace{1}_{27}\\
    &\quad\times 28\times 29\times\underbrace{10}_{30}\times 31\times 32\\
    &\equiv 1\times 2\times\underbrace{1}_{3} \times 4\times 5\times\underbrace{2}_{6}\times 7\times 8\times\underbrace{1}_{9}\\
    &\quad\times 1\times 2\times\underbrace{4}_{12}\times 4\times 5\times\underbrace{5}_{15}\times 7\times 8\times\underbrace{2}_{18}\\
    &\quad\times 1\times 2\times\underbrace{7}_{21}\times 4\times 5\times\underbrace{8}_{24}\times 7\times 8\times\underbrace{1}_{27}\\
    &\quad\times 1\times 2\times\underbrace{1}_{30}\times 4\times 5\\
    &=(1\times 2\times 4\times 5\times 7\times 8)^{3}\times (1\times 2\times 4\times 5)\\
    &\quad\times\begin{pmatrix}\underbrace{1}_{3}\times\underbrace{2}_{6}\times\underbrace{1}_{9}\times\underbrace{4}_{12}\times\underbrace{5}_{15}\times\underbrace{2}_{18}\\times\underbrace{7}_{21}\times\underbrace{8}_{24}\times\underbrace{1}_{27}\times\underbrace{1}_{30}\end{pmatrix}\pmod{9}.
    \end{aligned}
    $$
    
    The decomposition of $(32!)_3\bmod 9$ can also be divided into three parts:
    
    -   Complete blocks: the product of all integers between $1\sim 9$ not divisible by $3$, with a total of $\lfloor 32/9\rfloor=3$ blocks;
    -   Incomplete tail block: all integers not divisible by $3$ multiplied from $1$ to $32\bmod 9$;
    -   The product of all integers divisible by $3$, comparing with the result of the second-to-last equality sign, this is its first $\lfloor 32/3\rfloor=10$ terms, i.e., $(\lfloor 32/3\rfloor!)_3\bmod 9$.
    
    The recursive solution in the last parenthesis transforms the original problem into a smaller one.

From this, we can get the following recurrence result:

???+ note "Recurrence Result"
    For a prime $p$ and positive integers $\alpha,n$, we have:
    
    $$
    (n!)_p \equiv (\pm 1)^{\sum_{j\ge\alpha}\lfloor{n}/{p^j}\rfloor}\prod_{j\ge 0}F(\lfloor n/p^j\rfloor\bmod p^\alpha),
    $$
    
    where $F(m) = \prod_{1\le k\le m,\ k\perp p} k\bmod{p^\alpha}$ and the value of $\pm 1$ is the same as described above.

The implementation for the prime power modulus case is similar to that for the prime modulus case, with only some differences in details. Similar to above, precomputation can also be done outside the function.

??? example "Reference Implementation"
    ```cpp
    --8<-- "docs/math/code/factorial/fact-mod-pa.cpp:core"
    ```

The precomputation time complexity is $O(p^\alpha)$, and single query time complexity is $O(\log_p n)$.

## Computation of Exponents

This section discusses the computation of the exponent $\nu_p(n!)$ of $p$ in the factorial $n!$, which can be used to compute the remainder of binomial coefficients. Because both the numerator and denominator contain factorials in binomial coefficients, and whether the prime $p$ in the numerator and denominator can cancel each other becomes an important factor in determining the final remainder.

### Legendre's Formula

The exponent of prime $p$ in the factorial $n!$ can be computed by Legendre's formula, and it is related to the representation of $n$ in base $p$.

???+ note "Legendre's Formula"
    For a positive integer $n$, the exponent of prime $p$ contained in $n!$ is $\nu_p(n!)$:
    
    $$
    \nu_p(n!) = \sum_{i=1}^{\infty} \left\lfloor \dfrac{n}{p^i} \right\rfloor = \dfrac{n-S_p(n)}{p-1},
    $$
    
    where $S_p(n)$ is the sum of digits of $n$ in base $p$. In particular, the exponent of $2$ in the factorial is $\nu_2(n!)=n-S_2(n)$.

??? note "Proof"
    Because:
    
    $$
    n! = 1\times 2\times \cdots \times p\times \cdots \times 2p\times \cdots \times \lfloor n/p\rfloor p\times \cdots \times n.
    $$
    
    Among them, the product of multiples of $p$ is $p\times 2p\times \cdots \times \lfloor n/p\rfloor p=p^{\lfloor n/p\rfloor }\lfloor n/p\rfloor !$, and $\lfloor n/p\rfloor !$ may continue to have multiples of $p$. Therefore, for the exponent, there is the recurrence relation:
    
    $$
    \nu_p(n!) = \lfloor n/p\rfloor + \nu_p(\lfloor n/p\rfloor!).
    $$
    
    Expanding it gives Legendre's formula.
    
    To prove the second equality, first expand $n$ in base $p$, which is equivalent to writing it as the following sum:
    
    $$
    n = n_\ell p^{\ell} + \cdots + n_1 p + n_0 = \sum_{k=0}^\ell n_kp^k.
    $$
    
    Therefore:
    
    $$
    \begin{aligned}
    \nu_p(n!)
    &= \sum_{i=1}^{\ell}\left\lfloor\dfrac{n}{p^i}\right\rfloor 
    = \sum_{i=1}^\ell\sum_{k=i}^{\ell}n_kp^{k-i}
    = \sum_{k=1}^\ell n_k\sum_{i=1}^kp^{k-i} \\
    &= \sum_{k=1}^\ell n_k\dfrac{p^k-1}{p-1} 
    = \dfrac{\sum_{k=0}^\ell n_kp^k - \sum_{k=0}^\ell n_k}{p-1} 
    = \dfrac{n - S_p(n)}{p-1}.
    \end{aligned}
    $$

Reference implementation for computing prime exponents in factorials:

??? example "Reference Implementation"
    ```cpp
    --8<-- "docs/math/code/factorial/multiplicity.cpp:core"
    ```

It has a time complexity of $O(\log n)$.

### Kummer's Theorem

The result of a binomial coefficient modulo a number often forms a fractal structure. For example, the Sierpinski triangle can be obtained through binomial coefficients modulo $2$.

If analyzed carefully, whether $p$ divides a binomial coefficient is related to whether borrowing is needed when subtracting the upper and lower indices in base $p$. This gives **Kummer's theorem**.

???+ note "Kummer's Theorem"
    The exponent of prime $p$ in the binomial coefficient $\dbinom{m}{n}$ is exactly the number of times borrowing is needed when subtracting $n$ from $m$ in base $p$, i.e.:
    
    $$
    nu_p\left(\dbinom{m}{n}\right)=\frac{S_p(n)+S_p(m-n)-S_p(m)}{p-1}.
    $$
    
    In particular, the exponent of $2$ in the binomial coefficient is $\nu_2\left(\dbinom{m}{n}\right)=S_2(n)+S_2(m-n)-S_2(m)$.

??? note "Proof"
    First prove the expression below. For this, using Legendre's formula:
    
    $$
    \begin{aligned}
    nu_p\left(\dbinom{m}{n}\right)
    &=\nu_p(m!)-nu_p(n!)-nu_p((m-n)!)\\
    &=sum_{i=1}^\infty\left(\left\lfloor\dfrac{m}{p^i}\right\rfloor-\left\lfloor\dfrac{n}{p^i}\right\rfloor-\left\lfloor\dfrac{m-n}{p^i}\right\rfloor\right)\\
    &=\frac{S_p(n)+S_p(m-n)-S_p(m)}{p-1}.
    \end{aligned}
    $$
    
    This expression can be understood as the number of times borrowing is needed when subtracting $n$ from $m$ in base $p$. Because if there is a case where subtracting is insufficient and borrowing is needed at the $i$-th digit (the lowest digit index is $1$), then in the result of subtraction, the digit before the $i$-th digit $\left\lfloor\dfrac{m-n}{p^i}\right\rfloor$ is actually the digit before the $i$-th digit in $m$ $\left\lfloor\dfrac{m}{p^i}\right\rfloor$ minus one (i.e., the borrowed one), minus the digit before the $i$-th digit in $n$ $\left\lfloor\dfrac{n}{p^i}\right\rfloor$. So the difference:
    
    $$
    \left\lfloor\dfrac{m}{p^i}\right\rfloor-\left\lfloor\dfrac{n}{p^i}\right\rfloor-\left\lfloor\dfrac{m-n}{p^i}\right\rfloor = 1
    $$
    
    if and only if a borrowing occurs once; otherwise, the difference is $0$. Therefore, the summation in the above expression can be understood as the number of times borrowing occurs. This gives the literal statement of Kummer's theorem.

## Example Problems

???+ example "Example Problem HDU 2973 - YAPTCHA](https://acm.hdu.edu.cn/showproblem.php?pid=2973)"
    Given $n$, compute:
    
    $$
    \sum_{k=1}^n\left\lfloor\frac{(3k+6)!+1}{3k+7}-\left\lfloor\frac{(3k+6)!}{3k+7}\right\rfloor\right\rfloor
    $$

??? note "Solution Idea"
    If $3k+7$ is prime, then:
    
    $$
    (3k+6)!\equiv-1\pmod{3k+7}
    $$
    
    Let $(3k+6)!+1=k(3k+7)$
    
    Then:
    
    $$
    \left\lfloor\frac{(3k+6)!+1}{3k+7}-\left\lfloor\frac{(3k+6)!}{3k+7}\right\rfloor\right\rfloor=\left\lfloor k-\left\lfloor k-\frac{1}{3k+7}\right\rfloor\right\rfloor=1
    $$
    
    If $3k+7$ is not prime, then $(3k+7)\mid(3k+6)!$, i.e.:
    
    $$
    (3k+6)!\equiv 0\pmod{3k+7}
    $$
    
    Let $(3k+6)!=k(3k+7)$, then:
    
    $$
    \left\lfloor\frac{(3k+6)!+1}{3k+7}-\left\lfloor\frac{(3k+6)!}{3k+7}\right\rfloor\right\rfloor=\left\lfloor k+\frac{1}{3k+7}-k\right\rfloor=0
    $$
    
    Therefore:
    
    $$
    \sum_{k=1}^n\left\lfloor\frac{(3k+6)!+1}{3k+7}-\left\lfloor\frac{(3k+6)!}{3k+7}\right\rfloor\right\rfloor=\sum_{k=1}^n[3k+7\text{ is prime}]
    $$

??? example "Reference Code"
    ```cpp
    --8<-- "docs/math/code/factorial/wilson_1.cpp"
    ```

## References

-   Feng Keqin. Elementary Number Theory and Its Applications.
-   [Wilson's theorem - Wikipedia](https://en.wikipedia.org/wiki/Wilson%27s_theorem)
-   [Legendre's formula - Wikipedia](https://en.wikipedia.org/wiki/Legendre%27s_formula)

**This page is mainly translated from [Вычисление факториала по модулю](http://e-maxx.ru/algo/modular_factorial) and its English translation [Factorial modulo p](https://cp-algorithms.com/algebra/factorial-modulo.html). The Russian version is in the Public Domain + Leave a Link; the English version is in CC-BY-SA 4.0. Some content has been modified.**