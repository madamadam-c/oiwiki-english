author: GavinZhengOI, PlanariaIce

## Introduction

Discretization is a data-processing technique. In essence, it can be viewed as a kind of [hashing](../string/hash.md#hash-的思想), while ensuring that after hashing, the data still preserves the original [total/partial order](../math/order-theory.md#偏序集) relationship.

Informally, when some data cannot be conveniently used as array indices because the values themselves are too large or their type is unsupported, and only the relative order between elements affects the final result, we can process the original data by rank. This is discretization.

Objects used for discretization can be large integers, floating-point numbers, strings, and so on.

## Implementation

Discretizing an array and performing queries is a common use case.

### Method 1

Usually the original array contains duplicate elements, and identical elements are generally discretized to the same value.

The method is as follows:

1.  Create a copy of the original array.

2.  Sort the values in the copy from small to large.

3.  Remove duplicates from the sorted copy.

4.  Find the position of each element of the original array in the copy. This position is its rank and is used as the discretized value.

```cpp
// arr[i] is the initial array, with index range [1, n]

for (int i = 1; i <= n; ++i)  // step 1
  tmp[i] = arr[i];
std::sort(tmp + 1, tmp + n + 1);                          // step 2
int len = std::unique(tmp + 1, tmp + n + 1) - (tmp + 1);  // step 3
for (int i = 1; i <= n; ++i)                              // step 4
  arr[i] = std::lower_bound(tmp + 1, tmp + len + 1, arr[i]) - tmp;
```

The STL algorithms used in the reference implementation can be found in [STL Algorithms](../lang/csl/algorithm.md).

Similarly, we can also discretize a [std::vector](../lang/csl/sequence-container.md#vector):

```cpp
// std::vector<int> arr;
std::vector<int> tmp(arr);  // tmp is a copy of arr
std::sort(tmp.begin(), tmp.end());
tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());
for (int i = 0; i < n; ++i)
  arr[i] = std::lower_bound(tmp.begin(), tmp.end(), arr[i]) - tmp.begin();
```

### Method 2

Depending on problem requirements, sometimes identical elements must be discretized to different values according to input order.

At this point, implementing it with `std::lower_bound()` becomes somewhat difficult, so we need a different idea:

1.  Create a copy of the original array while recording the position where each element appears.

2.  Sort the copy by value from small to large. If values are equal, sort by occurrence order from small to large.

3.  Put the discretized numbers back into the original array.

```cpp
struct Data {
  int idx, val;

  bool operator<(const Data& o) const {
    if (val == o.val)
      return idx < o.idx;  // when values are equal, earlier elements get smaller discretized values
    return val < o.val;
  }
} tmp[MAXN];  // std::pair can also be used

for (int i = 1; i <= n; ++i) tmp[i] = Data{i, arr[i]};
std::sort(tmp + 1, tmp + n + 1);
for (int i = 1; i <= n; ++i) arr[tmp[i].idx] = i;
```

### Complexity

For Method 1, deduplication complexity is $O(n)$, sorting complexity is $O(n \log n)$, and the final $n$ searches have complexity $O(n \log n)$.

For Method 2, sorting complexity is $O(n \log n)$.

Therefore, the total time complexity of both methods is $O(n \log n)$.

The space complexity is $O(n)$.

## Exercises

-   [\[HAOI2014\] Posting Posters](https://www.luogu.com.cn/problem/P3740)
-   [\[NOI2015\] Automatic Program Analysis](https://www.luogu.com.cn/problem/P1955)
