author: littleparrot12345

## Definition

In a tree, if node $x$ is chosen as the root and the longest path starting from $x$ is minimized, then $x$ is called the **center** of the tree.

## Properties

-   A tree's center is not necessarily unique, but there can be at most $2$ centers, and they are adjacent.
-   The center of a tree always lies on its diameter.
-   Paths from all nodes to their farthest nodes always intersect at the tree's center.
-   When the center is the root, the two paths to the diameter endpoints are the longest and second-longest paths.
-   When merging two trees by connecting an edge, connecting their centers minimizes the diameter of the new tree.
-   The distance from the tree's center to any other node is at most half the tree's diameter.

## Finding the Center

Find a node $x$ such that when used as root, the longest path is minimized.

### Steps

1.  Maintain $len1_x$, the longest path within the subtree of node $x$.
2.  Maintain $len2_x$, the longest path that doesn't overlap with $len1_x$.
3.  Maintain $up_x$, the longest path outside the subtree of node $x$, which must pass through $x$'s parent.
4.  Find node $x$ that minimizes $\max(len1_x, up_x)$; this $x$ is the tree's center.

???+ note "Reference Code"
    ```cpp
    // This code assumes node indices start from 1, i.e., i ∈ [1, n], using vector for adjacency list
    int d1[N], d2[N], up[N], x, y, mini = 1e9;  // d1, d2 correspond to len1, len2 above

    struct node {
      int to, val;  // to is the target node, val is the edge weight
    };

    vector<node> nbr[N];

    void dfsd(int cur, int fa) {  // compute len1 and len2
      for (node nxtn : nbr[cur]) {
        int nxt = nxtn.to, w = nxtn.val;  // nxt is the adjacent node, val is the edge weight
        if (nxt == fa) {
          continue;
        }
        dfsd(nxt, cur);
        if (d1[nxt] + w > d1[cur]) {  // can update longest path
          d2[cur] = d1[cur];
          d1[cur] = d1[nxt] + w;
        } else if (d1[nxt] + w > d2[cur]) {  // cannot update longest, but can update second-longest
          d2[cur] = d1[nxt] + w;
        }
      }
    }

    void dfsu(int cur, int fa) {
      for (node nxtn : nbr[cur]) {
        int nxt = nxtn.to, w = nxtn.val;
        if (nxt == fa) {
          continue;
        }
        up[nxt] = up[cur] + w;
        if (d1[nxt] + w != d1[cur]) {  // if the longest path in cur's subtree doesn't go through nxt
          up[nxt] = max(up[nxt], d1[cur] + w);
        } else {  // longest path goes through nxt, must use second-longest
          up[nxt] = max(up[nxt], d2[cur] + w);
        }
        dfsu(nxt, cur);
      }
    }

    void GetTreeCenter() {  // find the tree center(s), stored in x and y (y if two exist)
      dfsd(1, 0);
      dfsu(1, 0);
      for (int i = 1; i <= n; i++) {
        if (max(d1[i], up[i]) < mini) {  // found a node with smaller max(len1, up)
          mini = max(d1[i], up[i]);
          x = i;
          y = 0;
        } else if (max(d1[i], up[i]) == mini) {  // another center
          y = i;
        }
      }
    }
    ```

### Example

Consider the following tree:

```text
           A
          / \
         B   C
        / \   \
       D   E   F
```

-   The tree's diameter is $D \rightarrow B \rightarrow A \rightarrow C \rightarrow F$, with length $4$.
-   Node $A$ is the tree's center because the longest path from $A$ (to $D$ or $F$) is $2$.
-   If $B$ or $C$ is used as the root, the longest path from that node increases, so they are not centers.

### Time Complexity

The time complexity of this algorithm is $O(n)$, where $n$ is the number of nodes in the tree.

## References

-   [TutorialsPoint: Centers of a Tree](https://www.tutorialspoint.com/centers-of-a-tree)
-   [ProofWiki: Definition of Center of Tree](https://proofwiki.org/wiki/Definition:Center_of_Tree)
-   [Wikipedia: Tree (graph theory)](https://en.wikipedia.org/wiki/Tree_%28graph_theory%29#Properties)