## Eigenspaces

All eigenvectors of matrix $A$ belonging to $\lambda_0$, plus the zero vector, form a vector space called an eigenspace of matrix $A$, denoted $E(\lambda_0)$. It is the solution space of the homogeneous linear system:

$$
(\lambda_0 I-A)X=0
$$

For eigenspace $E(\lambda_i)=N(\lambda_i I-A)$, by the rank-nullity theorem:

$$
r(\lambda_i I-A)+\operatorname{dim} N(\lambda_i I-A)=n
$$

Therefore, the dimension of eigenspace $E(\lambda_i)$ is:

$$
\operatorname{dim} E(\lambda_i)=n-r(\lambda_i I-A)
$$

This is also called the **geometric multiplicity** of $\lambda_i$.

## Invariant Subspaces

When studying linear transformation $T$, we often want to choose a basis of space $V$ such that the matrix of $T$ with respect to this basis has the simplest possible form.

Let $V$ be a vector space over field $F$, $W$ be a subspace of $V$, and $T$ be a linear transformation on $V$. If for any vector $x$ in $W$, $T(x)$ is also in $W$ (also called the space being invariant or stable under the transformation), then $W$ is called an invariant subspace of $T$.

The space being invariant under a transformation does not mean the coordinates truly "don't change" under transformation. They might undergo stretching or other deformations, as long as after deformation they still fall within the space.

-   Any subspace of a vector space $V$ is an invariant subspace of the scalar multiplication transformation.
-   For any linear transformation $T$ on $V$, space $V$ and the zero subspace are invariant subspaces of $T$, called trivial invariant subspaces.
-   The intersection and sum of invariant subspaces are also invariant subspaces.

Let $W$ be an invariant subspace of linear transformation $T$. Considering only the action of $T$ on invariant subspace $W$, we obtain a linear transformation on subspace $W$ itself, called the restriction of $T$ to subspace $W$, denoted ${T|}_W$.

For any linear transformation $T$ on $V$, the image space $R(T)$ and kernel space $N(T)$ are invariant subspaces of $T$. The meaning in these two cases is: space $V$ before and after transformation completes its own compression (image space), or compression to $0$ (kernel space).

For any linear transformation $T$ on $V$, the eigenspaces of $T$ are invariant subspaces of $T$.

## Primary Decomposition

By the fundamental theorem of algebra, the minimal polynomial can be factored as:

$$
m_A(\lambda)={(\lambda-\lambda_1)}^{r_1}\cdots{(\lambda-\lambda_S)}^{r_S}
$$

Consider substituting the variable $\lambda$ in the minimal polynomial with matrix $A$. The kernels of each factor form a series of invariant subspaces of matrix $A$:

$$
W_i=N({(\lambda_i I-A)}^{r_i})
$$

**Theorem:** The dimension of invariant subspace $W_i$ is exactly the algebraic multiplicity of eigenvalue $\lambda_i$.

Recall that algebraic multiplicity refers to the exponent of each factor in the characteristic polynomial, and geometric multiplicity refers to the dimension of eigenspace $E(\lambda_i)=N(\lambda_i I-A)$. This invariant subspace $W_i$ and eigenspace $E(\lambda_i)$ are both kernel spaces of matrices, and the two matrices are related by the minimal polynomial's $r_i$-th power. That is, the dimension of the eigenspace is the geometric multiplicity. The "eigenspace" after applying the minimal polynomial's $r_i$-th power becomes an "invariant subspace", whose dimension reaches the algebraic multiplicity of the characteristic polynomial.

This theorem is actually a corollary of the primary decomposition theorem below.

Let matrix $A$ correspond to linear transformation $T$. Let $T_i={T|}_{W_i}$ be the restriction of $T$ to each subspace $W_i$. Then the minimal polynomial of $T_i$ is $(x-\lambda_i)^{r_i}$.

**Theorem:** Let $V$ be a vector space over field $F$, and $T$ be a linear transformation on $V$. Then space $V$ can undergo primary decomposition with respect to $T$, decomposed into a direct sum of invariant subspaces $W_i$.

$$
V=W_1\oplus W_2\oplus\cdots\oplus W_S
$$

