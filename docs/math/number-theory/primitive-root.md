Prerequisites: [Fermat's Little Theorem](./fermat.md#fermats-little-theorem), [Euler's Theorem](./fermat.md#euler-theorem), [Lagrange's Theorem](./congruence-equation.md#theorem-3lagrange-theorem)

Order and primitive roots are important tools for understanding the multiplicative structure of the reduced residue system modulo $m$ $\mathbf Z_m^*$. Based on this, concepts such as [discrete logarithm](./discrete-logarithm.md) can be defined. More general discussions can be found in the abstract algebra sections on [group theory](../algebra/group-theory.md#order) and [ring theory](../algebra/ring-theory.md#application-the-multiplicative-group-of-integer-congruence-classes).

## Order

In this section, we always assume the modulus $m\in\mathbf N_+$ and base $a\in\mathbf Z$ are coprime, i.e., $(a,m)=1$, also written as $a\perp m$.

For $n\in\mathbf Z$, the powers $a^n\bmod m$ exhibit a cyclic structure. The minimal length of this cycle is the order of $a$ modulo $m$. The order is defined as the exponent when the power $a^n\bmod m$ first returns to the starting point $a^0\bmod m = 1$:

???+ abstract "Order"
    For $a\in\mathbf Z,m\in\mathbf N_+$ with $a\perp m$, the smallest positive integer $n$ satisfying the congruence $a^n \equiv 1 \pmod m$ is called **the order of $a$ modulo $m$**, denoted $\delta_m(a)$ or $\operatorname{ord}_m(a)$.

???+ tip "Note"
    In [abstract algebra](../algebra/group-theory.md#order), the "order" here is the order of the element $a$ in the group formed by the reduced residue system modulo $m$ under multiplication. Using the symbol $\delta$ to denote order only applies to this particular group. The following properties can be directly generalized to the properties of orders of elements in abstract groups.
    
    There is also the concept of "half-order", denoted by $\delta^-$ in number theory. It is the smallest positive integer satisfying $a^n \equiv -1 \pmod m$. Half-order is not a concept in group theory. Order always exists, but half-order may not.

### Cyclic Structure of Powers

Using order, we can characterize the cyclic structure of powers. For the power $a^n\bmod m$, we can perform Euclidean division of the exponent $n$ by the order $\delta_m(a)$:

$$
n = \delta_m(a)q + r, ~ 0\le r < \delta_m(a).
$$

Then, using the laws of exponents,

$$
a^n = a^{\delta_m(a)q + r} = (a^{\delta_m(a)})^q \cdot a^r \equiv a^r \pmod m.
$$

This shows that for any exponent, we can translate it to the first non-negative cycle. From this, we can derive a series of properties about order.

<a id="ord-prop-1"></a>

???+ note "Property 1"
    For $a\in\mathbf Z,m\in\mathbf N_+$ with $a\perp m$, the powers $a^0(=1),a,a^2,\cdots,a^{\delta_m(a)-1}$ are pairwise incongruent modulo $m$.

??? note "Proof"
    Proof by contradiction. Suppose there exist two numbers $0\le i< j<\delta_m(a)$ such that $a^i\equiv a^j\pmod m$. Then $a^{j - i}\equiv 1\pmod m$. But $0 < j - i < \delta_m(a)$. This contradicts the minimality of order. Hence the original proposition holds.

<a id="ord-prop-2"></a>

???+ note "Property 2"
    For $a,n\in\mathbf Z,m\in\mathbf N_+$ with $a\perp m$, the congruence $a^n \equiv 1 \pmod m$ holds if and only if $\delta_m(a)\mid n$.

??? note "Proof"
    As mentioned earlier, $a^{n}\equiv a^{n\bmod\delta_m(a)}\pmod m$. By [Property 1](#ord-prop-1), among $0\le r < \delta_m(a)$, the only $r$ that makes $a^r\equiv 1\pmod m$ is $r=0$. Therefore, $a^n \equiv 1 \pmod m$ if and only if $n\bmod \delta_m(a) = 0$, i.e., $\delta_m(a)\mid n$.

In [Euler's Theorem](./fermat.md#euler-theorem), the congruence $a^{\varphi(m)}\equiv 1\pmod m$ holds for all $a\perp m$. Combined with [Property 2](#ord-prop-2), this shows that for all $a\perp m$, we have $\delta_m(a)\mid\varphi(m)$. In other words, $\varphi(m)$ is a common multiple of the orders of all $a\perp m$. For a positive integer $m$, the least common multiple of all orders $\delta_m(a)$ for $a\perp m$, denoted $\lambda(m)$, is the [Carmichael function](#carmichael-function) of $m$. Its properties will be discussed in detail later.

Similar to other cyclic structures, we can compute the order of $a^k$ given the order of $a$.

<a id="ord-prop-3"></a>

???+ note "Property 3"
    For $k,a\in\mathbf Z,m\in\mathbf N_+$ with $a\perp m$, we have
    
    $$
    \delta_m(a^k) = \dfrac{\delta_m(a)}{(\delta_m(a),k)}.
    $$

??? note "Proof"
    By [Property 2](#ord-prop-2), the congruence $(a^k)^n = a^{kn} \equiv 1\pmod m$ holds if and only if $\delta_m(a) \mid kn$. This condition is equivalent to
    
    $$
    \dfrac{\delta_m(a)}{\left(\delta_m(a),k\right)} \mid n.
    $$
    
    The smallest positive integer satisfying this condition is
    
    $$
    \delta_m(a^k)=\dfrac{\delta_m(a)}{\left(\delta_m(a),k\right)}.
    $$

### Order of Products

Let $a,b$ be distinct integers coprime to $m$. If we know the orders $\delta_m(a)$ and $\delta_m(b)$, we can also obtain some information about the order of their product $ab$.

<a id="ord-prop-4"></a>

???+ note "Property 4"
    For $a,b\in\mathbf Z,m\in\mathbf N_+$ with $a,b\perp m$, we have
    
    $$
    \dfrac{[\delta_m(a),\delta_m(b)]}{(\delta_m(a),\delta_m(b))} \mid \delta_m(ab) \mid [\delta_m(a),\delta_m(b)].
    $$

??? note "Proof"
    Since $[\delta_m(a),\delta_m(b)]$ is a multiple of both $\delta_m(a)$ and $\delta_m(b)$, by [Property 2](#ord-prop-2),
    
    $$
    (ab)^{[\delta_m(a),\delta_m(b)]} = a^{[\delta_m(a),\delta_m(b)]} b^{[\delta_m(a),\delta_m(b)]} \equiv 1 \pmod m.
    $$
    
    Applying Property 2 again gives
    
    $$
    \delta_m(ab) \mid [\delta_m(a),\delta_m(b)].
    $$
    
    This gives the right-hand side divisibility.
    
    Conversely, since
    
    $$
    1 \equiv (ab)^{\delta_m(ab)\delta_m(b)} \equiv a^{\delta_m(ab)\delta_m(b)} \pmod m,
    $$
    
    applying Property 2 gives $\delta_m(a)\mid\delta_m(ab)\delta_m(b)$. Canceling $(\delta_m(a),\delta_m(b))$ on both sides gives
    
    $$
    \dfrac{\delta_m(a)}{(\delta_m(a),\delta_m(b))}\mid\delta_m(ab)\dfrac{\delta_m(b)}{(\delta_m(a),\delta_m(b))}.
    $$
    
    After canceling common factors, the two fractions are coprime, which gives
    
    $$
    \dfrac{\delta_m(a)}{(\delta_m(a),\delta_m(b))}\mid\delta_m(ab).
    $$
    
    Similarly,
    
    $$
    \dfrac{\delta_m(b)}{(\delta_m(a),\delta_m(b))}\mid\delta_m(ab).
    $$
    
    Since the left sides of the two divisibility relations are coprime, we have
    
    $$
    \dfrac{[\delta_m(a),\delta_m(b)]}{(\delta_m(a),\delta_m(b))} =\dfrac{\delta_m(a)\delta_m(b)}{(\delta_m(a),\delta_m(b))^2}\mid\delta_m(ab).
    $$
    
    This gives the left-hand side divisibility.

For the case where the orders of $a$ and $b$ are coprime, this conclusion has a simpler form.

<a id="ord-prop-4p"></a>

???+ note "Property 4'"
    For $a,b\in\mathbf Z,m\in\mathbf N_+$ with $a,b\perp m$, we have
    
    $$
    \delta_m(ab) = \delta_m(a)\delta_m(b) \iff \delta_m(a)\perp\delta_m(b).
    $$

??? note "Proof"
    If $\delta_m(a)\perp\delta_m(b)$, then all divisibility relations in [Property 4](#ord-prop-4) are equalities, so we have
    
    $$
    \delta_m(ab) = [\delta_m(a),\delta_m(b)] = \delta_m(a)\delta_m(b).
    $$
    
    Conversely, if $\delta_m(ab)=\delta_m(a)\delta_m(b)$, then by Property 4,
    
    $$
    \delta_m(a)\delta_m(b) = \delta_m(ab) \mid [\delta_m(a),\delta_m(b)].
    $$
    
    This immediately shows $(\delta_m(a),\delta_m(b))=1$, i.e., $\delta_m(a)\perp\delta_m(b)$.

In general, the bounds obtained in [Property 4](#ord-prop-4) are tight. It is easy to construct cases where the order of the product achieves the lower bound: for example, when $(a,b,m)=(3,5,7)$, $\delta_m(a)=\delta_m(b)=6$, but their product has order $\delta_m(ab)=1$.

Although in general the order of the product $ab$ is not necessarily their least common multiple, we can always find an element whose order equals this least common multiple.

<a id="ord-prop-5"></a>

???+ note "Property 5"
    For $a,b\in\mathbf Z,m\in\mathbf N_+$ with $a,b\perp m$, there always exists $c\in\mathbf Z$ with $c\perp m$ such that
    
    $$
    \delta_m(c) = [\delta_m(a),\delta_m(b)].
    $$

??? note "Proof"
    Consider prime factorization:
    
    $$
    \delta_m(a) = \prod_p p^{\alpha_p},~ \delta_m(b) = \prod_p p^{\beta_p}.
    $$
    
    Using the relative sizes of $\alpha_p$ and $\beta_p$, we can divide all prime factors into two classes:
    
    $$
    A = \{p : \alpha_p \ge \beta_p\}, ~ B = \{p : \alpha_p < \beta_p\}.
    $$
    
    Thus, set respectively
    
    $$
    \gamma_A = \prod_{p\in A}p^{\alpha_p},~\gamma_B = \prod_{p\in B}p^{\alpha_p},~\eta_A = \prod_{p\in A}p^{\beta_p},~\eta_B = \prod_{p\in B}p^{\beta_p},
    $$
    
    so that $\delta_m(a) = \gamma_A\gamma_B$ and $\delta_m(b)=\eta_A\eta_B$. By [Property 3](#ord-prop-3), we have
    
    $$
    \begin{aligned}
    \delta_m(a^{\gamma_B}) &= \dfrac{\delta_m(a)}{(\delta_m(a),\gamma_B)} = \dfrac{\delta_m(a)}{\gamma_B} = \gamma_A,\\
    \delta_m(b^{\eta_A}) &= \dfrac{\delta_m(b)}{(\delta_m(b),\eta_A)} = \dfrac{\delta_m(b)}{\eta_A} = \eta_B.
    \end{aligned}
    $$
    
    Since $\gamma_A\perp\eta_B$, by [Property 4'](#ord-prop-4p), we have
    
    $$
    \delta_m(a^{\gamma_B}b^{\eta_A}) = \gamma_A\eta_B = \prod_p p^{\max\{\alpha_p,\beta_p\}} = [\delta_m(a),\delta_m(b)].
    $$
    
    Therefore, $c=a^{\gamma_B}b^{\eta_A}$ is an element of order $[\delta_m(a),\delta_m(b)]$.

This conclusion is often used to construct elements of specified orders.

## Primitive Roots

A primitive root is a special element—its order equals the number of elements in the reduced residue system modulo $m$.

???+ abstract "Primitive Root"
    For $m\in\mathbf N_+$, if there exists $g\in\mathbf Z$ with $g\perp m$ such that $\delta_m(g)=|\mathbf Z_m^*|=\varphi(m)$, then $g$ is called a **primitive root modulo $m$**. Here, $\varphi(m)$ is the [Euler's totient function](./euler-totient.md).

Not all positive integers $m$ have primitive roots modulo $m$. From [Property 1](#ord-prop-1) above, if a primitive root $g$ modulo $m$ exists, then $g,g^2,\cdots,g^{\varphi(m)}$ are in distinct congruence classes, forming a reduced residue system modulo $m$. In particular, for a prime $p$, the remainders $g^i\bmod p$ for $i=1,2,\cdots,p-1$ are all distinct.

???+ tip "Note"
    In [abstract algebra](../algebra/ring-theory.md#application-the-multiplicative-group-of-integer-congruence-classes), a primitive root is a generator of a cyclic group. This concept is only called "primitive root" in the group formed by the reduced residue system modulo $m$ under multiplication; in general cyclic groups, it is called a "generator". Not every reduced residue system modulo $m$ under multiplication forms a cyclic group. The existence of a primitive root indicates it is isomorphic to a cyclic group; if no primitive root exists, it is not isomorphic.

When the modulus is $1$, the multiplicative group of integers modulo $1$ is $\{0\}$. This is obviously a cyclic group, so the primitive root is $0$.

### Primitive Root Existence Criterion

If we know all prime factors of $\varphi(m)$, it is easy to determine whether a primitive root modulo $m$ exists.

???+ note "Theorem"
    For integer $m\ge 3$ and $g\perp m$, $g$ is a primitive root modulo $m$ if and only if for every prime factor $p$ of $\varphi(m)$, we have
    
    $$
    g^{\frac{\varphi(m)}{p}}\not\equiv 1 \pmod m.
    $$

??? note "Proof"
    The necessity is obvious. To prove sufficiency, use proof by contradiction. If $g$ is not a primitive root modulo $m$, then $\delta_m(g) < \varphi(m)$. By [Property 2](#ord-prop-2) and Euler's theorem, $\delta_m(g)\mid\varphi(m)$. Let $p$ be a prime factor of $\dfrac{\varphi(m)}{\delta_m(g)}$. Then $\delta_m(g)\mid\dfrac{\varphi(m)}{p}$. Applying Property 2 again gives
    
    $$
    g^{\frac{\varphi(m)}{p}} \equiv 1 \pmod m.
    $$
    
    However, $p$ is also a factor of $\varphi(m)$, which contradicts the given condition. Thus, the sufficiency of the proposition holds.

### Number of Primitive Roots

If primitive roots exist, they are not necessarily unique. In general, for all elements in the reduced residue system modulo $m$, we have the following conclusions about possible orders and the number of elements of a given order:

???+ note "Theorem"
    If the positive integer $m$ has a primitive root $g$, then there exist elements of order $d$ modulo $m$ if and only if $d\mid\varphi(m)$, and there are exactly $\varphi(d)$ such elements. In particular, the number of primitive roots modulo $m$ is $\varphi(\varphi(m))$.

??? note "Proof"
    According to the definition of primitive root, all reduced congruence classes modulo $m$ can be written as $g^k\bmod m$, where $k$ is one of $1,2,\cdots,\varphi(m)$. By [Property 3](#ord-prop-3), the order of these elements equals
    
    $$
    \delta_m(g^k) = \dfrac{\varphi(m)}{(\varphi(m),k)}.
    $$
    
    Therefore, elements of order $d$ exist if and only if $d\mid\varphi(m)$. Moreover, for $d\mid\varphi(m)$, letting $d'=\varphi(m)/d$, the set of these elements is
    
    $$
    \begin{aligned}
    A &= \{g^k : (\varphi(m),k)=d',~1\le k \le\varphi(m)\} \\
    &= \{g^k : d'\mid k,~ (d, k/d') = 1,~ 1 \le k/d' \le d\}.
    \end{aligned}
    $$
    
    The corresponding $k'=k/d'$ are exactly those positive integers not exceeding $d$ and coprime to $d$. By the definition of Euler's totient function, there are $\varphi(d)$ of them.

### Primitive Root Existence Theorem

This section will establish the following primitive root existence theorem:

???+ note "Theorem"
    A primitive root modulo $m$ exists if and only if $m=1,2,4,p^e,2p^e$, where $p$ is an odd prime and $e\in\mathbf N_+$.

To explain this conclusion, we need to discuss the following four cases separately:

1.  $m=1,2,4$, the primitive roots are $g=0,1,3$ respectively, which obviously exist.

2.  $m=p^{e}$ is a power of an odd prime, where $p$ is an odd prime and $e\in\mathbf N_+$.

    ???+ note "Lemma 1"
        For an odd prime $p$, a primitive root modulo $p$ exists.

    ??? note "Proof"
        The proof has two steps.
        
        **Step 1**: For $d\mid(p-1)$, the congruence equation $x^d\equiv 1\pmod p$ has exactly $d$ distinct solutions.
        
        Let $p-1=kd$, and the polynomial
        
        $$
        f(x) = x^{d(k-1)} + x^{d(k-2)} + \cdots + x^d + 1. 
        $$
        
        According to [Euler's Theorem](./fermat.md#euler-theorem), the congruence equation $(x^d-1)f(x)=x^{p-1}-1\equiv 0\pmod{p}$ has exactly $p-1$ distinct solutions. These solutions are respectively the zeros of $x^d-1$ and $f(x)$. By [Lagrange's Theorem](./congruence-equation.md#theorem-3lagrange-theorem), they can have at most $d$ and $d(k-1)$ distinct zeros respectively. Since $d+d(k-1)=p-1$, the former can only have exactly $d$ distinct zeros. This shows the congruence equation $x^d\equiv 1\pmod p$ has exactly $d$ distinct solutions.
        
        **Step 2**: For $d\mid(p-1)$, there are exactly $\varphi(d)$ elements of order $d$.
        
        Sort all factors of $\varphi(p)$ and apply induction. Since the element of order $1$ can only be $1$, there is only one, so the induction base holds. For $d\mid(p-1)$, according to [Property 2](#ord-prop-2), all solutions to $x^d\equiv 1\pmod p$ must satisfy $\delta_p(x)\mid d$. Therefore, the number of elements of order $d$ is
        
        $$
        N(d) = d - \sum_{e\mid d,~e\neq d} N(e) =  d - \sum_{e\mid d,~e\neq d} \varphi(e) = \varphi(d).
        $$
        
        The second equality is the induction hypothesis, and the third equality is a property of Euler's totient function. By mathematical induction, for all $d\mid(p-1)$, there are exactly $\varphi(d)$ elements of order $d$.
        
        In particular, for $d=p-1$, there are exactly $\varphi(p-1)$ elements of order $p-1$. Therefore, a primitive root modulo $p$ exists.

    ???+ note "Lemma 2"
        For an odd prime $p$ and $e \in \mathbf{N}_+$, a primitive root modulo $p^e$ exists.

    ??? note "Proof"
        The proof has three steps.
        
        **Step 1**: There exists a primitive root $g$ modulo $p$ such that $g^{p-1}\not\equiv 1\pmod{p^2}$.
        
        Take any primitive root $g$ modulo $p$. If it does not satisfy the condition, i.e., $g^{p-1}\equiv 1\pmod{p^2}$, then we can prove $g+p$ satisfies the condition: $g+p$ is also a primitive root modulo $p$, and
        
        $$
        \begin{aligned}
        (g+p)^{p-1} &\equiv \binom{p-1}{0}g^{p-1} + \binom{p-1}{1}g^{p-2}p \\
        &= g^{p-1} + g^{p-2}p(p-1) \\ 
        &\equiv 1 - pg^{p-2} \not\equiv 1 \pmod{p^2}.
        \end{aligned}
        $$
        
        **Step 2**: The $g$ selected above satisfies $g^{\varphi(p^e)}\not\equiv 1\pmod{p^{e+1}}$ for any $e\ge 1$.
        
        The selection of $g$ ensures the equation holds for $e=1$. Suppose the equation holds for the case of $e$, now we prove the case of $e+1$ also holds. For any $e \ge 1$, by Euler's theorem, there exists $\lambda$ such that
        
        $$
        g^{\varphi(p^e)} = 1 + \lambda p^e
        $$
        
        holds. By the induction hypothesis, $\lambda\perp p$. Since $\varphi(p^{e+1})=p\varphi(p^e)$,
        
        $$
        g^{\varphi(p^{e+1})} = \left(g^{\varphi(p^{e})}\right)^p = (1 + \lambda p^e)^p \equiv 1 + \lambda p^{e+1} \pmod{p^{e+2}}.
        $$
        
        Combined with $\lambda\perp p$, we have $g^{\varphi(p^{e+1})}\not\equiv 1\pmod{p^{e+2}}$. By mathematical induction, the proposition holds.
        
        **Step 3**: The $g$ selected above is a primitive root modulo $p^e$ for any $e\ge 1$.
        
        The selection of $g$ ensures the proposition holds for $e=1$. Assuming the proposition holds for $e$, now we prove it also holds for $e+1$. Let $\delta_{p^{e+1}}(g)$ be abbreviated as $\delta$. Since $g^\delta\equiv 1\pmod{p^{e+1}}$, we also have $g^\delta\equiv 1\pmod{p^e}$. By the induction hypothesis, $\delta_{p^e}(g) = \varphi(p^e)$. Therefore, by Property 2 of order from earlier, $\varphi(p^e)\mid\delta$. Also by Euler's theorem, $\delta\mid\varphi(p^{e+1})$. But $\varphi(p^{e+1})=p\varphi(p^e)$. So there are only two possibilities: $\delta=\varphi(p^e)$ or $\delta=\varphi(p^{e+1})$. However, the conclusion from Step 2 shows $g^{\varphi(p^e)}\not\equiv 1\pmod{p^{e+1}}$. Therefore, the possibility $\delta=\varphi(p^e)$ does not hold. The only possibility is $\delta=\varphi(p^{e+1})$. This shows $g$ is a primitive root of $p^{e+1}$. By mathematical induction, the proposition holds for all $e\ge 1$.

3.  $m=2p^{e}$, where $p$ is an odd prime and $e\in\mathbf N_+$.

    ???+ note "Lemma 3"
        For an odd prime $p$ and $e \in \mathbf{N}_+$, a primitive root modulo $2p^e$ exists.

    ??? note "Proof"
        Let $g$ be a primitive root modulo $p^{e}$, then $g+p^e$ is also a primitive root modulo $p^{e}$. One of them must be odd, suppose it is $g$. Obviously, $(g,2p^e)=1$. Let $\delta=\delta_{2p^e}(g)$, and we need to prove $\delta=\varphi(2p^e)$. By Euler's theorem, $\delta\mid\varphi(2p^e)$. At the same time, by definition $g^\delta\equiv 1\pmod{2p^e}$, so $g^\delta\equiv 1\pmod{p^e}$, therefore by Property 2 of order and the selection of $g$, $\delta_{p^e}(g)=\varphi(p^e)\mid \delta$. From the Euler's totient function formula, $\varphi(2p^e) = \varphi(p^e)$. So $\delta=\delta_{2p^e}(g)=\varphi(p^e)$. This shows $\delta$ is a primitive root modulo $2p^e$.

4.  $m\ne 1,2,4,p^{e},2p^{e}$, where $p$ is an odd prime and $e\in\mathbf N_+$.

    <a id="prim-root-lem-4"></a>

    ???+ note "Lemma 4"
        Suppose $m\neq 1,2,4$ and there is no odd prime $p$ and positive integer $e$ such that $m=p^e$ or $m=2p^e$. Then no primitive root modulo $m$ exists.

    ??? note "Proof"
        For $m=2^e$ with $e\ge 3$, suppose a primitive root $g$ modulo $m$ exists. Since $g\perp m$, it must be odd. Suppose $g=2k+1$ with $k\in\mathbf N$, then we have
        
        $$
        \begin{aligned}
        g^{2^{e-2}}
        &=(2k+1)^{2^{e-2}} \\
        &\equiv 1 + \binom{2^{e-2}}{1}(2k) + \binom{{2^{e-2}}}{2}(2k)^2 \\
        &= 1 + 2^{e-1}k + 2^{e-1}(2^{e-2}-1)k^2 \\
        &= 1 + 2^{e-1}(k + (2^{e-2}-1)k^2) \\
        &\equiv 1 \pmod{2^{e}}.
        \end{aligned}
        $$
        
        In the second-to-last line, since $k$ and $(2^{e-2}-1)k^2$ have the same parity, their sum is even. By the definition of order, $\delta_{2^{e}}(g)\le 2^{e-2}< \varphi(2^{e}) = 2^{e-1}$. This contradicts the assumption that $g$ is a primitive root. By proof by contradiction, such a primitive root does not exist.
        
        Suppose $m$ satisfies the stated conditions and is not a power of $2$. Then there exist $2 < m_1 < m_2$ with $m_1\perp m_2$ such that $m=m_1m_2$ holds. Suppose a primitive root $g$ modulo $m$ exists. Since $g\perp m$, for $i=1,2$, we have $g\perp m_i$. By Euler's theorem,
        
        $$
        g^{\varphi(m_i)} \equiv 1 \pmod{m_i}.
        $$
        
        Since $m_i > 2$, $\varphi(m_i)$ is even, so for $i=1,2$,
        
        $$
        g^{\frac{1}{2}\varphi(m_1)\varphi(m_2)} \equiv 1 \pmod{m_i}.
        $$
        
        By the [Chinese Remainder Theorem](./crt.md),
        
        $$
        g^{\frac{1}{2}\varphi(m_1)\varphi(m_2)} \equiv 1 \pmod{m}.
        $$
        
        Also since $\varphi(m)=\varphi(m_1)\varphi(m_2)$, by the definition of order,
        
        $$
        \delta_m(g) \le \frac{1}{2}\varphi(m_1)\varphi(m_2) = \dfrac{1}{2}\varphi(m) < \varphi(m).
        $$
        
        This contradicts the assumption that $g$ is a primitive root modulo $m$. Therefore, by proof by contradiction, no primitive root modulo $m$ exists.

Synthesizing these four lemmas, we have given a necessary and sufficient condition for a number to have a primitive root.

### Algorithm for Finding Primitive Roots

For any modulus $m$ that has a primitive root, to find its primitive root $g$, we only need to enumerate possible positive integers and check whether each is a primitive root. When enumerating, there are two common approaches: enumerate in increasing order, or randomly generate some positive integers. These two enumeration methods have comparable actual efficiency.

When enumerating in increasing order, we obtain the smallest primitive root $g_m$ modulo $m$. Therefore, the complexity of the enumeration part depends on the size of $g_m$. For this, we have the following estimates:

-   Upper bound estimate: Wang[^yuan1959note] and Burgess[^burgess1962character] proved that for a prime $p$, the smallest primitive root $g_p=O\left(p^{0.25+\epsilon}\right)$, where $\epsilon>0$. Cohen, Odoni, and Stothers[^cohen1974least] and Elliott and Murata[^elliott1998least] proved this estimate also holds for moduli $p^2$ and $2p^2$, where $p$ is an odd prime. Since for $e>2$, a primitive root of $p^2$ (or $2p^2$) is also a primitive root of $p^e$ (or $2p^e$), the upper bound $O\left(p^{0.25+\epsilon}\right)$ holds for all cases.
-   Lower bound estimate: Fridlander[^fridlender1949least] and Salié[^salie1949kleinsten] proved there exists $C>0$ such that for infinitely many primes $p$, the smallest primitive root $g_p > C\log p$ holds.
-   Average case estimate: Burgess and Elliott[^burgess1968average] proved that in the average case, the smallest primitive root of a prime $p$ is $g_p=O((\log p)^2(\log\log p)^4)$. Elliott and Murata[^elliott1997average] further conjectured that the average value of the smallest primitive root of a prime $p$ is a constant, and numerical verification[^more-evidence] shows it to be approximately $4.926$. Subsequently, Elliott and Murata[^elliott1998least] extended this conjecture to the case of modulus $2p^2$.

Based on these analyses, when brute-forcing the smallest primitive root, the complexity $O(g_m(\log m)^2)$ of the enumeration part is acceptable.

In addition to enumerating in increasing order, we can also find primitive roots by randomly generating positive integers and verifying them. The density of primitive roots is not low:[^density-prim-root]

$$
\dfrac{\varphi(\varphi(m))}{m} = \Omega\left(\dfrac{1}{\log\log m}\right).
$$

Therefore, when using random methods to find primitive roots, the expected complexity of the enumeration part is $O((\log m)^2\log\log m)$.

It should be noted that determining primitive roots requires knowing the prime factorization of $\varphi(m)$. Among prime factorization algorithms commonly used in programming contests, the Pollard Rho algorithm with optimal complexity also requires $O(m^{1/4+\varepsilon})$ time. Therefore, as long as the prime factorization of $\varphi(m)$ is unknown, regardless of which enumeration method is used, the bottleneck in finding primitive roots is the prime factorization step, not the verification part.

## Carmichael Function

Relative to the local concept of the order of an element modulo $m$, the Carmichael function is a global concept. It is the least common multiple of the orders of all integers coprime to $m$.

???+ abstract "Carmichael Function"
    For $m\in\mathbf N_+$, define $\lambda(m)$ as the smallest positive integer $n$ such that the congruence $a^n\equiv 1\pmod m$ holds for all $a\perp m$. The function $\lambda:\mathbf N_+\to\mathbf N_+$ is called the **Carmichael function**.

According to [Property 2](#ord-prop-2), the condition that $a^n\equiv 1\pmod m$ holds for all $a\perp m$ means $\delta_m(a)\mid n$ for all $a\perp m$. In other words, positive integers satisfying this condition must be common multiples of all $\delta_m(a)$. Therefore, the smallest such $n$ is their least common multiple:

$$
\lambda(m) = \operatorname{lcm}\{\delta_m(a) : a\perp m\}.
$$

This is also often used as an equivalent definition of the Carmichael function.

Repeatedly applying [Property 5](#ord-prop-5) shows there must exist some $a\perp m$ such that $\delta_m(a)=\lambda(m)$. Therefore, the above can also be written as

$$
\lambda(m) = \max\{\delta_m(a) : a\perp m\}.
$$

The element $a\perp m$ that achieves this maximum is also called a **$\lambda$-primitive root** modulo $m$. It exists for all moduli $m$.

### Recurrence Formula

The Carmichael function is a [number-theoretic function](./basic.md#number-theoretic-function). This section discusses a recurrence formula for it, which provides another proof of the primitive root existence theorem.

Although it is not a multiplicative function, when computing the Carmichael function, we can also handle coprime factors separately.

???+ note "Lemma"
    For coprime positive integers $m_1,m_2$, we have $\lambda(m_1m_2)=[\lambda(m_1),\lambda(m_2)]$.

??? note "Proof"
    Let $a_1$ and $a_2$ be $\lambda$-primitive roots modulo $m_1$ and $m_2$ respectively. Let $m=m_1m_2$. By the [Chinese Remainder Theorem](./crt.md), there exists $a\perp m$ such that $a\equiv a_i\pmod{m_i}$ for $i=1,2$. Since $a^{\lambda(m)}\equiv 1\pmod m$, for $i=1,2$, we have $a_i^{\lambda(m)} \equiv 1\pmod{m_i}$, and then by [Property 2](#ord-prop-2) and the selection of $a_i$, $\lambda(m_i)=\delta_{m_i}(a_i)\mid \lambda(m)$. This shows $[\lambda(m_1),\lambda(m_2)]\mid\lambda(m)$.
    
    Conversely, for any $a\perp m$ and $i=1,2$, we have $a^{[\lambda(m_1),\lambda(m_2)]} \equiv 1 \pmod{m_i}$. Applying the Chinese Remainder Theorem, we get $a^{[\lambda(m_1),\lambda(m_2)]} \equiv 1 \pmod{m}$ for all $a\perp m$. By the definition of the Carmichael function, $\lambda(m)\mid [\lambda(m_1),\lambda(m_2)]$.
    
    Thus, the equality in the proposition holds.

Therefore, we next only need to compute the value of the Carmichael function at prime powers. First, handle the case of powers of $2$.

???+ note "Lemma"
    For $m=2^e$ with $e\in\mathbf N_+$, we have $\lambda(2)=1$, $\lambda(4)=2$, and for $e\ge 3$, $\lambda(m)=2^{e-2}$.

??? note "Proof"
    For the cases $m=2,4$, we can discuss them separately. For $m=2^e$ with $e\ge 3$, first repeat the first part of the proof of [Lemma 4](#prim-root-lem-4) to get $\lambda(m)\le 2^{e-2}$. Then we only need to prove an element of order $2^{e-2}$ exists. For this, we have
    
    $$
    5^{2^{e-3}} = (1 + 2^2)^{2^{e-3}} = 1 + 2^2\times 2^{e-3} = 1 + 2^{e-1} \not\equiv 1 \pmod{2^e}.
    $$
    
    This shows $\delta_m(5)\nmid 2^{e-3}$, and since $\delta_m(5) \mid 2^{e-2}$, $5$ can only be an element of order $2^{e-2}$. This shows $\lambda(m)=2^{e-2}$.

In the proof of this lemma, we actually obtained a characterization of the structure of the reduced residue system modulo $2^e$:

<a id="mod-pow-2"></a>

???+ note "Corollary"
    Let the modulus be $2^e$ with $e \ge 2$. Then all odd numbers are congruent to exactly one integer of the form $\pm 5^k$, where $k\in\mathbf N$ and $k < 2^{e-2}$. That is, $\pm 1,\pm 5,\cdots,\pm 5^{2^{e-2}-1}$ are pairwise incongruent and form a reduced residue system.

??? note "Proof"
    It is easy to verify that the case $e=2$ holds. For $e \ge 3$, since in the above proof we have obtained that the order of $5$ modulo $2^e$ is $2^{e-2}$, so $1,5,\cdots,5^{2^{e-2}-1}$ are pairwise incongruent. Since these integers are all congruent to $1$ modulo $4$, their opposites are all congruent to $3$ modulo $4$, so $\pm 1,\pm 5,\cdots,\pm 5^{2^{e-2}-1}$ are pairwise incongruent modulo $2^e$. Since they number exactly $2^{e-1}$, which equals the size of the reduced residue system modulo $2^{e}$, they themselves form the reduced residue system.

Then handle the case of odd prime powers.

???+ note "Lemma"
    For $m=p^e$, where $p$ is an odd prime and $e\in\mathbf N_+$, we have $\lambda(m)=p^{e-1}(p-1)$.

??? note "Proof"
    First prove the proposition holds for $e=1$, i.e., $m=p$ is an odd prime. For this, by the definition of the Carmichael function, all integers $a$ coprime to $p$ are solutions to the congruence $x^{\lambda(p)}\equiv 1\pmod{p}$. In modulo $p$ sense, this equation has $p-1$ distinct solutions. By [Lagrange's Theorem](./congruence-equation.md#theorem-3lagrange-theorem), $p-1\le\lambda(p)$. At the same time, Euler's theorem requires $\lambda(p)\mid\varphi(p)=p-1$. Therefore, $\lambda(p)=p-1$.
    
    For $m=p^e$ with $e> 1$, we can start by proving $1+p$ is an element of order $p^{e-1}$. For this, we have
    
    $$
    (1+p)^{p^{e-1}} \equiv 1,\quad (1+p)^{p^{e-2}} \equiv 1 + p^{e-1} \not\equiv 1 \pmod{p^e}.
    $$
    
    So $\delta_m(1+p)=p^{e-1}$. Additionally, let $g$ be a primitive root modulo $p$. Since $g^{\delta_m(g)}\equiv 1 \pmod{p}$, by Property 2 of order, $p-1\mid\delta_m(p)$. From the definition of the Carmichael function and Euler's theorem,
    
    $$
    p^{e-1}(p-1) = [\delta_m(p),p^{e-1}]\mid\lambda(m) \mid \varphi(m) = p^{e-1}(p-1).
    $$
    
    Therefore, $\lambda(m)=p^{e-1}(p-1)$.

Simply summarizing the results of this section, we obtain the recurrence formula for the Carmichael function:

???+ note "Theorem"
    For any positive integer $m$, we have
    
    $$
    \lambda(m) = \begin{cases}
    \varphi(m), & \text{if }m=1,2,4,p^e\text{ for odd prime }p\text{ and }e \ge 1,\\
    \frac{1}{2}\varphi(m), &\text{if }m=2^e,~e\ge 3,\\
    \operatorname{lcm}\{\lambda(p_1^{e_1}),\lambda(p_2^{e_2}),\cdots,\lambda(p_s^{e_s})\}, &\text{if }m = p_1^{e_1}p_2^{e_2}\cdots p_s^{e_s}\text{ for distinct }p_1,p_2,\cdots,p_s.
    \end{cases}
    $$

Using this recurrence formula, we can strengthen the previous results:

???+ note "Corollary"
    For positive integers $m_1,m_2$, we have $\lambda([m_1,m_2])=[\lambda(m_1),\lambda(m_2)]$.

Comparing the definitions of primitive roots and the Carmichael function, a primitive root modulo $m$ exists if and only if $\lambda(m)=\varphi(m)$. From the recurrence formula of the Carmichael function, we can easily deduce:

???+ note "Corollary"
    A primitive root modulo $m$ exists if and only if $m=1,2,4,p^e,2p^e$, where $p$ is an odd prime and $e\in\mathbf N_+$.

Since the proof of the recurrence formula in this section does not use the primitive root existence theorem, this constitutes another proof of that theorem.

### Carmichael Numbers

Using the Carmichael function, we can discuss the properties and distribution of Carmichael numbers (OEIS: [A002997](https://oeis.org/A002997)). These are composite numbers that can never be correctly excluded by the [Fermat primality test](./prime.md#fermat-primality-test).

???+ abstract "Carmichael Number"
    For a composite number $n$, if for all integers $a\perp n$, the congruence $a^{n-1} \equiv 1 \pmod n$ holds, then $n$ is called a **Carmichael number**.

The smallest Carmichael number is $561 = 3 \times 11 \times 17$.

From the definition of the Carmichael function, a composite number $n$ is a Carmichael number if and only if $\lambda(n)\mid n-1$, where $\lambda(n)$ is the Carmichael function. Furthermore, we can obtain the following method to determine whether a composite $n$ is a Carmichael number:

???+ note "Korselt's Criterion[^korselt1899probleme]"
    A composite $n$ is a Carmichael number if and only if $n$ is square-free and for any prime factor $p$ of $n$, we have $(p-1) \mid (n-1)$.

??? note "Proof"
    First prove the necessity of the condition. Assume $\lambda(n)\mid (n-1)$. Checking the recurrence formula of the Carmichael function, if $n$ has a square factor $p$, then $p\mid\lambda(n)$. But $p\nmid (n-1)$, contradiction. Similarly, the recurrence formula of the Carmichael function shows $(p-1)\mid\lambda(n)$, so $(p-1) \mid (n-1)$.
    
    Then prove the sufficiency of the condition. Since $n$ is composite, it must have an odd prime factor $p$, so $n-1$ is even, and $n$ is odd. For a square-free odd composite $n$, the recurrence formula of the Carmichael function gives $\lambda(n)=\operatorname{lcm}\{p-1:p\mid n\}$. Therefore, as long as $(p-1) \mid (n-1)$ holds for all prime factors $p$, we must have $\lambda(n)\mid (n-1)$.

From this criterion, we can establish some simple properties of Carmichael numbers:

???+ note "Corollary"
    Carmichael numbers are odd, square-free, and have at least $3$ distinct prime factors.

??? note "Proof"
    The first two properties can be directly obtained from Korselt's criterion and its proof. To get the third property, we only need to prove: for distinct primes $p_1,p_2$, their product $n=p_1p_2$ is definitely not a Carmichael number. Suppose $n=p_1p_2$ is a Carmichael number. By Korselt's criterion, $(p_i-1)\mid (n-1)$. But
    
    $$
    n-1=p_1p_2-1\equiv p_2-1 \pmod{p_1-1}.
    $$
    
    Therefore, $(p_1-1)\mid(p_2-1)$. Similarly, $(p_2-1)\mid(p_1-1)$. That is, $p_1=p_2$. This contradicts the assumption. Therefore, a Carmichael number $n$ has at least $3$ distinct prime factors.

Using analytic number theory, we can also obtain some properties of the distribution of Carmichael numbers. Let $C(n)$ be the number of Carmichael numbers not exceeding $n$. Alford, Granville, and Pomerance[^alford1994infinitely] proved that for sufficiently large $n$, $C(n)>n^{2/7}$. Hence, there are infinitely many Carmichael numbers. Before this, Erdős[^erdos1956pseudoprimes] had proved $C(n) < n\exp\left(-c\dfrac{\ln n\ln\ln\ln n}{\ln\ln n}\right)$, where $c$ is a constant. Therefore, the distribution of Carmichael numbers is (relative to primes) quite sparse. In fact, there is[^pinchcarmichael] $C(10^9)=646$, $C(10^{18})=1~401~644$.

## References

-   [Primitive root modulo n - Wikipedia](https://en.wikipedia.org/wiki/Primitive_root_modulo_n)
-   [The order of a unit - Course Notes](https://crypto.stanford.edu/pbc/notes/numbertheory/order.html)
-   [The primitive root theorem - Amin Witno's notes](http://witno.com/philadelphia/notes/won5.pdf)
-   [Carmichael function - Wikipedia](https://en.wikipedia.org/wiki/Carmichael_function)
-   [Carmichael's Lambda Function - Brilliant Math & Science Wiki](https://brilliant.org/wiki/carmichaels-lambda-function/)
-   [Carmichael number - Wikipedia](https://en.wikipedia.org/wiki/Carmichael_number)
-   [Carmichael Number - Wolfram MathWorld](https://mathworld.wolfram.com/CarmichaelNumber.html)

[^yuan1959note]: Wang Y. "On the least primitive root of a prime." (in Chinese). Acta Math Sinica, 1959, 4: 432–441; English transl. in*Sci. Sinica*, 1961, 10: 1–14.

[^burgess1962character]: BURGESS, David A. "On character sums and primitive roots." Proceedings of the London Mathematical Society, 1962, 3.1: 179-192.

[^cohen1974least]: Cohen, S. D., R. W. K. Odoni, and W. W. Stothers. "On the least primitive root modulo p 2." Bulletin of the London Mathematical Society 6, no. 1 (1974): 42-46.

[^elliott1998least]: Elliott, P. D. T. A., and L. Murata. "The least primitive root mod 2p2." Mathematika 45, no. 2 (1998): 371-379.

[^fridlender1949least]: FRIDLENDER, V. R. "On the least n-th power non-residue." Dokl. Akad. Nauk SSSR. 1949. p. 351-352.

[^salie1949kleinsten]: SALIÉ, Hans. "Über den kleinsten positiven quadratischen Nichtrest nach einer Primzahl." Mathematische Nachrichten, 1949, 3.1: 7-8.

[^burgess1968average]: Burgess, D. A., and P. D. T. A. Elliott. "The average of the least primitive root." Mathematika 15, no. 1 (1968): 39-50.

[^elliott1997average]: Elliott, Peter DTA, and Leo Murata. "On the average of the least primitive root modulo p." Journal of The london Mathematical Society 56, no. 3 (1997): 435-454.

[^more-evidence]: For more results, see [Least prime primitive root of prime numbers](https://sweet.ua.pt/tos/p_roots.html).

[^density-prim-root]: If a primitive root modulo $m$ exists, then $\varphi(m)\ge\dfrac{1}{3}m$, and equality holds only at $m=2\times 3^e~(e\in\mathbf N_+)$. Furthermore, when $m > 2$, for Euler's totient function $\varphi(m)$ we have: $\varphi(m)>\dfrac{m}{e^{\gamma}\log\log m+\frac{3}{\log\log m}}$. Combining these two gives the expression in the article. For this estimate of Euler's totient function, refer to the paper Rosser, J. Barkley, and Lowell Schoenfeld. "Approximate formulas for some functions of prime numbers." Illinois Journal of Mathematics 6, no. 1 (1962): 64-94.

[^korselt1899probleme]: Korselt, A. R. (1899). "Problème chinois." L'Intermédiaire des Mathématiciens. 6: 142–143.

[^alford1994infinitely]: W. R. Alford; Andrew Granville; Carl Pomerance (1994). "There are Infinitely Many Carmichael Numbers." Annals of Mathematics. 140 (3): 703–722.

[^erdos1956pseudoprimes]: Erdős, P. (1956). "On pseudoprimes and Carmichael numbers." Publ. Math. Debrecen. 4 (3–4): 201–206.

[^pinchcarmichael]: PINCH, Richard GE. The Carmichael numbers up to ${10}^{20}$.