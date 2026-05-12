This article introduces (planar) planar graphs and related concepts.

## Planar Graphs

If a graph $G$ can be drawn on a plane $S$ such that edges do not intersect except at vertices, then we say $G$ can be embedded on plane $S$, and $G$ is a **planar graph**. The drawn graph without edge intersections is called a planar embedding or **plane embedding** of $G$. This planar embedding of a planar graph is also called a **plane graph**.

???+ info ""Planar Graph""
    In different texts, the meaning of "planar graph" may vary. In the definitions of this article, a planar graph is a graph-theoretic object that may be embedded in the plane in different ways; a plane graph is a geometric object that, in addition to the graph-theoretic structure, also requires specifying the drawing method of the graph. The same planar graph often corresponds to multiple plane graphs. Therefore, in this article, if a conclusion depends only on the graph-theoretic structure, we will use the term "planar graph"; if it also depends on the plane embedding method of the graph, we will use the term "plane graph".

Here are simple examples of planar graphs:

![](images/planar-1.svg)

(Left: Butterfly graph; Right: Complete graph $K_4$ of order $4$)

Here are simple examples of non-planar graphs:

![](images/planar-2.svg)

(Left: Complete graph $K_5$ of order $5$; Right: Complete bipartite graph $K_{3,3}$ with 3 vertices in each part)

## Properties

This section introduces properties of planar graphs.

### Faces and Their Degrees

Let $G$ be a plane graph. The plane where $G$ lies is divided into several regions by the edges of $G$. Each region is called a **face** of $G$. The face with no boundary is called the **unbounded face** or **external face**, and those with boundaries are called bounded faces or internal faces. Each plane graph has exactly one external face.

The set of all edges surrounding each face is called the **boundary** of that face, and edges in the boundary are said to be **incident** with that face. The length of the boundary is called the **degree** of that face. When computing the degree of a face, each bridge is counted twice. In a plane graph, the sum of the degrees of all faces equals $2|E|$.

In plane graphs, a face of degree $1$ corresponds to a self-loop in the graph, and a face of degree $2$ usually corresponds to a pair of parallel edges in the graph[^face-2]. In a simple connected plane graph with $|V| \ge 3$, all faces have degree at least $3$.

### Euler's Formula

An important property of planar graphs is **Euler's formula**. It gives the relationship between the number of vertices $|V|$, number of edges $|E|$, and number of faces $|F|$ in a graph.

???+ note "Euler's Formula"
    For a connected plane graph $G$, we have
    
    $$
    |V| - |E| + |F| = 2.
    $$

??? note "Proof"
    Apply mathematical induction on the number of faces $|F|$. The base case is $|F|=1$. At this time, the plane graph has only one external face, and all edges are bridges. So graph $G$ is a tree, and we must have $|E|=|V|-1$. Substituting into Euler's formula shows it holds. Assume Euler's formula holds for plane graphs with $|F| = k$. For a plane graph $G$ with $|F|=k + 1$, there must be a non-bridge edge $e$, which is a common edge of two distinct faces. Remove edge $e$ from the graph to obtain graph $G-e$, which has $|V|$ vertices, $|E|-1$ edges, and $|F|-1$ faces. By the induction hypothesis, Euler's formula holds for $G-e$, i.e., $|V|-(|E|-1)+(|F|-1)=2$. Rearranging gives Euler's formula for $G$. Therefore, by mathematical induction, Euler's formula holds for all plane graphs.

???+ note "Corollary"
    For a planar graph $G$ with $k$ connected components, we have
    
    $$
    |V| - |E| + |F| = k + 1.
    $$

??? note "Proof"
    Each connected component of $G$ is a plane graph, but these connected components share the same external face. So applying Euler's formula directly to these connected components and summing them together gives the correct total number of vertices and edges, but the total number of faces is off by $(k-1)$ because the unique external face is counted $k$ times. Taking this correction into account yields $|V|-|E|+|F| = 2k - (k-1) = k+1$.

From this, we can derive the relationship between the number of edges and vertices in a planar graph.

???+ note "Theorem"
    For a planar graph $G$ with $k$ connected components, if each face of $G$ has degree at least $l \ge 3$, then
    
    $$
    |E| \le \dfrac{l}{l-2}(|V|-k-1).
    $$

