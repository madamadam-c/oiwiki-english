author: hsfzLZH1, sshwy, StudyingFather, Marcythm

Du's Sieve is used to handle prefix sum problems of arithmetic functions. For an arithmetic function $f$, Du's Sieve can compute $S(n)=\sum_{i=1}^{n}f(i)$ with a time complexity better than linear.

## Algorithm Idea

We try to construct a recurrence formula for $S(n)$ in terms of $S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)$.

For any arithmetic function $g$:

$$
\begin{aligned}
    \sum_{i=1}^{n}(f * g)(i) & =\sum_{i=1}^{n}\sum_{d \mid i}g(d)f\left(\frac{i}{d}\right)           \\
                             & =\sum_{i=1}^{n}g(i)S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)
\end{aligned}
$$

Where $f*g$ is the [Dirichlet convolution](./dirichlet.md#dirichlet-convolution) of arithmetic functions $f$ and $g$.

???+ note "Brief Proof"
    $g(d)f\left(\frac{i}{d}\right)$ contributes to all $i\leq n$. So change the order of summation, let $d$, $\frac{i}{d}$ be the new $i,j$:
    
    $$
    \begin{aligned}
        \sum_{i=1}^n\sum_{d \mid i}g(d)f\left(\frac{i}{d}\right) & =\sum_{i=1}^n\sum_{j=1}^{\left\lfloor n/i \right\rfloor}g(i)f(j) \\
                                                                 & =\sum_{i=1}^ng(i)\sum_{j=1}^{\left\lfloor n/i \right\rfloor}f(j) \\
                                                                 & =\sum_{i=1}^ng(i)S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)
    \end{aligned}
    $$

Then we can get the recurrence formula:

$$
\begin{aligned}
    g(1)S(n) & = \sum_{i=1}^n g(i)S\left(\left\lfloor\frac{n}{i}\right\rfloor\right) - \sum_{i=2}^n g(i)S\left(\left\lfloor\frac{n}{i}\right\rfloor\right) \\
             & = \sum_{i=1}^n (f * g)(i) - \sum_{i=2}^n g(i)S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)
\end{aligned}
$$

If we can construct an appropriate arithmetic function $g$ such that:

1.  $\sum_{i=1}^n(f * g)(i)$ can be computed quickly;
2.  The prefix sum of $g$ can be computed quickly, so that $\sum_{i=2}^ng(i)S\left(\left\lfloor\dfrac{n}{i}\right\rfloor\right)$ can be solved by number theoretic division.

Then we can compute $g(1)S(n)$ in a relatively short time.

???+ note "Note"
    Regardless of whether the arithmetic function $f$ is a multiplicative function, as long as an appropriate arithmetic function $g$ can be constructed, Du's Sieve can be used to compute the prefix sum of $f$.
    
    For example, considering $f(n)=\mathrm{i}\varphi(n)$, obviously $f$ is not a multiplicative function, but we can take $g(n)=1$, thus:
    
    $$
    \sum_{k=1}^n (f*g)(k)=\mathrm{i}\frac{n(n+1)}{2}
    $$
    
    The time complexity of computing $\sum_{k\leq m} (f*g)(k)$ and $\sum_{k \leq m} g(k)$ are both $O(1)$, so Du's Sieve can be considered.

## Time Complexity

