## Description

Given a string $s$ of length $n$, find all pairs $(i, j)$ such that the substring $s[i \dots j]$ is a palindrome. A string $t$ is a palindrome when $t = t_{\text{rev}}$ ($t_{\text{rev}}$ is the reverse string of $t$).

## Explanation

Obviously, in the worst case there can be $O(n^2)$ palindromes, so at first glance there seems to be no linear algorithm for this problem.

However, the information about palindromes can be expressed in **a more compact way**: for each position $i = 0 \dots n - 1$, we find values $d_1[i]$ and $d_2[i]$. Both represent the number of palindromes of odd length and even length centered at position $i$. Alternatively, they represent the radius length of the longest palindrome centered at position $i$ (radius length $d_1[i]$, $d_2[i]$ are both the number of characters from position $i$ to the right end of the palindrome).

For example, for string $s = \mathtt{abababc}$ centered at $s[3] = b$, there are three odd-length palindromes, and the longest palindrome has radius $3$, i.e., $d_1[3] = 3$:

$$
a\ \overbrace{b\ a\ \underset{s_3}{b}\ a\ b}^{d_1[3]=3}\ c
$$

For string $s = \mathtt{cbaabd}$ centered at $s[3] = a$, there are two even-length palindromes, and the longest palindrome has radius $2$, i.e., $d_2[3] = 2$:

$$
c\ \overbrace{b\ a\ \underset{s_3}{a}\ b}^{d_2[3]=2}\ d
$$

Thus, the key idea is that if we have a palindrome of length $l$ centered at some position $i$, then we also have palindromes of length $l - 2$, $l - 4$, etc. centered at $i$. So the two arrays $d_1[i]$ and $d_2[i]$ are sufficient to represent all palindrome information in the string.

A surprising fact is that there exists an algorithm with linear complexity and simple enough to compute the two "palindrome property arrays" $d_1[]$ and $d_2[]$. In this article we will describe this algorithm in detail.

## Solutions

In general, this problem has multiple solutions: using string hashing, it can be solved in $O(n \log n)$ time, and using suffix arrays and fast LCA, it can be solved in $O(n)$ time.

However, the algorithm described here is **overwhelmingly** simple and has smaller constants in terms of time and space complexity. This algorithm was proposed by **Glenn K. Manacher** in 1975.

## Naive Algorithm

To avoid ambiguity in subsequent descriptions, we point out what the "naive algorithm" is.

This algorithm works as follows: for each center position $i$, after comparing a pair of corresponding characters, the algorithm tries to increment the answer by $1$ as long as possible.

This algorithm is relatively slow: it can only compute the answer in $O(n^2)$ time.

The implementation of this naive algorithm is as follows:

???+ note "Implementation"
    === "C++"
        ```cpp
        vector<int> d1(n), d2(n);
        for (int i = 0; i < n; i++) {
          d1[i] = 1;
          while (0 <= i - d1[i] && i + d1[i] < n && s[i - d1[i]] == s[i + d1[i]]) {
            d1[i]++;
          }
        
          d2[i] = 0;
          while (0 <= i - d2[i] - 1 && i + d2[i] < n &&
                 s[i - d2[i] - 1] == s[i + d2[i]]) {
            d2[i]++;
          }
        }
        ```
    
    === "Python"
        ```python
        d1 = [0] * n
        d2 = [0] * n
        for i in range(0, n):
            d1[i] = 1
            while 0 <= i - d1[i] and i + d1[i] < n and s[i - d1[i]] == s[i + d1[i]]:
                d1[i] += 1
        
            d2[i] = 0
            while 0 <= i - d2[i] - 1 and i + d2[i] < n and s[i - d2[i] - 1] == s[i + d2[i]]:
                d2[i] += 1
        ```

## Manacher Algorithm

Here we will only describe the case of finding all odd-length sub-palindromes, i.e., only computing $d_1[]$. The algorithm for finding all even-length sub-palindromes (i.e., computing array $d_2[]$) only requires small modifications to the algorithm for odd-length case.

