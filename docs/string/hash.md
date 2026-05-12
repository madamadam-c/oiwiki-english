## Definition

We define a function $f$ that maps strings to integers, and this $f$ is called a Hash function.

We want this function $f$ to help us conveniently determine whether two strings are equal.

## Idea of Hash

The core idea of Hash is to map input to a small value range that can be easily compared.

??? warning "Warning"
    The meaning of "small value range" varies in different contexts.
    
    In [hash tables](../ds/hash.md), the value range needs to be small enough to accept linear space and time complexity.
    
    In string hashing, the value range needs to be small enough for fast comparison ($10^9$, $10^{18}$ are both fast to compare).
    
    At the same time, to reduce the hash collision rate, the value range cannot be too small either.

## Properties

Specifically, the most important properties of a hash function can be summarized as follows:

1.  When the hash function values are different, the two strings must be different;

2.  When the hash function values are the same, the two strings are not necessarily the same (but they are likely to be the same with high probability, and of course we would like them to always be the same).

    We call the phenomenon where the hash function values are the same but the original strings are different a hash collision.

## Explanation

What do we need to focus on?

Time complexity and the accuracy of Hash.

Typically, we use the polynomial Hash method. For a string $s$ of length $l$, we can define the polynomial Hash function as: $f(s) = \sum_{i=1}^{l} s[i] \times b^{l-i} \pmod M$. For example, for the string $xyz$, its hash function value is $xb^2+yb+z$.

It should be noted that many people use an alternative definition of the Hash function, namely $f(s) = \sum_{i=1}^{l} s[i] \times b^{i-1} \pmod M$. With this definition, the hash value of the same string $xyz$ becomes $x+yb+zb^2$.

Clearly, both definitions are viable, but the calculation formulas used for computing substring hash values (which will be discussed later) are different between the two. Therefore, be careful **not to confuse these two different Hash methods**.

Since the first definition is simpler to calculate, used by more people, and can be understood by analogy with a base-$b$ number, the discussion below will focus on the Hash function defined by $f(s) = \sum_{i=1}^{l} s[i] \times b^{l-i} \pmod M$.

Additionally, sometimes for convenience and to expand the modulus, we use `unsigned long long` in C++ to define the result of the Hash function. Due to C++'s characteristics, this effectively sets the modulus $M$ to $2^{64}$, which is also a good choice.

The accuracy will be discussed later.

## Analysis of Hash Error Rate

### Hash Collision

Hash collision refers to two different strings mapping to the same Hash value.

Let the value space of Hash (the number of all possible strings) be $d$, and the number of calculations (the number of strings to be calculated) be $n$.

Then the probability of Hash collision is:

$$
p(n,d) = 1 - \frac{d!}{d^n\left(d-n\right)!} \approx 1 - \exp(-\frac{n(n-1)}{2d} )
$$

??? note "Proof"
    When each value in Hash has equal probability of being generated, the probability of no collision is:
    
    $$
    \overline{p}(n,d) = 1 \cdot \left (1 - \frac{1}{d} \right) \cdot \left ( 1- \frac{2}{d}\right) \cdots \left ( 1- \frac{n-1}{d}\right)
    $$
    
    Simplifying gives:
    
    $$
    \begin{aligned}
    \overline{p}(n,d) 
    & = \frac{d}{d}\cdot \frac{d-1}{d}\cdot \frac{d-2}{d} \cdots \frac{d-n+1}{d}\\
    & = \frac{d\cdot (d-1)\cdot (d-2)\cdots(d-n+1)}{d^n}\\
    & = \frac{d!}{d^n\left(d-n\right)!}
    \end{aligned}
    $$
    
    Therefore, the probability of Hash collision is:
    
    $$
    p(n,d) = 1 - \frac{d!}{d^n\left(d-n\right)!}
    $$
    
    This formula is still too complex, so we simplify further.
    
    According to Taylor's formula:
    
    $$
    \exp(x) = \sum_{k=0}^{\infty}\frac{x^k}{k!}=1+x+\frac{x^2}{2}+\frac{x^3}{6}+\frac{x^4}{24}+\cdots
    $$
    
    When $x$ is an extremely small value, $\exp(x)$ approaches $1+x$.
    
    Substituting this into the original formula for no collision:
    
    $$
    \overline{p}(n,d) \approx 1 \cdot \exp(-\frac{1}{d}) \cdot \exp(-\frac{2}{d}) \cdots \exp(-\frac{n-1}{d})
    $$
    
    Simplifying:
    
    $$
    \begin{aligned}
    \overline{p}(n,d) & \approx \exp(-\frac{1}{d} - \frac{2}{d} - \cdots -\frac{n-1}{d})\\
    &=\exp(-\frac{n(n-1)}{2d} )
    \end{aligned}
    $$
    
    Therefore, the probability of Hash collision is:
    
    $$
    p(n,d) \approx 1 - \exp(-\frac{n(n-1)}{2d})
    $$

