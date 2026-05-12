## Elementary Matrices

The following three types of square matrices are called elementary matrices.

### Row-Scaling Matrix

A row-scaling matrix is a special diagonal matrix.

$$
D_i(k)=\operatorname{diag}\{1,\cdots,1,k,1,\cdots,1\}
$$

It represents a diagonal matrix with $k$ at the $i$-th position on the main diagonal, and $k$ is required to be non-zero; all other elements are $1$.

In particular, when $k$ is $1$, $D_i(1)$ is the identity matrix $I$.

### Row-Swapping Matrix

A row-swapping matrix is a special symmetric matrix.

$$
P_{ij}=\begin{pmatrix}
I_{i-1} &  &  &  & \\
 & 0 &  & 1 & \\
 &  & I_{j-i-1} &  & \\
 & 1 &  & 0 & \\
 &  &  &  & I_{n-j}\\
\end{pmatrix}
$$

The elements of a row-swapping matrix are all $0$ or $1$. All elements on the main diagonal are $1$, except the $i$-th and $j$-th elements are $0$, while the elements at row $i$, column $j$ and row $j$, column $i$ are $1$.

The row-swapping matrix requires $i$ and $j$ to be unequal.

### Row-Adding Matrix

A row-adding matrix is obtained from the identity matrix $I$ by setting the element at row $i$, column $j$ to $k$.

$$
T_{ij}(k)=\begin{pmatrix}
1 &  &  &  &  &  & \\
 & \ddots &  &  &  &  & \\
 &  & 1 & \cdots & k &  & \\
 &  &  & \ddots & \vdots &  & \\
 &  &  &  & 1 &  & \\
 &  &  &  &  & \ddots & \\
 &  &  &  &  &  & 1\\
\end{pmatrix}
$$

The row-adding matrix requires $i$ and $j$ to be unequal. If $k$ is $0$, then $T_{ij}(0)$ reduces to the identity matrix $I$.

A row-adding matrix is either an upper triangular matrix or a lower triangular matrix.

### Determinant of Elementary Matrices

The three types of elementary matrices have determinants:

$$
|D_i(k)|=k
$$

$$
|P_{ij}|=-1
$$

$$
|T_{ij}(k)|=1
$$

Since the determinant of a product of square matrices equals the product of determinants, and using the equivalence of elementary operations and matrix multiplication discussed below, this property of elementary matrices can be used for determinant computation.

## Elementary Operations

Not limited to square matrices, for a general matrix $A$, elementary row operations and elementary column operations can be performed, collectively called elementary operations.

There are three types of elementary row operations and three types of elementary column operations: scaling (multiplication), swapping (switching), and row-adding (addition). Elementary row operations are introduced first:

-   Multiply row $i$ by non-zero number $k$: $B\mapsto D_i(k)B$.
-   Swap rows $i$ and $j$: $B\mapsto P_{ij}B$.
-   Add $k$ times row $j$ to row $i$: $B\mapsto T_{ij}(k)B$.

Changing rows to columns in the above gives elementary column operations.

In elementary operations, swapping can be achieved through scaling and adding. Obviously, adding cannot be achieved through scaling and swapping. Using determinant knowledge, and the equivalence of elementary operations and matrix multiplication discussed below, scaling cannot be achieved through adding and swapping.

Therefore, compared to swapping, scaling and adding are more fundamental operations. The swapping operation is an auxiliary operation introduced to ensure orderly elimination in the elimination method.

## Elementary Operations and Matrix Multiplication

We can see that the three types of elementary matrices are obtained by performing the corresponding operation once on the identity matrix $I$. In the linear transformation discussed later, there is a correspondence between linear transformations and matrices, similar to the relationship here.

Regardless of whether matrix $A$ is square or not, performing elementary row operations on $A$ is equivalent to left-multiplying $A$ by an elementary matrix. Performing elementary column operations on $A$ is equivalent to right-multiplying $A$ by an elementary matrix.

### Scaling Operation

Left-multiplying by a scaling matrix $D_i(k)$ is equivalent to scaling row $i$ by $k$. Right-multiplying by a scaling matrix $D_i(k)$ is equivalent to scaling column $i$ by $k$.

The product of diagonal matrices is still a diagonal matrix. For diagonal matrix multiplication, multiply the corresponding elements on the main diagonal. Since the identity matrix is a special scaling matrix, and scaling matrices require $k$ to be non-zero, we can see that any diagonal matrix with all elements on the main diagonal non-zero can be decomposed into a product of scaling matrices.

