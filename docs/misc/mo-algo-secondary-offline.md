author: Lyccrius, AtomAlpaca

## Overview

Sometimes we encounter problems that seem very suitable for Mo's algorithm, but their single transition is not $O(1)$. In that case, directly using Mo's algorithm, even with adjusted block length, leads to incorrect complexity.

If the contribution of each transition to the answer can be differenced, we can split these transitions and process them offline in batches with other algorithms.

Use $f(x, l, r)$ to denote the contribution of $x$ with respect to $[l, r]$.

For example, when extending the current interval $[l, r]$ to $[l, r + 1]$, we need $f(a_{r + 1}, l, r)$. If it can be differenced, we can write it as $f(a_{r + 1}, 1, r) - f(a_{r + 1}, 1, l - 1)$. The first term can be preprocessed for every $r$, and for the latter term, we can store each such term offline at the corresponding $l - 1$, then enumerate in increasing order and process with a sweep line. The other transition directions can be handled similarly.

This algorithm, which performs another layer of offline processing on transitions within Mo's offline algorithm, is called secondary offline Mo's algorithm.

We explain it using concrete problems.

## Examples

???+ note "[Luogu P5047 \[Ynoi2019 Mock Contest\] Yuno loves sqrt technology II](https://www.luogu.com.cn/problem/P5047)"
    Given a sequence $a$ of length $n$ and $m$ queries, each query asks for the number of inversions in an interval.
    
    Data range: $1 \leq n,m \leq 10^5$, $0 \leq a_i \leq 10^9$.

Direct Mo's algorithm has at least $O(\log n)$ time per transition. Observe that the information needed for each transition is "the rank of a number within an interval", and this information can be differenced with respect to the interval, so we consider secondary offline processing.

When extending $[l, r]$ to $[l, r + 1]$, we need the number of elements in interval $[l, r]$ that are greater than $a_{r + 1}$.
Let $f(x, r)$ denote the number of elements greater than $a_x$ in interval $[1, r]$, and let $g(x, r)$ denote the number of elements smaller than $a_x$ in interval $[1, r]$. Then the change in the answer can be written as $f(r + 1, r) - f(r + 1, l - 1)$.

Similarly, the change when shrinking $[l, r]$ to $[l, r - 1]$ can be written as $-f(r, r - 1) + f(r, l - 1)$; extending $[l, r]$ to $[l - 1, r]$ can be written as $g(l - 1, r) - g(l - 1, l - 2)$, and shrinking $[l, r]$ to $[l + 1, r]$ can be written as $- g(l, r) + g(l, l - 1)$.

For $f(x, x - 1)$ and $g(x, x - 1)$ in these formulas, we can preprocess them with a Fenwick tree in $O(n \log n)$ time. For the remaining $f(x, p)$ and $g(x, p)$ terms, we store $x$ offline at $l$ and process them in batches.

There is a space optimization trick here: we find that when processing each query, the $x$ values offline at $p$ form a continuous segment, so we do not need to store every move; we only need to store the adjusted segment. This reduces the space from total movement count $O(n\sqrt{m})$ to query count $O(m)$.

Now process the secondary offline problem: insert numbers into a set and query the rank of a number in the set. Mo's algorithm moves endpoints $O(n\sqrt{m})$ times in total, while the array length is only $O(n)$, so we can solve this problem with value-domain decomposition supporting $O(\sqrt{n})$ insertion and $O(1)$ query.

Thus, we solve this problem in time complexity $O(n \sqrt{m} + n \sqrt{n})$ and space complexity $O(n + m)$.

Finally, note that what we obtain is the change in each answer, not the answer itself, so we need to take prefix sums to get the final answers.

??? note "Example Code"
    ```cpp
    --8<-- "docs/misc/code/mo-algo-secondary-offline/mo-algo-secondary-offline_1.cpp"
    ```

???+ note "[Luogu P5501 \[LnOI2019\] Those Who Come Are Welcome, Those Who Leave Are Not Pursued](https://www.luogu.com.cn/problem/P5501)"
    Multiple queries ask for the sum of the "Abbi values" of all numbers in interval $[l, r]$.
    
    The Abbi value is defined as follows: if $a_i$ is the $k$-th smallest number in the query interval $[l,r]$, then its "Abbi value" is $ka_i$.

Let $f(x,r)$ be the sum of numbers greater than $a_x$ in $[1,r]$, and let $g(x,r)$ be the count of numbers greater than $a_x$ in $[1,r]$. Then when moving the right endpoint right, the contribution is $f(r,r-1)-f(r,l-1) + a_r(r-l+ 1-(g(r,r-1)-g(r,l-1)))$. The other directions can be written similarly and are omitted here.

The $f(r, r - 1)$ and $g(r, r - 1)$ in the formula above can still be preprocessed, and the rest are stored offline at the other endpoint and processed with a sweep line. It is not hard to find that what we still need to process is $O(n)$ insertions and $O(n\sqrt{m})$ rank queries, so value-domain decomposition can again be used.

??? note "Example Code"
    ```cpp
    --8<-- "docs/misc/code/mo-algo-secondary-offline/mo-algo-secondary-offline_2.cpp"
    ```
