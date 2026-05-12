## Definition

Any complex-coefficient univariate polynomial equation of degree $n$ (with $n$ at least 1) has at least one root in the complex number field.

From this, a degree-$n$ complex-coefficient polynomial equation has exactly $n$ roots in the complex number field, with repeated roots counted by multiplicity.

Sometimes this theorem is also stated as:

Any non-zero univariate degree-$n$ complex-coefficient polynomial has exactly $n$ complex roots.

The proof of the Fundamental Theorem of Algebra generally uses complex analysis or modern algebra, so it's often treated as a well-known fact and directly applied.

According to the Fundamental Theorem of Algebra, a complex-coefficient polynomial $f(x)=a_nx^n+a_{n-1}x^{n-1}+\ldots+a_0$ can be uniquely factored as:

$$
f(x)=a_n{(x-x_1)}^{k_1}{(x-x_2)}^{k_2}\ldots{(x-x_t)}^{k_t}
$$

Where all roots are complex numbers, and $k_1+k_2+\ldots+k_t=n$.

## Conjugate Root Theorem

The Fundamental Theorem of Algebra deals with complex-coefficient polynomials. When studying real-coefficient polynomials, although we can also factor out complex roots, we need to expand the scope of study, which is inconvenient.

Non-real root: non-real number root.

Theorem: The conjugate complex number of a root of a real-coefficient polynomial is also a root of that polynomial.

Proof: Directly take conjugates on both sides of the Fundamental Theorem of Algebra equation to complete the proof.

If the root itself is a real number, taking the conjugate still gives itself and is unaffected.

If the root is a non-real root, the conjugate complex number of the non-real root is also a root of the original polynomial. Thus, two non-real roots can be paired.

Theorem: Conjugate non-real roots of a real-coefficient equation must appear in pairs, and the multiplicities of conjugate non-real roots are equal.

Proof: Assume one root is $a+b\mathrm{i}$, then the other root is $a-b\mathrm{i}$. This means there are two terms in the factorization:

$$
(x-a-b\mathrm{i})(x-a+b\mathrm{i})=x^2-2ax+a^2+b^2
$$

It can be seen that when multiplying these two terms, all coefficients become real numbers. This quadratic real-coefficient polynomial on the right side divides the original polynomial.

Thus, in the Fundamental Theorem of Algebra equation, dividing both sides by this quadratic polynomial and performing the same operation on the new equation, after repeated operations as the degree decreases, there will eventually be no non-real roots after several times.

Therefore, the multiplicities of each pair of conjugate non-real roots are equal. Proof complete.

The following are corollaries of the conjugate root theorem:

-   A real-coefficient odd-degree polynomial has at least one real root, and has an odd number of total real roots.
-   A real-coefficient even-degree polynomial may have no real roots, and has an even number of total real roots.

The quadratic polynomial $x^2-2ax+a^2+b^2=x^2+px+q$ above is called a quadratic irreducible factor over reals. "Irreducible" means it cannot be reduced within the real number range.

Theorem: A real-coefficient polynomial can always be factored into a product of linear or quadratic irreducible factors over reals.

Proof:

If a real-coefficient polynomial has a real root $c$, then there is a real-coefficient factor $x-c$ corresponding to it; if it has a pair of non-real roots $a\pm b\mathrm{i}$, then there is a real-coefficient factor $x^2-2ax+a^2+b^2$ corresponding to it.

Therefore, as long as we pair using the conjugate root theorem in the Fundamental Theorem of Algebra factorization, the proof is complete.

According to the conjugate root theorem, a real-coefficient polynomial $f(x)=a_nx^n+a_{n-1}x^{n-1}+\ldots+a_0$ can be uniquely factored as:

$$
f(x)=a_n{(x-x_1)}^{k_1}{(x-x_2)}^{k_2}\ldots{(x-x_t)}^{k_t}{(x^2+p_1x+q_1)}^{l_1}{(x^2+p_2x+q_2)}^{l_2}\ldots{(x^2+p_sx+q_s)}^{l_s}
$$

Where all coefficients are real numbers, and $k_1+k_2+\ldots+k_t+2(l_1+l_2+\ldots+l_s)=n$.

## Lin's Algorithm

### Introduction

How to perform the Fundamental Theorem of Algebra factorization on real-coefficient polynomials? Expanding the number field to complex numbers is complicated.

If we only factor within the real number range, we can only guarantee that when the degree is greater than $2$, there must be a real-coefficient quadratic factor.

This is because: if the polynomial has non-real roots, we can directly form a pair of conjugate non-real roots. If the polynomial has only real roots, multiplying the linear factors corresponding to any two real roots also yields a real-coefficient quadratic factor.

After finding the quadratic factor, solving real or complex roots from the quadratic equation becomes extremely easy. Thus, there is a calculation method for finding complex roots of higher-order equations by "finding a quadratic factor" step by step. This method avoids complex number operations.

