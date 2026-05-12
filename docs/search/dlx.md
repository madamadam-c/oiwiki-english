author: LeverImmy, 383494

This page introduces the exact cover problem, the repeated cover problem, Algorithm X for solving these two problems, and the doubly linked cross list Dancing Links used to optimize Algorithm X. This page also introduces how to use DLX with modeling to solve some search problems.

## Exact Cover Problem

### Definition

The exact cover problem is: given many sets $S_i (1 \le i \le n)$ and a set $X$, find an unordered tuple $(T_1, T_2, \cdots , T_m)$ satisfying the following conditions:

1.  $\forall i, j \in [1, m],T_i\bigcap T_j = \varnothing (i \neq j)$
2.  $X = \bigcup\limits_{i = 1}^{m}T_i$
3.  $\forall i \in[1, m], T_i \in \{S_1, S_2, \cdots, S_n\}$

### Explanation

For example, if we are given

$$
\begin{aligned}
  & S_1 = \{5, 9, 17\} \\
  & S_2 = \{1, 8, 119\} \\
  & S_3 = \{3, 5, 17\} \\
  & S_4 = \{1, 8\} \\
  & S_5 = \{3, 119\} \\
  & S_6 = \{8, 9, 119\} \\
  & X = \{1, 3, 5, 8, 9, 17, 119\}
\end{aligned}
$$

then $(S_1, S_4, S_5)$ is a valid solution.

### Problem Transformation

Discretizing all numbers in $\bigcup\limits_{i = 1}^{n}S_i$ gives the following model:

> Given a 01 matrix, you may choose some rows so that each column[^note1] has exactly one 1 in the end.
> For example, modeling the example above gives the following matrix:

$$
\begin{pmatrix}
0 & 0 & 1 & 0 & 1 & 1 & 0 \\
1 & 0 & 0 & 1 & 0 & 0 & 1 \\
0 & 1 & 1 & 0 & 0 & 1 & 0 \\
1 & 0 & 0 & 1 & 0 & 0 & 0 \\
0 & 1 & 0 & 0 & 0 & 0 & 1 \\
0 & 0 & 0 & 1 & 1 & 0 & 1
\end{pmatrix}
$$

> Here row $i$ represents $S_i$, and the entries in this row represent $[1 \in S_i],[3 \in S_i],[5 \in S_i],\cdots,[119 \in S_i]$ in order.

### Implementation

#### Brute Force 1

One method is to enumerate which rows are selected, and finally check whether the solution is valid.

Because each row has two states, selected or not selected, the time complexity of enumerating rows is $O(2^n)$.

Each check requires $O(nm)$ time. Therefore, the total complexity is $O(nm\cdot2^n)$.

??? note "Implementation"
    ```cpp
    int ok = 0;
    for (int state = 0; state < 1 << n; ++state) {  // Enumerate whether each row is selected
      for (int i = 1; i <= n; ++i)
        if ((1 << i - 1) & state)
          for (int j = 1; j <= m; ++j) a[i][j] = 1;
      int flag = 1;
      for (int j = 1; j <= m; ++j)
        for (int i = 1, bo = 0; i <= n; ++i)
          if (a[i][j]) {
            if (bo)
              flag = 0;
            else
              bo = 1;
          }
      if (!flag)
        continue;
      else {
        ok = 1;
        for (int i = 1; i <= n; ++i)
          if ((1 << i - 1) & state) printf("%d ", i);
        puts("");
      }
      memset(a, 0, sizeof(a));
    }
    if (!ok) puts("No solution.");
    ```

#### Brute Force 2

Considering the special nature of a 01 matrix, each row can be regarded as an $m$-bit binary number.

Therefore, the original problem is transformed into:

> Given $n$ $m$-bit binary numbers, choose some numbers so that the bitwise AND of any two numbers is 0, and the bitwise OR of all selected numbers is $2^m - 1$. `tmp` denotes the bitwise OR of the selected binary numbers so far.

Because each row has two states, selected or not selected, the time complexity of enumerating rows is $O(2^n)$.

Each computation of `tmp` requires $O(n)$ time. Therefore, the total complexity is $O(n\cdot2^n)$.

