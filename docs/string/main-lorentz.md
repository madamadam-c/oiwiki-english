## Tandem Repetitions

### Definition

Given a string $s$ of length $n$.

We call the new string obtained by writing a string consecutively twice a **tandem repetition**. In the following text, for precise wording, we call the string being repeated the original string. In other words, a tandem repetition is equivalent to a pair of indices $(i, j)$ such that $s[i \dots j]$ is formed by concatenating two identical strings.

Your goal is to find all tandem repetitions in the given string $s$. Or, solve a simpler problem: find any tandem repetition in $s$, or the longest one.

The algorithm below was proposed by Michael Main and Richard J. Lorentz in 1982.

???+ note "Convention"
    All string indices in the following text start from $0$.
    
    In the following text, let $\overline{s}$ denote the reverse of $s$. For example, $\overline{\tt abc} = \tt cba$.

### Explanation

Consider the string $\tt acababaee$, which contains three tandem repetitions:

-   $s[2 \dots 5] = \tt abab$
-   $s[3 \dots 6] = \tt baba$
-   $s[7 \dots 8] = \tt ee$

Here is another example, consider the string $\tt abaaba$, which has only two tandem repetitions:

-   $s[0 \dots 5] = \tt abaaba$
-   $s[2 \dots 3] = \tt aa$

### Number of Tandem Repetitions

A string of length $n$ can have up to $O(n^2)$ tandem repetitions. An obvious example is a string where all $n$ characters are the same; in this case, any substring with even length is a tandem repetition. In most cases, a periodic string with a small period will have many tandem repetitions.

However, this does not prevent us from computing the number of tandem repetitions in $O(n \log n)$ time. This is because the algorithm represents tandem repetitions in some compressed form, allowing us to compress multiple tandem repetitions into one.

Here are some interesting facts about the number of tandem repetitions:

-   If the original string of a tandem repetition is not itself a tandem repetition, we call this a **primitive repetition**. It can be proven that there are at most $O(n \log n)$ primitive repetitions.
-   If we compress a tandem repetition using a Crochemore triple $(i, p, r)$, where $i$ is the starting position of the tandem repetition, $p$ is the length of one period of this repetition (note: not the length of the original string!), and $r$ is the number of times this period repeats. Then all tandem repetitions of a string can be represented by $O(n \log n)$ Crochemore triples.
-   Fibonacci strings are defined as follows:

$$
\begin{align} t_0 &= a, \\ t_1 &= b, \\ t_i &= t_{i-1} + t_{i-2}, \end{align}
$$

It can be observed that Fibonacci strings have high periodicity. For a Fibonacci string $t_i$ of length $f_i$, even when compressed with Crochemore triples, there are $O(f_i \log f_i)$ triples. The number of primitive repetitions is also $O(f_i \log f_i)$.

## Main–Lorentz Algorithm

### Explanation

The core idea of the Main–Lorentz algorithm is **divide and conquer**.

This algorithm divides the string into left and right parts, first computes the number of tandem repetitions that are entirely in the left part (or right part), then computes the number of tandem repetitions that start in the left part and end in the right part. (In the following text, we call such tandem repetitions **crossing tandem repetitions**)

Computing the number of crossing tandem repetitions is the key point of the Main–Lorentz algorithm, which we will discuss in detail below.

### Process

#### Finding Crossing Tandem Repetitions

Let the left part of a string be $u$ and the right part be $v$. Then $s = u + v$, and the lengths of $u$ and $v$ are approximately half the length of $s$.

For any tandem repetition, consider its middle character. Here we call the first character of the right half of a tandem repetition its middle character. In other words, if $s[i...j]$ is a tandem repetition, then its middle character is $s[(i + j + 1)/2]$. If a tandem repetition's middle character is in $u$, we call it **left-biased**, otherwise **right-biased**.

Next, we will explore how to find all left-biased tandem repetitions.

Let the length of a left-biased tandem repetition be $2l$. Consider its first character that falls into $v$ (i.e., $s[|u|]$), this character must be identical to some character $u[\textit{cntr}]$ in $u$.

We consider fixing $\textit{cntr}$ and finding all qualifying tandem repetitions. For example: for the string $\tt c \; \underset{\textit{cntr}}{a} \; c \; | \; a \; d \; a$ (the $\tt |$ is used to distinguish the two parts), fixing $cntr = 1$, we can find the tandem repetition $\tt caca$ satisfies the condition.

Obviously, once we fix $\textit{cntr}$, we also fix the value of $l$. Once we know how to find all tandem repetitions, we can enumerate $\textit{cntr}$ from $0$ to $|u| - 1$ and find all qualifying tandem repetitions.

#### Determining Left-biased Tandem Repetitions

Even after fixing $\textit{cntr}$, there may still be multiple qualifying tandem repetitions. How do we find all of them?

Let's give another example: for the tandem repetition in string $\tt abcabcac$, $\overbrace{\tt a}^{l_1} \overbrace{\underset{\textit{cntr}}{\tt b} \tt c}^{l_2} \overbrace{\tt a}^{l_1}  \; | \; \overbrace{\tt b \; \tt c}^{l_2}$, we denote $l_1$ as the length of the substring from the first character of this tandem repetition to $s[\textit{cntr} - 1]$, and $l_2$ as the length of the substring from $s[\textit{cntr}]$ to the last character of the left original string of this tandem repetition.

