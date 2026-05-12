author: hydingsy, Link-cute, Ir1d, greyqz, LuoshuiTianyi, odeinjul, xyf007, GoodCoder666, paigeman, shenshuaijie, oldoldtea

Prerequisite: [Introduction to dynamic programming](./index.md).

## Introduction

Before describing what "knapsack DP" is, consider the following example:

???+ note "[USACO07 DEC Charm Bracelet](https://www.luogu.com.cn/problem/P2871)"
    Problem summary: There are $n$ items and a knapsack with capacity $W$. Each item has two attributes, weight $w_{i}$ and value $v_{i}$. Choose some items to put into the knapsack so that the total value is maximized while the total weight does not exceed the knapsack capacity.

In this example, each item has only two possible states, chosen or not chosen, corresponding to $1$ and $0$ in binary. Problems of this type are called **0-1 knapsack problems**.

## 0-1 Knapsack

### Explanation

The known data in the example are the weight $w_i$ and value $v_i$ of item $i$, and the total knapsack capacity $W$.

Let the DP state $f_{i,j}$ denote the maximum total value achievable with a knapsack of capacity $j$ when only the first $i$ items may be used.

Consider the transition. Suppose all states for the first $i-1$ items have already been computed. For item $i$, if it is not put into the knapsack, the remaining capacity and the total value both stay unchanged, so the best value in this case is $f_{i-1,j}$. If it is put into the knapsack, the remaining capacity decreases by $w_i$ and the total value increases by $v_i$, so the best value in this case is $f_{i-1,j-w_i}+v_i$.

Thus the state transition equation is:

$$
f_{i,j}=\max(f_{i-1,j},f_{i-1,j-w_{i}}+v_{i})
$$

If we directly use a two-dimensional array to store the states, we may get MLE. We can instead optimize with a rolling array.

Since only $f_{i-1}$ affects $f_i$, the first dimension can be removed. Use $f_i$ to denote the maximum value for capacity $i$ after processing the current item. This gives the following equation:

$$
f_j=\max \left(f_j,f_{j-w_i}+v_i\right)
$$

**Be sure to remember and understand this transition equation, because most knapsack transitions are derived from it.**

### Implementation

One more point deserves attention: it is very easy to write the following **incorrect core code**:

=== "C++"
    ```cpp
    for (int i = 1; i <= n; i++)
      for (int l = 0; l <= W - w[i]; l++)
        f[l + w[i]] = max(f[l] + v[i], f[l + w[i]]);
    // Simplified from f[i][l + w[i]] = max(max(f[i - 1][l + w[i]],
    // f[i - 1][l] + w[i]), f[i][l + w[i]]);
    ```

=== "Python"
    ```python
    for i in range(1, n + 1):
        for l in range(0, W - w[i] + 1):
            f[l + w[i]] = max(f[l] + v[i], f[l + w[i]])
    # Simplified from f[i][l + w[i]] = max(max(f[i - 1][l + w[i]],
    # f[i - 1][l] + w[i]), f[i][l + w[i]])
    ```

What is wrong with this code? The enumeration order is wrong.

Looking carefully at the code, for the current item $i$ and current state $f_{i,j}$, when $j\geqslant w_i$, $f_{i,j}$ is affected by $f_{i,j-w_i}$. This is equivalent to allowing item $i$ to be put into the knapsack multiple times, which contradicts the statement. In fact, this is exactly the solution for complete knapsack.

To avoid this, enumerate in the opposite direction, from $W$ down to $w_i$. Then the error above cannot occur, because $f_{i,j}$ is always updated before $f_{i,j-w_i}$.

Therefore the actual core code is:

=== "C++"
    ```cpp
    for (int i = 1; i <= n; i++)
      for (int l = W; l >= w[i]; l--) f[l] = max(f[l], f[l - w[i]] + v[i]);
    ```

=== "Python"
    ```python
    for i in range(1, n + 1):
        for l in range(W, w[i] - 1, -1):
            f[l] = max(f[l], f[l - w[i]] + v[i])
    ```

??? note "Example Code"
    ```cpp
    --8<-- "docs/dp/code/knapsack/knapsack_1.cpp"
    ```

## Complete Knapsack

### Explanation

The complete knapsack model is similar to 0-1 knapsack. The only difference is that each item can be chosen infinitely many times instead of at most once.

We can borrow the idea from 0-1 knapsack to define the state: let $f_{i,j}$ be the maximum value achievable with a knapsack of capacity $j$ when only the first $i$ item types may be used.

