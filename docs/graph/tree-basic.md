## Introduction

Trees in graph theory look similar to trees in real life, except we usually consider the root at the top when solving problems. This data structure looks like an inverted tree, hence the name.

## Definitions

A tree without a fixed root is called an **unrooted tree**. An unrooted tree has several equivalent formal definitions:

-   A connected undirected graph with $n$ nodes and $n-1$ edges

-   A connected acyclic undirected graph

-   An undirected graph where there exists exactly one simple path between any two nodes

-   A connected graph where every edge is a bridge

-   A graph with no cycles, and adding an edge between any two distinct vertices creates exactly one cycle

Based on an unrooted tree, if we designate a node as the **root**, we get a **rooted tree**. Rooted trees are often still represented as undirected graphs, but with a defined parent-child relationship between nodes. See below for details.

## Tree-Related Definitions

### Applicable to Both Unrooted and Rooted Trees

-   **Forest**: A graph where each connected component is a tree. By definition, a single tree is also a forest.

-   **Spanning tree**: A spanning subgraph of a connected undirected graph that is also a tree. That is, selecting $n-1$ edges from the edge set to connect all vertices.

-   **Leaf node of an unrooted tree**: A node with degree at most 1.

    ???+ question "Why not exactly degree 1?"
        Consider $n = 1$.

-   **Leaf node of a rooted tree**: A node with no children.

### Only Applicable to Rooted Trees

-   **Parent node**: For each node except the root, defined as the second node on the path from that node to the root.
    The root has no parent.
-   **Ancestor**: Any node on the path from a node to the root, excluding the node itself.
    The root's ancestor set is empty.
-   **Child node**: If $u$ is the parent of $v$, then $v$ is a child of $u$.
    The order of children is generally not distinguished, except for binary trees.
-   **Depth of a node**: The number of edges on the path to the root.
-   **Height of a tree**: The maximum depth of all nodes.
-   **Sibling**: Multiple children of the same parent are siblings.
-   **Descendant**: A child or a descendant of a child.
    Alternatively, if $u$ is an ancestor of $v$, then $v$ is a descendant of $u$.

![tree-definition.svg](images/tree-definition.svg)

-   **Subtree**: The subgraph formed by a node after removing the edge connecting it to its parent.

    ![tree-definition-subtree.svg](images/tree-definition-subtree.svg)

## Special Trees

-   **Chain/Path graph**: A tree where no node is incident to more than 2 edges.

-   **Star**: A tree where there exists a vertex $u$ such that all other vertices are connected to $u$.

-   **Rooted binary tree**: A rooted tree where each node has at most two children. The two children are often distinguished as the left child and right child.
    In most cases, **binary tree** refers to a rooted binary tree.

-   **Full/Proper binary tree**: A binary tree where each node has either 0 or 2 children. In other words, each node is either a leaf or has both left and right subtrees non-empty.

    ![](images/tree-binary-proper.svg)

-   **Complete binary tree**: A binary tree where all levels except possibly the last are completely filled, and all nodes in the last level are as far left as possible.

    ![](images/tree-binary-complete.svg)

-   **Perfect binary tree**: A binary tree where all leaf nodes have the same depth, and all non-leaf nodes have exactly 2 children.

    ![](images/tree-binary-perfect.svg)

???+ warning "Warning"
    The Chinese translation of "proper binary tree" is not fixed, and the definitions of "complete binary tree" and "full binary tree" vary across different textbooks. Always interpret based on context.

What OIers call "full binary tree" usually refers to perfect binary tree.

## Storage

### Storing Only Parent Nodes

Use an array `parent[N]` to record each node's parent.

This method provides limited information and is not convenient for top-down traversal. It is commonly used in bottom-up dynamic programming problems.

### Adjacency List

-   For unrooted trees: Create a linear list for each node, recording all connected nodes.
    ```cpp
    std::vector<int> adj[N];
    ```
