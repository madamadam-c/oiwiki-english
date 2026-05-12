author: sshwy, ComeIntoCalm

The exponential generating function (EGF) of a sequence $a$ is defined as a formal power series:

$$
\hat{F}(x)=\sum_{n}a_n \frac{x^n}{n!}
$$

## Basic Operations

The addition and subtraction of exponential generating functions are the same as those of ordinary generating functions—adding corresponding coefficients.

Consider multiplication of exponential generating functions. For two sequences $a,b$, with their exponential generating functions $\hat{F}(x),\hat{G}(x)$:

$$
\begin{aligned}
\hat{F}(x)\hat{G}(x)
&=\sum_{i\ge 0}a_i\frac{x^i}{i!}\sum_{j\ge 0}b_j\frac{x^j}{j!}\\
&=\sum_{n\ge 0}x^{n}\sum_{i=0}^na_ib_{n-i}\frac{1}{i!(n-i)!}\\
&=\sum_{n\ge 0}\frac{x^{n}}{n!}\sum_{i=0}^n\binom{n}{i}a_ib_{n-i}
\end{aligned}
$$

Therefore, $\hat{F}(x)\hat{G}(x)$ is the exponential generating function of the sequence:

$$
\left\langle \sum_{i=0}^n \binom{n}{i}a_ib_{n-i} \right\rangle
$$

## Closed Form

We also consider the closed form of exponential generating functions.

The exponential generating function of the sequence $\langle 1,1,1,\cdots\rangle$ is:

$$
\hat{F}(x) = \sum_{n \ge 0}\frac{x^n}{n!} = \mathrm{e}^x
$$

Because expanding $\mathrm{e}^x$ at $x = 0$ gives its infinite series form.

Similarly, the exponential generating function of the geometric progression $\langle 1,p,p^2,\cdots\rangle$ is:

$$
\hat{F}(x) = \sum_{n\ge 0}\frac{p^nx^n}{n!}=\mathrm{e}^{px}
$$

## Exponential Generating Function vs Ordinary Generating Function

How to understand exponential generating functions? We define the exponential generating function of sequence $a$ as:

$$
F(x)=\sum_{n\ge 0}a_n\frac{x^n}{n!}
$$

But $F(x)$ is actually the ordinary generating function of the sequence $\left\langle \dfrac{a_n}{n!} \right\rangle$.

These two understandings are both fine. In other words, different generating functions are just different ways of understanding the problem.

## Combinatorial Meaning of Polynomial exp in EGF

If you haven't studied polynomial exp yet, skip here first. This is a meaning that arises from understanding exp, and in a sense can deepen the understanding of EGF.

In EGF, $f^n(x)$'s $f$ is by default an EGF. So we first consider the product of any two EGFs:

$$
\hat{H}(x) = \hat{F}(x)\hat{G}(x) = \sum_{n\geq 0} \left[ \sum_{i = 0}^n\binom {n}{i}f_ig_{n-i} \right] \frac{x^n}{n!}
$$

The $[x^k]\hat{H}(x)$ obtained from multiplying two EGFs is actually a convolution. And $[x^k]\hat{H}(x)$ obtained from multiplying multiple EGFs is actually the sum of coefficients for each case where we select one term $x^{a_i}$ from each EGF such that $\sum_ia_i=k$.

From the perspective of sets, this is the number of ways to partition $n$ labeled elements into $k>0$ labeled sets.

> If $k=0$, the coefficient is obviously the product of constants of each term in the original EGF. However, some requirements in polynomial exp cause $f(x)$'s constant term to be $0$. The specific reason is explained below.

In the definition of multinomial coefficients (specifically refer to the combinatorial meaning of multinomial coefficients in combinatorics), sets are ordered by default. But in $\exp(f(x))$, $f^k(x)$, the EGF obtained from multiplying $k$ copies of $f(x)$ is the same, while set partitions are clearly unordered. So its coefficient should be multiplied by $\dfrac{1}{k!}$.

Let $F_k(n)$ be the number of ways to partition $n$ labeled elements into $k$ non-empty unordered sets (non-empty because of $\exp$), and $f_i$ be the number of ways for a specific combinatorial structure on a finite set of $i$ elements (it is the original EGF, counting schemes for the set elements, depending only on the size of the set). Then $F_k(n)$:

