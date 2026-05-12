author: H-J-Granger, ranwen, abc1763613206, Ahacad, Allenyou1126, AndrewWayne, AngelKitty, AtomAlpaca, Backl1ght, billchenchina, c-forrest, CCXXXI, Cheuring, Chrogeek, ChungZH, countercurrent-time, DepletedPrism, Early0v0, EarthMessenger, Enter-tainer, F1shAndCat, GavinZhengOI, Gesrua, Great-designer, greyqz, Haohu Shen, henryrabbit, heroming, hly1204, Ir1d, isdanni, jiang1997, kenlig, Lewy Zeng, lucifer1004, Menci, muoshuosha, NachtgeistW, needtocalmdown, opsiff, ouuan, ouuan, partychicken, schtonn, Sshwy, sshwy, StudyingFather, SukkaW, Taoran-01, Tiphereth-A, TrisolarisHD, untitledunrevised, Xeonacid, YouXam, Yukimaikoriya

Prerequisites: [Complex Numbers](../complex.md).

This article will introduce an algorithm that supports computing the multiplication of two degree-$n$ polynomials in $O(n\log n)$ time, which is more efficient than the naive $O(n^2)$ algorithm. Since the multiplication of two integers can also be treated as polynomial multiplication, this algorithm can also be used to accelerate large integer multiplication.

## Introduction

Now let's introduce two polynomials $A$ and $B$:

$$
\begin{aligned}
A ={}& 5x^2 + 3x + 7 \\
B ={}& 7x^2 + 2x + 1 \\
\end{aligned}
$$

The product $C = A \times B$ can be solved in $O(n^2)$ time complexity (here $n$ is the degree of polynomial $A$ or $B$):

$$
\begin{aligned}
C ={}& A \times B \\
   ={}& 35x^4 + 31x^3 + 60x^2 + 17x + 7
\end{aligned}
$$

Obviously, the coefficients $c_i$ of polynomial $C$ satisfy $c_i = \sum_{j = 0}^i a_j b_{i - j}$. For this naive algorithm, computing each term takes $O(n)$ time, and there are $O(n)$ terms, so the time complexity is $O(n^2)$.

Can we accelerate it to reduce time complexity? If we use fast Fourier transform, we can reduce the complexity to $O(n \log n)$.

## Fourier Transform

Fourier Transform is a method for analyzing signals. It can analyze the components of a signal and also synthesize signals using those components. Many waveforms can serve as components of a signal, and Fourier Transform uses sine waves as the components of signals.

Let $f(t)$ be a function of time $t$. Fourier Transform can detect the degree to which a cycle of frequency $\omega$ appears in $f(t)$:

$$
F(\omega)=\mathbb{F}[f(t)]=\int_{-\infty}^{\infty}f(t)\mathrm{e}^{-\mathrm{i}{\omega}t}dt
$$

Its inverse transform is:

$$
f(t)=\mathbb{F}^{-1}[F(\omega)]=\frac{1}{2\pi}\int_{-\infty}^{\infty}F(\omega)\mathrm{e}^{\mathrm{i}{\omega}t}d\omega
$$

The form of the inverse transform is very similar to the forward transform. The denominator $2\pi$ is exactly the period of the exponential function.

Fourier Transform is equivalent to taking the continuous inner product of the time-domain function with a complex exponential function of period $2\pi$. The inverse transform is also an inner product.

Fourier Transform has a corresponding convolution theorem, which can transform convolution in the time domain to multiplication in the frequency domain, and also transform convolution in the frequency domain to multiplication in the time domain.

## Discrete Fourier Transform

**Discrete Fourier Transform** (DFT) is the discrete form of Fourier Transform in both time domain and frequency domain, transforming the time-domain sampling of a signal into its DTFT (discrete-time Fourier transform) frequency-domain sampling.

Fourier Transform is an integral form of continuous function inner product; Discrete Fourier Transform is a summation form of inner product.

Let $\{x_n\}_{n=0}^{N-1}$ be a sequence satisfying some finite condition. Its discrete Fourier transform (DFT) is:

$$
X_k=\sum_{n=0}^{N-1}x_n\mathrm{e}^{-\mathrm{i}\frac{2\pi}{N}kn}
$$

Where $\mathrm{e}$ is the base of natural logarithm, $i$ is the imaginary unit. Usually this transform is denoted by $\mathcal {F}$:

$$
\hat{x}=\mathcal{F}x
$$

Similar to the integral form, its **inverse discrete Fourier transform** (IDFT) is:

$$
x_n=\frac{1}{N}\sum_{k=0}^{N-1}X_k\mathrm{e}^{\mathrm{i}\frac{2\pi}{N}kn}
$$

Can be denoted as:

$$
x=\mathcal{F}^{-1}\hat{x}
$$

Actually, the normalization coefficients in front of DFT and IDFT are not important. In the above definition, the coefficients before DFT and IDFT are $1$ and $\frac {1}{N}$ respectively. Sometimes we change both to $\frac{1}{{\sqrt{N}}}$.

Discrete Fourier Transform is still a transform from time domain to frequency domain. Due to the special nature of the summation form, there are other interpretations.

If we view sequence $x_n$ as the coefficient of $x^n$ in polynomial $f(x)$, then the computed $X_k$ is exactly the value of polynomial $f(x)$ at the root of unity $\mathrm{e}^{\frac{-2\pi \mathrm{i}k}{N}}$, i.e., $f(\mathrm{e}^{\frac{-2\pi \mathrm{i}k}{N}})$.

This provides another interpretation of the convolution theorem—that is, performing a special evaluation operation on polynomials. Discrete Fourier Transform is exactly evaluating polynomials at roots of unity.

For example, computing:

$$
\dbinom{n}{3}+\dbinom{n}{7}+\dbinom{n}{11}+\dbinom{n}{15}+\ldots
$$

Define function $f(x)$:

$$
f(x)={(1+x)}^n=\dbinom{n}{0}x^0+\dbinom{n}{1}x^1+\dbinom{n}{2}x^2+\dbino

m{n}{3}x^3+\ldots
$$

Then we can find that substituting the fourth root of unity $f(\mathrm{i})$ gives such a sequence:

$$
f(\mathrm{i})={(1+\mathrm{i})}^n=\dbinom{n}{0}+\dbinom{n}{1}\mathrm{i}-\dbinom{n}{2}-\dbinom{n}{3}\mathrm{i}+\ldots
$$

So the following summation can exactly cancel out the other terms:

$$
f(1)+\mathrm{i}f(\mathrm{i})-f(-1)-\mathrm{i}f(-\mathrm{i})=4\dbinom{n}{3}+4\dbinom{n}{7}+4\dbinom{n}{11}+4\dbinom{n}{15}+\ldots
$$

Therefore, the answer to this math problem is:

$$
\dbinom{n}{3}+\dbinom{n}{7}+\dbinom{n}{11}+\dbinom{n}{15}+\ldots=\frac{2^n+\mathrm{i}(1+\mathrm{i})^n-\mathrm{i}(1-\mathrm{i})^n}{4}
$$

This math problem, by evaluating at roots of unity, exactly constitutes Discrete Fourier Transform.

### Matrix Form

Since Discrete Fourier Transform is a **linear** operator, it can be described by matrix multiplication. In matrix representation, Discrete Fourier Transform is expressed as:

$$
\begin{bmatrix}
    X_{0}  \\
    X_{1}  \\
    X_{2}  \\
    \vdots \\
    X_{N-1}
\end{bmatrix}
=
\begin{bmatrix}
    1      & 1            & 1               & \cdots & 1                   \\
    1      & \alpha       & \alpha^{2}      & \cdots & \alpha^{N-1}        \\
    1      & \alpha^{2}   & \alpha^{4}      & \cdots & \alpha^{2(N-1)}     \\
    \vdots & \vdots       & \vdots          & \ddots & \vdots              \\
    1      & \alpha^{N-1} & \alpha^{2(N-1)} & \cdots & \alpha^{(N-1)(N-1)}
