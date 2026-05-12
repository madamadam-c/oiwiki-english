## Introduction

Constant-coefficient homogeneous linear recurrence sequences (also called C-finite or C-recursive sequences) are a common type of fundamental recurrence sequences.

For a sequence $\left(a_j\right)_{j\geq 0}$ and its recurrence relation

$$
a_n=\sum_{j=1}^{d}c_ja_{n-j},\qquad (n\geq d)
$$

where not all $c_j$ are zero, our goal is to compute $a_k$ given the initial values $a_0,\dots ,a_{d-1}$ and the coefficients $c_1,\dots ,c_d$ from the recurrence relation. If $k\gg d$, we want a faster algorithm.

Here $\left(a_j\right)_{j\geq 0}$ is called a $d$-order constant-coefficient homogeneous linear recurrence sequence.

### Fiduccia's Algorithm

Fiduccia's algorithm uses polynomial modulo and fast exponentiation to compute $a_k$ in $O(\mathsf{M}(d)\log k)$ time, where $O(\mathsf{M}(d))$ represents the time to multiply two polynomials of degree $O(d)$.

**Algorithm**: Construct polynomials $\Gamma(x):=x^d-\sum_{j=0}^{d-1}c_{d-j}x^j$ and $A(x):=\sum_{j=0}^{d-1}a_jx^j$, then

$$
a_k=\left\langle x^k\bmod{\Gamma(x)},A(x)\right\rangle
$$

where we define $\left\langle \left(\sum_{j=0}^{n-1}f_jx^j\right),\left(\sum_{j=0}^{n-1}g_jx^j\right) \right\rangle :=\sum_{j=0}^{n-1}f_jg_j$ as the inner product.

**Proof**: We define the companion matrix of $\Gamma(x)$ as

$$
C_\Gamma:=
\begin{bmatrix}
&&&c_d \\
1&&&c_{d-1} \\
&\ddots &&\vdots \\
&&1&c_1
\end{bmatrix}
$$

We define polynomial $b(x):=\sum_{j=0}^{d-1}b_jx^j$ and

$$
B_b:=\begin{bmatrix}b_0&b_1&\cdots &b_{d-1}\end{bmatrix}^{\intercal}
$$

Observe that

$$
\underbrace{\begin{bmatrix}
&&&c_d \\
1&&&c_{d-1} \\
&\ddots &&\vdots \\
&&1&c_1
\end{bmatrix}}_{C_\Gamma}
\underbrace{\begin{bmatrix}
b_0 \\
b_1 \\
\vdots \\
b_{d-1}
\end{bmatrix}}_{B_b}=
\underbrace{\begin{bmatrix}
c_db_{d-1} \\
b_0+c_{d-1}b_{d-1} \\
\vdots \\
b_{d-2}+c_1b_{d-1}
\end{bmatrix}} _ {B_{xb\bmod{\Gamma}}}
$$

And

$$
\begin{aligned}
C_\Gamma&=\begin{bmatrix}B_{x\bmod{\Gamma}}&B_{x^2\bmod{\Gamma}}&\cdots &B_{x^d\bmod{\Gamma}}\end{bmatrix}, \\
\left(C_\Gamma\right)^2&=\begin{bmatrix}B_{x^2\bmod{\Gamma}}&B_{x^3\bmod{\Gamma}}&\cdots &B_{x^{d+1}\bmod{\Gamma}}\end{bmatrix}, \\
\cdots \\
\left(C_\Gamma\right)^k&=\begin{bmatrix}B_{x^k\bmod{\Gamma}}&B_{x^{k+1}\bmod{\Gamma}}&\cdots &B_{x^{k+d}\bmod{\Gamma}}\end{bmatrix}
\end{aligned}
$$

Expressing this recurrence in matrix form:

$$
\begin{bmatrix}
a_{k} \\
a_{k+1} \\
\vdots \\
a_{k+d-1}
\end{bmatrix}=\underbrace{\begin{bmatrix}
&1&& \\
&&\ddots & \\
&&&1 \\
c_d&c_{d-1}&\cdots &c_1
\end{bmatrix}^k} _ {\left(\left(C_\Gamma\right)^{\intercal}\right)^k=\left(\left(C_\Gamma\right)^{k}\right)^{\intercal}}
\begin{bmatrix}
a_0 \\
a_{1} \\
\vdots \\
a_{d-1}
\end{bmatrix}
$$

The first row of $\left(\left(C_\Gamma\right)^{k}\right)^{\intercal}$ is $B_{x^k\bmod{\Gamma}}$, which proves the result by the definition of matrix multiplication.

### Represented as Rational Functions

For the sequence $\left(a_j\right)_{j\geq 0}$ above, there always exists a rational function

$$
\frac{P(x)}{Q(x)}=\sum_{j\geq 0}a_jx^j
$$

with $Q(x)=x^d\Gamma\left(x^{-1}\right)$ and $\deg{P}<d$. We call it "**rational function**" because $P(x),Q(x)$ are "**polynomials**".

