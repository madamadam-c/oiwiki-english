author: Persdre

Prerequisites: [Clique](./concept.md)

## Introduction

In computer science, the clique problem refers to the computational problem of finding a clique (a subset of vertices where every two vertices are adjacent, also called a complete subgraph) in a given graph.

Clique problems also appear in real life. Consider a social network where vertices represent users and edges represent that the two connected users know each other. Finding a clique in this graph means finding a group of people who all know each other.

To find the largest such group of mutual acquaintances, we need a maximum clique search algorithm.

We've already introduced the concept of [maximal clique](./concept.md). The maximum clique is the maximal clique with the most vertices.

## Explanation

The idea is to use recursion and backtracking. Maintain a list of vertices, and each time we add a vertex, check if these vertices still form a clique. If adding a vertex makes it impossible to remain a clique, backtrack to the last valid state and try a different vertex.

Backtracking is used because we don't know whether a vertex $v$ will ultimately be a member of a maximum clique. If the recursive algorithm chooses $v$ as a member but fails to find the maximum clique, it should backtrack and look for a solution that doesn't include $v$.

## Process

The **Bron–Kerbosch** algorithm provides an optimized implementation of this idea. Its basic form uses three sets: $R$, $P$, and $X$, and performs a recursive search. Steps:

1. Initialize $R$ and $X$ as empty sets, and $P$ as the set of all vertices in the graph.
2. Each time we take a vertex $v$ from set $P$. When there are no vertices left, there are two cases:
    1. Set $R$ is a maximal clique, and set $X$ is empty.
    2. No maximal clique exists, so we backtrack.
3. For each vertex $v$ taken from set $P$, the processing is:
    1. Add vertex $v$ to set $R$, then recursively call on $R, P, X$.
    2. Remove vertex $v$ from set $P$, and add vertex $v$ to set $X$.
    3. If both sets $P$ and $X$ are empty, then set $R$ is a maximal clique.

This method can be further optimized. To save time and enable faster backtracking, we can use a pivot vertex. Another optimization is to sort all vertices at the start and enumerate them in order to avoid duplicates.

## Implementation

### Pseudocode

```text
R := {}
P := node set of G
X := {}

BronKerbosch1(R, P, X):
    if P and X are both empty:
        report R as a maximal clique
    for each vertex v in P:
        BronKerbosch1(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
        P := P \ {v}
        X := X ⋃ {v}
```

### C++ Implementation

??? note "Implementation Code"
    ```cpp
    --8<-- "docs/graph/code/max-clique/max-clique_1.cpp"
    ```

## Examples

???+ note "[POJ 2989: All Friends](http://poj.org/problem?id=2989)"
    Problem: Given $n$ people and $m$ pairs of friends, find the number of maximal cliques.

    Approach: Template problem requiring the Bron–Kerbosch algorithm.

    Pseudocode:

    ```text
     BronKerbosch(All, Some, None):
         if Some and None are both empty:
             report All as a maximal clique // all vertices selected, no excluded vertices, increment answer
         for each vertex v in Some: // enumerate each element in Some
             BronKerbosch1(All ⋃ {v}, Some ⋂ N(v), None ⋂ N(v))
             // add v to All; only v's friends can be candidates; only v's friends in None affect future processing
             Some := Some - {v} // already processed, remove from Some and add to None
             None := None ⋃ {v}
    ```

    To save time and enable faster backtracking, we can optimize by selecting a pivot vertex $v$.

    In the algorithm above, there are inevitably many repeated computations of the same maximal cliques followed by backtracking.

    Using the sets $R$, $P$, $X$ mentioned earlier:

    Consider the following: pick a vertex $u$ from $P \cup X$. To form a maximal clique with $R$, the vertices we pick must be in $P \cap N(u)$ ($N(u)$ denotes vertices adjacent to $u$).

    If after picking $u$, a vertex $v$ adjacent to $u$ can also be added to the maximal clique, then picking only $u$ is sufficient. This reduces redundant computation of $v$ later. We only need to pick vertices not adjacent to $u$.

    C++ code with this optimization:

    ??? note "Implementation Code"
        ```cpp
        --8<-- "docs/graph/code/max-clique/max-clique_2.cpp"
        ```

## Exercises

- [ZOJ 1492 Maximum Clique](https://pintia.cn/problem-sets/91827364500/exam/problems/type/7?page=4&problemSetProblemId=91827364991)
- [POJ 1419 Maximum Clique in an Undirected Graph](http://poj.org/problem?id=1419)
- [POJ 1129 Radio Station](http://poj.org/problem?id=1129)

## References

- [Clique Problem - Wikipedia](https://en.wikipedia.org/wiki/Clique_problem)
- [Maximal and Maximum Cliques in Undirected Graphs (Bron–Kerbosch Algorithm)](https://blog.csdn.net/yo_bc/article/details/77453478)
- [Maximum Clique Problem — Bron–Kerbosch Algorithm](https://hallelujahjeff.github.io/2018/04/12/34/)
- [Maximum Clique Problem](https://www.cnblogs.com/zhj5chengfeng/archive/2013/07/29/3224092.html)