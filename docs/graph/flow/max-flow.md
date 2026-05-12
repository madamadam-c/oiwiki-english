This page mainly introduces algorithm knowledge related to the maximum flow problem.

## Overview

For basic concepts of network flow, see [Introduction to Network Flow](../flow.md).

Let $G=(V,E)$ be a network with a source and sink. We want to specify a suitable flow $f$ on $G$ to maximize the total flow of the network $|f|$ (i.e., $\sum_{x \in V} f(s, x) - \sum_{x \in V} f(x, s)$). This problem is called the Maximum flow problem.

## Ford–Fulkerson Augmentation

Ford–Fulkerson augmentation is a general term for a class of algorithms for computing maximum flow. This method uses a greedy approach, solving the maximum flow by finding augmenting paths to update.

### Overview

Given a network $G$ and a flow $f$ on $G$, we make the following definitions.

For an edge $(u, v)$, we call the difference between its capacity and flow the residual capacity $c_f(u,v)$ (Residual Capacity), i.e., $c_f(u,v)=c(u,v)-f(u,v)$.

We call the subgraph consisting of all nodes in $G$ and edges with residual capacity greater than 0 the residual network $G_f$ (Residual Network), i.e., $G_f=(V,E_f)$, where $E_f=\left\{(u,v) \mid c_f(u,v)>0\right\}$.

???+ warning "Warning"
    As we will soon mention, the flow can be negative, so edges in $E_f$ may not be in $E$. After introducing the concept of augmentation, we will explain this in detail below.

We call a path from source $s$ to sink $t$ in $G_f$ an augmenting path (Augmenting Path). For an augmenting path, we add equal amount of flow to each edge $(u, v)$ to increase the total flow of the network. This process is called augmenting (Augment). Thus, solving the maximum flow can be viewed as the superposition of flows obtained from several augmentations.

Additionally, during Ford–Fulkerson augmentation, for each edge $(u, v)$, we create a reverse edge $(v, u)$. We define $f(u, v) = -f(v, u)$, and this property can be ensured by introducing backflow operation during each augmentation, i.e., when $f(u, v)$ increases, $f(v, u)$ should decrease by the same amount.

???+ tip "Tip"
    In code implementation of maximum flow algorithms, we often need to support fast access to reverse edges. In an adjacency matrix, this operation is trivial ($g_{u, v} \leftrightarrow g_{v, u}$). However, the more common implementation uses chain forward star. A common technique is to number edges starting from even numbers (usually 0) and always add the reverse edge immediately after adding an edge so that their indices are adjacent. This way, we can ensure that the edge with index $i$ and the edge with index $i \oplus 1$ are always reverse edges of each other.

Readers encountering this method for the first time may notice a counter-intuitive situation—the flow on the reverse edge $f(v, u)$ may be negative. Actually, we can note that in the Ford–Fulkerson augmentation process, what truly matters is the residual capacity $c_f$, and the absolute value of $f(v, u)$ is irrelevant. We can view the decrease in reverse edge flow as an increase in the reverse edge's residual capacity $c_f(v, u)$—which also aligns with the meaning of backflow. The increase in reverse edge's residual capacity means we may later use the reverse edge to cancel the original forward augmentation, representing a "regret" operation.

The following case may help you understand this process. Suppose $G$ is a unit capacity network. Consider the following process:

-   There are multiple augmenting paths on $G$. We choose to perform an augmentation that first passes through $u, v$ (as shown in the left figure), increasing the flow by 1.
-   We notice that if we perform the augmentation shown in the middle figure, the maximum local flow is not 1 but 2. However, since the edge pointing to $u$ and the edge starting from $v$ were exhausted in the first augmentation, we cannot perform the middle figure's augmentation. This means our current flow is not optimal, but locally there may be no other augmenting paths (only passing through original edges without reverse edges).
-   Now we introduce backflow. After the first augmentation, backflow means $c_f(v, u)$ increased by 1 residual capacity, which is equivalent to adding edge $(v, u)$. Therefore, we can perform another augmentation passing through $p, v, u, q$ (as shown by the orange path in the right figure). The flow on undirected edge $(u, v)$ cancels out in the two augmentations. Surprisingly, we find that the result of superposing the two augmentations is actually equivalent to the middle figure.

![](./images/flow2.png)

This case tells us that the "cancelling" effect brought by backflow means we don't need to worry about selecting augmenting paths in the "wrong" order.

It is easy to see that as long as there exists an augmenting path on $G_f$, augmenting it can increase the total flow; otherwise, the total flow has reached its maximum possible value, and the solving process is complete. This is the Ford–Fulkerson augmentation process.

### Max-flow Min-cut Theorem

We have roughly understood the idea of Ford–Fulkerson augmentation, but how do we prove the correctness of this method? Why is the flow $f$ after augmentation a maximum flow?

In fact, the correctness of Ford–Fulkerson augmentation is equivalent to the Max-flow Mincut Theorem. This theorem states that for any network $G = (V, E)$, the maximum flow $f$ and minimum cut $\{S, T\}$ always satisfy $|f| = ||S, T||$.

To prove the max-flow min-cut theorem, we start from a lemma: For a network $G = (V, E)$, for any flow $f$ and cut $\{S, T\}$, we always have $|f| \leq ||S, T||$, where equality holds if and only if all edges in $\{(u, v) | u \in S, v \in T\}$ are saturated and all edges in $\{(u, v) | u \in T, v \in S\}$ have zero flow.

???+ note "Proof"
    $$
    \begin{aligned}
    |f| & = f(s) \\
        & = \sum_{u \in S} f(u) \\
        & = \sum_{u \in S} \left( \sum_{v \in V} f(u, v) - \sum_{v \in V} f(v, u) \right) \\
        & = \sum_{u \in S} \left( \sum_{v \in T} f(u, v) + \sum_{v \in S} f(u, v) - \sum_{v \in T} f(v, u) - \sum_{v \in S} f(v, u) \right) \\
        & = \sum_{u \in S} \left( \sum_{v \in T} f(u, v) - \sum_{v \in T} f(v, u) \right) + \sum_{u \in S} \sum_{v \in S} f(u, v) - \sum_{u \in S} \sum_{v \in S} f(v, u) \\
        & = \sum_{u \in S} \left( \sum_{v \in T} f(u, v) - \sum_{v \in T} f(v, u) \right) \\
        & \leq \sum_{u \in S} \sum_{v \in T} f(u, v) \\
        & \leq \sum_{u \in S} \sum_{v \in T} c(u, v) \\
        & = ||S, T|| \\
    \end{aligned}
    $$
    
    To achieve equality, the first inequality requires all edges in $\{(u, v) \mid u \in T, v \in S\}$ to have zero flow, and the second inequality requires all edges in $\{(u, v) \mid u \in S, v \in T\}$ to be saturated. The lemma is proven.

Now, for any network, can the equality condition always be satisfied? If the answer is yes, then the max-flow min-cut theorem is proven. Let us attempt to prove this.

???+ note "Proof"
    After one round of augmentation, we obtain a flow $f$ such that there is no augmenting path on $G_f$, i.e., there is no path from $s$ to $t$ on $G_f$. At this point, let $S$ be the set of nodes reachable from $s$, and let $T = V \setminus S$.
    
    Obviously, $\{S, T\}$ is a cut of $G_f$, and $||S, T|| = \sum_{u \in S} \sum_{v \in T} c_f(u, v) = 0$. Since residual capacity is non-negative, this also means for any $u \in S, v \in T, (u, v) \in E_f$, we have $c_f(u, v) = 0$. Below we discuss these edges in two cases: edges existing in the original graph and reverse edges:
    
    -   $(u, v) \in E$: At this time, $c_f(u, v) = c(u, v) - f(u, v) = 0$, so we have $c(u, v) = f(u, v)$, i.e., all edges in $\{(u, v) \mid u \in S, v \in T\}$ are saturated;
    -   $(v, u) \in E$: At this time, $c_f(u, v) = c(u, v) - f(u, v) = 0 - f(u, v) = f(v, u) = 0$, i.e., all edges in $\{(v, u) \mid u \in S, v \in T\}$ have zero flow.
    
    Therefore, after augmentation stops, the flow $f$ satisfies the equality condition. According to the size relationship indicated by the lemma, naturally, $f$ is a maximum flow of $G$, and $\{S, T\}$ is a minimum cut of $G$.

