Linear mappings study maps between linear spaces.

A linear mapping can be represented in matrix form. Therefore, many concepts from matrices have corresponding relationships in linear mappings.

## Linear Mappings and Linear Transformations

Let $V$ and $W$ be two linear spaces over field $F$, and $T$ be a map from $V$ to $W$.

If for any vectors $x, y$ in $W$ and any scalars $k, l$ in field $F$, we have:

$$
T(kx+ly)=kTx+lTy
$$

Then $T$ is called a linear mapping from $V$ to $W$. If $W=V$, then $T$ is called a linear transformation on $V$.

For example, the identity transformation $T_e$ keeps the space unchanged, and the zero transformation $T_0$ maps the space to the zero space.

We can denote $L(V,W)$ as the set of all linear mappings from $V$ to $W$. For all linear transformations $L(V,V)$, we also write $L(V)$.

### Properties

-   A linear mapping maps the zero vector to the zero vector.
-   A linear mapping preserves linear operation forms, i.e., the linear mapping of a linear operation equals the linear operation of the mappings.
-   A linear mapping preserves linear dependence, i.e., if vectors are linearly dependent before mapping, they are also linearly dependent after mapping.

However, a linear mapping does not preserve linear independence. Vectors linearly independent before mapping may not be linearly independent after mapping.

## Matrix Representation of Linear Mappings

Let the dimension of $V$ be $n$, with a basis $\alpha_1,\cdots,\alpha_n$, and the dimension of $W$ be $m$, with a basis $\beta_1,\cdots,\beta_m$. Let $T$ be a linear mapping from $V$ to $W$.

Express the image of each $\alpha$ under $T$ using $\beta$:

$$
T\alpha_j=a_{1j}\beta_1+\cdots+a_{mj}\beta_m
$$

Using matrix notation:

$$
T(\alpha_1,\cdots,\alpha_n)=(T\alpha_1,\cdots,T\alpha_n)=(\beta_1,\cdots,\beta_m)A
$$

Matrix $A$ is called the matrix representation of linear mapping $T$ with respect to these two bases.

## Kernel Space and Image Space of Linear Mappings

The kernel space and image space here are described from the perspective of linear mappings. Through the matrix representation, we can see that the kernel space and image space of a linear mapping are consistent with those of a matrix.

Let $T$ be a linear mapping from space $V$ to space $W$. Define:

$$
N(T)=\{x\in V|Tx=0\}
$$

$$
R(T)=Im(T)=\{y\in W|y=Tx,Vx\in V\}
$$

It is easy to verify that $N(T)$ is a subspace of $V$, and $R(T)$ is a subspace of $W$. $N(T)$ and $R(T)$ are called the kernel space and image space of $V$. The dimension of $N(T)$ is called the **nullity** or **defect** of $T$, and the dimension of $R(T)$ is called the **rank** of $T$.

**Theorem:** Let $T$ be a linear mapping from space $V$ to space $W$, with $V$ of finite dimension. Then $N(T)$ and $R(T)$ are both finite-dimensional, and:

$$
\operatorname{dim} N(T)+\operatorname{dim} R(T)=\operatorname{dim} V
$$

That is, the defect plus rank of $T$ equals the dimension of its domain $V$.

## Matrix Representation of Linear Transformations

Let the dimension of $V$ be $n$, with a basis $\alpha_1,\cdots,\alpha_n$. Let $T$ be a linear transformation on $V$. Then:

$$
T\alpha_j=a_{1j}\alpha_1+\cdots+a_{nj}\alpha_n
$$

Using matrix notation:

$$
T(\alpha_1,\cdots,\alpha_n)=(T\alpha_1,\cdots,T\alpha_n)=(\alpha_1,\cdots,\alpha_n)A
$$

Matrix $A$ is called the matrix representation of linear transformation $T$ with respect to this basis.

From the space structure and linearity of $T$, $T$ is completely determined by $T\alpha_1,\cdots,T\alpha_n$. Hence, $T$ uniquely determines a matrix $A$.

**Theorem:** Let $V$ have dimension $n$, and $\alpha_1,\cdots,\alpha_n$ be a basis of $V$. For any $n \times n$ matrix $A$, there exists exactly one linear transformation $T$ from $V$ to $V$ such that the matrix of $T$ is exactly $A$.

**Corollary:** There is a one-to-one correspondence between $L(V,V)$ and all $n \times n$ matrices.

For example: the zero transformation corresponds to the zero matrix, and the identity transformation corresponds to the identity matrix.

## The Space Formed by Linear Transformations

**Theorem:** $L(V)$ can also form a vector space. Define operations in $L(V)$: for any $T_1, T_2$ in $L(V)$, any $x$ in $V$, and any $k$ in field $F$:

$$
(T_1+T_2)x=T_1x+T_2x
$$

$$
(kT_1)x=k(T_1x)
$$

It is easy to verify that $L(V)$ is a vector space over $F$, called the linear transformation space.