??? note "Proof"
    Since each face of $G$ has degree at least $l$, the sum of the degrees of all faces is at least $l|F|$, i.e., $2|E| \ge l|F|$. Substituting from the corollary of Euler's formula $|V| - |E| + |F| = k + 1$, we get
    
    $$
    2|E| \ge l(k + 1 - |V| + |E|).
    $$
    
    Solving for $|E|$ using $l \ge 2$ gives
    
    $$
    |E| \le \dfrac{l}{l-2}(|V|-k-1).
    $$

???+ note "Corollary"
    Let $G$ be a simple planar graph and $|V|\ge 3$. Then
    
    $$
    |E| \le 3|V|-6.
    $$

??? note "Proof"
    When $G$ is connected, all faces have degree at least $3$. Taking $k=1$ and $l=3$ in the above theorem gives $|E|\le 3|V|-6$.
    
    When $G$ is not connected, there are two cases:
    
    -   If there exists a connected component with at least $3$ vertices, then for each connected component with at least $3$ vertices, we can establish the inequality $|E_i|\le 3|V_i|-6$. Since connected components with fewer than $3$ vertices must have $|E_i|\le |V_i| \le 3|V_i|$. Adding up the inequalities for all connected components gives $|E|\le 3|V|-6$.
    -   If all connected components have fewer than $3$ vertices, then we must have $|E|\le |V|$. Since when $|V|\ge 3$, $|V|\le 3|V|-6$, the inequality $|E|\le 3|V|-6$ still holds.
    
    In summary, the proposition is proved.

This corollary shows that simple planar graphs are sparse graphs.

### Dual Graph

Every plane graph has a corresponding (geometric) dual graph.

![](images/planar-dual-1.svg)

Let $G$ be a plane graph. We can draw graph $G^*$ as follows:

1.  Draw a point $v_i^*$ inside each face $f_i$ of $G$.
2.  For each edge $e$ of $G$, if $e$ is on the common boundary of faces $f_i$ and $f_j$, draw an edge $e^*$ connecting $v_i^*$ and $v_j^*$ that intersects $e$ exactly once and does not intersect any other edges of $G$ or $G^*$. In particular, when $e$ appears only on the boundary of a single face $f_i$, we need to draw a self-loop incident with $v_i^*$ that intersects $e$.

The resulting graph $G^*$ is called the **dual graph** of $G$.

???+ note "Theorem"
    Let $G^*$ be the dual graph of a plane graph $G$. Then $G^*$ is a connected plane graph. Moreover, $G^{**}$ is isomorphic to $G$ if and only if $G$ is connected.

??? note "Proof"
    That $G^*$ is a plane graph is guaranteed by its construction. We also need to prove that $G^*$ is connected. For any two vertices $v^*_i,v^*_j$ in $G^*$, suppose the line segment in the plane connecting $v^*_i$ and $v^*_j$ passes through faces and edges of $G$ in order: $f_i,e_{s_1},f_{s_1},\cdots,f_{s_{r-1}},e_{s_r},f_j$. They correspond to vertices and edges in the dual graph: $v_i^*,e_{s_1}^*,v^*_{s_1},\cdots,v^*_{s_{r-1}},e^*_{s_r},v^*_j$. From the construction of $G^*$, adjacent vertices and edges in the sequence are incident, so this describes a path in $G^*$. Therefore, $G^*$ is connected.
    
    $G^{**}$ is the dual graph of $G^*$, so it is necessarily connected. Thus, a necessary condition for $G$ to be isomorphic to $G^{**}$ is that $G$ is connected. Next, we need to prove this condition is also sufficient. For this, we only need to prove that when $G$ is connected, $G$ satisfies the construction requirements of the dual graph of $G^*$. Since the edges of $G^*$ naturally correspond to edges of $G$, we only need to prove that each face of $G^*$ contains exactly one vertex of $G$. For any face $f^*$ of $G^*$, let $e^*$ be an edge on its boundary. Then one endpoint of the corresponding edge $e$ in $G$ must be inside face $f^*$. Therefore, face $f^*$ contains at least one vertex of $G$. Since both $G^*$ and $G$ are connected, Euler's formula holds. $G$ and $G^*$ have the same number of edges, and the number of faces of $G$ equals the number of vertices of $G^*$. So the number of vertices of $G$ equals the number of faces of $G^*$. Therefore, each face of $G^*$ contains exactly one vertex of $G$. The proposition is proved.

