author: LeoJacob, Marcythm, minghu6

Convention: string indices start from $0$.

## Definition

For a string $s$ of length $n$, define the function $z[i]$ to represent the length of the longest common prefix (LCP) between $s$ and $s[i,n-1]$ (i.e., the suffix starting at $s[i]$), then $z$ is called the **Z-function** of $s$. In particular, $z[0] = 0$.

Foreign literature generally refers to the algorithm for computing this array as the **Z Algorithm**, while domestic literature calls it **extended KMP** (exKMP).

This article introduces the algorithm for computing the Z-function in $O(n)$ time complexity and its various applications.

## Explanation

The following examples show the Z-function for different strings:

-   $z(\mathtt{aaaaa}) = [0, 4, 3, 2, 1]$
-   $z(\mathtt{aaabaab}) = [0, 2, 1, 0, 2, 1, 0]$
-   $z(\mathtt{abacaba}) = [0, 0, 1, 0, 3, 0, 1]$

## Naive Algorithm

The naive algorithm for Z-function has $O(n^2)$ complexity:

???+ note "Implementation"
    === "C++"
        ```cpp
        vector<int> z_function_trivial(string s) {
          int n = (int)s.length();
          vector<int> z(n);
          for (int i = 1; i < n; ++i)
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
          return z;
        }
        ```
    
    === "Python"
        ```python
        def z_function_trivial(s):
            n = len(s)
            z = [0] * n
            for i in range(1, n):
                while i + z[i] < n and s[z[i]] == s[i + z[i]]:
                    z[i] += 1
            return z
        ```

## Linear Algorithm

Like most algorithms introduced for string topics, the key is to use the idea of an automaton to find the state transition function under constraints, so that we can use previously computed states to accelerate the calculation of new states.

In this algorithm, we compute $z[i]$ for $i$ from $1$ to $n-1$ sequentially ($z[0]=0$). While computing $z[i]$, we utilize the already computed $z[0],\ldots,z[i-1]$.

For $i$, the interval $[i,i+z[i]-1]$ is called the **matching segment** of $i$, also called a Z-box.

During the algorithm, we maintain the matching segment whose right endpoint is furthest to the right. For convenience, denote it as $[l,r]$. By definition, $s[l,r]$ is a prefix of $s$. When computing $z[i]$, we ensure $l\le i$. Initially $l=r=0$.

When computing $z[i]$:

-   If $i\le r$, then by the definition of $[l,r]$, we have $s[i,r] = s[i-l,r-l]$, so $z[i]\ge \min(z[i-l],r-i+1)$. In this case:
    -   If $z[i-l] < r-i+1$, then $z[i] = z[i-l]$.
    -   Otherwise $z[i-l]\ge r-i+1$, in which case we set $z[i] = r-i+1$, then brute-force enumerate the next character to extend $z[i]$ until it cannot be extended.
-   If $i>r$, then we directly follow the naive algorithm, starting from $s[i]$, to brute-force compute $z[i]$.
-   After computing $z[i]$, if $i+z[i]-1>r$, we need to update $[l,r]$, i.e., set $l=i, r=i+z[i]-1$.

