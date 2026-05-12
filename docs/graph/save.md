author: Ir1d, sshwy, Xeonacid, partychicken, Anguei, HeRaNO

In OI, to perform operations on graphs, you first need to learn how to store graphs.

## Prerequisites

This article assumes the reader has read and understood the basic content in [Graph Theory Concepts](./concept.md). If you encounter difficulties while reading, you can also refer to [Graph Theory Concepts](./concept.md).

In this article, we use $n$ to denote the number of vertices in a graph, $m$ to denote the number of edges, and $d^+(u)$ to denote the out-degree of vertex $u$, i.e., the number of edges outgoing from $u$.

## Storing Edges Directly

### Method

Use an array to store edges, where each element contains the source and destination vertices of an edge (for weighted graphs, it also contains the edge weight). (Alternatively, use multiple arrays to store the source vertices, destination vertices, and edge weights separately.)

??? note "Reference Code"
    === "C++"
        ```cpp
        #include <iostream>
        #include <vector>
        
        using namespace std;
        
        struct Edge {
          int u, v;
        };
        
        int n, m;
        vector<Edge> e;
        vector<bool> vis;
        
        bool find_edge(int u, int v) {
          for (int i = 1; i <= m; ++i) {
            if (e[i].u == u && e[i].v == v) {
              return true;
            }
          }
          return false;
        }
        
        void dfs(int u) {
          if (vis[u]) return;
          vis[u] = true;
          for (int i = 1; i <= m; ++i) {
            if (e[i].u == u) {
              dfs(e[i].v);
            }
          }
        }
        
        int main() {
          cin >> n >> m;
        
          vis.resize(n + 1, false);
          e.resize(m + 1);
        
          for (int i = 1; i <= m; ++i) cin >> e[i].u >> e[i].v;
        
          return 0;
        }
        ```
    
    === "Python"
        ```python
        class Edge:
            def __init__(self, u=0, v=0):
                self.u = u
                self.v = v
        
        
        n, m = map(int, input().split())
        
        e = [Edge() for _ in range(m)]
        vis = [False] * n
        
        for i in range(m):
            e[i].u, e[i].v = map(int, input().split())
        
        
        def find_edge(u, v):
            for i in range(m):
                if e[i].u == u and e[i].v == v:
                    return True
            return False
        
        
        def dfs(u):
            if vis[u]:
                return
            vis[u] = True
            for i in range(m):
                if e[i].u == u:
                    dfs(e[i].v)
        ```

### Complexity

Query whether an edge exists: $O(m)$.

Traverse all outgoing edges of a vertex: $O(m)$.

Traverse the entire graph: $O(nm)$.

Space complexity: $O(m)$.

### Applications

Since directly storing edges has low traversal efficiency, it is generally not used for graph traversal.

