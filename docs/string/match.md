This page gives a brief introduction to the string matching problem and its solutions.

## String Matching Problem

### Definition

Also known as pattern matching. The problem can be summarized as "given strings $S$ and $T$, find substring $T$ in the main string $S$". Character $T$ is called the pattern.

### Types

-   Single pattern matching: given a pattern and a text to match, find all positions of the pattern in the text.
-   Multiple pattern matching: given multiple patterns and a text to match, find all positions of these patterns in the text.
    -   When there are multiple texts to match, connecting them directly can be treated as one text.
    -   It can be treated directly as single pattern matching, but the efficiency is not high enough.
-   Other types: for example, matching any suffix of a string, matching any suffix of multiple strings......

## Brute Force

Abbreviated as BF (Brute Force) algorithm. The basic idea is to start from the first character of the main string $S$ and compare it with the first character of the pattern $T$; if they are equal, continue comparing the subsequent characters of both; otherwise, the pattern $T$ goes back to the first character and compares with the second character of the main string $S$. This repeats until all characters in $S$ or $T$ have been compared.

### Implementation

=== "C++"
    ```cpp
    /*
     * s: the main string to be matched
     * t: the pattern
     * n: length of the main string
     * m: length of the pattern
     */
    std::vector<int> match(char *s, char *t, int n, int m) {
      std::vector<int> ans;
      int i, j;
      for (i = 0; i < n - m + 1; i++) {
        for (j = 0; j < m; j++) {
          if (s[i + j] != t[j]) break;
        }
        if (j == m) ans.push_back(i);
      }
      return ans;
    }
    ```

=== "Python"
    ```python
    def match(s, t, n, m):
        if m < 1:
            return []
    
        ans = []
        for i in range(0, n - m + 1):
            for j in range(0, m):
                if s[i + j] != t[j]:
                    break
            else:
                ans.append(i)
        return ans
    ```

### Time Complexity

Let $n$ be the length of the main string and $m$ be the length of the pattern. By default $m \ll n$.

When BF algorithm matches successfully, in the best case, only one successful match occurs, with $m$ comparisons for this round, while each unsuccessful match occurs at the first character of the pattern, requiring $n-m$ more comparisons, so the total number of comparisons is $n$, giving time complexity $O(n)$; in the worst case, the number of successful matches is $n-m+1$, with $m$ comparisons per round, giving a total of $m(n-m+1)$ comparisons, so the time complexity is $O(mn)$.

When BF algorithm fails to match, in the best case, each unsuccessful match occurs at the first character of the pattern, requiring $n-m+1$ comparisons, giving time complexity $O(n)$; in the worst case, each unsuccessful match occurs at the last character of the pattern, requiring $m(n-m+1)$ comparisons, giving time complexity $O(mn)$.

If the pattern has at least two different characters, the average time complexity of BF algorithm is $O(n)$. However, in OI problems, the given strings are generally not purely random.

## Hash Method

See: [String Hash](./hash.md)

## KMP Algorithm

See: [Prefix Function and KMP Algorithm](./kmp.md)