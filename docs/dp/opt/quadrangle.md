author: Marcythm, zyf0726, hsfzLZH1, MingqiHuang, Ir1d, greyqz, billchenchina, Chrogeek, StudyingFather, NFLSCode, c-forrest

Quadrangle-inequality optimization exploits monotonicity of the optimal decision in a DP transition. It is therefore also often called **decision-monotonicity optimization for DP**.

## Prerequisites

Consider the simplest setting, where we need to solve the following family of optimization problems:

$$
f(i) = \min_{1 \leq j \leq i} w(j,i) \qquad \left(1 \leq i \leq n\right) \tag{1}
$$

Assume here that the cost function $w(j,i)$ can be computed in $O(1)$ time.

???+ info "Convention"
    DP transitions can often be written as a family of optimization problems. In (1), the problem has parameter $i$, and both the objective function and the feasible set may depend on $i$. For brevity, the optimization problem with parameter $i$ is called **problem $i$**; a feasible value $j$ is called **decision $j$**; and the optimal objective value is called the **state $f(i)$**. Let $\operatorname{opt}(i)$ denote the smallest optimal decision for problem $i$.

In the general case, solving all these problems costs $O(n^2)$, because problem $i$ may have to inspect every possible decision $j$. If the optimal decisions are monotone, the decision space can be restricted and the total complexity improved.

-   **Decision monotonicity**: for any $i_1 < i_2$, $\operatorname{opt}(i_1) \leq \operatorname{opt}(i_2)$.

??? note "Remark"
    The set of optimal decisions for a problem need not be an interval. Decision monotonicity can be defined on optimal-decision sets: for sets $A$ and $B$, define $A \leq B$ iff for any $a\in A$ and $b\in B$, both $\min\{a,b\}\in A$ and $\max\{a,b\}\in B$ hold. This implies monotonicity of the smallest and largest optimal decisions, which is the definition used here. All results stated for the smallest optimal decision also apply to the largest optimal decision. When implementing, always consistently choose either the smallest or the largest optimal decision, because it is possible that $\mathop{\mathrm{optmax}}(i_1) > \mathop{\mathrm{optmin}}(i_2)$ for some $i_1<i_2$.
    
    Problems with the same smallest optimal decision form an interval. These intervals, viewed as a function of the smallest optimal decision, are strictly increasing: if $j_1=\operatorname{opt}(i_1)$, $j_2=\operatorname{opt}(i_2)$, and $j_1<j_2$, then $i_1<i_2$.

The most common way to prove decision monotonicity is the quadrangle inequality. In other contexts it is also called the Monge property for matrices $A_{j,i}$, or submodularity for functions of intervals $f([j,i])$.

-   **Quadrangle inequality**: if for any $a\leq b\leq c\leq d$,

    $$
    w(a,c)+w(b,d) \leq w(a,d)+w(b,c),
    $$

    then $w$ is said to satisfy the quadrangle inequality, often remembered as "crossing is no larger than containing". If equality always holds, $w$ satisfies the **quadrangle identity**.

Unless otherwise stated, assume $a\leq b\leq c\leq d$. The quadrangle inequality is a sufficient, but not necessary, condition for decision monotonicity.

???+ note "Theorem 1"
    If $w$ satisfies the quadrangle inequality, then problem (1) has decision monotonicity.

??? note "Proof"
    Suppose, for contradiction, that for some $c<d$ we have $a=\operatorname{opt}(d)<\operatorname{opt}(c)=b$. Then $a<b\leq c<d$. Optimality gives $w(a,d)\leq w(b,d)$ and $w(b,c)<w(a,c)$, so $w(a,d)-w(b,d)\leq 0<w(a,c)-w(b,c)$, contradicting the quadrangle inequality.

Equivalently, the quadrangle inequality says that the mixed second difference $\Delta_i\Delta_jw(j,i)$ is non-positive on its natural domain.