It is easy to see that König's theorem is a special case of the max-flow min-cut theorem. In fact, both are related to duality in linear programming.

### Time Complexity Analysis

On a network $G = (V, E)$ with integer flows, trivially assuming each augmentation adds integer flow, an upper bound on the time complexity of Ford–Fulkerson augmentation is $O(|E||f|)$, where $f$ is the maximum flow on $G$. This is because the time complexity of a single round of augmentation is $O(|E|)$, and augmentation increases the total flow, so the number of augmentation rounds cannot exceed $|f|$.

Different implementations of Ford–Fulkerson augmentation have different time complexities. Among the more mainstream implementations are Edmonds–Karp, Dinic, SAP, ISAP, etc., which we will introduce below.

### Edmonds–Karp Algorithm

#### Algorithm Idea

How do we find an augmenting path in $G_f$? When considering the specific implementation of Ford–Fulkerson augmentation, the most natural approach is to use BFS. At this time, Ford–Fulkerson augmentation manifests as the Edmonds–Karp algorithm. The specific process is as follows:

-   If we can BFS from $s$ to $t$ on $G_f$, then we have found a new augmenting path.

-   For an augmenting path $p$, we compute the minimum residual capacity of the edges that $p$ passes through: $\Delta = \min_{(u, v) \in p} c_f(u, v)$. We add $\Delta$ flow to each edge on $p$, and remove $\Delta$ flow from their reverse edges, increasing the maximum flow by $\Delta$.

-   Since we have modified the flow, we obtain a new $G_f$. We repeat the above process on the new $G_f$ until there is no augmenting path, at which point the flow no longer increases.

This algorithm is the Edmonds–Karp algorithm.

#### Time Complexity Analysis

Now let us analyze the time complexity of the Edmonds–Karp algorithm.

Obviously, the time complexity of a single round of BFS augmentation is $O(|E|)$.

The upper bound on the total number of augmentations is $O(|V||E|)$. This claim is often falsely proven (or vaguely skipped over) in online resources. Below we attempt to give a more formal proof[^ref_ek].