Let $R(n)=\left\{\left\lfloor \dfrac{n}{k} \right\rfloor: k=2,3,\dots,n\right\}$. Using the [property](./sqrt-decomposition.md#properties) of number theoretic division, for any $m\in R(n)$, we have $R(m)\subseteq R(n)$. That is, after using memoization, we only need to compute $S(k)$ once for all $k\in R(n)$ to get the values of $R(n)$. The number of these points is $|R(n)|=O(\sqrt{n})$.

Let the time complexity of computing $\sum_{i=1}^n(f * g)(i)$ and $\sum_{i=1}^n g(i)$ be both $O(1)$. Let the time complexity of computing $S(n)$ be $T(n)$. Then:

$$
\begin{aligned}
    T(n) & = \sum_{k\in R(n)} T(k)\\
         & = \Theta(\sqrt n)+\sum_{k=1}^{\lfloor\sqrt n\rfloor} O(\sqrt k)+\sum_{k=2}^{\lfloor\sqrt n\rfloor} O\left(\sqrt{\dfrac{n}{k}}\right)\\
         & = O\left(\int_{0}^{\sqrt n} \left(\sqrt{x} + \sqrt{\dfrac{n}{x}}\right) \mathrm{d}x\right)\\
         & = O\left(n^{3/4}\right).
\end{aligned}
$$

If we can precompute some of $S(k)$ for $k=1,2,\dots,m$, where $m\geq \lfloor\sqrt n\rfloor$. Let the preprocessing time complexity be $T_0(m)$. Then $T(n)$ at this time is:

$$
\begin{aligned}
    T(n) & = T_0(m)+\sum_{k\in R(n);k>m} T(k)\\
         & = T_0(m)+\sum_{k=1}^{\lfloor n/m \rfloor} O\left(\sqrt{\dfrac{n}{k}}\right)\\
         & = O\left(T_0(m)+\int_{0}^{n/m} \sqrt{\dfrac{n}{x}} \mathrm{d}x\right)\\
         & = O\left(T_0(m)+\dfrac{n}{\sqrt m}\right).
\end{aligned}
$$

If $T_0(m)=O(m)$ (such as linear sieve), by the AM-GM inequality: when $m=\Theta\left(n^{2/3}\right)$, $T(n)$ attains its minimum value $O\left(n^{2/3}\right)$.

??? failure "A False Proof Example"
    Let the complexity of computing $S(n)$ be $T(n)$. Then:
    
    $$
    T(n)=\Theta\left(\sqrt{n}\right)+O\left(\sum_{i=2}^{\lfloor\sqrt{n}\rfloor} T\left(\left\lfloor\frac{n}{i}\right\rfloor\right)\right)
    $$
    
    
    $$
    \begin{aligned}
        T\left(\left\lfloor\frac{n}{i}\right\rfloor\right) & = \Theta\left(\sqrt{\frac{n}{i}}\right)+O\left(\sum_{j=2}^{\lfloor\sqrt{n/i}\rfloor} T\left(\left\lfloor\frac{n}{ij}\right\rfloor\right)\right) \\
                                                           & = O\left(\sqrt{\frac{n}{i}}\right)
    \end{aligned}
    $$
    
    Here, $O\left(\sum_{j=2}^{\lfloor\sqrt{n/i}\rfloor} T\left(\left\lfloor\dfrac{n}{ij}\right\rfloor\right)\right)$ is treated as higher-order infinitesimal, so it can be discarded. Therefore:
    
    $$
    \begin{aligned}
        T(n) & = \Theta\left(\sqrt{n}\right)+O\left(\sum_{i=2}^{\lfloor\sqrt{n}\rfloor} \sqrt{\frac{n}{i}}\right) \\
             & = O\left(\sum_{i=1}^{\lfloor\sqrt{n}\rfloor} \sqrt{\frac{n}{i}}\right) \\
             & = O\left(\int_{0}^{\sqrt{n}}\sqrt{\frac{n}{x}}\mathrm{d}x\right) \\
             & = O\left(n^{3/4}\right)
        \end{aligned}
    $$
    
    ??? bug "Bug"
        The problem is in "treating as higher-order infinitesimal and discarding". We substitute $T\left(\left\lfloor\dfrac{n}{i}\right\rfloor\right)$ into the formula for $T(n)$:
        
        $$
        \begin{aligned}
            T(n) & = \Theta\left(\sqrt{n}\right)+O\left(\sum_{i=2}^{\lfloor\sqrt{n}\rfloor} \sqrt{\frac{n}{i}}\right)+O\left(\sum_{i=2}^{\lfloor\sqrt{n}\rfloor}\sum_{j=2}^{\lfloor\sqrt{n/i}\rfloor} T\left(\left\lfloor\frac{n}{ij}\right\rfloor\right)\right)\\
                 & = O\left(\sqrt{n}+\int_{0}^{\sqrt{n}}\sqrt{\frac{n}{x}}\mathrm{d}x\right)+O\left(\sum_{i=2}^{\lfloor\sqrt{n}\rfloor}\sum_{j=2}^{\lfloor\sqrt{n/i}\rfloor} T\left(\left\lfloor\frac{n}{ij}\right\rfloor\right)\right)\\
                 & = O\left(n^{3/4}\right)+O\left(\sum_{i=2}^{\lfloor\sqrt{n}\rfloor}\sum_{j=2}^{\lfloor\sqrt{n/i}\rfloor} T\left(\left\lfloor\frac{n}{ij}\right\rfloor\right)\right)\\
        \end{aligned}
        $$
        
        We consider $\displaystyle\sum_{i=2}^{\lfloor\sqrt{n}\rfloor}\sum_{j=2}^{\lfloor\sqrt{n/i}\rfloor} T\left(\left\lfloor\frac{n}{ij}\right\rfloor\right)$. It is not hard to find:
        
        $$
        \begin{aligned}
            \sum_{i=2}^{\lfloor\sqrt{n}\rfloor}\sum_{j=2}^{\lfloor\sqrt{n/i}\rfloor} T\left(\left\lfloor\frac{n}{ij}\right\rfloor\right) & = \Omega\left(\sum_{i=2}^{\lfloor\sqrt{n}\rfloor} T\left(\left\lfloor\frac{n}{i}\cdot\left\lfloor\sqrt\frac{n}{i}\right\rfloor^{-1}\right\rfloor\right)\right) \\
                                                                                                                                          & = \Omega\left(\sum_{i=2}^{\lfloor\sqrt{n}\rfloor} T\left(\left\lfloor\sqrt\frac{n}{i}\right\rfloor\right)\right)
        \end{aligned}
        $$
        
        Since memoization is not introduced, $T\left(\left\lfloor\sqrt{\dfrac{n}{i}}\right\rfloor\right)$ in the above formula is still $\Omega\left(\left(\dfrac{n}{i}\right)^{1/4}\right)$. Thus the so-called "higher-order infinitesimal" part cannot be discarded.
        
        In fact, the sub-linear time complexity of Du's Sieve is guaranteed by memoization. Only after using memoization can it be ensured that the multi-summation term does not appear.

## Example Problems

### Problem One

???+ note "[P4213 Template Du's Sieve (Sum)](https://www.luogu.com.cn/problem/P4213)"
    Find the values of $S_1(n)= \sum_{i=1}^{n} \mu(i)$ and $S_2(n)= \sum_{i=1}^{n} \varphi(i)$, $1\leq n<2^{31}$.

=== "Möbius Function Prefix Sum"
    We know:
    
    $$
    \epsilon = [n=1] = \mu * 1 = \sum_{d \mid n} \mu(d)
    $$
    
    
    $$
    \begin{aligned}
        S_1(n) & =\sum_{i=1}^n \epsilon (i)-\sum_{i=2}^n S_1 \left(\left\lfloor \frac n i \right\rfloor\right) \\
               & = 1-\sum_{i=2}^n S_1\left(\left\lfloor \frac n i\right\rfloor\right)
    \end{aligned}
    $$
    
    The derivation of time complexity is in the [Time Complexity](#time-complexity) section.
    
    For larger values, we need to store the corresponding values in a `map`/`unordered_map` for direct use later.

=== "Euler's Totient Function Prefix Sum"
    Of course, we can also use Du's Sieve to find the prefix sum of $\varphi(x)$, but a better method is to apply Möbius inversion.
    
    === "Möbius Inversion"
        $$
        \begin{aligned}
            \sum_{i=1}^n \sum_{j=1}^n [\gcd(i,j)=1] & =\sum_{i=1}^n \sum_{j=1}^n \sum_{d \mid i,d \mid j} \mu(d)    \\
                                                     & =\sum_{d=1}^n \mu(d) {\left\lfloor \frac n d \right\rfloor}^2
        \end{aligned}
        $$
        
        Since what is asked is $\sum_{i=1}^n \sum_{j=1}^i [\gcd(i,j)=1]$, we exclude the case $i=1,j=1$ and divide the result by $2$.
        
        It can be observed that after finding the prefix sum of the Möbius function, we can quickly compute the prefix sum of Euler's totient function. Time complexity $O\left(n^{\frac 2 3}\right)$.
    
    === "Du's Sieve"
        Find $S(n)=\sum_{i=1}^n\varphi(i)$.
        
        Similarly, $\varphi * 1=\operatorname{id}$, thus:
        
        $$
            \begin{aligned}
                S(n) & =\sum_{i=1}^n i - \sum_{i=2}^n S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)    \\
                     & =\frac{1}{2}n(n+1) - \sum_{i=2}^n S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)
            \end{aligned}
        $$

