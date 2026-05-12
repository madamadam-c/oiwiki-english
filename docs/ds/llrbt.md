author: c-forrest, Enter-tainer, giiiiiithub, hly1204, iamtwz, Ir1d, kigawas, ksyx, luxuryspark567, mgt, orzAtalod, sandyzikun, SunsetGlow95, Tiphereth-A, current2020, untitledunrevised, yuhuoji

Left-leaning red-black tree is a variant of [red-black tree](./rbtree.md). It imposes restrictions on the positions of red links (nodes), so that its insertion and deletion operations correspond one-to-one with those of a [2-3 tree](https://en.wikipedia.org/wiki/2%E2%80%933_tree).

We assume that the reader has already mastered at least one rotation-based balanced tree, so this article does not explain rotation operations.

## Red-Black Tree

### Properties

A red-black tree satisfies the following properties:

1.  Every node is either red or black.
2.  NIL nodes (empty leaf nodes) are black.
3.  All children of a red node must be black; that is, no path from a leaf to the root may contain two consecutive red nodes.
4.  Every simple path from any node to each leaf in its subtree contains the same number of black nodes. (black-height balance)

This ensures that the longest path from the root to any leaf (alternating red and black) is no more than twice the shortest path (all black), thereby guaranteeing balance.

Maintaining these properties is relatively complicated. If we insert a node, it must first be colored red; otherwise property 4 is broken. Even so, property 3 may still be broken, so adjustments are needed. Deleting nodes is even more troublesome. Similar to insertion, we cannot delete a black node directly, or black-height balance will be broken. How can these problems be handled conveniently?

## Left-Leaning Red-Black Tree

### Explanation

A left-leaning red-black tree is an easy-to-implement red-black tree variant.

In the following diagrams of left-leaning red-black trees, edges have colors rather than nodes. We conventionally use a node's color to refer to the color of its parent edge.

Left-leaning red-black trees add an extra restriction to red-black trees. For the left and right children of a black node:

-   either both are black;
-   or the left child is red and the right child is black.

Valid cases:

![llrbt1](./images/llrbt-1.png)

Invalid cases:

![llrbt2](./images/llrbt-2.png)

This is the "left-leaning" property of the tree: red links may only lean left.

### Process

#### Insertion

We first use ordinary BST insertion to insert a red leaf node at the bottom of the tree, then adjust from bottom to top so that the resulting tree still satisfies the properties of a left-leaning red-black tree. The adjustment process is described below:

![llrbt3](./images/llrbt-3.png)

After insertion, a right-leaning red link may appear, so a left rotation is needed for this case:

![llrbt4](./images/llrbt-4.png)

After the left rotation, two consecutive left-leaning red links may be produced:

![llrbt5](./images/llrbt-5.png)

Therefore, a right rotation is needed. After the right rotation, we should perform `color_flip`, that is, flip the colors of this node and its two children:

![llrbt6](./images/llrbt-6.png)

This eliminates the right-leaning red link.

??? note "Reference Code (Partial)"
    ```cpp
    template <class Key, class Compare>
    typename Set<Key, Compare>::Node *Set<Key, Compare>::fix_up(
        Set::Node *root) const {
      if (is_red(root->rc) && !is_red(root->lc))  // fix right leaned red link
        root = rotate_left(root);
      if (is_red(root->lc) &&
          is_red(root->lc->lc))  // fix doubly linked left leaned red link
        // if (root->lc == nullptr), then the second expr won't be evaluated
        root = rotate_right(root);
      if (is_red(root->lc) && is_red(root->rc))
        // break up 4 node
        color_flip(root);
      root->size = size(root->lc) + size(root->rc) + 1;
      return root;
    }
    
    template <class Key, class Compare>
    typename Set<Key, Compare>::Node_Set<Key, Compare>::insert(
        Set::Node_root, const Key &key) const {
      if (root == nullptr) return new Node(key, kRed, 1);
      if (root->key == key)
        ;
      else if (cmp\_(key, root->key))  // if (key < root->key)
        root->lc = insert(root->lc, key);
      else
        root->rc = insert(root->rc, key);
      return fix_up(root);
    }
    ```

#### Deletion

Deletion is based on this idea: we cannot delete a black node, because that would break black height. Therefore, we must ensure that the node finally deleted is red.

##### Deleting the Minimum Node

First, try deleting the minimum value in the whole tree.

How can we guarantee that the node finally deleted is red? During the downward recursion, we need to maintain the following property: if the current node is `h`, then either `h` is red or `h->lc` is red.

Consider why this is correct. If we can successfully maintain this property through rotations and color flips, then when we reach the minimum node `h_min`, either `h_min` is red or the left subtree of `h_min` is red. But `h_min` has no left subtree at all! Therefore, the minimum node must be red. Since it is red, we can safely delete it and then adjust the tree with the same idea used for insertion.

Now consider how to satisfy this property. Note that during downward recursion we will **temporarily** break several properties of the left-leaning red-black tree, but they will be restored when returning from recursion.

The following diagram describes a relatively simple case. Here `h->rc->lc` is black, and only one color flip is needed:

![llrbt-7](./images/llrbt-7.png)

After the flip shown above, `h->rc` and `h->rc->lc` will not form consecutive red links.

But if `h->rc->lc` is red, the situation is more complicated:

![llrbt-8](./images/llrbt-8.png)

If we only flip colors, consecutive red links will be produced. Since this situation cannot be repaired when returning from recursion, it must be handled specially.

Deletion can then be performed:

??? note "Reference Code (Partial)"
    ```cpp
    template <class Key, class Compare>
    typename Set<Key, Compare>::Node *Set<Key, Compare>::move_red_left(
        Set::Node *root) const {
      color_flip(root);
      if (is_red(root->rc->lc)) {
        // assume that root->rc != nullptr when calling this function
        root->rc = rotate_right(root->rc);
        root = rotate_left(root);
        color_flip(root);
      }
      return root;
    }
    
    template <class Key, class Compare>
    typename Set<Key, Compare>::Node *Set<Key, Compare>::delete_min(
        Set::Node *root) const {
      if (root->lc == nullptr) {
        delete root;
        return nullptr;
      }
      if (!is_red(root->lc) && !is_red(root->lc->lc)) {
        // make sure either root->lc or root->lc->lc is red
        // thus make sure we will delete a red node in the end
        root = move_red_left(root);
      }
      root->lc = delete_min(root->lc);
      return fix_up(root);
    }
    ```

##### Deleting an Arbitrary Node

First consider deleting a leaf. Similar to deleting the minimum value, deleting any value also requires maintaining an invariant. This time it is special because we may go either left or right, not only left. Therefore, the invariant during deletion is: if we go left and the current node is `h`, then either `h` is red or `h->lc` is red; if we go right and the current node is `h`, then either `h` is red or `h->rc` is red. This guarantees that we eventually delete a red node.

Now consider deleting a non-leaf node. We only need to find the minimum node in its right subtree (if it has one), replace the current node's value with that minimum value, and finally delete the minimum node from the right subtree.

![llrbt-9](./images/llrbt-9.png)

What if there is no right subtree? We need to rotate the left subtree over, so this problem does not occur.

??? note "Reference Code (Partial)"
    ```cpp
    template <class Key, class Compare>
    typename Set<Key, Compare>::Node *Set<Key, Compare>::delete_arbitrary(
        Set::Node *root, Key key) const {
      if (cmp_(key, root->key)) {
        // key < root->key
        if (!is_red(root->lc) && !(is_red(root->lc->lc)))
          root = move_red_left(root);
        // ensure the invariant: either root->lc or root->lc->lc (or root and
        // root->lc after dive into the function) is red, to ensure we will
        // eventually delete a red node. therefore we will not break the black
        // height balance
        root->lc = delete_arbitrary(root->lc, key);
      } else {
        // key >= root->key
        if (is_red(root->lc)) root = rotate_right(root);
        if (key == root->key && root->rc == nullptr) {
          delete root;
          return nullptr;
        }
        if (!is_red(root->rc) && !is_red(root->rc->lc)) root = move_red_right(root);
        if (key == root->key) {
          root->key = get_min(root->rc);
          root->rc = delete_min(root->rc);
        } else {
          root->rc = delete_arbitrary(root->rc, key);
        }
      }
      return fix_up(root);
    }
    ```

## Implementation

The following code is a `Set` implemented with a left-leaning red-black tree, that is, an ordered set without duplicate elements:

??? note "Reference Code"
    ```cpp
    #include <algorithm>
    #include <memory>
    #include <vector>
    
    template <class Key, class Compare = std::less<Key>>
    class Set {
     private:
      enum NodeColor { kBlack = 0, kRed = 1 };
    
      struct Node {
        Key key;
        Node *lc{nullptr}, *rc{nullptr};
        size_t size{0};
        NodeColor color;  // the color of the parent link
    
        Node(Key key, NodeColor color, size_t size)
            : key(key), color(color), size(size) {}
    
        Node() = default;
      };
    
      void destroyTree(Node *root) const {
        if (root != nullptr) {
          destroyTree(root->lc);
          destroyTree(root->rc);
          root->lc = root->rc = nullptr;
          delete root;
        }
      }
    
      bool is_red(const Node *nd) const {
        return nd == nullptr ? false : nd->color;  // kRed == 1, kBlack == 0
      }
    
      size_t size(const Node *nd) const { return nd == nullptr ? 0 : nd->size; }
    
      Node *rotate_left(Node *node) const {
        // left rotate a red link
        //          <1>                   <2>
        //        /    \\               //    \
        //       *      <2>    ==>     <1>     *
        //             /   \          /   \
        //            *     *        *     *
        Node *res = node->rc;
        node->rc = res->lc;
        res->lc = node;
        res->color = node->color;
        node->color = kRed;
        res->size = node->size;
        node->size = size(node->lc) + size(node->rc) + 1;
        return res;
      }
    
      Node *rotate_right(Node *node) const {
        // right rotate a red link
        //            <1>               <2>
        //          //    \           /    \\
        //         <2>     *   ==>   *      <1>
        //        /   \                    /   \
        //       *     *                  *     *
        Node *res = node->lc;
        node->lc = res->rc;
        res->rc = node;
        res->color = node->color;
        node->color = kRed;
        res->size = node->size;
        node->size = size(node->lc) + size(node->rc) + 1;
        return res;
      }
    
      NodeColor neg_color(NodeColor n) const { return n == kBlack ? kRed : kBlack; }
    
      void color_flip(Node *node) const {
        node->color = neg_color(node->color);
        node->lc->color = neg_color(node->lc->color);
        node->rc->color = neg_color(node->rc->color);
      }
    
      Node *insert(Node *root, const Key &key) const;
      Node *delete_arbitrary(Node *root, Key key) const;
      Node *delete_min(Node *root) const;
      Node *move_red_right(Node *root) const;
      Node *move_red_left(Node *root) const;
      Node *fix_up(Node *root) const;
      const Key &get_min(Node *root) const;
      void serialize(Node *root, std::vector<Key> *) const;
      void print_tree(Set::Node *root, int indent) const;
      Compare cmp_ = Compare();
      Node *root_{nullptr};
    
     public:
      using KeyType = Key;
      using ValueType = Key;
      using SizeType = std::size_t;
      using DifferenceType = std::ptrdiff_t;
      using KeyCompare = Compare;
      using ValueCompare = Compare;
      using Reference = Key &;
      using ConstReference = const Key &;
    
      Set() = default;
    
      Set(Set &) = default;
    
      Set(Set &&) noexcept = default;
    
      ~Set() { destroyTree(root_); }
    
      SizeType size() const;
    
      SizeType count(const KeyType &key) const;
    
      SizeType erase(const KeyType &key);
    
      void clear();
    
      void insert(const KeyType &key);
    
      bool empty() const;
    
      std::vector<Key> serialize() const;
    
      void print_tree() const;
    };
    
    template <class Key, class Compare>
    typename Set<Key, Compare>::SizeType Set<Key, Compare>::count(
        ConstReference key) const {
      Node *x = root_;
      while (x != nullptr) {
        if (key == x->key) return 1;
        if (cmp_(key, x->key))  // if (key < x->key)
          x = x->lc;
        else
          x = x->rc;
      }
      return 0;
    }
    
    template <class Key, class Compare>
    typename Set<Key, Compare>::SizeType Set<Key, Compare>::erase(
        const KeyType &key) {
      if (count(key) > 0) {
        if (!is_red(root_->lc) && !(is_red(root_->rc))) root_->color = kRed;
        root_ = delete_arbitrary(root_, key);
        if (root_ != nullptr) root_->color = kBlack;
        return 1;
      } else {
        return 0;
      }
    }
    
    template <class Key, class Compare>
    void Set<Key, Compare>::clear() {
      destroyTree(root_);
      root_ = nullptr;
    }
    
    template <class Key, class Compare>
    void Set<Key, Compare>::insert(const KeyType &key) {
      root_ = insert(root_, key);
      root_->color = kBlack;
    }
    
    template <class Key, class Compare>
    bool Set<Key, Compare>::empty() const {
      return size(root_) == 0;
    }
    
    template <class Key, class Compare>
    typename Set<Key, Compare>::Node *Set<Key, Compare>::insert(
        Set::Node *root, const Key &key) const {
      if (root == nullptr) return new Node(key, kRed, 1);
      if (root->key == key)
        ;
      else if (cmp_(key, root->key))  // if (key < root->key)
        root->lc = insert(root->lc, key);
      else
        root->rc = insert(root->rc, key);
      return fix_up(root);
    }
    
    template <class Key, class Compare>
    typename Set<Key, Compare>::Node *Set<Key, Compare>::delete_min(
        Set::Node *root) const {
      if (root->lc == nullptr) {
        delete root;
        return nullptr;
      }
      if (!is_red(root->lc) && !is_red(root->lc->lc)) {
        // make sure either root->lc or root->lc->lc is red
        // thus make sure we will delete a red node in the end
        root = move_red_left(root);
      }
      root->lc = delete_min(root->lc);
      return fix_up(root);
    }
    
    template <class Key, class Compare>
    typename Set<Key, Compare>::Node *Set<Key, Compare>::move_red_right(
        Set::Node *root) const {
      color_flip(root);
      if (is_red(root->lc->lc)) {  // assume that root->lc != nullptr when calling
                                   // this function
        root = rotate_right(root);
        color_flip(root);
      }
      return root;
    }
    
    template <class Key, class Compare>
    typename Set<Key, Compare>::Node *Set<Key, Compare>::move_red_left(
        Set::Node *root) const {
      color_flip(root);
      if (is_red(root->rc->lc)) {
        // assume that root->rc != nullptr when calling this function
        root->rc = rotate_right(root->rc);
        root = rotate_left(root);
        color_flip(root);
      }
      return root;
    }
    
    template <class Key, class Compare>
    typename Set<Key, Compare>::Node *Set<Key, Compare>::fix_up(
        Set::Node *root) const {
      if (is_red(root->rc) && !is_red(root->lc))  // fix right leaned red link
        root = rotate_left(root);
      if (is_red(root->lc) &&
          is_red(root->lc->lc))  // fix doubly linked left leaned red link
        // if (root->lc == nullptr), then the second expr won't be evaluated
        root = rotate_right(root);
      if (is_red(root->lc) && is_red(root->rc))
        // break up 4 node
        color_flip(root);
      root->size = size(root->lc) + size(root->rc) + 1;
      return root;
    }
    
    template <class Key, class Compare>
    const Key &Set<Key, Compare>::get_min(Set::Node *root) const {
      Node *x = root;
      // will crash as intended when root == nullptr
      for (; x->lc != nullptr; x = x->lc);
      return x->key;
    }
    
    template <class Key, class Compare>
    typename Set<Key, Compare>::SizeType Set<Key, Compare>::size() const {
      return size(root_);
    }
    
    template <class Key, class Compare>
    typename Set<Key, Compare>::Node *Set<Key, Compare>::delete_arbitrary(
        Set::Node *root, Key key) const {
      if (cmp_(key, root->key)) {
        // key < root->key
        if (!is_red(root->lc) && !(is_red(root->lc->lc)))
          root = move_red_left(root);
        // ensure the invariant: either root->lc or root->lc->lc (or root and
        // root->lc after dive into the function) is red, to ensure we will
        // eventually delete a red node. therefore we will not break the black
        // height balance
        root->lc = delete_arbitrary(root->lc, key);
      } else {
        // key >= root->key
        if (is_red(root->lc)) root = rotate_right(root);
        if (key == root->key && root->rc == nullptr) {
          delete root;
          return nullptr;
        }
        if (!is_red(root->rc) && !is_red(root->rc->lc)) root = move_red_right(root);
        if (key == root->key) {
          root->key = get_min(root->rc);
          root->rc = delete_min(root->rc);
        } else {
          root->rc = delete_arbitrary(root->rc, key);
        }
      }
      return fix_up(root);
    }
    
    template <class Key, class Compare>
    std::vector<Key> Set<Key, Compare>::serialize() const {
      std::vector<int> v;
      serialize(root_, &v);
      return v;
    }
    
    template <class Key, class Compare>
    void Set<Key, Compare>::serialize(Set::Node *root,
                                      std::vector<Key> *res) const {
      if (root == nullptr) return;
      serialize(root->lc, res);
      res->push_back(root->key);
      serialize(root->rc, res);
    }
    
    template <class Key, class Compare>
    void Set<Key, Compare>::print_tree(Set::Node *root, int indent) const {
      if (root == nullptr) return;
      print_tree(root->lc, indent + 4);
      std::cout << std::string(indent, '-') << root->key << std::endl;
      print_tree(root->rc, indent + 4);
    }
    
    template <class Key, class Compare>
    void Set<Key, Compare>::print_tree() const {
      print_tree(root_, 0);
    }
    ```

## Relationship with 2-3 Trees

A 2-3 tree is a B-tree of order 3. Every node is either a 2-node or a 3-node and stores one or two data elements. Non-leaf 2-nodes and 3-nodes can have only two or three children respectively. In addition, all data stored in a 2-3 tree is ordered.

2-3 trees and left-leaning red-black trees are essentially equivalent. A node in a 2-3 tree can store one or two elements, while a node in a red-black tree can store only one element. As shown below, a 2-node in a 2-3 tree corresponds to a black node, and a 3-node corresponds to a red node plus a black node (the two can be regarded as parallel).

![2-3-tree-rbt](images/2-3-tree-rbt-1.svg)

![2-3-tree-rbt](images/2-3-tree-rbt-2.svg)

The following diagram shows the left-leaning red-black tree corresponding to a 2-3 tree.

![2-3-tree-rbt](images/2-3-tree-rbt-3.svg)

Insertion and deletion in 2-3 trees and left-leaning red-black trees correspond one-to-one.[^23-vs-llrbt]

## References and Further Reading

-   [Left-Leaning Red-Black Trees](https://sedgewick.io/wp-content/themes/sedgewick/papers/2008LLRB.pdf)-  Robert Sedgewick Princeton University
-   [Balanced Search Trees](https://algs4.cs.princeton.edu/lectures/keynote/33BalancedSearchTrees-2x2.pdf)-\_Algorithms\_Robert Sedgewick | Kevin Wayne

[^23-vs-llrbt]: [This blog post](https://riteme.site/blog/2016-3-12/2-3-tree-and-red-black-tree.html) provides a detailed description. The "red-black tree" mentioned in that article actually refers to a "left-leaning red-black tree".
