author: Ir1d, 0xis-cn

## Introduction

A **scapegoat tree** is a weight-balanced binary search tree that maintains balance through rebuilding operations. After insertion and deletion operations, a scapegoat tree checks whether the tree has become unbalanced; if it has, it rebuilds targeted subtrees to restore balance.

In general, scapegoat trees do not support range operations and cannot be made fully persistent. However, they have the advantages of simple implementation and relatively small constant factors.

## Basic Structure and Operations

The core operations of a scapegoat tree are rebuilding, insertion, and deletion.

### Node Information

A scapegoat tree needs to store the following information for self-balancing:

-   Tree structure information:
    -   `id`: the number of used nodes;
    -   `rt`: the root node;
    -   `lc[x]`, `rc[x]`: the left and right child nodes;
    -   `tot[x]`: the size of the subtree rooted at $x$ (each node counts as $1$)[^tot-cnt];
    -   `tot_active`: the number of nodes in the entire tree that have not been deleted, that is, `cnt[x] != 0`.

When using a scapegoat tree to implement a balanced tree, the following information also needs to be stored:

-   Balanced-tree node information:
    -   `val[x]`: the value stored in the node;
    -   `cnt[x]`: the count of the value stored in the node (possibly $0$);
    -   `sz[x]`: the count of stored values in the subtree rooted at $x$.

To maintain node information, the `push_up` operation can be implemented:

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/ds/code/sgt/sgt.cpp:push-up"
    ```

Note the difference between how `tot[x]` and `sz[x]` are updated.

### Rebuilding

When the tree becomes unbalanced, a certain subtree needs to be rebuilt to make it as balanced as possible. Rebuilding consists of two steps:

-   Perform an inorder traversal of the subtree to be rebuilt and store all non-deleted nodes in a sequence;
-   Build the tree by binary splitting, that is, take the midpoint as the root, recursively build the left and right subtrees, and update node information.

A reference implementation is as follows:

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/ds/code/sgt/sgt.cpp:rebuild"
    ```

When building the tree, remember to maintain node information, including information for leaf nodes.

The complexity of a single rebuild is $\Theta(|T_x|)$. Therefore, if rebuilding is performed after every insertion or deletion, the complexity becomes unacceptable. The core idea of the scapegoat tree is choosing when to rebuild, thereby achieving amortized $O(\log n)$ complexity.

### Insertion

An insertion may cause the tree to become unbalanced. To determine imbalance, introduce a parameter $\alpha\in(0.5,1)$, usually chosen between $0.7\sim 0.8$.

If the depth of the newly inserted node exceeds $\lfloor\log_{1/\alpha}|T|\rfloor$, where $|T|$ is the size of the updated tree, then during backtracking we need to find the node where imbalance occurs and rebuild it. At this point, the following condition is used to determine whether the subtree rooted at $x$ is unbalanced:

$$
\max\{|T_{\mathrm{left}(x)}|,|T_{\mathrm{right}(x)}|\} > \alpha\cdot |T_x|,
$$

where $\mathrm{left}(x)$ and $\mathrm{right}(x)$ are the left and right child nodes of $x$, respectively, and $|T_x|$ is the size of the subtree rooted at $x$.

The specific steps of insertion are as follows:

-   First, use the binary search tree property to search downward for the insertion position, recording the depth during descent;
-   If the node already exists, directly modify its node information; otherwise, create a new node;
-   If the newly created node is too deep, backtrack from bottom to top to the root, update node information, and record the first (or any) node whose subtree is unbalanced;
-   If an unbalanced node exists, rebuild the subtree rooted at that node.

