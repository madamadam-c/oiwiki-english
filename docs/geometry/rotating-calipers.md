This page mainly introduces rotating calipers.

## Introduction

The rotating calipers algorithm, based on convex hull algorithms, enumerates an edge of the convex hull while maintaining other needed points. It can solve convex-hull-related problems such as the diameter of a convex hull and the minimum-area enclosing rectangle in linear time.

???+ note "Chinese Name of the Algorithm"
    A common Chinese name of this algorithm literally means "rotating clamping shells". It can be understood as follows: according to the edge we enumerate, we can draw a line from each maintained point that is either parallel or perpendicular to that edge. To ensure optimality for the currently enumerated edge, our task is to make these lines just clamp the convex hull. Since the edges are usually enumerated in the order of rotation toward one direction, the whole process is one where the edge is "rotating" and the hull is being "clamped".
    
    The literal translation of the English term "rotating calipers" is closer to "rotating vernier calipers", where "calipers" means a measuring caliper. The original meaning in the paper that first proposed this term[^ref1] was: after using a dynamically adjustable pair of "calipers" to clamp the convex hull, rotate those "calipers" around the hull.

## Finding the Diameter of a Convex Hull

???+ note "Example 1: [Luogu P1452 Beauty Contest G](https://www.luogu.com.cn/problem/P1452)"
    Given $n$ points on the plane, find the longest distance among all pairs of points. ($2\leq n \leq 50000,|x|,|y| \leq 10^4$)

### Procedure

First use any convex hull algorithm to find the convex hull of all given points. The pair of points with the longest distance must lie on the convex hull. Because of the shape of a convex hull, if we traverse its edges counterclockwise and, for each edge, find the point farthest from that edge, then as the edge rotates, the corresponding farthest point also rotates counterclockwise and never moves backward. This means that while enumerating the convex hull edges counterclockwise, we can record and maintain the current farthest point and continuously compute and update the answer.

The array obtained after computing the convex hull is naturally ordered counterclockwise, but remember to append the leftmost-lower point, node 1, to the end of the array in advance, so that when enumerating edges $(i,i+1)$ one by one, every edge is included.

![](images/rotating-calipers1.png)

During enumeration, for each edge, check whether the distance from $j+1$ to edge $(i,i+1)$ is greater than that from $j$. If so, increment $j$; otherwise, $j$ is the optimal point for this edge. To compare distances from points to an edge, use cross products to compute the areas of the two triangles respectively, as in the figure, the yellow and blue triangles with the same base, and compare them directly.

### Implementation

???+ note "Core Code"
    === "C++"
        ```cpp
        int sta[N], top;  // Store node indices on the convex hull in a stack; the first and last are identical
        
        ll pf(ll x) { return x * x; }
        
        ll dis(int p, int q) { return pf(a[p].x - a[q].x) + pf(a[p].y - a[q].y); }
        
        ll sqr(int p, int q, int y) { return abs((a[q] - a[p]) * (a[y] - a[q])); }
        
        ll mx;
        
        void get_longest() {  // Find the diameter of the convex hull
          int j = 3;
          if (top < 4) {
            mx = dis(sta[1], sta[2]);
            return;
          }
          for (int i = 1; i < top; ++i) {
            while (sqr(sta[i], sta[i + 1], sta[j]) <=
                   sqr(sta[i], sta[i + 1], sta[j % top + 1]))
              j = j % top + 1;
            mx = max(mx, max(dis(sta[i + 1], sta[j]), dis(sta[i], sta[j])));
          }
        }
        ```
    
    === "Python"
        ```python
        sta = [0] * N
        top = 0  # Store node indices on the convex hull in a stack; the first and last are identical
        
        
        def pf(x):
            return x * x
        
        
        def dis(p, q):
            return pf(a[p].x - a[q].x) + pf(a[p].y - a[q].y)
        
        
        def sqr(p, q, y):
            return abs((a[q] - a[p]) * (a[y] - a[q]))
        
        
        def get_longest():  # Find the diameter of the convex hull
            j = 3
            if top < 4:
                mx = dis(sta[1], sta[2])
                return
            for i in range(1, top):
                while sqr(sta[i], sta[i + 1], sta[j]) <= sqr(
                    sta[i], sta[i + 1], sta[j % top + 1]
                ):
                    j = j % top + 1
                mx = max(mx, max(dis(sta[i + 1], sta[j]), dis(sta[i], sta[j])))
        ```

## Finding the Minimum Enclosing Rectangle

