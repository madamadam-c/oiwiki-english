author: Marcythm, Ir1d, Ycrpro, Xeonacid, konnyakuxzy, CJSoft, HeRaNO, ethan-enhe, ChungZH, Chrogeek, hsfzLZH1, billchenchina, orzAtalod, luoguojie, Early0v0, wy-luke

## introduce

Line segment tree is a data structure commonly used in algorithm competitions to maintain **interval information**.

The line segment tree can implement single point modification, interval modification, interval query (interval summation, interval maximum value, interval minimum value) and other operations within the time complexity of $O(\log N)$.

## The basic structure and construction of line segment trees

### process

The line segment tree divides each interval whose length is not $1$ into two left and right intervals for recursive solution, divides the entire line segment into a tree structure, and obtains the information of the interval by merging the information of the left and right intervals. This data structure can easily perform most interval operations.

There is a size-$5$ array $a=\{10,11,12,13,14\}$. To convert it into a line segment tree, there is the following method: set the root node number of the line segment tree to $1$, use array $d$ to save our line segment tree, and $d_i$ to save the value of the node numbered $i$ on the line segment tree (the value maintained by each node here is the sum of the intervals represented by this node).

We first give the shape of this line segment tree, as shown in the figure:

![](./images/segt1.svg)

The interval marked in red font in each node in the figure represents the position interval on the $a$ array governed by the node. For example, the interval governed by $d_1$ is $[1,5]$ ($a_1,a_2, \cdots ,a_5$), that is, the value stored in $d_1$ is $a_1+a_2+ \cdots +a_5$, and $d_1=60$ represents $a_1+a_2+ \cdots +a_5=60$.

It is not difficult to find through observation that the left child node of $d_i$ is $d_{2\times i}$, and the right child node of $d_i$ is $d_{2\times i+1}$. If $d_i$ represents the interval $[s,t]$ (that is, $d_i=a_s+a_{s+1}+ \cdots +a_t$), then the left child node of $d_i$ represents the interval $[ s, \frac{s+t}{2} ]$, and the right child node of $d_i$ represents the interval $[ \frac{s+t}{2} +1,t ]$.

During implementation, we consider recursive tree building. Assume that the current root node is $p$. If the length of the interval governed by the root node is already $1$, the node can be initialized directly according to the value of the corresponding position in the $a$ array. Otherwise, we divide the interval into two sub-intervals from the midpoint, enter the left and right sub-nodes to recursively build trees, and finally merge the information of the two sub-nodes.

### accomplish

The code implementation is given here, you can refer to the comments for understanding:

=== "C++"
    ```cpp
    void build(int s, int t, int p) {
      // Create a line segment tree for the interval [s,t], the current root number is p
      if (s == t) {
        d[p] = a[s];
        return;
      }
      int m = s + ((t - s) >> 1);
      // The shift operator has lower precedence than addition and subtraction, so parentheses are added
      // If written as (s + t) >> 1 it may exceed the range of int
      build(s, m, p * 2), build(m + 1, t, p * 2 + 1);
      // Recursively build trees for the left and right intervals
      d[p] = d[p * 2] + d[(p * 2) + 1];
    }
    ```

=== "Python"
    ```python
    def build(s, t, p):
        # Create a line segment tree for the interval [s,t], the current root number is p
        if s == t:
            d[p] = a[s]
            return
        m = s + ((t - s) >> 1)
        # The shift operator has lower precedence than addition and subtraction, so parentheses are added
        # If written as (s + t) >> 1 it may exceed the range of int
        build(s, m, p * 2)
        build(m + 1, t, p * 2 + 1)
        # Recursively build trees for the left and right intervals
        d[p] = d[p * 2] + d[(p * 2) + 1]
    ```

Regarding the space of the line segment tree: If heap storage is used ($2p$ is the left son of $p$, $2p+1$ is the right son of $p$), if there are $n$ leaf nodes, the maximum range of the d array is $2^{\left\lceil\log{n}\right\rceil+1}$.

