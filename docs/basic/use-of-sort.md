This page will briefly introduce the usage of sorting.

## Understanding Data Characteristics

Using sorting to process data helps understand the characteristics of the data, making subsequent analysis and visualization easier. Similar real-life examples include dictionaries and menus—if not arranged in a certain order, the time people need to find what they need would greatly increase.

Computers need to handle large-scale data. After sorting, people can design subsequent processing workflows for the computer based on the characteristics and requirements of the data.

## Reducing Time Complexity

Using sorting as preprocessing can reduce the time complexity needed to solve a problem, usually trading space for time. If a sorted list needs to be analyzed multiple times, spending resources on sorting only once is very cost-effective, as each subsequent analysis can save a lot of time.

???+ note "Example: Checking whether there are equal elements in a given sequence"
    Consider a sequence, and you need to check whether any elements are equal.

    A naive approach is to check every pair of numbers and determine whether the pair is equal. The time complexity is $O(n^2)$.

    Let's sort the sequence first. It's not hard to find that if two numbers are equal, they must be adjacent to each other in the new sequence. Then we only need to scan through the new sequence in $O(n)$ time.

    The total time complexity is the complexity of sorting, $O(n\log n)$.

## As Preprocessing for Searching

Sorting is the preprocessing work for [binary search](./binary.md). After sorting, using binary search allows finding a specified element in the sequence in $O(\log n)$ time.