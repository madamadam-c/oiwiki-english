author: jifbt, Mayuri0v0

## Definitions

For definitions of the following terms, see Graph Theory Related Concepts:

-   Edge connectivity, edge cut set;
-   Vertex connectivity, vertex cut set;
-   Clique.

## Properties

### Whitney's Inequality

**Whitney's inequality** (1932) gives the relationship between vertex connectivity $\kappa$, edge connectivity $\lambda$, and minimum degree $\delta$:

$$
\kappa \le \lambda \le \delta
$$

???+ note "Proof"
    Intuitively, if there is an edge cut set of size $\lambda$, by selecting one endpoint from each edge, we can obtain a vertex cut set of size $\lambda$, so the first inequality holds.
    
    All edges adjacent to a vertex with minimum degree (if there are multiple, choose any one) form an edge cut set of size $\delta$, so the second inequality also holds.

This inequality cannot be improved; in other words, for every triple that satisfies it, we can find a graph that satisfies this triple.

???+ note "Construction"
    Connect two cliques of size $\delta + 1$ with $\lambda$ edges, such that $\lambda$ and $\kappa$ different vertices in each clique are connected to these edges.

### Menger's Theorem

From the max-flow min-cut theorem (also known as the Ford-Fulkerson theorem), it follows that the maximum number of edge-disjoint (i.e., pairwise sharing no common edges) paths between two vertices equals the minimum size of a cut set (this corollary is also called **Menger's theorem**).

## Computation

All edge weights in the following graphs are $1$.

### Computing Edge Connectivity Using Max Flow

Enumerate vertex pairs $(s, t)$, treating $s$ as source and $t$ as sink, and run max flow with edge weight $1$. This requires $O(n^2)$ max flow runs. Using the Edmonds-Karp algorithm, the complexity is $O(|V|^3 |E|^2)$. Using the Dinic algorithm is better, with complexity $O(|V|^2 |E| \min(|V|^{2/3}, |E|^{1/2}))$.

### Global Min Cut

Using the Stoer-Wagner algorithm requires only one run of source-sink-less min cut. The complexity is $O(|V||E| + |V|^{2}\log|V|)$, which is generally considered $O(|V|^3)$.

### Vertex Connectivity

Still enumerate vertex pairs. This time, split each non-source-sink vertex $x$ into two vertices $x_1$ and $x_2$, and add an edge $(x_1, x_2)$. Replace all edges $(u, v)$ in the original graph with two edges $(u_2, v_1)$ and $(v_2, u_1)$. At this point, the max flow equals the size of the minimum vertex cut between $s$ and $t$ (also called local vertex connectivity). The complexity is the same as computing edge connectivity using max flow.

**This page is translated from the blog posts Рёберная связность. Свойства и нахождение, Вершинная связность. Свойства и нахождение and their English translations Edge connectivity/Vertex connectivity. The Russian version is in Public Domain + Leave a Link; the English version is under CC-BY-SA 4.0.**

## Further Reading

-   The paper *Connectivity Algorithms* introduces recent advances in connectivity computation algorithms. Interested readers may browse it on their own.