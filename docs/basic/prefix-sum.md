## Introduction

Prefix sum and difference are commonly used techniques in programming contests. The former is used for quickly computing range sums, and the latter is used for efficiently performing range updates.

???+ tip "Convention"
    For convenience, this article assumes that the array $\{a_i\}$ is 1-indexed, and we define $a_0 = 0$.

## Prefix Sum

A prefix sum can be simply understood as "the sum of the first $n$ elements of a sequence," and it is an important preprocessing technique.

### One-Dimensional Prefix Sum

For a sequence $\{a_i\}$ of length $n$, if you need to query the sum of elements in the range $[l, r]$ multiple times, you can consider using a prefix sum. The prefix sum of a sequence is defined as

$$
S_{i} = \sum_{j=1}^i a_j.
$$

It can be computed iteratively using the recurrence

$$
S_0 = 0,~ S_i = S_{i-1} + a_i.
$$

To query the sum of elements in range $[l, r]$, you only need to compute the difference

$$
S([l,r]) = S_r - S_{l-1}.
$$

Thus, with $O(n)$ preprocessing, a single range sum query can be reduced to $O(1)$ time.

???+ example "Reference Implementation"
    === "C++"
        ```cpp
        --8<-- "docs/basic/code/prefix-sum/prefix-sum_1.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/basic/code/prefix-sum/prefix-sum_1.py:core"
        ```