-   For rooted trees:
    -   Method 1: If the input is an undirected graph, we can still use the above structure. Below we explain how to distinguish the parent-child relationship.
    -   Method 2: If the input guarantees the parent-child relationship, we can use this information. Create a linear list for each node, recording all its children; if needed, also record its parent in another array.
        ```cpp
        std::vector<int> children[N];
        int parent[N];
        ```
        Of course, other structures (like linked lists) can replace `std::vector`.

### Left Child Right Sibling Representation

#### Process

For rooted trees, there exists a simple representation method.

First, assign an arbitrary order to all children of each node.

Then, for each node, record two values: its **first child** `child[u]` and its **next sibling** `sib[u]`. If there are no children, `child[u]` is empty; if the node is the last child of its parent, `sib[u]` is empty.

#### Implementation

Traversing all children of a node can be done as follows:

```cpp
int v = child[u];  // start from the first child
while (v != EMPTY_NODE) {
  // ...
  // process child v
  // ...
  v = sib[v];  // move to the next sibling
}
```

This can also be simplified to:

```cpp
for (int v = child[u]; v != EMPTY_NODE; v = sib[v]) {
  // ...
  // process child v
  // ...
}
```

### Binary Tree

We need to record the left and right children of each node.

???+ note "Implementation"
    ```cpp
    int parent[N];
    int lch[N], rch[N];
    // -- or --
    int child[N][2];
    ```

## Tree Traversal

### DFS on Trees

DFS on a tree is the process of first visiting the root, then recursively visiting each child's subtree.

It can be used to compute the depth, parent, and other information for each node.

### Binary Tree DFS Traversal

#### Preorder Traversal

![preorder](images/tree-basic-preorder.svg)

Traverse the binary tree in **root, left, right** order.

???+ note "Implementation"
    ```cpp
    void preorder(BiTree* root) {
      if (root) {
        cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
      }
    }
    ```

#### Inorder Traversal

![inorder](images/tree-basic-inorder.svg)

Traverse the binary tree in **left, root, right** order.

???+ note "Implementation"
    ```cpp
    void inorder(BiTree* root) {
      if (root) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
      }
    }
    ```

#### Postorder Traversal

![postorder](images/tree-basic-postorder.svg)

Traverse the binary tree in **left, right, root** order.

???+ note "Implementation"
    ```cpp
    void postorder(BiTree* root) {
      if (root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->key << " ";
      }
    }
    ```

#### Reconstruction

Given the inorder traversal and one other traversal, we can determine the third traversal.

![reverse](images/tree-basic-reverse.svg)

1.  The first element of preorder and the last element of postorder are both the root.
2.  First determine the root, then based on inorder, vertices to the left of the root form the left subtree, and vertices to the right form the right subtree.
3.  Each subtree can be treated as a completely new tree, following the same rules.

### BFS on Trees

Start from the root and strictly traverse by level.

During BFS, we can also compute the depth and parent of each node.

#### Level Order Traversal

Level order traversal traverses nodes horizontally level by level from root to leaves. By the definition of BFS, the traversal result is a level order. However, level order traversal requires distinguishing between different levels, so the result is usually represented as a 2D array.

For example, the level order traversal of the tree in the diagram is `[[1], [2, 3, 4], [5, 6]]` (left to right within each level).

![tree-basic-levelOrder](images/tree-basic-levelOrder.svg)

???+ note "Implementation"
    ```cpp
    vector<vector<int>> levelOrder(Node* root) {
      if (!root) {
        return {};
      }
      vector<vector<int>> res;
      queue<Node*> q;
      q.push(root);
      while (!q.empty()) {
        int currentLevelSize = q.size();  // number of nodes in current level
        res.push_back(vector<int>());
        for (int i = 0; i < currentLevelSize; ++i) {
          Node* cur = q.front();
          q.pop();
          res.back().push_back(cur->val);
          for (Node* child : cur->children) {  // add all children to queue
            q.push(child);
          }
        }
      }
      return res;
    }
    ```

### Morris Traversal for Binary Trees

