Given a rooted tree with a coin on some node. At each moment, the coin moves to a neighboring node with equal probability. Find the expected distance the coin moves to a neighboring node.

## Definitions

-   $T = (V, E)$: The tree under consideration
-   $d(u)$: The degree of node $u$
-   $w(u, v)$: The weight of the edge between nodes $u$ and $v$
-   $p_u$: The parent node of node $u$
-   $\textit{root}$: The root node of the tree
-   $\textit{son}_u$: The set of child nodes of node $u$
-   $\textit{sibling}_u$: The set of sibling nodes of node $u$

## Expected Distance to Parent Node

Let $f(u)$ represent the expected distance from node $u$ to its parent $p_u$. Then:

$$
f(u) = \cfrac{w(u,p_u) + \sum\limits_{v \in \textit{son}_u}(w(u,v) + f(v) + f(u))}{d(u)}
$$

The first part of the numerator represents directly moving to the parent node. The second part represents first moving to a child node, then coming back from that child node, and then moving to the parent node. The denominator $d(u)$ represents that the probability of moving from $u$ to any neighboring node is equal.

Simplifying:

$$
\begin{aligned}
    f(u) &= \cfrac{w(u,p_u) + \sum\limits_{v \in \textit{son}_u}(w(u,v) + f(v) + f(u))}{d(u)} \\
         &= \cfrac{w(u,p_u) + \sum\limits_{v \in \textit{son}_u}(w(u,v) + f(v)) + (d(u)-1)f(u)}{d(u)} \\
         &= w(u,p_u) + \sum\limits_{v \in \textit{son}_u}(w(u,v) + f(v)) \\
         &= \sum\limits_{(u,t) \in E}w(u,t) + \sum\limits_{v \in \textit{son}_u}f(v)
\end{aligned}
$$

For a leaf node $l$, the initial condition is $f(l) = w(p_l, l)$.

When all edges in the tree have weight 1, the formula becomes:

$$
f(u) = d(u) + \sum\limits_{v \in \textit{son}_u}f(v)
$$

This is the sum of degrees of all nodes in the subtree of $u$, which is twice the size of subtree $u$ minus 1 (each edge contributes 2 to degree count, except the edge between $u$ and $p_u$ which contributes only 1).

## Expected Distance to Child Node

Let $g(u)$ represent the expected distance from $p_u$ to its child node $u$. Then:

$$
g(u) = \cfrac{w(p_u,u) + \left(w(p_u,p_{p_u})+g(p_u)+g(u)\right) + \sum\limits_{s \in \textit{sibling}_u}(w(p_u,s)+f(s)+g(u))}{d(p_u)}
$$

The first part of the numerator represents directly moving to child node $u$. The second part represents first moving to the parent node, then coming back, and then moving to $u$. The third part represents first moving to a sibling node of $u$, then coming back, and then moving to $u$. The denominator $d(p_u)$ represents that the probability of moving from $p_u$ to any neighboring node is equal.

Simplifying:

$$
\begin{aligned}
    g(u) &= \cfrac{w(p_u,u) + \left(w(p_u,p_{p_u})+g(p_u)+g(u)\right) + \sum\limits_{s \in \textit{sibling}_u}(w(p_u,s)+f(s)+g(u))}{d(p_u)} \\
         &= \cfrac{w(p_u,u) + w(p_u,p_{p_u}) + g(p_u) + \sum\limits_{s \in \textit{sibling}_u}\left(w(p_u,s)+f(s)\right)+(d(p_u)-1)g(u)}{d(p_u)} \\
         &= w(p_u,u) + w(p_u,p_{p_u}) + g(p_u) + \sum\limits_{s \in \textit{sibling}_u}(w(p_u,s)+f(s)) \\
         &= \sum\limits_{(p_u,t) \in E}w(p_u,t) + g(p_u) + \sum\limits_{s \in \textit{sibling}_u}f(s) \\
         &= \sum\limits_{(p_u,t) \in E}w(p_u,t) + g(p_u) + \left(f(p_u)-\sum\limits_{(p_u,t) \in E}w(p_u,t)-f(u)\right) \\
         &= g(p_u) + f(p_u) - f(u)
\end{aligned}
$$

The initial condition is $g(\text{root}) = 0$.

## Implementation (Unweighted Tree Example)

```cpp
vector<int> G[MAXN];

void dfs1(int u, int p) {
  f[u] = G[u].size();
  for (auto v : G[u]) {
    if (v == p) continue;
    dfs1(v, u);
    f[u] += f[v];
  }
}

void dfs2(int u, int p) {
  if (u != root) g[u] = g[p] + f[p] - f[u];
  for (auto v : G[u]) {
    if (v == p) continue;
    dfs2(v, u);
  }
}
```