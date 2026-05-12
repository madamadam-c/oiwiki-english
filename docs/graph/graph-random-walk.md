This page introduces random walk problems on graphs. We explore this topic from three perspectives: grid graphs, sparse graphs, and general graphs. Various methods for solving such problems are introduced, along with comparisons of their advantages and disadvantages.

## Definition

Given a directed simple graph $G=(V, E)(V=\{v_1, v_2, \cdots, v_{|V|}\})$, a start node $s \in V$, and an end node $t \in V$, each edge $e=\left(x, y\right)$ has a positive weight $w_e$, satisfying $\forall x \in V \backslash\left\{t\right\}$, $\sum_{\left(x, y\right) \in E} w_{\left(x, y\right)}=1$, and for any node $x$ there exists a path from $x$ to $t$. A token starts at the start node. Each second, from the current node $x$, it chooses edge $\left(x, y\right)$ with probability $w_{(x, y)}$ and moves to $y$. The process stops when reaching the end node. Find the expected time.

Actually, this problem can also be expressed in matrix form. Define matrix $P$:

$$
P_{x, y}=
\begin{cases}
w_{(x, y)} & \text{if } (x, y) \in E \text{ and } x \neq t \\
0 & \text{if } (x, y) \notin E \text{ or } x=t \\
\end{cases}
$$

The answer we want is:

$$
\sum_{k \geq 0} k \times\left(P^k\right)_{s, t}
$$

Here, $\left(P^k\right)_{s, t}$ represents the probability of reaching the end node for the first time after exactly $k$ steps. When the graph is finite and all nodes can reach the end node, it can be proven from the definition of $P$ that all eigenvalues are less than 1, so the answer converges.

For convenience, in this page, unless specified otherwise, $n$ denotes $|V|$ and $m$ denotes $|E|$.

Also in this page, a sparse graph refers to a graph where the number of edges is on the same order as the number of nodes.

## Grid Graphs

???+ note "Problem 1 [Circles of Waiting](https://codeforces.com/problemset/problem/963/E)"
    A token starts at point $(0,0)$ in the Cartesian coordinate plane. Each second, the token moves randomly. If it is currently at $(x, y)$, it has probability $p_1$ to move to $(x-1, y)$, probability $p_2$ to move to $(x, y-1)$, probability $p_3$ to move to $(x+1, y)$, and probability $p_4$ to move to $(x, y+1)$. It is guaranteed that $p_1+p_2+p_3+p_4=1$.
    Find the expected time until the token moves to a position whose Euclidean distance from the origin exceeds $R$. $0 \leq R \leq 50$, $p_1, p_2, p_3, p_4>0$, answer modulo $10^9+7$.

### Naive Approach

Let $f(i, j)$ be the expected time for the token to reach a position whose Euclidean distance from the origin exceeds $R$ when starting from $(i, j)$. The transition is:

$$
f(i, j)=
\begin{cases}
p_1 f(i-1, j) + p_2 f(i, j-1) + p_3 f(i+1, j) + p_4 f(i, j+1) + 1 & i^2 + j^2 \leq R^2 \\
0 & i^2 + j^2 > R^2
\end{cases}
$$

Since the transitions do not follow a topological order, Gaussian elimination is needed. Time complexity is $O\left(R^6\right)$, which cannot pass this problem.

### Direct Elimination

Notice that most coefficients in the equations to be eliminated are 0. We can reduce complexity by only computing for positions with non-zero values.

Consider the elimination process, ordering equations from top to bottom in the coordinate plane, and within each row from left to right. Mark eliminated equations in yellow, cells adjacent to yellow cells in green, and the rest in black, as shown below:

![graph-random-walk-1](images/graph-random-walk-1.svg)

Now we eliminate the equation corresponding to the next green cell. In this equation, only the coefficients of variables corresponding to the green cell and the first black cell below it may be non-zero. Similarly, only in the equation of the first black cell below the green cell may the coefficient of the current cell's variable be non-zero.

Notice that there are only $O(R)$ green cells, so the time complexity for eliminating a single equation is $O\left(R^2\right)$. There are $O\left(R^2\right)$ equations in total, so the time complexity is reduced to $O\left(R^4\right)$, which can pass this problem.

### Pivot Method

There are $O\left(R^2\right)$ equations and variables. If we can reduce the scale to $O(R)$, naive Gaussian elimination will work.