Analysis: It is easy to know that the depth of the line segment tree is $\left\lceil\log{n}\right\rceil$, so in the case of heap storage, the number of leaf nodes (including useless leaf nodes) is $2^{\left\lceil\log{n}\right\rceil}$, and since it is a complete binary tree, its total number of nodes is $2^{\left\lceil\log{n}\right\rceil+1}-1$. Of course, if you are too lazy to calculate, you can directly set the array length to $4n$, because the maximum value of $\frac{2^{\left\lceil\log{n}\right\rceil+1}-1}{n}$ is obtained at $n=2^{x}+1(x\in N_{+})$, and the number of nodes at this time is $2^{\left\lceil\log{n}\right\rceil+1}-1=2^{x+2}-1=4n-5$.

However, there are useless leaf nodes in heap storage. You can consider using a memory pool to manage line segment tree nodes and obtain them from the pool whenever a new node is needed. Considering bottom-up, every two bottom-level nodes must be merged into an upper-level node. Therefore, it can be proved similar to the Huffman tree. If there are $n$ leaf nodes, such a line segment tree has a total of $2n-1$ nodes. Its space efficiency is better than heap storage and is the best possible situation.

Such a segment tree can be maintained bottom-up; see "[The Power of Statistics - Zhang Kunwei](https://github.com/hzwer/shareOI/blob/master/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/%E7%BB%9F%E8%AE%A1%E7%9A%84%E5%8A%9B%E9%87%8F%E2%80%94%E2%80%94%E7%BA%BF%E6%AE%B5%E6%A0%91%E5%85%A8%E6%8E%A5%E8%A7%A6_%E5%BC%A0%E6%98%86%E7%8E%AE.pptx)".

## Interval query of line segment tree

### process

Interval query, such as finding the sum of the interval $[l,r]$ (that is, $a_l+a_{l+1}+ \cdots +a_r$), finding the maximum/minimum value of the interval, etc.

![](./images/segt1.svg)

Still taking the first picture as an example, if you want to query the sum of the interval $[1,5]$, just get the value of $d_1$ ($60$) directly.

If the interval to be queried is $[3,5]$, the value of the interval cannot be obtained directly at this time, but $[3,5]$ can be split into $[3,3]$ and $[4,5]$, and the answer to this interval can be obtained by merging the answers of these two intervals.

Generally, if the interval to be queried is $[l,r]$, it can be split into up to $O(\log n)$ **maximum** intervals, and the answer to $[l,r]$ can be obtained by merging these intervals.

### accomplish

The code implementation is given here, you can refer to the comments for understanding:

=== "C++"
    ```cpp
    int getsum(int l, int r, int s, int t, int p) {
      // [l, r] is the query interval, [s, t] is the interval included by the current node, p is the number of the current node
      if (l <= s && t <= r)
        return d[p];  // When the current interval is a subset of the query interval, the sum of the current interval is directly returned.
      int m = s + ((t - s) >> 1), sum = 0;
      if (l <= m) sum += getsum(l, r, s, m, p * 2);
      // If the interval [s, m] represented by the left son intersects with the query interval, then the left son is recursively queried
      if (r > m) sum += getsum(l, r, m + 1, t, p * 2 + 1);
      // If the interval [m + 1, t] represented by the right son intersects with the query interval, then the right son is recursively queried
      return sum;
    }
    ```

=== "Python"
    ```python
    def getsum(l, r, s, t, p):
        # [l, r] is the query interval, [s, t] is the interval included by the current node, p is the number of the current node
        if l <= s and t <= r:
            return d[p]  # Directly return the current interval sum when it is a subset of the query interval.
        m = s + ((t - s) >> 1)
        sum = 0
        if l <= m:
            sum = sum + getsum(l, r, s, m, p * 2)
        # If the interval [s, m] represented by the left son intersects with the query interval, then the left son is recursively queried
        if r > m:
            sum = sum + getsum(l, r, m + 1, t, p * 2 + 1)
        # If the interval [m + 1, t] represented by the right son intersects with the query interval, then the right son is recursively queried
        return sum
    ```

## Interval modification and lazy marking of line segment trees

### process

If it is required to modify the interval $[l,r]$, all nodes contained in the interval $[l,r]$ must be traversed and modified once, and the time complexity is unbearable. We are going to introduce something called **"lazy mark"** here.

Lazy marking, simply put, delays changes to node information, thereby reducing the number of potentially unnecessary operations. Each time a modification is performed, we use a marking method to indicate that the interval corresponding to the node has been changed in a certain operation, but the information of the node's child nodes is not updated. Substantial modifications will be made only the next time the marked node is accessed.

