author: CCXXXI, countercurrent-time, Enter-tainer, FFjet, H-J-Granger, Ir1d, mgt, NachtgeistW, orzAtalod, ouuan, SukkaW

Prerequisite knowledge: [Language and judgment issues](./cc-basic.md#问题)

**Finite State Machine** (Finite State Machine, FSM, hereafter also referred to as automaton) is the simplest type of computing model, which is reflected in its extremely limited description ability and resources. Automata are widely used in OI and computer science, and their ideas are involved in many string algorithms. Therefore, it is recommended to complete the learning of automata before learning some string algorithms ([KMP](../string/kmp.md), [AC Automata](../string/ac-automaton.md), [SAM](../string/sam.md)).

## Introduction to automata

First, let's understand what an automaton is used for: An automaton is a mathematical model that determines whether a signal sequence satisfies a certain pattern or rule.

Some terms in this sentence can be explained in detail. "Signal sequence" refers to a signal arranged in order, such as every character from front to back of a string, every number from $1$ to $n$ in an array, every bit of a number from high to low, etc. "Determining whether a certain rule is met" can be understood as: we care about whether this sequence belongs to a specific set. This set is defined by rules we set in advance, such as "all binary strings with even length" or "all palindrome strings".

Sometimes we need to answer this type of question: Does a given sequence satisfy certain characteristics? For example, whether a binary number is an odd number, whether a string is a palindrome, or whether it is a subsequence of another string, etc. Automata are mathematical tools used to solve such problems.

The working principle of the automaton is very similar to the flow chart. Suppose you want to order a cup of milk tea on a takeaway platform, all your choices form a sequence. The following flow chart is an example:

![order fsm](./images/fsm1.svg)

For example, if your selection sequence is "Open the ordering interface -> Select milk tea -> Have money for milk tea", then the status you pass through in sequence may be "Takeaway platform -> Ordering interface -> Pay for milk tea -> Buy milk tea". In this way, our "milk tea automatic machine" helps us determine whether we have bought milk tea based on our choice. We can also find that there may be more than one way to reach a state. You also didn't buy milk tea. You may have exited directly from the ordering interface, or you didn't have the money for milk tea so you didn't buy milk tea.

Through this automaton, we divided the signal sequence into two categories: one is the signal sequence for buying milk tea, and the other is the signal sequence for not buying milk tea. Depending on the final state, we have completed a decision problem.

Although we just used a flow chart to analogy the working process of an automaton, the flow chart itself is only an intuitive visualization tool and does not constitute a mathematical definition of an automaton. In order to describe the structure of the automaton more accurately, we need to abstract the elements in the flow chart. After abstraction, we found that the structure of the flow chart can actually be simplified into a directed graph, in which each node represents a state and each directed edge represents the transition between states.

Therefore, the core structure of the automaton can be formally regarded as a directed graph, which we call **state chart**.

The working method of the automaton is similar to that of the flow chart, except that each node of the automaton is a decision node; the node of the automaton is just a simple state rather than a task; the edges of the automaton can accept a variety of characters (not limited to `T` or `F`).

For example, the automaton that completes "determining whether a binary number is an even number" is as follows:

![example fsm](./images/fsm2.svg)

Starting from the starting node, accept the binary sequence of this number from high to low, and then see where it ends up. If it finally stops at the red circle node, it is an even number; otherwise it is not.

Here, we need to emphasize that in the following we will mention terms such as "character" and "character set" many times. This does not mean that automata can only be used in the field of strings. Characters do not have to be letters such as $\tt abc\cdots z$, which can also be an option.

If you need to determine the relationship between a limited signal sequence and another signal sequence (for example, whether another signal sequence is a subsequence of a certain signal sequence), then a common method is to build an automaton for that limited signal sequence. This will be discussed when learning KMP.

It should be noted that an automaton is just a **mathematical model**, not an algorithm**, nor a data structure**. There are many ways to implement the same automaton, which may have different time and space complexities.

Next, you can choose to continue further research on automata on this page, or you can study specific examples such as [KMP](../string/kmp.md), [AC Automata](../string/ac-automaton.md) or [SAM](../string/sam.md).

FSM is divided into two categories: deterministic finite state automata and non-deterministic finite state automata.

## Deterministic Finite State Automata

**Deterministic Finite Automaton** (Deterministic Finite Automaton, DFA) is reflected in the fact that its decision process is deterministic. Take the "Milk Tea Automatic Machine" as an example. As long as you open the ordering interface, you will enter the ordering interface. There will be no unexpected situations such as the network crashes and cannot be opened, or the phone is out of battery and the screen goes black.

???+ abstract "DFA"
    DFA is a five-tuple $(Q,\Sigma,\delta,q_0,F)$, including:
    
    1.  **Finite state set** $Q$. If a DFA is viewed as a directed graph, then the states in the DFA are equivalent to the vertices on the graph.
    2.  **Character set** $\Sigma$. The automaton can only input these characters.
    3.  **Transfer function** $\delta:Q\times \Sigma \to Q$ is a function that accepts two parameters and returns a value. The first parameter and the return value are both a state, and the second parameter is a character in the character set. If a DFA is viewed as a directed graph, then the transfer function in the DFA is equivalent to the edges between vertices, and each edge has a character.
    4.  **Initial state** $q_0\in Q$ is a special state. In different articles, the initial state is generally represented by $s$, $\textit{start}$, and $q_0$. In this article, $q_0$ is chosen to represent it.
    5.  **Accept state set** $F\subseteq Q$ is a special set of states.

DFA can be simply represented by the following structure:

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/misc/code/fsm/dfa.hpp:dfa"
    ```

The process of finding the state sequence of the input string $w$ in DFA and determining whether it is accepted is called **calculation**.

???+ abstract "DFA calculation process"
    Suppose $M=(Q,\Sigma,\delta,q_0,F)$ is a DFA and $w=w_1w_2\cdots w_n\in\Sigma^*$ is a string. If there is a state sequence $r_0,r_1,\cdots,r_n$ in $Q$ that satisfies
    
    -   $r_0=q_0$，
    -   $\delta(r_i,w_{i+1})=r_{i+1}$ is true for any $i=0,1,\cdots,n-1$,
    -   $r_n\in F$，
    
    It is called $M$ **accepts** (accepts) $w$. Otherwise, it is called $M$ **not accepted** $w$.

When a DFA reads a string, it is transferred character by character according to the transfer function from the initial state. If it is in an accepting state after reading all the characters of a string, then we call this DFA **Accept** this string, otherwise we call this DFA **Not Accept** this string.

???+ abstract "formal language"
    A **formal language** (language), or **language** for short, on the character set $\Sigma$ is a set $L$ of strings on $\Sigma$.

???+ abstract "Language recognized by automata"
    For an automaton $M$, the language it recognizes $L(M)$ is defined as the set of all substrings it accepts $\{w\mid M\text{ accepts }w\}$.

Not all languages ​​can be recognized by DFA.

???+ abstract "regular language"
    If a language can be recognized by a certain DFA, it is called a regular language, also known as a regular language.

As mentioned above, an automaton can be represented by a state diagram. The following is a DFA that accepts and only accepts the strings $\tt a$, $\tt ab$, and $\tt aac$:

![](./images/fsm3.svg)

(The mismatch state is omitted in the figure, and all transitions not shown point to the mismatch state)

## non-deterministic finite state automata

**Nondeterministic Finite Automaton**[^nfa-and-nfaepsilon](Nondeterministic Finite Automaton, NFA) is a natural generalization of DFA. In NFA, for any state and any character, there may be zero, one or more successor states. At the same time, the NFA discussed in this section allows to accept null characters, that is, it can be transferred from one state to one of its successor states without consuming any characters.

For example, consider the "Milk Tea Automatic Machine". After placing an order, although you have money for milk tea, you may not be able to buy milk tea because of poor network. This means there are multiple successors; it may also be because your hand speed is slow, and although the input string (i.e., the operation sequence) is the same, you are not able to buy milk tea because the milk tea is sold out. This is the existence of null characters, and null characters may or may not be left. The above functions can be achieved by slightly modifying the previous automaton:

![order nfa](./images/fsm4.svg)

Obviously, all DFA is an NFA, so NFA can at least recognize all regular languages. But, as an extension of DFA, can NFA recognize more languages? In fact, this is not the case. We will discuss the equivalence of DFA and NFA later.

???+ abstract "NFA"
    Let $\mathcal{P}(Q)$ represent the power set of $Q$. Let $\varepsilon\notin\Sigma$ represent an empty string, and note $\Sigma_\varepsilon = \Sigma\cup\{\varepsilon\}$. NFA is a five-tuple $(Q,\Sigma,\delta,q_0,F)$ consisting of:
    
    1.  **Finite state set** $Q$,
    2.  **Character set** $\Sigma$,
    3.  **Transfer function** $\delta:Q\times \Sigma_{\varepsilon} \to \mathcal{P}(Q)$, a function that accepts two parameters and returns a **state set**, where the first parameter is a state, the second parameter is a character in the character set, and the return value is a set of all possible subsequent states (possibly empty),
    4.  **Start state** $q_0\in Q$,
    5.  **Accept status set** $F\subseteq Q$.

The calculation process of NFA is equivalent to running multiple DFA at the same time. Each operation exhaustively exhausts all possibilities. Finally, as long as one branch reaches the acceptance state, NFA accepts the entire string.

???+ abstract "NFA calculation process"
    Assuming $N=(Q,\Sigma,\delta,q_0,F)$ is an NFA, the string $w$ can be expressed as $y_1y_2\cdots y_m\in\Sigma^*_\varepsilon$. If there is a state sequence $r_0,r_1,\cdots,r_m$ in $Q$ that satisfies
    
    -   $r_0=q_0$，
    -   $r_{i+1}\in\delta(r_i,y_{i+1})$ is true for any $i=0,1,\cdots,m-1$,
    -   $r_m\in F$，
    
    Then it is called $N$ **Accept** $w$. Otherwise, it is called $N$ **not accepted** $w$.

Since null characters are allowed, when the string $w$ is represented as $y_1y_2\cdots y_m\in\Sigma^*_\varepsilon$, any number of null characters can be inserted. For example, the string $\texttt{abc}$ can be represented as $\texttt{a}\varepsilon\texttt{bc}\varepsilon\varepsilon\in\Sigma^*_\varepsilon$. Compared with DFA, each input corresponds to only one result, while each input of NFA may correspond to multiple results, forming a result set.

## Equivalence of DFA and NFA

We call two automata equivalent if and only if they can recognize the same language. DFA and NFA are equivalent, that is, each NFA is equivalent to a certain DFA; therefore, the language class recognized by NFA is also a general regular language. Each DFA can be directly regarded as an NFA; conversely, an NFA can be converted into a DFA through the method of powerset construction.

???+ abstract "Power set construction"
    Suppose NFA is $N = (Q, \Sigma, \delta, q_0, F)$. Definition $E(q)$ represents the set of states that can be reached starting from state $q$ and only along $\varepsilon$ transition.
    
    Construct the DFA as $M = (Q', \Sigma, \delta', E(q_0), F')$, where:
    
    -   **Finite state set** $Q' = \mathcal{P}(Q)$,
    -   **Transfer function** $\delta' : Q' \times \Sigma \to Q'$ satisfies $\delta'(S, c) = \bigcup_{q \in S,~q' \in \delta(q, c)} E(q')$,
    -   **Accept status set** $F' = \{ S \subseteq Q \mid S \cap F \neq \varnothing \}$.
    
    Obviously, in each step of the calculation, the state of $M$ corresponds to the set of states that $N$ may be in.

Although NFA and DFA have the same ability to identify languages, NFA is still useful. This is because for some regular languages, the number of states required to express it with NFA is much smaller than the number of states required by DFA. For example, an NFA with state number $n$ can be constructed such that its corresponding minimum DFA state number is $\Theta(2^n)$. At this time, it is better to directly calculate the time complexity of NFA.

## Calculate the time complexity of DFA and NFA

Suppose the given string length is $n$, the number of automaton states is $s$, and the character set size is a constant. Obviously, the time complexity of DFA calculation is $O(n)$, and you only need to simulate the above process.

The time complexity of naively calculating NFA is $O(ns^2)$. This is because each successor needs to be taken into account, as well as the complexity required for merging states. Of course, you can use bitset or Method of Four Russians to optimize the computational complexity to $O\left(\dfrac{ns^2}{w}\right)$ or $O\left(\dfrac{ns^2}{w\cdot \log n}\right)$.

## Regular expressions and regular languages

This section will discuss the definition and properties of regular expressions and regular languages, and study the relationship between regular expressions and FSM.

### regular expression

**Regular expression** (regular expression) is another commonly used method of describing regular languages. Although we can see this name in many modern languages ​​(such as Python), in fact these languages ​​implement a superset of regular expressions.

???+ abstract "regular expression"
    Given a character set $\Sigma$, a regular expression is a string of symbols inductively defined by the following rules:
    
    1.  Any character $c \in \Sigma$ is a regular expression;
    2.  The empty string symbol $\varepsilon$ is a regular expression;
    3.  The empty language symbol $\varnothing$ is a regular expression;
    4.  If $R_1$ and $R_2$ are regular expressions, then $(R_1 + R_2)$, $(R_1 R_2)$ (also recorded as $(R_1 \cdot R_2)$), and $(R_1^\ast)$ are all regular expressions.

The goal of regular expressions is to describe a language through these symbols. Every regular expression has a corresponding formal language.

???+ abstract "The language represented by the regular expression"
    Assume that the formal language corresponding to each regular expression $R$ is $L(R)$, then there is:
    
    1.  If $R = c$, where $c \in \Sigma$, then $L(R) = \{c\}$;
    2.  If $R = \varepsilon$, then $L(R) = \{\varepsilon\}$;
    3.  If $R = \varnothing$, then $L(R) = \varnothing$;
    4.  If $R = (R_1 + R_2)$, then $L(R) = L(R_1) \cup L(R_2)$;
    5.  If $R = (R_1 R_2) = (R_1\cdot R_2)$, then $L(R) = \{ uv \mid u \in L(R_1),~ v \in L(R_2) \}$, where $uv$ means splicing two strings together front and back;
    6.  If $R = (R_1^\ast)$, then $L(R) = \{u_1 u_2 \cdots u_n \mid u_i \in L(R_1),\ n \in \mathbf{N}_+\}\cup\{\varepsilon\}$, also known as **Kleene star** (Kleene star) or **Kleene closure** (Kleene closure), referred to as closure.

Of course, after specifying the priority of the operation, these parentheses can be omitted if it does not cause confusion.

???+ example "example"
    Assume $L(R_1) = \{0,\ 01\}$, $L(R_2) = \{\varepsilon,\ 1,\ 11,\ 111,\ \dots\}$, then we have:
    
    -   $L(R_1R_2) = \{0,\ 01,\ 011,\ 0111,\ \dots\}$，
    -   $R_2^\ast = R_2$，
    -   $L(R_1 + R_2) = \{0,\ 01,\ \varepsilon,\ 1,\ 11,\ 111,\ \dots\}$．

Each regular expression can be converted into an NFA through [Thompson's construction](https://zh.wikipedia.org/wiki/%E6%B1%A4%E6%99%AE%E6%A3%AE%E6%9E%84%E9%80%A0%E6%B3%95) (Thompson's construction), and each DFA can also be converted into a regular expression through the state elimination method [^state-elimination-method](State Elimination Method). Therefore, regular expressions and FSM are equivalent.

### regular language

In this section, we do not consider specific regular expressions, but instead consider regular expressions that take variables as parameters (variables can be any regular language). Applying the algebraic laws of regular expressions helps simplify regular expressions.

???+ note "Algebraic properties of regular languages"
    1.  Commutative law of union: $L + M = M + L$
    2.  The associative law of union: $(L + M) + N = L + (M + N)$
    3.  The associative law of connection: $(LM)N = L(MN)$
    4.  $\varnothing$ is the unit element of the union operation: $\varnothing + L = L + \varnothing = L$
    5.  $\varepsilon$ is the unit element of the connection operation: $\varepsilon L = L \varepsilon = L$
    6.  $\varnothing$ is the zero factor of the concatenation operation: $\varnothing L = L \varnothing = \varnothing$
    7.  Distributive law: $L(M + N) = LM + LN$, $(M + N)L = ML + NL$
    8.  Idempotent law of union: $L + L = L$
    9.  Closure-related laws: $(L^\ast)^\ast = L^\ast$, $\varnothing^\ast = \varepsilon$, $\varepsilon^\ast = \varepsilon$

The **closure** of regular languages ​​is also an important property. These properties allow us to start from some simple automata and through certain operations, construct a finite state machine (FSM) that can recognize other languages. In short, closure can be used as a tool to construct complex FSMs.

Regarding the closure of regular languages, we have:

???+ note "Closure of regular languages"
    Let $L,M$ be two regular languages ​​​​on the character set $\Sigma$, and map $h:\Sigma\to\Sigma^*$. Define the homomorphism of the string $s=s_1s_2\cdots s_n$ to be $h(s)=h(s_1)h(s_2)\cdots h(s_n)$. So,
    
    1.  The union $L + M$ of two regular languages ​​is regular,
    2.  The connection $LM$ of two regular languages ​​is regular,
    3.  The closure $L^*$ of a regular language is regular,
    4.  The complement of a regular language $\Sigma^*\setminus L$ is regular,
    5.  The intersection $L\cap M$ of two regular languages ​​is regular,
    6.  The difference $L\setminus M$ between the two regular languages ​​is regular,
    7.  The inversion of the regular language $L^R=\{s_n\cdots s_2s_1 \mid s=s_1s_2\cdots s_n\in L\}$ is regular,
    8.  The homomorphism $h(L)=\{h(s)\mid s\in L\}$ of a regular language is regular,
    9.  The inverse homomorphism $h^{-1}(L) = \{ s \in \Sigma^\ast \mid h(s) \in L \}$ of a regular language is regular.

A simple corollary is that all finite languages ​​are regular languages. In fact, [Dictionary Tree Trie](../string/trie.md) is an automaton that recognizes them.

## Myhill–Nerode Theorem

The Myhill–Nerode theorem gives the criterion for determining whether a language is a regular language. This theorem describes the structural characteristics of regular languages ​​through the concept of equivalence classes.

???+ abstract "Nerode equivalence"
    For a language $L$ and any string $x,y\in \Sigma^\ast$, if for any $z\in\Sigma^*$, there is $xz\in L\iff yz\in L$, then the strings $x$ and $y$ are said to be equivalent to $L$, denoted as $x\equiv_L y$.

That is to say, if for two strings $x$ and $y$, the same arbitrary string $z$ (including empty strings) is spelled after $x$ and $y$, they always either belong to $L$ at the same time or do not belong to $L$ at the same time, then we say that $x$ and $y$ are equivalent to $L$.

According to the above definition, we divide the set of all finite strings into one or more equivalence classes. If and only if the number of these equivalence classes is limited, these equivalence classes can be used to construct a DFA that recognizes the language. The number of states of this DFA is equal to the number of equivalence classes. Moreover, this number of states is the smallest among all DFAs that can recognize this language. This is the Myhill–Nerode theorem.

???+ note "Myhill–Nerode Theorem"
    A language $L$ is regular if and only if the number of equivalence classes into which $\Sigma^\ast$ is divided by the equivalence relation $\equiv_L$ is finite.
    
    For any DFA that can recognize the language $L$, any two strings $x$ and $y$ that can drive it to the same state must be in the same equivalence class.
    
    Furthermore, the number of equivalence classes is the number of states of the minimum DFA that can identify $L$. Each equivalence class corresponds to exactly one state in the minimal DFA. This minimal DFA is unique in the isomorphic sense.

This theorem provides a way to construct a DFA using equivalence relations:

-   The state set is all the equivalence classes divided according to the equivalence relationship. Each equivalence class randomly selects a representative string (for example, a string with the smallest length).
-   To construct a transfer function, you only need to add the characters in the transfer after the selected representative string, and find the state corresponding to the equivalence class of the obtained string, which is the successor state of the corresponding transfer. Because all strings in the same equivalence class are equivalent, arbitrarily selected representative strings will not affect the result of the transfer.
-   The initial state is the equivalence class corresponding to the empty string $\varepsilon$.
-   The set of accepting states is the set of equivalence classes that represent strings belonging to the given language.

As a classic example, [Suffix Automata](../string/sam.md) is a minimal DFA constructed using the Myhill–Nerode theorem.

The Myhill–Nerode theorem is usually applied to the construction of DFA corresponding to some infinite regular languages. Many times, the conditions of the problem are relatively simple. You only need to examine a set of strings that are not too long, and you can construct an automaton that recognizes the entire language.

### example

This section introduces how to apply the Myhill–Nerode theorem in practice through an example problem.

???+ example "[P12294 \[THUPC 2025 决赛\] is a 01 string, n times ternary operator, the final value is 1 (enhanced version)](https://www.luogu.com.cn/problem/P12294)"
    The meaning of the ternary operation table $s_0s_1\cdots s_7$ ($s$ is only composed of $0,1$) of $a,b,c$ is that if the $a+2b+4c$th bit of $s$ is $1$, then $1$ is returned, otherwise $0$ is returned.
    
    Given the operation tables $s$ and $q$ $01$ strings of length $2n+1$, you need to answer for each $01$ string separately:
    
    Can it be operated $n$ times, each time replacing three consecutive numbers with the corresponding operation values, so that the result of the operation is $1$? Give a solution, or judge that there is no solution.
    
    $1\le 2n+1\le 10^5,~\sum(2n+1)\le 3\times 10^5$．

??? note "Solution"
    The set of $01$ strings that can synthesize $1$ is a regular language (that is, there is a DFA that can determine whether a $01$ string can synthesize $1$) [^prove-regular-language]. Therefore, consider using the Myhill–Nerode theorem. Because the conditions are relatively simple, after experiments, we only need to divide the $01$ strings of length $\le 9$ into equivalence classes; when determining that two strings are equivalent, we only need to enumerate the suffixes of length $\le 6$ to make a determination. As long as two strings are connected with any suffix of length $\le 6$, they can either synthesize the string we want at the same time, or neither can synthesize the string we want, then the two strings are equivalent.
    
    Each transfer is equivalent to adding a new $01$ character after the current string, and then changing this new string into the string with the smallest string length in the equivalence class where the new string belongs. Design an automaton based on the above transfer. This automaton can determine within $O(n)$ complexity whether a string of length $n$ has an operation method such that the result is $1$. At the same time, the number of states of the automaton is very small.
    
    For convenience, we will build $6$ automata. These $6$ automata respectively indicate whether an operation method can be used to make the result $0,1,00,01,10,11$. For all possible arithmetic tables, the maximum number of states of the automaton is $47$.
    
    Using automata and appropriate preprocessing, you can consider using doubling or cat trees to implement static interval query to see if there is an operation method in the interval that makes the result $1$. The former query is $O(\log n)$, and the latter query is $O(1)$.
    
    Consider using divide and conquer to solve construction problems. Let $f(l,r,t)$ represent the solution of merging the interval $[l,r]$ into $t\in\{{0,1,00,01,10,11}\}$. At this time, heuristic splitting is used to maintain two pointers $i,j$, one scanning from left to right and one scanning from right to left, to enumerate the breakpoint $\textit{mid}$ as $i$ or $j$. For $t\in\{{0,1}\}$, enumerate how $t$ is divided into left and right parts. The length of one part $t$ is $2$, and the length of the other part $t$ is $1$. (For example, for the median operation table $s=00010111$, $1$ can be divided into $01$ and $1$.) For $t\in\{{00,01,10,11}\}$, $type$ is directly divided into left and right parts.
    
    If the left and right parts divided at this time are $t_1$ and $t_2$ respectively, then further determine whether $[l,mid]$ can generate $t_1$ and whether $[\textit{mid}+1,r]$ can generate $t_2$. If so, divide and conquer directly. If the $O(1)$ cat tree decision is used, the complexity of the heuristic splitting construction is $O(n\log n)$; otherwise, using the doubling decision, the complexity of the construction is $O(n\log^2n)$.
    
    If a cat tree is used, the total complexity is $O(n|Q|\log n+n\log n)$, where $|Q|\le 47$. For convenience, the reference code uses multiplication and reduces the constant through the underlying block. The corresponding total complexity is $O(n|Q|\log n+n\log^2 n)$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/fsm/fsm_1.cpp:main"
    ```

### exercise

-   [Median Replace Hard](https://qoj.ac/problem/12010)
-   [JOISC 2024 Card Collection](https://www.luogu.com.cn/problem/P10436) (Building an automaton through the Myhill–Nerode theorem, this question can be used to query multiple intervals)

## DFA minimization

As mentioned earlier, two DFAs are equivalent if and only if they recognize the same regular language. According to the different languages ​​recognized, the entire DFA is divided into infinite equivalence classes. When performing algorithms such as DP within DP, the $|Q|$ of the established DFA may be too large, making the outer DP transfer too complex. Therefore, it is often necessary to find the smallest DFA in the equivalence class to which the DFA belongs to reduce the outer DP transfer complexity.

The Myhill–Nerode theorem in the previous section provides a construction method. However, for some more complex problems, constructing it directly through the Myhill–Nerode theorem requires traversing a rather long set of strings, which takes a lot of time. Therefore, we need a method that can directly construct a minimal DFA starting from an already constructed DFA (which is usually easier). This is called the **DFA minimization** (DFA minimization) problem.

The commonly used algorithm for DFA minimization is **Hopcroft algorithm**. Because the Myhill–Nerode theorem points out that for any DFA that can recognize a certain language, the strings that can drive it to the same state must be Nerode equivalent. All Nerode equivalent strings correspond to the same state in the minimum DFA, so the state of the minimum DFA must be a set of several states in the current DFA. We can start from the existing DFA state sets and divide them into several equivalence classes without examining specific strings. The Hopcroft algorithm starts from the roughest partition $\{F,Q\setminus F\}$ and uses a series of evidence $A$ to improve this partition until no further improvement is possible. This is the core idea of ​​Hopcroft's algorithm.

The so-called **evidence** $A$ is a state set, and it and its complement $Q\setminus A$ must correspond to different Nerode equivalence classes. In other words, there is a certain string $s\in\Sigma^*$ such that starting from the states in $A$ and $Q\setminus A$ respectively, after reading the string $s$, all the states in $A$ are in the accepting state, while all the states in $Q\setminus A$ are in the non-accepting state, or vice versa. Therefore, if there are two states $u,v\in Q$, exactly one of them is transferred to the evidence $A$ under a certain character $c$, and one is transferred outside the evidence $A$, that is, $\delta(u,c)\in A$ and $\delta(v,c)\in A$ are established and only one is established, then $u,v$ also does not belong to a Nerode equivalence class - states $\delta(u,cs)$ and $\delta(v,cs)$ One and only one of them is in the accepting state. Therefore, by using whether $\delta(u,c)\in A$ is established, the division can be improved. Specifically, suppose

$$
S_x = \{u\mid u\in P_x,~\delta(u,c)\in A\}.
$$

If neither $S_x$ nor $P_x\setminus S_x$ is an empty set, then the current partitioning state set $P_x$ can be improved to $S_x$ and $P_x\setminus S_x$.

At the beginning, the accepted state set $F$ is inserted into the evidence set $W$ as a piece of evidence, that is, $W\gets\{F\}$, and the current division is maintained as $P\gets\{F,~Q\setminus F\}$. The initial evidence is clearly established: the states in $F$ and $Q\setminus F$ can never be equivalent. Each time, a set $A$ is randomly taken from the evidence set $W$ to improve the current partition. Enumerate all characters $c\in\Sigma$. For each state set $P_x$ in the current partition $P$, find $S_x$ described above. If $S_x\neq\varnothing$ and $|S_x|\neq|P_x|$, it means that $P_x$ can be further divided into two sets $S_x$ and $P_x\setminus S_x$, and they can be directly used to replace $P_x$ in $P$.

Whenever a more detailed division is obtained, it means that new evidence is obtained. In principle, the newly obtained $S_x$ and $P_x\setminus S_x$ can be stuffed into the evidence set $W$, waiting for further verification. However, this is not necessary. It is easy to understand that for the three evidences $P_x,S_x,P_x\setminus S_x$, you only need to verify any two of them to ensure the correctness of the result: because there are only three results: $\delta(u,c)\in S_x$, $\delta(u,c)\in P_x\setminus S_x$ and $\delta(u,c)\notin P_x$, and dividing the set into three parts only requires two judgments. Therefore, when dividing $P_x$ into $S_x$ and $P_x\setminus S_x$, if $P_x$ is still in the evidence set $W$, it means that the evidence $P_x$ has not been tested, and $P_x$ in the evidence set $W$ needs to be replaced with $S_x$ and $P_x\setminus S_x$ Two; otherwise, the current division must be equivalent to the result that [^smaller-evidence] has tested $P_x$, so only the smaller one of $S_x$ and $P_x\setminus S_x$ needs to be inserted into the evidence set $W$. Similar to heuristic splitting, this can lead to excellent complexity.

Writing the above process into pseudo code is:

$$
\begin{array}{l}
\textbf{Algorithm } \text{Hopcroft's Algorithm}(Q, \Sigma, \delta, q_0, F): \\
\textbf{Input. } \text{DFA } A=(Q, \Sigma, \delta, q_0, F). \\
\textbf{Output. } \text{A partition of } Q \text{ into equivalence classes of the minimal DFA.} \\
\textbf{Method. } \\
\begin{array}{ll}
1 & P \gets \{F,\; Q \setminus F\} \\
2 & W \gets \{F\} \\
3 & \textbf{while } W \ne \varnothing \\
4 & \quad \text{choose and remove any } A \in W \\
5 & \quad \textbf{for each } c \in \Sigma \\
6 & \quad \quad S \gets \{ q \in Q \mid \delta(q,c) \in A \} \\
7 & \quad \quad \textbf{for each } Y \in P \text{ such that } S \cap Y \ne \varnothing \text{ and } Y \setminus S \ne \varnothing \\
8 & \quad \quad \quad Y_1 \gets S \cap Y,~Y_2 \gets Y \setminus S \\
9 & \quad \quad \quad P \gets (P \setminus \{Y\}) \cup \{Y_1, Y_2\} \\
10 & \quad \quad \quad \textbf{if } Y \in W \\
11 & \quad \quad \quad \quad W \gets (W \setminus \{Y\}) \cup \{Y_1, Y_2\} \\
12 & \quad \quad \quad \textbf{else} \\
13 & \quad \quad \quad \quad \text{add the smaller of } Y_1 \text{ and } Y_2 \text{ to } W \\
14 & \textbf{return } P
\end{array}
\end{array}
$$

When implementing the algorithm, the complexity bottleneck lies in the calculation of $S$. It is not feasible to directly traverse all $q\in Q$ and then determine whether $\delta(q,c)\in A$ is true. Therefore, it is necessary to preprocess the reverse transfer edge $\{q\in Q\mid \delta(q,c)=a\}$ before running the algorithm, so that by using these reverse transfers and traversing $a\in A$, the set $S$ can be obtained. This ensures that each transfer $\delta(q,c)=a$ will only be traversed when $a$ belongs to a certain evidence; and the previous evidence screening method ensures that among the evidence sequences $A_1\supset A_2\supset\cdots\supset A_k$ containing $a$ actually used in the algorithm, the former one is at least twice the size of the latter one, therefore, $k\in O(\log n)$. In other words, each transfer edge will only be traversed $O(\log n)$ times at most, and the total number of transfers is $n|\Sigma|$. Therefore, the total complexity is $O(n|\Sigma|\log n)$.

The reference implementation is as follows: [^detail]

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/misc/code/fsm/dfa.hpp:hopcroft"
    ```

This reference implementation allows the state of the automaton to be labeled with any integer value, rather than a simple binary label of "accept" or "not accept". It can be seen from the reference implementation that the only difference from the basic Hopcroft algorithm lies in the initial partition and the construction of the evidence set. This extended automaton is also called [Moore machine](https://en.wikipedia.org/wiki/Moore_machine). An application of it can be seen in the second example of this section.

### example

This section introduces how to actually apply DFA minimization techniques through two examples.

???+ example "example"
    Given a $01?$ string $a$ of length $n$ and the initial variable $x = 0$, we traverse each bit of $a_i$ in order and perform the following operations:
    
    1.  If $a_i = 0$, let $x \gets x - \text{lowbit}(x)$;
    2.  If $a_i = 1$, let $x \gets x + \text{lowbit}(2^k - 1 - x)$;
    3.  If $a_i = ?$, you can choose $0$ or $1$, corresponding to one of the above two operations.
    
    In the end, if $x \in [0, r]$, the operation sequence is said to be good.
    
    Now we need to find out how many "good" complete sequences there are for each $j = 1 \ldots n$ under the premise of forcing $a_j = 0$. In particular, when $a_j = 1$, the answer is $0$.
    
    $1\le n\le 10^5,~1\le k\le 20,~0\le r<2^k$. The output is modulo $998244353$.

??? note "Solution"
    Consider naive DP. Let $f_{i,j}$ mean that starting from $x=0$, after the operation of $[1,i]$, the current number is the number of plans of $j$. Let $g_{i,j}$ represent the number of solutions starting from $x=j$, after the operation of $[i,n]$, and finally $x \in [0, r]$. The answer to force $a_i=0$ is $\sum_j f_{i-1,j}g_{i+1,j - \text{lowbit}(j)}$. The complexity is $O(n2^k)$.
    
    Consider directly constructing the transfer of $j$ into DFA, then run DFA minimization, and then DP.

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/fsm/fsm_2.cpp:main"
    ```

???+ example "[Minimal Subset Difference](https://codeforces.com/contest/956/problem/F)"
    Definition $f(n)$ means filling in the plus sign or minus sign between all the digits of the decimal number $n$, and the absolute minimum value of the final value obtained.
    
    $T$ group inquiry. Each group asks given $l, r, k$ to find the number of $m$ that satisfy $l \le m \le r$ and $f(m) \le k$.
    
    $1 \le T \le 5\times 10^4$，$1 \le l \le r \le 10^{18}$，$0 \le k \le 9$．

??? note "Solution"
    First, a method of greedily calculating $f(n)$ is given. Consider a number from high to low. Initially, assume that the sum of the obtained numbers is $0$. When calculating to a certain digit, if the currently synthesized number is a negative number, add the current digit, and if it is a positive number, subtract the current digit. In this way, the absolute value of $f(n)$ calculated greedily must be less than or equal to $9$. Therefore, the absolute value of the real $f(n)$ must be less than or equal to $9$.
    
    Let us further think about what is the maximum number that can be synthesized in the intermediate process to synthesize the final answer. Because the answer must be less than or equal to $9$, and there are only $18$ digits, you can only add or subtract at most $9$ each time. The number that can be synthesized during the process must be less than or equal to $90$, otherwise it will not be reduced in the end. In fact, this upper limit can be even lower [^upper-bound].
    
    Consider the naive DP set of DP. First, think about how the inner DP determines the answer to a number: defining $g_{i,c}$ means that this number can be synthesized into $c$ based only on the first $i$ bits. According to the previous article, $c$ only retains numbers less than or equal to $90$. If the current digit is $v$, then there is a transfer:
    
    $$
    g_{i+1,c+v}\gets g_{i,c},~
    g_{i+1,|c-v|}\gets g_{i,c}.
    $$
    
    The outer DP considers the digital DP. Will ask about the difference. Assume the state is $f_{\textit{len},\textit{lim},\textit{sta}}$, and its subscripts respectively indicate that the $\textit{len}$th bit has been considered, whether there is an upper bound limit, and the current automaton state is located at $\textit{sta}$, etc.
    
    Different from ordinary DFA, we need to record the corresponding answer for each state of the automaton. Run a brute force search and you will find that the status number of the inner DP is only $19564$. Then run DFA minimization directly to optimize the number of states to $715$.
    
    At this time, we have preprocessed all the digital DP answers of $\textit{lim}=0$. When performing multiple tests, we only need to run the case of $\textit{lim}=1$, and the answer can be found quickly.
    
    Time complexity $O(|S||\Sigma|\log |S|+(|Q||\Sigma|+T)|\Sigma|\log_{10} V)$ ($|S|=19564$, $|Q|=715$).

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/fsm/fsm_3.cpp:main"
    ```

### exercise

-   [Language Recognition](http://poj.org/problem?id=3576)
-   [Equanimous](https://qoj.ac/problem/7083)

## Common applications of automatic machines

This section lists some common automata applications in algorithm competitions [^is-dfa].

### dictionary tree

[Dictionary tree](../string/trie.md) is the first automaton that most OIers come into contact with. It accepts and only accepts elements in the specified string set. The transition function is the edge on the Trie, and the accepting state is the state reached when each string is inserted into the Trie.

### KMP automaton

[KMP algorithm](../string/kmp.md) can be regarded as an automaton. The KMP automaton based on the string $s$ accepts and only accepts strings with $s$ as the suffix, and its acceptance status is $|s|$.

Transfer function:

$$
\delta(i, c)=
\begin{cases}
i+1&s[i+1]=c\\
0&s[1]\ne c\land i=0\\
\delta(\pi(i),c)&s[i+1]\ne c\land i>0
\end{cases}
$$

### AC automatic machine

[AC Automata](../string/ac-automaton.md) accepts and only accepts strings suffixed by an element in the specified string set. That is Trie + KMP.

### suffix automaton

[Suffix Automation](../string/sam.md) accepts and only accepts the suffix of the specified string.

### Generalized suffix automata

[Generalized suffix automaton](../string/general-sam.md) accepts and only accepts the suffix of an element in the specified string set. That is Trie + SAM.

The relationship between generalized SAM and SAM is the relationship between AC automata and KMP automata.

### Palindrome Automata

[Palindromic Automata](../string/pam.md) is rather special, and it cannot be easily defined as an automaton.

If it needs to be defined, it accepts and only accepts the **center and right half** of all palindrome substrings of a certain string.

"Center and right part" is the literal meaning in an odd palindrome string, and is defined as a special character plus the right part in an even palindrome string. This definition may seem strange, but it makes PAM truly an automaton, not just two trees.

### sequential automata

[Sequence Automation](../string/seq-automaton.md) accepts and only accepts subsequences of the specified string.

### DP set DP

[DP within DP](../dp/dp-of-dp.md) is an application of automata. It can be seen as a technique of first building an automaton through the inner DP, and then using the DP on the outer layer to implement counting and optimization tasks.

## suffix link

Since automata and matching are inseparable, and a basic idea of ​​matching is "If this string doesn't work, try its suffix." Therefore, many automata (KMP, AC automata, SAM, PAM) have the concept of suffix linking.

A state will correspond to several strings. Its suffix link points to the longest corresponding state among the public true suffixes of the string corresponding to the state on the automaton. Generally, suffix links will form a tree, and the suffix link trees of different automata have some same properties, which can be paid attention to when learning.

## Extended reading

-   [Computational complexity (1) Warming Up: Automata model](https://lingeros-tot.github.io/2019/03/05/Warming-Up-自动机模型/)
-   [National Training Team 2021 Paper Xu Zhe’an briefly talks about finite state automata and their applications](https://github.com/OIerTFX/IOI/blob/master/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2021%E8%AE%BA%E6%96%87%E9%9B%86/pdf-files/%E5%BE%90%E5%93%B2%E5%AE%89%20%E6%B5%85%E8%B0%88%E6%9C%89%E9%99%90%E7%8A%B6%E6%80%81%E8%87%AA%E5%8A%A8%E6%9C%BA%E5%8F%8A%E5%85%B6%E5%BA%94%E7%94%A8.pdf)
-   [Myhill–Nerode theorem - Wikipedia](https://en.wikipedia.org/wiki/Myhill%E2%80%93Nerode_theorem)
-   Knuutila, Timo. "Re-describing an algorithm by Hopcroft." Theoretical Computer Science 250, no. 1-2 (2001): 333-363.
-   Hopcroft, John E., Rajeev Motwani, and Jeffrey D. Ullman. "Introduction to automata theory, languages, and computation." Acm Sigact News 32, no. 1 (2001): 60-65.

[^nfa-and-nfaepsilon]: In this definition we allow transitions between states through null characters ($\varepsilon$), so more accurately, this is a non-deterministic finite automaton (NFA-$\varepsilon$) with $\varepsilon$ transitions. In some textbooks, it is directly called NFA. For the sake of simplicity, this usage is adopted in this article. In theory, NFA and NFA-$\varepsilon$ are different, but in fact their computing capabilities are the same.

[^state-elimination-method]: For details, see Section 3.2 of [National Training Team 2021 Paper Xu Zhe'an Brief Discussion on Finite State Automata and Its Application](https://github.com/OIerTFX/IOI/blob/master/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2021%E8%AE%BA%E6%96%87%E9%9B%86/pdf-files/%E5%BE%90%E5%93%B2%E5%AE%89%20%E6%B5%85%E8%B0%88%E6%9C%89%E9%99%90%E7%8A%B6%E6%80%81%E8%87%AA%E5%8A%A8%E6%9C%BA%E5%8F%8A%E5%85%B6%E5%BA%94%E7%94%A8.pdf).

[^prove-regular-language]: For details, see [Official Solution](https://qoj.ac/download.php?type=attachments&id=2079&r=1).

[^smaller-evidence]: The "equivalent" here means that although $P_x$ may not have been actually tested, even if $P_x$ is tested on the current partition, there will be no improvement. A simple understanding is that on the tree of the evidence set obtained by the set split, one of its ancestors and all the branches on the path have been tested. Therefore, it can be explained inductively that it is equivalent to that it has also been tested.

[^detail]: There is a detail in the algorithm implementation: for a piece of evidence $A$, it is possible that after testing part of the characters, the evidence set will have been split into $B$ and $C$. Let’s assume $|B|\ge |C|$. Because in the reference implementation, the smaller set $C$ is inserted at the end of the evidence queue, and the larger evidence set $B$ is replaced at the original position of the set $A$. When the algorithm continues to run, it actually only uses the evidence $B$ to check the remaining characters. This is correct. This is because for the characters that have been verified, at least two sets $A$ and $C$ have been verified; for the characters that have not yet been verified, at least two sets $B$ and $C$ have been verified.

[^upper-bound]: For details, see example question 5.2 in [National Training Team 2021 paper Xu Zhe'an briefly talks about finite state automata and their applications](https://github.com/OIerTFX/IOI/blob/master/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2021%E8%AE%BA%E6%96%87%E9%9B%86/pdf-files/%E5%BE%90%E5%93%B2%E5%AE%89%20%E6%B5%85%E8%B0%88%E6%9C%89%E9%99%90%E7%8A%B6%E6%80%81%E8%87%AA%E5%8A%A8%E6%9C%BA%E5%8F%8A%E5%85%B6%E5%BA%94%E7%94%A8.pdf).

[^is-dfa]: The definition of automaton in this article requires that it be complete, that is, any state must have a transition under any character. In descriptions of these string-related automata, mismatch states are usually ignored. Trie, SAM, etc. are all examples of this. In order to be compatible with the definition provided in this article, mismatch states need to be added explicitly to the description of these automata.
