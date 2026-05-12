author: accelsao, Henry-ZHR, yuhuoji

This page covers maximum weight perfect matching in general graphs and maximum weight matching in general graphs (maximum weight matching can be converted to maximum weight perfect matching by adding zero-weight edges).

## Preliminaries

### Blossom

The difference between general graph matching and bipartite graph matching is that general graphs may contain odd cycles. We can treat even cycles as bipartite graphs.

The Blossom Algorithm handles this by contracting an odd cycle into a **blossom** when encountered, and marking all vertices in the blossom as even vertices. Since vertices on a blossom can all become even vertices, the entire blossom can be directly contracted into an even vertex. Note that a blossom can contain other blossoms.

This can also be formulated as a linear programming problem with dual variables, but requires some special handling for blossoms.

### Vertex Labeling and Equality Edge

Define $z_u$ as the vertex labeling of vertex $u$, with the same meaning as vertex labeling in the KM algorithm. Define an edge $e(u,v)$ as an "equality edge" if and only if the sum of the labels of vertices $u$ and $v$ equals the weight of edge $e$ (i.e., $z_u + z_v = w(e)$). In this case, the edge's label is $z_e = z_u + z_v - w(e) = 0$.

## Linear Programming for Maximum Weight Perfect Matching in General Graphs

### Definitions

Since a blossom has at least three vertices, after contraction it becomes one vertex. Let $O$ be the collection of sets with odd cardinality $\geq 3$ (containing all blossoms), and let $\gamma(S)$ denote the set of edges inside set $S$.

$$
\begin{aligned}
& \text{Let } S\subseteq V \\
& \gamma(S)=\{(u,v)\in E:u\in S,v\in S\} \\
& O=\{B\subseteq V:|B|\text{ is odd and }|B|\geq3\} \\
\end{aligned}
$$

### Dual Problem

???+ note "Primal Problem"
    $$
    \begin{aligned}
    & \max\sum_{e\in E}w(e)x_e \\
    & \text{subject to:} \\
    & x(\delta(u))=1:\forall u\in V \\
    & x(\gamma(B))\leq\lfloor\frac{|B|}{2}\rfloor:\forall B\in O \\
    & x_e\geq0:\forall e\in E \\
    \end{aligned}
    $$

The problem is then converted to a dual problem using the Primal-Dual method.

???+ note "Dual Problem"
    $$
    \begin{aligned}
    & \min\sum_{u\in V}z_u+\sum_{B\in O}\left\lfloor\frac{|B|}{2}\right\rfloor z_B \\
    & \text{subject to:} \\
    & z_B\geq0:\forall B\in O \\
    & z_e\geq0:\forall e\in E \\
    & \text{Let } e=(u,v),\text{ here} \\
    & \begin{array}{lll}
    z_e & = & z_u + z_v - w(e) + \sum_{\substack{B \in O \\ u,v \in \gamma(B)}} z_B
    \end{array}
    \end{aligned}
    $$

Edges with $x_e=1$ are matching edges, and edges with $x_e=0$ are non-matching edges. As with bipartite graphs, we must satisfy $x_e\in\{0,1\}:\forall e\in E$. Therefore, when finding the maximum weight perfect matching, all matching edges must be **equality edges**.

Unlike bipartite graphs, general graphs have additional $z_B$ variables to handle. Below we consider when $z_B$ should be greater than $0$.

We can see that setting $z_B=0$ whenever possible is ideal, but sometimes we must allow $z_B>0$. We can set $z_B>0$ when $x(\gamma(B)) = \left\lfloor \dfrac{|B|}2 \right\rfloor \text{and} x(\delta(B)) = 1$. Because apart from this case, $z_B>0$ would be meaningless.

According to complementary slackness conditions, we have the following correspondences:

-   For any selected edge $e$, we must have $z_e=0$.

    $$
    x_e>0 \longrightarrow z_e=0,\quad \forall e\in E
    $$

