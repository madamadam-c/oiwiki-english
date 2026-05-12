Prerequisites: [Continued Fractions](./continued-fraction.md), [Quadratic Fields](./quadratic.md)

## Introduction

This article discusses the solution of the (generalized) Pell equation. The generalized Pell equation is the Diophantine equation in $x$ and $y$

$$
x^2-Dy^2=N,
$$

where $D$ is a positive integer that is not a perfect square[^not-square], and $N$ is a nonzero integer. The Pell equation in the narrow sense refers specifically to the special cases $N=1$ or $N=\pm 1$, and sometimes also includes the case $N=\pm 4$. The generalized Pell equation is closely related to finding quadratic integers with norm $N$ in the real quadratic integer ring, and these cases often referred to as the (narrow sense) Pell equation can be viewed as finding units in the real quadratic integer ring.

When this article mentions Pell's equation, it specifically refers to the case $N=1$. Accordingly, the case $N=-1$ is called the negative Pell equation[^neg-pell].

## Structure of Solutions

The integer solutions $(x,y)$ of the generalized Pell equation are closely related to the quadratic integers $x+y\sqrt{D}$. For this reason, solutions of Pell's equation in the literature are often written in the form $x+y\sqrt{D}$. Since the norm of a quadratic integer is

$$
N(x+y\sqrt{D}) = x^2-Dy^2,
$$

the generalized Pell equation is roughly equivalent to finding quadratic integers with norm $N$. However, there is a subtle difference between them. When both $x$ and $y$ are integers, $x+y\sqrt{D}$ is certainly a quadratic integer; conversely, a quadratic integer does not necessarily require both $x$ and $y$ to be integers—in the case $D\equiv 1\pmod 4$, $x$ and $y$ can also both be half-integers[^half-int].