A reference implementation is as follows:

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/ds/code/sgt/sgt.cpp:insert"
    ```

Note that a single insertion causes at most one rebuild. If no new node is added, or the newly added node is not too deep, or a rebuild has already been performed during this backtracking process, there is no need to continue checking for imbalance. Extra rebuilding may cause efficiency loss[^insert-complexity]. The first unbalanced node encountered during backtracking is the so-called "scapegoat."

### Deletion

Deletion is handled very simply. The deletion strategy of a scapegoat tree is lazy deletion: when a node becomes empty, it is not removed immediately, but left for later processing.

Of course, if there are too many empty nodes in the tree, access efficiency will drop significantly. Therefore, a scapegoat tree maintains two counts: the number of non-deleted nodes in the entire tree and the number of nodes actually used by the entire tree. For a chosen threshold[^threshold] $\alpha\in(0,1)$, when the ratio of the former to the latter falls below $\alpha$, rebuild the entire tree once, deleting all empty nodes during the rebuild.

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/ds/code/sgt/sgt.cpp:remove"
    ```

### Time Complexity

For a scapegoat tree of size $n$, the time complexity for accessing nodes is $O(\log n)$ per operation, and the amortized time complexity of $\Theta(n)$ insertions and deletions is also $O(\log n)$ per operation.

This section gives only a brief argument for the time complexity of scapegoat trees. For a detailed proof, refer to the original paper.

??? note "Argument for the Time Complexity of Scapegoat Trees"
    Because lazy deletion is used, a scapegoat tree with $n$ non-deleted nodes may occupy $\alpha^{-1}n$ nodes. Since this differs only by a constant factor, this article does not distinguish between the number of non-deleted nodes and the number of occupied nodes in a scapegoat tree, and uniformly calls it the "tree size."
    
    1.  **Access operations**: The complexity of access operations is guaranteed because the height of a scapegoat tree of size $n$ is always $O(\log n)$.
    
        First, distinguish two concepts:
    
        -   $\alpha$-weight-balanced: at every node, the sizes of the subtrees of the left and right children are both at most $\alpha$ times the size of the subtree at that node;
        -   $\alpha$-height-balanced: the height of the tree does not exceed $\lfloor\log_{1/\alpha}|T|\rfloor$, where $T$ is the tree size.
    
        $\alpha$-weight-balance implies $\alpha$-height-balance, because every time the child depth increases by one, the size decreases to $\alpha$ times the original size. The converse is not necessarily true. More precisely, after every operation, a scapegoat tree is always $\alpha$-height-balanced[^hei-bal], which guarantees the complexity of access operations.
    
        Only insertion changes the tree structure, so it is sufficient to show that after every insertion, the scapegoat tree is still $\alpha$-height-balanced. If the newly inserted node is too deep and causes the whole tree to no longer be $\alpha$-height-balanced, then when backtracking from that node to the root, we must encounter at least one node, namely the "scapegoat," whose subtree is no longer $\alpha$-weight-balanced. After rebuilding it, the height of the subtree decreases by at least one, so the newly inserted node is no longer too deep.
    2.  **Insertion operations**: The complexity of insertion is amortized $O(\log n)$.
    
        Suppose that after some insertion, a subtree rebuild occurs at node $x$, with time cost $\Theta(|T_x|)$. When node $x$ was first inserted, or just after it last experienced a rebuild of itself or an ancestor, its left and right subtrees differed in size by at most one node. Before this rebuild, node $x$ must satisfy
    
        $$
        \max\{|T_{\mathrm{left}(x)}|,|T_{\mathrm{right}(x)}|\} > \alpha\cdot |T_x|.
        $$
    
        This condition guarantees that the difference between the sizes of the left and right subtrees is at least $(2\alpha-1)|T_x|$. Therefore, between these two rebuilds, the subtree $T_x$ received $\Omega(|T_x|)$ inserted nodes.
    
        By amortized analysis[^alternative-analysis], if each time a node is inserted, every node on the path from the root to that node (before a possible rebuild) receives $\Theta(1)$ potential, then before the subtree at node $x$ is rebuilt, node $x$ must have accumulated $\Omega(|T_x|)$ potential, enough to pay for node $x$'s subtree rebuilding cost $\Theta(|T_x|)$. Since the tree depth is always $O(\log n)$, the potential added by a single insertion is $O(\log n)$. This shows that the total increase in potential over $\Theta(n)$ insertions is $O(n\log n)$. Thus, the total cost of subtree rebuilding is also $O(n\log n)$, and the amortized time complexity of a single insertion operation, including rebuilding, is $O(\log n)$.
    
        Note that the analysis does not assume that, between two rebuilds at node $x$, no other rebuilds occur inside subtree $T_x$. Therefore, as long as we only rebuild subtrees at nodes that satisfy the imbalance condition, the complexity is guaranteed to be correct.
    3.  **Deletion operations**: The complexity of deletion is also amortized $O(\log n)$.
    
        A rebuild caused by deletion makes the entire tree contain no empty nodes. Before a rebuild caused by some deletion, there are already $\Theta(n)$ empty nodes in the entire tree, which means that at least $\Theta(n)$ deletion operations have been performed. Since each deletion operation has addressing complexity $O(\log n)$ and a single rebuild has complexity $\Theta(n)$, the actual time cost of these $\Theta(n)$ deletion operations is
    
        $$
        \Theta(n)O(\log n)+\Theta(n)
        $$
    
        Therefore, the amortized complexity of a single deletion is $O(\log n)$.

