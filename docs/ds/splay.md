This page will briefly introduce how to use Splay to maintain binary search trees.

## definition

**Splay tree**, or **stretch tree**, is a balanced binary search tree that continuously rotates a node to the root node through the **stretch (splay) operation** so that the entire tree still satisfies the properties of a binary search tree and can complete insertion, search, and deletion operations in an evenly distributed $O(\log N)$ time, and remains balanced without degenerating into a chain.

The Splay tree was invented by Daniel Sleator and Robert Tarjan in 1985.

## Basic structure and operation

This section discusses the basic structure of the Splay tree and its core operations, the most important of which is the stretch operation.

The Splay tree is a binary search tree. When searching for a certain value, it satisfies the following properties: the value of any node in the left subtree $<$ the value of the root node $<$ the value of any node in the right subtree.

### Maintenance information

This article uses array simulation pointers to implement the Splay tree, and the following information needs to be maintained:

|   rt  |    id   | fa\[i] | ch\[i]\[0/1] | val\[i] | cnt\[i] | sz\[i] |
| :---: | :-----: | :----: | :----------: | :-----: | :-----: | :----: |
| Root node number | Number of used nodes | Father | Left and right son numbers | Node weight | Number of weight occurrences | Subtree size |

During initialization, all information can be set to zero.

### Auxiliary operations

First are some simple auxiliary operations:

-   `dir(x)`: Determine whether node $x$ is the left son or right son of the father node;
-   `push_up(x)`: After changing the node position, update the information of node $x$ based on the child node information.

???+ example "implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:aux"
    ```

### rotation operation

In order to keep Splay balanced, rotation is required. The function of rotation is to move a node up one position.

Rotation needs to ensure:

-   The in-order traversal of the entire Splay remains unchanged (the properties of the binary search tree cannot be destroyed);
-   The information maintained by the affected nodes is still correct and valid;
-   `rt` must point to the rotated root node.

There are two types of rotation in Splay: left-hand rotation and right-hand rotation.

![](./images/splay-rotate.svg)

Observing the diagram, we can see that if the node $x$ ($1$ when turning left and $2$ when turning right) is moved upward through rotation, the direction of rotation is uniquely determined by whether the node is the left node or the right node of its parent node. Therefore, when implementing the rotation operation, you only need to pass in the node $x$ to be moved up.

Specific analysis of the rotation steps: (Assume that the node that needs to be moved up is $x$, taking right rotation as an example)

1.  First, record node $x$'s parent node $y$, and $y$'s parent node $z$ (possibly empty), and record whether $x$ is the left or right child node of $y$;
2.  In order from bottom to top in the rotated tree, update the left child node of $y$ to the right child node of $x$, the right child node of $x$ to $y$, and if $z$ is not empty, the child node of $z$ to $x$;
3.  In the same order, update the parent node of the left child node of the current $y$ (if it exists) to $y$, the parent node of $y$ to $x$, and the parent node of $x$ to $z$;
4.  Maintain node information from bottom to top.

???+ example "implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:rotate"
    ```

When implementing all functions, care should be taken not to modify the information of node $0$.

### Stretching

The Splay tree requires that every time a node $x$ is accessed, it must be forced to rotate to the root node. This operation is also called a stretching operation.

Let the node just visited be $x$. To do the stretching operation, you need to do a series of **stretching steps** on $x$. Each time a stretching step is performed on $x$, the distance between $x$ and the root node will be closer. Define $p$ as the parent node of $x$. There are three stretching steps:

1.  **zig**: Operate when $p$ is the root node. The Splay tree will rotate based on the edge between $x$ and $p$. **zig** exists to handle parity issues and is only executed as the last step of the stretch operation if $x$ has an odd depth at the beginning of the stretch operation.

    ![splay-zig](./images/splay-zig.svg)

That is, directly rotate $x$ to the right or left (Figure 1, 2).

![Picture 1](./images/splay-rotate1.svg)![Picture 2](./images/splay-rotate2.svg)

