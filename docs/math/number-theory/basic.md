This article provides an introduction to the fundamentals of number theory.

## Divisibility

???+ note "Definition"
    Let $a,b\in\mathbf{Z}$, $a\ne 0$. If $\exists q\in\mathbf{Z}$ such that $b=aq$, then we say $b$ is **divisible** by $a$, denoted $a\mid b$; otherwise, $b$ is not divisible by $a$, denoted $a\nmid b$.

Properties of divisibility:

-   $a\mid b\iff-a\mid b\iff a\mid-b\iff|a|\mid|b|$
-   $a\mid b\land b\mid c\implies a\mid c$
-   $a\mid b\land a\mid c\iff\forall x,y\in\mathbf{Z}, a\mid(xb+yc)$
-   $a\mid b\land b\mid a\implies b=\pm a$
-   Let $m\ne0$, then $a\mid b\iff ma\mid mb$.
-   Let $b\ne0$, then $a\mid b\implies|a|\le|b|$.
-   Let $a\ne0,b=qa+c$, then $a\mid b\iff a\mid c$.

### Multiples and Divisors

???+ note "Definition"
    If $a\mid b$, then $b$ is a **multiple** of $a$, and $a$ is a **divisor** of $b$.

$0$ is a multiple of all non-zero integers. For an integer $b\ne0$, $b$ has only finitely many divisors.

Trivial divisors (trivial factors): For an integer $b\ne0$, $\pm1$ and $\pm b$ are the trivial divisors of $b$. When $b=\pm1$, $b$ has only two trivial divisors.

Other divisors of an integer $b\ne0$ are called proper divisors (proper factors, non-trivial divisors, non-trivial factors).

Properties of divisors:

-   Let $b\ne0$ be an integer. When $d$ ranges over all divisors of $b$, $\dfrac{b}{d}$ also ranges over all divisors of $b$.
-   Let $b>0$ be an integer. When $d$ ranges over all positive divisors of $b$, $\dfrac{b}{d}$ also ranges over all positive divisors of $b$.

In specific problems, **unless otherwise specified, divisors always refer to positive divisors.**

## Division with Remainder

???+ note "Remainder"
    Let $a,b$ be two given integers with $a\ne0$, and let $d$ be a given integer. Then there exists a unique pair of integers $q$ and $r$ such that $b=qa+r,d\le r<|a|+d$.

Regardless of the value of the integer $d$, $r$ is collectively called the remainder. $a\mid b$ is equivalent to $a\mid r$.

In general, $d$ takes the value $0$, and the equation $b=qa+r,0\le r<|a|$ is called division with remainder (Euclidean division). Here, the remainder $r$ is called the least non-negative remainder.

There are two other common ways to define the remainder:

-   Least absolute remainder: $d$ takes the opposite of half of the absolute value of $a$. That is, $b=qa+r,-\dfrac{|a|}{2}\le r<|a|-\dfrac{|a|}{2}$.
-   Least positive remainder: $d$ takes $1$. That is, $b=qa+r,1\le r<|a|+1$.

In division with remainder, the remainder is only the least non-negative remainder. **Unless otherwise specified, the remainder always refers to the least non-negative remainder.**

Properties of remainders:

-   When any integer is divided by a positive integer $a$, the remainder is exactly one of the $a$ numbers from $0$ to $(a-1)$.
-   After dividing $a$ consecutive integers by the positive integer $a$, they cover exactly these $a$ remainders. In particular, there is exactly one number divisible by $a$.

## Greatest Common Divisor and Least Common Multiple

For the definitions of common divisor, common multiple, greatest common divisor, and least common multiple, see [Greatest Common Divisor](./gcd.md).

???+ warning "Warning"
    Some authors consider the greatest common divisor of $0$ and $0$ undefined, while others generally consider it to be $0$. The C++ STL implementation follows the latter, i.e., $\gcd(0,0)=0$[^gcdcpp].

Properties of the greatest common divisor:

-   $(a_1,\dots,a_n)=(|a_1|,\dots,|a_n|)$;
-   $(a,b)=(b,a)$;
-   If $a\ne 0$, then $(a,0)=(a,a)=|a|$;
-   $(bq+r,b)=(r,b)$;
-   $(a_1,\dots,a_n)=((a_1,a_2),a_3,\dots,a_n)$. Furthermore, $\forall 1<k<n-1,~(a_1,\dots,a_n)=((a_1,\dots,a_k),(a_{k+1},\dots,a_n))$;
-   For integers $a_1,\dots,a_n$ not all zero and non-zero integer $m$, $(ma_1,\dots,ma_n)=|m|(a_1,\dots,a_n)$;
-   For integers $a_1,\dots,a_n$ not all zero, if $(a_1,\dots,a_n)=d$, then $(a_1/d,\dots,a_n/d)=1$;
-   $(a^n,b^n)=(a,b)^n$.

