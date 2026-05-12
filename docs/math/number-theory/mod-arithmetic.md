author: 383494, buuzzing, c-forrest, cr4c1an, Emp7iness, Enter-tainer, Great-designer, HeRaNO, jifbt, Kaiser-Yang, Koishilll, ksyx, Marcythm, Qiu-Quanzhi, Saisyc, sshwy, StarryReverie, StudyingFather, Tiphereth-A, Xeonacid, xyf007

In competitive programming, an important component of number theory is **modular arithmetic**, which involves various integer operations under a given modulus. Beyond basic arithmetic operations (addition, subtraction, multiplication) and exponentiation, modular arithmetic also conveniently supports taking logarithms, extracting roots, computing factorials, and calculating binomial coefficients.

Modular arithmetic commonly appears in many types of problems, not just in number theory. The actual answer to many problems may be extremely large, exceeding the storage range of common integer types. To avoid introducing big integer arithmetic and printing long numbers, problems often require the answer to be taken modulo before output. This requires proficiency with various modular arithmetic techniques.

## Integer Division and Modulo in C/C++

In C/C++, integer division and modulo operations differ from the mathematical conventions.

For all standard versions of C/C++, the rules for integer division are:

1.  When the divisor is 0, the behavior is undefined;
2.  Otherwise, `(a / b) * b + a % b` equals `a`.

That is, the sign of the modulo operation depends on how the division rounds; and how the division rounds is implementation-defined (determined by the compiler).

Since C99 and C++11, division truncates toward zero (discarding the fractional part); the sign of the modulo then matches the dividend. Therefore, the following assertions always hold:

```c
assert(5 % 3 == 2);
assert(5 % -3 == 2);
assert(-5 % 3 == -2);
assert(-5 % -3 == -2);
```

## Modular Integer Class

Modular arithmetic can be viewed as performing various operations on congruence classes modulo a given number. If we represent a congruence class using a struct, and encapsulate operations like addition, subtraction, and multiplication as struct methods or operator overloads, then modular arithmetic naturally becomes a modular integer class. Below is a simple example that supports addition, subtraction, multiplication, and fast exponentiation of 32-bit signed integers under a modulus $M < 2^{30}$:

???+ example "A Simple Modular Integer Class"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/mod-arithmetic.cpp:core"
    ```

This implementation intentionally reduces the number of modulo operations, because modulo is usually much more expensive than ordinary addition, subtraction, multiplication, or comparison. The code comments provide equivalent but more straightforward implementations. The main idea behind these simple optimizations is that when two integers in $[0, M)$ undergo addition or subtraction, the result always lies in $(-M, 2M)$. Therefore, it can be adjusted back to $[0, M)$ with a single addition or subtraction. The exponentiation in this implementation uses the fast exponentiation technique.

Beyond these basic operations, the following can also be performed under various moduli:

-   [Multiplicative inverse](./inverse.md)
-   [Division](./linear-equation.md)
-   [Factorials](./factorial.md)
-   [Binomial coefficients](./lucas.md)
-   [Square roots](./quad-residue.md#modular-square-root)
-   [Logarithms](./discrete-logarithm.md)
-   [Roots](./residue.md#modular-root)

These operations are generally easier under a prime modulus. For a composite modulus, extended versions of the corresponding algorithms and the Chinese Remainder Theorem are often needed. Most of these modular operations can be viewed as solving some congruence equation. For general methods on solving congruence equations, refer to the Congruence Equation page.

## Related Algorithms

This section introduces methods to optimize modulo, multiplication, and fast exponentiation operations under a modulus. For the vast majority of problems, the simple implementation provided earlier is already sufficiently efficient. However, when the problem has strict requirements on algorithmic constants, these optimization methods can help by reducing unnecessary computations and modulo operations.

### Fast Multiplication

In primality testing and integer factorization, we often encounter modular multiplication where the modulus fits in a `long long`. To avoid integer overflow during computation, this section introduces a fast multiplication method that handles moduli within the `long long` range without using `__int128`, with $O(1)$ complexity. This algorithm requires that `long double` be represented as at least an 80-bit extended precision floating-point number on the evaluation system.

Assume $0 \le a, b < m$ and we want to compute $ab\bmod m$. Notice that:

$$
ab\bmod m=ab-\left\lfloor \dfrac{ab}m \right\rfloor m.
$$

Using natural overflow of `unsigned long long`:

$$
ab\bmod m=ab-\left\lfloor \dfrac{ab}m \right\rfloor m=\left(ab-\left\lfloor \dfrac{ab}m \right\rfloor m\right)\bmod 2^{64}.
$$

As long as we can compute the quotient $\left\lfloor\dfrac{ab}m\right\rfloor$, the multiplication and subtraction in the rightmost expression can be performed directly using `unsigned long long`.

Next, we only need to consider how to compute $\left\lfloor\dfrac {ab}m\right\rfloor$. The solution is to use `long double` to compute $\dfrac am$ and then multiply by $b$. Since we use `long double`, there will inevitably be precision error. Assuming `long double` is an 80-bit extended precision floating-point number (1 sign bit, 15 exponent bits, 64 mantissa bits), `long double` can accurately represent at most 64 significant bits. Therefore, $\dfrac am$ may start to diverge from the 65th bit onward, with an error range of $\left(-2^{-64},2^{-64}\right)$. Multiplying by $b$, a 64-bit signed integer, the error range becomes $(-0.5,0.5)$. To simplify the subsequent discussion, we add $0.5$ first and then round, resulting in an error range of $\{0,1\}$.

Finally, when substituting into the formula for computation, we need to multiply by $-m$, so the final error range becomes $\{0,-m\}$. Since $m$ is within the `long long` range, when the result $r\in[0,m)$, return $r$ directly; otherwise return $r+m$.

The implementation is as follows:

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/i64-mul.cpp:ld-mul"
    ```

