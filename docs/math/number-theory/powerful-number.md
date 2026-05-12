## Definition

Powerful Number (hereinafter PN) sieve is similar to the Dujiao sieve, or rather an extension of it, and can be used to compute prefix sums of some multiplicative functions.

**Requirements**:

-   There exists a function $g$ such that:
    -   $g$ is a multiplicative function.
    -   $g$ has a prefix sum that is easy to compute.
    -   For a prime $p$, $g(p) = f(p)$.

Assume we need to compute the prefix sum $F(n) = \sum_{i=1}^{n} f(i)$ of a multiplicative function $f$.

## Powerful Numbers

**Definition**: For a positive integer $n$, let its prime factorization be $n = \prod_{i=1}^{m} p_{i}^{e_{i}}$. $n$ is a PN if and only if $\forall 1 \le i \le m, e_{i} > 1$.

**Property 1**: All PNs can be expressed in the form $a^{2}b^{3}$.

**Proof**: If $e_i$ is even, combine $p_{i}^{e_{i}}$ into $a^{2}$; if $e_i$ is odd, first combine $p_{i}^{3}$ into $b^{3}$, then combine $p_{i}^{e_{i}-3}$ into $a^{2}$.

**Property 2**: The number of PNs not exceeding $n$ is at most $O(\sqrt{n})$.

**Proof**: Consider enumerating $a$, then consider the number of $b$ satisfying the condition. The number of PNs is approximately

$$
\int_{1}^{\sqrt{n}} \sqrt[3]{\frac{n}{x^2}} \mathrm{d}x = O(\sqrt{n})
$$

So how do we find all PNs not exceeding $n$? Use a linear sieve to find all primes within $\sqrt{n}$, then perform a DFS to search the exponents of each prime. Since the number of PNs not exceeding $n$ is at most $O(\sqrt{n})$, we search at most $O(\sqrt{n})$ times.

## PN Sieve

First, construct a multiplicative function $g$ whose prefix sum is easy to compute, satisfying $g(p) = f(p)$ for primes $p$. Let $G(n) = \sum_{i=1}^{n} g(i)$.

Then, construct the function $h = f / g$, where $/$ represents Dirichlet convolution division. According to the properties of Dirichlet convolution, $h$ is also a multiplicative function, so $h(1) = 1$. We have $f = g * h$, where $*$ denotes Dirichlet convolution.

For a prime $p$, $f(p) = g(1)h(p) + g(p)h(1) = h(p) + g(p) \implies h(p) = 0$. From $h(p)=0$ and $h$ being a multiplicative function, we can deduce that for non-PNs $n$, we have $h(n) = 0$, i.e., $h$ takes non-zero values only at PNs.

Now, from $f = g * h$ we have

$$
\begin{aligned}
F(n) &= \sum_{i = 1}^{n} f(i)\\
     &= \sum_{i = 1}^{n} \sum_{d|i} h(d) g\left(\frac{i}{d}\right)\\
     &= \sum_{d=1}^{n} \sum_{i=1}^{\lfloor \frac{n}{d}\rfloor} h(d) g(i)\\
     &= \sum_{d=1}^{n} h(d) \sum_{i=1}^{\lfloor \frac{n}{d}\rfloor}  g(i) \\
     &= \sum_{d=1}^{n} h(d) G\left(\left\lfloor \frac{n}{d}\right\rfloor\right)\\
     &= \sum_{\substack{d=1 \\ d \text{ is PN}}}^{n}h(d) G\left(\left\lfloor \frac{n}{d}\right\rfloor\right)
\end{aligned}
$$

Find all PNs in $O(\sqrt{n})$ and compute all effective values of $h$. To compute the effective values of $h$, we only need to compute the values at all $h(p^c)$, and then, since $h$ is a multiplicative function, we can derive all effective values of $h$. Now for each effective value $d$, we compute $h(d)G\left(\left\lfloor \dfrac{n}{d} \right\rfloor\right)$ and accumulate the sum to obtain $F(n)$.

Below we consider computing $h(p^c)$. There are two methods: one is to directly derive a formula for $h(p^c)$ that depends only on $p$ and $c$, and compute $h(p^c)$ according to the formula; the other is that from $f = g * h$ we have $f(p^c) = \sum_{i=0}^c g(p^i)h(p^{c-i})$, so by rearranging, $h(p^c) = f(p^c) - \sum_{i=1}^{c}g(p^i)h(p^{c-i})$, and now we can enumerate primes $p$ and exponents $c$ to solve for all $h(p^c)$.

