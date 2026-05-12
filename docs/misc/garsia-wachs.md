## Introduction

The **Garsia-Wachs algorithm** is an efficient algorithm used by computers to construct **optimal binary search trees** and **alphabetic Huffman codes** in **linear time**. It is named after Adriano Garsia and Michelle L. Wachs, who published the relevant paper in 1977.

## Problem Description

Given an integer $n$ and $n+1$ nonnegative weights $w_{0},w_{1},\dots ,w_{n}$, construct a rooted binary tree in which each of the $n$ internal nodes has two children, meaning the tree has $n+1$ leaves. We map the input sequence of length $n+1$ one-to-one with the order of the binary tree nodes. The goal is to find, among all possible tree structures with $n$ internal nodes, a tree that minimizes the weighted sum of external path lengths from the root to each leaf.

### Optimal Binary Search Tree

This problem can be understood as constructing a binary search tree for $n$ ordered keys, assuming the tree will only be used to search for values not present in the tree. In this case, the $n$ keys divide the search-value space into $n+1$ intervals, and the weight of one of these intervals can be treated as the probability that the search value falls in that interval. The weighted sum of external path lengths controls the expected search time.

### Alphabetic Huffman Code

This problem can also be used to construct Huffman codes. This is a method of unambiguously encoding $n+1$ given values using variable-length sequences of binary values. Under this interpretation, the code of a value is given by the sequence of left and right steps from parent to child on the path from the root to the leaf in the tree (for example, left is $0$ and right is $1$). Unlike standard Huffman codes, Huffman codes constructed this way are alphabetic; that is, the sorted order of these binary codes is the same as the input order of the values. If the weight of a value is its frequency in the encoded message, then the output of the Garsia-Wachs algorithm is an alphabetic Huffman code that compresses the message length as much as possible.

## Procedure

The Garsia-Wachs algorithm generally consists of three stages:

1.  Build a binary tree with values at the leaves, noting that the order may be incorrect.
2.  Compute the distance from the root to each leaf in the tree.
3.  Build another binary tree with the same leaf distances but the correct order.

![](./images/garsia-wachs.png)

As shown above, in the first stage of the algorithm, a binary tree is built by finding unordered triples to merge in the input sequence (left), and the algorithm outputs a correctly ordered binary tree whose leaf heights match those in the other tree.

If two sentinel values $\infty$ (or any sufficiently large finite value) are added to the start and end of the input sequence, the first stage of the algorithm is easier to describe. Therefore, when using the Garsia-Wachs algorithm in contest solutions, for an array $\mathit{num}$ of length $n$, we usually define $\mathit{num}[0] = \mathit{num}[n+1] = \infty$.

The first stage maintains a forest consisting of single-node trees initially created for each non-sentinel input weight. Each tree is associated with a value equal to the sum of the weights of its leaves. To maintain the sequence of these values, two sentinel values are placed at the ends. The initial sequence is simply the leaf weights in input order. Then repeat the following steps; each step reduces the length of the input sequence until only one tree contains all leaves:

-   Find the first three consecutive weight values $x$, $y$, $z$ in the sequence such that $x \leq z$. Because the sentinel value at the end of the sequence is greater than any previous two finite values, such a triple always exists.
-   Remove $x$ and $y$ from the sequence, and create a new tree node as the parent of the $x$ and $y$ nodes, with value $x+y$.
-   Reinsert the new node to the right of the value closest to $x$ before the original position of $x$ that is greater than or equal to $x+y$. Because the left sentinel exists, such a position always exists.

To implement this stage efficiently, the algorithm can maintain the current value sequence in any balanced binary search tree structure. Such a structure lets us remove $x$ and $y$ and reinsert their new parent node in logarithmic time. At each step, the weights at even indices up to the value $y$ form one decreasing sequence, and the weights at odd indices form another decreasing sequence. Therefore, the insertion position of $x+y$ can be found by performing two binary searches on these two decreasing sequences using balanced trees in logarithmic time. By linearly searching from the previous triple's value $z$, we can find the first position satisfying $x \leq z$ in total linear time.

