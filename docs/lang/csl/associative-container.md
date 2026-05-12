## `set`

`set` is an associative container: a sorted collection containing key-type objects. Search, removal, and insertion have logarithmic complexity. Internally, `set` is usually implemented with a [red-black tree](../../ds/rbtree.md). The properties of [balanced binary search trees](../../ds/bst.md) make `set` very suitable for cases that require lookup, insertion, and deletion at the same time.

Similar to mathematical sets, `set` does not contain elements with equal values. If equal elements are needed, use `multiset`. The usage of `multiset` is basically the same as that of `set`.

### Insertion and Deletion

-   `insert(x)` inserts element `x` into the `set` when the container has no equivalent element.
-   `erase(x)` deletes **all** elements with value `x` and returns the number of deleted elements.
-   `erase(pos)` deletes the element at iterator `pos`; the iterator must be valid.
-   `erase(first,last)` deletes all elements whose iterators are in the range $[first,last)$.
-   `clear()` clears the `set`.

???+ note "Return value of `insert`"
    The return type of `insert` is `pair<iterator, bool>`. The iterator points to the inserted element, or to the element already in the container whose value is equal to the inserted value. The bool indicates whether insertion succeeded. Because elements in a `set` are unique, insertion fails and returns `false` if an equal element already exists; otherwise it succeeds and returns `true`. The same applies to `insert` in `map`.

### Iterators

`set` provides the following iterators:

1.  `begin()/cbegin()`   
    Returns an iterator pointing to the first element, where `*begin = front`.
2.  `end()/cend()`   
    Returns an iterator pointing to the end placeholder of the array; note that it is not an element.
3.  `rbegin()/crbegin()`   
    Returns a reverse iterator pointing to the first element of the reversed array, which can be understood as the last element of the forward container.
4.  `rend()/crend()`   
    Returns an iterator pointing to the position after the last element of the reversed array, corresponding to the position before the container's first element; it is not an element.

Among the iterators listed above, those containing the character `c` are read-only iterators. You cannot modify elements in a `set` through read-only iterators. If a `set` itself is read-only, its ordinary iterators and read-only iterators are completely equivalent. Read-only iterators are supported since C++11.

### Lookup Operations

-   `count(x)` returns the number of elements in the `set` whose key is `x`.
-   `find(x)` returns an iterator to the element whose key is `x` if such an element exists in the `set`; otherwise it returns `end()`.
-   `lower_bound(x)` returns an iterator to the first element not less than the given key. If no such element exists, it returns `end()`.
-   `upper_bound(x)` returns an iterator to the first element greater than the given key. If no such element exists, it returns `end()`.
-   `empty()` returns whether the container is empty.
-   `size()` returns the number of elements in the container.

???+ warning "Time complexity of `lower_bound` and `upper_bound`"
    The member functions `lower_bound` and `upper_bound` of `set` have time complexity $O(\log n)$.
    
    However, using the `lower_bound` and `upper_bound` functions from the `algorithm` library to query elements in a `set` has time complexity $O(n)$.

???+ warning "Time complexity of `nth_element`"
    `set` does not provide a member `nth_element`. Using `nth_element` from the `algorithm` library to find the $k$-th largest element has time complexity $O(n)$.
    
    If you need the $O(\log n)$ operation of finding the $k$-th largest element, as supported by balanced binary search trees, you need to implement a balanced binary tree or value segment tree yourself, or use the balanced binary tree in the pb\_ds library.

### Examples

#### Using `set` in Greedy Algorithms

In greedy algorithms, operations such as **finding and deleting the smallest element greater than or equal to a certain value** are often needed. This can be done easily with `set`.

```cpp
// Currently available elements
set<int> available;
// Value that needs to be no greater than the selected element
int x;

// Find the smallest element greater than or equal to x
set<int>::iterator it = available.lower_bound(x);
if (it == available.end()) {
  // No such element exists; perform the corresponding operation...
} else {
  // Such an element was found; remove it from the currently available elements
  available.erase(it);
  // Perform the corresponding operation...
}
```

## `map`

`map` is an ordered key-value container whose element keys are unique. Search, removal, and insertion have logarithmic complexity. `map` is usually implemented as a [red-black tree](../../ds/rbtree.md).

