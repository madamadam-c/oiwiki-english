author: Backl1ght

The AHU algorithm is used to determine whether two rooted trees are isomorphic.

Another common approach for determining tree isomorphism is [Tree Hashing](tree-hash.md).

Prerequisites: [Tree Basics](tree-basic.md), [Tree Centroid](tree-centroid.md)

It is recommended to refer to the examples given in the references while reading.

## Definition of Tree Isomorphism

### Rooted Tree Isomorphism

For two rooted trees $T_1(V_1,E_1,r_1)$ and $T_2(V_2,E_2,r_2)$, if there exists a bijection $\varphi: V_1 \rightarrow V_2$ such that

$$
\forall u,v \in V_1,(u,v) \in E_1 \iff (\varphi(u),\varphi(v))  \in E_2
$$

**and** $\varphi(r_1)=r_2$ holds, then we say the rooted trees $T_1(V_1,E_1,r_1)$ and $T_2(V_2,E_2,r_2)$ are isomorphic.

### Unrooted Tree Isomorphism

For two unrooted trees $T_1(V_1,E_1)$ and $T_2(V_2,E_2)$, if there exists a bijection $\varphi: V_1 \rightarrow V_2$ such that

$$
\forall u,v \in V_1,(u,v) \in E_1 \iff (\varphi(u),\varphi(v))  \in E_2
$$

holds, then we say the unrooted trees $T_1(V_1,E_1)$ and $T_2(V_2,E_2)$ are isomorphic.

In simple terms, if by relabeling all nodes of tree $T_1$, tree $T_1$ and tree $T_2$ can be made **exactly the same**, then these two trees are isomorphic.

## Problem Transformation

The unrooted tree isomorphism problem can be transformed into a rooted tree isomorphism problem. The specific method is as follows:

For unrooted trees $T_1(V_1, E_1)$ and $T_2(V_2,E_2)$, first find **all** their centroids.