### Cracking Hash with Large Modulus

Notice this formula:

$$
p(n,d) \approx 1 - \exp(-\frac{n(n-1)}{2d} )
$$

To crack Hash, we need to satisfy the following conditions:

1.  $d$ must be greater than the modulus.
2.  $1-p(d,n)$ should be as small as possible.

For example:

If the character set is **uppercase and lowercase letters and digits**, and the modulus is $10^9+7$:

$\log_{62}10^9+7\approx 6$

$p(10^6,62^{6}) \approx 0.9$

Therefore, for this range, if we randomly generate $10^6$ strings of length $6$, the probability that they have the same Hash value is as high as $90\%$.

### Cracking Natural Overflow Hash

Since this Hash has too large a modulus, it cannot be cracked using the method above, so we need a different approach.

First, this Hash has the form $f(s) = \sum_{i=1}^{l} s[i] \times b^{l-i}$. We classify and discuss based on $b$.

#### When b is even

At this point, $f(s) = s_1\cdot b^l + s_2\cdot b^{l-1} + \cdots + s_l\cdot b \pmod M$, where $M$ is $2^{64}$.

It is easy to see that if $l \ge 64$, then $s_i\cdot b^l \equiv 0 \pmod M$.

So we just need to construct strings of length greater than $64$ in the form:

`aaa...a`

`baa...a`

to cause collision.

#### When b is odd

Define $!s_i$ as reversing all characters in $s_i$.

Example:

$s_i = abaab$

$!s_i = babba$

That is, change `a` to `b` and `b` to `a`.

Then define $hash_i$ as the Hash value of $s_i$, and $!hash_i$ as the Hash value of $!s_i$.

Continuously construct $s_i = s_{i-1} + !s_{i-1}$.

$s_{12}$ and $!s_{12}$ are the two strings we need.

??? note "Derivation"
    First, we have:
    
    $$
    \begin{aligned}
    hash_i = hash_{i-1}\cdot base^{2^{i-2}} + !hash_{i-1}\\
    !hash_{i} = !hash_{i-1}\cdot base^{2^{i-2}}+hash_{i-1}
    \end{aligned}
    $$
    
    Try subtracting:
    
    $$
    \begin{aligned}
    &hash_i - !hash_i\\
    =\ &hash_{i-1}\cdot base^{2^{i-2}} + !hash_{i-1}-(!hash_{i-1}\cdot base^{2^{i-2}}+hash_{i-1})\\
    =\ &(hash_{i-1}-!hash_{i-1})\cdot (base^{2^{i-2}}-1)
    \end{aligned}
    $$
    
    We find $2^i$ appears, but the original formula is too complex. Let's try substitution:
    
    Let:
    
    $$
    \begin{aligned}
    f_i = hash_i - !hash_i\\
    g_i = base^{2^{i-2}}-1
    \end{aligned}
    $$
    
    From the original formula:
    
    $$
    \begin{aligned}
    f_i &= f_{i-1} \cdot g_i\\
        &=f_1 \cdot g_1 \cdot g_2 \cdots g_{i-1}\\
    \end{aligned}
    $$
    
    Since $base^{2^{i-2}}$ is always odd, $g_i$ must be even.
    
    Therefore:
    
    $$
    2^{i-1} | f_i
    $$
    
    But this is too large, we need $i-1\ge 64$ to crack it. Continue simplifying:
    
    $$
    g_i = base^{2^{i-2}}-1 = (base^{2^{i-3}}-1)\cdot(base^{2^{i-3}}+1)\\
    $$
    
    That is, $g_i$ has the form $g_{i-1} \cdot c\ (c \equiv 0 \pmod 2)$.
    
    So $2 | s_1$, $4 | s_2$, ..., that is
    
    $$
    \begin{aligned}
    & 2^i &| g_i\\
    &2^1\cdot2^2\cdot2^3\cdots2^{i-1} &| f_i\\
    &2^{i(i-1)/2} &| f_i
    \end{aligned}
    $$
    
    That is, when $i=12$, we can make $2^{64} | hash_i - !hash_i$ to meet the requirements.

### Example Problems

???+ note "[Problem: BZOJ 3097 Hash Killer I](https://hydro.ac/p/bzoj-P3097)"
    Given a Hash implemented with **natural overflow**, construct a string to crack it.

???+ note "[Problem: BZOJ 3097 Hash Killer II](https://hydro.ac/p/bzoj-P3098)"
    Given a Hash implemented with **large modulus**, construct a string to crack it.

