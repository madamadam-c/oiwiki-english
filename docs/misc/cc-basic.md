This section will introduce basic computing theory knowledge. This part of the content is not very useful in OI (but it is still slightly useful: if you encounter an NP-hard problem, you can think that it does not have a solution with polynomial complexity), and can be learned as an interest, or to prepare for future learning.

Many conclusions in this article are without proof. If you are interested, you can check the relevant proofs by yourself.

Prerequisite knowledge: [Time complexity](../basic/complexity.md).

## question

### language

An **alphabet** is a non-empty finite set whose elements are called **symbols**.

Let $\Sigma^\ast$ represent a string formed by concatenating a non-negative integer number of characters in $\Sigma$. A **language (language)** on the alphabet $\Sigma$ is a subset of $\Sigma^\ast$.

It should be noted that "language" here is an abstract concept. In the usual sense, a string is a language, and all directed acyclic graphs can also be a language (01 A bijection can be established between a string and a directed graph, and there is no need to understand the specific method).

Since any language can be converted into the form of 01 string, $\Sigma=\{0, 1\}$.

### Determine the problem

The decision question is a question that can only be answered with YES/NO. It is essentially a question of determining whether a string belongs to a language, that is: $f:\Sigma^\ast\rightarrow\{0, 1\}, f(x)=1\iff x\in L$ is a decision question about the alphabet $\Sigma$ and the language $L$. For example, "determining whether a graph is a directed acyclic graph" is a determination problem.

Decision problems are often the object of computational theory research due to their simplicity. Unless otherwise stated in this article, "problem" refers to "decision problem". Of course, sometimes some propositions can be simply extended to other problems.

A language can also refer to the decision problem of "determining whether a string belongs to this language". Therefore, "language" and "problem" can be regarded as synonyms.

### functional issues

The answer to functional questions is not just YES/NO, it can be a number or something else. For example, "finding the sum of two numbers" is a functional problem.

Any functional problem can be transformed into a decision problem. For example, "find the sum of two numbers" can be transformed into "determine whether the sum of two numbers is equal to a third number."

The decision problem can also be transformed into a functional problem: find the indicator function of this decision problem, which is $f$ in the definition of the decision problem above.

## Turing machine

### Deterministic Turing Machine

Without explanation, "Turing machine" often refers to "deterministic Turing machine", which is also the case in this article.

There are many different definitions of Turing machines. Here we choose one of them. Turing machines under other definitions are often equivalent to the computing power of Turing machines defined below.

A Turing machine is a machine that operates on a paper tape that can be infinitely extended in both directions and is divided into a number of grids. It has an internal state and a magnetic needle that can be modified and moved on the paper tape.

Formally, a Turing machine is a seven-tuple $M=\langle Q,\Gamma,b,\Sigma,\delta,q_0,F\rangle$, where:

-   $Q$ is a finite non-empty **state set**;
-   $\Gamma$ is a finite non-empty **tape alphabet**;
-   $b\in\Gamma$ is the **null character**, which is the only character that can appear infinitely frequently on the tape during calculations;
-   $\Sigma\subseteq(\Gamma\setminus\{b\})$ is the **input symbol set**, which are characters that can appear on the initial tape (i.e. input);
-   $q_0\in Q$ is **initial state**;
-   $F\subseteq Q$ is the **accepting state**. If a Turing machine stops in a certain accepting state, it is said that the content on the initial tape is **accepted** by the Turing machine.
-   $\delta :(Q\setminus F)\times \Gamma \not \to Q\times \Gamma \times \{L,R\}$ is a partial function called a **transfer function** (that is, a function defined only for a subset of the domain). If $\delta$ is not defined in the current state, the Turing machine stops.

Starting from the initial state and the starting point of the paper tape, the Turing machine operates each time based on the current internal state $x$ and the character $y$ in the cell on the tape pointed by the current magnetic needle: if $\delta(x, y)$ is not defined, it will stop, otherwise if $\delta(x, y)=(a, b, c)$, the internal state will be modified to $a$, and the character in the grid pointed by the magnetic needle will be modified to $b$. If $c$ is If it is $L$, it will move one space to the left, and if it is $R$, it will move one space to the right.

In fact, it is not necessary to know the details of the working of Turing machines, just establish an intuitive understanding.

