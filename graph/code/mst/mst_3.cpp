#include <algorithm>
#include <iostream>
using namespace std;

int fa[1010];  // Define parent
int n, m, k;

struct edge {
  int u, v, w;
};

int l;
edge g[10010];

void add(int u, int v, int w) {
  l++;
  g[l].u = u;
  g[l].v = v;
  g[l].w = w;
}

// Standard DSU
int findroot(int x) { return fa[x] == x ? x : fa[x] = findroot(fa[x]); }

void Merge(int x, int y) {
  x = findroot(x);
  y = findroot(y);
  fa[x] = y;
}

bool cmp(edge A, edge B) { return A.w < B.w; }

// Kruskal algorithm
void kruskal() {
  int tot = 0;  // Stores the number of selected edges
  int ans = 0;  // Stores the total cost
  for (int i = 1; i <= m; i++) {
    int xr = findroot(g[i].u), yr = findroot(g[i].v);
    if (xr != yr) {        // If the parents are different
      Merge(xr, yr);       // Merge
      tot++;               // Increase edge count
      ans += g[i].w;       // Increase cost
      if (tot == n - k) {  // Check whether the selected edge count satisfies k marshmallows
        cout << ans << '\n';
        return;
      }
    }
  }
  cout << "No Answer\n";  // Cannot connect
}

int main() {
  cin >> n >> m >> k;
  if (n == k) {  // Handle boundary case separately
    cout << "0\n";
    return 0;
  }
  for (int i = 1; i <= n; i++) {  // Initialize
    fa[i] = i;
  }
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    add(u, v, w);  // Add edge
  }
  sort(g + 1, g + m + 1, cmp);  // Sort by edge weight first
  kruskal();
  return 0;
}