With decision monotonicity, many algorithms reduce the complexity to $O(n\log n)$. Which one to use depends on how $w(j,i)$ can be accessed. Unless stated otherwise, this article assumes **random access**: $w(j,i)$ can be queried or computed in $O(1)$. We also discuss two weaker access patterns:

-   **Moving access**: $w(j,i)$ can be updated from $w(j\pm 1,i)$ or $w(j,i\pm 1)$ in $O(1)$ time, similarly to [Mo's algorithm](../../misc/mo-algo.md).
-   **Dynamic computation**: computing $w(j,i)$ depends on $\{f(j'):j'<j\}$, so $f$ and $w$ must be computed in order.

These two properties are not mutually exclusive.

### Divide and Conquer {#divide-and-conquer}

To compute all states, it suffices to compute all optimal decisions. First compute $\operatorname{opt}(n/2)$. Then recursively compute decisions on the left and right halves: by monotonicity, the left half only needs decisions in $[1,\operatorname{opt}(n/2)]$, and the right half only needs decisions in $[\operatorname{opt}(n/2),n]$. Recording these search bounds gives $O(n\log n)$ total work: the recursion has $O(\log n)$ levels, and on each level each decision is tested only $O(1)$ times.

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/dp/code/opt/quadrangle/quadrangle-divide-conquer.cpp:core"
    ```

Besides the random-access case, this divide-and-conquer algorithm also works with moving access. Maintain a cursor $(j,i)$ and the current value $w(j,i)$, and move the cursor by brute force whenever a new value is requested. The complexity is still $O(n\log n)$. This is discussed further in [Simplified LARSCH Algorithm](#simplified-larsch-algorithm). However, divide and conquer cannot handle dynamic computation, because it needs the midpoint decision before the left half has been solved.

### Binary-Search Queue

For each decision $j$, the problems for which it is the smallest optimal decision form an interval. We can maintain, in a monotone queue, the interval of problems currently solved by each decision.

When processing a new decision $k$, the queue stores triples consisting of a candidate decision $j$ and the endpoints $l_j,r_j$ of the interval it currently solves. For any problem in $[l_j,r_j]$, $j$ is the smallest optimal decision among the decisions processed so far. The decisions in the queue need not be consecutive, but the still-unsolved problem range should be the disjoint union of the stored intervals.

???+ note "Corollary 1"
    Let $\operatorname{opt}_k(i)$ be the smallest optimal decision for problem $i$ when only decisions in $[1,k]$ are allowed. If $w$ satisfies the quadrangle inequality, then for any $i_1<i_2$, $\operatorname{opt}_k(i_1)\leq\operatorname{opt}_k(i_2)$.

??? note "Proof"
    Let $M$ be sufficiently large and define $w'(j,i)=w(j,i)+M[j>k]$, where $[\cdot]$ is the Iverson bracket. The new cost still satisfies the quadrangle inequality, and no decision $j>k$ can be the smallest optimum. Applying Theorem 1 to this auxiliary DP proves the claim.

The algorithm is as follows: [^cmp-min-opt]

-   Initially the queue is empty. As in a monotone queue, each new decision performs pop and push operations.
-   **Pop**: remove the previous problem $j-1$. If the front decision's right endpoint is exactly $j-1$, pop it; otherwise update its left endpoint to $j$.
-   **Push**: compare the new decision $j$ with the decision $j'$ at the back.
-   If $w(j,l_{j'})<w(j',l_{j'})$, pop $j'$ and continue.
-   If the queue becomes empty, push $(j,j,n)$.
-   If $j'$ is no worse than $j$ on $r_{j'}$, then push $(j,r_{j'}+1,n)$ when $r_{j'}<n$; otherwise $j$ is never useful.
-   Otherwise, binary-search the smallest $i\in[l_{j'},r_{j'}]$ such that $w(j,i)<w(j',i)$, change $j'$'s right endpoint to $i-1$, and push $(j,i,n)$.
-   After processing decision $j$, the front decision is the smallest optimal decision for problem $j$.

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/dp/code/opt/quadrangle/quadrangle-monotone-queue.cpp:core"
    ```

Each decision is pushed and popped at most once. Popping is $O(1)$, and pushing may require a binary search, so the total complexity is $O(n\log n)$.

Because this algorithm processes problems and decisions in order, it supports dynamic computation. Its binary search requires random access to $w(j,i)$, so it does not support moving-access-only costs.

???+ example "Example 1: [POI2011 Lightning Conductor](https://loj.ac/problem/2157)"
    Given a sequence $a_1,a_2,\cdots,a_n$, for every $1\leq i\leq n$ find the smallest non-negative integer $f_i$ satisfying
    
    $$
    \forall j\in\left[1,n\right]:a_j \leq a_i + f_i - \sqrt{|i-j|}.
    $$

??? note "Idea"
    Rearranging gives $f_i=\max_j\{a_j+\sqrt{|i-j|}-a_i\}$. Consider first $j\leq i$; the other side is analogous:
    
    $$
    f_i = -\min_{j\le i}\{-a_j-\sqrt{i-j}+a_i\}.
    $$
    
    Since $-\sqrt{x}$ is convex, $w(l,r)=-a_l-\sqrt{r-l}+a_r$ satisfies the quadrangle inequality, so the algorithms above solve the problem in $O(n\log n)$.

??? note "Implementation"
    ```cpp
    --8<-- "docs/dp/code/opt/quadrangle/quadrangle_1.cpp"
    ```

### Simplified LARSCH Algorithm

The previous two algorithms cannot handle the case where $w(j,i)$ is both dynamically computed and available only by moving access. This section presents a simplified version of the LARSCH algorithm by Larmore and Schieber[^larsch]. The original algorithm solves decision-monotone DP in $O(n)$ time but is considerably harder to implement.

Again use a divide-and-conquer process. When solving problems in $(l,r]$, assume the following are already known:

-   for all $i\in[1,l]$, the smallest optimal decision $\operatorname{opt}(i)$ and the optimal value; and
-   considering only decisions in $[1,l]$, the smallest optimal decision $\operatorname{opt}_l(r)$ and value for problem $r$.

Let $\textit{mid}$ be the midpoint of $(l,r]$. The recursion is:

1.  Scan decisions $i\in[\operatorname{opt}(l),\operatorname{opt}_l(r)]$ to update problem $\textit{mid}$.
2.  Recursively solve $(l,\textit{mid}]$.
3.  Scan decisions $i\in(l,\textit{mid}]$ to update problem $r$.
4.  Recursively solve $(\textit{mid},r]$.

Before the initial recursion on $[1,n]$, update problems $1$ and $n$ using decision $j=1$. Stop when $l=r$.

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/dp/code/opt/quadrangle/quadrangle-simplified-larsch.cpp:core"
    ```

Correctness follows from Corollary 1. After step 1, $\operatorname{opt}_l(\textit{mid})$ is known, so the prerequisites for the left recursion hold. After the left recursion, all optimal decisions up to $\textit{mid}$ are known; step 3 then gives $\operatorname{opt}_{\textit{mid}}(r)$, so the prerequisites for the right recursion hold.

The complexity is still $O(n\log n)$. The recursion depth is $O(\log n)$, and within one level the scanned decision intervals overlap only $O(1)$ times because $\operatorname{opt}(l)\leq\operatorname{opt}_l(r)\leq\operatorname{opt}(r)$.

For moving access, maintain cursors for steps 1 and 3. Moving the cursors by brute force over the recursion tree costs $O(n\log n)$ in total.

??? note "Complexity Proof for Non-Random Access"
    It suffices to bound cursor movement. Let cursors $A$ and $B$ correspond to steps 1 and 3. Before solving $(l,r]$, maintain $A$ at $(\operatorname{opt}(l),l)$ and $B$ at $(l,l)$; afterward, maintain $A$ at $(\operatorname{opt}(r),r)$ and $B$ at $(r,r)$.
    
    In step 1, cursor $A$ may move along
    
    $$
    (\operatorname{opt}(l),l)\to(\operatorname{opt}(l),\textit{mid})\to(\operatorname{opt}_l(r),\textit{mid})\to(\operatorname{opt}(l),\textit{mid})\to(\operatorname{opt}(l),l)
    $$
    
    and in step 3 cursor $B$ may move along
    
    $$
    (\textit{mid},\textit{mid}) \to (l,\textit{mid}) \to (l, r) \to (\textit{mid},r) \to (\textit{mid},\textit{mid})
    $$
    
    These routes are sufficient for all required queries and overestimate the actual movement. Step 1 costs
    
    $$
    2(\operatorname{opt}_l(r) - \operatorname{opt}(l)) + 2(\textit{mid} - l)
    $$
    
    moves, and step 3 costs
    
    $$
    2(\textit{mid}-l)+2(r-\textit{mid}) = 2(r-l)
    $$
    
    moves. Summing over each recursion level gives $O(n)$ per level and $O(n\log n)$ total.

Because this algorithm has already computed $f(i)$ for $i\leq l$ before solving $(l,r]$, it also supports dynamic computation.

## Interval Partitioning

Consider partitioning $[1,n]$ into intervals $[a_1,b_1],\cdots,[a_k,b_k]$, where $a_1=1$, $b_k=n$, and $b_i+1=a_{i+1}$. The cost is $\sum_{i=1}^kw(a_i,b_i)$. The 1D1D transition is

$$
f(i) = \min_{1\leq j\leq i} f(j-1)+w(j,i) \qquad (1\leq i\leq n)
$$

with $f(0)=0$. If $w(j,i)$ satisfies the quadrangle inequality, then so does $f(j-1)+w(j,i)$, because the first term has no mixed dependence on $j$ and $i$. Since the cost depends on previous states, this transition must be computed in order, so the binary-search queue or simplified LARSCH algorithm is preferred. The complexity is $O(n\log n)$.

### Fixed Number Of Intervals

If the number of intervals is fixed to $m$, add it as a DP dimension:

$$
f(k,i) = \min_{1\leq j\leq i} f(k-1,j-1)+w(j,i) \qquad (1\leq k\leq m,\ 1\leq i\leq n) \tag{2}
$$

where $f(0,0)=0$ and $f(0,i)=f(k,0)=\infty$. Each layer can be computed with the algorithms above in $O(n\log n)$, for a total of $O(mn\log n)$.

???+ note "Theorem 2"
    If $w$ satisfies the quadrangle inequality, then for problem (2), $\operatorname{opt}(k-1,i) \leq \operatorname{opt}(k,i) \leq \operatorname{opt}(k,i+1)$.

??? note "Proof"
    The second inequality is just decision monotonicity inside layer $k$. The key is the first inequality.
    
    We prove $\operatorname{opt}(k,i) \leq \operatorname{opt}(k+1,i)$. Suppose there are two partitions of $[1,i]$ (indexed in reverse order): $[a_{k},d_{k}],\cdots,[a_1,d_1]$ and $[b_{k+1},c_{k+1}],\cdots,[b_1,c_1]$. Each left endpoint is the smallest optimal decision for the problem ending at the corresponding right endpoint; symmetrically, when considering partitions from right to left, each right endpoint is the smallest optimal decision for the problem starting at the corresponding left endpoint. By decision monotonicity, if $a_{j-1} > b_{j-1}$, equivalently $d_j > c_j$, then $a_j > b_j$. Therefore, if the desired statement failed, then $a_1>b_1$, and induction would give $a_k>b_k$, contradicting the setup.
    
    The first inequality can also be proved as follows. Using the same two partitions, if the claim failed then $a_1>b_1$, while $a_k<b_k$. Let $j>1$ be the smallest index such that $a_j\leq b_j$. Then $a_{j-1}>b_{j-1}$, so $d_j>c_j$, giving $a_j \leq b_j \leq c_j < d_j$. Recombine the two partitions. For the $(k+1)$-interval partition $[b_{k+1},c_{k+1}],\cdots,[b_{j+1},c_{j+1}],[b_j,d_j],[a_{j-1},d_{j-1}],\cdots,[a_1,d_1]$, optimality gives
    
    $$
    \begin{aligned}
    &w(b_{k+1},c_{k+1})+\cdots+w(b_{j+1},c_{j+1})+w(b_j,c_j)+w(b_{j-1},c_{j-1})+\cdots+w(b_1,c_1) \\
    &\qquad \leq w(b_{k+1},c_{k+1})+\cdots+w(b_{j+1},c_{j+1})+w(b_j,d_j)+w(a_{j-1},d_{j-1})+\cdots+w(a_1,d_1).
    \end{aligned}
    $$
    
    Similarly, for the $k$-interval partition $[a_{k},d_{k}],\cdots,[a_{j+1},d_{j+1}],[a_j,c_j],[b_{j-1},c_{j-1}],\cdots,[b_1,c_1]$, we have
    
    $$
    \begin{aligned}
    &w(a_{k},d_{k})+\cdots+w(a_{j+1},d_{j+1})+w(a_j,d_j)+w(a_{j-1},d_{j-1})+\cdots+w(a_1,d_1) \\
    &\qquad < w(a_{k},d_{k})+\cdots+w(a_{j+1},d_{j+1})+w(a_j,c_j)+w(b_{j-1},c_{j-1})+\cdots+w(b_1,c_1).
    \end{aligned}
    $$
    
    The second inequality is strict because $a_1>b_1$, while $a_1$ is assumed to be the smallest optimal left endpoint of the last interval among all $k$-interval partitions. Adding the two inequalities gives $w(b_j,c_j)+w(a_j,d_j)<w(b_j,d_j)+w(a_j,c_j)$, contradicting the quadrangle inequality.

This theorem restricts the search range for $j$. Iterate $k$ forward and $i$ backward, and brute-force only the current bounds. The total complexity is $O(n(n+m))$, not $O(nm)$: over each secondary diagonal of the $n\times m$ state matrix the scanned decision ranges sum to $O(n)$, and there are $O(n+m)$ such diagonals.

???+ note "Theorem 3"
    If $w$ satisfies the quadrangle inequality, then the optimal value $g(k):=f(n,k)$ of problem (2) is convex in $k$.

??? note "Proof"
    We prove $g(k-1)+g(k+1)\ge 2g(k)$. Consider optimal partitions into $(k-1)$ and $(k+1)$ intervals, respectively $[a_1,d_1],\cdots,[a_{k-1},d_{k-1}]$ and $[b_1,c_1],\cdots,[b_{k+1},c_{k+1}]$. Take the smallest $1\leq j\leq k-1$ such that $c_{j+1}\leq d_j$; it exists because $c_k<n=d_{k-1}$. By minimality, $b_{j+1}>a_j$. Hence $a_j < b_{j+1} \leq c_{j+1} \leq d_j$. As above, swap the suffixes of the two partitions to obtain
    
    $$
    \begin{aligned}
    & [a_1,d_1],\cdots,[a_{j-1},d_{j-1}],[a_j,c_{j+1}],[b_{j+2},c_{j+2}],\cdots,[b_{k+1},c_{k+1}], \\
    & [b_1,c_1],\cdots,[b_j,c_j],[b_{j+1},d_j],[a_{j+1},d_{j+1}],\cdots,[a_{k-1},d_{k-1}].
    \end{aligned}
    $$
    
    Both are $k$-interval partitions, so optimality gives
    
    $$
    \begin{aligned}
    2g(k) &\le w(a_1,d_1) + \cdots + w(a_{j-1},d_{j-1}) + w(a_j,c_{j+1}) + w(b_{j+2},c_{j+2}) + \cdots + w(b_{k+1},c_{k+1}) \\
    &\quad + w(b_1,c_1) + \cdots + w(b_j,c_j) + w(b_{j+1},d_j) + w(a_{j+1},d_{j+1}) + \cdots + w(a_{k-1},d_{k-1}) \\
    &\le w(a_1,d_1) + \cdots + w(a_{j-1},d_{j-1}) + w(a_j,d_j) + w(a_{j+1},d_{j+1}) + \cdots + w(a_{k-1},d_{k-1}) \\
    &\quad + w(b_1,c_1) + \cdots + w(b_j,c_j) + w(b_{j+1},c_{j+1}) + w(b_{j+2},c_{j+2}) + \cdots + w(b_{k+1},c_{k+1}) \\
    &= g(k-1) + g(k+1).
    \end{aligned}
    $$
    
    The second inequality is exactly the quadrangle inequality, proving convexity.

This allows WQS binary search, also known as the Aliens Trick. Add a parameter $c$ to each interval cost, $w_c(j,i)=w(j,i)+c$, solve the unconstrained partitioning problem, and binary-search $c$ so that the optimal number of intervals is $m$. The original answer is $f(n,m)=f_c(n)-cm$. See [WQS Binary Search](./wqs-binary-search.md) for implementation details. The complexity is $O(n\log n\log C)$.

???+ example "Example 3: [P4767 [IOI2000] Post Office, Enhanced](https://www.luogu.com.cn/problem/P4767)  [P6246 [IOI2000] Post Office, Enhanced Enhanced](https://www.luogu.com.cn/problem/P6246)"
    There are villages on a highway, represented by distinct integer coordinates on a number line. Build a given number of post offices in some villages so that the sum of distances from every village to its nearest post office is minimized.

??? note "Idea"
    The villages served by one post office form a consecutive interval. For an interval $[i,j]$, the best post office location is the village at index $\left\lfloor\dfrac{i+j}2\right\rfloor$, and prefix sums compute $w(i,j)$. Thus the problem becomes fixed-count interval partitioning, and $w$ satisfies the quadrangle inequality.

??? note "Implementation 1, the second optimization above, complexity $O(n(n+m))$"
    ```cpp
    --8<-- "docs/dp/code/opt/quadrangle/quadrangle_2.cpp"
    ```

??? note "Implementation 2, WQS binary search, complexity $O(n\log n\log C)$"
    ```cpp
    --8<-- "docs/dp/code/opt/quadrangle/quadrangle_3.cpp"
    ```

## Interval Merging

Another class of problems optimized by the quadrangle inequality is interval merging: merge $n$ unit intervals $[i,i]$ pairwise until $[1,n]$ is obtained. Merging $[j,k]$ and $[k+1,i]$ costs $w(j,i)$. The transition is

$$
f(j,i) = \min_{j \leq k < i} f(j,k) + f(k+1,i) + w(j,i) \qquad (1\le j< i\le n) \tag{3}
$$

with $f(i,i)=0$. The naive complexity is $O(n^3)$. With decision monotonicity it can be reduced to $O(n^2)$. This is Knuth's optimization, also known as the Knuth-Yao speedup.

Besides the quadrangle inequality, interval merging needs monotonicity under interval inclusion.

-   **Interval-inclusion monotonicity**: if for any $a\leq b\leq c\leq d$,

    $$
    w(b,c) \leq w(a,d),
    $$

    then $w$ is monotone with respect to interval inclusion.

This is the first-order condition that $w(j,i)$ decreases as $j$ moves left and increases as $i$ moves right.

???+ note "Lemma 1"
    If $w$ satisfies interval-inclusion monotonicity and the quadrangle inequality, then $f(j,i)$ satisfies the quadrangle inequality.

??? note "Proof"
    Assume $a \leq b \leq c \leq d$. We prove $f(a,d) + f(b,c) \geq f(a,c) + f(b,d)$ by induction on $d-a$. The statement is an identity when $a=b$ or $c=d$. In the general case, classify by the position of $d'=\operatorname{opt}(a,d)$.
    
    First, suppose $c \leq d'$ or $d'<b$, so $[b,c]$ is contained in either $[a,d']$ or $[d'+1,d]$. Assume $c\leq d'$; the other case is analogous. Then
    
    $$
    \begin{aligned}
    f(a,d) + f(b,c)
    & = f(a,d') + f(d'+1,d) + w(a,d) + f(b,c) \\
    & \geq f(a,c) + f(b,d') + f(d'+1,d) + w(a,d) \\
    & \geq f(a,c) + f(b,d') + f(d'+1,d) + w(b,d) \\
    & \geq f(a,c) + f(b,d).
    \end{aligned}
    $$
    
    Here the first inequality is the induction hypothesis $f(a,c) + f(b,d') \leq f(a,d') + f(b,c)$, the second is interval-inclusion monotonicity $w(b,d)\leq w(a,d)$, and the third is optimality of $f(b,d)$.
    
    Second, suppose $b \leq d' < c$, so $d'$ lies inside $[b,c]$. Consider $c'=\operatorname{opt}(b,c)$. Assume $c'\leq d'$; the other case is analogous. Then
    
    $$
    \begin{aligned}
    f(a,d) + f(b,c)
    & = f(a,d') + f(d'+1,d) + w(a,d) + f(b,c') + f(c'+1,c) + w(b,c) \\
    & \geq f(a,c') + f(c'+1,c) + w(b,c) + f(b,d') + f(d'+1,d) + w(a,d) \\
    & \geq f(a,c') + f(c'+1,c) + w(a,c) + f(b,d') + f(d'+1,d) + w(b,d) \\
    & \geq f(a,c) + f(b,d).
    \end{aligned}
    $$
    
    The first inequality uses the induction hypothesis $f(a,c') + f(b,d') \leq f(a,d') + f(b,c')$, the second uses the quadrangle inequality $w(a,c)+w(b,d)\leq w(a,d)+w(b,c)$, and the third uses optimality of $f(a,c)$ and $f(b,d)$.

???+ note "Theorem 4"
    If $w$ satisfies interval-inclusion monotonicity and the quadrangle inequality, then the smallest optimal split $\operatorname{opt}(j,i)$ in (3) satisfies
    
    $$
    \operatorname{opt}(j,i-1) \leq \operatorname{opt}(j,i) \leq \operatorname{opt}(j+1,i). \qquad (j + 1 < i)
    $$

??? note "Proof"
    Lemma 1 shows that $f(j,i)$ satisfies the quadrangle inequality. For fixed $j$, the objective as a function of $(k,i)$ also satisfies it, giving $\operatorname{opt}(j,i-1)\leq\operatorname{opt}(j,i)$. For fixed $i$, applying the same argument as a function of $(k,j)$ gives $\operatorname{opt}(j,i)\leq\operatorname{opt}(j+1,i)$.

Compute intervals by increasing length. For each $[j,i]$, brute-force only $k\in[\operatorname{opt}(j,i-1),\operatorname{opt}(j+1,i)]$. For all intervals of the same length the total decision range is $O(n)$, so the total complexity is $O(n^2)$.

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/dp/code/opt/quadrangle/quadrangle-knuth-optimization.cpp:core"
    ```

## Functions Satisfying The Quadrangle Inequality

The following properties are useful when proving that a function satisfies the quadrangle inequality.

**Property 1**: If $w_1(j,i)$ and $w_2(j,i)$ both satisfy the quadrangle inequality (or interval-inclusion monotonicity), then for any $c_1,c_2\geq 0$, $c_1w_1+c_2w_2$ also satisfies it.

**Property 2**: If $w(j,i)=f(j)-g(i)$ for some functions $f$ and $g$, then $w$ satisfies the quadrangle identity. If $f$ and $g$ are increasing, then $w$ also satisfies interval-inclusion monotonicity.

**Property 3**: Let $h(x)$ be an increasing convex function. If $w(j,i)$ satisfies the quadrangle inequality and interval-inclusion monotonicity, then $h(w(j,i))$ also satisfies both.

**Property 4**: Let $h(x)$ be a convex function. If $w(j,i)$ satisfies the quadrangle identity and interval-inclusion monotonicity, then $h(w(j,i))$ satisfies the quadrangle inequality.

Here, "convex" means the usual lower-convex convention: where differentiable, the first derivative is increasing.

??? note "Proof"
    The first two properties are immediate. For Property 3, consider the mixed second difference for $a \leq j \leq b \leq c \leq i \leq d$:
    
    $$
    \begin{aligned}
    \Delta_i\Delta_j h\left(w(j,i)\right)
    &= h\left(w(b,d)\right) - h\left(w(a,c) + \Delta_jw(j,c) + \Delta_iw(a,i)\right) \\
    &\quad + h\left(w(a,c) + \Delta_jw(j,c) + \Delta_iw(a,i)\right) - h\left(w(a,c) + \Delta_jw(j,c)\right) \\
    &\quad - h\left(w(a,c) + \Delta_iw(a,i)\right) + h\left(w(a,c)\right).
    \end{aligned}
    $$
    
    Interval monotonicity gives $\Delta_iw(a,i)\geq0$ and $\Delta_jw(j,c)\leq0$. Convexity of $h$ makes the last two lines non-positive, and monotonicity of $h$ together with the quadrangle inequality makes the first line non-positive. Hence the mixed second difference is non-positive.
    
    This is the discrete analogue of
    
    $$
    \frac{\partial^2}{\partial x\partial y}h(w(x,y)) = h''(w(x,y))\frac{\partial }{\partial x}w(x,y)\frac{\partial}{\partial y}w(x,y) + h'(w(x,y))\frac{\partial^2}{\partial x\partial y}w(x,y) \leq 0.
    $$

## Exercises

-   [Codeforces - Ciel and Gondolas](https://codeforces.com/contest/321/problem/E)(Be careful with I/O!)
-   [SPOJ - LARMY](https://www.spoj.com/problems/LARMY/)
-   [Codechef - CHEFAOR](https://www.codechef.com/problems/CHEFAOR)
-   [Hackerrank - Guardians of the Lunatics](https://www.hackerrank.com/contests/ioi-2014-practice-contest-2/challenges/guardians-lunatics-ioi14)
-   [ACM ICPC World Finals 2017 - Money](https://open.kattis.com/problems/money)

## References And Notes

-   [Quora Answer by Michael Levin](https://www.quora.com/What-is-divide-and-conquer-optimization-in-dynamic-programming)
-   [Video Tutorial by "Sothe" the Algorithm Wolf](https://www.youtube.com/watch?v=wLXEWuDWnzI)
-   [Divide and Conquer DP](https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html)
-   [Knuth's Optimization](https://cp-algorithms.com/dynamic_programming/knuth-optimization.html)
-   [Quadrangle Inequality Properties](https://codeforces.com/blog/entry/86306)
-   [Wang Qinshi, "A Brief Analysis of a Class of Binary Search Methods"](https://github.com/hzwer/shareOI/blob/master/%E5%9F%BA%E7%A1%80%E7%AE%97%E6%B3%95/%E6%B5%85%E6%9E%90%E4%B8%80%E7%B1%BB%E4%BA%8C%E5%88%86%E6%96%B9%E6%B3%95_%E7%8E%8B%E9%92%A6%E7%9F%B3.pdf)
-   [Simplified LARSCH Algorithm by noshi91](https://noshi91.hatenablog.com/entry/2023/02/18/005856)
-   [Quadrangle Inequality and Decision Monotonicity by b6e0_ - Luogu Column](https://www.luogu.com.cn/article/h81hh5lk)
-   [A Poor-Man's LARSCH Algorithm for Online Decision Monotonicity by Register_int - Luogu Column](https://www.luogu.com.cn/article/vqf42hah)

[^cmp-min-opt]: In the algorithm description, "worse" and "better" are lexicographic comparisons: compare the function value first and the decision index second. "Better" means a smaller value, or the same value with a smaller decision index.

[^larsch]: Larmore, Lawrence L., and Baruch Schieber. "On-line dynamic programming with applications to the prediction of RNA secondary structure." Journal of Algorithms 12, no. 3 (1991): 490-515.
