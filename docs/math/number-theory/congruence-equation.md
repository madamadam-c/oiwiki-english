author: iamtwz, aofall, CCXXXI, CoelacanthusHex, Great-designer, Marcythm, Persdre, shuzhouliu, Tiphereth-A, Xeonacid

## Definition

???+ abstract "Congruence Equation"
    For a positive integer $m$ and a univariate polynomial with integer coefficients $f(x)=\sum_{i=0}^n a_ix^i$, where the unknown $x\in\mathbf{Z}_m$, an equation of the form
    
    $$
    f(x)\equiv 0\pmod m\tag{1}
    $$
    
    is called a univariate **congruence equation** (Congruence Equation) in modulus $m$ for the unknown $x$.
    
    If $a_n\not\equiv 0\pmod m$, then the above equation is called an $n$-degree congruence equation.
    
    Congruence equation systems can be defined similarly.

For content about linear congruence equations and systems, please refer to [Linear Congruence Equation](./linear-equation.md) and [Chinese Remainder Theorem](./crt.md).

This article first studies the solvability and solution set structure of congruence equations, then briefly introduces methods for solving higher-degree congruence equations.

As can be known from the [Chinese Remainder Theorem](./crt.md), solving congruence equations with composite modulus $m$ can be reduced to solving prime power modulus cases. Therefore, the following only introduces theories related to prime power modulus congruence equations and prime modulus congruence equations.

## Prime Power Modulus Congruence Equations

Assume here that the modulus $m=p^e~(p\in\mathbf{P},~e\in\mathbf{Z}_{>1})$.

Note that if $x_0$ is a solution of the equation

$$
f(x)\equiv 0\pmod{p^e}
$$

then $x_0$ is also a solution of the equation

$$
f(x)\equiv 0\pmod{p^{e-1}}.
$$

This inspires us to try to construct solutions for higher modulus powers from solutions for lower modulus powers. We have the following theorem:

<a id="theorem-1"></a>

???+ note "Theorem 1 (Hensel's Lemma)"
    For a prime $p$ and integer $e>1$, let $f(x)=\sum_{i=0}^na_ix^i~(p^e\nmid a_n)$ be a polynomial with integer coefficients, and let $f'(x)=\sum_{i=1}^nia_ix^{i-1}$ be its derivative. Let $x_0$ be a solution of the equation
    
    $$
    f(x)\equiv 0\pmod{p^{e-1}}\tag{2}
    $$
    
    Then:
    
    1.  If $f'(x_0)\not\equiv 0\pmod p$, then there exists an integer $t$ such that
    
        $$
        x=x_0+p^{e-1}t \tag{3}
        $$
    
        is a solution of the equation
    
        $$
        f(x)\equiv 0\pmod{p^e} \tag{4}
        $$
    
    2.  If $f'(x_0)\equiv 0\pmod p$ and $f(x_0)\equiv 0\pmod{p^e}$, then for $t=0,1,\dots,p-1$, the $x$ determined by equation $(3)$ are all solutions of equation $(4)$.
    3.  If $f'(x_0)\equiv 0\pmod p$ and $f(x_0)\not\equiv 0\pmod{p^e}$, then no solution of equation $(4)$ can be constructed from equation $(3)$.

???+ note "Proof"
    We assume equation $(3)$ is a solution of equation $(4)$, i.e.,
    
    $$
    f(x_0+p^{e-1}t)\equiv 0\pmod{p^e}
    $$
    
    After rearrangement, we get
    
    $$
    f(x_0)+p^{e-1}tf'(x_0)\equiv 0\pmod{p^e}
    $$
    
    Thus
    
    $$
    tf'(x_0)\equiv -\frac{f(x_0)}{p^{e-1}}\pmod p\tag{5}
    $$
    
    1.  If $f'(x_0)\not\equiv 0\pmod p$, then equation $(5)$ in $t$ has a unique solution $t_0$, and substituting into equation $(3)$ verifies that it is a solution of equation $(4)$.
    2.  If $f'(x_0)\equiv 0\pmod p$ and $f(x_0)\equiv 0\pmod{p^e}$, then any $t$ satisfies equation $(5)$, and substituting into equation $(3)$ verifies that they are all solutions of equation $(4)$.
    3.  If $f'(x_0)\equiv 0\pmod p$ and $f(x_0)\not\equiv 0\pmod{p^e}$, then equation $(5)$ has no solution, so no solution of equation $(4)$ can be constructed from equation $(3)$.

We then have the following corollary:

<a id="corollary-1"></a>