$$
F_k(n)=\frac{n!}{k!}\sum_{\sum_{i}^ka_i=n}\prod_{j=1}^{k}\frac{f_{a_j}}{a_j!}
$$

Let the EGF of $f_n$ be $\hat{F}(x)$, i.e.:

$$
\hat{F}(x) = \sum_{n \geq 0} f_n\frac{x^n}{n!}
$$

Let the EGF of $F_k(n)$ be $G_k(x)$, then:

$$
\begin{aligned}
G_k(x)&=\sum_{n \geq 0} F_k(n)\frac{x^n}{n!}\\
&=\sum_{n \geq 0} x^n\frac{1}{k!}\sum_{\sum_i^k a_i=n}\prod_{j=1}^{k}\frac{f_{a_j}}{a_j!}\\
&=\frac{1}{k!}\sum_{n \geq 0}\sum_{\sum_i^k a_i=n}\prod_{j=1}^{k}\frac{f_{a_j}x^{a_j}}{a_j!}\\
&=\frac{1}{k!}\hat{F}^k(x)
\end{aligned}
$$

For all $k \geq 0$:

$$
\sum_{k \geq 0}G_k(x) = \sum_{k \geq 0}\frac{\hat{F}^k(x)}{k!} = \exp{\hat{F}(x)}
$$

The above is a direct combinatorial formula understanding. We can also prove the relationship between $\exp(f(x))$ and $f(x)$ from the perspective of recurrence.

Similarly, let $F_k(n)$ be the number of ways to partition $n$ labeled elements into $k$ non-empty sets (unlabeled), $g_i$ be the number of schemes for a set of $i$ elements (same meaning as $f_i$ above), and let $G(x)$ be the EGF of $\{g_i\}$, $H_k(x)$ be the EGF of $\{F_k(n)\}$.

Among $n$ elements, selecting $i$ elements as a separately partitioned set has $g_i$ schemes, and the remaining $n-i$ elements form $k-1$ sets with $F_{k-1}(n-i)$ schemes. But in the final partition scheme, each set in a scheme will be enumerated as a separately partitioned set, so it's counted $k$ times, thus we need to divide by $k$.

$$
\begin{aligned}
H_k(x) &= \sum_{n\ge 0}\cfrac{x^n}{n!}F_k(n)\\
&=\sum_{n\ge 0}\cfrac{x^n}{n!}\sum_{i=1}^{n-k+1}\binom n {i} F_{k-1}(n-i)\times g_i\times \cfrac{1}{k}\\
&=\cfrac{1}{k}\sum_{n\ge 0}\cfrac{x^n}{n!}\sum_{i=0}^{n}\binom n {i}F_{k-1}(n-i)\times g_i\\
&=\cfrac{1}{k}\cdot   H_{k-1}(x)G(x)
\end{aligned}
$$

The upper bound comes from non-empty set partition: $n-(k-1)\geq i$ (the first $k-1$ sets each have at least one element). But if we exceed the enumeration upper bound and involve $F_{k-1}(n-i)$, setting it to 0 has no effect.

After getting the recurrence formula, it can be recursively expanded, with the boundary being $k=1$ where $H_1(x)=G(x)$.

$$
\begin{aligned}
H_k(x) &= \cfrac{1}{k}\cdot   H_{k-1}(x)G(x)\\
&= \cfrac{1}{k}\cdot\cfrac{1}{k-1}\cdot   H_{k-2}(x)G^2(x)\\
&=\cdots \\
&= \cfrac{1}{k}\cdot\cfrac{1}{k-1} \cdots\cfrac{1}{2}\cdot H_{1}(x)G^{k-1}(x)\\
&= \cfrac{1}{k!}G^{k}(x)
\end{aligned}
$$

Similarly:

$$
\begin{aligned}
\sum_{k\ge 0}H_k(x)=\sum_{k\ge 0}\cfrac{G^k(x)}{k!}=\exp G(x)
\end{aligned}
$$

