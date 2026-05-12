Prerequisites: [Basic Concepts of Abstract Algebra](./basic.md), [Group Theory](./group-theory.md), [Ring Theory](./ring-theory.md)

## Introduction

**Field theory** is the theory of fields.

The field theory involved in this article primarily focuses on field extensions. A field is an algebraic structure closed under addition, subtraction, multiplication, and division. In competitive programming, we often need to take modulo of a prime number $p$, which is equivalent to performing operations in the finite field $\mathbf F_p$. Similar to the case of the real field $\mathbf R$, some problems become easier to solve in larger fields (namely the complex field $\mathbf C$). A common example is using [Fast Fourier Transform](../poly/fft.md) to accelerate the multiplication of polynomials with real coefficients. Similar operations can be performed on finite fields. Since most readers are relatively unfamiliar with extensions of finite fields, understanding the general theory of field extensions is beneficial. At the end of this article, some algorithmic applications requiring field extensions are given, and briefly discusses extensions of integer rings that may be needed in some applications.

Closely related to field theory is **Galois theory**. It connects field extensions with their automorphism groups, allowing one to understand the properties of field extensions through group theory tools. Although this theory is often the core of related algebra courses, it is far from the content of competitive programming, so this article does not provide excessive introduction. Interested readers should consult specialized textbooks.

???+ info "Notation"
    When there is no ambiguity, this article may omit the multiplication symbol for rings and fields, and will write the ring $(R,+,\cdot)$ as the ring $R$, and the field $(F,+,\cdot)$ as the field $F$. The additive identity of a ring or field is called the zero element, and the multiplicative identity is called the unity element. Moreover, $p$ in this article is always a prime, and $q$ is always a prime power, which can be written as $p^n$, where $n$ is a positive integer.

## Field Extensions

Similar to the cases of groups and rings, we can establish the concepts of subfields and field homomorphisms.

???+ abstract "Subfield"
    For a field $F$, if its subring $E$ is also a field, then $E$ is called a **subfield** of $F$.

Here, regardless of how rings and subrings handle the unity element, the subfield $E$ must contain the unity element of $F$[^subfield-one].

???+ abstract "Field Homomorphism"
    A ring homomorphism $\varphi:F\rightarrow E$ from a field $F$ to a field $E$ is also called a **field homomorphism** from $F$ to $E$.

??? info "Field Homomorphisms and Unity Elements"
    If, unlike the definition in this article, ring homomorphisms require the unity element to map to the unity element, then field homomorphisms naturally require the unity element to map to the unity element. Otherwise, the unity element may also map to the zero element.

Since fields only have trivial ideals, a field homomorphism either maps the entire field to the zero element or must be an embedding. This shows that the discussion of field homomorphisms can be transformed into the discussion of subfields.

In the case of fields, the smaller field is often more familiar, so we usually examine larger fields with respect to subfields. This leads to the concept of field extensions.

???+ abstract "Field Extension"
    For fields $F$ and $E$, if $F$ is a subfield of $E$, then $E$ is called an **extension** of $F$, also called an **extension field**, denoted $E/F$.

???+ info "Notation for Field Extensions"
    Although the notation is the same, the concept of field extensions has no relation to quotient rings and should not be confused.

???+ example "Examples"
    The complex field $\mathbf C$ is an extension of the real field $\mathbf R$, and $\mathbf R$ is an extension of the rational field $\mathbf Q$.

### Degree of Field Extensions

For a field extension $E/F$, $E$ is always a [linear space](../linear-algebra/vector-space.md) over $F$. The dimension of this linear space is the degree of the field extension.

???+ abstract "Degree of Field Extension"
    The **degree** of a field extension $E/F$ is the dimension of $E$ considered as a linear space over $F$, namely $\dim_F(E)$, denoted $[E:F]$. If the degree is finite, the extension is called a **finite extension**; otherwise, it is called an **infinite extension**.

???+ example "Examples"
    The degree of the extension $\mathbf C/\mathbf R$ is $[\mathbf C:\mathbf R]=2$, so it is a finite extension. $\mathbf R/\mathbf Q$ is an infinite extension.

The degree of field extensions satisfies the multiplication formula.

???+ note "Theorem"
    Let $F\subseteq K\subseteq E$ all be fields, then the degrees satisfy $[E:F]=[E:K][K:F]$.

??? note "Proof"
    For infinite degree, this is obvious; otherwise, if $\{\alpha_i\}$ is a basis of $E$ as a linear space over $K$, and $\{\beta_j\}$ is a basis of $K$ as a linear space over $F$, then one can verify that $\{\alpha_i\beta_j\}$ is a basis of $E$ as a linear space over $F$.

The discussion in this article primarily focuses on finite field extensions.

### Characteristic of a Field

A natural starting point for studying field extensions is the smallest subfield containing the unity element of $F$, which is also called the **prime subfield** of $F$.

The structure of the prime subfield is uniquely determined by the properties of the unity element of the field. The characteristic of a field summarizes such properties.

???+ abstract "Characteristic of a Field"
    The **characteristic** of a field $F$ is the smallest positive integer $n$ such that $n\cdot 1=0$; if such $n$ does not exist, the characteristic of $F$ is $0$. Here, $n\cdot 1$ means the sum of $n$ unity elements $1$. If the characteristic of $F$ is not $0$, then $F$ is said to have **finite characteristic**.

The characteristic of a field can be understood through ring homomorphisms. The integer ring $\mathbf Z$ is the closed structure obtained starting from $0$ and $1$ by repeatedly applying addition, subtraction, and multiplication. It can be considered as a kind of "prototype", and all rings containing the unity element should "inherit" some structure of the integer ring[^initial-object-ring]. Therefore, for a field $F$, we can consider the ring homomorphism $\varphi:\mathbf Z\rightarrow F$ with $\varphi(1)=1$. Such a ring homomorphism is uniquely determined, mapping $n\in\mathbf N_+$ to $n\cdot 1$, the sum of $n$ unity elements $1$. The image $\varphi(\mathbf Z)$ embedded in $F$ necessarily contains the unity, is commutative, and has no zero divisors, so it is an integral domain. Hence, the kernel $\ker\varphi$ must be a prime ideal. The prime ideals of $\mathbf Z$ can only be of the form $(n)$, where $n=0$ or $n$ is a prime. The $n$ obtained is the characteristic of the field.

The characteristic determines the structure of the prime subfield:

1.  When the characteristic is $0$, $\varphi$ is injective, and $\mathbf Z$ is embedded in $F$. The field of rational numbers $\mathbf Q$ as the smallest field containing $\mathbf Z$ can also be embedded in $F$, and it is the prime subfield of $F$;
2.  When the characteristic is a prime $p$, the image $\mathbf Z/p\mathbf Z$ is embedded in $F$. At this point, $\mathbf Z/p\mathbf Z$ is already a field, denoted $\mathbf F_p$, and it is the prime subfield of $F$.

These discussions actually prove the following conclusion:

???+ note "Theorem"
    The characteristic of a field $F$ can only be $0$ or a prime $p$. The prime subfield of a field with characteristic $0$ is $\mathbf Q$, and the prime subfield of a field with characteristic $p$ is $\mathbf F_p$.

The $\mathbf Q$ and $\mathbf F_p$ in the theorem are also called **prime fields**, that is, fields whose only subfield is themselves. Finite fields necessarily have finite characteristic, because fields with characteristic $0$ contain at least the subfield $\mathbf Q$.

Fields with finite characteristic and those with characteristic zero often have different properties. For example, fields with finite characteristic have the following properties:

???+ note "Theorem"
    Let the characteristic of $F$ be $p$, then:
    
    1.  In the additive group of $F$, all non-zero elements have order $p$, that is, $px=0$ for all $x\in F$;
    2.  The "freshman's dream": for all $x,y\in F$, $(x+y)^p=x^p+y^p$. Furthermore, the map $x\mapsto x^p$ is an injective endomorphism of $F$, called the **Frobenius endomorphism**.

??? note "Proof"
    For the first property, note that $px=(p1)x=0x=0$. For the second property, note that in the binomial expansion of $(x+y)^p$, all other coefficients besides $x^p$ and $y^p$ are multiples of $p$, so by the first property, $(x+y)^p=x^p+y^p$. To verify that $x\mapsto x^p$ is an endomorphism, we only need to verify $(xy)^p=x^py^p$, which holds because field multiplication is commutative. Finally, a ring homomorphism between fields mapping the unity element to the unity element must be injective.

Of course, for finite fields, the Frobenius endomorphism is also surjective, and thus is a field automorphism.

### Simple Extensions

Similar to extending the real field to the complex field, many extensions can be completed by adding additional elements to the field and specifying their algebraic properties. In general, to avoid complications from specifying algebraic properties, we can consider adding elements from $E\setminus F$ to $F$ in the extension $E/F$, where the rules for operations between these additional elements and elements of $F$ are already determined in the larger field $E$.

???+ abstract "Extension Generated by a Subset"
    Let $E/F$ be a field extension and $S\subseteq E$. The **extension generated by $S$ over $F$** is the smallest subfield of $E$ containing both $F$ and $S$, denoted $F(S)$.

The simplest case is when the set $S$ has few elements.

???+ abstract "Finitely Generated Extension"
    Let $E/F$ be a field extension. If there exists a finite set $S=\{\alpha_1,\cdots,\alpha_n\}\subseteq E$ such that $E=F(S)$, then $E$ is called a **finitely generated extension** of $F$, also denoted $F(\alpha_1,\cdots,\alpha_n)$.

???+ abstract "Simple Extension"
    Let $E/F$ be a field extension. If there exists $\alpha\in E$ such that $E=F(\alpha)$, then $E$ is called a **simple extension** of $F$. The element $\alpha$ is called a **primitive element** of this simple extension.

???+ example "Examples"
    These examples are all obtained by adding elements of $\mathbf C$ to $\mathbf Q$:
    
    1.  For a square-free integer $D\neq 0,1$, the quadratic field $\mathbf Q(\sqrt D)$ is obtained by adding $\sqrt D\in\mathbf C\setminus\mathbf Q$ to $\mathbf Q$. It is a simple extension with degree $2$, because $\{1,\sqrt D\}$ forms a basis.
    2.  The field $\mathbf Q(\sqrt 2,\sqrt 3)$ is obtained by adding $\sqrt 2$ and $\sqrt 3$ to $\mathbf Q$. Of course, $\mathbf Q(\sqrt 2,\sqrt 3)=\mathbf Q(\sqrt 2)(\sqrt 3)=\mathbf Q(\sqrt 3)(\sqrt 2)$, meaning the final extension is independent of the order and method of adding elements. This is also a simple extension because $\mathbf Q(\sqrt 2,\sqrt 3)=\mathbf Q(\sqrt 2+\sqrt 3)$. Its degree is $4$, because $\{1,\sqrt 2,\sqrt 3,\sqrt 6\}$ forms a basis.
    3.  The field $\mathbf Q(\pi)$ is also a simple extension, where $\pi$ is the circumference ratio. It is an infinite extension because $\mathbf Q[\pi]\subseteq \mathbf Q(\pi)$ already has a basis $\{1,\pi,\pi^2,\cdots\}$.
    4.  The field $\mathbf Q(\pi,\mathrm e)$ is a finitely generated extension but not a simple extension. Here, $\pi$ is the circumference ratio, and $\mathrm e$ is the base of the natural logarithm.

These examples show that the properties of simple extensions can vary greatly. This depends on the nature of the added elements.

### Algebraic Extensions

