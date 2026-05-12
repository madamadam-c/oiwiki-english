author: c-forrest, Enter-tainer, hhc0001, Ir1d, KingMario, ksyx, Lutra-Fs, MegaOwIer, niujiaxing, StudyingFather, Tiphereth-A, TOMWT-qwq, ZnPdCo

**Positional notation**, also known as a **carry system**, **base system**, **positional notation**, **place-value notation**, or **positional numeral system**, is a numeral system that can represent all natural numbers using a finite set of symbols. The number of symbols available in a positional system is called the **radix** (or **base**). A base-$n$ system is called **$n$-ary** or **base-$n$** ($n>1$), such as decimal, which typically uses only the ten symbols `0, 1, 2, 3, 4, 5, 6, 7, 8, 9` for counting. "Carry" refers to the operation of setting a digit to 0 and incrementing the next higher digit when a digit reaches the base.

Generally, we write an $n$-ary number as $(a_k\cdots a_1a_0)_n$, $(a_k\cdots a_1a_0)_{(n)}$, ${a_k\cdots a_1a_0}_{(n)}$, or ${a_k\cdots a_1a_0}_{n}$. The subscript may be omitted if the base is implied by context. Note that $a_k\cdots a_1a_0$ here is not the product of $k+1$ numbers, but rather a sequence of digits.

For a $k$-ary number $a_n\cdots a_1a_0$, its value is $a_nk^n+\cdots+a_1k^1+a_0k^0=\sum_{i=0}^n a_ik^i$. For a number $m$, with its $k$-ary representation being $a_n\cdots a_1a_0$, we have:

$$
\begin{array}{cc}
    a_0=m-q_0k,&q_0=f(m/k),\\
    a_1=q_0-q_1k,&q_1=f(q_0/k),\\
    \vdots&\vdots\\
    a_n=q_{n-1}-q_nk,&q_n=f(q_{n-1}/k)=0,\\
\end{array}
$$

where $f(x)=\lfloor x\rfloor$.

The length of the $k$-ary representation of $n$ is $\lceil\log_k (n+1)\rceil$.

We generally use a decimal point "$.$" to denote fractions, a minus sign "$-$" to denote negative numbers, and an overline on a sequence of digits at the end to denote a repeating decimal. For readability, we can add separators (such as spaces, $,$ or `'`) every few digits, e.g., $12~345$ represents $12345$.

In computing, the commonly used positional systems are binary, octal, and hexadecimal.

## Conversion Between Different Bases

### Converting from Decimal to Other Bases

Here we demonstrate with binary as an example; other bases work similarly.

For the integer part, repeatedly divide the decimal number by $2$ until the quotient is $0$, then read the remainders from bottom to top. For the fractional part, multiply by $2$, take the integer part, then repeat with the fractional remainder until it becomes $0$, then read the integer parts from top to bottom.

???+ example "Example"
    Convert $35.25$ to binary.
    
    Integer part:
    
    $$
    \begin{aligned}
        35/2&=17  &\dots 1,\\
        17/2&=8   &\dots 1,\\
        8/2&=4    &\dots 0,\\
        4/2&=2    &\dots 0,\\
        2/2&=1    &\dots 0,\\
        1/2&=0    &\dots 1.
    \end{aligned}
    $$
    
    Fractional part:
    
    $$
    \begin{aligned}
        0.25\times 2&=0.5  &\dots 0,\\
        0.5\times 2&=1     &\dots 1.
    \end{aligned}
    $$
    
    Thus $35.25 = (100011.01)_2$.

???+ note "Implementation"
    ```cpp
    --8<-- "docs/math/code/base/base_1.cpp:from_dec"
    ```

### Converting to Decimal from Other Bases

Again, using binary as an example. To convert a binary number to decimal, multiply each digit by $2^i$, where $i$ is the position (0 for the units place).

???+ example "Example"
    Convert $(11010.01)_{2}$ to decimal.
    
    $$
    \begin{aligned}
        (11010.01)_{2}&=\phantom{+~}1\times 2^4+1\times 2^3+0\times 2^2+1\times 2^1+0\times 2^0\\
        &\phantom{=}+~0\times 2^{-1}+1\times 2^{-2} \\
                    &=26.25.
    \end{aligned}
    $$
    
    Thus $(11010.01)_2 = (26.25)_{10}$.