2.  **zig-zig**: Operate when $p$ is not the root node and $x$ and $p$ are both right child nodes or both left child nodes. The example below shows the situation when $x$ and $p$ are both left child nodes. The Splay tree is first rotated according to the edge connecting $p$ and its parent node $g$, and then rotated according to the edge connecting $x$ and $p$.

    ![splay-zig-zig](./images/splay-zig-zig.svg)

That is, first rotate $p$ to the right or left, and then rotate $x$ to the right or left (Figure 3, 4).

![Picture 3](./images/splay-rotate3.svg)![Picture 4](./images/splay-rotate4.svg)

3.  **zig-zag**: Operate when $p$ is not the root node and one of $x$ and $p$ is the right child node and the other is the left child node. The Splay tree is rotated first by the edge between $p$ and $x$, and then by the newly generated result edges of $x$ and $g$.

    ![splay-zig-zag](./images/splay-zig-zag.svg)

That is to say, $x$ first rotates left and then rotates right or first rotates right and then rotates left (Figure 5, 6).

![Picture 5](./images/splay-rotate5.svg)![Picture 6](./images/splay-rotate6.svg)

???+ tip "Tip"
Readers are asked to try to simulate $6$ rotation situations by themselves to understand the basic idea of ​​the stretching operation.

Comparing the three stretching steps, we can see that to distinguish which operation should be used at this time, the key is to determine whether $x$ is a child node of the root node, and whether $x$ and its parent node are on the same side of their respective parent nodes.

The implementation provided here can specify any root node $z$ and move any node $x$ up in its subtree to $z$:

1.  First, record the root node $z$'s parent node $w$, so that you can use `fa[x] == w` to determine that $x$ is already located at the root node;
2.  Record $x$'s current parent node $y$. If $y$ and $w$ are the same, it means $x$ has reached the root node;
3.  Otherwise, use `fa[y] == w` to determine whether $y$ is the root node. If so, directly perform zig operation to rotate $x$; if not, use `dir(x) == dir(y)` to determine whether to use zig-zig or zig-zag. The former rotates $y$ first and then $x$, and the latter directly rotates $x$ twice.