## Balanced-Tree Operations

This section introduces how to maintain a multiset with a scapegoat tree.

Except for the operations introduced in the previous section, the remaining operations are common balanced-tree operations. However, because empty nodes may exist in a scapegoat tree, these operations also need corresponding adjustments.

### Querying Rank

Use the binary search tree property to search downward for the node position, while recording the number of stored values on the left side of the path.

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/ds/code/sgt/sgt.cpp:find-rank"
    ```

### Querying a Value by Rank

Use the subtree value-count information recorded at each node to search downward. Note that nodes with zero count may exist.

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/ds/code/sgt/sgt.cpp:find-kth"
    ```

### Querying Predecessor and Successor

Combine the two functions above.

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/ds/code/sgt/sgt.cpp:pred-succ"
    ```

If implementing this directly, be careful to handle nodes whose count is zero.

### Reference Implementation

At the end of this section, here is a reference implementation for the template problem [Ordinary Balanced Tree](https://loj.ac/p/104).

??? example "Reference Implementation"
    ```cpp
    --8<-- "docs/ds/code/sgt/sgt.cpp:full-text"
    ```

## References

-   Galperin, Igal, and Ronald L. Rivest. "Scapegoat trees." Proceedings of the fourth annual ACM-SIAM Symposium on Discrete algorithms. 1993.
-   [Scapegoat Tree - Wikipedia](https://en.wikipedia.org/wiki/Scapegoat_tree)
-   [Scapegoat Tree - riteme's blog](https://riteme.site/blog/2016-4-6/scapegoat.html)

[^tot-cnt]: It is also possible to count only non-deleted nodes. In that case, `tot_active` is no longer needed; instead, count the total number of occupied nodes as `tot_max`, and adjust the code accordingly.

[^insert-complexity]: According to the later complexity analysis, these efficiency losses only mean a larger constant factor, while the complexity is still correct. Because checking tree depth may involve many floating-point logarithm operations, code that does not check tree depth and only checks imbalance may be faster on some data.

[^threshold]: This does not have to be the same as the parameter chosen for insertion above. Although the original paper makes this assumption, choosing different parameters only changes the constant factor in the complexity of a single operation, and the overall complexity remains correct.

[^hei-bal]: According to the original definition, $n$ refers to the number of non-deleted nodes, so it can only guarantee that the tree height does not exceed $\lfloor\log_{1/\alpha}n\rfloor+1$, which is called weak $\alpha$-height-balance. The constant-term difference is not examined in detail here.

[^alternative-analysis]: Some articles simply analyze this as $\Omega(|T_x|)$ insertions corresponding to one rebuild, so the amortized complexity is $\dfrac{\Omega(|T_x|)O(\log n)+\Theta(|T_x|)}{\Omega(|T_x|)} = O(\log n)$. This way of thinking can help understand why the amortized complexity is correct, but it is not rigorous. This is because one insertion may correspond to rebuilds of multiple ancestor nodes, so when node $x$ is rebuilt, it is not obvious that the number of nodes in the subtree that did not cause rebuilding is $\Omega(|T_x|)$.
