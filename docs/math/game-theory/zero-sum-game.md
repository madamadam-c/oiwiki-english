Prerequisites: [Introduction to Game Theory](./intro.md)

This article discusses (two-player) [zero-sum games](./intro.md#zero-sum-and-non-zero-sum-games).

In zero-sum games, the sum of payoffs for both players is always zero; one player's gain necessarily means the other player's loss. Zero-sum games can be viewed as a special case of constant-sum games. However, any constant-sum game can be equivalently transformed into a zero-sum game by adding or subtracting a constant to or from one player's payoff. Therefore, we only need to discuss zero-sum games.

In algorithm competitions, zero-sum games commonly encountered can be roughly divided into two categories: sequential zero-sum games and simultaneous zero-sum games.

## Sequential Zero-Sum Games

In sequential zero-sum games, two players take turns until the game terminates.

In sequential zero-sum games, the players' payoff functions exhibit a recursive structure. A game position $S$ can be divided into three categories: terminal positions $S_0$, positions where player $1$ moves $S_1$, and positions where player $2$ moves $S_2$. Suppose at terminal position $s\in S_0$, player $1$'s payoff is $v(s)$, and accordingly, player $2$'s payoff is $-v(s)$. Therefore, when it is player $2$'s turn to move, maximizing their payoff is equivalent to minimizing player $1$'s payoff. Thus, assuming both players adopt optimal strategies, the maximum payoff $V(s)$ that player $1$ can obtain at position $s\in S$ satisfies the following recurrence:

$$
V(s) = \begin{cases}
v(s), & s \in S_0,\\
\max_{t\in s} V(t), & s\in S_1,\\
\min_{t\in s} V(t), & s\in S_2.
\end{cases}
$$

Here, $t\in s$ denotes that $t$ is a successor of $s$. This is the [minimax idea](../../search/alpha-beta.md#minimax-algorithm).

When applying this algorithm to practical problems, there are usually the following specific methods:

-   If the number of positions in the game is small, one can directly implement this algorithm by brute force.

-   If the number of positions is large and has no special structure, one can consider using [alpha-beta pruning](../../search/alpha-beta.md#alpha-beta-pruning) combined with other search pruning algorithms.

-   If a single position in the game is often a successor of multiple positions, memoized search or other dynamic programming algorithms can be considered to avoid redundant search.

-   If the players' final payoff is the sum of payoffs from all moves before game end, one can optimize the modeling approach. Specifically, suppose when reaching terminal position $s\in S_0$, player $i=1,2$'s action sequences are $\{a^{(i)}_j\}_{j=1}^{k_i}$, the payoff corresponding to action $a$ is $w(a)$, and player $1$'s payoff function is

    $$
    v(s) = \sum_{j=1}^{k_1}w(a_j^{(1)}) - \sum_{j=1}^{k_2}w(a_j^{(2)}).
    $$

    Then, we can define $\tilde V(s)$ as the maximum score the current player can achieve in the game from position $s\in S$ onwards. For the initial state $s_0$, we have $V(s_0)=\tilde V(s_0)$, so finding $\tilde V(\cdot)$ is sufficient to solve the original problem. For $\tilde V(\cdot)$, we have the following recurrence:

    $$
    \tilde V(s) = \begin{cases}
    0, & s \in S_0, \\
    \max_{t\in s} w(a_{s\to t}) - \tilde V(t), & s\in S_1\cup S_2.
    \end{cases}
    $$

    Here, $a_{s\to t}$ denotes the action that can transition from state $s$ to $t$; if there are multiple such actions, take the one with the highest payoff $w(a)$.

-   Impartial combinatorial games are all sequential zero-sum games. One only needs to set the payoffs for the winning and losing players as $+1$ and $-1$ respectively. In this case, the recurrence for the payoff function $V(\cdot)$ is essentially the [lemma](./impartial-game.md#game-graph-and-states) for determining N-positions and P-positions.

    A common variant of such problems is finding the minimum number of rounds the winning player needs or the maximum number of rounds the losing player can persist. To do this, one only needs to note that when performing BFS from terminal positions and classifying N-positions and P-positions according to the lemma, the number of rounds at which each position is classified is the desired number of rounds. This is because to classify a position as an N-position, it only needs one successor to be a P-position, which is always the P-position with the smallest number of rounds among successors; to classify a position as a P-position, it needs all successors to be N-positions, which is always the N-position with the largest number of rounds among successors.

    This method can also be extended to general [directed graph games](./impartial-game.md#directed-graph-games).

### Example Problem

???+ example "[Codeforces 794 E. Choosing Carrot](https://codeforces.com/problemset/problem/794/E)"
    Let there be a sequence of numbers ${a_i}$ of length $n$. Two players $1$ and $2$ take turns taking one number from either end of the sequence until only one number remains. Player $1$'s goal is to maximize this last remaining number, and player $2$'s goal is to minimize it. Before the game officially starts, player $1$ can also make $k$ moves first. Assuming both players use optimal strategies throughout, find the number that remains at the end of the game for each $k = 0,1,2,\cdots,n-1$. Here $1 \le n \le 3\times 10^5$.

??? note "Solution"
    Since no matter how both players take numbers, the remaining portion of the sequence is always a contiguous interval. Therefore, the position in the game can be described solely by the interval $[l,r]$ and the current player $i=1,2$, and can be solved using dynamic programming. Let $f(l,r,i)$ be the number that remains at the end of the game when the position is described by $(l,r,i)$. From the previous analysis, when $l < r$, this function satisfies the state transition equations:
    
    $$
    \begin{aligned}
    f(l,r,1) &= \max\{f(l+1,r,2),f(l,r-1,2)\},\\
    f(l,r,2) &= \min\{f(l+1,r,1),f(l,r-1,1)\}.
    \end{aligned}
    $$
    
    The terminal condition is $f(l,l,1)=f(l,l,2) = a_l$. Based on this, all possible position function values can be computed in $\Theta(n^2)$ time. For each $k$, the answer is
    
    $$
    g(k) = \max f(l,r,1) \text{ subject to } r - l + 1 = k.
    $$
    
    This algorithm cannot pass the original problem's data limits, so we need to optimize the transitions. There are many approaches here; this article provides only one of them.
    
    Consider the state transition equations as operations on the entire sequence. The two transition equations represent obtaining a new sequence by taking the maximum and minimum of adjacent numbers respectively. Let's call these the "maximization operation" and "minimization operation" respectively. Each operation reduces the sequence length by one. All intervals of length $d$ correspond to $(n-d+1)$ results, which is equivalent to performing $(d-1)$ operations on the sequence. Additionally, to obtain the result of $f(l,r,1)$, we need to ensure that the last operation is a maximization operation. Therefore, these operation sequences always end with a maximization operation.
    
    Consider the effect of two consecutive operations on the sequence. Suppose we first do a minimization operation, then a maximization operation. In this case, the sequence $a_1,a_2,a_3$ becomes
    
    $$
    \max\{\min\{a_1,a_2\},\min\{a_2,a_3\}\}.
    $$
    
    Enumerating all possible size relationships between $a_1,a_2,a_3$, we find that except for the case where $a_1 < a_2$ and $a_2 > a_3$ (i.e., $a_2$ is a strict local maximum), this expression always equals $a_2$. In other words, if a sequence has no strict local maximum points, then two consecutive operations on it only have the effect of deleting one number from each end. This obviously greatly simplifies the transitions. The remaining unique question is: how to ensure the sequence has no strict local maximum points? In fact, performing a maximization operation on the sequence once can ensure there are no strict local maximum points. Therefore, the results of all even numbers of operations can be obtained by taking the sequence resulting from two operations on the initial sequence, then deleting one number from each end in pairs; the results of all odd numbers of operations can be obtained by taking the sequence resulting from one operation on the initial sequence, then deleting one number from each end in pairs.
    
    Since the complete operation on the sequence needs to be performed at most $3$ times, and the subsequent answer computation only needs $2$ passes, the total time complexity of this algorithm is $\Theta(n)$.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/math/code/zero-sum-game/zero-sum-game-1.cpp"
    ```

### Practice Problems

-   [Luogu P2734 \[USACO3.3\] A Game](https://www.luogu.com.cn/problem/P2734)
-   [Luogu P4576 \[CQOI2013\] Board Game](https://www.luogu.com.cn/problem/P4576)
-   [Luogu P7097 \[yLOI2020\] Puppet Show](https://www.luogu.com.cn/problem/P7097)
-   [Codeforces 388 C. Fox and Card Game](https://codeforces.com/problemset/problem/388/C)
-   [Codeforces 794 E. Choosing Carrot](https://codeforces.com/problemset/problem/794/E)
-   [Codeforces 1628 D2. Game on Sum (Hard Version)](https://codeforces.com/problemset/problem/1628/D2)
-   [Luogu P3210 \[HNOI2010\] Stone-removing Game](https://www.luogu.com.cn/problem/P3210)

## Simultaneous Zero-Sum Games

In simultaneous zero-sum games, both players act simultaneously.

Simultaneous zero-sum games are typically represented using a payoff matrix. Suppose player $i=1,2$'s action sets are $A_i$, and when players $i=1,2$ take actions $a_i\in A_i$ respectively, the payoffs for both players are $v(a_1,a_2)$ and $-v(a_1,a_2)$ respectively.

???+ example "Example"
    Consider the rock-paper-scissors game. Suppose winning gives $1$ point, losing gives $-1$ point, and a draw gives $0$ points. Then the payoffs for both players can be represented as
    
    $$
    \begin{pmatrix}
    0,0 & 1,-1 & -1,1 \\
    -1,1 & 0,0 & 1,-1 \\
    1,-1 & -1,1 & 0,0
    \end{pmatrix}.
    $$
    
    A general two-player simultaneous game can also be represented in a similar form, hence also called a [bimatrix game](https://en.wikipedia.org/wiki/Bimatrix_game). For zero-sum games, since player $1$'s payoff matrix and player $2$'s payoff matrix are negatives of each other, we only need to consider player $1$'s payoff matrix:
    
    $$
    V = (v(a_1,a_2))_{(a_1,a_2)\in A_1\times A_2} = \begin{pmatrix}
    0 & 1 & -1 \\
    -1 & 0 & 1 \\
    1 & -1 & 0
    \end{pmatrix}.
    $$

The problem to solve is: given a payoff matrix $V = (v(a_1,a_2))_{(a_1,a_2)\in A_1\times A_2}$, how do we find the optimal strategies for both players and the maximum payoff?

### Mixed Strategies

Compared to sequential zero-sum games, the roles of the two players in simultaneous games are symmetric. However, since we have solved sequential zero-sum games, consider the sequential version of a simultaneous game. For example, if we assume player $1$ moves first and player $2$ moves second, then according to the previous discussion, player $1$'s payoff at the end of the game will be given by

$$
w_-=\max_{a_1\in A_1}\min_{a_2\in A_2} v(a_1,a_2)
$$

Since player $1$'s action is unilaterally transparent to player $2$, this should be the worst result player $1$ can achieve. Symmetrically, if we assume player $2$ moves first, player $1$'s payoff will be given by

$$
w_+ = \min_{a_2\in A_2}\max_{a_1\in A_1} v(a_1,a_2)
$$

Since player $2$'s action is unilaterally transparent to player $1$, this should be the best result player $1$ can achieve. Player $1$ should expect the actual payoff during the game to be $w\in[w_-,w_+]$. Although the inequality $w_-\le w_+$ always holds (proof see [Weak Duality Theorem](../linear-programming.md#duality-principle)), since equality may not hold, using only sequential game analysis methods, we generally cannot uniquely determine the game outcome.

???+ example "Example (continued)"
    In rock-paper-scissors, if moves were sequential, the first player would lose and the second player would win. Translated into mathematical language, this is the following inequality:
    
    $$
    w_- = -1 \le +1 = w_+.
    $$
    
    Here, $w_-\neq w_+$ does not hold.

The above analysis overlooks a key factor of simultaneous games: players cannot accurately predict the opponent's actions. Formally, this means both players can adopt some random strategy. This idea does not hold in the context of sequential games because no matter how the first player randomly chooses an action, the second player can always accurately observe this action and respond accordingly. However, for simultaneous games, the strategic ambiguity introduced by random strategies makes it impossible for the opponent to effectively target the player's actions.

???+ example "Example (continued)"
    In rock-paper-scissors, if player $1$ uniformly randomly chooses one of the three actions—scissors, rock, or paper—then depending on player $2$'s action, player $1$'s possible payoffs are
    
    $$
    \frac{1}{3}(0,1,-1)^T + \frac{1}{3}(-1,0,1)^T + \frac{1}{3}(1,-1,0)^T = (0,0,0)^T.
    $$
    
    In this case, no matter how player $2$ chooses, player $1$'s expected payoff is always $0$. This is obviously better than deterministically choosing a single action.

This leads to the concept of mixed strategies.

???+ abstract "Mixed Strategy"
    In a simultaneous game, player $i$'s **mixed strategy** is a function $s_i:A_i\to[0,1]$ such that $\sum_{a_i\in A_i}s_i(a_i)=1$. That is, strategy $s_i$ is a probability distribution over player $i$'s action set $A_i$. The set of all mixed strategies for player $i$ is denoted $S_i=\Delta(A_i)$, where $\Delta(A_i)$ represents the set of all probability distributions over $A_i$. If $s_i$ is a degenerate probability distribution, i.e., there exists $a\in A_i$ such that $s_i(a)=1$, then strategy $s_i$ is also called a **pure strategy**.

The payoff of a mixed strategy is the expected value of individual action payoffs:

$$
v(s_1,s_2) = \sum_{a_1\in A_1}\sum_{a_2\in A_2}s_1(a_1)s_2(a_2)v(a_1,a_2).
$$

Treating individual actions as corresponding pure strategies, we can embed the action set $A_i$ into the (mixed) strategy set $S_i$, and the above $v(s_1,s_2)$ can be seen as extending $v(a_1,a_2)$ from $A_1\times A_2$ to $S_1\times S_2$.

### von Neumann's Theorem

After introducing mixed strategies, the results obtained from maximin and minimax are consistent, and therefore the outcome of simultaneous zero-sum games is also uniquely determined.

???+ note "Theorem (von Neumann)"
    In simultaneous zero-sum games allowing mixed strategies, if both players adopt optimal strategies, player $1$'s maximum payoff is
    
    $$
    w = \max_{s_1\in S_1}\min_{s_2\in S_2} v(s_1,s_2) = \min_{s_2\in S_2}\max_{s_1\in S_1} v(s_1,s_2),
    $$
    
    and player $2$'s maximum payoff is $-w$.

??? note "Proof"
    Let $w = \max_{s_1\in S_1}\min_{s_2\in S_2} v(s_1,s_2)$. Consider the inner minimization problem. Since $v(s_1,s_2)=\sum_{a_2\in A_2}s_2(a_2)v(s_1,a_2)$, we have $\max_{s_2\in S_2}v(s_1,s_2)=\max_{a_2\in A_2}v(s_1,a_2)$, and the optimal solution of the former is the optimal solution of the latter corresponding to a pure strategy. Therefore, $w = \max_{s_1\in S_1}\min_{a_2\in A_2} v(s_1,a_2)$. Then, introducing an auxiliary variable $u$, the problem can be rewritten as
    
    $$
    w = \max_{s_1\in S_1} u \text{ subject to }u \le \min_{a_2\in A_2} v(s_1,a_2).
    $$
    
    Because this constraint is equivalent to $u\le v(s_1,a_2)$ for all $a_2\in A_2$. Finally, introducing the definition of mixed strategy $s_1$ and the expression for the payoff function $v(s_1,a_2)$, the original problem is equivalent to a [linear programming problem](../linear-programming.md)
    
    $$
    (P) \qquad
    \begin{aligned}
    w = \max_{u,s_1}\; & u\\
    \text{subject to }& \sum_{a_1\in A_1}s_1(a_1)v(a_1,a_2) \ge u,~\forall a_2\in A_2,\\
    & \sum_{a_1\in A_1}s_1(a_1) = 1,\\
    & s_1(a_1) \ge 0,~\forall a_1\in A_1.
    \end{aligned}
    $$
    
    This problem is clearly feasible and has an optimal solution. According to the [duality principle](../linear-programming.md#duality-principle), its optimal solution equals the optimal solution of the dual problem:
    
    $$
    (D) \qquad
    \begin{aligned}
    w = \min_{t,s_2}\; & t\\
    \text{subject to }&\sum_{a_2\in A_2}s_2(a_2)v(a_1,a_2) \le t,~\forall a_1\in A_1,\\
    &\sum_{a_2\in A_2}s_2(a_2) = 1,\\
    &s_2(a_2)\ge 0,~\forall a_2\in A_2.
    \end{aligned}
    $$
    
    Repeating the steps from earlier, this problem is equivalent to $\min_{s_2\in A_2}\min_{s_1\in S_1}v(s_1,s_2)$. The theorem is proved.

This result is precisely the [Nash equilibrium](https://en.wikipedia.org/wiki/Nash_equilibrium) for this game. That is, assuming both players choose the equilibrium strategy, no player can strictly benefit by deviating from the equilibrium strategy.

### Transforming into Linear Programming

The proof of von Neumann's theorem also points to a method for solving simultaneous zero-sum games. Let $n$ and $m$ be the numbers of actions available to player $1$ and player $2$ respectively. Given player $1$'s payoff matrix $V\in\mathbf R^{n\times m}$, one can solve the following linear programming problem:

$$
\begin{aligned}
w = \max_{(u,s)\in\mathbf R\times\mathbf R^n}\; & u\\
\text{subject to }& V^Ts \ge u\mathbf 1,\\
& \mathbf 1^Ts = 1,\\
& s \ge 0.
\end{aligned}
$$

This is a linear programming problem of size $\Theta(n+m)$, which can be efficiently solved using the [simplex method](../simplex.md). The optimal solution $s$ obtained from the algorithm is player $1$'s optimal (mixed) strategy. To obtain player $2$'s optimal strategy, one only needs to obtain the dual variables (shadow prices) of the optimal solution from the simplex tableau.

### Practice Problems

-   [Luogu P4232 Hide and Seek Beyond the Unconscious](https://www.luogu.com.cn/problem/P4232)

## References and Notes

-   [Zero-sum game - Wikipedia](https://en.wikipedia.org/wiki/Zero-sum_game)
-   [Minimax theorem - Wikipedia](https://en.wikipedia.org/wiki/Minimax_theorem)