???+ example "implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:splay"
    ```

The stretching operation is the core operation of the Splay tree, and it is also a key step to ensure that its time complexity can be guaranteed. Please be sure to perform a stretch operation every time you access a node downwards.

In addition, the stretching operation will update all node information on the path from the current node $x$ to the root node $z$ from bottom to top. It is precisely because of this that the non-root node can be modified and then moved up to the root through a stretch operation to complete the information update of the entire tree.

### time complexity

For a Splay tree of size $n$, doing $m$ stretch operations has complexity $O((n+m)\log n)$, and the single amortized complexity is $O(\log n)$.

??? note "Complexity Proof Based on Potential Energy Analysis"
For this purpose, we only need to analyze the complexity of three operations: **zig**, **zig-zig** and **zig-zag**. To this end, we use the **potential energy analysis method** to deduce the amortized complexity of the operation by studying changes in potential energy. Assuming that a Splay tree containing $n$ nodes has been stretched $m$ times, it can be analyzed in the following way:
    
**definition**:
    
    1.  **Potential energy of a single node**: $w(x) = \log(\text{size}(x))$, where $\text{size}(x)$ represents the size of the subtree rooted at node $x$.
    2.  **Potential energy of the entire tree**: $\varphi = \sum w(x)$, that is, the sum of the potential energy of all nodes in the tree, and the initial potential energy satisfies $\varphi_0 \leq n \log n$.
    3.  **Amortized cost of the $i$th operation**: $c_i = t_i + \varphi_i - \varphi_{i-1}$, where $t_i$ is the actual operation cost, $\varphi_i$ and $\varphi_{i-1}$ are the potential energy after the operation and before the operation respectively.
    
**nature**:
    
    1.  If $p$ is the parent node of $x$, then there is $w(p) \geq w(x)$, that is, the potential energy of the parent node is not less than the potential energy of the child node.
    
    2.  Since the size of the root node's subtree remains unchanged before and after the operation, the potential energy of the root node remains unchanged during the operation.
    
    3.  If $\text{size}(p)\ge\text{size}(x)+\text{size}(y)$, then there is $2w(p) - w(x) - w(y) \geq 2$.
    
??? note "Proof of Property 3"
According to the mean inequality, we know
        
        $$
        \begin{aligned}
        2w(p) - w(x) - w(y) 
        &= \log\dfrac{\text{size}(p)^2}{\text{size}(x)\cdot\text{size}(y)} \\
        &> \log\dfrac{\left(\text{size}(x)+\text{size}(y)\right)^2}{\text{size}(x)\cdot\text{size}(y)} \\
        &\ge \log 4 \\
        &= 2.
        \end{aligned}
        $$
    
Next, perform potential energy analysis on the **zig**, **zig-zig** and **zig-zag** operations respectively. Assume that the potential energies of node $x$ before and after the operation are $w(x)$ and $w'(x)$ respectively. The notation of the nodes is consistent with [above](#stretch operation).
    
**zig**: According to properties 1 and 2, there is $w(p) = w'(x)$, and $w'(x) \geq w'(p)$. Therefore, the amortized cost is
    
    $$
    \begin{aligned}
    c_i &= 1 + w'(x) + w'(p) - w(x) - w(p)\\
    &= 1 + w'(p) - w(x)\\
    &\leq 1 + w'(x) - w(x).
    \end{aligned}
    $$
    
**zig-zig**: According to properties 1 and 2, there are $w(g) = w'(x)$, and $w'(x) \geq w'(p)$, $w(x) \leq w(p)$. because
    
    $$
    \begin{aligned}
    \text{size}'(x) 
    &= 3 + \text{size}(A) + \text{size}(B) + \text{size}(C) + \text{size}(D) \\
    &> (1 + \text{size}(A) + \text{size}(B)) + (1 + \text{size}(C) + \text{size}(D)) \\
    &= \text{size}(x) + \text{size}'(g),
    \end{aligned}
    $$
    
Available according to property 3
    
    $$
    2 w'(x) - w(x) - w'(g) \geq 2.
    $$
    
Therefore, the amortized cost is
    
    $$
    \begin{aligned}
    c_i &= 2 + w'(x) + w'(p) + w'(g) - w(x) - w(p) - w(g) \\
    &= 2 + w'(p) + w'(g) - w(x) - w(p) \\
    &\le (2 w'(x) - w(x) - w'(g)) + w'(p) + w'(g) - w(x) - w(p) \\
    &= 2(w'(x)-w(x)) + w'(p) - w(p) \\
    &\le 3(w'(x)-w(x)).
    \end{aligned}
    $$
    
**zig-zag**: According to properties 1 and 2, there is $w(g) = w'(x)$, and $w(p) \geq w(x)$. Because $\text{size}'(x)>\text{size}'(p)+\text{size}'(g)$, according to property 3, we can get
    
    $$
    2 \cdot w'(x) - w'(g) - w'(p) \geq 2.
    $$
    
Therefore, the amortized cost is
    
    $$
    \begin{aligned}
    c_i &= 2 + w'(x) + w'(p) + w'(g) - w(x) - w(p) - w(g) \\
    &= 2 + w'(p) + w'(g) - w(x) - w(p) \\
    &\le (2w'(x) - w'(g) - w'(p)) + w'(p) + w'(g) - w(x) - w(p) \\
    &= 2w'(x) - w(x) - w(p) \\
    &\le 2(w'(x) - w(x)).
    \end{aligned}
    $$
    
**Single stretching operation**:
    
Let $w^{(n)}(x)=(w^{(n-1)})'(x)$ and $w^{(0)}(x)=w(x)$. Assume that a stretch operation visits nodes such as $x_{1}, x_{2}, \cdots, x_{n}$ in sequence, and eventually $x_{1}$ becomes the root node. This must go through several **zig-zig** and **zig-zag** operations and at most one **zig** operation. The amortized cost of the first two operations does not exceed $3(w'(x)-w(x))$, and the amortized cost of the last operation does not exceed $3(w'(x) - w(x))+1$, so the total amortized cost does not exceed
    
    $$
    3(w^{(n)}(x_1) - w^{(0)}(x_1)) + 1 \le 3\log n + 1.
    $$
    
Therefore, the amortized complexity of a stretch operation is $O(\log n)$. Therefore, the time complexity of stretching-based insertion, query, deletion and other operations is also $O(\log n)$.
    
**in conclusion**:
    
Actual cost after $m$ stretches
    
    $$
    \begin{aligned}
    \sum_{i=1}^m t_i &= \sum_{i=1}^m \left(c_i + \varphi_{i-1} - \varphi_i \right) \\
    &= \sum_{i=1}^m c_i + \varphi_0 - \varphi_m \\
    &\le m(3\log n+1) + n\log n.
    \end{aligned}
    $$
    
Therefore, the actual time complexity of $m$ stretch operations is $O((m+n)\log n)$.

??? info "Why can the rebalancing operation of the Splay tree achieve an amortized complexity of $O(\log n)$?"
The simple idea of ​​rebalancing is to repeatedly rotate the node to make it rise until it becomes the root node. The problem with this simple idea is that for a chain tree in which all child nodes are left (right) nodes, it is equivalent to repeatedly performing the **zig** operation. Therefore, the constant term $1$ in the amortized complexity of the **zig** operation will continue to accumulate, causing the final amortized complexity to reach the $O(\log n+n)$ level. The design of the rebalancing operation of the Splay tree avoids constant accumulation in the case of continuous **zig**, so that in a complete stretch operation, at most one separate **zig** operation is performed, thus optimizing the time complexity.

## Balanced tree operation

This section discusses methods to implement common operations of balanced trees based on Splay trees. Among them, the more important thing is to find elements according to value or ranking. They can find a specific element and move it up to the root node for subsequent processing.

As an example, this section will discuss the implementation of the template topic [Ordinary Balanced Tree](https://loj.ac/problem/104).

### Find by value

As a binary search tree, you can find the corresponding node through the value $v$. You only need to compare the value to be found $v$ with the value of the current node. After finding it, move the element up to the root.

It should be noted that there are often situations where the corresponding node does not exist in the tree. For this case, record the last node visited (that is, $y$ in the implementation) and move $y$ up to the root. At this time, the value stored in node $y$ must be either the largest among all elements smaller than $v$ (i.e., the predecessor of $v$), or the smallest among all elements larger than $v$ (i.e., the successor of $v$). This is because the search process guarantees that the left subtree always stores a value less than $v$, and the right subtree always stores a value greater than $v$.

???+ example "implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:find"
    ```

