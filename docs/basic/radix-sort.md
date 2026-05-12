???+ warning "Note"
    This page is not about [**counting sort**](./counting-sort.md).

This page will briefly introduce radix sort.

## Definition

Radix sort is a non-comparison-based sorting algorithm, first used to solve card sorting problems. Radix sort decomposes the elements to be sorted into $k$ keys, and completes the sorting of all elements by sorting each key sequentially.

If comparing from the 1st key to the $k$-th key in order, this radix sort is called MSD (Most Significant Digit first) radix sort.

If comparing from the $k$-th key to the 1st key in order, this radix sort is called LSD (Least Significant Digit first) radix sort.

## Comparing k-Key Elements

Below, $a_i$ is used to denote the $i$-th key of element $a$.

Suppose an element has $k$ keys. For two elements $a$ and $b$, the default comparison method is:

-   Compare the 1st keys of the two elements, $a_1$ and $b_1$. If $a_1 < b_1$, then $a < b$; if $a_1 > b_1$, then $a > b$; if $a_1 = b_1$, proceed to the next step.
-   Compare the 2nd keys of the two elements, $a_2$ and $b_2$. If $a_2 < b_2$, then $a < b$; if $a_2 > b_2$, then $a > b$; if $a_2 = b_2$, proceed to the next step.
-   ……
-   Compare the $k$-th keys of the two elements, $a_k$ and $b_k$. If $a_k < b_k$, then $a < b$; if $a_k > b_k$, then $a > b$; if $a_k = b_k$, then $a = b$.

Examples:

-   If comparing natural numbers, align natural numbers by their units digit and pad with $0$ towards higher digits. The $i$-th digit from the left can be used as the $i$-th key.
-   If comparing strings based on lexicographical order, the $i$-th character from the left can be used as the $i$-th key.
-   C++'s built-in `std::pair` and `std::tuple` use the same default comparison method as described above.

## MSD Radix Sort

Based on the k-key element comparison method, one can think: by first comparing the 1st keys of all elements, the approximate size relationship of each element can be determined; then for **elements with the same 1st key**, compare their 2nd keys, and so on.

Since comparisons proceed from the 1st key to the $k$-th key, the sorting algorithm derived from this idea is called MSD (Most Significant Digit first) radix sort.

### Algorithm Process

Decompose the elements to be sorted into $k$ keys. First, perform a stable sort by the 1st key. Then, for each group **with the same key**, perform a stable sort by the 2nd key (recursively). … Finally, for each group **with the same key**, perform a stable sort by the $k$-th key.

Generally, we assume radix sort is stable. Therefore, in MSD radix sort, we only consider using a **stable algorithm** (usually counting sort) to complete the inner key sorting.

For correctness, refer to the k-key element comparison above.

### Reference Code

#### Sorting Natural Numbers

Below is C++ reference code for sorting elements within the `unsigned int` range using iterative MSD radix sort. Values of $W$ and $\log_2 W$ can be adjusted (it is recommended to set $\log_2 W$ to $2^k$ for bitwise optimization).

??? example "Reference Code"
    ```cpp
    --8<-- "docs/basic/code/radix-sort/radix-sort_1.cpp:core"
    ```

#### Sorting Strings

Below is C++ reference code for sorting null-terminated byte strings using iterative MSD radix sort based on lexicographical order:

??? example "Reference Code"
    ```cpp
    --8<-- "docs/basic/code/radix-sort/radix-sort_2.cpp:core"
    ```

Since comparing two strings can easily reach $O(n)$ linear complexity, for string sorting, MSD radix sort outperforms most comparison-based sorting algorithms in both time complexity and actual execution time.

### Relationship with Bucket Sort

Prerequisite: [Bucket Sort](./bucket-sort.md)

Bucket sort requires other sorting algorithms to complete the sorting of elements within each bucket. However, it is entirely possible to continue performing bucket sort on each bucket until the number of elements in a bucket becomes $\le 1$.

Therefore, another way to understand MSD radix sort is: bucket sort implemented using bucket sort.

Consequently, an optimization method for the time constant in MSD radix sort can be proposed: if at some step the number of elements in a bucket is $\le B$ (where $B$ is a constant of your choosing), directly perform insertion sort and return, reducing the number of recursive calls.

## LSD Radix Sort

MSD radix sort compares from the 1st key to the $k$-th key. For this, recursion or iteration is needed, and the time constant is still relatively large. It is also somewhat inconvenient for comparing natural numbers.

Reversing the recursive operation: comparing from the $k$-th key to the 1st key in order yields LSD (Least Significant Digit first) radix sort, a sorting algorithm that can be completed without recursion.

### Algorithm Process

Decompose the elements to be sorted into $k$ keys. First, perform a stable sort of **all elements** by the $k$-th key, then perform a stable sort of **all elements** by the $k-1$-th key, then by the $k-2$-th key, … Finally, perform a stable sort of **all elements** by the 1st key. This completes the stable sorting of the entire sequence.

![An example of the full LSD radix sort process](images/radix-sort-1.png "An example of the full LSD radix sort process")

LSD radix sort also requires a **stable algorithm** to complete the inner key sorting. Similarly, counting sort is usually used.

