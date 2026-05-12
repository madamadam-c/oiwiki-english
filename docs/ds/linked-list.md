This page briefly introduces linked lists.

## Introduction

A linked list is a data structure for storing data. It connects elements with pointers like links in a chain. Its advantage is that insertion and deletion are very convenient, but searching and reading data are less efficient.

## Differences from Arrays

Both linked lists and arrays can store data. Unlike a linked list, an array stores all elements sequentially. Their different storage structures give them different advantages:

Because of its chain-like structure, a linked list can delete and insert data conveniently, with $O(1)$ operations. However, for the same reason, searching and reading are less efficient than in arrays; random access takes $O(n)$ operations.

An array can find and read data conveniently, with $O(1)$ random access. However, deletion and insertion take $O(n)$ operations.

## Building a Linked List

???+ tip "Tip"
    When building a linked list, the parts involving pointers are relatively abstract. Text descriptions and code alone may be hard to understand, so drawing diagrams is recommended.

### Singly Linked List

A singly linked list contains a data field and a pointer field. The data field stores data, and the pointer field connects the current node to the next node.

![](images/list.svg)

???+ note "Implementation"
    === "C++"
        ```cpp
        struct Node {
          int value;
          Node *next;
        };
        ```
    
    === "Python"
        ```python
        class Node:
            def __init__(self, value=None, next=None):
                self.value = value
                self.next = next
        ```

### Doubly Linked List

A doubly linked list also has data and pointer fields. The difference is that the pointer field is split into left/right (or previous/next) pointers, used to connect the previous node, current node, and next node.

![](images/double-list.svg)

???+ note "Implementation"
    === "C++"
        ```cpp
        struct Node {
          int value;
          Node *left;
          Node *right;
        };
        ```
    
    === "Python"
        ```python
        class Node:
            def __init__(self, value=None, left=None, right=None):
                self.value = value
                self.left = left
                self.right = right
        ```

## Inserting (Writing) Data into a Linked List

### Singly Linked List

The rough procedure is as follows:

1.  Initialize the data `node` to be inserted.
2.  Point `node`'s `next` pointer to the node after `p`.
3.  Point `p`'s `next` pointer to `node`.

See the figures below for the detailed process:

1.  ![](./images/list-insert-1.svg)
2.  ![](./images/list-insert-2.svg)
3.  ![](./images/list-insert-3.svg)

The code implementation is as follows:

???+ note "Implementation"
    === "C++"
        ```cpp
        void insertNode(int i, Node *p) {
          Node *node = new Node;
          node->value = i;
          node->next = p->next;
          p->next = node;
        }
        ```
    
    === "Python"
        ```python
        def insertNode(i, p):
            node = Node()
            node.value = i
            node.next = p.next
            p.next = node
        ```

### Singly Circular Linked List

Connecting the head and tail of a linked list turns it into a circular linked list. Since the list is circular, insertion must check whether the original list is empty: if it is empty, the new node loops to itself; otherwise, insert normally.

The rough procedure is as follows:

1.  Initialize the data `node` to be inserted.
2.  Check whether the given list `p` is empty.
3.  If it is empty, point both `node`'s `next` pointer and `p` to `node` itself.
4.  Otherwise, point `node`'s `next` pointer to the node after `p`.
5.  Point `p`'s `next` pointer to `node`.

See the figures below for the detailed process:

1.  ![](./images/list-insert-cyclic-1.svg)
2.  ![](./images/list-insert-cyclic-2.svg)
3.  ![](./images/list-insert-cyclic-3.svg)

The code implementation is as follows:

???+ note "Implementation"
    === "C++"
        ```cpp
        void insertNode(int i, Node *p) {
          Node *node = new Node;
          node->value = i;
          node->next = NULL;
          if (p == NULL) {
            p = node;
            node->next = node;
          } else {
            node->next = p->next;
            p->next = node;
          }
        }
        ```
    
    === "Python"
        ```python
        def insertNode(i, p):
            node = Node()
            node.value = i
            node.next = None
            if p == None:
                p = node
                node.next = node
            else:
                node.next = p.next
                p.next = node
        ```