This implementation allows specifying any node $z$ as the root node and searching by value within its subtree.

### Visit by ranking

Because the subtree size information is recorded, the Splay tree can also access elements through ranking, that is, find the $k$th smallest element in the tree.

Let $k$ be the remaining ranking. The specific steps are as follows:

-   If the left subtree is not empty and the remaining ranking $k$ is not greater than the size of the left subtree, then search to the left subtree;
-   Otherwise, if $k$ is not larger than the size of the left subtree plus the root, then the root node is the one to be found;
-   Otherwise, subtract $k$ by the size of the left subtree and the root, and continue searching to the right subtree;
-   Move the finally found element up to the root.

???+ example "implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:loc"
    ```

The implementation needs to ensure that rank $k$ does not exceed the tree size at root $z$.

The operation $4$ in the template question requires the return value according to the ranking. Just call this method directly and return the value.

???+ example "implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:find-kth"
    ```

### merge operation

Sometimes it is necessary to merge two Splay trees.

Assume that the root nodes of the two trees are $x$ and $y$ respectively. In order to ensure that the result is still a binary search tree, it is necessary to require that the maximum value in the $x$ tree is less than the minimum value in the $y$ tree. This condition is usually met because two trees are often split from larger subtrees.

The merge operation is as follows:

-   If one or both of $x$ and $y$ are empty trees, directly return the root node of the tree that is not empty or the empty tree;
-   Otherwise, move the minimum value in the $y$ tree up to the root $y$ through `loc(y, 1)`, then set its left node (which must be empty at this time) to $x$, update the node information, and return to the node $y$.

