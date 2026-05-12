Similar to discrete Fourier transform, Chirp Z transform is an algorithm that, given a polynomial $f(x) = \sum_{i = 0}^{m - 1} f_i x^i \in \mathbb{C}\lbrack x\rbrack$ and $q \in \mathbb{C} \setminus \{0\}$, computes $f(1), f(q), \dots, f(q^{n - 1})$, where $q$ is not required to be a root of unity. It can also be used for number-theoretic transform. This article will introduce Chirp Z transform and its inverse transform.

## Chirp Z Transform

According to the definition, Chirp Z transform can be written as:

$$
\operatorname{\mathsf{CZT}}_n : \left(f(x), q\right) \mapsto
\begin{bmatrix}
f(1) & f(q) & \cdots & f\left(q^{n - 1}\right)
\end{bmatrix}
$$

Where $f(x) := \sum_{i = 0}^{m - 1} f_i x^i \in \mathbb{C}\lbrack x\rbrack$ and $q \in \mathbb{C} \setminus \{0\}$.

### Bluestein Algorithm

Consider:

$$
ij = \binom{i}{2} + \binom{-j}{2} - \binom{i - j}{2}
$$

Where $i, j \in \mathbb{Z}$, we can construct:

$$
\begin{aligned}
G(x) & := \sum_{i = -(m - 1)}^{n - 1} q^{-\binom{i}{2}}x^i, \\
F(x) & := \sum_{i = 0}^{m - 1} f_i q^{\binom{-i}{2}}x^i.
\end{aligned}
$$

Where $G(x) \in \mathbb{C}\left\lbrack x, x^{-1}\right\rbrack$. For $i = 0, \dots, n - 1$:

$$
\begin{aligned}
\left\lbrack x^i\right\rbrack\left(G(x)F(x)\right) &=
\sum_{j = 0}^{m - 1}\left(\left(\left\lbrack x^{i - j}\right\rbrack G(x)\right)\left(\left\lbrack x^j\right\rbrack F(x)\right)\right) \\
&= \sum_{j = 0}^{m - 1} f_j q^{\binom{-j}{2} - \binom{i - j}{2}} \\
&= q^{-\binom{i}{2}} f\left(q^i\right)
\end{aligned}
$$

And $q^{\binom{i + 1}{2}} = q^{\binom{i}{2}}\cdot q^i$, $\binom{-i}{2} = \binom{i + 1}{2}$. This can be completed with one polynomial multiplication. This algorithm is called the Bluestein algorithm.

??? note "Template ([P6800【Template】Chirp Z-Transform](https://www.luogu.com.cn/problem/P6800))"
    ```cpp
    --8<-- "docs/math/code/poly/czt/czt_1.cpp:core"
    ```

## Inverse Chirp Z Transform

Inverse Chirp Z transform can be written as:

$$
\operatorname{\mathsf{ICZT}}_n :
\left(
    \begin{bmatrix} f(1) & f(q) & \cdots & f\left(q^{n - 1}\right)
    \end{bmatrix},q
\right)
\mapsto f(x)
$$

Where $f(x) \in \mathbb{C}\left\lbrack x\right\rbrack_{< n}$ and $q \in \mathbb{C} \setminus \{0\}$, and $q^i \neq q^j$ holds for all $i \neq j$. This is the condition for polynomial interpolation.

### Bostan–Schost Algorithm

Recall that the [Lagrange Interpolation Formula](../numerical/interp.md#lagrange-interpolation-method) is:

$$
f(x) = \sum_{i = 0}^{n - 1}\left(f\left(x_i\right)\prod_{0 \leq j < n \atop j \neq i} \frac{x - x_j}{x_i - x_j}\right)
$$

With $x_i \neq x_j$ for all $i \neq j$. Same as in [Fast Polynomial Interpolation](./multipoint-eval-interpolation.md#fast-polynomial-interpolation), we let $M(x) := \prod_{i = 0}^{n - 1}\left(x - x_i\right)$. By L'Hôpital's rule:

$$
M'(x_i) = \lim_{x \to x_i} \frac{M(x)}{x - x_i} = \prod_{0 \leq j < n \atop j \neq i}\left(x_i - x_j\right)
$$

The modified Lagrange interpolation formula is:

$$
f(x) = M(x)\left(\sum_{i = 0}^{n - 1}\frac{f\left(x_i\right)/M'(x_i)}{x - x_i}\right)
$$

Now we have:

$$
f(x) = M(x)\left(\sum_{i = 0}^{n - 1}\frac{f\left(q^i\right)/M'\left(q^i\right)}{x - q^i}\right)
$$

Where $M(x)=\prod_{j = 0}^{n - 1}\left(x - q^j\right)$. If we let $n$ be even, let $n = 2k$ and $H(x) := \prod_{j = 0}^{k - 1}\left(x - q^j\right)$, then:

$$
M(x) = H(x) \cdot q^{k^2} \cdot H\left(\frac{x}{q^k}\right)
$$

This allows us to compute $M(x)$ quickly. Then use Bluestein algorithm to compute $M'(1), \dots, M'(q^{n - 1})$. Let $c_i := f\left(q^i\right)/M'\left(q^i\right)$, we have:

$$
f(x) = M(x)\left(\sum_{i = 0}^{n - 1}\frac{c_i}{x - q^i}\right)
$$

Since $\deg f(x) < n$, we only need to compute $\sum_{i = 0}^{n - 1}\frac{c_i}{x - q^i}\bmod{x^n}$, where $\frac{c_i}{x - q^i} \in \mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$, that is:

$$
\begin{aligned}
\sum_{i = 0}^{n - 1}\frac{c_i}{x - q^i} \bmod x^n &=
-\sum_{i = 0}^{n - 1}\left(\sum_{j = 0}^{n - 1} c_i q^{-i(j+1)}x^j\right) \\
&= -\sum_{j = 0}^{n - 1} C\left(q^{-j - 1}\right) x^j
\end{aligned}
$$

Where $C(x) = \sum_{i = 0}^{n - 1} c_i x^i$. We can use Bluestein algorithm to compute $C\left(q^{-1}\right), \dots, C\left(q^{-n}\right)$.

Simply put, we perform the following calculations respectively:

1.  Use decrease and conquer to compute $M(x)$;
2.  Use Bluestein algorithm to compute $M'(1), \dots, M'(q^{n - 1})$;
3.  Use Bluestein algorithm to compute $C\left(q^{-1}\right), \dots, C\left(q^{-n}\right)$;
4.  Compute $f(x)$ with one polynomial multiplication.

The time complexity of each step equals the time complexity of multiplying two polynomials of degree less than or equal to $n$.

??? note "Template Implementation"
    ```cpp
    --8<-- "docs/math/code/poly/czt/inv_czt_1.cpp:core"
    ```

## References

1.  [Bostan, A. (2010). Fast algorithms for polynomials and matrices. JNCF 2010. Algorithms Project, INRIA.](https://specfun.inria.fr/bostan/publications/exposeJNCF.pdf)