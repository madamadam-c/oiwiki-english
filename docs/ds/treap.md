author: Dev-XYS, ttzytt, Sora233, qwqAutomaton

Prerequisites: [Plain binary search tree](./bst.md), [Heap basics](./heap.md).

## Introduction

A treap is a **weakly balanced** **binary search tree**.

Besides the maintained **value** ($\textit{val}$), each treap node also has an additional random **priority** ($\textit{priority}$). The values satisfy the binary-search-tree property, while the priorities satisfy the heap property (either a min-heap or a max-heap).

The binary-search-tree property means:

-   The values ($\textit{val}$) of all nodes in the left subtree are smaller than the parent node's value.
-   The values ($\textit{val}$) of all nodes in the right subtree are greater than the parent node's value.

The heap property is:

-   A child node's priority ($\textit{priority}$) is greater or smaller than its parent's priority, depending on whether it is a min-heap or a max-heap.

It is not hard to see that if the same value is used for both structures, combining them would turn the tree into a chain. Therefore, on top of the search tree, we introduce another value $\textit{priority}$ for the heap. For $\textit{val}$, we maintain the search-tree property; for $\textit{priority}$, we maintain the heap property. The value of $\textit{priority}$ is assigned randomly.

The following figure is an example of a treap. Here a min-heap is used, so the root node has the smallest priority.

![An example of a treap](./images/treap-treap-example.svg)

Why do we go to all this trouble to make the data structure satisfy both tree and heap properties, and to assign heap values randomly?

To understand this, first consider the problem with a plain binary search tree. When inserting a new node into a plain search tree, we recursively start from the root of the search tree. If the new node is smaller than the current node, we recurse to the left; otherwise, we recurse to the right.

Finally, when we find that the current node has no child in the needed direction, we make the new node the left or right child of the current node according to its value.

If the values of inserted nodes are random, or equivalently if insertions are random, the height of this plain search tree is small, close to $\log n$ where $n$ is the number of nodes, and each level contains many nodes. In other words, its shape is quite "fat". The treap in the figure above is an example. Therefore, the complexity of any operation at this point is around $O(\log n)$.

However, this is only the complexity in the random case. If we insert nodes into a plain search tree in the following highly ordered sequence:

```plain
1 2 3 4 5
```

then the tree degenerates into a chain, becoming very "thin and long". Every inserted node is larger than the previous ones, so it is always placed as a right child:

![Example of degeneration into a chain](./images/treap-search-tree-chain.svg)

It is not hard to see that query complexity also changes from $O(\log n)$ to $O(n)$.

To solve this problem and reach a relatively "balanced" state, a treap maintains random priorities that satisfy the heap property. This "shuffles" the insertion order of nodes, allowing the binary search tree to achieve the desired complexity and avoiding degeneration into a chain.

## Proof of Treap Complexity

Since the complexity of treap operations is related to the depth of the operated node, we first prove that the expected depth of every node is $O(\log n)$.

### Notation

For convenience, we use the following notation:

-   $n$ is the number of nodes.
-   In a treap node, the field satisfying the binary-search-tree property is called the **value**, and the field satisfying the heap property, namely the random one, is called the **priority**. Without loss of generality, assume priorities satisfy the min-heap property.
-   $x_k$ denotes the node with the $k$-th smallest value.
-   $X_{i,j}$ denotes the set $\{x_i,x_{i+1},\cdots,x_{j-1},x_j\}$, namely the set of nodes from the $i$-th to the $j$-th after sorting by value in ascending order.
-   $\operatorname{dep}(x)$ denotes the depth of node $x$. The root node has depth $0$.
-   $Y_{i,j}$ is an indicator random variable. When $x_i$ is an ancestor of $x_j$, it is $1$, and otherwise $0$. In particular, $Y_{i,i}=0$.
-   $\Pr(A)$ denotes the probability that event $A$ occurs.

### Proof of Expected Node Depth

Since the depth of node $x_i$ equals the number of its ancestors, we have

$$
\operatorname{dep}(x_i)=\sum_{k=1}^nY_{k,i}.
$$

By linearity of expectation,

$$
E(\operatorname{dep}(x_i))=E\left(\sum_{k=1}^nY_{k,i}\right)=\sum_{k=1}^nE(Y_{k,i}).
$$

Since $Y_{k,i}$ is an indicator random variable, its expectation equals the probability that it is $1$. Therefore,

$$
E(\operatorname{dep}(x_i))=\sum_{k=1}^n\Pr(Y_{k,i}=1).
$$

We first prove a lemma: $Y_{i,j}=1$ if and only if $x_i$ has the smallest priority in $X_{i,j}$.

??? note "Proof of the lemma"
    Consider the cases for $x_i$ and $x_j$.
    
    1.  If $x_i$ is the root: since priorities satisfy the min-heap property, $x_i$ has the smallest priority, and for any $x_j$, $x_i$ is an ancestor of $x_j$.
    2.  If $x_j$ is the root: similarly, $x_j$ has the smallest priority, so $x_i$ does not have the smallest priority in $X_{i,j}$; also, $x_i$ is not an ancestor of $x_j$.
    3.  If $x_i$ and $x_j$ are in the two subtrees of the root, one on the left and one on the right, then the root $r\in X_{i,j}$. Thus $x_i$ cannot have the smallest priority in $X_{i,j}$, because the root's priority is smaller. Also, since $x_i$ and $x_j$ are in different subtrees, $x_i$ is not an ancestor of $x_j$.
    4.  If $x_i$ and $x_j$ are in the same subtree of the root, we can treat that subtree alone as a new treap and recursively apply the proof above.

By the lemma, the expected depth can be transformed into

$$
E(\operatorname{dep}(x_i))=\sum_{k=1}^n\Pr(x_k=\min X_{i,k}\land k\neq i).
$$

Because node priorities are random, we assume every node in $X_{i,j}$ is equally likely to have the smallest priority. Then

$$
\begin{aligned}
E(\operatorname{dep}(x_i))&=\sum_{k=1}^n\Pr(x_k=\min X_{i,k}\land k\neq i)\\
&=\sum_{k=1}^{n}\Pr(x_k=\min X_{i,k})-1\\
&=\sum_{k=1}^n\dfrac{1}{|i-k|+1}-1\\
&=\sum_{k=1}^{i-1}\dfrac{1}{i-k+1}+\sum_{k=i+1}^n\dfrac{1}{k-i+1}\\
&=\sum_{j=2}^i\dfrac 1j+\sum_{j=2}^{n-i+1}\dfrac 1j\\
&\le 2\sum_{j=2}^n\dfrac 1j < 2\sum_{j=2}^n\int_{j-1}^j\dfrac 1x\mathrm dx\\
&=2\int_1^n\dfrac 1x\mathrm dx=2\ln n=O(\log n).
\end{aligned}
$$

Therefore, the expected depth of every node is $O(\log n)$.

The operations of a plain binary search tree all have complexity $O(h)$, and maintaining the heap property in a treap also costs $O(h)$. Therefore, the expected complexity of all treap operations is $O(\log n)$.