This means that the matrix of $T$ with respect to some basis is a block diagonal matrix:

$$
\operatorname{diag}\{A_1,A_2,\cdots,A_S\}
$$

where $A_i$ is the matrix of $T_i$ with respect to the corresponding basis.

This theorem shows that invariant subspaces can be used to simplify the matrix of a linear transformation.

## Diagonalizable Matrices

For an $n \times n$ matrix $A$, if it is similar to a diagonal matrix, then $A$ is called a diagonalizable matrix, or simple matrix.

-   The sum, product, and inverse (if it exists) of diagonal matrices are still diagonal matrices. The elements on the diagonal are its eigenvalues.
-   The matrix of linear transformation $T$ being diagonalizable is equivalent to the matrix of $T$ with respect to some basis being a diagonal matrix.

**Theorem:** Let all distinct eigenvalues of matrix $A$ be $\lambda_1,\cdots,\lambda_m$. The following statements are equivalent:

-   Matrix $A$ is diagonalizable.
-   Matrix $A$ has $n$ linearly independent eigenvectors.
-   The following formula holds:

$$
\operatorname{dim} E(\lambda_1)+\cdots+\operatorname{dim} E(\lambda_m)=n
$$

Earlier, we noted that the exponent of each factor in the factorization of the characteristic polynomial is called algebraic multiplicity, and the dimension of the eigenspace is called geometric multiplicity. This theorem also shows that matrix $A$ is diagonalizable if and only if for each eigenvalue $\lambda$ of $A$, its algebraic multiplicity equals its geometric multiplicity.

**Corollary:** If an $n \times n$ matrix $A$ has exactly $n$ distinct eigenvalues, then it is necessarily diagonalizable. The converse is not necessarily true.

**Theorem:** Matrix $A$ is diagonalizable if and only if the minimal polynomial $m_A(\lambda)$ has no repeated roots.

Similarity also preserves linear dependence relations among eigenvectors.

Eigenvectors may not be real numbers. It is also possible that $n$ linearly independent eigenvectors cannot be found.

For repeated eigenvalues, the eigenvectors span a space. To describe this space, we need to select representatives from it. Generally, linearly independent representatives are selected, and the number of representatives equals the dimension of the space.

When selecting representatives, we often orthogonalize and normalize them. The final result is a set of orthonormal representatives.

Eigenvectors are not necessarily orthogonal. Eigenvectors belonging to distinct eigenvalues may not be orthogonal. Therefore, orthogonalization can only be performed on eigenvectors of repeated eigenvalues. However, normalization can be performed on any eigenvector.

## Nilpotent Matrices

Let $T$ be a linear transformation on space $V$. If there exists a positive integer $r$ such that $T^r$ is the zero transformation, then $T$ is called a nilpotent transformation on space $V$.

For some positive integer $r$, a matrix satisfying $N^r=0$ is called a nilpotent matrix.

Generally, we can further assume $r$ is the smallest positive integer such that $T^r$ is the zero transformation. Then the minimal polynomial of $T$ is $x^r$. Then there exists a vector $\xi_0$ such that:

-   $$
    T^r(\xi_0)=0
    $$
-   $$
    T^{r-1}(\xi_0)\neq 0
    $$

### Cyclic Subspace

**Theorem:** Let $T$ be a linear transformation on space $V$, and $\xi$ be a vector in $V$. If there exists a positive integer $s$ such that:

-   $$
    T^s(\xi)=0
    $$
-   $$
    T^{s-1}(\xi)\neq 0
    $$

Then the vectors $\xi,T(\xi),\cdots,T^{s-1}(\xi)$ are linearly independent.

From this theorem, we can give a definition:

Let $T$ be a linear transformation on space $V$, and $W$ be a subspace of $V$. If there exists a vector $\xi_0$ and a positive integer $r$ such that:

-   The vectors $\xi_0,T(\xi_0),\cdots,T^{r-1}(\xi_0)$ form a basis of $W$.
-   The following equation holds:

    $$
    T^r(\xi_0)=0
    $$

Then subspace $W$ is called a cyclic subspace with respect to $T$, or simply a $T$-cyclic subspace. At this point, $\xi_0$ is called a generating vector of cyclic subspace $W$, and the vectors $\xi_0,T(\xi_0),\cdots,T^{r-1}(\xi_0)$ are called a cyclic basis of $W$.

