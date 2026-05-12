## Introduction

RMQ is short for Range Maximum/Minimum Query, meaning range maximum or minimum query.

In the following descriptions, assume the initial array size is $n$ and the number of queries is $m$.

In the following descriptions, the default notation for time complexity is $O(A) \sim O(B)$, where $O(A)$ denotes preprocessing time complexity and $O(B)$ denotes the time complexity of a single query.

## Monotonic Stack

Since **OI Wiki** already describes this part, this article only provides a [link](../ds/monotonous-stack.md). We will not expand on it here.

Time complexity $O(m\log m) \sim O(\log n)$, space complexity $O(n)$.

## Sparse Table

Since **OI Wiki** already describes this part, this article only provides a [link](../ds/sparse-table.md). We will not expand on it here.

Time complexity $O(n\log n) \sim O(1)$, space complexity $O(n\log n)$.

## Segment Tree

Since **OI Wiki** already describes this part, this article only provides a [link](../ds/seg.md). We will not expand on it here.

Time complexity $O(n) \sim O(\log n)$, space complexity $O(n)$.

## Four Russians

Four Russians is an ST-table-based algorithm proposed by four Russian computer scientists.

The improvement that the Four Russians algorithm makes over the ST table is sequence blocking.

Specifically, divide the original array, which we call array A, into blocks of size $S$, for a total of $n/S$ blocks.

For each block, preprocess the minimum value inside the block, build an array B of length $n/S$, and preprocess array B using the ST table method.

At the same time, build an ST table for each scattered block of array A.

During a query, the query interval can be divided into at most 1 continuous block interval on array B and at most 2 continuous in-block intervals on array A. Clearly, these subproblems can be solved by range queries on ST tables.

When $S=\log n$, the preprocessing complexity is optimal: $O((n / \log n)\log n+(n / \log n)\times\log n\times\log \log n)=O(n\log \log n)$.

Time complexity $O(n\log \log n) \sim O(1)$, space complexity $O(n\log \log n)$.

Of course, because a query needs to run three ST tables, this implementation has a large constant factor.

??? note "Small Algorithmic Improvements"
    Observe that when the two endpoints of a query belong to different blocks in array A, the in-block queries on array A are prefix or suffix queries for each block.
    
    Clearly, these queries can be answered by precomputing answers in $O(n)$ time.
    
    Then during a query, we need to perform at most one ST-table query.

