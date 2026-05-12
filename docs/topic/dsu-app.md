author: sshwy

DSU and Kruskal reconstruction trees use very similar ways of thinking: both can be used to handle connectivity-related problems. This article introduces applications of DSU ideas through example problems.

## A

???+ note "A"
    There are $n$ vertices, all initially isolated.
    
    Then there are $m$ edge-addition operations. The $i$-th operation adds an undirected edge between $a_i$ and $b_i$. Let $L(i,j)$ denote that vertices $i$ and $j$ first become connected after the $L(i,j)$-th operation.
    
    After all $m$ operations, compute $\sum_{i=1}^n\sum_{j=i+1}^nL(i,j)$.

This is a basic DSU application. Use DSU to record subtree sizes. Consider the contribution of each operation. If in the $i$-th operation, $a_i$ and $b_i$ belong to two different subtrees, merge the two subtrees, multiply the product of their subtree sizes by $i$, and add it to the answer. The time complexity is $O(n\alpha(n))$.

## B

???+ note "B"
    There are $n$ vertices, all initially isolated.
    
    Then there are $m$ edge-addition operations. The $i$-th operation adds an undirected edge between $a_i$ and $b_i$.
    
    Then there are $q$ queries. The $i$-th query asks after which operation $u_i$ and $v_i$ first become connected.

During DSU merges, record a "DSU spanning tree". That is, if in the $i$-th operation, $a_i$ and $b_i$ belong to two different subtrees, include the edge $(a_i,b_i)$ in the spanning tree with edge weight $i$. Then a query asks for the maximum edge weight on the path from $u$ to $v$, which can be maintained with binary lifting on trees or heavy-light decomposition. The time complexity is $O(n\log n)$.

Another method is to maintain a Kruskal reconstruction tree. Its essence is the same as the DSU spanning tree, and the complexity is also the same.

## C

???+ note "C"
    There are $n$ vertices, all initially isolated.
    
    Then there are $m$ edge-addition operations. The $i$-th operation adds an undirected edge between $a_i$ and $b_i$.
    
    Then there are $q$ queries. The $i$-th query asks for the size of the connected component containing vertex $x_i$ after the $t_i$-th operation.

Offline algorithm: sort the queries by $t_i$ in increasing order. While adding edges, use DSU to answer the queries along the way. The time complexity is $O(q\log q+(n+q)\alpha(n))$.

Online algorithm: the online algorithm for this problem can only use a Kruskal reconstruction tree. The difference between a Kruskal reconstruction tree and DSU is: if in the $i$-th operation, $a_i$ and $b_i$ belong to two different subtrees, Kruskal creates a new node $u$, then connects the root of the subtree containing $a_i$ and the root of the subtree containing $b_i$ to $u$, as the two children of $u$. Suppose the vertex weight of $u$ is $i$. For the initial $n$ vertices, the vertex weight is $0$.

For a query, we only need to find the largest connected block containing $x_i$ in the reconstruction tree such that the maximum vertex weight in the block is at most $t_i$. The answer is the number of nodes with vertex weight $0$ in this connected block, i.e. the number of leaf nodes.

Since operation numbers are increasing, the weight of a parent in the reconstruction tree is always greater than the weight of its children. This means we can use binary lifting on the path from $x_i$ to the root to find the highest node whose vertex weight does not exceed $t_i$. This gives the answer. The time complexity is $O(n\log n)$.

## D

???+ note "D"
    Given length $n$ and a 01 sequence $a_1,\ldots,a_n$, initially all $0$, perform $m$ operations:
    
    -   Set $a_x=1$;
    -   Find the first position from the left among $a_x,a_{x+1},\ldots,a_n$ whose value is $0$.

Build a DSU. Let $f_i$ denote, among $a_i,a_{i+1},\ldots,a_n$, the first position with value $0$. Initially, $f_i=i$.

For an operation $a_x=1$, if $a_x$ was already $1$, do nothing. Otherwise, set $f_x=f_{x+1}$.

The time complexity is $O(n\log n)$. If union by rank is used, the implementation is more complicated but still feasible; in that case the time complexity can be $O(n\alpha(n))$.

## E

???+ note "E"
    Given length $n$ and three positive integer sequences $a$, $b$, and $c$. Enumerate $1\le i\le j\le n$, and find the maximum value of $a_i\cdot b_j\cdot \min_{i\le k\le j}c_k$.

