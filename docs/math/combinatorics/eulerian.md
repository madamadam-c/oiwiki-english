???+ warning "Note"
    The Eulerian numbers below specifically refer to Eulerian numbers. Be careful to distinguish this from Euler numbers and Euler's number (referring to mathematical constants related to Euler such as $\gamma$ or $\mathrm{e}$).

In combinatorics, the **Eulerian Number** $A(n, m)$ is the number of permutations of $n$ elements where exactly $m$ elements are greater than the previous element (having $m$ "ascents"). It is defined as:

$$
A(n, m) = 
\left\langle 
\begin{matrix}
  n\\
  m - 1
\end{matrix}
\right\rangle
$$

For example, there are exactly 4 permutations of numbers 1 to 3 where exactly one element is greater than the previous element:

| Permutation | Adjacent elements satisfying condition | Count |
| ----- | ----------- | -- |
| 1 2 3 | 1, 2 & 2, 3 | 2  |
| 1 3 2 | 1, 3        | 1  |
| 2 1 3 | 1, 3        | 1  |
| 2 3 1 | 2, 3        | 1  |
| 3 1 2 | 1, 2        | 1  |
| 3 2 1 |             | 0  |

So according to the definition of $A(n, m)$: if $n$ equals 3 and $m$ equals 1, the Eulerian number value is 4, meaning there are 4 permutations with exactly 1 element greater than the previous element.

For relatively small values of $n$ and $m$, we can directly obtain the results:

| $A(n, m)$ | Permutations satisfying the requirement                         | Count |
| --------- | -------------------------------------------- | -- |
| $A(1, 0)$ | $(1)$                                        | 1  |
| $A(2, 0)$ | $(2, 1)$                                     | 1  |
| $A(2, 1)$ | $(1, 2)$                                     | 1  |
| $A(3, 0)$ | $(3, 2, 1)$                                  | 1  |
| $A(3, 1)$ | $(1, 3, 2), (2, 1, 3), (2, 3, 1), (3, 1, 2)$ | 4  |
| $A(3, 2)$ | $(1, 2, 3)$                                  | 1  |

## Formulas

Eulerian numbers can be calculated using recurrence or recursion.

First, when $m \ge n$ or $n = 0$, there are no permutations satisfying the condition, i.e., the Eulerian number is $0$.

Second, when $m = 0$, only descending permutations satisfy the condition, i.e., the Eulerian number is $1$.

Finally, consider inserting $n$ into a permutation of $n-1$ to obtain a permutation of $n$. Since inserting $n$ can increase the Eulerian number by at most 1, $A(n, m)$ can only be obtained from transitions from $A(n-1, m-1)$ and $A(n-1, m)$.

Consider the position of $n$: when $p_{i-1} < p_i$, if $n$ is inserted before $p_i$, i.e., inserted into an "ascent", the Eulerian number of the permutation does not change. Also, inserting $n$ at the beginning of the permutation does not change the Eulerian number. Otherwise, if $n$ is inserted at other positions, the Eulerian number increases by $1$.

Consider transitioning from $A(n-1, m-1)$ to $A(n, m)$: at this time, we need to increase the Eulerian number by $1$. At this time, $n$ cannot be inserted into an "ascent" or at the beginning of the permutation, so there are $n - (m-1) - 1 = n - m$ ways.

Consider transitioning from $A(n-1, m)$ to $A(n, m)$: at this time, we need to keep the Eulerian number unchanged, so $n$ can only be inserted into an "ascent" or at the beginning of the permutation, with a total of $m + 1$ ways.

In summary, we have

$$
A(n, m) = \begin{cases}
    0, & m > n \text{ or } n = 0, \\
    1, & m = 0, \\
    (n-m) \cdot A(n-1, m-1) + (m+1) \cdot A(n-1, m), & \text{otherwise}.
\end{cases}
$$

## Implementation

=== "C++"
    ```cpp
    int eulerianNumber(int n, int m) {
      if (m >= n || n == 0) return 0;
      if (m == 0) return 1;
      return (((n - m) * eulerianNumber(n - 1, m - 1)) +
              ((m + 1) * eulerianNumber(n - 1, m)));
    }
    ```

=== "Python"
    ```python
    def eulerianNumber(n, m):
        if m >= n or n == 0:
            return 0
        if m == 0:
            return 1
        return ((n - m) * eulerianNumber(n - 1, m - 1)) + (
            (m + 1) * eulerianNumber(n - 1, m)
        )
    ```

## Exercises

-   [CF1349F1 Slime and Sequences (Easy Version)](https://codeforces.com/problemset/problem/1349/F1)
-   [CF1349F2 Slime and Sequences (Hard Version)](https://codeforces.com/problemset/problem/1349/F2)
-   [UOJ 593. 新年的军队](https://uoj.ac/problem/593)
-   [P7511 三到六](https://www.luogu.com.cn/problem/P7511)