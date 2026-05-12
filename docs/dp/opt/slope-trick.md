## Introduction

For a class of two-dimensional DP problems, if the value function $f(i,x)$ is convex in $x$ for every fixed $i$, then it is often useful to regard the whole function $f(i,\cdot)$ as the state at $i$ and maintain its difference, or slope,

$$
\Delta f(i,x) = f(i,x+1)-f(i,x)
$$

instead of the function values themselves. This DP optimization idea is called the Slope Trick.

???+ info "Slope"
    In most problems the functions are only evaluated at integer points, so there is no essential difference between calling this quantity a difference and calling it a slope. This article follows the term Slope Trick and uses "slope" throughout.

The exact way to maintain slopes depends on the problem. If the range of slope values is small, it is usually convenient to maintain the points where the slope changes, namely the breakpoints. If the domain is small, maintaining the slope sequence itself may be better. More complex problems may require maintaining both the slope value of each segment and its length. In all cases, the key observation is that the slope sequence changes only slightly under the transition.

## Convex Functions

Before discussing examples, we review the basic properties of convex functions and how their slopes change under common transformations.

### Convex Functions On The Real Line

The most general definition is on $\mathbf R$.

![](../images/slope-trick/epigraph-convex-def.svg)

???+ abstract "Convex Functions On $\mathbf R$"
    A function $f:\mathbf R\rightarrow\mathbf R\cup\{\pm\infty\}$ is **convex** if for all $x,y\in\mathbf R$ and $\alpha\in(0,1)$,
    
    $$
    f(\alpha x+(1-\alpha)y) \le \alpha f(x)+(1-\alpha)f(y),
    $$
    
    Arithmetic involving $\pm\infty$ follows the usual extended-real convention: multiplying by a positive real or adding a real number keeps $\pm\infty$, and $-\infty<x<+\infty$ for every real $x$.

Changing $\le$ to $\ge$ gives concavity[^convex-def]. Since $f$ is concave iff $-f$ is convex, this article only discusses convex functions.

???+ info "Only Proper Convex Functions Are Considered"
    To avoid issues such as $\infty-\infty$, we assume a convex function never takes the value $-\infty$ and is not identically $+\infty$. Such functions are called **proper convex functions**, which is enough for competitive-programming applications.

If $f$ is only defined on a subset of $\mathbf R$, extend it by

$$
\tilde f(x) =
\begin{cases}
f(x), & x\in\operatorname{dom}f,\\
+\infty,& x\notin\operatorname{dom}f
\end{cases}
$$

Then $f$ is convex iff $\tilde f$ is convex. Thus, unless stated otherwise, convex functions are treated as functions on all of $\mathbf R$; their finite domain must be an interval.

???+ example "Simple Examples"
    Common convex functions include:
    
    1.  constant functions $f(x)=c$;
    2.  affine functions $f(x)=kx+b$ with $k\ne0$;
    3.  absolute-value functions $f(x)=|x-a|$;
    4.  restrictions of convex functions to intervals, for example $0_{[a,b]}(x)$, the indicator function of $[a,b]$ in convex analysis.

More complicated convex functions can be built from the convexity-preserving transformations below.

### Convex Functions On Discrete Sets

In competitive programming, many functions are defined only on some integer points. Their domain is not convex, so the real-line definition cannot be applied directly. The usual approach is to linearly interpolate the function and then test convexity.

![](../images/slope-trick/epigraph-convex-discrete.svg)