The output of Turing machine $M$ under input $x$ is denoted as $M(x)$ ($M(x)=1$ if and only if $M$ accepts $x$, $M(x)=0$ if and only if $M$ halts in finite steps under input $x$ and $M$ does not accept $x$), you can also include multiple parameters in brackets, separated by commas. During specific implementation, you can add an element to the alphabet to represent commas to separate each parameter.

The time complexity difference between a Turing machine and a von Neumann computer in solving problems is within the polynomial level, so the Turing machine can be used as a computing model when studying complexity classes.

### non-deterministic Turing machine

The non-deterministic Turing machine is a type of Turing machine. The difference between it and the deterministic Turing machine is that each step of the deterministic Turing machine can only transfer to one state, while the non-deterministic Turing machine can transfer to multiple states "simultaneously", thereby computing in multiple "branches" in parallel. Once one of these "branches" stops in the accepting state, the non-deterministic Turing machine accepts this input.

In fact, any deterministic Turing machine can simulate the polynomial-time behavior of a non-deterministic Turing machine in exponential time using a method similar to iterative deepening search.

In real life, a deterministic Turing machine is equivalent to a single-core processor and only supports serial processing; a non-deterministic Turing machine is equivalent to an ideal multi-core processor and supports unlimited parallel processing.

### Multi-band Turing machine

The standard Turing machine can only operate on one paper tape, but for convenience, multi-tape Turing machines are studied in this article. For a $k$ Turing machine, one of the paper tapes is a read-only input tape, while the remaining $k-1$ paper tapes can be read and written, and one of the $k-1$ paper tapes is used as output.

The number of tapes in a multi-tape Turing machine must be limited.

For a multi-tape Turing machine, the space it uses is the number of cells that the head has visited on other tapes except the input tape.

### Coding of Turing Machine

Turing machines can be encoded by natural numbers, that is, there is a surjective function $f:\mathbb{N}\to\mathbb{M}$, so that each natural number corresponds to a Turing machine, and each Turing machine has countless codes. Therefore, a set of several Turing machines can be a language.

The Turing machine encoded by the natural number $\alpha$ is $M_{\alpha}$.

### universal turing machine

There exists a Turing machine $\mathcal U$ that satisfies:

1.  If $M_{\alpha}$ stops within a limited time under input $x$, then $\mathcal{U}(x, \alpha)=M_{\alpha}(x)$, otherwise $\mathcal{U}(x, \alpha)$ will not stop within a limited time;
2.  If for any $x\in\{0, 1\}^\ast$, $M_\alpha$ stops within $T(|x|)$ time under input $x$, then for any $x\in\{0, 1\}^\ast$, $\mathcal{U}(x, \alpha)$ stops within $O(T(|x|)\log T(|x|))$ time.

That is: there is a universal Turing machine, which can simulate any Turing machine, and the time it takes will only be slower than the logarithm of the running time of the simulated Turing machine.

## computability

### uncomputable problem

For a decision problem, if there is a Turing machine that always stops within a finite step and can make correct decisions, then the problem is a **Turing computable** problem, otherwise the problem is a **Turing uncomputable** problem.

Since Turing machines can be encoded by natural numbers, the number of Turing machines is countably infinite, and the number of languages ​​(i.e., sets of binary strings) is uncountable and infinite. Each Turing machine can determine at most one language, so there must be a problem that Turing is not computable.

### Downtime issues

The halting problem is a classic Turing uncomputable problem: given $\alpha$ and $x$, determine whether $M_{\alpha}$ will halt within a finite step when the input is $x$.

??? note "Halting problem is proof that Turing is not computable"
    Define function $\mathsf{UC}:\{0,1\}^\ast\to\{0,1\}$ as:
    
    $$
    \mathsf{UC}(\alpha)=\begin{cases}0&M_\alpha(\alpha)=1\\1&\text{otherwise}\end{cases}
    $$
    
    We first prove that the $\mathsf{UC}$ function is Turing uncomputable:
    
    Suppose there is a Turing machine $M_{\beta}$ that can calculate $\mathsf{UC}$, then according to the definition of $\mathsf{UC}$ we can get $\mathsf{UC}(\beta)=1\iff M_\beta(\beta)\neq 1$, and according to $M_{\beta}$ we can calculate $\mathsf{UC}$ we can get $M_{\beta}(\beta)=\mathsf{UC}(\beta)$, which creates a contradiction, so the assumption is not true, there is no Turing machine that can calculate $\mathsf{UC}$.
    
    Let $M_{\mathsf{HALT}}$ be a Turing machine that can solve the halting problem, and the value of $M_{\mathsf{HALT}}(x,\alpha)$ is the solution to the decision problem whether $M_\alpha$ will halt within a finite step when the input is $x$. Then we can construct a Turing machine $M_{\mathsf{UC}}$ that can calculate the $\mathsf{UC}$ function:
    
    $M_\mathsf{UC}$ first calls $M_\mathsf{HALT}(α,α)$, if it outputs $0$, then $M_\mathsf{UC}(α)=1$; otherwise, $M_\mathsf{UC}$ uses a universal Turing machine to simulate and calculate the answer.
    
    Since the $\mathsf{UC}$ function is Turing-uncomputable, $M_\mathsf{HALT}$ does not exist, which means that the halting problem is Turing-uncomputable.

