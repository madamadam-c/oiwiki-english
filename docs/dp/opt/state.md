author: Marcythm, partychicken, Xeonacid, hhc0001

## Overview

When optimizing DP, we do not have to optimize only the transition process. Sometimes we can also start from the state definition and reduce complexity by changing how states are designed.

The difficult part is that most optimizations of this kind are not general: they usually cannot be mechanically applied to many different problems. Therefore, the following sections use concrete examples to provide ideas and intuition that may help readers.

## Example 1

???+ note "Problem Statement"
    Given two strings $A,B$ of lengths $n,m$, respectively, containing only lowercase letters, find the longest common subsequence of $A$ and $B$. $(n\le 10^6,m\le 10^3)$

### Naive Solution

At first glance, this is just a template problem.

Define state $f_{i,j}$ as the LCS length between the first $i$ characters of $A$ and the first $j$ characters of $B$. Then:

$$
f_{i,j}=
\begin{cases}
\max(f_{i-1,j},f_{i,j-1}) & ,A_i \neq B_j \\
f_{i-1,j-1}+1 & ,A_i = B_j 
\end{cases}
$$

This approach has time complexity $O(nm)$ and cannot pass this problem.

### Better Solution

Think more carefully: the final answer cannot exceed $m$.

Think again: LCS has a greedy property.

Change the state definition. Let $f_{i,j}$ be the shortest prefix length of $A$ such that its LCS with the first $i$ characters of $B$ has length $j$. In other words, swap the answer of the naive method with the first dimension of the state.

By preprocessing, for every position of $A$, the next occurrence position of each of `a,b,\cdots,z` can be queried in $O(1)$, allowing forward transitions.

The complexity is $O(m^2+26n)$, which can pass this problem.

## Example 2

???+ note "Problem Statement"
    Given an unweighted directed graph with $n$ vertices, determine whether it has a Hamiltonian cycle. $(2\le n\le 20)$

### Naive Solution

Seeing the constraints, consider bitmask DP.

Let $f_{s,i}$ denote whether vertex $i$ can be reached from vertex $1$ by visiting only vertices in set $s$. Let $g$ be the adjacency matrix of the original graph. Then:

$$
f_{s, i} = \bigvee_{j\in s, j\neq i}f_{s \setminus \{i\}, j}\wedge g_{j, i} \left(i\in s\right)
$$

The time complexity is $O(n^2\times2^n)$. With a careful implementation it may pass, but it is not elegant.

### Better Solution

In the state design above, each DP value represents only one `bool`, which feels wasteful.

For each state $s$, compress $f_{s,1},f_{s,2},\dots,f_{s,n}$ into one `int`. After similarly compressing the adjacency matrix, transitions can be done in $O(1)$.

The time complexity is $O(n^2/w\times2^n)$, where $w$ is the number of bits in an `int`, and this can pass the problem.

## Example 3

???+ note "Problem Statement"
    A standard knapsack problem. Let $n$ be the number of items, $m$ the knapsack capacity, and $v_i,w_i$ the volume and value of the $i$-th item. $1\le n\le10^3$, $1\le m,v_i\le\color{red}{10^{18}}$, and $1\le\sum w_i\le10^3$.

### Naive Solution

This is a template knapsack problem.

Define state $f_{i,j}$ as the maximum total value after considering the first $i$ items and currently using capacity $j$ in the knapsack.

It is easy to get $f_{i,j}=\max(f_{i-1,j},f_{i-1,j-v_i}+w_i)$.

Since $v_i\le10^{18}$, this cannot pass the problem.

### Better Solution

Swap the answer with the second dimension of the state. Let $f_{i,j}$ be the minimum total volume after considering the first $i$ items and having total item **value $j$** in the knapsack.

Similarly, $f_{i,j}=\min(f_{i-1,j},f_{i-1,j-w_i}+v_i)$.

Note that after changing the second dimension of the state, the transition must also be changed accordingly.

The time complexity is $O(n\sum w_i)$, which can pass this problem.
