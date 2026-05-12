author: hsfzLZH1, Ir1d, JosephusW

A k-D Tree (KDT, k-Dimensional Tree) is a data structure that can **efficiently process information in $k$-dimensional space**.

When the number of nodes $n$ is much larger than $2^k$, k-D Tree has good time efficiency in practice.

In algorithm contest problems, usually $k=2$. When analyzing time complexity on this page, $k$ is treated as a constant.

## Building the Tree

A k-D Tree has the shape of a binary search tree, and every node in the binary search tree corresponds to a point in $k$-dimensional space. The points in each subtree all lie inside a $k$-dimensional hyperrectangle, and all points inside that hyperrectangle also belong to this subtree.

Suppose we already know the $k$-dimensional coordinates of $n$ distinct points. To build them into a k-D Tree, proceed as follows:

1.  If there is only one point in the current hyperrectangle, return this point.

2.  Choose one dimension and split the current hyperrectangle into two hyperrectangles along this dimension.

3.  Choose the splitting point: choose a point by its value in the selected dimension. Points whose value in this dimension is smaller than this point go into one hyperrectangle (the left subtree), and the remaining points go into the other hyperrectangle (the right subtree).

4.  Use the selected point as the root of this subtree, recursively build the left and right subtrees for the two split hyperrectangles, and maintain subtree information.

For easier understanding, consider an example with $k=2$.

![](./images/kdt1.jpg)

The constructed k-D Tree may have the following shape:

![](./images/kdt2.jpg)

Here, the coordinate on each tree node is the coordinate of the chosen splitting point, and the $x$ or $y$ beside each non-leaf node is the chosen splitting dimension.

The complexity of this direct approach is not guaranteed. For steps $2,3$, we introduce two optimizations:

1.  Choose the $k$ dimensions cyclically, ensuring that every dimension is split once in any consecutive $k$ levels.
2.  Each time a splitting point is chosen in a dimension, choose the **median** in that dimension, so the sizes of the left and right subtrees are as equal as possible.

After using optimization $2$, the height of the constructed k-D Tree is at most $\log n+O(1)$.

Now, the bottleneck in building a k-D Tree is quickly selecting the median in a dimension and placing elements whose value in that dimension is smaller than the median to the left of the median, and the rest to the right. If the `sort` function is used to sort by that dimension every time, the time complexity is $O(n\log^2 n)$. In fact, finding the median among $n$ elements once and placing it in its correct position after sorting can be done in $O(n)$ time.

Let us recall the idea of quicksort. Each time, we choose a number, put numbers smaller than it to its left and numbers greater than it to its right, ensuring that this number is in its correct sorted position, and then recursively sort the values on the left and right. The expected complexity is $O(n\log n)$. However, since a k-D Tree only requires the median to be in its correct sorted position, we only need to recursively sort the **side** containing the median. It can be proved that the expected complexity of this is $O(n)$. In the `algorithm` library, there is a function `nth_element()` that implements the same functionality. To find the value at position `s[mid]` after sorting the values between `s[l]` and `s[r]` according to comparator `cmp`, while ensuring values to the left of `s[mid]` are smaller than `s[mid]` and values to the right are greater than `s[mid]`, write `nth_element(s+l,s+mid,s+r+1,cmp)`.

With this idea, the time complexity of building a k-D Tree is $O(n\log n)$.

## Operations in High-Dimensional Space

When querying some information about all points inside a high-dimensional rectangular region, record the maximum and minimum coordinate values in every dimension for each node's subtree. If the rectangle corresponding to the current subtree has no intersection with the query rectangle, do not continue searching its subtree. If the rectangle corresponding to the current subtree is fully contained in the query rectangle, return the sum of weights of all points in the current subtree. Otherwise, check whether the current point is inside the query rectangle, update the answer, and recursively search for the answer in the left and right subtrees.

??? note "Implementation"
    ```cpp
    int query(int p) {
      if (!p) return 0;
      bool flag{false};
      for (int k : {0, 1}) flag |= (!(l.x[k] <= t[p].L[k] && t[p].R[k] <= h.x[k]));
      if (!flag) return t[p].sum;
      for (int k : {0, 1})
        if (t[p].R[k] < l.x[k] || h.x[k] < t[p].L[k]) return 0;
      int ans{0};
      flag = false;
      for (int k : {0, 1}) flag |= (!(l.x[k] <= t[p].x[k] && t[p].x[k] <= h.x[k]));
      if (!flag) ans = t[p].v;
      return ans += query(t[p].l) + query(t[p].r);
    }
    ```

### Complexity Analysis

First consider the two-dimensional case. When querying a rectangle $R$, we divide nodes in the k-D Tree into three categories:

1.  No intersection with $R$.
2.  Completely contained by $R$.
3.  Partially contained by $R$.

Clearly, the complexity of a single query is the number of nodes in category 3. Notice that the rectangles of category-3 nodes either completely contain $R$, or neither contains the other. The former clearly has only $O(h)=O(\log n)$ nodes, so now we analyze the number of the latter.

First, we may shift all sides of the rectangle by $\epsilon$, so that the query rectangle does not pass through any existing point. This clearly does not affect the set of points covered by the rectangle query.

Notice that for the rectangles corresponding to category-3 nodes where neither rectangle contains the other, one side of $R$ must pass through them. Therefore, we only need to compute, for each side of $R$, how many rectangles it passes through, namely the maximum number of point-corresponding rectangles that any axis-parallel line segment can pass through.

Consider a node $u$. It has four grandchildren, and from u to each grandchild, the space has been split once in each of the two dimensions. By observation, if a rectangle is divided into four subrectangles in this way, an axis-parallel line segment passes through at most two regions. That is, a query starting from $u$ enters at most two grandchildren that still contain category-3 nodes (if the segment exactly coincides with a splitting boundary this is not necessarily true, but our operation of shifting the query-rectangle boundary eliminates this case).

Because each point is the median of its entire subtree in the current splitting dimension when building the tree, the subtree size must be halved. Thus, if the subtree size of $u$ is $n$, we can write the recurrence:

$$
T(n)=2T(n/4)+O(1)
$$

By the master theorem, $T(n)=O(\sqrt{n})$.

Generalizing the recurrence to $k$ dimensions gives $T(n)=2^{k-1}T(n/2^k)+O(1)$, so $T(n)=O(n^{1-\frac1k})$ (treating $k$ as a constant).

### Insertion/Deletion

If the maintained set of $k$-dimensional points is mutable, meaning some points may be inserted or deleted, then the balance of the k-D Tree cannot be guaranteed. Due to the structure of the k-D Tree, rotations are not supported, and randomized priorities similar to those in FHQ Treap also cannot guarantee the complexity. There are two common maintenance methods for this.

???+ note "Note"
    Many contestants use a scapegoat-tree structure for maintenance. However, note that in the preceding complexity analysis, the child subtree size must be strictly halved, meaning the tree height must be exactly $\log n+O(1)$, while a scapegoat tree only guarantees height $O(\log n)$, so the query complexity cannot be guaranteed.

#### Square-Root Rebuilding

When inserting, first store the points to be inserted, and rebuild once every $B$ insertions.

For deletion, just mark the point. If the requirement is stricter, maintain how many points in the tree have been deleted and rebuild when this number reaches $B$.

The amortized modification complexity is $O(n\log n/B)$, and query complexity is $O(B+n^{1-\frac1k})$. If the numbers of modifications and queries are of the same order, then $B=O(\sqrt{n\log n})$ is optimal (modification $O(\sqrt{n\log n})$, query $O(\sqrt{n\log n}+n^{1-\frac1k})$).

#### Binary Grouping

Consider maintaining several k-D Trees whose sizes are powers of $2$, and whose total size is $n$.

When inserting, add a new k-D Tree of size $1$, and then repeatedly merge trees of the same size (flatten and rebuild directly). In implementation, this can be rebuilt only once.

It is easy to see that the sizes of the trees to be merged must start from $2^0$ and have consecutive exponents. The complexity is similar to binary addition and is amortized $O(n\log^2 n)$, because rebuilding itself has a $\log$ factor.

When querying, query each tree separately. The complexity is $O\left(\sum_{i\geq0} (\frac n{2^i})^{1-\frac1k}\right)=O(n^{1-\frac1k})$.

