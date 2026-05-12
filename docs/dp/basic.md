author: Ir1d, CBW2007, ChungZH, xhn16729, Xeonacid, tptpp, hsfzLZH1, ouuan, Marcythm, HeRaNO, greyqz, Chrogeek, partychicken, zhb2000, xyf007, Persdre, XiaoSuan250, hhc0001, ZhangZhanhaoxiang, Taoran\_01

This page introduces the basic idea of dynamic programming, as well as how to design states and transition equations. It is intended to give beginners an initial understanding of dynamic programming.

The other pages in this section introduce how to build dynamic-programming models for different types of problems, as well as optimization techniques for dynamic programming.

## Introduction

???+ note "[\[IOI1994\] Number Triangle](https://www.luogu.com.cn/problem/P1216)"
    Given a number triangle with $r$ rows ($r \leq 1000$), find a path starting from the top and ending anywhere on the bottom row such that the sum of the numbers on the path is maximized. Each step may move to the lower-left or lower-right adjacent position.
    
    ```plain
            7 
          3   8 
        8   1   0 
      2   7   4   4 
    4   5   2   6   5 
    ```
    
    In the example above, the optimal path is $7 \to 3 \to 8 \to 7 \to 5$.

The simplest brute-force idea is to try every path. Since there are $O(2^r)$ paths, this approach is unacceptable.

Notice the following fact: for an optimal path, every step decision along that path is also optimal.

For example, consider only the first four steps of the optimal path above: $7 \to 3 \to 8 \to 7$. There is no path from the top to the second number in row $4$ with a larger total weight.

For each point, there are only two possible next decisions: move to the lower-left or lower-right point, if it exists. Therefore, we only need to record the maximum weight that reaches the current point, and use this value to make the next decision and update the maximum weights of subsequent points.

This also has another benefit: we have successfully reduced the problem size by splitting one problem into several smaller problems. To obtain the optimal solution from the top to row $r$, it is enough to know the optimal-solution information from the top to row $r-1$.

There is still one issue: many subproblems overlap, and the same subproblem may be visited repeatedly, so the efficiency may still be poor. The solution is to store the answer to each subproblem and use memoization to restrict the access order, ensuring that each subproblem is visited only once.

The above is the basic idea of dynamic programming. The following sections introduce it more systematically.

## Principle of Dynamic Programming

Problems that can be solved by dynamic programming need to satisfy three conditions: optimal substructure, no aftereffect, and overlapping subproblems.

### Optimal Substructure

A problem with optimal substructure may also be suitable for a greedy method.

Make sure that all subproblems used in the optimal solution have been considered.

1.  Prove that the first component of the optimal solution is making a choice.
2.  For a given problem, among all possible first-step choices, assume that you already know which choice leads to the optimal solution. You do not care how that choice was found; you only assume that it is known.
3.  After fixing the choice that gives the optimal solution, determine which subproblems this choice creates and how to best characterize the subproblem space.
4.  Prove that, as components of the original problem's optimal solution, the solutions to all subproblems are themselves optimal. This can be shown by contradiction: if a subproblem solution used by the original solution were not optimal, then replacing it with the subproblem's optimal solution would produce a better solution to the original problem, contradicting the assumption that the original solution was optimal.

Keep the subproblem space as simple as possible, and expand it only when necessary.

Optimal substructures differ in two aspects:

1.  How many subproblems are involved in the optimal solution of the original problem.
2.  How many choices need to be considered when determining which subproblems are used in the optimal solution.

In the subproblem graph, each vertex corresponds to one subproblem, and the choices that need to be considered correspond to edges incident to subproblem vertices.

### No Aftereffect

Once a subproblem has been solved, its answer will not be affected by later decisions.

### Overlapping Subproblems

If there are many overlapping subproblems, we can store their answers and avoid repeatedly solving the same subproblems, improving efficiency.

### Basic Approach

For a problem that can be solved by dynamic programming, the usual approach is:

1.  Divide the original problem into several **stages**. Each stage corresponds to several subproblems, and the features extracted from these subproblems are called **states**.
2.  Find the possible **decisions** for each state, or equivalently the transitions between states. In mathematical language, this is the **state transition equation**.
3.  Solve the problems in each stage in order.

From a graph-theoretic point of view, we build a [directed acyclic graph](../graph/dag.md), where each state corresponds to a node and each decision corresponds to an edge between nodes. The problem is then transformed into finding a longest or shortest path in a DAG. See [DP on DAGs](./dag.md).

## Longest Common Subsequence

???+ note "Longest Common Subsequence Problem"
    Given a sequence $A$ of length $n$ and a sequence $B$ of length $m$ ($n,m \leq 5000$), find the longest sequence that is a subsequence of both $A$ and $B$.

For the definition of a subsequence, see [Subsequence](../string/basic.md). As a short example, the common subsequences of the strings `abcde` and `acde` include `a`, `c`, `d`, `e`, `ac`, `ad`, `ae`, `cd`, `ce`, `de`, `acd`, `ade`, `ace`, `cde`, and `acde`; the longest common subsequence has length 4.

Let $f(i,j)$ denote the length of the longest common subsequence when considering only the first $i$ elements of $A$ and the first $j$ elements of $B$. Finding this value is a **subproblem**. The pair $f(i,j)$ is what we call a **state**, and $f(n,m)$ is the final target state, namely the required answer.

