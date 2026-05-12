## Derangements

### Definition

A derangement is a permutation where no element appears in its original position. That is, for a permutation $P$ of $1 \sim n$, if $P_i \neq i$, then $P$ is called a derangement of $n$.

For example, the 3-element derangements are $\{2,3,1\}$ and $\{3,1,2\}$. The 4-element derangements are $\{2,1,4,3\}$, $\{2,3,4,1\}$, $\{2,4,1,3\}$, $\{3,1,4,2\}$, $\{3,4,1,2\}$, $\{3,4,2,1\}$, $\{4,1,2,3\}$, $\{4,3,1,2\}$, and $\{4,3,2,1\}$. Derangements are permutations with no fixed points, i.e., no cycles of length 1.

### Calculation using Inclusion-Exclusion Principle

The universal set $U$ is the set of permutations of $1 \sim n$, $|U| = n!$; let $S_i$ be the set of permutations satisfying $P_i \neq i$. Using complement and knowledge of the [Inclusion-Exclusion Principle](./inclusion-exclusion-principle.md), the problem becomes finding:

$$
\begin{aligned}
\left|\bigcap_{i=1}^n S_i\right|
&= |U| - \left|\bigcup_{i=1}^n \overline{S_i}\right|\\
&= n! - \sum_{k=1}^n (-1)^{k-1} \sum_{a_i < a_{i+1}} \left|\bigcap_{i=1}^k \overline{S_{a_i}}\right|
\end{aligned}
$$

Here, the sum means taking $a_1, a_2, \ldots, a_k$ from $1, 2, \cdots, n$ with $a_i < a_{i+1}$. Then

$$
\left|\bigcap_{i=1}^k \overline{S_{a_i}}\right|
$$

represents the number of permutations where $k$ numbers $a_1, a_2, \ldots, a_k$ satisfy $P_{a_i} = a_i$, while the remaining $n - k$ numbers can be in any positions. Therefore:

$$
\left|\bigcap_{i=1}^k \overline{S_{a_i}}\right| = (n - k)!
$$

There are $\binom{n}{k}$ ways to choose these $k$ numbers. Summing over all $k$:

$$
\begin{aligned}
&\sum_{k=1}^n (-1)^{k-1} \sum_{a_i < a_{i+1}} \left|\bigcap_{i=1}^k \overline{S_{a_i}}\right|\\
=&\sum_{k=1}^n (-1)^{k-1} \binom{n}{k} (n - k)!\\
=&\sum_{k=1}^n (-1)^{k-1} \frac{n!}{k!}\\
=&n! \sum_{k=1}^n \frac{(-1)^{k-1}}{k!}
\end{aligned}
$$

Therefore, the number of derangements of $n$ elements is:

$$
D_n = n! - n! \sum_{k=1}^n \frac{(-1)^{k-1}}{k!} = n! \sum_{k=0}^n \frac{(-1)^k}{k!}
$$

The first few terms of the derangement sequence are $0, 1, 2, 9, 44, 265$ ([OEIS A000166](http://oeis.org/A000166)).

### Calculation using Recurrence

Let's make the derangement problem concrete. Consider this problem:

There are $n$ different letters, numbered $1, 2, 3, 4, 5$. We need to put these five letters into envelopes numbered $1, 2, 3, 4, 5$, requiring that the envelope number is different from the letter number. How many different placement methods are there?

Consider the $n$-th envelope. Initially, temporarily put the $n$-th letter in the $n$-th envelope, then consider the recurrence for two cases:

-   All the first $n - 1$ envelopes are incorrectly filled;
-   Among the first $n - 1$ envelopes, one is not incorrectly filled, and the rest are incorrectly filled.

For the first case: All first $n - 1$ envelopes are incorrectly filled. Since the first $n - 1$ are all incorrectly filled, the $n$-th letter just needs to be swapped with any of the previous positions. There are $D_{n-1} \times (n - 1)$ cases.

For the second case: Among the first $n - 1$ envelopes, one is not incorrectly filled, and the rest are incorrectly filled. Consider this case: if among the $n - 1$ envelopes there is one that is not incorrectly filled, then swapping that with $n$ gives a complete derangement.

Other cases cannot become a derangement of length $n$ through a single operation.

Thus, the number of derangements satisfies the recurrence:

$$
D_n = (n - 1)(D_{n-1} + D_{n-2})
$$

Here is another recurrence:

$$
D_n = n D_{n-1} + {(-1)}^n
$$

### Other Relationships

The number of derangements has a simple rounding expression, with growth speed differing from factorial only by a constant:

$$
D_n = \left\lfloor \frac{n!}{\mathrm{e}} + \frac{1}{2} \right\rfloor
$$

As the number of elements increases, the probability $P$ of forming a derangement approaches:

$$
P = \lim_{n \to \infty} \frac{D_n}{n!} = \frac{1}{\mathrm{e}}
$$