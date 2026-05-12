author: accelsao, thallium, Chrogeek, Enter-tainer, ksyx, StudyingFather, H-J-Granger, countercurrent-time, william-song-shy, 5ab-juruo, XiaoQuQuSD, hhc0001, GCVillager

Prerequisites: [Bipartite Graph](../bi-graph.md), [Graph Matching](./graph-match.md)

## Introduction

This article discusses the maximum matching problem for bipartite graph $G=(X,Y,E)$.

A typical example of bipartite matching in real life is male-female pairing. Suppose there are several boys ($X$) and girls ($Y$), each person can be paired only once, and the possible pairings are given by a list ($E$). The task of the bipartite maximum matching algorithm is to find the maximum number of pairs under these constraints, so that as many people as possible are successfully paired.

???+ info "Note"
    This article assumes that a partition (coloring) of the bipartite graph vertex set $V$ is known: $V = X \cup Y$. If the partition of the bipartite graph vertex set $V$ is not known in advance, such a partition can be found in $O(|V| + |E|)$ time using the [bipartite graph coloring algorithm](../bi-graph.md#determination).

## Kuhn's Algorithm

Kuhn's Algorithm is a direct application of [Berge's Lemma](./graph-match.md#berge-lemma). It is also part of the [Hungarian Algorithm](./bigraph-weight-match.md#hungarian-algorithmkuhnmunkres-algorithm).

### Process

To find the maximum matching, the algorithm iterates through all vertices, finds an augmenting path starting from each vertex, and performs augmentation. Since the length of an augmenting path is always odd, in a bipartite graph, its endpoints must lie in the two different parts. This shows that we only need to consider augmenting paths starting from the left part.

To find augmenting paths, we can orient the bipartite graph according to the current matching $M$. In an augmenting path (or any alternating path) starting from an unmatched vertex in the left part, we can only traverse from a left vertex to a right vertex via a non-matching edge, and from a right vertex to a left vertex via a matching edge. Therefore, we can orient all non-matching edges toward the right vertices and all matching edges toward the left vertices. The problem of finding augmenting paths becomes finding a simple path from some unmatched left vertex to some unmatched vertex in the directed graph. This can be easily solved by [DFS](../dfs.md) or [BFS](../bfs.md) in $O(|E|)$ time.

![](images/bigraph-match-1.svg)

(In the figure, dark vertices are matched vertices, light vertices are unmatched vertices, red edges are matching edges, black edges are non-matching edges, and arrows show the orientation corresponding to the current matching. As can be seen from the figure, path $1 \rightarrow 8 \rightarrow 3 \rightarrow 11 \rightarrow 6 \rightarrow 12$ is an augmenting path with respect to the current matching.)

At the beginning of the algorithm, all edges are oriented toward the right vertices. After each augmenting path is found, all traversed edges are reversed to indicate their matching status has changed. At the end of the algorithm, all edges oriented toward the left vertices are matching edges.

Since at most $O(|V|)$ left vertices need to be enumerated [once each](./graph-match.md#berge-lemma), the total time complexity of the algorithm is $O(|V||E|)$.

### Optimizations

There are some simple techniques to optimize the constant factor of Kuhn's Algorithm:

1.  Kuhn's Algorithm is based on Berge's Lemma, which does not require the left and right parts to be given in advance. Therefore, Kuhn's Algorithm can still work correctly even when the two parts are not clearly divided, as long as the graph itself is bipartite. However, coloring the bipartite graph first to determine the left and right parts is often more efficient.
2.  Since the time complexity described above is actually $O(|X||E|)$, we can choose the smaller of the two parts as the left part $X$.
3.  When finding augmenting paths, the marking used to avoid duplicate searches does not need to be cleared for each DFS. Instead, we can try to find augmenting paths for all unmatched left vertices before clearing the marking. In one round of such search, all edges are visited at most once; however, in one round, multiple augmenting paths may be found. Therefore, the total number of rounds $k$ will not exceed $|M| + 1$, where $M$ is the maximum matching. Accordingly, the overall complexity is reduced to $O(k|E|)$.
4.  When finding augmenting paths, prioritize unmatched right vertices, as this means shorter augmenting paths.
5.  Since Berge's Lemma does not require the initial matching to be empty, at the beginning of Kuhn's Algorithm, we can randomly select some disjoint edges as the initial matching to reduce the number of subsequent searches. If optimization 3 has been applied, this optimization can be ignored.

Although the worst-case complexity is still $O(|V||E|)$, a fully optimized Kuhn's Algorithm is quite efficient. However, to avoid some specific cases reaching the worst-case complexity, the order of edges or vertices needs to be randomly shuffled before matching.

### Reference Implementation

When implementing, we don't actually need to maintain orientation; we only need to store for each vertex the vertex it is matched with.

??? example "Template Problem [Library Checker - Matching on Bipartite Graph](https://judge.yosupo.jp/problem/bipartitematching)"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/bigraph-match/bigraph-match_1.cpp"
    ```

## Hopcroft–Karp Algorithm

The Hopcroft–Karp Algorithm further optimizes the process of finding augmenting paths in Kuhn's Algorithm, reducing the total number of rounds to $O(|V|^{1/2})$, thereby achieving a time complexity of $O(|V|^{1/2}|E|)$. This algorithm is actually a special case of the [Dinic Algorithm](../flow/max-flow.md#dinic-algorithm).

### Process

The algorithm still searches for augmenting paths, but to complete matching in fewer rounds, it adopts the following strategy in each round:

1.  Orient matching edges toward left vertices and non-matching edges toward right vertices.
2.  Perform BFS from all unmatched left vertices in the directed graph, recording the layer number $d(v)$ of each visited vertex, until an unmatched right vertex is reached in some layer. If the BFS ends without finding an unmatched right vertex, the current matching is already maximum.
3.  Starting from each unmatched left vertex, perform DFS to find augmenting paths and perform augmentation. During DFS, expand along edges that satisfy the layer number being consecutive and strictly increasing (i.e., $d(v') = d(v) + 1$), and only visit vertices not yet visited in the current DFS round. In particular, DFS will not visit vertices not yet visited in the previous BFS step.

In network flow terminology, step 2 constructs a level graph, and step 3 finds a blocking flow on the level graph. The level graph refers to a graph where each edge must go from one layer to the next. In the current context, a blocking flow refers to a maximal set of augmenting paths that are pairwise vertex-disjoint. The set of augmenting paths obtained in step 3 is necessarily maximal: suppose not, there exists a new augmenting path; then when enumerating its starting point, such a path should have been found.

The key improvement of the Hopcroft–Karp Algorithm over the previous Kuhn's Algorithm is adding the level graph construction step before finding the blocking flow. Performing DFS based on the level graph effectively limits the algorithm to always reach vertices along the shortest paths. The benefit of this is that between different rounds of the algorithm, the lengths of augmenting paths strictly increase. Moreover, it can be proven that until the maximum matching is found, the augmenting path length increases at most $3|M|^{1/2}$ times, where $|M|$ is the size of the maximum matching. Therefore, the total number of augmentation rounds is controlled to $O(|M|^{1/2})$, giving a time complexity of $O(|M|^{1/2}|E|)$. Since $2|M| \le |V|$, the time complexity can also be written as the looser bound $O(|V|^{1/2}|E|)$.

??? note "Proof"
    First, we prove that between different rounds of the algorithm, the lengths of augmenting paths strictly increase.
    
    Suppose in the current round's BFS, vertices are extended forward by $\ell$ layers. Since all unmatched right vertices found in BFS are in the same layer, all augmenting paths found in this round's DFS have length $\ell$. We need to prove that after augmenting along the set of augmenting paths $\{P_i\}$ found in this round, there will be no augmenting path of length no more than $\ell$ in the reoriented directed graph.
    
    Actually, if $P$ is the shortest augmenting path with respect to $M$, and $P'$ is an augmenting path with respect to $M \oplus P$, we have $|P'| \ge |P| + 2|P \cap P'|$. This is because $N = (M \oplus P) \oplus P'$ augments $M$ twice. Similar to the [proof of Berge's Lemma](./graph-match.md#berge-lemma), we can show that the symmetric difference $M \oplus N = P \oplus P'$ contains at least two vertex-disjoint augmenting paths $P_1$ and $P_2$ with respect to $M$. Due to the minimality of $P$,
    
    $$
    2|P| \le |P_1| + |P_2| \le |P \oplus P'| = |P| + |P'| - 2|P \cap P'|.
    $$
    
    This shows $|P'| \ge |P| + 2|P \cap P'|$. Therefore, if after adding augmenting paths $\{P_i\}$, a new augmenting path $P'$ is still the same length, it must be pairwise disjoint with them, which contradicts the maximality of $\{P_i\}$. This contradiction shows that after augmenting the blocking flow, new augmenting paths must be strictly longer.
    
    Finally, we prove that the augmenting path length increases at most $3|M|^{1/2}$ times.
    
    Let $p = \lfloor |M|^{1/2} \rfloor$. After the first $p$ rounds, the remaining augmenting paths have length at least $|M|^{1/2}$. Let the current matching be $M_p$. Similar to the previous case, we can show that in the graph $(V, M \oplus M_p)$, there are $|M| - |M_p|$ vertex-disjoint augmenting paths with respect to $M_p$. Each augmenting path uses at least $|M|^{1/2}/2$ matching edges from $M$. Therefore, the total number of such augmenting paths does not exceed $2|M|^{1/2}$, i.e., $|M| - |M_p| \le 2|M|^{1/2}$. This shows that starting from $M_p$, at most $2|M|^{1/2}$ more augmentations can be performed, which also means the algorithm performs at most $2|M|^{1/2}$ more augmentation rounds. Therefore, the augmenting path length increases at most $3|M|^{1/2}$ times in total.

This is only an estimate of the worst-case complexity of the Hopcroft–Karp Algorithm. In practice, the time complexity of Hopcroft–Karp Algorithm in random graphs is very likely $O(|E| \log |V|)$[^hk-comp-ref].

### Optimization

When constructing the level graph, as in the general Dinic Algorithm, the Hopcroft–Karp Algorithm terminates when reaching an unmatched right vertex. However, for the bipartite matching problem specifically, this is unnecessary. Furthermore, because the BFS terminates too early, it limits the scope of subsequent DFS, which reduces the number of augmenting paths found in each round and thus slows down the overall matching efficiency. On some graphs, its efficiency is even worse than the optimized Kuhn's Algorithm. A simple improvement is to not terminate BFS early, but to construct the level graph for all reachable vertices.

??? note "Correctness Proof"
    In the optimized algorithm, the lengths of augmenting paths in the blocking flow are no longer the same, so the previous proof of complexity no longer holds. However, it can be shown that by constructing an auxiliary graph for each round of the algorithm, the conclusion that the shortest augmenting path length strictly increases can still be established, thereby ensuring the worst-case complexity is still correct.
    
    Let the bipartite graph be $G = (X, Y, E)$, and let the current matching be $M$. Let $W \subseteq Y$ be the set of unmatched right vertices reachable by BFS, and let the shortest augmenting path length to $y \in W$ be $d(y)$. Let $d_\text{max} = \max_{y \in W} d(y)$. Then for each $y \in W$, we can construct a new chain starting from $y$ with length $d_\text{max} - d(y)$, and mark the new vertices as alternating left and right vertices, and mark the new edges as matching and non-matching edges. Let the resulting graph be $G' = (X', Y', E')$, the matching be $M'$, and the shortest augmenting path length be $d_\text{max}$. Then there is a bijection between the augmenting paths found along the level graph in graph $G$ with respect to $M$ — that is, the shortest augmenting paths to the corresponding vertices — and the globally shortest augmenting paths in graph $G'$ with respect to $M'$. Therefore, finding the blocking flow in the level graph of $G$ and performing augmentation is equivalent to finding the blocking flow in the level graph of $G'$ and performing augmentation. According to the previous proof, after augmentation, there will be no augmenting path of length $d_\text{max}$ in $G'$. Therefore, there will also be no augmenting path of length $d_\text{min} = \min_{y \in W} d(y)$ in $G$: because such an augmenting path, when extended along the new alternating path, must correspond to an augmenting path of length $d_\text{max}$ in $G'$. This again establishes the conclusion that the shortest augmenting path length strictly increases between different rounds of the algorithm. Therefore, the overall complexity is still $O(|M|^{1/2}|E|)$.

### Reference Implementation

??? example "Template Problem [Library Checker - Matching on Bipartite Graph](https://judge.yosupo.jp/problem/bipartitematching)"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/bigraph-match/bigraph-match_2.cpp"
    ```

## Reduction to Maximum Flow Problem

The bipartite maximum matching problem can be reduced to the maximum flow problem.

![](images/bigraph-match-2.svg)

As shown in the figure, add two vertices as the source and sink respectively. From the source, connect an edge to each left vertex; from each right vertex, connect an edge to the sink; and for each undirected edge in the bipartite graph, add a directed edge from the left vertex to the right vertex. All edges have capacity 1. Every network flow in this directed graph corresponds one-to-one to a matching in the bipartite graph, and the capacity of the flow equals the size of the corresponding matching. Therefore, solving the bipartite maximum matching is equivalent to solving the maximum flow in the corresponding directed graph.

Any algorithm that can solve the maximum flow problem can be used to solve the bipartite maximum matching problem. It is easy to see that Kuhn's Algorithm and Hopcroft–Karp Algorithm are both special cases of their corresponding algorithms in the maximum flow problem. Similarly, [preflow-push algorithms](../flow/max-flow.md#push-relabel-预流推进算法) can also solve the bipartite maximum matching problem. However, it should be noted that any maximum flow algorithm, when applied to the bipartite maximum matching problem, needs to be optimized accordingly to avoid excessive constants.

### Linear Programming Form

Like other maximum flow problems, the maximum matching problem for bipartite graph $G = (V, E)$ can be written as a linear programming problem. If we use $x_e \in \{0, 1\}$ to denote whether edge $e$ belongs to the matching, we obtain the following linear programming problem:

$$
\begin{aligned}
\max_{\{x_e\}}\;& \sum_{e\in E}x_e \\
\text{subject to } & \sum_{e\sim v} x_{e} \le 1,~\forall v\in V,\\
& x_e\ge 0,~\forall e\in E.
\end{aligned}
$$

Where $e \sim v$ denotes the incidence relation, i.e., vertex $v$ is one of the endpoints of edge $e$. Except for the non-negativity constraint, the constraint also requires that at each vertex $v \in V$, at most one edge is incident. This is precisely the definition of a matching. Therefore, all matchings correspond to some integer points in the feasible region of this linear program.

The converse is not true. In feasible solutions, $x_e$ may be fractional, which does not represent any actual matching. Nevertheless, for bipartite graph $G$, all extreme point solutions of this linear program are integer points. This means the optimal value of the objective function is always attained at an integer point, without considering non-integer cases. This property does not hold for general graphs, so the above linear program is not equivalent to the maximum matching problem in general graphs.

The dual problem of this linear programming problem can be written as:

$$
\begin{aligned}
\min_{\{y_v\}}\;& \sum_{v\in V}y_v \\
\text{subject to } & y_u+y_v \ge 1,~\forall (u,v)\in E,\\
& y_v\ge 0,~\forall v\in V.
\end{aligned}
$$

As we will see, this is precisely the minimum vertex cover problem in bipartite graphs.

## Dulmage–Mendelsohn Decomposition

Using the maximum matching of a bipartite graph, vertices can be divided into several disjoint subsets, which fully characterizes the distribution and structural characteristics of all maximum matchings in the bipartite graph. This is the Dulmage–Mendelsohn Decomposition. In competitive programming, this decomposition can be used to identify critical vertices and edges in the maximum matching, and to determine the uniqueness of the maximum matching or to solve bipartite graph games, among other problems.

### Construction Method

Let $M$ be a maximum matching of bipartite graph $G = (X, Y, E)$.

![](images/bigraph-match-4.svg)

As shown in the figure, for all vertices $V = X \cup Y$, we can define the following three subsets:

-   Even-reachable vertices $\mathcal E$: the set of all vertices that can be reached from an unmatched vertex via an alternating path of even length.
-   Odd-reachable vertices $\mathcal O$: the set of all vertices that can be reached from an unmatched vertex via an alternating path of odd length.
-   Unreachable vertices $\mathcal U$: the set of all vertices that cannot be reached from an unmatched vertex via an alternating path.

It can be proven that the three vertex sets $\mathcal E, \mathcal O, \mathcal U$ obtained have the following properties:

???+ note "Properties"
    1.  The sets $\mathcal E, \mathcal O, \mathcal U$ form a partition of the vertex set, and this partition is independent of the choice of maximum matching $M$.
    2.  Every maximum matching of graph $G$ contains a perfect matching between the vertices of $\mathcal U$, and matches each vertex in $\mathcal O$ to a vertex in $\mathcal E$. That is, the size of the maximum matching of graph $G$ equals $|\mathcal O| + |\mathcal U|/2$.
    3.  Graph $G$ does not contain edges connecting vertices in $\mathcal E$ to vertices in $\mathcal E \cup \mathcal U$.

??? note "Proof"
    1.  By definition, $\mathcal U$ is disjoint from $\mathcal E \cup \mathcal O$. We only need to prove that $\mathcal E$ and $\mathcal O$ are disjoint. Suppose otherwise, for vertex $v \in \mathcal E \cap \mathcal O$, there exists an alternating path of even length from an unmatched vertex $a$ to $v$, as well as an alternating path of odd length from an unmatched vertex $b$ to $v$. Since graph $G$ is bipartite, $a \neq b$, and when the two paths reach $v$, the edges are respectively matching and non-matching edges. Therefore, connecting the two paths gives an alternating path from $a$ via $v$ to $b$. This is an augmenting path. This contradicts that $M$ is a maximum matching. Therefore, $\mathcal E \cap \mathcal O = \varnothing$.
    
        Let $M'$ be a maximum matching different from $M$. Repeating the [proof of Berge's Lemma](./graph-match.md#berge-lemma) shows that $M' \oplus M$ consists only of paths of even length and even cycles. Starting from maximum matching $M$, we can flip the edges in each connected block (paths and cycles) one by one (swapping matching and non-matching edges) to obtain maximum matching $M'$. When flipping even cycles, unmatched vertices remain unmatched, and the parity of alternating path lengths starting from them does not change. When flipping even-length paths, the matching status of the two endpoints of the path is swapped, but the parity of the path lengths from them to any vertex in the path is also consistent. Therefore, during the flipping process, the sets $\mathcal E, \mathcal O, \mathcal U$ remain unchanged. This shows that this decomposition is independent of the choice of maximum matching $M$.
    2.  If a matching edge appears in some alternating path starting from an unmatched vertex, then the parity of the distances from its two endpoints to that unmatched vertex must be different, so they respectively belong to sets $\mathcal E$ and $\mathcal O$. Otherwise, both its endpoints must be in $\mathcal U$. This shows that matching edges in the maximum matching must be either $\mathcal E \mathcal O$ edges or $\mathcal U \mathcal U$ edges. Conversely, unmatched vertices can reach themselves via an alternating path of length zero, so they only appear in set $\mathcal E$. This shows that sets $\mathcal O$ and $\mathcal U$ both contain matched vertices. Simple counting shows that the size of the maximum matching is $|\mathcal O| + |\mathcal U|/2$.
    3.  By definition, any vertex $a \in \mathcal E$ can be reached from an unmatched vertex $v$ via an alternating path of even length. That is, vertices in $\mathcal E$ are either unmatched vertices, or the alternating path $P$ to that vertex ends with a matching edge. If there exists an edge in graph $G$ connecting $a$ to some vertex $b \in \mathcal E \cup \mathcal U$, then according to the discussion in the previous paragraph, this edge must be a non-matching edge, and we can extend the alternating path $P$ along it. This shows that vertex $b$ also belongs to set $\mathcal O$, which contradicts the first property. Therefore, graph $G$ does not contain edges connecting vertices in $\mathcal E$ to vertices in $\mathcal E \cup \mathcal U$.

The resulting decomposition of the vertex set $V = \mathcal E \cup \mathcal O \cup \mathcal U$ is called the **Dulmage–Mendelsohn Decomposition**. After obtaining the maximum matching using the algorithm described above, the Dulmage–Mendelsohn Decomposition can be found in $O(|V| + |E|)$ time via BFS.

### Maximum Matching Critical Vertices

If a vertex $v$ is a matched vertex in every maximum matching of the bipartite graph $G$, then it is called a maximum matching critical vertex. The following conclusion shows that a vertex is critical if and only if in a maximum matching, there is no alternating path of even length from an unmatched vertex to that vertex.

???+ note "Theorem"
    Let the Dulmage–Mendelsohn decomposition of bipartite graph $G = (X, Y, E)$ be $V = \mathcal E \cup \mathcal O \cup \mathcal U$. Then vertex $v \in V$ is critical if and only if $v \in \mathcal O \cup \mathcal U$.

??? note "Proof"
    According to the properties of the Dulmage–Mendelsohn decomposition, in any maximum matching of graph $G$, vertices in $\mathcal O$ and $\mathcal U$ must be matched vertices. Therefore, vertices in $\mathcal O \cup \mathcal U$ are necessarily critical vertices. Then we need to show that set $\mathcal E$ definitely contains no critical vertices. If in maximum matching $M$, vertex $a \in \mathcal E$ is critical, then there exists an alternating path $P$ of even length connecting vertex $a$ to some unmatched vertex $b \in \mathcal E$. Flipping all edges on this path, in the resulting maximum matching $M \oplus P$, vertex $a$ becomes unmatched. Therefore, set $\mathcal E$ contains no critical vertices.

Therefore, to find maximum matching critical vertices, we only need to find the Dulmage–Mendelsohn decomposition.

### Maximum Matching Critical Edges

Similarly, if an edge $e$ is a matching edge in every maximum matching of the bipartite graph $G$, then it is called a maximum matching critical edge. The maximum matching of a bipartite graph is unique if and only if all matching edges in a maximum matching are critical edges.

???+ note "Theorem"
    Let the Dulmage–Mendelsohn decomposition of bipartite graph $G = (X, Y, E)$ be $V = \mathcal E \cup \mathcal O \cup \mathcal U$, and let $M$ be one of its maximum matchings. Then edge $e \in E$ is a critical edge if and only if both endpoints of $e$ are in $\mathcal U$, $e$ is a matching edge in $M$, and there is no alternating cycle containing edge $e$ with respect to $M$.

??? note "Proof"
    The endpoints of a critical edge must be critical vertices. According to the properties of the Dulmage–Mendelsohn decomposition, edges in the maximum matching can only be $\mathcal E \mathcal O$ edges or $\mathcal U \mathcal U$ edges. However, since there are no critical vertices in $\mathcal E$, critical edges can only be $\mathcal U \mathcal U$ edges. Of course, critical edges must also be matching edges in $M$. Let $e \in M$ be a $\mathcal U \mathcal U$ edge. It is not a critical edge if and only if there exists another maximum matching $M' \neq M$ such that $e \in M \oplus M'$. Repeating the [proof of Berge's Lemma](./graph-match.md#berge-lemma) shows that $M' \oplus M$ consists only of paths of even length and even cycles. One of the endpoints of these paths is an unmatched vertex with respect to $M$, so vertices in the paths are not in $\mathcal U$, which contradicts the choice of edge $e$. Therefore, edge $e$ can only appear in even cycles. Therefore, a $\mathcal U \mathcal U$ edge $e \in M$ is not a critical edge if and only if there exists an alternating cycle containing edge $e$ with respect to $M$. This is what we needed to prove.

Therefore, to find maximum matching critical edges, proceed as follows:

1.  Find the maximum matching $M$ of graph $G$.
2.  Orient the edges of graph $G$ according to $M$ to get the directed graph $G_M$.
3.  Perform BFS to find the set $\mathcal U$ in the Dulmage–Mendelsohn decomposition, i.e., the set of vertices that cannot be reached from unmatched vertices via alternating paths.
4.  Use [Tarjan Algorithm](../scc.md#tarjan-algorithm) to find all strongly connected components of the directed graph $G_M$.
5.  Iterate through edges in matching $M$. If both of its endpoints are in $\mathcal U$ but not in the same strongly connected component, it is a critical edge.

After obtaining the maximum matching, the time complexity of the subsequent steps is $O(|V| + |E|)$.

## Related Problems

Using bipartite maximum matching algorithms, other combinatorial optimization problems can be solved.

### Bipartite Minimum Vertex Cover

The minimum vertex cover problem is to select the minimum number of vertices in an undirected graph such that every edge has at least one endpoint selected.

The minimum vertex cover problem is NP-hard for general graphs. However, for bipartite graphs, Kőnig's Theorem shows that it can be reduced to the maximum matching problem, thus allowing efficient solution. The proof of the theorem also gives the construction of the minimum vertex cover.

???+ note "Kőnig's Theorem"
    In a bipartite graph, the number of vertices in the minimum vertex cover equals the number of edges in the maximum matching.

??? note "Proof"
    Let $M$ be a maximum matching of bipartite graph $G = (X, Y, E)$. Let $Z$ be the set of vertices that can be reached from an unmatched left vertex $U$ via some alternating path in graph $G$. Then the vertex set $C = (X \setminus Z) \cup (Y \cap Z)$ is the minimum vertex cover.
    
    ![](images/bigraph-match-3.svg)
    
    First, set $C$ is a vertex cover. Suppose not, there exists an edge $(u, v) \in E$ such that $u \in X \cap Z$ and $v \in Y \setminus Z$. Let $P_u$ be an alternating path reaching $u$. If edge $(u, v)$ is a matching edge, then the last edge in path $P_u$ is $(v, u)$, which contradicts $v \notin Z$. If edge $(u, v)$ is not a matching edge, then we can extend $P_u$ along edge $(u, v)$ to get an alternating path reaching $v$, also contradicting $v \notin Z$. These contradictions show that all edges contain at least one endpoint in $C$, so $C$ is a vertex cover.
    
    Then we need to show that $C$ is a minimum vertex cover. To cover all edges of the maximum matching $M$, any vertex cover requires at least $|M|$ vertices. Therefore, if we can prove $|C| = |M|$, it must be a minimum vertex cover. This is equivalent to proving that apart from containing one endpoint of each matching edge, $C$ contains no other vertices; that is, $C$ does not contain unmatched vertices. Suppose not, there exists an unmatched vertex $v \in C$. If $v \in X$, then $v \in U \subseteq Z$, which contradicts the construction of $C$. If $v \in Y$, then an alternating path reaching $v$ is an augmenting path with respect to $M$. By Berge's Lemma, this contradicts that $M$ is a maximum matching. These contradictions show that no such unmatched vertex exists, and thus $C$ is a minimum vertex cover.

From the perspective of network flows, the minimum vertex cover problem is the minimum cut problem: selecting a left vertex corresponds to cutting its edge to the source; selecting a right vertex corresponds to cutting its edge to the sink. From the perspective of linear programming, the minimum vertex cover problem is the dual problem of the maximum matching problem. Therefore, Kőnig's Theorem can be seen as a special case of the [Max-Flow Min-Cut Theorem](../flow/max-flow.md#最大流最小割定理), or more generally, the strong duality theorem of linear programming.

### Maximum Independent Set in Bipartite Graphs

The maximum independent set problem is to select the maximum number of vertices in an undirected graph such that no two are adjacent.

For general graphs, the following theorem holds:

???+ note "Theorem"
    In graph $G = (V, E)$, a vertex set $C \subseteq V$ is a vertex cover if and only if its complement $V \setminus C$ is an independent set.

??? note "Proof"
    A vertex set $C$ is a vertex cover if and only if for any edge $e \in E$, at least one of its two endpoints appears in set $C$. This is equivalent to saying that for any edge in $E$, both endpoints do not appear in set $V \setminus C$, which is equivalent to $V \setminus C$ being an independent set.

???+ note "Corollary"
    In graph $G = (V, E)$, the size of the minimum vertex cover plus the size of the maximum independent set equals the number of vertices.

Therefore, like the minimum vertex cover problem, the maximum independent set problem is NP-hard for general graphs, but for bipartite graphs it can be reduced to the maximum matching problem, thus allowing efficient solution.

### Minimum Path Cover in DAG

The minimum path cover problem is to select the minimum number of simple paths in a directed graph such that every vertex appears in exactly one path.

The minimum path cover problem on general directed graphs is NP-hard. However, for directed acyclic graphs, the problem can be reduced to the bipartite maximum matching problem. For a directed acyclic graph $G = (V, E)$, we can construct a bipartite graph $G' = (V^\text{in}, V^\text{out}, E')$ as follows:

-   For each vertex $v \in V$, create an input vertex $v^\text{in}$ and an output vertex $v^\text{out}$ respectively. Let the sets of all input vertices and output vertices be $V^\text{in}$ and $V^\text{out}$ respectively. They become the left and right parts of the new graph respectively.
-   For each directed edge $(u, v) \in E$, create an undirected edge $(u^\text{out}, v^\text{in})$. The set of all undirected edges is $E'$.

For this, we have the following theorem:

???+ note "Theorem"
    In a directed acyclic graph $G = (V, E)$, the minimum path cover plus the size of the maximum matching in the corresponding bipartite graph $G' = (V^\text{in}, V^\text{out}, E')$ equals the number of vertices.

??? note "Proof"
    Each matching $M'$ in bipartite graph $G'$ corresponds to a subgraph $F$ of graph $G$, and in subgraph $F$, each vertex has indegree and outdegree at most one. That is, subgraph $F$ is actually a collection of disjoint paths or cycles in directed graph $G$. However, since we have assumed that $G$ contains no cycles, $F$ only contains disjoint paths. Conversely, for each such subgraph $F$, a corresponding matching can be constructed. Since the size of matching $M$ is the difference between the number of vertices and the number of paths in $F$, the minimum path cover problem in graph $G$ corresponds to the maximum matching problem in graph $G'$.

The proof is constructive, so it is easy to construct the corresponding minimum path cover from the obtained maximum matching. Furthermore, this construction shows that for general directed graphs, this reduction no longer holds, precisely because a matching in a bipartite graph may correspond to cycles in a directed graph.

In particular, for a set $X$ and a partial order relation $P$ on it, we can construct a directed acyclic graph $G = (X, P)$. In this case, according to [Dilworth's Theorem](../../math/order-theory.md#dilworth-定理与-mirsky-定理), the size of the minimum path cover of graph $G$ equals the length of its longest antichain, which is the width of the partial order set $(X, P)$. Therefore, this section actually provides an efficient method to compute the width of any partial order set.

## Examples

The difficulty in applying bipartite matching is in constructing the graph. This section demonstrates graph construction techniques through some examples.

???+ example "[Luogu P1129 Matrix Game](https://www.luogu.com.cn/problem/P1129)"
    There is a 01 matrix. Each time you can swap two rows or two columns. Ask whether it is possible to swap so that the main diagonal (top-left to bottom-right) is all 1s.

??? note "Solution"
    Notice that if there exist $n$ 1s such that these 1s are not in the same row or the same column, then there must be a solution; otherwise, there must be no solution. The problem reduces to whether these $n$ 1s can be found.
    
    Considering a 1, the final solution selecting this 1 means that its row and column are occupied. Then we can construct a bipartite graph with $n$ left vertices and $n$ right vertices. For each element that is 1, we create an edge connecting the left vertex of its row to the right vertex of its column. Then we can perform bipartite graph matching.

??? note "Code"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/bigraph-match/bigraph-match_3.cpp"
    ```

???+ example "[Gym 104427B Lawyers](https://codeforces.com/gym/104427/problem/B)"
    There are $n$ lawyers, all accused of fraud. They need to defend each other to ensure that every lawyer is released. These $n$ lawyers have $m$ trust relationships. A trust relationship $(a, b)$ means $a$ can defend $b$. Any lawyer who receives a defense will be released without guilt, with one exception: if $a$ and $b$ defend each other, they will both be found guilty.
    
    Ask whether it is possible to have every lawyer released.

??? note "Solution"
    For each **unordered pair** $(a, b)$, if $a$ can defend $b$, connect this unordered pair to $b$'s edge, and vice versa.
    
    Only keep $(a, b)$ where there is an edge. The problem becomes a bipartite maximum matching with $m$ left vertices and $n$ right vertices.

??? note "Code"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/bigraph-match/bigraph-match_4.cpp"
    ```

???+ example "[Codeforces 1404E Bricks](https://codeforces.com/problemset/problem/1404/E)"
    Use some $1 \times x$ bricks to precisely cover an $n \times m$ grid. Bricks can be rotated. Some cells cannot be covered.

??? note "Solution"
    Consider how the final solution is composed:
    
    First, cover all coverable cells with $1 \times 1$ bricks. For a $1 \times x$ brick, it can be formed by $x$ consecutive $1 \times 1$ bricks in the same row by "row merging" sequentially. Similarly, for an $x \times 1$ brick. It can be formed by $x$ consecutive $1 \times 1$ bricks in the same column by "column merging" sequentially.
    
    Obviously, one row merge and one column merge cannot interfere with the same brick, and the more merges, the fewer bricks there are. Therefore, we can take row merges as left vertices, column merges as right vertices, and use the previous conflicts as edges to construct a bipartite graph. The original problem then becomes a bipartite maximum independent set problem.

??? note "Code"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/bigraph-match/bigraph-match_5.cpp"
    ```

???+ example "[Codeforces 1139E - Maximize Mex](https://codeforces.com/problemset/problem/1139/E)"
    There are $m$ multisets, each containing $n$ elements. Each time, delete one element from a certain multiset, then query "the maximum mex that can be achieved by selecting at most one element from each multiset".

??? note "Solution"
    First, consider how to do it without deleting elements.
    
    For each multiset, create a new node. For each possible answer, create a new node. Then for each element $a$ of a multiset corresponding to node $l_i$, connect an edge from $l_i$ to $r_a$. At this point, this weakened version becomes a bipartite maximum matching.
    
    Now, adding back the operation of deleting elements: we find that it's fundamentally unmanageable: deleting an edge may cause huge changes in the matching, and the complexity is unacceptable. So instead, we add an edge each time and then re-augment. Therefore, only Kuhn's Algorithm can be used for this problem.

??? note "Code"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/bigraph-match/bigraph-match_6.cpp"
    ```

???+ example "[Luogu P3355 - Knight Coexistence Problem](https://www.luogu.com.cn/problem/P3355)"
    There is an $n \times n$ chessboard. Some positions cannot place pieces. Ask how many knights can be placed at most such that they do not attack each other.

??? note "Solution"
    It can be observed that if we color the entire board such that all black squares and white squares are not adjacent, then knights can only attack squares of the opposite color.
    
    Then we can directly proceed with bipartite maximum independent set.

??? note "Code"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/bigraph-match/bigraph-match_7.cpp"
    ```

## Exercises

-   [Codeforces 1765A - Access Levels](https://codeforces.com/problemset/problem/1765/A)
-   [AtCoder abc274G - Security Camera 3](https://atcoder.jp/contests/abc274/tasks/abc274_g)
-   [Codeforces 1773D - Dominoes](https://codeforces.com/problemset/problem/1773/D)
-   [Luogu P5030 - Long Necked Deer Placement](https://www.luogu.com.cn/problem/P5030)
-   [Luogu P2071 - Seat Arrangement](https://www.luogu.com.cn/problem/P2071)
-   [LibreOJ 6002 - Minimum Path Cover](https://loj.ac/p/6002)

## References

-   [Kuhn's Algorithm - Maximum Bipartite Matching](https://cp-algorithms.com/graph/kuhn_maximum_bipartite_matching.html)
-   [Kőnig's Theorem for Bipartite Maximum Matching and Its Proof](https://matrix67.com/blog/archives/116)
-   [Implementing Dinitz on bipartite graphs by adamant - Codeforces blogs](https://codeforces.com/blog/entry/118098)
-   Bondy, John Adrian, and Uppaluri Siva Ramachandra Murty. Graph theory with applications. Vol. 290. London: Macmillan, 1976.
-   Chen Yinbo. A Discussion on Graph Matching Algorithms and Their Applications. 2015 Chinese National Informatics Olympiad Team Candidate Paper Collection.
-   [Dulmage–Mendelsohn decomposition - Wikipedia](https://en.wikipedia.org/wiki/Dulmage%E2%80%93Mendelsohn_decomposition)
-   [Notes on Dulmage–Mendelsohn decomposition](https://www.cse.iitm.ac.in/~meghana/matchings/bip-decomp.pdf)

[^hk-comp-ref]: Bast, Holger; Mehlhorn, Kurt; Schäfer, Guido; Tamaki, Hisao (2006), "Matching algorithms are fast in sparse random graphs", Theory of Computing Systems, 39 (1): 3–14.