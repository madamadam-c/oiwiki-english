## Description

Given a polynomial $G\left(x, y\right)$, we know that the polynomial $f\left(x\right)$ satisfies:

$$
G\left(x, f\left(x\right)\right)\equiv 0\pmod{x^{n}}
$$

And there exists a value $f_1$ such that $G\left(x, y\right)$ satisfies:

-   $G(0, f_1) = 0$;
-   $\dfrac{\partial G}{\partial y}(0, f_1) \neq 0$.

Find $f\left(x\right)$ modulo $x^{n}$.

## Newton's Method

Consider doubling.

First, when $n=1$, the solution to $\left[x^{0}\right]G\left(x, f\left(x\right)\right)=0$ needs to be solved separately—$f_1$ in the assumption is such a solution.

Assume we have obtained the solution $f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)$ modulo $x^{\left\lceil\frac{n}{2}\right\rceil}$, and we want to find the solution $f\left(x\right) = f_n\left(x\right)$ modulo $x^{n}$.

Expand $G\left(x, f(x)\right)$ around $f(x)=f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)$ using Taylor expansion:

$$
\sum_{i=0}^{+\infty}\frac{\frac{\partial^i G}{\partial y^i}\left(x, f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)}{i!}\left(f\left(x\right)-f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)^{i}\equiv 0\pmod{x^{n}}
$$

Since the lowest non-zero term of $f\left(x\right)-f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)$ has degree at least $\left\lceil\frac{n}{2}\right\rceil$, we have:

$$
\forall 2\leqslant i:\left(f\left(x\right)-f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)^{i}\equiv 0\pmod{x^{n}}
$$

Thus:

$$
\begin{aligned}
\sum_{i=0}^{+\infty}\frac{\frac{\partial^i G}{\partial y^i}\left(x, f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)}{i!}\left(f\left(x\right)-f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)^{i}&\equiv G\left(x, f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)+\frac{\partial G}{\partial y}\left(x, f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)\left[f\left(x\right)-f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right]\\
&\equiv 0\pmod{x^{n}}
\end{aligned}
$$

$$
f_n\left(x\right)\equiv f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)-\frac{G\left(x, f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)}{\frac{\partial G}{\partial y}\left(x, f_{\left\lceil\frac{n}{2}\right\rceil}\left(x\right)\right)}\pmod{x^{n}}
$$

Or:

$$
f_{2n}\left(x\right)\equiv f_n\left(x\right)-\frac{G\left(x, f_n\left(x\right)\right)}{\frac{\partial G}{\partial y}\left(x, f_n\left(x\right)\right)}\pmod{x^{2n}}
$$

## Example Problems

### [Polynomial Inverse](./elementary-func.md#polynomial-inverse)

Let the given function be $h\left(x\right)$:

$$
G\left(x, y\right)=\frac{1}{y}-h\left(x\right)
$$

Applying Newton's Method:

$$
\begin{aligned}
    f_{2n}\left(x\right)&\equiv f_{n}\left(x\right)-\frac{1/f_{n}\left(x\right)-h\left(x\right)}{-1/f_{n}^{2}\left(x\right)}&\pmod{x^{2n}}\\
    &\equiv 2f_{n}\left(x\right)-f_{n}^{2}\left(x\right)h\left(x\right)&\pmod{x^{2n}}
\end{aligned}
$$

Time complexity:

$$
T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)
$$

### [Polynomial Square Root](./elementary-func.md#polynomial-square-root)

Let the given function be $h\left(x\right)$:

$$
G\left(x, y\right)=y^{2}-h\left(x\right)\equiv 0
$$

Applying Newton's Method:

$$
\begin{aligned}
    f_{2n}\left(x\right)&\equiv f_{n}\left(x\right)-\frac{f_{n}^{2}\left(x\right)-h\left(x\right)}{2f_{n}\left(x\right)}&\pmod{x^{2n}}\\
    &\equiv\frac{f_{n}^{2}\left(x\right)+h\left(x\right)}{2f_{n}\left(x\right)}&\pmod{x^{2n}}
\end{aligned}
$$

Time complexity:

$$
T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)
$$