In August 1940, August 1943, and July 1947, Lin Shie successively published three papers on methods for calculating complex roots of higher-order equations in the "Mathematical Physics" journal published by MIT[^note1], each with improvements.

This method is still used for fast calculations in modern computers. The polynomial root program in computer software packages (such as MATLAB) also follows this algorithm.

### Process

To find a quadratic factor, we need to decompose the polynomial as:

$$
f(x)=(x^2+p_1x+q_1)g(x)
$$

Since we cannot find the quadratic factor at once, following the idea of iterative solution, for initial values we have:

$$
f(x)=(x^2+px+q)g(x)+rx+s
$$

This will generate a linear term as the remainder. As long as the remainder is small enough, we can approximately find the factor we seek.

We want the final solution to be the initial value plus an offset correction:

$$
p_1=p+dp
$$

$$
q_1=q+dq
$$

The two numbers $(r, s)$ in the remainder are determined by the given coefficients $(p, q)$ of the divisor. There are partial derivative relationships:

$$
dr=\frac{\partial r}{\partial p}dp+\frac{\partial r}{\partial q}dq
$$

$$
ds=\frac{\partial s}{\partial p}dp+\frac{\partial s}{\partial q}dq
$$

In the initial equation, the dividend $f(x)$ is given, and the quotient $g(x)$ and remainder $rx+s$ vary with the divisor $x^2+px+q$. So there are partial derivative relationships:

$$
0=xg(x)+\frac{\partial g(x)}{\partial p}(x^2+px+q)+\frac{\partial r}{\partial p}x+\frac{\partial s}{\partial p}
$$

$$
0=g(x)+\frac{\partial g(x)}{\partial q}(x^2+px+q)+\frac{\partial r}{\partial q}x+\frac{\partial s}{\partial q}
$$

Note that the partial derivative is just a numerical value, independent of the variable $x$. So there are divisibility relationships:

$$
xg(x)=-\frac{\partial g(x)}{\partial p}(x^2+px+q)-\frac{\partial r}{\partial p}x-\frac{\partial s}{\partial p}
$$

$$
g(x)=-\frac{\partial g(x)}{\partial q}(x^2+px+q)-\frac{\partial r}{\partial q}x-\frac{\partial s}{\partial q}
$$

Here, the conclusion is that the partial derivatives we seek are exactly the remainders from continuing to divide the quotient. The division of a polynomial by a given quadratic can be computed directly. Here we obtain four partial derivatives.

We want $s$ and $r$ plus offsets $ds$ and $dr$ to get $0$, i.e., $ds$ and $dr$ are the opposites of $s$ and $r$. So we need to solve the equations:

$$
-\frac{\partial r}{\partial p}dp-\frac{\partial r}{\partial q}dq=r
$$

$$
-\frac{\partial s}{\partial p}dp-\frac{\partial s}{\partial q}dq=s
$$

From these equations, we solve for the offsets $dp$ and $dq$ corresponding to $p$ and $q$, which can be directly solved using second-order determinants.

### Implementation

```C
// a is the original polynomial, n is the degree of the polynomial, p is the term to be solved, q is the constant term to be solved
void Shie(double a[], int n, double *p, double *q) {
  // Array b is the quotient of polynomial a divided by the current iterative quadratic
  memset(b, 0, sizeof(b));
  // Array c is the quotient of polynomial b multiplied by x squared and then divided by the current iterative quadratic
  memset(c, 0, sizeof(c));
  *p = 0;
  *q = 0;
  double dp = 1;
  double dq = 1;
  while (dp > eps || dp < -eps || dq > eps || dq < -eps)  // eps set by yourself
  {
    double p0 = p;
    double q0 = q;
    b[n - 2] = a[n];
    c[n - 2] = b[n - 2];
    b[n - 3] = a[n - 1] - p0 * b[n - 2];
    c[n - 3] = b[n - 3] - p0 * b[n - 2];
    int j;
    for (j = n - 4; j >= 0; j--) {
      b[j] = a[j + 2] - p0 * b[j + 1] - q0 * b[j + 2];
      c[j] = b[j] - p0 * c[j + 1] - q0 * c[j + 2];
    }
    double r = a[1] - p0 * b[0] - q0 * b[1];
    double s = a[0] - q0 * b[0];
    double rp = c[1];
    double sp = b[0] - q0 * c[2];
    double rq = c[0];
    double sq = -q0 * c[1];
    dp = (rp * s - r * sp) / (rp * sq - rq * sp);
    dq = (r * sq - rq * s) / (rp * sq - rq * sp);
    *p += dp;
    *q += dq;
  }
}
```

## References and Notes

[^note1]: [Lin Shie. On the Application of the Split-Factor Method to Solve High-Order Characteristic Equations. Advances in Mathematics, 1963(03):207-217.](https://cnki.net/kcms/detail/detail.aspx?filename=SXJZ196303000&dbcode=CJFD&dbname=CJFD1979)