## Introduction

The scanline technique is generally used on geometric figures. As its name suggests, it sweeps a line across the entire figure. It is usually used to solve problems such as area, perimeter, and two-dimensional point counting.

## Union Area of 2D Rectangles

In a two-dimensional coordinate system, given the lower-left and upper-right coordinates of multiple rectangles, compute the area of the figure formed by their union.

### Procedure

From the picture, the total area can be found directly by brute force. But what if the data size is large? This is where the **scanline** algorithm is needed.

Now suppose we have a line that starts scanning from bottom to top:

![](./images/scanning.svg)

As shown in the figure, divide the entire figure into small rectangles of different colors. The height of each small rectangle is the swept distance, while its horizontal width keeps changing.

Mark the lower and upper edges of every rectangle: mark a lower edge as 1 and an upper edge as -1. Whenever a horizontal edge is encountered, add this edge's mark to the weight of the interval where the edge projects onto the x-axis.

???+ note "Note"
    This operation is similar to traversing a bracket sequence: add 1 for an opening bracket and subtract 1 for a closing bracket. The "weight" corresponds to the depth at the current position, and whether the "weight" is greater than 0 corresponds to whether we are currently inside brackets, that is, whether this interval should be counted in the width of the small rectangle.

The width of the small rectangle or rectangles is the total length of intervals on the entire number line whose weight is greater than 0.

### Implementation

Use a segment tree to maintain the length of rectangles, namely the points on the whole number line whose coverage count is greater than 0. The requirements are:

-   Add 1 or subtract 1 from the weight of an interval.
-   Count the "sum of interval lengths" whose interval weight is greater than 0 on the whole number line.

If you try to implement this directly with a standard segment tree template, you may run into difficulties. Specifically, during interval addition, even when the modified interval coincides with the interval managed by a node, we still cannot know in constant time how the coverage count changes. This is because we cannot directly know how much length in the managed range changes from 1 to 0, or from 0 to 1.

This problem can be implemented with simple divide and conquer: for each node's managed interval, maintain two pieces of information, the "number of times the interval is completely covered `v[]`" (similar to a lazy tag that does not need to be pushed down) and the "covered length `w[]`".

[Discretization](../misc/discrete.md) is needed.

??? note "Reference code for [Luogu P5490 [Template] Scanline & Union Area of Rectangles](https://www.luogu.com.cn/problem/P5490)"
    ```cpp
    --8<-- "docs/geometry/code/scanning/scanning_1.cpp"
    ```

??? note "Reference code for [POJ 1151 Atlantis](http://poj.org/problem?id=1151)"
    ```cpp
    --8<-- "docs/geometry/code/scanning/scanning_2.cpp"
    ```

### Exercises

