## Polynomials and Generating Functions

Manipulating finite/infinite polynomials is an important content in OI mathematics, especially in generating functions.

Polynomial algorithms based on [Fast Fourier Transform](./fft.md) give algorithm competition players the ability to directly manipulate generating functions.

## Basic Concepts

For the summation $\sum a_nx^n$, if it is a finite sum, it is called a polynomial, denoted as $f(x)=\sum_{n=0}^m a_nx^n$.

A summable sum is called a series. In the sum $\sum_{n=0}^\infty a_nx^n$, each term is a constant multiplied by a non-negative integer power function—this form is called a power series.

When studying polynomial arithmetic, we first consider simpler polynomials; the concept of power series is only used for convenience in understanding. In mathematical analysis, the convergence of power series will be further studied.

For the general definitions of rings, fields, and their derived structures, see [Basic Concepts of Abstract Algebra](../algebra/basic.md).

For a general ring $R$, define the **polynomial ring** $R[x]$ over $R$.

Each element $f$ is called a **polynomial** over $R$, which can be expressed as:

$$
f=\left<f_0,f_1,f_2,\cdots,f_n\right>\quad(f_0,f_1,f_2,\cdots,f_n\in R)
$$

In other words, we directly define a polynomial as a sequence of coefficients. It can also be expressed as:

$$
f(x)=f_0+f_1x+f_2x^2+\cdots+f_nx^n
$$

Here we consider $x$ only as a **formal symbol**, a marker for coefficient positions.

If we also allow infinitely many terms:

$$
f(x)=f_0+f_1x+f_2x^2+\cdots
$$

Then we get the **formal power series ring** $R[[x]]$. Each element $f$ in it is called a **formal power series**, abbreviated as power series.

### Degree of a Polynomial

For a polynomial $f(x)$, the degree of its highest-order term is called its **degree**, denoted as $\operatorname{deg}{f}$.

### Polynomial Multiplication

The core operation is the multiplication of two polynomials, i.e., given polynomials $f(x)$ and $g(x)$:

$$
\begin{alignedat}{3}
f(x)&=a_0+a_1x+\dots+a_nx^n\quad \quad &(1)\\
g(x)&=b_0+b_1x+\dots+b_mx^m\quad \quad &(2)
\end{alignedat}
$$

To compute the polynomial $Q(x)=f(x)\cdot g(x)$:

$$
\boxed {Q(x) = \sum \limits_ {i = 0} ^ n \sum \limits_ {j = 0 } ^ m a_i b_j x ^ {i + j}} = c_0 + c_1 x + \dots + c_ {n + m} x ^ {n + m}
$$

Polynomial or power series multiplication satisfies associativity and distributivity over addition. If $R$ is a commutative ring or unity ring, multiplication correspondingly satisfies commutativity and has an identity element.

If there exist $2^n$-th roots of unity on $R$, [Fast Fourier Transform](./fft.md) allows us to compute the product of two degree-$2^n$ polynomials in $O(n2^n)$ instead of $O(2^{2n})$ time.

### Composition

Define the power of an element $f$ in $R[[x]]$ as:

$$
f^1=f,f^k=f^{k-1}\times f
$$

On this basis, define the composition of elements $f,g$ in $R[[x]]$ as:

$$
(f\circ g)(x)=f(g(x))=f_0+\sum_{k=1}^{+\infty}f_kg^k(x)
$$

We stipulate that $f\circ g$ exists if and only if $f$ has finitely many terms or $g_0=0$, so we don't involve limits on $R$.

$\circ$ satisfies associativity ($(f\circ g)\circ h$ and $f\circ (g\circ h)$ both exist), but not commutativity. When $R$ is a unity ring, $\circ$ has the identity element $1\times x$.

Polynomial composition (and composition inverse) has a $\Theta(n\log^2 n)$ method, proposed by Yasunori Kinoshita and Li Baitian in 2024. See [Formal Power Series Composition | Composition Inverse](./comp-rev.md).

### Derivative

Although a general ring may not even have limits,
we can still define the **formal derivative** of a formal power series as:

$$
\left(\sum_{k=0}^{+\infty}f_kx^k\right)'=\sum_{k=1}^{+\infty}kf_kx^{k-1}
$$

Where:

$$
kf_k=\underbrace{f_k+f_k+\cdots+f_k}_{k \text{ copies of } f_k}
$$

The basic differentiation rules—sum rule, product rule, and chain rule (when composition is allowed)—remain correct.

If division is allowed on $R$, we can similarly define the **formal indefinite integral** of a formal power series.

### Multiplicative Inverse

From the example:

$$
\dfrac{1}{1-x}=1+x+x^2+\cdots
$$

