This page will briefly introduce sorting algorithms.

## Definition

**Sorting algorithm** (English: Sorting algorithm) is an algorithm that arranges a set of specific data in a certain order. There are many types of sorting algorithms, and their properties also vary greatly.

## Properties

### Stability

Stability refers to whether the relative order of equal elements changes after sorting.

An algorithm with the stability property will maintain the relative order of records with equal keys. That is, if a sorting algorithm is stable, and there are two records $R$ and $S$ with equal keys, and $R$ appears before $S$ in the original list, then $R$ will also be before $S$ in the sorted list.

Radix sort, counting sort, insertion sort, bubble sort, and merge sort are stable sorts.

Selection sort, heap sort, quicksort, and shell sort are not stable sorts.

### Time Complexity

Main page: [Complexity](./complexity.md)

Time complexity measures the relationship between an algorithm's running time and input size, usually expressed using $O$.

A simple method to calculate complexity is to count the number of "simple operations" executed, and sometimes you can estimate it by counting the number of nested loops.

Time complexity includes best-case time complexity, average-case time complexity, and worst-case time complexity. In OI competitions, the worst-case time complexity is usually what needs to be considered, as it represents the lower bound of the algorithm's performance and no worse results will appear during judging.

The lower bound of time complexity for comparison-based sorting algorithms is $O(n\log n)$.

There are also algorithms that are not $O(n\log n)$. For example, [counting sort](./counting-sort.md) has a time complexity of $O(n+w)$, where $w$ represents the range of input values.

The following is a comparison of several sorting algorithms.

![Comparison of several sorting algorithms](images/sort-intro-1.apng)

### Space Complexity

Similar to time complexity, space complexity describes the scale of an algorithm's space consumption. Generally, the smaller the space complexity, the better the algorithm.

## External Links

-   [Sorting algorithm - Wikipedia, the free encyclopedia](https://en.wikipedia.org/wiki/Sorting_algorithm)