Clearly, a $T$-cyclic subspace $W$ is invariant under $T$. Moreover, for any vector $\xi$ in cyclic subspace $W$, we have $T^r(\xi)=0$, where $r$ is the dimension of the cyclic subspace.

### Nilpotent Jordan Blocks

If space $W$ is a cyclic subspace of transformation $T$, then the restriction ${T|}_W$ of $T$ to $W$ is a nilpotent transformation on $W$. Moreover, the matrix of ${T|}_W$ with respect to the reverse-order cyclic basis $T^{r-1}(\xi_0),T^{r-2}(\xi_0),\cdots,\xi_0$ of $W$ is an $r$-th order upper triangular matrix of the following form:

$$
N_r=\begin{pmatrix}
0 & 1 & 0 & \cdots & 0 & 0\\
0 & 0 & 1 & \cdots & 0 & 0\\
0 & 0 & 0 & \cdots & 0 & 0\\
\vdots & \vdots & \vdots &   & \vdots& \vdots\\
0 & 0 & 0 & \cdots & 0 & 1\\
0 & 0 & 0 & \cdots & 0 & 0\\
\end{pmatrix}
$$

Matrix $N_r$ is called an $r$-th order nilpotent Jordan matrix, or $r$-th order nilpotent Jordan block.

Let $T$ be a nilpotent transformation on an $n$-dimensional space $V$. The uniquely determined set of positive integers $r_1\geq\cdots\geq r_S$ appearing in the decomposition of $V$ into $T$-cyclic subspaces is called the invariant exponents of $T$.

For an $n$-th order nilpotent matrix $A$, $A$ is similar to a matrix $N$ of the above form, and a uniquely determined sequence of positive integers $r_1\geq\cdots\geq r_S$ is called the invariant exponents of matrix $A$.

Although nilpotent matrices cannot be diagonalized, they can be similar to such a standard form. In the Jordan normal form, by combining similarity diagonalization with the standard form of nilpotent matrices, we obtain the standard form that any general matrix can achieve through similarity transformations.

### Some Theorems

1.  Let $T$ be a nilpotent transformation on space $V$, and

    $$
    h(x)=a_0+a_1x+\cdots+a_mx^m
    $$

    be a polynomial. Then $h(T)$ has an inverse transformation if and only if $a_0\neq 0$. When $h(T)$ is invertible, its inverse is also a polynomial in $T$.

2.  Let $T$ be a nilpotent transformation on space $V$, and $W$ be an $r$-dimensional $T$-cyclic subspace. Let $\xi$ be a vector in $W$. If there exists an integer $k$ such that

    $$
    T^{r-k}(\xi)=0
    $$

    then there exists a vector $\eta$ in $W$ such that

    $$
    \xi=T^k(\eta)
    $$

3.  Let $T$ be a nilpotent transformation on an $n$-dimensional space $V$, and $x^r$ be the minimal polynomial of $T$. Let $W_1$ be an $r$-dimensional $T$-cyclic subspace. Then there exists a complement subspace $W_2$ of $W_1$ such that:

    $$
    V=W_1\oplus W_2
    $$

    And $W_2$ is also invariant under $T$.

4.  Let $T$ be a nilpotent transformation on an $n$-dimensional space $V$. Then $V$ can be decomposed into a direct sum of $T$-cyclic subspaces:

    $$
    V=W_1\oplus W_2\oplus\cdots\oplus W_S
    $$

5.  Every $n$-th order nilpotent matrix is similar to a matrix of the form:

    $$
    N=\begin{pmatrix}
    N_{r_1} &   &   & 0\\
      & N_{r_2} &   &  \\
      &   & \cdots &  \\
    0 &   &   & N_{r_S}\\
    \end{pmatrix}
    $$

    where each $N_{r_i}$ is an $r_i$-th order nilpotent Jordan block.

6.  If we require that $T$-cyclic subspaces $W_i$ are arranged in descending order of dimension $r_i\geq\cdots\geq r_S$, then the decomposition of $V$ into $T$-cyclic subspaces is uniquely determined by $T$.