For a general diagonal matrix, whether elements are $0$ or not, there is a corresponding conclusion. Left-multiplying by a diagonal matrix is equivalent to scaling the corresponding rows by the respective elements on the main diagonal of the diagonal matrix. Right-multiplying by a diagonal matrix performs the same operation on columns.

Since the determinant of scaling matrix $D_i(k)$ is $k$, after scaling a row or column of a square matrix, the corresponding determinant is multiplied by $k$. The determinant of a diagonal matrix is the product of elements on the main diagonal.

Scaling matrix multiplication is commutative, and diagonal matrix multiplication is also commutative. When only diagonal matrices are multiplied, the order can be arbitrary.

The scaling operation corresponding to the identity matrix leaves matrix $A$ unchanged; in practice, such an operation is not performed.

### Swapping Operation

Left-multiplying by a swapping matrix $P_{ij}$ is equivalent to swapping rows $i$ and $j$. Right-multiplying by a swapping matrix $P_{ij}$ is equivalent to swapping columns $i$ and $j$.

Similar to the relationship between scaling matrices and diagonal matrices, here we introduce the concept of permutation matrices. A permutation matrix is a square matrix with exactly one $1$ in each row and column, and $0$ elsewhere. The identity matrix $I$ is also a special permutation matrix.

Permutation matrices correspond exactly to permutations: a permutation matrix is consistent with performing permutation operations on rows of the identity matrix $I$, as well as on columns of the identity matrix $I$. The identity matrix $I$ itself corresponds to the identity transformation.

Left-multiplying by a permutation matrix is equivalent to permuting rows of the original matrix. Right-multiplying by a permutation matrix is equivalent to permuting columns of the original matrix. The permutation method is consistent with performing permutation operations on rows or columns of the identity matrix $I$.

Permutation matrices and permutations are in one-to-one correspondence. The group of permutation matrices under multiplication is isomorphic to the symmetric group. Since there is a theorem that any permutation can be decomposed into a product of transpositions (in the case where the identity transformation is considered as a product of zero transpositions), any permutation matrix can also be decomposed into a product of swapping matrices.

Since the determinant of a swapping matrix is $-1$, after swapping rows or columns of a square matrix, the corresponding determinant is multiplied by $-1$.

Swapping matrices do not commute in multiplication, nor do permutation matrices.

The determinant of a permutation matrix is ${(-1)}^p$, where $p$ is the number of inversions in the permutation corresponding to the permutation matrix, i.e., the number of transpositions in the decomposition of the permutation.

### Row-Adding Operation

Left-multiplying by row-adding matrix $T_{ij}(k)$ is equivalent to adding $k$ times row $j$ to row $i$. Right-multiplying by row-adding matrix $T_{ij}(k)$ is equivalent to adding $k$ times column $i$ to column $j$.

If it's hard to remember, observe what operation was performed on the identity matrix $I$ to get the row-adding matrix $T_{ij}(k)$. The two correspond: left-multiplying is a row operation, right-multiplying is a column operation, consistent with the mnemonic "left row, right column".

Since the determinant of a row-adding matrix is $1$, after performing a row-adding operation on a square matrix, the corresponding determinant remains unchanged.

Row-adding matrices do not commute in multiplication.

The row-adding operation corresponding to the identity matrix leaves matrix $A$ unchanged; in practice, such an operation is not performed.

#### Upper Triangular Matrix

A row-adding matrix is either an upper triangular matrix or a lower triangular matrix. Since the two types are symmetric about the main diagonal, we discuss upper triangular matrices. In this example, only elementary row operations are needed, no column operations.

If the main diagonal of an upper triangular matrix is all $1$, it can be decomposed into a product of a sequence of row-adding matrices. The order of decomposition is: first perform row-adding operations on the first row of the identity matrix $I$, then on the second row, and so on, until every row has been operated on.

Since row-adding matrix multiplication does not commute, the order of operations cannot be changed.

If the main diagonal of an upper triangular matrix is all non-zero, it can be decomposed into a product of a sequence of row-adding matrices and scaling matrices. When operating on each row of the identity matrix $I$, first scale that row so that the main diagonal element becomes the specified non-zero value.

If the main diagonal of an upper triangular matrix contains $0$, it cannot be decomposed into a product of a sequence of elementary matrices.

Regardless of whether the main diagonal of an upper triangular matrix has $0$ or not, the determinant of an upper triangular matrix equals the product of elements on the main diagonal, consistent with a diagonal matrix.

