#include <cstring>
#include <iostream>
#include <vector>

constexpr int MXN = 40005;
using namespace std;
vector<int> v[MXN];
vector<int> w[MXN];

int fa[MXN][31], cost[MXN][31], dep[MXN];
int n, m;
int a, b, c;

// dfs prepares for the LCA algorithm. It takes two parameters: the DFS start node and its parent.
void dfs(int root, int fno) {
  // Initialization: the 2^0 = 1-th ancestor is its parent, and dep is one more than the parent's dep.
  fa[root][0] = fno;
  dep[root] = dep[fa[root][0]] + 1;
  // Initialization for other ancestors: the 2^i-th ancestor is the 2^(i-1)-th ancestor
  // of the 2^(i-1)-th ancestor.
  for (int i = 1; i < 31; ++i) {
    fa[root][i] = fa[fa[root][i - 1]][i - 1];
    cost[root][i] = cost[fa[root][i - 1]][i - 1] + cost[root][i - 1];
  }
  // Traverse child nodes for DFS.
  int sz = v[root].size();
  for (int i = 0; i < sz; ++i) {
    if (v[root][i] == fno) continue;
    cost[v[root][i]][0] = w[root][i];
    dfs(v[root][i], root);
  }
}

// lca. Use binary lifting to compute the LCA of x and y.
int lca(int x, int y) {
  // Make y deeper than x.
  if (dep[x] > dep[y]) swap(x, y);
  // Move y and x to the same depth.
  int tmp = dep[y] - dep[x], ans = 0;
  for (int j = 0; tmp; ++j, tmp >>= 1)
    if (tmp & 1) ans += cost[y][j], y = fa[y][j];
  // If y = x now, then x and y are both their own ancestors.
  if (y == x) return ans;
  // Otherwise, find the first two nodes that are not their ancestors.
  for (int j = 30; j >= 0 && y != x; --j) {
    if (fa[x][j] != fa[y][j]) {
      ans += cost[x][j] + cost[y][j];
      x = fa[x][j];
      y = fa[y][j];
    }
  }
  // Return the result.
  ans += cost[x][0] + cost[y][0];
  return ans;
}

void Solve() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // Initialize the ancestor array fa, cost, and depth dep.
  memset(fa, 0, sizeof(fa));
  memset(cost, 0, sizeof(cost));
  memset(dep, 0, sizeof(dep));
  // Read the tree: there are n nodes and m queries, each asking for the LCA of two nodes.
  cin >> n >> m;
  // Initialize tree edges and edge weights.
  for (int i = 1; i <= n; ++i) {
    v[i].clear();
    w[i].clear();
  }
  for (int i = 1; i < n; ++i) {
    cin >> a >> b >> c;
    v[a].push_back(b);
    v[b].push_back(a);
    w[a].push_back(c);
    w[b].push_back(c);
  }
  // Run DFS to compute LCA information.
  dfs(1, 0);
  for (int i = 0; i < m; ++i) {
    cin >> a >> b;
    cout << lca(a, b) << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--) Solve();
  return 0;
}
