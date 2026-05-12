## Introduction

This page lists several common dynamic-programming (DP) optimization methods. DP optimization refers to the fact that many DP problems have easy-to-write naive transition equations, but computing them directly is often inefficient, so additional techniques are needed to reduce time complexity.

These methods are closely related, often contain similar ideas, and often need to be combined. Therefore, this page gives only a rough classification and focuses on the most basic ideas.

## Optimizing with Common Techniques

Many DP transitions can be optimized with common algorithms and data structures.

There are two common situations. In the first, the DP problem has a transition equation like:

$$
f(i) = F(a_i,\{f(j) : j < i\}).
$$

Here, computing the current state $f(i)$ depends on the current input $a_i$ and all previous states $\{f(j):j<i\}$. Therefore, we can maintain a data structure and treat each computation of $f(i)$ as a query. After obtaining $f(i)$, perform an update on the data structure so it can be used in later transitions.

In the second situation, the DP problem has a transition equation like:

$$
f(i,\cdot) = F(a_i,f(i-1,\cdot)).
$$

Here, each $f(i,\cdot)$ is an array or another relatively complex object. Although $f(i,\cdot)$ depends only on the single previous state, each transition is expensive, so data structures or similar techniques are needed to optimize it.

### Prefix-sum Optimization for DP

