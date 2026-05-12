author: Backl1ght

An Euler Tour Tree (ETT) is a data structure for solving **dynamic tree** problems. ETT converts operations on a dynamic tree into range operations on its DFS sequence, then uses another data structure to maintain those sequence range operations, thereby maintaining the dynamic tree operations. For example, ETT converts adding an edge in a dynamic tree into several sequence split and sequence merge operations. If sequence split and merge can be maintained, then edge insertion in the dynamic tree can be maintained.

LCT is also a data structure for dynamic tree problems, and it is more common than ETT. LCT is better suited for maintaining information on tree paths, while ETT is better suited for maintaining **subtree** information. For example, ETT can maintain subtree minimums, whereas LCT cannot.

ETT can be maintained with any data structure, as long as that data structure supports the required sequence range operations and meets the complexity requirements. Usually, balanced binary search trees such as splay trees or treaps are used to maintain the sequence. These data structures support range operations in $O(\log n)$ time, so dynamic tree operations can also be maintained in $O(\log n)$ time. If a multiway balanced search tree such as a B-tree is used to maintain range operations, even better complexity is possible.

ETT can be understood as an idea: maintain a sequence that has a one-to-one correspondence with the original tree, thereby maintaining the original tree. This article only introduces some feasible implementations and applications of this idea.

## Euler Tour Representation of a Tree

If each tree edge is regarded as two directed edges, then a tree can be represented as an Euler tour of a directed graph. This is called the tree's Euler tour representation (ETR).

The sequence maintained below is actually a variant of ETR: vertices in the tree are treated as self-loops and added to the ETR. However, since the original paper did not give it a new name, we will still call it ETR.

The Euler tour representation of a tree $T$ can be obtained by the following algorithm:

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{A rooted tree }T\\
2 & \textbf{Output. } \text{The dfs sequence of rooted tree }T\\
3 & \operatorname{ET}(u)\\
4 & \qquad \text{visit vertex }u\\
5 & \qquad \text{for all child } v \text{ of } u\\
6 & \qquad \qquad \text{visit directed edge } u \to v\\
7 & \qquad \qquad \operatorname{ET}(v)\\
8 & \qquad \qquad \text{visit directed edge } v \to u\\
\end{array}
$$

For tree $T$, the Euler tour representation $\operatorname{ETR}(T)$ is initially empty. During DFS, whenever a vertex or a directed edge is visited, append it to the end of $\operatorname{ETR}(T)$. This gives $\operatorname{ETR}(T)$.

If $T$ contains $n$ vertices, then it contains $2n - 2$ directed edges. During DFS, every vertex and every directed edge is visited once, so the length of $\operatorname{ETR}(T)$ is $3n - 2$.

Treat vertex $u$ as a self-loop. Then $\operatorname{ETR}(T)$ can be viewed as an Euler tour in a directed graph. We can cut the Euler tour at some position and view it as a chain formed by edges connected head-to-tail; we can also glue such a chain back together at the cut to restore the Euler tour; and we can add some new edges to splice two such chains into a new Euler tour.

In the following, unless otherwise stated, the maintained sequence is the tree's Euler tour representation.

## Basic ETT Operations

The following three operations are basic ETT operations. Each can be converted into a constant number of sequence operations, so their complexities are of the same order as the sequence operations.

The implementation given here is only one feasible approach. Any approach is fine as long as the modified corresponding sequence can be assembled using a constant number of sequence operations.

### MakeRoot(u)

This is the reroot operation. In ETT, rerooting is converted into one sequence split operation and one sequence merge operation. It can also be understood as one interval rotation operation.

Let the tree containing vertex $u$ be $T$, and let its current root be $r$. We want to change the root to $u$. Let the sequence corresponding to $T$ be $L$. Split $L$ at $(u, u)$ into sequences $L^1$ and $L^2$, where the former contains, in $L$, the elements before $(u, u)$ together with $(u, u)$, and the latter contains the remaining elements. Then merging $L^2$ and $L^1$ in order gives the sequence corresponding to the tree after rerooting.

This can be understood as rotating an Euler tour. An Euler tour is a cycle, and rotating it does not change the structure of the Euler tour, nor the structure of the tree; it only rotates vertex $u$ to the root position.

### Insert(u, v)

This is the edge insertion operation. In ETT, adding an edge is converted into two sequence split operations and five sequence merge operations.

