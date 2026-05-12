author: Chrogeek, Enter-tainer, HeRaNO, Ir1d, Marcythm, ShadowsEpic, StudyingFather, Xeonacid, bear-good, billchenchina, diauweb, diauweb, greyqz, kawa-yoiko, ouuan, partychicken, sshwy, stevebraveman, zhouyuyang2002, renbaoshuo, Hszzzx, y-kx-b, toprise

## Definition

Before reading the following content, please be sure to read the [Graph Theory Concepts](./concept.md) and [Tree Basics](./tree-basic.md) sections, and understand the following definitions:

1. Spanning Subgraph
2. Spanning Tree

We define the **Minimum Spanning Tree** (MST) of an undirected connected graph as the spanning tree with the minimum total edge weight.

Note: Only connected graphs have spanning trees; for disconnected graphs, only spanning forests exist.

## Kruskal's Algorithm

Kruskal's algorithm is a common and easy-to-implement minimum spanning tree algorithm, invented by Kruskal. The basic idea is to add edges in increasing order of weight, which is a greedy algorithm.

### Prerequisites

[Disjoint Set Union (Union-Find)](../ds/dsu.md), [Greedy](../basic/greedy.md), [Graph Storage](./save.md).

### Implementation

Illustration:

![](./images/mst-2.apng)

Pseudocode:

<!--
```pseudo
\begin{algorithm}
\caption{Kruskal}
\begin{algorithmic}
\INPUT{ The edges of the graph $e$ where each element in $e$ is $(u, v, w)$ denoting that there is an edge between $u$ and $v$ weighted $w$. }
\OUTPUT The edges of the MST of the input graph
\STATE $result \gets \varnothing$
\STATE sort $e$ into nondecreasing order by weight $w$
\FOR{each $(u, v, w)$ in the sorted $e$}
    \IF{$u$ \AND $v$ are not connected in the union-find set}
        \STATE connect $u$ \AND $v$ in the union-find set
        \STATE $result \gets result \bigcup (u, v, w)$
    \ENDIF
\ENDFOR
\RETURN $result$
\end{algorithmic}
\end{algorithm}
```
-->

$$
\begin{array}{ll}
1 &  \textbf{Input. } \text{The edges of the graph } e , \text{ where each element in } e \text{ is } (u, v, w) \\
  &  \text{ denoting that there is an edge between } u \text{ and } v \text{ weighted } w . \\
2 &  \textbf{Output. } \text{The edges of the MST of the input graph}.\\
3 &  \textbf{Method. } \\ 
4 &  result \gets \varnothing \\
5 &  \text{sort } e \text{ into nondecreasing order by weight } w \\ 
6 &  \textbf{for} \text{ each } (u, v, w) \text{ in the sorted } e \\ 
7 &  \qquad \textbf{if } u \text{ and } v \text{ are not connected in the union-find set } \\
8 &  \qquad\qquad \text{connect } u \text{ and } v \text{ in the union-find set} \\
9 &  \qquad\qquad  result \gets result\;\bigcup\ \{(u, v, w)\} \\
10 &  \textbf{return }  result
\end{array}
$$

Although the algorithm is simple, it requires appropriate data structures to support it... Specifically, maintain a forest, query whether two nodes are in the same tree, and connect two trees.

More abstractly, maintain a bunch of **sets**, query whether two elements belong to the same set, and merge two sets.

Among these, checking whether two points are connected and connecting two points can be maintained using a disjoint set union.

If we use a sorting algorithm with $O(m\log m)$ complexity and a disjoint set union with $O(m\alpha(m, n))$ or $O(m\log n)$ complexity, we can obtain a Kruskal's algorithm with time complexity $O(m\log m)$.

### Proof

The idea is simple: to construct a minimum spanning tree, we start from the edge with the smallest weight, and add edges in increasing order of weight. If adding an edge creates a cycle, we discard this edge. We continue until we have added $n-1$ edges, forming a tree.

