## Entringer Numbers

Entringer numbers (Entringer number, [OEIS A008281](http://oeis.org/A008281)) $E(n, k)$ is the number of permutations of $0$ to $n$ (a total of $n+1$ numbers) satisfying the following conditions:

-   The first element is $k$;
-   The next element after the first is smaller than the first, the next element is larger than the previous one, the next is smaller than the previous one, and so on. The alternating inequality relationship holds for all adjacent elements.

The initial values of Entringer numbers are:

$$
E(0, 0) = 1
$$

$$
E(n, 0) = 0
$$

There is a recurrence relation:

$$
E(n, k) = E(n, k-1) + E(n-1, n-k)
$$

## Seidel–Entringer–Arnold Triangle

An appropriate arrangement of Entringer numbers forms a numeric triangle, called the Seidel–Entringer–Arnold triangle (Seidel–Entringer–Arnold triangle, [OEIS A008280](http://oeis.org/A008280)). This triangle arranges Entringer numbers $E(n, k)$ in "ox-plowing order":

$$
\begin{aligned}
& E(0, 0) \\
& E(1, 0) \rightarrow E(1, 1) \\
& E(2, 2) \leftarrow E(2, 1) \leftarrow E(2, 0) \\
& E(3, 0) \rightarrow E(3, 1) \rightarrow E(3, 2) \rightarrow E(3, 3) \\
& E(4, 4) \leftarrow E(4, 3) \leftarrow E(4, 2) \leftarrow E(4, 1) \leftarrow E(4, 0)
\end{aligned}
$$

That is:

$$
\begin{aligned}
& 1 \\
& 0 \rightarrow 1 \\
& 1 \leftarrow 1 \leftarrow 0 \\
& 0 \rightarrow 1 \rightarrow 2 \rightarrow 2 \\
& 5 \leftarrow 5 \leftarrow 4 \leftarrow 2 \leftarrow 0
\end{aligned}
$$

The advantage of arranging Entringer numbers this way is that it is consistent with its recurrence relation $E(n, k) = E(n, k-1) + E(n-1, n-k)$, making it easy to remember and understand.

Entringer numbers have an exponential generating function:

$$
\sum_{m=0}^\infty\sum_{n=0}^\infty E\left(m+n,\frac{1}{2}\left(m+n+{(-1)}^{m+n}(n-m)\right)\right)\frac{x^m}{m!}\frac{x^n}{n!}=\frac{\cos x+\sin x}{\cos (x+y)}
$$

The coefficient distribution of this generating function is actually a simple stretch deformation of the Seidel–Entringer–Arnold triangle above:

$$
\begin{array}{ccccc}
E(0,0) & E(1,1) & E(2,0) & E(3,3) & E(4,0) \\
E(1,0) & E(2,1) & E(3,2) & E(4,1) & \\
E(2,2) & E(3,1) & E(4,2) & & \\
E(3,0) & E(4,3) & & & \\
E(4,4) & & & &
\end{array}
$$

That is:

$$
\begin{aligned}
& 1\quad 1\quad 0\quad 2\quad 0\\
& 0\quad 1\quad 2\quad 2\\
& 1\quad 1\quad 4\\
& 0\quad 5\\
& 5
\end{aligned}
$$

## Zigzag Permutations

A zigzag permutation is a permutation $c_1$ to $c_i$ of $1$ to $n$ such that for any element $c_i$, its value is neither between $c_{i-1}$ and $c_{i+1}$.

For the number of zigzag permutations $Z_n$ ([OEIS A001250](http://oeis.org/A001250)), starting from $n = 0$:

$$
1, 1, 2, 4, 10, 32, 122, 544, \cdots
$$

For example, the alternating permutations for the first few $n$ are:

$$
\begin{aligned}
n=1: & \{1\}\\
n=2: & \{1,2\}, \{2,1\}\\
n=3: & \{1,3,2\}, \{2,1,3\}, \{2,3,1\}, \{3,1,2\}\\
n=4: & \{1,3,2,4\}, \{1,4,2,3\}, \{2,1,4,3\}, \{2,3,1,4\}, \{2,4,1,3\}, \\
& \{3,1,4,2\}, \{3,2,4,1\}, \{3,4,1,2\}, \{4,1,3,2\}, \{4,2,3,1\}
\end{aligned}
$$

## Alternating Permutations and Zigzag Numbers

(Note: Distinguish this from "derangements".)

For $n > 1$, each zigzag permutation, when reversed, is still a zigzag permutation. They can be paired up, so the number must be even.

Another pairing method: Divide zigzag permutations into alternating permutations (alternating permutations) and reverse alternating permutations (reverse alternating permutations).

The first element of an alternating permutation is greater than the second element, with the following relationship:

$$
c_1 > c_2 < c_3 > \cdots
$$

The first element of a reverse alternating permutation is less than the second element, with the following relationship:

$$
c_1 < c_2 > c_3 < \cdots
$$

If we swap positions 1 and $n$, 2 and $n-1$, and so on, the sets of alternating permutations and reverse alternating permutations are interchanged. Therefore, the numbers of alternating permutations and reverse alternating permutations are equal, each being exactly half of the number of zigzag permutations.

For $n > 1$, let:

$$
A_n = \frac{Z_n}{2}
$$

Define the initial values:

$$
A_0 = A_1 = 1
$$

Here, $A_n$ is called the zigzag number (Euler zigzag number, [OEIS A000111](http://oeis.org/A000111)), starting from $n = 0$:

$$
1, 1, 1, 2, 5, 16, 61, 272, \cdots
$$

Now let's try to solve for $A_n$.

From $1$ to $n$, select $k$ numbers to form a subset, which can be done in $\binom{n}{k}$ ways.

In this $k$-element subset, select a reverse alternating permutation $u$, which can be done in $A_k$ ways; using the full set minus this $k$-element subset, in the remaining $(n-k)$-element subset, select a reverse alternating permutation $v$, which can be done in $A_{n-k}$ ways.

Consider the permutation $w$ of $n+1$ elements: place the reversed $u$ at the beginning, followed by $n+1$, then followed by $v$. Then $w$ must be a zigzag permutation, and any $(n+1)$-element zigzag permutation can be cut at position $n+1$ to obtain corresponding reverse alternating permutations $u$ and $v$, and different $(n+1)$-element zigzag permutations correspond to different $u$ and $v$.

Therefore, we have the recurrence relation:

$$
2A_{n+1} = \sum_{k=0}^n \binom{n}{k} A_k A_{n-k}
$$

$$
2(n+1)\frac{A_{n+1}}{(n+1)!} = \sum_{k=0}^n \frac{A_k}{k!}\frac{A_{n-k}}{(n-k)!}
$$

When $n = 0$, this recurrence formula does not hold. The initial values $A_0$ and $A_1$ are both $1$.

This is a convolution of exponential generating functions. Assuming the exponential generating function of $A_n$ is $y$, we have the differential equation:

$$
2\frac{\mathrm{d}y}{\mathrm{d}x} = y^2 + 1
$$

The $+1$ on the right side is to handle the special case when $n = 0$. The general solution of this equation is:

$$
y = \tan\left(\frac{1}{2}x + C\right)
$$

After substituting that the 0th term is $1$, we can obtain the specific solution:

$$
y = \tan x + \sec x
$$

The tangent function is odd, the secant function is even, and their sum forms the generating function of zigzag numbers.

## Relationship between Entringer Numbers and Zigzag Numbers

According to the definition of Entringer numbers, Entringer number $E(n, k)$ is the number of alternating permutations of $0$ to $n$ with first element $k$. Therefore, Entringer numbers are related to zigzag numbers:

$$
A_n = E(n, n)
$$

The reason for calling $A_n$ "zigzag number": Let $E_n$ be the Euler number and $B_n$ be the Bernoulli number.

When $n$ is even, zigzag numbers with even indices are also called "secant numbers" $S_n$ or "zig numbers". There is the relationship:

$$
A_n = (-1)^{n/2}E_n
$$

The first few terms are ([OEIS A000364](http://oeis.org/A000364)):

$$
1, 1, 5, 61, 1385, \cdots
$$

When $n$ is odd, zigzag numbers with odd indices are also called "tangent numbers" $T_n$ or "zag numbers". There is the relationship:

$$
A_n = \frac{(-1)^{(n-1)/2}2^{n+1}(2^{n+1}-1)B_{n+1}}{n+1}
$$

The first few terms are ([OEIS A000182](http://oeis.org/A000182)):

$$
1, 2, 16, 272, 7936, \cdots
$$

Thus, for the Taylor expansion at $x = 0$, we can give secant numbers and tangent numbers:

$$
\sec x = A_0 + A_2\frac{x^2}{2!} + A_4\frac{x^4}{4!} + \cdots
$$

$$
\tan x = A_1x + A_3\frac{x^3}{3!} + A_5\frac{x^5}{5!} + \cdots
$$

Or written together:

$$
\sec x + \tan x = A_0 + A_1x + A_2\frac{x^2}{2!} + A_3\frac{x^3}{3!} + A_4\frac{x^4}{4!} + A_5\frac{x^5}{5!} + \cdots
$$

This forms the generating function of zigzag numbers.

## References and Links

1.  [Alternating permutation - Wikipedia](https://en.wikipedia.org/wiki/Alternating_permutation)