## Introduction

Before reading the following content, be sure to understand the basics in [Graph Theory Concepts](./concept.md).

The definition of strong connectivity is: A directed graph G is strongly connected if any two vertices in G are connected.

The definition of a Strongly Connected Component (SCC) is: A maximal strongly connected subgraph.

What is introduced here is how to find strongly connected components.

## Tarjan's Algorithm

### Introduction

Robert E. Tarjan (1948~), born in Pomona, California, is a computer scientist.

Tarjan has invented many algorithms and data structures. Many algorithms invented by him are named after him, sometimes causing confusion between different algorithms. For example, Tarjan's algorithm for finding various connected components, Tarjan's algorithm for LCA (Lowest Common Ancestor). Disjoint set unions, Splay, and Toptree are also invented by Tarjan.

Here we introduce Tarjan's algorithm for finding strongly connected components in directed graphs.

### DFS Spanning Tree

Before introducing this algorithm, let's first understand the **DFS spanning tree**. Let's use the following directed graph as an example:

![DFS Spanning Tree](./images/dfs-tree.svg)

When running the DFS algorithm on a directed graph $G$, because edges have direction, starting from a single vertex may not be able to visit all vertices in the graph. Therefore, we need to traverse the entire vertex set: perform DFS again for each unvisited vertex. During each DFS process starting from a vertex, the tree edges (see below) form a tree, called a **DFS spanning tree**. After all vertices are visited, the collection of all DFS spanning trees forms the **DFS spanning forest** of the directed graph.

It should be noted that the specific structure of the spanning tree (and spanning forest), as well as the edge classification below, depends on the choice of starting vertex for DFS and the order of visiting adjacent vertices.

Edges in a directed graph $G$ can be classified into four types:

1.  **Tree edge**: Represented by black edges in the diagram. Each time we find an unvisited vertex, a tree edge is formed. All adjacent tree edges form the DFS spanning tree.
2.  **Back edge**: Also called reverse edge, represented by red edges in the diagram (i.e., $7 \rightarrow 1$), referring to a non-tree edge from a vertex to its ancestor during the search.
3.  **Forward edge**: Represented by green edges in the diagram (i.e., $3 \rightarrow 6$), referring to a non-tree edge from a vertex to a descendant in its subtree during the search.
4.  **Cross edge**: Represented by blue edges in the diagram (i.e., $9 \rightarrow 7$), referring to an edge from a vertex to an already visited vertex that is neither an ancestor nor a descendant during the search, i.e., edges that do not belong to the above three categories.

Let's consider the relationship between the DFS spanning tree and strongly connected components.

If vertex $u$ is the first vertex encountered in the search tree for some strongly connected component, then the other vertices of this strongly connected component are definitely in the subtree rooted at $u$ in the search tree. Vertex $u$ is called the root of this strongly connected component.

Proof by contradiction: Suppose there is a vertex $v$ in this strongly connected component but not in the subtree rooted at $u$. Then on the path from $u$ to $v$, there must be an edge leaving the subtree. However, such an edge can only be a cross edge or a back edge, but both require the target vertex to have already been visited, which contradicts $v$ not being in the subtree rooted at $u$. Proven.

### Tarjan's Algorithm for Strongly Connected Components

Tarjan's algorithm is based on performing [Depth-First Search](./dfs.md) on the graph. We treat each connected component as a subtree in the search tree. During the search, we maintain a stack and add unprocessed nodes from the search tree to the stack.

In Tarjan's algorithm, we maintain the following variables for each vertex $u$:

1.  $\textit{dfn}_u$: The order in which vertex $u$ is visited during the depth-first search traversal.
2.  $\textit{low}_u$: The earliest vertex that can be reached from the subtree of $u$ and is already in the stack. Let the subtree rooted at $u$ be $\textit{Subtree}_u$. $\textit{low}_u$ is defined as the minimum $\textit{dfn}$ among: vertices in $\textit{Subtree}_u$; vertices that can be reached from $\textit{Subtree}_u$ via an edge not in the search tree.

All vertices in a node's subtree have dfn greater than that node's dfn.

The dfn on a path from the root strictly increases, while low is strictly non-decreasing.

According to the order of the depth-first search algorithm, search all vertices in the graph, maintain each vertex's `dfn` and `low` variables, and push visited vertices onto the stack. Whenever a strongly connected element is found, pop vertices from the stack according to the number of vertices it contains. During the search, for vertex $u$ and its adjacent vertex $v$ ($v$ is not $u$'s parent), consider three cases:

1.  $v$ has not been visited: Continue the depth-first search on $v$. During backtracking, use $\textit{low}_v$ to update $\textit{low}_u$. Because there is a direct path from $u$ to $v$, any vertex that $v$ can reach in the stack, $u$ can also reach.
2.  $v$ has been visited and is already in the stack: According to the definition of low value, use $\textit{dfn}_v$ to update $\textit{low}_u$.
3.  $v$ has been visited and is no longer in the stack: This indicates that $v$ has finished its search and its connected component has been processed, so no operation is needed on it.

Write the above algorithm as pseudocode:

???+ note "Implementation"
    ```text
    TARJAN_SEARCH(int u)
        vis[u]=true
        low[u]=dfn[u]=++dfncnt
        push u to the stack
        for each (u,v) then do
            if v hasn't been searched then
                TARJAN_SEARCH(v) // search
                low[u]=min(low[u],low[v]) // backtrack
            else if v has been in the stack then
                low[u]=min(low[u],dfn[v])
    ```

For a connected component graph, it's easy to think that there is exactly one vertex $u$ such that $\textit{dfn}_u=\textit{low}_u$ in the connected graph. This vertex must be the first visited vertex in the connected component during the depth traversal, because its dfn and low values are the smallest and won't be affected by other vertices in the connected component.

Therefore, during backtracking, we check whether $\textit{dfn}_u=\textit{low}_u$ holds. If it holds, then $u$ and the vertices above it in the stack form an SCC.

### Implementation

=== "C++"
    ```cpp
    int dfn[N], low[N], dfncnt, s[N], in_stack[N], tp;
    int scc[N], sc;  // Number of the SCC that vertex i belongs to
    int sz[N];       // Size of strongly connected i
    
    void tarjan(int u) {
      low[u] = dfn[u] = ++dfncnt, s[++tp] = u, in_stack[u] = 1;
      for (int i = h[u]; i; i = e[i].nex) {
        const int &v = e[i].t;
        if (!dfn[v]) {
          tarjan(v);
          low[u] = min(low[u], low[v]);
        } else if (in_stack[v]) {
          low[u] = min(low[u], dfn[v]);
        }
      }
      if (dfn[u] == low[u]) {
        ++sc;
        do {
          scc[s[tp]] = sc;
          sz[sc]++;
          in_stack[s[tp]] = 0;
        } while (s[tp--] != u);
      }
    }
    ```

=== "Python"
    ```python
    dfn = [0] * N
    low = [0] * N
    dfncnt = 0
    s = [0] * N
    in_stack = [0] * N
    tp = 0
    scc = [0] * N
    sc = 0  # Number of the SCC that vertex i belongs to
    sz = [0] * N  # Size of strongly connected i
    
    
    def tarjan(u):
        low[u] = dfn[u] = dfncnt
        s[tp] = u
        in_stack[u] = 1
        dfncnt = dfncnt + 1
        tp = tp + 1
        i = h[u]
        while i:
            v = e[i].t
            if dfn[v] == False:
                tarjan(v)
                low[u] = min(low[u], low[v])
            elif in_stack[v]:
                low[u] = min(low[u], dfn[v])
            i = e[i].nex
        if dfn[u] == low[u]:
            sc = sc + 1
            while s[tp] != u:
                scc[s[tp]] = sc
                sz[sc] = sz[sc] + 1
                in_stack[s[tp]] = 0
                tp = tp - 1
            scc[s[tp]] = sc
            sz[sc] = sz[sc] + 1
            in_stack[s[tp]] = 0
            tp = tp - 1
    ```

Time complexity $O(n + m)$.

### Relationship Between Component Numbering and Topological Order

During the processing, Tarjan's algorithm actually discovers strongly connected components in a certain **reverse topological order**. This is because the algorithm first visits all nodes without outgoing edges during the depth-first search, which is opposite to the process of topological sorting.

If we contract each strongly connected component in the graph into a single node, then performing topological sorting on the DAG formed by these contracted nodes will give an order opposite to the order of SCC numbers given by Tarjan's algorithm.

Therefore, in the contracted DAG, **the order of strongly connected component (after contraction) numbers is the reverse of their topological order**. However, it should be noted that this statement only holds when considering the dependencies between strongly connected components (i.e., directed edges from one strongly connected component to another). Within a single strongly connected component, because there are cycles, the internal vertices do not satisfy the definition of topological order.

## Kosaraju's Algorithm

### Introduction

Kosaraju's algorithm was first proposed in 1978 by S. Rao Kosaraju in an unpublished paper, but Micha Sharir was the first to publish it.

### Process

The algorithm relies on two simple DFS passes:

In the first DFS, start from any vertex, traverse all unvisited vertices, and assign numbers to vertices before backtracking, i.e., post-order traversal.

