author: StudyingFather, Backl1ght, countercurrent-time, Ir1d, greyqz, MicDZ, ouuan

## Form

Assume $n=m$. For range query problems on a sequence, if the answer for $[l,r]$ can be extended in $O(1)$ to the answers for $[l-1,r],[l+1,r],[l,r+1],[l,r-1]$ (that is, intervals adjacent to $[l,r]$), then all query answers can be found in $O(n\sqrt{n})$ time.

## Explanation

After processing offline, sort the queries and handle them in order. Brute-force transition from the previous interval's answer to the next interval's answer by moving one step at a time.

## Sorting Method

For interval $[l,r]$, sort in increasing order by the block number containing $l$ as the first key, and by $r$ as the second key.

## Implementation

```cpp
void move(int pos, int sign) {
  // update nowAns
}

void solve() {
  BLOCK_SIZE = int(ceil(pow(n, 0.5)));
  sort(querys, querys + m);
  for (int i = 0; i < m; ++i) {
    const query &q = querys[i];
    while (l > q.l) move(--l, 1);
    while (r < q.r) move(++r, 1);
    while (l < q.l) move(l++, -1);
    while (r > q.r) move(r--, -1);
    ans[q.id] = nowAns;
  }
}
```

## Complexity Analysis

The following discussion assumes $n$ and $m$ are of the same order.

First, consider the blocking step. Its time complexity is $O(\sqrt{n}\cdot\sqrt{n}\log\sqrt{n}+n\log n)=O(n\log n)$.

Next comes the essence of Mo's algorithm. We will prove its time complexity is $O(n\sqrt{n})$ using an intuitive elementary method.

???+ note "Proof"
    Proof: Let the maximum value of $L$ in each block be $\max_1,\max_2,\max_3, \cdots , \max_{\lceil\sqrt{n}\rceil}$.
    
    From the first sorting key, we know $\max_1 \le \max_2 \le \cdots \le \max_{\lceil\sqrt{n}\rceil}$.
    
    Clearly, brute-forcing the first query in each block costs $O(n)$ time.
    
    Consider the worst case. In every block, the maximum value of $R$ is $n$, and each modification operation changes $L$ from $\max_{i - 1}$ to $\max_i$ or from $\max_i$ to $\max_{i - 1}$.
    
    Consider $R$: since $R$ has already been sorted within a block, modifying it throughout the same block costs $O(n)$ time. Across all blocks, this is $O(n\sqrt{n})$.
    
    Now focus on $L$: since each change costs $O(\max_i-\max_{i-1})$, the time complexity within the same block is $O(\sqrt{n}\cdot(\max_i-\max_{i-1}))$.
    
    Combining the time complexity of $L$ over all blocks gives:
    
    The total time complexity for $L$ is
    
    $$
    \begin{aligned}
    & O(\sqrt{n}(\max{}_1-1)+\sqrt{n}(\max{}_2-\max{}_1)+\sqrt{n}(\max{}_3-\max{}_2)+\cdots+\sqrt{n}(\max{}_{\lceil\sqrt{n}\rceil}-\max{}_{\lceil\sqrt{n}\rceil-1))} \\
    = \phantom{} & O(\sqrt{n}\cdot(\max{}_1-1+\max{}_2-\max{}_1+\max{}_3-\max{}_2+\cdots+\max{}_{\lceil\sqrt{n}\rceil-1}-\max{}_{\lceil\sqrt{n}\rceil-2}+\max{}_{\lceil\sqrt{n}\rceil}-\max{}_{\lceil\sqrt{n}\rceil-1)}) \\
    = \phantom{} & O(\sqrt{n}\cdot(\max{}_{\lceil\sqrt{n}\rceil}-1))\\
    \end{aligned}
    $$
    
    (telescoping sum)
    
    From the problem, $\max_{\lceil\sqrt{n}\rceil}$ is at most $n$, so the total time complexity for $L$ is $O(n\sqrt{n})$ in the worst case.

In summary, the time complexity of Mo's algorithm is $O(n\sqrt{n})$.

However, for other values of $m$, such as $m<n$, the blocking method needs to change to become more optimal.

How should we choose the block size?

Let the block length be $S$. For any number of queries in the same block, the movement distance is $n$. There are $\displaystyle \frac{n}{S}$ blocks, so the total number of moves is $\displaystyle \frac{n^2}{S}$. Since movement may cross blocks, we also add a complexity of $mS$. The total complexity is $\displaystyle O\left(\frac{n^2}{S}+mS\right)$. To minimize this value, make the two terms as equal as possible. We find that choosing $S$ as $\displaystyle \frac{n}{\sqrt{m}}$ is optimal, giving complexity $\displaystyle O\left(\frac{n^2}{\displaystyle \frac{n}{\sqrt{m}}}+m\left(\frac{n}{\sqrt{m}}\right)\right)=O(n\sqrt{m})$.

