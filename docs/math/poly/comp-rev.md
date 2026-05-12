Composition and composition inverse of formal power series are also common operations on formal power series. For $f$ without special properties, we have been using $O\left(n^2\right)$ algorithms to compute $f(g) \bmod{x^n}$ where $f\in\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack,g\in x\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$, but due to low efficiency, they are less used. We introduce the Kinoshita–Li algorithm with $O\left(\mathsf{M}\left(n\right)\log n\right)$ time, where $O\left(\mathsf{M}\left(n\right)\right)$ is the time to multiply two polynomials of degree $O\left( n\right)$.

## Composition of Formal Power Series/Polynomials

To compute $f\left(g\left(x\right)\right)\bmod{x^n}$, since each coefficient of $f\left(g\left(x\right)\right)$ is a finite sum, we need $f(x)\in\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack,g(x)\in x\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$. If $f(x),g(x)\in\mathbb{C}\lbrack x\rbrack$, this condition can also be satisfied. Since we need to truncate coefficients of $f\left(g\left(x\right)\right)$, we can directly consider the case where both $f(x)$ and $g(x)$ are polynomials. For $f(x)=\sum_{j=0}^{n-1}f_jx^j$:

$$
f\left(g\left(x\right)\right)=\sum_{j=0}^{n-1}f_jg\left(x\right)^j
$$

We consider the rational function on ring $\mathbb{C}\lbrack x\rbrack\left(\left( y\right)\right)$:

$$
\begin{aligned}
\frac{f\left(y^{-1}\right)}{1-y\cdot g(x)}&=\sum_{j\geq 0}\left(\cdots +f_jy^{-j}+\cdots\right)g(x)^jy^j \\
f\left(g\left(x\right)\right)&=\left\lbrack y^0\right\rbrack\frac{f\left(y^{-1}\right)}{1-y\cdot g(x)}
\end{aligned}
$$

According to the Bostan–Mori algorithm mentioned in [Constant-Coefficient Homogeneous Linear Recurrence](./linear-recurrence.md), Kinoshita and Li point out that it can be modified to a bivariate form:

$$
\begin{aligned}
\frac{P\left(y\right)}{Q\left(x,y\right)}\bmod{x^n}&=\left(\frac{P\left(y\right)}{Q\left(x,y\right)Q\left(-x,y\right)}\bmod{x^n}\right)Q\left(-x,y\right)\bmod{x^n} \\
&=\left(\frac{P(y)}{V(x^2,y)}\bmod{x^n}\right)Q\left(-x,y\right)\bmod{x^n} \\
&=\left.\left(\frac{P(y)}{V(z,y)}\bmod{z^{\left\lceil n/2\right\rceil}}\right)\right|_{z=x^2}Q\left(-x,y\right)\bmod{x^n}
\end{aligned}
$$

For recursive calculation, when $n=1$, we only need to compute:

$$
\frac{P(y)}{Q(x,y)}\bmod{x}=\frac{P(y)}{Q(0,y)}\in\mathbb{C}\left(\left( y\right)\right)
$$

