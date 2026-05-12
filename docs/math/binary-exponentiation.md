author: iamtwz, billchenchina, CBW2007, CCXXXI, chinggg, Enter-tainer, eyedeng, FFjet, gaojude, Great-designer, H-J-Granger, Henry-ZHR, hsfzLZH1, Ir1d, kenlig, Konano, ksyx, luoguyuntianming, Marcythm, Menci, NachtgeistW, ouuan, Peanut-Tang, qwqAutomaton, sshwy, StudyingFather, Tiphereth-A, TrisolarisHD, TRSWNCA, Xeonacid, Yuuko10032, Zhangjiacheng2006, Zhoier, Hszzzx, shenshuaijie, kfy666

## Introduction

**Fast exponentiation** (also known as **binary exponentiation** or **exponentiation by squaring**) is a technique for computing $a^n$ in $\Theta(\log n)$ time, whereas the brute-force approach requires $\Theta(n)$ time.

This technique can be applied to any multiplication of $a$ that satisfies the associative property, such as modular exponentiation, matrix exponentiation, etc. See the [Applications](#applications) section for details.

## Process

Computing $a$ to the $n$-th power means multiplying $a$ by itself $n$ times: $a^{n} = \underbrace{a \times a \cdots \times a}_{n\text{ copies of }a}$. However, when $n$ is too large or the cost of a single multiplication is too high, this method becomes impractical. The idea behind binary exponentiation is to split the exponentiation task into smaller subtasks based on the **binary representation** of the exponent.

???+ example "Example"
    Suppose we want to compute $3^{13}$. Expanding it as a product of factors would require $13-1=12$ multiplications. However, because
    
    $$
    3^{13} = 3^{(1101)_2} = 3^8 \times 3^4 \times 3^1,
    $$
    
    as long as we can quickly compute $3^{1}, 3^{2}, 3^{4}, 3^{8}$, we can compute $3^{13}$ with just $2$ multiplications. So we only need a fast way to compute the sequence of powers $3^{2^k}$. This is easy, because each element in the sequence (except the first) is the square of the previous element.
    
    Based on this analysis, the computation process for $3^{13}$ is as follows:
    
    $$
    \begin{aligned}
    3^1 &= 3, \\
    3^2 &= \left(3^1\right)^2 = 3^2 = 9, \\
    3^4 &= \left(3^2\right)^2 = 9^2 = 81, \\
    3^8 &= \left(3^4\right)^2 = 81^2 = 6561, \\
    3^{13} &= 6561 \times 81 \times 3 = 1594323.
    \end{aligned}
    $$
    
    Only $5$ multiplications were performed in this process.

This is the basic idea of fast exponentiation. For concrete implementations, there are two common versions.

### Iterative Version

Let the binary representation of $n$ be $(n_tn_{t-1}\cdots n_1n_0)_2$, that is,

$$
n = n_t2^t + n_{t-1}2^{t-1} + \cdots + n_12^1 + n_02^0,
$$

where $n_i\in\{0,1\}$. Then,

$$
\begin{aligned}
a^n & = a^{n_t2^t + n_{t-1}2^{t-1} + \cdots + n_12^1 + n_02^0}\\
& = a^{n_0 2^0} \times a^{n_1 2^1}\times \cdots \times a^{n_{t-1}2^{t-1}} \times a^{n_t2^t}.
\end{aligned}
$$

Note that only terms where $n_i=1$ actually appear in the product calculation.

Based on this expression, we can first compute the $\Theta(\log n)$ values of $a^{2^k}$ in $\Theta(\log n)$ time, then spend $\Theta(\log n)$ time multiplying the powers corresponding to bits equal to $1$ into the final result. This is the iterative implementation of fast exponentiation.

Pseudocode:

$$
\begin{array}{l}
\textbf{Algorithm }\text{FastPow}(a, n): \\
\textbf{Input. }\text{Base }a\text{ and exponent }n.\\
\textbf{Output. }\text{Power }a^n.\\
\textbf{Method.}\\
\begin{array}{ll}
1 & \textit{result}\gets\mathrm{Id}\\
2 & \textbf{while }n > 0\textbf{ do}\\
3 & \qquad \textbf{if }n \bmod 2 = 1\textbf{ then}\\
4 & \qquad \qquad \textit{result} \gets \textit{result}\cdot a\\
5 & \qquad \textbf{end if}\\
6 & \qquad a \gets a \cdot a\\
7 & \qquad n \gets n / 2\\
8 & \textbf{end while}\\
9 & \textbf{return }\textit{result}
\end{array}
\end{array}
$$

Using this method, $\Theta(\log n)$ multiplications are required to compute fast exponentiation.

### Recursive Version

This process can also be implemented recursively. Notice that the binary expansion of exponent $n$ can be recursively written as

$$
(n_tn_{t-1}\cdots n_1n_0)_2 = 2 \times (n_tn_{t-1}\cdots n_1)_2 + n_0.
$$

Therefore, $a^n$ can be computed recursively as

$$
a^n = \begin{cases}
1, & n = 0,\\
(a^{\lfloor n/2\rfloor})^2, & n > 0 \text{ and }n\text{ is even},\\
(a^{\lfloor n/2\rfloor})^2\cdot a, & n > 0 \text{ and }n\text{ is odd}.\\
\end{cases}
$$

This is the recursive implementation of fast exponentiation.

Pseudocode:

$$
\begin{array}{l}
\textbf{Algorithm }\text{FastPow}(a, n): \\
\textbf{Input. }\text{Base }a\text{ and exponent }n.\\
\textbf{Output. }\text{Power }a^n.\\
\textbf{Method.}\\
\begin{array}{ll}
1 & \textbf{if }n = 0\textbf{ then}\\
2 & \qquad \textbf{return }\mathrm{Id}\\
3 & \textbf{end if}\\
4 & \textit{result} \gets \text{FastPow}(a, n / 2) \\
5 & \textbf{if }n\bmod 2 = 0\textbf{ then}\\
6 & \qquad \textbf{return }\textit{result}\cdot\textit{result}\\
7 & \textbf{else}\\
8 & \qquad \textbf{return }\textit{result}\cdot\textit{result}\cdot a\\
9 & \textbf{end if}
\end{array}
\end{array}
$$

Using this method, fast exponentiation requires $\Theta(\log n)$ recursive calls, and also $\Theta(\log n)$ multiplications. Although the complexity is the same, in practice the iterative version is faster due to the overhead of recursion.

## Applications

### Modular Exponentiation

???+ example "[Luogu P1226 [Template] Fast Power](https://www.luogu.com.cn/problem/P1226)"
    Given three integers $a, b, p$, compute $a^b\bmod p$, where $p\ge 2$.

This is a very common application; for example, it can be used to compute modular multiplicative inverses. Since modular arithmetic does not interfere with multiplication, we simply take the modulus during the computation.

First, we can implement it directly using the recursive method:

???+ note "Reference Implementation"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/binary-exponentiation/luogu-P1226-1.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/binary-exponentiation/luogu-P1226-1.py:core"
        ```

The second implementation is non-recursive. It accumulates the products of powers corresponding to bits equal to $1$ during the loop. Although the theoretical complexity is the same, the second approach is faster in practice because recursion incurs overhead.

???+ note "Reference Implementation"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/binary-exponentiation/luogu-P1226-2.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/binary-exponentiation/luogu-P1226-2.py:core"
        ```

???+ warning "Note"
    -   The modulus is usually greater than $1$. In very special cases, the modulus $p$ may equal $1$, which requires special handling of the $b=0$ case.
    -   When the exponent is very large, use [Euler's extended theorem](./number-theory/fermat.md#extended-euler-theorem) to reduce the exponent before computing.

### Computing Fibonacci Numbers

Based on the Fibonacci recurrence $F_n = F_{n-1} + F_{n-2}$, we can construct a $2\times 2$ matrix representing the transformation from $F_i, F_{i+1}$ to $F_{i+1}, F_{i+2}$. When computing the $n$-th power of this matrix, we can use the fast exponentiation idea to compute the result in $\Theta(\log n)$ time. For more details, see [Fibonacci sequence](./combinatorics/fibonacci.md). For matrix exponentiation implementation, see [Matrix-accelerated recurrence](../math/linear-algebra/matrix.md#matrix-accelerated-recurrence).

### Multiple Permutations

???+ note "Problem Description"
    Given a sequence of length $n$ and a permutation, apply this permutation $k$ times to the sequence.

Simply raise this permutation to the $k$-th power, then apply it to the sequence. The time complexity is $O(n \log k)$. For more details, see [Permutation composition](./permutation.md#composition).

???+ warning "Note"
    By constructing a graph of this permutation and handling each cycle separately (which is equivalent to taking $k$ modulo the cycle length), this problem can be solved in $O(n)$ time complexity.

### Accelerating Point Set Operations in Geometry

???+ example "[HDU 4087 A Letter to Programmers](https://acm.hdu.edu.cn/showproblem.php?pid=4087)"
    Given $n$ points $p_i$ in three-dimensional space, apply $m$ operations to these points. There are 3 types of operations:
    
    1.  Shift the point position along a certain vector.
    2.  Scale the point coordinates by a factor (Scale).
    3.  Rotate around a line (Rotate).
    
    There is also a special operation: repeat a certain sequence of operations $k$ times (Repeat). Repeat operations can be nested. Output the coordinates of each point after all operations.

Refer to [Vectors and matrices](./linear-algebra/vector.md#vectors-and-matrices). Each type of operation can be represented by a transformation matrix. A sequence of consecutive transformations can be represented by a matrix product. A Repeat operation corresponds to taking a matrix to the $k$-th power. This allows us to compute the final matrix of the entire transformation sequence in $O(m \log k)$ time. Finally, applying it to the $n$ points gives a total complexity of $O(n + m \log k)$.

### Fixed-Length Path Counting

???+ note "Problem Description"
    Given a directed graph (edge weight 1), find the number of paths of length $k$ from any vertex $u$ to vertex $v$.

If we raise the adjacency matrix $M$ of the graph to the $k$-th power, then $M_{i,j}$ represents the number of paths of length $k$ from $i$ to $j$. The algorithm's complexity is $O(n^3 \log k)$. For details, see the [Matrix](./linear-algebra/matrix.md#fixed-length-path-counting) page.

### Modular Integer Multiplication

???+ note "Problem Description"
    Given non-negative integers $a, b$ and a positive integer $m$, compute $a\times b\bmod m$, where $a, b\le m\le 10^{18}$.

Similar to the idea of binary exponentiation, we express one of the factors as a sum of integer powers of $2$. When performing multiplication by $2$ followed by modulo, we can convert it to addition and subtraction to prevent integer overflow. This solves the problem in $O(\log m)$ time. The recursive method is:

$$
a \cdot b = \begin{cases}
0 &\text{if }a = 0 \\
2 \cdot \frac{a}{2} \cdot b &\text{if }a > 0 \text{ and }a \text{ even} \\
2 \cdot \frac{a-1}{2} \cdot b + b &\text{if }a > 0 \text{ and }a \text{ odd}
\end{cases}
$$

However, in practice, this method is not efficient due to increased computational overhead. In actual programming, [fast multiplication](./number-theory/mod-arithmetic.md#fast-multiplication) is typically used for multiplication with moduli in the `long long` range.

### High-Precision Fast Exponentiation

Prerequisite: [Big integer multiplication](./bignum.md#multiplication)

???+ example "[Luogu P1045 [NOIP 2003 Junior Group] Mason Number](https://www.luogu.com.cn/problem/P1045)"
    Given an integer $P$ ($1000 < P < 3100000$), compute the number of digits of $2^P - 1$ and the last $500$ digits (in decimal), padding with leading zeros if less than $500$ digits.

??? note "Code Implementation"
    ```cpp
    --8<-- "docs/math/code/binary-exponentiation/luogu-P1045.cpp"
    ```

## Precomputed Fast Exponentiation with Fixed Base

When the base $a$ is fixed, we can use the [block decomposition idea](../ds/decompose.md) to preprocess in a certain amount of time and answer each power query in $O(1)$ time. This algorithm is commonly called **light-speed exponentiation**. The process is as follows:

1.  Choose a number $s$, preprocess the values of $a^0, a^1, \cdots, a^{s-1}$ and $a^0, a^s, \cdots, a^{\lfloor p/s\rfloor s}$ and store them in two arrays;
2.  For each query $a^b$, split $b$ into $\lfloor b/s\rfloor s + (b\bmod s)$, then $a^b = a^{\lfloor b/s\rfloor s} \cdot a^{b\bmod s}$, which allows $O(1)$ computation of the answer.

Assuming the exponent $b$ ranges in $[0, n]$, the block size $s$ is often chosen as $\sqrt{n}$ or a power of $2$ close to it. Choosing $\sqrt{n}$ gives the optimal preprocessing complexity $O(\sqrt{n})$, while choosing a power of $2$ allows the use of bit operations to simplify computation.

In particular, for modular exponentiation, the base $a$ being the same implicitly requires the modulus $m$ to be the same. Due to [Euler's extended theorem](./number-theory/fermat.md#extended-euler-theorem), for any modulus $m$, the upper bound for the preprocessed exponent range is $n = 2\varphi(m)$. For a prime modulus $p$, the preprocessing range upper bound is $n = p - 1$. The preprocessing complexity for both cases is $O(\sqrt{m})$.

???+ example "Reference Code"
    ```cpp
    --8<-- "docs/math/code/binary-exponentiation/pre-exp.cpp:core"
    ```

## Practice Problems

-   [UVa 1230 - MODEX](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3671)
-   [UVa 374 - Big Mod](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=310)
-   [UVa 11029 - Leading and Trailing](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1970)
-   [Codeforces - Parking Lot](http://codeforces.com/problemset/problem/630/I)
-   [SPOJ - The last digit](http://www.spoj.com/problems/LASTDIG/)
-   [SPOJ - Locker](http://www.spoj.com/problems/LOCKER/)
-   [SPOJ - Just add it](http://www.spoj.com/problems/ZSUM/)

**Parts of this page are translated from the blog post [Бинарное возведение в степень](http://e-maxx.ru/algo/binary_pow) and its English translation [Binary Exponentiation](https://cp-algorithms.com/algebra/binary-exp.html). The Russian version is in the public domain with a leave-a-link credit; the English version is licensed under CC-BY-SA 4.0.**