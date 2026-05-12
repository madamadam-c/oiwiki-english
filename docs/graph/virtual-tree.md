author: HeRaNO, Ir1d, konnyakuxzy, ksyx, Xeonacid, konnyakuxzy, greyqz, sshwy, y-kx-b

## Introduction

???+ note "[SDOI2011 Consumption War](https://www.luogu.com.cn/problem/P2495)"
    In a war, the battlefield consists of $n$ islands and $n-1$ bridges, ensuring there is exactly one path between any two islands. Our army has discovered that the enemy headquarters is on island number $1$, and they no longer have enough energy to sustain the battle—our victory is within reach. It is known that there are abundant energy resources on other $k$ islands. To prevent the enemy from obtaining these resources, our mission is to destroy some bridges so that the enemy cannot reach any energy-rich islands. Since different bridges have different materials and structures, destroying different bridges has different costs. Our army hopes to minimize the total cost while achieving the objective.

    The intelligence department also discovered that the enemy has a mysterious machine. Even after we cut off all energy sources, they can still use that machine. The effect of the machine not only repairs all bridges we destroyed but also randomly redistributes resources (but it can be guaranteed that resources will not be distributed to island $1$). However, the intelligence department also discovered that this machine can only be used $m$ times, so we only need to complete each task.

    For all data, $2\le n\le 2.5\times 10^5,1\le m\le 5\times 10^5,\sum k_i\le 5\times 10^5,1\le k_i\le n-1$.

### Naive Approach

For the problem above, it's not hard to find that if the tree has few nodes, we can directly run DP.

First, we call the nodes selected in a query — **"key nodes"**.

Let $Dp(i)$ denote the **minimum cost** to disconnect $i$ from any key node in its subtree.

Let $w(a,b)$ denote the weight of the edge between $a$ and $b$.

Then enumerate children $v$ of $i$:

-   If $v$ is not a key node: $Dp(i)=Dp(i) + \min \{Dp(v),w(i,v)\}$;
-   If $v$ is a key node: $Dp(i)=Dp(i) + w(i,v)$.

Great, this gives us an $O(nq)$ solution.

Sounds interesting.

### Optimized Approach

It's not hard to find that many nodes are actually useless. Take the following figure as an example:

![vtree-1](images/vtree-tree.svg)

If the key nodes we select are:

![vtree-2](images/vtree-key-vertex.svg)

In the figure, only the two red nodes are **key nodes**, and all other nodes are "non-key nodes".

For this problem, we only need to ensure that the red nodes cannot reach node $1$.

