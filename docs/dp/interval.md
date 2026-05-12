## Definition

Interval dynamic programming is an extension of linear dynamic programming. When the problem is divided into stages, it depends heavily on the order in which elements appear in each stage and on which elements from the previous stage are merged.

Let the state $f(i,j)$ denote the maximum value obtainable by merging all elements from index $i$ to index $j$. Then $f(i,j)=\max\{f(i,k)+f(k+1,j)+cost\}$, where $cost$ is the value obtained by merging the two groups of elements.

## Properties

Interval DP has the following characteristics:

**Merging**: two or more parts are combined, though the process can also be considered in reverse.

**Structure**: the problem can be decomposed into parts that can be pairwise merged.

**Solution**: define an optimal value for the whole problem, enumerate the merge point, split the problem into left and right parts, and finally merge the optimal values of those two parts to obtain the optimal value of the original problem.

## Explanation

### Example Problem

???+ note "[NOI1995 Stone Merging](https://loj.ac/problem/10147)"
    Problem summary: there are $n$ numbers $a_1,a_2,\dots,a_n$ arranged on a ring. Perform $n-1$ merge operations. Each operation merges two adjacent piles into one pile and earns a score equal to the total number of stones in the new pile. Maximize the total score.

First consider the case where the stones are on a chain instead of a ring.

Let $f(i,j)$ denote the maximum score for merging all stones in the interval $[i,j]$ into one pile.

The **state transition equation** is $f(i,j)=\max\{f(i,k)+f(k+1,j)+\sum_{t=i}^{j} a_t \}~(i\le k<j)$.

Let $sum_i$ denote the prefix sum of array $a$. The transition equation becomes $f(i,j)=\max\{f(i,k)+f(k+1,j)+sum_j-sum_{i-1} \}$.

### How to Perform State Transitions

To compute $f(i,j)$, we need the values of all $f(i,k)$ and $f(k+1,j)$. Both contain fewer elements than $f(i,j)$, so we use $len=j-i+1$ as the DP stage. First enumerate $len$ from small to large, then enumerate $i$, compute $j$ from $len$ and $i$, and finally enumerate $k$. The time complexity is $O(n^3)$.

### How to Handle the Ring

In the problem, the stones form a ring rather than a chain. What should we do?

**Method 1**: Since the stones form a ring, enumerate the position where the ring is cut and convert it into a chain. This requires enumerating $n$ cuts, so the final time complexity is $O(n^4)$.

**Method 2**: Duplicate the chain to length $2\times n$, where the $i$-th pile is the same as the $(n+i)$-th pile. After running dynamic programming, take the best among $f(1,n),f(2,n+1),\dots,f(n,2n-1)$ as the final answer. The time complexity is $O(n^3)$.

## Implementation

=== "C++"
    ```cpp
    for (len = 2; len <= n; len++)
      for (i = 1; i <= 2 * n - len; i++) {
        int j = len + i - 1;
        for (k = i; k < j; k++)
          f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j] + sum[j] - sum[i - 1]);
      }
    ```

=== "Python"
    ```python
    for len in range(2, n + 1):
        for i in range(1, 2 * n - len + 1):
            j = len + i - 1
            for k in range(i, j):
                f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j] + sum[j] - sum[i - 1])
    ```

## Practice Problems

[NOIP 2006 Energy Necklace](https://www.luogu.com.cn/problem/P1063)

[NOIP 2007 Matrix Number Game](https://www.luogu.com.cn/problem/P1005)

[IOI2000 Post Office](https://www.luogu.com.cn/problem/P4767)
