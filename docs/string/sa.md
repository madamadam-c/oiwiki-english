## Some Conventions

For definitions related to strings, refer to [String Basics](./basic.md).

String indices start from $1$.

The length of string $s$ is $n$.

"Suffix $i$" refers to the suffix starting at the $i$-th character. When storing, we use $i$ to represent the suffix $s[i\dots n]$ of string $s$.

## What is a Suffix Array?

The Suffix Array mainly involves two arrays: $sa$ and $rk$.

Here, $sa[i]$ represents the index of the $i$-th smallest suffix after sorting all suffixes, which is what we call the suffix array, also referred to as the index array $sa$ in later sections;

$rk[i]$ represents the rank of suffix $i$, which is an important auxiliary array, also referred to as the rank array $rk$ in later sections.

These two arrays satisfy the property: $sa[rk[i]]=rk[sa[i]]=i$.

### Explanation

Suffix array example:

[![](./images/sa1.png)][2]

## How to Compute a Suffix Array?

### O(n^2logn) Approach

I believe this approach can be figured out by anyone: sort the array containing all suffix strings using `sort`. Since the sorting performs $O(n\log n)$ string comparisons, and each string comparison requires $O(n)$ character comparisons, this sorting has a time complexity of $O(n^2\log n)$.

### O(nlog^2n) Approach

This approach uses the doubling technique.

First, sort all substrings of length $1$ of string $s$, i.e., each character, to obtain the sorted index array $sa_1$ and rank array $rk_1$.

Doubling process:

1. Using the ranks of two substrings of length $1$, i.e., $rk_1[i]$ and $rk_1[i+1]$, as the first and second sort keys, we can sort all substrings of length $2$ of string $s$: $\{s[i\dots \min(i+1, n)]\ |\ i \in [1,\ n]\}$ to obtain $sa_2$ and $rk_2$;

2. Then, using the ranks of two substrings of length $2$, i.e., $rk_2[i]$ and $rk_2[i+2]$, as the first and second sort keys, we can sort all substrings of length $4$ of string $s$: $\{s[i\dots \min(i+3, n)]\ |\ i \in [1,\ n]\}$ to obtain $sa_4$ and $rk_4$;

3. Continue this doubling: using the ranks of substrings of length $w/2$, i.e., $rk_{w/2}[i]$ and $rk_{w/2}[i+w/2]$, as the first and second sort keys, we can sort all substrings of length $w$ of string $s$: $s[i\dots \min(i+w-1,\ n)]$ to obtain $sa_w$ and $rk_w$. Here, similar to alphabetical order sorting, when $i+w>n$, $rk_w[i+w]$ is treated as negative infinity;

4. $rk_w[i]$ is the rank of substring $s[i\dots i + w - 1]$. When $w \geqslant n$, the resulting index array $sa_w$ is the suffix array we need.

#### Process

Doubling sorting diagram:

[![](./images/sa2.png)][2]

Obviously, the doubling process is $O(\log n)$, and each doubling uses `sort` to sort substrings in $O(n\log n)$, with each substring comparison requiring 2 character comparisons;

Additionally, after each `sort` sorting in doubling, there are extra $O(n)$ operations to update $rk$, but they are negligible compared to $O(n\log n)$;

Therefore, the time complexity of this algorithm is $O(n\log^2n)$.

