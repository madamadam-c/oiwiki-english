## Definition

[Merge sort](https://en.wikipedia.org/wiki/Merge_sort) is an efficient comparison-based stable sorting algorithm.

## Properties

Merge sort is based on the divide-and-conquer approach to sort array segments and then merge them. The time complexity is $\Theta (n \log n)$ in the best, worst, and average cases, and the space complexity is $\Theta (n)$.

Merge sort can use only $\Theta (1)$ auxiliary space, but for convenience, an auxiliary array of the same length as the original array is typically used.

## Process

### Merging

The core part of merge sort is the merge process: merging two sorted arrays `a[i]` and `b[j]` into one sorted array `c[k]`.

Traverse `a[i]` and `b[j]` from left to right, find the smallest value and put it into array `c[k]`; repeat the above process until one of `a[i]` and `b[j]` is empty, then put the remaining elements of the other array into `c[k]`.

To ensure stability, when the first element of the first segment is less than or equal to the first element of the second segment (`a[i] <= b[j]`) rather than strictly less than (`a[i] < b[j]`), it should be taken as the minimum value and put into `c[k]`.

#### Implementation

=== "C/C++"
    === "Array implementation"
        ```cpp
        void merge(const int *a, size_t aLen, const int *b, size_t bLen, int *c) {
          size_t i = 0, j = 0, k = 0;
          while (i < aLen && j < bLen) {
            if (b[j] < a[i]) {  // <!> Check b[j] < a[i] first to ensure stability
              c[k] = b[j];
              ++j;
            } else {
              c[k] = a[i];
              ++i;
            }
            ++k;
          }
          // At this point, one array is empty and the other is non-empty; merge the non-empty array into c
          for (; i < aLen; ++i, ++k) c[k] = a[i];
          for (; j < bLen; ++j, ++k) c[k] = b[j];
        }
        ```

    === "Pointer implementation"
        ```cpp
        void merge(const int *aBegin, const int *aEnd, const int *bBegin,
                   const int *bEnd, int *c) {
          while (aBegin != aEnd && bBegin != bEnd) {
            if (*bBegin < *aBegin) {
              *c = *bBegin;
              ++bBegin;
            } else {
              *c = *aBegin;
              ++aBegin;
            }
            ++c;
          }
          for (; aBegin != aEnd; ++aBegin, ++c) *c = *aBegin;
          for (; bBegin != bEnd; ++bBegin, ++c) *c = *bBegin;
        }
        ```

    You can also use the `merge` function from the `<algorithm>` library, whose usage is the same as the pointer-style implementation above.

=== "Python"
    ```python
    def merge(a, b):
        i, j = 0, 0
        c = []
        while i < len(a) and j < len(b):
            # <!> Check b[j] < a[i] first to ensure stability
            if b[j] < a[i]:
                c.append(b[j])
                j += 1
            else:
                c.append(a[i])
                i += 1
        # At this point, one array is empty and the other is non-empty; merge the non-empty array into c
        c.extend(a[i:])
        c.extend(b[j:])
        return c
    ```

### Implementing Merge Sort with Divide-and-Conquer

1.  When the array length is $1$, the array is already sorted and does not need to be further divided.

2.  When the array length is greater than $1$, the array is likely not sorted. At this point, divide the array into two segments, then check whether each of the two arrays is sorted (using rule 1). If sorted, merge them into one sorted array; otherwise, repeat step 2 for the unsorted array, then merge.

Using mathematical induction, it can be proved that this process can transform an array into a sorted array.

To ensure sorting complexity, the array is typically divided into two segments of equal length as much as possible ($mid = \left\lfloor \dfrac{l + r}{2} \right\rfloor$).

#### Implementation

Note that the intervals represented by the code below are $[l, r)$, $[l, mid)$, and $[mid, r)$ respectively.

=== "C/C++"
    ```cpp
    void merge_sort(int *a, int l, int r) {
      if (r - l <= 1) return;
      // divide
      int mid = l + ((r - l) >> 1);
      merge_sort(a, l, mid), merge_sort(a, mid, r);
      // merge
      int tmp[1024] = {};  // Please set the length of the tmp array according to actual situation (same as a), or use
                           // vector; first put the merge result into tmp, then copy back to array a
      merge(a + l, a + mid, a + mid, a + r, tmp + l);  // pointer-style merge
      for (int i = l; i < r; ++i) a[i] = tmp[i];
    }
    ```

=== "Python"
    ```python
    def merge_sort(a, ll, rr):
        if rr - ll <= 1:
            return
        # divide
        mid = (rr + ll) // 2
        merge_sort(a, ll, mid)
        merge_sort(a, mid, rr)
        # merge
        a[ll:rr] = merge(a[ll:mid], a[mid:rr])
    ```

### Implementing Merge Sort with Doubling Method

It is known that when the array length is $1$, the array is already sorted.

Cut the entire array into segments of length $1$.

From left to right, merge two segments of length $1$ to get a series of sorted segments of length $\le 2$;

From left to right, merge two segments of length $\le 2$ to get a series of sorted segments of length $\le 4$;

From left to right, merge two segments of length $\le 4$ to get a series of sorted segments of length $\le 8$;

……

Repeat the above process until the array has only one sorted segment left. This segment is the sorted original array.

???+ note "Why is it $\le n$ rather than $= n$"
    The array length is likely not $2^x$, so at the end, segments of incomplete length may appear, and the last segment may be independent.

#### Implementation

=== "C/C++"
    ```cpp
    void merge_sort(int *a, size_t n) {
      int tmp[1024] = {};  // Please set the length of the tmp array according to actual situation (same as a), or use
                           // vector; first put the merge result into tmp, then copy back to array a
      for (size_t seg = 1; seg < n; seg <<= 1) {
        for (size_t left1 = 0; left1 < n - seg;
             left1 += seg + seg) {  // n - seg: if only one segment remains at the end, no merge is needed
          size_t right1 = left1 + seg;
          size_t left2 = right1;
          size_t right2 = std::min(left2 + seg, n);  // <!> pay attention to the boundary of the last segment
          merge(a + left1, a + right1, a + left2, a + right2,
                tmp + left1);  // pointer-style merge
          for (size_t i = left1; i < right2; ++i) a[i] = tmp[i];
        }
      }
    }
    ```

=== "Python"
    ```python
    def merge_sort(a):
        seg = 1
        while seg < len(a):
            for l1 in range(0, len(a) - seg, seg + seg):
                r1 = l1 + seg
                l2 = r1
                r2 = l2 + seg
                a[l1:r2] = merge(a[l1:r1], a[l2:r2])
        seg <<= 1
    ```

## Inversion Pair

Related reading and reference implementation: [Inversion Pair](../math/permutation.md#inversion-count)

An inversion pair is an ordered pair $(i, j)$ where $i < j$ and $a_i > a_j$.

The sorted array has no inversion pairs. In the merge operation of merge sort, each time the first element of the second segment is taken as the current minimum, the sum of the remaining elements in the first segment is exactly the number of inversion pairs reduced by the merge operation; therefore, the time complexity of merge sort for counting inversion pairs is $\Theta (n \log n)$. Additionally, inversion pair counting can also be solved using a Fenwick tree or segment tree, with time complexity also $O(n \log n)$; the detailed explanation of this algorithm is described in the corresponding section of [Fenwick Tree](../ds/fenwick.md#global-inversion-pairs-global-2d-partial-order). Reference implementations for both algorithms are in the [Inversion Pair](../math/permutation.md#inversion-count) section.

## External Links

-   [Merge Sort - GeeksforGeeks](https://www.geeksforgeeks.org/merge-sort/)
-   [Merge Sort - Wikipedia, the free encyclopedia](https://en.wikipedia.org/wiki/Merge_sort)
-   [Inversion Pair - Wikipedia, the free encyclopedia](https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics))