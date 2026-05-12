author: hsfzLZH1, cesonic, AtomAlpaca, caijianhong, Persdre, aofall, CoelacanthusHex, Marcythm, shuzhouliu, Tiphereth-A

## introduce

**Weight Balanced Leafy Tree**, hereinafter referred to as **WBLT**, is a balanced tree. Compared with other balanced trees, it has the main advantages of simple implementation and small constants. It supports interval operations and is durable.

Weight Balanced Leafy Tree, as the name suggests, is a combination of Weight Balanced Tree and Leafy Tree.

Each node of Weight Balanced Tree stores the size of the subtree under this node, and the tree height is guaranteed by keeping the size relationship between the left and right subtrees within a certain range.

The original information maintained by Leafy Tree is only stored on the **leaf nodes** of the tree, while non-leaf nodes are only used to maintain child node information and maintain the shape of the data structure. The line segment tree we are familiar with is a Leafy Tree.

![](images/leafy-tree-1.svg)

The trees in this article all refer to binary Leafy Tree, that is, the number of child nodes of each node can only be $0$ or $2$. $n$ in this article refers to the number of leaf nodes of the tree. For a tree with $n$ leaf nodes, the total number of nodes is $2n-1$. Therefore, the space occupied by WBLT is $\Theta(n)$.

## Basic structure and balance maintenance

This section introduces the basic structure of WBLT, defines the concept of $\alpha$-balance of a tree, and explains how to maintain the balance of the tree through rotation or merging.

### Node information

To implement a basic WBLT, you only need to record the following information for each node:

-   `lc[x]`, `rc[x]`: left and right child nodes;
-   `sz[x]`: The number of leaf nodes in the subtree rooted at $x$.

To implement a balanced tree using WBLT, you also need to record key value-related information at each node:

-   `val[x]`: The key value at node $x$.

Because only leaf nodes actually store key values, the information stored at other nodes is merged from their child nodes to facilitate subsequent queries.

For example, a common merging method is to store the larger key value of two child nodes in the node. In this way, each node stores the maximum value of the key values ​​of all leaf nodes in the subtree with it as the root. Based on this, the node information update method is as follows:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:push-up"
    ```

Of course, if necessary, you can also implement the corresponding `push_down(x)` function.

### Helper function

In addition to basic node information maintenance, WBLT usually also needs to implement the following auxiliary functions for memory management:

-   `new_node()`: Create a new node;
-   `del_node(x)`: delete node $x$;
-   `new_leaf(v)`: Create a new leaf node with $v$ as the key value;
-   `join(x, y)`: Connect the subtree, that is, use $x$ and $y$ as the left and right child nodes respectively, and create a new node $z$;
-   `cut(x)`: Split the subtree, that is, obtain the two child nodes of node $x$ and delete node $x$.

If the WBLT implementation relies heavily on splitting and joining subtrees, more new nodes will be created and an equal number of old nodes will be released. If old useless nodes are not recycled in time, the space will no longer be linear. Here are the array implementations of these helper functions:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:helper"
    ```

After encapsulating these auxiliary functions, there is no difference between array implementation and pointer implementation in subsequent functions.

### concept of balance

For a tree, its **balance degree** at a non-leaf node $x$ can be defined as

$$
\rho(x) = \dfrac{\min\{w(T_{\operatorname{left}(x)}),w(T_{\operatorname{right}(x)})\}}{w(T_x)}.
$$

Among them, $T_x$ represents the subtree rooted at $x$, $w(\cdot)$ represents the weight of the subtree (the number of its leaf nodes), and $\operatorname{left}(x)$ and $\operatorname{right}(x)$ represent the left and right leaf nodes of $x$ respectively. In particular, $\rho(x)=1/2$ is specified at leaf nodes.

For $\alpha\in(0,1/2]$, if the balance degree of a node $x$ is $\rho(x)\ge\alpha$, the node is said to be ** $\alpha$ -balanced**. A tree is said to be $\alpha$ -balanced if every node in the tree is $\alpha$ -balanced. The set of such trees is denoted $BB[\alpha]$ . A tree is $\alpha$ -balanced if and only if it itself is $\alpha$ -balanced, and its left and right subtrees are both $\alpha$ -balanced or it is a leaf node.

The tree is $\alpha$ -balanced, with the obvious benefit that its height is $O(\log n)$. This is because every time you move one step from a leaf node to the root, the number of leaf nodes contained in the subtree will be expanded to at least $1/(1-\alpha)$ times of the original, so it can only be moved $O(\log_{\frac{1}{1-\alpha}}n) = O(\log n)$ times. This ensures that in a $\alpha$ -balanced tree, the complexity of a single query is always strictly $O(\log n)$, and the constants of the algorithm are positively related to $\log(1/(1-\alpha))$ (based on $2$). When $\alpha$ is within the reasonable range provided below, this constant is approximately $2\sim 3.5$ .

Balance maintenance of WBLT can usually be performed by rotating or merging. WBLT implemented in both ways, the complexity of single insertion, deletion and other operations is strictly $O(\log n)$. However, unlike the fixed-priority [Treap](./treap.md), the structure of WBLT is not unique. Therefore, the structures of the trees maintained by the two methods are different, although this does not affect their use. Of course, balanced maintenance can also adopt a strategy similar to [scapegoat tree](./sgt.md), using refactoring to evenly amortize the complexity of $O(\log n)$, but this will lose the advantages of WBLT persistence and interval operations, so it is not recommended.

The following describes the methods of maintaining balance through rotation and merging respectively, and implements the corresponding functions for balance maintenance and merging operations. After encapsulating these functions, there is no difference between the two methods of maintaining tree balance in the subsequent implementation of specific balanced trees. Moreover, no matter which method is used, the time complexity of a single operation of maintaining balance is $O(1)$, and the complexity of a single merge of tree $T_1$ and tree $T_2$ is $O\left(\left|\log\dfrac{w(T_1)}{w(T_2)}\right|\right)$.