???+ note "Intuitive understanding of expected complexity"
    First, we need to realize that a node's $\textit{priority}$ attribute is directly related to its level. Recall the heap property:
    
    -   A child node's value ($\textit{priority}$) is greater or smaller than its parent's value, depending on whether it is a min-heap or a max-heap.
    
    We can see that nodes at smaller depths, such as the root of the whole tree, also have smaller $\textit{priority}$ values in a min-heap. In a plain search tree, nodes inserted earlier are also more likely to be at smaller depths. We can understand the $\textit{priority}$ attribute as being associated with insertion order. This explains why a treap can use $\textit{priority}$ to shuffle the order in which nodes are inserted.

When inserting a new node into a treap, both the tree property and the heap property must be maintained. The search-tree property can be maintained during insertion, while the heap property can be maintained in two ways: rotations, or split and merge. Treaps using these two methods are called **rotating treaps** and **rotationless treaps**, respectively.

## Rotating Treap

A **rotating treap** maintains balance by rotations. Similar to rotations in an AVL tree, they are divided into **left rotations** and **right rotations**. That is, while preserving the binary-search-tree condition, the treap is balanced according to heap priorities.

For ordinary balanced-tree problems, rotating treaps have relatively small constant factors among balanced trees.

The code in the following explanation implements a rotating treap with pointers. A complete array-based implementation is included at the end.

???+ info "Info"
    In the code, `rank` represents the priority mentioned above, the $\textit{priority}$ attribute. It satisfies the min-heap property.

### Node Structure

```cpp
struct Node {
  Node *ch[2];  // addresses of the two child nodes
  int val, rank;
  int rep_cnt;  // number of occurrences of the current value (val)
  int siz;      // size of the subtree rooted at the current node

  Node(int val) : val(val), rep_cnt(1), siz(1) {
    ch[0] = ch[1] = nullptr;
    rank = rand();
    // Note that rank is assigned randomly during initialization.
  }

  void upd_siz() {
    // Recompute siz after rotation or deletion.
    siz = rep_cnt;
    if (ch[0] != nullptr) siz += ch[0]->siz;
    if (ch[1] != nullptr) siz += ch[1]->siz;
  }
};
```

### Rotation

Rotation is a very important treap operation. It is mainly used to adjust the depths of different nodes while preserving the treap's tree property, thereby maintaining the heap property.

Left rotation and right rotation may not be especially easy to distinguish. Here are two relatively clear characteristics:

Meaning of a rotation:

-   Without affecting the search-tree property, make the subtree opposite to the rotation direction become the root. For example, a left rotation makes the right subtree become the root.
-   The property is preserved, and after rotation, the child in the same direction as the rotation becomes the original root. For example, after a left rotation, the left child is the root before rotation.

Left rotation and right rotation are inverse operations, as shown below.

![Rotation operation](./images/treap-rotate.svg)

```cpp
enum rot_type { LF = 1, RT = 0 };

void _rotate(Node *&cur,
             rot_type dir) {  // dir indicates the rotation direction: 0 for right, 1 for left
  // Note that cur is passed as a reference to a pointer. Changing this cur also
  // changes the corresponding variable. If this cur is a child node of another
  // tree, following ch from that tree will still reach the updated node here.

  // The following comments explain the left-rotation case.
  Node *tmp = cur->ch[dir];  // Let C become the root.
                             // tmp is a temporary node pointer that points to
                             // the node that will become the new root.

  /* Left rotation: make the right child become the root.
   *         A                 C
   *        / \               / \
   *       B  C    ---->     A   E
   *         / \            / \
   *        D   E          B   D
   */
  cur->ch[dir] = tmp->ch[!dir];    // Make A's right child become D.
  tmp->ch[!dir] = cur;             // Make C's left child become A.
  cur->upd_siz(), tmp->upd_siz();  // Update size information.
  cur = tmp;  // Finally assign the temporary C-tree variable to the current root.
}
```

### Insertion

It is similar to insertion in an ordinary binary search tree, but rotations are needed during insertion to maintain the heap property of priorities.

```cpp
void _insert(Node *&cur, int val) {
  if (cur == nullptr) {
    // Create the node directly if it does not exist.
    cur = new Node(val);
    return;
  } else if (val == cur->val) {
    // If a node with this value already exists, increase the duplicate count.
    cur->rep_cnt++;
    cur->siz++;
  } else if (val < cur->val) {
    // Maintain the search-tree property: insert to the left if val is smaller.
    _insert(cur->ch[0], val);
    if (cur->ch[0]->rank < cur->rank) {
      // In a min-heap, upper nodes must have smaller priorities.
      // Since the newly inserted left child is smaller than the parent, make it the parent.
      _rotate(cur, RT);  // To rotate the left child upward, use a right rotation.
    }
    cur->upd_siz();  // Size changes after insertion, so update it.
  } else {
    _insert(cur->ch[1], val);
    if (cur->ch[1]->rank < cur->rank) {
      _rotate(cur, LF);
    }
    cur->upd_siz();
  }
}
```

### Deletion

Deletion is mainly a case analysis: different cases require different handling. After deletion, the tree size changes, so remember to update it. If the node to be deleted has both left and right subtrees, we must decide which node becomes the parent after deletion, keeping the node with smaller `rank` above.

```cpp
void _del(Node *&cur, int val) {
  if (val > cur->val) {
    _del(cur->ch[1], val);
    // A larger value is in the right subtree, and vice versa.
    cur->upd_siz();
  } else if (val < cur->val) {
    _del(cur->ch[0], val);
    cur->upd_siz();
  } else {
    if (cur->rep_cnt > 1) {
      // If the node to delete has duplicates, just decrease the count.
      cur->rep_cnt--, cur->siz--;
      return;
    }
    uint8_t state = 0;
    state |= (cur->ch[0] != nullptr);
    state |= ((cur->ch[1] != nullptr) << 1);
    // 00: none; 01: left only; 10: right only; 11: both.
    Node *tmp = cur;
    switch (state) {
      case 0:
        delete cur;
        cur = nullptr;
        // If there is no child, delete this node directly.
        break;
      case 1:  // left child only
        cur = tmp->ch[0];
        // Make the root its left child, then delete the original root.
        // Note that tmp was copied from cur, while cur is a reference.
        delete tmp;
        break;
      case 2:  // right child only
        cur = tmp->ch[1];
        delete tmp;
        break;
      case 3:
        rot_type dir = cur->ch[0]->rank < cur->ch[1]->rank
                           ? RT
                           : LF;  // dir is the child with the smaller rank.
        _rotate(cur, dir);  // This rotates the child with smaller priority upward.
                            // rt is 0 and lf is 1, opposite to actual subtree indices.
        _del(
            cur->ch[!dir],
            val);  // After rotation, the original root is on the rotation-direction side,
                   // so continue deleting that original root.
                   // If the node to delete is near the top of the whole tree, these
                   // rotations keep moving it downward until it has no subtree, or only
                   // one subtree, and then it is deleted.
        cur->upd_siz();
        // Deletion changes the size.
        break;
    }
  }
}
```

### Query Rank by Value

Meaning of the operation: query the rank of value `val` in the subtree rooted at `cur`, namely the number of nodes in this subtree with value less than `val`, plus 1.

