## Definition

The drawer principle, also known as the pigeonhole principle (the pigeonhole principle).

It is often used for existence proofs and finding worst-case solutions.

## Simple Case

Dividing $n + 1$ objects into $n$ groups, there must be at least one group containing two or more objects.

This theorem seems obvious. The proof uses proof by contradiction: if each group has at most 1 object, then there can be at most $1 \times n = n$ objects, but we actually have $n + 1$ objects, a contradiction.

## Generalization

Dividing $n$ objects into $k$ groups, there must exist at least one group containing greater than or equal to $\left\lceil \dfrac{n}{k} \right\rceil$ objects.

The generalized form can also be proven by proof by contradiction: if each group has less than $\left\lceil \dfrac{n}{k} \right\rceil$ objects, then their sum $S \leq (\left\lceil \dfrac{n}{k} \right\rceil - 1) \times k = k\left\lceil \dfrac{n}{k}\right\rceil - k < k(\dfrac{n}{k} + 1) - k = n$, a contradiction.

Furthermore, the partition can be weakened to a cover while the conclusion remains unchanged.
Given a set $S$, a family of nonempty subsets of $S$ $\{A_1, A_2 \ldots A_k\}$

-   If $\bigcup_{i=1}^k A_i = S$, it is called a cover of $S$.
-   If a cover also satisfies $i \neq j \rightarrow A_i \cap A_j = \varnothing$, it is called a partition of $S$.

The pigeonhole principle can be stated as: for a cover of $S$, $\{A_1, A_2 \ldots A_k\}$, there is at least one set $A_i$ satisfying $\left| A_i \right| \geq \left\lceil \dfrac{|S|}{k} \right\rceil$.

## References

-   [Wikipedia: Pigeonhole principle](https://en.wikipedia.org/wiki/Pigeonhole_principle)
-   *Discrete Mathematics and Its Applications*: Chapter 6, Section 1