author: JiZiQian, llleixx, firefly-zjyjoe

## What Is a Leftist Tree?

A **leftist tree**, like a [**pairing heap**](./pairing-heap.md), is a **mergeable heap**. It has the heap property and supports fast merging.

## Definition and Properties of Leftist Trees

For a binary tree, define an **external node** as a node with fewer than two children. Define a node's $\mathrm{dist}$ as the number of edges on the path from it to the nearest external node in its subtree. The $\mathrm{dist}$ of an empty node is $0$.

???+ note "Note"
    Some references define $\mathrm{dist}$ as the $\mathrm{dist}$ value here minus $1$. This definition can omit some null checks in code, but the $\mathrm{dist}$ of empty nodes must be initialized to $-1$. All code in this article uses the $\mathrm{dist}$ definition where **empty nodes have $\mathrm{dist}$ as $-1$**, so note the difference from the prose $\mathrm{dist}$ definition.

A leftist tree is a binary tree that not only has the heap property but is also "leftist": for every node, the $\mathrm{dist}$ of its left child is at least the $\mathrm{dist}$ of its right child.

Therefore, in a leftist tree, each node's $\mathrm{dist}$ equals its right child's $\mathrm{dist}$ plus one.

Note that $\mathrm{dist}$ is not depth. **A leftist tree has no depth guarantee**; a chain extending to the left also satisfies the definition of a leftist tree.

## Core Operation: Merge

When merging two heaps, to satisfy the heap property, first take the root with the smaller value (for convenience, this article discusses min-heaps) as the root of the merged heap. Then keep this root's left child as the left child of the merged heap, and recursively merge its right child with the other heap to become the right child of the merged heap. To satisfy the leftist property, after merging, if the left child's $\mathrm{dist}$ is less than the right child's $\mathrm{dist}$, swap the two children.

Reference code:

???+ note "Implementation"
    ```cpp
    int merge(int x, int y) {
      if (!x || !y) return x | y;  // If one heap is empty, return the other.
      if (t[x].val > t[y].val) swap(x, y);  // Use the smaller value as the root.
      t[x].rs = merge(t[x].rs, y);          // Recursively merge the right child with the other heap.
      if (t[t[x].rs].d > t[t[x].ls].d)
        swap(t[x].ls, t[x].rs);   // Swap children if the leftist property is violated.
      t[x].d = t[t[x].rs].d + 1;  // Update dist.
      return x;
    }
    ```

Due to the leftist property, each recursive level decreases the $\mathrm{dist}$ of one heap root by $1$. For a binary tree with $n$ nodes, the root's $\mathrm{dist}$ is at most $\left\lceil\log (n+1)\right\rceil$, so merging heaps of sizes $n$ and $m$ takes $O(\log n+\log m)$ time.

???+ note "Proof of the $\mathrm{dist}$ Property"
    A binary tree whose root has $\mathrm{dist}$ as $x$ has at least $x-1$ full levels, so it has at least $2^x-1$ nodes. Note that this property holds for all binary trees; it is not unique to leftist trees.

There is also a way to write a leftist tree without explicitly swapping children: treat the child with larger $\mathrm{dist}$ as the left child, and the child with smaller $\mathrm{dist}$ as the right child:

???+ note "Implementation"
    ```cpp
    int& rs(int x) { return t[x].ch[t[t[x].ch[1]].d < t[t[x].ch[0]].d]; }
    
    int merge(int x, int y) {
      if (!x || !y) return x | y;
      if (t[x].val < t[y].val) swap(x, y);
      int& rs_ref = rs(x);
      rs_ref = merge(rs_ref, y);
      t[x].d = t[rs(x)].d + 1;
      return x;
    }
    ```

## Other Operations on Leftist Trees

### Insert a Node

A single node can also be regarded as a heap, so just merge it.

### Delete the Root

Just merge the root's left and right children.

### Delete an Arbitrary Node

#### Method

First merge the left and right children, then update $\mathrm{dist}$ from bottom to top, swapping left and right children whenever the leftist property is violated. End the recursion when $\mathrm{dist}$ no longer needs to be updated:

???+ note "Implementation"
    ```cpp
    int& rs(int x) { return t[x].ch[t[t[x].ch[1]].d < t[t[x].ch[0]].d]; }
    
    // With pushup, merging the left and right children deletes the node while preserving the leftist property.
    int merge(int x, int y) {
      if (!x || !y) return x | y;
      if (t[x].val < t[y].val) swap(x, y);
      int& rs_ref = rs(x);
      rs_ref = merge(rs_ref, y);
      t[rs_ref].fa = x;
      t[x].d = t[rs(x)].d + 1;
      return x;
    }
    
    void pushup(int x) {
      if (!x) return;
      if (t[x].d != t[rs(x)].d + 1) {
        t[x].d = t[rs(x)].d + 1;
        pushup(t[x].fa);
      }
    }
    
    void erase(int x) {
      int y = merge(t[x].ch[0], t[x].ch[1]);
      t[y].fa = t[x].fa;
      if (t[t[x].fa].ch[0] == x)
        t[t[x].fa].ch[0] = y;
      else if (t[t[x].fa].ch[1] == x)
        t[t[x].fa].ch[1] = y;
      pushup(t[y].fa);
    }
    ```

#### Complexity Proof

First consider the `merge` process. Each step moves either $x$ or $y$ down one level. In the most extreme case, it always follows the right node of a leftist tree (the node with the smallest $\mathrm{dist}$), so $\mathrm{dist}$ decreases by $1$ each time.

Now consider the `pushup` process. Let the current node being processed by `pushup` be $x$, and its parent be $y$. Define a node's "initial $\mathrm{dist}$" as its $\mathrm{dist}$ before `pushup`. Starting the recursion from the parent of the deleted node, there are two cases:

1.  $x$ is the right child of $y$. Then $y$'s initial $\mathrm{dist}$ is $x$'s initial $\mathrm{dist}$ plus one.
2.  $x$ is the left child of $y$. Since a node's $\mathrm{dist}$ decreases by at most one, recursion continues only when $y$'s left and right children have equal initial $\mathrm{dist}$ values (then the left child's $\mathrm{dist}$ decreasing by one causes the two children to be swapped). Thus $y$'s initial $\mathrm{dist}$ is still $x$'s initial $\mathrm{dist}$ plus one.

Therefore, for $x$, the initial $\mathrm{dist}$ increases by one at each recursive level, so there are at most $O(\log n)$ recursive levels.

### Add/Subtract a Value to the Whole Heap, or Multiply by a Positive Number

In fact, any operation that can be lazily tagged and does not change the relative order of keys is possible.

Put the lazy tag on the root, and push it down when deleting the root or merging heaps (that is, when accessing children):

???+ note "Implementation"
    ```cpp
    int merge(int x, int y) {
      if (!x || !y) return x | y;
      if (t[x].val > t[y].val) swap(x, y);
      pushdown(x);
      t[x].rs = merge(t[x].rs, y);
      if (t[t[x].rs].d > t[t[x].ls].d) swap(t[x].ls, t[x].rs);
      t[x].d = t[t[x].rs].d + 1;
      return x;
    }
    
    int pop(int x) {
      pushdown(x);
      return merge(t[x].ls, t[x].rs);
    }
    ```

## Other Mergeable Heaps

### Randomized Heap

???+ note "Implementation"
    ```cpp
    int merge(int x, int y) {
      if (!x || !y) return x | y;
      if (t[y].val < t[x].val) swap(x, y);
      if (rand() & 1)  // Randomly decide whether to swap the left and right children.
        swap(t[x].ls, t[x].rs);
      t[x].ls = merge(t[x].ls, y);
      return x;
    }
    ```

The only difference in this implementation is that it uses randomness during merging, which avoids the computations related to $\mathrm{dist}$. Its average time complexity is also $O(\log n)$. For a detailed proof, see [Randomized Heap](https://cp-algorithms.com/data_structures/randomized_heap.html).

### Skew Heap

A skew heap is a self-adjusting form of a leftist tree. When merging two heaps, it unconditionally swaps all nodes on the merge path in an attempt to maintain balance. By amortized analysis, insertion, merging, and deleting the minimum in a top-down skew heap all take $O(\log n)$ time[^ref1].

## Practice Problems

### Template Problems

[Luogu P3377 [Template] Leftist Tree (Mergeable Heap)](https://www.luogu.com.cn/problem/P3377)

[Monkey King](https://www.luogu.com.cn/problem/P1456)

[Roman Game](https://www.luogu.com.cn/problem/P2713)

Things to note:

1.  Before merging, check whether the two nodes are already in the same heap.

2.  The depth of a leftist tree may reach $O(n)$, so use a DSU to maintain the heap root containing a node; do not simply climb parent pointers by brute force. (Although many problems have weak data and brute-force parent climbing may pass.) When using a DSU to maintain roots, ensure that the old root points to the new root and the new root points to itself.

??? note "Reference Code for Roman Game"
    ```cpp
    --8<-- "docs/ds/code/leftist-tree/leftist-tree_1.cpp"
    ```

### Tree Problems

[APIO2012 Dispatching](https://www.luogu.com.cn/problem/P1552)

[JLOI2015 City Capture](https://loj.ac/problem/2107)

In these problems, each node often maintains a heap, merges it with its children, and performs pops, modifications, and answer computations according to the statement. This is somewhat similar to problems involving segment tree merging.

??? note "Reference Code for City Capture"
    ```cpp
    --8<-- "docs/ds/code/leftist-tree/leftist-tree_2.cpp"
    ```

### [SCOI2011 Tricky Operation](https://loj.ac/problem/2441)

First, use a DSU to find the heap root containing a node; do not climb upward by brute force.

For point queries, if lazy tags are applied in the ordinary way, you would need to query the sum of tags along the path from the node to the root, which can be $O(n)$ in the worst case. If only heap roots have tags, queries become fast, but how can we achieve that?

Use an idea similar to small-to-large merging. Each time heaps are merged, push the tag of the smaller heap down to every node in it by brute force, and use the tag of the larger heap as the tag of the merged heap. Since the merged heap also has the other heap's tag, when pushing down the smaller heap's tag, push down its tag minus the other heap's tag. Because every time a node's heap is merged, the heap size containing it at least doubles, each node has tags pushed down at most $O(\log n)$ times, so the total complexity of brute-force tag pushing is $O(n\log n)$.

For point add, delete the node first, then update it, and finally insert it back.

For the global maximum, maintain the root of each heap using a balanced tree, a heap supporting arbitrary deletion (such as a leftist tree), or a `multiset`.

Thus the operations are as follows:

1.  Brute-force push down the tag of the heap with fewer nodes, merge the two heaps, update `size` and `tag`, and remove from the `multiset` the old heap root that is no longer a root after merging.
2.  Delete the node, update its value, insert it back, and update the `multiset`. You need to distinguish whether the deleted node is the root.
3.  Apply a tag to the heap root and update the `multiset`.
4.  Apply a global tag.
5.  Query value + heap-root tag + global tag.
6.  Query root value + heap-root tag + global tag.
7.  Query maximum value in the `multiset` + global tag.

??? note "Reference Code for Tricky Operation"
    ```cpp
    --8<-- "docs/ds/code/leftist-tree/leftist-tree_3.cpp"
    ```

### [BOI2004 Sequence](https://www.luogu.com.cn/problem/P4331)

This is a paper-based problem. See [Huang Yuanhe -- Characteristics and Applications of Leftist Trees](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2005%E8%AE%BA%E6%96%87%E9%9B%86/%E9%BB%84%E6%BA%90%E6%B2%B3--%E5%B7%A6%E5%81%8F%E6%A0%91%E7%9A%84%E7%89%B9%E7%82%B9%E5%8F%8A%E5%85%B6%E5%BA%94%E7%94%A8/%E9%BB%84%E6%BA%90%E6%B2%B3.pdf) for details.

## References

[^ref1]: [Self-Adjusting Heaps](https://epubs.siam.org/doi/10.1137/0215004)
