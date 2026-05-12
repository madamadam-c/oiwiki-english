## Classification

![](images/container1.png)

### Sequence Containers

-   **Vector** (`vector`): a sequential list that can efficiently add elements at the back.
-   **Array** (`array`) **C++11**: a fixed-length sequential list, a simple wrapper around C-style arrays.
-   **Deque** (`deque`): a sequential list that can efficiently add elements at both ends.
-   **List** (`list`): a linked list that can be traversed in both directions.
-   **Forward list** (`forward_list`): a linked list that can be traversed in only one direction.

### Associative Containers

-   **Set** (`set`): a container that stores **distinct** elements in order. It is implemented as a red-black tree of nodes, where each node contains one element and nodes are ordered by a predicate that compares elements.
-   **Multiset** (`multiset`): a container that stores elements in order and allows equal elements.
-   **Map** (`map`): a collection of {key, value} pairs ordered by a predicate that compares keys.
-   **Multimap** (`multimap`): a multiset of {key, value} pairs, that is, a map that allows equal keys.

???+ note "What is a predicate ([**Predicate**](https://en.wikipedia.org/wiki/Predicate_%28mathematical_logic%29))?"
    A predicate is a function whose return value is true or false. STL containers often use predicates as template parameters.

### Unordered (Associative) Containers

-   **Unordered (multi)set** (`unordered_set`/`unordered_multiset`) **C++11**: unlike `set`/`multiset`, elements are unordered; it only cares whether an element exists and is implemented with hashing.
-   **Unordered (multi)map** (`unordered_map`/`unordered_multimap`) **C++11**: unlike `map`/`multimap`, keys are unordered; it only cares about the correspondence between keys and values and is implemented with hashing.

### Container Adapters

Container adapters are not really containers. They lack some container features, such as iterators and a `clear()` function.

> An adapter is a mechanism that makes one thing behave like another. A container adapter wraps a container so that it exhibits different behavior.

-   **Stack** (`stack`): a last-in-first-out (LIFO) container, by default a wrapper around a deque (`deque`).
-   **Queue** (`queue`): a first-in-first-out (FIFO) container, by default a wrapper around a deque (`deque`).
-   **Priority queue** (`priority_queue`): a queue whose element order is determined by a predicate applied to the stored values, by default a wrapper around a vector (`vector`).

## Common Features

### Container Declaration

All declarations have the form `containerName<typeName,...> name`, but the number and form of template parameters (the parameters inside `<>`) vary by container.

The essential reason is that STL is the Standard Template Library, so its containers are template classes.

### Iterators

See [Iterators](./iterator.md).

### Common Functions

`=`: assignment operator and copy constructor.

`begin()`: returns an iterator pointing to the first element.

`end()`: returns an iterator pointing to the element after the last element. `end()` does not point to an element; it is the successor of the last element.

`size()`: returns the number of elements in the container.

`max_size()`: returns the maximum number of elements the container can **theoretically** store. This depends on the container type and the stored value type.

`empty()`: returns whether the container is empty.

`swap()`: swaps two containers.

`clear()`: clears the container.

`==`/`!=`/`<`/`>`/`<=`/`>=`: compare two containers in **lexicographical order**. When comparing elements, each `map` element is equivalent to an element of `set<pair<key, value>>`. Unordered containers do not support `<`/`>`/`<=`/`>=`.
