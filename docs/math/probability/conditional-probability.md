## Overview

When some event has already occurred, the probabilities of some random events change due to the increase in known information. For example, when drawing in a mobile game, we might think that getting a 6-star and not getting a 6-star in a single draw are equally likely. But after drawing 50 times without a single 6-star, insisting that "getting and not getting a 6-star are equally likely" seems less reasonable.

In any case, studying the probability of events under certain known conditions is necessary.

## Conditional Probability

### Definition

If event $A$ is known to have occurred, the probability of event $B$ occurring under this condition is called **conditional probability**, denoted $P(B|A)$.

In the probability space $(\Omega, \mathcal{F}, P)$, if event $A \in \mathcal{F}$ satisfies $P(A) > 0$, then the conditional probability $P(\cdot|A)$ is defined as

$$
P(B|A) = \frac{P(AB)}{P(A)} \quad \forall B \in \mathcal{F}
$$

It can be verified that $P(\cdot|A)$ defined by the above formula is a probability function on $(\Omega, \mathcal{F})$.

The following two equalities can be directly derived from the definition of conditional probability:

-   **Multiplication rule of probability**: In the probability space $(\Omega, \mathcal{F}, P)$, if $P(A) > 0$, then for any event $B$,

$$
P(AB) = P(A)P(B|A)
$$

-   **Law of total probability**: In the probability space $(\Omega, \mathcal{F}, P)$, if a set of events $A_1, \cdots, A_n$ are pairwise disjoint and their union is $\Omega$, then for any event $B$,

$$
P(B) = \sum_{i=1}^{n} P(A_i)P(B|A_i)
$$

### Bayes' Formula

Generally, let the causes that could lead to event $B$ be $A_1, A_2, \cdots, A_n$. When $P(A_i)$ and $P(B|A_i)$ are known, the probability of event $B$ can be calculated using the law of total probability. But in many cases, we need to infer the probabilities of each cause event occurring based on the result that "event $B$ occurred." Thus,

$$
P(A_i|B) = \frac{P(A_iB)}{P(B)} = \frac{P(A_i)P(B|A_i)}{\sum_{j=1}^{n} P(A_j)P(B|A_j)}
$$

The above is Bayes' formula.

## Independence of Events

In the study of conditional probability, the situation $P(B|A) = P(B)$ may occur. Intuitively, this means that whether event $B$ occurs does not tell us any information about event $A$; that is, event $B$ is "unrelated" to event $A$. Hence we have the following definition.

### Definition

If events $A$ and $B$ in the same probability space satisfy

$$
P(AB) = P(A)P(B)
$$

then $A$ and $B$ are said to be **independent**. For multiple events $A_1, A_2, \cdots, A_n$, we say they are independent if and only if for any set of events $\{ A_{i_k} : 1 \leq i_1 < i_2 < \cdots < i_k \leq n \}$,

$$
P( A_{i_1}A_{i_2} \cdots A_{i_r} ) = \prod_{k=1}^{r} P(A_{i_k})
$$

### Independence of Multiple Events

For multiple events, pairwise independence generally does not imply joint independence. Consider the following counterexample:

There is a regular tetrahedron die, with three faces painted red, green, and blue respectively, and the remaining face having all three colors. Now roll this die once. Let events $A$, $B$, $C$ respectively represent that the face touching the table contains red, green, and blue.

It is easy to calculate $P(A) = P(B) = P(C) = \frac{1}{2}$, and $P(AB) = P(BC) = P(CA) = P(ABC) = \frac{1}{4}$.

Clearly $A, B, C$ are pairwise independent, but since $P(ABC) \neq P(A)P(B)P(C)$, $A, B, C$ are not independent.
