Please read [Max-Flow](./max-flow.md) and ensure you are proficient in max-flow algorithms before reading this article.

## Overview

Bounded network flow essentially sets an upper bound $c(u,v)$ and a lower bound $b(u,v)$ on the flow of each edge in the flow network. That is, a feasible flow must satisfy $b(u,v) \leq f(u,v) \leq c(u,v)$. Additionally, all vertices except the source and sink must satisfy flow balance.

Depending on the problem requirements, bounded network flow can be used to solve various problems.

## Feasible Flow without Source and Sink

Given a flow network $G$ without source and sink. Determine if there exists a way to assign flows to each edge such that each edge's flow satisfies the bounds and every vertex has balanced flow.

Assume each edge already has $b(u,v)$ flow, call this the initial flow. Add edges from $u$ to $v$ with capacity $c(u,v) - b(u,v)$ in the new graph. Consider adjustments on the new graph.

Since max-flow requires the initial flow balance condition (max-flow can be viewed as bounded max-flow with lower bound $0$), the constructed initial flow may not satisfy initial flow balance. Let $M$ be the initial inflow minus initial outflow for a vertex.

If $M=0$, the flow is balanced, and no additional edges are needed.

If $M>0$, the inflow is too large. Create a super source $S'$, and add an edge from $S'$ to this vertex with capacity $M$.

If $M<0$, the outflow is too large. Create a super sink $T'$, and add an edge from this vertex to $T'$ with capacity $-M$.

If all additional edges are saturated, the flow balance condition for this vertex can be satisfied; otherwise, it cannot. (Because the original flow balance is satisfied only after adding the additional flow.)

After constructing the graph, run max-flow from $S'$ to $T'$. If all edges from $S'$ are saturated, a feasible flow exists; otherwise, it does not.

## Feasible Flow with Source and Sink

Given a flow network $G$ with source and sink. Determine if there exists a way to assign flows to each edge such that each edge's flow satisfies the bounds and every vertex except the source and sink has balanced flow.

Assume the source is $S$ and the sink is $T$.

We can add an edge from $T$ to $S$ with upper bound $\infty$ and lower bound $0$ to transform this into a feasible flow without source and sink problem.

If a solution exists, the feasible flow from $S$ to $T$ equals the flow on the added edge from $T$ to $S$.

## Bounded Max-Flow with Source and Sink

Given a flow network $G$ with source and sink. Determine if there exists a way to assign flows to each edge such that each edge's flow satisfies the bounds and every vertex except the source and sink has balanced flow. If a solution exists, find the maximum feasible flow.

Find any feasible flow in the network. If no solution exists, we can stop.

Otherwise, consider the residual network after removing all additional edges and make adjustments on the network.

Run one more max-flow from $S$ to $T$ on the residual network. The sum of the feasible flow and this max-flow is the answer.

??? warning "A common mistake"
    The max-flow from $S$ to $T$ should be run directly on the residual network after finding the feasible bounded flow.
    
    Never run it on the original flow network.

## Bounded Min-Flow with Source and Sink

Given a flow network $G$ with source and sink. Determine if there exists a way to assign flows to each edge such that each edge's flow satisfies the bounds and every vertex except the source and sink has balanced flow. If a solution exists, find the minimum feasible flow.

Similarly, we consider removing excess flow from the residual network.

Find any feasible flow in the network. If no solution exists, we can stop.

Otherwise, consider the residual network after removing all additional edges.

Run one more max-flow from $T$ to $S$ on the residual network. The feasible flow minus this max-flow is the answer.

??? note "[AHOI 2014 Side Quest](https://loj.ac/problem/2226)"
    For each quest edge from $x$ to $y$ with cost $v$, set upper bound to $\infty$ and lower bound to $1$.
    
    For each vertex, add an edge to $T$ with cost $c$, upper bound $\infty$, lower bound $1$.
    
    Vertex $1$ is the source.
    
    Run one bounded min-cost feasible flow with source and sink.
    
    Since the min-cost feasible flow solution is similar to the min feasible flow, it is not elaborated here.