???+ abstract "Convex Functions On Discrete Sets"
    Let $S\subset\mathbf R$ be discrete, meaning $S\cap[a,b]$ is finite for every closed interval $[a,b]$. For $f:S\rightarrow\mathbf R\cup\{\pm\infty\}$, define $\tilde f:\mathbf R\rightarrow\mathbf R\cup\{\pm\infty\}$ by:
    
    -   if $x\in S$, then $\tilde f(x)=f(x)$;
    -   if $x\in(\inf S,\sup S)\setminus S$, let $s_- = \max\{s\in S:s\le x\}$ and $s_+ = \min\{s\in S:s\ge x\}$, and set
    
        $$
        \tilde f(x) = \dfrac{s_+-x}{s_+-s_-}f(s_-)+\dfrac{x-s_-}{s_+-s_-}f(s_+),
        $$
    -   if $x\notin[\inf S,\sup S]$, then $\tilde f(x)=+\infty$.
    
    If $\tilde f$ is convex on $\mathbf R$, then $f$ is called **convex on $S$**.

For $S=\mathbf Z$, there is a simpler equivalent condition.

???+ note "Equivalent Definition On $\mathbf Z$"
    A function $f:\mathbf Z\rightarrow\mathbf R\cup\{\pm\infty\}$ is convex iff
    
    $$
    f(x)-f(x-1)\le f(x+1)-f(x)
    $$
    
    holds for all $x\in\mathbf Z$.

??? note "Proof"
    This is the slope characterization of convexity. If $f$ is convex, slopes are nondecreasing:
    
    $$
    \Delta f(x-1,x)\le \Delta f(x-1,x+1) \le\Delta f(x,x+1).
    $$
    
    Conversely, if first differences are nondecreasing, then for any $x_1<x_2$,
    
    $$
    \Delta f(x_1,x_2) = \dfrac{1}{x_2-x_1}\sum_{i=x_1}^{x_2-1}\left(f(i)-f(i-1)\right).
    $$
    
    This is the arithmetic mean of all differences with $x_1\le i<x_2$. Moving the right endpoint right inserts a larger difference; moving the left endpoint right removes the smallest difference. Both operations increase the average, so all secant slopes are nondecreasing, which is convexity.

Thus a nondecreasing difference sequence can be viewed as a convex function on $\mathbf Z$.

### Two Characterizations Of Convexity

The slope characterization generalizes.

???+ note "Slope Characterization Of Convex Functions"
    Let $S$ be $\mathbf R$ or a discrete subset of it. A function $f:S\rightarrow\mathbf R\cup\{\pm\infty\}$ is convex iff the slope
    
    $$
    \Delta f(x_1,x_2) = \dfrac{f(x_2)-f(x_1)}{x_2-x_1}
    $$
    
    is nondecreasing in both $x_1$ and $x_2$ for all $x_1<x_2$ in $S$.

??? note "Proof"
    For functions on $\mathbf R$, set $x_3=\alpha x_1+(1-\alpha)x_2$. The inequalities
    
    $$
    \Delta f(x_1,x_3) \le \Delta f(x_1,x_2) \le \Delta f(x_3,x_2)
    $$
    
    are equivalent to
    
    $$
    \dfrac{f(x_3)-f(x_1)}{1-\alpha} \le f(x_2)-f(x_1) \le \dfrac{f(x_2)-f(x_3)}{\alpha}.
    $$
    
    Both inequalities are equivalent to $f(x_3)\le\alpha f(x_1)+(1-\alpha)f(x_2)$, namely convexity.
    
    For a function $f$ on a discrete subset $S$ of $\mathbf R$, necessity follows from convexity of $\tilde f$. For sufficiency, it is enough to prove that $\Delta\tilde f(x_1,x_2)$ is also nondecreasing. Let $S=\{s_i\}$ with $s_i$ strictly increasing in $i$, and suppose $s_{i_1}\le x_1\le s_{i_1+1}$ and $s_{i_2}\le x_2\le s_{i_2+1}$, so $i_1\le i_2$. Let $\Delta_i=\Delta f(s_i,s_{i+1})$. If $i_1=i_2$, then $\Delta_{i_1}=\Delta\tilde f(x_1,x_2)=\Delta_{i_2}$. Otherwise,
    
    $$
    \Delta\tilde f(x_1,x_2) = \dfrac{1}{x_2-x_1}\left((s_{i_1+1}-x_1)\Delta_{i_1}+(x_2-s_{i_2})\Delta_{i_2}+\sum_{j=i_1+1}^{i_2-1}(s_{j+1}-s_j)\Delta_j\right).
    $$
    
    Since the $\Delta_i$ are nondecreasing, $\Delta_{i_1}\le\Delta\tilde f(x_1,x_2)\le\Delta_{i_2}$. Applying this to $x_1<x_2$ and $x_3=\alpha x_1+(1-\alpha)x_2$, with $s_{i_3}\le x_3\le s_{i_3+1}$, gives
    
    $$
    \Delta\tilde f(x_1,x_3) \le \Delta_{i_3} \le \Delta\tilde f(x_3,x_2).
    $$
    
    Substituting the expression for $x_3$ gives convexity of $\tilde f$.