When computing $\dfrac{P(y)}{V(z,y)}\bmod{z^{\left\lceil n/2\right\rceil}}\in\mathbb{C}\left\lbrack z\right\rbrack\left(\left( y\right)\right)$, we don't need to keep all coefficients of $y$, because at the end we only need to extract the coefficient of $y^0$, so coefficients of $y^{>0}$ are not needed. And since after obtaining the former, we need to multiply it by several polynomials of the form $Q(-x,y)\in\mathbb{C}\lbrack x,y\rbrack$, we only need to keep coefficients that contribute to $y^0$. Let's prepare the pseudocode:

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{Comp}}\left(P(y),Q(x,y),n,m\right)\text{:} \\
&\textbf{Input}\text{: }P=\sum_{0\leq j< n}p_jy^{-j}\in\mathbb{C}((y)),Q\in\mathbb{C}\left\lbrack x,y\right\rbrack ,n,m\in\mathbb{N}_{>0}\text{.} \\
&\textbf{Output}\text{: }\left\lbrack y^{\left(-m,0\right\rbrack}\right\rbrack\dfrac{P(y)}{Q(x,y)}\bmod{x^n}\text{.} \\
&\textbf{Require}\text{: }\left\lbrack x^0y^0\right\rbrack Q=1\text{.} \\
1&\textbf{if }n=1\textbf{ then return }\left(\left\lbrack y^{-m+1}\right\rbrack\frac{P(y)}{Q(0,y)},\dots ,\left\lbrack y^0\right\rbrack\frac{P(y)}{Q(0,y)}\right) \\
2&V(x^2,y)\gets Q(x,y)Q(-x,y)\bmod{x^n} \\
3&d\gets\deg_y Q\left(-x,y\right)\\
4&\left(t_{-(m+d)+1},\dots ,t_0\right)\gets \operatorname{\mathsf{Comp}}\left(P(y),V(x,y),\left\lceil n/2\right\rceil,m+d\right) \\
5&T(x,y)\gets \sum_{j=-(m+d)+1}^0t_jy^j \\
6&U(x,y)=\sum_{j=-(m+d)+1}^d u_jy^j\gets T(x^2,y)Q(-x,y)\bmod{x^n} \\
7&\textbf{return }\left(u_{-m+1},\dots ,u_0\right)
\end{array}
$$

Then we have:

$$
f\left(g\left(x\right)\right)\bmod{x^n}=\operatorname{\mathsf{Comp}}\left(f\left(y^{-1}\right),1-y\cdot g(x),\max\left\lbrace 1+\deg f,n\right\rbrace ,1\right)\bmod{x^n}
$$

Note that the third parameter is because $g(0)$ may be non-zero. If $\deg f\geq n$, we cannot truncate $f(x)$ to compute $f\left(g(x)\right)$. We can also choose to compute $f(g)=f\circ \left(x+g(0)\right)\circ \left(g-g(0)\right)$. At this point, we can take $F:=f\left(x+g(0)\right)\bmod{x^n}$ and $G:=g-g(0)$, and then compute $\operatorname{\mathsf{Comp}}\left(F\left(y^{-1}\right),1-y\cdot G(x),n,1\right)$.

Also, due to the limitation of the call, the $Q(0,y)^{-1}$ when the recursion finally ends can be directly derived and does not need to use the formal power series multiplicative inverse algorithm to compute. We only need to compute once and extract the required coefficients.

## Common Special Form Compositions

Common [polynomial elementary functions](./elementary-func.md) can all be computed via composition:

$$
\begin{aligned}
g(0)=1&,\space g^{-1}=1+(1-g)+(1-g)^2+\cdots \\
g(0)=1&,\space \log g=-\dfrac{1-g}{1}-\dfrac{(1-g)^2}{2}-\dfrac{(1-g)^3}{3}-\cdots \\
g(0)=0&,\space \exp g=1+\dfrac{g}{1!}+\dfrac{g^2}{2!}+\dfrac{g^3}{3!}+\cdots \\
g(0)=1&,\space g^e=1+\dfrac{e}{1}(g-1)+\dfrac{e(e-1)}{2}(g-1)^2+\cdots
\end{aligned}
$$

Power function is also used in computing composition inverse.

### Kronecker Substitution

Before analyzing time complexity, let's consider how to do bivariate polynomial multiplication. One idea is to "pack" the coefficients. This method was proposed by Kronecker in 1882 to reduce multiplication on $R\lbrack x,y\rbrack$ to multiplication on $R\lbrack x\rbrack$, but it requires $N$ to be large enough.

Assume $\deg_x \left(AB\right)<N$. After computing $A\left(x,x^N\right)B\left(x,x^N\right)$, we can still restore $A(x,y)B(x,y)$, and the time for "packing" and "unpacking" is linear.

Using Kronecker substitution and then computing one-variable polynomial multiplication, we can find that when $n$ is a power of 2, the above algorithm can complete in $O\left(\mathsf{M}\left(n\right)\log n\right)$ time, because in each recursion the degree of $y$ doubles, but the degree of $x$ halves.

??? note "Template ([P5373【Template】Polynomial Composition Function](https://www.luogu.com.cn/problem/P5373))"
    The code has made some simplifications and modifications compared to the original algorithm to make it shorter.
    
    ```cpp
    --8<-- "docs/math/code/poly/comp-rev/comp_1.cpp"
    ```

## Composition Inverse of Formal Power Series

Given $f\in x\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$ with $f'(0)\neq 0$, find $g(x)\bmod{x^n}$ such that $f(g)\equiv g(f)\equiv x\pmod{x^n}$.

According to [Lagrange Inversion](./lagrange-inversion.md), for $n>1,k\geq 0$:

$$
\left\lbrack x^{n-1}\right\rbrack f(x)^k=\frac{k}{n-1}\left\lbrack x^{n-1-k}\right\rbrack \left(\frac{g(x)}{x}\right)^{-(n-1)}
$$

That is, if we can compute $\left\lbrack x^{n-1}\right\rbrack f(x)^k$ for $k=0,1,\dots ,n-1$, then we can find its composition inverse.

Kinoshita and Li point out that we can consider the bivariate rational function:

$$
\frac{1}{1-y\cdot f(x)}=\sum_{j\geq 0}f(x)^jy^j
$$

And this problem has a more general form: the Power Projection problem. We consider computing:

$$
u:=\left\lbrack x^{n-1}\right\rbrack\frac{P(x,y)}{Q(x,y)}\bmod{y^m}
$$

When $n-1=0$, obviously $u=\dfrac{P(0,y)}{Q(0,y)}\bmod{y^m}$. Otherwise:

$$
\frac{P(x,y)}{Q(x,y)}=\frac{P(x,y)Q(-x,y)}{Q(x,y)Q(-x,y)}=\frac{U_e\left(x^2,y\right)+xU_o\left(x^2,y\right)}{V\left(x^2,y\right)}
$$

Then:

$$
\begin{aligned}
u&=\begin{cases}
\left\lbrack x^{n-1}\right\rbrack\dfrac{U_e\left(x^2,y\right)}{V\left(x^2,y\right)}&\text{ if }n-1\text{ is even,} \\
\left\lbrack x^{n-1}\right\rbrack\dfrac{xU_o\left(x^2,y\right)}{V\left(x^2,y\right)}&\text{ if }n-1\text{ is odd.}
\end{cases} \\
&=\begin{cases}
\left\lbrack x^{\left\lceil n/2\right\rceil-1}\right\rbrack\dfrac{U_e\left(x,y\right)}{V\left(x,y\right)}&\text{ if }n-1\text{ is even,} \\
\left\lbrack x^{\left\lceil n/2\right\rceil-1}\right\rbrack\dfrac{U_o\left(x,y\right)}{V\left(x,y\right)}&\text{ if }n-1\text{ is odd.}
\end{cases}
\end{aligned}
$$

We give its pseudocode:

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{PowProj}}\left(P(x,y),Q(x,y),n,m\right)\text{:} \\
&\textbf{Input}\text{: }P,Q\in\mathbb{C}\left\lbrack x,y\right\rbrack ,n,m\in\mathbb{N}_{>0}\text{.} \\
&\textbf{Output}\text{: }\left\lbrack x^{n-1}\right\rbrack\dfrac{P(x,y)}{Q(x,y)}\bmod{y^m}\text{.} \\
&\textbf{Require}\text{: }\left\lbrack x^0y^0\right\rbrack Q=1\text{.} \\
1&\textbf{while }n>1\textbf{ do} \\
2&\qquad U(x,y)\gets P(x,y)Q(-x,y)\bmod{x^n}\bmod{y^m} \\
3&\qquad \textbf{if }n-1\text{ is even }\textbf{then} \\
4&\qquad\qquad P(x,y)\gets \sum_{j=0}^{\left\lceil n/2\right\rceil +1}\left(\left\lbrack x^{2j}\right\rbrack U(x,y)\right)x^j \\
5&\qquad \textbf{else} \\
6&\qquad\qquad P(x,y)\gets \sum_{j=0}^{\left\lceil n/2\right\rceil +1}\left(\left\lbrack x^{2j+1}\right\rbrack U(x,y)\right)x^j \\
7&\qquad \textbf{end if} \\
8&\qquad V(x,y)\gets Q(x,y)Q(-x,y)\bmod{x^n}\bmod{y^m} \\
9&\qquad Q(x,y)\gets \sum_{j=0}^{\left\lceil n/2\right\rceil +1}\left(\left\lbrack x^{2j}\right\rbrack V(x,y)\right)x^j \\
10&\qquad n\gets \left\lceil n/2\right\rceil \\
11&\textbf{end while} \\
12&\textbf{return }\left(\frac{P(0,y)}{Q(0,y)}\bmod{y^m}\right)
\end{array}
$$

