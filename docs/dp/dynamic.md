Prerequisites: [Matrices](../math/linear-algebra/matrix.md), [Heavy-Light Decomposition](../graph/hld.md).

Dynamic DP is an advanced technique introduced by Maokun in WC2018. It is generally used to solve DP problems on trees with point-weight or edge-weight modification operations.

## Example

Use the following template problem to explain the process of dynamic DP.

???+ note "Example Problem [Luogu P4719 [Template] Dynamic DP](https://www.luogu.com.cn/problem/P4719)"
    Given a tree with $n$ nodes, where nodes have weights, there are $m$ operations. Each operation gives $x,y$, meaning the weight of node $x$ is changed to $y$. After each operation, find the weight of the maximum-weight independent set of the tree.

### Generalized Matrix Multiplication

Define generalized matrix multiplication $A\times B=C$ as:

$$
C_{i,j}=\max_{k=1}^{n}(A_{i,k}+B_{k,j})
$$

This is equivalent to replacing multiplication in ordinary matrix multiplication with addition, and replacing addition with the $\max$ operation.

Generalized matrix multiplication also satisfies associativity, so fast matrix exponentiation can be used.

### Without Modification Operations

Let $f_{i,0}$ denote the maximum answer when $i$ is not selected, and let $f_{i,1}$ denote the maximum answer when $i$ is selected.

The DP equation is:

$$
\begin{cases}
f_{i,0}=\sum_{son}\max(f_{son,0},f_{son,1})\\
f_{i,1}=w_i+\sum_{son}f_{son,0}
\end{cases}
$$

The answer is $\max(f_{root,0},f_{root,1})$.

### With Modification Operations

First perform heavy-light decomposition on the tree. Suppose there is a heavy chain like this:

![](./images/dynamic.png)

Let $g_{i,0}$ denote the maximum answer when $i$ is not selected and only subtrees of light children of $i$ may be selected. Let $g_{i,1}$ denote the maximum answer when $i$ is selected without considering $son_i$, where $son_i$ is the heavy child of $i$.

Assuming $g_{i,0/1}$ is known, the DP equation is:

$$
\begin{cases}
f_{i,0}=g_{i,0}+\max(f_{son_i,0},f_{son_i,1})\\
f_{i,1}=g_{i,1}+f_{son_i,0}
\end{cases}
$$

The answer is $\max(f_{root,0},f_{root,1})$.

We can construct the matrix:

$$
\begin{bmatrix}
g_{i,0} & g_{i,0}\\
g_{i,1} & -\infty
\end{bmatrix}\times 
\begin{bmatrix}
f_{son_i,0}\\f_{son_i,1}
\end{bmatrix}=
\begin{bmatrix}
f_{i,0}\\f_{i,1}
\end{bmatrix}
$$

Note that generalized multiplication is used here.

It can be seen that a modification only needs to change $g_{i,1}$ and every upward heavy chain.

### Detailed Approach

1.  Run DFS preprocessing to compute $f_{i,0/1}$ and $g_{i,0/1}$.

2.  Perform heavy-light decomposition on the tree. Note that querying a point requires computing the interval matrix product from that point to the end of its heavy chain, so for each point record $End_i$, the node number of the end of the heavy chain containing $i$. Build a segment tree for each heavy chain; the segment tree maintains the $g$ matrix and interval products of $g$ matrices.

3.  During modification, first modify $g_{i,1}$ and the matrix of node $i$ in the segment tree. Compute the change in the matrix of $top_i$, and apply it to the matrix of $fa_{top_i}$.

4.  A query is the interval product from node 1 to the end of its heavy chain, followed by taking a $\max$.

??? note "Code Implementation"
    ```cpp
    --8<-- "docs/dp/code/dynamic/dynamic_1.cpp"
    ```

## Exercises

-   [SPOJ GSS3 - Can you answer these queries III](https://www.spoj.com/problems/GSS3/)
-   [NOIP2018 Defense of the Kingdom](https://loj.ac/p/2955)
-   [SDOI2017 Tree Cutting Game](https://loj.ac/p/2269)
