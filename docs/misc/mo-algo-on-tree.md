author: StudyingFather, Backl1ght, countercurrent-time, Ir1d, greyqz, MicDZ, ouuan, Linky

## Mo's Algorithm on Trees with Bracket Order

Ordinary Mo's algorithm can only handle linear problems, so we need to force the tree into a sequence.

We can obtain the bracket order of the tree, divide the bracket order into blocks, and run Mo's algorithm on this bracket order.

How exactly do we do this?

### Procedure

Run DFS on a tree. When DFS reaches node x, `push_back(x)`; when DFS finishes node x, directly `push_back(-x)`. Then, when moving the pointers:

-   The newly added value is x  --->`add(x)`
-   The newly added value is - x --->`del(x)`
-   The newly removed value is x  --->`del(x)`
-   The newly removed value is - x --->`add(x)`

In this way, we process a tree into a sequence.

### Example

???+ note "Example [WC2013 Candy Park](https://uoj.ac/problem/58)"
    Statement: given a tree where the color of the $i$-th node is $c_i$, each query asks for a path $u_i$,$v_i$ and asks you to compute, on this path,
    
    $\sum_{c}val_c\sum_{i=1}^{cnt_c}w_i$
    
    where $val$ denotes the value of a color, $cnt$ denotes the number of occurrences of a color, and $w$ denotes the value after the color has appeared $i$ times.

#### Procedure

First turn the tree into a sequence. Then each time a node is added or deleted, this node's contribution to the answer can be obtained in $O(1)$ time, namely $val_c\times w_{cnt_{c+1}}$.

Notice that this also scans the subtree of the starting point once, producing extra contributions. What should we do?

During the scan, nodes in the starting point's subtree will definitely be scanned twice, so their contribution is 0.

So we can maintain a $vis$ array. Every time node x is scanned, xor $vis_x$ by 1.

If $vis_x=0$, the contribution of this node can be ignored.

Therefore, this can be solved with Mo's algorithm on trees.

For modifications, just add one time dimension, turning it into Mo's algorithm on trees with modifications.

Finally, because the included interval may not contain the LCA, in that case the extra contribution should be removed, and then the solution is complete.

#### Implementation

