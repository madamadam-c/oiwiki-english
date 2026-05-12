author: 310552025atNYCU, accelsao, Chrogeek, Enter-tainer, iamtwz, mcendu, Shen-Linwood, shuzhouliu, StudyingFather, t4rf9, Tiphereth-A, TrickEye, wlbksy, Xeonacid, yuhuoji, c-forrest, aaron20100919

## Introduction

A **matching**, or **independent edge set**, is a set of edges in a graph that share no common endpoints. Graph matching algorithms are commonly used in competitive programming and can be roughly divided into two categories: maximum matching and maximum weight matching. Since matching in a [bipartite graph](../bi-graph.md) is equivalent to a network flow problem and has good properties, it is relatively easier to handle. Therefore, we will first introduce algorithms for bipartite graphs, then discuss algorithms for general graphs.

## Matching in Graphs

Let $G=(V,E)$ be an undirected graph, where $V$ is the set of vertices and $E$ is the set of edges. If a set of edges $M\subseteq E$ contains no self-loops and no two edges share a common vertex, then $M$ is called a **matching** or **independent edge set** of graph $G$. An edge $e\in E$ that appears in matching $M$ is called a **matched edge**, otherwise it is called an **unmatched edge**. Similarly, a vertex $v\in V$ is called a **matched vertex** if it is an endpoint of a matched edge, otherwise it is called an **unmatched vertex**.

The size of a matching $M$ is the number of edges it contains. For (weighted) undirected graphs, the following concepts are often considered:

-   **Maximal matching**: A matching to which no more edges can be added. A maximal matching is not necessarily a maximum matching.

    ![maximal matching](images/graph-match-1.svg)

-   **Maximum matching** or **maximum cardinality matching**: A matching with the maximum number of edges. There may be more than one maximum matching, but the number of edges in a maximum matching is fixed and cannot exceed half the number of vertices in the graph.

    ![maximum cardinality matching](images/graph-match-2.svg)

-   **Maximum weight matching**: In a weighted graph, a matching with the maximum sum of edge weights.

    ![maximum weight matching](images/graph-match-3.svg)

-   **Maximum weight maximum cardinality matching**: Among all maximum matchings (those with the most edges), the one with the maximum sum of edge weights. That is, the maximum weight matching among all maximum cardinality matchings.

    ![maximum weight maximum cardinality matching](images/graph-match-4.svg)

-   **Perfect matching**: A matching in which every vertex is a matched vertex. A perfect matching is always a maximum matching. Any complete graph with an even number of vertices necessarily has a perfect matching.

-   **Near-perfect matching**: A matching with exactly one unmatched vertex. This can only occur when the graph has an odd number of vertices. A near-perfect matching is always a maximum matching. Any complete graph with an odd number of vertices necessarily has a near-perfect matching.

In competitive programming, graph matching problems primarily refer to finding maximum matchings or maximum weight matchings.

## Augmenting Paths

In graph matching algorithms, augmenting paths are the core structures used to improve matchings.

### Definition

For a graph $G=(V,E)$ and its matching $M$, we can define the following two types of (simple) paths:

-   An **alternating path** is a path that alternates between matched edges and unmatched edges.
-   An **augmenting path** is an alternating path that starts and ends at unmatched vertices.

Since an augmenting path has one more unmatched edge than matched edges, the number of edges in an augmenting path is always odd. If we flip the matched and unmatched edges along an augmenting path, it remains an alternating path, and the matching size increases by 1. The process of finding an augmenting path and flipping it to increase the matching size is called **augmentation**. In mathematical terms, augmentation corresponds to taking the symmetric difference of the matching $M$ and the augmenting path $P$, obtaining a new matching $M\oplus P$.

The following figure demonstrates how an augmentation operation increases the matching size from 2 to 3.

![augment-1](./images/augment-1.png)

### Berge's Lemma

Berge's lemma shows that improving a matching using augmenting paths is sufficient. That is, when no augmenting path can be found, we have already obtained a maximum matching.