**Proof**: For $P(x)=\sum_{j=0}^{d-1}p_jx^j$ and $Q(x):=\sum_{j=0}^{d}q_jx^j$, consider the coefficient definition of $\dfrac{P(x)}{Q(x)}=\sum_{j\geq 0}\tilde{q}_jx^j$, which is essentially the definition of formal power series "**division**":

$$
\tilde{q}_N=
\begin{cases}
p_0q_0^{-1},&\text{ if }N=0, \\
\left(p_N-\sum_{j=1}^{N}q_j\tilde{q}_{N-j}\right)\cdot q_0^{-1},&\text{ else if }N<d, \\
-q_0^{-1}\sum_{j=1}^{d}q_j\tilde{q}_{N-j},&\text{ otherwise}.
\end{cases}
$$

We only need to set

$$
P(x)=\left(\left(\sum_{j\geq 0}a_jx^j\right)\cdot x^d\Gamma\left(x^{-1}\right)\right)\bmod{x^d}
$$

Then according to the definition of $\tilde{q}_N$, we must have $\dfrac{P(x)}{Q(x)}=\sum_{j\geq 0}a_jx^j$.

### Bostan–Mori Algorithm

#### Computing a Single Term

Our goal remains: given the polynomials $P(x),Q(x)$ above, compute $\left\lbrack x^k\right\rbrack\dfrac{P(x)}{Q(x)}$.

The Bostan–Mori algorithm is based on Graeffe iteration. For the polynomials $P(x),Q(x)$ above, we have

$$
\frac{P(x)}{Q(x)}=\frac{P(x)Q(-x)}{Q(x)Q(-x)}=\frac{U_0(x^2)+xU_1(x^2)}{V(x^2)}
$$

Since the denominator $V(x^2)$ is an even function, the subproblem only needs to consider one side

$$
\left\lbrack x^k\right\rbrack\dfrac{P(x)}{Q(x)}=\left\lbrack x^{\left\lfloor k/2\right\rfloor}\right\rbrack \frac{U_{k\bmod{2}}(x)}{V(x)}
$$

We pay the cost of two polynomial multiplications to reduce the problem to at least half its original size, and when $k=0$, we clearly have $\left\lbrack x^0\right\rbrack \dfrac{P(x)}{Q(x)}=\dfrac{P(0)}{Q(0)}$, with the same time complexity.

#### Computing Several Consecutive Terms

The goal is: given the polynomials $P(x),Q(x)$ above, compute $\left\lbrack x^{\left\lbrack L,R\right)}\right\rbrack\dfrac{P(x)}{Q(x)}$. In the following computation, we only need to consider coefficients that "**affect**" the answer—this is the key to the Bostan–Mori algorithm.

Assume $\deg{P}<\deg{Q}$, otherwise we can perform one division to return to this case.

We first consider the simpler problem:

$$
\left\lbrack x^{\left\lbrack L,R\right)}\right\rbrack\frac{1}{Q(x)}=\left\lbrack x^{\left\lbrack L,R\right)}\right\rbrack\frac{1}{Q(x)Q(-x)}\cdot Q(-x)
$$

We need to compute $\left\lbrack x^{\left\lbrack L-\deg{Q},R\right)}\right\rbrack\dfrac{1}{Q(x)Q(-x)}$ and then multiply by $Q(-x)$ and extract the coefficients of $x^L,\dots ,x^{R-1}$. Let $V(x^2)=Q(x)Q(-x)$, then we only need to compute

$$
\left\lbrack x^{\left\lbrack \left\lceil\frac{L-\deg{Q}}{2}\right\rceil,\left\lceil\frac{R}{2}\right\rceil\right)}\right\rbrack\frac{1}{V(x)}
$$

to recover $\left\lbrack x^{\left\lbrack L-\deg{Q},R\right)}\right\rbrack\dfrac{1}{Q(x)Q(-x)}$. Then we only need to compute $\left\lbrack x^{\left\lbrack L-\deg{P},R\right)}\right\rbrack\dfrac{1}{Q(x)}$ and multiply by $P(x)$ to get $\left\lbrack x^{\left\lbrack L,R\right)}\right\rbrack\dfrac{P(x)}{Q(x)}$.

Although the algorithm above already works, the time complexity of each recursion is related to $R-L$. We want to at least get rid of $R-L$ during recursive computation. More specifically, we first consider computing $\left\lbrack x^{\left\lbrack L,L+\deg Q+1\right)}\right\rbrack \dfrac{1}{Q(x)}$:

$$
\left\lbrack x^{\left\lbrack L,L+\deg Q+1\right)}\right\rbrack \frac{1}{Q(x)}=\left\lbrack x^{\left\lbrack L,L+\deg Q+1\right)}\right\rbrack \dfrac{1}{Q(x)Q(-x)}\cdot Q(-x)
$$

We need to compute

$$
\left\lbrack x^{\left\lbrack L-\deg Q,L+\deg Q+1\right)}\right\rbrack \dfrac{1}{Q(x)Q(-x)}
$$

