## Introduction

Given a sequence ${\left\langle a_i\right\rangle}_{i=1}^n$ of length n and an associative operation $\circ$ (for example, $\gcd,\min,\max,+,\operatorname{and},\operatorname{or},\operatorname{xor}$ are all associative), each range query $[l,r]$ asks us to compute $a_l\circ a_{l+1}\circ\dotsb\circ a_{r}$.

A Sqrt Tree can be preprocessed in $O(n\log\log n)$ time and answer queries in $O(1)$ time.

## Explanation

### Blocking The Sequence

First split the whole sequence into $O(\sqrt{n})$ blocks, each of size $O(\sqrt{n})$. For each block, compute:

1.  Prefix range answers $P_i$ inside the block.
2.  Suffix range answers $S_i$ inside the block.
3.  An additional array $\left\langle B_{i,j}\right\rangle$ denoting the range answer from block $i$ to block $j$.

For example, suppose $\circ$ is addition $+$ and the sequence is $\{1,2,3,4,5,6,7,8,9\}$.

First split the sequence into three blocks: $\{1,2,3\},\{4,5,6\},\{7,8,9\}$.

The prefix and suffix range answers of each block are

$$
\begin{aligned}
&P_1=\{1,3,6\},S_1=\{6,5,3\}\\
&P_2=\{4,9,15\},S_2=\{15,11,6\}\\
&P_3=\{7,15,24\},S_3=\{24,17,9\}\\
\end{aligned}
$$

The $B$ array is:

$$
B=\begin{bmatrix}
6 & 21 & 45\\
0 & 15 & 39\\
0 & 0 & 24\\
\end{bmatrix}
$$

(For invalid cases with $i>j$, assume the answer is 0.)

Clearly these values can be preprocessed in $O(n)$ time, and the space complexity is also $O(n)$. After preprocessing, they answer cross-block queries in $O(1)$ time. Queries whose whole interval lies in one block still cannot be handled, so more structure is needed.

### Building A Tree

A natural idea is to recursively build the same structure inside every block to support in-block queries. For a block of size $1$, queries can be answered in $O(1)$ time. This builds a tree where each node represents an interval of the sequence. Leaf intervals have length $1$ or $2$. A node of size $k$ has $O(\sqrt{k})$ children, so the whole tree has height $O(\log\log n)$, and the total interval length on each level is $O(n)$. Thus the construction complexity is $O(n\log\log n)$.

??? note "Proof Of The Tree Height"
    By definition, for $n$ elements, let $T(n)$ be the height of the subtree that controls them. Then
    
    $$
    T(n)=T(\sqrt n)+1
    $$
    
    Substitute $n=2^m$:
    
    $$
    T(2^m)=T(2^{\frac m2})+1
    $$
    
    Define $S(m)=T(2^m)$. Then
    
    $$
    S(m)=S(\dfrac m2)+1
    $$
    
    By the master theorem, $S(m)=O(\log m)$, so $T(n)=S(\log n)=O(\log\log n)$.

Now queries can be answered in $O(\log\log n)$ time. For a query $[l,r]$, find the minimum-length node $u$ such that $u$ contains $[l,r]$. Then $[l,r]$ must cross blocks in $u$'s block decomposition, so the answer can be computed in $O(1)$ time. The total query complexity is $O(\log\log n)$ because the tree height is $O(\log\log n)$. This process can still be optimized.

### Optimizing Query Complexity

One can binary search the height and test validity in $O(1)$, reducing the complexity to $O(\log\log\log n)$. We can make it faster.

Assume that:

1.  The size of every block is a power of $2$.
2.  Block sizes are identical on the same level.

To achieve this, append some $0$ elements to the end of the sequence so that its length becomes a power of $2$. Although some blocks may become twice as large as before, their size is still $O(\sqrt{k})$, so preprocessing a decomposition is still $O(n)$.

Now it is easy to determine whether a query interval is fully contained in one block. For interval $[l,r]$ (0-indexed), write the endpoints in binary. For example, for $k=4, l=39, r=46$:

$$
l = 39_{10} = 100111_2,
r = 46_{10} = 101110_2
$$

On each level the interval length is fixed, and block sizes are also fixed (in this example $2^k=2^4=16$). These blocks fully cover the sequence, so the first block represents $[0,15]$ (binary $[000000_2,001111_2]$), the second block represents $[16,31]$ (binary $[010000_2,011111_2]$), and so on. Positions of elements in the same block differ only in the last $k$ bits (in this example $k=4$). The example's $l,r$ also differ only in the last $k$ bits, so they are in the same block.

Therefore we only need to check whether the two endpoints differ only in the last $k$ bits, i.e. $l\oplus r\le 2^k-1$. We can quickly find the level containing the answer interval:

1.  For every $i\in [1,n]$, find $i$'s highest $1$ bit.
2.  For a query $[l,r]$, compute the highest set bit of $l\oplus r$ to determine the level.

This lets us answer queries in $O(1)$ time.

## Updating Elements

Sqrt Tree supports updates. Both point updates and range updates can be supported.

### Point Updates

Consider a point assignment $a_x=val$. We want to update the maintained information efficiently.

#### Naive Implementation

First consider what changes after one point update. For a node of length $l$ and its corresponding sequences $\left\langle P_i\right\rangle,\left\langle S_i\right\rangle,\left\langle B_{i,j}\right\rangle$, in $\left\langle P_i\right\rangle$ and $\left\langle S_i \right\rangle$ only $O(\sqrt{l})$ elements change, but in $\left\langle B_{i,j}\right\rangle$ $O(l)$ elements change. Thus $O(l)$ elements are updated at this tree node. The point-update complexity on a Sqrt Tree is therefore $O(n+\sqrt{n}+\sqrt{\sqrt{n}}+\dotsb)=O(n)$.

#### Replacing The B Array With A Sqrt Tree

The bottleneck is updating the root's $\left\langle B_{i,j}\right\rangle$. Replace the root's $\left\langle B_{i,j}\right\rangle$ by another Sqrt Tree called $index$. It has the same role as the original two-dimensional array: maintaining answers for whole-block ranges. Other non-root nodes still use $\left\langle B_{i,j}\right\rangle$. If the root of a Sqrt Tree has an $index$ structure, call it **indexed**; if the root has a $\left\langle B_{i,j}\right\rangle$ structure, call it **unindexed**. The $index$ tree itself is unindexed.

Update the $index$ tree as follows:

1.  In $O(\sqrt{n})$ time, update $\left\langle P_i\right\rangle$ and $\left\langle S_i\right\rangle$.
2.  Update $index$. Its length is $O(n)$, but only one element, representing the changed block, must be updated. This step costs $O(\sqrt{n})$ with the naive algorithm.
3.  Enter the changed child and update its information with the naive algorithm in $O(\sqrt{n})$ time.

Query complexity remains $O(1)$ because the $index$ tree is used at most once. Thus point-update complexity becomes $O(\sqrt{n})$.

### Updating A Range

Sqrt Tree also supports range assignment $\operatorname{Update}(l,r,x)$, which changes all numbers in $[l,r]$ to $x$. There are two implementations: one updates information in $O(\sqrt{n}\log\log n)$ and queries in $O(1)$; the other updates in $O(\sqrt{n})$ but increases query time to $O(\log\log n)$.

We can put lazy tags on a Sqrt Tree like on a segment tree. The difference is that pushing a node's lazy tag down can cost $O(\sqrt{n})$, so instead of pushing tags during queries, we check whether a parent has a tag and push it then.

#### First Implementation

In the first implementation, only level-$1$ nodes (whose interval length is $O(\sqrt{n})$) receive lazy tags. When a tag is pushed down, the whole subtree is updated directly in $O(\sqrt{n}\log\log n)$. The process is:

1.  For level-$1$ nodes fully covered by the modified interval, add a lazy tag.