## Church-Turing Thesis

The Church-Turing thesis states that if a type of problem has an efficient method to solve it, then this type of problem can be solved by a certain Turing machine.

Among them, "effective methods" need to meet:

1.  Contains a limited number of clear instructions;
2.  When used to solve one of these problems, the method needs to end in a finite number of steps and get the correct answer.

This thesis has not been proven, but it is a basic axiom of computational theory.

## Complexity class

There are many complexity classes, and this article will only introduce a small part of the more common ones.

### R and RE

For language $L$ and Turing machine $M$, if $M$ can halt in finite steps under any input, and $M(x)=1\iff x\in L$, then $M$ is said to be able to **determine** $L$.

For the language $L$ and the Turing machine $M$, if for any input belonging to $L$, $M$ stops within finite steps, and $M(x)=1\iff x\in L$, then it is said that $M$ can **recognize** $L$.

The complexity class $\mathsf R$ represents the set of languages ​​that can be judged by a certain Turing machine, that is, all Turing-computable languages.

The complexity class $\mathsf{RE}$ represents the set of languages ​​that can be recognized by a certain Turing machine. $\mathsf{RE}$ is also called a recursively enumerable language.

From the definition we can get $\mathsf{R}\subseteq\mathsf{RE}$.

### DTIME

If there is a deterministic Turing machine that can determine a language, and for any input $x$, this Turing machine can stop in $O(f(|x|))$ time, then this language belongs to the $\mathsf{DTIME}(f(n))$ class.

### P

The complexity class $\mathsf P$ represents decision problems that can be solved by a deterministic Turing machine in polynomial time, namely:

$$
\mathsf{P}=\bigcup\limits_{k\in\mathbb{N}}\mathsf{DTIME}(n^k)
$$

The decision versions of linear programming, calculating the greatest common divisor, and finding the maximum matching of a graph are all $\mathsf P$ problems.

### EXPTIME

The complexity class $\mathsf{EXPTIME}$ represents a decision problem that can be solved by a deterministic Turing machine in exponential time, that is:

$$
\mathsf{EXPTIME}=\bigcup\limits_{k\in\mathbb{N}}\mathsf{DTIME}(2^{n^k})
$$

A weakened version of the halting problem - given the encoding of a Turing machine and a positive integer $k$, determining whether the Turing machine halts within $k$ steps is a $\mathsf{EXPTIME}$ problem. Because the solution of this problem takes $O(k)$ time, and the number $k$ can be encoded as a binary string of length $O(\log k)$.

### NTIME

If there is a non-deterministic Turing machine that can determine a language, and for any input $x$, this Turing machine can stop in $O(f(|x|))$ time, then this language belongs to the $\mathsf{NTIME}(f(n))$ class.

### NP

The complexity class $\mathsf{NP}$ represents decision problems that can be solved by a non-deterministic Turing machine in polynomial time, namely:

$$
\mathsf{NP}=\bigcup\limits_{k\in\mathbb{N}}\mathsf{NTIME}(n^k)
$$

All problems of type $\mathsf P$ are problems of type $\mathsf{NP}$. For more $\mathsf{NP}$ problems, please see the NPC problem and NP-intermediate problem below.

#### NP-hard

If all problems of class $\mathsf{NP}$ can be reduced to problem $H$ in polynomial time, then problem $H$ is NP-hard.

In other words, if the NP-hard problem $H$ can be solved in one unit of time, then all $\mathsf{NP}$ problems can be solved in polynomial unit time.

#### NP-complete

If a problem is both a $\mathsf{NP}$ problem and NP-hard, then the problem is NP-complete, or it is an NPC problem.

