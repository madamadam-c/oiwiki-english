AA tree is a balanced tree structure for efficient storage and retrieval of ordered data, introduced by Professor Arne Andersson in his 1993 paper "Balanced search trees made simple". The design aims to reduce the number of cases considered in red-black trees. AA trees can perform search, insertion, and deletion in $O(\log N)$ time. Below is an example of an AA tree.

![aa-tree-1](images/aa-tree-1.jpg)

AA trees are a variant of red-black trees where red nodes can only be right children (unlike red-black trees). This causes AA trees to simulate 2-3 trees instead of 2-3-4 trees, greatly simplifying maintenance operations. Red-black tree maintenance algorithms need to consider seven different cases to properly balance the tree.

![red-black tree](images/aa-tree-2.svg)

Since red nodes can only be right children, AA trees only need to consider two cases.

![aa-tree](images/aa-tree-3.svg)

## Definition

AA trees follow the same rules as red-black trees but add one new rule: **red nodes cannot appear as left children**.

1.  Each node can be red or black.
2.  The root is always black.
3.  Leaves (NULL) are always black.
4.  Both children of a red node must be black (i.e., no two adjacent red nodes).
5.  Every path from root to NULL contains the same number of black nodes.
6.  Red nodes can only be right children.

## Balance Maintenance

Each AA tree node maintains a **level** field, similar to how red-black tree nodes maintain a color field ("RED" or "BLACK"). Level must satisfy the following 5 conditions:

1.  Every leaf node has level 1.
2.  Every left child has level equal to its parent's level minus 1.
3.  Every right child has level equal to its parent's level or parent's level minus 1.
4.  Every right grandchild has level strictly less than its grandparent's level.
5.  Every node with level greater than 1 has two children.

![aa-tree-4](images/aa-tree-4.jpg)

### Horizontal Link

A link where a child's level equals its parent's level is called a **horizontal link**, analogous to red links in red-black trees. Single right horizontal links are allowed, but consecutive right horizontal links are not; left horizontal links are not allowed. These restrictions are stricter than those in red-black trees, making the balancing process in AA trees much simpler programmatically than in red-black trees.

![aa-tree-5](images/aa-tree-5.jpg)

Insertion and deletion operations may temporarily cause AA trees to lose balance (i.e., violate AA tree invariants). Restoring balance requires only two different operations: "**skew**" and "**split**". "Skew" performs a right rotation on a subtree containing a left horizontal link to replace it with a subtree containing a right horizontal link. "Split" performs a left rotation and increases level to replace a subtree with two or more consecutive right horizontal links with a subtree having fewer consecutive right horizontal links. Balanced insertion and deletion implementations become simpler by relying on "skew" and "split" operations to modify the tree only when necessary, rather than letting the caller decide whether to perform "skew" or "split".

### split (Left Rotation)

A continuous rightward horizontal link (three consecutive right children at the same level, nodes R and X being red nodes).

At this point, left-rotate node *T*, treating nodes less than or equal to this level as a subtree.

1.  The root of the subtree's right child becomes the new subtree root;
2.  The original subtree root becomes the new subtree root's left child;
3.  New subtree root level increases by 1.

![aa-tree-split](images/aa-tree-split.svg)

???+ note "Pseudocode Implementation"
    $$
    \begin{array}{ll}
    1 & \textbf{function } \text{split}(\text{root}) \\
    2 & \qquad \textbf{if } \text{root}\rightarrow\text{right}\rightarrow\text{right}\rightarrow\text{level} == \text{root}\rightarrow\text{level} \\
    3 & \qquad\qquad \text{rotate\_left}(\text{root}) \\
    4 & \textbf{end function}
    \end{array}
    $$

### skew (Right Rotation)

A leftward horizontal link (two consecutive left children at the same level).

Right-rotate node *T*, treating nodes less than or equal to this level as a subtree.

1.  The root of the subtree's left child becomes the new subtree root;
2.  The original subtree root becomes the new subtree root's right child.

