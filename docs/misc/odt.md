## Introduction

Chtholly Tree, also known as ODT (Old Driver Tree), originated from [CF896C](https://codeforces.com/problemset/problem/896/C).

This name refers to a technique that uses a balanced tree (`std::set`, `std::map`, etc.) or a linked list (`std::list`, a manually written linked list, etc.) to maintain color segments with amortized complexity, rather than to a specific data structure. Its core idea is to merge a continuous interval with the same value into one node. Compared with traditional data structures such as segment trees, Chtholly Tree can maintain the value of each covered interval more conveniently for problems involving range assignment.

## Implementation (`std::set`)

### Node type

```cpp
struct Node_t {
  int l, r;
  mutable int v;

  Node_t(const int &il, const int &ir, const int &iv) : l(il), r(ir), v(iv) {}

  bool operator<(const Node_t &o) const { return l < o.l; }
};
```

Here, `int v` is the additional data specified by you.

???+ note "What does the `mutable` keyword mean?"
    `mutable` means "changeable", allowing us to modify the value of `v` in later operations. In C++, mutable is provided to bypass const restrictions. A variable modified by mutable (mutable can only modify non-static data members of a class) always remains changeable, even in a const function.
    
    This means we can directly modify the `v` value of an element already inserted into a `set`, without taking that element out and inserting it into the `set` again.

### Node storage

We want to maintain all nodes so that the left endpoints of the intervals represented by these nodes are strictly increasing and pairwise disjoint. Ideally, the union of all intervals should be a maximal continuous range. Here we use `std::set` as an example, maintaining all nodes with `set<Node_t> odt;`.

During initialization, insert a very long interval into the Chtholly Tree. For example, if the problem requires maintaining information for positions $1$ to $n$, insert the interval $[1,n+1]$.

### `split` operation

The `split` operation is the core of Chtholly Tree. It takes a position $x$, splits the interval originally containing point $x$ (denoted as $[l, r]$) into two intervals $[l, x)$ and $[x, r]$, and returns an iterator pointing to the latter.

Reference code:

```cpp
auto split(int x) {
  auto it = odt.lower_bound(Node_t(x, 0, 0));
  if (it != odt.end() && it->l == x) return it;
  --it;
  int l = it->l, r = it->r, v = it->v;
  odt.erase(it);
  odt.insert(Node_t(l, x - 1, v));
  return odt.insert(Node_t(x, r, v)).first;
}
```

On compilers that do not support return type deduction with `auto`, the return type of the function can be changed to `set<Node_t>::iterator`.

### `assign` operation

Another important operation is `assign`, which is used to assign a value to an interval. Suppose we are going to assign $v$ to the interval $[l,r]$.

First, extract the interval $[l, r]$. Call `split(r + 1), split(l)` in order, and denote the iterators returned by these two calls as $itr, itl$. Then the iterator range $[itl, itr)$ points to all intervals contained in $[l,r]$ in the Chtholly Tree.

Then delete the original information. `std::set` has a member method `erase` with a signature like `iterator erase( const_iterator first, const_iterator last );`, which can remove elements in the range `[first; last)`. Therefore, we call `odt.erase(itl, itr);` to delete the original information.

Finally, insert the new value for the interval $[l,r]$. Just call `odt.insert(Node_t(l, r, v))`.

Reference code:

```cpp
void assign(int l, int r, int v) {
  auto itr = split(r + 1), itl = split(l);
  odt.erase(itl, itr);
  odt.insert(Node_t(l, r, v));
}
```

???+ note "Why do we need to call `split(r + 1)` before `split(l)`?"
    1.  The `std::set::erase` method invalidates references and iterators pointing to erased elements. Other references and iterators are not affected.
    2.  The `std::set::insert` method does not invalidate any iterators or references.
    3.  The `split` operation splits an interval. After calling `split(r + 1)`, $r + 1$ becomes the left endpoint of the right interval among the two new intervals. At this point, splitting the left interval will definitely not access the interval whose left endpoint is $r + 1$, so it will not split and erase the interval whose left endpoint is $r + 1$, invalidating its iterator. Conversely, if we call `split(l)` first and then `split(r + 1)`, the interval whose left endpoint is $l$ may be erased, invalidating the iterator.

### `perform` operation

Extract an interval range from the Chtholly Tree and operate on it. This is similar to the `assign` operation, except that deleting the interval range is replaced by traversing it.

Reference code:

```cpp
void perform(int l, int r) {
  auto itr = split(r + 1), itl = split(l);
  for (; itl != itr; ++itl) {
    // Perform Operations here
  }
}
```

Note that such extraction operations should not be abused, as they may make the time complexity invalid. See the "Complexity analysis" section below.

## Implementation (`std::map`)

Compared with the `std::set` implementation, the `split` operation in the `std::map` implementation is simpler to write. Other than that, the remaining operations are no different from those in `std::set`.

### Node storage

Since the intervals stored in a Chtholly Tree are continuous, we do not necessarily need to record the right endpoints. We can use a `map<int, int> mp;` to store all intervals: the key maintains the left endpoint, and the value maintains the value from that left endpoint to before the next left endpoint.

During initialization, if the problem requires maintaining information for positions $1$ to $n$, call `mp[1] = -1, mp[n + 1] = -1` to indicate that $[1,n+1)$, namely $[1, n]$, is set to the special value $-1$. The interval $[n+1, +\infty)$ is used as a sentinel and can also be initialized.

### `split` operation

Reference code (first version):

```cpp
void split(int x) {
  auto it = prev(mp.upper_bound(x));  // Find the interval whose left endpoint is at most x.
  mp[x] = it->second;  // Create a new interval and copy the stored value from the previous interval.
}
```

Reference code (second version):

```cpp
auto split(int pos) {
  auto it = prev(mp.upper_bound(pos));  // Find the interval whose left endpoint is at most x.
  return mp.insert(it, make_pair(pos, it->second));
  // Create a new interval and copy the stored value from the previous interval.
}
```

Here we use the overload `iterator insert( const_iterator pos, const value_type& value );` of `std::map::insert`, which inserts `value` at the position as close as possible to just before `pos`. If the insertion happens exactly just before `pos`, the complexity is amortized constant; otherwise, the complexity is logarithmic in the container size.

### `assign` operation

For the assign operation, we need to delete all interval left endpoints in $[l,r−1]$, then create a new interval.

```cpp
void assign(int l, int r, int v) {  // Note: here r is the interval's right endpoint + 1
  split(l);
  split(r);
  auto it = mp.find(l);
  while (it->first != r) {
    it = mp.erase(it);
  }
  mp[l] = v;
}
```

### `perform` operation

```cpp
void perform(int l, int r) {  // Note: here r is the interval's right endpoint + 1
  split(l);
  split(r);
  auto it = mp.find(l);
  while (it->first != r) {
    // Perform Operations here
    it = next(it);
  }
}
```

## Implementation (linked list)

The mainstream implementation currently maintains nodes based on `set`, but because the average number of maintained intervals is small, the advantage of `set` is not obvious. In comparison, a linked list (or array) can maintain split and merge operations more concisely.

### Node storage

```cpp
using i64 = int64_t;

struct Block {
  Block *next;  // Next node in the linked list
  int l, r;     // Interval range
  i64 val;      // Value on the interval

  Block(Block *next, int l, int r, i64 val)
      : next(next), l(l), r(r), val(val) {}

  bool operator<(const Block &b) const { return val < b.val; }
} *root;
```

### `split` operation

```cpp
// Return the interval whose left endpoint is mid+1
Block *split(int mid) {
  for (Block *b = root; b; b = b->next) {  // Traverse the linked list
    if (b->l == mid + 1) {                 // Left endpoint is mid+1
      return b;
    }
    // Find an interval [l, r] that contains mid and mid+1, and split it into [l, mid] and [mid+1,
    // r]
    if (b->l <= mid && mid + 1 <= b->r) {
      b->next = new Block(b->next, mid + 1, b->r, b->val);
      b->r = mid;
      return b->next;
    }
  }
  return nullptr;  // Not found; return null
}
```

When operating on an interval, because we cannot maintain only part of an interval, the following operations all need to split intervals in advance before performing the corresponding operation.

```cpp
Block *lb, *rb;

// Pre-split to ensure subsequent operations are inside [l, r]
void prepare(int l, int r) {
  lb = split(l - 1);
  rb = split(r);
}
```

### `assign` operation

```cpp
void assign(int l, int r, i64 val) {
  prepare(l, r);
  lb->r = r;  // Change interval [lb.l, lb.r] to [lb.l, r]
  lb->val = val;
  lb->next = rb;  // Link [lb.l, r] to the adjacent interval on its right
}

// Note: the memory of deleted nodes is not freed here; add it yourself if needed
```

### `perform` operation

```cpp
void perform(int l, int r) {
  prepare(l, r);
  for (Block *b = lb; b != rb; b = b->next) {
    // Perform Operations here
  }
}
```

## Complexity analysis

### Calling `assign` on the same interval immediately after `perform`

In this case, we can observe that two `split` operations add at most two intervals. One `assign` deletes all intervals in the range and adds one interval, while also traversing the deleted intervals. Therefore, the number of intervals we traverse is linear in the number of intervals deleted. Since each operation only adds $O(1)$ intervals, the number of intervals we operate on is linear in the number of operations (including initialization). The time complexity is amortized $O(m\log n)$, where $m$ is the number of operations and $n$ is the maximum number of intervals in the Chtholly Tree (one may regard $n\leq m$).

### Not calling `assign` after `perform`

If specially constructed data is allowed, this can definitely be hacked. It is enough to make the Chtholly Tree contain sufficiently many different intervals and traverse them repeatedly, which can make its complexity reach, or even exceed, quadratic level.

To guarantee the stated complexity, the data must be random. See [the proof of Chtholly Tree complexity on Codeforces](http://codeforces.com/blog/entry/56135?#comment-398940). For a more detailed rigorous proof, see [Complexity Analysis of Chtholly Tree](https://zhuanlan.zhihu.com/p/102786071). The conclusion of the proof is that the complexity of Chtholly Tree implemented with `std::set` is $O(n \log \log n)$, while the complexity of the linked-list implementation is $O(n \log n)$.

## Practice

-   [「Luogu 1840」Color the Axis](https://www.luogu.com.cn/problem/P1840)
-   ~~[「SCOI2010」Sequence Operations](https://www.luogu.com.cn/problem/P2572)~~ (hack data has been added to this problem source)
-   [「SHOI2015」脑洞治疗仪](https://loj.ac/problem/2037)
-   [「Luogu 4979」矿洞：坍塌](https://www.luogu.com.cn/problem/P4979)
-   [「Luogu 8146」risrqnis](https://www.luogu.com.cn/problem/P8146)

## Further reading

[ODT 的映射思想的推广 - 洛谷专栏 (luogu.com.cn)](https://www.luogu.com.cn/article/0mys9qkh)

## References and notes

-   [Problem - 896C - Codeforces](https://codeforces.com/problemset/problem/896/C) (the origin of Chtholly Tree)
-   [CF896C Willem, Chtholly and Seniorious 题解 - 洛谷专栏 (luogu.com.cn)](https://www.luogu.com.cn/article/gyxbe23s) (`std::set` implementation reference)
-   [珂朵莉树的 map 实现 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/469794466) (`std::map` implementation reference)
-   [题解 CF896C【Willem, Chtholly and Seniorious】- 洛谷专栏 (luogu.com.cn)](https://www.luogu.com.cn/article/umiw1fwp) (linked-list implementation reference)
-   [Codeforces Round #449 Editorial - Codeforces](https://codeforces.com/blog/entry/56135?#comment-398940) (proof of Chtholly Tree complexity)
-   [珂朵莉树的复杂度分析 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/102786071) (complexity analysis of Chtholly Tree)
