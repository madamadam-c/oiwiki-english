author: hydingsy, hyp1231, ranwen, 383494

Prerequisites: [Number Theoretic Blocks](./sqrt-decomposition.md), [Dirichlet Convolution](./dirichlet.md#dirichlet-convolution)

Möbius inversion is an important technique in number theory. For some functions $f(n)$, if it is difficult to directly compute their values, but it is easy to compute their multiple sums or divisor sums $g(n)$, then Möbius inversion can be used to simplify the computation and obtain the value of $f(n)$.

## The Möbius Function

The Möbius function is defined as

$$
\mu(n)=
\begin{cases}
1,&n=1,\\
0,&n\text{ is divisible by a square }>1,\\
(-1)^k,&n\text{ is the product of }k\text{ distinct primes}.\\
\end{cases}
$$

Specifically, suppose the positive integer $n$ has the prime factorization $n=\prod_{i=1}^kp_i^{e_i}$, where $p_i$ are primes and $e_i$ are positive integers. Then the three cases correspond to:

1.  $\mu(1) = 1$;
2.  When there exists $i$ such that $e_i > 1$, i.e., any prime factor appears more than once, $\mu(n)=0$;
3.  Otherwise, for all $i$ we have $e_i = 1$, i.e., every prime factor appears exactly once, then $\mu(n)=(-1)^k$, where $k$ is the number of distinct prime factors.

### Properties

According to the definition, it is easy to verify that the Möbius function $\mu(n)$ is a multiplicative function, but not a completely multiplicative function. Beyond this, the most important property is the following identity:

???+ note "Property"
    For a positive integer $n$, we have
    
    $$
    \sum_{d\mid n}\mu(d) = [n = 1] =
    \begin{cases}
    1,&n=1,\\
    0,&n\neq 1.\\
    \end{cases}
    $$
    
    Here $[\cdot]$ is the Iverson bracket.

??? note "Proof"
    Let $n=\prod_{i=1}^kp_i^{e_i}$, and let $n' = \prod_{i=1}^kp_i$. According to the [Binomial Theorem](../combinatorics/combination.md#binomial-theorem), we have
    
    $$
    \sum_{d\mid n}\mu(d) = \sum_{d\mid n'}\mu(d) = \sum_{i=0}^k\binom{k}{i}(-1)^i = (1 + (-1))^k = [k = 0] = [n = 1].
    $$

Using Dirichlet convolution, this expression can be written as $\varepsilon = 1 * \mu$. That is, the Möbius function is the Dirichlet inverse of the constant function $1$.

This property has a very common application:

$$
[i\perp j] = [\gcd(i,j) = 1] = \sum_{d\mid\gcd(i,j)} \mu(d) = \sum_{d}[d\mid i][d\mid j]\mu(d).
$$

This transforms the coprimality condition into a sum involving the Möbius function, facilitating further derivation.

### Computation Methods

If we need to compute the Möbius function $\mu(n)$ for a single $n$, we can use its [prime factorization](./pollard-rho.md). For example, when $n$ is not too large, we can compute $\mu(n)$ in $O(\sqrt{n})$ time.

???+ example "Reference Implementation"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/mobius/mobius-func-1.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/mobius/mobius-func-1.py:core"
        ```

If we need to precompute $\mu(n)$ for the first $n$ positive integers, we can use the fact that it is a multiplicative function and compute it in $O(n)$ time using the [linear sieve](./sieve.md#sieving-for-mobius-function).

???+ example "Reference Implementation"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/mobius/mobius-func-2.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/mobius/mobius-func-2.py:core"
        ```

## Möbius Inversion

The most important application of the Möbius function is Möbius inversion.

???+ note "Möbius Inversion"
    Let $f(n),g(n)$ be two number-theoretic functions. Then we have
    
    $$
    f(n) = \sum_{d\mid n}g(d) \iff g(n) = \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)f(d).
    $$

??? note "Proof One"
    Direct verification:
    
    $$
    \begin{aligned}
    \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)f(d)
    &= \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)\sum_{k\mid d}g(k)\\
    &= \sum_{k\mid n}g(k)\sum_d[k\mid d\mid n]\mu\left(\dfrac{n}{d}\right)\\
    &= \sum_{k\mid n}g(k)\sum_{d\mid n}\left[\frac{n}{d}\mid\frac{n}{k}\right]\mu\left(\dfrac{n}{d}\right)\\
    &= \sum_{k\mid n}g(k)\left[\frac{n}{k} = 1\right] \\
    &= g(n).
    \end{aligned}
    $$
    
    The key to the transformation is swapping the order of summation and noting that $k\mid d\mid n$ is equivalent to $\dfrac{n}{d}\mid\dfrac{n}{k}$. The second-to-last equality corresponds to summing the Möbius function at $\dfrac{n}{d}$ over all divisors $\dfrac{n}{d}$ of $\dfrac{n}{k}$, which equals $\left[\dfrac{n}{k} = 1\right]$. This expression is nonzero only at $n=k$, and finally we obtain $g(n)$.

??? note "Proof Two"
    Using Dirichlet convolution, the proposition is equivalent to
    
    $$
    f = 1 * g \iff g = \mu * f.
    $$
    
    Using $1 * \mu = \varepsilon$, convolving both sides of the left equation with $\mu$ gives
    
    $$
    f * \mu = (1 * g) * \mu = (1 * \mu) * g = \varepsilon * g = g.
    $$

Möbius inversion is a powerful transformation tool for sums involving various divisibility relations of number-theoretic functions.

