Two-dimensional Mo's algorithm, as the name suggests, means each state can be extended in four directions.

Each pointer move in two-dimensional Mo's algorithm operates on a row or a column. The concrete implementation is similar to ordinary one-dimensional Mo's algorithm, so it is omitted here. This page focuses on choosing the block size.

## Choosing the Block Size

Let the number of queries be $q$, the upper-left coordinate of the current matrix be $(x_1,\ y_1)$, the lower-right coordinate be $(x_2,\ y_2)$, and the block size be $B$.

Then pointer $x_1$ moves $\Theta(q\cdot B)$ times, while pointer $y_2$ moves $\Theta(n^4\cdot B^{-3})$ times.

Therefore, it is enough to set $q\cdot B=n^4\cdot B^{-3}$, i.e. $B=n\cdot q^{-\frac 14}$.

Note that the result of this calculation for $B$ **may be $0$**, so **handle this special case**.

Finally, the computation part has time complexity $\Theta(n^2\cdot q^{\frac 34})$. Including the sorting process for queries, the total time complexity is $\Theta(n^2\cdot q^{\frac 34}+q\log q)$.

## Example 1

???+ note "[BZOJ 2639 Rectangle Calculation](https://hydro.ac/p/bzoj-P2639)"
    Given an $n\times m$ matrix where every element is an integer, and $q$ queries. Each query asks for the value of a submatrix. The value of a matrix is defined as follows: for an integer $x$, if it appears $p$ times in the matrix, then it contributes $p^2$ to the matrix value.
    
    Data range: $1\leq n,\ m\leq 200$, $0\leq q\leq 10^5$, $|$ matrix element value $| \leq 2\times 10^9$.

??? note "Solution"
    First discretize, then in two-dimensional Mo's algorithm, use an array to record the current occurrence count of each number.

??? note "Example Code"
    ```cpp
    --8<-- "docs/misc/code/mo-algo-2dimen/mo-algo-2dimen_1.cpp"
    ```

## Example 2

???+ note "[Luogu P1527 \[National Training Team\] Matrix Multiplication](https://www.luogu.com.cn/problem/P1527)"
    Given an $n\times n$ matrix and $q$ queries, each query asks for the $k$-th smallest number in a subrectangle.
    
    Data range: $1\leq n\leq 500$, $1\leq q\leq 6\times 10^4$, $0\leq a_{i,j}\leq 10^9$.

As in the previous problem, the whole matrix must first be discretized. But note that in this problem, besides blocking values, we also need to block the value domain in order to obtain the answer.

Odd-even ordering is also needed here for optimization. See [ordinary Mo's algorithm](../misc/mo-algo.md#普通莫队的优化) for details.

For this problem, the time limit is not very loose, so pay attention to constant factors. The computed block size is generally small; when both $n,\ q$ take their maximum values, the block size is around $11$, so it can be directly set as a constant to reduce running time.

??? note "Example Code"
    ```cpp
    --8<-- "docs/misc/code/mo-algo-2dimen/mo-algo-2dimen_2.cpp"
    ```
