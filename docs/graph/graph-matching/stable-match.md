## Introduction

The **stable matching problem** is a classic problem in combinatorial optimization and cooperative game theory. Compared to traditional graph theory matching problems, stable matching introduces individual preferences and stability constraints, which makes algorithm design rely more on preference orderings than on pure graph structure. In the stable matching problem model, each individual has preferences over potential match partners, and the stable matching problem seeks to establish a stable matching among them. In a stable matching, there is no group of individuals who would collude to deviate from the current matching because they could get better options. Stable matching and related problems are widely used in labor markets, school admissions, medical resource allocation, and other scenarios.

The stable matching problem most frequently encountered in competitive programming is one-to-one matching in two-sided markets, namely the stable marriage problem. This article will focus on introducing the stable marriage problem and its algorithms.

## Stable Marriage Problem

The stable marriage problem is the earliest studied stable matching problem. Similar to bipartite graph matching, it can be described as a matching problem in the marriage market: suppose there are several men and women, each having a strict preference ordering over members of the opposite sex. The goal is to find a matching such that there is no man and woman who would rather abandon their current partners and choose each other.

### Problem Description

The matching market consists of several men $M$ and several women $W$. Each person has a strict preference ordering over the opposite sex:

-   For each man $m\in M$, there exists a strict total order $\preceq_m$ on the set $W\cup\{m\}$.
-   For each woman $w\in W$, there exists a strict total order $\preceq_w$ on the set $M\cup\{w\}$.

In addition to comparing with members of the opposite sex, each person also includes themselves in this preference ordering. This means a person will only accept matching with members of the opposite sex who are ranked higher than themselves; these members are called **acceptable**. Obviously, the preference ordering over unacceptable members of the opposite sex is irrelevant; in principle, we only need to give the preference ordering among acceptable members. Therefore, preferences that include unacceptable members are also called **preferences with incomplete lists**.

???+ example "Example"
    Suppose $m$ is a man, and $w_1,w_2,w_3$ are three women, with the preference relation $w_1\prec_m m \prec_m w_2\prec_m w_3$. Then, the man $m$ prefers being single over being matched with woman $w_1$; prefers being matched with woman $w_2$ over being single; and prefers being matched with woman $w_3$ over being matched with woman $w_2$. For man $m$, woman $w_1$ is unacceptable, while women $w_2,w_3$ are acceptable.

A **matching** $\mu:M\cup W\rightarrow M\cup W$ in the market must satisfy the following properties:

-   Each person can only be matched with someone of the opposite sex or themselves, i.e., for all $m\in M$, we have $\mu(m)\in W\cup\{m\}$, and for all $w\in W$, we have $\mu(w)\in W\cup\{w\}$.
-   Matching is mutual, i.e., for all $i\in M\cup W$, we have $i = \mu(\mu(i))$.

There are two types of instability in a matching $\mu$:

-   If there exists an individual $i\in M\cup W$ such that $\mu(i)\prec_i i$, that is, the individual $i$ would rather be single than stay with their current match, then $i$ is called a **blocking individual** of matching $\mu$.
-   If there exists a pair of opposite-sex individuals $m\in M$ and $w\in W$ such that $\mu(m)\prec_m w$ and $\mu(w)\prec_w m$, that is, the man $m$ and woman $w$ would rather be with each other than with their current partners, then $(m,w)$ is called a **blocking pair** of matching $\mu$.

If a matching $\mu$ has neither blocking individuals nor blocking pairs, it is called **stable**. In a stable matching, no one can disrupt the current situation: single people cannot find someone willing to be with them; married people neither want to divorce and be single, nor can they find someone willing to elope with them.

The stable matching problem asks: for any given set of preference orderings, does a stable matching exist? If so, how to find such a stable matching?

### Gale–Shapley Algorithm

Gale and Shapley proposed the **deferred acceptance algorithm** in 1962, which can find a stable matching for any given set of preference orderings. Therefore, stable matchings always exist.

