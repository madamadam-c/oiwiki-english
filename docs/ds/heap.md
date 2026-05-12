author: ouuan, HeRaNO

A heap is a tree where each node has a key value, and each node's key is either greater than or equal to / less than or equal to its parent’s key.

If every node’s key is greater than or equal to its parent’s key, the heap is called a **min‑heap**; otherwise it is a **max‑heap**. The STL [`priority_queue`](../lang/csl/container-adapter.md#priority‑queue) is essentially a max‑heap.

A (min) heap primarily supports the following operations: insert a number, query the minimum value, delete the minimum value, merge two heaps, and decrease the value of an element.

Some powerful heap variants (e.g., **mergeable heaps**) can efficiently support merge and similar operations.

Even more advanced heaps support persistence, allowing queries or operations on any historical version, which then generates a new version.

## Heap Classifications

| Operation \ Data Structure[^ref4] | Pairing Heap | Binary Heap | Leftist Tree | Binomial Heap | Fibonacci Heap |
| :------------------------------: | :----------: | :----------: | :----------: | :------------: | :------------: |
| Insert (`insert`) | $O(1)$ | $O(\log n)$ | $O(\log n)$ | $O(\log n)$[^ref1] | $O(1)$ |
| Find‑min (`find‑min`) | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$[^ref2][^ref3] | $O(1)$ |
| Delete‑min (`delete‑min`) | $O(\log n)$[^ref3] | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(\log n)$[^ref3] |
| Merge (`merge`) | $O(1)$ | $O(n)$ | $O(\log n)$ | $O(\log n)$ | $O(1)$ |
| Decrease‑key (`decrease‑key`) | $o(\log n)$ (lower bound $\Omega(\log \log n)$, upper bound $O(2^{2\sqrt{\log \log n}})$)[^ref3] | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(1)$[^ref3] |
| Persistence support | $\times$ | $\checkmark$ | $\checkmark$ | $\checkmark$ | $\times$ |

[^ref1]: A single insertion costs $O(\log n)$, but for $k$ consecutive insertions you can create a binomial heap containing only the new elements and then merge it with the existing heap, giving an amortized $O(1)$ cost.

[^ref2]: By maintaining a pointer to the minimum element and updating it during other operations, you can achieve $O(1)$ query time.

[^ref3]: Complexity shown is amortized.

[^ref4]: Table sourced from [Wikipedia – Priority queue summary of running times](https://en.wikipedia.org/wiki/Priority_queue#Summary_of_running_times).

By convention, when “heap” is mentioned without qualification, it usually refers to a **binary heap**.
