In mathematical logic, Boolean algebra is a branch of algebra. In elementary algebra, the values of variables are numbers, and the main operations studied are addition, multiplication, exponentiation, and the inverse operations of these three. In Boolean algebra, the values of variables are only **true** and **false** (usually denoted as $1$ and $0$), and the main operations studied are conjunction (AND, $\land$), disjunction (OR, $\lor$), and negation (NOT, $\lnot$). Just as elementary algebra is a formalism for describing numerical operations, Boolean algebra is a formalism for describing logical operations.

## Boolean Functions

???+ abstract "Definition"
    A **boolean function** is a function of the form $f:\mathbf{B}^k\to \mathbf{B}$, where $\mathbf{B}=\{0,1\}$ is the **boolean domain**, and the non-negative integer $k$ is the **arity** of the boolean function. Boolean functions with $k=1$ are unary functions, and so on. When $k=0$, we consider the function as a constant in $\mathbf{B}$.

    We generally only study unary and binary boolean functions. Unless otherwise specified, boolean functions below are limited to the unary and binary cases.

    In addition to the general expression of functions, we can also represent boolean functions using **truth tables**, **logic gates**, and [Venn diagrams](https://en.wikipedia.org/wiki/Venn_diagram).

???+ abstract "Truth Table"
    For a boolean function, we enumerate all possible inputs and list the inputs along with their corresponding outputs in a table, called a truth table.

    An $n$-ary boolean function can also be represented by a **propositional formula** (propositional formula) containing $n$ variables. Propositional formulas $p$ and $q$ are **logically equivalent** if and only if they describe the same boolean function, denoted $p\iff q$.

    Below are some common boolean functions, which we also collectively refer to as **logical connectives** or **logical operators**:

| Name (Mathematical Logic)                                     | Other Names                  | Notation                             |
| ------------------------------------------------------------ | -------------------------- | ----------------------------------- |
| Truth (tautology)                                            |                            | $\top$                              |
| Falsity (contradiction)                                     |                            | $\bot$                              |
| Proposition                                                 | Identity                    | $A$                                 |
| Negation                                                    | NOT                        | $\lnot A$                           |
| Conjunction                                                 | AND                        | $A \land B$                        |
| Disjunction                                                 | OR                         | $A \lor B$                         |
| Non-conjunction                                             | NAND, Sheffer stroke       | $A \bar{\land} B$、$A\uparrow B$   |
| Non-disjunction                                             | NOR                        | $A \bar{\lor} B$、$A\downarrow B$  |
|                                                            | Exclusive-OR, XOR          | $A \oplus B$                       |
|                                                            | Exclusive-NOR              | $A \odot B$                        |
| Material implication[^note1]                                |                            | $A \to B$                          |
| Material nonimplication[^note1]                              |                            | $A \nrightarrow B$                  |
| Converse implication[^note1]                                 |                            | $A \gets B$                        |
| Converse nonimplication[^note1]                              |                            | $A \nleftarrow B$                 |
| Biconditional, Equivalence[^note1][^note2]                  |                            | $A \leftrightarrow B$               |
| Non-equivalence[^note1][^note3]                            |                            | $A \nleftrightarrow B$             |

Corresponding truth table (From [Wikipedia](https://commons.wikimedia.org/wiki/File:Logical_connectives_table.svg)):

![](./images/logical-connectives-table.svg)

Corresponding Venn diagram and [Hasse diagram](./order-theory.md#hasse-diagram) (with set inclusion $\subseteq$ as the partial order, From [Wikipedia](https://en.wikipedia.org/wiki/File:Logical_connectives_Hasse_diagram.svg)):

![](./images/logical-connectives-hasse-diagram.svg)

Since an $n$-ary boolean function has $2^n$ possible inputs, there are $2\uparrow (2\uparrow n)$ $n$-ary boolean functions, where $\uparrow$ is Knuth's up-arrow notation.

We call a combination of logical operators a **logical expression**.

If we view $\mathbf{B}$ as a [residue class](./number-theory/basic.md#congruence-classes-and-residue-systems) modulo $2$, then XOR is equivalent to addition modulo $2$, and AND is equivalent to multiplication modulo $2$, so we sometimes use $\mathbf{Z}_2$ to denote the boolean domain.

### Precedence

Unary logical operators have higher precedence than binary logical operators, i.e., the precedence of $\lnot$ is higher than that of $\land$, $\lor$, $\oplus$, etc.

There are various conventions regarding precedence among binary logical operators. Some sources consider $\land$, $\lor$, $\oplus$ to have higher precedence than $\to$, $\gets$, $\leftrightarrow$, while others hold the opposite view. Therefore, when using them, it is recommended to add extra parentheses to clarify the order.

For the precedence rules in C++, see [C++ Operator Precedence](./../lang/op.md#c-operator-precedence).

### Self-sufficient Operators and Functionally Complete Sets

In fact, we can express all other logical operators using only NAND or only NOR, and CPUs are built based on this principle. However, since the four logical operators **AND, OR, NOT, XOR** have better properties, we generally use only these four functions when studying Boolean algebra.

??? example "How to express all other logical operators using NAND or NOR"
    We have:
    
    -   $\lnot p=p\bar{\land} p=p\bar{\lor} p$,
    -   $p\land q=(p\bar{\land}q)\bar{\land}(p\bar{\land}q)=(p\bar{\lor}p)\bar{\lor}(q\bar{\lor}q)$,
    -   $p\lor q=(p\bar{\land}p)\bar{\land}(q\bar{\land}q)=(p\bar{\lor}q)\bar{\lor}(p\bar{\lor}q)$,
    -   $p\to q=p\bar{\land} (q\bar{\land} q)=((p\bar{\lor}p)\bar{\lor}q)\bar{\lor}((p\bar{\lor}p)\bar{\lor}q)$.
    
    Additionally:
    
    -   $p=\lnot\lnot p$,
    -   $p\nleftrightarrow q=p\oplus q=(p\lor q)\land\lnot (p\land q)$,
    -   $p\leftrightarrow q=p\odot q=\lnot(p\oplus q)$,
    -   $p\nrightarrow q=\lnot(p\to q)$,
    -   $p\gets q=q\to p$,
    -   $p\nleftarrow q=\lnot(p\gets q)$.

Can we describe all logical operators using a specified set of logical operators? This leads to the definition of functionally complete sets.

???+ abstract "Definition"
    For a given set of logical operators, if all logical operators can be described using only the functions from this set, then the set is called a **functionally complete operator set**. In particular, if only one logical operator is sufficient to describe all logical operators, then that operator is called a **sole sufficient operator** or **Sheffer function**.
    
    If any element can be removed from a functionally complete set and the remaining set can no longer describe all logical operators, then the set is called a **minimal functionally complete operator set**.

    It can be proven that among logical operators, only $\bar{\land}$ and $\bar{\lor}$ are sole sufficient operators.

    Below are common minimal functionally complete operator sets[^vaughan1942complete]:

    -   $\{\bar{\land}\}$，$\{\bar{\lor}\}$，
    -   $\{\land,\lnot\}$，$\{\lor,\lnot\}$，$\{\gets,\lnot\}$，$\{\to,\lnot\}$，$\{\nleftarrow,\lnot\}$，$\{\nrightarrow,\lnot\}$，
    -   $\{\gets,\bot\}$，$\{\to,\bot\}$，$\{\nleftarrow,\top\}$，$\{\nrightarrow,\top\}$，
    -   $\{\gets,\nleftarrow\}$，$\{\to,\nleftarrow\}$，$\{\gets,\nrightarrow\}$，$\{\to,\nrightarrow\}$，
    -   $\{\gets,\nleftrightarrow\}$，$\{\to,\nleftrightarrow\}$，$\{\nleftarrow,\leftrightarrow\}$，$\{\nrightarrow,\leftrightarrow\}$，
    -   $\{\lor,\leftrightarrow,\bot\}$，$\{\lor,\leftrightarrow,\nleftrightarrow\}$，$\{\lor,\nleftrightarrow,\top\}$，
    -   $\{\land,\leftrightarrow,\bot\}$，$\{\land,\leftrightarrow,\nleftrightarrow\}$，$\{\land,\nleftrightarrow,\top\}$．

### Properties

First, the properties related to algebraic structure:

-   Both AND and OR form [commutative monoids](./algebra/basic.md#groups) over $\mathbf{B}$. That is, both AND and OR are commutative, associative, and have identity elements ($x\land 1=x\lor 0=x$).
-   Both XOR and XNOR form [groups](./algebra/basic.md#groups) over $\mathbf{B}$. That is, both XOR and XNOR are commutative, associative, have identity elements ($x\oplus 0=x\odot 1=x$), and have inverses ($x\oplus x=0$, $x\odot x=1$).
-   NAND and NOR do not satisfy the associative law, so they do not form semigroups.

For $\land$ and $\lor$, we have:

-   Distributive law:
    -   $a\land(b\diamond c)=(a\land b)\diamond (a\land c)$, where $\diamond$ can be $\land$, $\lor$, or $\oplus$,
    -   $a\lor(b\diamond c)=(a\lor b)\diamond (a\lor c)$, where $\diamond$ can be $\land$, $\lor$, or $\odot$.
-   **Idempotent** law: $x\land x=x$, $x\lor x=x$.
-   Monotonicity: $a\to b\iff(a\land c)\to(b\land c)$, $a\to b\iff(a\lor c)\to(b\lor c)$.
-   **Absorption** law: $x\land(x\lor y)=x\lor(x\land y)=x$.
-   Relationship with $\to$:
    -   $a \lor b \iff (\lnot a \to b) \land (\lnot b \to a)$,
    -   $a \land b \iff \lnot((a \to \lnot b) \lor (b \to \lnot a))$.

???+ abstract "Monotonicity of Boolean Functions"
    For a boolean function $f(x_1,\dots,x_n)$ and two elements $(a_1,\dots,a_n),(b_1,\dots,b_n)$ in $\mathbf{B}^n$, if $f(a_1,\dots,a_n)\leq f(b_1,\dots,b_n)$ always holds whenever $a_i\leq b_i,~~\forall i=1,\dots,n$, then the boolean function is called monotonic.

We also have the following properties:

-   **Law of excluded middle**: $p\lor\lnot p$ is always true.
-   $\lnot p\iff p\to\bot$.
-   Double negation / **involution** law for $\lnot$: $\lnot\lnot x=x$.
-   Involution laws for $\oplus$ and $\odot$: $x\oplus y\oplus y=x$, $x\odot y\odot y=x$.
-   De Morgan's laws: $\lnot(p\land q)=\lnot p\lor \lnot q$, $\lnot(p\lor q)=\lnot p\land \lnot q$.

## Normal Forms of Logical Expressions

Based on the properties above, we can perform certain equivalence transformations on logical expressions to make them conform to specific normal forms. This can be used in automated theorem proving. Common normal forms include **conjunctive normal form** (CNF), **disjunctive normal form** (DNF), and **algebraic normal form** (ANF).

???+ abstract "Conjunctive Normal Form and Disjunctive Normal Form"
    We make the following recursive definitions:
    
    1.  **Literal**: For a variable $x$, both $x$ and $\lnot x$ are literals.
    2.  Clause:
        -   A literal is a clause,
        -   If $A$ is a literal and $B$ is a clause, then $A\lor B$ is a clause.
    3.  Conjunctive normal form:
        -   If $A$ is a clause, then $(A)$ is in conjunctive normal form,
        -   If $A$ is a clause and $B$ is in conjunctive normal form, then $(A)\land B$ is in conjunctive normal form.
    
    Similarly, swapping $\land$ and $\lor$ in the above definitions gives the definition of disjunctive normal form.

For example, the following logical expressions are all in disjunctive normal form:

-   $(A\land\lnot B)\lor(C\land D\land\lnot E)$,
-   $(A\land B)\lor (C)$,
-   $(A\land B)$,
-   $(A)$.

The following logical expressions are all in conjunctive normal form:

-   $(\lnot A\lor\lnot B\lor C)\land(\lor D\lor\lnot E)$,
-   $(A\lor B)\land (C)$,
-   $(A\lor B)$,
-   $(A)$.

The following logical expressions are neither in conjunctive normal form nor disjunctive normal form:

-   $\lnot(A\land B)$,
-   $A\land (B\lor (C\land D))$.

We can transform any logical expression containing only $\lnot$, $\land$, $\lor$ operations into DNF using the following steps:

$$
\begin{array}{rcccl}
    \lnot\lnot x &&\mapsto&& x,\\
    \lnot(x\lor y) &&\mapsto&& \lnot x\land \lnot y,\\
    \lnot(x\land y) &&\mapsto&& \lnot x\lor \lnot y,\\
    x\land(y\lor z) &&\mapsto&& (x\land y)\lor (x\land z),\\
    (x\lor y)\land z &&\mapsto&& (x\land z)\lor (y\land z).
\end{array}
$$

To get the CNF of an expression $X$, simply get the DNF of $\lnot X$, then negate it and apply De Morgan's law.

???+ abstract "Algebraic Normal Form"
    First, we define terms recursively as follows:
    
    -   A variable $x$ is a term,
    -   If $A$ is a term and $x$ is a variable, then $x\land A$ is a term.
    
    A logical expression is in algebraic normal form if it satisfies one of the following three forms:
    
    1.  $1$ or $0$,
    2.  XOR of several non-equivalent terms, such as $a\oplus b\oplus(a\land b)\oplus(a\land b\land c)$,
    3.  XOR of several non-equivalent terms and a unique $1$, such as $1\oplus a\oplus b\oplus(a\land b)\oplus(a\land b\land c)$.

    Note that algebraic normal forms correspond one-to-one with polynomials over $\mathbf{Z}_2$, so algebraic normal forms are also called **Zhegalkin polynomials** (Zhegalkin polynomial).

    We can transform any logical expression containing only $\lnot$, $\land$, $\lor$, $\oplus$ operations into ANF using the following steps:

    1.  $\oplus$: Expand directly, e.g., $(1\oplus x)\oplus(1\oplus x\oplus y)=1\oplus x\oplus 1\oplus x\oplus y=y$,
    2.  $\land$: Expand using the distributive law, e.g., $x\land(1\oplus x\oplus y)=(x\land 1)\oplus (x\land x)\oplus (x\land y)=x\oplus (x\land y)$,
    3.  $\lnot$: Replace $\lnot x$ with $1\oplus x$, e.g., $\lnot(1\oplus x\oplus y)=1\oplus 1\oplus x\oplus y=x\oplus y$,
    4.  $\lor$: Replace $x\lor y$ with $1\oplus((1\oplus x)\land(1\oplus y))$ or $x\oplus y\oplus (x\land y)$, e.g., $(1\oplus x)\lor(1\oplus x\oplus y)=1\oplus((1\oplus 1\oplus x)\land(1\oplus 1\oplus x\oplus y))=1\oplus x\oplus(x\land y)$.

## References and Notes

1.  [Boolean algebra - Wikipedia](https://en.wikipedia.org/wiki/Boolean_algebra)
2.  [Boolean function - Wikipedia](https://en.wikipedia.org/wiki/Boolean_function)
3.  [Logical connective - Wikipedia](https://en.wikipedia.org/wiki/Logical_connective)
4.  [Disjunctive normal form - Wikipedia](https://en.wikipedia.org/wiki/Disjunctive_normal_form)
5.  [Zhegalkin polynomial - Wikipedia](https://en.wikipedia.org/wiki/Zhegalkin_polynomial)

[^note1]: When used in propositional reasoning, double horizontal arrows should be used, such as $A\implies B$, $A\impliedby B$, $A\iff B$, etc.

[^note2]: Equivalent to XNOR.

[^note3]: Equivalent to XOR.

[^vaughan1942complete]: Vaughan, H. E. (1942). Complete sets of logical functions. *Transactions of the American Mathematical Society 51*: 117-32.
