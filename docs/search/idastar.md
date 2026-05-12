Prerequisites: [A\* algorithm](./astar.md), [iterative deepening search](./iterative.md)

This page briefly introduces the IDA\* algorithm. IDA\* is A\* using iterative deepening.

## Process

The IDA\* algorithm is a variant of iterative deepening search. Iterative deepening search limits the search depth in each DFS, while IDA\* limits the path cost of a single DFS.

In one iteration, the algorithm starts DFS from the start point $s$, records the actual cost $g(x)$ to reach the current node $x$, and uses the estimate $h(x)$ of the minimum cost from it to the target for pruning. If the estimated total cost of reaching the target along the current path

$$
f(x) = g(x) + h(x)
$$

exceeds the threshold $C$, the search of this branch stops.

The threshold $C$ is dynamically updated between iterations. The initial threshold is set to the total cost estimate of the start point, $h(s)$. In one iteration, whenever the search stops because the threshold is exceeded, record the minimum total cost estimate among all successor nodes that have not yet been visited. After the iteration ends, update the threshold to this minimum value and continue with the next round of search.

## Properties

Because it uses the same pruning strategy as the A\* algorithm, the discussion of A\* algorithm properties also applies to IDA\*.

Compared with the A\* algorithm, IDA\* has the following advantages:

-   It does not need duplicate detection or sorting, which helps depth-based pruning.
-   It has lower space requirements. Each iteration is a depth-first search, but the path cost in the search is limited, and using DFS can reduce space consumption.

At the same time, it also has disadvantages:

-   Repeated search. Even if two consecutive searches differ only slightly, every relaxation of the limit requires searching again from the beginning.

## Implementation

Let $h$ be a suitable evaluation function, and let $s$ be the search start point. The complete algorithm process is roughly as follows:

$$
\begin{array}{l}
\textbf{Algorithm. }\textrm{IdaStar}():\\
\textbf{Output. }\text{The shortest path, }\textit{path}\text{, and its cost, }C\text{, if a path exists,}\\
\quad \text{and }\textrm{NOT}\_\textrm{FOUND}\text{, otherwise.}\\
\textbf{Method.}\\
\begin{array}{ll}
1  & C \gets h(s) \\
2  & path \gets [s] \\
3  & \textbf{while }\text{true}\\
4  & \quad t \gets \textrm{Search}(\textit{path},0,C)\\
5  & \quad \textbf{if } t=\text{FOUND}\textbf{ then return }(\textit{path},C) \\
6  & \quad \textbf{if } t=\infty\textbf{ then return }\textrm{NOT}\_\textrm{FOUND} \\
7  & \quad C \gets t
\end{array}\\
\\
\textbf{Sub-Algorithm. }\textrm{Search}(\textit{path},g,C):\\
\textbf{Input. }\text{The current path, }\textit{path}\text{, its cost, }g\text{, and search limit }C.\\
\textbf{Output. }\text{FOUND, if the target node has been reached; }\infty\text{, if all}\\
\quad \text{reachable nodes have been explored; otherwise, the minimum}\\
\quad \text{total cost, }t\text{, among nodes not yet explored.}\\
\textbf{Method.}\\
\begin{array}{ll}
1  & \textit{node} \gets \text{the last element in }\textit{path}\\
2  & f \gets g + h(\textit{node}) \\
3  & \textbf{if } f > C \textbf{ then return } f \\
4  & \textbf{if }\textit{node}\text{ is the target }\textbf{then return }\text{FOUND}\\
5  & \textit{min} \gets \infty \\
6  & \textbf{for }\text{each }\textit{child}\text{ of }\textit{node }\textbf{do}\\
7  & \quad \textbf{if }\textit{child}\text{ not in }\textit{path}\textbf{ then}\\
8  & \quad \quad \text{append }\textit{child}\text{ to }\textit{path}\\
9  & \quad \quad t \gets \text{Search}(\textit{path}, g + \text{Cost}(\textit{node},\textit{child}), C)\\
10 & \quad \quad \textbf{if }t = \text{FOUND}\textbf{ then return }\text{FOUND}\\
11 & \quad \quad \textbf{if }t < \textit{min}\textbf{ then }\textit{min}\gets t\\
12 & \quad \quad \text{remove the last element of }\textit{path}\\
13 & \textbf{return }\textit{min}
\end{array}
\end{array}
$$

## Examples

???+ example "[Egyptian Fractions](https://www.luogu.com.cn/problem/P1763)"
    In ancient Egypt, people represented every rational number as a sum of distinct unit fractions (that is, $1/a$, $a\in\mathbf{N}_+$). For example, $\dfrac{2}{3}=\dfrac{1}{2}+\dfrac{1}{6}$, but $\dfrac{2}{3}=\dfrac{1}{3}+\dfrac{1}{3}$ is not allowed, because repeated unit fractions are not allowed among the addends.
    
    For a fraction $\dfrac{a}{b}$, there are many representations. The rule is: among different representations of the same fraction, one with fewer addends is better than one with more addends; if the number of addends is the same, the representation whose smallest fraction is larger is better. For example, $\dfrac{19}{45}=\dfrac{1}{5}+\dfrac{1}{6}+\dfrac{1}{18}$ is the best solution.
    
    Given integers $a,b$ ($0<a<b<1000$), write a program to compute the best expression.

