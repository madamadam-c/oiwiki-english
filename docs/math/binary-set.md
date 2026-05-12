Prerequisites: [Bit Operations](./bit.md#bit-operations), [Integers and Bit Sequences](./bit.md#integers-and-bit-sequences).

The binary representation of a number can be viewed as a set (where $0$ means not in the set and $1$ means in the set). For example, the set $\{1,3,4,8\}$ can be represented as $(100011010)_2$. Correspondingly, bitwise operations can be seen as operations on sets.

| Operation |      Set Representation      |        Bitwise Representation         |
| --------- | :--------------------------: | :---------------------------------: |
| Intersection |     $a \cap b$     |   $a \operatorname{AND} b$      |
| Union     |     $a \cup b$     |   $a \operatorname{OR} b$       |
| Complement |      $\bar{a}$      |   $\operatorname{NOT} a$ (universe is all 1s in binary) |
| Difference |    $a \setminus b$    |   $a \operatorname{AND} \operatorname{NOT} b$ |
| Symmetric Difference | $a\triangle b$ | $a \operatorname{XOR} b$   |

Before introducing the enumeration of all subsets of a set, let us first look at some application examples of bit operations.

### Modulo by a Power of Two

Taking the modulo of a number by a non-negative integer power of $2$ is equivalent to taking the lower bits of the number in binary, and equivalent to performing an AND operation with $mod-1$.

=== "C++"
    ```cpp
    int modPowerOfTwo(int x, int mod) { return x & (mod - 1); }
    ```

=== "Python"
    ```python
    def modPowerOfTwo(x, mod):
        return x & (mod - 1)
    ```

Therefore, we can see that taking a non-negative integer power of $2$ modulo itself gives $0$. That is, if $n$ is a non-negative integer power of $2$, the AND of $n$ and $n-1$ is $0$.

In fact, for a positive integer $n$, $n-1$ clears the lowest $1$ bit of $n$ and sets all subsequent bits to $1$. Therefore, the AND of $n$ and $n-1$ is equivalent to removing the lowest $1$ bit of $n$.

Using this property, we can determine whether a number is a non-negative integer power of $2$. A number $n$ is a non-negative integer power of $2$ if and only if its binary representation has exactly one $1$.

=== "C++"
    ```cpp
    bool isPowerOfTwo(int n) { return n > 0 && (n & (n - 1)) == 0; }
    ```

=== "Python"
    ```python
    def isPowerOfTwo(n):
        return n > 0 and (n & (n - 1)) == 0
    ```

### Enumerating Subsets

Enumerating all subsets of a set represented by a binary number is equivalent to enumerating all submasks of the corresponding mask.

A mask is a string of binary digits used to perform an AND operation with a source number to obtain a new operand after masking out certain input bits of the source number.

A mask acts as a filter on the source number: a $1$ bit in the mask means the corresponding bit of the source number is retained, while a $0$ bit in the mask means the corresponding bit of the source number is set to $0$. Changing some $1$ bits in a mask to $0$ bits yields submasks of the mask, and the mask itself is also a submask of itself.

Given a mask $m$, to efficiently iterate over all submasks $s$ of $m$, consider the following implementation using bitwise tricks.

```cpp
// Iterate over non-empty submasks of m in descending order
int s = m;
while (s > 0) {
  // s is a non-empty submask of m
  s = (s - 1) & m;
}
```

Or using a more compact for statement:

```cpp
// Iterate over non-empty submasks of m in descending order
for (int s = m; s; s = (s - 1) & m)
// s is a non-empty submask of m
```

Both of these code snippets do not handle the submask equal to $0$. To handle the submask equal to $0$, other methods can be used, for example:

```cpp
// Iterate over submasks of m in descending order
for (int s = m;; s = (s - 1) & m) {
  // s is a submask of m
  if (s == 0) break;
}
```

Next, we prove that the code above visits all submasks of $m$, without repetition, and in descending order.

Suppose we have a current mask $s$ and want to visit the next mask. Subtracting $1$ from mask $s$ is equivalent to removing the rightmost set bit in mask $s$ and setting all bits to its right to $1$.

To make $s-1$ a new submask, we need to remove all extra $1$ bits that are not contained in mask $m$. This removal can be performed using the bitwise operation `(s - 1) & m`.

These two operations are equivalent to truncating mask $s-1$ to determine the maximum value that can be achieved arithmetically, i.e., the next submask after $s$ in descending order.

Therefore, this algorithm generates all submasks of the mask in descending order, with only two operations per iteration.

The special case is $s=0$. After executing $s-1$, we get $-1$, where all bits are $1$. After the `(s - 1) & m` operation, the new $s$ equals $m$. Therefore, if the loop does not end when $s=0$, the loop will never terminate.

Using $\text{popcount}(m)$ to denote the number of $1$s in the binary representation of $m$, this method can enumerate subsets of set $m$ in $O(2^{\text{popcount}(m)})$ time complexity.

### Enumerating Submasks for Every Mask

In problems using DP over bitmask states, we sometimes want to, for each mask, iterate over all submasks of that mask:

```cpp
for (int m = 0; m < (1 << n); ++m)
  // Iterate over non-empty submasks of m in descending order
  for (int s = m; s; s = (s - 1) & m)
    // s is a non-empty submask of m
```

This iterates over all submasks of all subsets of a set of size $n$.

Next, we prove that this operation has time complexity $O(3^n)$, where $n$ is the total number of bits in the mask, i.e., the total number of elements in the set.

Consider the $i$-th bit, i.e., the $i$-th element in the set. There are three cases:

- It is $0$ in mask $m$, so it is $0$ in submask $s$, meaning the element is in neither the superset nor the subset.
- It is $1$ in $m$ but $0$ in $s$, meaning the element is only in the superset, not in the subset.
- It is $1$ in both $m$ and $s$, meaning the element is in both the superset and the subset.

There are $n$ bits in total, so there are $3^n$ different combinations.

An alternative proof is:

If mask $m$ has $k$ ones, then it has $2^k$ submasks. For a given $k$, there are $\dbinom{n}{k}$ masks $m$, so the total number of all masks is:

$$
\sum_{k=0}^n \dbinom{n}{k} 2^k
$$

The sum above equals the expansion of $(1+2)^n$ using the binomial theorem, so there are $3^n$ different combinations.

### References

**This page is primarily translated from the blog post [Перебор всех подмасок данной маски](http://e-maxx.ru/algo/all_submasks) and its English translation [Submask Enumeration](https://cp-algorithms.com/algebra/all-submasks.html). The Russian version is under Public Domain + Leave a Link; the English version is under CC-BY-SA 4.0.**

### Practice Problems

- [Atcoder - Close Group](https://atcoder.jp/contests/abc187/tasks/abc187_f)
- [Codeforces - Nuclear Fusion](https://codeforces.com/problemset/problem/71/E)
- [Codeforces - Sandy and Nuts](https://codeforces.com/problemset/problem/599/E)
- [UVa 1439 - Exclusive Access 2](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4185)
- [UVa 11825 - Hackers' Crackdown](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2925)
