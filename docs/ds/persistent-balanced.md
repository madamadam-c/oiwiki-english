## Persistent FHQ Treap

### Prerequisites

The **persistent balanced tree commonly used in OI** is generally the **persistent FHQ Treap**, so it is recommended to first learn [**FHQ Treap**](./treap.md).

### Idea/Approach

For a non-rotating Treap, persistence can be achieved by copying the nodes encountered on the path during **Merge** and **Split** operations. Usually this copying is done in **Split**, ensuring that previous versions are not affected.

For a rotating Treap, besides copying the nodes encountered on the path, you also need to copy the nodes affected by rotations. If such a node has already been copied during this operation, it does not need to be copied again. Since one rotation usually affects only two nodes, this does not increase the time complexity.

The method above is generally called path copying.

"All supported operations can be completed through **Merge Split Newnode Build**." The **Build** operation is only used for construction and does not need special attention; **Newnode** creates a new node and is the tool used for persistence.

Observe **Merge** and **Split**: both are top-down operations.

Therefore, we can make them persistent by **following the persistent segment tree approach**.

### Persistent Operations

**Persistence** is an operation on a **data structure**: it preserves historical information so that earlier versions can be accessed later.

For a **persistent segment tree**, creating a new historical version means copying the **modified path**.

For a persistent Treap, the version currently commonly used in domestic OI:

After copying a node $X_{a}$, the $X$ node's $a$-th version, into a new version $X_{a+1}$, the $X$ node's $a+1$-th version:

-   If some child node $Y$ does not need its information modified, directly make the pointer of $X_{a+1}$ point to $Y_{a}$, the $Y$ node's $a$-th version.
-   Otherwise, if $Y$ must be modified, then when **recursing to the lower level**, **create** the new node $Y_{a+1}$, the $Y$ node's $a+1$-th version, to **store the new information**, and make the pointer of $X_{a+1}$ point to $Y_{a+1}$, the $Y$ node's $a+1$-th version.

### Persistence

Required components:

-   A `struct` array storing information for **each node**; it is usually called the `tree` array. Of course, if you write a **pointer-based** balanced tree, you can consider not using this array.

-   A **root array** storing the *tree root* of each version. Each query on a version starts from the node stored in this root array.

-   `split()` splits **one tree into two trees**.

-   `merge()` merges **two trees according to random priorities**.

-   `newNode()` creates a new node.

-   `build()` builds the tree.

#### Split

For the **split operation**, create new nodes along the split path and point them to the separated paths. Use `std::pair` to store the roots of the two newly split trees.

`split(x,k)` returns a `std::pair`.

It means putting, from the tree rooted at $_x$, the first $k$ elements into **one tree**, while the remaining nodes form another tree, and returning the roots of the two trees. `first` is the root of the first tree, and `second` is the root of the second.

-   If the **left subtree** of $x$ has $key \geq k$, recursively enter the left subtree, and merge the second tree split from the left subtree with the current **right subtree** of $x$.
-   Otherwise, recurse into the **right subtree**.

```cpp
static std::pair<int, int> _split(int _x, int k) {
  if (_x == 0)
    return std::make_pair(0, 0);
  else {
    int _vs = ++_cnt;  // Create a new node, the essence of persistence
    _trp[_vs] = _trp[_x];
    std::pair<int, int> _y;
    if (_trp[_vs].key <= k) {
      _y = _split(_trp[_vs].leaf[1], k);
      _trp[_vs].leaf[1] = _y.first;
      _y.first = _vs;
    } else {
      _y = _split(_trp[_vs].leaf[0], k);
      _trp[_vs].leaf[0] = _y.second;
      _y.second = _vs;
    }
    _trp[_vs]._update();
    return _y;
  }
}
```

#### Merge

`merge(x,y)` returns the root of the merged tree.

It is also implemented recursively. If **x's random priority** > **y's random priority**, call `merge(x_{rc},y)`; otherwise call `merge(x,y_{lc})`.