In fact, if the block length is set inaccurately, the time complexity of Mo's algorithm can be greatly affected. For example, if $m$ is of the same order as $\sqrt n$ and the block length is mistakenly set to $\sqrt n$, it is easy to construct data that makes the time complexity $O(n \sqrt n)$ instead of the correct $O(n^{5/4})$.

Mo's algorithm looks very brute-force largely because its block-based sorting method appears crude. One might think of sorting all intervals using a seemingly more refined method. For example, treat all intervals $[l, r]$ as points $(l, r)$ on a plane, build a Manhattan minimum spanning tree over all points, and transfer answers between queries along edges of this tree. This seems able to improve the time complexity of Mo's algorithm, but in fact the upper bound of the block-sorting method for queries is already optimal.

Assume $n, m$ are of the same order and $n$ is a perfect square. Consider intervals of the form $[a \sqrt n, b \sqrt n](1 \le a, b \le \sqrt n)$; there are $n$ such intervals. If all intervals are viewed as points on a plane, the Manhattan distance between two points is exactly the transition cost between the two intervals, and the minimum Manhattan distance between any two intervals is $\sqrt n$. Therefore, the minimum time complexity for processing all queries is $O(n \sqrt n)$. Data constructions for other cases are similar.

Mo's algorithm has another feature: when $n$ is fixed, the larger $m$ is, the smaller the average transition cost per query becomes. Some other offline algorithms also have this feature, such as Tarjan's algorithm for LCA, but Mo's algorithm has the most obvious change in average transition cost as $m$ changes.

## Examples and Code

???+ note "Example [「国家集训队」小 Z 的袜子](https://www.luogu.com.cn/problem/P1494)"
    Problem summary:
    
    There is a sequence $\{c_i\}$ of length $n$. Given $m$ queries, each query gives two numbers $l,r$. Randomly choose two different numbers whose indices are between $l$ and $r$, and find the probability that the two numbers are equal.

### Process

Idea: this is a template problem for Mo's algorithm.

For interval $[l,r]$, sort in increasing order by the block number containing $l$ as the first key, and by $r$ as the second key.

Then compute answers starting from the first query in the sequence. The first query is computed directly by brute force in $O(n)$ time, and later queries are answered based on the previous query.

Detailed method:

For interval $[i,i]$, since it has only one element, the answer is easy to know. Then move step by step from the current interval (whose answer is known) toward the next interval.

Let $col[i]$ denote how many times color $i$ appears currently, and let $ans$ denote the current number of feasible pairing schemes, i.e. the number of ways to choose a pair of socks with the same color. Then update the answer whenever moving: suppose the current color is $k$. If the interval is expanded, add $\dbinom{col[k]+1}{2}-\dbinom{col[k]}{2}$ to $ans$; if it is shrunk, subtract $\dbinom{col[k]}{2}-\dbinom{col[k]-1}{2}$ from $ans$. The answer to this query is $\displaystyle \frac{ans}{\dbinom{r-l+1}{2}}$.

There is an optimization here: $\displaystyle \dbinom{a}{2}=\frac{a (a-1)}{2}$.

Therefore $\displaystyle \dbinom{a+1}{2}-\dbinom{a}{2}=\frac{(a+1) a}{2}-\frac{a (a-1)}{2}=\frac{a}{2}\cdot (a+1-a+1)=\frac{a}{2}\cdot 2=a$.

So $\dbinom{col[k]+1}{2}-\dbinom{col[k]}{2}=col[k]$.

Overall algorithm complexity: $O(n\sqrt{n} )$.

In the code below, `deno` denotes the denominator of the answer, `nume` denotes the numerator, `sqn` denotes the block size $\sqrt{n}$, `arr` is the input array, `node` is the structure storing queries, `tab` is the query sequence after sorting, and `col` is as described above.

**Note: because of `++l` and `--r`, the positions of the four while loops that move the interval in the code below are critical. Their relative order must not be changed arbitrarily.**