-   If the two unrooted trees have different numbers of centroids, then the two trees are not isomorphic.
-   If both unrooted trees have exactly one centroid, denoted as $c_1$ and $c_2$ respectively, then if rooted tree $T_1(V_1,E_1,c_1)$ is isomorphic to rooted tree $T_2(V_2,E_2,c_2)$, then unrooted tree $T_1(V_1, E_1)$ is isomorphic to unrooted tree $T_2(V_2,E_2)$, and vice versa.
-   If both unrooted trees have exactly two centroids, denoted as $c_1,c'_1$ and $c_2,c'_2$ respectively, then if rooted tree $T_1(V_1,E_1,c_1)$ is isomorphic to rooted tree $T_2(V_2,E_2,c_2)$ **or** rooted tree $T_1(V_1,E_1,c'_1)$ is isomorphic to rooted tree $T_2(V_2,E_2,c_2)$, then unrooted tree $T_1(V_1, E_1)$ is isomorphic to unrooted tree $T_2(V_2,E_2)$, and vice versa.

Therefore, as long as we can solve the rooted tree isomorphism problem, we can transform the unrooted tree isomorphism problem into a rooted tree isomorphism problem using the above method, thus solving the unrooted tree isomorphism problem.

Assuming there is an algorithm that can solve rooted tree isomorphism in $O(|V|)$, then according to the above method, we can also solve unrooted tree isomorphism in $O(|V|)$ time.

## Naive AHU Algorithm

The naive AHU algorithm is based on parenthesis sequences.

### Principle 1

We know that a valid parenthesis sequence uniquely corresponds to a rooted tree, and the parenthesis sequence of a tree is formed by concatenating the parenthesis sequences of its subtrees. If we obtain a new parenthesis sequence by changing the order of concatenating subtree parenthesis sequences, then the tree corresponding to the new parenthesis sequence is isomorphic to the tree corresponding to the original parenthesis sequence.

### Principle 2

Tree isomorphism is transitive. That is, if $T_1$ is isomorphic to $T_2$, and $T_2$ is isomorphic to $T_3$, then $T_1$ is isomorphic to $T_3$.

### Corollary

Consider the recursive algorithm for computing tree parenthesis sequences. When backtracking, we concatenate the parenthesis sequences of subtrees. If during concatenation we first concatenate the sequences in lexicographic order, and record the final result as $NAME$.

Take the $NAME$ of the subtree rooted at node $r$ as the $NAME$ of node $r$, denoted as $NAME(r)$. Then for rooted trees $T_1(V_1,E_1,r_1)$ and $T_2(V_2,E_2,r_2)$, if $NAME(r_1)=NAME(r_2)$, then $T_1$ and $T_2$ are isomorphic.

### Naming Algorithm

???+ note "Implementation"
    $$
    \begin{array}{ll}
    1 & \textbf{Input. } \text{A rooted tree }T\\
    2 & \textbf{Output. } \text{The name of rooted tree }T\\
    3 & \text{ASSIGN-NAME(u)}\\
    4 & \qquad \text{if  } u \text{  is a leaf}\\
    5 & \qquad \qquad \text{NAME(} u \text{) = (0)}\\
    6 & \qquad \text{else }\\
    7 & \qquad \qquad \text{for all child } v \text{ of } u\\
    8 & \qquad \qquad \qquad \text{ASSIGN-NAME(}v\text{)}\\
    9 & \qquad \text{sort the names of the children of }u\\
    10 & \qquad \text{concatenate the names of all children }u\text{ to temp}\\
    11 & \qquad \text{NAME(} u \text{) = (temp)}
    \end{array}
    $$

### AHU Algorithm

???+ note "Implementation"
    $$
    \begin{array}{ll}
    1 & \textbf{Input. } \text{Two rooted trees }T_1(V_1,E_1,r_1)\text{ and }T_2(V_2,E_2,r_2) \\
    2 & \textbf{Output. } \text{Whether these two trees are isomorphic}\\
    3 & \text{AHU}(T_1(V_1,E_1,r_1), T_2(V_2,E_2,r_2))\\
    4 & \qquad \text{ASSIGN-NAME(}r_1\text{)}\\
    5 & \qquad \text{ASSIGN-NAME(}r_2\text{)}\\
    6 & \qquad \text{if  NAME}(r_1) = \text{NAME}(r_2)\\
    7 & \qquad \qquad \text{return true}\\
    8 & \qquad \text{else}\\
    10 & \qquad \qquad \text{return false}
    \end{array}
    $$

### Complexity Proof

For a rooted tree with $n$ nodes, assuming it is a chain, the maximum length of a node's name can be $n$. Thus, the complexity of the ASSIGN-NAME algorithm is a constant multiple of $1+2+\cdots+n$, i.e., $\Theta(n^2)$. Therefore, the complexity of the naive AHU algorithm is $O(n^2)$.

## Optimized AHU Algorithm

The drawback of the naive AHU algorithm is that the length of the tree's $NAME$ may become too long. We can optimize this.

### Principle 1

Perform level decomposition on the tree. Nodes at level $i$ have the shortest distance to the root equal to $i$. The $NAME$ of a node at level $i$ can be obtained **solely** by concatenating the $NAME$s of nodes at level $i+1$.

### Principle 2

Within the same level, a node's $NAME$ can be uniquely identified by its rank within the level.

**Note**, the rank is for both trees. Assuming node $u$ is at level $i$, then node $u$'s rank equals the number of nodes at level $i$ in both $T_1$ and $T_2$ whose $NAME$ is smaller than $NAME(u)$.

### Corollary

We can replace the original $NAME$ of a node with its rank within the level, and replace the concatenation of node $NAME$s with appending elements to an array.

Using integers and arrays instead of strings does not affect the correctness of the algorithm, while significantly reducing the complexity.

### Complexity Proof

First, note that the total length of $NAME$s obtained by concatenation at level $i$ equals the sum of degrees of nodes at level $i$, i.e., the total number of nodes at level $i+1$. Let this be denoted by $L_i$. The next step of the algorithm treats these $NAME$s as strings (arrays), sorts them, and replaces them with their rank within the level (i.e., remapping to a number). The following lemma shows the complexity of sorting $m$ strings with total length $L$:

1.  We can use radix sort to complete the sorting in $O(L + |\Sigma|)$ time, where $|\Sigma|$ is the size of the character set. (See the references for some implementation details.)
2.  We can use quicksort to complete the sorting in $O(L \log m)$ time. The rough idea of the proof is that the height of the quicksort recursion tree is $O(\log m)$, and the complexity of comparing two strings of lengths $\ell_1$ and $\ell_2$ is $O(\min\{\ell_1,\ell_2\})$.

In the AHU algorithm, the character set size of strings at level $i$ is at most the number of nodes at level $i+1$, i.e., $L_i$. Therefore, the complexity of radix sort is linear. Since $\sum_i L_i = O(n)$, and summing the complexity of each level shows that if using radix sort for strings, the total complexity of the algorithm is $T(n) = O(n)$. Similarly, if using quicksort to sort strings, then $T(n) = O(n \log n)$.

## Example Problems

[SPOJ-TREEISO](https://www.spoj.com/problems/TREEISO/en/)

Problem translation: Given two unrooted trees, determine whether the two trees are isomorphic.

???+ note "Reference Code"
    ```cpp
    --8<-- "docs/graph/code/tree-ahu/tree-ahu_1.cpp"
    ```

## References

Most of this article is translated from [Paper](http://wwwmayr.in.tum.de/konferenzen/Jass08/courses/1/smal/Smal_Paper.pdf) and [Slide](https://logic.pdmi.ras.ru/~smal/files/smal_jass08_slides.pdf). The proofs in the references are more comprehensive and rigorous. This article has made some simplifications.

For the complexity analysis of the AHU algorithm and the linear-time radix sort algorithm for strings, see Section 3.2 "Radix Sorting" in The Design and Analysis of Computer Algorithms, including Example 3.2.