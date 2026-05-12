author: du33169, lingkerio, Taoran-01

## Definitions

(Do you remember these definitions? Before reading the following content, please make sure you understand the basics in [Graph Theory Concepts](./concept.md).)

-   Path
-   Shortest path
-   Shortest path in directed graphs, shortest path in undirected graphs
-   Single-source shortest path, all-pairs shortest path

## Notation

For convenience, we first give the meaning of some notation used below.

-   $n$ is the number of nodes in the graph, $m$ is the number of edges;
-   $s$ is the source vertex for shortest paths;
-   $D(u)$ is the **actual** shortest path length from $s$ to $u$;
-   $dis(u)$ is the **estimated** shortest path length from $s$ to $u$. At any time, $dis(u) \geq D(u)$. In particular, when the shortest path algorithm terminates, we should have $dis(u) = D(u)$.
-   $w(u,v)$ is the weight of edge $(u,v)$.

## Properties

For a graph with positive edge weights, the shortest path between any two nodes does not contain repeated nodes.

For a graph with positive edge weights, the shortest path between any two nodes does not contain repeated edges.

For a graph with positive edge weights, in the shortest path between any two nodes, the number of nodes does not exceed $n$, and the number of edges does not exceed $n-1$.

## Floyd Algorithm

Used to find the shortest path between any two nodes.

The time complexity is relatively high, but the constant factor is small and it is easy to implement (only three `for` loops).

Applicable to any graph, whether directed or undirected, with positive or negative edge weights, but a shortest path must exist (no negative cycles).

### Implementation

