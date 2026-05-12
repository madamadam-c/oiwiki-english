## Introduction

Link/Cut Tree is a data structure used to solve **dynamic tree problems**.

Link/Cut Tree is also called Link-Cut Tree, abbreviated as LCT. It is not itself called a dynamic tree; dynamic tree refers to a class of problems.

Splay Tree is the foundation of LCT, but the Splay Tree used in LCT differs from an ordinary Splay in some details, with several extensions.

## Problem Introduction

Maintain a tree and support the following operations:

-   Modify the weights on the path between two vertices.
-   Query the sum of weights on the path between two vertices.
-   Modify the weights in the subtree of a vertex.
-   Query the sum of weights in the subtree of a vertex.

This is a template problem for heavy-light decomposition.

But add one more operation:

-   Cut and link some edges, while guaranteeing that the result is still a tree.

The answers to the above queries must be computed online.

This becomes a dynamic tree problem, which can be solved with LCT.

## Dynamic Tree Problems

Maintain a **forest**, supporting deletion and insertion of edges while guaranteeing that the graph remains a forest after each operation. We need to maintain some information about this forest.

Common operations include connectivity between two vertices, sum of weights on a path between two vertices, linking two vertices, cutting an edge, modifying information, and so on.

### Reviewing Heavy-Light Decomposition from the LCT Perspective

-   Decompose the whole tree according to subtree sizes, and relabel the vertices.
-   After relabeling, we find that the tree forms several contiguous intervals by chains, and interval operations can be performed with a segment tree.

### Moving to Dynamic Tree Problems

The tree decomposition just discussed uses subtree size as the criterion for decomposition. Can we redefine a decomposition so that it better fits dynamic tree problems?

Consider what kind of chains a dynamic tree problem needs.

Since we maintain a forest dynamically, we clearly want these chains to be the ones we specify, so that we can use them to solve the problem.

## Preferred-Path Decomposition

For all edges from a vertex to its children, we choose one edge ourselves for the decomposition. The chosen edge is called a preferred edge, and the other edges are virtual edges. For a preferred edge, the child it connects to is called a preferred child. A chain consisting of preferred edges is likewise called a preferred path. Remember the most important reason for choosing preferred-path decomposition: it is chosen by us, so it is flexible and changeable. Because of this flexibility, we use Splay Trees to maintain these preferred paths.

## LCT

We can simply understand LCT as using several Splay Trees to maintain a dynamic tree-chain decomposition, so as to implement interval operations on a dynamic tree. For each preferred path, we build a Splay Tree to maintain information over the whole chain interval.

## Auxiliary Trees

Let us first look at some properties of auxiliary trees, and then understand their concrete structure through a figure.

In this article, you can think of several Splay Trees as forming one auxiliary tree. Each auxiliary tree maintains one tree, and several auxiliary trees form the LCT, which maintains the entire forest.

1.  An auxiliary tree consists of multiple Splay Trees. Each Splay Tree maintains a path in the original tree, and the sequence of vertices obtained by an inorder traversal of this Splay Tree corresponds, from front to back, to a path in the original tree from top to bottom.
2.  Each node in the original tree corresponds one-to-one to a Splay node in the auxiliary tree.
3.  The Splay Trees in an auxiliary tree are not independent. The parent of the root node of each Splay Tree should normally be empty, but in LCT the parent of the root node of each Splay Tree points to the parent node of **this chain** in the original tree, namely the parent of the topmost vertex of the chain. This kind of parent link differs from an ordinary Splay parent link in that the child recognizes the parent, but the parent does not recognize the child. It corresponds to a **virtual edge** in the original tree. Therefore, each connected component has exactly one vertex whose parent is empty.
4.  Because of the above properties of auxiliary trees, we do not need to maintain the original tree for any operation. An auxiliary tree can uniquely recover an original tree in all cases, so it is enough to maintain the auxiliary tree.

Suppose we have an original tree as shown below. Bold edges are preferred edges, and dashed edges are virtual edges.

![tree](images/lct-atree-1.svg)

According to the definitions above, the auxiliary tree has the following structure.

![auxtree](images/lct-atree-2.svg)

### Structural Relationship Between the Original Tree and Auxiliary Tree

-   A preferred path in the original tree: its nodes are all in one Splay Tree in the auxiliary tree.
-   A virtual path in the original tree: in the auxiliary tree, the `Father` of the Splay Tree containing the child points to the parent node, but neither of the parent node's two children points to the child node.
-   Note: the root of the original tree is not the same as the root of the auxiliary tree.
-   The `Father` pointers in the original tree are not the same as the `Father` pointers in the auxiliary tree.
-   The auxiliary tree can be rerooted arbitrarily as long as the properties of the auxiliary tree and Splay Tree are satisfied.
-   Switching between virtual and preferred paths can be done easily on the auxiliary tree, which is how dynamic tree-chain decomposition is maintained.

### Variable Declarations Used Below

-   `ch[N][2]` left and right children
-   `f[N]` parent pointer
-   `sum[N]` sum of path weights
-   `val[N]` vertex weight
-   `tag[N]` reversal tag
-   `laz[N]` weight tag
-   `siz[N]` subtree size in the auxiliary tree
-   Other\_Vars

### Function Declarations

#### General Data Structure Functions (Literally)

1.  `PushUp(x)`
2.  `PushDown(x)`

#### Splay Tree Functions

The following are functions used in a Splay Tree. For details, see [Splay Tree](./splay.md).

1.  `Get(x)` obtains which child of its parent $x$ is.
2.  `Splay(x)` rotates $x$ to **the root of the current Splay Tree** by working together with the `Rotate` operation.
3.  `Rotate(x)` rotates $x$ upward by one level.

#### New Operations

1.  `Access(x)` puts all vertices from the root to $x$ into one preferred path, making the path from the root to $x$ a preferred path contained in the same Splay Tree. **Only this operation must be implemented; the other operations are implemented as required by the problem.**
2.  `IsRoot(x)` determines whether $x$ is the root of its current tree.
3.  `Update(x)` recursively applies `PushDown` from top to bottom after an `Access` operation to update information.
4.  `MakeRoot(x)` makes vertex $x$ the root of its tree.
5.  `Link(x, y)` links an edge between vertices $x, y$.
6.  `Cut(x, y)` deletes the edge between vertices $x, y$.
7.  `Find(x)` finds the index of the root node of the tree containing $x$.
8.  `Fix(x, v)` changes the weight of vertex $x$ to $v$.
9.  `Split(x, y)` extracts the path between $x, y$, making interval operations convenient.