Some classic NPC problems: the decision version of the traveling salesman problem, the decision version of the maximum independent set problem, the decision version of the minimum point covering problem, the decision version of the longest path problem, the decision version of the 0-1 integer programming problem, the set covering problem, the graph coloring problem, the knapsack problem, the three-dimensional matching problem, the decision version of the maximum cut problem.

The functional version of the NPC problem is often NP-hard. For example: "Determine whether there is a clique of size $k$ in a graph" is both a $\mathsf{NP}$ problem and NP-hard, so it is an NPC problem, and its functional version "Find the largest clique in a graph" is not an NPC problem, but this functional version is still NP-hard.

Similarly, other complexity classes will also have "XX-complete", for example, all $\mathsf{EXPTIME}$ class problems can be reduced to EXPTIME-complete problems in polynomial time.

#### co-NP

A problem is a problem of type $\mathsf{co-NP}$ if and only if its complement is a problem of type $\mathsf{NP}$. If you understand "problem" as "language", and "language" is a subset of $\Sigma^\ast$, you can understand the "complement".

For example: "Given the $n$ subset, determine whether $k$ can be selected from it to cover the entire set" is an NPC problem, and its complement "Given the $n$ subset, determine whether any $k$ selected from it cannot cover the entire set" is a $\mathsf{co-NP}$ problem. If the answer to the first question is "yes", then it is equivalent to finding a set of counterexamples to the second question, so the answer to the second question is "no".

#### NP-intermediate

If a problem is a $\mathsf{NP}$ type problem, but it is neither a $\mathsf{P}$ type problem nor an NPC problem, it is called an NP-intermediate problem.

As far as people's current understanding is concerned, graph isomorphism problems, discrete logarithm problems and factorization problems may be NP-intermediate.

Ladner's theorem states that if $\mathsf{P}\ne\mathsf{NP}$, then there must be a problem that is NP-intermediate.

### NEXPTIME

The complexity class $\mathsf{NEXPTIME}$ represents a decision problem that can be solved by a non-deterministic Turing machine in exponential time, that is:

$$
\mathsf{NEXPTIME}=\bigcup\limits_{k\in\mathbb{N}}\mathsf{NTIME}(2^{n^k})
$$

### #P

