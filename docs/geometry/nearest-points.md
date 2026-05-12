## Introduction

Given $n$ points on a two-dimensional plane, find a pair of points with the smallest Euclidean distance.

Below we introduce a divide-and-conquer algorithm with time complexity $O(n\log n)$ for this problem. The algorithm was proposed by [Franco P. Preparata](https://en.wikipedia.org/wiki/Franco_P._Preparata) in 1975, and Preparata and [Michael Ian Shamos](https://en.wikipedia.org/wiki/Michael_Ian_Shamos) proved that it is optimal under the decision-tree model.

## Procedure

As with ordinary divide-and-conquer algorithms, we split the set of $n$ points into two sets $S_1, S_2$ of equal size and recurse. But we encounter a hard part: how do we merge? That is, how do we find the closest pair where one point lies in $S_1$ and the other in $S_2$? For now, assume the merge operation has time complexity $O(n)$. Then the total complexity is $T(n) = 2T(\frac{n}{2}) + O(n) = O(n\log n)$.

First sort all points by $x_i$ as the primary key and $y_i$ as the secondary key. Then use point $p_m (m = \lfloor \frac{n}{2} \rfloor)$ as the dividing point and split the point set into $A_1,A_2$:

$$
\begin{aligned}
A_1 &= \{p_i \ \big | \ i = 0 \ldots m \}\\
A_2 &= \{p_i \ \big | \ i = m + 1 \ldots n-1 \}
\end{aligned}
$$

Recurse on the two point sets and find the closest pair inside each of them. Let their distances be $h_1,h_2$, and let the smaller value be $h$.

Now it is time to merge. We try to find a pair of points where one belongs to $A_1$, the other belongs to $A_2$, and their distance is less than $h$. Therefore, put all points whose x-coordinate differs from $x_m$ by less than $h$ into set $B$:

$$
B = \{ p_i \ \big | \ \lvert x_i - x_m \rvert < h \}
$$

In the figure, line $m$ divides the points into two parts. The points on the left of $m$ form set $A_1$, and the points on the right form set $A_2$.

Then, according to the rule $B = \{ p_i \ \big | \ \lvert x_i - x_m \rvert < h \}$, we obtain set $B$, consisting of the green points. ![nearest-points1](./images/nearest-points1.png)

For each point $p_i$ in $B$, our current goal is to find a point that is also in $B$ and whose distance from it is less than $h$. To avoid considering each pair twice, we only consider points whose y-coordinate is less than $y_i$. Clearly, for a valid point $p_j$, $y_i - y_j$ must be less than $h$. Thus we obtain a set $C(p_i)$:

$$
C(p_i) = \{ p_j\ \big |\ p_j \in B,\ y_i - h < y_j \le y_i \}
$$

Choose a point $p_i$ in point set $B$. According to the rule $C(p_i) = \{ p_j\ \big |\ p_j \in B,\ y_i - h < y_j \le y_i \}$, we obtain the set $C$, consisting of the yellow points inside the red rectangle.

![nearest-points2](./images/nearest-points2.png)

If we sort the points in $B$ by $y_i$, then $C(p_i)$ is easy to obtain: it is just a few consecutive points adjacent to $p_i$.

Thus we get the merge steps:

1.  Build set $B$.
2.  Sort the points in $B$ by $y_i$. The usual approach is $O(n\log n)$, but we can change the strategy and optimize it to $O(n)$, as explained below.
3.  For each $p_i \in B$, consider $p_j \in C(p_i)$; compute the distance for every pair $(p_i,p_j)$ and update the answer, namely the closest pair in the current set.

Notice that we mentioned sorting twice above. Since the point coordinates never change, the first sorting only needs to be performed once before divide and conquer begins. Let each recursive call return the current point set sorted by $y_i$. For the second sorting, the upper level can directly merge the two already sorted point sets from the lower level.

It may seem that this algorithm is still not optimal, because $|C(p_i)|$ could be on the order of $O(n)$, making the total complexity wrong. In fact, this is not the case: its maximum size is $7$. We give the proof below.

## Complexity Proof

We have already seen that all points in $C(p_i)$ have y-coordinates in $(y_i-h,y_i]$; also, all points in $C(p_i)$ and $p_i$ itself have x-coordinates in $(x_m-h,x_m+h)$. This forms a $2h \times h$ rectangle.

Split this rectangle into two $h \times h$ squares. Ignoring $p_i$, the points in one square are $C(p_i) \cap A_1$, and the points in the other are $C(p_i) \cap A_2$. The distance between any two points inside either square is greater than $h$, because they come from the same lower-level recursive subproblem.

Split an $h \times h$ square into four $\frac{h}{2} \times \frac{h}{2}$ small squares. Each small square contains at most $1$ point, because the maximum distance between any two points in such a small square is the diagonal length, namely $\frac{h}{\sqrt 2}$, which is less than $h$.

![nearest-points3](./images/nearest-points3.png)

Therefore, each square contains at most $4$ points, the rectangle contains at most $8$ points, and after removing $p_i$ itself, $\max(C(p_i))=7$.

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/geometry/code/nearest-points/nearest-points_1.cpp"
    ```

## Extension: Minimum-Perimeter Triangle on the Plane

The algorithm above extends interestingly to this problem: given a set of points, choose three points so that the sum of their pairwise distances is minimized.

The algorithm is mostly unchanged. Each time, try to find a triangle with perimeter smaller than the current answer $d$. Put all points whose x-coordinate differs from $x_m$ by less than $\frac{d}{2}$ into set $B$ and try to update the answer. The longest side of a triangle with perimeter $d$ is less than $\frac{d}{2}$.

## Non-Divide-and-Conquer Algorithm

In fact, besides the divide-and-conquer algorithm above, there is another non-divide-and-conquer algorithm with the same time complexity $O(n \log n)$.

We can use a common idea from sequence counting: for each element, add the contributions between it and all elements to its left to the answer. The closest pair of points problem can also use this idea.

Specifically, sort all points by $x_i$ as the primary key and $y_i$ as the secondary key, and build a multiset keyed by $y_i$. For each position $i$, perform the following operations:

1.  Remove from the set all points satisfying $x_i - x_j \ge d$. They will no longer contribute to the answer.
2.  For all points in the set satisfying $\lvert y_i - y_j \rvert < d$, compute their distances to $p_i$.
3.  Insert $p_i$ into the set.

Since each point is inserted and removed at most once, the time complexity of insertions and deletions is $O(n \log n)$. The proof for the time complexity of the answer-computation part is similar to the complexity proof for the divide-and-conquer algorithm; readers may try it themselves.

??? example "Reference Implementation"
    ```cpp
    --8<-- "docs/geometry/code/nearest-points/nearest-points_2.cpp"
    ```

## Expected Linear-Time Method

In fact, besides the $O(n \log n)$ methods above, there is also an algorithm with **expected** complexity $O(n)$.

First [shuffle](../misc/random.md#shuffle) the points randomly. We maintain the answer for each prefix point set. Consider deriving the answer for the first $i$ points from the answer for the first $i - 1$ points.

Let the closest-pair distance among the first $i - 1$ points be $s$. Divide the plane into grids with side length $s$, and store the points in each grid cell, using a [hash table](../ds/hash.md). Then check all points in the nine grid cells around the cell containing the $i$-th point and update the answer. The number of points that need to be checked is $O(1)$, because the closest-pair distance among the first $i - 1$ points is $s$, so each grid cell contains at most $4$ points.

If the answer is updated during this process, rebuild the grid; otherwise, do not rebuild it. Among the first $i$ points, the probability that the closest pair contains point $i$ is $O\left(\frac{1}{i}\right)$, while rebuilding the grid costs $O(i)$. Therefore, the expected cost of processing the $i$-th point is $O(1)$. Hence, for $n$ points, the expected complexity of the algorithm is $O(n)$.

## Exercises

-   [UVa 10245 "The Closest Pair Problem" [difficulty: low]](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1186)
-   [SPOJ #8725 CLOPPAIR "Closest Point Pair" [difficulty: low]](https://www.spoj.com/problems/CLOPPAIR/)
-   [CODEFORCES Team Olympiad Saratov - 2011 "Minimum amount" [difficulty: medium]](http://codeforces.com/contest/120/problem/J)
-   [SPOJ #7029 CLOSEST "Closest Triple" [difficulty: medium]](https://www.spoj.com/problems/CLOSEST/)
-   [Google Code Jam 2009 Final "Min Perimeter" [difficulty: medium]](https://github.com/google/coding-competitions-archive/blob/main/codejam/2009/world_finals/min_perimeter/statement.pdf)

## References and Further Reading

**The divide-and-conquer section of this page is mainly translated from the blog post [Нахождение пары ближайших точек](http://e-maxx.ru/algo/nearest_points) and its English translation [Finding the nearest pair of points](https://github.com/e-maxx-eng/e-maxx-eng/blob/master/src/geometry/nearest_points.md). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**

[Zhihu Column: Computational Geometry - Closest Pair Problem](https://zhuanlan.zhihu.com/p/74905629)
