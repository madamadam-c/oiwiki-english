author: Ir1d, Anguei, hsfzLZH1

## Definition

A **system of difference constraints** is a special system of $n$ linear inequalities in $n$ variables $x_1, x_2, \dots, x_n$ with $m$ constraints. Each constraint is formed by the difference of two variables, in the form $x_i - x_j \leq c_k$, where $1 \leq i, j \leq n, i \neq j, 1 \leq k \leq m$ and $c_k$ is a constant (which can be non-negative or negative). The problem is to find a solution $x_1 = a_1, x_2 = a_2, \dots, x_n = a_n$ that satisfies all constraints, or determine that no solution exists.

Each constraint $x_i - x_j \leq c_k$ can be rewritten as $x_i \leq x_j + c_k$, which is very similar to the triangle inequality $dist[y] \leq dist[x] + z$ in single-source shortest paths. Therefore, we can treat each variable $x_i$ as a node in a graph, and for each constraint $x_i -_j \leq c_k$, add a directed edge from node $j$ to node $i$ with weight $c_k$.

Note that if $\{a_1, a_2, \dots, a_n\}$ is a solution to the system, then for any constant $d$, $\{a_1 + d, a_2 + d, \dots, a_n + d\}$ is also a solution, because the $d$ cancels out when taking differences.

## Process

Set $dist[0] = 0$ and add an edge of weight $0$ from the source to every node, then run single-source shortest path. If the graph contains a negative cycle, the system has no solution; otherwise, $x_i = dist[i]$ is a valid solution.

## Properties

Typically, Bellman-Ford or queue-optimized Bellman-Ford (commonly known as SPFA, which is fast on random graphs) is used to detect negative cycles. The worst-case time complexity is $O(nm)$.

## Common Variations

### Example [Luogu P1993 Little K's Farm](https://www.luogu.com.cn/problem/P1993)

Problem: Solve a system of difference constraints with $m$ constraints, each in the form $x_a - x_b \geq c_k$, $x_a - x_b \leq c_k$, or $x_a = x_b$. Determine if a solution exists.

|             Meaning            |                  Transformation                 |                Add Edge               |
| :---------------------------: | :-------------------------------------------: | :-----------------------------------: |
| $x_a - x_b \geq c$           |             $x_b - x_a \leq -c$               |        `add(a, b, -c);`              |
| $x_a - x_b \leq c$           |              $x_a - x_b \leq c$               |        `add(b, a, c);`               |
|       $x_a = x_b$             | $x_a - x_b \leq 0, \space x_b - x_a \leq 0$   | `add(b, a, 0), add(a, b, 0);`        |

Run negative cycle detection; if no negative cycle exists, output `Yes`, otherwise output `No`.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/graph/code/diff-constraints/diff-constraints_1.cpp"
    ```

### Example [P4926 [1007] Multiplier Measurement](https://www.luogu.com.cn/problem/P4926)

Ignoring binary search and other techniques, we only discuss solving the difference system $\frac{x_i}{x_j} \leq c_k$.

Taking the logarithm of each $x_i$, $x_j$, and $c_k$ transforms multiplication into addition: $\log x_i - \log x_j \leq \log c_k$, which can then be solved using difference constraints.

## Bellman-Ford Negative Cycle Detection Implementation

Below is the code for detecting negative cycles using the Bellman-Ford algorithm. Ensure the graph is connected before calling.

???+ note "Implementation"
    === "C++"
        ```cpp
        bool Bellman_Ford() {
          for (int i = 0; i < n; i++) {
            bool jud = false;
            for (int j = 1; j <= n; j++)
              for (int k = h[j]; ~k; k = nxt[k])
                if (dist[j] > dist[p[k]] + w[k])
                  dist[j] = dist[p[k]] + w[k], jud = true;
            if (!jud) break;
          }
          for (int i = 1; i <= n; i++)
            for (int j = h[i]; ~j; j = nxt[j])
              if (dist[i] > dist[p[j]] + w[j]) return false;
          return true;
        }
        ```

    === "Python"
        ```python
        def Bellman_Ford():
            for i in range(0, n):
                jud = False
                for j in range(1, n + 1):
                    while ~k:
                        k = h[j]
                        if dist[j] > dist[p[k]] + w[k]:
                            dist[j] = dist[p[k]] + w[k]
                            jud = True
                        k = nxt[k]
                if jud == False:
                    break
            for i in range(1, n + 1):
                while ~j:
                    j = h[i]
                    if dist[i] > dist[p[j]] + w[j]:
                        return False
                    j = nxt[j]
            return True
        ```

## Exercises

[Usaco2006 Dec Wormholes](https://loj.ac/problem/10085)

[「SCOI2011」Candy](https://loj.ac/problem/2436)

[POJ 1364 King](http://poj.org/problem?id=1364)

[POJ 2983 Is the Information Reliable?](http://poj.org/problem?id=2983)