author: isdanni

???+ warning "Note"
    This chapter is optional reading. Before reading it, please make sure you have some understanding of Functional Programming.

## Introduction

A **Finger Tree** is a **purely functional** data structure proposed by Ralf Hinze and Ross Paterson.

## Why Finger Trees Are Needed

In functional programming, lists are a very common data type. For sequence-based operations, including adding and deleting elements at both ends (deque operations), inserting, concatenating, and deleting at arbitrary nodes, finding an element satisfying some condition, and splitting a sequence into subsequences, almost all functional languages provide support. However, these languages have difficulty supporting more operations efficiently. Even when corresponding implementations exist, they are usually very complex and difficult to use in practice.

Finger trees provide a purely functional sequence data structure. They can perform operations such as access and adding to the front or back of a sequence in amortized constant time, and concatenation and random access in logarithmic time. Besides good asymptotic runtime bounds, finger trees are very flexible: when combined with a [monoidal tag](https://en.wikipedia.org/wiki/Monoidal_category) on elements, finger trees can be used to implement efficient random-access sequences, ordered sequences, interval trees, and priority queues.

## Basic Structure

Finger trees store data at the tree's "fingers" (leaves), where access time is amortized constant. A finger is a point that can access part of a data structure. In imperative languages, this is called a pointer. In a finger tree, a "finger" refers to a structure pointing to the end of a sequence or to a leaf node. Finger trees also store, in every internal node, the result of applying some associative operation to their descendants. The data stored in internal nodes can be used to provide functionality beyond ordinary tree-like data structures.

1.  The depth of a finger tree is counted from bottom to top.
2.  The first level of a finger tree, i.e. the leaves, contains only values and has depth $0$. The second level has depth $1$, the third level has depth $2$, and so on.
3.  The closer a node is to the root, the deeper the subtree it points to in the original tree (before it became a finger tree). Thus, working downward along the tree goes from leaves to the root of the original tree, the opposite of typical tree data structures. To obtain this structure, we must ensure that the original tree has uniform depth. When declaring node objects, they must be parameterized by the type of their child nodes. Nodes on the spine with depth $1$ or greater point to trees, and through this parameterization they can be represented by nested nodes.

### Turning a Tree into a Finger Tree

???+ note "Note"
    A **2-3 tree** is a tree data structure in which every node with children (internal node) has either two children (a $2$-node) and one data element, or three children (a $3$-node) and two data elements. A 2-3 tree is a B-tree of order $3$. Nodes outside the tree (leaf nodes) have no children and one or two data elements.

We start this process from a balanced 2-3 tree. For a finger tree to work properly, all leaf nodes need to be level. As shown below (image from the finger-tree paper):

![](./images/finger-tree-1.png)

A finger is "a structure that provides efficient access to nodes near a particular location in a tree." To make a finger tree, we place fingers at the left and right ends of the tree, take the leftmost and rightmost internal nodes, and pull them up so that the rest of the tree hangs between them. This gives us amortized constant-time access to the ends of the sequence.

![](./images/finger-tree-2.png)

This new data structure is called a finger tree. A finger tree consists of several levels (blue boxes below) distributed along its spine (brown line):

![](./images/finger-tree-3.png)

```haskell
data FingerTree a = Empty
                  | Single a
                  | Deep (Digit a) (FingerTree (Node a)) (Digit a)

data Digit a = One a | Two a a | Three a a a | Four a a a a
data Node a = Node2 a a | Node3 a a a
```

The numbers in the example are nodes with letters. Each list is divided by the prefix or suffix of each node on the spine. In the transformed 2-3 tree, the digit list at the top level seems to have length two or three, while lower levels have length only one or two. To allow some applications of finger trees to run so efficiently, finger trees allow $1$ to $4$ subtrees at every level. A finger-tree digit can be converted into a list, such as:

```haskell
type Digit a = One a | Two a a | Three a a a | Four a a a a
```

The top level has elements of type $a$, and the next level has elements of type node $a$, because there are nodes between the spine and the leaves. This usually means that the $n$-th level of the tree has element type $Node^{n}$ $a$, or 2-3 trees of depth $n$. This means a sequence of $n$ elements is represented by a tree of depth `Theta(log n)`. An element at distance $d$ from the nearest end is stored at depth `Theta(log d)` in the tree.

### Deque Operations

Finger trees can also implement efficient deques. Whether or not the structure is persistent, all operations take `Theta(1)` time. It can be viewed as an extension of implicit deques[^okasaki1999purely]:

1.  Replacing pairs with 2-3 nodes provides enough flexibility to support efficient concatenation. (To keep deque operations constant-time, `Digit` must be extended to four.)
2.  Annotating internal nodes with a monoid allows efficient splitting.

```haskell
data ImplicitDeque a = Empty
                     | Single a
                     | Deep (Digit a) (ImplicitDeque (a, a)) (Digit a)

data Digit a = One a | Two a a | Three a a a
```

## Time Complexity

Finger trees provide amortized constant-time access to the tree's "fingers" (leaves), where data is stored, and logarithmic-time concatenation and splitting in the size of the smaller part. They also store, in every internal node, the result of applying some associative operation to their descendants. The "summary" data stored in internal nodes can be used to provide functionality for data structures beyond trees.

| Operation | Finger tree | Annotated 2-3 tree | List | Vector |
| --------- | ----------- | ------------------ | ---- | ------ |
| `const`,`snoc` | $O(1)$ | $O(\log n)$ | $O(1)$/$O(n)$ | $O(n)$ |
| `viewl`,`viewr` | $O(1)$ | $O(\log n)$ | $O(1)$/$O(n)$ | $O(1)$ |
| `measure`/`length` | $O(1)$ | $O(1)$ | $O(n)$ | $O(1)$ |
| `append` | $O(\log \min(l1, l2))$ | $O(\log n)$ | $O(n)$ | $O(m+n)$ |
| `split` | $O(\log \min(n, l-n))$ | $O(\log n)$ | $O(n)$ | $O(1)$ |
| `replicate` | $O(\log n)$ | $O(\log n)$ | $O(n)$ | $O(n)$ |
| `fromList`,`toList`,`reverse` | $O(l)$/$O(l)$/$O(l)$ | $O(l)$ | $O(1)$/$O(1)$/$O(n)$ | $O(n)$ |
| `index` | $O(\log \min(n, l-n))$ | $O(\log n)$ | $O(n)$ | $O(1)$ |

## Applications

Finger trees can be used to build other trees. For example, a priority queue can be implemented by labeling internal nodes with the minimum priority among their child nodes, and an indexed list/array can be implemented by labeling nodes with the number of leaves in their child nodes. Other applications include random-access sequences (as described below), ordered sequences, and interval trees.

Finger trees can provide average $O(1)$ push, reverse, and pop operations, and $O(\log n)$ append and split operations; they can also adapt to indexed or sorted sequences. Like all functional data structures, they are inherently persistent, meaning old versions of the tree are always preserved.

For implementation, the finite sequence `Seq` in the Haskell core library uses 2-3 finger trees ([Data.Sequence](https://hackage.haskell.org/package/containers-0.6.5.1/docs/Data-Sequence.html)), and the [`BatFingerTree` module](https://ocaml-batteries-team.github.io/batteries-included/hdoc2/BatFingerTree.html) in OCaml also uses a generic finger-tree data structure. Finger trees can be implemented with or without lazy evaluation, but laziness allows a simpler implementation.

## References and Further Reading

1.  Ralf Hinze and Ross Paterson, "[Finger trees: a simple general-purpose data structure](http://www.staff.city.ac.uk/~ross/papers/FingerTree.html)", Journal of Functional Programming 16:2 (2006) pp 197-217.
2.  [Finger Tree - Wikipedia](https://en.wikipedia.org/wiki/Finger_tree)

[^okasaki1999purely]: [Purely Functional Data Structures](https://www.cambridge.org/us/academic/subjects/computer-science/programming-languages-and-applied-logic/purely-functional-data-structures), Chris Okasaki (1999)