-   For any selected set $B$, $z_B>0 \longrightarrow x(\gamma(B))= \left\lfloor \dfrac{|B|}2 \right\rfloor$, meaning all sets $B$ with $z_B>0$ have half of the set's edges selected. In other words, set $B$ is a blossom, and we select an edge in the blossom to augment. Additionally, we add the condition: $x(\delta(B))=1$, meaning $z_B>0$ is only meaningful when blossom $B$ has exactly one edge connecting to the outside.

    $$
    z_B>0 \longrightarrow x(\gamma(B))=\left\lfloor\frac{|B|}2\right\rfloor, x(\delta(B))=1\quad \forall B\in O
    $$

Using the concept of **equality edge** combined with the Blossom Algorithm: by continuously augmenting along alternating paths composed of equality edges, the final maximum weight perfect matching will still consist entirely of equality edges.

### Handling Blossoms

When encountering a blossom, it must be contracted into an even vertex. Set all vertices in the blossom as even vertices and set $z_B=0$.

Since contracted blossoms are stored until certain conditions are met before being expanded, we cannot record blossoms using the previous method.

Unless otherwise specified, all vertices mentioned previously include contracted blossom vertices since they are also even vertices.

Since blossoms may also be added to the queue as contracted vertices and the number of blossoms is not fixed, we cannot enumerate each vertex to check for augmenting paths as before. Therefore, during BFS, all unmatched vertices must be added to the queue.

This results in multiple alternating trees simultaneously.

### Four Steps of the Algorithm

The algorithm can be divided into four steps:

1.  GROW (Equality Edge): Construct an alternating tree using equality edges.
2.  AUGMENT (Augment): Find and perform augmentation along an augmenting path.
3.  SHRINK (Contract Blossom): Contract a blossom into a single vertex.
4.  EXPAND (Expand): Expand a blossom.

![general-weight-match-1](images/general-weight-match-1.png)

During the AUGMENT stage, since all unmatched vertices are on different alternating trees, when even vertices from two alternating trees connect, it indicates an augmenting path has been found.

### Cannot Find Equality Edge for Augmentation

As with bipartite graphs, there may be cases where no equality edge can be found for augmentation. In this case, vertex labeling needs to be adjusted.

### Adjusting Vertex Labeling

Vertex labeling must still maintain the greater-than-or-equal-to property, existing equality edges cannot be changed, and $z_B$ should be kept as small as possible.

???+ note "Notation for Odd/Even Vertices"
    Use $u^+$ to denote $u$ as an even vertex in the alternating tree.  
    Use $u^-$ to denote $u$ as an odd vertex in the alternating tree.  
    Use $u^\varnothing$ to denote $u$ is not in any alternating tree.  
    All $B$ mentioned later are assumed to be blossoms and represent contracted vertices.  
    Blossoms can also be odd or even blossoms, so the notations $B^+$, $B^-$, $B^\varnothing$ also apply.

Let there be $r$ alternating trees $T_i=(U_{t_i},V_{t_i}):1\leq i\leq r$, and let

$$
\begin{aligned}
d1 &= \min(\{z_e : e = (u^+,v^\varnothing)\}) \\
d2 &= \min(\{z_e : e = (u^+,v^+), ~ u^+ \in T_i, ~ v^+ \in T_j, ~ i \neq j\}) / 2 \\
d3 &= \min({z_{B^-} : B^- \in O\}) / 2
\end{aligned}
$$

Note that here $B$ is a contracted blossom, so it can have odd/even parity.

Let $d=\min(d1,d2,d3)$, and let

$$
\begin{aligned}
z_{u^+} - &= d \\
z_{v^-} + &= d \\
z_{B^+} + &= 2d \\
z_{B^-} - &= 2d \\
\end{aligned}
$$

If $z_B=0$ occurs (i.e., $d=d3$), to prevent $z_B<0$, this blossom must be expanded (EXPAND).
After expanding, only the alternating paths inside the blossom remain, and vertices not on the alternating path are marked as unvisited ($\varnothing$).

This creates additional equality edges: existing equality edges remain unchanged, the property $z_e\geq0:\forall e\in E$ is maintained, and $z_B$ is increased minimally so that augmenting paths can continue to be found.

## Maximum Weight Matching in General Graphs

The above method finds maximum weight perfect matching. To find maximum weight matching, an additional constraint is added to the vertex labeling: for all matched vertices $u$, $z_u>0$.

At the beginning, set all $z_u = \max(\{w(e):e\in E\}) / 2$.

Vertices with vertex labeling $0$ will eventually become unmatched.

