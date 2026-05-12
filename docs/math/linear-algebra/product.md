This article introduces simple operations between vectors.

Before this article, a note on translation. Due to historical reasons, mathematics and physics have various translations for "inner product" and "outer product".

In physics, they are generally translated as "scalar product" and "vector product", indicating that the results are scalar and vector quantities. High school mathematics textbooks also use "dot product" and "cross product" with this approach.

In mathematics, they are usually translated as "inner product" and "outer product", which are direct translations of the two terms. "Dot product" and "cross product" are colloquial names derived from the operation symbols, and are also common.

In the "dot product" operation, the dot symbol is often omitted. In linear algebra, it's often treated as matrix multiplication without the dot symbol.

## Inner Product

The concept of inner product **applies to vectors of any dimension**.

### Definition

There are different but equivalent ways to define inner product. Some are introduced below.

#### Geometric Definition

In $n$-dimensional Euclidean space $\mathbf{R}^n$, given two vectors $\boldsymbol{a}, \boldsymbol{b}$, with angle $\theta$ between them:

$$
\boldsymbol{a} \cdot \boldsymbol{b} = |\boldsymbol{a}| |\boldsymbol{b}| \cos \theta
$$

This is the **inner product** (also called **dot product** or **scalar product**) of the two vectors. Here $|\boldsymbol{b}|\cos \theta$ is called the projection of $\boldsymbol{b}$ onto the direction of $\boldsymbol{a}$. The geometric meaning of inner product is: $\boldsymbol{a} \cdot \boldsymbol{b}$ equals the product of the magnitude of $\boldsymbol{a}$ and the projection of $\boldsymbol{b}$ onto $\boldsymbol{a}$.

#### Algebraic Definition

In $n$-dimensional Euclidean space $\mathbf{R}^n$, given two vectors $\boldsymbol{a} = (a_1, a_2, \dots, a_n), \boldsymbol{b} = (b_1, b_2, \dots, b_n)$:

$$
\boldsymbol{a} \cdot \boldsymbol{b} = \sum_{i = 1}^{n} a_i b_i
$$

This is the **inner product** (also called **dot product** or **scalar product**) of the two vectors. The geometric and algebraic definitions are equivalent in Euclidean space, and the latter is more convenient to use.

When it does not cause confusion, the dot in inner product can be omitted. If a vector has a superscript $2$ in the upper right corner, it represents the abbreviation of the inner product of the vector with itself, i.e., **the square of the vector's magnitude**, omitting the magnitude symbol. This superscript $2$ cannot be interpreted as the square of the vector, because the result of a vector inner product is a scalar, and there is no inner product of any number of vectors other than $2$. Similarly, the square of the square of the vector's magnitude cannot be abbreviated as superscript $4$, but rather the result of superscript $2$ must be treated as a whole, and so on.

### Properties

One can see that the result of an inner product is a scalar. Its special property is that it is a bilinear operation that is linear in each argument separately. Specifically, inner product satisfies:

$$
\begin{aligned}
(\boldsymbol{a} + \boldsymbol{b}) \cdot \boldsymbol{c} &= \boldsymbol{a} \cdot \boldsymbol{c} + \boldsymbol{b} \cdot \boldsymbol{c} \\
\boldsymbol{a} \cdot (\boldsymbol{b} + \boldsymbol{c}) &= \boldsymbol{a} \cdot \boldsymbol{b} + \boldsymbol{a} \cdot \boldsymbol{c} \\
(\lambda \boldsymbol{a}) \cdot \boldsymbol{b} &= \lambda (\boldsymbol{a} \cdot \boldsymbol{b}) \\
\boldsymbol{a} \cdot (\lambda \boldsymbol{b}) &= \lambda (\boldsymbol{a} \cdot \boldsymbol{b})
\end{aligned}
$$

Inner product also satisfies the commutative law:

$$
\boldsymbol{a} \cdot \boldsymbol{b} = \boldsymbol{b} \cdot \boldsymbol{a}
$$

### Applications

Some common applications of inner product are introduced below.

1.  Determining perpendicular vectors:

    $$
    \boldsymbol{a} \perp \boldsymbol{b} \iff \boldsymbol{a} \cdot \boldsymbol{b} = 0
    $$

    That is, the inner product of two perpendicular vectors is $0$; the inner product of any vector with the zero vector is $0$. If we use zero inner product as the definition of perpendicularity, we can conclude that the zero vector is perpendicular to any vector.