???+ note "Proof of the upper bound on the total number of augmentations"
    First, we introduce a lemma—the shortest-path non-decreasing lemma. Specifically, let $d_f(u)$ be the distance from node $u$ to the source $s$ on $G_f$ (i.e., the shortest path length, same below). For one round of augmentation, let $f$ and $f'$ denote the flow before and after augmentation respectively. We assert that for any node $u$, augmentation always makes $d_{f'}(u) \geq d_f(u)$. We will prove this lemma shortly.
    
    Let us call the edge on the augmenting path with the minimum residual capacity a saturated edge (if multiple edges have the same minimum, pick any). If a directed edge $(u, v)$ is selected as a saturated edge, augmentation will empty its residual capacity, causing the saturated edge to disappear, and backflow creates a new reverse edge (if the reverse edge did not originally exist), i.e., $(u, v) \not \in E_{f'}$ and $(v, u) \in E_{f'}$. The above analysis tells us that for an undirected edge $(u, v)$, the two directions of augmentation always appear alternately.
    
    When augmenting along $(u, v)$ on $G_f$, $d_f(u) + 1 = d_f(v)$, after which the residual network becomes $G_{f'}$. When augmenting along $(v, u)$ on $G_{f'}$, $d_{f'}(v) + 1 = d_{f'}(u)$. From the shortest-path non-decreasing lemma we also have $d_{f'}(v) \geq d_f(v)$. Connecting all equations, we get $d_{f'}(u) \geq d_{f}(u) + 2$. In other words, if a directed edge $(u, v)$ is selected as a saturated edge, then compared to the last time it was selected as a saturated edge, the distance from $u$ to $s$ increases by at least 2.
    
    The distance from $s$ to any node cannot exceed $|V|$. Combined with the above property, we find that each edge can be selected as a saturated edge $O(|V|)$ times. Multiplying by the number of edges gives the upper bound on the total number of augmentations as $O(|V||E|)$.
    
    Next, we prove the shortest-path non-decreasing lemma, i.e., $d_{f'}(u) \geq d_f(u)$. This proof is not difficult, but may be slightly convoluted. Readers may pause and think carefully.
    
    ???+ note "Proof of the shortest-path non-decreasing lemma"
        Consider proof by contradiction. For one round of augmentation, suppose there are some nodes whose distance to $s$ decreased after this round of augmentation. Let $v$ be the one with the smallest distance to $s$ among them (i.e., $v = \arg \min_{x \in V, d_{f'}(x) < d_f(x)} d_{f'}(x)$). Note that according to the contradiction assumption, $d_{f'}(v) < d_f(v)$ is a known condition.
        
        On the shortest path from $s$ to $v$ in $G_{f'}$, let $u$ be the previous node of $v$, i.e., $d_{f'}(u) + 1 = d_{f'}(v)$.
        
        To not let $u$ destroy the "minimum distance" property of $v$, $u$ must satisfy $d_{f'}(u) \geq d_f(u)$.
        
        For the above equation, adding the same value to both sides gives $d_{f'}(v) \geq d_f(u) + 1$. Using the contradiction assumption for scaling, we get $d_f(v) > d_f(u) + 1$.
        
        Below we attempt to discuss the augmentation direction on $(u, v)$.
        
        -   Suppose directed edge $(u, v) \in E_f$. According to the "breadth-first" property of BFS, we have $d_f(u) + 1 \geq d_f(v)$. This equation conflicts with the scaling result, leading to a contradiction.
        -   Suppose directed edge $(u, v) \not \in E_f$. According to the definition of $u$, we already know $(u, v) \in E_{f'}$, so the existence of this edge must be the result of the current round of augmentation passing through $(v, u)$ and creating a reverse edge through backflow, i.e., $d_f(v) + 1 = d_f(u)$. This equation conflicts with the scaling result, leading to a contradiction.
        
        Since augmenting $(u, v)$ in any direction leads to a contradiction, we know the contradiction assumption is invalid, and the shortest-path non-decreasing lemma is proven.

Multiplying the complexity of a single round of BFS augmentation by the upper bound on the number of augmentations, we get that the time complexity of the Edmonds–Karp algorithm is $O(|V||E|^2)$.

#### Code Implementation

A possible implementation of the Edmonds–Karp algorithm is as follows.

??? note "Reference Code"
    ```cpp
    constexpr int MAXN = 250;
    constexpr int INF = 0x3f3f3f3f;
    
    struct Edge {
      int from, to, cap, flow;
    
      Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
    };
    
    struct EK {
      int n, m;             // n: number of vertices, m: number of edges
      vector<Edge> edges;   // edges: collection of all edges
      vector<int> G[MAXN];  // G[x]: indices in edges of all edges from x
      int a[MAXN], p[MAXN];  // a[x]: maximum flow sent to x by the edge that most recently reached x in BFS
                             // p[x]: edge that most recently reached x in BFS
    
      void init(int n) {
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
      }
    
      void AddEdge(int from, int to, int cap) {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
      }
    
      int Maxflow(int s, int t) {
        int flow = 0;
        for (;;) {
          memset(a, 0, sizeof(a));
          queue<int> Q;
          Q.push(s);
          a[s] = INF;
          while (!Q.empty()) {
            int x = Q.front();
            Q.pop();
            for (int i = 0; i < G[x].size(); i++) {  // Iterate over edges starting from x
              Edge& e = edges[G[x][i]];
              if (!a[e.to] && e.cap > e.flow) {
                p[e.to] = G[x][i];  // G[x][i] is the edge that most recently reached e.to
                a[e.to] =
                    min(a[x], e.cap - e.flow);  // Flow assigned by the edge that most recently reached e.to
                Q.push(e.to);
              }
            }
            if (a[t]) break;  // If the sink has received flow, exit BFS
          }
          if (!a[t])
            break;  // If the sink received no flow, the source and sink are not in the same connected component
          for (int u = t; u != s;
               u = edges[p[u]].from) {  // Trace the s -> t path found by BFS through u
            edges[p[u]].flow += a[t];      // Increase the flow on path edges
            edges[p[u] ^ 1].flow -= a[t];  // Decrease the flow on reverse path edges
          }
          flow += a[t];
        }
        return flow;
      }
    };
    ```

### Dinic Algorithm

#### Algorithm Idea

Consider performing BFS layering on $G_f$ before augmentation, i.e., dividing nodes into several layers according to the distance $d(u)$ from node $u$ to the source $s$. Flow passing through $u$ can only flow to nodes $v$ in the next layer, i.e., delete edges from $u$ to nodes with equal or smaller layer numbers. We call the remaining part of $G_f$ the level graph (Level Graph). Formally, we call $G_L = (V, E_L)$ the level graph of $G_f = (V, E_f)$, where $E_L = \left\{ (u, v) \mid (u, v) \in E_f, d(u) + 1 = d(v) \right\}$.

If we find a maximal augmenting flow $f_b$ on the level graph $G_L$ such that it is impossible to further increase $f_b$ on $G_L$ alone, then we call $f_b$ a blocking flow (Blocking Flow) of $G_L$.

??? warning "Warning"
    Although in the previous text we defined augmentation/augmenting flow only on a single augmenting path, in a broader sense, the term "augmentation" can refer not only to augmenting flow on a single path but also to the union of several augmenting flows—the latter is the meaning used when defining blocking flow.

After defining the level graph and blocking flow, the Dinic algorithm proceeds as follows:

1.  BFS on $G_f$ to construct the level graph $G_L$.
2.  DFS on $G_L$ to find a blocking flow $f_b$.
3.  Merge $f_b$ into the original flow $f$, i.e., $f \leftarrow f + f_b$.
4.  Repeat the above process until there is no path from $s$ to $t$.

At this point, $f$ is the maximum flow.

Before analyzing the complexity of this algorithm, we need to specifically explain the process of "DFS to find a blocking flow $f_b$ on $G_L$". Although BFS for the level graph should be trivial for readers of this page, the DFS for blocking flow requires some technique—we need to introduce current arc optimization.

Note that during DFS on $G_L$, if node $u$ has both a large number of incoming and outgoing edges, and $u$ traverses the outgoing edge table each time it receives flow from incoming edges to decide which outgoing edge to pass the flow to, then the time complexity of this local part of $u$ can be as high as $O(|E|^2)$ in the worst case. To avoid this flaw, if at some point we already know that edge $(u, v)$ has been augmented to its limit (edge $(u, v)$ has no remaining capacity or the side beyond $v$ has been augmented to blockage), then there is no need for $u$'s flow to try to flow to outgoing edge $(u, v)$ again. Accordingly, for each node $u$, we maintain the first outgoing edge in $u$'s outgoing edge table that still needs to be tried. Conventionally, we call this maintained pointer the current arc, and call this practice current arc optimization.

??? note "Multi-path Augmentation"
    Multi-path augmentation is a constant optimization of the Dinic algorithm—if we find an augmenting path $p$ from $s$ to $t$ on the level graph, then next we may not need to start from $s$ again to find the next augmenting path, but instead start from the last position on $p$ that still has remaining capacity to find a branch for augmentation. Considering its consistency with the backtracking form, this optimization is also natural in the DFS code implementation.
    
    ??? failure "Common Misconception"
        Perhaps due to erroneous statements in many online resources causing a chain of misinformation, a considerable number of contestants like to list current arc optimization and multi-path augmentation as two optimizations of the Dinic algorithm. In fact, current arc optimization is part of ensuring the correctness of Dinic's time complexity, while multi-path augmentation is merely a constant optimization that does not affect the complexity.

#### Time Complexity Analysis

With current arc optimization applied, the time complexity analysis of the Dinic algorithm is as follows.

First, we attempt to prove that the time complexity of finding a blocking flow via DFS in a single round of augmentation is $O(|V||E|)$.

???+ note "Proof of the time complexity of a single round of augmentation"
    Consider each augmenting path in the blocking flow $f_b$. They are all obtained by jumping along current arcs on $G_L$, where each augmenting path experiences at most $|V|$ jumps.
    
    For each augmenting path found, one saturated edge disappears (residual capacity becomes zero). Consider each augmenting path in the blocking flow $f_b$. Let $E_1$ be the set of saturated edges that become zero due to them. Considering the layered nature of $G_L$, after a saturated edge disappears, its reverse edge cannot be traversed by other augmenting paths in the same round of augmentation. Therefore, $E_1$ is a subset of $E_L$.
    
    Additionally, for cases where we jump along current arcs but fail to obtain an augmenting path due to blockage at some position, let $E_2$ be the set of last edges on these incomplete paths. Members of $E_2$ are not saturated, so $E_1$ and $E_2$ are disjoint, and $E_1 \cup E_2$ is still a subset of $E_L$.
    
    Since each member of $E_1 \cup E_2$ costs at most $|V|$ jumps (and with multi-path augmentation optimization, some jumps are counted multiple times), therefore, in summary, the total number of jumps in the DFS process cannot exceed $|V||E_L|$.
    
    ??? failure "A Common False Proof"
        For each node, we maintain the next edge that can be augmented, and the current arc can change at most $|E|$ times, so the worst-case time complexity of a single round of augmentation is $O(|V||E|)$.
    
    ??? bug "Bug"
        "The current arc changes at most $|E|$ times" cannot lead to "each node visits its outgoing edges at most $|E|$ times". This is because visiting the current arc does not necessarily exhaust its remaining capacity; node $u$ may visit the same current arc multiple times.

Note that the number of layers in the level graph obviously cannot exceed $|V$. If we can prove that the number of layers in the level graph strictly increases during augmentation, then the number of augmentation rounds in the Dinic algorithm is $O(|V|)$. Let us attempt to prove this conclusion[^ref_dinic].

???+ note "Proof of the monotonicity of the level graph layer count"
    We need to introduce a concept from preflow-push algorithms (another class of maximum flow algorithms)—height labels. To make it more convenient to combine with height labels in our proof, during the proof, we let $d_f(u)$ be the distance from node $u$ to the **sink** $t$ on $G_f$, and perform layering from the **sink** rather than from the source (this makes no essential difference). For one round of augmentation, let $f$ and $f'$ denote the flow before and after augmentation respectively. After solving and adding the blocking flow in this round, let the level graph change from $G_L = (V, E_L)$ to $G'_{L} = (V, E'_L)$.
    
    We give a non-strict temporary definition of height labels—on a network $G = (V, E)$, let $h$ be a function from the vertex set $V$ to the integer set $\mathbb{N}$. $h$ is a valid height label on $G$ if and only if $h(u) \leq h(v) + 1$ holds for all $(u, v) \in E$.
    
    Examining all members $(u, v)$ of $E_{f'}$, we find that $(u, v) \in E_{f'}$ is due to one of the following two reasons:
    
    -   $(u, v) \in E_f$, and the residual capacity was not exhausted during this round of augmentation—according to the definition of shortest path, at this time we have $d_f(u) \leq d_f(v) + 1$;
    -   $(u, v) \not \in E_f$, but during this round of augmentation, the blocking flow passed through $(v, u)$ and produced a reverse edge through backflow—according to the definitions of level graph and blocking flow, at this time we have $d_f(u) + 1 = d_f(v)$.
    
    This observation leads us to a conclusion—$d_f$ is a valid height label on $G_{f'}$. Of course, it is also on the subgraph $G'_L$ of $G_{f'}$.
    
    Now, for an augmenting path $p = (s, \dots, u, v, \dots, t)$ on $G'_L$, consider the process of starting from an empty path and adding one node at a time in reverse order of nodes on $p$ (the order from $t$ to $s$). Suppose node $v$ has been added, and node $u$ is being added. We find that after adding node $u$, according to the definition of the level graph, the value of $d_{f'}(u)$ increases by 1 compared to $d_{f'}(v)$. Meanwhile, since $d_f$ is a height label on $G'_L$, the value of $d_f(u)$ may either increase by 1 compared to $d_f(v)$, or remain the same or decrease. Therefore, after the entire path is added, we obtain $d_{f'}(s) \geq d_f(s)$, where equality holds if and only if $d_f(u) = d_f(v) + 1$ holds for all $(u, v) \in p$. If this inequality cannot be equal, then $d_{f'}(s) > d_f(s)$—that is, the conclusion we want: "the number of layers in the level graph strictly increases during augmentation". Let us attempt to prove that this inequality cannot be equal.
    
    Consider proof by contradiction. Assume $d_{f'}(s) = d_f(s)$ holds, and try to derive a contradiction. Now we assert that on $G'_L$, $p$ contains at least one edge $(u, v)$ such that $(u, v)$ does not exist on $G_L$. If there were no such edge, considering $d_f(s) = d_{f'}(s)$, combined with the definitions of level graph and blocking flow, the augmentation on $G_L$ should not be complete. To avoid this contradiction, our assertion must be correct.
    
    Let $(u, v)$ be the edge satisfying the assertion. The reason it satisfies the assertion can only be one of the following two:
    
    -   $(u, v) \in E_f$ but $d_f(u) \leq d_f(v) + 1$ did not achieve equality, so according to the definition of level graph, $(u, v) \not \in E_L$, and it is added to $E'_L$ in the new layering after augmentation;
    -   $(u, v) \not \in E_f$, which means the edge $(u, v)$ was created as a result of the blocking flow passing through $(v, u)$ and producing a reverse edge through backflow in the current round of augmentation, i.e., $d_f(u) = d_f(v) - 1$.
    
    Since no matter how we satisfy the assertion, we get $d_f(u) \neq d_f(v) + 1$, i.e., the necessary and sufficient condition for $d_{f'}(s) \geq d_f(s)$ to achieve equality cannot be satisfied, which conflicts with the contradiction assumption $d_{f'}(s) = d_f(s)$. The original proposition is proven.
    
    ??? failure "Another Common False Proof"
        Consider proof by contradiction. Assume the number of layers in the level graph equals the original after one round of augmentation, then there should still be at least one augmenting path from $s$ to $t$ on the level graph satisfying that the layer difference between adjacent nodes is 1. The fact that this augmenting path was not augmented means the round of augmentation is not complete. To avoid this contradiction, the original proposition holds.
    
    ??? bug "Bug"
        "The s-t shortest path on the new level graph after one round of augmentation equals the original" cannot lead to "the round of augmentation on the old level graph is not complete". This is because there is no reason to believe the edge sets of the two level graphs are the same; the s-t shortest path on the new level graph may pass through edges that do not exist on the old level graph.

Multiplying the time complexity of a single round of augmentation $O(|V||E|)$ by the number of augmentation rounds $O(|V|)$, the time complexity of the Dinic algorithm is $O(|V|^2|E|)$.

If we need the actual running time of the Dinic algorithm to approach its theoretical upper bound, we need to construct networks with special properties as input. Since in algorithm competition practice, the examination of network flow knowledge often focuses on the skill of modeling the original problem as a network flow problem. At this time, our modeling usually does not contain special properties that would cause Dinic to run slowly; on the contrary, Dinic is very efficient on most graphs. Therefore, the data ranges for network flow problems are usually large, and the method of "substituting the values of $|V|, |E|$ into $|V|^2|E|$ to estimate running time" is not applicable. In fact, accurate estimation requires contestants to have some experience with the actual efficiency of the Dinic algorithm. Readers can practice more.

#### Time Complexity Analysis for Special Cases

On some graphs with good properties, Dinic algorithm has better time complexity.

For a network $G = (V, E)$, if all its edges have capacity 1, i.e., $c(u, v) \in \{0, 1\}$ holds for all $(u, v) \in E$, then we call $G$ a unit capacity (Unit Capacity) network.

In unit capacity networks, the time complexity of a single round of augmentation for Dinic algorithm is $O(|E|)$.

???+ note "Proof"
    This is because each augmentation causes all edges on the augmenting path to become saturated and disappear, so in a single round of augmentation, each edge can be augmented at most once.

In unit capacity networks, the number of augmentation rounds for Dinic algorithm is $O(|E|^{\frac{1}{2}})$.

???+ note "Proof"
    Layer with the source $s$ as the center. Let $d_f(u)$ be the distance from node $u$ to the source $s$ on $G_f$. Additionally, we define the vertex set $\left\{u \mid u \in V, d_f(u) = k \right\}$ as level $D_k$ numbered $k$, and let $S_k = \cup_{i \leq k} D_i$.
    
    Suppose we have performed $|E|^{\frac{1}{2}}$ rounds of augmentation. By the pigeonhole principle, there must exist at least one $k$ such that the size of the edge set $\left\{ (u, v) \mid u \in D_k, v \in D_{k+1}, (u, v) \in E_f \right\}$ does not exceed $\frac {|E|} {|E|^{\frac{1}{2}}} \approx |E|^{\frac{1}{2}}$. Obviously, $\{S_k, V - S_k\}$ is an $s$-$t$ cut on $G_f$, and its cut capacity does not exceed $|E|^{\frac{1}{2}}$. By the max-flow mincut theorem, the maximum flow on $G_f$ does not exceed $|E|^{\frac{1}{2}}$, i.e., at most $|E|^{\frac{1}{2}}$ more rounds of augmentation can be performed on $G_f$. Therefore, the total number of augmentation rounds is $O(|E|^{\frac{1}{2}})$.

In unit capacity networks, the number of augmentation rounds for Dinic algorithm is $O(|V|^{\frac{2}{3}})$.

???+ note "Proof"
    Suppose we have performed $2 |V|^{\frac{2}{3}}$ rounds of augmentation. Since at most half of the levels ($|V|^{\frac{2}{3}}$ levels) contain more than $|V|^{\frac{1}{3}}$ nodes, no matter how we allocate the sizes of all levels, there must exist at least one $k$ such that two adjacent levels both contain no more than $|V|^{\frac{1}{3}}$ nodes, i.e., $|D_k| \leq |V|^{\frac{1}{3}}$ and $|D_{k+1}| \leq |V|^{\frac{1}{3}}$.
    
    To maximize the number of edges between $D_k$ and $D_{k+1}$, we assume this is a complete bipartite graph. At this time, the size of the edge set $\left\{ (u, v) \mid u \in D_k, v \in D_{k+1}, (u, v) \in E_f \right\}$ does not exceed $|V|^{\frac{2}{3}}$. Obviously, $\{S_k, V - S_k\}$ is an $s$-$t$ cut on $G_f$, and its cut capacity does not exceed $|V|^{\frac{2}{3}}$. By the max-flow mincut theorem, the maximum flow on $G_f$ does not exceed $|V|^{\frac{2}{3}}$, i.e., at most $|V|^{\frac{2}{3}}$ more rounds of augmentation can be performed on $G_f$. Therefore, the total number of augmentation rounds is $O(|V|^{\frac{2}{3}})$.

In unit capacity networks, if every node $u$ except the source and sink satisfies $\mathit{deg}_{\mathit{in}}(u) = 1$ or $\mathit{deg}_{\mathit{out}}(u) = 1$, then the number of augmentation rounds in Dinic algorithm is $O(|V|^{\frac{1}{2}})$. Here, $\mathit{deg}_{\mathit{in}}(u)$ and $\mathit{deg}_{\mathit{out}}(u)$ denote the indegree and outdegree of node $u$, respectively.

???+ note "Proof"
    We introduce the following lemma: for any network of this form, every flow can be decomposed into several unit-flow, **vertex-disjoint** augmenting paths.
    
    Suppose we have performed $|V|^{\frac{1}{2}}$ rounds of augmentation. By the definition of the level graph, any new augmenting path now has length at least $|V|^{\frac{1}{2}}$.
    
    Consider the augmenting-path decomposition of the maximum flow on $G_f$. The number of augmenting paths is at most $\frac {|V|} {|V|^{\frac{1}{2}}} \approx |V|^{\frac{1}{2}}$. This means at most $|V|^{\frac{1}{2}}$ more rounds of augmentation can be performed on $G_f$. Therefore, the total number of augmentation rounds is $O(|V|^{\frac{1}{2}})$.

In summary, we obtain the following corollaries.

-   In unit capacity networks, the total time complexity of Dinic algorithm is $O(|E| \min(|E|^\frac{1}{2}, |V|^{\frac{2}{3}}))$.
-   In unit capacity networks, if every node $u$ except the source and sink satisfies $\mathit{deg}_{\mathit{in}}(u) = 1$ or $\mathit{deg}_{\mathit{out}}(u) = 1$, the total time complexity of Dinic algorithm is $O(|E||V|^{\frac{1}{2}})$. For bipartite maximum matching, we often use the Hopcroft-Karp algorithm, which is in fact a special case of Dinic algorithm on a unit capacity network satisfying the degree restriction above.

#### Code Implementation

??? note "Reference Code"
    ```cpp
    struct MF {
      struct edge {
        int v, nxt, cap, flow;
      } e[N];
    
      int fir[N], cnt = 0;
    
      int n, S, T;
      ll maxflow = 0;
      int dep[N], cur[N];
    
      void init() {
        memset(fir, -1, sizeof fir);
        cnt = 0;
      }
    
      void addedge(int u, int v, int w) {
        e[cnt] = {v, fir[u], w, 0};
        fir[u] = cnt++;
        e[cnt] = {u, fir[v], 0, 0};
        fir[v] = cnt++;
      }
    
      bool bfs() {
        queue<int> q;
        memset(dep, 0, sizeof(int) * (n + 1));
    
        dep[S] = 1;
        q.push(S);
        while (q.size()) {
          int u = q.front();
          q.pop();
          for (int i = fir[u]; ~i; i = e[i].nxt) {
            int v = e[i].v;
            if ((!dep[v]) && (e[i].cap > e[i].flow)) {
              dep[v] = dep[u] + 1;
              q.push(v);
            }
          }
        }
        return dep[T];
      }
    
      int dfs(int u, int flow) {
        if ((u == T) || (!flow)) return flow;
    
        int ret = 0;
        for (int& i = cur[u]; ~i; i = e[i].nxt) {
          int v = e[i].v, d;
          if ((dep[v] == dep[u] + 1) &&
              (d = dfs(v, min(flow - ret, e[i].cap - e[i].flow)))) {
            ret += d;
            e[i].flow += d;
            e[i ^ 1].flow -= d;
            if (ret == flow) return ret;
          }
        }
        return ret;
      }
    
      void dinic() {
        while (bfs()) {
          memcpy(cur, fir, sizeof(int) * (n + 1));
          maxflow += dfs(S, INF);
        }
      }
    } mf;
    ```

### MPM Algorithm

**MPM** (Malhotra, Pramodh-Kumar and Maheshwari) algorithm obtains maximum flow in two ways: using a heap-based priority queue with time complexity $O(n^3\log n)$; commonly using BFS solution with time complexity $O(n^3)$. Note, this section only focuses on analyzing the better and simpler $O(n^3)$ algorithm.

The overall structure of MPM algorithm is similar to Dinic algorithm, also running in phases. In each phase, find augmenting paths in the layered network of the residual network of $G$. The main difference from Dinic algorithm is in the way of finding augmenting paths: the part of MPM algorithm that finds augmenting paths only takes $O(n^2)$, which has better time complexity than Dinic algorithm.

MPM algorithm needs to consider vertex capacity rather than edge capacity. In the layered network $L$, if we define the capacity of vertex $v$ as $p(v)$ as the minimum of its incoming residual and outgoing residual, then we have:

$$
\begin{aligned}
p_{in}(v) &= \sum\limits_{(u,v) \in L} (c(u, v) - f(u, v)) \\
p_{out}(v) &= \sum\limits_{(v,u) \in L} (c(v, u) - f(v, u)) \\
p(v) &= \min (p_{in}(v), p_{out}(v))
\end{aligned}
$$

We call node $r$ a reference node if and only if $p(r) = \min \{p(v)\}$. For a reference node $r$, we can definitely increase the flow through $r$ by $p(r)$ to make its capacity zero. This is because $L$ is a directed acyclic graph and the node capacity in $L$ is at least $p(r)$, so we can definitely find a directed path from $s$ through $r$ to $t$. Then we can increase the flow on all edges of this path by $p(r)$. This path is the augmenting path for this phase. Finding augmenting paths can use BFS. After augmentation, all saturated edges can be removed from $L$ because they will not be used after this phase. Similarly, all nodes other than $s$ and $t$ that have no outgoing or incoming edges can also be deleted.

#### Time Complexity Analysis

Each phase of MPM algorithm requires $O(V^2)$ because there are at most $V$ iterations (since at least the selected reference node is deleted), and in each iteration, we delete all edges traversed except at most $V$. Summing, we get $O(V^2+E)=O(V^2)$. Since the total number of phases is less than $V$, the total running time of MPM algorithm is $O(V^3)$.

???+ note "Proof that total phases < V"
    MPM algorithm finishes in fewer than $V$ phases. To prove this, we must first prove two lemmas.
    
    **Lemma 1**: After each iteration, the distance from $s$ to each point does not decrease, that is, $level_{i+1}[v] \ge level_{i}[v]$.
    
    **Proof**: Fix a phase $i$ and point $v$. Consider any shortest path $P$ from $s$ to $v$ in $G_{i}^R$. The length of $P$ equals $level_{i}[v]$. Note that $G_{i}^R$ can only contain backward edges and forward edges of $G_{i}^R$. If $P$ has no backward edge of $G_{i}^R$, then $level_{i+1}[v] \ge level_{i}[v]$ because $P$ is also a path in $G_{i}^R$. Now, suppose $P$ has at least one backward edge and the first such edge is $(u,w)$, then $level_{i+1}[u] \ge level_{i}[u]$ (because of the first case). Edge $(u,w)$ does not belong to $G_{i}^R$, therefore $(u,w)$ is affected by the augmenting path of the previous iteration. This means $level_{i}[u] = level_{i}[w]+1$. Additionally, $level_{i+1}[w] = level_{i+1}[u]+1$. From these two equations and $level_{i+1}[u] \ge level_{i}[u]$ we get $level_{i+1}[w] \ge level_{i}[w]+2$. The remaining part of the path can use the same reasoning.
    
    **Lemma 2**: $level_{i+1}[t] > level_{i}[t]$.
    
    **Proof**: From Lemma 1 we get $level_{i+1}[t] \ge level_{i}[t]$. Suppose $level_{i+1}[t] = level_{i}[t]$, note that $G_{i}^R$ can only contain backward edges and forward edges of $G_{i}^R$. This means there is a shortest path in $G_{i}^R$ that is not blocked by augmenting paths. This forms a contradiction.

#### Implementation

??? note "Reference Code"
    ```cpp
    struct MPM {
      struct FlowEdge {
        int v, u;
        long long cap, flow;
    
        FlowEdge() {}
    
        FlowEdge(int _v, int _u, long long _cap, long long _flow)
            : v(_v), u(_u), cap(_cap), flow(_flow) {}
    
        FlowEdge(int _v, int _u, long long _cap)
            : v(_v), u(_u), cap(_cap), flow(0ll) {}
      };
    
      constexpr static long long flow_inf = 1e18;
      vector<FlowEdge> edges;
      vector<char> alive;
      vector<long long> pin, pout;
      vector<list<int>> in, out;
      vector<vector<int>> adj;
      vector<long long> ex;
      int n, m = 0;
      int s, t;
      vector<int> level;
      vector<int> q;
      int qh, qt;
    
      void resize(int _n) {
        n = _n;
        ex.resize(n);
        q.resize(n);
        pin.resize(n);
        pout.resize(n);
        adj.resize(n);
        level.resize(n);
        in.resize(n);
        out.resize(n);
      }
    
      MPM() {}
    
      MPM(int _n, int _s, int _t) {
        resize(_n);
        s = _s;
        t = _t;
      }
    
      void add_edge(int v, int u, long long cap) {
        edges.push_back(FlowEdge(v, u, cap));
        edges.push_back(FlowEdge(u, v, 0));
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
      }
    
      bool bfs() {
        while (qh < qt) {
          int v = q[qh++];
          for (int id : adj[v]) {
            if (edges[id].cap - edges[id].flow < 1) continue;
            if (level[edges[id].u] != -1) continue;
            level[edges[id].u] = level[v] + 1;
            q[qt++] = edges[id].u;
          }
        }
        return level[t] != -1;
      }
    
      long long pot(int v) { return min(pin[v], pout[v]); }
    
      void remove_node(int v) {
        for (int i : in[v]) {
          int u = edges[i].v;
          auto it = find(out[u].begin(), out[u].end(), i);
          out[u].erase(it);
          pout[u] -= edges[i].cap - edges[i].flow;
        }
        for (int i : out[v]) {
          int u = edges[i].u;
          auto it = find(in[u].begin(), in[u].end(), i);
          in[u].erase(it);
          pin[u] -= edges[i].cap - edges[i].flow;
        }
      }
    
      void push(int from, int to, long long f, bool forw) {
        qh = qt = 0;
        ex.assign(n, 0);
        ex[from] = f;
        q[qt++] = from;
        while (qh < qt) {
          int v = q[qh++];
          if (v == to) break;
          long long must = ex[v];
          auto it = forw ? out[v].begin() : in[v].begin();
          while (true) {
            int u = forw ? edges[*it].u : edges[*it].v;
            long long pushed = min(must, edges[*it].cap - edges[*it].flow);
            if (pushed == 0) break;
            if (forw) {
              pout[v] -= pushed;
              pin[u] -= pushed;
            } else {
              pin[v] -= pushed;
              pout[u] -= pushed;
            }
            if (ex[u] == 0) q[qt++] = u;
            ex[u] += pushed;
            edges[*it].flow += pushed;
            edges[(*it) ^ 1].flow -= pushed;
            must -= pushed;
            if (edges[*it].cap - edges[*it].flow == 0) {
              auto jt = it;
              ++jt;
              if (forw) {
                in[u].erase(find(in[u].begin(), in[u].end(), *it));
                out[v].erase(it);
              } else {
                out[u].erase(find(out[u].begin(), out[u].end(), *it));
                in[v].erase(it);
              }
              it = jt;
            } else
              break;
            if (!must) break;
          }
        }
      }
    
      long long flow() {
        long long ans = 0;
        while (true) {
          pin.assign(n, 0);
          pout.assign(n, 0);
          level.assign(n, -1);
          alive.assign(n, true);
          level[s] = 0;
          qh = 0;
          qt = 1;
          q[0] = s;
          if (!bfs()) break;
          for (int i = 0; i < n; i++) {
            out[i].clear();
            in[i].clear();
          }
          for (int i = 0; i < m; i++) {
            if (edges[i].cap - edges[i].flow == 0) continue;
            int v = edges[i].v, u = edges[i].u;
            if (level[v] + 1 == level[u] && (level[u] < level[t] || u == t)) {
              in[u].push_back(i);
              out[v].push_back(i);
              pin[u] += edges[i].cap - edges[i].flow;
              pout[v] += edges[i].cap - edges[i].flow;
            }
          }
          pin[s] = pout[t] = flow_inf;
          while (true) {
            int v = -1;
            for (int i = 0; i < n; i++) {
              if (!alive[i]) continue;
              if (v == -1 || pot(i) < pot(v)) v = i;
            }
            if (v == -1) break;
            if (pot(v) == 0) {
              alive[v] = false;
              remove_node(v);
              continue;
            }
            long long f = pot(v);
            ans += f;
            push(v, s, f, false);
            push(v, t, f, true);
            alive[v] = false;
            remove_node(v);
          }
        }
        return ans;
      }
    };
    ```

### ISAP

In Dinic algorithm, after finding each augmenting path, we need to run BFS for layering. Is there a more efficient method?

The answer is the ISAP algorithm introduced below.

#### Process

Like Dinic algorithm, we still first run BFS to layer the nodes on the graph. However, slightly different from Dinic, we choose to run BFS on the reverse graph from point $t$ to point $s$.

After completing the layering process, we find augmenting paths through DFS.

The augmentation process is similar to Dinic. We only choose points with layer number one less than the current point to augment.

Unlike Dinic, we do not rerun BFS to relayer the nodes on the graph, but instead complete the relayering process during the augmentation process.

Specifically, let the layer of point $i$ be $d_i$. After finishing the augmentation process at point $i$, we traverse all outgoing edges of $i$ in the residual network, find the outgoing point $j$ with the minimum layer, then set $d_i \gets d_j+1$. Particularly, if $i$ has no outgoing edges in the residual network, then $d_i \gets n$.

It is easy to see that when $d_s \geq n$, there is no augmenting path on the graph, and the algorithm can terminate at this time.

Like Dinic, ISAP also has **current arc optimization**.

Additionally, ISAP has another optimization. We record the number of points with layer number $i$ as $num_i$. Whenever updating a point's layer from $x$ to $y$, we simultaneously update the values in the num array. If after updating $num_x=0$, it means a gap has appeared in the graph, and no more augmenting paths can be found. At this time, we can directly terminate the algorithm (in implementation, simply mark $d_s$ as $n$). This optimization is called **GAP optimization**.

#### Implementation

??? note "Reference Code"
    ```cpp
    struct Edge {
      int from, to, cap, flow;
    
      Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
    };
    
    bool operator<(const Edge& a, const Edge& b) {
      return a.from < b.from || (a.from == b.from && a.to < b.to);
    }
    
    struct ISAP {
      int n, m, s, t;
      vector<Edge> edges;
      vector<int> G[MAXN];
      bool vis[MAXN];
      int d[MAXN];
      int cur[MAXN];
      int p[MAXN];
      int num[MAXN];
    
      void AddEdge(int from, int to, int cap) {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
      }
    
      bool BFS() {
        memset(vis, 0, sizeof(vis));
        queue<int> Q;
        Q.push(t);
        vis[t] = true;
        d[t] = 0;
        while (!Q.empty()) {
          int x = Q.front();
          Q.pop();
          for (int i = 0; i < G[x].size(); i++) {
            Edge& e = edges[G[x][i] ^ 1];
            if (!vis[e.from] && e.cap > e.flow) {
              vis[e.from] = true;
              d[e.from] = d[x] + 1;
              Q.push(e.from);
            }
          }
        }
        return vis[s];
      }
    
      void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
      }
    
      int Augment() {
        int x = t, a = INF;
        while (x != s) {
          Edge& e = edges[p[x]];
          a = min(a, e.cap - e.flow);
          x = edges[p[x]].from;
        }
        x = t;
        while (x != s) {
          edges[p[x]].flow += a;
          edges[p[x] ^ 1].flow -= a;
          x = edges[p[x]].from;
        }
        return a;
      }
    
      int Maxflow(int s, int t) {
        this->s = s;
        this->t = t;
        int flow = 0;
        BFS();
        memset(num, 0, sizeof(num));
        for (int i = 0; i < n; i++) num[d[i]]++;
        int x = s;
        memset(cur, 0, sizeof(cur));
        while (d[s] < n) {
          if (x == t) {
            flow += Augment();
            x = s;
          }
          int ok = 0;
          for (int i = cur[x]; i < G[x].size(); i++) {
            Edge& e = edges[G[x][i]];
            if (e.cap > e.flow && d[x] == d[e.to] + 1) {
              ok = 1;
              p[e.to] = G[x][i];
              cur[x] = i;
              x = e.to;
              break;
            }
          }
          if (!ok) {
            int m = n - 1;
            for (int i = 0; i < G[x].size(); i++) {
              Edge& e = edges[G[x][i]];
              if (e.cap > e.flow) m = min(m, d[e.to]);
            }
            if (--num[d[x]] == 0) break;
            num[d[x] = m + 1]++;
            cur[x] = 0;
            if (x != s) x = edges[p[x]].from;
          }
        }
        return flow;
      }
    };
    ```

## Push-Relabel Preflow-Push Algorithm

This method ignores flow conservation during the solving process, and updates information for each node to solve the maximum flow.

### General Preflow-Push Algorithm

First we introduce the main idea of the Preflow-Push algorithm, and a feasible brute-force implementation algorithm.

Preflow-Push algorithm solves the maximum flow by updating individual nodes until no node needs to be updated.

The flow function maintained by the algorithm process does not necessarily preserve flow conservation. For a node, we allow the flow entering the node to exceed the flow leaving the node. The excess part is called the **excess flow** $e(u)$ of node $u$ ($u\in V-\{s,t\}$):

$$
e(u)=\sum_{(x,u)\in E}f(x,u)-\sum_{(u,y)\in E}f(u,y)
$$

If $e(u)>0$, we say node $u$ **overflows**[^note1]. Note that when we mention overflow nodes, we do not include $s$ and $t$.

Preflow-Push algorithm maintains a height $h(u)$ for each node, and stipulates that if an overflow node $u$ wants to push excess flow, it can only push to nodes with height less than $u$; if $u$ has no adjacent nodes with height less than $u$, then modify the height of $u$ (relabel).

#### Height Function[^note2]

Precisely, preflow-push maintains the following mapping $h:V\to \mathbf{N}$:

-   $h(s)=|V|,h(t)=0$
-   $\forall (u,v)\in E_f,h(u)\leq h(v)+1$

We call $h$ the height function of the residual network $G_f=(V_f,E_f)$.

Lemma 1: Let $h$ be the height function on $G_f$. For any two nodes $u,v\in V$, if $h(u)>h(v)+1$, then $(u,v)$ is not an edge in $G_f$.

The algorithm only performs push on edges where $h(u)=h(v)+1$.

#### Push

Applicable conditions: node $u$ overflows, and there exists node $v$ $((u,v)\in E_f,c(u,v)-f(u,v)>0,h(u)=h(v)+1)$, then the push operation applies to $(u,v)$.

Therefore, we try our best to push excess flow from $u$ to $v$. During the push process, we only care about the minimum of the excess flow and $c(u,v)-f(u,v)$, not whether $v$ overflows.

If $(u,v)$ becomes saturated after pushing, delete it from the residual network.

#### Relabel

Applicable conditions: if node $u$ overflows, and $\forall (u,v)\in E_f,h(u)\leq h(v)$, then the relabel operation applies to $u$.

Then we can update $h(u)$ to $\min_{(u,v)\in E_f}h(v)+1$.

#### Initialization

$$
\forall (u,v)\in E,~~f(u,v)=\begin{cases}
c(u,v),&u=s\\
0,&u\neq s
\end{cases}
$$

$$
\forall u\in V,~~h(u)=\begin{cases}
|V|,&u=s\\
0,&u\neq s
\end{cases}
$$

$$
e(u)=\sum_{(x,u)\in E}f(x,u)-\sum_{(u,y)\in E}f(u,y)
$$

The above fills $(s,v)\in E$ with flow, and raises $h(s)$ so that $(s,v)\notin E_f$, because $h(s)>h(v)$, and since $(s,v)$ is saturated anyway, there is no need to keep it in the residual network; the above also initializes $e(s)$ as the negative of $\sum_{(s,v)\in E}f(s,v)$.

#### Process

We scan the entire graph each time. As long as there exists a node $u$ that satisfies the conditions for push or relabel operations, we execute the corresponding operation.

As shown in the figure, the middle of each node represents the number, the bottom-left represents the height value $h(u)$, the bottom-right represents the excess flow $e(u)$, and the depth of node color also represents the height of the node; edge weights represent $c(u,v)-f(u,v)$, and green edges represent edges $(u,v)$ where $h(u)=h(v)+1$ (i.e., edges of the residual network $E_f$):

![p1](./images/2148.png)

Let's roughly go through the entire algorithm process. Here the author uses a brute-force algorithm, which is to brute-force scan whether there are overflow nodes, and update if there are

![p2](./images/2149.gif)

The final result

![p3](./images/2150.png)

We can find that the final excess flow partially returns to $s$, and except for the source and sink, no other nodes overflow; at this time, the flow function $f$ satisfies flow conservation, which is the maximum flow, and the flow value is $e(t)$.

However, actually the paper[^ref1] points out that only processing overflow nodes with height less than $n$ can also obtain the correct maximum flow value. However, in this case, at the end of the algorithm, the preflow still does not satisfy the flow function property, and we cannot know the real flow on each edge.

#### Implementation

???+ note "Core Code"
    ```cpp
    constexpr int N = 1e4 + 4, M = 1e5 + 5, INF = 0x3f3f3f3f;
    int n, m, s, t, maxflow, tot;
    int ht[N], ex[N];
    
    void init() {  // Initialization
      for (int i = h[s]; i; i = e[i].nex) {
        const int &v = e[i].t;
        ex[v] = e[i].v, ex[s] -= ex[v], e[i ^ 1].v = e[i].v, e[i].v = 0;
      }
      ht[s] = n;
    }
    
    bool push(int ed) {
      const int &u = e[ed ^ 1].t, &v = e[ed].t;
      int flow = min(ex[u], e[ed].v);
      ex[u] -= flow, ex[v] += flow, e[ed].v -= flow, e[ed ^ 1].v += flow;
      return ex[u];  // If u still overflows, return 1
    }
    
    void relabel(int u) {
      ht[u] = INF;
      for (int i = h[u]; i; i = e[i].nex)
        if (e[i].v) ht[u] = min(ht[u], ht[e[i].t]);
      ++ht[u];
    }
    ```

### HLPP Algorithm

The Highest Label Preflow-Push Algorithm (Highest Label Preflow Push) in the general preflow-push algorithm mentioned above, when selecting a node each time, always prioritizes the overflow node with the highest height. Its algorithm complexity is $O(n^2\sqrt m)$.

#### Process

Specifically, the HLPP algorithm process is as follows:

1.  Initialization (based on Preflow-Push algorithm);
2.  Select the node $u$ with the highest height among overflow nodes, and push along all edges that can be pushed;
3.  If $u$ still overflows, relabel it, and go back to step 2;
4.  If there are no overflow nodes, the algorithm ends.

A paper[^ref2] that tests the actual performance of maximum flow algorithms shows that for preflow-based algorithms, a considerable amount of time is actually spent on the relabel step. Below we introduce two optimizations from paper[^ref3] that can significantly reduce the number of relabel operations.

#### BFS Optimization

The upper bound of HLPP is $O(n^2\sqrt m)$, but it is quite tight when used; we can optimize when initializing height. Specifically, we initialize $h(u)$ as the shortest distance from $u$ to $t$; particularly, $h(s)=n$.

During BFS, we also conveniently check the connectivity of the graph to rule out the case of no solution.

#### GAP Optimization

The condition for HLPP push is $h(u)=h(v)+1$. If at some point in the algorithm there exists a $k$ such that the number of nodes with $h(u)=k$ is $0$, then for all nodes with $h(u)>k$, they can never push excess flow to $t$, so they can only be sent back to $s$. At this time, we directly set their height to at least $n+1$ to send them back to $s$ as quickly as possible, reducing relabel operations.

The following implementation adopts the method from paper[^ref2], using $N*2-1$ buckets `B`, where `B[i]` records all overflow nodes with current height $i$. It incorporates the two optimizations mentioned above, and only processes overflow nodes with height less than $n$.

It is worth noting that the bucket used in paper[^ref2] is a stack based on linked list, while the default container for `stack` in STL is `deque`. After simple testing, we found that `vector`, `deque`, and `list` have negligible efficiency differences in the actual running process of this problem.

#### Implementation

??? note "LuoguP4722【模板】最大流 加强版/预流推进"
    ```cpp
    #include <cstdio>
    #include <cstring>
    #include <queue>
    #include <stack>
    using namespace std;
    constexpr int N = 1200, M = 120000, INF = 0x3f3f3f3f;
    int n, m, s, t;
    
    struct qxx {
      int nex, t;
      long long v;
    };
    
    qxx e[M * 2 + 1];
    int h[N + 1], cnt = 1;
    
    void add_path(int f, int t, long long v) {
      e[++cnt] = qxx{h[f], t, v}, h[f] = cnt;
    }
    
    void add_flow(int f, int t, long long v) {
      add_path(f, t, v);
      add_path(t, f, 0);
    }
    
    int ht[N + 1];        // Height
    long long ex[N + 1];  // Excess flow
    int gap[N];           // GAP optimization. gap[i] is the number of nodes with height i
    stack<int> B[N];      // Bucket B[i] records all v with ht[v] == i
    int level = 0;        // Highest height among overflowing nodes
    
    int push(int u) {      // Push excess flow through all admissible edges as much as possible
      bool init = u == s;  // Whether this is initialization
      for (int i = h[u]; i; i = e[i].nex) {
        const int &v = e[i].t;
        const long long &w = e[i].v;
        // During initialization, do not require a height difference of 1
        if (!w || (init == false && ht[u] != ht[v] + 1) || ht[v] == INF) continue;
        long long k = init ? w : min(w, ex[u]);
        // Take the minimum of residual capacity and excess flow. During initialization, the source excess can become negative.
        if (v != s && v != t && !ex[v]) B[ht[v]].push(v), level = max(level, ht[v]);
        ex[u] -= k, ex[v] += k, e[i].v -= k, e[i ^ 1].v += k;  // push
        if (!ex[u]) return 0;  // Return after all excess has been pushed
      }
      return 1;
    }
    
    void relabel(int u) {  // Relabel the height
      ht[u] = INF;
      for (int i = h[u]; i; i = e[i].nex)
        if (e[i].v) ht[u] = min(ht[u], ht[e[i].t]);
      if (++ht[u] < n) {  // Only process nodes with height less than n
        B[ht[u]].push(u);
        level = max(level, ht[u]);
        ++gap[ht[u]];  // Update gap for the new height
      }
    }
    
    bool bfs_init() {
      memset(ht, 0x3f, sizeof(ht));
      queue<int> q;
      q.push(t), ht[t] = 0;
      while (q.size()) {  // Reverse BFS; enqueue unvisited nodes
        int u = q.front();
        q.pop();
        for (int i = h[u]; i; i = e[i].nex) {
          const int &v = e[i].t;
          if (e[i ^ 1].v && ht[v] > ht[u] + 1) ht[v] = ht[u] + 1, q.push(v);
        }
      }
      return ht[s] != INF;  // Return 0 if the graph is disconnected
    }
    
    // Select one node with the current maximum height, or return 0 if there are no overflowing nodes
    int select() {
      while (level > -1 && B[level].size() == 0) level--;
      return level == -1 ? 0 : B[level].top();
    }
    
    long long hlpp() {            // Return the maximum flow
      if (!bfs_init()) return 0;  // The graph is disconnected
      memset(gap, 0, sizeof(gap));
      for (int i = 1; i <= n; i++)
        if (ht[i] != INF) gap[ht[i]]++;  // Initialization gap
      ht[s] = n;
      push(s);  // Initialize the preflow
      int u;
      while ((u = select())) {
        B[level].pop();
        if (push(u)) {  // Still overflowing
          if (!--gap[ht[u]])
            for (int i = 1; i <= n; i++)
              if (i != s && ht[i] > ht[u] && ht[i] < n + 1)
                ht[i] = n + 1;  // Nodes relabeled to n+1 here are not overflowing nodes
          relabel(u);
        }
      }
      return ex[t];
    }
    
    int main() {
      scanf("%d%d%d%d", &n, &m, &s, &t);
      for (int i = 1, u, v, w; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        add_flow(u, v, w);
      }
      printf("%lld", hlpp());
      return 0;
    }
    ```

Here is the execution process.

![HLPP](./images/1152.png)

From pic13 to pic14, Relabel(4) is performed and the GAP optimization is applied.

## Footnotes

[^ref_ek]: <http://pisces.ck.tp.edu.tw/~peng/index.php?action=showfile&file=f6cdf7ef750d7dc79c7d599b942acbaaee86a2e3e>

[^ref_dinic]: <https://people.orie.cornell.edu/dpw/orie633/LectureNotes/lecture9.pdf>

[^ref1]: Cherkassky B V, Goldberg A V. On implementing push-relabel method for the maximum flow problem\[C]//International Conference on Integer Programming and Combinatorial Optimization. Springer, Berlin, Heidelberg, 1995: 157-171.

[^ref2]: Ahuja R K, Kodialam M, Mishra A K, et al. Computational investigations of maximum flow algorithms\[J]. European Journal of Operational Research, 1997, 97(3): 509-542.

[^ref3]: Derigs U, Meier W. Implementing Goldberg's max-flow-algorithm—A computational investigation\[J]. Zeitschrift für Operations Research, 1989, 33(6): 383-403.

[^note1]: In English literature, this is usually called "active".

[^note2]: In English literature, a node's height is usually called a "distance label". The term "height" used here comes from the corresponding chapter of *Introduction to Algorithms*. The reason for this terminology can be found in the footnote on page 432 of the China Machine Press translation of *Introduction to Algorithms*, 3rd edition.
