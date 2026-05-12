## Counting Simple Cycles

???+ note "[Example 1: Codeforces Beta Round 11 D. A Simple Task](https://codeforces.com/problemset/problem/11/D)"
    Given a simple graph, count the number of simple cycles in the graph. A simple cycle is a cycle with no repeated vertices or edges.
    
    Number of vertices $1\leq n\leq 19$.

??? note "Solution"
    Consider state compression dynamic programming. Let $f(s,i)$ denote the number of paths where the current set of visited vertices is $s$, we are currently at vertex $i$, and the first vertex is the vertex with the **smallest index** in set $s$.
    
    For state $f(s,i)$, enumerate the next vertex $u$. If $u$ is in set $s$ and is the vertex with the smallest index (i.e., the starting point), add $f(s,i)$ to the answer $A$. If $u$ is not in $s$, add $f(s,i)$ to $f(s\cup\{u\},u)$.
    
    This approach also counts 2-cycles (i.e., parallel edges), and each non-2-cycle is counted twice (since fixing the starting point allows traversing in two directions). Therefore, the answer is $\dfrac{A-m}2$, where $m$ is the number of edges. Time complexity is $O(2^nm)$.

??? note "Sample Code"
    ```cpp
    --8<-- "docs/graph/code/rings-count/rings-count_1.cpp"
    ```

## Counting Triangles

A **triangle** is an unordered triple $(u,\ v,\ w)$ in a simple graph $G$ such that there exist three edges connecting $(u,\ v)$, $(v,\ w)$, and $(w,\ u)$. The **triangle counting problem** asks for the number of all triangles in the graph.

First, orient all edges. We orient from the vertex with smaller degree to the one with larger degree; if degrees are equal, orient from the vertex with smaller index to the one with larger index. After this orientation, the graph becomes a directed acyclic graph (DAG).

