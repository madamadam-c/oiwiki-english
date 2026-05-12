## Introduction

The persistent Trie works similarly to a persistent segment tree: each update only modifies the newly added or changed nodes and retains unchanged nodes, linking edges from the previous version so that each version's Trie root yields a complete Trie containing all information.

In most persistent Trie problems, the Trie appears in the form of a [01-Trie](../string/trie.md#maintaining-xor-extremes).

??? note "Example – Maximum XOR Sum"
    For a length-$n$ array $a$, maintain the following operations:

    1. Append a number $x$ to the end of the array, increasing its length $n$ by $1$.
    2. Given a query interval $[l,r]$ and a value $k$, find, when $l\le p\le r$, the maximum of $k \oplus \bigoplus^{n}_{i=p} a_i$.

## Process

The target value can be tricky. Using the standard technique for prefix XOR, let $s_x=\bigoplus_{i=1}^x a_i$. Then the expression simplifies to $s_{p-1}\oplus s_n\oplus k$. Notice that $s_n \oplus k$ is fixed during a query, so the query reduces to finding the maximum XOR in the interval $[l-1,r-1]$ with the fixed value ($s_n\oplus k$).

Following the persistent segment-tree mindset, we build a Trie for the whole interval. We insert each prefix in the interval into this Trie, and during the query we greedily move to the child whose bit differs from the current bit of the constant to maximize the XOR.

To query an interval, we use the prefix-sum/difference idea: two prefix-Trie versions (the two historical versions after each insertion) are subtracted to obtain the Trie representing the interval. Using a dynamic-node-creation approach, we avoid adding nodes that have never been accessed, reducing memory usage.

```cpp
--8<-- "docs/ds/code/persistent-trie/persistent-trie_1.cpp"
```

## References

-   [XOR operator in LaTeX](https://en.wikipedia.org/wiki/Exclusive_or#Symbols)
-   [Persistent Trie - CP-Algorithms](https://cp-algorithms.com/data_structures/trie.html)