Let the tree containing vertex $u$ be $T_1$, and the tree containing vertex $v$ be $T_2$. After adding the edge, the two trees merge into one tree $T$. Let the sequence corresponding to $T_1$ be $L_1$, and the sequence corresponding to $T_2$ be $L_2$.

Split $L_1$ at $(u, u)$ into sequences $L_1^1$ and $L_1^2$, where the former contains, in $L_1$, the elements before $(u, u)$ together with $(u, u)$, and the latter contains the remaining elements. Similarly, split $L_2$ at $(v, v)$ into $L_2^1$ and $L_2^2$. Then merging $L_1^2, L_1^1, [(u, v)], L_2^2, L_2^1,  [(v, u)]$ in order gives the sequence corresponding to tree $T$, namely $L$.

This can be understood as two reroot operations, then cutting the two Euler tours at their current roots, and finally using the two newly added directed edges to splice the two Euler tours into a new Euler tour.

### Delete(u, v)

This is the edge deletion operation. In ETT, deleting an edge is converted into four sequence split operations and one sequence merge operation.

Let the tree containing edges $(u, v)$ and $(v, u)$ be $T$, and let its corresponding sequence be $L$. After deleting the edge, $T$ splits into two trees.

Split $L$ into $L_1, [(u, v)], L_2, [(v, u)], L_3$. The sequences corresponding to the two trees formed by deleting the edge are $L_2$ and the concatenation of $L_1, L_3$. Note that in sequence $L$, $[(u, v)]$ may appear after $[(v, u)]$; in that case, swap the values of $u$ and $v$ first, then proceed.

This can be understood as cutting one Euler tour at two directed edges to form two chains, then connecting each chain's ends to form two new Euler tours.

## Implementation

The following introduces an ETT implementation using a non-rotating treap as an example. The reader should already understand how to use a non-rotating treap to maintain range operations.

`Split` and `Merge` are both basic operations of non-rotating treaps, so they are not repeated here.

### SplitUp2(u)

Suppose the sequence containing $u$ is $L$. Split $L$ at $u$ into sequences $L^1$ and $L^2$, where the former contains, in $L$, the elements before $u$ together with $u$, and the latter contains the remaining elements.

If each node of the treap additionally maintains its parent, we can compute the position in the sequence of the element corresponding to a treap node in $O(\log n)$ time. Then `Split` by that position implements the function above.

We can also split bottom-up to implement this functionality, which is more efficient than the method above. Specifically, while climbing from the node corresponding to $u$ toward the root, the binary-search-tree property determines, in $L$, whether each node is before or after $u$. From this, we can compute the position of $u$ in the sequence and determine which split tree each node belongs to.

```cpp
/*
 * Bottom up split treap p into 2 treaps a and b.
 *   - a: a treap containing nodes with position less than or equal to p.
 *   - b: a treap containing nodes with postion greater than p.
 *
 * In the other word, split sequence containning p into two sequences, the first
 * one contains elements before p and element p, the second one contains
 * elements after p.
 */
static std::pair<Node*, Node*> SplitUp2(Node* p) {
  Node *a = nullptr, *b = nullptr;
  b = p->right_;
  if (b) b->parent_ = nullptr;
  p->right_ = nullptr;

  bool is_p_left_child_of_parent = false;
  bool is_from_left_child = false;
  while (p) {
    Node* parent = p->parent_;

    if (parent) {
      is_p_left_child_of_parent = (parent->left_ == p);
      if (is_p_left_child_of_parent) {
        parent->left_ = nullptr;
      } else {
        parent->right_ = nullptr;
      }
      p->parent_ = nullptr;
    }

    if (!is_from_left_child) {
      a = Merge(p, a);
    } else {
      b = Merge(b, p);
    }

    is_from_left_child = is_p_left_child_of_parent;
    p->Maintain();
    p = parent;
  }

  return {a, b};
}
```

### SplitUp3(u)

Suppose the sequence containing $u$ is $L$. Split $L$ at $u$ into sequence $L^1$, $u$, and sequence $L^2$, where the former contains, in $L$, the elements before $u$, and the latter contains the remaining elements.

This can be obtained by making a small modification to `SplitUp2`.

### MakeRoot(u)

This follows directly from `SplitUp2` and `Merge`.

```cpp
void MakeRoot(int u) {
  Node* vertex_u = vertices_[u];
  auto [L1, L2] = Treap::SplitUp2(vertex_u);
  Treap::Merge(L2, L1);
}
```