Note that although this definition is similar to 0-1 knapsack, its transition equation is different.

### Process

Consider a naive approach: for item $i$, enumerate how many copies are chosen and transition accordingly. This has time complexity $O(n^3)$.

The state transition equation is:

$$
f_{i,j}=\max_{k=0}^{+\infty}(f_{i-1,j-k\times w_i}+v_i\times k)
$$

Now consider a simple optimization. For $f_{i,j}$, it is enough to transition from $f_{i,j-w_i}$. Therefore the transition becomes:

$$
f_{i,j}=\max(f_{i-1,j},f_{i,j-w_i}+v_i)
$$

The reason is that when we transition this way, $f_{i,j-w_i}$ has already been updated from $f_{i,j-2\times w_i}$, so $f_{i,j-w_i}$ already fully accounts for the optimal result after considering how many copies of item $i$ are chosen. In other words, we reuse the previous enumeration process through the locally optimal substructure, reducing the enumeration cost.

As with 0-1 knapsack, we can remove the first dimension to optimize space complexity. If you understand the optimization for 0-1 knapsack, it is not hard to see that the compressed loop here goes forward, which is the "wrong optimization" mentioned above.

??? note "[Luogu P1616: Crazy Herb Gathering](https://www.luogu.com.cn/problem/P1616)"
    Problem summary: There are $n$ item types and a knapsack with capacity $W$. Each item type has weight $w_i$ and value $v_i$. Choose any number of items to put into the knapsack so that the total value is maximized while the total weight does not exceed the knapsack capacity.

??? note "Example Code"
    ```cpp
    --8<-- "docs/dp/code/knapsack/knapsack_2.cpp"
    ```

## Multiple Knapsack

Multiple knapsack is another variant of 0-1 knapsack. The difference is that each item type has $k_i$ copies instead of one.

A very naive idea is to transform "choose each item type up to $k_i$ times" into "there are $k_i$ identical items, and each can be chosen once". This reduces the problem to 0-1 knapsack, so the method above applies. The state transition equation is:

$$
f_{i,j}=\max_{k=0}^{k_i}(f_{i-1,j-k\times w_i}+v_i\times k)
$$

The time complexity is $O(W\sum_{i=1}^nk_i)$.

??? note "Core Code"
    ```cpp
    for (int i = 1; i <= n; i++) {
      for (int weight = W; weight >= w[i]; weight--) {
        // Add one more loop over the number of copies.
        for (int k = 1; k * w[i] <= weight && k <= cnt[i]; k++) {
          dp[weight] = max(dp[weight], dp[weight - k * w[i]] + k * v[i]);
        }
      }
    }
    ```

### Binary Grouping Optimization

Consider optimization. We still transform multiple knapsack into a 0-1 knapsack model.

### Explanation

Clearly, the $O(nW)$ part of the complexity cannot be further optimized, so we can only work on the $O(\sum k_i)$ part. For convenience, use $A_{i,j}$ to denote the $j$-th item split from item type $i$.

In the naive approach, for all $j\le k_i$, $A_{i,j}$ denotes the same item. The main reason for the low efficiency is the large amount of repeated work. For example, we consider both "choose $A_{i,1}$ and $A_{i,2}$" and "choose $A_{i,2}$ and $A_{i,3}$", two completely equivalent cases. We perform this kind of redundant work many times, so optimizing the splitting method is the key.

### Process

We can make the splitting more elegant using **binary grouping**.

Specifically, let $A_{i,j}\left(j\in\left[0,\lfloor \log_2(k_i+1)\rfloor-1\right]\right)$ denote bundled items made from $2^j$ individual items. If $k_i+1$ is not a power of $2$, add one final bundled item made from $k_i-2^{\lfloor \log_2(k_i+1)\rfloor-1}$ individual items to make up the remainder.

Examples:

-   $6=1+2+3$
-   $8=1+2+4+1$
-   $18=1+2+4+8+3$
-   $31=1+2+4+8+16$

Obviously, with this splitting method, any equivalent choice of at most $k_i$ items can be represented. After splitting each item type this way, solve the resulting problem using 0-1 knapsack.

The time complexity is $O(W\sum_{i=1}^n\log_2k_i)$.

### Implementation

