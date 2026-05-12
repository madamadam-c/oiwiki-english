author: wjy-yy, Ir1d, Xeonacid

## Definitions

### Half-Plane

A line together with one side of the line. A half-plane is a set of points, namely the point set formed by a line and one side of that line. If it includes the line, it is called a closed half-plane; if it does not include the line, it is called an open half-plane.

Its analytic expression is usually $Ax+By+C\ge 0$.

In computational geometry, it is represented by vectors, and a problem consistently treats either the left side or the right side of each vector as the half-plane.

![Half-plane](./images/hpi1.svg)

### Half-Plane Intersection

Half-plane intersection is the intersection of multiple half-planes. Since a half-plane is a point set, the intersection of point sets is still a point set. It forms a region in the Cartesian plane.

This is very similar to an ordinary linear programming problem: the resulting half-plane intersection is the feasible region in linear programming. In general, the half-plane intersection is bounded, and problems often ask for quantities such as area.

It can be understood as the intersection of the right sides of every vector in a vector set, or as the solution set of the following system of inequalities.

$$
\begin{cases}
A_1x+B_1y+C\ge 0\\
A_2x+B_2y+C\ge 0\\
\cdots
\end{cases}
$$

### Kernel of a Polygon

If, for every point in a point set, the segment connecting it to any point on the polygon has no other intersection with the polygon, then this point set is called the kernel of the polygon.

Treat each edge of the polygon as a head-to-tail vector. The half-plane intersection of the sides of these vectors facing the interior of the polygon is the kernel of the polygon.

## Solution - S&I Algorithm

### Polar-Angle Sorting

The C language has a library function called `atan2(double y,double x)`, which returns $\theta\in (-\pi,\pi]$, where $\theta =\arctan \frac{y}{x}$.

Call this function directly with the vector as the argument, and sort by the returned value to obtain the new edge, or vector, set.

When sorting, if collinear vectors with the same direction are encountered, keep the one closer to the feasible region. For example, if two vectors have the same polar angle and we need the left half-plane of the vectors, then we only need to keep the vector on the left. To determine this, compare the start point or endpoint of one vector with the other and check whether it lies on the left or right.

### Maintaining a Monotonic Queue

Because a half-plane intersection is a convex polygon, we need to maintain a convex hull. Since newly added edges can only affect the earliest or latest added edges, when the hull is connected, we only need to delete elements from the front and back of the queue, so a monotonic queue is used.

Traverse the sorted vectors and maintain another array of intersection points. When the monotonic queue contains more than 2 elements, intersections are generated between them.

For the current vector, if the previous intersection point lies on the **opposite side** of the half-plane represented by this vector, then the previous edge is no longer useful.

![Monotonic queue](./images/hpi2.svg)

As shown above, suppose we take the left half-plane of each vector. After polar-angle sorting, the traversal order should be $\vec a\to\vec b\to\vec c$. When $\vec a$ and $\vec b$ enter the queue, a point $D$ is generated in the intersection array. The intersection array stores, at the same index as a vector in the queue, the intersection point between that vector and the previous vector.

Next, when enumerating $\vec c$, we find that $D$ is on the right side of $\vec c$. Because the polar angle of the vector that **generated**  $D$  **must be smaller than** that of $\vec c$, the vector that generated $D$, namely $\vec b$, no longer affects the half-plane intersection.

Another possible case is that near the end, a newly added vector starts affecting the front of the queue.

![Effect on the queue front](./images/hpi7.svg)

Still suppose we take the left half-plane of each vector. After adding vector $\vec f$, the first intersection point $G$ lies on the right side of $\vec f$. Applying the criterion above in reverse, we know that vector $\vec a$, namely the vector at the **front of the queue**, should be deleted.

Finally, use the vector at the front of the queue to remove extra vectors at the back. The vector at the front is constrained by later vectors, while the vector at the back is not. At this point they form a cycle, so the front vector can constrain the back vector.

### Obtaining the Half-Plane Intersection

