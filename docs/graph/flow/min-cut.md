## Concepts

### Cut

For a flow network $G=(V,E)$, a cut is defined as a **partition of vertices**: dividing all vertices into two sets $S$ and $T=V-S$, where the source $s\in S$ and the sink $t\in T$.

### Capacity of a Cut

The capacity of a cut $(S,T)$, denoted $c(S,T)$, is the sum of capacities of all edges from $S$ to $T$, i.e., $c(S,T)=\sum_{u\in S,v\in T}c(u,v)$. We can also use $c(s,t)$ to denote $c(S,T)$.

### Minimum Cut

The minimum cut is a cut $(S,T)$ that minimizes the cut capacity $c(S,T)$.

## Proof

### Max-Flow Min-Cut Theorem

See the Max-Flow Min-Cut Theorem section on the [Max-Flow](max-flow.md) page.

## Code

### Minimum Cut

Using the **Max-Flow Min-Cut Theorem**, we can directly obtain the following code:

??? note "Reference Implementation"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <queue>
    
    constexpr int N = 1e4 + 5, M = 2e5 + 5;
    int n, m, s, t, tot = 1, lnk[N], ter[M], nxt[M], val[M], dep[N], cur[N];
    
    void add(int u, int v, int w) {
      ter[++tot] = v, nxt[tot] = lnk[u], lnk[u] = tot, val[tot] = w;
    }
    
    void addedge(int u, int v, int w) { add(u, v, w), add(v, u, 0); }
    
    int bfs(int s, int t) {
      memset(dep, 0, sizeof(dep));
      memcpy(cur, lnk, sizeof(lnk));
      std::queue<int> q;
      q.push(s), dep[s] = 1;
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = lnk[u]; i; i = nxt[i]) {
          int v = ter[i];
          if (val[i] && !dep[v]) q.push(v), dep[v] = dep[u] + 1;
        }
      }
      return dep[t];
    }
    
    int dfs(int u, int t, int flow) {
      if (u == t) return flow;
      int ans = 0;
      for (int &i = cur[u]; i && ans < flow; i = nxt[i]) {
        int v = ter[i];
        if (val[i] && dep[v] == dep[u] + 1) {
          int x = dfs(v, t, std::min(val[i], flow - ans));
          if (x) val[i] -= x, val[i ^ 1] += x, ans += x;
        }
      }
      if (ans < flow) dep[u] = -1;
      return ans;
    }
    
    int dinic(int s, int t) {
      int ans = 0;
      while (bfs(s, t)) {
        int x;
        while ((x = dfs(s, t, 1 << 30))) ans += x;
      }
      return ans;
    }
    
    int main() {
      scanf("%d%d%d%d", &n, &m, &s, &t);
      while (m--) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addedge(u, v, w);
      }
      printf("%d\n", dinic(s, t));
      return 0;
    }
    ```

### Finding the Cut

We can find all vertices in set $S$ by starting a DFS from the source $s$, traversing only edges with residual capacity greater than $0$.

```cpp
void dfs(int u) {
  vis[u] = 1;
  for (int i = lnk[u]; i; i = nxt[i]) {
    int v = ter[i];
    if (!vis[v] && val[i]) dfs(v);
  }
}
```

### Minimum Number of Cut Edges

If we need to minimize the number of cut edges under the constraint of a minimum cut, we first find the minimum cut. Then we change the capacity of non-saturated edges to $\infty$ and saturated edges to $1$, and run the minimum cut algorithm again to find the minimum number of cut edges. If there is no minimum cut constraint, simply set the capacity of all edges to $1$ and run the minimum cut algorithm.

## Problem Model 1

There are $n$ items and two sets $A$ and $B$. If an item is not placed in set $A$, it costs $a_i$; if not placed in set $B$, it costs $b_i$. There are also constraints of the form $u_i, v_i, w_i$, meaning that if $u_i$ and $v_i$ are not in the same set, it costs $w_i$. Each item must belong to exactly one set. Find the minimum total cost.

This is a classic **"either-or"** minimum cut problem. For each set, we create a source $s$ and a sink $t$. For the $i$-th item, we add an edge from $s$ with capacity $a_i$ and an edge to $t$ with capacity $b_i$. For each constraint $u, v, w$, we add a bidirectional edge between $u$ and $v$ with capacity $w$.

When the source and sink are disconnected, it means all these vertices have chosen the same set. Cutting an edge connected to $s$ or $t$ means not putting the item in set $A$ or $B$. Cutting an edge between items means these two items are not in the same set.

The minimum cut equals the minimum cost.

## Problem Model 2

Maximum weight closure of a graph: given a directed graph where each vertex has a weight (positive, negative, or zero), select a subgraph with maximum total weight such that for every vertex in the subgraph, all its successors are also in the subgraph.

Solution: Create a super source $s$ and a super sink $t$. If vertex $u$ has positive weight, add an edge from $s$ to $u$ with weight equal to the vertex weight. If vertex $u$ has negative weight, add an edge from $u$ to $t$ with weight equal to the negation of the vertex weight. Change all original edges to have weight $\infty$. Run the maximum flow algorithm. The sum of all positive weights minus the maximum flow is the answer.

Some key observations for the proof:

1. Every valid subgraph corresponds to a cut in the flow network. Since any cut divides the network into two parts, the part connected to $s$ has no edges pointing to the other part, satisfying the closure condition. This is both necessary and sufficient.

2. Edges removed by a minimum cut must be connected to either $s$ or $t$. Otherwise, the edge weight would be $\infty$, which cannot be part of a minimum cut.

3. For the selected subgraph, total weight = sum of all positive weights - sum of weights of unselected positive vertices + sum of weights of selected negative vertices. When we don't select a positive vertex, its edge to $s$ is cut. When we select a negative vertex, its edge to $t$ is cut. The sum of weights of cut edges equals the cut capacity. Therefore: total weight = sum of all positive weights - cut capacity.

4. Hence: maximum weight = sum of all positive weights - minimum cut = sum of all positive weights - maximum flow.

## Exercises

-   ["USACO 4.4" Pollutant Control](https://www.luogu.com.cn/problem/P1344)
-   ["USACO 5.4" Telecowmunication](https://www.luogu.com.cn/problem/P1345)
-   [Luogu 1361 - Little M's Crops](https://www.luogu.com.cn/problem/P1361)
-   ["SHOI 2007" Voting](https://www.luogu.com.cn/problem/P2057)
-   [Space Flight Plan Problem](https://www.luogu.com.cn/problem/P2762)
