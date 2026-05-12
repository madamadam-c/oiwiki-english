author: GitPinkRabbit, Early0v0, Backl1ght, mcendu, ksyx, iamtwz, Xeonacid, kenlig, Menci, Enter-tainer, CCXXXI, hcx2012Git

Before reading the following content, make sure you understand the [graph theory concepts](./concept.md) section.

Related reading: [Articulation Points and Bridges](./cut.md).

## Introduction

As is well known, trees (or forests) have good properties and are easy to maintain using many common data structures.

General graphs, however, do not have such nice properties. Fortunately, sometimes we can transform problems on general graphs into tree problems.

The Block-forest (also called Round-square tree)[^ref1] is a method to transform a graph into a tree. This article will introduce the construction, properties, and some applications of the block-forest tree.

Due to space limitations, some conclusions in this article are not proved. Readers can understand or prove them on their own.

## Definitions

The block-forest tree was originally a tool for processing "cactus graphs" (undirected graphs where each edge belongs to at most one simple cycle). However, by exploring its further properties, we can sometimes use it on general undirected graphs.

To introduce the block-forest tree, we first need to introduce **biconnected components** (also called vertex biconnected components).

One definition of a **biconnected graph** is: between any two distinct vertices in the graph, there exist at least two vertex-disjoint paths.
Vertex-disjoint means that the paths have no vertices in common (simple paths), and the two paths have empty intersection (of course, the paths must both pass through the starting and ending vertices, which are not considered).

It can be seen that graphs with only one vertex are difficult to define as biconnected. Here we do not consider graphs with 1 vertex.

An almost equivalent definition is: a graph without cut vertices.
This definition only fails when the graph has exactly two vertices connected by one edge. It has no cut vertex, but we cannot find two vertex-disjoint paths because there is only one path.
(We can also interpret that the single path can be counted twice, and indeed there is no intersection since no other vertices are traversed.)

Although the original definition is indeed the former, for convenience, we adopt the latter as the definition of a biconnected graph.

A **biconnected component** of a graph is a **maximally biconnected subgraph**.
Unlike strongly connected components, a vertex may belong to multiple biconnected components, but an edge belongs to exactly one biconnected component (if we use the first definition, an edge might not belong to any biconnected component).

In a block-forest tree, each original vertex corresponds to a **circle node** (or round node), and each biconnected component corresponds to a **square node**.  
Therefore, there are $n+c$ nodes in total, where $n$ is the number of vertices in the original graph and $c$ is the number of biconnected components.

For each biconnected component, its corresponding square node connects to every vertex in that biconnected component.
Each biconnected component forms a "star" (multiple square nodes connecting to a central vertex), and multiple "stars" are connected through cut vertices of the original graph (because cut vertices separate biconnected components).

Clearly, every edge in a block-forest tree connects a circle node and a square node.

The following diagram shows the biconnected components and the block-forest tree structure of a graph.[^ref2]

![](./images/block-forest1.svg)![](./images/block-forest2.svg)![](./images/block-forest3.svg)

The number of nodes in a block-forest tree is less than $2n$, because the number of cut vertices is less than $n$. Please note that various array sizes should be doubled.

In fact, if the original graph is connected, the "block-forest tree" is indeed a tree. If the original graph has $k$ connected components, its block-forest tree will form a forest of $k$ trees.

If a connected component in the original graph consists of only one vertex, specific analysis is needed. We do not consider isolated vertices in the following discussion.

## Construction

For a given graph, how do we construct its block-forest tree? First, note that if the graph is not connected, we can split it into connected components. So we only consider connected graphs.

Since the block-forest tree is based on biconnected components, and biconnected components are based on cut vertices, we only need to use a method similar to finding cut vertices.

The common algorithm for finding cut vertices is Tarjan's algorithm. If you know it, understanding the following content will be easy. If you don't, that's fine.

We skip Tarjan's algorithm for finding cut vertices and directly introduce the algorithm used for block-forest trees (which is actually a variant of Tarjan):

Perform a DFS on the graph, using two key arrays `dfn` and `low` (similar to Tarjan).

`dfn[u]` stores the DFS order of vertex $u$, i.e., the order in which $u$ is first visited.
`low[u]` stores the minimum DFS order that some vertex $v$ in the DFS subtree of $u$ can reach using **at most one back edge or tree edge to the parent**.
If you haven't heard of Tarjan's algorithm, this might be a bit difficult to understand. Let me give an example:

![](./images/block-forest4.svg)

(You can see this graph is equivalent to the one in the diagram above.)  
Here, tree edges are drawn as straight lines from top to bottom, and back edges are drawn as curves from bottom to top. The node numbers are their DFS orders.