```cpp
int _query_rank(Node *cur, int val) {
  int less_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
  // Number of nodes in this tree that are less than val.
  if (val == cur->val)
    // If this node is the queried node.
    return less_siz + 1;
  else if (val < cur->val) {
    if (cur->ch[0] != nullptr)
      return _query_rank(cur->ch[0], val);
    else
      return 1;  // If the left subtree is empty, this value is smaller than the minimum.
  } else {
    if (cur->ch[1] != nullptr)
      // If the queried value is larger than this node, both this node's left subtree
      // and this node itself must be smaller than the queried value.
      // Add these two parts, then add the result found in the right subtree.
      // That result is the rank of val in the subtree rooted at the right child.
      return less_siz + cur->rep_cnt + _query_rank(cur->ch[1], val);
    else
      return cur->siz + 1;
    // If there is no right subtree, use the whole tree + 1, equivalent to less_siz + cur->rep_cnt + 1.
  }
}
```

### Query Value by Rank

To query a value by rank, we first need to know how to determine which part of the tree contains the target node:

The following table gives a way to decide:

| Left subtree | Root/current node | Right subtree |
| ----------- | ---------------------------------- | ---------------------- |
| rank ≤ size of left subtree | rank > size of left subtree and rank ≤ size of left subtree + duplicate count of root | rank > size of left subtree + duplicate count of root |

Note that if the target is in the right subtree, the original `rank` must be adjusted during recursion. Recursing there is equivalent to querying a rank within the right subtree. To convert the rank to be relative to the right subtree, subtract the size of the left subtree and the duplicate count of the root from the original `rank`.

You can imagine all nodes as a sorted array or number line, as below:

    1 -> |left subtree nodes|root node|right subtree nodes| -> n
                               ^
                               rank to query
                         convert to a rank based on the right subtree
    1 -> |right subtree nodes| -> n
           ^
           rank to query

The conversion simply subtracts the size of the left subtree and the duplicate count of the root from the rank.

```cpp
int _query_val(Node *cur, int rank) {
  // Query the value of the node with rank rank in the tree.
  int less_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
  // less_siz is the size of the left subtree.
  if (rank <= less_siz)
    return _query_val(cur->ch[0], rank);
  else if (rank <= less_siz + cur->rep_cnt)
    return cur->val;
  else
    return _query_val(cur->ch[1], rank - less_siz - cur->rep_cnt);  // See above.
}
```

### Query the First Node Smaller Than `val`

Note that this uses a class-level variable, `q_prev_tmp`.

This value is changed only when `val` is greater than the current node's value. Therefore, returning this variable returns the last current-node value that was smaller than `val`.

```cpp
int _query_prev(Node *cur, int val) {
  if (val <= cur->val) {
    // The current node is still not smaller than val, so search in the left subtree.
    if (cur->ch[0] != nullptr) return _query_prev(cur->ch[0], val);
  } else {
    // q_prev_tmp is updated only when execution enters this else branch.
    q_prev_tmp = cur->val;
    // The current node is already smaller than val, but it may not be the largest one, so continue searching the right subtree.
    if (cur->ch[1] != nullptr) _query_prev(cur->ch[1], val);
    // The following recursion may no longer change q_prev_tmp, so return it directly.
    // In short, this returns cur->val from the last time this else branch was entered.
    return q_prev_tmp;
  }
  return NIL;
}
```

### Query the First Node Greater Than `val`

This is very similar to the previous operation, except the greater-than and less-than signs are swapped.

```cpp
int _query_nex(Node *cur, int val) {
  if (val >= cur->val) {
    if (cur->ch[1] != nullptr) return _query_nex(cur->ch[1], val);
  } else {
    q_nex_tmp = cur->val;
    if (cur->ch[0] != nullptr) _query_nex(cur->ch[0], val);
    return q_nex_tmp;
  }
  return NIL;
}
```

## Rotationless Treap

The way a rotationless treap operates makes it naturally support features such as maintaining sequences and persistence.

A **rotationless treap** is also called a split-merge treap. It has only two core operations: **split** and **merge**. With these two operations, many other operations can often be implemented more conveniently than with a rotating treap. We introduce the two operations below.

???+ note "Note"
    A discussion of rotationless treaps should mention **FHQ-Treap** by Fan Haoqiang: a persistent rotationless treap that supports interval operations. For more, refer to the PPT *Fan Haoqiang on Data Structures*.

### Split

#### Split by Value

The split procedure takes two parameters: the root pointer $\textit{cur}$ and the key value $\textit{key}$. It splits the treap pointed to by the root pointer into two treaps. All node values ($\textit{val}$) in the first treap are less than or equal to $\textit{key}$, and all node values in the second treap are greater than $\textit{key}$.

The procedure first checks whether $\textit{key}$ is smaller than the value of $\textit{cur}$. If it is, then $\textit{cur}$ and its entire right subtree are greater than $\textit{key}$, so they belong to the second treap. Of course, part of the left subtree may also have values greater than $\textit{key}$, so we must continue recursively splitting the left subtree. For the part of the left subtree that is greater than $\textit{key}$, we make it the left subtree of $\textit{cur}$; then all nodes under $\textit{cur}$ are greater than $\textit{key}$.

Correspondingly, if $\textit{key}$ is greater than or equal to the value of $\textit{cur}$, then the entire left subtree of $\textit{cur}$ and cur itself are less than or equal to $\textit{key}$, so they belong to the first treap after splitting. Also, part of $\textit{cur}$'s right subtree may be less than or equal to $\textit{key}$, so we must continue recursively splitting the right subtree. We make the part less than or equal to $\textit{key}$ the right subtree of $\textit{cur}$; then all nodes under $\textit{cur}$ are less than or equal to $\textit{key}$.

The following figure shows splitting by value when the value of $\textit{cur}$ is less than or equal to $\textit{key}$.[^ref1]

![Split by value](./images/treap-none-rot-split-by-val.svg)

```cpp
pair<Node *, Node *> split(Node *cur, int key) {
  if (cur == nullptr) return {nullptr, nullptr};
  if (cur->val <= key) {
    // cur and its left subtree must belong to the first tree after splitting.
    auto temp = split(cur->ch[1], key);
    // But part of its right subtree may also be smaller than key.
    cur->ch[1] = temp.first;
    // Take out the part smaller than key and make it cur's right subtree, so all of
    // cur is smaller than key. The remaining part of the right subtree becomes the
    // second treap after splitting.
    cur->upd_siz();
    // The tree size changes after splitting, so update it.
    return {cur, temp.second};
  } else {
    // Same as above.
    auto temp = split(cur->ch[0], key);
    cur->ch[0] = temp.second;
    cur->upd_siz();
    return {temp.first, cur};
  }
}
```

#### Split by Rank

Compared with splitting by value, this operation is more like querying a value by rank in a rotating treap, where a node's rank is the number of nodes in the tree with values smaller than this node's value, plus $+ 1$.

This function takes two parameters, the node pointer $\textit{cur}$ and the rank $\textit{rk}$, and returns the three treaps after splitting.

In the first treap, every node has rank less than $\textit{rk}$. The second treap has rank equal to $\textit{rk}$ and contains only one node; there cannot be multiple equal nodes, because if duplicates exist they are counted in `cnt` in the `Node` structure. The third treap contains nodes with greater ranks.