#### Converting a Square Matrix to a Diagonal Matrix Using Row-Adding Operations

Only using row-adding operations can convert any square matrix to a diagonal matrix. This example requires both elementary row operations and elementary column operations.

If the first row and first column of a square matrix have non-zero elements, the top-left element can be made non-zero using the row-adding method. Then, using elementary row operations and elementary column operations, all elements in the first row and first column except the top-left element can be made $0$.

If the first row and first column of a square matrix are all $0$, then directly look at the second row and second column.

Using this method, we can even ensure that the non-zero elements of the diagonal matrix are all in the top-left corner.

If the first row and first column of a square matrix are all $0$, look at whether the remaining rows and columns have non-zero elements. As long as there are non-zero elements, the first row and first column can be made to have a non-zero element using row-adding operations, thus reducing to the initial case where the top-left element is non-zero.

Only when the remaining rows and columns also have no non-zero elements can the top-left element not be made non-zero. At this point, the remaining square matrix is already a zero matrix.

#### Standard Form Matrix

Using elementary operations, any matrix, regardless of shape, can be reduced to a standard form matrix.

A standard form matrix has an identity matrix $I$ as a submatrix in the top-left corner, and all other parts are $0$. The reduction method is similar to converting a square matrix to a diagonal matrix, and also requires using scaling operations to make non-zero elements in the top-left corner become $1$.

After converting a matrix to standard form, the number of elements equal to $1$ is exactly the rank of the matrix.

## Invertible Matrices

Let $A$ be an $n \times n$ matrix. If there exists an $n \times n$ matrix $B$ such that $AB=BA=I$, then $A$ is called an invertible matrix or non-singular matrix, and $B$ is called the inverse matrix of $A$, denoted $A^{-1}$.

If matrix $A$ is invertible, then the inverse of $A$ is uniquely determined by $A$.

The inverse of an invertible matrix $A$ is also invertible, and the inverse of $A^{-1}$ is $A$.

The product $AB$ of two invertible matrices $A$ and $B$ is also invertible, and its inverse is $B^{-1}A^{-1}$.

The transpose $A^T$ of an invertible matrix $A$ is also invertible, and the inverse of the transpose equals the transpose of the inverse.

### Inverses of Elementary Matrices

All elementary matrices are invertible, and their inverses are elementary matrices of the same type:

$$
{D_i(k)}^{-1}=D_i\left(\frac{1}{k}\right)
$$

$$
P_{ij}^{-1}=P_{ij}
$$

$$
T_{ij}(k)^{-1}=T_{ij}(-k)
$$

Clearly, the identity matrix $I$ is invertible, and its inverse is still $I$.

Elementary operations preserve the invertibility of a matrix. Before and after transformation, a matrix is either both invertible or both non-invertible.

Matrix $A$ is invertible if and only if matrix $A$ can be written as a product of elementary matrices, i.e., can be transformed to the identity matrix $I$ through elementary operations.

After introducing determinants, we know:

Matrix $A$ is invertible if and only if the rank of matrix $A$ is $n$, if and only if the determinant of matrix $A$ is non-zero.

A simple notation: let $E_{ij}$ be an $n \times n$ matrix with $1$ at row $i$, column $j$ and $0$ elsewhere. Then:

-   $D_i(k)=I_n+(k-1)E_{ii}$
-   $P_{ij}=I_n-E_{ii}-E_{jj}+E_{ij}+E_{ji}$
-   $T_{ij}(k)=I_n+kE_{ij}$

This notation can also be applied to their inverses.

## Applications

### Solving Linear Systems

For a linear system, the coefficients before unknowns form the coefficient matrix. If the constants of the linear system are appended to the right of the coefficient matrix, the augmented matrix is formed.

Using elementary row operations, the augmented matrix of a linear system can first be transformed to a row echelon form, then to a reduced row echelon form, completing the solution of the linear system. This method is called the elimination method for solving linear systems. The Gauss–Jordan elimination discussed later is an elimination algorithm that proceeds in a certain order.

### Determinant Calculation

Since the determinant of a product of square matrices equals the product of determinants, and the determinants of elementary matrices are easy to compute, and elementary operations are equivalent to multiplication by elementary matrices, elementary operations are also used in determinant calculation.

Since performing elementary operations in a certain order makes program writing easier, determinant calculation can also use the Gauss–Jordan elimination algorithm discussed later.