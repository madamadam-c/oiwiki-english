Space optimization techniques are not very common in algorithm competitions, but they are still worth discussing.

## Information Entropy

Information entropy describes the lower bound on the space required to store data. If the actually available space is below this lower bound, information must be lost.

???+ note "Definition"
    For a random variable $X$, define its information entropy as
    
    $$
    H(X)=-\sum_{x}P(X=x)\log_2 P(X=x).
    $$

The logarithm base in the definition is $2$ because each bit of information stored in a computer has only $2$ possible values: $0$ and $1$.

For example, suppose $X$ follows the uniform distribution on $\{1,2,\dots,n\}$. Its information entropy is

$$
H(X)=-\sum_{i=1}^n\frac{1}{n}\log_2\frac{1}{n}=\log_2 n,
$$

so we need at least $\log_2 n$ bits to store an integer from $1$ to $n$.

### Example

???+ note "[\[WC2022\] Guess the Word](https://www.luogu.com.cn/problem/P8079)"
    This is an interactive problem. You need to guess a 5-letter word within a limited number of attempts. Each guess must be a word that exists in the word list. If the guess is correct, the game ends; after each wrong guess, the interaction library returns which letters are in the correct positions and which letters appear in the target word but are in wrong positions.
    
    ??? note "Solution"
        See [Solving Wordle using information theory - 3Blue1Brown](https://www.bilibili.com/video/BV1zZ4y1k7Jw).
        
        Consider computing information entropy. Clearly, choosing a word with high information entropy for each guess can minimize the expected number of guesses as much as possible.
        
        Since this problem gives the first letter of the answer before guessing, we can preprocess the optimal guess for each possible first letter.
        
        Also, if few words remain, we can consider outputting words that may be the answer first, reducing the number of attempts.

## Common Techniques

### Avoid Storing Unnecessary Data

For example:

-   In a [persistent segment tree](../ds/persistent-seg.md), because each modification only creates $O(\log n)$ new nodes, we do not need to store the full segment tree for every version; we only need to record the new nodes.
-   Consider [graph storage](../graph/save.md). For sparse graphs, using an adjacency matrix stores many useless $0$s, so adjacency lists are usually used for sparse graphs.
-   Each element of a `bool` array occupies one byte of space. When necessary, it can be replaced with `std::vector<bool>` or [bitset](../lang/csl/bitset.md), where each element occupies only one bit.
-   In [knapsack DP](../dp/knapsack.md), for 0-1 knapsack, each DP value only uses data from the previous computation, so we can optimize space with a rolling array and only record the current DP values.

### Use Data Properties

Consider a [DSU](../ds/dsu.md) supporting path compression and union by size/rank. The traditional implementation needs two arrays, recording the parent node number and subtree size separately.

Notice that:

1.  After path compression is applied, for a tree in the DSU, we only need to record the subtree size corresponding to the root node.
2.  The parent of a root node is always itself.

We can use the properties of signed integers: negative numbers represent root nodes, and positive numbers represent non-root nodes. Therefore, a DSU supporting path compression and heuristic merging can be implemented with only one array.

???+ note "Implementation"
    ```cpp
    --8<-- "docs/misc/code/space-optimization/space-optimization_1.cpp"
    ```

## Exercises

-   [QOJ 6669 Mapa](https://qoj.ac/problem/6669)
-   [\[SDOI/SXOI2022\] Nowhere to Store](https://www.luogu.com.cn/problem/P8353)

## References and Further Reading

1.  Chen Zhixuan. *A Brief Discussion on Space Optimization Problems in Informatics Competitions*. 2022 National Training Team Paper
2.  [Information theory - Wikipedia](https://en.wikipedia.org/wiki/Information_theory)
3.  [A Brief Discussion on Information Theory - Luogu Column](https://www.luogu.com.cn/article/i65ca8i5)
