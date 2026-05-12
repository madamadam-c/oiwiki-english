author: Xeonacid, ouuan, Ir1d, WAAutoMaton, Chrogeek, abc1763613206, Planet6174, i-Yirannn, opsiff, GoodCoder666

## `__gnu_pbds::priority_queue`

See also: [official documentation: complexity and constant-factor tests](https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/pq_performance_tests.html#std_mod1)

```cpp
#include <ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
__gnu_pbds::priority_queue<T, Compare, Tag, Allocator>
```

## Template Parameters

-   `T`: the stored element type.
-   `Compare`: a comparison type that provides a strict weak ordering.
-   `Tag`: one of five heap types provided by `__gnu_pbds`. The default `Tag` parameter is `pairing_heap_tag`. The five types are:
    -   `pairing_heap_tag`: pairing heap. The official documentation considers pairing heaps to perform best for non-native elements, such as custom structs, `std::string`, and `pair`.
    -   `binary_heap_tag`: binary heap. The official documentation considers binary heaps to perform best for native elements, although the author's tests did not show such good performance.
    -   `binomial_heap_tag`: binomial heap. It performs better than binary heaps for merge operations, but getting the heap top has higher complexity than in a binary heap.
    -   `rc_binomial_heap_tag`: redundant-counter binomial heap.
    -   `thin_heap_tag`: a tag whose complexities are the same as a Fibonacci heap except for merge.
-   `Allocator`: allocator type. It rarely appears in OI, so it is not explained here.

Since this article is intended for students learning competitive programming, it only briefly introduces the complexities of the latter four tags, while describing the member functions and usage of the first one.

Based on the author's local tests of basic heap operations on a Core i5 @3.1 GHz on macOS, together with GNU's official complexity tests and Dijkstra tests, the results show that, at least for OI contestants, the four tags other than pairing heap are of little practical value: they are either useless, have constants so large that they are worse than `std`, or may cause MLE. Therefore, only the default pairing heap is recommended here. Similarly, pairing heaps are also better than `make_heap()` from the `algorithm` library.

## Construction

The namespace must be specified because the class name conflicts with `std`.

```cpp
// __gnu_pbds::priority_queue<int>;
// __gnu_pbds::priority_queue<int, greater<int>>;
// __gnu_pbds::priority_queue<int, greater<int>, pairing_heap_tag>;
__gnu_pbds::priority_queue<int>::point_iterator id;  // point iterator
// modify and push both return a point_iterator; its usage is explained below
id = q.push(1);
```

## Member Functions

-   `push()`: pushes an element into the heap and returns an iterator to its position.
-   `pop()`: pops the heap top.
-   `top()`: returns the heap top.
-   `size()`: returns the number of elements.
-   `empty()`: returns whether it is empty.
-   `modify(point_iterator, const key)`: modifies the `key` at the iterator position to the passed `key`, then reorders the underlying storage structure.
-   `erase(point_iterator)`: erases the key-value at the iterator position from the heap.
-   `join(__gnu_pbds::priority_queue &other)`: merges `other` into `*this` and clears `other`.

The tag used determines the time complexity of each operation:

|                        | push                                | pop                                 | modify                              | erase                               | Join              |
| ---------------------- | ----------------------------------- | :---------------------------------- | ----------------------------------- | ----------------------------------- | ----------------- |
| `pairing_heap_tag`     | $O(1)$                              | worst $\Theta(n)$, amortized $\Theta(\log(n))$ | worst $\Theta(n)$, amortized $\Theta(\log(n))$ | worst $\Theta(n)$, amortized $\Theta(\log(n))$ | $O(1)$            |
| `binary_heap_tag`      | worst $\Theta(n)$, amortized $\Theta(\log(n))$ | worst $\Theta(n)$, amortized $\Theta(\log(n))$ | $\Theta(n)$                         | $\Theta(n)$                         | $\Theta(n)$       |
| `binomial_heap_tag`    | worst $\Theta(\log(n))$, amortized $O(1)$      | $\Theta(\log(n))$                   | $\Theta(\log(n))$                   | $\Theta(\log(n))$                   | $\Theta(\log(n))$ |
| `rc_binomial_heap_tag` | $O(1)$                              | $\Theta(\log(n))$                   | $\Theta(\log(n))$                   | $\Theta(\log(n))$                   | $\Theta(\log(n))$ |
| `thin_heap_tag`        | $O(1)$                              | worst $\Theta(n)$, amortized $\Theta(\log(n))$ | worst $\Theta(\log(n))$, amortized $O(1)$      | worst $\Theta(n)$, amortized $\Theta(\log(n))$ | $\Theta(n)$       |

## Example

```cpp
#include <algorithm>
#include <cstdio>
#include <ext/pb_ds/priority_queue.hpp>
#include <iostream>
using namespace __gnu_pbds;
// Since this article targets OI contestants, it uses the common heap pairing_heap_tag as an example
// For better readability, define the alias as follows:
using pair_heap = __gnu_pbds::priority_queue<int>;
pair_heap q1;  // max-heap, pairing heap
pair_heap q2;
pair_heap::point_iterator id;  // an iterator

int main() {
  id = q1.push(1);
  // Elements in the heap: [1];
  for (int i = 2; i <= 5; i++) q1.push(i);
  // Elements in the heap: [1, 2, 3, 4, 5];
  std::cout << q1.top() << std::endl;
  // Output: 5;
  q1.pop();
  // Elements in the heap: [1, 2, 3, 4];
  id = q1.push(10);
  // Elements in the heap: [1, 2, 3, 4, 10];
  q1.modify(id, 1);
  // Elements in the heap: [1, 1, 2, 3, 4];
  std::cout << q1.top() << std::endl;
  // Output: 4;
  q1.pop();
  // Elements in the heap: [1, 1, 2, 3];
  id = q1.push(7);
  // Elements in the heap: [1, 1, 2, 3, 7];
  q1.erase(id);
  // Elements in the heap: [1, 1, 2, 3];
  q2.push(1), q2.push(3), q2.push(5);
  // Elements in q1: [1, 1, 2, 3], elements in q2: [1, 3, 5];
  q2.join(q1);
  // q1 has no elements; elements in q2: [1, 1, 1, 2, 3, 3, 5];
}
```

## Invalidation Guarantees of \_\_gnu\_pbds Iterators (`invalidation\_guarantee`)

In the example above and in practice, such as using the pb-ds heap from this chapter to implement single-source shortest path algorithms, it is often necessary to save and use heap iterators, such as `__gnu_pbds::priority_queue<int>::point_iterator`.

However, different `Tag` parameters of `__gnu_pbds::priority_queue` have different underlying implementations, and their iterator invalidation conditions are also different. According to the design of the \_\_gnu\_pbds library, the following three cases are derived from top to bottom:

1.  Basic invalidation guarantee (`basic\_invalidation\_guarantee`): when the container is not modified, point iterators (`point\_iterator`), pointers, and references (key/value) **remain** valid.

2.  Point invalidation guarantee (`point\_invalidation\_guarantee`): after **modifying** the container, point iterators (`point\_iterator`), pointers, and references (key/value) **remain** valid as long as the corresponding element has not been deleted from the container.

3.  Range invalidation guarantee (`range\_invalidation\_guarantee`): after **modifying** the container, in addition to the properties in (2), any range-type iterator, including the return values of `begin()` and `end()`, is correct. Tags with range invalidation guarantees include `rb_tree_tag` and `splay_tree_tag` for `__gnu_pbds::tree`, as well as `pat_trie_tag` for `__gnu_pbds::trie`.

Running the following code shows that, except for `binary_heap_tag`, which has `basic_invalidation_guarantee` and invalidates iterators after modification, all others have `point_invalidation_guarantee`, which satisfies the requirement that point iterators (`point\_iterator`) remain valid after modification.

```cpp
#include <iostream>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
#include <cxxabi.h>

template <typename T>
void print_invalidation_guarantee() {
  using gute = __gnu_pbds::container_traits<T>::invalidation_guarantee;
  cout << abi::__cxa_demangle(typeid(gute).name(), 0, 0, 0) << endl;
}

int main() {
  using pairing =
      __gnu_pbds::priority_queue<int, greater<int>, pairing_heap_tag>;
  using binary = __gnu_pbds::priority_queue<int, greater<int>, binary_heap_tag>;
  using binomial =
      __gnu_pbds::priority_queue<int, greater<int>, binomial_heap_tag>;
  using rc_binomial =
      __gnu_pbds::priority_queue<int, greater<int>, rc_binomial_heap_tag>;
  using thin = __gnu_pbds::priority_queue<int, greater<int>, thin_heap_tag>;
  print_invalidation_guarantee<pairing>();
  print_invalidation_guarantee<binary>();
  print_invalidation_guarantee<binomial>();
  print_invalidation_guarantee<rc_binomial>();
  print_invalidation_guarantee<thin>();
  return 0;
}
```
