author: Marcythm, hsfzLZH1, abc1763613206, greyqz, Ir1d, billchenchina, Chrogeek, Enter-tainer, StudyingFather, MrFoodinChina, luoguyuntianming, sshwy, wood3

## Introductory Example

???+ note "[HNOI2008 Toy Packing](https://loj.ac/problem/10188)"
    There are $n$ toys. The $i$-th toy has value $c_i$. Arrange the $n$ toys in a row and divide them into several segments. For a segment $[l,r]$, its cost is $(r-l+\sum_{i=l}^r c_i-L)^2$, where $L$ is a constant. Find the minimum total segmentation cost.
    
    $1\le n\le5\times10^4$, $1\le L,c_i\le10^7$.

### Naive DP Approach

Let $f_i$ denote the minimum cost for partitioning the first $i$ items into several segments.

The transition equation is $f_i=\min_{j<i}\{f_j+(i-(j+1)+pre_i-pre_j-L)^2\}=\min_{j<i}\{f_j+(pre_i-pre_j+i-j-1-L)^2\}$.

Here, $pre_i$ denotes the sum of the first $i$ numbers, i.e. $\sum_{j=1}^i c_j$.

This approach has time complexity $O(n^2)$ and cannot solve the problem.

### Optimization

Simplify the transition above. Let $s_i=pre_i+i$ and $L'=L+1$. Then $f_i=\min_{j<i}\{f_j+(s_i-s_j-L')^2\}$.

Move the terms independent of $j$ outside the minimum:

$$
f_i - (s_i-L')^2=\min_{j<i}\{f_j+s_j^2 + 2s_j(L'-s_i) \} 
$$

Consider the slope-intercept form of a linear function $y=kx+b$. Rearranging gives $b=y-kx$. We express information related to $j$ as $y$, information related to both $i$ and $j$ as $kx$, and the quantity to minimize, which is related to $i$, as $b$, the intercept. Specifically, let:

$$
\begin{aligned}
x_j&=s_j\\
y_j&=f_j+s_j^2\\
k_i&=-2(L'-s_i)\\
b_i&=f_i-(s_i-L')^2\\
\end{aligned}
$$

Then the transition becomes $b_i=\min_{j<i}\{y_j-k_ix_j\}$. Treat $(x_j,y_j)$ as points in the plane. Then $k_i$ is the slope of a line, and $b_i$ is the intercept of a line with slope $k_i$ passing through $(x_j,y_j)$. The problem becomes choosing a suitable $j$ ($1\le j<i$) to minimize the line intercept.

![slope\_optimization](../images/optimization.svg)

As shown in the figure, move the line with slope $k_i$ upward from below until some point $(x_p,y_p)$ lies on it. Then $b_i=y_p-k_ix_p$, and this is the minimum value of $b_i$. After computing $f_i$, add point $(x_i,y_i)$ to the point set as a new DP decision. How should we maintain this point set?

It is easy to see that points that may minimize $b_i$ must lie on the lower convex hull. Therefore, when finding $p$, we do not need to enumerate all $i-1$ points; only points on the convex hull need to be considered. In this problem, $k_i$ increases as $i$ increases, so we can maintain the convex hull with a monotone queue.

Specifically, let $K(a,b)$ denote the slope of the line through $(x_a,y_a)$ and $(x_b,y_b)$. Consider the queue $q_l,q_{l+1},\ldots,q_r$, which maintains points on the lower convex hull. That is, for $l<i<r$, we always have $K(q_{i-1},q_i)<K(q_i,q_{i+1})$.

Maintain a pointer $e$ to compute the minimum value of $b_i$. We need to find $e$ such that $K(q_{e-1},q_e)\le k_i<K(q_e,q_{e+1})$, with special handling when $e=l$ or $e=r$. Then $p=q_e$, so $q_e$ is the optimal decision point for $i$. Since $k_i$ is monotonically increasing, the movement of $e$ is amortized $O(1)$.

When inserting a point $(x_i,y_i)$, check whether $K(q_{r-1},q_r)<K(q_r,i)$. If this inequality does not hold, pop $q_r$ until it does. Then insert $i$ at the back of queue $q$.

This optimizes the DP complexity to $O(n)$.

To summarize the convex hull trick template above:

1.  Push the initial state into the queue.
2.  Each time, use a line $f(i)$ related to $i$ to query the maintained convex hull, find the optimal decision, and update $dp_i$.
3.  Add state $dp_i$. If an existing state, i.e. a point on the convex hull, is no longer on the hull after adding $dp_i$, remove it before adding $dp_i$.

Next, we introduce advanced applications of convex hull trick DP, combining it with binary search, divide-and-conquer, and data structures to maintain DP equations whose properties are not as nice and lack certain monotonicities.

## Binary Search / CDQ / Balanced Tree Optimization for DP

When searching for the optimal decision at point $i$, we use a line $f(i)$ related to $i$ to query the convex hull we maintain. The touched point is the optimal decision.

In the example above, the slope of the line changes monotonically with $i$. However, in some problems, the slope is not monotonic. Then we need to maintain every node on the convex hull and query the hull with the current line each time. This can be done with binary search, because slopes between adjacent points on the convex hull are monotonic.

???+ note "Modified Toy Packing"
    There are $n$ toys. The $i$-th toy has value $c_i$. Arrange the $n$ toys in a row and divide them into several segments. For a segment $[l,r]$, its cost is $(r-l+\sum_{i=l}^r c_i-L)^2$, where $L$ is a constant. Find the minimum total segmentation cost.
    
    $1\le n\le5\times10^4$, $1\le L\le10^7$, $-10^7\le c_i\le10^7$.

The only difference between this problem and Toy Packing is that toy values may be negative. Continuing the previous idea, let $f_i$ denote the minimum cost for partitioning the first $i$ items into several segments.

The transition equation is $f_i=\min_{j<i}\{f_j+(pre_i-pre_j+i-j-1-L)^2\}$.

Here, $pre_i=\sum_{j=1}^i c_j$.

Apply the same transformation:

$$
f_i - (s_i-L')^2=\min_{j<i}\{f_j+s_j^2 + 2s_j(L'-s_i) \} 
$$

However, two conditions no longer hold:

1.  The slope of the line is no longer monotonic.
2.  The x-coordinate of each inserted decision point is no longer monotonic.

Still consider maintaining the convex hull.

When finding the optimal decision point, that is, when querying the hull with a line, replace the monotone-queue front query with binary search on the convex hull. Binary search for the hull edge whose slope is closest to the query line's slope, and the optimal decision can be found.

When adding a decision point, i.e. adding a point to the convex hull, there are two maintenance methods.

The first method is to directly maintain the convex hull with a balanced tree. Then the binary-search decision query becomes a binary search on the balanced tree, and inserting a decision point becomes inserting a node into the balanced tree and deleting several points that are removed from the hull. This method has a simple idea but is cumbersome to implement.

The following introduces an approach based on [CDQ divide-and-conquer](../../misc/cdq-divide.md).

Let $\text{CDQ}(l,r)$ denote computing $f_i$ for $i\in[l,r]$. Consider $\text{CDQ}(1,n)$:

-   First call $\text{CDQ}(1,mid)$ to compute $f_i$ for $i\in[1,mid]$. Then build the convex hull from decision points in interval $[1,mid]$, and use this hull to update $f_i$ for $i\in[mid+1,n]$. At this point the decision set is fixed, unlike before where decision points were added while computing DP values. Therefore, sort $f_i$ for $i\in[mid+1,n]$ by line slope $k_i$, then use a monotone queue to compute DP values. Alternatively, binary search on the static convex hull can also compute the DP values.

-   For each point in $[mid+1,n]$, if its optimal decision lies in $[1,mid]$, this operation updates it to the optimal answer. After this step, all points in $[1,mid]$ have exerted their full effect; whether they remain in the convex hull no longer affects future answer updates. Therefore, discard the decision points in this interval and use $\text{CDQ}(mid+1,n)$ to solve the remaining problem in the right interval.

The time complexity is $O(n\log^2 n)$.

Comparing Toy Packing and Modified Toy Packing, we can summarize two points:

-   Binary search, CDQ, balanced trees, and similar techniques can optimize the computation of a DP equation and reduce complexity to some extent, but they cannot change the equation itself.
-   The properties of a DP equation depend on the data features, but the equation itself depends on the mathematical model in the problem.

## Summary

Convex hull trick DP requires flexibility. Its purpose is to transform an optimization problem into a problem about extrema of line intercepts related to a convex hull in the two-dimensional plane. For equations with weaker properties, data structures may be needed; the specific solution should be chosen according to the problem.

## Exercises

-   [SDOI2016 Journey](https://loj.ac/problem/2035)
-   [ZJOI2007 Warehouse Construction](https://loj.ac/problem/10189)
-   [APIO2010 Commando](https://loj.ac/problem/10190)
-   [JSOI2011 Lemon](https://www.luogu.com.cn/problem/P5504)
-   [Codeforces 311B Cats Transport](http://codeforces.com/problemset/problem/311/B)
-   [NOI2007 Currency Exchange](https://loj.ac/problem/2353)
-   [NOI2019 Route Home](https://loj.ac/problem/3156)
-   [NOI2016 King's Drinking Plan](https://uoj.ac/problem/223)
-   [NOI2014 Ticket Purchase](https://uoj.ac/problem/7)
