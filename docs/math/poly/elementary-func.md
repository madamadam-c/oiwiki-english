author: 97littleleaf11, abc1763613206, CCXXXI, EndlessCheng, Enter-tainer, fps5283, Great-designer, H-J-Granger, hly1204, hsfzLZH1, huayucaiji, Ir1d, kenlig, Marcythm, ouuan, SamZhangQingChuan, shuzhouliu, sshwy, StudyingFather, test12345-pupil, Tiphereth-A, TrisolarisHD, untitledunrevised

This page contains common elementary function operations on polynomials. Specifically, this page includes:

1.  Polynomial inverse
2.  Polynomial square root
3.  Polynomial division
4.  Polynomial modulo
5.  Polynomial exponential function
6.  Polynomial logarithmic function
7.  Polynomial trigonometric functions
8.  Polynomial inverse trigonometric functions

??? note "Elementary Functions and Non-Elementary Functions"
    The definition of elementary functions is as follows[^ref1]:
    
    If there exists a mapping $u\to \partial u$ in a field $F$ satisfying:
    
    1.  $\partial(u+v)=\partial u+\partial v$
    2.  $\partial(uv)=u\partial v+v\partial u$
    
    Then this field is called a **differential field**.
    
    If a function $u$ on a differential field $F$ satisfies any of the following conditions, it is called an elementary function:
    
    1.  $u$ is an algebraic function on $F$.
    2.  $u$ is an exponential function on $F$, i.e., there exists $a\in F$ such that $\partial u=u\partial a$.
    3.  $u$ is a logarithmic function on $F$, i.e., there exists $a\in F$ such that $\partial u=\frac{\partial a}{a}$.
    
    The following are common elementary functions:
    
    1.  Algebraic function: function $f(x)$ where there exists a finite polynomial $P$ such that $P(f(x))=0$, e.g., $2x+1$,$\sqrt{x}$,$(1+x^2)^{-1}$,$|x|$.
    2.  Exponential function
    3.  Logarithmic function
    4.  Trigonometric functions
    5.  Inverse trigonometric functions
    6.  Hyperbolic functions
    7.  Inverse hyperbolic functions
    8.  Compositions of the above functions, e.g.:
    
        $$
        \frac{\mathrm{e}^{\tan x}}{1+x^2}\sin\left(\sqrt{1+\ln^2 x}\right)
        $$
    
        $$
        -\mathrm{i} \ln\left(x+\mathrm{i}\sqrt{1-x^2}\right)
        $$
    
    The following are common non-elementary functions:
    
    1.  Error function:
    
        $$
        \operatorname{erf}(x):=\frac{2}{\sqrt{\pi}}\int_{0}^{x}\exp\left(-t^2\right)\mathrm{d}t
        $$

## Polynomial Inverse

Given a polynomial $f\left(x\right)$, find $f^{-1}\left(x\right)$.

### Solution

#### Doubling Method

First, it is easy to know:

$$
\left[x^{0}\right]f^{-1}\left(x\right)=\left(\left[x^{0}\right]f\left(x\right)\right)^{-1}
$$

Assume we have already found the inverse $f^{-1}_{0}\left(x\right)$ of $f\left(x\right)$ modulo $x^{\left\lceil\frac{n}{2}\right\rceil}$. We have:

$$
\begin{aligned}
    f\left(x\right)f^{-1}_{0}\left(x\right)&\equiv 1 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
    f\left(x\right)f^{-1}\left(x\right)&\equiv 1 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
    f^{-1}\left(x\right)-f^{-1}_{0}\left(x\right)&\equiv 0 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}
\end{aligned}
$$

Squaring both sides:

$$
f^{-2}\left(x\right)-2f^{-1}\left(x\right)f^{-1}_{0}\left(x\right)+f^{-2}_{0}\left(x\right)\equiv 0 \pmod{x^{n}}
$$

Multiplying both sides by $f\left(x\right)$ and rearranging:

$$
f^{-1}\left(x\right)\equiv f^{-1}_{0}\left(x\right)\left(2-f\left(x\right)f^{-1}_{0}\left(x\right)\right) \pmod{x^{n}}
$$

Compute recursively.

**Time Complexity**:

$$
T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)
$$

#### Newton's Method