Still taking the original picture as an example, we will perform several operations of adding a value to the number in the interval. We now add a $t_i$ to each node, indicating the tag value of the node.

The situation at the beginning was like this (to save space, the intervals governed by each node are no longer shown here):

![](./images/segt2.svg)

Now we are going to add to every number on $[3,5]$ the value $5$. Based on the previous experience of interval query, we quickly found two maximum intervals $[3,3]$ and $[4,5]$ (corresponding to points $5$ and $3$ on the line segment tree respectively).

We make modifications directly on these two nodes and mark them:

![](./images/segt3.svg)

We found that although the information of node No. $3$ has been modified (because this interval governs two numbers, the number added to $d_3$ is $5 \times 2=10$), its two child nodes have not been updated and still retain the information before the modification. But don't worry, although the modification has not been carried out yet, when we want to query the information of these two sub-nodes, we will use the mark to modify the information of these two sub-nodes so that the query results are still accurate.

Next, we query the sum of the numbers in the $[4,4]$ interval.

We found the $[4,5]$ interval through recursion, and found that this interval is not our target interval, and there is a mark on this interval. At this point it’s time to mark the decentralization. We update the information of the two sub-intervals of this interval and clear the marks on this interval.

![](./images/segt4.svg)

Now the values ​​of the two nodes $6$ and $7$ have become the latest values, and the query results are also accurate.

### accomplish

Next, the reference implementation of interval modification and query operations in the presence of markers is given.

Interval modification (interval plus a certain value):

=== "C++"
    ```cpp
    // [l, r] is the modification interval, c is the change amount of the modified element, [s, t] is the interval included by the current node, p
    // is the number of the current node
    void update(int l, int r, int c, int s, int t, int p) {
      // When the current interval is a subset of the modified interval, directly modify the value of the current node, then mark it and end the modification.
      if (l <= s && t <= r) {
        d[p] += (t - s + 1) * c, b[p] += c;
        return;
      }
      int m = s + ((t - s) >> 1);
      if (b[p] && s != t) {
        // If the lazy tag of the current node is not empty, update the values ​​​​of the two child nodes of the current node and the lazy tag value.
        d[p * 2] += b[p] * (m - s + 1), d[p * 2 + 1] += b[p] * (t - m);
        b[p * 2] += b[p], b[p * 2 + 1] += b[p];  // Pass tags down to child nodes
        b[p] = 0;                                // Clear the mark of the current node
      }
      if (l <= m) update(l, r, c, s, m, p * 2);
      if (r > m) update(l, r, c, m + 1, t, p * 2 + 1);
      d[p] = d[p * 2] + d[p * 2 + 1];
    }
    ```

=== "Python"
    ```python
    def update(l, r, c, s, t, p):
        # [l, r] is the modification interval, c is the change amount of the modified element, [s, t] is the interval included by the current node, p
        # is the number of the current node
        if l <= s and t <= r:
            d[p] = d[p] + (t - s + 1) * c
            b[p] = b[p] + c
            return
        # When the current interval is a subset of the modified interval, directly modify the value of the current node, then mark it and end the modification.
        m = s + ((t - s) >> 1)
        if b[p] and s != t:
            # If the lazy tag of the current node is not empty, update the values ​​​​of the two child nodes of the current node and the lazy tag value.
            d[p * 2] = d[p * 2] + b[p] * (m - s + 1)
            d[p * 2 + 1] = d[p * 2 + 1] + b[p] * (t - m)
            # Pass tags down to child nodes
            b[p * 2] = b[p * 2] + b[p]
            b[p * 2 + 1] = b[p * 2 + 1] + b[p]
            # Clear the mark of the current node
            b[p] = 0
        if l <= m:
            update(l, r, c, s, m, p * 2)
        if r > m:
            update(l, r, c, m + 1, t, p * 2 + 1)
        d[p] = d[p * 2] + d[p * 2 + 1]
    ```

Interval query (interval summation):

