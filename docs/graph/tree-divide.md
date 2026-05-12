## Tree Divide and Conquer

Tree divide and conquer is suitable for handling large-scale tree path information problems.

??? note "Example 1: [Luogu P3806 Template: Tree Divide and Conquer 1](https://www.luogu.com.cn/problem/P3806)"
    Given a tree with $n$ nodes and weighted edges, there are $m$ queries. For each query, a number $k$ is given, asking whether there exists a pair of nodes with distance equal to $k$.
    
    $n\le 10000,m\le 100,k\le 10000000$

    We first randomly select a node as the root $\mathit{rt}$. All paths completely contained in its subtrees can be divided into two types: those passing through the current root, and those not passing through the current root. For paths passing through the current root, they can be further divided into two types: paths with the root as one endpoint, and paths with neither endpoint being the root. The latter type can be formed by merging two paths of the first type. Therefore, for the enumerated root $rt$, we first compute the contribution to the answer from paths in its subtrees that pass through this node, then recursively solve for paths not passing through this node in its subtrees.

    In this problem, for paths passing through the root $\mathit{rt}$, we first enumerate all its children $\mathit{ch}$, and compute the distances from all nodes in $\mathit{ch}$'s subtree to $\mathit{rt}$, using $\mathit{ch}$ as the root. Let the distance from node $i$ to the current root $rt$ be $\mathit{dist}_i$. Let $\mathit{tf}_{d}$ indicate whether there exists a node $v$ in previously processed subtrees such that $\mathit{dist}_v=d$. If a query's $k$ satisfies $tf_{k-\mathit{dist}_i}=true$, then there exists a path of length $k$. After determining whether edges in $\mathit{ch}$'s subtree can form a valid answer, we add these new distances to the $\mathit{tf}$ array.

    Note that when clearing the $\mathit{tf}$ array, we should not use `memset` directly. Instead, we should add the positions that were used to a queue and clear them through the queue. This ensures the correct time complexity.

    During tree divide and conquer, each layer's recursive processes handle each node once. If there are $h$ recursive layers, the total time complexity is $O(hn)$.

    If we always select the [centroid](./tree-centroid.md) of the subtree as the root, we can guarantee the minimum number of recursive layers, giving time complexity $O(n\log n)$. Therefore, tree divide and conquer is also called **centroid decomposition** in international competitive programming circles.

    Please note that after selecting a new root, you must recalculate the subtree sizes. Even a seemingly minor oversight can lead to incorrect time complexity or incorrectness.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/graph/code/tree-divide/tree-divide_1.cpp"
    ```

??? note "Example 2: [Luogu P4178 Tree](https://www.luogu.com.cn/problem/P4178)"
    Given a tree with $n$ nodes and weighted edges, and a number $k$, count the number of pairs of nodes with distance less than or equal to $k$.
    
    $n\le 40000,k\le 20000,w_i\le 1000$

    Since the query asks for the number of pairs with distance in $[0,k]$, we use a segment tree to support updates and queries.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/graph/code/tree-divide/tree-divide_2.cpp"
    ```

