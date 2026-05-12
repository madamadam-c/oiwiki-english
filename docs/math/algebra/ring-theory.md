Prerequisites: [Basic Concepts of Abstract Algebra](./basic.md), [Group Theory](./group-theory.md)

## Introduction

**Ring theory** studies various types of rings.

The ring theory content in this article is inseparable from the divisibility theory in number theory. First, similar to normal subgroups in group theory, we first introduce the kernel of ring homomorphisms, which is called an ideal; in fact, this is the generalization of the concept of numbers in number theory to general rings. Then, to extend concepts like prime numbers, Euclidean algorithm, and prime factorization over the integer ring to general rings, we get concepts of different types of integral domains.

Many conclusions in number theory still hold in other common rings. It can be said that one part of the work in ring theory is discussing whether these number theory conclusions can hold in general rings; if not, what restrictions need to be imposed on rings to make these conclusions hold.

???+ info "Notation"
    When there is no ambiguity, this article may omit the multiplication symbol for rings, and will write the ring $(R,+,\cdot)$ as the ring $R$. In the ring $R$, the additive identity is also called the zero element, denoted $0$; the multiplicative identity is also called the unity element, denoted $1$.

??? warning "The definition of rings in this article does not require a unity element"
    Note that the definition of rings in this article does not require a unity element. Some articles require rings to contain a unity element, so the statements of some conclusions in this article need slight adjustment. For example, in this article, ideals can be defined based on subrings, but in other articles, they may need to be defined based on additive subgroups.

## Ideals

Similar to the case of groups, we can establish the concepts of subrings and ring homomorphisms.

???+ abstract "Subring"
    For a ring $(R,+,\cdot)$ and its subset $S$, if $(S,+,\cdot)$ is also a ring, then $S$ is called a **subring** of $R$.

???+ example "Example: Integer Ring $\mathbf Z$"
    For any integer $n$, $n\mathbf Z=\{nk:k\in\mathbf Z\}$ is a subring of $\mathbf Z$.

???+ abstract "Ring Homomorphism"
    For rings $(R,+,\cdot)$ and $(S,\oplus,\odot)$, if $\pi$ preserves addition and multiplication, i.e., for all $r_1,r_2\in R$, $\pi(r_1+r_2)=\pi(r_1)\oplus\pi(r_2)$ and $\pi(r_1\cdot r_2)=\pi(r_1)\odot\pi(r_2)$ both hold, then the map $\pi:R\rightarrow S$ is called a **homomorphism** from ring $R$ to ring $S$.

??? info "When ring definitions require a unity element"
    If ring definitions require a unity element, then the definition of ring homomorphisms often also requires that the unity element maps to the unity element. For homomorphisms between non-zero unital rings, this additional requirement only ensures that the homomorphism does not map the entire unital ring to zero.

???+ example "Example: Integer Ring $\mathbf Z$ (continued)"
    The map modulo any non-zero integer $n$, i.e., $\pi:\mathbf Z\rightarrow\mathbf Z/n\mathbf Z$ where $\pi(a)=\bar a$, is a ring homomorphism.

The discussion of the kernel and image of group homomorphisms can be almost entirely transferred here. The (relative) size of the image of a homomorphism determines whether the homomorphism is surjective, and whether the kernel is trivial determines whether the homomorphism is injective. The kernel of a ring homomorphism is defined as follows:

???+ abstract "Kernel of a Homomorphism"
    For a homomorphism $\pi:R\rightarrow S$ from ring $R$ to ring $S$, the **kernel** is $\{r\in R:\pi(r)=0\}$, denoted $\ker\pi$, where $0$ is the additive identity of $S$.

Obviously, the kernel and image of a ring homomorphism are both subrings. Conversely, not all subrings can be the kernel of some ring homomorphism. Subrings that can be the kernel of a ring homomorphism are called ideals of the ring.

???+ abstract "Ideal"
    For a ring $R$ and its subring $I$, then $I$ is called
    
    -   a **left ideal** if for all $r\in R$, $rI\subseteq I$, where $rI=\{ra:a\in I\}$;
    -   a **right ideal** if for all $r\in R$, $Ir\subseteq I$, where $Ir=\{ar:a\in I\}$;
    -   an **ideal** if $I$ is both a left ideal and a right ideal of $R$.

Here, we require that the ideal $I$ is closed under left multiplication and right multiplication by the ring $R$. This condition is natural. Because elements in ideals map to zero under ring homomorphisms, and any number multiplied by zero on the left or right should equal zero, which is the required closure. Additionally, because the additive structure of rings is an abelian group, any subgroup is a normal subgroup; and the multiplicative structure of rings is very primitive and does not impose additional restrictions on substructures. This shows that the condition of being closed under left and right multiplication is also sufficient.

