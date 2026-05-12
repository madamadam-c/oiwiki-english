## Introduction

Order theory is a branch of mathematics that formalizes the concept of "order" using binary relations. The basic definitions of this branch are introduced below.

## Definitions

### Binary Relations

???+ note "Definition"
    A **binary relation** $R$ on sets $X$ and $Y$ is defined as the tuple $(X, Y, G(R))$, where $X$ is called the **domain**, $Y$ is called the **codomain**, and $G(R)\subseteq X\times Y=\{(x,y):x\in X,y\in Y\}$ is called the **graph** of the binary relation $R$. $xRy$ holds if and only if $(x,y)\in G(R)$.
    
    If $X=Y$, the binary relation is called a **homogeneous relation** or **endorelation**.
    
    Unless otherwise specified, all binary relations discussed below are homogeneous relations.

For example, divisibility $\mid$ and less-than-or-equal $\leq$ on $\mathbf{N}_+$ are both binary relations.

When studying binary relations, we often focus on whether they possess certain special properties. For a binary relation $R$ on set $S$, we define the following special properties:

1.  **Reflexive**: $(\forall~a \in S)~~aRa$,
2.  **Irreflexive** (anti-reflexive): $(\forall~a \in S)~~\lnot(aRa)$,
3.  **Symmetric**: $(\forall~a,b \in S)~~aRb \iff bRa$,
4.  **Antisymmetric**: $(\forall~a,b \in S)~~(aRb \land bRa) \implies a=b$,
5.  **Asymmetric**: $(\forall~a,b \in S)~~aRb \implies \lnot(bRa)$,
6.  **Transitive**: $(\forall~a,b,c \in S)~~(aRb \land bRc) \implies aRc$,
7.  **Connected**: $(\forall~a,b \in S)~~a \neq b \implies (aRb \lor bRa)$,
8.  **Well-founded**: $(\exists~m \in S \neq \varnothing)~~(\forall~a \in S\setminus\{m\})~~\lnot(aRm)$ (i.e., non-empty set $S$ has a minimal element $m$),
9.  **Transitive of incomparability**: $(\forall~a,b,c \in S)~~(\lnot(aRb \lor bRa) \land \lnot(bRc \lor cRb)) \implies \lnot(aRc \lor cRa)$ (if $\lnot(aRb \lor bRa)$, then $a$ and $b$ are **incomparable**).

We also define some special binary relations:

| Binary relation | Reflexive | Irreflexive | Symmetric | Antisymmetric | Asymmetric | Transitive | Connected | Well-founded | Transitive of incomparability |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Equivalence relation | Yes | | Yes | | | Yes | | | |
| Preorder (quasiorder) | Yes | | | | | Yes | | | |
| Partial order | Yes | | | Yes | | Yes | | | |
| Total order | Yes | | | Yes | | Yes | Yes | | |
| Well-order | Yes | | | Yes | | Yes | Yes | Yes | |
| Strict preorder | | Yes | | | | Yes | | | |
| Strict partial order | | Yes | | | Yes | Yes | | | |
| Strict weak order | | Yes | | | Yes | Yes | | | Yes |
| Strict total order | | Yes | | | Yes | Yes | Yes | | |

### Operations on Relations

For binary relations $R$ on sets $X$ and $Y$ and $S$ on sets $Y$ and $Z$, we can define the following operations:

1.  The **union** $R\cup S$ satisfies $G(R\cup S):=\{(x,y):xRy \lor xSy\}$ (e.g., $\leq$ is the union of $<$ and $=$),
2.  The **intersection** $R\cap S$ satisfies $G(R\cap S):=\{(x,y):xRy \land xSy\}$,
3.  The **complement** $\bar{R}$ satisfies $G(\bar{R}):=\{x,y):\lnot(xRy)\}$,
4.  The **converse** (transpose) $R^T$ satisfies $G(R^T):=\{(y,x):xRy\}$.

For binary relations $R$ on $X$ and $Y$ and $S$ on $Y$ and $Z$, we define their **composition** $S\circ R$ satisfying $G(S\circ R):=\{(x,z):(\exists~y\in Y)~~xRy\land ySz\}$.

### Partially Ordered Sets

