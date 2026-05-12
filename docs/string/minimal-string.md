## Definition

The minimal representation method is used to solve the string minimal representation problem.

## Minimal Representation of a String

### Cyclic Shift

When a position $i$ in string $S$ can be selected such that

$$
S[i\cdots n]+S[1\cdots i-1]=T
$$

then $S$ and $T$ are said to be cyclic shifts of each other.

### Minimal Representation

The minimal representation of string $S$ is the lexicographically smallest string among all strings that are cyclic shifts of $S$.

## Simple Brute Force

We compare the cyclic shifts starting at $i$ and $j$ each time, keeping track of the current position $k$. Whenever we encounter different characters, we skip the larger one. The remaining position is the optimal solution.

### Implementation

=== "C++"
    ```cpp
    int k = 0, i = 0, j = 1;
    while (k < n && i < n && j < n) {
      if (sec[(i + k) % n] == sec[(j + k) % n]) {
        ++k;
      } else {
        if (sec[(i + k) % n] > sec[(j + k) % n])
          ++i;
        else
          ++j;
        k = 0;
        if (i == j) i++;
      }
    }
    i = min(i, j);
    ```

=== "Python"
    ```python
    k, i, j = 0, 0, 1
    while k < n and i < n and j < n:
        if sec[(i + k) % n] == sec[(j + k) % n]:
            k += 1
        else:
            if sec[(i + k) % n] > sec[(j + k) % n]:
                i += 1
            else:
                j += 1
            k = 0
            if i == j:
                i += 1
    i = min(i, j)
    ```

### Explanation

This implementation performs well on random data, but special data can break it.

For example: for $\texttt{aaa}\cdots\texttt{aab}$, it is easy to see that this algorithm degenerates to $O(n^2)$.

We found that when there are multiple consecutive repeated substrings in the string, the efficiency of this algorithm decreases. We consider optimizing this process.

## Minimal Representation Method

### Core Algorithm

Consider a pair of strings $A, B$, with starting positions in the original string $S$ being $i, j$ respectively, and their first $k$ characters are all equal, i.e.,

$$
S[i \cdots i+k-1]=S[j \cdots j+k-1]
$$

First consider the case $S[i+k]>S[j+k]$. We find that strings with starting index $l$ satisfying $i \le l \le i+k$ cannot be the answer. Because for any string $S_{i+p}$ (representing the string starting at position $i+p$, $p \in [0, k]$), there always exists a string $S_{j+p}$ that is better than it.

So when comparing, we can skip index $l \in [i, i+k]$ and directly compare $S_{i+k+1}$.

Thus, we have completed the optimization of the brute force method above.

### Time Complexity

$O(n)$

### Process

1.  Initialize pointer $i$ to $0$, $j$ to $1$; initialize matching length $k$ to $0$.
2.  Compare the sizes of the $k$-th position, and jump to the corresponding pointer based on the comparison result. If both pointers are the same after jumping, arbitrarily increment one to ensure the two strings being compared are different.
3.  Repeat the above process until the comparison ends.
4.  The answer is the smaller of $i, j$.

### Implementation

=== "C++"
    ```cpp
    int k = 0, i = 0, j = 1;
    while (k < n && i < n && j < n) {
      if (sec[(i + k) % n] == sec[(j + k) % n]) {
        k++;
      } else {
        sec[(i + k) % n] > sec[(j + k) % n] ? i = i + k + 1 : j = j + k + 1;
        if (i == j) i++;
        k = 0;
      }
    }
    i = min(i, j);
    ```

=== "Python"
    ```python
    k, i, j = 0, 0, 1
    while k < n and i < n and j < n:
        if sec[(i + k) % n] == sec[(j + k) % n]:
            k += 1
        else:
            if sec[(i + k) % n] > sec[(j + k) % n]:
                i = i + k + 1
            else:
                j = j + k + 1
            if i == j:
                i += 1
            k = 0
    i = min(i, j)
    ```