\end{bmatrix}
\begin{bmatrix}
    x_{0}  \\
    x_{1}  \\
    x_{2}  \\
    \vdots \\
    x_{N-1}
\end{bmatrix}
$$

Where $\alpha = \mathrm{e}^{-\mathrm{i}\frac{2\pi}{N}}$.

## Fast Fourier Transform

FFT is an efficient algorithm for implementing DFT, called Fast Fourier Transform. It doesn't make new discoveries about the theory of Fourier Transform, but it's a huge step forward for applying Discrete Fourier Transform in computer systems or digital systems. Fast Number-Theoretic Transform (NTT) is the implementation of Fast Fourier Transform (FFT) based on number theory.

In 1965, Cooley and Tukey published the Fast Fourier Transform algorithm. In fact, FFT was discovered even earlier than this, but at that time modern computers hadn't been invented, and people didn't realize the importance of FFT. Some investigators think FFT was discovered by Runge and König in 1924. But in fact, Gauss invented this algorithm as early as 1805 but never published it.

### Divide-and-Conquer Implementation

The basic idea of the FFT algorithm is divide-and-conquer. For DFT, it uses divide-and-conquer to compute the value of $f(x)$ when $x=\omega_n^k$. The divide-and-conquer idea of radix-2 FFT is reflected in dividing the polynomial into odd and even terms.

For example, for a polynomial with 8 terms:

$$
f(x) = a_0 + a_1x + a_2x^2+a_3x^3+a_4x^4+a_5x^5+a_6x^6+a_7x^7
$$

Divide by parity of degree into two groups, then extract an $x$ from the right:

$$
\begin{aligned}
f(x) &= (a_0+a_2x^2+a_4x^4+a_6x^6) + (a_1x+a_3x^3+a_5x^5+a_7x^7)\\
     &= (a_0+a_2x^2+a_4x^4+a_6x^6) + x(a_1+a_3x^2+a_5x^4+a_7x^6)
\end{aligned}
$$

Create new functions from the odd and even terms:

$$
\begin{aligned}
G(x) &= a_0+a_2x+a_4x^2+a_6x^3\\
H(x) &= a_1+a_3x+a_5x^2+a_7x^3
\end{aligned}
$$

Then $f(x)$ can be expressed in terms of the new functions:

$$
f(x)=G\left(x^2\right) + x \times H\left(x^2\right)
$$

Using the property of even-order roots of unity $\omega^i_n = -\omega^{i + n/2}_n$, and that $G\left(x^2\right)$ and $H\left(x^2\right)$ are even functions, we know that on the complex plane, $\omega^i_n$ and $\omega^{i+n/2}_n$ have the same values for $G(x^2)$ and $H(x^2)$. We get:

$$
\begin{aligned}
f(\omega_n^k) &= G((\omega_n^k)^2) + \omega_n^k \times H((\omega_n^k)^2) \\
               &= G(\omega_n^{2k}) + \omega_n^k \times H(\omega_n^{2k}) \\
               &= G(\omega_{n/2}^k) + \omega_n^k \times H(\omega_{n/2}^k)
\end{aligned}
$$

And:

$$
\begin{aligned}
f(\omega_n^{k+n/2}) &= G(\omega_n^{2k+n}) + \omega_n^{k+n/2} \times H(\omega_n^{2k+n}) \\
                     &= G(\omega_n^{2k}) - \omega_n^k \times H(\omega_n^{2k}) \\
                     &= G(\omega_{n/2}^k) - \omega_n^k \times H(\omega_{n/2}^k)
\end{aligned}
$$

Thus, after finding $G(\omega_{n/2}^k)$ and $H(\omega_{n/2}^k)$, we can simultaneously find $f(\omega_n^k)$ and $f(\omega_n^{k+n/2})$. So we recursively perform DFT on $G$ and $H$ separately.

Considering that the polynomial length that divide-and-conquer DFT can handle can only be $2^m(m \in \mathbf{N}^ \ast )$, otherwise during divide-and-conquer the left and right have different lengths and the right cannot get coefficients. So before the first DFT, we need to pad the sequence up to a polynomial of length $2^m(m \in \mathbf{N}^ \ast )$ (fill high-degree coefficients with $0$), with highest degree $2^m-1$.

