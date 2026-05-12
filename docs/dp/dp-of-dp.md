author: Hope666666

## Introduction

This article introduces the idea of DP of DP and demonstrates how it is applied to concrete problems through two examples.

## Idea

"DP of DP" refers to a method where, during dynamic programming, the process of solving a subproblem, usually itself a DP, is abstracted into an automaton (DFA), and then a new outer DP is designed on top of that automaton.

This technique is mainly used for **sequence counting**, **probability**, and **expectation** problems. A typical problem has the following structure:

-   Given an alphabet $\Sigma$ and a set $A\subseteq\Sigma^n$ of "valid sequences" of length $n$ over that alphabet. Depending on the alphabet, the sequence may be a binary string, a digit string, a state sequence, and so on.
-   For each concrete sequence $s\in\Sigma^n$, dynamic programming can determine whether it is valid, i.e. whether $s\in A$, compute its weight, or compute some related value.
-   Ultimately, we want to count all sequences in $A$, compute their total weight, expectation, and so on.

Enumerating all sequences is infeasible. Therefore, consider abstracting the process of determining whether a sequence is valid, namely the inner DP, into a [deterministic finite automaton](../misc/fsm.md#确定性有限状态自动机) (DFA). In general, for a fixed sequence $s\in\Sigma^n$, the state function of the inner DP can be written as $g(i,x;s)$, meaning the value of some quantity after processing the length-$i$ prefix of sequence $s$, with other state components equal to $x$. The corresponding transition equation of the inner DP is:

$$
g(i,\cdot;s) = G(g(i-1,\cdot;s),s_i).
$$

That is, the function $g(i,\cdot;s)$ is uniquely determined by the previous function $g(i-1,\cdot;s)$ and the current character $s_i$. If we regard the function $g(i,\cdot;s)$ as one state of an automaton, then the transition equation of the inner DP gives one automaton transition. Therefore, the automaton $(Q,\Sigma,\delta,q_0,F)$ corresponding to the inner DP has the following structure:

-   The state set $Q$ is the set of all possible functions $g(i,\cdot;s)$ corresponding to all possible $s\in\Sigma^n$ and $i=0,1,\cdots,n$.
-   The transition function $\delta:Q\times\Sigma\to Q$ is the function $G$ in the transition equation of the inner DP.
-   The initial state $q_0$ is usually obvious: it is the initial state of the inner DP.
-   The accepting-state set $F$ corresponds to all valid sequences $s\in A$.

The function $g(i,\cdot;s)$ itself may be quite complex. Therefore, in concrete problems, it is usually necessary to use [state compression](./state.md) or combine it with DFA minimization to compress the state space. This is the main reason DP of DP can significantly reduce time and space complexity compared with brute-force DP.

After abstracting the inner DP as a DFA, we can design a new DP on this DFA to solve the original problem; this is the outer DP. For convenience, take a simple counting problem as an example. Define the outer DP state function as $f(i,q)$, the number of prefixes of length $i$ that reach state $q\in Q$ in the DFA. Its transition equation is:

$$
f(i,q) = \sum_{c\in\Sigma}\sum_{q'\in Q:\delta(q',c)=q} f(i-1,q').
$$

The initial state is naturally $f(0,q_0)$, and the final answer can usually be computed simply from $\{f(n,q):q\in F\}$. The outer DP is essentially a special case of [DP on DAGs](./dag.md).

## Examples

The following two examples explain the general method of DP of DP in detail.

### Example 1

???+ example "[Hero meet devil](https://www.luogu.com.cn/problem/P10614)"
    Given a string $S$ over the alphabet `ACGT`, with $|S|\le 15$. For every $0\leq i\leq |S|$, find how many strings $T$ of length $m$ over the alphabet `ACGT` have longest common subsequence length $i$ with $S$.

??? note "Solution"
    A first DP idea is to let $f_{i,j}$ denote the number of length-$i$ strings $T$ whose LCS with $S$ has length $j$. However, this cannot transition directly. The main problem is that we do not know which characters correspond to this longest common subsequence.
    
    Consider the naive process for computing the LCS. Let $g_{i,j}$ denote the LCS length of the first $i$ characters of $T$ and the first $j$ characters of $S$. Then:
    
    $$
    g_{i,j} = \max\{g_{i-1,j},g_{i,j-1},g_{i-1,j-1}+[T_i=S_j]\}.
    $$
    
    We observe that for a fixed $i$, recording the one-dimensional array $g_i$ is enough to accurately maintain the LCS state between $S$ and the first $i$ characters of $T$. Since $S$ has length only $15$, this idea is feasible.
    
    Redefine the state $f_{i,x}$ as the number of length-$i$ strings $T$ for which the DP array with $S$, namely $g_i$, is in state $x$. This DP appears to have many states. However, because $g_{i,j}-g_{i,j-1}\in\{0,1\}$, we can maintain the difference array of $g_i$, giving $2^{|S|}$ states.
    
    Now consider transitions. If we know the array $g_i$ and also know $T_{i+1}$, then we can compute $g_{i+1}$ using the naive LCS transition, namely the DP equation above. Thus, the naive LCS becomes the inner DP that helps transition $f$.
    
    Therefore, enumerate $T_{i+1}$, compute the state $x'$ after transitioning from $x$, and add $f_{i,x}$ to $f_{i+1,x'}$. This completes the state transition of the outer DP. Finally, record $\textit{ans}_i$ as the answer for LCS length $i$. Enumerate every state $S$ and add $f_{m,S}$ to $\textit{ans}_{\operatorname{popcount}(S)}$.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/dp/code/dp-of-dp/dp-of-dp_1.cpp"
    ```

### Example 2

???+ example "[\[ZJOI2019\] Mahjong](https://loj.ac/p/3042)"
    Suppose there are $n$ tile ranks in mahjong, and each rank has $4$ tiles. A meld is either three consecutive ranks $i,i+1,i+2$ (a chow) or three identical ranks $i,i,i$ (a pung). A pair is two identical ranks $i,i$. A sequence of mahjong tiles is winning if and only if, regarded as a multiset, it can be decomposed into four melds and one pair, or into seven distinct pairs. Given $13$ tiles, find the expected number of additional draws needed until there exists a winning subsequence.

??? note "Solution"
    First, for a hand, we only need to consider the count of each tile rank, not their order. Therefore, for any prefix of any hand, we can convert it into a sequence of length $n$ where each position is in $0\sim 4$. Initially, if the count of the $i$-th tile is $a_i$, this is equivalent to restricting the value $x_i$ at position $i$ to integers in $[a_i,4]$. Note that the converted sequence does not consider draw order, while the tile sequence in the problem does consider order.
    
    Let $X$ denote the minimum number of draws needed to win. Directly computing $\mathbf E[X]$ is difficult, so use the following transformation. Let $h_i$ denote the number of sequences that are **not winning** after drawing $i$ tiles. In the corresponding mahjong tile sequence, these $i$ tiles must appear before the remaining $(4n-13-i)$ tiles, while the orders of these $i$ tiles and the remaining $(4n-13-i)$ tiles are arbitrary. Therefore, the number of mahjong tile sequences where the first $i$ drawn tiles still cannot win is:
    
    $$
    h_i\cdot i!(4n-13-i)!.
    $$
    
    Since the total number of mahjong tile sequences is $(4n-13)!$, the probability that the first $i$ drawn tiles still cannot win is:
    
    $$
    \mathbf P[X>i] = \dfrac{h_i\cdot i!(4n-13-i)!}{(4n-13)!}.
    $$
    
    Using the tail-sum formula, the desired expectation is:
    
    $$
    \mathbf E[X] = \sum_{i=0}^\infty\mathbf P[X>i] = 1 + \sum_{i=1}^{4n-13}\dfrac{h_i\cdot i!(4n-13-i)!}{(4n-13)!}.
    $$
    
    The problem is now transformed into computing $h_i$. We solve this with DP of DP.
    
    First, consider the inner DP: use dynamic programming to determine whether a converted sequence corresponds to a winning hand. The seven-pairs case is relatively easy, so focus on the first winning form. Let $g_{0/1,i,j,k}$ denote, after processing the first $i$ tile ranks, the maximum number of melds when $j$ groups of $(i-1,i)$ and $k$ tiles of rank $i$ remain, and a pair exists or does not exist (the $0/1$ dimension). If running DP on a sequence yields a number at least $4$ in $g_{1,n}$, then the sequence is winning.
    
    The transition of this DP is complicated, so discuss it in two steps. First, consider the transition of $g_{0/1,i}$. This means adding $x_i$ tiles of rank $i$ to the current hand shape without forming a new pair, and asking how the number of melds transitions. If, after adding $x_i$ tiles of rank $i$, we want to obtain $\ell$ chows, $j$ groups of $(i-1,i)$, and $k$ single tiles of rank $i$, then we should transition from $(g_{0/1,i-1})_{\ell,j}$; this choice avoids waste as much as possible. The remaining tiles $(x_i-\ell-j-k)$ are used to form as many pungs as possible. Enumerating all possibilities gives:
    
    $$
    \tilde G(g_{0/1,i-1}, x_i)_{j,k} = \max\left\{(g_{0/1,i-1})_{\ell,j} + \ell + \left\lfloor\dfrac{x_i-\ell-j-k}{3}\right\rfloor:\ell+j+k\le x_i\right\}.
    $$
    
    Second, consider the case where a pair is formed. When adding $x_i$ tiles of rank $i$, there are three transitions:
    
    -   Add $x_i$ tiles to $g_{0,i-1}$ and transition to $g_{0,i}$.
    -   Add $x_i$ tiles to $g_{1,i-1}$ and transition to $g_{1,i}$.
    -   If $x_i\ge 2$, add $x_i-2$ tiles to $g_{0,i-1}$ and transition to $g_{1,i}$.
    
    This gives all transitions from $g_{i-1}$ to $g_i$ after adding $x_i$ tiles.
    
    After solving the inner DP transition, build the **winning-hand automaton**. The automaton transitions are exactly the transitions of the inner DP above. We also need to decide how to represent each automaton state. Each state corresponds to one possible value of $g_i$, which has dimensions $(0/1,j,k)$. Since $j$ and $k$ represent retained groups $(i-1,i)$ and single $i$ tiles used to form future chows, and since three identical chows can always be reorganized into three pungs, it is only necessary to consider demands for at most $2$ identical chows. Thus, each hand shape only needs to retain at most $2$ of each type, meaning $j,k\in\{0,1,2\}$. Therefore, $g_i$ can be represented as a $2\times3\times3$ array. Additionally, to maintain the seven-pairs winning form, add a counter to each state indicating the current maximum number of pairs.
    
    Each element of array $g_i$ may take values in $\{-\infty\}\cup\mathbf N$. However, since having at least $4$ melds is already winning, cap every value at $4$. Since adding any tile to a winning sequence still leaves a winning sequence, DFA minimization can be used to compress all winning states into one state. Therefore, for non-winning states, each position only needs values in $\{-\infty\}\cup\{0,1,2,3\}$. In implementation, $-\infty$ is represented by $-1$.
    
    Even so, there are still many theoretically possible states: $1+7\times5^{18}$. Enumerating them is unrealistic. In fact, most of these possibilities never actually appear in the winning-hand automaton. To avoid considering nonexistent states, use BFS: start from the initial state and expand states step by step until reaching winning states. The automaton obtained this way has $N=2092$ states.
    
    Finally, consider DP on the winning-hand automaton, namely the outer DP. Let $f_{i,j,k}$ denote the number of sequences after processing the $i$-th tile rank, having drawn $j$ tiles in total, and reaching state $k$ in the winning-hand automaton. During transition, enumerate the number of drawn tiles $0\leq t\leq4-a_i$, where $a_i$ is the number of tiles of rank $i$ used in the initial $13$ tiles. Multiply the previous sequence count by the number of ways to choose $t$ tiles from the remaining $4-a_i$ tiles, $\dbinom{4-a_i}{t}$, and accumulate. Formally:
    
    $$
    f_{i+1,j+t,k'} = \sum_{t=0}^{4-a_i}\dbinom{4-a_i}{t}f_{i,j,k}.
    $$
    
    Here, $k'=\delta(k,a_i+t)$ is the state after adding $a_i+t$ tiles to automaton state $k$. After the outer DP finishes, the number of sequences that have drawn $i$ tiles and still are not winning is:
    
    $$
    h_i=\sum_{j=1}^{N} f_{n,i,j}.
    $$
    
    Substituting this into the expression above gives the required expectation.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/dp/code/dp-of-dp/dp-of-dp_2.cpp"
    ```

## Exercises

-   [CF979E Kuro and Topological Parity](https://codeforces.com/problemset/problem/979/E)
-   [TJOI2018 Amusement Park](https://loj.ac/p/2575)
-   [NOI2022 Stone Removal](https://loj.ac/p/3848)
