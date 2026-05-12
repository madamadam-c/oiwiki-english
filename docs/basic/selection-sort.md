This page will briefly introduce selection sort.

## Definition

Selection sort (English: Selection sort) is a simple and intuitive sorting algorithm. Its working principle is to find the $i$-th smallest element (that is, the smallest element in $A_{i..n}$) each time, and then swap this element with the element at position $i$ in the array.

![selection sort animate example](images/selection-sort-animate.svg)

## Properties

### Stability

The stability of selection sort depends on its specific implementation.

If implemented using a linked list, since inserting and deleting at any position in a linked list are both $O(1)$, there is no need to use swap (swapping two elements) operations: each time after selecting the smallest element from the unsorted part (if there are multiple, select the first one), insert it before the first element of the unsorted part, which can guarantee stability.

If implemented using an array (the usual implementation in OI), since inserting and deleting at any position in an array are both $O(n)$, we can only use swap to move elements from the unsorted part to the sorted part. The swap operation makes the array implementation of selection sort unstable.

All the implementation examples given below are based on swapping array elements, so they are all **unstable**.

### Time Complexity

The optimal time complexity, average time complexity, and worst-case time complexity of selection sort are all $O(n^2)$.

## Implementation

### Pseudocode

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{An array } A \text{ consisting of }n\text{ elements.} \\
2 & \textbf{Output. } A\text{ will be sorted in nondecreasing order.} \\
3 & \textbf{Method. }  \\
4 & \textbf{for } i\gets 1\textbf{ to }n-1\\
5 & \qquad ith\gets i\\
6 & \qquad \textbf{for }j\gets i+1\textbf{ to }n\\
7 & \qquad\qquad\textbf{if }A[j]<A[ith]\\
8 & \qquad\qquad\qquad ith\gets j\\
9 & \qquad \text{swap }A[i]\text{ and }A[ith]\\
\end{array}
$$

=== "C++"
    ```cpp
    --8<-- "docs/basic/code/selection-sort/selection-sort_1.cpp"
    ```

=== "Python"
    ```python
    --8<-- "docs/basic/code/selection-sort/selection-sort_1.py:core"
    ```

=== "Java"
    ```java
    // arr code index starts from 1
    static void selection_sort(int[] arr, int n) {
        for (int i = 1; i < n; i++) {
            int ith = i;
            for (int j = i + 1; j <= n; j++) {
                if (arr[j] < arr[ith]) {
                    ith = j;
                }
            }
            // swap
            int temp = arr[i];
            arr[i] = arr[ith];
            arr[ith] = temp;
        }
    }
    ```