??? note "Example 3: [Luogu P2664 Tree Game](https://www.luogu.com.cn/problem/P2664)"
    A tree where each node has a given color. Define $s(i,j)$ as the number of colors on the path from $\mathit{i}$ to $\mathit{j}$, and $\mathit{sum_{i}}=\sum_{j=1}^n s(i,j)$. For all $1\leq i\leq n$, compute $sum_i$. ($1 \le n, c_i \le 10^5$)

    This problem is a good test of understanding and application of tree divide and conquer, making it a challenging example and practice problem.

    First, we need to understand a transformation. The problem defines $\mathit{sum_i}$ as the sum of the number of colors on paths from $i$ to all other nodes. However, using this definition directly in tree divide and conquer, it's difficult to count the answer, because it would be hard to merge information from two subtrees when the current root is involved. So we think of transforming the meaning of $\mathit{sum_i}$. For each color $j$, let $\mathit{cnt_j}$ be the number of paths with one endpoint being $i$ that contain color $j$. Then $\mathit{sum_i}$ is actually $\sum \mathit{cnt_j}$. This transformation changes the perspective: we consider the contribution of each color to $\mathit{sum_i}$. $\mathit{cnt_j}$ is easy to compute: whenever we encounter a new color, we do $\mathit{cnt_{col_u}}+=\mathit{size_u}$, where $\mathit{size_u}$ is the subtree size of $u$. This means all nodes in this subtree contribute one to the answer for $u$ on this color.

    Considering the tree divide and conquer process, we only need to consider two types of statistics separately:

    1.  Paths in the subtree with the current root as an endpoint, and their contribution to the root
    2.  Paths whose LCA is the current root, and their contribution to each node in the subtree

    Part 1 is relatively easy: since in tree divide and conquer, the number of recursive layers is at most $\log n$, at each layer we can traverse all subtrees, so we can use the definition of $\mathit{sum_i}$ to count while traversing.

    For part 2, let the current root be $u$, and let one of its child nodes be $d$. For any node $v$ in $d$'s subtree, the answer for $v$ can be divided into two parts:

    1.  Colors that appear on the path $(u, v)$, with count $\mathit{num}$. Let $\mathit{siz1}$ be the total size of all other subtrees of $u$ except $d$. Then the contribution of these colors to $v$'s answer is $\mathit{num}\times \mathit{siz1}$.
    2.  Colors $j$ that do not appear on the path $(u, v)$. Their contribution comes from $\mathit{cnt_j}$ of all other subtrees of $u$ except $d$, giving the answer $\sum_{j \notin (u, v)} \mathit{cnt_j}$.

    The above is the complete statistical approach. See the reference code for implementation details.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/graph/code/tree-divide/tree-divide_3.cpp"
    ```

## Edge Divide and Conquer

Similar to tree divide and conquer above, we select an edge that divides the tree into two parts as evenly as possible (so that the $\mathit{size}$ of the two subtrees connected by the edge are as close as possible). Then we recursively process the left and right subtrees and compute information.

However, this doesn't work well. Consider a star graph:

![Star graph](./images/tree-divide1.svg)

When a node has multiple children with similar $\mathit{size}$, the time complexity of edge divide and conquer becomes unacceptable.

If the graph is a binary tree, we can avoid the problem with star graphs. Therefore, we consider converting a multi-way tree into a binary tree.

Clearly, we can build this like a segment tree. Like this:

![Building the tree](./images/tree-divide2.svg)

Newly created nodes can be given appropriate information according to the problem requirements. For example, when counting path lengths, set the weight of original edges to $1$ and the weight of newly created edges to $0$.

Analyzing the complexity, we find that at most $O(n)$ additional nodes are created, so the total complexity is $O(n\log n)$.

Almost all problems solvable with tree divide and conquer can also be solved with edge divide and conquer (there are constant factor differences, but usually not tight), so no example problems are provided.

## Centroid Tree

A centroid tree is a reconstructed tree formed by changing the structure of the original tree to have a stable $\log n$ depth.

It is commonly used for problems with modifications that are independent of the original tree structure.

### Algorithm Analysis

We reconstruct the original tree by finding the centroid at each step of divide and conquer.

We connect the centroid found each time as a child of the centroid from the previous level. This forms a tree with $\log n$ layers.

Since the tree has $\log n$ layers, many originally problematic brute-force solutions have correct complexity on the centroid tree.

### Code Implementation

A small trick: each time, subtract the heavy child size of the previous layer's node from the previous layer's total size $\mathit{tot}$, which gives the total size of the current layer. This way, finding the centroid requires only one DFS.

???+ note "Reference Code"
    ```cpp
    #include <algorithm>
    #include <iostream>
    #include <vector>
    using namespace std;
    
    using IT = vector<int>::iterator;
    
    struct Edge {
      int to, nxt, val;
    
      Edge() {}
    
      Edge(int to, int nxt, int val) : to(to), nxt(nxt), val(val) {}
    } e[300010];
    
    int head[150010], cnt;
    
    void addedge(int u, int v, int val) {
      e[++cnt] = Edge(v, head[u], val);
      head[u] = cnt;
    }
    
    int siz[150010], son[150010];
    bool vis[150010];
    
    int tot, lasttot;
    int maxp, root;
    
    void getG(int now, int fa) {
      siz[now] = 1;
      son[now] = 0;
      for (int i = head[now]; i; i = e[i].nxt) {
        int vs = e[i].to;
        if (vs == fa || vis[vs]) continue;
        getG(vs, now);
        siz[now] += siz[vs];
        son[now] = max(son[now], siz[vs]);
      }
      son[now] = max(son[now], tot - siz[now]);
      if (son[now] < maxp) {
        maxp = son[now];
        root = now;
      }
    }
    
    struct Node {
      int fa;
      vector<int> anc;
      vector<int> child;
    } nd[150010];
    
    int build(int now, int ntot) {
      tot = ntot;
      maxp = 0x7f7f7f7f;
      getG(now, 0);
      int g = root;
      vis[g] = true;
      for (int i = head[g]; i; i = e[i].nxt) {
        int vs = e[i].to;
        if (vis[vs]) continue;
        int tmp = build(vs, ntot - son[vs]);
        nd[tmp].fa = now;
        nd[now].child.push_back(tmp);
      }
      return g;
    }
    
    int virtroot;
    
    int main() {
      int n;
      cin >> n;
      for (int i = 1; i < n; i++) {
        int u, v, val;
        cin >> u >> v >> val;
        addedge(u, v, val);
        addedge(v, u, val);
      }
      virtroot = build(1, n);
    }
    ```