=== "C++"
    ```cpp
    int getsum(int l, int r, int s, int t, int p) {
      // [l, r] is the query interval, [s, t] is the interval included by the current node, p is the number of the current node
      if (l <= s && t <= r) return d[p];
      // When the current interval is a subset of the query interval, the sum of the current interval is directly returned.
      int m = s + ((t - s) >> 1);
      if (b[p]) {
        // If the lazy tag of the current node is not empty, update the values ​​​​of the two child nodes of the current node and the lazy tag value.
        d[p * 2] += b[p] * (m - s + 1), d[p * 2 + 1] += b[p] * (t - m);
        b[p * 2] += b[p], b[p * 2 + 1] += b[p];  // Pass tags down to child nodes
        b[p] = 0;                                // Clear the mark of the current node
      }
      int sum = 0;
      if (l <= m) sum = getsum(l, r, s, m, p * 2);
      if (r > m) sum += getsum(l, r, m + 1, t, p * 2 + 1);
      return sum;
    }
    ```

=== "Python"
    ```python
    def getsum(l, r, s, t, p):
        # [l, r] is the query interval, [s, t] is the interval included by the current node, and p is the number of the current node.
        if l <= s and t <= r:
            return d[p]
        # When the current interval is a subset of the query interval, the sum of the current interval is directly returned.
        m = s + ((t - s) >> 1)
        if b[p]:
            # If the lazy tag of the current node is not empty, update the values ​​​​of the two child nodes of the current node and the lazy tag value.
            d[p * 2] = d[p * 2] + b[p] * (m - s + 1)
            d[p * 2 + 1] = d[p * 2 + 1] + b[p] * (t - m)
            # Pass tags down to child nodes
            b[p * 2] = b[p * 2] + b[p]
            b[p * 2 + 1] = b[p * 2 + 1] + b[p]
            # Clear the mark of the current node
            b[p] = 0
        sum = 0
        if l <= m:
            sum = getsum(l, r, s, m, p * 2)
        if r > m:
            sum = sum + getsum(l, r, m + 1, t, p * 2 + 1)
        return sum
    ```

If you want to modify the interval to a certain value instead of adding a certain value, the code is as follows:

=== "C++"
    ```cpp
    void update(int l, int r, int c, int s, int t, int p) {
      if (l <= s && t <= r) {
        d[p] = (t - s + 1) * c, b[p] = c, v[p] = 1;
        return;
      }
      int m = s + ((t - s) >> 1);
      // Additional array storage whether to modify the value
      if (v[p]) {
        d[p * 2] = b[p] * (m - s + 1), d[p * 2 + 1] = b[p] * (t - m);
        b[p * 2] = b[p * 2 + 1] = b[p];
        v[p * 2] = v[p * 2 + 1] = 1;
        v[p] = 0;
      }
      if (l <= m) update(l, r, c, s, m, p * 2);
      if (r > m) update(l, r, c, m + 1, t, p * 2 + 1);
      d[p] = d[p * 2] + d[p * 2 + 1];
    }
    
    int getsum(int l, int r, int s, int t, int p) {
      if (l <= s && t <= r) return d[p];
      int m = s + ((t - s) >> 1);
      if (v[p]) {
        d[p * 2] = b[p] * (m - s + 1), d[p * 2 + 1] = b[p] * (t - m);
        b[p * 2] = b[p * 2 + 1] = b[p];
        v[p * 2] = v[p * 2 + 1] = 1;
        v[p] = 0;
      }
      int sum = 0;
      if (l <= m) sum = getsum(l, r, s, m, p * 2);
      if (r > m) sum += getsum(l, r, m + 1, t, p * 2 + 1);
      return sum;
    }
    ```

=== "Python"
    ```python
    def update(l, r, c, s, t, p):
        if l <= s and t <= r:
            d[p] = (t - s + 1) * c
            b[p] = c
            v[p] = 1
            return
        m = s + ((t - s) >> 1)
        if v[p]:
            d[p * 2] = b[p] * (m - s + 1)
            d[p * 2 + 1] = b[p] * (t - m)
            b[p * 2] = b[p * 2 + 1] = b[p]
            v[p * 2] = v[p * 2 + 1] = 1
            v[p] = 0
        if l <= m:
            update(l, r, c, s, m, p * 2)
        if r > m:
            update(l, r, c, m + 1, t, p * 2 + 1)
        d[p] = d[p * 2] + d[p * 2 + 1]
    
    
    def getsum(l, r, s, t, p):
        if l <= s and t <= r:
            return d[p]
        m = s + ((t - s) >> 1)
        if v[p]:
            d[p * 2] = b[p] * (m - s + 1)
            d[p * 2 + 1] = b[p] * (t - m)
            b[p * 2] = b[p * 2 + 1] = b[p]
            v[p * 2] = v[p * 2 + 1] = 1
            v[p] = 0
        sum = 0
        if l <= m:
            sum = getsum(l, r, s, m, p * 2)
        if r > m:
            sum = sum + getsum(l, r, m + 1, t, p * 2 + 1)
        return sum
    ```

