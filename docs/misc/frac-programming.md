author: greyqz, Ir1d, hsfzLZH1, huaruoji, banglee13

Fractional programming is used to find the extremum of a fraction. Formally, given $a_i$ and $b_i$, find a set of $w_i\in\{0,1\}$ that minimizes or maximizes

$$
\displaystyle\frac{\sum\limits_{i=1}^na_i\times w_i}{\sum\limits_{i=1}^nb_i\times w_i}
$$

Informally, these problems are like: each item has two weights $a$ and $b$; choose several items so that $\displaystyle\frac{\sum a}{\sum b}$ is minimized or maximized.

Fractional programming problems usually also have special constraints, such as "the denominator is at least $W$".

## Solving

### Binary Search

The general method for fractional programming is binary search on the answer. Suppose the current binary-searched answer is $\textit{mid}$. Then a feasible set $\{w_i\}$ makes the value at least $\textit{mid}$. Based on this condition, write the inequality and transform it:

$$
\displaystyle
\begin{aligned}
&\frac{\sum a_i\times w_i}{\sum b_i\times w_i}\ge mid\\
\Longrightarrow&\sum a_i\times w_i-mid\times \sum b_i\cdot w_i\ge 0\\
\Longrightarrow&\sum w_i\times(a_i-mid\times b_i)\ge 0
\end{aligned}
$$

Then it is enough to find the maximum value of the expression on the left side of the inequality. If the maximum value is greater than $0$, then $mid$ is feasible; otherwise it is infeasible. The main difficulty in fractional programming is how to find the maximum or minimum value of $\displaystyle \sum w_i\times(a_i-mid\times b_i)$.

### Dinkelbach's Algorithm

The rough idea of Dinkelbach's algorithm[^note1] is to use the answer from the previous round as the new $L$ and iterate continuously until the answer converges.

## Examples

???+ example "[LOJ 149 01 Fractional Programming](https://loj.ac/p/149)"
    There are $n$ items, each with two weights $a$ and $b$. Find a set of $w_i\in\{0,1\}$ such that exactly $k$ of the $w_i$ are $1$, maximizing the value of $\displaystyle\frac{\sum a_i\times w_i}{\sum b_i\times w_i}$.

??? note "Solution"
    Treat $a_i-mid\times b_i$ as the weight of the $i$-th item, and greedily choose the $k$ items with largest weights. If the sum of weights is greater than $0$, it is feasible; otherwise it is infeasible.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/misc/code/frac-programming/frac-1.cpp"
    ```

???+ example "[Luogu 4377 Talent Show G](https://www.luogu.com.cn/problem/P4377)"
    There are $n$ items, each with two weights $a$ and $b$.
    
    You need to determine a set of $w_i\in\{0,1\}$ that maximizes $\displaystyle\frac{\sum w_i\times a_i}{\sum w_i\times b_i}$.
    
    The constraint is $\displaystyle\sum w_i\times b_i \geq W$.

??? note "Solution"
    This problem has the extra constraint that the denominator must be at least $W$, so the greedy algorithm from the previous problem can no longer be used.
    
    Consider 0-1 knapsack. Treat $b_i$ as the weight of the $i$-th item, and $a_i-mid\times b_i$ as the value of the $i$-th item; then the problem becomes knapsack. Thus $dp[n][W]$ is the maximum value.
    
    During DP, the sum of item weights may exceed $W$; in that case, directly treat it as $W$.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/misc/code/frac-programming/frac-2.cpp"
    ```

???+ example "[POJ2728 Desert King](http://poj.org/problem?id=2728)"
    Each edge has two weights $a_i$ and $b_i$. Find a spanning tree $T$ that minimizes $\displaystyle\frac{\sum_{e\in T}a_e}{\sum_{e\in T}b_e}$.

??? note "Solution"
    Treat $a_i-mid\times b_i$ as the weight of each edge; then the minimum spanning tree gives the minimum value. This problem requires solving the minimum spanning tree of a complete graph, so Prim's algorithm should be used.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/misc/code/frac-programming/frac-3.cpp"
    ```

???+ example "[\[HNOI2009\] Minimum Cycle](https://www.luogu.com.cn/problem/P3199)"
    Each edge has weight $w$. Find a cycle $C$ that minimizes $\displaystyle\frac{\sum_{e\in C}w}{|C|}$.

??? note "Solution"
    Treat $a_i-mid$ as the edge weight; then the cycle with minimum weight gives the minimum value.
    
    Because we only need to determine whether the minimum value is less than $0$, we only need to determine whether the graph contains a negative cycle.
    
    This problem also has an $O(nm)$ algorithm. If interested, read [this article](https://www.cnblogs.com/y-clever/p/7043553.html).

??? note "Reference Code"
    ```cpp
    --8<-- "docs/misc/code/frac-programming/frac-4.cpp"
    ```

## Exercises

-   [JSOI2016 Best Team](https://loj.ac/problem/2071)
-   [SDOI2017 Freshman Dance](https://loj.ac/problem/2003)
-   [UVa1389 Hard Life](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=4135)
-   [Luogu P2868 \[USACO07DEC\] Sightseeing Cows G](https://www.luogu.com.cn/problem/P2868)
-   [AtCoder Beginner Contest 324 F - Beautiful Path](https://atcoder.jp/contests/abc324/tasks/abc324_f)

## References and Notes

[^note1]: [Dinkelbach, Werner. "On nonlinear fractional programming." Management science 13.7 (1967): 492-498.](https://doi.org/10.1287/mnsc.13.7.492)