### Process

1.  Construct $g$
2.  Construct a method for fast computation of $G$
3.  Compute $h(p^c)$
4.  Search for PNs and accumulate the answer during the process
5.  Obtain the result

For step 3, we can compute directly from the formula, use enumeration for precomputation and lookup tables, or derive on the fly when encountered during the search.

### Properties

Let's analyze using the second method for computing $h(p^c)$. The analysis can be divided into two parts: computing $h(p^c)$ and searching.

For the first part, since the number of primes within $O(\sqrt{n})$ is $O\left(\dfrac{\sqrt{n}}{\log n}\right)$, each prime $p$ has at most $\log n$ exponents, and computing $h(p^c)$ requires a loop of $(c - 1)$ times. Therefore, the time complexity of the first part is $O\left(\dfrac{\sqrt{n}}{\log n} \cdot \log n \cdot \log n\right) = O(\sqrt{n}\log{n})$, and this is a loose upper bound. Depending on the problem, different optimizations can be added to reduce the time complexity of the first part.

For the search part, since the number of PNs not exceeding $n$ is at most $O(\sqrt{n})$, we search at most $O(\sqrt{n})$ times. For each PN, the time complexity varies depending on the method for computing $G$. For example, if the time complexity of computing $G\left(\left\lfloor \dfrac{n}{d}\right\rfloor\right)$ is $O(1)$, then the complexity of the second part is $O(\sqrt{n})$.

Specifically, if the Dujiao sieve is used to compute $G\left(\left\lfloor \dfrac{n}{d}\right\rfloor\right)$, the time complexity of the second part is that of the Dujiao sieve, namely $O(n^{\frac{2}{3}})$. Because if $G(n)$ is computed once in advance, and larger values are stored using a linear sieve optimization and data structures supporting fast random access (such as `std::map` and `std::unordered_map` in C++), then the $G\left(\left\lfloor \dfrac{n}{d}\right\rfloor\right)$ used in the Dujiao sieve are either recorded by the linear sieve or stored in `std::map`. This can be directly verified by program.

For space complexity, the bottleneck is storing $h(p^c)$. If a two-dimensional array $a$ is used, where $a_{i,j}$ represents the value of $h(p_i^j)$, the space complexity is $O\left(\dfrac{\sqrt{n}}{\log n} \cdot \log n\right) = O(\sqrt{n})$.

## Practice Problems

### [Luogu P5325 Template Min\_25 Sieve](https://www.luogu.com.cn/problem/P5325)

**Problem**: Given a multiplicative function $f(p^k) = p^k(p^k-1)$, compute $\sum_{i=1}^{n} f(i)$.

It is easy to see that $f(p) = p(p-1) = \operatorname{id}(p)\varphi(p)$, and we construct $g(n) = \operatorname{id}(n)\varphi(n)$.

Consider using the Dujiao sieve to compute $G(n)$. From $(\operatorname{id}\cdot \varphi) * \operatorname{id} = \operatorname{id}_2$, we get $G(n)= \sum_{i=1}^{n} i^2 - \sum_{d=2}^{n} d \cdot G\left(\left\lfloor \dfrac{n}{d} \right\rfloor\right)$.

Then the values of $h(p^k)$ can be computed by enumeration, and this method is not elaborated here.

Alternatively, this problem can directly derive a formula for $h(p^k)$ that depends only on $p$ and $k$, as follows:

$$
\begin{aligned}
& f(p^k) = \sum_{i=0}^{k} g(p^{k-i})h(p^i)\\
\iff & p^k(p^k-1) = \sum_{i=0}^{k} p^{k-i}\varphi(p^{k-i}) h(p^i)\\
\iff & p^k(p^k-1) = \sum_{i=0}^{k} p^{2k-2i-1}(p - 1) h(p^i)\\
\iff & p^k(p^k-1) = h(p^k) + \sum_{i=0}^{k-1} p^{2k-2i-1}(p - 1) h(p^i)\\
\iff & h(p^k) = p^k(p^k-1) - \sum_{i=0}^{k-1} p^{2k-2i-1}(p - 1) h(p^i)\\
\iff & h(p^k) - p^2h(p^{k-1}) = p^{k}(p^k-1)-p^{k+1}(p^{k-1}-1) - p(p-1)h(p^{k-1})\\
\iff & h(p^k) - ph(p^{k-1}) = p^{k+1} - p^k\\
\iff & \frac{h(p^k)}{p^k} - \frac{h(p^{k-1})}{p^{k-1}} = p - 1\\
\end{aligned}
$$

