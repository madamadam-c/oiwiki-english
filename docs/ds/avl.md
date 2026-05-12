AVL tree is a balanced binary search tree. Due to lengthy introductions of AVL in many algorithm textbooks, many people have the impression that AVL trees are complex and impractical. However, the principle of AVL trees is simple, and implementation is not complicated either.

## Properties

1.  An empty binary tree is an AVL tree
2.  If T is an AVL tree, then its left and right subtrees are also AVL trees, and $|h(ls) - h(rs)| \leq 1$, where h is the height of its left and right subtrees
3.  Tree height is $O(\log n)$

Balance factor: right subtree height - left subtree height

???+ note "Proof of tree height"
    Let $f_n$ be the minimum number of nodes in an AVL tree of height $n$, then
    
    $$
    f_n=
    \begin{cases}
    1&(n=1)\\
    2&(n=2)\\
    f_{n-1}+f_{n-2}+1& (n>2)
    \end{cases}
    $$
    
    According to the solution of constant-coefficient non-homogeneous linear difference equations, $\{f_n+1\}$ is a Fibonacci sequence. Here the general term of $f_n$ is:
    
    $$
    f_n=\frac{5+2\sqrt{5}}{5}\left(\frac{1+\sqrt{5}}{2}\right)^n+\frac{5-2\sqrt{5}}{5}\left(\frac{1-\sqrt{5}}{2}\right)^n-1
    $$
    
    Since the Fibonacci sequence grows exponentially, for tree height $n$ we have:
    
    $$
    n<\log_{\frac{1+\sqrt{5}}{2}} (f_n+1)<\frac{3}{2}\log_2 (f_n+1)
    $$
    
    Therefore, the height of an AVL tree is $O(\log f_n)$, where $f_n$ is the number of nodes.

## Process

### Insert Node

Similar to BST (binary search tree), first perform an unsuccessful search to determine the insertion position, insert the node, then decide whether adjustment is needed based on the balance factor.

### Delete Node

Deletion is similar to BST: swap the node with its successor, then delete.

Deletion causes tree height and balance factor to change, so we need to adjust along the path from the deleted node to the root.

### Maintaining Balance

After inserting or deleting a node, property 2 of AVL trees may be violated. Therefore, we need to maintain the tree along the path from the inserted/deleted node to the root. If for a certain node, property 2 is no longer satisfied, since we only inserted/deleted one node, the effect on tree height is at most 1, so the absolute value of this node's balance factor is at most 2. Due to symmetry, we only discuss the case where the left subtree's height exceeds the right subtree's height by 2, i.e., in the figure below $h(B)-h(E)=2$. At this point, we still need to discuss two cases based on the size relationship between $h(A)$ and $h(C)$. Note that since we maintain balance bottom-up, for all descendants of node D, property 2 remains satisfied.

![](./images/avl1.svg)

#### Case 1: A's tree height is not less than C's tree height

Let $h(E)=x$, then we have

$$
\begin{cases}
    h(B)=x+2\\
    h(A)=x+1\\
    x\leq h(C)\leq x+1
\end{cases}
$$

where $h(C)\geq x$ is due to node B satisfying property 2, so the difference between $h(C)$ and $h(A)$ will not exceed 1. At this point, we perform a right rotation on node D (rotation operation is the same as in other types of balanced binary search trees), as shown below.

![](./images/avl2.svg)

Clearly, the heights of nodes A, C, and E remain unchanged, and we have

$$
\begin{cases}
    0\leq h(C)-h(E)\leq 1\\
    x+1\leq h'(D)=\max(h(C),h(E))+1=h(C)+1\leq x+2\\
    0\leq h'(D)-h(A)\leq 1
\end{cases}
$$

Therefore, the rotated nodes B and D also satisfy property 2.

#### Case 2: A's tree height is less than C's tree height

Let $h(E)=x$, then similarly we have

$$
\begin{cases}
    h(B)=x+2\\
    h(C)=x+1\\
    h(A)=x
\end{cases}
$$

In this case, we first perform a left rotation on node B, then a right rotation on node D, as shown below.

![](./images/avl3.svg)

Clearly, the heights of nodes A and E remain unchanged, and B's new right son and D's new left son are C's original left and right sons, respectively, so we have

$$
\begin{cases}
    x-1\leq h'(rs_B),h'(ls_D)\leq x\\
    0\leq h(A)-h'(rs_B)\leq 1\\
    0\leq h(E)-h'(ls_D)\leq 1\\
    h'(B)=\max(h(A),h'(rs_B))+1=x+1\\
    h'(D)=\max(h(E),h'(ls_D))+1=x+1\\
    h'(B)-h'(D)=0
\end{cases}
$$

Therefore, the rotated nodes B, C, and D also satisfy property 2.

???+ note "Balance maintenance operations: pseudocode"
    $$
    \begin{array}{ll}
    1 &  \textbf{function } \mathrm{MaintainBalance}(p) \\
    2 &  \qquad l \gets ls_p, r \gets rs_p \\
    3 &  \qquad \textbf{if } h(l)-h(r)=2 \\
    4 &  \qquad\qquad \textbf{if } h(ls_l) \ge h(rs_l) \\
    5 &  \qquad\qquad\qquad \mathrm{RightRotate}(p) \\
    6 &  \qquad\qquad \textbf{else} \\
    7 &  \qquad\qquad\qquad \mathrm{LeftRotate}(l) \\
    8 &  \qquad\qquad\qquad \mathrm{RightRotate}(p) \\
    9 &  \qquad \textbf{else if } h(l)-h(r)=-2 \\
    10 &  \qquad\qquad \textbf{if } h(ls_r) \le h(rs_r) \\
    11 &  \qquad\qquad\qquad \mathrm{LeftRotate}(p) \\
    12 &  \qquad\qquad \textbf{else} \\
    13 &  \qquad\qquad\qquad \mathrm{RightRotate}(r) \\
    14 &  \qquad\qquad\qquad \mathrm{LeftRotate}(p) \\
    \end{array}
    $$

Same as other balanced binary search trees, AVL tree nodes' height, subtree size, etc. information needs to be maintained during rotation.

## Other Operations

Other operations of AVL trees (Predecessor, Successor, Select, Rank, etc.) are the same as those in ordinary binary search trees.

## Reference Code

The following code implements a `Map` using AVL trees, i.e., an ordered immutable mapping:

??? note "Reference Code"
    ```cpp
    --8<-- "docs/ds/code/avl-tree/AvlTreeMap.hpp"
    ```

## Other Resources

You can observe the process of AVL trees maintaining balance in [AVL Tree Visualization](https://www.cs.usfca.edu/~galles/visualization/AVLtree.html).

[Wikipedia -- AVL tree](https://en.wikipedia.org/wiki/AVL_tree)