??? note "Proof of Acyclicity"
    By contradiction, assume there exists a cycle. Then in the cycle, the degrees of vertices are strictly increasing, but to form a cycle, all degrees must be equal, yet indices must be different—a contradiction.
    
    Therefore, the graph after orientation cannot contain cycles.
    
    In fact, based on the above orientation rule, one can construct a [partial order](../math/order-theory.md#binary-relation), so the graph constructed by this rule (i.e., the [Hasse diagram](../math/order-theory.md#visualization-of-posets-hasse-diagram) of this partial order) is always a DAG.

Enumerate $u$ and vertices $v$ that $u$ points to, then enumerate $w$ among vertices pointed to by $v$, and check if $u$ is connected to $w$.

The time complexity of this algorithm is $O(m\sqrt m)$.

???+ note "Proof of Time Complexity"
    For the orientation step, we iterate over all edges, giving time complexity $O(n+m)$.
    
    For each pair $(v,\ w)$, the number of possible $u$ is at most the in-degree $d^-(v)$ of $v$.
    
    If $d^-(v)\leq\sqrt m$, since the number of $w$ is at most $n$, this part has time complexity $O(n\sqrt m)$.
    
    If $d^-(v) > \sqrt m$, since $v$ points to $w$, we have $d(v) \leq d(w)$, so $d(w) > \sqrt m$. However, there are only $m$ edges total, so the number of such $w$ is at most $\sqrt m$. Hence the time complexity is $O(m\sqrt m)$.
    
    Total time complexity is $O(n+m+n\sqrt m+m\sqrt m)=O(m\sqrt m)$.
    
    In fact, if we orient from the vertex with larger degree to the one with smaller degree, the complexity is still correct; we just need to swap $u$ and $w$, and the proof above still holds.

???+ note "Sample Code ([Luogu P1989 Counting Triangles in Undirected Graph](https://www.luogu.com.cn/problem/P1989))"
    ```cpp
    --8<-- "docs/graph/code/rings-count/rings-count_2.cpp"
    ```

### Example 2

???+ note "[HDU 6184 Counting Stars](https://acm.hdu.edu.cn/showproblem.php?pid=6184)"
    Given an undirected graph with $n$ vertices and $m$ edges, count the occurrences of the following subgraph.
    
    ![](./images/rings-count1.svg)
    
    $2\leq n\leq 10^5$, $1\leq m\leq\min\left\{2\times 10^5,\ \dfrac{n(n-1)}2\right\}$.

??? note "Solution"
    This subgraph is formed by two triangles sharing an edge. So we first run triangle counting to count how many triangles contain each edge. Let $x$ be the number of triangles containing a certain edge; then the contribution to the answer is $\dbinom x2$.
    
    Time complexity is $O(m\sqrt m)$.

??? note "Sample Code"
    ```cpp
    --8<-- "docs/graph/code/rings-count/rings-count_3.cpp"
    ```

## Counting 4-Cycles

Similarly, a **4-cycle** consists of four vertices $a,\ b,\ c,\ d$ such that edges $(a,\ b)$, $(b,\ c)$, $(c,\ d)$, and $(d,\ a)$ all exist.

Consider sorting vertices first. Vertices with smaller degree come first, and those with larger degree come later.

Consider enumerating vertex $a$ that comes last in the ordering. For each vertex $c$ that ranks before $a$, find how many vertices $b$ that rank before $a$ such that edges $(a,\ b)$ and $(b,\ c)$ exist. Then any two of these $b$ vertices form a 4-cycle. Finding the count of $b$ requires iterating through $b$ and $c$.

Note that the enumeration complexity is essentially equivalent to enumerating triangles, so the time complexity is also $O(m\sqrt m)$ (assuming $n$ and $m$ are of the same order).

Note that $(a,\ b,\ c,\ d)$ and $(a,\ c,\ b,\ d)$ can be two different 4-cycles.

Additionally, vertices with the same degree have different rankings, and one must check that $a\neq c$.

???+ note "Sample Code ([LibreOJ P191 Counting 4-Cycles in Undirected Graph](https://loj.ac/p/191))"
    ```cpp
    --8<-- "docs/graph/code/rings-count/rings-count_4.cpp"
    ```

### Example 3

???+ note "[Gym 102028L Connected Subgraphs](https://codeforces.com/gym/102028/problem/L)"
    Given an undirected graph with $n$ vertices and $m$ edges, count the number of connected induced subgraphs with four edges.
    
    $4\leq n\leq 10^5$, $4\leq m\leq 2\times 10^5$.

??? note "Solution"
    It's easy to categorize the cases into five types: star graph, 4-cycle, a triangle with one vertex having an extra edge, a chain of four vertices with the middle vertex having an extra edge, and a chain of five vertices.
    
    The star graph can be solved directly by enumerating vertex degrees and using combinatorial formulas. The 4-cycle can be obtained directly by the algorithm above. For the triangle case, enumerate the triangle $(u,\ v,\ w)$, and the contribution to the answer is $[d(u)-2]+[d(v)-2]+[d(w)-2]$.
    
    For the fourth case, enumerate the vertex $x$ with degree $2$, and enumerate a neighbor $y$ of $x$ as the vertex with degree $3$. The contribution to the answer is $[d(x)-1]\cdot\dbinom{d(y)-1}2$. However, note that neighbors of $y$ may overlap with neighbors of $x$, in which case the subgraph is equivalent to the third case. But each overcounted third-case subgraph is counted twice (since there are two vertices with degree $3$), so we should subtract twice the count of the third case.
    
    For the last case, first enumerate the middle vertex $x$. It's easy to see the contribution to the answer is
    
    $$
    \sum_{y\in son_x}\sum_{z\in son_x}[d(y)-1]\cdot[d(z)-1].
    $$
    
    Similarly, there are overcounted parts. Let the neighbors of $y$ be $s$, and neighbors of $z$ be $t$. After analysis, the overcounted cases are:
    
    1.  $y$ coincides with $t$, but $s$ does not coincide with $z$—equivalent to the third case;
    2.  $s$ coincides with $z$, but $y$ does not coincide with $t$—also equivalent to the third case;
    3.  Both $y$ and $t$ coincide, and $s$ and $z$ coincide—equivalent to a triangle;
    4.  $s$ and $t$ coincide—equivalent to a 4-cycle (the second case).
    
    Considering that in the third case, the two vertices with degree $2$ serve as $x$, which respectively correspond to the overcounted cases 1 and 2 above, we need to additionally subtract twice the count of the third case. For a triangle, all three vertices can serve as $x$, so it's overcounted $3$ times. Similarly, the 4-cycle case is overcounted $4$ times.
    
    Thus we obtain the algorithms for all cases. Time complexity is $O(n+m\sqrt m)$.

??? note "Sample Code"
    ```cpp
    --8<-- "docs/graph/code/rings-count/rings-count_5.cpp"
    ```

## Exercises

[Luogu P3547 \[POI2013\] CEN-Price List](https://www.luogu.com.cn/problem/P3547)

[CodeForces 985G Team Players](https://codeforces.com/contest/985/problem/G) (Inclusion-exclusion principle)