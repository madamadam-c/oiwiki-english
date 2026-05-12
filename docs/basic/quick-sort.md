This page briefly introduces quicksort.

## Definition

Quicksort (English: Quicksort), also known as partition-exchange sort, commonly referred to as "quicksort," is a widely used sorting algorithm.

## Principles and Implementation

### Process

Quicksort works by sorting an array using [divide and conquer](./divide-and-conquer.md).

Quicksort consists of three steps:

1.  Divide the sequence into two parts (ensuring relative size order is preserved);
2.  Recursively apply quicksort to both subsequences;
3.  No merging is needed because the sequence is now completely sorted.

Unlike merge sort, the first step does not directly split the sequence into front and back parts. Instead, during the division process, we must ensure relative size order. Specifically, the first step is to divide the sequence into two parts, ensuring that all elements in the first subsequence are smaller than those in the second. To guarantee average time complexity, we typically randomly select a value $m$ as the boundary between the two subsequences.

Then, we maintain two pointers $p$ and $q$ (front and back). We check whether each element is placed in the correct position (front or back). If the current element is misplaced — for example, if the back pointer $q$ encounters a value smaller than $m$ — we can swap the elements at positions $p$ and $q$, then move $p$ forward by one. After all elements are in their correct positions, we continue moving the pointers until they meet.

In fact, quicksort does not specify how to implement the first step. Both the process of selecting $m$ and the partitioning process have multiple possible implementations.

In the third step, both sequences are already sorted, and all elements in the first sequence are smaller than those in the second. So we simply concatenate them.

=== "C++"
    === "Non-recursive Implementation[^ref2]"
        ```cpp
        struct Range {
          int start, end;
        
          Range(int s = 0, int e = 0) { start = s, end = e; }
        };
        
        template <typename T>
        void quick_sort(T arr[], const int len) {
          if (len <= 0) return;
          Range r[len];
          int p = 0;
          r[p++] = Range(0, len - 1);
          while (p) {
            Range range = r[--p];
            if (range.start >= range.end) continue;
            T mid = arr[range.end];
            int left = range.start, right = range.end - 1;
            while (left < right) {
              while (arr[left] < mid && left < right) left++;
              while (arr[right] >= mid && left < right) right--;
              std::swap(arr[left], arr[right]);
            }
            if (arr[left] >= arr[range.end])
              std::swap(arr[left], arr[range.end]);
            else
              left++;
            r[p++] = Range(range.start, left - 1);
            r[p++] = Range(left + 1, range.end);
          }
        }
        ```
    
    === "Recursive Implementation"
        ```cpp
        template <typename T>
        int Partition(T A[], int low, int high) {
          int pivot = A[low];
          while (low < high) {
            while (low < high && pivot <= A[high]) --high;
            A[low] = A[high];
            while (low < high && A[low] <= pivot) ++low;
            A[high] = A[low];
          }
          A[low] = pivot;
          return low;
        }
        
        template <typename T>
        void QuickSort(T A[], int low, int high) {
          if (low < high) {
            int pivot = Partition(A, low, high);
            QuickSort(A, low, pivot - 1);
            QuickSort(A, pivot + 1, high);
          }
        }
        
        template <typename T>
        void QuickSort(T A[], int len) {
          QuickSort(A, 0, len - 1);
        }
        ```

=== "Python[^ref2]"
    ```python
    def quick_sort(alist, first, last):
        if first >= last:
            return
        mid_value = alist[first]
        low = first
        high = last
        while low < high:
            while low < high and alist[high] >= mid_value:
                high -= 1
            alist[low] = alist[high]
            while low < high and alist[low] < mid_value:
                low += 1
            alist[high] = alist[low]
        alist[low] = mid_value
        quick_sort(alist, first, low - 1)
        quick_sort(alist, low + 1, last)
    ```

## Properties

### Stability

Quicksort is an unstable sorting algorithm.

### Time Complexity

The optimal and average time complexity of quicksort is $O(n\log n)$, and the worst-case time complexity is $O(n^2)$.

For the optimal case, every chosen pivot is the median of the sequence. In this case, the algorithm's time complexity satisfies the recurrence $T(n) = 2T(\dfrac{n}{2}) + \Theta(n)$. By the master theorem, $T(n) = \Theta(n\log n)$.

For the worst case, every chosen pivot is either the minimum or maximum of the sequence. In this case, the algorithm's time complexity satisfies the recurrence $T(n) = T(n - 1) + \Theta(n)$. Summing gives $T(n) = \Theta(n^2)$.

For the average case, the pivot can be considered as selected uniformly at random.