![aa-tree-skew](images/aa-tree-skew.svg)

???+ note "Pseudocode Implementation"
    $$
    \begin{array}{ll}
    1 & \textbf{function } \text{skew}(\text{root}) \\
    2 & \qquad \textbf{if } \text{root}\rightarrow\text{left}\rightarrow\text{level} == \text{root}\rightarrow\text{level} \\
    3 & \qquad\qquad \text{rotate\_right}(\text{root}) \\
    4 & \textbf{end function}
    \end{array}
    $$

## AA Tree Operations

An AA tree is itself a binary search tree, so search operations are identical to those in other binary search trees. Insertion and deletion operations are similar to *AVL* trees: first insert or delete the key in the tree, then retreat along the search path to the root, reconstructing the tree during this process.

### Insertion

???+ note "Pseudocode Implementation"
    $$
    \begin{array}{ll}
    1 & \textbf{function } \text{insert}(\text{root}, \text{add}) \\
    2 & \qquad \textbf{if } \text{root} == \text{NULL} \\
    3 & \qquad\qquad \text{root} \gets \text{add} \\
    4 & \qquad \textbf{else if } \text{add}\rightarrow\text{key} < \text{root}\rightarrow\text{key} \qquad //如果允许重复<= \\ 
    5 & \qquad\qquad \text{insert}(\text{root}\rightarrow\text{left}, \text{add}) \\
    6 & \qquad \textbf{else if } \text{add}\rightarrow\text{key} > \text{root}\rightarrow\text{key} \\
    7 & \qquad\qquad \text{insert}(\text{root}\rightarrow\text{right}, \text{add}) \\
    8 & \qquad \textbf{end if} \\
    9 & \qquad \text{//如果不允许重复，在每一level上进行skew和split} \\
    10 & \qquad \text{skew}(\text{root}); \\
    11 & \qquad \text{split}(\text{root}); \\
    12 & \textbf{end function}
    \end{array}
    $$

### Deletion

The deletion process is similar to other binary balanced trees: first convert internal node deletion to leaf node deletion by replacing the internal node with its closest predecessor or successor node. Since all AA tree nodes with level greater than 1 have two children, predecessor or successor nodes will be at level 1, making deletion of level 1 nodes relatively simple.

???+ note "Pseudocode Implementation"
    $$
    \begin{array}{ll}
    1 &  \text{//To rebalance the tree} \\
    2 &  \textbf{if} \ \text{root->left->level} < \text{root->level} -1 \ \textbf{or} \ \text{root->right->level} < \text{root->level} -1 \\
    3 &  \{ \\
    4 & \qquad \textbf{if} \ \text{root->right->level} > \text{--root->level} \\
    5 & \qquad \{ \\
    6 & \qquad\qquad \text{root->right->level} \gets \text{root->level} \\
    7 & \qquad \} \\
    8 & \qquad \text{skew}(\text{root}) \\
    9 & \qquad \text{skew}(\text{root->right}) \\
    10 & \qquad \text{skew}(\text{root->right->right}) \\
    11 & \qquad \text{split}(\text{root}) \\
    12 & \qquad \text{split}(\text{root->right}) \\
    13 &  \} \\
    \end{array}
    $$

## Performance

AA tree performance is comparable to red-black tree performance. Although AA trees perform more rotation operations than red-black trees, AA tree algorithms are simpler, ultimately resulting in similar performance. Red-black tree performance is more consistent across various situations, while AA trees tend to be flatter, giving AA trees slightly faster search speed.

## References

1.  [AA tree - Wikipedia](https://en.wikipedia.org/wiki/AA_tree)
2.  [Introduction to AA trees](https://iq.opengenus.org/aa-trees/)
3.  [AA tree - Visualization](https://kubokovac.eu/gnarley-trees/AAtree.html)
4.  [CMSC 420 Lecture 6: 2-3, Red-black, and AA trees](https://www.cs.umd.edu/class/fall2019/cmsc420-0201/Lects/lect06-aa.pdf)