Set the first cell in each row as the pivot variable, giving $2 R+1$ pivots. Express all other cell variables as linear functions of these pivots. Consider each column from left to right. For the current cell $(i, j)$, notice that $f(i, j)$, $f(i-1, j)$, $f(i, j-1)$, and $f(i, j+1)$ are all known linear functions of the pivots. Rearranging the transition equation:

$$
f(i+1, j)=\frac{f(i, j)-p_1 f(i-1, j)-p_2 f(i, j-1)-p_4 f(i, j+1)-1}{p_3}
$$

This gives us $f(i+1, j)$ as a linear function of the pivots. If $(i+1, j)$ is already beyond Euclidean distance $R$ from the origin, we get an equation: $f(i+1, j)=0$. Eventually, we get $2 R+1$ equations, and Gaussian elimination on these gives the answer.

During the propagation of linear functions of pivots, there are $O\left(R^2\right)$ variables, and propagating a single variable takes $O(R)$ time. Then the problem size is reduced to $O(R)$. Both parts have $O\left(R^3\right)$ complexity, so the total is $O\left(R^3\right)$, which can pass this problem.

### Comparison of the Two Approaches

The following compares the two approaches from multiple perspectives:

From time complexity perspective, the pivot method has worst-case complexity $O(n \sqrt{n})$ on grid graphs (highest when both length and width are $O(\sqrt{n})$), while direct elimination has worst-case complexity $O\left(n^2\right)$, so the pivot method is better.

From numerical precision perspective, for problems requiring real number calculations rather than modular arithmetic, direct elimination has better precision than the pivot method.

From applicability perspective, the two methods suit different scenarios.

When there are obstacles in the grid graph or some edges have probability $0$, the pivot method requires adding a pivot for each obstacle or edge with probability $0$. When the number of such obstacles or edges exceeds $O(R)$, the pivot method's complexity increases, while direct elimination's complexity remains unchanged.

However, the pivot method can also handle elimination of transition equations similar to those on grid graphs, such as $f(i, j)=p_1 f(i+1, j)+p_2 f(i, j+1)+p_3 f(\operatorname{pre}(i, j))+1$, where $\operatorname{pre}(i, j)=(x, y)(x \leq i, y \leq j)$ is a given value, whereas the complexity analysis of direct elimination does not apply to this model.

Additionally, computing the determinant of the adjacency matrix of a grid graph cannot use the pivot method; only direct elimination can optimize the time complexity.

In summary, each method has its strengths, and the appropriate method should be chosen based on the specific problem.

## Sparse Graphs

???+ note "Problem 2 Expected Value"
    Given a simple undirected connected sparse graph $G=(V, E)$, a token starts at $v_1$. Each second, the token randomly chooses one of the edges connected to the current node with equal probability and moves to the adjacent node. Find the expected time to reach $v_n$. $n \leq 2000$, answer modulo $p$, where $p$ is a prime randomly generated in the interval $\left[10^9, 1.01 \times 10^9\right]$.

### Background

**Definition 4.1.** A polynomial $p(\lambda)$ such that $p(A) = 0$ is called an annihilating polynomial of matrix $A$.

**Definition 4.2.** Let $I_n$ be the $n \times n$ identity matrix. The characteristic polynomial of an $n \times n$ matrix $A$ is defined as $p(\lambda) = \det(\lambda I_n - A)$, where $\det$ denotes the determinant of a matrix.
It is easy to see that the characteristic polynomial of an $n \times n$ matrix has degree at most $n$.

**Theorem 4.2.** (Cayley-Hamilton Theorem) The characteristic polynomial of any matrix is its annihilating polynomial.

Therefore, the minimal annihilating polynomial of an $n \times n$ matrix also has degree at most $n$.

### Solving the Original Problem

Notice that the expected time $E(t)=\sum_{i\geq0}\Pr[t>i]$. If we can find the probability of not having finished after $i$ steps, summing over all $i \geq 0$ gives the answer.

Let $f(i, j)$ be the probability that after $i$ steps, the token is at $j$ and has never visited $n$. Then:

$$
f(i,j)=\sum_{(k,j)\in E}\frac{f(i-1,k)}{\deg_k}(j\neq n)
$$

Here, $\deg_k$ denotes the degree of $k$.