When substituting values, because we need to substitute $n$ different values, we substitute $\omega_n^0,\omega_n^1,\omega_n^2,\cdots, \omega_n^{n-1} (n=2^m(m \in \mathbf{N}^ \ast ))$, a total of $2^m$ different values.

In terms of code implementation, STL provides a complex number template, or we can implement it manually. The difference is that using STL's `complex` can call the `exp` function to find $\omega_n$. But in fact, using the imaginary number obtained from Euler's formula to find $\omega_n$ is equivalent.

This is the introduction of DFT in the FFT algorithm, which transforms a polynomial from coefficient representation to point-value representation.

It is worth noting that because it's a complex root of unity, we need to fill the high positions of the $n$-term polynomial with zeros, making $n = 2 ^ k, k \in \mathbf{N}^ \ast$.

???+ note "Recursive FFT"
    ```cpp
    #include <cmath>
    #include <complex>
    
    using Comp = std::complex<double>;  // STL complex
    
    constexpr Comp I(0, 1);  // i
    constexpr int MAX_N = 1 << 20;
    
    Comp tmp[MAX_N];
    
    // rev=1, DFT; rev=-1, IDFT
    // After applying this function, pay attention to handling normalization coefficients
    void DFT(Comp* f, int n, int rev) {
      if (n == 1) return;
      for (int i = 0; i < n; ++i) tmp[i] = f[i];
      // Put even on left, odd on right
      for (int i = 0; i < n; ++i) {
        if (i & 1)
          f[n / 2 + i / 2] = tmp[i];
        else
          f[i / 2] = tmp[i];
      }
      Comp *g = f, *h = f + n / 2;
      // Recursive DFT
      DFT(g, n / 2, rev), DFT(h, n / 2, rev);
      // cur is the current complex root. For k = 0, its corresponding complex root is omega^0_n = 1.
      // step is the difference between two complex roots, i.e., omega^k_n = step*omega^{k-1}*n,
      // defined equivalently as exp(I*(-2*M_PI/n*rev))
      Comp cur(1, 0), step(cos(2 * M_PI / n), sin(-2 * M_PI * rev / n));
      for (int k = 0; k < n / 2;
           ++k) {  // F(omega^k_n) = G(omega^k*{n/2}) + omega^k*n*H(omega^k*{n/2})
        tmp[k] = g[k] + cur * h[k];
        // F(omega^{k+n/2}*n) = G(omega^k*{n/2}) - omega^k_n*H(omega^k\_{n/2})
        tmp[k + n / 2] = g[k] - cur * h[k];
        cur *= step;
      }
      for (int i = 0; i < n; ++i) f[i] = tmp[i];
    }
    ```

Time complexity $O(n\log n)$.

### Doubling Implementation

This algorithm can continue to be optimized from the "divide-and-conquer" perspective. For radix-2 FFT, each time we separate the odd and even degree coefficients of the entire polynomial until only one coefficient remains. However, this recursive process requires more memory. Therefore, we can first "mimic recursion" to "split" these coefficients in the original array, and then "double" to merge these computed values.

For "splitting", bit-reversal permutation can be used.

For "merging", butterfly operation optimization can achieve $O(1)$ extra space to complete.

#### Bit-Reversal Permutation

Taking an 8-term polynomial as an example, simulate the splitting process:

-   Initial sequence: $\{x_0, x_1, x_2, x_3, x_4, x_5, x_6, x_7\}$
-   After first halving: $\{x_0, x_2, x_4, x_6\},\{x_1, x_3, x_5, x_7 \}$
-   After second halving: $\{x_0,x_4\} \{x_2, x_6\},\{x_1, x_5\},\{x_3, x_7 \}$
-   After third halving: $\{x_0\}\{x_4\}\{x_2\}\{x_6\}\{x_1\}\{x_5\}\{x_3\}\{x_7 \}$