2.  Determining collinear vectors:

    $$
    \exists\lambda \in \mathbf{R} (\boldsymbol{a} = \lambda \boldsymbol{b}) \iff |\boldsymbol{a} \cdot \boldsymbol{b}| = |\boldsymbol{a}| |\boldsymbol{b}|
    $$

3.  Computing the magnitude of a vector:

    $$
    |\boldsymbol a| = \sqrt{\boldsymbol{a} \cdot \boldsymbol{a}}
    $$

4.  Computing the angle between two vectors:

    $$
    \theta = \arccos \frac{\boldsymbol{a} \cdot \boldsymbol{b}}{|\boldsymbol a| |\boldsymbol b|}
    $$

## 2×2 and 3×3 Determinants

The $2 \times 2$ and $3 \times 3$ determinants can be defined as special simple cases of determinants. In the final part of calculus, Green's formula uses $2 \times 2$ determinants, Gauss's formula uses dot products, and Stokes' formula uses $3 \times 3$ determinants.

The $2 \times 2$ determinant can be viewed as a function of four numbers:

$$
\begin{vmatrix}
    a & b \\
    c & d
\end{vmatrix}=ad-bc
$$

The $3 \times 3$ determinant can be viewed as a function of nine numbers:

$$
\begin{vmatrix}
    a & b & c \\
    d & e & f \\
    g & h & i
\end{vmatrix}=aei+dhc+gbf-ahf-dbi-gec
$$

A special memory method uses the "diagonal rule", which only applies to $2 \times 2$ and $3 \times 3$ determinants.

**Special note:** A $4 \times 4$ determinant expands to 24 terms, and the term from the secondary diagonal has a positive sign. If one attempts to apply the "diagonal rule" for $3 \times 3$ determinants to higher-order ones, not only are there insufficient terms, but the sign of the secondary diagonal term is also incorrect. Therefore, the "diagonal rule" for $3 \times 3$ determinants does not apply to higher-order determinants, and higher-order determinants are not suitable for direct expansion.

## Cross Product

The cross product is an operation **specific to three-dimensional vectors**.

In physics, three-dimensional vectors are considered by default as vectors associated with spatial position, and are always in bold. However, in relativity, four-dimensional vectors are not in bold but use special notations and subscripts.

In linear algebra, all vectors are in bold, and since it's cumbersome and most operations in linear algebra involve vectors and matrices, which rarely cause ambiguity, the vector notation can be omitted when writing by hand.

### Definition

There are different but equivalent ways to define cross product. Some are introduced below.

#### Geometric Definition

In three-dimensional Euclidean space $\mathbf{R}^3$, define the cross product of vectors $\boldsymbol{a}, \boldsymbol{b}$ as a vector, denoted $\boldsymbol{a} \times \boldsymbol{b}$, with magnitude and direction defined as follows:

1.  $|\boldsymbol{a} \times \boldsymbol{b}| = |\boldsymbol{a}| |\boldsymbol{b}| \sin \langle \boldsymbol{a}, \boldsymbol{b} \rangle$;
2.  $\boldsymbol{a} \times \boldsymbol{b}$ is perpendicular to both $\boldsymbol{a}$ and $\boldsymbol{b}$, and the direction of $\boldsymbol{a}, \boldsymbol{b}, \boldsymbol{a} \times \boldsymbol{b}$ follows the right-hand rule.

Notice that the magnitude of the cross product, recalling the triangle area formula $S=\frac{1}{2}ab\sin C$, reveals the geometric meaning: **$|\boldsymbol{a} \times \boldsymbol{b}|$ is the area of the parallelogram with $\boldsymbol{a}, \boldsymbol{b}$ as adjacent sides**.

#### Algebraic Definition

In three-dimensional Euclidean space $\mathbf{R}^3$, define vectors $\boldsymbol{a} = (x_1, y_1, z_1), \boldsymbol{b} = (x_2, y_2, z_2)$. The cross product is a vector $\boldsymbol{c}$, denoted $\boldsymbol{c} = \boldsymbol{a} \times \boldsymbol{b}$, which can be expressed using a $3 \times 3$ determinant:

$$
\begin{vmatrix}
    \boldsymbol{i} & \boldsymbol{j} & \boldsymbol{k} \\
    x_1 & y_1 & z_1  \\
    x_2 & y_2 & z_2
\end{vmatrix}
$$

where $\boldsymbol{i}, \boldsymbol{j}, \boldsymbol{k}$ are unit vectors pointing along the $x, y, z$ axes, written at the corresponding coordinate positions. Expanding gives:

$$
\begin{aligned}
\boldsymbol{c} &= \boldsymbol{a} \times \boldsymbol{b} \\
&= (y_1z_2 - y_2z_1)\boldsymbol{i} + (z_1x_2 - z_2x_1)\boldsymbol{j} + (x_1y_2 - x_2y_1)\boldsymbol{k} \\
&= (y_1z_2 - y_2z_1, z_1x_2 - z_2x_1, x_1y_2 - x_2y_1)
\end{aligned}
$$

### Properties

1.  The cross product is bilinear, linear in each argument separately. Specifically, the cross product satisfies:

    $$
    \begin{aligned}
    (\boldsymbol{a} + \boldsymbol{b}) \times \boldsymbol{c} &= \boldsymbol{a} \times \boldsymbol{c} + \boldsymbol{b} \times \boldsymbol{c} \\
    \boldsymbol{a} \times (\boldsymbol{b} + \boldsymbol{c}) &= \boldsymbol{a} \times \boldsymbol{b} + \boldsymbol{a} \times \boldsymbol{c} \\
    (\lambda \boldsymbol{a}) \times \boldsymbol{b} &= \lambda (\boldsymbol{a} \times \boldsymbol{b}) \\
    \boldsymbol{a} \times (\lambda \boldsymbol{b}) &= \lambda (\boldsymbol{a} \times \boldsymbol{b})
    \end{aligned}
    $$

    The first two properties are also called the distributive law, i.e., cross product distributes over vector addition.

2.  The cross product satisfies the anticommutative law:

    $$
    \boldsymbol a \times \boldsymbol b=-\boldsymbol b \times \boldsymbol a
    $$

3.  From the geometric definitions of inner and cross product above:

    $$
    \begin{aligned}
    |\boldsymbol a \times \boldsymbol b| &= |\boldsymbol a| |\boldsymbol b| \sin \langle \boldsymbol a, \boldsymbol b \rangle \\
    \boldsymbol a \cdot \boldsymbol b &= |\boldsymbol a| |\boldsymbol b| \cos \theta \\
    &= |\boldsymbol a| |\boldsymbol b| \cos \langle \boldsymbol a, \boldsymbol b\rangle
    \end{aligned}
    $$

    We can write the identity:

    $$
    (\boldsymbol a\times \boldsymbol b) \cdot (\boldsymbol a\times \boldsymbol b) = |\boldsymbol a|^2 |\boldsymbol b|^2-{(\boldsymbol a \cdot \boldsymbol b)}^2
    $$

4.  The cross product satisfies the Jacobi identity:

    $$
    \boldsymbol a \times (\boldsymbol b \times \boldsymbol c) + \boldsymbol b \times (\boldsymbol c \times \boldsymbol a) + \boldsymbol c \times (\boldsymbol a \times \boldsymbol b) = \boldsymbol 0
    $$

### Applications

Some common applications of cross product are introduced below.

1.  Determining whether two vectors are collinear:

    $$
    \exists\lambda \in \mathbf{R} (\boldsymbol{a} = \lambda \boldsymbol{b}) \iff \boldsymbol{a} \times \boldsymbol{b} = \boldsymbol{0}
    $$

    That is, the cross product of two collinear three-dimensional vectors is $\boldsymbol 0$; the cross product of a three-dimensional vector with itself is $\boldsymbol 0$; the cross product of a three-dimensional vector with the zero vector is $\boldsymbol 0$. If we use zero cross product as the definition of collinearity, we can conclude that the zero vector is collinear with any vector.

2.  Computing the area of the parallelogram spanned by two vectors:

    $$
    S \langle \boldsymbol a, \boldsymbol b \rangle = |\boldsymbol a \times \boldsymbol b|
    $$

#### Two-Dimensional Vector Case

For two-dimensional vectors, cross product cannot be directly computed, but the area of the parallelogram spanned by two vectors can still be computed:

Let $\boldsymbol{a} = (m, n), \boldsymbol{b} = (p, q)$. Extend the plane Cartesian coordinate system to a spatial Cartesian coordinate system, with the original plane in the $xOy$ plane of the new system, and original coordinates $(m, n)$ and $(p, q)$ become $(m, n, 0)$ and $(p, q, 0)$.

Then the cross product of the two vectors is $(0, 0, mq - np)$, so the area of the parallelogram is $|mq - np|$, which can be viewed as the absolute value of the $2 \times 2$ determinant.