Proof: Use induction to prove that at any time, the set of edges chosen by Kruskal's algorithm is contained in some MST.

Base case: At the beginning of the algorithm, it obviously holds (the minimum spanning tree exists).

Induction: Assume it holds at some moment, with the current edge set being $F$, and let $T$ be this MST. Consider the next edge $e$ to be added.

If $e$ belongs to $T$, then it holds.

Otherwise, $T+e$ must contain a cycle. Consider another edge $f$ on this cycle that does not belong to $F$ (at least one such edge exists).

First, $f$'s weight cannot be smaller than $e$'s, otherwise $f$ would have been chosen before $e$.

Second, $f$'s weight cannot be larger than $e$'s, otherwise $T+e-f$ would be a spanning tree better than $T$.

Therefore, $T+e-f$ contains $F$ and is also a minimum spanning tree, completing the induction.

### Example Problem

???+ note "[Luogu P1195 Sky in Pocket](https://www.luogu.com.cn/problem/P1195)"
    There are $n$ clouds that you need to connect into $k$ marshmallows. Connecting cloud $X_i$ and cloud $Y_i$ costs $L_i$. Find the minimum cost.

??? note "Example Code"
    === "C++"
        ```cpp
        --8<-- "docs/graph/code/mst/mst_3.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/graph/code/mst/mst_3.py"
        ```
    
    === "Java"
        ```java
        --8<-- "docs/graph/code/mst/mst_3.java"
        ```

## Prim's Algorithm

Prim's algorithm is another common and easy-to-implement minimum spanning tree algorithm. Its basic idea is to start from a node and continuously add nodes (instead of adding edges like Kruskal's algorithm).

### Implementation

Illustration:

![](./images/mst-3.apng)

Specifically, each time we select a node with the minimum distance and use the new edge to update the distances of other nodes.

In fact, it's the same as Dijkstra's algorithm: each time find the node with the minimum distance. We can find it by brute force or maintain it with a heap.

The heap-optimized approach is similar to Dijkstra's heap optimization. However, if using a binary heap or other heaps that do not support $O(1)$ decrease-key, the complexity is not better than Kruskal's, and the constant factor is larger than Kruskal's. Therefore, Kruskal's algorithm is generally used. For dense graphs, especially complete graphs, brute-force Prim's complexity is better than Kruskal's, but it is **not necessarily** faster in practice.

Brute force: $O(n^2+m)$.

Binary heap: $O((n+m) \log n)$.

Fibonacci heap: $O(n \log n + m)$.

Pseudocode:

$$
\begin{array}{ll}
1 &  \textbf{Input. } \text{The nodes of the graph }V\text{ ; the function }g(u, v)\text{ which}\\
  &  \text{means the weight of the edge }(u, v)\text{; the function }adj(v)\text{ which}\\
  &  \text{means the nodes adjacent to }v.\\
2 &  \textbf{Output. } \text{The sum of weights of the MST of the input graph.} \\
3 &  \textbf{Method.} \\
4 &  result \gets 0 \\
5 & \text{choose an arbitrary node in }V\text{ to be the }root \\
6 &  dis(root)\gets 0 \\
7 &  \textbf{for } \text{each node }v\in(V-\{root\}) \\
8 &  \qquad  dis(v)\gets\infty \\
9 &  rest\gets V \\
10 &  \textbf{while }  rest\ne\varnothing \\
11 &  \qquad cur\gets \text{the node with the minimum }dis\text{ in }rest \\
12 &  \qquad  result\gets result+dis(cur) \\
13 &  \qquad  rest\gets rest-\{cur\} \\
14 &  \qquad  \textbf{for}\text{ each node }v\in adj(cur) \\
15 &  \qquad\qquad  dis(v)\gets\min(dis(v), g(cur, v)) \\
16 &  \textbf{return }  result 
\end{array}
$$

