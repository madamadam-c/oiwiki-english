## Introduction

A bipartite graph, also called a bicolored graph, is a type of graph with special structure. Its vertex set can be divided into two disjoint subsets such that every edge in the graph connects a pair of vertices between these two sets, rather than connecting vertices within the same set.

Due to this simple structure, bipartite graphs not only exhibit many elegant properties but are also widely used in real-world modeling scenarios such as task assignment, recommendation systems, and matching markets. Many optimization problems that are difficult on general graphs can be solved efficiently and accurately on bipartite graphs.

## Definition

If the vertex set $V$ of a graph $G=(V,E)$ can be divided into two disjoint subsets $X$ and $Y$ such that each edge $e\in E$ has its two endpoints belonging to $X$ and $Y$ respectively, then we call $G$ a **bipartite graph**. The sets $X$ and $Y$ are often called its two **parts**, or the left and right sides of the bipartite graph. When the two parts $X$ and $Y$ of a bipartite graph are known, it can also be denoted as a triple $(X, Y, E)$.

A typical bipartite graph is shown in the figure below.

![](./images/bi-graph-1.svg)

Trees, even cycles, and grid graphs are all common examples of bipartite graphs.

## Characterization

A bipartite graph can also be equivalently defined by the following properties:

-   Graph $G$ is 2-colorable. That is, all vertices of the graph can be colored with at most two colors such that adjacent vertices have different colors.
-   Graph $G$ contains no cycles of odd length.

Obviously, the first property is equivalent to the definition of a bipartite graph: we only need to color each part of the bipartite graph with one color.

The second property is slightly more complex. Consider trying to color the graph $G$ with two colors. Since different connected components do not interfere with each other's coloring, we only need to consider each connected component separately. Choose an arbitrary vertex $s$ in a connected component, perform DFS, and record the distance of each vertex $v$ from $s$. Starting from $s, by induction on the DFS spanning tree, if there exists a feasible coloring, it must be based on the parity of each vertex $v$'s distance from the starting vertex $s$: color them with two different colors accordingly.

![](./images/bi-graph-2.svg)

Now consider the edges not in the spanning tree. If the two endpoints of such a non-tree edge have different colors, then the current coloring scheme is feasible; otherwise, no feasible scheme exists. Furthermore, two vertices have different colors if and only if their distances to the root $s$ have different parity, which is equivalent to the non-tree edge forming an even cycle rather than an odd cycle. Therefore, as long as there are no odd cycles, these non-tree edges must connect vertices of different colors, and thus the entire graph can be colored with two colors, making the graph a bipartite graph.

## Testing

To determine whether a graph is a bipartite graph, we only need to use the above equivalent characterization and try to color the bipartite graph. To do this, we can traverse the graph using DFS or BFS. If we find an odd cycle, i.e., a situation where coloring is impossible, then it is not a bipartite graph; otherwise, it is a bipartite graph.

The specific process is as follows:

-   Traverse vertices. If we find an uncolored vertex, it means we have discovered a new connected component.
-   Choose any color to color this vertex, and use it as the starting point for DFS or BFS to try to color this connected component.
-   When traversing adjacent vertices, if we find a vertex that has already been colored, check whether its color is the same as the current vertex. If it is the same, then it is not a bipartite graph, return directly; otherwise, continue traversing.
-   If we find an uncolored vertex, color it with the opposite color of the current vertex.

Reference code is as follows:

???+ example "Reference Code"
    ```cpp
    --8<-- "docs/graph/code/bi-graph/check-bipartite.cpp:core"
    ```

The time complexity is $O(|V|+|E|)$.

## Applications

Due to the simple structure, many graph theory optimization problems can be efficiently solved on bipartite graphs. See the relevant main articles for details.

-   Maximum clique (trivial)
-   Minimum vertex coloring (trivial)
-   Minimum edge coloring
-   Maximum matching
-   Minimum edge cover
-   Minimum vertex cover
-   Maximum independent set
-   Maximum weight matching
-   Bipartite game