Then the `low` array is as follows:

|        $i$        | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ | $7$ | $8$ | $9$ |
| :---------------: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| $\mathrm{low}[i]$ | $1$ | $1$ | $1$ | $3$ | $3$ | $4$ | $3$ | $3$ | $7$ |

It's not difficult to understand. Note that the `low` of 9 is 7, which differs from some implementations for finding cut vertices. For convenience, we allow going up through the parent edge, but the main idea is the same.

We can easily write a DFS function to compute `dfn` and `low` (initially, set all `dfn` to zero):

???+ note "Implementation"
    === "C++"
        ```cpp
        void Tarjan(int u) {
          low[u] = dfn[u] = ++dfc;                // low is initialized to current node's dfn
          for (int v : G[u]) {                    // iterate through adjacent nodes of u
            if (!dfn[v]) {                        // if not visited
              Tarjan(v);                          // recursive call
              low[u] = std::min(low[u], low[v]);  // take min with low of unvisited nodes
            } else
              low[u] = std::min(low[u], dfn[v]);  // take min with dfn of visited nodes
          }
        }
        ```
    
    === "Python"
        ```python
        def Tarjan(u):
            low[u] = dfn[u] = dfc  # low is initialized to current node's dfn
            dfc = dfc + 1
            for v in G[u]:  # iterate through adjacent nodes of u
                if dfn[v] == False:  # if not visited
                    Tarjan(v)  # recursive call
                    low[u] = min(low[u], low[v])  # take min with low of unvisited nodes
                else:
                    low[u] = min(low[u], dfn[v])  # take min with dfn of visited nodes
        ```

Next, we consider the relationship between biconnected components, the DFS tree, and these two arrays.

It can be observed that each biconnected component is a connected subtree in the DFS tree and contains at least two vertices. In particular, the topmost node has only one child.

It can also be observed that each tree edge belongs to exactly one biconnected component.

We consider the topmost node $u$ of a biconnected component in the DFS tree. We determine the biconnected component at $u$, because $u$'s subtree contains the information of the entire biconnected component.

Since there are at least two vertices, consider the next vertex $v$ in this biconnected component. Then there is a tree edge between $u$ and $v$.

It is not hard to see that at this point, we must have $\mathrm{low}[v]=\mathrm{dfn}[u]$.
More precisely, for a tree edge $u\to v$, $u$ and $v$ are in the same biconnected component, and $u$ is the shallowest node in this biconnected component **if and only if** $\mathrm{low}[v]=\mathrm{dfn}[u]$.

Therefore, we can identify where biconnected components exist during the DFS process, but we cannot yet accurately determine the set of vertices in a biconnected component.

This is not difficult to handle. We can maintain a stack during DFS, storing vertices whose biconnected component membership has not yet been determined (possibly multiple).

When we find a biconnected component, all vertices in it except $u$ are at the top of the stack. We just need to pop from the stack until we pop $v$.

Of course, we can process the popped vertices simultaneously by connecting them to the newly created square node. Finally, we also connect $u$ to the square node.

This naturally completes the construction of the block-forest tree. We can label square nodes with integers starting from $n+1$, so that circle nodes and square nodes can be easily distinguished.

