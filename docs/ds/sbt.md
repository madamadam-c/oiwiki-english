Size Balanced Tree (SBT) is a self-balanced binary search tree (SBBST) proposed by Chinese OI contestant Chen Qifeng in 2007. It maintains balance by checking subtree sizes. Compared with mainstream self-balancing binary search trees such as red-black trees and AVL trees, Size Balanced Tree supports querying the rank of a key in the tree in $O(\log n)$ time.

## Node Definition

Compared with an ordinary binary search tree, each SBT node $N$ only needs to maintain one additional integer field, `size`, which stores the number of nodes in the subtree rooted at $N$. The concrete definition of the node type `Node` is as follows:

| Identifier | Type    | Description                                      |
| ---------- | ------- | ------------------------------------------------ |
| `left`     | `Node*` | Reference to the left child node                 |
| `right`    | `Node*` | Reference to the right child node                |
| `size`     | `int`   | Number of nodes in the subtree rooted at this node |

## Properties

Every node $N$ in a Size Balanced Tree satisfies the following properties:

```text
size(N.left) >= size(N.right.left)
size(N.left) >= size(N.right.right)
size(N.right) >= size(N.left.left)
size(N.right) >= size(N.left.right)
```

In natural language: the `size` of any node is not smaller than the `size` of any child of its sibling (that is, any nephew).

## Balance Maintenance

### Rotation

SBT mainly changes its height through rotations to maintain balance. Its rotations are similar to those in most self-balancing binary search trees. The only difference is that after a rotation, the `size` fields of the nodes whose left or right children changed during the rotation must be updated. Example code:

```cpp
void updateSize() {
  USize leftSize = this->left != nullptr ? this->left->size : 0;
  USize rightSize = this->right != nullptr ? this->right->size : 0;
  this->size = leftSize + rightSize + 1;
}

static void rotateLeft(NodePtr& node) {
  assert(node != nullptr);
  // clang-format off
  //     |                       |
  //     N                       S
  //    / \     l-rotate(N)     / \
  //   L   S    ==========>    N   R
  //      / \                 / \
  //     M   R               L   M
  // clang-format on
  NodePtr successor = node->right;
  node->right = successor->left;
  successor->left = node;

  node->updateSize();
  successor->updateSize();

  node = successor;
}

static void rotateRight(NodePtr& node) {
  assert(node != nullptr);
  // clang-format off
  //       |                   |
  //       N                   S
  //      / \   r-rotate(N)   / \
  //     S   R  ==========>  L   N
  //    / \                     / \
  //   L   M                   M   R
  // clang-format on
  NodePtr successor = node->left;
  node->left = successor->right;
  successor->right = node;

  node->updateSize();
  successor->updateSize();

  node = successor;
}
```

### Maintenance

#### Case 1

`size(N.left) < size(N.right.left)`

```cpp
if (size(node->right->left) > size(node->left)) {
  // clang-format off
  //     |                     |                      |
  //     N                     N                     [M]
  //    / \    r-rotate(R)    / \     l-rotate(N)    / \
  //  <L>  R   ==========>  <L> [M]   ==========>   N   R
  //      /                       \                /
  //    [M]                        R             <L>
  // clang-format on
  rotateRight(node->right);
  rotateLeft(node);
  fixBalance(node->left);
  fixBalance(node->right);
  fixBalance(node);
  return;
}
```

#### Case 2

`size(N.left) < size(N.right.right)`

```cpp
if (size(node->right->right) > size(node->left)) {
  // clang-format off
  //     |                       |
  //     N                       R
  //    / \     l-rotate(N)     / \
  //  <L>  R    ==========>    N  [M]
  //        \                 /
  //        [M]             <L>
  // clang-format on
  rotateLeft(node);
  fixBalance(node->left);
  fixBalance(node);
  return;
}
```

#### Case 3

`size(N.right) < size(N.left.left)`

```cpp
if (size(node->left->left) > size(node->right)) {
  // clang-format off
  //       |                       |
  //       N                       L
  //      / \     r-rotate(N)     / \
  //     L  <R>   ==========>   [M]  N
  //    /                             \
  //  [M]                             <R>
  // clang-format on
  rotateRight(node);
  fixBalance(node->right);
  fixBalance(node);
  return;
}
```

#### Case 4

`size(N.right) < size(N.left.right)`

```cpp
if (size(node->left->right) > size(node->right)) {
  // clang-format off
  //     |                     |                      |
  //     N                     N                     [M]
  //    / \    l-rotate(L)    / \     r-rotate(N)    / \
  //   L  <R>  ==========>  [M] <R>   ==========>   L   N
  //    \                   /                            \
  //    [M]                L                             <R>
  // clang-format on
  rotateLeft(node->left);
  rotateRight(node);
  fixBalance(node->left);
  fixBalance(node->right);
  fixBalance(node);
  return;
}
```

## Operations

### Insertion

SBT insertion recursively updates node `size` fields and performs balance maintenance after completing the ordinary binary search tree insertion. Example code:

```cpp
if (compare(key, node->key)) {
  /* key < node->key */
  if (node->left == nullptr) {
    node->left = Node::from(key, value);
    node->updateSize();
  } else {
    insert(node->left, key, value, replace);
    node->updateSize();
    fixBalance(node);
  }
} else {
  /* key > node->key */
  if (node->right == nullptr) {
    node->right = Node::from(key, value);
    node->updateSize();
  } else {
    insert(node->right, key, value, replace);
    node->updateSize();
    fixBalance(node);
  }
}
```

### Deletion

According to Chen Qifeng, the proposer of Size Balanced Tree, in his paper's description of deletion:

> It can result in a destroyed SBT. But with the insertion above, a BST is still kept at the height of $O(\log n)$ where $n$ is the total number of insertions, not the current size.

Although deletion may break the SBT properties, it does not increase the tree height and therefore does not affect the efficiency of subsequent operations. In practice, however, if many deletions and queries are performed after a batch insertion, imbalance may still affect overall efficiency. Therefore, this implementation still includes balance maintenance in SBT deletion. Reference code:

```cpp
bool remove(NodePtr& node, K key, NodeConsumer action) {
  assert(node != nullptr);

  if (key != node->key) {
    if (compare(key, node->key)) {
      /* key < node->key */
      NodePtr& left = node->left;
      if (left != nullptr && remove(left, key, action)) {
        node->updateSize();
        fixBalance(node);
        return true;
      } else {
        return false;
      }
    } else {
      /* key > node->key */
      NodePtr& right = node->right;
      if (right != nullptr && remove(right, key, action)) {
        node->updateSize();
        fixBalance(node);
        return true;
      } else {
        return false;
      }
    }
  }

  assert(key == node->key);
  action(node);

  if (node->isLeaf()) {
    // Case 1: no child
    node = nullptr;
  } else if (node->right == nullptr) {
    // Case 2: left child only
    // clang-format off
    //     P
    //     |  remove(N)  P
    //     N  ========>  |
    //    /              L
    //   L
    // clang-format on
    node = node->left;
  } else if (node->left == nullptr) {
    // Case 3: right child only
    // clang-format off
    //   P
    //   |    remove(N)  P
    //   N    ========>  |
    //    \              R
    //     R
    // clang-format on
    node = node->right;
  } else if (node->right->left == nullptr) {
    // Case 4: both left and right child, right child has no left child
    // clang-format off
    //    |                 |
    //    N    remove(N)    R
    //   / \   ========>   /
    //  L   R             L
    // clang-format on
    NodePtr right = node->right;
    swapNode(node, right);
    right->right = node->right;
    node = right;
    node->updateSize();
    fixBalance(node);
  } else {
    // Case 5: both left and right child, right child is not a leaf
    // clang-format off
    //   Step 1. find the node N with the smallest key
    //           and its parent P on the right subtree
    //   Step 2. swap S and N
    //   Step 3. remove node N like Case 1 or Case 3
    //   Step 4. update size for all nodes on the path
    //           from S to P
    //     |                  |
    //     N                  S                 |
    //    / \                / \                S
    //   L  ..  swap(N, S)  L  ..  remove(N)   / \
    //       |  =========>      |  ========>  L  ..
    //       P                  P                 |
    //      / \                / \                P
    //     S  ..              N  ..              / \
    //      \                  \                R  ..
    //       R                  R
    //
    // clang-format on

    std::stack<NodePtr> path;

    // Step 1
    NodePtr successor = node->right;
    NodePtr parent = node;
    path.push(node);

    while (successor->left != nullptr) {
      path.push(successor);
      parent = successor;
      successor = parent->left;
    }

    // Step 2
    swapNode(node, successor);

    // Step 3
    parent->left = node->right;
    // Restore node
    node = successor;

    // Step 4
    while (!path.empty()) {
      path.top()->updateSize();
      path.pop();
    }
  }

  return true;
}
```

Note that in Case 5 above, after using successor node $S$ (the predecessor can also be used) to replace the node $N$ to be deleted and deleting the replaced $N$, all `size` fields on the path from the original $S$ node's parent $P$ to the replaced $S$ node must be updated, as shown in the code comments. This implementation records the nodes on the path with a stack, then pops them in reverse traversal order to update them.

### Querying Rank

Because SBT nodes store subtree sizes, the rank of a `key` (or the number of nodes greater than or less than a `key`) can be queried in $O(\log n)$ time. Example code:

```cpp
USize countLess(ConstNodePtr node, K key, bool countEqual = false) const {
  if (node == nullptr) {
    return 0;
  } else if (key < node->key) {
    return countLess(node->left, key, countEqual);
  } else if (key > node->key) {
    return size(node->left) + 1 + countLess(node->right, key, countEqual);
  } else {
    return size(node->left) + (countEqual ? 1 : 0);
  }
}

USize countGreater(ConstNodePtr node, K key, bool countEqual = false) const {
  if (node == nullptr) {
    return 0;
  } else if (key < node->key) {
    return size(node->right) + 1 + countGreater(node->left, key, countEqual);
  } else if (key > node->key) {
    return countGreater(node->right, key, countEqual);
  } else {
    return size(node->right) + (countEqual ? 1 : 0);
  }
}
```

## Reference Code

The following code is a `Map` implemented with SBT, that is, an ordered map without duplicate keys:

??? note "Complete Code"
    ```cpp
    --8<-- "docs/ds/code/size-balanced-tree/SizeBalancedTreeMap.hpp"
    ```
