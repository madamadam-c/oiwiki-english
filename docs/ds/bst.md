author: 2323122, aofall, AtomAlpaca, Bocity, CoelacanthusHex, countercurrent-time, Early0v0, Enter-tainer, fearlessxjdx, Great-designer, H-J-Granger, hsfzLZH1, iamtwz, Ir1d, ksyx, Marcythm, NachtgeistW, ouuan, Persdre, shuzhouliu, StudyingFather, SukkaW, Tiphereth-A, wsyhb, Yesphet, yuhuoji, lingkerio, bililateral, q-wind

## Definition

A binary search tree is a binary-tree data structure defined as follows:

1.  The empty tree is a binary search tree.
2.  If the left subtree of a binary search tree is nonempty, then all additional key values in the left subtree are smaller than the root's value.
3.  If the right subtree of a binary search tree is nonempty, then all additional key values in the right subtree are greater than the root's value.
4.  The left and right subtrees of a binary search tree are both binary search trees.

The time spent by basic operations on a binary search tree is proportional to the tree height. For a binary search tree with $n$ nodes, the best complexity of these operations is $O(\log n)$ and the worst complexity is $O(n)$. The expected height of a randomly built binary search tree is $O(\log n)$.

## Procedures

### Binary Search Tree Node Definition

???+ note "Implementation"
    ```cpp
    struct TreeNode {
      int key;
      TreeNode* left;
      TreeNode* right;
      // Maintains extra information, such as height and node count.
      int size;   // Size of the subtree rooted at this node.
      int count;  // Number of duplicates of this node's value.
    
      TreeNode(int value)
          : key(value), size(1), count(1), left(nullptr), right(nullptr) {}
    };
    ```

### Traversing A Binary Search Tree

From the recursive definition of a binary search tree, its inorder traversal gives a nondecreasing sequence of key values. The time complexity is $O(n)$.

Code for traversing a binary search tree:

???+ note "Implementation"
    ```cpp
    void inorderTraversal(TreeNode* root) {
      if (root == nullptr) {
        return;
      }
      inorderTraversal(root->left);
      std::cout << root->key << " ";
      inorderTraversal(root->right);
    }
    ```

### Finding The Minimum/Maximum

By the properties of a binary search tree, the minimum value is at the end of the left chain, and the maximum value is at the end of the right chain. The time complexity is $O(h)$.

???+ note "Implementation"
    ```cpp
    int findMin(TreeNode* root) {
      if (root == nullptr) {
        return -1;
      }
      while (root->left != nullptr) {
        root = root->left;
      }
      return root->key;
    }
    
    int findMax(TreeNode* root) {
      if (root == nullptr) {
        return -1;
      }
      while (root->right != nullptr) {
        root = root->right;
      }
      return root->key;
    }
    ```

### Searching For An Element

Search for a node with value `value` in the binary search tree rooted at `root`.

Cases:

-   If `root` is empty, return `false`.
-   If `root`'s key equals `value`, return `true`.
-   If `root`'s key is greater than `value`, continue searching in `root`'s left subtree.
-   If `root`'s key is less than `value`, continue searching in `root`'s right subtree.

The time complexity is $O(h)$.

???+ note "Implementation"
    ```cpp
    bool search(TreeNode* root, int target) {
      if (root == nullptr) {
        return false;
      }
      if (root->key == target) {
        return true;
      } else if (target < root->key) {
        return search(root->left, target);
      } else {
        return search(root->right, target);
      }
    }
    ```

Insertion, deletion, and modification all first search in the binary search tree.

### Inserting An Element

Insert a node with value `value` into the binary search tree rooted at `root`.

Cases:

-   If `root` is empty, directly return a new node with value `value`.
-   If `root`'s key equals `value`, increase the extra field that stores the occurrence count by $1$.
-   If `root`'s key is greater than `value`, insert into `root`'s left subtree.
-   If `root`'s key is less than `value`, insert into `root`'s right subtree.

The time complexity is $O(h)$.

