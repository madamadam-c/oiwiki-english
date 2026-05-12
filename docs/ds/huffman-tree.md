author: Alex-McAvoy, lingkerio, LvCGame

## Weighted Path Length of a Tree

Suppose a binary tree has $n$ weighted leaf nodes. The sum, over all leaves, of the path length from the root to the leaf multiplied by that leaf's weight is called the **weighted path length of the tree (WPL)**.

Let $w_i$ be the weight of the $i$-th leaf node in the binary tree, and let $l_i$ be the path length from the root to the $i$-th leaf node. Then WPL is computed as follows:

$$
WPL=\sum_{i=1}^nw_il_i
$$

![](./images/huffman-tree-1.svg)

As shown above, its WPL is computed as follows:

$$
WPL=2*2+3*2+4*2+7*2=4+6+8+14=32
$$

## Structure

For a given set of leaf nodes with fixed weights, different binary trees can be constructed. Among them, the **binary tree with the minimum WPL** is called a **Huffman tree**.

In a Huffman tree, leaf nodes with smaller weights are farther from the root, and leaf nodes with larger weights are closer to the root. In addition, only leaf nodes have degree $0$; all other nodes have degree $2$.

## Huffman Algorithm

The Huffman algorithm constructs a Huffman tree. The steps are as follows:

1.  **Initialization**: Construct $n$ binary trees, each containing only one root node, from the given $n$ weights, forming a set of binary trees $F$.
2.  **Selection and merging**: From $F$, choose the two binary trees whose root weights are **minimum**, and use them as the left and right subtrees of a new binary tree. The root weight of this new binary tree is the sum of the root weights of its left and right subtrees.
3.  **Deletion and insertion**: Remove the two binary trees used as the left and right subtrees from $F$, and add the newly built binary tree to $F$.
4.  Repeat steps 2 and 3. When only one binary tree remains in the set, it is the Huffman tree.

![](./images/huffman-tree-2.svg)

### Proof of Correctness

???+ note "Lemma"
    The two leaf nodes with the smallest weights in an optimal prefix code tree (Huffman tree) are always among the deepest leaf nodes, and adjusting these two nodes to be siblings does not destroy the optimality of the code tree.

??? note "Proof"
    We prove this statement by contradiction. Suppose that in an optimal prefix code tree, there are two leaf nodes with the smallest weights that are not deepest leaves. Let these two nodes be $a$ and $b$, and suppose their depths are smaller than the depth of some deepest leaf node. For such a deepest leaf $c$, we can swap the positions of $a$ and $c$, or swap the positions of $b$ and $c$. Since the Huffman algorithm merges the smallest-weight leaves at each layer of the tree, after the swap the weighted path length (WPL) of the tree decreases. This contradiction shows that the assumption is false, so the two leaf nodes with the smallest weights must be deepest leaf nodes.
    
    Next, suppose these two minimum-weight leaves are $a$ and $b$, and they have the same depth. If they are not siblings in an optimal prefix code tree, suppose there are other nodes $c$ and $d$ that are siblings of $a$ and $b$ respectively (that is, $a$ and $c$ are siblings, and $b$ and $d$ are siblings). We can merge $a$ and $b$ into one subtree.
    
    -   If the sum of the weights of $a$ and $b$ after merging is less than the weight of $c$ or $d$, then we can merge the resulting subtree with the larger-weight node (such as $c$ or $d$) to form a new subtree, reducing the WPL.
    -   If the sum of the weights of $a$ and $b$ is not less than the weights of $c$ and $d$, we can directly adjust $a$ and $b$ to be siblings and let $c$ and $d$ be another pair of siblings; the WPL will not increase.
    
    Therefore, after such an adjustment, optimality is not destroyed. This proves the lemma.

???+ note "Theorem"
    The prefix code tree obtained by the Huffman algorithm is an optimal prefix code tree.

??? note "Proof"
    We prove the theorem by mathematical induction.
    
    -   **Base case**: When the number of letters is $n = 2$, directly merging the two letters into one tree is clearly optimal.
    -   **Induction hypothesis**: Suppose that when the number of letters is $n = k$ ($k \geq 2$), the Huffman algorithm can obtain an optimal prefix code tree.
    -   **Induction step**: For $n = k + 1$ letters, choose the two letters with the smallest weights from $k+1$ letters and merge them into one subtree, treating the subtree root as a virtual letter (virtual node). By the lemma, this operation does not destroy the optimality of the prefix code tree. Now this virtual letter together with the remaining $k$ letters gives $k + 1$ letters in total, and by the induction hypothesis, the Huffman algorithm can obtain an optimal prefix code tree for $k$ letters.
    
    Therefore, by mathematical induction, the Huffman algorithm can obtain an optimal prefix code tree for any number of letters $n$.

## Huffman Coding

In programming, each character is usually assigned a separate code to represent a set of characters; this is called **encoding**.

For binary encoding, if all codes have equal length, representing $n$ different characters requires $\left \lceil \log_2 n \right \rceil$ bits. This is called **fixed-length encoding**.