??? note "Implementation"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    
    using namespace std;
    
    constexpr int N = 1000010;
    
    char s[N];
    int n, w, sa[N], rk[N << 1], oldrk[N << 1];
    
    // To prevent array out-of-bounds when accessing rk[i+w], allocate double-sized array.
    // Of course, we can also check for bounds before accessing, but directly allocating double-sized array is more convenient.
    
    int main() {
      int i, p;
    
      scanf("%s", s + 1);
      n = strlen(s + 1);
      for (i = 1; i <= n; ++i) sa[i] = i, rk[i] = s[i];
    
      for (w = 1; w < n; w <<= 1) {
        sort(sa + 1, sa + n + 1, [](int x, int y) {
          return rk[x] == rk[y] ? rk[x + w] < rk[y + w] : rk[x] < rk[y];
        });  // Using lambda here
        memcpy(oldrk, rk, sizeof(rk));
        // Since the original rk will be overwritten when computing rk, we need to copy it first.
        // If two substrings are identical, their corresponding rk should also be the same, so we need to deduplicate.
        for (p = 0, i = 1; i <= n; ++i) {
          if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
              oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
            rk[sa[i]] = p;
          } else {
            rk[sa[i]] = ++p;
          }
        }
      }
    
      for (i = 1; i <= n; ++i) printf("%d ", sa[i]);
    
      return 0;
    }
    ```

### O(nlogn) Approach

In the previous $O(n\log^2n)$ approach, single sorting is $O(n\log n)$. If we can sort in $O(n)$, we can compute the suffix array in $O(n\log n)$.

Prerequisites: [Counting Sort](../basic/counting-sort.md), [Radix Sort](../basic/radix-sort.md).

Since the sort keys during suffix array computation are ranks with a value range of $O(n)$, and it's a double-key sort, we can use radix sort to optimize to $O(n)$.

??? note "Implementation"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    
    using namespace std;
    
    constexpr int N = 1000010;
    
    char s[N];
    int n, sa[N], rk[N << 1], oldrk[N << 1], id[N], cnt[N];
    
    int main() {
      int i, m, p, w;
    
      scanf("%s", s + 1);
      n = strlen(s + 1);
      m = 127;
      for (i = 1; i <= n; ++i) ++cnt[rk[i] = s[i]];
      for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
      for (i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;
      memcpy(oldrk + 1, rk + 1, n * sizeof(int));
      for (p = 0, i = 1; i <= n; ++i) {
        if (oldrk[sa[i]] == oldrk[sa[i - 1]]) {
          rk[sa[i]] = p;
        } else {
          rk[sa[i]] = ++p;
        }
      }
    
      for (w = 1; w < n; w <<= 1, m = n) {
        // For second key: id[i] + w, use counting sort
        memset(cnt, 0, sizeof(cnt));
        memcpy(id + 1, sa + 1,
               n * sizeof(int));  // id stores a copy of sa, essentially equivalent to oldsa
        for (i = 1; i <= n; ++i) ++cnt[rk[id[i] + w]];
        for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i) sa[cnt[rk[id[i] + w]]--] = id[i];
    
        // For first key: id[i], use counting sort
        memset(cnt, 0, sizeof(cnt));
        memcpy(id + 1, sa + 1, n * sizeof(int));
        for (i = 1; i <= n; ++i) ++cnt[rk[id[i]]];
        for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i) sa[cnt[rk[id[i]]]--] = id[i];
    
        memcpy(oldrk + 1, rk + 1, n * sizeof(int));
        for (p = 0, i = 1; i <= n; ++i) {
          if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
              oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
            rk[sa[i]] = p;
          } else {
            rk[sa[i]] = ++p;
          }
        }
      }
    
      for (i = 1; i <= n; ++i) printf("%d ", sa[i]);
    
      return 0;
    }
    ```

### Some Constant Optimizations

