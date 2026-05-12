/*
Luogu P3388 [Template] Cut Vertex (Articulation Point)
*/
#include <iostream>
#include <vector>
using namespace std;
int n, m;  // n: number of vertices, m: number of edges
int dfn[100001], low[100001], idx, res;
// dfn: records the timestamp of each vertex
// low: smallest index reachable without going through the parent; idx: timestamp; res: answer count
bool vis[100001], flag[100001];  // flag: answer marker; vis: duplicate marker
vector<int> edge[100001];        // Stores the graph

void Tarjan(int u, int fa) {  // u is the current vertex, fa is its parent
  vis[u] = true;              // Mark visited
  low[u] = dfn[u] = ++idx;    // Assign timestamp
  int child = 0;              // Number of children of this vertex
  for (const auto &v : edge[u]) {  // Visit all neighbors of this vertex (C++11)
    if (!vis[v]) {
      child++;                       // Add one child
      Tarjan(v, u);                  // Continue DFS
      low[u] = min(low[u], low[v]);  // Update the smallest reachable vertex index
      if (fa != u && low[v] >= dfn[u] && !flag[u]) {  // Main logic
        // If u is not the root, the smallest vertex reachable without going through the parent
        // satisfies the articulation-point condition, and u has not been marked yet
        // The condition means deleting u disconnects the child subtree, which can reach at most u
        flag[u] = true;
        res++;  // Record answer
      }
    } else if (v != fa) {
      // If this vertex is not the parent, update the smallest reachable vertex index
      low[u] = min(low[u], dfn[v]);
    }
  }
  // Main logic: the root needs at least 2 children
  if (fa == u && child >= 2 && !flag[u]) {
    flag[u] = true;
    res++;  // Record answer
  }
}

int main() {
  cin >> n >> m;                  // Read input
  for (int i = 1; i <= m; i++) {  // Note that vertices start from 1
    int x, y;
    cin >> x >> y;
    edge[x].push_back(y);
    edge[y].push_back(x);
  }  // Store the graph using vector
  for (int i = 1; i <= n; i++)  // The graph may be disconnected
    if (!vis[i]) {
      idx = 0;       // Initialize timestamp to 0
      Tarjan(i, i);  // Start from vertex i, with itself as parent
    }
  cout << res << endl;
  for (int i = 1; i <= n; i++)
    if (flag[i]) cout << i << " ";  // Output result
  return 0;
}