??? note "Binary Grouping Code"
    === "C++"
        ```cpp
        index = 0;
        for (int i = 1; i <= m; i++) {
          int c = 1, p, h, k;
          cin >> p >> h >> k;
          while (k > c) {
            k -= c;
            list[++index].w = c * p;
            list[index].v = c * h;
            c *= 2;
          }
          list[++index].w = p * k;
          list[index].v = h * k;
        }
        ```
    
    === "Python"
        ```python
        index = 0
        for i in range(1, m + 1):
            c = 1
            p, h, k = map(int, input().split())
            while k > c:
                k -= c
                index += 1
                list[index].w = c * p
                list[index].v = c * h
                c *= 2
            index += 1
            list[index].w = p * k
            list[index].v = h * k
        ```

### Monotone Queue Optimization

See [monotone queue/monotone stack optimization](./opt/monotonous-queue-stack.md).

Exercise: [Luogu P1776: Treasure Selection_NOI Guide 2010 Advanced (02)](https://www.luogu.com.cn/problem/P1776)

## Mixed Knapsack

Mixed knapsack combines the three knapsack types above: some items can be chosen only once, some infinitely many times, and some at most $k$ times.

This kind of problem may look intimidating, but once you understand the central ideas of the previous knapsack types, you can simply combine them. Pseudocode:

```plain
for (loop over item types) {
  if (this is 0-1 knapsack)
    apply the 0-1 knapsack code;
  else if (this is complete knapsack)
    apply the complete knapsack code;
  else if (this is multiple knapsack)
    apply the multiple knapsack code;
}
```

### Example

???+ note "[Luogu P1833: Cherry Blossoms](https://www.luogu.com.cn/problem/P1833)"
    There are $n$ types of cherry blossom trees and a time limit $T$. Some trees can be viewed only once, some at most $A_i$ times, and some infinitely many times. Each tree has an aesthetic value $C_i$. Determine which trees to view within time $T$ to maximize the aesthetic value.

??? note "Core Code"
    ```cpp
    for (int i = 1; i <= n; i++) {
      if (cnt[i] == 0) {  // If the count is unlimited, use complete knapsack.
        for (int weight = w[i]; weight <= W; weight++) {
          dp[weight] = max(dp[weight], dp[weight - w[i]] + v[i]);
        }
      } else {  // Finite items use multiple knapsack; it also handles 0-1 knapsack.
        for (int weight = W; weight >= w[i]; weight--) {
          for (int k = 1; k * w[i] <= weight && k <= cnt[i]; k++) {
            dp[weight] = max(dp[weight], dp[weight - k * w[i]] + k * v[i]);
          }
        }
      }
    }
    ```

Exercise: [HDU 5410 CRB and His Birthday](https://acm.hdu.edu.cn/showproblem.php?pid=5410)

## Two-Dimensional Cost Knapsack

???+ note "[Luogu P1855: Extracting kkksc03](https://www.luogu.com.cn/problem/P1855)"
    There are $n$ tasks to complete. Completing task $i$ takes $t_i$ minutes and costs $c_i$ yuan.
    
    Given $T$ minutes and $W$ yuan to handle these tasks, find the maximum number of tasks that can be completed.

This is clearly a 0-1 knapsack problem, except that choosing one item consumes two kinds of cost, budget and time. We only need to add one more dimension to the state to store the second cost.

At this point, note that it is no longer appropriate to add another dimension for the item index, because that can easily cause MLE.

### Implementation

=== "C++"
    ```cpp
    for (int k = 1; k <= n; k++)
      for (int i = m; i >= mi; i--)    // Enumerate the budget dimension.
        for (int j = t; j >= ti; j--)  // Enumerate the time dimension.
          dp[i][j] = max(dp[i][j], dp[i - mi][j - ti] + 1);
    ```

=== "Python"
    ```python
    for k in range(1, n + 1):
        for i in range(m, mi - 1, -1):  # Enumerate the budget dimension.
            for j in range(t, ti - 1, -1):  # Enumerate the time dimension.
                dp[i][j] = max(dp[i][j], dp[i - mi][j - ti] + 1)
    ```

## Group Knapsack

???+ note "[Luogu P1757: Group Knapsack](https://www.luogu.com.cn/problem/P1757)"
    There are $n$ items and a knapsack of size $m$. Item $i$ has value $w_i$ and volume $v_i$. Each item also belongs to a group, and at most one item can be chosen from each group. Find the maximum total value of items the knapsack can hold.

How should we think about this kind of problem? It changes from "choose one item among all items" to "choose one item from the current group", so running 0-1 knapsack once for each group is enough.

Now consider storage. We can let $t_{k,i}$ denote the index of the $i$-th item in group $k$, and use $\mathit{cnt}_k$ to denote the number of items in group $k$.

### Implementation

=== "C++"
    ```cpp
    for (int k = 1; k <= ts; k++)          // Loop over each group.
      for (int i = m; i >= 0; i--)         // Loop over knapsack capacity.
        for (int j = 1; j <= cnt[k]; j++)  // Loop over each item in this group.
          if (i >= w[t[k][j]])             // The knapsack has enough capacity.
            dp[i] = max(dp[i],
                        dp[i - w[t[k][j]]] + c[t[k][j]]);  // Transition like 0-1 knapsack.
    ```

=== "Python"
    ```python
    for k in range(1, ts + 1):  # Loop over each group.
        for i in range(m, -1, -1):  # Loop over knapsack capacity.
            for j in range(1, cnt[k] + 1):  # Loop over each item in this group.
                if i >= w[t[k][j]]:  # The knapsack has enough capacity.
                    dp[i] = max(
                        dp[i], dp[i - w[t[k][j]]] + c[t[k][j]]
                    )  # Transition like 0-1 knapsack.
    ```

Note: **the loop order must not be mistaken**, otherwise correctness cannot be guaranteed.

## Dependent Knapsack

???+ note "[Luogu P1064: Jinming's Budget Plan](https://www.luogu.com.cn/problem/P1064)"
    Jinming has $n$ yuan and wants to buy $m$ items. Item $i$ costs $v_i$ and has importance $p_i$. Some items are accessories attached to a main item; to buy such an item, its main item must also be bought.
    
    The goal is to maximize the sum of $v_i \times p_i$ over all purchased items.

Consider the cases. For a main item and its accessories, the possible choices are: buy only the main item, or buy the main item plus some accessories. Since exactly one of these possibilities can be chosen, this can be treated as group knapsack.

If the dependency structure is a forest of multiway trees, compute each child subtree first, then compute the parent subtree.

## Knapsack with Generalized Items

In this kind of knapsack, an item has no fixed cost or value. Its value depends on the cost allocated to it. In a knapsack problem with capacity $V$, when cost $v_i$ is allocated to the item, the value obtained is $h\left(v_i\right)$. In this case, replace the fixed value with a reference to a function.

## Miscellaneous

### Small Optimizations

By the greedy principle, when costs are equal, keep only the item with the highest value; when values are equal, keep only the item with the lowest cost; when there are two items $i,j$ such that item $i$ has higher value than item $j$ and lower cost than item $j$, keep only item $i$.

### Knapsack Variants

#### Outputting a Solution

Outputting a solution means recording how some state in the knapsack was derived. We can use $g_{i,v}$ to indicate whether item $i$ was chosen when the occupied space is $v$. During transitions, record which strategy was chosen, choose or not choose. Pseudocode for output:

```cpp
int v = V;  // Record the current storage space.

// Since the last item stores the final state, iterate from the last item.
for (loop from the last item to the first item) {
  if (g[i][v]) {
    item i was chosen;
    v -= the weight of item i;
  } else {
    item i was not chosen;
  }
}
```

#### Counting Solutions

For a problem with a given knapsack capacity, item costs, and other relations, count the total number of ways to reach a certain capacity.

Such problems simply replace maximization with summation.

For example, the transition for 0-1 knapsack becomes:

$$
\mathit{dp}_j \leftarrow \mathit{dp}_j + \mathit{dp}_{j-c_i} \qquad (j \ge c_i)
$$

Initial condition: $\mathit{dp}_0=1$.

When the capacity is $0$, there is also one valid solution: choose nothing.

#### Counting Optimal Solutions

To count the number of optimal solutions, slightly modify the definition of the $\mathit{dp}$ array in 0-1 knapsack. Let DP state $f_{i,j}$ be the maximum total value achievable when only the first $i$ items may be used and a knapsack of capacity $j$ is **filled exactly**.

After this modification, each DP state can use a corresponding $g_{i,j}$ to store the number of solutions.

$f_{i,j}$ denotes the maximum value when only the first $i$ items are considered and the knapsack volume is **exactly** $j$.

$g_{i,j}$ denotes the number of solutions when only the first $i$ items are considered and the knapsack volume is **exactly** $j$.

Transition rules:

If $f_{i,j} = f_{i-1,j}$ and $f_{i,j} \neq f_{i-1,j-v}+w$, then not putting the item into the knapsack is better, and the number of solutions transitions from $g_{i-1,j}$.

If $f_{i,j} \neq f_{i-1,j}$ and $f_{i,j} = f_{i-1,j-v}+w$, then putting the item into the knapsack is better, and the number of solutions transitions from $g_{i-1,j-v}$.

If $f_{i,j} = f_{i-1,j}$ and $f_{i,j} = f_{i-1,j-v}+w$, then both putting and not putting the item can achieve the optimum, and the number of solutions transitions from both $g_{i-1,j}$ and $g_{i-1,j-v}$.

Initial condition:

```cpp
memset(f, 0xcf, sizeof(f));
// Since we are maximizing, initialize to negative infinity to avoid transitions
// from states that are not filled exactly. For minimization, initialize to
// positive infinity, 0x3f.
f[0] = 0;
g[0] = 1;  // Choosing nothing is one solution.
```

Because the maximum knapsack volume may be impossible to fill, the optimal answer is not necessarily $f_m$.

Finally, find the value of the optimal solution and sum all entries in the $g_j$ array whose corresponding state reaches that optimum.

???+ note "Implementation"
    ```cpp
    for (int i = 0; i < N; i++) {
      for (int j = V; j >= v[i]; j--) {
        int tmp = std::max(dp[j], dp[j - v[i]] + w[i]);
        int c = 0;
        if (tmp == dp[j]) c += cnt[j];                       // Transition from dp[j].
        if (tmp == dp[j - v[i]] + w[i]) c += cnt[j - v[i]];  // Transition from dp[j-v[i]].
        dp[j] = tmp;
        cnt[j] = c;
      }
    }
    int max = 0;  // Find the optimal value.
    for (int i = 0; i <= V; i++) {
      max = std::max(max, dp[i]);
    }
    int res = 0;
    for (int i = 0; i <= V; i++) {
      if (dp[i] == max) {
        res += cnt[i];  // Sum the number of optimal solutions.
      }
    }
    ```

#### The $k$-th Best Knapsack Solution

Ordinary 0-1 knapsack asks for the optimal solution. By slightly modifying ordinary knapsack DP and adding one dimension to record the top $k$ solutions for the current state, we obtain an algorithm for finding the $k$-th best solution of 0-1 knapsack.

Specifically, $\mathit{dp_{i,j,k}}$ records the $k$-th largest value sum obtainable among the first $i$ items when the total volume of chosen items is $j$. This state can be understood as extending the ordinary 0-1 knapsack state $\mathit{dp_{i,j}}$, which stores only one value, into a sorted sequence of optimal values. During the transition, ordinary knapsack computes $\mathit{dp_{i,j}}=\max(\mathit{dp_{i-1,j}},\mathit{dp_{i-1,j-v_{i}}}+w_{i})$. Here, instead, we merge the two decreasing sequences of size $k$, $\mathit{dp_{i-1,j}}$ and $\mathit{dp_{i-1,j-v_{i}}}+w_i$, and keep the largest $k$ values in $\mathit{dp_{i,j}}$. This step uses two pointers and costs $O(k)$, so the total time complexity is $O(nmk)$. As in ordinary knapsack, the first dimension can be compressed, giving space complexity $O(mk)$.

??? note "Example [HDU 2639 Bone Collector II](https://acm.hdu.edu.cn/showproblem.php?pid=2639)"
    Find the strict $k$-th best solution of 0-1 knapsack. $n \leq 100,v \leq 1000,k \leq 30$

??? note "Implementation"
    ```cpp
    memset(dp, 0, sizeof(dp));
    int i, j, p, x, y, z;
    scanf("%d%d%d", &n, &m, &K);
    for (i = 0; i < n; i++) scanf("%d", &w[i]);
    for (i = 0; i < n; i++) scanf("%d", &c[i]);
    for (i = 0; i < n; i++) {
      for (j = m; j >= c[i]; j--) {
        for (p = 1; p <= K; p++) {
          a[p] = dp[j - c[i]][p] + w[i];
          b[p] = dp[j][p];
        }
        a[p] = b[p] = -1;
        x = y = z = 1;
        while (z <= K && (a[x] != -1 || b[y] != -1)) {
          if (a[x] > b[y])
            dp[j][z] = a[x++];
          else
            dp[j][z] = b[y++];
          if (dp[j][z] != dp[j][z - 1]) z++;
        }
      }
    }
    printf("%d\n", dp[m][K]);
    ```

## References and Notes

-   [Nine Lectures on the Knapsack Problem - Cui Tianyi](https://github.com/tianyicui/pack).
