author: Dev-jqe, HeRaNO, huaruoji

## Common Uses

In algorithm competitions, we sometimes need to maintain multi-dimensional information. In such cases, we often use tree-on-tree structures to record information. When we need to maintain predecessor, successor, the $k$-th largest, the rank of a certain number, or insertion/deletion, we usually need to use balanced trees to meet our needs, i.e., segment tree of balanced trees.

## Process

We take **binary balanced tree** as an example to explain the implementation principle.

For the construction of tree-on-tree, we normally build the outer segment tree. For a node on the segment tree, we establish a balanced tree containing the sequence covered by that node. Specifically, we can insert sequence elements one by one; each time we pass through a segment tree node, we add that element to the balanced tree of that node.

Operation 1: Query the rank of a certain value in a certain interval: For the outer segment tree, we perform normal operations. For the balanced tree of nodes in a certain interval, we return the number of elements in the balanced tree that are less than that value. When merging intervals, we sum the counts of smaller elements. Finally, we add $+1$ to the returned value, which gives the rank of that value in that interval.

Operation 2: Query the value with rank $k$ in a certain interval: We can use a binary search strategy. Since an element may appear multiple times, its rank forms an interval, and some elements in the original sequence may not exist. Therefore, we adopt a similar approach to Operation 1: we use the count of elements less than the value as a reference for binary search, and thus obtain the solution.

Operation 3: Replace a certain number with another number: We just need to delete the number from all balanced trees containing that number, then insert another number. The outer layer still performs normal segment tree operations.

Operation 4: Query the predecessor of a certain value in a certain interval: For the outer segment tree, we perform normal operations. For the balanced tree of nodes in a certain interval, we return the predecessor of that value in that balanced tree. When merging interval results of the segment tree, we take the maximum value.

## Properties

### Space Complexity

Each element is added to $O(\log n)$ balanced trees, so the space complexity is $O((n + q)\log{n})$.

### Time Complexity

-   For operations 1, 3, and 4: we consider that we perform $O(\log{n})$ operations on the outer segment tree, and each operation performs $O(\log{n})$ operations on an inner balanced tree, so the time complexity is $O(\log^2{n})$.
-   For operation 2: an additional binary search process is involved, making it $O(\log^3{n})$.

## Classic Example

[Binary Balanced Tree](https://loj.ac/problem/106): outer segment tree, inner balanced tree.

## Implementation

The code for the balanced tree part can be found in [Splay](./splay.md) and other related entries.

Operation 1:

```cpp
int vec_rank(int k, int l, int r, int x, int y, int t) {
  if (x <= l && r <= y) {
    return spy[k].chk_rank(t);
  }
  int mid = l + r >> 1;
  int res = 0;
  if (x <= mid) res += vec_rank(k << 1, l, mid, x, y, t);
  if (y > mid) res += vec_rank(k << 1 | 1, mid + 1, r, x, y, t);
  if (x <= mid && y > mid) res--;
  return res;
}
```

Operation 2:

```cpp
int el = 0, er = 100000001, emid;
while (el != er) {
  emid = el + er >> 1;
  if (vec_rank(1, 1, n, tl, tr, emid) - 1 < tk)
    el = emid + 1;
  else
    er = emid;
}
printf("%d\n", el - 1);
```

Operation 3:

```cpp
void vec_chg(int k, int l, int r, int loc, int x) {
  int t = spy[k].find(dat[loc]);
  spy[k].dele(t);
  spy[k].insert(x);
  if (l == r) return;
  int mid = l + r >> 1;
  if (loc <= mid) vec_chg(k << 1, l, mid, loc, x);
  if (loc > mid) vec_chg(k << 1 | 1, mid + 1, r, loc, x);
}
```

Operation 4:

```cpp
int vec_front(int k, int l, int r, int x, int y, int t) {
  if (x <= l && r <= y) return spy[k].chk_front(t);
  int mid = l + r >> 1;
  int res = 0;
  if (x <= mid) res = max(res, vec_front(k << 1, l, mid, x, y, t));
  if (y > mid) res = max(res, vec_front(k << 1 | 1, mid + 1, r, x, y, t));
  return res;
}
```

## Related Algorithms

When facing problems with multi-dimensional information, if the problem does not require strict online processing, we can still consider [CDQ Divide and Conquer](../misc/cdq-divide.md), or [Overall Binary Search](../misc/parallel-binsearch.md), etc., divide-and-conquer algorithms to avoid using advanced data structures and reduce implementation difficulty.