???+ note "Corollary 1"
    For the $p$, $e$, $f(x)$, $x_0$ of [Theorem 1](#theorem-1):
    
    1.  If $s$ is a solution of equation $f(x)\equiv 0\pmod p$ and $f'(s)\not\equiv 0\pmod p$, then there exists $x_s\in\mathbf{Z}_{p^e}$, $x_s\equiv s\pmod p$ such that $x_s$ is a solution of equation $(4)$.
    2.  If equation $f(x)\equiv 0\pmod p$ and equation $f'(x)\equiv 0\pmod p$ have no common solutions, then equation $(4)$ and equation $f(x)\equiv 0\pmod p$ have the same number of solutions.

Thus we can reduce prime power modulus congruence equations to prime modulus congruence equations.

## Prime Modulus Congruence Equations

Let $p\in\mathbf{P}$ here, and $f(x)=\sum_{i=0}^na_ix^i$ be a polynomial with integer coefficients, where $p\nmid a_n$, $x\in\mathbf{Z}_p$.

<a id="theorem-2"></a>

???+ note "Theorem 2"
    If equation
    
    $$
    f(x)\equiv 0\pmod p\tag{6}
    $$
    
    has $k$ distinct solutions $x_1,x_2,\dots,x_k~(k\leq n)$, then
    
    $$
    f(x)\equiv g(x)\prod_{i=1}^k(x-x_i)\pmod p,
    $$
    
    where $\deg g=n-k$ and $[x^{n-k}]g(x)=a_n$.

???+ note "Proof"
    Apply mathematical induction on $k$.
    
    -   When $k=1$, by polynomial division with remainder, we have $f(x)=(x-x_1)g(x)+r$, where $r\in\mathbf{Z}$.
        
        From $f(x_1)\equiv 0\pmod p$, we know $r\equiv 0\pmod p$, thus $f(x)\equiv(x-x_1)g(x)\pmod p$.
    -   Assume the proposition holds for $k-1$ ($k>1$). Now let $f(x)$ have $k$ distinct solutions $x_1,x_2,\dots,x_k$, then $f(x)\equiv(x-x_1)h(x)\pmod p$. Furthermore, for all $i=2,3,\dots,k$, we have
        
        $$
        0\equiv f(x_i)\equiv (x_i-x_1)h(x_i)\pmod p
        $$
        
        Thus $h(x)$ has $k-1$ distinct solutions $x_2,x_3,\dots,x_k$, and by the induction hypothesis,
        
        $$
        h(x)\equiv g(x)\prod_{i=2}^k(x-x_i)\pmod p
        $$
        
        where $\deg g=n-k$ and $[x^{n-k}]g(x)=a_n$.
        
        Therefore, the proposition is proved.

<a id="corollary-2"></a>

???+ note "Corollary 2"
    For prime $p$,
    
    -   $(\forall x\in\mathbf{Z}),~~x^{p-1}-1 \equiv \prod_{i=1}^{p-1}(x-i)\pmod p$.
    -   ([Wilson's Theorem](./factorial.md#wilsons-theorem)) $(p-1)! \equiv -1 \pmod p$.

<a id="theorem-3lagrange-theorem"></a>

???+ note "Theorem 3 (Lagrange's Theorem)"
    Equation $(6)$ has at most $n$ distinct solutions.

???+ note "Proof"
    Assume $f(x)$ has $n+1$ distinct solutions $x_1,x_2,\dots,x_{n+1}$, then by [Theorem 2](#theorem-2), for $x_1,x_2,\dots,x_n$ we have
    
    $$
    f(x)\equiv a_n\prod_{i=1}^n(x-x_i)\pmod p
    $$
    
    Let $x=x_{n+1}$, then
    
    $$
    0\equiv f(x_{n+1})\equiv a_n\prod_{i=1}^n(x_{n+1}-x_i)\pmod p
    $$
    
    But the right side is clearly not a multiple of $p$, so the assumption leads to a contradiction.

<a id="corollary-3"></a>

???+ note "Corollary 3"
    If the congruence equation $\sum_{i=0}^nb_ix^i\equiv 0\pmod p$ has more than $n$ solutions, then
    
    $$
    (\forall i=0,1,\dots,n),~~p\mid b_i.
    $$

<a id="theorem-4"></a>

???+ note "Theorem 4"
    If the number of solutions of equation $(6)$ is not $p$, then there exists a polynomial $r(x)$ with integer coefficients satisfying $\deg r<p$ such that the solution sets of $f(x)\equiv 0\pmod p$ and $r(x)\equiv 0\pmod p$ are identical.

???+ note "Proof"
    Assume $n\geq p$, perform polynomial division on $f(x)$
    
    $$
    f(x)=g(x)\left(x^p-x\right)+r(x)
    $$
    
    where $\deg r<p$.
    
    From [Fermat's Little Theorem](./fermat.md), for any integer $x$ we have $x^p\equiv x\pmod p$. Thus
    
    -   If $r(x)\equiv 0\pmod p$, then by [Corollary 2](#corollary-2), $f(x)$ has $p$ distinct solutions.
    -   If $r(x)\not\equiv 0\pmod p$, then from $f(x)\equiv r(x)\pmod p$, the solution sets of $f(x)$ and $r(x)$ are identical.

We can use this theorem to reduce the degree of congruence equations.

<a id="theorem-5"></a>

???+ note "Theorem 5"
    Let $n\leq p$, then equation
    
    $$
    x^n+\sum_{i=0}^{n-1}a_ix^i\equiv 0\pmod p\tag{7}
    $$
    
    has $n$ solutions if and only if there exist polynomials with integer coefficients $q(x)$, $r(x)~(\deg r < n)$ such that
    
    $$
    x^p-x=f(x)q(x)+pr(x). \tag{8}
    $$

???+ note "Proof"
    -   Necessity: From polynomial division, there exist polynomials with integer coefficients $q(x)$, $r_1(x)~(\deg r_1 < n)$ such that
        
        $$
        x^p-x=f(x)q(x)+r_1(x).
        $$
        
        If equation $(7)$ has $n$ solutions, then $r_1\equiv 0\pmod p$ also has $n$ the same solutions. Then by [Corollary 3](#corollary-3), there exists a polynomial with integer coefficients $r(x)$ satisfying $r_1(x)=pr(x)$. Thus the proposition is proved.
    -   Sufficiency: If equation $(8)$ holds, then from [Fermat's Little Theorem](./fermat.md), for any integer $x$,
        
        $$
        0\equiv x^p-x\equiv f(x)q(x)\pmod p.
        $$
        
        That is, equation $f(x)q(x)\equiv 0\pmod p$ has $p$ solutions.
        
        Let the number of solutions of equation $(7)$ be $s$, then by [Lagrange's Theorem](#theorem-3lagrange-theorem), $s\leq n$.
        
        Also, since $\deg q=p-n$, by [Lagrange's Theorem](#theorem-3lagrange-theorem), the number of solutions of $q(x)\equiv 0\pmod p$ does not exceed $p-n$. The solution set of $f(x)q(x)\equiv 0\pmod p$ is the union of the solution set of $f(x)\equiv 0\pmod p$ and the solution set of $q(x)\equiv 0\pmod p$. Hence $s+(p-n)\geq p$, so $s\geq n$.
        
        Therefore, $s=n$.

For non-monic polynomials, since $\mathbf{Z}_p$ is a field, we can convert them to monic polynomials, thus this theorem applies.

<a id="theorem-6"></a>

???+ note "Theorem 6"
    Let $n\mid p-1$, $p\nmid a$, then equation
    
    $$
    x^n\equiv a\pmod p\tag{9}
    $$
    
    has solutions if and only if
    
    $$
    a^{\frac{p-1}{n}}\equiv 1\pmod p.
    $$
    
    Moreover, if $(9)$ has solutions, the number of solutions is $n$.

???+ note "Note"
    For the specific structure of the solution set of equation $(9)$, please refer to [k-th Power Residue](./residue.md).

???+ note "Proof"
    -   Necessity: If equation $(9)$ has a solution $x_0$, then
        
        $$
        a^{\frac{p-1}{n}}\equiv {\left(x_0^n\right)}^{\frac{p-1}{n}}\equiv 1\pmod p
        $$
    -   Sufficiency: If $a^{\frac{p-1}{n}}\equiv 1\pmod p$, then
        
        $$
        \begin{aligned}
            x^p-x&=x\left(x^{p-1}-1\right)\\
            &=x\left(\left(x^n\right)^{\frac{p-1}{n}}-a^{\frac{p-1}{n}}+a^{\frac{p-1}{n}}-1\right)\\
            &=\left(x^n-a\right)P(x)+x\left(a^{\frac{p-1}{n}}-1\right)\\
        \end{aligned}
        $$
        
        where $P(x)$ is some polynomial with integer coefficients. Therefore, by [Theorem 5](#theorem-5), equation $(9)$ has $n$ solutions.

## Solving Methods for Higher-Degree Congruence Equations (Systems)

First, we can use the [Chinese Remainder Theorem](./crt.md) to transform solving **congruence equation systems** into solving **congruence equations**, and transform solving congruence equations with composite modulus $m$ into solving congruence equations with prime power modulus. Then we use [Theorem 1](#theorem-1) to transform solving congruence equations with prime power modulus into solving congruence equations with prime modulus.

Combining several theorems for prime modulus congruence equations, we only need to consider solving equations of the form

$$
x^n+\sum_{i=0}^{n-1}a_ix^i\equiv 0\pmod p
$$

where $p$ is a prime and $n<p$.

We can eliminate the $x^{n-1}$ term by substituting $x$ with $x-\dfrac{a_{n-1}}{n}$, so we only need to consider solving

$$
x^n+\sum_{i=0}^{n-2}a_ix^i\equiv 0\pmod p\tag{10}
$$

where $p$ is a prime and $n<p$.

-   If $n=1$, see [Linear Congruence Equation](./linear-equation.md).
-   If $n=2$, see [Quadratic Residue](./quad-residue.md).
-   If equation $(10)$ can be transformed into

    $$
    x^n\equiv a\pmod p,
    $$

    see [k-th Power Residue](./residue.md).

## References

1.  [Congruence Equation -- from Wolfram MathWorld](https://mathworld.wolfram.com/CongruenceEquation.html)
2.  [Lagrange's theorem (number theory) - Wikipedia](https://en.wikipedia.org/wiki/Lagrange%27s_theorem_%28number_theory%29)
3.  Pan Chengdong, Pan Chengbiao. Elementary Number Theory.
4.  Feng Keqin. Elementary Number Theory and Its Applications.
5.  Min Sihu, Yan Shijian. Elementary Number Theory.