??? note "Code Implementation"
    ```cpp
    --8<-- "docs/math/code/du/du_1.cpp"
    ```

### Problem Two

???+ note "[LuoguP3768 Simple Mathematical Problem](https://www.luogu.com.cn/problem/P3768)"
    Find:
    
    $$
    \sum_{i=1}^n\sum_{j=1}^ni\cdot j\cdot\gcd(i,j)\pmod p
    $$
    
    where $n\leq 10^{10},5\times 10^8\leq p\leq 1.1\times 10^9$, $p$ is prime.

Use $\varphi * 1=\operatorname{id}$ and Möbius inversion to get:

$$
\sum_{d=1}^nF^2\left(\left\lfloor\frac{n}{d}\right\rfloor\right)\cdot d^2\varphi(d)
$$

where $F(n)=\dfrac{1}{2}n(n+1)$

For $\sum_{d=1}^nF\left(\left\dfrac{n}{d}\right\rfloor\right)^2$, do number theoretic division, and the prefix sum of $d^2\varphi(d)$ is handled by Du's Sieve:

$$
f(n)=n^2\varphi(n)=(\operatorname{id}^2\varphi)(n)
$$

$$

S(n)=\sum_{i=1}^nf(i)=\sum_{i=1}^n(\operatorname{id}^2\varphi)(i)
$$

