**Counting DP** is a memoized-search method similar to DP. It differs somewhat from DP in the narrow sense, which usually refers to optimization problems, and is used to solve counting and summation problems.

## Basics

### Basic Idea

A counting problem usually asks for the size of a set $S$. In OI, the size of $S$ may reach $\Theta(n^n)$ or even $\Theta(2^{n!})$, where $n$ is the problem size. Of course, the answer is often taken modulo some fixed number. Therefore, we cannot enumerate the elements of $S$ one by one.

If we can partition $S$ into several disjoint subsets, then the number of elements in $S$ is the sum of the numbers of elements in those parts. If counting these subsets is similar to the original problem, we can solve it with a dynamic-programming-like method.

### Example Problem

???+ note "Example Problem"
    Given a positive integer $n$, find the number of ways to split $n$ into the sum of $k$ positive integers, where different orders are considered different partitions.

Let $S_{n,k}$ be the set of positive-integer tuples of the form $(a_1, \dots, a_k)$ such that $a_1 + \dots + a_k = n$. If $a_k$ is fixed, then because $a_1 + a_2 + \dots + a_{k-1} + a_k = n$, we have $a_1 + a_2 + \dots + a_{k-1} = n - a_k$. By the definition of $S_{n,k}$, $(a_1, a_2, \dots, a_{k-1}) \in S_{n-a_k,k-1}$.

Since $a_1,a_2,\dots,a_k$ are positive integers, the range of $a_k$ is $[1,n-k+1]\cap\mathbb Z$. Therefore, $S_{n,k}$ can be partitioned according to $a_k$ into $n-k+1$ subsets. When $a_k=i$, the subset is:

$$
\{(L, i) \mid L \in S_{n-i,k-1}\}.
$$

The number of elements in this subset is clearly $|S_{n-i,k-1}|$. Since different values of $i$ produce pairwise-disjoint subsets, we have:

$$
|S_{n,k}| = \sum_{i=1}^{n-k+1} |S_{n-i,k-1}|.
$$

Thus we can process it with a DP-like method. Let $f_{n,k}=|S_{n,k}|$. The transition equation is:

$$
f_{n,k} = \sum_{i=1}^{n-k+1} f_{n-i,k-1}.
$$

This can then be solved with dynamic programming.

### Similarities and Differences Compared with Optimization DP

Counting DP and optimization DP both compute a value over a range $\Omega$: a size or an optimum. This value is obtained by processing all elements of $\Omega$ once and then aggregating the processed values.

For example, in the 0-1 knapsack problem, the elements of $\Omega$ are all subsets of items in the knapsack. For one scheme $S\in\Omega$, we process $S$ and obtain $w(S)$, the total value of the items in $S$. We then take the maximum over all processed values to obtain the answer.

For a counting problem, the elements of $\Omega$ are the elements of the set $S$ whose size is being counted. The processing maps every element of $S$ to $1$, then sums all these $1$s. Since every element of $S$ corresponds to exactly one $1$, the resulting value is the number of elements in $S$.

When the aggregation operation is maximum or minimum, we can divide $\Omega$ into any number of parts as long as their union is $\Omega$; the parts do not need to be disjoint. Counting problems do not satisfy this property, so we need to divide $\Omega$ into pairwise-disjoint parts. This is the difference from optimization DP.

## Example Problem

???+ note "Example Problem"
    Given a positive integer $n$, find the number of ways to split $n$ into the sum of any number of positive integers, where different orders are considered the **same** partition.

### Solution 1

The elements of the set to be counted are positive-integer multisets whose sum is $n$. However, deriving transitions directly from this is clearly inconvenient.

If a multiset $T$ contains only positive integers $\le M$, and the sum of all elements in $T$ is $n$, write $T\in S_{n,M}$. Consider how many times $M$ appears. It may appear $k\in\left[0,\left\lfloor \dfrac nM \right\rfloor\right]\cap\mathbb Z$ times. Then it can transition to $S_{n-kM,M-1}$. Summing over all $k$ gives a solution with complexity $\Theta(n^2\log n)$; the $\log$ comes from the harmonic series caused by the range of $k$.

This is still not good enough. Consider the following example:

$$
\begin{aligned}
f_{8, 3} &= {\color{red}f_{8, 2} + f_{5, 2} + f_{2, 2}} \\
f_{9, 3} &= {\color{blue}f_{9, 2} + f_{6, 2} + f_{3, 2} + f_{0, 2}} \\
f_{10, 3} &= {\color{green}f_{10, 2} + f_{7, 2} + f_{4, 2} + f_{1, 2}}\\
f_{11, 3} &= f_{11, 2} + {\color{red}f_{8, 2} + f_{5, 2} + f_{2, 2}}\\
f_{12, 3} &= f_{12, 2} + {\color{blue}f_{9, 2} + f_{6, 2} + f_{3, 2} + f_{0, 2}}\\
f_{13, 3} &= f_{13, 2} + {\color{green}f_{10, 2} + f_{7, 2} + f_{4, 2} + f_{1, 2}}\\
\end{aligned}
$$

By substitution, $f_{11,3}=f_{11,2}+f_{8,3}$, $f_{12,3}=f_{12,2}+f_{9,3}$, and $f_{13,3}=f_{13,2}+f_{10,3}$. Similarly, we get a general transition equation:

$$
f_{n, M} = f_{n, M - 1} +
\begin{cases}
f_{n - M, M} & n \ge M, \\
0 & \text{otherwise}.
\end{cases}
$$

The time complexity is now $\Theta(n^2)$.

### Solution 2

Observe that any multiset $T$ of positive integers can be obtained through two operations: increment every element of $T$ by one, or add an element with value $1$ to $T$. Different operation sequences produce different results.

This transforms transitions on $T$ into transitions on operation sequences. Consider operation sequences that partition $n$ into $m$ numbers, denoted by $B_{n,m}$. Look at the last operation. If it is operation 1, it does not increase the number of elements, but $\sum T$ increases by $m$. To make the final $\sum T=n$, the previous $T$, denoted $T'$, must have sum $n-m$. Thus $B_{n,m}\to B_{n-m,m}$. If it is operation 2, it increases the number of elements by one and $\sum T$ by $1$, so $B_{n,m}\to B_{n-1,m-1}$.

This approach still has time complexity $\Theta(n^2)$.

### Solution 3

Split $T$ into two parts: $T_1$, containing elements greater than $\sqrt n$, and $T_2$, containing elements at most $\sqrt n$. $T_2$ can be computed with Solution 1. The number of possible $T_1$ can be computed by slightly modifying Solution 2: replace the two operations with incrementing every element of $T_1$, and adding an element with value $\lfloor\sqrt n\rfloor+1$ to $T_1$. The transition equation is easy to write down.

Split $n$ into two parts $A$ and $B$. Enumerating one part determines the other. Compute the number of $T_1$ with $\sum T_1=A$ and the number of $T_2$ with $\sum T_2=B$, multiply them, and sum over all $A$ to obtain the final result.

When computing the number of $T_1$, we have $M\le\sqrt n$, so using Solution 1 takes $\Theta(n^{3/2})$ time. Similarly, when computing the number of $T_2$, we have $|T_2|\le \dfrac{\sum T_2}{\sqrt n}\le \dfrac n{\sqrt n}=\sqrt n$, so using Solution 2 also takes $\Theta(n^{3/2})$ time. Therefore, the total time complexity is $\Theta(n^{3/2})$.
