Bit operations refer to unary and binary operations on the binary representation of integers, divided into **bitwise operations** and **shifts**. Bit operations are among the most fundamental operations in the CPU and are usually quite fast.

## Integers and Bit Sequences

See also: [Integer types](../lang/var.md#整数类型), [Two's complement](./numeral-sys/base.md#补数法)

We call a fixed-length sequence consisting only of `0` or `1` a bit sequence. The leftmost bit is called the most significant bit, and the rightmost bit is called the least significant bit.

Computers use bit sequences to represent integers within a certain range. A bit sequence of length $N$ has only $2^N$ different states, so it can only establish a one-to-one correspondence with $2^N$ integers. This one-to-one correspondence can be divided into two types: **signed** and **unsigned**. Signed means the corresponding integers include negative numbers; unsigned means the corresponding integers are all non-negative.

- For the unsigned correspondence, we can directly use the binary representation of the integer as the bit sequence, padding with `0` at the high bits if needed.

    Under the unsigned correspondence, a bit sequence of length $N$ can represent integers in $[0,2^N-1]$.

- For the signed correspondence, we have two representation rules: **ones' complement** and **two's complement**.

    For non-negative integers, the representation rule is the same as the unsigned rule; for negative integers, we take the bit sequence of its opposite number, **bitwise negate** it (changing `0` to `1` and `1` to `0`) to get the ones' complement, then convert the ones' complement to an integer according to the unsigned correspondence, add one, then convert to a bit sequence according to the unsigned correspondence, discarding any overflow beyond the original bit sequence length. The resulting new sequence is called two's complement.

    Under the ones' complement correspondence, a bit sequence of length $N$ can represent integers in $[-2^{N-1}+1,2^{N-1}-1]$.

    Under the two's complement correspondence, a bit sequence of length $N$ can represent integers in $[-2^{N-1},2^{N-1}-1]$.

Using 3-bit sequences as an example:

| Bit sequence | Unsigned integer | Signed integer (ones' complement) | Signed integer (two's complement) |
| ----- | ----- | --------- | --------- |
| `000` | $0$   | $0$       | $0$       |
| `001` | $1$   | $1$       | $1$       |
| `010` | $2$   | $2$       | $2$       |
| `011` | $3$   | $3$       | $3$       |
| `100` | $4$   | $-3$      | $-4$      |
| `101` | $5$   | $-2$      | $-3$      |
| `110` | $6$   | $-1$      | $-2$      |
| `111` | $7$   | $-0$      | $-1$      |

We can see that the main problem with ones' complement is the existence of $-0$, which is actually a non-existent "negative number," so we generally only use two's complement. Since when representing signed integers, the sign is determined solely by the most significant bit of the bit sequence, we call this bit the **sign bit**.

Converting a bit sequence to an integer is also straightforward: for non-negative numbers, no special operation is needed; for ones' complement, negating gives the opposite number; for two's complement, negating and adding one gives the opposite number.

## Bitwise Operations

Bitwise operations are operations that apply certain [Boolean functions](./boolean-algebra.md#布尔函数) bit by bit to bit sequences. Formally, for a Boolean function $f:\mathbf{B}^k\to \mathbf{B}$, a bitwise operation is a function of the form

$$
\begin{aligned}
    F:\left(\mathbf{B}^m\right)^k&\to \mathbf{B}^m\\
    ((p_{1,1},\dots,p_{m,1}),\dots,(p_{1,k},\dots,p_{m,k}))&\mapsto (f(p_{1,1},\dots,p_{1,k}),\dots,f(p_{m,1},\dots,p_{m,k}))
\end{aligned}
$$

where $m$ is the length of the bit sequence. Similarly, we generally only study unary and binary bitwise operations. Unless otherwise specified, the following discussion of bitwise operations is limited to unary and binary cases.

Generally, we consider **bitwise NOT**, **bitwise AND**, **bitwise OR**, and **bitwise XOR** as basic bitwise operations. All other bitwise operations can be composed from these.

| Bitwise operation | Mathematical symbol | Corresponding Boolean function | C++ operator | Explanation |
| ---- | ----------------------------- | -------- | --------------- | ----------------------- |
| Bitwise NOT | $\operatorname{NOT}$ | $\lnot$ | `~` | $0$ becomes $1$, $1$ becomes $0$ |
| Bitwise AND | $\operatorname{AND}$ | $\land$ | `&` | Result is $1$ only when both corresponding bits are $1$ |
| Bitwise OR | $\operatorname{OR}$ | $\lor$ | <code>\|</code> | Result is $1$ if at least one corresponding bit is $1$ |
| Bitwise XOR | $\oplus$, $\operatorname{XOR}$ | $\oplus$ | `^` | Result is $1$ only when the two corresponding bits are different |

???+ warning "Warning"
    Note the distinction between bitwise operations and Boolean functions.

For example:

- $\operatorname{NOT} 01010111 = 10101000$,
- $01010011 \operatorname{AND} 00110010 = 00010010$,
- $01010011 \operatorname{OR} 00110010 = 01110011$,
- $01010011 \operatorname{XOR} 00110010 = 01100001$.

Since the four bitwise operations operate on each bit independently, they directly inherit the properties of their corresponding Boolean functions.

For convenience, when the bit sequence length is known, we can also directly perform bitwise operations on integers, for example:

$$
\begin{aligned}
    \operatorname{NOT} 5 &= -6,\\
    \operatorname{NOT} (-5) &= 4,\\
    5 \operatorname{AND} 6 &= 4,\\
    5 \operatorname{OR} 6 &= 7,\\
    5 \operatorname{XOR} 6 &= 3.
\end{aligned}
$$

Assuming $x, y \geq 0$, we can also express bitwise operations in summation form:

$$
\begin{aligned}
    \operatorname{NOT} x &=\sum_{n=0}^{\lfloor\log_{2}x\rfloor}2^n\left(\left(\left\lfloor\frac{x}{2^n}\right\rfloor\bmod 2+1\right)\bmod 2\right)\\
    &=\sum_{n=0}^{\lfloor\log_{2}x\rfloor}\left(2^{\left\lfloor\log_{2}x\right\rfloor +1}-1-x\right)\\
    x\operatorname{AND} y &=\sum_{n=0}^{\lfloor\log_{2}\max\{x,y\}\rfloor}2^n\left(\left\lfloor\frac{x}{2^n}\right\rfloor\bmod 2\right)\left(\left\lfloor{\frac{y}{2^n}}\right\rfloor\bmod 2\right)\\
    x\operatorname{OR} y &=\sum_{n=0}^{\lfloor\log_{2}\max\{x,y\}\rfloor}2^n\left(\left(\left\lfloor\frac{x}{2^n}\right\rfloor\bmod 2\right)+\left(\left\lfloor{\frac{y}{2^n}}\right\rfloor\bmod 2\right)-\left(\left\lfloor\frac{x}{2^n}\right\rfloor\bmod 2\right)\left(\left\lfloor{\frac{y}{2^n}}\right\rfloor\bmod 2\right)\right)\\
    x\operatorname{XOR} y &=\sum_{n=0}^{\lfloor\log_{2}\max\{x,y\}\rfloor}2^n\left(\left(\left(\left\lfloor\frac{x}{2^n}\right\rfloor\bmod 2\right)+\left(\left\lfloor{\frac{y}{2^n}}\right\rfloor\bmod 2\right)\right)\bmod 2\right)\\
    &=\sum_{n=0}^{\lfloor\log_{2}\max\{x,y\}\rfloor}2^n\left(\left(\left\lfloor\frac{x}{2^n}\right\rfloor +\left\lfloor\frac{y}{2^n}\right\rfloor\right)\bmod 2\right)
\end{aligned}
$$

In the absence of ambiguity, "bitwise" is omitted below.

## Shifts

See also: [C++ bitwise operators](../lang/op.md#位操作符).

Shift is a type of binary operation that moves a bit sequence "bit by bit to the left or right." The first argument is the bit sequence, and the second argument is generally a non-negative integer. Moving left is called **left shift**, and moving right is called **right shift**. Based on how the vacated bits are filled, shift operations can be divided into **arithmetic shift**, **logical shift**, and **circular shift**. Among these:

- Logical shift fills vacated bits with 0.
- Arithmetic right shift fills vacated bits with the sign bit; arithmetic left shift is the same as logical left shift.
- Circular shift fills vacated bits with the overflow bits.

For example, for an 8-bit sequence `10 01 01 10`:

| Operation         | Result            |
| ---------- | ------------- |
| Arithmetic left shift by 2 | `01 01 10 00` |
| Arithmetic right shift by 2 | `11 10 01 01` |
| Logical left shift by 2 | `01 01 10 00` |
| Logical right shift by 2 | `00 10 01 01` |
| Circular left shift by 2 | `01 01 10 10` |
| Circular right shift by 2 | `10 10 01 01` |

In C++, we use `a << b` for left shift and `a >> b` for right shift. For specific shift rules, see [C++ bitwise operators](../lang/op.md#位操作符).

We can implement circular shift using the following code:

???+ note "Implementation"
    ```cpp
    --8<-- "docs/math/code/bit/bit_1.cpp:core"
    ```

## Applications of Bit Operations

Bit operations generally have three purposes:

1. Perform certain computations efficiently, replacing other less efficient methods. See [Compiler optimizations #Strength reduction](../lang/optimizations.md#强度削减-strength-reduction).
2. [Represent sets](./binary-set.md) (commonly used in [state compression DP](../dp/state.md)).
3. The problem itself requires bit operations.

Note that using bit operations to replace other computation methods often does not bring significant optimization, but makes the code more complex. Use with caution.

### Applications related to powers of 2

Since bit operations work on binary representation, many applications related to powers of 2 can be derived.

Multiplying (dividing) a number by a nonnegative integer power of 2:

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:mul"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:mul"
    ```

??? warning "Warning"
    Our usual division rounds toward zero, while right shift rounds down (note the difference). When the number is greater than or equal to 0, the two methods are equivalent; when the number is less than 0, there is a difference: for example, `-1 / 2` equals $0$, while `-1 >> 1` equals $-1$.

### Absolute value

On some machines, this is more efficient than `n > 0 ? n : -n`.

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:abs"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:abs"
    ```

### Getting the max/min of two numbers

On some machines, this is more efficient than `a > b ? a : b`.

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:minmax"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:minmax"
    ```

### Checking if two non-zero numbers have the same sign

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:sgn"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:sgn"
    ```

### Swapping two numbers

???+ note "This method has limitations"
    This method can only be used to swap two integers, so its range of application is limited.
    
    For general swap operations, it is recommended to directly call the `std::swap` function from the `algorithm` library.

```cpp
--8<-- "docs/math/code/bit/bit_2.cpp:swap"
```

### Manipulating individual bits of a number

Getting a specific bit of a number in binary:

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:get_bit"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:get_bit"
    ```

Setting a specific bit of a number in binary to $0$:

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:unset_bit"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:unset_bit"
    ```

Setting a specific bit of a number in binary to $1$:

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:set_bit"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:set_bit"
    ```

Toggling a specific bit of a number in binary:

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:flap_bit"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:flap_bit"
    ```

These operations are equivalent to treating a 32-bit integer as a boolean array of length 32.

## Hamming Weight

Hamming weight is the number of symbols in a string that differ from the zero-symbol (defined on the character set being used). For a binary number, its Hamming weight equals the number of $1$s (i.e., popcount).

To compute the Hamming weight of a number, we can solve it iteratively: we continuously remove the last bit in binary (i.e., right shift by 1), maintain an answer variable, and update the answer based on whether the lowest bit is $1$.

The code is as follows:

```cpp
--8<-- "docs/math/code/bit/bit_2.cpp:popcnt1"
```

Another way to compute the Hamming weight of a number is using the `lowbit` operation: we continuously subtract its `lowbit`[^note1] from the number until the number becomes $0$.

The code is as follows:

```cpp
--8<-- "docs/math/code/bit/bit_2.cpp:popcnt2"
```

### Constructing permutations with increasing Hamming weight

In [state compression DP](../dp/state.md), enumerating in order of increasing popcount can sometimes avoid enumerating duplicate states. This is one major use of constructing permutations with increasing Hamming weight.

Let's explore how to construct such permutations in $O(n)$ time.

We know that the smallest integer with Hamming weight $n$ is $2^n - 1$. If we can construct a successor with equal Hamming weight in constant time, we can construct the required permutation for $0 \sim n$ in $O(n)$ time by enumerating Hamming weights, starting from $2^n - 1$ and continuously finding the next number.

And finding the successor of a number $x$ with equal Hamming weight can be done as follows, using $(10110)_2$ as an example:

- Move the rightmost $1$ of $(10110)_2$ to the left. If it cannot be moved, move the $1$ to its left, and so on, to get $(11010)_2$.

- Then move all the $1$s from the position where the last moved $1$ originally was to the lowest bit to the rightmost side. Here, the last moved $1$ was originally in the third position, so the last three bits $010$ become $001$, yielding $(11001)_2$.

This process can be optimized using bit operations:

```cpp
--8<-- "docs/math/code/bit/bit_3.cpp:hamming1"
```

- In the first step, adding the `lowbit` to $x$ is equivalent to replacing the rightmost consecutive run of $1$s in $x$ with a $1$ to its left. For the binary number $(10110)_2$ mentioned earlier, adding its `lowbit` results in $(11000)_2$. This actually gives us the first part of our answer.

- Next, we need to fill in the remaining $1$s in the answer. The `lowbit` of $t$ is the position where the leftmost $1$ of the rightmost consecutive run of $1$s in $x$ moves to, while the `lowbit` of $x$ is the position of the rightmost $1$ in that run. Still using $(10110)_2$ as an example, $t = (11000)_2$, $\operatorname{lowbit}(t) = (01000)_2$, $\operatorname{lowbit}(x) = (00010)_2$.

- The division operation in the following part is the most difficult to understand in this bit operation, but also the most critical. Let the **original number** have its rightmost consecutive run of $1$s with the highest $1$ at bit position $r$ (bit positions start from 0) and the lowest $1$ at bit position $l$. The `lowbit` of $t$ equals `1 << (r+1)`, and the `lowbit` of $x$ equals `1 << l`. The result of `(((t&-t)/(x&-x))>>1)` is `(1<<(r+1))/(1<<l)/2 = (1<<r)/(1<<l) = 1<<(r-l)`, which in binary is $1$ followed by $r-l$ zeros. The number of zeros exactly equals the number of consecutive $1$s minus $1$. Taking our earlier number as an example, $\frac{\operatorname{lowbit}(t)/2}{\operatorname{lowbit}(x)} = \frac{(00100)_2}{(00010)_2} = (00010)_2$. Subtracting $1$ from this number gives the low bits we need to fill, and OR-ing with the original number gives the answer.

Therefore, the complete code for enumerating permutations with increasing Hamming weight from $0 \sim n$ is:

```cpp
--8<-- "docs/math/code/bit/bit_3.cpp:hamming2_begin"
--8<-- "docs/math/code/bit/bit_3.cpp:hamming2_end"
```

Note the special case of $0$, as $0$ has no successor with equal Hamming weight.

## Relevant Classes and Functions in C++

### GCC Built-in Functions

GCC also provides some built-in functions for bit operations:

- `int __builtin_ffs(int x)`: Returns the position of the last $1$ in the binary representation of $x$, with positions numbered starting from $1$ (the least significant bit is numbered $1$). Returns $0$ when $x$ is $0$.
- `int __builtin_clz(unsigned int x)`: Returns the number of leading zeros in the binary representation of $x$. When $x$ is $0$, the result is undefined.
- `int __builtin_ctz(unsigned int x)`: Returns the number of trailing zeros in the binary representation of $x$. When $x$ is $0$, the result is undefined.
- `int __builtin_clrsb(int x)`: When the sign bit of $x$ is $0$, returns the number of leading zeros in the binary representation of $x$ minus one; otherwise, returns the number of leading $1$s minus one.
- `int __builtin_popcount(unsigned int x)`: Returns the number of $1$s in the binary representation of $x$.
- `int __builtin_parity(unsigned int x)`: Determines the parity (odd/even) of the number of $1$s in the binary representation of $x$.

All these functions can have `l` or `ll` added to the function name (e.g., `__builtin_popcountll`) to change the parameter type to (`unsigned`)`long` or (`unsigned`)`long long` (the return type is still `int`).

For example, sometimes we want to compute the logarithm base 2 of a number. Ignoring the special case of $0$, this is equivalent to the number of bits in its binary representation minus 1. For an $N$-bit integer $n$, the number of bits in its binary representation can be expressed as `N - __builtin_clz(n)`. Therefore, `N - 1 - __builtin_clz(n)` gives the logarithm base 2 of $n$.

Since these functions are built-in, they are highly optimized by the compiler and run very fast (some require only a single instruction).

### More Bits

If you need to operate on very long bit sequences, you can use [`std::bitset`](../lang/csl/bitset.md).

## Recommended Problems

- [Luogu P1225 Black-White Chess Game](https://www.luogu.com.cn/problem/P1225)

## References and Notes

1. [Bit Twiddling Hacks](https://graphics.stanford.edu/~seander/bithacks.html)
2. [Bit Operation Builtins (Using the GNU Compiler Collection (GCC))](https://gcc.gnu.org/onlinedocs/gcc/Bit-Operation-Builtins.html)
3. [Bitwise operation - Wikipedia](https://en.wikipedia.org/wiki/Bitwise_operation)

[^note1]: The first $1$ in a number's binary representation from low to high, together with the zeros after it. For example, the `lowbit` of $(1010)_2$ is $(0010)_2$. See [Fenwick tree](../ds/fenwick.md) for details.