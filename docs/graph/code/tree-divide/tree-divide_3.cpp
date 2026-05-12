#include <algorithm>
#include <iostream>
using namespace std;
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
constexpr int N = 200005;
int h[N], nxt[N * 2], to[N * 2], c[N], gr;

void tu(int x, int y) { to[++gr] = y, nxt[gr] = h[x], h[x] = gr; }

using ll = long long;
int n, nn, siz[N], mn, rt;
bool vis[N];

void get_root(int u, int f) {
  siz[u] = 1;
  int mx = 0;
  for (int i = h[u]; i; i = nxt[i]) {
    int d = to[i];
    if (vis[d] || d == f) continue;
    get_root(d, u);
    siz[u] += siz[d];
    mx = max(mx, siz[d]);
  }
  mx = max(mx, nn - siz[u]);
  if (mx < mn) mn = mx, rt = u;
}

ll ans[N], sum;
int cnt[N], v[N];
// sum maintains the sum of cnt[i] in real time
int nowrt;

void get_dis(int u, int f, int now) {  // now is the number of colors on the current tree chain, excluding u
  siz[u] = 1;
  if (!v[c[u]]) {
    sum -= cnt[c[u]];  // Subtract color information that already appeared in previous subtrees
    now++;
  }
  v[c[u]]++;
  ans[u] += sum + now * siz[nowrt];  // Count contributions to u from paths passing through u
  for (int i = h[u]; i; i = nxt[i]) {
    int d = to[i];
    if (d == f || vis[d]) continue;
    get_dis(d, u, now);
    siz[u] += siz[d];
  }
  v[c[u]]--;
  if (!v[c[u]]) {
    sum += cnt[c[u]];  // Backtrack
  }
}

void get_cnt(int u, int f) {
  if (!v[c[u]]) {
    cnt[c[u]] += siz[u];
    sum += siz[u];  // Merge information from the subtree just traversed into cnt[i] and sum
  }
  v[c[u]]++;
  for (int i = h[u]; i; i = nxt[i]) {
    int d = to[i];
    if (vis[d] || d == f) continue;
    get_cnt(d, u);
  }
  v[c[u]]--;
}

void clear(int u, int f, int now) {
  if (!v[c[u]]) now++;
  v[c[u]]++;
  ans[u] -= now;
  ans[nowrt] += now;
  for (int i = h[u]; i; i = nxt[i]) {
    int d = to[i];
    if (vis[d] || d == f) continue;
    clear(d, u, now);
  }
  v[c[u]]--;
  cnt[c[u]] = 0;
}

void clear2(int u, int f) {
  cnt[c[u]] = 0;
  for (int i = h[u]; i; i = nxt[i]) {
    int d = to[i];
    if (vis[d] || d == f) continue;
    clear2(d, u);
  }
}

int son[N];

void divid(int u) {
  vis[u] = true;
  int tot = 0;
  nowrt = u;
  ans[u]++;
  for (int i = h[u]; i; i = nxt[i]) {
    if (vis[to[i]]) continue;
    son[++tot] = to[i];
  }
  siz[u] = sum = cnt[c[u]] = 1;
  v[c[u]]++;
  rep(i, 1, tot) {  // Count contributions from node pairs between each subtree and all previous subtrees
    int d = son[i];
    get_dis(d, u, 0);
    get_cnt(d, u);
    siz[u] += siz[d];
    cnt[c[u]] += siz[d];
    sum += siz[d];
  }
  clear2(u, 0);  // Clear arrays; remember not to use memset
  siz[u] = sum = cnt[c[u]] = 1;
  for (int i = tot; i >= 1;
       --i) {  // Count contributions from node pairs between each subtree and all later subtrees
    int d = son[i];
    get_dis(d, u, 0);
    get_cnt(d, u);
    siz[u] += siz[d];
    cnt[c[u]] += siz[d];
    sum += siz[d];
  }
  v[c[u]]--;
  clear(u, 0, 0);                      // Clear while counting answers
  for (int i = h[u]; i; i = nxt[i]) {  // Continue centroid decomposition downward
    int d = to[i];
    if (vis[d]) continue;
    nn = siz[d], mn = n + 1, rt = 0;
    get_root(d, u);
    divid(rt);
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n;
  int u, v;
  rep(i, 1, n) cin >> c[i];
  rep(i, 2, n) cin >> u >> v, tu(u, v), tu(v, u);
  rt = 0, nn = n, mn = n + 1;
  get_root(1, 0);
  divid(rt);
  rep(i, 1, n) cout << ans[i] << '\n';
  return 0;
}