2.  At most two blocks are only partially covered. Rebuild these two blocks in $O(\sqrt{n}\log\log n)$ time. If a block already has a lazy tag, push it down while rebuilding.

3.  Update the root's $\left\langle P_i\right\rangle$ and $\left\langle S_i\right\rangle$ in $O(\sqrt{n})$ time.

4.  Rebuild the $index$ tree in $O(\sqrt{n}\log\log n)$ time.

To answer queries with lazy tags:

1.  If the query is contained in a block with a lazy tag, compute the answer from the tag.

2.  If the query spans multiple blocks, only the leftmost and rightmost incomplete blocks need special handling. Middle blocks are queried from the $index$ tree, because the $index$ tree is rebuilt after every update, in $O(1)$ time.

Thus query complexity remains $O(1)$.

#### Second Implementation

In this implementation, every node may receive a lazy tag. When answering a query, we must consider lazy tags on ancestors, so query complexity becomes $O(\log\log n)$. Updates are faster:

1.  Add lazy tags to blocks fully covered by the modified interval in $O(\sqrt{n})$ time.
2.  For partially covered blocks, update $\left\langle P_i\right\rangle$ and $\left\langle S_i\right\rangle$ in $O(\sqrt{n})$ time, since there are only two such blocks.
3.  Update the $index$ tree in $O(\sqrt{n})$ time using the same update algorithm.
4.  For unindexed subtrees, update their $\left\langle B_{i,j}\right\rangle$.
5.  Recursively update the two intervals that are not fully covered.

The time complexity is $O(\sqrt{n}+\sqrt{\sqrt{n}}+\dotsb)=O(\sqrt{n})$.

## Implementation

The following implementation builds the tree in $O(n\log\log n)$ time, answers queries in $O(1)$ time, and supports point updates in $O(\sqrt{n})$ time.

