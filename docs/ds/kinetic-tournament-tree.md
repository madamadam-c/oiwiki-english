author: Jerry3128

Prerequisite: [Segment Tree](./seg.md)

## Problem Introduction

Given a sequence of univariate linear functions $F=\{f_1,\dots,f_n\}$, where $f_i: \mathbf{R} \rightarrow \mathbf{R}$, $f_i(x)=k_ix+b_i$, and $k_i,b_i \in \mathbf{R}$, we need to maintain the following operations:

-   $\operatorname{QueryMax}(l,r)$: given $l$ and $r$, return $\max_{i=l}^r{f_i(0)}$.
-   $\operatorname{TranslateLeft}(l,r,\delta)$: given $l$, $r$, and $\delta$, for all $i\in[l,r]$, perform $f_i(x) \leftarrow f_i(x+\delta)$. This is equivalent to performing $b_i\leftarrow b_i+k_i\delta$, where $\delta > 0$.

For convenience, assume all functions are distinct.

The essence of translating a range of linear functions to the left is $b_i \leftarrow k_i\cdot \delta$: for the constant term $b_i$, add the slope $k_i$ multiplied by the horizontal translation amount $\delta$. This operation is equivalent to the "position-coefficient weighted range add" often seen in data structure problems: for the interval $[l, r]$, for every index $i$, add a fixed number $\delta$ multiplied by the position-specific coefficient $k_i$ to its value. Therefore, range translation of linear functions is essentially position-coefficient weighted range addition.

To show the distinctive binary-tree divide-and-conquer structure of KTT, we will start directly from range translation.

## Kinetic Data Structures

Kinetic Data Structures are abbreviated as KDS. KDS are used to maintain properties of a system of geometric objects during continuous motion.

### Event Queue

Assume every point has a known motion plan, which can provide complete or partial information about its motion. For example, the curve or line formed by function $f_i(x)$ can describe the trajectory of moving point $i$ well. A motion plan may change at any time, perhaps due to collision or environmental interaction; we call the cause of a motion-plan change an event. The event queue gives events in chronological order.

A key aspect of KDS is that it needs easily maintainable events: the event types in the event queue correspond to possible combinatorial changes involving a constant, usually small, number of objects. For example, in this problem, one event type we use is "the relative order of function $f_i(0)$ and function $f_{j}(0)$ changes."

The event queue can be maintained implicitly.

### Certificates

These events should be equivalent to guarantees given by a set of low-degree algebraic conditions, each involving a finite number of objects. We call these conditions KDS certificates. For example, $[f_i(0) > f_j(0)]$.

## Kinetic Tournament Tree

### Introduction