Then, using $h(p) = 0$ and accumulation, we derive $h(p^k) = (k-1)(p-1)p^k$.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/math/code/powerful-number/powerful-number_1.cpp"
    ```

### [LOJ #6053 Simple Function](https://loj.ac/problem/6053)

Given $f(n)$:

$$
f(n) =
\begin{cases}
1 & n = 1 \\
p \oplus c & n=p^c \\
f(a)f(b) & n=ab \text{ and } a \perp b
\end{cases}
$$

It is easy to get:

$$
f(p) =
\begin{cases}
p + 1 & p = 2 \\
p - 1 & \text{otherwise} \\
\end{cases}
$$

Construct $g$ as:

$$
g(n) =
\begin{cases}
3 \varphi(n) & 2 \mid n \\
\varphi(n) & \text{otherwise} \\
\end{cases}
$$

It is easy to verify that $g(p) = f(p)$ and $g$ is a multiplicative function.

Now consider computing $G(n)$.

$$
\begin{aligned}
G(n)
&= \sum_{i=1}^{n}[i \bmod 2 = 1] \varphi(i) + 3 \sum_{i=1}^{n}[i \bmod 2 = 0] \varphi(i)\\
&= \sum_{i=1}^{n} \varphi(i) + 2\sum_{i=1}^{n} [i \bmod 2 = 0]\varphi(i) \\
&= \sum_{i=1}^{n} \varphi(i) + 2\sum_{i=1}^{\lfloor \frac{n}{2} \rfloor} \varphi(2i)
\end{aligned}
$$

Let $S_1(n) = \sum_{i=1}^{n} \varphi(i)$, $S_2(n) = \sum_{i=1}^{n} \varphi(2i)$, then $G(n) = S_1(n) + 2S_2\left(\left\lfloor \dfrac{n}{2} \right\rfloor\right)$.

When $2 \mid n$, we have

$$
\begin{aligned}
S_2(n)
&= \sum_{i=1}^{n} \varphi(2i) \\
&= \sum_{i=1}^{\frac{n}{2}} (\varphi(2(2i-1)) + \varphi(2(2i))) \\
&= \sum_{i=1}^{\frac{n}{2}} (\varphi(2i-1) + 2\varphi(2i)) \\
&= \sum_{i=1}^{\frac{n}{2}} (\varphi(2i-1) + \varphi(2i)) + \sum_{i=1}^{\frac{n}{2}} \varphi(2i) \\
&= \sum_{i=1}^{n} \varphi(i) + S_2\left(\frac{n}{2}\right)\\
&= S_1(n) + S_2\left(\left\lfloor \frac{n}{2} \right\rfloor\right)\\
\end{aligned}
$$

When $2 \nmid n$, we have

$$
\begin{aligned}
S_2(n)
&= S_2(n-1) + \varphi(2n) \\
&= S_2(n-1) + \varphi(n) \\
&= \sum_{i=1}^{n-1} \varphi(i) + S_2\left(\frac{n-1}{2}\right) + \varphi(n)\\
&= S_1(n) + S_2\left(\left\lfloor \frac{n}{2} \right\rfloor\right)\\
\end{aligned}
$$

In summary, we have $S_2(n) = S_1(n) + S_2\left(\left\lfloor \dfrac{n}{2} \right\rfloor\right)$.

$S_1$ can be computed using the Dujiao sieve, and $S_2$ can be computed directly from the formula, so $G$ can also be obtained.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/math/code/powerful-number/powerful-number_2.cpp"
    ```

## Exercises

-   [PE708 Twos are all you need](https://projecteuler.net/problem=708)
-   [PE639 Summing a multiplicative function](https://projecteuler.net/problem=639)
-   [PE484 Arithmetic Derivative](https://projecteuler.net/problem=484)

## References

-   [Wallbreaker No. 5 - Brief Solution for Powerful Number Sieve](https://www.cnblogs.com/wallbreaker5th/p/13901487.html)
-   [command_block - Du Jiao Sieve (+ Bell Series + Powerful Number)](https://www.luogu.com.cn/blog/command-block/du-jiao-shai)
