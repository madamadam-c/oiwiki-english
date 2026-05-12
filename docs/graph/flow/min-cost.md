Before reading this article, please see the definitions in [Network Flow Introduction](../flow.md).

## Minimum-Cost Flow

Given a network $G=(V,E)$, each edge has a capacity limit $c(u,v)$ and a unit flow cost $w(u,v)$.

When the flow on $(u,v)$ is $f(u,v)$, the cost incurred is $f(u,v)\times w(u,v)$.

$w$ also satisfies skew-symmetry, i.e., $w(u,v)=-w(v,u)$.

The maximum flow with minimum total cost in this network is called the **minimum-cost maximum flow**, which minimizes $\sum_{(u,v)\in E}f(u,v)\times w(u,v)$ while maximizing $\sum_{(s,v)\in E}f(s,v)$.

## SSP Algorithm

The SSP (Successive Shortest Path) algorithm is a greedy algorithm. Its idea is to find the augmenting path with minimum unit cost and augment along it, until no augmenting path exists in the graph.

If the graph contains cycles with negative total unit cost, the SSP algorithm cannot correctly find the minimum-cost maximum flow. In this case, a cycle-canceling algorithm must be used first to eliminate negative cycles.

### Proof

We prove the correctness of the SSP algorithm using mathematical induction and proof by contradiction.

Let the minimum cost for flow $i$ be $f_i$. We assume the initial network has **no negative cycles**, in which case $f_0=0$.

Assume the SSP algorithm produces $f_i$ as the minimum cost. Based on $f_i$, we find the shortest augmenting path and obtain $f_{i+1}$. At this point, $f_{i+1}-f_i$ equals the length of this shortest augmenting path.

Assume there exists a smaller $f_{i+1}$, call it $f'_{i+1}$. Since $f_{i+1}-f_i$ is already the shortest augmenting path, $f'_{i+1}-f_i$ must correspond to an augmenting path passing through **at least one negative cycle**.

A contradiction emerges: if such an augmenting path through at least one negative cycle exists, then $f_i$ is not the minimum cost. Because adding flow to this negative cycle would reduce the cost of $f_i$ without increasing the flow from $s$.

Therefore, the SSP algorithm correctly computes the minimum-cost maximum flow for networks without negative cycles.

### Time Complexity

If using [Bellman-Ford algorithm](../shortest-path.md#bellmanford-algorithm) for shortest paths, the time to find each augmenting path is $O(nm)$. Let the maximum flow of the network be $f$, then the worst-case time complexity is $O(nmf)$. In fact, the SSP algorithm is [pseudo-polynomial time](../../misc/cc-basic.md#pseudo-polynomial-time).

???+ note "Why is the SSP algorithm pseudo-polynomial time?"
    The time complexity upper bound of the SSP algorithm is $O(nmf)$, which is a polynomial in the value domain, so it is pseudo-polynomial time.
    
    A network with $m=n^2, f=2^{n/2}$ can be constructed[^note1] to make the SSP algorithm reach $O(n^3 2^{n/2})$, so the SSP algorithm is not polynomial time.

### Implementation

Simply replace the augmenting path finding process in the EK algorithm or Dinic algorithm with a shortest path algorithm that finds the augmenting path with minimum unit cost.

??? note "EK-based Implementation"
    ```cpp
    struct qxx {
      int nex, t, v, c;
    };
    
    qxx e[M];
    int h[N], cnt = 1;
    
    void add_path(int f, int t, int v, int c) {
      e[++cnt] = qxx{h[f], t, v, c}, h[f] = cnt;
    }
    
    void add_flow(int f, int t, int v, int c) {
      add_path(f, t, v, c);
      add_path(t, f, 0, -c);
    }
    
    int dis[N], pre[N], incf[N];
    bool vis[N];
    
    bool spfa() {
      memset(dis, 0x3f, sizeof(dis));
      queue<int> q;
      q.push(s), dis[s] = 0, incf[s] = INF, incf[t] = 0;
      while (q.size()) {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = h[u]; i; i = e[i].nex) {
          const int &v = e[i].t, &w = e[i].v, &c = e[i].c;
          if (!w || dis[v] <= dis[u] + c) continue;
          dis[v] = dis[u] + c, incf[v] = min(w, incf[u]), pre[v] = i;
          if (!vis[v]) q.push(v), vis[v] = true;
        }
      }
      return incf[t];
    }
    
    int maxflow, mincost;
    
    void update() {
      maxflow += incf[t];
      for (int u = t; u != s; u = e[pre[u] ^ 1].t) {
        e[pre[u]].v -= incf[t], e[pre[u] ^ 1].v += incf[t];
        mincost += incf[t] * e[pre[u]].c;
      }
    }
    
    // Usage: while(spfa())update();
    ```

??? note "Dinic-based Implementation"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <queue>
    
    constexpr int N = 5e3 + 5, M = 1e5 + 5;
    constexpr int INF = 0x3f3f3f3f;
    int n, m, tot = 1, lnk[N], cur[N], ter[M], nxt[M], cap[M], cost[M], dis[N], ret;
    bool vis[N];
    
    void add(int u, int v, int w, int c) {
      ter[++tot] = v, nxt[tot] = lnk[u], lnk[u] = tot, cap[tot] = w, cost[tot] = c;
    }
    
    void addedge(int u, int v, int w, int c) { add(u, v, w, c), add(v, u, 0, -c); }
    
    bool spfa(int s, int t) {
      memset(dis, 0x3f, sizeof(dis));
      memcpy(cur, lnk, sizeof(lnk));
      std::queue<int> q;
      q.push(s), dis[s] = 0, vis[s] = true;
      while (!q.empty()) {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int i = lnk[u]; i; i = nxt[i]) {
          int v = ter[i];
          if (cap[i] && dis[v] > dis[u] + cost[i]) {
            dis[v] = dis[u] + cost[i];
            if (!vis[v]) q.push(v), vis[v] = true;
          }
        }
      }
      return dis[t] != INF;
    }
    
    int dfs(int u, int t, int flow) {
      if (u == t) return flow;
      vis[u] = true;
      int ans = 0;
      for (int &i = cur[u]; i && ans < flow; i = nxt[i]) {
        int v = ter[i];
        if (!vis[v] && cap[i] && dis[v] == dis[u] + cost[i]) {
          int x = dfs(v, t, std::min(cap[i], flow - ans));
          if (x) ret += x * cost[i], cap[i] -= x, cap[i ^ 1] += x, ans += x;
        }
      }
      vis[u] = false;
      return ans;
    }
    
    int mcmf(int s, int t) {
      int ans = 0;
      while (spfa(s, t)) {
        int x;
        while ((x = dfs(s, t, INF))) ans += x;
      }
      return ans;
    }
    
    int main() {
      int s, t;
      scanf("%d%d%d%d", &n, &m, &s, &t);
      while (m--) {
        int u, v, w, c;
        scanf("%d%d%d%d", &u, &v, &w, &c);
        addedge(u, v, w, c);
      }
      int ans = mcmf(s, t);
      printf("%d %d\n", ans, ret);
      return 0;
    }
    ```

### Primal-Dual Algorithm

The time complexity of using Bellman-Ford for shortest paths is $O(nm)$, which is inferior to Dijkstra's algorithm[^note2] on both sparse and dense graphs. However, the network may contain edges with negative unit cost, so Dijkstra's algorithm cannot be directly used.

The Primal-Dual algorithm is similar to [Johnson's all-pairs shortest path algorithm](../shortest-path.md#johnson-全源最短路径算法). By assigning a potential to each vertex, all edge costs (edge weights) in the network become non-negative, allowing Dijkstra's algorithm to find the augmenting path with minimum unit cost.

First, run a shortest path algorithm to find the shortest distance from the source to each vertex (which is the initial potential of that vertex) $h_i$. Then, similar to Johnson's algorithm, for an edge from $u$ to $v$ with unit cost $w$, reset its weight to $w+h_u-h_v$.

It can be observed that after setting potentials this way, the shortest path in the new network corresponds exactly to the shortest path in the original network. The proof was given when introducing Johnson's algorithm, so it is not elaborated here.

Unlike conventional shortest path problems, the graph changes after each augmentation, so the potentials of each vertex need to be updated.

How to update? First, the conclusion: let $d'_i$ be the shortest distance from the source to vertex $i$ after augmentation (the distance after resetting edge weights), then we only need to add $d'_i$ to $h_i$. Below, we prove that after this update, all edge weights in the graph are non-negative.

It is easy to observe that after one augmentation, since some edges $(i,j)$ are on the augmenting path, corresponding $(j,i)$ edges appear in the residual network, and it must satisfy $d'_i+(w(i,j)+h_i-h_j)=d'_j$ (otherwise edge $(i,j)$ would not be on the augmenting path). After rearrangement, we get $w(j,i)+(h_j+d'_j)-(h_i+d'_i)=0$. Therefore, the new edges have non-negative weight.

For original edges, before augmentation, $d'_i+(w(i,j)+h_i-h_j) - d'_j \geq 0$, so $w(i,j)+(d'_i+h_i)-(d'_j+h_j) \geq 0$, meaning using $h_i+d'_i$ as the new potential does not make the weight of edge $(i,j)$ negative.

In summary, after augmentation, all edge weights are non-negative, so Dijkstra's algorithm can correctly find the shortest path in the graph.

??? note "Reference Implementation"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <queue>
    constexpr int INF = 0x3f3f3f3f;
    using namespace std;
    
    struct edge {
      int v, f, c, next;
    } e[100005];
    
    struct node {
      int v, e;
    } p[10005];
    
    struct mypair {
      int dis, id;
    
      bool operator<(const mypair& a) const { return dis > a.dis; }
    
      mypair(int d, int x) { dis = d, id = x; }
    };
    
    int head[5005], dis[5005], vis[5005], h[5005];
    int n, m, s, t, cnt = 1, maxf, minc;
    
    void addedge(int u, int v, int f, int c) {
      e[++cnt].v = v;
      e[cnt].f = f;
      e[cnt].c = c;
      e[cnt].next = head[u];
      head[u] = cnt;
    }
    
    bool dijkstra() {
      priority_queue<mypair> q;
      for (int i = 1; i <= n; i++) dis[i] = INF;
      memset(vis, 0, sizeof(vis));
      dis[s] = 0;
      q.push(mypair(0, s));
      while (!q.empty()) {
        int u = q.top().id;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; i; i = e[i].next) {
          int v = e[i].v, nc = e[i].c + h[u] - h[v];
          if (e[i].f && dis[v] > dis[u] + nc) {
            dis[v] = dis[u] + nc;
            p[v].v = u;
            p[v].e = i;
            if (!vis[v]) q.push(mypair(dis[v], v));
          }
        }
      }
      return dis[t] != INF;
    }
    
    void spfa() {
      queue<int> q;
      memset(h, 63, sizeof(h));
      h[s] = 0, vis[s] = 1;
      q.push(s);
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = head[u]; i; i = e[i].next) {
          int v = e[i].v;
          if (e[i].f && h[v] > h[u] + e[i].c) {
            h[v] = h[u] + e[i].c;
            if (!vis[v]) {
              vis[v] = 1;
              q.push(v);
            }
          }
        }
      }
    }
    
    int main() {
      scanf("%d%d%d%d", &n, &m, &s, &t);
      for (int i = 1; i <= m; i++) {
        int u, v, f, c;
        scanf("%d%d%d%d", &u, &v, &f, &c);
        addedge(u, v, f, c);
        addedge(v, u, 0, -c);
      }
      spfa();  // Compute initial potentials first
      while (dijkstra()) {
        int minf = INF;
        for (int i = 1; i <= n; i++) h[i] += dis[i];
        for (int i = t; i != s; i = p[i].v) minf = min(minf, e[p[i].e].f);
        for (int i = t; i != s; i = p[i].v) {
          e[p[i].e].f -= minf;
          e[p[i].e ^ 1].f += minf;
        }
        maxf += minf;
        minc += minf * h[t];
      }
      printf("%d %d\n", maxf, minc);
      return 0;
    }
    ```

## Exercises

-   ["Luogu 3381" Template: Minimum-Cost Maximum Flow](https://www.luogu.com.cn/problem/P3381)
-   ["Luogu 4452" Flight Scheduling](https://www.luogu.com.cn/problem/P4452)
-   ["SDOI 2009" Morning Run](https://www.luogu.com.cn/problem/P2153)
-   ["SCOI 2007" Car Repair](https://www.luogu.com.cn/problem/P2053)
-   ["HAOI 2010" Ordering](https://www.luogu.com.cn/problem/P2517)
-   ["NOI 2012" Gourmet Festival](https://loj.ac/problem/2674)

## References and Notes

[^note1]: For detailed construction method, refer to [min_25's blog](https://web.archive.org/web/20211009144446/https://min-25.hatenablog.com/entry/2018/03/19/235802).

[^note2]: On sparse graphs, using heap optimization can achieve $O(m \log n)$ time complexity, and on dense graphs without heap optimization, $O(n^2)$ can be achieved.