The key point of this operation is determining which part of the tree contains the node with rank $\textit{cur}$. This is also the important part of querying by rank in a rotating treap, and was explained in detail earlier, so we will not elaborate here.

The recursive part of this operation is also very similar to splitting by value, so we will not repeat the details.

```cpp
tuple<Node *, Node *, Node *> split_by_rk(Node *cur, int rk) {
  if (cur == nullptr) return {nullptr, nullptr, nullptr};
  int ls_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
  if (rk <= ls_siz) {
    // The node with rank rk is in the left subtree.
    Node *l, *mid, *r;
    tie(l, mid, r) = split_by_rk(cur->ch[0], rk);
    cur->ch[0] = r;  // The returned third treap contains ranks greater than rk.
    // After setting cur's left subtree to r, all nodes in cur have ranks greater than rk.
    cur->upd_siz();
    return {l, mid, cur};
  } else if (rk <= ls_siz + cur->cnt) {
    // The node equal to cur is the current node.
    Node *lt = cur->ch[0];
    Node *rt = cur->ch[1];
    cur->ch[0] = cur->ch[1] = nullptr;
    // After splitting, the second treap has only one node, so set its subtrees to null.
    return {lt, cur, rt};
  } else {
    // The node with rank rk is in the right subtree.
    // The recursive process is the same as above.
    Node *l, *mid, *r;
    tie(l, mid, r) = split_by_rk(cur->ch[1], rk - ls_siz - cur->cnt);
    cur->ch[1] = l;
    cur->upd_siz();
    return {cur, mid, r};
  }
}
```

### Merge

The merge procedure takes two parameters: the root pointer $\textit{u}$ of the left treap and the root pointer $\textit{v}$ of the right treap. It must satisfy that all node values in $\textit{u}$ are less than or equal to all node values in $\textit{v}$. In general, the two treaps being merged were originally split from one treap, so it is not hard to ensure that all node values in $\textit{u}$ are less than those in $\textit{v}$.

In a rotating treap, we use rotations to maintain that $\textit{priority}$ satisfies the heap property, while rotations must not change the tree property. In a rotationless treap, we use merge to achieve the same effect.

Because the two treaps are already ordered, when merging we only need to decide which tree is placed "above" and which is placed "below", that is, which tree should become a subtree. Clearly, by the heap property, the one with smaller $\textit{priority}$ should be placed above, since we use a min-heap here.

At the same time, we must also satisfy the search-tree property. Therefore, if $\textit{u}$'s root has smaller $\textit{priority}$ than $\textit{v}$'s, then $\textit{u}$ becomes the new root. Since values in $\textit{v}$ are greater than those in $\textit{u}$, it should be merged with $\textit{u}$'s right subtree. Otherwise, $\textit{v}$ becomes the new root, and since values in $u$ are smaller than those in $\textit{v}$, $v$'s left subtree is merged with them.

```cpp
Node *merge(Node *u, Node *v) {
  // The two input trees already internally satisfy the search-tree property,
  // and all node values in u are less than all node values in v.
  // Therefore, merging only needs to maintain the heap property.
  // A min-heap is used here.
  if (u == nullptr && v == nullptr) return nullptr;
  if (u != nullptr && v == nullptr) return u;
  if (v != nullptr && u == nullptr) return v;

  if (u->prio < v->prio) {
    // u has the smaller prio, so u should be the parent.
    u->ch[1] = merge(u->ch[1], v);
    // Since v is greater than u, make v part of u's right subtree.
    u->upd_siz();
    return u;
  } else {
    // v is smaller, so v should be the parent.
    v->ch[0] = merge(u, v->ch[0]);
    // u is smaller than v, so the recursive parameters are arranged this way.
    v->upd_siz();
    return v;
  }
}
```

### Insertion

In a rotationless treap, basic operations such as insertion, deletion, and querying rank by value can be implemented either with ordinary binary-search-tree methods or with split and merge. Generally speaking, implementations using split and merge are more concise, but slightly slower.[^ref2] To help understand rotationless treaps better, all operations below are implemented with split and merge.

When implementing insertion, we use a property of the split operation: nodes with values less than or equal to $\textit{val}$ are assigned to the first treap.

Suppose we split the current treap by $\textit{val}$. We obtain the following two trees, satisfying these conditions:

$$
\begin{aligned}
T_1 &\le val\\
T_2 &> val
\end{aligned}
$$

Here $T_1$ denotes the set of all nodes assigned to the first treap after splitting, and $T_2$ denotes the second.

If we further split by $\textit{val} - 1$ on $T_1$, the following two trees are produced and satisfy these conditions:

$$
\begin{gathered}
T_{1\ \text{left}} \le val - 1\\
T_{1\ \text{right}} > val - 1 \ \And \ T_{1\ \text{right}} \le val
\end{gathered}
$$

Here $T_{1\ \text{left}}$ denotes the set of all nodes assigned to the first treap after splitting $T_1$, and $T_{1\ \text{right}}$ denotes the second. In the formula above, the latter part $\And \ T_{1\ \text{right}} \le val$ comes from $T_1$ satisfying the condition $T_1 \le val$.

It is not hard to see that as long as $\textit{val}$ and node values are integers, which is the case in most use scenarios, the only nodes satisfying the condition for $T_{1\ \text{right}}$ have value equal to $\textit{val}$.

During insertion, if we find that a node satisfying $T_{1\ \text{right}}$ already exists, we can directly increase its duplicate count; otherwise, we create a new node.

After splitting the tree, remember to "glue" it back together with merge so it can continue to be used next time. Also note that the argument order of merge matters: all node values in the first tree must be smaller than those in the second.

```cpp
void insert(int val) {
  auto temp = split(root, val);
  // Split the whole tree into two according to val.
  // Note the split implementation: the subtree equal to val is in the left tree.
  auto l_tr = split(temp.first, val - 1);
  // l_tr's left tree <= val - 1. If there is a node equal to val, it must be in the right tree.
  Node *new_node;
  if (l_tr.second == nullptr) {
    // Create a new node if it does not exist; otherwise just increase the duplicate count.
    new_node = new Node(val);
  } else {
    l_tr.second->cnt++;
    l_tr.second->upd_siz();
  }
  Node *l_tr_combined =
      merge(l_tr.first, l_tr.second == nullptr ? new_node : l_tr.second);
  // Merge T_1 left and T_1 right.
  root = merge(l_tr_combined, temp.second);
  // Merge T_1 and T_2.
}
```

### Deletion

Deletion uses a method similar to insertion: find the node whose value equals $\textit{val}$, and delete it.

```cpp
void del(int val) {
  auto temp = split(root, val);
  auto l_tr = split(temp.first, val - 1);
  if (l_tr.second->cnt > 1) {
    // If this node has duplicate count greater than 1, just decrease it.
    l_tr.second->cnt--;
    l_tr.second->upd_siz();
    l_tr.first = merge(l_tr.first, l_tr.second);
  } else {
    if (temp.first == l_tr.second) {
      // The whole T_1 may contain only this node, so set it to null to mark it deleted.
      temp.first = nullptr;
    }
    delete l_tr.second;
    l_tr.second = nullptr;
  }
  root = merge(l_tr.first, temp.second);
}
```