???+ example "Examples"
    1.  Euler's totient function $\varphi(n)$ satisfies $n = \sum_{d\mid n}\varphi(d)$, i.e., $\mathrm{id}=1*\varphi$. Applying inversion gives $\varphi = \mu * \mathrm{id}$, i.e.,
        
        $$
        \varphi(n) = \sum_{d\mid n}d\mu\left(\dfrac{n}{d}\right).
        $$
    2.  The divisor function $\sigma_k(n) = \sum_{d\mid n}d^k$, i.e., $\sigma_k = 1 * \mathrm{id}_k$. Applying inversion gives $\mathrm{id}_k = \mu * \sigma_k$, i.e.,
        
        $$
        n^k = \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)\sigma_k(d).
        $$
    3.  The number of distinct prime factors function $\omega(n)=\sum_{d\mid n}[d\in\mathbf P]$, i.e., $\omega = 1* \mathbf{1}_{\mathbf P}$, where $\mathbf{1}_{\mathbf P}$ is the indicator function of the prime set $\mathbf P$. Applying inversion gives $\mathbf{1}_{\mathbf P} = \mu * \omega$, i.e.,
        
        $$
        [n\in\mathbf P] = \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)\omega(d).
        $$
    4.  Consider the number-theoretic function $\Lambda(n)$ satisfying $\log n = \sum_{d\mid n}\Lambda(d)$. This is the Möbius inversion of the logarithm function, also called the von Mangoldt function:
        
        $$
        \Lambda(n) = \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)\log d = 
        \begin{cases}
        \log p, & n = p^e,~p\in\mathbf P,~e\in\mathbf N_+, \\
        0, &\text{otherwise}.
        \end{cases}
        $$

??? note "Proof of the expression for $\Lambda(n)$"
    For prime powers $n=p^e~(e\in\mathbf N_+)$, we have
    
    $$
    \Lambda(n) = \sum_{i=0}^e\mu(p^{e-i})\log p^i = \log p^{e} - \log p^{e-1} = \log p.
    $$
    
    For $n=1$, we obviously have $\Lambda(n)=\log 1=0$. For other composite numbers $n$, we have
    
    $$
    \Lambda(n) = \sum_{d\mid n}\mu(d)(\log n-\log d) = \left(\sum_{d\mid n}\mu(d)\right)\log n-\sum_{d\mid n}\mu(d)\log d.
    $$
    
    According to the property of the Möbius function, the coefficient of $\log n$ is $[n=1]=0$. For the latter term, we can further decompose $d$ into the product of prime factors. For any prime $p\mid n$, consider the coefficient of $\log p$:
    
    $$
    -\sum_{p\mid d\mid n}\mu(d) = \sum_{(d/p)\mid(n/p)}\mu\left(\dfrac{d}{p}\right) = \left[\dfrac{n}{p}=1\right]=0.
    $$
    
    Thus, for composite numbers $n$ with more than one prime factor, we have $\Lambda(n)=0$.

### Extended Forms

In addition to the basic form above, there are some common extended forms of Möbius inversion. First, consider its multiple sum form.

???+ note "Extension One"
    Let $f(n),g(n)$ be two number-theoretic functions. Then we have
    
    $$
    f(n) = \sum_{n\mid d}g(d) \iff g(n) = \sum_{n\mid d}\mu\left(\dfrac{d}{n}\right)f(d).
    $$

??? note "Proof"
    Direct verification:
    
    $$
    \begin{aligned}
    \sum_{n\mid d}\mu\left(\dfrac{d}{n}\right)f(d)
    &= \sum_{n\mid d}\mu\left(\dfrac{d}{n}\right)\sum_{d\mid k}g(k)\\
    &= \sum_{n\mid k}g(k)\sum_{d}[n\mid d\mid k]\mu\left(\dfrac{d}{n}\right)\\
    &= \sum_{n\mid k}g(k)\sum_{n\mid d}\left[\dfrac{d}{n}\mid\dfrac{k}{n}\right]\mu\left(\dfrac{d}{n}\right)\\
    &= \sum_{n\mid k}g(k)\left[\dfrac{k}{n}=1\right]\\
    &= g(n).
    \end{aligned}
    $$
    
    This is completely symmetric to the derivation of the basic form.

