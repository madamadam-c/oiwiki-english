author: Ir1d, HeRaNO, Xeonacid

## Introduction

In fact, sqrt decomposition is an idea rather than a data structure.

From NOIP to NOI to IOI, sqrt-decomposition ideas of various difficulty levels have appeared.

The basic idea of sqrt decomposition is to divide the original data appropriately and preprocess some information on each block after division, thereby achieving better time complexity than a general brute-force algorithm.

The time complexity of sqrt decomposition mainly depends on the block length. In general, the optimal block length for a particular problem, and the corresponding time complexity, can be derived using the AM-GM inequality.

Sqrt decomposition is a very flexible idea. Compared with Fenwick trees and segment trees, its advantage is better generality: it can maintain many kinds of information that Fenwick trees and segment trees cannot.

Of course, its disadvantage is that its asymptotic complexity is not as good as segment trees or Fenwick trees.

Nevertheless, for most problems, sqrt decomposition is still a good choice.

Here are a few examples.

## Range Sum

??? note "Example [LibreOJ 6280 Introduction to Sequence Block Decomposition 4](https://loj.ac/problem/6280)"
    Given a length-$n$ sequence $\{a_i\}$, perform $n$ operations. There are two kinds of operations:
    
    1.  For all numbers in $a_l \sim a_r$, add $x$;
    2.  Compute $\sum_{i=l}^r a_i$.
    
        $1 \leq n \leq 5 \times 10^4$

We divide the sequence into blocks of $s$ elements each, and record the interval sum $b_i$ of each block.

$$
\underbrace{a_1, a_2, \ldots, a_s}_{b_1}, \underbrace{a_{s+1}, \ldots, a_{2s}}_{b_2}, \dots, \underbrace{a_{(s-1) \times s+1}, \dots, a_n}_{b_{\frac{n}{s}}}
$$

The last block may be incomplete (because $n$ is likely not a multiple of $s$), but this does not significantly affect our discussion.

First consider query operations:

-   If $l$ and $r$ are in the same block, directly compute the sum by brute force. Since the block length is $s$, the worst-case complexity is $O(s)$.
-   If $l$ and $r$ are not in the same block, the answer consists of three parts: the incomplete block starting at $l$, several complete blocks in the middle, and the incomplete block ending at $r$. For incomplete blocks, still use the brute-force method above; for complete blocks, directly use the precomputed $b_i$ values. In this case, the worst-case complexity is $O(\dfrac{n}{s}+s)$.

Next consider update operations:

-   If $l$ and $r$ are in the same block, directly update by brute force. Since the block length is $s$, the worst-case complexity is $O(s)$.
-   If $l$ and $r$ are not in the same block, three parts need to be updated: the incomplete block starting at $l$, several complete blocks in the middle, and the incomplete block ending at $r$. For incomplete blocks, brute-force modify every element's value (do not forget to update the interval sum $b_i$); for complete blocks, directly modify $b_i$. In this case, the worst-case complexity is still $O(\dfrac{n}{s}+s)$.

By the AM-GM inequality, when $\dfrac{n}{s}=s$, i.e. $s=\sqrt n$, the time complexity of a single operation is optimal: $O(\sqrt n)$.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/ds/code/decompose/decompose_1.cpp"
    ```

## Range Sum 2

The previous approach has complexity $\Omega(1) , O(\sqrt{n})$.

Here we introduce an $O(\sqrt{n}) - O(1)$ algorithm.

To answer queries in $O(1)$, we can maintain various prefix sums.

However, with updates, these are inconvenient to maintain; we can only maintain prefix sums inside a single block.

We also maintain prefix sums where each whole block is treated as one unit.

Each update costs $O(T+\frac{n}{T})$.

For queries, the range consists of three parts, each of which can be obtained directly through prefix sums, so the time complexity is $O(1)$.

## Blocking Queries

For the same problem, suppose the sequence length is $n$ and there are $m$ operations.

If the number of operations is small, we can record the operations and add their effects during queries.

Assume we record at most $T$ operations. Then updates cost $O(1)$ and queries cost $O(T)$.

After $T$ operations, recompute prefix sums in $O(n)$.

Total complexity: $O(mT+n\frac{m}{T})$.

When $T=\sqrt{n}$, the total complexity is $O(m \sqrt{n})$.

### Other Problems

Sqrt-decomposition ideas can also be applied to other integer-related problems: finding the number of zero elements, finding the first non-zero element, counting elements satisfying some property, and so on.

Some other problems can also be solved by sqrt decomposition, such as maintaining a set that allows adding or deleting numbers, checking whether a number belongs to the set, and finding the $k$-th largest number. To solve this problem, numbers must be stored in increasing order and divided into multiple blocks, each containing $\sqrt{n}$ numbers. Whenever a number is added or deleted, the blocks must be rebuilt by moving numbers across neighboring block boundaries.

A well-known offline algorithm, [Mo's Algorithm](../misc/mo-algo.md), is also implemented based on the idea of sqrt decomposition.

## Exercises

-   [UVa - 12003 - Array Transformer](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3154)
-   [UVa - 11990 Dynamic Inversion](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3141)
-   [SPOJ - Give Away](http://www.spoj.com/problems/GIVEAWAY/)
-   [Codeforces - Till I Collapse](http://codeforces.com/contest/786/problem/C)
-   [Codeforces - Destiny](http://codeforces.com/contest/840/problem/D)
-   [Codeforces - Holes](http://codeforces.com/contest/13/problem/E)
-   [Codeforces - XOR and Favorite Number](https://codeforces.com/problemset/problem/617/E)
-   [Codeforces - Powerful array](http://codeforces.com/problemset/problem/86/D)
-   [SPOJ - DQUERY](https://www.spoj.com/problems/DQUERY)

    **This page is mainly translated from the blog post [Sqrt-декомпозиция](http://e-maxx.ru/algo/sqrt_decomposition) and its English translation [Sqrt Decomposition](https://cp-algorithms.com/data_structures/sqrt_decomposition.html). The Russian version is licensed as Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