C++ standard library provides the prefix sum function [`std::partial_sum`](https://en.cppreference.com/w/cpp/algorithm/partial_sum), defined in the header `<numeric>`. Since C++17, the standard library also provides [`std::inclusive_scan`](https://en.cppreference.com/w/cpp/algorithm/inclusive_scan), which offers the same functionality, also defined in the header `<numeric>`.

### Two-Dimensional / Multi-Dimensional Prefix Sum

Extending one-dimensional prefix sum to multiple dimensions gives us multi-dimensional prefix sums. There are two common methods for computing multi-dimensional prefix sums.

#### Based on Inclusion-Exclusion Principle

This method is commonly used for two-dimensional prefix sums. Given a 2D array $A$ of size $m \times n$, we want to compute its prefix sum $S$. Then $S$ is also a 2D array of size $m \times n$, and

$$
S_{i,j} = \sum_{i'\le i}\sum_{j'\le j}A_{i',j'}.
$$

Analogous to the one-dimensional case, $S_{i,j}$ should be computable from $S_{i-1,j}$ or $S_{i,j-1}$ to avoid redundant computation of previous sums. However, directly adding $S_{i-1,j}$ and $S_{i,j-1}$, along with $A_{i,j}$, would double-count the overlapping portion $S_{i-1,j-1}$, so this portion needs to be subtracted. This is the [inclusion-exclusion principle](../math/combinatorics/inclusion-exclusion-principle.md). From this, we get the following recurrence:

$$
S_{i,j} = A_{i,j} + S_{i-1,j} + S_{i,j-1} - S_{i-1,j-1}. 
$$

In implementation, simply iterate over all $(i, j)$ pairs to compute the sum.

???+ note "Example"
    Consider a concrete example.
    
    ![Two-dimensional prefix sum example](./images/prefix-sum-2d.svg)
    
    Here, $S$ is the prefix sum of matrix $A$. By definition, $S_{3,3}$ is the sum of the submatrix in the dashed box in the left figure. Also, $S_{3,2}$ is the sum of the blue submatrix, and $S_{2,3}$ is the sum of the red submatrix. Their overlapping portion has sum $S_{2,2}$. Thus, if we directly add $S_{3,2}$ and $S_{2,3}$, we would double-count $S_{2,2}$, so we should have
    
    $$
    S_{3,3} = A_{3,3} + S_{2,3} + S_{3,2} - S_{2,2} = 5 + 18 + 15 - 9 = 29.
    $$

Similarly, after preprocessing the 2D prefix sum, to query the sum of a submatrix with top-left corner $(i_1, j_1)$ and bottom-right corner $(i_2, j_2)$, we can compute

$$
S_{i_2,j_2} - S_{i_1-1,j_2} - S_{i_2,j_1-1} + S_{i_1-1,j_1-1}.
$$

This can be done in $O(1)$ time.

In the 2D case, the time complexity of the above algorithm is simply $O(mn)$, which is linear in the size of the given array. However, when the dimension $k$ increases, the number of terms in the inclusion-exclusion principle grows exponentially, and the time complexity becomes $O(2^k N)$, where $k$ is the number of dimensions and $N$ is the size of the given array. Therefore, this algorithm is no longer applicable.

???+ example "[Luogu P1387 Maximum Square](https://www.luogu.com.cn/problem/P1387)"
    In an $n\times m$ matrix containing only $0$ and $1$, find the largest square that does not contain any $0$, and output its side length.

??? note "Reference Code"
    === "C++"
        ```cpp
        --8<-- "docs/basic/code/prefix-sum/prefix-sum_2.cpp:full-text"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/basic/code/prefix-sum/prefix-sum_2.py:full-text"
        ```

#### Dimension-by-Dimension Prefix Sum

For the general case, given a $k$-dimensional array $A$ of size $N$, we also want to compute its prefix sum $S$. Here,

$$
S_{i_1,\cdots,i_k} = \sum_{i'_1\le i_1}\cdots\sum_{i'_k\le i_k} A_{i'_1,\cdots,i'_k}.
$$

From the above formula, we can see that a $k$-dimensional prefix sum equals $k$ successive summations. Therefore, a straightforward algorithm is: each time consider only one dimension, fix all other dimensions, and compute several one-dimensional prefix sums. After summing over all $k$ dimensions, we get the $k$-dimensional prefix sum.

??? example "Reference Implementation for 3D Prefix Sum"
    ```cpp
    --8<-- "docs/basic/code/prefix-sum/prefix-sum_4.cpp:core"
    ```

Since each dimension only requires a single pass through the entire array, the algorithm has a time complexity of $O(kN)$, which is usually acceptable.

#### Special Case: Subset Sum DP

Cases with large dimensions frequently appear in a class of problems called **Subset Sum** (SOS). This is a special case of high-dimensional prefix sum.

The problem description is as follows. Consider a function $f$ defined on all subsets of a set of size $n$. We want to compute its subset sum function $g$, which satisfies

$$
g(S) = \sum_{T\subseteq S}f(T).
$$

That is, $g(S)$ equals the sum of $f(T)$ over all subsets $T \subseteq S$.

First, the subset sum problem can be expressed in the form of high-dimensional prefix sum. Note that subsets of $S$ can be represented as 0-1 strings of length $n$ using state compression. If we treat each bit of the string as a dimension of the array index, then $f$ is actually an $n$-dimensional array, and each dimension's index must be in $\{0, 1\}$. Also, the subset relation is equivalent to the index comparison relation, that is,

$$
T\subseteq S \iff \forall i(t_i \le s_i). 
$$

Therefore, summing over subsets is equivalent to computing the prefix sum of this $n$-dimensional array.

Now, we can directly use the dimension-by-dimension prefix sum method described earlier to compute the subset sum. The time complexity is $O(n2^n)$.

??? example "Reference Implementation"
    ```cpp
    --8<-- "docs/basic/code/prefix-sum/prefix-sum_5.cpp:core"
    ```

The inverse operation of subset sum needs to be performed using the [inclusion-exclusion principle](../math/combinatorics/inclusion-exclusion-principle.md). The subset sum problem is also a necessary step in fast Möbius transform.

### Prefix Sum on Trees

One-dimensional prefix sum can also be extended to rooted trees (with root at $1$). By preprocessing prefix sums, we can quickly compute the sum of weights along a path on the tree.

#### Node Weights

First, we discuss the case where weights are stored at nodes. Let the weight at node $x$ be $a_x$. We can compute the sum of node weights on the path from the root to node $x$ using the recurrence

$$
S_1 = a_1,~ S_{x} = S_{\operatorname{fa}(x)} + a_x
$$

where $\operatorname{fa}(x)$ denotes the parent of $x$. After preprocessing the prefix sum, the sum of node weights on the path connecting node $x$ and $y$ can be computed as

$$
S_x + S_y - S_{\operatorname{lca}(x, y)} - S_{\operatorname{fa}(\operatorname{lca}(x, y))}
$$

where $\operatorname{lca}(x, y)$ denotes the [lowest common ancestor](../graph/lca.md) of nodes $x$ and $y$.

#### Edge Weights

The case where weights are stored on edges can be almost transformed into the node weight case. For all non-root nodes $x \neq 1$, let $\operatorname{edge}(x)$ denote the edge connecting node $x$ and its parent $\operatorname{fa}(x)$. Then we can assume that the edge weight is stored at the node farther from the root. That is, node $x$ stores the weight of edge $\operatorname{edge}(x)$. The root node stores a weight of $0$. Then, using the recurrence discussed in the previous section, we can also preprocess $S_x$, the sum of edge weights on the path from the root to node $x$.

At this point, the sum of node weights on the path connecting node $x$ and $y$ can be queried by

$$
S_x + S_y - 2S_{\operatorname{lca}(x, y)}.
$$

Note that, unlike the node weight case, the queried weight sum does not include the weight at $\operatorname{lca}(x, y)$, because the edge weight stored there is not on the path being queried.

#### Subtree Sum

Unlike the array case, because the tree is not symmetric front and back, computing "prefix sum" bottom-up (from leaves to root) and top-down (from root to leaves) yields different results. In general, "prefix sum on trees" refers to the top-down computed prefix sum. For convenience, we call the bottom-up computed "prefix sum" **subtree sum** in this article.

The sum of node weights in the subtree rooted at node $x$, i.e., the corresponding subtree sum, is

$$
T_x = \sum_{y\in\operatorname{desc}(x)} a_x.
$$

where $\operatorname{desc}(x)$ denotes the set of all descendants of $x$ (including $x$ itself).

Unlike prefix sum on trees, subtree sum cannot be applied to $O(1)$ path weight sum queries, but it can be used to understand tree difference in the following section.

## Difference

Difference is a strategy opposite to prefix sum, being the inverse operation of prefix sum. Rather than computing the difference of a given sequence, a more common scenario in contests is to maintain information about the difference sequence to perform multiple range updates. After all range updates are completed, the original sequence information can be restored through prefix sum to perform queries on the original sequence. Note that update operations must come before query operations.

If you need to support mixed operations of multiple updates and queries, you need to use a [Fenwick tree (Binary Indexed Tree)](../ds/fenwick.md), but their underlying ideas are shared.

### One-Dimensional Difference

For a sequence $\{a_i\}$, its difference sequence $\{D_i\}$ is defined as

$$
D_i = a_i - a_{i-1},~ a_0 = 0.
$$

C++ standard library provides the difference function [`std::adjacent_difference`](https://en.cppreference.com/w/cpp/algorithm/adjacent_difference), defined in the header `<numeric>`.

The relationship between prefix sum and difference is as follows:

???+ note "Properties"
    Let $\{D_i\}$ be the difference sequence of $\{a_i\}$. Then we have
    
    -   The sequence $\{a_i\}$ is the prefix sum of the sequence $\{D_i\}$, that is
    
        $$
        a_i = \sum_{j=1}^i D_j.
        $$
    -   The prefix sum of the sequence $\{a_i\}$ is
    
        $$
        S_i = \sum_{j=1}^i\sum_{k=1}^jD_k = \sum_{j=1}^i(i-j+1)D_j. 
        $$

Difference information is often used to maintain multiple operations of adding a constant to a range of a sequence, followed by one or more queries for the value at a specific position.

Suppose we want to add $v$ to every element in the range $[l, r]$ of the sequence $\{a_i\}$. We can perform the following operation on its difference sequence $\{D_i\}$:

$$
D_{l} \gets D_{l} + v,~ D_{r+1}\gets D_{r+1} - v.
$$

After all update operations are completed, the updated values of $\{a_i\}$ can be restored by a prefix sum operation. A single update is $O(1)$. For queries, a one-time $O(n)$ prefix sum operation is needed, after which each query is $O(1)$.

???+ example "Reference Code"
    ```cpp
    --8<-- "docs/basic/code/prefix-sum/prefix-sum_6.cpp:core"
    ```

### Two-Dimensional / Multi-Dimensional Difference

Difference can also be extended to multiple dimensions. Treating multi-dimensional difference as the inverse operation of multi-dimensional prefix sum, then computing the original array from the multi-dimensional prefix sum can be done using the inclusion-exclusion principle. For example, the definition of 2D difference is

$$
D_{i,j} = a_{i,j} - a_{i-1,j} - a_{i,j-1} + a_{i-1,j-1}.
$$

However, if you want to compute the entire difference array, a simpler and more efficient approach is dimension-by-dimension difference, i.e., enumerate all dimensions and compute the difference along each dimension.

2D difference information is often used to maintain multiple rectangle additions on a 2D array. For example, to add $v$ to every element in the matrix with top-left corner $(x_1, y_1)$ and bottom-right corner $(x_2, y_2)$, you can perform the following operation on its difference array $\{D_{i,j}\}$:

$$
\begin{aligned}
D_{x_1,y_1} &\gets D_{x_1,y_1} + v, \\
D_{x_1,y_2+1} &\gets D_{x_1,y_2+1} - v,\\
D_{x_2+1,y_1} &\gets D_{x_2+1,y_1} - v,\\
D_{x_2+1,y_2+1} &\gets D_{x_2+1,y_2+1} + v.
\end{aligned}
$$

After all update operations are completed, you only need to perform a single 2D prefix sum to quickly query the updated array values.

??? example "Reference Code"
    ```cpp
    --8<-- "docs/basic/code/prefix-sum/prefix-sum_7.cpp:core"
    ```

Of course, similar ideas apply for dimensions $k > 2$, but a single update operation requires $O(2^k)$ time complexity, which becomes impractical as $k$ increases.

### Difference on Trees

Difference can be extended to rooted trees to implement range addition on tree paths. Depending on whether the maintained information is stored on nodes or edges, tree difference can be divided into **node difference** and **edge difference**, which differ slightly in implementation. Also, compared to prefix sum operations on trees, the more common approach is to compute subtree sums after all update operations, then query. This section discusses exactly this approach.

#### Node Difference

If you want to add $v$ to all node weights on the path between node $x$ and $y$, you can perform the following operation on its difference sequence $\{D_x\}$:

$$
\begin{aligned}
D_x &\gets D_x + v, \\
D_{\operatorname{lca}(x, y)} &\gets D_{\operatorname{lca}(x, y)} - v,\\
D_y &\gets D_y + v, \\
D_{\operatorname{fa}(\operatorname{lca}(x, y))} &\gets D_{\operatorname{fa}(\operatorname{lca}(x, y))} - v.
\end{aligned}
$$

After all update operations are completed, computing a single subtree sum gives the updated node weights.

???+ example "Example"
    When performing range addition on node weights on the path between nodes $S$ and $T$, the first two terms in the above formula perform a one-dimensional difference operation on the path in the blue box, and the last two terms perform a one-dimensional difference operation on the path in the red box:
    
    ![](./images/prefix_sum1.svg)
    
    Summing bottom-up is equivalent to computing prefix sums on these two ranges from bottom to top. Thus, by comparing with the one-dimensional difference operation above, we can understand the correctness of the node difference operation.

#### Edge Difference

If you want to add $v$ to all edge weights on the path between node $x$ and $y$, you can perform the following operation on its difference sequence $\{D_x\}$:

$$
\begin{aligned}
D_x &\gets D_x + v, \\
D_y &\gets D_y + v, \\
D_{\operatorname{lca}(x, y)} &\gets D_{\operatorname{lca}(x, y)} - 2v.
\end{aligned}
$$

After all update operations are completed, computing a single subtree sum gives the updated node weights.

???+ example "Example"
    As shown in the figure, edge difference operations can be used to solve the edge weight range addition problem on the red path.
    
    ![](./images/prefix_sum2.svg)
    
    Since performing difference directly on edges is difficult, the value that should be accumulated to the red edge is moved down to the adjacent node, making the operation more convenient. By comparing with the node difference formula, one can understand the edge difference formula.

### Example Problems

???+ example "[Luogu P3128 Maximum Flow](https://www.luogu.com.cn/problem/P3128)"
    FJ installed $N-1$ pipes between the $N (2 \le N \le 50,000)$ compartments of his barn, numbered from $1$ to $N$. All compartments are connected by pipes.
    
    FJ has $K (1 \le K \le 100,000)$ milk transport routes, with the $i$-th route transporting from compartment $s_i$ to compartment $t_i$. A transport route brings one unit of transport pressure to the compartments at both endpoints and all intermediate compartments along the way. You need to calculate the maximum pressure on any compartment.

??? note "Solution Approach"
    We need to count how many times each node is passed through. Using tree difference, we add one to each node on each path, and then we can quickly obtain the number of times each node is passed through. Here we use binary lifting to compute the LCA. Finally, we traverse the tree with DFS and, during backtracking, sum the difference array to get the answer.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/basic/code/prefix-sum/prefix-sum_3.cpp"
    ```

## Practice Problems

Prefix Sum:

-   [Luogu B3612 [Deep Dive 1. Example 1] Range Sum](https://www.luogu.com.cn/problem/B3612)
-   [Luogu U69096 Inverse of Prefix Sum](https://www.luogu.com.cn/problem/U69096)
-   [AtCoder joi2007ho_a Maximum Sum](https://atcoder.jp/contests/joi2007ho/tasks/joi2007ho_a)
-   [USACO16JAN Subsequences Summing to Sevens](https://www.luogu.com.cn/problem/P3131)
-   [USACO05JAN Moo Volume S](https://www.luogu.com.cn/problem/P6067)

Two-Dimensional / Multi-Dimensional Prefix Sum:

-   [HDU 6514 Monitor](https://acm.hdu.edu.cn/showproblem.php?pid=6514)
-   [Luogu P1387 Maximum Square](https://www.luogu.com.cn/problem/P1387)
-   [HNOI2003 Laser Bomb](https://www.luogu.com.cn/problem/P2280)
-   [CF 165E Compatible Numbers](https://codeforces.com/contest/165/problem/E)
-   [CF 383E Vowels](https://codeforces.com/problemset/problem/383/E)
-   [ARC 100C Or Plus Max](https://atcoder.jp/contests/arc100/tasks/arc100_c)

Prefix Sum on Trees:

-   [LOJ 10134.Dis](https://loj.ac/problem/10134)
-   [LOJ 2491. Sum](https://loj.ac/problem/2491)

Difference:

-   [Fenwick Tree 3: Range Update, Range Query](https://loj.ac/problem/132)
-   [Poetize6 IncDec Sequence](https://www.luogu.com.cn/problem/P4552)
-   [Luogu P4231 Triple Kill](https://www.luogu.com.cn/problem/P4231)

Two-Dimensional / Multi-Dimensional Difference:

-   [Luogu P3397 Carpet](https://www.luogu.com.cn/problem/P3397)
-   [Luogu P8228 [Wdoi-5] Modular Core Furnace](https://www.luogu.com.cn/problem/P8228)

Tree Difference:

-   [Luogu P3128 Maximum Flow](https://www.luogu.com.cn/problem/P3128)
-   [JLOI2014 Squirrel's New Home](https://loj.ac/problem/2236)
-   [NOIP2015 Transport Plan](http://uoj.ac/problem/150)
-   [NOIP2016 Daily Running](http://uoj.ac/problem/261)
