author: DanJoshua, opsiff, yzy-1, yingqi-z20

## Definitions

Since the definitions of **source and sink** are removed, we need to redefine the concept of a **cut**.

(In fact, the definition of a cut in the network flow section differs from the Wikipedia definition, but since the commonly encountered cuts are "minimum s-t cut problems", this convention has become standard.)

### Cut

A set of edges whose removal disconnects a flow network (i.e., splits it into two subgraphs) is called a cut of the graph.

That is: In an undirected graph $G = (V, E)$, let $C$ be a set of edges. If removing all edges in $C$ makes graph $G$ disconnected, then $C$ is called a cut of $G$.

### Minimum s-t Cut Problem

Same as defined in [Minimum Cut](./flow/min-cut.md).

### Global Minimum Cut Problem

The cut with minimum total weight of edges. Also called the global minimum cut.

Clearly, directly running network flow is not feasible.

***

## Stoer–Wagner Algorithm

### Introduction

The Stoer–Wagner algorithm was proposed by *Mechthild Stoer* and *Frank Wagner* in 1995. It is an algorithm that solves the **global minimum cut problem** on **undirected positive-weight graphs** using a **recursive** approach.

### Properties

The time complexity is $O(|V||E| + |V|^{2}\log|V|)$, which is generally approximated as $O(|V|^3)$.

Its implementation is based on the following fundamental fact: Let $S, T$ be any two vertices in graph $G$. Then for any cut $C$ of $G$, either $S$ and $T$ are in the same connected component, or $C$ is an $S$-$T$ cut.

### Process

1.  Arbitrarily specify two vertices $s, t$ in graph $G$, and compute the $S$-$T$ minimum cut of $G$ with these two as source and sink (called the *cut of phase*), updating the current answer.
2.  "Merge" vertices $s$ and $t$. If $|V| > 1$ in graph $G$, return to step 1.
3.  Output the minimum value among all *cut of phase* results.

Merging vertices $s$ and $t$: Delete the edge $(s, t)$ between $s$ and $t$. For any vertex $k$ in $G \setminus \{s, t\}$, delete $(t, k)$ and add its weight $d(t, k)$ to $d(s, k)$.

Explanation: If $s$ and $t$ are in the same connected component, for a vertex $k$ in $G \setminus \{s, t\}$, if $(k, s) \in C_{\min}$, then $(k, t) \in C_{\min}$ must also hold; otherwise, since $s$ and $t$ are connected, $k$ and $t$ are connected, causing $s$ and $k$ to be in the same connected component, and $C = C_{\min} \setminus \{(t, k)\}$ would be better than $C_{\min}$. The reverse also holds. Therefore, $s$ and $t$ can be treated as the same vertex.

Step 1 considers the case where $s$ and $t$ are not in the same connected component, and step 2 considers the remaining case. Since each execution of step 2 reduces $|V|$ by $1$, the algorithm terminates after $|V| - 1$ iterations.

### Computing the S-T Minimum Cut

(Clearly, not using network flow.)

Assume after several merges, the current graph is $G'=(V', E')$, and we execute step 1.

We construct a set $A$, initially with $A = \varnothing$.

We repeatedly add to set $A$ the vertex that is not in $A$ and has the maximum weight function $w(A, i)$ until $|A| = |V'|$.

The weight function is defined as:

$w(A, i) = \sum_{j \in A} d(i, j)$

(If $(i, j) \notin E'$, then $d(i, j) = 0$.)

It's easy to see that the order in which all vertices are added to $A$ is fixed. Let $\operatorname{ord}(i)$ denote the vertex added to $A$ at position $i$, and $t = \operatorname{ord}(|V'|)$. Let $\operatorname{pos}(v)$ denote the value of $|A|$ when $v$ is added to $A$, i.e., the position at which $v$ is added.

Then for any vertex $s$, a cut from $s$ to $t$ has weight $w(t)$.

### Proof

Define a vertex $v$ as *activated* if and only when $v$ is added to $A$, it is discovered that the last vertex $u$ added to $A$ before $v$ is in a different connected component from $v$ in graph $G'' = (V', E'/C)$.

![Stoer-Wagner1](./images/Stoer-Wagner1.png)

As shown in the figure, the blue and yellow regions are two different connected components, the numbers in brackets are the order of addition to $A$. Gray nodes are activated nodes, white nodes are not activated.

Define $A_v = \{u \mid \operatorname{pos}(u) < \operatorname{pos}(v)\}$, i.e., vertices that strictly preceded $v$ in being added to $A$. Let $E_v$ be the edge set of the induced subgraph of $E'$ on vertex set $A_v \cup\{v\}$. (Note that it includes vertex $v$.)

Define the induced cut $C_v$ as $C \cap E_v$. $w(C_v) = \sum_{(i,j) \in C_v} d(i, j)$.

???+ note "Lemma 1"
    For any activated vertex $v$, $w(A_v, v) \le w(C_v)$.
    
    Proof: By mathematical induction.
    
    For the first activated vertex $v_0$, by definition we have $w(A_{v_0}, v_0) = w(C_{v_0})$.
    
    For two subsequent activated vertices $u, v$, assume $\operatorname{pos}(v) < \operatorname{pos}(u)$. Then:
    
    $w(A_u, u) = w(A_v, u) + w(A_u - A_v, u)$
    
    Also, given:
    
    $w(A_v, u) \le w(A_v, v)$ and $w(A_v, v) \le w(C_v)$, combining gives:
    
    $w(A_u, u) \le w(C_v) + w(A_u - A_v, u)$
    
    Since $w(A_u - A_v, u)$ contributes to $w(C_u)$ but not to $w(C_v)$, with all edge weights being positive, we can derive:
    
    $w(A_u,u) \le w(C_u)$
    
    By induction, this is proven.

Since $\operatorname{pos}(s) < \operatorname{pos}(t)$ and $s, t$ are not in the same connected component, $t$ will be activated. Therefore, $w(A_t, t) \le w(C_t) = w(C)$.

??? note "[P5632 Stoer–Wagner Algorithm (Template)](https://www.luogu.com.cn/problem/P5632)"
    ```cpp
    --8<-- "docs/graph/code/stoer-wagner/stoer-wagner_1.cpp"
    ```

***

### Complexity Analysis and Optimization

The *contract* operation has complexity $O(|E| + |V|\log|V|)$.

A total of $O(|V|)$ *contract* operations are performed, giving total complexity $O(|E||V| + |V|^2\log|V|)$.

Based on the experience from [Shortest Path](./shortest-path.md), the bottleneck is finding the vertex with maximum weight.

In one *contract* operation, we need to find the heap top $|V|$ times and incrementally modify $|E|$ edge weights.

A Fibonacci heap can handle finding the heap top in $O(\log|V|)$ and incremental weight modification in $O(1)$, achieving theoretical complexity $O(|E| + |V|\log|V|)$. However, due to the large constant factor and high code complexity of Fibonacci heaps, its practical value is limited.

(In actual tests, O2 optimization is needed and benchmark fluctuations must be considered to pass.)