For $V(x^2)=Q(x)Q(-x)$, we only need to compute

$$
\left\lbrack x^{\left\lbrack \lceil (L-\deg Q)/2 \rceil,\lceil (L+\deg Q+1)/2 \rceil\right)}\right\rbrack \frac{1}{V(x)}
$$

This is because

$$
\left\lbrack x^{k}\right\rbrack\dfrac{1}{Q(x)Q(-x)}=
\begin{cases}
\left\lbrack x^{k/2}\right\rbrack\dfrac{1}{V(x)},&\text{if }k\equiv 0\pmod{2}, \\
0,&\text{otherwise}.
\end{cases}
$$

We know $L+\deg Q$ and $L-\deg Q$ have the same parity, so

$$
\left\lceil \frac{L+\deg Q+1}{2}\right\rceil -\left\lceil \frac{L-\deg Q}{2}\right\rceil =
\begin{cases}
\deg Q+1,&\text{if }L+\deg Q\equiv 0\pmod{2}, \\
\deg Q,&\text{otherwise}.
\end{cases}
$$

Thus we can write pseudocode:

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{Slice-Coefficients}(Q,L)\text{:} \\
&\textbf{Input}\text{: }Q(x)\in\mathbb{C}\left\lbrack x\right\rbrack,L\in\mathbb{Z}\text{.} \\
&\textbf{Output}\text{: }\left\lbrack x^{\left\lbrack L,L+\deg Q+1\right)}\right\rbrack Q(x)^{-1}\text{.} \\
1&\textbf{if }L\leq 1\textbf{ then return }\left\lbrack x^{\left\lbrack L,L+\deg Q+1\right)}\right\rbrack Q(x)^{-1} \\
&\text{Use other algorithm to compute }Q(x)^{-1} \\
2&V(x^2)\gets Q(x)Q(-x) \\
3&k\gets \left\lceil \frac{L-\deg Q}{2}\right\rceil \\
4&(t_k,\dots ,t_{k+\deg Q})\gets \operatorname{Slice-Coefficients}\left(V,k\right) \\
5&T(x)\gets x^{(L-\deg Q)\bmod{2}}\sum_{j=0}^{\deg Q}t_{j+k}x^{2j} \\
6&\textbf{return }\left\lbrack x^{\left\lbrack \deg Q,2\deg Q+1\right)}\right\rbrack T(x)Q(-x)
\end{array}
$$

But this algorithm alone is not enough—we need to find a new rational function and compute more coefficients.

#### Finding a New Rational Function Representation

We know part of the consecutive coefficients of $Q(x)$ itself and $Q(x)^{-1}$, such as $\left\lbrack x^{\left\lbrack L,L+\deg Q\right)}\right\rbrack Q(x)^{-1}$ for $L\geq 0$. We want to compute $\left\lbrack x^{\left\lbrack L+\deg Q,L+2\deg Q\right)}\right\rbrack Q(x)^{-1}$, which is equivalent to finding some $P(x)$ with $\deg P< \deg Q$ such that the first $\deg Q$ terms of $\dfrac{P(x)}{Q(x)}$ are the same as $\left\lbrack x^{\left\lbrack L,L+\deg Q\right)}\right\rbrack Q(x)^{-1}$. Simply put: the recurrence relation (the denominator of the rational function) remains unchanged; we only change the initial values (the numerator of the rational function).

Specifically, consider

$$
\frac{P(x)}{Q(x)}=\sum_{j\geq 0}a_jx^j
$$

Now we want to advance the recurrence by $n$ terms:

$$
\sum_{j\geq n}a_jx^{j-n}=\frac{P(x)}{Q(x)x^n}-\frac{Q(x)\sum_{j=0}^{n-1}a_jx^j}{Q(x)x^n}
$$

We first use $\operatorname{Slice-Coefficients}(Q,L-\deg{P})$ to compute $\left\lbrack x^{\left\lbrack L-\deg{P},L-\deg{P}+\deg{Q}+1\right)}\right\rbrack Q(x)^{-1}$, then extend to obtain $\left\lbrack x^{\left\lbrack L-\deg{P},L+\deg{Q}\right)}\right\rbrack Q(x)^{-1}$, and recalculate a numerator such that

$$
\frac{\widetilde{P}(x)}{Q(x)}=\sum_{j\geq 0}\left(\left\lbrack x^{L+j}\right\rbrack \frac{P(x)}{Q(x)}\right)x^j
$$

Finally, we use formal power series division to compute $\left\lbrack x^{\left\lbrack 0,R-L\right)}\right\rbrack\dfrac{\widetilde{P}(x)}{Q(x)}$ in $O(\mathsf{M}(d)\log L+\mathsf{M}(R-L))$ time.

## References

1.  Alin Bostan, Ryuhei Mori.[A Simple and Fast Algorithm for Computing the $N$-th Term of a Linearly Recurrent Sequence](https://arxiv.org/abs/2008.08822).