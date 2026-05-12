author: Ir1d, Marcythm, LucienShui, Anguei, H-J-Granger, CornWorld, ttzc

This article introduces the concept and basic properties of tree centroids.

## Definition

If removing a node $v$ from tree $T$ results in a graph $T\setminus\{v\}$ where each connected component has size no more than half of the original tree's node count, then node $v$ is called the **centroid** of the entire tree. The size of the largest connected component obtained after removing a node is also called the **weight** of that node. Using this concept, the definition of centroid can be restated as nodes whose weight does not exceed half of the tree's node count.

???+ info ""Subtree""
    This article may involve rooted trees, unrooted trees, and trees obtained by rerooting a rooted tree at a non-root node. To avoid confusion, we use $T$ to denote an unrooted tree, and $T^{(v)}$ to denote a rooted tree with node $v$ as the root. The "subtrees" mentioned in this article all refer to **rooted trees**, where a node and all its descendants form a tree. In rooted tree $T^{(v)}$, the subtree corresponding to node $u$ is denoted as $T^{(v)}_u$. By this definition, the entire tree is naturally included. If we want to explicitly exclude the entire tree itself, we call it a "proper subtree".
    
    "Subtrees" in unrooted trees usually refer to a connected subgraph. When discussing centroids, some authors use "subtree" specifically to refer to the maximal connected subgraph that does not contain a certain node, or specifically to refer to one of the two connected components obtained by removing an edge. It is easy to verify that the "subtrees" obtained by these two methods are consistent and do not include the tree itself. Since this is inconsistent with the subtree set of rooted trees, this article will avoid using the "subtree" concept for unrooted trees.
    
    When actually finding centroids or handling certain problems, there is usually a default root. At this time, when removing a non-root node $v$, among the connected components obtained, besides the subtrees corresponding to its child nodes, there is also an "upward" subtree. At this time, let the parent node of node $v$ be $u$, then this "upward" subtree is $T_u^{(v)}$. When mentioning such subgraphs in this article, we will explicitly call them "upward" subtrees. Unless otherwise specified, the subtrees mentioned in this article do not include such "upward" subtrees.