To compute quickly, we maintain the **boundary $[l, r]$** of the rightmost sub-palindrome found so far (i.e., the palindrome with the maximum $r$ value, where $l$ and $r$ are the positions of the left and right boundaries of that palindrome). Initially, we set $l = 0$ and $r = -1$ (*-1* needs to be distinguished from reverse index position; it can be any negative number here, only for convenience at the start of the loop).

### Process

Now suppose we want to compute $d_1[i]$ for the next $i$, and all values in $d_1[]$ have been computed before. We will compute as follows:

-   If $i$ is outside the current sub-palindrome, i.e., $i > r$, then we call the naive algorithm.

    Therefore, we will continuously increase $d_1[i]$, and at each step check whether the current substring $[i - d_1[i] \dots i + d_1[i]]$ ($d_1[i]$ represents the radius length, same below) is a palindrome. If we find the first place where the corresponding characters differ, or we reach the boundary of $s$, the algorithm stops. In both cases, we have finished computing $d_1[i]$. After that, we still need to remember to update $(l, r)$.

-   Now consider the case $i \le r$. We will try to get some information from the already computed $d_1[]$ values. First, reflect position $i$ in the sub-palindrome $(l, r)$, i.e., we get $j = l + (r - i)$. Now consider the value $d_1[j]$. Because positions $j$ and $i$ are symmetric, we **almost always** can set $d_1[i] = d_1[j]$. The idea is illustrated below (we can think of the palindrome centered at $j$ being "copied" to the position centered at $i$):

    $$
    \ldots\
    \overbrace{
        s_l\ \ldots\
        \underbrace{
            s_{j-d_1[j]+1}\ \ldots\ s_j\ \ldots\ s_{j+d_1[j]-1}
        }_\text{palindrome}\
        \ldots\
        \underbrace{
            s_{i-d_1[j]+1}\ \ldots\ s_i\ \ldots\ s_{i+d_1[j]-1}
        }_\text{palindrome}\
        \ldots\ s_r
    }^\text{palindrome}\
    \ldots
    $$

    However, there is a **tricky case** that needs to be handled correctly: when the "inner" palindrome reaches the boundary of the "outer" palindrome, i.e., $j - d_1[j] + 1 \le l$ (or equivalently, $i + d_1[j] - 1 \ge r$). Since symmetry outside the "outer" palindrome is not guaranteed, directly setting $d_1[i] = d_1[j]$ would be incorrect: we don't have enough information to assert that the palindrome at position $i$ has the same length.

    In fact, to handle this case correctly, we should "truncate" the palindrome length, i.e., set $d_1[i] = r - i + 1$. Then we will run the naive algorithm to try to increase the value of $d_1[i]$ as much as possible.

    The illustration of this case is as follows (the palindrome centered at $j$ has been truncated to fit within the "outer" palindrome):

    $$
    \ldots\
    \overbrace{
        \underbrace{
            s_l\ \ldots\ s_j\ \ldots\ s_{j+(j-l)}
        }_\text{palindrome}\
        \ldots\
        \underbrace{
            s_{i-(r-i)}\ \ldots\ s_i\ \ldots\ s_r
        }_\text{palindrome}
    }^\text{palindrome}\
    \underbrace{
        \ldots \ldots \ldots \ldots \ldots
    }_\text{try moving here}
    $$

    This illustration shows that although the palindrome centered at $j$ may be longer and extend beyond the "outer" palindrome, at position $i$ we can only use the part that completely lies within the "outer" palindrome. However, the answer at position $i$ may be larger than this value, so next we run the naive algorithm to try to extend it beyond the "outer" palindrome, i.e., the area marked as "try moving here".

    Finally, it is still necessary to remind that we should remember to update the values $(l, r)$ after computing each $d_1[i]$.

    Also, let us repeat: the algorithm for computing the even-length palindrome array $d_2[]$ is very similar to the algorithm for computing the odd-length palindrome array $d_1[]$.

## Complexity of Manacher Algorithm

Since we always run the naive algorithm when computing the answer for a specific position, at first glance it is not obvious that the time complexity of this algorithm is linear.

However, a more careful analysis shows that the algorithm has linear complexity. Here we need to point out that the [algorithm for computing the Z-function](./z-func.md) is quite similar to this algorithm and also has linear time complexity.

