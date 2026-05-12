author: ChungZH, Yukimaikoriya, tigerruanyifan, isdanni, Saisyc, 383494, Tiphereth-A, XuYueming520

## Introduction

**Number-theoretic transform** (NTT) is the implementation of discrete Fourier transform (DFT) based on number theory; **fast number-theoretic transform** (FNTT) is the implementation of [fast Fourier transform](./fft.md) (FFT) based on number theory.

**Number-theoretic transform** is a fast algorithm for computing convolution. The most common algorithm includes the fast Fourier transform mentioned earlier. However, fast Fourier transform has some implementation drawbacks—for example, the data vector must be multiplied by a matrix of complex coefficients, and each complex coefficient's real and imaginary parts are sine and cosine functions, so most coefficients are floating-point numbers, meaning complex and floating-point arithmetic must be performed, resulting in larger computational load and significant errors from floating-point arithmetic.

NTT solves the problem of polynomial multiplication with a modulus. It has some limitations due to the modulus, and numbers can be relatively large. The most common modulus is 998244353.

## Prerequisites

Prerequisites for learning number-theoretic transform: discrete Fourier transform, subgroups, [primitive roots](../number-theory/primitive-root.md), discrete logarithm. Related knowledge can be learned on the corresponding pages and will not be repeated here.

## Definition

### Number-Theoretic Transform

In mathematics, NTT is discrete Fourier transform (DFT) on any [ring](../algebra/basic.md#ring). In the case of finite fields, it is usually called number-theoretic transform (NTT).

**Number-theoretic transform** (NTT) is achieved by making discrete Fourier transform into $F={\mathbb {Z}/p}$, i.e., integers modulo a prime $p$. This is a **finite field**. As long as $n$ divides $p-1$, there exists an $n$-th primitive root, so we have $p=\xi n+1$ for positive integer $\xi$. Specifically, for prime $p=qn+1, (n=2^m)$, the primitive root $g$ satisfies $g^{qn} \equiv 1 \pmod p$. Taking $g_n=g^q\pmod p$ as the equivalent of $\omega_n$, it satisfies similar properties, such as $g_n^n \equiv 1 \pmod p, g_n^{n/2} \equiv -1 \pmod p$.

Since number-theoretic transform is involved here, $N$ (to distinguish from $n$ in FFT, we call it $N$ here) can be larger than $n$ in FFT, but as long as we take $\frac{qN}{n}$ as $q$ here, we can avoid the size issue.

Common ones are:

$$
p = 167772161 = 5 \times 2^{25}+1, g=3
$$

$$
p = 469762049 = 7 \times 2^{26}+1, g=3
$$

$$
p = 754974721 = 3^2 \times 5 \times 2^{24}+1, g=11
$$

$$
p = 998244353 = 7 \times 17 \times 2^{23}+1, g=3
$$

$$
p = 1004535809 = 479 \times 2^{21}+1, g=3
$$

This is the equivalent of $g^{qn}$ to $\mathrm{e}^{2\pi \mathrm{i} n}$.

When iterating to length $l$, $g_l = g^{\frac{p-1}{l}}$, or $\omega_n = g_l = g_N^{\frac{N}{l}} = g_N^{\frac{p-1}{l}}$.

## Fast Number-Theoretic Transform

**Fast number-theoretic transform** (FNTT) is the fast algorithm obtained by adding divide-and-conquer operations to number-theoretic transform (NTT).

The divide-and-conquer method used in fast number-theoretic transform is exactly the same as that used in fast Fourier transform. This means that we can obtain the code for fast number-theoretic transform by making simple modifications to the fast Fourier transform code.

In algorithm competitions, the term NTT usually actually refers to fast number-theoretic transform. It is generally assumed that "number-theoretic transform" means "fast number-theoretic transform".

The logic for this abbreviation is similar to that for fast Fourier transform. In fact, "fast Fourier transform" (FFT) refers to "fast discrete Fourier transform" (FDFT). However, since "fast" can only apply to discrete, or specifically the special case where the primitive root's order is a power of 2, it cannot apply to the continuous case. Therefore, the word "discrete" is omitted, and FDFT becomes FFT—meaning FFT always refers to the special discrete case.

Number-theoretic transform or fast number-theoretic transform is an operation performed under modular arithmetic. There is no continuous case; it is always discrete, so there is naturally no need to mention the word "discrete".

In the algorithm field, operations without speedup are meaningless. The reason we introduce DFT in the fast Fourier transform section is that DFT also has other specific applications in signal processing and image processing, and DFT is also the principle or prerequisite for FFT.

In cases where it does not cause confusion, NTT is often used to refer to FNTT. To avoid confusion with further introductions below, the two terms NTT and FNTT are separated in this article.

The specific relationships among DFT, FFT, NTT, FNTT are:

-   On the basis of DFT and NTT, add divide-and-conquer operations to get FFT and FNTT. The method and principle of divide-and-conquer can be found in the fast Fourier transform article.

-   On the basis of DFT and FFT, replace complex addition and complex multiplication with addition and multiplication modulo $p$, generally limited to between $0$ and $p-1$; replace the primitive root with a primitive root of the same order modulo $p$, with order being a power of 2, to get NTT and FNTT.

Since the replaced operations only involve addition and multiplication, DFT, FFT, NTT, and FNTT share the same principle—all operations are performed on rings that satisfy addition and multiplication, without requiring the more strict conditions of division on fields.

In fact, as long as there is a primitive root, i.e., a generator in group theory, NTT or FNTT can be performed under that modulus. Considering that moduli of $1$, $2$, and $4$ are too small to be practically meaningful, for odd primes $p$ and positive integer $\alpha$, as long as we are given primitive roots $g$ for moduli $p^\alpha$ and $2p^\alpha$, NTT or FNTT can still be performed using the same method.

## Template

??? example "[Library Checker - Convolution](https://judge.yosupo.jp/problem/convolution_mod)"
    ```cpp
    --8<-- "docs/math/code/poly/ntt/ntt_1.cpp"
    ```

## References and Further Reading

1.  [FWT (Fast Walsh Transform) Zero-Based Explanation qaq (ACM/OI)](https://zhuanlan.zhihu.com/p/41867199)
2.  [FFT (Fast Fourier Transform) 0-Based Explanation! Plus NTT (ACM/OI)](https://zhuanlan.zhihu.com/p/40505277)
3.  [Number-theoretic transform(NTT) - Wikipedia](https://en.wikipedia.org/wiki/Discrete_Fourier_transform_%28general%29#Number-theoretic_transform)
4.  [Tutorial on FFT/NTT—The tough made simple. (Part 1)](https://codeforces.com/blog/entry/43499)
5.  [NTT Template - BlackJack_ CSDN Blog](https://blog.csdn.net/blackjack_/article/details/79346433)