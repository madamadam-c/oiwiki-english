author: hly1204, ShaoChenHeng, Chrogeek, Enter-tainer, Great-designer, iamtwz, monkeysui, nanmenyangde, rgw2010, sshwy, StudyingFather, TachikakaMin, Tiphereth-A, Xeonacid, xyf007, marscheng1

## Introduction

Quadratic residues can be considered as discussing the feasibility of **taking square roots** modulo $m$. For higher-power roots, see [$k$-th residues](./residue.md).

## Definition

???+ abstract "Quadratic Residue"
    Let $a$ be an integer and $p$ satisfy $(a, p) = 1$. If there exists an integer $x$ such that
    
    $$
    x^2 \equiv a \pmod p,
    $$
    
    then $a$ is called a quadratic residue modulo $p$; otherwise, $a$ is called a quadratic nonresidue modulo $p$. In the following, when the modulus $p$ is clear from context, we may simply write quadratic (non)residue.

## Euler's Criterion

When the modulus is an odd prime, we have the following theorem:

???+ abstract "Euler's Criterion"
    For an odd prime $p$ and an integer $a$ satisfying $(a, p) = 1$, we have
    
    $$
    a^{\frac{p-1}{2}} \equiv \begin{cases}
        1 \pmod p, & (\exists x \in \mathbb{Z}),~~a \equiv x^2 \pmod p,\\
        -1 \pmod p, & \text{otherwise}.
    \end{cases}
    $$
    
    That is, for the above $p$ and $a$,
    
    1. $a$ is a quadratic residue modulo $p$ if and only if $a^{\frac{p-1}{2}} \equiv 1 \pmod p$.
    2. $a$ is a quadratic nonresidue modulo $p$ if and only if $a^{\frac{p-1}{2}} \equiv -1 \pmod p$.

