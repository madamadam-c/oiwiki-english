author: sshwy, zhouyuyang2002, StudyingFather, Ir1d, ouuan, Enter-tainer

## Introduction

A Cartesian tree is a binary tree where each node consists of a key-value pair $(k,w)$. The key $k$ is required to satisfy the binary search tree (BST) property, while $w$ satisfies the heap property. If the keys $k,w$ of a Cartesian tree are fixed, and all $k$ values are distinct and all $w$ values are distinct, then the structure of this Cartesian tree is unique. For example:

![eg](./images/cartesian-tree1.png)

(Image source: Wikipedia)

The Cartesian tree above is equivalent to treating array values as the key $w$ and array indices as the key $k$. We can see that the key $k$ satisfies the BST property, while the key $w$ satisfies the min-heap property. At the same time, by the property of binary search trees, this special Cartesian tree has the property that the indices inside any subtree form a contiguous interval.

In competitions, Cartesian trees commonly use array indices as the key $k$ in the pair, and the array index $k$ satisfies the BST property.

Below, when using $k,w$, we assume by default that $k$ satisfies the BST property and $w$ satisfies the heap property.

## Building a Cartesian Tree with a Monotonic Stack

### Process

Consider inserting elements into the current Cartesian tree in ascending order of $k$.

For a Cartesian tree, define the "right chain" as the chain obtained by starting from the root and repeatedly taking the right child until reaching a leaf. After inserting a node, this node must lie on the right chain. Since insertion is performed in increasing order of $k$, which satisfies the BST property, the newly inserted node must be at the **rightmost end** of the tree. This node cannot be a left child and has no right child.

Therefore, we perform the following process: compare nodes on the right chain with the current node $u$ by their $w$ values from bottom to top. If we find a node $x$ on the right chain such that $w_x<w_u$, attach $u$ as the right child of $x$, and the original right subtree of $x$ becomes the left subtree of $u$.

The red-boxed part in the figure is the right chain we maintain throughout:

![build](./images/cartesian-tree2.png)

Clearly, each element enters and leaves the right chain at most once (equivalently, each point stays on the right chain for one contiguous period of time). This process can be maintained with a monotonic stack. The stack stores the nodes currently on the Cartesian tree's right chain; when a point is no longer on the right chain, pop it. Thus each point is pushed and popped at most once, giving complexity $O(n)$.

???+ note "Cartesian Tree and Treap"
    In fact, a Treap is a kind of Cartesian tree, except that the value of $w$ in a Treap is completely random. Treaps have a linear construction algorithm: if the keys $k$ are sorted in advance, the monotonic-stack algorithm above can be used to build the tree, although it is rarely used this way.

### C++ Implementation

```cpp
// stk maintains the indices in the sequence corresponding to Cartesian-tree nodes
for (int i = 1; i <= n; i++) {
  int k = top;  // top is the stack top before the operation; k is the current stack top
  while (k > 0 && w[stk[k]] > w[i]) k--;  // maintain nodes on the right chain
  if (k) rs[stk[k]] = i;  // top element.right child := current element
  if (k < top) ls[i] = stk[k + 1];  // current element.left child := last popped element
  stk[++k] = i;                     // push current element
  top = k;
}
```

## Example

???+ note "[HDU 1506. Largest Rectangle in a Histogram](https://acm.hdu.edu.cn/showproblem.php?pid=1506)"
    There are $n$ positions, and the height at each position is $h_i$. Find the largest sub-rectangle, as shown below:
    
    ![eg](./images/cartesian-tree3.png)
    
    The shaded part is the largest sub-rectangle in the figure.

??? note "Solution"
    Specifically, use the index as the key $k$ and $h_i$ as the key $w$, satisfying the min-heap property, to build a Cartesian tree over $(i,h_i)$.
    
    Then enumerate every node $u$ and use $w_u$ (that is, node $u$'s height $h$) as the height of the largest sub-rectangle. Since the Cartesian tree we build satisfies the min-heap property, every node in $u$'s subtree has height at least $u$'s height. Also, the indices inside $u$'s subtree form a contiguous interval. Therefore, we only need to know the size of the subtree to compute the area of the largest sub-rectangle for this interval. Use the value computed for every point to update the answer. Clearly, this can be completed with one DFS, so the complexity is $O(n)$.

??? note "Reference Implementation"
    ```cpp
    --8<-- "docs/ds/code/cartesian-tree/cartesian-tree_1.cpp"
    ```

## References

[Cartesian tree - Wikipedia](https://en.wikipedia.org/wiki/Cartesian_tree)