### [Polynomial Exponential Function](./elementary-func.md#polynomial-logarithmic-function--exponential-function)

Let the given function be $h\left(x\right)$:

$$
G\left(x, y\right)=\ln{y}-h\left(x\right)
$$

Applying Newton's Method:

$$
\begin{aligned}
    f_{2n}\left(x\right)&\equiv f_{n}\left(x\right)-\frac{\ln{f_{n}\left(x\right)}-h\left(x\right)}{1/f_{n}\left(x\right)}&\pmod{x^{2n}}\\
    &\equiv f_{n}\left(x\right)\left(1-\ln{f_{n}\left(x\right)+h\left(x\right)}\right)&\pmod{x^{2n}}
\end{aligned}
$$

Time complexity:

$$
T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)
$$

## Manual Calculation Demonstration

For better understanding, let's demonstrate the algorithm flow with some examples.

### Square Root of Complex Polynomial Mod Polynomial

Assume $h$ is a complex polynomial not divisible by $x$ (has a constant term), find its square root modulo $x^n$.

We have the equation:

$$
G\left(f(x)\right) = f^2(x)-h(x) \equiv 0\pmod{x^{n}}
$$

Expand $G$ using Taylor. Note that this is expansion with respect to $f$, so the derivatives are all partial derivatives with respect to $f$, and $x$ is treated as a constant here.

$$
G(f(x)) = \sum_{i=0}^{+\infty}\frac{G^{\left(i\right)}\left(f_{0}(x)\right)}{i!}\left(f(x)-f_{0}(x)\right)^{i}
= G(f_0(x)) + 2f_0(x)(f(x)-f_0(x)) + (f(x)-f_0(x))^2
$$

Use doubling for calculation. Assume the intermediate results in doubling are $f_0(x), f_1(x), \ldots, f_j(x)$, or more precisely, $f_j(x)$ is a complex polynomial satisfying $G(f_j(x))\equiv 0\pmod{x^{2^j}}$, and for uniqueness it also satisfies:

-   The degree of $f_{j}(x)$ does not exceed $x^{2^j}$;
-   $f_{j+k}(x)-f_j(x)\equiv 0\pmod{x^{2^j}}$ for all $k$.

Substituting $f_{j+1}(x)$ and $f_j(x)$ into the above formula:

$$
G(f_{j+1}(x)) = G(f_j(x)) + 2f_j(f_{j+1}(x)-f_j(x)) + (f_{j+1}(x)-f_{j}(x))^2  \equiv 0 \pmod{x^{2^{j+1}}}
$$

Obviously, $f_{j+1}(x)-f_j(x)$ must be a multiple of $x^{2^j}$. Thus we get:

$$
f_{j+1}(x) \equiv f_j(x) - \frac{f_j^2(x)-h(x)}{2f_j(x)} \equiv \frac{f_j(x)^2 + h(x)}{2f_j(x)} \pmod{x^{2^{j+1}}}
$$

If $f_j(x)$ exists, then $2f_j(x)$ is not divisible by $x$ (has a constant term), so there must be an inverse modulo $x^{2^{j+1}}$. Therefore, the sequence $f_0,f_1\ldots,f_j$ exists if and only if $f_0$ exists. For a complex polynomial $h(x)$ not divisible by $x$, the square root modulo $x$ always exists, because reducing $h(x)$ modulo $x$ is just a non-zero complex number, which definitely has two square roots. So this algorithm can be used for all $h(x)$ with a constant term.

Taking $h(x)=x+1$ as an example for calculation:
-   $f_0(x)=1$, $f_1(x)=\dfrac{1^2+x+1}{2\times 1}\mod x^2 = \dfrac{1}{2}x+1$, $f_2(x)=\dfrac{\left(\dfrac{1}{2}x+1\right)^2+x+1}{2\times \left(\dfrac{1}{2}x+1\right)}\mod x^4 = \dfrac{1}{16}x^3-\dfrac{1}{8}x^2+\dfrac{1}{2}x+1$, $\ldots$
-   $f_0(x)=-1$, $f_1(x)=\dfrac{(-1)^2+x+1}{2\times (-1)}\mod x^2 = -\dfrac{1}{2}x-1$, $\ldots$ (equal to the negative of the previous one)