### Macro Definitions

-   `#define ls ch[p][0]`
-   `#define rs ch[p][1]`

## Function Explanations

### `PushUp()`

```cpp
void PushUp(int p) {
  // maintain other variables
  siz[p] = siz[ls] + siz[rs] + 1;
}
```

### `PushDown()`

```cpp
void PushDown(int p) {
  if (tag[p] != std_tag) {
    // pushdown the tag
    tag[p] = std_tag;
  }
}
```

### `Splay() && Rotate()`

Here, `Splay()` and `Rotate()` differ somewhat from their implementation in an ordinary Splay Tree.

```cpp
#define Get(x) (ch[f[x]][1] == x)

void Rotate(int x) {
  int y = f[x], z = f[y], k = Get(x);
  if (!isRoot(y)) ch[z][ch[z][1] == y] = x;
  // This line must be written first. Ordinary Splay does not need this because of isRoot (explained later)
  ch[y][k] = ch[x][!k], f[ch[x][!k]] = y;
  ch[x][!k] = y, f[y] = x, f[x] = z;
  PushUp(y), PushUp(x);
}

void Splay(int x) {
  Update(
      x);  // You will see this soon. Before Splay, PushDown all nodes on the path that rotations will pass through
  for (int fa; fa = f[x], !isRoot(x); Rotate(x)) {
    if (!isRoot(fa)) Rotate(Get(fa) == Get(x) ? fa : x);
  }
}
```

For the functions above, see [Splay Tree](./splay.md).

The following functions are specific to LCT.

### `isRoot()`

```cpp
// As stated earlier, LCT has the property that if a child is not a preferred child, its parent cannot find it
// Therefore, when a node is neither its parent's left child nor its parent's right child, it is the root of the current Splay
#define isRoot(x) (ch[f[x]][0] != x && ch[f[x]][1] != x)
```

### `Access()`

```cpp
// Access is the core operation of LCT. Suppose we want to solve a path query, and that path
// happens to be exactly the current Splay Tree. Then we can directly use its information.
// First look at the code, then follow the process together with the figures.
int Access(int x) {
  int p;
  for (p = 0; x; p = x, x = f[x]) {
    Splay(x), ch[x][1] = p, PushUp(x);
  }
  return p;
}
```

-   We have the following tree, where solid lines are preferred edges and dashed lines are virtual edges.

    ![initial tree](images/lct-access-1.svg)

-   Its auxiliary tree may look like this. Different construction methods may produce different LCT structures.

    ![initial auxtree](images/lct-access-2.svg)

-   Now we want to perform `Access(N)`, turning all edges on the path from $A$ to $N$ into preferred edges and pulling them into one Splay Tree.

    ![access tree](images/lct-access-3.svg)

-   The implementation updates Splay Trees step by step from bottom to top.

-   First, rotate $N$ to the root of the current Splay Tree.

-   To preserve the properties of the AuxTree (auxiliary tree), the original preferred edge from $N$ to $O$ must be changed into a virtual edge.

-   Because of the property that the child recognizes the parent but the parent does not recognize the child, we can unilaterally set $N$'s child to `NULL`.

-   Thus the original AuxTree changes from the following figure to the one after it.

    ![step 1 auxtree](images/lct-access-4.svg)

-   Next, rotate the `Father` pointed to by $N$, namely $I$, to the root of $I$'s Splay Tree.

-   The original preferred edge $I$-$K$ must be removed. At this point, set $I$'s right child to $N$, obtaining a Splay Tree for $I$-$L$.

    ![step 2 auxtree](images/lct-access-5.svg)

-   Next, following the same steps, since $I$'s `Father` points to $H$, rotate $H$ to the root of its Splay Tree and then set $H$'s `rs` to $I$.

-   The resulting tree is as follows.

    ![step 3 auxtree](images/lct-access-6.svg)

-   Similarly, perform `Splay(A)` and set $A$'s right child to $H$.

-   Thus we obtain the following AuxTree, and we can see that the whole path $A$-$N$ is already in the same Splay Tree.

    ![step final auxtree](images/lct-access-7.svg)

```cpp
// Review the code
int Access(int x) {
  int p;
  for (p = 0; x; p = x, x = f[x]) {
    Splay(x), ch[x][1] = p, PushUp(x);
  }
  return p;
}
```

We can see that `Access()` is actually quite simple. It has only the following four steps:

1.  Rotate the current node to the root.
2.  Replace its child with the previous node.
3.  Update the information of the current node.
4.  Replace the current node with its parent and continue.

The `Access` implementation provided here also has a return value. This return value is equivalent to the index of the virtual-edge parent node during the last virtual/preferred path switch. It has two meanings:

-   When two `Access` operations are performed consecutively, the return value of the second `Access` equals the LCA of the two nodes.
-   It represents the root of the Splay Tree containing the chain from $x$ to the root. This node must already have been rotated to the root, and its parent must be empty.

### `Update()`

```cpp
// Just pushDown level by level from top to bottom
void Update(int p) {
  if (!isRoot(p)) Update(f[p]);
  pushDown(p);
}
```

### `makeRoot()`

-   `Make_Root()` is no less important than `Access()`. When maintaining path information, paths whose depths do not strictly increase will inevitably appear. According to the properties of the AuxTree, such a path cannot appear in one Splay Tree.
-   This is when we need `Make_Root()`.
-   The role of `Make_Root()` is to make the specified vertex the root of the original tree. Consider how to implement this operation.
-   Suppose the return value of `Access(x)` is $y$. Then the path from $x$ to the current root forms exactly one Splay Tree, and the root of that Splay Tree is $y$.
-   Consider representing the tree as a directed graph, orienting each edge from child to parent. It is easy to see that rerooting is equivalent to reversing all edges on the path from $x$ to the root. Think about this carefully.
-   Therefore, it is enough to reverse the path from $x$ to the current root.
-   Since $y$ is the root of the Splay Tree representing the path from $x$ to the current root, simply perform an interval reversal on the Splay Tree rooted at $y$.

```cpp
void makeRoot(int p) {
  p = Access(p);
  swap(ch[p][0], ch[p][1]);
  tag[p] ^= 1;
}
```

### `Link()`