Through visual observation, we can conclude that the right subtree of node $1$ (though there may be multiple subtrees in practice, here there are only two, so we'll call it that for now) has no red nodes at all, **so there's no need to DP on it**.

Observing the conditions given in the problem, the total number of red nodes (key nodes) is of the same order as $n$. That is, in a single query, the red nodes are very sparse relative to the entire tree. So if we can make the complexity depend on the total number of red nodes, that would be ideal.

Therefore, we need to **condense information, compressing a large tree into a small tree**.

## Virtual Tree

This leads us to the concept of the **"Virtual Tree"**.

Let's first intuitively understand what a virtual tree looks like.

In the following figures, the red nodes are the key nodes we selected. Both red and black nodes are nodes in the virtual tree. The black edges are edges in the virtual tree.

![vtree-3](images/vtree-vtree1.svg)

![vtree-4](images/vtree-vtree2.svg)

![vtree-5](images/vtree-vtree3.svg)

![vtree-6](images/vtree-vtree4.svg)

Since the LCA of any two key nodes also needs to preserve important information, we need to preserve their LCAs. Therefore, a virtual tree does not necessarily contain only key nodes.

It is not hard to find that the ancestor-descendant relationship in the virtual tree does not change. (That is, there won't be cases where $a$ was originally an ancestor of $b$ but later $a$ becomes a descendant of $b$, etc.)

But we cannot $O(k^2)$ brute-force enumerate LCAs, so it's not hard to think of — first sort the key nodes by DFS order, then after sorting, for any two adjacent key nodes (adjacent means the absolute difference of indices in the sorted sequence is 1), compute their LCA and add it to the virtual tree.

Our urgent task is how to construct the virtual tree.

Before proposing a solution, let's confirm a fact — in a virtual tree, as long as the ancestor-descendant relationship is not changed, we can freely add nodes.

That is, if we want, we can add all nodes from the original tree to the virtual tree, which won't cause WA (though it will cause TLE).

Therefore, for convenience, we can first add node $1$ to the virtual tree, and it won't affect the answer.

### First Construction Method: Double Sort + LCA Edge Connection

Since the LCA of multiple nodes may be the same, we cannot add it to the virtual tree multiple times.

A very intuitive method is:

-   Sort key nodes by DFS order;
-   Traverse once, compute LCA for any two adjacent key nodes, and deduplicate;
-   Then build the tree according to the ancestor-descendant relationship in the original tree.

In implementation, on the **key node sequence**, enumerate **adjacent pairs**, compute their LCA for both and add to sequence $A$.

Due to the property of DFS order, sequence $A$ now contains **all nodes in the virtual tree**, but there may be duplicates.

So we sort sequence $A$ by DFS order **in ascending order and deduplicate**.

Finally, on sequence $A$, enumerate **adjacent** node IDs $x,y$, compute their LCA and connect $\operatorname{LCA}(x,y)$ and $y$. The virtual tree is now constructed.

Why does connecting $\operatorname{LCA}(x,y)$ and $y$ achieve no omission and no repetition?

??? note "Proof"
    If $x$ is an ancestor of $y$, then connect $x$ directly to $y$. Since DFS order ensures that $x$ and $y$ have adjacent DFS orders, there is no key node on the path from $x$ to $y$.
    
    If $x$ is not an ancestor of $y$, then treat $\operatorname{LCA}(x,y)$ as $y$'s ancestor. According to the first case, it can be proven that there is no key node on the path from $\operatorname{LCA}(x,y)$ to $y$.
    
    So connecting $\operatorname{LCA}(x,y)$ and $y$ neither omits nor repeats.
    
    Also, will it matter that the first node is not connected by any node? Since the first node must be the root of this tree, it won't matter. So the total number of edges is $m-1$.

Since at least two real nodes are needed to summon one virtual node, plus one root node, the number of nodes in the virtual tree is twice the number of real nodes.

Time complexity $O(m\log n)$, where $m$ is the number of key nodes and $n$ is the total number of nodes.

#### Implementation

```cpp
int dfn[MAXN];
int h[MAXN], m, a[MAXN], len;  // Store key nodes

bool cmp(int x, int y) {
  return dfn[x] < dfn[y];  // Sort by dfs order
}

void build_virtual_tree() {
  sort(h + 1, h + m + 1, cmp);  // Sort key nodes by dfs order
  for (int i = 1; i < m; ++i) {
    a[++len] = h[i];
    a[++len] = lca(h[i], h[i + 1]);  // Insert lca
  }
  a[++len] = h[m];
  sort(a + 1, a + len + 1, cmp);  // Sort all virtual tree nodes by dfs order
  len = unique(a + 1, a + len + 1) - a - 1;  // Deduplicate
  for (int i = 1, lc; i < len; ++i) {
    lc = lca(a[i], a[i + 1]);
    conn(lc, a[i + 1]);  // Connect edges, if edge weights exist, use distance(lc,a[i+1])
  }
}
```

In fact, this is sufficient to construct a virtual tree.

### Second Construction Method: Using Monotonic Stack

How to construct a virtual tree using a monotonic stack?

First, we need to clarify a purpose — we use the monotonic stack to maintain a chain on the virtual tree.

That is, two adjacent nodes in the stack are also adjacent on the virtual tree, and the stack is monotonically increasing from bottom to top (in terms of DFS order of nodes in the stack). In simple terms, the parent of a node is the node below it in the stack.

First, add node $1$ to the stack.

Then add key nodes in order of increasing DFS order.

If the LCA of the current node and the top node of the stack is the top node itself, then they are on the same chain. So just push the current node onto the stack.

![vtree-7](./images/vtree-add1.svg)

If the LCA of the current node and the top node of the stack is not the top node:

![vtree-8](./images/vtree-add2.svg)

At this time, the chain maintained by the current monotonic stack is:

![vtree-9](./images/vtree-add3.svg)

And we need to change the chain to:

![vtree-10](./images/vtree-add4.svg)

So we pop the nodes marked with dashed lines from the stack. Don't forget to connect edges to their parent in the virtual tree before popping.

![vtree-11](./images/vtree-add5.svg)

If after popping, the top of the stack is not the LCA, we need to push the LCA onto the stack.

Then push the current node onto the stack.

Below is a concrete example. Suppose we want to build a virtual tree for nodes 4, 6, and 7 of the following tree:

![vtree-12](./images/vtree-construction1.svg)

The steps are as follows:

-   Sort the 3 key nodes $6,4,7$ by DFS order, obtaining the sequence $[4,6,7]$.
-   Push $1$ onto the stack.

![vtree-13](./images/vtree-construction2.svg)

We use red nodes to represent nodes in the stack, and cyan nodes to represent nodes popped from the stack.

-   Take the first element in the sequence as the current node, which is $4$. Take the top element of the stack, which is $1$. Compute the LCA of $1$ and $4$: $LCA(1,4)=1$.
-   Found $LCA(1,4)=$ the top element, indicating they are on the same chain of the virtual tree. So directly push the current node $4$ onto the stack. Current stack: $4,1$.

![vtree-14](./images/vtree-construction3.svg)

-   Take the second element in the sequence as the current node, which is $6$. Take the top element of the stack, which is $4$. Compute the LCA of $6$ and $4$: $LCA(6,4)=1$.
-   Found $LCA(6,4)\neq$ the top element, enter the judgment phase.
-   Judgment phase: Found that the DFS order of the stack top node $4$ is greater than $LCA(6,4)$, but the second largest node (the node below the stack top) $1$ has DFS order equal to the LCA (in fact, equal DFS order means equal nodes), indicating the LCA is already in the stack. So directly connect edge $1\to4$, which is from LCA to the stack top. Pop $4$ from the stack.

![vtree-15](./images/vtree-construction4.svg)

-   End the judgment phase, push $6$ onto the stack. Current stack: $6,1$.

![vtree-16](./images/vtree-construction5.svg)

-   Take the third element in the sequence as the current node, which is $7$. Take the top element of the stack, which is $6$. Compute the LCA of $7$ and $6$: $LCA(7,6)=3$.
-   Found $LCA(7,6)\neq$ the top element, enter the judgment phase.
-   Judgment phase: Found that the DFS order of the stack top node $6$ is greater than $LCA(7,6)$, but the second largest node $1$ has DFS order less than the LCA, indicating the LCA has never been pushed onto the stack. So directly connect edge $3\to6$, which is from LCA to the stack top. Pop $6$ from the stack, and push $LCA(6,7)$ onto the stack.
-   End the judgment phase, push $7$ onto the stack. Current stack: $1,3,7$.

![vtree-17](./images/vtree-construction6.svg)

-   Found that all 3 nodes in the sequence have been added to the stack, exit the loop.
-   At this time, there are 3 nodes in the stack: $1,3,7$. Clearly they are on the same chain, so directly connect: $1\to3$ and $3\to7$.
-   The virtual tree is built!

![vtree-18](./images/vtree-construction7.svg)

Next, we delete those nodes that haven't been pushed onto the stack (non-cyan nodes). The virtual tree looks like this:

![vtree-19](./images/vtree-construction8.svg)

There are many details, such as when storing the virtual tree using adjacency lists, we need to clear the adjacency list. But directly clearing the entire adjacency list is slow. So we can **clear the adjacency list of an element when an element that has never been pushed onto the stack is pushed**.

Time complexity is also $O(m\log n)$ (due to sorting), where $m$ is the number of key nodes and $n$ is the total number of nodes.

#### Implementation

The C++ code for building a virtual tree looks like this:

???+ note "Code Implementation"
    ```cpp
    bool cmp(const int x, const int y) { return id[x] < id[y]; }
    
    void build() {
      sort(h + 1, h + k + 1, cmp);
      sta[top = 1] = 1, g.sz = 0, g.head[1] = -1;
      // Push node 1 to stack, clear adjacency list for node 1, set edge count to 0
      for (int i = 1, l; i <= k; ++i)
        if (h[i] != 1) {
          // If node 1 is a key node, don't add it again
          l = lca(h[i], sta[top]);
          // Compute LCA of current node and stack top
          if (l != sta[top]) {
            // If LCA and stack top are different, current node is not on the chain stored by current stack
            while (id[l] < id[sta[top - 1]])
              // When second largest node's DFS order is greater than LCA's DFS order
              g.push(sta[top - 1], sta[top]), top--;
            // Connect and pop the chain that doesn't overlap with current node's chain
            if (id[l] > id[sta[top - 1]])
              // If LCA is not equal to second largest node (greater here actually has no difference from not equal)
              g.head[l] = -1, g.push(l, sta[top]), sta[top] = l;
            // LCA is first time pushed, clear its adjacency list, connect edge, pop stack top, and push LCA onto stack
            else
              g.push(l, sta[top--]);
            // LCA is second largest node, directly pop stack top
          }
          g.head[h[i]] = -1, sta[++top] = h[i];
          // Current node is certainly first time pushed, clear adjacency list and push onto stack
        }
      for (int i = 1; i < top; ++i)
        g.push(sta[i], sta[i + 1]);  // Connect the remaining last chain
      return;
    }
    ```

So we've learned how to build a virtual tree!

For the "Battle" problem, we just need to run the DP described at the beginning directly on the virtual tree. We've essentially used the virtual tree to filter out those useless non-key nodes! Still consider all children $v$ of $i$:

-   If $v$ is not a key node: $Dp(i)=Dp(i) + \min \{Dp(v),w(i,v)\}$
-   If $v$ is a key node: $Dp(i)=Dp(i) + w(i,v)$

So this problem is easily solved.

## Recommended Problems

-   [SDOI2011 Consumption War](https://www.luogu.com.cn/problem/P2495)
-   [HEOI2014 Big Project](https://www.luogu.com.cn/problem/P4103)
-   [HNOI2014 World Tree](https://www.luogu.com.cn/problem/P3233)