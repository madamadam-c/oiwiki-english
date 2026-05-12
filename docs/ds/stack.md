## Introduction

![](./images/stack.svg)

A stack is a commonly used linear data structure in OI. Note that this article focuses on the stack data structure itself, not the system stack/stack memory used during program execution.

Stacks are modified and accessed following the last-in‑first-out principle, thus a stack is often called a last‑in‑first‑out (LIFO) table.

??? warning "Warning"
    LIFO refers to the **current container** where the most recently added element is the first to leave.
    
    Consider this stack:
    
    ```text
    push(1)
    pop(1)
    push(2)
    pop(2)
    ```
    
    If we view the whole process, 1 was pushed first and popped first, 2 was pushed last and popped last, which would be a first‑in‑first‑out table—clearly incorrect.
    
    Therefore, when assessing whether a data structure is LIFO or FIFO, consider only the current container contents.

## Simulating a Stack with an Array

We can conveniently simulate a stack using an array, as follows:

???+ note "Implementation"
    === "C++"
        ```cpp
        int st[N];
        // Here, st[0] (i.e., *st) represents the number of elements in the stack and also the index of the top.
        
        // Push:
        st[++*st] = var1;
        // Access top:
        int u = st[*st];
        // Pop (be careful of underflow; when *st == 0 you cannot pop):
        if (*st) --*st;
        // Clear stack:
        *st = 0;
        ```
    === "Python"
        ```python
        st = [0] * N
        # Here, st[0] represents the number of elements in the stack and also the index of the top.
        
        # Push:
        st[st[0] + 1] = var1
        st[0] = st[0] + 1
        # Access top:
        u = st[st[0]]
        # Pop (be careful of underflow; when st[0] == 0 you cannot pop):
        if st[0]:
            st[0] = st[0] - 1
        # Clear stack:
        st[0] = 0
        ```

## Stack in the C++ STL

The C++ STL also provides a container `std::stack`; you need to include the `<stack>` header before using it.

???+ info "Definition of `stack` in the STL"
    ```cpp
    // clang-format off
    template<
        class T,
        class Container = std::deque<T>
    > class stack;
    ```
    
    `T` is the type of elements stored in the stack.
    
    `Container` is the underlying container type used to store elements. This container must provide the following operations with typical semantics:
    
    -   `back()`
    -   `push_back()`
    -   `pop_back()`
    
    STL containers `std::vector`, `std::deque`, and `std::list` satisfy these requirements. If not specified, `std::deque` is used as the default underlying container.

The `std::stack` container offers several member functions, the most common being:

-   Element access
    -   `st.top()` returns the element at the top of the stack
-   Modification
    -   `st.push()` inserts the given argument at the top of the stack
    -   `st.pop()` removes the top element
-   Capacity
    -   `st.empty()` returns whether the stack is empty
    -   `st.size()` returns the number of elements

Additionally, `std::stack` provides some operators. A common use is the assignment operator `=` to copy one stack to another, as shown:

```cpp
// Create two stacks st1 and st2
std::stack<int> st1, st2;

// Push 1 onto st1
st1.push(1);

// Assign st1 to st2
st2 = st1;

// Output the top element of st2
cout << st2.top() << endl; // prints: 1
```

## Simulating a Stack with Python's `list`

In Python, you can use a list to simulate a stack:

???+ note "Implementation"
    ```python
    st = [5, 1, 4]
    
    # Append to push onto the stack
    st.append(2)
    st.append(3)
    # >>> st
    # [5, 1, 4, 2, 3]
    
    # Pop to remove the top element
    st.pop()
    # >>> st
    # [5, 1, 4, 2]
    
    # Clear the stack
    st.clear()
    ```

## References

1.  [std::stack – cppreference.com (English)](https://en.cppreference.com/w/cpp/container/stack)