???+ example "Example: Integer Ring $\mathbf Z$ (continued)"
    As an example, the subring $n\mathbf Z$ mentioned earlier is actually an ideal of $\mathbf Z$. It is the set of all multiples of $n$. A multiple of $n$, multiplied by any integer, yields a multiple of $n$. In fact, all ideals of $\mathbf Z$ are of this form, and such rings are called [principal ideal domains](#principal-ideal-domain). For general rings, some ideals are not the set of multiples of a single element; the existence of such general rings is precisely the original motivation for studying ideals (rather than simply studying multiples)[^ideal-history].

### Quotient Rings

As with groups, based on ideals of rings, we can define the **quotient ring** on the set of all (additive group) cosets. Consider the set

$$
R/I=\{a+I:a\in R\},
$$

where the coset $a+I=\{a+b:b\in I\}$. It can be proven that the operations

$$

\begin{aligned}
(a+I)+(b+I)&=(a+b)+I,\\
(a+I)(b+I)&=(ab)+I
\end{aligned}
$$

are well-defined, i.e., the results of these operations are independent of the choice of representatives in the cosets. Under these operations, $R/I$ forms a ring. Again, consistent with the case of groups, we can establish the **first isomorphism theorem** for rings, and there exists a natural homomorphism from the ring to its quotient ring. These proofs show that ideals of rings and normal subgroups of groups play the same role in the homomorphisms of their respective structures.

???+ note "First Isomorphism Theorem"
    Let $\pi:R\rightarrow S$ be a homomorphism from ring $R$ to ring $S$. Then $\ker\pi$ is an ideal of $R$, and $R/\ker\pi\cong\pi(R)$ is a subring of $S$.

???+ abstract "Natural Homomorphism"
    For a ring $R$ and its ideal $I$, the map $\pi:R\rightarrow R/I$ given by $\pi(r)=r+I$ is a surjective homomorphism from $R$ to $R/I$, called the **natural homomorphism** from $R$ to the quotient ring $R/I$.

???+ example "Example: Integer Ring $\mathbf Z$ (continued)"
    As an example, the ring of congruence classes modulo $n$ is $\mathbf Z/n\mathbf Z$, which is the quotient ring of $\mathbf Z$ modulo its ideal $n\mathbf Z$. This also explains the meaning of the symbol $\mathbf Z/n\mathbf Z$. The modulo $n$ map $\pi:\mathbf Z\rightarrow\mathbf Z/n\mathbf Z$ mentioned above is the natural homomorphism here, and the corresponding kernel is exactly the ideal $n\mathbf Z$.

Other isomorphism theorems also hold for rings.

???+ note "Second Isomorphism Theorem"
    Let ring $R$ have subring $A$ and ideal $B$. Then $A+B=\{a+b:a\in A,b\in B\}$ is also a subring of $R$, while $A\cap B$ is an ideal of $A$, $B$ is an ideal of $A+B$, and $(A+B)/B\cong A/(A\cap B)$.

???+ note "Third Isomorphism Theorem"
    Let ring $R$ have ideals $I,J$ with $I\subseteq J$. Then $J/I$ is also an ideal of $R/I$, and $(R/I)/(J/I)\cong R/J$.

???+ note "Correspondence Theorem"
    Let ring $R$ have ideal $I$. Then there is a bijection between the set of all subrings $\mathcal S=\{S:I\subseteq S\subseteq R\}$ of $R$ containing $I$ and the set of all subgroups $\mathcal T=\{T:T\le R/I\}$ of $R/I$. The bijection $\varphi:\mathcal S\rightarrow\mathcal T$ maps $S\in\mathcal S$ to $S/I\in\mathcal T$. This bijection preserves inclusion relations, and ideals of $R$ always map to ideals of $R/I$.

These theorems will play a fundamental role in discussing the structure of rings and ideals later.

### Operations on Ideals

Various operations can be defined on ideals of rings. This is similar to how greatest common multiples and least common multiples can be defined on the divisibility structure of integers.

???+ abstract "Operations on Ideals"
    Let $R$ have ideals $I,J$. The following operations can be defined:
    
    -   The **sum** of ideals: $I+J=\{a+b:a\in I,b\in J\}$;
    -   The **product** of ideals: $IJ=\{\sum_{i=1}^na_ib_i:a_i\in I,b_i\in J\}$, i.e., the set of all finite sums of products of the form $ab$;
    -   The **intersection** of ideals: $I\cap J$.

It is easy to verify that the results of these operations are still ideals of the ring.

???+ example "Example: Integer Ring $\mathbf Z$ (continued)"
    Consider the integer ring $\mathbf Z$. For ideals $n\mathbf Z$ and $m\mathbf Z$, we have
    
    $$
    \begin{aligned}
    n\mathbf Z+m\mathbf Z&=\gcd(m,n)\mathbf Z,\\
    (n\mathbf Z)(m\mathbf Z)&=(mn)\mathbf Z,\\
    (n\mathbf Z)\cap(m\mathbf Z)&=\mathrm{lcm}(m,n)\mathbf Z.
    \end{aligned}
    $$

In general, for a ring $R$ and its ideals $I$ and $J$,

$$
IJ\subseteq I\cap J\subseteq I,J\subseteq I+J.
$$

Using these definitions, we can generalize the Chinese remainder theorem for integers to general rings. But before that, we need to further generalize concepts like prime numbers and coprimality to general rings.

### Maximal Ideals

Through the structure of ideals of rings, we can understand the properties of rings.

A non-zero ring $R$ always has two trivial ideals: $\{0\}$ and $R$. If the ring $R$ is also commutative, then a ring with only these two ideals can only be a field[^simple-ring].

???+ note "Theorem"
    Let $R$ be a commutative non-zero unital ring. Then $R$ is a field if and only if $R$ has only trivial ideals $\{0\}$ and $R$.

??? note "Proof"
    If $R$ is a field, then for any non-zero ideal $I$, we can take any non-zero element $a\in I$. Then for any element $r\in R$, we have $r=(ra^{-1})a\in (ra^{-1})I\subseteq I$, so $I=R$. Conversely, for any $a\in R$ with $a\neq 0$, we can verify that $aR=\{ar:r\in R\}$ is an ideal, which must equal $R$. Therefore, there exists $b\in R$ such that $ab=1$, which shows that $a$ has an inverse, so $R$ is a field.

The condition of commutative rings is necessary here; otherwise, we need to restrict both left ideals and right ideals to be trivial to ensure the ring is a division ring.

This conclusion can be extended to cases where the ring itself is not a field. But at this time, we need to consider quotient rings, and discuss the condition for commutative non-zero unital quotient rings to be fields. The quotient ring $R/I$ being a field means that $R/I$ has only trivial ideals. According to the correspondence theorem, this means that there are no ideals in the original ring $R$ strictly between the ideal $I$ we mod out and $R$ itself. Such an ideal $I$ is called a maximal ideal.

???+ abstract "Maximal Ideal"
    For a ring $R$ and its ideal $M$, if $M\neq R$, and the only ideals of $R$ containing $M$ are $M$ and $R$, then $M$ is called a **maximal ideal**.

???+ note "Theorem"
    Let $R$ be a commutative non-zero unital ring with ideal $M$. Then the quotient ring $R/M$ is a field if and only if $M$ is a maximal ideal.

???+ example "Example: Integer Ring $\mathbf Z$ (continued)"
    For example, in the integer ring $\mathbf Z$, the ideal $n\mathbf Z$ is a maximal ideal if and only if $n$ is a prime. For a prime $p$, the quotient ring $\mathbf Z/p\mathbf Z$ is a field, also denoted $\mathbf F_p$.

Not all rings have maximal ideals, but non-zero unital rings always have maximal ideals.

???+ note "Theorem (Krull)"
    For any ideal $I\neq R$ of a non-zero unital ring $R$, there always exists a maximal ideal $M$ of $R$ such that $I\subseteq M$ holds.

??? note "Proof"
    The idea is to use Zorn's lemma. Consider the set $\mathcal S$ of all proper ideals of $R$ (i.e., ideals not equal to $R$) containing $I$. Since $I\in\mathcal S$, it is non-empty and forms a poset under inclusion. For any chain $J_0\subseteq J_1\subseteq\cdots\subseteq J_n\subseteq\cdots$ in it, let their union be $J$. It is easy to verify that this is also an ideal. Moreover, $J\neq R$, because otherwise $1\in J$, i.e., there exists $n$ such that $1\in J_n$, which contradicts $J_n$ being a proper ideal. Thus, by Zorn's lemma, there exists a maximal ideal $M\supseteq I$.

Maximal ideals, analogous to irreducible elements in divisibility theory. This is because the inclusion relation of ideals is the divisibility relation of integers; no ideal as a superset is like a factor that cannot divide. However, the concept of maximal ideals is broader than that of irreducible elements because not all ideals are principal ideals.

### Prime Ideals

The condition for fields is stricter than that for integral domains. Ideals that ensure the quotient ring is an integral domain are called prime ideals, which are analogous to the concept of prime numbers in divisibility theory.

???+ abstract "Prime Ideal"
    For a commutative ring $R$ and its ideal $P$, if $P\neq R$, and for any elements $a,b\in R$, whenever $ab\in P$ holds, there is always $a\in P$ or $b\in P$, then $P$ is called a **prime ideal**.

This definition may seem somewhat abrupt, but comparing with the [definition of prime numbers](../number-theory/basic.md#fundamental-theorem-of-arithmetic), this definition of prime ideals is also natural.

???+ note "Theorem"
    Let $R$ be a commutative non-zero unital ring with ideal $P$. Then the quotient ring $R/P$ is an integral domain if and only if $P$ is a prime ideal.

??? note "Proof"
    For a commutative non-zero unital ring $R$, the quotient ring $R/P$ is an integral domain if and only if $R/P$ has no zero divisors. Let the coset $a+P$ be denoted $\bar a$. The quotient ring $R/P$ having no zero divisors is equivalent to $\bar a\bar b=\bar 0$ always implying $\bar a=\bar 0$ or $\bar b=\bar 0$. According to the correspondence theorem, this is equivalent to $ab\in P$ always implying $a\in P$ or $b\in P$.

In the integer ring $\mathbf Z$, $n\mathbf Z$ is both a maximal ideal and a prime ideal if and only if $n$ is a prime. In general commutative rings, maximal ideals always imply prime ideals, but not conversely; this can be seen from the properties of their corresponding quotient rings.

???+ note "Theorem"
    For a commutative non-zero unital ring $R$, maximal ideals are necessarily prime ideals.

Later, we will see that the converse only holds in rings with good properties sufficiently similar to the integer ring.

### Principal Ideals

Similar to the concept of subgroups, in the discussion of rings, we often need to consider ideals generated by subsets.

???+ abstract "Ideal Generated by a Subset"
    For a non-zero unital ring $R$ and its non-empty subset $A\subseteq R$, if $I$ is the smallest ideal of $R$ containing $A$ (with respect to inclusion), then $I$ is called the **ideal generated by a subset** $A$, and denoted $(A)$. At this time, $A$ is called the **generating set** of $(A)$.

???+ abstract "Principal Ideal"
    An ideal generated by a single element $a\in R$ is called a **principal ideal**, denoted $(a)$. At this time, $a$ is called the **generator** of $(a)$.

For a set $A$, we can describe its generated ideal. First, we have the following definitions

$$

\begin{aligned}
RA&=\{r_1a_1+\cdots+r_na_n:r_i\in R,a_i\in A,n\in\mathbf Z\},\\
AR&=\{a_1r_1+\cdots+a_nr_n:r_i\in R,a_i\in A,n\in\mathbf Z\}.
\end{aligned}
$$

In fact, they are the left ideal and right ideal generated by $A$ respectively. Then, the ideal generated by $A$ is $RAR$. For commutative rings, all these structures defined are the same.

All ideals in the integer ring are principal ideals, often denoted as $(n)$ below.

## Integral Domains

An integral domain is a commutative, unital, non-zero ring without zero divisors. This concept is a generalization of the integer ring. However, the resulting ring may not be good enough to allow every conclusion from integer divisibility theory to be directly copied. To generalize number theory conclusions, we can further impose restrictions on integral domains. The three most common integral domains are Euclidean domains, principal ideal domains, and unique factorization domains; these concepts strictly contain each other.

### Divisibility Relations

First, we generalize the relevant concepts from integer divisibility theory to general commutative rings.

???+ abstract "Divisibility"
    Let a commutative ring $R$ have elements $a,b\in R$. If there exists $x\in R$ satisfying $a=bx$, then $b$ **divides** $a$, denoted $b\mid a$. At this time, $b$ is called a **divisor** of $a$.

???+ abstract "Associates"
    Let a commutative ring $R$ have elements $a,b\in R$. If they differ only by an invertible element, i.e., there exists an invertible element $u\in R$ satisfying $a=bu$, then $a$ and $b$ are called **associates**.

Divisibility relations are [partial order](../order-theory.md#binary-relations) relations on rings, while associate relations are equivalence relations on rings. From the perspective of ideals, $a\mid b$ is equivalent to $(b)\subseteq (a)$, and $a$ and $b$ being associates is equivalent to $(a)=(b)$. Therefore, when discussing elements in rings, we usually do not distinguish between associates. Similar to the integer case, the greatest common divisor of $a$ and $b$ in a commutative ring is defined as the greatest lower bound of $\{a,b\}$.

???+ abstract "Greatest Common Divisor"
    For a commutative ring $R$ and its elements $a,b\in R$, if there exists a non-zero element $d\in R$ such that $d\mid a$ and $d\mid b$, and for any $d'$ satisfying $d'\mid a$ and $d'\mid b$, we have $d'\mid d$, then $d$ is called the **greatest common divisor** of $a$ and $b$, denoted $\gcd(a,b)$.

In an integral domain, the greatest common divisor is uniquely determined up to associates. The discussion below is limited to integral domains.

We can also establish the concept of prime numbers in integral domains. In number theory, prime numbers have two equivalent definitions, but in general integral domains, these two definitions correspond to different concepts:

???+ abstract "Prime Element"
    Let an integral domain $R$ have a non-zero element $p\in R$. If $(p)$ is a prime ideal, that is, $p$ is not invertible, and $p\mid ab$ always implies $p\mid a$ or $p\mid b$, then $p$ is called a **prime element**.

???+ abstract "Irreducible Element"
    Let an integral domain $R$ have a non-zero element $r\in R$. If $r$ is not invertible, and for any $a,b\in R$ with $r=ab$, either $a$ or $b$ is invertible, then $r$ is called an **irreducible element**, or $r$ is irreducible. Conversely, if $r=ab$ and neither $a,b\in R$ are invertible, then $r$ is reducible.

It can be shown that the principal ideal $(r)$ generated by an irreducible element $r$ is always maximal among all principal ideals of the ring; however, in general integral domains, not all ideals are principal ideals, so the concepts of irreducible elements and maximal ideals are not equivalent.

Similar to proving that prime ideals are always maximal in principal ideal domains, we can generally prove the following conclusion:

???+ note "Theorem"
    Let $R$ be an integral domain. If $a\in R$ is a prime element, then $a$ is also an irreducible element.

??? note "Proof"
    Let $r\in R$ be a prime element, and $a,b\in R$ satisfy $r=ab$. Since $r$ is a prime element, we can assume $r\mid a$ holds, so $a=cr=cba$. Since cancellation holds in integral domains, we have $1=bc$, so $b$ has an inverse $c$. This shows that $r$ is irreducible.

The converse does not hold.

??? example "Counterexample"
    In the quadratic integer ring $\mathbf Z[\sqrt{-5}]$, $3$ is irreducible, but $9=3\cdot3=(2+\sqrt{-5})(2-\sqrt{-5})$, so it is not a prime element.
    
    Here is the proof of this counterexample. Readers unfamiliar with quadratic integer rings should first read the [Quadratic Integer Rings](#examples-quadratic-integer-ring) section. Let $N(\cdot)$ be the norm on the quadratic integer ring. For any factorization $3=ab$, we have $N(a)N(b)=N(3)=9$. If $a,b$ are not invertible, then both $N(a)$ and $N(b)$ are greater than $1$, so necessarily $N(a)=N(b)=3$. However, there is no such element on $\mathbf Z[\sqrt{-5}]$, i.e., $x^2+5y^2=3$ has no integer solutions. This shows that $3$ is irreducible. As for $3$ not being a prime element, it is to prove that $3$ cannot divide $2\pm\sqrt{-5}$, which is obvious.

### Euclidean Domains

Related reading: [(Extended) Euclidean Algorithm](../number-theory/gcd.md), [Bézout's Theorem](../number-theory/bezouts.md)

A Euclidean domain is an integral domain that allows Euclidean algorithm (i.e., division with remainder).

???+ abstract "Euclidean Domain"
    For an integral domain $R$, if there exists a map $N:R\setminus\{0\}\rightarrow\mathbf N$ such that for any $a,b\in R$ with $b\neq 0$, there exist $q,r\in R$ such that $a=qb+r$ holds and either $r=0$ or $N(r)<N(b)$, then $R$ is called a **Euclidean domain**. The map $N$ is called the **norm** of elements in the Euclidean domain.

??? info "Other Equivalent Definitions"
    The definition in this article only defines the norm at non-zero elements. Different texts may handle the definition of Euclidean domains differently. For example, some texts may additionally define $N(0)=0$; but since $N(0)$ is not used in the subsequent division with remainder, this is not important. For another example, the definition in [Wikipedia](https://en.wikipedia.org/wiki/Euclidean_domain) also requires that the norm $N$ satisfies: for any non-zero $a,b\in R$, $N(a)\le N(ab)$. However, it is easy to verify that if a Euclidean domain $R$ has a norm $N(\cdot)$ satisfying the conditions in this article's definition, then we can define $N'(a)=\min_{b\in R\setminus\{0\}} N(ab)$ to make it satisfy the additional property $N'(a)\le N'(ab)$. Therefore, these different definitions are equivalent.

This definition is actually a generalization of division with remainder in integers. The existence of the norm allows measuring the relative size of the remainder and divisor. When performing Euclidean algorithm, the norm of the corresponding remainder is also decreasing; because the norm takes values in natural numbers, such a process must end at $r=0$. Thus, we obtain the Euclidean algorithm on Euclidean domains.

Being able to perform Euclidean algorithm means that we can efficiently compute the greatest common divisor on Euclidean domains. Completely analogizing with integer divisibility theory, the result of Euclidean algorithm is always the greatest common divisor, and Bézout's theorem holds, where the coefficients can be determined by the extended Euclidean algorithm.

???+ note "Theorem"
    For a Euclidean domain $R$ and its elements $a,b\in R$, the result $d$ obtained by applying Euclidean algorithm to $a$ and $b$ is the greatest common divisor of $a$ and $b$, and there exist $x,y\in R$ such that $d=ax+by$ holds; conversely, any element of the form $ax+by$ is a multiple of $d$.

Note that in the language of ring theory, all elements of the form $ax+by$ are precisely the elements in the ideal $(a,b)$, and this theorem shows that $(a,b)$ must be the principal ideal $(d)$.

In fact, ideals in Euclidean domains are always principal ideals.

???+ note "Theorem"
    Ideals in Euclidean domains are always principal ideals.

??? note "Proof"
    Let $R$ be a Euclidean domain, and $I$ its ideal. If $I=\{0\}$, it is obviously a principal ideal. Suppose $I$ is a non-zero ideal. By definition, $R$ has a norm $N(\cdot)$, so we can take $d$, a non-zero element in $I$ with minimal norm. Then for any $a\in I$, we have $a=qd+r$ with $r=0$ or $N(r)<N(d)$. Since $r=a-qd\in I$, by the choice of $d$, we know $r=0$, i.e., $a=qd\in (d)$. This shows that $I$ is necessarily a principal ideal.

### Principal Ideal Domains

An integral domain where all ideals are principal ideals is called a principal ideal domain. This is a fairly well-behaved and quite common type of integral domain. In these rings, the concept of ideals in the ring is equivalent to the concept of multiples in integers.

???+ abstract "Principal Ideal Domain"
    For an integral domain $R$, if all its ideals are principal ideals, then it is called a **principal ideal domain** (PID).

Thus, the last theorem in the previous section can be restated as:

???+ note "Theorem"
    Euclidean domains are necessarily principal ideal domains.

In principal ideal domains, maximal ideals are equivalent to ideals generated by irreducible elements. Similar to how prime numbers and irreducible elements are equivalent in integers, in principal ideal domains, these two concepts are also equivalent, so maximal ideals and prime ideals are also completely equivalent.

???+ note "Theorem"
    Let $R$ be a principal ideal domain with non-zero ideal $I$. Then $I$ is a prime ideal if and only if $I$ is a maximal ideal.

??? note "Proof"
    We only need to prove that prime ideals are maximal. Let $(p)$ be a non-zero prime ideal in the principal ideal domain $R$, and let $(a)$ be an ideal satisfying $(p)\subseteq(a)\subseteq R$. This shows $a\mid p$, so there exists $b\in R$ such that $p=ab$. But since $(p)$ is a prime ideal, $ab\in(p)$ means $a\in(p)$ or $b\in(p)$. If $a\in(p)$, then $(a)\subseteq (p)$, so $(a)=(p)$; if $b\in(p)$, then $b=cp$, so $p=acp$, and since $p\neq 0$, we have $1=ac$, i.e., $a$ has an inverse $c$, so $(a)=R$. This shows that $(p)$ is a maximal ideal.

???+ note "Corollary"
    Let $R$ be a principal ideal domain with non-zero element $r$. Then $r$ is a prime element if and only if $r$ is irreducible.

The analysis of Bézout's theorem in the previous section can be transferred to principal ideal domains.

???+ note "Theorem"
    Let $R$ be a principal ideal domain, and $a,b\in R$ be non-zero elements. Let $d\in R$ be the generator of the ideal $(a,b)$. Then the greatest common divisor of $a$ and $b$ is $d$, and it is uniquely determined up to associates; moreover, there exist $x,y\in R$ such that $ax+by=d$ holds.

That is, [Bézout's theorem](../number-theory/bezouts.md) still holds in principal ideal domains. Also, the existence of greatest common divisors, the main difference between Euclidean domains and principal ideal domains is that in the former, greatest common divisors can be computed efficiently through Euclidean algorithm, but in principal ideal domains, there is generally no such efficient algorithm.

### Unique Factorization Domains

A more general concept than principal ideal domains is the unique factorization domain. The unique factorization theorem for integers is called the [Fundamental Theorem of Arithmetic](../number-theory/basic.md#fundamental-theorem-of-arithmetic). Similar unique factorization theorems actually hold in some integral domains that are not principal ideal domains. Such integral domains are called unique factorization domains.

???+ abstract "Unique Factorization Domain"
    For an integral domain $R$, if any non-zero and non-invertible element $r$ can be written as $r=p_1\cdots p_n$, where $p_1,\cdots,p_n$ are possibly repeated irreducible elements, and such factorization is unique up to associates and rearrangement, then $R$ is called a **unique factorization domain** (UFD).

The fundamental theorem of arithmetic shows that the integer ring $\mathbf Z$ is a unique factorization domain.

The previous section gave a counterexample where irreducible elements are not prime elements, and the integral domain $\mathbf Z[\sqrt{-5}]$ involved does not satisfy unique factorization. However, in all unique factorization domains, irreducible elements and prime elements are both equivalent.

???+ note "Theorem"
    For a unique factorization domain $R$ and its non-zero element $a\in R$, $a$ is a prime element if and only if $a$ is irreducible.

??? note "Proof"
    We only need to prove that irreducible elements are prime elements. For an irreducible element $r$, if $r\mid ab$, then there exists $c\in R$ such that $ab=rc$ holds. Since $R$ is a unique factorization domain, we can factor $a,b,c\in R$ into products of irreducible elements. Comparing both sides, from the uniqueness of factorization, $r$ must be associate with some irreducible factor of $a$ or $b$. Hence, $r$ divides $a$ or $b$. This shows that $r$ is also a prime element.

All principal ideal domains are unique factorization domains.

???+ note "Theorem"
    Principal ideal domains are necessarily unique factorization domains.

??? note "Proof"
    Let $R$ be a principal ideal domain, and $r\in R$ is neither zero nor invertible. To show that $r$ can be uniquely factored into a product of irreducible elements, we can do it in two steps: first prove existence of factorization, then prove uniqueness of factorization.
    
    The existence of factorization is quite natural. If $r$ is already irreducible, there is no need to continue factoring; otherwise, there must exist $r_1r_2$ such that $r=r_1r_2$ and neither $r_1$ nor $r_2$ are invertible. Furthermore, if $r_1$ and $r_2$ are both irreducible, then there is no need to continue factoring; otherwise, we can further factor those in $r_1$ and $r_2$ that are not irreducible, and $r$ can be written as a product of more elements. Thus, as long as not all factors in the product are irreducible, we can continue the factorization process. The factorization must terminate after finitely many steps. Otherwise, the axiom of choice guarantees that we can extract an infinite chain $\{r_{(i)}\}_{i=0}^\infty$ from $R$ satisfying $r_{(0)}=r$ and $r_{(i+1)}\mid r_{(i)}$ for all $i\in\mathbf N$, and these divisibility relations are all strict, i.e., there are no associates in the chain. In the language of ideals, this corresponds to a strictly increasing infinite chain of ideals: $I_{0}\subset I_{1}\subset \cdots\subset I_{i}\subset\cdots\subset R$, where $I_i=(r_{(i)})$. It is easy to verify that the union $I=\bigcup_{i=0}^\infty I_i$ is also an ideal, so it must be principal. Let $a$ be the generator of the principal ideal $I$. Thus, there exists $n\in\mathbf N$ such that $a\in I_n$. So $I=(a)\subseteq I_n$. This shows that such a strictly increasing infinite chain of ideals does not exist, so the factorization process must terminate after finitely many steps.
    
    Now we prove the uniqueness of factorization. We can do induction on the number of factors in the factorization. The key step in induction is to verify that if $r=p_1p_2\cdots p_n=q_1q_2\cdots q_m$ and $n\le m$, then $p_1$ must be associate with some $q_j$. Here we need to use the previous conclusion: in principal ideal domains, irreducible elements are all prime elements. Since $p_1$ is irreducible in $R$, it is also a prime element, so for the product on the right side, we can show by induction that there exists some element $q_j$ such that $p_1\mid q_j$. So there exists $c\in R$ such that $q_j=p_1c$, and since $q_j$ is irreducible and $p_1$ is also irreducible, by definition $c$ must be invertible, so $p_1$ is associate with $q_j$. Then we can use the cancellation law to cancel $p_1$ and $q_j$ on both sides, and multiply the associate difference by one of the remaining elements. By the induction hypothesis, the number of irreducible elements in $p_2\cdots p_n$ and $q_1\cdots q_{j-1}q_{j+1}\cdots q_m$ must be equal, and they are the same up to associates. Theorem proved.

Finally, the existence of greatest common divisors still holds on unique factorization domains.

???+ note "Theorem"
    Let $R$ be a unique factorization domain with non-zero elements $a,b\in R$. Suppose they can be factored as $a=up_1^{r_1}\cdots p_n^{r_n}$ and $b=vp_1^{s_1}\cdots p_n^{s_n}$, where $u,v$ are invertible elements, $p_1,\cdots,p_n$ are distinct irreducible elements, and $r_i,s_i$ are natural numbers. Then one greatest common divisor of them is $d=p_1^{\min\{r_1,s_1\}}\cdots p_n^{\min\{r_n,s_n\}}$.

This actually shows that the existence of greatest common divisors is a weaker condition than the unique factorization theorem[^gcd-domain].

### Example: Quadratic Integer Rings

Related reading: [Quadratic Fields](../number-theory/quadratic.md)

The understanding of abstract algebra cannot be separated from examples. It is precisely because the study of Fermat's Last Theorem required studying the properties of a type of algebraic integers that ring theory developed into what it is today[^ring-theory-history]. Here we discuss the simplest algebraic integers, i.e., quadratic integers. Many proofs in this section require complex algebraic number theory knowledge, so they are omitted.

A **quadratic integer** refers to the complex root of a quadratic equation $\alpha^2+b\alpha+c=0$ with integer coefficients and leading coefficient 1. All quadratic integers can and only can have the form

$$
\alpha=a+b\omega,~(a,b\in\mathbf Z)
$$

where

$$
\omega=\begin{cases}
\dfrac{1+\sqrt{D}}{2},& D\equiv 1\pmod 4,\\
\sqrt D,& D\equiv 2,3\pmod 4,
\end{cases}
$$

and $D$ is square-free.

??? note "Analysis"
    According to the quadratic formula, the roots of this equation can definitely be written as
    
    $$
    \alpha=\frac{-b\pm\sqrt{b^2-4c}}{2}.
    $$
    
    When $b=2k+1$ is odd, this root can be written as
    
    $$
    \alpha=-k-\frac{1\pm\sqrt{4(k^2+k-c)+1}}{2}.
    $$
    
    Otherwise, when $b=2k$ is even, this root can be written as
    
    $$
    \alpha=-k\pm\sqrt{k^2-c}.
    $$
    
    From this, we can conclude that quadratic integers must have the above form.

It is easy to verify that for such $\omega$, the set $\mathbf Z[\omega]=\{a+b\omega:a,b\in\mathbf Z\}$ forms a ring. This is called the **quadratic integer ring**, and its fraction field is the quadratic field $\mathbf Q(\sqrt D)$. When $D>0$, all quadratic integers are real numbers, so they are also called **real quadratic integer rings**; when $D<0$, quadratic integers other than integers are complex numbers, so they are also called **imaginary quadratic integer rings**.

All quadratic integer rings $\mathbf Z[\omega]$ are integral domains. When $D=-1$, $\mathbf Z[\sqrt{-1}]$ (also denoted $\mathbf Z[\mathrm{i}]$) is also called the Gaussian integer ring; when $D=-3$, $\mathbf Z\left[\dfrac{1+\sqrt{-3}}{2}\right]$ is also called the Eisenstein integer ring.

For a quadratic integer $a+b\omega$, its **conjugate** can be defined as $a+b\bar\omega$, where

$$
\bar\omega=\begin{cases}
\dfrac{1-\sqrt{D}}{2},& D\equiv 1\pmod 4,\\
-\sqrt D,& D\equiv 2,3\pmod 4,
\end{cases}
$$

Note that when $D>0$, quadratic integers are real numbers, so the concept of conjugate here is not exactly the same as the concept of conjugate for complex numbers, but they are both special cases of the concept of conjugate of algebraic elements in field theory. Conjugate quadratic integers are roots of the same quadratic equation with integer coefficients.

The **norm** can be defined on quadratic integer rings

$$

\begin{aligned}
N(a+b\omega)&=(a+b\omega)(a+b\bar\omega)\\
&=\begin{cases}
a^2+ab+\dfrac{1-D}{4}b^2,& D\equiv 1\pmod 4,\\
a^2-Db^2,& D\equiv 2,3\pmod 4.
\end{cases}
\end{aligned}
$$

The norm of a quadratic integer is always an integer. Particularly, when $D<0$, the norm is always a natural number. The norm preserves multiplicative structure, i.e., $N(ab)=N(a)N(b)$.

The invertible elements (units) in quadratic integer rings can and only can be those elements with norm $\pm1$. For the case $D>0$, this corresponds to considering solutions of the [Pell equation](../number-theory/pell-equation.md) $x^2-Dy^2=\pm1$ or $x^2-Dy^2=\pm4$. For the case $D<0$, it is easy to verify that except for the special cases where the invertible elements in the Gaussian integer ring $\mathbf Z[\rm{i}]$ are $\{\pm1,\pm\rm{i}\}$ and those in the Eisenstein integer ring $\mathbf Z[\omega]$ are $\{\pm1,\pm\omega,\pm\omega^2\}$, in other cases, invertible elements are only $\{\pm1\}$.

The norm $N(\alpha)$ defined on quadratic integer rings can be used to prove that they are Euclidean domains. For the case $D>0$, we need to use its absolute value $|N(\alpha)|$ as the norm in the definition of Euclidean domain. Using this norm, it can be proved that when $D<0$,

$$
D=-1,-2,-3,-7,-11
$$

or when $D>0$,

$$
D=2, 3, 5, 6, 7, 11, 13, 17, 19, 21, 29, 33, 37, 41, 57, 73
$$

the corresponding quadratic integer rings are Euclidean domains under the norm $|N(\cdot)|$. However, the norm in the definition of Euclidean domains is not necessarily the norm defined above. For example, when $D=14,69$, the corresponding quadratic integer rings are also Euclidean domains, but other norms need to be used. For the case $D<0$, it can be proved that the cases given above are all Euclidean domains in quadratic integer rings.

Using more complex methods, we can also determine whether a quadratic integer ring is a principal ideal domain. It can be proved that when $D<0$, only

$$
D=-1,-2,-3,-7,-11,-19,-43,-67,-163
$$

corresponding quadratic integer rings are principal ideal domains. Comparing with the above results, we can see that cases like $D=-19$ provide examples of principal ideal domains that are not Euclidean domains. For the case $D>0$, there are currently no complete results.

However, it can be proved that in quadratic integer rings, unique factorization domains and principal ideal domains are equivalent. The above results show that, for example, $\mathbf Z[\sqrt{-5}]$ is not a principal ideal domain, and therefore not a unique factorization domain. We have already actually proven through examples that it cannot be uniquely factored, i.e.,

$$
9=3\times3=(2+\sqrt{-5})\times(2-\sqrt{-5}).
$$

Using the same example, we can show that the ideal $(3,2+\sqrt 5)$ is also not principal. Later, we will see that a simple example of a unique factorization domain that is not a principal ideal domain is the polynomial ring $\mathbf Z[x]$.

Although many quadratic integer rings are not unique factorization domains, they are all [Dedekind domains](https://en.wikipedia.org/wiki/Dedekind_domain). This means that all non-trivial ideals in quadratic integer rings can be uniquely factored into products of prime ideals. However, if the quadratic integer ring itself is not a principal ideal domain, these prime ideal factors do not necessarily correspond to prime elements, so the unique factorization theorem (i.e., factoring numbers into products of primes) no longer holds: this is also the original motivation for studying ideals rather than numbers.

## Polynomial Rings

Related reading: [Introduction to Polynomial Techniques](../poly/intro.md)

In competitive programming, various operations on polynomials are often encountered. Operations on polynomials such as multiplication, inversion, and remainder can be seen as generalizations of operations on numbers to polynomial rings. Using the language of abstract algebra, we can more quickly understand the properties of related operations on polynomial rings.

???+ abstract "Polynomial"
    For a non-zero commutative unital ring $R$, a **polynomial** over $R$ is a formal sum
    
    $$
    \sum_{k=0}^{n}a_kx^k = a_0+a_1x+\cdots+a_{n-1}x^{n-1}+a_nx^n,
    $$
    
    where $n\in\mathbf N$, and for each $k$, $a_k\in R$. These $a_k$ are called the **coefficients** of the polynomial, and the corresponding $a_kx^k$ is called a **term** of the polynomial. The $k$ in the term $a_kx^k$ is called the **degree** of that term.
    
    Polynomials where all coefficients are zero (i.e., the zero element) are called **zero polynomials**, denoted $0$. For other polynomials, let $a_n\neq 0$, i.e., $a_nx^n$ is the term with the highest degree among terms with non-zero coefficients. At this time, the natural number $n$ is called the **degree** of the polynomial, and its term $a_nx^n$ is called the **leading term**, and $a_n$ is also called the **leading coefficient**. A polynomial whose leading coefficient is one (i.e., the unity element) is called a **monic** polynomial. The degree of the zero polynomial is not specified, or defined as $-\infty$.

The $x$ appearing in polynomial notation is called the **indeterminate** of the polynomial. It has no meaning itself and has no range of values. Its existence is only to mark the position of coefficients through its exponent. Therefore, polynomials can also be written as sequences over $R$

$$
(a_0,a_1,...,a_{n-1},a_n,0,0,\cdots).
$$

However, such sequences can only have finitely many non-zero terms. If two polynomials have the same coefficient sequence, they are said to be equal. This is equivalent to their formal sums being completely identical after complementing zero coefficients. Below, we will no longer distinguish the notation of formal sums of equal polynomials: readers can complement the missing zero coefficients themselves if needed.

Sometimes we need to substitute elements of the ring into the indeterminate of polynomials. For example, let $f(x)$ be a polynomial in $R$ and $a\in R$, then substituting $a$ into $f(x)$ gives $f(a)$. Its meaning is: in the formal sum of the polynomial, replacing $x$ with $a$, we get an arithmetic expression in $R$, and $f(a)$ is the result of this expression in $R$.

??? info ""Polynomial" and "Polynomial Function""
    Readers should not confuse these two concepts. Polynomials are only finite-length coefficient sequences, and they do not automatically become functions. Although the operation of substituting ring elements into indeterminates does map polynomials to polynomial functions, such a mapping is not necessarily injective. For example, as a polynomial over $\mathbf F_p$, $f(x)=x^p-x$ is obviously not equal to the zero polynomial; but as a polynomial function $\mathbf F_p\rightarrow \mathbf F_p$, it is always equal to zero (i.e., Fermat's little theorem). Although the two concepts are different, many concepts of polynomial functions can be generalized to polynomials, for example, we can define the (formal) [derivative](../poly/intro.md#derivative), [indefinite integral](../poly/intro.md#derivative), [composition](../poly/intro.md#composition) of polynomials by analogy with differentiation, indefinite integration, and composition of polynomial functions. These formal operations do not depend on any topological structure, but many operation rules still hold.

For polynomials

$$

\begin{aligned}
f(x)&=a_0+a_1x+\cdots+a_{n-1}x^{n-1}+a_nx^n,\\
g(x)&=b_0+b_1x+\cdots+b_{n-1}x^{n-1}+b_nx^n,
\end{aligned}
$$

the addition of polynomials is defined as

$$
f(x)+g(x) = (a_0+b_0)+(a_1+b_1)x+\cdots+(a_{n-1}+b_{n-1})x^{n-1}+(a_n+b_n)x^n,
$$

and the multiplication of polynomials is defined as

$$
f(x)g(x) = a_0b_0+(a_1b_0+a_0b_1)x+(a_2b_0+a_1b_1+a_0b_2)x^2+\cdots,
$$

where the coefficient of $x^k$ is $\sum_{i=0}^ka_{k-i}b_i$. Under the addition and multiplication defined this way, the set of all polynomials over $R$ forms a ring, denoted $R[x]$.

The degree of a polynomial $f(x)$ is denoted $\deg f(x)$. Polynomials with degree zero are constant polynomials, and along with the zero polynomial, they correspond to the embedding of $R$ in $R[x]$. Obviously, $R$ has zero divisors if and only if $R[x]$ has zero divisors.

???+ note "Theorem"
    The polynomial ring $R[x]$ is an integral domain if and only if $R$ is an integral domain.

On the polynomial ring $R[x]$ over an integral domain $R$, the results of addition and multiplication satisfy

$$

\begin{aligned}
\deg(f(x)+g(x)) &\le \max\{\deg f(x),\deg g(x)\},\\
\deg(f(x)g(x)) &= \deg f(x) + \deg g(x).
\end{aligned}
$$

Here we set $\deg 0 = -\infty$. Therefore, invertible elements in polynomial rings must also be those invertible elements in their constant polynomials. Any polynomial of degree one or higher is not invertible.

The discussion below will be limited to polynomials over integral domains.

???+ info "Convention"
    Below, we will not distinguish between "polynomials over ring $R$" and "polynomials in polynomial ring $R[x]$". For example, a polynomial being irreducible over ring $R$ means it is irreducible in ring $R[x]$. Moreover, if $R$ is a subring of $S$, then polynomials over $R$ automatically become polynomials over $S$; we will not repeat this.

### Polynomial Rings over Fields

Among polynomial rings over integral domains, the simplest are polynomial rings over fields. Polynomial ring over a field $F$ is $F[x]$. Since coefficients can be divided, we can define division with remainder. Let the norm of a non-zero polynomial $f(x)$ be $N(f(x))=\deg f(x)$. Then for polynomials $f(x)$ and non-zero polynomial $g(x)$ in $F[x]$, we can obviously perform division with remainder

$$
f(x)=g(x)q(x)+r(x),
$$

where $q(x),r(x)\in F[x]$, and $r(x)=0$ or $\deg r(x)<\deg g(x)$. This shows that polynomial rings over fields are all Euclidean domains.

???+ note "Theorem"
    The polynomial ring $F[x]$ over a field $F$ is a Euclidean domain, a principal ideal domain, and a unique factorization domain.

In competitive programming, due to calculation precision reasons, we often consider the polynomial ring $\mathbf F_p[x]=(\mathbf Z/p\mathbf Z)[x]$, where the modulus $p$ is required to be prime. Such rings allow operations like Euclidean algorithm. However, polynomial rings $(\mathbf Z/n\mathbf Z)[x]$ corresponding to arbitrary modulus $n$ are not even integral domains.

The fact that division with remainder holds means that polynomial roots always correspond to one factor of degree one.

???+ abstract "Root"
    A **root** of a polynomial $f(x)$ is an element $\xi\in F$ such that $f(\xi)=0$.

???+ note "Theorem"
    For a polynomial $f(x)$ over a field $F$ and an element $\xi\in F$, $\xi$ is a root of $f(x)$ if and only if $f(x)$ has a factor of degree one $(x-\xi)$.

??? note "Proof"
    Division with remainder shows there exist $q(x),r(x)$ such that $f(x)=q(x)(x-\xi)+r(x)$ and $\deg r(x)<\deg(x-\xi)=1$. Thus, $r(x)$ is a constant polynomial or zero polynomial, let $r(x)=c$, then we must have $f(x)=q(x)(x-\xi)+c$. Substituting $x=\xi$, hence $0=a(\xi)=c$, i.e., $f(x)=q(x)(x-\xi)$.

The concept of roots can be generalized to multiple roots.

???+ abstract "Multiple Root"
    If a polynomial $f(x)$ has a factor $(x-\xi)^k$, and $(x-\xi)^{k+1}$ does not divide $f(x)$, then $\xi$ is called a **$k$-fold root** of $f(x)$. If $k>1$, then $\xi$ is called a **multiple root** of $f(x)$; if $k=1$, then $\xi$ is called a **simple root** of $f(x)$.

???+ note "Theorem"
    If a polynomial $f(x)$ over a field $F$ has (possibly repeated) roots $\xi_1,\cdots,\xi_k$, then it must have the factor $(x-\xi_1)\cdots(x-\xi_k)$. Furthermore, if $f(x)$ over field $F$ has degree $n$, then it has at most $n$ roots (counting multiplicities).

??? note "Proof"
    Note that $F[x]$ is a unique factorization domain.

Although unique factorization holds for polynomials over fields, there is no general method to determine whether a given polynomial is reducible. Relatively small degrees are easier. For example, all linear polynomials are irreducible polynomials. On special fields where all irreducible polynomials are linear, such fields are called [algebraically closed fields](./field-theory.md#algebraically-closed-fields). On such fields, all polynomials that are not identically equal to non-zero constants have roots, so any polynomial of degree greater than one can be further factored. An example of such a field is the complex field $\mathbf C$. On the real field $\mathbf R$, there exist irreducible polynomials of degree two; on the rational field $\mathbf Q$, the structure of irreducible polynomials is more complex. The [Field Theory](./field-theory.md) page has more discussions on polynomials over rational fields and finite fields.

The above conclusions are all about polynomials over fields. For polynomials over more general integral domains, they can often be transformed to such cases.

Now consider the polynomial ring $R[x]$ over a unique factorization domain $R$. Directly performing operations in $R[x]$, because coefficients often cannot be divided, many operations are limited. Consider extending $R$ to its fraction field $F$, then consider factoring the polynomial $f(x)$ in $R[x]$ in $F[x]$. Since $F[x]$ is known to be a unique factorization domain, we can reverse the factorization in $F[x]$ to get the factorization in $R[x]$. Fortunately, such an approach is always possible.

???+ note "Gauss's Lemma"
    For a unique factorization domain $R$ and its fraction field $F$, if $f(x)\in R[x]$ and in $F[x]$ we have $f(x)=A(x)B(x)$, then there exist $s,t\in F$ such that $a(x)=sA(x)\in R[x]$, $b(x)=tB(x)\in R[x]$, and $f(x)=a(x)b(x)$. Therefore, if $f(x)$ is irreducible in $R[x]$, then it is also irreducible in $F[x]$.

??? note "Proof"
    Let $f(x)\in R[x]$ be reducible in $F[x]$, and $f(x)=A(x)B(x)$. Let $r_a$ and $r_b$ be the least common multiples of the denominators of all coefficients in $A(x)$ and $B(x)$ respectively. Then $\tilde a(x)=r_aA(x)$ and $\tilde b(x)=r_bB(x)$ are both polynomials over $R$. Let $r=r_ar_b$, then $rf(x)=\tilde a(x)\tilde b(x)$. If $r$ is an invertible element in $R$, we can take the factorization $f(x)=(r^{-1}\tilde a(x))\tilde b(x)$, which obviously satisfies the requirements of the lemma.
    
    Otherwise, if $r$ contains an irreducible element factor $p$, we need to prove that we can cancel this factor on both sides, and ensure all coefficients remain in the integral domain $R$. Note that $p$ must also be a prime element, so $(p)$ is a prime ideal. Taking both sides modulo $p$, we get the polynomial $0=\bar a(x)\bar b(x)$ over $(R/(p))[x]$, where $\bar a$ and $\bar b$ are the polynomials after taking modulo $p$. Since $R/(p)$ is an integral domain, $(R/(p))[x]$ is also an integral domain, so we can assume $\bar a(x)=0$. This shows that all coefficients of $\tilde a(x)$ are divisible by $p$. Therefore, we can directly cancel the factor $p$ on both sides.
    
    According to the definition of unique factorization domain, $r$ has only finitely many such irreducible element factors, so after canceling them finitely many times, we transform to the case where $r$ is an invertible element in $R$. The lemma is thus proved.

???+ note "Corollary"
    For a unique factorization domain $R$ and its fraction field $F$, if $f(x)\in R[x]$ and all non-zero coefficients of $f(x)$ are coprime (i.e., the greatest common divisor is the unity element of $R$), then $f(x)$ is irreducible in $R[x]$ if and only if $f(x)$ is irreducible in $F[x]$.

That is, irreducible elements in the polynomial ring $\mathbf Z[x]$ are all irreducible in $\mathbf Q[x]$. An effective method to determine whether a polynomial with integer coefficients is irreducible is the Eisenstein criterion. According to Gauss's lemma, it also provides a method to determine whether polynomials with rational coefficients are irreducible.

???+ note "Eisenstein Criterion"
    Let $f(x)=a_0+a_1x+\cdots+a_{n-1}x^{n-1}+a_nx^n$ be a polynomial with integer coefficients of degree $n$. If there exists a prime $p$ such that $p\mid a_i$ for all $i=0,1,\cdots,n-1$, and $p$ does not divide $a_n$, and $p^2$ does not divide $a_0$, then the polynomial $f(x)$ is irreducible over the rational field $\mathbf Q$. If $\gcd(a_0,a_1,\cdots,a_n)=1$, then the polynomial $f(x)$ is also irreducible over the integer ring $\mathbf Z$.

??? note "Proof"
    Using Gauss's lemma, if $f(x)$ is reducible over the rational field $\mathbf Q$, then it is also reducible over the integer ring $\mathbf Z$. Let $f(x)=b(x)c(x)$ be its factorization in $\mathbf Z[x]$. Taking both sides modulo prime $p$, we get the factorization $\overline{f}(x)=\overline{b}(x)\overline{c}(x)$ in $\mathbf F_p[x]$. But the condition of the theorem shows that $\overline{f}(x)=x^n$, so there must exist integers $m$ such that $\overline b(x)=x^m$ and $\overline c(x)=x^{n-m}$, where $0<m<n$. Therefore, the constant terms $b_0$ and $c_0$ of $b(x)$ and $c(x)$ are both multiples of $p$. Hence, the constant term $a_0=b_0c_0$ of $f(x)$ must be a multiple of $p^2$. This contradicts the given condition.

??? example "Examples"
    1.  The polynomial $x^3-2$ is irreducible in $\mathbf Q[x]$. Applying the Eisenstein criterion with $p=2$ suffices.
    2.  The polynomial $x^4+1$ is irreducible in $\mathbf Q[x]$. Otherwise, $(x+1)^4+1=x^4+4x^3+6x^2+4x+2$ would also be reducible. However, applying the Eisenstein criterion with $p=2$ shows that the latter is not irreducible.

For a unique factorization domain $R$, since the polynomial ring over its fraction field $F$ is a unique factorization domain, and Gauss's lemma shows that factorizations in $F[x]$ and $R[x]$ correspond to each other, $R[x]$ is also a unique factorization domain. Therefore, we have:

???+ note "Theorem"
    The polynomial ring $R[x]$ is a unique factorization domain if and only if $R$ is a unique factorization domain.

Here, $\mathbf Z[x]$ provides an example that a unique factorization domain is not necessarily a principal ideal domain. For example, in $\mathbf Z[x]$, $(2,x)$ is not a principal ideal.

There are many ways to extend polynomial rings. For example, for a polynomial ring $R[x]$ over an integral domain $R$, we can extend it to its fraction field, denoted $R(x)$. This fraction field is often called the **field of rational fractions**, where the basic form of elements is $\dfrac{f(x)}{g(x)}$, where both $f(x)$ and $g(x)$ are polynomials.

### Multivariate Polynomial Rings

Polynomial rings can be extended to cases with multiple indeterminates. For a commutative unital ring $R$, we can define the polynomial ring over $R$, i.e., the univariate polynomial ring $R[x]$. Then we can define the polynomial ring over $R[x]$, i.e., $R[x][y]$, which can be seen as the bivariate polynomial ring $R[x,y]$ over $R$. From this, we can inductively define the $k$-variate polynomial ring $R[x_1,\cdots,x_k]$ over $R$. When $R$ is an integral domain, any multivariate polynomial ring over $R$ is an integral domain; similarly, the property of unique factorization domains can also be transferred to any multivariate polynomial ring.

### Formal Power Series Rings

We can also consider cases where formal sums can have arbitrarily many non-zero coefficients. A **formal power series** over a commutative unital ring $R$ is defined as

$$
\sum_{k=0}^\infty a_kx^k=a_0+a_1x+a_2x^2+\cdots.
$$

Addition and multiplication between power series can be defined in the same way as for polynomial rings $R[x]$. Moreover, formal power series also form a ring, denoted $R[[x]]$. Here, formal power series do not consider convergence or divergence, because each formal power series is actually just its coefficient sequence, and no more topological structure is given.

The structure of formal power series rings is interesting. In polynomial rings over integral domains, invertible elements can only be constants. However, in formal power series rings, we can have

$$
(1-x)^{-1}=\sum_{k=0}^\infty x^k=1+x+x^2+\cdots.
$$

This phenomenon is universal. As long as the constant term $a_0$ of a formal power series is an invertible element in $R$, then $\sum_{k=0}^\infty a_kx^k$ is also invertible. This is because if we set

$$
\left(\sum_{k=0}^\infty a_kx^k\right)\left(\sum_{k=0}^\infty b_kx^k\right)=1,
$$

then by listing the equations that coefficients need to satisfy, we can recursively find expressions for $b_k$ that involve only the inverse of $a_0$.

Various operations can be defined on formal power series rings, such as inversion, division, compositional inverse, formal derivatives, elementary functions, etc. See [Introduction to Polynomial Techniques](../poly/intro.md) for details.

### Formal Laurent Series Rings

Formal power series rings can be further extended to allow terms with negative degrees. A **formal Laurent series** over a commutative unital ring $R$ is defined as

$$
\sum_{k=N}^\infty a_kx^k,
$$

where $N\in\mathbf Z$. Therefore, formal Laurent series can have finitely many negative degree terms. Extending the previous addition and multiplication to formal Laurent series gives the formal Laurent series ring, denoted $R((x))$. If $F$ is a field, then $F((x))$ is also a field.

Formal Laurent series rings have applications in [Lagrange Inversion](../poly/lagrange-inversion.md).

## Chinese Remainder Theorem

Related reading: [Chinese Remainder Theorem](../number-theory/crt.md)

In number theory, the Chinese remainder theorem is often used to solve systems of number theory equations. For general commutative unital rings, we can also establish the Chinese remainder theorem. Each congruence equation is equivalent to specifying the image of the unknown in some quotient ring. Therefore, the Chinese remainder theorem in commutative unital rings is equivalent to determining elements in the ring through these images in quotient rings.

This discussion can be transformed into formal language. For a non-zero commutative unital ring $R$ and its ideals $I_1,\cdots,I_n$, consider the ring homomorphism $\varphi:R\rightarrow R/I_1\times \cdots R/I_n$, which maps $r$ to $(r+I_1,\cdots,r+I_n)$. Here, $r+I_i$ is a coset, and $\times$ denotes the direct product of rings:

???+ abstract "Direct Product"
    For rings $R_1$ and $R_2$, the direct product of their additive groups $R_1\times R_2$ can define multiplication by multiplying each component separately, then $R_1\times R_2$ becomes a ring, called the **direct product** of rings $R_1$ and $R_2$, still denoted $R_1\times R_2$.

The kernel of the homomorphism $\varphi$ is $\ker\varphi=I_1\cap\cdots\cap I_n$. The question the Chinese remainder theorem needs to answer is under what conditions this map is surjective.

In the case of number theory, the theorem requires these moduli to be coprime. This condition can be generalized to the case of ring theory.

???+ abstract "Coprime"
    Let a ring $R$ have ideals $I$ and $J$. If $I+J=R$, then $I$ and $J$ are called **comaximal**.

For the case of unital rings, if we consider principal ideals $(a)$ and $(b)$, this condition is equivalent to the existence of $x,y\in R$ such that $ax+by=1$, which is similar to Bézout's theorem when integers are coprime. Using this definition, we can completely analogize the case of integer rings to establish the **Chinese Remainder Theorem** for commutative unital rings.

???+ note "Chinese Remainder Theorem"
    Let a non-zero commutative unital ring $R$ have ideals $I_1,\cdots,I_n$. If they are pairwise comaximal, then the ring homomorphism $\varphi$ defined above is surjective, its kernel equals the product of these ideals $\ker\varphi=I_1\cap\cdots\cap I_n=I_1\cdots I_n$, therefore
    
    $$
    R/(I_1\cdots I_n)=R/(I_1\cap\cdots\cap I_n)\cong R/I_1\times\cdots\times R/I_n.
    $$

??? note "Proof"
    The theorem is rich in content, but the conclusions that still need proof are only two: $\varphi$ is surjective and $I_1\cap\cdots\cap I_n=I_1\cdots I_n$. The key is to make good use of the comaximal condition.
    
    First prove the case $n=2$. Since ideals $I_1$ and $I_2$ are comaximal, i.e., $I_1+I_2=R$, the unity element $1$ in $R$ can be written in the form $a_1+a_2$ where $a_i\in I_i$. Since $a_1\in I_1$ and $a_1=1-a_2\in 1+I_2$, we have $\varphi(a_1)=(I_1,1+I_2)$; similarly, $\varphi(a_2)=(1+I_1,I_2)$. Therefore, $(\varphi(a_2),\varphi(a_1))$ plays a role similar to a "basis" in vector spaces. Therefore, for any image $(r_1+I_1,r_2+I_2)$, we can find the preimage $r_1a_2+r_2a_1$ under the homomorphism $\varphi$. This shows that $\varphi$ is surjective.
    
    We also need to prove $I_1\cap I_2=I_1I_2$. For general rings, $I_1I_2\subseteq I_1\cap I_2$ always holds, and the key is the other direction. For any $r\in I_1\cap I_2$, we have $r=r(a_1+a_2)=ra_1+ra_2\in I_1I_2$. Therefore, $I_1\cap I_2\subseteq I_1I_2$ also holds. This is what we needed to prove.
    
    For the case $n>2$, we need to use mathematical induction. The key step in induction is to prove that for pairwise comaximal ideals $I_1,\cdots,I_n$, the ideal $I_1$ and $I_2\cdots I_n$ are always comaximal. Since $I_1$ is comaximal with each of $I_2,\cdots,I_n$, for each $i=2,\cdots,n$, there exist $a_i\in I_1$ and $b_i\in I_i$ such that $1=a_i+b_i$ holds. Therefore, $1=(a_2+b_2)\cdots(a_n+b_n)$ holds. So, $1\in (b_2\cdots b_n)+I_1\subseteq I_1+(I_2\cdots I_n)$. This shows that the ideal $I_1$ and $I_2\cdots I_n$ are comaximal.

### Application: Lagrange Interpolation Formula

Related reading: [Lagrange Interpolation](../numerical/interp.md#lagrange-interpolation-method), [Fast Polynomial Interpolation](../poly/multipoint-eval-interpolation.md#fast-interpolation-of-polynomials)

The interpolation problem is: given a series of points $\{(x_i,y_i)\}_{i=1}^n$, find a polynomial $f(x)$ over field $F$ such that $f(x_i)=y_i$ holds for all $i=1,\cdots,n$. Of course, we assume all $x_i$ are distinct. The Lagrange interpolation formula gives the general solution to such problems.

For a polynomial $f(x)$ over field $F$, the condition $f(x_i)=y_i$ is equivalent to $x_i$ being a root of $f(x)-y_i$, hence equivalent to $(x-x_i)\mid(f(x)-y_i)$, i.e., $f(x)\equiv y_i\pmod{x-x_i}$. Therefore, the interpolation problem is equivalent to solving the system of congruence equations

$$
\begin{cases}
f(x)\equiv y_1&\pmod{x-x_1},\\
f(x)\equiv y_2&\pmod{x-x_2},\\
\cdots\\
f(x)\equiv y_n&\pmod{x-x_n}.
\end{cases}
$$

These linear polynomials $\{x-x_i\}_{i=1}^n$ are pairwise coprime. According to the Chinese remainder theorem, the solution should have the form

$$
f(x)=\sum_{i=1}^ny_iM_i(x),
$$

where $M_i(x)=m_i(x)\prod_{j\neq i}(x-x_j)$ and $M_i(x)\equiv 1\pmod{x-x_i}$. According to the equivalence derived earlier, this is equivalent to $M_i(x_i)=1$, i.e.,

$$
m_i(x_i)\prod_{j\neq i}(x_i-x_j) = 1.
$$

We can take $m_i(x)$ to be a constant polynomial, i.e.,

$$
m_i(x) = \frac{1}{\prod_{j\neq i}(x_i-x_j)}.
$$

From this, we get the Lagrange interpolation formula

$$
f(x)=\sum_{i=1}^ny_i\frac{\prod_{j\neq i}(x-x_j)}{\prod_{j\neq i}(x_i-x_j)}.
$$

In general, extending this method can also derive the [Hermite interpolation formula](https://en.wikipedia.org/wiki/Hermite_interpolation), which allows restricting the values of certain derivatives of polynomials at points.

### Application: Multiplicative Group of Integer Congruence Classes

Related reading: [Primitive Roots](../number-theory/primitive-root.md), [Fundamental Theorem of Finitely Generated Abelian Groups](./group-theory.md#classification-theorem)

As an application of the Chinese remainder theorem and related content of group theory, this section discusses the structure of the multiplicative group of integers modulo $n$. This section omits the overline notation for congruence classes.

The **multiplicative group of integers modulo $n$** refers to $(\mathbf Z/n\mathbf Z)^\times$, i.e., the multiplicative group of invertible elements in the quotient ring $\mathbf Z/n\mathbf Z$ (also called the group of units). The order of the group $(\mathbf Z/n\mathbf Z)^\times$ is $\varphi(n)$, because the necessary and sufficient condition for invertibility is coprime with $n$. Here, $\varphi(n)$ is the [Euler totient function](../number-theory/euler-totient.md). Moreover, the group $(\mathbf Z/n\mathbf Z)^\times$ is always an abelian group.

According to the fundamental theorem of arithmetic, modulus $n$ can be factored into the product of powers of distinct primes:

$$
n=p_1^{\alpha_1}\cdots p_s^{\alpha_s}.
$$

It is easy to verify that for ideals in the integer ring, the condition that ideals are comaximal is equivalent to the condition that their generators are coprime. Therefore, applying the Chinese remainder theorem gives

$$

\mathbf Z/n\mathbf Z\cong\mathbf Z/p_1^{\alpha_1}\mathbf Z\times\cdots\times\mathbf Z/p_s^{\alpha_s}\mathbf Z.
$$

Ring isomorphism implies corresponding multiplicative structures are also isomorphic, so

$$

(\mathbf Z/n\mathbf Z)^\times\cong(\mathbf Z/p_1^{\alpha_1}\mathbf Z)^\times\times\cdots\times(\mathbf Z/p_s^{\alpha_s}\mathbf Z)^\times.
$$

This shows that $\varphi(n)=\varphi(p_1^{\alpha_1})\cdots\varphi(p_n^{\alpha_n})$, i.e., the Euler function is a multiplicative function.

Therefore, to study the general case, we only need to consider the case where the modulus is a prime power $p^k$. For the case of prime powers, we need to consider separately the two cases of $p=2$ and $p$ being an odd prime:

-   For the case $p=2$, direct verification shows $(\mathbf Z/2\mathbf Z)^\times\cong C_1$ and $(\mathbf Z/4\mathbf Z)^\times\cong C_2$. For $k\ge3$, we have $(\mathbf Z/2^k\mathbf Z)^\times\cong C_2\times C_{2^{k-2}}$.

    ??? note "Proof"
        Using the binomial theorem, direct calculation shows
        
        $$
        \begin{aligned}
        5^{2^{k-2}}=(1+2^2)^{2^{k-2}}&\equiv 1\pmod {2^k},\\
        5^{2^{k-3}}=(1+2^2)^{2^{k-3}}&\equiv 1+2^{k-1}\pmod {2^k}.
        \end{aligned}
        $$
        
        So, $5$ is an element of order $2^{k-2}$ in $(\mathbf Z/2^k\mathbf Z)^\times$. At the same time, $-1$ and $5^{2^{k-3}}$ are two different elements orders of two, so $-1\notin\langle 5\rangle$. Therefore, $\langle-1\rangle$ and $\langle 5\rangle$ have trivial intersection, so by the second isomorphism theorem
        
        $$
        (\mathbf Z/2^k\mathbf Z)^\times\cong\langle-1\rangle\times\langle 5\rangle\cong C_2\times C_{2^{k-2}}.
        $$
-   For the case where $p$ is an odd prime, it can be proven that $(\mathbf Z/p^k\mathbf Z)^\times$ is isomorphic to the cyclic group $C_{\varphi(p^k)}$.

    ??? note "Proof"
        To prove $(\mathbf Z/p^k\mathbf Z)^\times$ is a cyclic group, using the fundamental theorem of finite abelian groups, we only need to prove that all its Sylow $q$-subgroups are cyclic. First, for the Sylow $p$-subgroup, direct calculation shows
        
        $$
        \begin{aligned}
        (1+p)^{p^{k-1}} &\equiv 1\pmod{p^k},\\
        (1+p)^{p^{k-2}} &\equiv 1+p^{k-1}\pmod{p^k}.
        \end{aligned}
        $$
        
        So, $(1+p)$ is an element of order $p^{k-1}$. That is, the unique Sylow $p$-subgroup of $(\mathbf Z/p^k\mathbf Z)^\times$ is the cyclic group $\langle 1+p\rangle$.
        
        For other Sylow $q$-subgroups ($q\neq p$), we can transform them to the case $k=1$ through group homomorphisms. Consider the group homomorphism $\varphi:(\mathbf Z/p^k\mathbf Z)^\times\rightarrow(\mathbf Z/p\mathbf Z)^\times$, which maps the coset $r+p^k\mathbf Z$ to the coset $r+p\mathbf Z$. The size of this kernel is $p^{k-1}$, so when $\varphi$ is restricted to the Sylow $q$-subgroup ($q\neq p$) of $(\mathbf Z/p^k\mathbf Z)^\times$, the restricted homomorphism has trivial kernel, so this Sylow $q$-subgroup is isomorphic to the image, i.e., the Sylow $q$-subgroup of $(\mathbf Z/p\mathbf Z)^\times$. Therefore, we only need to prove that the Sylow $q$-subgroups of $(\mathbf Z/p\mathbf Z)^\times$ are all cyclic.
        
        Finally, prove that all Sylow $q$-subgroups of $(\mathbf Z/p\mathbf Z)^\times$ are cyclic. Since $(\mathbf Z/p\mathbf Z)^\times$ is a finite abelian group, we can decompose it by invariant factors as
        
        $$
        C_{n_1}\times\cdots\times C_{n_r}.
        $$
        
        Here, $n_1\mid n_2\mid \cdots\mid n_r$. So each direct product factor has $n_1$ elements whose orders divide $n_1$. If $r>1$, then there are strictly more than $n_1$ elements satisfying $x^{n_1}=1$. But $\mathbf Z/p\mathbf Z$ is a field, and polynomials of degree $n_1$ over a field have at most $n_1$ roots, so $r=1$. That is, $(\mathbf Z/p\mathbf Z)^\times\cong C_{p-1}$.
        
        This proves $(\mathbf Z/p^k\mathbf Z)^\times\cong C_{p^{k-1}}\times C_{p-1}=C_{\varphi(p^{k})}$.

The structure of the multiplicative group for general moduli is also determined. From existing results, the multiplicative group of integers modulo $n$ is a cyclic group if and only if the modulus $n$ is

$$
1,2,4,p^k,2p^k
$$

where $p$ is an odd prime; otherwise, the multiplicative group of integers modulo $n$ always has a subgroup $C_2\times C_2$ and cannot be a cyclic group. When the multiplicative group is a cyclic group, the generator of the multiplicative group is called the **primitive root** of that modulus. Therefore, the theorem here gives exactly the necessary and sufficient conditions for the existence of primitive roots.

Of course, the analysis of the multiplicative group structure contains more information than just the conditions for the existence of primitive roots. It clearly reflects the orders of different elements in the multiplicative group. Elements $x$ in the group $(\mathbf Z/n\mathbf Z)^\times$ satisfying $x^k=1$, i.e., solutions to the congruence equation $x^k\equiv 1\pmod n$, are called **$k$-th roots of unity modulo $n$**; elements with order exactly equal to $k$ are called **primitive $k$-th roots of unity modulo $n$**. Using the structure of the multiplicative group, the existence and number of these roots can all be precisely calculated. Finally, the least common multiple of all orders of elements in $(\mathbf Z/n\mathbf Z)^\times$, i.e., the smallest positive integer $k$ such that $x^k=1$ holds for all $x\in (\mathbf Z/n\mathbf Z)^\times$, expressed as a function of $n$, is the [Carmichael function](../number-theory/primitive-root.md#carmichael-function). Its series of properties can all be obtained from the structure of the multiplicative group.

## References

-   Dummitt, D.S. and Foote, R.M. (2004) Abstract Algebra. 3rd Edition, John Wiley & Sons, Inc.
-   [Quadratic integer - Wikipedia](https://en.wikipedia.org/wiki/Quadratic_integer)
-   [Formal power series - Wikipedia](https://en.wikipedia.org/wiki/Formal_power_series)
-   [Multiplicative group of integers modulo $n$ - Wikipedia](https://en.wikipedia.org/wiki/Multiplicative_group_of_integers_modulo_n)

[^ideal-history]: <https://en.wikipedia.org/wiki/Ideal_(ring_theory)#History>

[^simple-ring]: Consistent with the case of groups, such rings are called **simple rings**. Commutative simple rings can only be fields, and the case of non-commutative simple rings is much more complex.

[^gcd-domain]: Integral domains where greatest common divisors exist are called [GCD domains](https://en.wikipedia.org/wiki/GCD_domain).

[^ring-theory-history]: A brief history of ring theory can be found [here](https://mathshistory.st-andrews.ac.uk/HistTopics/Ring_theory/).