Note: The above code only computes the total weight of the minimum spanning tree. To output the solution, we also need to record which edge each node's $dis$ represents.

??? note "Code Implementation"
    ```cpp
    // Prim's algorithm with binary heap optimization
    #include <cstring>
    #include <iostream>
    #include <queue>
    using namespace std;
    constexpr int N = 5050, M = 2e5 + 10;
    
    struct E {
      int v, w, x;
    } e[M * 2];
    
    int n, m, h[N], cnte;
    
    void adde(int u, int v, int w) { e[++cnte] = E{v, w, h[u]}, h[u] = cnte; }
    
    struct S {
      int u, d;
    };
    
    bool operator<(const S &x, const S &y) { return x.d > y.d; }
    
    priority_queue<S> q;
    int dis[N];
    bool vis[N];
    
    int res = 0, cnt = 0;
    
    void Prim() {
      memset(dis, 0x3f, sizeof(dis));
      dis[1] = 0;
      q.push({1, 0});
      while (!q.empty()) {
        if (cnt >= n) break;
        int u = q.top().u, d = q.top().d;
        q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        ++cnt;
        res += d;
        for (int i = h[u]; i; i = e[i].x) {
          int v = e[i].v, w = e[i].w;
          if (w < dis[v]) {
            dis[v] = w, q.push({v, w});
          }
        }
      }
    }
    
    int main() {
      cin >> n >> m;
      for (int i = 1, u, v, w; i <= m; ++i) {
        cin >> u >> v >> w, adde(u, v, w), adde(v, u, w);
      }
      Prim();
      if (cnt == n)
        cout << res;
      else
        cout << "No MST.";
      return 0;
    }
    ```

### Proof

Starting from any node, divide nodes into two categories: added and not added.

Each time, from the nodes not yet added, find the node with the minimum edge weight to the set of added nodes.

Then add this node and connect it with the edge of minimum weight.

Repeat $n-1$ times.

Proof: As before, we show that at each step, there exists a minimum spanning tree containing the selected edge set.

Base case: When there is only one node, it obviously holds.

Induction: If it holds at some step, with the current edge set being $F$, belonging to the MST $T$. Now we want to add edge $e$.

If $e$ belongs to $T$, then it holds.

Otherwise, consider another edge $f$ on the cycle in $T+e$ that can be added to the current edge set.

First, $f$'s weight is not less than $e$'s weight; otherwise $f$ would have been chosen instead of $e$.

Then, $f$'s weight is not greater than $e$'s weight; otherwise $T+e-f$ would be a smaller spanning tree.

Therefore, $e$ and $f$ have equal weights, and $T+e-f$ is also a minimum spanning tree and contains $F$.

## Boruvka's Algorithm

Next, we introduce another algorithm for solving the minimum spanning tree—Boruvka's algorithm. This algorithm combines the ideas of the first two algorithms. It can be used to find the minimum spanning forest of an undirected graph. (For an undirected connected graph, this is the minimum spanning tree.)

In problems where edges have special properties, Boruvka's algorithm has advantages. For example, the complete graph problem in [CF888G](https://codeforces.com/problemset/problem/888/G).

To describe this algorithm, we need to introduce some definitions:

1. Define $E'$ as the edges of the minimum spanning forest we have found so far. During the execution of the algorithm, we gradually add edges to $E'$. Define a **connected component** as a set of vertices $V' \subseteq V$ such that any two vertices $u, v$ in this set are connected (mutually reachable) in the subgraph formed by edges in $E'$.
2. Define the **minimum edge** of a connected component as the edge connecting it to another connected component with the smallest weight.

Initially, $E' = \varnothing$, and each vertex is its own connected component:

1. Determine which connected component each vertex belongs to. Set each connected component to have "no minimum edge".
2. Iterate through each edge $(u, v)$. If $u$ and $v$ are not in the same connected component, use this edge's weight to update the minimum edge for $u$'s and $v$'s connected components respectively.
3. If all connected components have no minimum edge, exit the program. At this point, $E'$ is the edge set of the minimum spanning forest of the original graph. Otherwise, add the minimum edge of each connected component that has one to $E'$, and return to step 1.