There are many solutions to this problem; here we focus on the DSU idea. Consider $c_k$ in descending order of value. This is equivalent to adding a point at $k$, then merging it with the connected components containing positions $k-1$ and $k+1$ (if those positions already have points). Record the maximum value of $a$ and the maximum value of $b$ in each connected component, and update the answer during merges. The time complexity is $O(n\log n)$.

## F

???+ note "F"
    Given a tree with $n$ vertices, then perform $m$ operations:
    
    -   Add an edge from $a_i$ to $b_i$.
    -   Query whether there are at least two edge-disjoint paths between vertices $u_i$ and $v_i$.

The query can be transformed into: determine whether $u_i$ and $v_i$ lie on the same simple cycle. Following the idea of contracting biconnected components, each time we add an edge between $a_i$ and $b_i$, we can contract the vertices on the tree path from $a_i$ to $b_i$ together. If the tree paths corresponding to two edges $(a_i,b_i)$ and $(a_j,b_j)$ intersect, then these two edges will be contracted together.

In other words, an edge-addition operation can be understood as covering the edges on the tree path from $a_i$ to $b_i$ once. The query becomes: determine whether there is any uncovered edge on the path from $u_i$ to $v_i$. If not, then $u_i$ and $v_i$ belong to the same edge-biconnected component, hence to the same simple cycle.

Use DSU to maintain this. Root the tree, and let $f_i$ denote the first uncovered edge on the path from $i$ to the root. For each edge-addition operation, brute-force jump along the DSU. After covering an edge, merge the $f$ of the node corresponding to that edge with its parent. Thus each edge is covered at most once, and the total complexity is $O(n\log n)$. Using union by rank in the DSU can also achieve $O(n\alpha(n))$.

This maintenance method is similar to the tree version of problem D.

## G

???+ note "G"
    An undirected graph $G$ has $n$ vertices and initially has no edges.
    
    Then there are $m$ edge-addition operations. The $i$-th operation adds an undirected edge between $a_i$ and $b_i$.
    
    After each operation, output the number of bridges in the graph.
    
    For an edge of $G$, namely $(x,y)$, if deleting it increases the number of connected components, then $(x,y)$ is called a bridge.
    
    The problem is forced online.

This problem tests understanding of DSU properties. Use DSU to maintain connectivity. For the edge-biconnected-component tree, maintain a rooted tree, and let $p_i$ denote the parent of node $i$. This is a DSU without path compression.

If in the $i$-th operation, $a_i$ and $b_i$ belong to the same connected component, then we need to contract the vertices on the path from $a_i$ to $b_i$ in the edge-biconnected-component tree. This can be maintained with DSU. Each contraction reduces the number of edge-biconnected components by $1$, and this can happen at most $n-1$ times, so the DSU complexity of the contraction part is $O(n\alpha(n))$.

To contract vertices, first find the LCA of $a_i$ and $b_i$ in the edge-biconnected-component tree. We can maintain a marker array for this. Starting from $a_i$ and $b_i$, alternately jump upward through ancestors one by one and mark the visited vertices. Once we jump to a vertex that has already been marked, that vertex is the LCA of $a_i$ and $b_i$. The complexity of this algorithm is linear in the path length from $a_i$ to $b_i$, which is acceptable.

If $a_i$ and $b_i$ belong to two different connected components, merge the two components and increase the number of bridges by $1$. At this point, we need to connect the two edge-biconnected-component trees, i.e. add an edge from $a_i$ to $b_i$. Therefore, reroot one of the two trees and attach it to the other. Here we use the idea of heuristic merging: reroot the tree with fewer nodes. The total complexity of this is $O(n\log n)$.

In summary, the total complexity of this algorithm is $O(n\log n+m\log n)$.

## Summary

DSU and Kruskal reconstruction trees have many common points, and the DSU optimization union by rank is an application of heuristic merging. Therefore, flexible use of DSU can conveniently handle many graph-theory problems related to connectivity.

**Part of this page is translated from the blog post [Поиск мостов в режиме онлайн](http://e-maxx.ru/algo/bridge_searching_online) and its English translation [Finding Bridges Online](https://cp-algorithms.com/graph/bridge-searching-online.html). The Russian version is licensed as Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