The $\mathsf{\#P}$ type problem is not a decision problem, but a counting problem about the $\mathsf{NP}$ type problem: counting the number of solutions to a $\mathsf{NP}$ type problem is a $\mathsf{\#P}$ type problem. In other words, counting how many branches a string is accepted in a nondeterministic Turing machine that always halts in polynomial time is a $\mathsf{\#P}$ problem.

Finding the number of matches or perfect matches for an ordinary graph or a bipartite graph is #P complete, and the corresponding determination problem is "determine whether there is a (perfect) match in a graph".

### DSPACE

If there is a deterministic Turing machine that can determine a language in the space of $O(f(|x|))$ when the input is $x$, then this language belongs to the $\mathsf{DSPACE}(f(n))$ class.

-   $\mathsf{REG}=\mathsf{DSPACE}(O(1))$ is a regular language, which is a language that an automaton can determine.

-   $\mathsf{L}=\mathsf{DSPACE}(O(\log n))$, it should be noted that the space used by the Turing machine does not include the space occupied by the input.

-   $\mathsf{PSPACE}=\bigcup\limits_{k\in\mathbb N}\mathsf{DSPACE}(n^k)$

-   $\mathsf{EXPSPACE}=\bigcup\limits_{k\in\mathbb N}\mathsf{DSPACE}(2^{n^k})$

### NSPACE

If there is a non-deterministic Turing machine that can determine a language in the space of $O(f(|x|))$ when the input is $x$, then this language belongs to the $\mathsf{NSPACE}(f(n))$ class.

-   $\mathsf{REG}=\mathsf{DSPACE}(O(1))=\mathsf{NSPACE}(O(1))$

-   $\mathsf{NL}=\mathsf{NSPACE}(O(\log n))$

-   $\mathsf{CSL}=\mathsf{NSPACE}(O(n))$, context-sensitive language.

-   $\mathsf{PSPACE}=\mathsf{NPSPACE}=\bigcup\limits_{k\in\mathbb N}\mathsf{NSPACE}(n^k)$

-   $\mathsf{EXPSPACE}=\mathsf{NEXPSPACE}=\bigcup\limits_{k\in\mathbb N}\mathsf{NSPACE}(2^{n^k})$

## polynomial time

Simply put, if there is a positive number $k$ such that the time complexity of an algorithm is $O(n^k)$ (note, not $\Theta(n^k)$), where $n$ is the problem size (length of input), then the algorithm is said to be **polynomial time**. If a problem can be solved by a polynomial-time algorithm (on a deterministic Turing machine), then the problem belongs to complexity class $\mathsf{P}$.

Polynomial time can be divided into strong polynomial time and weak polynomial time. In addition, there is pseudo-polynomial time.

### Strongly polynomial time Strongly polynomial time

We first define a calculation model, called an arithmetic model. In the arithmetic model, arithmetic operations between numbers (addition, subtraction, multiplication, division, comparison of sizes) can be completed within unit time (that is, $O(1)$ time, regardless of the size of the numbers).

An algorithm is **strongly polynomial time** if its operands under the arithmetic model are polynomials in the number of digits in the input, and its space complexity is polynomial in the size of the input (not the number of digits). Since arithmetic operations can be completed in polynomial time in the input size (i.e. the logarithm of the number size) under the general computing model, strong polynomial time algorithms must be polynomial time.

Generally speaking, the time complexity of a strong polynomial-time algorithm has nothing to do with the range.

### Weakly polynomial time Weakly polynomial time

If an algorithm is polynomial time but not strongly polynomial time, then it is **weakly polynomial time**.

For example, the Euclidean algorithm for calculating the greatest common divisor has a time complexity of $O(\log a + \log b)$ ($a$ and $b$ are the sizes of the input numbers), which is weak polynomial time.

### Pseudo-polynomial time

If the time of an algorithm is a polynomial in the range, it is said to be **pseudopolynomial time**. Pseudo-polynomial time algorithms may or may not be polynomial time. They may not be polynomial time because representing a positive integer of size $n$ generally only requires $O(\log n)$ binary bits, so polynomial-time algorithms on the range often take exponential time on the input length. Although pseudopolynomial time may also be polynomial time by definition, when we say that an algorithm is pseudopolynomial time, we generally mean that the algorithm is not polynomial time.

For example, the knapsack problem is an NP-hard problem, but it has a pseudopolynomial-time solution based on dynamic programming.

If an NPC/NP-hard problem has a pseudopolynomial-time solution, the problem is said to be a **weak NPC**/**weak NP-hard** problem. If an NPC/NP-hard problem has no pseudo-polynomial time solution under the premise $\mathsf{P} \ne \mathsf{NP}$, then the problem is said to be a **strong NPC**/**strong NP-hard** problem.

## Constructable function

### time constructor

Sometimes, we want the Turing machine to know how long it took, for example, to force the Turing machine to stop after performing $T(n)$ steps of calculation. But if the time taken to calculate $T(n)$ exceeds $T(n)$, this is impossible. For this reason, a time constructor function is defined to avoid such trouble.

If there is a Turing machine $M$, so that when the input is $1^n$ ($n$ 1), $M$ can stop within the time of $O(f(n))$ and output the binary representation of $f(n)$ (note that the output of the Turing machine here is not accept/not accept, but a string, and the output can be performed on paper tape), then $f(n)$ is a **time constructible function**.

Since reading requires $O(n)$ time, none of the non-valued functions of $o(n)$ are time constructible functions.

### space constructor

Similarly, spatial constructible functions can be defined.

If there is a Turing machine $M$, so that when the input is $1^n$ ($n$ 1), $M$ can stop in the space of $O(f(n))$ and output the binary representation of $f(n)$, then $f(n)$ is a **space constructible function**.

## Relationships between complexity classes

### time genealogy theorem

#### Deterministic time genealogy theorem

If $f(n)$ is a time constructible function, then:

$$
\mathsf {DTIME}\left(o\left({\frac {f(n)}{\log f(n)}}\right)\right)\subsetneq \mathsf {DTIME}(f(n))
$$

From the deterministic time spectrum theorem, we can get $\mathsf{P}\subsetneq\mathsf{EXPTIME}$.

??? note "Proof of Deterministic Time Genealogy Theorem"
    Definition language $L=\{(x, y)|\mathcal{U}((x, y), x)\text{ 在 }f(|x|+|y|)\text{ 时间内停机并拒绝}\}$, since $f(n)$ is a time constructible function, it can be calculated according to the definition to determine $L$, and the time taken is $O(f(|x|+|y|))$, so $L\in\mathsf{DTIME}(f(n))$.
    
    Now suppose $L\in\mathsf{DTIME}(o\left({\dfrac {f(n)}{\log f(n)}}\right))$, let $M_z$ be the Turing machine that determines $L$ in $o\left({\dfrac {f(n)}{\log f(n)}}\right)$ time.
    
    Let the time of the universal Turing machine $\mathcal{U}(x, z)$ with respect to $x$ be $g(|x|)$. From the above introduction to the universal Turing machine, we can get $g(n)=o(f(n))$. Therefore, when $y$ is large enough, $g(|z|+|y|)<f(|z|+|y|)$.
    
    Let $y'$ be a large enough $y$, then $\mathcal{U}((z, y'), z)$ must be able to stop within the time of $f(|z|+|y'|)$, thus $M_z(z, y')\ne M_z(z, y')$, resulting in a contradiction, so the assumption does not hold, and the deterministic time genealogy theorem has been proved.

#### Non-deterministic time genealogy theorem

If $g(n)$ is a temporally constructible function and $f(n+1)=o(g(n))$, then $\mathsf{NTIME}(f(n))\subsetneq\mathsf{NTIME}(g(n))$.

From the nondeterministic time spectrum theorem, we can get $\mathsf{NP}\subsetneq\mathsf{NEXPTIME}$.

### space genealogy theorem

If $f(n)$ is a spatially constructible function and $f(n)=\Omega(\log n)$, then $\mathsf{SPACE}(o(f(n)))\subsetneq\mathsf{SPACE}(f(n))$.

Among them, $\mathsf{SPACE}$ can refer to $\mathsf{DSPACE}$ or $\mathsf{NSPACE}$.

From the space genealogy theorem, we can get $\mathsf{PSPACE}\subsetneq\mathsf{EXPSPACE}$.

### Savage's theorem

A deterministic Turing machine can simulate it in the square of the space consumed by a non-deterministic Turing machine (although it may take much more time), that is:

If $f(n)=\Omega(\log n)$, then:

$$
\mathsf{NSPACE}\left(f\left(n\right)\right)\subseteq \mathsf {DSPACE}\left(\left(f\left(n\right)\right)^2\right)
$$

Inference: $\mathsf{PSPACE}=\mathsf{NPSPACE}$, $\mathsf{EXPSPACE}=\mathsf{NEXPSPACE}$.

### P?=NP

Whether the complexity classes $\mathsf{P}$ and $\mathsf{NP}$ are equal is a well-known unsolved problem in computational complexity theory.

If $\mathsf{P}=\mathsf{NP}$, you can get $\mathsf{NP}=\mathsf{co-NP}$, but not vice versa (there is currently no method to prove $\mathsf{P}=\mathsf{NP}$ based on $\mathsf{NP}=\mathsf{co-NP}$).

???+ note "Why isn't NP?=co-NP obvious?"
    Since the $\mathsf{NP}$ problem has the opposite answer to its corresponding $\mathsf{co-NP}$ problem, it is easy to think that for a $\mathsf{co-NP}$ problem, I can solve the $\mathsf{co-NP}$ problem by just inverting the output of the nondeterministic Turing machine that solves its complement, so $\mathsf{NP}=\mathsf{co-NP}$.
    
    In fact, the method mentioned above can indeed solve the $\mathsf{co-NP}$ problem, but a non-deterministic Turing machine has not been found to solve it: if what a Turing machine does is to reverse the output of a non-deterministic Turing machine, the Turing machine is not a non-deterministic Turing machine. Because the non-deterministic Turing machine accepts at a certain branch, and rejects at all branches; and inverting its output, it becomes acceptance at all branches, and rejects at one branch, and this does not meet the definition of a non-deterministic Turing machine, so being able to use this Turing machine to solve this $\mathsf{co-NP}$ problem does not make this $\mathsf{co-NP}$ problem become a $\mathsf{NP}$ problem.

If $\mathsf{P}=\mathsf{NP}$, you can also get $\mathsf{EXPTIME}=\mathsf{NEXPTIME}$.

If $\mathsf{P}\ne\mathsf{NP}$, it can be obtained that NP-intermediate is not empty.

## References

1.  [Computational complexity (1) Warming Up: Automata model](https://lingeros-tot.github.io/2019/03/05/Warming-Up-自动机模型/);

2.  [Computational complexity (2) Turing machine computing model](https://lingeros-tot.github.io/2019/03/05/图灵机模型与可计算性/);

3.  [Wikipedia](https://en.wikipedia.org/) related entries and reference materials for these entries.
