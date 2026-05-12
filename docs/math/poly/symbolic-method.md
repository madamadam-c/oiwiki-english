The symbolic method is a technique for quickly converting combinatorial objects into generating functions. We will consider specific operations defined on sets and derive the corresponding operations on generating functions.

We call a combinatorial class (or simply class) $(\mathcal{A},\lvert \cdot \rvert)$, where $\mathcal{A}$ is the set of combinatorial objects, and the function $\lvert \cdot \rvert$ maps each combinatorial object to a non-negative integer, generally called the size function. Note that this non-negative integer cannot be infinite. For example, for strings with alphabet $\{0,1\}$, we can set the length of the string as its size function; for trees or graphs, we can set the number of nodes as the size function. Note that this is not absolute—some specific nodes may have size function set to $0$, etc.

This article is a simplification based on Chapter 1 of Analytic Combinatorics.

## Unlabeled System

In the unlabeled system, we use ordinary generating functions (OGF). For a set $\mathcal{A}$, its corresponding OGF is denoted as

$$
A(z)=\sum_{\alpha\in\mathcal{A}}z^{\lvert \alpha \rvert}=\sum_{n\geq 0}a_nz^n
$$

We agree to use the same group of letters to represent the generating function of the same class, for example, using $a_n$ to denote $\lbrack z^n\rbrack A(z)$, i.e., the coefficient of $z^n$ in $A(z)$, and using $\mathcal{A}_n$ to denote the set of objects in $\mathcal{A}$ with size function $n$ (so $a_n=\operatorname{card}(\mathcal{A}_n)$ where $\operatorname{card}$ is cardinality).

This article will not discuss admissibility; readers can refer to the literature for content.

Next, we introduce two special combinatorial classes and objects:

-   Let $\epsilon$ be a neutral object and $\mathcal{E}=\lbrace \epsilon \rbrace$ be a neutral class. The neutral object has size $0$, and the OGF of the neutral class is $E(z)=1$.
-   Let $\circ$ or $\bullet$ be an atom object and $\mathcal{Z}_{\circ}=\lbrace \circ\rbrace$ or $\mathcal{Z}_{\bullet}=\lbrace \bullet\rbrace$ (or simply $\mathcal{Z}$) be an atom class. The atom object has size $1$, and the OGF of the atom class is $Z(z)=z$.

For two combinatorial classes $\mathcal{A}$ and $\mathcal{B}$, we denote combinatorial isomorphism as $\mathcal{A}=\mathcal{B}$ or $\mathcal{A}\cong\mathcal{B}$, but we only use the latter notation when the isomorphism is non-trivial.

We have

$$
\mathcal{A}\cong\mathcal{E}\times \mathcal{A}\cong\mathcal{A}\times\mathcal{E}
$$

where $\times$ is a binary operation representing the Cartesian product of sets.

### Set (Disjoint) Union Construction

For the union of classes $\mathcal{A}$ and $\mathcal{B}$, we denote

$$
\mathcal{A}+\mathcal{B}=(\mathcal{E}_{1}\times\mathcal{A})+(\mathcal{E}_2\times\mathcal{B})
$$

This definition avoids violating the requirement of disjoint sets in set theory. We can imagine coloring the objects in $\mathcal{A}$ red and the objects in $\mathcal{B}$ blue.

The corresponding OGF is

$$
A(z)+B(z)
$$

Consider

$$
A(z)+B(z)=\sum _ {\alpha\in\mathcal{A}}z^{\lvert \alpha\rvert} + \sum _ {\beta\in\mathcal{B}}z^{\lvert \beta\rvert}=\sum_{n\geq 0}(a_n+b_n)z^n
$$

Corresponding to addition of formal power series.

### Set Cartesian Product Construction

For the Cartesian product of classes $\mathcal{A}$ and $\mathcal{B}$, we denote

$$
\mathcal{A}\times \mathcal{B}=\left\lbrace (\alpha, \beta)\mid \alpha \in \mathcal{A},\beta\in\mathcal{B}\right\rbrace
$$

The corresponding OGF is

$$
A(z)\cdot B(z)
$$