???+ note "[Problem: Luogu U461211 String Hash (Data Enhancement)](https://www.luogu.com.cn/problem/U461211)"
    Given $n$ strings, determine how many distinct strings there are.

## Improvements to Hash

### Multi-value Hash

After seeing so many ways to crack Hash above, there are of course solutions.

Multi-value Hash means having multiple hash functions, each with a different modulus. This solves the problem of hash collisions.

When judging, as long as one of the Hash values is different, the two strings are considered different. If all Hash values are the same, the two strings are considered the same.

Generally, double-value Hash is sufficient.

### Multiple Substring Hash Queries

The time complexity of computing the hash of a single string is $O(n)$, where $n$ is the string length, which is no different from brute force matching. If we need to query the hash of substrings of a string multiple times, recalculating each time is very inefficient.

The common approach is to preprocess the hash value for each prefix of the entire string, treating the hash value as the result of a base-$b$ number modulo $M$. This allows us to quickly compute the hash of substrings:

Let $f_i(s)$ denote $f(s[1..i])$, i.e., the hash value of the prefix of length $i$ of the original string. Then according to the definition, $f_i(s)=s[1]\cdot b^{i-1}+s[2]\cdot b^{i-2}+\dots+s[i-1]\cdot b+s[i]$

Now, we want to quickly compute $f(s[l..r])$ using a prefix-sum-like method. According to the definition, the hash value of string $s[l..r]$ is $f(s[l..r])=s[l]\cdot b^{r-l}+s[l+1]\cdot b^{r-l-1}+\dots+s[r-1]\cdot b+s[r]$

Comparing the two formulas above, we find that $f(s[l..r])=f_r(s)-f_{l-1}(s) \times b^{r-l+1}$ holds (you can manually substitute to verify). Therefore, we can use this formula to quickly get the hash of a substring. Here, $b^{r-l+1}$ can be preprocessed in $O(n)$ and then answered in $O(1)$ for each query (or computed with fast exponentiation in $O(\log n)$ for each query).

## Implementation

### Modulus Hash:

Note: Low efficiency, not recommended for practical use.

=== "C++"
    ```cpp
    using std::string;
    
    constexpr int M = 1e9 + 7;
    constexpr int B = 233;
    
    using ll = long long;
    
    int get_hash(const string& s) {
      int res = 0;
      for (int i = 0; i < s.size(); ++i) {
        res = ((ll)res * B + s[i]) % M;
      }
      return res;
    }
    
    bool cmp(const string& s, const string& t) {
      return get_hash(s) == get_hash(t);
    }
    ```

=== "Python"
    ```python
    M = int(1e9 + 7)
    B = 233
    
    
    def get_hash(s):
        res = 0
        for char in s:
            res = (res * B + ord(char)) % M
        return res
    
    
    def cmp(s, t):
        return get_hash(s) == get_hash(t)
    ```

### Double-value Hash:

=== "C++"
    ```cpp
    using ull = unsigned long long;
    ull base = 131;
    ull mod1 = 212370440130137957, mod2 = 1e9 + 7;
    
    ull get_hash1(std::string s) {
      int len = s.size();
      ull ans = 0;
      for (int i = 0; i < len; i++) ans = (ans * base + (ull)s[i]) % mod1;
      return ans;
    }
    
    ull get_hash2(std::string s) {
      int len = s.size();
      ull ans = 0;
      for (int i = 0; i < len; i++) ans = (ans * base + (ull)s[i]) % mod2;
      return ans;
    }
    
    bool cmp(const std::string s, const std::string t) {
      bool f1 = get_hash1(s) != get_hash1(t);
      bool f2 = get_hash2(s) != get_hash2(t);
      return f1 || f2;
    }
    ```

=== "Python"
    ```python
    def get_hash1(s: str) -> int:
        base = 131
        mod1 = 212370440130137957
        ans = 0
        for char in s:
            ans = (ans * base + ord(char)) % mod1
        return ans
    
    
    def get_hash2(s: str) -> int:
        base = 131
        mod2 = 1000000007
        ans = 0
        for char in s:
            ans = (ans * base + ord(char)) % mod2
        return ans
    
    
    def cmp(s: str, t: str) -> bool:
        f1 = get_hash1(s) != get_hash1(t)
        f2 = get_hash2(s) != get_hash2(t)
        return f1 or f2
    ```

## Applications of Hash

### String Matching

After computing the hash of the pattern string, compute the hash of each substring of the text string with the same length as the pattern string, and compare each with the hash of the pattern string.

### String Matching Allowing k Mismatches

Problem: Given a source string $s$ of length $n$, and a pattern string $p$ of length $m$, find how many substrings in the source string match the pattern string. $s'$ matches $s$ if and only if $s'$ has the same length as $s$, and at most $k$ positions have different characters. Here $1\leq n,m\leq 10^6$, $0\leq k\leq 5$.