To analyze all possible cases of adding elements to a field, we can, following the earlier discussion on the characteristic of a field, consider ring homomorphisms from the polynomial ring $F[x]$ to the extension $E/F$. Here, $F[x]$ serves the same role as the integer ring $\mathbf Z$ discussed earlier: it is the "prototype" of the structure formed by adding an indeterminate $x$ to the field $F$ and closing under addition, subtraction, and multiplication[^polynomial-universal].

Let $\varphi:F[x]\rightarrow E$ be a ring homomorphism such that $\varphi$ restricted to $F$ is the identity map, and $\varphi(x)=\alpha$, that is, mapping the indeterminate to some element $\alpha$ in the extension $E$. At this time, since the image $\varphi(F[x])=F[\alpha]$ is necessarily an integral domain, the kernel $\ker\varphi$ must be a prime ideal of the polynomial ring $F[x]$. The polynomial ring over a field is a principal ideal domain, so it must have the form $(f(x))$, where $f(x)=0$ or $f(x)$ is an irreducible element of $F[x]$. The discussion is as follows:

1.  When $\ker\varphi=\{0\}$, the polynomial ring $F[x]$ is embedded into $E$, and its image $F[\alpha]$ is an integral domain. Therefore, the smallest field in $E$ containing both $F$ and $\alpha$ is the fraction field of $F[\alpha]$, namely $F(\alpha)$. This notation can be interpreted either as substituting $\alpha$ for the indeterminate in the rational function field $F(x)$, or as the simple extension of $F$ generated by $\alpha$; these two interpretations yield the same result in this context;

2.  When $\ker\varphi=(f(x))$ and $f(x)$ is irreducible, then $\varphi(f(x))=f(\alpha)=0$, that is, $\alpha\in E$ is a root of the polynomial $f(x)$ over $F$. Since $F$ is a field, let $f(x)$ be a monic polynomial. At this time, the image of $\varphi$ is the field $F(\alpha)$, so we have

    $$
    F[x]/(f(x))\cong F(\alpha).
    $$

    This can be divided into two cases:
    
    1.  If $f(x)$ is a linear polynomial, that is, $f(x)=x-\alpha$, then $\alpha\in F$, so the extension $F(\alpha)=F$ is trivial;
    2.  In other cases, $f(x)$ is an irreducible polynomial of degree greater than one, and $\alpha\in E\setminus F$. At this time, $F[\alpha]$ already contains $F$ and $\alpha$, so it is $F(\alpha)$, the extension of $F$ generated by $\alpha$, and $F(\alpha)\supset F$ is nontrivial.

This discussion leads to the following definitions:

???+ abstract "Algebraic and Transcendental Elements"
    For an extension $E/F$, if an element $\alpha\in E$ is a root of some non-zero polynomial $f(x)$ over $F$, then $\alpha$ is called an **algebraic element** over $F$; otherwise, $\alpha$ is called a **transcendental element** over $F$.

???+ abstract "Minimal Polynomial"
    For an algebraic element $\alpha$ over a field $F$, the monic polynomial $f(x)$ of smallest degree having $\alpha$ as a root is called its **minimal polynomial**.

The minimal polynomial here is exactly the irreducible polynomial $f(x)$ from the earlier analysis. Of course, it can also be directly proven that minimal polynomials are all irreducible. The minimality of $f(x)$ means that any polynomial over $F$ having $\alpha$ as a root must contain $f(x)$ as a factor.