Because slopes of convex functions are monotone, data structures such as [heaps](../../ds/heap.md) and [balanced binary search trees](../../ds/bst.md) are often used to maintain them.

Another useful characterization uses the epigraph

$$
\operatorname{epi} f = \{(x,y)\in\mathbf R^2 : y\ge f(x)\}.
$$

???+ note "Epigraph Characterization Of Convex Functions"
    A function $f:\mathbf R\rightarrow\mathbf R\cup\{\pm\infty\}$ is convex iff $\operatorname{epi}f$ is a convex subset of $\mathbf R^2$.

??? note "Proof"
    If $f$ is convex, then for $(x_1,y_1),(x_2,y_2)\in\operatorname{epi}f$ and any $\alpha\in(0,1)$,
    
    $$
    \alpha y_1+(1-\alpha)y_2 \ge \alpha f(x_1)+(1-\alpha)f(x_2) \ge f(\alpha x_1+(1-\alpha) x_2).
    $$
    
    Hence $\alpha(x_1,y_1)+(1-\alpha)(x_2,y_2)\in\operatorname{epi}f$.
    
    Conversely, if $\operatorname{epi}f$ is convex, then for any $x_1<x_2$ and $\alpha\in(0,1)$,
    
    $$
    \alpha(x_1,f(x_1))+(1-\alpha)(x_2,f(x_2)) \in \operatorname{epi}f.
    $$
    
    This is equivalent to $\alpha f(x_1)+(1-\alpha)f(x_2)\ge f\left(\alpha x_1+(1-\alpha)x_2\right)$, which is convexity of $f$.

This viewpoint connects infimal convolution of convex functions with Minkowski sums of convex sets.

## Transformations Of Convex Functions

### Nonnegative Linear Combinations

If $f$ and $g$ are convex and $\alpha,\beta\ge0$, then $\alpha f+\beta g$ is convex, and

$$
\Delta(\alpha f+\beta g) = \alpha\Delta f + \beta\Delta g.
$$

When maintaining slopes, compute the combined slope segment by segment. If one function has a simple form, lazy tags often reduce the update cost. When maintaining breakpoints, the breakpoints of $f+g$ are obtained by merging the breakpoint lists.

### Infimal Convolution (Minkowski Sum)

For functions $f$ and $g$,

$$
h(x) = \inf_{y\in\mathbf R}f(y)+g(x-y)
$$

is called their **infimal convolution**[^inf-conv]. If both are convex, so is $h$.

![](../images/slope-trick/epigraph-convex-minkowski.svg)