??? note "Some Heuristic Algorithmic Improvements"
    Since the Four Russians algorithm is based on ST tables, and algorithm competitions usually do not require extremely high time-complexity precision, Four Russians can usually be replaced by an ST table and is not very practical in algorithm competitions. Here is a more practical Four Russians improvement for competitions.
    
    Set the block size to $\sqrt n$, then preprocess the prefix and suffix RMQ of each block, and brute-force preprocess the RMQ between any continuous whole blocks. The time complexity is $O(n)$.
    
    For a query whose left and right endpoints are not in the same block, we can directly obtain in $O(1)$ the suffix RMQ of the block containing the left endpoint, the RMQ of the continuous whole blocks between the left and right endpoints, and the prefix RMQ of the block containing the right endpoint. The answer is the extremum among these three values.
    
    For a query whose left and right endpoints are in the same block, we can brute-force the RMQ between the two points. The time complexity is $O(\sqrt n)$, but the expected probability that the two endpoints of a single query are in the same block is $O(\frac{\sqrt n}{n})$, so the expected time complexity of this method is $O(n)$.
    
    In algorithm competitions, we do not need to worry too much about setters hacking this algorithm, because we can randomly fine-tune the block size around $\sqrt n$, largely avoiding worst cases constructed for a specific block size. Also, if the setter wants to hack this method, brute force may also pass.
    
    This is an algorithm whose expected time complexity reaches the lower bound and whose implementation difficulty and constant factors are both small, so it is quite practical in algorithm competitions.
    
    The above method refers to the solution for [P3793 Yuno Saves Grandpa](https://www.luogu.com.cn/problem/P3793).

## Plus-Minus 1 RMQ

If a sequence has adjacent elements differing by 1, RMQ on this sequence is called plus-minus 1 RMQ. Based on this property, the Four Russians algorithm can be improved to achieve time complexity $O(n) \sim O(1)$ and space complexity $O(n)$.

Since the bottleneck of the Four Russians algorithm is the in-block RMQ problem, we focus on optimizing in-block RMQ.

Because the difference between two adjacent numbers is $\pm 1$, when the left endpoint value is fixed, the number of possible right-side sequences of length at most $\log n$ is $\sum_{i=1}^{\log n} 2^{i-1}$, and this expression is clearly at most $n$.

This suggests that we can preprocess the value of minimum value minus first element for all at most $n$ cases.

During preprocessing, compute the differences between adjacent numbers inside each block and represent them in binary.

During a query, find the binary representation corresponding to the query interval, then look up the answer in the table.

This optimizes Four Russians preprocessing time complexity to $O(n)$.

## Application of Cartesian Trees to RMQ

If you are not familiar with Cartesian trees, please see [Cartesian Tree](../ds/cartesian-tree.md).

It is not hard to see that the min/max between two points in the original sequence equals the weight of the LCA of the two corresponding points in the Cartesian tree. Using this, we can solve RMQ by solving LCA between two tree nodes with $O(n) \sim O(1)$. Tree LCA with $O(n) \sim O(1)$ has already been described in [LCA - Standard RMQ](../graph/lca.md#标准-rmq), so it is not expanded here.

In summary, applying Cartesian trees to RMQ means transforming an ordinary RMQ problem into an LCA problem, then into a plus-minus 1 RMQ problem, with time complexity $O(n) \sim O(1)$. Of course, because there are many transformation steps, $O(n) \sim O(1)$ RMQ has a large constant factor.

If the data is random, we can also brute-force search on the Cartesian tree. The expected time complexity is then $O(n) \sim O(\log n)$, and in practice this algorithm often has a very small constant factor.

### Example [Luogu P3865 Template Sparse Table](https://www.luogu.com.cn/problem/P3865)

## Bitmask-Based Linear RMQ Algorithm

### Implicit Requirement

-   The sequence length $n$ satisfies $\log_2{n} \leq 64$.

### Prerequisites

-   [Sparse Table](../ds/sparse-table.md)

-   Basic bit operations

-   Prefix and suffix extrema

### Algorithm Principle

Divide the original sequence $A[1\cdots n]$ into blocks of length $O(\log_2{n})$, for a total of $O(\frac{n}{\log_2{n}})$ blocks.

> It is said that setting the block length to $1.5\times \log_2{n}$ gives a smaller constant factor.

Record the maximum value of each block and maintain inter-block maximum values with an ST table. The complexity is $O(n)$.

Record the prefix and suffix maximum value for every position in the block, $Pre[1\cdots n], Sub[1\cdots n]$ ($Pre[i]$ is the maximum value from $A[i]$ to the beginning of its block). The complexity is $O(n)$.

If the queried $l,r$ are in two different blocks, denote them as blocks $bl,br$. The maximum value is the maximum among the inter-block maximum over blocks $[bl+1,br-1]$, $Sub[l]$, and $Pre[r]$.

The remaining question is what to do when $l,r$ are in the same block.

Insert $A[1\cdots r]$ into a monotonic stack in order, recording indices and values, with values decreasing from stack bottom to stack top. Then the maximum value in $A[l,r]$ is the value of the first stack element from the bottom whose index $p \geq l$.

Since $A[p]$ is the maximum value in $A[l,r]$, when inserting $A[p]$, all elements in $A[l\cdots p-1]$ are popped, and when inserting $A[p+1\cdots r]$, $A[p]$ cannot be popped.

If we use $0/1$ to indicate whether each number is in the stack, we can store the state as a bitmask integer. Then $p$ is the position after the $l$-th bit of the first $1$.

Since the block size is $O(\log_2{n})$, it is at most $64$ bits, so it can be stored in one integer (this is the reason for the implicit condition).

??? note "Reference Code"
    ```cpp
    #include <algorithm>
    #include <cmath>
    #include <cstdio>
    
    constexpr int MAXN = 1e5 + 5;
    constexpr int MAXM = 20;
    
    struct RMQ {
      int N, A[MAXN];
      int blockSize;
      int S[MAXN][MAXM], Pow[MAXM], Log[MAXN];
      int Belong[MAXN], Pos[MAXN];
      int Pre[MAXN], Sub[MAXN];
      int F[MAXN];
    
      void buildST() {
        int cur = 0, id = 1;
        Pos[0] = -1;
        for (int i = 1; i <= N; ++i) {
          S[id][0] = std::max(S[id][0], A[i]);
          Belong[i] = id;
          if (Belong[i - 1] != Belong[i])
            Pos[i] = 0;
          else
            Pos[i] = Pos[i - 1] + 1;
          if (++cur == blockSize) {
            cur = 0;
            ++id;
          }
        }
        if (N % blockSize == 0) --id;
        Pow[0] = 1;
        for (int i = 1; i < MAXM; ++i) Pow[i] = Pow[i - 1] * 2;
        for (int i = 2; i <= id; ++i) Log[i] = Log[i / 2] + 1;
        for (int i = 1; i <= Log[id]; ++i) {
          for (int j = 1; j + Pow[i] - 1 <= id; ++j) {
            S[j][i] = std::max(S[j][i - 1], S[j + Pow[i - 1]][i - 1]);
          }
        }
      }
    
      void buildSubPre() {
        for (int i = 1; i <= N; ++i) {
          if (Belong[i] != Belong[i - 1])
            Pre[i] = A[i];
          else
            Pre[i] = std::max(Pre[i - 1], A[i]);
        }
        for (int i = N; i >= 1; --i) {
          if (Belong[i] != Belong[i + 1])
            Sub[i] = A[i];
          else
            Sub[i] = std::max(Sub[i + 1], A[i]);
        }
      }
    
      void buildBlock() {
        static int S[MAXN], top;
        for (int i = 1; i <= N; ++i) {
          if (Belong[i] != Belong[i - 1])
            top = 0;
          else
            F[i] = F[i - 1];
          while (top > 0 && A[S[top]] <= A[i]) F[i] &= ~(1 << Pos[S[top--]]);
          S[++top] = i;
          F[i] |= (1 << Pos[i]);
        }
      }
    
      void init() {
        for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
        blockSize = log2(N) * 1.5;
        buildST();
        buildSubPre();
        buildBlock();
      }
    
      int queryMax(int l, int r) {
        int bl = Belong[l], br = Belong[r];
        if (bl != br) {
          int ans1 = 0;
          if (br - bl > 1) {
            int p = Log[br - bl - 1];
            ans1 = std::max(S[bl + 1][p], S[br - Pow[p]][p]);
          }
          int ans2 = std::max(Sub[l], Pre[r]);
          return std::max(ans1, ans2);
        } else {
          return A[l + __builtin_ctz(F[r] >> Pos[l])];
        }
      }
    } R;
    
    int M;
    
    int main() {
      scanf("%d%d", &R.N, &M);
      R.init();
      for (int i = 0, l, r; i < M; ++i) {
        scanf("%d%d", &l, &r);
        printf("%d\n", R.queryMax(l, r));
      }
      return 0;
    }
    ```

### Exercises

[\[BJOI 2020\] Seal](https://loj.ac/problem/3298): SAM+RMQ
