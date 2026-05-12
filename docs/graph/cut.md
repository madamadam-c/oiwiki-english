author: Ir1d, sshwy, GavinZhengOI, Planet6174, ouuan, Marcythm, ylxmf2005, 0xis-cn

Related reading: [Biconnected Components](./bcc.md)

For rigorous definitions of cut vertices and bridges, see [Graph Theory Concepts](./concept.md).

## Cut Vertices

> For an undirected graph, if removing a vertex increases the number of connected components in the graph, then that vertex is a cut vertex (also known as an articulation point).

### Procedure

If we try to delete each vertex and check the graph's connectivity, the complexity would be prohibitively high. Therefore, we introduce a commonly used algorithm: Tarjan's algorithm.

First, let's look at a graph:

![](./images/cut1.svg)

It's easy to see that vertex 2 is a cut vertex, and this graph has only this one cut vertex.

First, we assign timestamps according to the DFS order (the order of visits).

![](./images/cut2.svg)

This information is stored in an array called `dfn`.

We also need another array `low`, which stores the minimum timestamp reachable without passing through its parent.

For example, `low[2]` is 1, and `low[5]` and `low[6]` are 3.

Then we start DFS. The rule for determining whether a vertex is a cut vertex is: for a vertex $u$, if there exists at least one child vertex $v$ such that $low_v \geq dfn_u$ (i.e., it cannot reach an ancestor), then $u$ is a cut vertex.

This rule does not apply to the root of the search. The root requires special consideration: if it is not a cut vertex, then other paths can still reach all nodes, so from the root we only "searched downward once", meaning there is only one child in the DFS tree. If there are two or more children in the DFS tree, then the root must be a cut vertex (consider the graph above starting from 2; the DFS tree should have two children: 3 or 4, and 5 or 6). If there is only one child, removing it has no effect. For example, in the graph below, a cycle is formed.

![](./images/cut3.svg)

When visiting node 1's children, suppose we first DFS to node 2, mark it as used, then recursively go down to node 4, and from 4 to node 3. When backtracking, we find that node 3 has already been visited, so it's not a cut vertex.

The pseudocode for updating `low` is as follows:

$$
\begin{array}{ll}
1 & \textbf{if } v \text{ is a child of } u \\
2 & \qquad \text{low}_u = \min(\text{low}_u, \text{low}_v) \\
3 & \textbf{else} \\
4 & \qquad \text{low}_u = \min(\text{low}_u, \text{dfn}_v) \\
\end{array}
$$

### Example Problem

[Luogu P3388 Template: Cut Vertices (Articulation Points)](https://www.luogu.com.cn/problem/P3388)

??? note "Example Code"
    ```cpp
    --8<-- "docs/graph/code/cut/cut_1.cpp"
    ```

## Bridges (Without Parallel Edges)

Similar to cut vertices, this is called a bridge.

> For an undirected graph, if removing an edge increases the number of connected components, that edge is called a bridge or cut edge. More formally: given a connected graph $G=\{V,E\}$, $e$ is an edge (i.e., $e \in E$), if $G-e$ is disconnected, then $e$ is a cut edge (bridge) of graph $G$.

For example, in the following graph,

![Bridge example](./images/bridge1.svg)

The red edge is a bridge.

### Procedure

Similar to cut vertices, with just one change: $low_v>dfn_u$ is sufficient, and there's no need to consider the root specially.

Bridges are independent of whether a vertex is the root. Originally, when finding cut vertices, we check whether child $v$ cannot reach an ancestor (including the parent) without going through parent $u$, so $u$ is a cut vertex. If $low_v=dfn_u$, it means $v$ can still reach the parent. If $v$ cannot reach an ancestor and has no alternative path back to the parent, then the edge $u-v$ is a bridge.

### Implementation

The following code finds bridges in an undirected graph **without parallel edges**, where `isbridge[x]` being true means `(father[x], x)` is a bridge.

=== "C++"
    ```cpp
    int low[MAXN], dfn[MAXN], idx;
    bool isbridge[MAXN];
    vector<int> G[MAXN];
    int cnt_bridge;
    int father[MAXN];
    
    void tarjan(int u, int fa) {
      father[u] = fa;
      low[u] = dfn[u] = ++idx;
      for (const auto &v : G[u]) {
        if (!dfn[v]) {
          tarjan(v, u);
          low[u] = min(low[u], low[v]);
          if (low[v] > dfn[u]) {
            isbridge[v] = true;
            ++cnt_bridge;
          }
        } else if (v != fa) {
          low[u] = min(low[u], dfn[v]);
        }
      }
    }
    ```

=== "Python"
    ```python
    low = [0] * MAXN
    dfn = [0] * MAXN
    idx = 0
    isbridge = [False] * MAXN
    G = [[0 for i in range(MAXN)] for j in range(MAXN)]
    cnt_bridge = 0
    father = [0] * MAXN
    
    
    def tarjan(u, fa):
        father[u] = fa
        idx = idx + 1
        low[u] = dfn[u] = idx
        for i in range(0, len(G[u])):
            v = G[u][i]
            if dfn[v] == False:
                tarjan(v, u)
                low[u] = min(low[u], low[v])
                if low[v] > dfn[u]:
                    isbridge[v] = True
                    cnt_bridge = cnt_bridge + 1
            elif v != fa:
                low[u] = min(low[u], dfn[v])
    ```

## Bridges (With Parallel Edges)

However, the above approach without parallel edges does not work correctly for undirected graphs with parallel edges.

Because there may be multiple edges between two nodes, in which case none of them would be a bridge.

### Procedure

One approach is to change the `fa` parameter to the edge number we just traversed (each edge has a unique number), i.e., change "don't use the parent node for updates" to "don't use the incoming edge for updates".

Another simpler approach is to maintain a flag indicating whether we have already traversed one edge to the parent node; when we encounter the parent node again, we update normally.

The following code finds bridges in an undirected graph that may **have parallel edges**.

=== "C++"
    ```cpp
    int low[MAXN], dfn[MAXN], idx;
    bool isbridge[MAXN];
    vector<int> G[MAXN];
    int cnt_bridge;
    int father[MAXN];
    
    void tarjan(int u, int fa) {
      bool flag = false;
      father[u] = fa;
      low[u] = dfn[u] = ++idx;
      for (const auto &v : G[u]) {
        if (!dfn[v]) {
          tarjan(v, u);
          low[u] = min(low[u], low[v]);
          if (low[v] > dfn[u]) {
            isbridge[v] = true;
            ++cnt_bridge;
          }
        } else {
          if (v != fa || flag)
            low[u] = min(low[u], dfn[v]);
          else
            flag = true;
        }
      }
    }
    ```

## Practice

-   [P3388 Template: Cut Vertices](https://www.luogu.com.cn/problem/P3388)
-   [POJ2117 Electricity](http://poj.org/problem?id=2117)
-   [HDU4738 Caocao's Bridges](https://acm.hdu.edu.cn/showproblem.php?pid=4738)
-   [HDU2460 Network](https://acm.hdu.edu.cn/showproblem.php?pid=2460)
-   [POJ1523 SPF](http://poj.org/problem?id=1523)

Tarjan's algorithm has many other applications, such as finding strongly connected components, graph condensation, and solving 2-SAT problems.