Notice that the transition of $f$ does not depend on $i$. We can view one transition as multiplying by a matrix, i.e., $f{i+1}=f_iM$. Since the minimal annihilating polynomial of $M$ has degree at most $n$, the shortest recurrence for $f$ also has length at most $n$. Hence, the shortest recurrence for $\Pr[t>i]=\sum_{j=1}^{n-1}f(i,j)$ also has length at most $n$. We can compute $\Pr[t>0],\Pr[t>1],\cdots,\Pr[t>3n]$ in $O(nm)$ time, then use the *Berlekamp-Massey* algorithm to find the shortest recurrence for $\Pr[t > i]$ in $O(n^2)$ time.

Consider finding the generating function of a $k$-order linear recurrence sequence $a$. Suppose for $i \geq i_0$, $a_i=\sum_{j=1}^kc_ja_{i-j}$. Let the generating functions of $a$ and $c$ be $A(x)$ and $C(x)$. Then $A(x)=A(x)C(x)+A_0(x)$, where $A_0(x)$ is determined by terms with $i < i_0$.

Back to the original problem. Since we can find the shortest recurrence for $\Pr[t > i]$, we can find $C(x)$ and $A_0(x)$ (same definitions as above). Rearranging, $A(x)=\frac{A_0(x)}{1-C(x)}$. We want $\sum_{i\geq0}[x^i]A(x)$. It is easy to see this equals $A(1)$, so we substitute $x = 1$ to solve. Since the modulus is a random prime, we can assume the denominator is not zero.

Thus, we solve the problem in $O(nm+n^2)$ time. If the graph $G$ has a number of edges on the same order as the number of nodes, the time complexity is $O(n^2)$.

## General Graphs

???+ note "Problem 3 Frank"
    Given a simple strongly connected directed graph $G = (V, E)$. For all $1 \leq s \leq n$, $1 \leq t \leq n$, $s \neq t$, answer the following:
    A token starts at $v_s$. Each second, the token randomly chooses one of the outgoing edges from the current node with equal probability and moves to the target node. Find the expected time to reach $v_t$. $3 \leq n \leq 400$.

### Analysis and Transformation

Let $p_{i, j}$ be the probability that when the token is at $i$, it chooses outgoing edge $(i, j)$ and moves to $j$. If there is no outgoing edge, the probability is $0$. Let $f_{i,j}$ be the expected time for a random walk from $i$ to $j$. In particular, $f_{i,i} = 0$. When $i \neq j$, the transition is:

$$
f_{i,j}=1+\sum_{1\leq k\leq n}p_{i,k}f_{k,j}
$$

When $i = j$, let $g_i$ be the expected time for a random walk starting from $i$ to return to $i$ for the first time. Then:

$$
f_{i,i}=1-g_i+\sum_{1\le k\le n}p_{i,k}f_{k,i}
$$

For clarity, we write the transitions in matrix form. Let $P$ be the transition matrix of the graph, $F$ be the answer matrix, $I$ be the $n \times n$ identity matrix, $J$ be the $n \times n$ all-ones matrix, and $G$ be an $n \times n$ matrix with $G_{i,i} = g_i$ and 0 elsewhere. Then:

$$
F=J-G+PF
$$

If we can find $G$, we just need to solve:

$$
(I − P)F = J − G
$$

### Finding $G$

**Definition 5.1.** A stationary distribution of an $n \times n$ transition matrix $P$ is an $n$-dimensional vector $π$ satisfying $\sum_{i=1}^{n}\pi_{i}=1$ and $πP = π$. Each component of $π$ lies in the interval $[0,1]$.

The practical meaning of the stationary distribution is easy to see. If at some moment the token has probability $π_i$ of being at $v_i$, then at any later time, the token still satisfies this probability distribution. We can find $π$ by Gaussian elimination in $O(n^3)$ time. What is the relationship between $π$ and $G$?

**Theorem 5.1.** For any $1 \leq i \leq n$, we have $π_ig_i = 1$.

???+ note "Proof"
    From $F = J - G + PF$, rearrange:
    
    $$
    G = PF + J − F
    $$
    
    Multiply by $π$ on the left:
    
    $$
    πG = πPF + πJ − πF
    $$
    
    From the definition of $π$, $πP = π$, so:
    
    $$
    πG = πJ
    $$
    
    Therefore:
    
    $$
    \pi_ig_i=\sum_{j=1}^n\pi_j=1  
    $$
    
    Q.E.D.

