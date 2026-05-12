author: Ir1d, LeoJacob, Xeonacid, greyqz, StudyingFather, Marcythm, minghu6, Backl1ght

## String Prefix and Suffix Definitions

For definitions of string prefix, proper prefix, suffix, and proper suffix, see [String Basics](./basic.md).

## Prefix Function

### Definition

Given a string $s$ of length $n$, its **prefix function** is defined as an array $\pi$ of length $n$.
The definition of $\pi[i]$ is:

1. If the substring $s[0\dots i]$ has a pair of equal proper prefix and proper suffix: $s[0\dots k-1]$ and $s[i - (k - 1) \dots i]$, then $\pi[i]$ is the length of this equal proper prefix (or proper suffix, since they are equal), i.e., $\pi[i]=k$;
2. If there is more than one such pair, then $\pi[i]$ is the length of the longest one;
3. If there are no equal pairs, then $\pi[i]=0$.

Simply put, $\pi[i]$ is the length of the longest equal proper prefix and proper suffix of the substring $s[0\dots i]$.

In mathematical terms:

$$
\pi[i] = \max_{k = 0 \dots i}\{k: s[0 \dots k - 1] = s[i - (k - 1) \dots i]\}
$$

By convention, $\pi[0]=0$.

### Process

For example, for the string `abcabcd`:

$\pi[0]=0$, because `a` has no proper prefix and proper suffix, by convention it is 0

$\pi[1]=0$, because `ab` has no equal proper prefix and proper suffix

$\pi[2]=0$, because `abc` has no equal proper prefix and proper suffix

$\pi[3]=1$, because `abca` has only one pair of equal proper prefix and proper suffix: `a`, length 1

$\pi[4]=2$, because `abcab` has equal proper prefix and proper suffix only `ab`, length 2

$\pi[5]=3$, because `abcabc` has equal proper prefix and proper suffix only `abc`, length 3

$\pi[6]=0$, because `abcabcd` has no equal proper prefix and proper suffix

Similarly, the prefix function for the string `aabaaab` is $[0, 1, 0, 1, 2, 2, 3]$.

## Naive Algorithm for Computing Prefix Function

### Process

A direct algorithm for computing the prefix function according to its definition:

-   Compute the prefix function values $\pi[i]$ in a loop with $i = 1\to n - 1$ ( $\pi[0]$ is set to $0$ ).
-   To compute the current prefix function value $\pi[i]$, we let variable $j$ start from the maximum proper prefix length $i$.
-   If the proper prefix and proper suffix are equal at the current length, then this length is $\pi[i]$; otherwise, decrement $j$ and continue matching until $j=0$.
-   If $j = 0$ and there has been no match yet, set $\pi[i] = 0$ and move to the next index $i + 1$.

???+ note "Implementation"
    The implementation is as follows:
    
    === "C++"
        ```cpp
        // Note:
        // string substr (size_t pos = 0, size_t len = npos) const;
        vector<int> prefix_function(string s) {
          int n = (int)s.length();
          vector<int> pi(n);
          for (int i = 1; i < n; i++)
            for (int j = i; j >= 0; j--)
              if (s.substr(0, j) == s.substr(i - j + 1, j)) {
                pi[i] = j;
                break;
              }
          return pi;
        }
        ```
    
    === "Python"
        ```python
        def prefix_function(s):
            n = len(s)
            pi = [0] * n
            for i in range(1, n):
                for j in range(i, -1, -1):
                    if s[0:j] == s[i - j + 1 : i + 1]:
                        pi[i] = j
                        break
            return pi
        ```
    
    === "Java"
        ```java
        static int[] prefix_function(String s) {
            int n = s.length();
            int[] pi = new int[n];
            for (int i = 1; i < n; i++) {
                for (int j = i; j >= 0; j--) {
                    if (s.substring(0, j).equals(s.substring(i - j + 1, i + 1))) {
                        pi[i] = j;
                        break;
                    }
                }
            }
            return pi;
        }
        ```

Obviously, the time complexity of this algorithm is $O(n^3)$, which has great room for improvement.

## Efficient Algorithm for Computing Prefix Function

### First Optimization

The first important observation is that **adjacent prefix function values can increase by at most 1**.

As shown in the figure below, when taking the largest possible $\pi[i+1]$, it must require the new character $s[i+1]$ to match the corresponding character, i.e., $s[i+1]=s[\pi[i]]$, in which case $\pi[i+1] = \pi[i]+1$.