???+ note "Implementation"
    ```cpp
    --8<-- "docs/math/code/base/base_1.cpp:to_dec"
    ```

### Conversion Between Binary, Octal, and Hexadecimal

One octal digit can be represented by 3 binary digits (since $2^3 = 8$), and one hexadecimal digit can be represented by 4 binary digits ($2^4 = 16$), and vice versa.

## Method of Complements

See also: [Ones' complement and two's complement](../bit.md#integers-and-bit-sequences)

The **method of complements** is a technique for representing negative numbers using positive numbers, allowing subtraction to be performed using the same algorithm/circuit/mechanism as addition. Complement methods are widely used in the design of calculators and computers to simplify their structure.

For an $n$-digit number $a$ in base $b$, its **radix complement** (called the $b$'s complement) is $b^n-a$, and its **diminished radix complement** (called the $b-1$'s complement, or simply the **complement**) is $b^n-1-a$. In binary, the radix complement is called the **two's complement**, also known as the **two's complement form**; the diminished radix complement is called the **ones' complement**, also known as the **ones' complement form**. In decimal, the radix complement is called the **ten's complement**, and the diminished radix complement is called the **nine's complement**. Other bases follow the same pattern.

For $n$-digit numbers $x, y$ in base $b$, to compute $x-y$, we have the following methods (if the result exceeds $n$ digits, discard the higher digits):

1.  Find the diminished radix complement of $x$, $x'=b^n-1-x$, compute $x'+y=b^n-1-x+y$, then the diminished radix complement of this result is the answer.
2.  Find the diminished radix complement of $y$, $y'=b^n-1-y$, compute $x+y'=b^n-1+x-y$, then simply add 1 to get the answer.
3.  Find the radix complement of $x$, $x'=b^n-x$, compute $x'+y=b^n-x+y$, then the radix complement of this result is the answer.
4.  Find the radix complement of $y$, $y'=b^n-y$, compute $x+y'=b^n+x-y$, which is the answer.

Additionally, for a number in base $k$, let $d=k-1$. Then $\cdots dd=:\overline{d}=\sum_{i=0}^{\infty} dk^i=-1$. So for an $n$-digit number $x$, with its radix complement represented as $a_{n-1}\cdots a_1a_0$ in base $k$, then $\overline{d}a_{n-1}\cdots a_1a_0$ equals $\sum_{i=0}^{n-1}a_ik^i+\sum_{i=n}^{\infty} dk^i=k^n-x+(-k^n)=-x$. This idea of "infinite-length numbers" can be generalized to the concept of [**$p$-adic numbers**](https://en.wikipedia.org/wiki/P-adic_number).

Furthermore, we have an interesting theorem relating complements to repeating decimals:

???+ note "Midy's Theorem"
    Let $a$ be a positive integer, $p$ be a positive prime, and $a/p$ in base $b$ be $0.\overline{a_1a_2\cdots a_l}$, where $l$ is the (minimal) period length. If $l$ is even[^note5], let $l=2k$. Then $a_1a_2\cdots a_k$ is the diminished radix complement of $a_{k+1}a_{k+2}\cdots a_{2k}$, i.e.:
    
    -   $a_i+a_{i+k}=b$,
    -   $a_1a_2\cdots a_k+a_{k+1}a_{k+2}\cdots a_{2k}=b^k-1$.
    
    Furthermore, if $l$ has a nontrivial divisor $k$, with $l=nk$, then $\sum_{i=0}^{n-1}a_{ik+1}a_{ik+2}\cdots a_{(i+1)k}$ is a multiple of $b^k-1$.

??? example "Example"
    For $1/19=0.\overline{052~631~578~947~368~421}=0.\overline{032~745}_{(8)}$, we have:
    
    -   $052~631~578+947~368~421=999~999~999$,
    -   $052+631+578+947+368+421=3\times 999$,
    -   $032_{(8)}+745_{(8)}=777_{(8)}$,
    -   $03_{(8)}+27_{(8)}+45_{(8)}=77_{(8)}$.

??? note "Proof"
    For the variables $a,b,p,l,n,k$ in the theorem, it is easy to see that $1\leq a<p$, $b>1$, and $(a,p)=(b,p)=1$.
    
    For an integer $0\leq i<l$, let $f(i)=b^i\cdot a/p-\lfloor b^i\cdot a/p\rfloor$. We have
    
    $$
    0<f(i)=0.\overline{a_{i+1}a_{i+2}\cdots a_{nk}a_1a_2\cdots a_i}<1 \implies 0<pf(i)<p.
    $$
    
    Note that $pf(i)\in\mathbf{N}_+$ and $pf(i)\equiv ab^i\pmod p$, so $pf(i)=ab^i\bmod p$.
    
    Let $S_n=\sum_{i=0}^{n-1}f(ik)=\sum_{i=0}^{n-1}0.\overline{a_{ik+1}a_{ik+2}\cdots a_{nk}a_1a_2\cdots a_{ik}}$. We can "swap" digits among the fractional parts (e.g., $0.\overline{{\color{Orchid}{14}}{\color{RoyalBlue}{28}}{\color{YellowGreen}{57}}}+0.\overline{{\color{RoyalBlue}{28}}{\color{YellowGreen}{57}}{\color{Orchid}{14}}}+0.\overline{{\color{YellowGreen}{57}}{\color{Orchid}{14}}{\color{RoyalBlue}{28}}}=0.\overline{\color{Orchid}{141414}}+0.\overline{\color{RoyalBlue}{282828}}+0.\overline{\color{YellowGreen}{575757}}=0.\overline{\color{Orchid}{14}}+0.\overline{\color{RoyalBlue}{28}}+0.\overline{\color{YellowGreen}{57}}=14/99+28/99+57/99=1$). Then
    
    $$
    \begin{aligned}
        S_n&=\sum_{i=0}^{n-1}0.\overline{a_{ik+1}a_{ik+2}\cdots a_{(i+1)k}}\\
        &=\sum_{i=0}^{n-1}a_{ik+1}a_{ik+2}\cdots a_{(i+1)k}/\left(b^k-1\right),
    \end{aligned}
    $$
    
    thus
    
    $$
    pS_n=p\sum_{i=0}^{n-1}a_{ik+1}a_{ik+2}\cdots a_{(i+1)k}/\left(b^k-1\right)= \sum_{i=0}^{n-1} \left(ab^{ik}\bmod p\right),
    $$
    
    therefore
    
    $$
    \sum_{i=0}^{n-1}a_{ik+1}a_{ik+2}\cdots a_{(i+1)k}=\left(b^k-1\right)\frac{\sum_{i=0}^{n-1} \left(ab^{ik}\bmod p\right)}{p}.
    $$
    
    If $p\mid \left(b^k-1\right)$, note that
    
    $$
    \left(b^k-1\right)a/p=a_1a_2\cdots a_k.\overline{a_{k+1}a_{k+2}\cdots a_{nk}a_1a_2\cdots a_k}-0.\overline{a_{1}a_{2}\cdots a_{nk}},
    $$
    
    so $a_{k+1}a_{k+2}\cdots a_{nk}a_1a_2\cdots a_k=a_{1}a_{2}\cdots a_{nk}$, and thus $a_1a_2\cdots a_k=a_{k+1}a_{k+2}\cdots a_{2k}=\dots=a_{(n-1)k+1}a_{(n-1)k+2}\cdots a_{nk}$, meaning $0.\overline{a_1a_2\cdots a_l}=0.\overline{a_1a_2\cdots a_k}$, which contradicts the definition of $l$. Hence $p\nmid \left(b^k-1\right)$.
    
    Therefore, there exists a positive integer $c=\dfrac{\sum_{i=0}^{n-1} \left(ab^{ik}\bmod p\right)}{p}$ such that
    
    $$
    \sum_{i=0}^{n-1}a_{ik+1}a_{ik+2}\cdots a_{(i+1)k}=c\left(b^k-1\right).
    $$

???+ note "Corollary"
    For the $b,n,k,p$ above, we have
    
    $$
    \sum_{i=0}^{n-1} b^{ik}\equiv 0\pmod p.
    $$

## Generalized Positional Numeral Systems

In standard positional systems, the base $b$ is always a fixed positive number, and each digit selects from $b$ distinct symbols, representing a non-negative number (ignoring decimal points and minus signs). In practice, there are many numeral systems with similar characteristics but not fully conforming to standard positional notation. We call such systems **generalized positional numeral systems** or **non-standard positional numeral systems**. Below we introduce several common generalized systems.

### Bijective Numeral Systems

Standard positional systems are not bijective with the numbers they represent; for example, $1$, $01$, and $001$ all represent the same number[^note1]. A **bijective numeral system** establishes a bijection between representations and numbers.

A bijective base-$k$ system ($k\geq 1$) uses the digit set $\{1,2,\dots,k\}$ to uniquely represent numbers, with the following rules:

1.  The empty string represents $0$.
2.  A non-empty string $a_n\cdots a_1a_0$ represents the number $a_nk^n+\cdots+a_1k^1+a_0k^0=\sum_{i=0}^n a_ik^i$.

For a positive number $m$, with its bijective base-$k$ representation as $a_n\cdots a_1a_0$, we have:

$$
\begin{array}{cc}
    a_0=m-q_0k,&q_0=f(m/k),\\
    a_1=q_0-q_1k,&q_1=f(q_0/k),\\
    \vdots&\vdots\\
    a_n=q_{n-1}-q_nk,&q_n=f(q_{n-1}/k)=0,\\
\end{array}
$$

where $f(x)=\lceil x\rceil-1$.

For example, Microsoft Excel's column labels use bijective base-26.

In bijective numeral systems, we have [unary](https://en.wikipedia.org/wiki/Unary_numeral_system), where non-empty strings consist only of $1$'s, and the length of the string represents the number.

Similar to the discussion of the [method of complements](#method-of-complements), in bijective base-$k$ where $k>1$, let $d=k-1$. Then $\cdots dd=:\overline{d}=\sum_{i=0}^{\infty} dk^i=-1$, and $\overline{d}k=0$. So if $x$ has bijective base-$k$ representation $a_{n-1}\cdots a_1a_0$, then $\overline{d}ka_{n-1}\cdots a_1a_0$ represents $-x$.

Here are some properties of bijective base-$k$ numbers:

-   There are exactly $k^l$ numbers of length $l\geq 0$.
-   When $k\geq 2$, the length of the bijective base-$k$ representation of number $n$ is $\lfloor\log_k (n+1)(k-1)\rfloor$.
-   When $k\geq 2$, if a number $n$ has no $0$ in its base-$k$ representation, then its base-$k$ and bijective base-$k$ representations are identical.

Converting bijective base-$k$ to decimal uses the same code as base-$k$ to decimal. Below is a reference implementation for converting decimal to bijective base-$k$:

???+ note "Implementation"
    ```cpp
    --8<-- "docs/math/code/base/base_1.cpp:from_dec_bi"
    ```

### Signed-Digit Positional Systems

Some positional systems allow negative digits in their representation, such as [balanced ternary](./balanced-ternary.md).

### Gray Code

Main article: [Gray Code](./gray-code.md)

Gray code, also called **cyclic binary code** or **reflected binary code** (RBC), is a special binary numeral system commonly used in data validation.

### Non-Positive Base Systems

We know that for a base-$k$ number $a_n\cdots a_1a_0$, its value is $\sum_{i=0}^n a_ik^i$. With a slight modification, we can define a base-$k$ number ${a_n\cdots a_1a_0}_{(-k)}$ to represent $\sum_{i=0}^n a_i(-k)^i$, where $a_n,\dots,a_1,a_0\in \{0,1,\dots,k-1\}$. For example, $12345_{(-10)}=8265_{(10)}$. This system is called a [**negative-base system**](https://en.wikipedia.org/wiki/Negative_base).

Similarly, we can define a [**complex-base system**](https://en.wikipedia.org/wiki/Complex-base_system), such as the [**quater-imaginary base**](https://en.wikipedia.org/wiki/Quater-imaginary_base) (quater-imaginary numeral system). We can also define a [**non-integer base of numeration**](https://en.wikipedia.org/wiki/Non-integer_base_of_numeration) for representing real numbers via **$\beta$-expansion**.

### Mixed-Radix Systems

In standard positional systems, each digit position has the same base. Mixed-radix systems allow different bases for each digit position. The most common application of mixed-radix systems is timekeeping: hours use base-24, minutes and seconds use base-60.

The number $a_n\cdots a_1a_0$ in base $b$ represents $\sum_{i=0}^n a_ib^i$, while in a mixed-radix system it represents $\sum_{i=0}^n a_i\prod_{j=0}^{i-1}b_j$, where $b_j$ is the base corresponding to $a_j$.

In competitive programming, the most common mixed-radix system is the [**factorial number system**](https://en.wikipedia.org/wiki/Factorial_number_system), where numbers can be written as ${a_n\cdots a_1a_0}_{~!}$, representing $\sum_{i=0}^na_i i!$[^note2]. Applications of the factorial number system in competitive programming can be found in [Lehmer code/Cantor expansion](../permutation.md#ranking).

???+ note "Implementation (decimal to factorial)"
    ```cpp
    --8<-- "docs/math/code/base/base_1.cpp:from_dec_factorial"
    ```

???+ note "Implementation (factorial to decimal)"
    ```cpp
    --8<-- "docs/math/code/base/base_1.cpp:to_dec_factorial"
    ```

## Implementation in C++

For non-negative numbers, C++ represents integer literals as `<prefix><digits><suffix>`, where both `<digits>` and `<suffix>` may be empty. The `<suffix>` indicates the type of the literal, such as `u` or `U` for `unsigned`, `l` or `L` for `long`, etc. For `<prefix>`:

-   When `<prefix>` is `0x` or `0X`, it denotes a hexadecimal literal; `<digits>` can only contain `0, 1, 2, 3, 4, 5, 6, 7, 8, 9, a, A, b, B, c, C, d, D, e, E, f, F`. For example, `0x1234ABCD` is $\text{1234ABCD}_{(16)}=305~441~741$.
-   When `<prefix>` is `0`, it denotes an octal literal; `<digits>` can only contain `0, 1, 2, 3, 4, 5, 6, 7`. For example, `01234567` is $1234567_{(8)}=342391$.[^note3]
-   When `<prefix>` is `1`, `2`, `3`, `4`, `5`, `6`, `7`, `8`, or `9`, it denotes a decimal literal; `<digits>` can only contain `0, 1, 2, 3, 4, 5, 6, 7, 8, 9`.
-   Since C++14, when `<prefix>` is `0b` or `0B`, it denotes a binary literal; `<digits>` can only contain `0, 1`. For example, `0b11001010` is $11001010_{(2)}=202$.

## References and Notes

-   [Positional notation - Wikipedia](https://en.wikipedia.org/wiki/Positional_notation)
-   [Method of complements - Wikipedia](https://en.wikipedia.org/wiki/Method_of_complements)
-   [Non-standard positional numeral systems - Wikipedia](https://en.wikipedia.org/wiki/Non-standard_positional_numeral_systems)
-   [Bijective numeration - Wikipedia](https://en.wikipedia.org/wiki/Bijective_numeration)
-   [Midy's theorem - Wikipedia](https://en.wikipedia.org/wiki/Midy%27s_theorem)
-   [N3472 - Binary Literals in the C++ Core Language](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3472.pdf)

[^note1]: We call zeros before the highest non-zero digit [**leading zeros**](https://en.wikipedia.org/wiki/Leading_zero). Similarly, we can define [**trailing zeros**](https://en.wikipedia.org/wiki/Trailing_zero).

[^note2]: The base corresponding to $a_i$ is $i+1$, with $0\leq a_i\leq i$. Note that $(n+1)!-n!=n\cdot n!$, so the representation of a number in factorial base is unique after removing leading zeros.

[^note3]: `0` is an octal literal.

[^note4]: Some regions use "$,$" as the decimal point.

[^note5]: When $a=1$, the sequence of primes satisfying this condition in decimal is [A028416](https://oeis.org/A028416).