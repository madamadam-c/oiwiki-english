This page introduces CDQ divide and conquer.

## Introduction

CDQ divide and conquer is an idea rather than a specific algorithm, similar to [dynamic programming](../dp/index.md). This idea has been extended widely. Depending on the principle and implementation, it is roughly divided into three categories:

-   Solving problems related to pairs of points.
-   Optimizing and transferring 1D dynamic programming.
-   Transforming some dynamic problems into static problems through CDQ divide and conquer.

The idea of CDQ divide and conquer was first organized and summarized by IOI 2008 gold medalist Danqi Chen in high school, and it is named after her initials.[^ref1]

## Solving Problems Related to Pairs of Points

Most problems of this type are similar to: "given a sequence of length $n$, count the number of pairs $(i,j)$ with certain properties", or "given a sequence of length $n$, find a pair $(i,j)$ that maximizes the value of some function".

The algorithmic process for using CDQ divide and conquer to solve this type of problem is as follows:

1.  Find the midpoint $mid$ of the sequence;

2.  Divide all pairs $(i,j)$ into 3 categories:

    1.  Pairs satisfying $1 \leq i \leq mid,1 \leq j \leq mid$;
    2.  Pairs satisfying $1  \leq i \leq mid ,mid+1 \leq j \leq n$;
    3.  Pairs satisfying $mid+1 \leq  i \leq n,mid+1 \leq j \leq n$.

3.  Split the sequence $(1,n)$ into two sequences $(1,mid)$ and $(mid+1,n)$. At this point, the first and third categories of pairs lie within these two sequences;

4.  Recursively process these two categories of pairs;

5.  Find a way to process the second category of pairs.

As we can see, the idea of CDQ divide and conquer is to continuously assign pairs of points to the left and right intervals recursively.

In practice, we usually use a function `solve(l,r)` to process pairs satisfying $l \leq i \leq r,l \leq j \leq r$. The recursive part of the above algorithm is implemented by `solve(l,mid)` and `solve(mid,r)`. The remaining second category of pairs requires an additional algorithm.

### Examples

???+ example "[三维偏序](https://www.luogu.com.cn/problem/P3810)"
    Given a sequence where each point has three attributes $a_i,b_i,c_i$, find how many pairs $(i,j)$ in the sequence satisfy $a_j \leq a_i$, $b_j \leq b_i$, $c_j \leq c_i$, and $j \ne i$.

??? note "Solution"
    Three-dimensional partial order is a classic CDQ divide and conquer problem.
    
    The problem asks us to count pairs of points in a sequence, so try CDQ divide and conquer.
    
    First sort the sequence by $a$.
    
    Suppose we have written `solve(l,r)` and have recursively handled `solve(l,mid)` and `solve(mid+1,r)`. What remains is to count, among pairs $(i,j)$ satisfying $l \leq i \leq mid$ and $mid+1 \leq j \leq r$, how many also satisfy the constraints $a_{i} \leq a_{j}$, $b_{i} \leq b_{j}$, and $c_{i} \leq c_{j}$.
    
    With a little thought, we find that the constraint $a_{i} \leq a_{j}$ is no longer useful: since $i$ is smaller than $mid$ and $j$ is larger than $mid$, $i$ must be smaller than $j$; after sorting the sequence by $a$, we must have $a_{i} \leq a_{j}$. Two constraints remain: $b_{i} \leq b_{j}$ and $c_{i} \leq c_{j}$. Based on these constraints, we can enumerate $j$ and find how many valid $i$ exist.
    
    To make enumeration convenient, sort all points in $(l,mid)$ and $(mid+1,r)$ by their $b$ values in increasing order. Then enumerate each $j$ in order and insert all points $i$ with $b_{i} \leq b_{j}$ into some data structure (here we choose a [Fenwick tree](../ds/fenwick.md)). Now, by querying how many points in the Fenwick tree have $c$ values less than or equal to $c_{j}$, we know how many $i$ can validly match this point $j$.
    
    When inserting a point whose $c$ value equals $x$, we add one to position $x$ in the Fenwick tree. Querying how many points in the Fenwick tree are less than $x$ is essentially computing a [prefix sum](../basic/prefix-sum.md). As long as all $c$ values have been [discretized](../misc/discrete.md) beforehand, the complexity is correct.
    
    For each $j$, we need to insert all points $i$ satisfying $b_{i} \leq b_{j}$ into the Fenwick tree. Since all $i$ and $j$ have already been sorted by $b$, inserting points into the Fenwick tree with two pointers reduces the number of insertions from $O(n^2)$ to $O(n)$.
    
    With this algorithmic process, we handle the information about the second category of pairs in $O(n\log n)$ time. The time complexity of the algorithm is then $T(n)=T(\lfloor \frac{n}{2} \rfloor)+T(\lceil \frac{n}{2} \rceil)+O(n\log n)=O(n\log^2n)$.

