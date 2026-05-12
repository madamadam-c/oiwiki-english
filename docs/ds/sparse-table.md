## Definition

![Sparse Table diagram](images/st.svg)

An ST table (Sparse Table) is a data structure for solving **overlapping contribution problems**.

???+ note "What is an overlapping contribution problem?"
    An **overlapping contribution problem** means that for an operation $\operatorname{opt}$, if $x\operatorname{opt} x=x$, then the corresponding interval query is an overlapping contribution problem. For example, maximum satisfies $\max(x,x)=x$, and gcd satisfies $\operatorname{gcd}(x,x)=x$, so RMQ and interval GCD are overlapping contribution problems. Interval sum does not have this property: if the preprocessed intervals used for interval sum overlap, the overlapping part is counted twice, which is not what we want. In addition, $\operatorname{opt}$ must also satisfy associativity to be solved with an ST table.

???+ note "What is RMQ?"
    RMQ is the abbreviation of Range Maximum/Minimum Query, meaning interval maximum/minimum query. There are many ways to solve RMQ; see the [RMQ topic](../topic/rmq.md).

## Introduction

???+ example "[Luogu P3865 Template: ST Table & RMQ Problem](https://www.luogu.com.cn/problem/P3865)"
    Given $n$ ($1\le n\le 10^5$) integers and $m$ ($1\le m\le 2\times 10^6$) queries, answer the maximum value in interval $[l,r]$ for each query.

Consider the brute-force approach. For every query, scan the interval $[l,r]$ once and compute the maximum value.

Clearly, this algorithm times out.

## ST Table

An ST table is based on [binary lifting](../basic/binary-lifting.md). It supports $\Theta(n\log n)$ preprocessing and answers each query in $\Theta(1)$, but it does not support modifications.

Based on binary lifting, consider how to compute interval maximum. We can see that if we follow the normal binary lifting process and jump $2^i$ steps at a time, query complexity is still $\Theta(\log n)$, which is not better than a segment tree, while preprocessing is even slower than a segment tree by one step.

We notice that $\max(x,x)=x$, meaning interval maximum has the "overlapping contribution" property. Even if the preprocessed intervals used to solve it overlap, as long as their union is the queried interval, the final answer is correct.

By manually simulating the process, we can see that at most two preprocessed intervals can cover the queried interval. Thus query time can be reduced to $\Theta(1)$, which is very effective for problems with many queries.

The implementation is as follows:

Let $f(i,j)$ denote the maximum value in interval $[i,i+2^j-1]$.

Clearly, $f(i,0)=a_i$.

According to the definition, the second dimension is equivalent to "jumping $2^j-1$ steps" in binary lifting. Following the binary lifting idea, the transition is: $f(i,j)=\max(f(i,j-1),f(i+2^{j-1},j-1))$.

![](./images/st-preprocess-lift.svg)

This is the preprocessing part. For queries, we can implement them simply as follows:

For each query $[l,r]$, split it into two parts: $[l,l+2^s-1]$ and $[r-2^s+1,r]$, where $s=\left\lfloor\log_2(r-l+1)\right\rfloor$. The maximum of the two parts is the answer.

![Query process of an ST table](./images/st-query.svg)

By the argument above for "overlapping contribution problems", because maximum is an overlapping contribution problem, overlap does not affect the interval maximum. Since these two intervals fully cover $[l,r]$, correctness is guaranteed.

???+ example "[Luogu P3865 Template: ST Table & RMQ Problem](https://www.luogu.com.cn/problem/P3865) Reference Implementation"
    === "C style"
        ```cpp
        --8<-- "docs/ds/code/sparse-table/sparse-table_1.cpp"
        ```
    
    === "C++ style"
        ```cpp
        --8<-- "docs/ds/code/sparse-table/sparse-table_2.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/ds/code/sparse-table/sparse-table_1.py"
        ```

## Notes

1.  Input and output data are usually large, so input/output optimization is recommended.

2.  When preprocessing an ST table, one dimension usually has size $\log n$ and the other has size $n$. Prefer making the dimension of size $\log n$ the first dimension to improve cache locality.