-   Linking two vertices is actually simple: first call `Make_Root(x)`, then make the parent of $x$ point to $y$. Obviously, this operation must not be performed within the same tree, so remember to check first.

```cpp
void Link(int x, int p) {
  makeRoot(x);
  splay(x);
  f[x] = p;
}
```

### `Split()`

-   The meaning of the `Split` operation is simple: extract a Splay Tree that maintains the path from $x$ to $y$.
-   First call `MakeRoot(x)`, then `Access(y)`. If you want $y$ to be the root, call `Splay(y)` as well.
-   In addition, these three operations in `Split` can directly extract the needed path into $y$'s subtree, allowing other operations to be performed.

### `Cut()`

-   There are two cases for `Cut`: the operation is guaranteed to be valid, or it is not necessarily valid.
-   If validity is guaranteed, directly call `Split(x, y)`. At this point $y$ is the root, and $x$ must be its child, so disconnect both directions. Like this:

```cpp
void Cut(int x, int p) { makeRoot(x), Access(p), Splay(p), ls = f[x] = 0; }
```

If validity is not guaranteed, we need to determine whether such an edge exists. One option is to store edges with a `map`, but here is a method that uses the properties of LCT:

To delete an edge, the following three conditions must be satisfied:

1.  $x,y$ are connected.
2.  There are no other chains on the path between $x,y$.
3.  $x$ has no right child.

In summary, the three statements above mean exactly one thing: there is an edge between $x,y$.

The concrete implementation is left as an exercise. Checking connectivity requires the later `Find`; for the other two conditions, a little thought about the structure will show how to test them.

### `Find()`

-   `Find()` finds the root of the **original tree** containing $x$. Do not confuse the original tree root with the auxiliary tree root. After `Access(p)`, call `Splay(p)`. Then the root is the vertex with the smallest depth in the tree; keep moving to the left child and apply `PushDown` along the way.
-   Keep moving until there is no `ls`; this is very simple.
-   Note that after each query, the node corresponding to the answer must be `Splay`ed upward to guarantee the complexity.

```cpp
int Find(int p) {
  Access(p);
  Splay(p);
  pushDown(p);
  while (ls) p = ls, pushDown(p);
  Splay(p);
  return p;
}
```

### Notes

-   Before each operation, always consider whether `PushUp` or `PushDown` is needed. Because LCT is very flexible, missing even one `Pushdown` or `Pushup` may apply modifications to the wrong nodes.
-   LCT's `Rotate` is different from Splay's; `if (z)` must be placed first.
-   LCT's `Splay` operation only rotates a node to the root. There is no operation to rotate it to be someone's child, because it is unnecessary.

## Time Complexity

Most operations in LCT are based on `Access`, and the remaining operations have constant time complexity, so we only need to analyze the time complexity of `Access`.

The time complexity of `Access` mainly comes from multiple splay operations and visits to virtual edges on the path. We analyze these two parts separately.

