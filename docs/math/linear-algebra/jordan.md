## Jordan Decomposition

Let $T$ be a linear transformation on an $n$-dimensional space $V$. If the minimal polynomial of $T$ is:

$$
m_A(\lambda)={(\lambda-\lambda_1)}^{r_1}{(\lambda-\lambda_2)}^{r_2}\cdots{(\lambda-\lambda_k)}^{r_k}
$$

Then by the primary decomposition theorem, the space $V$ can be decomposed into a direct sum of subspaces:

$$
V=V_1\oplus V_2\oplus\cdots\oplus V_k
$$

where $V_i=N\left({(A-\lambda_i I)}^{r_i}\right)$, $A$ being the matrix corresponding to $T$, and these subspaces are all invariant under $T$.

Let the transformation $T_i$ be the projection of $V$ onto the subspace $V_i$, i.e., construct a polynomial $u_i(T)$ such that:

-   $$
    T_i=u_i(T)\frac{m_A(T)}{{(T-\lambda_i T_e)}^{r_i}}
    $$
-   $$
    T_1+T_2+\cdots+T_k=T_e
    $$

where $T_e$ denotes the identity transformation on $V$. Then we have the properties:

-   The restriction of $T_i$ to $V_i$, denoted ${T_i|}_{V_i}$, is the identity transformation on $V_i$.
-   If $i \neq j$, the restriction of $T_i$ to $V_j$, denoted ${T_i|}_{V_j}$, is the zero transformation on $V_j$.

Thus, the transformation $T_i$ maps every vector $\xi$ in $V$ to its component in $V_i$.

Construct the transformation:

$$
T_D=\lambda_1 T_1+\lambda_2 T_2+\cdots+\lambda_k T_k
$$

Since each $T_i$ is a polynomial in $T$, $T_D$ is also a polynomial in $T$, so each subspace $V_i$ is invariant under $T_D$.

From the above, the restriction of $T_D$ to $V_i$, denoted ${T_D|}_{V_i}$, is a homothety on $V_i$ with ratio $\lambda_i$. Therefore, $T_D$ is diagonalizable.

Construct:

$$
T_N=T-T_D
$$

Then $T_N$ is also a polynomial in $T$, so each subspace $V_i$ is invariant under $T_N$. For any vector $\xi_i$ in $V_i$, we have:

$$
{T_N}^{r_i}(\xi_i)={T-T_D}^{r_i}(\xi_i)={T-\lambda_i T_i}^{r_i}(\xi_i)=0
$$

Let $r$ be the maximum of all $r_i$. Then for any vector $\xi$ in $V$, $T_N^r$ maps $\xi$ to the zero vector. Therefore, $T_N$ is a nilpotent transformation.

Thus, every transformation $T$ on $V$ can be written as:

$$
T=T_D+T_N
$$

where $T_D$ is diagonalizable and $T_N$ is nilpotent. Since $T_D$ and $T_N$ are both polynomials in $T$, their product commutes:

$$
T_DT_N=T_NT_D
$$

**Theorem:** Let $T_1$ and $T_2$ be two diagonalizable transformations on $V$ such that $T_1T_2=T_2T_1$. Then there exists a basis such that the matrices of both $T_1$ and $T_2$ with respect to this basis are diagonal.

**Theorem:** Let $T$ be a linear transformation on an $n$-dimensional space $V$. Then there exists a diagonalizable transformation $T_D$ and a nilpotent transformation $T_N$ such that:

-   $$
    T=T_D+T_N
    $$
-   $$
    T_DT_N=T_NT_D
    $$

They are both polynomials in $T$, and are uniquely determined by $T$.

This decomposition is called the Jordan decomposition of $T$, where $T_D$ is called the diagonalizable part of $T$, and $T_N$ is called the nilpotent part of $T$.

Similarly, there is the Jordan decomposition of matrices:

**Theorem:** Let $A$ be an $n \times n$ matrix. Then there exists a diagonalizable matrix $D$ and a nilpotent matrix $N$ such that:

-   $$
    A=D+N
    $$
-   $$
    DN=ND
    $$

They are both polynomials in $A$, and are uniquely determined by $A$.

This decomposition is called the Jordan decomposition of $A$, where $D$ is called the diagonalizable part of $A$, and $N$ is called the nilpotent part of $A$.

## Lambda Matrices

The following introduces a more general class of matrices containing a variable parameter $\lambda$, not merely a table of numbers. This discussion is more general than that of matrices over a field of numbers.

For $\lambda$-matrices, the corresponding field becomes the field of rational functions in one variable $\lambda$.

