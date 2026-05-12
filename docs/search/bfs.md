## Introduction

BFS (breadth-first search) is a fundamental algorithm in graph theory; see the [BFS (graph theory)](../graph/bfs.md) page for details. In **search algorithms**, it usually refers to a search method that uses a queue structure to expand states level by level. This is consistent with the idea of BFS in graph theory and is especially suitable for solving **shortest path** or **minimum number of steps** problems.

## Explanation

The core idea of BFS is **level-by-level expansion**: starting from the source, it scans reachable positions one level at a time. The path length when the target is first encountered is the shortest path. This method guarantees the layered nature and optimality of the search.

In actual execution, BFS starts from the source and first visits all nodes directly reachable from it. These reachable nodes form the first layer of the search. Then, using these reachable nodes as new starting points, it visits their neighbors in turn to form the second layer. This continues, expanding outward until the target node is found or all reachable nodes have been traversed. During this process, the algorithm uses a queue and a visited array to enqueue newly discovered nodes at each layer (nodes not yet recorded in the visited array) in order, ensuring that nodes in the same layer are processed in visitation order and strictly following the logic of "level-by-level expansion".

BFS is very good at quickly solving **shortest path** or **minimum number of steps** problems. When the algorithm first encounters the target at some layer, the path length (number of steps) taken at that point must be the shortest. This is because BFS's "level-by-level expansion" mechanism guarantees that every node is reached in the minimum number of steps: it is like starting from the source and continuously searching along the most direct paths until reaching the target, without detours or extra steps. For this type of problem, BFS is usually also more efficient than DFS.

However, compared with DFS, BFS also has disadvantages. In general, BFS requires more memory, lacks a natural backtracking process, and is less flexible than DFS for depth-based pruning.

## Examples

???+ example "Example [Luogu B3625 Maze Pathfinding](https://www.luogu.com.cn/problem/B3625)"
    In an $n \times m$ maze matrix, `.` represents a passable area and `#` represents an obstacle. Starting from $(1,1)$, you may move in four directions: up, down, left, and right. Determine whether it is possible to reach the target $(n,m)$.

??? note "Solution"
    In the implementation, maintain a queue to store coordinates to be processed, and use a visited marker array to avoid repeated computation. When a node expands to reachable nodes, it needs to expand up, down, left, and right. These four directions are $(x, y + 1)$, $(x, y - 1)$, $(x + 1, y)$, and $(x - 1, y)$, and a direction array is used in the code. Be careful not to expand into cells with obstacles.

??? note "Reference implementation"
    ```cpp
    --8<-- "docs/search/code/bfs/bfs-1.cpp"
    ```

???+ example "Example [Luogu P1135 Strange Elevator](https://www.luogu.com.cn/problem/P1135)"
    There are $n$ floors and an elevator. When the elevator is on floor $i$, the number of floors it moves up or down is equal to a fixed number $k_i$. If the resulting floor is invalid, that is, not between $1$ and $n$, the corresponding operation cannot be performed. Ask: what is the minimum number of elevator operations needed to go from floor $a$ to floor $b$? If it is impossible, output $-1$.

??? note "Solution"
    This problem requires computing the shortest path, which is exactly what BFS is good at. In the implementation, the queue needs to maintain both the floor position to be processed and the shortest distance from the starting floor $a$ to the current floor. A visited marker array is also used to avoid adding the same element repeatedly. When a node $i$ expands to reachable nodes, it needs to expand to $i + k_i$ and $i - k_i$, while avoiding invalid floors. When expanding to a valid floor that has not yet been reached, add it to the queue and record the shortest distance to that floor as the shortest distance to the current floor plus one. When node $b$ is first reached, the recorded shortest distance is the final answer.
    
    In the code, the distance array is recorded directly, and whether the distance is the default value (namely $-1$) is used to determine whether a node has not yet been visited.

??? note "Reference implementation"
    ```cpp
    --8<-- "docs/search/code/bfs/bfs-2.cpp"
    ```

## Exercises

-   [Luogu P1443 Knight's Traversal](https://www.luogu.com.cn/problem/P1443)
-   [Luogu P3956 \[NOIP 2017 Junior Group\] Chessboard](https://www.luogu.com.cn/problem/P3956)
-   [Luogu P1126 Robot Moving Heavy Objects](https://www.luogu.com.cn/problem/P1126)