??? note "Proof"
    First, by [Fermat's Little Theorem](./fermat.md#费马小定理), we have $a^{p-1} \equiv 1 \pmod p$, hence
    
    $$
    \left(a^{\frac{p-1}{2}} + 1\right)\left(a^{\frac{p-1}{2}} - 1\right) \equiv 0 \pmod p,
    $$
    
    so for any $a$ with $(a, p) = 1$, we have $a^{(p-1)/2} \equiv \pm 1 \pmod p$.
    
    Additionally, since $p$ is an odd prime, we have:
    
    $$
    x^{p-1} - a^{\frac{p-1}{2}} = \left(x^2\right)^{\frac{p-1}{2}} - a^{\frac{p-1}{2}} = (x^2 - a) P(x),
    $$
    
    where $P(x)$ is some polynomial with integer coefficients. Then:
    
    $$
    \begin{aligned}
        x^p - x &= x\left(x^{p-1} - a^{\frac{p-1}{2}}\right) + x\left(a^{\frac{p-1}{2}} - 1\right)\\
        &= (x^2 - a) x P(x) + \left(a^{\frac{p-1}{2}} - 1\right) x.
    \end{aligned}
    $$
    
    By [Theorem 5 of congruence equations](./congruence-equation.md#定理-5), $a$ is a quadratic residue modulo $p$ if and only if $a^{(p-1)/2} \equiv 1 \pmod p$. Therefore, $a$ is a quadratic nonresidue modulo $p$ if and only if $a^{(p-1)/2} \equiv -1 \pmod p$.

Based on Euler's Criterion, we can obtain the following corollary:

???+ note "Number of Quadratic Residues"
    For an odd prime $p$, there are exactly $\dfrac{p-1}{2}$ quadratic residues and $\dfrac{p-1}{2}$ quadratic nonresidues modulo $p$.

??? note "Proof"
    By Euler's Criterion, consider $a^{\frac{p-1}{2}} \equiv 1 \pmod p$.
    
    Note that $\dfrac{p-1}{2} \mid (p-1)$. By [Theorem 6 of congruence equations](./congruence-equation.md#定理-6), the equation $a^{\frac{p-1}{2}} \equiv 1 \pmod p$ has $\dfrac{p-1}{2}$ solutions. Therefore, there are exactly $\dfrac{p-1}{2}$ quadratic residues and $\dfrac{p-1}{2}$ quadratic nonresidues modulo $p$.

## Legendre Symbol

To facilitate the subsequent discussion, we introduce the following notation:

???+ abstract "Legendre Symbol"
    For an **odd prime** $p$ and an integer $a$, define the Legendre symbol as follows:
    
    $$
    \left(\frac{a}{p}\right) = \begin{cases}
        0, & p \mid a,\\
        1, & (p \nmid a) \land ((\exists x \in \mathbb{Z}),~~a \equiv x^2 \pmod p),\\
        -1, & \text{otherwise}.
    \end{cases}
    $$
    
    That is, for $a$ with $(a, p) = 1$:
    
    - $a$ is a quadratic residue modulo $p$ if and only if $\left(\dfrac{a}{p}\right) = 1$.
    - $a$ is a quadratic nonresidue modulo $p$ if and only if $\left(\dfrac{a}{p}\right) = -1$.

The following table shows some values of the Legendre symbol (From [Wikipedia](https://en.wikipedia.org/wiki/Legendre_symbol#Table_of_values))

![](./images/quad_residue.png)

### Properties

1. For any integer $a$,
    
    $$
    a^{\frac{p-1}{2}} \equiv \left(\frac{a}{p}\right) \pmod p.
    $$
    
    Furthermore, we have the following corollaries:
    
    - $$
        \left(\frac{1}{p}\right) = 1.
        $$
    - $$
        \left(\frac{-1}{p}\right) = (-1)^{\frac{p-1}{2}} = \begin{cases}
            1, & p \equiv 1 \pmod 4,\\
            -1, & p \equiv 3 \pmod 4.
        \end{cases}
        $$

2. $a_1 \equiv a_2 \pmod p \implies \left(\dfrac{a_1}{p}\right) = \left(\dfrac{a_2}{p}\right)$.

3. ([Complete multiplicativity](./basic.md#积性函数)) For any integers $a_1, a_2$,
    
    $$
    \left(\frac{a_1 a_2}{p}\right) = \left(\frac{a_1}{p}\right) \left(\frac{a_2}{p}\right).
    $$
    
    We have the corollary: for integers $a, b$ with $p \nmid b$,
    
    $$
    \left(\frac{a b^2}{p}\right) = \left(\frac{a}{p}\right).
    $$

4. $$
    \left(\frac{2}{p}\right) = (-1)^{\frac{p^2-1}{8}} = \begin{cases}
            1, & p \equiv \pm 1 \pmod 8,\\
            -1, & p \equiv \pm 3 \pmod 8.
        \end{cases}
    $$

??? note "Proof"
    1. This follows directly from the [definition of Legendre symbol](#legendre-符号) and [Euler's criterion](#euler-判别法).
    2. Note that
    
        $$
        a_1 \equiv a_2 \pmod p \implies \left(\frac{a_1}{p}\right) \equiv \left(\frac{a_2}{p}\right) \pmod p,
        $$
        
        and $\left|\left(\dfrac{a_1}{p}\right) - \left(\dfrac{a_2}{p}\right)\right| \leq 2$ with $p > 2$. Therefore,
    
        $$
        a_1 \equiv a_2 \pmod p \implies \left(\frac{a_1}{p}\right) = \left(\frac{a_2}{p}\right).
        $$
    3. From 1,
    
        $$
        \left(\frac{a_1 a_2}{p}\right) \equiv a_1^{\frac{p-1}{2}} a_2^{\frac{p-1}{2}} \equiv \left(\frac{a_1}{p}\right) \left(\frac{a_2}{p}\right) \pmod p.
        $$
        
        And $\left|\left(\dfrac{a_1 a_2}{p}\right) - \left(\dfrac{a_1}{p}\right)\left(\dfrac{a_2}{p}\right)\right| \leq 2$ with $p > 2$, so
    
        $$
        \left(\frac{a_1 a_2}{p}\right) = \left(\frac{a_1}{p}\right) \left(\frac{a_2}{p}\right).
        $$
    4. See [Quadratic reciprocity](#二次互反律).

Based on the above properties, if for any odd prime $p$ and $q$, the value of $\left(\dfrac{p}{q}\right)$ can be computed, then we can compute the Legendre symbol for any valid case. We now have a beautiful theorem that cleverly establishes a connection between $\left(\dfrac{p}{q}\right)$ and $\left(\dfrac{q}{p}\right)$, allowing us to compute it using an approach similar to the [Euclidean algorithm](./gcd.md#欧几里得算法).

### Quadratic Reciprocity

???+ note "Quadratic Reciprocity"
    Let $p$ and $q$ be two distinct odd primes. Then
    
    $$
    \left(\frac{p}{q}\right) \left(\frac{q}{p}\right) = (-1)^{\frac{p-1}{2} \frac{q-1}{2}}.
    $$

There are many ways to prove this[^ref5]. One proof method is based on the following lemma[^ref6]:

???+ note "Gauss's Lemma"
    Let $p$ be an odd prime and $(n, p) = 1$. For an integer $k$ with $1 \leq k \leq (p-1)/2$, let $r_k = nk \bmod p$. Let $A = \{r_k : r_k < p/2\}$ and $B = \{r_k : r_k > p/2\}$. Then
    
    $$
    \left(\frac{n}{p}\right) = (-1)^{|B|}.
    $$

??? note "Proof"
    Let $\lambda = |A|$ and $\mu = |B|$. Clearly, $\lambda + \mu = (p-1)/2$. Then
    
    $$
    n^{\frac{p-1}{2}} \left(\frac{p-1}{2}\right)! = \prod_{k=1}^{\frac{p-1}{2}} nk \equiv \prod_{a \in A} a \prod_{b \in B} b \pmod{p}.
    $$
    
    We know that for any element $b \in B$, we have $\dfrac{p}{2} < b < p$, so $0 < p - b < \dfrac{p}{2}$. Furthermore, for any $b \in B$, we have $p - b \notin A$. Otherwise, if there exist $a \in A$ and $b \in B$ such that $a = p - b$, then there exist integers $0 < k_1, k_2 < (p-1)/2$ such that $a = n k_1$, $b = n k_2$, and $p \mid n(k_1 + k_2)$. Since $(n, p) = 1$, we have $p \mid (k_1 + k_2)$. But $0 < k_1 + k_2 < p$, a contradiction. Therefore,
    
    $$
    n^{\frac{p-1}{2}} \left(\frac{p-1}{2}\right)! \equiv (-1)^{\mu} \prod_{a \in A} a \prod_{b \in B} (p - b) = (-1)^{\mu} \left(\frac{p-1}{2}\right)! \pmod{p},
    $$
    
    i.e.,
    
    $$
    n^{\frac{p-1}{2}} \equiv (-1)^{\mu} \pmod{p}.
    $$
    
    Then by [property 1 of Legendre symbol](#性质), the lemma is proved.

??? tip "Generalization"
    Gauss's Lemma can be generalized as follows[^ref7]:
    
    Let $p$ be an odd prime, and let $I \subset \mathbb{Z}_p^*$ satisfy $I \cup -I = \mathbb{Z}_p^*$ and $I \cap -I = \varnothing$, where $-I := \{-i : i \in I\}$. Then for any integer $n$ coprime to $p$,
    
    $$
    \left(\frac{n}{p}\right) = (-1)^{|J|},
    $$
    
    where $J = \{j \in I : n j \in -I\}$.
    
    It is easy to see that taking $I = \{1, 2, \dots, (p-1)/2\}$ gives Gauss's Lemma. The proof method is essentially the same as that of Gauss's Lemma, so it is omitted.

The following corollaries are easily obtained:

???+ note "Corollary"
    For an odd prime $p$,
    
    $$
    \left(\frac{2}{p}\right) = (-1)^{\frac{p^2-1}{8}} = \begin{cases}
            1, & p \equiv \pm 1 \pmod 8,\\
            -1, & p \equiv \pm 3 \pmod 8.
        \end{cases}
    $$
    
    For an odd prime $p$ and odd integer $n$ with $(n, p) = 1$,
    
    $$
    \left(\frac{n}{p}\right) = (-1)^{\sum_{i=1}^{(p-1)/2} \lfloor n i / p \rfloor}.
    $$

??? note "Proof"
    For $n, k, r_k, A, B, \lambda, \mu$ in Gauss's lemma, we have $n k = p \lfloor nk/p \rfloor + r_k$. Hence
    
    $$
    \begin{aligned}
        n \cdot \frac{p^2 - 1}{8} = \sum_{k=1}^{\frac{p-1}{2}} nk &= p \sum_{k=1}^{\frac{p-1}{2}} \left\lfloor \frac{nk}{p} \right\rfloor + \sum_{a \in A} a + \sum_{b \in B} b\\
        &= p \sum_{k=1}^{\frac{p-1}{2}} \left\lfloor \frac{nk}{p} \right\rfloor + \sum_{a \in A} a + \sum_{b \in B} (p - b) + 2 \sum_{b \in B} b - p \mu\\
        &= p \sum_{k=1}^{\frac{p-1}{2}} \left\lfloor \frac{nk}{p} \right\rfloor + \sum_{k=1}^{\frac{p-1}{2}} k + 2 \sum_{b \in B} b - p \mu\\
        &= p \sum_{k=1}^{\frac{p-1}{2}} \left\lfloor \frac{nk}{p} \right\rfloor + \frac{p^2 - 1}{8} + 2 \sum_{b \in B} b - p \mu,
    \end{aligned}
    $$
    
    therefore
    
    $$
    (n - 1) \frac{p^2 - 1}{8} = p \sum_{k=1}^{\frac{p-1}{2}} \left\lfloor \frac{nk}{p} \right\rfloor + 2 \sum_{b \in B} b - p \mu.
    $$
    
    If $n = 2$, then $0 < \dfrac{nk}{p} \leq \dfrac{p-1}{p} < 1$, thus
    
    $$
    \frac{p^2 - 1}{8} \equiv \mu \pmod{2}.
    $$
    
    If $2 \nmid n$, then
    
    $$
    \sum_{k=1}^{\frac{p-1}{2}} \left\lfloor \frac{nk}{p} \right\rfloor \equiv \mu \pmod{2}.
    $$

To prove quadratic reciprocity, it suffices to verify that

$$
\frac{p-1}{2} \frac{q-1}{2} = \sum_{k=1}^{\frac{p-1}{2}} \left\lfloor \frac{qk}{p} \right\rfloor + \sum_{k=1}^{\frac{q-1}{2}} \left\lfloor \frac{pk}{q} \right\rfloor.
$$

Consider the set $S$ of points $(p x, q y)$ with $1 \leq x \leq \dfrac{q-1}{2}$ and $1 \leq y \leq \dfrac{p-1}{2}$. Divide it into two parts according to the comparison of $p x$ and $q y$ (clearly $p x \neq q y$), and verify the sizes of the three sets.

Quadratic reciprocity can not only be used to determine whether a number $n$ is a quadratic residue modulo $p$, but also to determine the structure of moduli for which a given number $n$ is a quadratic residue.

???+ example "Example"
    - Odd primes $p$ for which $5$ is a quadratic residue satisfy $p \equiv \pm 1 \pmod 5$.
    - Odd primes $p$ for which $-3$ is a quadratic residue satisfy $p \equiv 1 \pmod 3$.
    - Odd primes $p$ for which $-2$ and $3$ are simultaneously quadratic residues satisfy $p \equiv 11 \pmod{24}$.

Furthermore, we can prove statements such as "there are infinitely many primes of the form $4k + 1$". Such statements are actually simple corollaries of [Dirichlet's theorem](https://en.wikipedia.org/wiki/Dirichlet%27s_theorem_on_arithmetic_progressions).

## Jacobi Symbol

Based on quadratic reciprocity, we can naturally think of a way to generalize the Legendre symbol:

???+ abstract "Jacobi Symbol"
    For a **positive odd integer** $m = p_1^{\alpha_1} \dots p_k^{\alpha_k}$ and an integer $a$, where $p_1, \dots, p_k$ are primes and $\alpha_1, \dots, \alpha_k$ are positive integers, define the Jacobi symbol as:
    
    $$
    \left(\frac{a}{m}\right) := \prod_{i=1}^k \left(\frac{a}{p_i}\right)^{\alpha_i}.
    $$
    
    Here, $\left(\frac{a}{p_i}\right)$ on the right-hand side is the [Legendre symbol](#legendre-符号). Additionally, for an integer $a$, we have $\left(\dfrac{a}{1}\right) = 1$.

???+ warning "Warning"
    We generally do not distinguish between the Legendre symbol and Jacobi symbol, because by complete multiplicativity, the Jacobi symbol has the same properties as the Legendre symbol, so the calculation methods for both symbols are consistent. However, one point needs attention: when $m$ **is not an odd prime**, the value of $\left(\dfrac{a}{m}\right$ is **not related to** whether $a$ is a quadratic residue modulo $m$. But if $\left(\dfrac{a}{m}\right) = -1$, then there exists at least one (actually an odd number of) prime factor $p$ of $m$ such that $a$ is a quadratic nonresidue modulo $p$. Thus in this case, $a$ is a quadratic nonresidue modulo $m$.

We can further generalize the modulus to **integers** (only need to add the definitions of $\left(\dfrac{a}{-1}\right)$, $\left(\dfrac{a}{0}\right)$ and $\left(\dfrac{a}{2}\right)$), which gives the [Kronecker symbol](https://en.wikipedia.org/wiki/Kronecker_symbol).

## Computing Square Roots Modulo $m$

This section discusses algorithms for computing square roots modulo $m$. In particular, this section mainly introduces the case of prime modulus. For general moduli, refer to the discussion on [taking higher roots modulo $m$](./residue.md#模意义下开方).

### Algorithms for Special Cases

For the congruence equation $x^2 \equiv a \pmod p$, where $p$ is an odd prime and $a$ is a quadratic residue, there is a simpler solution when $p \bmod 4 = 3$. Consider

$$
\begin{aligned}
\left(a^{(p+1)/4}\right)^2 &\equiv a^{(p+1)/2} &\pmod p\\
&\equiv x^{p+1} &\pmod p\\
&\equiv \left(x^2\right)\left(x^{p-1}\right) &\pmod p\\
&\equiv x^2 &\pmod p &\quad (\because{\text{Fermat's little theorem}})
\end{aligned}
$$

Thus $a^{(p+1)/4} \bmod p$ is a solution.

#### Atkin's Algorithm

Still consider the above congruence equation, this time with $p \bmod 8 = 5$. Let $b \equiv (2a)^{(p-5)/8} \pmod p$ and $\mathrm{i} \equiv 2a b^2 \pmod p$. Then $\mathrm{i}^2 \equiv -1 \pmod p$, and $ab(\mathrm{i} - 1) \bmod p$ is a solution.

???+ note "Proof"
    $$
    \begin{aligned}
    \mathrm{i}^2 &\equiv \left(2ab^2\right)^2 &\pmod p\\
    &\equiv \left(2a \cdot \left(2a\right)^{(p-5)/4}\right)^2 &\pmod p\\
    &\equiv \left(\left(2a\right)^{(p-1)/4}\right)^2 &\pmod p\\
    &\equiv \left(2a\right)^{\frac{p-1}{2}} &\pmod p\\
    &\equiv -1 &\pmod p
    \end{aligned}
    $$
    
    Then
    
    $$
    \begin{aligned}
    \left(ab(\mathrm{i} - 1)\right)^2 &\equiv a^2 \cdot \left(2a\right)^{(p-5)/4} \cdot (-2\mathrm{i}) &\pmod p\\
    &\equiv a \cdot (-\mathrm{i}) \cdot \left(2a\right)^{(p-1)/4} &\pmod p\\
    &\equiv a &\pmod p
    \end{aligned}
    $$

### Cipolla's Algorithm

Cipolla's algorithm is used to solve the congruence equation $y^2 \equiv a \pmod p$, where $p$ is an odd prime and $a$ is a quadratic residue.

This section considers operations in $\mathbf{F}_p[x] / (x^2 - g)$, where $g \in \mathbf{F}_p$.

??? note "Computation Method"
    Readers unfamiliar with [polynomial rings](../algebra/ring-theory.md#多项式环) can simply understand that elements in this set have the form $a_0 + a_1 x$ with $a_0, a_1 \in \mathbf{F}_p$, and follow these arithmetic rules:
    
    $$
    \begin{aligned}
    (a_0 + a_1x) + (b_0 + b_1x) &\equiv (a_0 + b_0) + (a_1 + b_1)x &\pmod{(x^2 - g)}\\
    (a_0 + a_1x)(b_0 + b_1x) &\equiv (a_0 b_0 + a_1 b_1 g) + (a_1 b_0 + a_0 b_1)x &\pmod{(x^2 - g)}
    \end{aligned}
    $$
    
    Note that here $x$ is not a specific number but a formal symbol in the polynomial. A key point in the arithmetic is to use $x^2 \equiv g \pmod{(x^2 - g)}$ to convert quadratic terms into linear terms and constant terms. Additionally, all integer arithmetic should be taken modulo $p$.
    
    For more about this structure, see [Polynomials](../poly/intro.md) and [Field Theory](../algebra/field-theory.md).

The first step of this algorithm is to find an $r$ such that $r^2 - a$ is a quadratic nonresidue. Of course, for $a \equiv 0 \pmod p$, it is impossible to find such $r$, and special handling is needed. Below we only discuss the case $a \not\equiv 0 \pmod p$. In this case, we can randomly pick an $r$ and check, which is expected to succeed in 2 steps. Then $(r - x)^{\frac{p+1}{2}} \bmod (x^2 - (r^2 - a))$ is a solution, which can be evaluated using fast exponentiation.

??? note "Why only 2 steps are expected"
    Consider the case where $r^2 - a$ is a quadratic residue. Then there exists an $x$ such that $r^2 - a \equiv x^2 \pmod p$. Rearranging gives $(r + x)(r - x) \equiv a \pmod p$. It is easy to see that each $(r + x) \in [1, p-1]$ corresponds one-to-one with a solution pair $(r, x)$. Thus there are $p - 1$ sets of solutions in total. We discuss two cases: $x \equiv 0$ and $x \not\equiv 0$. For $x \equiv 0$, since $a$ is a quadratic residue, there are 2 possible values of $r$. For $x \not\equiv 0$, there are $p - 1 - 2$ cases, each $r$ corresponds to 2 of them, giving $\dfrac{p-3}{2}$ possible values of $r$. In total, there are $2 + \dfrac{p-3}{2} = \dfrac{p+1}{2}$ cases where $r^2 - a$ is a quadratic residue. Therefore, the probability of obtaining a quadratic nonresidue with each random trial is $\dfrac{p-1}{2p}$, and the expected number of trials is $\dfrac{2p}{p-1} \approx 2$.

???+ note "Proof"
    For convenience, first let $f(x) = x^2 - (r^2 - a) \in \mathbf{F}_p[x]$.
    
    What needs to be proven is that $(r - x)^{\frac{p+1}{2}} \bmod f(x)$ is a solution to the original equation, and it belongs to $\mathbf{F}_p$. First, consider proving the former, i.e., proving $(r - x)^{p+1} \equiv a \pmod{f(x)}$. For this, we need to prove two lemmas first:
    
    **Lemma 1:** $x^p \equiv -x \pmod{f(x)}$
    
    Proof:
    
    $$
    \begin{aligned}
    x^p &= x(x^2)^{\frac{p-1}{2}}\\
    &\equiv x(r^2 - a)^{\frac{p-1}{2}} &\pmod{f(x)} &\quad (\because{x^2 \equiv r^2 - a \pmod{f(x)}})\\
    &\equiv -x &\pmod{f(x)} &\quad (\because{r^2 - a \text{ is quadratic non-residue}})
    \end{aligned}
    $$
    
    **Lemma 2:** $(a + b)^p \equiv a^p + b^p \pmod p$
    
    Using the binomial theorem, it is easy to find that except for the first and last terms, the $p$ in the numerator cannot be cancelled, leaving only $a^p + b^p$.
    
    $$
    \begin{aligned}
    (a + b)^p &= \sum_{i=0}^p \binom{p}{i} a^i b^{p-i}\\
    &= \sum_{i=0}^p \frac{p!}{i!(p-i)!} a^i b^{p-i}\\
    &\equiv a^p + b^p \pmod p
    \end{aligned}
    $$
    
    Now, let's prove the original equation:
    
    $$
    \begin{aligned}
    (r - x)^{p+1}
    &= (r - x)^p (r - x)\\
    &\equiv (r^p - x^p)(r - x) &\pmod{f(x)}\\
    &\equiv (r + x)(r - x) &\pmod{f(x)}\\
    &= r^2 - x^2\\
    &\equiv r^2 - (r^2 - a) &\pmod{f(x)}\\
    &= a.
    \end{aligned}
    $$
    
    Next, we prove by contradiction that the solution we found belongs to $\mathbf{F}_p$, i.e., the coefficient of $x$ is $0$.
    
    Assume there exists $(a_0 + a_1 x)^2 \equiv a \pmod{f(x)}$ satisfying $a_1 \not\equiv 0 \pmod p$. That is, $a_0^2 + 2 a_0 a_1 x + a_1^2 x^2 \equiv a \pmod{f(x)}$. Rearranging and simplifying gives:
    
    $$
    a_0^2 + a_1^2 (r^2 - a) - a \equiv -2 a_0 a_1 x \pmod{f(x)}.
    $$
    
    The left side has coefficient $0$ for $x$, so the right side must also have coefficient $0$ for $x$, i.e., $a_0 a_1 \equiv 0 \pmod p$. Since we set $a_1 \not\equiv 0 \pmod p$, we must have $a_0 \equiv 0 \pmod p$. Then $(a_1 x)^2 \equiv a \pmod{f(x)}$, i.e., $r^2 - a \equiv a a_1^{-2} \pmod p$.
    
    Since both $a$ and $a_1^{-2}$ are quadratic residues, by the multiplicativity of the Legendre symbol, $a a_1^{-2}$ is also a quadratic residue. This contradicts that $r^2 - a$ is a quadratic nonresidue. Therefore, there is no solution with nonzero coefficient of $x$, and the coefficient of $x$ in our solution must also be $0$.

??? example "Template Problem [Luogu P5491 [Template] Quadratic Residue](https://www.luogu.com.cn/problem/P5491)"
    ```cpp
    --8<-- "docs/math/code/quad-residue/quad-residue_1.cpp"
    ```

### Bostan-Mori Algorithm

This algorithm is based on Cipolla's algorithm. We transform the problem into a [linear recurrence with constant coefficients](../poly/linear-recurrence.md) and then apply the Bostan-Mori algorithm. Consider another common description of Cipolla's algorithm: $b = x^{\left(p+1\right)/2} \bmod{\left(x^2 - t x + a\right)}$ is a solution satisfying $b^2 \equiv a \pmod{p}$[^ref3], where $x^2 - t x + a \in \mathbf{F}_p[x]$ is an irreducible polynomial. The coefficient $t$ is also selected randomly. The proof process is omitted. Referring to the algorithm in Bostan and Mori's paper[^ref4], we can transform the problem into finding a certain coefficient of the multiplicative inverse of a formal power series:

$$
b = \left\lbrack x^{(p+1)/2} \right\rbrack \frac{1}{1 - t x + a x^2}
$$

And

$$
\left\lbrack x^n \right\rbrack \frac{k_0 + k_1 x}{1 + k_2 x + k_3 x^2} =
\begin{cases}
\left\lbrack x^{(n-1)/2} \right\rbrack \frac{k_1 - k_0 k_2 + k_1 k_3 x}{1 + (2k_3 - k_2^2)x + k_3^2 x^2}, & \text{if } n \bmod 2 = 1\\
\left\lbrack x^{n/2} \right\rbrack \frac{k_0 + (k_0 k_3 - k_1 k_2)x}{1 + (2k_3 - k_2^2)x + k_3^2 x^2}, & \text{else if } n \neq 0
\end{cases}
$$

And for $n = 0$, we clearly have $\left\lbrack x^0 \right\rbrack \frac{k_0 + k_1 x}{1 + k_2 x + k_3 x^2} = k_0$. This algorithm requires fewer multiplications than Cipolla's algorithm. Other algorithms with fewer multiplications can be found in Müller's paper[^ref2].

### Legendre's Algorithm

For the congruence equation $x^2 \equiv a \pmod p$, where $p$ is an odd prime and $a$ is a quadratic residue. Legendre's algorithm can be described as: find $r$ such that $r^2 - a$ is a quadratic nonresidue. Let $a_0 + a_1 x = (r - x)^{\frac{p-1}{2}} \bmod (x^2 - a)$. Then $a_0 \equiv 0 \pmod p$ and $a_1^{-2} \equiv a \pmod p$.

???+ note "Proof"
    Consider choosing $b$ such that $b^2 \equiv a \pmod p$. Then $(r - b)(r + b) = r^2 - a$ is a quadratic nonresidue, so
    
    $$
    (r - b)^{\frac{p-1}{2}} (r + b)^{\frac{p-1}{2}} \equiv -1 \pmod p.
    $$
    
    There exists a ring homomorphism
    
    $$
    \begin{aligned}
    \phi: \mathbf{F}_p[x]/(x^2 - a) &\to \mathbf{F}_p \times \mathbf{F}_p\\
    x &\mapsto (b, -b).
    \end{aligned}
    $$
    
    Then
    
    $$
    \begin{aligned}
    (a_0 + a_1 b, a_0 - a_1 b) &= \phi(a_0 + a_1 x)\\
    &= \phi(r - x)^{\frac{p-1}{2}}\\
    &= ((r - b)^{\frac{p-1}{2}}, (r + b)^{\frac{p-1}{2}})\\
    &= (\pm 1, \mp 1).
    \end{aligned}
    $$
    
    Thus $2 a_0 = (\pm 1) + (\mp 1) = 0$, while $2 a_1 b = (\pm 1) - (\mp 1) = \pm 2$.

### Tonelli-Shanks Algorithm

The Tonelli-Shanks algorithm is an algorithm for solving the congruence equation $x^2 \equiv a \pmod p$ based on discrete logarithms[^ref1], where $p$ is an odd prime and $a$ is a quadratic residue modulo $p$.

Let $p - 1 = m 2^n$, where $m$ is odd. Still use a random method to find $r \in \mathbf{F}_p$ such that $r$ is a quadratic nonresidue. Let $g \equiv r^m \pmod p$ and $b \equiv a^{(m-1)/2} \pmod p$. Then there exists an integer $e \in \{0, 1, 2, \dots, 2^n - 1\}$ such that $a b^2 \equiv g^e \pmod p$. If $a$ is a quadratic residue, then $e$ is even and $\left(a b g^{-e/2}\right)^2 \equiv a \pmod p$.

???+ note "Proof"
    By Fermat's Little Theorem,
    
    $$
    g^{2^n} \equiv r^{m 2^n} = r^{p-1} \equiv 1 \pmod p.
    $$
    
    Also, since $r$ is a quadratic nonresidue,
    
    $$
    g^{2^{n-1}} \equiv r^{m 2^{n-1}} = r^{\frac{p-1}{2}} \equiv -1 \pmod p.
    $$
    
    Therefore, the order of $g$ modulo $p$ is $2^n$. Since $a b^2 \equiv a^m \pmod p$ is a solution to $x^{2^n} \equiv 1 \pmod p$, $a^m$ is a power of $g$. Let $a^m \equiv g^e \pmod p$.
    
    Since $a$ is a quadratic residue,
    
    $$
    g^{e 2^{n-1}} \equiv a^{m 2^{n-1}} = a^{\frac{p-1}{2}} \equiv 1 \pmod p.
    $$
    
    By properties of order, $2^n \mid e 2^{n-1}$, so $e$ is even. Therefore, $a b g^{-e/2} \bmod p$ is well-defined, and
    
    $$
    \left(a b g^{-e/2}\right)^2 = a^2 b^2 g^{-e} \equiv a^{m+1} g^{-e} \equiv a \pmod p.
    $$

The remaining problem is how to compute $e$. Tonelli and Shanks proposed determining one binary digit of $e$ at a time. Let $e$ be expressed in binary as $e = e_0 + 2 e_1 + 4 e_2 + \cdots$, where $e_k \in \{0, 1\}$. Since $a$ is a quadratic residue, we initially have $e_0 = 0$. Then we determine the values of $e_k$ one by one using the following property:

$$
\left(g^e g^{-(e \bmod 2^k)}\right)^{2^{n-1-k}} \equiv g^{2^{n-1} \cdot e_k} \equiv 
\begin{cases}
1 \pmod p, & \text{if } e_k = 0\\
-1 \pmod p, & \text{if } e_k = 1
\end{cases}
$$

Here, $g^e \equiv a b^2 \pmod p$ is known, and the value of $e \bmod 2^k$ can be computed from the previous digits $e_0, e_1, \cdots, e_{k-1}$. Of course, when implementing the algorithm, we can directly maintain the product $g^e g^{-(e \bmod 2^k)} \bmod p$.

## Practice Problems

- [Luogu P5491 [Template] Quadratic Residue](https://www.luogu.com.cn/problem/P5491)
- ["Timus 1132" Square Root](https://acm.timus.ru/problem.aspx?space=1&num=1132)

## References and Notes

1. [Quadratic residue - Wikipedia](https://en.wikipedia.org/wiki/Quadratic_residue)
2. [Euler's criterion - Wikipedia](https://en.wikipedia.org/wiki/Euler%27s_criterion)

[^ref1]: Daniel. J. Bernstein. Faster Square Roots in Annoying Finite Fields.

[^ref2]: S. Müller, On the computation of square roots in finite fields, Design, Codes and Cryptography, Vol.31, pp. 301-312, 2004.

[^ref3]: A. Menezes, P. van Oorschot and S. Vanstone. Handbook of Applied Cryptography, 1996.

[^ref4]: Alin Bostan, Ryuhei Mori. A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence. Available at <https://arxiv.org/abs/2008.08822>.

[^ref5]: [Proofs of quadratic reciprocity - Wikipedia](https://en.wikipedia.org/wiki/Proofs_of_quadratic_reciprocity)

[^ref6]: Carl Friedrich Gauss. Untersuchungen über höhere Arithmetik, 1965. Page 458-462.

[^ref7]: Kobi Kremnizer. [Lectures in number theory 2022](https://courses.maths.ox.ac.uk/pluginfile.php/29788/mod_resource/content/1/numbertheory-2022.pdf). Proposition 4.3.