$$
\underbrace{\overbrace{s_0 ~ s_1 ~ s_2}^{\pi[i] = 3} ~ s_3}_{\pi[i+1] = 4} ~ \dots ~ \underbrace{\overbrace{s_{i-2} ~ s_{i-1} ~ s_{i}}^{\pi[i] = 3} ~ s_{i+1}}_{\pi[i+1] = 4}
$$

So when moving to the next position, the prefix function value either increases by one, stays the same, or decreases.

???+ note "Implementation"
    The improved algorithm at this stage is:
    
    === "C++"
        ```cpp
        vector<int> prefix_function(string s) {
          int n = (int)s.length();
          vector<int> pi(n);
          for (int i = 1; i < n; i++)
            for (int j = pi[i - 1] + 1; j >= 0; j--)  // improved: j=i => j=pi[i-1]+1
              if (s.substr(0, j) == s.substr(i - j + 1, j)) {
                pi[i] = j;
                break;
              }
          return pi;
        }
        ```
    
    === "Python"
        ```python
        def prefix_function(s):
            n = len(s)
            pi = [0] * n
            for i in range(1, n):
                for j in range(pi[i - 1] + 1, -1, -1):
                    if s[0:j] == s[i - j + 1 : i + 1]:
                        pi[i] = j
                        break
            return pi
        ```
    
    === "Java"
        ```java
        static int[] prefix_function(String s) {
            int n = s.length();
            int[] pi = new int[n];
            for (int i = 1; i < n; i++) {
                for (int j = pi[i - 1] + 1; j >= 0; j--) {
                    if (s.substring(0, j).equals(s.substring(i - j + 1, i + 1))) {
                        pi[i] = j;
                        break;
                    }
                }
            }
            return pi;
        }
        ```

In this initially improved algorithm, when computing each $\pi[i]$, the best case is that the first string comparison completes the match, meaning the base number of string comparisons is `n-1`.

And because of the constraint `j = pi[i-1]+1` (`pi[0]=0`) on the maximum number of string comparisons, it can be seen that each time only in the best case will the upper limit of string comparisons accumulate by 1, and any additional string comparisons consume the room for later growth.

From this, we can derive the worst case for the number of string comparisons: at least 1 string comparison consumption and at most `n-2` comparison accumulations, making the total number of string comparisons `n-1 + n-2 = 2n-3`.

Thus, after this optimization, computing the prefix function only requires $O(n)$ string comparisons, reducing the total complexity to $O(n^2)$.

### Second Optimization

In the first optimization, we discussed the best case when computing $\pi[i+1]$: $s[i+1]=s[\pi[i]]$, in which case $\pi[i+1] = \pi[i]+1$. Now let's go further along this line: discuss how to transition when $s[i+1] \neq s[\pi[i]]$.

![](images/prefix_str_1.svg)

As shown in the figure, when a mismatch occurs, we want to find for the substring $s[0\dots i]$ the second longest length $j$ (second to $\pi[i]$) such that the prefix property still holds at position $i$, i.e., $s[0 \dots j - 1] = s[i - j + 1 \dots i]$:

$$
\overbrace{\underbrace{s_0 ~ s_1}_j ~ s_2 ~ s_3}^{\pi[i]} ~ \dots ~ \overbrace{s_{i-3} ~ s_{i-2} ~ \underbrace{s_{i-1} ~ s_{i}}_j}^{\pi[i]} ~ s_{i+1}
$$

If we find such length $j$, then we only need to compare $s[i + 1]$ and $s[j]$ again. If they are equal, then $\pi[i + 1] = j + 1$. Otherwise, we need to find the second longest length $j^{(2)}$ for the substring $s[0\dots i]$ that maintains the prefix property, and so on, until $j = 0$. If $s[i + 1] \neq s[0]$, then $\pi[i + 1] = 0$. The second comparison is shown in the figure below.

![](images/prefix_str_2.svg)

Observing the figure, because $s[0\dots \pi[i]-1] = s[i-\pi[i]+1\dots i]$, for the second longest length $j$ of $s[0\dots i]$, we have the property:

$$
s[0 \dots j - 1] = s[i - j + 1 \dots i]= s[\pi[i]-j\dots \pi[i]-1]
$$

