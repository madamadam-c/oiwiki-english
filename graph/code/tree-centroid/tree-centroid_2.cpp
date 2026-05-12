// Verified by https://codeforces.com/gym/101649/problem/G.
// Codes associating I/O streams to files are omitted.
#include <iostream>
#include <vector>
using namespace std;

// --8<-- [start:core]
const int MAXN = 50005;

int n;
// This code assumes node indices start from 1, i.e., i in [1,n]
int siz[MAXN],  // The size of this node: all subtree nodes plus the node itself
    weight[MAXN];  // The weight of this node, i.e., the maximum size among all subtrees
vector<int> centroids;  // Records tree centroids by node index
vector<int> g[MAXN];

void dfs(int cur, int fa) {  // cur denotes the current node
  siz[cur] = 1;
  weight[cur] = 0;
  for (int v : g[cur]) {
    if (v != fa) {  // v denotes the node this directed edge points to
      dfs(v, cur);
      siz[cur] += siz[v];
      weight[cur] = max(weight[cur], siz[v]);
    }
  }
  weight[cur] = max(weight[cur], n - siz[cur]);
  if (weight[cur] <= n / 2) {  // Count according to the definition of a tree centroid
    centroids.push_back(cur);
  }
}

void get_centroids() { dfs(1, 0); }

// --8<-- [end:core]
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  get_centroids();
  if (centroids.size() == 1)
    cout << centroids.front() << '\n';
  else
    cout << min(centroids.front(), centroids.back()) << " "
         << max(centroids.front(), centroids.back()) << '\n';
  return 0;
}
