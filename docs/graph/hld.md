author: GoodCoder666, Ir1d, Marcythm, ouuan, hsfzLZH1, Xeonacid, greyqz, Chrogeek, ftxj, sshwy, LuoshuiTianyi, hyp1231, sun2snow

## Introduction

Tree decomposition is used to split a tree into several chains to maintain information about paths on the tree.

Specifically, the entire tree is decomposed into several chains, which together form a linear structure, and then other data structures are used to maintain information.

There are various forms of **tree decomposition** (tree splitting/chain splitting), such as **heavy-light decomposition**, **long-chain decomposition**, and decomposition for Link/cut Trees (sometimes called "real chain decomposition"). In most cases (when not specified otherwise), "tree decomposition" refers to "heavy-light decomposition".

Heavy-light decomposition can divide any path on a tree into at most $O(\log n)$ continuous chains, where each chain has vertices with distinct depths (i.e., a bottom-up chain, and the LCA of all vertices on the chain is one endpoint of the chain).

Heavy-light decomposition also guarantees that the DFS order of vertices on each chain is continuous, making it convenient to use data structures that maintain sequences (such as segment trees) to maintain path information on the tree. For example:

1.  Modify all vertex values on the **path between two vertices** on the tree.
2.  Query the **sum/maximum/other (information that can be maintained by data structures on sequences and is easy to merge)** of vertex values on the **path between two vertices** on the tree.

In addition to combining with data structures to maintain path information on trees, tree decomposition can also be used to find LCA in $O(\log n)$ (with a relatively small constant). In some problems, the properties of tree decomposition can be flexibly applied.

## Heavy-Light Decomposition

We provide some definitions:

A **heavy child** is defined as the child vertex with the largest subtree among the children. If there are multiple children with the largest subtree, pick one. If there are no children, there is no heavy child.

A **light child** is defined as all remaining child vertices.

The edge from this vertex to its heavy child is a **heavy edge**.

The edges to other light children are **light edges**.

Several heavy edges connected head-to-tail form a **heavy chain**.

Treating isolated vertices as heavy chains as well, the entire tree is decomposed into several heavy chains.

As shown in the figure:

![HLD](./images/hld.png)

## Implementation

Tree decomposition is implemented in two DFS passes. The pseudocode is as follows:

The first DFS records for each vertex: parent ($\textit{father}$), depth ($\textit{depth}$), subtree size ($\textit{size}$), and heavy child ($\textit{hson}$).

$$
\begin{array}{l}
\text{TREE-BUILD }(u,\textit{dep}) \\
\begin{array}{ll}
1 & u.\textit{hson}\gets 0 \\
2 & u.\textit{hson}.\textit{size}\gets 0 \\
3 & u.\textit{depth}\gets \textit{dep} \\
4 & u.\textit{size}\gets 1 \\
5 & \textbf{for }\text{each son }v\text{ of }u \\
6 & \qquad u.\textit{size}\gets u.\textit{size} + \text{TREE-BUILD }(v,\textit{dep}+1) \\
7 & \qquad v.\textit{father}\gets u \\
8 & \qquad \textbf{if }v.\textit{size}> u.\textit{hson}.\textit{size} \\
9 & \qquad \qquad u.\textit{hson}\gets v \\
10 & \textbf{return } u.\textit{size}
\end{array}
\end{array}
$$

The second DFS records: the top of the chain the vertex belongs to ($\textit{top}$, should be initialized to the vertex itself), the DFS order when traversing heavy edges first ($\textit{dfn}$), and the vertex number corresponding to the DFS order ($\textit{rank}$).

$$
\begin{array}{l}
\text{TREE-DECOMPOSITION }(u,\textit{top}) \\
\begin{array}{ll}
1 & u.\textit{top}\gets \textit{top} \\
2 & \textit{tot}\gets \textit{tot}+1\\
3 & u.\textit{dfn}\gets \textit{tot} \\
4 & \textit{rank}(\textit{tot})\gets u \\
5 & \textbf{if }u.\textit{hson}\text{ is not }0 \\
6 & \qquad \text{TREE-DECOMPOSITION }(u.\textit{hson},\textit{top}) \\
7 & \qquad \textbf{for }\text{each son }v\text{ of }u \\
8 & \qquad \qquad \textbf{if }v\text{ is not }u.\textit{hson} \\
9 & \qquad \qquad \qquad \text{TREE-DECOMPOSITION }(v,v) 
\end{array}
\end{array}
$$