Next, Möbius inversion is not limited to addition; in fact, it works for any operation in any [Abel group](../algebra/basic.md#group). For example, it has the following multiplicative form:

???+ note "Extension Two"
    Let $f(n),g(n)$ be two number-theoretic functions. Then we have
    
    $$
    f(n) = \prod_{d\mid n}g(d) \iff g(n) = \prod_{d\mid n}f(d)^{\mu(n/d)}.
    $$

??? note "Proof"
    Direct verification:
    
    $$
    \begin{aligned}
    \prod_{d\mid n}f(d)^{\mu(n/d)}
    &= \prod_{d\mid n}\left(\prod_{k\mid d}g(k)\right)^{\mu(n/d)}\\
    &= \prod_{k\mid n}g(k)\uparrow\left(\sum_d[k\mid d\mid n]\mu\left(\dfrac{n}{d}\right)\right)\\
    &= \prod_{k\mid n}g(k)\uparrow\left(\sum_{d\mid n}\left[\frac{n}{d}\mid\frac{n}{k}\right]\mu\left(\dfrac{n}{d}\right)\right)\\
    &= \prod_{k\mid n}g(k)\uparrow\left[\frac{n}{k} = 1\right] \\
    &= g(n).
    \end{aligned}
    $$
    
    Here, $a\uparrow b = a^b$ is Knuth's up-arrow notation. Comparing with the proof of the basic form, the only difference is that addition is replaced by multiplication, and multiplication is replaced by exponentiation.

From the perspective of Dirichlet convolution, Möbius inversion only uses the fact that "the Möbius function is the Dirichlet inverse of the constant function". It is easy to imagine that similar inversion relationships hold for general [Dirichlet inverses](./dirichlet.md#dirichlet-convolution) as well.

???+ note "Extension Three"
    Let $f(n),g(n),\alpha(n)$ all be number-theoretic functions, and $\alpha^{-1}(n)$ is the Dirichlet inverse of $\alpha(n)$, i.e.,
    
    $$
    [n=1] = \sum_{d\mid n}\alpha\left(\dfrac{n}{d}\right)\alpha^{-1}(d).
    $$
    
    Then we have
    
    $$
    f(n) = \sum_{d\mid n}\alpha\left(\dfrac{n}{d}\right)g(d) \iff g(n) = \sum_{d\mid n}\alpha^{-1}\left(\dfrac{n}{d}\right)f(d).
    $$

??? note "Proof"
    Direct verification:
    
    $$
    \begin{aligned}
    \sum_{d\mid n}\alpha^{-1}\left(\dfrac{n}{d}\right)f(d)
    &= \sum_{d\mid n}\alpha^{-1}\left(\dfrac{n}{d}\right)\sum_{k\mid d}\alpha\left(\dfrac{d}{k}\right)g(k)\\
    &= \sum_{k\mid n}g(k)\sum_d[k\mid d\mid n]\alpha\left(\dfrac{d}{k}\right)\alpha^{-1}\left(\dfrac{n}{d}\right)\\
    &= \sum_{k\mid n}g(k)\sum_{d\mid n}\left[\frac{n}{d}\mid\frac{n}{k}\right]\alpha\left(\dfrac{d}{k}\right)\alpha^{-1}\left(\dfrac{n/k}{d/k}\right)\\
    &= \sum_{k\mid n}g(k)\left[\frac{n}{k} = 1\right] \\
    &= g(n).
    \end{aligned}
    $$
    
    Compared with the proof of the basic form, we only need to replace the second-to-last equality with the definition of the Dirichlet inverse.

???+ note "Corollary"
    Let $f(n),g(n)$ be number-theoretic functions, and $t(n)$ is a completely multiplicative function. Then we have
    
    $$
    f(n) = \sum_{d\mid n}t\left(\dfrac{n}{d}\right)g(d) \iff g(n) = \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)t\left(\dfrac{n}{d}\right)f(d).
    $$

??? note "Proof"
    According to the properties of Dirichlet convolution, for a completely multiplicative function $t(n)$, its Dirichlet inverse is $\mu(n)t(n)$.

Finally, Möbius inversion can also be extended to complex-valued functions on $[1,+\infty)$, not limited to number-theoretic functions. The basic form of Möbius inversion can be seen as a special case of complex-valued functions that take zero at all non-integer points.

???+ note "Extension Four"
    Let $F(x)$ and $G(x)$ both be complex-valued functions on $[1,+\infty)$. Then we have
    
    $$
    F(x) = \sum_{n = 1}^{\lfloor x\rfloor}G\left(\dfrac{x}{n}\right) \iff G(x) = \sum_{n = 1}^{\lfloor x\rfloor}\mu(n)F\left(\dfrac{x}{n}\right).
    $$

??? note "Proof"
    We can extend the definitions of $F$ and $G$. Let $F(x)=G(x)=0$ when $x < 1$. Then the proposition is equivalent to:
    
    $$
    F(x) = \sum_n G\left(\dfrac{x}{n}\right) \iff G(x) = \sum_n \mu(n)F\left(\dfrac{x}{n}\right).
    $$
    
    These sums are over $n\in\mathbf N_+$.
    
    Direct verification:
    
    $$
    \begin{aligned}
    \sum_n \mu(n)F\left(\dfrac{x}{n}\right)
    &= \sum_n\mu(n)\sum_d G\left(\dfrac{x/n}{d}\right)\\
    &= \sum_k G\left(\dfrac{x}{k}\right)\sum_{n\mid k}\mu(n)\\
    &= \sum_k G\left(\dfrac{x}{k}\right)[k=1]\\
    &= G(x).
    \end{aligned}
    $$
    
    Here, to get the second equality, we let $k = nd$.

???+ note "Corollary"
    Let $f(n),g(n)$ be number-theoretic functions. Then we have
    
    $$
    f(n) = \sum_{k=1}^ng\left(\left\lfloor\dfrac{n}{k}\right\rfloor\right) \iff g(n)=\sum_{k=1}^n\mu(k)f\left(\left\lfloor\dfrac{n}{k}\right\rfloor\right).
    $$

??? note "Proof"
    We only need to take $F(x)=f(\lfloor x\rfloor)$ and $G(x)=g(\lfloor x\rfloor)$.

These extended forms can be combined with each other to obtain more complex inversion relationships.

### Dirichlet Prefix Sum

Prerequisites: [Prefix Sums and Differences](../../basic/prefix-sum.md)

Consider the basic form of Möbius inversion:

$$
f(n) = \sum_{d\mid n}g(d) \iff g(n) = \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)f(d).
$$

In the left equation, the value $f(n)$ is the sum of $g(n)$ at all divisors of $n$. If we understand $a\mid b$ as $a$ comes before $b$, then $f(n)$ can be understood as a kind of prefix sum of $g(n)$ in some sense. Therefore, in domestic competition circles, the process of obtaining $\{f(k)\}_{k=1}^n$ from $\{g(k)\}_{k=1}^n$ is also called **Dirichlet prefix sum**, and the inverse process is called Dirichlet difference. These methods mostly appear when precomputing some number-theoretic function at the first $N$ points.

