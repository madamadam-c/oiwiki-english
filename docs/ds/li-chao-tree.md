## Introduction

???+ note "[Luogu 4097 \[HEOI2013\]Segment](https://www.luogu.com.cn/problem/P4097)"
    Maintain two operations in the Cartesian plane (forced online):
    
    1.  Add a line segment to the plane. Let the label of the $i$-th inserted segment be $i$, and let its two endpoints be $(x_0,y_0)$ and $(x_1,y_1)$.
    2.  Given a number $k$, query the label of the segment whose intersection with the line $x = k$ has the maximum y-coordinate. If multiple segments attain the maximum intersection y-coordinate, output the smallest label among them. In particular, if no segment intersects the given line, output $0$.
    
    Constraints: total number of operations $1 \leq n \leq 10^5$, $1 \leq k, x_0, x_1 \leq 39989$, $1 \leq y_0, y_1 \leq 10^9$.

We can see that a traditional segment tree cannot maintain this information well. In this situation, the **Li Chao segment tree** comes into play.

## Procedure

We can transform the task into maintaining the following operations:

-   Add a linear function with domain $[l,r]$.
-   Given $k$, among all linear functions whose domains contain $k$, find the one with the maximum value at $x=k$; if multiple functions have the same value, choose the smallest label.

???+ warning "Note"
    When a segment is perpendicular to the $x$-axis, division by zero occurs. Suppose the two endpoints of the segment are $(x,y_0)$ and $(x,y_1)$, with $y_0<y_1$. Insert the linear function with domain $[x,x]$, $f(x)=0\cdot x+y_1$.

For range updates, following the usual segment-tree approach to interval problems, assign each node a lazy tag. The lazy tag of node $i$ is a line segment, denoted $l_i$, meaning that the whole interval represented by this node should be updated with $l_i$.

Now we need to insert a segment $f$. Consider a segment tree interval that is fully covered by the new segment $f$. If the interval has no tag, simply set its update tag to this segment.

If the interval already has a tag, the tags are hard to merge, so we can only push the tag down. But the child nodes also have their own tags and may also conflict, so we need to push tags down recursively.

![](images/li-chao-tree-1.png)

As shown in the figure, depending on whether the value of the new segment $f$ is greater than the old tag $g$, we can divide the current interval into two subintervals. **At least one subinterval is definitely fully contained in the left or right child interval**. In other words, among the two segments, at least one segment can only possibly become the answer in the left interval, or only possibly become the answer in the right interval. We recursively update the corresponding child with that segment, and use the other segment as the lazy tag for the whole interval. This guarantees the complexity of recursive pushing. A segment is pushed down only when it can only become the answer in the left or right interval, so there is no risk of missing any segment.

Specifically, let the midpoint of the current interval be $m$. Compare the value of the new segment $f$ at the midpoint with the value of the current best segment $g$ at the midpoint.

If the new segment $f$ is better, swap $f$ and $g$. Now consider the case where $f$ is no better than $g$ at the midpoint:

1.  If $f$ is better at the left endpoint, then $f$ and $g$ must intersect in the left half, and $f$ can only be better than $g$ in the left interval. Recurse into the left child and push it down.
2.  If $f$ is better at the right endpoint, then $f$ and $g$ must intersect in the right half, and $f$ can only be better than $g$ in the right interval. Recurse into the right child and push it down.
3.  If $g$ is better at both endpoints, then $f$ cannot become the answer and no further pushdown is needed.

Besides these cases, there is also the case where $f$ and $g$ intersect exactly at the midpoint. In implementation, this can be classified as the case where $f$ is no better than $g$ at the midpoint; the result will recursively push down toward the endpoint where $f$ is better.

Finally, use $g$ as the lazy tag of the current interval.

Pushing down tags:

???+ note "Implementation"
    ```cpp
    constexpr double eps = 1e-9;
    
    int cmp(double x, double y) {  // Floating-point numbers cause precision errors
      if (x - y > eps) return 1;
      if (y - x > eps) return -1;
      return 0;
    }
    
    //...
    
    void upd(int root, int cl, int cr, int u) {  // Modify an interval fully covered by the segment
      int &v = s[root], mid = (cl + cr) >> 1;
      int bmid = cmp(calc(u, mid), calc(v, mid));
      if (bmid == 1 || (!bmid && u < v))  // Remember to compare segment labels in this problem
        swap(u, v);
      int bl = cmp(calc(u, cl), calc(v, cl)), br = cmp(calc(u, cr), calc(v, cr));
      if (bl == 1 || (!bl && u < v)) upd(root << 1, cl, mid, u);
      if (br == 1 || (!br && u < v)) upd(root << 1 | 1, mid + 1, cr, u);
      // At most one of the two conditions above is true, which guarantees the Li Chao tree complexity
    }
    ```