You can visit [this website](https://personal.utdallas.edu/~besp/demo/John2010/z-algorithm.htm) to see a simulation of the Z-function.

### Implementation

=== "C++"
    ```cpp
    vector<int> z_function(string s) {
      int n = (int)s.length();
      vector<int> z(n);
      for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r && z[i - l] < r - i + 1) {
          z[i] = z[i - l];
        } else {
          z[i] = max(0, r - i + 1);
          while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        }
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
      }
      return z;
    }
    ```

=== "Python"
    ```python
    def z_function(s):
        n = len(s)
        z = [0] * n
        l, r = 0, 0
        for i in range(1, n):
            if i <= r and z[i - l] < r - i + 1:
                z[i] = z[i - l]
            else:
                z[i] = max(0, r - i + 1)
                while i + z[i] < n and s[z[i]] == s[i + z[i]]:
                    z[i] += 1
            if i + z[i] - 1 > r:
                l = i
                r = i + z[i] - 1
        return z
    ```

## Complexity Analysis

For the inner `while` loop, each execution moves $r$ forward by at least 1 position, and $r < n-1$, so it executes at most $n$ times in total.

For the outer loop, there is only one linear traversal.

Total complexity is $O(n)$.

## Applications

Now we consider applications of the Z-function in several specific cases.

These applications are largely similar to those of the [prefix function](./kmp.md).

### Matching All Substrings

To avoid confusion, we call $t$ the **text** and $p$ the **pattern**. The problem given is: find all occurrences of pattern $p$ in text $t$.

To solve this problem, we construct a new string $s = p + \diamond + t$, i.e., we concatenate $p$ and $t$ together, but place a separator character $\diamond$ in between (we choose $\diamond$ such that it definitely does not appear in $p$ or $t$).

First compute the Z-function of $s$. Then, for any $i$ in the range $[0,|t| - 1]$, consider the Z-function value $k = z[i + |p| + 1]$ of the suffix starting at $t[i]$ in $s$. If $k = |p|$, then we know there is an occurrence of $p$ at position $i$ in $t$, otherwise there is no occurrence of $p$ at position $i$ in $t$.

Its time complexity (and also space complexity) is $O(|t| + |p|)$.

### Number of Distinct Substrings

Given a string $s$ of length $n$, compute the number of distinct substrings of $s$.

Consider computing incrementally, i.e., given the number of distinct substrings of the current $s$, compute the number of distinct substrings after adding one character at the end of $s$.

Let $k$ be the number of distinct substrings of the current $s$. We add a new character $c$ to the end of $s$. Obviously, some new substrings ending with $c$ will appear (substrings ending with $c$ that did not appear before).

Let $t$ be the reversed string of $s + c$ (the reversed string is the string formed by reversing the characters of the original string). Our task is to count how many prefixes of $t$ do not appear elsewhere in $t$. Consider computing the Z-function of $t$ and finding its maximum value $z_{\max}$. Then the reverse of prefixes of $t$ with length $\le z_{\max}$ are already appeared substrings ending with $c$ in $s$.

Therefore, the number of new substrings after adding character $c$ to $s$ is $|t| - z_{\max}$.

The algorithm has $O(n^2)$ time complexity.

It is worth noting that we can use the same method to recompute the number of distinct substrings after adding or removing a character at either end in $O(n)$ time.

### String Period

Given a string $s$ of length $n$, find its shortest full period, i.e., find the shortest string $t$ such that $s$ can be represented by concatenating several copies of $t$.

Consider computing the Z-function of $s$, then the length of its full period is the smallest divisor $i$ of $n$ such that $i+z[i]=n$.

The proof of this fact is the same as for the [prefix function](./kmp.md).

## Practice Problems

-   [luogu P5410【Template】Extended KMP/exKMP (Z Function)](https://www.luogu.com.cn/problem/P5410)
-   [luogu P7114【NOIP2020】String Matching](https://www.luogu.com.cn/problem/P7114)
-   [CF126B Password](http://codeforces.com/problemset/problem/126/B)
-   [UVa # 455 Periodic Strings](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=396)
-   [UVa # 11022 String Factoring](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1963)
-   [UVa 11475 - Extend to Palindrome](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2470)
-   [Codechef - Chef and Strings](https://www.codechef.com/problems/CHSTR)
-   [Codeforces - Prefixes and Suffixes](http://codeforces.com/problemset/problem/432/D)
-   [Leetcode 2223 - Sum of Scores of Built Strings](https://leetcode.com/problems/sum-of-scores-of-built-strings/)

**This page is mainly translated from the blog post [Z-функция строки и её вычисление](http://e-maxx.ru/algo/z_function) and its English translation [Z-function and its calculation](https://cp-algorithms.com/string/z-function.html). The Russian version is in the Public Domain + Leave a Link; the English version is under CC-BY-SA 4.0.**