If you submit the above code to [LOJ #111: Suffix Sort](https://loj.ac/problem/111):

![](./images/sa3.png)

This is because the constants in the above code are indeed quite large.

#### Second Key Doesn't Need Counting Sort

Consider the essence of sorting by the second key: it actually puts the $sa[i]$ that exceed the string range (i.e., $sa[i] + w > n$) at the head of the $sa$ array, then puts the rest in their original order:

```cpp
int cur = 0;
for (int i = n - w + 1; i <= n; i++) id[++cur] = i;
for (int i = 1; i <= n; i++)
  if (sa[i] > w) id[++cur] = sa[i] - w;
```

#### Optimize the Value Range of Counting Sort

Every time after updating $rk$, we compute a $p$, which is the value range of $rk$. We can change the value range to this $p$.

#### If All Ranks Are Different, the Suffix Array Can Be Generated Directly

Consider the new $rk$ array; if its value range is $[1,n]$, then every rank is different, and no further sorting is needed.

??? note "Implementation"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    
    using namespace std;
    
    constexpr int N = 1000010;
    
    char s[N];
    int n;
    int m, p, rk[N * 2], oldrk[N], sa[N * 2], id[N], cnt[N];
    
    int main() {
      scanf("%s", s + 1);
      n = strlen(s + 1);
      m = 128;
    
      for (int i = 1; i <= n; i++) cnt[rk[i] = s[i]]++;
      for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
      for (int i = n; i >= 1; i--) sa[cnt[rk[i]]--] = i;
    
      for (int w = 1;; w <<= 1, m = p) {  // m = p is the value range optimization
        int cur = 0;
        for (int i = n - w + 1; i <= n; i++) id[++cur] = i;
        for (int i = 1; i <= n; i++)
          if (sa[i] > w) id[++cur] = sa[i] - w;
    
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; i++) cnt[rk[i]]++;
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--) sa[cnt[rk[id[i]]]--] = id[i];
    
        p = 0;
        memcpy(oldrk, rk, sizeof(oldrk));
        for (int i = 1; i <= n; i++) {
          if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
              oldrk[sa[i] + w] == oldrk[sa[i - 1] + w])
            rk[sa[i]] = p;
          else
            rk[sa[i]] = ++p;
        }
    
        if (p == n) break;  // When p = n, no further sorting is needed
      }
    
      for (int i = 1; i <= n; i++) printf("%d ", sa[i]);
    
      return 0;
    }
    ```

### O(n) Approach

In typical problems, the doubling method with small constants for computing suffix arrays is fully sufficient. The parts other than computing the suffix array often also have $O(n\log n)$ complexity, so doubling for suffix array does not become a bottleneck.

However, if encountering special problems, time-critical problems, or if you want to pursue shorter execution time, you need to learn the $O(n)$ method for computing suffix arrays.

#### SA-IS

Refer to [Induced Sorting and SA-IS Algorithm](https://riteme.site/blog/2016-6-19/sais.html), and its [comment page](https://github.com/riteme/riteme.github.io/issues/28) also has reference value.

#### DC3

Refer to [\[2009\] Suffix Array — A Powerful Tool for String Processing by. Luo Suiqian][2].

## Applications of Suffix Array

### Finding the Minimum Cyclic Shift Position

Copy string $S$ to become $SS$, which transforms it into a suffix sorting problem.

Example problem: [「JSOI2007」Character Encryption](https://www.luogu.com.cn/problem/P4051).

### Finding Substrings in a String

The task is to online find pattern string $S$ in main string $T$. "Online" means we already know main string $T$ in advance, but we only know pattern string $S$ when queried. We can first construct the suffix array of $T$, then search for substring $S$. If substring $S$ appears in $T$, it must be a prefix of some suffixes of $T$. Since we have sorted all suffixes, we can implement this by binary searching $S$ in the $sa$ array. Comparing substring $S$ with the current suffix takes $O(|S|)$ time, so the time complexity of finding a substring is $O(|S|\log |T|)$. Note that if the substring appears multiple times in $T$, each occurrence is adjacent in the $sa$ array. Therefore, the number of occurrences can be found by another binary search, and outputting each occurrence position is also easy.

### Minimizing Lexicographic Order by Taking Characters from String Start or End

Example problem: [「USACO07DEC」Best Cow Line](https://www.luogu.com.cn/problem/P2870).

Problem description: Given a string, each time take one character from the start or end to form a string. Among all possible strings that can be formed, find the one with the smallest lexicographic order.

??? note "Solution"
    The brute force approach is to $O(n)$ determine whether to take from the start or end each time (i.e., compare the string obtained by taking from the start with the reverse string obtained by taking from the end). We only need to optimize this judgment process.
    
    Since we need to compare within the set consisting of suffixes of the original string and suffixes of the reversed string, we can concatenate the reversed string after the original string with a character that never appears in between (like `#`, we can directly use a null character in the code), compute the suffix array, and complete this judgment in $O(1)$.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/string/code/sa/sa_1.cpp"
    ```

## Height Array

### LCP (Longest Common Prefix)

The LCP of two strings $S$ and $T$ is the largest $x$ ($x\le \min(|S|, |T|)$) such that $S_i=T_i\ (\forall\ 1\le i\le x)$.

In the following text, we use $lcp(i,j)$ to denote the longest common prefix (length) of suffix $i$ and suffix $j$.

### Definition of Height Array

$height[i]=lcp(sa[i],sa[i-1])$, i.e., the longest common prefix between the suffix at rank $i$ and the suffix at rank $i-1$.

$height[1]$ can be considered as $0$.

### A Lemma for Computing Height Array in O(n)

$height[rk[i]]\ge height[rk[i-1]]-1$

???+ note "Proof"
    When $height[rk[i-1]]\le1$, the inequality obviously holds (right side is $\le 0$).
    
    When $height[rk[i-1]]>1$:
    
    According to the definition of $height$, we have $lcp(sa[rk[i-1]], sa[rk[i-1]-1]) = height[rk[i-1]] > 1$.
    
    Since suffix $i-1$ and suffix $sa[rk[i-1]-1]$ have a longest common prefix of length $height[rk[i-1]]$,
    
    let's denote this longest common prefix as $aA$ (where $a$ is a character, and $A$ is a non-empty string of length $height[rk[i-1]]-1$).
    
    Then suffix $i-1$ can be expressed as $aAD$, and suffix $sa[rk[i-1]-1]$ can be expressed as $aAB$ ($B < D$, $B$ may be empty, $D$ is non-empty).
    
    Furthermore, suffix $i$ can be expressed as $AD$, and there exists suffix ($sa[rk[i-1]-1]+1$) $AB$.
    
    Since suffix $sa[rk[i]-1]$ is only one rank below suffix $sa[rk[i]]$ (i.e., suffix $i$) in the ranking, and $AB < AD$.
    
    Therefore, $AB \le$ suffix $sa[rk[i]-1] < AD$. Obviously, suffix $i$ and suffix $sa[rk[i]-1]$ share prefix $A$.
    
    Thus we can conclude that $lcp(i,sa[rk[i]-1])$ is at least $height[rk[i-1]]-1$, i.e., $height[rk[i]]\ge height[rk[i-1]]-1$.

### Code Implementation for Computing Height Array in O(n)

We can use the above lemma to compute it by brute force:

```cpp
for (i = 1, k = 0; i <= n; ++i) {
  if (rk[i] == 0) continue;
  if (k) --k;
  while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
  height[rk[i]] = k;
}
```

$k$ does not exceed $n$, it decreases at most $n$ times, so it increases at most $2n$ times. The total complexity is $O(n)$.

## Applications of Height Array

### Longest Common Prefix of Two Substrings

$lcp(sa[i],sa[j])=\min\{height[i+1..j]\}$

Intuitive understanding: if $height$ is always greater than some value, the first many characters remain unchanged; conversely, since suffixes are sorted, it cannot change and then change back.

For a rigorous proof, refer to [\[2004\] Suffix Array by. Xu Zhilei][1].

With this theorem, computing the longest common prefix of two substrings reduces to an [RMQ Problem](../topic/rmq.md).

### Comparing the Size Relationship of Two Substrings of a String

Assume we need to compare $A=S[a..b]$ and $B=S[c..d]$.

If $lcp(a, c)\ge\min(|A|, |B|)$, then $A<B\iff |A|<|B|$.

Otherwise, $A<B\iff rk[a]< rk[c]$.

### Number of Distinct Substrings

A substring is a prefix of a suffix. So we can enumerate each suffix, calculate the total number of prefixes, then subtract duplicates.

The "total number of prefixes" is actually the number of substrings, which is $n(n+1)/2$.

If we enumerate suffixes in the order of sorted suffixes, the new substrings added each time are the prefixes remaining after subtracting the LCP with the previous suffix. These prefixes must be new; otherwise, it would violate the property $lcp(sa[i],sa[j])=\min\{height[i+1..j]\}$. Only these prefixes are new because the LCP part was counted when enumerating the previous prefix.

Therefore, the answer is:

$\frac{n(n+1)}{2}-\sum\limits_{i=2}^nheight[i]$

### Maximum Length of Substring Appearing at Least k Times

Example problem: [「USACO06DEC」Milk Patterns](https://www.luogu.com.cn/problem/P2852).

??? note "Solution"
    Appearing at least $k$ times means that after suffix sorting, there are at least $k$ consecutive suffixes with this substring as their common prefix.
    
    Therefore, find the minimum value among each group of $k-1$ adjacent $height$ values, and the maximum of these minimum values is the answer.
    
    This can be solved using a monotonic queue in $O(n)$, but other methods are also sufficient to pass.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/string/code/sa/sa_2.cpp"
    ```

