author: MingqiHuang, Xeonacid, greyqz, i-Yirannn, ChenZ01

## `vector`

`std::vector` is a **contiguous-memory**, **variable-length** array, also called a list, data structure provided by STL. It provides linear-complexity insertion and deletion, and constant-complexity random access.

### Why Use `vector`?

As OI contestants, we care much more about program efficiency than engineering-level stability. Because `vector` handles memory dynamically, it can be slower than static arrays in some cases, and this can be worse on OJ servers that may not enable full optimization. Therefore, `vector` is usually not chosen for ordinary data storage. The following are several excellent features of `vector`; when these features are needed, `vector` can be very helpful.

#### `vector` Can Dynamically Allocate Memory

Often we cannot allocate such a large amount of space in advance, for example when preprocessing all divisors of every number from 1 to $n$. Although we may know that the total data volume is within memory limits, a single piece of data may still be very large. In this case, we need `vector` to keep memory usage within an appropriate range. `vector` also supports dynamic expansion, which is useful when memory is very tight.

#### `vector` Overloads Comparison and Assignment Operators

`vector` overloads the six comparison operators, implemented in lexicographical order. This makes it convenient to determine whether two containers are equal, with complexity linear in the container size. For example, `vector<char>` can be used to implement string comparison, though `std::string` is faster and more convenient. `vector` also overloads the assignment operator, making array copying more convenient.

#### Convenient Initialization of `vector`