At this point, according to the right-hand rule and the sign of the $z$ coordinate, we can determine the direction of $\boldsymbol b$ relative to $\boldsymbol a$. If it's counterclockwise, the $z$ coordinate is positive; otherwise, it's negative. This is briefly "negative when clockwise, positive when counterclockwise".

## Scalar Triple Product

Like cross product, the scalar triple product of vectors is an operation **specific to three-dimensional vectors**.

### Definition

Let $\boldsymbol a, \boldsymbol b, \boldsymbol c$ be three vectors in three-dimensional space. Then $(\boldsymbol a \times \boldsymbol b) \cdot \boldsymbol c$ is called the scalar triple product of the three vectors $\boldsymbol a, \boldsymbol b, \boldsymbol c$, denoted $[\boldsymbol a \boldsymbol b \boldsymbol c]$ or $(\boldsymbol a, \boldsymbol b, \boldsymbol c)$ or $(\boldsymbol a \boldsymbol b \boldsymbol c)$ or $\det(\boldsymbol a, \boldsymbol b, \boldsymbol c)$. The absolute value $|(\boldsymbol a \times \boldsymbol b) \cdot \boldsymbol c|$ represents the volume of the parallelepiped with edges $\boldsymbol a, \boldsymbol b, \boldsymbol c$.

The scalar triple product of vectors can be expressed using a $3 \times 3$ determinant:

$$
\begin{aligned}
(\boldsymbol a \times \boldsymbol b) \cdot \boldsymbol c &= \det(\boldsymbol a, \boldsymbol b, \boldsymbol c) \\
&= \begin{vmatrix}
    a_x & b_x & c_x \\
    a_y & b_y & c_y \\
    a_z & b_z & c_z
\end{vmatrix} \\
&= a_x b_y c_z + a_y b_z c_x + a_z b_x c_y - a_z b_y c_x -a _y b_x c_z - a_x b_z c_y
\end{aligned}
$$

### Properties

1.  The scalar triple product is linear in each of the three vectors:

    $$
    \begin{aligned}
    \det(\lambda\boldsymbol{u} + \mu\boldsymbol{v}, \boldsymbol{b}, \boldsymbol{c}) &= \lambda\det(\boldsymbol{u}, \boldsymbol{b}, \boldsymbol{c}) + \mu\det(\boldsymbol{v}, \boldsymbol{b}, \boldsymbol{c}) \\
    \det(\boldsymbol{a}, \lambda\boldsymbol{u} + \mu\boldsymbol{v}, \boldsymbol{c}) &= \lambda\det(\boldsymbol{a}, \boldsymbol{u}, \boldsymbol{c}) + \mu\det(\boldsymbol{a}, \boldsymbol{v}, \boldsymbol{c}) \\
    \det(\boldsymbol{a}, \boldsymbol{b}, \lambda\boldsymbol{u} + \mu\boldsymbol{v}) &= \lambda\det(\boldsymbol{a}, \boldsymbol{b}, \boldsymbol{u}) + \mu\det(\boldsymbol{a}, \boldsymbol{b}, \boldsymbol{v})
    \end{aligned}
    $$

2.  The scalar triple product is alternating: swapping two vectors changes the sign of the triple product:

    $$
    \det(\boldsymbol a, \boldsymbol b, \boldsymbol c) = \det(\boldsymbol b, \boldsymbol c, \boldsymbol a) = \det(\boldsymbol c, \boldsymbol a, \boldsymbol b) = -\det(\boldsymbol b, \boldsymbol a, \boldsymbol c) = -\det(\boldsymbol a, \boldsymbol c, \boldsymbol b)= -\det(\boldsymbol c, \boldsymbol b, \boldsymbol a)
    $$

    From this, we can also derive the following relationship between inner and cross product:

    $$
    (\boldsymbol a \times \boldsymbol b) \cdot \boldsymbol c = \boldsymbol a \cdot (\boldsymbol b \times \boldsymbol c)
    $$

### Applications

The scalar triple product has the following common applications.

1.  Computing the volume of tetrahedron $ABCD$:

    $$
    V=\frac{1}{6}\left|\det(\overrightarrow{AB}, \overrightarrow{AC}, \overrightarrow{AD})\right|
    $$

2.  Determining whether $\boldsymbol a, \boldsymbol b, \boldsymbol c$ are coplanar;

    Three three-dimensional vectors $\boldsymbol a, \boldsymbol b, \boldsymbol c$ are coplanar if and only if $\det(\boldsymbol a, \boldsymbol b, \boldsymbol c)=0$.

3.  Determining the handedness of the coordinate system formed by $\boldsymbol a, \boldsymbol b, \boldsymbol c$;

    The sign of $\det(\boldsymbol a, \boldsymbol b, \boldsymbol c)$ depends on whether the angle between $\boldsymbol a \times \boldsymbol b$ and $\boldsymbol c$ is acute or obtuse, i.e., whether $\boldsymbol c$ is on the same side or opposite side of the plane spanned by $\boldsymbol a$ and $\boldsymbol b$. This corresponds to whether $\boldsymbol a, \boldsymbol b, \boldsymbol c$ in order form a right-handed or left-handed system. Specifically:

    -   $\det(\boldsymbol a, \boldsymbol b, \boldsymbol c) < 0$ is equivalent to $\boldsymbol a, \boldsymbol b, \boldsymbol c$ in order forming a left-handed system;
    -   $\det(\boldsymbol a, \boldsymbol b, \boldsymbol c) > 0$ is equivalent to $\boldsymbol a, \boldsymbol b, \boldsymbol c$ in order forming a right-handed system.

## Vector Triple Product

The scalar triple product of three-dimensional vectors is a combination of inner and cross product, and has cyclic symmetry. The cross product of two three-dimensional vectors is still a three-dimensional vector. So, is there a related conclusion for the cross product of a cross product?

First, prove a lemma.

$$
(\boldsymbol a \times \boldsymbol b)\times \boldsymbol a = (\boldsymbol a \cdot \boldsymbol a) \boldsymbol b - (\boldsymbol a \cdot \boldsymbol b) \boldsymbol a
$$

Proof: By the right-hand rule, $\boldsymbol a \times \boldsymbol b$ is perpendicular to both $\boldsymbol a$ and $\boldsymbol b$. The left side of the equation to be proved is perpendicular to $\boldsymbol a \times \boldsymbol b$, so the left side is coplanar with $\boldsymbol a$ and $\boldsymbol b$.

Therefore, we can assume:

$$
(\boldsymbol a \times \boldsymbol b)\times \boldsymbol a = \lambda \boldsymbol a + \mu \boldsymbol b
$$

Taking the inner product of both sides with $\boldsymbol a$ and $\boldsymbol b$ respectively, using the scalar triple product results:

$$
\begin{aligned}
\lambda (\boldsymbol a \cdot \boldsymbol a)+\mu (\boldsymbol a \cdot \boldsymbol b) &= 0 \\
\lambda (\boldsymbol a \cdot \boldsymbol b) + \mu (\boldsymbol b \cdot \boldsymbol b) &= \det(\boldsymbol b, \boldsymbol a \times \boldsymbol b, \boldsymbol a) \\
&= (\boldsymbol a \times \boldsymbol b) \cdot (\boldsymbol a \times \boldsymbol b)
\end{aligned}
$$

From the identity derived earlier:

$$
(\boldsymbol a \times \boldsymbol b) \cdot (\boldsymbol a \times \boldsymbol b) = |\boldsymbol a|^2|\boldsymbol b|^2-(\boldsymbol a \cdot \boldsymbol b)^2
$$

We can solve for:

$$
\begin{aligned}
\lambda &= -\boldsymbol a \cdot \boldsymbol b \\
\mu &= \boldsymbol a \cdot \boldsymbol a
\end{aligned}
$$

Q.E.D.

In the proof above, $\boldsymbol a \times \boldsymbol b$ is coplanar with any vector crossed with it. Next, we prove the **vector triple product** formula:

$$
(\boldsymbol a\times \boldsymbol b)\times \boldsymbol c=(\boldsymbol a \cdot \boldsymbol c)\boldsymbol b - (\boldsymbol b \cdot \boldsymbol c)\boldsymbol a
$$

The coplanarity property above helps in memorizing the vector triple product formula. The lemma above is a special case of this formula.

Proof: Here we only need to consider the case where all three vectors are non-zero and not collinear; other special cases are obvious.

Vectors $\boldsymbol a$, $\boldsymbol b$, and $\boldsymbol a \times \boldsymbol b$ are not coplanar, so we can assume:

$$
\boldsymbol c = \alpha \boldsymbol a + \beta \boldsymbol b + \gamma(\boldsymbol a \times \boldsymbol b)
$$

Then:

$$
\begin{aligned}
(\boldsymbol a \times \boldsymbol b) \times \boldsymbol c &= (\boldsymbol a \times \boldsymbol b) \times (\alpha \boldsymbol a + \beta \boldsymbol b + \gamma(\boldsymbol a \times \boldsymbol b)) \\
&= \alpha(\boldsymbol a \times \boldsymbol b) \times \boldsymbol a + \beta(\boldsymbol a \times \boldsymbol b) \times \boldsymbol b
\end{aligned}
$$

From the lemma above:

$$
\begin{aligned}
(\boldsymbol a \times \boldsymbol b) \times \boldsymbol a &=(\boldsymbol a \cdot \boldsymbol a) \boldsymbol b - (\boldsymbol a \cdot \boldsymbol b) \boldsymbol a \\
(\boldsymbol a \times \boldsymbol b) \times \boldsymbol b
&= -(\boldsymbol b \times \boldsymbol a) \times \boldsymbol b \\
&= -(\boldsymbol b \cdot \boldsymbol b)\boldsymbol a+(\boldsymbol a \cdot \boldsymbol b) \boldsymbol b
\end{aligned}
$$

Therefore:

$$
\begin{aligned}
(\boldsymbol a \times \boldsymbol b) \times \boldsymbol c &= \alpha((\boldsymbol a \cdot \boldsymbol a)\boldsymbol b - (\boldsymbol a \cdot \boldsymbol b)\boldsymbol a) + \beta((\boldsymbol a \cdot \boldsymbol b)\boldsymbol b - (\boldsymbol b \cdot \boldsymbol b)\boldsymbol a) \\
&=(\alpha(-\boldsymbol a \cdot \boldsymbol b) + \beta(-\boldsymbol b \cdot \boldsymbol b))\boldsymbol a + (\alpha \boldsymbol a \cdot \boldsymbol a + \beta \boldsymbol a \cdot \boldsymbol b)\boldsymbol b \\
&= (\boldsymbol a \cdot \boldsymbol c) \boldsymbol b - (\boldsymbol b \cdot \boldsymbol c) \boldsymbol a
\end{aligned}
$$

Q.E.D.

From the anticommutative property of cross product, we get two vector triple product formulas:

$$
\begin{aligned}
(\boldsymbol a\times \boldsymbol b)\times \boldsymbol c &=(\boldsymbol a \cdot \boldsymbol c)\boldsymbol b - (\boldsymbol b \cdot \boldsymbol c)\boldsymbol a \\
\boldsymbol a \times(\boldsymbol b \times \boldsymbol c) &= (\boldsymbol a \cdot \boldsymbol c)\boldsymbol b - (\boldsymbol a \cdot \boldsymbol b)\boldsymbol c
\end{aligned}
$$

As you can see, the vector triple product has strict requirements on the order of operations.

Using the scalar triple product and vector triple product, we can also prove Lagrange's identity.

$$
(\boldsymbol a \times \boldsymbol b) \cdot (\boldsymbol c \times \boldsymbol d)=(\boldsymbol a \cdot \boldsymbol c)(\boldsymbol b \cdot \boldsymbol d)-(\boldsymbol a \cdot \boldsymbol d)(\boldsymbol b \cdot \boldsymbol c)
$$

Proof:

$$
\begin{aligned}
(\boldsymbol a \times \boldsymbol b) \cdot (\boldsymbol c \times \boldsymbol d) &= \det(\boldsymbol c, \boldsymbol d, \boldsymbol a \times \boldsymbol b) \\
&= \det(\boldsymbol a \times \boldsymbol b, \boldsymbol c, \boldsymbol d) \\
&= ((\boldsymbol a \times \boldsymbol b)\times \boldsymbol c)\cdot \boldsymbol d \\
&= (\boldsymbol b(\boldsymbol a \cdot \boldsymbol c)- \boldsymbol a(\boldsymbol b \cdot \boldsymbol c))\cdot \boldsymbol d \\
&= (\boldsymbol a \cdot \boldsymbol c)(\boldsymbol b \cdot \boldsymbol d) - (\boldsymbol a \cdot \boldsymbol d)(\boldsymbol b \cdot \boldsymbol c)
\end{aligned}
$$

As you can see, the earlier identity:

$$
(\boldsymbol a \times \boldsymbol b) \cdot (\boldsymbol a \times \boldsymbol b) = |\boldsymbol a|^2|\boldsymbol b|^2 - (\boldsymbol a \cdot \boldsymbol b)^2
$$

is a special case of Lagrange's identity.