## Definition

The minimum spanning tree on a directed graph is called the Minimum Branching (or Directed Minimum Spanning Tree, DMST).

The commonly used algorithm is Chu-Liu/Edmonds' algorithm (also known as Edmonds' algorithm), which can solve the minimum branching problem in $O(nm)$ time.

## Algorithm

1.  For each node, select the incoming edge with the minimum weight.
2.  If there are no cycles, the algorithm terminates; otherwise, contract the cycles and update distances.

## Implementation

```cpp
bool solve() {
  ans = 0;
  int u, v, root = 0;
  for (;;) {
    f(i, 0, n) in[i] = 1e100;
    f(i, 0, m) {
      u = e[i].s;
      v = e[i].t;
      if (u != v && e[i].w < in[v]) {
        in[v] = e[i].w;
        pre[v] = u;
      }
    }
    f(i, 0, m) if (i != root && in[i] > 1e50) return 0;
    int tn = 0;
    memset(id, -1, sizeof id);
    memset(vis, -1, sizeof vis);
    in[root] = 0;
    f(i, 0, n) {
      ans += in[i];
      v = i;
      while (vis[v] != i && id[v] == -1 && v != root) {
        vis[v] = i;
        v = pre[v];
      }
      if (v != root && id[v] == -1) {
        for (int u = pre[v]; u != v; u = pre[u]) id[u] = tn;
        id[v] = tn++;
      }
    }
    if (tn == 0) break;
    f(i, 0, n) if (id[i] == -1) id[i] = tn++;
    f(i, 0, m) {
      u = e[i].s;
      v = e[i].t;
      e[i].s = id[u];
      e[i].t = id[v];
      if (e[i].s != e[i].t) e[i].w -= in[v];
    }
    n = tn;
    root = id[root];
  }
  return ans;
}
```

## Tarjan's DMST Algorithm

Tarjan proposed an algorithm that can solve the minimum branching problem in $O(m+n\log n)$ time.

The algorithm description and reference code below are based on Professor Uri Zwick's lecture notes. See the original paper for more details.

### Algorithm

Tarjan's algorithm consists of two phases: **contraction** and **expansion**. Let us first describe the **contraction** phase.

We assume the input graph is strongly connected. If it is not, we add $O(n)$ edges with infinite weight to make it strongly connected.

We need a heap to store incoming edge indices, incoming edge weights, and total node costs. Since the algorithm requires heap merging operations, we use [Leftist Trees](../ds/leftist-tree.md) with [Disjoint Set Union](../ds/dsu.md). At each step, the algorithm selects an arbitrary node $v$ that is not a root and has no incoming edges in the heap. We add the minimum incoming edge of $v$ to the heap. If this new edge forms a cycle in the heap, we contract the nodes in that cycle into a **super node**. Continue this process until all vertices have been contracted into one super node. The contraction phase produces a contracted tree, which will then be expanded.

Edges in the heap always form a path $v_0\leftarrow v_1\leftarrow \dots\leftarrow v_k$. Since the graph is strongly connected, this path must exist, and each $v_i$ can be either an original single node or a contracted super node.

Initially, let $v_0=a$, where $a$ is an arbitrary node in the graph. Each time, select a minimum incoming edge $v_k\leftarrow u$. If $u$ is not one of $v_0,v_1,\dots,v_k$, extend the path to $v_{k+1}=u$. If $u$ is one of them, say $v_i$, we have found a cycle $v_i\leftarrow\dots\leftarrow v_k\leftarrow v_i$, and contract them into a super node $c$.

Enqueue all nodes and super nodes into a queue $P$, and initially select an arbitrary node $a$. While the queue is not empty, perform the following steps:

1.  Select the minimum incoming edge of $a$, ensuring no self-loop, and find the other endpoint $b$. If $b$ has not been recorded, no cycle has formed, so set $a\leftarrow b$ and continue searching.

2.  If $b$ has been recorded, a cycle has been found. Increment the total node count, renumber all nodes on the cycle, merge the heaps, and update the total weights. The weight update collects all incoming edges of nodes on the cycle and subtracts the cycle's incoming edge weights.

![dmst1](./images/dmst1.png)

As shown in the figure, the strongly connected graph on the left becomes the contracted tree on the right after contraction. Here, $a$ is the super node formed by contracting vertices 1 and 2; $b$ is the super node formed by contracting vertices 3, 4, and 5; and $A$ is the super node formed by contracting the two super nodes $a$ and $b$.

