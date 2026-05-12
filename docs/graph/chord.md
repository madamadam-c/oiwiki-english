Chordal graphs are a special type of graph where many NP-Hard problems on general graphs have excellent linear time complexity algorithms.

## Some Definitions and Properties

**Subgraph**: A graph whose vertex set and edge set are both subsets of the original graph's vertex set and edge set.

**Induced Subgraph**: A subgraph whose vertex set is a subset of the original graph's vertex set, and whose edge set contains all edges whose both endpoints are in the selected vertex set.

**Clique**: A complete subgraph.

**Maximal Clique**: A clique that is not a subgraph of another clique.

**Maximum Clique**: The clique with the maximum number of vertices.

**Clique Number**: The number of vertices in the maximum clique, denoted as $\omega(G)$.

**Minimum Coloring**: Using the minimum number of colors to color vertices such that all adjacent vertices have different colors.

**Chromatic Number**: The number of colors in a minimum coloring, denoted as $\chi(G)$.

**Maximum Independent Set**: The largest vertex set such that any two vertices in the set are not directly connected by an edge. The size of this set is denoted as $\alpha(G)$.

**Minimum Clique Cover**: Covering all vertices using the minimum number of cliques. The number of cliques used is denoted as $\kappa(G)$.

**Chord**: An edge connecting two non-adjacent vertices in a cycle.

**Chordal Graph**: A graph where every cycle of length greater than $3$ has a chord is called a chordal graph.

**Lemma 1**: Clique number $\omega(G)\le \chi(G)$ chromatic number

Proof: Consider coloring the induced subgraph of the maximum clique. At least $\omega(G)$ colors are needed.

**Lemma 2**: Maximum independent set size $\alpha(G)\le \kappa(G)$ minimum clique cover number

Proof: At most one vertex can be selected from each clique.

**Lemma 3**: Any induced subgraph of a chordal graph is always a chordal graph.

Proof: If a chordal graph has an induced subgraph that is not a chordal graph, then there exists a chordless cycle of length greater than $3$ in this induced subgraph. Regardless of how edges are added to the original graph (how to add edges), it would not make the original graph a chordal graph, contradiction.

**Lemma 4**: Any induced subgraph of a chordal graph cannot be a cycle with more than $3$ vertices.

Proof: A cycle with more than $3$ vertices is not a chordal graph. Use the above theorem to prove.

## Chordal Graph Recognition

### Problem Description

Given an undirected graph, determine whether it is a chordal graph.

### Vertex Cut

For two vertices $u,v$ on graph $G$, define the **vertex cut** between these two vertices as the set of vertices whose removal disconnects $u$ and $v$. If any proper subset of a vertex cut between $u,v$ is not a vertex cut, then this vertex cut is called a **minimal vertex cut**.

**Lemma 5**: The minimal vertex cut between $u,v$ on graph $G$ divides the original graph into several connected components. Let the connected component containing $u$ be $V_1$, and the one containing $v$ be $V_2$. Then for any vertex $a$ on the minimal vertex cut, $N(a)$ must contain vertices from both $V_1$ and $V_2$.

Proof: If $N(a)$ only contains vertices from at most one connected block in $V_1$ or $V_2$, then removing vertex $a$ from the vertex cut would still keep it disconnected, so the original vertex cut is not a minimal vertex cut.

**Lemma 6**: The induced subgraph of a minimal vertex cut between any two vertices on a chordal graph is always a clique.

Proof: When the size of the minimal vertex cut $\le 1$, the induced subgraph is certainly a clique.

Otherwise, assume there are two vertices $x,y$ on the minimal vertex cut. From **Lemma 5**, $N(x)$ has vertices in $V_1,V_2$, denoted as $x_1,x_2$. Similarly, denote $y_1,y_2$. Note that it is possible that $x_1=y_1,x_2=y_2$.

Since $V_1,V_2$ are both connected blocks, there exist shortest paths between the two vertex pairs $x_1,y_1$ and $x_2,y_2$. Let the shortest paths from $x,y$ inside $V_1,V_2$ be $x-x_1\sim y_1-y,x-x_2\sim y_2-y$. Then there exists a cycle $x-x_1\sim y_1-y-y_2\sim x_2-x$ on the graph. The size of this cycle is certainly $\ge 4$. According to the definition of chordal graph, there must be a chord on this cycle.

If this chord connects the two connected blocks $V_1,V_2$, then the vertex set is not a vertex cut. If this chord connects two vertices inside a single connected block or connects a vertex inside a connected block and a vertex on the vertex cut, both do not satisfy the property of shortest paths. So this chord can only connect vertices $x,y$.

Thus, it can be proven that any two vertices in each minimal vertex cut of a chordal graph have a direct edge between them. The property is proven.

