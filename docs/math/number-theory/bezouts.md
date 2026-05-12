Bézout's theorem reveals the profound connection between the greatest common divisor and integer linear combinations, and is one of the most fundamental and important conclusions in number theory. Based on this, this article further discusses the solution methods for linear Diophantine equations.

## Bézout's Theorem

**Bézout's theorem** (Bézout's lemma), also translated as Bézout's identity, gives a necessary and sufficient condition for an integer to be representable as an integer linear combination of two integers.

???+ note "Bézout's Theorem"
    Let $a,b$ be integers not both zero. Then, for any integers $x,y$, we have $\gcd(a,b)\mid ax+by$ always holds; moreover, there exist integers $x,y$ such that $ax+by=\gcd(a,b)$ holds.

??? note "Proof"
    Let $d=\gcd(a,b)$. Since $d\mid a,b$, there exist integers $u,v$ such that $a=du,~b=dv$ holds. Therefore, we always have
    
    $$
    ax + by = d(ux+vy).
    $$
    
    This shows that $d\mid ax+by$.
    
    Conversely, we need to show the existence of $x,y$ making the equation hold. If one of $a,b$ is $0$, suppose $b=0$, then their greatest common divisor is $d=a$, and obviously $(x,y)=(1,0)$ makes the equation hold. Next, consider the case where $a,b$ are both non-zero. Since $\gcd(a,b)=\gcd(-a,b)=\gcd(a,-b)$, we can assume $a,b$ are both positive.
    
    Considering the Euclidean algorithm, we have:
    
    $$
    \begin{aligned}
    a   &= q_1b   + r_1, && 0\le r_1 < b,\\
    b   &= q_2r_1 + r_2, && 0\le r_2 < r_1,\\
    r_1 &= q_3r_2 + r_3, && 0\le r_3 < r_2,\\
        & \cdots \\
    r_{n-3} &= q_{n-1}r_{n-2} + r_{n-1}, && 0\le r_{n-1} < r_{n-2},\\
    r_{n-2} &= q_nr_{n-1} + r_n,         && 0\le r_n     < r_{n-1},\\
    r_{n-1} &= q_{n+1}r_n.
    \end{aligned}
    $$
    
    Since the greatest common divisor is $d$, at the last step of the Euclidean algorithm, we must have $r_n=d$. Therefore, the second-to-last equation can be written as:
    
    $$
    d = r_n = r_{n-2} - q_nr_{n-1}.
    $$
    
    Solving from the third-to-last equation:
    
    $$
    r_{n-1} = r_{n-3} - q_{n-1}r_{n-2}
    $$
    
    Substituting into the above equation, we can eliminate $r_{n-1}$:
    
    $$
    \begin{aligned}
    d &= r_{n-2} - q_n(r_{n-3} - q_{n-1}r_{n-2}) \\
    &= (1 + q_nq_{n-1})r_{n-2} - q_nr_{n-3}.
    \end{aligned}
    $$
    
    Similarly, by gradually eliminating all $r_{n-2},r_{n-3},\cdots,r_2,r_1$, we finally get:
    
    $$
    d = xa + yb.
    $$
    
    This proves the existence of $x,y$ such that $ax+by=d$ holds. From the previous analysis, this also proves the original proposition.

