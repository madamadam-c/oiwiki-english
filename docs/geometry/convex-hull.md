## Two-Dimensional Convex Hull

### Definitions

#### Convex Polygon

A convex polygon is a **simple polygon** whose interior angles all lie in the range $[0,\pi]$.

#### Convex Hull

The smallest convex polygon on the plane that can contain all given points is called the convex hull.

Formally, for a given set $X$, the intersection $S$ of all convex sets containing $X$ is called the **convex hull** of $X$.

Intuitively, it can be understood as the shape formed by stretching a rubber band around all given points.

The convex hull encloses all given points with the minimum perimeter. If a concave polygon encloses all the points, its perimeter is definitely not minimal, as shown below. By the triangle inequality, a convex polygon is always optimal in perimeter.

![](./images/ch.png)

### Andrew's Algorithm for Convex Hull

Common methods include Graham scan and Andrew's algorithm. Here we mainly introduce Andrew's algorithm.

#### Properties

The time complexity of this algorithm is $O(n\log n)$, where $n$ is the size of the point set whose convex hull is to be found. The bottleneck is sorting all point coordinates by two keys.

#### Procedure

First sort all points by x-coordinate as the primary key and y-coordinate as the secondary key.

Obviously, the minimum and maximum elements after sorting must lie on the convex hull. Also, because the hull is a convex polygon, if we start from a point and walk counterclockwise, the path always "turns left"; once a right turn occurs, that segment is not on the convex hull. Therefore, we can use a monotonic stack to maintain the upper and lower hulls.

Because, viewed from left to right, the upper and lower hulls rotate in different directions, to make the monotonic stack work we first enumerate in **ascending order** to find the lower hull, then in **descending order** to find the upper hull.

When constructing a hull, if the point about to enter the stack, $P$, together with the top two stack points, $S_1,S_2$ where $S_1$ is the stack top, makes the path turn right, meaning the cross product is less than $0$: $\overrightarrow{S_2S_1}\times \overrightarrow{S_1P}<0$, then pop the stack top, return to the previous step, and continue checking until $\overrightarrow{S_2S_1}\times \overrightarrow{S_1P}\ge 0$ or only one element remains in the stack.

Usually, points lying on convex hull edges do not need to be kept. Therefore, the "$<$" in the condition $\overrightarrow{S_2S_1}\times \overrightarrow{S_1P}<0$ above can be changed to $\le$ depending on the situation, and the later condition should be changed to $>$ accordingly.

![Andrew](./images/andrew.svg)

#### Implementation

???+ note "Implementation"
    === "C++"
        ```cpp
        // stk[] is an integer array storing indices
        // p[] stores vectors or points
        tp = 0;                       // initialize the stack
        std::sort(p + 1, p + 1 + n);  // sort the points
        stk[++tp] = 1;
        // Add the first element to the stack without updating used, so that 1 also updates the monotonic stack when closing the hull at the end
        for (int i = 2; i <= n; ++i) {
          while (tp >= 2  // In the next line, operator * is overloaded as cross product
                 && (p[stk[tp]] - p[stk[tp - 1]]) * (p[i] - p[stk[tp]]) <= 0)
            used[stk[tp--]] = 0;
          used[i] = 1;  // used indicates being on the hull
          stk[++tp] = i;
        }
        int tmp = tp;  // tmp indicates the size of the lower hull
        for (int i = n - 1; i > 0; --i)
          if (!used[i]) {
            // Do not affect the lower hull when computing the upper hull
            while (tp > tmp && (p[stk[tp]] - p[stk[tp - 1]]) * (p[i] - p[stk[tp]]) <= 0)
              used[stk[tp--]] = 0;
            used[i] = 1;
            stk[++tp] = i;
          }
        for (int i = 1; i <= tp; ++i)  // copy into the new array
          h[i] = p[stk[i]];
        int ans = tp - 1;
        ```
    
    === "Python"
        ```python
        stk = []  # integer array storing indices
        p = []  # stores vectors or points
        tp = 0  # initialize the stack
        p.sort()  # sort the points
        tp = tp + 1
        stk[tp] = 1
        # Add the first element to the stack without updating used, so that 1 also updates the monotonic stack when closing the hull at the end
        for i in range(2, n + 1):
            while tp >= 2 and (p[stk[tp]] - p[stk[tp - 1]]) * (p[i] - p[stk[tp]]) <= 0:
                # In the next line, operator * is overloaded as cross product
                used[stk[tp]] = 0
                tp = tp - 1
            used[i] = 1  # used indicates being on the hull
            tp = tp + 1
            stk[tp] = i
        tmp = tp  # tmp indicates the size of the lower hull
        for i in range(n - 1, 0, -1):
            if used[i] == False:
                #      Do not affect the lower hull when computing the upper hull
                while tp > tmp and (p[stk[tp]] - p[stk[tp - 1]]) * (p[i] - p[stk[tp]]) <= 0:
                    used[stk[tp]] = 0
                    tp = tp - 1
                used[i] = 1
                tp = tp + 1
                stk[tp] = i
        for i in range(1, tp + 1):
            h[i] = p[stk[i]]
        ans = tp - 1
        ```

