author:ouuan, Backl1ght, billchenchina, CCXXXI, ChickenHu, ChungZH, cjsoft, countercurrent-time, diauweb, Early0v0, Enter-tainer, EtaoinWu, H-J-Granger, H-Shen, Henry-ZHR, HeRaNO, hsfzLZH1, huaruoji, iamtwz, imp2002, Ir1d, kenlig, Konano, Lyccrius, Marcythm, Menci, NachtgeistW, PeterlitsZo, psz2007, shuzhouliu, SkqLiao, sshwy, SukkaW, therehello, TrisolarisHD, ttzztztz, vincent-163, WAAutoMaton, Hunter19019

## Definition

The Lowest Common Ancestor (LCA) of two nodes is the common ancestor of these two nodes that is farthest from the root.
For convenience, we denote the LCA of a set of nodes $S=\{v_1,v_2,\ldots,v_n\}$ as $\text{LCA}(v_1,v_2,\ldots,v_n)$ or $\text{LCA}(S)$.

## Properties

> The **Properties** section is translated from [wcipeg](http://wcipeg.com/wiki/Lowest_common_ancestor) with modifications.

1.  $\text{LCA}(\{u\})=u$;
2.  $u$ is an ancestor of $v$ if and only if $\text{LCA}(u,v)=u$;
3.  If $u$ is not an ancestor of $v$ and $v$ is not an ancestor of $u$, then $u$ and $v$ lie in two different subtrees of $\text{LCA}(u,v)$;
4.  In a preorder traversal, $\text{LCA}(S)$ appears before all elements of $S$; in a postorder traversal, $\text{LCA}(S)$ appears after all elements of $S$;
5.  The LCA of the union of two node sets is the LCA of the LCAs of each set, i.e., $\text{LCA}(A\cup B)=\text{LCA}(\text{LCA}(A), \text{LCA}(B))$;
6.  The LCA of two nodes must lie on the shortest path between them;
7.  $d(u,v)=h(u)+h(v)-2h(\text{LCA}(u,v))$, where $d$ is the distance between two nodes on the tree, and $h$ represents the distance from a node to the root.

## Algorithms

### Naive Algorithm

#### Procedure

Each time, we can move the node with greater depth upward. Clearly, on a tree, the two nodes will eventually meet, and the meeting point is the desired LCA.
Alternatively, we can first adjust the depths of the two nodes to be equal, then move them upward together; they will also eventually meet.

#### Complexity

The naive algorithm requires a DFS of the entire tree for preprocessing, with time complexity $O(n)$, and each query takes $\Theta(n)$. If the tree has random properties, the time complexity is related to the expected height of this random tree.

### Binary Lifting

#### Procedure

Binary lifting is the most classic method for finding LCA. It is an improvement over the naive algorithm. By preprocessing the $\text{fa}_{x,i}$ array, the cursor can move quickly, greatly reducing the number of jumps. $\text{fa}_{x,i}$ represents the $2^i$-th ancestor of node $x$. The $\text{fa}_{x,i}$ array can be preprocessed using DFS.

Now let's see how to optimize these jumps:
In the first phase of adjusting the cursor, we need to move nodes $u$ and $v$ to the same depth. We can compute the depth difference between $u$ and $v$, denoted as $y$. By decomposing $y$ into binary, we optimize $y$ cursor jumps to "the number of `1`s in the binary representation of $y$" cursor jumps.
In the second phase, we iterate from the largest $i$ down to $0$ (inclusive). If $\text{fa}_{u,i}\not=\text{fa}_{v,i}$, then $u\gets\text{fa}_{u,i},v\gets\text{fa}_{v,i}$. The final LCA is $\text{fa}_{u,0}$.

#### Complexity

Binary lifting has preprocessing time complexity $O(n \log n)$, and each query takes $O(\log n)$.
Additionally, binary lifting can reduce cache misses and improve efficiency by swapping the two dimensions of the `fa` array so that the smaller dimension comes first.

??? note "Example"
    [HDU 2586 How far away?](https://acm.hdu.edu.cn/showproblem.php?pid=2586) - Query shortest paths on a tree.

    First find the LCA, then use property 7 to solve. Alternatively, compute the result directly while finding the LCA.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/graph/code/lca/lca_1.cpp"
    ```

### Tarjan Algorithm

#### Procedure

Tarjan's algorithm is an **offline algorithm** that uses [Disjoint Set Union (DSU)](../ds/dsu.md) to record ancestors of nodes. The approach is as follows:

1.  First, accept the input edges (adjacency list) and query edges (stored in another adjacency list). Query edges are virtually added edges; for convenience, each time a query edge is input, both this edge and its reverse edge are added to the `queryEdge` array.
2.  Then perform a DFS traversal, using a `visited` array to record whether a node has been visited and `parent` to record the parent of the current node.
3.  This involves **backtracking**. When we traverse to a node, we consider its root to be itself. After all DFS traversals starting from this node as root are completed, we set this node's root to its parent.
4.  During backtracking, if for a node, another node in the query edge has also been visited, we directly update the LCA result for that query edge.
5.  Finally, output the results.

#### Complexity

Tarjan's algorithm requires initializing the DSU, so preprocessing takes $O(n)$.

The naive Tarjan algorithm processes all $m$ queries in $O(m \alpha(m+n, n) + n)$, but Tarjan's constant factor is larger than binary lifting. An $O(m + n)$ implementation exists.

???+ warning "Note"
    There is no statement like "the DSU properties used in the naive Tarjan LCA algorithm are special, so a single call to `find()` has amortized $O(1)$ time complexity."
    
    The complexity of the following naive Tarjan implementation is $O(m \alpha(m+n, n) + n)$. If you need strictly linear complexity, refer to [Gabow and Tarjan's 1983 paper](https://dl.acm.org/doi/pdf/10.1145/800061.808753), which gives an $O(m + n)$ solution.

#### Implementation

??? note "Reference Code"
    ```cpp
    --8<-- "docs/graph/code/lca/lca_tarjan.cpp"
    ```

### Reducing LCA to RMQ using Euler Tour

#### Definition

When performing DFS on a tree, we record the node number each time we visit or backtrack from a node, resulting in a sequence of length $2n-1$, called the Euler tour sequence of the tree.

In the following, we denote the position of node $u$'s first appearance in the Euler tour sequence as $pos(u)$ (also called the Euler tour order of node $u$), and denote the Euler tour sequence itself as $E[1..2n-1]$.

#### Procedure

With the Euler tour sequence, the LCA problem can be reduced to an RMQ problem in linear time, i.e., $pos(LCA(u, v))=\min\{pos(k)|k\in E[pos(u)..pos(v)]\}$.

This identity is easy to understand: on the path from $u$ to $v$, we must pass through $LCA(u,v)$, but we will not pass through ancestors of $LCA(u,v)$. Therefore, the node with the minimum Euler tour order among those encountered from $u$ to $v$ is exactly $LCA(u, v)$.

Computing the Euler tour sequence with DFS takes $O(n)$ time, and the sequence length is also $O(n)$. Thus, the LCA problem can be reduced to an RMQ problem of equal scale in $O(n)$ time.

#### Implementation

???+ note "Reference Code"
    ```cpp
    int dfn[N << 1], pos[N], tot, st[30][(N << 1) + 2],
        rev[30][(N << 1) + 2];  // rev represents the node number corresponding to the minimum depth
    
    void dfs(int cur, int dep) {
      dfn[++tot] = cur;
      depth[tot] = dep;
      pos[cur] = tot;
      for (int i = head[t]; i; i = side[i].next) {
        int v = side[i].to;
        if (!pos[v]) {
          dfs(v, dep + 1);
          dfn[++tot] = cur, depth[tot] = dep;
        }
      }
    }
    
    void init() {
      for (int i = 2; i <= tot + 1; ++i)
        lg[i] = lg[i >> 1] + 1;  // Precompute lg to replace log2 for better constants
      for (int i = 1; i <= tot; i++) st[0][i] = depth[i], rev[0][i] = dfn[i];
      for (int i = 1; i <= lg[tot]; i++)
        for (int j = 1; j + (1 << i) - 1 <= tot; j++)
          if (st[i - 1][j] < st[i - 1][j + (1 << i - 1)])
            st[i][j] = st[i - 1][j], rev[i][j] = rev[i - 1][j];
          else
            st[i][j] = st[i - 1][j + (1 << i - 1)],
            rev[i][j] = rev[i - 1][j + (1 << i - 1)];
    }
    
    int query(int l, int r) {
      int k = lg[r - l + 1];
      return st[k][l] < st[k][r + 1 - (1 << k)] ? rev[k][l]
                                                : rev[k][r + 1 - (1 << k)];
    }
    ```

When we need to query the LCA of a pair $(u, v)$, we just query the node corresponding to the minimum value on the interval $[\min\{pos[u], pos[v]\}, \max\{pos[u], pos[v]\}]$.

If using a Sparse Table to solve the RMQ problem, this algorithm does not support online modifications. Preprocessing takes $O(n\log n)$ time, and each LCA query takes $O(1)$.

### Heavy-Light Decomposition

The LCA is the node with smaller depth when the two cursors are moved to the same heavy path.

Heavy-light decomposition has preprocessing time complexity $O(n)$ and each query takes $O(\log n)$, with a relatively small constant.

### Link Cut Tree

In a [Link Cut Tree](../ds/lct.md), let the nodes of two consecutive [access](../ds/lct.md#access) operations be `u` and `v`. The node returned by the second [access](../ds/lct.md#access) operation is the LCA of `u` and `v`.

Without link and cut operations, a single query using Link Cut Tree takes $O(\log n)$.

### Standard RMQ

Earlier we discussed reducing the LCA problem to RMQ using Euler tour, and the bottleneck is in RMQ. If we can solve RMQ in $O(n) \sim O(1)$, then we can also solve LCA in $O(n) \sim O(1)$.

Note that adjacent values in the Euler tour differ by 1 or -1, so we can use $O(n) \sim O(1)$ [Plus/Minus 1 RMQ](../topic/rmq.md#plus-minus-1-rmq).

Time complexity $O(n) \sim O(1)$, space complexity $O(n)$, supports online queries, with a relatively large constant.

#### Example [Luogu P3379 Template: Lowest Common Ancestor](https://www.luogu.com.cn/problem/P3379)

??? note "Reference Code"
    ```cpp
    --8<-- "docs/graph/code/lca/lca_2.cpp"
    ```

## Practice Problems

-   [Ancestor Query](https://loj.ac/problem/10135)
-   [Truck Transport](https://loj.ac/problem/2610)
-   [Distance Between Nodes](https://loj.ac/problem/10130)