Next, we discuss the computation of Dirichlet prefix sums. If we treat each prime as a dimension, this is a kind of high-dimensional prefix sum. Recall the [dimension-by-dimension prefix sum algorithm](../../basic/prefix-sum.md#dimension-by-dimension-prefix-sum): iterate through all dimensions one by one, and accumulate each position's value to its successor in that dimension. For number-theoretic functions, this is equivalent to iterating through all primes in increasing order and accumulating the function value at $n$ to $np$. This traversal order is consistent with the [Eratosthenes sieve](./sieve.md#eratosthenes-sieve). Therefore, this algorithm can compute the Dirichlet prefix sum of a sequence of length $n$ in $O(n\log\log n)$ time. Similarly, using dimension-by-dimension differences, we can compute the Dirichlet difference of the sequence in the same time complexity.

???+ example "Reference Implementation"
    === "Dirichlet Prefix Sum"
        ```cpp
        --8<-- "docs/math/code/mobius/mobius-func-3.cpp:presum"
        ```
    
    === "Dirichlet Difference"
        ```cpp
        --8<-- "docs/math/code/mobius/mobius-func-3.cpp:diff"
        ```

This computation method can be extended to the multiple sum form (Extension One), the product form (Extension Two), and using a completely multiplicative function instead of the constant function (the corollary of Extension Three).

## Example Problems

This section demonstrates the application methods of Möbius inversion and some common transformation techniques through example problems. First, let's get familiar with the basic technique for handling gcd conditions in sums through an example.

???+ example "[Luogu P2522 [HAOI 2011] Problem b](https://www.luogu.com.cn/problem/P2522)"
    $T$ test cases. For each test case, compute:
    
    $$
    \sum_{i=x}^{n}\sum_{j=y}^{m}[\gcd(i,j)=k].
    $$
    
    Constraints: $1\le T,x,y,n,m,k\le 5\times 10^4$.

??? note "Solution"
    According to the principle of inclusion-exclusion, the original expression can be divided into $4$ blocks, and each block has the form
    
    $$
    f(n,m,k)=\sum_{i=1}^{n}\sum_{j=1}^{m}[\gcd(i,j)=k].
    $$
    
    For this type of expression, the following is a standard derivation process: extract the common factor, apply the Möbius function property, and swap the order of summation.
    
    First, since $i$ and $j$ can only take multiples of $k$, we can factor this out first—this is equivalent to substituting $i=ki'$ and $j=kj'$:
    
    $$
    f(n,m,k)=\sum_{i=1}^{\lfloor n/k\rfloor}\sum_{j=1}^{\lfloor m/k\rfloor}[\gcd(i,j)=1].
    $$
    
    Then, using the property of the Möbius function:
    
    $$
    [\gcd(i,j)=1] = \sum_{d\mid\gcd(i,j)}\mu(d) = \sum_d[d\mid i][d\mid j]\mu(d).
    $$
    
    Substitute it into the expression and swap the order of summation:
    
    $$
    f(n,m,k)=\sum_d\mu(d)\left(\sum_{i=1}^{\lfloor n/k\rfloor}[d\mid i]\right)\left(\sum_{j=1}^{\lfloor m/k\rfloor}[d\mid j]\right).
    $$
    
    The benefit of this transformation is that when $d$ is fixed, the terms involving $i$ and $j$ in the sum are separated and can be summed separately. Next, because
    
    $$
    \sum_{i=1}^{\lfloor n/k\rfloor}[d\mid i] = \left\lfloor\dfrac{\lfloor n/k\rfloor}{d}\right\rfloor,~\sum_{j=1}^{\lfloor m/k\rfloor}[d\mid j]=\left\lfloor\dfrac{\lfloor m/k\rfloor}{d}\right\rfloor,
    $$
    
    we have
    
    $$
    f(n,m,k)=\sum_d\mu(d)\left\lfloor\dfrac{\lfloor n/k\rfloor}{d}\right\rfloor\left\lfloor\dfrac{\lfloor m/k\rfloor}{d}\right\rfloor.
    $$
    
    After preprocessing $\mu(d)$ with a linear sieve and its prefix sums, we can solve it using number theoretic blocks. The total time complexity is $O(N + T\sqrt{N})$, where $N$ is the upper bound of $n,m$, and $T$ is the number of test cases.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/math/code/mobius/mobius_1.cpp"
    ```

The next two example problems demonstrate the method of enumerating common divisors and using the [sieve](./sieve.md#general-multiplicative-function) to compute general multiplicative function values.

???+ example "[SPOJ LCMSUM](https://www.spoj.com/problems/LCMSUM/)"
    $T$ test cases. For each test case, compute:
    
    $$
    \sum_{i=1}^n \operatorname{lcm}(i,n).
    $$
    
    Constraints: $1\le T\le 3\times 10^5,~1\le n\le 10^6$.

??? note "Solution One"
    The problem provides the least common multiple, but the greatest common divisor is often easier to handle. So first, transform:
    
    $$
    f(n)=\sum_{i=1}^n \operatorname{lcm}(i,n) = \sum_{i=1}^n \frac{i\cdot n}{\gcd(i,n)}.
    $$
    
    Factor out $n$, and enumerate the greatest common divisor $k$:
    
    $$
    f(n)=n\sum_{k\mid n}\sum_{i=1}^n\dfrac{i}{k}[\gcd(i,n)=k].
    $$
    
    For the inner sum, this is the most common case involving the greatest common divisor. Following the standard processing:
    
    $$
    \begin{aligned}
    f(n) &= n\sum_{k\mid n}\sum_{i=1}^{n/k}i\left[\gcd\left(i,\dfrac{n}{k}\right)=1\right]\\
    &= n\sum_{k\mid n}\sum_{i=1}^{n/k}i\sum_d\mu(d)[d\mid i]\left[d\mid \dfrac{n}{k}\right]\\
    &= n\sum_{k\mid n}\sum_d\mu(d)\left[d\mid \dfrac{n}{k}\right]\left(\sum_{i=1}^{n/k}i[d\mid i]\right).
    \end{aligned}
    $$
    
    Again, the sum involving $i$ is separated from the other parts and can be handled separately. The final sum is actually an arithmetic series sum: (taking $i=di'$)
    
    $$
    \sum_{i=1}^{n/k}i[d\mid i] = d\frac{1}{2}\left(\dfrac{n}{kd}+1\right)\dfrac{n}{kd}=:dG\left(\dfrac{n}{kd}\right).
    $$
    
    From this, we obtain:
    
    $$
    f(n) = n\sum_{k\mid n}\sum_d\mu(d)\left[d\mid \dfrac{n}{k}\right]dG\left(\dfrac{n}{kd}\right).
    $$
    
    After enumerating common divisors, such double sums are very common. For them, there is also a standard method: set the product as a new variable $\ell=kd$, then swap the order of summation again. Since $d\mid(n/k)$ is equivalent to $d\mid\ell\mid n$, the original expression becomes:
    
    $$
    f(n) = n\sum_{\ell\mid n}G\left(\dfrac{n}{\ell}\right)\sum_{d\mid\ell}\mu(d)d.
    $$
    
    Let $F(\ell)=\sum_{d\mid\ell}\mu(d)d$, then the original expression has the form:
    
    $$
    f(n) = n\sum_{\ell\mid n}G\left(\dfrac{n}{\ell}\right)F(\ell).
    $$
    
    Since $\mu(d)d$ is a multiplicative function, its convolution with the constant function $1$, $F(n)$, is also a multiplicative function. Although the sum in the above expression has the form of Dirichlet convolution, $G(n)$ is not a multiplicative function, so the whole sum is not a multiplicative function. However, $G(n)$ is a polynomial, so it is actually a linear combination of several completely multiplicative functions. Therefore, we have
    
    $$
    f(n) = \dfrac{1}{2}n\left(\sum_{\ell}\left(\dfrac{n}{\ell}\right)^2F(\ell) + \sum_{\ell}\dfrac{n}{\ell}F(\ell)\right).
    $$
    
    These two terms (excluding the coefficient) are multiplicative functions and can be directly precomputed with a linear sieve (or after computing the inner function with linear sieve, precomputed with Dirichlet prefix sum in $O(N\log\log N)$ time). Specifically, let
    
    $$
    H_s(n) = \sum_{\ell}\left(\dfrac{n}{\ell}\right)^sF(\ell),~s=1,2.
    $$
    
    To derive their expressions, we only need to determine their values at prime powers. For a prime $p$ and positive exponent $e$, we have
    
    $$
    \begin{aligned}
    F(p^e) &= \mu(1) + \mu(p)p + \sum_{j=2}^e\mu(p^j)p^j = 1-p,\\
    H_s(p^e) &= (p^e)^{s}F(1) + \sum_{j=1}^e(p^{e-j})^sF(p^j) = p^{es} + (1-p)\dfrac{1-p^{es}}{1-p^s},~s=1,2.
    \end{aligned}
    $$
    
    In particular, $H_1(p^e)\equiv 1$ is a constant function, and
    
    $$
    H_2(p^e) = p^{2e} + (1-p)\dfrac{1-p^{2e}}{1-p^2} = H_2(p^{e-1}) + p^{2e} - p^{2e-1}.
    $$
    
    This can be easily solved with a linear sieve. After precomputing $H_2(n)$ with a linear sieve, a single query can be solved in $O(1)$ time using the expression $f(n)=(n/2)(H_2(n)+1)$. The total time complexity is $O(N+T)$, where $N$ is the upper bound of $n$, and $T$ is the number of test cases.
    
    In the reference implementation, due to the special nature of this problem's expression, further derivation is done for the linear sieve part, which is not required. Using only the values at prime powers, preprocessing can still be done in $O(N)$ time. These derivations are detailed in Solution Two.

??? note "Solution Two"
    For this problem, there is a more flexible approach. As can be seen from Solution One,
    
    $$
    f(n) = n\sum_{k\mid n}\sum_{i=1}^{n/k}i\left[\gcd\left(i,\dfrac{n}{k}\right)=1\right] = n\sum_{k\mid n}F\left(\dfrac{n}{k}\right).
    $$
    
    If at this step we do not continue with Möbius inversion, but observe that the following sum is actually the sum of integers not exceeding $d=n/k$ that are coprime to $d$. For $d>1$, since integers coprime to $d$ appear in pairs, i.e., $i$ and $d-i$ must both be coprime to $d$, we have
    
    $$
    F(d)=\sum_{i=1}^{n'}i[i\perp d] = \sum_{i=1}^{d}(d-i)[i\perp d] = \dfrac{1}{2}d\sum_{i=1}^{d}[i\perp d] = \dfrac{1}{2}d\varphi(d).
    $$
    
    For $d=1$, we have
    
    $$
    F(d)=1=\dfrac{1}{2}+\dfrac{1}{2}d\varphi(d).
    $$
    
    Therefore, the original expression can be written as
    
    $$
    f(n) = \dfrac{1}{2}n\left(\sum_{d\mid n}d\varphi(d) + 1\right).
    $$
    
    Since $G(n)=\sum_{d\mid n}d\varphi(d)$ is the Dirichlet convolution of the multiplicative function $n\varphi(n)$ and the constant function $1$, it is also a multiplicative function and can be precomputed with a linear sieve. For this, we only need to determine its value at prime powers. For a prime $p$ and positive exponent $e$, we have
    
    $$
    G(p^e) = 1 + \sum_{i=1}^ep^e(p^e-1) = G(p^{e-1}) + p^{2e} - p^{2e-1}.
    $$
    
    It can be seen that this expression is consistent with the result derived in Solution One. The total time complexity of this method is still $O(N+T)$.
    
    Finally, using the multiplicative function expression of this problem, we can further optimize the linear sieve computation. For a prime $p$, we have
    
    $$
    G(p) = 1 - p + p^2.
    $$
    
    The key for the linear sieve for general $n$ is to compute $G(pn)$. This further divides into two cases. When $p\perp n$, since $G$ is multiplicative,
    
    $$
    G(pn) = G(p)G(n).
    $$
    
    Otherwise, when $p\mid n$, let $n=p^em$ with $p\perp m$, then
    
    $$
    \begin{aligned}
    G(pn) &= G(p^{e+1})G(m)\\
    &= G(p^e)G(m) + (p^{2e+2} - p^{2e+1})G(m)\\
    &= G(n) + (p^{2e+2} - p^{2e+1})G(m).
    \end{aligned}
    $$
    
    Direct verification shows that this expression also holds for the case $p\perp n$. Therefore, we have
    
    $$
    G(n) - G\left(\dfrac{n}{p}\right) = (p^{2e}-p^{2e-1})G(m).
    $$
    
    Substituting into the above gives
    
    $$
    G(pn) = G(n) + p^2\left(G(n) - G\left(\dfrac{n}{p}\right)\right).
    $$
    
    This simplifies the computation in the linear sieve part. Of course, this derivation is not necessary; for multiplicative functions without special properties, we can directly use $G(pn)=G(p^{e+1})G(m)$ to complete the linear sieve computation.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/math/code/mobius/mobius_2.cpp"
    ```

???+ example "[BZOJ 2154 [National Team Training] Crash's Number Table](https://hydro.ac/p/bzoj-P2154)"
    Compute:
    
    $$
    \sum_{i=1}^n\sum_{j=1}^m\operatorname{lcm}(i,j)\mod{20101009}.
    $$
    
    Constraints: $1\le n,m\le 10^7$.

??? note "Solution"
    Ignore the modulus during derivation. Let
    
    $$
    f(n,m) = \sum_{i=1}^n\sum_{j=1}^m\operatorname{lcm}(i,j).
    $$
    
    Still converting the least common multiple to the greatest common divisor, enumerating common divisors, and applying the standard processing:
    
    $$
    \begin{aligned}
    f(n,m)
    &= \sum_k\sum_{i=1}^n\sum_{j=1}^m\dfrac{ij}{k}[\gcd(i,j)=k] \\
    &= \sum_k\sum_{i=1}^{\lfloor n/k\rfloor}\sum_{j=1}^{\lfloor m/k\rfloor} kij[\gcd(i,j)=1]\\
    &= \sum_k\sum_{i=1}^{\lfloor n/k\rfloor}\sum_{j=1}^{\lfloor m/k\rfloor} kij\sum_d\mu(d)[d\mid i][d\mid j]\\
    &= \sum_kk\sum_d\mu(d)\left(\sum_{i=1}^{\lfloor n/k\rfloor}i[d\mid i]\right)\left(\sum_{j=1}^{\lfloor m/k\rfloor}j[d\mid j]\right).
    \end{aligned}
    $$
    
    Again, the sum separates $i$ and $j$. First compute these inner sums, extract the factor (i.e., take $i=di'$):
    
    $$
    \sum_{i=1}^{\lfloor n/k\rfloor}i[d\mid i] = d\sum_{i=1}^{\lfloor\lfloor n/k\rfloor/d\rfloor}i = dG\left(\left\lfloor\dfrac{\lfloor n/k\rfloor}{d}\right\rfloor\right) = dG\left(\left\lfloor\dfrac{n}{kd}\right\rfloor\right).
    $$
    
    Here, $G(n)=\dfrac{1}{2}n(n+1)$ is the arithmetic series sum, and the last equality uses the property of the [floor function](./basic.md#floor-function). Similarly, the other sum can be computed. Substituting back into the earlier expression:
    
    $$
    f(n,m) = \sum_k k\sum_{d}\mu(d)d^2G\left(\left\lfloor\dfrac{n}{kd}\right\rfloor\right)G\left(\left\lfloor\dfrac{m}{kd}\right\rfloor\right).
    $$
    
    Consistent with the previous case, for such expressions enumerating common divisors, we often need to enumerate the product $\ell = kd$ and swap the order of summation again:
    
    $$
    f(n,m) = \sum_{\ell}\left(\sum_{d\mid\ell}\mu(d)d\ell\right)G\left(\left\lfloor\dfrac{n}{\ell}\right\rfloor\right)G\left(\left\lfloor\dfrac{m}{\ell}\right\rfloor\right).
    $$
    
    Let
    
    $$
    F(\ell) = \sum_{d\mid\ell}\mu(d)d\ell.
    $$
    
    This is the product of the multiplicative function $\ell$ and the multiplicative function $\sum_{d\mid\ell}\mu(d)d$, so it is also a multiplicative function. It can be directly precomputed with a linear sieve, and its prefix sums can also be precomputed. Then $f(n,m)$ can be computed using number theoretic blocks. The total time complexity is $O(\min\{n,m\})$.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/math/code/mobius/mobius_3.cpp"
    ```

The next example problem is special and requires transforming the divisor count function for products.

???+ example "[LOJ 2185. [SDOI2015] Sum of Number of Divisors](https://loj.ac/problem/2185)"
    $T$ test cases. For each test case, compute:
    
    $$
    \sum_{i=1}^n\sum_{j=1}^m\sigma_0(ij).
    $$
    
    Here, $\sigma_0(n)=\sum_{d \mid n}1$ represents the number of divisors of $n$.
    
    Constraints: $1\le n,m,T\le 5\times 10^4$.

??? note "Solution"
    The difficulty of this problem is transforming $\sigma_0(ij)$ into an expression in terms of the greatest common divisor. Since $\sigma_0$ is a multiplicative function, we first consider the case of prime powers. For a prime $p$ and non-negative exponents $e_1,e_2$, let $i=p^{e_1},~j=p^{e_2}$, then
    
    $$
    \sigma_0(ij) = 1 + e_1 + e_2 = \sum_{x\mid i}\sum_{y\mid j}[x\perp y].
    $$
    
    For the general case, let $i=\prod_p i_p$ and $j=\prod_p j_p$, where $i_p,j_p$ are respectively the powers of $p$ in the prime factorizations of $i,j$. Then
    
    $$
    \sigma_0(ij) = \prod_p\sigma_0(i_pj_p)= \prod_p\sum_{x_p\mid i_p}\sum_{y_p\mid j_p}[x_p\perp y_p].
    $$
    
    Note that enumerating all divisors $x_p$ of each prime power factor $i_p$ of $i$ is equivalent to enumerating all divisors $x$ of $i$ and then decomposing into all prime power factors $x_p$; similarly for $j$. Therefore, using the distributive law of multiplication, we have
    
    $$
    \sigma_0(ij) = \sum_{x\mid i}\sum_{y\mid j}\prod_p[x_p\perp y_p] = \sum_{x\mid i}\sum_{y\mid j}[x\perp y].
    $$
    
    The last step uses the conclusion: $x\perp y$ if and only if for each prime factor $p$, we have $x_p\perp y_p$.
    
    After obtaining this expression, we can apply the standard processing:
    
    $$
    \begin{aligned}
    \sigma_0(ij) 
    &= \sum_{x\mid i}\sum_{y\mid j}[x\perp y]\\
    &= \sum_{x\mid i}\sum_{y\mid j}\sum_d\mu(d)[d\mid x][d\mid y]\\
    &= \sum_d\mu(d)\left(\sum_{x}[d\mid x\mid i]\right)\left(\sum_{y}[d\mid y\mid j]\right)\\
    &= \sum_d\mu(d)[d\mid i][d\mid j]\sigma_0\left(\dfrac{i}{d}\right)\sigma_0\left(\dfrac{j}{d}\right).
    \end{aligned}
    $$
    
    The meaning of the last step of derivation is: the function is nonzero only when $d\mid i$ and $d\mid j$. At this time, enumerating $x$ satisfying $d\mid x\mid i$ is equivalent to enumerating divisors $\dfrac{x}{d}$ of $\dfrac{i}{d}$; similarly for $y$ and $j$.
    
    Substitute this expression back into the original expression and swap the order of summation:
    
    $$
    \begin{aligned}
    f(n,m)
    &= \sum_{i=1}^n\sum_{j=1}^m\sigma_0(ij)\\
    &= \sum_{i=1}^n\sum_{j=1}^m\sum_d\mu(d)[d\mid i][d\mid j]\sigma_0\left(\dfrac{i}{d}\right)\sigma_0\left(\dfrac{j}{d}\right)\\
    &= \sum_d\mu(d)\left(\sum_{i=1}^n[d\mid i]\sigma_0\left(\dfrac{i}{d}\right)\right)\left(\sum_{j=1}^m[d\mid j]\sigma_0\left(\dfrac{j}{d}\right)\right)\\
    &= \sum_d\mu(d)\left(\sum_{i=1}^{\lfloor n/d\rfloor}\sigma_0(i)\right)\left(\sum_{j=1}^{\lfloor m/d\rfloor}\sigma_0(j)\right).
    \end{aligned}
    $$
    
    Let $G(n)=\sum_{i=1}^n\sigma_0(i)$, then
    
    $$
    f(n,m)=\sum_{d}\mu(d)G\left(\left\lfloor\dfrac{n}{d}\right\rfloor\right)G\left(\left\lfloor\dfrac{m}{d}\right\rfloor\right).
    $$
    
    This can be solved using number theoretic blocks. We only need to precompute the prefix sums of $\mu(n)$ and $\sigma_0(n)$. The total time complexity is $O(N+T\sqrt{N})$, where $N$ is the upper bound of $n,m$, and $T$ is the number of test cases.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/math/code/mobius/mobius_4.cpp"
    ```

The final example problem demonstrates how to apply the multiplicative version of Möbius inversion.

???+ example "[Luogu P5221 Product](https://www.luogu.com.cn/problem/P5221)"
    Compute:
    
    $$
    \prod_{i=1}^n\prod_{j=1}^n\dfrac{\operatorname{lcm}(i,j)}{\gcd(i,j)}\pmod{104857601}.
    $$
    
    Constraints: $1\le n\le 1\times 10^6$.

??? note "Solution One"
    Ignore the modulus during derivation. Let
    
    $$
    f(n) = \prod_{i=1}^n\prod_{j=1}^n\dfrac{\operatorname{lcm}(i,j)}{\gcd(i,j)}.
    $$
    
    Still converting the least common multiple to the greatest common divisor:
    
    $$
    f(n) = \prod_{i=1}^n\prod_{j=1}^n\dfrac{ij}{(\gcd(i,j))^2}.
    $$
    
    Note that the product of these factors is independent of each other and can be computed separately. Let
    
    $$
    g(n) = \prod_{i=1}^n\prod_{j=1}^n\gcd(i,j).
    $$
    
    Then the original expression equals:
    
    $$
    f(n) = \dfrac{(n!)^{2n}}{g(n)^2}.
    $$
    
    The key is to solve the computation problem of $g(n)$. The processing flow is similar to that described earlier, but we need to switch to the corresponding multiplicative version. First, enumerate and extract the common divisor:
    
    $$
    \begin{aligned}
    g(n) &= \prod_k\prod_{i=1}^n\prod_{j=1}^nk\uparrow[\gcd(i,j)=k]\\
    &= \prod_k\prod_{i=1}^{\lfloor n/k\rfloor}\prod_{j=1}^{\lfloor n/k\rfloor}k\uparrow[\gcd(i,j)=1].
    \end{aligned}
    $$
    
    Here, $a\uparrow b=a^b$ is Knuth's up-arrow notation. Then substitute $[\gcd(i,j)=1]=\sum_d\mu(d)[d\mid i][d\mid j]$, and convert the sum in the exponent to a product of powers:
    
    $$
    g(n) = \prod_k\prod_d\prod_{i=1}^{\lfloor n/k\rfloor}\prod_{j=1}^{\lfloor n/k\rfloor}k\uparrow(\mu(d)[d\mid i][d\mid j]).
    $$
    
    Further extract the factor (i.e., let $i=di'$, $j=dj'$), and apply the property of the [floor function](./basic.md#floor-function):
    
    $$
    g(n) = \prod_k\prod_d\prod_{i=1}^{\lfloor n/(kd)\rfloor}\prod_{j=1}^{\lfloor n/(kd)\rfloor}k\uparrow\mu(d).
    $$
    
    Then separate the product regarding $i,j$, and we find the product does not contain $i,j$, so it is equivalent to raising the product to a power:
    
    $$
    g(n) = \prod_k\prod_d k\uparrow\left(\mu(d)\left\lfloor\dfrac{n}{kd}\right\rfloor^2\right).
    $$
    
    Since we enumerated common divisors earlier, for this expression we need to swap the order of multiplication again. Let $\ell = kd$:
    
    $$
    \begin{aligned}
    g(n) &= \prod_{\ell}\prod_{d\mid\ell}\left(\dfrac{\ell}{d}\right)\uparrow\left(\mu(d)\left\lfloor\dfrac{n}{\ell}\right\rfloor^2\right)\\
    &= \prod_\ell\left(\prod_{d\mid\ell}\left(\dfrac{\ell}{d}\right)\uparrow\mu(d)\right)\uparrow\left\lfloor\dfrac{n}{\ell}\right\rfloor^2.
    \end{aligned}
    $$
    
    Let
    
    $$
    F(n) = \prod_{d\mid n}\left(\dfrac{n}{d}\right)\uparrow\mu(d).
    $$
    
    This is easily seen to be the Möbius inversion in product form for $\tilde F(n)=n$. Even without knowing its expression, we can apply the [Dirichlet difference](#dirichlet-prefix-sum) method to preprocess in $O(n\log\log n)$ time. Of course, since the form of $\tilde F(n)$ is very simple, the expression for $F(n)$ can be directly obtained:
    
    $$
    F(n) = 
    \begin{cases}
    p, & n = p^e,~p\in\mathbf P,~e\in\mathbf N_+, \\
    1, &\text{otherwise}.
    \end{cases}
    $$
    
    The [von Mangoldt function](#mobius-inversion) is its natural logarithm. After obtaining the values of $F(n)$, we can directly apply the product version of number theoretic blocks to compute $g(n)$ in $O(\sqrt{n})$ time, and then obtain $f(n)$. The total time complexity is $O(n)$.
    
    It is worth noting that when computations involving products are involved, [Euler's theorem](./fermat.md) is often needed, so the modulus used for the exponent part is different from the modulus given in the problem.

??? note "Solution Two"
    The difficulty of the product version derivation is that the handling of products and exponents is relatively unfamiliar. Therefore, for such problems, we can also take the logarithm first and then derive. For this problem, consider only the derivation of $g(n)$. After taking its logarithm:
    
    $$
    \log g(n) = \sum_{i=1}^n\sum_{j=1}^n\log\gcd(i,j).
    $$
    
    For such expressions involving the greatest common divisor, directly applying the standard derivation process gives:
    
    $$
    \begin{aligned}
    \log g(n) 
    &= \sum_k\log k\sum_{i=1}^n\sum_{j=1}^n[\gcd(i,j)=k]\\
    &= \sum_k\log k\sum_{i=1}^{\lfloor n/k\rfloor}\sum_{j=1}^{\lfloor n/k\rfloor}[\gcd(i,j)=1]\\
    &= \sum_k\log k\sum_d\mu(d)\left(\sum_{i=1}^{\lfloor n/k\rfloor}[i\mid d]\right)\left(\sum_{j=1}^{\lfloor n/k\rfloor}[j\mid d]\right)\\
    &= \sum_k\log k\sum_d\mu(d)\left\lfloor\dfrac{n}{kd}\right\rfloor^2\\
    &= \sum_{\ell}\left(\sum_d\mu(d)\log\dfrac{\ell}{d}\right)\left\lfloor\dfrac{n}{\ell}\right\rfloor^2\\
    &= \sum_{\ell}\Lambda(\ell)\left\lfloor\dfrac{n}{\ell}\right\rfloor^2.
    \end{aligned}
    $$
    
    Here, $\Lambda(n)$ is the [von Mangoldt function](#mobius-inversion). Taking the exponent of this derivation result gives the result in Solution One.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/math/code/mobius/mobius_5.cpp"
    ```

## Practice Problems

-   [Luogu P3312 [SDOI2014] Number Table](https://www.luogu.com.cn/problem/P3312)
-   [Luogu P3700 [CQOI2017] Little Q's Table](https://www.luogu.com.cn/problem/P3700)
-   [Luogu P3704 [SDOI2017] Number Table](https://www.luogu.com.cn/problem/P3704)
-   [Luogu P3768 Simple Math Problem](https://www.luogu.com.cn/problem/P3768)
-   [Luogu P4464 [National Training Team] JZPKIL](https://www.luogu.com.cn/problem/P4464)
-   [Luogu P4619 [SDOI2018] Old Problems](https://www.luogu.com.cn/problem/P4619)
-   [Luogu P5518 [MtOI2019] Ghost Orchestra](https://www.luogu.com.cn/problem/P5518)
-   [Luogu P6222 Simple Problem Enhanced Version](https://www.luogu.com.cn/problem/P6222)
-   [Luogu P6825「EZEC-4」Sum](https://www.luogu.com.cn/problem/P6825)
-   [Luogu P7486「Stoi2031」Rainbow](https://www.luogu.com.cn/problem/P7486)
-   [AtCoder Grand Contest 038 C - LCMs](https://atcoder.jp/contests/agc038/tasks/agc038_c)
-   [Codeforeces 1139 D. Steps to One](https://codeforces.com/problemset/problem/1139/D)

## References

-   [Möbius function - Wikipedia](https://en.wikipedia.org/wiki/M%C3%B6bius_function)
-   [Möbius inversion formula - Wikipedia](https://en.wikipedia.org/wiki/M%C3%B6bius_inversion_formula)
-   [Von Mangoldt function - Wikipedia](https://en.wikipedia.org/wiki/Von_Mangoldt_function)
-   [algocode Algorithm Blog](https://web.archive.org/web/20190523150159/https://algocode.net/2018/04/18/20180418-KB-Mobius-Inversion-Formula/)
