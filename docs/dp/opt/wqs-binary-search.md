## Introduction

This article introduces WQS binary search for optimizing dynamic programming problems. It is also known as weighted binary search, convex DP optimization, convex complete-monotonicity DP, the Lagrange multiplier method, and, outside China, the Aliens Trick. It was first systematically summarized by Wang Qinshi in "A Brief Analysis of a Class of Binary Search Methods".

WQS binary search is usually used for optimization problems with a cardinality constraint: solving the constrained problem directly is expensive, but the unconstrained version is much easier.

For example, suppose we need to choose $m$ items from $n$ items and optimize a complicated objective. If $f(i,j)$ denotes the optimum using $j$ items among the first $i$ items, the answer is $f(n,m)$ and the direct DP is often $O(nm)$. If the unconstrained problem is easy, add a fixed penalty $k$ for every chosen item and solve the unconstrained problem instead. As $k$ changes, the optimal number of chosen items changes monotonically, so binary search can find a penalty that corresponds to $m$ items. If the penalized optimum is $f_k(n)$, the original answer is $f(n,m)=f_k(n)+km$. If one penalized solve costs $O(T(n))$, the total complexity is $O(T(n)\log L)$.

This idea works when $f(n,m)$ is convex in $m$ for minimization problems, or concave for maximization problems. Otherwise, there may be no penalty for which the optimal cardinality is exactly $m$.

## Traditional Method

Let $X$ be a nonempty finite decision space, let $f:X\rightarrow\mathbf R$ be the objective, and let $g:X\rightarrow\mathbf R^d$ describe the constraint. The original problem is the value function

$$
\begin{aligned}
v(y)=\min_{x\in X}\;&f(x)\\
\text{subject to }&g(x)=y.
\end{aligned}
$$

For a cardinality constraint, $X$ may be the family of item subsets, $f(x)$ the value of a subset, and $g(x)$ its size.

???+ info "Convention"
    This article discusses minimization. Maximization is analogous after replacing convexity by concavity, or by negating the objective.

### Geometric Intuition

Most competitive-programming instances are combinatorial, so $X$ has little useful structure. Instead, consider the point set

$$
\mathcal D = \{(g(x),f(x))\in\mathbf R\times\mathbf R^d:x\in X\}.
$$

The traditional method mainly handles $d=1$.

![](../images/wqs-binary-search/wqs-f-g-space.svg)

The desired value $v(y)$ is the smallest vertical coordinate among points with horizontal coordinate $y$. A line of slope $\lambda$ supports the lower convex hull at such a point. Define

$$
h(\lambda) = \min_{x\in X}f(x)-\lambda g(x).
$$

If the supporting line passes through $(y,v(y))$, then

$$
v(y) = h(\lambda) + \lambda y.
$$