### Simplicial Vertex

Let $N(x)$ denote the set of vertices adjacent to vertex $x$. If the induced subgraph of the vertex set $\{x\}+N(x)$ is a clique, then vertex $x$ is called a **simplicial vertex**.

**Lemma 7**: Any chordal graph has at least one simplicial vertex. A chordal graph that is not a complete graph has at least two non-adjacent simplicial vertices.

Proof: Mathematical induction. Consider each connected block separately.

Induction basis: When the graph is isomorphic to a complete graph, any vertex on the graph is a simplicial vertex. When the number of vertices $\le 3$, the lemma holds.

If the number of vertices $\ge 4$ and the graph is not a complete graph, there must exist $u,v$ such that $(u,v)\notin E$. Let $I$ be the minimal vertex cut between $u,v$. Let $A,B$ be the connected blocks where $u,v$ are located in the induced subgraph after removing $I$. Due to symmetry of the problem, we only consider side $A$. Let $L=A+I$. If $L$ is a complete graph, then $u$ is a simplicial vertex; if not, since $L$ is an induced subgraph of the original graph, it must also be a chordal graph, so it has two non-adjacent simplicial vertices. Since $I$ is a clique, any two vertices on it are adjacent, so there must be a simplicial vertex in $A$. This simplicial vertex is also a simplicial vertex when extended to the full graph.

Since each time the entire graph is divided into several connected blocks for proof, the size must decrease and all satisfy the property. So the induction holds.

### Perfect Elimination Sequence

Let $n=|V|$. A perfect elimination sequence $v_1,v_2,\ldots ,v_n$ is a permutation of $1,2,\ldots ,n$, satisfying that $v_i$ is a simplicial vertex in the induced subgraph of $\{v_i,v_{i+1},\ldots ,v_n\}$.

**Lemma 8**: An undirected graph is a chordal graph if and only if it has a perfect elimination sequence.

Sufficiency: A chordal graph with $1$ vertex has a perfect elimination sequence. From **Lemma 3** and **Lemma 7**, the perfect elimination sequence of a chordal graph with $n$ vertices can be obtained from the perfect elimination sequence of a chordal graph with $n-1$ vertices by adding one simplicial vertex.

Necessity: Suppose there is an undirected graph with a cycle of more than $3$ vertices that has a perfect elimination sequence. Let $v$ be the first vertex on the cycle to appear in the perfect elimination sequence. Let $v_1,v_2$ be the vertices connected to $v$ on the cycle. From the property of the perfect elimination sequence and the definition of simplicial vertex, $v_1,v_2$ have a direct edge between them, contradiction.

### Naive Algorithm

Each time find a **simplicial vertex** $v$, add it to the perfect elimination sequence.

Remove vertex $v$ and all its incident edges from the graph.

Repeat the above process. If all vertices are removed, then the original graph is a chordal graph and we have obtained a perfect elimination sequence; if there is no simplicial vertex on the graph, then the original graph is not a chordal graph.

Time complexity $O(n^4)$.

### MCS Algorithm

**Maximum Cardinality Search** is a method that can find the perfect elimination sequence of an undirected graph in $O(n+m)$ time.

Number the nodes in reverse order, that is, label vertices from $n$ to $1$.

Let $label_x$ denote how many labeled vertices are adjacent to vertex $x$. Each time, select the unlabeled vertex with the largest $label$ value for labeling.

Use a linked list to maintain for each $i$, all $x$ such that $label_x=i$.

Since each edge contributes at most $2$ to $\sum_{i=1}^n label_i$, time complexity is $O(n+m)$.

**Correctness Proof**:

Let $\alpha(x)$ be the position of $x$ in this sequence.
We need to prove that for any chordal graph, the sequence obtained by the algorithm is always a perfect elimination sequence. That is, for any vertex in the sequence, all vertices that come after it and are adjacent to it are pairwise adjacent.

**Lemma 9**: Consider three vertices $u,v,w$ satisfying $\alpha(u)<\alpha(v)<\alpha(w)$. If $uw$ is connected and $vw$ is not connected, then $w$ only contributes to $u$'s label, not to $v$'s. To make $v$ join the sequence before $u$, there must exist an $x$ satisfying $\alpha(v)<\alpha(x)$ and $vx$ connected but $ux$ not connected, i.e., $x$ only contributes to $v$ but not to $u$.

**Lemma 10**: Any chordal graph definitely does not have a sequence $v_0,v_1,\dots,v_k(k\ge 2)$ satisfying the following properties:

1.  $v_iv_j$ is connected if and only if $|i-j|=1$.
2.  $\alpha(v_0)>\alpha(v_i)(i\in[1,k])$.
3.  There exists $i\in[1,k-1]$ such that $\alpha(v_i)<\alpha(v_{i+1})<\dots<\alpha(v_k)$ and $\alpha(v_i)<\alpha(v_{i-1})<\dots<\alpha(v_1)<\alpha(v_k)<\alpha(v_0)$.

Proof:

Since $\alpha(v_1)<\alpha(v_k)<\alpha(v_0)$, and $v_1v_0$ is connected while $v_kv_0$ is not, by property 1, there exists $x$ such that $\alpha(v_k)<\alpha(x)$ and $v_kx$ is connected while $v_1x$ is not connected.

Consider the smallest $j\in(1,k]$ such that $v_jx$ is connected. We can deduce that $v_0x$ is not connected; otherwise $v_0v_1\cdots v_jx$ forms a chordless cycle of length $\ge 4$.

If $x<v_0$, then $v_0,v_1,\dots,v_j,x$ is also a sequence satisfying the properties; if $v_0<x$, then $x,v_j,\dots,v_1,v_0$ is also a sequence satisfying the properties.

In the derivation above, we enlarged $\min(v_0,v_k)$, and continuing indefinitely will definitely lead to a contradiction.

**Theorem 1**: For any chordal graph, the sequence obtained by the Maximum Cardinality Search algorithm is always a perfect elimination sequence.

Proof: Consider any three vertices $u,v,w$ satisfying $\alpha(u)<\alpha(v)<\alpha(w)$. We need to prove that if $uv$ is connected and $uw$ is connected, then $vw$ must also be connected.

Assume the opposite. Then $w,u,v$ is a sequence satisfying the properties in **Lemma 10**. We have proven that such a sequence does not exist, so contradiction, and $vw$ is connected.

Reference code:

```cpp
while (cur) {
  p[cur] = h[nww];
  rnk[p[cur]] = cur;
  h[nww] = nxt[h[nww]];
  lst[h[nww]] = 0;
  lst[p[cur]] = nxt[p[cur]] = 0;
  tf[p[cur]] = true;
  for (vector<int>::iterator it = G[p[cur]].begin(); it != G[p[cur]].end();
       it++)
    if (!tf[*it]) {
      if (h[deg[*it]] == *it) h[deg[*it]] = nxt[*it];
      nxt[lst[*it]] = nxt[*it];
      lst[nxt[*it]] = lst[*it];
      lst[*it] = nxt[*it] = 0;
      deg[*it]++;
      nxt[*it] = h[deg[*it]];
      lst[h[deg[*it]]] = *it;
      h[deg[*it]] = *it;
    }
  cur--;
  if (h[nww + 1]) nww++;
  while (nww && !h[nww]) nww--;
}
```

If the original graph is a chordal graph, the sequence obtained is a perfect elimination sequence; but since the original graph may not be a chordal graph, the sequence obtained is definitely not a perfect elimination sequence. So the problem becomes **determining whether the obtained sequence is a perfect elimination sequence of the original graph**.

### Determining Whether a Sequence is a Perfect Elimination Sequence

#### Naive Algorithm

According to the definition, sequentially check whether the vertices adjacent to $v_i$ in $\{v_i,v_{i+1},\ldots ,v_n\}$ form a clique. Time complexity $O(nm)$.

#### Optimized Algorithm

According to the definition of perfect elimination sequence, let the vertices adjacent to $v_i$ in $\{v_i,v_{i+1},\ldots , v_n\}$ in increasing order be $\{v_{c_1},v_{c_2},\ldots ,v_{c_k}\}$. Then we only need to check whether $v_{c_1}$ is directly connected to other vertices. Time complexity $O(n+m)$.

```cpp
jud = true;
for (int i = 1; i <= n; i++) {
  cur = 0;
  for (vector<int>::iterator it = G[p[i]].begin(); it != G[p[i]].end(); it++)
    if (rnk[p[i]] < rnk[*it]) {
      s[++cur] = *it;
      if (rnk[s[cur]] < rnk[s[1]]) swap(s[1], s[cur]);
    }
  for (int j = 2; j <= cur; j++)
    if (!st[s[1]].count(s[j])) {
      jud = false;
      break;
    }
}
if (!jud)
  printf("Imperfect\n");
else
  printf("Perfect\n");
```

Thus, the **chordal graph recognition problem** can be solved in $O(n+m)$ time.

## Maximal Cliques of Chordal Graphs

Let $N(x)$ be the set of vertices directly connected to $x$ and that appear after $x$ in the perfect elimination sequence. Then the maximal cliques of a chordal graph are always $\{x\}+N(x)$.

Proof: Consider a maximal clique $V$ of a chordal graph. Let $x$ be the first vertex of $V$ to appear in the perfect elimination sequence. We must have $V\subseteq \{x\}+N(x)$. Since $V$ is a maximal clique, $V=\{x\}+N(x)$.

