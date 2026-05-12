If you have already studied complex numbers, you may skip this page.

Learning complex numbers requires some background in vectors. If you have not studied vectors, please go to the [vectors page](../math/linear-algebra/vector.md).

## Complex Numbers

### Introduction

???+ note "Note"
    The introduction below is from the PEP (People's Education Press) high school mathematics A version, Volume 2 (compulsory).

From the perspective of equations, the question of whether negative real numbers have square roots reduces to whether the equation $x^2+a=0$ ($a>0$) has a solution, which further reduces to whether the equation $x^2+1=0$ has a solution.

Reviewing the process of extending number sets, we can see that each extension is closely related to practical needs. For example, to solve the problem of measuring the diagonal of a square and the fact that equations like $x^2-2=0$ have no solution in the rational number set, people extended the rational numbers to the real numbers. After a number set is extended, the addition and multiplication operations defined in the real numbers are consistent with those defined in the rational numbers, and both addition and multiplication satisfy the commutative and associative laws, with multiplication satisfying the distributive law over addition.

Following this idea, to solve the problem that equations like $x^2+1=0$ have no solution in the real number system, we introduce a new number $\mathrm{i}$, such that $x=\mathrm{i}$ is a solution of $x^2+1=0$, i.e., $\mathrm{i}^2=-1$.

Thought experiment: When adding the new number $\mathrm{i}$ to the real numbers, we want the number $\mathrm{i}$ and real numbers to be able to perform addition and multiplication like real numbers, and we want both addition and multiplication to satisfy the commutative and associative laws, with multiplication satisfying the distributive law over addition. Then, what numbers does the real number system consist of after extension?

Following the above idea, multiply real number $b$ by $\mathrm{i}$, and denote the result as $b\mathrm{i}$. Add real number $a$ and $b\mathrm{i}$, and denote the result as $a+b\mathrm{i}$. Noting that all real numbers and $\mathrm{i}$ can be written in the form $a+b\mathrm{i}$ ($a,b\in \mathbf{R}$), all these numbers are in the extended number set.

### Definition

We define numbers of the form $a+b\mathrm{i}$, where $a,b\in \mathbf{R}$, as **complex numbers**, where $\mathrm{i}$ is called the **imaginary unit**. The set of all complex numbers is called the **complex number set**, denoted $\mathbf{C}$.

Complex numbers are usually denoted by $z$, i.e., $z=a+b\mathrm{i}$. This form is called the **algebraic form of a complex number**. Here, $a$ is called the **real part** of complex number $z$, denoted $\operatorname{Re}(z)$, and $b$ is called the **imaginary part** of $z$, denoted $\operatorname{Im}(z)$. Unless otherwise specified, we always have $a,b\in \mathbf{R}$.

For a complex number $z$, it is a real number if and only if $b=0$, an imaginary number when $b\not = 0$, and a purely imaginary number when $a=0$ and $b\not = 0$.

The relationship between purely imaginary numbers, imaginary numbers, real numbers, and complex numbers is shown in the figure below.

![](images/complex-relation.svg)

## Properties and Operations

### Geometric Interpretation

We have established that numbers of the form $a+b\mathrm{i}$ are called complex numbers, and we have provided definitions and classifications. We can explore some deeper properties.

We place all real numbers on a number line and discover that points on the number line correspond one-to-one with real numbers. We consider doing the same for complex numbers.

First, we define **equality of complex numbers**: two complex numbers $z_1=a+b\mathrm{i}$ and $z_2=c+d\mathrm{i}$ are equal if and only if $a=c$ and $b=d$.

This definition is very natural, so we will not elaborate further.

That is, we can represent a complex number $z=a+b\mathrm{i}$ by a unique ordered pair of real numbers $(a,b)$. Thinking of the plane rectangular coordinate system, we find that **the set of complex numbers corresponds one-to-one with the set of points in the plane rectangular coordinate system**. Now we have found a geometric interpretation of complex numbers.

This plane rectangular coordinate system is no longer ordinary, because points in the plane rectangular coordinate system now have a special meaning—representing a complex number. We call such a plane rectangular coordinate system the **complex plane**. The $x$-axis is called the **real axis**, and the $y$-axis is called the **imaginary axis**. Furthermore, we say: **the set of complex numbers corresponds one-to-one with the set of all points in the complex plane**.

Considering our knowledge of plane vectors, we find that the coordinate representation of a vector is also an ordered pair of real numbers $(a,b)$. Clearly, the complex number $z=a+b\mathrm{i}$ corresponds to point $Z(a,b)$ in the complex plane, and it also corresponds to the plane vector $\overrightarrow{OZ}=(a,b)$. Thus we have found another geometric interpretation of complex numbers: **the set of complex numbers corresponds one-to-one with the set of vectors in the complex plane** (the real number $0$ corresponds to the zero vector).

Therefore, we transfer our knowledge of vectors to complex numbers. We define the **modulus of a complex number** as the modulus of the vector corresponding to the complex number. The modulus of a complex number $z=a+b\mathrm{i}$ is $|z|=\sqrt{a^2+b^2}$.

Thus, for convenience, we often call a complex number $z=a+b\mathrm{i}$ the point $Z$ or the vector $\overrightarrow{OZ}$, and we stipulate that equal vectors represent the same complex number.

And from our knowledge of vectors, we find that imaginary numbers cannot be compared in size (but real numbers can be).

### Addition and Subtraction

For complex numbers $z_1=a+b\mathrm{i}$ and $z_2=c+d\mathrm{i}$, the addition rule is defined as follows:

$$
z_1+z_2=(a+c)+(b+d)\mathrm{i}
$$

Clearly, the sum of two complex numbers is still a complex number.

Considering the addition operation on vectors, we find that the addition of complex numbers follows the same rules as vector addition. This also confirms the correctness of the geometric interpretation of complex numbers.

It can also be verified that complex number addition satisfies the **commutative** and **associative** laws. That is:

$$
\begin{aligned}
z_1+z_2&=z_2+z_1\\
(z_1+z_2)+z_3&=z_1+(z_2+z_3)
\end{aligned}
$$

Subtraction, being the inverse operation of addition, can be derived using the addition rule and the definition of complex number equality:

$$
z_1-z_2=(a-c)+(b-d)\mathrm{i}
$$

This also follows the rules of vector subtraction.

### Multiplication, Division, and Conjugation

For complex numbers $z_1=a+b\mathrm{i}$ and $z_2=c+d\mathrm{i}$, the multiplication rule is defined as follows:

$$
\begin{aligned}
z_1z_2&=(a+b\mathrm{i})(c+d\mathrm{i})\\
&=ac+bc\mathrm{i}+ad\mathrm{i}+bd\mathrm{i}^2\\
&=(ac-bd)+(bc+ad)\mathrm{i}
\end{aligned}
$$

It can be seen that multiplying two complex numbers is similar to multiplying two polynomials. You only need to replace $\mathrm{i}^2$ with $-1$ and combine the real and imaginary parts separately.

The multiplication of complex numbers is similar to the cross product form of vectors.

It is easy to see that complex number multiplication satisfies the **commutative**, **associative**, and **distributive** laws over addition:

-   $z_1z_2=z_2z_1$
-   $(z_1z_2)z_3=z_1(z_2z_3)$
-   $z_1(z_2+z_3)=z_1z_2+z_1z_3$

Since these laws hold, we find that **multiplication formulas in the real number domain also apply in the complex number domain**.

Division is the inverse operation of multiplication. Let us derive it:

$$
\begin{aligned}
\frac{a+b\mathrm{i}}{c+d\mathrm{i}}&=\frac{(a+b\mathrm{i})(c-d\mathrm{i})}{(c+d\mathrm{i})(c-d\mathrm{i})}\\
&=\frac{ac+bd}{c^2+d^2}+\frac{bc-ad}{c^2+d^2}\mathrm{i} &(c+d\mathrm{i}\not =0)
\end{aligned}
$$

Since vectors have no division, we will not discuss their relationship here.

To rationalize the denominator, we multiply by $c-d\mathrm{i}$. This expression is very meaningful.

For a complex number $z=a+b\mathrm{i}$, we call $a-b\mathrm{i}$ the **complex conjugate** of $z$, usually denoted $\bar z$. We can see that if two complex numbers are complex conjugates of each other, they are **symmetric with respect to the real axis**.

For complex numbers $z$ and $w$, the properties of complex conjugation are:

-   $z\cdot\bar{z}=|z|^2$
-   $\overline{\overline{z}}=z$
-   $\operatorname{Re}(z)=\dfrac{z+\bar{z}}{2}$, $\operatorname{Im}(z)=\dfrac{z-\bar{z}}{2}$
-   $\overline{z\pm w}=\bar{z}\pm\bar{w}$
-   $\overline{zw}=\bar{z}\bar{w}$
-   $\overline{z/w}=\bar{z}/\bar{w}$

### Argument and Principal Argument

If we set the real unit $1$ as the positive horizontal direction and the imaginary unit $\mathrm{i}$ as the positive vertical direction, we get the complex plane from the rectangular coordinate perspective.

The position of a complex number $z$ can also be determined using polar coordinates $(r, \theta)$. The value $r$ has already been mentioned above as the modulus of the complex number $z$.

The angle $\theta$ between the positive real axis and the vector corresponding to a **non-zero** complex number $z=x+\mathrm{i}y$ satisfies:

$$
\tan \theta=\frac{y}{x}
$$

This is called the **argument** of the complex number $z$, denoted:

$$
\theta= \arg z
$$

Any **non-zero** complex number $z$ has infinitely many arguments, so $\arg z$ is actually a set. We use $\operatorname{Arg} z$ (capital letter) to denote **one specific value** satisfying:

$$
-\pi<\operatorname{Arg} z \le \pi
$$

We call $\operatorname{Arg} z$ the **principal argument** or **principal value**. The argument is the principal argument plus an integer multiple of $2k\pi$ (which can be zero or negative), i.e., $\arg z = \{\operatorname{Arg} z + 2k\pi \mid k\in \mathbf Z\}$.

Note that the sum of two principal arguments is not necessarily a principal argument, whereas the sum of two arguments is always a valid argument.

Complex numbers with modulus less than $1$ form a shape in the complex plane called the **unit disk**. Complex numbers with modulus equal to $1$ are called **unit complex numbers**, and the set of all unit complex numbers in the complex plane is called the **unit circle**. In contexts where no confusion arises, the unit circle is sometimes simply called the unit disk.

From the perspective of polar coordinates, the multiplication and division of complex numbers become very simple. For multiplication: moduli multiply, arguments add. For division: moduli divide, arguments subtract.

### Euler's Formula

???+ note "Euler's formula[^ref1]"
    For any real number $x$,
    
    $$
    \mathrm{e}^{\mathrm{i}x}=\cos x+\mathrm{i}\sin x
    $$
    
    After supplementing the definitions of [complex exponential and complex trigonometric functions](#exponential-and-trigonometric-functions), this formula can be extended to all complex numbers.

### Exponential and Trigonometric Functions

For a complex number $z=x+\mathrm{i}y$, the function $f(z)=\mathrm{e}^x(\cos y+\mathrm{i}\sin y)$ satisfies $f(z_1+z_2)=f(z_1)f(z_2)$. From this, we give the definition of the **complex exponential function**:

$$
\exp z=\mathrm{e}^x(\cos y+\mathrm{i}\sin y)
$$

The complex exponential function is completely consistent with the real exponential function on the real number set. In the complex plane, it has the properties:

-   Positive modulus: $|\exp z|=\exp x>0$.
-   Argument: $\arg(\exp z)=\{y + 2k\pi \mid k\in\mathbf Z\}$.
-   Addition theorem: $\exp (z_1+z_2)=\exp (z_1)\exp (z_2)$.
-   Periodicity: $\exp z$ is a periodic function with basic period $2\pi \mathrm{i}$. If a function $f(z)$ has a period that is an integer multiple of some period, that period is called the **basic period**.

The definitions of **complex trigonometric functions** (also simply called **trigonometric functions**) are:

$$
\cos z=\frac{\exp (\mathrm{i}z)+\exp (-\mathrm{i}z)}{2}
$$

$$
\sin z=\frac{\exp (\mathrm{i}z)-\exp (-\mathrm{i}z)}{2\mathrm{i}}
$$

If we take $z\in\mathbf{R}$, then from [Euler's formula](#eulers-formula):

$$
\cos z=\operatorname{Re}\left(\mathrm{e}^{\mathrm{i}z}\right)
$$

$$
\sin z=\operatorname{Im}\left(\mathrm{e}^{\mathrm{i}z}\right)
$$

The complex trigonometric functions are completely consistent with the real trigonometric functions on the real number set. In the complex plane, they have the properties:

-   Parity: The sine function is odd, and the cosine function is even.
-   Trigonometric identities: The usual trigonometric identities all hold, such as the sum of squares equals $1$, or the angle addition and subtraction formulas.
-   Periodicity: The sine and cosine functions have a basic period of $2\pi$.
-   Zeros: The complete set of zeros of the real sine and real cosine functions constitutes the complete set of zeros of the complex sine and complex cosine functions. This extension does not introduce new zeros.
-   Unbounded modulus: The modulus of complex sine and complex cosine functions can exceed any given positive number, unlike real sine and cosine functions which are bounded within $1$.

## Three Forms of Complex Numbers

Using the perspectives of the rectangular coordinate system and the polar coordinate system, we can write complex numbers in three forms.

The **algebraic form** of a complex number is used to represent any complex number.

$$
z=x+y\mathrm{i}
$$

The algebraic form is convenient for computing the four operations: addition, subtraction, multiplication, and division of complex numbers.

The **trigonometric form** and **exponential form** of a complex number are used to represent non-zero complex numbers.

$$
z=r(\cos \theta +\mathrm{i}\sin \theta)=r \exp (\mathrm{i}\theta)
$$

These two forms are convenient for computing multiplication, division, and subsequent operations of complex numbers. If you only use functions encountered in high school, you can use the trigonometric form. If you introduce the complex exponential function, writing it in the equivalent exponential form is more convenient.

## Roots of Unity

Consider the solutions of the equation $x^n=1$ in the complex number domain. Clearly, there are $n$ such solutions, and these $n$ solutions are all called **$n$-th roots of unity** ($n$-th root of unity). According to the knowledge of the complex plane, the $n$-th roots of unity divide the unit circle into $n$ equal parts.

Let $\omega_n=\exp\dfrac{2\pi \mathrm{i}}{n}$ (i.e., the unit complex number with argument $2\pi/n$). Then the solution set of $x^n=1$ is $\{\omega_n^k\mid k=0,1\cdots,n-1\}$, where

$$
w_n^k = \exp\dfrac{2\pi k \mathrm{i}}{n} = \cos\dfrac{2\pi k}{n} + \mathrm{i}\sin\dfrac{2\pi k}{n}.
$$

Unless otherwise specified, the $n$-th root of unity mentioned in general discussion refers to the first solution in the counterclockwise direction starting from $1$, i.e., $\omega_n$ above. All other solutions can be expressed as powers of $\omega_n$.

???+ tip "Why is the first $n$-th root of unity usually referred to specifically?"
    This is mainly for convenience in applications. All $n$-th roots of unity can be expressed as powers of the first $n$-th root of unity $\omega_n$. Moreover, for any $k < n$, the complex number $\omega_n$ is not a $k$-th root of unity.

### Primitive Roots of Unity

In fact, among the $n$-th roots of unity, more than just $\omega_n$ satisfy similar properties. The set

$$
\{\omega_n^k\mid 0\le k<n,~\gcd(n,k)=1\}
$$

contains the **$n$-th primitive roots of unity**. From the above expression, there are $\varphi(n)$ $n$-th primitive roots of unity in total, where $\varphi(n)$ is the [Euler's totient function](./number-theory/euler-totient.md).

Any primitive root of unity $\omega$ has the same properties as $\omega_n$ above: for any $0<k<n$, the $k$-th power of $\omega$ is not $1$, that is, $\omega$ is not a $k$-th root of unity. Therefore, using any primitive root of unity, we can generate all roots of unity.

To understand the structure of $n$-th primitive roots of unity, we need to consider the following properties of roots of unity:

???+ note "Property"
    For integers $n$ and $k$, let $d=\gcd(n,k)$. Then $\omega_n^k = \omega_{n/d}^{k/d}$.

??? note "Proof"
    Direct calculation shows:
    
    $$
    w_n^k = \exp\dfrac{2\pi k\mathrm{i}}{n} = \exp\dfrac{2\pi (k/d)\mathrm{i}}{n/d} = \omega_{n/d}^{k/d}.
    $$

This shows that as long as $\gcd(n,k)\neq 1$, then $\omega_n^k$ is definitely a $\dfrac{n}{\gcd(n,k)}$-th (primitive) root of unity. Therefore, a root of unity $\omega_n^k$ satisfying the above properties must satisfy $\gcd(n,k)=1$. This is why primitive roots of unity have the definition above.

Additionally, as a simple corollary of this analysis:

???+ note "Theorem"
    When $k$ ranges over the divisors of $n$, all $k$-th primitive roots of unity exactly form a partition of the $n$-th roots of unity. Moreover, for $\ell\perp n$, the map $x\mapsto x^\ell$ gives a bijection among the $n$-th roots of unity, and this partition is preserved: it maps $k\mid n$-th primitive roots of unity to $k$-th primitive roots of unity.

Although there are many choices for primitive roots of unity, because the first root $\omega_n$ has the simplest form, $\omega_n$ is still the most commonly used in competitive programming. For some scenarios, to improve computational efficiency, we can also consider using a [primitive root of unity](./number-theory/residue.md#roots-of-unity) under a certain modulus instead of $\omega_n$ in the complex number domain.

## Complex Numbers in Programming Languages

### Complex Numbers in C

In the C99 standard, there is the `<complex.h>` header file.

In the `<complex.h>` header file, three types are provided: `double complex`, `float complex`, and `long double complex`.

The arithmetic operators '+', '-', '*', and '/' can be used for any mix of floating-point numbers and complex numbers. When one side of an expression is a complex number, the result is a complex number.

The `<complex.h>` header file provides the imaginary unit `I`. When this header file is included, the uppercase letter `I` cannot be used as a variable name.

For individual complex numbers, `<complex.h>` provides several operations: the `creal` function extracts the real part, `cimag` extracts the imaginary part, `cabs` calculates the modulus, and `carg` calculates the principal argument.

All functions have three versions depending on the type. For example, the `creal` function has `creal`, `crealf`, and `creall` for handling `double`, `float`, and `long double` respectively. The version without any suffix handles `double` by default. All functions below follow this pattern and will not be explained further.

All these functions return regular floating-point numbers. You can directly assign a regular floating-point number to a complex number, but you cannot directly assign a complex number to a floating-point number. Instead, you must use the extraction operations above.

The `conj` function calculates the complex conjugate and returns a complex number.

The `cexp` function calculates the complex exponential, `clog` calculates the principal value of the logarithm, `csin` calculates the sine, `ccos` calculates the cosine, and `ctan` calculates the tangent.

The `cpow` function calculates the power function, `csqrt` calculates the square root, `casin` calculates the inverse sine, `cacos` calculates the inverse cosine, and `catan` calculates the inverse tangent. All functions in this group calculate the principal value of multi-valued functions.

### Complex Numbers in C++

In C, the header `<ctype.h>` becomes `<cctype>` in C++. Almost all headers follow this naming convention.

However, `<complex.h>` does not follow this convention. There is no `<ccomplex>` header in C++. C++ has `<complex>` directly, and what it contains is completely different from C.

This is interesting. This is because in the first version of C++, C++98, `<complex>` already existed, whereas the C language did not add `<complex.h>` until C99.

In C++, complex number types are defined using `complex<float>`, `complex<double>`, and `complex<long double>`. Due to object-oriented polymorphism, function names are unique, eliminating the need for `f` or `l` suffixes.

A complex number object has member functions `real` and `imag` to access the real and imaginary parts.

A complex number object has non-member functions `real`, `imag`, `abs`, `arg` that return the real part, imaginary part, modulus, and argument respectively.

A complex number object also has non-member functions: `norm` for the square of the modulus, and `conj` for the complex conjugate.

A complex number object also has non-member functions: `exp`, `log` (principal value of the logarithm with base $\mathrm{e}$), `log10` (logarithm with base 10, not available in C), `pow`, `sqrt`, `sin`, `cos`, `tan`, with meanings the same as their C counterparts.

In C++14 and later, [literal operators `std::literals::complex_literals::""if, ""i, ""il`](https://en.cppreference.com/w/cpp/numeric/complex/operator%2522%2522i.html) are defined. For example, `100if`, `100i`, and `100il` return `std::complex<float>{0.0f, 100.0f}`, `std::complex<double>{0.0, 100.0}`, and `std::complex<long double>{0.0l, 100.0l}` respectively. This allows us to conveniently write complex number declarations like `auto z = 4.0 + 3i`.

## References and Links

-   [Complex number - Wikipedia](https://en.wikipedia.org/wiki/Complex_number)
-   [Euler's formula - Wikipedia](https://en.wikipedia.org/wiki/Euler's_formula)
-   [Complex number arithmetic - cppreference.com](https://en.cppreference.com/w/c/numeric/complex)
-   [std::complex - cppreference.com](https://en.cppreference.com/w/cpp/numeric/complex)

[^ref1]: For more about Euler's formula, you can refer to two videos: [Euler's Formula and Elementary Group Theory](https://www.bilibili.com/video/BV1fx41187tZ), [Differential Equations Lecture - Chapter 5: Understanding $\mathrm{e}^{\mathrm{i}\pi}$ in 3.14 minutes](https://www.bilibili.com/video/BV1G4411D7kZ).