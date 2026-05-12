Prerequisites: [Introduction to Game Theory](./intro.md)

This article discusses [impartial combinatorial games](./intro.md#impartial-combinatorial-games).

Among impartial combinatorial games, the most fundamental and important is the normal Nim game. The Sprague-Grundy theorem states that all impartial combinatorial games under normal play are equivalent to a single-pile Nim game. From this, the concepts of Sprague-Grundy functions and Nimbers can be developed, which completely characterize impartial combinatorial games under normal play. Therefore, this article first establishes the results of normal Nim games and the Sprague-Grundy theory. Then, this article discusses some common impartial combinatorial games in algorithm competitions.

Finally, this article briefly discusses misère Nim games. Misère games are much more complex than normal games and rarely appear in algorithm competitions. If not specified otherwise, all games mentioned in this article are assumed to be normal impartial combinatorial games.

???+ info ""States", "Positions", and "Games""
    This article uses these three terms interchangeably. In game theory, the state (state) of a game typically includes all information that could be relevant to the game up to a certain point in time. In general, the state of a game typically includes the past actions of both players, the realized values of random variables, the content of each player's known information, etc. The position (position) of a game is relatively not a standard term in game theory; it usually refers to the situation both players face at a certain point in the game, such as the positions of pieces in board games. Only for impartial combinatorial games (or more generally, zero-sum, deterministic, perfect information games), since the game involves no randomness and the set of future moves and payoff function for each player are independent of the historical path to the current position (i.e., previous actions of both players), the state's state and position are indistinguishable and can both be viewed as nodes on the game graph. Since a game can always be described by its initial position, the term "position" is sometimes used directly to refer to the game itself.

## Nim Game

The rules of the Nim game are simple:

???+ abstract "Nim Game"
    There are $n$ piles of stones, with the $i$-th pile containing $a_i$ stones. Two players take turns removing any positive number of stones from any single pile, but must remove at least one. The player who takes the last stone wins.

It is easy to verify that Nim is a normal impartial combinatorial game.

???+ example "Example"
    For instance, suppose there are $3$ piles of stones with $2,5,4$ stones respectively. One can remove $2$ stones from the first pile, making the position $0,5,4$; or remove $4$ stones from the second pile, making the position $2,1,4$. If at some point the position becomes $0,0,5$, and player A removes the $5$ stones from the third pile, taking the last stone, then player A wins.

### Game Graph and States

In Nim, the possible transitions of positions can be described using a game graph.

Treat each possible state as a node in the graph, and draw directed edges from a state to its successor states (i.e., states reachable by one move). This forms a directed acyclic graph, which is the game graph. The graph is acyclic because in Nim, the total number of stones strictly decreases with each move.

???+ example "Example"
    For example, for a Nim game with $3$ piles of stones containing $1,1,2$ stones respectively, the following game graph can be drawn:
    
    ![Example game graph](./images/nim.svg)
    
    As will be mentioned shortly, red nodes in the graph denote P-positions (winning for the previous player), and black nodes denote N-positions (winning for the next player).

Since Nim is an impartial combinatorial game, whether each player has a winning strategy depends only on the current state of the game, not on the player's identity. Therefore, all states can be classified into **P-positions** (previous player winning) and **N-positions** (next player winning), denoted as $\mathcal{P}$ and $\mathcal{N}$ respectively[^n-vs-p]. This definition applies to all impartial combinatorial games.

Through the following lemma, all states can be inductively labeled as P-positions or N-positions: <a id="np-lem"></a>

???+ note "Lemma"
    In impartial combinatorial games under normal play:
    
    1.  States with no successor states are P-positions,
    2.  A state is an N-position if and only if it has at least one successor that is a P-position,
    3.  A state is a P-position if and only if all of its successors are N-positions.

??? note "Proof"
    For the first statement: if the player has no available moves, they have already lost the game.
    
    For the second statement: if at least one successor of the current state is a P-position, the player can move to that P-position; then the opponent faces a P-position, and the player wins.
    
    For the third statement: if no successor is a P-position, then no matter what the player does, they can only move to an N-position; then the opponent faces an N-position, and the player loses.

In all impartial combinatorial games, the game graph is a directed acyclic graph. Therefore, using these three properties, after drawing the game graph, one can compute whether each state is a P-position or N-position in $O(|V|+|E|)$ time, where $|V|$ is the number of states in the game graph and $|E|$ is the number of edges, i.e., the total number of possible moves from all states.

This lemma can be extended to misère games and cases where the directed graph may contain cycles. See the [Directed Graph Games](#directed-graph-games) section for related discussion.

### Nim Sum

Continuing our study of Nim.

By drawing the game graph, one can determine whether a position is a winning position for the first player in $\Omega(\prod_{i=1}^na_i)$ time. However, this complexity is too high for practical use. In fact, one can observe that whether a Nim position is winning for the first player depends only on the Nim sum of the stone counts in the current position.

???+ abstract "Nim Sum"
    The **Nim sum** of natural numbers $a_1,a_2,\cdots,a_n$ is defined as $a_1\oplus a_2\oplus\cdots\oplus a_n$.

The Nim sum is simply the [bitwise XOR operation](../bit.md#bitwise-operations).

???+ note "Theorem"
    In Nim, the position $(a_1,a_2,\cdots,a_n)$ is a P-position if and only if the Nim sum
    
    $$
    a_1\oplus a_2\oplus\cdots\oplus a_n = 0.
    $$

??? note "Proof"
    Apply induction to all possible states:
    
    1.  If $a_i=0$ for all $i=1,\cdots,n$, the state has no successors, and the Nim sum equals $0$, so the proposition holds.
    2.  If $k = a_1\oplus a_2\oplus\cdots\oplus a_n\neq 0$, we need to prove this state is an N-position. That is, we need to construct a legal move such that the successor is a P-position; by the induction hypothesis, we only need to prove the successor satisfies $a'_1\oplus a'_2\oplus\cdots\oplus a'_n=0$. Using the properties of Nim sum (i.e., XOR), this is equivalent to saying there exists a pile of stones such that removing some stones from $a_i$ gives $a_i\oplus k$, which means $a_i>a_i\oplus k$.
    
        Specifically, let $d$ be the position of the highest bit of $k$ that is $1$. Then there must exist some $a_i$ whose binary representation has a $1$ at bit $d$. For that pile, we must have $a_i>a_i\oplus k$, because in $a_i\oplus k$, bit $d$ becomes $0$ while higher bits remain the same as in $a_i$.
    3.  If $a_1\oplus a_2\oplus\cdots\oplus a_n= 0$, we need to prove this state is a P-position. By the induction hypothesis, we only need to prove that all successors have a non-zero Nim sum. This is necessarily true: any legal move that changes $a_i$ to $a'_i\neq a_i$ will necessarily change the Nim sum to $a'_i\oplus a_i\neq 0$.

From this, one can determine whether a Nim position is winning for the first player in $O(n)$ time.

## Sprague-Grundy Theory

The Sprague-Grundy theory states that all impartial combinatorial games are equivalent to single-pile Nim games. The main application scenario is when a game consists of multiple independent subgames. In this case, the game state can be determined by computing the Nim sum of the SG function values of the subgames. If the game itself does not have such a structure, determining winning and losing positions only requires applying the [lemma](#np-lem) from the game graph section.

### Notation for Games

As discussed earlier, all impartial combinatorial games can be described by drawing the game graph. Since in the game graph, the nature of each state is determined only by its successors, a state $S$ in the game graph can be represented by the set of its successor states.

???+ example "Example (continued)"
    Using the game graph from above as an example, we can obtain the following state representations:
    
    $$
    \begin{aligned}
    S_{0,0,0} &= \{\},\\
    S_{0,1,0} &= \{S_{0,0,0}\} = \{\{\}\},\\
    S_{0,0,1} &= \{S_{0,0,0}\} = \{\{\}\},\\
    S_{0,0,2} &= \{S_{0,0,0},S_{0,0,1}\} = \{\{\},\{\{\}\}\},\\
    S_{0,1,1} &= \{S_{0,0,0},S_{0,1,0},S_{0,0,1}\} = \{\{\},\{\{\}\}\},\\
    S_{0,1,2} &= \{S_{0,0,2},S_{0,1,0},S_{0,1,1}\} = \{\{\{\}\},\{\{\},\{\{\}\}\}\}.
    \end{aligned}
    $$
    
    Note that $S_{0,1,0}=S_{0,0,1}$, $S_{0,0,2}=S_{0,1,1}$.

A game can be represented by its initial state.

Although impartial game representations can be quite complex, single-pile Nim games are relatively simple. When there is only one pile with $n$ stones, it can be represented as

$$
*0 = \{\},~*n = \{*m : m<n,~m\in\mathbf N\} = \{*0,*1,\cdots,*(n-1)\}.
$$

Here, the notation $*n$ represents the single-pile Nim game (and its initial state) with $n$ stones.

???+ example "Example (continued)"
    Using this notation, the states in the example above can be simply represented as:
    
    $$
    S_{0,0,0} = *0,~
    S_{0,1,0} = S_{0,0,1} = *1,~
    S_{0,0,2} = S_{0,1,1} = *2,~
    S_{0,1,2} = \{*1, *2\}.
    $$

In subsequent discussion, the notation $T\in S$ should be understood as state $T$ being a successor of state $S$.

### Sums and Equivalence of Games

The equivalence relation of games depends on the concept of the sum[^more-sums] of games.

???+ note "Sum of Games"
    The **sum** (or **combined game**) of games $G$ and $H$, denoted $G+H$, is the game
    
    $$
    G + H = \{g + H : g \in G\} \cup \{G + h : h \in H\}.
    $$

The sum of games can be understood as a game consisting of two simultaneously played independent subgames. In each move, the player can and must choose exactly one subgame and move one step in it. The game ends when both subgames cannot be moved. The concept of game sum can be extended to any number of games, and satisfies both associative and commutative laws—that is, the result of combining multiple games does not depend on the order or grouping of combinations. Nim is the sum of multiple single-pile Nim games.

One observation is that, although in single-pile Nim games, all positions except the empty pile are N-positions, when these different single-pile Nim games are combined with other single-pile Nim games, the resulting games are not the same. For example, the game $*n$ only yields a P-position when combined with another $*n$; combining with any other game $*n'\neq *n$ yields an N-position.

This observation suggests that one can study the properties of a game by examining its sums with other games. This leads to the concept of game equivalence.

???+ abstract "Equivalence Relation of Games"
    If for all games $H$, both $G_1+H$ and $G_2+H$ are either P-positions or N-positions, then games $G_1$ and $G_2$ are said to be **equivalent**, denoted $G_1\approx G_2$.

It is easy to verify that $\approx$ as defined is indeed an [equivalence relation](../order-theory.md#binary-relations) on all impartial games.

### Sprague-Grundy Function

The analysis of Nim shows that different single-pile Nim games are not equivalent. However, all impartial games are equivalent to some single-pile Nim game. From this, we can assign a number to each impartial game—this is the Sprague-Grundy function.

To prove these conclusions, we first need to establish two lemmas about game equivalence. First, combining a P-position with any game yields a game equivalent to the original.

???+ note "Lemma 1"
    For any game $G$ and any P-position $A\in\mathcal P$, we have $G\approx G + A$.

??? note "Proof"
    By definition, we only need to prove that for any game $H$, $G+H\approx G+A+H$ holds.
    
    If game $G+H$ has a winning strategy, then game $G+A+H$ also has a winning strategy. If the opponent moves in subgame $A$, we move to restore it to a P-position; otherwise, we follow the winning strategy from $G+H$. This guarantees victory.
    
    If game $G+H$ is a P-position, then game $G+A+H$ is also a P-position. Because whether the current turn plays a move in subgame $G+H$ or subgame $A$, the opponent can restore the respective subgame to a P-position in the next turn. Eventually, the first player will have no legal moves.

Second, two games are equivalent if and only if their sum is a P-position. This lemma provides a method to prove two games are equivalent.

<a id="sg-lem-2"></a>

???+ note "Lemma 2"
    Games $G$ and $G'$ are equivalent if and only if $G+G'\in\mathcal P$ is a P-position.

??? note "Proof"
    If games $G$ and $G'$ are equivalent, then $G+G'$ and $G+G$ are both P-positions or both N-positions, while game $G+G$ is a P-position. This is because for any move by the first player, the second player can make the same move in the other subgame, and eventually the first player will have no moves.
    
    Conversely, if $G+G'$ is a P-position, then by Lemma 1, $G\approx G+(G+G') = (G+G)+G' \approx G'$.

Using these lemmas, we can obtain the following theorem:

???+ note "Theorem (Sprague-Grundy)"
    For any (finite) impartial game $G$, there exists $n\in\mathbf N$ such that $G\approx *n$ holds.

??? note "Proof"
    We prove this by mathematical induction. Let $G = \{G_1,G_2,\cdots,G_k\}$. By the induction hypothesis, there exist $n_1,n_2,\cdots,n_k$ such that $G_i\approx *n_i$. Consider the game
    
    $$
    G' = \{*n_1,*n_2,\cdots,*n_k\}.
    $$
    
    We need to prove that $G'\approx *m$, where $m=\operatorname{mex}\{n_1,n_2,\cdots,n_k\}$ is the smallest natural number not in the set.
    
    First, we need to show $G\approx G'$. By [Lemma 2](#sg-lem-2), we only need to prove that game $G+G'$ is a P-position. Assume $G\neq *0$. If the first player chooses $G_i$, then the second player can choose $*n_i$; conversely, if the first player chooses $*n_i$, the second player can choose $G_i$. In either case, after these two moves, the game becomes $G_i+*n_i$, which by Lemma 2 and $G_i\approx *n_i$ is a P-position. This proves $G\approx G'$.
    
    Second, we need to show $G'\approx*m$. By [Lemma 2](#sg-lem-2), we only need to prove $G'+*m$ is a P-position. Assume $G'\neq *0$. If the first player chooses $*n_i\in *m$, then by the definition of $m$, the second player can choose $*n_i\in G'$, making the position $*n_i + *n_i\in\mathcal P$, which is a P-position. If the first player chooses $*n_i\in G'$ and $n_i<m$, then the second player can choose $*n_i\in *m$, and the position again becomes $*n_i+*n_i\in\mathcal P$. If the first player chooses $*n_i\in G'$ and $n_i>m$, then the second player can choose $*m\in *n_i$, and the position becomes $*m+*m\in\mathcal P$. This proves $G'\approx *m$.
    
    By the transitivity of equivalence, $G\approx *m$. This completes the induction, proving that every game $G$ is equivalent to a single-pile Nim game.

This conclusion shows that we can assign a natural number $n$ to every impartial game $G$ such that $G\approx *n$.

???+ abstract "Nimber"
    The **nimber** of an impartial game $G$ is the unique natural number $n$ such that $G\approx *n$.

This function mapping impartial games to nimbers is called the **Sprague-Grundy function**, or simply the **SG function**, denoted $\operatorname{SG}(\cdot)$. Since every state of an impartial game is another impartial game, we can compute the corresponding nimber for each state of an impartial game, also called the SG function value.

From the proof of the theorem in this section, the Sprague-Grundy function can be computed recursively as follows:

???+ note "Corollary"
    For a state $x$ of an impartial game $G$, the Sprague-Grundy function value $\operatorname{SG}(x)$ satisfies
    
    $$
    \operatorname{SG}(x) = \operatorname{mex}\{\operatorname{SG}(x'): x'\in x\}.
    $$
    
    Here, $\operatorname{mex}(A):=\min\{n\in\mathbf N:n\notin A\}$ is the smallest natural number not in set $A$.

That is, the SG function value of a state equals the mex of the SG function values of all its successors.

Using the SG function values (nimbers), we can determine whether a state is an N-position.

???+ note "Corollary"
    A state $x$ in an impartial game $G$ is an N-position if and only if $\operatorname{SG}(x)\neq 0$.

Finally, the SG function value of a sum of games is the Nim sum (XOR) of the SG function values of the subgames.

???+ note "Theorem (Sprague-Grundy)"
    For impartial games $G_1,G_2,\cdots,G_n$,
    
    $$
    \operatorname{SG}(G_1+ G_2+\cdots + G_n) = \operatorname{SG}(G_1)\oplus \operatorname{SG}(G_2)\oplus\cdots\oplus\operatorname{SG}(G_n).
    $$

??? note "Proof"
    Since $*a_1+ *a_2 + \cdots + *a_n$ is the Nim game with stone counts $(a_1,a_2,\cdots,a_n)$, by the Nim results, the game
    
    $$
    *a_1+ *a_2 + \cdots + *a_n + *(a_1\oplus a_2\oplus\cdots\oplus a_n)
    $$
    
    is a P-position. By [Lemma 2](#sg-lem-2),
    
    $$
    *a_1+ *a_2 + \cdots + *a_n \approx *(a_1\oplus a_2\oplus\cdots\oplus a_n).
    $$
    
    Therefore,
    
    $$
    \operatorname{SG}(*a_1 + *a_2 + \cdots + *a_n) = a_1\oplus a_2\oplus\cdots\oplus a_n.
    $$
    
    Let $a_i=\operatorname{SG}(G_i)$, then $G_i\approx *a_i$. Using the algebraic properties of $\approx$,
    
    $$
    (G_1+ G_2+\cdots + G_n) + (*a_1 + *a_2 + \cdots + *a_n) = \sum_{i=1}^n(G_i+*a_i) \in\mathcal P.
    $$
    
    So we have
    
    $$
    \begin{aligned}
    \operatorname{SG}(G_1+ G_2+\cdots + G_n) &= \operatorname{SG}(*a_1 + *a_2 + \cdots + *a_n) \\
    &= a_1\oplus a_2\oplus \cdots \oplus a_n \\
    &= \operatorname{SG}(G_1)\oplus \operatorname{SG}(G_2)\oplus\cdots\oplus\operatorname{SG}(G_n).
    \end{aligned}
    $$

Using this theorem, computing the SG function values for sums of games can be greatly simplified.

Thus, we can summarize the method for computing SG function values:

-   For multiple independent games, compute their SG function values separately, then take the Nim sum;
-   For a single game, the SG function value of each state is the mex of the SG function values of all its successors;
-   In particular, terminal states (states with no successors) have SG function value $\operatorname{mex}\varnothing = 0$.

### Nimbers

Every impartial game uniquely corresponds to a nimber. The set of (finite) nimbers is the natural number set $\mathbf N$. However, its algebraic properties differ from those of natural numbers. Specifically, two operations can be defined on nimbers: Nim addition $\oplus$ and Nim multiplication $\otimes$:

???+ abstract "Operations on Nimbers"
    For nimbers $a,b$, we define:
    
    -   Nim addition: $a\oplus b=\operatorname{mex}(\{a'\oplus b:a'<a,~a'\in\mathbf N\}\cup\{a\oplus b':b'<b,~b'\in\mathbf N\})$,
    -   Nim multiplication: $a\otimes b=\operatorname{mex}(\{(a'\otimes b)\oplus(a\otimes b')\oplus(a'\otimes b'):a'<a,~b'<b,~a',b'\in\mathbf N\})$.

Under the operations $\oplus$ and $\otimes$, the set of all nimbers forms a [field](../algebra/basic.md#fields) of characteristic $2$. Moreover, these operations and their inverses are closed for the first $2^{2^n}$ nimbers; this gives rise to a series of [finite fields](../algebra/field-theory.md#finite-fields) $\mathbf F_{2^{2^n}}$ of size $2^{2^n}$.

## Common Impartial Games

Although the Sprague-Grundy theory completely solves the problem of impartial games, applying the Sprague-Grundy theorem directly is still inefficient for actual impartial games. For example, in Nim, brute-force computation of Sprague-Grundy values has exponential complexity. Therefore, it is common to discover the specific results for a given impartial game by tabulation.

This section lists some common impartial games and their results. When presenting results, this section only gives the rules for determining P-positions and N-positions. For the winning strategy, one simply makes moves that leave the opponent in a P-position. Since variants of these games often appear in algorithm competitions, it is important to master the proof process for each game's results.

???+ info "Proof Methods for the Results in This Section"
    The proofs of the results in this section are constructive verifications. For a game, the results describe the P-positions and N-positions. In the proof, one only needs to verify that from a P-position, one can only reach N-positions; and from an N-position, one can always reach at least one P-position. To turn these proofs into rigorous ones, one needs to construct the game graph and apply mathematical induction on the states in the graph; these verification steps form the induction part.

### Bachet's Game

Compared to single-pile Nim, Bachet's game restricts the number of stones that can be removed each turn.

???+ abstract "Bachet's Game"
    There is one pile of stones containing $n$ stones. Two players take turns removing at least $1$ and at most $k$ stones. The player who takes the last stone wins.

The following result holds:

???+ note "Theorem"
    The first player loses if and only if $n\equiv 0\pmod {k+1}$.

??? note "Proof 1"
    When $n\not\equiv 0\pmod {k+1}$, removing $n\bmod{(k+1)}\in[1,k]$ stones guarantees the opponent is in a P-position. Therefore, this is an N-position.
    
    Conversely, when $n\equiv 0\pmod {k+1}$, either there are no choices, or after you remove $k'$ stones, the opponent can immediately remove $k+1-k'$ stones, putting you back to a P-position.

??? note "Proof 2"
    As an application of the Sprague-Grundy theorem, we can compute $f(n)$ as the SG function value of the position with only $n$ stones remaining.
    
    For $n\le k$, we can prove inductively that $f(n)=n$. This is the same as single-pile Nim because the restriction on the number of stones removed has no effect. For $n>k$, we can prove $f(n)=n\bmod{(k+1)}$, so we have
    
    $$
    f(n) = \operatorname{mex}\{f(n-k),f(n-k+1),\cdots,f(n-1)\}.
    $$
    
    This iterates through all residues modulo $k+1$ except $n\bmod{(k+1)}$. Therefore, $f(n) = n\bmod{(k+1)}$.

### Moore's Nim-$k$ Game

Compared to Nim, Moore's Nim-$k$ game allows removing stones from up to $k$ piles in one move.

???+ abstract "Moore's Nim-$k$ Game"
    There are $n$ piles of stones, with the $i$-th pile containing $a_i$ stones. Two players take turns removing any positive number of stones from at least $1$ and at most $k$ piles, but must remove at least one stone. The player who takes the last stone wins.

The following result holds:

???+ note "Theorem"
    Write the number of stones in each pile in binary. For each bit position $d$, count how many piles have a $1$ in bit $d$, and compute this count modulo $(k+1)$. If for every bit position, this remainder equals $0$, the first player loses; otherwise, the first player wins.

??? note "Proof"
    Following the proof of the Nim result, this conclusion is easy to prove. Let $d$ be the highest binary bit where the remainder is non-zero, and let the corresponding remainder be $k'\le k$. The winning strategy is: among the piles with a $1$ in binary bit $d$, choose $k$ piles, and remove stones such that in the opponent's position, the remainder for each bit position is $0$. The only thing to verify is that the choice of how many stones to remove is always feasible.
    
    Specifically, once we select these $k'$ piles, removing $2^d$ stones from each pile will make the remainder at bit $d$ become $0$. For lower bit positions, distribute these remainders arbitrarily to any pile(s).

### Staircase Nim

Staircase Nim is slightly more complex; it allows stones to move between adjacent piles.

???+ abstract "Staircase Nim"
    There are $n$ piles of stones, with the $i$-th pile containing $a_i$ stones. Two players take turns, and in each move, they either remove any positive number of stones from the first pile, or move any positive number of stones from pile $i>1$ to pile $i-1$. They must make some move. The player who takes the last stone wins.

The following result holds:

???+ note "Theorem"
    The first player loses if and only if the Nim sum of the odd-numbered piles $a_1\oplus a_3\oplus\cdots\oplus a_{n-1+(n\bmod 2)}=0$.

??? note "Proof"
    Whenever a player moves stones from an even-numbered pile to an odd-numbered pile, the opponent can continue moving those stones to the next even-numbered pile (or remove them), so such moves do not affect the odd-numbered piles. At this point, each odd-numbered pile moving down to the adjacent even-numbered pile (or being removed) can be seen as independent single-pile Nim games. By the Sprague-Grundy theorem regarding sums of games, the SG function value of Staircase Nim is the Nim sum of the SG function values of these subgames. This yields the above conclusion.

### Fibonacci Nim

Fibonacci Nim is similar to Bachet's game: there is only one pile of stones, and the number that can be removed is limited. Unlike Bachet's game, the restriction on the number of stones removed is dynamic.

???+ abstract "Fibonacci Nim"
    There is one pile of stones containing $n$ stones. Two players take turns removing stones. The first player to move can remove any number of stones but cannot take all the stones; thereafter, the number of stones removed each turn cannot exceed twice the number of stones removed by the opponent on the previous turn. The number of stones removed each turn must be positive. The player who takes the last stone wins.

The following result holds:

???+ note "Theorem"
    At the start of the game, the first player loses if and only if the number of stones $n$ is a [Fibonacci number](../combinatorics/fibonacci.md).

??? note "Proof"
    Let $q$ be the quota for the number of stones that can be removed in the current position. Then on the first turn, $q=n-1$; and in subsequent turns, $q$ is twice the number of stones removed by the opponent on the previous turn. Consider the [Fibonacci representation](../combinatorics/fibonacci.md#fibonacci-coding) of the remaining number of stones $n$, which uniquely decomposes $n$ into a sum of non-adjacent positive Fibonacci numbers. What needs to be proven is that the current position is an N-position if and only if $q$ is greater than or equal to the smallest Fibonacci number in the decomposition of $n$.
    
    The winning strategy is: if possible, remove all remaining stones; otherwise, remove the smallest Fibonacci number in the decomposition. Since the second smallest Fibonacci number in the decomposition is strictly greater than twice the smallest, if the current turn in an N-position does not take all stones, the opponent cannot take the second smallest Fibonacci number (which becomes the smallest for the next turn) on the next turn, so the opponent must be in a P-position.
    
    Conversely, if currently in a P-position, let the number removed be $k$, which is strictly less than the smallest Fibonacci number $F$ in the current decomposition. Suppose the smallest Fibonacci number for the next turn is $F'$, which is also the smallest Fibonacci number in the decomposition of $F - k$. Let $F'=F''+F'''$ with $F''>F'''$, that is, $F''',F'',F'$ are three consecutive Fibonacci numbers. If $k<F''$, then when computing $k + (F-k)$ using Fibonacci representation, there is no carry, so we naturally cannot get $F$. Therefore, we must have $k\ge F''$. This shows that the next turn's quota $2k>F''+F'''=F'$, which is an N-position.

### Wythoff Game

Wythoff game allows removing stones from multiple piles simultaneously, but requires removing the same number of stones from each pile.

???+ abstract "Wythoff Game"
    There are two piles of stones containing $a_1$ and $a_2$ stones respectively. Two players take turns removing stones from one or both piles, must remove at least one stone, but when removing from both piles, the number of stones removed must be the same. The player who takes the last stone wins.

The following result holds:

???+ note "Theorem"
    Without loss of generality, assume $a_1\le a_2$. The first player loses if and only if $a_1 = \lfloor(a_2-a_1)\phi\rfloor$, where $\phi=(\sqrt{5}+1)/2$ is the golden ratio.

To prove this conclusion, we need the following lemma:

???+ abstract "Beatty Sequence"
    Let $r > 1$ be an irrational number. The Beatty sequence it generates is $\mathcal B_r = \{\lfloor kr\rfloor : k \in\mathbf N_+\}$.

???+ note "Rayleigh Theorem"
    Let $r,s > 1$ be two irrational numbers such that $\dfrac{1}{r}+\dfrac{1}{s}=1$. Then the sequences $\mathcal B_r$ and $\mathcal B_s$ form a partition of the positive integers $\mathbf N_+$. In this case, they are also called complementary Beatty sequences.

??? note "Proof"
    Let $\mathcal A_r=\{kr:k\in\mathbf N_+\}$. Consider sorting the elements of the set $\mathcal A=\mathcal A_r\cup\mathcal A_\ell$ to get the sequence $\{a_i\}_{i\in\mathbf N_+}$. We need to prove that $i=\lfloor a_i\rfloor$ holds for all $i\in\mathbf N_+$, which gives that $\mathcal B_r\cup\mathcal B_s$ is a partition of $\mathbf N_+$.
    
    First, we prove that the sequence contains no duplicate elements. Suppose otherwise: there exist $k,\ell\in\mathbf N_+$ such that $kr=\ell s$ holds. Then,
    
    $$
    \dfrac{\ell}{k} = \dfrac{r}{s} = r - 1.
    $$
    
    But the left side is a rational number while the right side is irrational—a contradiction. Therefore, the numbers in the sequence are all distinct.
    
    Second, we prove that among the elements of set $\mathcal A$, there are exactly $\lfloor a_i\rfloor$ numbers less than or equal to $a_i$. Assume $a_i\in\mathcal A_r$, i.e., $a_i=kr$. Then, by counting elements in $\mathcal A_r$ and $\mathcal A_\ell$ separately, we get that the number of positive integers less than or equal to $a_i$ is
    
    $$
    k + \left\lfloor\dfrac{kr}{s}\right\rfloor = k + \lfloor k(r-1)\rfloor = \lfloor kr\rfloor = \lfloor a_i\rfloor.
    $$
    
    Hence, since the sequence $\{a_i\}$ is strictly increasing, there are exactly $i$ numbers less than or equal to $a_i$. This gives $i=\lfloor a_i\rfloor$.

From this, we can prove the earlier conclusion.

??? note "Proof of the Wythoff Game Result"
    For all positions $(a_1,a_2)$ with $a_1 < a_2$ that are P-positions, let $k = a_2 - a_1 \in\mathbf N_+$. We have $a_1=\lfloor k\phi\rfloor$ and $a_2=\lfloor k(\phi+1)\rfloor$. Since $\phi$ is the golden ratio, $\dfrac{1}{\phi}+\dfrac{1}{\phi+1}=1$. By Rayleigh's theorem, the sequences $\{\lfloor k\phi\rfloor\}$ and $\lfloor k(\phi+1)\rfloor$ form a partition of $\mathbf N_+$. This means that among all P-positions $(a_1,a_2)$ with $a_1 < a_2$, the components $a_1$ and $a_2$ each take on every positive integer exactly once, and their difference $a_2-a_1$ also takes on every positive integer exactly once.
    
    Since in Wythoff game, a legal move either keeps one component unchanged or keeps the difference unchanged, from a P-position, one cannot reach another P-position with a single legal move. Conversely, for any N-position $(a_1,a_2)$, assume $a_1\le a_2$, and let $k=a_2-a_1$. If $a_1>\lfloor k\phi\rfloor$, then the first player can remove $(a_1 - \lfloor k\phi\rfloor)$ stones from each pile, making the position a P-position. Conversely, by the previous paragraph's conclusion, for this $a_1$, there exists exactly one P-position $(a_1,a_2')$. Furthermore, if $a_1 > a_2'$, obviously $a_2' < a_2$; otherwise, if $a_1 < a_2'$, then we can let $k'=a_2'-a_1$ such that $a_1=\lfloor k'\phi\rfloor$, and we have $a_1 < \lfloor k\phi\rfloor$, so $k' < k$, therefore $a_2'=a_1 + k' < a_1+k = a_2$. So as long as $a_1 < \lfloor k\phi\rfloor$, we must have $a_2' < a_2$, and the first player only needs to remove $(a_2-a'_2)$ stones from the second pile to make the position a P-position.

### Turning Turtles

Turning Turtles is also a common type of impartial combinatorial game.

???+ abstract "Turning Turtles"
    Let $(S,\preceq)$ be a [well-founded partial order](../order-theory.md). Let a mapping $f:S\rightarrow\mathcal P\mathcal P S$ satisfy: for all $s\in S$, the set $f(s)$ is non-empty; for all $T\in f(s)$, we have $s\in T$; and for all $t\in T$, we have $t\preceq s$. At each element of set $S$, there is a coin that may be heads up or tails up. Players take turns. In each move, a player chooses a coin $s$ that is heads up and a set $T\in f(s)$, and flips all coins in the set $T$. The player who flips all coins to tails up wins.

Turning Turtles is actually a large class of games. Depending on the specific choice of the partial order $S$ and the mapping $f$, the concrete form of Turning Turtles varies. In the game description, the conditions that the mapping $f$ must satisfy mean that whenever a player chooses a set $T$ of coins to flip, there must be a heads-up coin $s$ in $T$ such that all elements in $T$ are ranked before $s$. This ensures the game terminates after a finite number of moves.

???+ example "Examples"
    1.  Let $S=\{1,2,\cdots,n\}$ and $f(s)=\{\{t,s\}:t \le s\}$. This means there is a row of $n$ coins; flip one heads-up coin each move, and choose one coin to its left to flip.
    2.  Let $S=\{1,2,\cdots,n\}$ and $f(s)=\{[t,s]:t \le s\}$. This means there is a row of $n$ coins; flip a contiguous segment of coins each move, but must ensure that the rightmost coin in the segment was heads-up before flipping.
    3.  Let $S=\{1,2,\cdots,n\}^2$ and $f(s)=\{\{s\}\}$. This means there is an $n\times n$ grid of coins; flip only one heads-up coin each move.
    4.  Let $S$ be the set of nodes in a rooted tree, and $f(s)$ is the set of all subsets of the node set on the path from vertex $s$ to the root that contain $s$ itself. This means there is a rooted tree with a coin at each node; flip one heads-up coin each move, and choose some of its ancestor nodes' coins to flip.

Although there are many varieties of Turning Turtles, their solution approach is the same. For Turning Turtles $(S,f)$, let $G_s$ be the position where only the coin at element $s$ is heads-up. These positions are called base positions. Then any position $G$ can be viewed as the sum of games corresponding to these base positions. That is, the following result holds:

???+ note "Theorem"
    For Turning Turtles $(S,f)$ and position $G$, let $H(G)\subseteq S$ be the set of positions where coins are heads-up. The SG function value of position $G$ is
    
    $$
    \operatorname{SG}(G) = \bigoplus_{s\in H(G)}\operatorname{SG}(G_s).
    $$

??? note "Proof"
    Consider a related game: in a position $G'$, place some number of stones at each element of set $S$; on each move, a player can remove one stone from $s$ and choose a set $T\in f(s)$, then place one stone at each element in $T\setminus\{s\}$. For such games, we can also define a base position $G'_s$, which is the position with only one stone at position $s$. In this type of game, every position is the sum of base positions corresponding to all its stones. This is because when placing a new stone, by associating it with the removed stone, each stone appearing in the game can be associated with a stone in the initial position; consequently, the subgame processes of different stones in the initial position do not interfere with each other, and the entire game can be viewed as the sum of these subgames. Since base positions corresponding to stones at the same position have the same SG value, by the properties of XOR, the SG value of position $G'$ depends only on the parity of the number of stones at each position, not on the specific count. Therefore, for game position $G'$, if we let $H(G')$ be the set of positions with an odd number of stones, the analysis in this paragraph can be summarized as:
    
    $$
    \operatorname{SG}(G') = \bigoplus_{s\in H(G')} \operatorname{SG}(G'_s).
    $$
    
    Hence, the proof of the formula in the theorem only requires establishing the equivalence between game $G'$ and game $G$.
    
    To explain: for a new game position $G'$ and a Turning Turtles position $G$, if the positions with an odd number of stones in $G'$ are exactly the same as the positions with heads-up coins in $G$, then $G'$ and $G$ are equivalent. By [Lemma 2 of the Sprague-Grundy theorem](#sg-lem-2), this is equivalent to proving that position $G+G'$ is a P-position. The second player's winning strategy is simple: if the first player removes a stone from $s$ and there is more than one stone there, the second player directly imitates the first player's action; otherwise, the second player chooses the same $s$ and $T\in f(s)$ as the first player, but chooses the other subgame—in other words, if the first player removes a stone, the second player flips a coin, and vice versa. Since whatever the first player does, the second player can continue to act and ensure that in the remaining position, the positions with an odd number of stones match the positions with heads-up coins. Thus the game inevitably ends when the first player has no legal moves, so the first player loses. The theorem is thus proved.

Using this result, to determine whether a position is an N-position, one only needs to compute the SG function values of all base positions corresponding to heads-up coins, then take the Nim sum. These base position SG function values are not difficult to compute because their successors are given by the mapping $f$, and the SG values of successors can be computed inductively:

$$
\operatorname{SG}(G_s) = \operatorname{mex}\limits_{T\in f(s)}\bigoplus_{t\in T\setminus\{s\}}\operatorname{SG}(G_t).
$$

This provides a recurrence formula for base position SG function values.

### Bipartite Graph Game

Prerequisites: [Maximum Bipartite Matching](../../graph/graph-matching/bigraph-match.md)

For the final part of this section, we discuss the bipartite graph game. Although this game is often called the bipartite graph game, its description and proof of the result have nothing to do with the bipartite structure. Therefore, the result actually holds for general undirected graphs. However, finding the maximum matching in general graphs is more complex, so this result often appears in bipartite graph problems.

???+ abstract "Bipartite Graph Game"
    Two players take turns. The position facing each player consists of an undirected graph $G=(V,E)$ and a vertex $v\in V$. On a player's turn, if the current position is $(G,v)$, the player must choose a vertex $u$ adjacent to $v$. Then, delete vertex $v$ and all its incident edges from $G$ to get the remaining graph $G'$. The new position is $(G',u)$, which becomes the other player's turn. If at the start of a player's turn, the current vertex $v$ has no adjacent vertices in the graph (i.e., there is no legal move), that player cannot move and therefore loses the game.

The following result holds:

???+ note "Theorem"
    The first player wins if and only if vertex $v$ is a [maximum matching essential vertex](https://en.wikipedia.org/wiki/Dulmage%E2%80%93Mendelsohn_decomposition) of graph $G$, that is, vertex $v$ is matched in all maximum matchings of $G$.

??? note "Proof"
    First, assume vertex $v$ is a maximum matching essential vertex. Let $M$ be a maximum matching of $G$. In this case, the first player can move to the vertex $u$ matched with vertex $v$ in $M$. Since vertex $v$ appears in all maximum matchings of $G$, the size of the maximum matching of the remaining graph $G'$ is at most $|M|-1$; moreover, removing edge $(v,u)$ from $M$ gives a matching $M'$ of size $|M|-1$ in $G'$. Combining these two points, $M'$ is a maximum matching of $G'$. However, in the position faced by the second player, vertex $u$ is not a matched vertex in matching $M'$. Therefore, the second player must be in a P-position.
    
    Conversely, suppose there exists a maximum matching $M$ such that $v$ is an unmatched vertex. Since $M$ is a maximum matching, all vertices adjacent to $v$ must be matched vertices; otherwise, we could add the edge between them to $M$ to get a larger matching. Therefore, no matter what the first player chooses, the second player is in an N-position.

See the [Bipartite Graph Matching page](../../graph/graph-matching/bigraph-match.md#maximum-matching-essential-vertices) for algorithms to find maximum matching essential vertices in bipartite graphs.

Additionally, there is a variant of the bipartite graph game:

???+ abstract "Variant of the Bipartite Graph Game"
    Let $G=(V,E)$ be an undirected graph with one stone placed on each vertex. Two players take turns removing stones. At the start of the game, the first player can remove any one stone; on subsequent turns, each player must remove a stone from a vertex adjacent to the vertex where the opponent removed a stone on the previous turn. The first player who cannot remove a stone loses.

Clearly, this variant is equivalent to letting the first player choose the initial position, then starting the bipartite graph game with the second player as the first mover. Therefore, in this variant, the first player loses if and only if every vertex is a maximum matching essential vertex, that is, graph $G$ has a [perfect matching](../../graph/graph-matching/graph-match.md#definition).

## Misère Nim

This section discusses the solution of misère Nim.

???+ abstract "Nim Game"
    There are $n$ piles of stones, with the $i$-th pile containing $a_i$ stones. Two players take turns removing any positive number of stones from any single pile, but must remove at least one. The player who takes the last stone loses.

The following result holds:

???+ note "Theorem"
    In misère Nim, the position $(a_1,a_2,\cdots,a_n)$ is a P-position if and only if
    
    1.  There exists $i$ such that $a_i>1$, and the Nim sum $a_1\oplus a_2\oplus\cdots\oplus a_n=0$, or
    2.  For all $i$, $a_i\le 1$, and the number of non-empty piles is odd.

??? note "Proof"
    Since having no moves is an N-position, we can prove by induction that if every pile has exactly one stone, then an odd number of piles corresponds to an N-position, and an even number of piles corresponds to a P-position.
    
    Next, consider the case where some piles have more than one stone.
    
    Case A: If only one pile has more than one stone, then the Nim sum is certainly non-zero. Moreover, the first player can choose to move to a position where all piles have at most one stone, and can control the parity of the remaining non-empty piles. Therefore, this is an N-position.
    
    Case B: Now suppose more than one pile has more than one stone. Then no matter what move is made, the next position will have at least one pile with more than one stone. By the induction hypothesis, in the next position, first player loses corresponds to Nim sum zero, and first player wins corresponds to Nim sum non-zero. This is exactly the same as the induction hypothesis for normal Nim. Therefore, by repeating the Nim argument, the current position also satisfies that Nim sum zero corresponds to a P-position.

## Directed Graph Games

The impartial combinatorial games discussed in this article require that the same position cannot appear twice and there is no possibility of a draw. Therefore, the corresponding game graph is always a directed acyclic graph. This section relaxes this restriction and discusses how to classify each state as first-player win, first-player loss, or draw on general directed graphs.

The rules of the directed graph game are largely the same as other impartial combinatorial games: starting from the initial state, players take turns moving one step along the directed edges of the graph until there are no moves. Depending on whether the game is normal or misère, the last player unable to move is respectively the loser or winner. In such games, each state has three possible outcomes: first-player win, first-player loss, draw. In a draw, the game never terminates. Although slightly more complex, the [lemmas](#np-lem) about P-positions and N-positions still hold, and the remaining states are draws:

-   A state has a first-player-winning successor if and only if one of its successors is a P-position;
-   If a state has successors, it is a first-player-losing position if and only if all successors are N-positions;
-   If a state cannot be classified as an N-position or P-position, it is a draw.

To classify all states into these three categories, we can use an approach similar to [topological sorting](../../graph/topo.md):

1.  At initialization, record the outdegree of all states, push all states with outdegree zero into a queue, and mark them as P-positions or N-positions based on whether the game is normal or misère.
2.  Pop the state at the front of the queue. If it is a P-position, mark all its predecessors as N-positions; otherwise, the current state is an N-position, so decrease the outdegree of all its predecessors by one, and mark any predecessor whose outdegree becomes zero as a P-position. Push all predecessors that can be determined as N-positions or P-positions into the queue.
3.  The algorithm terminates when the queue is empty. States not yet classified as N-positions or P-positions are all draw positions.

This algorithm can classify all states in $O(|V|+|E|)$ time.

## Examples

This section discusses some typical example problems.

???+ example "[Luogu P2148 \[SDOI2009\] E&D](https://www.luogu.com.cn/problem/P2148)"
    There are $2n$ piles of stones. For $k=1,2,\cdots,n$, piles $2k-1$ and $2k$ are grouped together. Two players take turns, each time choosing a group of piles, removing one pile, and splitting the other pile into two non-empty piles placed in the two positions of that group. If all piles have only one stone, the current player has no legal moves and loses the game. Given the number of stones in each pile $\{a_i\}_{i=1}^{2n}$, determine whether it is a first-player winning position.

??? note "Solution"
    Clearly, the games for different groups are independent, so as long as we compute the SG function value for each group's game, we can compute the SG value of the whole game and determine whether it is a winning position. The key is how to compute the SG function value for each group of piles. This is not easy. The common approach for solving such game theory problems is tabulation. Let the SG value when a group has $(i,j)$ stones be $f(i,j)$. Writing a brute-force tabulation program gives the following results:
    
    ```text
    0 1 0 2 0 1 0 3 0 1 0 2 0 1 0 4 
    1 1 2 2 1 1 3 3 1 1 2 2 1 1 4 4
    0 2 0 2 0 3 0 3 0 2 0 2 0 4 0 4
    2 2 2 2 3 3 3 3 2 2 2 2 4 4 4 4
    0 1 0 3 0 1 0 3 0 1 0 4 0 1 0 4
    1 1 3 3 1 1 3 3 1 1 4 4 1 1 4 4
    0 3 0 3 0 3 0 3 0 4 0 4 0 4 0 4
    3 3 3 3 3 3 3 3 4 4 4 4 4 4 4 4
    0 1 0 2 0 1 0 4 0 1 0 2 0 1 0 4
    1 1 2 2 1 1 4 4 1 1 2 2 1 1 4 4
    0 2 0 2 0 4 0 4 0 2 0 2 0 4 0 4
    2 2 2 2 4 4 4 4 2 2 2 2 4 4 4 4
    0 1 0 4 0 1 0 4 0 1 0 4 0 1 0 4
    1 1 4 4 1 1 4 4 1 1 4 4 1 1 4 4
    0 4 0 4 0 4 0 4 0 4 0 4 0 4 0 4
    4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4
    ```
    
    This table has a clear pattern. One can observe that the table is divided into several $2\times 2$ matrices, with the top-left corner always being $0$, while the other three values are always the same. Therefore, we can compress this table by reducing each $2\times 2$ matrix to the common value (except the top-left corner):
    
    ```text
    1 2 1 3 1 2 1 4 
    2 2 3 3 2 2 4 4 
    1 3 1 3 1 4 1 4 
    3 3 3 3 4 4 4 4 
    1 2 1 4 1 2 1 4 
    2 2 4 4 2 2 4 4 
    1 4 1 4 1 4 1 4 
    4 4 4 4 4 4 4 4 
    ```
    
    One can find that this compressed table is the value at the same position in the original full table plus one. The problem is actually solved. Assuming zero-based indexing, the value $g(i,j)$ at position $(i,j)$ in the table is given by the following recurrence:
    
    $$
    g(i,j) =
    \begin{cases}
    0, & \text{if }2\mid i\text{ and }2\mid j,\\
    g(\lfloor i/2\rfloor,\lfloor j/2\rfloor)+1,& \text{otherwise}.
    \end{cases}
    $$
    
    The SG function we need is $f(i,j)=g(i-1,j-1)$. Using this recurrence, the algorithm can compute $f(i,j)$ in $O(\log\min\{i,j\})$ time.
    
    Of course, by simple induction, one can find that $g(i,j)$ is actually the minimum number of times we need to simultaneously divide both $i$ and $j$ by $2$ until both are even. In other words, it is the number of trailing $1$s in the bitwise OR of $i$ and $j$. From this, one can directly compute this value using `__builtin_ctz(~(i | j))`.
    
    In such problems, as long as one obtains the SG function expression by tabulation and observation, it is easy to prove by induction. Therefore, the key to solving these problems is to obtain these results in some form rather than derive them. For example, knowing the result, the recurrence in this problem can be inductively proved as follows. Let $S_k$ be the set of SG values of positions obtained by splitting $k$ stones into two non-empty piles. Then $f(i,j) = \operatorname{mex}(S_i \cup S_j)$. Hence $S_k$ has the recurrence:
    
    $$
    S_k = \{\operatorname{mex}(S_i \cup S_j) : i + j = k,~i,j\in\mathbf N_+\}.
    $$
    
    What needs to be proven is that $d\in S_k$ if and only if bit $d$ (with the lowest bit being bit $0$) of $(k-1)$ in binary is $1$.
    
    Using mathematical induction. The base case $S_1=\varnothing$ obviously holds. Assume the proposition holds for all positive integers less than $k$. Then $d\in S_k$ if and only if there exist $i,j\in\mathbf N_+$ such that $i+j=k$ and both $(i-1)$ and $(j-1)$ have at least one $1$ in bits $d' < d$, and both have $0$ at bit $d$. Obviously, such a split exists if and only if, considering only bits $0\sim d$, i.e., modulo $2^{d+1}$, the value of $(k-1)=(i-1)+(j-1)+1$ ranges in $[2^d,2^{d+1}-1)$. This condition is equivalent to bit $d$ of $(k-1)$ being $1$. Thus the induction step holds. The original proposition is proved.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/math/code/impartial-game/impartial-game-1.cpp"
    ```

???+ example "[Luogu P5675 \[GZOI2017\] Stone Game](https://www.luogu.com.cn/problem/P5675)"
    There are $n$ piles of stones, with the $i$-th pile containing $a_i$ stones. Two people play Nim. Now, any number of piles can be arbitrarily designated as the initial position, and one of them can be designated as the pile from which the first player must remove stones on the first move, but the number of stones removed cannot be specified. How many ways are there to make such designations so that the first player cannot win? Data satisfies $n,a_i\le 200$.

??? note "Solution"
    For such problems, we need to use the results of common games combined with other knowledge to solve them. Suppose the first player must remove stones from pile $i$, and the Nim sum of all designated piles is $v$. Then the first player cannot win if and only if $a_i \le a_i\oplus v$, that is, the number of stones $a_i$ in pile $i$ does not exceed the Nim sum $a_i\oplus v$ of the remaining piles (excluding pile $i$). Since the data range is very small, we can enumerate the pile designated for the first move; when enumerating pile $i$, the remaining piles can be selected or not selected, and the number of ways to get different Nim sums can be computed by DP. Summing the number of ways where the Nim sum is greater than or equal to $a_i$ gives the answer.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/math/code/impartial-game/impartial-game-2.cpp"
    ```

??? note "Reference Code"
    ```cpp
    --8<-- "docs/math/code/impartial-game/impartial-game-3.cpp"
    ```