???+ example "Examples"
    1.  $\sqrt 2$ is algebraic over $\mathbf Q$, with minimal polynomial $x^2-2$.
    2.  $\sqrt 2$ is algebraic over $\mathbf R$, with minimal polynomial $x-\sqrt 2$.
    3.  $\pi$ is transcendental over $\mathbf Q$.
    4.  In general, algebraic elements over $\mathbf Q$ are called **algebraic numbers**, while transcendental elements are called **transcendental numbers**. Particularly, if the minimal polynomial of an algebraic number is a monic polynomial, it is called an **algebraic integer**. All algebraic integers in an algebraic extension form a ring. For example, the algebraic integers in the quadratic field $\mathbf Q(\sqrt{D})$ form the quadratic integer ring $\mathbf Z[\omega]$. See [Quadratic Integer Rings](./ring-theory.md#examples-quadratic-integer-ring) for the meaning of this notation.

???+ abstract "Algebraic and Transcendental Extensions"
    For an extension $E/F$, if all elements of $E$ are algebraic over $F$, then $E$ is called an **algebraic extension** of $F$; otherwise, $E$ is called a **transcendental extension** of $F$.

The results of simple extensions can be divided into two categories based on the nature of the added element. When the added element is transcendental, the simple extension is always isomorphic to the rational function field. At this time, there is no possibility for further simplification. However, when the added element is algebraic, the simple extension is actually $F[\alpha]$, that is, the result of directly replacing the indeterminate $x$ in the polynomial ring $F[x]$ with $\alpha$. From an elementary perspective, compared to transcendental elements, elements in the extension field in the case of algebraic simple extensions can have no denominators; this means that the process similar to "rationalizing denominators" in elementary arithmetic is always feasible in algebraic simple extensions. Since the extension fields involved in competitive programming are primarily simple algebraic extensions, the next section will discuss their computation in more detail.

The importance of simple algebraic extensions is also reflected in the following theorem:

???+ note "Theorem"
    A field extension is finite if and only if it is a finitely generated algebraic extension.

??? note "Proof"
    Let $F$ be a field, and $E=F(\alpha_1,\cdots,\alpha_n)$ be a finitely generated algebraic extension over $F$, where each $\alpha_i$ is algebraic over $F$. Let $E_i=F(\alpha_1,\cdots,\alpha_i)$, then $E_0=F$ and $E_n=E$. Note that $\alpha_i$ must be algebraic over $E_{i-1}$, because the minimal polynomial of $\alpha_i$ over $F$ is also a polynomial over $E_{i-1}$; moreover, the degree of the minimal polynomial of $\alpha_i$ over $E_{i-1}$ cannot exceed that over $F$. Therefore, $[E_i:E_{i-1}]$ is necessarily finite, and by the multiplication formula for degrees of field extensions, $[E:F]=\prod_{i=1}^n[E_i:E_{i-1}]$ is also finite. Conversely, starting from $E_0=F$, for each constructed $E_i$, we can choose an element $\alpha_{i+1}\in E\setminus E_i$ to add to $E_i$, obtaining $E_{i+1}=E_i(\alpha_{i+1})$, until $E_n=E$. Since the degree of the extension keeps decreasing, this process must terminate in a finite number of steps. Therefore, finite extensions are necessarily finitely generated algebraic extensions.

This means that to understand the properties of finite extensions, one only needs to understand simple algebraic extensions. Since finite extensions can always be obtained through finitely many simple algebraic extensions.

### Structure and Computation of Simple Algebraic Extensions

In this section, let $F$ be a number field, $E$ its extension field, and $\alpha\in E\setminus F$ be algebraic over $F$. Let the minimal polynomial of $\alpha$ be $f(x)$, and let $f(x)$ be an $n$-degree monic polynomial, that is,

$$
f(x)=x^n+a_{n-1}x^{n-1}+\cdots+a_1x+a_0,
$$

where $a_0,a_1,\cdots,a_{n-1}\in F$ and $f(x)$ is irreducible over $F$.

The isomorphism $F(\alpha)\cong F[x]/(f(x))$ indicates that the operations in the extension field $F(\alpha)$ are just computations of polynomials modulo $f(x)$. According to polynomial division with remainder, we only need to consider all congruence classes of polynomials with degree less than $n=\deg f(x)$. For these polynomials, a natural basis is $\{1,\alpha,\cdots,\alpha^{n-1}\}$. Therefore, we have the following theorem:

???+ note "Theorem"
    Under the assumptions of this section, the extension field $F(\alpha)$ can be written as
    
    $$
    F(\alpha)=\{\lambda(\alpha)=\lambda_0+\lambda_1\alpha+\cdots+\lambda_{n-1}\alpha^{n-1}:\lambda_0,\lambda_1,\cdots,\lambda_{n-1}\in F}.
    $$
    
    Here, $\lambda(x)$ ranges over all polynomials of degree less than $n$. Therefore, the degree of extension $[F(\alpha):F]=n$, which is the degree of the minimal polynomial of $\alpha$. In the extension field, the addition of elements $\lambda(\alpha)$ and $\mu(\alpha)$ is just polynomial addition, that is, adding coefficients at corresponding positions; the multiplication of $\lambda(\alpha)$ and $\mu(\alpha)$ can be written as $\rho(\alpha)$, where $\rho(x)$ is the remainder of $\lambda(x)\mu(x)$ divided by $f(x)$.

Of course, as a field, we can also compute division in $F(\alpha)$. According to the multiplication process described in the theorem, this is equivalent to solving a [linear congruence equation](../number-theory/linear-equation.md) over polynomial rings. Analogous to the integer case, to compute the quotient $\lambda(\alpha)/\mu(\alpha)$, we can first determine the multiplicative inverse of $\mu(\alpha)$, then multiply by $\lambda(\alpha)$. To compute the multiplicative inverse of $\mu(\alpha)$, we just need to solve the congruence equation $\mu(x)\xi(x)\equiv 1\pmod{f(x)}$. This can be achieved through the extended Euclidean algorithm.

Below, we understand the details of computation through specific examples.

???+ example "Examples"
    Consider the extension field $\mathbf Q(\alpha)$, where $\alpha$ is a root of the equation $x^3-2x-2=0$. To compute
    
    $$
    \frac{1+\alpha}{1+\alpha+\alpha^2}
    $$
    
    .
    
    The first step is to compute the inverse of $1+\alpha+\alpha^2$, that is, to solve the congruence equation
    
    $$
    (x^2+x+1)\xi(x)+(x^3-2x-2)\nu(x)=1
    $$
    
    . Apply the extended Euclidean algorithm to this. First perform Euclidean division:
    
    $$
    \begin{aligned}
    x^3-2x-2 &= (x-1)(x^2+x+1)+(-2x-1),\\
    x^2+x+1 &= \left(-\frac12x-\frac14\right)(-2x-1)+\frac34,\\
    -2x-1 &= \left(-\frac{8}{3}x-\frac{4}{3}\right)\frac{3}{4}.
    \end{aligned}
    $$
    
    Then compute the coefficients in the congruence equation:
    
    $$
    \begin{aligned}
    \frac{3}{4}
    &=(x^2+x+1)+\left(\frac12x+\frac14\right)(-2x-1)\\
    &=(x^2+x+1)+\left(\frac12x+\frac14\right)\left((x^3-2x-2)-(x-1)(x^2+x+1)\right)\\
    &=\left(-\frac12x^2+\frac14x+\frac54\right)(x^2+x+1)+\left(\frac12x+\frac14\right)(x^3-2x-2).
    \end{aligned}
    $$
    
    Therefore, the solution is
    
    $$
    \xi(x)=-\frac23x^2+\frac13x+\frac53,\ \nu(x)=\frac23x+\frac13.
    $$
    
    This shows that the inverse of $1+\alpha+\alpha^2$ is
    
    $$
    -\frac23\alpha^2+\frac13\alpha+\frac53.
    $$
    
    The second step is to compute the product of the inverse and $1+\alpha$:
    
    $$
    \begin{aligned}
    (1+\alpha)\left(-\frac23\alpha^2+\frac13\alpha+\frac53\right)
    &=-\frac23\alpha^3-\frac13\alpha^2+2\alpha+\frac53\\
    &=-\frac23(2\alpha+2)-\frac13\alpha^2+2\alpha+\frac53\\
    &=-\frac13\alpha^2+\frac23\alpha+\frac13.
    \end{aligned}
    $$
    
    This is the final answer.

In the example, only the condition that $\alpha$ is a root of the equation is used, without specifying which specific root it is. The polynomial $x^3-2x-2=0$ has one real root and a pair of conjugate complex roots in the complex field $\mathbf C$. The extension fields obtained by adding any of them to the rational field $\mathbf Q$ are all isomorphic. That is, these three distinct roots are not different from an algebraic perspective.

In general, for an irreducible polynomial $f(x)$ over a field $F$, in the extension field there are different roots $\alpha\neq\beta$. When performing simple extensions on the field $F$ separately, these roots exhibit the same algebraic properties. These roots are called **conjugates** of each other. The usual notion of conjugates over the complex field is a special case of this concept for the field extension $\mathbf C/\mathbf R$.

???+ example "Examples"
    Consider the extension field $\mathbf F_2(\alpha)$, where $\alpha$ is a root of the equation $x^2+x+1=0$. In general, for $a+b\alpha$ and $c+d\alpha$, the arithmetic rules are
    
    $$
    \begin{aligned}
    (a+b\alpha)+(c+d\alpha)&=(a+c)+(b+d)\alpha,\\
    (a+b\alpha)(c+d\alpha)&=ac+(ad+bc)\alpha+bd\alpha^2\\
    &=(ac+bd)+(ad+bc+bd)\alpha.
    \end{aligned}
    $$
    
    This provides arithmetic rules similar to those over the complex field. Most readers should be unfamiliar with such roots $\alpha$, but this does not prevent performing operations on elements in such a field. In fact, $[\mathbf F_2(\alpha):\mathbf F_2]=2$, so as a linear space, $|\mathbf F_2(\alpha)|=4$, that is, the finite field of size $4$ is obtained. Later, we will see that all finite fields are constructed in this way.

For small-scale computations, operations modulo the monic polynomial $f(x)$ can often be performed by substituting

$$
x^n=-a_{n-1}x^{n-1}-\cdots-a_1x-a_0
$$

to reduce the degree of the target polynomial. Moreover, for low-degree extensions, the arithmetic rules for coefficients can often be computed directly, using an implementation similar to complex number classes without computing modulo each time.

As an example of simple algebraic extensions, refer to the [reference implementation](#reference-implementation) below.

The algorithms described here can only handle extensions of low degree in practice, which is sufficient for most applications in competitive programming. For cases where the degree becomes a bottleneck, appropriate polynomial techniques ([Fast Fourier Transform](../poly/fft.md), [Number-Theoretic Transform](../poly/ntt.md), [Polynomial Fast Remainder](../poly/elementary-func.md#polynomial-division-and-modulo), [Polynomial Euclidean Algorithm](../poly/intro.md#factorization-and-euclidean) etc.) should be used to accelerate computations.

### Splitting Fields

The structure of simple algebraic extensions has been discussed in detail above. However, such extensions are often insufficient:

???+ example "Examples"
    Consider the extension $\mathbf Q(\sqrt[3]{2})/\mathbf Q$. The algebraic element $\sqrt[3]{2}$ has minimal polynomial $x^3-2$ over $\mathbf Q$. In the complex field $\mathbf C$, the polynomial $x^3-2$ has three roots: $\sqrt[3]{2},\sqrt[3]{2}\omega,\sqrt[3]{2}\omega^2$, where $\omega=\mathrm{e}^{2\pi\mathrm{i}/3}$ is a primitive third root of unity. Although $\mathbf Q(\sqrt[3]{2})\cong\mathbf Q(\sqrt[3]{2}\omega)\cong\mathbf Q(\sqrt[3]{2}\omega^2)$, $\mathbf Q(\sqrt[3]{2})$ does not contain the other two roots, making operations like $\sqrt[3]{2}+\sqrt[3]{2}\omega$ impossible. To completely examine these three roots, further extension of $\mathbf Q(\sqrt[3]{2})$ is needed, extending to $\mathbf Q(\sqrt[3]{2},\sqrt[3]{2}\omega,\sqrt[3]{2}\omega^2)$.
    
    As shown earlier, to make such an extension, we can perform simple extensions on elements one by one. It should be noted that the minimal polynomial of $\sqrt[3]{2}\omega$ over $\mathbf Q$ and over $\mathbf Q(\sqrt[3]{2})$ is not the same: the former is $x^3-2\in\mathbf Q[x]$, while the latter is $x^2+\sqrt[3]{2}x+\sqrt[3]{4}\in \mathbf Q(\sqrt[3]{2})[x]$, because
    
    $$
    x^3-2 = (x-\sqrt[3]{2})(x^2+\sqrt[3]{2}x+\sqrt[3]{4}).
    $$
    
    The original minimal polynomial factorizes into linear factors after the field extension, so the degree of the minimal polynomial of the remaining roots is lower than that over the original field. The process of continuously extending the field is the process of continuously "splitting" polynomials. Therefore, when performing each simple extension, the minimal polynomial needs to be redetermined.

Adding all roots of a polynomial to the field gives the splitting field of the polynomial.

???+ abstract "Split"
    Let $F$ be a field. If a polynomial $f(x)$ in $F[x]$ can be factored into a product of linear factors, then $f(x)$ is said to **split** in $F$.

???+ abstract "Splitting Field"
    For a polynomial $f(x)$ over a field $F$, if an extension $E/F$ satisfies that $f(x)$ splits in $E$ but not in any proper subfield of $E$, then $E$ is called the **splitting field** of $f(x)$.

It can be proven that, like simple extensions, the splitting field of a given polynomial is uniquely determined up to isomorphism, independent of the specific construction method. Splitting fields are always finite extensions.

???+ abstract "Normal Extension"
    For an algebraic extension $E/F$, if for all $\alpha\in E$, the minimal polynomial of $\alpha$ splits in $E$, then $E$ is called a **normal extension** of $F$.

Normal extensions play a fundamental role in Galois theory.

### Algebraically Closed Fields

Most extension concepts discussed earlier should, in principle, be carried out inside a field larger than the extension. Although for simple extensions, extensions can be constructed without relying on larger fields through polynomial rings, there is no such method for general cases. For the rational field $\mathbf Q$ and real field $\mathbf R$, we can always assume that algebraic extensions are contained within the complex field $\mathbf C$. For finite fields, there is no similar known field. In fact, for all fields, there exists an algebraic closure, so that all algebraic extensions over a field can be assumed to be within the algebraic closure. This completely resolves the issue.

???+ abstract "Algebraic Closure"
    For a field $F$, if $\overline F$ is an algebraic extension of $F$ and all $f(x)\in F[x]$ split in $\overline F$, then $\overline F$ is called the **algebraic closure** of $F$.

The algebraic closure is a normal extension over the field. Its construction method is basically to add all possible polynomial roots to the field. And like splitting fields, the algebraic closure of a field is also unique up to isomorphism.

???+ note "Theorem"
    Any field $F$ has an algebraic closure.

??? note "Proof"
    The difficulty of the proof comes from set theory. Here we cite a proof by Artin.
    
    The first part of the proof starts from $F$, constructing an extension $K_1/F$ such that all polynomials over $F$ have at least one root in $K_1$. For a field $F$, consider the multivariate polynomial ring[^multi-poly-ring] $R=F[\cdots,x_f,\cdots]$, where the indeterminates $x_f$ are indexed by all monic polynomials over $F$. At this time, the ideal generated by all $f(x_f)$ is denoted $I$. First, $I\neq R$, so a maximal ideal $M\supseteq I$ exists. Otherwise, if $1\in I$, there must exist finitely many monic polynomials $f_i$ over $F$ and corresponding elements $g_i$ in $R$ such that $g_1f_1(x_{f_1})+\cdots+g_kf_k(x_{f_k})=1$ holds. Let $F(\alpha_1,\cdots,\alpha_k)$ be the algebraic extension obtained by adding the roots $\alpha_i$ of $f_i(x)$ to $F$. Then, substituting $\alpha_i$ for $x_{f_i}$ in the above identity, and substituting $0$ for all other indeterminates $x_f$ appearing in $g_i$, we get the equation $0=1$ over $F(\alpha_1,\cdots,\alpha_k)$, which is a contradiction. Therefore, $I\neq R$, and the construction of the maximal ideal $M$ is valid. At this time, the quotient ring $R/M$ is a field, denoted $K_1$, and any monic polynomial $f(x)$ over $F$ has a root $\overline{x_f}$ in $K_1$.
    
    The second part of the proof obtains an algebraic closure $K$ containing $F$ (definition below) through induction. Repeating the above construction, based on the field $K_i$, we can construct $K_{i+1}$ such that all polynomials of $K_i$ have at least one root in $K_{i+1}$. Moreover, $K_i$ naturally embeds into $K_{i+1}$, so we can define their union $K=\bigcup_{i=1}^\infty K_i$. It is easy to verify that this is also a field, and all coefficients of any polynomial over $K$ are necessarily contained in some $K_i$, so one of its roots necessarily appears in $K_{i+1}\subseteq K$. This shows that all polynomials over $K$ have at least one root in $K$, so $K$ is an algebraically closed field.
    
    Finally, let $\overline F$ be the set of all algebraic elements over $F$ in $K$. It is obviously a field; because for any $\alpha,\beta\in\overline F$, we have $\alpha\pm\beta,\alpha\beta,\alpha/\beta\in F(\alpha,\beta)\subseteq\overline F$. It is also an algebraic extension of $F$, because its elements are all algebraic over $F$. For a polynomial $f(x)$ over $F$, all its roots are algebraic over $F$, so they are also in $\overline F$, and therefore can be factored into products of linear factors. This shows that $\overline F$ is the algebraic closure of $F$ over $F$.

???+ example "Examples"
    1.  The algebraic closure of the real field $\mathbf R$ is the complex field $\mathbf C$.
    2.  The algebraic closure of the rational field $\mathbf Q$ is the set of all algebraic numbers (i.e., algebraic elements in the field extension $\mathbf C/\mathbf Q$), denoted $\overline{\mathbf Q}$.

All algebraic extensions of algebraic closures are trivial. Such fields are called algebraically closed fields.

???+ abstract "Algebraically Closed Field"
    If every non-constant polynomial $f(x)$ over a field $F$ has at least one root $\alpha\in F$, then $F$ is called an **algebraically closed field**.

In fact, it has the following equivalent definitions:

???+ note "Theorem"
    For a field $F$, the following properties are all equivalent:
    
    1.  $F$ is algebraically closed;
    2.  All polynomials $f(x)$ over $F$ split;
    3.  The only irreducible polynomials over $F$ are linear polynomials;
    4.  $F$ has no non-trivial algebraic extensions;
    5.  $F$ has no non-trivial finite extensions;
    6.  $F$ is the algebraic closure of some field.

??? note "Proof"
    The equivalence of the first five properties is obvious from the definitions. For the sixth, an algebraically closed field is obviously its own algebraic closure because it has no non-trivial algebraic extensions; conversely, to prove that the algebraic closure of $F$ is algebraically closed. Let $\overline F$ be the algebraic closure of $F$, and $f(x)$ a polynomial over $\overline F$. Let $\alpha$ be a root of $f(x)$ in the splitting field of $f(x)$, and let the set of non-zero coefficients of $f(x)$ be $S\subseteq\overline F$. Then, since $F(S)(\alpha)=F(S\cup\{\alpha\})$ is a finite extension, $\alpha$ is also algebraic over $F$, so according to the definition of algebraic closure, the minimal polynomial of $\alpha$ over $F$ splits in $\overline F$, hence $\alpha\in\overline F$. This shows that any polynomial over $\overline F$ has at least one root.

Finally, the [Fundamental Theorem of Algebra](../poly/fundamental.md) [^fundamental-algebra] shows that $\mathbf C$ is algebraically closed. Irreducible polynomials over $\mathbf R$ are at most quadratic, or equivalently, the largest field obtainable through algebraic extensions is $\mathbf C$.

### Separable Extensions

The concept of splitting fields guarantees that for any polynomial over any field, there is an extension field containing all its roots, and the splitting field precisely gives such the smallest extension field. The properties of polynomials are closely related to the properties of their splitting fields. However, if one hopes to study the properties of polynomials through their splitting fields, the first problem to face is that the splitting field of a polynomial is unrelated to the multiplicities of the polynomial's roots. Therefore, if possible, we should consider some kind of "simplest representation" of the polynomial. Inspired by this, we call polynomials that have no multiple roots in the algebraic closure of the field separable polynomials.

???+ abstract "Separable Polynomial"
    For a polynomial $f(x)$ over a field $F$, if $f(x)$ has no multiple roots in the algebraic closure $\overline F$ of $F$, that is, when it factors into a product of linear factors there are no repeated factors, then $f(x)$ is called **separable**.

Since we always need to extend to the algebraic closure of $F$ to discuss separable polynomials, the determination of separable polynomials is actually independent of the choice of field $F$. However, because the coefficients of polynomials are in $F$, we should provide a method to determine whether a polynomial is separable over $F$ without explicitly constructing its extension field.

Readers familiar with analysis know that multiple roots of polynomial functions can be determined through their derivatives: multiple roots of polynomial functions are also roots of their derivatives. Although polynomials and polynomial functions are not the same concept, the method for determining multiple roots of polynomial functions can be analogously applied to polynomials. The derivative of a polynomial can be defined formally as follows:

???+ abstract "Formal Derivative"
    The **(formal) derivative** of a polynomial over $F$
    
    $$
    f(x)=a_0+a_1x+a_2x^2+\cdots+a_{n-1}x^{n-1}+a_nx^n=\sum_{i=0}^na_ix^i
    $$
    
    , denoted $Df(x)$, is defined as the polynomial
    
    $$
    Df(x)=a_1+2a_2x+\cdots+(n-1)a_{n-1}x^{n-1}+na_nx^{n-1}=\sum_{i=1}^nia_ix^{i-1}.
    $$

This definition applies to all polynomials over any field and does not depend on any topological structure. The derivative operator $D$ here just maps one polynomial to another. Moreover, by comparing coefficients, one can verify that the usual derivative rules, such as $D(f(x)g(x))=(Df(x))g(x)+f(x)(Dg(x))$, still hold for formal derivatives.

Furthermore, to check whether the polynomial $f(x)$ and its derivative $Df(x)$ have the same roots in the splitting field, we can not explicitly construct this splitting field, but determine it by their greatest common divisor; this is because polynomial roots always appear in its minimal polynomial, and repeated roots mean the corresponding minimal polynomial factors are also repeated. Therefore, we have the following criterion for multiple roots:

???+ note "Theorem"
    For a polynomial $f(x)$ over a field $F$, if $f(x)$ has a multiple root $\alpha$, then the derivative $Df(x)$ also has the same root $\alpha$. Furthermore, $f(x)$ is separable if and only if $f(x)$ and its derivative $Df(x)$ are coprime, that is, $\gcd(f(x),Df(x))=1$.

??? note "Proof"
    First, because Euclidean division still holds in extension fields, the results of the Euclidean algorithm are independent of the choice of extension field, so we only need to discuss their common factors in the splitting field. Thus, assuming $\alpha$ is a root of $f(x)$ with multiplicity $k>1$, in the splitting field we have $f(x)=(x-\alpha)^kg(x)$, so its derivative $Df(x)=k(x-\alpha)^{k-1}g(x)+(x-\alpha)^kDg(x)$ necessarily also has root $\alpha$. Conversely, if $f(x)$ and $Df(x)$ both have root $\alpha$, then for the splitting $f(x)=(x-\alpha)g(x)$, we have $Df(x)=(x-\alpha)Dg(x)+g(x)$, so $\alpha$ is also a root of $g(x)$, hence $\alpha$ is a multiple root of $f(x)$. This proves the first part of the theorem. Furthermore, $f(x)$ has a multiple root $\alpha$ if and only if $x-\alpha$ is a factor of $\gcd(f(x),Df(x))$. So $f(x)$ is inseparable is equivalent to $\deg\gcd(f(x),Df(x))\geq 1$.

Polynomials over fields can always be factored into products of irreducible polynomials. Because (up to associates) different irreducible polynomials always have different roots, repeated roots naturally link to repeated polynomial factors. Then, if there are no repeated irreducible factors in the factorization, can we determine that the polynomial is separable? In other words, are all irreducible polynomials separable? Unfortunately, in general, we cannot get a positive answer. The problem arises with fields of finite characteristic.

For an irreducible polynomial $f(x)$ over a field $F$, $\gcd(f(x),Df(x))$ as a factor of $f(x)$ can only be either $1$ or $f(x)$. In the first case, $f(x)$ is naturally separable; the problem is in the second case. However, since the definition of the derivative already guarantees $Df(x)=0$ or $\deg Df(x)<\deg f(x)$, that $f(x)$ becomes a factor of $Df(x)$ can only mean $Df(x)=0$. This is possible in fields of finite characteristic.

For a field $F$ of characteristic $p$, if $Df(x)=0$, then all non-zero coefficients of the polynomial can only appear in terms whose degrees are multiples of exactly $p$, that is, the polynomial $f(x)$ can be written as

$$
f(x)=a_0+a_px^p+a_{2p}x^{2p}+\cdots+a_{(k-1)p}x^{(k-1)p}+a_{kp}x^{kp}.
$$

If there really exists an irreducible polynomial $f(x)$ over $F$ that is both irreducible and inseparable, it can only have this form. However, if all elements in $F$ always have $p$-th roots, that is, for each coefficient $a_{jp}$ there exists $b_j\in F$ such that $a_{jp}$ can be written as $b_j^p$, then by the Frobenius endomorphism, we always have

$$
\begin{aligned}
f(x)&=a_0+a_px^p+a_{2p}x^{2p}+\cdots+a_{(k-1)p}x^{(k-1)p}+a_{kp}x^{kp}\\
&=b_0^p+b_1^px^p+b_2^px^{2p}+\cdots+b_{k-1}^px^{(k-1)p}+b_k^px^{kp}\\
&=\left(b_0+b_1x+b_2x+\cdots+b_{k-1}x^{k-1}+b_kx^k\right)^p.
\end{aligned}
$$

Therefore, such irreducible polynomials do not exist on such fields $F$. Thus, on such fields, all irreducible polynomials are separable. Such fields are called perfect fields.

???+ abstract "Perfect Field"
    If all irreducible polynomials over a field $F$ are separable, then $F$ is called a **perfect field**.

For perfect fields, the concept of separable polynomials is equivalent to the concept of polynomials with no square factors in their factorization.

???+ note "Theorem"
    Let $F$ be a perfect field. Then a polynomial over $F$ is separable if and only if it can be written as a product of (up to associates) distinct irreducible polynomials.

The discussion in this section is actually sufficient to provide a method for removing repeated factors in polynomials, which is a key step in polynomial factorization algorithms. But this is beyond the scope of this article. Interested readers can refer to related materials at the end of this article.

This discussion actually also gives a characterization of perfect fields:

???+ note "Theorem"
    A field $F$ is perfect if and only if either the characteristic of $F$ is zero, or the characteristic of $F$ is $p$ and every element $x\in F$ has a $p$-th root (that is, the Frobenius endomorphism is also an automorphism).

The rational field $\mathbf Q$ and the finite fields $\mathbf F_q$ discussed below are all perfect fields.

For fields that are not perfect fields, there do exist inseparable irreducible polynomials.

??? example "Examples"
    Consider the polynomial $x^2-t$ over the rational function field $\mathbf F_2(t)$ of $\mathbf F_2$. Since $\mathbf F_2(t)$ is the fraction field of the unique factorization domain $\mathbf F_2[t]$, and $t$ is a prime element in $\mathbf F_2[t]$, applying the Eisenstein criterion to the prime element $t$ shows that $x^2-t$ is irreducible in $\mathbf F_2[t]$, hence it is also irreducible in $\mathbf F_2(t)$. However, its derivative is $0$, so $x^2-t$ is not separable. In fact, in the extension field $\mathbf F_2(t)(\sqrt t)$, it has the double root $\sqrt t$.

Finally, we return to the discussion of field extensions.

???+ abstract "Separable Extension"
    For an algebraic extension $E/F$, if the minimal polynomial of every $\alpha\in E$ is a separable polynomial, then $E$ is called a **separable extension** of $F$.

All algebraic extensions over perfect fields are separable extensions. This can also serve as an equivalent definition of perfect fields.

If an algebraic extension is both a normal extension and a separable extension, it is also called a Galois extension. In Galois extensions, no irreducible polynomial has multiple roots, and the number of roots is always exactly equal to the degree of the polynomial. Thus, permutations of roots can fully reflect the properties of field extensions and polynomials. Such extensions provide the cornerstone for establishing Galois theory. Interested readers can refer to related materials at the end of this article.

## Cyclotomic Fields

As a simple example of field extensions, this section discusses cyclotomic fields. Another simple example of field extensions is [Quadratic Fields](../number-theory/quadratic.md).

### Group of Roots of Unity

In the complex field $\mathbf C$, the roots of the polynomial $x^n=1$ are called **$n$-th roots of unity**. Let $\zeta_n=\mathrm{e}^{2\pi\mathrm{i}/n}$. Then all $n$-th roots of unity are the set $C_n=\{\zeta_n^k:k\in\mathbf Z\}$. Under multiplication, $C_n$ forms a cyclic group of order $n$, which can be denoted $\langle\zeta_n\rangle$, and is called the group of $n$-th roots of unity. The generators of the group $C_n$, that is, elements with order exactly $n$, are called **primitive $n$-th roots of unity**. The set of $n$-th primitive roots of unity is $P_n={\zeta_n^k:k\in\mathbf Z,k\perp n}$, which has exactly $\varphi(n)$ elements; here, $\varphi(n)$ is the [Euler function](../number-theory/euler-totient.md). Classifying the elements of the root of unity group $C_n$ by their orders gives the following decomposition:

$$
C_n=\bigcup_{d|n}P_d.
$$

Counting elements on both sides gives the identity $n=\sum_{d\mid n}\varphi(d)$.

### Cyclotomic Fields

The cyclotomic field is the extension field obtained by adding roots of unity to the rational field.

???+ abstract "Cyclotomic Field"
    The extension field $\mathbf Q(\zeta_n)$ obtained by adding the $n$-th complex root of unity $\zeta_n=\mathrm{e}^{2\pi\mathrm{i}/n}$ to the rational field $\mathbf Q$ is called the **$n$-th cyclotomic field**.

Since all $n$-th roots of unity form a cyclic group $\langle\zeta_n\rangle$ under multiplication, the cyclotomic field $\mathbf Q(\zeta_n)$ also includes all these $n$-th roots of unity. In fact, $\mathbf Q(\zeta_n)$ is precisely the splitting field of the polynomial $x^n-1$ over $\mathbf Q$.

???+ note "Theorem"
    The cyclotomic field $\mathbf Q(\zeta_n)$ is the splitting field of the polynomial $x^n-1$ over $\mathbf Q$.

??? note "Proof"
    Let $F$ be the splitting field of $x^n-1$ over $\mathbf Q$. Since $\mathbf Q(\zeta_n)$ contains all complex roots of $x^n-1$, we have $F\subseteq\mathbf Q(\zeta_n)$. Conversely, since $\zeta_n\in F$, we must have $\mathbf Q(\zeta_n)=F$. This shows that $F=\mathbf Q(\zeta_n)$.

This can serve as an equivalent definition of cyclotomic fields. In fact, adding any $n$-th primitive root of unity to the cyclotomic field yields $\mathbf Q(\zeta_n)$.

### Cyclotomic Polynomials

The cyclotomic field $\mathbf Q(\zeta_n)$ is a simple algebraic extension over $\mathbf Q$. According to the analysis above, such fields are always isomorphic to the quotient ring of some polynomial ring. To obtain such an isomorphism, we need to analyze the minimal polynomial $f(x)$ of $\zeta_n$. Since $\zeta_n$ is a root of $x^n-1$, $f(x)$ must be a factor of $x^n-1$. This shows that we need to examine the factorization of $x^n-1$ in $\mathbf Q[x]$. According to Gauss's Lemma, it can be factored in $\mathbf Z[x]$ as a product of several irreducible monic polynomials.

Since $\mathbf Q(\zeta_n)$ is a splitting field, $x^n-1$ factors as:

$$
x^n-1=\prod_{\zeta\in C_n}(x-\zeta)=\prod_{d\mid n}\prod_{\zeta\in P_d}(x-\zeta).
$$

Because roots of unity with different orders have different algebraic properties, they cannot be roots of the same irreducible polynomial. Therefore, to examine the minimal polynomial of $\zeta_n$, we only need to consider the factor

$$
\Phi_n(x)=\prod_{\zeta\in P_n}(x-\zeta)
$$

in the above decomposition. The minimal polynomial of $\zeta_n$ must be a factor of $\Phi_n(x)$. Moreover, $\Phi_n(x)$ defined this way has the following properties:

???+ note "Theorem"
    $\Phi_n(x)$ is a monic polynomial with integer coefficients, and is irreducible in $\mathbf Z[x]$.

??? note "Proof"
    By definition, $\Phi_n(x)$ is obviously a monic polynomial. First, prove $\Phi_n(x)\in\mathbf Z[x]$. According to Gauss's Lemma, $x^n-1$ has the same factorization in $\mathbf Z[x]$ and $\mathbf Q[x]$, and each factor is a monic polynomial with integer coefficients. In this factorization, each factor $f(x)$ is irreducible over $\mathbf Q[x]$ and splits in $\mathbf Q(\zeta_n)$; all its roots are $n$-th roots of unity and necessarily have the same order, so these roots all belong to some $P_d$ rather than existing in different $P_d$'s. This means that each $f(x)$ is a factor of some $\Phi_d(x)$. Therefore, $\Phi_n(x)$ can be written as a product of several monic polynomials with integer coefficients, so it is also a monic polynomial with integer coefficients.
    
    Next, prove $\Phi_n(x)$ is irreducible in $\mathbf Z[x]$. Suppose it factors as $f(x)g(x)$ with $f(x)$ irreducible in $\mathbf Z[x]$. We only need to prove $f(x)$ contains all $n$-th primitive roots of unity. That is, let $\zeta$ be a root of $f(x)$, and we need to prove that for all $k\perp n$, $\zeta^k$ is also a root of $f(x)$; since $k$ can always be decomposed into prime factors, we only need to prove that for all primes $p\perp n$, $\zeta^p$ is a root of $f(x)$. Assume the contrary, $\zeta^p$ is a root of $g(x)$. Therefore, $\zeta$ is a common root of $f(x)$ and $g(x^p)$ in $\mathbf Z[x]$. Because $f(x)$ is the minimal polynomial of $\zeta$ over $\mathbf Q$, $f(x)$ must divide $g(x^p)$; that is, there exists $h(x)\in\mathbf Z[x]$ such that $g(x^p)=f(x)h(x)$. Taking modulo $p$ on both sides of the equation gives $\overline{g}(x^p)=\overline{f}(x)\overline{h}(x)$ over $\mathbf F_p[x]$. Using the Frobenius endomorphism, $\overline{g}(x)^p=\overline{f}(x)\overline{h}(x)$. Since $\mathbf F_p[x]$ is also a unique factorization domain, $\overline{g}(x)$ and $\overline{f}(x)$ must have a non-trivial common factor, so $x^n-\overline 1=\overline{f}(x)\overline{g}(x)$ is inseparable over $\mathbf F_p$. However, since $p\perp n$, its formal derivative $nx^{n-1}$ is coprime with itself, which contradicts its inseparability. Therefore, $\zeta^p$ must be a root of $f(x)$, so $f(x)$ contains all $n$-th primitive roots of unity, and it is $\Phi_n(x)$.

This shows that it is the minimal polynomial of $\zeta_n$, also called the **$n$-th cyclotomic polynomial**. The definition above shows that it has $\varphi(n)$ complex roots, and these complex roots are precisely all $n$-th primitive roots of unity; here, $\varphi(n)$ is the [Euler function](../number-theory/euler-totient.md). This also shows that $\mathbf Q(\zeta_n)/\mathbf Q$ is an extension of degree $\varphi(n)$.

The ring of algebraic integers in the cyclotomic field $\mathbf Q(\zeta_n)$ is $\mathbf Z[\zeta_n]$. Additionally, when $\varphi(n)=2$, the cyclotomic field is a [quadratic extension](../number-theory/quadratic.md). Specifically, $\mathbf Q(\zeta_4)$ is the quadratic field $\mathbf Q(\sqrt{-1})$; $\mathbf Q(\zeta_3)$ and $\mathbf Q(\zeta_6)$ are the same, both being the quadratic field $\mathbf Q(\sqrt{-3})$.

Using cyclotomic polynomials, $x^n-1$ has a unique factorization in $\mathbf Z[x]$

$$
x^n-1=\prod_{d\mid n}\Phi_d(x).
$$

Therefore, $(x^d-1)\mid(x^n-1)$ if and only if $d\mid n$. Moreover, applying [Möbius inversion](../number-theory/mobius.md) to this formula gives

$$
\Phi_d(x)=\prod_{d\mid n}(x^d-1)^{\mu(n/d)}.
$$

Using this expression, we can recursively compute all cyclotomic polynomials. Here are examples of the first few cyclotomic polynomials for readers to become familiar with.

???+ example "Cyclotomic Polynomials"
    The first 10 cyclotomic polynomials are as follows:
    
    $$
    \begin{aligned}
    \Phi_1(x) &= x-1,\\
    \Phi_2(x) &= x+1,\\
    \Phi_3(x) &= x^2+x+1,\\
    \Phi_4(x) &= x^2+1,\\
    \Phi_5(x) &= x^4+x^3+x^2+x+1,\\
    \Phi_6(x) &= x^2-x+1,\\
    \Phi_7(x) &= x^6+x^5+x^4+x^3+x^2+x+1,\\
    \Phi_8(x) &= x^4+1,\\
    \Phi_9(x) &= x^6+x^3+1,\\
    \Phi_{10}(x) &= x^4-x^3+x^2-x+1.
    \end{aligned}
    $$
    
    An interesting fact is that although it appears that the coefficients of these cyclotomic polynomials can only be $0$ and $\pm1$, this conclusion is not true for general $n$. The first counterexample appears in $\Phi_{105}(x)$, and it can be proven that as $n$ increases, the coefficients can take arbitrarily large values.

Using the Möbius inversion formula above, we can summarize the following properties to simplify the computation of $\Phi_n(x)$:

???+ note "Properties"
    For the cyclotomic polynomial $\Phi_n(x)$, we have:
    
    1.  If a prime $p\mid n$, then $\Phi_{pn}(x)=\Phi_n(x^p)$;
    2.  If a prime $p\perp n$, then $\Phi_{pn}(x)=\dfrac{\Phi_n(x^p)}{\Phi_n(x)}$;
    3.  Specifically, if $n$ is odd, then $\Phi_{2n}(x)=\Phi_n(-x)$;
    4.  For a prime $p$, $\Phi_{p}(x)=1+x+\cdots+x^{p-1}$;
    5.  Specifically, $\Phi_{2^k}(x)=x^{2^{k-1}}+1$.

These properties show that the computation of cyclotomic polynomials focuses on the case where the degree is a square-free odd number. And for such cases, we can add prime factors one by one using property 2; each addition of a prime factor only requires one polynomial division.

Cyclotomic polynomials have many other properties.

???+ note "Theorem"
    Let $\Phi_n(x)$ be the $n>1$-th cyclotomic polynomial, and the degree of the polynomial is $\varphi(n)$. Then we have:
    
    1.  $\Phi_n(x)$ is a palindromic polynomial, its $j$-th coefficient and $\varphi(n)-j$-th coefficient are the same, that is, $\Phi_n(x)=x^{\varphi(n)}\Phi_n(1/x)$;
    2.  The coefficient of the $\varphi(n)-1$-th term equals $-\mu(n)$;
    3.  If $n$ is a prime power $p^k$, then $\Phi_n(1)=p$; otherwise, $\Phi_n(1)=1$;
    4.  Let $b>1$ and $p$ be a prime factor of $\Phi_n(b)$. Then either $p\mid n$, or $n$ is the order of $b$ in the multiplicative group $(\mathbf Z/p\mathbf Z)^\times$, and these two cases cannot occur simultaneously.

??? note "Proof"
    For the first three properties, we only need to use Möbius inversion. For 1, directly examine the Möbius inversion form of $\Phi_n(x)$, that is, $\Phi_d(x)=\prod_{d\mid n}(x^d-1)^{\mu(n/d)}$; for 2, let the coefficient of the $\varphi(n)-1$-th term of $\Phi_n(x)$ be $f(n)$, then comparing the coefficients of the $n-1$-th term on both sides of $x^n-1=\prod_{d\mid n}\Phi_d(x)$ gives $\sum_{d\mid n}f(d)=-[n=1]$, then apply Möbius inversion; for 3, divide both sides of $x^n-1=\prod_{d\mid n}\Phi_n(x)$ by $\Phi_1(x)=x-1$, then substitute $x=1$, giving $n=\prod_{d\mid n,d\neq 1}\Phi_n(1)$, then apply Möbius inversion.
    
    Now prove the fourth property. First, if $n$ is the order of $b$ in the multiplicative group $(\mathbf Z/p\mathbf Z)^\times$, then $n$ is the smallest positive integer satisfying $p\mid b^n-1$, so $p\mid\Phi_n(b)$. Conversely, if $p\mid\Phi_n(b)$, then $b^n\equiv 1\pmod p$; but if $n$ is not the order of $b$ in the multiplicative group $(\mathbf Z/p\mathbf Z)^\times$, then let its order be $k$, we must have $k\mid n$ and $p\mid\Phi_k(b)$. At this time, $\Phi_k(x)$ and $\Phi_n(x)$ have a common root $b$ in $\mathbf F_p$, which shows that $x^n-1$ has a multiple root $b$. This shows that $p\mid n$; otherwise, $x^n-1$ is coprime with its derivative, so it is separable over $\mathbf F_p$ and cannot have multiple roots. Therefore, the prime factors of $\Phi_n(b)$ have only two cases: $p\mid n$, or $n$ is the order of $b$ in $(\mathbf Z/p\mathbf Z)^\times$. These two cases are mutually exclusive, because the latter means $n\mid p-1$.

Cyclotomic polynomials can also solve some number theory and algebra problems. For example, the length of the repeating part of a decimal in a certain base is closely related to cyclotomic polynomials. For these specific applications, interested readers can refer to the materials at the end of this article.

## Finite Fields

A **finite field**, also called a **Galois field**, is a field with only finitely many elements. The structure of a finite field is uniquely determined by its number of elements, and the number of elements must be a power of a prime.

???+ note "Theorem"
    A field of size $q$ exists if and only if $q$ has the form of a prime power $p^n$. Moreover, such a field is unique up to isomorphism, denoted $\mathbf F_q$. The prime $p$ is the characteristic of $\mathbf F_q$, and the positive integer $n$ is the degree of the extension $\mathbf F_q/\mathbf F_p$. Finally, $\mathbf F_q$ is the splitting field of the polynomial $x^q-x$ over $\mathbf F_p$, and it contains exactly $q$ distinct roots of $x^q-x$.

??? note "Proof"
    Let $F$ be a finite field. The characteristic of $F$ is necessarily finite, denoted $p$; therefore, $F$ has the prime subfield $\mathbf F_p$. Moreover, $F$ is necessarily a finite extension of $\mathbf F_p$, with the degree of extension denoted $n$. As an $n$-dimensional vector space over $\mathbf F_p$, $F$ has $q=p^n$ elements. The set of all non-zero elements of $F$ forms the group $F^\times$ of order $q-1$, so $x^{q-1}=1$. Therefore, $F=F^\times\cup\{0\}$ satisfies $x^q=x$, i.e., they are the $q$ distinct roots of $x^q-x$. Therefore, in $F$, $x^q-x$ has the factor $\prod_{\alpha\in F}(x-\alpha)$, but the degree of this factor is already $q$ and the leading coefficient is $1$, so $x^q-x=\prod_{\alpha\in F}(x-\alpha)$. This shows that $x^q-x$ splits in $F$. For any field that can make $x^q-x$ split, since $x^q-x$ has $q$ distinct roots, there must be at least $q$ elements. This shows that $F$ is the smallest field making $x^q-x$ split, i.e., the splitting field of $x^q-x$. In summary, a finite field of size $q$ is necessarily the splitting field of $x^q-x$ over its prime subfield. Since splitting fields are unique up to isomorphism, fields of size $q$ are also unique.
    
    Conversely, given a prime $p$ and its power $q=p^n$, to show that the splitting field of $x^q-x$ over $\mathbf F_p$ has exactly $q$ elements, we can only prove that all fields of order $q$ exist. Since the splitting field of $x^q-x$ over $\mathbf F_p$ always exists, let $F$ be the set of all roots of $x^q-x$ in this splitting field. Now we need to prove that $F$ is a field, so it is itself the splitting field of $x^q-x$. However, iterating the Frobenius endomorphism $n$ times shows that $x\mapsto x^q$ is also an endomorphism, so for any $\alpha,\beta\in F$, we have $(\alpha\pm\beta)^q=\alpha^q\pm\beta^q$, $(\alpha\beta)^q=\alpha^q\beta^q$ and $(\alpha^{-1})^q=(\alpha^q)^{-1}$. Therefore, the set $F$ is closed under addition, subtraction, multiplication, and division, it is a field. This shows that $F$ is the splitting field of $x^q-x$ over $\mathbf F_p$.

???+ note "Corollary"
    In a finite field $\mathbf F_q$ ($q>2$), the sum of all non-zero elements is $0$, and the product is $-1$.

??? note "Proof"
    The non-zero elements of a finite field are exactly the $q-1$ distinct roots of $x^{q-1}-1$, and applying Vieta's theorem gives the result.

In the prime field $\mathbf F_p$, the conclusion about the product in this corollary is precisely part of [Wilson's Theorem](../number-theory/factorial.md#wilson-theorem) in number theory.

### Multiplicative Structure

The multiplicative group $\mathbf F^\times=\mathbf F\setminus\{0\}$ of a finite field is always a cyclic group.

???+ note "Theorem"
    Any finite subgroup of the multiplicative group of a field is always cyclic.

??? note "Proof"
    Let $G$ be a subgroup of the multiplicative group of $F$ with $|G|=n$. Then $G$ is a finite abelian group. According to the fundamental theorem of finite abelian groups, $G$ has invariant factor decomposition $C_{n_1}\times\cdots\times C_{n_s}$ with $n_1\mid\cdots\mid n_s$. So for all elements $x$ in $G$, $x^{n_s}=1$. That is, all elements of $G$ are roots of the polynomial $x^{n_s}-1$ over $F$. But $x^{n_s}-1$ has at most $n_s$ distinct roots, i.e., $n\le n_s$. But $n_s\le n$, so $n_s=n$. This shows $G\cong C_{n_s}$, i.e., $G$ is cyclic.

???+ note "Corollary"
    The multiplicative group of a finite field $\mathbf F_q$ is $\mathbf F_q^\times\cong C_{q-1}$.

In the cyclic group $\mathbf F_q^\times$, there are $\varphi(q-1)$ generators, which are called primitive elements of the finite field; here, $\varphi(n)$ is the [Euler function](../number-theory/euler-totient.md).

???+ abstract "Primitive Element"
    A generator of the multiplicative group of a finite field $\mathbf F_q$ is called a **primitive element** of $\mathbf F_q$.

??? warning "Primitive Elements in Simple Extensions and Finite Fields are Different"
    Although the names are the same, primitive elements in simple extensions and primitive elements in finite fields are different. Primitive elements in simple extensions are generators of the corresponding simple extension, while primitive elements in finite fields are generators of the corresponding multiplicative group (as a cyclic group). The primitive element of a finite field as a simple extension of its prime subfield is not necessarily a primitive element of the finite field itself. For example, in $\mathbf F_{25}\cong\mathbf F_5[x]/(x^2+x+1)$, $\overline x$ is a primitive element of the field extension, but not a primitive element of $\mathbf F_{25}$ because its order is $3$.

??? warning "Primitive Elements in $\mathbf F_q$ and Primitive Roots Modulo $q$ are Also Different"
    For finite fields $\mathbf F_q$ of odd characteristic, there always exists a [primitive root](./ring-theory.md#application-multiplicative-group-of-integer-congruence-classes) modulo $q$. However, it should not be confused with primitive elements (primitive elements) in finite fields $\mathbf F_q$. Although they are both generators of the corresponding multiplicative structure as a cyclic group, $(\mathbf Z/q\mathbf Z)^\times$ and $\mathbf F_q$ are not the same when $q$ itself is not prime. For example, the order of the former is $\varphi(q)$ while the order of the latter is $q-1$, so the sizes of the two multiplicative groups are not the same.

Let $\alpha$ be a primitive element of a finite field $\mathbf F_q$. Then for all $x\in\mathbf F_q$, there exists a unique natural number $k<q-1$ such that $x=\alpha^k$; this $k$ is called the **discrete logarithm** of $x$ over $\mathbf F_q$ with respect to the basis $\alpha$. Consistent with the case over $\mathbf F_p$, the complexity of [discrete logarithm algorithms](../number-theory/discrete-logarithm.md) is relatively high.

Through multiplication, primitive elements can generate all non-zero elements of the field. This shows that a finite field, as an extension of its subfield, is necessarily a simple extension.

???+ note "Theorem"
    For a finite field $\mathbf F_q$, let $F$ be a subfield of $\mathbf F_q$. Then $\mathbf F_q$ is a simple algebraic extension over $F$; also let $\alpha$ be a primitive element of $\mathbf F_q$, then $\mathbf F_q=F(\alpha)$.

The minimal polynomial of a primitive element is an irreducible polynomial over a subfield of the finite field.

### Containment Relations

Subfields of finite fields are also finite fields. The containment relations between finite fields are also completely determined by their orders.

???+ note "Theorem"
    Let $\mathbf F_q$ and $\mathbf F_r$ be finite fields. Then $\mathbf F_r$ is a subfield of $\mathbf F_q$ if and only if there exists $k$ such that $q=r^k$. In other words, $\mathbf F_{p^d}$ is a subfield of $\mathbf F_{p^n}$ if and only if $d\mid n$.

??? note "Proof"
    If $\mathbf F_r$ is a subfield of $\mathbf F_q$, they must have the same characteristic $p$. The field extensions $\mathbf F_q/\mathbf F_r$, $\mathbf F_r/\mathbf F_p$, and $\mathbf F_q/\mathbf F_p$ are all simple algebraic extensions, with degrees $k$, $d$, and $n$ respectively, and the degrees satisfy $n=kd$. Moreover, $r=p^d$ and $q=p^n$, and $q=p^n=p^{kd}=(p^d)^k=r^k$.
    
    Conversely, to prove that for all $d\mid n$, $\mathbf F_{p^d}$ is a subfield of $\mathbf F_{p^n}$. Let $r=p^d$ and $q=p^n$. Let $F$ be the set of all roots of $x^r-x=0$ in $\mathbf F_q$. Through the Frobenius endomorphism, $F$ necessarily forms a field; the key is to prove that there are exactly $r$ such roots, so $F\cong\mathbf F_r$. Since $d\mid n$, $(p^d-1)\mid(p^n-1)$, so $(x^{p^d-1}-1)\mid(x^{p^n-1}-1)$, i.e., $(x^r-x)\mid (x^q-x)$. Therefore, $x^r-x$ splits over $\mathbf F_q$, so there are $r$ distinct roots in $\mathbf F_q$. This shows that $F\cong\mathbf F_r$ is a subfield of $\mathbf F_q$.

This theorem shows that the containment relations between finite fields $\mathbf F_{p^n}$ correspond to the divisibility relations between the exponents $n$ in the orders $p^n$. The lattice formed by all finite fields $\mathbf F_{p^n}$ of characteristic $p$ is isomorphic to the lattice formed by integers $n$ under divisibility. Of course, to make the intersection and other operations between $\mathbf F_{p^n}$ meaningful, we need to embed all fields of characteristic $p$ into the algebraic closure of $\mathbf F_p$.

???+ note "Theorem"
    Let $F$ be the algebraic closure of $\mathbf F_p$. Then the set of roots of $x^{p^n}-x$ in $F$ forms the finite field $\mathbf F_{p^n}$. Then we have:
    
    1.  $F=\bigcup_{n=1}^\infty\mathbf F_{p^n}$, i.e., the algebraic closure of $\mathbf F_p$ is the union of all finite fields of characteristic $p$;
    2.  The lattice formed by all finite fields $\mathbf F_{p^n}$ of characteristic $p$ under containment is isomorphic to the lattice formed by integers $n$ under divisibility. In particular, $\mathbf F_{p^n}\cap\mathbf F_{p^m}=\mathbf F_{p^{\gcd(n,m)}}$, and the smallest field containing both $\mathbf F_{p^n}$ and $\mathbf F_{p^m}$ is $\mathbf F_{p^{\operatorname{lcm}(n,m)}}$.

??? note "Proof"
    The key is to prove the first part, that $\bigcup_{n=1}^\infty\mathbf F_{p^n}$ is the algebraic closure of $\mathbf F_p$. The second part is a simple corollary of the theorem about subfields of finite fields.
    
    Note that for any $\alpha\in\bigcup_{n=1}^\infty\mathbf F_{p^n}$, there exists $n\in\mathbf N_+$ such that $\alpha\in\mathbf F_{p^n}$, so $\alpha$ is algebraic over $\mathbf F_p$; therefore, $\bigcup_{n=1}^\infty\mathbf F_{p^n}$ is an algebraic extension of $\mathbf F_p$. For any polynomial $f(x)$ of degree $m$ over $\mathbf F_p$, it has at most $m$ distinct roots $\{\alpha_i\}_{i=1}^m$ in the algebraic closure $F$. Let the degree of the minimal polynomial of $\alpha_i$ be $n_i$, then $\alpha_i$ is necessarily contained in $\mathbf F_{p^{n_i}}$; therefore, all roots of $f(x)$ are in $\alpha\in\bigcup_{n=1}^\infty\mathbf F_{p^n}$, i.e., $f(x)$ splits over $\alpha\in\bigcup_{n=1}^\infty\mathbf F_{p^n}$. According to the definition of algebraic closure, $\alpha\in\bigcup_{n=1}^\infty\mathbf F_{p^n}$ is the algebraic closure of $\mathbf F_p$.

### Automorphism Group

Subfields of a finite field $\mathbf F_q$ are all sets of roots of polynomials of the form $x^r-x$. In other words, they are all fixed point sets of some map $x\mapsto x^r$. This actually reveals a deep correspondence between subfields of finite fields and subgroups of the automorphism group.

All fields of characteristic $p$ have the Frobenius endomorphism $\sigma_p:x\mapsto x^p$. For finite fields $\mathbf F_q$, this is also an automorphism; this shows that all finite fields $\mathbf F_q$ are perfect fields. The automorphism group of $\mathbf F_q$ is the cyclic group $\langle\sigma_p\rangle$ of order $n$, and one generator is the Frobenius endomorphism $\sigma_p$.

???+ note "Theorem"
    The automorphism group $\operatorname{Aut}(\mathbf F_q)$ of a finite field $\mathbf F_q$ is a cyclic group of order $n$, and the generator $\sigma_p$ is the Frobenius endomorphism $x\mapsto x^p$.

??? note "Proof"
    First, the Frobenius endomorphism $\sigma_p$ is an automorphism on the finite field $\mathbf F_q$ because an injection on a finite set must also be a surjection. Therefore, $\sigma_p\in\operatorname{Aut}(\mathbf F_q)$.
    
    Then, the order of $\sigma_p$ is $n$. This is because for all $x\in\mathbf F_q$, we have $\sigma_p^n(x)=x^{p^n}=x$, so $x^{p^n}$ is the identity map; and for any $k<n$, $\sigma_p^k$ is not the identity map, otherwise all elements of $\mathbf F_q$ would be roots of $x^{p^k}-x$, which is impossible.
    
    Finally, $\operatorname{Aut}(\mathbf F_q)$ has at most $n$ elements. Let $\alpha$ be a primitive element of $\mathbf F_q$. Then an automorphism $\sigma\in \operatorname{Aut}(\mathbf F_q)$ is uniquely determined by its value at $\alpha$, $\sigma(\alpha)$. However, $\sigma$ must map $\alpha$ to its conjugate; otherwise, $\alpha$ and $\sigma(\alpha)$ are no longer roots of the same minimal polynomial. There are only $n$ such conjugates, which shows that $\operatorname{Aut}(\mathbf F_q)$ also has at most $n$ elements.
    
    Therefore, the $n$ elements in $\operatorname{Aut}(\mathbf F_q)$ are exactly $\langle\sigma_p\rangle$. Theorem proved.

Subgroups of the automorphism group $\operatorname{Aut}(\mathbf F_q)$ correspond one-to-one with subfields of $\mathbf F_q$.

???+ note "Theorem"
    Let $\mathbf F_q$ be a finite field, $\mathcal F$ its set of all subfields, and $\mathcal G$ the set of all subgroups of its automorphism group $\operatorname{Aut}(\mathbf F_q)$. Then we have:
    
    1.  For $F\in\mathcal F$, let $\operatorname{Aut}(\mathbf F_q/F)$ be the set of automorphisms in $\operatorname{Aut}(\mathbf F_q)$ that keep $F$ unchanged, i.e., $\operatorname{Aut}(\mathbf F_q/F)=\{\sigma\in\operatorname{Aut}(\mathbf F_q):\forall x\in F(\sigma(x)=x)\}$, then $\operatorname{Aut}(\mathbf F_q/F)\le\operatorname{Aut}(\mathbf F_q)$;
    2.  For $G\in\mathcal G$, let $F^G$ be the intersection of the fixed point sets of all automorphisms in $G$, i.e., $F^G=\{x\in\mathbf F_q:\forall\sigma\in G(\sigma(x)=x)\}$, then $F^G$ is a subfield of $\mathbf F_q$;
    3.  The maps $F\rightarrow\operatorname{Aut}(\mathbf F_q/F)$ and $G\rightarrow F^G$ are inverses of each other, and are a one-to-one correspondence between $\mathcal F$ and $\mathcal G$;
    4.  This one-to-one correspondence maps containment relations between subfields to containment relations between subgroups, i.e., for any $F_1\subseteq F_2$, we have $\operatorname{Aut}(\mathbf F_q/F_2)\le\operatorname{Aut}(\mathbf F_q/F_1)$.

This conclusion is a special case of the fundamental theorem of general Galois theory, connecting field extensions with group theory, thus allowing group theory methods to solve field extension problems.

### Irreducible Polynomials

Irreducible polynomials over finite fields $\mathbf F_q$ are very easy to determine. Because each $n$-degree irreducible polynomial over $\mathbf F_q$ corresponds to an $n$-degree algebraic extension, and such extensions are unique. Therefore, all $n$-degree irreducible polynomial roots can be found in $\mathbf F_{q^n}$. This shows that $n$-degree irreducible polynomials over $\mathbf F_q$ must be factors of $x^{q^n}-x$. To determine all $n$-degree irreducible polynomials over $\mathbf F_q$, we need to examine the factorization of $x^{q^n}-x$ over $\mathbf F_q$. This is very similar to the case of cyclotomic polynomials.

Algebraic elements over $\mathbf F_q$ can be classified according to the degree of their minimal polynomials. Let $P_n$ be the set of algebraic elements whose minimal polynomial has degree exactly $n$, then

$$
\mathbf F_{q^n} = \bigcup_{d\mid n}P_d.
$$

This corresponds to the factorization

$$
x^{q^n}-x = \prod_{d|n}\prod_{\zeta\in P_d}(x-\zeta).
$$

Because $n$-degree irreducible polynomials have $n$ roots, and all these roots have minimal polynomial degree $n$, $n$-degree irreducible polynomials must be factors of

$$
\prod_{\zeta\in P_n}(x-\zeta) = \prod_{d\mid n}\left(x^{q^d}-x\right)^{\mu(n/d)}
$$

; this expression is obtained by applying [Möbius inversion](../number-theory/mobius.md) to the previous factorization. Since the degree of this polynomial is

$$
\sum_{d\mid n}\mu(d)q^{n/d},
$$

the number of $n$-degree monic irreducible polynomials over $\mathbf F_q$ is

$$
\frac1n\sum_{d\mid n}\mu(d)q^{n/d}
$$

. This is exactly the number of necklaces of length $n$ that can be made with $q$ colors (not considering rotations) ([proof](../combinatorics/polya.md#cyclic-group)), so it is also called the necklace polynomial.

???+ note "Theorem"
    There exist irreducible polynomials of any degree over finite fields $\mathbf F_q$.

Because irreducible polynomials over finite fields have simple structure, factoring polynomials over finite fields is very easy. For example, to determine all $n$-degree irreducible factors of a given polynomial, we only need to find the greatest common divisor of the given polynomial with $x^{q^n}-x$[^ddf]. Similarly, if an $n$-degree polynomial is coprime with $x^{q^k}-1$ for all $k<n$, then we can conclude that the $n$-degree polynomial is irreducible over $\mathbf F_q$.

It was pointed out earlier that roots of irreducible polynomials over finite fields are not necessarily primitive elements of the corresponding extension fields as finite fields. Primitive elements of a finite field $\mathbf F_q$ over its prime field $\mathbf F_p$ are also called **primitive polynomials**[^prim-poly] over $\mathbf F_p$. Using such polynomials to implement extensions ensures that $\overline x$ must be a primitive element in the extension field. Primitive polynomials of degree $n$ over $\mathbf F_p$ can be obtained by factoring the cyclotomic polynomial $\Phi_n(x)$ over $\mathbf F_p$.

???+ note "Theorem"
    Let $p$ be a prime, $n$ a positive integer, and $p\perp n$. Also let $d$ be the order of element $p$ in the multiplicative group $(\mathbf Z/n\mathbf Z)^\times$. Then the cyclotomic polynomial $\Phi_n(x)$ factors over $\mathbf F_p$ into $\dfrac{\varphi(n)}{d}$ primitive polynomials of degree $d$ over $\mathbf F_p$. In particular, $\Phi_n(x)$ is irreducible over $\mathbf F_p$ if and only if $p$ is a primitive root modulo $n$.

??? note "Proof"
    Note that the roots of the $n$-th cyclotomic polynomial are all $n$-th primitive roots of unity over $\mathbf F_p$, and the degree of the minimal polynomial of an $n$-th primitive root of unity $d$ is the number of its conjugates (including itself), which is the length of its orbit under the automorphism group $\langle\sigma_p\rangle$. So $d$ is the length of the orbit of the cyclic subgroup of $\{\zeta^i:i\perp n\}$ under the map $\zeta^i\mapsto\zeta^{ip}$, which is also the order of element $p$ in the multiplicative group $(\mathbf Z/n\mathbf Z)^\times$. If one does not want to rely on Galois theory, this can also be proven by showing that $d$ is the smallest positive integer such that $(x^n-1)\mid(x^{p^d-1}-1)$. Other conclusions are obvious.

Although irreducible polynomials are very important for the implementation of finite fields, there is no good deterministic method to find an $n$-degree irreducible polynomial over $\mathbf F_q$. In general, random methods can be used to generate such irreducible polynomials. Because among all $n$-degree monic polynomials, irreducible polynomials account for $\Theta(1/n)$, we can first randomly generate an $n$-degree monic polynomial and then determine whether it is irreducible. This can find an irreducible polynomial after generating an expected $\Theta(n)$ monic polynomials. Of course, such generated irreducible polynomials are not necessarily primitive polynomials, and the coefficients are not necessarily simple. In practice, if the size of the finite field is given in advance, one can often find primitive polynomials with simple coefficients by looking up tables[^list-prim-poly] to facilitate subsequent calculations.

### Reference Implementation

This section provides a simple implementation of finite fields, for reference only. The code implements a method to randomly generate irreducible polynomials.

??? example "Reference Implementation"
    ```cpp
    --8<-- "docs/math/code/finite-field/finite-field_1.cpp"
    ```

Finite fields of characteristic $2$ are the most commonly used in cryptography. For such fields, elements can be stored as binary strings, and field operations can be implemented using bit operations.

## Applications

This section lists some applications of field extensions in competitive programming. The most important case is when calculating arithmetic expressions over fields, we need to introduce some elements that do not exist in the original field in the intermediate process, making direct calculation possible. Readers should be familiar with using complex numbers to solve real number problems, which is an example of extension over the real field; readers may be relatively unfamiliar with extensions over finite fields. Therefore, we mainly discuss extensions over finite fields here, especially extensions over prime fields $\mathbf F_p$.

In some cases, field extensions can reduce the complexity of calculations, so they are necessary, such as [Fast Fourier Transform](../poly/fft.md) over real fields; in some cases, field extensions are just one of many problem-solving methods, and there are usually methods of similar complexity that avoid using field extensions, such as the calculation of Fibonacci sequences to be mentioned shortly. While understanding these applications, readers should compare the advantages and disadvantages of different methods to choose the appropriate method when solving problems.

### Fibonacci Sequence

For computing the [Fibonacci sequence](../combinatorics/fibonacci.md), common methods are $O(n)$ linear recurrence and $O(\log n)$ matrix exponentiation. In fact, it can also be solved through field extensions, with the same time complexity $O(\log n)$. The Fibonacci sequence has a formula:

$$
f(n) = \frac{1}{\sqrt{5}}\left(\left(\frac{1+\sqrt{5}}{2}\right)^n-\left(\frac{1-\sqrt{5}}{2}\right)^n\right).
$$

Now we want to compute $f(n)$ modulo a prime $p\neq 5$[^fib-p5]. To transform this problem into computation over the finite field $\mathbf F_p$, the first problem to solve is the meaning of $\sqrt{5$ in $\mathbf F_p$. From an algebraic perspective, it is the square root of $5$. Therefore, if a square root of $5$ exists in $\mathbf F_p$, i.e., $5$ is a quadratic residue modulo $p$, we can directly compute its quadratic residue and substitute it into the calculation; otherwise, we need to perform calculations in the extension field $\mathbf F_p(\sqrt 5)\cong\mathbf F_p[x]/(x^2-5)$.

Of course, when calculating in the extension field, there is no need to add $\sqrt 5$. For example, for the Fibonacci sequence, we can also let $\phi$ be the root of $x^2-x-1$, then $f(n)$ can be written as

$$
f(n)=\frac{\phi^n-(-\phi)^{-n}}{2\phi-1}=\frac{\phi^n-(1-\phi)^n}{2\phi-1}.
$$

If $5$ is not a quadratic residue modulo $p$, the polynomial $x^2-x-1$ is irreducible. At this time, we can perform calculations in the extension field $\mathbf F_p(\theta)\cong\mathbf F_p[x]/(x^2-x-1)$, which can yield results consistent with the above.

The method for calculating Fibonacci sequences can certainly be extended to other cases. However, one point to note: the irreducibility of polynomials over finite fields is not consistent with that over the rational field. For example, $x^4-10x^2+1$ is irreducible over $\mathbf Q$, and its splitting field is $\mathbf Q(\sqrt 2+\sqrt 3)=\mathbf Q(\sqrt 2,\sqrt 3)$; but in $\mathbf F_p$, if both $2$ and $3$ are not quadratic residues modulo $p$, it is the product of two irreducible polynomials, i.e., the square root $\sqrt{3}$ already exists in the extension $\mathbf F_p(\sqrt 2)$ without further extension.

### Extending to "Extensions" over Rings

As shown in the previous section, field extensions have various limitations. For calculating Fibonacci sequences, the extension field method can only solve the case where the modulus $p$ is prime and $5$ is not a quadratic residue of $p$. However, it should be noted that the discussion in the [Algebraic Extensions](#algebraic-extensions) section shows that if we do not require division operations in the extended structure, we can extend rings[^ring-extension]. This section briefly discusses this method using the calculation of the Fibonacci sequence under arbitrary modulus $n$. Other common scenarios that do not involve too many division operations, such as determinant calculation and Fast Fourier Transform, can also try to apply this method when necessary.

Let $m$ be any positive integer, and $f(n)$ the $n$-th term of the Fibonacci sequence. The problem is to compute $f(n)\bmod m$. In principle, we need to calculate over $\mathbf Z/m\mathbf Z$. But as shown in the previous section, under different moduli, the reducibility and presence of multiple roots of $x^2-x-1$ are not consistent, so the formula for the Fibonacci sequence may vary greatly. Moreover, if $\mathbf Z/m\mathbf Z$ itself is not a field, the extended elements often do not have valid inverses (for example, when the modulus is $5$, the denominator $\sqrt 5$ is directly zero). Although there are many problems, in fact, under the condition that coefficients are taken modulo $m$, we can calculate the constant term of

$$

(1-x)^n-x^n\mod{x^2-x-1}
$$

. Comparing with the formula above, the reasonableness of this method is obvious: this seems to be calculating

$$

f(n)=\frac{(1-\phi)^n-\phi^n}{1-2\phi}
$$

in the "extension" $(\mathbf Z/m\mathbf Z)[x]/(x^2-x-1)$, and $\phi$ is the root of $x^2-x-1$.

Although it is not so obvious, this method is also valid. Note that the formula holds in the extension of the rational field $\mathbf Q(\phi)\cong\mathbf Q[x]/(x^2-x-1)$. This shows that in $\mathbf Z[x]$,

$$

(1-x)^n-x^n \equiv f(n)(1-2x) \pmod{x^2-x-1}
$$

holds. This only involves polynomials with integer coefficients, so it also holds in $\mathbf Z[x]$. Written as division with remainder, taking both sides modulo $m$ gives an identity over $(\mathbf Z/m\mathbf Z)[x]$. This conclusion holds for all $m$.

In general, if an expression can be calculated over an extension field of the rational field $\mathbf Q$, then we can always obtain a conclusion over $\mathbf Z[x]$ by removing denominators, and taking modulo $m$ gives a conclusion over $(\mathbf Z/m\mathbf Z)[x]$. The key to this approach working is that the step of removing denominators should not cause "irreversible" consequences. For example, for the calculation of Fibonacci sequences, if we do not use the constant term coefficient but use the linear term coefficient, then because the coefficient has factor $2$, when $2$ is even modulo $m$, it has no inverse, and we cannot recover $f(n)$; another example, also for the calculation of Fibonacci sequences, if we use the formula with the $(-\phi)^{-n}$ term, the step of removing denominators will introduce factors that are difficult to handle, so we cannot obtain a conclusion from the result after taking the remainder. Therefore, the choice of calculation process is the key to applying this technique.

### Cipolla Algorithm

This is a typical example of using extensions of finite fields for calculation. For a quadratic residue $a$ modulo $p\neq 2$, find its square root, i.e., find $x$ such that $x^2\equiv a\pmod p$. Although this is a problem over $\mathbf F_p$, the [Cipolla algorithm](../number-theory/quad-residue.md#cipolla-algorithm) performs calculations over the finite field $\mathbf F_{p^2}$. This section explains this algorithm using the language of field theory. The elementary number theory proof can be found in the given link.

Specifically, the Cipolla algorithm first chooses $r$ such that $r^2-a$ is a quadratic non-residue modulo $p$, which means $x^2-(r^2-a)$ is an irreducible polynomial. Therefore, let $u=r^2-a$, we can consider the extension field $\mathbf F_p(\sqrt u)$. Because the Frobenius endomorphism can only map elements to their conjugates, and such conjugate in a quadratic extension is unique, i.e., $(r-\sqrt u)^p=r+\sqrt u$. Therefore, $(r-\sqrt u)^{p+1}=(r+\sqrt u)(r-\sqrt u)=r^2-u=a$. So to find the square root, we only need to compute $(r-\sqrt u)^{(p+1)/2}$. This value must be in $\mathbf F_p$ because the splitting field of $x^2-a$ is $\mathbf F_p$ itself.

## Exercises

Finally, list some problems that directly apply the content of this article to deepen understanding. However, note that much of the content is not a conventional test point in competitive programming.

-   Cyclotomic polynomials:
    -   [Luogu P1520 Factorization](https://www.luogu.com.cn/problem/P1520)
    -   [Gym102114C Call It What You Want](https://codeforces.com/gym/102114/problem/C)
-   Finite fields:
    -   [Luogu P3923 College Math Problem](https://www.luogu.com.cn/problem/P3923)
    -   [COTS 2021]菜 Jelo](https://www.luogu.com.cn/problem/P11192)
    -   [CF1310F. Bad Cryptography](https://codeforces.com/problemset/problem/1310/F)
    -   [LOJ 178. Polynomial Root Finding](https://loj.ac/p/178)
-   Field extensions:
    -   [Oleksandr Kulkov Contest 2] Problem A. Square Root Partitioning](https://codeforces.com/gym/102354/problem/A)
    -   [CF1103E. Radix Sum](https://codeforces.com/problemset/problem/1103/E)

## References

-   Dummitt, D.S. and Foote, R.M. (2004) Abstract Algebra. 3rd Edition, John Wiley & Sons, Inc.
-   [Milne, J.S. Fields and Galois Theory.](https://www.jmilne.org/math/CourseNotes/FT.pdf)
-   [Factorization of polynomials - Wikipedia](https://en.wikipedia.org/wiki/Factorization_of_polynomials)
-   [Factorization of polynomials over finite fields - Wikipedia](https://en.wikipedia.org/wiki/Factorization_of_polynomials_over_finite_fields)
-   [Cyclotomic Polynomial - Wikipedia](https://en.wikipedia.org/wiki/Cyclotomic_polynomial)
-   [Brett Porter's Notes on Cyclotomic Polynomials](https://www.whitman.edu/documents/academics/majors/mathematics/2015/Final%20Project%20-%20Porter%2C%20Brett.pdf)
-   [Jordan Bell's Notes on Cyclotomic Polynomials](https://jordanbell.info/LaTeX/mathematics/cyclotomic/cyclotomic.pdf)
-   [Michel Waldschmidt. An introduction to the theory of finite fields](https://webusers.imj-prg.fr/~michel.waldschmidt/articles/pdf/FiniteFields.pdf)
-   [Finite Field Arithmetic - Wikipedia](https://en.wikipedia.org/wiki/Finite_field_arithmetic)

[^subfield-one]: This is because the unity element $1_E$ of $F$ must satisfy the relation $x^2-x=0$ over $F$, and the latter has only two roots $0_F$ and $1_F$ in $F$. Since the field definition requires $1_E\neq 0_E$, we must have $1_E=1_F$ and $0_E=0_F$.

[^initial-object-ring]: In category theory language, $\mathbf Z$ is the [initial object](https://en.wikipedia.org/wiki/Initial_and_terminal_objects) of the category of unital rings.

[^polynomial-universal]: Strictly speaking, this refers to the [universal property](https://en.wikipedia.org/wiki/Polynomial_ring#Polynomial_evaluation) of the polynomial ring $R[x]$.

[^multi-poly-ring]: The polynomial ring here has infinitely many indeterminates. To define such a polynomial ring, we first need to define monomials. Let the set of indeterminates be $X$, then monomials over it are functions $\alpha:X\rightarrow\mathbf N$ that are non-zero at only finitely many indeterminates, which can be written as $x_{i_1}^{\alpha(i_i)}\cdots x_{i_k}^{\alpha(i_k)}$, where $i_1,\cdots,i_k$ are the indices of all indeterminates where $\alpha$ takes non-zero values. Polynomials are linear combinations of finitely many monomials. They form rings under the correspondingly defined addition and multiplication. For the case of finitely many indeterminates, it can be proven that this definition gives the same result as the recursive definition in the [Multivariate Polynomial Rings](./ring-theory.md#multivariate-polynomial-rings) section.

[^fundamental-algebra]: Although named the Fundamental Theorem of Algebra, this conclusion is not purely algebraic because the construction of the real field requires topological structure.

[^ddf]: This statement is not entirely rigorous because factors with degrees $d\mid n$ will also be obtained. However, since algorithm implementations usually start factorizing from smaller degrees, when separating $n$-degree irreducible polynomial factors, smaller factors should have been separated, so this statement is also acceptable.

[^prim-poly]: Do not confuse this with primitive polynomials in polynomial theory (i.e., polynomials where the greatest common divisor of all coefficients is 1).

[^list-prim-poly]: For example, [Hansen, T., & Mullen, G. L. (1992). Primitive polynomials over finite fields. Mathematics of computation, 59(200), 639-643](https://www.ams.org/journals/mcom/1992-59-200/S0025-5718-1992-1134730-7/S0025-5718-1992-1134730-7.pdf) provides such a list in an appendix.

[^fib-p5]: When $p=5$, the characteristic equation $x^2-x-1=0$ of the Fibonacci sequence has a double root $x=3$, so in $\mathbf F_5$, the general term of the Fibonacci sequence is $f(n)=n3^{n-1}$.

[^ring-extension]: The so-called "extension over rings" usually has two meanings: one is a [generalization of group extensions](https://en.wikipedia.org/wiki/Algebra_extension), and the other is a [generalization of field extensions](https://en.wikipedia.org/wiki/Subring#Ring_extensions). This article refers to the second meaning. More specifically, the extensions discussed in this section are [integral extensions](https://en.wikipedia.org/wiki/Integral_element#Integral_extensions) over commutative unital rings, which is the generalization of the concept of algebraic extensions over fields to commutative unital rings.
