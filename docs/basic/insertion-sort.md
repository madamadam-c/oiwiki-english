This page gives a brief introduction to insertion sort.

## Definition

Insertion sort (English: Insertion sort) is a simple and intuitive sorting algorithm. Its working principle is to divide the elements to be sorted into "sorted" and "unsorted" parts, and each time select an element from the "unsorted" part and insert it into the correct position in the "sorted" part.

An identical operation to insertion sort is when playing card games: you pick up a card from the table and insert it into your hand in the correct position based on its value, then pick up the next card.

![insertion sort animate example](images/insertion-sort-animate.svg)

## Properties

### Stability

Insertion sort is a stable sorting algorithm.

### Time Complexity

The optimal time complexity of insertion sort is $O(n)$, and it is very efficient when the sequence is nearly sorted.

The worst-case and average time complexity of insertion sort are both $O(n^2)$.

## Code Implementation

### Pseudocode

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{An array } A \text{ consisting of }n\text{ elements.} \\
2 & \textbf{Output. } A\text{ will be sorted in nondecreasing order stably.} \\
3 & \textbf{Method. }  \\
4 & \textbf{for } i\gets 2\textbf{ to }n\\
5 & \qquad key\gets A[i]\\
6 & \qquad j\gets i-1\\
7 & \qquad\textbf{while }j>0\textbf{ and }A[j]>key\\
8 & \qquad\qquad A[j + 1]\gets A[j]\\
9 & \qquad\qquad j\gets j - 1\\
10 & \qquad A[j + 1]\gets key
\end{array}
$$

=== "C++"
    ```cpp
    --8<-- "docs/basic/code/insertion-sort/insertion-sort_1.cpp"
    ```

=== "Python"
    ```python
    --8<-- "docs/basic/code/insertion-sort/insertion-sort_1.py:core"
    ```

=== "Java"
    ```java
    --8<-- "docs/basic/code/insertion-sort/insertion-sort_1.java"
    ```

## Binary Insertion Sort

Insertion sort can also be optimized using binary search, and the optimization effect is more significant when sorting a larger number of elements.

### Time Complexity

Binary insertion sort follows the same basic idea as straight insertion sort. Binary insertion sort only optimizes the constant factor in the time complexity of insertion sort, so the overall time complexity remains unchanged.

### Code Implementation

=== "C++"
    ```cpp
    void insertion_sort(int arr[], int len) {
      if (len < 2) return;
      for (int i = 1; i != len; ++i) {
        int key = arr[i];
        auto index = upper_bound(arr, arr + i, key) - arr;
        // Use memmove to move elements, faster than a for loop, time complexity is still O(n)
        memmove(arr + index + 1, arr + index, (i - index) * sizeof(int));
        arr[index] = key;
      }
    }
    ```
