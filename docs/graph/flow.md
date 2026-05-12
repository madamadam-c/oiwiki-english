This page introduces basic knowledge related to network flow.

## Overview

A network is a special directed graph $G=(V,E)$, which differs from ordinary directed graphs in that it has capacities and source-sink pairs.

-   Each edge $(u, v)$ in $E$ has a weight called capacity, denoted as $c(u, v)$. When $(u,v) \notin E$, we can assume $c(u,v)=0$.

-   There are two special vertices in $V$: the source $s$ and the sink $t$ ($s \neq t$).

For a network $G=(V, E)$, a flow is a function from the edge set $E$ to the set of integers or real numbers that satisfies the following properties.

1.  Capacity constraint: For each edge, the flow through that edge must not exceed its capacity, i.e., $0 \leq f(u,v) \leq c(u,v)$;
2.  Flow conservation: Except for the source and sink, the net flow of any vertex $u$ is $0$. Here, we define the net flow of $u$ as $f(u) = \sum_{x \in V} f(u, x) - \sum_{x \in V} f(x, u)$.

For a network $G = (V, E)$ and a flow $f$ on it, we define the value of flow $f$ as the net flow at $s$, denoted as $|f|$. As a consequence of flow conservation, this also equals the negative of the net flow at $t$, i.e., $-f(t)$.

For a network $G = (V, E)$, if $\{S, T\}$ is a partition of $V$ (i.e., $S \cup T = V$ and $S \cap T = \varnothing$) and satisfies $s \in S, t \in T$, then we call $\{S, T\}$ an $s$-$t$ cut of $G$. We define the capacity of the $s$-$t$ cut $\{S, T\}$ as $||S, T|| = \sum_{u \in S} \sum_{v \in T} c(u, v)$.

## Common Problems

Common network flow problems include, but are not limited to, the following types.

-   Max flow problem: For a network $G = (V, E)$, assign flows to each edge to obtain a suitable flow $f$ such that the value of $f$ is as large as possible. In this case, we call $f$ a maximum flow of $G$.
-   Min cut problem: For a network $G = (V, E)$, find a suitable $s$-$t$ cut $\{S, T\}$ such that the total capacity of $\{S, T\}$ is as small as possible. In this case, we call the total capacity of $\{S, T\}$ a minimum cut of $G$.
-   Min cost max flow problem: On a network $G = (V, E)$, assign a weight $w(u, v)$ to each edge, called the cost, which represents the cost per unit of flow passing through $(u, v)$. Among all possible maximum flows of $G$, the one with the minimum total cost is called the minimum cost maximum flow.

We will provide detailed introductions to them in later sections.

## Example: Network Flow 24 Problems

The Network Flow 24 Problems is a widely circulated problem set on the Chinese internet (LibreOJ/Lojtag/Luogu), which has existed at least since around 2010. This problem set introduces some classic techniques for modeling other problems as network flow problems. Due to the limitations of the era, these problems may not be the most representative network flow problems, but they are still worth reading for readers aspiring to compete in algorithm contests.