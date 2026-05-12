author: xiezheyuan

Problems combining segment trees with offline queries also appear in OI. This technique is also called segment-tree divide and conquer.

If you need to maintain information that appears during certain time intervals, and you need to answer the combined information at some time under an offline setting, you can consider using segment-tree divide and conquer.

In practice, segment-tree divide and conquer often has the following uses:

1.  Simulating deletion operations with a data structure that originally does not support deletion but supports rollback. For example, a naive DSU cannot efficiently support edge deletion.
2.  Computing data with different attributes separately. For example, computing the answer for all colors except one specified color.

It is fine if these are not clear yet; both uses will be explained in the examples.

## Procedure

First build a segment tree over time. Each node maintains a `vector` storing the information that exists during this time interval.

Inserting information into the segment tree is similar to a normal segment tree range update.

Then consider how to process the combined information over every time interval. Start divide-and-conquer from the root, maintain the current combined information, and when visiting a node, merge all information stored at that node. When backtracking, undo this part of the contribution. Finally, when a leaf is reached, the current combined information is the answer for that time.

If changing information has time complexity $O(T(n))$, we can keep the changes on a stack and undo them in $O(T(n))$ time. Rollback does not preserve amortized complexity.

The total time complexity of the whole divide-and-conquer process is $O(n\log n(T(n) + M(n)))$, where $O(M(n))$ is the time complexity of merging information, and the space complexity is $O(n\log n)$.

??? note "Implementation"
    ```cpp
    #define ls (i << 1)
    #define rs (i << 1 | 1)
    #define mid ((l + r) >> 1)
    
    vector<Object> tree[N << 2];  // Segment tree
    
    void update(int ql, int qr, Object obj, int i, int l, int r) {  // Insert
      if (ql <= l && r <= qr) {
        tree[i].push_back(obj);
        return;
      }
      if (ql <= mid) update(ql, qr, obj, ls, l, mid);
      if (qr > mid) update(ql, qr, obj, rs, mid + 1, r);
    }
    
    stack<Object> sta;  // Stack for rollback
    Object now;         // Current merged information
    Object ans[N];      // Answers
    
    void solve(int i, int l, int r) {
      auto lvl = sta.size();  // Record the rollback point
      for (Object x : tree[i]) sta.push(now), now = Merge(now, x);  // Merge information
      if (l == r)
        ans[i] = now;  // Record the answer
      else
        solve(ls, l, mid), solve(rs, mid + 1, r);  // Divide and conquer
      while (sta.size() != lvl) {                  // Roll back information
        now = sta.top();
        sta.pop();
      }
    }
    ```

## Examples

???+ note "[Luogu P5787 Bipartite Graph / Template Segment-Tree Divide and Conquer](https://www.luogu.com.cn/problem/P5787)"
    Maintain an undirected graph with $n$ vertices and $m$ edges. The $i$-th edge is $(x_i,y_i)$ and exists during time interval $[l_i,r_i)$; it disappears at all other times.
    
    For every time, output `Yes` if the graph is bipartite at that time, otherwise output `No`.
    
    ??? note "Solution"
        Use species DSU to maintain whether a graph is bipartite, then apply segment-tree divide and conquer.
        
        Note that rollback DSU cannot use path compression; it can only use union by rank.
    
    ??? note "Reference Code"
        ```cpp
        --8<-- "docs/topic/code/segment-tree-offline/segment-tree-offline_1.cpp"
        ```

???+ note "Color Restriction"
    Given an undirected graph with $n$ vertices and $m$ edges. There are $k$ colors numbered $0\sim k-1$, and every edge has one color.
    
    For each color, determine whether deleting all edges of this color makes the resulting graph connected, and whether it makes the resulting graph a tree.
    
    Output the number of colors for which the graph is connected after deletion, and the number of colors for which the graph is a tree after deletion.
    
    ??? note "Solution"
        For each color, create a time during which edges of this color do not exist and all other edges do. Maintain this with a DSU.
    
    ??? note "Reference Code"
        ```cpp
        --8<-- "docs/topic/code/segment-tree-offline/segment-tree-offline_2.cpp"
        ```

???+ note "[Luogu P4219 \[BJOI2014\] Great Fusion](https://www.luogu.com.cn/problem/P4219)"
    Maintain a forest with $n$ vertices, initially all isolated.
    
    There are $q$ operations:
    
    -   `A x y` adds an edge $(x,y)$.
    -   `Q x y` outputs the number of paths passing through edge $(x,y)$.
    
    Offline processing is allowed.
    
    ??? note "Solution"
        Since offline processing is allowed, segment-tree divide and conquer is natural.
        
        Then consider how to support Q operations. If edge $(x,y)$ does not exist, the answer is the size of the connected component containing $x$ multiplied by the size of the connected component containing $y$. This can be maintained with DSU.
        
        Therefore, split Q into three times: $k-1,k,k+1$. Here $k-1$ is the end time of this edge, and $k+1$ is the start time of this edge. Thus at time $k$, this edge is absent, which is exactly when the query should be answered.
    
    ??? note "Reference Code"
        ```cpp
        --8<-- "docs/topic/code/segment-tree-offline/segment-tree-offline_3.cpp"
        ```

???+ note "[Luogu P2056 \[ZJOI2007\] Hide and Seek](https://www.luogu.com.cn/problem/P2056)"
    Given a tree with $n$ vertices. Each vertex has one of two colors, black or white. Initially every vertex is black. There are $q$ operations:
    
    -   `C x` flips the color of vertex $x$.
    -   `G` queries the farthest distance between two black vertices in the tree. In particular, if no black vertex exists, output $-1$.
    
    Offline processing is allowed.
    
    ??? note "Solution"
        First consider how to maintain the diameter of a set of vertices. We use the following conclusion:
        
        > For a set $S$ and a singleton set $\{P\}$, if the diameter of $S$ is $(U,V)$, then the diameter of the point set $S\cap\{P\}$ can only be one of $(U,V),(U,P)$, or $(V,P)$.
        
        Now solve the original problem. Maintain the set of black vertices, and maintain several time intervals during which each vertex belongs to the black set (specifically, use a bucket to record the last time it entered the black set).
        
        Then naturally process offline: insert all time intervals into the segment tree. Perform divide and conquer on the segment tree; each segment-tree node records the vertices newly added during the current time interval. For each newly added vertex, use the conclusion above to find the two endpoints of the new vertex-set diameter.
        
        Rollback is straightforward: use a stack to record changes to the diameter endpoints.
    
    ??? note "Reference Code"
        ```cpp
        --8<-- "docs/topic/code/segment-tree-offline/segment-tree-offline_4.cpp"
        ```

## Exercises

-   [CF601E A Museum Robbery](https://codeforces.com/problemset/problem/601/E): segment-tree divide and conquer + knapsack DP.
-   [CF19E Fairy](https://codeforces.com/problemset/problem/19/E): segment-tree divide and conquer + species DSU.
-   [Luogu P5227 \[AHOI2013\] Connected Graph](https://www.luogu.com.cn/problem/P5227): segment-tree divide and conquer + DSU.
-   [Luogu P4319 Changing Roads](https://www.luogu.com.cn/problem/P4319): segment-tree divide and conquer + Link-Cut Tree to maintain the minimum spanning tree.
-   [Luogu P3733 \[HAOI2017\] Eight Verticals and Eight Horizontals](https://www.luogu.com.cn/problem/P3733): segment-tree divide and conquer + linear basis.

**Part of this page refers to the blog post [Deleting from a data structure](https://cp-algorithms.com/data_structures/deleting_in_log_n.html), licensed under CC-BY-SA 4.0.**
