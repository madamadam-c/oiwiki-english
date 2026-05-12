## Introduction

Prerequisite: [heavy-light decomposition](../graph/hld.md)

Heavy-light decomposition has time complexity $O(n\log^2 n)$. The familiar LCT has time complexity $O(n\log n)$, but its constant factor is large and it may be slower than heavy-light decomposition. A global balanced binary tree provides an $O(n\log n)$ method with a relatively small constant.

A global balanced binary tree is actually a forest of binary trees, where each binary tree maintains one heavy chain. These binary trees are connected to each other: the root of each binary tree points to the parent of the head of the corresponding heavy chain, just like in LCT. Unlike LCT, however, a global balanced binary tree is static; once built, its shape does not change.

A global balanced binary tree supports path modifications and queries on a tree:

-   $O(\log n)$ to modify an entire path.
-   $O(\log n)$ to query an entire path.
-   $O(\log n)$ for LCA, subtree modification, subtree query, and similar operations, the same as heavy-light decomposition.

## Main Properties

1.  A global balanced binary tree consists of many binary trees connected by light edges. Each binary tree maintains one heavy chain of the original tree, and its inorder traversal is the order of increasing depth on that heavy chain. Each node appears in exactly one binary tree.
2.  Edges are heavy or light. Heavy edges are inside binary trees and are maintained like ordinary binary-tree edges, with left child, right child, and parent recorded. A light edge goes from the root of a binary tree to the parent of the top node of its corresponding heavy chain. A light edge records only the parent side: the child can access the parent, but not conversely. Note that edges in a global balanced binary tree do not correspond to edges in the original tree.
3.  Counting both heavy and light edges, the height of the global balanced binary tree is $O(\log n)$. This property guarantees its time complexity.

The following is an example of building a global balanced binary tree. The first figure is the original tree rooted at node 1. Solid lines are heavy edges.

![global-bst-1](images/global-bst-1.svg)

The second figure is the constructed global balanced binary tree. Dashed lines are light edges, solid lines are heavy edges, and each binary tree is circled in red.

![global-bst-2](images/global-bst-2.svg)

## Construction

First, as in ordinary heavy-light decomposition, run DFS once to find the heavy child of each node. Then start from the root and find the heavy chain containing it. Recursively build trees for the light children of these nodes and connect the light edges. Next, build a binary tree for the nodes on the heavy chain. Store the heavy-chain nodes in an array, compute for each node the sum of subtree sizes of its light children plus one, i.e. the size contributed by the node itself. Then find the weighted midpoint of the heavy chain and use it as the root of the binary tree. Recursively build the two sides and connect heavy edges.

Code:

???+ note "Implementation"
    ```cpp
    std::vector<int> G[N];
    int n, fa[N], son[N], sz[N];
    
    void dfsS(int u) {
      sz[u] = 1;
      for (int v : G[u]) {
        dfsS(v);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
      }
    }
    
    int b[N], bs[N], l[N], r[N], f[N], ss[N];
    
    // Builds a binary tree for points in b[bl, br), and returns its root.
    int cbuild(int bl, int br) {
      int x = bl, y = br;
      while (y - x > 1) {
        int mid = (x + y) >> 1;
        if (2 * (bs[mid] - bs[bl]) <= bs[br] - bs[bl])
          x = mid;
        else
          y = mid;
      }
      // Binary-search the midpoint weighted by bs.
      y = b[x];
      ss[y] = br - bl;  // ss: size of the heavy subtree in the binary tree.
      if (bl < x) {
        l[y] = cbuild(bl, x);
        f[l[y]] = y;
      }
      if (x + 1 < br) {
        r[y] = cbuild(x + 1, br);
        f[r[y]] = y;
      }
      return y;
    }
    
    int build(int x) {
      int y = x;
      do
        for (int v : G[y])
          if (v != son[y])
            f[build(v)] =
                y;  // Recursively build and connect a light edge from the binary-tree root.
      while (y = son[y]);
      y = 0;
      do {
        b[y++] = x;                              // Store points on the heavy chain.
        bs[y] = bs[y - 1] + sz[x] - sz[son[x]];  // Prefix sum of light-child sizes plus 1.
      } while (x = son[x]);
      return cbuild(0, y);
    }
    ```

The code shows that construction costs $O(n\log n)$. To prove the height is $O(\log n)$, consider jumping from any node to the root through parent pointers. Jumping across a light edge means moving to another heavy chain in the original tree, so by the properties of heavy-light decomposition there are at most $O(\log n)$ light-edge jumps. When building a binary tree, the root is chosen as the weighted midpoint including light-child sizes, so one heavy-edge jump at least doubles this weighted size; therefore there are also at most $O(\log n)$ heavy-edge jumps. The total height is $O(\log n)$.

## Queries

The remaining operations for path modification and path query are relatively simple. Start from the point to be operated on and jump upward to the root. Operating on all points of smaller depth on the same heavy chain is essentially operating on all nodes to the left of the target node in that heavy chain's binary tree. These operations can be decomposed into a series of subtree operations, similar to maintaining an ordinary binary tree, using subtree sums and subtree tags. The following implementation uses permanent tags. It is also possible to use `pushdown` for tags and `pushup` for subtree sums, but that is more complex because binary-tree operations are usually top-down, while here the jump path must first be determined before pushing down from top to bottom, increasing the constant factor.

Code:

???+ note "Implementation"
    ```cpp
    // a: subtree-add tag.
    // s: subtree sum, excluding add tags.
    int a[N], s[N];
    
    void add(int x) {
      bool t = true;
      int z = 0;
      while (x) {
        s[x] += z;
        if (t) {
          a[x]++;
          if (r[x]) a[r[x]]--;
          z += 1 + ss[l[x]];
          s[x] -= ss[r[x]];
        }
        t = (x != l[f[x]]);
        if (t && x != r[f[x]]) z = 0;  // Clear when jumping over a light edge.
        x = f[x];
      }
    }
    
    int query(int x) {
      int ret = 0;
      bool t = true;
      int z = 0;
      while (x) {
        if (t) {
          ret += s[x] - s[r[x]];
          ret -= 1ll * ss[r[x]] * a[r[x]];
          z += 1 + ss[l[x]];
        }
        ret += 1ll * z * a[x];
        t = (x != l[f[x]]);
        if (t && x != r[f[x]]) z = 0;  // Clear when jumping over a light edge.
        x = f[x];
      }
      return ret;
    }
    ```

For subtree operations, light children must also be considered. Maintain an additional subtree sum and subtree tag that include light children; this can solve [P3384 Template Heavy-Light Decomposition](https://www.luogu.com.cn/problem/P3384).

## Example Problem

??? note "[P4751 Template Dynamic DP & Dynamic Tree Divide And Conquer (Enhanced)](https://www.luogu.com.cn/problem/P4751)"
    The original page provides a full implementation for this problem. The core idea is to maintain two matrices for each point: one for the point plus its light children, and one for interval information on the binary tree. Updates climb through the global balanced binary tree and refresh affected matrices.

## References

[P4211 \[LNOI2014\] LCA | Global Balanced Binary Tree](https://www.luogu.com.cn/blog/nederland/globalbst)
