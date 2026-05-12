author: Ir1d, partychicken, ouuan, Marcythm, TianyiQ

## Overview

Prerequisite knowledge: [Random function](../misc/random.md) and [Preliminary probability](../math/probability/basic-conception.md)

This article will make a simple classification of randomization related techniques in OI/ICPC and introduce each classification. This article will also introduce some methods that are rarely used in OI/ICPC but are close to OI/ICPC in terms of style and other aspects. These contents will be marked with `(*)`.

This classification does not represent broad consensus and certainly cannot cover all possibilities, so it is for reference only.

**Notations and Conventions**:

-   $\mathrm{Pr}[A]$ represents the probability of event $A$ occurring.
-   $\mathrm{E}[X]$ represents the expectation of random variable $X$.
-   The assignment number $:=$ represents the introduction of a new quantity, for example, $Y:=1926$ represents the introduction of the quantity $Y$ with the value $1926$.

## Overwrite the target element with a random collection

There is one (or more) solutions in the huge solution space that we want. We can try to cast the net multiple times. As long as we can catch the target solution once, we will be successful.

### Example: Judgment of Tripartite Diagram

???+ note "question"
    Given a simple undirected graph with $n$ nodes and $m$ edges, use RGB three colors to color each node such that any pair of neighbors have different colors, or report no solution.

For each point $v$, independently and randomly select a color $C_v$ from $\{R,G,B\}$ with medium probability, and specify that $v$ **not** be dyed $C_v$. The probability that the optimal solution exactly meets these constraints is obviously $\big(\frac 23\big)^n$.

Under these constraints, for a pair of neighbors $(u,v)$, the requirement of "$u,v$ different colors" is equivalent to the following "pull-out" relationship:

-   For all colors $X$ that are different from $C_u,C_v$, if $u$ is dyed as $X$, then $v$ is dyed as $\{R,G,B\}\setminus\{X,C_v\}$.

So we can set the Boolean variable $B_v$ for each $v$, whose value indicates which of the two remaining colors $v$ is dyed into. This problem can be solved with the complexity of $O(n+m)$ using the 2-SAT model.

In this way, the single accuracy rate is $\big(\frac 23\big)^n$. Repeat the algorithm $-\big(\frac 32\big)^n\log \epsilon$ times, and output it as soon as the solution is obtained once. This can ensure the accuracy of $1-\epsilon$. (See "Analysis of Probability Upper Bound" later in the article for details)

***

**Review**: The "solution space" in this question is the set $\{R,G,B\}^n$. We search for the "target solution" - that is, a legal coloring scheme - within a narrowed range by randomly imposing restrictions each time.

### Example: [CodeChef SELEDGE](https://www.codechef.com/problems/SELEDGE)

???+ note "Brief question meaning"
    Given an undirected graph with non-negative weights for both points and edges, find an edge set $S$ of size $\leq K$ to maximize the sum of the weights of the points connected to $S$ minus the sum of the edge weights of $S$. The weight of a point is calculated only once.

Observation: If three of the selected edges form a chain, then deleting the middle one is not inferior; if there are several selected edges that form a cycle, then deleting any one of them is not inferior.

Corollary: The edge set selected by the optimal solution must form several disjoint chrysanthemum diagrams (that is, trees with a diameter not exceeding 2).

Corollary: The edge set selected by the optimal solution must form a bipartite graph.

We independently and randomly dye each point with one of two colors, black and white, with equal probability, and require this coloring scheme to be exactly the black-and-white coloring scheme of the bipartite graph corresponding to the optimal solution.

Try to calculate the probability that the optimal solution meets this requirement:

-   Consider a chrysanthemum picture with $n$ points. Obviously it has 2 dyeing schemes, so the probability of it being dyed the right color is $\dfrac 2{2^n}=2^{1-n}$.
-   Assuming that the number of nodes in each chrysanthemum in the optimal solution is $a_1,\cdots,a_l$, then there must be $(a_1-1)+\cdots+(a_l-1)\leq K$, where $K$ represents the maximum number of edges that can be selected.
-   Therefore, the probability that all chrysanthemums are dyed the right color is $2^{1-a_1}\cdots 2^{1-a_l}\geq 2^{-K}$.

Under the above requirements, try to establish a cost flow model to calculate the optimal answer:

-   Create a bipartite graph, with the white point on the left and connected to $S$, and the black point on the right and connected to $T$.
    -   For the white point $v$, there is an edge with a capacity of 1 and a cost of $-A_v$ and an edge with a capacity of $\infty$ and a cost of 0 connected to it from $S$.
    -   For the black point $v$, there is an edge with a capacity of 1 and a cost of $-A_v$ and an edge with a capacity of $\infty$ and a cost of 0 connected from it to $T$.
-   For the edge $(u,v,B)$ in the original image, $u$ is white and $v$ is black. If there is an edge from $u$ to $v$, the capacity is 1 and the cost is $B$.
-   In this figure, the traffic is limited to no more than $K$, then the opposite number of the minimum cost is the answer.

If SPFA cost flow is used to solve the problem, the complexity is $O\big(K^2(n+m)\big)$. Prove:

-   First, obviously the number of SPFA runs is $\leq K$.
-   Then, in a SPFA, any node can enter the team at most $O(K)$ times. This is because:
    -   There will be no more than $3K$ edges with traffic at any time, otherwise it means that more than $K$ edges have been selected in the original image.
    -   For any Zengguang road with a length of $L$, at least $\dfrac L2-2$ edges are the reverse edges of an edge with traffic, because the forward edges point from the left side of the graph to the right, and only these reverse edges will point from the right side to the left.
    -   Combining the above two, we can get that the length of any Zengguang Road does not exceed $6K+4$.
-   To sum up, the complexity is $O\big(K^2(n+m)\big)$.

Similar to the previous question, we need to repeat the whole process $-2^K \log\epsilon$ times to get the accuracy of $1-\epsilon$. Total complexity $O\big(2^KK^2(n+m)\cdot -\log\epsilon\big)$.

## Hit the target set with random elements

We need to determine any element in a set, so we randomly select elements in the hope of hitting this set exactly.

### Example: [Gym 101550I](https://codeforces.com/gym/101550/attachments)

???+ note "Brief question meaning"
    There is a graph such as: two parallel chains, plus two parallel sides connecting the two chains. Given several simple paths on this graph (each path represents a call), please choose as few edges as possible to place eavesdroppers so that there is at least one eavesdropper on each given path.

The whole picture can be divided into a ring and four chains extending from the ring. For any of these four chains (denoted as $C$), considering how to place eavesdroppers on this chain, it is easy to obtain a solution that satisfies the following conditions through a greedy algorithm:

-   On the premise of intercepting all calls made within $C$, the minimum number of eavesdroppers is used.
-   Under the premise of the previous item, make the shortest distance between the eavesdropper on $C$ and the ring as small as possible.
    -   The purpose of this requirement is to intercept calls with exactly one endpoint inside $C$ as much as possible.

Then consider a total of 4 edges where the chain and the ring connect, and we violently enumerate whether there are bugs placed on these edges. Obviously, if you want to intercept calls across chains and rings, it must be optimal to place eavesdroppers on these four edges. Now, we can divide the call lines into the following types:

1.  A completely on-chain call line. These lines must have been intercepted, so they can be ignored.
2.  Call lines that span chains and rings and have been intercepted. They can be ignored.
3.  Call lines that span chains and rings without being intercepted. We can directly cut off its part on the chain (because the eavesdropper placement scheme on the chain has been fixed) and only keep the part on the ring.
4.  A completely on-the-loop call line.

At this point, the problem is transformed into a problem on the ring.

Assume that a bug is placed on the edge set $S$ on the ring in the optimal solution. If we have determined any element $e$ in $S$, we can:

-   First break the ring into a chain at $e$.
-   Then start being greedy from $e$ and continue to find the next edge where the bug is placed. Note that with appropriate preprocessing, each greedy step can achieve $O(1)$ complexity.
-   Thus solving the problem with $O(|S|)$ complexity.

We consider randomly selecting an edge $e'$ on the ring, and specifying $e'\in S$, and then perform the above process, repeating many times to obtain the optimal result.

Analyze single complexity:

-   Observation: Note that $S'$ represents the optimal solution among all the solutions that selected $e'$, then $|S'|\leq |S|+1$.
-   Therefore, the single-shot complexity is $O(|S'|)=O(|S|)$.

Analysis accuracy:

-   Obviously the single accuracy rate is $\dfrac {|S|}n$, where $n$ represents the ring length.
-   Therefore, it is necessary to repeat $-\dfrac n{|S|}\log\epsilon$ times to obtain the accuracy of $1-\epsilon$.

In summary, the complexity of this algorithm is $O\big(|S|\cdot -\dfrac n{|S|}\log\epsilon\big)=O(-n\log\epsilon)$.

### Example: [CSES 1685 New Flight Routes](https://cses.fi/problemset/task/1685)

???+ note "Brief question meaning"
    Given a directed graph, please add the minimum number of edges to make the graph strongly connected. You need **output solution**.

First, perform strong connection reduction on the original image. Our goal is obviously to make every sink point reach every source point.

It is not difficult to prove that we will only connect edges from the sink point to the source point, because any other edge can correspond to the previous edge from the sink point to the source point that is not weaker than it.

One of our core operations is to take the sink point $t$ and the source point $s$ (they do not have to be in the same weakly connected component), and connect the edge $t\to s$ so that $s$ and $t$ are no longer sink points or source points (denoted as objective I). Ideally, this operation can reduce one sink point and one source point each time. Then we continue to operate until there is only one sink point or only one source point left, and this situation is very ordinary. From this, we guess that the answer is the larger value of the number of source points and the number of sink points.

It is not difficult to find that the necessary and sufficient conditions for the above operation to achieve goal I are: $t$ has a predecessor other than $s$, and $s$ has a successor other than $t$. It can be proved (the proof will be given later) that for any DAG with at least two source points and at least two sink points, there exists such $(s,t)$; but the existence conclusion cannot help us construct a solution, and other analysis is required.

-   With this necessary and sufficient condition, it is difficult to obtain the algorithm directly. The main reason is that connecting the edge $t\to s$ may affect the legality of other $(s',t')$ tuples, which is difficult to deal with.

Noting that we know very little about the relationship between source and sink points (even a quick query whether a pair of $s-t$ is reachable requires dfs + bitset preprocessing, and the time limit does not allow this), this suggests that we need some very general and powerful properties.

Observation: $(s,t)$ that does not satisfy target I has at most $n+m-1$ pairs, where $n$ represents the number of source points and $m$ represents the number of sink points.

-   Reason: For each such pair of $(s,t)$, if it is regarded as an edge between $s,t$, then the graph formed by all these edges is like a number of disjoint chains, so the number of edges does not exceed the number of points minus one.
-   The motivation for making this observation is that in order to apply existential conclusions to algorithms, the preliminary step is often to strengthen the qualitative results into quantitative results.

Corollary: $(s,t)$ is randomly selected with equal probability, and the probability of meeting the above requirements is $\geq \dfrac {(n-1)(m-1)}{nm}$.

-   Note that this conclusion is strictly stronger than the existence conclusion given previously.

Corollary: If we independently and randomly select $\dfrac {\min(n,m)}2$ pairs of $(s,t)$ without common elements with equal probability, and operate them **sequentially** (that is, connect edges $t\to s$), then the probability of all these operations satisfying target I is $\geq \dfrac 14$.

-   reason:

$$
\begin{aligned}
&\phantom{=\ }\dfrac {(n-1)(m-1)}{nm}\cdot\dfrac{(n-2)(m-2)}{(n-1)(m-1)}\cdots\dfrac{(n-k)(m-k)}{(n-k+1)(m-k+1)}\\
&=\dfrac{(n-k)(m-k)}{nm}\\
&\geq \dfrac 14
\end{aligned}
$$

After continuously selecting $k$ and $(s,t)$, it is very simple to judge whether they all meet the target I. Just run the strongly connected contraction point again and judge whether $n,m$ has reduced by $k$. Note that if $k=\dfrac{\min(n,m)}2$ is reduced each time, $\min(n,m)$ must become 1 in $O\big(\log(n+m)\big)$ rounds, which transforms into a trivial situation.

???+ note "Algorithm pseudocode"
    ```text
    while(n>1 and m>1):
        randomly choose k=min(n,m)/2 pairs (s,t)
        add edge t->s for all these pairs
        if new_n>n-k or new_m>m-k:
            roll_back()
    solve_trivial()
    ```

Complexity $O\big((|V|+|E|) \log |V|\big)$.

***

**Review**: We need to determine any pair of binary pairs $(s,t)$ that can achieve goal I. For this purpose, we randomly select $(s,t)$.

## Using randomization to obtain properties of random data

If the data for a question is randomly generated, we may be able to use the properties of random data to solve it. In some cases, even if the data is not randomly generated, we can give it some characteristics of random data through randomization to help solve the problem.

### Example: random increment method

The randomly generated element sequence may have properties such as "the number of changes to the prefix optimal solution is expected to be very small", and the random increment method obtains these properties by randomly disrupting the input sequence.

See [Random Increment Method](../geometry/random-incremental.md) for details.

### Example: [TopCoder MagicMolecule](https://archive.topcoder.com/ProblemStatement/pm/11705) randomization method

???+ note "Brief question meaning"
    Given an undirected graph with $n$ points and point weights, find the one with the largest sum of point weights among all clusters whose size is not less than $\dfrac {2n}3$.
    
    $n\leq 50$

It is not difficult to think of half search. Divide the point set evenly into two halves $V_L,V_R$ (both sizes are $\dfrac n2$), and calculate the array $f_{L,k}$ to represent the maximum weight sum of all $\geq k$ tuples in the point set $L\subseteq V_L$. Then we enumerate each cluster $C_R$ on the right half, calculate which points on the left half are connected to all points in $C_R$ (this point set is recorded as $N_L$), and update the answer with $f_{N_L,\frac 23 n-|C_R|}+\textit{value}(C_R)$.

-   Note that $O(1)$ can be transferred to each $f_{L,k}$. Specifically, take $d$ as any element in $L$, and then discuss it in categories:
    -   Assuming that $d$ in the optimal solution is not in the group, it is transferred from $f_{L\setminus \{d\},k}$.
    -   Assuming that $d$ in the optimal solution is in the group, it is transferred from $f_{L\cap N(d),k}+\textit{value}(d)$, where $N(d)$ represents the neighbor set of $d$.
    -   Don’t forget to use $f_{L,k+1}$ to update $f_{L,k}$.

This solution will time out. Try to optimize:

-   When the point set is bisected, it is divided evenly and randomly. In this case, the point set $C_{res}$ of the optimal solution is also equally divided (i.e. $|C_{res}\cap V_L|=|C_{res}\cap V_R|$) with considerable probability.
    -   Of course, $|C_{res}|$ may be an odd number. For the sake of simplicity, it is assumed here that it is an even number; the case of an odd number does not essentially change the solution.
    -   Experiments have found that after about 20 random attempts, this property can be satisfied at least once with a high probability. In other words, if our algorithm relies on the property of "$C_{res}$ is divided equally", then repeating the algorithm 20 times to get the best result can also guarantee that the correct answer will be obtained with a high probability.
-   With this property, we can directly determine the sizes of the left group $L$ and the right group $C_R$ to be $\geq \dfrac n3$. This will bring two improvements to complexity:
    -   $f$ can omit the record size dimension.
    -   Since only groups of size $\geq \dfrac n3$ need to be considered, the number of left group $L$ and right group $C_R$ that need to be considered is also greatly reduced to about $1.8\cdot 10^6$.
-   The bottleneck now becomes finding the weight sum of a certain subset of one side, because this requires $O\big(2^{|V_L|}+2^{|V_R|}\big)$ preprocessing.
    -   Solution: Halve again inside $V_L,V_R$; when querying the weight sum of a subset, divide the subset into left and right halves for query, and then add the answers.
-   This way you can pass this question.

***

**Review**: A random set has the property that "the numerical difference between the two divided halves will not be too large", and we obtain this property through random division.

## Randomization for hashing

### Example: [UOJ #207 Covalent Master Travels to Changsha](https://uoj.ac/problem/207)

???+ note "Brief question meaning"
    Maintain a dynamically changing tree and a dynamically changing node tuple set. You need support for:
    
    -   Delete edges, add edges. You are guaranteed to get a tree.
    -   Add/delete a node tuple.
    -   Given an edge $e$, determine whether for each node tuple $(s,t)$ and $e$ in the set, they are on a simple path between $s,t$.

For each edge $e$ in the graph, we define the set $S_e$ to represent the set of critical paths passing through the edge (i.e. $(a,b)$ in the question). Consider dynamically maintaining the hash value of the set $S_e$ for each edge, so that you can easily determine whether $S_e$ is equal to the full set (that is, whether $e$ is the "only way").

The hashing method is to assign a random non-negative integer $H_{(a,b)}$ within $2^{64}$ to each $(a,b)$, and then the hash value of a set is the XOR sum of the $H$ values ​​of the elements.

In this case, the hash value of any fixed set must obey the uniform distribution on $R:=\left\{0,1,\cdots,2^{64}-1\right\}$ (in other words, the hash value range is $R$, and the probability of taking each value is equal). This is because:

1.  A single $H_{(a,b)}$ obviously obeys a uniform distribution.
2.  The XOR sum of two independent random variables that obey the uniform distribution on $R$ must also obey the uniform distribution on $R$. It is not difficult to prove it yourself.

Therefore, the accuracy of the algorithm is guaranteed.

As for how to maintain this hash value, just use LCT.

### Example: [CodeChef PANIC](https://www.codechef.com/problems/PANIC) and its error rate analysis

Rough solution to this question:

1.  It can be proved that [^ref1] $S(N)$ obeys a $O(K)$ order linear recurrence about $N$.
2.  Use the BM algorithm to find this recursive formula.
3.  With the help of recursion formula, use Cayley's Hamilton theorem to calculate $S(N)$.

Here we only focus on the second part, that is, how to find the recursive formula of a matrix sequence. So we only need to consider the following questions:

???+ note "question"
    Given a matrix sequence, which obeys a homogeneous linear recurrence in the modulo $P:=998244353$ sense (the multiplication and addition operations in the recurrence are defined as the multiplication and addition of matrices), find the shortest recurrence.

If a series of matrices obeys a recurrence formula $F$, then each bit of it must also obey $F$. However, if the shortest recurrence $F'$ is found for a certain bit, $F'$ may be shorter than $F$, causing problems.

Solution: Assign a random weight value $x_{i,j}$ with value $<P$ to each bit $(i,j)$ of the matrix, then calculate the weighted sum of all bits modulo $P$ for each matrix in the sequence, and then connect the calculated numbers for each matrix into a sequence. Finally, we run the BM algorithm on the resulting sequence.

Error rate analysis:

-   Assume that the above method obtains the $l$ order recurrence formula $F'$ that is different from $F$ (and obviously not longer than $F$).
-   Because the matrix sequence does not obey $F'$, there must be a certain position $(i,j)$ in the matrix, and the sequence $S_{i,j}$ corresponding to this position does not obey $F'$ at a certain $N$. That is to say:

$$
S(N)_{i,j}-F'_1S(N-1)_{i,j}-\cdots-F'_lS(N-l)_{i,j}\not\equiv 0\pmod {P}
$$

-   Assuming that $(i,j)$ is the only disobedient position, there must be:

$$
T_{i,j}:=\Big(x_{i,j}\cdot\big(S(N)_{i,j}-F'_1S(N-1)_{i,j}-\cdots-F'_lS(N-l)_{i,j}\big)\bmod P\Big)=0
$$

-   Obviously this is true only when $x_{i,j}=0$, with probability $P^{-1}$.
-   What if there are multiple disobedient positions?
    -   For each such position $(i,j)$, it is easy to prove that $T_{i,j}$ obeys the uniform distribution on $R:=\{0,1,\cdots,P-1\}$.
    -   For several mutually independent random variables that obey the uniform distribution on $R$, their sum in the modular sense still obeys the uniform distribution on $R$. It is not difficult to prove it yourself.
    -   Therefore, the error rate in this case is also $P^{-1}$.

### Example: [UOJ #552 Isomorphic Determination Duck](https://uoj.ac/problem/552) and its error rate analysis

???+ note "Brief question meaning"
    Given two directed graphs $G_0,G_1$ whose edge weights are lowercase letters, you need to calculate "the multiset composed of strings corresponding to all paths" (possibly an infinite set) for these two graphs, and determine whether the two multisets are equal. If they are not equal, you have to give the shortest string such that the number of occurrences in the two multisets is not equal.

Let $f_{K,i,j}$ represent all paths with length $j$ starting from point $i$ in graph $G_K$, and the hash values ​​of the multiset composed of all strings corresponding to these paths. Consider each state in ascending order of $j$. When transitioning, enumerate the outgoing edges of $i$ and specify this edge as the first edge on the path.

To determine whether there is a bad string of length $=L$, just "integrate" $\{f_{0,*,L}\}$ and $\{f_{1,*,L}\}$ and compare them (the wildcard `*` here represents each node, for example, $\{f_{0,*,L}\}$ represents the set of all $f_{0,i,L}$, where $i$ takes all nodes). The official solution [^ref2] proves that the length of the shortest bad string (if it exists) must not exceed $n_1+n_2$, so the complexity of this solution is reliable.

Next consider the specific hashing method. Note that the conventional hashing method - that is, mapping the string $a_1a_2\cdots a_k$ to $\big(a_1+Pa_2+P^2a_3+\cdots+P^{k-1}a_k\big)\bmod Q$, and then defining the hash value of the multiset as the sum of the hash values ​​of the elements modulo $Q$ - does not work here. A counterexample is that the hash value of the set `{"ab","cd"}` and the set `{"cb","ad"}` are the same, regardless of how $P,Q$ takes the value.

The problem with the above approach is that the hash value of a string is a sum, so each item in it can be taken apart and reassembled. To avoid this problem, we consider changing the hash value to a continuous multiplication. In addition, the commutative law of multiplication will make different bits indistinguishable. To avoid this, we need to assign different weights to different bits.

For each tuple $(c,j)$ (where $c$ is a character and $j$ is an integer indicating the number of $c$ in a certain string), we generate a random number $x_{c,j}$ in advance. Then we map the string $a_1a_2\cdots a_k$ to $x_{a_1,1}x_{a_2,2}\cdots x_{a_k,k}\bmod Q$ (where $Q$ is a **randomly selected** prime number), and then set the hash value of the multiset as the sum of the hash values ​​of the elements modulo $Q$. Next, analyze its error rate.

???+ note "(*)Schwartz–Zippel Lemma"
    Let $f\in F[z_1,\cdots,z_k]$ be the $d$ degree non-zero polynomial of $k$ elements on the domain $F$, let $S$ be a finite subset of $F$, then there are at most $d\cdot |S|^{k-1}$ groups $(z_1,\cdots,z_k)\in S^k$ that satisfy $f(z_1,\cdots,z_k)=0$.
    
    ??? note "If you don't know what a domain is"
        All you need to remember is that these two things are domains:
        
        1.  The remainder system of modulo prime numbers, and various operations on it.
        2.  The set of real numbers, and various operations on it.
    
    Corollary: If $z_1,\cdots,z_k$ are all independently and randomly selected from $S$ with medium probability, then $\mathrm{Pr}\big[f(z_1,\cdots,z_k)=0\big]\leq \dfrac d{|S|}$.

Let $F$ be the domain corresponding to the residual system modulo $Q$. Then for a $L\leq n_1+n_2$, $\sum\limits_i f_{0,i,L}$ and $\sum\limits_i f_{1,i,L}$ respectively correspond to a $L$ degree multivariate polynomial on $F$ with respect to the variable set $\{x_{*,*}\}$. We might as well record these two polynomials as $P_0,P_1$.

If two different string multisets have the same hash value, there are two possibilities:

1.  $P_0\equiv P_1\pmod {Q}$, that is, each coefficient of $P_0,P_1$ is equal in the modulo $Q$ sense.
2.  Although $P_0\not\equiv P_1\pmod {Q}, P_0(x_{*,*})\equiv P_1(x_{*,*})\pmod {Q}$, that is, $P_0,P_1$ are not identical, the group of $\{x_{*,*}\}$ we selected just makes their point values ​​here equal.

Analyze the probability of the former happening:

-   Observation: For any $A\neq B; A,B\leq N$ and a randomly selected prime number $Q\leq Q_{\max}$, there must be:

$$
\mathrm{Pr}\big[A\equiv B\pmod {Q}\big]=O\Big(\dfrac{\log N \log Q_{max}}{Q_{max}}\Big)
$$

-   This is because: $Q$ that makes $A\equiv B$ true must satisfy $Q\big|(A-B)$, and there are $\omega(A-B)\leq \log_2 N$ such $Q$; and according to the prime number theorem, there are $\Theta\Big(\dfrac {Q_{\max}}{\log Q_{\max}}\Big)$ different prime numbers within $Q_{\max}$. Divide the two to get the above formula.
-   In the above observation, taking $A,B$ (satisfying $A\neq B$) as the coefficient of a specific item in $P_0,P_1$ (which is equal to the number of occurrences of the string corresponding to the item in $G_0,G_1$), then it is easy to see $A,B\leq (m_1+m_2)^{L}$, and we get:

$$
\mathrm{Pr}\big[A\equiv B\pmod {Q}\big]=O\Big(\dfrac{L\log (m_1+m_2) \log Q_{max}}{Q_{max}}\Big)
$$

-   So taking $Q_{\max}\approx 10^{12}$ is more than enough. If the machine cannot support such large integer operations, double hashing can be used instead.

Analyze the probability of the latter happening:

-   In the Schwartz–Zippel lemma:
    -   Take the domain $F$ as the domain corresponding to the remainder system modulo $Q$
    -   Let $f(x_{*,*})=P_0(x_{*,*})-P_1(x_{*,*})$ be a non-zero polynomial of degree $L$
    -   Take $S=F$
-   Obtain: the desired probability $\leq \dfrac LQ$.

Note that we need to ensure correctness for each $L$, so if we want to ensure rigor, we need to use Union Bound (see later) to explain.

In practice, we don't need to randomly select the modulus, because - for example - using your own birthday as the modulus is actually equivalent to a random number.

### Example: (\*) Number of different elements in sub-matrix

???+ note "question"
    Given a matrix of $n\times m$, querying the number of different elements in a continuous submatrix $q$ times requires an online algorithm.
    
    Allow a relative error of $\epsilon$ and an error rate of $\delta$. In other words, you have to give answers to at least $(1-\delta)q$ queries that are within a relative error of no more than $\epsilon$ from the correct answer.
    
    $n\cdot m\leq 2\cdot10^5;q\leq 10^6;\epsilon=0.5,\delta=0.2$

Lemma: Let $X_{1\cdots k}$ be mutually independent random variables, and their values ​​are uniformly distributed in $[0,1]$, then $\mathrm{E}\big[\min\limits_i X_i\big]=\dfrac 1{k+1}$.

-   Proof: Consider a unit circle, on which $k+1$ points with **relative positions** are distributed uniformly and randomly, respectively at positions $0,X_1,X_2,\cdots,X_k$. Then $\min\limits_i X_i$ is equal to the length of a specific segment in the $k+1$ segment gap. And because these gaps are "symmetrical" to each other, the expected length of any specific gap is $\dfrac 1{k+1}$.

We take $k$ as the number of different elements, and use the above lemma to derive $k$ from $\min\limits_i X_i$.

Consider using a hash function to uniformly and independently randomly map each element in the matrix to a real number in $[0,1]$, and equal elements will be mapped to equal real numbers. In this case, the real numbers corresponding to all elements in a submatrix, after deduplication, are exactly an instance of the previous set $\{X_1,\cdots,X_k\}$, where $k$ is equal to the number of different elements in the submatrix.

So we get the algorithm:

1.  Assign the hash value in $[0,1]$ to the elements in the matrix. To ensure randomness, the hash function can be directly implemented using `map` and a random number generator, that is, every time it encounters a new value that has not appeared before, it will be given a random hash value.
2.  When answering the query, try to find the minimum value of the hash value $M$ in the submatrix, and output $\dfrac 1M-1$.

However, this algorithm is not satisfactory. Its expected output value is $\mathrm{E}\Big[\dfrac 1{\min\limits_i X_i}-1\Big]$, but in fact this value is not equal to $\dfrac 1{\mathrm{E}\big[\min\limits_i X_i\big]}-1=k$, but (can be proven) equal to $\infty$.

In other words, we cannot directly put the single value of $\min\limits_i X_i$ on the denominator, but must first calculate its expectation and then put the expected value on the denominator.

How to calculate expected value? Take the average multiple times randomly.

We use $C$ groups of different hash functions to perform the above process respectively. When answering the query, we calculate $C$ different $M$ values, calculate their average $\overline M$, and then output $\big(\overline M\big)^{-1}-1$.

The experiment found that $C\approx 80$ can meet the requirements. The strict proof is very cumbersome and will be omitted here.

Finally, how to find the minimum value of the submatrix? Just use a two-dimensional S-T table, preprocess $O(nm\log n\log m)$, and answer the query $O(1)$.

## Other applications of randomization in algorithms

Other effects of randomization include:

-   Prevent those who have created data from being stuck with targeted data. For example, randomly shuffling the order of neighbors during search.
-   Ensure that the "operations" performed during the algorithm are uniform (in a certain sense). For example, [Simulated Annealing](../misc/simulated-annealing.md) algorithm.

In these scenarios, randomization is often (but not always) linked to practices such as messing around and cheating on scores.

### Example: ["TJOI2015"Linear Algebra](https://loj.ac/problem/2100)

The standard algorithm for this question is network flow, but here we adopt this messy approach:

-   Each time a position is randomized, the position is inverted, the size is determined and the answer is updated.

??? note "code"
    ```cpp
    #include <algorithm>
    #include <cstdlib>
    #include <iostream>
    
    int n;
    
    int a[510], b[510], c[510][510], d[510];
    int p[510], q[510];
    
    int maxans = 0;
    
    void check() {
      memset(d, 0, sizeof d);
      int nowans = 0;
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) d[i] += a[j] * c[i][j];
      for (int i = 1; i <= n; i++) nowans += (d[i] - b[i]) * a[i];
      maxans = std::max(maxans, nowans);
    }
    
    int main() {
      srand(19260817);
      std::cin >> n;
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) std::cin >> c[i][j];
      for (int i = 1; i <= n; i++) std::cin >> b[i];
      for (int i = 1; i <= n; i++) a[i] = 1;
      check();
      for (int T = 1000; T; T--) {
        int tmp = rand() % n + 1;
        a[tmp] ^= 1;
        check();
      }
      std::cout << maxans << '\n';
    }
    ```

### Example: (\*) random heap [^ref3]

The most commonly used way to write a merged heap is to use a left-skewed tree. By maintaining the tree height and making the tree left-skewed, the complexity of the merge is ensured. However, maintaining the height of the tree is a bit troublesome, and we hope to avoid it as much as possible.

Then you can consider using a random heap, that is, not exchanging sons according to the height of the tree, but randomly exchanging.

???+ note "code"
    ```cpp
    struct Node {
      int child[2];
      long long val;
    } nd[100010];
    
    int root[100010];
    
    int merge(int u, int v) {
      if (!(u && v)) return u | v;
      int x = rand() & 1, p = nd[u].val > nd[v].val ? u : v;
      nd[p].child[x] = merge(nd[p].child[x], u + v - p);
      return p;
    }
    
    void pop(int &now) { now = merge(nd[now].child[0], nd[now].child[1]); }
    ```

Random heap does not have any hard or soft requirements on the shape of the heap. The expected complexity of the merge operation is true for any two heaps (as parameters of the `merge` function). Submit the certificate.

???+ note "Proof of expected complexity"
    It will be proved that for any heap $A$, starting from the root node and randomly choosing the left or right each time (until there is no way to go), the expected value of the path length (that is, the number of nodes on the path) is $h(A)\leq\log_2 (|A|+1)$.
    
    -   Note that in the aforementioned process, the expected complexity of the merged heap $A,B$ is $O\big(h(A)+h(B)\big)$, so the above conclusion can guarantee the expected complexity of the random heap.
    
    The proof uses mathematical induction. The boundary case is that $A$ is an empty graph, which is obvious at this time. Let $A$ be non-empty.
    
    Assume that the two subtrees of $A$ are $L,R$ respectively, then:
    
    $$
    \begin{align} h(A)
    &=1+\frac{h(L)+h(R)}2
    \\&\leq1+\frac{\log_2(|L|+1)+\log_2(|R|+1)}2
    \\&=\log_2{2\sqrt{(|L|+1)(|R|+1)}}
    \\&\leq\log_2{\frac{2\big((|L|+1)+(|R|+1)\big)}2}
    \\&=\log_2{(|A|+1)} \end{align}
    $$
    
    Certificate completed.

## Proof techniques related to randomness

Here are a few more useful techniques.

Of course, these few can't be all; if you know of any techniques not listed, please feel free to add them.

### Analysis of Probability Upper Bounds

See the [Probability Inequality](../math/probability/concentration-inequality.md) page for details.

In addition to the various inequalities mentioned on the above page, the following conclusions are often used during the derivation process:

**Use of natural constants**: $\Big(1-\dfrac{1}{n}\Big)^n\leq \dfrac{1}{\mathrm{e}},\forall n\geq1$

-   The left equation is monotonically increasing with respect to $n\geq 1$ and the limit at $+\infty$ is $\dfrac{1}{\mathrm{e}}$, so we have this conclusion.
-   This tells us that if there are $n$ independent events, each with probability $1-\dfrac 1n$, then the probability of all of them occurring is at most $\dfrac{1}{\mathrm{e}}$.

### "Coupling" thinking

The idea of ​​"coupling" is often used to process more than one random object at the same time, or to process random objects and deterministic objects at the same time.

#### Introduction: Connectivity of Random Graphs

???+ note "question"
    For $n \in \mathbf{N}^*; p,q\in [0,1]$ and $q\leq p$, verify: the expected value of the number of connected components of the random graph $G_1(n,p)$ does not exceed the expected value of the number of connected components of the random graph $G_2(n,q)$. Here $G(n,\alpha)$ represents a simple undirected graph $G$ with $n$ nodes, in which each of the $\dfrac {n(n-1)}2$ possible edges has a probability of $\alpha$, and these probabilities are independent of each other.

This conclusion seems natural, but it is not so easy to prove strictly.

???+ note "Proof idea"
    We assume that these two pictures use a 01 random number generator to know whether each edge exists or not. The generator $T_1$ of $G_1$ outputs 1 with a probability of $p$ every time, and the generator $T_2$ of $G_2$ outputs 1 with a probability of $q$ every time. In this way, to construct a graph, you only need to run the corresponding generator $\dfrac {n(n-1)}2$ times.
    
    Now we combine the two generators into one. Consider the random number generator $T$, which outputs 0 with a probability of $q$, 1 with a probability of $p-q$, and 2 with a probability of $1-p$. If we run this $T$ $\dfrac {n(n-1)}2$ times, we can construct $G_1$ and $G_2$ at the same time. Specifically, if the output is 0, it is considered that there is no currently considered edge in $G_1$ and $G_2$; if the output is 1, it is considered that only $G_1$ has the currently considered edge; if the output is 2, it is considered that both $G_1$ and $G_2$ have currently considered edges.
    
    It is easy to verify that the $G_1$ and $G_2$ generated in this way conform to their definitions, and in each instance, the edge set of $G_2$ is a subset of the edge set of $G_1$. Therefore, in each instance, the number of connected components of $G_2$ is not less than the number of connected components of $G_1$; then the expected value naturally satisfies the same size relationship.

The idea used in this proof is called "coupling", and this idea can be understood literally. In this case, it is embodied in combining two originally independent random processes into one.

#### Application: [NERC 2019 Problem G: Game Relics](https://codeforces.com/contest/1267/problem/G)

???+ note "Brief question meaning"
    There are several items, each item has a price $c_i$. You want to get all the items, and to do so you can do either of two things:
    
    1.  Choose an item $i$ that you don’t own and buy it for $c_i$ yuan.
    2.  Spend $x$ dollars to randomly select one from all items (including those you already own) with a medium probability. If you don't already own the item, get it directly; otherwise, get nothing, but $\dfrac x2$ dollars will be returned. $x$ is the input constant.
    
    Ask about the expected cost under the optimal strategy.

Observation: If you choose to draw items, you will definitely keep drawing until you get new items.

-   Reason: If no new item is obtained after drawing once, the new situation will be exactly the same as the situation before the item was drawn. Therefore, if the optimal action in the old situation is "drawing one shot", the optimal action in the new situation must also be "drawing another shot".

We can calculate $f_k$ which means: if we already have $k$ different items, how much money do we expect to spend to draw new items. Based on the observations just now, we can directly regard $f_k$ as a fixed price, that is, convert it into "each time you spend $f_k$ yuan to randomly obtain a new item."

???+ note "Calculation of expected cost"
    Obviously $f_k=\dfrac x2 \cdot (R-1)+x$, where $R$ represents the expected number of draws to get new items.
    
    Lemma: If a coin has a probability of $p$ that it will come up heads, then the expected number of times it takes to flip heads for the first time is $\dfrac 1p$.
    
    -   Perceptual understanding: $\dfrac 1p \cdot p = 1$, so it seems more right to throw it so many times and expect to get 1 head.
    -   This perceptual understanding can be made rigorous through the [law of large numbers](https://en.wikipedia.org/wiki/Law_of_large_numbers), that is, consider $n\to \infty$ experiments of "continuously tossing a coin until you get heads". The details of the derivation are omitted.
    -   Another feasible way to prove it is to directly bring the definition of expectation into the calculation. The details of the derivation are omitted.
    
    Obviously the probability of getting a new item by drawing once is $\dfrac {n-k}n$, then $R=\dfrac n{n-k}$.

Conclusion: The optimal strategy must be to draw a few items first, and then buy all the undrawn items.

This conclusion is intuitive, because $f_k$ is increasing with respect to $k$, and early draw does seem to be better than late draw.

???+ note "prove"
    Consider first proving a special case. Will prove:
    
    -   Random process $A$: first buy item $x$, and then continue to draw until you get all the items
    -   ...must not be better than...
    -   Random process $B$: Keep drawing until you get all items except $x$, and then buy $x$ if you don’t have it yet
    
    Consider letting the random process $A$ and the random process $B$ use the same random number generator. That is, the first extraction of $A$ and the first extraction of $B$ will extract the same element, and the same will happen for the second and third times...
    
    Obviously, at this time, the number of extractions of $A$ and $B$ must be equal. For an item $y\neq x$ drawn by $A$, observe:
    
    -   The number of items already held when $y$ is drawn from $A$ must be greater than or equal to the number of items already held when $y$ is drawn from $B$.
    
    Therefore, the single extraction cost of $B$ is not higher than the single extraction cost of $A$, and the total extraction cost is not higher than $A$.
    
    Obviously, the purchase price of $B$ is also not higher than $A$. To sum up, $B$ must not be inferior to $A$.
    
    This conclusion can then be extended to general situations through mathematical induction. Specifically, every time we find the last purchase in the current strategy, and then based on the above conclusion, it is not bad to move this purchase to the end. Details omitted.

Based on this conclusion, we equivalently transform the problem again: changing the operation of "choose an item and pay the corresponding price to buy" to "randomly select an item that you don't own and pay the corresponding price to buy it." The reason for equivalence is that since the purchase is only for cleaning up, it doesn't matter which one you choose.

Now we find that "extraction" and "purchase" have essentially become the same operation, the only difference is the price paid. Choosing to buy or draw has no effect on the order in which items are obtained, and each order in which items are obtained is equally possible.

Observation: At a certain moment, we should choose to buy if and only if the cost of the next draw (determined by the number of items that have been drawn) is greater than the average price of the remaining items (if equal, it is arbitrary).

-   It can be proved that as time goes on, the growth rate of the drawing cost is never lower than the growth rate of the average price of the remaining items. This shows that there is only one "critical point" from drawing to buying, which further verifies the previous conclusion.

Finally, we enumerate all possible situations (that is, the set of elements we already have), calculate the probability of this situation occurring (the number of arrangement options for existing elements divided by the total number of options), multiply this by the cost of the optimal decision in the current situation (determined by the number of elements we have and the total price of the remaining items), and add it all up. This process can be optimized using backpack-style DP, and this question can be passed.

***

**Review**: It can be seen that the coupling technique is used twice in this question. The first time is to make the two random processes use the same random source during the proof process; the second time is to convert the purchase into a random purchase (that is, introduce a random source), so that the two operations of purchase and extraction are essentially "coupled" into the same operation (that is, the extraction and purchase operations share a random source).

## References

[^ref1]: [PANIC - Editorial](https://discuss.codechef.com/t/panic-editorial/80145)

[^ref2]: [UOJ NOI Round #4 Day2 Problem Solution](https://peehs-moorhsum.blog.uoj.ac/blog/6375)

[^ref3]: [Anna Gambin and Adam Malinowski, Randomized Meldable Priority Queues](https://www.researchgate.net/publication/2801527_Randomized_Meldable_Priority_Queues)
