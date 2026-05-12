This page gives a brief introduction to the concept, implementation, and applications of Eulerian graphs.

## Definition

In this article, we only discuss finite graphs.

In graph theory, an **Eulerian path** is a path that traverses each edge exactly once, and an **Eulerian circuit** is a circuit that traverses each edge exactly once. If a graph contains an Eulerian circuit, it is called an **Eulerian graph**; if a graph does not contain an Eulerian circuit but contains an Eulerian path, it is called a **semi-Eulerian graph**.

??? warning "Warning"
    Although the term "path" is used in this definition, strictly speaking, the concept used here should be "trail". Eulerian paths and Eulerian circuits can only use each edge exactly once, but there is no restriction on how vertices are visited.

## Properties

In the following, we assume that the graph $G$ under discussion has no isolated vertices. This assumption is without loss of generality, because for a graph $G$ with isolated vertices, the following properties still hold for the graph $G'$ obtained by removing isolated vertices from $G$.

For a connected graph $G$, the following three properties are equivalent:

1.  $G$ is an Eulerian graph;
2.  All vertices in $G$ have even degree (for directed graphs, each vertex's in-degree equals its out-degree);
3.  $G$ can be decomposed into a union of edge-disjoint circuits.

We prove the equivalence below.

If a graph $G$ is an Eulerian graph, then all vertices in $G$ have even degree: Consider starting from any vertex and walking along the Eulerian circuit once. For each vertex $v$, the degree of $v$ equals the number of times we leave $v$ plus the number of times we arrive at $v$. Since the walk is a circuit, for each vertex $v$, the number of times we leave $v$ equals the number of times we arrive at $v$. This means each vertex's degree is of the form $2k$, i.e., even.
In particular, for directed graphs, by the same reasoning, each vertex's in-degree equals its out-degree.

If all vertices in a graph $G$ have even degree (or in-degree equals out-degree), then it can be decomposed into a disjoint union of edge-disjoint circuits: Consider starting from any vertex $u$, choosing any outgoing edge $(u, v)$, moving to the corresponding adjacent vertex $v$ and deleting $(u, v)$, until we return to the starting vertex $u$. It can be proven that this process must eventually return to $u$: whenever we arrive at a new vertex $v \neq u$, according to the previous property, the remaining degree of this vertex is odd, meaning there must exist an outgoing edge, so the process will not terminate at vertex $v$. (In other words, the process will only stop when it returns to vertex $u$.) Since the number of edges in graph $G$ is finite, this process must stop in a finite number of steps, so we will inevitably return to $u$ and obtain a circuit. Note that in the above proof we only used the property that all vertex degrees are even, and after finding and deleting one circuit, the remaining graph still satisfies this property. We can repeat this process until the remaining graph is empty, thus splitting $G$ into several edge-disjoint circuits.
Furthermore, each circuit can be decomposed into a disjoint union of simple cycles from vertices that are traversed multiple times, so the simple circuits in the above property can also be replaced by simple cycles.

If a connected graph $G$ can be decomposed into a disjoint union of edge-disjoint circuits, then $G$ is an Eulerian graph: For a set of edge-disjoint circuits, each time we select two circuits that share a vertex and merge them into one circuit, repeating this process until there are no two circuits sharing a vertex.
It can be proven that at the end of this process, the remaining circuit is unique. For any two edge-disjoint circuits $P_1, P_2$, if $P_1$ and $P_2$ share a vertex, they can be merged directly at the shared vertex; otherwise, take any vertex $v_1$ on $P_1$ and any vertex $v_2$ on $P_2$. By the connectivity of $G$, there exists a path connecting $v_1$ and $v_2$, say $e_1, e_2, \ldots, e_k$, where each edge $e_i$ is contained in a circuit $C_i$, and $P_1$ shares a vertex with $C_1$, $C_i$ shares a vertex with $C_{i+1}$, and $C_k$ shares a vertex with $P_2$ (or $C_i = C_{i+1}$, this case does not affect the proof). In this case, $P_1$ and $P_2$ can be merged through $C_1, \ldots, C_k$. That is, any two circuits can be merged, and the final remaining circuit must be unique, and the set of edges composing this circuit is the union of all edge-disjoint circuits, which is $E(G)$. This circuit is an Eulerian circuit on $G$, so $G$ is an Eulerian graph.

The above properties also constitute the criteria for determining Eulerian graphs. Specifically, a graph is an Eulerian graph if and only if all non-zero degree vertices are (strongly) connected, and all vertices have even degree (or in-degree equals out-degree).

For semi-Eulerian graphs, the properties are similar to Eulerian graphs: a semi-Eulerian graph has exactly two vertices of odd degree, and these two vertices are the two endpoints of the Eulerian path. By connecting these two vertices, a semi-Eulerian graph can be transformed into an Eulerian graph. By deleting any edge from an Eulerian graph, a semi-Eulerian graph can be obtained.
From this, the criterion for semi-Eulerian graphs can be derived: a graph is a semi-Eulerian graph if and only if all non-zero degree vertices are (strongly) connected, and there are exactly two vertices of odd degree. For directed graphs, the second condition is that there exist exactly two vertices $u, v$ where $\deg^+(u) - \deg^-(u) = 1, \deg^+(v) - \deg^-(v) = -1$, and for all other vertices, in-degree equals out-degree.

## Constructing Eulerian Circuits/Eulerian Paths

Here we introduce the most commonly used Hierholzer algorithm, whose core idea is to use the third point in the properties of Eulerian graphs mentioned above, i.e., an Eulerian graph can be decomposed into a union of edge-disjoint circuits.
It can be noted that the complete feasible operation for merging edge-disjoint circuits into an Eulerian circuit was actually mentioned in the above proof, and with appropriate data structures (such as using a linked-list-like structure to store cycles), the implementation is not difficult.

The specific algorithm flow is: first find a circuit in the graph as the current circuit, each time select a vertex with non-zero remaining degree from the current circuit, find a new simple circuit starting from that vertex, and merge this simple circuit with the current circuit. Repeat this process until all vertices in the current circuit have no remaining degree. At this point, the current circuit is the Eulerian circuit.

This algorithm also works for directed graphs. For semi-Eulerian graphs, find a path connecting the two odd-degree vertices as the current path in the graph, each time select a vertex with non-zero degree to find a simple circuit and merge it with the current path, and finally obtain the Eulerian path.

### Implementation

The pseudocode for Hierholzer's algorithm is as follows:

$$
\begin{array}{ll}
1 &  \textbf{Input. } \text{The edges of the graph } e , \text{ where each element in } e \text{ is } (u, v) \\
2 &  \textbf{Output. } \text{The vertex of the Euler Road of the input graph}.\\
3 &  \textbf{Method. } \\
4 &  \textbf{Function } \text{Hierholzer } (v) \\
5 &  \qquad circle \gets \text{Find a Circle in } e \text{ Begin with } v \\
6 &  \qquad \textbf{if } circle=\varnothing \\
7 &  \qquad\qquad \textbf{return } v \\
8 &  \qquad e \gets e-circle \\
9 &  \qquad \textbf{for} \text{ each } v \in circle \\
10&  \qquad\qquad v \gets \text{Hierholzer}(v) \\
11&  \qquad \textbf{return } circle \\
12&  \textbf{Endfunction}\\
13&  \textbf{return } \text{Hierholzer}(\text{any vertex})
\end{array}
$$

### Time Complexity Analysis

The time complexity of Hierholzer's algorithm is $O(|E| + |V|)$.

Note that in the correctness analysis above, the process of finding a simple circuit (or the initial path for semi-Eulerian graphs) on an Eulerian or semi-Eulerian graph is **without backtracking**. As long as we follow the remaining edges, we will inevitably find the required circuit or path, and **each edge is visited only once**.
To exploit this property, in implementation, edges should be stored in a linked-list-like manner, such as adjacency lists or chain forward stars, so that each edge can be deleted immediately after being visited. If a naive adjacency matrix is used, each edge search takes $O(|V|)$ time, resulting in a total complexity of $O(|V||E|)$.

???+ note "Note"
    In fact, the exact complexity of this algorithm should be $O(|E|)$ rather than $O(|V| + |E|)$, because the implementation can use an edge-dependent rather than vertex-dependent method, by maintaining a linked list of remaining edges to find the next circuit.

If the lexicographically smallest Eulerian path or Eulerian circuit needs to be output, edges need to be sorted, with time complexity $\Theta(|E|\log |E|)$ or $\Theta(|E|)$ (using counting sort or radix sort).

### Application

Directed Eulerian graphs can be used for computer decoding.

Suppose we have $m$ letters, and we want to construct a disk with $m^n$ sectors, with one letter on each sector, such that each consecutive $n$ positions on the disk correspond to a symbol string of length $n$. After rotating for one cycle ($m^n$ times), we obtain $m^n$ distinct symbol strings of length $n$ produced by the $m$ letters.

![](images/euler1.svg)

Construct the following directed Eulerian graph:

Let $S = \{a_1, a_2, \cdots, a_m\}$, construct $D=\langle V, E\rangle$ as follows:

$V = \{a_{i_1}a_{i_2}\cdots a_{i_{n-1}} |a_i \in S, 1 \leq i \leq n - 1 \}$

$E = \{a_{j_1}a_{j_2}\cdots a_{j_{n-1}}|a_j \in S, 1 \leq j \leq n\}$

The incidence relationship between vertices and edges in $D$ is defined as follows:

Vertex $a_{i_1}a_{i_2}\cdots a_{i_{n-1}}$ has $m$ outgoing edges: $a_{i_1}a_{i_2}\cdots a_{i_{n-1}}a_r, r=1, 2, \cdots, m$.

Edge $a_{j_1}a_{j_2}\cdots a_{j_{n-1}}$ enters vertex $a_{j_2}a_{j_3}\cdots a_{j_{n}}$.

![](images/euler2.svg)

Such $D$ is connected, and each vertex has in-degree equal to out-degree (both equal to $m$), so $D$ is a directed Eulerian graph.

Find any Eulerian circuit $C$ in $D$, take the last letter of each edge in $C$, arrange them in the order of edges in $C$ in a circle and place them on the disk.

## Example Problems

???+ note "[Luogu P2731 Riding Repair Fences](https://www.luogu.com.cn/problem/P2731)"
    Given an undirected graph with 500 vertices, find an Eulerian path or Eulerian circuit in this graph. If there are multiple solutions, output the smallest one.
    
    In this problem, the Eulerian path or Eulerian circuit does not need to pass through all vertices.
    
    The number of edges $m$ satisfies $1\leq m \leq 1024$.

??? note "Solution Idea"
    This problem is a direct application of Hierholzer's algorithm.
    
    To save the answer, we can use `std::stack<int>`, because if what we find is not a circuit, that part must be placed at the end.
    
    Note that we cannot use an adjacency matrix to store the graph, otherwise the time complexity will degrade to $\Theta(nm)$. Since edges need to be sorted, it is recommended to use forward stars or `std::vector` to store the graph. The sample code uses `std::vector`.

??? note "Sample Code"
    ```cpp
    --8<-- "docs/graph/code/euler/euler_1.cpp"
    ```

## Practice Problems

-   [SGU 101 Domino](https://codeforces.com/problemsets/acmsguru/problem/99999/101)

-   [POJ 1780 Code](http://poj.org/problem?id=1780)

-   [Luogu P1127 Word Chain](https://www.luogu.com.cn/problem/P1127)

-   [Luogu P1333 RuiRui's Stick](https://www.luogu.com.cn/problem/P1333)

-   [Luogu P1341 Unordered Letter Pair](https://www.luogu.com.cn/problem/P1341)

-   [Luogu P6066 [USACO05JAN]Watchcow S](https://www.luogu.com.cn/problem/P6066)

-   [Luogu P6628 [Provincial Selection 2020 B] Lilac Road](https://www.luogu.com.cn/problem/P6628)

-   [Luogu P3520 [POI 2011] SMI-Garbage](https://www.luogu.com.cn/problem/P3520)