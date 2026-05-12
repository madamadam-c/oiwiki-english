author: Chrogeek, HeRaNO, Dev-XYS, Dev-jqe

## Common Uses

In algorithm competitions, we sometimes need to maintain multi-dimensional information. In such cases, we often need tree-of-tree structures to record information.

## Implementation Principle

Consider how to use a tree-of-tree structure to perform point updates and rectangle queries on a two-dimensional plane. For the outer segment tree, the subtrees of the bottom-level nodes $1$ to $n$ represent the segment trees for rows $1$ to $n$, respectively. The parent nodes corresponding to these bottom-level nodes represent the region covered by the subtrees of their two children.

## Properties

### Space Complexity

Normally, we cannot build an inner segment tree for every node of the outer segment tree, because this requires too much space. Tree-of-tree structures usually use dynamic node allocation. For a single update, we touch $\log{n}$ nodes in the outer segment tree, and for each node's inner tree we touch $\log{n}$ nodes, so the maximum additional space produced by one update is $\log^2{n}$.

### Time Complexity

For a query operation, we perform $\log{n}$ operations on the outer segment tree, and each operation performs $\log{n}$ operations on an inner segment tree. Therefore, the time complexity is $\log^2{n}$.
An update operation has the same complexity as a query operation, also $\log^2{n}$.

## Classic Example

[Flowers Blooming](https://www.luogu.com.cn/problem/P3810): sort by the first dimension, then use a tree-of-tree structure to maintain the second and third dimensions.

## Example Code

Second-dimension query:

```cpp
int tree_query(int k, int l, int r, int x) {
  if (k == 0) return 0;
  if (1 <= l && r <= sec[x].y) return vec_query(ou_root[k], 1, p, 1, sec[x].z);
  int mid = l + r >> 1, res = 0;
  if (1 <= mid) res += tree_query(ou_ch[k][0], l, mid, x);
  if (sec[x].y > mid) res += tree_query(ou_ch[k][1], mid + 1, r, x);
  return res;
}
```

Second-dimension update:

```cpp
void tree_insert(int &k, int l, int r, int x) {
  if (k == 0) k = ++ou_tot;
  vec_insert(ou_root[k], 1, p, sec[x].z);
  if (l == r) return;
  int mid = l + r >> 1;
  if (sec[x].y <= mid)
    tree_insert(ou_ch[k][0], l, mid, x);
  else
    tree_insert(ou_ch[k][1], mid + 1, r, x);
}
```

Third-dimension query:

```cpp
int vec_query(int k, int l, int r, int x, int y) {
  if (k == 0) return 0;
  if (x <= l && r <= y) return data[k];
  int mid = l + r >> 1, res = 0;
  if (x <= mid) res += vec_query(ch[k][0], l, mid, x, y);
  if (y > mid) res += vec_query(ch[k][1], mid + 1, r, x, y);
  return res;
}
```

Third-dimension update:

```cpp
void vec_insert(int &k, int l, int r, int loc) {
  if (k == 0) k = ++tot;
  data[k]++;
  if (l == r) return;
  int mid = l + r >> 1;
  if (loc <= mid) vec_insert(ch[k][0], l, mid, loc);
  if (loc > mid) vec_insert(ch[k][1], mid + 1, r, loc);
}
```

## Related Algorithms

When facing problems with multi-dimensional information, if the problem does not require forced online processing, we can also consider divide-and-conquer algorithms such as **CDQ Divide and Conquer** or **Overall Binary Search** to avoid using advanced data structures and reduce implementation difficulty.
