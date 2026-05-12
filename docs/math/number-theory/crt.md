## Introduction

> The "Counting Objects" problem: There are objects of unknown number, when counted by 3, the remainder is 2; when counted by 5, the remainder is 3; when counted by 7, the remainder is 2. What is the number of objects?

That is, find an integer satisfying: leave remainder 2 when divided by 3, leave remainder 3 when divided by 5, leave remainder 2 when divided by 7.

This problem first appeared in Sunzi's Arithmetic, and there was a specific solution method. In the Song Dynasty, mathematician Qin Jiushao gave a complete and systematic solution to the "Counting Objects" problem in 1247 in the first and second volumes of "Mathematical Treatise in Nine Chapters" ("Shushu Jiuzhang"). The solution rhyme for the specific problem was given by mathematician Cheng Dawei in the Ming Dynasty in "General Meaning of Algorithms" ("Suanfa Tongzong"):

> Three people together get seventy, five plum blossoms make twenty-one, seven sons reunite for half a month, subtract one hundred and five to get it.

$2\times 70+3\times 21+2\times 15=233=2\times 105+23$, so the answer is $23$.

## Definition

The Chinese Remainder Theorem (CRT) can solve systems of linear congruences in the following form (where $n_1, n_2, \cdots, n_k$ are pairwise coprime):

$$
\begin{cases}
x &\equiv a_1 \pmod {n_1} \\
x &\equiv a_2 \pmod {n_2} \\
  &\vdots \\
x &\equiv a_k \pmod {n_k} \\
\end{cases}
$$

The above "Counting Objects" problem is an example of a system of linear congruences.

## Process

1.  Calculate the product $n$ of all moduli;
2.  For the $i$-th equation:
    1.  Calculate $m_i=\frac{n}{n_i}$;
    2.  Calculate the [inverse](./inverse.md) $m_i^{-1}$ of $m_i$ modulo $n_i$;
    3.  Calculate $c_i=m_im_i^{-1}$ (**do not take modulo with $n_i$**).
3.  The unique solution modulo $n$ is: $x=\sum_{i=1}^k a_ic_i \pmod n$.

## Implementation

=== "C++"
    ```cpp
    LL CRT(int k, LL* a, LL* r) {
      LL n = 1, ans = 0;
      for (int i = 1; i <= k; i++) n = n * r[i];
      for (int i = 1; i <= k; i++) {
        LL m = n / r[i], b, y;
        exgcd(m, r[i], b, y);  // b * m mod r[i] = 1
        ans = (ans + a[i] * m * b % n) % n;
      }
      return (ans % n + n) % n;
    }
    ```

=== "Python"
    ```python
    def CRT(k, a, r):
        n = 1
        ans = 0
        for i in range(1, k + 1):
            n = n * r[i]
        for i in range(1, k + 1):
            m = n // r[i]
            b = y = 0
            exgcd(m, r[i], b, y)  # b * m mod r[i] = 1
            ans = (ans + a[i] * m * b % n) % n
        return (ans % n + n) % n
    ```

## Proof

We need to prove that the $x$ calculated by the above algorithm satisfies $x\equiv a_i \pmod {n_i}$ for any $i=1,2,\cdots,k$.

When $i\neq j$, we have $m_j \equiv 0 \pmod {n_i}$, so $c_j \equiv m_j \equiv 0 \pmod {n_i}$. Also, $c_i \equiv m_i \cdot (m_i^{-1} \bmod {n_i}) \equiv 1 \pmod {n_i}$. So we have:

$$
\begin{aligned}
x&\equiv \sum_{j=1}^k a_jc_j                      &\pmod {n_i} \\
  &\equiv a_ic_i                                   &\pmod {n_i} \\
  &\equiv a_i \cdot m_i \cdot (m^{-1}_i \bmod n_i) &\pmod {n_i} \\
  &\equiv a_i                                      &\pmod {n_i}
\end{aligned}
$$

That is, for any $i=1,2,\cdots,k$, the $x$ obtained from the above algorithm always satisfies $x\equiv a_i \pmod{n_i}$, which proves the correctness of the algorithm for solving the system of congruences.

Since we did not impose special restrictions on the inputs $a_i$, any set of inputs $\{a_i\}$ corresponds to a solution $x$. Furthermore, if $x\neq y$, then there always exists an $i$ such that $x$ and $y$ are not congruent modulo $n_i$. Therefore, there is a one-to-one correspondence between the coefficient list $\{a_i\}$ and the solution $x$, and the system always has a unique solution.