The proof of the third stage of the Garsia-Wachs algorithm, namely that another tree with the same distances exists and that this tree gives the optimal solution, is important. However, because there are several proof methods and they are too complicated, they are omitted here. Assuming the correctness of the third stage, the second and third stages are easy to implement in linear time. Therefore, for an input sequence of length $n$, the total time complexity of the Garsia-Wachs algorithm is $O(n\log n)$.

## Applications

The [garsia-wachs package](https://hackage.haskell.org/package/garsia-wachs) for the functional programming language Haskell implements the Garsia-Wachs algorithm functionally. It is mainly used to build optimal search tables or to balance the [rope](https://hackage.haskell.org/package/rope) data structure with optimal complexity.

???+ note "Note"
    **rope** is a tool in Haskell for manipulating bytestring [finger trees](../ds/finger-tree.md) with optional annotations.

## Examples

???+ note "[POJ 1738 An old Stone Game](http://poj.org/problem?id=1738)"
    There is an ancient stone game. At the start of the game, the player arranges $n$ ($1 \leq n \leq 50000$) piles of stones in a row. The goal is to merge the stones into one pile. The rule is: at each step, the player may merge two adjacent piles into a new pile. The score is the total number of stones in the new pile. Compute the minimum possible total score.

??? note "Solution Idea"
    Stone merging is a classic problem. Usually we can solve it with interval DP, but when the data size is large, such as $n$ ($1 \leq n \leq 50000$) in this problem, the Garsia-Wachs algorithm is more efficient. First, initialize an array $\mathit{num}[n]$ of size $n$, where $\mathit{num}[0] = \mathit{num}[n+1] = \infty$. Second, each time find the smallest $i$ such that $\mathit{num}[i-1] \leq \mathit{num}[i+1]$, and merge $\mathit{num}[i-1], \mathit{num}[i]$ into $\mathit{temp}$; find the largest previous $j$ such that $\mathit{num}[j] > \mathit{temp}$, and move $\mathit{temp}$ after $j$. Repeat this step until only $1$ pile remains.
    Regarding the requirement that only adjacent piles can be merged each time, since $\mathit{num}[j]\geq \mathit{num}[i-1] + \mathit{num}[i]$, we can view $\mathit{num}[j+1]$ through $\mathit{num}[i-2]$ as a whole $\mathit{num}[mid]$, so $\mathit{sum}$ must be merged first. Therefore, this does not violate the problem requirement.

???+ note "[ATCODER N-Slimes](https://atcoder.jp/contests/dp/tasks/dp_n)"
    $N$ slimes are arranged in a row. Initially, the size of the $i$-th slime from the left is $a_{i}$. Taro tries to combine all slimes into one larger slime. He repeatedly performs the following operation until only one slime remains:
    choose two adjacent slimes and combine them into a new slime. The size of the new slime is $x+y$, where $x$ and $y$ are the sizes of the slimes before combination. This operation incurs cost $x+y$. The positional relationship of slimes does not change when combining them. Find the minimum possible total cost.

## References and Further Reading

1.  [Garsia-Wachs algorithm - Wikipedia](https://en.wikipedia.org/wiki/Garsia%E2%80%93Wachs_algorithm)
2.  [Data.Algorithm.GarsiaWachs - Hackage Haskell](https://hackage.haskell.org/package/garsia-wachs-1.2/docs/Data-Algorithm-GarsiaWachs.html)
3.  [garsia-wachs: A Functional Implementation of the Garsia-Wachs Algorithm](https://hackage.haskell.org/package/garsia-wachs)
4.  [Sentinel value - Wikipedia](https://en.wikipedia.org/wiki/Sentinel_value)
5.  [A new proof of the Garsia-Wachs algorithm](https://www.sciencedirect.com/science/article/abs/pii/0196677488900090)