??? note "Reference code"
    ```cpp
    #include <algorithm>
    #include <cmath>
    #include <cstdio>
    using namespace std;
    
    constexpr int MAXN = 200010;
    
    int f[MAXN], g[MAXN], id[MAXN], head[MAXN], cnt, last[MAXN], dep[MAXN],
        fa[MAXN][22], v[MAXN], w[MAXN];
    int block, index, n, m, q;
    int pos[MAXN], col[MAXN], app[MAXN];
    bool vis[MAXN];
    long long ans[MAXN], cur;
    
    struct edge {
      int to, nxt;
    } e[MAXN];
    
    int cnt1 = 0, cnt2 = 0;  // Timestamp
    
    struct query {
      int l, r, t, id;
    
      bool operator<(const query &b) const {
        return (pos[l] < pos[b.l]) || (pos[l] == pos[b.l] && pos[r] < pos[b.r]) ||
               (pos[l] == pos[b.l] && pos[r] == pos[b.r] && t < b.t);
      }
    } a[MAXN], b[MAXN];
    
    void addedge(int x, int y) {
      e[++cnt] = edge{y, head[x]};
      head[x] = cnt;
    }
    
    void dfs(int x) {
      id[f[x] = ++index] = x;
      for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].to != fa[x][0]) {
          fa[e[i].to][0] = x;
          dep[e[i].to] = dep[x] + 1;
          dfs(e[i].to);
        }
      }
      id[g[x] = ++index] = x;  // Bracket order
    }
    
    int lca(int x, int y) {
      if (dep[x] < dep[y]) swap(x, y);
      if (dep[x] != dep[y]) {  // Climb to the same height
        int dis = dep[x] - dep[y];
        for (int i = 20; i >= 0; i--)
          if (dis >= (1 << i)) dis -= 1 << i, x = fa[x][i];
      }
      if (x == y) return x;
      for (int i = 20; i >= 0; i--) {
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
      }
      return fa[x][0];
    }
    
    void add(int x) {
      if (vis[x])
        cur -= (long long)v[col[x]] * w[app[col[x]]--];
      else
        cur += (long long)v[col[x]] * w[++app[col[x]]];
      vis[x] ^= 1;
    }
    
    // Move along the time dimension
    void modify(int x, int t) {
      if (vis[x]) {
        add(x);
        col[x] = t;
        add(x);
      } else
        col[x] = t;
    }
    
    int main() {
      scanf("%d%d%d", &n, &m, &q);
      for (int i = 1; i <= m; i++) scanf("%d", &v[i]);
      for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
      for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        addedge(x, y);
        addedge(y, x);
      }
      for (int i = 1; i <= n; i++) {
        scanf("%d", &last[i]);
        col[i] = last[i];
      }
      dfs(1);
      for (int j = 1; j <= 20; j++)
        for (int i = 1; i <= n; i++)
              fa[i][j] = fa[fa[i][j - 1]][j - 1];  // Preprocess ancestors
      int block = pow(index, 2.0 / 3);
      for (int i = 1; i <= index; i++) {
        pos[i] = (i - 1) / block;
      }
      while (q--) {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 0) {
          b[++cnt2].l = x;
          b[cnt2].r = last[x];
          last[x] = b[cnt2].t = y;
        } else {
          if (f[x] > f[y]) swap(x, y);
          a[++cnt1] = query{lca(x, y) == x ? f[x] : g[x], f[y], cnt2, cnt1};
        }
      }
      sort(a + 1, a + cnt1 + 1);
      int L, R, T;  // Pointer coordinates
      L = R = 0;
      T = 1;
      for (int i = 1; i <= cnt1; i++) {
        while (T <= a[i].t) {
          modify(b[T].l, b[T].t);
          T++;
        }
        while (T > a[i].t) {
          modify(b[T].l, b[T].r);
          T--;
        }
        while (L > a[i].l) {
          L--;
          add(id[L]);
        }
        while (L < a[i].l) {
          add(id[L]);
          L++;
        }
        while (R > a[i].r) {
          add(id[R]);
          R--;
        }
        while (R < a[i].r) {
          R++;
          add(id[R]);
        }
        int x = id[L], y = id[R];
        int llca = lca(x, y);
        if (x != llca && y != llca) {
          add(llca);
          ans[a[i].id] = cur;
          add(llca);
        } else
          ans[a[i].id] = cur;
      }
      for (int i = 1; i <= cnt1; i++) {
        printf("%lld\n", ans[i]);
      }
      return 0;
    }
    ```

## True Mo's Algorithm on Trees

The tree Mo's algorithm above only transforms the tree into a chain. The following is the true Mo's algorithm on trees.

Since problems related to Mo's algorithm are mostly template problems, the implementation part will not be explained in much detail.

### Query ordering

First, we know that Mo's algorithm is based on block decomposition, so we need to find a way to decompose a tree into blocks to guarantee the time complexity.

Conditions:

-   The distance between nodes belonging to the same block does not exceed the given block size
-   Each block must contain neither too many nor too few nodes
-   Every node must belong to a block
-   The distance between blocks with adjacent numbers must not be too large

