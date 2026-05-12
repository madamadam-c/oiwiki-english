Before this article, a note on translation issues. Due to historical reasons, the translation of "vector" differs between mathematics and physics.

In physics and mathematics, related Chinese terminology may use different words for concepts such as "vector" versus "scalar", "eigen" versus "characteristic", and the two senses of "unitary". This article uses the standard mathematical terminology.

In **OI Wiki**, which primarily targets computer science and other engineering-related fields, and has a closer relationship with mathematics, we use the term "vector".

## Definitions and Related Concepts

**Vector**: A quantity that has both magnitude and direction is called a vector. In mathematics, we study **free vectors**, which are vectors that can be arbitrarily moved parallelly without changing their magnitude and direction. Denoted as $\vec a$ or $\boldsymbol{a}$.

**Directed line segment**: A line segment with a direction is called a directed line segment. A directed line segment has three elements: **starting point, direction, length**. Knowing these three elements uniquely determines the endpoint. Directed line segments are generally used to represent vectors.

**Magnitude of a vector**: The length of directed line segment $\overrightarrow{AB}$ is called the magnitude of the vector, which is the size of this vector. Denoted as: $|\overrightarrow{AB}|$ or $|\boldsymbol{a}|$.

**Zero vector**: A vector with magnitude $0$. The direction of a zero vector is arbitrary. Denoted as: $\vec 0$ or $\boldsymbol{0}$.

**Unit vector**: A vector with magnitude $1$ is called the unit vector in that direction. Generally denoted as $\vec e$ or $\boldsymbol{e}$.

**Parallel vectors**: Two **non-zero** vectors with the same or opposite direction. Denoted as: $\boldsymbol a\parallel \boldsymbol b$. For multiple parallel vectors, we can draw a line parallel to all of them. Any group of parallel vectors can be translated to the same line, so parallel vectors are also called **collinear vectors**.

**Equal vectors**: Vectors with equal magnitude and the same direction.

**Opposite vectors**: Vectors with equal magnitude and opposite directions.

**Angle between vectors**: Given two non-zero vectors $\boldsymbol a,\boldsymbol b$, let $\overrightarrow{OA}=\boldsymbol a,\overrightarrow{OB}=\boldsymbol b$, then $\theta=\angle AOB$ is the angle between vector $\boldsymbol a$ and vector $\boldsymbol b$. Denoted as: $\langle \boldsymbol a,\boldsymbol b\rangle$. Clearly, when $\theta=0$, the two vectors point in the same direction; when $\theta=\pi$, they point in opposite directions; when $\theta=\frac{\pi}{2}$, the two vectors are perpendicular, denoted as $\boldsymbol a\perp \boldsymbol b$. It is specified that $\theta \in [0,\pi]$.

Note that plane vectors have directionality, so two vectors cannot be compared in size (though the magnitudes of two vectors can be compared). However, two vectors can be equal.

## Linear Operations on Vectors

### Addition and Subtraction of Vectors

After defining a quantity, we want to perform operations on it. Vector operations can be compared to operations on numbers. From the perspective of physics, we can also study vector operations.

Comparing with the concept of displacement in physics: if a person goes from $A$ through $B$ to $C$, then the displacement is $\overrightarrow{AB}+\overrightarrow{BC}$, which is essentially equivalent to the person going directly from $A$ to $C$, i.e., $\overrightarrow{AB}+\overrightarrow{BC}=\overrightarrow{AC}$.

Note that the law of composition of forces — the parallelogram law — can also be seen as adding some vectors.

Summarizing the vector addition rules:

1.  **Triangle rule for vector addition**: If the vectors to be added are connected head to tail in sequence, then the sum of these vectors is the vector from the starting point of the first vector to the ending point of the last vector.

2.  **Parallelogram rule for vector addition**: If the two vectors to be added have a common starting point, then their sum vector is the diagonal of the parallelogram with these two vectors as adjacent sides, with the starting point being the common starting point of the two vectors, and the direction being along the diagonal of the parallelogram.

This gives geometric meaning to vector addition. It can be verified that vector addition satisfies the **commutative and associative laws**.

Since subtraction of real numbers can be written as adding the opposite, consider doing the same for vectors. That is: $\boldsymbol a-\boldsymbol b=\boldsymbol a+(-\boldsymbol b)$.

Thus, for vectors with a common starting point, following the parallelogram rule to construct their difference, after translation, we can find that "the difference vector of vectors with a common starting point" is the directed line segment from the "subtrahend vector" to the "minuend vector". This is also the geometric meaning of vector subtraction.

Sometimes, given two points $A,B$, to find $\overrightarrow{AB}$, we can use the subtraction operation $\overrightarrow{AB}=\overrightarrow{OB}-\overrightarrow{OA}$.

### Scalar Multiplication of Vectors