Today, most evaluation systems' C/C++ compilers already support the `__int128` type, so we can also directly promote the multiplier type to `__int128` and then compute the modulo:

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/i64-mul.cpp:i128-mul"
    ```

Of course, `__int128` modulo operations are not inexpensive. If we need to further optimize for constant factors, we can consider the methods introduced in the next two sections.

### Barrett Reduction

As mentioned earlier, division and modulo operations are generally more expensive than the other four arithmetic operations. To reduce the overhead of modulo operations, there are algorithms that can obtain the same result without performing modulo directly. The Barrett reduction algorithm introduced in this section is one such method.

Let $m$ be a fixed modulus, and suppose we need to compute $a\bmod m$ for various $a > 0$. By the division algorithm,

$$
z = a\bmod m = a - \left\lfloor\dfrac{a}{m}\right\rfloor m.
$$

The key is computing the quotient $\left\lfloor\dfrac{a}{m}\right\rfloor$. Let $R$ be some constant, then

$$
\left\lfloor\dfrac{a}{m}\right\rfloor = \left\lfloor a\dfrac{R}{m} / R\right\rfloor \approx \left\lfloor a\left\lfloor\dfrac{R}{m}\right\rfloor/R\right\rfloor.
$$

If we choose $R = 2^k$, then $\left\lfloor\dfrac{R}{m}\right\rfloor$ can be precomputed, and division by $R$ can be done via a bit shift. Therefore, using the right-hand side to compute the quotient requires only one multiplication and one shift operation. Substituting back into the expression for $a\bmod m$ gives an estimate $z'$ for the desired remainder.

Now let's analyze the error. The floor function has the property that for $x > y > 0$, $\lfloor x\rfloor - \lfloor y\rfloor \le \lceil x - y\rceil$. So the error is

$$
\begin{aligned}
\Delta &= |z' - z| = m\left|\left\lfloor\dfrac{a}{m}\right\rfloor - \left\lfloor a\left\lfloor\dfrac{R}{m}\right\rfloor/R\right\rfloor\right|\\
&\le m\left\lceil a\left(\dfrac{R}{m} - \left\lfloor\dfrac{R}{m}\right\rfloor\right) /R\right\rceil \le m\left\lceil\dfrac{a}{R}\right\rceil.
\end{aligned}
$$

As long as $a \le R$, the error $\Delta$ does not exceed $m$. Since $z' \ge z$, the estimated value $z'$ can only be $z$ or $z + m$. By subtracting the extra $m$ when $z' \ge m$ after obtaining the estimate, we can guarantee a correct answer.

In the process of Barrett reduction, only two multiplications, one shift operation, and at most two subtractions are used to complete the integer modulo. But the efficiency gain is not without cost: the intermediate variables in Barrett reduction are often longer than the input variables. It is easy to see that the longest intermediate variable in Barrett reduction is $a\left\lfloor\dfrac{R}{m}\right\rfloor$. Let $\ell(x)$ be the binary length of integer $x$. Then

$$
\ell\left(a\left\lfloor\dfrac{R}{m}\right\rfloor\right) \approx \ell(a) + \ell(R) - \ell(m).
$$

Since $R$ must satisfy $a < R$, this length is at least $2\ell(a) - \ell(m)$. However, when taking a modulo, we generally have $\ell(m)\le\ell(a)$, so the intermediate variable length may be greater than the input length $\ell(a)$. For example, if we need to take a 64-bit integer modulo a 32-bit integer, the intermediate variable actually requires 96 bits.

One application of Barrett reduction is computing the remainder of a product $ab\bmod m$. If one factor is fixed, say $b$, we can use

$$
ab\bmod m = ab - \left\lfloor a\left\lfloor\dfrac{bR}{m}\right\rfloor/R\right\rfloor m
$$

for an estimation similar to the above, requiring only $\left\lfloor\dfrac{bR}{m}\right\rfloor$ to be precomputed. This fixed-$b$ case is sometimes called Shoup modular multiplication.

The more common case is that both $a$ and $b$ are variable. In this case, we first compute $ab$, then use Barrett reduction to obtain $ab\bmod m$. For example, when implementing modular multiplication, we need to compute $ab\bmod m$ for $0 \le a,b < m$. Here, the chosen $R$ must satisfy $ab < R$. From the previous analysis, the longest intermediate variable in the computation is $2\ell(ab)-\ell(m)$. When $\ell(a)\approx\ell(b)\approx\ell(m)$, this length is $3\ell(m)$. That is, if we use Barrett reduction to implement 32-bit integer modular multiplication, the intermediate variable requires 96 bits. This is a limitation of Barrett reduction in practical competitive programming applications.

As an example, the reference implementation of 32-bit signed integer modular multiplication using Barrett reduction is as follows:

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/i32-mul.cpp:barrett"
    ```