If the half-plane intersection is a convex $n$-gon, then the intersection array will finally contain $n$ points. Connecting them head-to-tail gives an $n$-gon with a consistent orientation, either clockwise or counterclockwise.

At this point, triangulation can be used to compute the area. Computing area is the most basic type of problem.

Occasionally, the half-plane intersection may not exist or may have area 0, so pay attention to boundary cases.

### Notes

When there is a vector that can pop all points in the queue, meaning all points in the queue are on the right side of this vector, we **must** process the back of the queue before the front. Therefore, in the loop, we first handle the `--r;` part and then the `++l;` part; otherwise the algorithm can be wrong. The reason is as follows.

![](./images/hpi4.svg)

In the usual case, when we add an edge, vector $\vec w$, after the queue, whose order is $\left\{\vec{u},\vec{v}\right\}$, an intersection point $N$ is generated, shrinking the region after $\vec{v}$.

![](./images/hpi5.svg)

However, since each operation is generic, it is possible for point $M$ to be "squeezed out".

![](./images/hpi6.svg)

If at this point a vector $\vec a$ appears such that $M$ lies on the right side of $\vec a$, then $M$ must leave the queue. If we enumerate `++l` from the front of the queue at this point, the region is obviously expanded. In fact, point $M$ is jointly formed by $\vec u$ and $\vec v$, so we need to consider whether $\vec u$ or $\vec v$ affects the current process. Since after polar-angle sorting the vectors are in counterclockwise order, the influence of $\vec v$ is greater.

As shown above, if $M$ is confirmed to be on the right side of $\vec a$, then the influence of $\vec v$ definitely contributes nothing to the answer of the half-plane intersection.

The reason we remove the front of the queue is that **the current vector imposes a stronger constraint than the front vector**. This condition assumes that the queue has more than two segments, or vectors; otherwise the case above can occur.

Therefore, always remove from the back before removing from the front.

???+ note "Code - Comparison Part"
    ```cpp
    friend bool operator<(seg x, seg y) {
      db t1 = atan2((x.b - x.a).y, (x.b - x.a).x);
      db t2 = atan2((y.b - y.a).y, (y.b - y.a).x);  // find polar angle
      if (fabs(t1 - t2) > eps)                      // if polar angles differ
        return t1 < t2;
      return (y.a - x.a) * (y.b - x.a) >
             eps;  // determine which side vector x is on relative to y; put the leftmost first
    }
    ```

???+ note "Code - Incremental Part"
    ```cpp
    // pnt its(seg a,seg b) computes the intersection of segments a and b
    // s[] contains the vectors after polar-angle sorting
    // q[] is the vector queue
    // t[i] is the intersection of s[i-1] and s[i]
    // Code style: the queue range is (l,r]
    // We compute the half-plane on the left side of each vector
    int l = 0, r = 0;
    for (int i = 1; i <= n; ++i)
      if (s[i] != s[i - 1]) {
        // Remember to check the back first
        while (r - l > 1 && (s[i].b - t[r]) * (s[i].a - t[r]) >
                                eps)  // pop the back if the previous intersection is on the right side of the vector
          --r;
        while (r - l > 1 && (s[i].b - t[l + 2]) * (s[i].a - t[l + 2]) >
                                eps)  // pop the front if the first intersection is on the right side of the vector
          ++l;
        q[++r] = s[i];
        if (r - l > 1) t[r] = its(q[r], q[r - 1]);  // compute the new intersection
      }
    while (r - l > 1 &&
           (q[l + 1].b - t[r]) * (q[l + 1].a - t[r]) > eps)  // remember to delete extra elements
      --r;
    t[r + 1] = its(q[l + 1], q[r]);  // compute the new intersection again
    ++r;
    // Note that ++r cannot be placed inside t here.
    ```

## Exercises

[POJ 2451 Uyuw's Concert](http://poj.org/problem?id=2451) pay attention to boundaries

[POJ 1279 Art Gallery](http://poj.org/problem?id=1279) find the kernel of a polygon

[CQOI2006 Convex Polygon](https://www.luogu.com.cn/problem/P4196)