The "product of a real number $\lambda$ and vector $\boldsymbol a$" is defined as a vector. This operation is called **scalar multiplication** of vectors, denoted as $\lambda \boldsymbol a$. Its length and direction are defined as follows:

1.  $|\lambda \boldsymbol a|=|\lambda||\boldsymbol a|$;

2.  When $\lambda >0$, $\lambda\boldsymbol a$ has the same direction as $\boldsymbol a$; when $\lambda =0$, $\lambda \boldsymbol a=\boldsymbol 0$; when $\lambda<0$, $\lambda\boldsymbol a$ has the opposite direction to $\boldsymbol a$.

According to the definition of scalar multiplication, the following laws can be verified:

$$
\begin{aligned}
\lambda(\mu \boldsymbol a)&=(\lambda \mu)\boldsymbol a\\
(\lambda+\mu)\boldsymbol a&=\lambda \boldsymbol a+\mu \boldsymbol a\\
\lambda(\boldsymbol a+\boldsymbol b)&=\lambda \boldsymbol a+\lambda \boldsymbol b
\end{aligned}
$$

In particular:

$$
\begin{gathered}
(-\lambda)\boldsymbol a=-(\lambda \boldsymbol a)=-\lambda(\boldsymbol a)\\
\lambda(\boldsymbol a-\boldsymbol b)=\lambda \boldsymbol a-\lambda \boldsymbol b
\end{gathered}
$$

### Determining Collinear Vectors

Two **non-zero** vectors $\boldsymbol a$ and $\boldsymbol b$ are collinear $\iff$ there exists a unique real number $\lambda$ such that $\boldsymbol b=\lambda \boldsymbol a$.

Proof: From the definition of scalar multiplication, for a **non-zero** vector $\boldsymbol a$, if there exists a real number $\lambda$ such that $\boldsymbol b=\lambda \boldsymbol a$, then $\boldsymbol a \parallel \boldsymbol b$.

Conversely, if $\boldsymbol a\parallel \boldsymbol b$, $\boldsymbol a \not = \boldsymbol 0$, and $|\boldsymbol b|=\mu |\boldsymbol a|$, then when $\boldsymbol a$ and $\boldsymbol b$ have the same direction, $\boldsymbol b=\mu \boldsymbol a$; when they have opposite directions, $\boldsymbol b=-\mu \boldsymbol a$.

Finally, vector addition, subtraction, and scalar multiplication are collectively called linear operations on vectors.

## Fundamental Theorem of Plane Vectors and Coordinate Representation

### Fundamental Theorem of Plane Vectors

Theorem: If two vectors $\boldsymbol{e_1},\boldsymbol{e_2}$ are not collinear, then there exists a unique ordered pair $(x,y)$ such that for any vector $\mathbf p$ coplanar with $\boldsymbol{e_1},\boldsymbol{e_2}$, we have $\mathbf p=x\boldsymbol{e_1}+y\boldsymbol{e_2}$.

There are many plane vectors. How can we represent all plane vectors with as few quantities as possible?

Obviously, using only one vector to represent all vectors is impossible — at most it can represent vectors on a certain line.

Adding another vector, using two **non-collinear** vectors (two collinear vectors here can be regarded as the same vector), we can decompose any plane vector into the directions of these two vectors.

Two non-collinear vectors in the same plane are called a **basis**. If the bases are perpendicular to each other, then decomposing vectors is **orthogonal decomposition**.

### Coordinate Representation of Plane Vectors

If we take unit vectors $i,j$ in the directions of the x-axis and y-axis as a basis, then according to the fundamental theorem of plane vectors, all vectors in the plane correspond one-to-one with ordered real pairs $(x,y)$.

An ordered real pair $(x,y)$ corresponds one-to-one with points on the rectangular coordinate plane. So, let $\overrightarrow{OP}=\boldsymbol p$, then the endpoint $P(x,y)$ is also uniquely determined. Since the object of study is free vectors, we can freely translate the starting point. Thus, in the rectangular coordinate plane, each vector can be represented uniquely by an ordered real pair.

## Coordinate Operations of Plane Vectors

### Linear Operations on Plane Vectors

From the linear operations on plane vectors, we can derive their coordinate operations. The main method is to convert all coordinates to be expressed using the basis, then use the operation laws to combine them, and finally express the resulting coordinates.

If two vectors are $\boldsymbol a=(m,n)$, $\boldsymbol b=(p,q)$, then:

$$
\begin{aligned}
\boldsymbol a+\boldsymbol b&=(m+p,n+q)\\
\boldsymbol a-\boldsymbol b&=(m-p,n-q)\\
k\boldsymbol a&=(km,kn)
\end{aligned}
$$

### Finding the Coordinate Representation of a Vector