We define an array `f[k][x][y]`, representing the shortest path length from node $x$ to node $y$ when only nodes $1$ to $k$ are allowed as intermediate nodes (that is, in the subgraph $V'={1, 2, \ldots, k}$, note that $x$ and $y$ are not necessarily in this subgraph).

Clearly, `f[n][x][y]` is the shortest path length from $x$ to $y$ (because $V'={1, 2, \ldots, n}$ equals $V$ itself, and its represented shortest path is the desired path).

Next, consider how to compute the values of the `f` array.

`f[0][x][y]`: the edge weight between $x$ and $y$, or $0$ if $x = y$, or $+\infty$ (when should `f[0][x][y]` be $+\infty$? When there is a directly connected edge between $x$ and $y$, it is their edge weight; when $x = y$, it is zero because the distance to itself is zero; when there is no direct edge between $x$ and $y$, it is $+\infty$).

`f[k][x][y] = min(f[k-1][x][y], f[k-1][x][k]+f[k-1][k][y])` (`f[k-1][x][y]` is the shortest path not passing through $k$, and `f[k-1][x][k]+f[k-1][k][y]` is the shortest path passing through $k`).

The above two statements are clearly correct. Therefore, the space complexity is $O(N^3)$. We increase the problem scale step by step ($k$ from $1$ to $n$) and check the shortest path between any two nodes under the current problem scale.

=== "C++"
    ```cpp
    for (k = 1; k <= n; k++) {
      for (x = 1; x <= n; x++) {
        for (y = 1; y <= n; y++) {
          f[k][x][y] = min(f[k - 1][x][y], f[k - 1][x][k] + f[k - 1][k][y]);
        }
      }
    }
    ```

=== "Python"
    ```python
    for k in range(1, n + 1):
        for x in range(1, n + 1):
            for y in range(1, n + 1):
                f[k][x][y] = min(f[k - 1][x][y], f[k - 1][x][k] + f[k - 1][k][y])
    ```

Since the first dimension has no effect on the result, we find that the first dimension of the array can be omitted. Therefore, we can directly change it to `f[x][y] = min(f[x][y], f[x][k]+f[k][y])`.

???+ note "Proof that the first dimension has no effect on the result"
    For a given `k`, when updating `f[k][x][y]`, the involved elements always come from row $k$ and column $k$ of the `f[k-1]` array. Then we notice that for a given `k`, when updating `f[k][k][y]` or `f[k][x][k]`, no value update ever occurs because according to the formula `f[k][k][y] = min(f[k-1][k][y], f[k-1][k][k]+f[k-1][k][y])`, `f[k-1][k][k]` is 0, so this value is always `f[k-1][k][y]`. The proof for `f[k][x][k]` is similar.
    
    Therefore, if we omit the first dimension, for a given `k`, no element used in updating any other element has been updated in this iteration. Hence, omitting the first dimension does not affect the result.

=== "C++"
    ```cpp
    for (k = 1; k <= n; k++) {
      for (x = 1; x <= n; x++) {
        for (y = 1; y <= n; y++) {
          f[x][y] = min(f[x][y], f[x][k] + f[k][y]);
        }
      }
    }
    ```

=== "Python"
    ```python
    for k in range(1, n + 1):
        for x in range(1, n + 1):
            for y in range(1, n + 1):
                f[x][y] = min(f[x][y], f[x][k] + f[k][y])
    ```

In summary, the time complexity is $O(N^3)$ and the space complexity is $O(N^2)$.

### Applications

???+ question "Given a positively weighted undirected graph, find a cycle with the minimum total weight."

    First, this must be a simple cycle.
    
    Think about how this cycle is formed.
    
    Consider the node $u$ with the largest index on the cycle.
    
    `f[u-1][x][y]` and $(u,x)$,$(u,y)$ together form the cycle.
    
    Enumerate $u$ during the Floyd process and compute the minimum of this sum.
    
    Time complexity is $O(n^3)$.
    
    See also the [Minimum Cycle](./min-cycle.md) section.

???+ question "Given a directed graph with edges between any two nodes, determine whether any two nodes are connected."
    This problem is finding the **transitive closure** of the graph.
    
    We only need to follow the Floyd process and add nodes one by one to check.
    
    Here the edge weights become $1/0$, and taking $\min$ becomes the **OR** operation.
    
    Further optimization with bitset can achieve $O(\frac{n^3}{w})$.
    
    ```cpp
    // std::bitset<SIZE> f[SIZE];
    for (k = 1; k <= n; k++)
      for (i = 1; i <= n; i++)
        if (f[i][k]) f[i] = f[i] | f[k];
    ```

## Bellman–Ford Algorithm

The Bellman–Ford algorithm is a shortest path algorithm based on the relax operation. It can find shortest paths in graphs with negative edge weights and can detect cases where no shortest path exists.

In the Chinese OI community, "SPFA" which you may have heard of is an implementation of the Bellman–Ford algorithm.

### Process

First, introduce the relax operation used by the Bellman–Ford algorithm (Dijkstra's algorithm also uses the relax operation).

For an edge $(u,v)$, the relax operation corresponds to the following formula: $dis(v) = \min(dis(v), dis(u) + w(u, v))$.

The meaning of this operation is clear: we try to use the path $S \to u \to v$ (where $S \to u$ takes the shortest path) to update the shortest path length to $v$. If this path is better, we update.

The Bellman–Ford algorithm does exactly this: it repeatedly attempts to relax every edge in the graph. After each iteration, we have attempted to relax all edges in the graph. The algorithm stops when no successful relaxation occurs in an iteration.

Each iteration is $O(m)$. So, what is the maximum number of iterations?

Assuming a shortest path exists, one relax operation increases the number of edges in the shortest path by at least $1$, and the maximum number of edges in a shortest path is $n-1$. Therefore, the entire algorithm executes at most $n-1$ rounds of relaxation. Hence, the total time complexity is $O(nm)$.

However, there is another case: if from the source $S$, we can reach a negative cycle, the relax operation will continue indefinitely. Note that the previous argument has already shown that for a graph where a shortest path exists, relax operations execute at most $n-1$ rounds. Therefore, if an edge can still be relaxed in the $n$-th round, it means that from $S$, we can reach a negative cycle.

???+ warning "Common misconceptions in negative cycle detection"
    Note that when running the Bellman–Ford algorithm with $S$ as the source, if it does not report a negative cycle, it only means that no negative cycle can be reached from $S$. It does not mean that there is no negative cycle in the graph.
    
    Therefore, if you need to check whether a negative cycle exists in the entire graph, the most rigorous approach is to create a super source, connect an edge of weight 0 to every node in the graph, and then run the Bellman–Ford algorithm with the super source as the starting point.

### Implementation

??? note "Reference Implementation"
    === "C++"
        ```cpp
        struct Edge {
          int u, v, w;
        };
        
        vector<Edge> edge;
        
        int dis[MAXN], u, v, w;
        constexpr int INF = 0x3f3f3f3f;
        
        bool bellmanford(int n, int s) {
          memset(dis, 0x3f, (n + 1) * sizeof(int));
          dis[s] = 0;
          bool flag = false;  // Flag to check if any relaxation occurred in this iteration
          for (int i = 1; i <= n; i++) {
            flag = false;
            for (int j = 0; j < edge.size(); j++) {
              u = edge[j].u, v = edge[j].v, w = edge[j].w;
              if (dis[u] == INF) continue;
              // Infinity plus/minus a constant is still infinity
              // Therefore, edges from a node with shortest path length INF cannot cause relaxation
              if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                flag = true;
              }
            }
            // Stop the algorithm when there are no edges that can be relaxed
            if (!flag) {
              break;
            }
          }
          // If relaxation can still occur in the n-th round, node s can reach a negative cycle
          return flag;
        }
        ```
    
    === "Python"
        ```python
        class Edge:
            def __init__(self, u=0, v=0, w=0):
                self.u = u
                self.v = v
                self.w = w
        
        
        INF = 0x3F3F3F3F
        edge = []
        
        
        def bellmanford(n, s):
            dis = [INF] * (n + 1)
            dis[s] = 0
            for i in range(1, n + 1):
                flag = False
                for e in edge:
                    u, v, w = e.u, e.v, e.w
                    if dis[u] == INF:
                        continue
                    # Infinity plus/minus a constant is still infinity
                    # Therefore, edges from a node with shortest path length INF cannot cause relaxation
                    if dis[v] > dis[u] + w:
                        dis[v] = dis[u] + w
                        flag = True
                # Stop the algorithm when there are no edges that can be relaxed
                if not flag:
                    break
            # If relaxation can still occur in the n-th round, node s can reach a negative cycle
            return flag
        ```

### Queue Optimization: SPFA

That is, Shortest Path Faster Algorithm.

Often, we don't need so many useless relaxation operations.

Clearly, only the edges connected from nodes that were just relaxed in the previous step can possibly cause the next relaxation operation.

So we use a queue to maintain "which nodes might cause relaxation operations," so that we only visit necessary edges.

SPFA can also be used to check whether node $s$ can reach a negative cycle. We only need to record how many edges the shortest path has traversed. When it has traversed at least $n$ edges, node $s$ can reach a negative cycle.

??? note "Implementation"
    === "C++"
        ```cpp
        struct edge {
          int v, w;
        };
        
        vector<edge> e[MAXN];
        int dis[MAXN], cnt[MAXN], vis[MAXN];
        queue<int> q;
        
        bool spfa(int n, int s) {
          memset(dis, 0x3f, (n + 1) * sizeof(int));
          dis[s] = 0, vis[s] = 1;
          q.push(s);
          while (!q.empty()) {
            int u = q.front();
            q.pop(), vis[u] = 0;
            for (auto ed : e[u]) {
              int v = ed.v, w = ed.w;
              if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;  // Record the number of edges in the shortest path
                if (cnt[v] >= n) return false;
                // Without passing through a negative cycle, the shortest path traverses at most n - 1 edges
                // Therefore, if it traverses more than n edges, it must have passed through a negative cycle
                if (!vis[v]) q.push(v), vis[v] = 1;
              }
            }
          }
          return true;
        }
        ```
    
    === "Python"
        ```python
        from collections import deque
        
        
        class Edge:
            def __init__(self, v=0, w=0):
                self.v = v
                self.w = w
        
        
        e = [[Edge() for i in range(MAXN)] for j in range(MAXN)]
        INF = 0x3F3F3F3F
        
        
        def spfa(n, s):
            dis = [INF] * (n + 1)
            cnt = [0] * (n + 1)
            vis = [False] * (n + 1)
            q = deque()
        
            dis[s] = 0
            vis[s] = True
            q.append(s)
            while q:
                u = q.popleft()
                vis[u] = False
                for ed in e[u]:
                    v, w = ed.v, ed.w
                    if dis[v] > dis[u] + w:
                        dis[v] = dis[u] + w
                        cnt[v] = cnt[u] + 1  # Record the number of edges in the shortest path
                        if cnt[v] >= n:
                            return False
                        # Without passing through a negative cycle, the shortest path traverses at most n - 1 edges
                        # Therefore, if it traverses more than n edges, it must have passed through a negative cycle
                        if not vis[v]:
                            q.append(v)
                            vis[v] = True
        ```

Although SPFA runs fast in most cases, its worst-case time complexity is $O(nm)$. It is not difficult to construct data that reaches this complexity. Therefore, use it with caution in contests (when there are no negative weight edges, it is best to use Dijkstra's algorithm; when there are negative weight edges and the graph has no special properties, if SPFA is part of the intended solution, the problem should not give data ranges that Bellman–Ford cannot handle).

???+ note "Other optimizations for Bellman–Ford"
    Besides queue optimization (SPFA), Bellman–Ford has other forms of optimization, which are effective on some graphs but may reach exponential worst-case complexity on certain special graphs.
    
    -   Heap optimization: Replace the queue with a heap. Unlike Dijkstra's, it allows a node to be enqueued multiple times. On graphs with negative edge weights, it may be reduced to exponential complexity.
    -   Stack optimization: Replace the queue with a stack (changing the original BFS process to DFS). It may be more efficient when finding negative cycles, but the worst time complexity is still exponential.
    -   LLL optimization: Replace the regular queue with a deque. Compare each enqueued node's distance with the average distance of nodes in the queue; if larger, insert at the tail, otherwise insert at the head.
    -   SLF optimization: Replace the regular queue with a deque. Compare each enqueued node's distance with the front of the queue; if larger, insert at the tail, otherwise insert at the head.
    -   D'Esopo–Pape algorithm: Replace the regular queue with a deque. If a node has not been enqueued before, insert it at the tail; otherwise, insert it at the head.
    
    For more optimizations and hacks against them, see [fstqwq's answer on Zhihu](https://www.zhihu.com/question/292283275/answer/484871888).

## Dijkstra Algorithm

Dijkstra's algorithm (/ˈdikstrɑ/ or /ˈdɛikstrɑ/) was discovered by Dutch computer scientist E. W. Dijkstra in 1956 and published in 1959. It is an algorithm for solving single-source shortest paths on **non-negative weight graphs**.

### Process

Divide nodes into two sets: the set of nodes with determined shortest path lengths (denoted as set $S$) and the set of nodes with undetermined shortest path lengths (denoted as set $T$). Initially, all nodes belong to set $T$.

Initialize $dis(s) = 0$, and $dis$ for all other nodes is $+\infty$.

Then repeat these operations:

1.  From set $T$, select the node with the smallest shortest path length and move it to set $S$.
2.  Perform relax operations on all outgoing edges of the node just added to set $S$.

Repeat until set $T$ is empty, at which point the algorithm ends.

### Time Complexity

The naive implementation is to directly search for the node with the smallest shortest path length in set $T$ after each step 2 operation. The total time complexity of step 2 is $O(m)$, and step 1 is $O(n^2)$. The overall time complexity is $O(n^2 + m) = O(n^2)$.

We can optimize this process using a heap: each time an edge $(u,v)$ is successfully relaxed, insert $v$ into the heap (if $v$ is already in the heap, perform Decrease-key directly). Step 1 is simply taking the top node from the heap. There are $O(m)$ Decrease-key operations and $O(n)$ pop operations. Different heaps give different complexities. See the [Heap](../ds/heap.md) page for reference. The optimal complexity achievable with heap optimization is $O(n\log n + m)$. Fibonacci heaps and similar data structures can achieve this complexity.

In particular, a priority queue can be used. At this time, the Decrease-key operation cannot be performed, but we can re-insert the node each time it is relaxed and check during popping whether the node has already been relaxed; if so, skip it. The complexity is $O(m\log n)$, and the advantage is relatively simple implementation.

The heap here can also be implemented with a segment tree, with complexity $O(m\log n)$. With some special non-recursive segment tree implementations, this approach has a smaller constant factor than the heap. Moreover, segment trees support more operations, and in some special graph problems, only segment trees can maintain the data.

In sparse graphs where $m = O(n)$, the heap-optimized Dijkstra algorithm has a significant efficiency advantage; in dense graphs where $m = O(n^2)$, the naive implementation is better.

### Correctness Proof

We prove the correctness of Dijkstra's algorithm under the premise that **all edge weights are non-negative** using mathematical induction[^1].

Simply put, what we need to prove is that during step 1, the node $u$ being removed has its shortest path already determined, i.e., $D(u) = dis(u)$.

Initially, $S = \varnothing$, and the assumption holds.

Now, we use proof by contradiction.

Let $u$ be the first node in the algorithm that does not satisfy $D(u) = dis(u)$ when it is added to set $S$. Since the source $s$ must satisfy $D(s) = dis(s) = 0$ and is definitely the first node added to set $S$, before $u$ is added to set $S$, we have $S \ne \varnothing$. If there is no path from $s$ to $u$, then $D(u) = dis(u) = +\infty$, contradicting the assumption.

Therefore, a path $s \to x \to y \to u$ must exist, where $y$ is the first node on the $s \to u$ path that belongs to set $T$, and $x$ is the predecessor of $y$ (clearly $x \in S$). Note that it is possible that $s = x$ or $y = u$, i.e., $s \to x$ or $y \to u$ may be an empty path.

Since all nodes added to set $S$ before $u$ satisfy $D(u) = dis(u)$, when node $x$ is added to set $S$, we have $D(x) = dis(x)$. At this time, edge $(x,y)$ will be relaxed, so when $u$ is added to set $S$, we must have $D(y) = dis(y)$.

Next, we prove $D(u) = dis(u)$ holds. On the path $s \to x \to y \to u$, since all edge weights in the graph are non-negative, $D(y) \leq D(u)$. Thus $dis(y) = D(y) \leq D(u) \leq dis(u)$. However, when node $u$ is removed from set $T$ in step 1, node $y$ has not yet been removed from set $T$. Therefore, at this time, $dis(u) \leq dis(y)$. Combining with the previous inequality, we get $dis(y) = D(y) = D(u) = dis(u)$, which contradicts the assumption $D(u) \neq dis(u)$. Hence, the assumption does not hold.

Therefore, we have proven that in step 1, the shortest path of every node taken out has already been determined. The proposition is proven.

Note that the key inequality $D(y) \leq D(u)$ in the proof relies on the condition that all edge weights in the graph are non-negative. When the graph contains negative-weight edges, this inequality no longer holds, the correctness of Dijkstra's algorithm cannot be guaranteed, and the algorithm may produce incorrect results.

### Implementation

Here we give both the $O(n^2)$ brute-force implementation and the $O(m \log m)$ priority queue implementation.

???+ note "Naive Implementation"
    === "C++"
        ```cpp
        struct edge {
          int v, w;
        };
        
        vector<edge> e[MAXN];
        int dis[MAXN], vis[MAXN];
        
        void dijkstra(int n, int s) {
          memset(dis, 0x3f, (n + 1) * sizeof(int));
          dis[s] = 0;
          for (int i = 1; i <= n; i++) {
            int u = 0, mind = 0x3f3f3f3f;
            for (int j = 1; j <= n; j++)
              if (!vis[j] && dis[j] < mind) u = j, mind = dis[j];
            vis[u] = true;
            for (auto ed : e[u]) {
              int v = ed.v, w = ed.w;
              if (dis[v] > dis[u] + w) dis[v] = dis[u] + w;
            }
          }
        }
        ```
    
    === "Python"
        ```python
        class Edge:
            def __init(self, v=0, w=0):
                self.v = v
                self.w = w
        
        
        e = [[Edge() for i in range(MAXN)] for j in range(MAXN)]
        INF = 0x3F3F3F3F
        
        
        def dijkstra(n, s):
            dis = [INF] * (n + 1)
            vis = [0] * (n + 1)
        
            dis[s] = 0
            for i in range(1, n + 1):
                u = 0
                mind = INF
                for j in range(1, n + 1):
                    if not vis[j] and dis[j] < mind:
                        u = j
                        mind = dis[j]
                vis[u] = True
                for ed in e[u]:
                    v, w = ed.v, ed.w
                    if dis[v] > dis[u] + w:
                        dis[v] = dis[u] + w
        ```

???+ note "Priority Queue Implementation"
    === "C++"
        ```cpp
        struct edge {
          int v, w;
        };
        
        struct node {
          int dis, u;
        
          bool operator>(const node& a) const { return dis > a.dis; }
        };
        
        vector<edge> e[MAXN];
        int dis[MAXN], vis[MAXN];
        priority_queue<node, vector<node>, greater<node>> q;
        
        void dijkstra(int n, int s) {
          memset(dis, 0x3f, (n + 1) * sizeof(int));
          memset(vis, 0, (n + 1) * sizeof(int));
          dis[s] = 0;
          q.push({0, s});
          while (!q.empty()) {
            int u = q.top().u;
            q.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            for (auto ed : e[u]) {
              int v = ed.v, w = ed.w;
              if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push({dis[v], v});
              }
            }
          }
        }
        ```
    
    === "Python"
        ```python
        def dijkstra(e, s):
            """
            Input:
            e: adjacency list
            s: source node
            Returns:
            dis: shortest path length from s to each vertex
            """
            dis = defaultdict(lambda: float("inf"))
            dis[s] = 0
            q = [(0, s)]
            vis = set()
            while q:
                _, u = heapq.heappop(q)
                if u in vis:
                    continue
                vis.add(u)
                for v, w in e[u]:
                    if dis[v] > dis[u] + w:
                        dis[v] = dis[u] + w
                        heapq.heappush(q, (dis[v], v))
            return dis
        ```

## Johnson All-Pairs Shortest Path Algorithm

Like Floyd's algorithm, Johnson's algorithm can find the shortest path between any two nodes in a graph without negative cycles. This algorithm was proposed by Donald B. Johnson in 1977.

The shortest path between any two nodes can be found by enumerating each source vertex and running Bellman–Ford $n$ times, with time complexity $O(n^2m)$. Alternatively, Floyd's algorithm can be used directly, with time complexity $O(n^3)$.

Note that the heap-optimized Dijkstra algorithm for single-source shortest paths has better time complexity than Bellman–Ford. If we enumerate each source vertex and run Dijkstra $n$ times, the problem can be solved in $O(nm\log m)$ (depending on the implementation of Dijkstra's algorithm), which is better than running Bellman–Ford $n$ times and is also better than Floyd's algorithm on sparse graphs.

However, Dijkstra's algorithm cannot correctly solve shortest paths with negative-weight edges. Therefore, we need to preprocess the edges of the original graph to ensure all edge weights are non-negative.

One naive approach is to add the same positive number $x$ to all edge weights, making all edge weights non-negative. If the shortest path from the source to the destination in the new graph traverses $k$ edges, we can subtract $kx$ from the shortest path to get the actual shortest path.

But this approach is incorrect. Consider the following graph:

![](./images/shortest-path1.svg)

The shortest path from $1 \to 2$ is $1 \to 5 \to 3 \to 2$ with length $-2$.

But what if we add $5$ to the weight of each edge?

![](./images/shortest-path2.svg)

In the new graph, the shortest path from $1 \to 2$ is $1 \to 4 \to 2$, which is no longer the actual shortest path.

Johnson's algorithm reweights edges using a different method.

We create a new virtual node (let's say its number is $0$). Draw an edge of weight $0$ from this node to all other nodes.

Then use the Bellman–Ford algorithm to find the shortest path from node $0$ to all other nodes, and denote it as $h_i$.

If there is an edge from node $u$ to node $v$ with weight $w$, we reset the edge weight to $w + h_u - h_v$.

Now, run Dijkstra's algorithm $n$ times with each node as the source to find the shortest path between any two nodes.

The initial Bellman–Ford algorithm is not the time bottleneck. If Dijkstra's algorithm is implemented using `priority_queue`, the time complexity of this algorithm is $O(nm\log m)$.

### Correctness Proof

Why is this edge reweighting method correct?

Before discussing this, let's first discuss a physical concept — potential energy.

Both gravitational potential energy and electric potential energy share a characteristic: the change in potential energy depends only on the relative positions of the start and end points, not on the path taken from the start to the end.

Potential energy also has a characteristic: the absolute value of potential energy often depends on the location of the zero potential point, but regardless of where the zero potential point is set, the difference in potential energy between two points is fixed.

Now, back to the main topic.

On the relabeled graph, the length of a path $s \to p_1 \to p_2 \to \dots \to p_k \to t$ from node $s$ to node $t$ is expressed as follows:

$(w(s,p_1)+h_s-h_{p_1})+(w(p_1,p_2)+h_{p_1}-h_{p_2})+ \dots +(w(p_k,t)+h_{p_k}-h_t)$

After simplification, we get:

$w(s,p_1)+w(p_1,p_2)+ \dots +w(p_k,t)+h_s-h_t$

Regardless of which path we take from $s$ to $t$, the value of $h_s - h_t$ does not change. This perfectly matches the property of potential energy!

For convenience, we refer to $h_i$ as the potential energy of node $i$.

In the new graph, the length of the shortest path from $s$ to $t$ consists of two parts: the sum of edge weights in front is the shortest path from $s$ to $t$ in the original graph, and the latter part is the potential difference between the two nodes. Since the potential difference between two nodes is constant, the shortest path from $s$ to $t$ in the original graph corresponds to the shortest path from $s$ to $t$ in the new graph.

At this point, half of the correctness proof is resolved — we have proven that the shortest path in the new graph is still the original shortest path. Next, we need to prove that all edge weights in the new graph are non-negative because Dijkstra's algorithm guarantees correct results on non-negative weight graphs.

According to the triangle inequality, for any edge $(u,v)$ in the graph, the two endpoints satisfy: $h_v \leq h_u + w(u,v)$. The reweighted edge weight is $w'(u,v) = w(u,v) + h_u - h_v \geq 0$. Thus, we have proven that all edge weights in the new graph are non-negative.

With this, we have proven the correctness of Johnson's algorithm.

## Comparison of Different Methods

| Shortest Path Algorithm | Floyd       | Bellman–Ford | Dijkstra     | Johnson        |
| ---------------------- | ----------- | ------------ | ------------ | -------------- |
| Path Type              | All-pairs   | Single-source | Single-source | All-pairs       |
| Applicable to          | Any graph   | Any graph    | Non-negative | Any graph       |
| Can detect negative cycle? | Yes      | Yes          | No           | Yes             |
| Time Complexity        | $O(N^3)$    | $O(NM)$      | $O(M\log M)$ | $O(NM\log M)$  |

Note: The Dijkstra algorithm in the table uses `priority_queue` implementation for complexity calculation.

## Outputting the Path

Maintain a `pre` array during distance updates to record how the next node is reached. Before the algorithm finishes, output the path recursively.

For example, in Floyd's algorithm, record `pre[i][j] = k`; for Bellman–Ford and Dijkstra, generally record `pre[v] = u`.

## Special Cases

-   Shortest path in graphs where edge weights are only $0$ and $1$: [0-1 BFS](./bfs.md#deque-bfs);
-   Shortest path problems allowing at most $k$ changes in path cost or similar operations: [Layered Graph Shortest Path](./node.md#layered-graph-shortest-path).

## References and Notes

[^1]: *Introduction to Algorithms (3rd Edition Chinese Translation)*, Mechanical Industry Press, 2013, pp. 384-385.