Thus, by introducing the stationary distribution, we can find $G$ in $O(n^3)$ time.

### Solving the Original Problem

During the solving process, we encounter a problem: $(I - P)$ is not full rank, so we cannot solve by multiplying the inverse matrix.

**Definition 5.2.** A spanning arborescence rooted at $r \in V$ of a directed graph $G = (V,E)$ is a subgraph $T = (V,A)$ satisfying:

1.  For any $i \neq r$, vertex $i$ has outdegree $1$.
2.  Vertex $r$ has outdegree $0$.
3.  $T$ contains no cycles.

**Lemma 5.1.** (Matrix-Tree Theorem for Directed Graphs) For a directed graph $G$, let $D$ be the outdegree matrix, where $D_{i,i} = d_i$, $D_{i,j} = 0(i \neq j)$, with $d_i$ being the outdegree of $i$. Let $A$ be the adjacency matrix. The number of spanning arborescences rooted at $r$ equals the determinant of $D - A$ after removing row $r$ and column $r$.

**Theorem 5.2.** For the transition matrix $P$ of a strongly connected graph $G = (V,E)$, $(I - P)$ has rank $n - 1$.

???+ note "Proof"
    Since multiplying a row of a matrix by a non-zero constant does not change its rank, we multiply row $i$ of $(I - P)$ by the outdegree of $v_i$ to get a new matrix $L$. We only need to prove that $L$ has rank $n - 1$.  
    Since each row of $L$ sums to 0, summing all column vectors of $L$ gives the zero vector, meaning these vectors are linearly dependent. Thus $L$ does not have full rank $n$.  
    It is easy to see that $L$ equals the outdegree matrix minus the adjacency matrix of graph $G$. By Lemma 5.1, the determinant of $L$ after removing row $i$ and column $i$ equals the number of spanning arborescences rooted at $v_i$.  
    Since $G$ is strongly connected, the number of spanning arborescences rooted at any vertex is non-zero. Therefore, $L$ remains full rank after removing row $i$ and column $i$.  
    Since adding a column does not decrease rank, all row vectors of $L$ after removing row $i$ are linearly independent. Hence, $L$ has rank $n - 1$.  
    Back to the original problem, consider solving the equation $AX = B$, where $A$ and $B$ are known and $X$ is to be found. Since $A$ is not full rank, there are infinitely many solutions. First, we find one particular solution.  
    Perform Gaussian elimination on $A$ and $B$ together. Reduce the first $n - 1$ rows of $A$ to have values only on the main diagonal and column $n$, and the last row to all zeros, giving the following form:
    
    $$
    \begin{bmatrix}
    1 & 0 & 0 & \cdots & 0 & a_1 \\0&1&0&\cdots&0&a_2\\0&0&1&\cdots&0&a_3\\
    \vdots&\vdots&\vdots&\ddots&\vdots&\vdots
    \\0&0&0&\cdots&1&a_{n-1}\\0&0&0&\cdots&0&0
    \end{bmatrix}
    X=
    \begin{bmatrix}
    b_{1,1}&b_{1,2}&b_{1,3}&\cdots&b_{1,n-1}&b_{1,n}
    \\b_{2,1}&b_{2,2}&b_{2,3}&\cdots&b_{2,n-1}&b_{2,n}
    \\b_{3,1}&b_{3,2}&b_{3,3}&\cdots&b_{3,n-1}&b_{3,n}
    \\\vdots&\vdots&\vdots&\ddots&\vdots&\vdots
    \\b_{n-1,1}&b_{n-1,2}&b_{n-1,3}&\cdots&b_{n-1,n-1}&b_{n-1,n}
    \\0&0&0&\cdots&0&0
    \end{bmatrix}
    $$
    
    Set $X_{n,i} = 0$, solve for a particular solution, and denote it as $Y$. Next, adjust the particular solution to the actual solution.  
    Notice that $X_{n,i} = 0$. Considering the combinatorial meaning, $Y_{i,j} = 1 + Y_{j,j} + P_{i,k}X_{k,j}$. It is not hard to solve $X_{i,j} = Y_{i,j} - Y_{j,j}$.  
    The problem is solved in $O(n^3)$ time complexity.

## References

1.  A Brief Discussion on Random Walk Problems on Graph Models. IOI 2019 China National Team Candidate Papers (pp. 17-26)
