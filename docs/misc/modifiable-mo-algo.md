author: StudyingFather, Backl1ght, countercurrent-time, Ir1d, greyqz, MicDZ, ouuan, renbaoshuo, Lixuannan

Please make sure you already know ordinary Mo's algorithm. If not, read the previous [ordinary Mo's algorithm](./mo-algo.md) first.

## Characteristics

Ordinary Mo's algorithm cannot handle modifications.

We can force it to support modifications. Like DP, we can forcibly add one more **time dimension**, representing the time of this operation.

The time dimension represents the number of modifications experienced.

That is, turn a query $[l,r]$ into $[l,r,\text{time}]$.

Then our coordinate can also move along the time dimension. That is, $[l,r,\text{time}]$ gains one additional movable direction and can become:

-   $[l-1,r,\text{time}]$
-   $[l+1,r,\text{time}]$
-   $[l,r-1,\text{time}]$
-   $[l,r+1,\text{time}]$
-   $[l,r,\text{time}-1]$
-   $[l,r,\text{time}+1]$

These transitions are also $O(1)$, but sorting has one more key. Handle it similarly.

Using a sorting method similar to ordinary Mo's algorithm, this can achieve $O(n^{5/3})$.

This time, the sorting method uses blocks of size $n^{2/3}$, divided into $n^{1/3}$ blocks. The first key is the block containing the left endpoint, the second key is the block containing the right endpoint, and the third key is time.

???+ note "Optimal Block Size and Time Complexity Analysis"
    Let the sequence length be $n$, with $m$ queries and $t$ modifications.
    
    The second sorting key of Mo's algorithm with modifications is the block number of the right endpoint, unlike ordinary Mo's algorithm.
    
    Think about what happens if the right endpoint is not blocked:
    
    -   If right endpoints are unordered, they may move $n$ times per query.
    -   If right endpoints are ordered, time becomes unordered and may move $t$ times per query.
    
    Either case has unacceptable time cost.
    
    Now analyze the time complexity.
    
    Let the block size be $s$, so there are $\dfrac{n}{s}$ blocks. For block $i$ and block $j$, let $q_{i,j}$ be the number of queries whose left endpoint lies in block $i$ and right endpoint lies in block $j$.
    
    For each "group" of queries $(i,j)$ where the left and right endpoints do not change blocks, the endpoints move $O(s)$ times per query, and time increases monotonically, costing $O(t)$.
    
    The time for endpoints changing blocks is ignored.
    
    Written out:
    
    $$
    \begin{aligned}
    &\sum_{i=1}^{n/s}\sum_{j=i+1}^{n/s}(q_{i,j}\cdot s+t)\\
    =&ms+\left(\dfrac{n}{s}\right)^2t\\
    =&ms+\dfrac{n^2t}{s^2}
    \end{aligned}
    $$
    
    Consider differentiating to minimize this expression. Let $f(s)=ms+\dfrac{n^2t}{s^2}$. Then $f'(s)=m-\dfrac{2n^2t}{s^3}=0$.
    
    Thus $s=\sqrt[3]{\dfrac{2n^2t}{m}}=\dfrac{2^{1/3}n^{2/3}t^{1/3}}{m^{1/3}}=s_0$.
    
    In other words, when the block size is $\dfrac{n^{2/3}t^{1/3}}{m^{1/3}}$, the optimal time complexity is $O\left(n^{2/3}m^{2/3}t^{1/3}\right)$.
    
    The commonly stated $O\left(n^{5/3}\right)$ treats $n,m,t$ as being of the same order.
    
    In practice, it is still recommended to set the block size to $n^{2/3}$.

## Example

???+ note "Example [\[National Training Team\] Number of Colors / Maintain Queue](https://www.luogu.com.cn/problem/P1903)"
    Problem summary: given a sequence and M operations, there are two types of operations:
    
    1.  Modify the number at one position in the sequence.
    2.  Query the number of distinct values in interval $[l,r]$ (multiple equal numbers count only once).

It is not hard to see that without operation 1 (modification), ordinary Mo's algorithm can solve the problem easily.

But the problem also has point modifications, so use **Mo's algorithm with modifications**.

### Procedure

First consider ordinary Mo's algorithm:

-   When expanding the interval, each time a number is added, count how many times it has already appeared. If its occurrence count before adding is $0$, it means this is a new number, so answer $+1$. Then increase this number's occurrence count by $+1$.
-   When shrinking the interval, each time a number is deleted, count its occurrence count after deletion. If its occurrence count after deletion is $0$, it means this number has been completely removed from the current interval, so the current interval has one fewer color and the answer is $-1$. Then decrease this number's occurrence count by $-1$.

Now consider modifications:

-   For a point modification, modify the number at one position. Suppose we transfer from a query that has experienced $i$ modifications to a query that has experienced $j$ modifications, and $i<j$. Then we need to forcibly apply modifications $i+1$ through $j$.
-   If $j<i$, we need to forcibly roll back modifications $i$ through $j+1$.

How do we forcibly apply a modification? Suppose a modification changes the color at position $pos$: the original color at pos is $a$, and the new color is $b$. Also suppose the current Mo interval is $[l,r]$.

-   Apply this modification: first check whether $pos$ lies inside interval $[l,r]$. If so, this is equivalent to deleting color $a$ from the interval, adding color $b$, and changing the color at position $pos$ in the current color sequence to $b$. If $pos$ is not inside interval $[l,r]$, directly change the color at position $pos$ in the current color sequence to $b$.
-   Roll back this modification: this is equivalent to applying a modification at position $pos$ that changes color $b$ back to color $a$.

Thus, this problem can be solved easily with Mo's algorithm with modifications.

### Implementation

??? note "Reference Code"
    ```cpp
    --8<-- "docs/misc/code/modifiable-mo-algo/modifiable-mo-algo_1.cpp"
    ```