The Gale–Shapley algorithm has two symmetric versions: one where men propose and one where women propose. Taking the men-proposing Gale–Shapley algorithm as an example, the algorithm works as follows:

1.  At the beginning of the algorithm, each woman is considered to hold her own proposal, and all men are marked as active.
2.  An active man proposes to the most preferred woman among those he finds acceptable and has not yet proposed to; if no such woman exists, no action is taken. Regardless of whether a proposal is made, all men are marked as inactive.
3.  When a woman receives new proposal requests, she compares them with the proposals she previously held, keeping only the most preferred one (which may be her own) and rejecting all others. The rejected men are marked as active again.
4.  Repeat the previous two steps until there are no active men. At this point, each woman accepts the proposal she currently holds. The resulting matching is a stable matching.

Since each man proposes to each woman at most once, the algorithm always terminates in $O(|M||W|)$ time.

The reference implementation is as follows:

??? example "Template Problem [SPOJ STABLEMP - Stable Marriage Problem](https://www.spoj.com/problems/STABLEMP/) Reference Implementation"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/stable-match/stable-match.cpp"
    ```

### Properties of Stable Matchings

Stable matchings have nice theoretical properties. First, the Gale–Shapley algorithm constructively proves that stable matchings always exist.

???+ note "Theorem 1 (Gale and Shapley, 1962)"
    The matching obtained by the Gale–Shapley algorithm is a stable matching. Therefore, stable matchings exist.

??? note "Proof"
    Men do not propose to women they find unacceptable, and women immediately reject men they find unacceptable. Therefore, the final mutually matched man and woman must accept each other, so there cannot be blocking individuals. To prove it is a stable matching, we only need to show there are no blocking pairs.

    Proof by contradiction. Suppose $(m,w)$ is a blocking pair. Then, before man $m$ proposes to $\mu(m)$, he must have already proposed to $w$. But since woman $w$ rejected $m$, she must have received a proposal from someone she prefers, say $m'$. If $m'\neq \mu(w)$, then woman $w$ prefers $\mu(w)$ over $m'$. Therefore, relative to $m$, woman $w$ definitely prefers her final match $\mu(w)$. This contradicts that $(m,w)$ is a blocking pair. So the matching is stable.

???+ note "Corollary"
    If $|M|=|W|$ and all members of the opposite sex are acceptable, then there exists a stable perfect matching.

In the Gale–Shapley algorithm, either men can propose or women can propose. In general, the two versions of the Gale–Shapley algorithm produce different stable matchings. In fact, the stable matching obtained by the men-proposing Gale–Shapley algorithm is the most favorable to all men among all stable matchings; and vice versa.

???+ note "Theorem 2 (Gale and Shapley, 1962)"
    Let $\mu_M$ and $\mu_W$ be the stable matchings obtained by the men-proposing and women-proposing Gale–Shapley algorithms respectively. For any stable matching $\mu$, we have $\mu(m)\preceq_m\mu_M(m)$ for all $m\in M$, and $\mu(w)\preceq_w\mu_W(w)$ for all $w\in W$.

??? note "Proof"
    By symmetry, we only need to prove $\mu(m)\preceq_m\mu_M(m)$ for all $m\in M$. To do this, still consider the men-proposing Gale–Shapley algorithm, and denote by $k(m,w)$ the round in which woman $w$ rejects man $m$'s proposal. This round number is well-defined for all $(m,w)$ satisfying $\mu_M(m)\prec_m w$.

    Suppose $\mu_M$ is not the most favorable to all men, that is, there exists a stable matching $\mu$ and a man $m\in M$ such that $\mu_M(m)\prec_m\mu(m)$ holds. Since $\mu_M$ is stable, we have $m\preceq_m\mu_M(m)\prec_m\mu(m)$, so $\mu(m)$ is a woman, and $k(m,\mu(m))$ is well-defined. Then, let $m$ be exactly such a man with the smallest $k(m,\mu(m))$. During the algorithm, when woman $w=\mu(m)$ rejects man $m$, she keeps the proposal from man $m'$, that is, $m=\mu(w)\prec_w m'$. Since $\mu$ is a stable matching, $(w,m')$ cannot be a blocking pair, and since $\mu(m')\neq w$, we have $w\prec_{m'}\mu(m')$. During the Gale–Shapley algorithm, woman $w$ may not keep $m'$'s proposal until the end, so $\mu_M(m')\preceq_{m'}w\prec_{m'}\mu(m')$. At this point, $k(m',\mu(m'))$ is well-defined. Moreover, since $w\prec_{m'}\mu(m')$, after woman $\mu(m')$ rejects $m'$'s proposal, $w$ keeps $m'$'s proposal, that is, $k(m',\mu(m')) < k(m,\mu(m))$. This contradicts the choice of $m$. Therefore, by proof by contradiction, $\mu_M$ is the stable matching most favorable to all men.

A matching market may have an exponentially large number of stable matchings. Let $\mathcal S$ be the set of all stable matchings. On this set, we can define two partial orders:

-   $\mu_1\preceq_M\mu_2$ if and only if $\mu_1(m)\preceq_m\mu_2(m)$ holds for all $m\in M$.
-   $\mu_1\preceq_W\mu_2$ if and only if $\mu_1(w)\preceq_w\mu_2(w)$ holds for all $w\in W$.

These two partial orders represent matchings that are better for all men and all women respectively. In general, two stable matchings may not be comparable. However, any two stable matchings can be decomposed as shown in the figure, such that in the three resulting parts, $\mu_1\preceq_M\mu_2$, $\mu_1=\mu_2$, and $\mu_2\preceq_M\mu_1$ hold respectively. Note that although not directly shown, the part where $\mu_1=\mu_2$ actually includes the case of being matched to oneself (i.e., unmatched).

![](./images/stable-match-decompose.svg)

This decomposition relies on the following lemma:

???+ note "Lemma (Knuth, 1976)"
    Let $\mu_1$ and $\mu_2$ be two stable matchings. Let $M(\mu_i)=\{m\in M : \mu_j(m)\prec_m\mu_i(m)\}$ and $W(\mu_i)=\{w\in W:\mu_j(w)\prec_w\mu_i(w)\}$ be the sets of men and women who prefer the matching in $\mu_i$ over that in $\mu_j$, where $i,j=1,2$ and $i\neq j$. Then both $\mu_1$ and $\mu_2$ are bijections between $M(\mu_1)$ and $W(\mu_2)$, as well as between $M(\mu_2)$ and $W(\mu_1)$.

??? note "Proof"
    Let $m\in M(\mu_1)$. Since $m\preceq_m \mu_2(m)\prec_m\mu_1(m)$, we have $\mu_1(m)\in W$. Let $w=\mu_1(m)$. Since $\mu_2(w)\neq m$, and $\mu_2(w)\prec_w m$ implies $(m,w)$ is a blocking pair of $\mu_2$, we have $\mu_1(w)=m\prec_w\mu_2(w)$. That is, $w\in W(\mu_2)$. This shows $\mu_1(M(\mu_1))\subseteq W(\mu_2)$. By symmetry, we can also establish $\mu_2(W(\mu_2))\subseteq M(\mu_1)$. Since both $\mu_1$ and $\mu_2$ are injections, we have $|M(\mu_1)|=|W(\mu_2)|$ and both mappings are surjections. This shows that both $\mu_1$ and $\mu_2$ are bijections between $M(\mu_1)$ and $W(\mu_2)$. Similarly, they are also bijections between $M(\mu_2)$ and $W(\mu_1)$.

This lemma shows that the partially ordered sets $(\mathcal S,\preceq_M)$ and $(\mathcal S,\preceq_W)$ are [duals](../../math/order-theory.md#duality) of each other. Moreover, under each partial order, the set $\mathcal S$ forms a [lattice](../../math/order-theory.md#directed-sets-and-lattices). Since $\mathcal S$ is finite, both lattices must have maximum and minimum elements. These two extreme elements are precisely the stable matchings obtained by the two versions of the Gale–Shapley algorithm mentioned earlier.

???+ note "Theorem 3 (Conway and Knuth, 1976)"
    The partially ordered sets $(\mathcal S,\preceq_M)$ and $(\mathcal S,\preceq_W)$ are mutually dual lattices. Moreover, $\mu_M$ and $\mu_W$ are respectively the maximum and minimum elements of $(\mathcal S,\preceq_M)$, and also the minimum and maximum elements of $(\mathcal S,\preceq_W)$ respectively.

??? note "Proof"
    According to the lemma, it is easy to show the two partially ordered sets are duals. If $\mu_1\preceq_M\mu_2$, this means $M(\mu_1)=\varnothing$; by the lemma, $W(\mu_2)=\varnothing$, which is $\mu_2\preceq_W\mu_1$. And vice versa. This shows they are mutually duals. Combined with Theorem 2 from before, we get that $\mu_M$ and $\mu_W$ are the extreme elements of the two partially ordered sets. What remains to be proved is that the two partially ordered sets are lattices. By symmetry, we only need to prove $(\mathcal S,\preceq_M)$ is a lattice. Then, by the symmetry of join and meet operations, we only need to prove that the join of stable matchings is still a stable matching. Formally, for any $\mu_1,\mu_2\in\mathcal S$, we need to prove that the matching $\mu=\mu_1\lor_M\mu_2$ defined by $\mu(m)=\mu_1(m)\lor_m\mu_2(m)$ for all $m\in M$ is a stable matching, where $\lor_m$ is the join operation in the total order $\preceq_m$ (i.e., the one that $m$ prefers more).

    Still using the notation from the lemma. For $i\in M(\mu_1)\cup W(\mu_2)$, we have $\mu(i)=\mu_1(i)$; otherwise, $\mu(i)=\mu_2(i)$. Since both $\mu_1$ and $\mu_2$ are stable, there are no blocking individuals, so $\mu$ has no blocking individuals either. Suppose $(m,w)$ is a blocking pair of $\mu$. If $m\in M(\mu_1)$, then $\mu_2(m)\prec_m\mu_1(m)=\mu(m)\prec_m w$. At this point, if $w\in W(\mu_2)$, then $\mu_1(w)=\mu(w)\prec_w m$, so $(m,w)$ is a blocking pair of $\mu_1$, a contradiction; otherwise, $w\in W\setminus W(\mu_2)$, and we have $\mu_2(w)=\mu(w)\prec_w m$, so $(m,w)$ is a blocking pair of $\mu_2$, also a contradiction. Similarly, the case $m\in M\setminus M(\mu_1)$ also leads to a contradiction. By proof by contradiction, such a blocking pair does not exist. Therefore, $\mu_1\lor_M\mu_2$ is a stable matching. The proposition is proved.

Finally, in all stable matchings, the set of unmatched men and women is fixed.

???+ note "Theorem 4 (McVitie and Wilson, 1970)"
    Let $\mu_1$ and $\mu_2$ be two stable matchings. Then the fixed-point sets of $\mu_1$ and $\mu_2$ are the same.

??? note "Proof"
    Suppose there exists $m\in M$ such that $\mu_1(m)=m$ and $\mu_2(m)\neq m$ for some $\mu_1,\mu_2\in\mathcal S$. At this point, we have $m\in M(\mu_2)$. By the lemma, we have $m=\mu_1(m)\in W(\mu_1)$, which contradicts $m\in M$. So such $m\in M$ does not exist. Similarly, such $w\in W$ does not exist. Therefore, the fixed-point sets of any two stable matchings must be the same.

In addition to the properties discussed in this section, stable matchings also have some nice strategic properties. For these contents, please refer to the references provided at the end of the article.

## Related Problems

Stable matching and similar problems also appear in many other contexts.

### College Admissions Problem

If we relax the one-to-one matching constraint in the stable marriage problem to allow many-to-one matching, we get the **college admissions problem**. At this time, a college can admit multiple students as long as it does not exceed its quota; however, a student is still allowed to enter at most one college. Similar scenarios also appear in company recruitment, hospitals admitting resident doctors, and other situations.

For such problems, the Gale–Shapley algorithm still applies. For example, in the student-proposing Gale–Shapley algorithm, colleges can maintain a waiting list not exceeding the quota length, and whenever the number of applications exceeds the quota, they simply reject the worst student. The discussion of stable matching properties earlier still applies to this scenario. In particular, the version of Theorem 4 is that in all stable matchings, the number of students a school can admit is fixed. This is also called the **rural hospitals theorem**. This means that no matter how the matching mechanism is changed, as long as the result is stable, those rural hospitals that cannot fill their doctor positions will never be able to recruit them.

### Stable Roommates Problem

If we relax the constraint in the stable marriage problem that one can only match with members of the opposite sex, we get the **stable roommates problem**. At this time, initially there are several students who need to be paired into roommates. For such problems, stable matchings may not exist. Irving proposed an algorithm in 1985 that can solve this problem in $O(n^2)$ time.

### House Allocation Problem

In the stable marriage problem, the two groups of individuals have preferences for each other, so it is a two-sided matching problem. In addition, we can also consider one-sided matching problems. A common scenario is the **house allocation problem**. There are $n$ residents, each owning a house. Each person has a strict preference over all houses. Now, these houses need to be reallocated to these residents, requiring that each resident not be allocated a house worse than their original one, and that there is no group of residents who can privately exchange houses to get a more satisfactory outcome. This problem can be solved by the Top Trading Cycle algorithm in $O(n^2)$ time. Such problems also appear in scenarios like kidney transplants.

## Practice Problems

-   [UOJ 41. Matrix Transformation](https://uoj.ac/problem/41)
-   [Codeforces 1147 F. Zigzag Game](https://codeforces.com/problemset/problem/1147/F)

## References and Notes

-   [What is an Algorithm: How to Find a Stable Marriage Pair - Matrix67](https://matrix67.com/blog/archives/2976)
-   [Gale–Shapley Algorithm: Finding Stable Matchings in Bipartite Graphs](https://reimuyk.github.io/2021-03-24-Gale-Shapley-Algorithm/)
-   [Stable matching problem - Wikipedia](https://en.wikipedia.org/wiki/Stable_matching_problem)
-   [Lattice of stable matchings - Wikipedia](https://en.wikipedia.org/wiki/Lattice_of_stable_matchings)
-   [Stable roommates problem - Wikipedia](https://en.wikipedia.org/wiki/Stable_roommates_problem)
-   [Top trading cycle - Wikipedia](https://en.wikipedia.org/wiki/Top_trading_cycle)
-   [Stable matching: Theory, evidence, and practical design - the 2012 Nobel Prize in Economics](https://www.nobelprize.org/uploads/2018/06/popular-economicsciences2012.pdf)
-   [Notes on Matching and Market Design by Xiang Sun](https://www.xiangsun.org/wp-content/uploads/2013/02/notes-2015-matching.pdf)
-   Gale, David, and Lloyd S. Shapley. "College admissions and the stability of marriage." The American mathematical monthly 69, no. 1 (1962): 9-15.
-   Irving, Robert W. "An efficient algorithm for the stable roommates problem." Journal of Algorithms 6, no. 4 (1985): 577-595.
-   Knuth, Donald Ervin. "Marriages stables." Technical report (1976).
-   McVitie, David G., and Leslie B. Wilson. "Stable marriage assignment for unequal sets." BIT Numerical Mathematics 10, no. 3 (1970): 295-309.
-   Roth, Alvin E., and Marilda Sotomayor. "Two-sided matching." Handbook of game theory with economic applications 1 (1992): 485-541.
-   Roth, Alvin E. "Deferred acceptance algorithms: History, theory, practice, and open questions." international Journal of game Theory 36, no. 3-4 (2008): 537-569.