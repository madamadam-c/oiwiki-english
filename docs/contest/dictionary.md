Prerequisite knowledge: [Block decomposition](../ds/decompose.md).

Naive precomputation refers to calculating the answers for all possible inputs during a contest and saving them, then storing the answers in an array in the code and directly outputting them.

Note that this technique is only applicable when the input value range is small (e.g., the input is a single number with a very small range). Otherwise, it may cause issues such as excessive code length, MLE, or the precomputation taking too long.

???+ note "Example Problem"
Define $f(x)$ as the number of $1$s in the binary representation of integer $x$. Given a positive integer $n$ ($n\leq 10^9$), output $\sum_{i=1}^n f^2(i)$.

If we were to output $f(n)$ for every $n$, besides potentially causing MLE, the code might also exceed the maximum code length limit, resulting in a compilation failure.

We consider optimizing this answer table. Using the idea of [block decomposition](../ds/decompose.md), we set a reasonable step size $m$ (this step size is generally determined by the code length), and for the $i$-th block, we compute:

$$
\sum_{k=\frac{n}{m}(i-1)+1}^{\frac{ni}{m}} f^2(k)
$$

Then, when outputting the answer, we process it using the block decomposition approach. That is, for complete blocks, we use the precomputed values, and for partial blocks, we compute the answer by brute force.

In general, such problems involve computing individual function values $f(x)$ quickly, but require summing (multiplying, or performing some quickly mergeable operation on) a large number of function values, where straightforward enumeration would exceed the time limit. When a standard approach cannot be found, segmented precomputation is a good alternative.

???+ note "Notes"
When the exponent in the problem above is not constant but has a small range, precomputation can also be considered.

### Example Problems

[「BZOJ 3798」Special Primes](https://hydro.ac/p/bzoj-P3798): Find how many primes in the interval $[l,r]$ can be decomposed into the sum of squares of two positive integers.

[「Luogu P1822」Magic Fingerprint](https://www.luogu.com.cn/problem/P1822)
