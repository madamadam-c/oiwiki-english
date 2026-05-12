## Introduction

Vandermonde's convolution is an identity for combining binomial coefficients, primarily used in formula derivations in combinatorics.

## Vandermonde's Convolution Formula

$$
\sum_{i=0}^k \binom{n}{i} \binom{m}{k-i} = \binom{n+m}{k}
$$

### Proof

Consider proving it using the binomial theorem:

$$
\begin{aligned}
\sum_{k=0}^{n+m} \binom{n+m}{k} x^k &= (x+1)^{n+m}\\
&= (x+1)^n (x+1)^m\\
&= \sum_{r=0}^n \binom{n}{r} x^r \sum_{s=0}^m \binom{m}{s} x^s\\
&= \sum_{k=0}^{n+m} \sum_{r=0}^k \binom{n}{r} \binom{m}{k-r} x^k
\end{aligned}
$$

That is:

$$
\binom{n+m}{k} = \sum_{r=0}^k \binom{n}{r} \binom{m}{k-r}
$$

If we consider a combinatorial proof:

To select $k$ numbers from a set of size $n+m$, this can be equivalent to splitting the size $(n+m)$ set into two sets of sizes $n$ and $m$, then selecting $i$ numbers from $n$ and $k-i$ numbers from $m$. Since we have an enumeration over $i$, we only need to consider one split method, as different split methods are equivalent.

## Corollaries

### Corollary 1 and Proof

$$
\sum_{i=-r}^{s} \binom{n}{r+i} \binom{m}{s-i} = \binom{n+m}{r+s}
$$

The proof is similar to the original formula.

### Corollary 2 and Proof

$$
\sum_{i=1}^n \binom{n}{i} \binom{n}{i-1} = \binom{2n}{n-1}
$$

Based on basic combinatorial knowledge, we derive:

$$
\sum_{i=1}^n \binom{n}{i} \binom{n}{i-1} = \sum_{i=0}^{n-1} \binom{n}{i+1} \binom{n}{i} = \sum_{i=0}^{n-1} \binom{n}{n-1-i} \binom{n}{i} = \binom{2n}{n-1}
$$

### Corollary 3 and Proof

$$
\sum_{i=0}^n \binom{n}{i}^2 = \binom{2n}{n}
$$

Based on basic combinatorial knowledge, we derive:

$$
\sum_{i=0}^n \binom{n}{i}^2 = \sum_{i=0}^n \binom{n}{i} \binom{n}{n-i} = \binom{2n}{n}
$$

### Corollary 4 and Proof

$$
\sum_{i=0}^m \binom{n}{i} \binom{m}{i} = \binom{n+m}{m}
$$

Based on basic combinatorial knowledge, we derive:

$$
\sum_{i=0}^m \binom{n}{i} \binom{m}{i} = \sum_{i=0}^m \binom{n}{i} \binom{m}{m-i} = \binom{n+m}{m}
$$

Among these, $\binom{n+m}{m}$ is the more familiar number of paths in grid graph counting. So we can consider its combinatorial proof.

In a grid graph, from $(0, 0)$ to $(n, m)$, we take $n+m$ steps in total. Assuming $(0, 0)$ is at the top-left of the grid graph, where we take $n$ steps down and $m$ steps right, the number of ways is $\binom{n+m}{m}$.

From another perspective, we split the $n+m$ steps into two parts: first take $n$ steps, then take $m$ steps. If there are $i$ steps to the right among the $n$ steps, then there are $m-i$ steps to the right among the $m$ steps. This proves it.

## Exercises

-   [CF785D Anton and School - 2](https://codeforces.com/problemset/problem/785/D)

-   [Luogu P2791 幼儿园篮球题](https://www.luogu.com.cn/problem/P2791)

## References and Notes

1.  [Vandermonde's Convolution Formula](https://www.cut-the-knot.org/arithmetic/algebra/VandermondeConvolution.shtml)