See [Newton's Method](./newton.md#newtons-method).

#### Graeffe's Method

To find $f^{-1}(x)\bmod x^{2n}$, consider:

$$
\begin{aligned}
f^{-1}(x)\bmod x^{2n}&= f(-x)(f(x)f(-x))^{-1}\bmod x^{2n}\\
&=f(-x)g^{-1}(x^2)\bmod x^{2n}
\end{aligned}
$$

We only need to find $g^{-1}(x)\bmod x^n$ to restore $g^{-1}(x^2)\bmod x^{2n}$ because $f(x)f(-x)$ is an even function. Time complexity is the same.

### Code

??? note "Polynomial Inverse"
    ```cpp
    constexpr int MAXN = 262144;
    constexpr int mod = 998244353;
    
    using i64 = long long;
    using poly_t = int[MAXN];
    using poly = int *const;
    
    void polyinv(const poly &h, const int n, poly &f) {
      /* f = 1 / h = f_0 (2 - f_0 h) */
      static poly_t inv_t;
      std::fill(f, f + n + n, 0);
      f[0] = fpow(h[0], mod - 2);
      for (int t = 2; t <= n; t <<= 1) {
        const int t2 = t << 1;
        std::copy(h, h + t, inv_t);
        std::fill(inv_t + t, inv_t + t2, 0);
    
        DFT(f, t2);
        DFT(inv_t, t2);
        for (int i = 0; i != t2; ++i)
          f[i] = (i64)f[i] * sub(2, (i64)f[i] * inv_t[i] % mod) % mod;
        IDFT(f, t2);
    
        std::fill(f + t, f + t2, 0);
      }
    }
    ```

### Example Problems

1.  Counting labeled simple connected graphs: ["POJ 1737" Connected Graph](http://poj.org/problem?id=1737)

## Polynomial Square Root

Given polynomial $g\left(x\right)$, find $f\left(x\right)$ such that:

$$
f^{2}\left(x\right)\equiv g\left(x\right) \pmod{x^{n}}
$$

### Solution

#### Doubling Method

First, discuss the case where $\left[x^0\right]g(x)$ is not $0$.

We know:

$$
\left[x^0\right]f(x) = \sqrt{\left[x^0\right]g(x)}
$$

If $\left[x^0\right]g(x)$ has no square root, then polynomial $g(x)$ has no square root.

> $\left[x^0\right]g(x)$ may have multiple square roots; choosing different roots yields different $f(x)$.

Assume we have already found the square root $f_{0}\left(x\right)$ of $g\left(x\right)$ modulo $x^{\left\lceil\frac{n}{2}\right\rceil}$:

$$
\begin{aligned}
    f_{0}^{2}\left(x\right)&\equiv g\left(x\right) &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
    f_{0}^{2}\left(x\right)-g\left(x\right)&\equiv 0 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
    \left(f_{0}^{2}\left(x\right)-g\left(x\right)\right)^{2}&\equiv 0 &\pmod{x^{n}}\\
    \left(f_{0}^{2}\left(x\right)+g\left(x\right)\right)^{2}&\equiv 4f_{0}^{2}\left(x\right)g\left(x\right) &\pmod{x^{n}}\\
    \left(\frac{f_{0}^{2}\left(x\right)+g\left(x\right)}{2f_{0}\left(x\right)}\right)^{2}&\equiv g\left(x\right) &\pmod{x^{n}}\\
    \frac{f_{0}^{2}\left(x\right)+g\left(x\right)}{2f_{0}\left(x\right)}&\equiv f\left(x\right) &\pmod{x^{n}}\\
    2^{-1}f_{0}\left(x\right)+2^{-1}f_{0}^{-1}\left(x\right)g\left(x\right)&\equiv f\left(x\right) &\pmod{x^{n}}
\end{aligned}
$$

Compute by doubling.

**Time Complexity**:

$$
T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)
$$

There is also a method with smaller constant: while maintaining $f\left(x\right)$ by doubling, also maintain $f^{-1}\left(x\right)$ instead of computing the inverse every time.

> When $\left[x^{0}\right]g\left(x\right)\neq 1$, quadratic residues may be needed to compute $\left[x^{0}\right]f\left(x\right)$.

The above method requires knowing the inverse of $f_{0}(x)$, so the constant term cannot be $0$.

If $\left[x^0\right]g(x) = 0$, decompose $g(x)$ as $x^{k}h(x)$, where $\left[x^0\right]h(x) \neq 0$.

-   If $k$ is odd, then $g(x)$ has no square root.
-   If $k$ is even, find the square root $\sqrt{h(x)}$ of $h(x)$, then get $f(x) \equiv x^{k/2} \sqrt{h(x)} \pmod{x^{n}}$.

??? note "Luogu Template Problem [P5205【Template】Polynomial Square Root](https://www.luogu.com.cn/problem/P5205) Reference Code"
    ```cpp
    --8<-- "docs/math/code/poly/sqrt/sqrt_1.cpp"
    ```

#### Newton's Method

See [Newton's Method](./newton.md#newtons-method).

### Example Problems

1.  ["Codeforces Round #250" E. The Child and Binary Tree](https://codeforces.com/contest/438/problem/E)

## Polynomial Division & Modulo

Given polynomials $f\left(x\right),g\left(x\right)$, find the quotient $Q\left(x\right)$ and remainder $R\left(x\right)$ when $g\left(x\right)$ divides $f\left(x\right)$.

### Solution

Find that if we can eliminate the effect of $R\left(x\right)$, we can directly solve it using [Polynomial Inverse](#polynomial-inverse).

Consider the transformation:

$$
f^{R}\left(x\right)=x^{\operatorname{deg}{f}}f\left(\frac{1}{x}\right)
$$

Observe that this is reversing the coefficients of $f\left(x\right)$.

Let $n=\operatorname{deg}{f},m=\operatorname{deg}{g}$.

Replace $x$ with $\frac{1}{x}$ in $f\left(x\right)=Q\left(x\right)g\left(x\right)+R\left(x\right)$ and multiply both sides by $x^{n}$:

$$
\begin{aligned}
    x^{n}f\left(\frac{1}{x}\right)&=x^{n-m}Q\left(\frac{1}{x}\right)x^{m}g\left(\frac{1}{x}\right)+x^{n-m+1}x^{m-1}R\left(\frac{1}{x}\right)\\
    f^{R}\left(x\right)&=Q^{R}\left(x\right)g^{R}\left(x\right)+x^{n-m+1}R^{R}\left(x\right)
\end{aligned}
$$

Note that the coefficients of $R^{R}\left(x\right)$ in the above equation are of degree $x^{n-m+1}$, so we can eliminate the effect of $R^{R}\left(x\right)$ by taking modulo $x^{n-m+1}$.

Since $Q^{R}\left(x\right)$ has degree $(n-m)<(n-m+1)$, $Q^{R}\left(x\right)$ is not affected.

Thus:

$$
f^{R}\left(x\right)\equiv Q^{R}\left(x\right)g^{R}\left(x\right)\pmod{x^{n-m+1}}
$$

Use polynomial inverse to find $Q\left(x\right)$, then substitute back to get $R\left(x\right)$.

**Time Complexity**: $O\left(n\log{n}\right)$.

## Polynomial Logarithmic Function & Exponential Function

Given polynomial $f(x)$, find $\ln{f(x)}$ and $\exp{f(x)}$ modulo $x^{n}$.

### Solution

#### Ordinary Method

=== "Polynomial Logarithmic Function"
    First, for polynomial $f(x)$, if $\ln{f(x)}$ exists, by its [definition](./intro.md#composition), it must satisfy:
    
    $$
    [x^{0}]f(x)=1
    $$
    
    Differentiate $\ln{f(x)}$ and integrate:
    
    $$
    \begin{aligned}
        \frac{\mathrm{d} \ln{f(x)}}{\mathrm{d} x} & \equiv \frac{f'(x)}{f(x)} & \pmod{x^{n}} \\
        \ln{f(x)} & \equiv \int \mathrm{d} \ln{f(x)} \equiv \int\frac{f'(x)}{f(x)} \mathrm{d} x & \pmod{x^{n}}
    \end{aligned}
    $$
    
    Polynomial differentiation and integration take $O(n)$ time, and inverse takes $O(n\log{n})$ time. So polynomial logarithm takes $O(n\log{n})$ time.

=== "Polynomial Exponential Function"
    First, for polynomial $f(x)$, if $\exp{f(x)}$ exists, it must satisfy:
    
    $$
    [x^{0}]f(x)=0
    $$
    
    Otherwise, the constant term of $\exp{f(x)}$ does not converge.
    
    Differentiate $\exp{f(x)}$:
    
    $$
    \frac{\mathrm{d} \exp{f(x)}}{\mathrm{d} x} \equiv \exp{f(x)}f'(x)\pmod{x^{n}}
    $$
    
    Equating coefficients:
    
    $$
    [x^{n-1}]\frac{\mathrm{d} \exp{f(x)}}{\mathrm{d} x} = \sum_{i = 0}^{n - 1} \left([x^{i}]\exp{f(x)}\right) \left([x^{n-i-1}]f'(x)\right)
    $$
    
    $$
    n[x^{n}]\exp{f(x)} = \sum_{i = 0}^{n - 1} \left([x^{i}]\exp{f(x)}\right) \left((n - i)[x^{n - i}]f(x)\right)
    $$
    
    This can be solved using divide-and-conquer FFT.
    
    **Time Complexity**: $O(n\log^{2}{n})$.

#### Newton's Method

Using [Newton's Method](./newton.md#newtons-method), we can solve polynomial exp in $O(n\log{n})$ time.

### Code

??? note "Polynomial ln/exp"
    ```cpp
    constexpr int MAXN = 262144;
    constexpr int mod = 998244353;
    
    using i64 = long long;
    using poly_t = int[MAXN];
    using poly = int *const;
    
    void derivative(const poly &h, const int n, poly &f) {
      for (int i = 1; i != n; ++i) f[i - 1] = (i64)h[i] * i % mod;
      f[n - 1] = 0;
    }
    
    void integrate(const poly &h, const int n, poly &f) {
      for (int i = n - 1; i; --i) f[i] = (i64)h[i - 1] * inv[i] % mod;
      f[0] = 0; /* C */
    }
    
    void polyln(const poly &h, const int n, poly &f) {
      /* f = ln h = ∫ h' / h dx */
      assert(h[0] == 1);
      static poly_t ln_t;
      const int t = n << 1;
    
      derivative(h, n, ln_t);
      std::fill(ln_t + n, ln_t + t, 0);
      polyinv(h, n, f);
    
      DFT(ln_t, t);
      DFT(f, t);
      for (int i = 0; i != t; ++i) ln_t[i] = (i64)ln_t[i] * f[i] % mod;
      IDFT(ln_t, t);
    
      integrate(ln_t, n, f);
    }
    
    void polyexp(const poly &h, const int n, poly &f) {
      /* f = exp(h) = f_0 (1 - ln f_0 + h) */
      assert(h[0] == 0);
      static poly_t exp_t;
      std::fill(f, f + n + n, 0);
      f[0] = 1;
      for (int t = 2; t <= n; t <<= 1) {
        const int t2 = t << 1;
    
        polyln(f, t, exp_t);
        exp_t[0] = sub(pls(h[0], 1), exp_t[0]);
        for (int i = 1; i != t; ++i) exp_t[i] = sub(h[i], exp_t[i]);
        std::fill(exp_t + t, exp_t + t2, 0);
    
        DFT(f, t2);
        DFT(exp_t, t2);
        for (int i = 0; i != t2; ++i) f[i] = (i64)f[i] * exp_t[i] % mod;
        IDFT(f, t2);
    
        std::fill(f + t, f + t2, 0);
      }
    }
    ```

### Example Problems

1.  Compute $f^{k}(x)$
    
    The ordinary method is polynomial fast exponentiation, with time complexity $O(n\log{n}\log{k})$.
    
    When $[x^{0}]f(x)=1$:
    
    $$
    f^{k}(x)=\exp{\left(k\ln{f(x)}\right)}
    $$
    
    When $[x^{0}]f(x)\neq 1$, let the lowest degree term of $f(x)$ be $f_{i}x^{i}$:
    
    $$
    f^{k}(x)=f_{i}^{k}x^{ik}\exp{\left(k\ln{\frac{f(x)}{f_{i}x^{i}}}\right)}
    $$
    
    **Time Complexity**: $O(n\log{n})$.

## Polynomial Trigonometric Functions

Given polynomial $f\left(x\right)$, find $\sin{f\left(x\right)}, \cos{f\left(x\right)}$ and $\tan{f\left(x\right)}$ modulo $x^{n}$.

### Solution

First, from [Euler's formula](../complex.md#euler-formula) ($\mathrm{e}^{\mathrm{i}x} = \cos{x} + \mathrm{i}\sin{x}$), we can get [another expression of trigonometric functions](https://en.wikipedia.org/wiki/Trigonometric_functions#Relationship_to_exponential_function_and_complex_numbers):

$$
\begin{aligned}
    \sin{x} &= \frac{\mathrm{e}^{\mathrm{i}x} - \mathrm{e}^{-\mathrm{i}x}}{2\mathrm{i}} \\
    \cos{x} &= \frac{\mathrm{e}^{\mathrm{i}x} + \mathrm{e}^{-\mathrm{i}x}}{2}
\end{aligned}
$$

Then substituting $f\left(x\right)$:

$$
\begin{aligned}
    \sin{f\left(x\right)} &= \frac{\exp{\left(\mathrm{i}f\left(x\right)\right)} - \exp{\left(-\mathrm{i}f\left(x\right)\right)}}{2\mathrm{i}} \\
    \cos{f\left(x\right)} &= \frac{\exp{\left(\mathrm{i}f\left(x\right)\right)} + \exp{\left(-\mathrm{i}f\left(x\right)\right)}}{2}
\end{aligned}
$$

We can directly write the program according to the above expression to get $\sin{f\left(x\right)}$ and $\cos{f\left(x\right)}$ modulo $x^{n}$. Then $\tan{f\left(x\right)} = \frac{\sin{f\left(x\right)}}{\cos{f\left(x\right)}}$ can be used to find $\tan{f\left(x\right)}$.

### Code

??? note "Polynomial Trigonometric Functions"
    Note that we are doing NTT on $\mathbb{Z}_{998244353}$, so the imaginary unit $\mathrm{i}$ should be replaced by $86583718$ or $911660635$:
    
    $$
    \begin{aligned}
               & \mathrm{i} = \sqrt{-1} \equiv \sqrt{998244352} \pmod{998244353}       \\
       \implies & \phantom{\text{or}} \quad \mathrm{i} \equiv 86583718 \pmod{998244353} \\
                & \text{or} \quad \mathrm{i} \equiv 911660635 \pmod{998244353}
    \end{aligned}
    $$
    
    ```cpp
    constexpr int MAXN = 262144;
    constexpr int mod = 998244353;
    constexpr int imgunit = 86583718; /* sqrt(-1) = sqrt(998233452) */
    
    using i64 = long long;
    using poly_t = int[MAXN];
    using poly = int *const;
    
    void polytri(const poly &h, const int n, poly &sin_t, poly &cos_t) {
      /* sin(f) = (exp(i * f) - exp(- i * f)) / 2i */
      /* cos(f) = (exp(i * f) + exp(- i * f)) / 2 */
      /* tan(f) = sin(f) / cos(f) */
      assert(h[0] == 0);
      static poly_t tri1_t, tri2_t;
    
      for (int i = 0; i != n; ++i) tri2_t[i] = (i64)h[i] * imgunit % mod;
      polyexp(tri2_t, n, tri1_t);
      polyinv(tri1_t, n, tri2_t);
    
      if (sin_t != nullptr) {
        const int invi = fpow(pls(imgunit, imgunit), mod - 2);
        for (int i = 0; i != n; ++i)
          sin_t[i] = (i64)(tri1_t[i] - tri2_t[i] + mod) * invi % mod;
      }
      if (cos_t != nullptr) {
        for (int i = 0; i != n; ++i) cos_t[i] = div2(pls(tri1_t[i], tri2_t[i]));
      }
    }
    ```

## Polynomial Inverse Trigonometric Functions

Given polynomial $f\left(x\right)$, find $\arcsin{f\left(x\right)}, \arccos{f\left(x\right)}$ and $\arctan{f\left(x\right)}$ modulo $x^{n}$.

### Solution

Mimicking the method for polynomial $\ln$, differentiate inverse trigonometric functions and integrate:

$$
\begin{aligned}
    \frac{\mathrm{d}}{\mathrm{d} x} \arcsin{x} &= \frac{1}{\sqrt{1 - x^{2}}} \\
    \arcsin{x} &= \int \frac{1}{\sqrt{1 - x^{2}}} \mathrm{d} x \\
    \frac{\mathrm{d}}{\mathrm{d} x} \arccos{x} &= - \frac{1}{\sqrt{1 - x^{2}}} \\
    \arccos{x} &= - \int \frac{1}{\sqrt{1 - x^{2}}} \mathrm{d} x \\
    \frac{\mathrm{d}}{\mathrm{d} x} \arctan{x} &= \frac{1}{1 + x^{2}} \\
    \arctan{x} &= \int \frac{1}{1 + x^{2}} \mathrm{d} x
\end{aligned}
$$

Then substituting $f\left(x\right)$:

$$
\begin{aligned}
    \frac{\mathrm{d}}{\mathrm{d} x} \arcsin{f\left(x\right)} &= \frac{f'\left(x\right)}{\sqrt{1 - f^{2}\left(x\right)}} \\
    \arcsin{f\left(x\right)} &= \int \frac{f'\left(x\right)}{\sqrt{1 - f^{2}\left(x\right)}} \mathrm{d} x \\
    \frac{\mathrm{d}}{\mathrm{d} x} \arccos{f\left(x\right)} &= - \frac{f'\left(x\right)}{\sqrt{1 - f^{2}\left(x\right)}} \\
    \arccos{f\left(x\right)} &= - \int \frac{f'\left(x\right)}{\sqrt{1 - f^{2}\left(x\right)}} \mathrm{d} x \\
    \frac{\mathrm{d}}{\mathrm{d} x} \arctan{f\left(x\right)} &= \frac{f'\left(x\right)}{1 + f^{2}\left(x\right)} \\
    \arctan{f\left(x\right)} &= \int \frac{f'\left(x\right)}{1 + f^{2}\left(x\right)} \mathrm{d} x
\end{aligned}
$$

Just compute directly according to the formula.

### Code

??? note "Polynomial Inverse Trigonometric Functions"
    ```cpp
    constexpr int MAXN = 262144;
    constexpr int mod = 998244353;
    
    using i64 = long long;
    using poly_t = int[MAXN];
    using poly = int *const;
    
    void derivative(const poly &h, const int n, poly &f) {
      for (int i = 1; i != n; ++i) f[i - 1] = (i64)h[i] * i % mod;
      f[n - 1] = 0;
    }
    
    void integrate(const poly &h, const int n, poly &f) {
      for (int i = n - 1; i; --i) f[i] = (i64)h[i - 1] * inv[i] % mod;
      f[0] = 0; /* C */
    }
    
    void polyarcsin(const poly &h, const int n, poly &f) {
      /* arcsin(f) = ∫ f' / sqrt(1 - f^2) dx  */
      static poly_t arcsin_t;
      const int t = n << 1;
      std::copy(h, h + n, arcsin_t);
      std::fill(arcsin_t + n, arcsin_t + t, 0);
    
      DFT(arcsin_t, t);
      for (int i = 0; i != t; ++i) arcsin_t[i] = sqr(arcsin_t[i]);
      IDFT(arcsin_t, t);
    
      arcsin_t[0] = sub(1, arcsin_t[0]);
      for (int i = 1; i != n; ++i)
        arcsin_t[i] = arcsin_t[i] ? mod - arcsin_t[i] : 0;
    
      polysqrt(arcsin_t, n, f);
      polyinv(f, n, arcsin_t);
      derivative(h, n, f);
    
      DFT(f, t);
      DFT(arcsin_t, t);
      for (int i = 0; i != t; ++i) arcsin_t[i] = (i64)f[i] * arcsin_t[i] % mod;
      IDFT(arcsin_t, t);
    
      integrate(arcsin_t, n, f);
    }
    
    void polyarccos(const poly &h, const int n, poly &f) {
      /* arccos(f) = - ∫ f' / sqrt(1 - f^2) dx  */
      polyarcsin(h, n, f);
      for (int i = 0; i != n; ++i) f[i] = f[i] ? mod - f[i] : 0;
    }
    
    void polyarctan(const poly &h, const int n, poly &f) {
      /* arctan(f) = ∫ f' / (1 + f^2) dx  */
      static poly_t arctan_t;
      const int t = n << 1;
      std::copy(h, h + n, arctan_t);
      std::fill(arctan_t + n, arctan_t + t, 0);
    
      DFT(arctan_t, t);
      for (int i = 0; i != t; ++i) arctan_t[i] = sqr(arctan_t[i]);
      IDFT(arctan_t, t);
    
      inc(arctan_t[0], 1);
      std::fill(arctan_t + n, arctan_t + t, 0);
    
      polyinv(arctan_t, n, f);
      derivative(h, n, arctan_t);
    
      DFT(f, t);
      DFT(arctan_t, t);
      for (int i = 0; i != t; ++i) arctan_t[i] = (i64)f[i] * arctan_t[i] % mod;
      IDFT(arctan_t, t);
    
      integrate(arctan_t, n, f);
    }
    ```

## References

[^ref1]: [Elementary function——Wikipedia](https://en.wikipedia.org/wiki/Elementary_function)