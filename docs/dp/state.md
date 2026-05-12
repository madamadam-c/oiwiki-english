## Introduction

Bitmask DP is a type of dynamic programming that represents a set of states as an integer inside the DP state, enabling state transitions through compressed state representations.

To achieve lower time complexity, it is usually necessary to find a state representation with fewer possible states. Most problems use binary states, representing $n$ independent binary states with an $n$-bit binary number.

State compression usually involves bit operations. For basic bit operations, see [Bit Operations](../math/bit.md).

## Example 1

???+ note "[SCOI2005 Non-attacking Kings](https://loj.ac/problem/2153)"
    Place $K$ kings on an $N\times N$ chessboard ($1 \leq N \leq 9, 1 \leq K \leq N \times N$) so that no two kings attack each other. Count the number of valid placements.
    
    A king can attack one adjacent square in each of the eight directions: up, down, left, right, upper-left, lower-left, upper-right, and lower-right.

### Explanation

Let $f(i,j,l)$ denote the number of valid schemes after processing the first $i$ rows, where the state of row $i$ is $j$, and $l$ kings have already been placed on the board.

For the state numbered $j$, use the binary integer $sit(j)$ to represent the king placement. A binary bit of $sit(j)$ equal to $0$ means no king is placed at the corresponding position, and a bit equal to $1$ means a king is placed there. Let $sta(j)$ denote the number of kings in this state, i.e. the number of $1$ bits in $sit(j)$. For example, the state shown below can be represented by the binary number $100101$ (the left side of the board corresponds to the low binary bits), so $sit(j)=100101_{(2)}=37$ and $sta(j)=3$.

![](./images/SCOI2005-互不侵犯.png)

Let the current row state be $j$ and the previous row state be $x$. The following transition equation is obtained: $f(i,j,l) = \sum f(i-1,x,l-sta(j))$.

Let $x$ be the state number of the previous row. Under the condition that the current row and previous row do not conflict, enumerate all possible $x$ and transition with:

$$
f(i,j,l) = \sum f(i-1,x,l-sta(j))
$$

### Implementation

??? note "Reference Code"
    ```cpp
    --8<-- "docs/dp/code/state/state_1.cpp"
    ```

## Example 2

???+ note "[\[POI2004\] PRZ](https://www.luogu.com.cn/problem/P5911)"
    There are $n$ people who need to cross a bridge. The $i$-th person has weight $w_i$ and takes time $t_i$ to cross. The people are divided into several groups when crossing; only after every person in one group has crossed can the next group cross. The bridge has maximum load $W$. Find the minimum time for everyone to cross.
    
    $100\le W \le 400$, $1\le n\le 16$, $1\le t_i\le 50$, $10\le w_i\le 100$.

### Explanation

Use $S$ to denote a subset of all people. Let $t(S)$ denote the maximum crossing time among people in $S$, $w(S)$ denote the total weight of all people in $S$, and $f(S)$ denote the minimum time for all people in $S$ to cross. Then:

$$
\begin{cases}
    f(\varnothing)=0,\\
    f(S)=\min\limits_{T\subseteq S;~w(T)\leq W}\left\{t(T)+f(S\setminus T)\right\}.
\end{cases}
$$

Note that we should not directly enumerate sets and then check whether they are subsets. Instead, use [submask enumeration](../math/binary-set.md#遍历所有掩码的子掩码), which gives time complexity $O(3^n)$.

### Implementation

??? note "Reference Code"
    ```cpp
    --8<-- "docs/dp/code/state/state_2.cpp"
    ```

## Exercises

-   [NOI2001 Artillery Positions](https://loj.ac/problem/10173)
-   [USACO06NOV Corn Fields](https://www.luogu.com.cn/problem/P1879)
-   [Nine-Province Joint Contest 2018 A Pair of Wooden Chess Pieces](https://loj.ac/problem/2471)