??? example "Interpreting The Figure"
    To compute $h$, move the graph of $g$ along the graph of $f$ and take the lower envelope. Each slope segment of $h$ is a slope segment of either $f$ or $g$, reordered by slope. Geometrically, $\operatorname{epi}h$ is the [Minkowski sum](../../geometry/convex-hull.md#闵可夫斯基和) of $\operatorname{epi}f$ and $\operatorname{epi}g$.

??? note "Proof"
    For $x_1<x_2$ and $\alpha\in(0,1)$, choose near-optimal decompositions $x_i=y_i+z_i$ such that
    
    $$
    h(x_i) + \varepsilon > f(y_i) + g(z_i).
    $$
    
    Convexity of $f$ and $g$ gives
    
    $$
    \begin{aligned}
    \alpha h(x_1)+(1-\alpha)h(x_2) + \varepsilon 
    &> \alpha f(y_1) + (1-\alpha) f(y_2) + \alpha g(z_1) + (1-\alpha) g(z_2)\\
    &\ge f\left(\alpha y_1+(1-\alpha)y_2\right) + g\left(\alpha z_1+(1-\alpha)z_2\right)\\
    &\ge h(\alpha x_1+(1-\alpha)x_2).
    \end{aligned}
    $$
    
    Since $\varepsilon>0$ is arbitrary,
    
    $$
    \alpha h(x_1)+(1-\alpha)h(x_2) \ge h(\alpha x_1+(1-\alpha)x_2).
    $$
    
    This proves convexity. The epigraph relation is
    
    $$
    \operatorname{epi} f + \operatorname{epi} g\subseteq \operatorname{epi}h \subseteq \operatorname{cl}(\operatorname{epi} f + \operatorname{epi} g).
    $$
    
    For any $(x,y)\in\operatorname{epi} f + \operatorname{epi} g$, there are $(x_1,y_1)\in\operatorname{epi} f$ and $(x_2,y_2)\in\operatorname{epi} g$ such that $x=x_1+x_2$ and
    
    $$
    y = y_1+y_2 \ge f(x_1)+g(x_2) \ge h(x_1+x_2)=h(x).
    $$
    
    Hence $(x,y)\in\operatorname{epi}h$. Conversely, if $(x,y)\in\operatorname{epi}h$, then $y\ge h(x)$. For any $\varepsilon>0$, there exist $x_1+x_2=x$ such that
    
    $$
    y + \varepsilon > f(x_1) + g(x_2).
    $$
    
    Taking $\varepsilon\to0$ gives the inclusion into the closure. Thus equality holds when the sum is closed, as in the usual piecewise-linear cases.

If one function has few slope segments, insert them into the larger structure directly; otherwise use [DSU on tree](../../graph/dsu-on-tree.md), mergeable heaps, or another problem-specific merging strategy.

### Min And Max Operations

The maximum of two convex functions is convex, but the minimum of two convex functions need not be convex.

Many useful minimum operations can be rewritten as infimal convolution.

???+ example "Examples"
    -   $f(x)=\min_{y\in [x+a,x+b]}g(y)$ is convex because
    
        $$
        f(x) = \min_{y\in\mathbf R}g(y) + 0_{[-b,-a]}(x-y).
        $$
    -   $f(x)=\min\{g(x-a_i)+b_i\}$ is convex on $\mathbf Z$ if $g$ is convex on $\mathbf Z$ and $h:a_i\mapsto b_i$ is convex on the finite set $\{a_i\}$, because the interpolated function can be written as the infimal convolution
    
        $$
        \tilde f(x) = \min_{y\in\mathbf R}\tilde h(y)+\tilde g(x-y).
        $$
    
        Therefore the original function $f(x)$ is also convex.

???+ example "Counterexample"
    If $g(x)$ is convex, $f(x)=\min\{g(x-1)+kx,g(x)\}$ is not necessarily convex.

Some DP transitions are minima of convex functions that cannot easily be expressed as infimal convolutions, but convexity still holds. In practice, tables and pattern-spotting are often used to discover the correct slope transition.

## Maintaining Breakpoints

This type of problem often appears when minimizing sums of absolute values. Because slopes change by small integer amounts, maintaining breakpoints is convenient.

Maintaining breakpoints means storing the points where the slope of a piecewise-linear function changes. If the breakpoint multiset is $\xi_{-s}\le\cdots\le\xi_{-1}\le\xi_{1}\le\cdots\le\xi_{t}$, then the slope is $0$ on $[\xi_{-1},\xi_1]$, decreases by one when passing a breakpoint to the left, and increases by one when passing a breakpoint to the right. Formally,

$$
f(x) = f(\xi_1) + \sum_{i=-s}^{-1}\max\{\xi_i-x,0\} + \sum_{i=1}^{\ell}\max\{x-\xi_i,0\}.
$$

The minimum value is $f(\xi_{-1})=f(\xi_1)$ and is attained anywhere in $[\xi_{-1},\xi_1]$.

![](../images/slope-trick/epigraph-convex-kinks.svg)

### Example: Minimum-Cost Increasing Sequence

???+ example "[[BalticOI 2004] Sequence](https://www.luogu.com.cn/problem/P4331)"
    Given a sequence $\{a_i\}$ of length $n$, find a strictly increasing sequence $\{b_i\}$ minimizing $\sum_i|a_i-b_i|$, and output the minimum value and any optimal sequence.

??? note "Solution"
    Strictly increasing $\{b_i\}$ is equivalent to nondecreasing $b'_i=b_i-i$. Let $a'_i=a_i-i$. Define $f_i(x)$ as the minimum cost after choosing the first $i$ values of $b'$ with $b'_i\le x$:
    
    $$
    f_i(x) = \min\sum_{j=1}^i|a'_j-b'_j|\text{ s.t. }b'_1\le b'_2\le\cdots\le b'_i\le x.
    $$
    
    The transition is
    
    $$
    f_i(x) = \min_{y\le x}f_{i-1}(y)+|a'_i-y|.
    $$
    
    Add two breakpoints at $a'_i$, then delete all positive-slope breakpoints. Since after every step there are no positive-slope breakpoints, a max-heap of breakpoints suffices: insert $a'_i$ twice and pop the heap top.
    
    The minimum value must also be maintained. If the heap top before an operation is $\xi_{-1}$, the new minimum is the function value at the heap top before it is popped, namely
    
    $$
    f_{i-1}(\max\{a'_i,\xi_{-1}\})+|\max\{a'_i,\xi_{-1}\}-a'_i|=f_{i-1}(\xi_{-1})+\max\{0,\xi_{-1}-a'_i\}.
    $$
    
    Thus add $\max\{0,\xi_{-1}-a'_i\}$ to the answer each step. To reconstruct a solution, record the current minimizer and go backward, taking prefix minima.
    
    The complexity is $O(n\log n)$.
    
    ```cpp
    --8<-- "docs/dp/code/opt/slope-trick/sequence.cpp"
    ```

Template problems:

-   [Codeforces 713 C. Sonya and Problem Without a Legend](https://codeforces.com/problemset/problem/713/C)
-   [Luogu P2893 [USACO08FEB] Making the Grade G](https://www.luogu.com.cn/problem/P2893)
-   [Luogu P4331 [BalticOI 2004] Sequence](https://www.luogu.com.cn/problem/P4331)
-   [Luogu P4597 Sequence](https://www.luogu.com.cn/problem/P4597)
-   [AtCoder Dwango Programming Contest V Prelims E - Fireworks](https://atcoder.jp/contests/dwango2016-prelims/tasks/dwango2016qual_e)

### Example: Transitions With Constraints

???+ example "[[NOISG 2018 Finals] Safety](https://www.luogu.com.cn/problem/P11598)"
    Given a sequence $\{a_i\}$, find a sequence $\{b_i\}$ satisfying $|b_i-b_{i-1}|\le h$ for all $1<i\le n$ and minimizing $\sum_i|a_i-b_i|$.

??? note "Solution"
    Let $f_i(x)$ be the minimum cost when $b_i=x$:
    
    $$
    f_i(x) = \min\sum_{j=1}^i|a_j-b_j|\text{ s.t. }|b_{j-1}-b_j|\le h,\forall 1<j\le i,~b_i=x.
    $$
    
    Then
    
    $$
    f_i(x) = |a_i-x| + \min_{|y-x|\le h} f_{i-1}(y). 
    $$
    
    The first operation is infimal convolution with $0_{[-h,h]}$, which shifts all negative-slope breakpoints left by $h$ and all positive-slope breakpoints right by $h$. Then add two breakpoints at $a_i$. Use two heaps, a max-heap and a min-heap, to maintain negative and positive breakpoints, with lazy offsets. If the heap tops cross, swap them and add their distance to the minimum value.
    
    Specifically, if $\xi_{-1}>\xi_1$, then swapping the heap tops changes the local expression from
    
    $$
    \max\{0,x-\xi_{-1}\}+\max\{0,x-\xi_1\}
    $$
    
    to
    
    $$
    \max\{0,x-\xi_{1}\}+\max\{0,x-\xi_{-1}\}.
    $$
    
    The shape is unchanged, only shifted downward by $|\xi_{-1}-\xi_1|$, so add this distance to the minimum value to keep the function unchanged. Each step swaps at most once, so the complexity is $O(n\log n)$.
    
    ```cpp
    --8<-- "docs/dp/code/opt/slope-trick/safety.cpp"
    ```

Template problems:

-   [Luogu P4272 [CTSC2009] Sequence Transformation](https://www.luogu.com.cn/problem/P4272)
-   [Luogu P11598 [NOISG 2018 Finals] Safety](https://www.luogu.com.cn/problem/P11598)
-   [AtCoder Beginner Contest 217 H - Snuketoon](https://atcoder.jp/contests/abc217/tasks/abc217_h)
-   [AtCoder Regular Contest 070 E - NarrowRectangles](https://atcoder.jp/contests/arc070/tasks/arc070_c)
-   [AtCoder Regular Contest 123 D - Inc, Dec - Decomposition](https://atcoder.jp/contests/arc123/tasks/arc123_d)

## Maintaining Slopes

In some problems, maintaining slopes directly is more convenient. Such problems are often also solvable by undoable greedy methods or by simulating min-cost flow. In a min-cost-flow model, the minimum cost is often a convex function of the flow value, which provides the basis for Slope Trick.

### Example: Stock Trading

???+ example "[Codeforces 865 D. Buy Low Sell High](https://codeforces.com/problemset/problem/865/D)"
    Given stock prices $\{p_i\}$ for $n$ days, initially holding no stock, each day you may buy one share, sell one share, or do nothing. Find the maximum profit after $n$ days.

??? note "Solution"
    Let $f_i(x)$ be the maximum profit after day $i$ while holding $x\ge0$ shares:
    
    $$
    f_i(x) = \max\{f_{i-1}(x-1)-p_i,f_{i-1}(x),f_{i-1}(x+1)+p_i\}.
    $$
    
    Start with $f_0(0)=0$ and $f_0(x)=-\infty$ for $x\ne0$; the answer is $f_n(0)$. The transition first performs supremal convolution with the piecewise-linear extension of
    
    $$
    h_i(x) = \begin{cases}
    p_i, & x=-1,\\
    0, & x=0,\\
    -p_i, & x=1
    \end{cases}
    $$
    
    Then the function is restricted back to $[0,+\infty)$. In slope terms, insert two unit segments of slope $-p_i$, then delete the largest finite-slope unit segment. A max-heap suffices: insert $-p_i$ twice and pop the top. Maintain $f_i(0)$ by adding the popped slope after the temporary shift. Complexity is $O(n\log n)$.
    
    ```cpp
    --8<-- "docs/dp/code/opt/slope-trick/stock.cpp"
    ```

Template problem:

-   [Codeforces 865 D. Buy Low Sell High](https://codeforces.com/problemset/problem/865/D)

### Example: Moving Soil And Stone

???+ example "[[USACO16OPEN] Landscaping P](https://www.luogu.com.cn/problem/P2748)"
    Given sequences $\{a_i\}$ and $\{b_i\}$, where garden $i$ currently has $a_i$ units of soil and needs exactly $b_i$, buying one unit costs $X$, discarding one unit costs $Y$, and moving one unit from garden $i$ to garden $j$ costs $Z|i-j|$. Find the minimum cost. Here $a_i,b_i\le10$.

??? note "Solution"
    Let $f_i(x)$ be the minimum cost after satisfying the first $i$ gardens with net surplus $x$ units carried to later gardens. If $x<0$, it represents a deficit. The transition is
    
    $$
    f_i(x) = \min_{y\in\mathbf R} f_{i-1}(y) + |y|Z + h((x-y)+(b_i-a_i)).
    $$
    
    where
    
    $$
    h(\delta) = \max\{0,\delta\}X + \max\{0,-\delta\}Y = \max\{\delta X,-\delta Y\}.
    $$
    
    The transition consists of adding $|x|Z$, taking infimal convolution with $h$, and shifting left by $b_i-a_i$. Since $a_i,b_i$ are small, maintain unit-length slope segments with two stacks around the origin and lazy tags. Clamp slopes below $-Y$ and above $X$, then move $b_i-a_i$ unit segments between stacks while updating the answer by the crossed slope. The complexity is $O(n\max\{a_i,b_i\})$.
    
    ```cpp
    --8<-- "docs/dp/code/opt/slope-trick/landscaping.cpp"
    ```

Template problems:

-   [Luogu P2748 [USACO16OPEN] Landscaping P](https://www.luogu.com.cn/problem/P2748)
-   [Kyoto University PC 2016 H - WAAAAAAAAAAAAALL](https://atcoder.jp/contests/kupc2016/tasks/kupc2016_h)
-   [JAG Practice Contest 2017 J - Farm Village](https://atcoder.jp/contests/jag2017autumn/tasks/jag2017autumn_j)

## Exercises

The following problems from programming contests can be solved with Slope Trick.

-   [Luogu P3642 [APIO2016] Fireworks](https://www.luogu.com.cn/problem/P3642)
-   [Luogu P9962 [THUPC 2024 Preliminary] A Tree](https://www.luogu.com.cn/problem/P9962)
-   [Luogu P11317 [RMI 2021] Paths](https://www.luogu.com.cn/problem/P11317)
-   [AtCoder Beginner Contest 383 G - Bar Cover](https://atcoder.jp/contests/abc383/tasks/abc383_g)
-   [Codeforces 280 D. k-Maximum Subsequence Sum](https://codeforces.com/problemset/problem/280/D)
-   [Codeforces 280 E. Sequence Transformation](https://codeforces.com/problemset/problem/280/E)
-   [Codeforces 802 O. April Fools' Problem (hard)](https://codeforces.com/contest/802/problem/O)
-   [Codeforces 1209 H. Moving Walkways](https://codeforces.com/contest/1209/problem/H)
-   [Codeforces 1229 F. Mateusz and Escape Room](https://codeforces.com/contest/1229/problem/F)
-   [Codeforces 1534 G. A New Beginning](https://codeforces.com/problemset/problem/1534/G)
-   [Codeforces 1787 H. Codeforces Scoreboard](https://codeforces.com/problemset/problem/1787/H)
-   [2019 Summer Petrozavodsk Camp H. Honorable Mention](https://codeforces.com/gym/102331/problem/H)
-   [2018 ACM-ICPC World Finals C. Conquer The World](https://codeforces.com/gym/102482/problem/C)
-   [300iq Contest 3 F. Farm of Monsters](https://codeforces.com/gym/102538/problem/F)

## References And Notes

-   [[Tutorial] Slope Trick - zscoder](https://codeforces.com/blog/entry/47821)
-   [Slope trick explained - Kuroni](https://codeforces.com/blog/entry/77298)
-   [Slope Trick - USACO Guide](https://usaco.guide/adv/slope-trick?lang=cpp)
-   [[Tutorial] Intuition on Slope Trick - maomao90](https://codeforces.com/blog/entry/103222)

[^convex-def]: Different textbooks may use different terminology for convex and concave functions.

[^inf-conv]: Also called min-convolution, inf-convolution, or $(\min,+)$ convolution.