The implementation requires 128-bit integers.

### Montgomery Modular Multiplication

The Montgomery modular multiplication algorithm has a similar function to Barrett's algorithm, also reducing the overhead of modulo operations in modular integer arithmetic. Unlike the previous two algorithms which both approximate the quotient, Montgomery modular multiplication maps all integers into Montgomery space, where operations are relatively easier, thereby reducing the overall computational cost.

Let the modulus $m$ be odd and choose $R = 2^k > m$. Then the Montgomery form of the congruence class $a \bmod m$ is

$$
aR\bmod m.
$$

Since $R\perp m$, there is a bijection between the congruence class $a \bmod m$ and its Montgomery form $aR\bmod m$. Therefore, we can convert integers to Montgomery form, perform several operations modulo $m$, and then convert the resulting Montgomery form back to an integer, with the result always being correct.

Using Montgomery form, many modular integer operations can be conveniently performed. We have already shown that to compare two congruence classes for equality, we only need to compare their Montgomery forms. Also, since

$$
(a+b)R\bmod m = ((aR\bmod m)\pm(bR\bmod m)) \bmod{m},
$$

addition and subtraction of congruence classes correspond to addition and subtraction of their Montgomery forms. However, to compute the multiplication of congruence classes, we cannot directly multiply two Montgomery forms. Because

$$
(ab)R\bmod m = ((aR\bmod m)(bR\bmod m)R^{-1})\bmod{m},
$$

so to compute the multiplication of two Montgomery forms, we need to perform a **Montgomery reduction** on their product $x$:

$$
\operatorname{REDC}: x \mapsto xR^{-1}\bmod m.
$$

Using this operation, the Montgomery form of the product $ab$ is $\operatorname{REDC}((aR\bmod m)(bR\bmod m))$. The Montgomery reduction is the core operation of Montgomery modular multiplication:

-   Converting $a$ to its Montgomery form is $\operatorname{REDC}((a\bmod m)(R^2\bmod m))$.
-   Converting the Montgomery form of $a$ back to $a\bmod m$ is $\operatorname{REDC}(aR\bmod m)$.
-   The Montgomery form of the modular inverse $a^{-1}\bmod m$ is $\operatorname{REDC}((aR\bmod m)^{-1}(R^3\bmod m))$.

Now we discuss the implementation of the Montgomery reduction $\operatorname{REDC}$. When computing $\operatorname{REDC}(x)$, we always assume $0 \le x < m^2$, which holds for all the above cases. Since $R\perp m$, by Bézout's theorem, there exist integers $R^{-1}, m'$ such that

$$
RR^{-1} + mm' = 1.
$$

So, let $q=\lfloor xm' / R\rfloor$, then