???+ example "implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:merge"
    ```

The splitting operation is similar. Therefore, the Splay tree can simulate the idea of ​​[irrotational treap](./treap.md#%E6%97%A0%E6%97%8B-treap) to perform various operations, including interval operations. [The section below](#sequence-operations) will introduce a more Splay tree-style interval operation processing method.

### insert operation

The insertion operation is a relatively complex process. The specific steps are as follows: (assuming the inserted value is $v$)

-   Similar to the process of searching by value, search downwards according to $v$ to the node storing $v$ or an empty node, and record the parent node $y$ in the process;
-   If there exists a node storing $v$, call it $x$ and update its information directly, otherwise create a new node $x$;
-   Perform a stretching operation and move the last node $x$ up to the root.

???+ example "implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:insert"
    ```

This implementation allows values ​​to be inserted directly into an empty tree. If you don't want to deal with an empty tree, you can insert dummy nodes in the tree in advance.

### Delete operation

The deletion operation is also a relatively complex operation. The specific steps are as follows: (assuming the deleted value is $v$)

-   First find the node where it is stored according to the value $v$ and move up to the root;
-   If there is no node to store it, return directly; (the stretching operation has been done in the previous step)
-   Otherwise, update the node information;
-   If the obtained root node is an empty node, merge the left and right subtrees as the new root node. Note that the parent nodes of the roots of the two subtrees need to be updated before merging to be empty.

???+ example "implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:remove"
    ```

### Query ranking

Just access the node directly according to the value $v$ (and move up to the root), and then return the corresponding value.

Note that when $v$ does not exist, the relationship between the root returned by method `find(rt, v)` and $v$ cannot be determined and needs to be discussed separately.

???+ example "implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:find-rank"
    ```

### Query predecessor

The precursor is defined as the largest number less than $v$. The specific steps are as follows:

-   Visit the node by value $v$ (and move up to the root);
-   If the value of the root is less than $v$, then it must be the largest one and is returned directly;
-   Otherwise, find the maximum value in the left subtree and move it up to the root.

The last step is equivalent to calling `loc(ch[rt][0], sz[ch[rt][0]])` directly, except that unnecessary judgment is omitted.

???+ example "implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:find-prev"
    ```

This implementation allows the predecessor to not exist, in which case $-1$ is returned.

### Query successor

The successor is defined as the smallest number greater than $x$. The query method is similar to the predecessor, except that the maximum value of the left subtree is replaced by the minimum value of the right subtree, that is, calling `loc(ch[rt][1], 1)`.

???+ example "implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:find-next"
    ```

### Reference implementation