??? note "Solution idea"
    In theory, this problem can be solved with backtracking, but the solution tree is very "terrifying": not only does the depth have no obvious upper bound, but the choices of addends are also theoretically infinite. In other words, if breadth-first traversal is used, even one layer cannot be fully expanded, because every layer is infinite.
    
    The solution is to use iterative deepening search: enumerate the depth limit $C$ from small to large, and each search only considers nodes whose depth does not exceed $C$. In this way, as long as the solution depth is finite, it can certainly be enumerated in finite time.
    
    The depth limit $C$ can also be used for pruning. Expand in increasing order of denominators. If at level $i$, the sum of the first $i$ fractions is $\dfrac{c}{d}$ and the $i$-th fraction is $\dfrac{1}{e}$, then at least
    
    $$
    h = \left(\dfrac{a}{b}-\dfrac{c}{d}\right)/\left(\dfrac{1}{e+1}\right)
    $$
    
    more fractions are needed for the sum to reach $\dfrac{a}{b}$. For example, suppose the current search has reached $\dfrac{19}{45}=\dfrac{1}{5}+\dfrac{1}{100}+\cdots$. Then each later fraction is at most $\dfrac{1}{101}$, and at least $\left({\dfrac{19}{45}-\dfrac{1}{5}}\right)/\left({\dfrac{1}{101}}\right)=23$ terms are needed for the sum to reach $\dfrac{19}{45}$. Therefore, the first $22$ iterations will not consider this subtree at all. The key here is that we can estimate how many more steps are at least needed before a solution can appear.
    
    Note that the word "at least" here means the estimate is "optimistic". As with the A\* algorithm, a good estimation function must be "optimistic"; that is, it must not overestimate the actual cost. Replacing the depth limit $g\le C$ in iterative deepening search with the stricter limit $g + h \le C$ gives the IDA\* algorithm discussed on this page. Because the path cost in this article is its length, the IDA\* algorithm is also limiting the path length, but with an added estimate of how many more steps are needed. In more general problems, other estimation functions can be designed according to the specific cost to be minimized.
    
    In the implementation, further pruning optimizations are applied to the IDA\* algorithm:
    
    1.  When expanding a node, the next denominator to consider is at least $\left(\dfrac{a}{b}-\dfrac{c}{d}\right)^{-1}$, which can be used to improve the starting point for enumerating $e$.
    2.  The path cost limit of IDA\* can be transformed into
    
        $$
        e \le \left(\dfrac{a}{b}-\dfrac{c}{d}\right)^{-1}(C-g) - 1.
        $$
    
        Therefore, it is unnecessary to enumerate all subsequent denominators and check them one by one; it is enough to enumerate up to this upper bound.
    3.  When the search reaches the last two fractions, directly use a quadratic equation to determine feasibility instead of continuing the search. Specifically, we need to find $e<x<y\le E_\text{max}$ such that
    
        $$
        \dfrac{1}{x} + \dfrac{1}{y} = \dfrac{p}{q} := \dfrac{a}{b}-\dfrac{c}{d},
        $$
    
        We only need to solve the system of two quadratic equations
    
        $$
        \begin{cases}
        x + y = kp,\\
        xy = kq
        \end{cases}
        $$
    
        where $k\in\mathbf N_+$. From the theory of quadratic equations, the system has two distinct real roots only when
    
        $$
        \Delta = k^2p^2-4kq > 0 \iff k > \dfrac{4q}{p^2}
        $$
    
        holds:
    
        $$
        x = \dfrac{kp - \sqrt{\Delta}}{2},~ y = \dfrac{kp + \sqrt{\Delta}}{2}.
        $$
    
        Therefore, we can directly enumerate all feasible $k$ values and determine whether such a set of integer solutions exists. When enumerating $k$, the upper bound is determined by $y < E_\text{max}$.
    4.  Each time a solution is obtained, adjust the upper bound of the denominator $M_e$ to one less than the largest denominator in the current solution.
    
    In addition, the implementation directly records the values of $\dfrac{a}{b}-\dfrac{c}{d}$ and $C-g$. The numerator and denominator of the former are stored in variables `a` and `b`, respectively, while the latter is stored as variable `d`.

??? note "Sample code"
    ```cpp
    --8<-- "docs/search/code/idastar/idastar_1.cpp"
    ```

## Exercises

-   [UVa1343 The Rotation Game](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=4089)