For each $f(i,j)$, there are three decisions. If $A_i=B_j$, we may append it to the end of the common subsequence. The other two decisions are to skip $A_i$ or skip $B_j$. The transition equation is:

$$
f(i,j)=
\begin{cases}
f(i-1,j-1)+1&A_i=B_j\\
\max(f(i-1,j),f(i,j-1))&A_i\ne B_j
\end{cases}
$$

You can refer to [SourceForge's interactive LCS page](http://lcs-demo.sourceforge.net/) to better understand the implementation of LCS.

???+ example "Reference Implementation"
    === "C++"
        ```cpp
        --8<-- "docs/dp/code/basic/lcs.cpp:core"
        ```
    
    === "Python"
        ```cpp
        --8<-- "docs/dp/code/basic/lcs.py:core"
        ```

The time complexity of this approach is $O(nm)$.

This problem also has an $O\left(\dfrac{nm}{w}\right)$ algorithm[^ref1]. Interested readers can explore it on their own.

## Longest Non-decreasing Subsequence

???+ note "Longest Non-decreasing Subsequence Problem"
    Given a sequence $a$ of length $n$ ($n \leq 5000$), find the longest subsequence of $a$ such that each element is not smaller than the previous one.

### Algorithm 1

Let $f(i)$ denote the length of the longest non-decreasing subsequence ending at $a_i$. The answer is then $\max_{1 \leq i \leq n} f(i)$.

When computing $f(i)$, try appending $a_i$ after other longest non-decreasing subsequences and update the answer. This gives the transition equation $f(i)=\max_{1 \leq j < i,~a_j \leq a_i} (f(j)+1)$.

???+ example "Reference Implementation"
    === "C++"
        ```cpp
        --8<-- "docs/dp/code/basic/lis-1.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/dp/code/basic/lis-1.py:core"
        ```

It is easy to see that this algorithm has time complexity $O(n^2)$.

### Algorithm 2

When the constraint is expanded to $n \leq 10^5$, the first approach is no longer fast enough. The following is an $O(n \log n)$ approach.

Consider the previously defined state $(i,l)$, meaning that the longest non-decreasing subsequence ending at the $i$-th element has length $l$. Unlike the usual method of processing states by fixed $i$, here we directly determine whether $(i,l)$ is valid:

-   The initial state $(1,1)$ is certainly valid.
-   For any $(i,l)$, if there exists $j<i$ such that $(j,l-1)$ is valid and $a_j \le a_i$, then $(i,l)$ is valid.

Finally, it is enough to find the valid state $(i,l)$ with maximum $l$; this gives the length of the longest non-decreasing subsequence.

Let the original sequence be $a_1, \cdots, a_n$. Define an array $d$, where position $x$ stores the minimum possible last element of a non-decreasing subsequence of length $x$. Initially, the sequence is empty. Iterate $i$ from $1$ to $n$ and compute the length of the longest non-decreasing subsequence among the first $i$ elements. For the current element $a_i$:

-   If $a_i$ is greater than or equal to the last element of $d$, insert $a_i$ at the end of $d$.
    -   Explanation: if $a_i$ is greater than or equal to the last element of the current longest subsequence, then there exists a non-decreasing subsequence that can be extended by $a_i$. Not inserting it would break optimality.
-   If $a_i$ is strictly smaller than the last element of $d$, find the **first** element greater than it and replace that element with $a_i$.
    -   Explanation: directly inserting it at the end would break the monotonicity of $d$. Replacement keeps the ending element of each length as small as possible, preserving more possibilities for later elements.
    -   Optimization: since $d$ is non-decreasing, binary search can find the insertion position directly, reducing the total complexity to $O(n\log n)$ instead of the brute-force $O(n^2)$.

If the actual longest non-decreasing subsequence also needs to be output, maintain an additional array $d'_x$, representing the position of the minimum ending element among non-decreasing subsequences of length $x$; if there are several, choose any one. During maintenance, whenever $a_i$ is inserted into $d_x$, also update $d'_x$ to $i$. At the same time, record the best predecessor of $i$ as $p_i=d'_{x-1}$. Finally, start from any maximum-length state and follow the predecessor links $p_i$ backward to recover the full subsequence.

???+ example "Reference Implementation"
    === "C++"
        ```cpp
        --8<-- "docs/dp/code/basic/lis-2.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/dp/code/basic/lis-2.py:core"
        ```

The time complexity of this algorithm is $O(n\log n)$. The time complexity for outputting the answer is $O(\textit{ans})$.

???+ tip "Note"
    For the longest **increasing** subsequence problem, similarly let $d_i$ denote the minimum possible last element among all longest increasing subsequences of length $i$.
    
    Note that in step 2, if $a_i \leq d_{len}$, adjacent elements in a longest increasing subsequence cannot be equal, so we need to find the **first** element in $d$ that is **not less than** $a_i$ and replace it with $a_i$.
    
    In implementation, taking C++ as an example, replace `upper_bound` with `lower_bound`.

## References and Notes

-   [Detailed explanation of the $n\log n$ longest non-decreasing subsequence algorithm - lvmememe - CNBlogs](https://www.cnblogs.com/itlqs/p/5743114.html)

[^ref1]: [Finding the longest common subsequence with bit operations - -Wallace- - CNBlogs](https://www.cnblogs.com/-Wallace-/p/bit-lcs.html)
