author: sshwy, StudyingFather, orzAtalod

## Definition

First, we introduce the concept of Lyndon decomposition.

Lyndon word: For a string $s$, if the lexicographic order of $s$ is strictly less than the lexicographic order of all suffixes of $s$, we call $s$ a simple word, or **Lyndon word**. Some examples: `a`, `b`, `ab`, `aab`, `abb`, `ababb`, `abcd` are all Lyndon words. $s$ is a Lyndon word if and only if its lexicographic order is strictly less than all of its non-trivial (non-trivial: non-empty and not equal to itself) cyclic shifts.

Lyndon decomposition: The Lyndon decomposition of string $s$ is denoted as $s = w_1w_2\cdots w_k$, where all $w_i$ are simple words, and their lexicographic order is in non-strictly decreasing order, i.e., $w_1 \ge w_2 \ge \cdots \ge w_k$. It can be found that such a decomposition exists and is unique.

## Duval Algorithm

### Explanation

Duval can compute the Lyndon decomposition of a string in $O(n)$ time.

First, we introduce another concept: if a string $t$ can be decomposed as $t = ww\cdots\overline{w}$, where $w$ is a Lyndon word and $\overline{w}$ is a prefix of $w$ ($\overline{w}$ may be empty), then we call $t$ a pre-simple word, or pre-Lyndon word. A Lyndon word is also a pre-Lyndon word.

The Duval algorithm uses a greedy approach. During the algorithm, we divide the string $s$ into three parts $s = s_1s_2s_3$, where $s_1$ is a Lyndon word whose Lyndon decomposition has been recorded; $s_2$ is a pre-Lyndon word; $s_3$ is the unprocessed part.

### Process

Overall, in each iteration, the algorithm attempts to add the first character of $s_3$ to the end of $s_2$. If $s_2$ is no longer a pre-Lyndon word, then we can extract a prefix from $s_2$ (i.e., its Lyndon decomposition) and append it to the end of $s_1$.

Let us explain the algorithm process in more detail. Define a pointer $i$ pointing to the first character of $s_2$, then $i$ traverses from $1$ to $n$ (the length of the string). During the loop, we define another pointer $j$ pointing to the first character of $s_3$, and a pointer $k$ pointing to the character we are currently considering in $s_2$ (which means the character corresponding to $j$ in the previous period of $s_2$). Our goal is to add $s[j]$ to the end of $s_2$, which requires comparing $s[j]$ with $s[k]$:

1.  If $s[j] = s[k]$, adding $s[j]$ to the end of $s_2$ will not affect its pre-simplicity. So we just need to increment pointers $j$ and $k$ (move to the next position).
2.  If $s[j] > s[k]$, then $s_2s[j]$ becomes a Lyndon word, so we increment $j$ and let $k$ point to the first character of $s_2$, making $s_2$ a new Lyndon word with a period of 1.
3.  If $s[j] < s[k]$, then $s_2s[j]$ is not a pre-simple word anymore, so we need to decompose $s_2$ into one of its Lyndon substrings, whose length will be $j-k$, i.e., one of its periods. Then $s_2$ becomes the remaining part after decomposition, and we continue the loop (note, in this case we do not change pointers $j, k$), until the period is extracted. For the remaining part, we only need to "rewind" the progress to the beginning of the remaining part.

### Implementation

The following code returns the Lyndon decomposition of string $s$.

=== "C++"
    ```cpp
    // duval_algorithm
    vector<string> duval(string const& s) {
      int n = s.size(), i = 0;
      vector<string> factorization;
      while (i < n) {
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
          if (s[k] < s[j])
            k = i;
          else
            k++;
          j++;
        }
        while (i <= k) {
          factorization.push_back(s.substr(i, j - k));
          i += j - k;
        }
      }
      return factorization;
    }
    ```

=== "Python"
    ```python
    # duval_algorithm
    def duval(s):
        n, i = len(s), 0
        factorization = []
        while i < n:
            j, k = i + 1, i
            while j < n and s[k] <= s[j]:
                if s[k] < s[j]:
                    k = i
                else:
                    k += 1
                j += 1
            while i <= k:
                factorization.append(s[i : i + j - k])
                i += j - k
        return factorization
    ```

### Complexity Analysis

Now we prove the complexity of this algorithm.

The outer loop runs at most $n$ times, because $i$ increases each time. The second inner loop is also $O(n)$, because it only records the Lyndon decomposition. Now let us analyze the inner loop. It is easy to find that each Lyndon word found in the outer loop is longer than the remaining strings we have compared, so the total length of the remaining strings is less than $n$. Thus, we run the inner loop at most $O(n)$ times. In fact, the total number of iterations does not exceed $4n-3$, and the time complexity is $O(n)$.

## Minimal Representation Method (Finding the smallest cyclic shift)

For a string $s$ of length $n$, we can find the minimal representation of this string using the above algorithm.

We construct the Lyndon decomposition of the string $ss$, and find a Lyndon word $t$ in this decomposition such that its starting point is less than $n$ and its ending point is greater than or equal to $n$. Using the properties of Lyndon decomposition, it is easy to prove that the first character of the substring $t$ is the first character of the minimal representation of $s$, that is, the string formed by the $n$ characters starting from the beginning of $t$ is the minimal representation of $s$.

So we just need to record the beginning of each pre-Lyndon word during the decomposition.

=== "C++"
    ```cpp
    // smallest_cyclic_string
    string min_cyclic_string(string s) {
      s += s;
      int n = s.size();
      int i = 0, ans = 0;
      while (i < n / 2) {
        ans = i;
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
          if (s[k] < s[j])
            k = i;
          else
            k++;
          j++;
        }
        while (i <= k) i += j - k;
      }
      return s.substr(ans, n / 2);
    }
    ```

=== "Python"
    ```python
    # smallest_cyclic_string
    def min_cyclic_string(s):
        s += s
        n = len(s)
        i, ans = 0, 0
        while i < n / 2:
            ans = i
            j, k = i + 1, i
            while j < n and s[k] <= s[j]:
                if s[k] < s[j]:
                    k = i
                else:
                    k += 1
                j += 1
            while i <= k:
                i += j - k
        return s[ans : ans + n / 2]
    ```

## Problems

-   [UVa #719 - Glass Beads](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=660)

    **This page is mainly translated from the blog post [Декомпозиция Линдона. Алгоритм Дюваля. Нахождение наименьшего циклического сдвига](http://e-maxx.ru/algo/duval_algorithm) and its English translation [Lyndon factorization](https://cp-algorithms.com/string/lyndon_factorization.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**