The rule: actually, for the original sequence, represent each number in binary, then flip the binary symmetrically—that's the final position index. For example, $x_1$ is 001, flipped is 100, which is 4, and indeed the final position is 4. We call this transformation bit-reversal permutation. The proof is left to the reader.

According to its definition, we can find the result after transformation for each number in $O(n)$ time:

???+ note "Bit-Reversal Permutation Implementation ($O(n)$)"
    ```cpp
    /*
     * Perform inverse transformation before FFT and IFFT
     * Position i and position with binary reversal of i swap
     * len must be a power of 2
     */
    void change(Complex y[], int len) {
      // At first i is 0...01, j is 10...0, which are opposites in binary.
      // Then i gradually increases by 1, while j remains opposite to i.
      // Until i = 1...11.
      for (int i = 1, j = len / 2, k; i < len - 1; i++) {
        // Swap elements that are reverses of each other. i < j ensures each pair is swapped once.
        if (i < j) swap(y[i], y[j]);
        // i does normal +1, j does reverse-type +1, always keeping i and j reversed.
        // Here k represents the highest bit of 0. j first subtracts the number with all high bits as 1,
        // until it encounters 0, then adds it back.
        // Consider the number of bit flips in j. The highest bit flips n times,
        // second highest flips n/2 times, and so on. So time complexity is:
        // T(n) = n + n/2 + n/4 + ... = O(n)
        k = len / 2;
        while (j >= k) {
          j = j - k;
          k = k / 2;
        }
        j += k;
      }
    }
    ```

Bit-reversal permutation can also be implemented in $O(n)$ from small to large. Let $len=2^k$, where $k$ is the length of binary numbers. Let $R(x)$ be the number obtained by reversing binary $x$ of length $k$ (high bits filled with $0$). We want to find $R(0),R(1),\cdots,R(n-1)$.

First, $R(0)=0$.

We find $R(x)$ from small to large. So when finding $R(x)$, the value of $R\left(\left\lfloor \dfrac{x}{2} \right\rfloor\right)$ is known. So we shift $x$ right by one bit (divide by 2), then reverse, then shift right by one bit again, which gives the result of flipping all bits **except the (binary) units place** of $x$.

Consider the result of flipping the units place: if the units place is $0$, after flipping, the highest bit is $0$. If the units place is $1$, after flipping, the highest bit is $1$, so we need to add $\dfrac{len}{2}=2^{k-1}$. In summary:

$$
R(x)=\left\lfloor \frac{R\left(\left\lfloor \frac{x}{2} \right\rfloor\right)}{2} \right\rfloor + (x\bmod 2)\times \frac{len}{2}
$$

As an example: let $k=5$, $len=(100000)_2$. To flip $(11001)_2$:

1.  Consider $(1100)_2$, we know $R((1100)_2)=R((01100)_2)=(00110)_2)$, then shift right by one bit to get $(00011)_2$.
2.  Consider the units place, if it's $1$, it flips to the highest bit of the number, i.e., add $(10000)_2=2^{k-1}$; if it's $0$, no change needed.

???+ note "Bit-Reversal Permutation Implementation ($O(n)$)"
    ```cpp
    // Also ensure len is a power of 2
    // rev[i] is the reversed value of i
    void change(Complex y[], int len) {
      for (int i = 0; i < len; ++i) {
        rev[i] = rev[i >> 1] >> 1;
        if (i & 1) {  // If the last bit is 1, flip to len/2
          rev[i] |= len >> 1;
        }
      }
      for (int i = 0; i < len; ++i) {
        if (i < rev[i]) {  // Ensure each pair is swapped only once
          swap(y[i], y[rev[i]]);
        }
      }
      return;
    }
    ```

#### Butterfly Operation Optimization

After knowing $G(\omega_{n/2}^k)$ and $H(\omega_{n/2}^k)$, we need to use the following two formulas to find $f(\omega_n^k)$ and $f(\omega_n^{k+n/2})$:

$$
\begin{aligned}
    f(\omega_n^k)       & = G(\omega_{n/2}^k) + \omega_n^k \times H(\omega_{n/2}^k) \\
    f(\omega_n^{k+n/2}) & = G(\omega_{n/2}^k) - \omega_n^k \times H(\omega_{n/2}^k)
\end{aligned}
$$

After using bit-reversal permutation, for given $n, k$:

-   The value of $G(\omega_{n/2}^k)$ is stored at array index $k$, and $H(\omega_{n/2}^k)$ is stored at index $k + \dfrac{n}{2}$.
-   The value of $f(\omega_n^k)$ will be stored at index $k$, and $f(\omega_n^{k+n/2})$ will be stored at index $k + \dfrac{n}{2}$.

Therefore, we can directly overwrite at indices $k$ and $k + \frac{n}{2}$ without opening extra arrays to save values. This method is called **butterfly operation**, or more precisely, radix-2 butterfly operation.

Let's describe how to complete all merge operations of segment length $\frac{n}{2}$ with butterfly operation:

1.  Let segment length be $s = \frac{n}{2}$;
2.  Simultaneously enumerate left endpoints $l_g = 0, 2s, 4s, \cdots, N-2s$ of sequence $\{G(\omega_{n/2}^k)\}$ and left endpoints $l_h = s, 3s, 5s, \cdots, N-s$ of sequence $\{H(\omega_{n/2}^k)\}$;
3.  When merging two segments, enumerate $k = 0, 1, 2, \cdots, s-1$. At this time, $G(\omega_{n/2}^k)$ is stored at index $l_g + k$, and $H(\omega_{n/2}^k)$ is stored at index $l_h + k$;
4.  Use butterfly operation to find $f(\omega_n^k)$ and $f(\omega_n^{k+n/2})$, then directly overwrite in place.

## Inverse Fast Fourier Transform

Inverse Fourier transform can be expressed using Fourier transform. We have two ways to understand this.

### Linear Algebra Perspective

IDFT (Fourier inverse transform) is to convert the point-value form of the target polynomial to coefficient form. DFT itself is a linear transform, which can be understood as multiplying the target polynomial as a vector by a matrix to get the transformed vector, to simulate substituting the unit complex root into the polynomial:

$$
\begin{bmatrix}y_0 \\ y_1 \\ y_2 \\ y_3 \\ \vdots \\ y_{n-1} \end{bmatrix}
=
\begin{bmatrix}1 & 1 & 1 & 1 & \cdots & 1 \\
1 & \omega_n^1 & \omega_n^2 & \omega_n^3 & \cdots & \omega_n^{n-1} \\
1 & \omega_n^2 & \omega_n^4 & \omega_n^6 & \cdots & \omega_n^{2(n-1)} \\
1 & \omega_n^3 & \omega_n^6 & \omega_n^9 & \cdots & \omega_n^{3(n-1)} \\
\vdots & \vdots & \vdots & \vdots & \ddots & \vdots \\
1 & \omega_n^{n-1} & \omega_n^{2(n-1)} & \omega_n^{3(n-1)} & \cdots & \omega_n^{(n-1)^2} \end{bmatrix}
\begin{bmatrix} a_0 \\ a_1 \\ a_2 \\ a_3 \\ \vdots \\ a_{n-1} \end{bmatrix}
$$

Now we have obtained the leftmost result. The middle $x$ values also correspond one-to-one in the point-value representation of the target polynomial. So, according to basic matrix knowledge, we just need to multiply the inverse matrix of the large matrix in the middle on both sides.

Since the elements of this matrix are very special, its inverse matrix also has special properties: each element **takes the reciprocal**, then **divides by the transform length $n$**, which gives its inverse matrix.

Note: The length of the Fourier transform is not the length of the polynomial. The transform length should be longer than the product polynomial length. If the polynomials to be multiplied are not long enough, we need to fill $0$ in high-order positions.

To make the result become the original reciprocal, according to Euler's formula, we can get:

$$
\frac{1}{\omega_k}=\omega_k^{-1}=\mathrm{e}^{-\frac{2\pi \mathrm{i}}{k}}=\cos\left(\frac{2\pi}{k}\right)+\mathrm{i} \sin\left(-\frac{2\pi}{k}\right)
$$

