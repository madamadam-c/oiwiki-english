Prerequisites: [Prefix Sum](./prefix-sum.md)

???+ warning "Note"
    This page is not about [**Radix Sort**](./radix-sort.md).

This page gives a brief introduction to counting sort.

## Definition

Counting sort (English: Counting sort) is a linear-time sorting algorithm.

## Process

The working principle of counting sort is to use an additional array $C$, where the $i$-th element is the number of elements in the array $A$ to be sorted whose value equals $i$, and then use the array $C$ to place the elements in $A$ in their correct positions.[^ref1]

Its working process consists of three steps:

1.  Count how many times each number appears;
2.  Compute the [prefix sum](./prefix-sum.md) of the occurrence counts of each number;
3.  Use the prefix sums of the occurrence counts to compute the rank of each number from right to left.

### Why Compute Prefix Sums

Simply placing the elements corresponding to positive values in $C$ into $A$ in order cannot handle the case of duplicate elements.

By computing the prefix sum for each entry in the additional array $C$, and combining it with the value of each entry, we can assign a unique rank to duplicate elements.

The value of each entry in the additional array $C$ represents the number of duplicate elements for that key value, and the prefix sum of that entry represents the rank of the last duplicate element.

If we sort in the reverse order of $A$, then the sorted array will clearly preserve the original order of $A$ (for elements with the same key value), which yields a stable sorting algorithm.

![counting sort animate example](images/counting-sort-animate.svg)

## Properties

### Stability

Counting sort is a stable sorting algorithm.

### Time Complexity

The time complexity of counting sort is $O(n+w)$, where $w$ represents the range of values in the input data.

## Code Implementation

### Pseudocode

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{An array } A \text{ consisting of }n\text{ positive integers no greater than } w. \\
2 & \textbf{Output. } \text{Array }A\text{ after sorting in nondecreasing order stably.} \\
3 & \textbf{Method. }  \\
4 & \textbf{for }i\gets0\textbf{ to }w\\
5 & \qquad \textit{cnt}[i]\gets0\\
6 & \textbf{for }i\gets1\textbf{ to }n\\
7 & \qquad \textit{cnt}[A[i]]\gets\textit{cnt}[A[i]]+1\\
8 & \textbf{for }i\gets1\textbf{ to }w\\
9 & \qquad \textit{cnt}[i]\gets \textit{cnt}[i]+\textit{cnt}[i-1]\\
10 & \textbf{for }i\gets n\textbf{ downto }1\\
11 & \qquad B[\textit{cnt}[A[i]]]\gets A[i]\\
12 & \qquad \textit{cnt}[A[i]]\gets \textit{cnt}[A[i]]-1\\
13 & \textbf{return } B
\end{array}
$$

=== "C++"
    ```cpp
    --8<-- "docs/basic/code/counting-sort/counting-sort_1.cpp"
    ```

=== "Python"
    ```python
    --8<-- "docs/basic/code/counting-sort/counting-sort_1.py:core"
    ```

## References and Footnotes

[^ref1]: [Counting sort - Wikipedia, the free encyclopedia](https://en.wikipedia.org/wiki/Counting_sort)