Obviously, **defining as non-empty set partition** ($g_0=0$) is consistent with its meaning. If **it includes the empty set** ($g_0=1$), then in $[x^n]G^k$ there will be contributions from $[x^n]G^y, y>k$ (selecting the constant term in at least one $G$), causing double counting, and we can't get the desired result.

From the perspective of recurrence, the product of multiple EGFs can also be seen as a knapsack-like combination (the process of merging two counting objects).

Summarizing the meaning of polynomial exp: the number of cases in the generating set family of sets composed of labeled elements, or the total number of schemes for partitioning into any number of non-empty subsets.

## Permutations and Circular Permutations

The exponential generating function for the number of permutations of length $n$ is:

$$
\hat{P}(x)=\sum_{n\ge 0}\frac{n!x^n}{n!}=\sum_{n\ge 0}x^n=\frac{1}{1-x}
$$

The definition of circular permutation is the number of ways to arrange $1,2,\cdots,n$ in a ring. That is, schemes after rotation are equivalent (but reflection is not equivalent).

The number of circular permutations of $n$ numbers is obviously $(n-1)!$. Therefore, the exponential generating function for the number of circular permutations of $n$ numbers is:

$$
\hat{Q}(x)=\sum_{n\ge 1}\frac{(n-1)!x^n}{n!}=\sum_{n\ge 1}\frac{x^n}{n}=-\ln(1-x)=\ln\left( \frac{1}{1-x} \right)
$$

That is, $\exp \hat{Q}(x)=\hat{P}(x)$. But this is only mathematical derivation. How do we intuitively understand that the exp of the EGF of circular permutations is the EGF of permutations?

A permutation consists of several permutation cycles. For example, $p=[4,3,2,5,1]$ has two permutation cycles:

![](./images/p1.png)

(That is, we draw directed edges from $p_i$ to $i$)

And different permutation cycles lead to different permutations. For example, changing the second permutation cycle to:

![](./images/p2.png)

Then its corresponding permutation is $[5,3,2,1,4]$.

That is, the number of schemes for permutations of length $n$ is:

1.  Divide $1,2,\cdots,n$ into several sets.
2.  Each set forms a permutation cycle.

The number of schemes for a set of numbers forming a permutation cycle is clearly the number of circular permutation schemes for that set's size. Therefore, the number of schemes for permutations of length $n$ is: divide $1,2,\cdots,n$ into several sets, multiply the circular permutation schemes of each set.

This is the intuitive understanding of polynomial exp.

Extension:

-   If the EGF of labeled trees with $n$ nodes is $\hat{F}(x)$, then the EGF of labeled forests with $n$ nodes is $\exp \hat{F}(x)$—intuitively, split $n$ nodes into several sets, and multiply the schemes of each set forming a spanning tree.
-   If the EGF of labeled connected undirected graphs with $n$ nodes is $\hat{F}(x)$, then the EGF of labeled undirected graphs with $n$ nodes is $\exp \hat{F}(x)$, which can be easily computed:

    $$
    \exp \hat{F}(x)=\sum_{n\ge 0}2^{\binom{n}{2}}\frac{x^n}{n!}
    $$

    Therefore, to compute the former, just one polynomial $\ln$ is needed.

Now let's look at some applications of exponential generating functions.

### Derangements

???+ note "Derangements"
    Define a derangement of length $n$ as a permutation satisfying $p_i\ne i$.
    
    Find the exponential generating function for derangements.

From the perspective of permutation cycles, a derangement is a permutation with no self-loops in permutation cycles. That is, there is no permutation cycle of length 1. The latter's exponential generating function is:

$$
\sum_{n\ge 2}\frac{x^n}{n}=-\ln\left(1-x\right)-x
$$

Therefore, the exponential generating function for derangements is $\exp(-\ln(1-x)-x)$.

### Fixed Points

???+ note "[Fixed Points](https://www.51nod.com/Html/Challenge/Problem.html#problemId=1728)"
    Problem: Find how many mappings $f:\{1,2,\cdots,n\}\to \{1,2,\cdots,n\}$ satisfy:
    
    $$
    \underbrace{f\circ f\circ\cdots\circ f}_{k}=\underbrace{f\circ f\circ\cdots\circ f}_{k-1}
    $$
    
    $nk\le 2\times 10^6,1\le k\le 3$.