??? note "Proof"
    We will prove that in this case the algorithm's time complexity is $O(n\log n)$.
    
    **Lemma 1:** When sorting an array of $n$ elements with quicksort, suppose the total number of comparisons during partitioning is $X$. Then the time complexity of quicksort is $O(n + X)$.
    
    Since a pivot is selected during each partition operation, partitioning occurs at most $n$ times. Since the number of comparisons during partitioning and the number of other basic operations are of the same order of magnitude, the total time complexity is $O(n + X)$.
    
    Let $a_i$ be the $i$-th smallest element in the original array. Define $A_{i,j}$ as $\{ a_i, a_{i+1}, \dots, a_j \}$. $X_{i,j}$ is a discrete random variable taking values $0$ or $1$, indicating whether $a_i$ and $a_j$ are compared during the sorting process.
    
    Obviously, each selected pivot is different, and elements are only compared with the pivot. So the total number of comparisons is
    
    $$
    \begin{aligned} X = \sum \limits _ {i = 1} ^ {n - 1} \sum \limits _ {j = i + 1} ^ n X_{i,j} \end{aligned}
    $$
    
    By linearity of expectation,
    
    $$
    \begin{aligned} E[X] & = E \left[ \sum \limits _ {i = 1} ^ {n - 1} \sum \limits _ {j = i + 1} ^ n X_{i,j} \right] \\ & = \sum \limits _ {i = 1} ^ {n - 1} \sum \limits _ {j = i + 1} ^ n E[X_{i,j}] \\ & = \sum \limits _ {i = 1} ^ {n - 1} \sum \limits _ {j = i + 1} ^ n P(a_i\ \text{and}\ a_j\ \text{are compared}) \end{aligned}
    $$
    
    **Lemma 2:** $a_i$ and $a_j$ are compared if and only if $a_i$ or $a_j$ is the first selected pivot in set $A_{i,j}$.
    
    We first prove necessity: if neither $a_i$ nor $a_j$ is the first selected pivot in set $A_{i,j}$, then $a_i$ and $a_j$ are not compared.
    
    If neither $a_i$ nor $a_j$ is the first selected pivot in set $A_{i,j}$, there exists some $x$ with $i < x < j$ such that $a_x$ is the first selected pivot in $A_{i,j}$. In the partition with $a_x$ as pivot, $a_i$ and $a_j$ are divided into two different subsequences. Thus, $a_i$ and $a_j$ will never be compared afterward. Since elements are only compared with the pivot, $a_i$ and $a_j$ are not compared before or during this partition. Therefore, $a_i$ and $a_j$ are not compared.
    
    We now prove sufficiency: if $a_i$ or $a_j$ is the first selected pivot in set $A_{i,j}$, then $a_i$ and $a_j$ are compared.
    
    Without loss of generality, assume $a_i$ is the first selected pivot in set $A_{i,j}$. Since no other element in $A_{i,j}$ has been selected as pivot, all elements in $A_{i,j}$ are in the same subsequence of the array. In the partition with $a_i$ as pivot, $a_i$ is compared with all elements in the current subsequence, so $a_i$ and $a_j$ are compared.
    
    Let's calculate $P(a_i\ \text{and}\ a_j\ \text{are compared})$. Before an element in $A_{i,j}$ is selected as pivot, all elements in $A_{i,j}$ are in the same subsequence of the array. Therefore, each element in $A_{i,j}$ is equally likely to be selected first as pivot. Since $A_{i,j}$ contains $j - i + 1$ elements, by Lemma 2,
    
    $$
    P(a_i \text{and} a_j \text{are compared}) = P(a_i \text{or} a_j \text{is the first selected pivot in} A_{i,j}) = \dfrac{2}{j-i+1}
    $$
    
    Hence
    
    $$
    \begin{aligned} E[X] & = \sum \limits _ {i = 1} ^ {n - 1} \sum \limits _ {j = i + 1} ^ n P(a_i\ \text{and}\ a_j\ \text{are compared}) \\ & = \sum \limits _ {i = 1} ^ {n - 1} \sum \limits _ {j = i + 1} ^ n \dfrac{2}{j - i + 1} \\ & = \sum \limits _ {i = 1} ^ {n - 1} \sum \limits _ {k = 2} ^ {n - i + 1} \dfrac{2}{k} \\ & = \sum \limits _ {i = 1} ^ {n - 1} O(\log n) \\ & = O(n \log n) \end{aligned}
    $$
    
    Therefore, the expected time complexity of quicksort is $O(n \log n)$.

In practice, the worst case is almost never reached, and quicksort's memory access follows the principle of locality. Therefore, in most cases, quicksort significantly outperforms heap sort and other $O(n \log n)$ sorting algorithms.

## Optimizations

### Naive Optimization Ideas

