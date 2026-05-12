## Dynamic Tree Divisor (Centroid) Decomposition

Dynamic centroid decomposition solves tree path information queries with **vertex/edge weight updates**.

### Centroid Tree

Let's review the centroid decomposition process.

For a node $x$, simple paths in its subtree are of two types: those passing through $x$ (composed of one or two paths starting from $x$), and those not passing through $x$ (already contained in the subtrees of its children).

To compute paths in a subtree, we select a centroid $rt$ as the division center, compute path information for paths passing through $rt$ in its subtree. Then for each child, we treat the connected component containing that child after removing $rt$ as a new subtree and recurse. The chosen centroid nodes form a tree structure called the **centroid tree**. It can be shown that the total size of connected components represented by nodes at the same level of the centroid tree is $O(n)$. This means the time complexity of centroid decomposition is related to the height of the centroid tree; if the height is $h$, the complexity is $O(nh)$.

It can be proven that when we always select the centroid of a connected component as the division center, the height of the centroid tree is minimized, at $O(\log n)$. This allows us to compute information for all $O(n^2)$ tree paths in $O(n \log n)$ time.

Since the tree structure never changes during dynamic centroid decomposition, the centroid tree structure also remains unchanged.

Reference code for building the centroid tree:

```cpp
void calcsiz(int x, int f) {
  siz[x] = 1;
  maxx[x] = 0;
  for (int j = h[x]; j; j = nxt[j])
    if (p[j] != f && !vis[p[j]]) {
      calcsiz(p[j], x);
      siz[x] += siz[p[j]];
      maxx[x] = max(maxx[x], siz[p[j]]);
    }
  maxx[x] =
      max(maxx[x], sum - siz[x]);  // maxx[x] is the largest subtree size when x is root
  if (maxx[x] < maxx[rt])
    rt = x;  // cannot use <= here, to ensure rt doesn't change during second calcsiz
}

void pre(int x) {
  vis[x] = true;  // mark x as excluded from future consideration
  for (int j = h[x]; j; j = nxt[j])
    if (!vis[p[j]]) {
      sum = siz[p[j]];
      rt = 0;
      maxx[rt] = inf;
      calcsiz(p[j], -1);
      calcsiz(rt, -1);  // run twice; second call computes subtree sizes with rt as root
      fa[rt] = x;
      pre(rt);  // record parent in centroid tree
    }
}

int main() {
  sum = n;
  rt = 0;
  maxx[rt] = inf;
  calcsiz(1, -1);
  calcsiz(rt, -1);
  pre(rt);
}
```

### Handling Updates

During queries and updates, we traverse ancestors in the centroid tree. Since the height of the centroid tree is at most $O(\log n)$, this maintains the desired complexity.

During dynamic centroid decomposition, we need information about distances from a node to its ancestors in the centroid tree. Since each node has at most $O(\log n)$ ancestors, we can precompute depth $dep[x]$ or use LCA to handle distance queries. **Note**: Distances from a node to its centroid tree ancestors are not necessarily increasing and cannot be accumulated.

During dynamic centroid decomposition, information from a node's ancestors in the centroid tree may be double-counted. The standard fix is to maintain two types of records for each component: one for distances to the centroid, and one for distances to the centroid's parent in the centroid tree. This will be illustrated in the examples.

??? note "Example [「ZJOI2007」Hide and Seek](https://www.luogu.com.cn/problem/P2056)"
    Given a tree with $n$ nodes, initially all nodes are black. Implement two operations:

    1. Toggle a node's color (black to white, or white to black);
    2. Query the distance between the two farthest black nodes.

    $n \leq 10^5, m \leq 5 \times 10^5$

    Build the centroid tree. For each node $x$, maintain two **deletable heaps**. $dist[x]$ stores distances from all black nodes in the component represented by $x$ to $x$. $ch[x]$ stores distances from black nodes in $x$'s children (in the centroid tree) and $x$ itself to $x$. Since this problem uses a greedy approach to find the answer, and paths from the same subtree cannot form a complete path, we only insert its own value and the maximum value from each subtree into $ch[x]$. We observe that the sum of the two largest values in $ch[x]$ (or all values if fewer than two) gives the longest path of black endpoints when the centroid is $x$. We maintain all node answers in a deletable heap $ans$, and the maximum value in $ans$ is the answer.

    We maintain $dist[x]$, $ch[x]$, and $ans$ based on the above definitions. When values in $dist[x]$ change, we can update $ch[x]$ and $ans$ in $O(\log n)$ time.

    Let's examine what happens to $dist[x]$ when we toggle a node's color. If the node was originally black, we delete; if it was white, we insert.

    Suppose we toggle node $x$. For each ancestor $u$, we insert or delete $dist(x, u)$ in $dist[u]$, while updating $ch[x]$ and $ans$. Specifically, we insert or delete value $0$ in $ch[x]$.

    Reference code:

    ```cpp
    --8<-- "docs/graph/code/dynamic-tree-divide/dynamic-tree-divide_1.cpp"
    ```

???+ note "Example [Luogu P6329 【Template】Centroid Tree | Seismic Waves](https://www.luogu.com.cn/problem/P6329)"
    Given a tree with $n$ nodes, each node has a weight $v[x]$. Implement two operations:

    1. Query the sum of weights of all nodes within distance $y$ from node $x$;
    2. Update node $x$'s weight to $y$, i.e., $v[x] = y$.

    We use a dynamic segment tree to store distance information.

    Similar to the previous problem, for each node we maintain a segment tree $dist[x]$ representing all nodes in centroid component $x$ and their distances to $x$. The index is the distance and the value is the node weight. Segment tree $ch[x]$ represents all nodes in centroid component $x$ and their distances to $x$'s parent in the centroid tree.

    In this problem, all queries and updates need to traverse ancestors in the centroid tree.

    Take a query as example. To query the sum of weights of nodes within distance $y$ from $x$, we first add the sum of weights with distance $0$ to $y$ from segment tree $dist[x]$. Then we traverse all ancestors $u$ of $x$, with $v$ being $u$'s parent. Let $d = dist(x, u)$. If we exclude the subtree containing $x$ (the one rooted at $v$), we add the sum with distance $0$ to $y - d$ from segment tree $dist[u]$. Since we double-counted the subtree rooted at $v$, we subtract the sum with distance $0$ to $y - d$ from segment tree $ch[v]$.

    During updates, we maintain both $dist[x]$ and $ch[x]$.

    Reference code:

    ```cpp
    --8<-- "docs/graph/code/dynamic-tree-divide/dynamic-tree-divide_2.cpp"
    ```