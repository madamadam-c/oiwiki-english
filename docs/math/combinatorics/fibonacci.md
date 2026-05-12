The Fibonacci sequence (The Fibonacci sequence, [OEIS A000045](http://oeis.org/A000045)) is defined as follows:

$$
F_0 = 0, F_1 = 1, F_n = F_{n-1} + F_{n-2}
$$

The first few terms of this sequence are:

$$
0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, \dots
$$

## Lucas Sequence

The Lucas sequence (The Lucas sequence, [OEIS A000032](http://oeis.org/A000032)) is defined as follows:

$$
L_0 = 2, L_1 = 1, L_n = L_{n-1} + L_{n-2}
$$

The first few terms of this sequence are:

$$
2, 1, 3, 4, 7, 11, 18, 29, 47, 76, 123, 199, \dots
$$

When studying Fibonacci sequences, we often need to use Lucas numbers as a tool.

## Fibonacci Sequence Closed Form

The $n$-th Fibonacci number can be calculated using the recurrence formula in $\Theta(n)$ time. However, there are faster methods.

### Analytical Solution

The analytical solution is the formula solution. We have the closed form for the Fibonacci sequence (Binet's Formula):

$$
F_n = \frac{\left(\frac{1 + \sqrt{5}}{2}\right)^n - \left(\frac{1 - \sqrt{5}}{2}\right)^n}{\sqrt{5}}
$$

This formula can be easily proven by induction, and can also be derived using generating functions or by solving an equation.

Of course, you may notice that the second term in the numerator is always less than 1, and it decreases exponentially. So we can write this formula as

$$
F_n = \left[\frac{\left(\frac{1 + \sqrt{5}}{2}\right)^n}{\sqrt{5}}\right]
$$

Here, the brackets denote rounding to the nearest integer.

These formulas require extremely high precision in calculations, so they are rarely used in practice. But don't ignore them! Combined with the concepts of quadratic residues and inverses modulo, this formula can still be useful in OI.

### Lucas Sequence Closed Form

We have the closed form for the Lucas sequence:

$$
L_n = \left(\frac{1 + \sqrt{5}}{2}\right)^n + \left(\frac{1 - \sqrt{5}}{2}\right)^n
$$

Very similar to the Fibonacci sequence. In fact:

$$
\frac{L_n + F_n\sqrt{5}}{2} = \left(\frac{1 + \sqrt{5}}{2}\right)^n
$$

That is, $L_n$ and $F_n$ exactly form the numerator coefficients after expanding and combining like terms of $\left(\frac{1 + \sqrt{5}}{2}\right)^n$ using the binomial theorem. That is, the Pell equation

$$
x^2 - 5y^2 = -4
$$

has all its solutions as

$$
\frac{x_n + y_n\sqrt{5}}{2} = \frac{L_n + F_n\sqrt{5}}{2}
$$

which are exactly the Lucas sequence and Fibonacci sequence. Therefore, there is

$$
{L_n}^2 - 5{F_n}^2 = -4
$$

### Matrix Form

The recurrence of the Fibonacci sequence can be expressed in matrix multiplication form:

$$
\begin{bmatrix}F_{n-1} & F_{n} \cr\end{bmatrix} = \begin{bmatrix}F_{n-2} & F_{n-1} \cr\end{bmatrix} \begin{bmatrix}0 & 1 \cr 1 & 1 \cr\end{bmatrix}
$$

Let $P = \begin{bmatrix}0 & 1 \cr 1 & 1 \cr\end{bmatrix}$, we get

$$
\begin{bmatrix}F_n & F_{n+1} \cr\end{bmatrix} = \begin{bmatrix}F_0 & F_1 \cr\end{bmatrix} P^n
$$

Thus, we can compute the Fibonacci sequence in $\Theta(\log n)$ time using matrix multiplication. Additionally, the formula from the previous section can also be obtained using matrix diagonalization techniques.

### Fast Doubling Method

Using the above method, we can obtain the following equations:

$$
\begin{aligned}
F_{2k} &= F_k (2 F_{k+1} - F_{k}) \\
F_{2k+1} &= F_{k+1}^2 + F_{k}^2
\end{aligned}
$$

Thus, we can quickly compute two consecutive Fibonacci numbers using this method (the constant is smaller than matrix multiplication). The code is as follows, returning a pair $(F_n, F_{n+1})$.

```cpp
pair<int, int> fib(int n) {
  if (n == 0) return {0, 1};
  auto p = fib(n >> 1);
  int c = p.first * (2 * p.second - p.first);
  int d = p.first * p.first + p.second * p.second;
  if (n & 1)
    return {d, c + d};
  else
    return {c, d};
}
```

## Properties

The Fibonacci sequence has many interesting properties. Here are some simple ones:

1.  Cassini's identity: $F_{n-1} F_{n+1} - F_n^2 = (-1)^n$.
2.  Additional property: $F_{n+k} = F_k F_{n+1} + F_{k-1} F_n$.
3.  Setting $k = n$ in the previous property, we get $F_{2n} = F_n (F_{n+1} + F_{n-1})$.
4.  By induction from the previous property, $\forall k\in \mathbb{N}, F_n | F_{nk}$.
5.  The above property is reversible, i.e., $\forall F_a | F_b, a | b$.
6.  GCD property: $(F_m, F_n) = F_{(m, n)}$.
7.  Using consecutive Fibonacci numbers as input makes the Euclidean algorithm reach worst-case complexity (see [Wikipedia - Lamé](https://en.wikipedia.org/wiki/Gabriel_Lam%C3%A9) for details).

### Relationship between Fibonacci and Lucas Sequences

It is not hard to find that the equations involving Lucas numbers and Fibonacci numbers are highly similar to trigonometric formulas. For example:

$$
\frac{L_n + F_n\sqrt{5}}{2} = \left(\frac{1 + \sqrt{5}}{2}\right)^n
$$

and

$$
\cos nx + i\sin nx = \left(\cos x + i\sin x\right)^n
$$

are very similar. And

$$
{L_n}^2 - 5{F_n}^2 = -4
$$

is similar to

$$
\cos^2 x + \sin^2 x = 1
$$

Therefore, the Lucas sequence is similar to the cosine function, while the Fibonacci sequence is similar to the sine function. For example, from

$$
\left(\frac{1 + \sqrt{5}}{2}\right)^m\left(\frac{1 + \sqrt{5}}{2}\right)^n = \left(\frac{1 + \sqrt{5}}{2}\right)^{m+n}
$$

we can get the formula for the sum of two indices:

$$
2L_{m+n} = 5F_mF_n + L_mL_n
$$

$$
2F_{m+n} = F_mL_n + L_mF_n
$$

Thus, there is a formula for doubling the index:

$$
L_{2n} = {L_n}^2 - 2{\left(-1\right)}^n
$$

$$
F_{2n} = F_nL_n
$$

This is also a way to quickly double the index. Similarly, we can also deduce more equations involving Lucas and Fibonacci sequences by imitating trigonometric formula properties such as parity, sum-to-product, product-to-sum, half-angle, and Weierstrass substitution, etc.

## Fibonacci Encoding

We can use Fibonacci numbers to encode positive integers. According to Zeckendorf's theorem, any natural number $n$ can be uniquely represented as a sum of several Fibonacci numbers:

$$
N = F_{k_1} + F_{k_2} + \ldots + F_{k_r}
$$

And $k_1 \ge k_2 + 2,\ k_2 \ge k_3 + 2, \ \ldots,\ k_r \ge 2$ (i.e., two consecutive Fibonacci numbers cannot be used).

Thus, we can represent a positive integer with the encoding $d_0 d_1 d_2 \dots d_s 1$, where $d_i = 1$ indicates that $F_{i+2}$ is used. At the end of the encoding, we force a 1 (which results in two consecutive 1s), indicating the end of this encoding string. Here are some examples:

$$
\begin{aligned}
1 &=& 1 &=& F_2 &=& (11)_F \\
2 &=& 2 &=& F_3 &=& (011)_F \\
6 &=& 5 + 1 &=& F_5 + F_2 &=& (10011)_F \\
8 &=& 8 &=& F_6 &=& (000011)_F \\
9 &=& 8 + 1 &=& F_6 + F_2 &=& (100011)_F \\
19 &=& 13 + 5 + 1 &=& F_7 + F_5 + F_2 &=& (1001011)_F
\end{aligned}
$$

The encoding process for $n$ can be solved using a greedy algorithm:

1.  Enumerate Fibonacci numbers $F_i$ from largest to smallest until $F_i \le n$.
2.  Subtract $F_i$ from $n$, and place a 1 at position $i-2$ in the encoding (encoding is 0-indexed from left to right).
3.  If $n$ is positive, go back to step 1.
4.  Finally, add a 1 at the end of the encoding, indicating the end position of the encoding.

The decoding process is similar: first remove the last 1, and for each position $i$ in the encoding that is 1 (encoding is 0-indexed from left to right), add $F_{i+2}$ to the answer. The final answer is the original number.

## Periodicity modulo m

For the Fibonacci sequence modulo $m$, it can be easily proven using the drawer principle that the sequence is periodic. Since each term of the Fibonacci sequence depends on the previous two terms, we need to describe the state of the sequence using pairs of consecutive Fibonacci numbers. Consider the first $m^2 + 1$ Fibonacci pairs modulo $m$:

$$
(F_0,\ F_1),\ (F_1,\ F_2),\ \ldots,\ (F_{m^2},\ F_{m^2 + 1})
$$

The size of the residue system modulo $m$ is $m$, which means there can be at most $m^2$ different pairs. Therefore, among the first $m^2 + 1$ pairs, there must be two identical pairs, and from these two pairs, the same Fibonacci sequence can be generated. Thus, the Fibonacci sequence is periodic, and the (minimal positive) period does not exceed $m^2$.

### Pisano Period

The minimal positive period of the Fibonacci sequence modulo $m$ is called the **Pisano period** (Pisano period, [OEIS A001175](http://oeis.org/A001175)). In this article, we denote $\pi(m)$ as the Pisano period modulo $m$.

This observation can be used to compute the $n$-th Fibonacci number modulo $m$. If $n$ is very large, we need to compute the period of the Fibonacci number modulo $m$. Of course, we only need to compute the period, not necessarily the minimal positive period.

For this, we have the following conclusions:

1.  For coprime moduli $m_1, m_2$, we have $\pi(m_1m_2) = \operatorname{lcm}(\pi(m_1), \pi(m_2))$.
2.  For a prime $p$ and a positive integer $e$, we have $\pi(p^e) \mid p^{e-1}\pi(p)$.
3.  For $m = 2^e~(e\in\mathbf N_+)$, we have $\pi(m) = 3 \cdot 2^{e-1}$.
4.  For $m = 5^e~(e\in\mathbf N_+)$, we have $\pi(m) = 4 \cdot 5^e$.
5.  Finally, for a prime $p \equiv \pm 1 \pmod{10}$, we have $\pi(p) \mid (p-1)$; for a prime $p \equiv \pm 3 \pmod{10}$, we have $\pi(p) \mid 2(p+1)$.

Synthesizing these cases, we can show that the Pisano period modulo $m$ does not exceed $6m$, and equality holds if and only if $m = 2 \times 5^e~(e\in\mathbf N_+)$.

Using the above conclusions, we can quickly compute the Pisano period based on prime factorization:

??? example "Reference code"
    ```cpp
    --8<-- "docs/math/code/combinatorics/fibonacci/pisano_estimate.cpp:pisano"
    ```

The period obtained this way may only be a multiple of the Pisano period. To get the exact Pisano period, we can further examine the factors of this period; or, we can directly compute it using the [BSGS algorithm](../number-theory/discrete-logarithm.md#baby-step-giant-step-algorithm) in $O(\sqrt{m})$ time.

### Proof

Finally, we briefly prove the above conclusions about the Pisano period. It is worth noting that using the method described below, similar conclusions can be extended to general second-order linear homogeneous recurrence relations with constant coefficients. Although the specific constants differ, the Pisano periods of these sequences modulo $m$ are all $O(m)$.

The first observation: using the [Chinese Remainder Theorem](../number-theory/crt.md), we can limit the discussion to the case of prime powers. Let $m_1, m_2$ be two coprime moduli. The Fibonacci sequence has a period of $\pi(m_1)$ and its multiples modulo $m_1$, and a period of $\pi(m_2)$ and its multiples modulo $m_2$. Therefore, its minimal positive period modulo $m_1m_2$ is exactly the least common multiple of $\pi(m_1)$ and $\pi(m_2)$. This is conclusion 1 from above.

Another observation: the Pisano period modulo $m$ is actually the smallest positive integer $k$ such that

$$
A^k = \begin{pmatrix} 1&1\\1&0 \end{pmatrix}^k \equiv I \pmod{m}.
$$

That is, it is actually the [order](../algebra/group-theory.md#order) of the matrix $A$ modulo $m$.

For the case of prime powers $m = p^e$, we can connect the situation to the corresponding prime modulus using a classic lifting argument. Let $k = \pi(p^e)$, then there exists a $2 \times 2$ matrix $\Lambda$ such that

$$
A^k = p^e\Lambda + I 
$$

holds. Therefore, by the [binomial theorem](./combination.md#binomial-theorem),

$$
A^{kp} = (p^e\Lambda + I)^p = I + \sum_{i=1}^p\binom{p}{i}(p^e\Lambda)^i \equiv I\pmod{p^{e+1}}. 
$$

Thus, from the [properties of orders](../number-theory/primitive-root.md#cycle-structure-of-powers), we have $\pi(p^{e+1}) \mid kp = p\pi(p^e)$. By induction on $e$, we can show that $\pi(p^e) \mid p^{e-1}\pi(p)$ always holds.

For the case of prime modulus $p$, we discuss two proof methods.

=== "Using the closed form formula"
    One method uses the closed form of the Fibonacci sequence:
    
    $$
    F_n = \dfrac{1}{\sqrt{5}}\left(\dfrac{1+\sqrt{5}}{2}\right)^n - \dfrac{1}{\sqrt{5}}\left(\dfrac{1-\sqrt{5}}{2}\right)^n.
    $$
    
    Expand it using the binomial theorem and eliminate the radical terms:
    
    $$
    F_n = \dfrac{1}{2^{n-1}}\sum_{i=0}^{\lfloor(n-1)/2\rfloor}\binom{n}{2i+1}5^i.
    $$
    
    For $p = 2$, this expression cannot be directly taken modulo, but we can verify that the corresponding Pisano period is $\pi(2) = 3$. For $p = 5$, we have $F_n \equiv n \cdot 3^{n-1} \pmod{p}$, and we can directly verify that the corresponding Pisano period is $\pi(5) = 20$. For the remaining odd prime moduli, there are two cases:
    
    -   If $p \equiv 1,4\pmod{5}$, then
        
        $$
        \begin{aligned}
        F_{p} &\equiv \dfrac{1}{2^{p-1}}\binom{p}{p}5^{(p-1)/2} \equiv 1 \pmod{p},\\
        F_{p+1} &\equiv \dfrac{1}{2^p}\left(\binom{p+1}{1} + \binom{p+1}{p}5^{(p-1)/2}\right) \equiv 1 \pmod{p}.
        \end{aligned}
        $$
        
        In the simplification process, we use the following conclusions: from the [Lucas Theorem](../number-theory/lucas.md), for $0 < k < p$, we have $\dbinom{p}{k} \equiv 0\pmod{p}$, and for $1 < k < p$, we have $\dbinom{p+1}{k} \equiv 0\pmod{p}$; from [Fermat's Little Theorem](../number-theory/fermat.md#fermat-little-theorem), we have $2^{p-1} \equiv 5^{p-1} \equiv 1\pmod{p}$; for $p \equiv 1,4\pmod{5}$, $p$ is a quadratic residue modulo 5, and using the [Quadratic Reciprocity Law](../number-theory/quad-residue.md#quadratic-reciprocity-law), 5 is also a quadratic residue modulo $p$, so $5^{(p-1)/2} \equiv 1\pmod{p}$. From this, we have $(F_p, F_{p+1}) \equiv (F_1, F_2) \pmod{p}$, so $(p-1)$ is a period modulo $p$. Thus, $\pi(p) \mid (p-1)$.
    -   If $p \equiv 2,3\pmod{5}$, then
        
        $$
        \begin{aligned}
        F_{2p} &\equiv \dfrac{1}{2^{2p-1}}\binom{2p}{p}5^{(p-1)/2} \equiv -1 \pmod{p},\\
        F_{2p+1} &\equiv \dfrac{1}{2^{2p}}\left(\binom{2p+1}{1} + \binom{2p+1}{p}5^{(p-1)/2} + \binom{2p+1}{2p+1}5^p\right) \equiv -1\pmod{p}.
        \end{aligned}
        $$
        
        In the simplification process, we use the following conclusions: from the Lucas Theorem, for $0 < k < p$ and $p < k < 2p$, we have $\dbinom{p}{k} \equiv 0\pmod{p}$, and $\dbinom{2p}{p} \equiv 2\pmod{p}$, and for $1 < k < p$ and $p + 1 < k < 2p$, we have $\dbinom{p}{k} \equiv 0\pmod{p}$, and $\dbinom{2p+1}{p} \equiv 2\pmod{p}$; from Fermat's Little Theorem, we have $2^{p-1} \equiv 5^{p-1} \equiv 1\pmod{p}$; for $p \equiv 2,3\pmod{5}$, $p$ is a quadratic nonresidue modulo 5, and using the Quadratic Reciprocity Law, 5 is also a quadratic nonresidue modulo $p$, so $5^{(p-1)/2} \equiv -1\pmod{p}$. From this, we have $(F_{2p}, F_{2p+1}) \equiv (F_{-2}, F_{-1}) \pmod{p}$, so $2(p+1)$ is a period modulo $p$. Thus, $\pi(p) \mid 2(p+1)$.
    
    This completes the proof. The limitation of this method is that it heavily depends on the closed form of the Fibonacci sequence, so it is difficult to directly generalize to general cases.

=== "Using extension fields"
    Another proof method tries to directly compute the order of matrix $A = \begin{pmatrix}1&1\\1&0\end{pmatrix}$. Its [characteristic polynomial](../linear-algebra/char-poly.md) is $f(x) = x^2 - x - 1$, with discriminant $\Delta = 5$. For modulus $p = 5$, we have $\Delta \equiv 0 \pmod{5}$, and matrix $A$ has two identical eigenvalues $\lambda = 3$, and cannot be diagonalized, requiring separate calculation. For modulus $p \equiv 1,4\pmod{5}$, by the Quadratic Reciprocity Law, the discriminant $\Delta = 5$ is a quadratic residue modulo $p$, matrix $A$ has two distinct eigenvalues $\lambda_1 \neq \lambda_2$ in the field $\mathbf F_p$, and the order of matrix $A$ is $\operatorname{lcm}(\operatorname{ord}(\lambda_1), \operatorname{ord}(\lambda_2))$, which necessarily divides $|\mathbf F_p^\times| = p - 1$. For modulus $p \equiv 2,3\pmod{5}$, by the Quadratic Reciprocity Law, the discriminant $\Delta = 5$ is a quadratic nonresidue modulo $p$, matrix $A$ has no eigenvalues in the field $\mathbf F_p$, but has two distinct eigenvalues $\lambda_1 \neq \lambda_2$ only in the [extension field](../algebra/field-theory.md#field-extensions) $\mathbf F_p[\sqrt{5}]$. Since the Frobenius automorphism $x \mapsto x^p$ swaps the two roots, we have $\lambda_2 = \lambda_1^p$, so $\lambda_1^{p+1} = \lambda_2^{p+1} = \lambda_1\lambda_2 = -1$, that is, $\lambda_1^{2(p+1)} = \lambda_2^{2(p+1)} = 1$. Therefore, the order of matrix $A$ is $\operatorname{lcm}(\operatorname{ord}(\lambda_1), \operatorname{ord}(\lambda_2))$, which necessarily divides $2(p+1)$. This gives the same conclusion as the previous method.

Summarizing, for different cases, we have:

-   $\pi(2^e) = \dfrac{3}{2} \cdot 2^e,~\dfrac{1}{4}\pi(5^e) = 5^e$.
-   When $p \equiv \pm 1 \pmod{10}$, $\pi(p^e) \mid (p-1)p^{e-1}$, so $\pi(p^e) \le p^e$.
-   When $p \equiv \pm 3 \pmod{10}$, $\dfrac{1}{4}\pi(p^e) \mid \dfrac{p+1}{2}p^{e-1}$, so $\dfrac{1}{4}\pi(p^e) \le p^e$.

So, using conclusion 1, for a general modulus $m = \prod_i p_i^{e_i}$, we have

$$
\begin{aligned}
\pi(m) &= \operatorname{lcm}\{\pi(p_i^{e_i}): p_i \in \mathbf P\} \\
&\le \operatorname{lcm}\{\pi(p_i^{e_i}): p_i = 2 \text{ or } p_i \equiv \pm 1 \pmod{10}\}\\
&\quad \cdot 4 \cdot \operatorname{lcm}\{\pi(p_i^{e_i})/4: p_i = 5 \text{ or } p_i \equiv \pm 3 \pmod{10}\}\\
&\le \prod\{\pi(p_i^{e_i}): p_i = 2 \text{ or } p_i \equiv \pm 1 \pmod{10}\}\\
&\quad \cdot 4 \cdot \prod\{\pi(p_i^{e_i})/4: p_i = 5 \text{ or } p_i \equiv \pm 3 \pmod{10}\}\\
&\le \dfrac{3}{2} \cdot \prod\{p_i^{e_i}: p_i = 2 \text{ or } p_i \equiv \pm 1 \pmod{10}\}\\
&\quad \cdot 4 \cdot \prod\{p_i^{e_i}: p_i = 5 \text{ or } p_i \equiv \pm 3 \pmod{10}\}\\
&= 6m.
\end{aligned}
$$

This shows that the Pisano period of the Fibonacci sequence modulo $m$ never exceeds $6m$, and equality holds if and only if $m = 2 \cdot 5^e$.

## Exercises

-   [SPOJ - Euclid Algorithm Revisited](http://www.spoj.com/problems/MAIN74/)
-   [SPOJ - Fibonacci Sum](http://www.spoj.com/problems/FIBOSUM/)
-   [HackerRank - Is Fibo](https://www.hackerrank.com/challenges/is-fibo/problem)
-   [Project Euler - Even Fibonacci numbers](https://www.hackerrank.com/contests/projecteuler/challenges/euler002/problem)
-   [Luogu P4000 斐波那契数列](https://www.luogu.com.cn/problem/P4000)

## References and Notes

-   [Fibonacci sequence - Wikipedia](https://en.wikipedia.org/wiki/Fibonacci_sequence)
-   [Zeckendorf's theorem - Wikipedia](https://en.wikipedia.org/wiki/Zeckendorf%27s_theorem)
-   [Pisano period - Wikipedia](https://en.wikipedia.org/wiki/Pisano_period)

**This page is mainly translated from the blog post [Числа Фибоначчи](http://e-maxx.ru/algo/fibonacci_numbers) and its English version [Fibonacci Numbers](https://cp-algorithms.com/algebra/fibonacci-numbers.html). The Russian version is in the Public Domain + Leave a Link; the English version is under CC-BY-SA 4.0. Content has been modified.**

[^mod-m]: Strictly speaking, it is the order of matrix $A$ in the general linear group $GL_2(\mathbf Z_m)$.