Properties of the greatest common divisor related to coprimality:

-   If $b|ac$ and $(a,b)=1$, then $b|c$;
-   If $b|c$, $a|c$ and $(a,b)=1$, then $ab|c$;
-   If $(a,b)=1$, then $(a,bc)=(a,c)$;
-   If $(a_i,b_j)=1,~\forall 1\leq i\leq n,1\leq j\leq m$, then $\left(\prod_i a_i,\prod_j b_j\right)=1$. In particular, if $(a,b)=1$, then $(a^n,b^m)=1$;
-   For integers $a_1,\dots,a_n$, if $\exists v\in \mathbf{Z},~\prod_i a_i=v^m$, and $(a_i,a_j)=1,~\forall i\ne j$, then $\forall 1\leq i\leq n,~\sqrt[m]{a_i}\in\mathbf{Z}$.

Properties of the least common multiple:

-   $[a_1,\dots,a_n]=[|a_1|,\dots,|a_n|]$;
-   $[a,b]=[b,a]$;
-   If $a\ne 0$, then $[a,1]=[a,a]=|a|$;
-   If $a\mid b$, then $[a,b]=|b|$;
-   $[a_1,\dots,a_n]=[[a_1,a_2],a_3,\dots,a_n]$. Furthermore, $\forall 1<k<n-1,~[a_1,\dots,a_n]=[[a_1,\dots,a_k],[a_{k+1},\dots,a_n]]$;
-   If $a_i\mid m,~\forall 1\leq i\leq n$, then $[a_1,\dots,a_n]\mid m$;
-   $[ma_1,\dots,ma_n]=|m|[a_1,\dots,a_n]$;
-   $[a,b,c][ab,bc,ca]=[a,b][b,c][c,a]$;
-   $[a^n,b^n]=[a,b]^n$.

The greatest common divisor and least common multiple can be combined into many wonderful equations:

-   $(a,b)[a,b]=|ab|$;
-   $(ab,bc,ca)[a,b,c]=|abc|$;
-   $\dfrac{(a,b,c)^2}{(a,b)(b,c)(a,c)}=\dfrac{[a,b,c]^2}{[a,b][b,c][a,cabled}$.

All these properties can be proven from the definitions or the [Unique Factorization Theorem](#fundamental-theorem-of-arithmetic), and the proof using the unique factorization theorem is easier to understand.

### Coprimality

???+ note "Definition"
    If $(a_1,a_2)=1$, then $a_1$ and $a_2$ are said to be **coprime** (**relatively prime**).
    
    If $(a_1,\ldots,a_k)=1$, then $a_1,\ldots,a_k$ are said to be **coprime** (**relatively prime**).

Several integers being coprime does not imply they are pairwise coprime. For example, $6$, $10$, and $15$ are coprime, but any two of them are not coprime.

Properties of coprimality and the theory of greatest common divisors: Bézout's identity. See [Bézout's Theorem](./bezouts.md).

### Euclidean Algorithm

The Euclidean algorithm is an algorithm, also called Euclid's algorithm. See [Greatest Common Divisor](./gcd.md).

## Prime Numbers and Composite Numbers

For algorithms related to prime numbers, see [Prime Numbers](./prime.md).

???+ note "Definition"
    Let $p\ne0,\pm1$ be an integer. If $p$ has no divisors other than the trivial ones, then $p$ is called a **prime number** (irreducible number).
    
    If $a\ne0,\pm 1$ is an integer and $a$ is not a prime number, then $a$ is called a **composite number**.

$p$ and $-p$ are always both primes or both composites. **Unless otherwise specified, prime numbers always refer to positive prime numbers.**

If a factor of an integer is a prime number, that prime number is called a prime factor (prime divisor) of that integer.

Simple properties of prime and composite numbers:

-   An integer $a>1$ is composite if and only if $a$ can be expressed as the product of integers $d$ and $e$ ($1<d,e<a$).
-   If a prime $p$ has a divisor $d>1$, then $d=p$.
-   Any integer $a>1$ can be expressed as a product of prime numbers.
-   For a composite number $a$, there must exist a prime number $p\le\sqrt{a}$ such that $p\mid a$.
-   There are infinitely many prime numbers.
-   All prime numbers greater than $3$ can be expressed in the form $6n\pm 1$[^ref1].

## Fundamental Theorem of Arithmetic

???+ note "Fundamental Lemma of Arithmetic"
    Let $p$ be a prime number, $p\mid a_1a_2$. Then at least one of $p\mid a_1$ and $p\mid a_2$ holds.

The converse of the fundamental lemma of arithmetic can be slightly modified to give an alternative definition of prime numbers.

???+ note "Alternative Definition of Prime Numbers"
    For an integer $p\ne 0,\pm 1$, if for any integers $a_1,a_2$ satisfying $p\mid a_1a_2$, we have $p\mid a_1$ or $p\mid a_2$, then $p$ is called a prime number.

??? tip "Tip"
    The motivation for this definition can be found in [Prime Ideals](../algebra/ring-theory.md#prime-ideals).

???+ note "Fundamental Theorem of Arithmetic (Unique Factorization Theorem)"
    For a positive integer $a$, there must exist a representation:
    
    $$
    a=p_1p_2\cdots p_s
    $$
    
    where $p_j(1\le j\le s)$ are prime numbers. Moreover, this representation is unique up to ordering.

???+ note "Standard Prime Factorization"
    Combining identical prime numbers in the above representation, we get:
    
    $$
    a={p_1}^{\alpha_1}{p_2}^{\alpha_2}\cdots{p_s}^{\alpha_s},p_1<p_2<\cdots<p_s
    $$
    
    This is called the standard prime factorization of the positive integer $a$.

The fundamental theorem of arithmetic and the fundamental lemma of arithmetic are equivalent.

## Congruence

???+ note "Definition"
    Let $m\ne0$ be an integer. If $m\mid(a-b)$, then $m$ is called the **modulus** (modulo), $a$ is congruent to $b$ modulo $m$, and $b$ is the **residue** of $a$ modulo $m$. Denoted $a\equiv b\pmod m$.
    
    Otherwise, $a$ is not congruent to $b$ modulo $m$, and $b$ is not a residue of $a$ modulo $m$. Denoted $a\not\equiv b\pmod m$.
    
    Such equations are called congruences modulo $m$, or simply **congruences**.

From the properties of divisibility, the above congruence is also equivalent to $a\equiv b\pmod{(-m)}$.

In the following, unless otherwise specified, the modulus is always a **positive integer**.

In the equation, $b$ is the residue of $a$ modulo $m$, which is exactly the same concept as the remainder. By restricting the range of $b$, we have the least non-negative residue, the least absolute residue, and the least positive residue of $a$ modulo $m$.

Properties of congruence:

-   Congruence is an [equivalence relation](../order-theory.md#binary-relations), meaning congruence has:
    -   Reflexivity: $a\equiv a\pmod m$.
    -   Symmetry: If $a\equiv b\pmod m$, then $b\equiv a\pmod m$.
    -   Transitivity: If $a\equiv b\pmod m,b\equiv c\pmod m$, then $a\equiv c\pmod m$.
-   Linear operations: If $a,b,c,d\in\mathbf{Z},m\in\mathbf{N}^*,a\equiv b\pmod m,c\equiv d\pmod m$, then:
    -   $a\pm c\equiv b\pm d\pmod m$.
    -   $a\times c\equiv b\times d\pmod m$.
-   Let $f(x)=\sum_{i=0}^n a_ix^i$ and $g(x)=\sum_{i=0}^n b_ix^i$ be two polynomials with integer coefficients, $m\in\mathbf{N}^*$, and $a_i\equiv b_i\pmod m,~0\leq i\leq n$. Then for any integer $x$, we have $f(x)\equiv g(x)\pmod m$. Furthermore, if $s\equiv t\pmod m$, then $f(s)\equiv g(t)\pmod m$.
-   If $a,b\in\mathbf{Z},k,m\in\mathbf{N}^*,a\equiv b\pmod m$, then $ak\equiv bk\pmod{mk}$.
-   If $a,b\in\mathbf{Z},d,m\in\mathbf{N}^*,d\mid a,d\mid b,d\mid m$, then when $a\equiv b\pmod m$ holds, we have $\dfrac{a}{d}\equiv\dfrac{b}{d}\left(\bmod\;{\dfrac{m}{d}}\right)$.
-   If $a,b\in\mathbf{Z},d,m\in\mathbf{N}^*,d\mid m$, then when $a\equiv b\pmod m$ holds, we have $a\equiv b\pmod d$.
-   If $a,b\in\mathbf{Z},d,m\in\mathbf{N}^*$, then when $a\equiv b\pmod m$ holds, we have $(a,m)=(b,m)$. If $d$ can divide $m$ and one of $a,b$, then $d$ must divide the other of $a,b$.

There is also the property of multiplicative inverses. See [Multiplicative Inverse](./inverse.md).

## Congruence Classes and Residue Systems

For convenience in discussion, for a set $A,B$ and an element $r$, we introduce the following notation:

-   $r+A:=\{r+a:a\in A\}$;
-   $rA:=\{ra:a\in A\}$;
-   $A+B:=\{a+b:a\in A,b\in B\}$;
-   $AB:=\{ab:a\in A,b\in B\}$.

???+ note "Congruence Class"
    For a non-zero integer $m$, we divide all integers into $|m|$ pairwise disjoint sets, and any two numbers in the same set are congruent modulo $m$. We call these $|m|$ sets the **congruence classes** or **residue classes** modulo $m$. We use $r\bmod m$ to denote the congruence class modulo $m$ containing the integer $r$.
    
    It is easy to prove that for any non-zero integer $m$, the above partition scheme always exists and is unique.

From the definition of congruence classes, we know:

-   $r\bmod m=\{r+km:k\in\mathbf{Z}\}$;
-   $r\bmod m=s\bmod m\iff r\equiv s\pmod m$;
-   For any $r,s\in\mathbf{Z}$, either $r\bmod m=s\bmod m$, or $(r\bmod m)\cap (s\bmod m)=\varnothing$;
-   If $m_1\mid m$, then for any integer $r$, we have $r+m\mathbf{Z}\subseteq r+m_1\mathbf{Z}$.

Note that congruence is an equivalence relation, so congruence classes are exactly the equivalence classes of the congruence relation.

We denote the set of all congruence classes modulo $m$ as $\mathbf{Z}_m$, i.e.,

$$
\mathbf{Z}_m:=\{r\bmod m:0\leq r<m\}
$$

It is easy to find:

-   For any integer $a$, $a+\mathbf{Z}_m=\mathbf{Z}_m$;
-   For any integer $b$ coprime with $m$, $b\mathbf{Z}_m=\mathbf{Z}_m$.

From the definition of [quotient groups](../algebra/group-theory.md#quotient-groups), we have $\mathbf{Z}_m=\mathbf{Z}/m\mathbf{Z}$, so we sometimes also use $\mathbf{Z}/m\mathbf{Z}$ to denote $\mathbf{Z}_m$.

From the [pigeonhole principle](../combinatorics/drawer-principle.md), we know:

-   Taking any $m+1$ integers, there must be two integers congruent modulo $m$.
-   There exist $m$ pairwise incongruent integers modulo $m$.

From this we give the definition of the (complete) residue system:

???+ note "(Complete) Residue System"
    For $m$ integers $a_1,a_2,\dots,a_m$, if for any number $x$, there is exactly one $a_i$ such that $x$ is congruent to $a_i$ modulo $m$, then these $m$ integers $a_1,a_2,\dots,a_m$ are called the **complete residue system** modulo $m$, or simply **residue system**.

We can also define for modulus $m$:

-   Least non-negative (complete) residue system: $0,\dots,m-1$;
-   Least positive (complete) residue system: $1,\dots,m$;
-   Least absolute (complete) residue system: $-\lfloor m/2\rfloor,\dots,-\lfloor -m/2\rfloor-1$;
-   Greatest non-positive (complete) residue system: $-m+1,\dots,0$;
-   Greatest negative (complete) residue system: $-m,\dots,-1$.

Unless otherwise specified, we generally only use the least non-negative residue system.

We note that the following proposition holds:

-   In any congruence class modulo $m$, taking any two integers $a_1,a_2$, we have $(a_1,m)=(a_2,m)$.

Considering the congruence class $r\bmod m$, if $(r,m)=1$, then all elements of this congruence class are coprime with $m$, which indicates that we might be able to know the structure of the set of all integers coprime with $m$ through a similar method.

???+ note "Reduced Congruence Class"
    For the congruence class $r\bmod m$, if $(r,m)=1$, then this congruence class is called a **reduced congruence class** or **reduced residue class**.
    
    We denote the number of reduced residue classes modulo $m$ as $\varphi(m)$, called the [Euler's Totient Function](./euler-totient.md).

We denote the set of all reduced congruence classes modulo $m$ as $\mathbf{Z}_m^*$, i.e.,

$$
\mathbf{Z}_m^*:=\{r\bmod m:0\leq r<m,(r,m)=1\}
$$

???+ warning "Warning"
    For any integer $a$ and integer $b$ coprime with $m$, $b\mathbf{Z}_m^*=\mathbf{Z}_m^*$, but $a+\mathbf{Z}_m^*$ is not necessarily $\mathbf{Z}_m^*$. This is different from $\mathbf{Z}_m$.

From the [pigeonhole principle](../combinatorics/drawer-principle.md), we know:

-   Taking any $\varphi(m)+1$ integers coprime with $m$, there must be two integers congruent modulo $m$.
-   There exist $\varphi(m)$ pairwise incongruent integers coprime with $m$.

From this we give the definition of the reduced residue system:

???+ note "Reduced Residue System"
    For $t=\varphi(m)$ integers $a_1,a_2,\dots,a_t$, if $(a_i,m)=1,~\forall 1\leq i\leq t$, and for any number $x$ with $(x,m)=1$, there is exactly one $a_i$ such that $x$ is congruent to $a_i$ modulo $m$, then these $t$ integers $a_1,a_2,\dots,a_t$ are called the **reduced residue system**, **coterminous residue system**, or **simplified residue system** modulo $m$.

Similarly, we can also define concepts such as the least non-negative reduced residue system.

Unless otherwise specified, we generally only use the least non-negative reduced residue system.

### Composition of Residue Systems

For a positive integer $m$, we have the following theorem:

-   If $m=m_1m_2,~1\leq m_1,m_2$, let $Z_{m_1},Z_{m_2}$ be the **complete** residue systems modulo $m_1,m_2$ respectively. Then for any $a$ coprime with $m_1$:

    $$
    Z_m=aZ_{m_1}+m_1Z_{m_2}.
    $$

    Is the **complete** residue system modulo $m$. Furthermore, if $m=\prod_{i=1}^k m_i,~1\leq m_1,m_2,\dots,m_k$, let $Z_{m_1},\dots,Z_{m_k}$ be the **complete** residue systems modulo $m_1,\dots,m_k$ respectively. Then:

    $$
    Z_m=\sum_{i=1}^k\left(\prod_{j=1}^{i-1}m_j\right)Z_{m_i}.
    $$

    Is the **complete** residue system modulo $m$.

???+ note "Proof"
    We only need to prove that for any $x,x'\in Z_{m_1},y,y'\in Z_{m_2}$ satisfying $ax+m_1y\equiv ax'+m_1y'pmod{m_1m_2}$, we have:
    
    $$
    ax+m_1y=ax'+m_1y'.
    $$
    
    Actually, from $m_1\mid m_1m_2$, we have $ax+m_1y\equiv ax'+m_1y'\pmod{m_1}$, then $ax\equiv ax'\pmod{m_1}$, and from $(a,m_1)=1$, we know $x\equiv x'\pmod{m_1}$, then $x=x'$.
    
    Furthermore, $m_1y\equiv m_1y'\pmod{m_1m_2}$, then $y\equiv y'\pmod{m_2}$, i.e., $y=y'$.
    
    Therefore,
    
    $$
    ax+m_1y=ax'+m_1y'.
    $$

-   If $m=m_1m_2,~1\leq m_1,m_2,(m_1,m_2)=1$, let $Z_{m_1}^*,Z_{m_2}^*$ be the **reduced** residue systems modulo $m_1,m_2$ respectively. Then:

    $$
    Z_m^*=m_2Z_{m_1}^*+m_1Z_{m_2}^*.
    $$

    Is the **reduced** residue system modulo $m$.

???+ tip "Tip"
    This theorem is equivalent to proving that Euler's function is a [multiplicative function](#multiplicative-function).

???+ note "Proof"
    Let $Z_{m_1},Z_{m_2}$ be the complete residue systems modulo $m_1,m_2$ respectively. We have already proven that
    
    $$
    Z_m=m_2Z_{m_1}+m_1Z_{m_2}
    $$
    
    is the complete residue system modulo $m$. Let $M=\{a\in Z_m:(a,m)=1\}\subseteq Z_m$. Obviously, $M$ is the reduced residue system modulo $m$, so we only need to prove $M=Z_m^*$.
    
    Obviously $Z_m^*\subseteq Z_m$.
    
    Taking any $m_2x+m_1y\in M$, where $x\in Z_{m_1}$ and $y\in Z_{m_2}$, we have $(m_2x+m_1y,m_1m_2)=1$. From $(m_1,m_2)=1$, we get
    
    $$
    1=(m_2x+m_1y,m_1)=(m_2x,m_1)=(x,m_1),
    $$
    
    $$
    1=(m_2x+m_1y,m_2)=(m_1y,m_2)=(y,m_2).
    $$
    
    Therefore, we have $x\in Z_{m_1}^*$ and $y\in Z_{m_2}^*$, i.e., $M\subseteq Z_m^*$.
    
    Taking any $m_2x+m_1y\in Z_m^*$, where $x\in Z_{m_1}^*$ and $y\in Z_{m_2}^*$, we have $(x,m_1)=1$ and $(y,m_2)=1$. From $(m_1,m_2)=1$, we get
    
    $$
    (m_2x+m_1y,m_1)=(m_2x,m_1)=(x,m_1)=1,
    $$
    
    $$
    (m_2x+m_1y,m_2)=(m_1y,m_2)=(x,m_2)=1,
    $$
    
    Therefore, we have $(m_2x+m_1y,m_1m_2)=1$, i.e., $Z_m^*\subseteq M$.
    
    In summary,
    
    $$
    Z_m^*=m_2Z_{m_1}^*+m_1Z_{m_2}^*.
    $$
    
    Is the **reduced** residue system modulo $m$.

## Arithmetic Functions

Arithmetic functions (also called number-theoretic functions) are functions whose domain is the set of positive integers. Arithmetic functions can also be regarded as a sequence.

### Multiplicative Functions

???+ note "Definition"
    In number theory, if a function $f(n)$ satisfies $f(1)=1$, and $f(xy)=f(x)f(y)$ for any coprime $x, y \in\mathbf{N}^*$, then $f(n)$ is called a **multiplicative function**.
    
    In number theory, if a function $f(n)$ satisfies $f(1)=1$ and $f(xy)=f(x)f(y)$ for any $x, y \in\mathbf{N}^*$, then $f(n)$ is called a **completely multiplicative function**.

#### Properties

If $f(x)$ and $g(x)$ are both multiplicative functions, then the following functions are also multiplicative:

$$
\begin{aligned}
h(x)&=f(x^p)\\
h(x)&=f^p(x)\\
h(x)&=f(x)g(x)\\
h(x)&=\sum_{d\mid x}f(d)g\left(\dfrac{x}{d}\right)
\end{aligned}
$$

For a positive integer $x$, let its unique prime factorization be $x=\prod p_i^{k_i}$, where $p_i$ are prime numbers.

If $F(x)$ is a multiplicative function, then $F(x)=\prod F(p_i^{k_i})$.

If $F(x)$ is a completely multiplicative function, then $F(x)=\prod F(p_i^{k_i})=\prod F(p_i)^{k_i}$.

#### Examples

-   Identity function: $\varepsilon(n)=[n=1]$. (Completely multiplicative)
-   Power function: $\operatorname{id}_k(n)=n^k$, $\operatorname{id}_{1}(n)$ is usually abbreviated as $\operatorname{id}(n)$. (Completely multiplicative)
-   Constant function: $1(n)=1$. (Completely multiplicative)
-   Divisor function: $\sigma_{k}(n)=\sum_{d\mid n}d^{k}$. $\sigma_{0}(n)$ is usually abbreviated as $d(n)$ or $\tau(n)$, and $\sigma_{1}(n)$ is usually abbreviated as $\sigma(n)$.
-   Euler's totient function: $\varphi(n)=\sum_{i=1}^n[(i,n)=1]$.
-   Möbius function: $\mu(n)=\begin{cases}1&n=1\\0&\exists d>1,d^{2}\mid n\\(-1)^{\omega(n)}&\text{otherwise}\end{cases}$, where $\omega(n)$ denotes the number of distinct prime factors of $n$.

### Additive Functions

???+ note "Definition"
    In number theory, if a function $f(n)$ satisfies $f(1)=0$ and $f(xy)=f(x)+f(y)$ for any coprime $x, y \in\mathbf{N}^*$, then $f(n)$ is called an **additive function**.
    
    In number theory, if a function $f(n)$ satisfies $f(1)=0$ and $f(xy)=f(x)+f(y)$ for any $x, y \in\mathbf{N}^*$, then $f(n)$ is called a **completely additive function**.

??? warning "Additive Functions"
    The additive functions in this section refer to number-theoretic additive functions, which should be distinguished from additive maps in algebra.

#### Properties

For a positive integer $x$, let its unique prime factorization be $x=\prod p_i^{k_i}$, where $p_i$ are prime numbers.

If $F(x)$ is an additive function, then $F(x)=\sum F(p_i^{k_i})$.

If $F(x)$ is a completely additive function, then $F(x)=\sum F(p_i^{k_i})=\sum F(p_i)\cdot k_i$.

#### Examples

For convenience, let the set of all prime numbers be $\mathbf P$.

-   Multiplicity of $p$ in the prime factorization: $\nu_p(n) = \max\{k\in\mathbf N: p^k\mid n\}$, where $p\in\mathbf P$. (Completely additive)
-   Number of all prime factors: $\Omega(n)=\sum_{p \in\mathbf P} \nu_p(n)$. (Completely additive)
-   Number of distinct prime factors: $\omega(n)=\sum_{p \in\mathbf P} [p \mid n]$.
-   Sum of all prime factors: $a_0(n)=\sum_{p \in\mathbf P} \nu_p(n)\cdot p$. (Completely additive)
-   Sum of distinct prime factors: $a_1(n)=\sum_{p \in\mathbf P} [p \mid n] \cdot p$.

## Floor and Ceiling Functions

For a real number $x$, we define the **floor function** and **ceiling function** respectively as

$$
\lfloor x\rfloor = \max\{k\in\mathbf Z:k\le x\},~\lceil x\rceil = \min\{k\in\mathbf Z:k\ge x\}.
$$

Using the floor function, a real number can be decomposed into its integer part and fractional part: $x = \lfloor x\rfloor + \{x\}$, where $\{x\}$ denotes the fractional part of $x$.

The floor and ceiling functions have the following basic properties: ($x\in\mathbf R,~n\in\mathbf Z$)

-   $x\in\mathbf Z \iff x = \lfloor x\rfloor = \lceil x\rceil$.
-   $\lceil x\rceil - \lfloor x\rfloor = [x\notin\mathbf Z]$.
-   $x - 1 < \lfloor x\rfloor \le x \le \lceil x\rceil < x + 1$.
-   $\lfloor -x\rfloor = -\lceil x\rceil,~\lceil -x\rceil = -\lfloor x\rfloor$.
-   $\lfloor x + n\rfloor = \lfloor x\rfloor + n,~\lceil x + n\rceil = \lceil x \rceil + n$.
-   Both $\lfloor x\rfloor$ and $\lceil x\rceil$ are monotonically weakly increasing functions of $x$.

Proving equalities involving floor (ceiling) functions often uses the following equivalent forms: ($x\in\mathbf R,~n\in\mathbf Z$)

-   $\lfloor x\rfloor = n \iff n \le x < n + 1 \iff x - 1 < n \le x$.
-   $\lceil x\rceil = n \iff n - 1 < x \le n \iff x \le n < x + 1$.

Proving inequalities involving floor (ceiling) functions often uses the following equivalent forms: ($x\in\mathbf R,~n\in\mathbf Z$)

-   $x < n \iff \lfloor x\rfloor < n$.
-   $n < x \iff n < \lceil x\rceil$.
-   $x \le n \iff \lceil x\rceil \le n$.
-   $n \le x \iff n \le \lfloor x\rfloor$.

Properties involving sums and differences are: ($x,y\in\mathbf R$)

-   $\lfloor x\rfloor + \lfloor y\rfloor \le \lfloor x + y\rfloor \le \lfloor x\rfloor + \lfloor y\rfloor + 1$, and exactly one equality holds.
-   $\lceil x\rceil +\lceil y\rceil -1\leq \lceil x+y\rceil \leq \lceil x\rceil +\lceil y\rceil$, and exactly one equality holds.
-   $\lfloor|x - y|\rfloor \le |\lfloor x\rfloor - \lfloor y\rfloor| \le \lceil|x - y|\rceil$.
-   $\lfloor|x - y|\rfloor \le |\lceil x\rceil - \lceil y\rceil| \le \lceil|x-y|\rceil$.

Properties involving division are: ($x\in\mathbf R,~n\in\mathbf Z,~m\in\mathbf Z_+$)

-   $\left\lceil\dfrac{n}{m}\right\rceil = \left\lfloor\dfrac{n+m-1}{m}\right\rfloor,~\left\lfloor\dfrac{n}{m}\right\rfloor = \left\lceil\dfrac{n-m+1}{m}\right\rceil$.
-   $\left\lfloor\dfrac{x + n}{m} \right\rfloor = \left\lfloor\dfrac{\lfloor x\rfloor + n}{m} \right\rfloor,~\left\lceil\dfrac{x + n}{m} \right\rceil = \left\lceil\dfrac{\lceil x\rceil + n}{m} \right\rceil$.
-   $\left\lfloor\dfrac{\lfloor x/n\rfloor}{m}\right\rfloor = \left\lfloor\dfrac{x}{nm}\right\rfloor,~\left\lceil\dfrac{\lceil x/n\rceil}{m}\right\rceil = \left\lceil\dfrac{x}{nm}\right\rceil$.
-   For $x > 0$, we have $\displaystyle\left\lfloor\dfrac{x}{m}\right\rfloor = sum_{k=1}^{\lfloor x\rfloor}[m\mid k]$.

Here, the second and third properties can be seen as direct corollaries of the following conclusion:

-   Let $f$ be a continuously increasing function, and whenever $f(x)\in\mathbf{Z}$, we have $x\in\mathbf{Z}$. Then

    $$
    \lfloor f(x)\rfloor = \lfloor f(\lfloor x\rfloor)\rfloor,~ \lceil f(x)rceil = \lceil f(\lceil x\rceil)rceil.
    $$

    ??? note "Proof"
        By symmetry, we only need to prove the first equality. If $x$ is an integer, the proposition is obvious. Otherwise, $\lfloor x\rfloor < x$. From the monotonicity of $f$ and the floor function, $\lfloor f(x)\rfloor \ge \lfloor f(\lfloor x\rfloor)\rfloor$. If the equality does not hold, let $y = \lfloor f(x)\rfloor$, which satisfies $\lfloor f(\lfloor x\rfloor)\rfloor < y \le \lfloor f(x)\rfloor$, which is equivalent to $f(\lfloor x\rfloor) < y \le f(x)$. From the continuity of $f$, there exists $\lfloor x\rfloor < x_0 \le x$ such that $f(x_0)=y$. Since $y\in\mathbf{Z}$, we have $x_0\in\mathbf{Z}$, which contradicts the definition of $\lfloor x\rfloor$. Therefore, the equality holds, i.e., $\lfloor f(x)\rfloor = \lfloor f(\lfloor x\rfloor)\rfloor$.

Finally, a set of conclusions for summations involving floor and ceiling functions: ($x\in\mathbf R,~n\in\mathbf Z,~m\in\mathbf Z_+$)

-   $n = \left\lfloor\dfrac{n}{2}\right\rfloor + \left\lceil\dfrac{n}{2}\right\rceil$.
-   $n = \left\lfloor\dfrac{n}{m} \right\rfloor + \left\lfloor\dfrac{n+1}{m} \right\rfloor + \cdots + \left\lfloor\dfrac{n+m-1}{m} \right\rfloor$.
-   $n = \left\lceil\dfrac{n}{m} \right\rceil + \left\lceil\dfrac{n-1}{m} \right\rceil + \cdots + \left\lceil\dfrac{n-m+1}{m} \right\rceil$.
-   $\lfloor mx\rfloor = \lfloor x\rfloor + \left\lfloor x+\dfrac{1}{m}\right\rfloor + \cdots + \left\lfloor x+\dfrac{m-1}{m}\right\rfloor$.
-   $\lceil mx\rceil = \lceil x\rceil + \left\lceil x - \dfrac{1}{m}\right\rceil + \cdots + \left\lceil x - \dfrac{m-1}{m}\right\rceil$.
-   When $m\perp n$, $\displaystyle\sum_{k=1}^{m-1}\left\lfloor\dfrac{kn}{m}\right\rfloor=\dfrac{1}{2}(n-1)(m-1)$.
-   When $m\perp n$, $\displaystyle\sum_{k=1}^{m-1}\left\lceil\dfrac{kn}{m}\right\rceil=\dfrac{1}{2}(n+1)(m-1)$.

The derivation of these and more general similar summations can be referred to the [Euclidean Algorithm](./euclidean.md) page.

More properties and applications of floor and ceiling functions can be found at:

-   Modular arithmetic: $n\bmod m = n - \left\lfloor\dfrac{n}{m}\right\rfloor m$. It can be used to [optimize integer modular operations](./mod-arithmetic.md#related-algorithms).
-   Using Gauss's lemma to prove the [Quadratic Reciprocity Law](./quad-residue.md#quadratic-reciprocity-law).
-   [Number Theoretic Division](./sqrt-decomposition.md), especially its properties proof section.
-   [Legendre's Formula](./factorial.md#legendre-formula) for computing prime powers in factorials.
-   [Beatty Sequences](../game-theory/impartial-game.md#wythoff-game), the Rayleigh theorem, and Wythoff's game.

## References and Notes

-   Pan Chengdong, Pan Chengbiao. Elementary Number Theory. Beijing University Press.
-   [Floor and ceiling functions - Wikipedia](https://en.wikipedia.org/wiki/Floor_and_ceiling_functions)
-   Graham, Ronald L., Donald E. Knuth, and Oren Patashnik. "Concrete mathematics: a foundation for computer science." (1989).

[^ref1]: [Are all primes (past 2 and 3) of the forms 6n+1 and 6n-1?](https://primes.utm.edu/notes/faq/six.html)

[^gcdcpp]: [std::gcd - cppreference.com](https://en.cppreference.com/w/cpp/numeric/gcd)