### Query Rank by Value

The rank is the number of nodes smaller than this value, plus $+ 1$. Therefore, if we split the current tree by $\textit{val} - 1$, the first tree after splitting satisfies:

$$
T_1 \le val - 1
$$

If the tree values and $\textit{val}$ are integers, then $T_1$ contains all nodes with values smaller than $\textit{val}$.

```cpp
int qrank_by_val(Node* cur, int val) {
  auto temp = split(cur, val - 1);
  int ret = (temp.first == nullptr ? 0 : temp.first->siz) + 1;  // +1 by definition.
  root = merge(temp.first, temp.second);  // Glue it back after splitting.
  return ret;
}
```

### Query Value by Rank

After calling `split_by_rk()`, the three split treaps are returned. The second contains only one node, whose rank equals $\textit{rk}$, so we directly return that node's $\textit{val}$.

```cpp
int qval_by_rank(Node *cur, int rk) {
  Node *l, *mid, *r;
  tie(l, mid, r) = split_by_rk(cur, rk);
  int ret = mid->val;
  root = merge(merge(l, mid), r);
  return ret;
}
```

### Query the First Node Smaller Than `val`

This problem can be transformed into finding the node with the largest rank among all nodes smaller than $\textit{val}$. We split this treap by $\textit{val}$, so all node values in the returned first treap are smaller than $\textit{val}$. Then we call `qval_by_rank()` to find the node with the largest value in this tree.

```cpp
int qprev(int val) {
  auto temp = split(root, val - 1);
  // temp.first is the subtree whose values are less than val.
  int ret = qval_by_rank(temp.first, temp.first->siz);
  // Query the largest value among all nodes smaller than val.
  root = merge(temp.first, temp.second);
  return ret;
}
```

### Query the First Node Greater Than `val`

Similar to the previous operation, this problem can be transformed into finding the node with the smallest rank among all nodes greater than $\textit{val}$. After splitting by $\textit{val}$, all node values in the returned second treap are greater than $\textit{val}$.

Then we query the value of the node with rank $1$ in this tree, namely the node with the smallest value, and obtain the first node greater than $\textit{val}$.

```cpp
int qnex(int val) {
  auto temp = split(root, val);
  int ret = qval_by_rank(temp.second, 1);
  // Query the smallest value in the subtree containing all values greater than val.
  root = merge(temp.first, temp.second);
  return ret;
}
```

### Build

Convert a sequence with $n$ nodes, $\{a_n\}$, into a treap.

We can brute-force insert these $n$ nodes one by one. Each time we insert a node with value $v$, split the whole treap by value into a part with values less than or equal to $v$ and a part with values greater than $v$, create a new node with value $v$, and then merge the two parts and the new node in ascending order. A single insertion takes $O(\log n)$ time, and the total time complexity is $O(n\log n)$.

In some problems, there may be many operations that insert an ordered sequence. In this case, building the tree must be completed in $O(n)$ time.

Method 1: During recursive construction, choose the midpoint of the current interval as the root of that interval each time, and assign suitable priority values to each node so that the new tree satisfies the heap property. This guarantees tree height $O(\log n)$.

Method 2: During recursive construction, choose the midpoint of the current interval as the root of that interval each time, and then assign every node a random priority. This guarantees tree height $O(\log n)$, but does not guarantee that the heap property is satisfied. This is still correct, because in a rotationless treap the priority is used to make the `merge` operation more random, not to guarantee tree height.

Method 3: Observe that a treap is a Cartesian tree, and use the $O(n)$ Cartesian-tree construction method, maintaining the right chain with a monotonic stack.

### Interval Operations on a Rotationless Treap

#### Build