### Whether a Certain String Appears at Least Twice Non-overlappingly in the Text String

We can binary search the length $|s|$ of the target string, divide the $h$ array into several consecutive segments where LCP is greater than or equal to $|s|$. Use RMQ to find the maximum and minimum indices among the numbers appearing in each segment. If the distance between these two indices satisfies the condition, then there must be a string of length $|s|$ appearing twice non-overlappingly.

### Consecutive Identical Substrings

We can enumerate the length $|s|$ of the consecutive string, divide the entire string into blocks according to $|s|$, and perform LCP and LCS queries on the block headers of adjacent blocks. For details, see [\[2009\] Suffix Array — A Powerful Tool for String Processing][2].

Example problem: [「NOI2016」Excellent Splitting](https://loj.ac/p/2083).

### Combined with Disjoint Set Union (DSU)

Some problems require dividing the suffix array into several consecutive segments where LCP length is greater than or equal to a certain value, i.e., dividing the $h$ array into several consecutive segments where the minimum value is greater than or equal to a certain value, and counting the answer for each segment. If there are multiple queries, we can process them offline. Observe that when the given value decreases monotonically, the number of satisfying intervals always decreases, and new intervals are formed by connecting two or more original intervals. Moreover, in new intervals, the $h$ values of parts not included in the original intervals are all equal to this decreased value. We only need to maintain a DSU, merging adjacent intervals each time and maintaining statistical information.

Classic problem: [「NOI2015」Banquet](https://uoj.ac/problem/131)

### Combined with Segment Tree

Some problems ask to find the first several numbers satisfying the condition, and these numbers lie in an interval in the suffix sorting. At this time, we can use the property of merge sort to merge information from two nodes, and use a segment tree to maintain and query interval answers.

### Combined with Monotonic Stack

Example problem: [「AHOI2013」Difference](https://loj.ac/problem/2377)

??? note "Solution"
    The first two terms of the summand are easy to handle, being $n(n-1)(n+1)/2$ (each suffix appears $n-1$ times, and the total length of suffixes is $n(n+1)/2$). The key is the last term, i.e., the pairwise LCP of suffixes.
    
    We know that $lcp(i,j)=k$ is equivalent to $\min\{height[i+1..j]\}=k$. Therefore, we can record $lcp(i,j)$ as $\min\{x|i+1\le x\le j, height[x]=lcp(i,j)\}$'s contribution to the answer.
    
    Consider the contribution of each position to the answer: which suffixes' LCP it is. Actually, it's from the suffixes starting from it to the left that have several consecutive $height$ greater than it, choose one, and from the suffixes to the right that have several consecutive $height$ not less than it, choose one. This can be computed using a [Monotonic Stack](../ds/monotonous-stack.md).
    
    The monotonic stack part is similar to [Luogu P2659 Beautiful Sequence](https://www.luogu.com.cn/problem/P2659) and [Suspended Line Method](../misc/hoverline.md).

??? note "Reference Code"
    ```cpp
    --8<-- "docs/string/code/sa/sa_3.cpp"
    ```

Similar problems: [「HAOI2016」Finding Identical Characters](https://loj.ac/problem/2064).

## Practice Problems

-   [UVa 760 - DNA Sequencing](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=701)
-   [UVa 1223 - Editor](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3664)
-   [Codechef - Tandem](https://www.codechef.com/problems/TANDEM)
-   [Codechef - Substrings and Repetitions](https://www.codechef.com/problems/ANUSAR)
-   [Codechef - Entangled Strings](https://www.codechef.com/problems/TANGLED)
-   [Codeforces - Martian Strings](http://codeforces.com/problemset/problem/149/E)
-   [Codeforces - Little Elephant and Strings](http://codeforces.com/problemset/problem/204/E)
-   [SPOJ - Ada and Terramorphing](http://www.spoj.com/problems/ADAPHOTO/)
-   [SPOJ - Ada and Substring](http://www.spoj.com/problems/ADASTRNG/)
-   [UVa - 1227 - The longest constant gene](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=3668)
-   [SPOJ - Longest Common Substring](http://www.spoj.com/problems/LCS/en/)
-   [UVa 11512 - GATTACA](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2507)
-   [QOJ 11240 - Suffixes and Palindromes](https://qoj.ac/problem/11240)
-   [GYM - Por Costel and the Censorship Committee](http://codeforces.com/gym/100923/problem/D)
-   [UVa 1254 - Top 10](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3695)
-   [UVa 12191 - File Recover](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3343)
-   [UVa 12206 - Stammering Aliens](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=3358)
-   [Codechef - Jarvis and LCP](https://www.codechef.com/problems/INSQ16F)
-   [Luogu P8617 - Repeated Pattern](https://www.luogu.com.cn/problem/P8617)
-   [UVa 11107 - Life Forms](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2048)
-   [UVa 12974 - Exquisite Strings](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=862&page=show_problem&problem=4853)
-   [UVa 10526 - Intellectual Property](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&page=show_problem&problem=1467)
-   [UVa 12338 - Anti-Rhyme Pairs](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=3760)
-   [DevSkills Reconstructing Blue Print of Life](https://devskill.com/CodingProblems/ViewProblem/328)
-   [UVa 12191 - File Recover](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3343)
-   [SPOJ - Suffix Array](http://www.spoj.com/problems/SARRAY/)
-   [Gym 102470J - Stammering Aliens](https://codeforces.com/gym/102470/problem/J)
-   [SPOJ - LCS2](http://www.spoj.com/problems/LCS2/)
-   [Codeforces - Fake News (hard)](http://codeforces.com/contest/802/problem/I)
-   [SPOJ - Longest Commong Substring](http://www.spoj.com/problems/LONGCS/)
-   [SPOJ - Lexicographical Substring Search](http://www.spoj.com/problems/SUBLEX/)
-   [Codeforces - Forbidden Indices](http://codeforces.com/contest/873/problem/F)
-   [Codeforces - Tricky and Clever Password](http://codeforces.com/contest/30/problem/E)
-   [Gym 101470B - Circle of digits](https://codeforces.com/gym/101470/problem/B)

## References

This page (introduced in [4070a9b](https://github.com/OI-wiki/OI-wiki/pull/950/commits/4070a9b3db8576db16c74d3ec33806ad10476eef)) is mainly translated from the article [Суффиксный массив](http://e-maxx.ru/algo/suffix_array) and its English translation [Suffix Array](https://cp-algorithms.com/string/suffix-array.html). The Russian version is in the Public Domain with Leave a Link; the English version is under CC-BY-SA 4.0.

Papers:

1.  [\[2004\] Suffix Array by. Xu Zhilei][1]

2.  [\[2009\] Suffix Array — A Powerful Tool for String Processing by. Luo Suiqian][2]

[1]: https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2004%E8%AE%BA%E6%96%87%E9%9B%86/%E8%AE%B8%E6%99%BA%E7%A3%8A--%E5%90%8E%E7%BC%80%E6%95%B0%E7%BB%84.pdf "[2004] Suffix Array by. Xu Zhilei"

[2]: https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2009%E8%AE%BA%E6%96%87%E9%9B%86/11.%E7%BD%97%E7%A9%97%E9%AA%9E%E3%80%8A%E5%90%8E%E7%BC%80%E6%95%B0%E7%BB%84%E2%80%94%E2%80%94%E5%A4%84%E7%90%86%E5%AD%97%E7%AC%A6%E4%B8%B2%E7%9A%84%E6%9C%89%E5%8A%9B%E5%B7%A5%E5%85%B7%E3%80%8B/%E5%90%8E%E7%BC%80%E6%95%B0%E7%BB%84%E2%80%94%E2%80%94%E5%A4%84%E7%90%86%E5%AD%97%E7%AC%A6%E4%B8%B2%E7%9A%84%E6%9C%89%E5%8A%9B%E5%B7%A5%E5%85%B7.pdf "[2009] Suffix Array — A Powerful Tool for String Processing by. Luo Suiqian"