If you implement quicksort according to the basic idea described above (or simply copy a template), you will most likely fail to pass [P1177 [Template] Quicksort](https://www.luogu.com.cn/problem/P1177). This is because malicious test data can degrade naive quicksort to $O(n^2)$.

Therefore, we need to optimize the naive quicksort idea. There are three common optimization approaches:

-   Use **median-of-three** (selecting the median of the first, last, and middle elements) to choose the partition element (pivot). This avoids degradation caused by extreme data (such as sorted or reverse-sorted sequences);
-   When the sequence is short, **insertion sort** is more efficient;
-   After each pass, **gather elements equal to the pivot around the pivot**. This avoids degradation caused by extreme data (such as sequences with many identical elements).

Below are several well-established quicksort optimization methods.

### Three-Way Quicksort

#### Definition

Three-way radix quicksort (English: 3-way Radix Quicksort) is a hybrid of quicksort and [radix sort](./radix-sort.md). Its algorithm is based on the solution to the [Dutch national flag problem](https://en.wikipedia.org/wiki/Dutch_national_flag_problem).

#### Process

Unlike the original quicksort, three-way quicksort, after randomly selecting a pivot $m$, divides the input sequence into three parts: elements less than $m$, elements equal to $m$, and elements greater than $m$. This achieves the effect of gathering elements equal to the pivot around the pivot.

#### Properties

Three-way quicksort is much more efficient than the original quicksort when processing arrays containing multiple duplicate values. Its best time complexity is $O(n)$.

#### Implementation

Three-way quicksort is very simple to implement. Below is a C++ implementation.

=== "C++"
    ```cpp
    // Template parameter T represents the element type, which must define less-than (<) operator
    template <typename T>
    // arr is the array to be sorted, len is the array length
    void quick_sort(T arr[], const int len) {
      if (len <= 1) return;
      // Randomly select the pivot
      const T pivot = arr[rand() % len];
      // i: current element index
      // arr[0, j): elements less than pivot
      // arr[k, len): elements greater than pivot
      int i = 0, j = 0, k = len;
      // Complete one pass of three-way quicksort, dividing the sequence into:
      // elements less than pivot | elements equal to pivot | elements greater than pivot
      while (i < k) {
        if (arr[i] < pivot)
          swap(arr[i++], arr[j++]);
        else if (pivot < arr[i])
          swap(arr[i], arr[--k]);
        else
          i++;
      }
      // Recursively complete quicksort for the two sub-sequences
      quick_sort(arr, j);
      quick_sort(arr + k, len - k);
    }
    ```

=== "Python[^ref2]"
    ```python
    def quick_sort(arr, l, r):
        if l >= r:
            return
        random_index = random.randint(l, r)
        pivot = arr[random_index]
        arr[l], arr[random_index] = arr[random_index], arr[l]
        i = l + 1
        j = l
        k = r + 1
        while i < k:
            if arr[i] < pivot:
                arr[i], arr[j + 1] = arr[j + 1], arr[i]
                j += 1
                i += 1
            elif arr[i] > pivot:
                arr[i], arr[k - 1] = arr[k - 1], arr[i]
                k -= 1
            else:
                i += 1
        arr[l], arr[j] = arr[j], arr[l]
        quick_sort(arr, l, j - 1)
        quick_sort(arr, k, r)
    ```

### Introsort

#### Definition

Introsort (English: Introsort or Introspective sort) is a hybrid of quicksort and [heap sort](./heap-sort.md), invented by David Musser in 1997. Introsort is essentially an optimization of quicksort, guaranteeing a worst-case time complexity of $O(n\log n)$.

#### Properties

Introsort limits the maximum recursion depth of quicksort to $\lfloor \log_2n \rfloor$. When this limit is exceeded, it switches to heap sort. This preserves the locality of quicksort's memory access while preventing quicksort from degrading to $O(n^2)$ in certain cases.

#### Implementation

Since June 2000, the `sort()` function in SGI C++ STL's `stl_algo.h` has used the introsort algorithm.

## Linear Selection of the k-th Largest Element

In the code examples below, the $k$-th largest element is defined as the element at position $k$ when the sequence is sorted in ascending order (numbering starts from 0).

The simplest way to find the $k$-th largest element (K-th order statistic) is to first sort, then directly access the element at position $k$. This takes $O(n\log n)$ time, which is not cost-effective for this problem.

We can use the idea of quicksort to solve this problem. Consider the partitioning step in quicksort. After partitioning, the sequence $A_{p} \cdots A_{r}$ is divided into $A_{p} \cdots A_{q}$ and $A_{q+1} \cdots A_{r}$. At this point, we can determine whether to search only the left part or only the right part based on the number of elements on the left side ($q - p + 1$) and the value of $k$.

Like quicksort, the time complexity of this method depends on the pivot selection during partitioning. If pivot selection is randomized, it can be proven that the expected time complexity of the program is $O(n)$.

### Implementation (C++)

```cpp
// Template parameter T represents the element type, which must define less-than (<) operator
template <typename T>
// arr is the search range array, rk is the rank to search (starting from 0), len is the array length
T find_kth_element(T arr[], int rk, const int len) {
  if (len <= 1) return arr[0];
  // Randomly select the pivot
  const T pivot = arr[rand() % len];
  // i: current element index
  // arr[0, j): elements less than pivot
  // arr[k, len): elements greater than pivot
  int i = 0, j = 0, k = len;
  // Complete one pass of three-way partition, dividing the sequence into:
  // elements less than pivot | elements equal to pivot | elements greater than pivot
  while (i < k) {
    if (arr[i] < pivot)
      swap(arr[i++], arr[j++]);
    else if (pivot < arr[i])
      swap(arr[i], arr[--k]);
    else
      i++;
  }
  // Based on the rank to find and the positions of the two partition boundaries, recursively search the k-th largest element in the appropriate range
  // If there are more elements less than pivot than k, the k-th largest element must be one less than pivot
  if (rk < j) return find_kth_element(arr, rk, j);
  // Otherwise, if the count of elements less than pivot plus elements equal to pivot is still less than k,
  // the k-th largest element must be one greater than pivot
  else if (rk >= k)
    return find_kth_element(arr + k, rk - k, len - k);
  // Otherwise, the pivot is the k-th largest element
  return pivot;
}
```

### Improvement: Median of Medians

The median of medians (English: Median of medians) provides a deterministic method for selecting the partition pivot, enabling the K-th largest element selection algorithm to achieve linear time complexity even in the worst case.

The algorithm's procedure is as follows:

1.  Divide the entire sequence into $\left \lfloor \dfrac{n}{5} \right \rfloor$ groups, with each group containing at most 5 elements;
2.  Find the median of each group (since the number of elements is small, you can use [insertion sort](./insertion-sort.md) or other algorithms directly);
3.  Find the median of the medians of these $\left \lfloor \dfrac{n}{5} \right \rfloor$ groups. Use this element as the partition pivot for each iteration of the algorithm above.

#### Time Complexity Proof

We will prove that the algorithm's worst-case time complexity is $O(n)$. Let $T(n)$ be the amount of computation needed to solve the problem when the problem size is $n$.

First, analyze the first two steps — partitioning and finding medians. Since each group has very few elements after partitioning, we can assume the time complexity of finding the median of a group is $O(1)$. Therefore, finding the medians of all $\left \lfloor \dfrac{n}{5} \right \rfloor$ groups takes $O(n)$ time.

Next, analyze the third step — the recursive process. This step involves two recursive calls: the first is to find the median of the medians, which obviously costs $T(\dfrac{n}{5})$; the second is to enter either the left or right side of the pivot. Based on our pivot selection, at least $\dfrac{1}{2} \times \left \lfloor \dfrac{n}{5} \right \rfloor = \left \lfloor \dfrac{n}{10} \right \rfloor$ groups have medians smaller than the pivot. In these groups, elements smaller than the median are also smaller than the pivot. Therefore, the total number of elements smaller than the pivot in the entire sequence is at least $3 \times \left \lfloor \dfrac{n}{10} \right \rfloor = \left \lfloor \dfrac{3n}{10} \right \rfloor$. Similarly, there are at least $\left \lfloor \dfrac{3n}{10} \right \rfloor$ elements greater than the pivot. Therefore, at most $\dfrac{7n}{10}$ elements are on either the left or right side of the pivot. The time cost of this recursive step has an upper bound of $T(\dfrac{7n}{10})$.

Summarizing, we can write this inequality:

$$
T(n) \leq T(\dfrac{n}{5}) + T(\dfrac{7n}{10}) + O(n)
$$

Assume $T(n) = O(n)$ holds when the problem size is sufficiently small. By definition, we have $T(n) \leq cn$, where $c$ is a positive constant. Substituting all $T(n)$ on the right side of the inequality:

$$
\begin{aligned}
T(n) & \leq T(\dfrac{n}{5}) + T(\dfrac{7n}{10}) + O(n)\\
     & \leq \dfrac{cn}{5} + \dfrac{7cn}{10} + O(n)\\
     & \leq \dfrac{9cn}{10} + O(n)\\
     & = O(n)
\end{aligned}
$$

At this point, we have proven that the algorithm has $O(n)$ time complexity even in the worst case.

## References and Notes

[^ref1]: [C++ Performance Juicer - Principle of Locality - I'm Root lee !](http://irootlee.com/juicer_locality/)

[^ref2]: [Algorithm Implementation/Sorting/Quicksort - Wikibooks, Free Textbook](https://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Quicksort)

[^ref3]: [Three Types of Quicksort and Quicksort Optimization](https://blog.csdn.net/insistGoGo/article/details/7785038)

[^ref4]: [Introsort](https://en.wikipedia.org/wiki/Introsort)
