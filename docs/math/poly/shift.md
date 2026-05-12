## Polynomial Shift

Polynomial shift is a simple case of polynomial composition transformation. Given the coefficients of $f(x)=\sum _ {i=0}^nf_ix^i$ and a constant $c$, find the coefficients of $f(x+c)$, i.e., $f(x)\mapsto f(x+c)$.

### Divide-and-Conquer Method

Let:

$$
f(x)=f_0(x)+x^{\left\lfloor n/2\right\rfloor}f_1(x)
$$

Then:

$$
f(x+c)=f_0(x+c)+(x+c)^{\left\lfloor n/2\right\rfloor}f_1(x+c)
$$

The coefficients of $(x+c)^{\left\lfloor n/2\right\rfloor}$ are binomial coefficients, so:

$$
T(n)=2T(n/2)+O(n\log n)=O(n\log^2 n)
$$

Where $O(n\log n)$ is the time for polynomial multiplication.

### Taylor Formula Method

Applying the Taylor formula to $f(x)$ at $c$:

$$
f(x)=f(c)+\frac{f'(c)}{1!}(x-c)+\frac{f''(c)}{2!}(x-c)^2+\cdots +\frac{f^{(n)}(c)}{n!}(x-c)^n
$$

Then:

$$
f(x+c)=f(c)+\frac{f'(c)}{1!}x+\frac{f''(c)}{2!}x^2+\cdots +\frac{f^{(n)}(c)}{n!}x^n
$$

Observe that for $t\geq 0$:

$$
\begin{aligned}
t!\lbrack x^t\rbrack f(x+c)&=f^{(t)}(c)\\
&=\sum _ {i=t}^nf_ii!\frac{c^{i-t}}{(i-t)!}\\
&=\sum _ {i=0}^{n-t}f _ {i+t}(i+t)!\frac{c^i}{i!}
\end{aligned}
$$

Let:

$$
\begin{aligned}
A_0(x)&=\sum _ {i=0}^nf _ {n-i}(n-i)!x^i\\
B_0(x)&=\sum _ {i=0}^n\frac{c^i}{i!}x^i
\end{aligned}
$$

Then:

$$
\begin{aligned}
\lbrack x^{n-t}\rbrack (A_0(x)B_0(x))&=\sum _ {i=0}^{n-t} (\lbrack x^{n-t-i}\rbrack A_0(x))(\lbrack x^i\rbrack B_0(x))\\
&=\sum _ {i=0}^{n-t}f _ {i+t}(i+t)!\frac{c^i}{i!}\\
&=t!\lbrack x^t\rbrack f(x+c)
\end{aligned}
$$

### Binomial Theorem Method

Consider the binomial theorem $\displaystyle (a+b)^n=\sum _ {i=0}^n\binom{n}{i}a^ib^{n-i}$:

$$
\begin{aligned}
f(x+c)&=\sum _ {i=0}^nf_i(x+c)^i\\
&=\sum _ {i=0}^nf_i\left(\sum _ {j=0}^i\binom{i}{j}x^jc^{i-j}\right)\\
&=\sum _ {i=0}^nf_ii!\left(\sum _ {j=0}^i\frac{x^j}{j!}\frac{c^{i-j}}{(i-j)!}\right)\\
&=\sum _ {i=0}^n\frac{x^i}{i!}\left(\sum _ {j=i}^{n}f_jj!\frac{c^{j-i}}{(j-i)!}\right)
\end{aligned}
$$

The result obtained is the same as the above method.

## Continuous Point Value Shift

???+ note "Problem [LOJ 166 Lagrange Interpolation 2](https://loj.ac/p/166)"
    Given the consecutive point values $f(0),f(1),\dots ,f(n)$ of a polynomial $f$ with degree $\le n$, compute $f(c),f(c+1),\dots ,f(c+n)$ modulo $998244353$, where $1\leq n\leq 10^5,n < m\leq 10^8$.

### Lagrange Interpolation Formula Method

Consider the [Lagrange Interpolation Formula](../numerical/interp.md#lagrange-interpolation-method):

$$
\begin{aligned}
f(x)&=\sum _ {0\leq i\leq n}f(i)\prod _ {0\leq j\leq n\,\land \,j\neq i}\frac{x-j}{i-j}\\
&=\sum _ {0\leq i\leq n}f(i)\frac{x!}{(x-n-1)!(x-i)}\frac{(-1)^{n-i}}{i!(n-i)!}\\
&=\frac{x!}{(x-n-1)!}\sum _ {0\leq i\leq n}\frac{f(i)}{(x-i)}\frac{(-1)^{n-i}}{i!(n-i)!}
\end{aligned}
$$

The above is in convolution form but cannot guarantee $x-i\neq 0$ in the denominator. So below we only consider the case $c > n$; other cases (like avoiding zeros in denominators when coefficients are under modulo prime) can be discussed case by case. Let:

$$
\begin{aligned}
A_0(x)&=\sum _ {0\leq i\leq n}\frac{f(i)(-1)^{n-i}}{i!(n-i)!}x^i\\
B_0(x)&=\sum _ {i\geq 0}\frac{1}{c-n+i}x^i
\end{aligned}
$$

Then for $t\geq 0$:

$$
\begin{aligned}
\lbrack x^{n+t}\rbrack (A_0(x)B_0(x))&=\sum _ {i=0}^{n+t}(\lbrack x^i\rbrack A_0(x))(\lbrack x^{n+t-i}\rbrack B_0(x))\\
&=\sum _ {i=0}^{n}\frac{f(i)(-1)^{n-i}}{i!(n-i)!}\frac{1}{c+t-i}\\
&=\frac{(c+t-n-1)!}{(c+t)!}f(c+t)
\end{aligned}
$$

In implementation, taking the required part of $B_0(x)$ by truncation can compute more point values, and cyclic convolution can be used.

With a slight modification to the problem, if for some $d$ we are given point values $f(d),f(d+k),\dots ,f(d+nk)$, we can compute $f(c+d),f(c+d+k),\dots ,f(c+d+nk)$. This can be viewed as shifting the point values of $g(x)=f(d+kx)$ from $g(0),g(1),\dots ,g(n)$ to $g(c/k),g(c/k+1),\dots ,g(c/k+n)$.

The Lagrange interpolation formula also provides a linear-time method for computing a single point value by maintaining some prefix and suffix products.

## Applications

### Unsigned Stirling Numbers of the First Kind on the Same Row

???+ note "Problem [P5408 Stirling Numbers of the First Kind Row](https://www.luogu.com.cn/problem/P5408)"
    Find $\displaystyle {n\brack 0},{n\brack 1},\dots ,{n\brack n}$ modulo prime $167772161$, where $1\leq n< 262144$.

Consider:

$$
x^{\overline{n}}=\sum _ {i=0}^n{n\brack i}x^i,\quad n\geq 0
$$

Where $x^{\overline{n}}=x\cdot (x+1)\cdots (x+n-1)$ is the rising factorial, and let $f_n(x)=x^{\overline{n}}$. Then:

$$
f_{2n}(x)=x^{\overline{n}}\cdot (x+n)^{\overline{n}}=f_n(x)f_n(x+n)
$$

Using polynomial shift, we can compute $f_n(x+n)$ in $O(n\log n)$, reducing the problem to half: find the coefficients of $f_n(x)$:

$$
T(n)=T(n/2)+O(n\log n)=O(n\log n)
$$

### Factorial Modulo Prime

???+ note "Problem [P5282【Template】Fast Factorial Algorithm](https://www.luogu.com.cn/problem/P5282)"
    Find $n!\bmod p$, where $p$ is prime and $1\leq n< p\leq 2^{31}-1$.

Let $v=\lfloor\sqrt{n}\rfloor$ and $g(x)=\prod _ {i=1}^v(x+i)$. Then:

$$
n!\equiv \left(\prod _ {i=0}^{v-1}g(iv)\right)\cdot \prod _ {i=v^2+1}^n i\pmod{p}
$$

Where $\prod _ {i=v^2+1}^n i$ can be computed in $O(\sqrt{n})$ time. We want to quickly compute the first part.

#### Polynomial Multi-Point Evaluation

The coefficients of $g(x)$ can be obtained in $O(n\log n)$ time using the polynomial shift algorithm above, but multi-point evaluation to compute $g(0),g(v),g(2v),\dots ,g(v^2-v)$ requires $O(\sqrt{n}\log^2n)$ time.

#### Continuous Point Value Shift

Let $g_d(x)=\prod _ {i=1}^d(x+i)$. We can uniquely determine this degree $d$ polynomial from $d+1$ point values $g_d(0),g_d(v),\dots ,g_d(dv)$. Also:

$$
g _ {2d}(x)=g_d(x)g_d(x+d)
$$

So only $2d+1$ point values can uniquely determine $g _ {2d}(x)$. Then use continuous point value shift to compute $g_d((d+1)v),g_d((d+2)v),\dots ,g_d(2dv)$ (i.e., shift point values of $h(x)=g_d(vx)$ from $h(0),h(1),\dots ,h(d)$ to $h(d+1),h(d+2),\dots ,h(2d)$) and $g_d(d),g_d(v+d),\dots ,g_d(2dv+d)$ (i.e., shift point values of $h(x)=g_d(vx)$ from $h(0),h(1),\dots ,h(d)$ to $h(d/v),h(d/v+1),h(d/v+2),\dots ,h(d/v+2d)$), then multiply the corresponding point values to get $g _ {2d}(0),g _ {2d}(v),\dots ,g _ {2d}(2dv)$.

To compute $g _ {d+1}(0),g _ {d+1}(v),\dots ,g _ {d+1}(dv),g _ {d+1}((d+1)v)$ from $g_d(0),g_d(v),\dots ,g_d(dv)$, consider:

$$
g _ {d+1}(x)=(x+d+1)\cdot g_d(x)
$$

The additional point value can be computed with a linear-time algorithm. Then maintaining $g_1(0)=1,g_1(v)=v+1$ at the start and using continuous point value shift to double these point values:

$$
T(n)=T(n/2)+O(n\log n)=O(n\log n)
$$

And we only need about $\sqrt{n}$ point values, so the time complexity is $O(\sqrt{n}\log n)$.

### Binomial Coefficient Prefix Sum Modulo Prime

???+ note "Problem [LOJ 6386 Binomial Coefficient Prefix Sum](https://loj.ac/p/6386)"
    Compute $\displaystyle \sum _ {i=0}^m\binom{n}{i}\bmod 998244353$, where $0\leq m\leq n\leq 9\times 10^8$.

Consider using a matrix to describe the recurrence $n!=n\cdot (n-1)!$:

$$
\begin{bmatrix}
n!
\end{bmatrix}
=
\left(
\prod _ {i=0}^{n-1}
\begin{bmatrix}i+1\end{bmatrix}
\right)
\begin{bmatrix}
1
\end{bmatrix}
$$

Similarly, the recurrence for binomial coefficient prefix sum can be described as:

$$
\begin{bmatrix}
\binom{n}{m+1}\\
\sum _ {i=0}^m\binom{n}{i}
\end{bmatrix}=
\begin{bmatrix}
(n-m)/(m+1)&0\\
1&1
\end{bmatrix}
\begin{bmatrix}
\binom{n}{m}\\
\sum _ {i=0}^{m-1}\binom{n}{i}
\end{bmatrix}
$$

Note the order of matrix multiplication:

$$
\begin{aligned}
\begin{bmatrix}
\binom{n}{m+1}\\
\sum _ {i=0}^m\binom{n}{i}
\end{bmatrix}
&=
\left(
\prod _ {i=0}^{m}
\begin{bmatrix}
(n-i)/(i+1)&0\\1&1
\end{bmatrix}
\right)
\begin{bmatrix}
1\\0
\end{bmatrix}\\
&=
\frac{1}{(m+1)!}
\left(
\prod _ {i=0}^{m}
\begin{bmatrix}
n-i&0\\i+1&i+1
\end{bmatrix}
\right)
\begin{bmatrix}
1\\0
\end{bmatrix}
\end{aligned}
$$

Let $v=\lfloor\sqrt{m}\rfloor$, consider maintaining the point values of the matrix:

$$
\begin{aligned}
M _ d(x)&=
\prod _ {i=1}^d
\begin{bmatrix}
-x+n+1-i&0\\
x+i&x+i
\end{bmatrix}\\
&=
\begin{bmatrix}
f_d(x)&0\\
g_d(x)&h_d(x)
\end{bmatrix}
\end{aligned}
$$

Namely, the point values $M _ d(0),M _ d(v),\dots ,M_d(dv)$, i.e., $f_d(0),f_d(v),\dots ,f_d(dv)$, $h_d(0),\dots ,h_d(dv)$ and $g_d(0),\dots ,g_d(dv)$. Also:

$$
\begin{aligned}
M _ {2d}(x)&=
\prod _ {i=1}^{2d}
\begin{bmatrix}
-x+n+1-i&0\\
x+i&x+i
\end{bmatrix}\\
&=
\left(
\prod _ {i=1}^d
\begin{bmatrix}
-x-d+n+1-i&0\\
x+d+i&x+d+i
\end{bmatrix}
\right)
\left(
\prod _ {i=1}^d
\begin{bmatrix}
-x+n+1-i&0\\
x+i&x+i
\end{bmatrix}
\right) \\
&=
\begin{bmatrix}
f_d(x+d)&0\\
g_d(x+d)&h_d(x+d)
\end{bmatrix}
\begin{bmatrix}
f_d(x)&0\\
g_d(x)&h_d(x)
\end{bmatrix} \\
&=
\begin{bmatrix}
f_d(x+d)f_d(x)&0\\
g_d(x+d)f_d(x)+h_d(x+d)g_d(x)&h_d(x+d)h_d(x)
\end{bmatrix}
\end{aligned}
$$

The bottom-right element of the matrix is exactly what we maintain in the factorial algorithm. Then:

$$
\begin{aligned}
\prod _ {i=0}^{m}
\begin{bmatrix}
n-i&0\\i+1&i+1
\end{bmatrix}=
\left(
\prod _ {i=(k+1)v}^m
\begin{bmatrix}
n-i&0\\
i+1&i+1
\end{bmatrix}
\right)
\begin{bmatrix}
f_v(kv)&0\\
g_v(kv)&h_v(kv)
\end{bmatrix}
\cdots
\begin{bmatrix}
f_v(0)&0\\
g_v(0)&h_v(0)
\end{bmatrix}
\end{aligned}
$$

This can be computed in $O(\sqrt m\log m)$ time.

### Harmonic Number Modulo Prime

???+ note "Problem [P5702 Harmonic Series Sum](https://www.luogu.com.cn/problem/P5702)"
    Compute $\sum _ {i=1}^ni^{-1}\bmod p$, where $p$ is prime and $1\leq n< p< 2^{30}$.

Let $H_n=\sum _ {k=1}^nk^{-1}$. One step of recurrence is:

$$
\begin{bmatrix}
(n+1)!\\(n+1)!H _ {n+1}
\end{bmatrix}=
\begin{bmatrix}
n+1&0\\1&n+1
\end{bmatrix}
\begin{bmatrix}
n!\\n!H_n
\end{bmatrix}
$$

Then:

$$
\begin{bmatrix}
{n+1\brack 1}\\{n+1\brack 2}
\end{bmatrix}=
\begin{bmatrix}
n!\\n!H_n
\end{bmatrix}=
\left(
\prod _ {i=0}^{n-1}
\begin{bmatrix}
i+1&0\\1&i+1
\end{bmatrix}
\right)
\begin{bmatrix}
1\\0
\end{bmatrix}
$$

Here $\displaystyle {n+1\brack 1}$ and $\displaystyle {n+1\brack 2}$ are unsigned Stirling numbers of the first kind. The method for maintaining point value matrices is the same as above.

## Integral Recurrence

For more general cases, similar to the above fast factorial algorithm case, what kind of algorithm do we expect?

???+ note "Problem [P6115【Template】Integral Recurrence](https://www.luogu.com.cn/problem/P6115)"
    Given a sequence $a$ satisfying $\forall n\ge m,\sum_{k=0}^ma_{n-k}P_k(n)=0$, where $P_k$ are polynomials of degree at most $d$.  
    Given all coefficients of $P_k$, and $a_0,a_1,\dots,a_{m-1}$, find $a_n$.
    Modulo $998244353$. $n\le6\times10^8$, $1\le m,d\le7$, time limit $7s$.

To systematically describe the process of constructing matrices in the above example problems, we introduce the concept of [$\lambda$ matrix](../linear-algebra/jordan.md#lambda-matrix).

To implement integral recurrence, we should note that during the fast factorial algorithm, the point values we maintain are actually not $n!$, but $\prod_{i=0}^{T-1}(aT+i)$, i.e., the **ratio relationship between pairs of point values**.

Since the order $m$ of integral recurrence is not just $1$, we can no longer directly maintain the ratio relationship between a pair of numbers; instead, we maintain a **linear transformation between pairs of $m$-dimensional vectors**, i.e., an $m\times m$ matrix, where **each entry of the matrix corresponds to a point value of some polynomial**.

It is easy to find that for general integral recurrence far coefficient evaluation problems, we can construct:

$$
-{\frac{1}{P_0(n)}}\begin{bmatrix}P_1(n)&P_2(n)&P_3(n)&\cdots&P_{m-1}(n)&P_m(n)\\-P_0(n)\\&-P_0(n)\\&&-P_0(n)\\&&&\ddots\\&&&&-P_0(n)\\\end{bmatrix}
\begin{bmatrix}a_{n-1}\\a_{n-2}\\a_{n-3}\\\vdots\\a_{n-m+1}\\a_{n-m}\end{bmatrix}
=\begin{bmatrix}a_n\\a_{n-1}\\a_{n-2}\\\vdots\\a_{n-m+2}\\a_{n-m+1}\end{bmatrix}
$$

Let:

$$
B(\lambda)=\begin{bmatrix}
    P_1(\lambda)&P_2(\lambda)&P_3(\lambda)&\cdots&P_{m-1}(\lambda)&P_m(\lambda)\\
    -P_0(\lambda)\\
    &-P_0(\lambda)\\
    &&-P_0(\lambda)\\
    &&&\ddots\\
    &&&&-P_0(\lambda)\\
\end{bmatrix}
$$

Ignoring the $-\frac1{P_0(n)}$ factor, we now need to maintain something of the form $\prod_{i=0}^{T-1}B(aT+m+i)$, where multiplication goes from right to left.

It is easy to find that $B_T(\lambda)=\prod_{i=0}^{T-1}B(\lambda+i)$ is a $\lambda$ matrix with each entry of degree no higher than $dT$, which can be maintained with only $dT+1$ values.

So we maintain point values of these $\lambda$ matrices: $B_T(m)$, $B_T(m+T)$, $B_T(m+2T)$, $\dots$, $B_T(m+(dT-1)T)$, $B_T(m+dT^2)$. Then we use a method similar to the fast factorial algorithm to perform polynomial point value shift and doubling.

Specifically, to raise $t=\log_2T$ by $1$:

1.  Obtain $B_T(p+dT^2)$, $B_T(p+(dT+1)T)$, $B_T(p+(dT+2)T)$, $\cdots$, $B_T(p+(2dT-1)T)$, $B_T(p+(2dT)dT)$ in $O(m^2dT\log(dT))$ time.
2.  Obtain $B_T(p+2dT^2)$, $B_T(p+(2dT+1)T)$, $B_T(p+(2dT+2)T)$, $\cdots$, $B_T(p+(3dT-1)T)$, $B_T(p+(3dT)dT)$ in $O(m^2dT\log(dT))$ time.
3.  Obtain $B_T(p+3dT^2)$, $B_T(p+(3dT+1)T)$, $B_T(p+(3dT+2)T)$, $\cdots$, $B_T(p+(4dT-1)T)$, $B_T(p+(4dT)dT)$ in $O(m^2dT\log(dT))$ time.
4.  Compute $B_{2T}(v)=B_{T}(v+T)B_{T}(v)$.

We spend $O(m^2dT\log(dT))$ complexity per round for shifting; at the same time, we only need to do $\Theta(dT)$ matrix multiplications per round, with complexity considered as $O(m^3dT)$.

Finally, we only need $T\ge\sqrt{n/d}$.

The $-\frac1{P_0(n)}$ factor can be solved similarly.

Thus, the preprocessing complexity is $\Theta(\sqrt{nd}(m^3+m^2\log(nd)))$.

For queries, we only need $\Theta(n/T)$ vector-matrix multiplications and $O(T)$ brute-force transitions.

It is easy to find that this part of computation is not the complexity bottleneck.

Therefore, the total complexity of this algorithm is $\Theta(\sqrt{nd}(m^3+m^2\log(nd)))$.

When coding, we can use cyclic convolution tricks to reduce the NTT constant.

In practical applications, we often extract far coefficients from a known differentially finite GF, so $m,d$ are both constants, achieving $\Theta(\sqrt n\log n)$ far coefficient evaluation.

## References

-   Alin Bostan, Pierrick Gaudry, and Eric Schost. Linear recurrences with polynomial coefficients and application to integer factorization and Cartier–Manin operator.
-   Min_25's blog
-   [ZZQ's Blog - Factorial Mod Large Prime](https://www.cnblogs.com/zzqsblog/p/8408691.html)