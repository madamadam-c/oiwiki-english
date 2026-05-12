## Definitions

A path that passes through each vertex in a graph exactly once is called a Hamiltonian path.

A cycle that passes through each vertex in a graph exactly once is called a Hamiltonian cycle.

A graph that contains a Hamiltonian cycle is called a Hamiltonian graph.

A graph that has a Hamiltonian path but does not have a Hamiltonian cycle is called a semi-Hamiltonian graph.

## Properties

Let $G=\langle V, E\rangle$ be a Hamiltonian graph. Then for any nonempty proper subset $V_1$ of $V$, we have $p(G-V_1) \leq |V_1|$. Here $p(x)$ denotes the number of connected components of $x$.

Corollary: Let $G=\langle V, E\rangle$ be a semi-Hamiltonian graph. Then for any nonempty proper subset $V_1$ of $V$, we have $p(G-V_1) \leq |V_1| + 1$. Here $p(x)$ denotes the number of connected components of $x$.

The complete graph $K_{2k+1} (k \geq 1)$ contains $k$ edge-disjoint Hamiltonian cycles, and these $k$ edge-disjoint Hamiltonian cycles contain all edges of $K_{2k+1}$.

The complete graph $K_{2k} (k \geq 2)$ contains $k-1$ edge-disjoint Hamiltonian cycles. After removing these $k-1$ edge-disjoint Hamiltonian cycles from $K_{2k}$, the resulting graph contains $k$ pairwise non-adjacent edges.

## Sufficient Conditions

Let $G$ be an undirected simple graph of order $n(n \geq 2)$. If for any two nonadjacent vertices $v_i, v_j$ in $G$, we have $d(v_i) + d(v_j) \geq n - 1$, then $G$ contains a Hamiltonian path.

Corollary 1: Let $G$ be an undirected simple graph of order $n(n \geq 3)$. If for any two nonadjacent vertices $v_i, v_j$ in $G$, we have $d(v_i) + d(v_j) \geq n$, then $G$ contains a Hamiltonian cycle, and thus $G$ is a Hamiltonian graph.

Corollary 2: Let $G$ be an undirected simple graph of order $n(n \geq 3)$. If for any vertex $v_i$, we have $d(v_i) \geq \frac{n}{2}$, then $G$ contains a Hamiltonian cycle, and thus $G$ is a Hamiltonian graph.

Let $D$ be a tournament of order $n(n \geq 2)$. Then $D$ has a Hamiltonian path.

If $D$ contains a tournament of order $n(n \geq 2)$ as a subgraph, then $D$ has a Hamiltonian path.

A strongly connected tournament is a Hamiltonian graph.

If $D$ contains a strongly connected tournament of order $n(n \geq 2)$ as a subgraph, then $D$ has a Hamiltonian cycle.