### Reference Implementation

For convenient implementation, edge weights are multiplied by 2 to calculate $z_e$, avoiding floating-point errors.

???+ note "Storage"
    ```cpp
    constexpr int INF = INT_MAX;
    constexpr int MAXN = 400;
    
    struct edge {
      int u, v, w;
    
      // Represents edge (u,v) with weight w
      edge() {}
    
      edge(int u, int v, int w) : u(u), v(v), w(w) {}
    };
    
    int n, n_x;
    // There are n vertices, numbered 1 ~ n
    // n_x represents the current number of vertices plus blossoms, numbered from n+1 to n_x are blossom nodes
    edge g[MAXN * 2 + 1][MAXN * 2 + 1];
    // Graph stored as adjacency matrix, since there can be at most n-1 blossoms, size is MAXN*
    vector<int> flower[MAXN * 2 + 1];
    // flower[b] records which vertices are in blossom b
    // We record vertices in a blossom by only recording the outermost blossoms
    ```

Here is an example of nested blossoms:

![general-weight-match-2](images/general-weight-match-2.png)

Where $\{ 6, 5, 8\} \in b1,\{ b1, 4, 3, 2, 11, 10, 9\} \in b2$. Stored as:

```text
flower[b2] = {b1, 4, 3, 2, 11, 10, 9} 
flower[b1] = {6, 5, 8}
```

![general-weight-match-3](images/general-weight-match-3.png)

```text
flower[b2] = {9, b1, 4, 3, 2, 11, 10} 
flower[b1] = {5, 8, 6}
```

```cpp
int lab[MAXN * 2 + 1];
// lab[u] records z_u, lab[b] records z_B
int match[MAXN * 2 + 1], slack[MAXN * 2 + 1], st[MAXN * 2 + 1],
    pa[MAXN * 2 + 1];
// match[x]=y indicates (x,y) is a match, x and y can be blossoms
// slack[x]=u indicates z(x,u) is the minimum among all edges adjacent to x
// Represents the blossom containing vertex x. If x=b and b<=n, then x
// is a normal vertex (not in any blossom) Represents in the alternating tree that the parent of vertex v is u
int flower_from[MAXN * 2 + 1][MAXN + 1], S[MAXN * 2 + 1], vis[MAXN * 2 + 1];
/*
flower_from[b][x]=xs indicates the largest sub-blossom of b containing x is xs
x is a vertex in b, xs is a blossom or vertex in b, also x=xs or x is one of xs's vertices
*/
// S[u]={-1:unvisited 0:even vertex 1:odd vertex}
// vis is only used to check if visited when finding lca
queue<int> q;
// BFS queue for finding augmenting paths
```

![general-weight-match-4](images/general-weight-match-4.png)

```text
flower_from[b2][6] = b1 
flower_from[b2][5] = b1 
flower_from[b2][9] = 9 
flower_from[b1][6] = 6 
and so on
```

```cpp
int e_delta(const edge &e) {
  // Calculate ze, first multiply all edge weights by 2 for convenience
  // Directly calculating e_delta in blossoms leads to errors
  return lab[e.u] + lab[e.v] - g[e.u][e.v].w * 2;
}

void update_slack(int u, int x) {
  // Update slack[x] with u
  if (!slack[x] || e_delta(g[u][x]) < e_delta(g[slack[x]][x])) {
    slack[x] = u;
  }
}

void set_slack(int x) {
  // Calculate slack[x], slack[x]=0 indicates x is a vertex in the alternating tree
  slack[x] = 0;
  for (int u = 1; u <= n; ++u) {
    if (g[u][x].w > 0 && st[u] != x && S[st[u]] == 0) {
      update_slack(u, x);
    }
  }
}
```

```cpp
void q_push(int x) {
  // Add x to queue, we don't directly push a blossom into the queue
  if (x <= n)
    q.push(x);
  else {
    // If pushing a blossom, add all original vertices in the blossom to the queue
    for (size_t i = 0; i < flower[x].size(); i++) {
      q_push(flower[x][i]);
    }
  }
}

void set_st(int x, int b) {
  // Set the blossom containing x to b
  st[x] = b;
  if (x > n) {
    // If x is also a blossom, set the blossoms containing x's vertices to b
    for (size_t i = 0; i < flower[x].size(); ++i) {
      set_st(flower[x][i], b);
    }
  }
}
```