The correctness of LSD radix sort can be found in the solution to Problem 8.3-3 in [Introduction to Algorithms (3rd Edition)](https://walkccc.github.io/CLRS/Chap08/8.3/#83-3), or see the explanation below:

### Correctness

Reviewing the k-key element comparison method:

-   If you want to determine the size of two elements $a$ and $b$ by just comparing $a_1$ and $b_1$, you need to know the conclusion obtained from comparing $a_2$ and $b_2$ in advance, to handle the case where $a_1 = b_1$.
-   If you want to determine the size of two elements $a$ and $b$ by just comparing $a_2$ and $b_2$, you need to know the conclusion obtained from comparing $a_3$ and $b_3$ in advance, to handle the case where $a_2 = b_2$.
-   ……
-   If you want to determine the size of two elements $a$ and $b$ by just comparing $a_{k-1}$ and $b_{k-1}$, you need to know the conclusion obtained from comparing $a_k$ and $b_k$ in advance, to handle the case where $a_{k-1} = b_{k-1}$.
-   $a_k$ and $b_k$ can be compared directly.

Now, reverse the order:

-   $a_k$ and $b_k$ can be compared directly.
-   After knowing the conclusion from comparing $a_k$ and $b_k$, you can obtain the conclusion for comparing $a_{k-1}$ and $b_{k-1}$.
-   ……
-   After knowing the conclusion from comparing $a_2$ and $b_2$, you can obtain the conclusion for comparing $a_1$ and $b_1$.
-   After knowing the conclusion from comparing $a_1$ and $b_1$, you finally obtain the conclusion for comparing $a$ and $b$.

In this process, by comparing and rearranging the order of elements for each key, you get LSD radix sort.

### Pseudocode

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{An array } A \text{ consisting of }n\text{ elements, where each element has }k\text{ keys.}\\
2 & \textbf{Output. } \text{Array }A\text{ will be sorted in nondecreasing order stably.} \\
3 & \textbf{Method. }  \\
4 & \textbf{for }i\gets k\textbf{ down to }1\\
5 & \qquad\text{sort }A\text{ into nondecreasing order by the }i\text{-th key stably}
\end{array}
$$

### Reference Code

Below is the k-key element sorting using LSD radix sort.

??? example "Reference Code"
    ```cpp
    --8<-- "docs/basic/code/radix-sort/radix-sort_lsd.cpp:core"
    ```

In fact, it is not mandatory to enumerate from back to front for stable sorting. An operation on the `cnt` array equivalent to `std::exclusive_scan` is sufficient.

???+ note "Problem [Luogu P1177【Template】Quick Sort](https://www.luogu.com.cn/problem/P1177)"
    Given $n$ positive integers, output them in ascending order.
    
    ```cpp
    #include <algorithm>
    #include <iostream>
    #include <utility>
    
    void radix_sort(int n, int a[]) {
      int *b = new int[n];  // temporary space
      int *cnt = new int[1 << 8];
      int mask = (1 << 8) - 1;
      int *x = a, *y = b;
      for (int i = 0; i < 32; i += 8) {
        for (int j = 0; j != (1 << 8); ++j) cnt[j] = 0;
        for (int j = 0; j != n; ++j) ++cnt[x[j] >> i & mask];
        for (int sum = 0, j = 0; j != (1 << 8); ++j) {
          // equivalent to std::exclusive_scan(cnt, cnt + (1 << 8), cnt, 0);
          sum += cnt[j], cnt[j] = sum - cnt[j];
        }
        for (int j = 0; j != n; ++j) y[cnt[x[j] >> i & mask]++] = x[j];
        std::swap(x, y);
      }
      delete[] cnt;
      delete[] b;
    }
    
    int main() {
      std::ios::sync_with_stdio(false);
      std::cin.tie(nullptr);
      int n;
      std::cin >> n;
      int *a = new int[n];
      for (int i = 0; i < n; ++i) std::cin >> a[i];
      radix_sort(n, a);
      for (int i = 0; i < n; ++i) std::cout << a[i] << ' ';
      delete[] a;
      return 0;
    }
    ```

## Properties

### Stability

If the inner key sorting is stable, then both MSD and LSD radix sort are stable sorting algorithms.

### Time Complexity

Generally speaking, radix sort is faster than comparison-based sorting algorithms (such as quicksort). However, since additional memory space is required, when memory space is scarce, in-place sorting algorithms (such as quicksort) may be a better choice.[^ref1]

Generally, if the range of each key is not large, [counting sort](./counting-sort.md) can be used as the inner sorting, with complexity $O(kn+\sum\limits_{i=1}^k w_i)$, where $w_i$ is the range size of the $i$-th key. If the key range is very large, comparison-based $O(nk\log n)$ sorting can be used directly without using radix sort.

### Space Complexity

Both MSD and LSD radix sort have space complexity $O(k+n)$.

## References and Notes

[^ref1]: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein. *Introduction to Algorithms* (3rd ed.). MIT Press and McGraw-Hill, 2009. ISBN 978-0-262-03384-8. "8.3 Radix sort", pp. 199.
