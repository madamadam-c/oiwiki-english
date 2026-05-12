Problems in the following forms can be solved using the method of **congruence shortest path**:
- Given $n$ integers, how many other integers can be formed using them (each integer can be used repeatedly)?
- Given $n$ integers, find the smallest (or largest) integer that cannot be formed?
- How many operations are needed at minimum to form a number with remainder $p$ modulo $K$?

Congruence shortest path uses congruences to construct states, achieving optimization of space complexity.

Analogous to the [difference constraints](./diff-constraints.md) method, the states constructed using congruences can be viewed as nodes in single-source shortest path. The state transitions in congruence shortest path are typically $f(i+y) = f(i) + y$, similar to $f(v) = f(u) + edge(u, v)$ in single-source shortest path.

## Examples

### Example 1

???+ note "[P3403 Building](https://www.luogu.com.cn/problem/P3403)"
    Problem: Given $x, y, z, h$, for $k \in [1, h]$, how many values of $k$ satisfy $ax + by + cz = k$? ($0 \leq a, b, c$, $1 \leq x, y, z \leq 10^5$, $h \leq 2^{63} - 1$)

    Assume $x < y < z$.

    Let $d_i$ be the minimum floor reachable using **operation 2** and **operation 3** such that $p \bmod x = i$. That is, the minimum number congruent to $i$ modulo $x$ that can be obtained, used to count how many numbers in this congruence class satisfy the conditions.

    We have two state transitions:

    - $i \xrightarrow{y} (i + y) \bmod x$
    - $i \xrightarrow{z} (i + z) \bmod x$

    Note that we typically take the modulus using the smallest number among $a_i$, which is $x$ in this case, to minimize space complexity (smallest residue system).

    This is equivalent to adding edges in shortest path:

    `add(i, (i + y) % x, y)`
    `add(i, (i + z) % x, z)`

    Then we only need to find $d_0, d_1, d_2, \dots, d_{x-1}$ by running a single shortest path computation.

??? example "Shortest Path Implementation"
    ```cpp
    --8<-- "docs/graph/code/mod-shortest-path/mod-shortest-path_1.cpp"
    ```

    However, we don't actually need a full shortest path computation. Two special properties apply:

    First, there are only two edge weights, and due to the commutativity of addition, the order of traversing edges does not matter. Therefore, we can run two separate shortest path computations, each using only one type of edge weight.

    Second, in a graph with only one type of edge weight, each node $u$ has one in-degree (from $(u - y) \bmod x$) and one out-degree (from $(u + y) \bmod x$), so the entire graph consists of several cycles. It can be proven that there are $\gcd(x, y)$ cycles of equal length.

???+ note "Proof"
    Let $d = \gcd(x, y)$, with $x = da, y = db$, so $\gcd(a, b) = 1$.

    Starting from $u$, after $k$ steps we reach $(u + ky) \bmod x$. For a cycle to form, we need $ky \equiv 0 \pmod x$, i.e., $kb \equiv 0 \pmod a$.

    Since $\gcd(a, b) = 1$, the smallest such $k$ is $k = a$, so the cycle length is $a = \frac{x}{d}$. Since we can start from any point, all cycles have the same length, and there are $d$ cycles.

    Moreover, since edge weights are positive, after traversing a cycle twice, no further relaxation is possible. We can simply iterate and update — this achieves $O(x)$ time complexity without being bound by shortest path complexity.

    Similar to difference constraints, when a solution $\{a_1, a_2, \cdots, a_n\}$ exists, $\{a_1 + d, a_2 + d, \cdots, a_n + d\}$ is also a solution. So in this problem, we use $i = 1$ as the source, where $dis_1 = 1$ is the minimum value in the known range, giving us a minimal solution.

    The answer is:

    $$
    \sum_{i=0}^{x-1}\left(\frac{h - d_i}{x} + 1\right)
    $$

    The $+1$ is because the floor at $d_i$ also counts as one.

    Note that since $h \leq 2^{63} - 1$, the initial value of $d_i$ should be set to at least $2^{63}$ before computing shortest paths, which exceeds the maximum value of `long long` in C++. We can use `unsigned long long` instead, or first set $h \gets h - 1$ and the minimum floor to $0$.

??? example "Cycle Optimization Implementation"
    ```cpp
    --8<-- "docs/graph/code/mod-shortest-path/mod-shortest-path_2.cpp"
    ```

### Example 2

???+ note "[ARC084B Small Multiple](https://atcoder.jp/contests/arc084/tasks/arc084_b)"
    Problem: Given $n$, find the minimum digit sum among all multiples of $n$. ($1 \leq n \leq 10^5$)

    This problem can be solved using circular convolution to optimize knapsack in $O(n \log^2 n)$ time, but we aim for a linear algorithm.

    Observe that any positive integer can be obtained from $1$ by repeatedly applying operations of multiplying by $10$ and adding $1$ in some order. The number of times $1$ is added is the digit sum of the number. This suggests using shortest path.

    For all $0 \leq k \leq n - 1$, add an edge of weight $0$ from $k$ to $10k$, and an edge of weight $1$ from $k$ to $k + 1$. (Node indices are taken modulo $n$)

    Each multiple of $n$ corresponds to a path from node $1$ to node $0$ in this graph. Finding the shortest path from $1$ to $0$ gives the answer. Some paths are invalid (e.g., taking $10$ consecutive edges of weight $1$), but such paths never produce optimal answers.

    Time complexity: $O(n)$.

## Exercises

[Luogu P3403 Building](https://www.luogu.com.cn/problem/P3403)

[Luogu P2662 Cow Fence](https://www.luogu.com.cn/problem/P2662)

[National Training Team] Momo's Equation](https://www.luogu.com.cn/problem/P2371)

[「NOIP2018」Currency System](https://loj.ac/problem/2951)

[AGC057D - Sum Avoidance](https://atcoder.jp/contests/agc057/tasks/agc057_d)

[「THUPC 2023 Prelim」Knapsack](https://loj.ac/p/6872)