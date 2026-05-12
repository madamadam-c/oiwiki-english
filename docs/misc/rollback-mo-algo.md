author: StudyingFather, Backl1ght, countercurrent-time, Ir1d, greyqz, MicDZ, ouuan, YOYO-UIAT

## Introduction

In some problems, when transferring intervals, either insertion or deletion may be impossible to implement. If only insertion is impossible or only deletion is impossible, rollback Mo's algorithm can solve the problem in $O(n \sqrt m)$ time. The core idea of rollback Mo's algorithm is: since only one operation can be implemented, use only that operation and leave the rest to rollback.

Rollback Mo's algorithm is divided into the version that only uses insertion operations and the version that only uses deletion operations. Below we only introduce the insertion-only version. The deletion-only version differs only slightly in implementation, so it is omitted.

## Example [JOISC 2014 Day1 Historical Research](https://loj.ac/problem/2874)

Given an array $A$ of length $n$ and $m$ queries $(1 \leq n, m \leq 10^5)$, each query asks for the number with the largest importance in an interval $[L, R]$, and requires **outputting its importance**. The importance of a number $i$ is defined as $i$ multiplied by the number of times $i$ appears in the interval.

In this problem, updating the answer during insertion is easy, but updating it during deletion is difficult. If an insertion affects the answer, the new answer must be the importance of the number just inserted. But after deletion, if the number with maximum importance changes, it is hard to determine the new maximum-importance number. Therefore, ordinary Mo's algorithm is hard to apply.

## Procedure

-   Block the original sequence, and sort queries by ascending block number of the left endpoint as the first key, and ascending right endpoint as the second key.
-   Process queries in order:
    -   If the block $B$ containing the query's left endpoint differs from that of the previous query, initialize the left endpoint of Mo's interval to the right endpoint of block $B$ plus $1$, and initialize the right endpoint of Mo's interval to the right endpoint of block $B$;
    -   If the query's left and right endpoints are in the same block, directly scan the interval to answer the query;
    -   If the query's left and right endpoints are in different blocks:
        -   If the query's right endpoint is greater than the right endpoint of Mo's interval, keep extending the right endpoint until it equals the query's right endpoint;
        -   Keep extending the left endpoint of Mo's interval until it equals the query's left endpoint;
        -   Answer the query;
        -   Undo the changes to the left endpoint of Mo's interval, rolling it back to the right endpoint of block $B$ plus $1$.

## Complexity Proof

Assume the block size of rollback Mo's algorithm is $b$:

-   Queries whose left and right endpoints are in the same block can be computed in $O(b)$ time;
-   For other queries, consider queries whose left endpoints are in the same block. Their right endpoints are monotonically increasing, so moving the right endpoint costs $O(n)$ time. The left endpoint moves at most $b$ per query. Since there are $\frac{n}{b}$ blocks, the total complexity is $O(mb+\frac{n^2}{b})$. Taking $b=\frac{n}{\sqrt{m}}$ is optimal, giving time complexity $O(n\sqrt{m})$.

## Implementation

??? note "Reference Code"
    ```cpp
    --8<-- "docs/misc/code/rollback-mo-algo/rollback-mo-algo_1.cpp"
    ```

## References

-   [Rollback Mo's Algorithm and Simple Applications | Parsnip's Blog](https://www.cnblogs.com/Parsnip/p/10969989.html)