Both can be verified as correct sequences of modular square root polynomials.

### Square Root of Integer Mod Prime Power

Newton's iteration algorithm can also be applied to the case of integers modulo prime powers.
Assume $h$ is an integer not divisible by 3. ("Convenient" means "must have a solution", specific conditions will be discussed later.) Assume we want to compute the square root of $h$ modulo $3^n$. We have:

$$
G\left(f\right) = f^2-h \equiv 0\pmod{3^{n}}
$$

Expand $G$ using Taylor:

$$
G(f) = \sum_{i=0}^{+\infty}\frac{G^{\left(i\right)}\left(f_{0}\right)}{i!}\left(f-f_{0}\right)^{i}
= G(f_0) + 2f_0(f-f_0) + (f-f_0)^2
$$

Use doubling for calculation. Assume the intermediate results obtained by doubling are $f_0, f_1, \ldots, f_j$, or more precisely, $f_j$ is an integer satisfying $G(f_j)\equiv 0\pmod{3^{2^j}}$, and for uniqueness it also satisfies:

-   $0 < f_{j} < 3^{2^j}$;
-   $f_{j+k}-f_j\equiv 0\pmod{3^{2^j}}$ for all $k$.

Substituting $f_{j+1}$ and $f_j$ into the above formula:

$$
G(f_{j+1}) = G(f_j) + 2f_j(f_{j+1}-f_j) + (f_{j+1}-f_{j})^2  \equiv 0 \pmod{3^{2^{j+1}}}
$$

Obviously, $f_{j+1}-f_j$ must be a multiple of $3^{2^j}$. Thus we get:

$$
f_{j+1} \equiv f_j - \frac{f_j^2-h}{2f_j} \equiv \frac{f_j^2 + h}{2f_j} \pmod{3^{2^{j+1}}}
$$

If $f_j$ exists, then $2f_j$ is not divisible by 3, so there must be an inverse modulo $3^{2^{j+1}}$. Therefore, the sequence $f_0,f_1\ldots,f_j$ exists if and only if $f_0$ exists. For an integer $h$ not divisible by 3, its square root modulo 3 either does not exist or has two. So $h$ having a square root modulo 3 is the only condition for the entire algorithm to run.

Here we take $h=46$ for actual calculation example.
-   $f_0=1$, $f_1=\dfrac{1^2+46}{2\times 1}\mod 9 = 1$, $f_2=\dfrac{1^2+46}{2\times 1}\mod 81 = 64$, $f_3=\dfrac{64^2+46}{2\times 64}\mod 6561 = 955$, $\ldots$
-   $f_0=2$, $f_1=\dfrac{2^2+46}{2\times 2}\mod 9 = 8$, $f_2=\dfrac{8^2+46}{2\times 8}\mod 81 = 17$, $f_3=\dfrac{17^2+46}{2\times 17}\mod 6561 = 5606$, $\ldots$ (equal to the negative of the previous one)

We can verify that both are correct sequences of modular square roots.

## Algebraic Proof

This section extends the previous content, proving in the language of abstract algebra that as long as $f$ satisfies the initial solution condition, Newton's method can give solutions for all $n$, and we can obtain all solutions.

### Proof of Existence of Solutions

