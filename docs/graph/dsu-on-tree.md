author: abc1763613206, cesonic, Ir1d, MingqiHuang, xinchengo, xiaofu-15191, hsefz-ChenJunJie

## Introduction

What is a heuristic algorithm?

A heuristic algorithm is an optimization of some algorithms based on human experience and intuition.

For example, the most common one is the heuristic merge in disjoint set union (DSU). The code is:

```cpp
void merge(int x, int y) {
  int xx = find(x), yy = find(y);
  if (size[xx] < size[yy]) swap(xx, yy);
  fa[yy] = xx;
  size[xx] += size[yy];
}
```

Here, for two sets of different sizes, we merge the smaller set into the larger one, rather than merging the larger into the smaller.

Why? The size of a set can be thought of as its height (under normal circumstances), and merging the set with smaller height into the one with larger height clearly helps us find the parent.

Making the smaller-height tree a subtree of the larger-height tree—this optimization can be called the heuristic merge algorithm.

## Algorithm

Dsu on tree (tree DSU, also known as small-to-large merging) is an algorithm that can be faster than most algorithms and is easier to understand and implement for certain offline tree problems.

Consider the following problem: [Counting Colors on a Tree](https://www.luogu.com.cn/problem/U41492).

???+ note "Problem Introduction"
    Given a rooted tree with $n$ nodes rooted at $1$. Node $u$ has color $c_u$. For each node $u$, answer the number of distinct colors in the subtree rooted at $u$.
    
    $n\le 2\times 10^5$.

![dsu-on-tree-1.png](./images/dsu-on-tree-1.svg)

The common approach for this problem uses heavy data structures (like segment trees with segment trees, etc.). If we can work offline, is there a simpler method?

## Process

Since we support offline queries, consider preprocessing so that answering queries takes $O(1)$.

A naive preprocessing approach has time complexity $O(n^2)$—for each subtree, we traverse it once, and each traversal is $O(n)$. With $n$ nodes, the complexity is $O(n^2)$.

Observe that the answer for each node is derived from its subtrees and itself. Consider using this property to solve the problem.

We can first preprocess the size of each node's subtree and its heavy child. The heavy child, just like in heavy-light decomposition, is the child with the most children. This can clearly be done in $O(n)$.

We use $cnt_i$ to represent the occurrence count of color $i$, and $ans_u$ to represent the answer for node $u$.

When traversing a node $u$, we follow these steps:

1.  First, traverse all light (non-heavy) children of $u$ and compute their answers, but **do not keep** the effects on the $cnt$ array after traversal;
2.  Traverse the heavy child of $u$, **keeping** its effects on the $cnt$ array;
3.  Traverse the subtrees of all light children of $u$ again, adding their contributions to obtain the answer for $u$.

![dsu-on-tree-2.png](./images/dsu-on-tree-2.svg)

The figure above is an example.

This way, for a node, we traverse the heavy subtree once and the light subtrees twice, which is clearly the most economical approach.

By executing this process, we obtain answers for all subtrees of this node.

Why not merge step 1 and step 3? Because the $cnt$ array cannot be reused, otherwise the memory would be too large. We need to complete the work within $O(n)$ memory.

Clearly, if a node $u$ is traversed $x$ times, its heavy child will be traversed $x$ times, and each light child (if any) will be traversed $2x$ times.

Note that except for the heavy child, the $cnt$ array must be cleared after each traversal.

## Proof

We define heavy edges and light edges just like in heavy-light decomposition (edges connecting to heavy children are heavy edges, others are light edges). For the definitions of heavy child and heavy edges, see the figure below. For a tree with $n$ nodes:

The number of light edges on the path from the root to any node is at most $\log n$. Let the number of light edges from the root to a node be $x$, and the subtree size of that node be $y$. Clearly, the child connected by a light edge has a subtree size less than half of the parent (if it were more than half, it wouldn't be a light edge). Therefore, $y<n/2^x$, and since $n>2^x$, we have $x<\log n$.

Also, if a node is the heavy child of its parent, its subtree must be the largest among its siblings. Therefore, on the path from any node to the root, all heavy edges lead to parent nodes that will not traverse to this node when computing the answer. So the number of times a node is traversed equals the number of light edges on the path from the node to the root plus $1$ (the $+1$ is because the node itself must be traversed). Therefore, the number of traversals for a node is $\log n+1$, and the total time complexity is $O(n(\log n+1))=O(n\log n)$. Outputting answers costs $O(m)$.

![dsu-on-tree-3.png](./images/dsu-on-tree-3.svg)

*The bold edges in the figure are heavy edges, and the child connected by a heavy edge is the heavy child.*

## Optimization

During the proof, it's mentioned that dsu on tree utilizes the concept of heavy and light children from heavy-light decomposition to accelerate merging. With this in mind, we can also directly use the dfs order from heavy-light decomposition, converting recursion to iteration for further constant optimization.

The dfs order itself has the property that the subtree of a node is contiguous in the dfs order. Therefore, we can iterate through the dfs order array in reverse. This ensures that when we visit a node, all other nodes in its subtree have already been processed.

The dfs order from heavy-light decomposition has the following good property: a heavy path is contiguous in the dfs order. Therefore, when iterating through nodes in reverse dfs order, for a node at the top of a heavy path, the next node to visit is definitely not its parent, so we need to clear its effects; for nodes not at the top of a heavy path, the previous node visited is either its heavy child or another node from a different branch whose effects have already been cleared, so we can directly inherit its effects. Based on this, we can use the dfs order to quickly count the effects of all light children and record the answer.

The above process is called the non-recursive/iterative implementation of dsu on tree (also known as the dfs order implementation of dsu on tree). Compared to the original recursive implementation, it reduces the time and space overhead of recursive function calls, achieving noticeable constant optimization, **especially when processing trees with many chain structures, where it has significant advantages in stack space**.

## Implementation

??? example "Reference Implementation"
    === "Recursive Implementation"
        ```cpp
        --8<-- "docs/graph/code/dsu-on-tree/dsu-on-tree_1.cpp"
        ```
    
    === "Non-recursive Implementation"
        ```cpp
        --8<-- "docs/graph/code/dsu-on-tree/dsu-on-tree_2.cpp"
        ```

## Applications

1.  Problems where the intended solution is dsu on tree

    For example, [CF741D](http://codeforces.com/problemset/problem/741/D). Given a tree where each node has a letter from 'a' to 'v', each query asks to find a path in a subtree such that the characters on the path form a palindrome when sorted.

    Because it's about forming a palindrome after sorting, a character appearing twice is equivalent to it not appearing at all. In other words, the path satisfies **at most one character appears an odd number of times**.

    The normal approach is to do a dfs on each node; when arriving at a node, enumerate all letters, find paths whose XOR result is greater than $1$ with the current path, and take the longest. This is $O(n^2\log n)$. Dsu on tree can optimize this to $O(n\log^2n)$. For the specific approach, refer to the extended reading below.

2.  Problems that can be solved with DSU hacking

    You can get some partial points on tree segment tree (segment tree of segment trees) problems (without modification operations), and DSU's complexity is better than that of tree Mo's algorithm, which is $O(n\sqrt{m})$.

## Practice Problems

[CF600E Lomsat gelral](http://codeforces.com/problemset/problem/600/E)

Problem translation: Tree nodes have colors. A color occupies a subtree if and only if no other color appears more frequently in that subtree. Find the sum of all colors that occupy each subtree.

[UOJ284 Happy Game Chicken](https://uoj.ac/problem/284)

[CF1709E XOR Tree](https://codeforces.com/contest/1709/problem/E)

## References / Extended Reading

[CF741D Author's Introduction to DSU on Tree](http://codeforces.com/blog/entry/44351)

[The Author's Solution](http://codeforces.com/blog/entry/48871)