???+ info "omit weight symbol"
    In order to maintain the balance of the tree, only the weight information of the subtree needs to be retained. Therefore, for convenience of expression, the following two sections discussing balance maintenance will use the notation of a tree and its weights interchangeably. For example, the weight of subtree $x$ is also represented by $x$ instead of $w(x)$. Similarly, the tree obtained by merging subtrees $x$ and $y$ is also represented by its weight, which is directly written as tree $x+y$.

### Maintenance by rotation

WBLT's rotation operation is exactly the same as [Treap's rotation operation](./treap.md#rotation), and you can adopt the same rotation strategy as Treap. Of course, rotation itself can also be regarded as a process of redistributing the weight of subtrees, so it can also be completed by splitting and connecting subtrees. The results of the two implementations are completely consistent, but the second implementation is more convenient for WBLT persistence.

???+ example "Reference code"
    === "Does not depend on connection"
        ```cpp
        --8<-- "docs/ds/code/wblt/wblt-1.cpp:rotate-not-by-joining"
        ```
    
    === "Dependent connection"
        ```cpp
        --8<-- "docs/ds/code/wblt/wblt-1.cpp:rotate-by-joining"
        ```

Suppose that after a modification operation on a certain tree, the balance of the tree is being restored from bottom to top. Now, the left and right subtrees $x$ and $y$ are no longer balanced, but they themselves are balanced. Let's assume that the right subtree $y$ is too light, that is, $y<\alpha(x+y)$. At this time, the shape of the tree is as shown in the tree on the left side of the figure.

![](images/wblt-balance.svg)

A simple balance maintenance strategy is to rotate $x$ to the root node, so that its original right child node $w$ and $y$ become the right child node of the new tree, and its original left child node $z$ becomes the left child node of the new tree. This is equivalent to moving the weight of $w$ from the left side of the original tree to its right side. If the weights of $w$ are appropriate, such an operation can restore the balance of the tree. The tree obtained in this way is shown as the tree on the right side of the figure.

However, if $w$ itself is too heavy, such an operation may move too much weight to the right subtree, thus making the left subtree in the new tree too light, that is, $z<\alpha(x+y)$. In this case, because the weights of subtree $z$ and subtree $y$ are too small, we can only consider splitting $w$ into two subtrees and connecting them to $z$ and $y$ respectively to become two subtrees of the new tree. This is equivalent to first rotating node $w$ to node $x$, and then rotating it to the root node. Likewise, we can expect that the tree obtained in this way will reach equilibrium, with the shape shown in the upper tree in the figure.

These two rotation strategies are called single rotation and double rotation respectively. The selection of single-rotation and double-rotation strategies mainly depends on the proportion of subtree $w$ relative to subtree $x$, that is, there is a threshold $\beta$, such that

-   When $w\le\beta x$, the single-spin strategy should be selected;
-   When $w>\beta x$, the double-spin strategy should be selected.

The difficulty lies in the selection of the threshold $\beta$, which requires some specific calculations. Blum and Mehlhorn proved that for the parameter [^wrong-range]

$$
\alpha\in\left(\dfrac{2}{11},1-\dfrac{\sqrt{2}}{2}\right]\approx(0.182,0.292],~\beta=\frac{1}{2-\alpha},
$$

The balance of WBLT that is imbalanced by a single insertion or deletion can be maintained through the above-mentioned strategy of combining single rotation and double rotation.

??? note "prove"
    What needs to be proved is that if the tree becomes unbalanced after a single insertion or deletion, its balance can be restored through the above strategy. Combined with the above diagram, let
    
    $$
    \rho_1 = \dfrac{y}{x+y}, ~\rho_2 = \dfrac{w}{x}, ~\rho_3 = \dfrac{v}{w}.
    $$
    
    Then, there is $\rho_1<\alpha\le\rho_2,\rho_3\le 1-\alpha$ . There is also an implicit condition here, which is about the value range of $\rho_1$:
    
    -   If the imbalance is caused by inserting a single element, then, there should be
    
        $$
        \dfrac{y}{x-1+y} \ge \alpha \implies \rho_1 \ge \dfrac{\alpha y}{y+\alpha} \ge \dfrac{\alpha}{1+\alpha}.
        $$
    -   If the imbalance is caused by deleting a single element, then, there should be
    
        $$
        \dfrac{y+1}{x+y+1} \ge \alpha \implies \rho_1 \ge \dfrac{\alpha y}{y+1-\alpha} \ge \dfrac{\alpha}{2-\alpha}.
        $$
    
    Because for $0<\alpha<1/2$ , there is always $\alpha/(2-\alpha)<\alpha/(1+\alpha)$ , so deleting an element will cause a more serious imbalance than adding an element, especially if the size of the tree is small.
    
    Next, the operation to restore balance is divided into two situations:
    
    ??? note "Scenario 1: $w$ is not overweight, that is, when $\rho_2\le\beta$, single rotation"
        First, $z$ and $w+y$ are balanced. This is because
        
        $$
        \left(1-\dfrac{\alpha}{2-\alpha}\right)\alpha+\dfrac{\alpha}{2-\alpha} \le \dfrac{w+y}{x+y} = (1-\rho_1)\rho_2+\rho_1 < (1-\alpha)\dfrac{1}{2-\alpha}+\alpha.
        $$
        
        The expression on the left side, when $\alpha\in(0,1)$, is always greater than $\alpha$, and the expression on the right side, when $\alpha\in(0,1-\sqrt{2}/2]$, is always not greater than $(1-\alpha)$.
        
        Secondly, $w$ and $y$ are balanced. Likewise, consider
        
        $$
        \dfrac{y}{w+y} = \dfrac{\rho_1}{(1-\rho_1)\rho_2+\rho_1}.
        $$
        
        On the one hand, for all $\alpha\in(0,(3-\sqrt{5})/2)$ , there are
        
        $$
        \dfrac{y}{w+y} < \dfrac{\alpha}{(1-\alpha)\alpha+\alpha} < 1-\alpha.
        $$
        
        On the other hand, for all $\alpha\in(0,1/3)$ , except the case where the element is deleted and $y=1$
        
        $$
        \rho_1 \ge \min\left\{\dfrac{\alpha}{1+\alpha},\dfrac{2\alpha}{3-\alpha}\right\} = \dfrac{2\alpha}{3-\alpha},
        $$
        
        So, there is
        
        $$
        \dfrac{y}{w+y} \ge \dfrac{\dfrac{2\alpha}{3-\alpha}}{\left(1-\dfrac{2\alpha}{3-\alpha}\right)\dfrac{1}{2-\alpha}+\dfrac{2\alpha}{3-\alpha}} > \alpha.
        $$
        
        Finally, consider the remaining case, when the element is deleted and $y=1$ is present. The most likely imbalance situation occurs when $x=\lfloor 2/\alpha\rfloor-2$ and $w=\lfloor\beta x\rfloor$. The tree can be restored to equilibrium if and only if
        
        $$
        \dfrac{1}{1+\lfloor\beta x\rfloor}\ge\alpha \iff \lfloor\beta x\rfloor\le\dfrac{1}{\alpha}-1 \iff \beta x < \dfrac{1}{\alpha} \iff x < \dfrac{2}{\alpha}-1.
        $$
        
        And this is always true. This completes the proof of the situation. Note that the proof of the last case exploits the property that weights are always integers and cannot be merged into the previous discussion.
    
    ??? note "Scenario 2: $w$ is too heavy, that is, when $\rho_2>\beta$, double rotation"
        First, $z+u$ and $v+y$ are balanced. This is because
        
        $$
        \dfrac{\alpha}{2-\alpha}+\left(1-\dfrac{\alpha}{2-\alpha}\right)\dfrac{1}{2-\alpha}\alpha < \dfrac{z+u}{x+y} = \rho_1+(1-\rho_1)\rho_2\rho_3 <\alpha+(1-\alpha)^3
        $$
        
        The expression on the left, when $\alpha\in(0,1)$, is always greater than $\alpha$, and the expression on the right, when $\alpha\in(0,(3-\sqrt{5})/2)$, is always less than $(1-\alpha)$.
        
        Then, $z$ and $u$ are balanced. This is because for $\alpha\in(0,1)$ , it always holds
        
        $$
        \alpha=\dfrac{\dfrac{1}{2-\alpha}\alpha}{1-\dfrac{1}{2-\alpha}(1-\alpha)}<\dfrac{u}{z} = \dfrac{\rho_2(1-\rho_3)}{1-\rho_2\rho_3} <\dfrac{(1-\alpha)^2}{1-(1-\alpha)\alpha} < 1-\alpha.
        $$
        
        Finally, $v$ and $y$ are balanced. Similar to other situations, consider
        
        $$
        \dfrac{y}{v+y} = \dfrac{\rho_1}{\rho_1+(1-\rho_1)\rho_2\rho_3}.
        $$
        
        On the one hand, for all $\alpha\in(0,1-\sqrt{2}/2]$ , there is
        
        $$
        \dfrac{y}{v+y} < \dfrac{\alpha}{\alpha+(1-\alpha)\dfrac{1}{2-\alpha}\alpha} \le 1-\alpha.
        $$
        
        on the other hand,
        
        $$
        \dfrac{y}{v+y} \ge \dfrac{\rho_1}{\rho_1+(1-\rho_1)(1-\alpha)^2}.
        $$
        
        The right-hand expression is not less than $\alpha$ if and only if
        
        $$
        \rho_1 \ge \dfrac{\alpha(1-\alpha)}{1+\alpha(1-\alpha)}.
        $$
        
        If the imbalance is caused by insertion, then $\rho_1\ge \alpha/(1+\alpha)$ obviously holds. Otherwise, the situation is somewhat complicated:
        
        -   when $y\ge 3$, $\rho_1\ge 3\alpha/(4-\alpha)$, and $3\alpha/(4-\alpha)\ge\alpha(1-\alpha)/(1+\alpha(1-\alpha))$ are true for all $\alpha\in[1-\sqrt{3}/2,1)$;
        -   When $y=2$, the most likely imbalance situation occurs when $x=\lfloor 3/\alpha\rfloor-3$, $w=\lfloor(1-\alpha)x\rfloor$ and $v=\lfloor(1-\alpha)w\rfloor$, at this time $v/(v+y)\ge\alpha$ is true for all $\alpha\in(3/22,1)$;
        -   When $y=1$, the most likely imbalance situation occurs when $x=\lfloor 2/\alpha\rfloor-2$, $w=\lfloor(1-\alpha)x\rfloor$ and $v=\lfloor(1-\alpha)w\rfloor$, at this time $v/(v+y)\ge\alpha$ is true for all $\alpha\in(2/11,1)$.
        
        The discussion of the last two cases also takes advantage of the fact that the weights of all nodes are integers.
    
    Combining the two situations, when $\alpha\in(2/11,1-\sqrt{2}/2]$, the aforementioned strategy of combining single rotation and double rotation can ensure the balance of the tree.
    
    From this analysis process, it can be seen that the most difficult situation to maintain balance occurs when nodes are deleted from small-scale trees. In addition to $\beta=1/(2-\alpha)$, to prove the correctness of the selection of other parameters, the above process can also be repeated, but some of the inequalities used need to be adjusted accordingly.

Subsequently, Hirai and Yamamoto completely determined the range of all feasible $(\alpha,\beta)$ through machine proofs, resulting in a rather complex two-dimensional graph:

![](images/wblt-param-range.svg)

In their article, they recommend the following strategies to maintain balance:

-   When $x>3y$, the judgment is imbalanced;
-   When $w\le 2z$, select the single-rotation strategy, otherwise, select the double-rotation strategy.

The reason is that this is the only strategy within the feasible parameter range that can be represented by simple integers, thus avoiding the efficiency loss caused by floating point operations. The strategy they recommend is equivalent to taking $(\alpha,\beta)=(1/4,2/3)$ . In practice, appropriate parameters can be selected according to specific circumstances.

The reference implementation is as follows:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:too-heavy"
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:balance"
    ```

After implementing the strategy of maintaining balance, the algorithm for merging two trees is very simple. Still assuming $x>y$ , the merge strategy is as follows:

-   If the right subtree $y$ is empty, directly return the left subtree $x$;
-   If the left and right subtrees $x$ and $y$ are already balanced, that is, $y\ge\alpha(x+y)$, the two subtrees are directly connected;
-   Otherwise, merge $x$'s right subtree $w$ and $y$, connect the left subtree $z$ with their merged results, and adjust the balance of the new tree.

The reference implementation is as follows:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:merge-by-balancing"
    ```

It can be proved that this can maintain the balance of the merged tree, and the complexity of this operation is $O(|\log(x/y)|)$.

??? note "Proof of balance and complexity"
    You only need to consider the case where $y$ is too light, that is, $y<\alpha(x+y)$. At this time, merge $w$ and $y$ first, and then connect $z$ and $w+y$. What needs to be proved is that as long as the balance of the tree is adjusted at the root of the tree, the balance of the tree can be guaranteed. Assume that the left and right subtrees of tree $w+y$ are $c$ and $d$ respectively, and the left and right subtrees of $c$ are $a$ and $b$ respectively. Adjusting the balance at the root of the tree can be divided into three situations:
    
    ??? note "Scenario 1: $z$ and $w+y$ are already balanced and no further adjustment is needed, i.e. $z\ge\alpha(x+y)$"
        According to the definition of balance, subtrees $z$ and $w+y$ are both balanced, and they are balanced with each other, then the entire tree is also balanced.
    
    ??? note "Scenario 2: $z$ is too light and $c$ is not too heavy. The balance can be restored through single rotation, that is, $z<\alpha(x+y)$ and $c\le\beta(w+y)$"
        At this time, because $z$ and $w$ are balanced, but $y$ is too light compared to $x = z+w$, so the weight of subtree $z$ satisfies
        
        $$
        \alpha(1-\alpha)(x+y) <  \alpha(z+w) \le z \le \alpha(x+y) .
        $$
        
        The weight of $c$ satisfies
        
        $$
        \alpha(w+y) \le c \le \beta(w+y).
        $$
        
        Thus, $z$ and $c$ balance each other as long as
        
        $$
        \dfrac{\alpha}{1-\alpha}<\dfrac{1-\alpha}{\alpha}\alpha<\dfrac{c}{z}=\dfrac{w+y}{z}\dfrac{c}{w+y} < \dfrac{1-\alpha(1-\alpha)}{\alpha(1-\alpha)}\beta\le\dfrac{1-\alpha}{\alpha},
        $$
        
        This requires
        
        $$
        \beta\le \dfrac{(1-\alpha)^2}{1-\alpha(1-\alpha)}.
        $$
        
        and $z+c$ and $d$ balance each other, as long as
        
        $$
        \alpha\le (1-\beta)(1-\alpha)\le \dfrac{d}{w+y}\dfrac{w+y}{x+y}  = \dfrac{d}{x+y} < \dfrac{d}{c+d} \le 1-\alpha,
        $$
        
        This requires
        
        $$
        \beta \le \dfrac{1-2\alpha}{1-\alpha}.
        $$
    
    ??? note "Scenario 3: $z$ is too light and $c$ is too heavy. The balance can be restored through double rotation, that is, $z<\alpha(x+y)$ and $c>\beta(w+y)$"
        Similar to situation 2, there are
        
        $$
        \begin{aligned}
        \alpha(1-\alpha)(x+y) < z &\le \alpha(x+y),\\
        \beta(w+y)<c &\le (1-\alpha)(w+y),\\
        \alpha c\le a,b &\le (1-\alpha)c.
        \end{aligned}
        $$
        
        Thus, $z$ and $a$ balance each other as long as
        
        $$
        \dfrac{\alpha}{1-\alpha}\le\dfrac{1-\alpha}{\alpha}\beta\alpha\le\dfrac{a}{z} = \dfrac{w+y}{z}\dfrac{a}{c+d} < \dfrac{1-\alpha(1-\alpha)}{\alpha(1-\alpha)}(1-\alpha)^2,
        $$
        
        This requires
        
        $$
        \beta\ge\dfrac{\alpha}{(1-\alpha)^2}.
        $$
        
        Second, $b$ and $d$ balance each other, as long as
        
        $$
        \dfrac{\alpha}{1-\alpha}\le\dfrac{\beta}{1-\beta}\alpha \le \dfrac{b}{d} = \dfrac{c}{d}\dfrac{b}{c} \le \dfrac{1-\alpha}{\alpha}(1-\alpha) < \dfrac{1-\alpha}{\alpha},
        $$
        
        This requires
        
        $$
        \beta\ge\dfrac{1}{2-\alpha}.
        $$
        
        Finally, $z+a$ and $b+d$ balance each other as long as
        
        $$
        \alpha<(1-\alpha)(1-(1-\alpha)^2)\le\frac{b+d}{x+y} = \dfrac{w+y}{x+y}\dfrac{b+d}{w+y} < (1-\alpha(1-\alpha))(1-\beta\alpha) \le 1-\alpha,
        $$
        
        This requires
        
        $$
        \beta\ge\dfrac{\alpha}{1-\alpha+\alpha^2}.
        $$
    
    Considering the three situations, as long as
    
    $$
    0<\alpha\le 1-\dfrac{\sqrt{2}}{2},~\dfrac{1}{2-\alpha}\le\beta\le\dfrac{1-2\alpha}{1-\alpha},
    $$
    
    This can ensure that the merged tree can be adjusted to balance using the strategy of combining single rotation and double rotation. This obviously includes the parameter range given in the text.
    
    Finally, let’s briefly explain why the complexity of this algorithm is $O(|\log(x/y)|)$. During the merge process, if $y$ is too light compared to $x$, try to merge with the right subtree of $x$. This process continues until the subtree rooted at a descendant node of $x$ is balanced with $y$. Because each time you deepen one level, the weight of the subtree changes to at least the original $(1-\alpha)$, so it only takes at most $\log_{\frac{1}{1-\alpha}}(x/y)$ iterations to find a subtree that is balanced with $y$. Therefore, this merge algorithm calls the balancing algorithm [^merge-complexity-cmp] $O(\log n)$ times, and the complexity is $O(\log n)$.
    
    Although it is not obvious, this argument relies on the conclusion that in the process of continuously taking the right subtree, $y$ will not change from being too light compared to the subtree on the left to being too heavy compared to it before and after one iteration. This is because the weight range of subtrees that can be balanced with $y$ is between $\alpha y/(1-\alpha)$ and $(1-\alpha)y/\alpha$. Therefore, if $y$ is too light to $y$ is too heavy in one iteration, the weight of the subtree of $x$ will be reduced to at least $\alpha^2/(1-\alpha)^2$ times of the original during that iteration. However, in a single iteration, the subtree weight can only be reduced to at most $\alpha$ times of the original, but in the range of $\alpha$ mentioned above, $\alpha>\alpha^2/(1-\alpha)^2$ . This shows that the presupposed situation is impossible. After a certain iteration, there will definitely be a situation where a certain subtree of $y$ and $x$ is balanced.

### Maintained by merging

Merging two subtrees means to ensure that the key value of the left subtree is always not greater than the key value of the right subtree, then establish a new tree so that the information of all leaf nodes is exactly the sum of the information of the left and right subtree leaf nodes, and ensure the balance of the tree.

For this purpose, there is the following strategy [^more-join]: (Still assuming $x>y$ )

-   If the right subtree $y$ is empty, directly return the left subtree $x$;
-   If the left and right subtrees $x$ and $y$ are already balanced, that is, $y\ge\alpha(x+y)$, the two subtrees are directly connected;
-   Otherwise, the right subtree $y$ is too light, but if $x$'s left subtree $z$ and $w+y$ can be balanced, that is, $z\ge\alpha(x+y)$, merge $w$ and $y$ first, and then merge $z$ and $w+y$;
-   Otherwise, both $z$ and $y$ are too light. At this time, you need to first merge $z$ and $w$'s left subtree $u$, then merge $w$'s right subtree $v$ and $y$, and then merge the results of the two merges into a new tree.

Comparing this strategy with the previous balancing strategy, we can see that the combination of nodes in the latter two cases is similar to the results of single rotation and double rotation in the aforementioned balancing strategy, except that the connections of the subtrees are replaced by merging.

It can be proved that when

$$
0<\alpha \le 1-\dfrac{\sqrt{2}}{2}\approx 0.292
$$

When , the tree obtained in this way is always balanced, and the complexity of this operation is $O(|\log(x/y)|)$. In other words, the cost of merging two trees has nothing to do with the absolute sizes of the two trees, but only with their relative sizes.

??? note "Proof of balance and complexity"
    Suppose that when merging two subtrees with weights $x$ and $y$ respectively, the number of times that the two subtrees need to be directly connected is $\tau(x,y)$. Strictly speaking, we need to prove that when $0<\alpha\le 1-\sqrt{2}/2$ , there is a constant $C>0$ , and for any $x>y>0$ , there is
    
    $$
    \tau(x,y) \le 1+C\log^+\dfrac{\alpha x}{(1-\alpha)^2y},
    $$
    
    Among them, $\log^+ x = \max\{0,\log x\}$ ; and, for every $x/y\le(1-\alpha)/\alpha$ , there is $\tau(x,y)=1$ . In fact, the constant in the formula can be taken as
    
    $$
    C = -\dfrac{2}{\log(1-\alpha)}.
    $$
    
    This shows that the complexity of the merging algorithm is $O(|\log(x/y)|)$.
    
    In order to prove that the tree obtained by the merging algorithm is always balanced and the above complexity expression holds, induction needs to be used. For all grid points $(x,y)\in\mathbf N^2_+$ in the first quadrant, the dictionary order of $(x+y,|x-y|)$ can be assigned, which is obviously a good order on the set, and can be summarized along this order. The starting point of induction is $(x,y)=(1,1)$. At this time, both subtrees have only one leaf node. The subtree obtained by direct connection must be balanced, and $\tau(x,y)=1$ conforms to the above formula. Suppose below that the induction proceeds to $(x,y)$ and the conclusion holds for all points before $(x,y)$. This is divided into three situations:
    
    ??? note "Scenario 1: Trees $x$ and $y$ are balanced, that is, $y\ge\alpha(x+y)$"
        At this time, the tree obtained by direct connection is also balanced, and the tree connection algorithm is only called once, so there is $\tau(x,y)=1$.
    
    ??? note "Case 2: Tree $y$ is too light, but $z$ is not too light, that is, $y<\alpha(x+y)\le z$"
        At this point, $w$ and $y$ are merged first, and then $z$ and $w+y$ are merged, so
        
        $$
        \tau(x,y) = \tau(w,y) + \tau(z,w+y).
        $$
        
        By the inductive assumption, subtree $w+y$ is already balanced. For the second step of merging, it can actually be directly proved that $z$ and $w+y$ are balanced:
        
        $$
        \alpha \le \dfrac{z}{z+(w+y)} = \dfrac{z}{x+y} < \dfrac{z}{z+w} \le 1-\alpha.
        $$
        
        Therefore, merging $z$ and $w+y$ is actually directly connecting the two subtrees, with $\tau(z,w+y) = 1$ . Therefore, the final tree obtained is also balanced.
        
        Now estimate the size of $\tau(w,y)$. Because $y>(\alpha/(1-\alpha))x$ and $\alpha x\le w\le(1-\alpha)x$ , so, after scaling, we can see
        
        $$
        \dfrac{\alpha}{1-\alpha}<1-\alpha=\dfrac{\alpha x}{(\alpha/(1-\alpha))x}< \dfrac{w}{y} \le \dfrac{(1-\alpha)x}{y}.
        $$
        
        This shows that $w$ and $y$ are unbalanced and only appear when $w>y$ is used, so there are
        
        $$
        \begin{aligned}
        \tau(w,y) &\le 1+C\log^+\dfrac{\alpha w}{(1-\alpha)^2y} \le 1+C\log^+\dfrac{\alpha x}{(1-\alpha)y} \\
        &= 1 + C\log(1-\alpha) + C\log^+\dfrac{\alpha x}{(1-\alpha)^2y}.
        \end{aligned}
        $$
        
        The equation in the last step holds because $x/y>(1-\alpha)/\alpha$ .
        
        Therefore, there are
        
        $$
        \tau(x,y) \le 2 + C\log(1-\alpha) + C\log^+\dfrac{\alpha x}{(1-\alpha)^2y}.
        $$
    
    ??? note "Case 3: Both trees $y$ and $z$ are too light, that is, $y,z<\alpha(x+y)$"
        At this time, $z$ and $u$ are merged first, then $v$ and $y$ are merged, and finally $z+u$ and $v+y$ are merged. therefore,
        
        $$
        \tau(x,y) = \tau(z,u) + \tau(v,y) + \tau(z+u,v+y).
        $$
        
        Similar to the previous situation, the weight ratio of the two subtrees at each step of merging can be estimated.
        
        Because $z,y<\alpha(x+y)$ , so $w>(1-2\alpha)(x+y)$ . At the same time, using equilibrium conditions, there is $\alpha\le z/x,w/x,u/w,v/w\le 1-\alpha$. This shows
        
        $$
        \begin{aligned}
        \dfrac{\alpha}{1-\alpha}<\dfrac{\alpha}{1-\alpha}\frac{1}{1-\alpha}\le \dfrac{z}{u} &= \dfrac{z}{w}\dfrac{w}{u} < \dfrac{\alpha}{1-2\alpha}\dfrac{1}{\alpha} \le \dfrac{1-\alpha}{\alpha},\\
        \dfrac{\alpha}{1-\alpha}\le\alpha\dfrac{1-2\alpha}{\alpha}< \dfrac{v}{y} &= \dfrac{v}{w}\dfrac{w}{y} \le (1-\alpha)\dfrac{(1-\alpha)x}{y} = (1-\alpha)^2\dfrac{x}{y}.
        \end{aligned}
        $$
        
        For the last term, there are
        
        $$
        \dfrac{z+u}{v+y} = \dfrac{x+y}{v+y}-1 = \dfrac{x+y}{y}\dfrac{y}{v+y} - 1 < (1-\alpha)\left(\dfrac{x}{y}+1\right)-1 < (1-\alpha)\dfrac{x}{y}.
        $$
        
        On the other hand, there are
        
        $$
        \dfrac{z+u}{v+y} = \dfrac{x+y}{v+y}-1 \ge \dfrac{x+y}{(1-\alpha)^2x+y}-1 > \dfrac{1}{(1-\alpha)^3+\alpha}-1 > \dfrac{\alpha}{1-\alpha}.
        $$
        
        Using these inequalities, it can be shown that the final tree must be balanced. Using the inductive hypothesis, it can be seen that merging $z$ and $u$, and merging $v$ and $y$ can ensure that the resulting tree is balanced. Moreover, the first step of merging $z$ and $u$ is actually directly connecting the two trees. For the merger of tree $z+u$ and tree $v+y$, there are two sub-cases:
        
        -   If $z+u\le v+y$ , then their weight ratio is strictly greater than $\alpha/(1-\alpha)$ , so they can be connected directly, and the result is balanced;
        -   Otherwise, their weight ratio must be strictly less than $x/y$, but $(z+u)+(v+y)=x+y$, so $|(z+u)-(v+y)|<|x-y|$, judged by the lexicographic order given above. In this case, the inductive hypothesis can also be applied, and the result is also balanced.
        
        Further application of the inductive hypothesis shows that:
        
        $$
        \begin{aligned}
        \tau(z,u) &= 1,\\
        \tau(v,y) &\le 1+C\log^+\dfrac{\alpha x}{y},\\
        \tau(z+u,v+y) &\le 1 + C\log^+\dfrac{\alpha x}{(1-\alpha)y}.
        \end{aligned}
        $$
        
        Direct addition of three inequalities will cause the coefficient in front of the logarithmic term to become $2C$, making induction impossible. Therefore, more detailed estimation is needed here.
        
        When $\max\{v/y,(z+u)/(v+y)\}\le(1-\alpha)/\alpha$, one of $\tau(v,y)$ and $\tau(z+u,v+y)$ must be $1$, so, there is
        
        $$
        \begin{aligned}
        \tau(v,y) + \tau(z+u,v+y) &\le 2 + C\log^+\dfrac{\alpha x}{(1-\alpha)y}\\
        &= 2 + C\log(1-\alpha) + C\log^+\dfrac{\alpha x}{(1-\alpha)^2y}.
        \end{aligned}
        $$
        
        Otherwise, there should be
        
        $$
        \begin{aligned}
        \tau(v,y) + \tau(z+u,v+y) 
        &\le 2 + C\log^+\dfrac{\alpha v}{(1-\alpha)^2y} + C\log^+\dfrac{\alpha(z+u)}{(1-\alpha)^2(v+y)}\\
        &= 2 + C\log\dfrac{\alpha}{(1-\alpha)^2} + C\log^+\dfrac{\alpha v(z+u)}{(1-\alpha)^2y(v+y)}.
        \end{aligned}
        $$
        
        For $0<\alpha\le 1-\sqrt{2}/2$ , there is
        
        $$
        \dfrac{\alpha}{(1-\alpha)^2} < 1-\alpha.
        $$
        
        Moreover, there are
        
        $$
        \begin{aligned}
        \dfrac{v(z+u)}{y(v+y)} &= \left(\dfrac{v+y}{y}-1\right)\left(\dfrac{x+y}{y}\dfrac{y}{v+y} - 1\right) \\
        &= \dfrac{x+y}{y} + 1 -\dfrac{x+y}{y}\dfrac{y}{v+y}-\dfrac{v+y}{y} < \dfrac{x}{y}.
        \end{aligned}
        $$
        
        This shows that for the latter situation, there are also
        
        $$
        \tau(v,y) + \tau(z+u,v+y) < 2 + C\log(1-\alpha) + C\log^+\dfrac{\alpha x}{(1-\alpha)^2y}.
        $$
        
        The overall merging complexity is
        
        $$
        \tau(x,y) \le 3 + C\log(1-\alpha) + C\log^+\dfrac{\alpha x}{(1-\alpha)^2y}.
        $$
    
    Taking all circumstances into account, there are
    
    $$
    \tau(x,y) \le 3 + C\log(1-\alpha) + C\log^+\dfrac{\alpha x}{(1-\alpha)^2y}.
    $$
    
    Therefore, as long as $2+C\log(1-\alpha)\le 0$ is taken, the complexity induction can be completed. An obvious choice is
    
    $$
    C = -\dfrac{2}{\log(1-\alpha)}.
    $$
    
    This constant shows that when two trees are merged, the number of direct subtree connections will roughly not exceed twice the difference in tree height.

The reference implementation is as follows:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:merge"
    ```

Using this merging strategy, it is also easy to achieve tree balance maintenance: when there is an imbalance, just merge the left and right subtrees directly.

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:balance-by-merging"
    ```

Because the sizes of the two trees that need to be rebalanced are always nearly balanced, the complexity of maintaining balance is $O(1)$.

## Basic operations of balanced trees

Using the functions implemented previously, WBLT can support all basic operations of balanced trees. This section takes resettable as an example to discuss WBLT's method of implementing balanced trees.

### make achievements

The tree building operation is very similar to the line segment tree. You only need to recurse down the two-partition interval until the interval length is $1$, put the information to be maintained on the leaf node, and merge the interval information during backtracking.

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-2.cpp:build"
    ```

The time complexity is $O(n)$.

### Insertion and deletion

For the insertion operation, you need to recurse downward from the root node until you find the leaf node with a weight greater than or equal to the minimum weight of the inserted element, and then create two new nodes, one of which is used to store the newly inserted value, and the other is used as the new parent of the two leaves to replace the position of the minimum leaf node, and then connect the two leaves to this parent. When backtracking, the balance of the tree needs to be maintained.

![](./images/wblt-insert-delete.svg)

As shown in the figure, the element with value $4$ is to be inserted into the tree on the left. First find the leaf node with value $5$, then create new leaf node $4$ and non-leaf node $\text{d}$, and connect $4$ and $5$ to $\text{d}$. This gives us the tree on the right.

For deletion, consider the reverse process of the above process. That is, find a leaf node whose weight is equal to the value to be deleted, delete it and its parent node, and replace the father's position with another son of its father. When backtracking, it is also necessary to maintain the balance of the tree.

The reference implementation is as follows:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:insert-remove"
    ```

Pay attention to the handling of empty trees. If you don't want to deal with an empty tree, you can insert the $\infty$ element into the tree in advance.

The time complexity of both operations is $O(\log n)$.

### Query ranking

Because the shape of WBLT is very similar to the line segment tree, the query ranking can use a bisection method similar to the line segment tree: if the maximum value of the left subtree is greater than or equal to the value to be checked, jump to the left subnode; otherwise, jump to the right subnode, and the answer is added with the weight of the left subtree.

The reference implementation is as follows:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:rank"
    ```

The time complexity is $O(\log n)$.

### Query based on ranking

The idea of ​​bisection on the line segment tree is still used, but here the comparison is the weight of the nodes.

The reference implementation is as follows:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:kth-element"
    ```

The time complexity is $O(\log n)$.

### Find predecessors and successors

The above two functions can be combined.

The reference implementation is as follows:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:prev-next"
    ```

If you want to implement it directly, you need to note that nodes with the same key value may be stored in multiple leaf nodes.

### Split operation

The split of WBLT is similar to [irrotational Treap](./treap.md#split), which recursively splits the left or right subtree downwards based on the size or weight of the subtree. The difference is that WBLT needs to merge the split subtrees to maintain the balance of the final split tree.

The reference implementation of splitting based on subtree size is as follows:

???+ example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-2.cpp:split"
    ```

The time complexity is $O(\log n)$.

??? note "Proof of complexity"
    The number of downward recursive levels obviously does not exceed the tree height, which is $O(\log n)$. What needs to be proved is that the complexity of merging the split subtrees on the left and right sides is $O(\log n)$. We might as well consider only the subtree on the left side because the right side is symmetric. Assume that the subtrees split from the left are $T_1,T_2,\cdots,T_\ell$ from bottom to top, and the number of these subtrees is $\ell\in O(\log n)$. The merging process can be described as starting from $T'_1=T_1$, merging $T'_{i-1}$ and $T_i$ to obtain $T'_i$, and recursively merging all subtrees. The total complexity of the merger can be expressed as
    
    $$
    \sum_{i=2}^\ell \tau(T_i,T'_{i-1}),
    $$
    
    Among them, $\tau(T_i,T'_{i-1})$ is the complexity of combining $T_i$ and $T'_{i-1}$.
    
    If there is always $w(T_i)\ge w(T'_{i-1})$ , then according to the complexity expression of merging two subtrees, there is
    
    $$
    \tau(T_i,T'_{i-1}) \in O\left(\log\dfrac{w(T_i)}{w(T'_{i-1})}\right) \subseteq O\left(\log\dfrac{w(T'_i)}{w(T'_{i-1})}\right).
    $$
    
    Because the constants in these large $O$ notations are consistent, they can be added directly and the split terms cancel.
    
    However, it should be noted that $w(T_i)\ge w(T'_{i-1})$ is not always true, because $T'_{i-1}$ is split from the right subtree corresponding to $T_i$ in the original tree, and this right subtree may be larger than the left subtree $T_i$. Nonetheless, even if $T'_{i-1}$ is larger than $T_i$, as part of the right subtree, the weight $w(T'_{i-1})$ will not exceed $w(T_i)$ by more than a factor of $(1-\alpha)/\alpha$, which means that at this time, $T'_{i-1}$ and $T_i$ must be balanced, and the complexity of the merger is $O(1)$.
    
    Summarizing these two cases together, the complexity of a single merge can be written as
    
    $$
    \tau(T_i,T'_{i-1}) \in O\left(\log\dfrac{w(T'_i)}{w(T'_{i-1})}\right) + O(1).
    $$
    
    From this, the total complexity of the merge is
    
    $$
    O\left(\sum_{i=2}^\ell\left( 1+\log\dfrac{w(T'_i)}{w(T'_{i-1})}\right) \right) \subseteq O(\ell+\log w(T'_\ell)) \subseteq O(\log n).
    $$
    
    This also shows that the total complexity of the splitting algorithm is $O(\log n)$.

## Reference implementation

This article introduces how to use WBLT to complete the basic operations of balanced trees. The following is [Common Balanced Tree Template] (https://loj.ac/p/104) implemented using WBLT.

??? example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-1.cpp:full-text"
    ```

By using merging and splitting, a literary and artistic balanced tree can also be realized. The following is the [Literary Balanced Tree Template] (https://loj.ac/p/105) implemented using WBLT, which needs to pass down the lazy mark when accessing the node downwards.

??? example "Reference code"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt-2.cpp:full-text"
    ```

Note that WBLT requires twice the space; when splitting and merging are involved, you need to pay attention to garbage collection and recycle useless nodes in time, otherwise the space is not linear.

## References and Notes

-   [Weight-balanced tree - Wikipedia](https://en.wikipedia.org/wiki/Weight-balanced_tree)
-   Nievergelt, J.; Reingold, E. M. (1973). "Binary Search Trees of Bounded Balance". SIAM Journal on Computing. 2: 33–43.
-   Blum, Norbert; Mehlhorn, Kurt (1980). "On the average number of rebalancing operations in weight-balanced trees". Theoretical Computer Science. 11 (3): 303–320.
-   Hirai, Y.; Yamamoto, K. (2011). "Balancing weight-balanced trees". Journal of Functional Programming. 21 (3): 287.
-   Blelloch, Guy E.; Ferizovic, Daniel; Sun, Yihan (2016), "Just Join for Parallel Ordered Sets", Symposium on Parallel Algorithms and Architectures, Proc. of 28th ACM Symp. Parallel Algorithms and Architectures (SPAA 2016), ACM, pp. 253–264.
-   Straka, Milan. (2011). "Adams’Trees Revisited: Correctness Proof and Efficient Implementation." International Symposium on Trends in Functional Programming. Berlin, Heidelberg: Springer Berlin Heidelberg.

[^wrong-range]: The parameter range $\alpha < 1-\dfrac{\sqrt{2}}{2},~\beta=\dfrac{1-2\alpha}{1-\alpha}$ given in Nievergelt and Reingold's original paper is wrong. Hirai and Yamamoto's article provides corresponding counterexamples. The problem mainly occurs in some very small trees, which leads to the failure of the entire inductive proof. Of course, in actual algorithm competitions, it is difficult to create data that can eliminate these wrong parameters, so it may not have much impact in practice.

[^merge-complexity-cmp]: Because a single balancing operation is equivalent to connecting subtrees at most twice, and when the last two subtrees have been balanced, the algorithm for connecting subtrees needs to be called once. Therefore, if calculated by the number of times the algorithm for connecting subtrees is called, the algorithm constants of the merging operation based on balancing and the balancing operation of direct merging below are consistent.

[^more-join]: It can be seen from the later proof that in the third case, $z$ and $w+y$ are always balanced; in the fourth case, $z$ and $u$ are always balanced. They can all be connected directly without merging.