Below is an example with a dynamic illustration (image from [Wikipedia](https://en.wikipedia.org/wiki/Bor%C5%AFvka%27s_algorithm)):

![eg](./images/mst-1.apng)

When the original graph is connected, the number of connected components at least halves each iteration, so the algorithm iterates at most $O(\log V)$ times. When the original graph is disconnected, it corresponds to multiple subproblems. Therefore, the algorithm's complexity is $O(E \log V)$. The pseudocode of the algorithm is given below (modified from [Wikipedia](https://en.wikipedia.org/wiki/Bor%C5%AFvka%27s_algorithm)):

$$
\begin{array}{ll}
1 &  \textbf{Input. } \text{A graph }G\text{ whose edges have distinct weights. } \\
2 &  \textbf{Output. } \text{The minimum spanning forest of }G .  \\
3 &  \textbf{Method. }  \\
4 & \text{Initialize a forest }F\text{ to be a set of one-vertex trees} \\
5 &  \textbf{while } \text{True} \\
6 &  \qquad \text{Find the components of }F\text{ and label each vertex of }G\text{ by its component } \\
7 &  \qquad \text{Initialize the cheapest edge for each component to "None"} \\
8 &  \qquad  \textbf{for } \text{each edge }(u, v)\text{ of }G  \\
9 &  \qquad\qquad  \textbf{if }  u\text{ and }v\text{ have different component labels} \\
10 &  \qquad\qquad\qquad  \textbf{if }  (u, v)\text{ is cheaper than the cheapest edge for the component of }u  \\
11 &  \qquad\qquad\qquad\qquad\text{ Set }(u, v)\text{ as the cheapest edge for the component of }u \\
12 &  \qquad\qquad\qquad  \textbf{if }  (u, v)\text{ is cheaper than the cheapest edge for the component of }v  \\
13 &  \qquad\qquad\qquad\qquad\text{ Set }(u, v)\text{ as the cheapest edge for the component of }v  \\
14 &  \qquad  \textbf{if }\text{ all components'cheapest edges are "None"} \\
15 &  \qquad\qquad  \textbf{return }  F \\
16 &  \qquad  \textbf{for }\text{ each component whose cheapest edge is not "None"} \\
17 &  \qquad\qquad\text{ Add its cheapest edge to }F \\
\end{array}
$$

Note that comparing edges usually requires a secondary key (e.g., sorting by edge index) to distinguish edges when they have the same weight.

## Exercises

-   [「HAOI2006」Smart Monkeys](https://www.luogu.com.cn/problem/P2504)
-   [「SCOI2005」Busy City](https://loj.ac/problem/2149)

## Uniqueness of Minimum Spanning Tree

Consider the uniqueness of the minimum spanning tree. If an edge is **not in the minimum spanning tree's edge set** and can replace another edge **with equal weight that is in the minimum spanning tree edge set**, then this minimum spanning tree is not unique.

For Kruskal's algorithm, we only need to count how many edges of the current weight can be placed and how many are actually placed. If these two values are different, it indicates that these edges form a cycle with previous edges (this cycle must contain at least two edges of the current weight; otherwise, according to the union-find set, this edge cannot be placed). This means the minimum spanning tree is not unique.

To find edges with the same weight as the current edge, we only need to record head and tail pointers and use a monotonic queue to solve this problem with $O(\alpha(m))$ time complexity (where m is the number of edges), which is excellent (basically the same as the original algorithm's time).

??? note "Example: [POJ 1679](http://poj.org/problem?id=1679)"
    ```cpp
    --8<-- "docs/graph/code/mst/mst_1.cpp"
    ```

## Second Minimum Spanning Tree

### Non-Strict Second Minimum Spanning Tree

#### Definition

In an undirected graph, the spanning tree with the minimum total edge weight such that the total weight is **greater than or equal to** the weight of the minimum spanning tree.

#### Solution Method

-   Find the minimum spanning tree $T$ of the undirected graph, and let its total weight be $M$.
-   Iterate through each unselected edge $e = (u, v, w)$, find the edge with maximum weight $e' = (s, t, w')$ on the path from $u$ to $v$ in $T$. Then, by replacing $e'$ with $e$ in $T$, we can obtain a spanning tree $T'$ with total weight $M' = M + w - w'$.
-   Take the minimum value among all $M'$ obtained from replacements.

How to find the maximum edge weight on the path between $u$ and $v$?

We can use binary lifting to maintain, preprocessing each node's $2^i$-th ancestor and the maximum edge weight on the path to its $2^i$-th ancestor. This allows us to directly compute it during the LCA process with binary lifting.

### Strict Second Minimum Spanning Tree

#### Definition

In an undirected graph, the spanning tree with the minimum total edge weight such that the total weight is **strictly greater than** the weight of the minimum spanning tree.

#### Solution Method

Consider the non-strict second minimum spanning tree solution process. Why is the solution obtained non-strict?

Because the minimum spanning tree guarantees that the maximum edge weight on the path between $u$ and $v$ in the tree is **not greater than** the maximum edge weight on any other path from $u$ to $v$. In other words, when the edge used for replacement has the same weight as the edge being replaced in the original tree, the obtained second minimum spanning tree is non-strict.

The solution is natural: while maintaining the maximum edge weight on the path to the $2^i$-th ancestor, also maintain the **strictly second maximum** edge weight. When the edge used for replacement has the same weight as the maximum edge weight on the path in the original tree, we use the strictly second maximum value for replacement.

This process can be solved with binary lifting, with complexity $O(m \log m)$.

??? note "Code Implementation"
    ```cpp
    #include <algorithm>
    #include <iostream>
    
    constexpr int INF = 0x3fffffff;
    constexpr long long INF64 = 0x3fffffffffffffffLL;
    
    struct Edge {
      int u, v, val;
    
      bool operator<(const Edge &other) const { return val < other.val; }
    };
    
    Edge e[300010];
    bool used[300010];
    
    int n, m;
    long long sum;
    
    class Tr {
     private:
      struct Edge {
        int to, nxt, val;
      } e[600010];
    
      int cnt, head[100010];
    
      int pnt[100010][22];
      int dpth[100010];
      // Maximum edge weight on the path to the ancestor
      int maxx[100010][22];
      // Strictly second maximum edge weight on the path to the ancestor, -INF if none
      int minn[100010][22];
    
     public:
      void addedge(int u, int v, int val) {
        e[++cnt] = Edge{v, head[u], val};
        head[u] = cnt;
      }
    
      void insedge(int u, int v, int val) {
        addedge(u, v, val);
        addedge(v, u, val);
      }
    
      void dfs(int now, int fa) {
        dpth[now] = dpth[fa] + 1;
        pnt[now][0] = fa;
        minn[now][0] = -INF;
        for (int i = 1; (1 << i) <= dpth[now]; i++) {
          pnt[now][i] = pnt[pnt[now][i - 1]][i - 1];
          int kk[4] = {maxx[now][i - 1], maxx[pnt[now][i - 1]][i - 1],
                       minn[now][i - 1], minn[pnt[now][i - 1]][i - 1]};
          // Get the maximum value from four values
          std::sort(kk, kk + 4);
          maxx[now][i] = kk[3];
          // Get strictly second maximum value
          int ptr = 2;
          while (ptr >= 0 && kk[ptr] == kk[3]) ptr--;
          minn[now][i] = (ptr == -1 ? -INF : kk[ptr]);
        }
    
        for (int i = head[now]; i; i = e[i].nxt) {
          if (e[i].to != fa) {
            maxx[e[i].to][0] = e[i].val;
            dfs(e[i].to, now);
          }
        }
      }
    
      int lca(int a, int b) {
        if (dpth[a] < dpth[b]) std::swap(a, b);
    
        for (int i = 21; i >= 0; i--)
          if (dpth[pnt[a][i]] >= dpth[b]) a = pnt[a][i];
    
        if (a == b) return a;
    
        for (int i = 21; i >= 0; i--) {
          if (pnt[a][i] != pnt[b][i]) {
            a = pnt[a][i];
            b = pnt[b][i];
          }
        }
        return pnt[a][0];
      }
    
      int query(int a, int b, int val) {
        int res = -INF;
        for (int i = 21; i >= 0; i--) {
          if (dpth[pnt[a][i]] >= dpth[b]) {
            if (val != maxx[a][i])
              res = std::max(res, maxx[a][i]);
            else
              res = std::max(res, minn[a][i]);
            a = pnt[a][i];
          }
        }
        return res;
      }
    } tr;
    
    int fa[100010];
    
    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
    
    void Kruskal() {
      int tot = 0;
      std::sort(e + 1, e + m + 1);
      for (int i = 1; i <= n; i++) fa[i] = i;
    
      for (int i = 1; i <= m; i++) {
        int a = find(e[i].u);
        int b = find(e[i].v);
        if (a != b) {
          fa[a] = b;
          tot++;
          tr.insedge(e[i].u, e[i].v, e[i].val);
          sum += e[i].val;
          used[i] = true;
        }
        if (tot == n - 1) break;
      }
    }
    
    int main() {
      std::ios::sync_with_stdio(false);
      std::cin.tie(nullptr);
    
      std::cin >> n >> m;
      for (int i = 1; i <= m; i++) {
        int u, v, val;
        std::cin >> u >> v >> val;
        e[i] = Edge{u, v, val};
      }
    
      Kruskal();
      long long ans = INF64;
      tr.dfs(1, 0);
    
      for (int i = 1; i <= m; i++) {
        if (!used[i]) {
          int _lca = tr.lca(e[i].u, e[i].v);
          // Find the maximum edge weight on the path that is not equal to e[i].val
          long long tmpa = tr.query(e[i].u, _lca, e[i].val);
          long long tmpb = tr.query(e[i].v, _lca, e[i].val);
          // Such edge may not exist, only update answer when such edge exists
          if (std::max(tmpa, tmpb) > -INF)
            ans = std::min(ans, sum - std::max(tmpa, tmpb) + e[i].val);
        }
      }
      // Output -1 if second minimum spanning tree does not exist
      std::cout << (ans == INF64 ? -1 : ans) << '\n';
      return 0;
    }
    ```

## Bottleneck Spanning Tree

### Definition

A bottleneck spanning tree of an undirected graph $G$ is a spanning tree such that its maximum edge weight is minimum among all spanning trees of $G$.

### Properties

**The minimum spanning tree is a sufficient but not necessary condition for being a bottleneck spanning tree.** That is, the minimum spanning tree is always a bottleneck spanning tree, but a bottleneck spanning tree is not necessarily a minimum spanning tree.

Regarding the proposition that the minimum spanning tree is a bottleneck spanning tree, we can prove it by contradiction: Let the maximum edge weight in the minimum spanning tree be $w$. If the minimum spanning tree is not a bottleneck spanning tree, then all edge weights in the bottleneck spanning tree are less than $w$. We only need to delete the longest edge in the original minimum spanning tree and connect the two resulting trees with an edge from the bottleneck spanning tree. The new spanning tree must have a smaller total weight than the original minimum spanning tree, which leads to a contradiction.

### Example Problem

???+ note "POJ 2395 Out of Hay"
    Given n farms and m edges, farms are numbered from 1 to n. A person needs to travel from farm 1 to other farms. Find the maximum amount of water he needs to carry during the journey. Note that he can restock water at each farm, and the total path length should be minimized.
    The problem asks for the maximum edge weight of the bottleneck tree, which can be solved by finding the minimum spanning tree.

## Minimum Bottleneck Path

### Definition

In an undirected graph $G$, a minimum bottleneck path from $x$ to $y$ is a simple path such that the maximum edge weight on this path is minimum among all simple paths from $x$ to $y$.

### Properties

According to the definition of minimum spanning tree, the maximum edge weight on the minimum bottleneck path from $x$ to $y$ equals the maximum edge weight on the path from $x$ to $y$ on the minimum spanning tree. Although the minimum spanning tree is not unique, all minimum spanning trees have the same maximum edge weight on the path between $x$ and $y$, and this is the minimum value. That is, every path from $x$ to $y$ on every minimum spanning tree is a minimum bottleneck path.

However, not all minimum bottleneck paths correspond to a simple path between $x$ and $y$ on some minimum spanning tree.

For example, in the following graph:

![](./images/mst5.png)

The minimum bottleneck paths from node 1 to node 4 are obviously: 1-2-3-4 and 1-3-4.

But 1-2 does not appear on any minimum spanning tree.

### Application

Since the minimum bottleneck path is not unique, generally the maximum edge weight on the minimum bottleneck path is queried.

That is, we need to find the maximum on the path in the minimum spanning tree.

Both binary lifting and heavy-light decomposition can solve this; we will not elaborate further here.

## Kruskal Reconstruction Tree

### Definition

During the execution of Kruskal's algorithm, we add several edges in increasing order of weight. Now we follow this order.

First, create $n$ sets, each containing exactly one node, with node weight $0$.

Each time we add an edge, we merge two sets. We can create a new node with weight equal to the weight of the added edge, and set the root nodes of the two sets as the left and right children of the new node. Then we merge the two sets and the new node into one set, and set the new node as the root.

It is not difficult to find that after $n-1$ rounds, we obtain a binary tree with exactly $n$ leaves, and each non-leaf node has exactly two children. This tree is called the Kruskal reconstruction tree.

For example:

![](./images/mst5.png)

The Kruskal reconstruction tree of this graph is:

![](./images/mst6.png)

### Properties

It is not difficult to find that the minimum value of the maximum edge weight among all simple paths between two points in the original graph equals the maximum edge weight on the simple path between the two points on the minimum spanning tree equals the weight of the LCA of the two points on the Kruskal reconstruction tree.

That is, all points $y$ such that the minimum value of the maximum edge weight on the simple path to point $x$ is $\le val$ are all in a subtree of the Kruskal reconstruction tree, and exactly all leaf nodes of that subtree.

We find the shallowest node on the path from $x$ to the root in the Kruskal reconstruction tree whose weight is $\le val$. Obviously, this is the root of the subtree containing all points satisfying the condition.

If we need to find the maximum value of the minimum edge weight among all simple paths between two points in the original graph, we add edges in decreasing order of weight during Kruskal's algorithm.

??? note "[「LOJ 137」Enhanced Minimum Bottleneck Path](https://loj.ac/problem/137)"
    ```cpp
    --8<-- "docs/graph/code/mst/mst_2.cpp"
    ```

??? note "[NOI 2018 Return Journey](https://uoj.ac/problem/393)"
    First, preprocess the shortest distance from each node to the root.
    
    We construct a maximum spanning tree based on elevation. Obviously, for each query, the nodes that can be reached are those on the path from the query node in the maximum spanning tree where the minimum edge weight is $> p$.
    
    According to the properties of the Kruskal reconstruction tree, these nodes all belong to a subtree and are all its leaf nodes.
    
    That is, we only need to find the minimum weight among the leaves of each subtree on the Kruskal reconstruction tree to support subtree queries.
    
    The root node for the query can be found using binary lifting on the Kruskal reconstruction tree.
    
    Time complexity $O((n+m+Q) \log n)$.