```cpp
int get_pr(int b, int xr) {
  // xr is a vertex in flower[b], return value pr is its position
  // For convenient execution, we let flower[b][0]~flower[b][pr] be the alternating path in the blossom
  int pr = find(flower[b].begin(), flower[b].end(), xr) - flower[b].begin();
  if (pr % 2 == 1) {
    // Check its position in the blossom, if flower[b][0]~flower[b][pr] is not an alternating path
    // reverse the entire blossom and recalculate pr
    // Let flower[b][0]~flower[b][pr] be the alternating path in the blossom
    reverse(flower[b].begin() + 1, flower[b].end());
    return (int)flower[b].size() - pr;
  } else
    return pr;
}
```

![general-weight-match-5](images/general-weight-match-5.png)

If using `get_pr(b2,11)`, `flower[b2]` becomes `{9,10,11,2,3,4,b1}` and returns 2.

If using `get_pr(b2,2)`, `flower[b2]` becomes `{9,b1,4,3,2,11,10}` and returns 4.

```cpp
void set_match(int u, int v) {
  // Set u and v as matched edges, u and v can be blossoms
  match[u] = g[u][v].v;
  if (u > n) {
    // If u is a blossom
    edge e = g[u][v];
    int xr = flower_from[u][e.u];  // Find which blossom e.u is in flower[u]
    int pr = get_pr(u, xr);  // Find xr's position and let 0~pr be the alternating path in the blossom
    for (int i = 0; i < pr; ++i) {  // Reverse matched and unmatched edges on the alternating path in the blossom
      set_match(flower[u][i], flower[u][i ^ 1]);
    }
    set_match(xr, v);  // Set (xr,v) as matched edge
    rotate(flower[u].begin(), flower[u].begin() + pr, flower[u].end());
    // Finally set pr as the base, since flower[u][0] is u's base
    // So we need to rotate flower[u][pr] to the front
  }
}

void augment(int u, int v) {
  // Augment all ancestors of u and set (u,v) as matched edge
  for (;;) {
    int xnv = st[match[u]];
    set_match(u, v);
    if (!xnv) return;
    set_match(xnv, st[pa[xnv]]);
    u = st[pa[xnv]];
    v = xnv;
  }
}

int get_lca(int u, int v) {
  // Find lca of u,v in alternating tree
  static int t = 0;
  for (++t; u || v; swap(u, v)) {
    if (u == 0) continue;
    if (vis[u] == t) return u;
    vis[u] = t;  // This method avoids needing to clear the vis array
    u = st[match[u]];
    if (u) u = st[pa[u]];
  }
  return 0;
}
```

???+ note "Adding an Odd Blossom"
    ```cpp
    void add_blossom(int u, int lca, int v) {
      // Contract u,v,lca into a single vertex b
      // lca in the alternating tree is the base
      int b = n + 1;
      while (b <= n_x && st[b]) ++b;
      if (b > n_x) ++n_x;
      // Find an unused blossom number
      lab[b] = 0;             // Set z_B=0
      S[b] = 0;               // The entire blossom is an even vertex
      match[b] = match[lca];  // Set blossom's matched edge to base's matched edge
      flower[b].clear();
      flower[b].push_back(lca);
      for (int x = u, y; x != lca; x = st[pa[y]]) {
        flower[b].push_back(x);
        y = st[match[x]];
        flower[b].push_back(y);
        q_push(y);
      }
      reverse(flower[b].begin() + 1, flower[b].end());
      for (int x = v, y; x != lca; x = st[pa[y]]) {
        flower[b].push_back(x);
        y = st[match[x]];
        flower[b].push_back(y);
        q_push(y);
      }
      // All vertices in b are added to flower[b] in circular order, with base as the first element
      set_st(b, b);  // Set all elements' blossoms in the entire blossom to b
      for (int x = 1; x <= n_x; ++x) {
        g[b][x].w = 0;
        g[x][b].w = 0;
      }
      for (int x = 1; x <= n; ++x) {
        flower_from[b][x] = 0;
      }
      for (size_t i = 0; i < flower[b].size(); ++i) {
        int xs = flower[b][i];
        for (int x = 1; x <= n_x; ++x) {
          // Set edges adjacent to b to the edge with minimum e_delta among edges adjacent to x in b
          if (g[b][x].w == 0 || e_delta(g[xs][x]) < e_delta(g[b][x])) {
            g[b][x] = g[xs][x];
            g[x][b] = g[x][xs];
          }
        }
        for (int x = 1; x <= n; ++x) {
          if (flower_from[xs][x]) {
            // If some vertex xs in b contains x
            // Then flower_from[b][x] will be xs
            flower_from[b][x] = xs;
          }
        }
      }
      set_slack(b);
      // Finally must set b's slack value
    }
    ```