??? note "Implementation"
    ```cpp
    int ok = 0;
    for (int i = 1; i <= n; ++i)
      for (int j = m; j >= 1; --j) num[i] = num[i] << 1 | a[i][j];
    for (int state = 0; state < 1 << n; ++state) {
      int tmp = 0;
      bool flag = true;
      for (int i = 1; i <= n; ++i)
        if ((1 << i - 1) & state) {
          if (tmp & num[i]) {
            flag = false;
            break;
          }
          tmp |= num[i];
        }
      if (flag && tmp == (1 << m) - 1) {
        ok = 1;
        for (int i = 1; i <= n; ++i)
          if ((1 << i - 1) & state) printf("%d ", i);
        puts("");
      }
    }
    if (!ok) puts("No solution.");
    ```

## Repeated Cover Problem

The repeated cover problem is similar to the exact cover problem, but it has no restriction on element overlap. The [Algorithm X](#algorithm-x) introduced below was originally designed for exact cover problems, but with some modifications and optimizations (marked where they appear), it can also efficiently solve repeated cover problems.

## Algorithm X

Donald E. Knuth proposed Algorithm X. Its idea is similar to the brute-force methods above, but it is easier to optimize.

### Process

Continuing with the example above, we obtain the following 01 matrix:

$$
\begin{pmatrix}
  0 & 0 & 1 & 0 & 1 & 1 & 0 \\
  1 & 0 & 0 & 1 & 0 & 0 & 1 \\
  0 & 1 & 1 & 0 & 0 & 1 & 0 \\
  1 & 0 & 0 & 1 & 0 & 0 & 0 \\
  0 & 1 & 0 & 0 & 0 & 0 & 1 \\
  0 & 0 & 0 & 1 & 1 & 0 & 1
\end{pmatrix}
$$

1.  At this point, the first row has $3$ $1$s, the second row has $3$ $1$s, the third row has $3$ $1$s, the fourth row has $2$ $1$s, the fifth row has $2$ $1$s, and the sixth row has $3$ $1$s. Select the first row, delete it, and mark all columns containing a $1$ in this row.

    $$
    \begin{pmatrix}
      \color{Blue}0 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 & \color{Blue}0 \\
      1 & 0 & \color{Red}0 & 1 & \color{Red}0 & \color{Red}0 & 1 \\
      0 & 1 & \color{Red}1 & 0 & \color{Red}0 & \color{Red}1 & 0 \\
      1 & 0 & \color{Red}0 & 1 & \color{Red}0 & \color{Red}0 & 0 \\
      0 & 1 & \color{Red}0 & 0 & \color{Red}0 & \color{Red}0 & 1 \\
      0 & 0 & \color{Red}0 & 1 & \color{Red}1 & \color{Red}0 & 1
      \end{pmatrix}
    $$

2.  Select all marked columns, delete them, and mark the rows containing $1$ in these columns (marking is not needed for repeated cover problems).

    $$
    \begin{pmatrix}
      \color{Blue}0 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 & \color{Blue}0 \\
      1 & 0 & \color{Blue}0 & 1 & \color{Blue}0 & \color{Blue}0 & 1 \\
      \color{Red}0 & \color{Red}1 & \color{Blue}1 & \color{Red}0 & \color{Blue}0 & \color{Blue}1 & \color{Red}0 \\
      1 & 0 & \color{Blue}0 & 1 & \color{Blue}0 & \color{Blue}0 & 0 \\
      0 & 1 & \color{Blue}0 & 0 & \color{Blue}0 & \color{Blue}0 & 1 \\
      \color{Red}0 & \color{Red}0 & \color{Blue}0 & \color{Red}1 & \color{Blue}1 & \color{Blue}0 & \color{Red}1
    \end{pmatrix}
    $$

3.  Select all marked rows and delete them.

    $$
    \begin{pmatrix}
      \color{Blue}0 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 & \color{Blue}0 \\
      1 & 0 & \color{Blue}0 & 1 & \color{Blue}0 & \color{Blue}0 & 1 \\
      \color{Blue}0 & \color{Blue}1 & \color{Blue}1 & \color{Blue}0 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 \\
      1 & 0 & \color{Blue}0 & 1 & \color{Blue}0 & \color{Blue}0 & 0 \\
      0 & 1 & \color{Blue}0 & 0 & \color{Blue}0 & \color{Blue}0 & 1 \\
      \color{Blue}0 & \color{Blue}0 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 & \color{Blue}0 & \color{Blue}1
    \end{pmatrix}
    $$

    **This means that this row has been selected, and the columns containing all $1$s in this row cannot have any other $1$s**.

    Thus, we obtain a new smaller 01 matrix:

    $$
    \begin{pmatrix}
      1 & 0 & 1 & 1 \\
      1 & 0 & 1 & 0 \\
      0 & 1 & 0 & 1
    \end{pmatrix}
    $$

4.  At this point, the first row (the original second row) has $3$ $1$s, the second row (the original fourth row) has $2$ $1$s, and the third row (the original fifth row) has $2$ $1$s. Select the first row (the original second row), delete it, and mark all columns containing a $1$ in this row.

    $$
    \begin{pmatrix}
      \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 \\
      \color{Red}1 & 0 & \color{Red}1 & \color{Red}0 \\
      \color{Red}0 & 1 & \color{Red}0 & \color{Red}1
    \end{pmatrix}
    $$

5.  Select all marked columns, delete them, and mark the rows containing $1$ in these columns.

    $$
    \begin{pmatrix}
      \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 \\
      \color{Blue}1 & \color{Red}0 & \color{Blue}1 & \color{Blue}0 \\
      \color{Blue}0 & \color{Red}1 & \color{Blue}0 & \color{Blue}1
    \end{pmatrix}
    $$

6.  Select all marked rows and delete them.

    $$
    \begin{pmatrix}
      \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 \\
      \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 \\
      \color{Blue}0 & \color{Blue}1 & \color{Blue}0 & \color{Blue}1
    \end{pmatrix}
    $$

    This gives an empty matrix. However, the last deleted row `1 0 1 1` was not all $1$s, which means the selection was wrong.

    $$
    \begin{pmatrix}
    \end{pmatrix}
    $$

7.  Backtrack to step 4 and consider selecting the second row (the original fourth row). Delete it and mark all columns containing a $1$ in this row.

    $$
    \begin{pmatrix}
      \color{Red}1 & 0 & \color{Red}1 & 1 \\
      \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 \\
      \color{Red}0 & 1 & \color{Red}0 & 1
    \end{pmatrix}
    $$

8.  Select all marked columns, delete them, and mark the rows containing $1$ in these columns.

    $$
    \begin{pmatrix}
      \color{Blue}1 & \color{Red}0 & \color{Blue}1 & \color{Red}1 \\
      \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 \\
      \color{Blue}0 & 1 & \color{Blue}0 & 1
    \end{pmatrix}
    $$

9.  Select all marked rows and delete them.

    $$
    \begin{pmatrix}
      \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 \\
      \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 \\
      \color{Blue}0 & 1 & \color{Blue}0 & 1
      \end{pmatrix}
    $$

    Thus, we obtain the following matrix:

    $$
    \begin{pmatrix}
      1 & 1
    \end{pmatrix}
    $$

10. At this point, the first row (the original fifth row) has $2$ $1$s. Delete all of them to obtain an empty matrix:

    $$
    \begin{pmatrix}
    \end{pmatrix}
    $$

11. In the previous deletion, the deleted row was all $1$s, so the algorithm succeeds and terminates.

    The answer is the three deleted rows: $1, 4, 5$.

It is strongly recommended to simulate the process of deleting, restoring, and backtracking through the matrix yourself before continuing.

From the steps above, the process of Algorithm X can be summarized as follows:

1.  For the current matrix $M$, select and mark a row $r$, and add $r$ to $S$.
2.  If all choices of $r$ have been tried and no solution is found, terminate the algorithm and output that there is no solution.
3.  Mark the rows $r_i$ and columns $c_i$ related to $r$ (related rows and columns are defined in the same way as in step 2 of [Algorithm X](#process); the same applies below).
4.  Delete all marked rows and columns to obtain a new matrix $M'$.
5.  If $M'$ is empty and $r$ is all $1$s, terminate the algorithm and output the set $S$ consisting of the deleted rows.

    If $M'$ is empty and $r$ is not all $1$s, restore the rows $r_i$ and columns $c_i$ related to $r$, and jump to step 1.

    If $M'$ is not empty, jump to step 1.

It is easy to see that Algorithm X requires many operations that delete rows, delete columns, restore rows, and restore columns.

A naive idea is to store the matrix in a two-dimensional array, and then use four arrays to store, for each row, the indices of adjacent rows, so that each deletion and restoration only needs to update elements in the four arrays. However, because in matrices from typical problems the number of 0s is far greater than the number of 1s, the space complexity of this approach is unacceptable.

Donald E. Knuth came up with using a doubly linked cross list to maintain these operations.

The process of continuously jumping on the doubly linked cross list is vividly compared to "dancing", so the doubly linked cross list used to optimize Algorithm X is also called "Dancing Links".

## Algorithm X Optimized by Dancing Links

### Preprocessor Directive

```cpp
#define IT(i, A, x) for (i = A[x]; i != x; i = A[i])
```

### Definition

There are four pointer fields in a doubly linked cross list, pointing to the elements above, below, to the left, and to the right. Each element $i$ corresponds to a cell in the whole doubly linked cross list system, so the column and row containing $i$ must also be represented, as shown in the figure:

![dlx-1.svg](./images/dlx-1.svg)

A large doubly linked list is more complex:

![dlx-2.svg](./images/dlx-2.svg)

Each row has a row-head indicator, and each column has a column indicator.

The row-head indicator is `first[]`, and the column indicators are the newly created $c + 1$ sentinel nodes. It is worth noting that **a row-head indicator is not a sentinel node in the linked list**. It is virtual, similar to the `first[]` array in an adjacency list, and **directly points** to the first element in that row.

Meanwhile, each column has a `siz[]` value indicating the number of elements in that column.

Specially, node $0$ having no right node is equivalent to this Dancing Links structure being empty.

```cpp
constexpr int MS = 1e5 + 5;
int n, m, idx, first[MS], siz[MS];
int L[MS], R[MS], U[MS], D[MS];
int col[MS], row[MS];
```

### Process

#### remove Operation

`remove(c)` means deleting column $c$ and the rows and columns related to it in Dancing Links.

First delete $c$. At this point:

-   The right node of the node to the left of $c$ should be the right node of $c$.
-   The left node of the node to the right of $c$ should be the left node of $c$.

That is, `L[R[c]] = L[c], R[L[c]] = R[c];`.

![dlx-3.svg](./images/dlx-3.svg)

Then go downward along this column and delete every row encountered.

How do we delete each row? Enumerate the pointer $j$ in the current row. At this point:

-   The down node of the node above $j$ should be the down node of $j$.
-   The up node of the node below $j$ should be the up node of $j$.

Remember to update the number of elements in each column.

That is, `U[D[j]] = U[j], D[U[j]] = D[j], --siz[col[j]];`.

![dlx-4.svg](./images/dlx-4.svg)

The code implementation of the `remove` function is as follows:

???+ note "Implementation"
    ```cpp
    void remove(const int &c) {
      int i, j;
      L[R[c]] = L[c], R[L[c]] = R[c];
      // Traverse this column from top to bottom
      IT(i, D, c)
      // Traverse this row from left to right
      IT(j, R, i)
      U[D[j]] = U[j], D[U[j]] = D[j], --siz[col[j]];
    }
    ```

#### recover Operation

`recover(c)` means restoring column $c$ and the rows and columns related to it in Dancing Links.

`recover(c)` is the inverse operation of `remove(c)`, so it is not repeated here.

**It is worth noting that the order of all operations in** `recover(c)` **is exactly the reverse of the operations in** `remove(c)`.

The code implementation of `recover(c)` is as follows:

???+ note "Implementation"
    ```cpp
    void recover(const int &c) {
      int i, j;
      IT(i, U, c) IT(j, L, i) U[D[j]] = D[U[j]] = j, ++siz[col[j]];
      L[R[c]] = R[L[c]] = c;
    }
    ```

#### build Operation

`build(r, c)` means creating a new Dancing Links structure of size $r \times c$, that is, with $r$ rows and $c$ columns.

Create $c + 1$ new nodes as column indicators.

The left node of point $i$ is $i - 1$, the right node is $i + 1$, the up node is $i$, and the down node is $i$. Specially, the left node of node $0$ is $c$, and the right node of node $c$ is $0$.

Thus we obtain a circular doubly linked list:

![dlx-5.svg](./images/dlx-5.svg)

This initializes a Dancing Links structure.

The code implementation of `build(r, c)` is as follows:

???+ note "Implementation"
    ```cpp
    void build(const int &r, const int &c) {
      n = r, m = c;
      for (int i = 0; i <= c; ++i) {
        L[i] = i - 1, R[i] = i + 1;
        U[i] = D[i] = i;
      }
      L[0] = c, R[c] = 0, idx = c;
      memset(first, 0, sizeof(first));
      memset(siz, 0, sizeof(siz));
    }
    ```

#### insert Operation

`insert(r, c)` means inserting a node at row $r$, column $c$.

The insertion operation has two cases:

-   If row $r$ has no elements, insert an element directly and make `first[r]` point to this element.

    This can be implemented with `first[r] = L[idx] = R[idx] = idx;`.

-   If row $r$ has elements, connect this new element with $c$ and $first(r)$ in a special way.

    Let this new element be $idx$, then:

    -   Insert $idx$ directly below $c$. At this point:

        -   The node below $idx$ is the original down node of $c$.
        -   The up node of the node below $idx$ (that is, the original down node of $c$) is $idx$.
        -   The up node of $idx$ is $c$.
        -   The down node of $c$ is $idx$.

        Remember to record the column and row containing $idx$, and update the number of elements in this column.

        ```cpp
        col[++idx] = c, row[idx] = r, ++siz[c];
        U[idx] = c, D[idx] = D[c], U[D[c]] = idx, D[c] = idx;
        ```

        **Readers are strongly advised to fully understand the order of these steps before continuing.**

    -   Insert $idx$ directly to the right of $first(r)$. At this point:

        -   The node to the right of $idx$ is the original right node of $first(r)$.
        -   The left node of the original right node of $first(r)$ is $idx$.
        -   The left node of $idx$ is $first(r)$.
        -   The right node of $first(r)$ is $idx$.

        ```cpp
        L[idx] = first[r], R[idx] = R[first[r]];
        L[R[first[r]]] = idx, R[first[r]] = idx;
        ```

        **Readers are strongly advised to fully understand the order of these steps before continuing.**

The `insert(r, c)` operation can be understood with the help of the figure:

![dlx-6.svg](./images/dlx-6.svg)

Pay attention to the directions of the curved arrows.

The code implementation of `insert(r, c)` is as follows:

???+ note "Implementation"
    ```cpp
    void insert(const int &r, const int &c) {
      row[++idx] = r, col[idx] = c, ++siz[c];
      U[idx] = c, D[idx] = D[c], U[D[c]] = idx, D[c] = idx;
      if (!first[r])
        first[r] = L[idx] = R[idx] = idx;
      else {
        L[idx] = first[r], R[idx] = R[first[r]];
        L[R[first[r]]] = idx, R[first[r]] = idx;
      }
    }
    ```

#### dance Operation

`dance()` is the process of recursively deleting and restoring rows and columns.

1.  If node $0$ has no right node, the matrix is empty; record the answer and return.
2.  Select the column with the fewest elements and delete this column.
3.  Traverse all rows in this column that have a $1$, and enumerate whether each is selected.
4.  Recursively call `dance()`. If it is feasible, return; if not, restore the selected row.
5.  If there is no solution, return.

The code implementation of `dance()` is as follows:

???+ note "Implementation"
    ```cpp
    bool dance(int dep) {
      int i, j, c = R[0];
      if (!R[0]) {
        ans = dep;
        return true;
      }
      IT(i, R, 0) if (siz[i] < siz[c]) c = i;
      remove(c);
      IT(i, D, c) {
        stk[dep] = row[i];
        IT(j, R, i) remove(col[j]);
        if (dance(dep + 1)) return true;
        IT(j, L, i) recover(col[j]);
      }
      recover(c);
      return false;
    }
    ```

Here `stk[]` is used to record the answer.

Note that each time we preferentially choose the column with the fewest elements to delete. This gives the program some heuristic behavior and minimizes the branching of the search tree.

For repeated cover problems, an evaluation function (similar to the one in [A\*](astar.md)) can be used for pruning during search: if the number of selected rows in the current best case already exceeds the current optimal solution, return directly.

## Template

??? note "[Template code](https://www.luogu.com.cn/problem/P4929)"
    ```cpp
    --8<-- "docs/search/code/dlx/dlx_1.cpp"
    ```

## Properties

The number of recursive and backtracking steps in DLX is related to the number of $1$s in the matrix, and is unrelated to parameters such as $r, c$ of the matrix. Therefore, its time complexity is **exponential**. The theoretical complexity is roughly around $O(c^n)$, where $c$ is a constant very close to $1$, and $n$ is the number of $1$s in the matrix.

In practice, however, DLX performs well and can generally solve most problems.

## Modeling

The difficulty of DLX lies not entirely in building the linked list, but in modeling.

Please make sure you have fully mastered the DLX template before continuing.

Whenever we get a problem, we should consider what the rows and columns represent:

-   Rows represent *decisions*, because each row corresponds to a set, and therefore corresponds to selecting or not selecting it.

-   Columns represent *states*, because column $i$ corresponds to some condition $P_i$.

For a certain row, because the values in different columns vary, we **define a decision through different states**.

### Example 1 [P1784 Sudoku](https://www.luogu.com.cn/problem/P1784)

??? note "Solution idea"
    First consider what the decisions are.
    
    In this problem, each decision can be represented by an ordered triple of the form $(r, c, w)$.
    
    Note that the "block" is not a parameter of the decision, because it **can be represented by each determined $(r, c)$**.
    
    Therefore, there are $9 \times 9 \times 9 = 729$ rows.
    
    Next consider what the states are.
    
    Think about what effects the decision $(r, c, w)$ will cause. Let $b$ be the block containing $(r, c)$.
    
    1.  Row $r$ uses a $w$ (represented by $9 \times 9 = 81$ columns).
    2.  Column $c$ uses a $w$ (represented by $9 \times 9 = 81$ columns).
    3.  Block $b$ uses a $w$ (represented by $9 \times 9 = 81$ columns).
    4.  A number is filled into $(r, c)$ (represented by $9 \times 9 = 81$ columns).
    
    Therefore, there are $81 \times 4 = 324$ columns and a total of $729 \times 4 = 2916$ $1$s.
    
    At this point, we have successfully transformed the $9 \times 9$ Sudoku problem into an exact cover problem with **$729$ rows, $324$ columns, and a total of $2916$ $1$s**.

??? note "Reference code"
    ```cpp
    --8<-- "docs/search/code/dlx/dlx_2.cpp"
    ```

### Example 2 [Target Sudoku](https://www.luogu.com.cn/problem/P1074)

??? note "Solution idea"
    The model construction for this problem is **exactly the same** as [Sudoku](https://www.luogu.com.cn/problem/P1784). The main difference lies in updating the answer.
    
    For this problem, create a weight array. Each time a Sudoku solution is found,
    
    multiply the number at each position by the corresponding weight and add it to the answer.

??? note "Reference code"
    ```cpp
    --8<-- "docs/search/code/dlx/dlx_3.cpp"
    ```

### Example 3 [NOI2005 Smart Bead Game](https://www.luogu.com.cn/problem/P4205)

??? note "Solution idea"
    Definition: the shape of a smart bead given in the problem is called this smart bead's *standard shape*.
    
    Obviously, we can change the shape of this smart bead by changing two parameters: $d$ (the number of clockwise rotations by $90^{\circ}$) and $f$ (whether it is flipped horizontally).
    
    Again, first consider what the decisions are.
    
    In this problem, each decision can be represented by an ordered 5-tuple of the form $(v, d, f, i)$.
    
    It represents that the upper-left position of the *standard shape* of the $i$-th smart bead has index $v$, and it has been rotated clockwise by $90^{\circ}$ a total of $d$ times.
    
    Conveniently, we can set $f = 1$ for no horizontal flip and $f = -1$ for a horizontal flip, simplifying the code.
    
    Therefore, there are $55 \times 4 \times 2 \times 12 = 5280$ rows.
    
    Note that because of some invalid placements, such as $(1, 0, 1, 4)$,
    
    **in actual operation, even an empty smart bead board only needs $2730$ rows to be constructed.**
    
    Next consider what the states are.
    
    The states in this problem are relatively simple.
    
    Think about what effects the decision $(v, d, f, i)$ will cause.
    
    1.  Some cells are occupied (represented by $55$ columns).
    2.  The $i$-th smart bead is used (represented by $12$ columns).
    
    Therefore, there are $55 + 12 = 67$ columns and a total of $5280 \times (5 + 1) = 31680$ $1$s.
    
    At this point, we have successfully transformed the smart bead game into an exact cover problem with **$5280$ rows, $67$ columns, and a total of $31680$ $1$s**.

??? note "Reference code"
    ```cpp
    --8<-- "docs/search/code/dlx/dlx_4.cpp"
    ```

## Exercises

-   [SUDOKU - Sudoku](https://www.spoj.com/problems/SUDOKU/)
-   ["kuangbin takes you flying" Topic 3: Dancing Links](https://vjudge.net/contest/65998#overview)

## External Links

-   [Dancing Links Algorithm for Solving Exact Cover Problems - Wancang Yishu](https://www.cnblogs.com/grenet/p/3145800.html)
-   [Search: DLX Algorithm - Jingting Fengyin](https://www.cnblogs.com/aininot260/p/9629926.html)
-   [Training Guide for Algorithm Competitions](https://book.douban.com/subject/35431537/)

## Notes

[^note1]: Terminology differs across regions: in Taiwan, column may be called a vertical row, and row may be called a horizontal row.