### Example Problem

???+ note "[Luogu P4148 Simple Problem](https://www.luogu.com.cn/problem/P4148)"
    On an initially all-$0$ two-dimensional $n\times n$ matrix, perform $q$ operations. Each operation is one of the following two types:
    
    1.  `1 x y A`: add to the number at coordinate $(x,y)$ the value $A$.
    2.  `2 x1 y1 x2 y2`: output the sum of the numbers inside the rectangle with $(x1,y1)$ as its lower-left corner and $(x2,y2)$ as its upper-right corner, including the rectangle boundary.
    
    The problem is forced online. The memory limit is `20M`. It is guaranteed that the answer and all intermediate values fit in `int`.
    
    $1\le n\le 500000 , 1\le q\le 200000$

The `20M` space limit rules out all tree-of-tree approaches, and forced online rules out CDQ divide and conquer, so only a k-D Tree can be used.

The following is reference code using binary grouping.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/ds/code/kdt/kdt_3.cpp"
    ```

## Nearest-Neighbor Queries

???+ warning "Warning"
    The worst-case time complexity of a single nearest-point query with a k-D Tree is still $O(n)$, but it is nevertheless an excellent heuristic solution. Please be careful when using it. The explanation of nearest-neighbor queries here is only intended to deepen understanding of the k-D Tree structure.

???+ note "Example Problem [Luogu P1429 Closest Pair of Points in the Plane (Enhanced)](https://www.luogu.com.cn/problem/P1429)"
    Given $n$ points $(x_i,y_i)$ on the plane, find the [Euclidean distance](../geometry/distance.md) between the closest pair of points on the plane.
    
    $2\le n\le 200000 , 0\le x_i,y_i\le 10^9$

First, build a 2-D Tree for these $n$ points.

Enumerate each node. For each node, find the point not equal to this node with minimum distance from it, and the answer can be obtained. Brute-force traversal of every node in the 2-D Tree for each query takes $O(n)$ time, so pruning is needed. We can maintain the minimum and maximum coordinate values in each dimension for all nodes in a subtree. Suppose the distance of the closest pair found so far is $ans$. If the **minimum** distance from the query point to the rectangle containing all points in the subtree is greater than or equal to $ans$, then this subtree cannot contain an answer, so the search does not enter this subtree.

In addition, a heuristic search method can be used: if both subtrees of a node may contain the answer, search the subtree whose rectangle is closest to the query point first. We can regard **the minimum distance from the query point to the rectangle corresponding to a subtree as the evaluation function for this problem**.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/ds/code/kdt/kdt_1.cpp"
    ```

???+ note "Example Problem [CQOI2016 K-th Farthest Point Pair](https://loj.ac/problem/2043)"
    Given $n$ points $(x_i,y_i)$ on the plane, find the distance of the $k$-th farthest unordered pair of points under Euclidean distance.
    
    $n\le 100000 , 1\le k\le 100 , 0\le x_i,y_i<2^{31}$

Similar to the previous example problem, the task changes from closest pair to $k$-th farthest pair, and the evaluation function becomes the farthest distance from the query point to the rectangular region corresponding to a subtree. Use a min-heap to maintain the distances of the current top $k$ farthest point pairs found. If the distance of the currently found point pair is greater than the heap top, pop the heap top and insert this distance. Similarly, use the distance at the heap top for pruning.

Because the problem emphasizes unordered point pairs, swapping the order of the two points still gives the same point pair. Thus, each ordered point pair is counted twice, so the input $k$ should be multiplied by $2$.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/ds/code/kdt/kdt_2.cpp"
    ```

## Exercises

[SDOI2010 Hide and Seek](https://www.luogu.com.cn/problem/P2479)

[Violet Angel Doll / SJY Places Chess Pieces](https://www.luogu.com.cn/problem/P4169)

[National Training Team JZPFAR](https://www.luogu.com.cn/problem/P2093)

[BOI2007 Mokia](https://www.luogu.com.cn/problem/P4390)

[Luogu P4475 Chocolate Kingdom](https://www.luogu.com.cn/problem/P4475)

[CH Weak Province Mock Contest R2 TATT](https://www.luogu.com.cn/problem/P3769)