???+ note "Expanding Blossom"
    ```cpp
    void expand_blossom(int b) {
      // b is an odd blossom and z_B=0, must expand b
      // Since we only expand b, if b contains other blossoms
      // we don't need to expand them
      for (size_t i = 0; i < flower[b].size(); ++i) {
        set_st(flower[b][i], flower[b][i]);
        // First set each element's blossom in flower[b] to itself
      }
      int xr = flower_from[b][g[b][pa[b]].u];
      // xr represents which blossom the parent of b in the alternating tree is in flower[b]
      int pr = get_pr(b, xr);  // Find xr's position and let 0~pr be the alternating path in the blossom
      for (int i = 0; i < pr; i += 2) {
        // Expand the alternating path into the alternating tree
        // Add even vertices in the alternating path to the queue
        int xs = flower[b][i];
        int xns = flower[b][i + 1];
        pa[xs] = g[xns][xs].u;
        S[xs] = 1;
        S[xns] = 0;
        slack[xs] = 0;
        set_slack(xns);
        q_push(xns);
      }
      S[xr] = 1;  // Now xr will be an odd vertex or odd blossom
      pa[xr] = pa[b];
      for (size_t i = pr + 1; i < flower[b].size(); ++i) {
        // Set all vertices in the blossom not on the alternating path to unvisited
        int xs = flower[b][i];
        S[xs] = -1;
        set_slack(xs);
      }
      st[b] = 0;
    }
    ```

???+ note "Trying to Augment with an Equality Edge"
    ```cpp
    bool on_found_edge(const edge &e) {
      // During BFS, find an equality edge e
      // Perform the following processing
      // Here u must be an even vertex
      int u = st[e.u], v = st[e.v];
      if (S[v] == -1) {
        // v is an unvisited vertex
        pa[v] = e.u;
        S[v] = 1;
        int nu = st[match[v]];
        slack[v] = 0;
        slack[nu] = 0;
        S[nu] = 0;
        q_push(nu);
      } else if (S[v] == 0) {
        // v is an even vertex
        int lca = get_lca(u, v);
        if (!lca) {  // lca=0 indicates u,v are in different alternating trees, there is an augmenting path
          augment(u, v);
          augment(v, u);
          return true;  // Found augmenting path
        } else
          add_blossom(u, lca, v);
        // Otherwise u,v in the same tree will form a blossom, contract it
      }
      return false;
    }
    ```

