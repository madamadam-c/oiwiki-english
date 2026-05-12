The Steiner tree problem is a combinatorial optimization problem, similar to the minimum spanning tree, representing a shortest network. The minimum spanning tree seeks the shortest network connecting all given points from a given set of points and edges. The minimum Steiner tree allows adding extra points beyond the given points to minimize the total cost of the resulting shortest network.

## Problem Introduction

In the early 19th century, Steiner, a famous geometer at the University of Berlin, studied a very simple yet illuminating problem: connecting three villages with roads of minimal total length. Mathematically, given three points $A$, $B$, $C$ in the plane, find a fourth point $P$ in the plane such that the sum $a + b + c$ is minimized, where $a$, $b$, $c$ are respectively the distances from $P$ to $A$, $B$, $C$.

The answer to the problem is: if each interior angle of triangle $\textit{ABC}$ is less than $120^\circ$, then $P$ is the point where the angles subtended by edges $\textit{AB}$, $\textit{BC}$, $\textit{AC}$ at $P$ are all $120^\circ$. If triangle $\textit{ABC}$ has an angle, say angle $C$, greater than or equal to $120^\circ$, then point $P$ coincides with vertex $C$.

### Problem Generalization

1.  In the Steiner problem, three fixed points $A, B, C$ are given. This problem naturally generalizes to the case of $n$ given points $A_1, A_2, \dots, A_n$; we need to find a point $P$ in the plane that minimizes the sum of distances $a_1 + a_2 + \dots + a_n$, where $a_i$ is the distance $PA_i$.

2.  Considering other related factors of points, a weight representation is introduced. The other related factors of $n$ points can be converted into a weight representation. Find a point $P$ in the plane that minimizes the sum of products of distance and weight $a_1 \cdot w_1 + a_2 \cdot w_2 + \dots + a_n \cdot w_n$, where $w_i$ is the weight of each point.

3.  Courant and Robbins proposed that the first generalization is superficial. To obtain a truly valuable generalization of the Steiner problem, we must abandon the search for a single point $P$ and instead consider a "road network" of minimum total length. Mathematically: given $n$ points $A_1, A_2, \cdots, A_n$, find the system of line segments of minimum total length that connects these $n$ points, such that any two points can be connected by a polygonal chain composed of line segments in the system. They called this new problem the **Steiner tree problem**. For $n$ given points, there will be at most $n - 2$ Steiner points. At most three edges pass through each Steiner point. If there are three edges, they intersect pairwise at $120^\circ$ angles; if there are two edges, this Steiner point must be one of the given points, and the two edges must intersect at an angle greater than or equal to $120^\circ$.

Connecting more than three points with the shortest network

![steiner-tree1](./images/steiner-tree-1.svg)

In the first case, the solution consists of five line segments, with two Steiner points (red $s_1, s_2$) where three line segments intersect at $120^\circ$ angles. The second case's solution contains three Steiner points. In the third case, one or more Steiner points may degenerate, or be replaced by one or more given points.

We present the Steiner tree problem in graph-theoretic terms.

![steiner-tree2](./images/steiner-tree-2.svg)

For form one, if the key points are $\{1, 2, 3, 4\}$, we can find that the minimum edge weight sum directly connecting these four key points is 12, which is clearly not optimal. If we consider using node 5, the minimum edge weight sum becomes 9, yielding a better answer.

For form two, if the key points are $\{1, 2, 3, 4\}$, we can find that some of these four key points are not even directly connected; we must consider using Steiner points. Taking node 5 into account gives a minimum edge weight sum of 9.

Moreover, we can observe that in both figures, the Steiner points for nodes 1 and 4 have degenerated, being replaced by nodes 1 or 4.

## Example Problems

First, let's use a template problem to familiarize everyone with the minimum Steiner tree problem. See [Template: Minimum Steiner Tree](https://www.luogu.com.cn/problem/P6192).

The problem is clear: given $n$ points and $k$ key points in a connected graph $G$, connect the $k$ key points such that the sum of edge weights in the resulting tree is minimized.

Based on the above knowledge, we know that directly connecting the $k$ key points does not necessarily produce the minimum weight sum, or these $k$ key points may not be directly (adjacent) connected. Therefore, we should use the remaining $n - k$ points.

We use state compression dynamic programming to solve. Let $f(i, S)$ represent the minimum edge weight sum of a tree rooted at $i$ that contains all points in set $S$.

Consider the state transitions:

-   First, transition for connected subsets: $f(i, S) \leftarrow \min(f(i, S), f(i, T) + f(i, S - T))$.

-   Perform edge relaxation on the current connected subset: $f(i, S) \leftarrow \min(f(i, S), f(j, S) + w(j, i))$. In the code below, a `tree[tot]` is used to record the information of two connected nodes $i, j$.

??? note "Reference Implementation"
    ```cpp
    --8<-- "docs/graph/code/steiner-tree/steiner-tree_1.cpp"
    ```

Another classic problem [WC2008 Tour Plan](https://www.luogu.com.cn/problem/P4294).

This problem asks for a Steiner tree with minimum point weight sum. Let $f(i, S)$ represent the minimum point weight sum of a tree rooted at $i$ that contains all points in set $S$. Let $a_i$ represent the point weight.

Consider the state transitions:

-   $f(i, S) \leftarrow \min(f(i, S), f(i, T) + f(i, S - T) - a_i)$. Since when merging, the same point $a_i$ gets added twice, we subtract it.

-   $f(i, S) \leftarrow \min(f(i, S), f(j, S) + w(j, i))$.

It can be seen that the state transitions are similar to the template problem above. The difficulty is outputting the answer. During DP, we also need to record the path.

Use `pre[i][s]` to record the information about the node and set when transitioning to node $i$ as root with connected state set $s`. After DP finishes, start from `pre[root][S]`, find nodes connected to points in the set and gradually decompose set $S`. Use an array `ans` to record the points used. When the set decomposition is complete, the search ends.

??? note "Reference Implementation"
    ```cpp
    --8<-- "docs/graph/code/steiner-tree/steiner-tree_2.cpp"
    ```

## Practice Problems

-   [Template: Minimum Steiner Tree](https://www.luogu.com.cn/problem/P6192)
-   [WC2008 Tour Plan](https://www.luogu.com.cn/problem/P4294)
-   [JLOI2015 Pipeline Connection](https://loj.ac/problem/2110)
-   [APIO2013 Robot](https://www.luogu.com.cn/problem/P3638)