A diagram of this formula is shown below:

![](images/prefix_str_3.svg)

That is, $j$ is equivalent to the prefix function value of the substring $s[\pi[i]-1]$, corresponding to the lower half of the figure above, i.e., $j=\pi[\pi[i]-1]$. Similarly, the second longest length to $j$ is equivalent to the prefix function value of $s[j-1]$, i.e., $j^{(2)}=\pi[j-1]$.

Obviously, we can obtain a state transition equation for $j$: $j^{(n)}=\pi[j^{(n-1)}-1], \ \ (j^{(n-1)}>0)$

### Final Algorithm

Thus, we can finally build an algorithm that requires no string comparisons at all and only performs $O(n)$ operations.

And the implementation is surprisingly short and intuitive:

???+ note "Implementation"
    === "C++"
        ```cpp
        vector<int> prefix_function(string s) {
          int n = (int)s.length();
          vector<int> pi(n);
          for (int i = 1; i < n; i++) {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j]) j = pi[j - 1];
            if (s[i] == s[j]) j++;
            pi[i] = j;
          }
          return pi;
        }
        ```
    
    === "Python"
        ```python
        def prefix_function(s):
            n = len(s)
            pi = [0] * n
            for i in range(1, n):
                j = pi[i - 1]
                while j > 0 and s[i] != s[j]:
                    j = pi[j - 1]
                if s[i] == s[j]:
                    j += 1
                pi[i] = j
            return pi
        ```
    
    === "Java"
        ```java
        static int[] prefix_function(String s) {
            int n = s.length();
            int[] pi = new int[n];
            for (int i = 1; i < n; i++) {
                int j = pi[i - 1];
                while (j > 0 && s.charAt(i) != s.charAt(j)) {
                    j = pi[j - 1];
                }
                if (s.charAt(i) == s.charAt(j)) {
                    j++;
                }
                pi[i] = j;
            }
            return pi;
        }
        ```

This is an **online** algorithm, i.e., it processes data as it arrives—for example, you can read the string character by character and immediately process them to compute the prefix function value for each character. This algorithm still needs to store the string itself and the previously computed prefix function values, but if we already know the maximum possible value $M$ of the prefix function for this string, then we only need to store the first $M + 1$ characters of the string and the corresponding prefix function values.

## Applications

### Finding a Substring in a String: Knuth–Morris–Pratt Algorithm

This algorithm was jointly published by Knuth, Pratt, and Morris in 1977[^kmp]. This task is a typical application of the prefix function.

#### Process

Given a text $t$ and a string $s$, we try to find and display all occurrences of $s$ in $t$.

For convenience, we use $n$ to denote the length of string $s$, and $m$ to denote the length of text $t$.

We construct a string $s + \# + t$, where $\#$ is a delimiter that appears in neither $s$ nor $t$. Then we compute the prefix function of this string. Now consider the meaning of the prefix function values after excluding the first $n + 1$ values (i.e., those belonging to string $s$ and the delimiter). By definition, $\pi[i]$ is the length of the longest proper substring that ends at $i$ and is simultaneously a prefix. In our specific case, it is the length of the longest substring ending at $i$ that matches a prefix of $s$. Due to the presence of the delimiter, this length cannot exceed $n$. And if the equation $\pi[i] = n$ holds, it means that $s$ appears completely at that position (i.e., its right end is at position $i$). Note that the position index is in terms of the string $s + \# + t$.

Therefore, if at some position $i$ we have $\pi[i] = n$, then string $s$ appears at position $i - (n - 1) - (n + 1) = i - 2n$ in string $t$. The following figure shows the index diagram.

![](images/strstr_kmp_indices.svg)

As already mentioned in computing the prefix function, if we know that the prefix function values never exceed a certain value, then we don't need to store the entire string and the entire prefix function, but only the beginning of both. In our case, this means we only need to store the string $s + \#$ and the corresponding prefix function values. We can read the string $t$ one character at a time and compute the prefix function value for the current position.

Thus, the Knuth–Morris–Pratt algorithm (KMP algorithm for short) solves this problem in $O(n + m)$ time and $O(n)$ memory.