???+ note "Definition"
    If a binary relation $\preceq$ on a set $S$ is **reflexive**, **antisymmetric**, and **transitive**, then $S$ is called a **partially ordered set** (poset), and $\preceq$ is a **partial order** on it.
    
    If the partial order $\preceq$ is also **connected**, it is called a **total order**, and the corresponding set is called a **totally ordered set**, **linearly ordered set** (loset), or **simply ordered set**.

It is easy to see that $\mathbf{N}$, $\mathbf{Z}$, $\mathbf{Q}$, and $\mathbf{R}$ are all totally ordered sets under $\leq$.

### Visualizing Partially Ordered Sets: Hasse Diagrams

For finite partially ordered sets, we can use Hasse diagrams to intuitively represent the partial order.

???+ note "Definition"
    For a finite partially ordered set $S$ with partial order $\preceq$, define $x\prec y\iff (x\preceq y\land x\neq y)$. Its corresponding **Hasse diagram** is a graph $G=\langle V,E\rangle$ satisfying:
    
    -   $V=S$,
    -   $E=\{(x,y)\in S\times S: x\prec y \land ((\nexists~z\in S)~~x\prec z\prec y)\}$

For example, for the power set $S$ of $\{0,1,2\}$ with set inclusion $\subseteq$, its Hasse diagram is:

![](images/order-theory1.svg)

Since a partial order is antisymmetric, a Hasse diagram is always a [directed acyclic graph](../graph/dag.md), and therefore we can construct a total order for any finite partially ordered set via [topological sorting](../graph/topo.md).

### Chains and Antichains

???+ note "Definition"
    For a partially ordered set $S$ with partial order $\preceq$, a totally ordered subset of $S$ is called a **chain**. If every two distinct elements in a subset $T$ of $S$ are incomparable (i.e., $(\forall~a,b \in T)~~a \neq b \implies (a \npreceq b \land b \npreceq a)$), then $T$ is called an **antichain**.
    
    For a partially ordered set $S$ with partial order $\preceq$, the length of the longest antichain of $S$ is called the **width** (partial order width) of $S$.

For example, for the power set $S$ of $\{0,1,2\}$ with set inclusion $\subseteq$, $\{\varnothing,\{1\},\{1,2\}\}$ is a chain, $\{\{1\},\{0,2\}\}$ is an antichain, and the width of $S$ is $3$.

### Special Elements in Preordered Sets

In preordered sets, we can define the concepts of maximal (minimal) elements, upper (lower) bounds, supremum (infimum), etc. These concepts can be extended to other order relations.

???+ note "Definition"
    For a preordered set $S$ with preorder $\preceq$, take an element $m$ in $S$:
    
    1.  If $(\forall~a \in S\setminus\{m\})~~\lnot(m\preceq a)$, then $m$ is called a **maximal element**,
    2.  If for $T \subseteq S$ we have $(\forall~t\in T)~~t\preceq m$, then $m$ is called an **upper bound** of $T$,
    3.  If for $T \subseteq S$ we have $m$ is an upper bound of $T$ and for any upper bound $n$ of $T$ we have $m \preceq n$, then $m$ is called the **supremum** of $T$.
    
    **Minimal elements**, **lower bounds**, and **infimum** can be defined similarly.

For example, $1$ is a minimal element and lower bound of $\mathbf{N}_+$.

It can be proven that:

-   In a preordered set, maximal (minimal) elements, upper (lower) bounds, and supremum (infimum) may not exist, and even if they exist, they may not be unique.

-   If a subset $T$ of a partially ordered set $S$ has a supremum (infimum), it must be unique.

    We denote the supremum and infimum of $T$ as $\sup T$ and $\inf T$ respectively. If a partially ordered set $S$ has both an upper bound and a lower bound, $S$ is called **bounded**.

In infinite partially ordered sets, maximal elements may not exist. **Zorn's Lemma** can be used to determine whether maximal elements exist in infinite partially ordered sets.

???+ note "[Zorn's Lemma](https://en.wikipedia.org/wiki/Zorn%27s_lemma)"
    **Zorn's Lemma** is also known as the **Kuratowski–Zorn lemma**. Its statement is: if every chain in a non-empty partially ordered set has an upper bound, then the partially ordered set has a maximal element.

Zorn's Lemma is equivalent to the **[Axiom of Choice](https://en.wikipedia.org/wiki/Axiom_of_choice)** and the **[Well-ordering theorem](https://en.wikipedia.org/wiki/Well-ordering_theorem)**.

### Directed Sets and Lattices

We know that if a subset of a partially ordered set has a supremum (infimum), it must be unique. However, this does not apply to maximal (minimal) elements. For example: consider the partially ordered set $S=\{\{0\},\{1\},\{2\},\{0,1\},\{0,2\},\{1,2\}\}$ with partial order $\subseteq$. It is easy to see it has $3$ maximal elements and $3$ minimal elements.

We want to add certain conditions to partially ordered sets so that if maximal (minimal) elements exist, they must be unique. This allows us to define the concept of greatest (least) elements.

???+ note "Directed set"
    For a preordered set $S$ with preorder $\preceq$, if $(\forall~a,b\in S)~~(\exists~c\in S)~~a\preceq c\land b\preceq c$, then $\preceq$ is called a **direction** on $S$, and $S$ is called a **directed set** or **filtered set**.
    
    Sometimes such a set $S$ is called an **upward directed set**. **Downward directed sets** can be defined analogously.

Directed sets can also be defined as follows:

???+ note "Equivalent definition of directed sets"
    For a preordered set $S$ with preorder $\preceq$, if every finite subset $T$ of $S$ has an upper bound, then $\preceq$ is called a direction on $S$, and $S$ is called a directed set.

It is easy to see that:

-   If an upward directed set has a maximal element, it must be unique. We call the maximal element of an upward directed set the **greatest element**.
-   If a downward directed set has a minimal element, it must be unique. We call the minimal element of a downward directed set the **least element**.

In a directed partially ordered set, for any elements $a$ and $b$, $\{a,b\}$ has an upper bound. If we replace the upper bound with the supremum, we get the definition of a join semilattice.

For a partially ordered set $S$ with partial order $\preceq$:

???+ note "Join semilattice"
    If for any elements $a,b$ in $S$, $\{a,b\}$ has a supremum $c$, then $S$ is called a **join-semilattice** (or **upper semilattice**), and we call $c$ the **join** of $a$ and $b$, denoted $a\lor b$.

???+ note "Meet semilattice"
    If for any elements $a,b$ in $S$, $\{a,b\}$ has an infimum $c$, then $S$ is called a **meet-semilattice** (or **lower semilattice**), and we call $c$ the **meet** of $a$ and $b$, denoted $a\land b$.

???+ note "Lattice"
    If $S$ is both a join-semilattice and a meet-semilattice, then $S$ is called a **lattice**.

For example, the set $S=\{1,2,3,4,5,6,10,12,15,20,30,60\}$ of positive divisors of $60$ forms a partially ordered set under divisibility. For any positive integers $a,b$, $\operatorname{lcm}(a,b)$ is the join of $a$ and $b$, and $\gcd(a,b)$ is the meet of $a$ and $b$. Thus $S$ is a lattice.

### Duality

In order theory, duality is a very common concept. For example, maximal and minimal elements are dual, upper and lower bounds are dual, supremum and infimum are dual.

For a partially ordered set $P$ with partial order $\preceq$, define its **dual** (or **opposite**) partially ordered set $P^d$ such that: $x \preceq y$ holds in $P$ if and only if $y \preceq x$ holds in $P^d$. The Hasse diagram of $P^d$ can be obtained by reversing the edges of the Hasse diagram of $P$.

## Dilworth's Theorem and Mirsky's Theorem

For a finite partially ordered set $S$ with partial order $\preceq$, we have the following pair of dual theorems:

???+ note "Dilworth's Theorem"
    The width of $S$ (length of the longest antichain) equals the minimum chain cover number.
    
    ??? note "Proof"
        We use mathematical induction. When $|S|\leq 3$, the statement is trivially true.
        
        Assume the statement holds for all partially ordered sets with fewer than $|S|$ elements. Let the width of $S$ be $d$. If all elements in $|S|$ are incomparable, the statement holds trivially. Otherwise, take a chain of length greater than $1$ in $S$, and let its least element be $m$ and greatest element be $M$.
        
        Let $T=S\setminus\{m,M\}$. If the width of $T$ does not exceed $d-1$, then by the induction hypothesis, $T$ can be covered by at most $d-1$ chains. Adding the chain $\{m,M\}$ covers $S$, so the statement holds. Otherwise, the width of $T$ is also $d$. Let $A$ be a longest antichain in $T$.
        
        Consider the following two sets:
        
        $$
        S^+:=\{x\in S:(\exists~a\in A)~~a\preceq x\}
        $$
        
        $$
        S^-:=\{x\in S:(\exists~a\in A)~~x\preceq a\}
        $$
        
        We observe the following properties:
        
        -   $S^+\cup S^-=S$,
        -   $S^+\cap S^-=A$,
        -   $|S^+|<|S|$, $|S^-|<|S|$ (because $m\notin S^+$ and $M\notin S^-$).
        
        Applying the induction hypothesis to both $S^+$ and $S^-$, the minimum chain cover number of these two sets is $d$, and these chains each contain exactly one element $a$ from $A$. Let these chains be $C_a^+$ and $C_a^-$. Then $\{C_a^-\cup\{a\}\cup C_a^+\}_{a\in A}$ is a minimum chain cover of $S$, completing the proof.

