author: HeRaNO, Zhoier, Ir1d, Xeonacid, wangdehu, ouuan, ranwen, ananbaobeichicun, Ycrpro, dbxxx-oi, HowieHz, y-kx-b

## Introduction

A Fenwick tree is a compact data structure that supports **point updates** and **range queries**.

??? note "What are \"point updates\" and \"range queries\"?"
    Suppose we have the following problem:
    
    Given a sequence $a$, you need to perform the following two operations:
    
    -   Given $x, y$, increase $a[x]$ by $y$.
    -   Given $l, r$, compute the sum of $a[l \ldots r]$.
    
    The first operation is a "point update", and the second operation is a "range query".
    
    Similarly, there are also "range updates" and "point queries". Examples are:
    
    -   Range update: given $l, r, x$, increase every number in $a[l \ldots r]$ by $x$.
    -   Point query: given $x$, compute the value of $a[x]$.
    
    Note that range problems are generally strictly stronger than point problems, because an operation on a single point is equivalent to an operation on an interval of length $1$.

For an ordinary Fenwick tree, the maintained information and operation must be **associative** and **invertible**, such as addition (sum), multiplication (product), xor, and so on.

-   Associativity: $(x \circ y) \circ z = x \circ (y \circ z)$, where $\circ$ is a binary operator.
-   Invertibility: the operation has an inverse; that is, given $x \circ y$ and $x$, we can recover $y$.

Notes:

-   For multiplication modulo a number to be invertible, every number must have a modular inverse (this is guaranteed when the modulus is prime).
-   Information such as $\gcd$ and $\max$ is not invertible, so it cannot be handled by an ordinary Fenwick tree. However:
    -   Two Fenwick trees can be used to handle range extrema; see [Efficient Range Minimum Queries using Binary Indexed Trees](http://history.ioinformatics.org/oi/files/volume9.pdf#page=41).
    -   This page will also introduce an extended Fenwick tree that supports queries for non-invertible information in $\Theta(\log^2n)$ time.

In fact, the problems Fenwick trees can solve are a subset of the problems segment trees can solve: anything a Fenwick tree can do, a segment tree can also do; but a segment tree can do things a Fenwick tree may not be able to. However, Fenwick trees require much less code and have a smaller constant factor, so they are still worth learning.

Sometimes, with the help of difference arrays and auxiliary arrays, Fenwick trees can also solve the stronger **range add, point value** and **range add, range sum** problems.

## Fenwick Tree

### First Impression

Start with an example: if we want to know the prefix sum of $a[1 \ldots 7]$, how can we do it?

One method is to compute $a_1 + a_2 + a_3 + a_4 + a_5 + a_6 + a_7$, which requires summing $7$ numbers.

But if we already know three values $A$, $B$, and $C$, where $A = a[1 \ldots 4]$ is the sum, $B = a[5 \ldots 6]$ is the sum, and $C = a[7 \ldots 7]$ is the sum (that is, $a[7]$ itself), how would you compute it? Of course, $A + B + C$, so only $3$ numbers need to be summed.

This is why a Fenwick tree can answer queries quickly: we can always split a prefix $[1, n]$ into **no more than $\boldsymbol{\log n}$ intervals**, and the information for these $\log n$ intervals is **already known**.

Therefore, we only need to merge the information of these $\log n$ intervals to obtain the answer. Compared with directly merging $n$ pieces of information, this is much more efficient.

It is easy to see that the information must satisfy associativity; otherwise, we could not merge it as above.

The following figure shows how a Fenwick tree works:

![](./images/fenwick.svg)

The bottom eight blocks represent the original data array $a$. The staggered blocks above them (the same array as the top eight blocks) represent the higher-level array of $a$, namely the $c$ array.

The $c$ array stores the sums of certain intervals of the original array $a$. In other words, the information for these intervals is known, and our goal is to split the queried prefix into these small intervals.

For example, from the figure we can see:

-   $c_2$ covers $a[1 \ldots 2]$.
-   $c_4$ covers $a[1 \ldots 4]$.
-   $c_6$ covers $a[5 \ldots 6]$.
-   $c_8$ covers $a[1 \ldots 8]$.
-   Each remaining $c[x]$ covers only $a[x]$ itself (it can be regarded as the interval $a[x \ldots x]$ of length $1$).

It is not hard to see that $c[x]$ always stores the total information of an interval whose right endpoint is $x$. For now, ignore the left endpoint and first see how a Fenwick tree answers a query.

Example: compute the sum of $a[1 \ldots 7]$.

Process: start from $c_{7}$ and jump backward. We find that $c_{7}$ only covers the element $a_{7}$; then we find $c_{6}$, $c_{6}$ covers $a[5 \ldots 6]$; then we jump to $c_{4}$, $c_{4}$ covers $a[1 \ldots 4]$; finally we would try to jump to $c_0$, but $c_0$ does not exist, so we stop.

The $c$ values we found are $c_7, c_6, c_4$. These are exactly the three small intervals into which $a[1 \ldots 7]$ is split, so the answer is $c_7 + c_6 + c_4$.

Example: compute the sum of $a[4 \ldots 7]$.

We still start from $c_7$, jump to $c_6$, and then to $c_4$. At this point, c_4 covers the sum of $a[1 \ldots 4]$, but we do not want the part $a[1 \ldots 3]$. What should we do? Simply subtract the sum of $a[1 \ldots 3]$.

So from the beginning, we can transform the query for the sum of $a[4 \ldots 7]$ into queries for the sums of $a[1 \ldots 7]$ and $a[1 \ldots 3]$, then subtract the two results.

![](images/fenwick-query.svg)

### Covered Intervals

Now the question is: how far left does the interval covered by $c[x](x \ge 1)$ extend? In other words, what is the interval length?

In a Fenwick tree, the length of the interval covered by $c[x]$ is defined as $2^{k}$, where:

-   If the least significant bit is bit $0$, then $k$ is exactly the bit position of the lowest `1` in the binary representation of $x$.
-   $2^k$ (the length of the interval covered by $c[x]$) is exactly the number formed by the lowest `1` in the binary representation of $x$ and all the following `0`s.

For example, which interval does $c_{88}$ cover?

Since $88_{(10)}=01011000_{(2)}$, the binary number formed by its lowest `1` and the following `0`s is `1000`, namely $8$. Therefore, $c_{88}$ covers $8$ elements of the array $a$.

Thus, $c_{88}$ represents the interval information of $a[81 \ldots 88]$.

We denote the number formed by the lowest binary `1` of $x$ and the following `0`s as $\operatorname{lowbit}(x)$. Then the interval covered by $c[x]$ is $[x-\operatorname{lowbit}(x)+1, x]$.

???+ warning "Note"
    $\operatorname{lowbit}$ does not mean the bit position $k$ of the lowest `1`; it means the value $2^k$ formed by this `1` and all following `0`s.

How do we compute `lowbit`? From bit operations, we have `lowbit(x) = x & -x`.

??? note "Why lowbit works"
    Invert all bits of the binary representation of `x`, then add 1, and we obtain the binary encoding of `-x`. For example, the binary encoding of $6$ is `110`; after inverting all bits we get `001`, and adding `1` gives `010`.
    
    Suppose the original binary encoding of `x` is `(...)10...00`. After inverting all bits we get `[...]01...11`, and after adding `1` we get `[...]10...00`, which is the binary encoding of `-x`. Here the shown `1` in the binary representation of `x` is the lowest `1` of `x`.
    
    Each omitted bit in `(...)` and `[...]` is opposite, so `x & -x = (...)10...00 & [...]10...00 = 10...00`. The result is exactly `lowbit`.

???+ note "Implementation"
    === "C++"
        ```cpp
        int lowbit(int x) {
          // The number formed by the lowest 1 in x's binary representation
          // and all following 0s.
          // lowbit(0b01011000) == 0b00001000
          //          ~~~~^~~~
          // lowbit(0b01110010) == 0b00000010
          //          ~~~~~~^~
          return x & -x;
        }
        ```
    
    === "Python"
        ```python
        def lowbit(x):
            """
            The number formed by the lowest 1 in x's binary representation
            and all following 0s.
            lowbit(0b01011000) == 0b00001000
                    ~~~~~^~~
            lowbit(0b01110010) == 0b00000010
                    ~~~~~~~^~
            """
            return x & -x
        ```

### Range Queries

Next, let us look at the concrete operations of a Fenwick tree, starting with range queries.

Recall the process of querying $a[4 \ldots 7]$: we transformed it into two subproblems, querying the sums of $a[1 \ldots 7]$ and $a[1 \ldots 3]$, then subtracting the results.

In fact, any range query can be handled this way: the sum of $a[l \ldots r]$ equals the sum of $a[1 \ldots r]$ minus the sum of $a[1 \ldots l - 1]$. This turns a range problem into a prefix problem, which is easier to handle.

In contests, transforming a query on $l \ldots r$ into prefix queries on $1 \ldots r$ and $1 \ldots l - 1$ and then taking their difference is a very common technique.

How do we perform a prefix query? Recall the process of querying $a[1 \ldots 7]$:

> Jump backward from $c_{7}$ and find that $c_{7}$ only covers the element $a_{7}$; then find $c_{6}$, $c_{6}$ covers $a[5 \ldots 6]$; then jump to $c_{4}$, $c_{4}$ covers $a[1 \ldots 4]$; finally try to jump to $c_0$, but $c_0$ does not exist, so we stop.
>
> The $c$ values we found are $c_7, c_6, c_4$. These are exactly the three small intervals into which $a[1 \ldots 7]$ is split; after merging them, the answer is $c_7 + c_6 + c_4$.

Observe that in the above process, each backward jump must go to the position immediately left of the current interval's left endpoint and use it as the right endpoint of the new interval. Only then can the prefix be split without overlaps or gaps. For example, $c_6$ covers $a[5 \ldots 6]$, so the next jump is to $5 - 1 = 4$, namely $c_4$.

We can now describe the process of querying $a[1 \ldots x]$:

-   Start from $c[x]$ and jump backward. Here $c[x]$ covers $a[x-\operatorname{lowbit}(x)+1 \ldots x]$.
-   Set $x \gets x - \operatorname{lowbit}(x)$. If $x = 0$, we have reached the end and terminate the loop; otherwise, return to the first step.
-   Merge all visited $c$ values.

In implementation, we do not need to collect all $c$ values first and then merge them; we can merge while jumping.

For example, if the maintained information is a sum, initialize $\mathrm{ans} = 0$. Each time we reach a $c[x]$, set $\mathrm{ans} \gets \mathrm{ans} + c[x]$. The final $\mathrm{ans}$ is the merged result.

???+ note "Implementation"
    === "C++"
        ```cpp
        int getsum(int x) {  // sum of a[1]..a[x]
          int ans = 0;
          while (x > 0) {
            ans = ans + c[x];
            x = x - lowbit(x);
          }
          return ans;
        }
        ```
    
    === "Python"
        ```python
        def getsum(x):  # sum of a[1]..a[x]
            ans = 0
            while x > 0:
                ans = ans + c[x]
                x = x - lowbit(x)
            return ans
        ```

### Properties of the Fenwick Tree as a Tree

Before explaining point updates, let us first discuss some basic properties of Fenwick trees and where their tree structure comes from. This helps in understanding point updates better.

We use the following conventions:

-   $l(x) = x - \operatorname{lowbit}(x) + 1$. That is, $l(x)$ is the left endpoint of the range covered by $c[x]$.
-   For any positive integer $x$, we can always write $x$ as $s \times 2^{k + 1} + 2^k$, where $\operatorname{lowbit}(x) = 2^k$.
-   Below, "$c[x]$ and $c[y]$ are disjoint" means the ranges covered by $c[x]$ and $c[y]$ do not intersect, that is, $[l(x), x]$ and $[l(y), y]$ do not intersect. Phrases such as "$c[x]$ is contained in $c[y]$" are interpreted similarly.

**Property $\boldsymbol{1}$: For $\boldsymbol{x \le y}$, either $\boldsymbol{c[x]}$ and $\boldsymbol{c[y]}$ are disjoint, or $\boldsymbol{c[x]}$ is contained in $\boldsymbol{c[y]}$.**

??? note "Proof"
    Proof: Suppose $c[x]$ and $c[y]$ intersect, that is, $[l(x), x]$ and $[l(y), y]$ intersect. Then we must have $l(y) \le x \le y$.
    
    Write $y$ as $s \times 2^{k +1} + 2^k$. Then $l(y) = s \times 2^{k + 1} + 1$. Therefore, $x$ can be written as $s \times 2^{k +1} + b$, where $1 \le b \le 2^k$.
    
    It is easy to see that $\operatorname{lowbit}(x) = \operatorname{lowbit}(b)$. Also, $b - \operatorname{lowbit}(b) \ge 0$.
    
    Hence $l(x) = x - \operatorname{lowbit}(x) + 1 = s \times 2^{k +1} + b - \operatorname{lowbit}(b) +1 \ge s \times 2^{k +1} + 1 = l(y)$, so $l(y) \le l(x) \le x \le y$.
    
    Therefore, if $c[x]$ and $c[y]$ intersect, the range covered by $c[x]$ is completely contained in the range covered by $c[y]$.

**Property $\boldsymbol{2}$: $\boldsymbol{c[x]}$ is properly contained in $\boldsymbol{c[x + \operatorname{lowbit}(x)]}$.**

??? note "Proof"
    Proof: Let $y = x + \operatorname{lowbit}(x)$ and $x = s \times 2^{k + 1} + 2^k$. Then $y = (s + 1) \times 2^{k +1}$ and $l(x) = s \times 2^{k + 1} + 1$.
    
    It is easy to see that $\operatorname{lowbit}(y) \ge 2^{k + 1}$, so $l(y) = (s + 1) \times 2^{k + 1} - \operatorname{lowbit}(y) + 1 \le s \times 2^{k +1} + 1= l(x)$, that is, $l(y) \le l(x) \le x < y$.
    
    Therefore, $c[x]$ is properly contained in $c[x + \operatorname{lowbit}(x)]$.

**Property $3$: For any $\boldsymbol{x < y < x + \operatorname{lowbit}(x)}$, $\boldsymbol{c[x]}$ and $\boldsymbol{c[y]}$ are disjoint.**

??? note "Proof"
    Proof: Let $x = s \times 2^{k + 1} + 2^k$. Then $y = x + b = s \times 2^{k + 1} + 2^k + b$, where $1 \le b < 2^k$.
    
    It is easy to see that $\operatorname{lowbit}(y) = \operatorname{lowbit}(b)$. Also, $b - \operatorname{lowbit}(b) \ge 0$.
    
    Therefore $l(y) = y - \operatorname{lowbit}(y) + 1 = x + b - \operatorname{lowbit}(b) + 1 > x$, so $l(x) \le x < l(y) \le y$.
    
    Thus, $c[x]$ and $c[y]$ are disjoint.

With these three properties established, let us look at the tree structure of a Fenwick tree (ignore the edges from $a$ to $c$).

![](./images/fenwick.svg)

In fact, the tree structure of a Fenwick tree is the graph obtained by adding an edge from $x$ to $x + \operatorname{lowbit}(x)$, where $x + \operatorname{lowbit}(x)$ is the parent of $x$.

Note that when considering the tree structure, we ignore the size limit of the Fenwick tree and regard it as an infinite tree for easier analysis. In actual implementation, we only use, for $x \le n$, the $c[x]$ values, where $n$ is the length of the original array.

This tree naturally satisfies many useful properties. Some are listed below (let $fa[u]$ denote the direct parent of $u$):

-   $u < fa[u]$.
-   $u$ is greater than any descendant of $u$ and less than any ancestor of $u$.
-   Node $u$'s $\operatorname{lowbit}$ is strictly smaller than $fa[u]$'s $\operatorname{lowbit}$.

??? note "Proof"
    Let $y = x + \operatorname{lowbit}(x)$ and $x = s \times 2^{k + 1} + 2^k$. Then $y = (s + 1) \times 2^{k +1}$. It is easy to see that $\operatorname{lowbit}(y) \ge 2^{k + 1} > \operatorname{lowbit}(x)$, completing the proof.

-   The height of node $x$ is $\log_2\operatorname{lowbit}(x)$, namely the bit position of the lowest binary `1` of $x$.

??? note "Definition of height"
    Node $x$ has height $h(x)$ satisfying: if $x \bmod 2 = 1$, then $h(x) = 0$; otherwise $h(x) = \max(h(y)) + 1$, where $y$ ranges over all children of $x$ (in this case $x$ has at least the child $x - 1$).
    
    In other words, the height of a node is exactly $1$ more than the height of its highest child. If a node has no children, its height is $0$.
    
    We introduce the concept of height here to make the later complexity analysis easier.

-   $c[u]$ is properly contained in $c[fa[u]]$ (Property $2$).
-   $c[u]$ is properly contained in $c[v]$, where $v$ is any ancestor of $u$ (by induction on the previous property).
-   $c[u]$ properly contains $c[v]$, where $v$ is any descendant of $u$ (swap $u$ and $v$ in the previous property).
-   For any $v' > u$, if $v'$ is not an ancestor of $u$, then $c[u]$ and $c[v']$ are disjoint.

??? note "Proof"
    Among $u$ and the ancestors of $u$, there must be a node $v$ such that $v < v' < fa[v]$. By Property $3$, $c[v']$ is disjoint from $c[v]$; since $c[v]$ contains $c[u]$, $c[v']$ is also disjoint from $c[u]$.

-   For any $v < u$, if $v$ is not in the subtree of $u$, then $c[u]$ and $c[v]$ are disjoint (swap $u$ and $v'$ in the previous property).
-   For any $v > u$, if and only if $v$ is an ancestor of $u$, $c[u]$ is properly contained in $c[v]$ (a summary of the previous properties). This is the core principle behind point updates in a Fenwick tree.
-   Let $u = s \times 2^{k + 1} + 2^k$. Then it has $k = \log_2\operatorname{lowbit}(u)$ children, numbered $u - 2^t(0 \le t < k)$.
    -   Example: suppose $k = 3$ and the binary number of $u$ is `...1000`. Then $u$ has three children, whose binary numbers are `...0111`, `...0110`, and `...0100`.

??? note "Proof"
    For a number $x$, subtracting $2^t$ from $x$ flips bit $t$, while lower bits remain unchanged.
    
    Consider a child of $u$, denoted $v$. We have $v + \operatorname{lowbit}(v) = u$, so $v = u - 2^t$ and $\operatorname{lowbit}(v) = 2^t$. Let $u = s \times 2^{k + 1} + 2^k$.
    
    **Consider $\boldsymbol{0 \le t < k}$**. In $u$, bit $t$ and all lower bits are $0$, so in $v = u - 2^t$, bit $t$ becomes $1$ while lower bits remain $0$. Thus it **satisfies** $\operatorname{lowbit}(v) = 2^t$.
    
    **Consider $\boldsymbol{t = k}$**. Then $v = u - 2^k$, and in $v$, bit $k$ becomes $0$, so it **does not satisfy** $\operatorname{lowbit}(v) = 2^t$.
    
    **Consider $\boldsymbol{t > k}$**. Then $v = u - 2^t$, and in $v$, bit $k$ is $1$, so $\operatorname{lowbit}(v) = 2^k$. It **does not satisfy** $\operatorname{lowbit}(v) = 2^t$.

-   For $u$, the intervals covered by the corresponding $c$ values of all children concatenate exactly into $[l(u), u - 1]$.
    -   Example: suppose $k = 3$ and the binary number of $u$ is `...1000`. Then $u$ has three children, whose binary numbers are `...0111`, `...0110`, and `...0100`.
    -   `c[...0100]` represents `a[...0001 ~ ...0100]`.
    -   `c[...0110]` represents `a[...0101 ~ ...0110]`.
    -   `c[...0111]` represents `a[...0111 ~ ...0111]`.
    -   It is easy to see that the union of the three covered intervals above is exactly `a[...0001 ~ ...0111]`, namely $[l(u), u - 1]$.

??? note "Proof"
    The children of $u$ can always be written as $u - 2^t(0 \le t < k)$. It is easy to see that the smaller $t$ is, the larger $u - 2^t$ is, and the farther right the represented interval is. Let $f(t) = u - 2^t$. Then $f(k - 1), f(k - 2), \ldots, f(0)$ are the children of $u$ from left to right.
    
    It is easy to see that $\operatorname{lowbit}(f(t)) = 2^t$, so $l(f(t)) = u - 2^t - 2^t + 1 = u - 2^{t + 1} + 1$.
    
    Consider two adjacent children $f(t + 1)$ and $f(t)$. The right endpoint of the interval covered by the former is $f(t + 1) = u - 2^{t + 1}$, and the left endpoint of the interval covered by the latter is $l(f(t)) = u - 2^{t + 1} + 1$, so they are exactly adjacent.
    
    For the leftmost child $f(k - 1)$, its covered left boundary is $l(f(k - 1)) = u - 2^k + 1$, exactly $l(u)$.
    
    For the rightmost child $f(0)$, its covered right boundary is $u - 1$.
    
    Therefore, the intervals covered by these children concatenate exactly into $[l(u), u - 1]$.

### Point Updates

Now consider how to perform a point update on $a[x]$.

Our goal is to maintain the $c$ array quickly and correctly. For efficiency, we only need to traverse and modify all values covering $a[x]$, namely all $c[y]$, because all other $c$ values clearly remain unchanged.

Anything covering $a[x]$, namely $c[y]$, must contain $c[x]$ (by Property $1$), so $y$ is an ancestor of $x$ in the Fenwick tree structure. Therefore, we start from $x$ and repeatedly jump to the parent until we exceed the length of the original array.

Let $n$ be the size of $a$. The process of point-updating $a[x]$ is:

-   Initially set $x' = x$.
-   Modify $c[x']$.
-   Set $x' \gets x' + \operatorname{lowbit}(x')$. If $x' > n$, we have reached the end and terminate the loop; otherwise, return to the second step.

The maintained interval information and the type of point update together determine how $c[x']$ is modified. Here are some examples:

-   If $c[x']$ maintains interval sums and the update adds to $a[x]$ the value $p$, then we add to every affected $c[x']$ the value $p$.
-   If $c[x']$ maintains interval products and the update multiplies $a[x]$ by $p$, then we multiply every affected $c[x']$ by $p$.

However, the flexibility of point updates means the update type and the maintained information do not have to use the same operation. For example, if $c[x']$ maintains interval sums and the update assigns $a[x]$ to $p$, we can transform it into changing $a[x]$ by adding $p - a[x]$. If the update multiplies $a[x]$ by $p$, we can transform it into changing $a[x]$ by adding $a[x] \times p - a[x]$.

The following implementation uses interval sums with point addition as an example.

???+ note "Implementation"
    === "C++"
        ```cpp
        void add(int x, int k) {
          while (x <= n) {  // Do not go out of bounds
            c[x] = c[x] + k;
            x = x + lowbit(x);
          }
        }
        ```
    
    === "Python"
        ```python
        def add(x, k):
            while x <= n:  # Do not go out of bounds
                c[x] = c[x] + k
                x = x + lowbit(x)
        ```

### Building the Tree

This means building the Fenwick tree from the initially given sequence, with all $c$ values preprocessed.

Usually, this can be directly transformed into $n$ point updates, with time complexity $\Theta(n \log n)$ (complexity analysis appears later).

For example, if the given sequence is $a = (5, 1, 4)$ and we need to build the tree, we can simply regard it as adding to $a[1]$ the value $5$, adding to $a[2]$ the value $1$, and adding to $a[3]$ the value $4$.

There is also a $\Theta(n)$ building method; see the [$\Theta(n)$ building](#thetan-building) section on this page.

### Complexity Analysis

The space complexity is clearly $\Theta(n)$.

Time complexity:

-   For range queries: the entire iteration $x \gets x - \operatorname{lowbit}(x)$ can be viewed as gradually changing all, in $x$'s binary representation, $1$s from low bits to high bits into $0$s. The number of split intervals equals the number, in $x$'s binary representation, of $1$s (that is, $\operatorname{popcount}(x)$). Therefore, a single query takes $\Theta(\log n)$ time.
-   For point updates: when jumping to parents, the visited height strictly increases, and we always have $x \le n$. Since the height of node $x$ is $\log_2\operatorname{lowbit}(x)$, the height reached never exceeds $\log_2n$, so the number of visited $c$ values is on the order of $\log n$. Therefore, a single point update takes $\Theta(\log n)$ time.

## Range Add, Range Sum

Prerequisite: [Prefix Sum & Difference](../basic/prefix-sum.md).

This problem can be solved by using two Fenwick trees to maintain a difference array.

Consider sequence $a$'s difference array $d$, where $d[i] = a[i] - a[i - 1]$. Since the prefix sum of the difference array is the original array, $a_i=\sum_{j=1}^i d_j$.

Similarly, we transform a range-sum query into a prefix-sum query through differences. Consider querying the sum of $a[1 \ldots r]$, namely $\sum_{i=1}^{r} a_i$:

$$
\begin{aligned}
&\sum_{i=1}^{r} a_i\\=&\sum_{i=1}^r\sum_{j=1}^i d_j
\end{aligned}
$$

From this expression, each $d_j$ is added a total of $r - j + 1$ times. Continuing the derivation:

$$
\begin{aligned}
&\sum_{i=1}^r\sum_{j=1}^i d_j\\=&\sum_{i=1}^r d_i\times(r-i+1)
\\=&\sum_{i=1}^r d_i\times (r+1)-\sum_{i=1}^r d_i\times i
\end{aligned}
$$

$\sum_{i=1}^r d_i$ is not enough to derive the value of $\sum_{i=1}^r d_i \times i$, so we use two Fenwick trees to maintain the sums of $d_i$ and $d_i \times i$ separately.

How do we perform a range add? Consider adding to the original array interval $a[l \ldots r]$ the value $x$ and its effect on $d$.

Because the difference is $d[i] = a[i] - a[i - 1]$:

-   $a[l]$ increases by $v$ while $a[l - 1]$ is unchanged, so $d[l]$ increases by $v$.
-   $a[r + 1]$ is unchanged while $a[r]$ increases by $v$, so $d[r + 1]$ decreases by $v$.
-   For values not equal to $l$ and not equal to $r+1$, any $i$ has either neither of $a[i]$ and $a[i - 1]$ change, or both increase by $v$. Thus $a[i] + v - (a[i - 1] + v)$ is still $a[i] - a[i - 1]$, so all other $d[i]$ remain unchanged.

The maintenance method is then straightforward: for the Fenwick tree maintaining $d_i$, at $l$ add $v$, and at $r + 1$ add $-v$; for the Fenwick tree maintaining $d_i \times i$, at $l$ add $v \times l$, and at $r + 1$ add $-v \times (r + 1)$.

For the weaker problem, "range add, point query", it is enough to use one Fenwick tree to maintain the difference array $d_i$. To query the point value $a[x]$, directly compute the sum of $d[1 \ldots x]$.

Here is the code for "range add, range sum":

???+ note "Implementation"
    === "C++"
        ```cpp
        int t1[MAXN], t2[MAXN], n;
        
        int lowbit(int x) { return x & (-x); }
        
        void add(int k, int v) {
          int v1 = k * v;
          while (k <= n) {
            t1[k] += v, t2[k] += v1;
            // Do not write t2[k] += k * v, because k is no longer the original array index.
            k += lowbit(k);
          }
        }
        
        int getsum(int *t, int k) {
          int ret = 0;
          while (k) {
            ret += t[k];
            k -= lowbit(k);
          }
          return ret;
        }
        
        void add1(int l, int r, int v) {
          add(l, v), add(r + 1, -v);  // Convert a range add into two prefix adds.
        }
        
        long long getsum1(int l, int r) {
          return (r + 1ll) * getsum(t1, r) - 1ll * l * getsum(t1, l - 1) -
                 (getsum(t2, r) - getsum(t2, l - 1));
        }
        ```
    
    === "Python"
        ```python
        t1 = [0] * MAXN
        t2 = [0] * MAXN
        n = 0
        
        
        def lowbit(x):
            return x & (-x)
        
        
        def add(k, v):
            v1 = k * v
            while k <= n:
                t1[k] = t1[k] + v
                t2[k] = t2[k] + v1
                k = k + lowbit(k)
        
        
        def getsum(t, k):
            ret = 0
            while k:
                ret = ret + t[k]
                k = k - lowbit(k)
            return ret
        
        
        def add1(l, r, v):
            add(l, v)
            add(r + 1, -v)
        
        
        def getsum1(l, r):
            return (
                (r) * getsum(t1, r)
                - l * getsum(t1, l - 1)
                - (getsum(t2, r) - getsum(t2, l - 1))
            )
        ```

By the same principle, one can implement "range multiply, range product", "range xor by a number, query range xor", and so on, as long as the maintained information and the range operation are the same operation. Interested readers can try this themselves.

## Two-Dimensional Fenwick Tree

### Point Updates, Submatrix Queries

A two-dimensional Fenwick tree, also called a Fenwick tree of Fenwick trees, is used to maintain point updates and prefix information on a two-dimensional array.

Similar to the one-dimensional Fenwick tree, we use $c(x, y)$ to represent the total information of the matrix $a(x - \operatorname{lowbit}(x) + 1, y - \operatorname{lowbit}(y) + 1) \ldots a(x, y)$, that is, the matrix whose lower-right corner is $a(x, y)$, height is $\operatorname{lowbit}(x)$, and width is $\operatorname{lowbit}(y)$.

For point updates, define:

$$
f(x, i) = \begin{cases}x &i = 0\\f(x, i - 1) + \operatorname{lowbit}(f(x, i - 1)) & i > 0\\\end{cases}
$$

That is, $f(x, i)$ is, for $x$ in the Fenwick tree structure, the $i$-th ancestor (the $0$-th ancestor is itself).

Then only elements of the form $c(f(x, i), f(y, j))$ cover $a(x, y)$. When modifying $a(x, y)$, we only need to modify all $c(f(x, i), f(y, j))$ such that $f(x, i) \le n$ and $f(y, j) \le m$.

??? note "Correctness proof"
    Suppose $c(p, q)$ covers $a(x, y)$; determine the possible values of $p$ and $q$.
    
    Consider a one-dimensional Fenwick tree of size $n$, namely $c_1$ (corresponding to original array $a_1$), and a one-dimensional Fenwick tree of size $m$, namely $c_2$ (corresponding to original array $a_2$).
    
    The proposition is equivalent to the condition that $c_1(p)$ covers $a_1[x]$ and $c_2(q)$ covers $a_2[y]$.
    
    In other words, in the Fenwick tree structure, $p$ is one of $x$ and its ancestors, and $q$ is one of $y$ and its ancestors.
    
    Therefore, $p = f(x, i)$ and $q = f(y, j)$.

For queries, define:

$$
g(x, i) = \begin{cases}x &i = 0\\g(x, i - 1) - \operatorname{lowbit}(g(x, i - 1)) & i, g(x, i - 1) > 0\\0&\text{otherwise.}\end{cases}
$$

Then merge all $c(g(x, i), g(y, j))$ where $g(x, i), g(y, j) > 0$.

??? note "Correctness proof"
    Let $\circ$ denote the operator used to merge two pieces of information (for example, if the information is a range sum, then $\circ = +$).
    
    Consider a one-dimensional Fenwick tree $c_1$. The expression $c_1[g(x, 0)] \circ c_1[g(x, 1)] \circ c_1[g(x, 2)] \circ \cdots$ exactly represents the interval information of $[1 \ldots x]$ in the original array.
    
    Similarly, let $t(x) = c(x, g(y, 0)) \circ c(x, g(y, 1)) \circ c(x, g(y, 2)) \circ \cdots$. Then $t(x)$ exactly represents the matrix information of $a(x - \operatorname{lowbit}(x) + 1, 1) \ldots a(x, y)$.
    
    Likewise, $t(g(x, 0)) \circ t(g(x, 1)) \circ t(g(x, 2)) \circ \cdots$ represents the matrix information of $a(1, 1) \ldots a(x, y)$.
    
    If the function $t(x)$ is viewed as a Fenwick tree, this is equivalent to putting one Fenwick tree inside another, which is where the name "Fenwick tree of Fenwick trees" comes from.

The following code implements point addition and submatrix-sum queries.

???+ note "Implementation"
    === "Point add"
        ```cpp
        void add(int x, int y, int v) {
          for (int i = x; i <= n; i += lowbit(i)) {
            for (int j = y; j <= m; j += lowbit(j)) {
              // Loop variables are necessary here; unlike the one-dimensional case,
              // we cannot directly write while (x <= n).
              c[i][j] += v;
            }
          }
        }
        ```
    
    === "Query submatrix sum"
        ```cpp
        int sum(int x, int y) {
          int res = 0;
          for (int i = x; i > 0; i -= lowbit(i)) {
            for (int j = y; j > 0; j -= lowbit(j)) {
              res += c[i][j];
            }
          }
          return res;
        }
        
        int ask(int x1, int y1, int x2, int y2) {
          // Query the submatrix sum.
          return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1);
        }
        ```

### Submatrix Add, Submatrix Sum

Prerequisites: [Prefix Sum & Difference](../basic/prefix-sum.md) and the [Range Add, Range Sum](#range-add-range-sum) section on this page.

Similar to the one-dimensional Fenwick tree problem "range add, range sum", consider maintaining a difference array.

The difference array for a two-dimensional array is defined as follows:

$$
d(i, j) = a(i, j) - a(i - 1, j) - a(i, j - 1) + a(i - 1, j - 1)．
$$

??? note "Why is it defined this way?"
    This is because, ideally, taking the two-dimensional prefix sum of the difference matrix should recover the original matrix, since these are inverse operations.
    
    The formula for a two-dimensional prefix sum is:
    
    $s(i, j) = s(i - 1, j) + s(i, j - 1) - s(i - 1, j - 1) + a(i, j)$．
    
    Therefore, if $a$ is the original array and $d$ is the difference array, then:
    
    $a(i, j) = a(i - 1, j) + a(i, j - 1) - a(i - 1, j - 1) + d(i, j)$
    
    Rearranging gives the formula for the two-dimensional difference array.
    
    $d(i, j) = a(i, j) - a(i - 1, j) - a(i, j - 1) + a(i - 1, j - 1)$．

Thus, for the submatrix whose upper-left corner is $(x_1, y_1)$ and lower-right corner is $(x_2, y_2)$, adding $v$ is equivalent to, on the difference array, adding to $d(x_1, y_1)$ and $d(x_2 + 1, y_2 + 1)$ the value $v$, and adding to $d(x_2 + 1, y_1)$ and $d(x_1, y_2 + 1)$ the value $-v$.

For the reason, write these four $d$ values using the definition and analyze how each term changes.

For example, if the initial difference array is $0$, then after adding to the submatrix $a(2, 2) \ldots a(3, 4)$ the value $v$, the difference array becomes:

$$
\begin{pmatrix}0&0&0&0&0\\0&v&0&0&-v\\0&0&0&0&0\\0&-v&0&0&v\end{pmatrix}
$$

(Here the submatrix $a(2, 2) \ldots a(3, 4)$ is exactly the $2 \times 3$ matrix located in the center above.)

Therefore, submatrix addition is performed by transforming it into four point-add operations on the difference array.

Now consider querying a submatrix sum.

For a point $(x, y)$, its two-dimensional prefix sum can be written as:

$$
\sum_{i = 1}^x\sum_{j = 1}^y\sum_{h = 1}^i\sum_{k = 1}^j d(h, k)
$$

The reason is that the prefix sum of the prefix sum of the difference array is exactly the original prefix sum.

Similar to the one-dimensional "range add, range sum" problem, count the number of appearances of $d(h, k)$; it is $(x - h + 1) \times (y - k + 1)$.

Then continue the derivation:

$$
\begin{aligned}
&\sum_{i = 1}^x\sum_{j = 1}^y\sum_{h = 1}^i\sum_{k = 1}^j d(h, k)
\\=&\sum_{i = 1}^x\sum_{j = 1}^y d(i, j) \times (x - i + 1) \times (y - j + 1)
\\=&\sum_{i = 1}^x\sum_{j = 1}^y d(i, j) \times (xy + x + y + 1) - d(i, j) \times i \times (y + 1) - d(i, j) \times j \times (x + 1) + d(i, j) \times i \times j
\end{aligned}
$$

Therefore, we need to maintain four Fenwick trees, storing the sum information of $d(i, j)$, $d(i, j) \times i$, $d(i, j) \times j$, and $d(i, j) \times i \times j$, respectively.

Of course, as in the one-dimensional case, if we only need submatrix addition and point queries, maintaining one difference array and querying its prefix sum is enough.

The code is as follows:

???+ note "Implementation"
    ```cpp
    using ll = long long;
    ll t1[N][N], t2[N][N], t3[N][N], t4[N][N];
    
    void add(ll x, ll y, ll z) {
      for (int X = x; X <= n; X += lowbit(X))
        for (int Y = y; Y <= m; Y += lowbit(Y)) {
          t1[X][Y] += z;
          t2[X][Y] += z * x;  // Use z * x, not z * X; similarly below.
          t3[X][Y] += z * y;
          t4[X][Y] += z * x * y;
        }
    }
    
    void range_add(ll xa, ll ya, ll xb, ll yb,
                   ll z) {  // Submatrix from (xa, ya) to (xb, yb).
      add(xa, ya, z);
      add(xa, yb + 1, -z);
      add(xb + 1, ya, -z);
      add(xb + 1, yb + 1, z);
    }
    
    ll ask(ll x, ll y) {
      ll res = 0;
      for (int i = x; i; i -= lowbit(i))
        for (int j = y; j; j -= lowbit(j))
          res += (x + 1) * (y + 1) * t1[i][j] - (y + 1) * t2[i][j] -
                 (x + 1) * t3[i][j] + t4[i][j];
      return res;
    }
    
    ll range_ask(ll xa, ll ya, ll xb, ll yb) {
      return ask(xb, yb) - ask(xb, ya - 1) - ask(xa - 1, yb) + ask(xa - 1, ya - 1);
    }
    ```

## Frequency Fenwick Tree and Applications

We know that an ordinary Fenwick tree is built directly on the original sequence, and $c_6$ represents the interval information of $a[5 \ldots 6]$.

However, we can also build a Fenwick tree on the frequency array of the original sequence. This is a frequency Fenwick tree.

??? note "What is a frequency array?"
    A sequence $a$'s frequency array $b$ satisfies that $b[x]$ is the number of occurrences of $x$ in $a$.
    
    For example, the frequency array of $a = (1, 3, 4, 3, 4)$ is $b = (1, 0, 2, 2)$.
    
    Clearly, the size of $b$ depends on the value range of $a$.
    
    If the value range of the original sequence is too large, and what matters is not the concrete values but the relative order between values, we often [discretize](../misc/discrete.md) the original array before building the frequency array.
    
    In addition, a frequency array is a representation of the original array that ignores order: it focuses on the multiset of elements and ignores their order. If two arrays differ only in order and contain the same elements, their frequency arrays are the same.
    
    Therefore, for problems where the order of the given array does not affect the answer, thinking in terms of the frequency array is usually more intuitive, such as [\[NOIP2021\] Sequence](https://www.luogu.com.cn/problem/P7961).

Using a frequency Fenwick tree, we can solve some classic problems.

### Point Updates, Query the Global $k$-th Smallest

Here we only discuss the $k$-th smallest. The $k$-th largest problem can be transformed into the $k$-th smallest problem by a simple calculation.

This problem can use discretization. If the value range of the original sequence $a$ is too large, discretize it before building the frequency array $b$. Note that values involved in point updates must also be discretized; it is not enough to discretize only the elements initially in $a$.

For point updates, simply transform a point update on the original sequence into point updates on the frequency array. Specifically, if $a[x]$ changes from $y$ to $z$, then in the frequency array $b$, decrement $b[y]$ by $1$ and increment $b[z]$ by $1$.

To query the $k$-th smallest, we can binary search $x$ and query the prefix sum of $[1, x]$ in the frequency array. Find $x_0$ such that the prefix sum of $[1, x_0]$ is $< k$ while the prefix sum of $[1, x_0 + 1]$ is $\ge k$; then the $k$-th smallest number is $x_0 + 1$ (here the prefix sum of $[1, 0]$ is considered to be $0$).

This has time complexity $\Theta(\log^2n)$.

Consider replacing binary search with binary lifting.

Set $x = 0$ and $\mathrm{sum} = 0$, then enumerate $i$ from $\log_2n$ down to $0$:

-   Query, in the frequency array, the range sum of $[x + 1 \ldots x + 2^i]$, denoted $t$.
-   If $\mathrm{sum} + t < k$, the extension succeeds, so set $x \gets x + 2^i$ and $\mathrm{sum} \gets \mathrm{sum} + t$; otherwise, the extension fails and we do nothing.

The resulting $x$ is the maximum value whose prefix sum over $[1 \ldots x]$ is $< k$, so the final answer is $x + 1$.

At first glance this method does not improve time efficiency, but in fact, querying the range sum of $[x + 1 \ldots x + 2^i]$ only requires accessing the value of $c[x + 2^i]$.

The reason is simple. Consider $\operatorname{lowbit}(x + 2^i)$: it must be $2^i$, because $x$ has previously only accumulated terms $2^j$ with $j > i$. Therefore, the interval represented by $c[x + 2^i]$ is exactly $[x + 1 \ldots x + 2^i]$.

Thus, the time complexity is reduced to $\Theta(\log n)$.

???+ note "Implementation"
    === "C++"
        ```cpp
        // Query the k-th smallest in a frequency Fenwick tree.
        int kth(int k) {
          int sum = 0, x = 0;
          for (int i = log2(n); ~i; --i) {
            x += 1 << i;                   // Try to extend.
            if (x > n || sum + t[x] >= k)  // If the extension fails.
              x -= 1 << i;
            else
              sum += t[x];
          }
          return x + 1;  // Return n + 1 if not found.
        }
        ```
    
    === "Python"
        ```python
        # Query the k-th smallest in a frequency Fenwick tree.
        def kth(k):
            sum = 0
            x = 0
            i = int(log2(n))
            while ~i:
                x = x + (1 << i)  # Try to extend.
                if x > n or sum + t[x] >= k:  # If the extension fails.
                    x = x - (1 << i)
                else:
                    sum = sum + t[x]
                i = i - 1
            return x + 1  # Return n + 1 if not found.
        ```

### Global Inversions (Global Two-Dimensional Partial Order)

Related reading and reference implementations: [Inversions](../math/permutation.md#inversions)

Global inversions can also be solved elegantly with a frequency Fenwick tree. The problem is: given length $n$ and sequence $a$, count in $a$ the number satisfying $i < j$ and $a[i] > a[j]$ of pairs $(i, j)$.

This problem can use discretization. If the value range of the original sequence $a$ is too large, discretize it before building the frequency array $b$.

Enumerate from $n$ to $1$ in reverse order the index $i$ as the first element in an inversion, compute how many $j > i$ satisfy $a[j] < a[i]$, and accumulate the answer.

In fact, we only need to do the following (let the current $a[i] = x$):

-   Query the prefix sum of $b[1 \ldots x - 1]$, which is the number of inversions whose left endpoint is $a[i]$.
-   Increment $b[x]$ by $1$.

The reason is natural: elements appearing in $b[1 \ldots x-1]$ are certainly smaller than the current $x = a[i]$, and because $i$ is enumerated in reverse order, the elements already in the frequency array have indices $j$ in the original array greater than the current index $i$.

For example, let $a = (4, 3, 1, 2, 1)$.

Scan $i$ from $5 \to 1$:

-   $a[5] = 1$: query the prefix sum of $b[1 \ldots 0]$, which is $0$; increment $b[1]$ by $1$, so $b = (1, 0, 0, 0)$.
-   $a[4] = 2$: query the prefix sum of $b[1 \ldots 1]$, which is $1$; increment $b[2]$ by $1$, so $b = (1, 1, 0, 0)$.
-   $a[3] = 1$: query the prefix sum of $b[1 \ldots 0]$, which is $0$; increment $b[1]$ by $1$, so $b = (2, 1, 0, 0)$.
-   $a[2] = 3$: query the prefix sum of $b[1 \ldots 2]$, which is $3$; increment $b[3]$ by $1$, so $b = (2, 1, 1, 0)$.
-   $a[1] = 4$: query the prefix sum of $b[1 \ldots 3]$, which is $4$; increment $b[4]$ by $1$, so $b = (2, 1, 1, 1)$.

Therefore, the final answer is $0 + 1 + 0 + 3 + 4 = 8$.

Notice that after visiting $i$, the two steps of querying $b[1 \ldots x - 1]$ and incrementing $b[x]$ can be swapped: increment $b[x]$ first, then query $b[1 \ldots x - 1]$. This does not affect the answer. There are two ways to see this:

-   Modifying $b[x]$ does not affect the query on $b[1 \ldots x - 1]$.
-   After swapping the order, we are effectively counting pairs with $i \le j$ and $a[i] > a[j]$. Since when $i = j$, $a[i] > a[j]$ is impossible, $i \le j$ is equivalent to $i < j$ here, so this is equivalent to the original inversion problem.

If we query the number of non-strict inversions ($i < j$ and $a[i] \ge a[j]$), then we should query the sum of $b[1 \ldots x]$. In this case, the two steps cannot be swapped. Again, there are two ways to see this:

-   Modifying $b[x]$ **does affect** the query on $b[1 \ldots x]$.
-   After swapping the order, we are effectively counting pairs with $i \le j$ and $a[i] \ge a[j]$. Since when $i = j$, $a[i] \ge a[j]$ always holds, $i \le j$ is **not equivalent** to $i < j$, so it is **not equivalent** to the original problem.

If we want to count pairs with $i \le j$ and $a[i] \ge a[j]$, then these two steps should be swapped.

For the original inversion problem, another method is to enumerate $j$ in forward order and query how many $i < j$ satisfy $a[i] > a[j]$. The method is as follows (let $x = a[j]$):

-   Query the range sum of $b[x + 1 \ldots V]$ ($V$ is the size of $b$, namely the value range of $a$, or the discretized value range).
-   Increment $b[x]$ by $1$.

Reason: elements appearing in $b[x + 1 \ldots V]$ are certainly greater than the current $x = a[j]$, and because $j$ is enumerated in forward order, elements already in the frequency array have indices $i$ in the original array less than the current index $j$.

In addition, inversions can also be counted by [merge sort](../basic/merge-sort.md#inversions). This method avoids discretization. Its time complexity is also $O(n\log n)$. Reference implementations of both algorithms are in the [Inversions](../math/permutation.md#inversions) section.

## Fenwick Trees for Non-Invertible Information

For example, maintaining range extrema.

Note that although this method has little code, both point updates and range queries take $\Theta(\log^2n)$ time, which is worse than the $\Theta(\log n)$ time complexity of a segment tree.

### Range Queries

We still follow the previous idea: jump backward from $r$ along $\operatorname{lowbit}$, but we cannot jump to the left of $l$.

Therefore, if we reach $c[x]$, first check whether the next position $x - \operatorname{lowbit}(x)$ is less than $l$:

-   If it is less than $l$, directly merge the **single point $\boldsymbol{a[x]}$** into the total information, then jump to $c[x - 1]$.
-   If it is at least $l$, it does not cross the boundary, so merge $c[x]$ normally and jump to $c[x - \operatorname{lowbit}(x)]$.

The following code uses querying the range maximum as an example:

???+ note "Implementation"
    ```cpp
    int getmax(int l, int r) {
      int ans = 0;
      while (r >= l) {
        ans = max(ans, a[r]);
        --r;
        for (; r - lowbit(r) >= l; r -= lowbit(r)) {
          // Do not write the loop condition as r - lowbit(r) + 1 >= l;
          // otherwise, when l = 1, r jumps to 0 and the loop never terminates.
          ans = max(ans, C[r]);
        }
      }
      return ans;
    }
    ```

It can be proven that the time complexity of the above algorithm is $\Theta(\log^2n)$.

??? note "Time complexity proof"
    Consider the highest bit where $r$ and $l$ differ. At this bit, $r$ must be $1$ and $l$ must be $0$ (because $r \ge l$).
    
    If $r$ still has a $1$ after this bit, then we must have $r - \operatorname{lowbit}(r) \ge l$, so the next step changes, in $r$, the lowest $1$ to $0$.
    
    If in $r$ this bit $1$ is $r$'s lowest $1$, then whether we do $r \gets r - \operatorname{lowbit}(r)$ or $r \gets r - 1$, this bit of $r$ as $1$ will become $0$.
    
    Therefore, $r$, after at most $\log n$ transformations, has the highest bit where $r$ and $l$ differ decrease by one. Hence the total time complexity is $\Theta(\log^2n)$.

### Point Updates

???+ note "Note"
    Please understand the following two properties of the Fenwick tree structure before studying this section.
    
    -   Let $u = s \times 2^{k + 1} + 2^k$. Then it has $k = \log_2\operatorname{lowbit}(u)$ children, numbered $u - 2^t(0 \le t < k)$.
    -   For $u$, the intervals covered by the corresponding $c$ values of all children concatenate exactly into $[l(u), u - 1]$.
    
    The meanings and proofs of these two properties can be found in the [Properties of the Fenwick Tree as a Tree](#properties-of-the-fenwick-tree-as-a-tree) section on this page.

After updating $a[x]$, we only need to update values where $y$ is an ancestor of $x$ in the Fenwick tree structure, namely $c[y]$.

For extrema (using maximum as an example), a common wrong idea is: if $a[x]$ is changed to $p$, update every $c[y]$ to $\max(c[y], p)$. Here is a counterexample: in $(1, 2, 3, 4, 5)$, change $5$ to $4$. The maximum is $4$, but the above update would give $5$. Directly changing $c[y]$ to $p$ is also wrong; a counterexample is changing $3$ to $4$ in the same example.

In fact, for non-invertible information, using only $p$, there is no way to directly modify $c[y]$. This is because an update is equivalent to "removing" the old number from the original interval and then adding a new number. The effect of "removal" on interval information is equivalent to applying an inverse operation, but non-invertible information has no inverse operation, so $c[y]$ cannot be modified directly.

In other words, for every affected $c[y]$, we must reconstruct the information of that interval.

Consider the children of $c[y]$. Their information must be correct (because we update children before parents), and these children exactly form the covered interval $[l(y), y - 1]$. Merging one additional point $a[y]$ then gives $[l(y), y]$, namely $c[y]$. In this way, by merging at most $\log n$ intervals, each $c$ that needs modification can be reconstructed.

???+ note "Implementation"
    ```cpp
    void update(int x, int v) {
      a[x] = v;
      for (int i = x; i <= n; i += lowbit(i)) {
        // Enumerate affected intervals.
        C[i] = a[i];
        for (int j = 1; j < lowbit(i); j *= 2) {
          C[i] = max(C[i], C[i - j]);
        }
      }
    }
    ```

It is easy to see that the time complexity of the above algorithm is $\Theta(\log^2n)$.

### Building the Tree

We can split it into $n$ point updates, building the tree in $\Theta(n\log^2n)$ time.

There is also a $\Theta(n)$ building method; see method one in the [$\Theta(n)$ building](#thetan-building) section on this page.

## Tricks

### $\Theta(n)$ Building

Use maintaining range sums as an example.

Method one:

The value of each node is obtained by summing the values of all its directly connected children. Therefore, we can consider contributions in reverse: after determining the value of a child, use it to update its direct parent.

???+ note "Implementation"
    === "C++"
        ```cpp
        // Θ(n) building
        void init() {
          for (int i = 1; i <= n; ++i) {
            t[i] += a[i];
            int j = i + lowbit(i);
            if (j <= n) t[j] += t[i];
          }
        }
        ```
    
    === "Python"
        ```python
        # Θ(n) building
        def init():
            for i in range(1, n + 1):
                t[i] = t[i] + a[i]
                j = i + lowbit(i)
                if j <= n:
                    t[j] = t[j] + t[i]
        ```

Method two:

As mentioned above, the interval represented by $c[i]$ is $[i-\operatorname{lowbit}(i)+1, i]$. Therefore, we can first preprocess a prefix-sum array $\mathrm{sum}$, then compute the $c$ array.

???+ note "Implementation"
    === "C++"
        ```cpp
        // Θ(n) building
        void init() {
          for (int i = 1; i <= n; ++i) {
            t[i] = sum[i] - sum[i - lowbit(i)];
          }
        }
        ```
    
    === "Python"
        ```python
        # Θ(n) building
        def init():
            for i in range(1, n + 1):
                t[i] = sum[i] - sum[i - lowbit(i)]
        ```

### Timestamp Optimization

This is a common technique for handling multiple test cases. If we forcibly clear the Fenwick tree every time new data is read, it may cause a timeout. Therefore, use a $\mathrm{tag}$ marker to store the last usage time of the current node (that is, the most recent test case in which it was used). During each operation, compare the time in $\mathrm{tag}$ at this position with the current time to determine whether this position should be treated as $0$ or as the value stored in the array.

???+ note "Implementation"
    === "C++"
        ```cpp
        // Timestamp optimization
        int tag[MAXN], t[MAXN], Tag;
        
        void reset() { ++Tag; }
        
        void add(int k, int v) {
          while (k <= n) {
            if (tag[k] != Tag) t[k] = 0;
            t[k] += v, tag[k] = Tag;
            k += lowbit(k);
          }
        }
        
        int getsum(int k) {
          int ret = 0;
          while (k) {
            if (tag[k] == Tag) ret += t[k];
            k -= lowbit(k);
          }
          return ret;
        }
        ```
    
    === "Python"
        ```python
        # Timestamp optimization
        tag = [0] * MAXN
        t = [0] * MAXN
        Tag = 0
        
        
        def reset():
            Tag = Tag + 1
        
        
        def add(k, v):
            while k <= n:
                if tag[k] != Tag:
                    t[k] = 0
                t[k] = t[k] + v
                tag[k] = Tag
                k = k + lowbit(k)
        
        
        def getsum(k):
            ret = 0
            while k:
                if tag[k] == Tag:
                    ret = ret + t[k]
                k = k - lowbit(k)
            return ret
        ```

## Examples

-   [Fenwick Tree 1: Point Updates, Range Queries](https://loj.ac/problem/130)
-   [Fenwick Tree 2: Range Updates, Point Queries](https://loj.ac/problem/131)
-   [Fenwick Tree 3: Range Updates, Range Queries](https://loj.ac/problem/132)
-   [Two-Dimensional Fenwick Tree 1: Point Updates, Range Queries](https://loj.ac/problem/133)
-   [Two-Dimensional Fenwick Tree 2: Range Updates, Point Queries](https://loj.ac/problem/134)
-   [Two-Dimensional Fenwick Tree 3: Range Updates, Range Queries](https://loj.ac/problem/135)