If every character has the **same frequency of use**, fixed-length encoding is undoubtedly the most space-efficient encoding method. If characters appear with different frequencies, then high-frequency characters can be assigned shorter codes and low-frequency characters longer codes, forming a **variable-length encoding** and achieving better space efficiency.

When designing variable-length encodings, the uniqueness of decoding must be considered. If no code in a set is the prefix of any other code, this set is called a **prefix code**, which guarantees unique decoding.

A Huffman tree can be used to construct the **shortest prefix code**, namely a **Huffman code**. The construction steps are as follows:

1.  Let the character set to be encoded be $d_1,d_2,\dots,d_n$, and let their frequencies in the string be $w_1,w_2,\dots,w_n$.
2.  Use $d_1,d_2,\dots,d_n$ as leaf nodes and $w_1,w_2,\dots,w_n$ as their weights to construct a Huffman tree.
3.  Let the left branch of the Huffman coding tree represent $0$ and the right branch represent $1$. Then the sequence of $0$s and $1$s along the path from the root to each leaf is the code for the character corresponding to that leaf.

![](./images/huffman-tree-3.svg)

## Sample Code

??? note "Building a Huffman Tree"
    ```cpp
    struct HNode {
      int weight;
      HNode *lchild, *rchild;
    };
    
    using Htree = HNode *;
    
    Htree createHuffmanTree(int arr[], int n) {
      Htree forest[N];
      Htree root = NULL;
      for (int i = 0; i < n; i++) {  // Put all nodes into the forest.
        Htree temp;
        temp = (Htree)malloc(sizeof(HNode));
        temp->weight = arr[i];
        temp->lchild = temp->rchild = NULL;
        forest[i] = temp;
      }
    
      for (int i = 1; i < n; i++) {  // Build the Huffman tree in n - 1 iterations.
        int minn = -1, minnSub;  // minn is the minimum root index; minnSub is the second minimum.
        for (int j = 0; j < n; j++) {
          if (forest[j] != NULL && minn == -1) {
            minn = j;
            continue;
          }
          if (forest[j] != NULL) {
            minnSub = j;
            break;
          }
        }
    
        for (int j = minnSub; j < n; j++) {  // Assign according to minn and minnSub.
          if (forest[j] != NULL) {
            if (forest[j]->weight < forest[minn]->weight) {
              minnSub = minn;
              minn = j;
            } else if (forest[j]->weight < forest[minnSub]->weight) {
              minnSub = j;
            }
          }
        }
    
        // Build a new tree.
        root = (Htree)malloc(sizeof(HNode));
        root->weight = forest[minn]->weight + forest[minnSub]->weight;
        root->lchild = forest[minn];
        root->rchild = forest[minnSub];
    
        forest[minn] = root;     // Store the pointer to the new tree at minn.
        forest[minnSub] = NULL;  // The minnSub position is emptied.
      }
      return root;
    }
    ```

??? note "Computing the WPL of a Built Huffman Tree"
    ```cpp
    struct HNode {
      int weight;
      HNode *lchild, *rchild;
    };
    
    using Htree = HNode *;
    
    int getWPL(Htree root, int len) {  // Recursive WPL for an already built Huffman tree.
      if (root == NULL)
        return 0;
      else {
        if (root->lchild == NULL && root->rchild == NULL)  // Leaf node.
          return root->weight * len;
        else {
          int left = getWPL(root->lchild, len + 1);
          int right = getWPL(root->rchild, len + 1);
          return left + right;
        }
      }
    }
    ```

??? note "Computing WPL Directly Without Building the Huffman Tree"
    ```cpp
    int getWPL(int arr[], int n) {  // Directly compute WPL without building the Huffman tree.
      priority_queue<int, vector<int>, greater<int>> huffman;  // Min-heap.
      for (int i = 0; i < n; i++) huffman.push(arr[i]);
    
      int res = 0;
      for (int i = 0; i < n - 1; i++) {
        int x = huffman.top();
        huffman.pop();
        int y = huffman.top();
        huffman.pop();
        int temp = x + y;
        res += temp;
        huffman.push(temp);
      }
      return res;
    }
    ```

??? note "Computing Huffman Codes for a Given Sequence"
    ```cpp
    struct HNode {
      int weight;
      HNode *lchild, *rchild;
    };
    
    using Htree = HNode *;
    
    void huffmanCoding(Htree root, int len, int arr[]) {  // Compute Huffman codes.
      if (root != NULL) {
        if (root->lchild == NULL && root->rchild == NULL) {
          printf("The code for the character at node %d is: ", root->weight);
          for (int i = 0; i < len; i++) printf("%d", arr[i]);
          printf("\n");
        } else {
          arr[len] = 0;
          huffmanCoding(root->lchild, len + 1, arr);
          arr[len] = 1;
          huffmanCoding(root->rchild, len + 1, arr);
        }
      }
    }
    ```