We can see that the reciprocal of a polynomial can be expanded into an infinite series. The reciprocal exists if and only if the constant term is non-zero, and the reciprocal also has a non-zero constant term.

Therefore, for a formal power series $f$, if $f_0\neq 0$, its **multiplicative inverse** $f^{-1}$ is another formal power series satisfying:

$$
f\times f^{-1}=f^{-1}\times f=1
$$

Expanding this using the definition of formal power series multiplication, we can get a recurrence formula for the coefficients of $f^{-1}$:

$$
f^{-1}_0=\dfrac{1}{f_0},f^{-1}_n=\dfrac{-1}{f_0}\sum_{k=0}^{n-1}f^{-1}_kf_{n-k}
$$

Computing the first $n$ terms directly using the recurrence formula is $O(n^2)$. Using FFT, we can get an $O(n\log n)$ algorithm. See [Polynomial Inverse](./elementary-func.md#polynomial-inverse).

???+ note "Note"
    It is easy to find that the reciprocal of $f(x)$ is the infinite-term Maclaurin expansion (infinite-term Taylor expansion at $x=0$) of $\frac{1}{f(x)}$.

### Common Power Series Expansions

In mathematical analysis, a univariate function that is differentiable several times at some point or on some interval can be expanded into a polynomial in the corresponding range—this is generally called Taylor expansion. If expanded at $0$, it's also called Maclaurin expansion.

If infinitely differentiable, it can be expanded into a power series. The most common is still expansion at $0$.

In complex analysis, some functions cannot be Taylor-expanded at singular points but can be expanded into Laurent series.

The following equations only hold when the power series converges; we only write the expansion form here without discussing the domain of convergence.

The two basic expansions are the exponential function and the power function:

$$
\mathrm{e}^x=1+x+\frac{1}{2!}x^2+\ldots+\frac{1}{n!}x^n+\ldots
$$

$$
(1+x)^a=1+ax+\frac{a(a-1)}{2!}x^2+\ldots+\frac{a(a-1)\ldots(a-n+1)}{n!}x^n+\ldots
$$

More expansions are often derived from the above two. For example, sine and cosine are obtained by substituting complex numbers into the exponential function:

$$
\cos x=1-\frac{1}{2!}x^2+\frac{1}{4!}x^4+\ldots+\frac{(-1)^n}{(2n)!}x^{2n}+\ldots
$$

$$
\sin x=x-\frac{1}{3!}x^3+\frac{1}{5!}x^5+\ldots+\frac{(-1)^n}{(2n+1)!}x^{2n+1}+\ldots
$$

Logarithm and inverse trigonometric functions are obtained via integration:

$$
\frac{1}{1+x}=1-x+x^2+\ldots+{(-1)}^n x^n+\ldots
$$

$$
\ln(1+x)=x-\frac{1}{2}x^2+\frac{1}{3}x^3+\ldots+\frac{{(-1)}^{n-1}}{n}x^n+\ldots
$$

$$
\frac{1}{1+x^2}=1-x^2+x^4+\ldots+{(-1)}^n x^{2n}+\ldots
$$

$$
\arctan x=x-\frac{1}{3}x^3+\frac{1}{5}x^5+\ldots+\frac{{(-1)}^{n}}{2n+1}x^{2n+1}+\ldots
$$

$$
\frac{1}{\sqrt{1+x}}=1-\frac{1}{2}x+\frac{3}{8}x^2+\ldots+{(-1)}^n\frac{(2n)!}{{(n!)}^2 4^n} x^{n}+\ldots
$$

$$
\frac{1}{\sqrt{1-x^2}}=1+\frac{1}{2}x^2+\frac{3}{8}x^4+\ldots+\frac{(2n)!}{{(n!)}^2 4^n} x^{2n}+\ldots
$$

$$
\arcsin x=x+\frac{1}{6}x^3+\frac{3}{40}x^5+\ldots+\frac{(2n)!}{{(n!)}^2(2n+1)4^n} x^{2n+1}+\ldots
$$

### Composition Inverse

**Composition inverse** is the generalization of the inverse function concept to formal power series rings.

For a formal power series $f$ satisfying $f_0=0$ and $f_1\neq 0$, its composition inverse is a formal power series $g$ satisfying $g(f(x))=f(g(x))=x$. From Lagrange inversion, for any integers $n,k$:

$$
n[x^n]f^k=k[x^{n-k}]\left(\dfrac{x}{g}\right)^n
$$

Where $[x^k]f(x)$ represents the coefficient of $x^k$ in $f(x)$.

### Polynomial Divisibility

For polynomials $f(x)$ and $g(x)$, if there exists a polynomial $h(x)$ such that:

$$
f(x)=g(x)h(x)
$$

Then polynomial $g(x)$ divides polynomial $f(x)$.

Obviously, polynomial $g(x)$ divides polynomial $f(x)$ if and only if all roots of $g(x)$ are roots of $f(x)$, and the multiplicity in $g(x)$ does not exceed the corresponding multiplicity in $f(x)$.

### Remainder and Quotient of Polynomials

For polynomials $f(x), g(x)$, there exists a **unique** pair $Q(x), R(x)$ satisfying:

$$
\begin{aligned}
    f(x) &= Q(x) g(x) + R(x) \\
    \operatorname{deg}{R} &< \operatorname{deg}{g}
\end{aligned}
$$

When $\operatorname{deg}{f} \ge \operatorname{deg}{g}$, we have $\operatorname{deg}{Q} = \operatorname{deg}{f} - \operatorname{deg}{g}$; otherwise, $Q(x) = 0$. We call $Q(x)$ the **quotient** of dividing $g(x)$ into $f(x)$, and $R(x)$ the **remainder**.

## Modular Polynomials

A modular polynomial is a subring of the polynomial ring, obtained by dividing the polynomial ring by the equivalence relation of congruence.

In the division with remainder mentioned above, polynomial $f(x)$ and its remainder $R(x)$ are congruent modulo the polynomial $g(x)$:

$$
f(x) \equiv R(x) \pmod{g(x)}
$$

This congruence also means that for any root $x_0$ of polynomial $g(x)$, substituting into $f(x)$ and $R(x)$ yields the same point value:

$$
f(x_0)=R(x_0)
$$

And if the root $x_0$ has multiplicity $k$ in polynomial $g(x)$, i.e., $(x-x_0)^k$ divides $g(x)$, then for any integer $t$ where $0 \le t < k$:

$$
f^{t}(x_0)=R^{t}(x_0)
$$

Here the notation denotes the $t$-th derivative.

Modular polynomial congruence can be applied to power series. An infinite-term power series can be congruent to a finite-term polynomial under a specific polynomial modulus. For example:

$$
1+x+x^2+x^3+\ldots \equiv 1+x+\ldots+x^{n-1} \pmod{x^n}
$$

Obviously, all remaining terms are divisible by $x^n$. So the operation modulo $x^n$ is equivalent to "truncating" the infinite-term power series to the first $n$ terms, directly losing higher-order information.

In some specific cases, we can also modulo other polynomials; the corresponding situations will be explained below.

### Multi-Point Evaluation and Interpolation of Polynomials

**Multi-point evaluation of polynomials** gives a polynomial $f(x)$ and $n$ points $x_{1}, x_{2}, \dots, x_{n}$, and asks for:

$$
f(x_{1}), f(x_{2}), \dots, f(x_{n})
$$

**Polynomial interpolation** gives $n+1$ points:

$$
(x_{0}, y_{0}), (x_{1}, y_{1}), \dots, (x_{n}, y_{n})
$$

Find an $n$-degree polynomial $f(x)$ such that all $n+1$ points lie on $f(x)$.

The essence of these two operations is converting between **coefficient representation** and **point-value representation** of polynomials. Multi-point evaluation converts coefficient representation to point-value representation, and interpolation converts point-value representation to coefficient representation.

???+ note "Note"
    From the perspective of power series, multi-point evaluation "compresses" infinite-term information into finitely many point values, thus losing some information; interpolation restores to the corresponding degree coefficient representation.
    
    Common programming evaluation and interpolation, such as discrete Fourier transform (and its inverse), choose $n+1$ points with multiplicity 1 (i.e., all different), avoiding the trouble of derivatives.
    
    This "compression" only guarantees consistency at the $n+1$ points. From the explanation of modular polynomial congruence above, if the power series $f(x)$ is evaluated at $x_0$ to $x_n$ and then interpolated to get polynomial $R(x)$, then letting:
    
    $$
    g(x)=(x-x_0)\ldots(x-x_n)
    $$
    
    We have:
    
    $$
    f(x) \equiv R(x) \pmod{g(x)}
    $$
    
    Since the degree of $R(x)$ is strictly less than $g(x)$, the $R(x)$ obtained through evaluation and interpolation is the remainder. Therefore, in this case, if the power series can be evaluated at the roots, it can be modulo a polynomial. A counterexample is:
    
    $$
    \frac{1}{1-x}=1+x+x^2+x^3+\ldots
    $$
    
    It cannot be evaluated at $x=1$, so the series $1+x+x^2+x^3+\ldots$ cannot be modulo the polynomial $x-1$.
    
    Since any-order derivative of a power series always has a value at $0$, modulo $x^n$ can always be computed, consistent with the meaning of "truncation" above. Discrete Fourier transform (and its inverse) is equivalent to modulo the polynomial $x^n-1$.

### Factorization and Euclidean

Many conclusions from elementary number theory can be extended to polynomials.

On the complex field, by the fundamental theorem of algebra, for a degree-$n$ polynomial $f$, the equation:

$$
f(x)=0
$$

Has exactly $n$ solutions (counting multiplicity).

Thus $f(x)$ can be uniquely factored in the complex field as:

$$
a(x-x_1)^{c_1}(x-x_2)^{c_2}\cdots(x-x_m)^{c_m}
$$

$$
c_1+c_2+\cdots+c_m=n,x_1,x_2,\cdots,x_m \text{ are pairwise distinct}
$$

At this point, analogously to the greatest common divisor of positive integers, we can obtain the **greatest common divisor** (gcd) of polynomials. It can be solved using the Euclidean algorithm:

$$
\gcd(f,0)=f,\gcd(f,g)=\gcd(g,f\bmod g)
$$

This property can be extended to more general cases:

> For the polynomial ring $P[x]$ over any field $P$,
> polynomials can be uniquely factored, and the greatest common divisor can be computed using the Euclidean algorithm.
> Note that for polynomials over general rings, this conclusion may not hold.

When the Euclidean algorithm holds, we can use the extended Euclidean algorithm to give a particular solution $(P(x),Q(x))$ for the indefinite equation:

$$
f(x)P(x)+g(x)Q(x)=\gcd(f(x),g(x))
$$

And use [Bézout's theorem](../number-theory/bezouts.md) to judge the solvability of the indefinite equation:

$$
f(x)P(x)+g(x)Q(x)=h(x)
$$

[HALF-GCD](https://loj.ac/p/172) allows us to compute polynomial Euclidean algorithm in $O(n\log^2 n)$ time.

### Multiplicative Inverse Modulo Polynomial

Under the modulus of polynomial $h(x)$, the power series $f(x)$ sometimes has an inverse. The inverse is the remainder obtained by taking the reciprocal of power series $f(x)$ modulo polynomial $h(x)$.

This definition is also equivalent to: for polynomial $f(x)$, if there exists $g(x)$ such that:

$$
\begin{aligned}
    f(x) g(x) & \equiv 1 \pmod{h(x)}
\end{aligned}
$$

Then $g(x)$ is called the **inverse** of $f(x)$ modulo $h(x)$. When polynomial Euclidean algorithm allows, the inverse exists if and only if $\gcd(f,g)=1$.

The inverse modulo $h(x)$ is always unique. If the degree of polynomial $f(x)$ is also less than $h(x)$, the resulting $g(x)$ and $f(x)$ are inverses of each other.

Considering the concept of "truncation", we generally denote the inverse modulo $x^n$ as $f^{-1}(x)$, which is also the inverse concept used by default in later sections. Without specification, the modulus of the inverse is $x^n$.

???+ note "Note"
    One question is: can we directly solve the "inverse" using various interpolation transformations, such as computing:
    
    $$
    IDFT\left(\frac{DFT(1)}{DFT(f(x))}\right)
    $$
    
    The answer is no. According to the explanation above, the inverse directly obtained here using discrete Fourier transform (and its inverse) is the inverse modulo polynomial $x^n-1$, not the usual inverse modulo polynomial $x^n$. Also, since the original polynomial may be $0$ at some point values, this solution may not be possible.

## Generating Functions

A generating function is a formal power series whose coefficients can provide information about the sequence.

There are many different types of generating functions, but they can generally be expressed as a single form:

$$
F(x)=\sum_n a_nk_n(x)
$$

Where $k_n(x)$ is called the kernel function. Different kernel functions lead to different generating functions with different properties. For example:

1.  Ordinary generating function: $k_n(x)=x^n$.
2.  Exponential generating function: $k_n(x)=\dfrac{x^n}{n!}$.
3.  [Dirichlet generating function](../number-theory/dirichlet.md#dirichlet-generating-function): $k_n(x)=\dfrac{1}{n^x}$.

## References and Further Reading

-   [**Picks's Blog**](https://picks.logdown.com)
-   [**Miskcoo's Space**](https://blog.miskcoo.com)
-   [**Polynomial ring - Wikipedia**](https://en.wikipedia.org/wiki/Polynomial_ring)
-   [**Formal power series - Wikipedia**](https://en.wikipedia.org/wiki/Formal_power_series#The_ring_of_formal_power_series)
-   《Computing Theory Framework for Generating Functions in Programming Competitions》
