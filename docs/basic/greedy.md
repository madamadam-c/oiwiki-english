This page briefly introduces greedy algorithms.

## Introduction

Greedy algorithm (English: greedy algorithm) is a way to simulate with a computer a "greedy" person making decisions. This person is very greedy, always choosing the optimal operation according to some metric at each step. And he is short-sighted, only looking at the present, not considering the impact it may have in the future.

As can be imagined, greedy does not always obtain the optimal solution, so when using greedy algorithm, one must usually ensure one can prove its correctness.

## Explanation

### Scope of Application

Greedy algorithm is particularly effective in problems with optimal substructure. Optimal substructure means the problem can be decomposed into subproblems to solve, and the optimal solution of subproblems can be extrapolated to the optimal solution of the final problem.[^ref1]

### Proof

There are two proof methods for greedy algorithms: proof by contradiction and mathematical induction. Generally, a problem will only use one of these methods for proof.

1.  Proof by contradiction: If swapping any two elements/adjacent elements in the solution does not make the answer better, then it can be concluded that the current solution is already optimal.
2.  Mathematical induction: First calculate the optimal solution for edge cases (for example, $n = 1$) as $F_1$, then prove: for each $n$, $F_{n+1}$ can be derived from $F_n$.

## Key Points

### Common Problem Types

In problems at the improvement level and below, the two most common greedy approaches are:

-   "We sort XXX according to some order, then select in a certain order (for example, from small to large)."
-   "We always take the largest/smallest thing from XXX, and update XXX." (Sometimes "the largest/smallest thing in XXX" can be optimized, such as using a priority queue to maintain)

The difference between the two is that one is offline, processing then selecting; the other is online, processing while selecting.

### Sorting Solution

A common situation for the sorting method is inputting an array containing a few (generally one or two) weight values, and using sorting then traversal simulation to calculate the optimal value.

### Regret Solution

The idea is to accept the current choice whether it is optimal or not, then compare. If after making the choice it is no longer optimal, regret, discard this choice; otherwise, formally accept it. Repeat this process.

## Differences

### Difference from Dynamic Programming

The difference between greedy algorithm and dynamic programming is that it makes a choice for each subproblem and cannot go back. Dynamic programming saves previous computation results and makes selections based on previous results, having the ability to go back.

## Example Problem Explanation

### Example of Adjacent Exchange Method

???+ note "[NOIP 2012 King's Game](https://www.luogu.com.cn/problem/P1080)"
    It is the National Day of Country H. The king invites n ministers to play a prize game. First, he asks each minister to write an integer on their left and right hand. The king also writes an integer on his left and right hand. Then, these n ministers line up, with the king at the very front of the queue. After lining up, all ministers receive some gold coins from the king. The number of gold coins each minister receives is: the product of all the numbers on the left hands of everyone in front of that minister, divided by the number on their own right hand, floored.
    
    The king does not want any minister to receive too many rewards, so he asks you to help rearrange the order of the queue, so that the minister who receives the most reward gets as few rewards as possible. Note: the king's position is always at the very front of the queue.

??? note "Solution Idea"
    Let $a_i, b_i$ be the numbers on the left and right hand of the $i$-th minister after sorting. Consider deriving the greedy strategy using the adjacent exchange method.
    
    Let $s$ be the product of $a_i$ of all ministers in front of the $i$-th minister. Then the reward for the $i$-th minister is $\dfrac{s} {b_i}$, and the reward for the $i+1$-th minister is $\dfrac{s \cdot a_i} {b_{i+1}}$.
    
    If we swap the $i$-th minister with the $i+1$-th minister, then the reward for the $i$-th minister becomes $\dfrac{s} {b_{i+1}}$, and the reward for the $i+1$-th minister becomes $\dfrac{s \cdot a_{i+1}} {b_i}$.
    
    The swap is better if and only if
    
    $$
    \max \left(\dfrac{s} {b_i}, \dfrac{s \cdot a_i} {b_{i+1}}\right)  < \max \left(\dfrac{s} {b_{i+1}}, \dfrac{s \cdot a_{i+1}} {b_i}\right)
    $$
    
    Extract the common $s$ and simplify to get
    
    $$
    \max \left(\dfrac{1} {b_i}, \dfrac{a_i} {b_{i+1}}\right)  < \max \left(\dfrac{1} {b_{i+1}}, \dfrac{a_{i+1}} {b_i}\right)
    $$
    
    Then convert fractions to integers to get
    
    $$
    \max (b_{i+1}, a_i\cdot b_i)  < \max (b_i, a_{i+1}\cdot b_{i+1})
    $$
    
    In implementation, we use a struct to store the two input numbers and overload the operator:
    
    ```cpp
    struct uv {
      int a, b;
    
      bool operator<(const uv &x) const {
        return max(x.b, a * b) < max(b, x.a * x.b);
      }
    };
    ```

### Example of Regret Method

???+ note "[「USACO09OPEN」Work Scheduling](https://www.luogu.com.cn/problem/P2949)"
    John's workday starts at time $0$ and has $10^9$ time units. At any time unit, he can choose to complete any of $N (1 \leq N \leq 10^5)$ jobs numbered $1$ to $N$. Job $i$ has a deadline $D_i (1 \leq D_i \leq 10^9)$ and a profit $P_i (1 \leq P_i \leq 10^9)$. Given the job profits and deadlines, find the maximum profit John can obtain.

??? note "Solution Idea"
    1.  First assume we do every job, sort all jobs by deadline and add them to the queue;
    2.  When determining whether to do the $i$-th job or not, if its deadline meets the condition, compare it with the job with the smallest profit in the queue. If the $i$-th job has higher profit (regret), then `ans += a[i].p - q.top()`. Use a priority queue (min-heap) to maintain the smallest element at the front of the queue.
    3.  `a[i].d<=q.size()` can be understood as: from 0 to `a[i].d`, only `a[i].d` tasks can be done. And if `q.size()>=a[i].d`, it means completing `q.size()` tasks takes time greater than or equal to `a[i].d` time. So when the $i$-th task has relatively high profit, the smallest task should be replaced out of the priority queue.

??? note "Reference Code"
    === "C++"
        ```cpp
        --8<-- "docs/basic/code/greedy/greedy_1.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/basic/code/greedy/greedy_1.py"
        ```

??? note "Complexity Analysis"
    -   Space Complexity: When input is $n$ tasks, using $n$ array elements for $a$, the priority queue may store $n$ elements in the worst case, so the space complexity is $O(n)$.
    -   Time Complexity: The time complexity of `std::sort` is $O(n\log n)$, and maintaining the priority queue has time complexity $O(n\log n)$. In summary, the time complexity is $O(n\log n)$.

## Practice Problems

-   [P1209[USACO1.3] Barn Repair - Luogu](https://www.luogu.com.cn/problem/P1209)
-   [P2123 Queen's Game - Luogu](https://www.luogu.com.cn/problem/P2123)
-   [Problems tagged greedy on LeetCode](https://leetcode.com/tag/greedy/)

## References and Notes

[^ref1]: [Greedy algorithm - Wikipedia, the free encyclopedia](https://en.wikipedia.org/wiki/Greedy_algorithm)