This distinction is particularly important when finding fundamental units. Since a unit in the quadratic integer ring is a quadratic integer with norm $\pm 1$. For $D\equiv 2,3\pmod 4$, to find such a unit, one only needs to solve the generalized Pell equation with $N=\pm 1$; but for $D\equiv 1\pmod 4$, the case $N=\pm 4$ also needs to be considered. The solution method for units will be discussed [below](#the-case-of-norm-4).

To understand the structure of solutions to the generalized Pell equation, one must start with the [Brahmagupta identity](https://en.wikipedia.org/wiki/Brahmagupta%27s_identity):

$$
(x_1^2-Dy_1^2)(x_2^2-Dy_2^2)=(x_1x_2+Dy_1y_2)^2-D(x_1y_2+x_2y_1)^2.
$$

This is equivalent to the norm of quadratic integers being multiplicative, i.e.,

$$
\begin{aligned}
N\left(x_1+y_1\sqrt{D}\right)N\left(x_2+y_2\sqrt{D}\right) &= N\left((x_1+y_1\sqrt{D})(x_2+y_2\sqrt{D})\right) \\
&= N\left((x_1x_2+Dy_1y_2)+(x_1y_2+x_2y_1)\sqrt{D}\right).
\end{aligned}
$$

Using this identity, one can combine integer solutions of $x^2-Dy^2=N_1$ and $x^2-Dy^2=N_2$ to obtain integer solutions of $x^2-Dy^2=N_1N_2$. Of course, from the perspective of quadratic integers, combining solutions is just multiplying quadratic integers, which demonstrates the convenience of representing Pell equation solutions as quadratic integers. In particular, taking $N_1=N$ and $N_2=1$, if one knows a solution to $x^2-Dy^2=N$ and all solutions to the corresponding Pell equation $x^2-Dy^2=1$, then more solutions to $x^2-Dy^2=N$ can be obtained. Of course, this method may not generate all solutions. However, this at least shows that understanding the solution structure of the Pell equation is important for understanding the solution structure of the generalized Pell equation.

### Pell's Equation

The geometric meaning of the equation $x^2-Dy^2=1$ is a hyperbola with the real axis as the $x$-axis and the imaginary axis as the $y$-axis. Each point on the hyperbola uniquely corresponds to a nonzero value of $x+y\sqrt{D}$: the left branch of the hyperbola corresponds to negative values of $x+y\sqrt{D}$, while the right branch corresponds to positive values. Moreover, on each branch, as one moves from bottom to top, the values of $x+y\sqrt{D}$ are strictly increasing. The values of quadratic integers give the solutions of Pell's equation a natural ordering.

The hyperbola is symmetric about both the $x$-axis and $y$-axis, so to discuss solutions of Pell's equation one only needs to consider the segment in the first quadrant; the remaining solutions can be obtained through symmetry. This is equivalent to considering only solutions with $x+y\sqrt{D}>1$. If the equation has nontrivial solutions beyond $(\pm 1,0)$, there must exist a solution $(x_1,y_1)$ in the first quadrant with the smallest value of $x+y\sqrt{D}$, which is also the integer point with the smallest horizontal and vertical coordinates in the first quadrant (excluding the axes). This is called the fundamental solution of Pell's equation[^fundamental-solution]. According to the previous discussion, integer pairs $(x_k,y_k)$ satisfying $x_k+y_k\sqrt{D}=(x_1+y_1\sqrt{D})^k$ are all solutions of Pell's equation and lie in the first quadrant. Conversely, these are indeed all solutions of Pell's equation in the first quadrant. Using symmetry again, we obtain the following conclusion:

???+ note "Theorem"
    Let $(x_1,y_1)$ be the fundamental solution of the Pell equation $x^2-Dy^2=1$. Then all its solutions are
    
    $$
    \{(x,y):x+y\sqrt{D}=\pm(x_1+y_1\sqrt{D})^k,k\in\mathbf Z\}.
    $$

??? note "Proof"
    First, prove that there are no other solutions in the first quadrant. Suppose there is another solution $x+y\sqrt{D}$ and for some $k\ge 0$,
    
    $$
    x_k+y_k\sqrt{D}< x+y\sqrt{D}< x_{k+1}+y_{k+1}\sqrt{D}.
    $$
    
    Geometrically, this means the integer point $(x,y)$ lies between the points $(x_k,y_k)$ and $(x_{k+1},y_{k+1})$ on the hyperbola (excluding the endpoints). Multiplying the inequality by $x_k-y_k\sqrt{D}=(x_k+y_k\sqrt{D})^{-1}$ gives
    
    $$
    1< (x+y\sqrt{D})(x_k-y_k\sqrt{D})=(xx_k-Dyy_k)+(x_ky-xy_k)\sqrt{D} < x_1+y_1\sqrt{D}.
    $$
    
    According to the monotonicity mentioned earlier, this inequality shows that $(xx_k-Dyy_k,x_ky-xy_k)$ is an integer point between $(1,0)$ and $(x_1,y_1)$. This contradicts the choice of $(x_1,y_1)$.
    
    When extending solutions from the first quadrant to the entire plane, taking the reciprocal (negating the exponent $k$) corresponds to symmetry about the $x$-axis, and taking the overall negative corresponds to symmetry about the origin. Together with the trivial solution when $k=0$, we obtain all solutions of Pell's equation.

The previous discussion only assumed the existence of a fundamental solution. Now we need to show that Pell's equation always has nontrivial solutions.

???+ note "Theorem"
    The Pell equation $x^2-Dy^2=1$ always has integer solutions other than $(\pm 1,0)$.

??? note "Proof"
    First, [Dirichlet's Theorem](./continued-fraction.md#用渐近分数逼近实数) shows that there exist infinitely many pairs of positive integers $(x,y)$ such that
    
    $$
    \left|\dfrac{x}{y}-\sqrt{D}\right| \le \dfrac{1}{y^2}
    $$
    
    holds. They all satisfy
    
    $$
    |x^2-Dy^2|=y^2\left|\dfrac{x}{y}-\sqrt{D}\right|\left|\dfrac{x}{y}+\sqrt{D}\right| \le \dfrac{1}{y^2}+2\sqrt{D}<1+2\sqrt{D}.
    $$
    
    Therefore, there must exist an integer $m\in(-1-2\sqrt{D},1+2\sqrt{D})$ such that there are infinitely many pairs $(x,y)$ satisfying $x^2-Dy^2 = m$. Grouping these $(x,y)$ by their remainders modulo $m$, we know that for some pair of integers $(x_0,y_0)$, there are infinitely many $(x,y)$ such that $x\equiv x_0\pmod m$ and $y\equiv y_0\pmod m$ hold. Taking any two distinct pairs $(x_1,y_1)$ and $(x_2,y_2)$ satisfying these conditions, then
    
    $$
    \dfrac{x_1+y_1\sqrt{D}}{x_2+y_2\sqrt{D}}=\dfrac{x_1x_2-Dy_1y_2}{m}+\dfrac{x_2y_1-x_1y_2}{m}\sqrt{D}.
    $$
    
    Because according to the congruence relations,
    
    $$
    \begin{aligned}
    x_1x_2-Dy_1y_2 &\equiv x_0^2-Dy_0^2 = m \equiv 0 \pmod{|m|},\\
    x_2y_1-x_1y_2 &\equiv x_0y_0-x_0y_0 = 0 \pmod{|m|},
    \end{aligned}
    $$
    
    this shows the right-hand side yields integer solutions. Moreover, since $(x_1,y_1)\neq(x_2,y_2)$, it is nontrivial. This demonstrates that Pell's equation indeed has nontrivial solutions.

Of course, this section provides a non-constructive proof. When discussing solution methods for Pell's equation below, we will directly use the convergent of continued fractions to construct solutions to Pell's equation, thus providing another proof of the existence of nontrivial solutions to Pell's equation. Additionally, although the solution structure of Pell's equation obtained in this section is consistent with the structure of units in the real quadratic integer ring, for the case $D\equiv 1\pmod 4$, this section does not completely resolve the structure problem of units in the corresponding quadratic integer ring, which will be discussed further below.

### Generalized Pell Equation

The graph of the generalized Pell equation $x^2-Dy^2=N$ is also a hyperbola in the plane, also symmetric about the $x$-axis and $y$-axis. As noted earlier, some solutions of the equation $x^2-Dy^2=N$ may differ by a factor that is a solution of the Pell equation, which means the solutions of $x^2-Dy^2=N$ can be divided into equivalence classes. For two solutions $(x_1,y_1)$ and $(x_2,y_2)$ of $x^2-Dy^2=N$, if there exists a solution $(u,v)$ of the Pell equation such that $x_2+y_2\sqrt{D}=(x_1+y_1\sqrt{D})(u+v\sqrt{D})$, then the solutions $(x_1,y_1)$ and $(x_2,y_2)$ are said to be equivalent. The necessary and sufficient condition for two solutions to be equivalent is

$$
N\mid (x_1x_2-Dy_1y_2),\ N\mid (x_2y_1-x_1y_2).
$$

Since solutions of the Pell equation are relatively easy to find, a natural idea is to find one solution in each of the above equivalence classes. Once these solutions are known, all solutions of the generalized Pell equation can be obtained using the corresponding solutions of the Pell equation. In the equivalence classes of solutions to the generalized Pell equation, due to symmetry, each equivalence class has a solution with non-negative $y$ that is as small as possible: if such a solution is unique, it is called the fundamental solution of that equivalence class; otherwise, the equivalence class must have two solutions with non-negative $y$ that are minimal, and they are symmetric about the $y$-axis, in which case we choose the one with $x>0$ as the fundamental solution. Thus, solving the generalized Pell equation $x^2-Dy^2=N$ is equivalent to solving for its fundamental solution set $U$. Let the fundamental solution of the corresponding Pell equation be $(r,s)$, then the set of all solutions of the generalized Pell equation is

$$
\{(x,y):x+y\sqrt{D}=\pm(r+s\sqrt{D})^k(u+v\sqrt{D}),k\in\mathbf Z,u+v\sqrt{D}\in U\}.
$$

The fundamental solutions of the generalized Pell equation are necessarily finite. This is because from the general solution expression above, the absolute value $|u+v\sqrt{D}|$ must lie between $r-s\sqrt{D}$ and $r+s\sqrt{D}$. References at the end of the article provide stricter estimates for the range of coordinates of fundamental solutions. Of course, unlike the case of Pell's equation, the generalized Pell equation may have no solutions.

In addition to combining solutions, the method of obtaining all solutions in the same equivalence class using a solution $(u,v)$ of the generalized Pell equation and the fundamental solution $(r,s)$ of the Pell equation can also use the following recurrence relation

$$
x_{k} = 2rx_{k-1} - x_{k-2},\ y_{k} = 2ry_{k-1} - y_{k-2},
$$

where $x_k+y_k\sqrt{D}=(r+s\sqrt{D})^k(u+v\sqrt{D})$. This is because both $x_k$ and $y_k$ can be written in the form $A(r+s\sqrt{D})^k+B(r-s\sqrt{D})^k$ for some pair of real numbers $(A,B)$, and according to Vieta's theorem, $r\pm s\sqrt{D}$ are the two real roots of the equation $x^2-2rx+1=0$, so $x_n$ and $y_n$ both satisfy the above second-order linear recurrence relation with constant coefficients. Compared to combining solutions, this recurrence formula has fewer multiplications.

## Solution Methods

The solutions of both Pell's equation and the generalized Pell equation can be obtained based on continued fractions.

### PQa Algorithm

The algorithms discussed in this article are all based on the PQa algorithm, which can be used to find the continued fraction expansion of a specific quadratic irrational.

Let integers $P_0, Q_0, D$ satisfy $Q_0\neq 0$, $D>0$ and not a perfect square, and $P_0^2\equiv D\pmod{Q_0}$. Then the continued fraction expansion $[a_0,a_1,\cdots]$ of the quadratic irrational

$$
\omega=\dfrac{P_0+\sqrt{D}}{Q_0}
$$

can be obtained through the following [recurrence formula](./continued-fraction.md#二次无理数):

$$
a_k = \left\lfloor\dfrac{P_k+\sqrt{D}}{Q_k}\right\rfloor,\ P_{k+1} = a_kQ_k - P_k,\ Q_{k+1} = \dfrac{D-P_{k+1}^2}{Q_k}.
$$

Furthermore, the numerator and denominator $A_k$ and $B_k$ of the $k$-th convergent of $\omega$ are given by the following [recurrence formula](./continued-fraction.md#递推关系):

$$
A_k = a_kA_{k-1} + A_{k-2},\ B_k = a_kB_{k-1} + B_{k-2}
$$

with $A_{-1} = 1$, $A_{-2}=0$, $B_{-1}=0$, $B_{-2}=1$.

The correctness of these formulas has been proven in the article on continued fractions. There it is also explained that because quadratic irrationals are [periodic continued fractions](./continued-fraction.md#二次无理数), the triple $(P_k,Q_k,a_k)$ will eventually enter a cycle, so the algorithm always terminates in a finite number of steps. Let the minimal period length be $\ell$, and the earliest starting position of the cycle be $k_0$, then the continued fraction expansion of the quadratic irrational can be written as

$$
\omega=[a_0,\cdots,a_{k_0-1},\overline{a_{k_0},\cdots,a_{k_0+\ell-1}}].
$$

To solve Pell's equation using the PQa algorithm, the following theorem is needed:

???+ note "Theorem"
    Continuing with the above notation. Let $G_k=Q_0A_k-P_0B_k$, then the integer pair $(G_{k-1},B_{k-1})$ satisfies
    
    $$
    G_{k-1}^2-DB_{k-1}^2=(-1)^{k}Q_0Q_{k},
    $$
    
    and their greatest common divisor $\gcd(G_{k-1},B_{k-1})$ divides $Q_{k}$.

??? note "Proof"
    Let the $k$-th remainder (complete quotient) in the continued fraction expansion of $\omega$ be $\omega_k$, that is,
    
    $$
    \omega = [a_0,a_1,\cdots,a_{k-1},\omega_k] = \dfrac{\omega_k A_{k-1}+A_{k-2}}{\omega_k B_{k-1}+B_{k-2}}.
    $$
    
    Substituting $\omega=(P_0+\sqrt{D})/Q_0$ and $\omega_k=(P_k+\sqrt{D})/Q_k$ into the above gives
    
    $$
    \dfrac{P_0+\sqrt{D}}{Q_0} = \dfrac{(P_k+\sqrt{D})A_{k-1}+Q_kA_{k-2}}{(P_k+\sqrt{D})B_{k-1}+Q_kB_{k-2}}.
    $$
    
    After eliminating denominators on both sides and comparing coefficients of rational and irrational parts, then substituting the expression for $G_k$, we obtain:
    
    $$
    \begin{aligned}
    G_{k-1} &= P_kB_{k-1} + Q_kB_{k-2},\\
    DB_{k-1} &= P_kG_{k-1} + Q_kG_{k-2}.
    \end{aligned}
    $$
    
    Therefore, multiplying the first equation by $G_{k-1}$ and subtracting the second equation multiplied by $B_{k-1}$, we have
    
    $$
    \begin{aligned}
    G_{k-1}^2-DB_{k-1}^2 &= (B_{k-2}G_{k-1}-B_{k-1}G_{k-2})Q_k \\
    &= (A_{k-1}B_{k-2}-B_{k-1}A_{k-2})Q_0Q_k \\
    &= (-1)^kQ_0Q_k.
    \end{aligned}
    $$
    
    The last step uses the [difference formula for convergents](./continued-fraction.md#误差估计). This proves the first conclusion.
    
    To prove the second conclusion, substituting the expression for $G_k$ into the first conclusion gives
    
    $$
    (Q_0A_{k-1}-P_0B_{k-1})^2 - DB_{k-1}^2 = (-1)^kQ_0Q_k.
    $$
    
    Therefore, using $Q_0\mid(P_0^2-D)$,
    
    $$
    Q_0A_{k-1}^2 +\left(\dfrac{P_0^2-D}{Q_0}B_{k-1}- 2P_0A_{k-1}\right)B_{k-1} = (-1)^kQ_k.
    $$
    
    Hence, $\gcd(G_{k-1},B_{k-1}) = \gcd(Q_0A_{k-1},B_{k-1})$ divides $Q_k$.

This conclusion provides a method to find solutions to the equation $x^2-Dy^2=N$. If $Q_0>0$ is chosen reasonably and $P_0$ is chosen as a solution to the congruence $P_0^2\equiv D\pmod{Q_0}$, then by running the PQa algorithm on $(P_0+\sqrt{D})/Q_0$ until $(-1)^kQ_0Q_{k}=N$ is found, $(G_{k-1},B_{k-1})$ becomes a solution to the original equation. Moreover, if $Q_k=\pm 1$, then the solution obtained is necessarily primitive, meaning $G_{k-1}$ and $B_{k-1}$ are coprime.

This idea is the core of solving Pell's equation and the generalized Pell equation. After understanding this idea, we now proceed to handle some details of the algorithm and prove that all solutions can be obtained through this method.

### Pell's Equation

To solve the Pell equation $x^2-Dy^2=1$, one only needs to run the PQa algorithm on $(P_0,Q_0,D)=(0,1,D)$ until $(-1)^kQ_k=1$ appears. At this point, $(A_{k-1},B_{k-1})$ is a solution to Pell's equation (since $G_{k-1}$ is $A_{k-1}$ at this time). Of course, for Pell's equation, this process can be described more precisely.

First, solutions definitely appear at the end of the periodic part. This process is equivalent to performing the continued fraction expansion of $\sqrt{D}$. For this, there is already a [conclusion](./continued-fraction.md#纯循环连分数):

$$
\sqrt{D} = [\lfloor\sqrt{D}\rfloor,\overline{a_1,\cdots,a_{\ell-1},2\lfloor\sqrt{D}\rfloor}].
$$

Here, the period length is $\ell$, and the starting position is the 1st term (index starts from 0). Moreover, its $\ell$-th remainder equals $\lfloor\sqrt{D}\rfloor+\sqrt{D}$, which shows $Q_{\ell}=1$. Therefore, if $\ell$ is even, then $(A_{\ell-1},B_{\ell-1})$ is a nontrivial solution of Pell's equation; if $\ell$ is odd, then $(A_{2\ell-1},B_{2\ell-1})$ is a nontrivial solution of Pell's equation.

Next, we need to show that the solution obtained just now is definitely the fundamental solution. This conclusion is based on two reasons: first, all positive integer solutions $(x,y)$ of Pell's equation correspond to fractions $x/y$ that appear in the convergents of $\sqrt{D}$, which ensures that $(x,y)$ must be some $(A_k,B_k)$ in the PQa algorithm process; second, except for the end of the periodic part, no other position has $Q_k=1$, because the recurrence relation of $A_k$ and $B_k$ guarantees their values increase with the index, so the smallest positive integer solution (i.e., the fundamental solution) must appear at the position just indicated. These two reasons can be derived from the following two theorems respectively:

???+ note "Theorem"
    Suppose the equation $x^2-Dy^2=N$ has a positive integer solution $(x,y)$. If $|N|<\sqrt{D}$, then $\dfrac{x}{y}$ must equal a convergent of $\sqrt{D}$.

??? note "Proof"
    When $N>0$, since $x^2-Dy^2>0$, we have $x>y\sqrt{D}$. Hence,
    
    $$
    \left|\dfrac{x}{y}-\sqrt{D}\right| = \dfrac{N}{y(x+y\sqrt{D})}<\dfrac{N}{2y^2\sqrt{D}}<\dfrac{1}{2y^2}.
    $$
    
    According to [Legendre's Criterion](./continued-fraction.md#渐近分数的判定), $\dfrac{x}{y}$ is a convergent of $\sqrt{D}$.
    
    When $N<0$, $x>y\sqrt{D}$ no longer holds. So we instead consider the solutions of $y^2-\dfrac{1}{D}x^2=-\dfrac{N}{D}$. Since $\dfrac{|N|}{D}<\sqrt{\dfrac{1}{D}}$, the above argument still holds. This shows $\dfrac{y}{x}$ is a convergent of $\dfrac{1}{\sqrt{D}}$. According to the [Reciprocal Theorem](./continued-fraction.md#递推关系), $\dfrac{x}{y}$ is also a convergent of $\sqrt{D}$.

???+ note "Theorem"
    In the process of running the above PQa algorithm on $(P_0,Q_0,D)=(0,1,D)$, $Q_k=1$ necessarily implies $\ell\mid k$.

??? note "Proof"
    In the continued fraction expansion of $\sqrt{D}$, except for the 0-th remainder, all other remainders are [purely periodic continued fractions](./continued-fraction.md#纯循环连分数). Suppose $Q_k=1$. According to Galois's result, there must be a remainder $\omega_k=P_k+\sqrt{D}>1$, and its conjugate $-1<P_k-\sqrt{D}<0$, which means $P_k=\lfloor\sqrt{D}\rfloor$. Therefore, the remainder $\omega_k$ equals $\omega_\ell$. However, repetition of remainders implies periodicity of the continued fraction. If $k$ is not a multiple of $\ell$, it contradicts that $\ell$ is the minimal positive period. So necessarily $\ell\mid k$.

Synthesizing the discussion in this section, as long as we perform the continued fraction expansion of $\sqrt{D}$, i.e., start the PQa algorithm with $(P_0,Q_0,D)=(0,1,D)$, when we first obtain $Q_\ell=1$, we have reached the end of the first period. At this point, if $\ell$ is even, then $(A_{\ell-1},B_{\ell-1})$ is the fundamental solution of Pell's equation; otherwise, $(A_{2\ell-1},B_{2\ell-1})$ is the fundamental solution of Pell's equation. For the case where the period length $\ell$ is odd, one does not need to continue the PQa algorithm to twice the period length; it will be explained immediately that $A_{2\ell-1}+B_{2\ell-1}\sqrt{D}=(A_{\ell-1}+B_{\ell-1}\sqrt{D})^2$, so the fundamental solution of Pell's equation can be directly calculated from $(A_{\ell-1},B_{\ell-1})$. All other solutions of Pell's equation can be computed from the fundamental solution.

??? example "Example"
    1.  Solve the equation $x^2-14y^2=1$.
    
        Running the PQa algorithm on $(P_0,Q_0,D)=(0,1,14)$ gives the following results: (the red part is the first period)
    
        | $k$ | $P$ | $Q$ |        $a$       |  $A$  |  $B$  |  $G$  | $G^2-DB^2$ |
        | :-: | :-: | :-: | :--------------: | :---: | :--: | :---: | :--------: |
        | $0$ | $0$ | $1$ |        $3$       |  $3$  |  $1$ |  $3$  |    $-5$    |
        | $1$ | $3$ | $5$ | $\color{red}{1}$ |  $4$  |  $1$ |  $4$  |     $2$    |
        | $2$ | $2$ | $2$ | $\color{red}{2}$ |  $11$ |  $3$ |  $11$ |    $-5$    |
        | $3$ | $2$ | $5$ | $\color{red}{1}$ |  $15$ |  $4$ |  $15$ |     $1$    |
        | $4$ | $3$ | $1$ | $\color{red}{6}$ | $101$ | $27$ | $101$ |    $-5$    |
        | $5$ | $3$ | $5$ |        $1$       | $116$ | $31$ | $116$ |     $2$    |
    
        The period length $\ell=4$ is even. The minimal positive integer solution of the equation is $(G_3,B_3)=(15,4)$.
    2.  Solve the equation $x^2-41y^2=1$.
    
        Running the PQa algorithm on $(P_0,Q_0,D)=(0,1,41)$ gives the following results: (the red part is the first period)
    
        | $k$ | $P$ | $Q$ |        $a$        |   $A$   |   $B$  |   $G$   | $G^2-DB^2$ |
        | :-: | :-: | :-: | :---------------: | :-----: | :----: | :-----: | :--------: |
        | $0$ | $0$ | $1$ |        $6$        |   $6$   |   $1$  |   $6$   |    $-5$    |
        | $1$ | $6$ | $5$ |  $\color{red}{2}$ |   $13$  |   $2$  |   $13$  |     $5$    |
        | $2$ | $4$ | $5$ |  $\color{red}{2}$ |   $32$  |   $5$  |   $32$  |    $-1$    |
        | $3$ | $6$ | $1$ | $\color{red}{12}$ |  $397$  |  $62$  |  $397$  |     $5$    |
        | $4$ | $6$ | $5$ |        $2$        |  $826$  |  $129$ |  $826$  |    $-5$    |
        | $5$ | $4$ | $5$ |        $2$        | $2049$ |  $320$ | $2049$ |     $1$    |
        | $6$ | $6$ | $1$ |        $12$       | $25414$ | $3969$ | $25414$ |    $-5$    |
        | $7$ | $6$ | $5$ |        $2$        | $52877$ | $8258$ | $52877$ |     $5$    |
    
        The period length $\ell=3$ is odd. The minimal positive integer solution of the equation is $(G_5,B_5)=(2049,320)$. It can also be calculated from $(G_2,B_2)=(32,5)$:
    
        $$
        (32+5\sqrt{41})^2=2049+320\sqrt{41}.
        $$

### Negative Pell Equation

According to the discussion in the previous section, solutions to the negative Pell equation must also correspond to convergents of $\sqrt{D}$, and can only appear at positions where $(-1)^kQ_k=-1$. This can only occur at the end of the periodic part. Therefore, the negative Pell equation has solutions if and only if the period length $\ell$ is odd. When a solution exists, $(A_{\ell-1},B_{\ell-1})$ is the fundamental solution of the negative Pell equation. Its solution method is the same as in the previous section.

Using a proof similar to that for the structure of solutions to Pell's equation, the following conclusion can be proved:

???+ note "Theorem"
    Suppose the equation $x^2-Dy^2=-1$ has a solution, and its fundamental solution is $(x_1,y_1)$. Then all integer solutions to $x^2-Dy^2=\pm 1$ belong to the set
    
    $$
    \{(x,y):x+y\sqrt{D}=\pm(x_1+y_1\sqrt{D})^k,k\in\mathbf Z\}.
    $$
    
    In particular, the integer solution $(x_2,y_2)$ satisfying $x_2+y_2\sqrt{D}=(x_1+y_1\sqrt{D})^2$ is exactly the fundamental solution of $x^2-Dy^2=1$.

??? note "Proof"
    Due to symmetry, we only need to consider positive integer solutions, i.e., $x+y\sqrt{D}>1$. However, since $x^2-Dy^2=\pm 1$ consists of two branches of the hyperbola, $x+y\sqrt{D}$ cannot establish a one-to-one correspondence with $(x,y)$. To handle this difficulty, first prove that the above $(x_2,y_2)$ is the fundamental solution of $x^2-Dy^2=1$.
    
    Obviously, $(x_2,y_2)$ is a solution to $x^2-Dy^2=1$. If $(z,w)$ is the fundamental solution to $x^2-Dy^2=1$, then we must have $1<z+w\sqrt{D}\le x_2+y_2\sqrt{D}$. If the right inequality does not include equality, then dividing the inequality by $x_1+y_1\sqrt{D}$ gives $-x_1+y_1\sqrt{D}<(z+w\sqrt{D})(-x_1+y_1\sqrt{D})<x_1+y_1\sqrt{D}$. Expanding the middle term of this inequality yields the form $x'+y'\sqrt{D}$, whose norm is $-1$ and $(x',y')$ is also an integer solution. Taking the reciprocal of this inequality shows that $-x'+y'\sqrt{D}$ also lies between $-x_1+y_1\sqrt{D}$ and $x_1+y_1\sqrt{D}$. The quadratic integers $\pm x'+y'\sqrt{D}$ are reciprocals of each other, and one must be greater than $1$. However, there should be no other quadratic integers with norm $-1$ between $1$ and $x_1+y_1\sqrt{D}$, which contradicts the minimality of $x_1+y_1\sqrt{D}$. Therefore, we must have $x_2+y_2\sqrt{D}=z+w\sqrt{D}$, i.e., $(x_2,y_2)$ is the fundamental solution to $x^2-Dy^2=1$.
    
    Based on this, if there is a solution $(x,y)$ to $x^2-Dy^2=\pm 1$ that does not correspond to some $(x_1+y_1\sqrt{D})^k$, then there must exist a $k$ such that $(x_1+y_1\sqrt{D})^{2k}<x+y\sqrt{D}<(x_1+y_1\sqrt{D})^{2k+2}$. Factoring out $(x_1+y_1)^{2k+1}$, it shows there exists a quadratic integer $x'+y'\sqrt{D}\neq 1$ with norm $\pm 1$ lying between $-x_1+y_1\sqrt{D}$ and $x_1+y_1\sqrt{D}$. Repeating the argument using reciprocals from the previous paragraph shows this contradicts the minimality of $x_1+y_1\sqrt{D}$. Thus the original proposition is proven.

Since $(A_{\ell-1},B_{\ell-1})$ is the minimal positive integer solution of the negative Pell equation, and all positive integer solutions to $x^2-Dy^2=\pm 1$ appear in the set

$$
\{(x,y):x+y\sqrt{D}=(A_{\ell-1}+B_{\ell-1}\sqrt{D})^k,k\in\mathbf N_+\}
$$

and since these positive integer solutions must correspond to convergents at the end of the periodic part of $\sqrt{D}$ (the previous position), and the numerators and denominators of convergents are strictly increasing, we always have

$$
(A_{\ell-1}+B_{\ell-1}\sqrt{D})^k = A_{k\ell-1}+B_{k\ell-1}\sqrt{D}.
$$

Among all these positive integer solutions, when $k$ is odd they are solutions to the negative Pell equation, and when $k$ is even they are solutions to Pell's equation, alternating.

To determine whether the negative Pell equation has solutions, one needs to calculate the period length of the continued fraction expansion of $\sqrt{D}$, which is not easy to compute. Therefore, we hope to find a simpler judgment method. However, there is currently no condition that is simple and easy to compute[^solubility-neg-pell]. We only provide a simple conclusion here.

???+ note "Theorem"
    The equation $x^2-Dy^2=-1$ has solutions only if $4$ does not divide $D$ and $D$ does not contain prime factors of the form $4k+3$. Conversely, if $D=2$ or $D$ is a prime of the form $4k+1$, then the equation certainly has solutions.

??? note "Proof"
    First, if the negative Pell equation has solutions, then $-1$ is a quadratic residue modulo $D$, hence $-1$ is also a quadratic residue modulo any divisor $d$ of $D$, so $d\neq 4$ and $d$ is not a prime of the form $4k+3$. Conversely, the equation $x^2-2y^2=-1$ has a nontrivial solution $(1,1)$. The remaining case is when $D$ is a prime of the form $4k+1$.
    
    Let $D$ be a prime of the form $4k+1$. The idea is to start with the fundamental solution $(u,v)$ of the Pell equation $x^2-Dy^2=1$ and construct a solution $(\alpha,\beta)$ to $x^2-Dy^2=-1$. If $u$ is even, reducing $u^2-Dv^2=1$ modulo $4$ gives $v^2\equiv -1\pmod 4$, but $-1$ is not a quadratic residue modulo $4$. This contradiction shows $u$ is odd. Consider the equation $Dv^2=u^2-1=(u+1)(u-1)$. Since $u$ is odd, $\gcd(u+1,u-1)=\gcd(u+1,2)=2$. Based on this fact, the factors of $Dv^2$ are distributed to $u+1$ and $u-1$, one must be $2\alpha^2$ and the other $2D\beta^2$, where $\alpha$ and $\beta$ are coprime positive integers and $v=2\alpha\beta$. Substituting $u=\alpha^2+D\beta^2$ and $v=2\alpha\beta$ into $u^2-Dv^2=1$ yields $\alpha^2-D\beta^2=\pm 1$. Since $(u,v)$ is the fundamental solution to Pell's equation and $(\alpha,\beta)$ is a smaller positive integer pair than $(u,v)$, the right side cannot be $+1$, so it must be $-1$. This proves that $x^2-Dy^2=-1$ has a solution $(\alpha,\beta)$.

If $D$ is composite, then being square-free and not containing prime factors of the form $4k+3$ does not guarantee that $x^2-Dy^2=-1$ has solutions—for example, $x^2-34y^2=-1$ has no solutions.

??? example "Example"
    Using the calculation results from the examples above, the equation $x^2-14y^2=-1$ has no solutions, and the minimal positive integer solution of $x^2-41y^2=-1$ is $(G_2,B_2)=(32,5)$.

### The Case of Norm ±4

Next, we discuss solutions to the equation $x^2-Dy^2=\pm 4$. At this time, the behavior of solutions depends on the value of $D\bmod 4$.

Some cases are easy. If $D\equiv 0\pmod 4$, then $x$ is even, so $(x/2,y)$ is a solution to $u^2-(D/4)v^2=\pm 1$. In the remaining cases, $x$ and $y$ must be both odd or both even. If $x$ and $y$ are both odd, reducing both sides modulo $4$ yields $D\equiv 1\pmod 4$. So if $D\equiv 2,3\pmod 4$, then $x$ and $y$ can only be both even, so $(x/2,y/2)$ is a solution to $u^2-Dv^2=\pm 1$. Therefore, except for the case $D\equiv 1\pmod 4$, solutions to $x^2-Dy^2=\pm 4$ can all be obtained from solutions to the (negative) Pell equation.

Now we discuss the case $D\equiv 1\pmod 4$, which cannot be simply transformed into the already solved cases. To find the fundamental solution, apply the PQa algorithm to $(P_0,Q_0,D)=(1,2,D)$. When $Q_\ell=2$ is first obtained, we reach the end of the first period. If the period length $\ell$ is even, then $(G_{\ell-1},B_{\ell-1})$ is the fundamental solution to $x^2-Dy^2=4$; otherwise, $(G_{\ell-1},B_{\ell-1})$ is the fundamental solution to $x^2-Dy^2=-4$. Starting from $(G_{\ell-1},B_{\ell-1})$, all solutions to $x^2-Dy^2=\pm 4$ can be obtained:

$$
\left\{(x,y):\dfrac{x+y\sqrt{D}}{2}=\pm\left(\dfrac{G_{\ell-1}+B_{\ell-1}\sqrt{D}}{2}\right)^k,k\in\mathbf Z\right\}.
$$

If the period length $\ell$ is even, all of these are solutions to $x^2-Dy^2=4$; otherwise, when $k$ is odd, $(x,y)$ is a solution to $x^2-Dy^2=-4$, and when $k$ is even, $(x,y)$ is a solution to $x^2-Dy^2=4$.

The correctness of this algorithm depends on the following facts:

???+ note "Theorem"
    Suppose the equation $x^2-Dy^2=\pm 4$ has a positive integer solution $(x,y)$. If $D\equiv 1\pmod 4$, then $\dfrac{(x+y)/2}{y}$ must be a convergent of $\dfrac{1+\sqrt{D}}{2}$.

??? note "Proof"
    First note that at this time, $x$ and $y$ must have the same parity, so $(x+y)/2$ is an integer. If $(x,y)$ is a solution to $x^2-Dy^2=4$, then $x>y\sqrt{D}>2y$, so,
    
    $$
    \left|\dfrac{(x+y)/2}{y}-\dfrac{1+\sqrt{D}}{2}\right| = \dfrac{2}{y(x+y\sqrt{D})}<\dfrac{1}{2y^2}.
    $$
    
    According to [Legendre's Criterion](./continued-fraction.md#渐近分数的判定), $\dfrac{(x+y)/2}{y}$ is a convergent of $\dfrac{1+\sqrt{D}}{2}$.
    
    If $(x,y)$ is a solution to $x^2-Dy^2=-4$, to establish the above inequality, we only need to prove $4y<x+y\sqrt{D}$. This holds for all cases except possibly $D=5,13$. For $D=5,13$, substituting $x=\sqrt{Dy^2-4}$ into this inequality shows it is equivalent to $2(\sqrt{D}-2)y^2>1$. Except for $(D,y)=(5,1)$, this inequality holds for all $D=5,13$ and positive integers $y$. The remaining case is to verify $(D,y)=(5,1)$. At this time, the solution to $x^2-5y^2=-4$ is $(x,y)=(1,1)$, and what needs to be verified is that $\dfrac{1}{1}$ is a convergent of $\dfrac{1+\sqrt{5}}{2}=[\overline{1}]$, which is obviously true.

???+ note "Theorem"
    Let $D$ be a positive integer that is not a perfect square. The continued fraction expansion of the quadratic irrational $\omega=\dfrac{1+\sqrt{D}}{2}$ has the form
    
    $$
    \omega = [\lfloor\omega\rfloor,\overline{a_1,\cdots,a_{\ell-1},2\lfloor\omega\rfloor-1}],
    $$
    
    where $\ell$ is the period length, and $a_k=a_{\ell-k}$ holds for any $1<k<\ell$.

??? note "Proof"
    Since $\lfloor\omega\rfloor-1+\omega>1$ and its conjugate equals $\lfloor\omega\rfloor - \omega$, which lies between $-1$ and $0$, according to [Galois's result](./continued-fraction.md#纯循环连分数), $\lfloor\omega\rfloor-1+\omega$ is a purely periodic continued fraction and can be written as
    
    $$
    \lfloor\omega\rfloor-1+\omega = [\overline{2\lfloor\omega\rfloor-1,a_1,\cdots,a_{\ell-1}}].
    $$
    
    And Galois's result on reciprocal negative conjugates says
    
    $$
    \dfrac{1}{\omega-\lfloor\omega\rfloor} = [\overline{a_{\ell-1},\cdots,a_1,2\lfloor\omega\rfloor-1}].
    $$
    
    Therefore, according to the definition of continued fractions,
    
    $$
    \lfloor\omega\rfloor-1+\omega = 2\lfloor\omega\rfloor-1 + \dfrac{1}{\dfrac{1}{\omega-\lfloor\omega\rfloor}} = [2\lfloor\omega\rfloor-1,\overline{a_{\ell-1},\cdots,a_1,2\lfloor\omega\rfloor-1}].
    $$
    
    The uniqueness of continued fraction expansion shows $a_k=a_{\ell-k}$ for all $1<k<\ell$, so the expansion to be proved also holds.

???+ note "Theorem"
    Let $D\equiv 1\pmod 4$. In the process of running the above PQa algorithm on $(P_0,Q_0,D)=(1,2,D)$, $Q_k=2$ necessarily implies $\ell\mid k$.

??? note "Proof"
    In the continued fraction expansion of $\dfrac{1+\sqrt{D}}{2}$, except for the 0-th remainder, all other remainders are [purely periodic continued fractions](./continued-fraction.md#纯循环连分数). Suppose $Q_k=2$. According to Galois's result, there must be a remainder $\omega_k=\dfrac{P_k+\sqrt{D}}{2}$ whose conjugate $-1<\dfrac{P_k-\sqrt{D}}{2}<0$, i.e., $\sqrt{D}-2<P_k<\sqrt{D}$. Since in the PQa algorithm we always have $Q_k\mid P_k^2-D$ (see [algorithm correctness proof](./continued-fraction.md#二次无理数)), $P_k$ must be odd, which means $P_k$ takes a unique value, i.e., $P_k=P_0+2(\lfloor\omega\rfloor-1)$, that is, the remainder $\omega_k=\omega_\ell$. However, repetition of remainders implies periodicity of the continued fraction. If $k$ is not a multiple of $\ell$, it contradicts that $\ell$ is the minimal positive period. So necessarily $\ell\mid k$.

???+ note "Theorem"
    Let the minimal positive integer solution of the equation $x^2-Dy^2=\pm 4$ be $(x_1,y_1)$. Then all its solutions are
    
    $$
    \left\{(x,y):\dfrac{x+y\sqrt{D}}{2}=\pm\left(\dfrac{x_1+y_1\sqrt{D}}{2}\right)^k,k\in\mathbf Z\right\}.
    $$

??? note "Proof"
    Due to symmetry, we only need to consider positive integer solutions $(x,y)$. What needs to be proved here is only that the real pairs $(x,y)$ in the set are indeed integer solutions to $x^2-Dy^2=\pm 4$. The remaining part only needs to restate the proof of the structure of solutions to the equation $x^2-Dy^2=\pm 1$.
    
    Actually, what needs to be proved is that for any integer solutions $(x_1,y_1)$ and $(x_2,y_2)$ to $x^2-Dy^2=\pm 4$, the following defined positive real pair $(x_3,y_3)$ is still an integer solution:
    
    $$
    \dfrac{x_3+y_3\sqrt{D}}{2} = \dfrac{x_1+y_1\sqrt{D}}{2}\dfrac{x_2+y_2\sqrt{D}}{2}.
    $$
    
    Expanding the right-hand side and comparing coefficients of rational and irrational terms gives
    
    $$
    x_3=\dfrac{x_1x_2+Dy_1y_2}{2},\ y_3=\dfrac{x_1y_2+x_2y_1}{2}.
    $$
    
    Since for $i=1,2$ we have $x_i\equiv x_i^2\equiv Dy_i^2\equiv Dy_i\pmod 2$, we have
    
    $$
    \begin{aligned}
    2x_3 &= x_1x_2+Dy_1y_2 \equiv D^2y_1y_2+Dy_1y_2=D(D+1)y_1y_2 \equiv 0 \pmod 2,\\
    2y_3 &= x_1y_2+x_2y_1 \equiv Dy_1y_2+Dy_2y_1 = 2Dy_1y_2 \equiv 0 \pmod 2.
    \end{aligned}
    $$
    
    This shows $x_3$ and $y_3$ are both integers. Then using the property that norm is multiplicative, $(x_3,y_3)$ is a solution to $x^2-Dy^2=\pm 4$.

Synthesizing these facts and repeating the discussions from the previous sections, we can explain the correctness of the algorithm for solving $x^2-Dy^2=\pm 4$. These results show that the equation $x^2-Dy^2=\pm 4$ has a simple solution structure similar to $x^2-Dy^2=\pm 1$: all its solutions can be expressed through its minimal positive integer solution without solving other equations.

In fact, all solutions to $x^2-Dy^2=\pm 1$ can be found among solutions to $x^2-Dy^2=\pm 4$, so from this perspective, $x^2-Dy^2=\pm 4$ is more fundamental. Obviously, $(x,y)$ is a solution to $x^2-Dy^2=\pm 1$ if and only if $(2x,2y)$ is a solution to $x^2-Dy^2=\pm 4$. The analysis above indicates that when $D\equiv 2,3\pmod 4$, all solutions to $x^2-Dy^2=\pm 4$ are necessarily both even, so they correspond to solutions to $x^2-Dy^2=\pm 1$.

When $D\equiv 0\pmod 4$, among solutions $(x,y)$ to $x^2-Dy^2=\pm 4$, $x$ must be even, but $y$ may be odd. If in the minimal positive integer solution $(x_1,y_1)$ to $x^2-Dy^2=\pm 4$, $y_1$ is even, then $y$ is even in all solutions, so these integer solutions correspond one-to-one with integer solutions to $x^2-Dy^2=\pm 1$; however, if in the minimal integer solution $(x_1,y_1)$, $y_1$ is odd, then the parity of $y_k$ will be consistent with $k$, alternating, so only when $k$ is even does it correspond to a solution to $x^2-Dy^2=\pm 1$. If in the minimal positive integer solution to $x^2-Dy^2=\pm 4$, $y_1$ is odd and the norm of $x_1+y_1\sqrt{D}$ is $-4$, then for such $D$, $x^2-Dy^2=-4$ has solutions, but $x^2-Dy^2=-1$ has no solutions.

When $D\equiv 1\pmod 4$, solutions $(x,y)$ to $x^2-Dy^2=\pm 4$ may be both odd or both even. If the minimal positive integer solution $(x_1,y_1)$ is already both even, then all its integer solutions are also both even, so they always correspond to integer solutions to $x^2-Dy^2=\pm 1$. If the minimal positive integer solution $(x_1,y_1)$ is both odd, we have the following conclusion:

???+ note "Theorem"
    Let the minimal positive integer solution to $x^2-Dy^2=\pm 4$ be $(x_1,y_1)$. If $x_1$ and $y_1$ are both odd, then $D\equiv 5\pmod 8$, and the integer solution $(x,y)$ is even if and only if
    
    $$
    \dfrac{x+y\sqrt{D}}{2} = \pm\left(\dfrac{x_1+y_1\sqrt{D}}{2}\right)^{3k},k\in\mathbf Z.
    $$

??? note "Proof"
    Reducing both sides of $x_1^2-Dy_1^2=\pm 4$ modulo $8$ gives $D\equiv 5\pmod 8$. To prove the second conclusion, first prove that $(x_3,y_3)$ are both even, because
    
    $$
    \dfrac{x_3+y_3\sqrt{D}}{2} = \left(\dfrac{x_1+y_1\sqrt{D}}{2}\right)^{3} = \dfrac{x_1^3+3Dxy_1^2}{8}+\dfrac{3x_1^2y_1+Dy_1^3}{8}\sqrt{D},
    $$
    
    so we only need to prove the right-hand side is an integer. Since the square of an odd number is $1$ modulo $8$, we have
    
    $$
    \begin{aligned}
    &x_1^3+3Dxy_1 = x_1(x_1^2+3Dy_1) \equiv x_1(1+3\times 5\times 1) = 16x_1 = 0 \pmod 8,\\
    &3x_1^2y_1+Dy_1^3 = y_1(3x_1^2+Dy_1^2) \equiv y_1(3\times 1+5\times 1) = 8y_1 = 0 \pmod 8.
    \end{aligned}
    $$
    
    This shows $x_3,y_3$ are both even. Then for all $k\in\mathbf Z$, we have
    
    $$
    \dfrac{x+y\sqrt{D}}{2} = \pm\left(\dfrac{x_1+y_1\sqrt{D}}{2}\right)^{3k} = \pm\left(\dfrac{x_3+y_3\sqrt{D}}{2}\right)^k \in \mathbf Z,
    $$
    
    so at this time $(x,y)$ are both even. Conversely, for $r=1,2$, we always have
    
    $$
    \pm\left(\dfrac{x_1+y_1\sqrt{D}}{2}\right)^{3k+r} = \pm\left(\dfrac{x_3+y_3\sqrt{D}}{2}\right)^k\left(\dfrac{x_r+y_r\sqrt{D}}{2}\right).
    $$
    
    To prove the corresponding $(x,y)$ are not integers, we only need to prove the right-hand side is not an integer. For $r=1$, this is the known condition; for $r=2$, because
    
    $$
    \dfrac{x_2+y_2\sqrt{D}}{2} = \left(\dfrac{x_1+y_1\sqrt{D}}{2}\right)^2 = \dfrac{x_1^2+Dy_1^2}{4} + \dfrac{x_1y_1}{2}\sqrt{D},
    $$
    
    and $x_1^2+Dy_1^2\equiv 1+1\times 1=2\pmod 4$, $x_1y_1\equiv 1\pmod 2$, so this expression is also not an integer. This proves that only when the exponent is a multiple of $3$ are the corresponding solutions all even.

That is, among every three solutions to $x^2-Dy^2=\pm 4$, one is both even, which corresponds to integer solutions to $x^2-Dy^2=\pm 1$. This also shows that for $D\equiv 1\pmod 4$, $x^2-Dy^2=-4$ has solutions if and only if $x^2-Dy^2=-1$ has solutions.

The discussion so far is sufficient to compute the fundamental units of the real quadratic integer ring. Let $D$ be a positive integer without square factors. For $D\equiv 2,3\pmod 4$, one only needs to find the minimal positive integer solutions to $x^2-Dy^2=\pm 1$; for $D\equiv 1\pmod 4$, one only needs to find the minimal positive integer solutions to $x^2-Dy^2=\pm 4$. When the minimal positive integer solution $(x,y)$ is obtained, for $D\equiv 2,3\pmod 4$, the fundamental unit is $\pm x\pm y\sqrt{D}$; for $D\equiv 1\pmod 4$, the fundamental unit is $\dfrac{\pm x\pm y\sqrt{D}}{2}$.

??? example "Example"
    1.  Solve the equation $x^2-14y^2=\pm 4$.
    
        Using calculations from the previous example, the minimal positive integer solution to $x^2-14y^2=4$ is $(30,8)$, and $x^2-14y^2=-4$ has no solutions.
    2.  Solve the equation $x^2-41y^2=\pm 4$.
    
        Running the PQa algorithm on $(P_0,Q_0,D)=(1,2,41)$ gives the following results: (the red part is the first period)
    
        |  $k$ | $P$ | $Q$ |        $a$       |   $A$   |   $B$  |   $G$   | $G^2-DB^2$ |
        | :--: | :-: | :-: | :--------------: | :-----: | :----: | :-----: | :--------: |
        |  $0$ | $1$ | $2$ |        $3$       |   $3$   |   $1$  |   $5$   |    $-16$   |
        |  $1$ | $5$ | $8$ | $\color{red}{1}$ |   $4$   |   $1$  |   $7$   |     $8$    |
        |  $2$ | $3$ | $4$ | $\color{red}{2}$ |   $11$  |   $3$  |   $19$  |    $-8$    |
        |  $3$ | $5$ | $4$ | $\color{red}{2}$ |   $26$  |   $7$  |   $45$  |    $16$    |
        |  $4$ | $3$ | $8$ | $\color{red}{1}$ |   $37$  |  $10$  |   $64$  |    $-4$    |
        |  $5$ | $5$ | $2$ | $\color{red}{5}$ |  $211$  |  $57$  |  $365$  |    $16$    |
        |  $6$ | $5$ | $8$ |        $1$       |  $248$  |  $67$  |  $429$  |    $-8$    |
        |  $7$ | $3$ | $4$ |        $2$       |  $707$  |  $191$ |  $1223$ |     $8$    |
        |  $8$ | $5$ | $4$ |        $2$       | $1662$ |  $449$ |  $2875$ |    $-16$   |
        |  $9$ | $3$ | $8$ |        $1$       | $2369$ |  $640$ |  $4098$ |     $4$    |
        | $10$ | $5$ | $2$ |        $5$       | $13507$ | $3649$ | $23365$ |    $-16$   |
        | $11$ | $5$ | $8$ |        $1$       | $15876$ | $4289$ | $27463$ |     $8$    |
    
        The period length $\ell=5$ is odd. The minimal positive integer solution to $x^2-41y^2=-4$ is $(G_4,B_4)=(64,10)$, and the minimal positive integer solution to $x^2-41y^2=4$ is $(G_9,B_9)=(4098,640)$. They have the following relationship:
    
        $$
        \dfrac{4098+640\sqrt{41}}{2} = \left(\dfrac{64+10\sqrt{41}}{2}\right)^2.
        $$
    
        Of course, since $D\equiv 1\pmod 8$, according to the previous conclusion, the minimal positive integer solutions to $x^2-41y^2=\pm 4$ must both be even, and are always twice the minimal positive integer solutions to $x^2-41y^2=\pm 1$. So they can also be directly obtained from the previous example.
    3.  Solve the equation $x^2-13y^2=\pm 4$.
    
        Running the PQa algorithm on $(P_0,Q_0,D)=(1,2,13)$ gives the following results: (the red part is the first period)
    
        | $k$ | $P$ | $Q$ |        $a$       |  $A$ |  $B$ |  $G$  | $G^2-DB^2$ |
        | :-: | :-: | :-: | :--------------: | :--: | :--: | :---: | :--------: |
        | $0$ | $1$ | $2$ |        $2$       |  $2$ |  $1$ |  $3$  |    $-4$    |
        | $1$ | $3$ | $2$ | $\color{red}{3}$ |  $7$ |  $3$ |  $11$ |     $4$    |
        | $2$ | $3$ | $2$ |        $3$       | $23$ | $10$ |  $36$ |    $-4$    |
        | $3$ | $3$ | $2$ |        $3$       | $74$ | $33$ | $119$ |     $4$    |
    
        The period length $\ell=1$ is odd. The minimal positive integer solution to $x^2-13y^2=-4$ is $(G_0,B_0)=(3,1)$, and the minimal positive integer solution to $x^2-13y^2=4$ is $(G_1,B_1)=(11,3)$.
    
        Since the minimal positive integer solutions to this equation are all odd, we can use the pair $(G_2,B_2)=(36,10)$ at the end of the third period to obtain the minimal positive integer solutions $(18,5)$ to the corresponding (negative) Pell equation $x^2-13y^2=\pm 1$. It can also be obtained by direct calculation:
    
        $$
        \dfrac{36+10\sqrt{13}}{2}=\left(\dfrac{3+\sqrt{13}}{2}\right)^3.
        $$
    
        Moreover, this is a solution to the negative Pell equation. The minimal positive integer solution to the corresponding Pell equation is $(649,180)$.
    4.  Solve the equation $x^2-52y^2=\pm 4$.
    
        Since the minimal positive integer solutions to $x^2-13y^2=\pm 1$ are $(18,5)$ and $(649,180)$ respectively, the minimal positive integer solutions to $x^2-52y^2=\pm 4$ are $(36,10)$ and $(1298,360)$ respectively.

### General Case

Finally, we discuss the solution method for the generalized Pell equation.

For the case $|N|<\sqrt{D}$, there is a simple solution method. The conclusion from earlier shows that solutions $(x,y)$ to the equation $x^2-Dy^2=N$ must satisfy $\dfrac{x}{y}$ equals some convergent of $\sqrt{D}$. Moreover, according to the solution structure discussed earlier, each fundamental solution $(x,y)$ satisfies $x+y\sqrt{D}$ being less than or equal to the fundamental solution $x_1+y_1\sqrt{D}$ of the corresponding Pell equation $x^2-Dy^2=1$. Using the monotonicity of the denominator sequence $B_k$ in the PQa algorithm, these fundamental solutions to the generalized Pell equation must appear before the fundamental solution of the corresponding Pell equation. Therefore, one only needs to run the PQa algorithm on $(P_0,Q_0,D)=(0,1,D)$ until $Q_{\ell'}=1$ and $\ell'$ is even. During this process, for each $(A_k,B_k)$ that appears, check whether there exists an integer $f$ such that
    
    $$
    A_k^2-DB_k^2 = (-1)^{k+1}Q_{k+1} = N/f^2
    $$
    
    holds. If it does, then $(fA_k, fB_k)$ is recorded as a minimal positive integer solution. All $(fA_k, fB_k)$ recorded in this process are the complete minimal positive integer solutions to the equation $x^2-Dy^2=N$. Using $(A_{\ell'-1},B_{\ell'-1})$, i.e., the fundamental solution of the corresponding Pell equation, all solutions to the generalized Pell equation can be generated from these minimal positive integer solutions. Note that depending on whether the period length $\ell$ is even or odd, $\ell'$ may be $\ell$ or $2\ell$.

For the more general case of $N$, the above method no longer applies. First, enumerate all square factors $f^2$ of $N$, let $m=N/f^2$, and enumerate all solutions $z$ to the congruence $z^2\equiv D\pmod{|m|}$ satisfying $-|m|/2<z \le |m|/2$. Then run the PQa algorithm on $(P_0,Q_0,D)=(z,|m|,D)$ until $Q_k=\pm 1$ or a period has already completed. In the second case, there is no solution to the equation related to this set $(f,z)$. In the first case, further determine whether $(-1)^kQ_k=N/|N|$ matches. If they match in sign, then $(fG_{k-1},fB_{k-1})$ is a solution to $x^2-Dy^2=N$; otherwise, it is a solution to $x^2-Dy^2=-N$, and only when the corresponding negative Pell equation has solutions can the solution to $x^2-Dy^2=N$ be obtained by combining it with the fundamental solution of the corresponding negative Pell equation. After completing the traversal of all sets $(f,z)$, we obtain exactly one solution in each equivalence class of solutions to $x^2-Dy^2=N$, and that solution is the fundamental solution or minimal positive integer solution in that equivalence class. Using them together with the fundamental solution of the corresponding Pell equation, all integer solutions to the equation can be generated. This algorithm is called the **Lagrange–Matthews–Mollin algorithm**.

The correctness of this algorithm is guaranteed by the following theorem:

???+ note "Theorem"
    Suppose the equation $x^2-Dy^2=N$ has an integer solution $(x,y)$ with $x\ge 0, y>0,\gcd(x,y)=1$. Let $Q_0=|N|$, then $\gcd(Q_0,y)=1$. Let $P_0$ be a solution to the congruence $x\equiv -P_0y\pmod{Q_0}$ with $-Q_0/2<P_0\le Q_0/2$, and let $X$ be the integer such that $x=Q_0X-P_0y$ holds. Then $P_0^2\equiv D\pmod{Q_0}$, $\dfrac{X}{y}$ is a convergent $\dfrac{A_{k-1}}{B_{k-1}}$ of $\omega=\dfrac{P_0+\sqrt{D}}{Q_0}$, and $Q_k=(-1)^k\dfrac{N}{|N|}$.

??? note "Proof"
    Using $x\equiv -P_0y\pmod{Q_0}$ and $x^2-Dy^2=N\equiv 0\pmod{Q_0}$, we obviously have $P_0^2\equiv D\pmod{Q_0}$. Therefore,
    
    $$
    P_0x+Dy\equiv -P_0^2y+Dy = (D-P_0^2)y\equiv 0\pmod{Q_0}.
    $$
    
    From this, we can consider the integer matrix
    
    $$
    \begin{pmatrix}P & R \\ Q & S\end{pmatrix}
    =
    \begin{pmatrix}X & \dfrac{P_0x+Dy}{Q_0} \\ y & x\end{pmatrix}.
    $$
    
    Its determinant is
    
    $$
    PS-QR = \dfrac{x(x+P_0y)-y(P_0x+Dy)}{Q_0} = \dfrac{x^2-Dy^2}{Q_0} = \pm 1.
    $$
    
    Moreover, letting $\zeta =\sqrt{D} > 1$, we have
    
    $$
    \dfrac{P\zeta+R}{Q\zeta+S} = \dfrac{(x+P_0y)\sqrt{D}+(P_0x+Dy)}{(x+y\sqrt{D})Q_0} = \dfrac{P_0+\sqrt{D}}{Q_0} = \omega.
    $$
    
    Next, we prove $\dfrac{P}{Q}$ is a convergent of $\omega$. Suppose $\dfrac{P}{Q}$ has a [continued fraction expansion](./continued-fraction.md#简单连分数)
    
    $$
    \dfrac{P}{Q} = [a_0,a_1,\cdots,a_k]
    $$
    
    and $PS-QR = (-1)^{k-1}$. If $\dfrac{p_k}{q_k}$ is its $k$-th convergent, then $(p_k,q_k)=(P,Q)$, and according to the [difference formula for convergents](./continued-fraction.md#误差估计), $p_kq_{k-1}-q_kp_{k-1}=(-1)^{k-1}$. This shows
    
    $$
    p_k(S-q_{k-1}) = q_k(R-p_{k-1}).
    $$
    
    We consider cases:
    
    -   If $S=0$, then it is easy to verify $Q=R=1$, so $\omega=P+\zeta^{-1}=[P,\zeta]$, hence $\dfrac{P}{Q}=P$ is the $0$-th convergent of $\omega$;
    -   If $Q=S>0$, then $Q=S=1$ and $P-R=\pm 1$. At this time,
        -   If $P=R+1$, then $\omega=R+\dfrac{1}{1+\zeta^{-1}}=[R,1,\zeta]$, hence $\dfrac{P}{Q}=\dfrac{R+1}{1}=[R,1]$ is the $1$-st convergent of $\omega$;
        -   If $P=R-1$, then $\omega=R-1+\dfrac{1}{1+\zeta}=[R-1,\zeta-1]$, hence $\dfrac{P}{Q}=R-1$ is the $0$-th convergent of $\omega$;
    -   If $Q\neq S>0$, then since $Q=q_k\mid(S-q_{k-1})$, there always exists an integer $\kappa$ such that $S=\kappa q_k+q_{k-1}$ and $R=\kappa p_k+p_{k-1}$ hold. Since $q_k\ge q_{k-1}$ and $S>0$, $\kappa\ge 0$. Therefore, $\omega=\dfrac{(\kappa+\zeta)p_k+p_{k-1}}{(\kappa+\zeta)q_k+q_{k-1}}=[a_0,a_1,\cdots,a_k,\kappa+\zeta]$, hence $\dfrac{P}{Q}$ is its $k$-th convergent.
    
    In summary, $\dfrac{X}{y}$ is always a convergent of $\omega=\dfrac{P_0+\sqrt{D}}{Q_0$, and following the notation in the PQa algorithm, we denote it as $\dfrac{A_{k-1}}{B_{k-1}}. Since $A_{k-1}^2-DB_{k-1}^2=(-1)^kQ_0Q_k$, we have $Q_k=(-1)^k\dfrac{N}{|N|}$.

This theorem guarantees that all positive solutions to the equation exist in the convergents of the corresponding quadratic irrational. Because when using the PQa algorithm to compute convergents, once entering the periodic part, it can be guaranteed that the convergents are always positive. Therefore, as long as we enumerate all quadratic irrationals allowed by the theorem conditions and compute their convergents until within one period, we can find a solution. Since two solutions appearing in the convergents of the same quadratic irrational are definitely equivalent, we only need to get the first solution satisfying $(-1)^kQ_k=N/|N|$ and stop the subsequent calculations. Different from all previous algorithms, here the $k$ satisfying the condition may appear before entering the period.

??? example "Example"
    1.  Solve the equation $x^2-157y^2=12$.
    
        Since $12^2<157$, running the PQa algorithm on $(P_0,Q_0,D)=(0,1,157)$ gives the following results: (the red part is the first period)
    
        |  $k$ |  $P$ |  $Q$ |        $a$        |         $A$        |        $B$       |         $G$        | $G^2-DB^2$ |
        | :--: | :--: | :--: | :---------------: | :----------------: | :--------------: | :----------------: | :--------: |
        |  $0$ |  $0$ |  $1$ |        $12$       |        $12$        |        $1$       |        $12$        |    $-13$   |
        |  $1$ | $12$ | $13$ |   $\color{red}1$  |        $13$        |        $1$       |        $13$        |    $12$    |
        |  $2$ |  $1$ | $12$ |   $\color{red}1$  |        $25$        |        $2$       |        $25$        |    $-3$    |
        |  $3$ | $11$ |  $3$ |   $\color{red}7$  |        $188$       |       $15$       |       $188$       |    $19$    |
        |  $4$ | $10$ | $19$ |   $\color{red}1$  |        $213$       |       $17$       |       $213$       |    $-4$    |
        |  $5$ |  $9$ |  $4$ |   $\color{red}5$  |       $1253$       |       $100$      |       $1253$       |     $9$    |
        |  $6$ | $11$ |  $9$ |   $\color{red}2$  |       $2719$       |       $217$      |       $2719$       |    $-12$   |
        |  $7$ |  $7$ | $12$ |   $\color{red}1$  |       $3972$       |       $317$      |       $3972$       |    $11$    |
        |  $8$ |  $5$ | $11$ |   $\color{red}1$  |       $6691$       |       $534$      |       $6691$       |    $-11$   |
        |  $9$ |  $6$ | $11$ |   $\color{red}1$  |      $10663$      |       $851$      |      $10663$      |    $12$    |
        | $10$ |  $5$ | $12$ |   $\color{red}1$  |      $17354$      |      $1385$      |      $17354$      |    $-9$    |
        | $11$ |  $7$ |  $9$ |   $\color{red}2$  |      $45371$      |      $3621$      |      $45371$      |     $4$    |
        | $12$ | $11$ |  $4$ |   $\color{red}5$  |      $244209$      |      $19490$     |      $244209$      |    $-19$   |
        | $13$ |  $9$ | $19$ |   $\color{red}1$  |      $289580$      |      $23111$     |      $289580$      |     $3$    |
        | $14$ | $10$ |  $3$ |   $\color{red}7$  |      $2271269$     |     $181267$     |      $2271269$     |    $-12$   |
        | $15$ | $11$ | $12$ |   $\color{red}1$  |      $2560849$     |     $204378$     |      $2560849$     |    $13$    |
        | $16$ |  $1$ | $13$ |   $\color{red}1$  |      $4832118$     |     $385645$     |      $4832118$     |    $-1$    |
        | $17$ | $12$ | $1$ | $\color{red}{24}$ |     $118531681$    |     $9459858$    |     $118531681$    |    $13$    |
        | $18$ | $12$ | $13$ |        $1$        |     $123363799$    |     $9845503$    |     $123363799$    |    $-12$   |
        | $19$ |  $1$ | $12$ |        $1$        |     $241895480$    |    $19305361$    |    $241895480$    |     $3$    |
        | $20$ | $11$ |  $3$ |        $7$        |    $1816632159$    |   $144983030$   |    $1816632159$    |    $-19$   |
        | $21$ | $10$ | $19$ |        $1$        |    $2058527639$    |   $164288391$   |    $2058527639$    |     $4$    |
        | $22$ |  $9$ |  $4$ |        $5$        |   $12109270354$   |   $966424985$   |   $12109270354$   |    $-9$    |
        | $23$ | $11$ |  $9$ |        $2$        |   $26277068347$   |  $2097138361$   |   $26277068347$   |    $12$    |
        | $24$ |  $7$ | $12$ |        $1$        |   $38386338701$   |  $3063563346$   |   $38386338701$   |    $-11$   |
        | $25$ |  $5$ | $11$ |        $1$        |   $64663407048$   |  $5160701707$   |   $64663407048$   |    $11$    |
        | $26$ |  $6$ | $11$ |        $1$        |  $103049745749$   |  $8224265053$   |  $103049745749$   |    $-12$   |
        | $27$ |  $5$ | $12$ |        $1$        |  $167713152797$   |  $13384966760$  |  $167713152797$   |     $9$    |
        | $28$ |  $7$ |  $9$ |        $2$        |  $438476051343$   |  $34994198573$  |  $438476051343$   |    $-4$    |
        | $29$ | $11$ |  $4$ |        $5$        | $2360093409512$  | $188355959625$  | $2360093409512$  |    $19$    |
        | $30$ |  $9$ | $19$ |        $1$        | $2798569460855$  | $223350158198$  | $2798569460855$  |    $-3$    |
        | $31$ | $10$ |  $3$ |        $7$        | $21950079635497$ | $1751807067011$ | $21950079635497$ |    $12$    |
