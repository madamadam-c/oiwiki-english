author: Xeonacid, ksyx, Early0v0

## Stack

The STL [stack](../../ds/stack.md) (`std::stack`) is a last-in-first-out container adapter. It only supports querying or deleting the most recently added element, the top element, does not support random access, and does not support iterators in order to preserve strict ordering.

### Header

```cpp
#include <stack>
```

### Definition

```cpp
std::stack<TypeName> s;  // Uses the default underlying container deque, with data type TypeName
std::stack<TypeName, Container> s;  // Uses Container as the underlying container
std::stack<TypeName> s2(s1);        // Constructs s2 from a copy of s1
```

### Member Functions

**All of the following functions have constant complexity**

-   `top()` accesses the top element. This is an error if the stack is empty.
-   `push(x)` inserts element `x` into the stack.
-   `pop()` removes the top element.
-   `size()` queries the number of elements in the container.
-   `empty()` queries whether the container is empty.

### Simple Example

```cpp
std::stack<int> s1;
s1.push(2);
s1.push(1);
std::stack<int> s2(s1);
s1.pop();
std::cout << s1.size() << " " << s2.size() << std::endl;  // 1 2
std::cout << s1.top() << " " << s2.top() << std::endl;    // 2 1
s1.pop();
std::cout << s1.empty() << " " << s2.empty() << std::endl;  // 1 0
```

## Queue

The STL [queue](../../ds/queue.md) (`std::queue`) is a first-in-first-out container adapter. It only supports querying or deleting the first added element, the front element, does not support random access, and does not support iterators in order to preserve strict ordering.

### Header

```cpp
#include <queue>
```

### Definition

```cpp
std::queue<TypeName> q;  // Uses the default underlying container deque, with data type TypeName
std::queue<TypeName, Container> q;  // Uses Container as the underlying container

std::queue<TypeName> q2(q1);  // Constructs q2 from a copy of q1
```

### Member Functions

**All of the following functions have constant complexity**

-   `front()` accesses the front element. This is an error if the queue is empty.
-   `push(x)` inserts element `x` into the queue.
-   `pop()` removes the front element.
-   `size()` queries the number of elements in the container.
-   `empty()` queries whether the container is empty.

### Simple Example

```cpp
std::queue<int> q1;
q1.push(2);
q1.push(1);
std::queue<int> q2(q1);
q1.pop();
std::cout << q1.size() << " " << q2.size() << std::endl;    // 1 2
std::cout << q1.front() << " " << q2.front() << std::endl;  // 1 2
q1.pop();
std::cout << q1.empty() << " " << q2.empty() << std::endl;  // 1 0
```

## Priority Queue

The priority queue `std::priority_queue` is a kind of [heap](../../ds/heap.md), usually a [binary heap](../../ds/binary-heap.md).

### Header

```cpp
#include <queue>
```

### Definition

```cpp
std::priority_queue<TypeName> q;             // Data type is TypeName
std::priority_queue<TypeName, Container> q;  // Uses Container as the underlying container
std::priority_queue<TypeName, Container, Compare> q;
// Uses Container as the underlying container and Compare as the comparison type

// The default underlying container is vector
// The comparison type is less<TypeName>, so top() returns the maximum value
// To make top() return the minimum value, use greater<TypeName> as the comparison type
// Note: you cannot skip Container and pass Compare directly

// Since C++11, if you use a lambda function to customize Compare,
// pass it as a constructor argument, for example:
auto cmp = [](const std::pair<int, int> &l, const std::pair<int, int> &r) {
  return l.second < r.second;
};
std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                    decltype(cmp)>
    pq(cmp);
```

### Member Functions

**All of the following functions have constant complexity**

-   `top()` accesses the heap top. The priority queue must not be empty.
-   `empty()` queries whether the container is empty.
-   `size()` queries the number of elements in the container.

**All of the following functions have logarithmic complexity**

-   `push(x)` inserts an element and orders the underlying container.
-   `pop()` removes the heap top. The priority queue must not be empty.

### Simple Example

```cpp
std::priority_queue<int> q1;
std::priority_queue<int, std::vector<int>> q2;
// Since C++11, the space may be omitted
std::priority_queue<int, std::deque<int>, std::greater<int>> q3;
// q3 is a min-heap
for (int i = 1; i <= 5; i++) q1.push(i);
// Elements in q1: [1, 2, 3, 4, 5]
std::cout << q1.top() << std::endl;
// Output: 5
q1.pop();
// Elements in the heap: [1, 2, 3, 4]
std::cout << q1.size() << std::endl;
// Output: 4
for (int i = 1; i <= 5; i++) q3.push(i);
// Elements in q3: [1, 2, 3, 4, 5]
std::cout << q3.top() << std::endl;
// Output: 1
```
