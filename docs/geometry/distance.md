author: Chrogeek, frank-xjh, ChungZH, hsfzLZH1, Marcythm, Planet6174, partychicken, i-Yirannn

## Euclidean Distance

### Two-Dimensional Space

#### Definition

Euclidean distance is also commonly called Euclidean metric. In a Cartesian coordinate system on the plane, suppose the coordinates of points $A,B$ are $A(x_1,y_1),B(x_2,y_2)$ respectively. Then the Euclidean distance between the two points is:

$$
\left | AB \right | = \sqrt{\left ( x_2 - x_1 \right )^2 + \left ( y_2 - y_1 \right )^2}
$$

#### Explanation

For example, if there are two points $A(6,5),B(2,2)$ in the Cartesian plane, the formula easily gives the Euclidean distance between $A,B$:

$$
\left | AB \right | = \sqrt{\left ( 2 - 6 \right )^2 + \left ( 2 - 5 \right )^2} = \sqrt{4^2+3^2} = 5
$$

In addition, the Euclidean distance from $P(x,y)$ to the origin can be expressed as:

$$
|P| = \sqrt{x^2+y^2}
$$

### n-Dimensional Space

#### Introduction

What about the formula for the Euclidean distance between two points in three-dimensional space? Consider the figure below.

![dis-3-dimensional](./images/distance-0.png)

It is easy to see that in $\triangle ADC$, $\angle ADC = 90^\circ$; and in $\triangle ACB$, $\angle ACB = 90^\circ$.

$$
\begin{aligned}
\therefore ~ |AB| &= \sqrt{|AC|^2+|BC|^2} \\
&= \sqrt{|AD|^2+|CD|^2+|BC|^2}
\end{aligned}
$$

#### Definition

Therefore, the Euclidean distance formula in three-dimensional space is:

$$
\begin{gathered}
\left | AB \right | = \sqrt{\left ( x_2 - x_1 \right )^2 + \left ( y_2 - y_1 \right )^2 + \left ( z_2 - z_1 \right )^2} \\
|P| = \sqrt{x^2+y^2+z^2}
\end{gathered}
$$

#### Explanation

