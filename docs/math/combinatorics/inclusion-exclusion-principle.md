## Introduction

???+ note "Introductory Example"
    Suppose there are 10 students who like math, 15 students who like Chinese, and 21 students who like programming in a class. How many students like at least one subject?

    Is it $10 + 15 + 21 = 46$ students? No, because some students may like both math and Chinese, or both Chinese and programming, or even all three.

    For convenience, let's denote the sets of students who like Chinese, math, and programming as $A, B, C$ respectively. Then the total number of students equals $|A \cup B \cup C|$. As explained, if we directly add the sizes of these three sets $|A|, |B|, |C|$, some elements will be counted multiple times, so we need to subtract $|A \cap B|, |B \cap C|, |C \cap A|$, but then we will have subtracted a small part too much, so we need to add back $|A \cap B \cap C|$. That is:

    $$
    |A \cup B \cup C| = |A| + |B| + |C| - |A \cap B| - |B \cap C| - |C \cap A| + |A \cap B \cap C|
    $$

    ![Inclusion-exclusion principle - Venn diagram example](./images/incexcp.png)

    Generalizing the above problem to a general case is what we know as the inclusion-exclusion principle.

## Definition

Let there be $n$ different properties for elements in universal set $U$, and the $i$-th property is called $P_i$. Elements having property $P_i$ form set $S_i$. Then:

$$
\begin{aligned}
\left|\bigcup_{i=1}^{n} S_i\right| = &\sum_{i} |S_i| - \sum_{i < j} |S_i \cap S_j| + \sum_{i < j < k} |S_i \cap S_j \cap S_k| - \cdots\\
&+ (-1)^{m-1} \sum_{a_i < a_{i+1}} \left|\bigcap_{i=1}^{m} S_{a_i}\right| + \cdots + (-1)^{n-1} |S_1 \cap \cdots \cap S_n|
\end{aligned}
$$

That is:

$$
\left|\bigcup_{i=1}^{n} S_i\right| = \sum_{m=1}^{n} (-1)^{m-1} \sum_{a_i < a_{i+1}} \left|\bigcap_{i=1}^{m} S_{a_i}\right|
$$

### Proof

Use the binomial theorem to calculate the number of occurrences for each element. For element $x$, suppose it appears in sets $T_1, T_2, \cdots, T_m$. Then its number of occurrences is:

$$
\begin{aligned}
Cnt &= |\{T_i\}| - |\{T_i \cap T_j|i < j\}| + \cdots + (-1)^{k-1} \left|\left\{\bigcap_{i=1}^{k} T_{a_i} | a_i < a_{i+1}\right\}\right|\\
    &+ \cdots + (-1)^{m-1} |\{T_1 \cap \cdots \cap T_m\}|\\
&= \binom{m}{1} - \binom{m}{2} + \cdots + (-1)^{m-1} \binom{m}{m}\\
&= \binom{m}{0} - \sum_{i=0}^{m} (-1)^i \binom{m}{i}\\
&= 1 - (1 - 1)^m = 1
\end{aligned}
$$

Since each element appears exactly once, combining them gives the union. Q.E.D.

### Complement

For the **union of sets** under universal set $U$, we can use the inclusion-exclusion principle, and for the **intersection of sets**, we find it by subtracting the union of **complements**:

$$
\left|\bigcap_{i=1}^{n} S_i\right| = |U| - \left|\bigcup_{i=1}^{n} \overline{S_i}\right|
$$

The right side uses inclusion-exclusion.

Readers familiar with inclusion-exclusion will know the above, but what they care more about is the application of inclusion-exclusion.

So next, we provide 3 example problems at different levels to demonstrate the application of the inclusion-exclusion principle.

## Counting Non-negative Integer Solutions of Diophantine Equations

???+ note "Counting non-negative integer solutions of Diophantine equations"
    Given a Diophantine equation $\sum_{i=1}^{n} x_i = m$ and $n$ constraints $x_i \leq b_i$, where $m, b_i \in \mathbb{N}$. Find the number of non-negative integer solutions.

### Without constraints

