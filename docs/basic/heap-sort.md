This page briefly introduces heap sort.

## Definition

Heapsort (English: Heapsort) is a sorting algorithm that uses the data structure of [binary heap](../ds/binary-heap.md). The applicable data structure for heapsort is an array.

## Process

The essence of heapsort is selection sort based on a heap.

### Sorting

First, build a max heap, then take out the element at the root as the maximum value, swap it with the element at the end of the array, and maintain the property of the remaining heap;

Then take out the element at the root as the second largest value, swap it with the second-to-last element of the array, and maintain the property of the remaining heap;

And so on, after $n-1$ operations, the entire array is sorted.

### Building a Binary Heap on an Array

Starting from the root node, arrange the nodes of each level in the array in order.

Thus, for a node with index `i` in the array, its parent, left child, and right child are as follows:

```cpp
iParent(i) = (i - 1) / 2;
iLeftChild(i) = 2 * i + 1;
iRightChild(i) = 2 * i + 2;
```

## Properties

### Stability

Like selection sort, it is an unstable sorting algorithm due to the swapping of positions.

### Time Complexity

The optimal time complexity, average time complexity, and worst-case time complexity of heapsort are all $O(n\log n)$.

### Space Complexity

Since the heap can be built on the input array, this is an in-place algorithm.

## Implementation

=== "C++"
    ```cpp
    void sift_down(int arr[], int start, int end) {
      // Calculate indices of parent and child nodes
      int parent = start;
      int child = parent * 2 + 1;
      while (child <= end) {  // Only compare when child index is in range
        // First compare the two children, choose the larger one
        if (child + 1 <= end && arr[child] < arr[child + 1]) child++;
        // If parent is larger than child, adjustment is done, exit the function
        if (arr[parent] >= arr[child])
          return;
        else {  // Otherwise swap parent and child, then compare child with grandchild
          swap(arr[parent], arr[child]);
          parent = child;
          child = parent * 2 + 1;
        }
      }
    }
    
    void heap_sort(int arr[], int len) {
      // Start from the parent of the last node and sift down to complete heapify
      for (int i = (len - 1 - 1) / 2; i >= 0; i--) sift_down(arr, i, len - 1);
      // First swap the first element with the element before the sorted portion, then readjust (elements before the just adjusted element) until sorted
      for (int i = len - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        sift_down(arr, 0, i - 1);
      }
    }
    ```

=== "Python"
    ```python
    def sift_down(arr, start, end):
        # Calculate indices of parent and child nodes
        parent = int(start)
        child = int(parent * 2 + 1)
        while child <= end:  # Only compare when child index is in range
            # First compare the two children, choose the larger one
            if child + 1 <= end and arr[child] < arr[child + 1]:
                child += 1
            # If parent is larger than child, adjustment is done, exit the function
            if arr[parent] >= arr[child]:
                return
            else:  # Otherwise swap parent and child, then compare child with grandchild
                arr[parent], arr[child] = arr[child], arr[parent]
                parent = child
                child = int(parent * 2 + 1)
    
    
    def heap_sort(arr, len):
        # Start from the parent of the last node and sift down to complete heapify
        i = (len - 1 - 1) / 2
        while i >= 0:
            sift_down(arr, i, len - 1)
            i -= 1
        # First swap the first element with the element before the sorted portion, then readjust (elements before the just adjusted element) until sorted
        i = len - 1
        while i > 0:
            arr[0], arr[i] = arr[i], arr[0]
            sift_down(arr, 0, i - 1)
            i -= 1
    ```

## External Links

-   [Heapsort - Wikipedia, the free encyclopedia](https://en.wikipedia.org/wiki/Heapsort)