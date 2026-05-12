Prerequisites: [Discrete Logarithm](./discrete-logarithm.md)

This article discusses $k$-th power residues and roots of unity modulo $m$, and presents algorithms for taking $k$-th roots modulo $m$.

## $k$-th Power Residues

The study of $k$-th power residues modulo $m$ is essentially concerned with the feasibility of taking $k$-th roots modulo $m$. It is a generalization of [quadratic residues](./quad-residue.md).

???+ abstract "$k$-th Residue"
    Let $k \ge 2$ be an integer, and let $a$ and $m$ be coprime positive integers. If there exists an integer $x$ such that
    
    $$
    x^k \equiv a \pmod m,
    $$
    
    then $a$ is called a **$k$-th residue** modulo $m$, and $x$ is a **$k$-th root** of $a$ modulo $m$. Otherwise, $a$ is called a **$k$-th nonresidue** modulo $m$.

That is, a $k$-th root of $a$ modulo $m$ exists if and only if $a$ is a $k$-th residue modulo $m$.

### Properties

Similar to quadratic residues, we can discuss the determination, number, and classification of $k$-th residues. As with other [congruence equations](./congruence-equation.md), we can use the [Chinese Remainder Theorem](./crt.md) to reduce them to the case of prime power moduli. Depending on the existence of primitive roots, this is further divided into odd prime power moduli and powers of $2$.

The case of odd prime powers is relatively simple. In fact, for all moduli where primitive roots exist, we have the following result:

???+ note "Theorem"
    Let $k \ge 2$ be an integer, and let $a$ and $m$ be coprime positive integers. Suppose a primitive root modulo $m$ exists, and let $g$ be such a primitive root. Let $d = \gcd(k, \varphi(m))$ and $d' = \dfrac{\varphi(m)}{d}$, where $\varphi(m)$ is the [Euler totient](./euler-totient.md). Then:
    
    1. $a$ is a $k$-th residue modulo $m$ if and only if
    
        $$
        a^{d'} \equiv 1 \pmod m.
        $$
    2. When $a$ is a $k$-th residue, there are exactly $d$ distinct $k$-th roots of $a$ modulo $m$ (up to congruence), and they have the form
    
        $$
        x \equiv g^{y_0 + i d'} \pmod{\varphi(m)},~0 \le y_0 < d',~i = 0,1,\cdots,d-1.
        $$
    3. The number of $k$-th residue classes modulo $m$ is $d'$, and they are precisely
    
        $$
        \{g^{d i} \bmod m : 0 \le i < d'\}.
        $$

??? note "Proof"
    Since $a \perp m$, we have $x \perp m$. Since $g$ is a primitive root modulo $m$, both $x$ and $a$ are congruent to some powers of $g$. Let $x \equiv g^y \pmod m$. The equation $x^k \equiv a \pmod m$ is equivalent to
    
    $$
    g^{k y} \equiv g^{\operatorname{ind}_g a} \pmod m,
    $$
    
    where $\operatorname{ind}_g a$ is the discrete logarithm. By the [properties of order](./primitive-root.md#幂的循环结构) and $\delta_m(g) = \varphi(m)$, this is equivalent to the linear congruence
    
    $$
    k y \equiv \operatorname{ind}_g a \pmod{\varphi(m)}.
    $$
    
    This is a [linear congruence](./linear-equation.md) in $y$. Applying the analysis of its solution structure from that page, we know the equation has a solution if and only if $d \mid \operatorname{ind}_g a$, and the general solution has the form
    
    $$
    y = y_0 + i d' \pmod{\varphi(m)},~0 \le y_0 < d',~i = 0,1,\cdots,d-1.
    $$
    
    From this, almost all of the theorem follows. The only remaining item is the criterion $a^{d'} \equiv 1 \pmod m$. By [property 3 of order](./primitive-root.md#ord-prop-3),
    
    $$
    \delta_m(a) = \delta_m(g^{\operatorname{ind}_g a}) = \dfrac{\varphi(m)}{\gcd(\varphi(m),\operatorname{ind}_g a)} = \dfrac{\varphi(m)}{\operatorname{ind}_g a}.
    $$
    
    Since the equation has a solution if and only if $d \mid \operatorname{ind}_g a$, i.e., $\delta_m(a) \mid d'$, by [property 2 of order](./primitive-root.md#ord-prop-2), this is equivalent to the criterion.

The case of powers of $2$ is special. To handle this case, we use a [result](./primitive-root.md#mod-pow-2) about the structure of the reduced residue system modulo $2^e$: every odd $a$ is uniquely congruent to some integer of the form $(-1)^s 5^r \bmod 2^e$, where $s \in \{0,1\}$ and $0 \le r < 2^{e-2}$. Using this, we obtain:

???+ note "Theorem"
    Let $k \ge 2$ be an integer, let $a$ be odd, and let $m = 2^e$ with $e \ge 2$. When $k$ is odd:
    
    1. $a$ is always a $k$-th residue modulo $m$.
    2. $a$ has exactly one $k$-th root modulo $m$.
    3. The number of $k$-th residue classes modulo $m$ is $2^{e-1}$, which are all the reduced residue classes.
    
    When $k$ is even, let $d = \gcd(k, 2^{e-2})$ and $d' = \dfrac{2^{e-2}}{d}$:
    
    1. $a$ is a $k$-th residue modulo $m$ if and only if $a \equiv 1 \pmod 4$ and $a^{d'} \equiv 1 \pmod m$.
    2. When $a$ is a $k$-th residue, there are exactly $2d$ distinct $k$-th roots of $a$ modulo $m$, and they have the form
    
        $$
        x \equiv \pm 5^{y_0 + i d'} \pmod{2^{e-1}},~0 \le y_0 < d',~i = 0,1,\cdots,d-1.
        $$
    3. The number of $k$-th residue classes modulo $m$ is $d'$, and they are precisely
    
        $$
        \{5^{d i} \bmod m : 0 \le i < d'\}.
        $$

??? note "Proof"
    Since $a \perp m$, we have $x \perp m$. Since both $x$ and $a$ are odd, by the above result, we can write $a \equiv (-1)^s 5^r \pmod{2^e}$ and $x \equiv (-1)^z 5^y \pmod{2^e}$. Because the representation is unique, the congruence $x^k \equiv a \pmod{2^e}$ is equivalent to the system of [linear congruences](./linear-equation.md)
    
    $$
    \begin{aligned}
    k z &\equiv s \pmod{2},\\
    k y &\equiv r \pmod{2^{e-2}}.
    \end{aligned}
    $$
    
    Applying the analysis of linear congruences, we obtain the solution structure of $x^k \equiv a \pmod{2^e}$. Depending on the parity of $k$, there are two cases:
    
    - When $k$ is odd, since $\gcd(k, 2) = \gcd(k, 2^{e-2}) = 1$, both linear congruences have solutions for all $s, r$. Hence the original congruence always has a solution for all odd $a$.
    - When $k$ is even, the first equation has a solution if and only if $2 \mid s$, and the second has a solution if and only if $d = \gcd(k, 2^{e-2}) \mid r$. Combining these gives the full set of $k$-th residue classes. The first condition is equivalent to $a \equiv 1 \pmod 4$; repeating the analysis for odd prime powers, the second condition is equivalent to $a^{d'} = 1$. Together, these give the criterion in the theorem. The general solutions to the two linear congruences are also known:
    
        $$
        \begin{aligned}
        z &\equiv 0, 1 \pmod 2,\\
        y &\equiv y_0 + i d' \pmod{2^{e-2}},~0 \le y_0 < 2^{e-2}.
        \end{aligned}
        $$
    
        Combining them gives the general solution to the original equation.

This completely solves the determination of $k$-th residues for different moduli. The Legendre symbol and quadratic reciprocity from quadratic residues can be generalized to $k$-th residues, but this is not easy and requires concepts like [cyclotomic fields](../algebra/field-theory.md#分圆域). In algebraic number theory, quadratic reciprocity ultimately generalizes to [Artin reciprocity](https://en.wikipedia.org/wiki/Artin_reciprocity).

## Roots of Unity

As a special case of $k$-th roots, this section discusses the concept of $k$-th (primitive) roots of unity modulo $m$. It can be seen as the analogue in the reduced residue system $\mathbb{Z}_m^*$ of the concept of $k$-th roots of unity in the complex numbers $\mathbb{C}$. When the modulus $m$ is suitable, using $k$-th primitive roots of unity modulo $m$ instead of the complex root $\omega_k$ can accelerate computations.

Similar to the complex case, we have:

???+ abstract "$k$-th Root of Unity Modulo $m$"
    For modulus $m$, a $k$-th root of $1$ is called a **$k$-th root of unity modulo $m**. In particular, if $x$ is a $k$-th root of unity modulo $$ and is not a $k'$-th root of unity for any $k' < k$, then $x$ is called a **$k$-th primitive root of unity modulo $m**.

Comparing with the [definition of primitive roots](./primitive-root.md#原根), a primitive root $g$ is a $\varphi(m)$-th primitive root of unity modulo $m$, where $\varphi(m)$ is the [Euler totient](./euler-totient.md).

When $k$-th primitive roots of unity modulo $m$ exist, their algebraic properties match those of the primitive $k$-th roots of unity $\omega_k$ in the complex numbers, and they can replace $\omega_k$ in various computations. For example, applying them to the [Fast Fourier Transform](../poly/fft.md) yields the [Number Theoretic Transform](../poly/ntt.md) over finite fields[^fnnt].

### Properties

In the complex numbers, (primitive) roots of unity exist for any order. However, this is not the case in number theory.

???+ note "Properties"
    For modulus $m$, let $\lambda(m)$ be its [Carmichael function](./primitive-root.md#carmichael-函数):
    
    1. Every integer $a$ coprime with $m$ is a $\delta_m(a)$-th primitive root of unity modulo $m$, where $\delta_m(a)$ is the [order](./primitive-root.md#阶) of $a$ modulo $m$.
    2. If $a$ is a $k$-th root of unity modulo $m$ and $k'$ is any multiple of $k$, then $a$ is also a $k'$-th root of unity modulo $m$.
    3. If $a$ is a $k$-th (primitive) root of unity modulo $m$, then $a^\ell$ is a $\dfrac{k}{\gcd(k,\ell)}$-th (primitive, respectively) root of unity modulo $m$.
    4. As $k'$ ranges over the divisors of $k$, the $k'$-th primitive roots of unity modulo $m$ form a partition of the $k$-th roots of unity. Moreover, for $\ell \perp k$, the map $x \mapsto x^\ell$ gives a bijection between $k$-th roots of unity that preserves the above partition: it maps $k'$-th primitive roots to $k'$-th primitive roots for $k' \mid k$.
    5. A $k$-th primitive root of unity modulo $m$ exists if and only if $k \mid \lambda(m)$. In particular, a $\lambda(m)$-th primitive root of unity modulo $m$ exists, called a **$\lambda$-primitive root** modulo $m$.
    6. An element $a$ is a $k$-th root of unity modulo $m$ if and only if $a^k \equiv 1 \pmod{m}$ and for every prime divisor $p \mid k$, $a^{k/p} \not\equiv 1 \pmod{m}$.

??? note "Proof"
    By the definition of order, every integer $a$ coprime with $m$ is a $\delta_m(a)$-th primitive root of unity modulo $m$. Conversely, if $a$ is a $k$-th root of unity modulo $m$, then $\gcd(a^k, m) = 1$, so $\gcd(a, m) = 1$. Hence $a$ is a (primitive) root of unity modulo $m$ if and only if $a$ is coprime to $m$. This is property 1.
    
    By direct verification of the definition, if $k \mid k'$, then $a^k \equiv 1 \pmod m$ implies $a^{k'} \equiv 1 \pmod m$, which is property 2. By [property of order](./primitive-root.md#ord-prop-3),
    
    $$
    \delta(a^\ell) = \dfrac{\delta_m(a)}{\gcd(\delta_m(a),\ell)}.
    $$
    
    If $a$ is a $k$-th primitive root of unity modulo $m$, then $\delta_m(a) = k$. Substituting gives $a^\ell$ is a $\dfrac{k}{\gcd(k,\ell)}$-th primitive root of unity. If $a$ is merely a $k$-th root of unity, let it be a $k'$-th primitive root of unity for some $k' \mid k$. Then $a^\ell$ is a $\dfrac{k'}{\gcd(k',\ell)}$-th primitive root of unity. Since $k' \mid k$,
    
    $$
    \dfrac{k'}{\gcd(k',\ell)} \mid \dfrac{k}{\gcd(k,\ell)},
    $$
    
    and by property 2, $a^\ell$ is a $\dfrac{k}{\gcd(k,\ell)}$-th root of unity. This is property 3.
    
    For $k' \mid k$, by property 2, a $k'$-th primitive root of unity modulo $m$ is necessarily a $k$-th root of unity. They are pairwise disjoint, forming a partition. For $\ell \perp k$, we always have $\ell \perp k'$, so for a $k'$-th primitive root of unity $a$ modulo $m$, $a^\ell$ is also a $k'$-th primitive root of unity. Taking $\ell' = \ell^{-1} \bmod k$, we can verify that $x \mapsto x^\ell$ and $x \mapsto x^{\ell'}$ are inverse maps, so $x \mapsto x^\ell$ is a bijection. This is property 5.
    
    By properties of the Carmichael function, a $\lambda(m)$-th primitive root of unity modulo $m$ always exists. Let it be $a$, with $\delta_m(a) = \lambda(m)$. For $k \mid \lambda(m)$, let $k' = \dfrac{\lambda(m)}{k}$. Then
    
    $$
    \delta_m(a^{k'}) = \dfrac{\lambda(m)}{(\lambda(m), k')} = \dfrac{\lambda(m)}{k'} = k.
    $$
    
    Thus $a^{k'}$ is a $k$-th primitive root of unity. And by the definition of the Carmichael function, the order of all $x \perp m$ divides $\lambda(m)$. This yields property 5.
    
    Property 6 follows by essentially repeating the proof of the [primitive root test](./primitive-root.md#原根判定定理). This criterion actually verifies $\delta_m(a) = k$.

From these properties, we can see that relative to the case where primitive roots exist, the $\lambda$-primitive root modulo $m$ plays a similar fundamental role. Unlike primitive roots, the powers of a $\lambda$-primitive root do not generate all roots of unity modulo $m$. Nevertheless, since the density of $\lambda$-primitive roots is not low[^lambda-density], if one genuinely needs to find a $k$-th primitive root, one can first find a $\lambda$-primitive root by random methods, then obtain a $k$-th primitive root by taking powers.

If one $k$-th root of $a$ modulo $m$ is known, the set of all $k$-th roots of $a$ modulo $m$ can be generated from the set of all $k$-th roots of unity modulo $m$.

???+ note "Theorem"
    Let $x$ be a $k$-th root of $a$ modulo $m$. As $r$ ranges over all $k$-th roots of unity modulo $m$, $xr$ ranges over all $k$-th roots of $a$ modulo $m$.

??? note "Proof"
    For two $k$-th roots $x, y$ of $a$ modulo $m$, let $r = x^{-1} y \bmod m$. Then $r$ satisfies $r^k \equiv 1 \pmod m$, i.e., it is a $k$-th root of unity. Conversely, if $r$ is a $k$-th root of unity modulo $m$, then $(xr)^k = x^k r^k \equiv a \pmod m$, so $xr$ is a $k$-th root.

Generating all $k$-th roots from $k$-th roots of unity is analogous to generating the general solution of an inhomogeneous linear equation from the solution of the homogeneous one.

The above discusses the general case. Only when primitive roots exist is the structure of roots of unity simpler:

???+ note "Theorem"
    For modulus $m$, suppose a primitive root modulo $m$ exists, and let $a$ be a $k$-th primitive root of unity modulo $m$. Then $b$ is a $k$-th root of unity modulo $m$ if and only if it can be expressed as a power of $a$.

??? note "Proof"
    Let $g$ be a primitive root modulo $m$. Then every element coprime to $m$ can be expressed as a power of $g$. So $a$ is a $k$-th primitive root of unity modulo $m$ if and only if
    
    $$
    \delta_m(a) = \delta_m(g^{\operatorname{ind}_g a}) = \dfrac{\varphi(m)}{\gcd(\varphi(m),\operatorname{ind}_g a)} = k.
    $$
    
    Similarly, $b$ is a $k$-th root of unity modulo $m$ if and only if
    
    $$
    \delta_m(b) = \delta_m(g^{\operatorname{ind}_g b}) = \dfrac{\varphi(m)}{\gcd(\varphi(m),\operatorname{ind}_g b)} = k' \mid k.
    $$
    
    Hence,
    
    $$
    \gcd(\varphi(m),\operatorname{ind}_g a) \mid \gcd(\varphi(m),\operatorname{ind}_g b) \mid \operatorname{ind}_g b.
    $$
    
    By the [analysis of linear congruences](./linear-equation.md), this condition is equivalent to the equation
    
    $$
    (\operatorname{ind}_g a) x \equiv \operatorname{ind}_g b \pmod{\varphi(m)}
    $$
    
    having a solution. Exponentiating this condition with base $g$ gives $a^x \equiv b \pmod m$, i.e., $b$ can be expressed as a power of $a$.

This theorem shows that when primitive roots exist, all $k$-th roots of unity form a [cyclic group](../algebra/group-theory.md#循环群), and the $k$-th primitive roots of unity are generators of this cyclic group. Later, we will see that the Tonelli-Shanks algorithm uses this to accelerate the discrete logarithm computation in root extraction.

## Computing $k$-th Roots Modulo $m$

Finally, we discuss methods for finding $k$-th roots. For $k = 2$, there are [many efficient algorithms](./quad-residue.md#模意义下开平方) for computing square roots modulo $m$. However, for general $k$, no polynomial-time algorithm is known. This section introduces two common algorithms that can find a $k$-th root in $O(m^{1/2})$ and $O(m^{1/4+\varepsilon})$ time respectively. Since the Chinese Remainder Theorem can always reduce the problem to prime power moduli, this section focuses on solving the prime power case.

### Naive Algorithm

The analysis of $k$-th residue properties above already points to a method for finding $k$-th roots modulo prime powers. Strictly speaking, the above solved the case where the radicand $a$ is coprime to the modulus $m$. The algorithm process is summarized as follows:

- When $m = p^e$ is an odd prime power, let $g$ be a primitive root modulo $m$. Then the equation $x^k \equiv a \pmod m$ can be transformed into the linear congruence
    
    $$
    k y \equiv \operatorname{ind}_g a \pmod{\varphi(m)}.
    $$
    
    Here, $\operatorname{ind}_g a$ can be found using the [BSGS algorithm](./discrete-logarithm.md#大步小步算法), and the solutions to the [linear congruence](./linear-equation.md) are easy to find. From this, we obtain all $k$-th roots $x \equiv g^y \pmod m$ of $a$.
    
    There is another similar approach. Also let $x \equiv g^y \pmod m$, but by rewriting
    
    $$
    x^k \equiv (g^k)^y \equiv a \pmod m,
    $$
    
    we transform it into finding the discrete logarithm of $a$ with base $g^k$. This can also be solved by the BSGS algorithm to find a particular solution. Its general solution can be obtained from the expression in the previous section, i.e., by multiplying the particular solution by all $k$-th roots of unity.
    
    Regardless of which approach is used, when the primitive root is known, the complexity of finding a single solution is $O(m^{1/2})$. Since a primitive root can be found in $o(m^{1/2})$ time, the overall time complexity remains $O(m^{1/2})$.

- When $m = 2^e$ with $e \in \mathbb{N}_+$, we can first find $s, r$ in $a \equiv (-1)^s 5^r \pmod m$. Among these two exponents, $s$ can be determined in $O(1)$ time:
    
    $$
    s = \begin{cases}0, & a \equiv 1 \pmod 4,\\ 1, & a \equiv 3 \pmod 4.\end{cases}
    $$
    
    And $r = \operatorname{ind}_5((-1)^s a)$ can be found using the BSGS algorithm in $O(m^{1/2})$ time. Next, we just need to solve the system of linear congruences:
    
    $$
    \begin{aligned}
    k z &\equiv s \pmod{2},\\
    k y &\equiv r \pmod{2^{e-2}}.
    \end{aligned}
    $$
    
    The general solution $(z, y)$ is easy to find, and $x = (-1)^z 5^y$ is the desired root. The complexity of finding a single solution is still $O(m^{1/2})$.

Of course, for the case of no solution, we can quickly determine this in $O(\log m)$ time using the criteria described above, without needing to determine it during the solving process.

Reference implementation for finding $k$-th roots modulo a prime (note: this is for demonstration only, as the time complexity is too high to pass):

??? example "Template Problem [Library Checker - Kth Root (Mod)](https://judge.yosupo.jp/problem/kth_root_mod) Reference Implementation"
    ```cpp
    --8<-- "docs/math/code/residue/bsgs-mod-p.cpp"
    ```

### Improved Tonelli-Shanks Algorithm

By appropriately generalizing the [Tonelli-Shanks algorithm](./quad-residue.md#tonellishanks-算法) for computing square roots modulo $m$, we can solve the root extraction problem for prime power moduli. A direct generalization is the Adleman-Manders-Miller algorithm[^amm], but its complexity is still not excellent[^amm-comp]. This section introduces the improved Tonelli-Shanks algorithm proposed by sugarknri, Min_25, 37zigen, etc. It can find a $k$-th root in $O(m^{1/4+\varepsilon})$ time.

The core idea of Tonelli-Shanks is to place the discrete logarithm computation in a group of order $2^e$, thereby reducing the time complexity. Similarly, discrete logarithms in groups of order $p^e$ (prime power) can be solved relatively efficiently, but the complexity is $\Omega(\sqrt{p})$. The Adleman-Manders-Miller algorithm breaks the $k$-th root extraction into computing discrete logarithms in several prime power order groups, but limited by the largest prime factor $p_\text{max}(k)$ of $k$, the complexity is still $\Omega(\sqrt{p_\text{max}(k)})$. This algorithm further improves on this process, avoiding computing discrete logarithms for large prime factors, thereby controlling the overall complexity at $O(m^{1/4+\varepsilon})$.

#### Process

Consider computing a $k$-th root of $a$ modulo a prime power $m$, i.e., solving:

$$
x^k \equiv a \pmod m.
$$

In particular, for $m = 2^e$, we also need to ensure $a \equiv 1 \pmod 4$, so $a$ can be written as a power of $g = 5$. Similar to the previous discussion, computing $k$-th roots modulo $2^e$ can always be reduced to this case. When handling the case of $2^e$, all $\varphi(m)$ mentioned in this section should be replaced with $\delta_m(5) = 2^{e-2}$.

First, the problem can be reduced to the case where the root order divides $\varphi(m)$. Let $d = \gcd(k, \varphi(m))$. Then, by the properties of $k$-th residues, when $a$ is a $k$-th residue modulo $m$, $a$ is always a $\dfrac{\varphi(m)}{d}$-th root of unity modulo $m$. By the properties of roots of unity, for any $\ell \perp \dfrac{\varphi(m)}{d}$, the map $x \mapsto x^\ell$ is a bijection between $\dfrac{\varphi(m)}{d}$-th roots of unity. Therefore, we can take

$$
\ell = \left(\dfrac{k}{d}\right)^{-1} \bmod \dfrac{\varphi(m)}{d}.
$$

Raising both sides of the original congruence to the $\ell$-th power gives

$$
x^d \equiv x^{k\ell} \equiv a^\ell =: b \pmod m.
$$

The left congruence uses [Euler's theorem](./fermat.md#欧拉定理) and the following congruence ($c \in \mathbb{Z}$):

$$
k\ell = d\left(\frac{k}{d}\ell\right) = d\left(c\frac{\varphi(m)}{d} + 1\right) \equiv d \pmod{\varphi(m)}.
$$

For the transformed problem, consider the prime factorization of $d$:

$$
d = \prod_{p \in \mathbb{P}} p^e.
$$

Starting from $b = a^\ell$, for each $p^e \neq 1$, we can successively take $p^e$-th roots, finally obtaining a $d$-th root of $b$, which is a $k$-th root of $a$.

Finally, the problem reduces to solving:

$$
x^{p^e} \equiv b \pmod m.
$$

Let $\varphi(m) = p^s r$ with $p \perp r$. Let $q \in \mathbb{N}_+$ be a solution to $qr \equiv -1 \pmod{p^e}$. Then, since $b$ is an $r p^{s-e}$-th root of unity, $b^{qr}$ is definitely a $p^{s-e}$-th root of unity. Let $\zeta$ be a $p^s$-th primitive root of unity modulo $m$. Then $\zeta^{p^e}$ is a $p^{s-e}$-th primitive root, so there exists $h \in \mathbb{N}$ such that $b^{qr} \equiv \zeta^{h p^e} \pmod m$. Then, direct verification shows

$$
x \equiv b^{(qr+1)/p^e} \zeta^{-h} \pmod m
$$

is a $p^e$-th root of $b$ modulo $m$.

To compute $x$, we need to find a $p$-th non-residue $\eta$ modulo $m$. By the properties above, we can randomly choose $\eta \perp m$ and verify that $\eta^{\varphi(m)/p} \bmod m \neq 1$. The density of such numbers is

$$
\frac{\varphi(m)}{m}\left(1 - \frac{1}{p}\right) \ge \frac{1}{4}.
$$

Therefore, on average, we need to try at most 4 random numbers. Note that $\eta^{r p^{s-1}} \not\equiv 1 \pmod m$ and $\eta^{r p^s} \equiv 1 \pmod m$. So if we let $\zeta = \eta^r \bmod m$ and $\xi = \eta^{r p^{s-1}} \bmod m$, they are a $p^s$-th and $p$-th primitive root of unity respectively.

Finally, we need to compute $h \in \mathbb{N}$. Obviously, we can take $h < p^{s-e}$. Consider the $p$-ary representation of $h$:

$$
h = \sum_{j=0}^{s-e-1} h_j p^j = h_0 + h_1 p + h_2 p^2 + \cdots.
$$

Compute these digits one by one. When the first $j$ digits have been computed, we must have

$$
\left(b^{qr} \zeta^{-p^e(h_0 + h_1 p + \cdots + h_{j-1} p^{j-1})}\right)^{p^{s-e-j-1}} \equiv \zeta^{h_j p^{s-1}} \equiv \xi^{h_j} \pmod m.
$$

Therefore, $h_j$ can be found by computing a discrete logarithm with respect to $\xi$. To achieve better time complexity, we use the BSGS algorithm. We need to compute $(s-e)$ discrete logarithms in total. If we preprocess $B$ powers of $\xi$, the time for a single discrete logarithm is $O(p/B)$, and the total time complexity is

$$
O\left(B + (s-e) \frac{p}{B}\right).
$$

When $B = \sqrt{(s-e)p}$, the total time complexity is $O\left(\sqrt{(s-e)p}\right)$. After obtaining $h$, substituting into the expression for $x$ gives a particular solution.

#### Time Complexity

The time complexity of this algorithm is $O(m^{1/4+\varepsilon})$. In this section, we always assume a single multiplication takes $O(1)$ time, and when computing powers, we always apply Euler's theorem for reduction, so each power computation can be done in $O(\log m)$ time.

First, consider computing a single $p^e$-th root. Finding a $p$-th non-residue only requires testing an expected $O(1)$ numbers, with total time complexity $O(\log m)$. Computing $s, r, \zeta, \eta, b^{qr}$ each takes $O(\log m)$ time. When computing $h$, each digit requires $O(\log m)$ time for power computation, and there are $(s-e)$ digits in total, so the time complexity is $O((s-e) \log m)$. As shown earlier, the total time for preprocessing and $(s-e)$ queries for discrete logarithms is $O\left(\sqrt{(s-e)p}\right)$. Since $s-e \in O(\log m)$, the time complexity for a single $p^e$-th root is $O(p^{1/2+\varepsilon})$. In particular, when $s = e$, the time complexity can be further reduced to $O(\log m)$.

Now consider the total time complexity of the algorithm. Computing $\varphi(m), d, \ell$ each takes $O(\log m)$ time. Next, we need to factor $d = \prod_p p^e$. This step can be done in $O(m^{1/4})$ time using the [Pollard Rho algorithm](./pollard-rho.md#pollard-rho-算法). Finally, the total time complexity for sequentially computing $p^e$-th roots is

$$
O\left(\sum_{e < s} p^{1/2+\varepsilon}\right).
$$

Since for any prime factor $p$ with $e < s$, $p$ appears at least twice in $\varphi(m)$, we must have $p < m^{1/2}$. Therefore, the total time complexity is $O(m^{1/4+\varepsilon})$.

In fact, in this setting, we can still achieve $O(m^{1/4+\varepsilon})$ time complexity without using Pollard Rho for factorization. In fact, we just need to naively trial-divide $d$ and only enumerate prime factors up to $m^{1/4}$. Let $z$ be the integer after removing these small prime factors. Then for any prime factor $p > m^{1/4}$ of $z$, we must have $\nu_p(\varphi(m)) < 4$, where $\nu_p(n)$ denotes the exponent of $p$ in the prime factorization of $n$. Since we only need to consider

$$
1 \le e = \nu_p(d) < s = \nu_p(\varphi(m)) < 4,
$$

there can be at most one such prime factor; otherwise, their product in $\varphi(m)$ would exceed $m$. To isolate this (possibly existing) unique large prime factor, we just need to compute

$$
p^\star = \gcd\left(z, \frac{\varphi(m)}{z}\right) = \prod_{p: \nu_p(d) < \nu_p(\varphi(m))} p^{\min\{\nu_p(d), \nu_p(\varphi(m)) - \nu_p(d)\}}.
$$

Enumerating all possibilities for $\nu_p(d), \nu_p(\varphi(m))$, the exponent of $p$ in this product is always 1, so what we compute is the unique large prime factor $p^\star$ (if it exists). As for the remaining part $z/p^\star$, since it can only contain prime factors with $e = s$, no further factorization is needed.

Reference implementation for finding $k$-th roots modulo a prime:

??? example "Template Problem [Library Checker - Kth Root (Mod)](https://judge.yosupo.jp/problem/kth_root_mod) Reference Implementation"
    ```cpp
    --8<-- "docs/math/code/residue/tonelli-shanks-mod-p.cpp"
    ```

### Handling the General Case

Consider the general case, still with modulus $m = p^e$ a prime power, but $\gcd(a, m) > 1$. If $a \equiv 0 \pmod m$, then

$$
x = p^{\lceil e/k \rceil} \ell \pmod{p^e},~\ell = 0, 1, \cdots, p^{e - \lceil e/k \rceil} - 1
$$

are all solutions to the original equation. Next, consider the case $a \not\equiv 0 \pmod m$. Let $a = p^s a'$ with $p \perp a'$. Then let $x = p^z x'$ with $p \perp x'$. We have

$$
x^k = p^{kz} (x')^k \equiv p^s a' \pmod{p^e}.
$$

Since $(x')^k \perp p$, this holds if and only if $k z = s$ and $(x')^k \equiv a' \pmod{p^{e-s}}$. The first equation has a solution $z = \dfrac{s}{k}$ if and only if $k \mid s$; the solution of the second equation has already been solved. Note that because the modulus of the general solution to the second equation differs from that of the original equation, each solution $x'$ of the second equation corresponds to several solutions of the original equation:

$$
x \equiv p^{s/k}(x' + \ell p^{e-s}) \pmod{p^e},~\ell = 0, 1, \cdots, p^{s - s/k} - 1.
$$

Reference implementation for finding all $k$-th roots for any modulus:

??? example "Template Problem [Luogu P5668 [Template] K-th Residue](https://www.luogu.com.cn/problem/P5668) Reference Implementation"
    === "Naive Algorithm"
        ```cpp
        --8<-- "docs/math/code/residue/bsgs.cpp"
        ```
    
    === "Improved Tonelli-Shanks Algorithm"
        ```cpp
        --8<-- "docs/math/code/residue/tonelli-shanks.cpp"
        ```

## References and Notes

- 冯克勤. 初等数论及其应用.
- [Root of unity modulo n - Wikipedia](https://en.wikipedia.org/wiki/Root_of_unity_modulo_n)
- [No.981 General Power Root Explanation by 37zigen](https://yukicoder.me/problems/no/981/editorial)

[^fnnt]: In fact, the modulus $m$ need not be prime. As long as $a$ is a $2^e$-th primitive root of unity modulo $m$, it can be used for the Number Theoretic Transform modulo $m$. However, since the $2^e$ that needs to be handled is usually large, this means every prime factor of $m$ is of the form $c 2^e + 1$. Thus a single prime factor is large, and $m$ is usually even larger, so the general modulus case is not as commonly used as the prime modulus case.

[^lambda-density]: From the [results on the number of primitive roots](./primitive-root.md#原根个数), the number of $\lambda$-primitive roots is exactly $\varphi(\lambda(m))$, where $\varphi(\cdot)$ and $\lambda(\cdot)$ are the Euler function and Carmichael function respectively. Since for almost all integers $m$, $\lambda(m)/m = \exp(-(1+o(1))\log\log m \log\log\log m)$, and there exists $C > 0$ such that for integers $m > 2$, $\varphi(m)/m = C / \log\log m$, for almost all integers $m$, we have $\varphi(\lambda(m))/m = \exp(-(1+o(1))\log\log m \log\log\log m)$. The $o(1)$ in the exponent absorbs the contribution from the factor $\varphi(\lambda(m))/\lambda(m)$. Therefore, a $\lambda$-primitive root can be found in expected $\exp((1+o(1))\log\log m \log\log\log m)$ attempts. For estimates of the Euler function, see Rosser, J. Barkley, and Lowell Schoenfeld. "Approximate formulas for some functions of prime numbers." Illinois Journal of Mathematics 6, no. 1 (1962): 64-94. For estimates of the Carmichael function, see Erdos, Paul, Carl Pomerance, and Eric Schmutz. "Carmichael's lambda function." Acta Arith 58, no. 4 (1991): 363-385.

[^amm]: The original paper is Adleman, Leonard, Kenneth Manders, and Gary Miller. "On taking roots in finite fields." In 18th Annual Symposium on Foundations of Computer Science (sfcs 1977), pp. 175-178. IEEE Computer Society, 1977. A more readable introduction can be found in Cao, Zhengjun, Qian Sha, and Xiao Fan. "Adleman-Manders-Miller root extraction method revisited." In International Conference on Information Security and Cryptology, pp. 77-85. Berlin, Heidelberg: Springer Berlin Heidelberg, 2011.

[^amm-comp]: Since this algorithm requires $k$ to be prime, in the worst case, we need to find a $p$-th root of $a$ modulo $m$ for the largest prime factor $p$ of $\varphi(m)$. This process requires computing discrete logarithms modulo $p$-th primitive roots of unity. Even with the BSGS algorithm, this takes $O(\sqrt{p})$ time. However, the paper Fouvry, Étienne. "Théorème de Brun-Titchmarsh; application au théorème de Fermat." Inventiones mathematicae 79, no. 2 (1985): 383-407 shows that there exists a positive density of primes $m$ such that the largest prime factor $p$ of $\varphi(m) = m-1$ is $\Omega(m^{2/3})$. This means the complexity of this algorithm is at least $\Omega(m^{1/3})$, which is worse than the improved Tonelli-Shanks algorithm presented here.