According to the code above, the final convex hull has $\textit{ans}$ elements. Since point $1$ is stored additionally, the $h$ array has $\textit{ans}+1$ elements, and they are sorted counterclockwise. The perimeter is

$$
\sum_{i=1}^{\textit{ans}}\left|\overrightarrow{h_ih_{i+1}}\right|
$$

### Graham Scan

#### Properties

Like Andrew's algorithm, Graham scan has time complexity $O(n\log n)$, and its bottleneck is also sorting all points.

#### Procedure

First find a point $P$ with the smallest y-coordinate among all points. By the definition of the convex hull, this point must lie on the convex hull. Then sort all points by their polar angle relative to point P.

![](./images/ch1.svg)

Similar to Andrew's algorithm, consider starting from point $P$ and walking counterclockwise along the convex hull. Every node we pass must be a "left turn". Formally, for any three consecutive points $P_1, P_2, P_3$ on the convex hull in counterclockwise order, it must hold that $\overrightarrow{P_1 P_2} \times \overrightarrow{P_2 P_3} \ge 0$.

Create a new stack to store convex hull information. First push $P$ onto the stack, then try to add each point in polar-angle order. If the point entering the stack, $P_0$, together with the top two stack points $P_1, P_2$ where $P_1$ is the stack top, makes the path "turn right", pop the stack top $P_1$. Repeat this process until the entering point and the top two stack points satisfy the condition, or only one element remains in the stack, then push $P_0$ onto the stack.

![](./images/ch2.svg)

![](./images/ch3.svg)

???+ note "Implementation"
    ```cpp
    struct Point {
      double x, y, ang;
    
      Point operator-(const Point& p) const { return {x - p.x, y - p.y, 0}; }
    } p[MAXN];
    
    double dis(Point p1, Point p2) {
      return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }
    
    bool cmp(Point p1, Point p2) {
      if (p1.ang == p2.ang) {
        return dis(p1, p[1]) < dis(p2, p[1]);
      }
      return p1.ang < p2.ang;
    }
    
    double cross(Point p1, Point p2) { return p1.x * p2.y - p1.y * p2.x; }
    
    int main() {
      for (int i = 2; i <= n; ++i) {
        if (p[i].y < p[1].y || (p[i].y == p[1].y && p[i].x < p[1].x)) {
          std::swap(p[1], p[i]);
        }
      }
      for (int i = 2; i <= n; ++i) {
        p[i].ang = atan2(p[i].y - p[1].y, p[i].x - p[1].x);
      }
      std::sort(p + 2, p + n + 1, cmp);
      sta[++top] = 1;
      for (int i = 2; i <= n; ++i) {
        while (top >= 2 &&
               cross(p[sta[top]] - p[sta[top - 1]], p[i] - p[sta[top]]) < 0) {
          top--;
        }
        sta[++top] = i;
      }
      return 0;
    }
    ```

## Minkowski Sum

### Definition

The Minkowski sum $P+Q$ of point sets $P$ and $Q$ is defined as $P+Q=\{a+b|a\in P,b\in Q\}$. That is, regard every point in point set $Q$ as a vector, translate every point in point set $P$ along these vectors, and the final set of results is point set $P+Q$. Here we only discuss the Minkowski sum of **convex hulls**.

For example, for point set $P=\{(0,0),(-3,3),(2,1)\}$ and point set $Q=\{(0,0),(-1,3),(1,4),(2,2)\}$,

![](./images/convex-hull1.svg)

translate $P$ along each vector in $Q$:

![](./images/convex-hull2.svg)

It is not hard to see that the new figure is also a **convex hull**:

![](./images/convex-hull3.svg)

### Properties

1.  If point sets $P$ and $Q$ are convex sets, then their Minkowski sum $P+Q$ is also convex.

    ??? note "Proof"
        Let $e,f\in P+Q$. Then there exist $a,b \in P$ and $c,d\in Q$ such that $e=a+c,f=b+d$. For any $t\in[0,1]$, we have:
        
        $$
        \begin{aligned}
        te + (1-t)f &= t(a+c)+(1-t)(b+d)\\
        &=(ta+(1-t)b)+(tc+(1-t)d)\\
        &\in P+Q.
        \end{aligned}
        $$
        
        This proves the claim.