Note that these connected components are also unrooted trees. By removing the centroid of a tree, a tree becomes several trees each at most half the size of the original tree. This property of centroids makes it possible to apply divide-and-conquer thinking to solve problems on trees. This is [Tree Centroid Decomposition](./tree-divide.md#centroid-decomposition), also called centroid decomposition.

## Properties

This section discusses the properties of centroids. First, the centroid of a tree has the following equivalent definitions:

???+ note "Equivalent Definitions"
    A node $v$ in tree $T$ is its centroid if and only if any one of the following holds:
    
    === "Unrooted Tree Version"
        1.  After removing node $v$ from the tree, the size of each connected component in the resulting graph $T\setminus\{v\}$ does not exceed half of the original tree's node count.
        2.  Among the sizes of the largest connected components obtained after removing each node, removing node $v$ gives the minimum value.
        3.  Among the sums of distances from all nodes to some node, the sum of distances to node $v$ is minimum.
    
    === "Rooted Tree Version"
        1.  When the tree is rooted at node $v$, the size of any proper subtree does not exceed half of the original tree's node count.
        2.  Among the sizes of the largest proper subtrees when rooted at each node, rooting at node $v$ gives the minimum value.
        3.  Among the sums of depths of all nodes when rooted at each node, rooting at node $v$ gives the minimum depth sum.

??? note "Proof"
    First, introduce some notation. The rooted and unrooted tree versions are clearly equivalent. Define $W(x)=\max_{u\sim x}|T_u^{(x)|$, where $u\sim x$ means $u$ and $x$ are adjacent. Define $S(x)=\sum_{u\in T}d(u,x)$, where $d(u,x)$ represents the distance between node $u$ and $x$. Then Definition 1 is equivalent to requiring $W(v)\le |T|/2$, Definition 2 is equivalent to requiring $v\in\arg\min_{x\in T}W(x)$, and Definition 3 is equivalent to requiring $v\in\arg\min_{x\in T}S(x)$. We need to prove these three conditions are equivalent.
    
    Understand $S(x)$ as the sum of node depths when rooted at $x$, and consider its change when the tree root changes from node $v$ to an adjacent node $u$. Note that after removing edge $(v,u)$ in the tree, the two connected components obtained are subtree $T_v^{(u)}$ and $T_u^{(v)}$. Before and after rerooting, each node in subtree $T_v^{(u)}$ has its depth increased by 1, and each node in subtree $T_u^{(v)}$ has its depth decreased by 1. Therefore, the change in depth sum is:
    
    $$
    \Delta S_{v\to u} = S(u) - S(v) = |T_v^{(u)}| - |T_u^{(v)}| = |T| - 2|T_u^{(v)}|.
    $$
    
    So the condition in Definition 1 is equivalent to requiring $\Delta S_{v\to u}\le 0$ for all adjacent nodes $u$ of $v$, that is, $v$ is a local minimum point of $S(x)$.
    
    Now let $v$ be a (one of the) minimum points of $S(x)$ (i.e., Definition 3), which must exist and is definitely a local minimum point. Consider the rooted tree $T^{(v)}$ with $v$ as root. Let $u \neq v$ be a non-root node, and on the directed path from $v$ to $u$, let the next node after $v$ be $y$ (which could be $u$ itself), and the previous node of $u$ be $x$ (which could be $v$ itself). Then, since $T_u^{(x)}\subseteq T_y^{(v)}$, we have:
    
    $$
    2|T_x^{(u)}| = 2|T| - 2|T_u^{(x)}| \ge 2|T| - 2|T_y^{(v)}| \ge |T|.
    $$
    
    Here, the last step uses the fact that $v$ is a local minimum point of $S(x)$. At this point, there are two cases:
    
    -   There exists a node $u$ such that $2|T_x^{(u)}|=|T|$ holds. In this case, according to the above inequality, it must be that $(x,u)=(v,y)$, and $|T_v^{(u)}|=|T_{u}^{(v)}| = |T|/2$. That is, there can be only one node $u$ that makes the equality hold, and it must be adjacent to $v$. At this time, for all other nodes $u'\neq u,v$, there exists $x'\sim u'$ such that $|T_{x'}^{(u')}| > |T|/2$ holds. The set of nodes satisfying condition 1 is $\{v,u\}$.
        
        Note that when removing any node, the sum of sizes of connected components is always $|T|-1$. So as long as one connected component has size at least $|T|/2$, it must be the largest connected component. Therefore, in this case, $W(v)=W(u)=|T|/2$, and for all $u'\neq u,v$, we have $W(u') > |T|/2$. Thus, the set of nodes satisfying condition 2 is $\arg\min W(x) = \{v,u\}$.
        
        Also, since $\Delta S_{v\to u} = 0$, we have $S(v)=S(u)$. Since $v$ is a minimum point, $u$ must also be a minimum point. And for $u'\neq u,v$, there exists $x'\sim u'$ such that $|T_{x'}^{(u')}| > |T|/2$, which violates the condition that a local minimum point must satisfy. Therefore, $u'$ is definitely not a minimum point. Thus, the set of nodes satisfying condition 3 is $\arg\min S(x) = \{v,u\}$.
    -   There is no node $u$ such that $2|T_x^{(u)}|=|T|$ holds. In this case, for all nodes $u\neq v$, there exists a node $x\sim u$ such that $|T_x^{(u)}| > |T|/2$. Repeating the previous analysis, for all nodes $u\neq v$, we have $W(u) > |T|/2$, and $u$ is not a local minimum point of $S(x)$. Therefore, the only node satisfying condition 1 is $v$, and $\arg\min W(x)=\arg\min S(x) = \{v\}$.
    
    In either case, the sets satisfying the three conditions are the same. This proves the three definitions are equivalent.

In addition to these equivalent definitions, centroids of trees have the following common properties:

???+ note "Properties"
    1.  If the centroid of a tree is not unique, there are exactly two. These two centroids are adjacent. Moreover, after removing the edge connecting them, the tree becomes two connected components of equal size.
    2.  Adding or removing a leaf node to a tree causes its centroid to move at most one edge.
    3.  Connecting two trees with an edge to form a new tree, then the centroid of the new tree lies on the path connecting the centroids of the two original trees.
    4.  The centroid of a rooted tree must lie on the heavy path where the root is located. The centroid of a tree must be an ancestor of the centroid of the subtree of the root's heavy child.

??? note "Proof"
    Property 1 can be obtained from the proof of the equivalent definitions of centroid.
    
    Property 2 only needs to consider the case of adding one leaf node. This is further divided into two cases:
    
    -   Tree $T$ has only one centroid $v$. Let $x$ be the newly added leaf node, and in the graph $T\cup\{x\}\setminus\{v\}$ obtained by removing node $v$ from the new tree, the connected component containing $x$ is $B\cup\{x\}$. Since $v$ is the only centroid of tree $T$, we have $2|B| < |T|$, i.e., $2|B|+1\le |T|$. Furthermore, we have:
        
        $$
        2|B\cup\{x\}| = 2(|B|+1) \le |T| + 1 = |T\cup\{x\}|.
        $$
        
        Therefore, $v$ is still the centroid of the new tree $T\cup\{x\}$. Even if the centroid of the new tree is not unique, it must be adjacent to $v$. Thus, the centroid moves at most one edge.
    -   Tree $T$ has two centroids $u,v$. At this time, removing $(u,v)$ yields two connected components $T_u^{(v)}$ and $T_v^{(u)}$ of equal size, both being $|T|/2$. Suppose the newly added leaf node $x$ is attached to the connected component where $v$ is located, i.e., $T_v^{(u)}$. Then, since:
        
        $$
        |T_v^{(u)}\cup\{x\}| = |T|/2 + 1 > (|T|+1)/2 = |T\cup\{x\}|/2,
        $$
        
        $u$ is no longer the centroid of the new tree. Conversely, because after removing $v$, there is still a connected component $T_u^{(v)}$ of size $|T|/2$, and the sum of sizes of the other connected components is:
        
        $$
        |T\cup\{x\}| - 1 - |T_u^{(v)}| = |T|/2 \le |T_u^{(v)}|,
        $$
        
        $v$ is still the centroid of the new tree. Since the number of nodes in the new tree is odd, the centroid is unique. Therefore, the centroid also moves at most one edge.
    
    Summarizing the analysis of both cases, the centroid of the new tree must lie on the path between the centroid of the old tree and the newly added leaf node.
    
    Property 3 can be explained by induction. When connecting $T$ and $T'$, the newly added edge is $(x,y)$, with $x\in T, y\in T'$. Suppose a (one of the) centroid(s) of the new tree lies in $T$. Consider starting from tree $T$, and gradually adding nodes in $T'$ as leaf nodes of tree $T$. It can be proven inductively that a (one of the) centroid(s) of the tree always lies on the path connecting the centroid of tree $T$ and node $x$. The base case is obvious. Assume the proposition holds up to some point. Let the centroid at this time be $v$. From the analysis of Property 2, the centroid of the new tree must lie on the path connecting the newly added node and the current centroid $v$. Since it cannot move outside tree $T$, we only need to consider the common part of the path with tree $T$, which is the path connecting the current centroid $v$ and node $x$. By the inductive hypothesis, $v$ already lies on the path connecting the centroid of tree $T$ and node $x$. Therefore, the centroid of the new tree must also lie on the path connecting the current centroid $v$ and node $x$. By induction, the proposition holds.
    
    Property 4 only needs to be explained by combining with the properties of [Heavy Path Decomposition](./hld.md#properties-of-heavy-light-decomposition). Let $v$ be a (one of the) centroid(s) of tree $T$. When $v$ is the root node, the proposition is obviously true. Now assume $v$ is a non-root node, and $u$ is its parent. Since $|T_u^{(v)}| \le |T|/2$, the size of the subtree where $v$ is located is at least $|T|/2$. However, if it passes through a light edge on the path to the root, the size of its subtree will be strictly less than $|T|/2$, a contradiction. Therefore, it must be on the heavy path where the root is located. Furthermore, according to the definition of heavy paths, the heavy path where the root is located in the subtree of the root's heavy child is part of the heavy path where the root is located in the original tree. And according to Property 3, after adding the heavy child and all its light child subtrees to the subtree of the heavy child, the centroid position moves along the path between the current centroid and the root. Therefore, the new centroid must be an ancestor of the old centroid.

## Finding Methods

According to the equivalent definitions of centroid, there are two methods to find all centroids of a tree in $O(n)$ time, where $n$ is the size of the tree.

### DFS to Count Subtree Sizes

Calculate the size of each subtree through DFS. For each node, record the sizes of all subtrees corresponding to its child nodes, and use the total number of nodes minus the current subtree size to get the "upward" subtree size. Then we can find the centroid according to the definition.

??? example "Reference Implementation"
    ```cpp
    --8<-- "docs/graph/code/tree-centroid/tree-centroid_2.cpp:core"
    ```

### Reroot DP to Count Depth Sums

We can also use reroot DP to calculate the sum of depths of all nodes when rooted at different nodes (i.e., the sum of distances to the current root node). According to the definition, we just need to find the node that minimizes this depth sum.

??? example "Reference Implementation"
    ```cpp
    --8<-- "docs/graph/code/tree-centroid/tree-centroid_3.cpp:core"
    ```

## Example Problems

???+ example "[Codeforces Round 359 (Div. 1) B. Kay and Snowflake](https://codeforces.com/problemset/problem/685/B)"
    Given a rooted tree, find the centroid of each subtree.

??? note "Solution Idea"
    According to Property 3, for a subtree rooted at node $u$, its centroid must lie on the path from the centroid of the subtree rooted at $u$'s direct child to node $u$.
    
    Similar to the DFS method for finding centroids mentioned above, for each subtree rooted at node $u$, first find the centroids of all subtrees rooted at $u$'s direct child nodes (the centroid of a leaf node is itself), then upward check whether the nodes on the path are centroids.
    
    The centroids of all subtrees can be found in $O(n)$ time.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/graph/code/tree-centroid/tree-centroid_1.cpp"
    ```

## Practice Problems

-   [Gym 101649G Godfather](https://codeforces.com/gym/101649/problem/G)
-   [POJ 1655 Balancing Art](http://poj.org/problem?id=1655)
-   [Luogu P1364 Hospital Setup](https://www.luogu.com.cn/problem/P1364)
-   [Codeforces 1406C Link Cut Centroids](https://codeforces.com/contest/1406/problem/C)
-   [Codeforces 708C Centroids](https://codeforces.com/problemset/problem/708/C)

## References

-   [Some Properties of Tree "Centroid" and Dynamic Maintenance - fanhq666](https://web.archive.org/web/20181122041458/http://fanhq666.blog.163.com/blog/static/81943426201172472943638) ([Blog Garden Repost](https://www.cnblogs.com/qlky/p/5781081.html))
-   [Tree Diameter, Tree Centroid and Tree Point Division - cyendra](https://www.cnblogs.com/zinthos/p/3899075.html)
-   [Properties of Tree Centroid and Its Proof - suxxsfe](https://www.cnblogs.com/suxxsfe/p/13543253.html)
-   Informatics Olympiad Dictionary, Section 2.4.7.11, Part 1: Tree Centroid