??? note "Sample Code"
    ```cpp
    --8<-- "docs/misc/code/cdq-divide/cdq-divide_1.cpp"
    ```

???+ example "[CQOI2011 动态逆序对](https://www.luogu.com.cn/problem/P3157)"
    For a sequence $a$, its number of inversions is defined as the number of elements in the set $\{(i,j)| i < j \wedge a_i > a_j \}$.
    
    Given a permutation of $1\sim n$, delete $m$ elements one by one in some order. Your task is to count the number of inversions in the whole sequence before each deletion.

??? note "Sample Code"
    ```cpp
    --8<-- "docs/misc/code/cdq-divide/cdq-divide_2.cpp"
    ```

## Optimizing 1D/1D Dynamic Programming Transitions with CDQ Divide and Conquer

Related content: [CDQ divide and conquer optimization for DP](../dp/opt/dp-opt.md#cdq-分治优化-dp)

1D/1D dynamic programming refers to a specific class of DP problems where the DP array is one-dimensional and each transition is $O(n)$. Under suitable conditions, CDQ divide and conquer can sometimes reduce their time complexity from $O(n^2)$ to $O(n\log^2n)$.

For example, given a sequence where each element has two attributes $a$ and $b$, suppose we want to compute a DP value with the following transition:

$dp_{i}=1+ \max_{j=1}^{i-1}dp_{j}[a_{j} < a_{i}][b_{j} < b_{i}]$

This is the DP equation for a two-dimensional longest increasing subsequence: only points $j$ satisfying $j < i,a_{j} < a_{i},b_{j} < b_{i}$ can update the DP value of point $i$.

Direct transition is clearly $O(n^2)$. The following explains how to optimize the transition process using CDQ divide and conquer.

We observe that the transition relation from $dp_{j}$ to $dp_{i}$ is also a relation between pairs of points, so we handle it similarly to how CDQ divide and conquer handles pair relations.

This transition process is relatively standard. Suppose the interval currently being processed is $(l,r)$. The algorithm is roughly as follows:

1.  If $l=r$, the $\max$ part of $dp_{r}$ has already been computed. Directly set $dp_{r} \gets dp_{r} + 1$ and return;
2.  Recursively call `solve(l,mid)`;
3.  Process all transition relations with $l \leq j \leq mid$ and $mid+1 \leq i \leq r$;
4.  Recursively call `solve(mid+1,r)`.

Step 3 is similar to using CDQ divide and conquer for three-dimensional partial order. When processing transitions with $l \leq j \leq mid$ and $mid+1 \leq i \leq r$, the constraint $j < i$ no longer needs to be considered. Therefore, we still first sort all points $i$ and $j$ by their $a$ values, then insert points $j$ into a Fenwick tree using two pointers, and finally query the prefix maximum to update $dp_{i}$.

### Correctness Proof of the Transition Process

The biggest difference between this CDQ implementation and the CDQ implementation for relations between pairs of points is the part that processes pairs with $l \leq j \leq mid$ and $mid+1 \leq i \leq r$. In the CDQ implementation for point-pair relations, this part can be placed anywhere. However, when using CDQ divide and conquer to optimize DP, this process must be placed between $solve(l,mid)$ and $solve(mid+1,r)$. The reason is that DP transitions are **ordered** and must satisfy two conditions; otherwise they are incorrect:

1.  All $dp_{j}$ values used to compute $dp_{i}$ must already be fully computed; no "semi-finished products" may exist;

2.  All $dp_{j}$ values used to compute $dp_{i}$ must be able to update $dp_{i}$; no such $dp_{j}$ value may be missed.

These two conditions are fairly easy to satisfy in the $O(n^2)$ brute-force method. After using CDQ divide and conquer, however, the transition order is clearly disrupted, so it is necessary to examine correctness.

The recursion tree of CDQ divide and conquer is shown below.

![Recursion tree of CDQ divide and conquer](./images/cdq-divide.svg)

If we execute the algorithm above, take point $8$ as an example. Its DP value is updated in the three functions `solve(1,8)`, `solve(5,8)`, and `solve(7,8)`, and the points used to update it are the three disjoint intervals $(1,4)$, $(5,6)$, and $(7,7)$. For point $5$, its DP value is handled in `solve(1,4)`, and the interval that updates it is $(1,4)$. A closer look shows that the DP value of a point $i$ is updated $\log$ times, and the updating intervals are exactly the $\log$ intervals into which $(1,i)$ is decomposed on the segment tree. Therefore, all legal $j$ have indeed updated point $i$, satisfying condition 2.

Next, analyze the execution process of the algorithm:

1.  The first function to finish is `solve(1,1)`. At this point, $dp_{1}$ has been fully computed;
2.  The first function to execute transitions is `solve(1,2)`. At this point, $dp_{2}$ has been fully transitioned;
3.  The second function to finish is `solve(2,2)`. At this point, $dp_{2}$ has been fully computed;
4.  Then `solve(1,2)` finishes, and all $dp$ values in interval $(1,2)$ have been computed;
5.  The next function to execute transitions is `solve(1,4)`. After this transition, $dp_{3}$ has been fully transitioned;
6.  The next function to finish is `solve(3,3)`. We find that the DP value of $dp_{3}$ has been computed;
7.  The next transition is `solve(3,4)`. At this point, $dp_{4}$ has been transitioned once by $(1,2)$ in `solve(1,4)`, and now it is transitioned by $(3,3)$, so $dp_{4}$ has also been fully transitioned;
8.  `solve(4,4)` finishes, and $dp_{4}$ has been fully computed;
9.  `solve(3,4)` finishes, and the values in $(3,4)$ have been computed;
10. `solve(1,4)` finishes, and the values in $(1,4)$ have been computed.
11. ……

By simulating the function process, we find that whenever `solve(l,r)` finishes, all DP values in interval $(l,r)$ have been computed. Since `solve(l,mid)` has already finished every time we execute the transition function, every transition process we execute is legal and satisfies condition 1.

From the above process, we find that if the recursion tree of CDQ divide and conquer is regarded as a segment tree, then CDQ divide and conquer is the **in-order traversal function** of this segment tree. Thus, we process all DP values in order; only the transition order has been split apart. Therefore, the algorithm is correct.

### Examples

???+ example "[SDOI2011 拦截导弹](https://www.luogu.com.cn/problem/P2487)"
    To defend against enemy missile attacks, a country developed a missile interception system. However, this system has a flaw: although its first shell can reach any height and intercept missiles of any speed, each subsequent shell cannot be higher than the previous one, and the flight speed of the missile it intercepts cannot exceed that of the previous one. One day, radar detects incoming enemy missiles. Since the system is still in trial use, there is only one system, so it may not be able to intercept all missiles.
    
    If not all missiles can be intercepted, we naturally choose the plan that minimizes national losses, namely the one that intercepts the maximum number of missiles. However, there may be multiple optimal plans. If there are multiple optimal plans, one is chosen at random as the final missile interception plan.
    
    Our spies have obtained the height and speed of every enemy missile. Your task is to compute the probability that each missile is intercepted under the decision process above.

??? note "Sample Code"
    ```cpp
    --8<-- "docs/misc/code/cdq-divide/cdq-divide_3.cpp"
    ```

## Transforming Dynamic Problems into Static Problems

In the first two cases, CDQ divide and conquer is used to halve a sequence and recursively process relations between pairs of points to obtain good complexity. In this section, however, the sequence being halved is not an ordinary sequence, but a time sequence.

It applies to some data structure problems that need to support "perform xxx modification and then answer xxx query". This type of problem has two characteristics:

-   If the queries are processed [offline](offline.md), all operations naturally form a sequence ordered by time.
-   Each modification is closely related to later query operations. There may be $O(n^2)$ such "modification-query" relations.

We can use CDQ divide and conquer on this operation sequence to process the relations between modifications and queries.

Similar to CDQ divide and conquer for point-pair relations, suppose the sequence currently being divided is $(l,r)$. We first recursively process the modification-query relations in $(l,mid)$ and $(mid,r)$, then process all modification-query relations with $l \leq i \leq mid$ and $mid+1 \leq j \leq r$, where $i$ is a modification and $j$ is a query.

Note that if the modifications are **independent** of one another, we do not need to handle the temporal relation between $l \leq i \leq mid$ and $mid+1 \leq j \leq r$, or between `solve(l,mid)` and `solve(mid+1,r)` (for example, ordinary addition and subtraction problems). But if modifications are not independent (such as assignment operations), the state of the sequence after a modification may depend on the previous sequence. In that case, the step that processes all modification-query relations crossing mid must be placed between `solve(l,mid)` and `solve(mid+1,r)`. The reason is the same as for optimizing 1D/1D dynamic programming with CDQ divide and conquer: dividing in in-order traversal order ensures that every modification is executed strictly in chronological order.

### Examples

???+ example "Rectangle Add, Rectangle Sum"
    Maintain a two-dimensional array, supporting adding a number to a rectangular region and querying the sum of a rectangular region.

??? note "Solution"
    For the version of this problem without modifications, namely "given a two-dimensional array, answer multiple queries for the sum of a rectangular region", there is a classic approach using a scanline with a segment tree. Specifically, first split each rectangle into an insertion and a deletion operation, then split each query into differences of two-dimensional prefix sums, and finally process offline. However, the original problem has modifications, so this approach cannot be used directly.
    
    Try applying CDQ divide and conquer. We process all queries and modifications offline. These operations form a sequence, with $O(N^2)$ modification-query relations. Following the general CDQ divide and conquer process, divide all relations into three categories. At this divide-and-conquer level, only process modification-query relations crossing $mid$; the remaining relations are handled recursively.
    
    We find that all modifications have already been completed before the queries. At this point, the original problem is equivalent to: "there are some static rectangles on a plane, and we repeatedly query the sum of a rectangular region".
    
    Use a scanline to process all modification-query relations crossing $mid$ in $O(n\log n)$ time. The remaining work is to recursively divide and conquer the modification-query relations on the left and right sides.
    
    In this CDQ divide and conquer implementation, the same query is processed $O(\log n)$ times. This is fine, because the modifications contributing to this query each time are disjoint. The overall time complexity is $T(n)=T(\lfloor \frac{n}{2} \rfloor)+T(\lceil \frac{n}{2} \rceil)+ O(n\log n)=O(n\log^2n)$.
    
    Observing the above algorithm, we see that at first we could only solve the static rectangle-add rectangle-sum problem, but after simply using CDQ divide and conquer, we can solve a dynamic rectangle-add rectangle-sum problem offline. The essence of transforming dynamic problems into static problems is that CDQ divide and conquer only processes modification-query relations crossing a certain point each time. Thus, we only need to consider the simple problem where "all queries occur after all modifications". This is why CDQ divide and conquer is called a "tool for transforming dynamic problems into static problems".

???+ example "[\[Ynoi2016\] 镜中的昆虫](https://www.luogu.com.cn/problem/P4690)"
    Maintain a sequence of length $n$, denoted $a_i$, with $m$ operations.
    
    1.  Modify all values in interval $[l,r]$ to $x$;
    2.  Query how many distinct numbers appear in interval $[l,r]$, where multiple occurrences of the same number are counted only once.
    
    In one sentence: interval assignment and interval color counting.

??? note "Solution"
    Maintain the position of the first point to the left of each position with the same color, denoted $pre_{i}$. Then interval color counting is transformed into a classic two-dimensional point counting problem.
    
    By treating a consecutive segment of the same color as one point, we can prove that the total change in $pre$ is $O(n+m)$, meaning each operation only causes $O(1)$ changes to $pre$ values. Then we can use CDQ divide and conquer to solve the dynamic point-add rectangle-sum problem.
    
    The specific changes of the $pre$ array can be handled using `std::set`. This technique of maintaining consecutive intervals with a set is also called [old driver tree](./odt.md).

??? note "Sample Code"
    ```cpp
    --8<-- "docs/misc/code/cdq-divide/cdq-divide_4.cpp"
    ```

???+ example "[\[HNOI2010\] 城市建设](https://www.luogu.com.cn/problem/P3206)"
    The country PS is a large country with many cities. King Louis has put great effort into urban transportation construction. Louis can build roads between some cities, and building roads between different cities has different costs.
    
    Louis wants to build the fewest roads needed to connect all cities in the country. However, due to certain factors, the cost of building roads between cities changes over time. Louis continuously receives news that the construction cost of some road has changed. After each message, he wants to immediately know the minimum total cost required to connect all cities. Louis asks you to complete this task.
    
    In one sentence: given a graph with dynamic edge-weight modifications, output the minimum total cost of the graph's minimum spanning tree after each edge-weight modification.

??? note "Solution"
    In fact, this problem can be solved by segment tree divide and conquer with LCT, but the constant factor of that implementation is too large and may require delicate constant optimization to pass. Therefore, consider using CDQ divide and conquer.
    
    Unlike ordinary problems solved by CDQ divide and conquer, here there is no modification-query relation for CDQ to divide on, because we cannot separately consider "what contribution modifying one edge makes to the minimum spanning tree of the whole graph". The traditional CDQ divide and conquer idea does not seem very effective.
    
    From the previous examples, we can see that ordinary CDQ divide and conquer has a special connection with segment trees: during CDQ divide and conquer, we implicitly build a segment tree (because the recursion tree of CDQ divide and conquer is a segment tree). Usual CDQ considers the relation between the left and right children of the segment tree. For this problem, however, we need to consider the relation between a parent and its child. In other words, when we are at the interval `$solve(l,r)$`, if we can find a way to make the graph size become a variable related to the interval length, we can solve this problem.
    
    How should the algorithm be designed in detail?
    
    Suppose we are constructing the edge set of the minimum spanning tree for interval $(l,r)$, and we already know the edge set of its parent's minimum spanning tree. For the edges that change in interval $(l,r)$, assign their weights to $+ \infty$ and $-\infty$ respectively, run Kruskal once for each case, and find the edges that appear in the minimum spanning tree.
    
    For an edge:
    
    -   If all modified edge weights in the minimum spanning tree are assigned $+\infty$, and this edge does not appear in the tree, then it cannot appear in the minimum spanning tree for the queries in $(l,r)$. Therefore, we only add the tree edges of the minimum spanning tree to the edge set of $(l,r)$.
    -   If all modified edge weights in the minimum spanning tree are assigned $-\infty$, and this edge appears in the tree, then it must appear in the minimum spanning tree for interval $(l,r)$. In that case, we can use DSU to contract the endpoints of these edges and add their weights to the answer.
    
    In this way, we construct the edge set for interval $(l,r)$. The minimum spanning tree computed using these edges is equivalent to directly computing the minimum spanning tree of the original graph.
    
    Why is the complexity correct?
    
    First, modified edges are always added to our edge set, and the number of such edges is $O(len)$.
    
    Next, we need to prove that there are not too many unmodified edges in the edge set. We only add tree edges from the minimum spanning tree when all modified edge weights are set to $+\infty$, so the number of edges we add will not exceed the number of vertices in the current graph.
    
    Now we only need to prove that the number of vertices in the graph at each recursive level is $O(len)$, which implies that the number of edges in the graph is also $O(len)$.
    
    Proving that the number of vertices is a constant multiple of $O(len)$ is then simple. Each time we recurse downward, the contracted edges are unmodified edges that appear in the $-\infty$ spanning tree. Conversely, we have cut all modified edges that appear in the $-\infty$ spanning tree. Clearly, we cut at most $len$ edges, so the whole graph splits into at most $O(len)$ connected components, and the number of vertices in the new graph is $O(len)$. Thus, we have proved that every graph on which we run Kruskal is of size $O(len)$, so the time complexity of each level is $O(n\log n)$.
    
    The time complexity is $T(n)=T(\lfloor \frac{n}{2} \rfloor)+T(\lceil \frac{n}{2} \rceil)+ O(n\log n)=O(n\log^2n)$.
    
    The code implementation may be somewhat difficult. Note that DSU cannot use path compression, otherwise rollback is not supported. When performing contractions, it is also unnecessary to actually contract vertices; each level's Kruskal can be run directly on the DSU of the previous level.

??? note "Sample Code"
    ```cpp
    --8<-- "docs/misc/code/cdq-divide/cdq-divide_5.cpp"
    ```

## References and Notes

[^ref1]: [Applications of a Class of Divide-and-Conquer Algorithms Starting from "Cash"](https://www.cs.princeton.edu/~danqic/papers/divide-and-conquer.pdf)