Because `vector` overloads the `=` operator, we can conveniently assign a whole `vector`. Since C++11, `vector` also supports [list initialization](https://en.cppreference.com/w/cpp/language/list_initialization), for example `vector<int> data {1, 2, 3};`.

### Usage of `vector`

Common usage is introduced below. For details, [see the C++ documentation](https://en.cppreference.com/w/cpp/container/vector).

#### Constructors

See the following code for examples, assuming you have already `using`-imported the relevant types from the `std` namespace:

```cpp
// 1. Create an empty vector; constant complexity
vector<int> v0;
// 1+. This guarantees constant time complexity when inserting the first 3 elements into vector
v0.reserve(3);
// 2. Create a vector with initial size 3; default element value is 0; linear complexity
vector<int> v1(3);
// 3. Create a vector with initial size 3; default element value is 2; linear complexity
vector<int> v2(3, 2);
// 4. Create a vector with initial size 3; default element value is 1,
// and use v2's allocator; linear complexity
vector<int> v3(3, 1, v2.get_allocator());
// 5. Create vector v4 as a copy of v2, with the same elements; linear complexity
vector<int> v4(v2);
// 6. Create vector v5 as a copy of part of v4, containing {v4[1], v4[2]}; linear complexity
vector<int> v5(v4.begin() + 1, v4.begin() + 3);
// 7. Move v2 into newly created vector v6 without copying; constant complexity; requires C++11
vector<int> v6(std::move(v2));  // Or v6 = std::move(v2);
```

??? note "Test code"
    ```cpp
    // The following is test code; interested readers can compile and run it themselves.
    cout << "v1 = ";
    copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << "v2 = ";
    copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << "v3 = ";
    copy(v3.begin(), v3.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << "v4 = ";
    copy(v4.begin(), v4.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << "v5 = ";
    copy(v5.begin(), v5.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << "v6 = ";
    copy(v6.begin(), v6.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    ```

The methods above are sufficient for constructing a `vector` in typical use.

#### Element Access

`vector` provides the following methods for element access:

1.  `at()`

    `v.at(pos)` returns a reference to the element at index `pos` in the container. If the index is out of range, it throws an exception of type `std::out_of_range`.

2.  `operator[]`

    `v[pos]` returns a reference to the element at index `pos` in the container. It does not perform bounds checking.

3.  `front()`

    `v.front()` returns a reference to the first element.

4.  `back()`

    `v.back()` returns a reference to the last element.

5.  `data()`

    `v.data()` returns a pointer to the first element in the contiguous memory used internally by `v` to store data.

#### Iterators

`vector` provides the following [iterators](./iterator.md):

1.  `begin()/cbegin()`

    Returns an iterator pointing to the first element, where `*begin = front`.

2.  `end()/cend()`

    Returns an iterator pointing to the container's end placeholder; note that it is not an element.

3.  `rbegin()/crbegin()`

    Returns a reverse iterator pointing to the first element of the reversed array, which can be understood as the last element of the forward container.

4.  `rend()/crend()`

    Returns an iterator pointing to the position after the last element of the reversed array, corresponding to the position before the container's first element; it is not an element.

Among the iterators listed above, those containing the character `c` are read-only iterators. You cannot modify elements in a `vector` through read-only iterators. If a `vector` itself is read-only, its ordinary iterators and read-only iterators are completely equivalent. Read-only iterators are supported since C++11.

#### Size and Capacity

`vector` has the following functions related to container size and capacity. Note that the size of a `vector` means the number of valid elements, while capacity means the amount of memory actually allocated. See the implementation details below for more information.

**Size-related functions**:

-   `empty()` returns a `bool` value, equivalent to `v.begin() == v.end()`: `true` means empty, `false` means non-empty.

-   `size()` returns the container size, that is, the number of elements, equivalent to `std::distance(v.begin(), v.end())`.

-   `resize(n)` changes the size of the `vector` to `n`. If `n` is greater than the current size, elements are appended; if an element value is provided as a parameter, that value is used, otherwise the default value is used. If `n` is less than the current size, the first `n` elements are kept and later elements are deleted.

-   `max_size()` returns the maximum possible size of the container.

    **Capacity-related functions**:

-   `reserve()` makes `vector` reserve a certain amount of memory to avoid unnecessary allocation and copying.

-   `capacity()` returns the container's capacity, that is, how many elements the current `vector` has allocated space for.

-   `shrink_to_fit()` makes the capacity of the `vector` match its size, removing unused capacity.

### Adding, Removing, and Modifying Elements

-   `clear()` removes all elements.
-   `insert()` supports inserting one or multiple elements at an iterator position. Its **complexity is linear in the distance from `pos` to the end, not constant**.
-   `erase()` deletes an element at an iterator or a range of elements, and returns the iterator after the last deleted element. Its complexity is the same as `insert`.
-   `push_back()` inserts an element at the end, with **constant** amortized complexity and linear worst-case complexity.
-   `pop_back()` deletes the last element, with constant complexity.
-   `swap()` swaps with another container. This operation has **constant complexity**, not linear complexity.

### Implementation Details of `vector`

The underlying storage of `vector` is still a fixed-length array. It supports dynamic expansion by adding operations that avoid capacity overflow. First, note that the number of elements in a `vector`, its size $n$, is not the same as the maximum number of elements its allocated memory can hold, its capacity $N$; `vector` stores these two values separately. When an element is added to a `vector`, if $n>N$, the container allocates an array of size $2N$, copies the old data from its original location to the new array, and then releases the old memory. Although the asymptotic complexity of this operation is $O(n)$, its amortized complexity can be proven to be $O(1)$. Deleting elements at the end and accessing elements are still $O(1)$ operations.
Therefore, as long as the size of the `vector` is estimated properly and `resize()` and `reserve()` are used well, the efficiency of `vector` will not differ much from that of a fixed-length array.

### `vector<bool>`

The standard library provides a special `vector` specialization for `bool`, where each "`bool`" occupies only 1 bit and dynamic growth is supported. However, the return type of its `operator[]` is not `bool&`, but `vector<bool>::reference`. Therefore, use `vector<bool>` cautiously; consider using `deque<bool>` or `vector<char>` instead. If you need to save space, use [`bitset`](./bitset.md) directly.

## `array`(C++11)

`std::array` is a **contiguous-memory**, **fixed-length** array data structure provided by STL. It is essentially a direct wrapper around native arrays.

### Why Use `array`?

`array` is STL's wrapper around arrays. Compared with `vector`, it sacrifices dynamic expansion, but gains performance almost identical to native arrays, assuming full optimization is enabled. Therefore, when C++11 features are available, fixed-length arrays can almost always be replaced directly by `array`, while dynamically allocated arrays can be replaced by `vector`.

### Member Functions

#### Implicitly Defined Member Functions

| Function    | Effect                                                 |
| ----------- | ------------------------------------------------------ |
| `operator=` | Rewrites each corresponding element with elements from another `array` |

#### Element Access

| Function     | Effect                                             |
| ------------ | -------------------------------------------------- |
| `at`         | Accesses the specified element with bounds checking |
| `operator[]` | Accesses the specified element **without** bounds checking |
| `front`      | Accesses the first element                         |
| `back`       | Accesses the last element                          |
| `data`       | Returns a pointer to the first array element in memory |

`at` throws `std::out_of_range` if `pos >= size()`.

#### Capacity

| Function   | Effect                                  |
| ---------- | --------------------------------------- |
| `empty`    | Checks whether the container is empty   |
| `size`     | Returns the number of contained elements |
| `max_size` | Returns the maximum number of elements it can contain |

Since every `array` is a fixed-size container, the value returned by `size()` equals the value returned by `max_size()`.

### Operations

| Function | Effect                              |
| -------- | ----------------------------------- |
| `fill`   | Fills the container with a specified value |
| `swap`   | Swaps contents                      |

**Note that swapping two `array`s is $\Theta(\text{size})$, not $O(1)$ like ordinary STL containers.**

### Non-Member Functions

| Function            | Effect                                      |
| ------------------- | ------------------------------------------- |
| `operator==`, etc.  | Compares values in `array` lexicographically |
| `std::get`          | Accesses an element of an `array`           |
| `std::swap`         | Specialized `std::swap` algorithm           |

The following is an example of using `array`:

```cpp
// 1. Create an empty array of length 3; constant complexity
std::array<int, 3> v0;
// 2. Create an array with specified constants; constant complexity
std::array<int, 3> v1{1, 2, 3};

v0.fill(1);  // Fill the array

// Access the array
for (int i = 0; i != arr.size(); ++i) cout << arr[i] << " ";
```

## `deque`

`std::deque` is a [double-ended queue](../../ds/queue.md#双端队列) data structure provided by STL. It provides linear-complexity insertion and deletion, and constant-complexity random access.

### Usage of `deque`

Common usage is introduced below. For details, [see the C++ documentation](https://en.cppreference.com/w/cpp/container/deque). The iterator functions of `deque` are the same as those of `vector`, so they are not described in detail.

#### Constructors

See the following code, assuming you have already `using`-imported the relevant types from the `std` namespace:

```cpp
// 1. Define an empty deque v0 of type int
deque<int> v0;
// 2. Define a deque v1 of type int and set its initial size to 10; linear complexity
deque<int> v1(10);
// 3. Define a deque v2 of type int and initialize it with ten 1s; linear complexity
deque<int> v2(10, 1);
// 4. Copy the existing deque v1; linear complexity
deque<int> v3(v1);
// 5. Create deque v4 as a copy of v2, containing v2[0] through v2[2]; linear complexity
deque<int> v4(v2.begin(), v2.begin() + 3);
// 6. Move v2 into newly created deque v5 without copying; constant complexity; requires C++11
deque<int> v5(std::move(v2));
```

#### Element Access

Same as `vector`, but underlying memory cannot be accessed. For its efficient element access speed, see the implementation details section.

-   `at()` returns a reference to the element at a specified position in the container, performs bounds checking, and has **constant complexity**.
-   `operator[]` returns a reference to the element at a specified position in the container. It does not perform bounds checking and has **constant complexity**.
-   `front()` returns a reference to the first element.
-   `back()` returns a reference to the last element.

#### Iterators

Same as `vector`.

#### Size

Same as `vector`, but without `reserve()` and `capacity()`. It still has `shrink_to_fit()`.

#### Adding, Removing, and Modifying Elements

Same as `vector`, with additional functions for adding elements to the front of the queue.

-   `clear()` removes all elements.
-   `insert()` supports inserting one or multiple elements at an iterator position. Its **complexity is linear in the smaller distance from `pos` to either end**.
-   `erase()` deletes an element at an iterator or a range of elements, and returns the iterator after the last deleted element. Its complexity is the same as `insert`.
-   `push_front()` inserts an element at the front, with **constant complexity**.
-   `pop_front()` deletes the front element, with **constant complexity**.
-   `push_back()` inserts an element at the end, with **constant complexity**.
-   `pop_back()` deletes the last element, with **constant complexity**.
-   `swap()` swaps with another container. This operation has **constant complexity**, not linear complexity.

### Implementation Details of `deque`

The usual underlying implementation of `deque` is multiple non-contiguous buffers, while memory inside each buffer is contiguous. Each buffer also records head and tail pointers to mark the valid data range. When a buffer is full, a new buffer is allocated before or after it to store more data. For more detailed explanation, see [the implementation principle of `deque` in *STL Source Code Analysis*](https://www.cnblogs.com/q1076452761/p/16903229.html).

## `list`

`std::list` is a [doubly linked list](../../ds/linked-list.md) data structure provided by STL. It provides linear-complexity random access and constant-complexity insertion and deletion.

### Usage of `list`

The usage of `list` is basically the same as that of `deque`, but the complexities of insertion/deletion and access differ. For details, [see the C++ documentation](https://en.cppreference.com/w/cpp/container/list). The iterator, size, and element insertion/deletion/modification functions of `list` are the same as those of `deque`, so they are not described in detail.

#### Element Access

Because `list` is implemented as a linked list, it does not provide a random access interface. To access middle elements, use iterators.

-   `front()` returns a reference to the first element.
-   `back()` returns a reference to the last element.

#### Operations

The `list` type also provides some STL algorithm functions implemented specifically for its characteristics. Since these algorithms require [random access iterators](./iterator.md), `list` provides special implementations for convenient use. These algorithms include `splice()`, `remove()`, `sort()`, `unique()`, `merge()`, and others.

## `forward_list`（C++11）

`std::forward_list` is a [singly linked list](../../ds/linked-list.md) data structure provided by STL. Compared with `std::list`, it reduces space overhead.

### Usage of `forward_list`

The usage of `forward_list` is almost the same as that of `list`, but its iterators are only one-way, so its detailed usage is not described here. For details, [see the C++ documentation](https://en.cppreference.com/w/cpp/container/forward_list).
