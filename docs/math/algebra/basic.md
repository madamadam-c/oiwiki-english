author: jifbt, billchenchina, Enter-tainer, Great-designer, iamtwz, ImpleLee, isdanni, Menci, ouuan, Tiphereth-A, warzone-oier, Xeonacid, c-forrest

This chapter provides a brief introduction to abstract algebra. Currently, the main content of competitive programming contests does not directly test abstract algebra knowledge; however, basic concepts of abstract functions often appear in algorithm descriptions or problem solutions, enabling readers with a foundation in abstract algebra to understand certain algorithms more quickly. Therefore, this chapter is not mandatory for any competitor, but serves as reference material for interested readers or those who may benefit from it. Additionally, this chapter will avoid overly comprehensive or deep coverage of abstract algebra[^oi-wiki-not-wikipedia], focusing instead on fundamental concepts and parts most closely related to other OI topics. Readers wishing to systematically study abstract algebra should consult specialized textbooks.

To better help readers understand the potential benefits of studying this material, here are some examples of how abstract algebra may appear in competitive programming:

-   Many theorems in number theory and polynomial theory are special cases of results in abstract algebra;
-   In data structures, structures like [segment trees](../../ds/seg.md) can maintain information of monoids, and many DP recurrence relations can be abstracted into such monoid structures;
-   In combinatorics, the rigorous statement and proof of [Pólya's enumeration theorem](../combinatorics/polya.md) requires concepts from group theory.

Based on this, this chapter will focus on essential foundational knowledge and parts directly related to these applications. As a starting point, this article introduces the basic concepts of groups, rings, and fields.

## Groups

A group is defined as follows.

???+ abstract "Group"
    Let $G$ be a nonempty set with a binary operation $\cdot:G\times G\rightarrow G$. If they satisfy the following properties, then $(G,\cdot)$ is called a **group**:

    1.  Associative property: For all $a,b,c\in G$, we have $a\cdot(b\cdot c)=(a\cdot b)\cdot c$;
    2.  Existence of identity element: There exists $e\in G$ such that for any $a\in G$, we have $a\cdot e=e\cdot a=a$. Here, $e$ is called the **identity element** (or identity) of $G$;
    3.  Existence of inverse element: For all $a\in G$, there exists $b\in G$ such that $a\cdot b=b\cdot a=e$. Here, $b$ is called the **inverse element** of $a$.

??? info "On the closure condition in the definition"
    The binary operation here implicitly includes the so-called closure condition, i.e., for any $a,b\in G$, we have $a\cdot b\in G$. Some texts may list this separately.

???+ note "Basic properties of groups"
    For a group $(G,\cdot)$, the following properties always hold:

    1.  For any finite sequence $\{g_i\}_{i=1}^k\subseteq G$, the product $g_1\cdot g_2\cdot\cdots\cdot g_k$ is independent of how parentheses are placed;
    2.  The identity element $e$ is always unique;
    3.  For any element $a\in G$, its inverse $a^{-1}$ is also unique;
    4.  Cancellation law: For $a,b,c\in G$, if $a\cdot c=b\cdot c$ or $c\cdot a=c\cdot b$, then $a=b$.

Groups are quite common. Intuitively, all structure-preserving transformations automatically form a group. Here are some common types of groups.

???+ example "Examples of groups"
    -   **Symmetric group**: All [permutations](../permutation.md) on a set $M$, i.e., bijections from $M$ to itself, form a group $S_M$ under composition of mappings. The identity element is the identity transformation, and the inverse is the inverse mapping (a bijection necessarily has an inverse). If the set $M$ is finite with size $n$, it is often denoted $S_n$, called the symmetric group of degree $n$.
    -   **Symmetry group**: For a geometric figure, all transformations that map it onto itself form a group under composition. This describes the spatial symmetry of the geometric figure. See [Common spatial symmetry groups](../combinatorics/polya.md#常见空间对称群) for specific examples.
    -   **Additive group of integers**: The set of integers $\mathbf Z$ forms a group $(\mathbf Z,+)$ under addition. The identity element is $0$, and the inverse is the additive inverse.
    -   **Multiplicative group of integers modulo $n$**: For a modulus $n$, all integers coprime to $n$, represented by their [congruence classes](../number-theory/basic.md#同余类与剩余系), form a group $((\mathbf Z/n\mathbf Z)^\times,\times)$ under multiplication. The identity element is $\bar 1$, and the inverse is the [multiplicative inverse modulo $n$](../number-theory/inverse.md) (the corresponding congruence class), whose existence is guaranteed by the [Bézout's theorem](../number-theory/bezouts.md). See [Multiplicative group of integers modulo $n$](./ring-theory.md#应用整数同余类的乘法群) for detailed structure analysis.
    -   **General linear group**: All invertible $n\times n$ matrices over a number field $F$ form a group $GL_n(F)$ under matrix multiplication. The identity element is the identity matrix, and the inverse is the inverse matrix.

To better understand the definition of groups, it helps to see some examples that are not groups.

???+ example "Examples that are not groups"
    -   All mappings from $M$ to itself (not necessarily bijections) do not form a group, because non-bijective mappings do not have inverses.
    -   Integers under multiplication do not form a group, because $2$ has no multiplicative inverse in the integers.
    -   Positive integers under addition do not form a group, because positive integers have no additive identity.
    -   All nonzero congruence classes modulo $n$ often do not form a group under multiplication. For example, in $(\mathbf Z/6\mathbf Z)\setminus\{\overline 0\}$, we have $\overline 2\times\overline 3=\overline 0$, which is not in this set, meaning multiplication is not a well-defined binary operation on this set (i.e., it does not satisfy closure).

Sometimes, it is necessary to discuss properties of these less complete structures. Therefore, the following concepts can be defined, which are more general than groups.

???+ abstract "Semigroup"
    For a nonempty set $G$ with a binary operation $\cdot$, if the operation satisfies the associative property, then $(G,\cdot)$ is called a **semigroup**.

???+ abstract "Monoid"
    For a semigroup $(G,\cdot)$, if it also has an identity element, then $(G,\cdot)$ is called a **monoid**.

???+ example "Examples of monoids and semigroups"
    In the above examples, $(\mathbf N_+,+)$ is a semigroup, while $(\mathbf Z,\times)$ is a monoid.

Finally, many familiar operations on groups satisfy not only the associative property but also the commutative property. Such groups have relatively simple structure and are called Abelian groups, or commutative groups.

???+ abstract "Abelian group"
    For a group $(G,\cdot)$, if the operation $\cdot$ also satisfies the commutative property, i.e., for all $a,b\in G$, we have $a\cdot b=b\cdot a$, then $(G,\cdot)$ is called an **Abelian group** or **commutative group**.

???+ example "Examples of Abelian and non-Abelian groups"
    -   The integer additive group $(\mathbf Z,+)$ is an Abelian group.
    -   When $n\ge 3$, the symmetric group $S_n$ is not an Abelian group.

These are the basic definitions related to group theory. For more on group theory, see [Group Theory](./group-theory.md) or related books.

## Rings

A ring is defined as follows.

???+ abstract "Ring"
    For a nonempty set $R$ with two binary operations $+:R\times R\rightarrow R$ and $\cdot:R\times R\rightarrow R$, if they satisfy the following properties, then $(R,+,\cdot)$ is a **ring**:

    1.  $(R,+)$ forms an Abelian group, with identity denoted $0$, and the additive inverse of $a\in R$ denoted $-a$.
    2.  $(R,\cdot)$ forms a semigroup, i.e., $\cdot$ satisfies the associative property.
    3.  Distributive property: For all $a,b,c\in R$, we have $a\cdot(b+c)=a\cdot b+a\cdot c$ and $(a+b)\cdot c=a\cdot c+b\cdot c$.

For convenience, these two binary operations $+$ and $\cdot$ are often called addition and multiplication of the ring, respectively. Correspondingly, the additive identity is called the **zero**, and the multiplicative identity (if it exists) is called the **identity**. Care should be taken to avoid confusion with addition and multiplication in specific number systems, as well as the natural number zero and one.

??? info "On whether the definition requires a multiplicative identity"
    In some definitions, a ring must have a multiplicative identity; correspondingly, rings without a multiplicative identity are called **rngs** or **pseudo-rings**. Context should determine which definition is being used. Wikipedia uses this definition[^ring-wiki].

The additive structure of rings is quite simple, but the multiplicative structure is very primitive. Therefore, analogous to groups, if we impose additional requirements on multiplication, we can obtain the following related definitions.

???+ abstract "Ring with identity"
    For a ring $(R,+,\cdot)$, if it has an identity, i.e., there exists a multiplicative identity denoted $1$, then $(R,+,\cdot)$ is called a **ring with identity**.

???+ abstract "Division ring"
    For a nonzero ring with identity $(R,+,\cdot)$, if for all nonzero elements $a\in R$, there exists a multiplicative inverse (denoted $a^{-1}$), then $(R,+,\cdot)$ is called a **division ring**.

???+ abstract "Commutative ring"
    For a ring $(R,+,\cdot)$, if its multiplication satisfies the commutative property, then $(R,+,\cdot)$ is called a **commutative ring**.

An interesting point in the definition of division rings is that it treats $0$ as a special element in the multiplicative structure. This is because $0 = 0\cdot a = a\cdot 0$[^zero-multiplication]. That is, in a ring, the additive identity multiplied by any element yields itself. Thus, it naturally cannot have a multiplicative inverse unless it itself is the multiplicative identity. The only such ring is the zero ring (see the example below).

The insight here is that to understand the multiplicative structure of a general ring, one should remove the influence of the additive identity and consider $R\setminus\{0\}$. Based on this idea, we have the following definitions.

???+ abstract "Zero divisor"
    For a ring $(R,+,\cdot)$, if there exists $b\in R$ with $b\ne 0$ such that $a\cdot b=0$ or $b\cdot a=0$, then the nonzero element $a$ is called a **zero divisor**.

???+ abstract "Unit"
    For a ring $(R,+,\cdot)$, if an element $a$ has a multiplicative inverse, i.e., there exists $b\in R$ such that $a\cdot b=b\cdot a=1$, then the element $a\in R$ is called a **unit**.

??? warning ""Unit" vs "Identity""
    Please do not confuse these two concepts. To avoid confusion, this part of abstract algebra will use the term "invertible element" instead of "unit".

Zero divisors cannot be invertible, and invertible elements cannot be zero divisors. However, a nonzero element can be neither a zero divisor nor an invertible element.

If a ring has no zero divisors, then the set of all nonzero elements is closed under multiplication, i.e., $(R\setminus\{0\},\cdot)$ forms a semigroup. Furthermore, if we require it to be a commutative monoid, we get the definition of an integral domain.

???+ abstract "Integral domain"
    For a nonzero ring $(R,+,\cdot)$, if it is a commutative ring, has a multiplicative identity, and has no zero divisors, then it is called an **integral domain**.

Although elements in an integral domain do not necessarily have inverses, the property of having no zero divisors is sufficient to establish a cancellation law on integral domains.

???+ note "Cancellation law in integral domains"
    Let $R$ be an integral domain with elements $a,b,c\in R$ and $a\neq 0$. If $ab=ac$, then necessarily $b=c$.

For a general ring with identity, if we consider only its invertible elements, we again obtain a group structure. This is called the multiplicative group or the group of units.

???+ abstract "Multiplicative group (group of units)"
    For a ring with identity $(R,+,\cdot)$, let $R^\times$ be the set of all invertible elements in $R$. Then $(R^\times,\cdot)$ forms a group, called the **multiplicative group** or **unit group** of the ring $R$.

Some of the simplest examples of rings are as follows.

???+ example "Examples of rings"
    -   **Zero ring**: The set $\{0\}$ under ordinary addition $+$ and multiplication $\times$ forms a ring, called the zero ring. It is the only ring with one element, and the only ring where the additive and multiplicative identities coincide.
    -   **Integer ring**: The set of integers $\mathbf Z$ with the ordinary addition $+$ and multiplication $\times$ forms the ring $(\mathbf Z,+,\times)$. Actually, this is an integral domain, but it is not a division ring.
    -   **Polynomial ring**: For a ring $R$, one can define a [polynomial ring](./ring-theory.md#多项式环) $R[x]$. If $R$ is an integral domain, then this polynomial ring is necessarily an integral domain.
    -   **Quaternion**: Analogous to complex numbers, consider the set $\mathbf H=\{a+b\mathrm{i}+c\mathrm{j}+d\mathrm{k}:a,b,c,d\in\mathbf R\}$ with defined addition and multiplication, where the multiplication of $\mathrm{i},\mathrm{j},\mathrm{k}$ satisfies

        $$
        \mathrm{i}^2=\mathrm{j}^2=\mathrm{k}^2=-1,\ \mathrm{i}\mathrm{j}=-\mathrm{j}\mathrm{i}=\mathrm{k},\ \mathrm{j}\mathrm{k}=-\mathrm{k}\mathrm{j}=\mathrm{i},\ \mathrm{k}\mathrm{i}=-\mathrm{i}\mathrm{k}=\mathrm{j}.
        $$

        Then one can verify that $\mathbf H$ forms a ring, and it is a non-commutative division ring.
    -   The subset $2\mathbf Z$ of the integers forms a ring under ordinary addition and multiplication. It is a commutative ring with no zero factors, but it does not have an identity.
    -   The integer modulo $n$ congruence classes $\mathbf Z/n\mathbf Z$ form a ring under addition and multiplication of congruence classes. It is a commutative ring with identity (i.e., $\bar 1$). Such a ring has zero divisors if and only if $n$ is composite. Therefore, when $n$ is a prime, the ring $(\mathbf Z/n\mathbf Z, +,\times)$ is an integral domain; moreover, it is also a division ring, so it actually forms a field. Its multiplicative group $((\mathbf Z/n\mathbf Z)^\times,\times)$ is the multiplicative group of integers modulo $n$.
    -   **Matrix ring**: All $n\times n$ matrices over a ring $R$ form a ring $M_n(R)$ under matrix addition and multiplication. In general, this ring has zero divisors and is not commutative.
    -   For a set $A$, the power set $\mathcal P(A)$ forms a ring $(\mathcal P(A),\triangle,\cap)$ where symmetric difference $\triangle$ is the addition and intersection $\cap$ is the multiplication. In general, this ring has an identity, has zero divisors, and is commutative.

Of course, the discussion of ring structure is far from complete. For more information, see [Ring Theory](./ring-theory.md) or related books.

## Fields

A field is an algebraic structure with stronger properties than a ring. Specifically, a field is a commutative division ring. Its complete definition can also be written.

???+ abstract "Field"
    For a nonempty set $F$ with two binary operations $+:F\times F\rightarrow F$ and $\cdot:F\times F\rightarrow F$, if they satisfy the following properties, then $(F,+,\cdot)$ is a **field**:

    1.  $(F,+)$ forms an Abelian group, with identity denoted $0$, and the additive inverse of $a\in F$ denoted $-a$.
    2.  $(F\setminus\{0\},\cdot)$ forms an Abelian group, with identity denoted $1$, and the multiplicative inverse of $a\in F\setminus\{0\}$ denoted $a^{-1}$.

In other words, a field is an algebraic structure closed under the four arithmetic operations: addition, subtraction, multiplication, and division.

Common examples of fields are as follows.

???+ example "Examples of fields"
    -   **Number fields**: The rational number set $\mathbf Q$, real number set $\mathbf R$, and complex number set $\mathbf C$ all form fields under ordinary addition and multiplication.
    -   **Finite fields**: The set of integer congruence classes modulo a prime $p$, i.e., $\mathbf Z/p\mathbf Z$, forms a field under addition and multiplication of congruence classes. There are also other finite fields besides these; their structure is uniquely determined by their size, which must be a prime power.
    -   **Fraction field**: Let $(R,+,\cdot)$ be an integral domain. Consider the set $Q$ of elements of the form $ab^{-1}$. Strictly speaking, define an equivalence relation on the set $R\times(R\setminus\{0\})$: $(a_1,b_1)\sim(a_2,b_2)$ if and only if $a_1b_2=a_2b_1$. Then the set $Q$ is the set of equivalence classes $R\times(R\setminus\{0\})/\sim$, where the equivalence class containing $(a,b)$ is denoted $ab^{-1}$. If we define operations on it as

        $$
        \begin{aligned}
        a_1b_1^{-1}+a_2b_2^{-1} &= (a_1\cdot b_2+a_2\cdot b_1)(b_1\cdot b_2)^{-1},\\
        (a_1b_1^{-1})\cdot(a_2b_2^{-1}) &= (a_1\cdot a_2)(b_1\cdot b_2)^{-1}
        \end{aligned}
        $$

        then $(Q,+,\cdot)$ forms a field, called the fraction field of $R$. For example, the rational number field $(\mathbf Q,+,\times)$ is the fraction field of the integer ring $(\mathbf Z,+,\times)$.
    -   **Quadratic field**: This is obtained by adjoining $\sqrt d$ to the rational field $\mathbf Q$, where $d\neq 0,1$ is square-free. Related content can be found in [Quadratic fields](../number-theory/quadratic.md).

Compared to rings, fields have very simple additive and multiplicative structures. Therefore, the structure of fields themselves is often quite simple. This makes the study of fields quite different from the study of rings; typically, one studies field extensions and corresponding Galois theory. In competitive programming, sometimes calculations need to be performed on extensions of the rational field or finite fields. For content related to field theory, see [Field Theory](./field-theory.md) or related books.

## Applications

Finally, the following problem is used as an example to illustrate how abstract algebraic objects can help analyze specific problems.

???+ note "[Template] Dynamic DP & Dynamic Tree Divide and Conquer (Enhanced Version)](https://www.luogu.com.cn/problem/P4751)"
    Given a tree with $n$ vertices with weights, perform $m$ vertex weight modifications. After each modification, output the sum of weights of the maximum weighted independent set on the tree. The problem is forced to be online.

???+ note "Analysis"
    This problem is a dynamic DP template. A correct implementation requires using [global balanced binary search trees](../../ds/global-bst.md), with sample code on the corresponding page. Here, only the modeling process is analyzed in the context of the problem.

    To highlight the key points, we temporarily ignore how global balanced binary search trees handle tree structures, and instead consider the DP problem for maximum weighted independent sets on a chain. Consider each vertex on the chain $[1,n]$ in order. For vertex $i$, we can either select it ($1$) or not select it ($0$). Let the optimal solutions for the subproblem on $[1,i]$ under these two cases be $f_{i,1}$ and $f_{i,0}$, respectively. Thus, we can write the DP equations as

    $$
    \begin{aligned}
    f_{i,1}&=w_{i}+f_{i-1,0},\\
    f_{i,0}&=\max\{f_{i-1,1},f_{i-1,0}\}.
    \end{aligned}
    $$

    Its initial values are $(f_{0,1},f_{0,0})=(0,0)$, and the final answer is $\max\{f_{n,1},f_{n,0}\}$. To represent the influence of vertex $i$ on the final result, we only need to note that this recurrence can be written as

    $$
    (f_{i,1},f_{i,0})=g(f_{i-1,1},f_{i-1,0};w_i).
    $$

    This is a sequence of maps from $\mathbf R^2$ to $\mathbf R^2$, mapping $(f_{i-1,1},f_{i-1,0})$ to $(f_{i,1},f_{i,0})$. In the language of groups, these transformations form a monoid under composition. This is exactly what segment trees can maintain.

    However, such parameterized transformations $g(\cdot;w_i)$ without special structure cannot generally be described by finite-dimensional data for arbitrary maps from $\mathbf R^2$ to $\mathbf R^2$. Another observation is needed: if on $\mathbf R\cup\{-\infty\}$, we define $\max$ as addition and $+$ as multiplication, then $\mathbf R\cup\{-\infty\}$ forms a structure similar to a ring, where $-\infty$ is the additive identity and $0$ is the multiplicative identity. However, it is not a ring because not all elements have additive inverses. Such a structure is called a semiring[^semiring], and the semiring $(\mathbf R\cup\{-\infty\},\max,+)$ is called the **tropical semiring**.

    Based on the tropical semiring $(R,\oplus,\otimes)$, we can define matrix multiplication on it. That is, for an $m\times n$ matrix $A=(a_{ij})$ and an $n\times p$ matrix $B=(b_{jk})$, we can define their product $AB$ as $(c_{ik})$, where each element equals

    $$
    c_{ik} = \bigoplus_{j=1}^n(b_{ij}\otimes c_{jk}) = \max_{1\le j\le n}\;(b_{ij}+c_{jk}).
    $$

    With this notation, the above recurrence can be viewed as a linear transformation on the tropical semiring and written in matrix form as

    $$
    \left(\begin{matrix}f_{i,1}\\f_{i,0}\end{matrix}\right)
    =\left(\begin{matrix}-\infty&w_i\\0&0\end{matrix}\right)\left(\begin{matrix}f_{i-1,1}\\f_{i-1,0}\end{matrix}\right).
    $$

    Thus, by maintaining the product of matrices on this tropical semiring with a segment tree, we can answer the dynamic DP problem on a chain with multiple modifications.

    Now consider the tree version of this problem. For a node $i$ on the tree, let $S(i)$ be the set of its child nodes. The DP equations at this point are

    $$
    \begin{aligned}
    f_{i,1}&=w_i+\sum_{j\in S(i)}f_{j,0},\\
    f_{i,0}&=\sum_{j\in S(i)}\max\{f_{j,1},f_{j,0}\}.
    \end{aligned}
    $$

    First, transform the problem into a chain version through heavy-light decomposition. Let $h$ be the heavy child of $i$. Then the above recurrence can be written as

    $$
    \begin{aligned}
    f_{i,1}&=w_i+f_{h,0}+g_{i,1},\\
    f_{i,0}&=\max\{f_{j,0},f_{j,1}\}+g_{i,0},
    \end{aligned}
    $$

    where

    $$
    \begin{aligned}
    g_{i,1}&=\sum_{j\in S(i),\ j\neq h}f_{j,0},\\
    g_{i,0}&=\sum_{j\in S(i),\ j\neq h}\max\{f_{j,1},f_{j,0}\}
    \end{aligned}
    $$

    summarize the contributions of light child nodes. According to the description above, these transformations can all be written in matrix form on the tropical semiring, so the entire problem can be maintained on the segment tree after tree decomposition. However, the direct use of tree decomposition plus segment tree has $O(\log^2 n)$ per modification, so the global balanced binary search tree mentioned above is needed to optimize to $O(\log n)$, or alternatively, an LCT can be used for maintenance.

    The tropical semiring and the matrix operations on it are not uncommon. If $\max$ is replaced with $\min$ above, the corresponding tropical semiring is often used in shortest path problems. If an $n\times n$ matrix $A$ gives the (shortest) edge weights between two vertices of a graph with $n$ vertices, then the element at position $(i,j)$ in $A^k$ is the shortest distance from vertex $i$ to vertex $j$ using at most $k$ edges; in particular, $A^n$ is the distance matrix of the graph. Of course, in actual implementation, one does not really compute the power of this matrix naively, but uses the Floyd algorithm with $O(n^3)$ complexity.

## References and Notes

-   Dummitt, D.S. and Foote, R.M. (2004) Abstract Algebra. 3rd Edition, John Wiley & Sons, Inc.
-   [Tropical semiring - Wikipedia](https://en.wikipedia.org/wiki/Tropical_semiring)

[^oi-wiki-not-wikipedia]: Because [OI Wiki is not an encyclopedia](../../intro/what-oi-wiki-is-not.md#oi-wiki-不是百科全书).

[^ring-wiki]: [Ring (mathematics) - Wikipedia](https://en.wikipedia.org/wiki/Ring_%28mathematics%29)

[^zero-multiplication]: The derivation of this equation is $0\cdot a+0 = 0\cdot a = (0+0)\cdot a = 0\cdot a + 0\cdot a$, where the first and second equalities follow from the definition of the additive identity, the third from the distributive property, and the final implication follows from the cancellation law of addition. The other side of multiplication is similar.

[^semiring]: A semiring is obtained by relaxing the requirement that addition must have inverses in the definition of a ring with identity, i.e., the additive structure is a commutative monoid and the multiplicative structure is a monoid. For more information, see [Wikipedia](https://en.wikipedia.org/wiki/Semiring).