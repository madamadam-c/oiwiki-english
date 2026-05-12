author: codewasp942, Tiphereth-A

A vector space is a generalization of $d$-dimensional Euclidean space ($0\leq d\leq 3$), and related concepts can be found in [Relationship between Euclidean space and vector space](#relationship-between-euclidean-space-and-vector-space).

Prerequisites: Abelian groups, fields.

Informally, a set closed under an operation, satisfying associativity, identity, and inverses forms a group. If it also satisfies commutativity, it forms an Abelian group.

If a set is closed under the four arithmetic operations, it forms a field. See [Basic concepts of abstract algebra](../algebra/basic.md#field) for details.

## Definition

A vector space (or linear space) is a fundamental concept and important object of study in linear algebra. A vector space is an algebraic structure $(V, +, \cdot, \mathbb{P})$ consisting of a set of vectors $V$, a field $\Bbb{P}$, addition $+$, and scalar multiplication (scalar product).

Specifically, let $(V,+)$ be an Abelian group, and $\Bbb{P}$ be a field.

Define an algebraic operation between elements of $\Bbb{P}$ and elements of $V$, called **scalar multiplication**: $\cdot:\Bbb{P}\times V\mapsto V$, denoted $p\cdot v$ or $pv$, where $p$ is in field $\Bbb{P}$ and $v$ is in Abelian group $V$. This operation must be closed; the result is always meaningful and remains in group $V$.

And satisfy the following conditions:

1.  **Scalar multiplication distributes over vector addition**: For $\mathbf u,\mathbf v\in V,a\in \Bbb{P}$, $a(\mathbf u+\mathbf v)=a\mathbf u+a\mathbf v$
2.  **Scalar multiplication distributes over scalar addition**: For $a,b\in \Bbb{P},\mathbf u\in V$, $(a+b)\mathbf u=a\mathbf u+b\mathbf u$
3.  **Scalar multiplication is associative (consistent with field multiplication)**: For $a,b\in \Bbb{P},\mathbf u\in V$, $a(b\mathbf u)=(ab)\mathbf u$
4.  **Scalar multiplication identity**: Let $1\in \Bbb{P}$ be the multiplicative identity of $\Bbb{P}$. Then for $u\in V$, $1\mathbf u=\mathbf u$

Then the algebraic system $(V,+,\cdot,\mathbb{P})$ is called a **vector space** over $\Bbb{P}$, $\Bbb{P}$ is called the **base field** of the vector space, elements of $V$ are called **vectors**, and elements of $\Bbb{P}$ are called **scalars**. When $\Bbb{P}$ is the real number field, it is called a real vector space. When $\Bbb{P}$ is the complex number field, it is called a complex vector space.

Whether it's a sequence of numbers, an arrow, or something else, as long as it satisfies the above axioms, it can be considered a vector, and the theory of linear algebra can be applied.

The zero element of the additive group is called the zero vector, denoted $\mathbf 0$ or $\mathbf\theta$.

The original addition and subtraction of vectors in the Abelian group, combined with the newly defined scalar multiplication, are collectively called **linear operations**.

???+ note "Note"
    For convenience in the following discussion:
    
    1.  Elements of $V$ are not bolded.
    2.  The algebraic system $(V,+,\cdot,\mathbb{P})$ satisfying the vector space definition is also called a vector space.
    
    Please distinguish between these.

### Intuitive Understanding

Not strictly speaking, scalar multiplication corresponds to a kind of "**scaling**", elements of base field $\Bbb{P}$ represent the "**ratio**" of scaling, and vector addition corresponds to "**superposition**". At the same time, elements of $\Bbb{P}$ also represent the "**range of coordinates**" for vectors.

Conditions 1-4 describe the relationship between "scaling" and "superposition". This can be understood by considering arrows in the plane.

### Basic Properties

???+ note "Note"
    The following properties can be found in group theory, etc.

For a vector space $(V,+,\cdot,\Bbb{P})$:

1.  $\theta$ is unique
2.  $\forall\alpha\in V$, $-\alpha$ is unique
3.  $\exists 0\in\mathbb{P}$, $\forall\alpha\in V$, $0\alpha=\theta$
4.  $\forall k\in\mathbb{P}$, $k\theta=\theta$
5.  $(-1)\alpha=-\alpha,~\forall\alpha\in V$
6.  No zero divisors: $\forall\alpha\in V,k\in\mathbb{P}$, $k\alpha=\theta\implies k=0\lor\alpha=\theta$
7.  Cancellation law for addition: $\forall\alpha,\beta,\gamma\in V$, $\alpha+\beta=\alpha+\gamma\implies\beta=\gamma$

    > In fact, the cancellation law is a property of Abelian groups.

### Examples

1.  $\Bbb{P}^n$ forms a vector space over field $\Bbb{P}$ with addition and scalar multiplication. For example, $\Bbb{P}$ can be $\Bbb{R}$, $\Bbb{C}$, $\Bbb{N}_p$ (where $p$ is prime), etc.
2.  The $n \times m$ matrices over field $\Bbb{P}$, denoted $\Bbb{P}^{n\times m}$, form a vector space over $\Bbb{P}$ with matrix addition and scalar multiplication.
3.  The ring of single-variable polynomials over field $\Bbb{P}$, denoted $\Bbb{P}[x]$, forms a vector space over $\Bbb{P}$ with polynomial addition and scalar multiplication.
4.  The set of all continuous functions on interval $[a,b]$ (denoted $C[a,b]$) forms a vector space over the codomain field with "function addition" and "scalar multiplication of functions".

## Related Concepts

### Linear Dependence, Linear Independence

For a vector space $(V,+,\cdot,\Bbb{P})$:

1.  Vectors $a_1,a_2,\dots,a_n\in V$ are called a **vector set**.
2.  For $k_1,k_2,\dots,k_n\in\Bbb{P}$, $\sum_{i=1}^nk_ia_i$ is called a **linear combination** of the vector set $a_1,a_2,\dots,a_n$.
3.  If vector $\beta\in V$ can be expressed as a linear combination of vector set $a_1,a_2,\dots,a_n$, then $\beta$ is said to be **linearly represented** by vector set $a_1,a_2,\dots,a_n$.
4.  For $k_1,k_2,\dots,k_n\in\Bbb{P}$, if the vector set $a_1,a_2,\dots,a_n$ satisfies $\sum_{i=1}^nk_ia_i=\theta\iff k_i=0, i=1,2,\dots,n$, then the vector set $a_1,a_2,\dots,a_n$ is **linearly independent**; otherwise, the vector set $a_1,a_2,\dots,a_n$ is **linearly dependent**.

The zero vector is linearly dependent with any vector.

Linear representation or linear dependence can be written in matrix multiplication form:

$$
\beta=k_1a_1+k_2a_2+\cdots+k_ra_r=(a_1,a_2,\cdots,a_r)\begin{pmatrix} k_1 \\ k_2 \\ \vdots \\ k_r \end{pmatrix}
$$

By convention, vectors $a$ are placed side by side on the left; scalars $k$ are placed vertically on the right, forming a "column vector".

Note: The "column vector" formed by scalars here is just a convenient formal notation, not belonging to space $V$, and fundamentally differs from the vectors on the left. If the left-side vectors happen to be column vectors, arranging them side by side formally constitutes a "matrix", and the above product is exactly the common form of "matrix times column vector".

As noted below, linear representation is equivalent to the vector $\beta$ lying in the image space of the matrix $(a_1,a_2\cdots,a_r)$.

According to the definition below, the zero vector always lies in the image space. From the perspective of linear transformations, linear dependence is equivalent to multiple vectors being mapped to the zero vector after transformation, while linear independence is equivalent to only the zero vector itself being mapped to the zero vector.

#### Properties

For a vector space $(V,+,\cdot,\Bbb{P})$:

1.  If a subset of a vector set is linearly dependent, then the vector set is linearly dependent. If a vector set is linearly independent, then any non-empty subset is linearly independent. Brief summary: **"Large independent, small independent"; "Small dependent, large dependent"**.
2.  A vector set containing $\theta$ is linearly dependent.
3.  A vector set is linearly dependent if and only if some vector in the set can be linearly expressed by the other vectors.
4.  If vector $\beta$ can be linearly expressed by vector set $a_1,a_2,\dots,a_n$, then the expression is unique if and only if the vector set $a_1,a_2,\dots,a_n$ is linearly independent.
5.  If vector set $a_1,a_2,\dots,a_n$ is linearly independent, then vector $\beta$ can be linearly expressed by vector set $a_1,a_2,\dots,a_n$ if and only if vector set $a_1,a_2,\dots,a_n,\beta$ is linearly dependent.

### Maximal Linearly Independent Set, Rank

Linear dependence can be understood as "redundancy", indicating that some vectors in the set can be expressed by others and can be deleted. After deleting them, what remains is a maximal linearly independent set.

For a vector space $(V,+,\cdot,\Bbb{P})$:

1.  For vector set $b_1,b_2,\dots,b_m$, let $\{a_1,a_2,\dots,a_n\}\subseteq\{b_1,b_2,\dots,b_m\}$, if:

    -   Vector set $a_1,a_2,\dots,a_n$ is linearly independent.
    -   $\forall\beta\in\{b_1,b_2,\dots,b_m\}\setminus\{a_1,a_2,\dots,a_n\}$, vector set $a_1,a_2,\dots,a_n,\beta$ is linearly dependent.

    Then vector set $a_1,a_2,\dots,a_n$ is called a **maximal linearly independent set** of vector set $b_1,b_2,\dots,b_m$. Similarly, maximal linearly independent sets of vector space $V$ can be defined.

    By convention, the maximal linearly independent set of vector set $\theta,\theta,\dots,\theta$ is the empty set. Thus, the vector set corresponding to an all-zero matrix has no maximal linearly independent set.

    The method of deleting vectors from a set is not unique, so maximal linearly independent sets are not unique. Conventionally, delete from left to right.

    Conveniently, by deleting in order, the vectors left over are exactly the columns corresponding to the positions of $1$'s in the row-reduced echelon matrix from the "row perspective" view of Gaussian elimination.

    The size of a maximal linearly independent set of vector set $b_1,b_2,\dots,b_m$ is called the **rank** of the vector set, denoted $\operatorname{rank}\{b_1,b_2,\dots,b_m\}$, with $\operatorname{rank}\{\theta,\theta,\dots,\theta\}=0$.

    Thus, the definition of rank for vector sets is completely consistent with the definition of rank for matrices.

2.  If vector set $a_1,a_2,\dots,a_n$ can linearly express all vectors in vector set $b_1,b_2,\dots,b_m$, then vector set $b_1,b_2,\dots,b_m$ is said to be linearly expressed by vector set $a_1,a_2,\dots,a_n$.

3.  If vector set $a_1,a_2,\dots,a_n$ can be linearly expressed by vector set $b_1,b_2,\dots,b_m$, and vector set $b_1,b_2,\dots,b_m$ can be linearly expressed by vector set $a_1,a_2,\dots,a_n$, then the two vector sets are called **equivalent**, denoted $\{a_1,a_2,\dots,a_n\}\cong\{b_1,b_2,\dots,b_m\}$.

    **Equivalence** of vector sets means the same spanned space. Vector sets with the same spanned space are equivalent; vector sets with different spanned spaces are not equivalent.

    Vector set equivalence is stronger than matrix equivalence. It not only requires the same rank but also the exact same space. Therefore, when two matrices are placed **side by side**, the rank must not change.

    Matrix equivalence only requires the same rank. Therefore, matrix equivalence indicates that the first matrix (or space) can be transformed to the second matrix (or space) by an invertible transformation.

#### Properties

For a vector space $(V,+,\cdot,\Bbb{P})$:

1.  If vector set $a_1,a_2,\dots,a_n$ can be linearly expressed by vector set $b_1,b_2,\dots,b_m$.
    -   If $n>m$, then vector set $a_1,a_2,\dots,a_n$ is linearly dependent.
    -   If vector set $a_1,a_2,\dots,a_n$ is linearly independent, then $n\leq m$.

2.  Equivalent linearly independent vector sets have the same size.

    Any maximal linearly independent set of a vector set has the same size.

3.  A vector set is linearly independent if and only if its rank equals its size.

4.  If vector set $a_1,a_2,\dots,a_n$ can be linearly expressed by vector set $b_1,b_2,\dots,b_m$, then $\operatorname{rank}\{a_1,a_2,\dots,a_n\}\leq\operatorname{rank}\{b_1,b_2,\dots,b_m\}$.

5.  Equivalent vector sets have the same rank.

### Span

For a vector space $(V,+,\cdot,\Bbb{P})$, $\left\{v=\sum_{i=1}^nk_ia_i:a_i\in V,k_i\in\Bbb{P},i=1,2,\dots,n\right\}$ also forms a vector space, called the **span** (or **linear span**) of vector set $a_1,a_2,\dots,a_n$, denoted $\operatorname{span}\{a_1,a_2,\dots,a_n\}$.

Here, the $n$ vectors $a$ are not necessarily linearly independent.

### Linear Subspace

For a vector space $(V,+,\cdot,\Bbb{P})$, if the algebraic system $(V_1,+,\cdot,\Bbb{P})$ satisfies:

1.  $\varnothing\ne V_1$
2.  $V_1\subseteq V$
3.  $V_1$ forms a vector space over $\mathbb{P}$ under $+,\cdot$

Then $V_1$ is called a **linear subspace** (or subspace) of $V$, denoted $V_1\leq V$.

Any space $V$ has two **trivial subspaces**: itself $V$ and the zero subspace. The zero subspace contains only the zero vector and has no linearly independent vectors.

If condition 2 uses $\subset$ instead of $\subseteq$, then $V_1$ is called a **proper subspace** of $V$, denoted $V_1<V$.

It is easy to prove: A non-empty subset $V_1$ of a vector space $V$ is a subspace if and only if linear operations are closed on $V_1$, i.e.:

1.  $\forall u,v\in V_1$, $u+v\in V_1$
2.  $\forall v\in V_1$, $\forall k\in \Bbb{P}$, $kv\in V_1$

### Intersection, Sum, Direct Sum, Direct Product

For vector spaces $(V_1,+,\cdot,\Bbb{P})$ and $(V_2,+,\cdot,\Bbb{P})$:

1.  It is easy to verify: Addition and scalar multiplication are closed on $V_1\cap V_2$, so $V_1\cap V_2$ is called the **intersection** of $V_1$ and $V_2$.

    Similarly, the intersection of multiple vector spaces $\bigcap_{i=1}^m V_i$ can be defined.

2.  If vector space $V$ satisfies $V=\{u+v|u\in V_1,v\in V_2\}$, then $V$ is called the **sum** of $V_1$ and $V_2$, denoted $V=V_1+V_2$.

    It can be verified: $V_1+V_2$ is the smallest subspace containing $V_1\cup V_2$.

    Similarly, the sum of multiple vector spaces $\sum_{i=1}^m V_i$ can be defined.

3.  Let $V=V_1+V_2$. If for any element $v$ in $V$, there exists a unique pair of vectors $v_1,v_2$ satisfying $v=v_1+v_2$, then $V$ is called the **direct sum** of $V_1$ and $V_2$, denoted $V_1\oplus V_2$.

    Similarly, the direct sum of multiple vector spaces $\bigoplus_{i=1}^m V_i$ can be defined.

4.  The **direct product** $V_1\times V_2$ of $V_1$ and $V_2$ is defined as the Cartesian product with the following addition and scalar multiplication, forming a vector space over $\Bbb{P}$:

    1.  $+:(V_1\times V_2)\times(V_1\times V_2)\mapsto V_1\times V_2; ((u_1,v_1),(u_2,v_2))\to (u_1+u_2,v_1+v_2)$
    2.  $\cdot:\Bbb{P}\times(V_1\times V_2)\mapsto V_1\times V_2; (k,(u,v))\to (ku,kv)$

    Similarly, the direct product of multiple vector spaces $\prod_{i=1}^m V_i$ can be defined.

#### Examples

For vector space $V=\Bbb{R}^3$, let:

-   $V_1:=\{(x,0,0)|x\in\Bbb{R}\}$
-   $V_2:=\{(x,y,0)|x,y\in\Bbb{R}\}$
-   $V_3:=\{(0,y,z)|y,z\in\Bbb{R}\}$
-   $V_4:=\{(x,0,z)|x,z\in\Bbb{R}\}$

Then:

1.  $V_1<V_2<V$, $V_3<V$
2.  $V_2=V_1+V_2$
3.  $V=V_1\oplus V_3=V_2+V_3$
4.  $V_2\oplus V_3=V_4$, $V_2\oplus V_4=V_3$, $V_3\oplus V_4=V_2$
5.  $V_2+V_3\leq V$

#### Properties

1.  Let $V_1,V_2,V_3$ be vector spaces over $\Bbb{P}$. Like set intersection, the intersection of vector spaces follows:
    1.  Commutative law: $V_1\cap V_2=V_2\cap V_1$
    2.  Associative law: $V_1\cap(V_2\cap V_3)=(V_1\cap V_2)\cap V_3$
2.  Let $V_1,V_2,V_3$ be vector spaces over $\Bbb{P}$. Like set union, the sum of vector spaces follows:
    1.  Commutative law: $V_1+V_2=V_2+V_1$
    2.  Associative law: $V_1+(V_2+V_3)=(V_1+V_2)+V_3$
3.  Let $V_1,V_2,V_3$ be vector spaces over $\Bbb{P}$. The intersection and sum of vector spaces have the following relationship:
    1.  $V_1\cap (V_2+V_3)\supseteq (V_1\cap V_2)+(V_1\cap V_3)$
    2.  $V_1+(V_2\cap V_3)\subseteq (V_1+V_2)\cap (V_1+V_3)$
4.  $\operatorname{span}\{a_1,a_2,\dots,a_n\}+\operatorname{span}\{b_1,b_2,\dots,b_m\}=\operatorname{span}\{a_1,a_2,\dots,a_n,b_1,b_2,\dots,b_m\}$
5.  Let $V_1,V_2$ be vector spaces over $\Bbb{P}$. The following are equivalent:

    1.  $V_1+V_2=V_1\oplus V_2$

    2.  There exists $\beta\in V_1+V_2$ such that the decomposition into vectors from $V_1$ and $V_2$ is unique (any $\to$ exists)

    3.  The decomposition of $\theta$ into vectors from $V_1$ and $V_2$ is unique

    4.  $V_1\cap V_2=\{\theta\}$

    ???+ note "Proof"
        $1\implies 2$: Direct from definition.
        
        $2 \implies 3$:
        
        Let $\beta=\beta_1+\beta_2$, where $\beta_1\in V_1, \beta_2\in V_2$. If $\theta=\alpha_1+\alpha_2$, $\theta\ne\alpha_1\in V_1,\alpha_2\in V_2$, then $\beta=\beta+\theta=(\beta_1+\alpha_1)+(\beta_2+\alpha_2)$.
        
        But $\beta_1\ne\beta_1+\alpha_1$, contradiction.
        
        $3 \implies 4$:
        
        Take a non-zero vector $\alpha$ in $V_1$ and $V_2$. Then $\theta=\alpha+(-\alpha)=(-\alpha)+\alpha$, contradiction.
        
        $4 \implies 1$:
        
        If $V_1+V_2$ is not a direct sum, then there exists $\beta\in V_1+V_2$ such that $\beta=\beta_1+\beta_2=\gamma_1+\gamma_2$, where $\beta_1,\gamma_1\in V_1,\beta_2,\gamma_2\in V_2$ and $\beta_1,\beta_2,\gamma_1,\gamma_2$ are all distinct.
        
        Then $\theta\ne\beta_1-\gamma_1=\gamma_2-\beta_2\in V_1\cap V_2$, contradiction.

### Isomorphism

Let $V$ and $V'$ be vector spaces over field $\Bbb{P}$. If there exists a bijection $\sigma:V\mapsto V'$ that preserves addition and scalar multiplication, i.e., $\forall u,v\in V$, $\forall k\in\Bbb{P}$ satisfies:

1.  $\sigma(u+v)=\sigma(u)+\sigma(v)$
2.  $\sigma(ku)=k\sigma(u)$

Then $\sigma$ is called an **isomorphism** from $V$ to $V'$, and $V$ and $V'$ are said to be **isomorphic**, denoted $V\cong V'$.

???+ note "Note"
    If $\sigma$ is injective, a **monomorphism** can be defined; if $\sigma$ is surjective, an **epimorphism** can be defined.

#### Properties

1.  Two vector spaces over $\Bbb{P}$ are isomorphic if and only if they have the same dimension. (See [Linear basis](./basis.md) for the definition of dimension.)
2.  (Corollary of 1) An $n$-dimensional vector space over $\Bbb{P}$ is isomorphic to the vector space $\Bbb{P}^n$.

    ???+ note "Note"
        This property shows that we can essentially equate coordinates with vectors.

## Relationship between Euclidean Space and Vector Space

Taking the familiar three-dimensional Euclidean space as an example, the corresponding concepts in vector space are:

| Three-dimensional Euclidean space | Vector space              |
| -------- | ----------------- |
| Vector       | Vector                |
| Perpendicular       | Orthogonal (i.e., inner product is $0$)      |
| Three vectors collinear/coplanar | $k$ vectors linearly dependent       |
| Three vectors non-coplanar   | $k$ vectors linearly independent       |
| Basis vectors      | [Linear basis](./basis.md) |
| Dimension of space    | Dimension of space             |

## Applications

From this section, we mainly discuss the "column perspective" on linear systems.

Matrix $A$ itself is also composed of column vectors. By treating $A$ as a vector set, and $x$ as unknown coefficients, we ask whether this set of column vectors in $A$ can be combined with unknowns to form column vector $b$. Here, column vector $x$ is completely unknown.

The equation $Ax=b$ can be reorganized as:

$$
\alpha_1 x_1 +\alpha_2 x_2 +\cdots+\alpha_n x_n=b 
$$

Here, matrix $A$ on the left of the matrix multiplication can be seen as a vector set, i.e., a group of column vectors. This set of column vectors, as a basis, spans a space. We explore whether column vector $b$ lies in this space.

### Solving Linear Systems from the Column Perspective

Rank is the number of vectors in a maximal linearly independent set, representing "constraints". The remaining vectors give the degrees of freedom, allowing redundant vectors in other directions.

If we denote $n$ as the number of columns of matrix $A$ (the number of column vectors), and $r(A)$ as the rank of matrix $A$, then the degrees of freedom $S$ is:

$$
S=n-r(A)
$$

The set of all solutions to the system also forms a vector set. The degrees of freedom $S$ is the rank of the solution vector set of $Ax=0$, i.e., the dimension of the kernel space below.

### Equivalent Systems

The common solutions of two systems are defined as the intersection of their two solution sets.

Two systems are **equivalent** if their solution sets are equal. Systems with equal solution sets are equivalent; systems with different solution sets are not equivalent.

System equivalence is stronger than matrix equivalence. Not only must the ranks be equal, but when the two matrices are placed **vertically**, the rank must still not change.

This contrasts with vector set equivalence, where vector set equivalence requires matrices placed **horizontally** with unchanged rank. Therefore, the following relationship holds:

Matrix equivalence does not necessarily imply corresponding vector set equivalence or system equivalence, but if vector set equivalence or system equivalence holds, then corresponding matrix equivalence (same rank) must hold.

If the vector set corresponding to a matrix is equivalent, then transposing the matrix makes the corresponding systems equivalent, and vice versa.

### Kernel Space and Image Space of a Matrix

The kernel space and image space here are described from the perspective of vector spaces.

For a matrix $A$, let $W$ be the set of all solutions $x$ to the equation $Ax=0$. Then $W$ is a vector space. The scalar field of $W$ is the same as the field containing elements of $A$.

$W$ is called the **kernel space** (or null space) of matrix $A$, denoted $N(A)$.

The kernel space $N(A)$ of matrix $A$ is the **solution space** of equation $Ax=0$. According to the definition of basis below, the **fundamental solution set** of this equation is a basis of the kernel space.

If matrix $A$ is invertible, then its kernel space $N(A)$ contains only the zero vector.

For matrix $A$, its $n$ columns are vectors $\alpha$. The space spanned by the $n$ column vectors $\alpha$ is called the **image space** (or **column space**) of $A$, denoted:

$$
R(A)=\operatorname{span}\{\alpha_1,\alpha_2,\cdots,\alpha_n\}
$$

According to the definition of dimension below, the dimension of the image space equals the rank of matrix $A$.

From the definition, for every element $y$ in image space $R(A)$, there exists a representation:

$$
y=k_1\alpha_1+k_2\alpha_2+\cdots+k_n\alpha_n=(\alpha_1,\alpha_2,\cdots,\alpha_n)\begin{pmatrix}k_1\\ k_2\\\vdots\\ k_n\end{pmatrix}=A\begin{pmatrix}k_1\\ k_2\\\vdots\\ k_n\end{pmatrix}
$$

Therefore, image space $R(A)$ is the **range** of $Ax$ for any vector $x$.

Similarly, the **row space** of $A$ can be defined as the range of $A^T$, denoted $R(A^T)$.

Since the row rank equals the column rank, the dimension of the row space also equals the rank of the matrix. Thus, transposition changes the image space but not its dimension.

Here we can establish correspondences with the preceding discussion:

Vector set equivalence is equivalent to the image spaces $R(A)$ of the corresponding matrices being the same.

System equivalence is equivalent to the row spaces $R(A^T)$ of the corresponding matrices being the same.

## References

1.  Qiu Weisheng, Advanced Algebra (Vol. 2). Tsinghua University Press.
2.  [Vector space](https://en.wikipedia.org/w/index.php?title=Vector_space&oldid=1108546097). *Wikipedia, The Free Encyclopedia*.