Similarly, we can also directly derive $Q(0,y)^{-1}$ without computing formal power series multiplicative inverse. Then the composition inverse algorithm is:

$$
\begin{array}{ll} &\textbf{Algorithm }\operatorname{\mathsf{Rev}}(f(x),n)\text{:} \\
&\textbf{Input}\text{: }f\in x\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack, f'(0)\neq 0,n\in\mathbb{N}_{\geq 2}\text{.} \\
&\textbf{Output}\text{: }g(x)\bmod{x^n} \text{ such that }f(g)\equiv g(f)\equiv x\pmod{x^n}\text{.} \\
1&t\gets f'(0) \\
2&F(x)\gets f\left(t^{-1}x\right) \\
3&\sum_{k=0}^{n-1}a_ky^k\gets \operatorname{\mathsf{PowProj}}\left(1,1-y\cdot F(x),n,n\right) \\
4&G(x)\gets \sum_{k=1}^{n-1}\frac{n-1}{k}a_{k}x^{n-1-k} \\
5&H(x)\gets \left(G(x)^{1/(n-1)}\right)^{-1}\bmod{x^{n-1}} \\
6&\textbf{return }\left((t^{-1}x) \circ \left(x\cdot H\right)\right)
\end{array}
$$

??? note "Template ([P5809【Template】Polynomial Composition Inverse](https://www.luogu.com.cn/problem/P5809))"
    The code has made some simplifications and modifications compared to the original algorithm to make it shorter.
    
    ```cpp
    --8<-- "docs/math/code/poly/comp-rev/rev_1.cpp"
    ```

### Derived from Transposition Principle

The Power Projection problem is the transpose of Modular Composition. Kinoshita and Li point out that our composition algorithm above can be directly transposed from the Power Projection algorithm. Similarly, if optimization can be applied to the Power Projection algorithm, it can also be applied to the Modular Composition algorithm. We omit the details.

## References

1.  Yasunori Kinoshita, Baitian Li.[Power Series Composition in Near-Linear Time](https://arxiv.org/abs/2404.05177). FOCS 2024.
2.  Alin Bostan, Ryuhei Mori.[A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence](https://arxiv.org/abs/2008.08822). SOSA 2021: 118-132
3.  R. P. Brent and H. T. Kung. 1978.[Fast Algorithms for Manipulating Formal Power Series](https://doi.org/10.1145/322092.322099). J. ACM 25, 4 (Oct. 1978), 581–595.
4.  Daniel J. Bernstein. "[Fast multiplication and its applications](https://cr.yp.to/papers.html#multapps)." Pages 325–384 in Algorithmic number theory: lattices, number fields, curves and cryptography, edited by Joe Buhler, Peter Stevenhagen, Cambridge University Press, 2008, ISBN 978-0521808545.