Consider the following scenario: you need to store some key-value pairs, such as scores corresponding to student names: `Tom 0`, `Bob 100`, `Alan 100`. Since array indices can only be non-negative integers, names cannot be used as indices. The simplest solution is to use STL's `map`.

`map` overloads `operator[]`, so any type that defines `operator <` can be used as an index. In `map`, this is called a `key`:

```cpp
map<Key, T> yourMap;
```

Here, `Key` is the key type and `T` is the value type. The following is an example of using `map`:

```cpp
map<string, int> mp;
```

`map` does not contain elements with the same key. `multimap` allows multiple elements to have the same key. The usage of `multimap` is basically the same as that of `map`.

??? warning "Warning"
    Because `multimap` allows multiple elements to have the same key, it does not provide a method to access the corresponding value by key.

### Insertion and Deletion

-   You can directly use subscript access for lookup or insertion, for example `mp["Alan"]=100`.
-   Inserting a value of type `pair<Key, T>` into a `map` inserts an element, for example `mp.insert(pair<string,int>("Alan",100));`.
-   `erase(key)` deletes **all** elements whose key is `key`. The return value is the number of deleted elements.
-   `erase(pos)`: deletes the element at iterator `pos`; the iterator must be valid.
-   `erase(first,last)`: deletes all elements whose iterators are in the range $[first,last)$.
-   `clear()` clears the entire container.

???+ note "Caveats of subscript access"
    When accessing an element in a `map` by subscript, if the `map` does not contain an element with the corresponding key, a new element is automatically inserted into the `map` and its value is set to the default value. For integers, the value is zero; for types with a default constructor, the default constructor is called for initialization.
    
    If subscript access is too frequent, many meaningless elements may appear in the container and affect the efficiency of `map`. Therefore, it is generally recommended to use `find()` to search for elements with a specific key.

### Query Operations

-   `count(x)`: returns the number of elements in the container whose key is `x`. Complexity is $O(\log(size)+ans)$, logarithmic in container size plus the number of matches.
-   `find(x)`: returns an iterator to the element whose key is `x` if it exists in the container; otherwise returns `end()`.
-   `lower_bound(x)`: returns an iterator to the first element not less than the given key.
-   `upper_bound(x)`: returns an iterator to the first element greater than the given key. If all elements in the container are less than or equal to the given key, returns `end()`.
-   `empty()`: returns whether the container is empty.
-   `size()`: returns the number of elements in the container.

### Examples

#### Using `map` to Store Complex States

In search algorithms, we sometimes need to store complex states, such as coordinates, values that cannot be discretized, strings, and so on, together with related answers, such as the minimum number of steps to reach the state. `map` can implement this functionality. The key is the state, and the value is the related answer. The following example shows how to use `map` to store states represented by `string`.

```cpp
// Store states and corresponding answers
map<string, int> record;

// Newly found state and corresponding answer
string status;
int ans;
// Check whether the corresponding state has appeared
map<string, int>::iterator it = record.find(status);
if (it == record.end()) {
  // This state has not been searched; add it to the state record
  record[status] = ans;
  // Perform the corresponding operation...
} else {
  // This state has already been searched; perform the corresponding operation...
}
```

## Traversing Containers

Iterators can be used to traverse all elements of an associative container.

```cpp
set<int> s;
using si = set<int>::iterator;
for (si it = s.begin(); it != s.end(); it++) cout << *it << endl;
```

Note that dereferencing a `map` iterator gives a key-value pair of type `pair<Key, T>`.

In C++11, using a range-based `for` loop makes the code much simpler:

```cpp
set<int> s;
for (auto x : s) cout << x << endl;
```

For any associative container, traversing the container with iterators has time complexity $O(n)$.

## Custom Comparison

By default, the comparison function of `set` is `<`. For non-built-in types, you need to [overload the `<` operator](../op-overload.md#比较运算符). However, in some special cases, we want to customize the comparison method inside `set`.

This can be solved by passing a custom comparator.

Specifically, define a class and [overload the `()` operator](../op-overload.md#函数调用运算符) in it.

For example, to maintain a `set` of integers with larger values first, implement it as follows:

```cpp
struct cmp {
  bool operator()(int a, int b) const { return a > b; }
};

set<int, cmp> s;
```

For other associative containers, custom comparison can be implemented similarly and will not be repeated here.