At the end of this section, the reference implementation of the template problem [Ordinary Balanced Tree](https://loj.ac/problem/104) is given.

??? example "reference implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-1.cpp:full-text"
    ```

## Sequence operations

Splay trees can also be used on sequences to maintain interval information. Compared with the line segment tree, the Splay tree has larger constants, but supports more complex sequence operations, such as interval flipping, etc. As mentioned above, the Splay tree also supports splitting and merging operations, so it can simulate [irrotational treap](./treap.md#%E6%97%A0%E6%97%8B-treap) to perform interval operations, which will not be discussed further here. This section mainly discusses the implementation method of interval operation based on stretch operation.

The Splay tree built from the sequence has the following properties:

-   In-order traversal of the Splay tree is equivalent to traversal of the original sequence from left to right;
-   A node in the Splay tree represents an element of the original sequence;
-   A subtree on the Splay tree represents an interval of the original sequence.

Because of the stretching operation, the Splay subtree representing a certain interval can be quickly extracted.

As an example, this section will discuss the implementation of the template problem [Literary Balance Tree](https://loj.ac/problem/105).

### Build tree based on sequence

Before operation, the Splay tree needs to be built according to the given sequence. According to the characteristics of the Splay tree, you can directly build a chain with only the left son. The time complexity is $O(n)$.

???+ example "reference implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-2.cpp:build"
    ```

The final stretch operation updates the node information from bottom to top. For the convenience of subsequent interval operations, two sentinel nodes are added to the left and right sides of the sequence.

### range flip

Taking interval flipping as an example, you can understand the method of interval operation: (Set the interval as $[L,R]$)

-   First, move the node $L-1$ up to the root node, and then in its right subtree, move the node $R+1$ up to the root node of the right subtree;
-   At this time, assuming $x$ is the left child node of the right child node of the root node, then the subtree with $x$ as the root corresponds to the interval $[L,R]$;
-   At $x$, perform operations on the interval $[L,R]$ and mark it as lazy;
-   Pass the mark down once at $x$, and then use the stretch operation to move $x$ up to the root.

The first step required is the "access by ranking" in the previous balanced tree operation, because the label of the element is its ranking. Because it involves the management of lazy tags, its implementation is slightly different from the above.

???+ example "reference implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-2.cpp:reverse"
    ```

The stretching operation in the last step is not to ensure the correct complexity, but to update the node information. Because the stretching operation involves the left and right child nodes of node $x$, the mark at node $x$ needs to be downloaded first. Of course, only for the interval flip operation, the flip of the subinterval will not affect the ancestor nodes, so it is correct to omit this step. These two lines are retained here to illustrate the operation method under general circumstances.

### Lazy tag management

First, the auxiliary functions `lazy_reverse(x)` and `push_down(x)` are needed. The former exchanges the left and right nodes and updates the lazy mark; the latter downloads the mark.

???+ example "reference implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-2.cpp:push-down"
    ```

Then, you only need to download the tags as you go down through the nodes. The operations required by the template question are relatively simple. Only the operation of searching according to ranking (i.e. `loc`) involves downward access to nodes. Note that the tag needs to be downloaded **before** each time the function accesses a new node.

???+ example "reference implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-2.cpp:push-down-lazy"
    ```

Because all lazy markers along the path have been removed when accessing the node downwards, there is no need to deal with lazy markers when using the stretch operation to move the node up. However, the node used in the interval operation should be handled with caution: because it is also on the path of the stretch operation, but just after the operation, there may be marks that have not yet been downloaded, and it needs to be downloaded first and then the stretch operation is performed, just like what was done above.

### Reference implementation

At the end of this section, a reference implementation of the template problem [Literary Balance Tree](https://loj.ac/problem/105) is given.

??? example "reference implementation"
    ```cpp
    --8<-- "docs/ds/code/splay/splay-2.cpp:full-text"
    ```

## exercise

These questions are all bare Splay tree maintenance binary search trees:

-   [[Template]Ordinary balanced tree](https://loj.ac/problem/104)
-   [[Template]Literary Balance Tree](https://loj.ac/problem/105)
-   ["HNOI2002" turnover statistics](https://loj.ac/problem/10143)
-   [「HNOI2004」Pet Adoption Center](https://loj.ac/problem/10144)

Splay trees also appear in more complex application scenarios:

-   [「Cerc2007」robotic sort mechanical sorting](https://www.luogu.com.cn/problem/P4402)
-   ["HNOI2011" bracket repair/"JSOI2011" bracket sequence](https://www.luogu.com.cn/problem/P3215)
-   [Two forced balanced trees (trees within trees)](https://loj.ac/problem/106)
-   [BZOJ 2827 Thousands of Mountains Birds Fly Absolutely](https://hydro.ac/p/bzoj-P2827)
-   ["Lydsy1706 Monthly Competition" K minimum value query](https://hydro.ac/p/bzoj-P4923)
-   [POJ3580 SuperMemo](http://poj.org/problem?id=3580)

## References and Notes

Part of this article is quoted from the algocode algorithm blog, special thanks!
