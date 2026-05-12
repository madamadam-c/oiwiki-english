Prerequisite: [Time Complexity](./complexity.md)

This page introduces the basics of amortized complexity.

## Introduction

Amortized Analysis is a technique for analyzing the performance of algorithms and dynamic data structures. It doesn't just focus on the cost of individual operations, but provides a more accurate assessment of overall performance by evaluating the average cost of a sequence of operations. Amortized analysis does not involve probability and can only ensure that the average time spent per operation in the worst-case performance is bounded, not the average performance of the system. In the worst case, amortized analysis spreads the overhead of high-cost operations across low-cost operations, ensuring the overall average cost remains within reasonable bounds.

Amortized analysis typically uses three main analysis methods: aggregate analysis, accounting method, and potential method. These methods have different focuses and are suitable for different scenarios, but their common goal is to balance operation costs and optimize the overall performance of data structures in the worst case.

## Content

Consider a resizable array, such as `vector` in C++, with an initial capacity of $m = 1$. Each time a new element is inserted, if the array is full, the array size needs to be doubled, then elements from the original array are copied to the new array, and finally the new element is inserted.

Next, using the insertion operation of a dynamic array as an example, we will analyze its amortized cost through three methods: aggregate analysis, accounting method, and potential method.

### Aggregate Analysis

Aggregate Analysis calculates the total cost of a sequence of operations and amortizes it to each operation, thereby obtaining the amortized time complexity of each operation.

Using the dynamic array as an example, first, the two key costs of the insertion operation can be obtained:

-   If the array is not full, the insertion operation costs $O(1)$.
-   If the array is full, the insertion operation needs to expand the capacity. After expansion, copying elements costs $O(m)$, where $m$ is the current array size.

Therefore, to calculate the total cost of $n$ insertion operations, it can be separated into two parts:

1.  **Cost of insertion operations**: The direct cost of inserting a new element each time is constant time $O(1)$. For $n$ operations, the total cost is $O(n)$.
2.  **Cost of array expansion**: Each expansion involves copying elements from the original array to the new array. These operations occur when the array size is $1, 2, 4, \ldots , 2^k$, where $2^k$ is the largest power less than or equal to $n$. The costs of expansion operations are $1, 2, 4, \ldots , 2^{k-1}$ respectively, with a total of $1 + 2 + 4 + \ldots  + 2^{k-1} = 2^k - 1$, which is the sum of a geometric series, with a result of $O(n)$.

Therefore, the total insertion cost of the array is $O(n)$, amortized to each operation is $O(1)$. Even in the worst case, the average cost per insertion operation is still constant time.

### Accounting Method

The Accounting Method pre-allocates a fixed amortized cost for each operation to ensure that the total cost of all operations does not exceed the sum of these pre-allocated costs. The accounting method is similar to a **fee prepayment** mechanism, where lower-cost operations store some of the fee to pay for future high-cost operations.

Using the dynamic array as an example, a fixed amortized cost can be allocated for each insertion operation to ensure that sufficient fees have been reserved when expansion is needed.

1.  **Fee allocation**:
    -   Assume the actual cost of each insertion operation is $1$, and the amortized cost is set to $3$.
    -   Among them, $1$ is used for the current insertion operation, and $2$ is used for future possible expansion operations.

2.  **Fee usage**:
    -   When the array is full, an expansion operation needs to be performed, with an actual cost of $O(m)$, where $m$ is the current array size.
    -   Assume the array has $n$ elements before expansion. Since the second half of the original array ($n/2$ elements) stored a total of $n$ units of amortized cost during insertion, this is exactly enough to pay for the expansion operation.

The following is a concrete example:

```text
Initial state:
arr    = [1, 2, 3, 4]  // initial array
amount = [2, 2, 2, 2]  // pre-stored fee for each element

// First round of expansion: array is full, needs expansion
arr    = [1, 2, 3, 4, null, null, null, null]  // array after expansion
amount = [2, 2, 0, 0, 0, 0, 0, 0]  // fees of 3, 4 used for expansion

// Continue inserting new elements until full again
arr    = [1, 2, 3, 4, 5, 6, 7, 8]  // continue filling the array
amount = [2, 2, 0, 0, 2, 2, 2, 2]  // newly inserted elements also pre-store fees

// Second round of expansion: array is full again, needs more space
arr    = [1, 2, 3, 4, 5, 6, 7, 8, null, null, null, null, null, null, null, null]  // array after expansion
amount = [2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]  // fees of 5, 6, 7, 8 used for expansion
```

The above process shows that the amortized cost stored for each insertion operation is sufficient to pay for future expansion operations, thus ensuring that the amortized cost of each operation remains $O(1)$.

### Potential Method

The Potential Method defines a potential function (usually denoted as $\Phi$) to measure the **potential energy** of a data structure, i.e., reserved resources in the system state that can be used to pay for future high-cost operations. Changes in potential are used to balance the total cost of operation sequences, thereby ensuring that the amortized cost of the entire algorithm remains within reasonable bounds.

#### Principle

First, define the **state** $S$ as the state of the data structure at a certain point in time, which may include information such as the number of elements, capacity, pointers, etc. The initial state is defined as $S_0$, which is the state before any operation is performed.

Second, define the potential function $\Phi(S)$ to measure the potential energy of the data structure in state $S$, which satisfies the following two properties:

1.  **Initial potential**: In the initial state $S_0$ of the data structure, the potential $\Phi(S_0) = 0$.
2.  **Non-negativity**: In any state $S$, the potential $\Phi(S) \geq 0$.

For each operation, the amortized cost $\hat{c}$ is defined as:

$$
\hat{c} = c + \Phi(S') - \Phi(S)
$$

Where $c$ is the actual cost of the operation, and $S$ and $S'$ represent the data structure state before and after the operation respectively. This formula shows that the amortized cost equals the actual cost plus the change in potential. If the operation increases potential (i.e., $\Phi(S') > \Phi(S)$), the amortized cost increases; if the operation consumes potential (i.e., $\Phi(S') < \Phi(S)$), the amortized cost decreases.

We can use the potential function to analyze the total cost of a sequence of operations. Let $S_1, S_2, \dots, S_m$ be the state sequence generated from the initial state $S_0$ after $m$ operations, and $c_i$ be the actual cost of the $i$-th operation. Then the amortized cost $p_i$ of the $i$-th operation is:

$$
p_i = c_i + \Phi(S_i) - \Phi(S_{i-1})
$$

Therefore, the total time spent on $m$ operations is:

$$
\sum_{i=1}^m c_i = \sum_{i=1}^m p_i + \Phi(S_0) - \Phi(S_m)
$$

Since $\Phi(S) \geq \Phi(S_0)$, the upper bound of total time spent is:

$$
\sum_{i=1}^m p_i \geq \sum_{i=1}^m c_i
$$

Therefore, if $p_i = O(T(n))$, then $O(T(n))$ is an upper bound for amortized complexity.

#### Example: Dynamic Array Expansion Analysis

Using the insertion operation of a dynamic array `vector` as an example, define the potential function $\Phi(h)$ as follows:

$$
\Phi(h) = 2n - m
$$

Where $n$ is the number of elements in the array, and $m$ is the current capacity of the array. This potential function reflects the amount of remaining available space in the array, i.e., the difference between current capacity and actual used space.

1.  **Insertion operation (no expansion needed)**:
    -   **Operation cost**: $O(1)$, because only one element needs to be inserted.
    -   **Potential change**: After insertion, the number of elements increases by $1$, and potential increases by $2$.
        -   $\Phi(h') - \Phi(h) = 2(n + 1) - m - (2n - m) = 2$
    -   **Amortized cost**: $1 + 2 = 3$

2.  **Insertion operation (triggers expansion)**:
    -   Assume current capacity $m = n$, inserting a new element triggers expansion, and the new capacity becomes $2n$.
    -   **Operation cost**: $O(n)$, because all elements need to be copied to the new array and the new element inserted.
    -   **Potential change**: After expansion, capacity increases and potential decreases, with a change of $2 - n$.
        -   $\Phi(h') - \Phi(h) = 2(n + 1) - 2n - (2n - n) = 2 - n$
    -   **Amortized cost**: $n + 1 + (2 - n) = 3$

From the above analysis, it can be seen that although the actual cost of expansion operations is high, due to the design of the potential function, the overall amortized cost remains at a constant level $O(1)$.

## Extended Example: Stack Operations

Stack operations are one of the classic application scenarios of amortized analysis. Assume stack `S` supports the following three operations:

| Operation | Description | Actual Cost $c_i$ |
| ---------------- | ---------- | ---------------------------- |
| `S.push(x)`      | Push element x onto stack   | $1$                          |
| `S.pop()`        | Pop top element     | $1$                          |
| `S.multi-pop(k)` | Pop k elements from top | $O(\min{\lvert S\rvert, k})$ |

We will analyze the amortized cost of these stack operations through three methods: aggregate analysis, accounting method, and potential method.

### Aggregate Analysis Method

Aggregate analysis calculates the total cost of all operations and amortizes it to each operation to obtain the amortized cost.

1.  For $n_{push}$ `push(x)` operations, each costs $O(1)$, so the total cost is $O(n_{push})$.
2.  For $n_{pop}$ `pop()` operations, each costs $O(1)$, so the total cost is $O(n_{pop})$.
3.  For $n_{multi-pop}$ `multi-pop(k)` operations, although the actual cost of each is $O(\min(\lvert S \rvert, k))$, the number of elements popped by these operations will not exceed the number of elements previously pushed by `push(x)`, so the total cost is still bounded by $n_{push}$.

Since the total number of operations $n = n_{push} + n_{pop} + n_{multi-pop} \leq 2 \times n_{push}$, the total cost is $O(n_{push}) = O(n)$, and the amortized cost per operation is $O(n)/n = O(1)$.

### Accounting Method

The accounting method pre-allocates a portion of the fee for each `push(x)` operation to pay for future possible `pop()` or `multi-pop(k)` operations.

1.  **`S.push(x)`**: Assume the amortized cost of each `push(x)` operation is $2$, where $1$ unit is used for the current operation, and $1$ unit is stored as fee to pay for future `pop()` or `multi-pop(k)` operations.
2.  **`S.pop()`**: The actual cost is $1$, but since the previous `push(x)` operation has pre-stored $1$ unit of fee for it, the amortized cost is $0$.
3.  **`S.multi-pop(k)`**: The actual cost of each popped element is $1$, which can be paid by the fee pre-stored by the `push(x)` operation for that element, so the amortized cost is $0$.

From the above analysis, the fee pre-stored by push operations is sufficient to pay for future pop operations of that element, so the amortized cost per operation is $O(1)$.

### Potential Method

The potential method defines a potential function to measure the state of the stack and uses changes in potential to balance operation costs.

1.  **Potential function**: Let $\Phi(h)$ be the number of elements in the stack, i.e., $\Phi(h) = \lvert S \rvert$. Each element contributes $1$ unit of potential.
2.  **`S.push(x)`**: Each `push(x)` operation increases the number of elements in the stack by $1$, so potential increases by $1$, therefore the amortized cost is $1 + 1 = 2$.
3.  **`S.pop()`**: Each `pop()` operation decreases the number of elements in the stack by $1$, so potential decreases by $1$, therefore the amortized cost is $1 - 1 = 0$.
4.  **`S.multi-pop(k)`**: The `multi-pop(k)` operation pops $k$ elements, so potential decreases by $k$, therefore the amortized cost is $k - k = 0$.

Through the above potential function design, the amortized cost of `push(x)` operations is $2$, while the amortized cost of `pop()` and `multi-pop(k)` operations is $0$. Therefore, the amortized cost of all stack operations is $O(1)$.

## References

-   [Amortized Analysis - Wikipedia](https://en.wikipedia.org/wiki/Amortized_analysis)
-   [Cornell CS 3110 - Lecture 20: Amortized Analysis](https://www.cs.cornell.edu/courses/cs3110/2011sp/Lectures/lec20-amortized/amortized.htm)