$$
\begin{aligned}
xR^{-1} &= x\dfrac{1 - mm'}{R} \equiv \dfrac{x-xmm' + qmR}{R} = \dfrac{x - m(xm'\bmod R)}{R} \pmod{m}.
\end{aligned}
$$

Since $0 \le x < m^2 < mR$ and $0 \le xm'\bmod R < R$, we have

$$
-m < \dfrac{x - m(xm'\bmod R)}{R} < m.
$$

That is, this quotient differs from $xR^{-1}\bmod m$ by at most one $m$. So we just need to add $m$ back when the quotient is negative to obtain $\operatorname{REDC}(x)$. Computing this quotient requires only two integer multiplications, one integer subtraction, and two bit operations (respectively taking modulo $R=2^k$ and performing division). Therefore, the Montgomery reduction can be performed efficiently.

To perform Montgomery modular multiplication, a series of constants need to be precomputed. First, $m' = m^{-1}\bmod R$ used in Montgomery reduction can be computed using the Newton–Hensel method described in the next section. Second, when reducing different operations to Montgomery reduction, constants such as $R^2\bmod m$ are involved. To obtain it, we first compute $R\bmod m$ once, add it to itself to get $2R\bmod m$. Then, treating it as the Montgomery form of $2$, we directly compute fast exponentiation to get $2^kR\bmod m = R^2\bmod m$.

As an example, the Montgomery modular multiplication implementation for 32-bit signed integers is as follows:

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/i32-mul.cpp:montgomery"
    ```

Compared to the Barrett reduction implementation of modular multiplication, Montgomery modular multiplication involves multiple steps: conversion, Montgomery form multiplication, and inverse conversion. Therefore, only when the number of modular operations between conversion and inverse conversion is large enough can the conversion and inverse conversion costs be amortized, achieving higher overall efficiency. However, since Montgomery modular multiplication only involves intermediate variables of length $2\ell(m)$, it is more flexible to implement. For example, 32-bit integer modular multiplication only requires 64-bit intermediate variables. So, if we need to implement a modular integer class for various number theory computations, Montgomery modular multiplication is more suitable.

### Modular Integer Class for Powers of 2

This section discusses the implementation of the modular integer class when the modulus is a power of 2. In this special case, division and modulo operations can be implemented using bit operations, achieving high computational efficiency. Barrett reduction and Montgomery modular multiplication both accelerate computation by leveraging the property of $2^e$ being the divisor and modulus. Specifically, when the modulus is exactly $2^{32}$, $2^{64}$, etc., we can implement the modular integer class using unsigned integers of the corresponding bit length combined with natural overflow, without any explicit modulo operations. Even when the modulus is not exactly such a number, it can be reduced to these special moduli cases. For example, when the modulus is $2^{58}$, we can complete intermediate computations under modulus $2^{64}$, and finally take the result modulo $2^{58}$. Beyond convenient modulo operations, there are also many special implementations for other operations of integers modulo $2^e$. This section focuses on the implementation of modular inverses and exponentiation.

First, the inverse operation: given an odd number $a$ and modulus $m=2^e~(e > 2)$, find $a^{-1}\bmod m$. Common methods for finding modular inverses include the extended Euclidean algorithm and fast exponentiation. The extended Euclidean algorithm involves modulo operations for general moduli; the ordinary fast exponentiation method requires computing $a^{\varphi(m)-1}\bmod{m}$, which requires $\Theta(e)$ integer multiplications. A more efficient method is the Newton–Hensel method. Specifically, consider applying the following conclusion:

$$
mx \equiv 1 \pmod{2^e} \implies mx(2 - mx) \equiv 1\pmod{2^{2e}}.
$$

According to this expression, starting from $x = 1$ and repeatedly applying $x \gets x(2-mx)$, we obtain $m^{-1}\bmod R$ after $\lceil\log_2 e\rceil$ iterations.

As an example, the reference implementation of the modular inverse for modulo $2^{32}$ is as follows:

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/mod-32-inv-pow.cpp:inv"
    ```

Next, we discuss the exponentiation operation: given $x, a, b$ and modulus $m=2^e~(e > 2)$, find $xa^b\bmod m$, where $a$ is odd. According to the analysis of the multiplicative structure of integers modulo $2^e$, $a$ can always be written as $\pm g^{\ell}$, and the negative sign appears if and only if $a\equiv 3\pmod 4$. For this case, we can replace $a$ with $-a$ and multiply the final result by $(-1)^b$. Therefore, we assume $a\equiv 1\pmod 4$ holds for the following discussion. The core idea of the algorithm is to write $a$ as $g^{L(a)}\bmod m$, and then compute $xg^{bL(a)}\bmod m$.

Computing $L(a)$ is computing the discrete logarithm $\operatorname{ind}_ga$. Notice that as long as $a\equiv 1\pmod 4$, $a$ can always be written in the following form:

$$
a \equiv (2^{e_1}+1)(2^{e_2}+1)\cdots(2^{e_s}+1) \pmod{m},
$$

where $1 < e_1 < e_2 < \cdots < e_s < e$. This is because expanding this product reveals that the second-least significant 1-bit in the binary representation of $a$ is at position $e_1$ (index starting from 0), allowing us to recursively find this representation. According to the properties of discrete logarithms, we have

$$
4L(a) \equiv 4L(2^{e_1}+1) + 4L(2^{e_2}+1) + \cdots + 4L(2^{e_s}+1) \pmod{m}.
$$

Since the modulus of the discrete logarithm equals the order $\delta_m(g)=2^{e-2}=m/4$, we multiply the entire congruence by 4 to ensure the computation can be performed in the residue classes modulo $m$. Therefore, by precomputing all $4L(2^d+1)$ for $1 < d < e$, we can quickly compute the value of $4L(a)$.

Conversely, from $L(a)$ we can also easily obtain $g^a\bmod{m}$. According to the binomial theorem, for $1 < d < e$, we have

$$
\begin{aligned}
(2^d+1)^{2^{e-d}} \equiv 1 \pmod{m},\quad
(2^d+1)^{2^{e-d-1}} \equiv 1 + 2^{e-1} \pmod{m},
\end{aligned}
$$

so $\delta_m(2^d+1) = 2^{e-d}$. According to the properties of orders,

$$
\delta_m(2^d+1) = \dfrac{\delta_m(g)}{\gcd(\delta_m(g), \operatorname{ind}_g(2^d+1))}.
$$

Therefore, $\gcd(\delta_m(g), \operatorname{ind}_g(2^d+1)) = 2^{d-2}$. This means $L(2^d+1) = \operatorname{ind}_g(2^d+1) = 2^{d-2}r$, where $2\nmid r$. So in the binary representation of $4L(2^d+1)$, the lowest 1-bit is exactly at position $d$ (index starting from 0). Therefore, we can also recursively decompose $4L(a)$ into a sum of terms of the form $4L(2^d+1)$ using its binary representation. From this, we can obtain the value of $a$.

During concrete implementation, there are some points for further optimization. First, when decomposing $a$ into a product form, division is still needed. A more convenient approach is to compute the decomposition of $a^{-1}$, that is, find $1 < e_1 < e_2 < \cdots < e_s < e$ such that

$$
a(2^{e_1}+1)(2^{e_2}+1)\cdots(2^{e_s}+1) \equiv 1 \pmod{m}
$$

holds. Similarly, we find the second-least significant 1-bit to determine $e_1$, but to eliminate the $2^{e_1}+1$ factor from $a^{-1}$, we only need to multiply $2^{e_1}+1$ on $a$, which can be done via bit operations. Also, since $4L(a^{-1})=-4L(a)$, when counting $4L(a)$, we need to use subtraction instead of addition. Second, for a specially chosen base $g$, the iteration does not need to go all the way to $d = e-1$, but only to $d = \lceil e/2\rceil - 1$. To achieve this, we need to choose $g$ such that

$$
4L(2^{\lceil e/2\rceil} + 1) = 2^{\lceil e/2\rceil}.
$$

For $d \ge e / 2$, we have

$$
(2^d+1)^2 = 2^{2d} + 2^{d+1} + 1 \equiv 2^{d+1} + 1 \pmod{m}.
$$

So by induction starting from $d = \lceil e/2\rceil$, $L(2^d+1)=2^d$ holds for all $d \ge e/2$. Consequently, as long as $e/2 \le e_1 < e_2 < \cdots < e_s < e$, we have

$$
(2^{e_1}+1)(2^{e_2}+1)\cdots(2^{e_s}+1) \equiv 1 + 2^{e_1} + 2^{e_2} + \cdots + 2^{e_s} \pmod{m}
$$

and

$$
4L((2^{e_1}+1)(2^{e_2}+1)\cdots(2^{e_s}+1)) = 2^{e_1} + 2^{e_2} + \cdots + 2^{e_s}.
$$

Therefore, after processing all binary digits with $d < e/2$, we can directly obtain the discrete logarithm of the remaining part without calculating it bit by bit. After applying the first optimization, the entire exponentiation operation requires only $O(e)$ additions/subtractions and bit operations plus 1 multiplication; after applying the second optimization, we can save about half of the additions/subtractions and bit operations, but need an additional 1 multiplication.

As an example, the reference implementation of modular exponentiation for modulo $2^{32}$ is as follows:

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/mod-32-inv-pow.cpp:pow"
    ```

The precomputation of discrete logarithms can be done using the Pohlig–Hellman algorithm, and the base $g$ can be chosen as

$$
5^{\operatorname{ind}_5(2^{\lceil e/2\rceil})/2^{\lceil e/2\rceil - 2}}\bmod{2^e}.
$$

## References and Notes

-   [Fast modular multiplication by orz - Codeforces](https://codeforces.com/blog/entry/96759)
-   [Barrett Reduction - Wikipedia](https://en.wikipedia.org/wiki/Barrett_reduction)
-   [Barrett Reduction - A41](https://encrypt.a41.io/primitives/modular-arithmetic/modular-reduction/barrett-reduction#cost-analysis-of-modular-multiplication)
-   [Barrett Reduction Principle and Correctness Proof by Chen - Zhihu Column](https://zhuanlan.zhihu.com/p/690876166)
-   [Montgomery Multiplication - CP Algorithms](https://cp-algorithms.com/algebra/montgomery_multiplication.html)
-   [Montgomery Modular Multiplication by Chen - Zhihu Column](https://zhuanlan.zhihu.com/p/645428404)
-   [Binary Exponentiation by Factoring - CP Algorithms](https://cp-algorithms.com/algebra/factoring-exp.html)
-   Barrett, Paul. "Implementing the Rivest Shamir and Adleman public key encryption algorithm on a standard digital signal processor." In Conference on the Theory and Application of Cryptographic Techniques, pp. 311-323. Berlin, Heidelberg: Springer Berlin Heidelberg, 1986.
-   Becker, Hanno, Vincent Hwang, Matthias J. Kannwischer, Bo-Yin Yang, and Shang-Yi Yang. "Neon NTT: Faster Dilithium, Kyber, and Saber on Cortex-A72 and Apple M1." IACR Transactions on Cryptographic Hardware and Embedded Systems (2022): 221-244.
-   Montgomery, Peter L. "Modular multiplication without trial division." Mathematics of computation 44, no. 170 (1985): 519-521.

[^long-double-80bit]: This applies to GCC or Clang compilers on most 64-bit systems.

[^floating-format]: See [Double-precision floating-point format - Wikipedia](https://en.wikipedia.org/wiki/Double-precision_floating-point_format).

[^ld-mul-err]: This uses the condition $a < m$, i.e., $a / m \in [0,1)$.

[^int128]: On current mainstream compilers, only MSVC on Windows does not support the `__int128` type. If cross-platform compatible code is needed, the macro `_MSC_VER` can be used to detect the MSVC compiler environment and include the [`<intrin.h>`](https://learn.microsoft.com/en-us/cpp/intrinsics/x64-amd64-intrinsics-list?view=msvc-170) header file under that condition, using its built-in functions (such as `_umul128`, etc.) to indirectly implement 128-bit integer arithmetic (only available on 64-bit platforms).

[^floor-barrett]: Here $\left\lfloor\dfrac{r}{m}\right\rfloor$ can also be replaced with other integer estimates of $\dfrac{r}{m}$, such as the ceiling function $\left\lceil\dfrac{r}{m}\right\rceil$ and the rounding function $\left\lfloor\dfrac{r}{m}\right\rceil$, as long as the error correction step for the estimate is adjusted accordingly.

[^shoup]: Shoup implemented this extension of Barrett reduction in his number theory library [NTL](https://libntl.org/), hence the name.

[^newton-hensel]: Direct verification: from $mx \equiv 1 \pmod{2^e}$, we can set $mx = 1 + \lambda 2^e$, then $mx(2-mx) = (1+\lambda 2^e)(1-\lambda 2^e) = 1 - \lambda^2 2^{2e} \equiv 1\pmod{2^{2e}}$.

[^mod-2-g]: The referenced page only proves that $g$ can be $5$. In fact, by completely repeating that proof, it can be shown that $g$ can be any integer congruent to $5$ modulo $8$. The method of choosing $g$ will be discussed later in this article.
