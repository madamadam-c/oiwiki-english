## Introduction

A pairing heap is a mergeable heap data structure that supports insertion, querying/deleting the minimum, merging, and modifying elements. It is fast in practice and structurally simple, but because its guarantees are amortized via potential analysis, it cannot be made persistent.

## Definition

A pairing heap is a weighted multiway tree satisfying the heap property (as shown below): each node's key is less than or equal to the keys of all its children (using a min-heap as the example throughout).
![](./images/pairingheap1.jpg)

Usually we store a pairing heap with the child-sibling representation (shown below), where all children of a node form a singly linked list. Each node stores a pointer to its first child, which is the head of that list, and a pointer to its right sibling.

This representation makes pairing heaps easy to implement and also simplifies complexity analysis.

![](./images/pairingheap2.jpg)

```cpp
struct Node {
  T v;  // T is the key type
  Node *child, *sibling;
  // child points to the node's first child; sibling points to its next sibling.
  // If the node has no child/next sibling, the pointer is nullptr.
};
```

From the definition, compared with other common heap structures, a pairing heap maintains no extra information such as subtree size, depth, or rank. A binary heap also stores no extra information, but it guarantees operation complexity by maintaining a strict complete binary tree structure. Any tree satisfying the heap property is a valid pairing heap. This simple and highly flexible structure is the basis of pairing heaps' excellent practical efficiency; by contrast, Fibonacci heaps have poor constants because they need to maintain a lot of extra information.

A pairing heap guarantees its overall complexity through a carefully designed order of operations. The original paper[^ref1] calls it a "self-adjusting heap". In this sense it is quite similar to splay trees, which were called "self-adjusting binary trees" in their original paper.

## Operations

### Query the Minimum

By the definition of a pairing heap, the root must have the minimum key, so we can directly return the root node.

### Meld

Melding two pairing heaps is simple: first make the smaller of the two roots the new root, then insert the larger root as one of its children (see the figure below).

![](./images/pairingheap3.jpg)

Note that a node's child list is ordered by insertion time: the rightmost node became the parent's child earliest, and the leftmost node became the parent's child most recently.

???+ note "Implementation"
    ```cpp
    Node* meld(Node* x, Node* y) {
      // If either heap is empty, return the other one directly.
      if (x == nullptr) return y;
      if (y == nullptr) return x;
      if (x->v > y->v) std::swap(x, y);  // After swap, x has the smaller key.
      // Make y a child of x.
      y->sibling = x->child;
      x->child = y;
      return x;  // The new root is x.
    }
    ```

### Insert

With meld available, insertion simply treats the new element as a new pairing heap and melds it with the original heap.

### Delete the Minimum

First, note that the operations above are quite lazy and do not maintain the data structure at all, so we must design delete-min carefully to keep the overall complexity under control.

The root is the minimum, so the node to delete is the root. Consider what happens after removing it: all of its former children form a forest. Since a pairing heap should be a single tree, we need to merge all these children in some order.

A natural idea is to use `meld` to merge the children one by one from left to right. This is obviously correct, but it can degrade a single operation to $O(n)$.

To guarantee the overall amortized complexity, use a two-pass merging method:

1.  Pair the children two by two, and use `meld` to merge the two children in each pair (see figure 1 below).
2.  Merge the newly produced heaps one by one **from right to left** (from older children toward newer children; see figure 2 below).

![](./images/pairingheap4.jpg)

![](./images/pairingheap5.jpg)

First implement a helper function `merges`, which merges all siblings of a node.

???+ note "Implementation"
    ```cpp
    Node* merges(Node* x) {
      if (x == nullptr || x->sibling == nullptr)
        return x;  // If the tree is empty or has no next sibling, no merge is needed.
      Node* y = x->sibling;                // y is x's next sibling.
      Node* c = y->sibling;                // c is the sibling after y.
      x->sibling = y->sibling = nullptr;   // Detach them.
      return meld(merges(c), meld(x, y));  // Core step.
    }
    ```

The last line is the core of this function. It has three parts:

1.  `meld(x,y)` pairs `x` and `y`.
2.  `merges(c)` recursively merges `c` and its siblings.
3.  Meld the two new trees produced by the two operations above.

Note that the second pass above requires a specific merge direction (from right to left). This recursive implementation already guarantees that order. If you implement an iterative version yourself, make sure to preserve this order; otherwise the complexity guarantee is lost.

