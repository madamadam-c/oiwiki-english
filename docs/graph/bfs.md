author: Ir1d, greyqz, yjl9903, Anguei, Marcythm, ChungZH, Xeonacid, ylxmf2005

BFS stands for [Breadth First Search](https://en.wikipedia.org/wiki/Breadth-first_search), also known as breadth-first search.

It is one of the most fundamental and important search algorithms on graphs.

The idea of breadth-first is to try visiting all nodes at the same depth before moving to the next depth.

If all nodes at the current depth have been visited, then move to the next depth.

As a result, the path found by BFS from the start node is the **shortest** valid path. In other words, this path contains the minimum number of edges.

When BFS finishes, every node is visited via the shortest path from the start node.

The algorithm can be visualized as the spread of fire on a graph: initially only the start node is on fire, and at each moment, every burning node spreads the fire to all adjacent nodes.

## Implementation

The C++ and Python implementations below use adjacency lists based on chained forward stars. For details, see the [Graph Storage](./save.md) page.

=== "Pseudocode"
    ```text
    bfs(s) {
      q = new queue()
      q.push(s), visited[s] = true
      while (!q.empty()) {
        u = q.pop()
        for each edge(u, v) {
          if (!visited[v]) {
            q.push(v)
            visited[v] = true
          }
        }
      }
    }
    ```

=== "C++"
    ```cpp
    void bfs(int u) {
      while (!Q.empty()) Q.pop();
      Q.push(u);
      vis[u] = 1;
      d[u] = 0;
      p[u] = -1;
      while (!Q.empty()) {
        u = Q.front();
        Q.pop();
        for (int i = head[u]; i; i = e[i].nxt) {
          if (!vis[e[i].to]) {
            Q.push(e[i].to);
            vis[e[i].to] = 1;
            d[e[i].to] = d[u] + 1;
            p[e[i].to] = u;
          }
        }
      }
    }
    
    void restore(int x) {
      vector<int> res;
      for (int v = x; v != -1; v = p[v]) {
        res.push_back(v);
      }
      std::reverse(res.begin(), res.end());
      for (int i = 0; i < res.size(); ++i) printf("%d", res[i]);
      puts("");
    }
    ```

=== "Python"
    ```python
    from queue import Queue
    
    
    def bfs(u):
        Q = Queue()
        Q.put(u)
        vis[u] = True
        d[u] = 0
        p[u] = -1
        while Q.qsize() != 0:
            u = Q.get()
            i = head[u]
            while i:
                if vis[e[i].to] == False:
                    Q.put(e[i].to)
                    vis[e[i].to] = True
                    d[e[i].to] = d[u] + 1
                    p[e[i].to] = u
                i = e[i].nxt
    
    
    def restore(x):
        res = []
        v = x
        while v != -1:
            res.append(v)
            v = p[v]
        res.reverse()
        for i in range(0, len(res)):
            print(res[i])
    ```

Specifically, we use a queue `Q` to record nodes to be processed, and a boolean array `vis[]` to mark whether a node has been visited.

Initially, we set all nodes' `vis` values to 0, indicating they have not been visited, then add the start node `s` to queue `Q` and set `vis[s]` to 1.

Then, each time we take the node at the front of queue `Q` (call it `u`), and mark all nodes adjacent to `u` as visited and add them to queue `Q`.

Repeat until queue `Q` is empty, which indicates BFS is complete.

During BFS, we can also record additional information. In the code above, the `d` array records the shortest distance from the start node to any node (minimum number of edges), and the `p` array records which node we came from to reach the current node.

With the `d` array, we can easily get the distance from the start node to any node.

With the `p` array, we can easily reconstruct the shortest path from the start node to a node. The `restore` function in the code above uses this array to output all nodes on the shortest path from the start node to node `x`.

Time complexity: $O(n + m)$

Space complexity: $O(n)$ (`vis` array and queue)

## Open-Closed Table

When implementing BFS, we essentially place unvisited nodes in a container called "open", and visited nodes in a container called "closed".

## BFS on Trees/Graphs

### BFS Sequence

Similar to DFS sequence, a BFS sequence is the sequence of node numbers visited during BFS.

### BFS on General Graphs

If the original graph is disconnected, we can only reach nodes reachable from the start node.

BFS sequences are generally not unique.

Similarly, we can define a BFS tree: during BFS, by recording which node each node was visited from, we can build a tree structure, which is the BFS tree.

## Applications

-   Finding shortest paths from the start node to all other nodes in an unweighted graph.
-   Finding all connected components in $O(n+m)$ time. (We just start BFS from each unvisited node; each BFS will traverse one connected component)
-   If we view a game's actions as edges in a state graph (transitions), BFS can be used to find the minimum number of steps to reach one state from another.
-   Finding the minimum cycle in a directed unweighted graph. (Start BFS from each node; when we are about to reach a previously visited node, we have found a cycle. The minimum cycle of the graph is the average of the minimum cycles found in each BFS.)
-   Finding edges that must be on the $(a, b)$ shortest path. (Run BFS from both `a` and `b` to get two `d` arrays. For each edge $(u, v)$, if $d_a[u]+1+d_b[v]=d_a[b]$, then this edge is on a shortest path.)
-   Finding vertices that must be on the $(a, b)$ shortest path. (Run BFS from both `a` and `b` to get two `d` arrays. For each vertex `v`, if $d_a[v]+d_b[v]=d_a[b]$, then `v` is on some shortest path.)
-   Finding a shortest path of even length. (Construct a new graph by splitting each vertex into two new vertices. For each edge $(u, v)$ in the original graph, create edges $((u, 0), (v, 1))$ and $((u, 1), (v, 0))$. Run BFS on the new graph. The shortest path between $(s, 0)$ and $(t, 0)$ is the answer.)
-   Finding shortest paths on a graph with edge weights 0/1, see deque BFS below.

## Deque BFS

If you are not familiar with `deque`, see the [deque section](../lang/csl/sequence-container.md#deque).

Deque BFS is also known as 0-1 BFS.

### Scope

Applicable to shortest path problems where edge weights may or may not exist (since BFS is suitable for graphs with weight 1, the weights are typically 0 or 1), or can be transformed to this form.

For example, in a maze problem, you can either spend 1 coin to walk 5 steps, or walk 1 step for free. This can be solved with 0-1 BFS.

### Implementation

Normally, we place nodes reached via unweighted edges at the front of the deque, and nodes reached via weighted edges at the back. This ensures that the weights from the front to the back of the deque are monotonically non-decreasing, just like regular BFS.

Pseudocode:

```cpp
while (queue not empty) {
  int u = front;
  pop front;
  for (neighbors of u) {
    update data
    if (...)
      add to front;
    else
      add to back;
  }
}
```

### Example Problem

### [Codeforces 173B](http://codeforces.com/problemset/problem/173/B)

Given an $n \times m$ grid, a laser starts from the top-left corner heading right. Each time it encounters a '#', you can choose to shoot the laser in four directions, or do nothing. Find the minimum number of '#' that need to shoot in four directions so that the laser exits from the right side of row $n$.

The intended solution is not 0-1 BFS, but 0-1 BFS is applicable and reduces mental effort. Many top competitors used this approach during contests.

The approach is simple: shooting in one direction costs nothing (0), while shooting in four directions costs (1). Then just run the algorithm.

#### Code

```cpp
--8<-- "docs/graph/code/bfs/bfs_1.cpp"
```

## Priority Queue BFS

A priority queue is essentially a binary heap. STL provides [`std::priority_queue`](../lang/csl/container-adapter.md) for convenient priority queue usage.

In priority queue BFS, we always extract the node with the minimum cost from the front for further search. This greedy approach can be proven correct, because expanding from this node will never update nodes with higher costs. In other words, for the other nodes with higher costs, we will not consider updating them.

Of course, each node may be enqueued multiple times, each with a different cost. When a node is extracted from the priority queue for the first time, we don't need to search from that node again; we can simply ignore subsequent extractions. Therefore, in priority queue BFS, each node is processed exactly once.

Compared to regular queue BFS, the time complexity has an additional $\log n$ factor for maintaining the priority queue. However, regular BFS may enqueue and dequeue each node multiple times, giving $O(n^2)$ time complexity, not $O(n)$. So priority queue BFS is usually faster.

Hey? Doesn't this sound a lot like heap-optimized [Dijkstra](./shortest-path.md#dijkstra-algorithm)? Indeed, heap-optimized Dijkstra is essentially priority queue BFS.

## Practice Problems

-   [NOIP2017 Cheese](https://uoj.ac/problem/332)

Deque BFS:

-   [CF1063B Labyrinth](https://codeforces.com/problemset/problem/1063/B)
-   [CF173B Chamber of Secrets](https://codeforces.com/problemset/problem/173/B)
-   [BalticOI 2011 Day1 Switch the Lamp On](https://loj.ac/p/2632)

## References

<https://cp-algorithms.com/graph/breadth-first-search.html>
