author: fudonglai, AngelKitty, labuladong

This page introduces the differences between recursion and divide-and-conquer algorithms, as well as their combined application.

## Recursion

### Definition

Recursion, in mathematics and computer science, refers to a method of defining a function in terms of itself, and in computer science, it additionally refers to a method of solving a problem by repeatedly decomposing it into subproblems of the same type.

### Introduction

> To understand recursion, you must first understand what recursion is.

The basic idea of recursion is that a certain function calls itself directly or indirectly, so that the solution to the original problem is transformed into many subproblems with the same properties but smaller scale. When solving, you only need to focus on how to divide the original problem into eligible subproblems, without paying too much attention to how these subproblems are actually solved.

Here are some examples to help understand recursion:

1.  [What is recursion?](./divide-and-conquer.md)
2.  How do you sort a bunch of numbers? Answer: split in half, sort the left half first, then the right half, finally merge. As for how to sort the left and right sides, please read this sentence again.
3.  How old are you this year? Answer: last year's age plus one. I was born in 1999.
4.  ![An example to understand recursion](images/divide-and-conquer-1.png)

Recursion is very common in mathematics. For example, the formal set-theoretic definition of natural numbers is: 1 is a natural number, and every natural number has a successor, which is also a natural number.

The two most important characteristics of recursive code: a termination condition and self-calls. Self-calls solve subproblems, while the termination condition defines the answer to the simplest subproblem.

```cpp
int func(input value) {
  if (termination condition) return smallest subproblem solution;
  return func(reduced scale);
}
```

### Why Write Recursion

1.  Clear structure and strong readability. For example, implementing [merge sort](./merge-sort.md) with different methods:

    === "C++"
        ```cpp
        // Non-recursive merge sort algorithm
        template <typename T>
        void merge_sort(vector<T> a) {
          int n = a.size();
          for (int seg = 1; seg < n; seg = seg + seg)
            for (int start = 0; start < n - seg; start += seg + seg)
              merge(a, start, start + seg - 1, std::min(start + seg + seg - 1, n - 1));
        }
        
        // Recursive merge sort algorithm
        template <typename T>
        void merge_sort(vector<T> a, int front, int end) {
          if (front >= end) return;
          int mid = front + (end - front) / 2;
          merge_sort(a, front, mid);
          merge_sort(a, mid + 1, end);
          merge(a, front, mid, end);
        }
        ```

    === "Python"
        ```python
        # Non-recursive merge sort algorithm
        def merge_sort(a):
            n = len(a)
            seg, start = 1, 0
            while seg < n:
                while start < n - seg:
                    merge(a, start, start + seg - 1, min(start + seg + seg - 1, n - 1))
                    start = start + seg + seg
                seg = seg + seg
        
        
        # Recursive merge sort algorithm
        def merge_sort(a, front, end):
            if front >= end:
                return
            mid = front + (end - front) / 2
            merge_sort(a, front, mid)
            merge_sort(a, mid + 1, end)
            merge(a, front, mid, end)
        ```

    Obviously, the recursive version is easier to understand than the non-recursive version. The recursive version's approach is straightforward: sort the left half, sort the right half, finally merge the two halves. The non-recursive version looks confusing, full of various boundary calculation details that are hard to understand, prone to bugs, and difficult to debug.

2.  Practice analyzing problem structure. When you find that a problem can be decomposed into smaller problems of the same structure, writing recursion many times will help you keen to notice this characteristic, thus solving problems efficiently.

### Disadvantages of Recursion

In program execution, recursion is implemented using a stack. Every time a function call is entered, the stack grows by one frame, and every time a function returns, the stack shrinks by one frame. The stack is not infinite. When the recursion depth is too large, it causes **stack overflow**.

Obviously, sometimes recursive processing is efficient, such as merge sort; **sometimes it is inefficient**, such as counting the hairs on Sun Wukong (Monkey King), because the stack consumes extra space, while simple iteration does not consume space. For example, given the head of a linked list, calculate its length:

```cpp
// Typical iterative traversal framework
int size(Node *head) {
  int size = 0;
  for (Node *p = head; p != nullptr; p = p->next) size++;
  return size;
}

// I insist on writing recursion, recursion is the best
int size_recursion(Node *head) {
  if (head == nullptr) return 0;
  return size_recursion(head->next) + 1;
}
```

