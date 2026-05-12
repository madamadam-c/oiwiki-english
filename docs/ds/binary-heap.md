author: HeRaNO, Xeonacid, AzurIce

## Structure

Starting from the structure of a binary heap, it is a binary tree and a complete binary tree, with each node storing an element (or rather, a weight).

Heap property: the parent's weight is not less than the child's weight (max-heap). Similarly, we can define a min-heap. This article takes the max-heap as an example.

By the heap property, the tree root stores the maximum value (getmax operation solves this).

## Process

### Insertion Operation

Insertion operation refers to inserting an element into the binary heap, ensuring that after insertion it remains a complete binary tree.

The simplest method is to insert after the rightmost leaf on the bottom level.

If the bottom level is full, we add a new level.

After insertion, the heap property might be violated?

**Shift-up**: if this node's weight is greater than its parent's weight, swap them, repeating this process until the condition is no longer met or we reach the root.

It can be proven that after insertion and shift-up, no other node will violate the heap property.

The time complexity of shift-up is $O(\log n)$.

![Insertion operation of binary heap](./images/binary_heap_insert.svg)

### Deletion Operation

Deletion operation refers to deleting the maximum element in the heap, i.e., deleting the root node.

However, if we delete it directly, it becomes two heaps, which is difficult to handle.

Therefore, we can consider the reverse of the insertion operation: try to move the root node to the last node, then delete it directly.

In practice, it's not easy to do this, so we usually adopt the method of directly swapping the root node with the last node.

Then we directly delete (at the last node's position) the root node, but the new root node may not satisfy the heap property……

**Shift-down**: among this node's children, find the maximum, swap with it, and repeat this process until we reach the bottom level.

It can be proven that after deletion and shift-down, no other node will violate the heap property.

Time complexity: $O(\log n)$.

### Increasing the Weight of a Certain Point

Obviously, after direct modification, a single shift-up suffices, with time complexity $O(\log n)$.

## Implementation

We find that the several operations introduced above mainly depend on two cores: shift-up and shift-down.

Consider using a sequence $h$ to represent the heap. The two children of $h_i$ are $h_{2i}$ and $h_{2i+1}$, and $1$ is the root node:

![Heap structure of h](./images/binary-heap-array.svg)

Reference code:

```cpp
void up(int x) {
  while (x > 1 && h[x] > h[x / 2]) {
    std::swap(h[x], h[x / 2]);
    x /= 2;
  }
}

void down(int x) {
  while (x * 2 <= n) {
    t = x * 2;
    if (t + 1 <= n && h[t + 1] > h[t]) t++;
    if (h[t] <= h[x]) break;
    std::swap(h[x], h[t]);
    x = t;
  }
}
```

### Building a Heap

Consider this problem: starting from an empty heap, insert $n$ elements, not caring about order.

Directly inserting one by one takes $O(n \log n)$ time. Is there a better method?

#### Method 1: Using decreasekey (i.e., shift-up)

Start from the root, proceed in BFS order.

```cpp
void build_heap_1() {
  for (i = 1; i <= n; i++) up(i);
}
```

Why do this: for a node at level $k$, the complexity of shift-up is $O(k)$ instead of $O(\log n)$.

Total complexity: $\log 1 + \log 2 + \cdots + \log n = \Theta(n \log n)$.

(This has been proven in "comparison-based sorting".)

#### Method 2: Using shift-down

At this point, we change our approach: start from the leaves and perform shift-down one by one.

```cpp
void build_heap_2() {
  for (i = n; i >= 1; i--) down(i);
}
```

Another way to understand this: each time we "merge" two already adjusted heaps, which explains correctness.

Noting that the complexity of shift-down is $O(\log n - k)$, and also noting that leaf nodes need no adjustment, we can start adjusting from approximately position $n/2$ in the sequence, which can reduce some constants but does not affect the complexity.

???+ note "Proof"
    $$
    \begin{aligned}
    \text{总复杂度} & = n \log n - \log 1 - \log 2 - \cdots - \log n \\
    & \leq n \log n - 0 \times 2^0 - 1 \times 2^1 -\cdots - (\log n - 1) \times \frac{n}{2} \\\
    & = n \log n - (n-1) - (n-2) - (n-4) - \cdots - (n-\frac{n}{2}) \\
    & = n \log n - n \log n + 1 + 2 + 4 + \cdots + \frac{n}{2} \\
    & = n - 1 \\ &  = O(n)
    \end{aligned}
    $$

The reason we can build a heap in $O(n)$ time is because the heap property is weak, and binary heaps are not unique.

If it were as strict a condition as sorting, it would be hard to say.

## Applications

### Double-Ended Heap

??? note "[SPOJ RMID2 - Running Median Again](https://www.spoj.com/problems/RMID2/)"
    Maintain a sequence supporting two operations:

    1.  Insert an element into the sequence
    2.  Output and delete the current sequence's median (if the sequence length is even, output the smaller median)

    This problem can be further abstracted as: dynamically maintain the $k$-th largest number in a sequence, where the $k$ value may change.

    For such problems, we can use the **double-ended heap** technique to solve them (avoiding the hassle of writing a value segment tree or BST).

    A double-ended heap consists of a max-heap and a min-heap, where the min-heap maintains large values, i.e., the top $k$ values (including the k-th), and the max-heap maintains small values, i.e., other numbers smaller than the $k$-th largest.

    These two heaps forming a data structure support the following operations:

    -   Maintenance: when the size of the min-heap is less than $k$, continuously extract and insert the top element of the max-heap into the min-heap until the min-heap's size equals $k$; when the size of the min-heap is greater than $k$, continuously extract and insert the top element of the min-heap into the max-heap until the min-heap's size equals $k$;
    -   Insert element: if the inserted element is greater than or equal to the top element of the min-heap, insert it into the min-heap; otherwise, insert it into the max-heap, then maintain the double-ended heap;
    -   Query the $k$-th largest element: the top element of the min-heap is exactly what we seek;
    -   Delete the $k$-th largest element: delete the top element of the min-heap, then maintain the double-ended heap;
    -   $k$ value $+1/-1$: directly maintain the double-ended heap according to the new $k$ value.

    Obviously, the time complexity of querying the $k$-th largest element is $O(1)$. Due to insertion, deletion, or adjustment of the $k$ value causing the min-heap's size to differ from the expected $k$ value by at most $1$, each maintenance requires at most one adjustment of elements in the max-heap and min-heap, so the time complexity of these operations is $O(\log n)$.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/ds/code/binary-heap/binary-heap_1.cpp"
    ```

### Exercises

-   [SPOJ RMID - Running Median](https://www.spoj.com/problems/RMID)
-   [Luogu P1801 Black Box](https://www.luogu.com.cn/problem/P1801)