Consider connecting $i$ to $f(i)$. This means that starting from any $i$ and going $k$ steps reaches the same point as going $k-1$ steps. That is, the cycle in the rooted forest is a self-loop with depth not exceeding $k$ (root node depth is 1). Treating this rooted forest as a rooted tree is the same. So our problem becomes: counting forests of rooted trees with $n$ labeled nodes and depth not exceeding $k$.

Consider rooted trees with $n$ labeled nodes and depth not exceeding $k$, assuming its generating function is:

$$
\hat{F_k}(x)=\sum_{n\ge 0}f_{n,k}\frac{x^n}{n!}
$$

Consider solving $\hat{F_k}(x)$ recursively. A rooted tree with depth not exceeding $k$ is actually several rooted trees with depth not exceeding $k-1$, connecting all their root nodes to one node. Therefore:

$$
\hat{F_k}(x)=x\exp \hat{F}_{k-1}(x)
$$

Then the answer's exponential generating function is $\exp \hat{F}_k(x)$. Find its $n$-th term.

### Lust

???+ note "[Lust](https://codeforces.com/contest/891/problem/E)"
    Given a sequence of $n$ numbers $a_1,a_2,\cdots,a_n$, and a variable $s$ initialized to $0$, repeat the following operation $k$ times:
    
    -   Randomly select an $x$ from $1,2,\cdots,n$ with equal probability.
    -   Let $s$ add $\prod_{i\ne x}a_i$.
    -   Let $a_x$ decrement by $1$.
    
    Find the expected value of $s$ after $k$ operations.
    
    $1\le n\le 5000,1\le k\le 10^9,0\le a_i\le 10^9$.

Assume after $k$ operations, $a_i$ decreases by $b_i$. Then actually:

$$
s=\prod_{i=1}^n a_i-\prod_{i=1}^n(a_i- b_i)
$$

Therefore, our problem actually becomes: find the expected value of $\prod_{i=1}^n (a_i- b_i)$ after $k$ operations.

Consider calculating the sum of $\prod_{i=1}^n (a_i- b_i)$ for each scheme, and finally divide by $n^k$.

And in the sequence of $k$ operations, the number of schemes where $i$ appears $b_i$ times is:

$$
\frac{k!}{b_1!b_2!\cdots b_n!}
$$

This is similar to the coefficient of exponential generating function multiplication.

Let $a_j$'s exponential generating function be:

$$
F_j(x)=\sum_{i\ge 0}(a_j-i)\frac{x^i}{i!}
$$

Then the answer is:

$$
[x^k]\prod_{j=1}^nF_j(x)
$$

To quickly compute the answer, we need to transform $F_j(x)$ into closed form:

$$
\begin{aligned}
F_j(x)&=\sum_{i\ge 0}a_j\frac{x^i}{i!}-\sum_{i\ge 1}\frac{x^i}{(i-1)!}\\
&=a_j\mathrm{e}^x-x\mathrm{e}^x\\
&=(a_j-x)\mathrm{e}^x
\end{aligned}
$$

Therefore, we get:

$$
\prod_{j=1}^nF_j(x)=\mathrm{e}^{nx}\prod_{j=1}^n(a_j-x)
$$

Where $\prod_{j=1}^n(a_j-x)$ is an $n$-degree polynomial, which can be computed by brute force. Assuming its expansion is $\sum_{i=0}^nc_ix^i$, then:

$$
\begin{aligned}
\prod_{j=1}^nF_j(x)
&=\left(\sum_{i\ge 0} \frac{n^ix^i}{i!}\right)\left(\sum_{i=0}^nc_ix^i\right)\\
&=\sum_{i\ge 0}\sum_{j=0}^i c_jx^j\frac{n^{i-j}x^{i-j}}{(i-j)!}\\
&=\sum_{i\ge 0}\frac{x^{i}}{i!}\sum_{j=0}^i n^{i-j}i^{\underline{j}}c_j
\end{aligned}
$$

Compute the coefficient of $x^k$ in this polynomial.