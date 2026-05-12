## Definition

The order between suffixes is defined by lexicographic order. A suffix balanced tree is a balanced tree that maintains the order of these suffixes, i.e., the suffix balanced tree of string $T$ is the ordered set of all suffixes of $T$. Each node on the suffix balanced tree corresponds to a suffix of the original string.

In particular, the inorder traversal of the suffix balanced tree is the suffix array.

## Construction Process

To build a suffix balanced tree for a string $T$ of length $n$, consider adding its suffixes to the suffix balanced tree in reverse order.

Let the set maintained by the suffix balanced tree be $X$, and the current suffix being added be $S$. Then adding the next suffix is adding $\texttt{c}S$ to $X$ (which can also be understood as the string maintained by the suffix balanced tree being $S$, and next we add a character $\texttt{c}$ in front of $S$). This operation is essentially inserting a node into the balanced tree.

Here we use a balanced tree with expected height $O(\log n)$, such as Scapegoat tree or Treap.

### Method 1

When inserting, we brute-force compare the sizes of two suffixes to determine which subtree to add to. Thus, a single insertion requires at most $O(\log n)$ comparisons, and each comparison takes $O(n)$ time in the worst case, for a total of $O(n \log n)$.

A total of $n$ insertions will be performed, so this method has time complexity $O(n^2 \log n)$.

### Method 2

Note that the difference between $\texttt{c}S$ and $S$ is only $\texttt{c}$, and $S$ already belongs to $X$. We can use this to optimize the insertion.

Suppose we need to compare the sizes of $\texttt{c}S$ and $A$, where $A, S \in X$. When comparing, we first compare the first characters of both strings. If the first characters are not equal, the relationship between the strings is already determined; if the first characters are equal, we only need to determine the relationship between the strings after removing the first character. After removing the first character, both strings already belong to $X$, so we can use the $O(\log n)$ ranking operation of the balanced tree to complete the subsequent comparison. Thus, a single insertion takes at most $O(\log^2 n)$.

A total of $n$ insertions will be performed, so this method has time complexity $O(n \log^2 n)$.

### Method 3

Based on Method 2, if we can determine the size relationship between two nodes in the balanced tree in $O(1)$, then the suffix balanced tree can be constructed in $O(n \log n)$.

Let $val_i$ be the value of node $i$. If, when building the balanced tree, each node maintains an additional tag $tag_i$, such that $tag_i > tag_j \iff val_i > val_j$, then we can determine the size of two nodes in the balanced tree in $O(1)$ based on the size of $tag_i$.

Let each node in the balanced tree correspond to a real interval, and let the root correspond to $(0, 1)$. For node $i$, let its corresponding real interval be $(l, r)$, then $tag_i = \frac{l + r}{2}$, its left subtree corresponds to the real interval $(l, tag_i)$, and its right subtree corresponds to the real interval $(tag_i, r)$. It is easy to verify that $tag_i$ satisfies the above requirement.

Since we use a balanced tree with expected height $O(\log n)$, the precision is guaranteed to some extent. In actual implementation, we can also use a larger interval, for example, let the root correspond to $(0, 10^{18})$.

### Method 4

In fact, we can first construct the suffix array, and then construct the suffix balanced tree based on the suffix array. The complexity bottleneck of this method lies in the construction complexity of the suffix array or the complexity of inserting $n$ elements into the balanced tree at once.

## Delete Operation

Suppose the current suffix being added is $\texttt{c}S$, and the previous suffix added was $S$. The suffix balanced tree also supports deleting the suffix $\texttt{c}S$ (which can also be understood as the string maintained by the suffix balanced tree being $\texttt{c}S$, deleting the leading $\texttt{c}$).

Similar to the insertion operation, we can complete the deletion of $\texttt{c}S$ by using the delete node operation of the balanced tree.

## Advantages of Suffix Balanced Tree

-   The idea of suffix balanced tree is relatively clear, easier to understand compared to suffix automaton and other suffix structures; if you can write a balanced tree, you can write this.
-   The complexity of suffix balanced tree does not depend on the size of the character set.
-   Suffix balanced tree supports deleting a character at the beginning of the string.
-   If a persistent balanced tree is used, then the suffix balanced tree can also be persistent.

## Problems

### [P3809 [Template] Suffix Sorting](https://www.luogu.com.cn/problem/P3809)

This is a template problem for suffix array. After building the suffix balanced tree, obtain the suffix array through inorder traversal.

??? note "Reference code for SGT version"
    ```cpp
    --8<-- "docs/string/code/suffix-bst/suffix-bst_1.cpp"
    ```

### [P6164 [Template] Suffix Balanced Tree](https://www.luogu.com.cn/problem/P6164)

???+ note "Problem statement"
    Given an initial string $s$ and $q$ operations:
    
    1.  Insert several characters at the end of the current string.
    2.  Delete several characters at the end of the current string.
    3.  Query how many times the string $t$ appears as a contiguous substring in the current string.
    
    The problem **requires online processing**, the length of string changes and the initial length $\le 8 \times 10^5$, $q \le 10^5$, and the total length of all queries $\le 3 \times 10^6$.

For operations 1 and 2, since the suffix balanced tree conveniently supports head-insertion and head-deletion, we can convert tail-insertion and tail-deletion to head-insertion and head-deletion. Here, if we maintain the suffix balanced tree of the reversed string of $s$ instead of $s$, we can complete the above conversion. Both insertion and deletion in the balanced tree are $O(\log n)$, so the time complexity of inserting or deleting a character is $O(\log n)$. Let $N$ be the total number of characters inserted and deleted, then this part has total time complexity $O(N \log n)$.

For operation 3, the occurrence count of $t$ equals the number of suffixes with prefix $t$, and the number of suffixes with prefix $t$ equals the rank of its successor minus the rank of its predecessor. By adding a very large character after $t$, we can construct a successor of $t$. By decrementing the last character of $t$ by 1, we can construct a predecessor of $t$.

Now to query the rank of a string $t$ in the suffix balanced tree, since we cannot guarantee that $t$ has appeared in the suffix balanced tree, we can only brute-force compare the sizes of strings each time. Each comparison takes $O(|t|)$ time, and each query requires at most $O(\log n)$ comparisons, so the complexity of each query is $O(|t|\log n)$. Let $L$ be the sum of lengths of all query strings, then this part has total time complexity $O(L \log n)$.

??? note "Reference code for SGT version"
    ```cpp
    --8<-- "docs/string/code/suffix-bst/suffix-bst_2.cpp"
    ```

## References

-   Liu Jiazhe - "Applications of Weight-balanced Trees and Suffix Balanced Trees in Olympiad Informatics"