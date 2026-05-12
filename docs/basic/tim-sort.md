This page introduces Timsort, a hybrid, stable sorting algorithm.

## Introduction

Timsort was designed by Tim Peters, a Python core developer, in 2002 and applied to the Python language. It cleverly combines the advantages of insertion sort and merge sort, with precise optimization for the orderedness in the dataset, making it especially suitable for processing datasets containing many partially ordered subsequences. Since Python 2.3, Timsort has been chosen as the default sorting algorithm in Python's standard library and has been widely used in other programming environments, such as sorting non-primitive object arrays in Java SE 7.

## Steps

The core idea of Timsort is to improve sorting efficiency by identifying and utilizing the existing order in the dataset. It mainly includes the following steps:

1.  **Identify Run**: Scan the array to be sorted and identify ordered contiguous subsequences (Runs).
2.  **Extend Run**: If the identified Run length is less than `MIN_RUN`, use insertion sort to extend it.
3.  **Merge Run**: Timsort maintains a special stack and uses a specific merge strategy to combine existing Runs in the stack into larger ordered sequences.

### Identifying Run

First, Timscan scans the array from left to right to identify contiguous ordered sequences, which are called Runs:

-   **Ascending Run**: If the next element is greater than or equal to the previous element, continue extending the Run.
-   **Descending Run**: If the next element is less than the previous element, continue extending the Run, then reverse this Run to ascending order.

### Extending Run

To improve sorting efficiency for small-scale data, Timsort introduces a minimum Run length `MIN_RUN`. Its value is usually calculated dynamically based on the length of the array to be sorted, typically between $32$ and $64$.

-   If the identified Run length is greater than or equal to `MIN_RUN`, no additional operation is needed, and the Run is directly pushed onto the stack.
-   If the identified Run length is less than `MIN_RUN`, use binary insertion sort to insert subsequent elements into the Run until the Run length reaches `MIN_RUN`, then push it onto the stack.

### Merging Run

In Timsort, merge sort is managed and controlled through a **stack**. The stack saves the identified ordered Runs and controls the merging of Runs in the stack through specific merge rules, with the goal of maintaining balance and stability during merging.

#### Merge Rules

Timsort is a stable sorting algorithm, meaning equal elements maintain their original relative order after sorting. To ensure this, Timsort only merges adjacent, consecutive Runs during merging, and does not directly merge non-adjacent Runs. Because there may be equal elements between non-adjacent Runs, directly merging them may disrupt their relative order.

At the same time, to ensure balanced merging, Timsort introduces specific merge rules. Before each merge operation, the algorithm checks the three Runs X, Y, and Z at the top of the stack to ensure the following two conditions are met:

-   **Condition one**: `len(Z) > len(Y) + len(X)`
-   **Condition two**: `len(Y) > len(X)`

If the three Runs at the top of the stack do not meet the above conditions, Timsort merges Y with the smaller of X or Z, then checks the conditions again. Once the conditions are met, it continues searching for new Runs, adds them to the stack, and starts the next round of merging.

![Merge Rules](./images/tim-sort-1.png)

#### Merge Optimization

To improve efficiency and reduce space overhead when merging Runs of different lengths, Timsort precisely locates the range of elements to process through binary search before merging, only merging the parts that need to be moved:

1.  **Determine insertion points**: Use binary search to find the insertion position of the first element of the second Run in the first Run, and the insertion position of the last element of the first Run in the second Run. This allows reducing the merge range to only process elements that need to be moved.

2.  **Temporary buffer**: Traditional in-place merge algorithms are too inefficient and require a large amount of element movement. To reduce this overhead, Timsort uses a temporary buffer, copying the shorter Run into the buffer, then gradually copying elements from the buffer back to the original array.

For example, suppose there are two Runs A and B:

-   Run A: $[1, 2, 3, 6, 10]$
-   Run B: $[4, 5, 7, 9, 12, 14, 17]$

Through binary search, it can be determined that:

-   Element $4$ should be inserted at the fourth position of Run A.
-   Element $10$ should be inserted at the fifth position of Run B.

Therefore, the first $3$ elements of Run A and the last $3$ elements of Run B are already in the correct positions and do not need processing. Only Run A's $[6, 10]$ and Run B's $[4, 5, 7, 9]$ need to be merged, as shown in the figure below:

![Timsort Merge](./images/tim-sort-2.apng)

#### Galloping Mode

To further improve merging efficiency, Timsort introduces **Galloping Mode**. In the standard merge process, the algorithm compares elements in both Runs one by one, placing the smaller element into the result array. However, if one Run has many consecutive elements that are smaller than the current element of the other Run, performing one-by-one comparisons would cause unnecessary overhead.

To solve this problem, Timsort sets a threshold `Min_Gallop` (default value is $7$). When the number of consecutive winning comparisons from one Run reaches `Min_Gallop`, the algorithm enters galloping mode to quickly locate element positions:

1.  **Exponential search**: Starting from the current position, the algorithm searches in one Run with exponentially growing step sizes $(1, 2, 4, 8, \dots)$ until an interval is found such that the target element is within that interval.
2.  **Binary search**: Once the interval containing the target element is determined, the algorithm uses binary search within that interval to precisely locate the target element's position.

Through this method, Timskip can skip a large number of unnecessary comparisons, quickly process consecutive smaller (or larger) elements from one Run, and batch move them to the merged result.

However, galloping mode is not always more efficient. In some data distributions, galloping mode may lead to more comparisons. Therefore, Timsort adopts a dynamic adjustment strategy:

-   **Threshold adjustment**: Maintain a variable `Min_Gallop` parameter. When galloping mode performs well (i.e., consecutively selecting elements from the same Run multiple times), `Min_Gallop` is decremented by $1$, encouraging continued use of galloping mode; when galloping mode performs poorly (frequently switching between two Runs), `Min_Gallop` is incremented by $1$, reducing the frequency of galloping mode usage.

By dynamically adjusting the value of `Min_Gallop`, the algorithm can balance between normal merge mode and galloping mode based on actual data. For partially ordered or highly ordered data, galloping mode can significantly improve efficiency, making Timsort's performance close to $O(n)$; for random data, the algorithm gradually tends to use normal merging, thus guaranteeing $O(n \log n)$ time complexity.

## Complexity

Timsort's time complexity depends on the orderliness of the data:

-   **Best case**: $O(n)$
    -   When the data is already ordered or nearly ordered, the Run lengths identified by the algorithm approach $n$, the number of merges decreases, and complexity approaches $O(n)$.
-   **Worst case**: $O(n \log n)$
    -   When the data is completely unordered, each Run's length approaches $1$, so $O(\log n)$ merges are needed, each merge costs $O(n)$, and the total complexity is $O(n \log n)$.

**Proof**:

-   **Identifying and extending Runs**:
    -   Identifying Runs requires one linear traversal of the array, with complexity $O(n)$.
    -   Using insertion sort to extend Runs also requires linear traversal of the array, with complexity $O(n)$.

-   **Merging Runs**:
    -   The total number of merge operations is related to the total number of Runs. In the worst case, the number of Runs is `n / MIN_RUN`. Since `MIN_RUN` is a constant, the number of Runs can be considered $O(n)$.
    -   $O(n)$ Runs require $O(\log n)$ merges, and each merge operation costs $O(n)$, so the total complexity of merge operations is $O(n \log n)$.

For space complexity, since Timsort requires approximately $O(n)$ additional space for storing the stack and temporary buffers, the total space complexity is $O(n)$.

## Implementation

???+ note "Pseudocode implementation"
    $$
    \begin{array}{ll}
    1 & nRemaining \gets \text{array length} \\
    2 & minRun \gets \text{choose appropriate MinRun value}(nRemaining) \\
    3 & startIndex \gets 0 \\
    4 & \textbf{while } nRemaining > 0 \ \textbf{do} \\
    5 & \qquad runLength \gets \text{identify Run }(array, startIndex, nRemaining) \\
    6 & \qquad \textbf{if } runLength < minRun \ \textbf{then} \\
    7 & \qquad \qquad extendLength \gets \min(minRun, nRemaining) \\
    8 & \qquad \qquad \text{use insertion sort to extend range } [startIndex, startIndex + extendLength - 1]\\
    9 & \qquad \qquad runLength \gets extendLength \\
    10 & \qquad \textbf{end if} \\
    11 & \text{push Run } (startIndex, runLength) \text{ onto stack} \\
    12 & \textbf{call } \text{mergeCollapse(stack)} \ \text{check and merge Runs in the stack} \\
    13 & \qquad startIndex \gets startIndex + runLength \ \text{update start position} \\
    14 & \qquad nRemaining \gets nRemaining - runLength \ \text{update remaining length} \\
    15 & \textbf{end while} \\
    16 & \textbf{call } \text{mergeForceCollapse(stack)} \ \text{final merge of all Runs in the stack} \\
    \end{array}
    $$

## References

1.  [Timsort](https://en.wikipedia.org/wiki/Timsort)
2.  [On the Worst-Case Complexity of TimSort](https://drops.dagstuhl.de/opus/volltexte/2018/9467/pdf/LIPIcs-ESA-2018-4.pdf)
3.  [Original Explanation by Tim Peters](https://github.com/python/cpython/blob/main/Objects/listsort.txt)
4.  [Java Implementation](https://cs.android.com/android/platform/superproject/main/+/main:libcore/ojluni/src/main/java/java/util/TimSort.java)
5.  [C Implementation](https://github.com/python/cpython/blob/main/Objects/listobject.c)