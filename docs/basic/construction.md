author: leoleoasd, yzxoi, Estrella-Explore

This page briefly introduces construction problems.

## Introduction

Construction problems are a common type of problem in competitions.

In terms of form, the answers to such problems often have some regularity, making it possible to find answers relatively easily even when the problem scale grows rapidly.

This requires thinking about how the growth of problem scale affects the answer, and whether this effect can be generalized. For example, when designing a dynamic programming method, consider what impact the transition from one state to subsequent states will have.

## Characteristics

A very notable characteristic of construction problems is high flexibility, meaning there may be many ways to construct a solution for a given problem, but there will be a relatively simple construction method that satisfies the requirements. It seems to relax the requirements and make the problem easier, but often, it is precisely this high flexibility that leads to having no clear approach and not knowing where to start.

Another characteristic of construction problems is flexible form and diverse variations. There is no general solution or pattern that can solve all construction problems, and it is even difficult to find commonality in the problem-solving approach.

## Example Problems

Below, some example problems are listed to help readers understand the ideas behind construction problems and provide inspiration for approaches. It is recommended to think deeply before looking at the solution, and everyone is welcome to share interesting construction problems.

### Example 1

???+ note "[Codeforces Round #384 (Div. 2) C.Vladik and fractions](http://codeforces.com/problemset/problem/743/C)"
    Construct a set of $x,y,z$ such that for a given $n$, $\dfrac{1}{x}+\dfrac{1}{y}+\dfrac{1}{z}=\dfrac{2}{n}$

??? note "Solution Idea"
    The construction method can be seen from sample 2.
    
    Obviously $n,n+1,n(n+1)$ is a valid solution. Special case: when $n=1$, there is no solution, because at this time $n+1$ equals $n(n+1)$.
    
    As for how the construction idea came about, it is probably a matter of observing the samples plus a bit of number sense. This problem is not difficult for those with strong mathematical intuition.

### Example 2

???+ note "[Luogu P3599 Koishi Loves Construction](https://www.luogu.com.cn/problem/P3599)"
    Task1: Try to determine if it is possible to construct and construct a permutation of length $n$ of $1\dots n$, such that its $n$ prefix sums are all distinct under modulo $n$
    
    Task2: Try to determine if it is possible to construct and construct a permutation of length $n$ of $1\dots n$, such that its $n$ prefix products are all distinct under modulo $n$

??? note "Solution Idea"
    For task1:
    
    When $n$ is odd, it is impossible to construct a valid solution;
    
    When $n$ is even, a sequence of the form $n,1,n-2,3,\cdots$ can be constructed.
    
    First, we can find that $n$ must appear at the first position of the sequence, otherwise the two prefix sums before and after $n$ will inevitably fall into the awkward situation of being equal under modulo;
    
    Then, consider how to construct the entire sequence:
    
    Consider obtaining the original sequence by constructing the prefix sum sequence. It can be found that the differences between pairs of prefix sums cannot be equal under modulo, because the difference sequence of the prefix sum sequence corresponds to the original permutation.
    
    Therefore, we try to construct the sequence with the prefix sum sequence under modulo being
    
    $$
    0,1,-1,2,-2,\cdots
    $$
    
    It is not difficult to find that it perfectly satisfies all constraints.
    
    For task2:
    
    When $n$ is a composite number other than $4$, it is impossible to construct a valid solution
    
    When $n$ is a prime number or $4$, a sequence of the form $1,\dfrac{2}{1},\dfrac{3}{2},\cdots,\dfrac{n-1}{n-2},n$ can be constructed
    
    First consider when there is a solution:
    
    Obviously, when $n$ is a composite number, there is no solution. Because for a composite number, there exist two numbers $p,q$ smaller than it such that $p\times q \equiv 0 \pmod n$, such as $(3\times6)\%9=0$. Then, after both $p$ and $q$ have appeared, the prefix products of the sequence will always be $0$, so there is no solution for composite numbers. Special case: we can find that $4=2\times 2$, there is no $p,q$ satisfying the condition, so there is a valid solution.
    
    Consider how to construct this sequence:
    
    Using the same approach as task1, we find that $1$ must appear at the first position of the sequence, otherwise the two prefix products before and after $1$ must be equal; and $n$ must appear at the last position of the sequence, because all prefix products after $n$ appears are $0$ under modulo. After analyzing the sample cases given in the problem, we find that all samples have a valid solution where the prefix products under modulo are $1,2,3,\cdots,n$, so we can construct the sequence described above to satisfy this condition. Then we only need to prove these $n$ numbers are all different.
    
    We find that these numbers are all the inverses of $1\cdots n-2$ plus $1$, so they are all different. This problem is solved.

### Example 3

???+ note "[AtCoder Grand Contest 032 B](https://atcoder.jp/contests/agc032/tasks/agc032_b)"
    Given an integer $N$, construct an undirected graph with $N$ nodes. Let node numbers be $1\ldots N$, and it must satisfy the following conditions:
    
    -   This is a simple connected graph.
    -   There exists an integer $S$ such that for any node, the sum of the indices of its adjacent nodes is $S$.
    
    The input data is guaranteed to have a solution.

??? note "Solution Idea"
    By analyzing the cases for $n=3,4,5$, we can find a construction approach.
    
    Construct a complete $k$-partite graph, ensuring that these $k$ parts have equal sums. Then $S$ is equal for every node, being $\dfrac{(k-1)\sum_{i=1}^{n}i}{k}$.
    
    If $n$ is even, we can pair them front and back, i.e., $\{1,n\},\{2,n-1\}\cdots$
    
    If $n$ is odd, we can take out $n$ as a single group, and pair the remaining $n-1$ nodes in pairs, i.e., $\{n\},\{1,n-1\},\{2,n-2\}\cdots$
    
    The connectivity of the graph constructed this way is easy to prove when $n\ge 3$, and will not be elaborated here.
    
    This problem is solved.

### Example 4

???+ note "[BZOJ 4971「Lydsy1708 Monthly Contest」Backpack in Memory](https://vjudge.net/problem/BZOJ-4971)"
    After a day of hard work, Little Q fell into a dream. In his mind, the scene of learning the 0-1 backpack problem when he just entered university appeared. At that time, as a freshman, Little Q solved a simple 0-1 backpack problem. The problem is as follows:
    
    Given $n$ items, with volumes $v_1,v_2,…,v_n$ respectively, please calculate the number of ways to select some items (or select none) such that the total volume is exactly $w$. Since the answer may be very large, you only need to output the answer modulo $P$.
    
    Due to long-term late-night problem-solving, he only saw $w$ and $P$ in the sample input, and the sample output is $k$. He couldn't see how many items there were or what the volume of each item was. Until he woke up, Little Q still couldn't see $n$ and $v$. Please write a program to help Little Q recall the original sample input.

??? note "Solution Idea"
    This is one of the construction problems with the highest flexibility. This leads to having no clue and being difficult to start.
    
    First, it is not difficult to find that the modulus is fake. Since we can construct data freely, we can always make the number of solutions not exceed the modulus.
    
    Through some strange approach, we think of constructing $n$ small items with cost $1$ and several large items with cost greater than $\dfrac{w}{2}$.
    
    Since only one large item can be taken, the contribution of each large item with cost $x$ to the number of solutions is $\dbinom{n}{w-x}$.
    
    Let $f_{i,j}$ represent the minimum number of large items when there are $i$ ones and the number of solutions is $j$.
    
    Use DP to precompute $f$. Through calculation, it can be seen that only all values for $i\le 20$ need to be precomputed.
    
    This problem is solved.