Thus, we can give a **necessary and sufficient condition** for a substring of length $2l = 2(l_1 + l_2) = 2(|u| - \textit{cntr})$ to be a tandem repetition:

Let $k_1$ be the maximum integer satisfying $u[\textit{cntr} - k_1 \dots \textit{cntr} - 1] = u[|u| - k_1 \dots |u| - 1]$, and let $k_2$ be the maximum integer satisfying $u[\textit{cntr} \dots \textit{cntr} + k_2 - 1] = v[0 \dots k_2 - 1]$. Then for any pair $(l_1, l_2)$ satisfying $l_1 \le k_1$ and $l_2 \le k_2$, we can find exactly one corresponding tandem repetition.

Summarizing:

-   Fix a $\textit{cntr}$.
-   Then the length of all tandem repetitions we need to find is $2l = 2(|u| - \textit{cntr})$. There may still be multiple qualifying tandem repetitions, depending on the values of $l_1$ and $l_2$.
-   Compute the $k_1$, $k_2$ mentioned above.
-   Then all qualifying tandem repetitions satisfy:

$$
\begin{align} l_1 + l_2 &= l = |u| - \textit{cntr} \\ l_1 &\le k_1, \\ l_2 &\le k_2. \\ \end{align}
$$

Next, we only need to consider how to quickly compute $k_1$ and $k_2$. Using the [Z-function](./z-func.md), we can compute them in $O(1)$:

-   To compute $k_1$: just compute the Z-function of $\overline{u}$.
-   To compute $k_2$: just compute the Z-function of $v + \# + u$, where $\#$ is a character that does not appear in either $u$ or $v$.

#### Right-biased Tandem Repetitions

The method for computing right-biased tandem repetitions is almost the same as for left-biased ones. Consider its first character that falls into $u$ (i.e., $s[|u| - 1]$), it must be identical to some character in $v$. Let the position of this character in $v$ be $\textit{cntr}$.

Let $k_1$ be the maximum integer satisfying $v[\textit{cntr} - k_1 + 1 \dots \textit{cntr}] = u[|u| - k_1 \dots |u| - 1]$, and $k_2$ be the maximum integer satisfying $v[\textit{cntr} + 1 \dots \textit{cntr} + k_2] = v[0 \dots k_2 - 1]$. Then we can obtain $k_1$ and $k_2$ by computing the Z-functions of $\overline{u} + \# + \overline{v}$ and $v$ respectively.

Enumerate $\textit{cntr}$ and use a similar method to find right-biased tandem repetitions.

### Implementation

The Main–Lorentz algorithm outputs all tandem repetitions in the form of quadruples $(\textit{cntr}, l, k_1, k_2)$. If you only need to count the number of tandem repetitions, or only need to find the longest one, the information provided by these quadruples is sufficient. By the [Master Theorem](../basic/complexity.md#master-theorem-master-theorem), the time complexity of the Main–Lorentz algorithm is $O(n \log n)$.

Note that if you want to find all starting and ending positions of tandem repetitions from these quadruples, the worst-case time complexity will reach $O(n^2)$. We have implemented this in the program below, storing all starting and ending positions of tandem repetitions in `repetitions`.

```cpp
vector<int> z_function(string const& s) {
  int n = s.size();
  vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; i++) {
    if (i <= r) z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
  return z;
}

int get_z(vector<int> const& z, int i) {
  if (0 <= i && i < (int)z.size())
    return z[i];
  else
    return 0;
}

vector<pair<int, int>> repetitions;

void convert_to_repetitions(int shift, bool left, int cntr, int l, int k1,
                            int k2) {
  for (int l1 = max(1, l - k2); l1 <= min(l, k1); l1++) {
    if (left && l1 == l) break;
    int l2 = l - l1;
    int pos = shift + (left ? cntr - l1 : cntr - l - l1 + 1);
    repetitions.emplace_back(pos, pos + 2 * l - 1);
  }
}

void find_repetitions(string s, int shift = 0) {
  int n = s.size();
  if (n == 1) return;

  int nu = n / 2;
  int nv = n - nu;
  string u = s.substr(0, nu);
  string v = s.substr(nu);
  string ru(u.rbegin(), u.rend());
  string rv(v.rbegin(), v.rend());

  find_repetitions(u, shift);
  find_repetitions(v, shift + nu);

  vector<int> z1 = z_function(ru);
  vector<int> z2 = z_function(v + '#' + u);
  vector<int> z3 = z_function(ru + '#' + rv);
  vector<int> z4 = z_function(v);

  for (int cntr = 0; cntr < n; cntr++) {
    int l, k1, k2;
    if (cntr < nu) {
      l = nu - cntr;
      k1 = get_z(z1, nu - cntr);
      k2 = get_z(z2, nv + 1 + cntr);
    } else {
      l = cntr - nu + 1;
      k1 = get_z(z3, nu + 1 + nv - 1 - (cntr - nu));
      k2 = get_z(z4, (cntr - nu) + 1);
    }
    if (k1 + k2 >= l) convert_to_repetitions(shift, cntr < nu, cntr, l, k1, k2);
  }
}
```

**This page is mainly translated from the blog post [Поиск всех тандемных повторов в строке. Алгоритм Мейна-Лоренца](http://e-maxx.ru/algo/string_tandems) and its English translation [Finding repetitions](https://cp-algorithms.com/string/main_lorentz.html). The Russian version is in the Public Domain + Leave a Link; the English version is under CC-BY-SA 4.0.**