-   [「POJ1177」Picture](http://poj.org/problem?id=1177)
-   [「POJ3832」Posters](http://poj.org/problem?id=3832)
-   [Luogu P1856 [IOI1998] [USACO5.5] Rectangle Perimeter Picture](https://www.luogu.com.cn/problem/P1856)
    -   The contribution of horizontal edges is the change in covered length.
    -   Calculating once in each of the two directions avoids discussing vertical edges.
    -   When sorting operations, be careful about the case where edges of two rectangles coincide.
    -   The data range allows direct quadratic-time simulation without a segment tree.

## B-Dimensional Orthogonal Range

A B-dimensional orthogonal range refers to the set of points in a B-dimensional Cartesian coordinate system whose coordinate in the $i$-th dimension lies within an integer range $[l_i,r_i]$.

Generally, a one-dimensional orthogonal range is simply called an interval, a two-dimensional orthogonal range is called a rectangle, and a three-dimensional orthogonal range is called a cuboid. The commonly mentioned two-dimensional point counting problem is a two-dimensional orthogonal range problem.

For a static two-dimensional problem, we can use a scanline to sweep one dimension and use a data structure to maintain the other dimension.
As the scanline sweeps from left to right, modifications and queries are generated on the dimension maintained by the data structure.
If the queried information can be differenced, use difference directly; otherwise divide and conquer is needed. Difference is usually maintained with a Fenwick tree or segment tree, but because a Fenwick tree is easy to write and has small constants, most people choose a Fenwick tree. The divide-and-conquer method is usually CDQ divide and conquer, though divide and conquer is not covered here.

Another easier-to-understand viewpoint is to look at the problem from the sequence perspective rather than the two-dimensional plane perspective. From this viewpoint, the scanline is actually enumerating the right endpoint $r=1\cdots n$ while maintaining a data structure that supports querying, for the current $r$ and a given value $l$, what the answer from $l$ to $r$ is. In other words, the scanline sweeps over query right endpoints, while the data structure maintains answers for all left endpoints; equivalently, we traverse one dimension and maintain the other with a data structure.

The complexity is usually $O((n+m)\log n)$.

## Two-Dimensional Point Counting

Given a sequence of length $n$ and $m$ queries, each query asks for the number of elements in interval $[l,r]$ whose values lie in $[x,y]$.

This problem is called two-dimensional point counting. It is equivalent to querying the number of points inside a rectangle on a two-dimensional plane. Here we discuss the simplest way to handle it: scanline + Fenwick tree.

Clearly, this is a static two-dimensional problem. With a scanline, we can transform the static two-dimensional problem into a dynamic one-dimensional problem. To maintain the dynamic one-dimensional problem, use a data structure over the sequence; here a Fenwick tree can be used.

First discretize all queries and use a Fenwick tree to maintain weights. For each query's $l$ and $r$, when we enumerate to $l-1$, count the current number of values in interval $[x,y]$ as $a$. Continue enumerating forward; when we reach $r$, count the current number of values in interval $[x,y]$ as $b$. Then $b-a$ is the answer to this query.

### Examples

???+ note "[Luogu P2163 [SHOI2007] The Gardener's Troubles](https://www.luogu.com.cn/problem/P2163)"
    First discretize. Let a rectangle with lower-left corner $(0, 0)$ and upper-right corner $(x, y)$ contain $ans_{x, y}$ points. Then the answer to a query can be differenced as $ans_{c, d} - ans_{a - 1, d} - ans_{c, b - 1} + ans_{a - 1, b - 1}$.
    
    ??? note "Code"
        ```cpp
        --8<-- "docs/geometry/code/scanning/scanning_3.cpp"
        ```

???+ note "[Luogu P1908 Inversions](https://www.luogu.com.cn/problem/P1908)"
    Yes, inversions can also be solved with scanline thinking. Consider transforming the task of counting inversions into enumerating each position $i$ from back to front and finding the number of points in interval $[i+1,n]$ whose values lie in $[0,a_i]$. The data range in the problem is $10^9$, so discretization is clearly needed first. We can traverse the array from back to front, updating the Fenwick tree or segment tree whenever we visit a number, and then count how many numbers are currently smaller than the enumerated number. Since we traverse from back to front, the number of values smaller than the current value is the number of inversions contributed by it. This can be done with point modifications and interval queries using a Fenwick tree or segment tree.
    
    ??? note "Code"
        ```cpp
        --8<-- "docs/geometry/code/scanning/scanning_4.cpp"
        ```

???+ note "[Luogu P1972 [SDOI2009] HH's Necklace](https://www.luogu.com.cn/problem/P1972)"
    Brief statement: given a sequence, answer multiple queries asking how many distinct numbers appear in interval $[l,r]$.
    
    For this kind of problem, we can derive useful properties and then use a scanline to enumerate all right endpoints while a data structure maintains the answer for each left endpoint. We can also transform the problem onto a two-dimensional plane, turning it into a rectangle query problem.
    
    In this problem, let the previous occurrence position of $a_i$ in the sequence be $pre_i$; if $a_i$ has not appeared before, then $pre_i = 0$. According to the statement, if a number appears multiple times in an interval, it contributes only once. We may regard the contribution position of each number as its first occurrence in the interval. Then we can see that the total contribution is exactly the number of positions satisfying $pre_x \le l - 1$, which is easy to prove by contradiction.
    
    Now the problem becomes: given a sequence $pre$, answer multiple queries asking how many $pre_i \le l - 1$ there are in interval $[l,r]$.
    
    We can regard $pre_i$ as a point on a two-dimensional plane: $i$ is the x-coordinate, and $pre_i$ is the y-coordinate. The problem is then transformed into two-dimensional point counting: each query asks how many points are inside the rectangle whose lower-left corner is $(l,0)$ and upper-right corner is $(r,l - 1)$.
    
    Notice that this query can be differenced. We can express it as the number of points in the rectangle with lower-left corner $(0,0)$ and upper-right corner $(r,l - 1)$ minus the number of points in the rectangle with lower-left corner $(0,0)$ and upper-right corner $(l - 1,l - 1)$, which makes it convenient to use the scanline idea.
    
    Each operation costs $O(\log n)$. There are $n$ point-insertion operations and $2m$ query operations, so the total time complexity is $O((n + m) \log n)$.
    
    ??? note "Code"
        ```cpp
        --8<-- "docs/geometry/code/scanning/scanning_5.cpp"
        ```

### Exercises

-   [Luogu P8593 [KDOI-02] A Projectile's Shot](https://www.luogu.com.cn/problem/P8593), an application of inversions.
-   [AcWing 4709. Triples](https://www.acwing.com/problem/content/4712/), a weakened version of the previous problem, also an application of inversions.
-   [Luogu P8773 [Lanqiao Cup 2022 Provincial A] Selecting Numbers with XOR](https://www.luogu.com.cn/problem/P8773), a modified version of HH's Necklace.
-   [Luogu P8844 [Chuanzhi Cup #4 Preliminary] Xiaoka and Fallen Leaves](https://www.luogu.com.cn/problem/P8844), transforms a tree problem into a sequence problem and then performs two-dimensional point counting.

In summary, the main idea of two-dimensional point counting is to maintain one dimension with a data structure and enumerate the other dimension.

## References

-   [cnblogs/Yang1208: Scanline explanation, dynamic segment tree](https://www.cnblogs.com/yangsongyi/p/8378629.html)
-   [csdn/riba2534: POJ1151 Atlantis solution](https://blog.csdn.net/riba2534/article/details/76851233)
-   [csdn/Daodaogou 0102: POJ1151 Atlantis solution](https://blog.csdn.net/winddreams/article/details/38495093)
-   [A Brief Discussion of Scanline](https://www.luogu.com.cn/article/f8q5bmnz)
