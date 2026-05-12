## Introduction

Catalan numbers frequently appear in various counting problems. The Belgian mathematician Eugène Charles Catalan discovered this sequence in 1958 while studying the counting of bracket sequences, and it was named after him. The Chinese mathematician Ming An Tu had already discovered this sequence in the 1930s.

Catalan numbers satisfy the following recurrence relation:

$$
C_n = \begin{cases}
1, & n = 0, \\
\sum_{i=0}^{n-1} C_i C_{n-1-i}, & n > 0.
\end{cases}\tag{1}
$$

The first few terms of the sequence are: ([OEIS: A000108](https://oeis.org/A000108), indices start from 0)

$$
1, 1, 2, 5, 14, 42, 132, 429, 1430, \ldots
$$

## Applications

The recurrence relation of Catalan numbers $C_n$ has a natural recursive structure: a counting problem of size $n$, $C_n$, can be split into two subproblems of sizes $i$ and $(n-1-i)$ by enumerating the dividing point. This recurrence makes Catalan numbers widely appear in various problems with similar recursive structures.

-   <a id="path-counting"></a>**Path Counting Problem**: There is an $n \times n$ grid, with the bottom-left corner at $(0, 0)$ and the top-right corner at $(n, n)$. Starting from the bottom-left corner, we can only move one unit to the right or up each time. Without going above the diagonal $y = x$ (but we can touch it), the total number of paths to reach the top-right corner is $C_n$.

    ??? note "Proof"
        Let the number of paths be $T_n$. Consider $n \ge 2$. Let the point where the path first touches the diagonal $y = x$ be $(k, k)$ ($k \in [1, n]$). Consider the path from $(0, 0)$ to $(k, k)$, where intermediate points do not touch the diagonal (cannot touch).
        
        ![catalan2](./images/catalan-2.svg)
        
        As shown in the figure, the first step of these paths must go right, from $(0, 0)$ to $(1, 0)$; the last step must go up, from $(k, k-1)$ to $(k, k)$. Therefore, these paths are exactly the paths from $(1, 0)$ to $(k, k-1)$ that do not cross the line $y = x-1$, and the number of such paths is $T_{k-1}$. Similarly, the number of valid paths from $(k, k)$ to $(n, n)$ is $T_{n-k}$. By the multiplication principle, the number of paths that first touch the diagonal at $(k, k)$ is $T_{k-1} T_{n-k}$. Enumerating all possible $k$, the number of all valid paths is:
        
        $$
        T_n = \sum_{k=1}^n T_{k-1} T_{n-k}.
        $$
        
        Making the substitution $k = i + 1$, we find this is exactly the recurrence relation of Catalan numbers. From $T_0 = 1$, we know $T_n = C_n$.

    <!-- To make bot happy. Do NOT delete this line. -->

-   **Non-intersecting Chords Counting Problem**: There are $2n$ points on a circle. Pairing these points to get $n$ line segments that are pairwise non-intersecting yields $C_n$ ways.

    ??? note "Proof"
        Let the number of ways for $2n$ points be $T_n$. Label the $2n$ points in clockwise order as $1, 2, \ldots, 2n$. Since the chords do not intersect, point 1 can only connect to an even-numbered point; otherwise, the odd number of points between the two cannot be paired without crossing the line connecting them. If it connects to $2k$ ($k \in [1, n]$), there are $2k-2$ points on the left and $2n-2k$ points on the right. By the multiplication principle, the number of ways is $T_{k-1} T_{n-k}$. Therefore, enumerating $k$, we have $T_n = \sum_{k=1}^n T_{k-1} T_{n-k}$. Let $k = i + 1$, and we get the recurrence relation of Catalan numbers. From $T_0 = 1$, we know $T_n = C_n$.

    <!-- To make bot happy. Do NOT delete this line. -->

-   <a id="triangulation-counting"></a>**Triangulation Counting Problem**: With no diagonals intersecting, the number of ways to divide a convex $(n+2)$-gon into triangular regions is $C_n$.

    ??? note "Proof"
        Let the number of triangulations of an $(n+2)$-gon be $T_n$. First, fix one edge $(1, n+2)$ as the base edge. It must belong to a triangle. Let the third vertex of that triangle be $k$ ($k \in [2, n+1]$). This divides the original convex polygon into three parts:
        
        -   Triangle $(1, k, n+2)$.
        -   A $k$-gon with vertices $1 \sim k$.
        -   An $(n+3-k)$-gon with vertices $k \sim (n+2)$.
        
        The latter two parts are both subproblems, so we have the recurrence:
        
        $$
        T_n = \sum_{k=2}^{n+1} T_{k-2} T_{n+1-k}.
        $$
        
        Let $k = i + 2$, and we get the recurrence relation of Catalan numbers. From $T_0 = T_1 = 1$, we know $T_n = C_n$.

    <!-- To make bot happy. Do NOT delete this line. -->

-   **Binary Tree Counting Problem**: The number of distinct binary trees with $n$ nodes is $C_n$. Equivalently, the number of distinct full binary trees with $n$ internal nodes is also $C_n$.

    ??? note "Proof"
        Let the number of binary trees with $n$ nodes be $T_n$. Take any node as the root. Enumerate the sizes of the left and right subtrees. Let the size of the left subtree be $i \in [0, n-1]$, then the right subtree has size $(n-1-i)$. Both subtrees are subproblems, so we have the recurrence:
        
        $$
        T_n = \sum_{i=0}^{n-1} T_i T_{n-1-i}.
        $$
        
        This is exactly the recurrence relation of Catalan numbers. From $T_0 = T_1 = 1$, we know $T_n = C_n$.

    <!-- To make bot happy. Do NOT delete this line. -->

-   **Bracket Sequence Counting Problem**: The number of valid bracket sequences formed by $n$ pairs of parentheses is $C_n$.

    ??? note "Proof"
        Relate to the path counting problem. Consider a left parenthesis as moving up, and a right parenthesis as moving right. A valid bracket sequence means that at any position, the number of left parentheses is not less than the number of right parentheses. This is equivalent to the path counting problem where at any time, the number of moves up is not less than the number of moves right. Therefore, there is a bijection between valid bracket sequences and valid paths. The number of valid bracket sequences is also $C_n$.

    <!-- To make bot happy. Do NOT delete this line. -->

-   **Pop Sequence Counting Problem**: The input sequence for a stack (infinite size) is $1, 2, 3, \ldots, n$. The number of valid pop sequences is $C_n$.

    ??? note "Proof"
        Relate to the bracket sequence counting problem. Consider pushing as left parenthesis and popping as right parenthesis. At any time, the number of pushes is not less than the number of pops. Therefore, there is a bijection between valid pop sequences and valid bracket sequences. The number of valid pop sequences is also $C_n$.

    <!-- To make bot happy. Do NOT delete this line. -->

-   <a id="seq-counting"></a>**Sequence Counting Problem**: Among sequences of $n$ $+1$'s and $n$ $-1$'s, i.e., $a_1, a_2, \ldots, a_{2n}$, the number of sequences where the partial sum satisfies $a_1 + a_2 + \ldots + a_k \ge 0$ ($k = 1, 2, 3, \ldots, 2n$) is $C_n$.

    ??? note "Proof"
        Relate to the bracket sequence counting problem. Consider $+1$ as a left parenthesis and $-1$ as a right parenthesis. At any time, the number of $+1$'s is not less than the number of $-1$'s. Therefore, there is a bijection between valid sequences and valid bracket sequences. The number of valid sequences is also $C_n$.

Although this recurrence is widely used, the direct calculation complexity is high, so we need to find a simpler formula.

## Common Forms

Catalan numbers have the following common expressions:

$$
C_n = \frac{1}{n+1}\binom{2n}{n} = \dfrac{(2n)!}{n!(n+1)!},~ n \ge 0. \tag{2}
$$

$$
C_n = \binom{2n}{n} - \binom{2n}{n+1},~ n \ge 0. \tag{3}
$$

$$
C_n = \frac{(4n-2)}{n+1} C_{n-1},~ n > 0,~ C_0 = 1. \tag{4}
$$

These forms of Catalan numbers can be calculated efficiently: the first two convert it to factorial and binomial coefficient calculations, and the third provides a recurrence formula for sequential calculation.

For these three common forms, this article provides two proof methods.

### Algebraic Derivation

The algebraic derivation of these expressions for Catalan numbers consists of two steps. First, verify that the three forms are equivalent to each other.

??? note "Proof that expressions $(2) \sim (4)$ are equivalent"
    Only need to prove that expression $(3)$ can be transformed into the factorial form in expression $(2)$:
    
    $$
    \begin{aligned}
    C_n &= \binom{2n}{n} - \binom{2n}{n+1} \\
    &= \frac{(2n)!}{n! n!} - \frac{(2n)!}{(n-1)!(n+1)!} \\
    &= \frac{(2n)!}{n! n!} \left(1 - \frac{n!}{(n-1)!(n+1)}\right) \\
    &= \frac{(2n)!}{n! n!} \left(1 - \frac{n}{n+1}\right) \\
    &= \dfrac{(2n)!}{n!(n+1)!}.
    \end{aligned}
    $$
    
    Also, expression $(4)$ can be transformed into the factorial form in expression $(2)$:
    
    $$
    C_n = \prod_{i=1}^n \frac{(4i-2)}{i+1} = \prod_{i=1}^n \frac{2i(2i-1)}{i(i+1)} = \dfrac{(2n)!}{n!(n+1)!}.
    $$
    
    Therefore, the three expressions are mutually equivalent.

Next, verify that these forms are indeed solutions to the recurrence formula of Catalan numbers. For this, we directly use the generating function method to find the solution to the recurrence formula $(1)$.

??? note "Using generating function method to solve recurrence formula $(1)$"
    Consider the ordinary generating function $C(x) = \sum_{n=0}^{\infty} C_n x^n$. Since the recurrence relation of Catalan numbers is very similar to a convolution form, consider constructing an equation for $C(x)$ using convolution:
    
    $$
    \begin{aligned}
    C(x) &= \sum_{n=0}^{\infty} C_n x^n\\
    &= 1 + \sum_{n=1}^{\infty} \left(\sum_{i=0}^{n-1} C_i C_{n-i-1}\right) x^{n}\\
    &= 1 + x \sum_{n=1}^{\infty} \sum_{i=0}^{n-1} C_i x^i C_{n-i-1} x^{n-i-1}\\
    &= 1 + x \sum_{i=0}^{\infty} C_i x^i \sum_{j=0}^{\infty} C_j x^j\\
    &= 1 + x C^2(x).
    \end{aligned}
    $$
    
    In the second-to-last step, we swapped the order of summation and set $j = n - 1 - i$. From this, we solve:
    
    $$
    C(x) = \dfrac{1 \pm \sqrt{1-4x}}{2x} = \frac{2}{1 \mp \sqrt{1-4x}}.
    $$
    
    From the initial condition $C_0 = 1$, we know $C(0) = 1$. Substituting to check, the only feasible solution is:
    
    $$
    C(x) = \dfrac{1 - \sqrt{1-4x}}{2x}.
    $$
    
    Next, we need to expand it as a power series. Using the power series expansion of $(1+x)^a$ ([common power series expansions](../poly/intro.md#common-power-series-expansions)):
    
    $$
    \sqrt{1-4x} = \sum_{n=0}^{\infty} \dfrac{\left(\frac{1}{2}\right)_{-n}}{n!}(-4x)^n,
    $$
    
    where $\left(\dfrac{1}{2}\right)_{-n}$ is the falling factorial:
    
    $$
    \begin{aligned}
    \left(\frac{1}{2}\right)_{-n} &= \prod_{k=0}^{n-1}\left(\dfrac{1}{2} - k\right) = \dfrac{1}{2^n}\prod_{k=1}^{n-1}(1-2k) = \dfrac{(-1)^{n-1}}{2^n}\prod_{k=1}^{n-1}(2k-1)\\
    &= \dfrac{(-1)^{n-1}}{2^{2n-1}}\prod_{k=1}^{n-1}\dfrac{(2k-1)2k}{k} = \dfrac{(-1)^{n-1}}{2^{2n-1}}\dfrac{(2n-2)!}{(n-1)!}.
    \end{aligned}
    $$
    
    Substituting into the expression for $C(x)$, we get:
    
    $$
    \begin{aligned}
    C(x) &= \dfrac{1}{2x}\left(1 - \sum_{n=0}^{\infty} \dfrac{\left(\frac{1}{2}\right)_{-n}}{n!}(-4x)^n\right)\\
    &= -\dfrac{1}{2x}\sum_{n=1}^{\infty} \dfrac{(-4x)^n}{n!}\left(\frac{1}{2}\right)_{-n} \\
    &= -\dfrac{1}{2x}\sum_{n=1}^{\infty} \dfrac{(-4x)^n}{n!}\dfrac{(-1)^{n-1}}{2^{2n-1}}\dfrac{(2n-2)!}{(n-1)!} \\
    &= \sum_{n=1}^{\infty}\dfrac{(2n-2)!}{(n-1)!n!} x^{n-1}\\
    &= \sum_{n=0}^{\infty}\dfrac{(2n)!}{n!(n+1)!} x^n.
    \end{aligned}
    $$
    
    Thus, we obtain expression $(2)$ for $C_n$.

### Combinatorial Meaning

Since Catalan numbers have obvious combinatorial meanings, these forms can also be proven using only combinatorial counting methods. This section provides a combinatorial proof for each of the three expressions.

??? note "Proof of expression $(2)$"
    Consider the [sequence counting problem](#seq-counting). For any sequence $\{a_i\}_{i=1}^{2n}$ consisting of $\pm 1$, define its partial sum as $S_i = \sum_{j=1}^{i} a_i$, and define its **exceedance** as the number of indices where $S_i < 0$ and $a_i = -1$. An exceedance of 0 is exactly equivalent to the sequence being valid; the range of exceedance is $[0, n]$, with $(n+1)$ possible values. What needs to be proven is that the number of sequences with different exceedances is actually the same.
    
    For this, we can construct a mapping $f$ from sequences with exceedance $e > 0$ to sequences with exceedance $(e-1)$. For a sequence $\{a_i\}$ with exceedance $e > 0$, take $k$ as the smallest index where $S_i = 0$ and $a_i = +1$ holds. Swap the sequences on the left and right of $a_k$, resulting in the following sequence $\{a'_i\}$:
    
    $$
    a_{k+1}, a_{k+2}, \cdots, a_{2n}, a_k, a_{1}, a_{2}, \cdots, a_{k-1}.
    $$
    
    Since the partial sum sequence corresponding to the part to the right of $a_k$ in the original sequence remains unchanged before and after the swap, the exceedance they contribute also remains unchanged. For the part to the left of $a_k$ in the original sequence, their corresponding partial sums all increase by 1 after the swap, so the exceedance they contribute decreases, and the decrease is exactly equal to the number of indices in the part to the left of $a_k$ where $S_i = -1$ and $a_i = -1$. Since the choice of $a_k$ ensures that such indices exist exactly once, the exceedance of the sequence $\{a'_i\}$ equals $(e-1)$. That is, mapping $f$ can reduce the exceedance of a sequence by exactly 1.
    
    Mapping $f$ is invertible. Note that in sequence $\{a'_i\}$, the position corresponding to $a_k$ is exactly the maximum index where $S'_k = +1$ and $a'_i = +1$ holds. This is because after the swap, these partial sums are all exactly 1 greater than the corresponding partial sums before the swap. However, according to the choice of $k$, this part (i.e., the part to the left of $a_k$ in the original sequence) before the swap has no index where $S_i = 0$ and $a_i = +1$ holds.
    
    Thus, mapping $f$ establishes a bijection between sequences with exceedance $e > 0$ and sequences with exceedance $(e-1)$. This shows that the number of sequences with different exceedances is actually the same. Since the total number of sequences is $\dbinom{2n}{n}$, the number of valid sequences (i.e., sequences with exceedance 0) equals:
    
    $$
    C_n = \dfrac{1}{n+1} \dbinom{2n}{n}.
    $$
    
    This proves expression $(2)$ of Catalan numbers.

??? note "Proof of expression $(3)$"
    Consider the [path counting problem](#path-counting). This is a typical lattice path counting problem, which can be solved using the reflection principle. Specifically, consider using the total number of paths minus the number of invalid paths. The total number of paths requires $2n$ steps in total, with $n$ steps to the right. The number of ways is $\dbinom{2n}{n}$. A path is invalid if and only if it touches the line $y = x + 1$. For any invalid path, we can find the position where it first touches the line $y = x + 1$ and reflect the part of the path after that position about the line $y = x + 1$. At this point, an invalid path from $(0, 0)$ to $(n, n)$ becomes a path from $(0, 0)$ to $(n-1, n+1)$.
    
    ![catalan1](./images/catalan-1.svg)
    
    Since any path from $(0, 0)$ to $(n-1, n+1)$ must cross the line $y = x + 1$, each such path corresponds to an invalid path from $(0, 0)$ to $(n, n)$. Similar to the calculation of total paths, the total number of invalid paths is $\dbinom{2n}{n+1}$. Therefore, the total number of valid paths is:
    
    $$
    C_n = \binom{2n}{n} - \binom{2n}{n+1}.
    $$
    
    This is expression $(3)$ of Catalan numbers.

??? note "Proof of expression $(4)$"
    Consider the [triangulation counting problem](#triangulation-counting). Let $P$ be a convex $(n+2)$-gon, fix one of its edges as the base edge. For each triangulation of polygon $P$, we can choose one of its non-base edges (including edges added during triangulation) to mark and orient. There are $(4n + 2) C_n$ such triangulation-marking schemes. Let $Q$ be a convex $(n+3)$-gon, still fix one of its edges as the base edge. For polygon $Q$, we can choose one of its non-base edges to mark, then perform triangulation. There are $(n + 2) C_{n+1}$ such marking-triangulation schemes.
    
    ![](./images/catalan-triangulation.svg)
    
    As shown in the figure, there is an obvious bijection between the results of these two sets of operations. For a result of triangulating and marking $P$, we can extend the marked edge into a triangle, extend the endpoint that the orientation points to into a new edge, and mark this new edge, which gives a result of marking and triangulating $Q$. For a result of marking and triangulating $Q$, we can compress the marked edge into a point, mark the diagonal obtained from compression, and point to the compressed vertex, which gives a result of triangulating and marking $P$. Therefore:
    
    $$
    (4n + 2) C_n = (n + 2) C_{n+1}.
    $$
    
    Rearrange slightly, combined with $C_0 = 1$, we get expression $(4)$ of Catalan numbers.

## Example Problems

???+ example "[Luogu P1044 Stack](https://www.luogu.com.cn/problem/P1044)"
    The input sequence is $1, 2, \ldots, n$. Find the total number of possible output sequences.

??? note "Reference code"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/combinatorics/catalan/catalan_1.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/combinatorics/catalan/catalan_1.py"
        ```

## Exercises

-   [Luogu P2532 [AHOI2012] Tree House Ladder](https://www.luogu.com.cn/problem/P2532)
-   [Luogu P1641 [SCOI2010] Generating Strings](https://www.luogu.com.cn/problem/P1641)
-   [Luogu P3200 [HNOI2009] Interesting Sequence](https://www.luogu.com.cn/problem/P3200)
-   [AtCoder Beginner Contest 205 E - White and Black Balls](https://atcoder.jp/contests/abc205/tasks/abc205_e)
-   [AtCoder Regular Contest 145 C - Split and Maximize](https://www.luogu.com.cn/problem/AT_arc145_c)
-   [Luogu P5014 Water Triangle (Modified)](https://www.luogu.com.cn/problem/P5014)
-   [Luogu P3978 [TJOI2015] Probability Theory](https://www.luogu.com.cn/problem/P3978)

## References and Notes

-   [Catalan number - Wikipedia](https://en.wikipedia.org/wiki/Catalan_number)