In [Kruskal's Algorithm](./mst.md#kruskal-algorithm), directly storing edges is necessary because edges need to be sorted by weight.

In some problems, you may need to build multiple graphs (e.g., building the original graph and its reverse graph). You can either use multiple data structures to store multiple graphs simultaneously, or store edges directly and rebuild the graph from the stored edges when needed.

## Adjacency Matrix

### Method

Use a 2D array `adj` to store edges, where `adj[u][v]` equals 1 if there is an edge from $u$ to $v$, and 0 if there is no edge. For weighted graphs, `adj[u][v]` can store the weight of the edge from $u$ to $v$.

??? note "Reference Code"
    === "C++"
        ```cpp
        #include <iostream>
        #include <vector>
        
        using namespace std;
        
        int n, m;
        vector<bool> vis;
        vector<vector<bool>> adj;
        
        bool find_edge(int u, int v) { return adj[u][v]; }
        
        void dfs(int u) {
          if (vis[u]) return;
          vis[u] = true;
          for (int v = 1; v <= n; ++v) {
            if (adj[u][v]) {
              dfs(v);
            }
          }
        }
        
        int main() {
          cin >> n >> m;
        
          vis.resize(n + 1);
          adj.resize(n + 1, vector<bool>(n + 1));
        
          for (int i = 1; i <= m; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u][v] = true;
          }
        
          return 0;
        }
        ```
    
    === "Python"
        ```python
        vis = [False] * (n + 1)
        adj = [[False] * (n + 1) for _ in range(n + 1)]
        
        for i in range(1, m + 1):
            u, v = map(lambda x: int(x), input().split())
            adj[u][v] = True
        
        
        def find_edge(u, v):
            return adj[u][v]
        
        
        def dfs(u):
            if vis[u]:
                return
            vis[u] = True
            for v in range(1, n + 1):
                if adj[u][v]:
                    dfs(v)
        ```

### Complexity

Query whether an edge exists: $O(1)$.

Traverse all outgoing edges of a vertex: $O(n)$.

Traverse the entire graph: $O(n^2)$.

Space complexity: $O(n^2)$.

### Applications

Adjacency matrices are only suitable for cases without parallel edges (or where parallel edges can be ignored).

The most notable advantage is that you can query whether an edge exists in $O(1)$.

Since adjacency matrices are very inefficient on sparse graphs (especially on graphs with many vertices, where the space is unbearable), they are generally only used on dense graphs.

## Adjacency List

### Method

Use an array of data structures that support dynamic insertion, such as `vector<int> adj[n + 1]`, to store edges, where `adj[u]` stores all information about outgoing edges from vertex $u$ (destinations, weights, etc.).

??? note "Reference Code"
    === "C++"
        ```cpp
        #include <iostream>
        #include <vector>
        
        using namespace std;
        
        int n, m;
        vector<bool> vis;
        vector<vector<int>> adj;
        
        bool find_edge(int u, int v) {
          for (int i = 0; i < adj[u].size(); ++i) {
            if (adj[u][i] == v) {
              return true;
            }
          }
          return false;
        }
        
        void dfs(int u) {
          if (vis[u]) return;
          vis[u] = true;
          for (int i = 0; i < adj[u].size(); ++i) dfs(adj[u][i]);
        }
        
        int main() {
          cin >> n >> m;
        
          vis.resize(n + 1);
          adj.resize(n + 1);
        
          for (int i = 1; i <= m; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
          }
        
          return 0;
        }
        ```
    
    === "Python"
        ```python
        vis = [False] * (n + 1)
        adj = [[] for _ in range(n + 1)]
        
        for i in range(1, m + 1):
            u, v = map(lambda x: int(x), input().split())
            adj[u].append(v)
        
        
        def find_edge(u, v):
            for i in range(0, len(adj[u])):
                if adj[u][i] == v:
                    return True
            return False
        
        
        def dfs(u):
            if vis[u]:
                return
            vis[u] = True
            for i in range(0, len(adj[u])):
                dfs(adj[u][i])
        ```

### Complexity

Query whether an edge from $u$ to $v$ exists: $O(d^+(u))$ (if pre-sorted, you can use [Binary Search](../basic/binary.md) to achieve $O(\log(d^+(u)))$).

Traverse all outgoing edges of vertex $u$: $O(d^+(u))$.

Traverse the entire graph: $O(n+m)$.

Space complexity: $O(m)$.

### Applications

Suitable for storing various types of graphs, unless there are special requirements (e.g., need to quickly query whether an edge exists and there are few vertices, in which case an adjacency matrix can be used).

Particularly suitable for cases where all outgoing edges of a vertex need to be sorted.

## Linked Forward Star

### Method

Essentially an adjacency list implemented using linked lists. The core code is as follows:

=== "C++"
    ```cpp
    // head[u] and cnt are both initialized to -1
    void add(int u, int v) {
      nxt[++cnt] = head[u];  // successor of current edge
      head[u] = cnt;          // first edge from source u
      to[cnt] = v;            // destination of current edge
    }
    
    // traverse outgoing edges of u
    for (int i = head[u]; ~i; i = nxt[i]) {  // ~i means i != -1
      int v = to[i];
    }
    ```

=== "Python"
    ```python
    # head[u] and cnt are both initialized to -1
    def add(u, v):
        cnt = cnt + 1
        nex[cnt] = head[u]  # successor of current edge
        head[u] = cnt  # first edge from source u
        to[cnt] = v  # destination of current edge
    
    
    # traverse outgoing edges of u
    i = head[u]
    while ~i:  # ~i means i != -1
        v = to[i]
        i = nxt[i]
    ```

??? note "Reference Code"
    ```cpp
    #include <iostream>
    #include <vector>
    
    using namespace std;
    
    int n, m;
    vector<bool> vis;
    vector<int> head, nxt, to;
    
    void add(int u, int v) {
      nxt.push_back(head[u]);
      head[u] = to.size();
      to.push_back(v);
    }
    
    bool find_edge(int u, int v) {
      for (int i = head[u]; ~i; i = nxt[i]) {  // ~i means i != -1
        if (to[i] == v) {
          return true;
        }
      }
      return false;
    }
    
    void dfs(int u) {
      if (vis[u]) return;
      vis[u] = true;
      for (int i = head[u]; ~i; i = nxt[i]) dfs(to[i]);
    }
    
    int main() {
      cin >> n >> m;
    
      vis.resize(n + 1, false);
      head.resize(n + 1, -1);
    
      for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        add(u, v);
      }
    
      return 0;
    }
    ```

### Complexity

Query whether an edge from $u$ to $v$ exists: $O(d^+(u))$.

Traverse all outgoing edges of vertex $u$: $O(d^+(u))$.

Traverse the entire graph: $O(n+m)$.

Space complexity: $O(m)$.

### Applications

Suitable for storing various types of graphs, but cannot quickly query whether an edge exists, nor conveniently sort outgoing edges of a vertex.

The advantage is that edges are numbered, which can be very useful sometimes. Also, if `cnt` is initialized to an odd number, when storing bidirectional edges, `i ^ 1` is the reverse edge of `i` (commonly used in [Network Flow](./flow.md)).