```cpp
static int _merge(int _x, int _y) {
  if (_x == 0 || _y == 0)
    return _x ^ _y;
  else {
    if (_trp[_x].fix < _trp[_y].fix) {
      _trp[_x].leaf[1] = _merge(_trp[_x].leaf[1], _y);
      _trp[_x]._update();
      return _x;
    } else {
      _trp[_y].leaf[0] = _merge(_x, _trp[_y].leaf[0]);
      _trp[_y]._update();
      return _y;
    }
  }
}
```

## Persistent WBLT

### Prerequisites

Persistent WBLT is modified from WBLT, so first learn [WBLT](./wblt.md).

### Idea/Approach

Use **path copying**: copy all nodes **modified** during an operation, so previous nodes are not affected.

### Handling Lazy Tags

To handle lazy tags, consider this: in a persistent WBLT, a node may have multiple parents, but it can only have $0$ or $2$ children. A `pushdown` operation only affects its children. Calling `pushdown` on a node itself has no harmful effect; the issue is with its children. A child may have more than one parent, and pushing the tag down to that child may add a lazy tag that does not belong to another parent's version, which is incorrect, unless the child has only this one parent. Therefore, during `pushdown`, we should copy the children once and apply the lazy tags to the new children.

### Implementing Path Copying

When doing path copying, define a `refresh` function that takes a reference to a node $p$, meaning: copy node $p$, produce a new node, and assign the new node back to $p$. The rule for using `refresh` is: if the node is about to be modified, or if the children it owns are about to change (not merely that information inside its children will change), then refresh it; otherwise it is unnecessary.

For static queries, no refresh is needed except for `pushdown`. If every operation is guaranteed to use path copying, then the order of `pushdown` and `refresh` does not matter.

### A Small Optimization for Persistent WBLT

Here is an optimization. We observed that `pushdown` copies two nodes. Tag permanence can be used, but as mentioned above, if a child has only this one parent, there is no need to copy it. This property can be used to reduce unnecessary node copies.

Record how many parents each node has, counting each version root as having one parent; denote this by $use$. During each `refresh`, if $use\leq 1$, there is no need to copy the node again. Otherwise, create a new node and decrement $use$ by $1$, indicating that the parent has taken this child away; then the parent may freely modify the new node without affecting other versions. In addition, each time a node is copied, if it has children, increment both children's $use$ by $1$. When two subtrees are merged, the returned node also contributes one parent's $use$ to each of its two children. When a node is deleted, both child nodes lose one parent. This can optimize time and space somewhat.

### Code Implementation

??? note "Full Code (Persistent Splay-Like Balanced Sequence Tree)"
    ```cpp
    --8<-- "docs/ds/code/persistent-balanced/persistent-wblt.cpp"
    ```

## Examples

???+ note "[Luogu P3835 [Template] Persistent Balanced Tree](https://www.luogu.com.cn/problem/P3835)"
    You need to implement a data structure supporting the following operations. Initially, the data structure is empty.
    
    1.  Insert number $x$.
    2.  Delete number $x$. If there are multiple equal numbers, delete only one; if there is none, ignore the operation.
    3.  Query the rank of number $x$. The rank is defined as the number of elements smaller than the current number plus 1.
    4.  Query the number whose rank is $x$.
    5.  Find the predecessor of $x$. The predecessor is the greatest number less than $x$; if it does not exist, output $-2\,147\,483\,647$.
    6.  Find the successor of $x$. The successor is the smallest number greater than $x$; if it does not exist, output $2\,147\,483\,647$.
    
    All operations are based on some historical version and generate a new version. Operations 3, 4, 5, and 6 keep the original version unchanged. The number of each version is the index of the operation. In particular, the initial version is numbered 0.

This is the persistent version of the **ordinary balanced tree** problem, and the operations are similar.

It just uses persistent `merge` and `split` operations.

## Recommended Practice Problems

1.  [「Luogu P3919」Persistent Array (Template)](https://www.luogu.com.cn/problem/P3919)

2.  [「Codeforces 702F」T-shirt](http://codeforces.com/problemset/problem/702/F)

3.  [「Luogu P5055」Persistent Implicit Balanced Tree](https://www.luogu.com.cn/problem/P5055)

4.  [「Luogu P5350」Sequence](https://www.luogu.com.cn/problem/P5350)
