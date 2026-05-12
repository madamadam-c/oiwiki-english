## Introduction

Before reading the following content, be sure to understand the [Graph Theory Related Concepts](./concept.md) section.

Related reading: [Cut Vertices and Bridges](./cut.md)

## Definition

For more rigorous definitions of cut vertices and bridges, see [Graph Theory Related Concepts](./concept.md).

In a connected undirected graph, for two vertices $u$ and $v$, if no matter which edge we remove (only one edge can be removed), they cannot become disconnected, then we say $u$ and $v$ are **edge-biconnected**.

In a connected undirected graph, for two vertices $u$ and $v$, if no matter which vertex we remove (only one vertex can be removed, and we cannot remove $u$ and $v$ themselves), they cannot become disconnected, then we say $u$ and $v$ are **vertex-biconnected**.

Edge-biconnectivity is transitive: if $x,y$ are edge-biconnected and $y,z$ are edge-biconnected, then $x,z$ are edge-biconnected.

Vertex-biconnectivity is **not** transitive. A counterexample is shown in the figure below: $A,B$ are vertex-biconnected, $B,C$ are vertex-biconnected, but $A,C$ are **not** vertex-biconnected.

![bcc-counterexample.png](./images/bcc-0.svg)

For a **maximal** edge-biconnected subgraph in an undirected graph, we call this subgraph an **edge-biconnected component**.

For a **maximal** vertex-biconnected subgraph in an undirected graph, we call this subgraph a **vertex-biconnected component**.

## DFS Spanning Tree

For a connected undirected graph, we can start DFS from any vertex to obtain a DFS spanning tree of the original graph (with the starting vertex as the root). The edges on this spanning tree are called **tree edges**, and edges not on the spanning tree are called **non-tree edges**.

Due to the nature of DFS, we can guarantee that for any non-tree edge, the two vertices it connects satisfy that one is an ancestor of the other on the spanning tree.

The DFS code is as follows:

???+ note "Implementation"
    === "C++"
        ```cpp
        void DFS(int p) {
          visited[p] = true;
          for (int to : edge[p])
            if (!visited[to]) DFS(to);
        }
        ```
    
    === "Python"
        ```python
        def DFS(p):
            visited[p] = True
            for to in edge[p]:
                if visited[to] == False:
                    DFS(to)
        ```

## Edge-Biconnected Components

???+ note "[Problem: Luogu P8436 [Template] Edge-Biconnected Components](https://www.luogu.com.cn/problem/P8436)"
    For an undirected graph with $n$ vertices and $m$ edges, output the number of edge-biconnected components, and output each edge-biconnected component.

### Tarjan's Algorithm 1