In fact, note that each iteration of the naive algorithm increases $r$ by $1$, and $r$ never decreases during the execution of the algorithm. These two observations tell us that the naive algorithm will perform a total of $O(n)$ iterations.

The other part of Manacher's algorithm is obviously also linear, so the total complexity is $O(n)$.

## Implementation of Manacher Algorithm

### Case Analysis

To compute $d_1[]$, we have the following code:

=== "C++"
    ```cpp
    vector<int> d1(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
      int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
      while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
        k++;
      }
      d1[i] = k--;
      if (i + k > r) {
        l = i - k;
        r = i + k;
      }
    }
    ```

=== "Python"
    ```python
    d1 = [0] * n
    l, r = 0, -1
    for i in range(0, n):
        k = 1 if i > r else min(d1[l + r - i], r - i + 1)
        while 0 <= i - k and i + k < n and s[i - k] == s[i + k]:
            k += 1
        d1[i] = k
        k -= 1
        if i + k > r:
            l = i - k
            r = i + k
    ```

The code for computing $d_2[]$ is very similar, but there are some differences in the arithmetic expressions:

=== "C++"
    ```cpp
    vector<int> d2(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
      int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
      while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
        k++;
      }
      d2[i] = k--;
      if (i + k > r) {
        l = i - k - 1;
        r = i + k;
      }
    }
    ```

=== "Python"
    ```python
    d2 = [0] * n
    l, r = 0, -1
    for i in range(0, n):
        k = 0 if i > r else min(d2[l + r - i + 1], r - i + 1)
        while 0 <= i - k - 1 and i + k < n and s[i - k - 1] == s[i + k]:
            k += 1
        d2[i] = k
        k -= 1
        if i + k > r:
            l = i - k - 1
            r = i + k
    ```

### Unified Treatment

Although in the explanation and the above implementation we considered the computation of $d_1[]$ and $d_2[]$ separately, in fact they can be unified into the computation of $d_1[]$ using a trick.

Given a string $s$ of length $n$, we insert a separator $\#$ into each of its $n + 1$ gaps, thereby constructing a string $s'$ of length $2n + 1$. For example, for $s = \mathtt{abababc}$, its corresponding $s' = \mathtt{\#a\#b\#a\#b\#a\#b\#c\#}$.

The actual meaning of $\#$ between letters corresponds to the "gap" in $s$. The $\#$ at the two ends are for the convenience of implementation.

Note that after computing $d_1[]$ for $s'$, for a position $i$, the longest sub-palindrome described by $d_1[i]$ must end at a $\#$ (if it ends at a letter, since there must be a $\#$ on each side of the letter, it can be extended outward by one to get a longer one). Therefore, for a maximal sub-palindrome in $s$ centered at a letter, with length $m + 1$, it corresponds in $s'$ to a maximal sub-palindrome centered at the corresponding letter with length $2m + 3$. For a maximal sub-palindrome in $s$ centered at a gap, with length $m$, it corresponds in $s'$ to a maximal sub-palindrome centered at the $\#$ representing that gap with length $2m + 1$ (in both cases above, $m$ is even, but whether this property holds does not affect the conclusion). After combining the above observations and some calculations, it is easy to get that in $s'$, $d_1[i]$ represents **the total length plus one** of the maximal sub-palindrome in $s$ centered at the corresponding position.

The above conclusion establishes the relationship between $d_1[]$ of $s'$ and $d_1[]$ and $d_2[]$ of $s$.

Since this unified treatment is essentially computing $d_1[]$ of $s'$, after obtaining $s'$, the code is the same as in the previous section for computing $d_1[]$.

## Practice Problems

-   [UVa #11475 "Extend to Palindrome"](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2470)
-   [「National Team」Longest Double Palindrome](https://www.luogu.com.cn/problem/P4555)
-   [CF1326D2. Labyrinth](https://codeforces.com/contest/1326/problem/D2)

**This page is mainly translated from the article [Нахождение всех подпалиндромов](http://e-maxx.ru/algo/palindromes_count) and its English translation [Finding all sub-palindromes in $O(N)$](https://cp-algorithms.com/string/manacher.html). The Russian version is in the Public Domain with Leave a Link; the English version is under CC-BY-SA 4.0.**