Need to construct a multiplicative function $g$ such that $f\times g$ and $g$ can have their prefix sums computed quickly.

The prefix sum of pure $\varphi$ can be handled by Du's Sieve of $\varphi * 1$, but here $f$ has an extra $\operatorname{id}^2$, so we convolve an $\operatorname{id}^2$ to make it a constant:

$$
S(n)=\sum_{i=1}^n\left(\left(\operatorname{id}^2\varphi\right) * \operatorname{id}^2\right)(i)-\sum_{i=2}^n\operatorname{id}^2(i)S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)
$$

Simplify the convolution:

$$
\begin{aligned}
    ((\operatorname{id}^2\varphi)* \operatorname{id}^2)(i) & =\sum_{d \mid i}\left(\operatorname{id}^2\varphi\right)(d)\operatorname{id}^2\left(\frac{i}{d}\right) \\
                                                           & =\sum_{d \mid i}d^2\varphi(d)\left(\frac{i}{d}\right)^2                                               \\
                                                           & =\sum_{d \mid i}i^2\varphi(d)=i^2\sum_{d \mid i}\varphi(d)                                            \\
                                                           & =i^2(\varphi*1)(i)=i^3
\end{aligned}
$$

Simplify $S(n)$:

$$
\begin{aligned}
    S(n) & =\sum_{i=1}^n\left((\operatorname{id}^2\varphi)* \operatorname{id}^2\right)(i)-\sum_{i=2}^n\operatorname{id}^2(i)S\left(\left\lfloor\frac{n}{i}\right\rfloor\right) \\
         & =\sum_{i=1}^ni^3-\sum_{i=2}^ni^2S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)                                                                                  \\
         & =\left(\frac{1}{2}n(n+1)\right)^2-\sum_{i=2}^ni^2S\left(\left\lfloor\frac{n}{i}\right\rfloor\right)                                                                 \\
\end{aligned}
$$

Solve by number theoretic division.

??? note "Code Implementation"
    ```cpp
    --8<-- "docs/math/code/du/du_2.cpp"
    ```

## References

1.  Ren Zhizhou, 2016, "Several Methods for Summing Multiplicative Functions", 2016 China Olympiad Informatics National Team Candidate Paper
2.  [Time and Space Complexity Analysis of Du's Sieve - riteme.site](https://riteme.site/blog/2018-9-11/time-space-complexity-dyh-algo.html)