author: 0x03A6, abc1763613206, auuuu4, CCXXXI, Conless, Enter-tainer, fanenr, happyZYM, hsfzLZH1, iamtwz, LeverImmy, leverimmy, Lhcfl, Marcythm, RIvance, Tiphereth-A, trudbot, Xeniume, Xeonacid, YBYCS, yuhuoji

A red-black tree is a self-balancing binary search tree. Each node stores an additional `color` field (`"RED"` or `"BLACK"`) to keep the tree balanced during insertion and deletion.

Red-black trees are a variant of order-4 B-trees ([2-3-4 trees](https://en.wikipedia.org/wiki/2%E2%80%933%E2%80%934_tree)).[^gilbas1978]

## Properties

A valid red-black tree must satisfy the following four properties:

1.  Every node is either red or black.
2.  NIL nodes (empty leaf nodes) are black.
3.  The children of a red node are black.
4.  Every path from the root to a NIL node contains the same number of black nodes.

The following figure shows a valid red-black tree:

![rbtree-example](images/rbtree-example.svg)

???+ note "Note"
    Some sources add a fifth property: the root must be black. This requires recoloring the root black after insertion if it is red. However, recoloring the root black can also be delayed until deletion, so this property is not mandatory. The implementation in this article does satisfy it. For precision, here is the explanation from [Wikipedia](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree#Properties):
    
    > Some authors, e.g. Cormen & al.,[^cite_note-cormen2009-18]claim "the root is black" as fifth requirement; but not Mehlhorn & Sanders[^cite_note-mehlhorn2008-17]or Sedgewick & Wayne.[^cite_note-algs4-16]Since the root can always be changed from red to black, this rule has little effect on analysis. This article also omits it, because it slightly disturbs the recursive algorithms and proofs.

## Red-Black Tree Class Definition

```cpp
--8<-- "docs/ds/code/rbtree/rbtree.hpp:class-node1"
  // ...
--8<-- "docs/ds/code/rbtree/rbtree.hpp:class-node2"
```

???+ note "Note"
    In red-black tree nodes, storing child pointers in an array can improve code reuse.

## Operations

???+ note "Note"
    There are several ways to implement insertion and deletion in red-black trees. This article follows *Introduction to Algorithms*: insertion fix-up is divided into 3 cases, and deletion fix-up into 4 cases.

Traversal, finding the minimum/maximum, searching, querying the rank of an element, finding an element by rank, and finding predecessors/successors are the same as in a [binary search tree](./bst.md), so they are omitted here.

In the code comments for insertion/deletion fix-up below, we use the following conventions:

-   `p` means node `p` is black.
-   `[p]` means node `p` is red.
-   `{p}` means node `p` is either red or black.
-   `|p|` means node `p` is a NIL node or is black.

### Rotation

Rotation is the key operation that lets most balanced trees maintain balance. It changes local node depths without changing the inorder traversal of a valid BST.

![rbtree-rotations](images/rbtree-rotate.svg)

???+ note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:rotate"
    ```

### Insertion

Insertion in a red-black tree is similar to insertion in an ordinary BST. A newly inserted node is initially red. After insertion, the tree must be fixed according to the states of the inserted node and related nodes so that the four properties above hold.

???+ note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:insert"
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:insert-leaf"
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:insert-fixup1"
        // ...
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:insert-fixup2"
    ```

### Balance Maintenance After Insertion

???+ note "Note"
    To deepen your understanding, verify that property 4 holds after each fix-up.

Since an inserted node is red unless it becomes the root, insertion may violate property 3, so balance must be restored.

Let the inserted node be $n$, its parent be $p$, its grandparent be $g$, and its uncle be $u$. By property 3, $g$ must be black.

Fix-up proceeds recursively upward from the insertion point. If $p$ is black, stop; otherwise there are 3 cases.

```cpp
--8<-- "docs/ds/code/rbtree/rbtree.hpp:insert-aux1"
      // ...
--8<-- "docs/ds/code/rbtree/rbtree.hpp:insert-aux2"
```

#### Insert Case 1

Both $p$ and $u$ are red. Recoloring is sufficient.

![](images/rbtree-insert-case1.svg)

???+ note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:insert-case1"
    ```

#### Insert Case 2

$p$ is red, $u$ is black, and the direction of $p$ differs from the direction of $n$.

Rotate node $p$ to transform this into case 3.

![](images/rbtree-insert-case2.svg)

???+ note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:insert-case2"
    ```

#### Insert Case 3

$p$ is red, $u$ is black, and the directions of $p$ and $n$ are the same.

Rotate node $g$ so that $p$ becomes the root of the subtree, then swap the colors of $p$ and $g$.

![](images/rbtree-insert-case3.svg)

???+ note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:insert-case3"
    ```

### Deletion

Deletion in a red-black tree has more steps than deletion in an ordinary BST:

-   If the node $n$ to be deleted has two children, swap the data of $n$ with the minimum node $s$ in its right subtree, then set $n$ to $s$. Now $n$ cannot have two children.
-   If $n$ has one child $s$, then property 4 implies $s$ must be red, and property 3 implies $n$ must be black. Replace the pointer to $n$ in its parent $p$ by the address of $s$, replace $s$'s parent pointer by $p$, and recolor $s$ black.
-   If $n$ has no children, then if $n$ is the root or $n$ is red, delete it directly. Otherwise direct deletion violates property 4, so balance must be restored.

???+ note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:delete"
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:delete-leaf"
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:delete-fixup1"
        // ...
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:delete-fixup2"
    ```

### Balance Maintenance After Deletion

???+ note "Note"
    To deepen your understanding, verify that property 4 holds after each fix-up.

From the discussion above, $n$ is a black leaf and is not the root. Let $n$'s parent be $p$, its sibling be $s$, and its nephews be $c$ and $d$.

Deletion fix-up also proceeds recursively upward from $n$. If $n$ is the root or $n$ is red, stop; otherwise there are 4 cases.

```cpp
--8<-- "docs/ds/code/rbtree/rbtree.hpp:delete-aux1"
      // Delete case 1
      // ...
      // Other cases
--8<-- "docs/ds/code/rbtree/rbtree.hpp:delete-aux2"
      // ...
--8<-- "docs/ds/code/rbtree/rbtree.hpp:delete-aux3"
```

#### Delete Case 1

$s$ is red.

Rotate $p$ so that $s$ becomes the subtree root, then swap the colors of $s$ and $p$ to transform this into one of the other three cases.

![](images/rbtree-remove-case1.svg)

???+ note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:delete-case1"
    ```

#### Delete Case 2

The color of $p$ is unknown, and $s$, $c$, $d$ are all black.

Only recolor $s$ red.

![](images/rbtree-remove-case2.svg)

Note that if $p$ is red, property 3 would be violated, but if $p$ is red the loop exits immediately, so we recolor it black at the end.

???+ note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:delete-case2"
    ```

#### Delete Case 3

The color of $p$ is unknown, $s$ and $d$ are black, and $c$ is red.

Rotate $s$ so that $c$ becomes the root of the subtree formerly rooted at $s$, then swap the colors of $s$ and $c$ to transform this into case 4.

![](images/rbtree-remove-case3.svg)

???+ note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:delete-case3"
    ```

#### Delete Case 4

The colors of $p$ and $c$ are unknown, $s$ is black, and $d$ is red.

Rotate $p$ so that $s$ becomes the subtree root, swap the colors of $s$ and $p$, recolor $d$ black, and stop the fix-up.

![](images/rbtree-remove-case4.svg)

???+ note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:delete-case4"
    ```

## Reference Code

The following code implements a `set` with a red-black tree:

??? note "Implementation"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:full"
    ```

??? note "Example Problems: [Luogu P3369 Template Ordinary Balanced Tree](https://www.luogu.com.cn/problem/P3369) and [Luogu P6136 Template Ordinary Balanced Tree (Enhanced Data)](https://www.luogu.com.cn/problem/P6136)"
    ```cpp
    --8<-- "docs/ds/code/rbtree/rbtree.hpp:class"
    --8<-- "docs/ds/code/rbtree/rbtree_1.cpp:main"
    ```

## Relationship With 2-3-4 Trees

A 2-3-4 tree is an order-4 B-tree. Like ordinary B-trees, it supports search, insertion, and deletion in $O(\log n)$ time. Its nodes are 2-nodes, 3-nodes, and 4-nodes, containing one, two, or three data elements respectively. All leaf nodes have the same depth, and all data is stored in order.

2-3-4 trees and red-black trees are isomorphic. Every red-black tree corresponds to a 2-3-4 tree. Insertions and deletions in a 2-3-4 tree cause node expansion, splitting, and merging, corresponding to recoloring and rotations in a red-black tree. The following figure shows the red-black tree nodes corresponding to 2-, 3-, and 4-nodes of a 2-3-4 tree. A 3-node in a 2-3-4 tree corresponds to two cases in a red-black tree, with the red node leaning left or right, so one red-black tree may correspond to multiple 2-3-4 trees.

![2-3-4-tree-rbt-1](images/2-3-4-tree-rbt-1.svg)

The following figure shows a red-black tree and its corresponding 2-3-4 tree. Move red nodes in the red-black tree up to the left or right side of their parent to form B-tree nodes, obtaining the corresponding 2-3-4 tree. The number of nodes in the red-black tree equals the number of data elements in the 2-3-4 tree.

![2-3-4-tree-rbt](images/2-3-4-tree-rbt-2.svg)

Comparing with 2-3-4 trees can help understand insertion and deletion in red-black trees.[^234-vs-rbt]

## Use In Real Engineering Projects

Red-black trees are among the most widely used in-memory balanced trees in industry because of their overall efficiency. This section lists several practical uses and links to their source code for comparison and study.

### Linux

Source code:

-   [`linux/lib/rbtree.c`](https://elixir.bootlin.com/linux/latest/source/lib/rbtree.c)

Linux implements all red-black tree operations iteratively, preserving efficiency while adding many comments for readability. Reading it is highly recommended. Red-black trees are widely used in the Linux kernel; here are a few classic examples.

-   [CFS non-real-time task scheduling](https://www.kernel.org/doc/html/latest/scheduler/sched-design-CFS.html)

    Since stable kernel version 2.6.24, Linux has used the CFS scheduler. All runnable non-real-time processes are maintained in a red-black tree keyed by virtual runtime, enabling fairer and more efficient scheduling. CFS abandons active/expired arrays and dynamic priority calculation. It no longer tracks sleep time or distinguishes interactive tasks; instead, it selects the next task by a time-based red-black tree key and determines scheduling priority according to CPU time usage.

-   [epoll](https://man7.org/linux/man-pages/man7/epoll.7.html)

    `epoll`, short for event poll, is an implementation of IO multiplexing in the Linux kernel and an improvement over `poll`/`select`. Linux uses a red-black tree to store file descriptors in `epoll`.

### Nginx

Source code:

-   [`nginx/src/core/ngx_rbtree.h`](https://github.com/nginx/nginx/blob/master/src/core/ngx_rbtree.h)
-   [`nginx/src/core/ngx_rbtree.c`](https://github.com/nginx/nginx/blob/master/src/core/ngx_rbtree.c)

User-space timers in nginx are implemented with red-black trees. All timer nodes are maintained by one red-black tree. In each worker-process loop, `ngx_process_events_and_timers` calls `ngx_event_expire_timers`, which repeatedly extracts the node with the minimum time value from the red-black tree, checks whether it has timed out, and executes its function until the next extracted node has not timed out.

There are many public analyses of nginx's red-black tree source code; readers can search and study them.

### C++

Source code:

-   GNU libstdc++

    -   [`libstdc++-v3/include/bits/stl_tree.h`](https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/bits/stl_tree.h)
    -   [`libstdc++-v3/src/c++98/tree.cc`](https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/src/c%2B%2B98/tree.cc)

    In addition, `libstdc++` provides [`__gnu_cxx::rb_tree`](https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/ext/rb_tree) in `<ext/rb_tree>`. It inherits from `std::_Rb_tree` and can be regarded as an externally usable type alias. Note that this header is **not** part of the C++ standard, so it is not recommended unless necessary.

    `libstdc++` also provides red-black trees in [`pb_ds`](../lang/pb-ds/tree.md).

-   LLVM libcxx
    -   [`libcxx/include/__tree`](https://github.com/llvm/llvm-project/blob/main/libcxx/include/__tree)

-   Microsoft STL
    -   [`stl/inc/xtree`](https://github.com/microsoft/STL/blob/main/stl/inc/xtree)

Most STL implementations use red-black trees internally for `std::set` and `std::map`, including those listed above. However, the C++ standard does not require `std::set` and `std::map` to be implemented with red-black trees, so engineering projects should not depend directly on their internal data structures.

### OpenJDK

Source code:

-   [`java.util.TreeMap<K, V>`](https://github.com/openjdk/jdk/blob/master/src/java.base/share/classes/java/util/TreeMap.java)
-   [`java.util.TreeSet<K, V>`](https://github.com/openjdk/jdk/blob/master/src/java.base/share/classes/java/util/TreeSet.java)
-   [`java.util.HashMap<K, V>`](https://github.com/openjdk/jdk/blob/master/src/java.base/share/classes/java/util/HashMap.java)

In the JDK, `TreeMap` and `TreeSet` use red-black trees as their underlying data structure. Since JDK 1.8, a bucket chain inside `HashMap` is also automatically converted into a red-black tree when its length exceeds 8, improving lookup efficiency.

## References

-   Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2022).*Introduction to algorithms*. MIT press.
-   [Red-Black Tree - Wikipedia](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree)
-   [Red-Black Tree Visualization](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html)

[^gilbas1978]: L. J. Guibas and R. Sedgewick, "A dichromatic framework for balanced trees,"*19th Annual Symposium on Foundations of Computer Science (sfcs 1978)*, Ann Arbor, MI, USA, 1978, pp. 8-21, doi:[10.1109/SFCS.1978.3](https://doi.org/10.1109%2FSFCS.1978.3).

[^cite_note-cormen2009-18]: <https://en.wikipedia.org/wiki/Red–black_tree#cite_note-Cormen2009-18>

[^cite_note-mehlhorn2008-17]: <https://en.wikipedia.org/wiki/Red–black_tree#cite_note-Mehlhorn2008-17>

[^cite_note-algs4-16]: <https://en.wikipedia.org/wiki/Red–black_tree#cite_note-Algs4-16>: 432–447

[^234-vs-rbt]: [This blog post](https://www.cnblogs.com/zhenbianshu/p/8185345.html) provides a detailed description.