![](https://quick-bench.com/q/rZ7jWPmSdltparOO5ndLgmS9BVc)](images/divide-and-conquer-2.png)

### Optimizing Recursion

Main page: [Search Optimization](../search/opt.md) and [Memoization](../dp/memo.md)

A basic recursive implementation may have too many recursive calls and easily times out. In this case, recursion needs to be optimized.[^ref1]

## Divide and Conquer

### Definition

Divide and Conquer, literally meaning "divide and rule," means decomposing a complex problem into two or more subproblems of the same or similar type, until the subproblems can be easily solved directly. The solution to the original problem is the merge of the subproblem solutions.

### Process

The core idea of divide-and-conquer algorithms is "divide and conquer."

The general process can be divided into three steps: decompose -> solve -> merge.

1.  Decompose the original problem into subproblems with the same structure.
2.  Continue decomposing until reaching a boundary that is easy to solve, then solve recursively.
3.  Merge the subproblem solutions into the original problem's solution.

Problems suitable for divide and conquer generally have the following characteristics:

-   The problem's scale reduces to a certain degree, making it easy to solve.
-   The problem can be decomposed into several smaller subproblems of the same type, i.e., the problem has an optimal substructure property. The solutions to the subproblems decomposed from this problem can be merged into the solution of this problem.
-   The subproblems decomposed from this problem are independent of each other, i.e., the subproblems do not contain common subproblems.

???+ warning "Note"
    If the subproblems are not independent, divide and conquer will repeatedly solve common subproblems, doing a lot of unnecessary work. Although divide and conquer can still be used in this case, [dynamic programming](../dp/basic.md) is generally better.

Take merge sort as an example. Suppose the function implementing merge sort is named `merge_sort`. Clarify the function's responsibility: **sort an array passed to it**. This problem can obviously be decomposed. Sorting an array equals sorting the left and right halves separately, then merging them into one array.

```cpp
void merge_sort(an array) {
  if (can be easily processed) return;
  merge_sort(left half of array);
  merge_sort(right half of array);
  merge(left half of array, right half of array);
}
```

Pass it half an array, and after processing, that half will be sorted. Notice that `merge_sort` is extremely similar to the post-order traversal template of a binary tree. Because the divide-and-conquer algorithm pattern is **decompose -> solve (reach bottom) -> merge (backtrack)**: first decompose left and right, then solve and merge. Backtracking is popping from the stack, equivalent to post-order traversal.

The implementation of the `merge` function is the same as merging two sorted linked lists.

## Key Points

### Key Points for Writing Recursion

**Understand what a function does and trust that it can complete this task. Never try to dive into the function and explore more details.** Otherwise, you will fall into endless details. How many stack frames can a human brain handle?

Take traversing a binary tree as an example.

```cpp
void traverse(TreeNode* root) {
  if (root == nullptr) return;
  traverse(root->left);
  traverse(root->right);
}
```

A few lines of code are enough to traverse any binary tree. For the recursive function `traverse(root)`, just trust that given a root node `root`, it can traverse the tree. So you only need to pass this node's left and right children to the function.

The same extends to traversing an N-ary tree. The writing is exactly the same as for a binary tree. However, for an N-ary tree, there is obviously no in-order traversal.

```cpp
void traverse(TreeNode* root) {
  if (root == nullptr) return;
  for (auto child : root->children) traverse(child);
}
```

## Differences

### Differences Between Recursion and Enumeration

The difference between recursion and enumeration is: enumeration divides the problem horizontally, then solves the subproblems in order; recursion divides the problem level by level, which is vertical decomposition.

### Differences Between Recursion and Divide and Conquer

Recursion is a programming technique, a way of thinking about solving problems; divide and conquer is an algorithmic idea largely based on recursion, solving more specific problems.

## Example Problem Explained

???+ note "[437. Path Sum III](https://leetcode-cn.com/problems/path-sum-iii/)"
    Given a binary tree where each node holds an integer value.
    
    Find the number of paths that sum to a given value.
    
    The path does not need to start from the root node or end at a leaf node, but the direction of the path must be downward (from a parent node to a child node only).
    
    The binary tree has at most 1000 nodes, and node values are integers in the range \[-1000000, 1000000].
    
    Example:
    
    ```text
    root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8
    
          10
         /  \
        5   -3
       / \    \
      3   2   11
     / \   \
    3  -2   1
    
    Return 3. Paths summing to 8:
    
    1.  5 -> 3
    2.  5 -> 2 -> 1
    3. -3 -> 11
    ```
    
    ```cpp
    --8<-- "docs/basic/code/divide-and-conquer/divide-and-conquer_1.h"
    ```

??? note "Reference Code"
    ```cpp
    --8<-- "docs/basic/code/divide-and-conquer/divide-and-conquer_1.cpp"
    ```

??? note "Problem Analysis"
    The problem looks complex, but the code is extremely simple.
    
    First, clarify that recursively solving tree problems must traverse the entire tree, so the binary tree traversal framework (recursively calling the function itself on the left and right subtrees) must appear in the main function pathSum. Then for each node, what should they do? They should see how many valid paths are contained in themselves and their subtrees. That's it. Problem solved.
    
    Following the technique mentioned earlier, based on the previous analysis, clearly define what each recursive function should do:
    
    `PathSum` function: Given a node and a target value, return the total number of paths summing to the target value in the tree rooted at this node.
    
    `count` function: Given a node and a target value, return how many paths starting from this node can be formed that sum to the target value in the tree rooted at this node.
    
    ??? note "Reference Code (with comments)"
        ```cpp
        int pathSum(TreeNode *root, int sum) {
          if (root == nullptr) return 0;
          int pathImLeading = count(root, sum);  // paths starting with myself
          int leftPathSum = pathSum(root->left, sum);  // total left paths (trust it can compute)
          int rightPathSum =
              pathSum(root->right, sum);  // total right paths (trust it can compute)
          return leftPathSum + rightPathSum + pathImLeading;
        }
        
        int count(TreeNode *node, int sum) {
          if (node == nullptr) return 0;
          // Can I be a standalone path?
          int isMe = (node->val == sum) ? 1 : 0;
          // Left side, how many sum - node.val can you make?
          int leftNode = count(node->left, sum - node->val);
          // Right side, how many sum - node.val can you make?
          int rightNode = count(node->right, sum - node->val);
          return isMe + leftNode + rightNode;  // I can make this many
        }
        ```
    
    As said before, **understand what each function can do, and trust that they can complete it.**
    
    To summarize, the `PathSum` function provides the binary tree traversal framework, calling the `count` function on each node during traversal (here pre-order traversal is used, but in-order and post-order also work). The `count` function is also a binary tree traversal, used to find paths starting from that node that sum to the target value.

## Exercises

-   [Recursion I Practice on LeetCode](https://leetcode.com/explore/learn/card/recursion-i/)
-   [Divide and Conquer Practice on LeetCode](https://leetcode.com/tag/divide-and-conquer/)

## References and Notes

[^ref1]: [labuladong's Algorithm Cheatsheet - Recursion Explained](https://labuladong.gitbook.io/algo/suan-fa-si-wei-xi-lie/di-gui-xiang-jie)