A chordal graph has at most $n$ maximal cliques. To find each maximal clique of a chordal graph, we can check whether each $\{x\}+N(x)$ is a maximal clique.

Let $A=\{x\}+N(x),B=\{y\}+N(y)$. If $A\subsetneqq B$, then $A$ is not a maximal clique. At this time, in the perfect elimination sequence, $y$ is clearly before $x$.

Let $nxt_x$ denote the vertex in $N(x)$ that appears earliest in the perfect elimination sequence. Let $y*$ denote the vertex among all $y$ satisfying $A\subseteq B$ that appears latest. At this time, we must have $nxt_{y*}=x$, otherwise $y*$ is not the latest; let $y*=nxt_{y*}$ still satisfies the condition.

$A\subsetneqq B$ if and only if $|A|+1\le |B|$.

The problem becomes determining whether there exists $y$ such that $nxt_y=x$ and $|N(x)|+1\le |N(y)|$. Time complexity $O(n+m)$.

```cpp
for (int i = 1; i <= n; i++) {
  cur = 0;
  for (vector<int>::iterator it = G[p[i]].begin(); it != G[p[i]].end(); it++)
    if (rnk[p[i]] < rnk[*it]) {
      s[++cur] = *it;
      if (rnk[s[cur]] < rnk[s[1]]) swap(s[1], s[cur]);
    }
  fst[p[i]] = s[1];
  N[p[i]] = cur;
}
for (int i = 1; i <= n; i++) {
  if (!vis[p[i]]) ans++;
  if (N[p[i]] >= N[fst[p[i]]] + 1) vis[fst[p[i]]] = true;
}
```

## Chromatic Number / Clique Number of Chordal Graphs

A construction method: Color each vertex from back to front according to the perfect elimination sequence, giving each vertex the smallest color it can take. Time complexity $O(m+n)$.

Correctness proof: Let the number of colors used by this method be $t$. Then $t\ge \chi(G)$. Since each vertex on a clique requires a different color, $t=\omega(G)$. From **Lemma 1**, $t=\omega(G)\le \chi(G)$. In summary, $t=\chi(G)=\omega(G)$.

When we don't need the coloring scheme but only need the chromatic number/clique number of the chordal graph, we can take the maximum value of $|\{x\}+N(x)|$.

```cpp
for (int i = 1; i <= n; i++) ans = max(ans, deg[i] + 1);
```

## Maximum Independent Set / Minimum Clique Cover of Chordal Graphs

Maximum Independent Set: From front to back in the perfect elimination sequence, select all vertices that are not directly connected to already selected vertices.

Minimum Clique Cover: Let the maximum independent set be $\{v_1,v_2,\ldots ,v_t\}$. Then the set of cliques $\{\{v_1+N(v_1)\},\{v_2+N(v_2)\},\ldots ,\{v_t+N(v_t)\}\}$ is the minimum clique cover of the graph. Time complexity $O(n+m)$.

Correctness proof: Let the independent set number and clique cover number of this scheme be $t$. From the definition, $t\le \alpha(G),t\ge \kappa(G)$. From **Lemma 2**, $\alpha(G)\le \kappa(G)$. So $t=\alpha(G)=\kappa(G)$.

```cpp
for (int i = 1; i <= n; i++)
  if (!vis[p[i]]) {
    ans++;
    for (vector<int>::iterator it = G[p[i]].begin(); it != G[p[i]].end(); it++)
      vis[*it] = true;
  }
```

## Problems

[SPOJ FISHNET - Fishing Net](https://www.spoj.com/problems/FISHNET)

[P3196 [HNOI2008] Magical Kingdom](https://www.luogu.com.cn/problem/P3196)

[P3852 [TJOI2007] Children](https://www.luogu.com.cn/problem/P3852)

## References

[Chordal Graph Topics](https://yhx-12243.github.io/OI-transit/memos/15.html)

[2009 WC Lecture Notes](https://github.com/hzwer/shareOI/blob/master/%E5%9B%BE%E8%AE%BA/%E5%BC%A6%E5%9B%BE%E4%B8%8E%E5%8C%BA%E9%97%B4%E5%9B%BE_%E9%99%88%E4%B8%B9%E7%90%A6.pptx)

[Chordal Graph Summary - Rent Su Yu](https://www.cnblogs.com/zhoushuyu/p/8716935.html)

[R. E. Tarjan and M. Yannakakis, Simple linear-time algorithms to test chordality of graphs,test acyclicity of hypergraphs,and selectively reduce acyclic hypergraphs, SIAM J. Comput., 13 (1984), pp. 566–579.](https://dl.acm.org/doi/abs/10.1137/0213035)