## Introduction

The **Kahan summation** algorithm, also known as compensated summation or carry summation, is an algorithm used to **reduce the error in the accumulated sum of a finite-precision floating-point sequence**. It mainly works by maintaining a separate variable to accumulate the error, commonly named $c$.

The algorithm was mainly discovered by William Kahan in the 1960s. Since Ivo Babuška also independently proposed a similar algorithm, Kahan summation is also known as the Kahan-Babuška summation algorithm.

## Rounding Error

In computer programs, we need to approximate real numbers with a finite number of bits. Most modern computers use floating-point numbers specified by [IEEE-754](https://en.wikipedia.org/wiki/IEEE_754) as this approximation. For $\frac{1}{3}$, because we cannot represent it exactly with finitely many bits, when using IEEE-754 representation, part of the value must be rounded (truncate). This **rounding error** is a characteristic of floating-point computation.

In floating-point addition, commutativity holds, but associativity does not. That is, $a+b = b+a$ but $(a+b)+c \neq a+(b+c)$. Therefore, when adding a floating-point sequence, we can accumulate from left to right one by one, or pair up numbers in the original order. The second algorithm is relatively slower and requires more memory, and is often used by specific summation functions in some languages, but its result is more accurate.

To obtain a more accurate floating-point accumulation result, we need to use Kahan summation.

When computing $S_{new}=S_{old}+a$ (where $a$ is one value in the floating-point sequence), define the value actually added to $S$ as $a_{eff}=S_{new}-S_{old}$. If $a_{eff}$ is greater than $a$, there is upward rounding error; if $a_{eff}$ is less than $a$, there is downward rounding error. The rounding error is defined as $E_{roundoff} = a_{eff} - a$. The value used to correct this rounding error is therefore $a-a_{eff}$, the negative of $E_{roundoff}$. Define $c$ as the compensation variable for lost low-order bits, and we get $c_{new} = c_{old} + (a - a_{eff})$.

## Procedure

Kahan summation mainly uses one separate variable to accumulate error. As shown in the reference code below, $sum$ is the final accumulated result. $c$ is the compensation variable for lost low-order bits (the part that was discarded), and is the necessary variable in Kahan summation.

Because $sum$ is large and $y$ is small, the low-order bits of $y$ are lost. $(t - sum)$ cancels the high-order part of $y$, and subtracting $y$ restores the negative value (the low-order part of $y$). Therefore, algebraically, $c$ is always zero. In the next iteration, the lost low-order part is updated and added to $y$.

## Implementation

??? note "Reference Code"
    ```cpp
    float kahanSum(vector<float> nums) {
      float sum = 0.0f;
      float c = 0.0f;
      for (auto num : nums) {
        float y = num - c;
        float t = sum + y;
        c = (t - sum) - y;
        sum = t;
      }
      return sum;
    }
    ```

## Exercises

In OI, Kahan summation mainly exists as an auxiliary tool, providing computation results with smaller error.

???+ note "Example [CodeForces Contest 800 Problem A. Voltage Keepsake](https://codeforces.com/contest/800/problem/A)"
    There are $n$ devices being used at the same time. The $i$-th device consumes $a_{i}$ units of power per second. This usage is continuous. That is, during $\lambda$ seconds, the device consumes $\lambda \times a_{i}$ units of power. The $i$-th device currently stores $b_{i}$ units of power. All devices can store any amount of power. There is a charger that can be plugged into any single device. The charger adds $p$ units of power per second to a device. This charging is continuous. That is, if a device is plugged in for $\lambda$ seconds, it gains $\lambda \times p$ units of power. We can switch which device is being charged at any real-valued time point (the time required for switching is ignored). Find the longest time these devices can be used before some device reaches $0$ units of power.

???+ note "Example [CodeForces Contest 504 Problem B. Misha and Permutations Summation](https://codeforces.com/problemset/problem/504/B)"
    Define the sum of two permutations $p$ and $q$ of numbers $0, 1, \cdots, (n - 1)$ as $Perm((Ord(p)+Ord(q))\bmod n!)$, where $Perm(x)$ is the $x$-th lexicographic permutation of numbers $0, 1, \cdots, (n-1)$ (counting from zero), and $Ord(p)$ is the number of permutation $p$ in lexicographic order. For example, $Perm(0) = (0, 1, \cdots , n - 2, n - 1)$, $Perm(n! - 1) = (n - 1, n-2,\cdots, 1,0))$. Misha has two permutations $p$ and $q$; find their sum.

## Summation in Programming Languages

Python's standard library specifies the exactly rounded summation function [fsum](https://docs.python.org/3/library/math.html#math.fsum), which can return the accurate floating-point sum of values in an iterable. It avoids precision loss by using Shewchuk's algorithm to track multiple intermediate partial sums.

In Julia, the default implementation of the [sum](https://docs.julialang.org/en/v1/base/collections/#Base.sum) function is pairwise summation, achieving high precision and good performance. Meanwhile, the external library function [sum\_kbn](http://www.jlhub.com/julia/manual/en/function/sum_kbn) provides a Neumaier variant implementation for cases requiring higher precision; see [KahanSummation.jl](https://github.com/JuliaMath/KahanSummation.jl) for details.

## References and Notes

1.  [Kahan\_summation\_algorithm - Wikipedia](https://en.wikipedia.org/wiki/Kahan_summation_algorithm)
2.  [Kahan summation - Rosetta Code](https://rosettacode.org/wiki/Kahan_summation)
3.  [VK Cup Round 2 + Codeforces Round 409 Announcement](https://codeforces.com/blog/entry/51577)
4.  [Rounding off errors in Java - GeeksforGeeks](https://www.geeksforgeeks.org/rounding-off-errors-java/)