2.  If point sets $P$ and $Q$ are convex sets, then the edge set of their Minkowski sum $P+Q$ is the result of connecting the edges of convex sets $P$ and $Q$ after sorting them by polar angle.

    ??? note "Proof"
        Without loss of generality, assume that the slope of any edge in convex set $P$ differs from the slope of any edge in $Q$. Rotate the coordinate system so that an edge $XY$ of $P$ is parallel to the $x$-axis and lies at the bottom.
        
        Let $U$ be the lowest point in $Q$, and let $A$ be the **lowest** and **leftmost** point of $P+Q$.
        
        We know $\vec{A} = \vec{X} + \vec{U}$, so $A$ must lie on the boundary of $P+Q$.
        
        Similarly, for the **lowest** and **rightmost** point $B$ in $P+Q$, we have $\vec{B} = \vec{Y} + \vec{U}$, so it also must lie on the boundary of $P+Q$.
        
        Therefore, $\vec{AB} = \vec{XY} + \vec{U}$.
        
        If we rotate in order, the result continuously forms every edge of $P+Q$.
        
        This proves the claim.

### Implementation

By property 2, we can sort convex sets $P,Q$ by polar angle to obtain the order in which their edges appear on $P+Q$. Treat $P_1+Q_1$ as the starting point of $P+Q$, then place edges in order using a method similar to **merge**.

Time complexity: $O(n+m)$

???+ note "Implementation"
    ```cpp
    template <class T>
    struct Point {
      T x, y;
    
      Point(T x = 0, T y = 0) : x(x), y(y) {}
    
      friend Point operator+(const Point &a, const Point &b) {
        return {a.x + b.x, a.y + b.y};
      }
    
      friend Point operator-(const Point &a, const Point &b) {
        return {a.x - b.x, a.y - b.y};
      }
    
      // Dot product
      friend T operator*(const Point &a, const Point &b) {
        return a.x * b.x + a.y * b.y;
      }
    
      // Cross product
      friend T operator^(const Point &a, const Point &b) {
        return a.x * b.y - a.y * b.x;
      }
    };
    
    template <class T>
    vector<Point<T>> minkowski_sum(vector<Point<T>> a, vector<Point<T>> b) {
      vector<Point<T>> c{a[0] + b[0]};
      for (usz i = 0; i + 1 < a.size(); ++i) a[i] = a[i + 1] - a[i];
      for (usz i = 0; i + 1 < b.size(); ++i) b[i] = b[i + 1] - b[i];
      a.pop_back(), b.pop_back();
      c.resize(a.size() + b.size() + 1);
      merge(a.begin(), a.end(), b.begin(), b.end(), c.begin() + 1,
            [](const Point<i64> &a, const Point<i64> &b) { return (a ^ b) < 0; });
      for (usz i = 1; i < c.size(); ++i) c[i] = c[i] + c[i - 1];
      return c;
    }
    ```

### Example

???+ note "[Example [JSOI2018] War](https://loj.ac/p/2549)"
    There are two convex hulls $P,Q$. Translate $Q$ a total of $q$ times, and ask whether there is an intersection after each move. $1\le n,m\le 10^5,1\le q\le 10^5$.

??? note "Implementation"
    ```cpp
    --8<-- "docs/geometry/code/convex-hull/convex-hull_1.cpp"
    ```

## Three-Dimensional Convex Hull

### Basic Knowledge

> Circle inversion: the inversion center is $O$ and the inversion radius is $R$. If a line passing through $O$ passes through $P$,$P'$, and $OP\times OP'=R^{2}$, then $P$ and $P'$ are called inverses with respect to $O$.

### Procedure

The process of finding the convex hull is as follows:

-   First apply a tiny perturbation to avoid four coplanar points.
-   Given a known convex hull, add a new point $P$. Regard $P$ as a point light source and cast rays toward the convex hull. The visible faces and invisible faces must be separated by several edges.
-   Delete the visible faces and add the planes formed by their separating edges and $P$.
    Repeat this process. By [Pick's Theorem](./pick.md), Euler's formula, where in a convex polyhedron its vertices $V$, edges $E$, and faces $F$ satisfy $V−E+F=2$, and circle inversion, the complexity is $O(n^2)$.[^3d-v]

### Template Problem

[P4724 [Template] Three-Dimensional Convex Hull](https://www.luogu.com.cn/problem/P4724)

Repeat the process above to obtain the answer.

???+ note "Implementation"
    ```cpp
    --8<-- "docs/geometry/code/3d/3d_1.cpp"
    ```

## Exercises

-   [UVa11626 Convex Hull](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=78&page=show_problem&problem=2673)

-   [USACO5.1 Fencing the Cows](https://www.luogu.com.cn/problem/P2742)

-   [POJ1873 The Fortified Forest](http://poj.org/problem?id=1873)

-   [POJ1113 Wall](http://poj.org/problem?id=1113)

-   [USACO22JAN Multiple Choice Test P](https://www.luogu.com.cn/problem/P8101)

-   [SHOI2012 Credit Card Convex Hull](https://www.luogu.com.cn/problem/P3829)

## References and Notes

[^3d-v]: [Study Notes on Three-Dimensional Convex Hull](https://www.cnblogs.com/xzyxzy/p/10225804.html)
