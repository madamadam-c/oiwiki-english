## Overview

When studying concrete random phenomena, we usually focus on the following elements:

-   Sample space $\Omega$, which specifies all possible outcomes of the random phenomenon.
-   Event field $\mathcal{F}$, representing all events we care about.
-   Probability $P$, describing the likelihood of each event occurring.

## Sample Space and Random Events

### Definition

The indivisible possible outcomes of a random phenomenon are called **sample points**. The set of all sample points is called the **sample space**, usually denoted by $\Omega$.

A **random event** is a subset of the sample space $\Omega$, consisting of several sample points, and is denoted by capital letters $A, B, C, \cdots$.

For an outcome $\omega$ of a random phenomenon and a random event $A$, we say event $A$ **occurred** if and only if $\omega \in A$.

For example, the number obtained from rolling a die once is a random phenomenon, and its sample space can be expressed as $\Omega = \{1, 2, 3, 4, 5, 6\}$. Let random event $A$ be "the number obtained is greater than $4$", then $A = \{5, 6\}$. If in a particular roll the number $\omega = 3$, since $\omega \notin A$, event $A$ did not occur.

### Operations on Events

Since we define random events as subsets of the sample space $\Omega$, we can apply set operations (such as intersection, union, complement, etc.) to random events. The notation is consistent with set operations.

Specifically, the union of events $A \cup B$ can also be written as $A + B$, and the intersection $A \cap B$ can also be written as $AB$. In this context, they may also be called **sum events** and **product events** respectively.

## Event Field

When studying concrete random phenomena, we need to determine which events interest us. According to the definition of random events, we clearly have $\mathcal{F} \subset 2^{\Omega}$ (where $2^{\Omega}$ denotes the power set of $\Omega$), but $\mathcal{F} = 2^{\Omega}$ is not required. This may be somewhat difficult to understand when the sample space $\Omega$ is finite, since $2^{\Omega}$ is larger but still finite. When $\Omega$ is an infinite set, the cardinality of $2^{\Omega}$ becomes even larger, and inevitably there will be some "pathological" events that we don't care about. In this case, giving up some properties to accommodate these events would not be worth the cost.

Although $\mathcal{F} = 2^{\Omega}$ is not required, this does not mean that any subset of $2^{\Omega}$ can become an event field. We are usually interested in the probabilities of events obtained by performing operations on some events, so we require the event field $\mathcal{F}$ to satisfy the following conditions:

-   $\varnothing \in \mathcal{F}$;
-   If $A \in \mathcal{F}$, then the complement $\bar{A} \in \mathcal{F}$;
-   If there is a sequence of events $A_n \in \mathcal{F}, n = 1, 2, 3\dots$, then $\bigcup A_n \in \mathcal{F}$.

In short, the event field $\mathcal{F}$ is closed under complement and countable union, and contains the element $\varnothing$.

It can be proven that an event field $\mathcal{F}$ satisfying the three conditions above is also closed under countable intersection.

Taking die rolling as an example, when the sample space is $\Omega = \{1, 2, 3, 4, 5, 6\}$, the following two sets can serve as event fields:

-   $\mathcal{F}_1 = \{ \varnothing, \Omega \}$
-   $\mathcal{F}_2 = \{ \varnothing, \{1, 3, 5\}, \{2, 4, 6\}, \Omega \}$

But the following two sets cannot:

-   $\mathcal{F}_3 = \{ \varnothing, \{1\}, \Omega \}$ (not closed under complement)
-   $\mathcal{F}_4 = \{ \{1, 3, 5\}, \{2, 4, 6\} \}$ (does not contain $\varnothing$ and is not closed under union)

## Probability

### Definition

#### Classical Definition

In the early practice of probability theory, since the random phenomena involved were relatively simple, specifically with finite sample space $\Omega$ and intuitively all sample points equally likely to occur, people derived the following definition:

If a random phenomenon satisfies:

-   There are only finitely many elementary outcomes;
-   Each elementary outcome is equally likely to occur;

Then for each event $A$, its probability is defined as

$$
P(A) = \frac{\#(A)}{\#(\Omega)}
$$

where $\#(\cdot)$ denotes the measure of the size of a random event (a set).

Later, people found that this definition can be directly extended to some scenarios where $\Omega$ is infinite, leading to what is called the [geometric probability model](https://en.wikipedia.org/wiki/Geometric_probability).

#### Axiomatic Definition

The above intuitive definition has a significant logical flaw: the concept of "probability" is defined using the term "likelihood," creating a circular definition. At the same time, "equally likely" becomes ambiguous when the sample space is infinite, leading to a series of problems including the [Bertrand paradox](https://en.wikipedia.org/wiki/Bertrand%27s_paradox).

After continuous exploration, Soviet mathematician Kolmogorov first gave the axiomatic definition of probability in 1933 in his book "Foundations of Probability Theory":

The probability function $P$ is a mapping from the event field $\mathcal{F}$ to the closed interval $[0, 1]$, satisfying:

-   **Normality**: The probability of event $\Omega$ is $1$, i.e., $P(\Omega) = 1$.
-   **Countable additivity**: If a sequence of events $A_1, A_2, \cdots$ are pairwise disjoint, then $P\left( \bigcup_{i \geq 1} A_i \right) = \sum_{i \geq 1} P(A_i)$.

### Properties of Probability Functions

For any random events $A, B \in \mathcal{F}$:

-   **Monotonicity**: If $A \subset B$, then $P(A) \leq P(B)$.
-   **Inclusion-exclusion principle**: $P(A + B) = P(A) + P(B) - P(AB)$.
-   $P(A - B) = P(A) - P(AB)$, where $A - B$ denotes the set difference.

## Probability Space

At the beginning, we mentioned that when studying concrete random phenomena, we usually focus on the sample space $\Omega$, the event field $\mathcal{F}$, and the probability function $P$. We call the triple $(\Omega, \mathcal{F}, P)$ a **probability space**.

Probability only has meaning when discussed in a determined probability space. The Bertrand paradox mentioned earlier is fundamentally caused by an unclear definition of the sample space $\Omega$.

## References and Notes

-   [Probability Theory (mathematical branch) - Wikipedia](https://en.wikipedia.org/wiki/Probability)
-   [Probability Theory - Baidu Baike](https://baike.baidu.com/item/概率论/829122)