The following is the code implementation.

We first give some definitions:

-   $\operatorname{fa}(x)$ denotes the parent of vertex $x$ in the tree.
-   $\operatorname{dep}(x)$ denotes the depth of vertex $x$ in the tree.
-   $\operatorname{siz}(x)$ denotes the number of vertices in the subtree of vertex $x$.
-   $\operatorname{son}(x)$ denotes the **heavy son** of vertex $x$.
-   $\operatorname{top}(x)$ denotes the top vertex (with minimum depth) of the **heavy chain** that vertex $x$ belongs to.
-   $\operatorname{dfn}(x)$ denotes the **DFS order** of vertex $x$, which is also its index in the segment tree.
-   $\operatorname{rnk}(x)$ denotes the vertex number corresponding to the DFS order, satisfying $\operatorname{rnk}(\operatorname{dfn}(x))=x$.

We perform two DFS passes to preprocess these values. The first DFS computes $\operatorname{fa}(x)$, $\operatorname{dep}(x)$, $\operatorname{siz}(x)$, $\operatorname{son}(x)$, and the second DFS computes $\operatorname{top}(x)$, $\operatorname{dfn}(x)$, $\operatorname{rnk}(x)$.

```cpp
void dfs1(int u, int f) {
  fa[u] = f, dep[u] = dep[f] + 1, siz[u] = 1;
  for (auto v : G[u]) {
    if (v == f) continue;
    dfs1(v, u);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}

void dfs2(int u, int ftop) {
  top[u] = ftop, dfn[u] = ++idx, rnk[idx] = u;
  if (son[u]) dfs2(son[u], ftop);
  for (auto v : G[u])
    if (v != son[u] && v != fa[u]) dfs2(v, v);
}
```

## Properties of Heavy-Light Decomposition

**Each vertex on the tree belongs to and only belongs to one heavy chain.**

The vertex at the beginning of a heavy chain is never a heavy child (because the vertex at the beginning of a heavy chain is either the root or a light child of its parent).

All heavy chains **completely decompose** the entire tree.

During decomposition, **heavy edges are traversed first**. After DFS, the DFS order of vertices within a heavy chain is continuous. The sequence sorted by DFN is the decomposed chains.

The DFS order of vertices within a subtree is continuous.

It can be observed that when we traverse down through a **light edge**, the size of the current subtree at least halves.

Therefore, for any path on the tree, if we split it into two directions from the [LCA](./lca.md), each direction requires at most $O(\log n)$ steps. Thus, every path on the tree can be split into at most $O(\log n)$ heavy chains.

??? info "How to construct data to stress-test tree decomposition"
    Under normal circumstances, the $O(\log n)$ constant of tree decomposition is hard to stress-test if not fully utilized. To stress-test it, one can only build a binary tree with low depth.
    
    So we can consider a compromise.
    
    We build a binary tree with $\sqrt{n}$ vertices. For each edge from a vertex to its child, we replace it with a chain of length $\sqrt{n}$.
    
    This way, we can stress-test the average number of heavy-light chain switches to about $\frac{\log n}{2}$, while having a depth of $O(\sqrt{n} \log n)$.
    
    Adding some random leaves may stress-test tree decomposition. However, the small constant of tree decomposition may make it hard to stress-test.

## Common Applications

### Path Maintenance

To query the path weight sum between two vertices on a tree using tree decomposition, the pseudocode is as follows:

$$
\begin{array}{l}
\text{TREE-PATH-SUM }(u,v) \\
\begin{array}{ll}
1 & \textit{tot}\gets 0 \\
2 & \textbf{while }u.\textit{top}\text{ is not }v.\textit{top} \\
3 & \qquad \textbf{if }u.\textit{top}.\textit{depth}< v.\textit{top}.\textit{depth} \\
4 & \qquad \qquad \text{SWAP}(u, v) \\
5 & \qquad \textit{tot}\gets \textit{tot} + \text{sum of values between }u\text{ and }u.\textit{top} \\
6 & \qquad u\gets u.\textit{top}.\textit{father} \\
7 & \textit{tot}\gets \textit{tot} + \text{sum of values between }u\text{ and }v \\
8 & \textbf{return } \textit{tot} 
\end{array}
\end{array}
$$

The DFS order on a chain is continuous, so a segment tree or binary indexed tree can be used for maintenance.

Each time, we select the deeper chain and jump up until both vertices are on the same chain.

The same jumping structure applies to maintaining and querying other information on paths.

### Subtree Maintenance

Sometimes we need to maintain information on subtrees, such as adding $v$ to the value of all vertices in the subtree rooted at $x$.

During DFS, the vertices in a subtree have continuous DFS order.

Each vertex records `bottom`, which represents the endpoint of the continuous interval of its subtree.

This transforms subtree information into a continuous segment of interval information.

### Finding the Lowest Common Ancestor

Continuously jump up the heavy chains. When both vertices end up on the same heavy chain, the vertex with smaller depth is the LCA.

When jumping up the heavy chains, we should first jump from the chain with greater top depth.

Reference code:

```cpp
int lca(int u, int v) {
  while (top[u] != top[v]) {
    if (dep[top[u]] > dep[top[v]])
      u = fa[top[u]];
    else
      v = fa[top[v]];
  }
  return dep[u] > dep[v] ? v : u;
}
```

### Root Changing Operation

Consider a new type of problem: in addition to the basic operations supported by tree decomposition, there are root changing operations.

Since the information maintained by tree decomposition is static, it does not support dynamic modifications. At the same time, it is impossible to re-preprocess information after each root change, as the complexity would be too high. Therefore, we need to fully utilize the previously obtained information to help solve root changing operations.

For path modification and query operations, since the simple path between two vertices on a tree is unique, it does not change, so they are handled the same way as normal operations.

