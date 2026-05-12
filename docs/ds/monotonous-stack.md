## Introduction

What is a monotonic stack? As the name suggests, a monotonic stack is a stack structure that satisfies monotonicity. Compared with a monotonic queue, it only performs insertion and deletion at one end.

For convenience, the following examples and pseudocode use an increasing monotonic stack of integers as the example.

## Process

### Insertion

When inserting an element into a monotonic stack, to maintain monotonicity, we need to pop the minimum number of elements while ensuring that the whole stack remains monotonic after inserting the element at the top.

For example, the elements in the stack from top to bottom are $\{0,11,45,81\}$.

![](images/monotonous-stack-before.svg)

When inserting the element $14$, to preserve monotonicity, elements $0,11$ need to be popped in sequence. After the operation, the stack becomes $\{14,45,81\}$.

![](images/monotonous-stack-after.svg)

The pseudocode is as follows:

???+ note "Implementation"
    ```text
    insert x
    while !sta.empty() && sta.top()<x
        sta.pop()
    sta.push(x)
    ```

### Usage

Naturally, we read an element from the top of the stack. This element satisfies one end of the monotonic property.

In the example above, the element taken is the minimum value in the stack.

## Applications

??? note "[POJ3250 Bad Hair Day](http://poj.org/problem?id=3250)"
    There are $N$ cows standing in a row from left to right, and each cow has a height $h_i$. Let the number of cows between the $i$-th cow from the left and the first cow to its right whose height is $≥h_i$ be $c_i$. Compute $\sum_{i=1}^{N} c_i$.

One basic application is this problem. It is a simple use of a monotonic stack: record the position where each cow is popped. If a cow is never popped, treat it as extending to the farthest end. With some simple processing, the required result can be computed.

In addition, monotonic stacks can also solve RMQ problems offline.

We can sort all queries by their right endpoint. Then scan the sequence from left to right up to the current query's right endpoint, inserting scanned elements into the monotonic stack. When answering a query, the values stored in the monotonic stack are decision points with positions $\le r$ that may become the answer, and these elements satisfy the monotonic property. At this point, the first element on the monotonic stack with position $\ge l$ is the answer for the current query, and this can be found with binary search. Solving RMQ with a monotonic stack has time complexity $O(q\log q + q\log n)$ and space complexity $O(n)$.

## Exercises

-   [Luogu P5788 Template: Monotonic Stack](https://www.luogu.com.cn/problem/P5788)
-   [Luogu P1901 Launching Station](https://www.luogu.com.cn/problem/P1901)
