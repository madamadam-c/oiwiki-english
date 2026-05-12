## Introduction

???+ question "Problem"
    Given a graph, find the minimum-weight cycle composed of $n$ nodes ($n \ge 3$).

    The minimum cycle in a graph is also called the girth.

## Process

### Brute Force

Let there be an edge of weight $w$ between $u$ and $v$. Let $dis(u,v)$ be the shortest path between $u$ and $v$ after removing the edge between $u$ and $v$.

Then the minimum cycle in an undirected graph is $dis(u,v) + w$.

Note that if finding the minimum cycle in a directed graph, the corresponding formula needs to be modified: the minimum cycle is $dis(v,u) + w$.

Total time complexity is $O(n^2m)$.

### Dijkstra

Related links: [Shortest Path/Dijkstra](./shortest-path.md#dijkstra-algorithm)

#### Process

Enumerate all edges. For each edge, run Dijkstra starting from one endpoint of that edge after deleting it, for the same reasoning as above.

#### Properties

Time complexity is $O(m(n+m)\log n)$.

### Floyd

Related links: [Shortest Path/Floyd](./shortest-path.md#floyd-algorithm)

#### Process

Let the edge weight between $u$ and $v$ in the original graph be $val(u,v)$.

We notice that Floyd's algorithm has a property: when the outermost loop reaches node $k$ (before the $k$-th iteration starts), in the shortest path array $dis$, $dis_{u,v}$ represents the shortest path from $u$ to $v$ that passes only through nodes with indices in the range $[1, k)$.

From the definition of a minimum cycle, it has at least three vertices. Let the vertex with the largest index be $w$, and its two adjacent vertices on the cycle be $u$ and $v$. When the outermost loop enumerates $k = w$, the length of this cycle is $dis_{u,v} + val(v,w) + val(w,u)$.

Therefore, during the loop, for each $k$, enumerate pairs $(i,j)$ satisfying $i < k, j < k$ and update the answer.

#### Recording the Path

Now we know the cycle is in the form $u \to k \to v$, then from $v$ back to $u$ (all passed nodes have index $< k$).

The problem becomes finding the path from $v \leadsto u$. By the triangle inequality $dis_{u,v} \le dis_{u,i} + dis_{i,v}$, consider recording $pos_{u,v} = j$ to represent a point $j$ such that $dis_{u,v} = dis_{u,j} + dis_{j,v}$. Clearly, $j$ is on the path from $v \leadsto u$.

Thus, the path can be split into two segments: $v \leadsto j$ and $j \leadsto u$, processed recursively.

???+ note "Proof that recursion does not fall into infinite loops"
    Use proof by contradiction.
    
    Suppose the cycle passes through a node $u$ more than once. Then on the cycle there is a path from $u$ that goes through several edges and returns to $u$. This forms a new cycle.
    
    Since the graph does not contain negative cycles (if it did, there would be no minimum cycle), the total edge weight of the new cycle is less than or equal to that of the original cycle.
    
    So by taking only this one cycle, no node $u$ is passed through more than once. The assumption is contradicted, so the cycle does not pass through any node more than once.
    
    Therefore, when recursing to nodes $u$ and $v$, their $pos_{u,v}$ must be different from the indices of both nodes, meaning a new node has been added.
    
    In particular, when $u$ and $v$ are adjacent, just return directly.
    
    Since the total number of nodes is $n$, the number of new nodes added (i.e., the number of recursive calls) does not exceed $n$. Therefore, recursion does not fall into infinite loops.

#### Properties

Time complexity: $O(n^3)$.

#### Implementation

The reference implementations in C++ and Python (with path recording) are given below:

=== "C++"
    ```cpp
    // The graph has n vertices
    int val[MAXN + 1][MAXN + 1];  // Adjacency matrix of the original graph
    int cnt, path[MAXN + 5];      // Record the minimum cycle path and length
    
    void get_path(int u, int v) {  // Get the path from u to v
      if (pos[u][v] == 0) return;
    
      int k = pos[u][v];
      get_path(u, k);
      path[++cnt] = k;
      get_path(k, v);
    }
    
    void Floyd(const int &n) {
      static int dis[MAXN + 1][MAXN + 1];  // Shortest path matrix
      static int pos[MAXN + 1][MAXN + 1];
      memcpy(dis, val, sizeof(val));
      memset(pos, 0, sizeof(pos));
      for (int k = 1; k <= n; ++k) {
        for (int i = 1; i < k; ++i)
          for (int j = 1; j < i; ++j)
            if (ans >
                (long long)val[i][k] + val[k][j] + dis[i][j]) {  // Found a shorter cycle
              // Since i < k and j < i are guaranteed here, the three vertices are different, no zero cycle occurs.
              ans = val[i][k] + val[k][j] + dis[i][j], cnt = 0;
              path[++cnt] = i, path[++cnt] = k,
              path[++cnt] = j;  // Add vertices i, k, j in order
              get_path(j, i);   // Add the path from j to i
            }
    
        for (int i = 1; i <= n; ++i)  // Normal Floyd shortest path update
          for (int j = 1; j <= n; ++j) {
            if (dis[i][j] > dis[i][k] + dis[k][j]) {
              dis[i][j] = dis[i][k] + dis[k][j];
              pos[i][j] = k;  // Current path can be updated through k
            }
          }
      }
    }
    ```

=== "Python"
    ```python
    # Define a sufficiently large value to represent infinity
    INF = sys.maxsize
    
    
    def get_path(i, j, pos, path, cnt):
        """
        Recursively get the intermediate nodes on the shortest path from node i to node j.
    
        Args:
            i (int): Starting node (0-based index).
            j (int): Ending node (0-based index).
            pos (list[list[int]]): Matrix recording intermediate nodes of the shortest path. pos[i][j] = k means the shortest path from i to j passes through k.
            path (list[int]): List storing path nodes (using 0-based index).
            cnt (int): Current number of path nodes.
    
        Returns:
            int: Updated number of path nodes.
        """
        # If pos[i][j] is -1, there is no intermediate node between i and j
        if pos[i][j] == -1:
            return cnt
    
        # Get the intermediate node k
        k = pos[i][j]
        # Recursively get the path from i to k
        cnt = get_path(i, k, pos, path, cnt)
        # Add intermediate node k to the path
        path[cnt] = k
        cnt += 1
        # Recursively get the path from k to j
        cnt = get_path(k, j, pos, path, cnt)
        return cnt
    
    
    def find_minimum_cycle_undirected(n, edges):
        """
        Find the minimum cycle in an undirected graph using the Floyd-Warshall algorithm.
    
        Args:
            n (int): Number of nodes in the graph (1 to n).
            edges (list[tuple]): List of edges, each element is (u, v, w), meaning there is an edge of weight w between nodes u and v.
                                 Node indices are 1 to n.
    
        Returns:
            tuple: Contains the length of the minimum cycle and the path.
                   If no cycle exists, returns (INF, []).
                   The path is a list of node indices (1-based index).
        """
        # Internally use 0-based indexing
        N = n
        # Initialize adjacency matrix g representing original edge weights
        g = [[INF for _ in range(N)] for _ in range(N)]
        # Initialize shortest path matrix dis, initially the same as g
        dis = [[INF for _ in range(N)] for _ in range(N)]
        # Initialize pos matrix recording intermediate nodes of shortest paths
        pos = [[-1 for _ in range(N)] for _ in range(N)]
    
        # Initialize diagonal to 0 (distance from a node to itself)
        for i in range(N):
            g[i][i] = 0
            dis[i][i] = 0
    
        # Build adjacency matrix from input edges (undirected graph)
        for u, v, w in edges:
            # Convert 1-based index to 0-based
            u -= 1
            v -= 1
            # For undirected graph, edges are bidirectional
            g[u][v] = min(g[u][v], w)
            g[v][u] = min(g[v][u], w)
            dis[u][v] = min(dis[u][v], w)
            dis[v][u] = min(dis[v][u], w)
    
        # Initialize minimum cycle length to infinity
        min_cycle_len = INF
        # Initialize minimum cycle path
        min_cycle_path = []
    
        # Floyd-Warshall algorithm core
        # k as intermediate node (0-based index)
        for k in range(N):
            # Before updating dis[i][j], check if a smaller cycle can be formed through node k
            # The cycle consists of i -> k -> j -> ... -> i
            # Here, dis[i][j] is the shortest path considering nodes 0 to k-1 as intermediate nodes
            # C++ code uses loop order i < k and j < i, we follow the same logic (0-based)
            for i in range(k):  # 0 <= i < k
                for j in range(i):  # 0 <= j < i
                    # Check if i, k, j form a cycle connected through dis[i][j]
                    # Ensure original edges g[i][k] and g[k][j] exist (not INF)
                    # And the shortest path dis[i][j] exists (not INF)
                    if g[i][k] != INF and g[k][j] != INF and dis[i][j] != INF:
                        current_cycle_len = g[i][k] + g[k][j] + dis[i][j]
                        if current_cycle_len < min_cycle_len:
                            min_cycle_len = current_cycle_len
                            # Reconstruct the path
                            path = [0] * (N + 5)  # Temporary array for path storage, large enough
                            cnt = 0
                            # Add vertices in order i, k, j
                            path[cnt] = i
                            cnt += 1
                            path[cnt] = k
                            cnt += 1
                            path[cnt] = j
                            cnt += 1
                            # Get intermediate nodes on the shortest path from j to i (using previously computed dis and pos)
                            cnt = get_path(j, i, pos, path, cnt)
                            # Extract actual path nodes (remove unused part)
                            # Convert 0-based index to 1-based
                            min_cycle_path = [node + 1 for node in path[:cnt]]
    
            # Standard Floyd-Warshall shortest path update
            for i in range(N):
                for j in range(N):
                    if (
                        dis[i][k] != INF
                        and dis[k][j] != INF
                        and dis[i][j] > dis[i][k] + dis[k][j]
                    ):
                        dis[i][j] = dis[i][k] + dis[k][j]
                        # Record that the shortest path from i to j passes through k
                        pos[i][j] = k
    
        return min_cycle_len, min_cycle_path
    ```

## Template Problem

??? note "[AcWing 344 Tourist Route](https://www.acwing.com/problem/content/346)"
    Given an undirected graph with $n$ vertices, find a cycle in the graph containing at least $3$ vertices with no repeated vertices, and the sum of edge lengths on the cycle is minimized.
    
    This problem is called the minimum cycle problem for undirected graphs.
    
    You need to output a minimum cycle. If there are multiple minimum cycles, outputting any one is acceptable.
    
    $n \le 100$

The $O(n^3)$ solution is acceptable for the time complexity, and we can directly apply the Floyd method for finding minimum cycles.

=== "C++"
    ```cpp
    #include <bits/stdc++.h>
    using lint = long long;
    // Define a sufficiently large constant for the maximum number of nodes
    const int MAXN = 110;
    
    // Define a sufficiently large value for infinity, initialize the minimum cycle length
    lint ans = 1e9;  // lint is an alias for long long
    
    // Number of nodes n, number of edges m
    // cnt records the number of nodes in the minimum cycle path
    // path stores the minimum cycle path nodes
    int n, m, cnt, path[MAXN];
    
    // g stores the adjacency matrix of the original graph
    // dis stores the shortest path matrix (updated during Floyd-Warshall algorithm computation)
    // pos records intermediate nodes of the shortest path, pos[i][j] = k means the shortest path from i to j passes through k
    int g[MAXN][MAXN], dis[MAXN][MAXN], pos[MAXN][MAXN];
    
    // Recursive function: get intermediate nodes on the shortest path from node u to node v
    // Reconstruct the path based on the pos matrix
    void get_path(int u, int v) {
      // If pos[u][v] is 0, there is no intermediate node between u and v, return directly
      if (pos[u][v] == 0) return;
    
      // Get the intermediate node k
      int k = pos[u][v];
      // Recursively get the path from u to k
      get_path(u, k);
      // Add intermediate node k to the path
      path[++cnt] = k;
      // Recursively get the path from k to v
      get_path(k, v);
    }
    
    // Floyd-Warshall algorithm function: find the minimum cycle in the graph
    void Floyd() {
      // Outer loop: k as intermediate node (1 to n)
      for (int k = 1; k <= n; ++k) {
        // Inner loop: i and j, used to check if a smaller cycle can be formed through node k
        // Loop order here is i from 1 to k-1, j from 1 to i-1
        // This checks cycles composed of i -> k -> j -> ... -> i
        for (int i = 1; i < k; ++i)
          for (int j = 1; j < i; ++j)
            // Check if connecting i and j through node k forms a smaller cycle
            // Cycle length is original edge weight g[i][k] from i to k plus g[k][j] from k to j
            // plus current shortest path dis[i][j] from i to j
            if (ans > (long long)g[i][k] + g[k][j] + dis[i][j]) {
              // Found a smaller cycle
              ans = g[i][k] + g[k][j] + dis[i][j];  // Update minimum cycle length
              cnt = 0;                              // Reset path count
              // Add i, k, j to the path in order
              path[++cnt] = i, path[++cnt] = k, path[++cnt] = j;
              // Get intermediate nodes on the shortest path from j to i, add to the path
              get_path(j, i);
            }
    
        // Standard Floyd-Warshall shortest path update
        // i from 1 to n, j from 1 to n
        for (int i = 1; i <= n; ++i)
          for (int j = 1; j <= n; ++j) {
            // If a shorter path from i to j can be obtained through intermediate node k
            if (dis[i][j] > dis[i][k] + dis[k][j]) {
              // Update shortest path
              dis[i][j] = dis[i][k] + dis[k][j];
              // Record that the shortest path from i to j passes through k
              pos[i][j] = k;
            }
          }
      }
    }
    
    // Main function
    int main() {
      // Read number of nodes n and edges m
      std::cin >> n >> m;
      // Initialize original adjacency matrix g, set all edge weights to infinity (0x3f usually represents a large value)
      memset(g, 0x3f, sizeof(g));
      // Set distance from a node to itself to 0
      for (int i = 1; i <= n; ++i) g[i][i] = 0;
      // Read m edges, build original adjacency matrix g
      // For undirected graph, edges are bidirectional, take the smaller weight
      for (int i = 0, u, v, w; i < m; ++i) {
        std::cin >> u >> v >> w;
        g[u][v] = g[v][u] = std::min(g[u][v], w);
      }
      // Copy original adjacency matrix g to shortest path matrix dis
      memcpy(dis, g, sizeof(g));
      // Call Floyd algorithm to find minimum cycle
      Floyd();
      // Determine if a cycle exists based on the minimum cycle length
      if (ans == 1e9) {  // If the minimum cycle length is still infinity, no cycle exists
        puts("No solution.");
      } else {
        // If a cycle exists, print the path nodes
        // std::cout << "ans = " << ans << std::endl; // Print minimum cycle length (commented out)
        // Print path nodes separated by spaces
        for (int i = 1; i <= cnt; ++i)
          std::cout << path[i]
                    << (i == cnt ? "" : " ");  // No space after the last node
        std::cout << std::endl;                // Newline after path printing
      }
      return 0;
    }
    ```

=== "Python"
    ```python
    import copy
    import sys
    
    # Define a sufficiently large value to represent infinity
    INF = sys.maxsize
    
    
    def get_path(i, j, pos, path, cnt):
        """
        Recursively get the intermediate nodes on the shortest path from node i to node j.
    
        Args:
            i (int): Starting node (0-based index).
            j (int): Ending node (0-based index).
            pos (list[list[int]]): Matrix recording intermediate nodes of the shortest path. pos[i][j] = k means the shortest path from i to j passes through k.
            path (list[int]): List storing path nodes (using 0-based index).
            cnt (int): Current number of path nodes.
    
        Returns:
            int: Updated number of path nodes.
        """
        # If pos[i][j] is -1, there is no intermediate node between i and j
        if pos[i][j] == -1:
            return cnt
    
        # Get the intermediate node k
        k = pos[i][j]
        # Recursively get the path from i to k
        cnt = get_path(i, k, pos, path, cnt)
        # Add intermediate node k to the path
        path[cnt] = k
        cnt += 1
        # Recursively get the path from k to j
        cnt = get_path(k, j, pos, path, cnt)
        return cnt
    
    
    def find_minimum_cycle_undirected(n, edges):
        """
        Find the minimum cycle in an undirected graph using the Floyd-Warshall algorithm.
    
        Args:
            n (int): Number of nodes in the graph (1 to n).
            edges (list[tuple]): List of edges, each element is (u, v, w), meaning there is an edge of weight w between nodes u and v.
                                 Node indices are 1 to n.
    
        Returns:
            tuple: Contains the length of the minimum cycle and the path.
                   If no cycle exists, returns (INF, []).
                   The path is a list of node indices (1-based index).
        """
        # Internally use 0-based indexing
        N = n
        # Initialize adjacency matrix g representing original edge weights
        g = [[INF for _ in range(N)] for _ in range(N)]
        # Initialize shortest path matrix dis, initially the same as g
        dis = [[INF for _ in range(N)] for _ in range(N)]
        # Initialize pos matrix recording intermediate nodes of shortest paths
        pos = [[-1 for _ in range(N)] for _ in range(N)]
    
        # Initialize diagonal to 0 (distance from a node to itself)
        for i in range(N):
            g[i][i] = 0
            dis[i][i] = 0
    
        # Build adjacency matrix from input edges (undirected graph)
        for u, v, w in edges:
            # Convert 1-based index to 0-based
            u -= 1
            v -= 1
            # For undirected graph, edges are bidirectional
            g[u][v] = min(g[u][v], w)
            g[v][u] = min(g[v][u], w)
            dis[u][v] = min(dis[u][v], w)
            dis[v][u] = min(dis[v][u], w)
    
        # Initialize minimum cycle length to infinity
        min_cycle_len = INF
        # Initialize minimum cycle path
        min_cycle_path = []
    
        # Floyd-Warshall algorithm core
        # k as intermediate node (0-based index)
        for k in range(N):
            # Before updating dis[i][j], check if a smaller cycle can be formed through node k
            # The cycle consists of i -> k -> j -> ... -> i
            # Here, dis[i][j] is the shortest path considering nodes 0 to k-1 as intermediate nodes
            # C++ code uses loop order i < k and j < i, we follow the same logic (0-based)
            for i in range(k):  # 0 <= i < k
                for j in range(i):  # 0 <= j < i
                    # Check if i, k, j form a cycle connected through dis[i][j]
                    # Ensure original edges g[i][k] and g[k][j] exist (not INF)
                    # And the shortest path dis[i][j] exists (not INF)
                    if g[i][k] != INF and g[k][j] != INF and dis[i][j] != INF:
                        current_cycle_len = g[i][k] + g[k][j] + dis[i][j]
                        if current_cycle_len < min_cycle_len:
                            min_cycle_len = current_cycle_len
                            # Reconstruct the path
                            path = [0] * (N + 5)  # Temporary array for path storage, large enough
                            cnt = 0
                            # Add vertices in order i, k, j
                            path[cnt] = i
                            cnt += 1
                            path[cnt] = k
                            cnt += 1
                            path[cnt] = j
                            cnt += 1
                            # Get intermediate nodes on the shortest path from j to i (using previously computed dis and pos)
                            cnt = get_path(j, i, pos, path, cnt)
                            # Extract actual path nodes (remove unused part)
                            # Convert 0-based index to 1-based
                            min_cycle_path = [node + 1 for node in path[:cnt]]
    
            # Standard Floyd-Warshall shortest path update
            for i in range(N):
                for j in range(N):
                    if (
                        dis[i][k] != INF
                        and dis[k][j] != INF
                        and dis[i][j] > dis[i][k] + dis[k][j]
                    ):
                        dis[i][j] = dis[i][k] + dis[k][j]
                        # Record that the shortest path from i to j passes through k
                        pos[i][j] = k
    
        return min_cycle_len, min_cycle_path
    
    
    # --- Main program entry ---
    if __name__ == "__main__":
        # Read number of nodes n and edges m
        n, m = map(int, sys.stdin.readline().split())
    
        # Read edge information
        edges = []
        for _ in range(m):
            u, v, w = map(int, sys.stdin.readline().split())
            edges.append((u, v, w))
    
        # Find minimum cycle
        min_len, path = find_minimum_cycle_undirected(n, edges)
    
        # Output result
        if min_len == INF:
            print("No solution.")
        else:
            # Print path nodes (1-based index) separated by spaces
            print(" ".join(map(str, path)))
    ```

## Problem 2

GDOI2018 Day2 Patrol

Given an undirected graph with $n$ vertices and non-negative edge weights. Perform $q$ operations, three types:

1.  Delete a vertex and all edges connected to it
2.  Restore a deleted vertex and all its edges
3.  Query the size of the minimum cycle containing vertex $x$

For $50\%$ of the data, $n, q \le 100$.

For any simple cycle containing vertex $x$, there are two edges adjacent to $x$. Removing either of them turns the simple cycle into a simple path.

Therefore, enumerate all edges adjacent to $x$. For each, remove one of them and run Dijkstra.

Alternatively, for each query, run Floyd once to find the minimum cycle, $O(qn^3)$.

For $100\%$ of the data, $n, q \le 400$.

Still use the Floyd algorithm for finding minimum cycles.

If there are no deletions, removing the query vertex splits the simple cycle into a simple path.

However, the second step uses Floyd to compute.

The answer is to find the distances between any two nodes without passing through the query vertex $x$.

How to do it online?

Force offline processing to avoid deletion operations.

Arrange queries in chronological order and build a segment tree over these queries.

The appearance time of each vertex covers all moments except when the vertex is queried. If a vertex is queried $x$ times, its appearance time can be seen as $x + 1$ segments, inserted into the segment tree.

After completion, traverse the entire segment tree. When passing through a node, store a backup of the Floyd array, then add all vertices inserted in this interval. When leaving, restore using the backup array.

The time complexity of this approach is $O(qn^2\log q)$.

There is also an online approach with better time complexity.

For a query on vertex $x$, run a shortest path algorithm with $x$ as the source, build the shortest path tree, and determine which subtree each vertex belongs to.

Then there must be a non-tree edge such that its two endpoints are in different subtrees of the root. This non-tree edge plus the paths from both endpoints to the root forms a minimum cycle.

Proof:

Clearly, the minimum cycle contains at least one non-tree edge whose two endpoints are in different subtrees of the root.

Suppose this edge is $(u,v)$. In the shortest path tree, the path from $x$ to $u$ is the shortest among all paths from $x$ to $u$, and the path from $x$ to $v$ is also the shortest. Therefore, the cycle $x\to u\to v\to x$ cannot be longer than the minimum cycle.

Then we can enumerate all non-tree edges and update the answer.

The complexity of each query is the complexity of running a single-source shortest path, $O(n^2)$.

Total time complexity is $O(qn^2)$.