Therefore, we can try to take the root of unity as $\mathrm{e}^{-\frac{2\pi \mathrm{i}}{k}}$, so our calculation result will become the original reciprocal, and then the only extra operation is to **divide by its length $n$**, while all other operations are exactly the same as DFT. We can define a function with a parameter $1$ or $-1$ and multiply it by $\pi$. Passing $1$ is DFT, passing $-1$ is IDFT.

### Periodicity of Complex Roots of Unity

IDFT's relationship with DFT can also be understood using the periodicity of complex roots of unity.

Consider the original polynomial $f(x)=a_0+a_1x+a_2x^2+\cdots+a_{n-1}x^{n-1}=\sum_{i=0}^{n-1}a_ix^i$. And IDFT is to restore your point-value representation to coefficient representation.

Consider **construction method**. We know $y_i=f\left( \omega_n^i \right),i\in\{0,1,\cdots,n-1\}$, find $\{a_0,a_1,\cdots,a_{n-1}\}$. Construct the polynomial:

$$
A(x)=\sum_{i=0}^{n-1}y_ix^i
$$

This is equivalent to treating $\{y_0,y_1,2,\cdots,y_{n-1}\}$ as the coefficient representation of polynomial $A$.

Now we have two derivation methods, which correspond to two implementation methods.

#### Method 1

Let $b_i=\omega_n^{-i}$, then the point-value representation of polynomial $A$ at $x=b_0,b_1,\cdots,b_{n-1}$ is $\{ A(b_0),A(b_1),\cdots,A(b_{n-1}) \}$.

Doing some transformation on the definition of $A(x)$, we can express $A(b_k)$ as:

$$
\begin{aligned}
A(b_k)&=\sum_{i=0}^{n-1}f(\omega_n^i)\omega_n^{-ik}=\sum_{i=0}^{n-1}\omega_n^{-ik}\sum_{j=0}^{n-1}a_j(\omega_n^i)^{j}\\
&=\sum_{i=0}^{n-1}\sum_{j=0}^{n-1}a_j\omega_n^{i(j-k)}=\sum_{j=0}^{n-1}a_j\sum_{i=0}^{n-1}\left(\omega_n^{j-k}\right)^i\\
\end{aligned}
$$

Let $S\left(\omega_n^a\right)=\sum_{i=0}^{n-1}\left(\omega_n^a\right)^i$.

When $a=0 \pmod{n}$, $S\left(\omega_n^a\right)=n$.

When $a\neq 0 \pmod{n}$, we subtract term by term:

$$
\begin{aligned}
S\left(\omega_n^a\right)&=\sum_{i=0}^{n-1}\left(\omega_n^a\right)^i\\
\omega_n^a S\left(\omega_n^a\right)&=\sum_{i=1}^{n}\left(\omega_n^a\right)^i\\
S\left(\omega_n^a\right)&=\frac{\left(\omega_n^a\right)^n-\left(\omega_n^a\right)^0}{\omega_n^a-1}=0\\
\end{aligned}
$$

That is:

$$
S\left(\omega_n^a\right)=
\begin{cases}
n,&a=0\\
0,&a\neq 0
\end{cases}
$$

Then substitute back:

$$
A(b_k)=\sum_{j=0}^{n-1}a_jS\left(\omega_n^{j-k}\right)=a_k\cdot n
$$

That is, given point $b_i=\omega_n^{-i}$, the point-value representation of $A$ is:

$$
\begin{aligned}
&\left\{ (b_0,A(b_0)),(b_1,A(b_1)),\cdots,(b_{n-1},A(b_{n-1})) \right\}\\
=&\left\{ (b_0,a_0\cdot n),(b_1,a_1\cdot n),\cdots,(b_{n-1},a_{n-1}\cdot n) \right\}
\end{aligned}
$$

In summary, we take the root of unity as its reciprocal, run FFT on $\{y_0,y_1,2,\cdots,y_{n-1}\}$, then divide by $n$ to get the coefficient representation of $f(x)$.

