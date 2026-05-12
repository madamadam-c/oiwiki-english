author: Enter-tainer, Falicitas, HeRaNO, iamtwz, ImpleLee, Tiphereth-A, Xeonacid, Yanjun-Zhao

## Definition

Balanced ternary, also known as symmetric ternary, is a generalized positional system.

Standard ternary digits are composed of `0`, `1`, and `2`, while balanced ternary uses `-1`, `0`, and `1`. Its base is also `3` (because there are three possible values). Since writing `-1` as a digit is inconvenient, we use the letter `Z` to represent `-1`.

## Explanation

Here are some examples:

| Decimal | Balanced Ternary | Decimal | Balanced Ternary |
| --- | ----- | --- | ----- |
| `0` | `0`   | `5` | `1ZZ` |
| `1` | `1`   | `6` | `1Z0` |
| `2` | `1Z`  | `7` | `1Z1` |
| `3` | `10`  | `8` | `10Z` |
| `4` | `11`  | `9` | `100` |

Negative numbers are easy to represent: simply flip the digits of the positive number (`Z` becomes `1`, `1` becomes `Z`).

| Decimal  | Balanced Ternary |
| ---- | ----- |
| `-1` | `Z`   |
| `-2` | `Z1`  |
| `-3` | `Z0`  |
| `-4` | `ZZ`  |
| `-5` | `Z11` |

It is easy to see that negative numbers have `Z` as their most significant digit, while positive numbers have `1`.

## Conversion Process

In the balanced ternary conversion method, we first write the given number $x$ in standard ternary. When $x$ is expressed in standard ternary, each digit is `0`, `1`, or `2`. Starting from the lowest digit and iterating upward, we can skip any `0`s and `1`s, but when encountering a `2`, we should change it to `Z` and add `1` to the next higher digit. When encountering digit `3`, it should become `0` and add `1` to the next higher digit.

### Application 1

Convert `64` to balanced ternary.

First, write this number in standard ternary:

$$
\text 64_{10} = 02101_3
$$

Let's process from the digit with the least effect on the entire number (the least significant digit):

-   `101` is skipped (since `0` and `1` are allowed in balanced ternary);
-   `2` becomes `Z`, and the digit to its left is incremented by `1`, giving `1Z101`;
-   `1` is skipped, resulting in `1Z101`.

The final result is `1Z101`.

Let's convert it back to decimal:

$$
\texttt {1Z101}=81 \times 1 +27 \times (-1) + 9 \times 1 + 3 \times 0 + 1 \times 1 = 64_{10}
$$

### Application 2

Convert `237` to balanced ternary.

First, write this number in standard ternary:

$$
\text 237_{10} = 22210_3
$$

-   `0` and `1` are skipped (since `0` and `1` are allowed in balanced ternary);
-   `2` becomes `Z`, and the digit to the left is incremented by `1`, giving `23Z10`;
-   `3` becomes `0`, and the digit to the left is incremented by `1`, giving `30Z10`;
-   `3` becomes `0`, and the digit to the left (defaulting to `0`) is incremented by `1`, giving `100Z10`;
-   `1` is skipped, resulting in `100Z10`.

The final result is `100Z10`.

Let's convert it back to decimal:

$$
\texttt{100Z10} = 243 \cdot 1 + 81 \cdot 0 + 27 \cdot 0 + 9 \cdot (-1) + 3 \cdot 1 + 1 \cdot 0 = 237_{10}
$$

## Properties

For a balanced ternary number $X_3$, it uniquely maps to a decimal number $Y_{10}$ by multiplying each digit $x_i$ by its corresponding weight $3^i$.

So for a decimal number $Y_{10}$, does it **uniquely correspond to one balanced ternary number**?

The answer is yes. This property is called the uniqueness of balanced ternary.

???+ note "Proof"
    We use **proof by contradiction**:
    
    Suppose a decimal number $Y_{10}$ has two **different balanced ternary numbers** $A_3, B_3$ that both convert to $Y_{10}$ in decimal. We need to prove $A_3 = B_3$. Consider cases:
    
    1.  When $Y_{10}=0$, clearly $A_3 = B_3 = 0_3$, contradicting the assumption.
    2.  When $Y_{10}>0$:
    
        -   Number the positions of digits in $A_3$ and $B_3$ from least significant to most significant. Let $a_i$ be the $i$-th digit of $A_3$, and $b_i$ be the $i$-th digit of $B_3$. In $A_3$ and $B_3$, there must exist an $i$ such that $a_i \neq b_i$. Notice that positions $i-1, i-2, \dots, 0$ are irrelevant to the proof. Thus, shifting $A_3$ and $B_3$ right by $i$ positions yields $A_3', B_3'$, and the original problem reduces to proving $A_3' = B_3'$.
        -   For the least significant digit of $A_3', B_3'$, we have $a_0 \neq b_0$. Suppose $b_0 > a_0$ (the case where $a_0 > b_0$ is symmetric). It follows that $b_0 - a_0 \in \{1, 2\}$. The contribution of digits at position $i=1,2,3,\dots$ to $A_3'$ is $S_1 = a_1 \times 3^1 + a_2 \times 3^2 + \dots$, and the contribution to $B_3'$ is $S_2 = b_1 \times 3^1 + b_2 \times 3^2 + \dots$. Since $A_3' = B_3'$, we get $S_1 - S_2 = b_0 - a_0$. $S_1$ and $S_2$ share a common factor of $3$, but $b_0 - a_0$ is not divisible by $3$, contradicting the assumption. Therefore $A_3' \neq B_3'$.
    3.  When $Y_{10}<0$, the proof is the same as for $Y_{10}>0$.
    
    Hence, for any decimal $Y_{10}$, there is a unique corresponding balanced ternary $X_3$.

## Practice Problems

[Topcoder SRM 604 PowerOfThree](https://archive.topcoder.com/ProblemStatement/pm/12917)

**Some content of this page is adapted from the article [Троичная сбалансированная система счисления](http://e-maxx.ru/algo/balanced_ternary) and its English translation [Balanced Ternary](https://cp-algorithms.com/algebra/balanced-ternary.html). The Russian version is in the Public Domain with a link requirement; the English version is licensed under CC-BY-SA 4.0.**