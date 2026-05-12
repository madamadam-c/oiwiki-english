## Chairman Tree

The full name of a Chairman Tree is persistent value segment tree. See this [Zhihu discussion](https://www.zhihu.com/question/59195374).

???+ warning "About Functional Segment Trees"
    A **functional segment tree** is a segment tree using functional-programming ideas. In functional programming, computation is viewed as mathematical functions, and mutable state or variables are avoided. It is easy to see that a functional segment tree is [fully persistent](persistent.md#fully-persistent).

## Introduction

First, introduce a problem: given $n$ integers forming a sequence $a$, query, for a specified closed interval $[l, r]$, its $k$-th smallest value.

How should this be solved?

One feasible solution is to use a Chairman Tree.
The main idea of a Chairman Tree is to save the historical version of every insertion operation so that the $k$-th smallest value in an interval can be queried.

How do we save it? A simple brute-force idea is to create a segment tree every time.
But would that not explode memory usage?

## Explanation

After analysis, we find that every modification changes the same number of nodes.
(For example, in the figure below, the node corresponding to value 1 in $[1,8]$ is modified; red nodes are changed nodes.)
![](./images/persistent-seg.png)

Only $O(\log{n})$ nodes are changed, forming a chain. In other words, the number of changed nodes each time equals the height of the tree.
Note that a Chairman Tree cannot use heap-style storage: we cannot use $x\times 2$ and $x\times 2+1$ to represent the left and right children. Instead, nodes should be allocated dynamically, and each node's left and right child indices should be saved.
Therefore, on top of recording left and right children, we only need to save the root node when each number is inserted to achieve persistence.

Simplify the problem: each time, find in interval $[1,r]$ the $k$-th smallest value.
How do we do this? Simply find the root-node version after inserting r, then use an ordinary value segment tree (also called a key segment tree or value-domain segment tree).

This should be understandable. Returning to the original problem: find in interval $[l,r]$ the $k$-th smallest value.
Here we connect to another concept: **prefix sums**.
This little trick cleverly uses interval subtraction, preprocessing information to answer each query in $O(1)$.

We can observe that the information counted by the Chairman Tree also satisfies this property.
Therefore, to obtain the statistics of $[l,r]$, just use the information of $[1,r]$ minus the information of $[1,l - 1]$.

At this point, the problem is solved!

For space, analyze as follows: because nodes are allocated dynamically, one segment tree only contains $2n-1$ nodes.
Then there are $n$ modifications, and each modification adds at most $\lceil\log_2{n}\rceil+1$ nodes. Therefore, in the worst case, the total number of nodes after $n$ modifications reaches $2n-1+n(\lceil\log_2{n}\rceil+1)$.
For this problem, $n \leq 10^5$, and a single modification adds at most $\lceil\log_2{10^5}\rceil+1 = 18$ nodes. Thus the total node count after $n$ modifications is $2\times 10^5-1+18\times 10^5$; ignoring $-1$, it is about $20\times 10^5$.

One final piece of advice: do not be stingy with space (most problems have relatively generous memory limits, so there is usually no need to worry about memory limit exceeded)! Be bold and directly allocate $2^5\times 10^5$, close to twice the original space (i.e. `n << 5`).

## Implementation

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
constexpr int MAXN = 1e5;  // data range
int tot, n, m;
int sum[(MAXN << 5) + 10], rt[MAXN + 10], ls[(MAXN << 5) + 10],
    rs[(MAXN << 5) + 10];
int a[MAXN + 10], ind[MAXN + 10], len;

int getid(const int &val) {  // discretization
  return lower_bound(ind + 1, ind + len + 1, val) - ind;
}

int build(int l, int r) {  // build tree
  int root = ++tot;
  if (l == r) return root;
  int mid = l + r >> 1;
  ls[root] = build(l, mid);
  rs[root] = build(mid + 1, r);
  return root;  // return the root node of this subtree
}

int update(int k, int l, int r, int root) {  // insertion operation
  int dir = ++tot;
  ls[dir] = ls[root], rs[dir] = rs[root], sum[dir] = sum[root] + 1;
  if (l == r) return dir;
  int mid = l + r >> 1;
  if (k <= mid)
    ls[dir] = update(k, l, mid, ls[dir]);
  else
    rs[dir] = update(k, mid + 1, r, rs[dir]);
  return dir;
}

int query(int u, int v, int l, int r, int k) {  // query operation
  int mid = l + r >> 1,
      x = sum[ls[v]] - sum[ls[u]];  // interval subtraction gives the count stored in the left child
  if (l == r) return l;
  if (k <= x)  // if k <= x, the k-th smallest number is stored in the left child
    return query(ls[u], ls[v], l, mid, k);
  else  // otherwise it is in the right child
    return query(rs[u], rs[v], mid + 1, r, k - x);
}

void init() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%d", a + i);
  memcpy(ind, a, sizeof ind);
  sort(ind + 1, ind + n + 1);
  len = unique(ind + 1, ind + n + 1) - ind - 1;
  rt[0] = build(1, len);
  for (int i = 1; i <= n; ++i) rt[i] = update(getid(a[i]), 1, len, rt[i - 1]);
}

int l, r, k;

void work() {
  while (m--) {
    scanf("%d%d%d", &l, &r, &k);
    printf("%d\n", ind[query(rt[l - 1], rt[r], 1, len, k)]);  // answer query
  }
}

int main() {
  init();
  work();
  return 0;
}
```

## Extension: Persistent DSU Based on Chairman Tree

Chairman Tree is a convenient way to implement a persistent DSU, so an example implementation of a persistent DSU based on Chairman Tree is also provided here.

```cpp
--8<-- "docs/ds/code/persistent-seg/persistent-seg_1.cpp"
```

## References

<https://en.wikipedia.org/wiki/Persistent_data_structure>

<https://www.cnblogs.com/zinthos/p/3899565.html>
