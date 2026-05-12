## Preface

The concept of "domination" was introduced by Reese T. Prosser in [a paper on network flow](http://portal.acm.org/ft_gateway.cfm?id=1460314&type=pdf&coll=GUIDE&dl=GUIDE&CFID=79528182&CFTOKEN=33765747) in 1959, but no specific algorithm was proposed; it was not until 1969 that Edward S. Lowry and C. W. Medlock first proposed [an effective algorithm](http://portal.acm.org/ft_gateway.cfm?id=362838&type=pdf&coll=GUIDE&dl=GUIDE&CFID=79528182&CFTOKEN=33765747). The most widely used Lengauer–Tarjan algorithm was proposed by Lengauer and Tarjan in 1979 in [a paper](https://www.cs.princeton.edu/courses/archive/fall03/cs528/handouts/a%20fast%20algorithm%20for%20finding.pdf).

In the OI community, the concept of a dominator tree was first introduced in [ZJOI2012 Disaster](https://www.luogu.com.cn/problem/P2597), where it was also called an "extinction tree"; Chen Sunli also introduced this algorithm in a 2020 national training team paper.

Currently, dominator trees are not popular in competitive programming, and related practice problems are rare; however, dominator trees are widely used in industry, especially in compiler-related fields.

This article introduces the concept of dominator trees and several methods for solving them.

## Domination Relation

Consider an arbitrary directed graph with a designated entry node $s$. For a node $u$, if every path from $s$ to $u$ passes through a node $v$, then we say $v$ **dominates** $u$, and $v$ is called a **dominator** of $u$, denoted $v\ dom\ u$.

Nodes unreachable from $s$ have no meaningful domination relation; therefore, unless otherwise specified, we assume $s$ can reach every node in the graph.

![](images/dom-tree1.png)

For example, in this directed graph, $2$ is dominated by $1$, $3$ is dominated by $1$ and $2$, $4$ is dominated by $1$, $2$, and $3$, $5$ is dominated by $1$ and $2$, etc.

### Lemmas

In the lemmas below, assume $u, v, w \ne s$.

**Lemma 1:** $s$ dominates all nodes; every node dominates itself.

**Proof:** Obviously, every path from $s$ to $u$ must pass through both $s$ and $u$.

**Lemma 2:** The domination relation derived from simple paths is the same as that derived from all paths.

**Proof:** For non-simple paths, let $S$ be the set of nodes traversed between two visits to the same node. If we delete all nodes in $S$, each non-simple path can be mapped to a simple path.

Nodes in $S$ that appear on non-simple paths but not on simple paths cannot be dominators, because there exists at least one simple path from $s$ to $u$ that does not include this node; meanwhile, nodes on both simple and non-simple paths only need to be discussed on simple paths.

Therefore, removing non-simple paths does not affect the domination relation.

**Lemma 3:** If $u\ dom\ v$ and $v\ dom\ w$, then $u\ dom\ w$.

**Proof:** Paths passing through $w$ must pass through $v$, and paths passing through $v$ must pass through $u$, so paths passing through $w$ must pass through $u$, i.e., $u\ dom\ w$.

**Lemma 4:** If $u\ dom\ v$ and $v\ dom\ u$, then $u = v$.

**Proof:** Assume $u \ne v$. Then every path reaching $v$ has already passed through $u$, and every path reaching $u$ has already passed through $v$, a contradiction.

**Lemma 5:** If $u \ne v \ne w$, $u\ dom\ w$ and $v\ dom\ w$, then either $u\ dom\ v$ or $v\ dom\ u$.

**Proof:** Consider a path $s \rightarrow \dots \rightarrow u \rightarrow \dots \rightarrow v \rightarrow \dots \rightarrow w$. If $u$ and $v$ have no domination relation, then there exists a path from $s$ to $v$ that does not pass through $u$, i.e., a path $s \rightarrow \dots \rightarrow v \rightarrow \dots \rightarrow w$, contradicting $u\ dom\ w$.

### Solving Domination Relations

#### Node Deletion Method

An equivalent condition to the definition: if we delete a node from the graph and some nodes become unreachable, then the deleted node dominates those unreachable nodes.

Therefore, we can try deleting each node and running a DFS, with time complexity $O(n^3)$. The core code is given below.

```cpp
// Assume the graph has n nodes, start node s = 1
std::bitset<N> vis;
std::vector<int> edge[N];
std::vector<int> dom[N];

void dfs(int u, int del) {
  vis[u] = true;
  for (int v : edge[u]) {
    if (v == del or vis[v]) {
      continue;
    }
    dfs(v, del);
  }
}

void getdom() {
  for (int i = 2; i <= n; ++i) {
    vis.reset();
    dfs(1, i);
    for (int j = 1; j <= n; ++j) {
      if (!vis[j]) {
        dom[j].push_back(i);
      }
    }
  }
}
```

#### Dataflow Iteration Method

The dataflow iteration method is also an uncommon topic in OI. Here we give a brief introduction.

Dataflow analysis is a concept in compiler theory, used to analyze how data flows along program execution paths; the dataflow iteration method lists equations on nodes of a program's flow graph and iteratively solves them to obtain dataflow values at certain points. Here, we treat the directed graph as a program flow graph.

In this problem, the equation is:

$$

dom(u)=\{u\} \cup \left(\bigcap_{v\in pre(u)}{dom(v)}\right)

$$

where $pre(u)$ is the set of predecessor nodes of $u$. This equation can be derived from Lemma 3.

In plain terms, the set of dominators of a node is the intersection of the dominator sets of all its predecessor nodes, union with itself. Based on this equation, we iteratively update the dominator set for each node until the answer stabilizes.

To improve efficiency, we want each predecessor of the current node to have already completed this iteration. Therefore, we use depth-first ordering to get the reverse postorder of the graph and iterate in that order.

The reference implementation of the core code is given below. Here, the predecessor set of each node and the reverse postorder of the graph need to be preprocessed, but this is not the main topic of this article, so no reference implementation is provided here.

```cpp
std::vector<int> pre[N];  // Predecessor nodes of each node
std::vector<int> ord;     // Reverse postorder of the graph
std::bitset<N> dom[N];
std::vector<int> Dom[N];

void getdom() {
  dom[1][1] = true;
  flag = true;
  while (flag) {
    flag = false;
    for (int u : ord) {
      std::bitset<N> tmp;
      tmp[u] = true;
      for (int v : pre[u]) {
        tmp &= dom[v];
      }
      if (tmp != dom[u]) {
        dom[u] = tmp;
        flag = true;
      }
    }
  }
  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (dom[i][j]) {
        Dom[i].push_back(j);
      }
    }
  }
}
```

The time complexity of this algorithm is $O(n^2)$.

## Dominator Tree

In the previous section, we found that for every node except $s$, there are at least two dominators: $s$ and the node itself.

Among the dominators of an arbitrary node $u$, the dominator $v$ that is closest to $u$ (excluding $u$ itself) is called the **immediate dominator** of $u$, denoted $idom(u) = v$. Obviously, except for $s$ which has no immediate dominator, every node has exactly one immediate dominator.

If we draw an edge from $idom(u)$ to $u$ for every node $u \ne s$, we get a directed graph with $n$ nodes and $n - 1$ edges. By Lemma 3 and Lemma 4, the domination relation never forms a cycle, so these edges never form a cycle, and the resulting graph is a tree. We call this tree the **dominator tree** of the original graph.

## Solving Dominator Trees

### Solving from Dom Sets

Consider the dominator set $\{s_1, s_2, \dots, s_k\}$ of some node $u$. There must exist a path $s \rightarrow \dots \rightarrow s_1 \rightarrow \dots \rightarrow s_2 \rightarrow \dots \rightarrow \dots \rightarrow s_k \rightarrow\dots \rightarrow u$. Clearly, the immediate dominator of $u$ is $s_k$. Therefore, the definition of immediate dominator is equivalent to:

For a node $u$ with dominator set $S$, if $v \in S$ satisfies $\forall w \in S\setminus\{u,v\}, w\ dom\ v$, then $idom(u)=v$.

Therefore, after obtaining the dominator set of each node using the algorithm described earlier, we can easily obtain the immediate dominator of each node according to the above definition, and thus construct the dominator tree. The reference code is given below.

```cpp
std::bitset<N> dom[N];
std::vector<int> Dom[N];
int idom[N];

void getidom() {
  for (int u = 2; u <= n; ++u) {
    for (int v : Dom[u]) {
      std::bitset<N> tmp = (dom[v] & dom[u]) ^ dom[u];
      if (tmp.count() == 1 and tmp[u]) {
        idom[u] = v;
        break;
      }
    }
  }
  for (int u = 2; u <= n; ++u) {
    e[idom[u]].push_back(u);
  }
}
```

### Special Case: Trees

Clearly, the dominator tree of a tree graph is itself.

### Special Case: DAGs

We observe that DAGs have a nice property: when solving by topological order, the solutions obtained earlier do not affect subsequent solutions. We can use this property to efficiently compute the dominator tree of a DAG.

???+ warning "Note"
    It is important to note that the DAG here can only have one source. If there are multiple sources, nodes dominated by different sources may have multiple parents in the dominator tree, making the domination relation not expressible simply as a dominator tree.

**Lemma 6:** In a directed graph, $v\ dom\ u$ if and only if $\forall w \in pre(u), v\ dom\ w$.

**Proof:** First, we prove sufficiency. Consider any path from $s$ to $u$. It must pass through some node $w \in pre(u)$. Since $v$ dominates this node, any path from $s$ to $u$ must pass through $v$, so we get $v\ dom\ u$.

Now for necessity. If $\exists w\in pre(u)$ such that $v$ does not dominate $w$, then there exists a path $s \rightarrow \cdots \rightarrow w \rightarrow \cdots \rightarrow u$ that does not pass through $v$, so $v$ does not dominate $u$.

We find that the dominator of $u$ must be a common ancestor of all its predecessors in the dominator tree. Therefore, the immediate dominator of $u$ is the LCA of all predecessors in the dominator tree. Considering using binary lifting to compute LCA, we can support adding one node at a time, so the above algorithm is clearly feasible.

The reference implementation is given below:

```cpp
std::stack<int> sta;
std::vector<int> e[N], g[N], tree[N];  // g is the reverse graph, tree is the dominator tree
int n, s, in[N], tpn[N], dep[N], idom[N];  // n is total nodes, s is start node, in is indegree
int fth[N][17];

void topo(int s) {
  sta.push(s);
  while (!sta.empty()) {
    int u = sta.top();
    sta.pop();
    tpn[++tot] = u;
    for (int v : e[u]) {
      --in[v];
      if (!in[v]) {
        sta.push(v);
      }
    }
  }
}

int lca(int u, int v) {
  if (dep[u] < dep[v]) {
    std::swap(u, v);
  }
  for (int i = 15; i >= 0; --i) {
    if (dep[fth[u][i]] >= dep[v]) {
      u = fth[u][i];
    }
  }
  if (u == v) {
    return u;
  }
  for (int i = 15; i >= 0; --i) {
    if (fth[u][i] != fth[v][i]) {
      u = fth[u][i];
      v = fth[v][i];
    }
  }
  return fth[u][0];
}

void build() {
  topo(s);
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j <= 15; ++j) fth[i][j] = s;
  for (int i = 1; i <= n; ++i) {
    int u = tpn[i];
    if (g[u].size()) {
      int v = g[u][0];
      for (int j = 1, q = g[u].size(); j < q; ++j) {
        v = lca(v, g[u][j]);
      }
      tree[v].push_back(u);
      fth[u][0] = v;
      dep[u] = dep[v] + 1;
      for (int i = 1; i <= 15; ++i) {
        fth[u][i] = fth[fth[u][i - 1]][i - 1];
      }
    }
  }
}

```

### Lengauer–Tarjan Algorithm

The Lengauer–Tarjan algorithm is one of the most famous algorithms for solving dominator trees, computing the dominator tree of a directed graph in $O(n\alpha(n, m))$ time. This algorithm introduces the concept of **semi-dominators** and uses them to find immediate dominators.

#### Conventions

First, we perform a DFS from $s$ on this directed graph. The traversed nodes and edges form a tree $T$. We call traversed edges tree edges and the rest non-tree edges. Let $dfn(u)$ denote the order in which node $u$ is visited; define $u < v$ if and only if $dfn(u) < dfn(v)$.

#### Semi-Dominators

The semi-dominator of a node $u$ is the smallest node $v$ such that there is a path from $v$ to $u$ where, except for $u$ and $v$, every node on the path is greater than $u$. Formally, the semi-dominator $sdom(u)$ of $u$ is defined as:

$sdom(u) = \min(v|\exists v=v_0 \rightarrow v_1 \rightarrow\dots \rightarrow v_k = u, \forall 1\le i\le k - 1, v_i > u)$

We observe that semi-dominators have some useful properties:

**Lemma 7:** For any node $u$, $sdom(u) < u$.

**Proof:** By definition, the parent $fa(u)$ of $u$ in $T$ also satisfies the condition to be a semi-dominator, and $fa(u) < u$. Therefore, no node greater than $u$ can be its semi-dominator.

**Lemma 8:** For any node $u$, $idom(u)$ is an ancestor of $u$ in $T$.

**Proof:** The path from $s$ to $u$ in $T$ corresponds to a path in the original graph, so $idom(u)$ must be on this path.

**Lemma 9:** For any node $u$, $sdom(u)$ is an ancestor of $u$ in $T$.

**Proof:** Suppose $sdom(u)$ is not an ancestor of $u$. Then $sdom(u)$ cannot connect to any node with DFS order greater than or equal to $u$ (otherwise this node should be in the subtree of $sdom(u)$ rather than another subtree), a contradiction.

**Lemma 10:** For any node $u$, $idom(u)$ is an ancestor of $sdom(u)$.

**Proof:** Consider that we can go from $s$ to $sdom(u)$, then along the path in the definition to $u$. By definition, nodes on the path from $sdom(u)$ to $u$ do not dominate $u$, so $idom(u)$ must be an ancestor of $sdom(u)$.

**Lemma 11:** For any nodes $u \ne v$ where $v$ is an ancestor of $u$, either $v$ is an ancestor of $idom(u)$, or $idom(u)$ is an ancestor of $idom(v)$.

**Proof:** For any node $w$ between $v$ and $idom(v)$, by the definition of immediate dominator, there exists a path from $s$ to $idom(v)$ then to $v$ that does not pass through $w$. Therefore, these nodes $w$ are not $idom(u)$. So $idom(u)$ is either a descendant of $v$ or an ancestor of $idom(v)$.

From the above lemmas, we can derive the following theorem:

**Theorem 1:** The semi-dominator of a node $u$ is the minimum among the semi-dominators of all ancestors of $u$'s predecessors and $u$'s dominators in $T$ that are greater than $u$. Formally, $sdom(u)=\min(\{v|\exists v \rightarrow u, v < u \} \cup \{sdom(w) | w > u\ and\ \exists w \rightarrow \dots \rightarrow v \rightarrow u \})$.

**Proof:** Let $x$ equal the right side of the equation.

First, we prove $sdom(u) \le x$. By Lemma 7, this statement is equivalent to proving that both cases in the definition satisfy the semi-dominator condition. When $x$ is a predecessor of $u$, this is obvious. For the second part, consider the path $x=v_0\rightarrow\dots\rightarrow v_j=w$ from the semi-dominator definition and a path $w=v_j \rightarrow\dots\rightarrow v_k=v$ in $T$ satisfying $\forall i\in[j, k-1], v_i\ge w > u$, along with the path $v \rightarrow u$. Concatenating these gives a path satisfying the semi-dominator definition.

Then we prove $sdom(u)\ge x$. Consider the path $sdom(u)=v_0\rightarrow v_1 \rightarrow\dots\rightarrow v_k=u$ from $u$ to its semi-dominator. It is clear that $k=1$ and $k > 1$ correspond to the two selection methods in the definition. If $k = 1$, there is a directed edge $sdom(u) \rightarrow u$, which proves the case by Lemma 7. If $k>1$, let $j$ be the minimum index satisfying $j \ge 1$ and $v_j$ is an ancestor of $v_{k-1}$ in $T$. Since $k$ satisfies the above condition, such $j$ must exist.

To prove $v_0 \rightarrow \dots \rightarrow v_j$ is a path satisfying the semi-dominator condition for $v_j$, we need $\forall i \in [1, j), v_i>v_j$. If not, let $i$ be the smallest index such that $v_i < v_j$. By Lemma 11, $v_i$ is an ancestor of $v_j$, which contradicts the definition of $j$. Thus $sdom(v_j)\le sdom(u)$. Since $sdom(v_j) \le x$ and $v_j$'s semi-dominator is at least $x$ (as $v_j \le u$), we have $sdom(u)\le x$. Therefore $x=sdom(u)$.

By Theorem 1, we can compute the semi-dominator of each node. The bottleneck in computing semi-dominators is the second case. We use a weighted union-find with path compression and update the minimum during compression.

```cpp
void dfs(int u) {
  dfn[u] = ++dfc;
  pos[dfc] = u;
  for (int i = h[0][u]; i; i = e[i].x) {
    int v = e[i].v;
    if (!dfn[v]) {
      dfs(v);
      fth[v] = u;
    }
  }
}

int find(int x) {
  if (fa[x] == x) {
    return x;
  }
  int tmp = fa[x];
  fa[x] = find(fa[x]);
  if (dfn[sdm[mn[tmp]]] < dfn[sdm[mn[x]]]) {
    mn[x] = mn[tmp];
  }
  return fa[x];
}

void getsdom() {
  dfs(1);
  for (int i = 1; i <= n; ++i) {
    mn[i] = fa[i] = sdm[i] = i;
  }
  for (int i = dfc; i >= 2; --i) {
    int u = pos[i], res = INF;
    for (int j = h[1][u]; j; j = e[j].x) {
      int v = e[j].v;
      if (!dfn[v]) {
        continue;
      }
      find(v);
      if (dfn[v] < dfn[u]) {
        res = std::min(res, dfn[v]);
      } else {
        res = std::min(res, dfn[sdm[mn[v]]]);
      }
    }
    sdm[u] = pos[res];
    fa[u] = fth[u];
  }
}

```

#### Computing Immediate Dominators

##### Transforming to a DAG

But I still don't know what semi-dominators are for!

Consider adding directed edges $sdom(u) \rightarrow u$ for every $u$ in $T$. By Lemma 9, the resulting graph $G$ must be a DAG; and by Lemma 10, adding these edges does not change the domination relation. So we transform the original graph into a DAG and can use the algorithm above to solve it.

##### Solving via Semi-Dominators

Building a bunch of graphs is not elegant!

**Theorem 2:** For any node $u$, if every node $v$ on the path from $sdom(u)$ to $w$ in $T$ satisfies $sdom(v) \ge sdom(w)$, then $idom(u) = sdom(u)$.

**Proof:** By Lemma 10, we know $idom(u)$ is $sdom(u)$ or its ancestor, so we only need to prove $sdom(u)\ dom\ u$.

Consider any path $P$ from $s$ to $u$. We need to prove $sdom(u)$ is in $P$. Let $v$ be the last node in $P$ satisfying $v < sdom(u)$. If $v$ does not exist, then $sdom(u) = idom(u) = s$. Otherwise, let $w$ be the first node on the path in the DFS tree from $sdom(u)$ to $u$ that appears after $v$ in $P$.

Next, we prove $sdom(w) \le v < sdom(v)$. Consider the path $v = v_0 \rightarrow \dots \rightarrow v_k = w$ in $T$. If the statement does not hold, there exists $i \in [1, k-1]$ such that $v_i < w$. Then there exists $j \in [i, k-1]$ such that $v_j$ is an ancestor of $w$. By the definition of $v$, we know $sdom(u) \le v_j$. So $v_j$ is also on the path from $sdom(u)$ to $u$ in the DFS tree, contradicting the definition of $w$. Therefore $sdom(w) \le v < sdom(v)$. By the condition of the theorem, $y = sdom(u)$, i.e., path $P$ contains $sdom(u)$.

**Theorem 3:** For any node $u$, among all nodes on the path from $sdom(u)$ to $u$ in $T$, the node $v$ with the minimum semi-dominator satisfies $sdom(v) \le sdom(u)$ and $idom(v) = idom(u)$.

**Proof:** Since $u$ itself satisfies the condition for $v$, we have $sdom(v) \le sdom(u)$.

Since $idom(u)$ is an ancestor of $v$ in $T$, by Lemma 11, $idom(u)$ is also an ancestor of $idom(v)$. So we only need to prove $idom(v)$ dominates $u$.

Consider any path $P$ from $s$ to $u$. We need to prove $sdom(u)$ is in $P$. Let $x$ be the last node in $P$ satisfying $x < sdom(u)$. If $x$ does not exist, then $sdom(u) = idom(u) = s$. Otherwise, let $y$ be the first node on the path in the DFS tree from $sdom(u)$ to $u$ that appears after $x$ in $P$.

By the same reasoning as in the proof of Theorem 2, we get $sdom(y) \le x$. By Lemma 10, $sdom(y) \le x < idom(v) \le sdom(v)$. From the definition of $v$, we know $y$ cannot be a descendant of $sdom(u)$. On the other hand, $y$ cannot be both a descendant of $idom(v)$ and an ancestor of $v$, otherwise the path from $s$ to $sdom(y)$ along the DFS tree, then along $P$ to $y$, and finally along the DFS tree to $v$ would not pass through $idom(v)$, contradicting the definition of dominator. Therefore $y = idom(v)$, i.e., $P$ contains $idom(v)$.

From the above two theorems, we can obtain the relationship between $sdom(u)$ and $idom(u)$.

Let $v$ be the node with the minimum $sdom(v)$ among all nodes between $sdom(u)$ and $u$. Then:

$$

idom(u) =
\left\{
\begin{aligned}
& sdom(u), &\text{if}\ sdom(u) = sdom(v)
\\
&idom(v), &\text{otherwise}
\end{aligned}
\right.

$$

The semi-dominator computation code can be slightly modified to compute this.

```cpp
struct E {
  int v, x;
} e[MAX * 4];

int h[3][MAX * 2];

int dfc, tot, n, m, u, v;
int fa[MAX], fth[MAX], pos[MAX], mn[MAX], idm[MAX], sdm[MAX], dfn[MAX],
    ans[MAX];

void add(int x, int u, int v) {
  e[++tot] = {v, h[x][u]};
  h[x][u] = tot;
}

void dfs(int u) {
  dfn[u] = ++dfc;
  pos[dfc] = u;
  for (int i = h[0][u]; i; i = e[i].x) {
    int v = e[i].v;
    if (!dfn[v]) {
      dfs(v);
      fth[v] = u;
    }
  }
}

int find(int x) {
  if (fa[x] == x) {
    return x;
  }
  int tmp = fa[x];
  fa[x] = find(fa[x]);
  if (dfn[sdm[mn[tmp]]] < dfn[sdm[mn[x]]]) {
    mn[x] = mn[tmp];
  }
  return fa[x];
}

void tar(int st) {
  dfs(st);
  for (int i = 1; i <= n; ++i) {
    fa[i] = sdm[i] = mn[i] = i;
  }
  for (int i = dfc; i >= 2; --i) {
    int u = pos[i], res = INF;
    for (int j = h[1][u]; j; j = e[j].x) {
      int v = e[j].v;
      if (!dfn[v]) {
        continue;
      }
      find(v);
      if (dfn[v] < dfn[u]) {
        res = std::min(res, dfn[v]);
      } else {
        res = std::min(res, dfn[sdm[mn[v]]]);
      }
    }
    sdm[u] = pos[res];
    fa[u] = fth[u];
    add(2, sdm[u], u);
    u = fth[u];
    for (int j = h[2][u]; j; j = e[j].x) {
      int v = e[j].v;
      find(v);
      if (sdm[mn[v]] == u) {
        idm[v] = u;
      } else {
        idm[v] = mn[v];
      }
    }
    h[2][u] = 0;
  }
  for (int i = 2; i <= dfc; ++i) {
    int u = pos[i];
    if (idm[u] != sdm[u]) {
      idm[u] = idm[idm[u]];
    }
  }
}

```

## Problems

### [Luogu P5180 Template Dominator Tree](https://www.luogu.com.cn/problem/P5180)

You can solve only the domination relation, recording how many nodes each node dominates during the process. Alternatively, you can build the dominator tree and compute the size of each node.

The code for the second approach is given below.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/graph/code/dom-tree/dom-tree_1.cpp"
    ```

### [ZJOI2012 Disaster](https://www.luogu.com.cn/problem/P2597)

Compute the dominator tree on the DAG and then compute the node sizes.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/graph/code/dom-tree/dom-tree_2.cpp"
    ```
