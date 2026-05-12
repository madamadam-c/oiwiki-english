## Introduction

**Young tableau**, also known as Young diagram, is a combinatorial object commonly used in representation theory and Schubert calculus.

A Young diagram is a special kind of matrix. It facilitates the study of group representations and properties of symmetric groups and general linear groups. Young tableaux were first proposed by mathematician Alfred Young at Cambridge University in 1900, and were applied to the study of symmetric groups by German mathematician Ferdinand Georg Frobenius in 1903.

???+ note "Note"
    **Representation theory** is a branch of mathematics that studies abstract algebraic structures by representing elements as linear transformations of vector spaces. **Schubert calculus** is a branch of algebraic geometry introduced in the 19th by Hermann Schubert to solve counting problems in projective geometry.

## Definition

### Young Diagram

A **Young diagram** (also called [Ferrers diagram](https://en.wikipedia.org/wiki/Partition_%28number_theory%29#Ferrers_diagram) when using dots; there is a related introduction in the section [partition numbers](./combinatorics/partition.md#ferrers-%E5%9B%BE)) is a finite collection of boxes or cells aligned to the left, with row lengths in non-increasing order. If we list the number of cells in each row of a Young diagram, we obtain an **integer partition** $\lambda$ of a nonnegative integer $n$ (the total number of cells). Therefore, we can view the shape of a Young diagram as $\lambda$, because it carries the same information as its integer partition.

The inclusion relation between Young diagrams defines a [partial order](../math/order-theory.md#偏序集) on integer partitions. This relation has the structure of a [lattice](../math/order-theory.md#有向集与格), called **Young's lattice**. If we list the number of cells in each column of a Young diagram, we obtain the "conjugate partition" or "transpose partition" of the integer partition $\lambda$. The Young diagram corresponding to this conjugate partition can be obtained by mirroring the original Young diagram along the main diagonal.

The position of each cell in a Young diagram is determined by two coordinates representing the **row number** and **column number**. Columns are ordered from left to right, and rows are ordered from most cells to fewest cells. Note that there are two different conventions for drawing Young diagrams depending on the convention: the first places rows with fewer cells below rows with more cells, and the second stacks rows from largest to smallest. Since the first convention is mainly used in English-speaking countries while the latter is typically used in French-speaking countries, they are conventionally called the English style and French style respectively.

The following table shows different drawings of the Young diagram for the integer partition $(5, 4, 1)$:

- English style: ![](./images/young-diagram-1.svg)
- French style: ![](./images/young-diagram-2.svg)

### Young Tableau

#### Definition

A **Young tableau** is obtained by filling the boxes of a Young diagram with symbols from some alphabet, which is usually required to be a totally ordered set. The filled elements are written as $x_1$, $x_2$, $x_3$, $\ldots$. However, for convenience, positive integers are directly filled in.

When Young tableaux were originally applied to the representation theory of symmetric groups, any distinct positive integers from $1$ to $n$ could be arbitrarily placed in the $n$ boxes of a Young diagram. However, modern research mostly uses "standard" Young tableaux, which satisfy the condition that the numbers in each row and each column are strictly increasing. The number of distinct Young tableaux with $n$ boxes forms the [telephone number](https://en.wikipedia.org/wiki/Telephone_number_%28mathematics%29) sequence:

???+ note "Note"
    The **telephone number** (involution number/telephone number) is an integer sequence in mathematics that counts the number of ways to connect $n$ telephone lines where each line can be connected to at most one other line. It also describes the number of matchings on a complete graph with $n$ vertices, the number of permutations of $n$ involutions, the sum of absolute values of coefficients of Hermite polynomials, and the number of standard Young tableaux with $n$ cells, as well as the sum of degrees of irreducible symmetric groups.

$1, 1, 2, 4, 10, 26, 76, 232, 764, 2620, 9496, \ldots$ (sequence [A000085](https://oeis.org/A000085) in [OEIS](https://en.wikipedia.org/wiki/On-Line_Encyclopedia_of_Integer_Sequences))

In other applications, Young diagrams can also be filled with repeated numbers. If the numbers in each column are strictly increasing and the numbers in each row are non-decreasing, such a Young tableau is called a **semistandard Young tableau** (SSYT, sometimes called column-strict). The sequence recording how many times each number appears in a Young tableau is considered the **weight** of the Young tableau. Therefore, the weight of a standard Young tableau must be $(1, 1, \ldots, 1)$, because in a standard Young tableau, each positive integer from $1$ to $n$ appears exactly once.

#### Insertion algorithm for standard Young tableaux

The properties of permutations can be intuitively represented by Young tableaux. The **RSK insertion algorithm** provides a way to connect Young tableaux and permutations. It was proposed by Robinson, Schensted, and Knuth.

Let $S$ be a Young tableau, and define $S \leftarrow x$ as inserting $x$ into the first row of the Young tableau as follows:

1. Find the smallest number $y$ in the current row that is greater than $x$.
2. If found, replace $y$ with $x$, move to the next row, set $x \leftarrow y$, and repeat step 1.
3. If not found, place $x$ at the end of this row and exit. Let $x$ be at row $s$ and column $t$. $(s, t)$ must be a corner. A cell $(s, t)$ is a corner if and only if both $(s + 1, t)$ and $(s, t + 1)$ do not exist.

For example, the steps to insert $3$ into the Young tableau $(2, 5, 9)(6, 7)(8)$ are:

![](./images/young-tableau-insert.svg)

### Variations

There are many variations of non-strictly-standard Young tableaux. For example, row-strict Young tableaux require strictly increasing numbers in each row and non-decreasing numbers in each column, which is the conjugate of column-strict Young tableaux. Additionally, in the theory of plane partitions, it is conventional to change the increasing order to decreasing order in the above definition. Other variations, such as ribbon Young tableaux, first pack some boxes into groups and require that boxes in the same group be filled with the same number.

### Skew Young Tableau

Given two Young diagrams $\lambda = (\lambda_1, \lambda_2, \ldots)$ and $\mu = (\mu_1, \mu_2, \ldots)$ such that $\lambda$ contains $\mu$, i.e., $\mu_i \leq \lambda_i$ for all $i$. Define the "skew Young diagram" $\lambda / \mu$ as the set of all cells in $\lambda$ minus all cells in $\mu$, i.e., the set difference of $\lambda$ and $\mu$. Filling elements into the cells of a skew Young diagram forms a **skew Young tableau**.

For example, the following is a standard skew Young tableau corresponding to the integer partition $(5, 4, 1)$:

![](./images/skew-tableau.svg)]

Similarly, if the numbers in each column are strictly increasing and the numbers in each row are non-decreasing, such a skew Young tableau is called a **semistandard skew Young tableau**. If a semistandard skew Young tableau fills distinct numbers from $1$ to $n$ (where $n$ is the total number of cells) without repetition, it is called a **standard skew Young tableau**. Note that different $\lambda$ and $\mu$ can yield the same $\lambda / \mu$. Although most properties of skew Young tableaux depend only on the cells after taking the set difference, some operations still depend on the choice of $\lambda$ and $\mu$. Therefore, $\lambda / \mu$ must be considered as containing two pieces of information: $\lambda$ and $\mu$. When $\mu$ is the empty partition (the only partition of $0$), the skew Young tableau $\lambda / \mu$ becomes the Young tableau $\lambda$.

## Applications

Young tableaux are commonly used in combinatorics, representation theory, and algebraic geometry to obtain definitions and related identities of Schur functions through various methods of counting Young tableaux. In competitive programming (informatics olympiad), there are often problems that test the hook length formula.

### Hook Length

Given a Young tableau $\pi_\lambda$ with $n$ cells, fill the numbers $1$ to $n$ into the Young tableau such that each row from left to right and each column from bottom to top is strictly increasing. Let $\dim_{\pi_\lambda}$ denote the number of ways to do this.

For a cell $v$ in a Young tableau, define its **hook length** $\mathrm{hook}(v)$ as the number of cells to the right in the same row plus the number of cells above in the same column, plus $1$ (the cell itself).

### Hook Length Formula

If we denote by $\dim_\lambda$ the number of such methods, the **hook length formula** states that the number of methods equals $n!$ divided by the product of the hook lengths of all cells.

$$
\dim \pi _{\lambda}={\frac {n!}{\prod_{{x\in Y(\lambda)}}{\mathrm {hook}}(x)}}.
$$

![](./images/young-tableau-2.svg)

Therefore, for the Young tableau of integer partition $10 = 5 + 4 + 1$, as shown in the figure above, we have

$$
\dim \pi _{\lambda } = {\frac {10!}{7\cdot 5\cdot 4\cdot 3\cdot 1\cdot 5\cdot 3\cdot 2\cdot 1\cdot 1}} = 288.
$$

methods.

## Example Problems

### Subsequence problems

For a Young tableau $P$, define for a permutation $X = x_1, \ldots, x_n$ from $1$ to $n$:

1. The length of the first row in $P_X$ is the length of the **longest increasing subsequence (LIS)** of permutation $X$. Note that the first row of $P$ may not be the LIS itself, so the properties of Young tableaux cannot be directly used to solve problems like "LIS partition."

2. For a permutation $X$ and its Young tableau $P_X$, if $X^R$ is the reverse of $X$, then the Young tableau $P_{X^R}$ obtained from $X^R$ is obtained by swapping rows and columns of $P_X$.

    For example, for permutation $X = 1, 5, 7, 2, 8, 6, 3, 4$ and $X^R = 4, 3, 6, 8, 2, 7, 5, 1$, we can obtain the following Young tableau $P_X$:

    ![](./images/young-tableau-LIS.svg)

3. The length of the first column in Young tableau $P_X$ is the length of the **longest decreasing subsequence (LDS)** of permutation $X$.

Define the length of LIS/LDS not exceeding $k$ as $k$-LIS and $k$-LDS. Such problems can also be solved using Young tableaux. For $1$-LIS, the longest $1$-LIS subsequence is obviously the LDS of the sequence, which is exactly the first column of the Young tableau. Similarly, the sum of the lengths of the first $k$ columns of the Young tableau is the length of the longest $k$-LIS subsequence. The proof is as follows:

For a permutation $X$ and its $m$-row Young tableau $P$, let permutation $X^*$ be $(P_{m,1}\ldots P_{m,\lambda_m}, P_{m-1,1}\ldots P_{1,1}\ldots P_{1,\lambda_1})$ (i.e., writing each row of the Young tableau from bottom to top in sequence). Then $X$ can be transformed into $X^*$ through swap operations.

Therefore, the length of the longest $k$-LIS subsequence can be expressed as $F(k) = \sum_{i=1}^{m} \min(k, \lambda_i)$, i.e., the sum of the lengths of the first $k$ columns.

???+ note "[CTSC2017 Longest Increasing Subsequence](https://uoj.ac/problem/301)"
    There is a sequence $b$ of length $n$. For the sequence $B_m = (b_1, b_2, \ldots, b_m)$, let $C$ be a subsequence of $B_m$, and the length of the longest increasing subsequence of $C$ does not exceed $k$. Query the maximum length of $C$.

??? note "Solution approach"
    For multiple queries, consider using a sweep line method. This requires maintaining the Young tableau for each prefix. Using the above conclusion, the problem becomes how to quickly maintain the sum of the lengths of the first $k$ columns of the Young tableau. If maintained directly, the complexity is $O(n^2 \log n)$, which is unacceptable. Consider maintaining the first $\sqrt{n}$ columns and first $\sqrt{n}$ rows.
    
    It can be found that the Young tableau never completely covers this $W \times H$ rectangle. If $K \leq W$, the answer can be obtained directly; if $K > W$, the part greater than $W$ must be within $H$ rows. So consider how to maintain the first $\sqrt{n}$ columns and first $\sqrt{n}$ rows simultaneously. Flipping the permutation gives the transpose of the Young tableau, so we only need to also maintain $-A_i$, with complexity $O(n \sqrt{n} \log n)$.

???+ note "[BJWC2018 Longest Increasing Subsequence](https://www.luogu.com.cn/problem/P4484)"
    Now there is a random permutation of length $n$. Find the expected value of its longest increasing subsequence length.

???+ note "[CF1268B Young's Dominoes](https://codeforces.com/problemset/problem/1268/B)"
    Given a histogram with $n$ columns of lengths $a_1, a_2, \ldots, a_n$ ($a_1 \geq a_2 \geq \ldots \geq a_n \geq 1$). The Young diagram for $a = [3, 2, 2, 2, 1]$. Find the maximum number of non-overlapping dominoes ($1 \times 2$ or $2 \times 1$ rectangles) that can be drawn in this histogram.

## References and Further Reading

1. [Young Tableau - from Wolfram MathWorld](https://mathworld.wolfram.com/YoungTableau.html)
2. [Young tableau - Wikipedia](https://en.wikipedia.org/wiki/Young_tableau)
3. [Hook length formula - Wikipedia](https://en.wikipedia.org/wiki/Hook_length_formula)
4. Yuan Fangzhou, ["A Brief Discussion on the Application of Young Matrices in Informatics Olympiad" IOI2019](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AF%E9%98%B5%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AF%E9%98%B52019%E8%AE%BA%E6%96%87%E9%9B%86.pdf), Chinese National Team Candidate Papers, 202-229