Splitting a segment:

???+ note "Implementation"
    ```cpp
    void update(int root, int cl, int cr, int l, int r,
                int u) {  // Locate intervals fully covered by the inserted segment
      if (l <= cl && cr <= r) {
        upd(root, cl, cr, u);  // Fully covers the current interval; update its tag
        return;
      }
      int mid = (cl + cr) >> 1;
      if (l <= mid) update(root << 1, cl, mid, l, r, u);  // Recursively split the interval
      if (mid < r) update(root << 1 | 1, mid + 1, cr, l, r, u);
    }
    ```

Note that a lazy tag is not equivalent to the segment with the maximum value at the midpoint of the interval.

![](images/li-chao-tree-2.png)

As shown in the figure, after adding the yellow segment, only the tag of the red node is updated, while the tags of the green nodes have not changed. However, at the midpoints of the second, third, and fourth green intervals, the yellow segment clearly has the maximum value.

During queries, use the idea of tag permanence: among the tag segments of all segment tree intervals containing $x$ (no more than $O(\log n)$ intervals), compare them to obtain the final answer.

Query:

???+ note "Implementation"
    ```cpp
    pdi query(int root, int l, int r, int d) {  // Query
      if (r < d || d < l) return {0, 0};
      int mid = (l + r) >> 1;
      double res = calc(s[root], d);
      if (l == r) return {res, s[root]};
      return pmax({res, s[root]}, pmax(query(root << 1, l, mid, d),
                                       query(root << 1 | 1, mid + 1, r, d)));
    }
    ```

According to the description above, the time complexity of a query is clearly $O(\log n)$. During insertion, the original segment must be split into $O(\log n)$ intervals, and for each interval we spend another $O(\log n)$ time recursively pushing down. Therefore, the insertion time complexity is $O(\log^2 n)$.

??? note "Reference Code for [\[HEOI2013\]Segment](https://www.luogu.com.cn/problem/P4097)"
    ```cpp
    --8<-- "docs/ds/code/li-chao-tree/li-chao-tree_1.cpp"
    ```

## Merging

Similar to merging ordinary segment trees, define the following procedure to merge two Li Chao segment tree nodes $u,v$, using $u$ as the new root.

1.  If $v$ is empty, end the procedure.

2.  If $u$ is empty, copy $v$ to $u$.

3.  Insert the segment corresponding to $v$ into the subtree rooted at $u$.

4.  Recursively merge the corresponding left and right subtrees of $u,v$.

If the total number of nodes involved in merging several Li Chao segment trees is $n$, then the complexity of this procedure is $O(n\log n)$. For any node corresponding to a segment in the tree, each time it is moved, either its depth increases by $+1$, or it is deleted directly from the tree. Both operations cost $O(1)$, and the depth of each node is at most $O(\log n)$, giving the complexity above.

???+ note "Implementation"
    ```cpp
    void upd(int &root, int cl, int cr,
             int u) {  // Merging multiple Li Chao segment trees; use dynamic node allocation.
      static int idx = 0;
      if (!root) {
        s[root = ++idx] = u;
        return;
      }
      int &v = s[root], mid = (cl + cr) >> 1;
      int bmid = cmp(calc(u, mid), calc(v, mid));
      if (bmid == 1 || (!bmid && u < v)) swap(u, v);
      int bl = cmp(calc(u, cl), calc(v, cl)), br = cmp(calc(u, cr), calc(v, cr));
      if (bl == 1 || (!bl && u < v)) upd(ls[root], cl, mid, u);
      if (br == 1 || (!br && u < v)) upd(rs[root], mid + 1, cr, u);
    }
    
    int merge(int &u, int &v, int l, int r) {
      if (!u || !v) {
        return u + v;
      }
      if (l == r) {
        int b = cmp(calc(s[v], l), calc(s[u], l));
        if (b == 1 || (!b && s[v] < s[u])) return v;
        return u;
      }
      upd(u, l, r, s[v]);
      int mid = (l + r) >> 1;
      ls[u] = merge(ls[u], ls[v], l, mid);
      rs[u] = merge(rs[u], rs[v], mid + 1, r);
      return u;
    }
    ```

## Exercises

[「JSOI2008」Blue Mary Starts a Company](https://www.luogu.com.cn/problem/P4254)

[「CodeChef」TSUM2 Sum on Tree](https://www.codechef.com/problems/TSUM2)

[「USACO13MAR」Hill Walk G](https://www.luogu.com.cn/problem/P3081)

[「CF932F」Escape Through Leaf](https://codeforces.com/problemset/problem/932/F)