The process of finding biconnected components using Tarjan is similar to finding strongly connected components. You can first read [Tarjan's Algorithm for Strongly Connected Components](./scc.md).

We first find all bridges, then use DFS to find edge-biconnected components.

Finding bridges can be seen in the bridge section of [Cut Vertices and Bridges](./cut.md).

Time complexity is $O(n+m)$.

??? note "Sample Code"
    ```cpp
    --8<-- "docs/graph/code/bcc/bcc_1.cpp"
    ```

### Tarjan's Algorithm 2

First, we summarize an important property: in an undirected graph, an edge on the DFS spanning tree is either a tree edge or a non-tree edge.

Let's recall the method for finding strongly connected components. In an undirected graph, if a component has no bridges, then all its vertices are in the same strongly connected component on the DFS spanning tree.

Conversely, a strongly connected component on the DFS spanning tree is an edge-biconnected component in the original undirected graph.

We can find that the process of finding edge-biconnected components is actually the same as finding strongly connected components.

Time complexity is $O(n+m)$.

??? note "Sample Code"
    ```cpp
    --8<-- "docs/graph/code/bcc/bcc_2.cpp"
    ```

### Difference Algorithm

Similar to Tarjan's Algorithm 1, we first find all bridges, then use difference to find edge-biconnected components.

First, perform DFS on the original graph.

![bcc-1.png](./images/bcc-1.svg)

As shown in the figure, black and green edges are tree edges, and red edges are non-tree edges. Each non-tree edge uniquely corresponds to a simple path consisting of tree edges on the tree. We say this non-tree edge **covers** all edges on this simple path.

In the figure, green tree edges are covered by at least one non-tree edge, and black tree edges are not covered by **any** non-tree edge.

Obviously, **non-tree edges** and **green tree edges** are definitely not bridges, and **black tree edges** are definitely bridges.

First consider a brute force approach: for each non-tree edge, mark each tree edge it covers as green one by one, with time complexity $O(nm)$.

Consider using difference for optimization. For each non-tree edge, mark `-1` at the endpoint with smaller tree depth, and mark `+1` at the endpoint with larger tree depth. Then calculate the sum of marks within each vertex's subtree in $O(n)$ time.

For a vertex $u$, the sum of marks inside its subtree equals the number of non-tree edges covering the tree edge between $u$ and $fa_u$. If this value equals $0$, then the tree edge between $u$ and $fa_u$ is a **bridge**.

Then use DFS to find edge-biconnected components.

Time complexity is $O(n+m)$.

??? note "Sample Code"
    ```cpp
    --8<-- "docs/graph/code/bcc/bcc_4.cpp"
    ```

???+ note "[#2788. "CEOI2015 Day1" Pipes](https://loj.ac/p/2788)"
    Given an undirected graph with $N$ vertices and $M$ edges, not guaranteed to be connected. Treat each connected component as a subgraph, find the bridges in each subgraph. **You only have 16 MB of memory space.**

??? note "Solution"
    The biggest characteristic of this problem is that you cannot store all edges.
    
    Consider optimizing edge storage. If one non-tree edge is completely covered by another non-tree edge, then this edge is useless.
    
    Use a union-find set to maintain this.

## Vertex-Biconnected Components

???+ note "[Problem: Luogu P8435 [Template] Vertex-Biconnected Components](https://www.luogu.com.cn/problem/P8435)"
    For an undirected graph with $n$ vertices and $m$ edges, output the number of vertex-biconnected components, and output each vertex-biconnected component.

### Tarjan's Algorithm

First, you need to learn about cut vertices. You can see the cut vertex section of [Cut Vertices and Bridges](./cut.md).

First, give two properties:

1.  Two vertex-biconnected components share at most one common vertex, which must be a cut vertex.
2.  For a vertex-biconnected component, the vertex with the smallest dfn value in the DFS search tree is definitely a cut vertex or the tree root.

We discuss according to the second property:

1.  When this vertex is a cut vertex, it must be the root of the vertex-biconnected component, because if it still contains its parent node, it is still a cut vertex.
2.  When this vertex is the tree root:
    1.  If it has two or more subtrees, it is a cut vertex.
    2.  If it has only one subtree, it is the root of a vertex-biconnected component.
    3.  If it has no subtree, it is considered as a vertex-biconnected component.

??? note "Sample Code"
    ```cpp
    --8<-- "docs/graph/code/bcc/bcc_3.cpp"
    ```

### Difference Algorithm

![bcc-2.png](./images/bcc-2.svg)

As shown in the figure, black edges are tree edges, and red edges are non-tree edges. Each non-tree edge uniquely corresponds to a simple path consisting of tree edges on the tree.

Consider a new graph where each vertex in the new graph corresponds to each tree edge in the original graph (shown as blue vertices in the figure). For each non-tree edge in the original graph, connect all the blue vertices corresponding to the tree edges on the simple path that the non-tree edge corresponds to into a connected component (shown as blue edges in the figure).

Thus, a vertex is **not** a cut vertex if and only if all the blue vertices corresponding to edges connected to it belong to the **same** connected component.

Two vertices **are** vertex-biconnected if and only if all the blue vertices corresponding to edges on their path in the original tree belong to the **same** connected component. That is, each connected component formed by blue vertices is a vertex-biconnected component.

The connectivity relationship between blue vertices can be maintained using a method similar to the difference algorithm used for finding edge-biconnected components, with time complexity $O(n+m)$.