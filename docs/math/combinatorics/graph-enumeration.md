## Introduction

In combinatorics, graph enumeration is a branch that studies counting problems for graphs satisfying specific properties. [Generating functions](../poly/intro.md), [Pólya's counting theorem](./polya.md), [symbolic methods](../poly/symbolic-method.md#combinatorial-cycle-structures), and [OEIS](https://oeis.org/) are the most important mathematical tools for solving such problems. Graph enumeration can be divided into labeled and unlabeled problems. In most cases[^1], labeled problems are simpler than their unlabeled counterparts, so we will first examine the counting of labeled problems.

[^1]: Unlabeled binary trees may be a counterexample; when the structure is simple, the corresponding permutation group is the identity group, and the labeled version can be directly obtained by multiplying by $n!$.

## Labeled Trees

This is Cayley's formula. See the article on [Prüfer sequences](../../graph/prufer.md). We can also obtain this result using [Kirchhoff's matrix-tree theorem](../../graph/matrix-tree.md) or [generating functions](../poly/intro.md#generating-functions) and [Lagrange's theorem](https://codeforces.com/blog/entry/104184).

### Exercises

-   [Hihocoder 1047. Random Tree](https://vjudge.net/problem/HihoCoder-1047)

## Labeled Connected Graphs

### Example Problem "POJ 1737" Connected Graph

???+ note "Example Problem [「POJ 1737」Connected Graph](http://poj.org/problem?id=1737)"
    Problem: Find the number of labeled connected graphs with $n$ vertices ($n \le 50$).

This type of problem first appeared in the "Man Eight Problems" series by the coach. Let $g_n$ be the number of labeled graphs with $n$ vertices, and $c_n$ be the sequence to be found. A graph with $n$ vertices has at most $\binom{n}{2}$ edges, each edge has two states (present or absent), each state is independent, so $g_n = 2^{\binom{n}{2}}$. We fix one vertex and enumerate the size of its connected component. Then we need to choose $i-1$ vertices from the remaining $n-1$ vertices to form a connected component. Vertices outside the connected component can have arbitrary edges. Therefore, we have the following recurrence:

$$
\begin{align}
\sum_{i=1}^{n} \binom{n-1}{i-1} c_i g_{n-i} &= g_n \\
c_n &= g_n - \sum_{i=1}^{n-1} \binom{n-1}{i-1} c_i g_{n-i} 
\end{align}
$$

By rearranging, we get an $O(n^2)$ recurrence formula for sequence $c_n$, which can solve this problem.

### Example Problem "Training Camp 2013" Urban Planning

???+ note "Example Problem [「Training Camp 2013」Urban Planning](https://www.luogu.com.cn/problem/P4841)"
    Problem: Find the number of labeled connected graphs with $n$ vertices ($n \le 130000$).

For sequence problems with larger data ranges, we often need to construct generating functions for these sequences to use efficient polynomial algorithms.

#### Method 1: Divide and Conquer FFT

The above recurrence can be seen as a self-convolution form, so divide and conquer FFT can be used for calculation, with complexity $O(n \log^2 n)$.

#### Method 2: Polynomial Inversion

Expand the binomial coefficients in the above recurrence and rearrange:

$$
\begin{align}
\sum_{i=1}^{n} \binom{n-1}{i-1} c_i g_{n-i} &= g_n \\
\sum_{i=1}^{n} \frac{c_i}{(i-1)!} \frac{g_{n-i}}{(n-i)!} &= \frac{g_n}{(n-1)!}
\end{align}
$$

Construct polynomials:

$$
\begin{align}
C(x) &= \sum_{n=1} \frac{c_n}{(n-1)!} x^n \\
G(x) &= \sum_{n=0} \frac{g_n}{n!} x^n \\
H(x) &= \sum_{n=1} \frac{g_n}{(n-1)!} x^n
\end{align}
$$

Substitute into the above to get $CG = H$. Use [polynomial inversion](../poly/elementary-func.md#polynomial-inversion) and then convolution to solve for $C(x)$.

#### Method 3: Polynomial exp

Another method uses the combinatorial meaning of polynomial exp in EGFs. Let $C(x)$ be the EGF of labeled connected graphs and simple graphs, and $G(x)$ be the EGF of simple graphs. Then they have the following relationship:

$$
\begin{align}
\exp(C(x)) &= G(x) \\
C(x) &= \ln(G(x))
\end{align}
$$

Use [polynomial logarithm](../poly/elementary-func.md#polynomial-logarithm-and-exponential-functions) to solve for $C(x)$.

## Labeled Eulerian Graphs, Bipartite Graphs

### Example Problem "SPOJ KPGRAPHS" Counting Graphs

???+ note "Example Problem [「SPOJ KPGRAPHS」Counting Graphs](http://www.spoj.com/problems/KPGRAPHS/)"
    Problem: Find the number of labeled graphs with $n$ vertices satisfying the following properties ($n \le 1000$):
    -   Connected graphs [A001187](https://oeis.org/A001187).
    -   Eulerian graphs [A033678](https://oeis.org/A033678).
    -   Bipartite graphs [A047864](https://oeis.org/A047864).

The problem has code length restrictions, so we cannot directly use polynomial templates, but generating functions can still help us analyze.

The connected graph problem has been solved in the previous example. Consider Eulerian graphs. Note that the several methods for counting connected graphs above can all be extended to labeled connected graphs satisfying any property. For example, we can replace $g_n$ in the connected graph recurrence formula with graphs where all vertex degrees are even. Then the obtained $c_n$ is the number of Eulerian graphs.

We encapsulate the recurrence process of POJ 1737 into a connectivity function:

```cpp
void ln(Int C[], Int G[]) {
  for (int i = 1; i <= n; ++i) {
    C[i] = G[i];
    for (int j = 1; j <= i - 1; ++j)
      C[i] -= binom[i - 1][j - 1] * C[j] * G[i - j];
  }
}
```

The first two questions can be easily solved:

```cpp
for (int i = 1; i <= n; ++i) G[i] = pow(2, binom[i][2]);
ln(C, G);
for (int i = 1; i <= n; ++i) G[i] = pow(2, binom[i - 1][2]);
ln(E, G);
```

Note that the connectivity recurrence process is actually equivalent to taking the polynomial ln of its EGF. Similarly, we can write the inverse connectivity function, which is equivalent to taking the polynomial exp of its EGF.

```cpp
void exp(Int G[], Int C[]) {
  for (int i = 1; i <= n; ++i) {
    G[i] = C[i];
    for (int j = 1; j <= i - 1; ++j)
      G[i] += binom[i - 1][j - 1] * C[j] * G[i - j];
  }
}
```

Next, we discuss labeled bipartite graph counting.

Let $b_n$ represent the number of bipartite graphs with $n$ vertices, and $g_n$ represent the number of graphs where we perform 2-coloring on $ $n$ vertices, with no edges between vertices of the same color. Enumerate the number of vertices of one color[^2]:

$$
g_n = \sum_{i=0}^{n} \binom{n}{i} 2^{i(n-i)}
$$

[^2]: [Pink Rabbit's blog](https://www.luogu.com.cn/blog/PinkRabbit/solution-sp4420) tells us that this sequence can also be optimized using [Chirp Z-Transform](../poly/czt.md).

Next, we establish the relationship between $g_n$ and $b_n$ using two different methods.

#### Method 1: Counting Twice

Let $c_{n, k}$ represent the number of bipartite graphs with $k$ connected components. Then it's not hard to get:

$$
\begin{align}
b_n &= \sum_{i=1}^{n} c_{n, i} \\
g_n &= \sum_{i=1}^{n} c_{n, i} 2^i 
\end{align}
$$

Compare the two expressions for $g_n$, expand to get:

$$
\begin{align}
\sum_{i=0}^{n} \binom{n}{i} 2^{i(n-i)} &= \sum_{i=1}^{n} c_{n, i} 2^i \\
c_{n, i} &= \sum_{i=0}{n-1} \binom{n-1}{i-1} c_{n, 1}c_{n-i,k-1}
\end{align}
$$

We can get the recurrence for $b_n$ with $O(n^3)$ complexity. Furthermore, using the inclusion-exclusion principle, we can optimize to $O(n^2)$ to solve this problem.

#### Method 2: Connectivity Recurrence

Methods 2 and 3 both use connected bipartite graphs $b1_n$ [A001832](https://oeis.org/A001832) to establish a bridge between $g_n$ and $b_n$.

Note that for each connected bipartite graph, we have exactly two different coloring methods, corresponding to two different connected 2-colored graphs. Therefore, performing connectivity on $g_n$, the resulting sequence is exactly twice $b1_n$, while $b_n$ is obtained by inverse connectivity from $b1_n$.

Therefore:

```cpp
for (int i = 1; i <= n; ++i) {
  G[i] = 0;
  for (int j = 0; j < i + 1; ++j) G[i] += binom[i][j] * pow(2, j * (i - j));
}
ln(B1, G);
for (int i = 1; i <= n; ++i) B1[i] /= 2;
exp(B, B1);
```

Both recurrence processes have $O(n^2)$ complexity and can solve this problem.

#### Method 3: Polynomial exp

We can also understand the recurrence process above using EGFs.

Let $G(x)$ be the EGF of $g_n$, $B1(x)$ be the EGF of $b1_n$, and $B(x)$ be the EGF of $b_n$. Applying the method from 2, we have:

$$
\begin{align}
G(x) &= \exp(2B1(x)) \\
B(x) &= \exp(B1(x)) \\
     &= \exp(\frac{\ln G(x)}{2}) \\
     &= \sqrt{G}
\end{align}
$$

We can take derivatives on both sides and compare coefficients to get a recurrence formula that's easy to code. Note that method 2 and method 3 are essentially the same, and in general, method 3 can achieve better time complexity.

$$
\begin{align}
B_n^2 &= G \\
2B_n B_n' &= G'
\end{align}
$$

??? note "Reference code"
    ```cpp
    --8<-- "docs/math/code/combinatorics/graph-enumeration/graph-enumeration_1.cpp"
    ```

### Exercises

-   [UOJ Goodbye Jihai D. New Year's Chase](https://uoj.ac/contest/50/problem/498)
-   [BZOJ 3864. Big Friend and Multichotomous Tree](https://hydro.ac/p/bzoj-P3864)
-   [BZOJ 2863. Angry Leader](https://hydro.ac/p/bzoj-P2863)
-   [Luogu P6295. Labeled DAG Counting](https://www.luogu.com.cn/problem/P6295)
-   [LOJ 6569. Cactus Counting](https://loj.ac/p/6569)
-   [LOJ 6570. Caterpillar Counting](https://loj.ac/p/6570)
-   [Luogu P5434. Labeled Desert Counting](https://www.luogu.com.cn/problem/P5434)
-   [Luogu P3343. [ZJOI2015] Fantasy Village After Earthquake](https://www.luogu.com.cn/problem/P3343)
-   [HDU 5279. YJC Plays Minecraft](https://acm.hdu.edu.cn/showproblem.php?pid=5279)
-   [Luogu P7364. Labeled Bipartite Graph Counting](https://www.luogu.com.cn/problem/P7364)
-   [Luogu P5827. Vertex-Biconnected Graph Counting](https://www.luogu.com.cn/problem/P5827)
-   [Luogu P5827. Edge-Biconnected Graph Counting](https://www.luogu.com.cn/problem/P5828)
-   [Luogu P6596. How Many of Them](https://www.luogu.com.cn/problem/P6596)
-   [Luogu U152448. Labeled Strongly Connected Graph Counting](https://www.luogu.com.cn/problem/U152448)
-   [Project Euler 434. Rigid graphs](https://projecteuler.net/problem=434)

## Riddell's Formula

The usage of EGF's exp above is sometimes called Riddell's formula for labeled graphs. The [Euler transform](../poly/symbolic-method.md#combinatorial-multiset-structures) of generating functions is sometimes also called Riddell's formula for unlabeled graphs. The latter first appeared in Euler's research on partition numbers. Besides solving graph enumeration problems, it also appears in the unbounded knapsack problem.

For a given sequence $a_i$ and its OGF $A(x)$, the Euler transform of $A(x)$ is defined as:

$$
\begin{align}
\mathcal{E}(A(x)) &= \prod_{i} (1 - x^i)^{-a_i} \\
                  &= \exp (\sum_{i} \frac{A(x^i)}{i})  
\end{align}
$$

Let the coefficients of $\mathcal{E}(A(x))$ be $b_i$. Define an auxiliary array $c_i = \sum_{d|n} d a_d$. Then there is a recurrence formula:

$$
n b_n = c_n + \sum_{i=1}^{n-1} c_i b_{n-i}
$$

## Unlabeled Trees

### Example Problem "SPOJ PT07D" Let us count 1 2 3

???+ note "Example Problem [「SPOJ PT07D」Let us count 1 2 3](https://www.spoj.com/problems/PT07D/)"
    Problem: Find the number of trees with $n$ vertices satisfying various properties:
    -   Labeled rooted trees [A000169](https://oeis.org/A000169).
    -   Labeled unrooted trees [A000272](https://oeis.org/A000272).
    -   Unlabeled rooted trees [A000081](https://oeis.org/A000081).
    -   Unlabeled unrooted trees [A000055](https://oeis.org/A000055).

#### Rooted Trees

The labeled case has been solved above. Now consider unlabeled rooted trees. Let their OGF be $F(x)$. Applying the Euler transform, we get:

$$
F(x) = x \mathcal{E}(F(x))
$$

Extract the coefficients.

#### Unrooted Trees

Consider inclusion-exclusion. We subtract from the rooted tree schemes those where the root is not the centroid, and discuss based on the parity of $n$.

When $n$ is odd:

There must be a subtree with size $\ge \left\lceil \frac{n}{2}\right\rceil$. Enumerate the size of this subtree:

$$
g_n = f_n - \sum_{i=\left\lceil\frac{n}{2}\right\rceil}^{n-1} f_i f_{n-i}
$$

When $n$ is even:

Note that when there are two centroids, the above process only subtracts once. So we also need to subtract:

$$
g_n = f_n - \sum_{i=\left\lceil\frac{n}{2}\right\rceil}^{n-1} f_i f_{n-i} - \binom{f_{\frac{n}{2}}}{2}
$$

### Example Problem "Luogu P5900" Unlabeled Unrooted Tree Counting

???+ note "Example Problem [「Luogu P5900」Unlabeled Unrooted Tree Counting](https://www.luogu.com.cn/problem/P5900)"
    Problem: Find the number of unlabeled unrooted trees with $n$ vertices ($n \le 200000$).

For larger data ranges, the method is the same. After the Euler transform, use polynomial templates.

## Unlabeled Simple Graphs

### Example Problem "SGU 282. Isomorphism" Isomorphism

???+ note "Example Problem [「SGU 282. Isomorphism」Isomorphism](https://codeforces.com/problemsets/acmsguru/problem/99999/282)"
    Problem: Find the number of ways to color the edges of an unlabeled complete graph with $n$ vertices with $m$ colors.

Note that when $m = 2$, the desired object is an unlabeled simple graph [A000088](https://oeis.org/A000088). Consider Pólya's counting theorem:

$$
\frac{1}{|G|}\sum_{g \in G} m^{c(g)}
$$

In this problem, the permutation group $G$ is the edge permutation group generated by the symmetric group on $n$ vertices. However, the brute force enumeration is $O(n!)$, which cannot solve this problem.

Consider classifying according to the cycle structure of permutations. Each cycle structure corresponds to an integer partition. We use dfs() to generate partitions. Then the problem becomes finding, for each partition $p$, the number of permutations $w(p)$ corresponding to it and the number of cycles $c(p)$ in each type of permutation. The answer is:

$$
\frac{1}{|G|} \sum_{p \in P} w(p) m^{c(p)}
$$

Consider $w(p)$. Each partition corresponds to a cyclic permutation, and permutations of the same size are independent of order. Therefore:

$$
w(p) = \frac{n!}{\prod_{i}(p_i)\prod_{i}(q_i!)} 
$$

Here, $q_i$ represents the number of partitions of size $i$ that appear in $p$.

Consider $c(p)$. The cycles of the point set affected by $p$ are $|p|$. But since the problem is about edge coloring, we also need to consider the edge permutations generated by point permutations.

If an edge's two vertices are in the same cycle, let the cycle size be $p_i$. Then the cycle generated by the edge is exactly $\left\lfloor \frac{p_i}{2} \right\rfloor$.

If an edge's two vertices are in two different cycles, let them be $p_i$ and $p_j$, and the length of each cycle segment is $\operatorname{lcm}(p_i, p_j)$. Therefore, the number of cycles generated by the edge is exactly $\frac{p_i p_j}{\operatorname{lcm}(p_i, p_j)} = \gcd(p_i, p_j)$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/math/code/combinatorics/graph-enumeration/graph-enumeration_2.cpp"
    ```

## Exercises

-   [CodeForces 438 E. The Child and Binary Tree](https://codeforces.com/problemset/problem/438/E)
-   [Luogu P5448. [THUPC2018] Good Graph Counting](https://www.luogu.com.cn/problem/P5448)
-   [Luogu P5818. [JSOI2011] Isomer Counting](https://www.luogu.com.cn/problem/P5818)
-   [Luogu P6597. Alkene Counting](https://www.luogu.com.cn/problem/P6597)
-   [Luogu P6598. Alkane Counting](https://www.luogu.com.cn/problem/P6598)
-   [Luogu P4128. [SHOI2006] Colored Graph](https://www.luogu.com.cn/problem/P4128)
-   [Luogu P4727. [HNOI2009] Graph Isomorphism Counting](https://www.luogu.com.cn/problem/P4727)
-   [AtCoder Beginner Contest 222 H. Binary Tree](https://atcoder.jp/contests/abc222/tasks/abc222_h)
-   [AtCoder Beginner Contest 284 Ex. Count Unlabeled Graphs](https://atcoder.jp/contests/abc284/tasks/abc284_h)
-   [Luogu P4708. Draw](https://www.luogu.com.cn/problem/P4708)
-   [Luogu P7592. Number Tree (2021 CoE-II E)](https://www.luogu.com.cn/problem/P7592)
-   [Luogu P5206. [WC2019] Number Tree](https://www.luogu.com.cn/problem/P5206)

## References and Notes

1.  [WC2015, Participant Exchange Materials by Gu Yuzhou - Graphical Enumeration](https://github.com/lychees/ACM-Training/blob/master/Note/%E5%86%AC%E4%BB%A4%E8%90%A5/2015/%E9%A1%BE%E6%98%B1%E6%B4%B2%E8%90%A5%E5%91%98%E4%BA%A4%E6%B5%8B%E8%B5%84%E6%96%87%20Graphical%20Enumeration.pdf)
2.  [WC2019, Generating Functions, Polynomial Algorithms and Graph Counting](https://github.com/lychees/ACM-Training/tree/master/Note/%E5%86%AC%E4%BB%A4%E8%90%A5/2019/d4)
3.  [Counting labeled graphs - Algorithms for Competitive Programming](https://cp-algorithms.com/combinatorics/counting_labeled_graphs.html)
4.  [Graphical Enumeration Paperback, Frank Harary, Edgar M. Palmer](https://github.com/lychees/ACM-Training/blob/master/Note/Book/)
5.  [The encyclopedia of integer sequences, N. J. A. Sloane, Simon Plouffe](https://github.com/lychees/ACM-Training/blob/master/Note/Book/The%20encyclopedia%20of%20integer%20sequences%20\(N.%20J.A.%20Sloane%2C%20Simon%20Plouffe\).pdf)
6.  [Combinatorial Problems and Exercises, László Lovász](https://github.com/lychees/ACM-Training/blob/master/Note/Book/Combinatorial%20Problems%20and%20Exercises_L%C3%A1szl%C3%B3%20Lov%C3%A1sz.pdf)
7.  [Graph Theory and Additive Combinatorics](https://yufeizhao.com/gtacbook/)