If there are no constraints $x_i \leq b_i$, the number of non-negative integer solutions to $\sum_{i=1}^{n} x_i = m$ is $\dbinom{m + n - 1}{n - 1}$.

Brief proof: Stars and bars.

This is equivalent to distributing $m$ balls into $n$ boxes, where some boxes may be empty. This problem cannot be directly solved using binomial coefficients.

So we add $n - 1$ more balls. The problem becomes: in a sequence of $m + n - 1$ balls, choose $n - 1$ balls, and these $n - 1$ balls separate the sequence into $n$ parts, which can correspond to $n$ boxes. The number of ways to choose $n - 1$ balls from $m + n - 1$ balls is $\dbinom{m + n - 1}{n - 1}$.

### Inclusion-exclusion model

Now we try to abstract the model of the inclusion-exclusion principle:

1.  Universal set $U$: Non-negative integer solutions to $\sum_{i=1}^{n} x_i = m$
2.  Elements: Variables $x_i$
3.  Properties: The condition that $x_i$ satisfies, i.e., the condition $x_i \leq b_i$

Goal: The size of the set when all variables satisfy their corresponding properties, i.e., $|\bigcap_{i=1}^{n} S_i|$.

This can be solved using $\left|\bigcap_{i=1}^{n} S_i\right| = |U| - \left|\bigcup_{i=1}^{n} \overline{S_i}\right|$. $|U|$ can be calculated using binomial coefficients, and the latter part naturally uses inclusion-exclusion.

So the problem becomes, for some $\overline{S_{a_i}}$ intersections, find the size. Consider the meaning of $\overline{S_{a_i}}$, which represents the number of solutions where $x_{a_i} \geq b_{a_i} + 1$. The intersection represents simultaneously satisfying these conditions. So in this intersection's Diophantine equation, some variables have **lower bound constraints**, while some have no constraints.

Can we eliminate these lower bound constraints? Since we need non-negative integer solutions, and some variables have lower bounds greater than 0, we can directly **subtract this lower bound** to make the lower bound of these variables become 0, i.e., no lower bound. Therefore, for:

$$
\left|\bigcap_{a_i < a_{i+1}}^{1 \leq i \leq k} S_{a_i}\right|
$$

the Diophantine equation form is:

$$
\sum_{i=1}^{n} x_i = m - \sum_{i=1}^{k} (b_{a_i} + 1)
$$

This can also be calculated using binomial coefficients. This array of length $k$, $a$, is equivalent to enumerating subsets.

## HAOI2008 Coin Shopping

???+ note "HAOI2008 Coin Shopping"
    There are 4 types of coins, with the $i$-th type having value $C_i$. There are $n$ queries, each query gives the quantity $D_i$ of each type of coin and a price $S$. Find the number of payment methods.
    
    $n \leq 10^3, S \leq 10^5$.

If we use knapsack, the complexity is $O(4nS)$, which is unbearable. The most obvious characteristic of this problem is that there are only 4 types of coins. Abstract the model, which is essentially to find the number of non-negative integer solutions to $\sum_{i=1}^{4} C_i x_i = S, x_i \leq D_i$.

Using the same inclusion-exclusion method, the property of $x_i$ is $x_i \leq D_i$. Applying the inclusion-exclusion formula, finally we need to solve:

$$
\sum_{i=1}^{4} C_i x_i = S - \sum_{i=1}^{k} C_{a_i} (D_{a_i} + 1)
$$

That is an unbounded knapsack problem. This can be preprocessed, and including the queries, the total complexity is $O(4S + 2^4 n)$.

??? note "Code implementation"
    ```cpp
    --8<-- "docs/math/code/inclusion-exclusion-principle/inclusion-exclusion-principle_1.cpp"
    ```

## Complete Graph Subgraph Coloring Problem

The previous three problems are forward applications of the inclusion-exclusion principle. This problem requires reverse analysis using the inclusion-exclusion principle.

