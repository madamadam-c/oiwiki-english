The **diameter** of a tree is the longest simple path between any two nodes.

Prerequisites: [Tree Basics](./tree-basic.md).

## Introduction

Clearly, a tree can have multiple diameters, but they all have the same length.

The tree diameter can be found in $O(n)$ time using either two DFS/BFS passes or tree DP.

## Two DFS/BFS

First, start a DFS from any node $y$, and find the farthest node from $y$, call it $z$. Then start a second DFS from $z$, and find the node $z'$ that is farthest from $z$. Then $\delta(z, z')$ is the tree diameter.

Obviously, if node $z$ from the first DFS is one endpoint of a diameter, then node $z'$ from the second DFS is the other endpoint. We only need to prove that under any circumstance, $z$ is always an endpoint of some diameter.

Theorem: In any tree, starting from an arbitrary node $y$, the node $z$ farthest from $y$ (found by a DFS) is always an endpoint of a diameter.

???+ note "Proof"
    Proof by contradiction. Let the starting node be $y$. Let the actual diameter be $\delta(s, t)$, and let $z$ be the farthest node from $y$. Suppose $z$ is neither $t$ nor $s$. There are three cases:

    - If $y$ lies on $\delta(s, t)$:

    ![y on s-t path](./images/tree-diameter1.svg)

    We have $\delta(y, z) > \delta(y, t) \Longrightarrow \delta(x, z) > \delta(x, t) \Longrightarrow \delta(s, z) > \delta(s, t)$, which contradicts that $\delta(s, t)$ is the longest simple path between any two nodes.

    - If $y$ is not on $\delta(s, t)$, and $\delta(y, z)$ shares some common path with $\delta(s, t)$:

    ![y not on s-t, y-z shares path with s-t](./images/tree-diameter2.svg)

    We have $\delta(y, z) > \delta(y, t) \Longrightarrow \delta(x, z) > \delta(x, t) \Longrightarrow \delta(s, z) > \delta(s, t)$, which contradicts that $\delta(s, t)$ is the longest simple path.

    - If $y$ is not on $\delta(s, t)$, and $\delta(y, z)$ shares no common path with $\delta(s, t)$:

    ![y not on s-t, y-z shares no path with s-t](./images/tree-diameter3.svg)

    We have $\delta(y, z) > \delta(y, t) \Longrightarrow \delta(x', z) > \delta(x', t) \Longrightarrow \delta(x, z) > \delta(x, t) \Longrightarrow \delta(s, z) > \delta(s, t)$, again contradicting that $\delta(s, t)$ is the longest simple path.

    In all three cases, the assumption leads to contradiction, so the theorem is proven.

???+ warning "Negative Weight Edges"
    The proof above assumes no edge has negative weight. If the tree contains negative weight edges, the proof does not hold. Therefore, the two DFS/BFS method cannot be used when negative weight edges exist.

If you need to output all nodes on a diameter, you can record the parent of each node during the second DFS, then trace back from one endpoint to reconstruct the entire diameter.

## Tree DP

### Method 1

We maintain, for each node as the root, the longest path length $d_1$ and the second longest path length $d_2$ (which has no edges in common with the longest path) within its subtree. The diameter is the maximum value of $d_1 + d_2$ over all nodes.

Tree DP can find the diameter even when negative weight edges are present.

If you need to output all nodes on a diameter, record the child nodes corresponding to the longest and second longest paths for each node during the DP. When computing $d$, also record the node $u$ such that $d = d_1[u] + d_2[u]$. Then trace along the corresponding child from $u$ in the appropriate direction (for a rooted tree, follow upward; for an unrooted tree, note the direction recorded for each node).

### Method 2

This is a tree DP method using only one array.

Define $dp[u]$ as the length of the longest path starting from $u$ within the subtree rooted at $u$. The recurrence is: $dp[u] = \max(dp[u], dp[v] + w(u, v))$, where $v$ is a child of $u$, and $w(u, v)$ is the edge weight.

The tree diameter can be found by enumerating the sum of two paths from some node. Therefore, during DP, before updating $dp[u]$, compute $d = \max(d, dp[u] + dp[v] + w(u, v))$ to obtain the diameter $d$.

## Examples

???+ example "[Luogu B4016 Tree Diameter](https://www.luogu.com.cn/problem/B4016)"
    Given a tree with $n$ nodes, find the length of its diameter. $1 \leq n \leq 10^5$.

??? note "Two DFS/BFS Reference Implementation"
    ```cpp
    --8<-- "docs/graph/code/tree-diameter/tree-diameter_1.cpp"
    ```

??? note "Tree DP with Two Arrays Reference Implementation"
    ```cpp
    --8<-- "docs/graph/code/tree-diameter/tree-diameter_2.cpp"
    ```

??? note "Tree DP with One Array Reference Implementation"
    ```cpp
    --8<-- "docs/graph/code/tree-diameter/tree-diameter_3.cpp"
    ```

## Properties

The tree diameter has the following property: if all edge weights are positive, then all diameters share the same midpoint.

???+ note "Proof"
    Proof by contradiction. Let two diameters with different midpoints be $\delta(s, t)$ and $\delta(s', t')$, with midpoints $x$ and $x'$ respectively. Clearly, $\delta(s, x) = \delta(x, t) = \delta(s', x') = \delta(x', t')$.

    ![All diameters of a tree with positive edge weights share the same midpoint](./images/tree-diameter4.svg)

    We have $\delta(s, t') = \delta(s, x) + \delta(x, x') + \delta(x', t') > \delta(s, x) + \delta(x, t) = \delta(s, t)$, contradicting that $\delta(s, t)$ is the longest simple path. Hence the property holds.

## Exercises

- [CodeChef, Diameter of Tree](https://www.codechef.com/problems/DTREE)
- [Educational Codeforces Round 35, Problem F, Tree Destruction](https://codeforces.com/contest/911/problem/F)
- [ZOJ 3820 Building Fire Stations](https://pintia.cn/problem-sets/91827364500/exam/problems/type/7?problemSetProblemId=91827369872&page=28)
- [CEOI2019/CodeForces 1192B. Dynamic Diameter](https://codeforces.com/contest/1192/problem/B)
- [ICPC 2019 Shanghai Regional Preliminary, Lightning Routing I](https://vjudge.net/problem/%E8%AE%A1%E8%92%9C%E5%AE%A2-A2290)
- [NOIP2007 Senior Group Tree Core](https://www.luogu.com.cn/problem/P1099)
- [SDOI2011 Fire Protection](https://www.luogu.com.cn/problem/P2491)
- [APIO2010 Patrol](https://www.luogu.com.cn/problem/P3629)