This page provides a brief introduction to sorting algorithms implemented in the C and C++ standard libraries.

Except where noted, all functions described on this page are defined in the `<algorithm>` header.

## qsort

See: [`qsort`](https://en.cppreference.com/w/c/algorithm/qsort), [`std::qsort`](https://en.cppreference.com/w/cpp/algorithm/qsort)

This function implements [quicksort](./quick-sort.md) as part of the C standard library, defined in `<stdlib.h>`. In the C++ standard library, it is defined in `<cstdlib>`.

### Comparison function for qsort and bsearch

The qsort function takes four parameters: array name, number of elements, element size, and comparison rule. The comparison rule is implemented by specifying a comparison function; different comparison functions can achieve different sorting rules.

The comparison function's parameters are constrained to two `const void` type pointers. The return value must be a positive number, negative number, or zero.

An example of a comparison function:

```c
int compare(const void *p1, const void *p2)  // comparison function for int array
{
  int *a = (int *)p1;
  int *b = (int *)p2;
  if (*a > *b)
    return 1;  // return positive to indicate a is greater than b
  else if (*a < *b)
    return -1;  // return negative to indicate a is less than b
  else
    return 0;  // return 0 to indicate a and b are equivalent
}
```

Note: Using the difference of two elements to represent positive/negative values is a typical error, as it may cause overflow errors.

Here is an example of sorting a struct:

```c
struct eg  // example struct
{
  int e;
  int g;
};

int compare(const void *p1,
            const void *p2)  // comparison function for struct eg array: sort by member e
{
  struct eg *a = (struct eg *)p1;
  struct eg *b = (struct eg *)p2;
  if (a->e > b->e)
    return 1;  // return positive to indicate a is greater than b
  else if (a->e < b->e)
    return -1;  // return negative to indicate a is less than b
  else
    return 0;  // return 0 to indicate a and b are equivalent
}
```

As you can see, equivalence does not mean equality; it only means the two elements are equivalent under this comparison rule.

## std::sort

See: [`std::sort`](https://en.cppreference.com/w/cpp/algorithm/sort)

Usage:

```cpp
// a[0] .. a[n - 1] is the sequence to be sorted
// sorts a in-place, arranging elements in ascending order
std::sort(a, a + n);

// cmp is a custom comparison function
std::sort(a, a + n, cmp);
```

Note: The comparison function for sort returns true and false, using true and false to indicate the size (order) relationship between two elements, which is completely different from the semantics of qsort's three-value comparison function. See the sort documentation linked above for details.

If you want to simply convert sort to qsort while maintaining the overall sorting order (ignoring equivalent elements), you need to change returning true to -1 and returning false to 1.

`std::sort` is the more commonly used C++ library comparison function. Its last parameter is a binary comparison function; if no `cmp` function is specified, it sorts in ascending order by default.

In older C++ standards, it was only required to achieve **average** time complexity of $O(n\log n)$. C++11 and subsequent standards require **worst-case** time complexity of $O(n\log n)$.

The C++ standard does not strictly mandate the implementation algorithm for this function; the specific implementation depends on the compiler. Both [libstdc++](https://github.com/mirrors/gcc/blob/master/libstdc++-v3/include/bits/stl_algo.h) and [libc++](http://llvm.org/svn/llvm-project/libcxx/trunk/include/algorithm) implementations use [Introsort](./quick-sort.md#introsort).

## std::nth_element

See: [`std::nth_element`](https://en.cppreference.com/w/cpp/algorithm/nth_element)

Usage:

```cpp
std::nth_element(first, nth, last);
std::nth_element(first, nth, last, cmp);
```

It rearranges elements in `[first, last)` such that the element pointed to by `nth` is changed to whatever element would appear in that position if the range were fully sorted. All elements before this new `nth` are less than or equal to all elements after it.

The implementation algorithm is an incomplete introsort.

For both usages above, the C++ standard requires an average time complexity of $O(n)$, where n is `std::distance(first, last)`.

It is commonly used for building [K-D Trees](../ds/kdt.md).

## std::stable_sort

See: [`std::stable_sort`](https://en.cppreference.com/w/cpp/algorithm/stable_sort)

Usage:

```cpp
std::stable_sort(first, last);
std::stable_sort(first, last, cmp);
```

Stable sorting, which preserves the relative order of equal elements in the sorted output as they were in the original sequence.

Time complexity is $O(n\log^2 n)$; when extra memory is available, complexity is $O(n\log n)$.

## std::partial_sort

See: [`std::partial_sort`](https://en.cppreference.com/w/cpp/algorithm/partial_sort)

Usage:

```cpp
// mid = first + k
std::partial_sort(first, mid, last);
std::partial_sort(first, mid, last, cmp);
```

Sorts the first `k` elements of the range in ascending order according to `cmp`, leaving the remaining elements in an unspecified order. If no `cmp` function is specified, it sorts in ascending order by default.

Complexity: approximately $(\mathit{last}-\mathit{first})\log(\mathit{mid}-\mathit{first})$ applications of `cmp`.

Principle:

`std::partial_sort` works by: constructing a max-heap from elements in `[first, mid)` using `make_heap()`, then comparing each element in `[mid, last)` with `first` to ensure the elements in `[first, mid)` are the largest in the heap. If an element is smaller than the maximum, swap them and adjust `[first, mid)` to maintain the max-heap property. After all comparisons, perform a heap sort (`sort_heap()`) on `[first, mid)` to arrange elements in ascending order. Note that heap order and ascending order are different.

## Custom Comparison

See: [operator overloading](https://en.cppreference.com/w/cpp/language/operators)

Built-in types (such as `int`) and user-defined structs allow customization of the comparison function used when calling STL sorting functions. You can pass a binary comparison function as the last parameter when calling the function.

For user-defined structs, you must define at least one relational operator before using STL sorting functions, or provide a binary comparison function when using the function. It is generally recommended to define `operator<`.[^note1]

Example:

```cpp
int a[1009], n = 10;
// ...
std::sort(a + 1, a + 1 + n);                  // sort in ascending order
std::sort(a + 1, a + 1 + n, greater<int>());  // sort in descending order
```

```cpp
struct data {
  int a, b;

  bool operator<(const data rhs) const {
    return (a == rhs.a) ? (b < rhs.b) : (a < rhs.a);
  }
} da[1009];

bool cmp(const data u1, const data u2) {
  return (u1.a == u2.a) ? (u1.b > u2.b) : (u1.a > u2.a);
}

// ...
std::sort(da + 1, da + 1 + 10);  // use the < operator defined in the struct, sort in ascending order
std::sort(da + 1, da + 1 + 10, cmp);  // use cmp function, sort in descending order
```

### Strict Weak Ordering

See also: [Application in C++ - Order Theory](../math/order-theory.md#application-in-c)

The operator used for sorting must satisfy [strict weak ordering](../math/order-theory.md#binary-relation), otherwise unexpected behavior may occur (such as runtime errors or incorrect sorting).

Common mistakes:

-   Using `<=` to define the less-than operator in sorting.
-   Reading external values that may change during comparison calls (common in shortest path algorithms).
-   Using the result of comparing the maximum and minimum of multiple numbers as the sorting operator (a classic error in problems like "Queen's Game / Production Scheduling").

## External Links

-   [A Brief Discussion on the Application of Adjacent Swap Sorting and Issues to Note](https://ouuan.github.io/浅谈邻项交换排序的应用以及需要注意的问题/)

## References and Notes

[^note1]: Because most standard algorithms use `operator<` for comparison by default.