The expansion phase is relatively simple. Starting from the original root $r$, expand each cycle on the path from $r$ to the root of the contracted tree. Then, starting from $r$'s ancestor $f_r$, expand cycles along the path to the root, until all nodes have been traversed.

### Implementation

```cpp
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

using ll = long long;
constexpr int MAXN = 102;
constexpr int INF = 0x3f3f3f3f;

struct UnionFind {
  int fa[MAXN << 1];

  UnionFind() { memset(fa, 0, sizeof(fa)); }

  void clear(int n) { memset(fa + 1, 0, sizeof(int) * n); }

  int find(int x) { return fa[x] ? fa[x] = find(fa[x]) : x; }

  int operator[](int x) { return find(x); }
};

struct Edge {
  int u, v, w, w0;
};

struct Heap {
  Edge *e;
  int rk, constant;
  Heap *lch, *rch;

  Heap(Edge *_e) : e(_e), rk(1), constant(0), lch(NULL), rch(NULL) {}

  void push() {
    if (lch) lch->constant += constant;
    if (rch) rch->constant += constant;
    e->w += constant;
    constant = 0;
  }
};

Heap *merge(Heap *x, Heap *y) {
  if (!x) return y;
  if (!y) return x;
  if (x->e->w + x->constant > y->e->w + y->constant) swap(x, y);
  x->push();
  x->rch = merge(x->rch, y);
  if (!x->lch || x->lch->rk < x->rch->rk) swap(x->lch, x->rch);
  if (x->rch)
    x->rk = x->rch->rk + 1;
  else
    x->rk = 1;
  return x;
}

Edge *extract(Heap *&x) {
  Edge *r = x->e;
  x->push();
  x = merge(x->lch, x->rch);
  return r;
}

vector<Edge> in[MAXN];
int n, m, fa[MAXN << 1], nxt[MAXN << 1];
Edge *ed[MAXN << 1];
Heap *Q[MAXN << 1];
UnionFind id;

void contract() {
  bool mark[MAXN << 1];
  // Record all nodes connected to each node in the graph.
  for (int i = 1; i <= n; i++) {
    queue<Heap *> q;
    for (int j = 0; j < in[i].size(); j++) q.push(new Heap(&in[i][j]));
    while (q.size() > 1) {
      Heap *u = q.front();
      q.pop();
      Heap *v = q.front();
      q.pop();
      q.push(merge(u, v));
    }
    Q[i] = q.front();
  }
  mark[1] = true;
  for (int a = 1, b = 1, p; Q[a]; b = a, mark[b] = true) {
    // Find minimum incoming edge and its endpoint, ensuring no cycles.
    do {
      ed[a] = extract(Q[a]);
      a = id[ed[a]->u];
    } while (a == b && Q[a]);
    if (a == b) break;
    if (!mark[a]) continue;
    // Contract the discovered cycle, renumber nodes, update total weights.
    for (a = b, n++; a != n; a = p) {
      id.fa[a] = fa[a] = n;
      if (Q[a]) Q[a]->constant -= ed[a]->w;
      Q[n] = merge(Q[n], Q[a]);
      p = id[ed[a]->u];
      nxt[p == n ? b : p] = a;
    }
  }
}

ll expand(int x, int r);

ll expand_iter(int x) {
  ll r = 0;
  for (int u = nxt[x]; u != x; u = nxt[u]) {
    if (ed[u]->w0 >= INF)
      return INF;
    else
      r += expand(ed[u]->v, u) + ed[u]->w0;
  }
  return r;
}

ll expand(int x, int t) {
  ll r = 0;
  for (; x != t; x = fa[x]) {
    r += expand_iter(x);
    if (r >= INF) return INF;
  }
  return r;
}

void link(int u, int v, int w) { in[v].push_back({u, v, w, w}); }

int main() {
  int rt;
  scanf("%d %d %d", &n, &m, &rt);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    link(u, v, w);
  }
  // Ensure strong connectivity
  for (int i = 1; i <= n; i++) link(i > 1 ? i - 1 : n, i, INF);
  contract();
  ll ans = expand(rt, n);
  if (ans >= INF)
    puts("-1");
  else
    printf("%lld\n", ans);
  return 0;
}
```

## References

Uri Zwick. (2013), [Directed Minimum Spanning Trees](http://www.cs.tau.ac.il/~zwick/grad-algo-13/directed-mst.pdf), Lecture notes on "Analysis of Algorithms"

<https://riteme.site/blog/2018-6-18/mdst.html#_3>