```cpp
SqrtTreeItem op(const SqrtTreeItem &a, const SqrtTreeItem &b);

int log2Up(int n) {
  int res = 0;
  while ((1 << res) < n) {
    res++;
  }
  return res;
}

class SqrtTree {
 private:
  int n, lg, indexSz;
  vector<SqrtTreeItem> v;
  vector<int> clz, layers, onLayer;
  vector<vector<SqrtTreeItem>> pref, suf, between;

  void buildBlock(int layer, int l, int r) {
    pref[layer][l] = v[l];
    for (int i = l + 1; i < r; i++) {
      pref[layer][i] = op(pref[layer][i - 1], v[i]);
    }
    suf[layer][r - 1] = v[r - 1];
    for (int i = r - 2; i >= l; i--) {
      suf[layer][i] = op(v[i], suf[layer][i + 1]);
    }
  }

  void buildBetween(int layer, int lBound, int rBound, int betweenOffs) {
    int bSzLog = (layers[layer] + 1) >> 1;
    int bCntLog = layers[layer] >> 1;
    int bSz = 1 << bSzLog;
    int bCnt = (rBound - lBound + bSz - 1) >> bSzLog;
    for (int i = 0; i < bCnt; i++) {
      SqrtTreeItem ans;
      for (int j = i; j < bCnt; j++) {
        SqrtTreeItem add = suf[layer][lBound + (j << bSzLog)];
        ans = (i == j) ? add : op(ans, add);
        between[layer - 1][betweenOffs + lBound + (i << bCntLog) + j] = ans;
      }
    }
  }

  void buildBetweenZero() {
    int bSzLog = (lg + 1) >> 1;
    for (int i = 0; i < indexSz; i++) {
      v[n + i] = suf[0][i << bSzLog];
    }
    build(1, n, n + indexSz, (1 << lg) - n);
  }

  void updateBetweenZero(int bid) {
    int bSzLog = (lg + 1) >> 1;
    v[n + bid] = suf[0][bid << bSzLog];
    update(1, n, n + indexSz, (1 << lg) - n, n + bid);
  }

  void build(int layer, int lBound, int rBound, int betweenOffs) {
    if (layer >= (int)layers.size()) {
      return;
    }
    int bSz = 1 << ((layers[layer] + 1) >> 1);
    for (int l = lBound; l < rBound; l += bSz) {
      int r = min(l + bSz, rBound);
      buildBlock(layer, l, r);
      build(layer + 1, l, r, betweenOffs);
    }
    if (layer == 0) {
      buildBetweenZero();
    } else {
      buildBetween(layer, lBound, rBound, betweenOffs);
    }
  }

  void update(int layer, int lBound, int rBound, int betweenOffs, int x) {
    if (layer >= (int)layers.size()) {
      return;
    }
    int bSzLog = (layers[layer] + 1) >> 1;
    int bSz = 1 << bSzLog;
    int blockIdx = (x - lBound) >> bSzLog;
    int l = lBound + (blockIdx << bSzLog);
    int r = min(l + bSz, rBound);
    buildBlock(layer, l, r);
    if (layer == 0) {
      updateBetweenZero(blockIdx);
    } else {
      buildBetween(layer, lBound, rBound, betweenOffs);
    }
    update(layer + 1, l, r, betweenOffs, x);
  }

  SqrtTreeItem query(int l, int r, int betweenOffs, int base) {
    if (l == r) {
      return v[l];
    }
    if (l + 1 == r) {
      return op(v[l], v[r]);
    }
    int layer = onLayer[clz[(l - base) ^ (r - base)]];
    int bSzLog = (layers[layer] + 1) >> 1;
    int bCntLog = layers[layer] >> 1;
    int lBound = (((l - base) >> layers[layer]) << layers[layer]) + base;
    int lBlock = ((l - lBound) >> bSzLog) + 1;
    int rBlock = ((r - lBound) >> bSzLog) - 1;
    SqrtTreeItem ans = suf[layer][l];
    if (lBlock <= rBlock) {
      SqrtTreeItem add =
          (layer == 0) ? (query(n + lBlock, n + rBlock, (1 << lg) - n, n))
                       : (between[layer - 1][betweenOffs + lBound +
                                             (lBlock << bCntLog) + rBlock]);
      ans = op(ans, add);
    }
    ans = op(ans, pref[layer][r]);
    return ans;
  }

 public:
  SqrtTreeItem query(int l, int r) { return query(l, r, 0, 0); }

  void update(int x, const SqrtTreeItem &item) {
    v[x] = item;
    update(0, 0, n, 0, x);
  }

  SqrtTree(const vector<SqrtTreeItem> &a)
      : n((int)a.size()), lg(log2Up(n)), v(a), clz(1 << lg), onLayer(lg + 1) {
    clz[0] = 0;
    for (int i = 1; i < (int)clz.size(); i++) {
      clz[i] = clz[i >> 1] + 1;
    }
    int tlg = lg;
    while (tlg > 1) {
      onLayer[tlg] = (int)layers.size();
      layers.push_back(tlg);
      tlg = (tlg + 1) >> 1;
    }
    for (int i = lg - 1; i >= 0; i--) {
      onLayer[i] = max(onLayer[i], onLayer[i + 1]);
    }
    int betweenLayers = max(0, (int)layers.size() - 1);
    int bSzLog = (lg + 1) >> 1;
    int bSz = 1 << bSzLog;
    indexSz = (n + bSz - 1) >> bSzLog;
    v.resize(n + indexSz);
    pref.assign(layers.size(), vector<SqrtTreeItem>(n + indexSz));
    suf.assign(layers.size(), vector<SqrtTreeItem>(n + indexSz));
    between.assign(betweenLayers, vector<SqrtTreeItem>((1 << lg) + bSz));
    build(0, 0, n, 0);
  }
};
```

## Exercises

[CodeChef - SEGPROD](https://www.codechef.com/NOV17/problems/SEGPROD)

**This page is mainly translated from [Sqrt Tree - Algorithms for Competitive Programming](https://cp-algorithms.com/data_structures/sqrt-tree.html), licensed under CC-BY-SA 4.0.**