???+ note "Mirsky's Theorem"
    The length of the longest chain of $S$ equals the minimum antichain cover number.
    
    ??? note "Proof"
        Let the length of the longest chain of $S$ be $d$. By definition, the minimum antichain cover number is at least $d$.
        
        Let $f(s)$ be the length of the longest chain with $s$ as the minimal element. Note that if $f(s)=f(t)$, then $s$ and $t$ are incomparable. Thus $(\forall~n\in\mathbf{N})~~f^{-1}(\{n\})$ are all antichains, where $f^{-1}(\{n\}):=\{a\in S:f(a)=n\}$ is called a [level set](https://en.wikipedia.org/wiki/Level_set).
        
        Therefore, it follows that $\{f^{-1}(\{i\}):1\leq i\leq d\}$ is an antichain cover, so the minimum antichain cover number is at most $d$.

Dilworth's theorem is equivalent to [Hall's marriage theorem](../graph/graph-matching/graph-match.md#hall-theorem).

We can use Dilworth's theorem to prove the following theorem:

???+ note "Erdős–Szekeres Theorem"
    Any sequence of $rs+1$ real numbers either has a non-decreasing subsequence of length $r+1$, or has a non-increasing subsequence of length $s+1$.
    
    ??? note "Proof"
        Let the sequence length be $n\geq rs+1$. Define the partially ordered set $\{(i,a_i)\}_{i=1}^{n}$ with partial order $\preceq$ defined as:
        
        $$
        (i,a_i)\preceq (j,a_j)\iff (i\leq j\land a_i\leq a_j)
        $$
        
        Suppose the width of this partially ordered set does not exceed $s$. Then by Dilworth's theorem, the partially ordered set can be covered by at most $s$ chains. If none of these chains has length exceeding $r$, the sequence contains at most $rs$ elements, contradicting the condition.

### Example Problems

???+ note "[Luogu P1020 [NOIP1999 Senior Group] Missile Interception](https://www.luogu.com.cn/problem/P1020)"
    A certain country has developed a missile interception system for defending against enemy missile attacks. However, this missile interception system has a flaw: while the first missile can reach any altitude, each subsequent missile cannot be higher than the previous one. One day, radar detects incoming enemy missiles. Since the system is still in the trial phase, there is only one system, so it may not be able to intercept all the missiles.
    
    Given the altitudes of the missiles in the order they arrive, compute the maximum number of missiles this system can intercept, and the minimum number of such missile interception systems needed to intercept all missiles.
    
    For all data, the missile altitudes are positive integers not exceeding $5\times 10^4$.
    
    ??? note "Solution"
        Let there be $n$ missiles, with the $i$-th missile at altitude $h_i$. The set $\{(i,h_i)\}_{i=1}^{n}$ is a partially ordered set with partial order $\preceq$ defined as:
        
        $$
        (i,h_i)\preceq(j,h_j) \iff (i\leq j \land h_i\geq h_j)
        $$
        
        Then by Dilworth's theorem: **the minimum chain cover number of non-increasing subsequences equals the length of the longest non-decreasing subsequence**. Thus this problem can be solved using the $O(n\log n)$ method for the [longest non-decreasing subsequence](../dp/basic.md#algorithm-2).
    
    ??? note "Reference Code"
        ```cpp
        --8<-- "docs/math/code/order-theory/order-theory_1.cpp"
        ```

???+ note "[[TJOI2015] Combinatorics](https://www.luogu.com.cn/problem/P3974)"
    Given an $n$ rows by $m$ columns grid, each cell contains several treasures. Starting from the top-left corner, you can only move right or down. Each time you pass through a cell, you can pick up at most one treasure. How many times must you walk to possibly collect all the treasures?
    
    $1\le n \le 1000$, $1\le m \le 1000$, each cell contains at most $10^6$ treasures.
    
    ??? note "Solution"
        Ignoring the point weights of the grid, it is easy to see that walking on the grid following the given rules is equivalent to walking on a DAG. Thus we can view it as a Hasse diagram to construct a partially ordered set. By Dilworth's theorem: **the minimum chain cover number of a DAG equals the size of the largest vertex independent set**.
        
        Therefore, the problem asks for the sum of weights of a maximum-weight vertex independent set in the given grid.
        
        Let $a_{ij}$ be the weight at point $(i,j)$ in the grid, and $f(i,j)$ be the answer for the subgrid from $(i,j)$ to $(1,m)$. Note that each point is not adjacent to its upper-right diagonal point. The state transition equation is:
        
        $$
        f(i,j)=\max\{f(i-1,j),f(i,j+1),f(i-1,j+1)+a_{ij}\}
        $$
        
        The answer is $f(n,1)$.
    
    ??? note "Reference Code"
        ```cpp
        --8<-- "docs/math/code/order-theory/order-theory_2.cpp"
        ```

### Practice Problems

-   [[CTSC2008] Sacrifice](https://www.luogu.com.cn/problem/P4298)
-   [CodeForces 590-E Birthday](https://codeforces.com/problemset/problem/590-E)

## Applications in C++

See also: [Sorting-related STL - Algorithm Basics](../basic/stl-sort.md).

The C++ STL has [applications of order theory](https://en.cppreference.com/w/cpp/named_req/Compare#Standard_library) in algorithms and data structures that require comparisons. We often need to define custom comparators in C++. The STL [requires](https://en.cppreference.com/w/cpp/named_req/Compare) them to be **strict weak orders**. Let $<$ be the custom comparator. Then we can define:

-   $x>y$ as $y<x$;
-   $x \leq y$ as $y \nless x$;
-   $x \geq y$ as $x \nless y$;
-   $x=y$ as $x \nless y\land y \nless x$.

## References and Further Reading

1.  [Order theory - From Academic Kids](https://academickids.com/encyclopedia/index.php/Order_theory)
2.  [Binary Relation - Wikipedia](https://en.wikipedia.org/wiki/Binary_relation)
3.  [Order Theory - Wikipedia](https://en.wikipedia.org/wiki/Order_theory)
4.  [Hasse diagram - Wikipedia](https://en.wikipedia.org/wiki/Hasse_diagram)
5.  [Directed set - Wikipedia](https://en.wikipedia.org/wiki/Directed_set)
6.  [Order Theory, Lecture Notes by Mark Dean for Decision Theory](http://www.columbia.edu/~md3405/DT_Order_15.pdf)
7.  Lu Kaicheng, Lu Huaming, [*Combinatorics* (3rd Edition)](http://www.tup.tsinghua.edu.cn/bookscenter/book_00458101.html), 2006
8.  [List of Order Theory Topics - Wikipedia](https://en.wikipedia.org/wiki/List_of_order_theory_topics)
9.  [A Discussion on Adjacent Exchange Sort and Its Caveats by ouuan](https://ouuan.github.io/post/%E6%B5%85%E8%B0%88%E9%82%BB%E9%A1%B9%E4%BA%A4%E6%8D%A2%E6%8E%92%E5%BA%8F%E7%9A%84%E5%BA%94%E7%94%A8%E4%BB%A5%E5%8F%8A%E9%9C%80%E8%A6%81%E6%B3%A8%E6%84%8F%E7%9A%84%E9%97%AE%E9%A2%98/)
10. [One thing you should know about comparators—Strict Weak Ordering](https://codeforces.com/blog/entry/72525)
11. [Dilworth's theorem - Wikipedia](https://en.wikipedia.org/wiki/Dilworth%27s_theorem)
12. [Dilworth's Theorem | Brilliant Math & Science Wiki](https://brilliant.org/wiki/dilworths-theorem/)
13. [Hall's marriage theorem - Wikipedia](https://en.wikipedia.org/wiki/Hall's_marriage_theorem)
14. [Hall's Marriage Theorem | Brilliant Math & Science Wiki](https://brilliant.org/wiki/hall-marriage-theorem/)
15. [Dilworth Learning Notes - Selfish](https://www.luogu.com.cn/blog/Rolling-Code/dilworth)