## Explanation

Below is a demonstration of how CRT solves the "Counting Objects" problem.

1.  $n=3\times 5\times 7=105$;
2.  Three people together get **seventy**: $n_1=3, m_1=n/n_1=35, m_1^{-1}\equiv 2\pmod 3$, so $c_1=35\times 2=70$;
3.  Five plum blossoms make **twenty-one**: $n_2=5, m_2=n/n_2=21, m_2^{-1}\equiv 1\pmod 5$, so $c_2=21\times 1=21$;
4.  Seven sons reunite for **half a month**: $n_3=7, m_3=n/n_3=15, m_3^{-1}\equiv 1\pmod 7$, so $c_3=15\times 1=15$;
5.  So the unique solution of the system is $x\equiv 2\times 70+3\times 21+2\times 15\equiv 233\equiv 23 \pmod {105}$. (Subtract **one hundred and five** to get it)

## Garner Algorithm

Another use of CRT is to represent a large integer using a set of relatively small prime numbers.

For example, if $a$ satisfies the following system of linear equations, and $a < \prod_{i=1}^k p_i$ (where $p_i$ are prime numbers):

$$
\begin{cases}
a &\equiv a_1 \pmod {p_1} \\
a &\equiv a_2 \pmod {p_2} \\
  &\vdots \\
a &\equiv a_k \pmod {p_k} \\
\end{cases}
$$

We can represent $a$ in the following form (called the mixed radix representation of $a$):

$$
a = x_1 + x_2 p_1 + x_3 p_1 p_2 + \ldots + x_k p_1 \ldots p_{k-1}
$$

The **Garner algorithm** will be used to compute the coefficients $x_1, \ldots, x_k$.

Let $r_{ij}$ be the [inverse](./inverse.md) of $p_i$ modulo $p_j$:

$$
p_i \cdot r_{i,j} \equiv 1 \pmod{p_j}
$$

Substituting $a$ into the first equation we obtained:

$$
a_1 \equiv x_1 \pmod{p_1}
$$

Substituting into the second equation gives:

$$
a_2 \equiv x_1 + x_2 p_1 \pmod{p_2}
$$

Subtracting $x_1$ from both sides and dividing by $p_1$:

$$
\begin{aligned}
    a_2 - x_1           &\equiv x_2 p_1             &\pmod{p_2} \\
    (a_2 - x_1) r_{1,2} &\equiv x_2                 &\pmod{p_2} \\
    x_2                 &\equiv (a_2 - x_1) r_{1,2} &\pmod{p_2}
\end{aligned}
$$

Similarly, we can get:

$$
x_k=(\dots((a_k-x_1)r_{1,k}-x_2)r_{2,k})-\dots)r_{k-1,k} \bmod p_k
$$

??? note "Implementation"
    === "C++"
        ```cpp
        for (int i = 0; i < k; ++i) {
          x[i] = a[i];
          for (int j = 0; j < i; ++j) {
            x[i] = r[j][i] * (x[i] - x[j]);
            x[i] = x[i] % p[i];
            if (x[i] < 0) x[i] += p[i];
          }
        }
        ```
    
    === "Python"
        ```python
        for i in range(0, k):
            x[i] = a[i]
            for j in range(0, i):
                x[i] = r[j][i] * (x[i] - x[j])
                x[i] = x[i] % p[i]
                if x[i] < 0:
                    x[i] = x[i] + p[i]
        ```

The time complexity of this algorithm is $O(k^2)$. In fact, Garner algorithm does not require the moduli to be prime; it only requires them to be pairwise coprime. We have the following pseudocode:

$$
\begin{array}{ll}
&\textbf{Chinese Remainder Algorithm }\operatorname{cra}(\mathbf{v}, \mathbf{m})\text{:} \\
&\textbf{Input}\text{: }\mathbf{m}=(m_0,m_1,\dots ,m_{n-1})\text{, }m_i\in\mathbb{Z}^+\land\gcd(m_i,m_j)=1\text{ for all } i\neq j\text{,} \\
&\qquad \mathbf{v}=(v_0,\dots ,v_{n-1}) \text{ where }v_i=x\bmod m_i\text{.} \\
&\textbf{Output}\text{: }x\bmod{\prod_{i=0}^{n-1} m_i}\text{.} \\
1&\qquad \textbf{for }i\text{ from }1\text{ to }(n-1)\textbf{ do} \\
2&\qquad \qquad C_i\gets \left(\prod_{j=0}^{i-1}m_j\right)^{-1}\bmod{m_i} \\
3&\qquad x\gets v_0 \\
4&\qquad \textbf{for }i\text{ from }1\text{ to }(n-1)\textbf{ do} \\
5&\qquad \qquad u\gets (v_i-x)\cdot C_i\bmod{m_i} \\
6&\qquad x\gets x+u\prod_{j=0}^{i-1}m_j \\
7&\qquad \textbf{return }(x)
\end{array}
$$