Related page: [Prefix Sum](../../basic/prefix-sum.md#前缀和)

If the current state depends on the sum of a subsegment of previous states, maintain prefix sums to speed up computation. A class of problems involving high-dimensional prefix sums is also called [SOS DP](../../basic/prefix-sum.md#特例子集和-dp).

Exercises:

-   [Luogu P2513 \[HAOI2009\] Inversion Sequence](https://www.luogu.com.cn/problem/P2513)
-   [AtCoder Educational DP Contest M - Candies](https://atcoder.jp/contests/dp/tasks/dp_m)

### Monotone Queue/Stack Optimization for DP

Main page: [Monotone Queue/Stack Optimization](./monotonous-queue-stack.md)

If the current state depends on range extrema or similar information from previous states, maintain a monotone queue or monotone stack to speed up computation.

### Segment Tree/Fenwick Tree Optimization for DP

Related pages: [Segment Tree](../../ds/seg.md), [Fenwick Tree](../../ds/fenwick.md)

If every state transition queries sums, extrema, or similar information over an interval, or if a single update involves range updates, maintain a segment tree or Fenwick tree to speed up computation.

Exercises:

-   [AtCoder Educational DP Contest Q - Flowers](https://atcoder.jp/contests/dp/tasks/dp_q)
-   [AtCoder Educational DP Contest W - Intervals](https://atcoder.jp/contests/dp/tasks/dp_w)
-   [Codeforces 115 E. Linear Kingdom Races](https://codeforces.com/problemset/problem/115/E)

### CDQ Divide-and-Conquer Optimization for DP

Main page: [CDQ Divide-and-Conquer Optimization for DP](../../misc/cdq-divide.md#cdq-分治优化-1d1d-动态规划的转移)

As above, view the whole DP process as a sequence of queries and updates. For some problems, computing sequentially is too expensive. We can process the whole query/update process offline and use CDQ divide-and-conquer to speed up computation.

CDQ divide-and-conquer optimization for DP also commonly appears in the following kinds of problems:

-   [Convex hull trick DP based on CDQ divide-and-conquer](./slope.md#二分cdq平衡树优化-dp)
-   [Divide-and-conquer optimization for monotone-decision DP](./quadrangle.md#divide-and-conquer)

### Binary-lifting Optimization for DP

Related page: [Binary Lifting](../../basic/binary-lifting.md)

In some problems, state $f(i)$ is defined as the result after applying $2^i$ transitions from the initial state. This uses the idea of binary lifting to transform the original problem, so it is often called binary-lifting-optimized DP.

Sometimes, DP problems with a transition equation like:

$$
f(i,j) = f(i-1,f(i-1,j))
$$

are also called binary-lifting DP or binary-lifting-optimized DP.

Exercises:

-   [Luogu P1081 \[NOIP 2012 Advanced\] Driving Travel](https://www.luogu.com.cn/problem/P1081)
-   [Luogu P1613 Running Away](https://www.luogu.com.cn/problem/P1613)
-   [Luogu P4739 \[CERC2017\] Donut Drone](https://www.luogu.com.cn/problem/P4739)

## Optimizing with Problem Structure

Many DP problems have structural properties such as convexity and monotonicity. Using these properties properly can make them fast to solve.

### Convex Hull Trick DP

Main page: [Convex Hull Trick](./slope.md)

Similar to the optimization methods in the previous section, if the problem has convexity, maintain a convex hull to speed up each transition.

### Quadrangle Inequality Optimization for DP

Main page: [Quadrangle Inequality Optimization](./quadrangle.md)

DP problems whose involved functions satisfy the quadrangle inequality often satisfy some form of decision monotonicity. This property enables many specialized methods for reducing computational complexity. Common problem types include one-dimensional decision-monotonicity problems, interval partitioning problems, and interval merging problems.

### Slope Trick Optimization for DP

Main page: [Slope Trick](./slope-trick.md)

In some problems, the difference of the state function, namely its slope, is easier to maintain during state transitions. This optimization also usually requires the problem to have convexity.

### WQS Binary Search / Convex Optimization for DP

Main page: [WQS Binary Search](./wqs-binary-search.md)

For optimization DP problems with a count constraint, if the problem is easier to solve when the count constraint is ignored and the optimal value is a convex function of that constraint, WQS binary search can simplify the computation.

## Optimizing with Mathematical Methods

Many DP transitions can be accelerated with mathematical tools.

### Fast Matrix Exponentiation Optimization for DP

Related page: [Binary Exponentiation](../../math/binary-exponentiation.md)

If the state transition equation of a DP problem can be written in an autonomous form:

$$
f(i) = F(f(i-1)),
$$

that is, the current state $f(i)$ depends only on the previous state $f(i-1)$ and not on other input, then fast exponentiation can directly accelerate the computation:

$$
f(n) = F^n(f(0))
$$

This obtains the final answer. Since a single operation $F$ can often be written as a matrix, this method is commonly called fast-matrix-exponentiation optimization for DP. In fact, any associative transformation, i.e. any element of a [monoid](../../math/algebra/basic.md#群), can use this method for acceleration.

Exercises:

-   [Luogu P1397 \[NOI2013\] Matrix Game](https://www.luogu.com.cn/problem/P1397)
-   [Luogu P3176 \[HAOI2015\] Digit String Splitting](https://www.luogu.com.cn/problem/P3176)
-   [Codeforces 576 D. Flights for Regular Customers](https://codeforces.com/problemset/problem/576/D)
-   [Luogu P6772 \[NOI2020\] Gourmet](https://www.luogu.com.cn/problem/P6772)

### FFT Optimization for DP

Related page: [FFT](../../math/poly/fft.md)

If the transition equation of a DP problem has the form of a convolution, consider using FFT to accelerate transitions. Depending on the specific problem, other polynomial techniques may also be useful.

Exercises:

-   [Codeforces 553 E. Kyoya and Train](https://codeforces.com/contest/553/problem/E)
-   [Codeforces 1784 D. Wooden Spoon](https://codeforces.com/problemset/problem/1784/D)

### Lagrange Interpolation Optimization for DP

Related page: [Lagrange Interpolation](../../math/numerical/interp.md#lagrange-插值法)

For some DP problems, the state function $f(i,j)$ is a degree-$k$ polynomial in $j$. In this case, directly compute its values at $k+1$ points, use Lagrange interpolation to obtain the expression for $f(i,\cdot)$, and then optimize transitions or even obtain the answer directly.

Exercises:

-   [Luogu P5223 Function](https://www.luogu.com.cn/problem/P5223)
-   [Luogu P4463 \[Training Team Mutual Test 2012\] calc](https://www.luogu.com.cn/problem/P4463)
-   [Luogu P5469 \[NOI2019\] Robot](https://www.luogu.com.cn/problem/P5469)

## Optimizing by Simplifying States

Besides optimizing transitions, we can also reduce computational complexity by simplifying states.

### DP of DP and DFA Minimization

Main pages: [DP of DP](../dp-of-dp.md), [DFA Minimization](../../misc/fsm.md#dfa-最小化)

Some DP problems have a state function of the form $f(i,x)$, but the transition of $x$ itself is complicated and may even depend on another DP problem. For such problems, first build an automaton for transitions of state $x$, use DFA minimization to reduce the number of states, and then run the outer DP.

### State Design Optimization for DP

Main page: [State Design Optimization](./state.md)

Some special problems can greatly reduce the number of states through clever state design.

## Further Reading

-   [A miscellany of DP optimization methods by Alex Wei](https://www.cnblogs.com/alex-wei/p/DP_Involution.html)
