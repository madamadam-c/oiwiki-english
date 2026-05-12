author: H-J-Granger, accelsao, Ir1d, Early0v0, Henry-ZHR, HeliumOI, AntiLeaf, ShizuhaAki, pukui

## Blossom Algorithm

The Blossom Algorithm (also called the Edmonds' Blossom Algorithm) can solve the maximum cardinality matching problem in general graphs. This algorithm was proposed by Jack Edmonds in 1961. With some modifications, it can also solve the maximum weight matching problem in general graphs. This algorithm was the first to prove that maximum matching has polynomial complexity.

The difference between general graph matching and bipartite graph matching is that general graphs may contain odd cycles.

![general-matching-1](./images/general-matching-1.png)

Take this graph as an example. If we directly invert (swap matching edges and non-matching edges), the resulting $M$ would be invalid, as some vertices would appear in two matchings. The problem lies in the odd cycle.

Now consider the augmenting algorithm for general graphs. From the perspective of bipartite graphs, we enumerate an unmatched vertex each time, set it as the root, label it as **"o"**, then alternately label vertices as **"o"** and **"i"**. It is not hard to find that the edge from **"i"** to **"o"** is a matching edge.

Assume the current vertex is $v$ and the adjacent vertex is $u$. There are two cases:

1.  If $u$ has not been visited: when $u$ is an unmatched vertex, we have found an augmenting path. Otherwise, we look for augmenting paths from $u$'s partner.
2.  If $u$ has been visited: encountering label "o" represents the need to **contract a blossom**. Otherwise, it represents encountering an even cycle, which we skip.

For the case of even cycles, we can treat it as a bipartite graph and ignore it. After contracting the blossom, we continue searching for augmenting paths in the new graph.

![general-matching-2](./images/general-matching-2.png)

Let the original graph be $G$ and the contracted graph be $G'$. We only need to prove:

1.  If $G$ has an augmenting path, $G'$ also has one.
2.  If $G'$ has an augmenting path, $G$ also has one.

![general-matching-3](./images/general-matching-3.png)

Let the non-tree edge (the edge that forms the cycle) be $(u, v)$, and define the blossom root $h = \text{LCA}(u, v)$. The odd cycle is alternating, and exactly two edges incident to $h$ are of the same type—they are both non-matching edges. Therefore, the tree edge entering $h$ is definitely a matching edge, and edges from other vertices on the cycle to outside the cycle are all non-matching edges.

From observation, there are two ways to exit from an edge outside the cycle: clockwise or counterclockwise.

![general-matching-4](./images/general-matching-4.png)

Therefore, whether to contract the blossom or not does not affect correctness.

In implementation, after finding a **blossom**, we don't actually need to contract it; we can use an array to record which blossom each vertex belongs to under which root.

### Complexity Analysis

Each time we search for augmenting paths, we traverse all edges. When encountering **blossoms**, we maintain the vertices on the blossoms, taking $O(|E|^2)$ time.

Enumerating all unmatched vertices for augmenting paths takes $O(|V||E|^2)$ total.

### Reference Code

??? note "Reference Code"
    ```cpp
    // graph
    template <typename T>
    class graph {
     public:
      struct edge {
        int from;
        int to;
        T cost;
      };
    
      vector<edge> edges;
      vector<vector<int>> g;
      int n;
    
      graph(int _n) : n(_n) { g.resize(n); }
    
      virtual int add(int from, int to, T cost) = 0;
    };
    
    // undirectedgraph
    template <typename T>
    class undirectedgraph : public graph<T> {
     public:
      using graph<T>::edges;
      using graph<T>::g;
      using graph<T>::n;
    
      undirectedgraph(int _n) : graph<T>(_n) {}
    
      int add(int from, int to, T cost = 1) {
        assert(0 <= from && from < n && 0 <= to && to < n);
        int id = (int)edges.size();
        g[from].push_back(id);
        g[to].push_back(id);
        edges.push_back({from, to, cost});
        return id;
      }
    };
    
    // blossom / find_max_unweighted_matching
    template <typename T>
    vector<int> find_max_unweighted_matching(const undirectedgraph<T> &g) {
      std::mt19937 rng(std::random_device{}());
      vector<int> match(g.n, -1);   // matching
      vector<int> aux(g.n, -1);    // timestamp
      vector<int> label(g.n);        // "o" or "i"
      vector<int> orig(g.n);         // blossom root
      vector<int> parent(g.n, -1);  // parent node
      queue<int> q;
      int aux_time = -1;
    
      auto lca = [&](int v, int u) {
        aux_time++;
        while (true) {
          if (v != -1) {
            if (aux[v] == aux_time) {  // found visited vertex, which is LCA
              return v;
            }
            aux[v] = aux_time;
            if (match[v] == -1) {
              v = -1;
            } else {
              v = orig[parent[match[v]]];  // continue searching from matched vertex's parent
            }
          }
          swap(v, u);
        }
      };  // lca
    
      auto blossom = [&](int v, int u, int a) {
        while (orig[v] != a) {
          parent[v] = u;
          u = match[v];
          if (label[u] == 1) {  // initial vertex set to "o" to find augmenting path
            label[u] = 0;
            q.push(u);
          }
          orig[v] = orig[u] = a;  // contract blossom
          v = parent[u];
        }
      };  // blossom
    
      auto augment = [&](int v) {
        while (v != -1) {
          int pv = parent[v];
          int next_v = match[pv];
          match[v] = pv;
          match[pv] = v;
          v = next_v;
        }
      };  // augment
    
      auto bfs = [&](int root) {
        fill(label.begin(), label.end(), -1);
        iota(orig.begin(), orig.end(), 0);
        while (!q.empty()) {
          q.pop();
        }
        q.push(root);
        // initial vertex set to "o", here we use "0" for "o" and "1" for "i"
        label[root] = 0;
        while (!q.empty()) {
          int v = q.front();
          q.pop();
          for (int id : g.g[v]) {
            auto &e = g.edges[id];
            int u = e.from ^ e.to ^ v;
            if (label[u] == -1) {  // found unvisited vertex
              label[u] = 1;        // label as "i"
              parent[u] = v;
              if (match[u] == -1) {  // found unmatched vertex
                augment(u);          // find augmenting path
                return true;
              }
              // found matched vertex, add her matched vertex to queue to extend alternating tree
              label[match[u]] = 0;
              q.push(match[u]);
              continue;
            } else if (label[u] == 0 && orig[v] != orig[u]) {
              // found visited vertex with same label "o", found "blossom"
              int a = lca(orig[v], orig[u]);
              // find LCA then contract blossom
              blossom(u, v, a);
              blossom(v, u, a);
            }
          }
        }
        return false;
      };  // bfs
    
      auto greedy = [&]() {
        vector<int> order(g.n);
        // randomly shuffle order
        iota(order.begin(), order.end(), 0);
        shuffle(order.begin(), order.end(), rng);
    
        // match vertices that can be matched
        for (int i : order) {
          if (match[i] == -1) {
            for (auto id : g.g[i]) {
              auto &e = g.edges[id];
              int to = e.from ^ e.to ^ i;
              if (match[to] == -1) {
                match[i] = to;
                match[to] = i;
                break;
              }
            }
          }
        }
      };  // greedy
    
      // first perform random matching
      greedy();
      // search augmenting paths for unmatched vertices
      for (int i = 0; i < g.n; i++) {
        if (match[i] == -1) {
          bfs(i);
        }
      }
      return match;
    }
    ```

??? note "[UOJ #79. General Graph Maximum Matching](https://uoj.ac/problem/79)"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/general-match/general_match_1.cpp"
    ```

## General Graph Matching Algorithm Based on Gaussian Elimination

???+ tip "Note"
    Before reading the following content, you may need to read the matrix-related content in the "Linear Algebra" section:
    
    -   [Matrix](../../math/linear-algebra/matrix.md)
    -   [Determinant](../../math/linear-algebra/determinant.md)
    -   [Gaussian Elimination](../../math/numerical/gauss.md)

This section introduces a general graph matching algorithm based on Gaussian elimination. Compared to the traditional Blossom Algorithm, its advantage is that it is easier to understand and implement, and it conveniently solves problems such as "essential vertices in maximum matching". Its disadvantage is that the constant factor is relatively large, as Gaussian elimination runs roughly $O(n^3)$ in practice, while the Blossom Algorithm generally does not reach this bound.

### Preliminaries: Tutte Matrix

**Definition**: For an undirected graph $G = (V, E)$ with $n$ vertices, its Tutte matrix $\tilde{A}(G)$ is an $n \times n$ matrix where:

$$
\tilde{A}(G)_{i,j} = \begin{cases}
x_{i,j}, & i<j,\; (v_i, v_j)\in E \\
-x_{i,j}, & i > j,\; (v_i, v_j) \in E \\
0, & \text{otherwise}
\end{cases}
$$

Where $x_{i,j}$ is a variable, so $\tilde{A}(G)$ contains $|E|$ variables in total.

Without ambiguity, we abbreviate $\tilde{A}(G)$ to $\tilde{A}$ in the following.

**Theorem** (Tutte's Theorem): $G$ has a perfect matching if and only if $\det \tilde{A} \ne 0$.

??? note "Proof"
    We introduce the concept of "even cycle cover": an even cycle cover of an undirected graph $G$ uses several even cycles (including 2-cycles) to cover all vertices without overlap and without omission.
    
    It is easy to prove that $G$ has a perfect matching if and only if $G$ has an even cycle cover.
    
    -   If $G$ has an even cycle cover, we can take every other edge in each cycle to obtain a perfect matching.
    -   If $G$ has a perfect matching, we can extract the 2-cycles corresponding to matching edges to obtain an even cycle cover.
    
    Then we prove that $G$ has an even cycle cover if and only if $\tilde{A} \ne 0$.
    
    Consider the definition of the determinant:
    
    $$
    \det A = \sum_{\pi} (-1)^{\pi} \prod_{i} A_{i, \pi_i}
    $$
    
    Where $\pi$ is any permutation, and $(-1)^{\pi}$ is $-1$ if the number of inversions in $\pi$ is odd, otherwise $1$.
    
    It is not difficult to see that each permutation can be regarded as a cycle cover of $G$. If there is an odd cycle in this cycle cover, the sum after flipping this cycle is definitely $0$. Therefore, only even cycle covers can make the determinant non-zero, completing the proof.

**Theorem**: $\operatorname{rank} \tilde{A}$ is always even, and the size of the maximum matching in $G$ equals half of $\operatorname{rank} \tilde{A}$.

??? note "Proof"
    The rank of a skew-symmetric matrix must be even; the latter is left for the reader to verify.

In practice, it is impossible to carry $|E|$ variables during computation. Instead, we can take a number field—for example, take the residue system modulo some prime $p$—and replace each variable with a randomly selected number from $\mathcal{Z}_p$, then compute. Without ambiguity, we use $\tilde{A}$ directly to represent the replaced matrix in the following.

**Theorem**: $\operatorname{rank} \tilde{A}$ is at most twice the size of the maximum matching in $G$, and they are equal with probability at least $1 - \frac{n}{p}$.

Considering that $n$ in general graph maximum matching generally does not exceed $10^3$, in practice, taking a prime around $10^9$ is sufficient.

By the theorem, if we only need to find the number of maximum matching, and not the matching scheme, we can simply use Gaussian elimination once to find $\operatorname{rank} \tilde{A}$, which is much simpler than the Blossom Algorithm. However, if we need to output the scheme, it is slightly more complex, and we need to use the algorithm introduced below.

### Constructing a Perfect Matching

From Tutte's Theorem and the above theorem, if $G$ has a perfect matching, then $\tilde{A}$ has a high probability of being full rank. For convenience, the following description omits "with high probability".

Label vertex $i$ in $G$ as $v_i$. Furthermore, we have the following theorem:

**Theorem**: $\tilde{A}^{-1}_{j,i} \ne 0 \iff G - \{v_i, v_j\}$ has a perfect matching.

???+ tip "Inverse Matrix and Adjugate Matrix"
    For any $n \times n$ matrix $A$, define its adjugate matrix as $A^*_{i, j} = (-1)^{i + j} M_{j, i}$, where $M_{j, i}$ is the minor obtained by deleting row $j$ and column $i$. In other words, if $M$ is the matrix of cofactors of $A$, then $A^* = M^T$.
    
    **Theorem**: If $A$ is invertible, then $A^{-1} = \frac{1}{\det A} A^*$.
    
    So $A^{-1}_{j, i} \ne 0 \iff M_{i, j} \ne 0$, which means the submatrix obtained by deleting row $i$ and column $j$ from $A$ is full rank.

In other words, if $(v_i, v_j) \in E$ and $\tilde{A}^{-1}_{j, i} \ne 0$, it indicates there exists a perfect matching scheme containing edge $(v_i, v_j)$. We call such an edge a **feasible edge**.

From the above theorem, for an undirected graph $G$ with a perfect matching, we can obtain a brute-force algorithm to find a perfect matching: enumerate $i, j$ each time—if $(v_i, v_j)$ is a feasible edge (the edge exists and $\tilde{A}^{-1}_{j, i} \ne 0$)—add $(v_i, v_j)$ to the matching scheme, delete both vertices from $G$, and recalculate $\tilde{A}^{-1}$.

We need to perform $\frac{n}{2}$ rounds in total, each round taking $O(n^3)$, for a total complexity of $O(n^4)$, which is somewhat slow. In fact, when recalculating $\tilde{A}^{-1}$, we don't need to compute the inverse matrix via Gaussian elimination each time. Instead, we can use the following theorem:

**Theorem** (Elimination Theorem): Let

$$
A = \begin{bmatrix}
  a_{1, 1} & v^T \\
  u & B
\end{bmatrix} \quad A^{-1} = \begin{bmatrix}
  \hat a^{1, 1} & \hat v^T \\
  \hat u & \hat B
\end{bmatrix}
$$

And if $\hat a_{1, 1} \ne 0$, then we have

$$
B^{-1} = \hat B - \frac{\hat u \hat v^T}{\hat a_{1, 1}}
$$

The theorem describes the case of eliminating the first row and column. In fact, it can be very obviously extended to the case of eliminating any row and column. Therefore, we only need to compute $\tilde{A}^{-1}$ once at the beginning of the algorithm, and each time we delete two vertices, we only need to perform two $O(n^2)$ elimination operations.

??? note "The description is somewhat abstract; refer to C++ code"
    ```cpp
    void eliminate(int A[][MAXN], int r, int c) {  // eliminate row r and column c
      row_marked[r] = col_marked[c] = true;        // already eliminated
    
      int inv = quick_power(A[r][c], p - 2);  // multiplicative inverse
    
      for (int i = 1; i <= n; i++)
        if (!row_marked[i] && A[i][c]) {
          int tmp = (long long)A[i][c] * inv % p;
    
          for (int j = 1; j <= n; j++)
            if (!col_marked[j] && A[r][j])
              A[i][j] = (A[i][j] - (long long)tmp * A[r][j]) % p;
        }
    }
    ```

We need to perform $\frac{n}{2}$ rounds in total, each round with $O(n^2)$ complexity. Therefore, the above algorithm can find a perfect matching in $O(n^3)$ time.

### Constructing Maximum Matching

We have just solved the problem of constructing a perfect matching, but when solving problems, we generally need the maximum matching.

As mentioned earlier, the size of the maximum matching in $G$ equals half of $\operatorname{rank} \tilde{A}$. If we can find a largest full-rank submatrix of $\tilde{A}$, then finding a perfect matching on the induced subgraph corresponding to this submatrix will yield a maximum matching of $G$.

From another perspective, if $G$ has a perfect matching, then $\tilde{A}$ is full rank, meaning the rows of $\tilde{A}$ are linearly independent. Therefore, if $\tilde{A}$ is not full rank, we can find a basis of $\tilde{A}$ and then keep only the rows and columns corresponding to the basis to obtain a largest full-rank submatrix of $\tilde{A}$.

After finding the largest full-rank submatrix, use the algorithm above to find a perfect matching on the induced subgraph, which yields a maximum matching of the original graph. Note that since there may be row swaps during Gaussian elimination, when implementing, we need to maintain the vertex numbering carefully.

??? note "[UOJ #79. General Graph Maximum Matching](https://uoj.ac/problem/79)"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/general-match/general_match_2.cpp"
    ```

## Exercises

-   [UOJ #79. General Graph Maximum Matching](https://uoj.ac/problem/79)
-   [UOJ#171.【WC2016】Challenge NPC](https://uoj.ac/problem/171)

## References

1.  Mucha M, Sankowski P.[Maximum matchings via Gaussian elimination](http://web.eecs.umich.edu/~pettie/matching/Mucha-Sankowski-maximum-matching-matrix-multiplication.pdf)
2.  Zhou Zixin, Yang Jiaqi. General Graph Matching Based on Linear Algebra
3.  ZYQN [General Graph Matching Algorithm Based on Linear Algebra](https://oi.cyo.ng/wp-content/uploads/2017/02/maximum_matchings_via_gaussian_elimination.pdf)