In STL, an iterator is an object used to access and inspect elements in STL containers. Its behavior is similar to a pointer, but it wraps some validity checks and provides a unified access format. Similar concepts exist in many other high-level languages, such as Python's `__iter__` function and C#'s `IEnumerator`.

## Basic Usage

The term iterator may sound obscure, but an iterator itself can be viewed as a data pointer. Iterators mainly support two operators: increment (`++`) and dereference (the unary `*` operator). Increment moves the iterator, and dereference obtains or modifies the element it points to.

The type of an iterator pointing to an element in an [STL container](./container.md) `container` is usually `container::iterator`.

Iterators can be used to traverse containers. For example, the following two `for` loops have the same effect:

```cpp
vector<int> data(10);

for (int i = 0; i < data.size(); i++)
  cout << data[i] << endl;  // Access elements by index

for (vector<int>::iterator iter = data.begin(); iter != data.end(); iter++)
  cout << *iter << endl;  // Access elements by iterator
// Since C++11, auto iter = data.begin() can simplify the code above
```

???+ tip "Using `auto` in contests"
    Most contestants like to use `auto` instead of verbose iterator declarations. According to the [Supplementary Explanation on Programming Language Restrictions in NOI-Series Events](https://www.noi.cn/xw/2021-09-01/735729.shtml) published in September 2021, NOI-series contests, including CSP J/S, use **C++14** for judging, and this version already supports the `auto` keyword.

## Categories

In the STL definition, iterators are classified by the operations they support into the following categories:

-   InputIterator: only needs to support copying, increment, and dereference access.
-   OutputIterator: only needs to support copying, increment, and dereference assignment.
-   ForwardIterator: based on InputIterator, supports multiple passes and guarantees that repeated dereference access produces consistent results.
-   BidirectionalIterator: based on ForwardIterator, supports decrement, that is, backward access.
-   RandomAccessIterator: based on BidirectionalIterator, supports addition/subtraction and comparison operations, that is, random access.
-   ContiguousIterator: based on RandomAccessIterator, requires that for a dereferenceable iterator `a + n`, `*(a + n)` is equivalent to `*(std::address_of(*a) + n)`, meaning contiguous storage, where `a` is a contiguous iterator and `n` is an integer value.

    ContiguousIterator was formally introduced in C++17.

???+ tip "Why is an input iterator called an input iterator?"
    "Input" means that input can be obtained from the iterator, while "output" means that output can be written to the iterator.
    
    The actors of "input" and "output" are other parts of the program, not the iterator itself.

These iterator categories are not mutually exclusive. In fact, except for output iterators, the iterators earlier in the list are included by the iterators later in the list. For example, where a forward iterator is required, a bidirectional iterator can also be used. Starting from forward iterators, if such iterators also implement the functionality of output iterators, that is, allow write operations, they are called mutable iterators. This gives rise to categories such as "mutable random access iterator".

Different [STL containers](./container.md) support different iterator categories, so pay attention when using them.

Array pointers satisfy all requirements of contiguous iterators, or random access iterators in C++14 and earlier, and can be used as contiguous iterators.

## Related Functions

Many [STL functions](./algorithm.md) use iterators as parameters.

You can use `std::advance(it, n)` to move iterator `it` forward by `n` steps. If `n` is negative, it moves backward accordingly; in this case the iterator must satisfy BidirectionalIterator, otherwise the behavior is undefined.

Since C++11, `std::next(it)` obtains the successor of forward iterator `it` without modifying `it`, and `std::next(it, n)` obtains the `n`-th successor of forward iterator `it`.

Since C++11, `std::prev(it)` obtains the predecessor of bidirectional iterator `it` without modifying `it`, and `std::prev(it, n)` obtains the `n`-th predecessor of bidirectional iterator `it`.

[STL containers](./container.md) generally support access from one or both ends, as well as support for the [const modifier](../const.md). For example, a container's `begin()` function obtains an iterator pointing to the first element, `rbegin()` obtains a reverse iterator pointing to the last element, `cbegin()` obtains a const iterator pointing to the first element, and `end()` obtains an iterator pointing to the end of the container. The "end" is not the last element; it can be viewed as the successor of the last element. Its predecessor is the last element in the container, and it itself does not point to any element.

More usage can be found at [Iterator library - cppreference.com](https://en.cppreference.com/w/cpp/iterator).
