#include <cstdio>
#include <vector>
using namespace std;

constexpr int N = 2e5 + 5;

int n, m;

// g[u]: stores nodes adjacent to u
vector<int> g[N];

// sz: subtree size
// son[u]: index of node u's heavy child
// col: node color
// dfn[u]: DFS order of node u
// bottom[u]: maximum DFS order among nodes in u's subtree
// totdfn: node counter, also the current maximum DFS order among visited nodes
// fa[u]: parent index of node u
// top[u]: top node of the heavy chain containing node u
// rnk[i]: node whose DFS order is i
// ans[u]: stores the answer
// cnt[i]: number of nodes with color i
// totColor: number of colors that have appeared so far
int sz[N], son[N], col[N], dfn[N], fa[N], bottom[N], totdfn;
int top[N], rnk[N];
int ans[N], cnt[N], totColor;

void add(int u) {
  if (cnt[col[u]] == 0) ++totColor;
  cnt[col[u]]++;
}

void del(int u) {
  cnt[col[u]]--;
  if (cnt[col[u]] == 0) --totColor;
}

int getAns() { return totColor; }

void dfs0(int u, int p) {
  sz[u] = 1;
  fa[u] = p;
  for (int v : g[u])
    if (v != p) {
      dfs0(v, u);
      sz[u] += sz[v];
      if (!son[u] || sz[son[u]] < sz[v]) son[u] = v;
    }
}

void dfs1(int u, int t) {
  rnk[bottom[u] = dfn[u] = ++totdfn] = u;
  top[u] = t;
  if (!son[u]) return;
  dfs1(son[u], t);
  for (int v : g[u])
    if (v != fa[u] && v != son[u]) dfs1(v, v);
  bottom[u] = totdfn;
}

void dsu_on_tree() {
  for (int i = totdfn; i >= 1; i--) {
    int u = rnk[i];
    for (int v : g[u])
      if (v != fa[u] && v != son[u]) {
        for (int i = dfn[v]; i <= bottom[v]; i++) {
          add(rnk[i]);
        }
      }
    add(u);
    ans[u] = getAns();
    if (u == top[u]) {
      for (int i = dfn[u]; i <= bottom[u]; i++) {
        del(rnk[i]);
      }
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) scanf("%d", &col[i]);
  dfs0(1, 1);
  dfs1(1, 1);
  dsu_on_tree();
  scanf("%d", &m);
  for (int i = 1; i <= m; i++) {
    int q;
    scanf("%d", &q);
    printf("%d\n", ans[q]);
  }
  return 0;
}