???+ note "Implementation"
    ```cpp
    TreeNode* insert(TreeNode* root, int value) {
      if (root == nullptr) {
        return new TreeNode(value);
      }
      if (value < root->key) {
        root->left = insert(root->left, value);
      } else if (value > root->key) {
        root->right = insert(root->right, value);
      } else {
        root->count++;  // Equal node value; increase duplicate count.
      }
      root->size = root->count + (root->left ? root->left->size : 0) +
                   (root->right ? root->right->size : 0);  // Update subtree size.
      return root;
    }
    ```

### Deleting An Element

Delete a node with value `value` from the binary search tree rooted at `root`.

First search for the node whose key is `value`, then consider:

-   If its additional `count` is greater than $1$, only decrease `count`.

-   If its additional `count` is $1$:

    -   If `root` is a leaf, delete it directly.

    -   If `root` is a chain node, i.e. has only one child, return that child.

    -   If `root` has two nonempty children, usually replace it by the maximum value in its left subtree (the rightmost node of the left subtree) or the minimum value in its right subtree (the leftmost node of the right subtree), then delete that replacement node.

The time complexity is $O(h)$.

???+ note "Implementation"
    Calling `root = remove(root, 1)` means deleting the node with value 1 from the tree rooted at `root`, and returning the new root.
    
    ```cpp
    // Returns the new root after deleting value.
    TreeNode* remove(TreeNode* root, int value) {
      if (root == nullptr) {
        return root;
      }
      if (value < root->key) {
        root->left = remove(root->left, value);
      } else if (value > root->key) {
        root->right = remove(root->right, value);
      } else {
        if (root->count > 1) {
          root->count--;  // Duplicate count is greater than 1; decrease it.
        } else {
          if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
          } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
          } else {
            TreeNode* successor = findMinNode(root->right);
            root->key = successor->key;
            root->count = successor->count;  // Update duplicate count.
            // If successor->count > 1, this node should still be deleted;
            // otherwise later deletion would only decrease the duplicate count.
            successor->count = 1;
            root->right = remove(root->right, successor->key);
          }
        }
      }
      // Continue maintaining size. Do not write --root->size because value
      // may not be in the tree, so deletion may not have happened.
      root->size = root->count + (root->left ? root->left->size : 0) +
                   (root->right ? root->right->size : 0);
      return root;
    }
    
    // Here the minimum in the right subtree is used as an example.
    TreeNode* findMinNode(TreeNode* root) {
      while (root->left != nullptr) {
        root = root->left;
      }
      return root;
    }
    ```

### Querying The Rank Of An Element

The rank is defined as the number of elements before the first equal element after sorting in ascending order, plus one.

To find an element's rank, start at the root and move toward the element. When moving right, add the size of the left child plus the duplicate count of the current node. At the destination, add the size of the left subtree plus one.

The time complexity is $O(h)$.

???+ note "Implementation"
    ```cpp
    int queryRank(TreeNode* root, int v) {
      if (root == nullptr) return 0;
      if (root->key == v) return (root->left ? root->left->size : 0) + 1;
      if (root->key > v) return queryRank(root->left, v);
      return queryRank(root->right, v) + (root->left ? root->left->size : 0) +
             root->count;
    }
    ```

### Finding The Element With Rank k

In a subtree, the root's rank depends on the size of its left subtree.

-   If the left subtree size is at least $k$, the element lies in the left subtree.

-   If the left subtree size is in $[k-\textit{count},k-1]$, where `count` is the occurrence count of the current node's value, the element is the subtree root.

-   If the left subtree size is less than $k-\textit{count}$, the element lies in the right subtree.

The time complexity is $O(h)$.

???+ note "Implementation"
    ```cpp
    int querykth(TreeNode* root, int k) {
      if (root == nullptr) return -1;  // Or return another suitable value.
      if (root->left) {
        if (root->left->size >= k) return querykth(root->left, k);
        if (root->left->size + root->count >= k) return root->key;
      } else {
        if (k <= root->count) return root->key;
      }
      return querykth(root->right,
                      k - (root->left ? root->left->size : 0) - root->count);
    }
    ```

## Introduction To Balanced Trees

One purpose of using search trees is to reduce the time for insertion, deletion, modification, and lookup. Insertion, deletion, and modification all include lookup.

For lookup efficiency, if a tree has height $h$, searching for a key requires at most $h$ comparisons in the worst case. The lookup time complexity, also called average search length (ASL), is at most $O(h)$. In an ideal binary search tree, all operation times can be reduced to $O(\log n)$, where n is the total number of nodes.