There are many structural correspondences between a plane graph and its dual graph:

-   Faces in $G$ correspond to vertices in $G^*$, edges in $G$ correspond to edges in $G^*$, and vertices in $G$ correspond to faces in $G^*$.
-   Self-loops in $G$ correspond to bridges in $G^*$, and self-loops in $G^*$ correspond to bridges in $G$.
-   Edge cutsets in $G$ correspond to cycles in $G^*$, and cycles in $G^*$ correspond to edge cutsets in $G$.

It should be noted that the concept of dual graph only applies to specific plane graphs and cannot be defined on arbitrary planar graphs. In fact, dual graphs of isomorphic plane graphs are not necessarily isomorphic. That is, different planar embeddings of the same graph may have non-isomorphic dual graphs.

???+ example "Example"
    The figure below shows two isomorphic plane graphs, but their dual graphs are not isomorphic.
    
    ![](images/planar-dual-2.svg)
    
    The reason the dual graphs are not isomorphic is that the right figure has a degree-1 face, whose dual graph has a degree-1 vertex, while the left figure does not.

Transforming problems of plane graphs onto dual graphs sometimes makes them easier to solve. A typical example is that the [minimum cut](./flow/min-cut.md) problem on a plane graph can be transformed into a [shortest path](./shortest-path.md) problem on the dual graph. Let $G$ be a plane graph with edge weights, and $s,t$ be two vertices. We need to find the minimum $s$-$t$ cut.

![](images/planar-dual-3.svg)

As shown in the figure, by choosing a suitable planar embedding, we can always make $s$ and $t$ appear on the boundary of the external face of $G$. Additionally, add rays extending from $s$ and $t$ to divide the external face into two parts $f_{+}$ and $f_{-}$. Based on this graph, construct the dual graph and assign edge weights to the corresponding edges in the dual graph. Then, the path between vertices corresponding to faces $f_{+}$ and $f_{-}$ in the dual graph (shown in thick red lines) corresponds one-to-one to the $s$-$t$ cut in graph $G$ (shown in thick black lines), and they have the same weight. Thus, by finding the shortest path in the dual graph, we obtain the minimum $s$-$t$ cut in the dual graph.

### More Results

Of course, there are many famous results on planar graphs. This section briefly lists them without discussion.

???+ note "Four Color Theorem"
    (Without self-loops) planar graphs are all $4$-colorable.

???+ note "Fáry's Theorem"
    Simple planar graphs always have a planar embedding where all edges are straight line segments.

???+ note "Theorem (Wood)"
    A planar graph has at most $8|V|-16$ maximal cliques.

???+ note "Theorem (Tutte)"
    $4$-vertex-connected planar graphs are all Hamiltonian graphs.

## Recognition

This section discusses methods to determine whether a given graph is planar.

### Forbidden Graphs

The most classic characterization of planar graphs uses **forbidden graphs** (forbidden subgraphs).

First, $K_5$ and $K_{3,3}$ are not planar graphs.

???+ note "Theorem"
    $K_5$ and $K_{3,3}$ are not planar graphs.

??? note "Proof"
    As explained earlier, a simple connected plane graph with $|V|\ge 3$ must satisfy
    
    $$
    |E| \le \dfrac{l}{l-2}(|V|-2).
    $$
    
    Where $l$ is the minimum face degree. For $K_5$, we have $l=3,~|V|=5,~|E|=10$, so $K_5$ cannot be drawn as a planar graph. For $K_{3,3}$, we have $l=4,~|V|=6,~|E|=9$, so $K_{3,3}$ cannot be drawn as a planar graph.

In fact, they are the smallest structures that make a graph non-planar. That is, as long as a graph does not (in some way) contain these two graphs as substructures, the graph must be planar.

The first planarity testing theorem is Kuratowski's Theorem. It uses the concept of graph homeomorphism: If two graphs $G_1$ and $G_2$ are isomorphic, or become isomorphic after repeatedly inserting or removing degree-2 vertices, then they are said to be **homeomorphic**. From this, we can state:

???+ note "Kuratowski's Theorem"
    Graph $G$ is a planar graph if and only if $G$ contains no subgraph homeomorphic to $K_5$ or $K_{3,3}$.

Another related theorem is Wagner's Theorem. It characterizes planar graphs using the contraction operation. The contraction operation means repeatedly contracting an edge of a graph into a single vertex. From this, we can state:

???+ note "Wagner's Theorem"
    Graph $G$ is a planar graph if and only if $G$ contains no subgraph that can be contracted to $K_5$ or $K_{3,3}$.

That planar graphs do not contain such subgraphs is relatively obvious, so the key part of these two theorems is the sufficiency of the forbidden graph conditions. Since a subgraph homeomorphic to $K_5$ or $K_{3,3}$ can certainly be contracted to them, but not necessarily vice versa, Kuratowski's Theorem provides a weaker and easier-to-check condition for testing planarity.

### Planarity Testing Algorithms

Although it doesn't seem easy, there are actually many linear-time algorithms for planarity testing. However, because implementations of these algorithms are usually quite complex, they almost never appear in programming contests.

The first linear-time algorithm is the Hopcroft–Tarjan algorithm[^ht74], but its implementation is quite complex. The de Fraysseix–Ossona de Mendez–Rosenstiehl algorithm (also called the LR planarity algorithm)[^dor06][^df08][^bra09] further improves on the Hopcroft–Tarjan algorithm and is currently one of the best planarity testing algorithms. Python's NetworkX library has an [implementation](https://github.com/networkx/networkx/blob/main/networkx/algorithms/planarity.py) of this algorithm.

Another excellent algorithm is the Boyer–Myrvold algorithm[^bm99][^bm04]. It can test in linear time whether a given graph is planar. Moreover, if the graph is planar, the algorithm will output a planar embedding; otherwise, it will output a Kuratowski subgraph (i.e., a subgraph homeomorphic to $K_5$ or $K_{3,3}$). C++'s Boost library has an [implementation](https://www.boost.org/doc/libs/1_67_0/boost/graph/planar_detail/boyer_myrvold_impl.hpp) of this algorithm.

For more related algorithms, refer to the literature provided at the end.

## Special Planar Graphs

This section introduces several special types of planar graphs.

### Maximal Planar Graphs

For a simple planar graph $G$, if adding edges between any two non-adjacent vertices results in a non-planar graph, then $G$ is called a **maximal planar graph**. The plane embedding of a maximal planar graph is called a **maximal plane graph**.

???+ note "Theorem"
    A maximal planar graph $G$ must be connected. Moreover, when the number of vertices $|V|\ge 3$, graph $G$ has no bridges.

??? note "Proof"
    If planar graph $G$ is not connected, then for any planar embedding, we can choose two vertices from different connected components and connect them inside the external face. The resulting graph is obviously still a plane graph, which shows that graph $G$ is not a maximal planar graph. Therefore, if graph $G$ is a maximal planar graph, it must be connected.
    
    If planar graph $G$ has $|V|\ge 3$ and has a bridge $e=(u,v)$, then after removing edge $e$, graph $G-e$ has exactly two connected components, with $u$ and $v$ belonging to different connected components. Assume the connected component containing $v$ has at least two vertices. Then we can first draw connected component $G_1$ containing $u$ on the plane, and select any face $f$ whose boundary contains $u$ from $G_1$, and draw the other connected component $G_2$ inside face $f$. Since $G_2$ is a simple graph, its external face boundary is certainly not a self-loop, so there exists another vertex $w\neq u,v$. Connect $v$ and $w$ to $u$ respectively, obtaining a plane graph containing $G$ as a subgraph. So graph $G$ is not a maximal planar graph. Therefore, a maximal planar graph with $|V|\ge 3$ must have no bridges.

The structure of maximal plane graphs can be described more precisely.

???+ note "Theorem"
    For a plane graph $G$ with $|V|\ge 3$, it is a maximal plane graph if and only if it is a simple graph and all its faces have degree $3$.

??? note "Proof"
    The sufficiency of the condition is obvious. We only need to prove necessity, i.e., to prove that in a maximal plane graph $G$ with $|V|\ge 3$, all faces have degree $3$. Since $G$ is a connected simple plane graph and $|V|\ge 3$, all faces have degree at least $3$. So if the proposition does not hold, there must exist a face $f$ whose boundary length is at least $4$. Since graph $G$ has no bridges, this boundary can only be a cycle. Let this cycle be $v_1v_2v_3v_4\cdots v_1$. Then, if $v_1$ and $v_3$ are not adjacent, connecting $v_1$ and $v_3$ inside face $f$ would not destroy planarity, contradicting the maximality of $G$. So $v_1$ and $v_3$ are adjacent; similarly, $v_2$ and $v_4$ are adjacent. However, edges $(v_1,v_3)$ and $(v_2,v_4)$ do not appear in face $f$. This means both edges must be outside face $f$. But this is impossible: no matter how we draw them, these two edges must intersect. Therefore, there are no faces with degree greater than $3$ in graph $G$. The original proposition is proved.

