## `__gnu_pbds::tree`

See also: [official documentation](https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/tree_based_containers.html)

```cpp
#include <ext/pb_ds/assoc_container.hpp>  // tree is defined here, so include this header
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
__gnu_pbds::tree<Key, Mapped, Cmp_Fn = std::less<Key>, Tag = rb_tree_tag,
                 Node_Update = null_tree_node_update,
                 Allocator = std::allocator<char>>
```

## Template Parameters

-   `Key`: the stored element type. If you want to store multiple identical `Key` elements, you need to use a method similar to `std::pair` or `struct`, together with the `lower_bound` and `upper_bound` member functions for lookup.
-   `Mapped`: the mapped-policy type. To indicate that the associative container is a **set**, similar to storing elements in `std::set`, use `null_type` here; in older versions of `g++`, this is `null_mapped_type`. To indicate that the associative container is a **set with values**, similar to storing elements in `std::map`, use a `Value` type similar to `std::map<Key, Value>`.
-   `Cmp_Fn`: key comparison functor, such as `std::less<Key>`.
-   `Tag`: selects the underlying data structure type. The default is `rb_tree_tag`. `__gnu_pbds` provides three different balanced trees:
    -   `rb_tree_tag`: red-black tree. This is generally used; the latter two usually perform worse than red-black trees.
    -   `splay_tree_tag`: splay tree.
    -   `ov_tree_tag`: ordered-vector tree. It is merely an ordered structure implemented by `vector`, similar to using a sorted `vector` to implement a balanced tree; its performance depends on whether the data is adversarial.
-   `Node_Update`: the policy used to update nodes. The default is `null_node_update`. To use `order_of_key` and `find_by_order`, use `tree_order_statistics_node_update`.
-   `Allocator`: allocator type.

## Construction

```cpp
__gnu_pbds::tree<std::pair<int, int>, __gnu_pbds::null_type,
                 std::less<std::pair<int, int>>, __gnu_pbds::rb_tree_tag,
                 __gnu_pbds::tree_order_statistics_node_update>
    trr;
```

## Member Functions

-   `insert(x)`: inserts an element `x` into the tree and returns `std::pair<point_iterator, bool>`, where the first element is an iterator to the insertion position and the second element indicates whether insertion succeeded.
-   `erase(x)`: deletes an element/iterator `x` from the tree. If `x` is an iterator, it returns an iterator to the element after `x`, or `end()` if `x` is `end()`. If `x` is a `Key`, it returns whether deletion succeeded; deletion fails if the key does not exist.
-   `order_of_key(x)`: returns the number of elements strictly less than `x`, using `Cmp_Fn` as the comparison logic, that is, the zero-based rank.
-   `find_by_order(x)`: returns an iterator to the element with rank `x` under the `Cmp_Fn` comparison.
-   `lower_bound(x)`: returns an iterator to the first element not less than `x`, using `Cmp_Fn` as the comparison logic.
-   `upper_bound(x)`: returns an iterator to the first element strictly greater than `x`, using `Cmp_Fn` as the comparison logic.
-   `join(x)`: merges tree `x` into the current tree and clears tree `x`. The **comparison function** and **element type** of the two trees must be the same.
-   `split(x,b)`: using `Cmp_Fn` for comparison, elements less than or equal to `x` remain in the current tree, and the rest go into tree `b`.
-   `empty()`: returns whether it is empty.
-   `size()`: returns the size.

???+ warning "Note"
    The `join(x)` function requires that the key value ranges of the tree being merged and the current tree **do not intersect**. In other words, all values in the merged tree must be greater than or less than all values in the current tree; otherwise, a `join_error` exception is thrown.
    
    To merge two trees whose value ranges intersect, insert the elements of one tree into the other one by one.

## Example

```cpp
// Common Header Simple over C++11
#include <iostream>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
__gnu_pbds::tree<pair<int, int>, __gnu_pbds::null_type, less<pair<int, int>>,
                 __gnu_pbds::rb_tree_tag,
                 __gnu_pbds::tree_order_statistics_node_update>
    trr;

int main() {
  int cnt = 0;
  trr.insert(make_pair(1, cnt++));
  trr.insert(make_pair(5, cnt++));
  trr.insert(make_pair(4, cnt++));
  trr.insert(make_pair(3, cnt++));
  trr.insert(make_pair(2, cnt++));
  // Elements in the tree: {(1,0), (2,4), (3,3), (4,2), (5,1)}

  auto it = trr.lower_bound(make_pair(2, 0));
  trr.erase(it);
  // Elements in the tree: {(1,0), (3,3), (4,2), (5,1)}

  // Output first of the element with rank 1 among ranks 0, 1, 2, 3
  auto it2 = trr.find_by_order(1);
  cout << (*it2).first << endl;  // Output: 3

  // Output its rank
  int pos = trr.order_of_key(*it2);
  cout << pos << endl;  // Output: 1

  // Split trr by it2
  decltype(trr) newtr;
  trr.split(*it2, newtr);
  for (auto i = newtr.begin(); i != newtr.end(); ++i) {
    cout << (*i).first << ' ';  // Output: 4 5
  }
  cout << endl;

  // Merge newtr into trr; newtr is cleared.
  trr.join(newtr);
  for (auto i = trr.begin(); i != trr.end(); ++i) {
    cout << (*i).first << ' ';  // Output: 1 3 4 5
  }
  cout << endl;
  cout << newtr.size() << endl;  // Output: 0

  return 0;
}
```

## References

-   [Tree-Based Containers](https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/tree_based_containers.html)
-   [Implementation of the `join` function in GCC 14.1.0](https://gcc.gnu.org/onlinedocs/gcc-14.1.0/libstdc++/api/a18391_source.html#l00043)
-   [Implementation of the `erase` function in GCC 14.1.0](https://gcc.gnu.org/onlinedocs/gcc-14.1.0/libstdc++/api/a18211_source.html#l00043)