With `merges`, the `delete-min` operation is straightforward.

???+ note "Implementation"
    ```cpp
    Node* delete_min(Node* x) {
      Node* t = merges(x->child);
      delete x;  // If memory reclamation is needed.
      return t;
    }
    ```

### Decrease the Key of an Element

To implement this operation, add a "parent" pointer to each node. When a node has a left sibling, this pointer points to the left sibling rather than the actual parent; otherwise, it points to its parent.

First modify the node definition as follows:

???+ note "Implementation"
    ```cpp
    struct Node {
      LL v;
      int id;
      Node *child, *sibling;
      Node *father;  // Added: parent pointer; nullptr if this node is the root.
    };
    ```

Modify `meld` as follows:

???+ note "Implementation"
    ```cpp
    Node* meld(Node* x, Node* y) {
      if (x == nullptr) return y;
      if (y == nullptr) return x;
      if (x->v > y->v) std::swap(x, y);
      if (x->child != nullptr) {  // Added: maintain parent pointers.
        x->child->father = y;
      }
      y->sibling = x->child;
      y->father = x;  // Added: maintain parent pointers.
      x->child = y;
      return x;
    }
    ```

Modify `merges` as follows:

???+ note "Implementation"
    ```cpp
    Node *merges(Node *x) {
      if (x == nullptr) return nullptr;
      x->father = nullptr;  // Added: maintain parent pointers.
      if (x->sibling == nullptr) return x;
      Node *y = x->sibling, *c = y->sibling;
      y->father = nullptr;  // Added: maintain parent pointers.
      x->sibling = y->sibling = nullptr;
      return meld(merges(c), meld(x, y));
    }
    ```

Now consider how to implement `decrease-key`.
After decreasing the key of node `x`, the subtree rooted at `x` still satisfies the pairing heap property, but the heap property between `x` and its parent may be violated.
Therefore, cut out the entire subtree rooted at `x`. Now both resulting trees satisfy the pairing heap property; meld them to complete the operation.

???+ note "Implementation"
    ```cpp
    // root is the heap root, x is the node to operate on, and v is the new key.
    // When calling, ensure v <= x->v. The return value is the new root.
    Node *decrease_key(Node *root, Node *x, LL v) {
      x->v = v;                 // Update the key.
      if (x == root) return x;  // If x is the root, return directly.
      // Cut x out from its parent's children; handle cases by x's position.
      if (x->father->child == x) {
        x->father->child = x->sibling;
      } else {
        x->father->sibling = x->sibling;
      }
      if (x->sibling != nullptr) {
        x->sibling->father = x->father;
      }
      x->sibling = nullptr;
      x->father = nullptr;
      return meld(root, x);  // Meld x with the root again.
    }
    ```

## Complexity Analysis

Pairing heaps are simple in structure and implementation, but their time complexity analysis is not easy.

The original paper[^ref1] only proved amortized $O(\log n)$ complexity for both `meld` and `delete-min`, but conjectured that all operations have the same complexities as Fibonacci heaps.

Unfortunately, later work showed that for pairing heaps that maintain no extra information, the amortized lower bound of `decrease-key` is at least $\Omega (\log \log n)$ under certain operation sequences[^ref2].

Current good upper-bound estimates include Iacono's $O(1)$ `meld` and $O(\log n)$ `decrease-key`[^ref3], and Pettie's $O(2^{2 \sqrt{\log \log n}})$ bounds for `meld` and `decrease-key`[^ref4]. Note that all these bounds are amortized, so you cannot take the minimum of the separate results independently.

## References

[^ref1]: [The pairing heap: a new form of self-adjusting heap](http://www.cs.cmu.edu/~sleator/papers/pairing-heaps.pdf)

[^ref2]: [On the efficiency of pairing heaps and related data structures](https://dl.acm.org/doi/10.1145/320211.320214)

[^ref3]: [Improved upper bounds for pairing heaps](https://arxiv.org/abs/1110.4428)

[^ref4]: [Towards a Final Analysis of Pairing Heaps](http://web.eecs.umich.edu/~pettie/papers/focs05.pdf)

-   <https://en.wikipedia.org/wiki/Pairing_heap>
-   <https://brilliant.org/wiki/pairing-heap/>
