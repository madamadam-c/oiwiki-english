## Introduction

The Lindström–Gessel–Viennot lemma, i.e., the LGV lemma, can be used to solve problems such as counting non-intersecting paths on a directed acyclic graph.

Prerequisites: Basic concepts in [Graph Theory](./concept.md), [Matrices](../math/linear-algebra/matrix.md), and [Gaussian elimination for determinants](../math/numerical/gauss.md).

The LGV lemma only applies to **directed acyclic graphs**.

## Definitions

$\omega(P)$ denotes the product of edge weights along path $P$. (For path counting, you can set all edge weights to $1$.) (In fact, edge weights can be generating functions.)

$e(u, v)$ denotes the sum of $\omega(P)$ over **every** path $P$ from $u$ to $v$, i.e., $e(u, v)=\sum\limits_{P:u\rightarrow v}\omega(P)$.

The set of sources $A$ is a subset of vertices of a directed acyclic graph with size $n$.

The set of sinks $B$ is also a subset of vertices of a directed acyclic graph with size $n$.

A set $S$ of non-intersecting paths from $A$ to $B$: $S_i$ is a path from $A_i$ to $B_{\sigma(S)_i}$ ($\sigma(S)$ is a permutation), and for any $i\ne j$, $S_i$ and $S_j$ share no common vertices.

$t(\sigma)$ denotes the number of inversions in permutation $\sigma$.

## Lemma

$$
M = \begin{bmatrix}e(A_1,B_1)&e(A_1,B_2)&\cdots&e(A_1,B_n)\\
e(A_2,B_1)&e(A_2,B_2)&\cdots&e(A_2,B_n)\\
\vdots&\vdots&\ddots&\vdots\\
e(A_n,B_1)&e(A_n,B_2)&\cdots&e(A_n,B_n)\end{bmatrix}
$$

$$
\det(M)=\sum\limits_{S:A\rightarrow B}(-1)^{t(\sigma(S))}\prod\limits_{i=1}^n \omega(S_i)
$$

where $\sum\limits_{S:A\rightarrow B}$ iterates over every set $S$ of non-intersecting paths from $A$ to $B$ satisfying the conditions above.

### Proof

From the definition of the determinant, we have

$$
\begin{align}
\det(M)&=\sum_{\sigma}(-1)^{t(\sigma)}\prod_{i=1}^n e(a_i,b_{\sigma(i)})\\
&=\sum_{\sigma}(-1)^{t(\sigma)}\prod_{i=1}^n \sum_{P:a_i\to b_{\sigma(i)}} \omega(P)
\end{align}
$$

Observe that $\prod\limits_{i=1}^n \sum\limits_{P:a_i\to b_{\sigma(i)}} \omega(P)$ is actually the sum of $\omega(P)$ over all sets of paths $P$ from $A$ to $B$ with permutation $\sigma$.

$$
\begin{align}
&\sum_{\sigma}(-1)^{t(\sigma)}\prod_{i=1}^n \sum_{P:a_i\to b_{\sigma(i)}} \omega(P)\\
=&\sum_{\sigma}(-1)^{t(\sigma)}\sum_{P=\sigma}\omega(P)\\
=&\sum_{P:A\to B}(-1)^{t(\sigma)}\prod_{i=1}^n \omega(P_i)
\end{align}
$$

Here $P$ is any set of paths.

Let $U$ be a set of non-intersecting paths and $V$ be a set of intersecting paths,

$$
\begin{align}
&\sum_{P:A\to B}(-1)^{t(\sigma)}\prod_{i=1}^n \omega(P_i)\\
=&\sum_{U:A\to B}(-1)^{t(U)}\prod_{i=1}^n \omega(U_i)+\sum_{V:A\to B}(-1)^{t(V)}\prod_{i=1}^n \omega(V_i)
\end{align}
$$

Suppose $P$ contains an intersecting pair $P_i:a_1 \to u \to b_1, P_j:a_2 \to u \to b_2$. Then there must exist a corresponding intersecting pair $P_i'=a_1\to u\to b_2, P_j'=a_2\to u\to b_1$, where all other paths in $P'$ are the same as in $P$. We have $\omega(P)=\omega(P'), t(P)=t(P')\pm 1$.

Therefore, we have $\sum\limits_{V:A\to B}(-1)^{t(\sigma)}\prod\limits_{i=1}^n \omega(V_i)=0$.

Thus $\det(M)=\sum\limits_{U:A\to B}(-1)^{t(U)}\prod\limits_{i=1}^n \omega(U_i)$.

Q.E.D.[^1]

## Example Problems

???+ note "Example 1 [CF348D Turtles](https://codeforces.com/contest/348/problem/D)"
    Problem: There is an $n\times m$ grid where some cells are walkable and others are not. A turtle starting at $(x, y)$ can only move to $(x+1, y)$ or $(x, y+1)$. Find the number of non-intersecting paths from $(1, 1)$ to $(n, m)$ modulo $10^9+7$. $2\le n,m\le3000$.

    This is a straightforward application of the LGV lemma. Consider all valid paths and notice that any path starting from $(1,1)$ must pass through $A=\{(1,2), (2,1)\}$, and any path ending at $(n,m)$ must pass through $B=\{(n-1, m), (n, m-1)\}$. So $A$ and $B$ are immediately determined. Applying the LGV lemma, the answer is:

    $$
    \begin{vmatrix}
    f(a_1, b_1) & f(a_1, b_2) \\
    f(a_2, b_1) & f(a_2, b_2)
    \end{vmatrix} = f(a_1, b_1)\times f(a_2, b_2) - f(a_1, b_2)\times f(a_2, b_1)
    $$

    where $f(a, b)$ is the number of paths from $a$ to $b$ in the graph. Path counting with obstacles can be done with a simple $O(nm)$ DP, so $f$ is easy to compute. The overall complexity is $O(nm)$.

    ??? note "Reference Code"
        ```cpp
        --8<-- "docs/graph/code/lgv/lgv_2.cpp"
        ```

???+ note "Example 2 [HDU 5852 Intersection is not allowed!](https://acm.hdu.edu.cn/showproblem.php?pid=5852)"
    Problem: There is an $n\times n$ chessboard. A piece at $(x, y)$ can only move to $(x, y+1)$ or $(x + 1, y)$. There are $k$ pieces, with the $i$-th piece initially at $(1, a_i)$ and ultimately moving to $(n, b_i)$. Paths must be pairwise non-intersecting. Find the number of ways modulo $10^9+7$. $1\le n\le 10^5$, $1\le k\le 100$, with $1\le a_1<a_2<\dots<a_n\le n$, $1\le b_1<b_2<\dots<b_n\le n$.

    Observe that if paths are non-intersecting, then piece $i$ must go from $a_i$ to $b_i$. Therefore, in the LGV lemma, we have $\sigma(S)_i=i$, and we don't need to consider sign issues. Setting all edge weights to $1$, we can directly apply the lemma.

    The number of paths from $(1, a_i)$ to $(n, b_j)$ is equivalent to choosing $n-1$ downward steps from $n-1+b_j-a_i$ steps, so $e(A_i, B_j)=\binom{n-1+b_j-a_i}{n-1}$.

    The determinant can be computed using Gaussian elimination.

    The complexity is $O(n+k(k^2 + \log p))$, where $\log p$ is the complexity for modular inverses.

    ??? note "Reference Code"
        ```cpp
        --8<-- "docs/graph/code/lgv/lgv_1.cpp"
        ```

## References

[^1]: The proof is from [Zhihu - LGV Lemma Proof](https://zhuanlan.zhihu.com/p/517819133)