## Definition

Edges are directed, with no cycles.

The English name is Directed Acyclic Graph, abbreviated as DAG.

## Properties

-   A graph that can be [topologically sorted](./topo.md) must be a directed acyclic graph;

    If there is a cycle, then any two nodes on the cycle cannot satisfy the condition in any ordering.

-   A directed acyclic graph can always be topologically sorted;

    (Induction) Assume that all directed acyclic graphs with at most $k$ nodes can be topologically sorted. Then for a graph with exactly $k$ nodes, consider the situation after performing the first step of topological sorting.

## Detection

How to determine whether a graph is a directed acyclic graph?

Simply check if it can be [topologically sorted](./topo.md).

Alternatively, perform a [DFS](../search/dfs.md) on the graph and check if there are any non-tree edges (back edges) connecting to ancestors in the DFS tree. If there are, then there is a cycle.

## Applications

### DP for Longest/Shortest Path

On general graphs, the optimal time complexity for finding the single-source longest/shortest path is $O(nm)$ ([Bellman-Ford algorithm](./shortest-path.md#bellmanford-algorithm), applicable to graphs with negative weights) or $O(m \log m)$ ([Dijkstra algorithm](./shortest-path.md#dijkstra-algorithm), applicable to graphs without negative weights).

However, on DAGs, we can use DP to find the longest/shortest path, optimizing the time complexity to $O(n + m)$. The state transition is $dis_v = \min(dis_v, dis_u + w_{u,v})$ or $dis_v = \max(dis_v, dis_u + w_{u,v})$.

After topological sorting, traverse each node in topological order and use the current node to update subsequent nodes.

```cpp
struct edge {
  int v, w;
};

int n, m;
vector<edge> e[MAXN];
vector<int> L;                               // Stores the topological sort result
int max_dis[MAXN], min_dis[MAXN], in[MAXN];  // in stores the in-degree of each node

void toposort() {  // Topological sort
  queue<int> S;
  memset(in, 0, sizeof(in));
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < e[i].size(); j++) {
      in[e[i][j].v]++;
    }
  }
  for (int i = 1; i <= n; i++)
    if (in[i] == 0) S.push(i);
  while (!S.empty()) {
    int u = S.front();
    S.pop();
    L.push_back(u);
    for (int i = 0; i < e[u].size(); i++) {
      if (--in[e[u][i].v] == 0) {
        S.push(e[u][i].v);
      }
    }
  }
}

void dp(int s) {  // Find single-source longest/shortest path starting from s
  toposort();     // Perform topological sort first
  memset(min_dis, 0x3f, sizeof(min_dis));
  memset(max_dis, 0, sizeof(max_dis));
  min_dis[s] = 0;
  for (int i = 0; i < L.size(); i++) {
    int u = L[i];
    for (int j = 0; j < e[u].size(); j++) {
      min_dis[e[u][j].v] = min(min_dis[e[u][j].v], min_dis[u] + e[u][j].w);
      max_dis[e[u][j].v] = max(max_dis[e[u][j].v], max_dis[u] + e[u][j].w);
    }
  }
}
```

See also: [DP on DAG](../dp/dag.md).