???+ note "Lemma 1"
    Let $R$ be an [integral domain](../algebra/ring-theory.md#integral-domain) with a polynomial or [formal power series](../algebra/ring-theory.md#formal-power-series-ring) $f(X) = \sum_{i\geq 0}a_iX^i$ and $r,p\in R$ such that $f(r)\in Rp$ (i.e., $r$ is a root of $f(X)$ modulo $p$) and $f'(r)\in R$ is invertible modulo $p$. Here $f'(X) := \sum_{i\geq 0}(i+1)a_{i+1}X^i$ is the **formal derivative** of $f(X)$. Then $f\left(r-\dfrac{f(r)}{f'(r)}\right) \equiv 0\pmod {p^2}$.

??? note "Proof"
    For all $s\in R$:
    
    $$
    \begin{aligned}
    f(r+sp) &= \sum_{i\geq 0}a_i(r+sp)^i \\
    &= \sum_{i\geq 0}a_ir^i + sp\sum_{i\geq 1}ia_ir^{i-1} + s^2p^2\left(\ldots\right) \\
    &= f(r) + spf'(r) + s^2p^2\left(\frac{f''(r)}{2!} + \cdots\right),
    \end{aligned}
    $$
    
    So:
    
    $$
    f(r+sp) \in Rp^2 \iff f(r)+f'(r)sp \in Rp^2
    $$
    
    Since $f(r)\in Rp$ and $f'(r)$ is invertible, taking $sp = -\dfrac{f(r)}{f'(r)}$ works. Here $\dfrac{1}{f'(r)}$ is the inverse modulo $p^2$. Since $f'(r)$ is invertible modulo $p$, it must also have an inverse modulo $p^2$: let $a,b,c\in R$ satisfy $af'(r) = bp+1$ and $f(r)=cp$, then $\left(a^2f'(r)-2\right)f'(r) = b^2p^2+1$, so we can take $s=c(2-a^2f'(r))$.

For a polynomial ring $k[X]$ over a field $k$, with $G(X, Y)\in k[X, Y]$ and $f_n\in k[X]$ such that $G(X, f_n(X))\in k[X]X^n$, applying Lemma 1 yields:

$$
G\left(X, f_n(X) - \frac{G(X, f_n(X))}{\frac{\partial G}{\partial Y}(X, f_n(X))} \right)\equiv 0 \pmod {X^{2n}}
$$

The initial condition for doubling only requires $f_1\in k$ such that $G(X, f_1)\equiv 0\pmod X$ and $\dfrac{\partial G}{\partial Y}(X, f_1)\not\equiv 0\pmod X$. The latter condition guarantees that $\dfrac{\partial G}{\partial Y}$ has a non-zero constant term, and since $X\left| \dfrac{G(X, f_n(X))}{\frac{\partial G}{\partial Y}(X, f_n(X))} \right.$, $\dfrac{\partial G}{\partial Y}(X, f_n)$ is always invertible modulo $X^n$, satisfying the condition for the next iteration.

### Proof of Obtaining All Solutions

???+ note "Lemma 2"
    If $R$ is a [UFD](../algebra/ring-theory.md#unique-factorization-domain), with $f,r,p$ defined as in Lemma 1. Then the $r-\dfrac{f(r)}{f'(r)}$ given by Lemma 1 is the unique value of $x$ modulo $p^{2}$ satisfying:
    
    -   $f(x)\in Rp^{2}$
    -   $x-r\in Rp$
    
    That is:
    
    $$
    \forall x\in R,\qquad p^2\mid f(x)\wedge p\mid (x-r) \implies x\equiv r-\dfrac{f(r)}{f'(r)} \pmod {p^2}
    $$

??? note "Proof"
    Let $s = -\dfrac{f(r)}{f'(r)p}$ and $u = r+sp$. Lemma 1 guarantees $u$ satisfies both conditions, and $f(r) + f'(r)sp \in Rp^{2}$.
    Let $v$ be a value satisfying the above conditions, so $v = r+tp$ and $f(r) + f'(r)tp \in Rp^{2}$.
    Then $f'(r)(t-s)p\in Rp^{2}$ and $v-u\in Rp^{2}$.

Newton's method can guarantee obtaining all solutions modulo $X^{2^n}$. Assume $G(X, h)\equiv 0\pmod {X^{2^n}}$, then let $h_{2^i} := h\pmod {X^{2^i}}$, take $f_1 = h_1$ and use Newton's method. According to Lemma 2, we have $f_{2^i} \equiv h_{2^i}\pmod {X^{2^i}}$, so definitely $f_{2^n} = h$.

The above argument also shows that when $\dfrac{\partial G}{\partial y}(0, y)$ is always invertible, the number of solutions to $G(X, f)\equiv 0\pmod {X^n}$ equals the number of solutions to $G(0, f)\equiv 0\pmod X$. This conclusion is non-trivial. See the following example.

??? example "Example where the number of solutions increases with degree when Newton's method fails"
    Modulo $X$, the square root of $X^2$ only has $0$, but modulo $X^4$, the square roots of $X^2$ include $X, -X, X^3+X, \ldots$.