The core problem of binary tree traversal is: after traversing the children of the current node, how do we return to the current node and continue? Both recursive and iterative methods use a stack to record the return path, enabling movement from lower to upper levels. The space complexity is $O(\log n)$ in the best case and $O(n)$ in the worst case (when the tree is linear).

The essence of Morris traversal is to avoid using a stack. Instead, it utilizes the idle `right` pointer of certain nodes to point back to an ancestor node, thereby completing the movement from lower to upper levels.

#### Morris Traversal Process

Assume we are at current node `cur`. Initially, we start at the root.

1.  If `cur` is null, stop. Otherwise, proceed with the following steps.
2.  If `cur` has no left subtree, move `cur` to the right (`cur = cur->right`).
3.  If `cur` has a left subtree, find the rightmost node in the left subtree, denoted `mostRight`.
    -   If `mostRight`'s `right` pointer points to null, make it point to `cur`, then move `cur` to the left (`cur = cur->left`).
    -   If `mostRight`'s `right` pointer points to `cur`, set it to `null`, then move `cur` to the right (`cur = cur->right`).

For example, start visiting `cur` from node 1.

![tree-basic-morris-1](images/tree-basic-morris-1.svg)

When `cur` first visits node 2, find the rightmost node 4 in the left subtree. Set 4's `right` pointer to `cur` (node 2).

![tree-basic-morris-2](images/tree-basic-morris-2.svg)

`cur` returns to the upper level through 4's `right` pointer. When visiting node 2 the second time, find the rightmost node 4. Set 4's `right` pointer to `null`, then continue visiting the right subtree. The subsequent process is omitted.

![tree-basic-morris-1](images/tree-basic-morris-1.svg)

The traversal order of the entire tree is `1242513637`. We can see that nodes with a left subtree are visited twice, while nodes without a left subtree are visited only once.

???+ note "Implementation"
    ```cpp
    void morris(TreeNode* root) {
      TreeNode* cur = root;
      while (cur) {
        if (!cur->left) {
          // if current node has no left child, output current node's value and go to right subtree
          std::cout << cur->val << " ";
          cur = cur->right;
          continue;
        }
        // find the rightmost node in current node's left subtree
        TreeNode* mostRight = cur->left;
        while (mostRight->right && mostRight->right != cur) {
          mostRight = mostRight->right;
        }
        if (!mostRight->right) {
          // if rightmost node's right pointer is null, point it to current node and go to left subtree
          mostRight->right = cur;
          cur = cur->left;
        } else {
          // if rightmost node's right pointer points to current node, left subtree is done, output current node's value and go to right subtree
          mostRight->right = nullptr;
          std::cout << cur->val << " ";
          cur = cur->right;
        }
      }
    }
    ```

### Unrooted Tree

#### Process

Tree traversal is generally depth-first. The most important thing to avoid is revisiting nodes.

Since a tree is an acyclic graph, we only need to record which node we came from to reach the current node. Then, we visit all adjacent nodes except that one, to avoid revisiting.

???+ note "Implementation"
    ```cpp
    void dfs(int u, int from) {
      // recursively visit all children except 'from'
      // for the starting node, 'from' is null, so all adjacent nodes are visited, as expected
      for (int v : adj[u])
        if (v != from) {
          dfs(v, u);
        }
    }
    
    // when starting traversal
    int EMPTY_NODE = -1;  // a non-existent label
    int root = 0;         // pick any node as the starting point
    dfs(root, EMPTY_NODE);
    ```

### Rooted Tree

For rooted trees, we need to distinguish the parent-child relationship.

Consider the traversal process above. If we start from the root, when we visit a node, the value of `from` is the label of its parent.

Using this method, we can find the parent and children list for all nodes from undirected input.

**Some content on this page is quoted from the article [Binary Tree: Preorder, Inorder, Postorder Traversal](https://blog.csdn.net/weixin_43357638/article/details/99730284), under CC 4.0 BY-SA license.**