One major advantage of a rotationless treap over a rotating treap is that it can implement various interval operations. Below, we use the [template problem](https://loj.ac/problem/105) for the literary balanced tree as an example to introduce treap interval operations.

> You need to write a data structure, as hinted by the problem title, to maintain an ordered sequence.
>
> It must support the following operation: reverse an interval. For example, if the original ordered sequence is $5\ 4\ 3\ 2\ 1$ and the reversed interval is $[2,4]$, the result is $5\ 2\ 3\ 4\ 1$.
> For $100\%$ of the data, $1 \le n$ (initial interval length), $m$ (number of reversals) $\le 10^5$.

In this problem, we need to implement interval reversal, so we first need to consider how to build the tree. The constructed tree must represent the initial interval.

We only need to insert the indices of the interval into the treap in order. Then an inorder traversal, visiting the left subtree, then the current node, then the right subtree, yields this interval.[^ref3]

We know that in a plain binary search tree, inserting nodes in increasing order builds a long chain. An inorder traversal naturally yields this interval.

<div align=center>
  <img style="width: 50%; " src="../images/treap-search-tree-chain.svg" >
</div>

As shown above, inserting nodes into a plain search tree in the order $1\ 2\ 3\ 4\ 5$ also gives $1\ 2\ 3\ 4\ 5$ during inorder traversal.

However, in a treap, after inserting nodes in increasing order, merge operations also adjust the tree structure according to $\textit{priority}$. In this situation, how can we ensure that inorder traversal always outputs the correct sequence?

You can refer to the [monotonic-stack construction method for Cartesian trees](./cartesian-tree.md) to understand this issue.

Let the newly inserted node be $\textit{u}$.

First, because nodes are inserted in increasing order, every newly inserted node must be connected to the treap's right chain: the chain formed by starting at the root and repeatedly going to the right subtree.

Starting from the root, the $\textit{priority}$ values on the right chain are increasing in a min-heap. We can find the first node on the right chain whose $\textit{priority}$ is greater than that of $\textit{u}$; call this node $\textit{v}$, and replace it with $\textit{u}$.

Because $\textit{u}$ must be greater than every other node in the tree, we need to make $\textit{v}$ and its subtree the left subtree of $\textit{u}$. At this time, $\textit{u}$ has no right subtree.

We can see that $\textit{u}$ must be the last node visited in inorder traversal, because $\textit{u}$ is the last node on the right chain, and the right subtree is visited last in inorder traversal.

The following figure shows, when inserting nodes $1 \sim 5$ in increasing order, the change when inserting node $5$ into a treap. It can help you better understand the process of increasing-order insertion.

![Insert a node](./images/treap-none-rot-seg-build.svg)

#### Interval Reversal

When reversing the interval $[l, r]$, the basic idea is to split the tree into three intervals, $[1, l - 1],\ [l, r],\ [r + 1, n]$, and then reverse the middle interval $[l, r]$.[^ref3]

The concrete reversal operation swaps the left and right children of every subtree inside the interval. The following figure shows the treap after reversing intervals $[3, 4]$ and $[3, 5]$ in the treap above.

![Interval reversal](./images/treap-none-rot-seg-flip-ex.svg)

Note that if we reverse using this method directly, then every reversal of interval $[l, r]$ causes $r - l$ nodes to be swapped. Such frequent operations clearly cannot satisfy the $10^5$ data range. Its $O(n \times \log_2 n)$ complexity for a single reversal is even worse than brute force, because besides spending linear time swapping nodes, we also spend $O(\log_2 n)$ time in the tree to find the nodes to swap.

Looking again at the problem requirements, we can see that because only the final interval after all operations needs to be output, there is no need to actually swap every time. Thus we can use the lazy tag commonly used in segment trees to optimize the complexity. During a swap, it is enough to mark the parent node, indicating that every pair of left and right children under this subtree needs to be swapped.

In a segment tree, we usually push down lazy tags during updates and queries. This is because the range we want to update or query may not coincide with the range represented by a lazy tag, so we push the tag down first to ensure the queried or updated values are correct.

The same applies in a rotationless treap. In the concrete operation, we split the treap into the three trees mentioned above, mark the middle tree with a lazy tag, and then merge the three trees. Because the interval we want to reverse may not coincide with the interval represented by a lazy tag, we must push tags down while splitting. Also, split and merge operations change each node and the set of nodes represented by its lazy tag, so lazy tags also need to be pushed down before merging.

In other words, when the tree structure changes, before a split or merge operation changes the left or right child information of some node, we should push the tag down, not afterward. This is because a lazy tag must be propagated to child nodes; if the left and right child information is changed before an unpushed lazy tag is propagated, the lazy tag loses the targets it should have been pushed to.[^ref4]

<!-- TODO: Add a figure explaining why tags need to be pushed down during split and merge. -->

The following is a code explanation. The code references [^ref3].

Because most interval operations are the same as in an ordinary rotationless treap, we only explain the parts that differ from an ordinary rotationless treap.

#### Push Down Tags

Note that the lazy tag here means every pair of child nodes in this tree needs to be swapped. Therefore, if a child of the current node also has a lazy tag, the two reversals cancel out. If the child does not need to be reversed yet, this lazy tag must continue to be pushed down to the child.

```cpp
// Here pushdown is a member function of the Node class, where to_rev is the lazy tag.
void pushdown() {
  swap(ch[0], ch[1]);
  if (ch[0] != nullptr) ch[0]->to_rev ^= 1;
  if (ch[1] != nullptr) ch[1]->to_rev ^= 1;
  to_rev = false;
}

void check_tag() {
  if (to_rev) pushdown();
}
```

#### Split

Note that in this problem, because of reversal operations, $\textit{val}$ in the treap may no longer satisfy the binary-search-tree property; see the figure in the interval reversal section. Therefore, we cannot decide whether to recurse into the left or right subtree based on $\textit{val}$.

Thus the split here is more similar to splitting by rank in an ordinary rotationless treap. It decides whether to recurse left or right according to the size of the current tree; in other words, it uses the node's original position in the tree.

In the returned result, all node ranks in the first treap are less than or equal to $\textit{sz}$, while all node ranks in the second treap are greater than $\textit{sz}$.

```cpp
#define siz(_) (_ == nullptr ? 0 : _->siz)

pair<Node*, Node*> split(Node* cur, int sz) {
  // Decide according to tree size.
  if (cur == nullptr) return {nullptr, nullptr};
  cur->check_tag();
  // Push down before splitting.
  if (sz <= siz(cur->ch[0])) {
    auto temp = split(cur->ch[0], sz);
    cur->ch[0] = temp.second;
    cur->upd_siz();
    return {temp.first, cur};
  } else {
    auto temp =
        split(cur->ch[1],
              sz - siz(cur->ch[0]) -
                  1);  // This conversion was explained in "Query Value by Rank" for rotating treaps.
    cur->ch[1] = temp.first;
    cur->upd_siz();
    return {cur, temp.second};
  }
}
```

#### Merge

The only thing to note is that lazy tags must be pushed down before merging.

```cpp
Node *merge(Node *sm, Node *bg) {
  // small, big
  if (sm == nullptr && bg == nullptr) return nullptr;
  if (sm != nullptr && bg == nullptr) return sm;
  if (sm == nullptr && bg != nullptr) return bg;
  sm->check_tag(), bg->check_tag();
  if (sm->prio < bg->prio) {
    sm->ch[1] = merge(sm->ch[1], bg);
    sm->upd_siz();
    return sm;
  } else {
    bg->ch[0] = merge(sm, bg->ch[0]);
    bg->upd_siz();
    return bg;
  }
}
```

#### Interval Reversal

As introduced earlier, split out the three intervals $[1, l - 1],\ [l, r],\ [r + 1, n]$, mark the middle interval, and then merge them back.

```cpp
void seg_rev(int l, int r) {
  // Here less and more are relative to l.
  auto less = split(root, l - 1);
  // All elements less than or equal to l - 1 are in less's left tree.
  auto more = split(less.second, r - l + 1);
  // The interval of the first r - l + 1 elements starting from l.
  more.first->to_rev = true;
  root = merge(less.first, merge(more.first, more.second));
}
```

#### Print by Inorder Traversal

Remember to push down tags while printing.

```cpp
void print(Node* cur) {
  if (cur == nullptr) return;
  cur->check_tag();
  // Inorder traversal: left subtree first, then self, then right subtree.
  print(cur->ch[0]);
  cout << cur->val << " ";
  print(cur->ch[1]);
}
```

## Complete Code

### Rotating Treap

#### Pointer Implementation

??? note "Complete code"
    The following is the complete version of the code explained above. It is template code for an ordinary balanced tree.
    
    ```cpp
    // author: (ttzytt)[ttzytt.com]
    #include <cstdint>
    #include <cstdio>
    #include <cstdlib>
    using namespace std;
    
    struct Node {
      Node *ch[2];
      int val, rank;
      int rep_cnt;
      int siz;
    
      Node(int val) : val(val), rep_cnt(1), siz(1) {
        ch[0] = ch[1] = nullptr;
        rank = rand();
      }
    
      void upd_siz() {
        siz = rep_cnt;
        if (ch[0] != nullptr) siz += ch[0]->siz;
        if (ch[1] != nullptr) siz += ch[1]->siz;
      }
    };
    
    class Treap {
     private:
      Node *root;
    
      constexpr static int NIL = -1;  // Used to indicate that the queried value does not exist.
    
      enum rot_type { LF = 1, RT = 0 };
    
      int q_prev_tmp = 0, q_nex_tmp = 0;
    
      void _rotate(Node *&cur, rot_type dir) {  // 0 for right rotation, 1 for left rotation.
        Node *tmp = cur->ch[dir];
        cur->ch[dir] = tmp->ch[!dir];
        tmp->ch[!dir] = cur;
        cur->upd_siz(), tmp->upd_siz();
        cur = tmp;
      }
    
      void _insert(Node *&cur, int val) {
        if (cur == nullptr) {
          cur = new Node(val);
          return;
        } else if (val == cur->val) {
          cur->rep_cnt++;
          cur->siz++;
        } else if (val < cur->val) {
          _insert(cur->ch[0], val);
          if (cur->ch[0]->rank < cur->rank) {
            _rotate(cur, RT);
          }
          cur->upd_siz();
        } else {
          _insert(cur->ch[1], val);
          if (cur->ch[1]->rank < cur->rank) {
            _rotate(cur, LF);
          }
          cur->upd_siz();
        }
      }
    
      void _del(Node *&cur, int val) {
        if (val > cur->val) {
          _del(cur->ch[1], val);
          cur->upd_siz();
        } else if (val < cur->val) {
          _del(cur->ch[0], val);
          cur->upd_siz();
        } else {
          if (cur->rep_cnt > 1) {
            cur->rep_cnt--, cur->siz--;
            return;
          }
          uint8_t state = 0;
          state |= (cur->ch[0] != nullptr);
          state |= ((cur->ch[1] != nullptr) << 1);
          // 00: none; 01: left only; 10: right only; 11: both.
          Node *tmp = cur;
          switch (state) {
            case 0:
              delete cur;
              cur = nullptr;
              break;
            case 1:  // left child only
              cur = tmp->ch[0];
              delete tmp;
              break;
            case 2:  // right child only
              cur = tmp->ch[1];
              delete tmp;
              break;
            case 3:
              rot_type dir = cur->ch[0]->rank < cur->ch[1]->rank ? RT : LF;
              _rotate(cur, dir);
              _del(cur->ch[!dir], val);
              cur->upd_siz();
              break;
          }
        }
      }
    
      int _query_rank(Node *cur, int val) {
        int less_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
        if (val == cur->val)
          return less_siz + 1;
        else if (val < cur->val) {
          if (cur->ch[0] != nullptr)
            return _query_rank(cur->ch[0], val);
          else
            return 1;
        } else {
          if (cur->ch[1] != nullptr)
            return less_siz + cur->rep_cnt + _query_rank(cur->ch[1], val);
          else
            return cur->siz + 1;
        }
      }
    
      int _query_val(Node *cur, int rank) {
        int less_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
        if (rank <= less_siz)
          return _query_val(cur->ch[0], rank);
        else if (rank <= less_siz + cur->rep_cnt)
          return cur->val;
        else
          return _query_val(cur->ch[1], rank - less_siz - cur->rep_cnt);
      }
    
      int _query_prev(Node *cur, int val) {
        if (val <= cur->val) {
          if (cur->ch[0] != nullptr) return _query_prev(cur->ch[0], val);
        } else {
          q_prev_tmp = cur->val;
          if (cur->ch[1] != nullptr) _query_prev(cur->ch[1], val);
          return q_prev_tmp;
        }
        return NIL;
      }
    
      int _query_nex(Node *cur, int val) {
        if (val >= cur->val) {
          if (cur->ch[1] != nullptr) return _query_nex(cur->ch[1], val);
        } else {
          q_nex_tmp = cur->val;
          if (cur->ch[0] != nullptr) _query_nex(cur->ch[0], val);
          return q_nex_tmp;
        }
        return NIL;
      }
    
     public:
      void insert(int val) { _insert(root, val); }
    
      void del(int val) { _del(root, val); }
    
      int query_rank(int val) { return _query_rank(root, val); }
    
      int query_val(int rank) { return _query_val(root, rank); }
    
      int query_prev(int val) { return _query_prev(root, val); }
    
      int query_nex(int val) { return _query_nex(root, val); }
    };
    
    Treap tr;
    
    int main() {
      srand(0);
      int t;
      scanf("%d", &t);
      while (t--) {
        int mode;
        int num;
        scanf("%d%d", &mode, &num);
        switch (mode) {
          case 1:
            tr.insert(num);
            break;
          case 2:
            tr.del(num);
            break;
          case 3:
            printf("%d\n", tr.query_rank(num));
            break;
          case 4:
            printf("%d\n", tr.query_val(num));
            break;
          case 5:
            printf("%d\n", tr.query_prev(num));
            break;
          case 6:
            printf("%d\n", tr.query_nex(num));
            break;
        }
      }
    }
    ```

#### Array Implementation

The following is bzoj template code for an ordinary balanced tree, implemented with arrays.

??? note "Complete code"
    ```cpp
    --8<-- "docs/ds/code/treap/treap_1.cpp"
    ```

### Rotationless Treap

#### Pointer Implementation

??? note "Complete code"
    The following is the complete version of the code explained above. It is template code for an ordinary balanced tree.
    
    ```cpp
    
    // author: (ttzytt)[ttzytt.com]
    #include <cstdio>
    #include <cstdlib>
    #include <ctime>
    #include <tuple>
    using namespace std;
    
    struct Node {
      Node *ch[2];
      int val, prio;
      int cnt;
      int siz;
    
      Node(int _val) : val(_val), cnt(1), siz(1) {
        ch[0] = ch[1] = nullptr;
        prio = rand();
      }
    
      Node(Node *_node) {
        val = _node->val, prio = _node->prio, cnt = _node->cnt, siz = _node->siz;
      }
    
      void upd_siz() {
        siz = cnt;
        if (ch[0] != nullptr) siz += ch[0]->siz;
        if (ch[1] != nullptr) siz += ch[1]->siz;
      }
    };
    
    struct none_rot_treap {
    #define _3 second.second
    #define _2 second.first
      Node *root;
    
      pair<Node *, Node *> split(Node *cur, int key) {
        if (cur == nullptr) return {nullptr, nullptr};
        if (cur->val <= key) {
          auto temp = split(cur->ch[1], key);
          cur->ch[1] = temp.first;
          cur->upd_siz();
          return {cur, temp.second};
        } else {
          auto temp = split(cur->ch[0], key);
          cur->ch[0] = temp.second;
          cur->upd_siz();
          return {temp.first, cur};
        }
      }
    
      tuple<Node *, Node *, Node *> split_by_rk(Node *cur, int rk) {
        if (cur == nullptr) return {nullptr, nullptr, nullptr};
        int ls_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
        if (rk <= ls_siz) {
          Node *l, *mid, *r;
          tie(l, mid, r) = split_by_rk(cur->ch[0], rk);
          cur->ch[0] = r;
          cur->upd_siz();
          return {l, mid, cur};
        } else if (rk <= ls_siz + cur->cnt) {
          Node *lt = cur->ch[0];
          Node *rt = cur->ch[1];
          cur->ch[0] = cur->ch[1] = nullptr;
          return {lt, cur, rt};
        } else {
          Node *l, *mid, *r;
          tie(l, mid, r) = split_by_rk(cur->ch[1], rk - ls_siz - cur->cnt);
          cur->ch[1] = l;
          cur->upd_siz();
          return {cur, mid, r};
        }
      }
    
      Node *merge(Node *u, Node *v) {
        if (u == nullptr && v == nullptr) return nullptr;
        if (u != nullptr && v == nullptr) return u;
        if (v != nullptr && u == nullptr) return v;
        if (u->prio < v->prio) {
          u->ch[1] = merge(u->ch[1], v);
          u->upd_siz();
          return u;
        } else {
          v->ch[0] = merge(u, v->ch[0]);
          v->upd_siz();
          return v;
        }
      }
    
      void insert(int val) {
        auto temp = split(root, val);
        auto l_tr = split(temp.first, val - 1);
        Node *new_node;
        if (l_tr.second == nullptr) {
          new_node = new Node(val);
        } else {
          l_tr.second->cnt++;
          l_tr.second->upd_siz();
        }
        Node *l_tr_combined =
            merge(l_tr.first, l_tr.second == nullptr ? new_node : l_tr.second);
        root = merge(l_tr_combined, temp.second);
      }
    
      void del(int val) {
        auto temp = split(root, val);
        auto l_tr = split(temp.first, val - 1);
        if (l_tr.second->cnt > 1) {
          l_tr.second->cnt--;
          l_tr.second->upd_siz();
          l_tr.first = merge(l_tr.first, l_tr.second);
        } else {
          if (temp.first == l_tr.second) {
            temp.first = nullptr;
          }
          delete l_tr.second;
          l_tr.second = nullptr;
        }
        root = merge(l_tr.first, temp.second);
      }
    
      int qrank_by_val(Node *cur, int val) {
        auto temp = split(cur, val - 1);
        int ret = (temp.first == nullptr ? 0 : temp.first->siz) + 1;
        root = merge(temp.first, temp.second);
        return ret;
      }
    
      int qval_by_rank(Node *cur, int rk) {
        Node *l, *mid, *r;
        tie(l, mid, r) = split_by_rk(cur, rk);
        int ret = mid->val;
        root = merge(merge(l, mid), r);
        return ret;
      }
    
      int qprev(int val) {
        auto temp = split(root, val - 1);
        int ret = qval_by_rank(temp.first, temp.first->siz);
        root = merge(temp.first, temp.second);
        return ret;
      }
    
      int qnex(int val) {
        auto temp = split(root, val);
        int ret = qval_by_rank(temp.second, 1);
        root = merge(temp.first, temp.second);
        return ret;
      }
    };
    
    none_rot_treap tr;
    
    int main() {
      srand(time(nullptr));
      int t;
      scanf("%d", &t);
      while (t--) {
        int mode;
        int num;
        scanf("%d%d", &mode, &num);
        switch (mode) {
          case 1:
            tr.insert(num);
            break;
          case 2:
            tr.del(num);
            break;
          case 3:
            printf("%d\n", tr.qrank_by_val(tr.root, num));
            break;
          case 4:
            printf("%d\n", tr.qval_by_rank(tr.root, num));
            break;
          case 5:
            printf("%d\n", tr.qprev(num));
            break;
          case 6:
            printf("%d\n", tr.qnex(num));
            break;
        }
      }
    }
    ```

### Interval Operations on a Rotationless Treap

#### Pointer Implementation

??? note "Complete code"
    The following is the complete version of the code explained above. It is template code for the literary balanced tree problem.
    
    ```cpp
    
    // author: (ttzytt)[ttzytt.com]
    #include <cstdlib>
    #include <ctime>
    #include <iostream>
    using namespace std;
    
    // Reference: https://www.cnblogs.com/Equinox-Flower/p/10785292.html
    struct Node {
      Node* ch[2];
      int val, prio;
      int cnt;
      int siz;
      bool to_rev = false;  // Every node under this subtree needs to be reversed.
    
      Node(int _val) : val(_val), cnt(1), siz(1) {
        ch[0] = ch[1] = nullptr;
        prio = rand();
      }
    
      int upd_siz() {
        siz = cnt;
        if (ch[0] != nullptr) siz += ch[0]->siz;
        if (ch[1] != nullptr) siz += ch[1]->siz;
        return siz;
      }
    
      void pushdown() {
        swap(ch[0], ch[1]);
        if (ch[0] != nullptr) ch[0]->to_rev ^= 1;
        // If the child originally also needs reversal, the two reversals cancel out.
        // If the child does not need reversal, this tag must continue to be pushed to it.
        if (ch[1] != nullptr) ch[1]->to_rev ^= 1;
        to_rev = false;
      }
    
      void check_tag() {
        if (to_rev) pushdown();
      }
    };
    
    struct Seg_treap {
      Node* root;
    #define siz(_) (_ == nullptr ? 0 : _->siz)
    
      pair<Node*, Node*> split(Node* cur, int sz) {
        // Split according to tree size.
        if (cur == nullptr) return {nullptr, nullptr};
        cur->check_tag();
        if (sz <= siz(cur->ch[0])) {
          // The left subtree is enough.
          auto temp = split(cur->ch[0], sz);
          // The entire left subtree may not be needed; temp.second is the unneeded part.
          cur->ch[0] = temp.second;
          cur->upd_siz();
          return {temp.first, cur};
        } else {
          // The left part plus part of the right part, including this node itself.
          auto temp = split(cur->ch[1], sz - siz(cur->ch[0]) - 1);
          cur->ch[1] = temp.first;
          cur->upd_siz();
          return {cur, temp.second};
        }
      }
    
      Node* merge(Node* sm, Node* bg) {
        // small, big
        if (sm == nullptr && bg == nullptr) return nullptr;
        if (sm != nullptr && bg == nullptr) return sm;
        if (sm == nullptr && bg != nullptr) return bg;
        sm->check_tag(), bg->check_tag();
        if (sm->prio < bg->prio) {
          sm->ch[1] = merge(sm->ch[1], bg);
          sm->upd_siz();
          return sm;
        } else {
          bg->ch[0] = merge(sm, bg->ch[0]);
          bg->upd_siz();
          return bg;
        }
      }
    
      void insert(int val) {
        auto temp = split(root, val);
        auto l_tr = split(temp.first, val - 1);
        Node* new_node;
        if (l_tr.second == nullptr) new_node = new Node(val);
        Node* l_tr_combined =
            merge(l_tr.first, l_tr.second == nullptr ? new_node : l_tr.second);
        root = merge(l_tr_combined, temp.second);
      }
    
      void seg_rev(int l, int r) {
        // Here less and more are relative to l.
        auto less = split(root, l - 1);
        // All elements less than or equal to l - 1 are on the left side of less.
        auto more = split(less.second, r - l + 1);
        // Take out the first r - l + 1 elements starting from l.
        more.first->to_rev = true;
        root = merge(less.first, merge(more.first, more.second));
      }
    
      void print(Node* cur) {
        if (cur == nullptr) return;
        cur->check_tag();
        print(cur->ch[0]);
        cout << cur->val << " ";
        print(cur->ch[1]);
      }
    };
    
    Seg_treap tr;
    
    int main() {
      srand(time(nullptr));
      int n, m;
      cin >> n >> m;
      for (int i = 1; i <= n; i++) tr.insert(i);
      while (m--) {
        int l, r;
        cin >> l >> r;
        tr.seg_rev(l, r);
      }
      tr.print(tr.root);
    }
    ```

## Example Problems

[Ordinary Balanced Tree](https://loj.ac/problem/104)

[Literary Balanced Tree (Splay)](https://loj.ac/problem/105)

[ZJOI2006 Bookcase](https://www.luogu.com.cn/problem/P2596)

[NOI2005 Maintaining a Sequence](https://www.luogu.com.cn/problem/P2042)

[CF 702F T-Shirts](http://codeforces.com/problemset/problem/702/F)

## References and Notes

[^ref1]: The design of this figure refers to the illustration in the [Wikipedia Treap article](https://en.wikipedia.org/wiki/Treap).

[^ref2]: <https://charleswu.site/archives/1051>

[^ref3]: <https://www.cnblogs.com/Equinox-Flower/p/10785292.html>

[^ref4]: <https://www.luogu.com.cn/blog/85514/fhq-treap-xue-xi-bi-ji>