[Luogu P3187 Minimum Enclosing Rectangle](https://www.luogu.com.cn/problem/P3187)

Given the coordinates of some points, find the rectangle with minimum area that can cover all points. ($3\leq n \leq 50000$)

### Procedure

With the previous problem as background, the intuitive idea for this problem is still to use rotating calipers. However, this time we need the area. If, as in the previous problem, we maintain only one optimal point, we can only find a pair of parallel lines with minimum distance; we also need to determine the left and right boundaries of the rectangle. Therefore, this time we maintain three points: one point opposite the enumerated line, and two points on different sides. The optimal opposite point is still compared by using cross products to compute areas; here comparing areas is equivalent to comparing one side length of the rectangle. The optimal side points are compared by dot products, because comparing dot products compares projection lengths, and the sum of the left and right projection lengths represents the other side length of the rectangle. The optimality of these two side lengths is independent, so once the three optimal point positions are found, we can determine the minimum area rectangle covering all points when the line containing the current edge is one side of the rectangle.

![](images/rotating-calipers2.png)

When computing the final answer, if the problem does not require outputting all four vertices, there is a clever way to directly compute the rectangle area using cross products and dot products. Let twice the area of the purple part be $S$; the final area is

$$
S\times (|\overrightarrow{AD}\cdot \overrightarrow{AB}|+|\overrightarrow{BC}\cdot \overrightarrow{BA}|-|\overrightarrow{AB}\cdot \overrightarrow{BA}|)/|\overrightarrow{AB}\cdot \overrightarrow{BA}|
$$

### Implementation

The necessary convex hull computation is omitted; the core code for this problem is shown here:

???+ note "Core Code"
    === "C++"
        ```cpp
        void get_biggest() {
          int j = 3, l = 2, r = 2;
          double t1, t2, t3, ans = 2e10;
          for (int i = 1; i < top; ++i) {
            while (sqr(sta[i], sta[i + 1], sta[j]) <=
                   sqr(sta[i], sta[i + 1], sta[j % top + 1]))
              j = j % top + 1;
            while (dot(sta[i + 1], sta[r % top + 1], sta[i]) >=
                   dot(sta[i + 1], sta[r], sta[i]))
              r = r % top + 1;
            if (i == 1) l = r;
            while (dot(sta[i + 1], sta[l % top + 1], sta[i]) <=
                   dot(sta[i + 1], sta[l], sta[i]))
              l = l % top + 1;
            t1 = sqr(sta[i], sta[i + 1], sta[j]);
            t2 = dot(sta[i + 1], sta[r], sta[i]) + dot(sta[i + 1], sta[l], sta[i]);
            t3 = dot(sta[i + 1], sta[i + 1], sta[i]);
            ans = min(ans, t1 * t2 / t3);
          }
        }
        ```
    
    === "Python"
        ```python
        def get_biggest():
            j = 3
            l = 2
            r = 2
            ans = 2e10
            for i in range(1, top):
                while sqr(sta[i], sta[i + 1], sta[j]) <= sqr(
                    sta[i], sta[i + 1], sta[j % top + 1]
                ):
                    j = j % top + 1
                while dot(sta[i + 1], sta[r % top + 1], sta[i]) >= dot(
                    sta[i + 1], sta[r], sta[i]
                ):
                    r = r % top + 1
                if i == 1:
                    l = r
                while dot(sta[i + 1], sta[l % top + 1], sta[i]) <= dot(
                    sta[i + 1], sta[l], sta[i]
                ):
                    l = l % top + 1
                t1 = sqr(sta[i], sta[i + 1], sta[j])
                t2 = dot(sta[i + 1], sta[r], sta[i]) + dot(sta[i + 1], sta[l], sta[i])
                t3 = dot(sta[i + 1], sta[i + 1], sta[i])
                ans = min(ans, t1 * t2 / t3)
        ```

## Exercises

-   [POJ 3608. Bridge Across Islands](http://poj.org/problem?id=3608)
-   [2011 ACM-ICPC World Finals, Problem K. Trash Removal](https://codeforces.com/gym/101175)
-   [ICPC WF Moscow Invitational Contest - Online Mirror, Problem F. Framing Pictures](https://codeforces.com/contest/1578/problem/F)

## References and Notes

[^ref1]: Toussaint, Godfried T. (1983). "Solving geometric problems with the rotating calipers". Proc. MELECON '83, Athens. CiteSeerX 10.1.1.155.5671

-   <https://en.wikipedia.org/wiki/Rotating_calipers>

-   <http://www-cgrl.cs.mcgill.ca/~godfried/research/calipers.html>

-   Shamos, Michael (1978). "Computational Geometry" (PDF). Yale University. pp. 76–81.