???+ note "Corollary"
    For a graph $G$ with $|V|\ge 3$, we always have $|E|=3|V|-6$ and $|F|=2|V|-4$.

Since each face in a maximal plane graph is bounded by three edges, maximal plane graphs are also called **plane triangulations**.

### Outerplanar Graphs

Let $G$ be a planar graph. If $G$ has a planar embedding $\tilde{G}$ such that all vertices of $G$ lie on the boundary of one face of $\tilde{G}$, then $G$ is called an **outerplanar graph**. This embedding is also called an outerplanar embedding or **outerplane graph**. Usually, the face whose boundary passes through all vertices is drawn as the external face.

![](images/planar-outer.svg)

All outerplanar graphs are planar graphs, but not necessarily vice versa. Outerplanar graphs can also be characterized using forbidden graphs.

???+ note "Theorem"
    Graph $G$ is an outerplanar graph if and only if $G$ contains no subgraph homeomorphic to $K_4$ or $K_{2,3}$.

For outerplanar graphs, we can also discuss the concept of maximal outerplanar graphs. For a simple outerplanar graph $G$, if adding edges between any two non-adjacent vertices results in a non-outerplanar graph, then $G$ is called a **maximal outerplanar graph**. The outerplanar embedding of a maximal outerplanar graph is called a **maximal outerplane graph**. A maximal outerplane graph is essentially a triangulation of a polygon in the plane.

???+ note "Theorem"
    For a maximal outerplanar graph $G$ with $|V|\ge 3$, with all vertices on the boundary of the external face, graph $G$ has exactly $|V|-2$ internal faces.

??? note "Proof"
    Apply mathematical induction on $|V|$. The base case is $|V|=3$. At this time, graph $G$ is a triangle with 3 vertices, having exactly 1 internal face, and the proposition holds. Assume the proposition holds for $|V| = k$. Now we prove that when $|V| = k+1$, the proposition still holds.
    
    First, graph $G$ must have a degree-2 vertex. Otherwise, except for adjacent vertices on the boundary of the external face, all vertices need to be connected to a third vertex. Let's number the vertices on the boundary of the external face in order, and for each $i = 1,2,\cdots,k+1$, define $f(i)$ as the smallest numbered vertex connected to vertex $i$ that is not adjacent to $i$. Consider possible values of $f(i)$. First, $1 < f(1)$. Since vertex $1$ is already connected to $f(1)$, the line from vertex $2$ to $f(2)$ cannot cross edge $(1,f(1))$, so we must have $1 < 2 < f(2) < f(1)$. Similarly, $2 < 3 < f(3) < f(2)$. Since there are only finitely many vertices, this gradually shrinking process must terminate after finitely many steps. Let $i^*$ be the largest index satisfying $1 < \cdots < i-1 < i < f(i) < f(i-1) < \cdots < f(1)$. Then, since vertices $i^*$ and $f(i^*)$ are not adjacent, we must have $i^* < i^* + 1 < f(i^*)$. Repeating the previous argument, we should still have $i^* < i^*+1 < f(i^*+1) < f(i^*)$, which contradicts the maximality of $i^*$. This contradiction shows that graph $G$ must have a degree-2 vertex.
    
    Let $v$ be a degree-2 vertex. Removing this vertex from graph $G$ gives an outerplane graph $G-v$ with $k$ vertices. It must be a maximal outerplane graph; otherwise, a valid way to add edges to it would also apply to graph $G$. By the induction hypothesis, $G-v$ has exactly $k-2$ internal faces. When removing vertex $v$, exactly one internal face of $G$ is reduced. So the number of internal faces of $G$ is $k-1$. The proposition is proved.

???+ note "Theorem"
    For an outerplanar graph $G$ with $|V|\ge 3$, with all vertices on the boundary of the external face, graph $G$ is a maximal outerplane graph if and only if the boundary of the external face is a cycle of length $|V|$, and all internal face boundaries are cycles of length $3$.