???+ note "Implementation"
    === "C++"
        ```cpp
        vector<int> find_occurrences(string text, string pattern) {
          string cur = pattern + '#' + text;
          int sz1 = text.size(), sz2 = pattern.size();
          vector<int> v;
          vector<int> lps = prefix_function(cur);
          for (int i = sz2 + 1; i <= sz1 + sz2; i++) {
            if (lps[i] == sz2) v.push_back(i - 2 * sz2);
          }
          return v;
        }
        ```
    
    === "Python"
        ```python
        def find_occurrences(t, s):
            cur = s + "#" + t
            sz1, sz2 = len(t), len(s)
            ret = []
            lps = prefix_function(cur)
            for i in range(sz2 + 1, sz1 + sz2 + 1):
                if lps[i] == sz2:
                    ret.append(i - 2 * sz2)
            return ret
        ```
    
    === "Java"
        ```java
        static List<Integer> find_occurrences(String text, String pattern) {
            String cur = pattern + '#' + text;
            int sz1 = text.length(), sz2 = pattern.length();
            List<Integer> v = new ArrayList<>();
            int[] lps = prefix_function(cur);
            for (int i = sz2 + 1; i <= sz1 + sz2; i++) {
                if (lps[i] == sz2) {
                    v.add(i - 2 * sz2);
                }
            }
            return v;
        }
        ```

### Period of a String

For a string $s$ and $0 < p \le |s|$, if $s[i] = s[i+p]$ holds for all $i \in [0, |s| - p - 1]$, then $p$ is called a period of $s$.

For a string $s$ and $0 \le r < |s|$, if the prefix of $s$ of length $r$ equals the suffix of $s$ of length $r$, then the prefix of $s$ of length $r$ is called a border of $s$.

From $s$ having a border of length $r$, it follows that $|s|-r$ is a period of $s$.

According to the definition of the prefix function, we can obtain all border lengths of $s$, i.e., $\pi[n-1],\pi[\pi[n-1]-1], \ldots$.[^ref1]

Therefore, using the prefix function, we can compute all periods of $s$ in $O(n)$ time. Since $\pi[n-1]$ is the length of the longest border of $s$, $n - \pi[n-1]$ is the minimal period of $s$.

### Counting Occurrences of Each Prefix

In this section, we will discuss two problems simultaneously. Given a string $s$ of length $n$, in the first variant of the problem we want to count the number of occurrences of each prefix $s[0 \dots i]$ in the same string, and in the second variant we want to count the number of occurrences of each prefix $s[0 \dots i]$ in another given string $t$.

First, let's solve the first problem. Consider the prefix function value $\pi[i]$ at position $i$. By definition, it means that a prefix of $s$ of length $\pi[i]$ appears at position $i$ with $i$ as its right end, and there is no longer prefix satisfying the above definition. At the same time, shorter prefixes may also have this position as their right end. It is easy to see that we have encountered a question already answered when computing the prefix function: given a prefix of length $j$ that is also a suffix ending at position $i$, what is the next smaller prefix length $k < j$? Such a prefix must also be a suffix ending at $i$. Therefore, ending at position $i$, there is a prefix of length $\pi[i]$, a prefix of length $\pi[\pi[i] - 1]$, a prefix of length $\pi[\pi[\pi[i] - 1] - 1]$, and so on, until the length becomes $0$. Thus, we can compute the answer in the following way.

???+ note "Implementation"
    === "C++"
        ```cpp
        vector<int> ans(n + 1);
        for (int i = 0; i < n; i++) ans[pi[i]]++;
        for (int i = n - 1; i > 0; i--) ans[pi[i - 1]] += ans[i];
        for (int i = 0; i <= n; i++) ans[i]++;
        ```
    
    === "Python"
        ```python
        ans = [0] * (n + 1)
        for i in range(0, n):
            ans[pi[i]] += 1
        for i in range(n - 1, 0, -1):
            ans[pi[i - 1]] += ans[i]
        for i in range(0, n + 1):
            ans[i] += 1
        ```

#### Explanation

In the above code, we first count how many times each prefix function value appears in the array $\pi$, and then compute the final answer: if we know that a prefix of length $i$ appears exactly $\text{ans}[i]$ times, this value must be added to the occurrence count of its longest substring that is both a suffix and a prefix. Finally, to count the original prefixes, we add 1 to each result.

Now consider the second problem. We apply the trick from Knuth–Morris–Pratt: construct a string $s + \# + t$ and compute its prefix function. The only difference from the first problem is that we only care about prefix function values related to string $t$, i.e., $\pi[i]$ for $i \ge n + 1$. With these values, we can solve this problem using the same algorithm as in the first problem.