### Insert(u, v)

This follows directly from `SplitUp2` and `Merge`.

```cpp
void Insert(int u, int v) {
  Node* vertex_u = vertices_[u];
  Node* vertex_v = vertices_[v];

  Node* edge_uv = AllocateNode(u, v);
  Node* edge_vu = AllocateNode(v, u);
  tree_edges_[u][v] = edge_uv;
  tree_edges_[v][u] = edge_vu;

  auto [L11, L12] = Treap::SplitUp2(vertex_u);
  auto [L21, L22] = Treap::SplitUp2(vertex_v);

  Node* L = L12;
  L = Treap::Merge(L, L11);
  L = Treap::Merge(L, edge_uv);
  L = Treap::Merge(L, L22);
  L = Treap::Merge(L, L21);
  L = Treap::Merge(L, edge_vu);
}
```

### Delete(u, v)

This follows directly from `SplitUp3` and `Merge`.

```cpp
void Delete(int u, int v) {
  Node* edge_uv = tree_edges_[u][v];
  Node* edge_vu = tree_edges_[v][u];
  tree_edges_[u].erase(v);
  tree_edges_[v].erase(u);

  int position_uv = Treap::GetPosition(edge_uv);
  int position_vu = Treap::GetPosition(edge_vu);
  if (position_uv > position_vu) {
    std::swap(edge_uv, edge_vu);
    std::swap(position_uv, position_vu);
  }

  auto [L1, uv, _] = Treap::SplitUp3(edge_uv);
  auto [L2, vu, L3] = Treap::SplitUp3(edge_vu);
  Treap::Merge(L1, L3);

  FreeNode(edge_uv);
  FreeNode(edge_vu);
}
```

## Maintaining Connectivity

Vertices $u$ and $v$ are connected if and only if they belong to the same tree $T$, that is, $(u, u)$ and $(v, v)$ belong to $\operatorname{ETR}(T)$. This can be determined by checking whether the treap nodes corresponding to vertices $u$ and $v$ have the same treap root.

### Example Problem [P2147 [SDOI2008] Cave Survey](https://www.luogu.com.cn/problem/P2147)

A template problem for maintaining connectivity.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/ds/code/ett/ett_connectivity.cpp"
    ```

## Maintaining Subtree Information

Below, subtree size is used as an example.

For each element in $\operatorname{ETR}(T)$, if it corresponds to a vertex in the tree, set its weight to $1$; if it corresponds to an edge in the tree, set its weight to $0$. Then the number of vertices in tree $T$ can be viewed as the sum of weights of elements in $\operatorname{ETR}(T)$. Maintaining subtree sizes only requires maintaining sequence weight sums, which is a classic operation for non-rotating treaps.

Similarly, operations such as subtree minimum can be converted into classic balanced-tree operations such as sequence minimum and then maintained.

### Example Problem [LOJ #2230. BJOI2014 Great Fusion](https://loj.ac/p/2230)

??? note "Reference Code"
    ```cpp
    --8<-- "docs/ds/code/ett/ett_subtree_size.cpp"
    ```

## Maintaining Tree Path Information

A common technique is to use properties of bracket sequences to convert tree path information into interval information. Then a data structure can maintain the sequence, thereby maintaining tree path information. However, this technique requires the maintained information to be **subtractable**.

The sequence operations corresponding to the dynamic tree operations introduced above may move a right bracket in the bracket sequence before its left bracket. Therefore, when maintaining information such as path vertex-weight sums, extra care is needed: operations must not change the relative order of corresponding left and right brackets. This may require rethinking the sequence operations corresponding to dynamic tree operations, or even rethinking which DFS order to maintain.

In addition, ETT has difficulty maintaining tree path updates.

### Example Problem [Interstellar Exploration](https://hydro.ac/p/bzoj-P3786)

In this problem, the only dynamic tree operation is changing the parent. This can be viewed as deleting an edge and then adding an edge, but doing so may change the relative order of the corresponding brackets.

We can convert vertex weights into edge weights, maintain the tree's bracket sequence, and convert the change-parent operation into moving the bracket sequence corresponding to the entire subtree to just after the parent's left bracket.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/ds/code/ett/ett_1.cpp"
    ```

## References

-   Dynamic trees as search trees via euler tours, applied to the network simplex algorithm - Robert E. Tarjan
-   Randomized fully dynamic graph algorithms with polylogarithmic time per operation - Henzinger et al.
