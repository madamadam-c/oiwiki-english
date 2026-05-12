author: Marcythm, Xeonacid, CSPNOIP

## Definition

In terms of its methodology, this sieve is also known as the "Extended Eratosthenes Sieve".

It is called "Min_25 Sieve" because it was invented and first used by [Min\_25](http://min-25.hatenablog.com/).

## Properties

It can solve prefix sum problems for a class of **multiplicative functions** in $O\left(\frac{n^{\frac{3}{4}}}{\log{n}}\right)$ or $\Theta\left(n^{1 - \epsilon}\right)$ time complexity.

Requirements: $f(p)$ is a sum of completely multiplicative functions that can be quickly evaluated for $p$ (e.g., polynomials); $f(p^c)$ can be quickly evaluated.

## Notations

-   **Unless otherwise specified, in this section all variables denoted by $p$ take values in the set of all primes.**
-   $x / y := \left\lfloor\frac{x}{y}\right\rfloor$
-   $\operatorname{isprime}(n) := [ |\{d : d \mid n\}| = 2 ]$, i.e., its value is $1$ when $n$ is prime, and $0$ otherwise.
-   $p_{k}$: the $k$-th smallest prime (e.g., $p_{1} = 2, p_{2} = 3$). Special case: let $p_{0} = 1$.
-   $\operatorname{lpf}(n) := [1 < n] \min\{p : p \mid n\} + [1 = n]$, i.e., the smallest prime factor of $n$. Special case: when $n = 1$, its value is $1$.
-   $F_{\mathrm{prime}}(n) := \sum_{2 \le p \le n} f(p)$
-   $F_{k}(n) := \sum_{i = 2}^{n} [p_{k} \le \operatorname{lpf}(i)] f(i)$

## Explanation

Observing the definition of $F_{k}(n)$, we find that the answer is $F_{1}(n) + f(1) = F_{1}(n) + 1$.

Consider how to compute $F_{k}(n)$. By enumerating the smallest prime factor and its exponent for each $i$, we obtain the recurrence:

$$
\begin{aligned}
    F_{k}(n)
    & = \sum_{i = 2}^{n} [p_{k} \le \operatorname{lpf}(i)] f(i) \\
    & = \sum_{\substack{k \le i \\ p_{i}^{2} \le n}} \sum_{\substack{c \ge 1 \\ p_{i}^{c} \le n}} f\left(p_{i}^{c}\right) ([c > 1] + F_{i + 1}\left(n / p_{i}^{c}\right)) + \sum_{\substack{k \le i \\ p_{i} \le n}} f(p_{i}) \\
    & = \sum_{\substack{k \le i \\ p_{i}^{2} \le n}} \sum_{\substack{c \ge 1 \\ p_{i}^{c + 1} \le n}} \left(f\left(p_{i}^{c}\right) F_{i + 1}\left(n / p_{i}^{c}\right) + f\left(p_{i}^{c + 1}\right)\right) + F_{\mathrm{prime}}(n) - F_{\mathrm{prime}}(p_{k - 1})
\end{aligned}
$$

The last step is based on the fact: for $c$ satisfying $p_{i}^{c} \le n < p_{i}^{c + 1}$, we have $p_{i}^{c + 1} > n \iff n / p_{i}^{c} < p_{i} < p_{i + 1}$, hence $F_{i + 1}\left(n / p_{i}^{c}\right) = 0$.

Its boundary condition is $F_{k}(n) = 0$ when $p_{k} > n$.

Assuming we have already computed all $F_{\mathrm{prime}}(n)$, there are two ways to compute all $F_{k}(n)$:

1.  Compute directly according to the recurrence.
2.  Enumerate $p$ from large to small; since transitions only contribute when $p^2 < n$, we can optimize using suffix sums according to the recurrence.

Now consider how to compute $F_{\mathrm{prime}}{(n)}$.

Observing the process of computing $F_{k}(n)$, it is easy to see that $F_{\mathrm{prime}}$ only has useful values at $O(\sqrt{n})$ points: $1, 2, \dots, \left\lfloor\sqrt{n}\right\rfloor, n / \sqrt{n}, \dots, n / 2, n$.

Generally, $f(p)$ is a low-degree polynomial in $p$, which can be expressed as $f(p) = \sum a_{i} p^{c_{i}}$.

For each $p^{c_{i}}$, its contribution to $F_{\mathrm{prime}}(n)$ is $a_{i} \sum_{2 \le p \le n} p^{c_{i}}$.

Considering the contributions of each $p^{c_{i}}$ separately, the problem reduces to: given $n, s, g(p) = p^s$, compute $\sum_{p \le m} g(p)$ for all $m = n / i$.

???+ tip "Note"
    $g(p) = p^s$ is a completely multiplicative function!

Thus, let $G_{k}(n) := \sum_{i = 2}^{n} \left[p_{k} < \operatorname{lpf}(i) \lor \operatorname{isprime}(i)\right] g(i)$, i.e., the sum of $g$ values of numbers remaining after the $k$-th round of the Eratosthenes sieve.

For a composite number $x \le n$, we must have $\operatorname{lpf}(x) \le \sqrt{x} \le \sqrt{n}$. Let $p_{\ell(n)}$ be the largest prime not exceeding $\sqrt{n}$, then $\sum_{2\le p\le n}g(p) = G_{\ell(n)}(n)$, i.e., after $\ell$ rounds of the Eratosthenes sieve, the remaining numbers are all primes.

Consider the boundary value of $G$. Obviously, $G_{0}(n) = \sum_{i = 2}^{n} g(i)$. (Remember? We specially defined $p_{0} = 1$)

For the transition, considering the process of the Eratosthenes sieve, we analyze the contributions of each part:

1.  For the part where $n < p_{k}^{2}$, the $G$ value remains unchanged, i.e., $G_{k}(n) = G_{k - 1}(n)$.
2.  For the part where $p_{k}^{2} \le n$, the numbers being sieved must have prime factor $p_{k}$, i.e., $-g(p_{k}) G_{k - 1}(n / p_{k})$.
3.  For the second part, since $p_{k}^{2} \le n \iff p_{k} \le n / p_{k}$, numbers satisfying $\operatorname{lpf}(i) < p_{k}$ are subtracted extra. This part should be added back, i.e., $g(p_{k}) G_{k - 1}(p_{k - 1})$.

Then we have:

$$
G_{k}(n) = G_{k - 1}(n) - \left[p_{k}^{2} \le n\right] g(p_{k}) (G_{k - 1}(n / p_{k}) - G_{k - 1}(p_{k - 1}))
$$

## Complexity Analysis

For the computation of $F_{k}(n)$, the time complexity of the first method is proven to be $O\left(n^{1 - \epsilon}\right)$ (see Zhu Zhenting's training paper [Some Summation Problems for Special Number-Theoretic Functions](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2018%E8%AE%BA%E6%96%87%E9%9B%86.pdf) Section 2.3);

For the second method, its essence is the second part of the Min_25 sieve, which is also mentioned in Ren Zhizhou's paper [Several Methods for Summing Multiplicative Functions](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87%E9%9B%86.pdf) (Section 6.5.4), and its time complexity is proven to be $O\left(\frac{n^{\frac{3}{4}}}{\log{n}}\right)$.

For the computation of $F_{\mathrm{prime}}(n)$, its implementation is actually the same as the first part of the Min_25 sieve.

For each $m = n / i$, transitions only contribute when enumerating $p_{k}$ satisfying $p_{k}^{2} \le m$. The time complexity can be estimated as:

$$
\begin{aligned}
    T(n)
    & = \sum_{i^{2} \le n} O\left(\pi\left(\sqrt{i}\right)\right) + \sum_{i^{2} \le n} O\left(\pi\left(\sqrt{\frac{n}{i}}\right)\right) \\
    & = \sum_{i^{2} \le n} O\left(\frac{\sqrt{i}}{\ln{\sqrt{i}}}\right) + \sum_{i^{2} \le n} O\left(\frac{\sqrt{\frac{n}{i}}}{\ln{\sqrt{\frac{n}{i}}}}\right) \\
    & = O\left(\int_{1}^{\sqrt{n}} \frac{\sqrt{\frac{n}{x}}}{\log{\sqrt{\frac{n}{x}}}} \mathrm{d} x\right) \\
    & = O\left(\frac{n^{\frac{3}{4}}}{\log{n}}\right)
\end{aligned}
$$

For space complexity, we can see that both $F_{k}$ and $F_{\mathrm{prime}}$ only have valid values at $n / i$, with $O(\sqrt{n})$ points in total. Recording only the valid values can reduce space complexity to $O(\sqrt{n})$.

First, we can obtain all valid values through one number-theoretic block division, and record them in an array $\text{lis}$ of size $O(\sqrt{n})$. For a valid value $v$, let $\text{id}(v)$ be its index in $\text{lis}$. It is easy to see that for all valid values $v$, $\text{id}(v) \le \sqrt{n}$.

Then we separately consider valid values $\le \sqrt{n}$ and $> \sqrt{n}$: for valid values $v \le \sqrt{n}$, we use an array $\text{le}$ to record $\text{id}(v)$, i.e., $\text{le}_v = \text{id}(v)$; for valid values $v > \sqrt{n}$, we use an array $\text{ge}$ to record $\text{id}(v)$. Since $v$ is too large, we use $v' = n / v < \sqrt{n}$ to record $\text{id}(v)$, i.e., $\text{ge}_{v'} = \text{id}(v)$.

This way, we can use two arrays of size $O(\sqrt{n})$ to record all $\text{id}$ values for valid values and query them in $O(1)$. When computing $F_{k}$ or $F_{\mathrm{prime}}$, using the $\text{id}$ of valid values instead of the valid values themselves as indices reduces space complexity to $O(\sqrt{n})$.

## Procedure

For the computation of $F_{k}(n)$, we generally choose the first method with lower implementation difficulty, which often performs better than the second method for smaller data scales;

For the computation of $F_{\mathrm{prime}}(n)$, we can implement it directly according to the recurrence.

For $p_{k}^{2} \le n$, we can preprocess $s_{k} := F_{\mathrm{prime}}(p_{k})$ using linear sieve to replace $F_{\mathrm{prime}}(p_{k - 1})$ in the $F_{k}$ recurrence.

Correspondingly, $G_{k - 1}(p_{k - 1}) = \sum_{i = 1}^{k - 1} g(p_{i})$ in the $G$ recurrence can also be preprocessed this way.

When using the Extended Eratosthenes Sieve to compute the prefix sum of a **multiplicative function** $f$, the following should be clarified:

-   How to quickly (generally in linear time complexity) sieve out the first $\sqrt{n}$ values of $f$;
-   The polynomial representation of $f(p)$;
-   How to quickly compute $f(p^c)$.

After clarifying these points, implement the following parts in order:

1.  Sieve out primes in $[1, \sqrt{n}]$ and the first $\sqrt{n}$ values of $f$;
2.  For each term in the polynomial representation of $f(p)$, sieve out the corresponding $G$, and combine them to get all $O(\sqrt{n})$ useful values of $F_{\mathrm{prime}}$;
3.  Implement the recursion according to the $F_{k}$ recurrence to compute $F_{1}(n)$.

## Example Problems

???+ example "[Luogu P4213 Template: Du Jiao Sieve](https://www.luogu.com.cn/problem/P4213)"
    Compute $\displaystyle\sum_{i = 1}^{n} \varphi(i)$ and $\displaystyle\sum_{i = 1}^{n} \mu(i)$.

??? note "Solution"
    For computing the prefix sum of $\varphi(i)$, first note that $f(p) = p - 1$. For the linear term $(p)$ in $f(p)$, we have $g(p) = p, G_{0}(n) = \sum_{i = 2}^{n} g(i) = \frac{(n + 2) (n - 1)}{2}$; for the constant term $(-1)$, we have $g(p) = -1, G_{0}(n) = \sum_{i = 2}^{n} g(i) = -n + 1$. Sieve twice and add them together to get all $O(\sqrt{n})$ required values of $F_{\mathrm{prime}}$.

    For computing the prefix sum of $\mu(i)$, we know $f(p) = -1$. Thus $g(p) = -1, G_{0}(n) = \sum_{i = 2}^{n} g(i) = -n + 1$. Direct sieving gives all $O(\sqrt{n})$ required values of $F_{\mathrm{prime}}$.

???+ example "[LOJ 6053 Simple Function](https://loj.ac/p/6053)"
    Given $f(n)$:

    $$
    f(n) = \begin{cases}
        1 & n = 1 \\
        p \operatorname{xor} c & n = p^{c} \\
        f(a)f(b) & n = ab \land a \perp b
    \end{cases}
    $$

    Compute $\displaystyle\sum_{i = 1}^{n} f(i)$.

??? note "Solution"
    It is easy to see that $f(p) = p - 1 + 2[p = 2]$. Sieve following the method for $\varphi$, and discuss the special case of $2$.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/math/code/min-25/min-25_1.cpp"
    ```