Here, the proof of existence is constructive, and it simultaneously gives a method to compute such coefficients. This computation method is the [Extended Euclidean Algorithm](./gcd.md#extended-euclidean-algorithm).

Considering the special case of Bézout's theorem when $\gcd(a,b)=1$, we get the following corollary:

???+ note "Corollary"
    The integers $a,b$ are coprime if and only if there exist integers $x,y$ such that $ax+by=1$ holds.

### The Case of Multiple Integers

Bézout's theorem can be extended to the case of multiple integers.

???+ note "Theorem"
    Let $a_1,a_2,\cdots,a_n$ be integers not all zero. Then, for any integers $x_1,x_2,\cdots,x_n$, we have $\gcd(a_1,a_2,\cdots,a_n)\mid a_1x_1+a_2x_2+\cdots+a_nx_n$ always holds; moreover, there exist integers $x_1,x_2,\cdots,x_n$ such that $\gcd(a_1,a_2,\cdots,a_n)=a_1x_1+a_2x_2+\cdots+a_nx_n$ holds.

??? note "Proof"
    Using the fact that $\gcd(a_1,a_2,\cdots,a_n)=\gcd(\gcd(a_1,a_2,\cdots,a_{n-1}),a_n)$, we can prove by induction on $n$.

### Example Problems

???+ example "[Codeforces 510 D. Fox And Jumping](https://codeforces.com/problemset/problem/510-D)"
    Given $n\le 300$ cards, each with $l_i$ and $c_i$. On an infinite strip of paper, you can choose to spend $c_i$ to buy card $i$, after which you can jump $l_i$ units left or right any number of times. Find the minimum amount of money needed to reach all positions on the strip. If impossible, output $-1$.

??? note "Solution"
    Analyzing the problem, to reach every position, the chosen numbers $l_{i_1}, \cdots, l_{i_k}$ must be able to obtain an absolute value of $1$ through several additions or subtractions. That is, there exist integers $x_1, \cdots, x_k$ such that $l_{i_1} x_1 + \cdots + l_{i_k} x_k = 1$. By Bézout's theorem for multiple integers, this is equivalent to selecting several numbers from the array $l_1, \cdots, l_n$ such that their greatest common divisor is $1$, while minimizing the total cost.
    
    **Solution 1**: Treating the minimum total cost as a shortest path problem, Dijkstra's algorithm can be used. The graph's vertices store the current value of the greatest common divisor. The starting point is $0$, and the target is $1$. At each step, from the current vertex $x$, we move along an edge of length $c_i$ to the vertex $\gcd(x,l_i)$. The time complexity of this algorithm is $O(n^2\log n)$.
    
    **Solution 2**: From the array $l_1, \cdots, l_n$, selecting several numbers with greatest common divisor $1$ and minimizing the total cost reminds us of the 0-1 knapsack problem.
    
    Let $f_{i, j}$ denote the minimum cost when considering the first $i$ numbers and the greatest common divisor is $j$. The transition equation is:
    
    $$
    f_{i, j} = \min_{\gcd(k, l_i) = j} f_{i - 1, k} + c_i.
    $$
    
    The final total cost after DP is $f_{n, 1}$.
    
    Like the general 0-1 knapsack problem, we can use a rolling array to optimize, removing the first dimension. The possible values of the greatest common divisor $j$ that can be formed from 300 numbers are very sparse, so a hash map can be used for storage.
    
    Actually, the graph built in Solution 1 is exactly the state transition graph for dynamic programming in Solution 2, and Solution 2 is equivalent to finding the shortest path in a directed acyclic graph. Therefore, Solution 1 and Solution 2 are equivalent. However, Solution 2 does not need to store the full graph, and the DP time complexity is $O(n + m)$, which is lower than Dijkstra's algorithm. Therefore, Solution 2 is better in both time and space.

## Linear Diophantine Equations

A **linear Diophantine equation** is a Diophantine equation in the form:

$$
a_1x_1 + a_2x_2 + \cdots + a_nx_n = b
$$

where $a_1,a_2,\cdots,a_n$ are all integers. The goal of this section is to find all integer solutions of this equation.

### The Case of Two Variables

First, consider the binary linear Diophantine equation:

$$
a_1x_1 + a_2x_2 = b.
$$

Bézout's theorem states that this equation has a solution if and only if:

$$
d = \gcd(a_1,a_2) \mid b.
$$

Next, assuming this condition holds. Using the extended Euclidean algorithm, we can find a solution $(x_1^*,x_2^*)$ to the equation $a_1x_1 + a_2x_2 = d$. From this, we can obtain a particular solution to the original equation:

$$
(x_1^\circ,x_2^\circ) = \left(\frac{b}{d}x_1^*,\frac{b}{d}x_2^*\right).
$$

To obtain all solutions, consider subtracting the original equation from the identity $a_1x_1^\circ+a_2x_2^\circ = b$:

$$
a_1(x_1 - x_1^\circ) + a_2(x_2 - x_2^\circ) = 0.
$$

This is a homogeneous linear Diophantine equation in $(x_1-x_1^\circ,x_2-x_2^\circ)$, and it has the general solution:

$$
(x_1-x_1^\circ,x_2-x_2^\circ) = \left(t\dfrac{a_2}{d},-t\dfrac{a_1}{d}\right).\quad(t\in\mathbf Z)
$$

Therefore, the general solution to the original equation is:

$$
(x_1,x_2) = \left(x_1^\circ + t\dfrac{a_2}{d},x_2^\circ - t\dfrac{a_1}{d}\right).\quad(t\in\mathbf Z)
$$

These are a series of equally spaced integer points on the line $a_1x_1+a_2x_2 = b$.

### The Case of Multiple Variables

Having solved the binary case, the multivariate case becomes easy to solve. For an $n$-variable linear Diophantine equation:

$$
a_1x_1 + a_2x_2 + \cdots + a_nx_n = b,\quad (n>3)
$$

By Bézout's theorem, the equation has a solution if and only if:

$$
\gcd(a_1,a_2,\cdots,a_n) \mid b.
$$

Similar to the binary case, the general solution to the multivariate linear Diophantine equation can also be written as:

$$
(x_1^\circ,x_2^\circ,\cdots,x_n^\circ) + \sum_{k=1}^{n-1} t_k(x_1^{(k)},x_2^{(k)},\cdots,x_n^{(k)})
$$

where $x^\circ$ is a particular solution, and $x^{(k)}$ are the $n-1$ solutions of the corresponding homogeneous equation.

To find the explicit form of the general solution, we can convert the $n$-variable equation into an $(n-1)$-variable equation. Let $d_1 = \gcd(a_1,a_2)$. Then, according to Bézout's theorem, the set of all $a_1x_1+a_2x_2$ is exactly all multiples of $d_1$. Therefore, we first solve the $(n-1)$-variable linear Diophantine equation:

$$
d_1y_1 + a_3x_3 + a_4x_4 + \cdots + a_nx_n = b.
$$

Let its general solution be:

$$
\begin{aligned}
y_1 &= y_1^\circ + \sum_{k=2}^{n-1}t_ky_1^{(k)}, \\
x_i &= x_i^\circ + \sum_{k=2}^{n-1}t_kx_i^{(k)},\quad i=3,\cdots,n.
\end{aligned}
$$

Let $(x_1^*,x_2^*)$ be a particular solution of $a_1x_1+a_2x_2=d_1$. Then, according to the discussion in the previous section, the general solution to the binary linear Diophantine equation $a_1x_1+a_2x_2=d_1y_1$ in $x_1,x_2$ is:

$$
x_1 = x_1^*y_1 + t_1\dfrac{a_2}{d_1},~x_2 = x_2^*y_1 - t_1\dfrac{a_1}{d_1}.
$$

Substituting the expression for $y_1$, we obtain the general solution to the original equation:

$$
\begin{aligned}
x_1 &= x_1^*y_1^\circ + t_1\dfrac{a_2}{d_1} + \sum_{k=2}^{n-1}t_kx_1^*y_1^{(k)}, \\
x_2 &= x_2^*y_1^\circ - t_1\dfrac{a_1}{d_1} + \sum_{k=2}^{n-1}t_kx_2^*y_1^{(k)}, \\
x_i &= x_i^\circ + \sum_{k=2}^{n-1}t_kx_i^{(k)},\quad i=3,\cdots,n.
\end{aligned}
$$

## Frobenius Coin Problem

Bézout's theorem gives a necessary and sufficient condition for an integer to be representable as a linear combination of several integers. Closely related to this is the **Frobenius coin problem**:

-   If there are several kinds of integer coin denominations $a_1,a_2,\cdots,a_n$, and $\gcd(a_1,a_2,\cdots,a_n)=1$, what is the largest integer that cannot be represented by these coins?

Also examining when an integer $k$ can be represented in the form $a_1x_1+a_2x_2+\cdots+a_nx_n$, in Bézout's theorem, $x_i$ can be any integer, but in the Frobenius coin problem, $x_i$ can only be natural numbers.

The case with only one coin type is trivial because we can only have $a_1=1$, so all natural numbers can be represented by it. The case with $n>2$ is too complex, so this section only discusses the case $n=2$.

### Sylvester's Theorem

In 1882, Sylvester completely solved the Frobenius coin problem for $n = 2$:

???+ note "Theorem (Sylvester)"
    For coprime positive integers $a_1,a_2$, the largest integer that cannot be written as $a_1x_1+a_2x_2~(x_1,x_2\in\mathbf N)$ is $C = a_1a_2 - a_1 - a_2$. Moreover, for all $k\in\mathbf Z$, exactly one of $k$ and $C-k$ can be written in this form.

For convenience, integers that can be written in the form $a_1x_1+a_2x_2~(x_1,x_2\in\mathbf N)$ are called **representable**.

??? note "Proof One"
    Since $a_1,a_2$ are coprime, for any integer $k$, the equation $a_1x_1+a_2x_2=k$ always has a solution, and the general solution is:
    
    $$
    (x_1,x_2) = (x_1^\circ + ta_2, x_2^\circ - ta_1).\quad(t\in\mathbf Z)
    $$
    
    Taking $t$ as the quotient from dividing $x_2^\circ$ by $a_1$, then the remainder $x_2 = x_2^\circ-ta_1$ is between $0$ and $a_1-1$. Examining the solution $(x_1,x_2)$ obtained at this time. Since $x_2$ is its smallest non-negative value, $n$ is representable if and only if $x_1\ge 0$.
    
    **Step One**: Prove that all integers greater than $C$ are representable.
    
    When $k > C$, we have:
    
    $$
    a_1x_1 = k - a_2x_2 > C - a_2(a_1-1) = -a_1.
    $$
    
    So, $x_1 > -1$, that is, $x_1\ge 0$. This shows that $(x_1,x_2)$ is a natural number solution. At this time, $k$ can be written in the required form.
    
    **Step Two**: Prove that $C$ is not representable. Furthermore, $C$ is the largest unrepresentable integer, and $k$ and $C-k$ are not both representable.
    
    Proof by contradiction. Suppose $C$ can be represented, i.e., there exist $x_1,x_2\in\mathbf N$ such that $a_1x_1+a_2x_2=C$ holds. Substituting the expression for $C$, we know:
    
    $$
    a_1a_2 = a_1(x_1+1) + a_2(x_2+1).
    $$
    
    Therefore, $a_2\mid (x_1+1)$ and $a_1\mid (x_2+1)$. Since $x_1+1,x_2+1$ are all positive, we have:
    
    $$
    a_1a_2 \ge a_1a_2 + a_2a_1 = 2a_1a_2.
    $$
    
    Contradiction. This shows that $C$ is not representable. Combined with step one, it is the largest unrepresentable integer.
    
    If both $k$ and $C-k$ can be represented, then adding the coefficients in the representations of $k$ and $C-k$ gives the coefficients in the representation of $C$, which contradicts that $C$ is not representable. Therefore, at most one of $k$ and $C-k$ can be represented.
    
    **Step Three**: Prove that if $k$ is not representable, then $C-k$ must be representable.
    
    Let $(x_1,x_2)$ be the integer solution to the equation $a_1x_1+a_2x_2=k$ set above. Then as discussed earlier, $k$ not being representable is equivalent to $x_1<0$. Therefore, we have:
    
    $$
    C - k = a_1a_2 - a_1 - a_2 - a_1x_1 - a_2x_2 = a_1(-1-x_1) + a_2(a_1-1-x_2).
    $$
    
    Here, both $-1-x_1$ and $a_1-1-x_2$ are non-negative integers, so $C-k$ can be represented.

??? note "Proof Two"
    Here we only prove that $C=a_1a_2-a_1-a_2$ is the largest unrepresentable natural number; the rest of the proof is similar to Proof One.
    
    Consider, modulo $a_2$, the minimum representable natural number in each residue class. Since different natural numbers in the same residue class can be transformed into each other by adding or subtracting several $a_2$, when discussing the minimum representable number, we only need to consider the possibility of adding or subtracting $a_1$. Since $a_1$ and $a_2$ are coprime, the minimum representable natural number in each residue class is exactly a multiple of $a_1$:
    
    $$
    0,~a_1,~2a_1,~\cdots,~(a_2-1)a_1.
    $$
    
    Therefore, the largest unrepresentable number is:
    
    $$
    \max_{0\le i < a_2} ia_1 - a_2 = (a_2-1)a_1 - a_2 = C.
    $$

### Geometric Interpretation

Considering the equation $a_1x_1 + a_2x_2 = k$ as a line. Then $k$ is representable if and only if this line passes through an integer point in the first quadrant (including the coordinate axes). When $k < ab$, this line can pass through at most one integer point in the first quadrant. Therefore, for $0\le k < ab$, the integer $k$ is representable if and only if the line passes through exactly one integer point in the first quadrant.

Therefore, the number of representable natural numbers less than or equal to $k < ab$ is exactly equal to the number of integer points (including boundary points) under the line $a_1x_1 + a_2x_2 = k$ in the first quadrant. This number equals:

$$
\sum_{i=0}^{\lfloor k / a_1 \rfloor} \left\lfloor\dfrac{k-ia_1}{a_2}\right\rfloor.
$$

This is a classic problem of counting integer points under a line, which can be solved in $O(\log\min\{a_1,a_2,k\})$ time using the [Euclidean Algorithm](./euclidean.md#euclidean-algorithm).

### Practice Problems

-   [Luogu P3951 NOIP2017 Premium Group - Xiaokai's Confusion/Lanqiao Cup 2013 Province - Unobtainable Numbers](https://www.luogu.com.cn/problem/P3951)