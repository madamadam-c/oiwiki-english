This page briefly introduces Shellsort.

## Definition

Shellsort (English: Shell sort), also known as the diminishing increment sort, is an improved version of [insertion sort](./insertion-sort.md). Shellsort is named after its inventor, Donald Shell.

## Process

Sorting involves comparing and moving records that are not adjacent to each other:

1.  Divide the sequence to be sorted into several subsequences (where each subsequence's elements have the same spacing in the original array);
2.  Perform insertion sort on these subsequences;
3.  Reduce the spacing between elements in each subsequence, and repeat the above process until the spacing is reduced to $1$.

## Properties

### Stability

Shellsort is an unstable sorting algorithm.

### Time Complexity

The optimal time complexity of Shellsort is $O(n)$.

The average and worst-case time complexity of Shellsort depends on the choice of gap sequence. Let the gap sequence be $H$. Two classic choices for $H$ are given below, both of which reduce the sorting algorithm's complexity to $o(n^2)$.

???+ note "Proposition 1"
    If the gap sequence is $H = \{ 2^k - 1 \mid k = 1, 2, \ldots, \lfloor \log_2 n \rfloor \}$ (in decreasing order), then the time complexity of Shellsort is $O(n^{3/2})$.

???+ note "Proposition 2"
    If the gap sequence is $H = \{ k = 2^p \cdot 3^q \mid p, q \in \mathbb{N}, k \le n \}$ (in decreasing order), then the time complexity of Shellsort is $O(n \log^2 n)$.

To prove these two propositions, we first present and prove an important theorem, which reflects the main characteristic of Shellsort.

???+ note "Theorem 1"
    Once the program has executed $\text{InsertionSort}(h)$, regardless of how subsequent calls to $\text{InsertionSort}$ proceed and how array $A$ changes, the following property is always maintained:
    
    $$
    \begin{array}{c}
    A_1, A_{1+h}, A_{1+2h}, \ldots \\
    A_2, A_{2+h}, A_{2+2h}, \ldots \\
    \vdots \\
    A_h, A_{h+h}, A_{h+2h}, \ldots
    \end{array}
    $$

Now we prove Theorem 1.

We first prove Lemma 1.

???+ note "Lemma 1"
    For integers $n, m$, positive integer $l$, and two arrays $X(x_1, x_2, \ldots, x_{n+l}), Y(y_1, y_2, \ldots, y_{m+l})$, satisfying the following requirement:
    
    $$
    y_1 \le x_{n+1}, y_2 \le x_{n+2}, \ldots, y_l \le x_{n+l}
    $$
    
    Then after sorting both arrays in ascending order, the above requirement still holds.

??? note "Proof of Lemma 1"
    Let the sorted $X$ be $X'(x'_1, \ldots, x'_{n+l})$, and the sorted $Y$ be $Y'(y'_1, \ldots, y'_{m+l})$.
    
    For any $1 \le i \le l$, $x'_{n+i}$ is less than or equal to $l-i$ elements in array $X'$, and also less than or equal to $l-i$ elements in array $X$ (this is because $X$ and $X'$ have the same multiset of elements).
    
    Therefore, in the multiset $\{ x_{n+1}, \ldots, x_{n+l} \} \subset X$, the number of elements greater than or equal to $x'_{n+i}$ is at most $l-i$.
    
    Consequently, the number of elements less than $x'_{n+i}$ is at least $i$. Take $i$ of them, and denote them as $x_{n+k_1}, x_{n+k_2}, \ldots, x_{n+k_i}$. Then we have:
    
    $$
    y_{k_1} \le x_{n+k_1} \le x'_{n+i}, y_{k_2} \le x_{n+k_2} \le x'_{n+i}, \ldots, y_{k_i} \le x_{n+k_i} \le x'_{n+i}
    $$
    
    So $x'_{n+i}$ is at least greater than or equal to $i$ elements in $Y$, which is also $Y'$. Then naturally we have $y'_i \le x'_{n+i}\,(1 \le i \le l)$.

Returning to the proof of the original proposition:

We actually only need to prove that after the next call to $\text{InsertionSort}(k)$ following $\text{InsertionSort}(h)$, the $h$ subsequences remain sorted. The rest follows easily by induction. Below we consider only the next call:

After executing $\text{InsertionSort}(h)$, the following groups have been sorted:

$$
\begin{array}{c}
A_1, A_{1+h}, A_{1+2h}, \ldots \\
A_2, A_{2+h}, A_{2+2h}, \ldots \\
\vdots \\
A_h, A_{h+h}, A_{h+2h}, \ldots
\end{array}
$$

Then executing $\text{InsertionSort}(k)$ will sort the following groups:

$$
\begin{array}{c}
A_1, A_{1+k}, A_{1+2k}, \ldots \\
A_2, A_{2+k}, A_{2+2k}, \ldots \\
\vdots \\
A_k, A_{k+k}, A_{k+2k}, \ldots
\end{array}
$$

For each $i$ $(1 \le i \le \min(h, k))$, consider the following two groups:

$$
\begin{array}{c}
A_i, A_{i+k}, A_{i+2k}, \ldots \\
\ldots, A_{i+h}, A_{i+h+k}, A_{i+h+2k}, \ldots
\end{array}
$$

The reason we also add "$\ldots$" at the front of the second group is that it is possible that $i + h \ge k$, so there are also elements before.

Then the second group is the $X$ array from Lemma 1, the first group is the $Y$ array, $l$ is the length of the second group from $i+h$ to the end, $n$ is the length of "$\ldots$" before the second group, and $m$ is the number of elements remaining in the first group after removing the first $l$.

Since we have:

$$
A_i \le A_{i+h}, A_{i+k} \le A_{i+h+k}, \ldots
$$

by Lemma 1, after $\text{InsertionSort}(k)$ sorts both groups separately, this relationship is still maintained, that is, we still have $A_i \le A_{i+h}\,(1 \le i \le \min(h, k))$.

If $i > \min(h, k)$, it is easy to find that taking a positive integer $w$ $(1 \le w \le \min(h, k))$ plus some multiples of $k$ yields $i$, so the previous case already encompasses the proof for this case.

Summing up the above arguments, we have: after executing $\text{InsertionSort}(k)$, we still have $A_i \le A_{i+h}\,(1 \le i \le n-h)$.

Thus Theorem 1 is proven.

This theorem reveals the key to Shellsort achieving optimized complexity with specific gap sets $H$, because throughout the process, it can consistently maintain the progress already made (i.e., the $h$ subsequences are respectively sorted), thereby greatly reducing the number of moves of pointer $i$ in subsequent calls.

Next, we separately prove a number theory lemma. This lemma is well-known in the OI community due to the problem [Little Kai's Confusion](https://www.luogu.com.cn/problem/P3951). And in the proof of Shellsort complexity, it greatly extends Theorem 1.

???+ note "Lemma 2"
    If $a, b$ are both positive integers and are coprime, then the largest positive integer not belonging to the set $\{ ax + by \mid x, y \in \mathbb{N} \}$ is $ab - a - b$.

??? note "Proof of Lemma 2"
    We prove in two steps:
    
    -   First, prove that the equation $ax + by = ab - a - b$ has no solution with both $x, y$ as nonnegative integers:
    
        If there were no restriction to nonnegative integers, we could easily obtain two solutions: $(b-1, -1), (-1, a-1)$.
    
        Through the general solution form $x = x_0 + tb, y = y_0 - ta$, it is easy to see that these two solutions are "adjacent" (because $b-1-b = -1$).
    
        When $t$ increases, $x$ increases and $y$ decreases. Therefore, if the equation has nonnegative integer solutions, they must be sandwiched between these two solutions. But since these two solutions are "adjacent", there are no other solutions between them.
    
        Hence, nonnegative integer solutions are impossible.
    -   Second, prove that for any integer $c > ab - a - b$, the equation $ax + by = c$ has nonnegative integer solutions:
    
        We find a solution $(x_0, y_0)$ satisfying $0 \le x_0 < b$ (from the general solution expression, this is possible).
    
        Then:
    
        $$
        by_0 = c - ax_0 \ge c - a(b-1) > ab - a - b - ab + a = -b
        $$
    
        So $b(y_0 + 1) > 0$, and since $b > 0$, we have $y_0 + 1 > 0$, so $y_0 \ge 0$.
    
        Therefore, $(x_0, y_0)$ is a nonnegative integer solution.
    
    The proof is complete.

The following theorem reveals how Lemma 2 extends Theorem 1.

???+ note "Theorem 2"
    If $\gcd(h_{t+1}, h_t) = 1$, then after the program finishes executing $\text{InsertionSort}(h_{t+1})$ and $\text{InsertionSort}(h_t)$, the time complexity of executing $\text{InsertionSort}(h_{t-1})$ is $O\left(\dfrac{nh_{t+1}h_t}{h_{t-1}}\right)$, and for each $j$, the number of moves of $i$ is $O\left(\dfrac{h_{t+1}h_t}{h_{t-1}}\right)$.

??? note "Proof of Theorem 2"
    For the part where $j \le h_{t+1}h_t$, the number of moves of $i$ is obviously $O\left(\dfrac{h_{t+1}h_t}{h_{t-1}}\right)$.
    
    Therefore, assume $j > h_{t+1}h_t$.
    
    For any positive integer $k$ satisfying $1 \le k \le j - h_{t+1}h_t$, note that: $h_{t+1}h_t - h_{t+1} - h_t < h_{t+1}h_t \le j - k \le j - 1$
    
    Also, since $\gcd(h_{t+1}, h_t) = 1$, by Lemma 2, there exist nonnegative integers $a, b$ such that: $ah_{t+1} + bh_t = j - k$.
    
    That is:
    
    $$
    k = j - ah_{t+1} - bh_t
    $$
    
    By Theorem 1:
    
    $$
    A_{j-bh_t} \le A_{j-(b-1)h_t} \le \ldots \le A_{j-h_t} \le A_j
    $$
    
    and
    
    $$
    A_{j-bh_t-ah_{t+1}} \le A_{j-bh_t-(a-1)h_{t+1}} \le \ldots \le A_{j-bh_t-h_{t+1}} \le A_{j-bh_t}
    $$
    
    Combining these: $A_k = A_{j-ah_{t+1}-bh_t} \le A_j$.
    
    So for any $1 \le k \le j - h_{t+1}h_t$, we have $A_k \le A_j$.
    
    In the Shellsort pseudocode, pointer $i$ decreases by $h_{t-1}$ each time. After decreasing $O\left(\dfrac{h_{t+1}h_t}{h_{t-1}}\right)$ times, we can make $i \le j - h_{t+1}h_t$, and then $A_i \le A_j$, so the while loop condition is not satisfied and it exits.
    
    After proving the move complexity for each $j$, the total time complexity can be obtained:
    
    $$
    \sum_{j=h_{t-1}+1}^n O\left(\frac{h_{t+1}h_t}{h_{t-1}}\right) = O\left(\frac{nh_{t+1}h_t}{h_{t-1}}\right)
    $$
    
    QED.

Careful observation of the proof process of Theorem 2 reveals that Theorem 1 can be "linearly combined": if $A$ is sorted with spacing $h$, and also sorted with spacing $k$, then it is still sorted with any nonnegative linear combination of $h$ and $k$. This "linearity" is guaranteed by Lemma 2.

With these two theorems, we can prove Propositions 1 and 2.

??? note "Proof of Proposition 1"
    Write $H$ in sequence form:
    
    $$
    H(h_1 = 1, h_2 = 3, h_3 = 7, \ldots, h_{\lfloor \log_2 n \rfloor} = 2^{\lfloor \log_2 n \rfloor} - 1)
    $$
    
    Shellsort executes in the order: $\text{InsertionSort}(h_{\lfloor \log_2 n \rfloor}), \text{InsertionSort}(h_{\lfloor \log_2 n \rfloor-1}), \ldots, \text{InsertionSort}(h_2), \text{InsertionSort}(h_1)$.
    
    We analyze complexity in two parts:
    
    -   For the first several $h_t$ satisfying $h_t \ge \sqrt{n}$, the time complexity of $\text{InsertionSort}(h_t)$ is obviously $O\left(\dfrac{n^2}{h_t}\right)$.
    
        Consider the term $h_k$ closest to $\sqrt{n}$:
    
        $$
        O\left(\frac{n^2}{h_t}\right) = O(n^{3/2})
        $$
    
        For $h_i$ where $i > k$, since $2h_i < h_{i+1}$, we have:
    
        $$
        O\left(\frac{n^2}{h_i}\right) = O(n^{3/2}/2^{i-k})\,(i>k)
        $$
    
        Therefore, the total time complexity for the part greater than or equal to $\sqrt{n}$ is:
    
        $$
        \sum_{i=k}^{\lfloor \log_2 n \rfloor} O(n^{3/2}/2^{i-k}) = O(n^{3/2})
        $$
    -   For the remaining part satisfying $h_t < \sqrt{n}$, the complexity of the first two terms is still $O(n^{3/2})$. For the subsequent terms $h_t$, by Theorem 2, the time complexity is:
    
        $$
        O\left(\frac{nh_{t+2}h_{t+1}}{h_t}\right) = O\left(\frac{nh_{t+2} \cdot h_{t+2}/2}{h_{t+2}/4}\right) = O(nh_{t+2})
        $$
    
        Using the property $2h_i < h_{i+1}$ again, the total time complexity of this part is (where $k$ has the same meaning as in the previous case):
    
        $$
        2O(n^{3/2}) + \sum_{i=1}^{k-3} O(nh_{i+1}) = O(n^{3/2}) + \sum_{i=1}^{k-3} O(nh_{k-1}/2^{k-i-3}) = O(n^{3/2}) + O(nh_{k-1}) = O(n^{3/2})
        $$
    
    Summing up, the total time complexity is $O(n^{3/2})$.

??? note "Proof of Proposition 2"
    Note a fact: if $\text{InsertionSort}(2)$ and $\text{InsertionSort}(3)$ have already been executed, then because $2 \cdot 3 - 2 - 3 = 1$, by Theorem 2, each element only needs to be compared with its immediate predecessor, and all previous elements are smaller than it. Therefore, pointer $i$ needs at most two moves to exit the while loop. That is, at this point, executing $\text{InsertionSort}(1)$ has complexity $O(n)$.
    
    Going further: if $\text{InsertionSort}(4)$ and $\text{InsertionSort}(6)$ have already been executed, we consider all elements with odd indices and all elements with even indices as two separate subsequences. This is equivalent to executing $\text{InsertionSort}(2)$ and $\text{InsertionSort}(3)$ on these two subsequences separately. Then, executing $\text{InsertionSort}(2)$ is equivalent to executing $\text{InsertionSort}(1)$ on each of the two subsequences, which also requires only $O(n)$ complexity to make the array 2-spacing sorted.
    
    By continuous induction: if $\text{InsertionSort}(2h)$ and $\text{InsertionSort}(3h)$ have already been executed, then the complexity of executing $\text{InsertionSort}(h)$ is also only $O(n)$.
    
    Next, we analyze complexity in two parts:
    
    -   For the part where $h_t > n/3$, the complexity of executing each $\text{InsertionSort}(h_t)$ is $O(n^2/h_t)$.
    
        And $n^2/h_t < 3n$, so the single insertion sort complexity is $O(n)$.
    
        The number of elements in this part is $O(\log^2 n)$, so the total time complexity of this part is $O(n \log^2 n)$.
    -   For the part where $h_t \le n/3$, since $3h_t \le n$, $\text{InsertionSort}(2h_t)$ and $\text{InsertionSort}(3h_t)$ have already been executed before. Therefore, the time complexity of executing $\text{InsertionSort}(h_t)$ is $O(n)$.
    
        Similarly, the number of elements in this part is also $O(\log^2 n)$, so the total time complexity of this part is $O(n \log^2 n)$.
    
    Summing up, the total time complexity is $O(n \log^2 n)$.

### Space Complexity

The space complexity of Shellsort is $O(1)$.

## Implementation

=== "C++[^ref1]"
    ```cpp
    template <typename T>
    void shell_sort(T array[], int length) {
      int h = 1;
      while (h < length / 3) {
        h = 3 * h + 1;
      }
      while (h >= 1) {
        for (int i = h; i < length; i++) {
          for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {
            std::swap(array[j], array[j - h]);
          }
        }
        h = h / 3;
      }
    }
    ```

=== "Python"
    ```python
    def shell_sort(array, length):
        h = 1
        while h < length / 3:
            h = int(3 * h + 1)
        while h >= 1:
            for i in range(h, length):
                j = i
                while j >= h and array[j] < array[j - h]:
                    array[j], array[j - h] = array[j - h], array[j]
                    j -= h
            h = int(h / 3)
    ```

## References and Notes

[^ref1]: [Shellsort - Wikipedia, the Free Encyclopedia](https://en.wikipedia.org/wiki/Shellsort)