??? note "Discussion of the positions of the four loops"
    Moving an interval in Mo's algorithm is equivalent to adding the elements of $[1,r]$ and deleting the elements of $[1,l-1]$. Therefore,
    
    -   When $l\le r$, the elements of $[1,l-1]$ are effectively added once and deleted once, the elements of $[l,r]$ are added once, and the elements of $[r+1,+\infty)$ are not added. This is a valid interval.
    -   When $l=r+1$, the elements of $[1,r]$ are effectively added once and deleted once, and the elements of $[r+1,+\infty)$ are not added. This interval represents the empty interval.
    -   When $l>r+1$, the elements of $[r+1,l-1]$ (a nonempty interval) are deleted once but not added, so the number of times such an element has been added is negative.
    
    Therefore, if $l>r+1$ occurs at some moment, there will be an element whose addition count is negative. This causes problems in some tasks. For example, if we use a `set` to maintain all numbers in the interval, we may need to delete an element that does not exist in the `set`.
    
    The four while loops in the code have $4!=24$ possible orders. Suppose the first loop operates on the left endpoint; then there are the following $12$ orders (the other $12$ are symmetric). The table lists the correctness of these 12 orders and gives counterexamples for incorrect ones.
    
    | Loop order        | Correctness | Counterexample or note |
    | ----------------- | ----------- | ---------------------- |
    | `l--,l++,r--,r++` | Incorrect   | $l<r<l'<r'$            |
    | `l--,l++,r++,r--` | Incorrect   | $l<r<l'<r'$            |
    | `l--,r--,l++,r++` | Incorrect   | $l<r<l'<r'$            |
    | `l--,r--,r++,l++` | Correct     | Proof is tedious       |
    | `l--,r++,l++,r--` | Correct     |                        |
    | `l--,r++,r--,l++` | Correct     |                        |
    | `l++,l--,r--,r++` | Incorrect   | $l<r<l'<r'$            |
    | `l++,l--,r++,r--` | Incorrect   | $l<r<l'<r'$            |
    | `l++,r++,l--,r--` | Incorrect   | $l<r<l'<r'$            |
    | `l++,r++,r--,l--` | Incorrect   | $l<r<l'<r'$            |
    | `l++,r--,l--,r++` | Incorrect   | $l<r<l'<r'$            |
    | `l++,r--,r++,l--` | Incorrect   | $l<r<l'<r'$            |
    
    Among all 24 orders, only 6 are correct, and the proofs for 2 of them are tedious. Here we only give the proof for 4 of them.
    
    The common feature of these 4 correct orders is that the first two steps expand the interval (`l--` or `r++`), and the last two steps shrink it (`l++` or `r--`). With this order, the first two steps expand the interval and keep $l\le r+1$. After the first two steps, $l\le l'\le r'\le r$ must hold. The last two steps only shrink the interval to $[l',r']$, and still maintain $l\le r+1$, so this order is correct.

### Implementation

??? note "Reference Code"
    ```cpp
    --8<-- "docs/misc/code/mo-algo/mo-algo_1.cpp"
    ```

## Optimization of Ordinary Mo's Algorithm

### Process

Consider the following data:

```text
// Assume the block size is 2
1 1
2 100
3 1
4 100
```

By simulating manually, we find that the r pointer moves about 300 times. After processing the first block, $l = 2, r = 100$. At this point, only moving the l pointer twice would obtain the answer to the fourth query, but instead we move the r pointer to 1 to answer the third query, then move it back to 100 to answer the fourth query. This adds more than ninety pointer moves. How can we optimize this? Use odd-even sorting.

What is odd-even sorting? For queries in odd-numbered blocks, sort r in increasing order; for queries in even-numbered blocks, sort r in decreasing order. Then after the r pointer finishes an odd block, it processes the even block on the way back, and then moves toward n to process the next odd block. This optimizes the number of moves of the r pointer. In general, this optimization can make the program about 30% faster.

### Implementation

Sorting code:

=== "One-line Style"
    ```cpp
    // clang-format off
    // There is a small detail here, explained later
    int unit; // Block size
    struct node {
      int l, r, id;
      bool operator < (const node &x) const {
        return l / unit == x.l / unit ? (r == x.r ? 0 : ((l / unit) & 1) ^ (r < x.r)) : l < x.l;
      }
    };
    ```

=== "Expanded Style"
    ```cpp
    struct node {
      int l, r, id;
    
      bool operator<(const node &x) const {
        if (l / unit != x.l / unit) return l < x.l;
        // Note: the following two lines must not use <= or >=, otherwise errors occur
        if ((l / unit) & 1) return r < x.r;
        return r > x.r;
      }
    };
    ```

???+ warning "Small Detail"
    When using `sort` to compare two structures, it must not be possible for both $a < b$ and $b < a$ to be true at the same time; otherwise a runtime error may occur. See [common mistakes](../contest/common-mistakes.md#会导致-re).

For the one-line version, without the special case `r == x.r`, when l belongs to the same odd block and r is equal, the issue described above occurs (try simulating it manually). For the expanded version, the same issue occurs if less-than-or-equal or greater-than-or-equal is used.

## References

-   [莫队算法学习笔记 | Sengxian's Blog](https://blog.sengxian.com/algorithms/mo-s-algorithm)