This problem cannot be solved using KMP, but can be solved with hash + binary search.

Enumerate all possible matching substrings. Suppose the currently enumerated substring is $s'$. Using hash + binary search, we can quickly find the first different position between $s'$ and $p$. Then delete the part of $s'$ and $p$ from this mismatch position and before, and continue searching for the next mismatch position. This process occurs at most $k$ times.

The total time complexity is $O(m+kn\log_2m)$.

### Longest Palindromic Substring

Binary search the answer, and when checking feasibility, enumerate the palindrome center (axis of symmetry) and use hash to check if the two sides are equal. Need to preprocess both forward and reverse hash values. Time complexity is $O(n\log n)$.

This problem can be solved using the [Manacher algorithm](./manacher.md) in $O(n)$ time.

It can also be solved in $O(n)$ using hash. The specific method is to let $R_i$ denote the length of the longest palindrome ending at $i$. Then the answer is $\max_{i=1}^nR_i$. Considering that $R_i\leq R_{i-1}+2$, we only need to brute force starting from $R_{i-1}+2$ and decrease until finding the first palindrome. Let variable $z$ denote the current enumerated $R_i$, initially $0$. Then $z$ increases by $2$ each time $i$ increases, and decreases by $1$ during each brute force iteration. Therefore, the brute force loop executes at most $2n$ times, giving a total time complexity of $O(n)$.

### Longest Common Substring

Problem: Given $m$ non-empty strings with total length not exceeding $n$, find the longest common substring among all strings. If there are multiple, output any one of them. Here $1\leq m, n\leq 10^6$.

Clearly, if there exists a longest common substring of length $k$, then a common substring of length $k-1$ must also exist. Therefore, we can binary search the length of the longest common substring. Suppose the current length is $k$. The logic of `check(k)` is to hash all substrings of length $k$ from each string and store the hash values in $n$ hash tables. Then compute the intersection.

Time complexity is $O(m+n\log n)$.

### Counting Distinct Substrings in a String

Problem: Given a string of length $n$, consisting only of lowercase English letters, find the number of distinct substrings in this string.

To solve this problem, we iterate over all substrings of length $l=1,\cdots ,n$. For each length $l$, we multiply its Hash value by the same power of $b$ and store it in an array. The number of distinct elements in the array equals the number of distinct substrings of that length in the string, and this number is added to the final answer.

For convenience, we will use $h[i]$ as the prefix hash, and define $h[0]=0$.

??? note "Reference Code"
    ```cpp
    int count_unique_substrings(string const& s) {
      int n = s.size();
    
      constexpr static int b = 31;
      constexpr static int m = 1e9 + 9;
      vector<long long> b_pow(n);
      b_pow[0] = 1;
      for (int i = 1; i < n; i++) b_pow[i] = (b_pow[i - 1] * b) % m;
    
      vector<long long> h(n + 1, 0);
      for (int i = 0; i < n; i++)
        h[i + 1] = (h[i] + (s[i] - 'a' + 1) * b_pow[i]) % m;
    
      int cnt = 0;
      for (int l = 1; l <= n; l++) {
        set<long long> hs;
        for (int i = 0; i <= n - l; i++) {
          long long cur_h = (h[i + l] + m - h[i]) % m;
          cur_h = (cur_h * b_pow[n - i - 1]) % m;
          hs.insert(cur_h);
        }
        cnt += hs.size();
      }
      return cnt;
    }
    ```

### Example Problems

???+ note "[CF1200E Compress Words](http://codeforces.com/contest/1200/problem/E)"
    You are given several strings. The answer string initially starts empty. At step $i$, append the $i$-th string to the end of the answer string, but try to remove the overlapping part (i.e., remove the longest string that is both a suffix of the previous answer and a prefix of the $i$-th string). Find the final resulting string.
    
    The number of strings does not exceed $10^5$, and the total length does not exceed $10^6$.
    
    ??? note "Solution"
        Each time we need to find the longest string that is a suffix of the previous answer and a prefix of the $i$-th string. Enumerate the length of this string and compare using hash.
        
        Of course, this problem can also be solved using the [KMP algorithm](./kmp.md).
    
    ??? note "Reference Code"
        ```cpp
        --8<-- "docs/string/code/hash/hash_1.cpp"
        ```

**Parts of this page are translated from the blog post [строковый хеш](https://github.com/e-maxx-eng/e-maxx-eng/blob/61aff51f658644424c5e1b717f14fb7bf054ae80/src/string/string-hashing.md) and its English translation [String Hashing](https://cp-algorithms.com/string/string-hashing.html). The Russian version is under Public Domain + Leave a Link; the English version is under CC-BY-SA 4.0.**
