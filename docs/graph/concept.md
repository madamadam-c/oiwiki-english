This page provides an overview of some concepts in graph theory. Not all of these concepts are commonly seen in OI (Olympiad in Informatics). For OIers, it is sufficient to master the basic parts of this page. If you encounter concepts you don't understand while studying, you can refer back to this page.

??? warning "Warning"
    Definitions of graph theory concepts may vary across different textbooks. Always interpret them based on context.

## Graph

A **graph** $G$ is a pair $G=(V(G), E(G))$ where $V(G)$ is a non-empty set called the **vertex set**, and each element of $V$ is called a **vertex** or **node**, simply a **point**; $E(G)$ is the set of edges between nodes in $V(G)$, called the **edge set**.

We commonly use $G=(V,E)$ to denote a graph.

When both $V$ and $E$ are finite sets, $G$ is called a **finite graph**.

When $V$ or $E$ is an infinite set, $G$ is called an **infinite graph**.

There are various types of graphs, including **undirected graphs**, **directed graphs**, **mixed graphs**, etc.

If $G$ is an undirected graph, each element in $E$ is an unordered pair $(u, v)$, called an **undirected edge** or simply **edge**, where $u, v \in V$. For $e = (u, v)$, $u$ and $v$ are called the **endpoints** of $e$.

If $G$ is a directed graph, each element in $E$ is an ordered pair $(u, v)$, sometimes written as $u \to v$, called a **directed edge** or **arc**. It can also be called an **edge** when there is no ambiguity. For $e = u \to v$, $u$ is called the **tail** of $e$, and $v$ is called the **head** of $e$. The tail and head are also called the **endpoints** of $e$. We also say $u$ is a direct predecessor of $v$, and $v$ is a direct successor of $u$.

???+ note "Why is the starting point called 'tail' and the ending point 'head'?"
    Edges are usually represented with arrows, and arrows point from the "tail" to the "head".

If $G$ is a mixed graph, $E$ contains both **directed edges** and **undirected edges**.

If each edge $e_k=(u_k,v_k)$ of $G$ is assigned a number as the **weight** of that edge, $G$ is called a **weighted graph**. If all weights are positive real numbers, $G$ is called a **positively weighted graph**.

The number of vertices $\left| V(G) \right|$ in graph $G$ is also called the **order** of graph $G$.

In simple terms, a graph consists of several points and the edges connecting them.

## Adjacency

In an undirected graph $G = (V, E)$, if vertex $v$ is an endpoint of edge $e$, then $v$ and $e$ are said to be **incident** or **adjacent**. For two vertices $u$ and $v$, if edge $(u, v)$ exists, $u$ and $v$ are said to be **adjacent**.

The **neighborhood** of a vertex $v \in V$ is the set of all vertices adjacent to it, denoted $N(v)$.

The neighborhood of a vertex set $S$ is the set of all vertices adjacent to at least one vertex in $S$, denoted $N(S)$, that is:

$$
N(S) = \bigcup_{v \in S} N(v)
$$

## Simple Graph

**Loop**: For an edge $e = (u, v)$ in $E$, if $u = v$, then $e$ is called a loop.

**Multiple edge (parallel edge)**: If there exist two identical elements (edges) $e_1, e_2$ in $E$, they are called (a set of) multiple edges.

**Simple graph**: A graph without loops or multiple edges is called a simple graph. In any simple undirected graph with at least two vertices, there must exist vertices with the same degree. ([Pigeonhole principle](../math/combinatorics/drawer-principle.md))

If a graph contains loops or multiple edges, it is called a **multigraph**.

??? warning "Warning"
    In undirected graphs, $(u, v)$ and $(v, u)$ count as one set of multiple edges. In directed graphs, $u \to v$ and $v \to u$ are not multiple edges.

??? warning "Warning"
    In problems, unless specified otherwise, loops and multiple edges are allowed. You need to consider them specially when solving problems.

## Degree

The number of edges incident to a vertex $v$ is called the **degree** of that vertex, denoted $d(v)$. Specifically, for edge $(v, v)$, each such edge contributes 2 to $d(v)$.

For an undirected simple graph, we have $d(v) = \left| N(v) \right|$.

Handshaking lemma (also called the fundamental theorem of graph theory): For any undirected graph $G = (V, E)$, we have $\sum_{v \in V} d(v) = 2 \left| E \right|$.

Corollary: In any graph, the number of vertices with odd degree must be even.