## Dynamic open point segment tree

As mentioned earlier, in the case of heap storage, an array of size $4n$ needs to be opened for the line segment tree. In order to save space, we can not build the tree all at once, but initially only create one root node to represent the entire interval. When we need to access a certain sub-range, we create a child node representing this range. In this way, we no longer use $2p$ and $2p+1$ to represent the sons of the $p$ node, but use $\text{ls}$ and $\text{rs}$ to record the number of the son. In short, the core idea of ​​the dynamic open-point line segment tree is: **nodes are only created when needed**.

The time complexity of a single operation is constant, $O(\log n)$. Since each operation may create and access a new series of nodes, the number of nodes after $m$ single-point operations is $O(m\log n)$. At most, only $2n-1$ nodes are needed, so there is no waste.

Single point modification:

```cpp
// root represents the root node of the entire line segment tree; cnt represents the current number of nodes
int n, cnt, root;
int sum[n * 2], ls[n * 2], rs[n * 2];

// Usage: update(root, 1, n, x, f); where x is the number of the node to be modified
void update(int& p, int s, int t, int x, int f) {  // Passing parameters by reference
  if (!p) p = ++cnt;  // When the node is empty, create a new node
  if (s == t) {
    sum[p] += f;
    return;
  }
  int m = s + ((t - s) >> 1);
  if (x <= m)
    update(ls[p], s, m, x, f);
  else
    update(rs[p], m + 1, t, x, f);
  sum[p] = sum[ls[p]] + sum[rs[p]];  // pushup
}
```

Interval query:

```cpp
// Usage: query(root, 1, n, l, r);
int query(int p, int s, int t, int l, int r) {
  if (!p) return 0;  // If the node is empty, return 0
  if (s >= l && t <= r) return sum[p];
  int m = s + ((t - s) >> 1), ans = 0;
  if (l <= m) ans += query(ls[p], s, m, l, r);
  if (r > m) ans += query(rs[p], m + 1, t, l, r);
  return ans;
}
```

The interval modification is the same, but when delegating the mark, be careful to create a new child directly if there is a lack of children. Or use the mark-permanence technique.

## some optimizations

Here is a summary of several line segment tree optimizations:

-   There is no need to send lazy marks to leaf nodes, so lazy marks do not need to be sent to leaf nodes.

-   To delegate the lazy mark, you can write a special function `pushdown`. To update the current node from the child node, you can also write a special function `maintain` (or use `pushup` symmetrically) to reduce the difficulty of writing code.

-   Marking is permanent: If it is determined that the lazy mark will not be added to the overflow midway (that is, it exceeds the maximum range that can be represented by this type of data), then the mark can be made permanent. Permanent marking can avoid downloading lazy markings, and only needs to add the influence of markings to the answers when asking, thereby reducing program constants. The specific method of handling is related to the characteristics of the topic and needs to be written in conjunction with the topic. This is also a technique used in trees within trees and persistent data structures.

## C++ template

??? note "SegTreeLazyRangeAdd is a line segment tree template that can add/sum the interval"
    ```cpp
    --8<-- "docs/ds/code/seg/seg_4.hpp"
    ```

??? note "SegTreeLazyRangeSet is a segment tree template that can be modified/summed in intervals"
    ```cpp
    --8<-- "docs/ds/code/seg/seg_5.hpp"
    ```

## example

???+ note "[luogu P3372【Template】Line Segment Tree 1](https://www.luogu.com.cn/problem/P3372)"
Given a sequence, you need to perform the following two operations:
    
    -   Add $k$ to each number in a certain range.
    
    -   Find the sum of every number in a certain interval.
    
??? note "reference code"
        ```cpp
        --8<-- "docs/ds/code/seg/seg_1.cpp"
        ```

???+ note "[luogu P3373【Template】Line Segment Tree 2](https://www.luogu.com.cn/problem/P3373)"
Given a sequence, you need to perform the following three operations:
    
    -   Multiply each number in a range by $x$.
    
    -   Add $x$ to each number in a certain range.
    
    -   Find the sum of every number in a certain interval.
    