#### Method 2

We directly substitute $\omega_n^i$ into $A(x)$.

The derivation process is similar to method one. Finally, we get $A(\omega_n^k) = \sum_{j=0}^{n-1}a_jS\left(\omega_n^{j+k}\right)$.

Only when $j+k=0 \pmod{n}$ does $S\left(\omega_n^{j+k}\right) = n$, otherwise it is $0$. So $A(\omega_n^k) = a_{n-k}\cdot n$.

This means after doing DFT transform on $\{y_0,y_1,2,\cdots,y_{n-1}\}$ and dividing by $n$, then reversing the last $n-1$ elements, we can also restore the coefficient representation of $f(x)$.

### Code Implementation

So our FFT function can integrate DFT and IDFT. The code is as follows:

???+ note "Non-Recursive FFT (corresponding to method one)"
    ```cpp
    /*
     * Do FFT
     * len must be of the form 2^k
     * on == 1 is DFT, on == -1 is IDFT
     */
    void fft(Complex y[], int len, int on) {
      // Bit-reversal permutation
      change(y, len);
      // Simulate merging process. First merge from length 1 to length 2, all the way to length len.
      for (int h = 2; h <= len; h <<= 1) {
        // wn: current complex root spacing: w^1_h
        Complex wn(cos(2 * PI / h), sin(on * 2 * PI / h));
        // Merge, len/h times.
        for (int j = 0; j < len; j += h) {
          // Compute current complex root. Initially it's 1 = w^0_n, then increases by wn as interval: w^1_n
          // ...
          Complex w(1, 0);
          for (int k = j; k < j + h / 2; k++) {
            // Left part and right part are solutions to sub-problems
            Complex u = y[k];
            Complex t = w * y[k + h / 2];
            // This is adding the results of the two parts of divide-and-conquer
            y[k] = u + t;
            y[k + h / 2] = u - t;
            // In the latter half of "step", ω is definitely opposite to that in the former half.
            // Points on the "red circle" rotate one full circle "back", half a circle becomes opposite.
            // The square of the opposite of a number equals the square of the number itself.
            w = w * wn;
          }
        }
      }
      // If it's IDFT, each element of its inverse matrix is not only the reciprocal of the original element but also divided by length len.
      if (on == -1) {
        for (int i = 0; i < len; i++) {
          y[i].x /= len;
          y[i].y /= len;
        }
      }
    }
    ```

???+ note "Non-Recursive FFT (corresponding to method two)"
    ```cpp
    /*
     * Do FFT
     * len must be of the form 2^k
     * on == 1 is DFT, on == -1 is IDFT
     */
    void fft(Complex y[], int len, int on) {
      change(y, len);
      for (int h = 2; h <= len; h <<= 1) {             // Simulate merging process
        Complex wn(cos(2 * PI / h), sin(2 * PI / h));  // Compute current complex root
        for (int j = 0; j < len; j += h) {
          Complex w(1, 0);  // Compute current complex root
          for (int k = j; k < j + h / 2; k++) {
            Complex u = y[k];
            Complex t = w * y[k + h / 2];
            y[k] = u + t;  // This is adding the results of the two parts of divide-and-conquer
            y[k + h / 2] = u - t;
            // In the latter half of "step", ω is definitely opposite to that in the former half.
            // Points on the "red circle" rotate one full circle "back", half a circle becomes opposite.
            // The square of the opposite of a number equals the square of the number itself.
            w = w * wn;
          }
        }
      }
      if (on == -1) {
        reverse(y + 1, y + len);
        for (int i = 0; i < len; i++) {
          y[i].x /= len;
          y[i].y /= len;
        }
      }
    }
    ```

??? note "FFT Template ([HDU 1402 - A * B Problem Plus](http://acm.hdu.edu.cn/showproblem.php?pid=1402))"
    ```cpp
    --8<-- "docs/math/code/poly/fft/fft_3.cpp"
    ```

## References

1.  [Peach Sauce's Algorithm Notes](https://zhuanlan.zhihu.com/p/41867199).