In the second DFS, for the reversed graph, start DFS from the vertex with the largest number. The vertices traversed form a strongly connected component. For all unvisited vertices, select the one with the largest number and repeat the above process.

After two DFS passes, the strongly connected components are found. The time complexity of Kosaraju's algorithm is $O(n+m)$.

### Implementation

=== "C++"
    ```cpp
    // g is the original graph, g2 is the reversed graph
    
    void dfs1(int u) {
      vis[u] = true;
      for (int v : g[u])
        if (!vis[v]) dfs1(v);
      s.push_back(u);
    }
    
    void dfs2(int u) {
      color[u] = sccCnt;
      for (int v : g2[u])
        if (!color[v]) dfs2(v);
    }
    
    void kosaraju() {
      sccCnt = 0;
      for (int i = 1; i <= n; ++i)
        if (!vis[i]) dfs1(i);
      for (int i = n; i >= 1; --i)
        if (!color[s[i]]) {
          ++sccCnt;
          dfs2(s[i]);
        }
    }
    ```

=== "Python"
    ```python
    def dfs1(u):
        vis[u] = True
        for v in g[u]:
            if vis[v] == False:
                dfs1(v)
        s.append(u)
    
    
    def dfs2(u):
        color[u] = sccCnt
        for v in g2[u]:
            if color[v] == False:
                dfs2(v)
    
    
    def kosaraju(u):
        sccCnt = 0
        for i in range(1, n + 1):
            if vis[i] == False:
                dfs1(i)
        for i in range(n, 0, -1):
            if color[s[i]] == False:
                sccCnt = sccCnt + 1
                dfs2(s[i])
    ```

## Garbow's Algorithm

### Process

Garbow's algorithm is another implementation of Tarjan's algorithm. Tarjan's algorithm uses dfn and low to compute the root of strongly connected components. Garbow maintains a vertex stack and uses a second stack to determine when to pop vertices belonging to the same strongly connected component from the first stack. During the DFS process starting from vertex $w$, when a path shows that this group of vertices all belong to the same strongly connected component, as long as the visiting time of the stack top vertex is greater than the visiting time of root $w$, pop that vertex from the second stack. Then only root $w$ remains. In this process, every popped vertex belongs to the same strongly connected component.

When backtracking to a vertex $w$, if this vertex is at the top of the second stack, it indicates this vertex is the starting vertex of a strongly connected component. Then all vertices searched after this vertex belong to the same strongly connected component. So pop those vertices from the first stack to form a strongly connected component.

### Implementation

=== "C++"
    ```cpp
    int garbow(int u) {
      stack1[++p1] = u;
      stack2[++p2] = u;
      low[u] = ++dfs_clock;
      for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (!low[v])
          garbow(v);
        else if (!sccno[v])
          while (low[stack2[p2]] > low[v]) p2--;
      }
      if (stack2[p2] == u) {
        p2--;
        scc_cnt++;
        do {
          sccno[stack1[p1]] = scc_cnt;
          // all_scc[scc_cnt] ++;
        } while (stack1[p1--] != u);
      }
      return 0;
    }
    
    void find_scc(int n) {
      dfs_clock = scc_cnt = 0;
      p1 = p2 = 0;
      memset(sccno, 0, sizeof(sccno));
      memset(low, 0, sizeof(low));
      for (int i = 1; i <= n; i++)
        if (!low[i]) garbow(i);
    }
    ```

=== "Python"
    ```python
    def garbow(u):
        stack1[p1] = u
        stack2[p2] = u
        p1 = p1 + 1
        p2 = p2 + 1
        low[u] = dfs_clock
        dfs_clock = dfs_clock + 1
        i = head[u]
        while i:
            v = e[i].to
            if low[v] == False:
                garbow(v)
            elif sccno[v] == False:
                while low[stack2[p2]] > low[v]:
                    p2 = p2 - 1
        if stack2[p2] == u:
            p2 = p2 - 1
            scc_cnt = scc_cnt + 1
            while stack1[p1] != u:
                p1 = p1 - 1
                sccno[stack1[p1]] = scc_cnt
    
    
    def find_scc(n):
        dfs_clock = scc_cnt = 0
        p1 = p2 = 0
        sccno = []
        low = []
        for i in range(1, n + 1):
            if low[i] == False:
                garbow(i)
    ```

## Application

We can contract each strongly connected component in a graph into a single vertex.

Then this graph becomes a DAG, on which topological sorting and many other operations can be performed.

As a simple example, finding a path that can pass through repeated vertices, requiring the maximum number of distinct vertices visited.

## Problems

[USACO Fall/HAOI 2006 Popular Cows](https://loj.ac/problem/10091)

[POJ1236 Network of Schools](http://poj.org/problem?id=1236)