A matrix whose entries are polynomials in $\lambda$ is called a $\lambda$-matrix, denoted $A(\lambda)$.

Since a polynomial field contains a number field, numeric matrices are special cases of $\lambda$-matrices. In particular, the characteristic matrix $\lambda I - A$ of a numeric matrix $A$ is a $\lambda$-matrix.

### Elementary Operations on Lambda Matrices

For $\lambda$-matrices, addition, subtraction, multiplication, and elementary operations can be defined similarly. For square $\lambda$-matrices, determinant, minor, and cofactor can also be defined.

For $\lambda$-matrices, elementary operations are mostly the same as for numeric matrices, except that the row-addition operation is modified (taking row operations as an example):

-   Multiply a row by a polynomial $\varphi(\lambda)$ in $\lambda$ and add to another row.

Note that the row-scaling operation is not modified. This is because row addition does not change the determinant, while row scaling does. To preserve the rank properties in the polynomial field, the determinant can only be changed over a number field.

The corresponding elementary matrices are modified accordingly.

It is easy to see that the determinants of the three types of elementary matrices are all nonzero constants, hence all are full rank. Therefore, left or right multiplication by them does not change the rank of a $\lambda$-matrix.

If $A(\lambda)$ can be transformed into $B(\lambda)$ through a finite number of elementary operations, then $A(\lambda)$ and $B(\lambda)$ are said to be equivalent.

For $\lambda$-matrices, equivalent implies same rank. The converse is not true, which differs from numeric matrices.

## Smith Normal Form

**Theorem:** Let the rank of a $\lambda$-matrix be $r$. Then $A(\lambda)$ is always equivalent to:

$$
\begin{pmatrix}
D(\lambda) & 0\\
0 & 0\\
\end{pmatrix}
$$

where:

$$
D(\lambda)=\begin{pmatrix}
d_1(\lambda) &  \\
 & \ddots & \\
 &  & d_r(\lambda)\\
\end{pmatrix}
$$

Each $d_i(\lambda)$ is a monic polynomial, and consecutive polynomials satisfy the divisibility relation $d_i(\lambda)|d_{i+1}(\lambda)$.

This normal form is called the Smith normal form, and $d_i(\lambda)$ are called invariant factors.

The specific method to compute the Smith normal form is: eliminate from the top-left to bottom-right, each time taking the greatest common divisor of all remaining polynomials in the top-left corner, and using that element to zero out the rest of that row and column.

**Theorem:** The condition that $A(\lambda)$ and $B(\lambda)$ are equivalent is equivalent to the condition that $A(\lambda)$ and $B(\lambda)$ have exactly the same invariant factors.

### Elementary Divisors

By the fundamental theorem of algebra, let the invariant factors of $A(\lambda)$ be $d_1(\lambda),d_2(\lambda),\cdots,d_m(\lambda)$, with factorization:

$$
d_i(\lambda)={(\lambda-\lambda_1)}^{e_{i1}}{(\lambda-\lambda_2)}^{e_{i2}}\cdots{(\lambda-\lambda_S)}^{e_{iS}}
$$

where $\lambda_1,\cdots,\lambda_S$ are distinct. Since:

$$
d_i(\lambda)|d_{i+1}(\lambda)
$$

the exponents $e_{1j},e_{2j},\cdots,e_{mj}$ are non-decreasing, and the last factor $d_m(\lambda)$ has all exponents nonzero.

All factors with positive exponent in the above expression are collectively called the elementary divisors of $A(\lambda)$.

Note that elementary divisors count multiplicities. If for some $j$, the exponent $e_{ij}$ appears multiple times, the corresponding elementary divisor ${(\lambda-\lambda_j)}^{e_{ij}}$ should also appear the same number of times.

The previous theorem states that $A(\lambda)$ and $B(\lambda)$ are equivalent if and only if they have exactly the same invariant factors. Same invariant factors obviously imply same elementary divisors, but not conversely. In fact, we have:

**Theorem:** $A(\lambda)$ and $B(\lambda)$ having exactly the same invariant factors is equivalent to having exactly the same elementary divisors and rank.

Thus, "exactly the same elementary divisors and rank" is also a criterion for equivalence of $\lambda$-matrices.

During elementary operations, one can also first transform $A(\lambda)$ to a diagonal matrix, then find the elementary divisors and rank, and finally get the invariant factors for the normal form. There is:

**Theorem:** Let $A(\lambda)$ be equivalent to the diagonal matrix:

$$
\operatorname{diag}\{f_1(\lambda),f_2(\lambda),\cdots,f_r(\lambda),0,\cdots,0\}
$$