We define the size of $(\alpha,\beta)$ as the sum of the sizes of its components. Then we also have

$$
\gamma =(\alpha_1,\alpha_2,\dots ,\alpha_n)\implies \lvert \gamma\rvert =\lvert \alpha_1\rvert +\lvert \alpha_2\rvert +\cdots +\lvert \alpha_n\rvert
$$

So

$$
A(z)\cdot B(z)=\left(\sum _ {\alpha\in\mathcal{A}}z^{\lvert \alpha\rvert}\right)\left(\sum _ {\beta\in\mathcal{B}}z^{\lvert \beta\rvert}\right)=\sum _ {(\alpha, \beta)\in(\mathcal{A}\times \mathcal{B})}z^{\lvert \alpha\rvert +\lvert \beta\rvert}=\sum_{n\geq 0}\sum_{i+j=n}a_ib_jz^n
$$

Corresponding to multiplication of formal power series.

### Set Sequence Construction

The Sequence construction generates all possible combinations.

???+ note "Example"
    $$
    \begin{aligned}
    \operatorname{SEQ}(\lbrace a\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace +\lbrace (a,a)\rbrace +\lbrace (a,a,a)\rbrace +\cdots\\
    \operatorname{SEQ}(\lbrace a,b\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a,b\rbrace +\lbrace (a,b)\rbrace + \lbrace(b,a)\rbrace +\lbrace (a,a)\rbrace +\lbrace (b,b)\rbrace\\
    &+\lbrace (a,b,a)\rbrace +\lbrace (a,b,b)\rbrace +\lbrace (a,a,b)\rbrace\\
    &+\lbrace (b,b,a)\rbrace +\lbrace (b,a,b)\rbrace +\lbrace (b,b,b)\rbrace +\lbrace (a,a,a)\rbrace +\lbrace (b,a,a)\rbrace\\
    &+\cdots
    \end{aligned}
    $$
    
    We can see that elements with different orders of components like $\lbrace (a,b)\rbrace ,\lbrace (b,a)\rbrace$ are generated. The Sequence construction generates ordered combinations.

We define

$$
\operatorname{SEQ}(\mathcal{A})=\mathcal{E}+\mathcal{A}+(\mathcal{A}\times \mathcal{A})+(\mathcal{A}\times \mathcal{A}\times \mathcal{A})+\cdots
$$

And require $\mathcal{A}_0=\varnothing$, i.e., there are no objects of size $0$ in $\mathcal{A}$.

The corresponding OGF is

$$
Q(A(z))=1+A(z)+A(z)^2+A(z)^3+\cdots =\frac{1}{1-A(z)}
$$

Where $Q$ is Pólya's quasi-inversion.

???+ note "Example: Ordered Rooted Tree"
    We can use the Sequence construction to define ordered rooted trees, i.e., rooted trees where the order among children is significant. Let this combinatorial class be $\mathcal{T}$. A tree consists of a root node and a Sequence of trees:
    
    $$
    \mathcal{T}=\lbrace \bullet\rbrace\times\operatorname{SEQ}(\mathcal{T})
    $$
    
    The corresponding OGF is
    
    $$
    T(z)=\frac{z}{1-T(z)}
    $$
    
    The first few coefficients are `0 1 1 2 5 14 42 132 429 1430 4862 16796`. Ignoring the constant term, this is OEIS [A000108](http://oeis.org/A000108).

### Set Multiset Construction

The Multiset construction generates all possible combinations but does not distinguish the order among elements in a component.

???+ note "Example"
    $$
    \begin{aligned}
    \operatorname{MSET}(\lbrace a\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace +\lbrace (a,a)\rbrace +\lbrace (a,a,a)\rbrace +\cdots\\
    \operatorname{MSET}(\lbrace a,b\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace +\lbrace (a,a)\rbrace +\lbrace (a,a,a)\rbrace +\cdots\\
    &+\lbrace b\rbrace +\lbrace (a,b)\rbrace +\lbrace (a,a,b)\rbrace +\cdots \\
    &+\lbrace (b,b)\rbrace + \lbrace (a,b,b)\rbrace +\lbrace (a,a,b,b)\rbrace + \cdots\\
    &+\cdots
    \end{aligned}
    $$
    
    Note that $\lbrace (b,a)\rbrace,\lbrace (a,b,a)\rbrace$ appear in $\operatorname{SEQ}(\lbrace a,b\rbrace)$ but not in $\operatorname{MSET}(\lbrace a,b\rbrace)$. We can consider that Multiset generates unordered combinations.

We define its recursive formula as

$$
\operatorname{MSET}(\lbrace \alpha_0,\alpha_1,\dots, \alpha_n\rbrace)=\operatorname{MSET}(\lbrace \alpha_0,\alpha_1,\dots, \alpha_{n-1}\rbrace)\times \operatorname{SEQ}(\lbrace \alpha_n\rbrace)
$$

That is

$$
\operatorname{MSET}(\mathcal{A})=\prod _ {\alpha\in\mathcal{A}}\operatorname{SEQ}(\lbrace \alpha\rbrace)
$$

And require $\mathcal{A}_0=\varnothing$. Alternatively, we can give the equivalent

$$
\operatorname{MSET}(\mathcal{A})=\operatorname{SEQ}(\mathcal{A})/\mathbf{R}
$$

Where $\mathbf{R}$ is an equivalence relation. We say $(\alpha_1,\dots,\alpha_n)\mathbf{R}(\beta_1,\dots,\beta_n)$ if and only if there exists a permutation $\sigma$ such that $\beta_{j}=\alpha_{\sigma(j)}$ for all $j$.

The corresponding OGF is

$$
\operatorname{Exp}(A(z))=\prod _ {\alpha \in\mathcal{A}}\left(1-z^{\lvert \alpha \rvert}\right)^{-1}=\prod _ {n\geq 1}\left(1-z^n\right)^{-a_n}
$$

Note that

$$
\ln(1+z)=\frac{z}{1}-\frac{z^2}{2}+\frac{z^3}{3}-\cdots =\sum_{n\geq 1}\frac{(-1)^{n-1}z^n}{n}
$$

And $A(z)=\exp(\ln(A(z)))$, so

$$
\begin{aligned}
\operatorname{Exp}(A(z))&=\exp\left(\sum _ {n\geq 1}-a_n\cdot \ln\left(1-z^n\right)\right)\\
&=\exp\left(\sum _ {n\geq 1}-a_n\cdot \sum _ {m\geq 1}\frac{-z^{nm}}{m}\right)\\
&=\exp\left(\frac{A(z)}{1}+\frac{A(z^2)}{2}+\frac{A(z^3)}{3}+\cdots \right)
\end{aligned}
$$

Here, $\operatorname{Exp}$ is Pólya's exponentiation operator, also known as the Euler transform.

???+ note "Problem [LOJ 6268. Partition Number](https://loj.ac/p/6268)"
    **Problem**: Let $f(n)$ be the number of ways to partition $n$, compute $f(1),f(2),\dots,f(10^5)$ modulo $998244353$.
    
    **Solution**: Let the class of all positive integers be $\mathcal{I}$, then $\mathcal{I}=\operatorname{SEQ}_{\geq 1}(\mathcal{Z})=\mathcal{Z}\times \operatorname{SEQ}(\mathcal{Z})$ (the subscript $\geq 1$ is a constrained construction, see later). What we want is
    
    $$
    \operatorname{MSET}(\mathcal{I})
    $$
    
    The corresponding OGF's first few coefficients are `1 2 3 5 7 11 15 22 30 42` (ignoring the constant term), i.e., OEIS [A000041](https://oeis.org/A000041).

???+ note "Problem [Luogu P4389 Princess Fu's Backpack](https://www.luogu.com.cn/problem/P4389)"
    **Problem**: Given $n$ types of items with volumes $v_1,\dots ,v_n$ and a positive integer $m$, find the number of ways to fill backpacks of volumes $1,2,\dots,m$ (unlimited quantity of each item, items of the same volume but different types are considered different) modulo $998244353$. It is guaranteed that $1\leq n,m\leq 10^5$ and $1\leq v_i\leq m$.
    
    **Solution**: Let the class of items be $\mathcal{A}$, what we want is the coefficients of the OGF corresponding to $\operatorname{MSET}(\mathcal{A})$.

???+ note "Problem [Luogu P5900 Unlabeled Unrooted Tree Counting](https://www.luogu.com.cn/problem/P5900)"
    **Problem**: Find the number of unlabeled unrooted trees with $n$ nodes modulo $998244353$. It is guaranteed that $1\leq n\leq 2\times 10^5$.
    
    **Solution**: Let the class of unlabeled rooted trees be $\mathcal{T}$, then
    
    $$
    \mathcal{T}=\lbrace \bullet\rbrace\times\operatorname{MSET}(\mathcal{T})
    $$
    
    According to Richard Otter's paper [The Number of Trees](https://users.math.msu.edu/users/magyarp/Math482/Otter-Trees.pdf), the corresponding OGF for unrooted trees is
    
    $$
    T(z)-\frac{1}{2}T^2(z)+\frac{1}{2}T(z^2)
    $$
    
    The first few coefficients are `1 1 1 2 3 6 11 23 47 106` (ignoring the constant term), i.e., OEIS [A000055](https://oeis.org/A000055).

### Set Powerset Construction

The Powerset construction generates all subsets.

???+ note "Example"
    $$
    \begin{aligned}
    \operatorname{PSET}(\lbrace a\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace \\
    \operatorname{PSET}(\lbrace a,b\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace +\lbrace b\rbrace +\lbrace (a,b)\rbrace \\
    \operatorname{PSET}(\lbrace a,b,c\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace +\lbrace b\rbrace +\lbrace (a,b)\rbrace +\lbrace c\rbrace +\lbrace (a,c)\rbrace +\lbrace (b,c)\rbrace +\lbrace (a,b,c)\rbrace\\
    \end{aligned}
    $$

We define its recursive formula as

$$
\operatorname{PSET}(\lbrace \alpha_0,\alpha_1,\dots, \alpha_n\rbrace)=\operatorname{PSET}(\lbrace \alpha_0,\alpha_1,\dots, \alpha_{n-1}\rbrace)\times (\lbrace \epsilon\rbrace +\lbrace \alpha_n\rbrace)
$$

That is

$$
\operatorname{PSET}(\mathcal{A})\cong \prod _ {\alpha\in\mathcal{A}}\left(\lbrace \epsilon \rbrace +\lbrace \alpha\rbrace\right)
$$

And require $\mathcal{A}_0=\varnothing$.

The corresponding OGF is

$$
\begin{aligned}
\overline{\operatorname{Exp}}(A(z))&=\prod _ {\alpha\in\mathcal{A}}\left(1+z^{\lvert \alpha \rvert}\right)=\prod _ {n\geq 1}\left(1+z^n\right)^{a_n}\\
&=\exp\left(\sum _ {n\geq 1}a_n\cdot \ln\left(1+z^n\right)\right)\\
&=\exp\left(\sum _ {n\geq 1}a_n\cdot \sum _ {m\geq 1}\frac{(-1)^{m-1}z^{nm}}{m}\right)\\
&=\exp\left(\frac{A(z)}{1}-\frac{A(z^2)}{2}+\frac{A(z^3)}{3}-\cdots \right)
\end{aligned}
$$

Here, $\overline{\operatorname{Exp}}$ is the modified Pólya exponentiation operator.

It is easy to find that $\operatorname{PSET}(\mathcal{A})\subset \operatorname{MSET}(\mathcal{A})$.

### Set Cycle Construction

The Cycle construction generates all possible combinations but does not distinguish between combinations that differ only by rotation.

We define

$$
\operatorname{CYC}(\mathcal{A})=\left(\operatorname{SEQ}(\mathcal{A})\setminus\lbrace \epsilon\rbrace\right)/\mathbf{S}
$$

Where $\mathbf{S}$ is an equivalence relation. We say $(\alpha_1,\dots,\alpha_n)\mathbf{S}(\beta_1,\dots,\beta_n)$ if and only if there exists a cyclic shift $\tau$ such that $\beta_j=\alpha_{\tau(j)}$ for all $j$.

???+ note "Example"
    For simplicity, let both $\texttt{a}$ and $\texttt{b}$ be characters of size $1$. Here we only list strings of size $3$ and $4$:
    
    $$
    \operatorname{CYC}(\lbrace \texttt{a},\texttt{b}\rbrace)_3=\lbrace \texttt{aaa}\rbrace +\lbrace \texttt{aab}\rbrace+\lbrace \texttt{abb}\rbrace+\lbrace \texttt{bbb}\rbrace
    $$
    
    Where $\texttt{aab}\mathbf{S}\texttt{baa}\mathbf{S}\texttt{aba}$ only keeps one, and similarly $\texttt{abb}\mathbf{S}\texttt{bab}\mathbf{S}\texttt{bba}$ only keeps one.
    
    $$
    \operatorname{CYC}(\lbrace \texttt{a},\texttt{b}\rbrace)_4=\lbrace \texttt{aaaa}\rbrace +\lbrace \texttt{aaab}\rbrace+\lbrace \texttt{aabb}\rbrace+\lbrace \texttt{abbb}\rbrace+\lbrace \texttt{bbbb}\rbrace +\lbrace \texttt{abab}\rbrace
    $$
    
    Where $\texttt{aaab}\mathbf{S}\texttt{baaa}\mathbf{S}\texttt{abaa}\mathbf{S}\texttt{aaba}$, $\texttt{aabb}\mathbf{S}\texttt{baab}\mathbf{S}\texttt{bbaa}\mathbf{S}\texttt{abba}$, $\texttt{abbb}\mathbf{S}\texttt{babb}\mathbf{S}\texttt{bbab}\mathbf{S}\texttt{bbba}$ and $\texttt{abab}\mathbf{S}\texttt{baba}$.

The corresponding OGF is

$$
\operatorname{Log}(A(z))=\sum _ {n\geq 1}\frac{\varphi(n)}{n}\ln\frac{1}{1-A(z^n)}
$$

Where $\varphi$ is Euler's totient function and $\operatorname{Log}$ is Pólya's log.

Since the proof is relatively complex, readers can refer to Flajolet's paper [The Cycle Construction](https://epubs.siam.org/doi/10.1137/0404006) or the appendix of Analytic Combinatorics.

### Constrained Constructions

For all the constructions above, we did not limit the number of "components". If we add a predicate on integers to the subscript of $\operatorname{SEQ}$ to constrain the number of components, such as

$$
\operatorname{SEQ}_{=k}(\mathcal{B}),\quad \operatorname{SEQ}_{\geq k}(\mathcal{B}),\quad \operatorname{SEQ}_{1..k}(\mathcal{B})
$$

Where $\operatorname{SEQ}_{=k}(\mathcal{B})$ is often abbreviated as $\operatorname{SEQ}_k(\mathcal{B})$, and $\operatorname{SEQ}_{1..k}(\mathcal{B})$ means on the interval $\lbrack 1..k\rbrack$.

Let $\mathfrak{K}$ be any one of $\operatorname{SEQ},\operatorname{PSET},\operatorname{MSET},\operatorname{CYC}$ above, and

$$
\mathcal{A}=\mathfrak{K}_k(\mathcal{B})
$$

That is, for $\alpha\in\mathcal{A}$, we have

$$
\alpha =\lbrace (\beta_1,\beta_2,\dots ,\beta_k)\mid \beta\in\mathcal{B}\rbrace
$$

Let function $\chi$ act on combinatorial objects to return the number of components, i.e., we require $\chi(\alpha)=k$. Let's add an extra variable to "track" the number of components.

Let

$$
A _ {n,k}=\operatorname{card}\left\lbrace \alpha\in\mathcal{A}\mid \lvert \alpha\rvert =n,\chi(\alpha)=k\right\rbrace
$$

Then

$$
A(z,u)=\sum _ {n,k}A _ {n,k}u^kz^n=\sum _ {\alpha\in\mathcal{A}}z^{\lvert \alpha\rvert}u^{\chi(\alpha)}
$$

Then we just need to extract the coefficient of $u^k$ to get the corresponding expression. For example, for $\mathcal{A}=\operatorname{SEQ}_k(\mathcal{B})$, we can directly derive

$$
\begin{aligned}
&{}A(z,u)=\sum _ {k\geq 0}u^kB(z)^k=\frac{1}{1-uB(z)}\\
\implies &{}A(z)=B(z)^k
\end{aligned}
$$

Obviously, we also have

$$
\mathcal{A}=\operatorname{SEQ}_{\geq k}(\mathcal{B})\implies A(z)=\frac{B(z)^k}{1-B(z)}
$$

For $\operatorname{MSET} _ k(\mathcal{B})$ and $\operatorname{PSET} _ k(\mathcal{B})$, we have

$$
\begin{aligned}
&{}A(z,u)=\prod_n\left(1-uz^n\right)^{-b_n}\\
\implies &{}A(z)=\lbrack u^k\rbrack \exp\left(\frac{u}{1}B(z)+\frac{u^2}{2}B(z^2)+\frac{u^3}{3}B(z^3)+\cdots\right)
\end{aligned}
$$

And

$$
\begin{aligned}
&{}A(z,u)=\prod_n\left(1+uz^n\right)^{b_n}\\
\implies &{}A(z)=\lbrack u^k\rbrack \exp\left(\frac{u}{1}B(z)-\frac{u^2}{2}B(z^2)+\frac{u^3}{3}B(z^3)-\cdots\right)
\end{aligned}
$$

Similarly for $\operatorname{CYC}_k(\mathcal{B})$.

??? note "Using the above formula to compute OGFs for $\operatorname{MSET}_3(\mathcal{B})$ and $\operatorname{MSET}_4(\mathcal{B})$"
    Try computing $\mathcal{A}=\operatorname{MSET}_3(\mathcal{B})$:
    
    $$
    \begin{aligned}
    \lbrack u^3\rbrack A(z,u)&= \frac{1}{0!}\left(\lbrack u^3\rbrack 1\right)+\frac{1}{1!}\left(\lbrack u^3\rbrack \left(\frac{u}{1}B(z)+\frac{u^2}{2}B(z^2)+\frac{u^3}{3}B(z^3)+\cdots \right)\right)\\
    &+\frac{1}{2!}\left(\lbrack u^3\rbrack \left(\frac{u}{1}B(z)+\frac{u^2}{2}B(z^2)+\cdots \right)^2\right)\\
    &+\frac{1}{3!}\left(\lbrack u^3\rbrack \left(\frac{u}{1}B(z)+\cdots \right)^3\right)\\
    &=\frac{B(z)^3}{6}+\frac{B(z)B(z^2)}{2}+\frac{B(z)^3}{3}
    \end{aligned}
    $$
    
    Try computing $\mathcal{A}=\operatorname{MSET}_4(\mathcal{B})$:
    
    $$
    \begin{aligned}
    \lbrack u^4\rbrack A(z,u)&= \frac{1}{0!}\left(\lbrack u^4\rbrack 1\right)+\frac{1}{1!}\left(\lbrack u^4\rbrack \left(\frac{u}{1}B(z)+\frac{u^2}{2}B(z^2)+\frac{u^3}{3}B(z^3)+\frac{u^4}{4}B(z^4)+\cdots \right)\right)\\
    &+\frac{1}{2!}\left(\lbrack u^4\rbrack \left(\frac{u}{1}B(z)+\frac{u^2}{2}B(z^2)+\frac{u^3}{3}B(z^3)+\cdots \right)^2\right)\\
    &+\frac{1}{3!}\left(\lbrack u^4\rbrack \left(\frac{u}{1}B(z)+\frac{u^2}{2}B(z^2)+\cdots \right)^3\right)\\
    &+\frac{1}{4!}\left(\lbrack u^4\rbrack \left(\frac{u}{1}B(z)+\cdots \right)^4\right)\\
    &=\frac{B(z^4)}{4}+\frac{1}{2!}\left(\frac{B(z^2)^2}{4}+\frac{2B(z)B(z^3)}{3}\right)+\frac{1}{3!}\left(\frac{3B(z)^2B(z^2)}{2}\right)+\frac{B(z)^4}{4!}\\
    &=\frac{B(z)^4}{24}+\frac{B(z)^2B(z^2)}{4}+\frac{B(z)B(z^3)}{3}+\frac{B(z^2)^2}{8}+\frac{B(z^4)}{4}
    \end{aligned}
    $$

We find that for $\mathcal{A}=\mathfrak{K}_k(\mathcal{B})$, $A(z)$ is an expression in terms of $B(z),B(z^2),\dots ,B(z^k)$.

Note that for the constrained construction $\mathfrak{K}_k(\mathcal{B})$, it is not required that $\mathcal{B}_0=\varnothing$.

???+ note "Common Constrained Constructions"
    $$
    \begin{aligned}
    \operatorname{PSET} _ {2}(\mathcal{A})&:\quad \frac{A(z)^2}{2}-\frac{A(z^2)}{2}\\
    \operatorname{MSET} _ {2}(\mathcal{A})&:\quad \frac{A(z)^2}{2}+\frac{A(z^2)}{2}\\
    \operatorname{CYC} _ {2}(\mathcal{A})&:\quad \frac{A(z)^2}{2}+\frac{A(z^2)}{2}
    \end{aligned}
    $$
    
    $$
    \begin{aligned}
    \operatorname{PSET} _ {3}(\mathcal{A})&:\quad \frac{A(z)^3}{6}-\frac{A(z)A(z^2)}{2}+\frac{A(z^3)}{3}\\
    \operatorname{MSET} _ {3}(\mathcal{A})&:\quad \frac{A(z)^3}{6}+\frac{A(z)A(z^2)}{2}+\frac{A(z^3)}{3}\\
    \operatorname{CYC} _ {3}(\mathcal{A})&:\quad \frac{A(z)^3}{3}+\frac{2A(z^3)}{3}\\
    \end{aligned}
    $$
    
    $$
    \begin{aligned}
    \operatorname{PSET} _ {4}(\mathcal{A})&:\quad \frac{A(z)^4}{24}-\frac{A(z)^2A(z^2)}{4}+\frac{A(z)A(z^3)}{3}+\frac{A(z^2)^2}{8}-\frac{A(z^4)}{4}\\
    \operatorname{MSET} _ {4}(\mathcal{A})&:\quad \frac{A(z)^4}{24}+\frac{A(z)^2A(z^2)}{4}+\frac{A(z)A(z^3)}{3}+\frac{A(z^2)^2}{8}+\frac{A(z^4)}{4}\\
    \operatorname{CYC} _ {4}(\mathcal{A})&:\quad \frac{A(z)^4}{4}+\frac{A(z^2)^2}{4}+\frac{A(z^4)}{2}\\
    \end{aligned}
    $$

Although the calculation method above is effective, it is relatively cumbersome. Readers can read related materials on WolframMathWorld such as [Pólya Enumeration Theorem](https://mathworld.wolfram.com/PolyaEnumerationTheorem.html) and [Cycle Index](https://mathworld.wolfram.com/CycleIndex.html). The latter Cycle Index also frequently appears in generating function expressions in OEIS.

???+ note "Problem [LOJ 6538. Alkyl Count Enhanced Enhanced](https://loj.ac/p/6538)"
    **Problem**: Find the number of ordered trees with $n$ nodes where the root node has degree at most $3$ and other nodes have degree at most $4$, modulo $998244353$. It is guaranteed that $1\leq n\leq 10^5$.
    
    **Solution**: Let the combinatorial class be $\mathcal{T}$, then
    
    $$
    \mathcal{T}=\lbrace \bullet\rbrace\times\operatorname{MSET}_{0,1,2,3}(\mathcal{T})
    $$
    
    Or let the combinatorial class $\hat{\mathcal{T}}=\mathcal{T}+\lbrace \epsilon\rbrace$, then
    
    $$
    \hat{\mathcal{T}}=\lbrace \epsilon\rbrace +\lbrace \bullet\rbrace\times\operatorname{MSET}_{3}(\hat{\mathcal{T}})
    $$
    
    These yield the same result.

## References

-   Philippe Flajolet and Robert Sedgewick.[Analytic Combinatorics](http://algo.inria.fr/flajolet/Publications/books.html).