[NOIP2017 Senior Group Cheese](https://uoj.ac/problem/332) uses this fact and can serve as an example problem for Euclidean distance.

By analogy, we obtain the Euclidean distance formula in $n$-dimensional space: for $\vec A(x_{11}, x_{12}, \cdots,x_{1n}) ,~ \vec B(x_{21}, x_{22}, \cdots,x_{2n})$, we have

$$
\begin{aligned}
\lVert\overrightarrow{AB}\rVert &= \sqrt{\left ( x_{11} - x_{21} \right )^2 + \left ( x_{12} - x_{22} \right )^2 + \cdot \cdot \cdot +\left ( x_{1n} - x_{2n} \right )^2}\\
&= \sqrt{\sum_{i = 1}^{n}(x_{1i} - x_{2i})^2}
\end{aligned}
$$

Although Euclidean distance is useful, it also has an obvious drawback. When computing the Euclidean distance between two integer-coordinate points, the answer is often a floating-point value and may contain some error.

## Manhattan Distance

### Definition

In two-dimensional space, the Manhattan distance between two points is the sum of the absolute difference of their x-coordinates and the absolute difference of their y-coordinates. Let the points be $A(x_1,y_1),B(x_2,y_2)$. Then the Manhattan distance between $A,B$ can be expressed as:

$$
d(A,B) = |x_1 - x_2| + |y_1 - y_2|
$$

### Explanation

Observe the figure below:

![manhattan-dis-diff](./images/distance-1.png)

Between $A,B$, the yellow and orange lines both represent Manhattan distance, while the red and blue lines represent equivalent Manhattan distances, and the green line represents Euclidean distance.

For the same example, in the figure below, the coordinates of $A,B$ are $A(25,20),B(10,10)$ respectively.

![manhattan-dis](./images/distance-2.svg)

Using the formula, we easily get the Manhattan distance between $A,B$:

$$
d(A,B) = |20 - 10| + |25 - 10| = 10 + 15 = 25
$$

After derivation, the Manhattan distance formula in $n$-dimensional space is:

$$
\begin{aligned}
d(A,B) &= |x_1 - y_1| + |x_2 - y_2| + \cdot \cdot \cdot + |x_n - y_n|\\
&= \sum_{i = 1}^{n}|x_i - y_i|
\end{aligned}
$$

### Properties

Besides the formula, Manhattan distance has the following mathematical properties:

-   Non-negativity: Manhattan distance is nonnegative, namely $d(i,j)\geq 0$.
-   Identity: the Manhattan distance from a point to itself is $0$, namely $d(i,i) = 0$.
-   Symmetry: the Manhattan distance from $A$ to $B$ equals that from $B$ to $A$, namely $d(i,j) = d(j,i)$.
-   Triangle inequality: the direct distance from point $i$ to $j$ is no greater than the distance through any other point $k$, namely $d(i,j)\leq d(i,k)+d(k,j)$.

### Example

[P5098「USACO04OPEN」Cave Cows 3](https://www.luogu.com.cn/problem/P5098)

According to the statement, for the expression $|x_1-x_2|+|y_1-y_2|$, we can assume $x_1 - x_2 \geq 0$ and split into two cases according to the sign of $y_1 - y_2$:

-   $(y_1 - y_2 \geq 0)\rightarrow |x_1-x_2|+|y_1-y_2|=x_1 + y_1 - (x_2 + y_2)$

-   $(y_1 - y_2 < 0)\rightarrow |x_1-x_2|+|y_1-y_2|=x_1 - y_1 - (x_2 - y_2)$

It is enough to find the maximum and minimum values of $x+y, x-y$ respectively.

??? note "Reference Code"
    === "C++"
        ```cpp
        #include <algorithm>
        #include <cstdio>
        using namespace std;
        
        int main() {
          int n, x, y, minx = 0x7fffffff, maxx = 0, miny = 0x7fffffff, maxy = 0;
          scanf("%d", &n);
          for (int i = 1; i <= n; i++) {
            scanf("%d%d", &x, &y);
            minx = min(minx, x + y), maxx = max(maxx, x + y);
            miny = min(miny, x - y), maxy = max(maxy, x - y);
          }
          printf("%d\n", max(maxx - minx, maxy - miny));
          return 0;
        }
        ```
    
    === "Python"
        ```python
        minx = 0x7FFFFFFF
        maxx = 0
        miny = 0x7FFFFFFF
        maxy = 0
        n = int(input())
        for i in range(1, n + 1):
            x, y = map(lambda x: int(x), input().split())
            minx = min(minx, x + y)
            maxx = max(maxx, x + y)
            miny = min(miny, x - y)
            maxy = max(maxy, x - y)
        print(max(maxx - minx, maxy - miny))
        ```

There is actually a second approach: transform Manhattan distance into Chebyshev distance. This will be discussed in the final part.

## Chebyshev Distance

### Definition

Chebyshev distance is a metric in vector spaces. The distance between two points is defined as the maximum absolute difference among their coordinate values.[^ref1]

In two-dimensional space, the Chebyshev distance between two points is the maximum of the absolute difference of their x-coordinates and the absolute difference of their y-coordinates. Let the points be $A(x_1,y_1),B(x_2,y_2)$. Then the Chebyshev distance between $A,B$ can be expressed as:

$$
d(A,B) = \max(|x_1 - x_2|, |y_1 - y_2|)
$$

The Chebyshev distance formula in $n$-dimensional space can be expressed as:

$$
\begin{aligned}
d(x,y) &= \max\begin{Bmatrix} |x_1 - y_1|,|x_2 - y_2|,\cdot \cdot \cdot,|x_n - y_n|\end{Bmatrix} \\
&= \max\begin{Bmatrix} |x_i - y_i|\end{Bmatrix}(i \in [1, n])\end{aligned}
$$

### Explanation

Using the same example, in the figure below, the coordinates of $A,B$ are $A(25,20),B(10,10)$ respectively.

![Chebyshev-dis](./images/distance-2.svg)

$$
d(A,B) = \max(|20 - 10|, |25 - 10|) = \max(10, 15) = 15
$$

## Conversion Between Manhattan Distance and Chebyshev Distance

### Procedure

First, consider drawing all points in the Cartesian plane whose Manhattan distance to the origin is $1$.

From the formula, we easily obtain the equation $|x| + |y| = 1$.

Expanding the absolute values gives $4$ linear functions:

$$
\begin{aligned}
&y = -x + 1 &(x \geq 0, y \geq 0) \\
&y = x + 1 &(x \leq 0, y \geq 0) \\
&y = x - 1  &(x \geq 0, y \leq 0)  \\
&y = -x - 1  &(x \leq 0, y \leq 0) \\
\end{aligned}
$$

Drawing these $4$ functions in the Cartesian plane gives a square with side length $\sqrt{2}$, as shown below:

![dis-diff-square-1](./images/distance-3.svg)

Every point on the boundary of the square has Manhattan distance $1$ to the origin.

Similarly, consider drawing all points in the Cartesian plane whose Chebyshev distance to the origin is $1$.

From the formula, we know $\max(|x|,|y|)=1$.

Expanding the expression, we also obtain $4$ line segments:

$$
\begin{aligned}
&y = 1&(-1\leq x \leq 1) \\
&y = -1&(-1\leq x \leq 1) \\
&x = 1,&(-1\leq y \leq 1) \\
&x = -1,&(-1\leq y \leq 1) \\
\end{aligned}
$$

Drawing them in the Cartesian plane gives a square with side length $2$, as shown below:

![dis-diff-square-2](./images/distance-4.svg)

Every point on the boundary of the square has Chebyshev distance $1$ to the origin.

Comparing these two figures, we surprisingly find that:

These $2$ squares are similar figures.

### Proof

So, is there a relationship between Manhattan distance and Chebyshev distance?

We briefly prove it below:

Assume $A(x_1,y_1),B(x_2,y_2)$.

If we expand the absolute values in the Manhattan distance, we obtain four values. The maximum of these four values is the sum of two nonnegative numbers, namely the Manhattan distance. Therefore, the Manhattan distance between $A,B$ is:

$$
\begin{aligned}
d(A,B)&=|x_1 - x_2| + |y_1 - y_2|\\
&=\max\begin{Bmatrix} x_1 - x_2 + y_1 - y_2, x_1 - x_2 + y_2 - y_1,x_2 - x_1 + y_1 - y_2, x_2 - x_1 + y_2 - y_1\end{Bmatrix}\\
&= \max(|(x_1 + y_1) - (x_2 + y_2)|, |(x_1 - y_1) - (x_2 - y_2)|)
\end{aligned}
$$

It is easy to see that this is exactly the Chebyshev distance between points $(x_1 + y_1,x_1 - y_1), (x_2 + y_2,x_2 - y_2)$.

Thus, after transforming every point $(x,y)$ into $(x + y, x - y)$, Chebyshev distance in the new coordinate system equals Manhattan distance in the original coordinate system.

Similarly, the Chebyshev distance between $A,B$ is:

$$
\begin{aligned}
d(A,B)&=\max\begin{Bmatrix} |x_1 - x_2|,|y_1 - y_2|\end{Bmatrix}\\
&=\max\begin{Bmatrix} \left|\dfrac{x_1 + y_1}{2}-\dfrac{x_2 + y_2}{2}\right|+\left|\dfrac{x_1 - y_1}{2}-\dfrac{x_2 - y_2}{2}\right|\end{Bmatrix}
\end{aligned}
$$

This is exactly the Manhattan distance between points $(\dfrac{x_1 + y_1}{2},\dfrac{x_1 - y_1}{2}), (\dfrac{x_2 + y_2}{2},\dfrac{x_2 - y_2}{2})$.

Thus, after transforming every point $(x,y)$ into $(\dfrac{x + y}{2},\dfrac{x - y}{2})$, Manhattan distance in the new coordinate system equals Chebyshev distance in the original coordinate system.

### Conclusions

-   The Manhattan coordinate system is obtained by rotating the Chebyshev coordinate system by $45^\circ$ and then scaling it down to half its original size.
-   After changing the coordinates of a point $(x,y)$ to $(x + y, x - y)$, Manhattan distance in the original coordinate system equals Chebyshev distance in the new coordinate system.
-   After changing the coordinates of a point $(x,y)$ to $(\dfrac{x + y}{2},\dfrac{x - y}{2})$, Chebyshev distance in the original coordinate system equals Manhattan distance in the new coordinate system.

When encountering problems involving Chebyshev distance or Manhattan distance, we can often transform one into the other. The two distances have different advantages and disadvantages in different problems, so use them flexibly.

### Examples

[P4648 [IOI2007] pairs](https://www.luogu.com.cn/problem/P4648) (Manhattan distance to Chebyshev distance)

[P3964 [TJOI2013] Squirrel Gathering](https://www.luogu.com.cn/problem/P3964) (Chebyshev distance to Manhattan distance)

Finally, here is the second solution to [P5098「USACO04OPEN」Cave Cows 3](https://www.luogu.com.cn/problem/P5098):

Consider transforming the Manhattan distance required by the problem into Chebyshev distance, namely changing the coordinates of each point $(x,y)$ into $(x + y, x - y)$.

The desired answer becomes $\max\limits_{i,j\in n}\begin{Bmatrix} \max\begin{Bmatrix} |x_i - x_j|,|y_i - y_j|\end{Bmatrix}\end{Bmatrix}$.

Now, to maximize the difference of x-coordinates and y-coordinates, it is enough to preprocess the maximum and minimum values of $x,y$.

??? note "Reference Code"
    === "C++"
        ```cpp
        #include <algorithm>
        #include <cstdio>
        using namespace std;
        
        int main() {
          int n, x, y, a, b, minx = 0x7fffffff, maxx = 0, miny = 0x7fffffff, maxy = 0;
          scanf("%d", &n);
          for (int i = 1; i <= n; i++) {
            scanf("%d%d", &a, &b);
            x = a + b, y = a - b;
            minx = min(minx, x), maxx = max(maxx, x);
            miny = min(miny, y), maxy = max(maxy, y);
          }
          printf("%d\n", max(maxx - minx, maxy - miny));
          return 0;
        }
        ```
    
    === "Python"
        ```python
        minx = 0x7FFFFFFF
        maxx = 0
        miny = 0x7FFFFFFF
        maxy = 0
        n = int(input())
        for i in range(1, n + 1):
            a, b = map(lambda x: int(x), input().split())
            x = a + b
            y = a - b
            minx = min(minx, x)
            maxx = max(maxx, x)
            miny = min(miny, y)
            maxy = max(maxy, y)
        print(max(maxx - minx, maxy - miny))
        ```

Comparing the two pieces of code, we can also see that two different ideas lead to completely equivalent code. Isn't that interesting? Of course, deeper topics are left for readers to study further.

## Minkowski Distance

We define the Minkowski distance between two points $X(x_1, x_2, \dots, x_n)$ and $Y(y_1, y_2, \dots, y_n)$ in $n$-dimensional space as:

$$
D(X, Y) = \left(\sum_{i=1}^n \left\vert x_i - y_i \right\vert ^p\right)^{\frac{1}{p}}.
$$

In particular:

1.  When $p=1$, $D(X, Y) = \sum_{i=1}^n \left\vert x_i - y_i \right\vert$ is the Manhattan distance.
2.  When $p=2$, $D(X, Y) = \left(\sum_{i=1}^n (x_i - y_i)^2\right)^{1/2}$ is the Euclidean distance.
3.  When $p \to \infty$, $D(X, Y) = \lim_{p \to \infty}\left(\sum_{i=1}^n \left\vert x_i - y_i \right\vert ^p\right) ^{1/p} = \max\limits_{i=1}^n \left\vert x_i - y_i \right\vert$ is the Chebyshev distance.

Note: Minkowski distance is a metric only when $p \ge 1$. For a detailed proof, see [Minkowski distance - Wikipedia](https://en.wikipedia.org/wiki/Minkowski_distance).

## References and Links

1.  [A Brief Discussion of Three Common Distance Algorithms](https://www.luogu.com.cn/blog/xuxing/Distance-Algorithm), thanks to author xuxing for authorization.

[^ref1]: [Chebyshev distance - Wikipedia](https://zh.wikipedia.org/wiki/%E5%88%87%E6%AF%94%E9%9B%AA%E5%A4%AB%E8%B7%9D%E7%A6%BB)