### Number of Distinct Substrings in a String

Given a string $s$ of length $n$, we want to compute the number of distinct substrings.

We will solve this problem iteratively. In other words, given the current number of distinct substrings, we want to find a way to recalculate this number after adding a character at the end of $s$.

Let $k$ be the current number of distinct substrings of $s$. We add a new character $c$ to $s$. Obviously, some new substrings will end with character $c$. We want to count these substrings ending with this character that we have not encountered before.

Construct the string $t = s + c$ and reverse it to get $t^{\sim}$. Now our task becomes: how many prefixes of $t^{\sim}$ do not appear anywhere else in $t^{\sim}$? If we compute the maximum prefix function value $\pi_{\max}$ of $t^{\sim}$, then the longest prefix that appears in $s$ has length $\pi_{\max}$. Naturally, all shorter prefixes also appear.

Therefore, the number of new substrings appearing after adding a new character is $|s| + 1 - \pi_{\max}$.

Thus, for each added character, we can compute the number of new substrings in $O(n)$ time, so the final complexity is $O(n^2)$.

It is worth noting that we can also recalculate the number of distinct substrings when adding a character at the beginning, or removing a character from the end or beginning.

### String Compression

Given a string $s$ of length $n$, we want to find its shortest "compressed" representation, i.e., we want to find the shortest string $t$ such that $s$ can be represented by concatenating one or more copies of $t$.

Obviously, we only need to find the length of $t$. Knowing this length, the answer to the problem is the prefix of $s$ of that length.

Let's compute the prefix function of $s$. Using the last value of this function $\pi[n - 1]$, we define $k = n - \pi[n - 1]$. We will prove that if $k$ divides $n$, then $k$ is the answer; otherwise, no valid compression exists, so the answer is $n$.

Assume $n$ is divisible by $k$. Then the string can be divided into blocks of length $k$. By the definition of the prefix function, the prefix of the string of length $n - k$ equals its suffix. However, this means the last block equals the second-to-last block, and the second-to-last block equals the third-to-last block, and so on. As a result, all blocks are equal, so we can compress string $s$ to length $k$.

???+ note "Proof"
    Indeed, we still need to prove that this value is optimal. Actually, if there is a compressed representation smaller than $k$, then the last value of the prefix function $\pi[n - 1]$ must be greater than $n - k$. Therefore, $k$ is the answer.
    
    Now assume $n$ is not divisible by $k$. We will prove by contradiction that this means the answer is $n$[^1]. Suppose its minimal compressed representation $r$ has length $p$ ( $p$ divides $n$ ), and string $s$ is divided into $n / p \ge 2$ blocks. Then the last value of the prefix function $\pi[n - 1]$ must be greater than $n - p$ (if equal, then $n$ can be divided by $k$), i.e., the suffix it represents partially covers the first block. Now consider the second block of the string. This block has two explanations: the first is $r_0 r_1 \dots r_{p - 1}$, and the second is $r_{p - k} r_{p - k + 1} \dots r_{p - 1} r_0 r_1 \dots r_{p - k - 1}$. Since both explanations correspond to the same string, we can obtain a system of $p$ equations, which can be simplified to $r_{(i + k) \bmod p} = r_{i \bmod p}$, where $\cdot \bmod p$ denotes the smallest non-negative remainder modulo $p$.
    
    $$
    \begin{gathered}
    \overbrace{r_0 ~ r_1 ~ r_2 ~ r_3 ~ r_4 ~ r_5}^p ~ \overbrace{r_0 ~ r_1 ~ r_2 ~ r_3 ~ r_4 r_5}^p \\
    r_0 ~ r_1 ~ r_2 ~ r_3 ~ \underbrace{\overbrace{r_0 ~ r_1 ~ r_2 ~ r_3 ~ r_4 ~ r_5}^p ~ r_0 ~ r_1}_{\pi[11] = 8}
    \end{gathered}
    $$
    
    Using the extended Euclidean algorithm, we can obtain $x$ and $y$ such that $xk + yp = \gcd(k, p)$. By appropriately combining with the equation $pk - kp = 0$, we can obtain $x' > 0$ and $y' < 0$ such that $x'k + y'p = \gcd(k, p)$. This means that by repeatedly applying the equations in the system, we can obtain a new system $r_{(i + \gcd(k, p)) \bmod p} = r_{i \bmod p}$.
    
    Since $\gcd(k, p)$ divides $p$, this means $\gcd(k, p)$ is a period of $r$. And since $\pi[n - 1] > n - p$, we have $n - \pi[n - 1] = k < p$, so $\gcd(k, p)$ is a period of $r$ smaller than $p$. Therefore, string $s$ has a compressed representation of length $\gcd(k, p) < p$, contradicting the minimality of $p$.
    
    In summary, there is no compressed representation with length smaller than $k$, so the answer is $k$.

