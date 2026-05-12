Prerequisites: [Dijkstra Algorithm](./shortest-path.md#dijkstra-algorithm), [A* Algorithm](../search/astar.md), [Persistent Mergeable Heap](../ds/persistent-heap.md)

## Problem Description

Given a directed graph with $n$ nodes and $m$ edges, find the length of the $k$-th shortest path among all distinct paths from $s$ to $t$.

???+ info ""Path""
    The "path" referred to in this article allows passing through the same edge or node multiple times. Therefore, the strict term should be "[Walk](./concept.md#path)" rather than "Path". The problem discussed here is strictly the **$k$ shortest walk** problem. However, following convention, this article still uses the term "path", and refers to non-self-intersecting paths as "simple paths".

## A* Algorithm

A* is a search algorithm. It sets an evaluation function $f(x) = g(x) + h(x)$ for each current state $x$, where $g(x)$ is the actual cost from the initial state to the current state, and $h(x)$ is the estimated cost from the current state to the goal state. During search, we always expand the state $x$ with the smallest $f(x)$. A **priority queue** can be used to maintain this value.

When solving the $k$-shortest-path problem, let $h(x)$ be the shortest path length from the current node to the target $t$. This can be precomputed by running single-source shortest path from node $t$ on the reverse graph. For each state, we need to record two values: the current node $x$ and the distance already traveled $g(x)$. Denote this state as $(x, g(x))$. Initially, add the initial state $(s, 0)$ to the priority queue. Each time, pop the state with the smallest evaluation function $f(x) = g(x) + h(x)$, enumerate all outgoing edges of the node $x$ where this state is located, and add the corresponding successor states to the priority queue. When a node is visited for the $k$-th time, the $g(x)$ of the corresponding state is the length of the $k$-shortest path from the start node $s$ to that node.

This search process can be optimized. Since we only need to find the $k$-shortest paths from the start node to the target node, when a state has been popped more than $k$ times for a node, we can stop expanding its successors. This state will not affect the final answer, because when the node was popped the previous $k$ times, $k$ valid paths to that node have already been formed, which is sufficient to construct the first $k$ shortest paths to the target node.

If using a priority queue to optimize Dijkstra's algorithm, since each edge is added to the priority queue at most $k$ times, the time complexity is $O(km \log km)$ and the space complexity is $O(km)$. Compared to direct search, A* performs pruning towards the target node $t$, but this only improves the constant, not the asymptotic complexity. Although the algorithm described in this section does not have excellent complexity, it can find the first $k$ shortest paths to each node in the shortest path tree rooted at $t$ within the same complexity.

### Implementation

??? example "Template Problem [Library Checker - K-Shortest Walk](https://judge.yosupo.jp/problem/k_shortest_walk) Reference Implementation"
    ```cpp
    --8<-- "docs/graph/code/k-shortest-walk/k-shortest-walk-1.cpp"
    ```

## Persistent Mergeable Heap Approach

The previous algorithm actually finds the $k$-shortest paths to all nodes. If we only need the $k$-shortest paths to a given target node $t$, we can actually do it faster. This section provides an approach with complexity $O(m \log m + k \log k)$ based on persistent mergeable heaps.

### Shortest Path Tree and Sidetrack Edges

The bottleneck of the previous algorithm is that we only update the answer when reaching the target node $t$. However, different paths may not differ much. For example, the second shortest path differs from the shortest path only by possibly taking a detour at one edge, while the rest of the path is the same; the previous algorithm may need to search through these same edges repeatedly to find the second shortest path. Since only the detour part is key, to get the first $k$ shortest paths, we only need to consider the $k$ smallest detour methods. This leads to the concept of the shortest path tree.

Run single-source shortest path from the target node $t$ on the reverse graph. For each node $x$, record the shortest path length $h(x)$ from $x$ to $t$, and record the first edge $f_x$ of the shortest path starting from node $x$; if there are multiple optimal choices, any one can be chosen. All these edges $f_x$ and their endpoints form a tree, and the simple path from each node $x$ on this tree to the root $t$ is a shortest path from $x$ to $t$. This is the **shortest path tree** $T$.

After obtaining the shortest path tree $T$, we can compute how much extra distance each edge not in $T$ adds. For an edge $e = (u, v) \notin T$ with weight $w$, we can define a new edge still pointing from $u$ to $v$, with cost $\Delta(e) = w + h(v) - h(u)$. In this article, we informally call these edges with weight $\Delta(e)$ as **sidetrack edges**, and $\Delta(e)$ as the sidetrack cost. If an edge's endpoints are not both in the shortest path tree $T$, it does not affect the computation of $k$-shortest paths to node $t$, and can be directly removed.

The left side of the figure below is the directed graph $G$, and the right side shows its corresponding shortest path tree $T$ (thick edges) and the corresponding sidetrack edges (thin edges):

![](./images/k-shortest-path-1.svg)

Let $P$ be the set of edges of a path from $s$ to $t$. Remove the intersection with $T$ from $P$ to get $P'$. Then, arranging the edges in $P'$ in sequence, two consecutive edges $e_1 = (u_1, v_1)$ and $e_2 = (u_2, v_2)$ must satisfy:

-   Condition $(*)$: The starting point $u_2$ of the latter is an ancestor (including itself) of the endpoint $v_1$ in the shortest path tree $T$.

This is because in the original path $P$, $v_1$ and $u_2$ are connected by several tree edges in $T$. Conversely, for any edge set $P'$ satisfying condition $(*)$, there is a unique corresponding path $P$ in graph $G$. This is because the simple path from $v_1$ to $u_2$ on the shortest path tree $T$ is unique. This shows that any path $P$ in the original graph corresponds one-to-one with a sidetrack edge sequence $P'$ satisfying condition $(*)$. Moreover, the length of path $P$ equals the shortest path length $h(s)$ plus the sum of these sidetrack costs:

$$
h(s) + \sum_{e\in P'}\Delta(e).
$$

This discussion shows that finding the $k$-shortest paths is transformed into finding the $k$-th smallest sidetrack edge sequence $P'$ that satisfies condition $(*)$.

To handle condition $(*)$, instead of searching for ancestors on the shortest path tree each time, we can directly propagate each node's sidetrack edge set to its descendants on the shortest path tree. This constructs a graph like $G'$:

![](./images/k-shortest-path-2.svg)

On this graph, condition $(*)$ is transformed into requiring that edges in $P'$ are connected end-to-end, i.e., $P'$ is a path in graph $G'$. The problem is further transformed into finding the $k$-th smallest path **to any node** starting from $s$ in this graph. Compared to the original $k$-shortest-path problem, we no longer require the path to end at the target node $t$.

The transformed problem is easy to solve. Simply run single-source shortest path starting from node $s$. Each time we pop a node from the priority queue, we have found a path in graph $G'$, which corresponds to a path to the target node $t$ in graph $G$.

### Persistent Mergeable Heap Optimization

The algorithm idea is clear. However, a naive implementation has too high complexity. In graph $G'$, the number of edges at a single node could be $\Theta(m)$. Therefore, each single-source shortest path computation might need to push an edge set of size $\Theta(m)$ into the priority queue. In fact, it is not necessary to push all edges into the priority queue: in many cases, only the shortest ones among the pushed edges might be popped from the queue in subsequent calculations. That is, we can treat the entire edge set at a single node as one storage unit pushed into the priority queue, and each time we can quickly access the shortest edge in the edge set.

This inspires us to use a min-heap to store the edge set at each node. In the priority queue for single-source shortest path, we only need to store these heaps, and their cost is the shortest path cost corresponding to the heap top. Each time we pop from the queue, we need to pop the top edge from the heap at the front. Then, we push the heap back into the priority queue after popping the top, and also push the heap corresponding to the sidetrack edge set at the endpoint of the popped top edge into the priority queue.

Using heaps to store edge sets also solves the problem of propagating edge sets along the shortest path tree. Propagating edge sets to descendants requires merging the current node's edge set into its child nodes. Therefore, the heap needs to support merge operations; while merging to child nodes, we must not destroy the edge set at the current node, so the heap also needs to support persistence. This is exactly a persistent mergeable heap.

Thus, the complete process of the algorithm is:

1.  From the target node $t$, run single-source shortest path to find the shortest path tree.
2.  For each node on the shortest path tree, construct its corresponding sidetrack edge set and store it in a persistent mergeable heap.
3.  Along the edges of the shortest path tree, starting from the target node $t$, merge each node's heap into its child node's heap.
4.  Starting from the start node $s$, push the heap at that location into the priority queue.
5.  Pop the heap from the front, record the answer, push the heap after popping the top back into the priority queue, and push the heap at the endpoint of the popped top edge into the priority queue.

Generally, leftist trees or randomized heaps are used to implement persistent mergeable heaps. At this point, the last step can be further optimized. The internal structure of these heaps is binary trees. After popping the heap top, normally we would merge the two child nodes and push the merged heap back into the priority queue; however, in this algorithm, we can skip the merge operation and directly push the two child node heaps into the priority queue separately. This saves the $O(\log m)$ complexity of a single merge. Since after each heap pop, at most three new heaps are pushed into the priority queue, the size of the priority queue is $O(k)$. This reduces the single query time complexity to $O(\log k)$. The total query complexity is $O(k \log k)$.

Since the complexity of constructing the shortest path tree and constructing the persistent mergeable heap are both $O(m \log m)$, the total time complexity of the algorithm is $O(m \log m + k \log k)$.

### Implementation

??? example "Template Problem [Library Checker - K-Shortest Walk](https://judge.yosupo.jp/problem/k_shortest_walk) Reference Implementation"
    ```cpp
    --8<-- "docs/graph/code/k-shortest-walk/k-shortest-walk-2.cpp"
    ```

## Practice Problems

-   [SDOI2010 Magic Pig Academy](https://www.luogu.com.cn/problem/P2483)

## References and Notes

-   [Tutorial: k shortest paths and Eppstein's algorithm by meooow - Codeforces](https://codeforces.com/blog/entry=102085)