Kinetic Tournament Tree, abbreviated KTT, belongs to Kinetic Data Structures. It first appeared in the 1999 paper [Data Structures for Mobile Data](https://www.sciencedirect.com/science/article/pii/S0196677498909889), and is used to maintain continuously changing data. More generally, any structure using the following kinetization strategy can be called a Kinetic Tournament:

-   Generate correctness certificates for key operations in a static algorithm, such as comparisons, and associate each certificate with a global event queue that records the time at which the certificate may fail.
-   When a certificate fails, efficiently update the algorithm output and maintain the certificate set.

In the competitive programming community, it became popular through the 2020 National Training Team paper *[A Brief Discussion on Dynamic Maintenance of Function Extrema](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/IOI2020%E4%B8%AD%E5%9B%BD%E5%9B%BD%E5%AE%B6%E5%80%99%E9%80%89%E9%98%9F%E8%AE%BA%E6%96%87%E9%9B%86%20%E9%9D%9E%E6%AD%A3%E5%BC%8F%E7%89%88.pdf)*. KTT in academia differs from KTT in competitive programming in application domain and implementation, so we introduce the KTT optimized for the competitive programming setting.

### Basic Structure

First, consider designing a data structure similar to a segment tree to maintain a static maximum. Build the segment tree structure. For each non-leaf node, its value is the larger value among its two child nodes. After $O(n)$ comparisons, the value at the root is the global maximum. Now the values begin to change. As long as the KTT can detect every change in the source of the maximum at a tree node, we can maintain the global maximum.

To let the KTT detect every change in the source of a maximum on the tree, for a tree node $x$ and the functions $f_L$ and $f_R$ provided by its left and right children, define the certificate as "the relative order of $f_L$ and $f_R$ remains unchanged." When the certificate fails, we need to walk along a path in the tree to the node whose certificate failed, then update its information. To maintain the failure time of each certificate, observe that a certificate fails exactly when two functions have equal values. Thus the problem becomes finding the x-coordinate of the intersection of two linear functions, which can be done in $O(1)$ time.

For each tree node, maintain the function attaining the maximum value at $0$, the current certificate failure time, and the earliest failure time among all certificates in the subtree. Then, at the failure time of any node certificate, we can find it and update its information. This information records the functions themselves. Next, consider maintaining range translation operations. Since translations can simply be accumulated, we can handle range translation operations with lazy tags.

Define a lazy tag $\Delta_v$ indicating that all functions on nodes inside the subtree of node $v$ should be translated left by $\Delta_v$ units. Now suppose a new operation translates all functions in the subtree of tree node $v$ left by $\delta$, i.e. $f(x)\leftarrow f(x+\delta)$. We need to update the lazy tag: $\Delta_v\leftarrow \Delta_v + \delta$, accumulating the offset for all nodes in the subtree. At the same time, left translation also changes function values at $0$. If the certificate failure x-coordinate is $t$, then after translation the failure coordinate becomes $t-\delta$. If $t-\delta$ crosses $0$, the certificate has failed, so we need to recursively find the node containing the current certificate, update that node, and update the new information upward to the root. This process can be performed together with the modification.

Thus, we obtain a simple implementation.

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/ds/code/ktt/ktt_1.cpp:core"
    ```

### Complexity Analysis

Proving the time complexity of KTT requires potential analysis.

Let $d(x)$ be the depth of node $x$ in the segment tree, with the root depth equal to $1$. Define the potential of node $x$ in the segment tree as:

$$
\alpha(x) = \begin{cases}
d(x) & \text{if the lower slope function has larger value}  \\
0    & \text{otherwise}\\
\end{cases}
$$

That is, among the two functions compared at $x$, if the function with smaller slope has a larger value at $0$, then the current node's potential is $d(x)$; otherwise it is $0$.

Define the potential of the whole KTT as the sum of all node potentials:

$$
\Phi = \sum_x \alpha(x)
$$

Consider an actual update of node $x$ and its parent $p$, with cost $c=1$. Let the potentials before and after the update be $\Phi$ and $\Phi'$ respectively. Compute the amortized update cost of updating node $x$. Since the current node $x$ is updated, its potential must drop from $d(x)$ to $0$ at this moment. For $p$, in the worst case its potential may rise from $0$ to $d(p)$:

$$
\begin{aligned}
\hat{c} &= 1 + \Phi' - \Phi\\
    &= 1 + (\alpha'(p) + \alpha'(x)) - (\alpha(p) + \alpha(x))\\
    &= 1 + (\alpha'(p) - \alpha(p)) + (\alpha'(x) - \alpha(x))\\
    &\leq 1 + d(p) - d(x)\\
    &= 0
\end{aligned}
$$

Summing the actual costs, define the initial potential $\Phi_s$ and the final potential $\Phi_t$:

$$
\begin{aligned}
\sum c  &= \sum \hat{c} + \Phi_{s} - \Phi_{t}\\
    &\leq \Phi_{s} - \Phi_{t}\\
    &=O(n\log n)
\end{aligned}
$$

This bounds the number of times KTT finishes all certificate-failure updates when only global modifications exist.

Additionally, consider the effect of range translation on the potential. For one range translation, the nodes to consider are those whose subtree contains some, but not all, tree nodes affected by the range translation. These are exactly the nodes visited on the tree during the modification operation; there are at most $O(\log n)$ of them. In the worst case, each node's potential increases by $d(x)\le \log n$, so each operation increases the potential by $O(\log^2 n)$.

To maintain range translation, certificate-update operations will be executed $O(n\log n + m\log^2 n)$ times. Each certificate update requires walking down a path in the tree to the node whose certificate failed, which costs $O(\log n)$. Therefore, the total time complexity is $O(n\log^2 n+ m\log^3 n)$.

The advantage of this method is that it already touches the lower bound of the problem's time complexity, $O(\lambda_{s}(n)\log^2 n)$. Here $\lambda_{s}(n)$ denotes the longest length of an (n, s) Davenport-Schinzel sequence. Linear functions correspond to $s=1$, where $\lambda_1(n)=n$. This belongs to computational geometry, and this article will not elaborate further.

### Higher-Degree Cases

If we maintain polynomial functions, or even more complex functions, rather than linear functions, how should we handle them? Two complex functions may have multiple intersection points. Given a sequence of continuous, fully defined univariate functions $F=\{f_1,\dots,f_n\}$, where $f_i: \mathbf{R} \rightarrow \mathbf{R}$, assume every pair of function graphs intersects at most $s$ times. A set of degree-$s$ polynomial functions is a representative case satisfying this requirement.

For the same problem, use potential analysis.

Let $d(x)$ be the depth of node $x$ in the segment tree, with the root depth equal to $1$. Define $I(x)$ as, for node $x$, the number of intersection points after $0$ between the two functions compared there. Define the potential of node $x$ in the segment tree as:

$$
\alpha(x)=d(x)^{\log_2(s+1)}I(x)
$$

Define the potential of the whole KTT as the sum of all node potentials:

$$
\Phi = \sum_x \alpha(x)
$$

Consider an actual update of node $x$ and its parent $p$, with cost $c=1$. Let the potentials before and after the update be $\Phi$ and $\Phi'$ respectively. Compute the amortized update cost of updating node $x$. Since the current node $x$ is updated, its potential must drop from $d(x)^{\log_2(s+1)}I(x)$ to $d(x)^{\log_2(s+1)}(I(x)-1)$ at this moment. For $p$, in the worst case its potential may rise from $0$ to $d(p)^{\log_2(s+1)}$:

$$
\begin{aligned}
        \hat{c} &= 1 + \Phi' - \Phi\\
                &= 1 + (\alpha'(x) - \alpha(x)) + (\alpha'(p) - \alpha(p))\\
                &\leq 1 - d(x)^{\log_2{(s+1)}} + s(d(x)-1)^{\log_2{(s+1)}}\\
                &\leq 0
    \end{aligned}
$$

From the third line to the fourth line, we use the restriction that $d(x)$ is a positive integer.

Summing the actual costs, define the initial potential $\Phi_s$ and the final potential $\Phi_t$:

$$
\begin{aligned}
    \sum c  &= \sum \hat{c} - \Phi_t + \Phi_s\\
            &\leq \Phi_s - \Phi_t\\
            &= O(ns (\log n)^{\log_2{(s+1)}})
\end{aligned}
$$

We get the upper bound $O(ns (\log n)^{1+\log_2{(s+1)}} + ms (\log n)^{2+\log_2{(s+1)}})$.[^ref1]

### Approximate Case

Given a sequence of continuous, fully defined univariate functions $F=\{f_1,\dots,f_n\}$, define $\mathfrak U_F(x)$, $\mathfrak L_F(x)$, and $\mathfrak E_F(x)$ as the upper envelope, lower envelope, and extent, respectively.

$$
\begin{aligned}
    \mathfrak U_F(x) & = \max\{f_i(x) \mid f_i \in F\} \\
    \mathfrak L_F(x) & = \min\{f_i(x) \mid f_i \in F\} \\
    \mathfrak E_F(x) & = \mathfrak U_F(x) - \mathfrak L_F(x)
\end{aligned}
$$

We only require the program to return $\tilde{\mathfrak U}_F(x)$ satisfying

$$
\mathfrak U_F(x) \geq \tilde{\mathfrak U}_F(x) \geq \mathfrak U_F(x) - \epsilon \mathfrak E_F(x)
$$

Then, in complex cases, we can achieve $O((1/\epsilon^2)n\log^3 n)$, independent of the polynomial degree, and we allow functions to undergo range left or right translations simultaneously.

## References and Notes

[^ref1]: Note that this only gives an upper bound. The lower bound of the complexity should be $O(\lambda_{s}(n)\log n)$. The author conjectures that this potential-analysis construction should refer to the general formula for $\lambda_{s}(n)$ corresponding to Davenport-Schinzel sequences to obtain a tighter upper bound.

-   P. K. Agarwal, S. Har-Peled, and K. R. Varadarajan. Approximating extent measures of points. J. ACM, 51(4):606–635, July 2004.
-   J. Basch, L. J. Guibas, and J. Hershberger. Data structures for mobile data. Journal of Algorithms, 31(1):1–28, 1999.
-   G. Alexandron, H. Kaplan, and M. Sharir. Kinetic and dynamic data structures for convex hulls and upper envelopes. Computational Geometry, 36(2):144–158, 2007.
