author: Early0v0

## Prerequisites

-   [Multiplicative functions](./basic.md#multiplicative-functions)

## Definition

The Zhou sieve (also known as the Dujiao sieve) is a sieve algorithm that can compute the prefix sum of most multiplicative functions in sublinear time complexity.

Below, we use computing $\displaystyle\sum_{i=1}^nf(i)$ as an example to elaborate on the principles of the Zhou sieve.

## Notations

-   $\mathbb P$ denotes the set of primes, and $p_i$ denotes the $i$-th prime.
-   $m$ denotes the number of primes within $\sqrt n$.

## Requirements

When $p\in\mathbb P$ and $c\in\mathbb N$, $f(p^c)$ is a low-degree polynomial in $p$.

## Idea

-   For any integer in $[1,n]$, it has at most one prime factor greater than $\sqrt n$.
-   We leverage the fact that $\left\lfloor\dfrac ni\right\rfloor(i\in[1,n]\cap\mathbb N)$ takes only $O(\sqrt n)$ distinct values to reduce the time complexity.

## Process

Divide all integers in $[1,n]$ into two categories based on whether they have a prime factor greater than $\sqrt n$:

$$
\sum_{i=1}^nf(i)=\sum_{i=1}^n\left[\exists d\in(\sqrt n,n]\cap\mathbb P,d\mid i\right]f(i)+\sum_{i=1}^n\left[\forall d\in(\sqrt n,n]\cap\mathbb P,d\nmid i\right]f(i)
$$

For the first part, enumerate the largest factor; using the property of multiplicative functions, we can transform it:

$$
\sum_{i=1}^nf(i)=\sum_{i=1}^{\sqrt n}f(i)\cdot\left(\sum_{d=\lfloor\sqrt n\rfloor+1}^{\lfloor\frac ni\rfloor}[d\in\mathbb P]f(d)\right)+\sum_{i=1}^n\left[\forall d\in(\sqrt n,n]\cap\mathbb P,d\nmid i\right]f(i)
$$

The two parts can be computed separately.

### Part 1

> Compute $\displaystyle\sum_{i=1}^{\sqrt n}f(i)\cdot\left(\sum_{d=\lfloor\sqrt n\rfloor+1}^{\lfloor\frac ni\rfloor}[d\in\mathbb P]f(d)\right)$.

Consider enumerating $i$, then computing the inner part in $O(1)$.

Define $\displaystyle g(t,l)=\sum_{i=1}^l[\forall j\in[1,t],\gcd(i,p_j)=1]f(i)$, which is the sum of $f$ values over numbers in $[1,l]$ that are coprime with $p_1,p_2,\dots,p_t$.

Then Part 1 becomes $\displaystyle\sum_{i=1}^{\sqrt n}f(i)\cdot g\left(m,\left\lfloor\frac ni\right\rfloor\right)$.

The boundary is $g(0,l)=\sum_{i=1}^lf(i)$, and the transition is $g(t,l)=g(t-1,l)-f(p_t)\cdot g\left(t-1,\left\lfloor\frac l{p_t}\right\rfloor\right)$.

There are $O(\sqrt n)$ distinct values of $l$, and for each value we need to enumerate its prime factors, so the complexity is $\displaystyle O\left(\frac{\sqrt n}{\ln\sqrt n}\cdot\sqrt n\right)= O\left(\frac n{\log n}\right)$, which needs optimization.

Notice that when $p_{t+1}^2>l$, the only number satisfying the condition is $1$, so at this point $g(t,l)=f(1)=1$.

Substituting into the recurrence gives: when $p_t^2>l$, $g(t,l)=g(t-1,l)-f(p_t)$.

Therefore, as soon as we find $p_t^2>l$, we stop the transition. Let $t_l$ be the value of $t$ at that point. Then for all $t>t_l$, $g(t,l)=g(t_l,l)-\sum_{i=t_l}^{t-1}f(p_i)$.

By precomputing the prefix sum of $f$ values for primes, $g$ can be computed quickly, and the time complexity is optimized to $O\left(\dfrac{n^{\frac34}}{\log n}\right)$.

### Part 2

> Compute $\displaystyle\sum_{i=1}^n\left[\forall d\in(\sqrt n,n]\cap\mathbb P,d\nmid i\right]f(i)$.

Define $\displaystyle h(t,l)=\sum_{i=1}^l\left[i=\prod_{j=t}^mp_j^{c_j},c_j\in\mathbb N\right]f(i)$, which is the sum of $f$ values over numbers in $[1,l]$ whose prime factors are only among $p_t,p_{t+1},\dots,p_m$.

Part 2 is computing $h(0,n)$.

The boundary is $h(m+1,l)=1$, and the transition is $\displaystyle h(t,l)=h(t+1,l)+\sum_{c\in\mathbb N^*}f(p_t^c)\cdot h\left(t+1,\left\lfloor\frac l{p_t^c}\right\rfloor\right)$.

There are $O(\sqrt n)$ distinct values of $l$, so a direct transition has complexity $\displaystyle O\left(\sqrt n\cdot\frac{\sqrt n}{\ln\sqrt n}\right)= O\left(\frac n{\log n}\right)$, which needs optimization.

Similar to the optimization for $g$, notice that when $p_t>l$, the only number that can be formed from $p_t,p_{t+1},\dots,p_m$ is $1$, so at this point $h(t,l)=f(1)=1$.

Similarly, we derive $\forall p_t^2>l,h(t,l)=h(t+1,l)+f(p_t)$.

Therefore, as soon as we find $p_t^2>l$, we stop the transition. Let $t_l$ be the value of $t$ at that point. When $h$ is used later, we add $\displaystyle\sum_{i=p_{t_l}}^{\min(l,\sqrt n)}[i\in\mathbb P]f(i)$ to the value of $h$ at that point.

The time complexity is optimized to $O\left(\dfrac{n^{\frac34}}{\log n}\right)$.

### Summation

After computing the answers for Part 1 and Part 2, their sum is $\displaystyle\sum_{i=1}^nf(i)$.

## References

[Study Notes on Linear Sieve for Multiplicative Functions, Du Jiao Sieve, and Zhou Sieve | Bill Yang's Blog](https://blog.bill.moe/multiplicative-function-sieves-notes)