For subtree modification and query operations, the general approach is to map the subtree after changing the root to the original subtree. This requires discussing the relative positions of the root of the operated subtree, the new root of the entire tree after changing, and the original root. See [the example below](./hld.md#loj-139-tree-decomposition) for details.

## Examples

This article demonstrates how to apply heavy-light decomposition through examples. First, a template problem.

???+ example "[「ZJOI2008」Tree Statistics](https://loj.ac/problem/10138)"
    For a tree with $n$ vertices, where vertices have weights, perform three types of operations a total of $q$ times:
    
    1.  Modify the weight of a single vertex;
    2.  Query the maximum weight on the path from $u$ to $v$;
    3.  Query the sum of weights on the path from $u$ to $v$.
    
    Guarantee $1\le n\le 30000$, $0\le q\le 200000$.

??? note "Solution"
    According to the problem description and the properties described earlier, the segment tree needs to support three operations:
    
    1.  Single point modification;
    2.  Range query for maximum value;
    3.  Range query for sum.
    
    Single point modification is easy to implement.
    
    Since the DFS order of a subtree is continuous (regardless of tree decomposition), modifying a vertex's subtree only requires modifying this continuous DFS order segment.
    
    The problem is how to modify/query the path between two vertices.
    
    Consider how we use **binary lifting to find LCA**. First, we **raise both vertices to the same height, then jump both vertices up together**. The same idea can be applied to tree decomposition.
    
    During the process of jumping up, if the current vertex is on a heavy chain, jump to the top of the heavy chain; if the current vertex is not on a heavy chain, jump to the parent vertex. Continue until both vertices are the same. Update/query range information along the way.
    
    For each query, at most $O(\log n)$ heavy chains are traversed, and each heavy chain has a segment tree complexity of $O(\log n)$, so the total time complexity is $O(n\log n+q\log^2 n)$. In practice, the number of heavy chains rarely reaches $O(\log n)$ (a complete binary tree can maximize it), so tree decomposition generally has a small constant.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/graph/code/hld/hld_1.cpp"
    ```

Next is a template problem with root changing operations.

<a id="loj-139-tree-decomposition"></a>

???+ example "[LOJ 139. Tree Decomposition](https://loj.ac/p/139)"
    Given a tree with $n$ vertices (initially rooted at vertex $1$), support $m$ operations:
    
    -   Change root: set vertex $u$ as the new root of the tree.
    -   Modify path: add $w$ to the weights of all vertices on the path from vertex $u$ to vertex $v$ (including both endpoints).
    -   Modify subtree: add $w$ to the weights of all vertices in the subtree rooted at vertex $u$.
    -   Query path: query the sum of weights of all vertices on the path from vertex $u$ to vertex $v$ (including both endpoints).
    -   Query subtree: query the sum of weights of all vertices in the subtree rooted at vertex $u$.
    
    $1 \le n,m \le 10^5$.

??? note "Solution"
    First, run DFS with $1$ as the root to preprocess the necessary information for tree decomposition. For convenience of description, we call the tree rooted at $1$ the "original tree", and the tree after several root changes the "current tree". During operations, we maintain $\textit{root}$ as the root of the current tree. Since the segment tree stores information based on the DFS order of the original tree, each query and modification needs to be transformed from the current tree to the original tree.
    
    For the root change operation, we simply set $\textit{root}\gets u$. For path operations, since root changing does not affect paths, we perform the corresponding operations directly on the original tree.
    
    The key is to consider subtree operations. We classify the discussion based on the relative position of $u$ and $\textit{root}$:
    
    -   $u = \textit{root}$: This is the most special case, equivalent to operating on the entire tree. Simply tag the root of the segment tree or query the answer.
    -   $u$ is an ancestor of $\textit{root}$ in the original tree, i.e., $u$ is on the simple path from $1$ to $\textit{root}$.
    
        This is the most noteworthy case. Define $v$ as the vertex on the simple path from $u$ to $\textit{root}$ in the original tree that is not $u$ and has the smallest depth. It can be observed that the part of the original tree excluding $v$ and its subtree is exactly $u$ and its subtree in the current tree.
    
        Consider how to efficiently find $v$. We first set $v\gets\textit{root}$, then jump up along the heavy chain until $\operatorname{dep}(\operatorname{top}(v))\le\operatorname{dep}(u)+1$.
    
        -   If $\operatorname{dep}(\operatorname{top}(v))=\operatorname{dep}(u)+1$, set $v\gets\operatorname{top}(v)$. At this point, $v$ is a light child of $u$.
        -   If $\operatorname{dep}(\operatorname{top}(v))<\operatorname{dep}(u)+1$, i.e., $\operatorname{dep}(\operatorname{top}(v))\le \operatorname{dep}(u)$, this means $u$ and $v$ are on the same heavy chain. According to the property that DFS order is continuous on the same heavy chain, the desired $v$ must satisfy $\operatorname{dfn}(v)=\operatorname{dfn}(u)+1$. Therefore, set $v\gets\operatorname{rnk}(\operatorname{dfn}(u)+1)$.
    
        Note that these two cases can be merged: after jumping, we can directly set
    
        $$
        v\gets\operatorname{rnk}(\operatorname{dfn}(\operatorname{top}(v))+\operatorname{dep}(u)+1-\operatorname{dep}(\operatorname{top}(v))).
        $$
    
        It is easy to verify that the $v$ found using this expression is equivalent to the $v$ found through case analysis. This expression is used in the reference implementation.
    
        Since the interval covered by $v$'s subtree is $[\operatorname{dfn}(v),\operatorname{dfn}(v)+\operatorname{siz}(v))$, we only need to operate on $[1,\operatorname{dfn}(v))\cup[\operatorname{dfn}(v)+\operatorname{siz}(v),n]$.
    -   Other cases. It can be observed that root changing does not affect the subtree of $u$, so we can maintain it in the normal way.
    
    The complexity of this approach is the same as the approach without root changing, both $O(n\log^2 n)$.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/graph/code/hld/hld_4.cpp"
    ```

Finally, an interactive problem, which is a non-traditional application of tree decomposition.

???+ example "[Nauuo and Binary Tree](https://loj.ac/problem/6669)"
    There is a binary tree rooted at $1$. You can query the distance between any two vertices. Determine the parent of each vertex.
    
    The number of vertices does not exceed $3000$, and you can make at most $30000$ queries.

??? note "Solution"
    First, the depth of each vertex can be determined through $n-1$ queries.
    
    Then consider determining the parent of each vertex in order of increasing depth. This way, when determining the parent of a vertex, all its ancestors are already known.
    
    Before determining the parent of a vertex, perform heavy-light decomposition on the known part of the tree.
    
    Suppose we need to find the position of vertex $k$ in subtree $u$. We can query the distance between $k$ and the tail of the heavy chain containing $u$, which can further determine the position of $k$. See the figure for details:
    
    ![](./images/hld2.png)
    
    The red dashed line is a heavy chain, $d$ is the result of the query, i.e., $\textit{dis}(k, \textit{bot}(u))$, and the depth of $v$ is $(\textit{dep}(k)+\textit{dep}(\textit{bot}(u))-d)/2$.
    
    This way, if $v$ has only one child, then $k$'s parent is $v$. Otherwise, we can recursively find $k$'s parent in the subtree of $w$.
    
    Time complexity is $O(n^2)$, and query complexity is $O(n\log n)$.
    
    Specifically, let $T(n)$ be the maximum number of queries required to find the position of a new vertex in a tree of size $n$. We have:
    
    $$
    T(n)\le
    \begin{cases}
    0&n=1\\
    T\left(\left\lfloor\frac{n-1}2\right\rfloor\right)+1&n\ge2
    \end{cases}
    $$
    
    $2999+\sum_{i=1}^{2999}T(i)\le 29940$. In fact, this upper bound can be reached through data construction. However, with some random perturbations (such as using an unstable sorting algorithm when sorting depths), the number of queries rarely exceeds $21000$.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/graph/code/hld/hld_2.cpp"
    ```

## Long-Chain Decomposition

Long-chain decomposition is essentially another way of chain decomposition.

Define the **heavy child** as the child with the maximum subtree depth among children. If there are multiple children with the maximum subtree, pick one. If there are no children, there is no heavy child.

Define the **light child** as all remaining children.

The edge from this vertex to its heavy child is a **heavy edge**.

Edges to other light children are **light edges**.

Several heavy edges connected head-to-tail form a **heavy chain**.

Treating isolated vertices as heavy chains as well, the entire tree is decomposed into several heavy chains.

As shown in the figure (this decomposition can be viewed as either heavy-chain decomposition or long-chain decomposition):

![HLD](./images/hld.png)

The implementation of long-chain decomposition is similar to heavy-light decomposition, so we won't go into detail here.

### Common Applications

First, we notice that the number of light edge switches along the path from a vertex to the root in long-chain decomposition is $O(\sqrt{n})$.

??? info "How to construct data to maximize light-heavy edge switches"
    We can construct a binary tree T with the following structure:
    
    Suppose the binary tree has a parameter $D$.
    
    If $D \neq 0$, construct a binary tree with parameter $D-1$ on the left child, and a chain of length $2D-1$ on the right child.
    
    If $D = 0$, we can directly construct a single leaf node and end the call.
    
    This construction guarantees that all edges from the leaf to the root are light edges, requiring $D^2$ level nodes.
    
    Taking $D=\sqrt{n}$ suffices.

#### Long-Chain Decomposition Optimized DP

Generally, DP that can be optimized using long-chain decomposition has a dimension for depth.

We can consider using long-chain decomposition to optimize tree DP.

Specifically, each vertex's state directly inherits from its heavy son's state, while the DP states of light sons are merged by brute force.

???+ example "[Codeforces 1009 F. Dominant Indices](http://codeforces.com/contest/1009/problem/F)"
    Given a rooted tree with $n$ vertices, with vertex $1$ as the root.
    
    Define the depth array of vertex $x$ as an infinite sequence $[d_{x, 0}, d_{x, 1}, d_{x, 2}, \dots]$, where $d_{x, i}$ denotes the number of vertices $y$ satisfying:
    
    -   $x$ is an ancestor of $y$;
    -   The simple path from $x$ to $y$ contains exactly $i$ edges.
    
    The dominant index of the depth array of vertex $x$ (for short, the dominant index of vertex $x$) is defined as an index $j$ such that:
    
    -   For all $k < j$, we have $d_{x, k} < d_{x, j}$;
    -   For all $k > j$, we have $d_{x, k} \le d_{x, j}$.
    
    Please compute the dominant index of each vertex in the tree.

??? note "Solution"
    Let $f_{i,j}$ denote the number of vertices in subtree $i$ at distance $j$ from $i$.
    
    Direct brute-force transition has time complexity $O(n^2)$.
    
    We consider inheriting the heavy son's DP array and answer during each transition, then updating on that basis.
    
    First, we need to insert an element 1 at the front of the heavy son's DP array, representing the current vertex.
    
    Then, we brute-force merge all light sons' DP arrays with the current vertex's DP array.
    
    Note that the DP array length of a light son equals the length of the heavy chain it belongs to, and the sum of all heavy chain lengths is $n$.
    
    In other words, the total time complexity of brute-force merging light sons is $O(n)$.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/graph/code/hld/hld_3.cpp"
    ```

Note that generally, DP array memory is allocated for an entire heavy chain at once, and different vertices on the chain have different starting position pointers.

The length of the DP array can be calculated based on the deepest vertex in the subtree.

Of course, there are many techniques for long-chain decomposition optimized DP, including but not limited to lazy propagation, etc. We won't expand on this here.

Reference: [Rent's Blog](https://www.cnblogs.com/zhoushuyu/p/9468669.html).

#### Finding k-th Ancestor using Long-Chain Decomposition

That is, given a vertex, find the vertex reached by jumping $k$ times to its parent.

First, assume we have preprocessed the $2^i$-th ancestor for each vertex.

Now assume we have found the $2^i$-th ancestor of the query vertex such that $2^i \le k < 2^{i+1}$.

We consider finding the vertex on its heavy chain and list it in a table by depth. Assume the heavy chain has length $d$.

At the same time, during preprocessing, we find the $1$ to $d$-th ancestors of the root of each heavy chain, also put in a table.

According to the properties of long-chain decomposition, $k-2^i \le 2^i \leq d$. That is, we can find the $k$-th ancestor of this vertex on the table of the heavy chain in $O(1)$.

Preprocessing requires binary lifting to compute $2^i$-th ancestors, and also requires preprocessing the table for each heavy chain.

Preprocessing complexity is $O(n\log n)$, query complexity is $O(1)$.

## Exercises

-   [「Luogu P3379」[Template] Lowest Common Ancestor (LCA)](https://www.luogu.com.cn/problem/P3379) (Tree decomposition for LCA doesn't require data structures, can be used for practice)
-   [「JLOI2014」Squirrel's New Home](https://loj.ac/problem/2236) (Tree difference can also be used)
-   [「HAOI2015」Tree Operations](https://loj.ac/problem/2125)
-   [「Luogu P3384」[Template] Heavy-Light Decomposition / Tree Decomposition](https://www.luogu.com.cn/problem/P3384)
-   [「Luogu P1505」[National Training Team] Travel](https://www.luogu.com.cn/problem/P1505)
-   [「NOI2015」Package Manager](https://uoj.ac/problem/128)
-   [「SDOI2011」Coloring](https://www.luogu.com.cn/problem/P2486)
-   [「SDOI2014」Travel](https://hydro.ac/p/bzoj-P3531)
-   [「Luogu P3979」Distant Country](https://www.luogu.com.cn/problem/P3979)
-   [「POI2014」Hotel Enhanced](https://hydro.ac/p/bzoj-P4543) (Long-chain decomposition optimized DP)
-   [Strategy](https://hydro.ac/p/bzoj-P3252) (Long-chain decomposition optimized greedy)
