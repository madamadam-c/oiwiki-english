This article introduces the A\* search algorithm.

The A\* search algorithm (A\* is pronounced A-star), abbreviated as the A\* algorithm, is an algorithm for finding the shortest path between a given start point and end point in a weighted directed graph. It belongs to graph traversal and best-first search algorithms, and is also an improvement over [BFS](./bfs.md).

## Process

The goal of the A\* algorithm is to find the shortest path from the start point $s$ to the end point $t$ in a directed graph. Let $d(x,y)$ be the distance between nodes $x$ and $y$, that is, the length of the shortest path between them. Let $g(x)=d(s,x)$ be the distance function from the start point $s$ to node $x$, let $h^*(x)$ be the distance function from node $x$ to the end point $t$, and let $h(x)$ be an estimate of $h^*(x)$[^note1]. Finally, denote the estimate of the shortest path length from $s$ through $x$ to $t$ as

$$
f(x) = g(x) + h(x).
$$

During the search, the A\* algorithm takes from the priority queue the node with the smallest $f$ each time. Then it pushes all of its successor nodes $x$ into the priority queue and updates $f(x)$ using the actually recorded $g(x)$ and the estimated $h(x)$.

## Properties

Because the actual value of $h^*(x)$ is unknown during the search, an easily computed $h(x)$ must be used as its estimate. The actual complexity of A\* search depends on the properties of this estimation function $h(x)$. It is easy to imagine that if $h\equiv h^*$, that is, the estimate is exact, then the search process will proceed strictly along the shortest path. If $h\equiv 0$, then the A\* algorithm degenerates into [Dijkstra's algorithm](./../graph/shortest-path.md#dijkstra-算法); when $h\equiv 0$ and all edge weights are $1$, it is [BFS](./bfs.md).

Assume the graph has no negative-weight edges. If the estimate $h(x)$ never exceeds the actual distance $h^*(x)$, namely $0\le h\le h^*$, then the A\* algorithm is guaranteed to find an optimal solution. An estimation function $h(x)$ satisfying this condition is called **admissible**. According to the discussion above, the closer $h$ is to $h^*$, the more efficient the corresponding A\* algorithm is. In general, in the worst case, the algorithm will visit all nodes satisfying

$$
f(x) = g(x) + h(x) \le C^*
$$

where $C^*$ is the shortest distance between the start point $s$ and the end point $t$. Intuitively, the closer $h$ is to $h^*$, the fewer successor nodes can satisfy this condition at each expansion, and therefore the fewer branches the algorithm searches. Thus, the A\* algorithm can be seen as a kind of "pruning" optimization for search algorithms.

If $h$ is not only admissible but also **consistent**, namely

$$
h(x) \le h(y) + d(x, y),
$$

then the A\* algorithm will not add a node that has already been popped from the queue back into the queue. The consistency condition can be understood as the triangle inequality among nodes $x,y,t$.

## Examples

A classic application of the A\* algorithm is solving the k-th shortest path problem. For the problem statement, the A\* approach, and the persistent meldable heap approach with better complexity, see the [k-th shortest path problem](./../graph/kth-path.md) page.

This section introduces a classic problem that can be solved with the A\* algorithm.

???+ example "[Eight Puzzle](https://www.luogu.com.cn/problem/P1379)"
    On a $3\times 3$ board, there are eight tiles, each labeled with one of the numbers from $1$ to $8$. One cell on the board is empty, represented by $0$. Tiles adjacent to the empty cell can be moved into it, making their original position empty. Given an initial layout and a target layout (to simplify the problem, the target state is set as follows), find a sequence of moves with the minimum number of steps from the initial layout to the target layout.
    
    $$
    \begin{aligned}
    123\\
    804\\
    765
    \end{aligned}
    $$

??? note "Solution idea"
    The $h$ function can be defined as the number of tiles that are not in their correct positions. It is easy to see that $h$ is both admissible and consistent. This problem can be solved with the A\* algorithm.

??? note "Reference code"
    ```cpp
    --8<-- "docs/search/code/astar/astar_1.cpp"
    ```

## References and Notes

-   [A\* search algorithm - Wikipedia](https://en.wikipedia.org/wiki/A*_search_algorithm)

[^note1]: Here $h$ stands for heuristic. See [Heuristic - Wikipedia](https://en.wikipedia.org/wiki/Heuristic) and the Bounded relaxation section of [A\* search algorithm - Wikipedia](https://en.wikipedia.org/wiki/A*_search_algorithm#Bounded_relaxation).
