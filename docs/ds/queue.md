This page introduces data structures related to queues and their applications.

![](./images/queue.svg)

## Introduction

A queue is a list with the property that "the element that enters the queue first must leave the queue first." Because of this property, a queue is also commonly called a first-in-first-out list, or FIFO list.

## Implementation

### Simulating a Queue with an Array

Usually, an array is used to simulate a queue, with two variables marking the front and rear of the queue.

```cpp
int q[SIZE], ql = 1, qr;
```

The code corresponding to queue operations is as follows:

-   Insert an element: `q[++qr] = x;`
-   Delete an element: `ql++;`
-   Access the front: `q[ql]`
-   Access the rear: `q[qr]`
-   Clear the queue: `ql = 1; qr = 0;`

??? example "[Luogu B3616 Template: Queue](https://www.luogu.com.cn/problem/B3616) Reference implementation using array simulation"
    ```cpp
    --8<-- "docs/ds/code/queue/queue_1.cpp"
    ```

### Simulating a Queue with Two Stacks

Another less common method is to use two [stacks](./stack.md) to simulate a queue.

This method uses two stacks $F$ and $S$ to simulate a queue. Here, $F$ is the stack for the rear of the queue, and $S$ represents the stack for the front of the queue. It supports push, which inserts at the rear, and pop, which removes from the front:

-   push: insert into stack $F$.
-   pop: if $S$ is nonempty, pop from $S$; otherwise, move the elements of $F$ into $S$ in reverse order (that is, pop and insert them one by one, so the front and rear are reversed afterward), then pop from $S$.

It is easy to prove that each element is inserted, transferred, and popped at most once, so the amortized complexity is $O(1)$.

??? example "[Luogu B3616 Template: Queue](https://www.luogu.com.cn/problem/B3616) Reference implementation using two stacks"
    ```cpp
    --8<-- "docs/ds/code/queue/queue_2.cpp"
    ```

## Queues in the C++ STL

C++ provides the container `std::queue` in the STL. Before using it, include the `<queue>` header.

???+ info "Definition of `queue` in the STL"
    ```cpp
    // clang-format off
    template<
        class T,
        class Container = std::deque<T>
    > class queue;
    ```
    
    `T` is the type of data to be stored in the queue.
    
    `Container` is the type of underlying container used to store elements. This container must provide the following functions with usual semantics:
    
    -   `back()`
    -   `front()`
    -   `push_back()`
    -   `pop_front()`
    
    The STL containers `std::deque` and `std::list` satisfy these requirements. If not specified, `std::deque` is used as the underlying container by default.

The STL `queue` container provides many member functions. Commonly used ones include:

-   Element access
    -   `q.front()` returns the front element
    -   `q.back()` returns the rear element
-   Modifiers
    -   `q.push()` inserts an element at the rear
    -   `q.pop()` pops the front element
-   Capacity
    -   `q.empty()` checks whether the queue is empty
    -   `q.size()` returns the number of elements in the queue

In addition, `queue` provides some operators. A commonly used one is the assignment operator `=` for assigning one `queue` to another. Example:

```cpp
std::queue<int> q1, q2;

// Insert 1 at the rear of q1.
q1.push(1);

// Assign q1 to q2.
q2 = q1;

// Output the front element of q2.
std::cout << q2.front() << std::endl;
// Output: 1
```

## Special Queues

### Deque

A deque is a queue that can insert or delete elements at either the front or the rear. It is equivalent to combining the functionality of a stack and a queue. Specifically, a deque supports four operations:

-   Insert an element at the front
-   Insert an element at the rear
-   Delete an element from the front
-   Delete an element from the rear

The method for simulating a deque with an array is the same as for an ordinary queue.

Similarly, the idea of simulating a queue with two stacks can also be used to maintain a deque. However, note that when one stack is empty, alternating queries to the front and rear will invalidate the amortized analysis. Consider moving only half of the elements from the nonempty stack into the empty stack while preserving the front-stack and rear-stack properties. With this handling, insertion and deletion can still be done in amortized constant time.

??? note "Brief Proof"
    Since insertion operations contribute only constant complexity, now consider pop operations. Suppose initially there are $m$ elements in the queue. We compute the time complexity of popping all elements, regardless of whether from the front or the rear. The first balancing costs $O(m)$. Then the two stacks each contain $\frac{m}{2}$ elements. At this point, it takes $O(\frac{m}{2})$ time to empty one of the stacks, which can trigger another balancing operation with cost $O(\frac{m}{2})$, and so on until all elements are popped. Therefore, the total complexity is
    
    $$
    T(m)=T\left(\frac{m}{2}\right)+O(m)
    $$
    
    By the master theorem, $T(m)=O(m)$. Thus, the total complexity of this maintenance method is still amortized constant time.

??? example "[Luogu B3656 Template: Deque 1](https://www.luogu.com.cn/problem/B3656) Reference Implementation"
    ```cpp
    --8<-- "docs/ds/code/queue/queue_3.cpp"
    ```

#### Deques in the C++ STL

C++ also provides the container `std::deque` in the STL. Before using it, include the `<deque>` header.

??? info "Definition of `deque` in the STL"
    ```cpp
    // clang-format off
    template<
        class T,
        class Allocator = std::allocator<T>
    > class deque;
    ```
    
    `T` is the type of data to be stored in the deque.
    
    `Allocator` is the allocator. It is not explained further here; generally, the default is sufficient.

The STL `deque` container provides many member functions. Commonly used ones include:

-   Element access
    -   `q.front()` returns the front element
    -   `q.back()` returns the rear element
-   Modifiers
    -   `q.push_back()` inserts an element at the rear
    -   `q.pop_back()` pops the rear element
    -   `q.push_front()` inserts an element at the front
    -   `q.pop_front()` pops the front element
    -   `q.insert()` inserts an element before a specified position (given an iterator and the element)
    -   `q.erase()` deletes the element at a specified position (given an iterator)
-   Capacity
    -   `q.empty()` checks whether the queue is empty
    -   `q.size()` returns the number of elements in the queue

In addition, `deque` provides some operators. Commonly used ones include:

-   Use the assignment operator `=` to assign one `deque` to another, similar to `queue`.
-   Use `[]` to access elements, similar to `vector`.

The `<queue>` header also provides the priority queue `std::priority_queue`. Since it is more similar to a [heap](./heap.md), it is not discussed further here.

#### Deques in Python

In Python, the deque container is provided by `collections.deque`.

An example is as follows:

???+ note "Implementation"
    ```python
    from collections import deque
    
    # Create a new deque and initialize it with [1, 2, 3].
    queue = deque([1, 2, 3])
    
    # Insert element 4 at the rear.
    queue.append(4)
    
    # Insert element 0 at the front.
    queue.appendleft(0)
    
    # Access the queue.
    # >>> queue
    # deque([0, 1, 2, 3, 4])
    ```

### Circular Queue

Using an array to simulate a queue causes a problem: as time passes, the entire queue moves toward the end of the array. Once it reaches the very end of the array, even if there is free space at the front of the array, another enqueue operation will cause overflow. This phenomenon, where the array actually has free space but an overflow occurs, is called false overflow.

The solution to false overflow is to organize the array that stores queue elements circularly, that is, treat the position with array index 0 as the successor of the last position. (For the element with array index `x`, its successor is `(x + 1) % SIZE`.) This forms a circular queue.

## References

1.  [std::queue - zh.cppreference.com](https://zh.cppreference.com/w/cpp/container/queue)
2.  [std::deque - zh.cppreference.com](https://zh.cppreference.com/w/cpp/container/deque)
