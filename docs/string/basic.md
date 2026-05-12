author: Ir1d, ouuan, qinggniq, i-Yirannn, minghu6

## Definition

### Character Set

A **character set** $\Sigma$ is a set with a [total order](../math/order-theory.md#偏序集) relation established, that is, any two different elements $\alpha$ and $\beta$ in $\Sigma$ can be compared in size, either $\alpha<\beta$, or $\beta<\alpha$. The elements in character set $\Sigma$ are called characters.

### String

A **string** $S$ is a sequence formed by arranging $n$ characters in order, where $n$ is called the length of $S$, denoted as $|S|$.

If the string index starts from $1$, the $i$-th character of $S$ is denoted as $S[i]$;

If the string index starts from $0$, the $i$-th character of $S$ is denoted as $S[i-1]$.

### Substring

The **substring** $S[i..j], i\le j$ of string $S$ represents the segment from position $i$ to $j$ in $S$, that is, the string formed by arranging $S[i], S[i+1], \ldots, S[j]$ sequentially.

Sometimes $S[i..j], i>j$ is also used to represent the empty string.

### Subsequence

A **subsequence** of string $S$ is a sequence formed by extracting several elements from $S$ without changing their relative positions, namely $S[p_1], S[p_2], \ldots, S[p_k]$, where $1\le p_1< p_2<\cdots< p_k\le|S|$.

### Suffix

A **suffix** is a special substring that starts from some position $i$ and ends at the end of the string. The suffix starting from $i$ of string $S$ is denoted as $\textit{Suffix(S,i)}$, which is $\textit{Suffix(S,i)}=S[i..|S|-1]$.

**Proper suffix** refers to suffixes of $S$ other than $S$ itself.

For example, all suffixes of string `abcabcd` are `{d, cd, bcd, abcd, cabcd, bcabcd, abcabcd}`, and its proper suffixes are `{d, cd, bcd, abcd, cabcd, bcabcd}`.

### Prefix

A **prefix** is a special substring that starts from the beginning of the string and ends at some position $i$. The prefix ending at position $i$ of string $S$ is denoted as $\textit{Prefix(S,i)}$, which is $\textit{Prefix(S,i)}=S[0..i]$.

**Proper prefix** refers to prefixes of $S$ other than $S$ itself.

For example, all prefixes of string `abcabcd` are `{a, ab, abc, abca, abcab, abcabc, abcabcd}`, and its proper prefixes are `{a, ab, abc, abca, abcab, abcabc}`.

### Lexicographic Order

Compare by the $i$-th character as the $i$-th key, and the empty character is less than any character in the character set (that is: $a< aa$).

### Palindrome

A **palindrome** is a string that is the same when read forward and backward, i.e., a string $s$ that satisfies $\forall 1\le i\le|s|, s[i]=s[|s|+1-i]$.

### Hamming Distance

**Hamming distance** is the distance between two strings of equal length, representing the number of positions where the corresponding characters differ between two strings of the same length.

We can simply consider that performing XOR on two strings, the number of positions where the result is $1$ is the Hamming distance between the two strings.

## String Storage

-   Use a `char` array to store, using the null character `\0` to indicate the end of the string (C-style string).
-   Use the [`string` class](../lang/csl/string.md) provided by the C++ standard library.
-   String constants can be represented by string literals (strings enclosed in double quotes).