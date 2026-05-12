A persistent mergeable heap is generally used to solve the $k$-shortest paths problem.

If the time complexity of a mergeable heap is not amortized, then after making it persistent, the time complexity of a single operation is guaranteed to be $O(\log n)$; that is, special data will not cause the complexity to degrade.

## Persistent Leftist Tree

Before learning this topic, please first understand the related content of [Leftist Tree](./leftist-tree.md).

### Process

Recall the merge process of a leftist tree. Suppose we want to merge two leftist trees rooted at $x,y$, and the maintained leftist trees satisfy the min-heap property:

1.  If either node among $x,y$ is empty, return $x+y$.

2.  Choose the node with smaller weight among $x,y$ as the root of the merged leftist tree.

3.  Recursively merge $x$'s right subtree with $y$, and use the merged root as $x$'s right child.

4.  Maintain the leftist property of the current merged leftist tree, maintain the `dist` value, and return the selected root node.

Because each recursive step decreases `dist[x]+dist[y]` by one, and `dist[x]` is $O(\log n)$, at most $O(\log n)$ nodes are modified in one merge. Thus the time complexity is $O(\log n)$.

Persistence requires preserving historical information so that previous versions can be accessed later. To make a leftist tree persistent, copy the path that is modified along the way.

Therefore, the merge process for a persistent leftist tree is as follows:

1.  If either node among $x,y$ is empty, return $x+y$.

2.  Choose the node with smaller weight among $x,y$, create a copy $p$ of this node, and use it as the root of the merged leftist tree.

3.  Recursively merge $p$'s right subtree with $y$, and use the merged root as $p$'s right child.

4.  Maintain the leftist property of the leftist tree rooted at $p$, maintain its `dist` value, and return $p$.

Since one leftist-tree operation modifies and creates at most $O(\log n)$ nodes, if the number of operations is $m$, then both the time complexity and space complexity of a persistent leftist tree are $O(m\log n)$.

### Reference Implementation

```cpp
int merge(int x, int y) {
  if (!x || !y) return x + y;
  if (v[x] > v[y]) swap(x, y);
  int p = ++cnt;
  lc[p] = lc[x];
  v[p] = v[x];
  rc[p] = merge(rc[x], y);
  if (dist[lc[p]] < dist[rc[p]]) swap(lc[p], rc[p]);
  dist[p] = dist[rc[p]] + 1;
  return p;
}
```
