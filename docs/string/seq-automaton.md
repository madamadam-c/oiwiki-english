Before reading this article, please read [automaton](../misc/fsm.md) first.

## Definition

A sequence automaton is an automaton that accepts and only accepts subsequences of a string.

In this article, $s$ denotes this string.

### States

If $s$ contains $n$ characters, then the sequence automaton contains $n+1$ states.

Let $t$ be a subsequence of $s$, then $\delta(start, t)$ is the position where $t$ first appears in $s$.

That is, a state $i$ represents the difference set between subsequences of prefix $s[1..i]$ and subsequences of prefix $s[1..i-1]$.

All states on the sequence automaton are accepting states.

### Transitions

From the state definition, we can get $\delta(u, c)=\min\{i|i>u,s[i]=c\}$, which is the position where character $c$ appears next.

Why is it the position of the "next" occurrence? Because if $i>j$, the subsequences of suffix $s[i..|s|]$ are a subset of the subsequences of suffix $s[j..|s|]$, so choosing the earlier one is always optimal.

## Implementation

Scan from back to front, maintaining the earliest occurrence position of each character during the process:

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{A string } S\\
2 & \textbf{Output. } \text{The state transition of the sequence automaton of }S \\
3 & \textbf{Method. }  \\
4 & \textbf{for }c\in\Sigma\\
5 & \qquad next[c]\gets null\\
6 & \textbf{for }i\gets|S|\textbf{ downto }1\\
7 & \qquad next[S[i]]\gets i\\
8 & \qquad \textbf{for }c\in\Sigma\\
9 & \qquad\qquad \delta(i-1,c)\gets next[c]\\
10 & \textbf{return }\delta
\end{array}
$$

The time complexity of this construction is $O(n|\Sigma|)$.

## Example Problems

???+ example "[「HEOI2015」Shortest Uncommon Substring](https://loj.ac/problem/2123)"
    You are given two strings $A$ and $B$ consisting of lowercase English letters ($1\le |A|, |B|\le 2000$), find:
    
    1. A shortest substring of $A$ that is not a substring of $B$;
    2. A shortest substring of $A$ that is not a subsequence of $B$;
    3. A shortest subsequence of $A$ that is not a substring of $B$;
    4. A shortest subsequence of $A$ that is not a subsequence of $B$.

??? note "Solution"
    Questions 1 and 3 of this problem require a suffix automaton, and the approaches are similar. Here I will only explain questions 2 and 4.
    
    Question 2 is relatively simple: enumerate substrings of $A$ and feed them into the sequence automaton of $B$. If it is not accepted, record it as an answer.
    
    Question 4 requires DP. Let $f(i, j)$ represent the number of additional characters needed to make it not a common subsequence when in state $i$ of the sequence automaton of $A$ and state $j$ of the sequence automaton of $B$. The state transition equation is:
    
    $$
    f(i, j)=\min_{\delta_A(i,c)\ne \textit{null}}f(\delta_A(i, c), \delta_B(j, c))+1.
    $$
    
    The starting point of the transition is $f(i, \textit{null})=0$.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/string/code/seq-automaton/seq-automaton_1.cpp"
    ```