It can be found that the computation process in line six corresponds to the representation of the mixed radix mentioned above.

## Applications

Some counting problems or number theory problems, for the purposes of making the code longer, increasing the difficulty, or for other reasons, give moduli that are **not prime**!

However, upon factorizing it, we find that it has no square factors, that is, the modulus is composed of several distinct prime numbers multiplied together.

Then we can compute for each of these moduli separately and finally merge the answers using CRT.

The following problem is a good example.

???+ note "[Luogu P2480 [SDOI2010] Ancient Pig Documents](https://www.luogu.com.cn/problem/P2480)"
    Given $G,n$ ($1 \leq G,n \leq 10^9$), find:
    
    $$
    G^{\sum_{k\mid n}\binom{n}{k}} \bmod 999~911~659
    $$

First, when $G=999~911~659$, the answer is obviously $0$.

Otherwise, according to [Euler's Theorem](./fermat.md), the answer is:

$$
G^{\sum_{k\mid n}\binom{n}{k} \bmod 999~911~658} \bmod 999~911~659
$$

Now consider how to compute:

$$
\sum_{k\mid n}\binom{n}{k} \bmod 999~911~658
$$

Since $999~911~658$ is not prime, it cannot be guaranteed that for all $x \in [1,999~911~657]$, $x$ has an inverse. This expression cannot be computed directly.

Note that $999~911~658=2 \times 3 \times 4679 \times 35617$, where each prime factor appears at most once. We can consider computing $\sum_{k\mid n}\binom{n}{k}$ modulo $2$, $3$, $4679$, and $35617$ respectively, and finally merge the answers using the Chinese Remainder Theorem.

That is, we actually need to find the solution to the following system of linear equations:

$$
\begin{cases}
x \equiv a_1 \pmod 2\\
x \equiv a_2 \pmod 3\\
x \equiv a_3 \pmod {4679}\\
x \equiv a_4 \pmod {35617}
\end{cases}
$$

And computing a binomial coefficient modulo a relatively small prime can use [Lucas' Theorem](./lucas.md).

## Extension: Non-coprime Moduli

### Two Equations

Let the two equations be $x\equiv a_1 \pmod {m_1}$, $x\equiv a_2 \pmod {m_2`;

Converting them to Diophantine equations: $x=m_1p+a_1=m_2q+a_2$, where $p, q$ are integers. Then we have $m_1p-m_2q=a_2-a_1$.

By [Bézout's Theorem](./bezouts.md), when $a_2-a_1$ cannot be divided by $\gcd(m_1,m_2)$, there is no solution;

In other cases, we can solve a feasible solution $(p, q)$ using the [Extended Euclidean Algorithm](./gcd.md);

Then the solution to the system of modular equations composed of the two original equations is $x\equiv b\pmod M$, where $b=m_1p+a_1$, $M=\text{lcm}(m_1, m_2)$.

### Multiple Equations

Merge them pairwise using the above method.

## Practice Problems

-   [Template: Chinese Remainder Theorem (CRT)/Chao Cong Pig Raising](https://www.luogu.com.cn/problem/P1495)
-   [Template: Extended Chinese Remainder Theorem](https://www.luogu.com.cn/problem/P4777)
-   [NOI2018] Dragon Slayer](https://uoj.ac/problem/396)
-   [TJOI2009] Guess the Number](https://www.luogu.com.cn/problem/P3868)

    **Part of this page is translated from [Китайская теорема об остатках](http://e-maxx.ru/algo/chinese_theorem) and its English translation [Chinese Remainder Theorem](https://cp-algorithms.com/algebra/chinese-remainder-theorem.html). The Russian version is in the Public Domain + Leave a Link; the English version is in CC-BY-SA 4.0.**