author: HeRaNO, konnyakuxzy, littlefrog

![./images/kuaizhuanglianbiao.png](./images/kuaizhuanglianbiao.png "./images/kuaizhuanglianbiao.png")

A block linked list roughly looks like this...

It is easy to see that a block linked list is a linked list where each node points to an array.
We split the original array of length n into $\sqrt{n}$ nodes, and each node corresponds to an array of size $\sqrt{n}$.
Therefore, we define the structure as shown below.
Here `sqn` means `sqrt(n)`, i.e. $\sqrt{n}$, and `pb` means `push_back`, i.e. adding an element into this `node`.

???+ note "Implementation"
    ```cpp
    struct node {
      node* nxt;
      int size;
      char d[(sqn << 1) + 5];
    
      node() { size = 0, nxt = NULL, memset(d, 0, sizeof(d)); }
    
      void pb(char c) { d[size++] = c; }
    };
    ```

A block linked list should at least support splitting, insertion, and lookup.
What is splitting? Splitting means splitting one `node` into two smaller `node`s, so that the size of every `node` remains close to $\sqrt{n}$ (otherwise it may degenerate into an ordinary array). When a `node`'s size exceeds $2\times \sqrt{n}$, perform a split operation.

How is splitting done? First create a new node, then `copy` the last $\sqrt{n}$ values of the split node into the new node, delete those last $\sqrt{n}$ values from the split node (`size--`), and finally insert the new node after the split node.

All operations on a block linked list have complexity $\sqrt{n}$.

There is one more point to mention.
As elements are inserted (or deleted), $n$ changes, and so does $\sqrt{n}$. This means the block size changes. Do we need to maintain the block size every time?

Actually, no. Just set $\sqrt{n}$ to a fixed value. For example, if the problem's limit is $10^6$, set $\sqrt{n}$ to a constant of size $10^3$ and do not change it.

```cpp
list<vector<char>> orz_list;
```

## `rope` in libstdc++

### Importing

The `rope` in libstdc++ also plays the role of a block linked list. It is implemented with a persistent balanced tree and can support random access, insertion, and deletion of elements.

Since `rope` is not truly implemented with a block linked list, its time complexity is not the same as a block linked list. Instead, it is equivalent to the complexity of a persistent balanced tree, i.e. $O(\log n)$.

It can be imported as follows:

```cpp
#include <ext/rope>
using namespace __gnu_cxx;
```

???+ warning "About library functions starting with double underscores"
    In OI, whether library functions starting with double underscores could be used was once uncertain. In 2021, CCF published the [Supplementary Explanation on Programming Language Restrictions in NOI Series Events](https://www.noi.cn/xw/2021-09-01/735729.shtml), mentioning that "library functions or macros starting with an underscore are allowed, except for library functions and macros with explicitly prohibited operations." Therefore, `rope` can currently be used normally in OI.

### Basic Operations

| Operation | Effect |
| :-------: | :-----: |
| `rope<int> a` | Initialize a `rope` (very similar to containers such as `vector`) |
| `a.push_back(x)` | Add element `x` to the end of `a` |
| `a.insert(pos, x)` | Insert element `x` at position `pos` in `a` |
| `a.erase(pos, x)` | Delete `x` elements starting at position `pos` in `a` |
| `a.at(x)` or `a[x]` | Access the `x`-th element of `a` |
| `a.length()` or `a.size()` | Get the size of `a` |

## Example

[POJ2887 Big String](http://poj.org/problem?id=2887)

Solution:
This is a simple template problem. The code is as follows:

```cpp
--8<-- "docs/ds/code/block-list/block-list_1.cpp"
```