This section might not be entirely clear. Below is a piece of code with detailed comments and helpful output statements, along with a sample input. Readers are encouraged to copy the code and practice understanding it. After all, code is the best way to understand (don't forget to enable C++11).

???+ note "Implementation"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <vector>
    
    constexpr int MN = 100005;
    
    int N, M, cnt;
    std::vector<int> G[MN], T[MN * 2];
    
    int dfn[MN], low[MN], dfc;
    int stk[MN], tp;
    
    void Tarjan(int u) {
      printf("  Enter : #%d\n", u);
      low[u] = dfn[u] = ++dfc;                // low is initialized to current node's dfn
      stk[++tp] = u;                          // push onto stack
      for (int v : G[u]) {                    // iterate through adjacent nodes of u
        if (!dfn[v]) {                        // if not visited
          Tarjan(v);                          // recursive call
          low[u] = std::min(low[u], low[v]);  // take min with low of unvisited nodes
          if (low[v] == dfn[u]) {  // indicates finding a new BCC with u as root
            ++cnt;                 // increment square node count
            printf("  Found a New BCC #%d.\n", cnt - N);
            // Pop vertices except u from stack and connect to square node in block-forest tree
            for (int x = 0; x != v; --tp) {
              x = stk[tp];
              T[cnt].push_back(x);
              T[x].push_back(cnt);
              printf("    BCC #%d has vertex #%d\n", cnt - N, x);
            }
            // Note: u itself needs to be connected (but not popped from stack)
            T[cnt].push_back(u);
            T[u].push_back(cnt);
            printf("    BCC #%d has vertex #%d\n", cnt - N, u);
          }
        } else
          low[u] = std::min(low[u], dfn[v]);  // take min with dfn of visited nodes
      }
      printf("  Exit : #%d : low = %d\n", u, low[u]);
      printf("  Stack:\n    ");
      for (int i = 1; i <= tp; ++i) printf("%d, ", stk[i]);
      puts("");
    }
    
    int main() {
      scanf("%d%d", &N, &M);
      cnt = N;  // BCC / square node labels start from N
      for (int i = 1; i <= M; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);  // add bidirectional edge
        G[v].push_back(u);
      }
      // handle disconnected graphs
      for (int u = 1; u <= N; ++u)
        if (!dfn[u]) Tarjan(u), --tp;
      // note: when exiting Tarjan, there's still one element (root) on the stack, pop it
      return 0;
    }
    ```

A test case:

```text
13 15
1 2
2 3
1 3
3 4
3 5
4 5
5 6
4 6
3 7
3 8
7 8
7 9
10 11
11 10
11 12
```

The corresponding graph for this example (includes parallel edges and isolated vertices):

![](./images/block-forest5.svg)

## Example Problems

We will discuss some example problems that can be solved using block-forest trees.

???+ note "[APIO2018 Ironman Three](https://loj.ac/p/2587)"
    ??? note "Problem Summary"
        Given a simple undirected graph, count how many ordered triples $\langle s, c, f \rangle$ ($s, c, f$ are all distinct) such that there exists a simple path from $s$ to $f$ passing through $c$.
    
    ??? note "Solution"
        When talking about simple paths, we must mention a good property of biconnected components: for two vertices in the same biconnected component, the union of simple paths between them exactly equals this biconnected component.
        That is, for any two distinct vertices $u, v$ in the same biconnected component, and any given vertex $w$ in that biconnected component, there must exist a simple path from $u$ to $v$ passing through $w$.
        
        Proof of this property:
        
        -   Obviously, if a simple path leaves a biconnected component, it cannot return to that component, otherwise it would conflict with the definition of biconnected components.
        -   So we only need to prove that in a biconnected graph, for any three distinct vertices $u, v, c$, there exists a simple path from $u$ to $v$ passing through $c$.
        -   First, exclude the case where the graph has 2 vertices. It satisfies the property, but we cannot select 3 distinct vertices.
        -   For the remaining cases, consider building a network flow model. Connect a source to $c$ with capacity 2, and connect $u$ and $v$ to the sink with capacity 1 each.
        -   For each bidirectional edge $\langle x,y\rangle$ in the original graph, add an edge from $x$ to $y$ with capacity 1 and an edge from $y$ to $x$ with capacity 1.
        -   Finally, assign capacity 1 to every vertex except the source, sink, and $c$. This can be done by vertex splitting.
        -   Since the edge from source to $c$ has capacity 2, if the maximum flow of this network is 2, then there must exist a path passing through $c$.
        -   Consider the max-flow min-cut theorem. Obviously, the minimum cut is less than or equal to 2. Now we need to prove the minimum cut is greater than 1.
        -   This is equivalent to proving that cutting any edge with capacity 1 cannot disconnect the source and sink.
        -   Consider cutting the vertex connecting $u$ or $v$ to the sink. According to the first definition of biconnected components, there must exist a simple path from $c$ to the other uncut vertex.
        -   Consider cutting an edge formed by vertex splitting. This is equivalent to deleting a vertex. According to the second definition of biconnected components, the remaining graph is still connected.
        -   Consider cutting an edge originally from the graph. This is equivalent to deleting an edge, which is weaker than deleting a vertex. Obviously, a path exists.
        -   Therefore, we have proved the minimum cut is greater than 1, i.e., the maximum flow equals 2. QED.
        
        What does this conclusion tell us? It tells us: consider the path between two circle nodes on the block-forest tree. The set of circle nodes adjacent to the square nodes on that path equals the set of vertices on simple paths between the two original vertices.
        
        Back to the problem, fix $s$ and $f$. The number of valid $c$ is clearly equal to the number of vertices in the union of simple paths between $s$ and $f$ minus 2 (excluding $s$ and $f$ themselves).
        
        After constructing the block-forest tree of the original graph, the number of vertices on simple paths between two vertices is related to the number of square nodes (biconnected components) and circle nodes on the path between them on the block-forest tree.
        
        Next is a common technique for block-forest trees: assign appropriate weights to vertices during path counting.
        In this problem, each square node's weight is the size of its corresponding biconnected component, and each circle node's weight is $-1$.
        
        After such weight assignment, the sum of vertex weights on the path between two circle nodes on the block-forest tree exactly equals the size of the union of simple paths between the original two vertices minus 2.
        
        The problem is transformed into counting $\sum$ path weights between all pairs of circle nodes on the block-forest tree.
        
        From another perspective, we can count the contribution of each vertex to the answer, i.e., weight times the number of paths passing through it. This can be computed with a simple tree DP.
        
        Finally, don't forget to handle the case where the graph is not connected. Below is the corresponding code:
    
    ??? note "Reference Code"
        ```cpp
        --8<-- "docs/graph/code/block-forest/block-forest_1.cpp"
        ```
    
    By the way, the answer for the test case above on this problem is $212$.

???+ note "[Codeforces #487 E. Tourists](https://codeforces.com/contest/487/problem/E)"
    ??? note "Problem Summary"
        Given a simple undirected connected graph, support two types of operations:
        
        1.  Update the weight of a vertex.
        
        2.  Query the minimum vertex weight on all simple paths between two vertices.
    
    ??? note "Solution"
        Similarly, we construct the block-forest tree of the original graph. Let the weight of a square node be the minimum of the weights of its adjacent circle nodes. The problem becomes finding the minimum value on a path.
        
        Path minimum can be maintained using tree decomposition and segment trees. But what about updates?
        
        When updating a circle node's weight, we need to update all adjacent square nodes. This can easily be $O(n)$ updates.
        
        Here we use the property that the block-forest tree is a tree. Let the weight of a square node be the minimum of its child circle nodes' weights. Then during an update, we only need to modify the parent square node.
        
        For maintaining square nodes, we only need to open a `multiset` for each square node to maintain the weight set.
        
        Note that if the LCA is a square node during a query, we also need to query the weight of its parent circle node.
        
        Note: The number of nodes in the block-forest tree should be twice that of the original graph; otherwise, array out of bounds will occur.
    
    ??? note "Reference Code"
        ```cpp
        --8<-- "docs/graph/code/block-forest/block-forest_2.cpp"
        ```

???+ note "[SDOI2018 Strategic Game](https://loj.ac/p/2562)"
    ??? note "Problem Summary"
        Given a simple undirected connected graph. There are $q$ queries:
        
        Each query gives a vertex set $S$ ($2 \le |S| \le n$), and asks how many vertices $u$ satisfy $u \notin S$ and after removing $u$, the vertices in $S$ are not all in one connected component.
        
        Multiple test cases per problem.
    
    ??? note "Solution"
        First, construct the block-forest tree. Then the problem becomes: find the number of circle nodes in the connected subgraph of the block-forest tree corresponding to $S$ minus $|S|$.
        
        How to compute the number of circle nodes in a connected subgraph? One method:
        
        Put the weight of each circle node on the edge connecting it to its parent square node. The problem becomes finding the sum of edge weights. This problem can be referenced by a solution to [SDOI2015 Treasure Hunt](https://loj.ac/p/2182).
        That is, sort the vertices in $S$ by DFS order, compute the sum of distances between consecutive vertices (including the distance between the last and first), and the answer is half of that sum, because each edge is traversed exactly twice.
        
        Finally, if the shallowest node in the subgraph is a circle node, add 1 to the answer, because we haven't counted it.
        
        Since there are multiple test cases, remember to reinitialize the arrays.
    
    ??? note "Reference Code"
        ```cpp
        --8<-- "docs/graph/code/block-forest/block-forest_3.cpp"
        ```

## Practice Problems

-   [UVa 1464 Traffic Real Time Query](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4210)
-   [Luogu P4320 Road Meeting](https://www.luogu.com.cn/problem/P4320)
-   [Luogu P10517 National Planning](https://www.luogu.com.cn/problem/P10517)

## External Links

immortalCO, [Block-forest Tree - A Powerful Tool for Processing Cactus](https://immortalco.blog.uoj.ac/blog/1955), Universal OJ.

## References and Notes

[^ref1]: In 2017, Chen Junkun defined and named the block-forest tree structure in his IOI2017 China national team paper "Problem Report and Extensions of 'Magical Subgraphs'".

[^ref2]: Chen Junkun, "Ordinary Block-forest Trees and Magical (~~Dynamic~~) Dynamic Programming", NOI2018 Winter Camp, Page 4.