???+ note "Berge's Lemma"
    For a graph $G=(V,E)$ and its matching $M$, the matching $M$ is maximum if and only if there exists no augmenting path relative to $M$.

??? note "Proof"
    The forward direction was already shown above: when there exists an augmenting path $P$, the matching $M\oplus P$ is larger than $M$, so $M$ cannot be a maximum matching.

    Conversely, we need to show that if there exists a matching $M'$ that is larger than $M$, then there must exist an augmenting path $P$ relative to $M$. To show this, consider the symmetric difference $M\oplus M'$. In the graph $(V,M\oplus M'$, each vertex has degree 0, 1, or 2; the connected components of such a graph must be paths, cycles, or isolated vertices. Moreover, the two edges adjacent to a vertex of degree 2 must come from different matchings, so the number of edges from $M$ and $M'$ in each cycle is equal. Since $M'$ is larger than $M$, there exists at least one path in which the number of edges from $M'$ exceeds the number from $M$; call this path $P$. Then both endpoints of $P$ are unmatched vertices in $M$, and $P$ is an alternating path relative to $M$, so $P$ must be an augmenting path relative to $M$. This completes the proof.

From this theorem, we can derive the core approach for finding maximum matchings:

-   Enumerate all unmatched vertices, searching for augmenting paths, until no augmenting path can be found.

In fact, after each augmentation operation, we don't need to re-enumerate all unmatched vertices. In the entire process of finding a maximum matching, each vertex only needs to be traversed once.

??? note "Proof"
    We only need to show that if, when enumeration reaches vertex $v$, there is no augmenting path starting from $v$, then even after several rounds of augmentation, there will still be no augmenting path starting from $v$. This shows that even if augmentation changes the matching, we don't need to re-check previously enumerated unmatched vertices.

    Suppose otherwise. That is, suppose $v$ is an already-enumerated unmatched vertex, and after some round of augmentation along an augmenting path $P$ from $u$ to $w$, a new augmenting path $P'$ starting from $v$ appears that didn't exist before. Then path $P'$ must share an edge with $P$; otherwise, augmenting along $P$ wouldn't change the matching status of any edge in $P'$, so $P'$ wouldn't be a newly created augmenting path due to this augmentation.

    ![augment-2](./images/augment-2.svg)

    (In the figure, black edges represent unmatched edges, while red and blue edges represent different matching states.)

    Let $x$ be the first vertex of $P$ encountered when traversing along $P'$ starting from $v$. Since there existed an alternating path from $v$ to $x$ before this augmentation, $x$ must be a matched vertex, and thus cannot be either vertex $u$ or vertex $w$. Therefore, on the augmenting path $P$, the two edges adjacent to $x$ have opposite matching status. This means that regardless of the matching status of the edge when arriving at vertex $x$ along an alternating path starting from $v$, we can extend the alternating path along path $P$ to reach either $u$ or $w$. This shows that before the augmentation, there already existed an augmenting path starting from $v$, contradicting our assumption.

### Alternating Trees

Another concept closely related to augmenting paths is the alternating tree. It is a tree generated during the process of searching for augmenting paths using DFS or BFS starting from an unmatched vertex.

For a graph $G=(V,E)$ and its matching $M$, if a subgraph $H\subseteq G$ is a tree rooted at an unmatched vertex $r$, and the path connecting $r$ and any $v\in H$ is an alternating path, then $H$ is called an **alternating tree**. Vertices at even depths in the tree are called even vertices, and vertices at odd depths are called odd vertices.

The following figure shows an alternating tree that might be obtained by starting BFS from unmatched vertex 1. (In the figure, red edges are matched edges, black edges are unmatched edges; dark vertices are matched vertices, light vertices are unmatched vertices.)

![](./images/alternating-tree.svg)

## Existence of Perfect Matchings

In graph matching theory, there are two important existence theorems that can be used to determine whether a perfect matching exists in a bipartite graph or general graph.

### Hall's Theorem

Assume $G=(X,Y,E)$ is a bipartite graph with $|X|\le |Y|$. For a matching $M$ of graph $G$, if all vertices in $X$ are matched vertices, then $M$ is called an **$X$-perfect matching**, sometimes simply called a (bipartite graph $G$) perfect matching. This is the largest matching that can be achieved in a bipartite graph. Hall's theorem provides a necessary and sufficient condition for the existence of such a matching.

Hall's theorem states that as long as for any subset of $X$, there are enough vertices in $Y$ that can be matched with it, an $X$-perfect matching must exist.

???+ note "Hall's Theorem"
    Assume $G=(X,Y,E)$ is a bipartite graph with $|X|\le |Y|$. For any $W\subseteq X$, let $N_G(W)$ be the set of all vertices in graph $G$ adjacent to vertices in $W$. Then an $X$-perfect matching exists if and only if $|W|\le |N_G(W)|$ holds for all $W\subseteq X$.

??? note "Proof"
    The condition is clearly necessary. Suppose an $X$-perfect matching $M$ exists, then every vertex in $X$ is matched to a distinct vertex in $Y$. The set $N_G(W)$ includes at least the vertices matched with vertices in $W$, so its size is at least $|W|$.

    The condition is also sufficient. Suppose no $X$-perfect matching exists, then there must be a maximum matching $M$ such that a vertex $v\in X$ remains unmatched. Let $Z$ be the set of all vertices reachable by alternating paths starting from $v$, and let $S=Z\cap X$, $T=Z\cap Y$. The set $S\setminus\{v\}$ must all be matched vertices, otherwise there would be an odd cycle, contradicting that $G$ is a bipartite graph. The set $T$ must also all be matched vertices, otherwise there would be an augmenting path, contradicting that $M$ is a maximum matching by Berge's lemma. Since they are all matched vertices, and matching can only occur between $X$ and $Y$, the vertices in $S\setminus\{v\}$ correspond one-to-one with vertices in $T$, so $|T|=|S|-1$. Since vertices in $T$ are already matched with vertices in $S$, we have $T\subseteq N_G(S)$. However, there is no unmatched vertex in $N_G(S)$, because if there were an unmatched vertex $u$ adjacent to some $v'$ in $S$, we could extend the alternating path reaching $v'$ to reach $u$. This shows $T=N_G(S)$. These arguments show $|N_G(S)|<|S|$, which contradicts the condition assumed in Hall's theorem. This proves that an $X$-perfect matching exists.

???+ note "Corollary"
    Every regular bipartite graph has a perfect matching.

??? note "Proof"
    In a regular bipartite graph, all vertices have the same degree, say $k$. First verify that Hall's condition holds, i.e., for any $W\subseteq X$, we have $|N_G(W)|\ge |W|$. The number of edges adjacent to vertices in $W$ is $k|W|$, and each vertex in $N_G(W)$ can be adjacent to at most $k$ of these edges, so we must have $k|W|\le k|N_G(W)|$, i.e., $|W|\le |N_G(W)|$. In particular, we have $|X|\le |Y|$; since $X$ and $Y$ are symmetric, we have $|X|=|Y|$. This shows that in a regular bipartite graph, an $X$-perfect matching is also a perfect matching. Since Hall's theorem guarantees the existence of an $X$-perfect matching, a perfect matching must also exist.

### Tutte's Theorem

Tutte's theorem provides a necessary and sufficient condition for the existence of perfect matchings in general graphs. This condition comes from a direct observation: a graph with an odd number of vertices cannot have a perfect matching.

???+ note "Tutte's Theorem"
    A graph $G=(V,E)$ has a perfect matching if and only if for every $U\subseteq V$, we have $\operatorname{odd}(G-U)\le |U|$, where $G-U$ denotes the subgraph obtained by deleting vertices in $U$ and all edges incident to them from graph $G$, and $\operatorname{odd}(G-U)$ denotes the number of connected components of $G-U$ that have an odd number of vertices.

??? note "Proof"
    We only need to consider simple graphs, since multiple edges and self-loops do not affect Tutte's condition or the existence of perfect matchings.

    The necessity of the condition is relatively straightforward. Suppose a perfect matching $M$ exists. For any $U\subseteq V$, after removing vertices in $U$ from graph $G$, each connected component with an odd number of vertices has at least one vertex that cannot be matched with vertices in the same connected component; these vertices must seek to be matched with vertices in $U$. For such a matching to exist, we must have $\operatorname{odd}(G-U)\le |U|$. This is the Tutte condition.

    The sufficiency of the condition is more complex. Suppose $G$ satisfies the Tutte condition but has no perfect matching. Since adding any edge to $G$ would still satisfy the Tutte condition, we may assume $G$ is a maximal such graph; that is, $G$ has no perfect matching, but for any non-existent edge $e$, $G+e$ has a perfect matching. Let $U\subseteq V$ be the set of all vertices with degree $|V|-1$. It can be shown that each connected component of $G-U$ is a complete graph. From this, we can construct a perfect matching of $G$: first take a maximum matching of each connected component of $G-U$; only when a connected component has an odd number of vertices does one unmatched vertex appear; then match these unmatched vertices to vertices in $U$; since $G$ has an even number of vertices (taking $U=\varnothing$ in the Tutte condition), the remaining unmatched vertices in $U$ are also even in number, so they can be paired up. This contradiction shows that there is no $G$ that satisfies the Tutte condition but has no perfect matching.

    The key is to prove that each connected component of $G-U$ is a complete graph. Suppose not. Let vertices $x,y,z$ belong to such a connected component with $(x,y)\in E$, $(y,z)\in E$, but $(x,z)\notin E$. Moreover, since $y\notin U$, there exists $w\in V\setminus U$ such that $(y,w)\notin E$. Due to the maximality of $G$, graphs $G+(x,z)$ and $G+(y,w)$ each have perfect matchings $M_1$ and $M_2$ respectively. Consider their symmetric difference $M_1\oplus M_2$. Since in the graph $(V,M_1\oplus M_2)$ all vertices have degree either 0 or 2, $M_1\oplus M_2$ is actually a disjoint union of even cycles, where each even cycle consists of alternating matched edges from $M_1$ and $M_2$.

    ![](./images/tutte-proof.svg)

    As shown in the figure, there are two cases:

    -   $(x,z)$ and $(y,w)$ are in different cycles (as shown on the left): let $C$ be the cycle containing $(y,w)$, then the edge set $M_2\oplus C$ is a perfect matching of $G$.
    -   $(x,z)$ and $(y,w)$ are in the same cycle (as shown on the right): by symmetry, assume the cycle goes through $x,y,w,z$ in order; then take the path from $y$ through $w$ to $z$ along the cycle, call it $P$, and let $C = \{(y,z)\}\cup P$ be the cycle; then the edge set $M_2\oplus C$ is also a perfect matching of $G$.

    In either case, this contradicts the choice of $G$. This contradiction shows that each connected component of $G-U$ is a complete graph.

???+ note "Corollary"
    Every bridgeless 3-regular graph has a perfect matching.

??? note "Proof"
    To verify that the Tutte condition holds, for any $U\subseteq V$, we need to prove $\operatorname{odd}(G-U)\le |U|$. Let $G_1,\cdots,G_n$ be all connected components of $G-U$ with an odd number of vertices. Let $m_i$ be the number of edges connecting vertices in $G_i$ to vertices in $U$. Simple counting shows

    $$
    3|V(G_i)| = \sum_{v\in V(G_i)} d(v) = 2|E(G_i)| + m_i.
    $$

    Therefore, $m_i$ must be odd. Since $G$ has no bridges (i.e., cut edges), we have $m_i\ge 3$. This shows

    $$
    \operatorname{odd}(G-U) = n \le \dfrac{1}{3}\sum_{i=1}^n m_i \le \dfrac{1}{3}\sum_{v\in U} d(v) = |U|.
    $$

    Therefore, the Tutte condition holds, and graph $G$ must have a perfect matching.

## Common Algorithms

A fundamental problem in combinatorial optimization is finding maximum matchings and maximum weight matchings in graphs.

### Maximum Matching in Bipartite Graphs

See the [Maximum Matching in Bipartite Graphs](./bigraph-match.md) page.

In an unweighted bipartite graph, the Kuhn algorithm can solve it in $O(|V||E|)$ time, or the Hopcroft–Karp algorithm can solve it in $O(|V|^{1/2}|E|)$ time.

### Maximum Weight Matching in Bipartite Graphs

See the [Maximum Weight Matching in Bipartite Graphs](./bigraph-weight-match.md) page.

In a weighted bipartite graph, the Hungarian algorithm can be used. If Bellman–Ford is used for shortest path finding, the time complexity is $O(|V|^2|E|)$; if Dijkstra's algorithm or Fibonacci heap is used, it can be solved in $O(|V|^{2}\log {|V|}+|V||E|)$ time.

### Maximum Matching in General Graphs

See the [Maximum Matching in General Graphs](./general-match.md) page.

In an unweighted general graph, Edmonds' blossom algorithm can solve it in $O(|V|^2|E|)$ time.

### Maximum Weight Matching in General Graphs

See the [Maximum Weight Matching in General Graphs](./general-weight-match.md) page.

In a weighted general graph, Edmonds' blossom algorithm can solve it in $O(|V|^2|E|)$ time.

## Related Problems

Maximum (weight) matchings are closely related to other graph theory problems. This section only discusses general graphs; the conclusions for bipartite graphs can be found on the [Maximum Matching in Bipartite Graphs](./bigraph-match.md#related-problems) page.

### Maximum Weight Maximum Cardinality Matching

The maximum weight maximum cardinality matching problem and the maximum weight matching problem can be reduced to each other. A notable difference between them is that maximum weight maximum cardinality matching may contain negative-weight edges, while maximum weight matching cannot.

First, the maximum weight matching problem can be reduced to the maximum weight maximum cardinality matching problem. First, set the weights of all negative-weight edges in graph $G$ to 0; then, by connecting several edges with weight 0, expand the graph to a complete graph $G'$. Note that in a complete graph with non-negative edge weights, maximum weight maximum cardinality matching and maximum weight matching coincide. Therefore, we only need to compute the maximum weight maximum cardinality matching $M'$ of $G'$, and then delete all zero-weight edges from $M'$; the resulting edge set $M$ is the maximum weight matching of graph $G$.[^other-approach]

![graph-match](images/graph-match-5.svg)

Conversely, the maximum weight maximum cardinality matching problem can also be reduced to the maximum weight matching problem. We only need to add a sufficiently large positive constant $K$ to the weight of all edges in graph $G$ to ensure that the maximum weight matching of the resulting graph $G'$ is also a maximum matching, and thus necessarily a maximum weight maximum cardinality matching. This is because computing the maximum weight matching of $G'$ is equivalent to maximizing

$$
K|M| + \sum_{e\in M}w(e)
$$

over all matchings in graph $G$.

When $K$ is sufficiently large, the gain $K$ from adding one more edge to the matching exceeds any possible change in the sum of edge weights. Therefore, the algorithm will first try to match as many edges as possible, then maximize the sum of edge weights of matched edges. The constant $K$ only needs to be strictly greater than the difference between two possible matchings. An obvious choice is

$$
K = \sum_{e\in E}|w(e)| + 1.
$$

![graph-match](images/graph-match-6.svg)

### Minimum (Weight) Edge Cover

Another problem closely related to maximum (weight) matchings is the minimum (weight) edge cover. The relationship between edge covers and matchings (also called edge independent sets) is similar to the relationship between vertex covers and independent sets.

A set of edges $C\subseteq E$ in a graph $G=(V,E)$ is called an **edge cover** if every vertex $v\in V$ is an endpoint of some edge in $C$. When discussing edge covers, we always assume that graph $G$ has no isolated vertices.

For unweighted graphs, the minimum edge cover problem is almost equivalent to the maximum matching problem. For any maximum matching $M$ of graph $G$, by adding one incident edge for each unmatched vertex, we can obtain a minimum edge cover $C$. Their sizes satisfy a simple relationship: $|M|+|C|=|V|$. The following figure shows some examples of minimum edge covers:

![graph-match](images/graph-match-7.svg)

For weighted graphs, the minimum weight edge cover problem can be reduced to a **minimum weight perfect matching** problem. First, copy graph $G=(V,E)$ to obtain $\tilde G=(\tilde V,\tilde E)$, with the same edge weights as the original; then, for each vertex $v\in V$, connect it to its copy $\tilde v\in\tilde V$ with an edge weight equal to the minimum weight of edges incident to $v$ in graph $G$. Denote the resulting graph as $G'=(V',E')$. If graph $G$ is a bipartite graph or a sparse graph, then graph $G'$ is also a bipartite graph or sparse graph respectively. Moreover, the minimum weight edge cover problem of graph $G$ is reduced to the minimum weight perfect matching problem of graph $G'$[^edge-cover]: for the minimum weight perfect matching $M'$ of $G'$, by retaining edges in $E$ and replacing all matched edges $(v,v')$ with the minimum weight edge incident to $v$ in graph $G$, we obtain a minimum weight edge cover of graph $G$.

## References

1.  [Wikiwand - Matching (graph theory)](https://www.wikiwand.com/en/Matching_%28graph_theory%29)
2.  [Wikiwand - Blossom algorithm](https://www.wikiwand.com/en/Blossom_algorithm)
3.  2015 "A Brief Discussion on Graph Matching Algorithms and Their Applications" - Yinbo Chen
4.  [Algorithm Notes - Matching](http://web.ntnu.edu.tw/~algo/Matching.html)
5.  [the-tourist/algo](https://github.com/the-tourist/algo)
6.  [Bill Yang's Blog - Blossom Algorithm Notes](https://blog.bill.moe/blossom-algorithm-notes/)
7.  [Maximum Matching, Perfect Matching and Hungarian Algorithm in Bipartite Graphs](https://www.renfei.org/blog/bipartite-matching.html)
8.  [Wikiwand - Hopcroft–Karp algorithm](https://www.wikiwand.com/en/Hopcroft%E2%80%93Karp_algorithm)
9.  Bondy, John Adrian, and Uppaluri Siva Ramachandra Murty. Graph theory with applications. Vol. 290. London: Macmillan, 1976.

[^other-approach]: Of course, this is not the only reduction method. For graph $G=(V,E)$, we can also take a copy $\tilde G=(\tilde V,\tilde E)$ and connect it pointwise to the original graph, setting the weights of all newly added edges (including edges in the copy) to 0, to obtain graph $G'=(V',E')$. In other words, the vertex set of the new graph $G'$ is $V\cup\tilde V$, and its edge set, besides edges in $G$, also connects each vertex $v\in V$ to its copy $\tilde v$ with a zero-weight edge, and for each edge $(u,v)\in E$, connects $\tilde u$ to $\tilde v$ with a zero-weight edge. Every matching $M$ in graph $G$ corresponds to a perfect matching in graph $G'$ with the same total weight: simply match all unmatched vertices $v$ in $G$ with their copies $\tilde v$, and for each matched edge $(u,v)$, match $\tilde u$ with $\tilde v$. Therefore, the maximum weight maximum cardinality matching in $G'$, which is also the maximum weight perfect matching, when restricted to $E$, gives the maximum weight matching of $G$. The benefit of this reduction is that if $G$ is a bipartite graph or sparse graph, then the expanded graph $G'$ is also a bipartite graph or sparse graph respectively.

[^edge-cover]: For every perfect matching $M'$ in $G'$, we can obtain an edge cover $C$ of $G$ as described here, and the total weight of the latter is half of that of the former; conversely, for every edge cover $C$ of $G$, we can construct a perfect matching $M'$ of $G'$ whose total weight is at most twice that of $C$. This shows the reduction is valid.