???+ note "Complete graph subgraph coloring problem"
    A and B like to color graphs (not necessarily connected), with the rule that adjacent nodes must be colored with the same color. Today A and B play a game. For an $n$-order **complete graph** $G = (V, E)$. They define an evaluation function $F(S)$, where $S$ is an edge set, $S \subseteq E$. The value of $F(S)$ is the total number of colorings of graph $G' = (V, S)$ using $m$ colors. Their another rule is that if $|S|$ is odd, then A's score increases by $F(S)$, otherwise B's score increases by $F(S)$. Find the difference in scores between A and B.

### Mathematical form

The trend of this problem is not obvious, so for a tricky problem, first abstract the mathematical form. The score difference is the parity symmetric difference, which can use $-1$ raised to a power as the coefficient. We are looking for:

$$
Ans = \sum_{S \subseteq E} (-1)^{|S|-1} F(S)
$$

### Inclusion-exclusion model

We take "adjacent nodes must be colored with the same color" as the property. Here we first don't follow the coloring rules, and directly color the graph using $m$ colors. For graph $G' = (V, S)$, we treat it as **elements**. The **property** $x_i = x_j$ means nodes $i, j$ have the same color (note: we don't require $i, j$ to have an edge between them).

And the **set** corresponding to property $x_i = x_j$ is defined as $Q_{i,j}$, which means the number of coloring schemes of graph $G'$ satisfying this property. The elements in the set are essentially colored graphs of graph $G'$ satisfying this property.

Back to the problem, "adjacent nodes must be colored with the same color" can be understood as the intersection of several $Q$ sets. So we can write:

$$
F(S) = \left|\bigcap_{(i,j) \in S} Q_{i,j}\right|
$$

The meaning of the right side of the equation is: for every edge $(i, j)$ in $S$, the number of coloring schemes satisfying $x_i = x_j$, which is $F(S)$.

Doesn't it smell like inclusion-exclusion? Since the inclusion-exclusion principle doesn't have a form for pairs, we map **all** edges $(i, j)$ to $T = \frac{n(n+1)}{2}$ integers, assuming $(i, j)$ is mapped to $k, 1 \leq k \leq T$, and $Q_{i,j}$ is mapped to $Q_k$. Then property $x_i = x_j$ is defined as $P_k$.

Also, $S$ can be represented as a set of several $k$, i.e., $S \iff K = \{k_1, k_2, \cdots, k_m\}$. (That is, we establish an equivalence relationship between edge sets and number sets.)

And $E$ corresponds to set $M = \left\{1, 2, \cdots, \frac{n(n+1)}{2}\right\}$. So:

$$
F(S) \iff F(\{k_i\}) = \left|\bigcap_{k_i} Q_{k_i}\right|
$$

### Reverse analysis

Then expand the required formula:

$$
\begin{aligned}
Ans &= \sum_{K \subseteq M} (-1)^{|K|-1} \left|\bigcap_{k_i \in K} Q_{k_i}\right|\\
    &= \sum_{i} |Q_i| - \sum_{i < j} |Q_i \cap Q_j| + \sum_{i < j < k} |Q_i \cap Q_j \cap Q_k| - \cdots + (-1)^{T-1} \left|\bigcap_{i=1}^{T} Q_i\right|
\end{aligned}
$$

Then the inclusion-exclusion principle appears, so we derive from this formula in reverse:

$$
Ans = \left|\bigcup_{i=1}^{T} Q_i\right|
$$

Now consider the meaning of the right side: as long as any condition from $1 \sim T$ is satisfied, i.e., there exists a pair of nodes with the same color (not necessarily adjacent). And we know the universal set of coloring schemes is $U$, with $|U| = m^n$. Converting to the complement, we get the number of schemes where all pairs have different colors, i.e., $A_m^n = \frac{m!}{(m-n)!}$. Therefore:

$$
Ans = m^n - A_m^n
$$

To solve this problem, we first abstract the mathematical form of the problem, then start from the condition with the most information in the problem, the definition of function $F(S)$, transform it into set intersections and unions. Then transform the formula into the form of the inclusion-exclusion principle and **derive in reverse** to get the final result. This demonstrates the reverse use of the inclusion-exclusion principle.

## Inclusion-exclusion in Number Theory

The inclusion-exclusion principle can cleverly solve some number theory problems.

### Using inclusion-exclusion to count pairs with GCD equal to k

Consider the following problem:

???+ note "Count pairs with GCD equal to k"
    Let $1 \le x, y \le N$, $f(k)$ represent the number of ordered pairs $(x, y)$ with GCD equal to $k$. Find the values from $f(1)$ to $f(N)$.

This problem can be solved using Euler's totient function or Möbius inversion, but neither is as simple as using the inclusion-exclusion principle.

From the inclusion-exclusion principle, first find all pairs with **common divisor** $k$, then from those, remove all pairs with **common divisor** being multiples of $k$. The remaining pairs are those with **greatest common divisor** $k$. That is, $f(k) = $ number of pairs with **common divisor** $k$ - number of pairs with **common divisor** $k$'s multiples.

Further, it can be found that the number of pairs with **common divisor** being multiples of $k$ equals the sum of the number of pairs with **greatest common divisor** being multiples of $k$. So we can write:

$$
f(k) = \lfloor (N/k) \rfloor ^2 - \sum_{i=2}^{i*k \le N} f(i*k)
$$

Since when $k > N/2$, we can directly calculate $f(k) = \lfloor (N/k) \rfloor ^2$, so we can calculate from $f(N)$ to $f(1)$ in reverse. So we have solved this problem using the inclusion-exclusion principle.

```cpp
for (long long k = N; k >= 1; k--) {
  f[k] = (N / k) * (N / k);
  for (long long i = k + k; i <= N; i += k) f[k] -= f[i];
}
```

The time complexity of the above method is $O(\sum_{i=1}^{N} N/i) = O(N \sum_{i=1}^{N} 1/i) = O(N \log N)$.

Here are three similar problems for practice:

-   [Luogu P2398 GCD SUM](https://www.luogu.com.cn/problem/P2398)
-   [Luogu P2158[SDOI2008] Guard](https://www.luogu.com.cn/problem/P2158)
-   [Luogu P1447[NOI2010] Energy Collection](https://www.luogu.com.cn/problem/P1447)

### Using inclusion-exclusion to derive Euler's totient function

Consider the following problem:

???+ note "Euler's totient function formula"
    Find Euler's totient function $\varphi(n)$. Where $\varphi(n) = |\{1 \le x \le n | \gcd(x, n) = 1\}|$.

Direct calculation is $O(n \log n)$, linear sieve is $O(n)$, and Du's sieve is $O(n^{\frac{2}{3}})$ (by the way, why would we need to mention Du's sieve for an introductory number theory problem?), then let's derive the formula for Euler's totient function using inclusion-exclusion.

To determine whether two numbers are coprime, first factorize:

$$
n = \prod_{i=1}^{k} p_i^{c_i}
$$

Then we need that for any $p_i$, $x$ is not a multiple of $p_i$, i.e., $p_i \nmid x$. Take this as the property, and the corresponding set is $S_i$. Therefore:

$$
\varphi(n) = \left|\bigcap_{i=1}^{k} S_i\right| = |U| - \left|\bigcup_{i=1}^{k} \overline{S_i}\right|
$$

The universal set size $|U| = n$, and $\overline{S_i}$ represents the set where $p_i \mid x$, with size $|\overline{S_i}| = \frac{n}{p_i}$. From this, we derive:

$$
\left|\bigcap_{a_i < a_{i+1}} S_{a_i}\right| = \frac{n}{\prod p_{a_i}}
$$

Therefore:

$$
\begin{aligned}
\varphi(n) &= n - \sum_{i} \frac{n}{p_i} + \sum_{i < j} \frac{n}{p_i p_j} - \cdots + (-1)^k \frac{n}{p_1 p_2 \cdots p_k}\\
&= n \left(1 - \frac{1}{p_1}\right)\left(1 - \frac{1}{p_2}\right) \cdots \left(1 - \frac{1}{p_k}\right)\\
&= n \prod_{i=1}^{k} \left(1 - \frac{1}{p_i}\right)
\end{aligned}
$$

This is the mathematical representation of Euler's totient function.

## Generalization of Inclusion-exclusion

The inclusion-exclusion principle is often used for counting problems of sets. For two sets' functions $f(S), g(S)$, if:

$$
f(S) = \sum_{T \subseteq S} g(T)
$$

Then:

$$
g(S) = \sum_{T \subseteq S} (-1)^{|S| - |T|} f(T)
$$

### Proof

Let's briefly prove this. Starting from the right side of the equation:

$$
\begin{aligned}
&\sum_{T \subseteq S} (-1)^{|S| - |T|} f(T)\\
=&\sum_{T \subseteq S} (-1)^{|S| - |T|} \sum_{Q \subseteq T} g(Q)\\
=&\sum_{Q} g(Q) \sum_{Q \subseteq T \subseteq S} (-1)^{|S| - |T|}
\end{aligned}
$$

We find that the latter sum has nothing to do with $Q$, so we remove the latter part of $Q$:

$$
= \sum_{Q} g(Q) \sum_{T \subseteq (S \setminus Q)} (-1)^{|S \setminus Q| - |T|}
$$

Define a function on set $P$: $F(P) = \sum_{T \subseteq P} (-1)^{|P| - |T|}$, and simplify this function:

$$
\begin{aligned}
F(P) &= \sum_{T \subseteq P} (-1)^{|P| - |T|}\\
&= \sum_{i=0}^{|P|} \binom{|P|}{i} (-1)^{|P| - i} = \sum_{i=0}^{|P|} \binom{|P|}{i} 1^i (-1)^{|P| - i}\\
&= (1 - 1)^{|P|} = 0^{|P|}
\end{aligned}
$$

Therefore, the value of the original formula is:

$$
\sum_{Q} g(Q) \sum_{T \subseteq (S \setminus Q)} (-1)^{|S \setminus Q| - |T|} = \sum_{Q} g(Q) F(S \setminus Q) = \sum_{Q} g(Q) \cdot 0^{|S \setminus Q|}
$$

Analysis shows that only when $|S \setminus Q| = 0$ do we have $0^0 = 1$, at which point $Q = S$, and the contribution to the answer is $g(S)$. In other cases, $0^{|S \setminus Q|} = 0$, so there is no contribution to the answer. So we get:

$$
\sum_{Q} g(Q) \cdot 0^{|S \setminus Q|} = g(S)
$$

In summary, it is proven.

### Corollary

This form has another corollary. Under universal set $U$, for functions $f(S), g(S)$, if:

$$
f(S) = \sum_{S \subseteq T} g(T)
$$

Then:

$$
g(S) = \sum_{S \subseteq T} (-1)^{|T| - |S|} f(T)
$$

This corollary is actually the complement form, and the proof is similar.

## DAG Counting

???+ note "DAG counting"
    Count labeled directed acyclic graphs on $n$ vertices, modulo $10^9 + 7$. $n \leq 5 \times 10^3$.

### Direct DP

Consider DP. Define $f[i,j]$ as the number of DAGs on $i$ vertices with $j$ vertices having in-degree 0. After removing these $j$ vertices, suppose there are $k$ vertices with in-degree 0. Then before removal, these $k$ vertices must have at least some edges connecting to these $j$ vertices, i.e., $2^j - 1$ cases; and these $j$ vertices can also have arbitrary edges to the remaining vertices, i.e., $2^{i-j-k}$ cases. Therefore:

$$
f[i,j] = \binom{i}{j} \sum_{k=1}^{i-j} (2^j - 1)^k 2^{(i-j-k)j} f[i-j,k]
$$

The complexity of calculating the above is $O(n^3)$.

### Relax the constraint

The above DP definition is exactly $j$ vertices with in-degree 0, which is too strict. We can relax it to at least $j$ vertices with in-degree 0. Directly define $f[i]$ as the number of DAGs on $i$ vertices. We can use inclusion-exclusion directly. Consider selecting $j$ vertices, these $j$ vertices can have arbitrary edges with the remaining $i - j$ vertices, i.e., $(2^{i-j})^j = 2^{(i-j)j}$ cases:

$$
f[i] = \sum_{j=1}^{i} (-1)^{j-1} \binom{i}{j} 2^{(i-j)j} f[i-j]
$$

The complexity of calculating the above is $O(n^2)$.

## Min-max Inclusion-exclusion

For a sequence $\{x_i\}$ that satisfies a [total order](../order-theory.md#poset) relationship and whose elements satisfy additivity, let its length be $n$, and let $S = \{1, 2, 3, \cdots, n\}$. Then:

$$
\max_{i \in S}{x_i} = \sum_{T \subseteq S}{(-1)^{|T|-1} \min_{j \in T}{x_j}}
$$

$$
\min_{i \in S}{x_i} = \sum_{T \subseteq S}{(-1)^{|T|-1} \max_{j \in T}{x_j}}
$$

**Proof:** Consider mapping to the general inclusion-exclusion principle. For $x \in S$, suppose $x$ is the $k$-th smallest element. Then define a map $f: x \mapsto \{1, 2, \cdots, k\}$. Obviously, this is a bijection.

Then it's easy to find that for $x, y \in S$, $f(\min(x, y)) = f(x) \cap f(y)$, $f(\max(x, y)) = f(x) \cup f(y)$. Therefore, we get:

$$
\begin{aligned}
\left|f\left(\max_{i \in S}{x_i}\right)\right|
&= \left| \bigcup_{i \in S} f(x_i) \right|\\
&= \sum_{T \subseteq S} (-1)^{|T|-1} \left|\bigcap_{j \in T} f(x_j)\right|\\
&= \sum_{T \subseteq S} (-1)^{|T|-1} \left|f\left(\min_{j \in T}{x_j}\right)\right|
\end{aligned}
$$

Then map $\left|f\left(\max_{i \in S}{x_i}\right)\right|$ back to $\max_{i \in S}{x_i}$, and similarly for $\min$.

Q.E.D.

But you might think this formula is silly; the maximum can be found directly. The reason why min-max inclusion-exclusion is so important is that it also holds for expectations, that is:

$$
E\left(\max_{i \in S}{x_i}\right) = \sum_{T \subseteq S}{(-1)^{|T|-1} E\left(\min_{j \in T}{x_j}\right)}
$$

$$
E\left(\min_{i \in S}{x_i}\right) = \sum_{T \subseteq S}{(-1)^{|T|-1} E\left(\max_{j \in T}{x_j}\right)}
$$

**Proof:** Consider a method for calculating expectations:

$$
E\left(\max_{i \in S}{x_i}\right) = \sum_{y}{P(y = x) \max_{j \in S}{y_j}}
$$

Here, $y$ is a sequence of length $n$.

We use the previous formula on the $\max$:

$$
\begin{aligned}
E\left(\max_{i \in S}{x_i}\right) &= \sum_{y}{P(y = x) \max_{j \in S}{y_j}}\\
&= \sum_{y}{P(y = x) \sum_{T \subseteq S}{(-1)^{|T|-1} \min_{j \in T}{y_j}}}
\end{aligned}
$$

Swap the order of summation:

$$
\begin{aligned}
E\left(\max_{i \in S}{x_i}\right)
&= \sum_{y}{P(y = x) \sum_{T \subseteq S}{(-1)^{|T|-1} \min_{j \in T}{y_j}}}\\
&= \sum_{T \subseteq S}{(-1)^{|T|-1} \sum_y{P(y = x) \min_{j \in T}{y_j}}}\\
&= \sum_{T \subseteq S}{(-1)^{|T|-1} E\left(\min_{j \in T}{y_j}\right)}
\end{aligned}
$$

Similarly for $\min$.

Q.E.D.

And there is a stronger one:

$$
\underset{i \in S}{\operatorname{kthmax}{x_i}} = \sum_{T \subseteq S}{(-1)^{|T|-k}\dbinom {|T|-1}{k-1} \min_{j \in T}{x_j}}
$$

$$
\underset{i \in S}{\operatorname{kthmin}{x_i}} = \sum_{T \subseteq S}{(-1)^{|T|-k}\dbinom {|T|-1}{k-1} \max_{j \in T}{x_j}}
$$

$$
E\left(\underset{i \in S}{\operatorname{kthmax}{x_i}}\right) = \sum_{T \subseteq S}{(-1)^{|T|-k}\dbinom {|T|-1}{k-1} E\left(\min_{j \in T}{x_j}\right)}
$$

$$
E\left(\underset{i \in S}{\operatorname{kthmin}{x_i}}\right) = \sum_{T \subseteq S}{(-1)^{|T|-k}\dbinom {|T|-1}{k-1} E\left(\max_{j \in T}{x_j}\right)}
$$

Note that if $n < m$, then $\dbinom{n}{m} = 0$.

**Proof:** Suppose $\forall 1 \le i < n, x_i \le x_{i+1}$. Then:

$$
\begin{aligned}
\sum_{T \subseteq S}{(-1)^{|T|-k}\dbinom {|T|-1}{k-1} \min_{j \in T}{x_j}}
&= \sum_{i \in S}{x_i \sum_{T \subseteq S}{(-1)^{|T|-k}\dbinom {|T|-1}{k-1}\left[x_i = \min_{j \in T}{x_j} \right]}}\\
&= \sum_{i \in S}{x_i \sum_{j=k}^n{\binom{n-i}{j-1}\binom{j-1}{k-1}(-1)^{j-k}}}
\end{aligned}
$$

And because there is the combinatorial identity: $\dbinom{a}{b}\dbinom{b}{c} = \dbinom{a}{c}\dbinom{a-c}{b-c}$, so:

$$
\begin{aligned}
\sum_{T \subseteq S}{(-1)^{|T|-k}\dbinom {|T|-1}{k-1} \min_{j \in T}{x_j}}
&= \sum_{i \in S}{x_i \sum_{j=k}^n{\binom{n-i}{j-1}\binom{j-1}{k-1}(-1)^{j-k}}}\\
&= \sum_{i \in S}{x_i \sum_{j=k}^n{\binom{n-i}{k-1}\binom{n-i-k+1}{j-k}(-1)^{j-k}}}\\
&= \sum_{i \in S}{\binom{n-i}{k-1}x_i \sum_{j=k}^n{\binom{n-i-k+1}{j-k}(-1)^{j-k}}}\\
&= \sum_{i \in S}{\binom{n-i}{k-1}x_i \sum_{j=0}^{n-i-k+1}{\binom{n-i-k+1}{j}(-1)^{j}}}
\end{aligned}
$$

When $i = n - k + 1$:

$$
\binom{n-i}{k-1} \sum_{j=0}^{n-i-k+1}{\binom{n-i-k+1}{j}(-1)^{j}} = 1
$$

Otherwise:

$$
\binom{n-i}{k-1} \sum_{j=0}^{n-i-k+1}{\binom{n-i-k+1}{j}(-1)^{j}} = 0
$$

So:

$$
\sum_{i \in S}{\binom{n-i}{k-1}x_i \sum_{j=0}^{n-i-k+1}{\binom{n-i-k+1}{j}(-1)^{j}}} = \underset{i \in S}{\operatorname{kthmax}}{x_i}
$$

The other three are similar.

Q.E.D.

From min-max inclusion-exclusion, we can also get the following formula:

$$
\underset{i \in S}{\operatorname{lcm}}{x_i} = \prod_{T \subseteq S}{\left(\gcd_{j \in T}{x_j} \right)^{(-1)^{|T|-1}}}
$$

Because $\operatorname{lcm}, \gcd, a^1, a^{-1}$ correspond to $\max, \min, +, -$ respectively, that is, it performs min-max inclusion-exclusion on the exponents, which is naturally correct.

## PKUWC2018 Random Walk

???+ note "[PKUWC2018 Random Walk](https://loj.ac/problem/2542)"
    Given a tree with $n$ nodes, you start from $x$ and each time randomly choose an edge adjacent to the current node to walk to.
    
    There are $Q$ queries. Each query gives a set $S$. Find the expected number of steps to walk until all nodes in set $S$ have been visited at least once, starting from $x$.
    
    In particular, node $x$ (the starting point) is considered as already visited once.
    
    Take modulo $998244353$.
    
    $1 \le n \le 18, 1 \le Q \le 5000, 1 \le |S| \le n$.

The expected number of steps is the walking time. Let random variable $x_i$ represent the time to first reach node $i$. Then we need to find:

$$
E\left(\max_{i \in S} x_i\right)
$$

Using min-max inclusion-exclusion, we get:

$$
E\left(\max_{i \in S} x_i\right)
= E\left(\sum_{T \subseteq S}(-1)^{|T|-1} \min_{i \in T} x_i\right)
= \sum_{T \subseteq S}(-1)^{|T|-1} E\left(\min_{i \in T} x_i\right)
$$

For a set $T \in [n]$, consider finding $F(T) = E(\min_{i \in T} x_i)$.

Consider the meaning of $E(\min_{i \in T} x_i)$, which is the expected time to first reach any node in $T$. Let $f(i)$ represent the expected time to first reach some node in $T$ starting from node $i$.

-   For $i \in T$, we have $f(i) = 0$.
-   For $i \notin T$, we have $f(i) = 1 + \frac{1}{\text{deg}(i)} \sum_{(i, j) \in E} f(j)$.

If we directly use Gaussian elimination, the complexity is $O(n^3)$. Then for each $T$, calculating $F(T)$ would have a total complexity of $O(2^n n^3)$, which is not acceptable. We use tree elimination techniques.

Suppose root node is 1, and the parent of node $u$ is $p_u$. For leaf node $i$, $f(i)$ only depends on its parent (or $f(i) = 0$, which is better). So we can express $f(i)$ as $f(i) = A_i + B_i f(p_i)$, where $A_i, B_i$ can be calculated quickly.

For non-leaf node $i$, consider its child sequence $j_1, \cdots, j_k$. Since $f(j_e) = A_{j_e} + B_{j_e} f(i)$. Therefore:

$$
f(i) = 1 + \frac{1}{\deg(i)} \sum_{e=1}^k \left(A_{j_e} + B_{j_e} f(i)\right) + \frac{f(p_i)}{\deg(i)}
$$

Then we can transform to get:

$$
f(i) = \frac{\deg(i) + \sum_{e=1}^k A_{j_e}}{\deg(i) - \sum_{e=1}^k B_{j_e}} + \frac{f(p_i)}{\deg(i) - \sum_{e=1}^k B_{j_e}}
$$

So we also write $f(i)$ in the form $A_i + B_i f(p_i)$. This can be recursively traced back to the root node. And the root node has no parent, so:

$$
f(1) = \frac{\deg(1) + \sum_{e=1}^k A_{j_e}}{\deg(1) - \sum_{e=1}^k B_{j_e}}
$$

Solving this equation gives $f(1)$, and then pushing it downward once gives $f(i)$ for each node. Then $F(T) = f(x)$. The time complexity is $O(n)$.

Thus, we can calculate $F(T)$ for each $T$, with time complexity $O(2^n n)$.

Back to the inclusion-exclusion part, we know $E(\max_{i \in S} x_i) = \sum_{T \subseteq S}(-1)^{|T|-1} F(T)$.

Let $F'(T) = (-1)^{|T|-1} F(T)$. Then we further get $E(\max_{i \in S} x_i) = \sum_{T \subseteq S} F'(T)$. So we can use FMT (also called subset prefix sum, or FWT) to calculate $E(\max_{i \in S} x_i)$ for each $S$ in $O(2^n n)$ time, so we can answer queries in $O(1)$.

### Exercises

-   [ABC331- G - Collect Them All](https://atcoder.jp/contests/abc331/tasks/abc331_g)
-   [Luogu P4707 Return to the Present](https://www.luogu.com.cn/problem/P4707)

## References

[Exploring the Inclusion-Exclusion Principle - Wang Di](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2013%E8%AE%BA%E6%96%87%E9%9B%86.pdf), 2013 Information Olympiad Chinese National Team Candidate Paper Collection

[Counting Problems for Labeled DAG Series - Cyhlnj](https://www.cnblogs.com/cjoieryl/p/10078167.html)

[Total Order Relation - Wikipedia](https://en.wikipedia.org/wiki/Total_order)