Then the factors ${(\lambda-\lambda_j)}^{e_{ij}}$ of $f_1(\lambda),f_2(\lambda),\cdots,f_r(\lambda)$, where each $f_i$ is a product of linear factors, together form the elementary divisors of $A(\lambda)$.

The specific method to construct invariant factors from elementary divisors and rank is: first classify the elementary divisors by factors, arrange them in a table, put factors of the same type in the same row in descending powers, fill the columns to rank $r$ with 1's, then the product of each column forms an invariant factor.

### Application to Characteristic Matrices

If $A$ and $B$ are numeric matrices, then their characteristic matrices are $\lambda$-matrices. We have:

**Theorem:** Two numeric matrices $A$ and $B$ are similar if and only if their characteristic matrices $\lambda I-A$ and $\lambda I-B$ are equivalent.

Since the characteristic matrix $\lambda I-A$ has exactly $n$ entries of $\lambda$ on the main diagonal, its rank is $n$. From the above, characteristic matrices of same-sized numeric matrices always have the same rank, so we have the equivalence:

Numeric matrices $A$ and $B$ are similar if and only if their characteristic matrices $\lambda I-A$ and $\lambda I-B$ have exactly the same elementary divisors.

For the characteristic matrix $\lambda I-A$, elementary operations preserve equivalence, so do not change the rank.

Observing the three types of elementary operations, since the only modified operation (row addition) does not change the determinant, in fact all three types of elementary operations only change the determinant polynomial by a constant factor, thus do not change the factorization or degree of the determinant polynomial.

Therefore, the determinant of the characteristic matrix $\lambda I-A$ is an $n$-degree polynomial. After transforming to Smith normal form via elementary operations, since the rank is $n$, the determinant equals the product of all invariant factors on the main diagonal, which also equals the product of all elementary divisors. Thus, the sum of the degrees of all elementary divisors of $\lambda I-A$ equals $n$.

## Jordan Normal Form

A matrix

$$
\begin{pmatrix}
\lambda & 1 & 0 & \cdots & 0 & 0\\
0 & \lambda & 1 & \cdots & 0 & 0\\
0 & 0 & \lambda & \cdots & 0 & 0\\
\vdots & \vdots & \vdots &  & \vdots & \vdots\\
0 & 0 & 0 & \cdots & \lambda & 1\\
0 & 0 & 0 & \cdots & 0 & \lambda\\
\end{pmatrix}
$$

with all elements on the main diagonal equal to $\lambda$, all elements immediately above the main diagonal equal to $1$, and all other elements $0$, is called a Jordan matrix (or Jordan block) associated with $\lambda$.

Clearly, a nilpotent Jordan matrix is a special case of a Jordan matrix, namely when $\lambda = 0$.

**Theorem:** Let $T$ be a transformation on an $n$-dimensional space $V$, and $\lambda_1,\cdots,\lambda_k$ be all distinct eigenvalues of $T$. Then there exists a basis such that the matrix of $T$ with respect to this basis has the form:

$$
\begin{pmatrix}
B_1 &  &  & 0\\
 & B_2 &  & \\
 &  & \ddots & \\
0 &  &  & B_k\\
\end{pmatrix}
$$

where

$$
B_i=\begin{pmatrix}
J_{i1} &  &  & 0\\
 & J_{i2} &  & \\
 &  & \ddots & \\
0 &  &  & J_{is_i}\\
\end{pmatrix}
$$

and $J_{i1},\cdots,J_{is_i}$ are all Jordan blocks associated with $\lambda_i$.

The proof proceeds as follows. First, according to the minimal polynomial:

$$
m_A(\lambda)={(\lambda-\lambda_1)}^{r_1}{(\lambda-\lambda_2)}^{r_2}\cdots{(\lambda-\lambda_k)}^{r_k}
$$

we have the primary decomposition:

$$
V=V_1\oplus V_2\oplus\cdots\oplus V_k
$$

where:

$$
V_i=N\left({(A-\lambda_i I)}^{r_i}\right)
$$

and $A$ is the matrix corresponding to $T$.

Let $S_i$ be the restriction of $T$ to $V_i$, denoted ${T|}_{V_i}$. Next, we attempt to perform Jordan decomposition on each $S_i$.

Let $T_e$ be the identity transformation on $V$. Unlike the previous Jordan decomposition, denote $T_i$ as the nilpotent part in the Jordan decomposition of $S_i$:

$$
S_i=\lambda_i T_e+T_i
$$

Then $T_i$ is a nilpotent transformation on subspace $V_i$, which is indeed the restriction ${(T-\lambda_i T_e)|}_{V_i}$.