??? note "reference code"
        ```cpp
        --8<-- "docs/ds/code/seg/seg_2.cpp"
        ```

???+ note "[HihoCoder 1078 Interval modification of segment tree](https://vjudge.net/problem/HihoCoder-1078)"
Assume that there are $N$ products on the shelf from left to right, and they are numbered $1$ to $N$. The price of the product numbered $i$ is $Pi$. Each operation of Little Hi is divided into two possibilities. The first is to modify the price: Little Hi gives a range $[L, R]$ and a new price $\textit{NewP}$, and the prices of all commodities marked in this range become $\textit{NewP}$. The second operation is to ask: Little Hi gives a range $[L, R]$, and what Little Ho has to do is to calculate the total price of all goods labeled in this range, and then tell Little Hi.
    
??? note "reference code"
        ```cpp
        --8<-- "docs/ds/code/seg/seg_3.cpp"
        ```

???+ note "[2018 Multi-University Training Contest 5 Problem G. Glad You Came](https://acm.hdu.edu.cn/showproblem.php?pid=6356)"
??? note "Problem-solving ideas"
Just maintain the permanent mark of each interval, and finally run the DFS statistical results on the line segment tree. Pay attention to adding pruning optimization when marking, otherwise TLE will occur.

## expand

Line segment trees are widely used. Common extensions and variations are as follows:

-   [Persistible Segment Tree](./persistent-seg.md)
-   Various types of trees within trees:
    -   [Line segment tree within line segment tree](./seg-in-seg.md)
    -   [Tree Array Set Line Segment Tree](./seg-in-bit.md)
    -   [Balanced tree within line segment tree](./balanced-in-seg.md)
    -   [Balanced tree set tree array](./seg-in-balanced.md)
-   [Li Chao Line Segment Tree](./li-chao-tree.md)
-   [Cat Tree](./cat-tree.md)
-   [Ji driver line segment tree](./seg-beats.md)

Please refer to the relevant pages for details.

## Application: Line segment tree optimization mapping

In the process of connecting edges in a graph, we sometimes encounter this problem. A point connects an edge to a point in a continuous interval or a continuous interval connects an edge to a point. If we really connect them one by one, the complexity will explode once the number of points increases. Here we need to use the interval properties of the line segment tree to optimize our graph construction.

Below is a line segment tree.

![](./images/segt5.svg)

Each node represents an interval. Suppose we want to connect edges to the interval $[2, 4]$.

![](./images/segt6.svg)

In some questions, there will be a situation where an interval is connected to a point, so we can reverse all the directed edges of the first picture above. The tree above is called the entry tree, and the one below is called the exit tree.

![](./images/segt7.svg)

???+ note "[Legacy](https://codeforces.com/problemset/problem/786/B)"
The general idea of ​​the question: There are $n$ points and $q$ operations. Each operation is one of the following three types:
    
    -   Operation 1: Connect a directed edge of $u \rightarrow v$ with a weight of $w$.
    -   Operation 2: For all directed edges from $i \in [l,r]$ to $u \rightarrow i$, the weight is $w$.
    -   Operation 3: For all directed edges from $i \in [l,r]$ to $i \rightarrow u$, the weight is $w$.
    
Find the shortest path from point $s$ to other points.
    
    $1 \le n,q \le 10^5, 1 \le w \le 10^9$．
    
??? note "reference code"
        ```cpp
        --8<-- "docs/ds/code/seg/seg_8.cpp"
        ```

## Practice questions

-   [luogu P3372【Template】Line Segment Tree 1](https://www.luogu.com.cn/problem/P3372)
-   [luogu P13825 Line Segment Tree 1.5 [Dynamic Open Point Line Segment Tree]](https://www.luogu.com.cn/problem/P13825)
-   [luogu P3373【Template】Line Segment Tree 2](https://www.luogu.com.cn/problem/P3373)
-   [luogu P4588【TJOI2018】Mathematical calculation](https://www.luogu.com.cn/problem/P4588)
-   [luogu P5490【Template】Scan line & rectangular area union](https://www.luogu.com.cn/problem/P5490)
-   [luogu P1471 variance](https://www.luogu.com.cn/problem/P1471)