If $d(v) = 0$, then $v$ is called an **isolated vertex**.

If $d(v) = 1$, then $v$ is called a **leaf vertex** or **pendant vertex**.

If $2 \mid d(v)$, then $v$ is called an **even vertex**.

If $2 \nmid d(v)$, then $v$ is called an **odd vertex**. The number of odd vertices in a graph is even.

If $d(v) = \left| V \right| - 1$, then $v$ is called a **universal vertex**.

For a graph, the minimum degree among all vertices is called the **minimum degree** of $G$, denoted $\delta (G)$; the maximum degree is called the **maximum degree**, denoted $\Delta (G)$. That is: $\delta (G) = \min_{v \in G} d(v)$, $\Delta (G) = \max_{v \in G} d(v)$.

In a directed graph $G = (V, E)$, the number of edges with vertex $v$ as the starting point is called the **out-degree** of that vertex, denoted $d^+(v)$. The number of edges with vertex $v$ as the ending point is called the **in-degree** of that vertex, denoted $d^-(v)$. Clearly, $d^+(v)+d^-(v)=d(v)$.

For any directed graph $G = (V, E)$, we have:

$$
\sum_{v \in V} d^+(v) = \sum_{v \in V} d^-(v) = \left| E \right|
$$

If every vertex of an undirected graph $G = (V, E)$ has the same degree $k$, then $G$ is called a **$k$-regular graph**.

If a given sequence $a$ can be realized as the degree sequence of some graph $G$, then $a$ is called **graphical**.

If a given sequence $a$ can be realized as the degree sequence of some simple graph $G$, then $a$ is called **simple graphical**.

## Path

**Walk**: A walk is a sequence of edges connecting a sequence of vertices, which can be of finite or infinite length. Formally, a finite walk $w$ is a sequence of edges $e_1, e_2, \ldots, e_k$, such that there exists a sequence of vertices $v_0, v_1, \ldots, v_k$ satisfying $e_i = (v_{i-1}, v_i)$, where $i \in [1, k]$. Such a walk can be abbreviated as $v_0 \to v_1 \to v_2 \to \cdots \to v_k$. Typically, the number of edges $k$ is called the **length** of this walk (if edges are weighted, length usually refers to the sum of edge weights on the walk, though problems may define it differently).

**Trail**: For a walk $w$, if $e_1, e_2, \ldots, e_k$ are all distinct, then $w$ is called a trail.

**Path** (also called **simple path**): For a trail $w$, if the vertex sequence has no repeated vertices, then $w$ is called a path.

**Circuit**: For a trail $w$, if $v_0 = v_k$, then $w$ is called a circuit.

**Cycle** (also called **simple circuit**): For a circuit $w$, if $v_0 = v_k$ is the only pair of repeated vertices in the sequence, then $w$ is called a cycle.

??? warning "Warning"
    Definitions of "path" may vary in different sources. For example, "path" might refer to "walk" in this article, and "cycle" might refer to "circuit". If you see similar terms in problems without special explanations like "simple path" or "non-simple path" (i.e., "walk" in this article), it's best to ask for clarification.

## Subgraph

For a graph $G = (V, E)$, if there exists another graph $H = (V', E')$ such that $V' \subseteq V$ and $E' \subseteq E$, then $H$ is called a **subgraph** of $G$, denoted $H \subseteq G$.

If for $H \subseteq G$, for all $\forall u, v \in V'$, whenever $(u, v) \in E$, we also have $(u, v) \in E'$, then $H$ is called an **induced subgraph** of $G$.

