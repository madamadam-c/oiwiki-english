???+ note "Note"
    This article is translated from [e-maxx Prüfer Code](https://github.com/e-maxx-eng/e-maxx-eng/blob/master/src/graph/pruefer_code.md). Additionally, the original uses 0-indexed nodes, but this article follows the common convention of using 1-indexed nodes.

This article introduces the Prüfer sequence (Prüfer code), a method to uniquely represent a labeled tree as an integer sequence.

The Prüfer sequence can be used to prove [Cayley's formula](#cayleys-formula). We will also cover how to count the number of ways to add edges to make a graph connected.

**Note**: We do not consider trees with only 1 node.

## Prüfer Sequence

### Introduction

The Prüfer sequence can represent a labeled tree with $n$ nodes using $n-2$ integers from $[1,n]$. It can also be understood as a bijection between spanning trees of a complete graph and sequences. It is commonly used in combinatorial counting problems.

Heinz Prüfer invented this sequence in 1918 to prove [Cayley's formula](#cayleys-formula).

### Constructing a Prüfer Sequence from a Tree

The construction works as follows: each time, select the leaf node with the smallest label and remove it, then record the node it was connected to in the sequence. Repeat $n-2$ times until only two nodes remain, and the algorithm ends.

Clearly, using a heap achieves $O(n\log n)$ complexity.

???+ note "Implementation"
    === "C++"
        ```cpp
        // Code from the original, nodes are 0-indexed
        vector<vector<int>> adj;
        
        vector<int> pruefer_code() {
          int n = adj.size();
          set<int> leafs;
          vector<int> degree(n);
          vector<bool> killed(n);
          for (int i = 0; i < n; i++) {
            degree[i] = adj[i].size();
            if (degree[i] == 1) leafs.insert(i);
          }
        
          vector<int> code(n - 2);
          for (int i = 0; i < n - 2; i++) {
            int leaf = *leafs.begin();
            leafs.erase(leafs.begin());
            killed[leaf] = true;
            int v;
            for (int u : adj[leaf])
              if (!killed[u]) v = u;
            code[i] = v;
            if (--degree[v] == 1) leafs.insert(v);
          }
          return code;
        }
        ```
    
    === "Python"
        ```python
        # Nodes are 0-indexed
        adj = [[]]
        
        
        def pruefer_code():
            n = len(adj)
            leafs = set()
            degree = [0] * n
            killed = [False] * n
            for i in range(1, n):
                degree[i] = len(adj[i])
                if degree[i] == 1:
                    leafs.intersection(i)
            code = [0] * (n - 2)
            for i in range(1, n - 2):
                leaf = leafs[0]
                leafs.pop()
                killed[leaf] = True
                for u in adj[leaf]:
                    if killed[u] == False:
                        v = u
                code[i] = v
                if degree[v] == 1:
                    degree[v] = degree[v] - 1
                    leafs.intersection(v)
            return code
        ```

For example, here is the construction process of the Prüfer sequence for a tree with 7 nodes:

![Prüfer](./images/prufer1.png)

The final sequence is $2,2,3,3,2$.

Of course, there is also a linear-time construction algorithm.

### Linear-Time Construction of Prüfer Sequence

The essence of the linear-time construction is to maintain a pointer pointing to the node we are about to delete. First, observe that the number of leaf nodes is non-strictly monotonically decreasing. When we delete a leaf node, the total number of leaf nodes either stays the same or decreases by 1.

Therefore, we consider the following process: maintain a pointer $p$. Initially, $p$ points to the leaf node with the smallest label. We also maintain the degree of each node so we know when deleting a node will create new leaf nodes. The operations are:

1.  Delete the node pointed to by $p$, and check if new leaf nodes are created.
2.  If new leaf nodes are created, suppose the label is $x$, compare $p$ and $x$. If $x > p$, do nothing else; otherwise, immediately delete $x$, then check if deleting $x$ creates new leaf nodes. Repeat step 2 until no new node is created or the new node's label is $> p$.
3.  Increment pointer $p$ until it encounters an undeleted leaf node;

#### Correctness

Loop the above operations $n-2$ times to complete the sequence construction. Now let's consider the correctness of the algorithm.

$p$ is the leaf node with the smallest label. If no leaf node is created after deleting $p$, we can only look for the next leaf node; if a leaf node $x$ is created:

-   If $x > p$, then $p$ will eventually scan past it anyway, so no operation is needed;
-   If $x < p$, since $p$ was originally the leaf node with the smallest label, and $x$ is even smaller than $p$, then $x$ is the current leaf node with the smallest label, and it should be deleted first. Continue this reasoning after deleting $x$ until there are no smaller leaf nodes.

Analyzing the time complexity, each edge is visited at most once (when reducing degrees), and the pointer traverses each node at most once. Therefore, the time complexity is $O(n)$.

#### Implementation

=== "C++"
    ```cpp
    // Code from the original, also 0-indexed
    vector<vector<int>> adj;
    vector<int> parent;
    
    void dfs(int v) {
      for (int u : adj[v]) {
        if (u != parent[v]) parent[u] = v, dfs(u);
      }
    }
    
    vector<int> pruefer_code() {
      int n = adj.size();
      parent.resize(n), parent[n - 1] = -1;
      dfs(n - 1);
    
      int ptr = -1;
      vector<int> degree(n);
      for (int i = 0; i < n; i++) {
        degree[i] = adj[i].size();
        if (degree[i] == 1 && ptr == -1) ptr = i;
      }
    
      vector<int> code(n - 2);
      int leaf = ptr;
      for (int i = 0; i < n - 2; i++) {
        int next = parent[leaf];
        code[i] = next;
        if (--degree[next] == 1 && next < ptr) {
          leaf = next;
        } else {
          ptr++;
          while (degree[ptr] != 1) ptr++;
          leaf = ptr;
        }
      }
      return code;
    }
    ```

=== "Python"
    ```python
    # Also 0-indexed
    adj = [[]]
    parent = [0] * n
    
    
    def dfs(v):
        for u in adj[v]:
            if u != parent[v]:
                parent[u] = v
                dfs(u)
    
    
    def pruefer_code():
        n = len(adj)
        parent[n - 1] = -1
        dfs(n - 1)
    
        ptr = -1
        degree = [0] * n
        for i in range(0, n):
            degree[i] = len(adj[i])
            if degree[i] == 1 and ptr == -1:
                ptr = i
    
        code = [0] * (n - 2)
        leaf = ptr
        for i in range(0, n - 2):
            next = parent[leaf]
            code[i] = next
            if degree[next] == 1 and next < ptr:
                degree[next] = degree[next] - 1
                leaf = next
            else:
                ptr = ptr + 1
                while degree[ptr] != 1:
                    ptr = ptr + 1
                leaf = ptr
        return code
    ```

### Properties of Prüfer Sequences

1.  After constructing the Prüfer sequence, two nodes remain in the original tree, one of which must be the node with the largest label $n$.
2.  Each node appears in the sequence exactly (its degree minus 1) times. (Nodes that don't appear are leaf nodes.)

### Reconstructing a Tree from a Prüfer Sequence

The tree reconstruction method is similar. Based on the properties of the Prüfer sequence, we can determine the degree of each node in the original tree. Then we can also find the leaf node with the smallest label, which must be connected to the node corresponding to the first number in the Prüfer sequence. Then we reduce the degrees of both nodes by 1.

By now you might already know what to do. Each time, select the leaf node with the smallest label whose degree is 1, connect it to the current node from the Prüfer sequence, then reduce the degrees of both nodes. At the end, we have two nodes with degree 1, one of which is node $n$. Connect them. Using a heap to maintain this process, when a node's degree drops to 1, add it to the heap. This approach has $O(n\log n)$ complexity.

???+ note "Implementation"
    ```cpp
    // Code from the original
    vector<pair<int, int>> pruefer_decode(vector<int> const& code) {
      int n = code.size() + 2;
      vector<int> degree(n, 1);
      for (int i : code) degree[i]++;
    
      set<int> leaves;
      for (int i = 0; i < n; i++)
        if (degree[i] == 1) leaves.insert(i);
    
      vector<pair<int, int>> edges;
      for (int v : code) {
        int leaf = *leaves.begin();
        leaves.erase(leaves.begin());
    
        edges.emplace_back(leaf, v);
        if (--degree[v] == 1) leaves.insert(v);
      }
      edges.emplace_back(*leaves.begin(), n - 1);
      return edges;
    }
    ```

### Linear-Time Tree Reconstruction

Similar to the linear-time construction of Prüfer sequences. When reducing degrees, new leaf nodes are created, so we compare the new leaf node with the pointer $p$. If it's smaller, we prioritize it.

#### Implementation

```cpp
// Code from the original
vector<pair<int, int>> pruefer_decode(vector<int> const& code) {
  int n = code.size() + 2;
  vector<int> degree(n, 1);
  for (int i : code) degree[i]++;

  int ptr = 0;
  while (degree[ptr] != 1) ptr++;
  int leaf = ptr;

  vector<pair<int, int>> edges;
  for (int v : code) {
    edges.emplace_back(leaf, v);
    if (--degree[v] == 1 && v < ptr) {
      leaf = v;
    } else {
      ptr++;
      while (degree[ptr] != 1) ptr++;
      leaf = ptr;
    }
  }
  edges.emplace_back(leaf, n - 1);
  return edges;
}
```

Through these processes, we can understand that the Prüfer sequence establishes a bijection between labeled rooted trees.

## Cayley's Formula

The complete graph $K_n$ has $n^{n-2}$ spanning trees.

How to prove it? There are many methods, but using the Prüfer sequence is very simple. Any integer sequence of length $n-2$ with values in $[1,n]$ can bijectively correspond to a spanning tree through the Prüfer sequence. Therefore, the number of spanning trees is $n^{n-2}$.

## Number of Ways to Make a Graph Connected

The Prüfer sequence is more powerful than you might think. It can create formulas more general than [Cayley's formula](#cayleys-formula). For example, consider the following problem:

> A labeled undirected graph has $n$ vertices and $m$ edges, with $k$ connected components. We want to add $k-1$ edges to make the entire graph connected. Find the number of ways.

### Proof

Let $s_i$ denote the number of vertices in the $i$-th connected component. We consider constructing a Prüfer sequence for the $k$ connected components. Since there are many ways to connect two components, this is not an ordinary Prüfer sequence. Let $d_i$ be the degree of the $i$-th connected component. Since the sum of degrees equals twice the number of edges, we have $\sum_{i=1}^kd_i=2k-2$. Then for a given $d$ sequence, the number of ways to construct a Prüfer sequence is

$$
\binom{k-2}{d_1-1,d_2-1,\cdots,d_k-1}=\frac{(k-2)!}{(d_1-1)!(d_2-1)!\cdots(d_k-1)!}
$$

For the $i$-th connected component, there are ${s_i}^{d_i}$ ways to connect it. Therefore, for a given $d$ sequence, the number of ways to make the graph connected is

$$
\binom{k-2}{d_1-1,d_2-1,\cdots,d_k-1}\cdot \prod_{i=1}^k{s_i}^{d_i}
$$

Now we need to enumerate the $d$ sequence, and the expression becomes

$$
\sum_{d_i\ge 1，\sum_{i=1}^kd_i=2k-2}\binom{k-2}{d_1-1,d_2-1,\cdots,d_k-1}\cdot \prod_{i=1}^k{s_i}^{d_i}
$$

This is a very unwieldy expression. But don't panic! We have the multinomial theorem:

$$
(x_1 + \dots + x_m)^p = \sum_{\substack{c_i \ge 0 ,\  \sum_{i=1}^m c_i = p}} \binom{p}{c_1, c_2, \cdots ,c_m}\cdot \prod_{i=1}^m{x_i}^{c_i}
$$

Let $e_i=d_i-1$, then $\sum_{i=1}^ke_i=k-2$. Substituting into the original expression:

$$
\sum_{e_i\ge 0，\sum_{i=1}^ke_i=k-2}\binom{k-2}{e_1,e_2,\cdots,e_k}\cdot \prod_{i=1}^k{s_i}^{e_i+1}
$$

Simplifying gives

$$
(s_1+s_2+\cdots+s_k)^{k-2}\cdot \prod_{i=1}^ks_i
$$

That is,

$$
n^{k-2}\cdot\prod_{i=1}^ks_i
$$

as the answer.

## Practice Problems

-   [Luogu P6086【Template】Prüfer Sequence](https://www.luogu.com.cn/problem/P6086) (Template problem)
-   [Luogu P11039【MX-X3-T6】「RiOI-4」TECHNOPOLIS 2085](https://www.luogu.com.cn/problem/P11039)
-   [UVa #10843 - Anne's game](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=20&page=show_problem&problem=1784)
-   [Timus #1069 - Prufer Code](http://acm.timus.ru/problem.aspx?space=1&num=1069)
-   [Codeforces - Clues](http://codeforces.com/contest/156/problem/D)
-   [Topcoder - TheCitiesAndRoadsDivTwo](https://archive.topcoder.com/ProblemStatement/pm/10774)