???+ note "Augmentation"
    ```cpp
    bool matching() {
      memset(S + 1, -1, sizeof(int) * n_x);
      memset(slack + 1, 0, sizeof(int) * n_x);
      q = queue<int>();  // Clear queue
      for (int x = 1; x <= n_x; ++x) {
        if (st[x] == x && !match[x]) {
          // Add all unmatched vertices to queue and set as even vertices
          pa[x] = 0;
          S[x] = 0;
          q_push(x);
        }
      }
      if (q.empty()) return false;  // All vertices are matched
      for (;;) {
        while (q.size()) {
          // BFS
          int u = q.front();
          q.pop();
          if (S[st[u]] == 1) continue;
          for (int v = 1; v <= n; ++v) {
            if (g[u][v].w > 0 && st[u] != st[v]) {
              if (e_delta(g[u][v]) == 0) {
                if (on_found_edge(g[u][v])) return true;
              } else
                update_slack(u, st[v]);
            }
          }
        }
        // Update lab values
        int d = INF;
        for (int u = 1; u <= n; ++u) {
          // This is to prevent lab<0
          // End program if any lab[u]=0
          if (S[st[u]] == 0) d = min(d, lab[u]);
        }
        for (int b = n + 1; b <= n_x; ++b) {
          if (st[b] == b && S[b] == 1) d = min(d, lab[b] / 2);
        }
        for (int x = 1; x <= n_x; ++x)
          if (st[x] == x && slack[x]) {
            if (S[x] == -1)
              d = min(d, e_delta(g[slack[x]][x]));
            else if (S[x] == 0)
              d = min(d, e_delta(g[slack[x]][x]) / 2);
          }
        for (int u = 1; u <= n; ++u) {
          if (S[st[u]] == 0) {
            if (lab[u] == d) return false;
            // If lab[u]=0, end program
            lab[u] -= d;
          } else if (S[st[u]] == 1)
            lab[u] += d;
        }
        for (int b = n + 1; b <= n_x; ++b) {
          if (st[b] == b) {
            if (S[st[b]] == 0)
              lab[b] += d * 2;
            else if (S[st[b]] == 1)
              lab[b] -= d * 2;
          }
        }
        q = queue<int>();  // Clear queue
        for (int x = 1; x <= n_x; ++x) {
          // Check if augmenting paths are generated
          if (st[x] == x && slack[x] && st[slack[x]] != x &&
              e_delta(g[slack[x]][x]) == 0)
            if (on_found_edge(g[slack[x]][x])) return true;
        }
        for (int b = n + 1; b <= n_x; ++b) {
          // EXPAND operation, expand all blossoms with lab[b]=0
          if (st[b] == b && S[b] == 1 && lab[b] == 0) expand_blossom(b);
        }
      }
      return false;
    }
    ```

???+ note "Main Function"
    ```cpp
    pair<long long, int> weight_blossom() {
      // Main function, initialize first
      memset(match + 1, 0, sizeof(int) * n);
      n_x = n;  // No blossoms initially
      int n_matches = 0;
      long long tot_weight = 0;
      for (int u = 0; u <= n; ++u) {
        // Set each vertex's blossom to itself first
        st[u] = u;
        flower[u].clear();
      }
      int w_max = 0;
      for (int u = 1; u <= n; ++u)
        for (int v = 1; v <= n; ++v) {
          // When u is a vertex, the only vertex it contains is itself
          flower_from[u][v] = (u == v ? u : 0);
          w_max = max(w_max, g[u][v].w);
          // Find the maximum edge weight
        }
      for (int u = 1; u <= n; ++u) lab[u] = w_max;
      // Set all lab to the maximum edge weight
      // Since implementation uses edge weight times 2 to calculate ze, no need to divide by 2
      while (matching()) ++n_matches;
      for (int u = 1; u <= n; ++u)
        if (match[u] && match[u] < u) tot_weight += g[u][match[u]].w;
      return make_pair(tot_weight, n_matches);
    }
    ```

???+ note "Initialization"
    Important: Must initialize before use
    
    ```cpp
    void init_weight_graph() {
      // Must initialize before inputting edges into the graph
      // Since this is maximum weight matching, set non-existent edges to 0
      for (int u = 1; u <= n; ++u)
        for (int v = 1; v <= n; ++v) g[u][v] = edge(u, v, 0);
    }
    ```

## Complexity Analysis

Each blossom can only be contracted or expanded once during a BFS. Each contraction or expansion takes $O(|V|)$ time. There can be at most $O(|V|)$ blossoms, so blossom processing takes $O(|V|^2)$ time. BFS takes $O(|V| + |E|)$ time. Therefore, finding augmenting paths takes $O(|V| + |E|) + O(|V|^2) = O(|V|^2)$ time.

At most $|V|$ BFS iterations are performed. So the total time complexity is $O(|V|^3)$.

## Exercises

-   [UOJ #81. General Graph Maximum Weight Matching](https://uoj.ac/problem/81)

## References

1.  [Kolmogorov, Vladimir (2009), "Blossom V: A new implementation of a minimum cost perfect matching algorithm"](http://pub.ist.ac.at/~vnk/papers/BLOSSOM5.html)
2.  [From Hungarian Algorithm to Weighted Blossom - Detailed Explanation of Dual Problems in Graph Matching](https://www.luogu.com.cn/blog/potassium/solution-p6699)