??? note "Proof"
    Sufficiency is obvious. In fact, consider connecting two non-adjacent vertices on the boundary of the external face. If the connection occurs in the external face, then all vertices cannot appear on the boundary of a single face; otherwise, their connecting line must intersect the boundary of an internal face.
    
    Next, we prove necessity. Assume the boundary of the external face of graph $G$ is not a cycle. Then it repeats through a vertex multiple times, i.e., there exists $i\neq j$ and $i-j\neq\pm 1\pmod{n}$ such that $v_i=v_j$. Let $1 < i < j < n$. At this time, edges incident to $v_{i-1}$ can only appear in the bounded region enclosed by the cycle $v_jv_{j+1}\cdots v_nv_1\cdots v_{i-1}v_i$, and edges incident to $v_{i+1}$ can only appear in the bounded region enclosed by the cycle $v_iv_{i+1}\cdots v_{j-1}v_{j}$. So $v_{i-1}$ and $v_{i+1}$ cannot be adjacent. We can add an edge $e$ connecting $v_{i-1}$ and $v_{i+1}$ inside the external face, obtaining graph $G+e$. This is obviously also a plane graph, and the external face boundary contains all vertices. This contradicts the maximal outerplanarity of $G$. Therefore, the external face of $G$ must be a cycle of length $|V|$. The reason all internal face boundaries of $G$ are cycles of length $3$ is the same as for maximal plane graphs and will not be repeated here.

???+ note "Corollary"
    For a maximal outerplanar graph $G$ with $|V|\ge 3$:
    
    1.  $|E|=2|V|-3$.
    2.  There are at least 3 vertices in $G$ with degree at most 3, and at least 2 vertices with degree 2.
    3.  The vertex connectivity of $G$ is $2$.

## Problems

-   [Luogu P3209 [HNOI2010] Planar Graph Judgment](https://www.luogu.com.cn/problem/P3209)
-   [Luogu P3249 [HNOI2016] Mining Area](https://www.luogu.com.cn/problem/P3249)
-   [Luogu P4001 [ICPC-Beijing 2006] Wolf Catching Rabbit](https://www.luogu.com.cn/problem/P4001)
-   [Luogu P4073 [WC2013] Planar Graph](https://www.luogu.com.cn/problem/P4073)
-   [Luogu P7295 [USACO21JAN] Paint by Letters P](https://www.luogu.com.cn/problem/P7295)

## References and Notes

-   [Planar graph - Wikipedia](https://en.wikipedia.org/wiki/Planar_graph)
-   [Planarity testing - Wikipedia](https://en.wikipedia.org/wiki/Planarity_testing)
-   Bondy, John Adrian, and Uppaluri Siva Ramachandra Murty. Graph theory with applications. Vol. 290. London: Macmillan, 1976.
-   Diestel, Reinhard. Graph theory. Vol. 173. Springer Nature, 2025.
-   Patrignani, Maurizio. "Planarity Testing and Embedding." (2013): 1-42.

[^face-2]: But this is not the only possibility. Two nested self-loops also form a degree-2 face. Also, having a degree-2 face does not necessarily mean the graph is not simple; for example, in a graph with only one edge, the only face (the external face) is also degree-2.

[^ht74]: Hopcroft, John, and Robert Tarjan. "Efficient planarity testing." Journal of the ACM (JACM) 21, no. 4 (1974): 549-568.

[^dor06]: De Fraysseix, Hubert, Patrice Ossona De Mendez, and Pierre Rosenstiehl. "Trémaux trees and planarity." International Journal of Foundations of Computer Science 17, no. 05 (2006): 1017-1029.

[^df08]: De Fraysseix, Hubert. "Trémaux trees and planarity." Electronic Notes in Discrete Mathematics 31 (2008): 169-180.

[^bra09]: Brandes, Ulrik. "The left-right planarity test." Manuscript submitted for publication 3 (2009).

[^bm99]: Boyer, John M., and Wendy J. Myrvold. "Stop Minding Your p's and q's: A Simplified O (n) Planar Embedding Algorithm." In SODA, vol. 99, pp. 140-146. 1999.

[^bm04]: Boyer, John M., and Wendy J. Myrvold. "Simplified o (n) planarity by edge addition." Graph Algorithms and Applications 5 (2006): 241.