It is easy to see that the induced subgraph of a graph is determined solely by the vertex set. Therefore, the induced subgraph with vertex set $V'$ ($V' \subseteq V$) is denoted $G \left[ V' \right]$.

If $H \subseteq G$ satisfies $V' = V$, then $H$ is called a **spanning subgraph** of $G$.

Clearly, $G$ is itself a subgraph, spanning subgraph, and induced subgraph; the [edgeless graph](#special-graphs) is a spanning subgraph of $G$. The original graph $G$ and the edgeless graph are both trivial subgraphs of $G$.

If an undirected graph $G$ has a spanning subgraph $F$ that is $k$-regular, then $F$ is called a **$k$-factor** of $G$.

If a directed graph $G = (V, E)$ has an induced subgraph $H = G \left[ V^\ast \right]$ such that for all $v \in V^\ast$, if $(v, u) \in E$, then $u \in V^\ast$, then $H$ is called a **closed subgraph** of $G$.

## Connectivity

### Undirected Graph

For an undirected graph $G = (V, E)$, for $u, v \in V$, if there exists a walk such that $v_0 = u, v_k = v$, then $u$ and $v$ are **connected**. By definition, any vertex is connected to itself, and the two endpoints of any edge are connected.

If an undirected graph $G = (V, E)$ satisfies that any two vertices are connected, then $G$ is called a **connected graph**. This property of $G$ is called **connectivity**.

If $H$ is a connected subgraph of $G$, and there exists no $F$ such that $H\subsetneq F \subseteq G$ and $F$ is a connected graph, then $H$ is a **connected component** (maximally connected subgraph) of $G$.

### Directed Graph

For a directed graph $G = (V, E)$, for $u, v \in V$, if there exists a walk such that $v_0 = u, v_k = v$, then $u$ **reaches** $v$. By definition, any vertex can reach itself, and the tail of any edge can reach the head. (Connectivity in undirected graphs can be viewed as mutual reachability.)

If a directed graph has vertices where every pair is mutually reachable, then the graph is **strongly connected**.

If replacing all edges of a directed graph with undirected edges results in a connected graph, then the original directed graph is **weakly connected**.

Similar to connected components, there are **weakly connected components** (maximal weakly connected subgraphs) and **strongly connected components** (maximal strongly connected subgraphs).

For related algorithms, see [Strongly Connected Components](./scc.md).

### Cuts

For related algorithms, see [Articulation Points and Bridges](./cut.md) and [Biconnected Components](./bcc.md).

In this section, "connectivity" for directed graphs generally refers to "strong connectivity".

For a connected graph $G = (V, E)$, if $V'\subseteq V$ and $G\left[V\setminus V'\right]$ (i.e., removing vertices in $V'$ from $G$) is not connected, then $V'$ is a **vertex cut** of $G$. A vertex cut of size 1 is called a **cut vertex**.

For a connected graph $G = (V, E)$ and an integer $k$, if $|V|\ge k+1$ and $G$ has no vertex cut of size $k-1$, then $G$ is **$k$-vertex-connected**. The largest such $k$ is called the **vertex connectivity** of $G$, denoted $\kappa(G)$. (For non-complete graphs, vertex connectivity equals the size of the minimum vertex cut. For the complete graph $K_n$, vertex connectivity is $n-1$.)

For a graph $G = (V, E)$ and vertices $u, v\in V$ with $u\ne v$, $u$ and $v$ are non-adjacent, and $u$ reaches $v$. If $V'\subseteq V$, $u, v\notin V'$, and in $G\left[V\setminus V'\right]$ $u$ and $v$ are not connected, then $V'$ is called a **vertex cut** from $u$ to $v$. The size of the minimum vertex cut from $u$ to $v$ is called the **local connectivity** from $u$ to $v$, denoted $\kappa(u, v)$.

Similar definitions can be made for edges:

For a connected graph $G = (V, E)$, if $E'\subseteq E$ and $G' = (V, E\setminus E')$ (i.e., removing edges in $E'$ from $G$) is not connected, then $E'$ is an **edge cut** of $G$. An edge cut of size 1 is called a **bridge**.

For a connected graph $G = (V, E)$ and an integer $k$, if $G$ has no edge cut of size $k-1$, then $G$ is **$k$-edge-connected**. The largest such $k$ is called the **edge connectivity** of $G$, denoted $\lambda(G)$. (For any graph, edge connectivity equals the size of the minimum edge cut.)

For a graph $G = (V, E)$ and vertices $u, v\in V$ with $u\ne v$, and $u$ reaches $v$. If $E'\subseteq E$, and in $G'=(V, E\setminus E')$ $u$ and $v$ are not connected, then $E'$ is called an **edge cut** from $u$ to $v$. The size of the minimum edge cut from $u$ to $v$ is called the **local edge-connectivity** from $u$ to $v$, denoted $\lambda(u, v)$.

**Biconnected** is almost identical to $2$-vertex-connected, except for a graph consisting of two vertices connected by one edge, which is biconnected but not $2$-vertex-connected. In other words, a connected graph without cut vertices is biconnected.

**$2$-edge-connected** is identical to $2$-edge-connected. In other words, a connected graph without bridges is $2$-edge-connected.

Similar to connected components, there are **biconnected components** (maximal biconnected subgraphs) and **$2$-edge-connected components** (maximal $2$-edge-connected subgraphs).

**Whitney's theorem**: For any graph $G$, we have $\kappa(G)\le \lambda(G)\le \delta(G)$. (The three terms are vertex connectivity, edge connectivity, and minimum degree.)

## Sparse Graph / Dense Graph

If a graph has far fewer edges than the square of its number of vertices, it is a **sparse graph**.

If a graph has a number of edges close to the square of its number of vertices, it is a **dense graph**.

These concepts do not have strict definitions. They are generally used when discussing efficiency differences between $O(|V|^2)$ and $O(|E|)$ algorithms (on dense graphs, these two algorithms have similar efficiency, while on sparse graphs, $O(|E|)$ algorithms are significantly more efficient).

## Complement Graph

For an undirected simple graph $G = (V, E)$, its **complement graph** is defined as follows: denoted $\bar G$, with $V \left( \bar G \right) = V \left( G \right)$, and for any pair of vertices $(u, v)$, $(u, v) \in E \left( \bar G \right)$ if and only if $(u, v) \notin E \left( G \right)$.

## Transpose Graph

For a directed graph $G = (V, E)$, its **transpose graph** has the same vertex set, with each edge reversed. That is, if the transpose of $G$ is $G'=(V, E')$, then $E'=\{(v, u)|(u, v)\in E\}$.

## Special Graphs

If an undirected simple graph $G$ has an edge between every pair of distinct vertices, then $G$ is called a **complete graph**. An $n$-vertex complete graph is denoted $K_n$. If a directed simple graph $G$ has two edges in opposite directions between every pair of distinct vertices, then $G$ is called a **complete digraph**.

A graph with empty edge set is called an **edgeless graph**, **empty graph**, or **null graph**. An $n$-vertex edgeless graph is denoted $\overline{K}_n$ or $N_n$. $N_n$ and $K_n$ are complement graphs of each other.

??? warning "Warning"
    **Null graph** can also refer to the **order-zero graph** $K_0$, which has both vertex set and edge set empty.

If a directed simple graph $G$ has exactly one edge (in one direction) between every pair of distinct vertices, then $G$ is called a **tournament graph**.

If an undirected simple graph $G = \left( V, E \right)$ has all its edges forming a cycle, then $G$ is called a **cycle graph**. An $n$-vertex ($n \geq 3$) cycle graph is denoted $C_n$. It is easy to see that a graph is a cycle graph if and only if it is a $2$-regular connected graph.

If an undirected simple graph $G = \left( V, E \right)$ has a vertex $v$ that is a universal vertex, and no edges between other vertices, then $G$ is called a **star graph**. An $n + 1$-vertex ($n \geq 1$) star graph is denoted $S_n$.

If an undirected simple graph $G = \left( V, E \right)$ has a vertex $v$ that is a universal vertex, and other vertices form a cycle, then $G$ is called a **wheel graph**. An $n + 1$-vertex ($n \geq 3$) wheel graph is denoted $W_n$.

If an undirected simple graph $G = \left( V, E \right)$ has all its edges forming a simple path, then $G$ is called a **path graph**. An $n$-vertex path graph is denoted $P_n$. It is easy to see that a path can be obtained by removing one edge from a cycle graph.

If an undirected connected graph contains no cycles, it is called a **tree**. For more details, see [Tree Basics](./tree-basic.md).

If an undirected connected graph contains exactly one cycle, it is called a **pseudotree**.

If a directed weakly connected graph has in-degree 1 for every vertex, it is called an **in-tree** (or rooted out-tree).

If a directed weakly connected graph has out-degree 1 for every vertex, it is called an **out-tree** (or rooted in-tree).

Multiple trees can form a **forest**, multiple pseudotrees can form a **pseudoforest**, multiple in-trees can form an **in-forest**, and multiple out-trees can form an **out-forest** (also called a **functional graph**).

If an undirected connected graph has each edge belonging to at most one cycle, it is called a **cactus**. Multiple cacti can form a **desert**.

If the vertex set of a graph can be divided into two parts such that there are no edges within each part, then the graph is a **bipartite graph**. If in a bipartite graph every pair of vertices in different parts are connected by an edge, then the graph is a **complete bipartite graph** (or biclique). A complete bipartite graph with parts of size $n$ and $m$ is denoted $K_{n, m}$. For more details, see [Bipartite Graph](./bi-graph.md).

If a graph can be drawn on a plane with no two edges crossing except at their endpoints, then the graph is a **planar graph**. A necessary and sufficient condition for a graph to be planar is that none of its subgraphs is $K_5$ or $K_{3, 3}$. For a simple connected planar graph $G=(V, E)$ with $V\ge 3$, we have $|E|\le 3|V|-6$.

## Isomorphism

Two graphs $G$ and $H$, if there exists a bijection $f : V(G) \to V(H)$ such that $(u,v)\in E(G)$ if and only if $(f(u),f(v))\in E(H)$, then we say $f$ is an **isomorphism** from $G$ to $H$, and graphs $G$ and $H$ are **isomorphic**, denoted $G \cong H$.

From the definition, if $G \cong H$, the following must hold:

-   $|V(G)|=|V(H)|,|E(G)|=|E(H)|$
-   The non-increasing sequences of vertex degrees in $G$ and $H$ are identical
-   $G$ and $H$ have isomorphic induced subgraphs

## Binary Operations on Undirected Simple Graphs

For undirected simple graphs, we can define the following binary operations:

**Intersection**: For graphs $G = \left( V_1, E_1 \right), H = \left( V_2, E_2 \right)$, the intersection is defined as $G \cap H = \left( V_1 \cap V_2, E_1 \cap E_2 \right)$.

It can easily be proven that the intersection of two undirected simple graphs is still an undirected simple graph.

**Union**: For graphs $G = \left( V_1, E_1 \right), H = \left( V_2, E_2 \right)$, the union is defined as $G \cup H = \left( V_1 \cup V_2, E_1 \cup E_2 \right)$.

**Sum/Direct Sum/Disjoint Union**: For $G = \left( V_1, E_1 \right), H = \left( V_2, E_2 \right)$, construct $H' \cong H$ such that $V \left( H' \right) \cap V_1 = \varnothing$ ($H'$ can equal $H$). Any graph isomorphic to $G \cup H'$ is called the sum/direct sum/disjoint union of $G$ and $H$, denoted $G + H$ or $G \oplus H$.

If $G$ and $H$ have disjoint vertex sets, then $G \cup H = G + H$.

For example, a forest can be defined as the sum of several trees.

???+ note "Difference between Union and Sum"
    Think of it this way: "union" merges vertices and edges with the same names in the two graphs, while "sum" does not.

## Special Vertex Sets / Edge Sets

### Dominating Set

For an undirected graph $G=(V, E)$, if $V'\subseteq V$ and for every $v\in(V\setminus V')$ there exists an edge $(u, v)\in E$ with $u\in V'$, then $V'$ is a **dominating set** of $G$.

The size of the minimum dominating set of undirected graph $G$ is denoted $\gamma(G)$. Finding the minimum dominating set of a graph is [NP-hard](../misc/cc-basic.md#np-hard).

For a directed graph $G=(V, E)$, if $V'\subseteq V$ and for every $v\in(V\setminus V')$ there exists an edge $(u, v)\in E$ with $u\in V'$, then $V'$ is an **out-dominating set** of $G$. Similarly, we can define the **in-dominating set** of a directed graph.

The size of the minimum out-dominating set of directed graph $G$ is denoted $\gamma^+(G)$, and the size of the minimum in-dominating set is denoted $\gamma^-(G)$.

### Edge Dominating Set

For a graph $G=(V, E)$, if $E'\subseteq E$ and for every $e\in(E\setminus E')$ there exists an edge in $E'$ sharing an endpoint with $e$, then $E'$ is an **edge dominating set** of $G$.

Finding the minimum edge dominating set of a graph is [NP-hard](../misc/cc-basic.md#np-hard).

### Independent Set

For a graph $G=(V, E)$, if $V'\subseteq V$ and no two vertices in $V'$ are adjacent, then $V'$ is an **independent set** of $G$.

The size of the maximum independent set of graph $G$ is denoted $\alpha(G)$. Finding the maximum independent set of a graph is [NP-hard](../misc/cc-basic.md#np-hard).

### Matching

For a graph $G=(V, E)$, if $E'\subseteq E$ and no two distinct edges in $E'$ share a common endpoint, and no edge in $E'$ is a loop, then $E'$ is a **matching** of $G$, also called an **independent edge set**. If a vertex is an endpoint of some edge in the matching, it is called **matched** or **saturated**; otherwise, it is called **unmatched**.

A matching with the maximum number of edges is called a **maximum-cardinality matching**. The size of the maximum matching of graph $G$ is denoted $\nu(G)$.

If edges have weights, a matching with maximum total weight is called a **maximum-weight matching**.

If a matching becomes non-matching when any edge is added to it, then this matching is a **maximal matching**. The largest maximal matching is the maximum matching, and every maximum matching is a maximal matching. A maximal matching is always an edge dominating set, but an edge dominating set is not necessarily a matching. The minimum maximal matching and minimum edge dominating set have the same size, but the minimum edge dominating set is not necessarily a matching. Finding the minimum maximal matching is NP-hard.

If all vertices are matched in a matching, then this matching is a **perfect matching**. If exactly one vertex is unmatched in a matching, then this matching is a **near-perfect matching**.

Finding the number of matchings or perfect matchings in a general graph or bipartite graph is [#P-complete](../misc/cc-basic.md#p_1).

For a matching $M$, if a path starts at an unmatched vertex, and alternatingly contains edges in and not in the matching, then this path is called an **alternating path**. An alternating path that ends at an unmatched vertex is called an **augmenting path**.

**Tutte's theorem**: An $n$-vertex undirected graph $G$ has a perfect matching if and only if for any $V' \subset V(G)$, $p_{\text{odd}}(G-V')\leq |V'|$, where $p_{\text{odd}}$ denotes the number of odd-order connected components.

**Tutte's theorem (corollary)**: Every bridgeless 3-regular graph has a perfect matching.

### Vertex Cover

For a graph $G=(V, E)$, if $V'\subseteq V$ and for every $e\in E$, at least one endpoint of $e$ is in $V'$, then $V'$ is a **vertex cover** of $G$.

A vertex cover is necessarily a dominating set, but a minimal vertex cover is not necessarily a minimal dominating set.

A vertex set is a vertex cover if and only if its complement is an independent set. Therefore, the complement of a minimum vertex cover is a maximum independent set. Finding the minimum vertex cover of a graph is [NP-hard](../misc/cc-basic.md#np-hard).

The size of any matching in a graph is at most the size of any vertex cover. For a complete bipartite graph $K_{n, m}$, the maximum matching and minimum vertex cover both have size $\min(n, m)$.

### Edge Cover

For a graph $G=(V, E)$, if $E'\subseteq E$ and for every $v\in V$, $v$ is adjacent to at least one edge in $E'$, then $E'$ is an **edge cover** of $G$.

The size of a minimum edge cover is denoted $\rho(G)$, which can be obtained greedily from a maximum matching: for all unmatched vertices, add one adjacent edge to the maximum matching to obtain a minimum edge cover.

A maximum matching can also be obtained from a minimum edge cover: for each pair of edges in the minimum edge cover that share a common endpoint, delete one of them.

The size of a minimum edge cover plus the size of a maximum matching equals the number of vertices: $\rho(G)+\nu(G)=|V(G)|$.

The size of a maximum matching is at most the size of a minimum edge cover: $\nu(G)\le\rho(G)$. In particular, a perfect matching is always a minimum edge cover, which is the only case where the equality holds.

The size of any independent set is at most the size of any edge cover. For a complete bipartite graph $K_{n, m}$, the maximum independent set and minimum edge cover both have size $\max(n, m)$.

### Clique

For a graph $G=(V, E)$, if $V'\subseteq V$ and every pair of distinct vertices in $V'$ are adjacent, then $V'$ is a **clique** of $G$. The induced subgraph of a clique is a complete graph.

If adding any vertex to a clique makes it no longer a clique, then this clique is a **maximal clique**.

The size of the maximum clique of a graph is denoted $\omega(G)$. The size of the maximum clique equals the size of the maximum independent set in the complement graph: $\omega(G)=\alpha(\bar{G})$. Finding the maximum clique of a graph is [NP-hard](../misc/cc-basic.md#np-hard).

## References

[OI Transit - Graph Theory Concept Overview](https://yhx-12243.github.io/OI-transit/memos/14.html)

[Wikipedia](https://en.wikipedia.org/wiki/Glossary_of_graph_theory_terms) (and corresponding articles for related concepts)

Discrete Mathematics (Revised Edition), Tian Wencheng, Zhou Luxin, Tianjin Literature Publishing House, P184-187

Dai Yiqi, Hu Guanzhang, Chen Wei. Graph Theory and Algebraic Structures [M]. Beijing: Tsinghua University Press, 1995.
