author: 2008verser, aofall, CoelacanthusHex, Early0v0, Great-designer, Marcythm, Persdre, shuzhouliu, Tiphereth-A, Enter-tainer, gavinliu266, gi-b716, hjsjhn, Ir1d, MegaOwIer, wjy-yy, c-forrest

Permutations and arrangements are common concepts in various problems.

???+ warning "This article does not discuss permutations (combinatorics)"
    This article discusses full permutations, not the number of permutations in combinatorics. For related content on permutation numbers, refer to [Combinatorics](./combinatorics/combination.md).

???+ info "Convention"
    In this article, if not specified otherwise, we always discuss finite sets.

## Definition

A bijection (one-to-one correspondence) from a set $X$ to itself is called a **permutation** of $X$. If the set $X$ also has a [total order](./order-theory.md#二元关系) relation, then a permutation of it is also often called a **(total) arrangement** or **permutation**. This total order relation is called the natural order on the set.

??? info ""Permutation" vs "Arrangement""
    In Chinese terminology, the word translated as "permutation" usually refers to changing the order of elements, while the word translated as "arrangement" usually refers to arranging elements in a line. When there is a natural order between elements, these two concepts are the same: "arrangement" can be seen as the result of "permutation"; compared to the natural order of elements, the order in an "arrangement" specifies the "permutation". Since this article always assumes a natural order exists when using the term "arrangement," we will not deliberately distinguish between these two concepts.

    Of course, elements without a natural order can also be "arranged." This type of "arrangement" often appears in combinatorial counting problems. This is beyond the scope of this article.

If the size of set $X$ is $n$, then the total number of permutations on $X$ is $n!$. In particular, $0! = 1$, meaning there is exactly one permutation on the empty set, namely the empty permutation.

???+ info "Notation"
    Permutations discuss the correspondence between elements, not what the elements specifically are. Therefore, when discussing a set of size $n$, we usually assume the set under discussion is $\{1, 2, \cdots, n\}$; when a natural order is needed on the set, we usually assume the natural order on natural numbers is used.

## Representation Methods

There are multiple ways to represent permutations. Here, using the following permutation as an example, we discuss different representation methods.

$$
\sigma(1) = 2,\
\sigma(2) = 6,\
\sigma(3) = 5,\
\sigma(4) = 4,\
\sigma(5) = 3,\
\sigma(6) = 1.
$$

### Two-line notation

A permutation on set $X = \{x_1, x_2, \cdots, x_n\}$ can be represented as

$$
\sigma=\begin{pmatrix}x_1&x_2&\cdots&x_n\\
x_{p_1}&x_{p_2}&\cdots&x_{p_n}
\end{pmatrix}.
$$

This represents that permutation $\sigma$ maps element $x_i$ to $x_{p_i}$. Here, of course, we need $X = \{x_{p_1}, x_{p_2}, \cdots, x_{p_n}\}$. In the two-line notation of a permutation, the order of elements in the first row is not important; what matters is the correspondence between the two rows.

For example, the previous example can be written in two-line notation as

$$
\sigma=
\begin{pmatrix}
1 & 2 & 3 & 4 & 5 & 6 \\
2 & 6 & 5 & 4 & 3 & 1
\end{pmatrix},
$$

or it can also be written as

$$
\sigma=
\begin{pmatrix}
6 & 5 & 4 & 3 & 2 & 1 \\
1 & 3 & 4 & 5 & 6 & 2
\end{pmatrix}.
$$

### One-line notation

Often, a set $X$ has a natural order. If in the two-line notation we default to writing the first row in natural order and omit the first row, then the permutation can be expressed as

$$
\sigma = \sigma(1)\sigma(2)\cdots\sigma(n).
$$

This is more like the concept of arrangement in natural language. Therefore, sometimes this ordered tuple is called a permutation.

The previous example in one-line notation is

$$
\sigma = 265431.
$$

This one-line notation is often used to compare the sizes of different permutations.

### Cycle notation

There is a more compact way to express permutations, called cycle notation. It expresses a permutation as a product of disjoint cycles. Below we describe the steps to write a given permutation in cycle notation.

Given a permutation $\sigma$, it can be written in cycle notation through the following steps:

1. If there are still unwritten elements in $X$, write a left parenthesis and any such element.
2. When the last written element is $x$:
    - If $\sigma(x)$ has already been written before, write a right parenthesis and return to step 1.
    - If $\sigma(x)$ has not been written yet, write $\sigma(x)$ and continue with step 2.
3. When all elements of $X$ have been written, end.

Each pair of parentheses is a cycle. The number of elements in parentheses is called the length of the corresponding cycle. In practice, cycles of length one are often omitted.

The previous example in cycle notation is

$$
\sigma = (126)(35)(4) = (126)(35).
$$

In the identity transformation, all cycles have length one, which is often written as $(1)$ rather than all being omitted.

## Composition

The composition of permutations is the composition of mappings. The composition of permutations is also often called permutation multiplication.

Given two permutations

$$
\sigma=\begin{pmatrix}x_1&x_2&\cdots&x_n\\ x_{p_1}&x_{p_2}&\cdots&x_{p_n}\end{pmatrix},\ \pi=\begin{pmatrix}x_{p_1}&x_{p_2}&\cdots&x_{p_n}\\ x_{q_1}&x_{q_2}&\cdots&x_{q_n}\end{pmatrix},
$$

then their product $\pi\circ\sigma$ has the value

$$
\pi\circ\sigma=\begin{pmatrix}x_1&x_2&\cdots&x_n\\
x_{q_1}&x_{q_2}&\cdots&x_{q_n}\end{pmatrix}.
$$

Simply put, it first goes through the mapping $\sigma$, then through the mapping $\pi$. Note that in the two-line notation above, the order of the second row of the inner mapping $\sigma$ is consistent with the first row of the outer mapping $\pi$.

Since permutations $\sigma$ and $\pi$ are essentially two mappings, we have $(\pi\circ\sigma)(x) = \pi(\sigma(x))$. The evaluation order of permutation composition is right-to-left. Permutation multiplication does not satisfy the commutative law, so using the wrong order may lead to incorrect results.

The product of multiple consecutive permutations is called the power of a permutation, which can be accelerated using [binary exponentiation](./binary-exponentiation.md#多次置换).

### Inverse permutation

Since a permutation is a bijection, every permutation has a corresponding inverse permutation.

Given a permutation

$$
\sigma=\begin{pmatrix}x_1&x_2&\cdots&x_n\\ x_{p_1}&x_{p_2}&\cdots&x_{p_n}\end{pmatrix},
$$

its inverse permutation is

$$
\sigma^{-1}=\begin{pmatrix}x_{p_1}&x_{p_2}&\cdots&x_{p_n}\\x_1&x_2&\cdots&x_n\end{pmatrix}.
$$

In cycle notation, to get the inverse of a permutation, we just need to invert each cycle; to invert a cycle, we just reverse the order of elements. For example, the inverse permutation of the example above in cycle notation is

$$
\sigma^{-1} = (621)(53) = (162)(35).
$$

Given a permutation of $1 \sim n$ and the sequence of rankings of each element, they are inverses of each other.

## Cycles

A **cycle** itself is a special permutation. The characteristic of a cycle is that starting from any point $x$ in the cycle, you can obtain another point $y$ in the cycle by repeatedly applying the permutation $\sigma$. A cycle of length $k$ is also called a **$k$-cycle**. Applying a $k$-cycle $k$ times yields the identity transformation, i.e., every element returns to its starting position.

The cycle notation of a permutation can be seen as writing the permutation as a product of these special permutations (i.e., cycles). Therefore, the cycle notation of a permutation can also be seen as the **cycle decomposition** of the permutation. For each permutation, the way it decomposes into a product of cycles is unique up to order. Cycles can be seen as the basic building blocks that make up a permutation.

The cycle decomposition of a permutation has clear geometric significance. If we view each ordered pair $(x, \sigma(x))$ in a permutation on set $S$ as an edge in a directed graph with $S$ as vertices, then these cycles are the cycles in this directed graph. If permutation $\sigma$ can be decomposed into $m$ cycles, it means the corresponding directed graph has a total of $m$ cycles (including self-loops). These cycles are naturally disjoint.

### Fixed points

A $1$-cycle is a **fixed point** of a permutation. For a permutation $\sigma$ on set $X$, we usually use $X^\sigma$ to represent the set of fixed points of $\sigma$, i.e., $X^\sigma = \{x \in X : \sigma(x) = x\}$.

### Transpositions

A $2$-cycle is also called a **transposition**. That is, a transposition is a permutation that only swaps one pair of elements. Its cycle notation is $(x_i x_j)$, meaning it swaps the positions of $x_i$ and $x_j$.

Any permutation can be written as a product of a series of transpositions. This is equivalent to saying that any permutation can be restored to a specified normal order through a series of operations that swap two elements. This is exactly what swap-based sorting algorithms do.

Furthermore, the correctness of [bubble sort](../basic/bubble-sort.md) actually shows that any permutation can be written as a product of a series of adjacent transpositions. Here, an **adjacent transposition** refers to a transposition that only swaps adjacent elements.

## Properties

In applications, we often need to focus on the properties of individual permutations.

### Parity

The way to decompose a cycle into transpositions is not unique. For example,

$$
(123) = (13)(12) = (12)(23) = (12)(13)(12)(13).
$$

However, when decomposing a permutation into a series of transpositions, the parity (odd/even) of the number of transpositions required is fixed. The parity of the number of transpositions in a transposition decomposition is also called the **parity** of the permutation.

A permutation that can be decomposed into an even number of transpositions is called an even permutation, and one that can be decomposed into an odd number of transpositions is called an odd permutation. When $n \ge 2$, the number of odd permutations and even permutations of size $n$ is the same.

### Sign

Based on the parity of a permutation, we can also define the **sign** of a permutation, denoted $\operatorname{sgn}\sigma$. The sign of an even permutation is defined as $+1$, and the sign of an odd permutation is defined as $-1$.

The sign of the product of permutations equals the product of their signs, i.e.,

$$
\operatorname{sgn}(\pi\circ\sigma)=\operatorname{sgn}
\pi\cdot\operatorname{sgn}\sigma.
$$

In other words, the composition of two permutations with the same parity is an even permutation, and the composition of two permutations with different parities is an odd permutation. This conclusion is obvious from the perspective of transposition decomposition.

In particular, a single transposition always changes the parity of a permutation. This also explains why although the way to decompose into transpositions is not unique, the parity of the number of transpositions required is fixed.

The sign of a permutation appears in the [Leibniz expansion of determinants](../math/linear-algebra/determinant.md#全排列方法定义).

### Order of a permutation

The **order** of a permutation is the smallest positive integer $a$ such that after applying the permutation $a$ times, all elements return to their original positions. That is,

$$
\operatorname{ord}\sigma = \min\{a \in \mathbf N_+ : \sigma^a = (1)\}.
$$

On a finite set, the order of all permutations is finite. This means that starting from an initial order, as long as we repeatedly shuffle a given sequence according to a fixed pattern, we can always restore the permutation within a finite time.

### Cycle type of a permutation

When decomposing a permutation of $n$ elements into cycles, the **cycle type** of the permutation is the multiset of cycle lengths in the decomposition. These cycle lengths form an integer partition of $n$, the length of the permutation. If the decomposition contains $\alpha_k$ cycles of length $k$, then the cycle type of the permutation is often denoted as

$$
1^{\alpha_1}2^{\alpha_2}\cdots n^{\alpha_n},
$$

and these coefficients satisfy $\sum_{k=1}^n k\alpha_k = n$.

Given the cycle type of a permutation, the number of different permutations is

$$
\frac{n!}{1^{\alpha_1}2^{\alpha_2}\cdots n^{\alpha_n}\alpha_1!\alpha_2!\cdots\alpha_n!}.
$$

??? note "Analysis"
    This is because given any permutation of $1 \sim n$, it can be split into the corresponding cycle decomposition according to the cycle type of the permutation. However, the order of cycles with the same length does not affect the permutation, so the total count needs to be divided by $\prod_k \alpha_k!$. Additionally, within the same cycle, it is actually a circular arrangement; the choice of starting point does not affect the permutation, so it needs to be divided by $\prod_k k^{\alpha_k}$. This gives the formula above.

If only the number of cycles $c(\sigma)$ that the permutation decomposes into is given, then the number of different permutations is the [Stirling number of the first kind](./combinatorics/stirling.md#第一类斯特林数stirling-number) $\begin{bmatrix}n\\ k\end{bmatrix}$. The number of different cycle types is the [partition number](./combinatorics/partition.md) $p_n$ of $n$.

From the cycle type of a permutation, we can easily determine properties such as the order and parity of the permutation.

Since the order of a $k$-cycle is $k$, and different cycles are disjoint, the order of permutation $\sigma$ is

$$
\operatorname{lcm}\{k : \alpha_k > 0\}.
$$

Similarly, since the parity of a $k$-cycle is opposite to the parity of $k$, the parity of permutation $\sigma$ is the parity of

$$
\sum_k (k-1)\alpha_k = \sum_k k\alpha_k - \sum_k \alpha_k = n - c(\sigma)
$$

Here, $c(\sigma)$ is the number of cycles (including $1$-cycles, i.e., fixed points).

The cycle type of a permutation plays an important role in [Pólya counting](./combinatorics/polya.md).

## Arrangements

If set $X$ itself has a natural order, then a permutation $\sigma$ is often called an arrangement or permutation, expressed in one-line notation as

$$
\sigma(1)\sigma(2)\cdots\sigma(n)
$$

Note not to confuse this with cycle notation.

### Inversion count

In an arrangement, if a larger number appears before a smaller number, these two numbers form an **inversion** or anti-sequence. The comparison here is done under the natural order.

The total number of inversions in an arrangement is called the **inversion count** of the permutation. The inversion count of an arrangement is the minimum number of adjacent transpositions needed to restore it to the normal order. Therefore, the parity of the inversion count of an arrangement is consistent with the parity of the corresponding permutation. This can serve as an equivalent definition of the parity of a permutation.

Algorithms for solving the inversion count can use [merge sort](../basic/merge-sort.md#逆序对) or [Fenwick tree](../ds/fenwick.md#全局逆序对全局二维偏序), both with time complexity $O(n\log n)$. The explanations of both algorithms are in the corresponding sections. Here we provide their reference implementations.

??? example "Reference implementation"
    === "Merge sort"
        ```cpp
        --8<-- "docs/math/code/permutation/inversion_2.cpp"
        ```
    
    === "Fenwick tree"
        ```cpp
        --8<-- "docs/math/code/permutation/inversion_1.cpp"
        ```

### Ordering

Arrangements can be compared in size. Since each one-line notation is a string, the order of arrangements is the [lexicographic order](../string/basic.md#字典序) on this string.

In C++'s STL library `<algorithm>`, you can use `prev_permutation` and `next_permutation` to find the previous and next arrangements in lexicographic order respectively.

### Ranking

List all $n$-element arrangements in lexicographic order from smallest to largest. The position of a certain arrangement in this sequence is its rank. It establishes a one-to-one correspondence between arrangements and positive integers, often used for state compression in permutation-related problems.

In the Chinese competitive programming community, this rank is often called the "Cantor expansion" of the arrangement, but this name is not standard. A more rigorous statement is that the **Cantor expansion** of a permutation's rank corresponds to its **Lehmer code**.

??? info "About "Cantor expansion""
    As the name suggests, Cantor expansion is a method for expanding natural numbers into number sequences. It can be seen as a special base, also called [factorial number system](./numeral-sys/base.md#混合基数进制). In this base, the radix for different digits is not the same. For example, the decimal number $463_{10}$ can be expressed in factorial number system as
    
    $$
    463_{10} = 341010_{!}.
    $$
    
    It represents the following meaning
    
    $$
    463 = 3 \times 5! + 4 \times 4! + 1 \times 3! + 0 \times 2! + 1 \times 1! + 0 \times 0!.
    $$
    
    Cantor studied this type of mixed-radix representation, so the digit representation of natural numbers in this base is also often called the Cantor expansion of natural numbers.

??? example "Example"
    Readers unfamiliar with the ranking calculation method can understand the basic idea of the following algorithm through this simple example.
    
    To calculate the rank of arrangement $\sigma = 452631$, we need to count how many arrangements have lexicographic order smaller than $\sigma$, plus one. The idea is similar to [digit DP](../dp/number.md), discussing digit by digit.
    
    - The first digit being smaller than $\sigma$ can only be from $\{1, 2, 3\}$, and the remaining 5 positions can be any, giving $3 \times 5!$ possible arrangements.
    - If the first digit is also $4$, then the second digit being smaller than $\sigma$ can only be from $\{1, 2, 3\}$ (since $4$ has been selected), and the remaining 4 positions can be any, giving $3 \times 4!$ possible arrangements.
    - Similarly, when the first 2 digits are the same as $\sigma$, the third digit being smaller than $\sigma$ can only be from $\{1\}$, and the remaining 3 positions can be any, giving $1 \times 3!$ possible arrangements.
    - When the first 3 digits are the same as $\sigma$, the fourth digit being smaller than $\sigma$ can only be from $\{1, 3\}$, and the remaining 2 positions can be any, giving $2 \times 2!$ possible arrangements.
    - When the first 4 digits are the same as $\sigma$, the fifth digit being smaller than $\sigma$ can only be from $\{1\}$, and the remaining 1 position can be any, giving $1 \times 1!$ possible arrangements.
    - When the first 5 digits are the same as $\sigma$, the sixth digit cannot yield an arrangement smaller than $\sigma$, so $0 \times 0!$ possible arrangements.
    
    Therefore, the rank of arrangement $\sigma$ is
    
    $$
    1 + 3 \times 5! + 3 \times 4! + 1 \times 3! + 2 \times 2! + 1 \times 1! + 0 \times 0! = 444.
    $$
    
    For different arrangements, the key point is determining the coefficients before the factorials. These coefficients are actually the number of elements that come after that position but are smaller than that element.

From the example, the algorithm for solving the rank of a given arrangement can be divided into two steps:

1. Convert the given arrangement of length $n$ into its Lehmer code, which is a sequence $L_\sigma$ of length $n$, where the $i$-th position is
    
    $$
    L_\sigma(i) = \#\{j > i : \sigma(j) < \sigma(i)\},
    $$
    
    i.e., the number of elements that come after the $i$-th position but are smaller than $\sigma(i)$ in the arrangement. It equals the rank (minus one) of the given element among the unused elements.

2. Treat the Lehmer code as the Cantor expansion of a natural number, find the original natural number, and add one. That is, the final rank equals
    
    $$
    \operatorname{rank}\sigma = 1 + L_\sigma(1)(n-1)! + L_\sigma(2)(n-2)! + \cdots + L_\sigma(n)0!.
    $$

To solve the inverse problem, i.e., given a rank to find the corresponding arrangement, simply reverse the above process. In this process, the sum of the digits in the Lehmer code obtained is the inversion count of the arrangement.

In programming, the key is to be able to quickly calculate "the rank of a given element among unused elements" (when computing rank) and "the element with a given rank among unused elements" (when computing arrangement). These can all be maintained using data structures such as [Fenwick tree](../ds/fenwick.md) or [segment tree](../ds/seg.md). The time complexity of both forward and reverse operations is $O(n\log n)$.

??? example "Reference implementation"
    === "Computing the rank of a given arrangement"
        ```cpp
        --8<-- "docs/math/code/permutation/perm_rank.cpp"
        ```
    
    === "Computing the arrangement for a given rank"
        ```cpp
        --8<-- "docs/math/code/permutation/rank_perm.cpp"
        ```

## References and Notes

- [Permutation - Wikipedia](https://en.wikipedia.org/wiki/Permutation)
- [Lehmer code - Wikipedia](https://en.wikipedia.org/wiki/Lehmer_code)
- [Factorial number system - Wikipedia](https://en.wikipedia.org/wiki/Factorial_number_system)
