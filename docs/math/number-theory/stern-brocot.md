## Introduction

This article introduces data structures for storing reduced fractions and other related concepts. They are closely related to [continued fractions](./continued-fraction.md), can be used to solve a series of number theory problems in competitive programming, and may appear as the hidden background of certain problems.

## Stern-Brocot Tree

The Stern-Brocot tree is an elegant structure for maintaining fractions, containing all distinct positive rational numbers. This structure was independently discovered by Moritz Stern in 1858 and Achille Brocot in 1861.

### Construction

#### Layer-by-Layer Construction

The Stern-Brocot tree can be obtained in the process of iteratively constructing the $k$-th order Stern-Brocot sequence. The $0$-th order Stern-Brocot sequence consists of two simple fractions:

$$
\frac{0}{1},\ \frac{1}{0}.
$$

Here, $\dfrac{1}{0}$ is not technically a rational number; it can be understood as representing $\infty$ in lowest terms.

In the $k$-th order Stern-Brocot sequence, between two adjacent fractions $\dfrac{a}{b}$ and $\dfrac{c}{d}$, we insert their [mediant](http://en.wikipedia.org/wiki/Mediant_(mathematics))[^mediant] $\dfrac{a+c}{b+d}$ to obtain the $(k+1)$-th order Stern-Brocot sequence. Although the definition of mediant itself allows for fraction reduction, in the construction of the Stern-Brocot tree, we only need to directly add the numerators and denominators without worrying about reduction. In this way, we can iteratively construct Stern-Brocot sequences of all orders. The results of the first few iterations are:

$$
\begin{array}{ccccccccc}
&&&\dfrac{0}{1}, & \dfrac{1}{1}, & \dfrac{1}{0} &&&\\\\
&&\dfrac{0}{1}, & \dfrac{1}{2}, & \dfrac{1}{1}, & \dfrac{2}{1}, & \dfrac{1}{0} &&\\\\
\dfrac{0}{1}, & \dfrac{1}{3}, & \dfrac{1}{2}, & \dfrac{2}{3}, & \dfrac{1}{1}, & \dfrac{3}{2}, & \dfrac{2}{1}, & \dfrac{3}{1}, & \dfrac{1}{0}
\end{array}
$$

Connecting the newly added fractions at each iteration into a tree structure gives the Stern-Brocot tree, as shown in the following figure:

![](./images/stern-brocot-tree.svg)

The $k$-th order Stern-Brocot sequence, excluding the left and right endpoints, is the inorder traversal of the Stern-Brocot tree at depth $k-1$.

#### Triple Construction

Another equivalent construction method uses the triple

$$
\left(\dfrac{0}{1},\dfrac{1}{1},\dfrac{1}{0}\right)
$$

as the root node, and at each node

$$
\left(\dfrac{a}{b},\dfrac{p}{q},\dfrac{c}{d}\right)
$$

we add respectively

$$
\left(\dfrac{a}{b},\dfrac{a+p}{b+q},\dfrac{p}{q}\right),\ \left(\dfrac{p}{q},\dfrac{p+c}{q+d},\dfrac{c}{d}\right)
$$

as the left and right child nodes, which constructs the entire Stern-Brocot tree. In the triple stored at each node of the Stern-Brocot tree, the actual stored fraction is the middle fraction $\dfrac{p}{q}$ of the triple, while the left and right fractions $\dfrac{a}{b}$ and $\dfrac{c}{d}$ are fractions that appeared earlier. Moreover, considering the first construction method, the fraction $\dfrac{p}{q}$ is obtained precisely by inserting the mediant of $\dfrac{a}{b}$ and $\dfrac{c}{d}$.

#### Matrix Representation and Stern-Brocot Number System

The triple construction implies that each node on the Stern-Brocot tree corresponds to a matrix

$$
S = \begin{pmatrix}
b & d\\
a & c
\end{pmatrix}.
$$

The root node of the Stern-Brocot tree is the identity matrix $I$, and moving to the left child and right child corresponds to multiplying the current matrix on the right by

$$
L = \begin{pmatrix}
1 & 1 \\
0 & 1
\end{pmatrix},~
R = \begin{pmatrix}
1 & 0 \\
1 & 1
\end{pmatrix}
$$

respectively. The fraction actually corresponding to each node is $f(S) = \dfrac{a+c}{b+d}$. Each node's matrix $S$ can be written as a product of a series of matrices $L$ and $R$, which can also be understood as a string of $L$ and $R$ representing the path from the root node to it. Representing all positive rational numbers uniquely as such a string can be considered as obtaining a representation of positive rational numbers, hence it is also called the **Stern-Brocot number system**.

#### Tree Building Implementation

The tree building algorithm only needs to simulate the above process. Below is code for performing an inorder traversal of the first $n$ layers of the Stern-Brocot tree.

???+ example "Tree Building"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/stern-brocot/tree-build.cpp:core"
        ```
    
    === "Python"
        ```py
        --8<-- "docs/math/code/stern-brocot/tree-build.py:core"
        ```

The complexity of the tree building algorithm is $O(n^2)$.

### Properties

Now we discuss the properties of the Stern-Brocot tree. In short, the Stern-Brocot tree is a [binary search tree](../../ds/bst.md) containing all positive reduced rational fractions. It is also a [heap](../../ds/binary-heap.md) of numerators and denominators, and a [Cartesian tree](../../ds/cartesian-tree.md) of the pairs formed by denominator and numerator. If we consider the interval formed by the endpoints in the triple construction, the Stern-Brocot tree can also be viewed as a [segment tree](../../ds/seg.md) on $[0, \infty]$. These statements can be derived from the following three basic properties:

#### Monotonicity

In the above construction, the fractions at each level are monotonically increasing. This can be proved by induction. Because if $\dfrac{a}{b} < \dfrac{c}{d}$, then we must have

$$
\dfrac{a}{b} < \dfrac{a+c}{b+d} < \dfrac{c}{d}.
$$

This can be obtained by clearing denominators in the inequality. The base case is $\dfrac{0}{1} < \dfrac{1}{0}$, and monotonicity clearly holds.

#### Reduced Form

In the above construction, each fraction is in lowest terms. This also requires inductive proof. In each level of the construction, adjacent fractions $\dfrac{a}{b}$ and $\dfrac{c}{d}$ satisfy

$$
bc - ad = \det\begin{pmatrix}
b & d\\
a & c
\end{pmatrix} = 1.
$$

At the root, this is the identity matrix, which clearly holds. When moving downward, the determinant of the matrices $L$ and $R$ multiplied are both $1$. By properties of [determinants](../linear-algebra/determinant.md), the following also holds at the next level:

$$
\det\begin{pmatrix}b & b+d \\ a & a+c \end{pmatrix} = \det\begin{pmatrix}b+d & d \\ a+c & c\end{pmatrix} = 1.
$$

This is also obvious for the base case $\dfrac{0}{1}$ and $\dfrac{1}{0}$. Thus, by [Bézout's identity](./bezouts.md), the numerator and denominator of each fraction must be coprime, i.e., all fractions are in lowest terms.

#### Completeness

Finally, we need to show that the Stern-Brocot tree includes all positive reduced fractions. Because the first two properties already show that the Stern-Brocot tree is a binary search tree, and any positive reduced fraction $\dfrac{p}{q}$ must lie between $\dfrac{0}{1}$ and $\dfrac{1}{0}$. According to the search method on a binary search tree, the only possibility that the binary search tree does not contain $\dfrac{p}{q}$ is that the search process runs infinitely. This is impossible.

Assume we now know

$$
\dfrac{a}{b} < \dfrac{p}{q} < \dfrac{c}{d}.
$$

Then we must have

$$
bp - aq \ge 1,\ cq - dp \ge 1.
$$

Multiplying the two inequalities by $(c+d)$ and $(a+b)$ respectively, we get

$$
(c+d)(bp-aq) + (a+b)(cq-dp) \ge a+b+c+d.
$$

Using the previously established equation $bc - ad = 1$, we obtain

$$
p+q \ge a+b+c+d.
$$

Each time the search goes one level deeper, the right side strictly increases while the left side remains unchanged, so the search must terminate in a finite number of steps.

### Finding a Fraction

In practical applications of the Stern-Brocot tree, we often need to query the position of a given fraction in the Stern-Brocot tree.

#### Naive Algorithm

Since the Stern-Brocot tree is a binary search tree, we can determine the path from the root to the given fraction by comparing the current fraction with the target fraction. Represent moving to the left child as $L$ and moving to the right child as $R$. Each path corresponds to a string of $L$ and $R$, which is exactly the representation of the rational number in the Stern-Brocot number system mentioned above. The process of finding the path to a rational number is equivalent to obtaining its representation in the Stern-Brocot number system.

The implementation of the naive fraction finding algorithm is as follows:

???+ example "Naive Fraction Finding"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/stern-brocot/fraction-finding-1.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/stern-brocot/fraction-finding-1.py:core"
        ```

The complexity of the algorithm is $O(p+q)$, so it is not practical in competitive programming.

In the Stern-Brocot number system, each positive irrational number corresponds to a unique infinite-length string. The same algorithm can be used to construct this string. Each prefix of this infinite string corresponds to a reduced rational fraction. Arranging these reduced fractions in a sequence, the denominators in the sequence are strictly increasing, and the limit of the sequence is the irrational number. Therefore, the Stern-Brocot tree can be used to find rational approximations of any accuracy for a given irrational number. However, it should be noted that the difference between this rational sequence and the irrational number is not strictly decreasing. For the rigorous theory of rational approximation, refer to the section on [Diophantine approximation](./continued-fraction.md#丢番图逼近) on the continued fractions page. When using the Stern-Brocot tree to find the best approximation of a real number with denominators not exceeding a certain range, one should compare the distances of the left and right interval endpoints to the real number.

#### Fast Algorithm

The naive fraction finding algorithm is not efficient, but with simple optimization, we can obtain a fast search algorithm with $O(\log(p+q))$ complexity. The key to optimization is to process consecutive $L$ and $R$ operations together.

If the fraction $\dfrac{p}{q}$ to be found lies between $\dfrac{a}{b}$ and $\dfrac{c}{d}$, then when moving to the right $t$ times consecutively, the right boundary stays still while the left node moves to $\dfrac{a+tc}{b+td}$. Conversely, when moving to the left $t$ times consecutively, the left boundary stays still while the right node moves to $\dfrac{ta+c}{tb+d}$. Therefore, we can directly determine the number of moves to the right and left by $\dfrac{a+tc}{b+td} < \dfrac{p}{q}$ or $\dfrac{p}{q} < \dfrac{ta+c}{tb+d}$. We use strict inequality here because the algorithm moves the endpoints, and the fraction to be found appears as the mediant of the final endpoints.

???+ example "Fast Fraction Finding"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/stern-brocot/fraction-finding-2.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/stern-brocot/fraction-finding-2.py:core"
        ```

The current search algorithm requires the fraction $\dfrac{p}{q}$ to be known. If the target fraction is unknown, we often need to use exponential search or binary search for the number of moves each time we move left or right. In this case, the complexity of the fraction finding algorithm is $O(\log^2(p+q))$.

#### Algorithm Based on Continued Fractions

For the case where the fraction is known, we can use continued fractions to give a simpler algorithm. Assume the first group of moves is to the right; if not, set the number of first right moves to zero. Alternating between moving right and left, we arrange the positions of each group of moves as follows:

$$
\dfrac{p_0}{q_0},~\dfrac{p_1}{q_1},~\dfrac{p_2}{q_2},~\cdots,~\dfrac{p_{n-2}}{q_{n-2}},~\dfrac{p_{n-1}}{q_{n-1}},~\dfrac{p_n}{q_n}.
$$

Here, the even-numbered groups of moves are to the right, thus recording the position of the left endpoint; the odd-numbered groups of moves are to the left, thus recording the position of the right endpoint. Add two more endpoints in front of this sequence:

$$
\dfrac{p_{-2}}{q_{-2}} = \dfrac{0}{1},~\dfrac{p_{-1}}{q_{-1}} = \dfrac{1}{0}.
$$

Let the number of moves in the $k$-th group be $t_k$. Then, based on the relationship between the number of moves and the endpoint position obtained above, we have

$$
\dfrac{p_k}{q_k} = \dfrac{t_k p_{k-1} + p_{k-2}}{t_k q_{k-1} + q_{k-2}}.
$$

According to the [recurrence relation of continued fractions](./continued-fraction.md#递推关系), the endpoints

$$
\dfrac{p_k}{q_k} = [t_0, t_1, \cdots, t_k].
$$

The final continued fraction is

$$
\dfrac{p}{q} = \dfrac{p_k + p_{k-1}}{q_k + q_{k-1}} = [t_0, t_1, \cdots, t_{n-1}, t_n, 1].
$$

Therefore, in the [continued fraction representation](./continued-fraction.md#简单连分数) of the target fraction, excluding the final 1, the preceding terms encode the path from the root to the current node on the Stern-Brocot tree. Among them, the even terms (starting from index 0) are edges to right child nodes, and odd terms are edges to left child nodes.

The continued fraction representation of a rational number can be obtained by the Euclidean algorithm. Therefore, the complexity of the fraction finding algorithm based on continued fraction representation is $O(\log \min\{p, q\})$.

???+ example "Continued Fraction Based Fraction Finding"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/stern-brocot/fraction-finding-3.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/stern-brocot/fraction-finding-3.py:core"
        ```

Using the continued fraction representation, we can easily express the parent and child nodes of a node. For a node $[t_0, t_1, \cdots, t_n, 1]$, its parent node is the node obtained by moving one step less in the final direction: when $t_k > 1$, the parent node is $[t_0, t_1, \cdots, t_n - 1, 1]$; otherwise, the parent node is $[t_0, t_1, \cdots, t_{n-1}, 1]$. Its two child nodes are $[t_0, t_1, \cdots, t_n + 1, 1]$ and $[t_0, t_1, \cdots, t_n, 1, 1]$. Which node is the left child and which is the right child depends on the parity of $n$.

## Calkin-Wilf Tree

Another simpler structure for storing positive rational fractions is the Calkin-Wilf tree. It is usually shown as follows:

![pic](./images/calkin-wilf-tree.svg)

The root node of the tree is $\dfrac{1}{1}$. Then, for a fraction $\dfrac{p}{q}$ at a node, its left and right children are $\dfrac{p}{p+q}$ and $\dfrac{p+q}{q}$ respectively. Similar to the Stern-Brocot tree, every fraction in it is in lowest terms, and each positive reduced fraction appears exactly once.

### Relationship with Continued Fractions

Unlike the Stern-Brocot tree, the Calkin-Wilf tree is not a binary search tree, so it cannot be used for binary search of rational numbers.

In the Calkin-Wilf tree, when $p > q$, the parent node of fraction $\dfrac{p}{q}$ is $\dfrac{p-q}{q}$; when $p < q$, it is $\dfrac{p}{q-p}$. For the first case, starting from $\dfrac{p}{q}$, it is the right child of its parent node, and can move up through the right side of the parent node until the numerator is no longer greater than the denominator. At this point, the fraction stored at the node is $\dfrac{p \bmod q}{q}$, and the number of moves in this group is $\left\lfloor \dfrac{p}{q} \right\rfloor$. For the second case, it is the left child of its parent node, and can move up through the left side of the parent node until the denominator is no greater than the numerator. At this point, the fraction stored at the node is $\dfrac{p}{q \bmod p}$, and the number of moves in this group is $\left\lfloor \dfrac{q}{p} \right\rfloor$.

Using the language of continued fractions, let the current node store the remainder $s_k$ of some continued fraction. Then moving up $\lfloor s_k \rfloor$ times along the right side of the parent node reaches the fraction $\dfrac{1}{s_{k+1}}$, followed by moving $\lfloor s_{k+1} \rfloor$ times along the left side to reach $s_{k+2}$. Therefore, starting from node $s_0 = \dfrac{p}{q}$ and moving up to the root $\dfrac{1}{1}$, the path is encoded by the continued fraction $[t_0, t_1, \cdots, t_n, 1]$: excluding the final 1, the even terms (starting from index 0) represent the number of moves along the right side of the parent node, and the odd terms represent the number of moves along the left side.

For the node storing fraction $\dfrac{p}{q} = [t_0, t_1, \cdots, t_n, 1]$, its parent node has the following representation:

1. When $t_0 > 0$, its parent node is $\dfrac{p-q}{q} = [t_0 - 1, t_1, \cdots, t_n, 1]$.
2. When $t_0 = 0$ and $t_1 > 1$, its parent node is $\dfrac{p}{q-p} = [0, t_1 - 1, t_2, \cdots, t_n, 1]$.
3. When $t_0 = 0$ and $t_1 = 1$, its parent node is $\dfrac{p}{q-p} = [t_2, t_3, \cdots, t_n, 1]$.

Conversely, its child nodes are $\dfrac{p+q}{q} = [t_0 + 1, t_1, \cdots, t_n, 1]$ and $\dfrac{p}{p+q} = [0, 1, t_0, t_1, \cdots, t_n, 1]$. For the continued fraction representation of the second child node, when $t_0 = 0$, it should be understood as $[0, 1 + t_1, \cdots, t_n, 1]$.

### Relationship with Stern-Brocot Tree

Similarly, establishing a connection with continued fractions, the nodes along the path in the Stern-Brocot tree exhibit a recursive relationship of convergent fractions, while the nodes along the path in the Calkin-Wilf tree exhibit a recursive relationship of remainders. The continued fraction representation of the same fraction is fixed, so the encoding of its path from the node to the root on the Calkin-Wilf tree is exactly the same as the encoding of the path from the root to the node on the Stern-Brocot tree. However, because the direction of the path is reversed, although the Stern-Brocot tree and Calkin-Wilf tree store the same fractions at the same level, their positions are different.

If we perform [breadth-first search](../../graph/bfs.md) on both trees and number the nodes sequentially, with the root node numbered as $1$, then for a node numbered $v$, its left and right children are $2v$ and $2v + 1$ respectively. From the binary representation of the number, excluding the leading $1$, each $1$ from high to low represents moving to a right child, and each $0$ represents moving to a left child. On the Calkin-Wilf tree, the rational number represented by continued fraction $[t_0, t_1, \cdots, t_n, 1]$ is at the node numbered

$$
1\cdots \underbrace{0\cdots 0}_{t_3}\underbrace{1\cdots 1}_{t_2}\underbrace{0\cdots 0}_{t_1}\underbrace{1\cdots 1}_{t_0}.
$$

Correspondingly, on the Stern-Brocot tree, the rational number represented by continued fraction $[t_0, t_1, \cdots, t_n, 1]$ is at the node numbered

$$
1\underbrace{1\cdots 1}_{t_0}\underbrace{0\cdots 0}_{t_1}\underbrace{1\cdots 1}_{t_2}\underbrace{0\cdots 0}_{t_3}\cdots.
$$

Removing the initial $1$, the remaining binary digits form the number of vertices at the same level from left to right (starting from $0$). This derivation shows that the arrangement of fractions at the same level in the Stern-Brocot tree and Calkin-Wilf tree are bit-reversal permutations of each other.

This is why nodes on the Stern-Brocot tree are sometimes numbered according to their corresponding Calkin-Wilf tree node numbers, as shown in the following figure:

![pic](./images/stern-brocot-index.svg)

This numbering can be constructed recursively: the root node is numbered $1$. Each time we move to a left child, we replace the leading $1$ of the number with $10$, and when moving to a right child, we replace the leading $1$ with $11$. Reading this number from right to left gives the path from the root to that node.

### Stern's Diatomic Sequence

Arranging all fractions in the Calkin-Wilf tree according to the breadth-first search numbering, or arranging all fractions in the Stern-Brocot tree according to the numbering shown in the figure above, we obtain the following sequence:

$$
\frac{1}{1},~\dfrac{1}{2},~\dfrac{2}{1},~\dfrac{1}{3},~\dfrac{3}{2},~\dfrac{2}{3},~\dfrac{3}{1},~\dfrac{1}{4},~\dfrac{4}{3},~\dfrac{3}{5},~\dfrac{5}{2},\cdots.
$$

Using the construction process of the Calkin-Wilf tree, it can be proved that in this sequence, for any two adjacent fractions, the denominator of the first equals the numerator of the second. Extracting the numerators gives the Stern's diatomic sequence (Stern diatomic sequence, [OEIS A002487](https://oeis.org/A002487)), also called the Stern-Brocot sequence. The sequence numbering starts from $1$, with the 0th term specified as $0$.

Let $a_n$ be the $n$-th number in the Stern's diatomic sequence. Then it satisfies the following recurrence:

$$
\begin{aligned}
a_{2n} &= a_n,\\
a_{2n+1} &= a_n + a_{n+1}.
\end{aligned}
$$

The recurrence starts with $a_0 = 0$ and $a_1 = 1$. To find the value of $a_n$ in the Stern's diatomic sequence, directly using the recurrence gives $O(\log^2 n)$ complexity, which is not good. A better approach is to treat it as the numerator of the fraction numbered $n$ on the Calkin-Wilf tree, and use the continued fraction based recurrence relationship described above to solve it with $O(\log n)$ complexity.

## Farey Sequence

The Farey sequence has extremely similar characteristics to the Stern-Brocot tree. Denote the **$n$-th order Farey sequence** (Farey sequence of order $n$) as $F_n$. It represents the sequence of all reduced fractions with denominator not exceeding $n$ in the interval $[0, 1]$, arranged in increasing order:

$$
\begin{array}{lllllllllllll}
F_1 = \bigg\{&\dfrac{0}{1},&&&&&&&&&&\dfrac{1}{1}&\bigg\}\\\\
F_2 = \bigg\{&\dfrac{0}{1},&&&&&\dfrac{1}{2},&&&&&\dfrac{1}{1}&\bigg\}\\\\
F_3 = \bigg\{&\dfrac{0}{1},&&&\dfrac{1}{3},&&\dfrac{1}{2},&&\dfrac{2}{3},&&&\dfrac{1}{1}&\bigg\}\\\\
F_4 = \bigg\{&\dfrac{0}{1},&&\dfrac{1}{4},&\dfrac{1}{3},&&\dfrac{1}{2},&&\dfrac{2}{3},&\dfrac{3}{4},&&\dfrac{1}{1}&\bigg\}\\\\
F_5 = \bigg\{&\dfrac{0}{1},&\dfrac{1}{5},&\dfrac{1}{4},&\dfrac{1}{3},&\dfrac{2}{5},&\dfrac{1}{2},&\dfrac{3}{5},&\dfrac{2}{3},&\dfrac{3}{4},&\dfrac{4}{5},&\dfrac{1}{1}&\bigg\}
\end{array}
$$

By the definition of the Farey sequence, it naturally satisfies monotonicity, reduced form, and completeness. As shown in the figure, the fractions newly added to $F_k$ compared to $F_{k-1}$ are always the mediants of adjacent fractions in $F_{k-1}$.

The algorithm for constructing the Stern-Brocot tree above can also be used to construct the Farey sequence. Since the Stern-Brocot tree contains all reduced fractions, we can obtain code for constructing the Farey sequence by simply modifying the boundary condition to the restriction on denominators. The $n$-th order Farey sequence $F_n$ can be viewed as a subsequence of the $(n-1)$-th order Stern-Brocot sequence.

???+ example "Constructing Farey Sequence"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/stern-brocot/farey-build.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/stern-brocot/farey-build.py:core"
        ```

The complexity of directly constructing the Farey sequence is $O(|F_n|) = O(n^2)$.

### Sequence Length and Fraction Finding

The length of the Farey sequence can be found recursively. Compared to $F_{n-1}$, the additional fractions in $F_n$ all have denominator $n$, and the numerator does not exceed $n$ and is coprime with $n$. Therefore:

$$
\begin{aligned}
|F_n| &= |F_{n-1}| + \varphi(n) = 1 + \sum_{k=1}^n \varphi(k).
\end{aligned}
$$

Here, $\varphi(n)$ is the [Euler totient](./euler-totient.md). This formula can be computed in $O(n)$ time using the [linear sieve](./sieve.md#筛法求欧拉函数), and the complexity can be reduced to $O(n^{2/3})$ using the [Du Jiao sieve](./du.md#问题一).

More commonly than directly finding the sequence length is finding the index of a fraction $r = \dfrac{p}{q}$ in the sequence $F_k$. This is equivalent to computing

$$
1 + \sum_{k = 1}^n \sum_{i=1}^{\lfloor r k \rfloor} [i \perp k] = 1 + \sum_{d=1}^n \mu(d) \sum_{j=1}^{\lfloor n/d \rfloor} \lfloor r j \rfloor.
$$

To obtain the right-hand side, we used [Möbius inversion](./mobius.md). Combining linear sieve and enumerating factors can achieve $O(n)$ preprocessing and $O(n \log n)$ queries. Combining the Du Jiao sieve with the [generalized Euclidean algorithm](./euclidean.md) can achieve $O(n^{2/3})$ preprocessing and $O(\sqrt{n} \log n)$ queries.

Conversely, to find the fraction given an index, we can perform binary search on real numbers in $[0, 1]$, or perform binary search on the [Stern-Brocot tree](#快速算法). The former may be limited by floating-point precision, with $O(\log V)$ queries where $V$ is the precision range. The latter is not limited by floating-point precision, but requires $O(\log^2 n)$ queries.

### Farey Neighbors

If fractions $\dfrac{a}{b}$ and $\dfrac{c}{d}$ are adjacent in some Farey sequence, they are called **Farey neighbors** (Farey neighbors), also known as a Farey pair (Farey pair).

Let $\dfrac{a}{b} < \dfrac{c}{d}$. From the construction process of the Farey sequence, the fraction added later among two adjacent fractions must be the mediant of the other fraction and its previous neighbor. Therefore, Farey neighbors are also adjacent in some order of the Stern-Brocot sequence. According to the property proved in [Reduced form](#最简性), we must also have

$$
bc - ad = 1.
$$

Conversely, this is also a sufficient condition for two reduced proper fractions to become Farey neighbors. We now explain this. Let $\dfrac{a}{b}$ be the fraction with the larger denominator among the two. Then both fractions appear in $F_b$. Let $\dfrac{e}{f}$ be the fraction to the right of $\dfrac{a}{b}$ in $F_b$. According to the necessity we have shown, $be - af = 1$. However, the linear congruence equation $bx - ay = 1$ has only one positive integer solution with $y \le b$. Therefore, $(e, f) = (c, d)$.

In fact, because the next reduced fraction that will appear between them is $\dfrac{a+c}{b+d}$, both $\dfrac{a}{b}$ and $\dfrac{c}{d}$ are adjacent in the Farey sequences from order $\max\{b, d\}$ to order $(b+d-1)$.

The Farey neighbor relationships for fractions with denominators not exceeding $9$ are shown in the following figure:

![](./images/farey-diagram-ford-circle.svg)

The circles in the figure are called [Ford circles](https://en.wikipedia.org/wiki/Ford_circle): for each reduced fraction $\dfrac{p}{q}$ in $[0, 1]$, we draw a circle with center $\left(\dfrac{p}{q}, \dfrac{1}{2q^2}\right)$ and radius $\dfrac{1}{2q^2}$. The figure shows that the Ford circles of two fractions can only be tangent or disjoint, and the two circles are tangent if and only if the two fractions are Farey neighbors. Moreover, for any two tangent circles in the figure, there exists a unique third circle that is tangent to both. The fraction corresponding to this third circle is the mediant of the two fractions corresponding to the two circles.

To verify that tangent circles always correspond to Farey neighbors, we can directly compute the distance between the two circle centers:

$$
\left(\dfrac{a}{b} - \dfrac{c}{d}\right)^2 + \left(\dfrac{1}{2b^2} - \dfrac{1}{2d^2}\right)^2 = \left(\dfrac{1}{2b^2} + \dfrac{1}{2d^2}\right)^2 + \frac{(bc - ad)^2 - 1}{b^2 d^2}.
$$

Since the two reduced fractions are not equal, $|bc - ad| \ge 1$. Therefore, the two circles can only be tangent or disjoint. Moreover, the two circles are tangent if and only if $|bc - ad| = 1$, which is equivalent to the two fractions being Ford neighbors.

Finally, to compute the number of Farey neighbors. Except for $\left(\dfrac{0}{1}, \dfrac{1}{1}\right)$, the denominators of other Farey neighbors are different. Let $\dfrac{p}{q}$ be the one with the larger denominator. Then the other fraction can be obtained from the binary linear Diophantine equation

$$
qx - py = \pm 1.
$$

Each equation has exactly one positive integer solution satisfying $y < q$, corresponding to the neighbor on the left and right of $\dfrac{p}{q}$ respectively. Thus, each proper fraction in $(0, 1)$ has two Farey neighbors with smaller denominators. Together with $\dfrac{0}{1}$ and $\dfrac{1}{1}$, this means there are $(2|F_n| - 3)$ pairs of Farey neighbors in sequence $F_n$.

Of course, the fractions $\dfrac{a}{b} < \dfrac{c}{d}$ found in this process are precisely the left and right neighbors when inserting $\dfrac{p}{q}$ into the sequence. Therefore, they are already Farey neighbors, and $\dfrac{p}{q}$ is their mediant. Let $\dfrac{p}{q} = [t_0, t_1, \cdots, t_n, 1]$. Then these two Farey neighbors with smaller denominators are $[t_0, t_1, \cdots, t_n]$ and $[t_0, t_1, \cdots, t_{n-1}]$ respectively.

To compute other Farey neighbors of the current fraction $\dfrac{p}{q}$, we just need to use the [extended Euclidean algorithm](./bezouts.md#两个变量的情形) to find all solutions satisfying the conditions.

### Recurrence Relation

The Farey sequence has a simple recurrence relation, which can be used to sequentially find all fractions of the $n$-th order Farey sequence from left to right.

First, the analysis above points out that in $F_n$, the newly added term $\dfrac{p}{n}$ is always the mediant of the left and right adjacent fractions. In fact, this relationship holds for all fractions in $F_n$ (except the endpoints). Let $\dfrac{a}{b} < \dfrac{p}{q} < \dfrac{c}{d}$. According to the necessary and sufficient condition for Farey neighbors, we always have

$$
bp - aq = 1 = cq - dp \iff \frac{p}{q} = \dfrac{a + c}{b + d}.
$$

However, for the general case, the fraction $\dfrac{a+c}{b+d}$ may need reduction.

Using this observation, we can construct the following recurrence relation. Let $\dfrac{a}{b}$ and $\dfrac{p}{q}$ be known. We want to find the value of the third fraction $\dfrac{c}{d}$. At this point, there exists $k$ such that

$$
a + c = kp,\ b + d = kq
$$

holds. Because the difference

$$
\frac{kp - a}{kq - b} - \dfrac{p}{q} = \dfrac{bp - aq}{q(kq - b)} = \dfrac{1}{q(kq - b)}
$$

decreases as $k$ increases, and the fraction closest to $\dfrac{p}{q}$ should be the one with the smallest difference among all fractions satisfying $kq - d \le n$. Thus we must have

$$
k = \left\lfloor\dfrac{n + b}{q}\right\rfloor.
$$

It can be verified that the fraction obtained in this way is indeed in $F_n$. Therefore, the numerators and denominators of fractions in $F_n$ satisfy the recurrence relation:

$$
\begin{aligned}
p_k &= \left\lfloor\frac{n + q_{k-2}}{q_{k-1}}\right\rfloor p_{k-1} - p_{k-2},\\
q_k &= \left\lfloor\frac{n + q_{k-2}}{q_{k-1}}\right\rfloor q_{k-1} - q_{k-2}.
\end{aligned}
$$

The recurrence starts with $(p_0, q_0) = (0, 1)$ and $(p_1, q_1) = (1, n)$.

## Practice Problems

Problems based on the material in this article:

- [LOJ 6685. Maze](https://loj.ac/p/6685)
- [UVa 10077. The Stern-Brocot Number System](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=33&page=show_problem&problem=1018)
- [Luogu P8058. [BalkanOI2003] Farey Sequence](https://www.luogu.com.cn/problem/P8058)
- [UVa 12995. Farey Sequence](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=862&page=show_problem&problem=4878)
- [UVa 10408. Farey Sequences](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1349)
- [UVa 12438. Farey Polygon](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=279&page=show_problem&problem=3869)
- [AtCoder ARC123F. Insert Addition](https://atcoder.jp/contests/arc123/tasks/arc123_f)

Problems requiring binary search on the Stern-Brocot tree:

- [AtCoder ABC333G. Nearest Fraction](https://atcoder.jp/contests/abc333/tasks/abc333_g)
- [SPOJ DIVCNT1 - Counting Divisors](https://www.spoj.com/problems/DIVCNT1/)
- [SPOJ AFS3 - Amazing Factor Sequence (hard)](https://www.spoj.com/problems/AFS3/)

## References and Notes

- [Stern-Brocot tree - Wikipedia](https://en.wikipedia.org/wiki/Stern%E2%80%93Brocot_tree)
- [Calkin-Wilf tree - Wikipedia](https://en.wikipedia.org/wiki/Calkin%E2%80%93Wilf_tree)
- [Farey sequence - Wikipedia](https://en.wikipedia.org/wiki/Farey_sequence)

**Part of this page is translated from the article [Дерево Штерна-Броко. Ряд Фарея](http://e-maxx.ru/algo/stern_brocot_farey) and its English translation [The Stern-Brocot Tree and Farey Sequences](https://cp-algorithms.com/others/stern_brocot_tree_farey_sequences.html). The Russian version is in the public domain with a link left; the English version is licensed under CC-BY-SA 4.0. Part of the content is also translated from [Continued fractions](https://cp-algorithms.com/algebra/continued-fractions.html), licensed under CC-BY-SA 4.0. Content has been modified.**

[^mediant]: The translation name comes from Section 4.5 of "Concrete Mathematics" translated by Mingyao Zhang and Fan Zhang.