[^1]: In the Russian and English versions, this proof seems to be incorrect. The proof in this article was added by the author.

### Building an Automaton from the Prefix Function

Let's return to the new string formed by concatenating two strings with a delimiter. For strings $s$ and $t$, we compute the prefix function of $s + \# + t$. Obviously, because $\#$ is a delimiter, the prefix function values will never exceed $|s|$. Therefore, we only need to store the string $s + \#$ and its corresponding prefix function values, after which we can dynamically compute the prefix function values for all subsequent characters:

$$
\underbrace{s_0 ~ s_1 ~ \dots ~ s_{n-1} ~ \#}_{\text{need to store}} ~ \underbrace{t_0 ~ t_1 ~ \dots ~ t_{m-1}}_{\text{do not need to store}}
$$

Actually, in this case, knowing the next character $c$ of $t$ and the prefix function value at the previous position is sufficient to compute the prefix function value at the next position, without using any other characters of $t$ and their corresponding prefix function values.

In other words, we can construct an **automaton** (a finite state machine): its states are the current prefix function values, and transitions from one state to another are determined by the next character.

Therefore, even without string $t$, we can also construct a transition table $( \text { old } \pi , c ) \rightarrow \text { new } _ { - } \pi$ using the algorithm for constructing the transition table:

???+ note "Implementation"
    ```cpp
    void compute_automaton(string s, vector<vector<int>>& aut) {
      s += '#';
      int n = s.size();
      vector<int> pi = prefix_function(s);
      aut.assign(n, vector<int>(26));
      for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) {
          int j = i;
          while (j > 0 && 'a' + c != s[j]) j = pi[j - 1];
          if ('a' + c == s[j]) j++;
          aut[i][c] = j;
        }
      }
    }
    ```

However, in this form, for a lowercase alphabet, the time complexity of the algorithm is $O(|\Sigma|n^2)$. Note that we can use dynamic programming to utilize the already computed parts of the table. As long as we transition from value $j$ to $\pi[j - 1]$, we are actually saying that the transition $(j, c)$ leads to the same state as transition $(\pi[j - 1], c)$, but this answer has already been precisely computed before.

???+ note "Implementation"
    ```cpp
    void compute_automaton(string s, vector<vector<int>>& aut) {
      s += '#';
      int n = s.size();
      vector<int> pi = prefix_function(s);
      aut.assign(n, vector<int>(26));
      for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) {
          if (i > 0 && 'a' + c != s[i])
            aut[i][c] = aut[pi[i - 1]][c];
          else
            aut[i][c] = i + ('a' + c == s[i]);
        }
      }
    }
    ```

Finally, we can construct this automaton in $O(|\Sigma|n)$ time complexity.

When is this automaton useful? First, recall that most of the time we use the prefix function of $s + \# + t$ for one purpose: finding all occurrences of string $s$ in string $t$.

Therefore, the most direct benefit of using this automaton is **accelerating the computation of the prefix function of $s + \# + t$**.

By building the automaton of $s + \#$, we no longer need to store string $s$ and its corresponding prefix function values. All transitions have already been computed in the table.

But besides this, there is a second, less direct application. We can use this automaton to speed up computation when string $t$ is **some giant string constructed by some rules**. Gray strings, or strings constructed by recursive combinations of some short input strings, are such examples.

For completeness, let's solve such a problem: given a number $k \le 10^5$, and a string $s$ of length $\le 10^5$, we need to compute the number of occurrences of $s$ in the $k$-th Gray string. Recall that Gray strings are defined as follows:

$$
\begin{aligned}
g_1 &= \mathtt{a}\\
g_2 &= \mathtt{aba}\\
g_3 &= \mathtt{abacaba}\\
g_4 &= \mathtt{abacabadabacaba}
\end{aligned}
$$

Due to its astronomical length, in this case it is impossible to even construct string $t$: the $k$-th Gray string has $2^k - 1$ characters. However, we can efficiently compute the prefix function values at the end of this string knowing only the first few prefix function values.

In addition to the automaton, we also need to compute the value $G[i][j]$: the state of the automaton after processing $g_i$ starting from state $j$, and the value $K[i][j]$: the number of occurrences of $s$ in $g_i$ after processing $g_i$ starting from state $j$. Actually, $K[i][j]$ is the number of times the prefix function takes the value $|s|$ during the operation. It is easy to see that the answer to the problem is $K[k][0]$.

How do we compute these values? First, according to the definition, the initial conditions are $G[0][j] = j$ and $K[0][j] = 0$. Then all values can be computed from previous values using the automaton. To compute the values for a certain $i$, recall that string $g_i$ is formed by concatenating $g_{i - 1}$, the $i$-th character of the alphabet, and $g_{i - 1}$. Therefore, the automaton will pass through the following states:

$$
\begin{gathered}
\text{mid} = \text{aut}[G[i - 1][j]][i] \\
G[i][j] = G[i - 1][\text{mid}]
\end{gathered}
$$

The value of $K[i][j]$ can also be computed simply.

$$
K[i][j] = K[i - 1][j] + [\text{mid} == |s|] + K[i - 1][\text{mid}]
$$

where $[\cdot]$ evaluates to $1$ when the expression is true, and $0$ otherwise. Thus, we have solved the problem about Gray strings, as well as a large class of similar problems. For example, using the same method, we can solve the following problem: given a string $s$ and some patterns $t_i$, where each pattern is given as follows: the pattern consists of ordinary characters, among which previous strings may be recursively inserted in the form $t_{k}^{\text{cnt}}$, i.e., at that position we must insert string $t_k$ $\text{cnt}$ times. Here is an example of such patterns:

$$
\begin{aligned}
t_1 &= \mathtt{abdeca} \\
t_2 &= \mathsf{abc} + t_1^{30} + \mathsf{abd} \\
t_3 &= t_2^{50} + t_1^{100} \\
t_4 &= t_2^{10} + t_3^{100}
\end{aligned}
$$

Recursive substitution causes the string length to explode exponentially, and their lengths can even reach the order of $100^{100}$. And we must find the number of occurrences of string $s$ in each of these strings.

This problem can also be solved by constructing the automaton of the prefix function. As before, we compute the transitions for each pattern using the previously computed results and count the answers accordingly.

## Practice Problems

-   [UVa 455 "Periodic Strings"](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=396)
-   [UVa 11022 "String Factoring"](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1963)
-   [UVa 11452 "Dancing the Cheeky-Cheeky"](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2447)
-   [UVa 12604 - Caesar Cipher](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4282)
-   [UVa 12467 - Secret Word](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3911)
-   [UVa 11019 - Matrix Matcher](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1960)
-   [SPOJ - Pattern Find](http://www.spoj.com/problems/NAJPF/)
-   [Codeforces - Anthem of Berland](http://codeforces.com/contest/808/problem/G)
-   [Codeforces - MUH and Cube Walls](http://codeforces.com/problemset/problem/471/D)

## References and Notes

**This page is mainly translated from the article [Префикс-функция. Алгоритм Кнута-Морриса-Пратта](http://e-maxx.ru/algo/prefix_function) and its English translation [Prefix function. Knuth–Morris–Pratt algorithm](https://cp-algorithms.com/string/prefix-function.html). The Russian version is in the Public Domain with Leave a Link; the English version is under CC-BY-SA 4.0.**

[^ref1]: [Jin Ce - Selected Lectures on String Algorithms](https://github.com/hzwer/shareOI/blob/master/%E5%AD%97%E7%AC%A6%E4%B8%B2/%E5%AD%97%E7%AC%A6%E4%B8%B2%E7%AE%97%E6%B3%95%E9%80%89%E8%AE%B2_%E9%87%91%E7%AD%96.pdf)

[^kmp]: Knuth, Donald E., James H. Morris, Jr, and Vaughan R. Pratt. "Fast pattern matching in strings." SIAM journal on computing 6.2 (1977): 323-350.[doi: 10.1137/0206024](https://epubs.siam.org/doi/abs/10.1137/0206024)