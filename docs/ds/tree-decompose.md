author: ouuan, Ir1d, Marcythm, Xeonacid

## Tree Blocking Methods

You can refer to [True Mo's Algorithm on Trees](../misc/mo-algo-on-tree.md).

You can also refer to [ouuan's blog / Detailed explanation of Mo's algorithm, Mo's algorithm with modifications, and Mo's algorithm on trees / Mo's algorithm on trees](https://ouuan.github.io/莫队、带修莫队、树上莫队详解/#树上莫队).

Mo's algorithm on trees can also refer to the two articles above.

## Applications of Tree Blocking

Besides being used in Mo's algorithm, tree blocking can also be applied flexibly to some tree problems. However, problems that can be solved with tree blocking often have better approaches, so there are relatively few related problems.

Incidentally, the tree-blocking solution for "gty's Girl Tree" can be defeated by a star graph.

### [BZOJ4763 Xuehui](https://hydro.ac/p/bzoj-P4763)

First perform tree blocking. Then, for each key point in each block, preprocess the bitset of colors on the path from it to every key-point ancestor, and preprocess each key point's nearest key-point ancestor. The complexity is $O(n\sqrt n+\frac{nc}{32})$, where $n\sqrt n$ is the complexity of brute-force jumping upward from every key point, and $\frac{nc}{32}$ is the cost of storing $O(n)$ `bitset`s.

When answering a query, first brute-force jump from the path endpoints to the key points of their blocks. Then jump block by block upward from the key point of the current block until reaching the block containing the $lca$, and finally brute-force jump to the $lca$. The `bitset`s between key points have already been preprocessed; the remaining part is computed during brute-force jumps. The complexity of a single query is $O(\sqrt n+\frac c{32})$, where $\sqrt n$ is the cost of brute-force jumping inside blocks and jumping upward between blocks, and $O(\frac c{32})$ is the cost of merging preprocessed results with brute-force results. The number of colors can be counted with `bitset`'s `count()`, and $\operatorname{mex}$ can be found with `bitset`'s `_Find_first()`.

Therefore, the total complexity is $O((n+m)(\sqrt n+\frac c{32}))$.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/ds/code/tree-decompose/tree-decompose_1.cpp"
    ```

### [BZOJ4812 Yuno Plays Poker](https://hydro.ac/p/bzoj-P4812)

This problem is basically the same as the previous one. The only difference is how to compute the answer after obtaining the `bitset`.

~~Because BZOJ uses a total time limit over all test points and is hard to hack, `_Find_next()` can pass.~~

The intended solution processes every $16$ bits together. Preprocess, for all $2^{16}$ possible states, the number of consecutive $1$s at the high end, the number of consecutive $1$s at the low end, and the middle contribution. However, this requires implementing `bitset` manually, because the standard library `bitset` cannot extract an arbitrary group of $16$ bits.

The code can refer to [this blog post](https://www.cnblogs.com/FallDream/p/bzoj4763.html).