3.  Recomputing logarithms each time with [std::log](https://en.cppreference.com/w/cpp/numeric/math/log) is not worthwhile. It is recommended to use built-ins such as `__builtin_clz` or `__lg`. If these built-ins cannot be used, logarithm values can also be preprocessed as follows:

$$
\begin{cases}
\texttt{Logn}[1] \gets 0, \\
\texttt{Logn}\left[i\right] \gets \texttt{Logn}\left[\frac{i}{2}\right] + 1.
\end{cases}
$$

## Maintaining Other Information with ST Tables

Besides RMQ, there are other "overlapping contribution problems". For example, interval bitwise AND, interval bitwise OR, and interval GCD can all be solved efficiently with ST tables.

Note that for interval GCD, the query complexity of an ST table is not better than a segment tree. Let the value domain be $w$; ST table query complexity is $\Theta(\log w)$, while segment tree complexity is $\Theta(\log n+\log w)$, and the value domain is usually larger than $n$. However, ST table preprocessing complexity is not worse than a segment tree, and ST tables are much simpler to program.

On closer analysis, overlapping contribution problems generally have some RMQ-like component. For example, interval bitwise AND takes the minimum on each bit, while interval GCD takes the minimum exponent of every prime factor.

## Summary

ST tables can maintain interval information with "overlapping contribution" well (the operation should also satisfy associativity), with low time complexity and much less code than many other algorithms. However, the information ST tables can maintain is very limited, they do not extend well, and they do not support modifications.

## Exercises

-   [SCOI2007 Rainfall](https://loj.ac/p/2279)

-   [[USACO07JAN] Balanced Lineup](https://www.luogu.com.cn/problem/P2880)

## Appendix: Time Complexity Analysis of ST Table for Interval GCD

During the algorithm, there may be $\Theta(\log n)$ iterations. Each iteration may use the GCD function recursively. Let the value domain be $w$; the worst-case time complexity of the GCD function is $\Omega(\log w)$, so the total time complexity seems to be $O(n\log n\log w)$.

However, during GCD computation, every recursive call except the last one reduces some number in the sequence by at least half. The numbers in the sequence can be halved at most $\log_2 (w^n)=\Theta(n\log w)$ times in total. Thus the recursive part of GCD runs at most $O(n\log w)$ times. Adding the loop part (and the final recursive layer), which is $\Theta(n\log n)$, the final time complexity is $O(n(\log w+\log n))$. Since data can be constructed to make the time complexity $\Omega(n(\log w+\log n))$, the final time complexity is $\Theta(n(\log w+\log n))$.

The query part is easy to analyze: in the worst case, every query asks about the worst pair of numbers, so the time complexity is $\Theta(\log w)$. Therefore, for maintaining interval GCD with an ST table, preprocessing is $\Theta(n(\log n+\log w))$, and each query is $\Theta(\log w)$.

The corresponding segment tree operations are preprocessing $\Theta(n\log w)$ and each query $\Theta(\log n+\log w)$.

This is not a rigorous mathematical proof; a more rigorous proof is attached below:

??? note "More Rigorous Proof"
    Understanding this paragraph may require knowledge of "potential analysis" from [Time Complexity](../basic/complexity.md).
    
    First analyze the time complexity of preprocessing:
    
    Let the "sequence under consideration" be the sequence in the current layer loop during ST table preprocessing. For example, the zeroth layer is the original sequence, and the first layer is the sequence after one iteration of the zeroth layer, i.e. `st[1..n][1]`; denote it by $A$.
    
    Define the potential function as the base-2 logarithm of the product of all numbers in the "sequence under consideration": $\Phi(A)=\log_2\left(\prod\limits_{i=1}^n A_i\right)$.
    
    In one iteration, the time spent is the sum of the iteration loop time and the time spent by GCD. GCD time varies: it may take only two or even one recursive calls in the shortest case, and $O(\log w)$ calls in the longest case. However, during GCD, except for the first and last layers, every recursive call reduces some result in the "sequence under consideration" by at least half. That is, $\Phi(A)$ decreases by at least $1$, and the time used by that recursive layer can be amortized by the potential function.
    
    At the same time, the initial value of $\Phi(A)$ is at most $\log_2 (w^n)=\Theta(n\log w)$, and $\Phi(A)$ never increases. Therefore, the time complexity of ST table preprocessing is $O(n(\log w+\log n))$.
