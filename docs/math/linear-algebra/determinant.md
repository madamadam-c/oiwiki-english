The determinant is an operation on square matrices. For a square matrix $A$, $\det A$ denotes the determinant of square matrix $A$.

This article introduces three definitions of determinants. It can be proven that the definition methods in this article are equivalent.

## Definition by Permutations

Prerequisites: [Permutation](../permutation.md), [Inversion number](../permutation.md#inversion-number).

This method can be used to manually calculate determinants of lower orders. Its time complexity is factorial level.

Use the notation $\pi(j_1j_2\cdots j_n)$ to denote the inversion number of permutation $j_1j_2\cdots j_n$, and let $S_n$ be the set of all permutations of length $n$. The notation:

$$
\begin{aligned}
\det A &= \begin{vmatrix}
a_{11} & a_{12} & \cdots & a_{1n}\\
a_{21} & a_{22} & \cdots & a_{2n}\\
\vdots & \vdots &  & \vdots\\
a_{n1} & a_{n2} & \cdots & a_{nn}\\
\end{vmatrix} \\
&= \sum_{(j_1j_2\cdots j_n) \in S_n} (-1)^{\pi(j_1j_2\cdots j_n)} a_{1 j_1} a_{2 j_2}\dots a_{n j_n}
\end{aligned}
$$

denotes an $n$-th order determinant, which is an algebraic sum of $n!$ terms. These terms are the products of $n$ elements taken from different rows and different columns of square matrix $A$: $a_{1j_1}a_{2j_2}\cdots a_{nj_n}$.

The sign before term $a_{1j_1}a_{2j_2}\cdots a_{nj_n}$ is ${(-1)}^{\pi(j_1j_2\cdots j_n)}$. That is, when $j_1j_2\cdots j_n$ is an even permutation, the sign is positive; when $j_1j_2\cdots j_n$ is an odd permutation, the sign is negative.

For the diagonal rule of second and third order determinants, in fact, the full permutation definition is used. For determinants of order four and above, the diagonal rule is no longer applicable, for the same reason. In particular, a first-order determinant is the element itself.

Theorem: Taking elements from the $i_1,i_2,\cdots,i_n$-th rows and $j_1,j_2,\cdots,j_n$-th columns of an $n$-th order determinant to multiply

$$
a_{i_1j_1}a_{i_2j_2}\cdots a_{i_nj_n}
$$

Here, $i_1,i_2,\cdots,i_n$ and $j_1,j_2,\cdots,j_n$ are both permutations of $1,2,\cdots,n$. Then this term has sign ${(-1)}^{s+t}$ in the determinant, where

$$
s=\pi(i_1i_2\cdots i_n)
$$

$$
t=\pi(j_1j_2\cdots j_n)
$$

Theorem: A determinant equals its transpose.

Theorem: Let the $i$-th row of determinant $\det A$ have all elements that can be expressed as the sum of two terms:

$$
\begin{vmatrix}
a_{11} & a_{12} & \cdots & a_{1n}\\
\vdots & \vdots &  & \vdots\\
b_{i1}+c_{i1} & b_{i2}+c_{i2} & \cdots & b_{in}+c_{in}\\
\vdots & \vdots &  & \vdots\\
a_{n1} & a_{n2} & \cdots & a_{nn}\\
\end{vmatrix}
$$

Then this determinant equals the sum of two determinants $\det A_1$ and $\det A_2$. Where the $i$-th row of $A_1$ is $b_{i1},b_{i2},\cdots,b_{in}$, the $i$-th row of $A_2$ is $c_{i1},c_{i2},\cdots,c_{in}$, and all other rows of $A_1$ and $A_2$ are the same as $A$. The same property holds for columns.

## Definition by Induction

This method only describes an algebraic property of determinants, and its time complexity is also factorial level, so it is not suitable for computation.

### Algebraic Cofactor

In an $n$-th order determinant $\det A$, arbitrarily select $k$ rows and $k$ columns of matrix $A$. The $k$-order matrix formed by elements at the intersections of these rows and columns is called a $k$-order submatrix, and its determinant is called a $k$-order minor.

For an $n$-th order determinant $\det A$, the cofactor matrix $M_{ij}$ of element $a_{ij}$ refers to the $(n-1)$-order submatrix remaining after removing the row and column where $a_{ij}$ is located in the original matrix $A$. Its determinant $\det M_{ij}$ is called the cofactor.

For an $n$-th order determinant $\det A$, the cofactor $\det M_{ij}$ of element $a_{ij}$ multiplied by the sign ${(-1)}^{i+j}$ is called the algebraic cofactor of element $a_{ij}$, denoted as $A_{ij}$.

From the definition in the previous section on the full permutation method, we can derive:

Theorem: If in an $n$-th order determinant $\det A$, all elements in the $i$-th row or $j$-th column are $0$ except for $a_{ij}$, then this determinant equals $a_{ij}$ multiplied by its algebraic cofactor $A_{ij}$.

### Determinant Expansion

Since transpose of a square matrix leaves the determinant unchanged, we only need to introduce one of row expansion or column expansion.

The determinant $\det A$ is defined as the sum of the products of all elements in any row (or column) and their corresponding algebraic cofactors.

In other words, the determinant can be recursively defined by row (or column) expansion:

$$
\begin{aligned}
\det A &= a_{i1}A_{i1}+a_{i2}A_{i2}+\cdots+a_{in}A_{in} \\
&= \sum_{j = 1}^{n} a_{ij}A_{ij} \\
&= \sum_{j = 1}^{n} (-1)^{i + j} a_{ij} \det M_{ij}
\end{aligned}
$$

$$
\begin{aligned}
\det A &= a_{1j}A_{1j}+a_{2j}A_{2j}+\cdots+a_{nj}A_{nj} \\
&= \sum_{i = 1}^{n} a_{ij}A_{ij} \\
&= \sum_{i = 1}^{n} (-1)^{i + j} a_{ij} \det M_{ij}
\end{aligned}
$$

The recursive endpoint is the determinant of a first-order matrix, which is the only element contained in that matrix.

From this, we have:

Theorem: The sum of the products of elements in one row (or column) of determinant $\det A$ and the algebraic cofactors of corresponding elements in another row (or column) equals $0$.

In other words, when $i\neq j$:

$$
a_{i1}A_{j1}+a_{i2}A_{j2}+\cdots+a_{in}A_{jn}=0
$$

$$
a_{1i}A_{1j}+a_{2i}A_{2j}+\cdots+a_{ni}A_{nj}=0
$$

## Axiomatic Definition

The axiomatic definition says that the operation that satisfies certain properties can only be the determinant.

Prerequisites: [Elementary operations](./elementary-operations.md).

Let $D_i(k)$ be the [row-scaling matrix](./elementary-operations.md#row-scaling-matrix), $P_{ij}$ be the [row-swapping matrix](./elementary-operations.md#row-swapping-matrix), and $T_{ij}(k)$ be the [row-adding matrix](./elementary-operations.md#row-adding-matrix).

For an operation $\det$ on an $n$-th order matrix $A$, if it satisfies the following four properties, it is called a determinant:

-   Multiplying all elements in a row or column of a determinant by a number $k$ is equivalent to multiplying the determinant by $k$.

    $$
    \det(D_i(k)A) = \det(AD_i(k)) = k \det A
    $$

-   Swapping two rows or two columns of a determinant changes the sign of the determinant.

    $$
    \det(P_{ij}A) = \det(AP_{ij}) = -\det A
    $$

-   Multiplying elements in one row or column of a determinant by the same number and adding them to the corresponding elements of another row or column leaves the determinant unchanged.

    $$
    \det(T_{ij}(k)A) = \det(AT_{ij}(k))= \det A
    $$

-   The determinant of the identity matrix is $1$.

    $$
    \det I = 1
    $$

Using the properties of determinants related to elementary operations, we can manually calculate determinants of higher orders more conveniently. The [Gaussian elimination method for calculating determinants](../numerical/gauss.md#determinant-calculation) also uses this property, with time complexity $O(n^3)$.

These properties also have several corollaries:

-   A common factor in a row or column of a determinant can be factored out of the determinant sign.

-   If all elements in a row or column of a determinant are $0$, then the determinant equals $0$.

-   If two rows or two columns of a determinant have proportional corresponding elements, then the determinant equals $0$.

-   If two rows or two columns of a determinant are exactly the same, then the determinant equals $0$.

These corollaries are very useful when manually calculating determinants.