### Doubly Circular Linked List

When inserting data into a doubly circular linked list, besides checking whether the given list is empty, both the left and right pointers must be modified.

The rough procedure is as follows:

1.  Initialize the data `node` to be inserted.
2.  Check whether the given list `p` is empty.
3.  If it is empty, point `node`'s `left` and `right` pointers, as well as `p`, to `node` itself.
4.  Otherwise, point `node`'s `left` pointer to `p`.
5.  Point `node`'s `right` pointer to `p`'s right node.
6.  Point the `left` pointer of `p`'s right node to `node`.
7.  Point `p`'s `right` pointer to `node`.

The code implementation is as follows:

???+ note "Implementation"
    === "C++"
        ```cpp
        void insertNode(int i, Node *p) {
          Node *node = new Node;
          node->value = i;
          if (p == NULL) {
            p = node;
            node->left = node;
            node->right = node;
          } else {
            node->left = p;
            node->right = p->right;
            p->right->left = node;
            p->right = node;
          }
        }
        ```
    
    === "Python"
        ```python
        def insertNode(i, p):
            node = Node()
            node.value = i
            if p == None:
                p = node
                node.left = node
                node.right = node
            else:
                node.left = p
                node.right = p.right
                p.right.left = node
                p.right = node
        ```

## Deleting Data from a Linked List

### Singly (Circular) Linked List

Suppose the node to delete is `p`. To delete it from the linked list, copy the value of `p`'s next node `p->next` into `p`, and update the link to the node after `p->next`.

The rough procedure is as follows:

1.  Assign the value of the node after `p` to `p`, overwriting `p->value`.
2.  Create a temporary node `t` to store the address of `p->next`.
3.  Point `p`'s `next` pointer to the node after `p->next`, removing `p->next` from the list.
4.  Delete `t`. At this point, although the original address of node `p` is still in use and the deleted address is the original `p->next`, `p`'s data has been overwritten by `p->next`, so the original `p` effectively no longer exists.

See the figures below for the detailed process:

1.  ![](./images/list-delete-1.svg)
2.  ![](./images/list-delete-2.svg)
3.  ![](./images/list-delete-3.svg)

The code implementation is as follows:

???+ note "Implementation"
    === "C++"
        ```cpp
        void deleteNode(Node *p) {
          p->value = p->next->value;
          Node *t = p->next;
          p->next = p->next->next;
          delete t;
        }
        ```
    
    === "Python"
        ```python
        def deleteNode(p):
            p.value = p.next.value
            p.next = p.next.next
        ```

### Doubly Circular Linked List

The rough procedure is as follows:

1.  Point the right pointer of `p`'s left node to `p`'s right node.
2.  Point the left pointer of `p`'s right node to `p`'s left node.
3.  Create a temporary node `t` to store the address of `p`.
4.  Assign the address of `p`'s right node to `p` to avoid making `p` a dangling pointer.
5.  Delete `t`.

The code implementation is as follows:

???+ note "Implementation"
    === "C++"
        ```cpp
        void deleteNode(Node *&p) {
          p->left->right = p->right;
          p->right->left = p->left;
          Node *t = p;
          p = p->right;
          delete t;
        }
        ```
    
    === "Python"
        ```python
        def deleteNode(p):
            p.left.right = p.right
            p.right.left = p.left
            p = p.right
        ```

## Tricks

### XOR Linked List

An XOR linked list is still essentially a **doubly linked list**, but it uses bitwise XOR values to implement the functionality of a doubly linked list using only the memory size of one pointer.

In the `Node` structure, define `lr = left ^ right`, the **bitwise XOR** of the addresses of the previous and next elements. During forward traversal, XOR the address of the previous element with the current node's `lr` to obtain the address of the next element. During backward traversal, XOR the address of the next element with the current node's `lr` to obtain the address of the previous element.
In this way, the same functionality as a doubly linked list can be implemented with half the memory.