Thus the key questions are whether such a slope exists, and how to find it. Existence is equivalent to $(y,v(y))$ lying on the lower convex hull, i.e. to $v(y)$ being a [convex function](./slope-trick.md#convex-functions-on-discrete-sets). To find the slope, solve $h(\lambda)$, record $g(x_\lambda)$ for an optimal decision, compare it with $y$, and adjust $\lambda$.

The traditional workflow is:

1.  Choose an initial interval for $\lambda$.
2.  Choose a trial $\lambda$ in the current interval.
3.  Solve $h(\lambda)=\min_{x\in X}f(x)-\lambda g(x)$ and record $g(x_\lambda)$ for an optimum.
4.  If $g(x_\lambda)=y$, return $v(y)=h(\lambda)+\lambda y$.
5.  Otherwise shrink the interval according to whether $g(x_\lambda)$ is too large or too small.

### Handling Collinear Points

The basic workflow mishandles collinear points on the lower hull. If several optimal points share the same supporting slope $\lambda^*$, the solve for $h(\lambda^*)$ may return any of them. If it returns the wrong one, the binary search may discard the correct slope.

One fix is to break ties consistently, always taking the largest (or smallest) possible $g(x_\lambda)$, and change the stopping condition to searching for the smallest (or largest) $\lambda$ satisfying $g(x_\lambda)\ge y$ (or $\le y$). The final answer must be $h(\lambda)+\lambda y$, not $h(\lambda)+\lambda g(x_\lambda)$.

Another fix is real-valued binary search. Even when all true slopes are integers, searching over real numbers lets the interval approach the excluded integer slope from one side. Once the interval contains only one integer, that integer is the desired slope.

These techniques solve most contest problems, but they still require recording $g(x_\lambda)$ and do not generalize well to high-dimensional constraints. The dual method below removes this dependency.

## Dual Method

Assume that for every $\lambda\in\mathbf R^d$ we can efficiently compute

$$
h(\lambda) = \min_{x\in X}f(x)-\lambda\cdot g(x)
$$

and that the original value function $v(y)$ is convex in $y\in\mathbf R^d$[^high-d-convex]. Then

$$
v^\star(y) = \sup_{\lambda\in\mathbf R^d} h(\lambda)+\lambda\cdot y,
$$

The dual objective is concave in $\lambda$, so it is unimodal and can be optimized by [ternary search](../../basic/binary.md#三分法), [golden-section search](../../basic/binary.md#优化黄金分割法), or nested one-dimensional searches. The complexity remains $O(T(n)\log^d L)$.

For $d=1$ with integer parameters, the range of $g(x_\lambda)$ can be recovered from $h$ alone:

$$
[h(\lambda-1)-h(\lambda),h(\lambda)-h(\lambda+1)].
$$

This provides another way to handle collinearity without recording tie-broken decisions.

### Lagrange Duality

Introduce a Lagrange multiplier $\lambda\in\mathbf R^d$ and the Lagrangian

$$
L(x,\lambda,y) = f(x) - \lambda\cdot g(x)+\lambda\cdot y.
$$

Because any nonzero component of $g(x)-y$ can be amplified by $\lambda$,

$$
\sup_{\lambda\in\mathbf R^d}L(x,\lambda,y)
= \begin{cases}
f(x),&g(x)=y,\\
+\infty,&\text{otherwise}.
\end{cases}
$$

Thus

$$
\begin{aligned}
v(y) &= \min_{x\in X}\sup_{\lambda\in\mathbf R^d}L(x,\lambda,y).
\end{aligned}
$$

and exchanging the two optimizations gives the dual problem

$$
\begin{aligned}
v^\star(y)&=\sup_{\lambda\in\mathbf R^d}\min_{x\in X}L(x,\lambda,y)\\
&=\sup_{\lambda\in\mathbf R^d}h(\lambda)+\lambda\cdot y.
\end{aligned}
$$

Strong duality holds under convexity of $v(y)$.

### Convex Conjugates

???+ abstract "Convex Conjugate"
    For $f:\mathbf R^d\rightarrow\mathbf R\cup\{\pm\infty\}$, the **convex conjugate**, or **Legendre-Fenchel transform**, is
    
    $$
    f^*(x^*) = \sup_{x\in\mathbf R^d}x^*\cdot x - f(x).
    $$

Since it is a supremum of linear functions, $f^*$ is convex.

???+ info "Slope Vector And Intercept Of A Hyperplane"
    Hyperplanes are written as
    
    $$
    y = k\cdot x + b.
    $$
    
    We call $k$ the slope vector and $b$ the intercept. In standard form this is $k\cdot x-y=-b$, whose normal vector is $(k,-1)$.
    
    $$
    k\cdot x - y = -b.
    $$

Geometrically, $f^*(x^*)$ records the intercept of the supporting hyperplane of slope vector $x^*$ to the epigraph

$$
\operatorname{epi}f = \{(x,y)\in\mathbf R^d\times\mathbf R:f(x)\le y\}
$$

Minimizing $f(x)-\lambda\cdot g(x)$ over $X$ is equivalent to minimizing $v(y)-\lambda\cdot y$ over $y\in g(X)$:

$$
\begin{aligned}
\min_x f(x)-\lambda\cdot g(x) &= \min_{y\in g(X)}\left(\min_{x\in X:g(x)=y} f(x) - \lambda\cdot g(x)\right)\\
&= \min_{y\in g(X)}\left(\min_{x\in X:g(x)=y} f(x)\right) - \lambda\cdot y \\
&= \min_{y\in g(X)}v(y) - \lambda\cdot y.
\end{aligned}
$$

Therefore

$$
h(\lambda) = \min_{y\in g(X)}v(y) - \lambda\cdot y = -v^*(\lambda).
$$

so $h$ is concave, and

$$
v^\star(y) = \sup_{\lambda\in\mathbf R^d}\lambda\cdot y-v^*(\lambda) = v^{**}(y).
$$

The dual value is the biconjugate of the original value function.

???+ note "Theorem (Fenchel-Moreau)"
    For $f:\mathbf R^d\rightarrow\mathbf R\cup\{\pm\infty\}$, $f^{**}=f$ iff one of the following holds:
    
    1.  $f$ is a proper convex function and [lower semicontinuous](https://en.wikipedia.org/wiki/Semi-continuity);
    2.  $f\equiv+\infty$; or
    3.  $f\equiv-\infty$.

??? note "Proof"
    Weak duality, $f\ge f^{**}$, follows directly from the definition of the conjugate:
    
    $$
    f^*(x^*) \ge x^*\cdot x-f(x).
    $$
    
    Thus, for all $x,x^*\in\mathbf R^d$,
    
    $$
    f(x) \ge x^*\cdot x-f^*(x^*).
    $$
    
    For the reverse inequality, separate the point $(x_0,f^{**}(x_0))$ from the closed convex epigraph of $f$ using the hyperplane separation theorem. This gives
    
    $$
    \lambda\cdot x-ty <\alpha <\lambda\cdot x_0 - tf^{**}(x_0)
    $$
    
    for all $x\in\operatorname{dom}f$ and $y\ge f(x)$. Since $y$ can be arbitrarily large, $t\ge0$. If $t>0$, normalize by setting $\lambda'=t^{-1}\lambda$ and $\alpha'=t^{-1}\alpha$:
    
    $$
    \lambda'\cdot x-y < \alpha'< \lambda'\cdot x_0-f^{**}(x_0).
    $$
    
    Setting $y=f(x)$ gives
    
    $$
    \alpha' > \lambda'\cdot x - f(x).
    $$
    
    Taking the supremum over $x$ gives
    
    $$
    \alpha' \ge \sup_{x\in\mathbf R^d}\lambda'\cdot x - f(x) = f^*(\lambda').
    $$
    
    Therefore,
    
    $$
    f^{**}(x_0) < \lambda'\cdot x_0-f^*(\lambda') \le \sup_{x^*\in\mathbf R^d}x^*\cdot x_0-f^*(x^*) = f^{**}(x_0).
    $$
    
    a contradiction. The case $t=0$ is reduced to the same argument by a small perturbation. Choose $\lambda_0\in\operatorname{dom}f^*$; then for any $x\in\operatorname{dom}f$ and $y\ge f(x)$,
    
    $$
    \lambda_0\cdot x-y\le f^*(\lambda_0).
    $$
    
    Hence, for any $\varepsilon>0$,
    
    $$
    (\lambda+\varepsilon\lambda_0)\cdot x - \varepsilon y<\alpha+\varepsilon f^*(\lambda_0).
    $$
    
    For sufficiently small $\varepsilon>0$,
    
    $$
    \alpha+\varepsilon f^*(\lambda_0) < (\lambda+\varepsilon\lambda_0)\cdot x_0 - \varepsilon f^{**}(x_0).
    $$
    
    Taking $\lambda'=\lambda+\varepsilon\lambda_0$, $t'=\varepsilon$, and $\alpha'=\alpha+\varepsilon f^*(\lambda_0)$ gives
    
    $$
    \lambda'\cdot x-t'y <\alpha' <\lambda'\cdot x_0 - t'f^{**}(x_0).
    $$
    
    This returns to the previous case and again gives a contradiction.

Thus strong duality holds exactly when the value function is convex in the relevant sense[^other-conditions].

### Subgradients

For nonsmooth convex functions, derivatives are replaced by subgradients.

???+ abstract "Subgradient"
    For a convex function $f:\mathbf R^d\rightarrow\mathbf R\cup\{\pm\infty\}$ and $x_0\in\operatorname{dom}f$, a vector $x^*\in\mathbf R^d$ is a **subgradient** at $x_0$ if for every $x\in\mathbf R^d$,
    
$$
f(x) \ge f(x_0)+x^*\cdot(x-x_0),
$$
    
    The set of all subgradients at $x_0$ is the **subdifferential**, denoted $\partial f(x_0)$.

In one dimension,

$$
\partial f(x_0) = [\partial_-f(x_0),\partial_+f(x_0)],
$$

For an integer-domain convex function extended by interpolation,

$$
\partial\tilde f(k) = [f(k)-f(k-1),f(k+1)-f(k)]. 
$$

???+ note "Theorem (Convex Conjugate And Subgradient)"
    For a proper convex function $f:\mathbf R^d\rightarrow\mathbf R$ and any $x,x^*\in\mathbf R^d$,
    
    $$
    x^*\in\partial f(x) \iff x^*\cdot x = f(x) + f^*(x^*).
    $$
    
    If $f$ is also lower semicontinuous, these are equivalent to $x\in\partial f^*(x^*)$.

??? note "Proof"
    The subgradient definition is equivalent to
    
    $$
    f(x') \ge f(x) + x^*\cdot(x'-x),~\forall x'\in\mathbf R^d.
    $$
    
    This is equivalent to
    
    $$
    x^*\cdot x - f(x) \ge x^*\cdot x'-f(x'),~\forall x'\in\mathbf R^d.
    $$
    
    And therefore to
    
    $$
    x^*\cdot x - f(x) \ge \sup_{x'\in\mathbf R^d}x^*\cdot x'-f(x') = f^*(x^*).
    $$
    
    while the reverse inequality always holds by definition:
    
    $$
    x^*\cdot x - f(x) \le f^*(x^*).
    $$
    
    Hence equality is necessary and sufficient:
    
    $$
    x^*\cdot x = f(x) + f^*(x^*).
    $$
    
    If $f$ is lower semicontinuous, Fenchel-Moreau gives $f^{**}=f$, so the same condition is
    
    $$
    x^*\cdot x = f^*(x^*) + f^{**}(x).
    $$
    
    Applying the first part again proves the final equivalence.

???+ note "Corollary"
    For lower-semicontinuous proper convex $f$,
    
    $$
    \begin{aligned}
    \partial f(x) &= \arg\max_{y^*\in\mathbf R^d} x\cdot y^* - f^*(y^*),\\
    \partial f^*(x^*) &= \arg\max_{y\in\mathbf R^d} x^*\cdot y - f(y).
    \end{aligned}
    $$

??? note "Proof"
    For the second equality, by definition of the convex conjugate,
    
    $$
    f^*(x^*) = \sup_{y\in\mathbf R^d} x^*\cdot y - f(y),
    $$
    
    so
    
    $$
    x \in \arg\max_{y\in\mathbf R^d} x^*\cdot y - f(y)
    $$
    
    iff $f^*(x^*)=x^*\cdot x-f(x)$, which is equivalent to $x\in\partial f^*(x^*)$.

In our setting, when solving

$$
h(\lambda) = \min_{x\in X}f(x)-\lambda\cdot g(x) = \min_{y\in g(X)}v(y) - \lambda\cdot y
$$

the possible values of $g(x)$ among optimal decisions are exactly $\partial(-h(\lambda))$. For $d=1$ and integer parameters, this is

$$
[h(\lambda-1)-h(\lambda),h(\lambda)-h(\lambda+1)].
$$

## Proving Convexity

Convexity of the value function is the prerequisite for WQS binary search. In contests it is often guessed from tables or intuition, but rigorous proofs usually use one of four patterns:

-   reduce the problem to a parametric convex optimization problem, such as [linear programming](../../math/linear-programming.md) or [min-cost flow](../../graph/flow/min-cost.md);
-   prove convexity inductively from the DP transition, often using [convexity-preserving transformations](./slope-trick.md#transformations-of-convex-functions);
-   for interval partitioning problems, prove the cost satisfies the [quadrangle inequality](./quadrangle.md);
-   use an exchange argument tailored to the problem.

We illustrate them with the following classic problem.

???+ example "Tree Planting Problem"
    There are $n$ pits and $m$ trees to plant. No two adjacent pits may both contain trees. Given rewards $\{a_i\}$, find the maximum total reward from planting exactly $m$ trees. Equivalently, find the maximum-weight independent set of size $m$ on a path.

### Reduction To Parametric Convex Optimization

For a parametric convex optimization problem

$$
v(y)=\inf_{x\in\mathcal D(y)} f(x,y).
$$

if $f(x,y)$ is convex in $(x,y)$ and the graph $\{(x,y):x\in\mathcal D(y)\}$ is convex, then $v(y)$ is convex whenever it is bounded below. The proof checks that for any $y_1,y_2\in\mathbf R^d$ and $\alpha\in(0,1)$,

$$
v(\alpha y_1+(1-\alpha)y_2) \le \alpha v(y_1) + (1-\alpha) v(y_2).
$$

For nearly optimal $x_i\in\mathcal D(y_i)$, convexity of the graph gives

$$
\alpha x_1+(1-\alpha)x_2 \in \mathcal D(\alpha y_1+(1-\alpha)y_2).
$$

Then convexity of the objective gives

$$
\begin{aligned}
    v(\alpha y_1+(1-\alpha)y_2)
    &\le f(\alpha x_1+(1-\alpha)x_2,\alpha y_1+(1-\alpha)y_2) \\
    &\le \alpha f(x_1,y_1) + (1-\alpha)f(x_2,y_2) \\
    &< \alpha v(y_1) + (1-\alpha) v(y_2) + \varepsilon.
    \end{aligned}
$$

Letting $\varepsilon\rightarrow0$ yields

$$
v(\alpha y_1+(1-\alpha)y_2) \le \alpha v(y_1) + (1-\alpha) v(y_2).
$$

Linear programs are the most common contest example:

???+ note "Corollary"
    For
    
    $$
    v(y_1,y_2)=\min_{x\in\mathbf R^n} c\cdot x \text{ subject to }A_1x\le y_1,A_2x=y_2,x\ge 0.
    $$
    
    the value function is convex in $(y_1,y_2)$.

Many graph problems can be formulated as LPs, including max flow/min cut, min-cost flow, shortest paths without negative cycles, bipartite matching and vertex cover, general matching, and minimum spanning tree[^mst].

???+ warning "Integer Constraints"
    Graph models often hide integrality constraints. If relaxing an integer linear program to an LP changes the optimum, convexity of the LP value function does not prove convexity of the original combinatorial problem.

???+ note "Corollary"
    In a [minimum-cost flow model](../../graph/flow/min-cost.md), the minimum cost $v(m)$ is a convex function of the flow value $m$.

??? note "Proof"
    Write min-cost flow as the LP
    
    $$
    \begin{aligned}
    v(m)=\min_{\{f_{ij}\}}\;&\sum_{(i,j)\in E}w_{ij}f_{ij}\\
    \text{subject to }&\sum_{(j,i)\in E}f_{ji} - \sum_{(i,j)\in E}f_{ij} = 
    \begin{cases}
    -m, & i=s,\\
    m,  & i=t,\\
    0,  & \text{otherwise},
    \end{cases}
    ~\forall i\in V,\\
    &0\le f_{ij}\le c_{ij},~\forall (i,j)\in E.
    \end{aligned}
    $$
    
    The flow value $m$ appears as a parameter in linear equality constraints, so the value is convex in $m$.

??? example "Convexity Proof 1"
    The tree-planting problem can be modeled as maximum-cost flow: connect a source to a root with capacity $m$, connect the root to odd positions, connect even positions to the sink, and add edges representing planting choices with reward $a_i$. The total flow $m$ appears in a capacity constraint, so the maximum reward is concave in $m$.

### Using The DP Transition

The DP recurrence itself can sometimes prove convexity. For tree planting, let $f(i,j)$ be the maximum reward from planting $j$ trees among the first $i$ pits:

$$
f(i,j) = \max\{f(i-1,j),f(i-2,j-1)+a_i\}.
$$

??? example "Convexity Proof 2"
    Inductively prove that $f(i,j)-f(i-2,j-1)$ is nonincreasing in $j$, and $f(i,j)-f(i-1,j)$ is nondecreasing in $j$. These two facts imply that
    
    $$
    f(i-1,j) - f(i-2,j-1) = (f(i,j)-f(i-2,j-1)) - (f(i,j)-f(i-1,j))
    $$
    
    is nonincreasing in $j$. Hence
    
    $$
    f(i,j) - f(i-2,j-1) = \max\{f(i-1,j) - f(i-2,j-1), a_i\}
    $$
    
    is nonincreasing in $j$, and
    
    $$
    f(i,j) - f(i-1,j) = \max\{0,a_i-(f(i,j) - f(i-2,j-1))\}
    $$
    
    is nondecreasing in $j$. Therefore
    
    $$
    f(i,j) - f(i,j-1) = (f(i,j)-f(i-2,j-1)) - (f(i,j-1) - f(i-1,j-1)) - (f(i-1,j-1) - f(i-2,j-1))
    $$
    
    is nonincreasing in $j$, so $f(i,\cdot)$ is concave. Hence $v(m)=f(n,m)$ is concave. The same proof also shows that for each $i$ there is a threshold $p_i$ such that
    
    $$
    f(i,j) =
    \begin{cases}
    f(i-1,j), & j\le p_i,\\
    f(i-2,j-1) + a_i, & j> p_i.
    \end{cases}
    $$

### Quadrangle Inequality

[Interval partitioning](./quadrangle.md#interval-partitioning) is another common source of convex value functions. If the interval cost satisfies the quadrangle inequality, then the minimum cost with a fixed number of intervals is convex in the number of intervals. One direct test is the mixed second difference

$$
\begin{aligned}
\Delta_l \Delta_r w(l,r) &= \Delta_l(w(l,r+1)-w(l,r)) \\
&= w(l+1,r+1)-w(l+1,r)-w(l,r+1)+w(l,r).
\end{aligned}
$$

$w$ satisfies the quadrangle inequality iff this value is non-positive.

??? example "Convexity Proof 3"
    Add an arbitrary $a_0$ before the reward sequence. The tree-planting problem is equivalent to partitioning $\{a_0,a_1,\cdots,a_n\}$ into $m$ segments with segment reward
    
    $$
    w(l,r) = \max_{i\in[l+1,r]} a_i
    $$
    
    For maximization, prove the reversed quadrangle inequality:
    
    $$
    w(a,c)+w(b,d) \ge w(a,d)+w(b,c).
    $$
    
    Let
    
    $$
    A = \max_{i\in[a+1,b]} a_i,~ B = \max_{i\in[b+1,c]} a_i,~ C = \max_{i\in[c+1,d]}a_i,
    $$
    
    The needed inequality becomes
    
    $$
    \max\{A,B\} + \max\{B,C\} \ge \max\{A,B,C\} + B.
    $$
    
    which is immediate. With range maximum preprocessing, interval-partitioning algorithms apply.

### Exchange Argument

For combinatorial optimization, convexity can often be proved by exchanging parts of optimal solutions for parameters $m-1$ and $m+1$ to construct feasible solutions for $m$.

???+ warning "Increasing Marginal Cost Does Not Always Imply Convexity"
    Supermodularity is often used to formalize increasing marginal cost, but optimizing a supermodular objective under a cardinality constraint does not necessarily produce a convex value function. The reason is that one usually cannot construct a size-$m$ feasible solution with the desired value relation from size $m-1$ and $m+1$ optima.
    
    $$
    v(m) = \min_{A\subseteq X} f(A) \text{ subject to }|A|=m
    $$

??? example "Convexity Proof 4"
    Let optimal planting schemes for $m-1$ and $m+1$ trees be binary sequences $x^{(m-1)}$ and $x^{(m+1)}$. Define
    
    $$
    z_i = x_i^{(m+1)} - x_i^{(m-1)},~i=1,\cdots,n.
    $$
    
    In every maximal nonzero segment of $z$, the signs alternate, and the zeros on both sides correspond to pits unused in both schemes. At least two such segments have sum $+1$. Swapping choices within one such segment turns the two original schemes into two feasible schemes with exactly $m$ trees, without changing their total reward. Therefore
    
    $$
    v(m-1) + v(m+1) \le 2v(m),
    $$
    
    so $v(m)$ is concave.

## Examples

### Template Problems

???+ example "[Luogu P1484 Tree Planting](https://www.luogu.com.cn/problem/P1484)"
    There are $n$ pits and at most $m$ trees may be planted. Adjacent pits cannot both contain trees. Given rewards $\{a_i\}$, maximize the total reward.

??? note "Solution"
    This asks for $\tilde v(m)=\max_{k\le m}v(k)$ rather than exactly $m$. Since $v$ is concave, only the part with nonnegative slope matters, so the WQS slope range starts from $0$.
    
    After removing the cardinality constraint, compute maximum-weight independent set on a path with adjusted weights $a_i+k$:
    
    $$
    \begin{aligned}
    f(i,0) &= \max\{f(i-1,0),f(i-1,1)\},\\
    f(i,1) &= f(i-1,0) + a_i + k.
    \end{aligned}
    $$
    
    The single-solve complexity is $O(n)$.
    
    === "Traditional Method"
        ```cpp
        --8<-- "docs/dp/code/opt/wqs-binary-search/plant-tree-1.cpp"
        ```
    
    === "Dual Method"
        ```cpp
        --8<-- "docs/dp/code/opt/wqs-binary-search/plant-tree-2.cpp"
        ```

???+ example "[Luogu P2619 [National Training Team] Tree I](https://www.luogu.com.cn/problem/P2619)"
    Given a connected weighted undirected graph whose edges are black or white, find the minimum-weight spanning tree containing exactly $m$ white edges.

??? note "Solution"
    An exchange argument proves that the optimum $v(m)$ is convex. The key lemma is that for two spanning trees $S,T$ and any $e\in S\setminus T$, there exists $f\in T\setminus S$ such that both $S-e+f$ and $T-f+e$ are spanning trees[^edge-swap].
    
    Apply WQS binary search by subtracting $k$ from every white edge and computing an MST using [Kruskal's algorithm](../../graph/mst.md#kruskal-算法). Since only white edges shift together, sort white and black edges separately once, then merge them for each trial. The total complexity is $O(E\log E+E\alpha(V)\log L)$.
    
    === "Traditional Method"
        ```cpp
        --8<-- "docs/dp/code/opt/wqs-binary-search/black-white-mst-1.cpp"
        ```
    
    === "Dual Method"
        ```cpp
        --8<-- "docs/dp/code/opt/wqs-binary-search/black-white-mst-2.cpp"
        ```

### Interval Partitioning

???+ example "[Luogu P6246 [IOI 2000] Post Office, Enhanced Enhanced](https://www.luogu.com.cn/problem/P6246)"
    Given increasing village positions $\{a_i\}$ along a highway, build $m$ post offices to minimize the sum of distances from every village to its nearest post office.

??? note "Solution"
    This is a standard [interval partitioning problem](./quadrangle.md#interval-partitioning). Villages served by one post office are consecutive, and the best post office location for $[l,r]$ is the median. Thus
    
    $$
    w(l,r) = \sum_{i=l}^r|a_i-a_{\lfloor(l+r)/2\rfloor}|.
    $$
    
    Its mixed second difference is non-positive:
    
    $$
    \Delta_l\Delta_r w(l,r)
    = \Delta_l(a_{r+1} - a_{\lfloor(l+r+1)/2\rfloor})
    = a_{\lfloor(l+r+1)/2\rfloor}-a_{\lfloor(l+r+2)/2\rfloor} \le 0.
    $$
    
    Combine the binary-search queue with WQS binary search to solve it in $O(n\log n\log L)$.
    
    === "Traditional Method"
        ```cpp
        --8<-- "docs/dp/code/opt/wqs-binary-search/post-office-1.cpp"
        ```
    
    === "Dual Method"
        ```cpp
        --8<-- "docs/dp/code/opt/wqs-binary-search/post-office-2.cpp"
        ```

### Two-Dimensional Constraints

???+ example "[Codeforces 739 E. Gosha is hunting](https://codeforces.com/problemset/problem/739/E)"
    There are $n$ Pokemon. Probabilities $p_i$ and $q_i$ are the chances of catching Pokemon $i$ with a Pokeball and an Ultraball. You have $m_1$ Pokeballs and $m_2$ Ultraballs. Each Pokemon may receive either, both, or neither. Maximize the expected number caught.
    
    More generally, given positive sequences $\{A_i\},\{B_i\},\{C_i\}$ with $C_i\le A_i+B_i$, choose sets $X,Y$ with $|X|=m_1$, $|Y|=m_2$ to maximize
    
    $$
    \sum_{i\in X\setminus Y}A_i + \sum_{i\in Y\setminus X}B_i + \sum_{i\in X\cap Y}C_i.
    $$

??? note "Solution"
    The Pokemon problem is the special case
    
    $$
    A_i = p_i,~ B_i = q_i,~ C_i = p_i+q_i-p_iq_i
    $$
    
    A max-cost-flow model proves that the value function $v(m_1,m_2)$ is concave in $(m_1,m_2)$.
    
    After removing the cardinality constraints, give an extra reward $k_1$ for putting an index into $X$ and $k_2$ for putting it into $Y$. Decisions become independent:
    
    $$
    h(k_1,k_2) = \sum_{i=1}^n\max\{0,A_i+k_1,B_i+k_2,C_i+k_1+k_2\}.
    $$
    
    The answer is
    
    $$
    v(m_1,m_2) = \min_{k_1,k_2} h(k_1,k_2) - k_1m_1 - k_2m_2
    $$
    
    The complexity is $O(n\log^2L)$.
    
    ```cpp
    --8<-- "docs/dp/code/opt/wqs-binary-search/gosha-is-hunting.cpp"
    ```

### Broader Constraints

???+ example "[Codeforces 1661 F. Teleporters](https://codeforces.com/problemset/problem/1661/F)"
    There are $n$ segments with lengths $\{a_i\}$. You may cut them into integer-length pieces. Minimize the sum of squares of all piece lengths, and find the minimum number of cuts needed to make this sum at most $V$.

??? note "Solution"
    Let $f(a,m)$ be the minimum square sum after cutting a segment of length $a$ exactly $m$ times. The pieces should be as equal as possible:
    
    $$
    \begin{aligned}
    f(a,m) &= (a\bmod (m+1))\left\lceil\dfrac{a}{m+1}\right\rceil^2 + (m+1-(a\bmod (m+1)))\left\lfloor\dfrac{a}{m+1}\right\rfloor^2 \\
    &= (a\bmod (m+1))\left(\left\lfloor\dfrac{a}{m+1}\right\rfloor+1\right)^2 + (m+1-(a\bmod (m+1)))\left\lfloor\dfrac{a}{m+1}\right\rfloor^2.
    \end{aligned}
    $$
    
    Extending to real $m\ge0$, when $\lfloor a/(m+1)\rfloor=q$,
    
    $$
    \begin{aligned}
    f(a,m) &= (a-(m+1)q)(q+1)^2 + ((m+1)(q+1)-a)q^2 \\
    &= a(2q+1) - q(q+1)(m+1).
    \end{aligned}
    $$
    
    a line whose slope increases as $m$ grows. Hence $f(a,m)$ is convex in $m$.
    
    The minimum square sum after a total of $m$ cuts is
    
    $$
    v(m) = \min_{\{m_i\}}\sum_i f(a_i,m_i)\text{ subject to }\sum_i m_i=m,~m_i\in\mathbf N.
    $$
    
    an infimal convolution of convex functions. The task asks for the smallest $m$ with $v(m)\le V$. Two approaches are common.
    
    **Method 1**: binary-search the slope $k$ and use the range of optimal $m$ values to bound $v(m)$. Once $k$ is known, compute the smallest $m$ from
    
    $$
    v(m) = h(k) + km
    $$
    
    **Method 2**: rewrite the optimization so the dual value is the required answer:
    
    $$
    m(v) = \min_{\{m_i\}} \sum_i m_i \text{ subject to }\sum_i f(a_i,m_i) \le V.
    $$
    
    and solve its dual
    
    $$
    m(v) = \max_{k} \sum_i\min_{m_i}(m_i - \lambda f(a_i,m_i)) + \lambda V.
    $$
    
    Both approaches run in $O(n\log^2L)$.
    
    === "Method 1"
        The code is illustrative. To pass the original constraints, use 128-bit integers and set the initial binary-search interval to $[0,10^{60}]$.
        
        ```cpp
        --8<-- "docs/dp/code/opt/wqs-binary-search/teleporters-1.cpp"
        ```
    
    === "Method 2"
        The code is illustrative and cannot pass the original constraints because of floating-point precision.
        
        ```cpp
        --8<-- "docs/dp/code/opt/wqs-binary-search/teleporters-2.cpp"
        ```

## Exercises

Problems that can be solved with WQS binary search:

-   [Luogu P1484 Tree Planting](https://www.luogu.com.cn/problem/P1484)
-   [Luogu P1792 [National Training Team] Tree Planting](https://www.luogu.com.cn/problem/P1792)
-   [Luogu P2619 [National Training Team] Tree I](https://www.luogu.com.cn/problem/P2619)
-   [Luogu P3620 [APIO/CTSC2007] Data Backup](https://www.luogu.com.cn/problem/P3620)
-   [Luogu P4072 [SDOI2016] Journey](https://www.luogu.com.cn/problem/P4072)
-   [Luogu P4383 [Eight-Province Joint Contest 2018] Link-Cut Tree](https://www.luogu.com.cn/problem/P4383)
-   [Luogu P4983 Forgetfulness](https://www.luogu.com.cn/problem/P4983)
-   [Luogu P5308 [COCI 2018/2019 #4] Akvizna](https://www.luogu.com.cn/problem/P5308)
-   [Luogu P5633 Degree-Constrained Minimum Spanning Tree](https://www.luogu.com.cn/problem/P5633)
-   [Luogu P5896 [IOI 2016] aliens](https://www.luogu.com.cn/problem/P5896)
-   [Luogu P6246 [IOI 2000] Post Office, Enhanced Enhanced](https://www.luogu.com.cn/problem/P6246)
-   [AtCoder Beginner Contest 218 H - Red and Blue Lamps](https://atcoder.jp/contests/abc218/tasks/abc218_h)
-   [AtCoder Beginner Contest 305 Ex - Shojin](https://atcoder.jp/contests/abc305/tasks/abc305_h)
-   [AtCoder Regular Contest 164 E - Segment-Tree Optimization](https://atcoder.jp/contests/arc164/tasks/arc164_e)
-   [Codeforces 125 E. MST Company](https://codeforces.com/problemset/problem/125/E)
-   [Codeforces 321 E. Ciel and Gondolas](https://codeforces.com/problemset/problem/321/E)
-   [Codeforces 739 E. Gosha is hunting](https://codeforces.com/problemset/problem/739/E)
-   [Codeforces 802 O. April Fools' Problem (hard)](https://codeforces.com/contest/802/problem/O)
-   [Codeforces 958 E2. Guard Duty (medium)](https://codeforces.com/problemset/problem/958/E2)
-   [Codeforces 1279 F. New Year and Handle Change](https://codeforces.com/problemset/problem/1279/F)
-   [Codeforces 1661 F. Teleporters](https://codeforces.com/problemset/problem/1661/F)
-   [Codeforces 1799 F. Halve or Subtract](https://codeforces.com/problemset/problem/1799/F)
-   [2019 Summer Petrozavodsk Camp H. Honorable Mention](https://codeforces.com/gym/102331/problem/H)

## References And Notes

-   [Wang Qinshi, "A Brief Analysis of a Class of Binary Search Methods"](https://github.com/hzwer/shareOI/blob/master/%E5%9F%BA%E7%A1%80%E7%AE%97%E6%B3%95/%E6%B5%85%E6%9E%90%E4%B8%80%E7%B1%BB%E4%BA%8C%E5%88%86%E6%96%B9%E6%B3%95_%E7%8E%8B%E9%92%A6%E7%9F%B3.pdf)
-   [Theoretical grounds of lambda optimization by adamant - Codeforces blog](https://codeforces.com/blog/entry/98334)
-   [A Rigorous WQS Binary Search Method by YeahPotato - Luogu Blog](https://www.luogu.com.cn/article/vsffwrc3)
-   [Study Notes: Detailed WQS Binary Search and Common Misconceptions by ikrvxt - CSDN Blog](https://blog.csdn.net/Emm_Titan/article/details/124035796)
-   [Convex conjugate - Wikipedia](https://en.wikipedia.org/wiki/Convex_conjugate)
-   [Fenchel-Moreau theorem - Wikipedia](https://en.wikipedia.org/wiki/Fenchel%E2%80%93Moreau_theorem)
-   [Subderivative - Wikipedia](https://en.wikipedia.org/wiki/Subderivative)
-   [Boyd, Stephen P., and Lieven Vandenberghe. Convex optimization. Cambridge university press, 2004.](https://web.stanford.edu/~boyd/cvxbook/bv_cvxbook.pdf)
-   Papadimitriou, Christos H., and Kenneth Steiglitz. Combinatorial optimization: algorithms and complexity. Courier Corporation, 1998.
-   Conforti, Michele, Gerard Cornuejols, and Giacomo Zambelli. Integer programming. Springer International Publishing, 2014.
-   Schrijver, Alexander. Combinatorial optimization: polyhedra and efficiency. Vol. 24, no. 2. Berlin: Springer, 2003.

[^high-d-convex]: In real problems, $y$ may only take finitely many lattice points in $\mathbf R^d$. The actual condition needed is that $v(y)$ can be extended to a convex function $\tilde v:\mathbf R^d\rightarrow \mathbf R\cup\{\pm\infty\}$; that is, $v$ is **convex-extensible**. Geometrically, the points $\{(y,v(y))\}$ all lie on the lower hull of their convex hull.

[^other-conditions]: The theorem's conditions look stronger than convexity, but for competitive-programming settings, especially finite $X$, convexity is usually enough. The interpolated extension of a proper convex function on a finite discrete set is lower semicontinuous because the convex hull of finitely many points is closed.

[^mst]: The minimum spanning tree problem has two common LP formulations: the subtour-elimination formulation and the cut-based formulation. Only the former guarantees equivalence with the original problem.

[^edge-swap]: This lemma also holds for general [matroids](../../math/matroid.md). It is called the **symmetric base-exchange property**; see the related [Wikipedia page](https://en.wikipedia.org/wiki/Basis_of_a_matroid).

[^conv-int]: The convex hull of $f(a,m)$ on real $m$ and the convex hull of its restriction to integer points are not necessarily the same, because $f(a,m)$ may have extreme points at non-integer positions. Thus the real-domain function cannot be used directly as the optimization problem in this task.