However, $O(\log n)$ is only the ideal case. In the worst case, a search tree may degenerate into a linked list. For example, if every node of a binary search tree has only a right child, then it behaves like a linked list, and all operations take $O(n)$ time.

Thus operation complexity is related to tree height $h$. This motivates balanced trees, which maintain tree height, or balance, through certain operations to reduce complexity.

### Definition Of Balance

Different balanced trees define **balance** differently. For example, if a binary search tree rooted at T has left and right subtrees with very different heights, or the left subtree has far more nodes than the right subtree, the tree is clearly not balanced.

For binary search trees, a common definition is: for every node in the tree rooted at T, the heights of its left and right subtrees differ by at most 1.

-   In a [Splay tree](splay.md), every access operation, whether search, insertion, or deletion, moves the accessed node to the root.
-   In an [AVL tree](avl.md), every node N maintains the height of the tree rooted at N. An AVL tree is balanced iff both subtrees are AVL trees and $|height(T->left) - height(T->right)| \leq 1$.
-   In a [Size Balanced Tree](sbt.md), every node N maintains the number of nodes `size` in the tree rooted at N. Its balance definition requires the `size` of any node to be no smaller than the `size` of all children of its sibling.

For search trees with the same set of element values, the balanced state may not be unique. Two different search trees may contain the same set of element values and both be balanced.

### Balance Adjustment Process

Adjusting a search tree that violates the balance condition can restore balance.

For binary balanced trees, adjustment operations include **left rotation (Left Rotate, or zag)** and **right rotation (Right Rotate, or zig)**. Because adjustment must preserve the inorder traversal sequence, both operations keep that sequence unchanged.

Right rotation, also called single right rotation or LL balance rotation, is introduced first. A right rotation on node $A$ rotates node $A$'s left child $B$ upward to the right to replace $A$ as the root; $A$ rotates downward to become the root of $B$'s right subtree; and $B$'s original right subtree becomes $A$'s left subtree.

![bst-rotate](images/bst-rotate.svg)

A right rotation changes only three groups of node links, equivalent to cyclically permuting three edges, so one node must be temporarily stored before updating links.

The usual update order for a right rotation is: temporarily store node $B$ (the new root), set $A$'s left child to $B$'s right subtree $T2$, set $B$'s right child pointer to $A$, and finally set $A$'s parent to the temporary $B$.

Similarly, there is a corresponding left rotation, also called single left rotation or RR balance rotation. Left rotation and right rotation are mirror operations.

The following code gives left and right rotations.

???+ note "Implementation"
    ```cpp
    TreeNode* rotateLeft(TreeNode* root) {
      TreeNode* newRoot = root->right;
      root->right = newRoot->left;
      newRoot->left = root;
      // Update information for related nodes.
      updateHeight(root);
      updateHeight(newRoot);
      return newRoot;  // Return the new root.
    }
    
    TreeNode* rotateRight(TreeNode* root) {
      TreeNode* newRoot = root->left;
      root->left = newRoot->right;
      newRoot->right = root;
      updateHeight(root);
      updateHeight(newRoot);
      return newRoot;
    }
    ```

For this sample code, the caller must save `root`'s parent `pre`. The function returns a pointer to the new root; just set `pre` to point to it.

#### Four Cases Of Balance Violation

Although different binary balanced trees have different definitions, they mainly differ in the information maintained at each node and the information updated after rotations. There are only four kinds of balance violation in binary balanced trees, and adjustment uses only left and right rotations.

LL type: T's left child's left subtree is too long, breaking balance.

Adjustment: right-rotate node T.

![bst-LL](images/bst-LL.svg)

RR type: similar to LL, T's right child's right subtree is too long.

Adjustment: left-rotate node T.

![bst-RR](images/bst-RR.svg)

LR type: T's left child's right subtree is too long.

Adjustment: first left-rotate node L to become the LL type, then right-rotate node T.

![bst-LR](images/bst-LR.svg)

RL type: similar to LR, T's right child's left subtree is too long.

Adjustment: first right-rotate node R to become the RR type, then left-rotate node T.

![bst-RL](images/bst-RL.svg)