After understanding these conditions, consider the problem [SCOI2005 Royal Federation](https://loj.ac/problem/2152).

Based on this problem, we only need to guarantee the last condition to solve the block decomposition problem.

??? note "Idea"
    Let lim be the desired block size. First, run DFS over the whole tree. When the size of a subtree is greater than lim, put those nodes into one block. It is easy to see that some nodes may remain for the root, so put these nodes into the last block.

    Method: use a stack to maintain the children visited with the current node as their parent. When the distance from the stack top to the parent is greater than the desired block size, pop this part of the elements and make them one block. The final remaining part forms a separate block.

    Final sorting method: if the first-dimensional timestamp is greater than the second-dimensional one, swap them. Sort by the block of the first dimension as the first key, and by the second-dimensional timestamp as the second key.

### Pointer movement

#### Procedure

It is natural to think that we can mark the nodes counted in the answer, move the pointer directly toward the target, and toggle the nodes on the path at the same time.

However, this has a problem. If both pointers initially stand on x, then x is clearly marked. When both pointers move to the same child node (and in many other cases), x should be unmarked, but in reality x remains marked, because the two pointers each mark it once and the operations cancel out.

How can we solve this?

There is an obvious property: these nodes must be some LCAs, because only at an LCA can repeated cancellation cause cancellation to fail.

Therefore, we do not mark the LCA each time. When we need to query the answer, we mark the LCA and then undo it.

#### Implementation

```cpp
// Toggle all nodes on the path except the LCA
void move(int x, int y) {
  if (dp[x] < dp[y]) swap(x, y);
  while (dp[x] > dp[y]) update(x), x = fa[x];
  while (x != y) update(x), update(y), x = fa[x], y = fa[y];
  // x!=y ensures that the LCA is not toggled
}
```

For computing LCA, we can use heavy-light decomposition. Then we can put the block decomposition step into the first DFS of HLD, and the timestamp can directly use the DFS order from the second DFS.

```cpp
int bl[100002], bls = 0;  // Block it belongs to, number of blocks
unsigned step;            // Block size
int fa[100002], dp[100002], hs[100002] = {0}, sz[100002] = {0};
// Parent node, depth, heavy child, size
stack<int> sta;

void dfs1(int x) {
  sz[x] = 1;
  unsigned ss = sta.size();
  for (int i = head[x]; i; i = nxt[i])
    if (ver[i] != fa[x]) {
      fa[ver[i]] = x;
      dp[ver[i]] = dp[x] + 1;
      dfs1(ver[i]);
      sz[x] += sz[ver[i]];
      if (sz[ver[i]] > sz[hs[x]]) hs[x] = ver[i];
      if (sta.size() - ss >= step) {
        bls++;
        while (sta.size() != ss) bl[sta.top()] = bls, sta.pop();
      }
    }
  sta.push(x);
}

// main
if (!sta.empty()) {
  bls++;  // This line is optional
  while (!sta.empty()) bl[sta.top()] = bls, sta.pop();
}
```

### Time complexity

Now comes the key point: this concerns the choice of block size.

Let the block size be $unit$:

-   For the x pointer, because the distance between nodes in each block is around $unit$, the x pointer moves $unit^2$ times in each block ($unit\times dis_{\max}$), for a total of $n\times unit$ times ($unit^2 \times (\frac{n}{unit})$).
-   For the y pointer, it moves at most $O(n)$ times in each block, for a total of $\frac{n^2}{unit}$ times ($n \times (\frac{n}{unit})$).

The sum is roughly minimized near the square root (because the block sizes in Mo's algorithm on trees are not fixed, this does not have to be followed strictly).

### Example: WC2013 Candy Park

Because there is an extra time dimension, choosing a block size around $n^{0.6}$ is about right.

??? note "Reference code"
    ```cpp
    #include <algorithm>
    #include <cmath>
    #include <cstdio>
    #include <stack>
    using namespace std;
    
    int gi() {
      int x, c, op = 1;
      while (c = getchar(), c < '0' || c > '9')
        if (c == '-') op = -op;
      x = c ^ 48;
      while (c = getchar(), c >= '0' && c <= '9')
        x = (x << 3) + (x << 1) + (c ^ 48);
      return x * op;
    }
    
    int head[100002], nxt[200004], ver[200004], tot = 0;
    
    void add(int x, int y) {
      ver[++tot] = y, nxt[tot] = head[x], head[x] = tot;
      ver[++tot] = x, nxt[tot] = head[y], head[y] = tot;
    }
    
    int bl[100002], bls = 0;
    unsigned step;
    int fa[100002], dp[100002], hs[100002] = {0}, sz[100002] = {0}, top[100002],
                                id[100002];
    stack<int> sta;
    
    void dfs1(int x) {
      sz[x] = 1;
      unsigned ss = sta.size();
      for (int i = head[x]; i; i = nxt[i])
        if (ver[i] != fa[x]) {
          fa[ver[i]] = x, dp[ver[i]] = dp[x] + 1;
          dfs1(ver[i]);
          sz[x] += sz[ver[i]];
          if (sz[ver[i]] > sz[hs[x]]) hs[x] = ver[i];
          if (sta.size() - ss >= step) {
            bls++;
            while (sta.size() != ss) bl[sta.top()] = bls, sta.pop();
          }
        }
      sta.push(x);
    }
    
    int cnt = 0;
    
    void dfs2(int x, int hf) {
      top[x] = hf, id[x] = ++cnt;
      if (!hs[x]) return;
      dfs2(hs[x], hf);
      for (int i = head[x]; i; i = nxt[i])
        if (ver[i] != fa[x] && ver[i] != hs[x]) dfs2(ver[i], ver[i]);
    }
    
    int lca(int x, int y) {
      while (top[x] != top[y]) {
        if (dp[top[x]] < dp[top[y]]) swap(x, y);
        x = fa[top[x]];
      }
      return dp[x] < dp[y] ? x : y;
    }
    
    struct qu {
      int x, y, t, id;
    
      bool operator<(const qu a) const {
        return bl[x] == bl[a.x] ? (bl[y] == bl[a.y] ? t < a.t : bl[y] < bl[a.y])
                                : bl[x] < bl[a.x];
      }
    } q[100001];
    
    int qs = 0;
    
    struct ch {
      int x, y, b;
    } upd[100001];
    
    int ups = 0;
    long long ans[100001];
    int b[100001] = {0};
    int a[100001];
    long long w[100001];
    long long v[100001];
    long long now = 0;
    bool vis[100001] = {false};
    
    void back(int t) {
      if (vis[upd[t].x]) {
        now -= w[b[upd[t].y]--] * v[upd[t].y];
        now += w[++b[upd[t].b]] * v[upd[t].b];
      }
      a[upd[t].x] = upd[t].b;
    }
    
    void change(int t) {
      if (vis[upd[t].x]) {
        now -= w[b[upd[t].b]--] * v[upd[t].b];
        now += w[++b[upd[t].y]] * v[upd[t].y];
      }
      a[upd[t].x] = upd[t].y;
    }
    
    void update(int x) {
      if (vis[x])
        now -= w[b[a[x]]--] * v[a[x]];
      else
        now += w[++b[a[x]]] * v[a[x]];
      vis[x] ^= 1;
    }
    
    void move(int x, int y) {
      if (dp[x] < dp[y]) swap(x, y);
      while (dp[x] > dp[y]) update(x), x = fa[x];
      while (x != y) update(x), update(y), x = fa[x], y = fa[y];
    }
    
    int main() {
      int n = gi(), m = gi(), k = gi();
      step = (int)pow(n, 0.6);
      for (int i = 1; i <= m; i++) v[i] = gi();
      for (int i = 1; i <= n; i++) w[i] = gi();
      for (int i = 1; i < n; i++) add(gi(), gi());
      for (int i = 1; i <= n; i++) a[i] = gi();
      for (int i = 1; i <= k; i++)
        if (gi())
          q[++qs].x = gi(), q[qs].y = gi(), q[qs].t = ups, q[qs].id = qs;
        else
          upd[++ups].x = gi(), upd[ups].y = gi();
      for (int i = 1; i <= ups; i++) upd[i].b = a[upd[i].x], a[upd[i].x] = upd[i].y;
      for (int i = ups; i; i--) back(i);
      fa[1] = 1;
      dfs1(1), dfs2(1, 1);
      if (!sta.empty()) {
        bls++;
        while (!sta.empty()) bl[sta.top()] = bls, sta.pop();
      }
      for (int i = 1; i <= n; i++)
        if (id[q[i].x] > id[q[i].y]) swap(q[i].x, q[i].y);
      sort(q + 1, q + qs + 1);
      int x = 1, y = 1, t = 0;
      for (int i = 1; i <= qs; i++) {
        if (x != q[i].x) move(x, q[i].x), x = q[i].x;
        if (y != q[i].y) move(y, q[i].y), y = q[i].y;
        int f = lca(x, y);
        update(f);
        while (t < q[i].t) change(++t);
        while (t > q[i].t) back(t--);
        ans[q[i].id] = now;
        update(f);
      }
      for (int i = 1; i <= qs; i++) printf("%lld\n", ans[i]);
      return 0;
    }
    ```
