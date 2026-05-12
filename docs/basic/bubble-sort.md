This page will briefly introduce bubble sort.

## Definition

Bubble sort (English: Bubble sort) is a simple sorting algorithm. Because during the algorithm's execution, smaller elements slowly "float" to the top of the sequence like bubbles, it is called bubble sort.

## Process

Its working principle is to check each pair of adjacent elements each time, and if the preceding element satisfies the given sorting condition with the following element, swap the two adjacent elements. When there are no adjacent elements that need to be swapped, the sorting is complete.

After $i$ scans, the last $i$ items of the array must be the largest $i$ items, so bubble sort needs at most $n-1$ scans of the array to complete sorting.

## Properties

### Stability

Bubble sort is a stable sorting algorithm.

### Time Complexity

When the sequence is completely in order, bubble sort only needs to traverse the array once without performing any swap operations, with a time complexity of $O(n)$.

In the worst case, bubble sort performs $\frac{(n-1)n}{2}$ swap operations, with a time complexity of $O(n^2)$.

The average time complexity of bubble sort is $O(n^2)$.

## Implementation

### Pseudocode

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{An array } A \text{ consisting of }n\text{ elements.} \\
2 & \textbf{Output. } A\text{ will be sorted in nondecreasing order stably.} \\
3 & \textbf{Method. }  \\
4 & flag\gets True\\
5 & \textbf{while }flag\\
6 & \qquad flag\gets False\\
7 & \qquad\textbf{for }i\gets1\textbf{ to }n-1\\
8 & \qquad\qquad\textbf{if }A[i]>A[i + 1]\\
9 & \qquad\qquad\qquad flag\gets True\\
10 & \qquad\qquad\qquad \text{Swap } A[i]\text{ and }A[i + 1]
\end{array}
$$

=== "C++"
    ```cpp
    --8<-- "docs/basic/code/bubble-sort/bubble-sort_1.cpp"
    ```

=== "Python"
    ```python
    --8<-- "docs/basic/code/bubble-sort/bubble-sort_1.py:core"
    ```

=== "Java"
    ```java
    // Suppose the array size is n + 1, bubble sort starts from array index 1
    static void bubble_sort(int[] a, int n) {
        boolean flag = true;
        while (flag) {
            flag = false;
            for (int i = 1; i < n; i++) {
                if (a[i] > a[i + 1]) {
                    flag = true;
                    int t = a[i];
                    a[i] = a[i + 1];
                    a[i + 1] = t;
                }
            }
        }
    }
    ```