Given two points $A(a,b),B(c,d)$, it is easy to prove that $\overrightarrow{AB}=(c-a,d-b)$.

### Translating a Point

Sometimes we need to translate a point $P$ along a certain direction by a certain distance. We combine the direction and distance into a vector, and use the triangle rule for vector addition to add this vector to $\overrightarrow{OP}$. The endpoint of the resulting vector is the point after translation.

### Determining Collinearity of Three Points

If points $A,B,C$ are collinear, then $\overrightarrow{OB}=\lambda \overrightarrow{OA}+(1-\lambda)\overrightarrow{OC}$.

### Extension of the Three-Point Collinearity Condition

In triangle $ABC$, if $D$ is the $n$-division point of $BC$ ($n\ BD=k\ DC$), then: $\overrightarrow{AD}=\frac{n}{k+n}\overrightarrow{AB}+\frac{k}{k+n}\overrightarrow{AC}$

## Extension in Three-Dimensional Space (Solid Geometry/Space Vectors)

In space, all the content described above still holds. Moreover:

### Fundamental Theorem of Space Vectors

Theorem: If three vectors $\boldsymbol{e_1},\boldsymbol{e_2},\boldsymbol{e_3}$ are not coplanar, then there exists a unique ordered triple $(x,y,z)$ such that any vector $\mathbf p$ in space satisfies $\mathbf p=x\boldsymbol{e_1}+y\boldsymbol{e_2}+z\boldsymbol{e_3}$.

According to the fundamental theorem of space vectors, we can also use three mutually perpendicular bases $\boldsymbol{e_1},\boldsymbol{e_2},\boldsymbol{e_3}$ as orthogonal bases to establish a **spatial rectangular coordinate system** and use a triple $(x,y,z)$ as coordinates to represent space vectors.

### Fundamental Theorem of Coplanar Vectors

If there exist two non-collinear vectors $\boldsymbol{x},\boldsymbol{y}$, then vector $\boldsymbol{p}$ is coplanar with $\boldsymbol{x},\boldsymbol{y}$ if and only if there exists a unique ordered pair $(a,b)$ such that $\boldsymbol{p}=a\boldsymbol{x}+b\boldsymbol{y}$.

### Direction Vectors

The direction of a space line is represented by a non-zero vector parallel to that line. This vector is called a direction vector of the line. The position of a line in space is **completely determined** by a point it passes through and one of its direction vectors.

Note that lines in a plane also have direction vectors.

For lines in **space**, the following methods can be used to find the direction vector:

-   If we have $A(x_1,y_1,z_1),B(x_2,y_2,z_2)$, then a direction vector of the line $AB$ is $\boldsymbol{s}=(x_2-x_1,y_2-y_1,z_2-z_1)$.

-   If we know a plane **perpendicular** to the line to be found, the general equation of this plane is $ax+by+cz+d=0$, then a direction vector of the line perpendicular to this plane is $\boldsymbol{s}=(a,b,c)$. This direction vector is also **a normal vector** of the plane.

### Normal Vectors

For a face $ABCD$, its normal vector $\boldsymbol{n}$ is perpendicular to this face.

Calculation method: Take two lines in the plane $\overrightarrow{AB},\overrightarrow{AD}$ such that $\overrightarrow{AB} \cdot \boldsymbol{n}=\boldsymbol{0}$ and $\overrightarrow{AD} \cdot \boldsymbol{n}=\boldsymbol{0}$, then use the coordinate method to calculate.

## Vectors and Matrices

In linear algebra, linear transformations can be represented by matrices. Let $T$ be a linear transformation mapping $\mathbf R^n$ to $\mathbf R^m$, and $\mathbf x$ be an $n$-dimensional column vector. Then there exists an $m\times n$ matrix $A$ such that

$$
T(\mathbf x)=A\mathbf x.
$$

Matrix $A$ is called the transformation matrix of linear transformation $T$. In algorithm problems, linear transformations generally occur in the same dimension, so $A$ is a square matrix. This way, the problem of linear transformation on vectors can be transformed into matrix multiplication.

Next, we discuss three common transformations in competitions and their corresponding transformation matrices: scaling transformation (transformation matrix denoted $S$), rotation transformation (transformation matrix denoted $R$), and translation transformation (transformation matrix denoted $T$).

### Scaling Transformation

For an $n$-dimensional column vector $\boldsymbol a$, scale each dimension by $v_1,v_2,\ldots,v_n$. It is easy to find that the transformation matrix $R$ for the scaling operation is an $n\times n$ diagonal matrix, i.e., $S=\operatorname{diag}\{v_1,v_2,\ldots,v_n\}$.

### Rotation Transformation

Vector rotation is a relatively complex operation. We only discuss the cases in two and three dimensions.

#### Rotating a Vector Around a Point