1.  splay

    -   Define $w(x) = \log size(x)$, where $size(x)$ denotes the total number of virtual and preferred edges in the subtree rooted at $x$.

    -   Define the potential function $\Phi = \sum_{x \in T} w(x)$, where $T$ denotes the set of all nodes.

    From the analysis of [the time complexity of Splay](./splay.md#时间复杂度), it is easy to see that the amortized time complexity of a splay operation is $O(\log n)$.

2.  Visiting virtual edges

    Referring to [heavy-light decomposition](../graph/hld.md#重链剖分), define two types of virtual edges:

    -   **Heavy virtual edge**: a virtual edge from node $v$ to its parent, where $size(v) > \frac{1}{2} size(parent(v))$.

    -   **Light virtual edge**: a virtual edge from node $v$ to its parent, where $size(v) \leq \frac{1}{2} size(parent(v))$.

    For handling virtual edges, we can use potential analysis. Define the potential function $\Phi$ as the number of all heavy virtual edges, and define the amortized cost $c_i = t_i + \Delta \Phi_i$, where $t_i$ is the actual cost of the operation and $\Delta \Phi_i$ is the change in potential.

    -   After traversing a heavy virtual edge, it is converted into a preferred edge. This operation decreases the potential by $1$ because it optimizes the tree structure by strengthening an important connection. Since its actual cost is $O(1)$, it offsets the increase in potential and does not increase the amortized cost. All amortized cost is concentrated in the handling of light virtual edges.

    -   Each `Access` operation traverses at most $O(\log n)$ light virtual edges, so it consumes at most $O(\log n)$ actual cost and creates $O(\log n)$ heavy virtual edges, meaning the potential increases by at most $O(\log n)$.

    Therefore, the final amortized complexity of visiting virtual edges is the sum of the actual operation cost and the change in potential, namely $O(\log n)$.

In summary, the time complexity of the `Access` operation in LCT is the sum of the complexities of splay operations and virtual-edge visits. Therefore, the final amortized complexity is $O(\log n)$. That is, for an LCT with n nodes, performing m `Access` operations takes $O(n \log n + m \log n)$ time. Consequently, operations based on `Access`, such as `Cut`, `Link`, and `Findroot`, also have amortized complexity $O(\log n)$.

## Exercises

-   [「BZOJ 3282」Tree](https://hydro.ac/p/bzoj-P3282)
-   [「HNOI2010」Bouncing Sheep](https://www.luogu.com.cn/problem/P3203)

## Maintaining Tree-Chain Information

Through the `Split(x,y)` operation, LCT can extract the path from vertex $x$ to vertex $y$ in the tree into the Splay Tree rooted at $y$. Modifying and querying tree-chain information are transformed into operations on a balanced tree, which gives LCT an advantage in maintaining tree-chain information. In addition, binary search on a tree chain implemented with LCT saves one $O(\log n)$ factor compared with heavy-light decomposition.

???+ note "Example [「National Training Team」Tree II](https://www.luogu.com.cn/problem/P1501)"
    Given a tree with $n$ nodes, where each node initially has weight $1$. There are $q$ operations, each of one of the following four types:
    
    1.  `- u1 v1 u2 v2`: delete the edge between vertices $u_1,v_1$ in the tree, and connect vertices $u_2,v_2$. The operation is guaranteed to be valid and the graph remains a tree after linking.
    2.  `+ u v c`: add to the weights of all vertices on the path between $u,v$ in the tree by $c$.
    3.  `* u v c`: multiply the weights of all vertices on the path between $u,v$ in the tree by $c$.
    4.  `/ u v`: output the sum of vertex weights on the path between $u,v$ in the tree, modulo $51061$.
    
        $1\le n,q\le 10^5,0\le c\le 10^4$
    
        The `-` operation can be implemented directly as `Cut(u1,v1),Link(u2,v2)`.

When modifying the path between vertices $u,v$ in the tree, first call `Split(u,v)`.

This problem requires subtree addition, subtree multiplication, and subtree sum queries on the auxiliary tree. Therefore, besides the subtree reversal tag needed by a normal LCT, we also need to maintain subtree addition and multiplication tags. The method for handling tags is the same as in a Splay Tree.

When applying and pushing down an addition tag, the change in the subtree weight sum depends on the number of nodes in the subtree, so we also need to maintain the subtree size `siz`.

When pushing down tags, pay attention to the order: push down the multiplication tag first, then the addition tag. The subtree reversal tag does not conflict with the subtree addition and multiplication tags.

??? note "Reference Code"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    using namespace std;
    constexpr long long MAXN = 100010;
    constexpr long long mod = 51061;
    long long n, q, u, v, c;
    char op;
    
    struct Splay {
      long long ch[MAXN][2], fa[MAXN], siz[MAXN], val[MAXN], sum[MAXN], rev[MAXN],
          add[MAXN], mul[MAXN];
    
      void clear(long long x) {
        ch[x][0] = ch[x][1] = fa[x] = siz[x] = val[x] = sum[x] = rev[x] = add[x] =
            0;
        mul[x] = 1;
      }
    
      long long getch(long long x) { return (ch[fa[x]][1] == x); }
    
      long long isroot(long long x) {
        clear(0);
        return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
      }
    
      void maintain(long long x) {
        clear(0);
        siz[x] = (siz[ch[x][0]] + 1 + siz[ch[x][1]]) % mod;
        sum[x] = (sum[ch[x][0]] + val[x] + sum[ch[x][1]]) % mod;
      }
    
      void pushdown(long long x) {
        clear(0);
        if (mul[x] != 1) {
          if (ch[x][0])
            mul[ch[x][0]] = (mul[x] * mul[ch[x][0]]) % mod,
            val[ch[x][0]] = (val[ch[x][0]] * mul[x]) % mod,
            sum[ch[x][0]] = (sum[ch[x][0]] * mul[x]) % mod,
            add[ch[x][0]] = (add[ch[x][0]] * mul[x]) % mod;
          if (ch[x][1])
            mul[ch[x][1]] = (mul[x] * mul[ch[x][1]]) % mod,
            val[ch[x][1]] = (val[ch[x][1]] * mul[x]) % mod,
            sum[ch[x][1]] = (sum[ch[x][1]] * mul[x]) % mod,
            add[ch[x][1]] = (add[ch[x][1]] * mul[x]) % mod;
          mul[x] = 1;
        }
        if (add[x]) {
          if (ch[x][0])
            add[ch[x][0]] = (add[ch[x][0]] + add[x]) % mod,
            val[ch[x][0]] = (val[ch[x][0]] + add[x]) % mod,
            sum[ch[x][0]] = (sum[ch[x][0]] + add[x] * siz[ch[x][0]] % mod) % mod;
          if (ch[x][1])
            add[ch[x][1]] = (add[ch[x][1]] + add[x]) % mod,
            val[ch[x][1]] = (val[ch[x][1]] + add[x]) % mod,
            sum[ch[x][1]] = (sum[ch[x][1]] + add[x] * siz[ch[x][1]] % mod) % mod;
          add[x] = 0;
        }
        if (rev[x]) {
          if (ch[x][0]) rev[ch[x][0]] ^= 1, swap(ch[ch[x][0]][0], ch[ch[x][0]][1]);
          if (ch[x][1]) rev[ch[x][1]] ^= 1, swap(ch[ch[x][1]][0], ch[ch[x][1]][1]);
          rev[x] = 0;
        }
      }
    
      void update(long long x) {
        if (!isroot(x)) update(fa[x]);
        pushdown(x);
      }
    
      void print(long long x) {
        if (!x) return;
        pushdown(x);
        print(ch[x][0]);
        printf("%lld ", x);
        print(ch[x][1]);
      }
    
      void rotate(long long x) {
        long long y = fa[x], z = fa[y], chx = getch(x), chy = getch(y);
        fa[x] = z;
        if (!isroot(y)) ch[z][chy] = x;
        ch[y][chx] = ch[x][chx ^ 1];
        fa[ch[x][chx ^ 1]] = y;
        ch[x][chx ^ 1] = y;
        fa[y] = x;
        maintain(y);
        maintain(x);
        maintain(z);
      }
    
      void splay(long long x) {
        update(x);
        for (long long f = fa[x]; f = fa[x], !isroot(x); rotate(x))
          if (!isroot(f)) rotate(getch(x) == getch(f) ? f : x);
      }
    
      void access(long long x) {
        for (long long f = 0; x; f = x, x = fa[x])
          splay(x), ch[x][1] = f, maintain(x);
      }
    
      void makeroot(long long x) {
        access(x);
        splay(x);
        swap(ch[x][0], ch[x][1]);
        rev[x] ^= 1;
      }
    
      long long find(long long x) {
        access(x);
        splay(x);
        while (ch[x][0]) x = ch[x][0];
        splay(x);
        return x;
      }
    } st;
    
    main() {
      scanf("%lld%lld", &n, &q);
      for (long long i = 1; i <= n; i++) st.val[i] = 1, st.maintain(i);
      for (long long i = 1; i < n; i++) {
        scanf("%lld%lld", &u, &v);
        if (st.find(u) != st.find(v)) st.makeroot(u), st.fa[u] = v;
      }
      while (q--) {
        scanf(" %c%lld%lld", &op, &u, &v);
        if (op == '+') {
          scanf("%lld", &c);
          st.makeroot(u), st.access(v), st.splay(v);
          st.val[v] = (st.val[v] + c) % mod;
          st.sum[v] = (st.sum[v] + st.siz[v] * c % mod) % mod;
          st.add[v] = (st.add[v] + c) % mod;
        }
        if (op == '-') {
          st.makeroot(u);
          st.access(v);
          st.splay(v);
          if (st.ch[v][0] == u && !st.ch[u][1]) st.ch[v][0] = st.fa[u] = 0;
          scanf("%lld%lld", &u, &v);
          if (st.find(u) != st.find(v)) st.makeroot(u), st.fa[u] = v;
        }
        if (op == '*') {
          scanf("%lld", &c);
          st.makeroot(u), st.access(v), st.splay(v);
          st.val[v] = st.val[v] * c % mod;
          st.sum[v] = st.sum[v] * c % mod;
          st.mul[v] = st.mul[v] * c % mod;
        }
        if (op == '/')
          st.makeroot(u), st.access(v), st.splay(v), printf("%lld\n", st.sum[v]);
      }
      return 0;
    }
    ```

### Exercises

-   [luogu P3690 [Template] Link Cut Tree (Dynamic Tree)](https://www.luogu.com.cn/problem/P3690)
-   [「SDOI2011」Coloring](https://www.luogu.com.cn/problem/P2486)
-   [「SHOI2014」Trigeminal Nerve Tree](https://loj.ac/problem/2187)

## Maintaining Connectivity

### Determining Connectivity

Using LCT's `Find()` function, we can determine whether two vertices in a dynamic forest are connected. If `Find(x)==Find(y)`, then vertices $x,y$ are in the same tree and are connected.

???+ note "Example [「SDOI2008」Cave Survey](https://www.luogu.com.cn/problem/P2147)"
    Initially there are $n$ isolated vertices and $m$ operations. Each operation is one of the following:
    
    1.  `Connect u v`: connect an edge between vertices $u,v$.
    2.  `Destroy u v`: delete the edge between vertices $u,v$; it is guaranteed that such an edge existed before.
    3.  `Query u v`: ask whether vertices $u,v$ are connected.
    
    It is guaranteed that the graph is a forest at all times.
    
    $n\le 10^4, m\le 2\times 10^5$

??? note "Reference Code"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    using namespace std;
    constexpr int MAXN = 10010;
    
    struct Splay {
      int ch[MAXN][2], fa[MAXN], tag[MAXN];
    
      void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = tag[x] = 0; }
    
      int getch(int x) { return ch[fa[x]][1] == x; }
    
      int isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
    
      void pushdown(int x) {
        if (tag[x]) {
          if (ch[x][0]) swap(ch[ch[x][0]][0], ch[ch[x][0]][1]), tag[ch[x][0]] ^= 1;
          if (ch[x][1]) swap(ch[ch[x][1]][0], ch[ch[x][1]][1]), tag[ch[x][1]] ^= 1;
          tag[x] = 0;
        }
      }
    
      void update(int x) {
        if (!isroot(x)) update(fa[x]);
        pushdown(x);
      }
    
      void rotate(int x) {
        int y = fa[x], z = fa[y], chx = getch(x), chy = getch(y);
        fa[x] = z;
        if (!isroot(y)) ch[z][chy] = x;
        ch[y][chx] = ch[x][chx ^ 1];
        fa[ch[x][chx ^ 1]] = y;
        ch[x][chx ^ 1] = y;
        fa[y] = x;
      }
    
      void splay(int x) {
        update(x);
        for (int f = fa[x]; f = fa[x], !isroot(x); rotate(x))
          if (!isroot(f)) rotate(getch(x) == getch(f) ? f : x);
      }
    
      void access(int x) {
        for (int f = 0; x; f = x, x = fa[x]) splay(x), ch[x][1] = f;
      }
    
      void makeroot(int x) {
        access(x);
        splay(x);
        swap(ch[x][0], ch[x][1]);
        tag[x] ^= 1;
      }
    
      int find(int x) {
        access(x);
        splay(x);
        while (ch[x][0]) x = ch[x][0];
        splay(x);
        return x;
      }
    } st;
    
    int n, q, x, y;
    char op[MAXN];
    
    int main() {
      scanf("%d%d", &n, &q);
      while (q--) {
        scanf("%s%d%d", op, &x, &y);
        if (op[0] == 'Q') {
          if (st.find(x) == st.find(y))
            printf("Yes\n");
          else
            printf("No\n");
        }
        if (op[0] == 'C')
          if (st.find(x) != st.find(y)) st.makeroot(x), st.fa[x] = y;
        if (op[0] == 'D') {
          st.makeroot(x);
          st.access(y);
          st.splay(y);
          if (st.ch[y][0] == x && !st.ch[x][1]) st.ch[y][0] = st.fa[x] = 0;
        }
      }
      return 0;
    }
    ```

### Maintaining Edge-Biconnected Components

If we need to contract each edge-biconnected component into a single point, then whenever an edge is added, if the two connected vertices in the tree are already connected, all vertices on that path will be contracted into one point.

???+ note "Example [「AHOI2005」Route Planning](https://www.luogu.com.cn/problem/P2542)"
    Given $n$ vertices, initially with $m$ undirected edges, and $q$ operations. Each operation is one of the following:
    
    1.  `0 u v`: delete the edge between $u,v$; it is guaranteed that such an edge exists at this time.
    2.  `1 u v`: query the number of edges that every possible path between vertices $u,v$ must pass through at this time.
    
    It is guaranteed that the graph is connected at all times.
    
    $1<n<3\times 10^4,1<m<10^5,0\le q\le 4\times 10^4$

We can see that the number of edges that every possible path between vertices $u,v$ must pass through equals the number of nodes on the path between the contracted point containing $u$ and the contracted point containing $v$ $-1$ after all edge-biconnected components are contracted into points.

Since edge deletion in the problem is hard to handle, we consider processing the operations offline in reverse, turning deletions into insertions.

When adding an edge, if the two vertices were not originally connected, connect them in the LCT. Otherwise, extract the path between these two vertices in the LCT before adding this edge. Traversing this subtree in the auxiliary tree is equivalent to traversing the path; merge these points and use a disjoint-set union to maintain the merged information.

Use the representative element of the merged DSU set to replace the original path in the tree. Note that in every subsequent operation, you must find the representative element of each operation vertex in the DSU before operating on it.

??? note "Reference Code"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <map>
    using namespace std;
    constexpr int MAXN = 200010;
    int f[MAXN];
    
    int findp(int x) { return f[x] ? f[x] = findp(f[x]) : x; }
    
    void merge(int x, int y) {
      x = findp(x);
      y = findp(y);
      if (x != y) f[x] = y;
    }
    
    struct Splay {
      int ch[MAXN][2], fa[MAXN], tag[MAXN], siz[MAXN];
    
      void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = tag[x] = siz[x] = 0; }
    
      int getch(int x) { return ch[findp(fa[x])][1] == x; }
    
      int isroot(int x) {
        return ch[findp(fa[x])][0] != x && ch[findp(fa[x])][1] != x;
      }
    
      void maintain(int x) {
        clear(0);
        if (x) siz[x] = siz[ch[x][0]] + 1 + siz[ch[x][1]];
      }
    
      void pushdown(int x) {
        if (tag[x]) {
          if (ch[x][0]) tag[ch[x][0]] ^= 1, swap(ch[ch[x][0]][0], ch[ch[x][0]][1]);
          if (ch[x][1]) tag[ch[x][1]] ^= 1, swap(ch[ch[x][1]][0], ch[ch[x][1]][1]);
          tag[x] = 0;
        }
      }
    
      void print(int x) {
        if (!x) return;
        pushdown(x);
        print(ch[x][0]);
        printf("%d ", x);
        print(ch[x][1]);
      }
    
      void update(int x) {
        if (!isroot(x)) update(findp(fa[x]));
        pushdown(x);
      }
    
      void rotate(int x) {
        x = findp(x);
        int y = findp(fa[x]), z = findp(fa[y]), chx = getch(x), chy = getch(y);
        fa[x] = z;
        if (!isroot(y)) ch[z][chy] = x;
        ch[y][chx] = ch[x][chx ^ 1];
        fa[ch[x][chx ^ 1]] = y;
        ch[x][chx ^ 1] = y;
        fa[y] = x;
        maintain(y);
        maintain(x);
        if (z) maintain(z);
      }
    
      void splay(int x) {
        x = findp(x);
        update(x);
        for (int f = findp(fa[x]); f = findp(fa[x]), !isroot(x); rotate(x))
          if (!isroot(f)) rotate(getch(x) == getch(f) ? f : x);
      }
    
      void access(int x) {
        for (int f = 0; x; f = x, x = findp(fa[x]))
          splay(x), ch[x][1] = f, maintain(x);
      }
    
      void makeroot(int x) {
        x = findp(x);
        access(x);
        splay(x);
        tag[x] ^= 1;
        swap(ch[x][0], ch[x][1]);
      }
    
      int find(int x) {
        x = findp(x);
        access(x);
        splay(x);
        while (ch[x][0]) x = ch[x][0];
        splay(x);
        return x;
      }
    
      void dfs(int x) {
        pushdown(x);
        if (ch[x][0]) dfs(ch[x][0]), merge(ch[x][0], x);
        if (ch[x][1]) dfs(ch[x][1]), merge(ch[x][1], x);
      }
    } st;
    
    int n, m, q, x, y, cur, ans[MAXN];
    
    struct oper {
      int op, a, b;
    } s[MAXN];
    
    map<pair<int, int>, int> mp;
    
    int main() {
      scanf("%d%d", &n, &m);
      for (int i = 1; i <= n; i++) st.maintain(i);
      for (int i = 1; i <= m; i++)
        scanf("%d%d", &x, &y), mp[{x, y}] = mp[{y, x}] = 1;
      while (scanf("%d", &s[++q].op)) {
        if (s[q].op == -1) {
          q--;
          break;
        }
        scanf("%d%d", &s[q].a, &s[q].b);
        if (!s[q].op) mp[{s[q].a, s[q].b}] = mp[{s[q].b, s[q].a}] = 0;
      }
      reverse(s + 1, s + q + 1);
      for (map<pair<int, int>, int>::iterator it = mp.begin(); it != mp.end(); it++)
        if (it->second) {
          mp[{it->first.second, it->first.first}] = 0;
          x = findp(it->first.first);
          y = findp(it->first.second);
          if (st.find(x) != st.find(y))
            st.makeroot(x), st.fa[x] = y;
          else {
            if (x == y) continue;
            st.makeroot(x);
            st.access(y);
            st.splay(y);
            st.dfs(y);
            int t = findp(y);
            st.fa[t] = findp(st.fa[y]);
            st.ch[t][0] = st.ch[t][1] = 0;
            st.maintain(t);
          }
        }
      for (int i = 1; i <= q; i++) {
        if (s[i].op == 0) {
          x = findp(s[i].a);
          y = findp(s[i].b);
          st.makeroot(x);
          st.access(y);
          st.splay(y);
          st.dfs(y);
          int t = findp(y);
          st.fa[t] = st.fa[y];
          st.ch[t][0] = st.ch[t][1] = 0;
          st.maintain(t);
        }
        if (s[i].op == 1) {
          x = findp(s[i].a);
          y = findp(s[i].b);
          st.makeroot(x);
          st.access(y);
          st.splay(y);
          ans[++cur] = st.siz[y] - 1;
        }
      }
      for (int i = cur; i >= 1; i--) printf("%d\n", ans[i]);
      return 0;
    }
    ```

### Exercises

-   [Luogu P3950 Tribal Conflict](https://www.luogu.com.cn/problem/P3950)
-   [BZOJ 4998 Planet Alliance](https://hydro.ac/p/bzoj-P4998)
-   [BZOJ 2959 Long-Distance Running](https://hydro.ac/p/bzoj-P2959)

## Maintaining Edge Weights

LCT cannot directly handle edge weights. In this case, we need to create a corresponding vertex for each edge, making it convenient to query edge information on a chain. Using this technique, we can dynamically maintain a spanning tree.

???+ note "Example [luogu P4234 Minimum-Difference Spanning Tree](https://www.luogu.com.cn/problem/P4234)"
    Given a weighted undirected graph with $n$ vertices and $m$ edges, find a spanning tree that minimizes the difference between its maximum edge weight and minimum edge weight, and output this difference.
    
    The data guarantees that at least one spanning tree exists.
    
    $1\le n\le 5\times 10^4,1\le m\le 2\times 10^5,1\le w_i\le 10^4$

Sort the edges by weight in increasing order, and enumerate the rightmost selected edge. To obtain the optimal answer, the minimum edge weight among the selected edges should be as large as possible.

Add edges in order. If the two vertices to be connected are already connected, delete the edge with the minimum weight on the path between them. If the whole graph has become connected as a tree, update the answer with the current edge weight minus the minimum edge weight. The minimum edge weight can be updated with the two-pointer method.

There is no fixed parent-child relationship in an LCT, so edge weights cannot be recorded directly as vertex weights.

To record edge information on a tree chain, use **edge splitting**. Create a corresponding vertex for each edge, and connect this edge-vertex to the two endpoints of the edge. The original link and cut operations each become two operations.

??? note "Reference Code"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <set>
    using namespace std;
    constexpr int MAXN = 5000010;
    
    struct Splay {
      int ch[MAXN][2], fa[MAXN], tag[MAXN], val[MAXN], minn[MAXN];
    
      void clear(int x) {
        ch[x][0] = ch[x][1] = fa[x] = tag[x] = val[x] = minn[x] = 0;
      }
    
      int getch(int x) { return ch[fa[x]][1] == x; }
    
      int isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
    
      void maintain(int x) {
        if (!x) return;
        minn[x] = x;
        if (ch[x][0]) {
          if (val[minn[ch[x][0]]] < val[minn[x]]) minn[x] = minn[ch[x][0]];
        }
        if (ch[x][1]) {
          if (val[minn[ch[x][1]]] < val[minn[x]]) minn[x] = minn[ch[x][1]];
        }
      }
    
      void pushdown(int x) {
        if (tag[x]) {
          if (ch[x][0]) tag[ch[x][0]] ^= 1, swap(ch[ch[x][0]][0], ch[ch[x][0]][1]);
          if (ch[x][1]) tag[ch[x][1]] ^= 1, swap(ch[ch[x][1]][0], ch[ch[x][1]][1]);
          tag[x] = 0;
        }
      }
    
      void update(int x) {
        if (!isroot(x)) update(fa[x]);
        pushdown(x);
      }
    
      void print(int x) {
        if (!x) return;
        pushdown(x);
        print(ch[x][0]);
        printf("%d ", x);
        print(ch[x][1]);
      }
    
      void rotate(int x) {
        int y = fa[x], z = fa[y], chx = getch(x), chy = getch(y);
        fa[x] = z;
        if (!isroot(y)) ch[z][chy] = x;
        ch[y][chx] = ch[x][chx ^ 1];
        fa[ch[x][chx ^ 1]] = y;
        ch[x][chx ^ 1] = y;
        fa[y] = x;
        maintain(y);
        maintain(x);
        if (z) maintain(z);
      }
    
      void splay(int x) {
        update(x);
        for (int f = fa[x]; f = fa[x], !isroot(x); rotate(x))
          if (!isroot(f)) rotate(getch(x) == getch(f) ? f : x);
      }
    
      void access(int x) {
        for (int f = 0; x; f = x, x = fa[x]) splay(x), ch[x][1] = f, maintain(x);
      }
    
      void makeroot(int x) {
        access(x);
        splay(x);
        tag[x] ^= 1;
        swap(ch[x][0], ch[x][1]);
      }
    
      int find(int x) {
        access(x);
        splay(x);
        while (ch[x][0]) x = ch[x][0];
        splay(x);
        return x;
      }
    
      void link(int x, int y) {
        makeroot(x);
        fa[x] = y;
      }
    
      void cut(int x, int y) {
        makeroot(x);
        access(y);
        splay(y);
        ch[y][0] = fa[x] = 0;
        maintain(y);
      }
    } st;
    
    constexpr int inf = 2e9 + 1;
    int n, m, ans, nww, x, y;
    
    struct Edge {
      int u, v, w;
    
      bool operator<(Edge x) const { return w < x.w; };
    } s[MAXN];
    
    multiset<int> mp;
    
    int main() {
      scanf("%d%d", &n, &m);
      for (int i = 1; i <= n; i++) st.val[i] = inf, st.maintain(i);
      for (int i = 1; i <= m; i++) scanf("%d%d%d", &s[i].u, &s[i].v, &s[i].w);
      sort(s + 1, s + m + 1);
      for (int i = 1; i <= m; i++) st.val[n + i] = s[i].w, st.maintain(n + i);
      for (int i = 1; i <= m; i++) {
        x = s[i].u;
        y = s[i].v;
        if (x == y) continue;
        if (st.find(x) != st.find(y)) {
          nww++;
          st.link(x, n + i);
          st.link(n + i, y);
          mp.insert(s[i].w);
          if (nww == n - 1) ans = s[i].w - (*(mp.begin()++));
        } else {
          st.makeroot(x);
          st.access(y);
          st.splay(y);
          int t = st.minn[y] - n;
          st.cut(s[t].u, t + n);
          st.cut(t + n, s[t].v);
          mp.erase(mp.find(s[t].w));
          st.link(x, n + i);
          st.link(n + i, y);
          mp.insert(s[i].w);
          if (nww == n - 1) ans = min(ans, s[i].w - (*(mp.begin()++)));
        }
      }
      printf("%d\n", ans);
      return 0;
    }
    ```

### Exercises

-   [「WC2006」Chief of the Water Pipe Bureau](https://www.luogu.com.cn/problem/P4172)
-   [「BJWC2010」Strictly Second-Best Minimum Spanning Tree](https://www.luogu.com.cn/problem/P4180)
-   [「NOI2014」Magic Forest](https://uoj.ac/problem/3)

## Maintaining Subtree Information

LCT is not good at maintaining subtree information. By aggregating the information of all virtual subtrees of a node, we can obtain the information of the whole tree.

???+ note "Example [「BJOI2014」Great Fusion](https://loj.ac/problem/2230)"
    Given $n$ nodes and $q$ operations, each operation has one of the following forms:
    
    1.  `A x y`: connect an edge between nodes $x$ and $y$.
    2.  `Q x y`: given an existing edge $(x,y)$, find how many simple paths contain edge $(x,y)$.
    
    It is guaranteed that the graph is a forest at all times.
    
    $1\le n,q,x,y\le 10^5$

Consider another formulation of query `Q`. We find that the answer equals the product of the number of nodes on the edge $(x,y)$'s $x$ side and the number of nodes on the $y$ side, namely, after cutting edge $(x,y)$, the sizes of the two trees containing $x$ and $y$ respectively. To eliminate the effect of cutting the edge, we connect edge $(x,y)$ again after the query.

The operations in the problem include both linking and cutting, and it is guaranteed that the graph is always a forest, so LCT naturally comes to mind. However, in this problem LCT maintains subtree sizes, unlike the usual case of maintaining information on a chain. Moreover, LCT's structure **lets children recognize parents, but not parents recognize children**, which makes direct subtree statistics inconvenient. What should we do?

The method is to aggregate the contribution of the subtrees represented by all virtual children of a node $x$, that is, nodes whose parent is $x$ but which are not among $x$'s left or right children in the Splay Tree.

Define $siz2[x]$ as the number of nodes in the subtrees represented by all virtual children of node $x$, and $siz[x]$ as the number of nodes in the subtree of node $x$.

Unlike the usual way of maintaining the number of nodes in a Splay subtree, when computing the number of nodes in the subtree of node $x$, we also need to add $siz2[x]$, namely:

```cpp
void maintain(int x) {
  clear(0);
  if (x) siz[x] = siz[ch[x][0]] + 1 + siz[ch[x][1]] + siz2[x];
}
```

Moreover, when we **change the shape of a Splay Tree**, meaning when we change a node's left or right child pointer in the Splay Tree, we need to update the value of $siz2[x]$ in time.

In `Rotate()` and `Splay()`, we only change the relative positions of nodes inside the Splay Tree. We do not change whether any edge is virtual or preferred, so we do not modify $siz2[x]$.

In the `access` operation, after each splay, the right child of the node just splayed changes. In other words, the preferred/virtual status of the edge between this node and its original right child, and the edge between this node and its new right child, changes. We need to add the contribution of the subtree connected by the edge that has just become virtual, and subtract the contribution of the subtree connected by the edge that has just become preferred. The code is as follows:

```cpp
void access(int x) {
  for (int f = 0; x; f = x, x = fa[x])
    splay(x), siz2[x] += siz[ch[x][1]] - siz[f], ch[x][1] = f, maintain(x);
}
```

In `MakeRoot()` and `Find()`, we only call previous functions or traverse edges in the Splay Tree, so no modification is needed.

When linking two nodes, we modify the parent of one node. We need to add the subtree-size contribution of the new child node to the $siz2$ value of the parent node.

```cpp
st.makeroot(x);
st.makeroot(y);
st.fa[x] = y;
st.siz2[y] += st.siz[x];
```

When cutting an edge, we only delete a preferred edge in the Splay Tree. The `Maintain` operation maintains this information, so no additional modification is needed.

The above are the details of the code changes. Finally, summarize the requirements and methods for maintaining subtree information with LCT:

1.  The maintained information must be **subtractable**, such as subtree node count or subtree weight sum. Subtree maximum and minimum values cannot be maintained directly, because when a virtual edge becomes a preferred edge, the contribution of the original virtual edge must be excluded.
2.  Create an additional value to store the contribution of virtual subtrees. When calculating statistics, add it to the answer for this node, and maintain it promptly when an edge changes between virtual and preferred.
3.  The remaining parts are the same as in a normal LCT. When querying subtree information, be sure to make that node the root.
4.  If the maintained information is not subtractable, such as interval extrema, a balanced tree can be created for each node to maintain the extrema in that node's virtual subtrees.

??? note "Reference Code"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    using namespace std;
    constexpr int MAXN = 100010;
    using ll = long long;
    
    struct Splay {
      int ch[MAXN][2], fa[MAXN], siz[MAXN], siz2[MAXN], tag[MAXN];
    
      void clear(int x) {
        ch[x][0] = ch[x][1] = fa[x] = siz[x] = siz2[x] = tag[x] = 0;
      }
    
      int getch(int x) { return ch[fa[x]][1] == x; }
    
      int isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
    
      void maintain(int x) {
        clear(0);
        if (x) siz[x] = siz[ch[x][0]] + 1 + siz[ch[x][1]] + siz2[x];
      }
    
      void pushdown(int x) {
        if (tag[x]) {
          if (ch[x][0]) swap(ch[ch[x][0]][0], ch[ch[x][0]][1]), tag[ch[x][0]] ^= 1;
          if (ch[x][1]) swap(ch[ch[x][1]][0], ch[ch[x][1]][1]), tag[ch[x][1]] ^= 1;
          tag[x] = 0;
        }
      }
    
      void update(int x) {
        if (!isroot(x)) update(fa[x]);
        pushdown(x);
      }
    
      void rotate(int x) {
        int y = fa[x], z = fa[y], chx = getch(x), chy = getch(y);
        fa[x] = z;
        if (!isroot(y)) ch[z][chy] = x;
        ch[y][chx] = ch[x][chx ^ 1];
        fa[ch[x][chx ^ 1]] = y;
        ch[x][chx ^ 1] = y;
        fa[y] = x;
        maintain(y);
        maintain(x);
        maintain(z);
      }
    
      void splay(int x) {
        update(x);
        for (int f = fa[x]; f = fa[x], !isroot(x); rotate(x))
          if (!isroot(f)) rotate(getch(x) == getch(f) ? f : x);
      }
    
      void access(int x) {
        for (int f = 0; x; f = x, x = fa[x])
          splay(x), siz2[x] += siz[ch[x][1]] - siz[f], ch[x][1] = f, maintain(x);
      }
    
      void makeroot(int x) {
        access(x);
        splay(x);
        swap(ch[x][0], ch[x][1]);
        tag[x] ^= 1;
      }
    
      int find(int x) {
        access(x);
        splay(x);
        while (ch[x][0]) x = ch[x][0];
        splay(x);
        return x;
      }
    } st;
    
    int n, q, x, y;
    char op;
    
    int main() {
      scanf("%d%d", &n, &q);
      while (q--) {
        scanf(" %c%d%d", &op, &x, &y);
        if (op == 'A') {
          st.makeroot(x);
          st.makeroot(y);
          st.fa[x] = y;
          st.siz2[y] += st.siz[x];
        }
        if (op == 'Q') {
          st.makeroot(x);
          st.access(y);
          st.splay(y);
          st.ch[y][0] = st.fa[x] = 0;
          st.maintain(x);
          st.makeroot(x);
          st.makeroot(y);
          printf("%lld\n", (ll)(st.siz[x] * st.siz[y]));
          st.makeroot(x);
          st.makeroot(y);
          st.fa[x] = y;
          st.siz2[y] += st.siz[x];
        }
      }
      return 0;
    }
    ```

### Exercises

-   [luogu P4299 Capital](https://www.luogu.com.cn/problem/P4299)
-   [SPOJ QTREE5 - Query on a tree V](https://www.spoj.com/problems/QTREE5)