For linear transformations $T_1$ and $T_2$ in $L(V)$, define the product $T_1T_2$ as:

$$
(T_1T_2)x=T_2(T_1x)
$$

It can be verified that $(T_1T_2)$ is also a linear transformation in $L(V)$. The product of linear transformations satisfies the associative law but not the commutative law, similar to matrix multiplication.

For linear transformation $T_1$ in $L(V)$, if there exists linear transformation $T_2$ in $L(V)$ such that for any vector $x$ in $V$:

$$
(T_1T_2)x=T_1(T_2x)=x
$$

Then $T_2$ is called the inverse of $T_1$, denoted:

$$
T_2=T_1^{-1}
$$

And:

$$
T_1T_2=T_2T_1=T_e
$$

**Theorem:** Let $V$ have dimension $n$, and $\alpha_1,\cdots,\alpha_n$ be a basis of $V$. Under this basis, the matrix of linear transformation $T_1$ is $A$, and the matrix of $T_2$ is $B$. Then:

-   The matrix of linear transformation $T_1+T_2$ is $A+B$
-   The matrix of scalar multiplication $kT_1$ is $kA$
-   The matrix of product $T_1T_2$ is $AB$
-   If the inverse of linear transformation $T_1$ exists, its matrix is $A^{-1}$

## Coordinates

Let the $n$ vectors $x$ be a basis of $n$-dimensional space $V$. For any vector $y$ in $V$, let:

$$
y=a_1x_1+a_2x_2+\cdots+a_nx_n=(x_1,x_2,\cdots,x_n)\begin{pmatrix}a_1\\a_2\\\vdots\\a_n\end{pmatrix}
$$

The column vector:

$$
\begin{pmatrix}a_1\\a_2\\\vdots\\a_n\end{pmatrix}
$$

is called the **coordinate** of vector $y$ with respect to basis $x_1,x_2,\cdots,x_n$.

As you can see, coordinates are column vectors composed of scalars from the field, which should be distinguished from vectors in the Abelian group.

## Coordinate Transformation Formula

Let $V$ have dimension $n$. Let $T$ be a transformation in $L(V)$, with matrix $A$ under basis $\alpha_1,\cdots,\alpha_n$. Let:

$$
\xi=(\alpha_1,\cdots,\alpha_n)\begin{pmatrix}x_1\\x_2\\\vdots\\x_n\end{pmatrix}
$$

And:

$$
T\xi=T(\alpha_1,\cdots,\alpha_n)\begin{pmatrix}y_1\\y_2\\\vdots\\y_n\end{pmatrix}
$$

Then:

$$
T\xi=T(\alpha_1,\cdots,\alpha_n)\begin{pmatrix}y_1\\y_2\\\vdots\\y_n\end{pmatrix}=(\alpha_1,\cdots,\alpha_n)A\begin{pmatrix}x_1\\x_2\\\vdots\\x_n\end{pmatrix}
$$

Column vectors in space $V$ are essentially all in the form "basis times coordinate". A column vector $x$ in space $V$ itself uses identity matrix $I$ as the basis, i.e., $x=Ix$.

Only when the same basis is fixed, and we consider a pure linear transformation $T$, the coordinate is simply left-multiplied by a regular matrix.

Consider linear transformation $T$ as a "filter" observing space $V$. The action of $T$ is on space $V$, distorting it. After applying the filter, the point itself doesn't change position.

This theorem also shows that for a linear transformation $T$ on a column vector basis, it is equivalent to right-multiplying the basis by a transition matrix.

Therefore, between different bases, coordinates are related by left-multiplying by the inverse of the transition matrix.

## Transition Matrix

Let the $n$ vectors $x$ and $n$ vectors $y$ be two bases of space $V$. For $1\leq i\leq n$, let each vector $y_i$ have coordinate:

$$
y_i=(x_1,x_2,\cdots,x_n)\begin{pmatrix}a_{1i}\\a_{2i}\\\vdots\\a_{ni}\end{pmatrix}
$$

Then the $n$ vectors $y$ form the matrix on the left side of the equation, and the $n$ coordinates form the matrix $A$ on the right side:

$$
(y_1,y_2,\cdots,y_n)=(x_1,x_2,\cdots,x_n)A
$$

Matrix $A$ is called the **transition matrix** from basis $x_1,x_2\cdots,x_n$ to basis $y_1,y_2\cdots,y_n$, also called the change of basis matrix.

Clearly, the transition matrix is invertible. From the above, the transition matrix from basis $y_1,y_2\cdots,y_n$ to basis $x_1,x_2\cdots,x_n$ is $A^{-1}$.

As noted earlier, the transition matrix is composed of scalars from the field, not vectors from the Abelian group arranged as a matrix. They should be distinguished.

Let the $n$ vectors $x$ and $n$ vectors $y$ be two bases of space $V$. For the same vector $z$ in space $V$, we have:

$$
z=(x_1,x_2,\cdots,x_n)\begin{pmatrix}\xi_1\\\xi_2\\\vdots\\\xi_n\end{pmatrix}=(y_1,y_2\cdots,y_n)\begin{pmatrix}\eta_1\\\eta_2\\\vdots\\\eta_n\end{pmatrix}
$$

Substituting from earlier:

$$
(y_1,y_2\cdots,y_n)=(x_1,x_2\cdots,x_n)A
$$

By uniqueness, we get:

$$
\begin{pmatrix}\xi_1\\\xi_2\\\vdots\\\xi_n\end{pmatrix}=A\begin{pmatrix}\eta_1\\\eta_2\\\vdots\\\eta_n\end{pmatrix}
$$

Or:

$$
\begin{pmatrix}\eta_1\\\eta_2\\\vdots\\\eta_n\end{pmatrix}=A^{-1}\begin{pmatrix}\xi_1\\\xi_2\\\vdots\\\xi_n\end{pmatrix}
$$

This is purely a transformation between coordinates. All coordinate transformation formulas are in the scalar field. As distinguished earlier, vectors in linear spaces and Abelian groups are "abstract vectors", while coordinates and elements of transition matrices are in the scalar field, considered as "concrete vectors". The two types should be considered "different things".

A matrix can transform the entire space, i.e., all coordinates. Column vector $x$ as a coordinate ranges over the entire space.

Identity matrix $I$ is composed of unit vectors. Matrix $A$ transforms identity matrix $I$ to each column vector of matrix $A$, i.e., transforms unit vectors to each column vector of matrix $A$. Therefore, left-multiplying by matrix $A$ can also be seen as performing such a transformation on the space.

Left-multiplying a vector by a matrix can also be seen as left-multiplying coordinates by a vector set. Using the coordinate perspective:

$$
Iy=Xa
$$

The same column vector $y$, in the "normal" space with identity matrix $I$ as the basis, has coordinate $y$, but in the new transformed space, the coordinate will be recorded as $a$. In this way, matrix $X$ is not only a basis in the normal space but also the transition matrix from vector set $I$ to vector set $X$.

Linear transformation $T$ maps one basis to another, so coordinates are also mapped to other coordinates.

If the linear transformation $T$ that maps basis $\alpha$ to $\beta$ has transition matrix $A$, then the corresponding basis matrix satisfies $\beta=\alpha A$.

Thus, the coordinate relationship is exactly reversed. Suppose after linear transformation $T$, the coordinate is $b$, i.e., after applying the filter, we observe coordinate $b$. Then the point's representation in $V$ is $\beta b$. The way to restore it is using the transition matrix, writing the point's representation in $V$ as $\alpha Ab$. Then the coordinate transformation by left-multiplying by the inverse of the transition matrix is now clear.

## Linear Transformations and Matrix Similarity

Consider a linear transformation $T$ on space $V$ with respect to basis $\alpha$ of $V$:

Linear transformation $T$ acts on basis $\alpha$, mapping $\alpha$ to $T(\alpha)$, which is equivalent to right-multiplying $\alpha$ by $A$, i.e., $T(\alpha)=\alpha A$.

Matrix similarity considers the question: same linear transformation $T$, described as matrix $B$ in space $V$ with basis $\beta$, and as matrix $A$ in space $V$ with basis $\alpha$.

If the transition matrix is $C$, i.e., $\beta=\alpha C$, what is the relationship between the two descriptions $B$ and $A$?

Since it is the same transformation $T$, we find that the relationship of the transition matrix always holds before and after transformation:

$$
T(\beta)=T(\alpha)C=\alpha AC
$$

Linear transformation $T$ from the perspective of basis $\beta$ is still right-multiplication. Basis $\beta$ transforms to basis $\alpha$ then right-multiplies by $C$. Before and after transformation, the relationship of transition matrix $C$ is maintained:

$$
T(\beta)=\beta B=\alpha CB
$$

Thus the problem is solved:

$$
B=C^{-1}AC
$$

**Theorem:** Let $T$ be a transformation in $L(V)$. Then $T$ is **similar** under different bases.

For square matrices $A$ and $B$, if there exists an invertible matrix $C$ such that $B=C^{-1}AC$, then $A$ and $B$ are similar.

Matrix similarity preserves rank, so matrix similarity implies matrix equivalence. However, two equivalent matrices are not necessarily similar.

Since matrix similarity is closely related to shape, there is no relationship between matrix similarity and vector set equivalence or system equivalence.

Looking back, the interpretation of matrix similarity involves four equations: $\beta=\alpha C$, $T(\alpha)=\alpha A$, $T(\beta)=\beta B$, $T(\beta)=T(\alpha)C$.

## References

-   [【Official Bilingual/Collection】Essence of Linear Algebra - Series Collection P13 09 - Basis Change](https://www.bilibili.com/video/BV1Ls411b7r2)