For rotating a vector around a point, it generally refers to rotating around the origin. To rotate around another point $P$, we can use a translation transformation to move point $P$ to the origin, perform vector rotation, then translate the coordinate system back to its original position. Let the transformation matrix for translation be $T$, and the transformation matrix for rotation around the origin be $R$. Then the transformation matrix for the entire process is $TRT^{-1}$. According to geometric meaning, $T^{-1}$ must exist.

For two-dimensional space, let $\boldsymbol a=(x,y)$, with inclination angle $\theta$, and length $l=\sqrt{x^2+y^2}$. Then $x=l\cos \theta,y=l\sin\theta$. Let it rotate counterclockwise by angle $\alpha$ around the origin to get vector $\boldsymbol b=(l\cos(\theta+\alpha),l\sin(\theta+\alpha))$.

![](./images/vector-rotation.svg)

Using trigonometric identities,

$$
\boldsymbol{b}=(l(\cos\theta\cos\alpha-\sin\theta\sin\alpha),l(\sin\theta\cos\alpha+\cos\theta\sin\alpha))
$$

Simplifying,

$$
\boldsymbol b=(l\cos\theta\cos\alpha-l\sin\theta\sin\alpha,l\sin\theta\cos\alpha+l\cos\theta\sin\alpha)
$$

Substituting back the $x,y$ from above,

$$
\boldsymbol b=(x\cos\alpha-y\sin\alpha,y\cos\alpha+x\sin\alpha)
$$

Therefore, in two-dimensional space, the transformation matrix $R$ is

$$
R=
\begin{bmatrix}
\cos\alpha & -\sin\alpha\\
\sin\alpha & \cos\alpha
\end{bmatrix}.
$$

For three-dimensional space, vector rotation requires two angle parameters, namely the polar angle rotation angle and the azimuth angle rotation angle. This can be performed using the [space spherical coordinate system](../coordinate.md#空间球坐标系).

#### Rotating a Vector Around a Line

For three-dimensional vectors, it is more common to rotate around a certain line. Similarly, for convenience, this line passes through the origin. If the line does not pass through the origin, we can still translate the coordinate system to transform it.

Take the direction vector of the line $\boldsymbol u=(u_x,u_y,u_z)$. Let a three-dimensional vector rotate counterclockwise by angle $\theta$ around it. Then the corresponding transformation matrix $R$ is[^note1]

$$
R=
\begin{bmatrix}
u_x^2 \left(1-\cos \theta\right) + \cos \theta & u_x u_y \left(1-\cos \theta\right) - u_z \sin \theta & u_x u_z \left(1-\cos \theta\right) + u_y \sin \theta \\ 
u_x u_y \left(1-\cos \theta\right) + u_z \sin \theta & u_y^2\left(1-\cos \theta\right) + \cos \theta & u_y u_z \left(1-\cos \theta\right) - u_x \sin \theta \\ 
u_x u_z \left(1-\cos \theta\right) - u_y \sin \theta & u_y u_z \left(1-\cos \theta\right) + u_x \sin \theta & u_z^2\left(1-\cos \theta\right) + \cos \theta
\end{bmatrix}.
$$

### Translation Transformation

Translation transformation is not a linear transformation, but an affine transformation. However, affine transformations in $\mathbf R^n$ can still be represented by linear transformations in $\mathbf R^{n+1}$.

Consider an $n$-dimensional vector $\boldsymbol a=(a_1,a_2, \ldots , a_n)$. Now we want to translate it along vector $\boldsymbol t=(t_1, t_2, \ldots , t_n)$. We add a dimension to column vector $\boldsymbol a$ and set it to $1$, getting a new column vector $\boldsymbol a'=(a_1, a_2, \ldots , a_n, 1)$. Then the transformation matrix $T$ can be written as

$$
T=
\begin{bmatrix}
1 &   &        &   & t_1    \\
  & 1 &        &   & t_2    \\
  &   & \ddots &   & \vdots \\
  &   &        & 1 & t_n    \\
  &   &        &   & 1      \\
\end{bmatrix}.
$$

For other linear transformation matrices, by adding a column and a row, with the element at the bottom right being $1$ and all other elements being $0$, all linear transformation matrices can be converted to affine transformation matrices. For example, for two-dimensional vector rotation, the transformation matrix can become

$$
R'=
\begin{bmatrix}
\cos\alpha & -\sin\alpha & 0\\
\sin\alpha & \cos\alpha & 0\\
0 & 0 & 1
\end{bmatrix}.
$$

## A More Strict Definition of Vectors

In the above, vectors are defined as directed line segments in space. But strictly speaking, vectors are not just directed line segments. To give a more strict definition of vectors, we need to first define [vector space](./vector-space.md). See the introduction on the [Vector space](./vector-space.md) page.

[^note1]: See [Rotation matrix from axis and angle - Wikipedia](https://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle)
