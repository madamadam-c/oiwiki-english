Partition: The representation of a natural number $n$ as a sum of decreasing positive integers.

$$
n = r_1 + r_2 + \ldots + r_k \quad r_1 \ge r_2 \ge \ldots \ge r_k \ge 1
$$

Each positive integer in the sum is called a part.

Partition number: $p_n$. The number of ways to partition the natural number $n$.

Partitions starting from 0:

| n     | 0 | 1 | 2 | 3 | 4 | 5 | 6  | 7  | 8  |
| ----- | - | - | - | - | - | - | -- | -- | -- |
| $p_n$ | 1 | 1 | 2 | 3 | 5 | 7 | 11 | 15 | 22 |

## k-Partition Number

A partition of $n$ into exactly $k$ parts is called a k-partition number, denoted $p(n, k)$.

Obviously, the k-partition number $p(n, k)$ is also the number of solutions to the following equation:

$$
n - k = y_1 + y_2 + \ldots + y_k \quad y_1 \ge y_2 \ge \ldots \ge y_k \ge 0
$$

If there are exactly $j$ parts that are nonzero in this equation, then there are exactly $p(n - k, j)$ solutions. Therefore, we have the sum:

$$
p(n, k) = \sum_{j=0}^k p(n - k, j)
$$

Taking the difference between two consecutive sums, we get:

$$
p(n, k) = p(n - 1, k - 1) + p(n - k, k)
$$

If we list a table, each cell's value equals the value of the cell to the upper-left plus the value of the cell above in the same column of cells.

| k        | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| -------- | - | - | - | - | - | - | - | - | - |
| $p(0,k)$ | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| $p(1,k)$ | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| $p(2,k)$ | 0 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
| $p(3,k)$ | 0 | 1 | 1 | 1 | 0 | 0 | 0 | 0 | 0 |
| $p(4,k)$ | 0 | 1 | 2 | 1 | 1 | 0 | 0 | 0 | 0 |
| $p(5,k)$ | 0 | 1 | 2 | 2 | 1 | 1 | 0 | 0 | 0 |
| $p(6,k)$ | 0 | 1 | 3 | 3 | 2 | 1 | 1 | 0 | 0 |
| $p(7,k)$ | 0 | 1 | 3 | 4 | 3 | 2 | 1 | 1 | 0 |
| $p(8,k)$ | 0 | 1 | 4 | 5 | 5 | 3 | 2 | 1 | 1 |

### Example Problem

???+ note "Calculate k-partition number"
    Calculate the k-partition number $p(n, k)$. Multiple test cases, where the upper bound of $n$ is 10000 and the upper bound of $k$ is 1000, take modulo 1000007.
    
    Observing the table and recurrence formula, updating by column is better for storage. It's not hard to write the program:
    
    ```cpp
    #include <cstdio>
    #include <cstring>
    
    int p[10005][1005]; /*Number of ways to partition natural number n into k parts*/
    
    int main() {
      int n, k;
      while (~scanf("%d%d", &n, &k)) {
        memset(p, 0, sizeof(p));
        p[0][0] = 1;
        int i;
        for (i = 1; i <= n; ++i) {
          int j;
          for (j = 1; j <= k; ++j) {
            if (i - j >= 0) /*p[i-j][j] all parts are greater than 1*/
            {
              p[i][j] = (p[i - j][j] + p[i - 1][j - 1]) %
                        1000007; /*p[i-1][j-1] has at least one part equal to 1.*/
            }
          }
        }
        printf("%d\n", p[n][k]);
      }
    }
    ```

### Generating Function

From the geometric series sum formula:

$$
\frac{1}{1 - x^k} = 1 + x^k + x^{2k} + x^{3k} + \ldots
$$

$$
1 + p_1 x + p_2 x^2 + p_3 x^3 + \ldots = \frac{1}{1-x} \frac{1}{1-x^2} \frac{1}{1-x^3}\ldots
$$

For k-partition numbers, the generating function is slightly more complex. Specifically:

$$
\sum_{n,k=0}^\infty {p(n,k) x^n y^k } = \frac{1}{1-xy} \frac{1}{1-x^2 y} \frac{1}{1-x^3 y}\ldots
$$

### Ferrers Diagram

A Ferrers diagram represents each part of a partition with a row of dots. The number of dots in each row is the size of that part.

According to the definition of partitions, different rows in a Ferrers diagram are arranged in decreasing order. The longest row is at the top.

For example: The Ferrers diagram of the partition $12 = 5 + 4 + 2 + 1$.

![](./images/ferrers.jpg)

Flipping a Ferrers diagram along the diagonal gives a new Ferrers diagram called the conjugate of the original, and the new partition is called the conjugate of the original partition. Obviously, conjugation is a symmetric relation.

For example, the conjugate of the partition $12 = 5 + 4 + 2 + 1$ is the partition $12 = 4 + 3 + 2 + 2 + 1$.

Maximum k-partition number: The number of partitions of natural number $n$ where the maximum part is $k$.

According to the definition of conjugation, there is an obvious conclusion:

The maximum k-partition number is the same as the k-partition number, both equal to $p(n, k)$.

## Distinct Partition Number

Distinct partition number: $pd_n$. The number of partitions of natural number $n$ where all parts are distinct.

| n      | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| ------ | - | - | - | - | - | - | - | - | - |
| $pd_n$ | 1 | 1 | 1 | 2 | 2 | 3 | 4 | 5 | 6 |

Similarly, define distinct k-partition number $pd(n, k)$, representing the number of distinct partitions with at most $k$ parts, which is the number of solutions to:

$$
n = r_1 + r_2 + \ldots + r_k \quad r_1 > r_2 > \ldots > r_k \ge 1
$$

Exactly the same, it's also the number of solutions to:

$$
n - k = y_1 + y_2 + \ldots + y_k \quad y_1 > y_2 > \ldots > y_k \ge 0
$$

Here, unlike above, because they are distinct, in the new equation there can be at most one part that is zero. There is an unchanged conclusion: exactly $j$ parts are nonzero, then there are exactly $pd(n - k, j)$ solutions, where $j$ only takes $k$ or $k - 1$. Therefore, we directly get the recurrence:

$$
pd(n, k) = pd(n - k, k - 1) + pd(n - k, k)
$$

Similarly, like binomial coefficients, list a table, each cell's value equals the value of the cell in the previous column in the same row of cells, plus the value of the cell above in the same column of cells.

| k         | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| --------- | - | - | - | - | - | - | - | - | - |
| $pd(0,k)$ | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| $pd(1,k)$ | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| $pd(2,k)$ | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| $pd(3,k)$ | 0 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
| $pd(4,k)$ | 0 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
| $pd(5,k)$ | 0 | 1 | 2 | 0 | 0 | 0 | 0 | 0 | 0 |
| $pd(6,k)$ | 0 | 1 | 2 | 1 | 0 | 0 | 0 | 0 | 0 |
| $pd(7,k)$ | 0 | 1 | 3 | 1 | 0 | 0 | 0 | 0 | 0 |
| $pd(8,k)$ | 0 | 1 | 3 | 2 | 0 | 0 | 0 | 0 | 0 |

### Example Problem

???+ note "Calculate distinct partition number"
    Calculate the distinct partition number $pd_n$. Multiple test cases, where $n$ upper bound is 50000, take modulo 1000007.
    
    Observing the table and recurrence formula, updating by column is better for storage. The code reduces the space by keeping only two adjacent columns.
    
    ```cpp
    #include <cstdio>
    #include <cstring>
    
    int pd[50005][2]; /*Number of distinct partitions of natural number n into k parts*/
    
    int main() {
      int n;
      while (~scanf("%d", &n)) {
        memset(pd, 0, sizeof(pd));
        pd[0][0] = 1;
        int ans = 0;
        int j;
        for (j = 1; j < 350; ++j) {
          int i;
          for (i = 0; i < 350; ++i) {
            pd[i][j & 1] = 0; /*pd[i][j] only depends on pd[][j] and pd[][j-1]*/
          }
          for (i = 0; i <= n; ++i) {
            if (i - j >= 0) /*pd[i-j][j] all parts are greater than 1*/
            {
              pd[i][j & 1] = (pd[i - j][j & 1] + pd[i - j][(j - 1) & 1]) %
                             1000007; /*pd[i-j][j-1] has at least one part equal to 1.*/
            }
          }
          ans = (ans + pd[n][j & 1]) % 1000007;
        }
        printf("%d\n", ans);
      }
    }
    ```

### Odd Partition Number

Odd partition number: $po_n$. The number of partitions of natural number $n$ where all parts are odd.

There is an obvious equation:

$$
\prod_{i=1}^\infty (1 + x^i) = \frac{\prod_{i=1}^\infty (1 - x^{2i})}{\prod_{i=1}^\infty (1 - x^i)} = \prod_{i=1}^\infty \frac{1}{1 - x^{2i - 1}}
$$

The leftmost is the generating function for distinct partition numbers, the rightmost is the generating function for odd partition numbers. The corresponding coefficients are the same, so odd partition numbers and distinct partition numbers are equal:

$$
po_n = pd_n
$$

But obviously, k-part odd partition numbers and distinct k-partition numbers are not the same concept, so they are not listed here.

Introduce two more concepts:

Distinct even partition number: $pde_n$. The number of distinct partitions of natural number $n$ where the number of parts is even.

Distinct odd partition number: $pdo_n$. The number of distinct partitions of natural number $n$ where the number of parts is odd.

Therefore:

$$
pd_n = pde_n + pdo_n
$$

There are also corresponding k-part concepts. They are too complex to list here.

## Pentagonal Number Theorem

Observe the denominator part of the generating function for partition numbers:

$$
\prod_{i=1}^\infty (1 - x^i)
$$

Expanding this, we can consider distinct partitions and the parity of the number of parts in distinct partitions.

Specifically, distinct even-part partitions are counted positively in the expansion, and distinct odd-part partitions are counted negatively. Therefore, the coefficients in the expansion are the difference between the two method counts. That is:

$$
\sum_{i=0}^\infty ({pde}_n - {pdo}_n) x^n = \prod_{i=1}^\infty (1 - x^i)
$$

Next, we explain that in most cases, the two method counts are equal, so the coefficient in the expansion is 0; only in a few positions do the two method counts differ by 1 or -1.

This can be done using a constructive bijection.

Draw the Ferrers diagram of each distinct partition. The last row is called the bottom of the diagram, and the number of dots on the bottom is denoted as $b$ (Bottom); the longest 45-degree line segment connecting the last point of the top row to some point in the diagram is called the slope of the diagram, and the number of dots on the slope is denoted as $s$ (Slide).

![](./images/bottom_slide.jpg)

To construct a bijection between distinct even-part partitions and distinct odd-part partitions, we need to define a transformation that changes the number of rows by 1 while preserving the distinctness condition.

Transformation A: When $b \le s$, move the bottom to the right to become a new slope.

Transformation B: When $b > s$, move the slope down to become a new bottom.

These two transformations, for any distinct partition of most $n$, exactly one transformation can be applied, constructing a one-to-one correspondence between distinct even-part partitions and distinct odd-part partitions. Since the two parts with a one-to-one correspondence have equal counts, the coefficient of the $n$-th term in the expansion is 0.

However, for some $n$, there exists exactly one distinct partition that cannot undergo the above transformation.

-   Case 1: When $b = s$ and the bottom and slope have a common point, transformation A cannot be performed. At this time,

$$
n = s + (s + 1) + \ldots + (s + s - 1) = \frac{s(3s - 1)}{2}
$$

The $n$-th term in the expansion is related to the parity of the number of parts, which is $(-1)^s x^n$.

-   Case 2: When $b = s + 1$ and the bottom and slope have a common point, transformation B cannot be performed. At this time,

$$
n = (s + 1) + (s + 2) + \ldots + (s + s) = \frac{s(3s + 1)}{2}
$$

The $n$-th term in the expansion is $(-1)^s x^n$.

Replace $s$ with $-s$ in the formula, getting $n = \frac{s(3s - 1)}{2}$ where $s$ is a negative integer, and the $n$-th term in the expansion is still $(-1)^s x^n$.

Since the two cases do not appear at the same $n$, we can combine the two conditions, and the condition $n$ must satisfy is

$$
\exists k \in \mathbb{Z}, n = \frac{k(3k - 1)}{2}
$$

Thus, we have proven:

$$
(1 - x)(1 - x^2)(1 - x^3)\ldots = \sum_{k = -\infty}^{+\infty} (-1)^k x^{\frac{k(3k - 1)}{2}} = \ldots + x^{26} - x^{15} + x^7 - x^2 + 1 - x + x^5 - x^{12} + x^{22} - \ldots
$$

Recall: This formula is the reciprocal of the generating function for partition numbers, so its product with the generating function for partition numbers equals 1. Organizing and comparing coefficients on both sides gives the recurrence formula for the partition number sequence.

$$
(1 + p_1 x + p_2 x^2 + p_3 x^3 + \ldots)(1 - x - x^2 + x^5 + x^7 - x^{12} - x^{15} + x^{22} + x^{26} - \ldots) = 1
$$

$$
p_n = p_{n-1} + p_{n-2} - p_{n-5} - p_{n-7} + \ldots
$$

This recurrence has infinitely many terms, but if we define the partition number of a negative number as 0 (the partition number of 0 is already defined as 1), then it simplifies to finite terms.

### Example Problem

???+ note "Calculate partition number"
    Calculate the partition number $p_n$. Multiple test cases, where the upper bound of $n$ is 50000, take modulo 1000007.
    
    Using the pentagonal number theorem method. There is code:
    
    ```cpp
    #include <cstdio>
    
    long long a[100010];
    long long p[50005];
    
    int main() {
      p[0] = 1;
      p[1] = 1;
      p[2] = 2;
      int i;
      for (i = 1; i < 50005;
           i++) /*Recurrence coefficients 1,2,5,7,12,15,22,26... i*(3*i-1)/2, i*(3*i+1)/2*/
      {
        a[2 * i] = i * (i * 3 - 1) / 2; /*Pentagonal numbers are 1,5,12,22... i*(3*i-1)/2*/
        a[2 * i + 1] = i * (i * 3 + 1) / 2;
      }
      for (
          i = 3; i < 50005;
          i++) /*p[n] = p[n-1] + p[n-2] - p[n-5] - p[n-7] + p[12] + p[15] - ... + p[n-i*[3i-1]/2] + p[n-i*[3i+1]/2]]*/
      {
        p[i] = 0;
        int j;
        for (j = 2; a[j] <= i; j++) /*May be negative, add 1000007 in the formula*/
        {
          if (j & 2) {
            p[i] = (p[i] + p[i - a[j]] + 1000007) % 1000007;
          } else {
            p[i] = (p[i] - p[i - a[j]] + 1000007) % 1000007;
          }
        }
      }
      int n;
      while (~scanf("%d", &n)) {
        printf("%lld\n", p[n]);
      }
    }
    ```