The subspace $V_i$ can be decomposed into a direct sum of cyclic subspaces for the nilpotent transformation $T_i$:

$$
V_i=W_{i1}\oplus W_{i2}\oplus\cdots\oplus W_{is_i}
$$

In each cyclic subspace $W_{ij}$, take a cyclic basis and arrange in reverse order to form a basis of $V_i$. Then the matrix of $T_i$ with respect to this basis has the form:

$$
N_i=\begin{pmatrix}
N_{i1} &  &  & 0\\
 & N_{i2} &  & \\
 &  & \ddots & \\
0 &  &  & N_{is_i}\\
\end{pmatrix}
$$

All $N_{ij}$ are nilpotent Jordan blocks. Then with respect to the basis chosen for $V_i$, the matrix of $S_i$ is:

$$
B_i=\begin{pmatrix}
\lambda_i &  &  & 0\\
 & \lambda_i &  & \\
 &  & \ddots & \\
0 &  &  & \lambda_i\\
\end{pmatrix}+\begin{pmatrix}
N_{i1} &  &  & 0\\
 & N_{i2} &  & \\
 &  & \ddots & \\
0 &  &  & N_{is_i}\\
\end{pmatrix}=\begin{pmatrix}
J_{i1} &  &  & 0\\
 & J_{i2} &  & \\
 &  & \ddots & \\
0 &  &  & J_{is_i}\\
\end{pmatrix}
$$

Here $J_{i1},J_{i2},\cdots,J_{is_i}$ are all Jordan blocks associated with $\lambda_i$.

For each subspace $V_i$, choose a basis as above. Putting them together forms a basis of $V$. Then the matrix of $T$ with respect to this basis exactly has the form prescribed in the theorem.

A matrix of the form:

$$
\begin{pmatrix}
J_1 &  &  & 0\\
 & J_2 &  & \\
 &  & \ddots & \\
0 &  &  & J_m\\
\end{pmatrix}
$$

where each $J_i$ is a Jordan block, is called a Jordan normal form.

**Theorem:** Every $n \times n$ matrix $A$ is similar to a Jordan normal form. Apart from the order of Jordan blocks, the Jordan normal form similar to $A$ is uniquely determined by $A$.

Note that in the constructed matrix $B_i$, the first term is a scalar multiple of the identity, so it commutes with the second term. Therefore, the first term is the diagonalizable part of the Jordan decomposition of $B_i$, and the second term is the nilpotent part.

In the Jordan normal form of a matrix, the diagonal matrix formed by the elements on the main diagonal is the diagonalizable part of the Jordan normal form, and replacing those elements with $0$ gives the nilpotent part.

**Theorem:** For each Jordan block in the Jordan normal form of matrix $A$:

$$
J_i=\begin{pmatrix}
\lambda_i & 1 &  &  & \\
 & \lambda_i & 1 &  & \\
 &  & \ddots & \ddots & \\
 &  &  & \ddots & 1\\
 &  &  &  & \lambda_i\\
\end{pmatrix}
$$

it corresponds to an elementary divisor ${(\lambda-\lambda_i)}^{n_i}$ of the characteristic matrix $\lambda I - A$. All elementary divisors of $\lambda I - A$ correspond to all Jordan blocks in the Jordan normal form of $A$.

This is because matrix $A$ is similar to its Jordan normal form, so their characteristic matrices are also equivalent. Transforming the characteristic matrix of the Jordan normal form to Smith normal form reveals this.

From this theorem, with the elementary divisors of the characteristic matrix $\lambda I - A$, one can write the Jordan normal form of $A$.

A corollary is that matrix $A$ is diagonalizable if and only if all elementary divisors of $\lambda I - A$ are linear.

## Frobenius Theorem

Above, we noted that the Smith normal form of an $n$-th order characteristic matrix has rank $n$.

**Theorem:** Let the Smith normal form of the characteristic matrix $\lambda I - A$ of matrix $A$ be:

$$
\operatorname{diag}\{d_1(\lambda),d_2(\lambda),\cdots,d_n(\lambda)\}
$$

Then the last invariant factor $d_n(\lambda)$ is exactly the minimal polynomial $m_A(\lambda)$ of matrix $A$.

**Corollary:** Equivalent conditions for matrix $A$ to be diagonalizable are:

-   The minimal polynomial $m_A(\lambda)$ has no repeated roots.
-   No invariant factor of the characteristic matrix $\lambda I - A$ has repeated roots.
-   All elementary divisors of the characteristic matrix $\lambda I - A$ are linear.