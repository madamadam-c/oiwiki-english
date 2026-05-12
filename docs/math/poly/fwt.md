author: Xeonacid, nocriz, ZnPdCo

## Introduction

Walsh Transform[^note1] is a method used as an alternative to discrete Fourier transform in spectrum analysis, widely used in signal processing. FFT uses double type, but Walsh decomposes the signal under different oscillating frequency square waves, so all coefficients are integers of the same absolute value, which eliminates the need for floating-point multiplication and improves computation speed.

Therefore, the core idea of FWT and FFT should be the same—they both transform an array. We denote the result of performing fast Walsh transform on array $A$ as $FWT[A]$.

The core idea of FWT is:

We need a new sequence $C$, obtained from sequence $A$ and sequence $B$ through some operation rule, i.e., $C = A \cdot B$;

We first forward-transform to get $FWT[A], FWT[B]$, then according to $FWT[C]=FWT[A] \cdot FWT[B]$, we compute $FWT[C]$ in $O(n)$ time complexity, where $\cdot$ is element-wise multiplication;

Then we perform inverse transformation to get the original sequence $C$. Time complexity is $O(n \log{n})$.

In algorithm competitions, FWT is used to solve convolution problems with bitwise operations on indices.

Formula: $C_{i} = \sum_{i=j \oplus k}A_{j} B_{k}$

(Where $\oplus$ is some binary bitwise operation)

Below we give examples using $\cup$ (bitwise OR), $\cap$ (bitwise AND), and $\oplus$ (bitwise XOR).

## FWT Operations

### OR Operation

If $k=i\cup j$, then the positions where $i$'s binary has 1 and the positions where $j$'s binary has 1 must be a subset of the positions where $k$'s binary has 1.

Now to get $FWT[C] = FWT[A] \cdot FWT[B]$, we need to construct the rule for this FWT.

According to the definition, we can construct $FWT[A]_i = A'_i = \sum_{i=i\cup j}A_{j}$, representing $j$ whose binary 1s are a subset of $i$'s 1s.

Then:

$$
\begin{aligned}
FWT[A]_i\cdot FWT[B]_i&=\left(\sum_{i\cup j=i} A_j\right)\left(\sum_{i\cup k=i} B_k\right) \\
&=\sum_{i\cup j=i}\sum_{i\cup k=i}A_jB_k \\
&=\sum_{i\cup(j\cup k)=i}A_jB_k \\
&= FWT[C]_i
\end{aligned}
$$

Now let's see how to compute $FWT[A]$.

Enumerate would be too slow, with complexity $O(n^2)$. Since we can't enumerate all at once, consider divide-and-conquer.

We bisect the entire interval. After bisecting, there is a pattern when writing indices in binary.

Let $A_0$ represent the first half of $A$, and $A_1$ the second half. $A_0$ is the set of indices whose highest bit is 0—its subset is itself (since the highest bit is 0). But $A_1$'s highest bit is 1; the subsets that satisfy the condition are not only itself but also those with the highest bit as 0:

$$
FWT[A] = merge(FWT[A_0], FWT[A_0] + FWT[A_1])
$$

Where merge concatenates two arrays like string concatenation, and $+$ is ordinary addition, representing adding corresponding binary digits.

This way, we can complete the concatenation in $O(\log{n})$ time through bisection, and each concatenation requires one operation, so we get $FWT[A]$ in $O(n\log{n})$ time.

Now for inversion. Since we know $A_0$'s subsets are itself ($A_0 = FWT[A_0]$), and $A_1$'s subsets are $FWT[A_0] + FWT[A_1]$, we can easily derive the inversion recurrence:

$$
UFWT[A'] = merge(UFWT[A_0'], UFWT[A_1'] - UFWT[A_0'])
$$

Below we give the code implementation. It is easy to find that forward and inverse transforms can be merged into one function, with $\text{type}=1$ for forward transform and $\text{type}=-1$ for inverse transform.

???+ note "Implementation"
    ```cpp
    void Or(ll *a, ll type) {  // Iterative implementation, smaller constant
      for (ll x = 2; x <= n; x <<= 1) {
        ll k = x >> 1;
        for (ll i = 0; i < n; i += x) {
          for (ll j = 0; j < k; j++) {
            (a[i + j + k] += a[i + j] * type) %= P;
          }
        }
      }
    }
    ```

### AND Operation

By analogy with OR operation, we can get similar conclusions:

$$
FWT[A] = merge(FWT[A_0] + FWT[A_1], FWT[A_1])
$$

$$
UFWT[A'] = merge(UFWT[A_0'] - UFWT[A_1'], UFWT[A_1'])
$$

Below we give the code implementation. Forward transform uses $\text{type}=1$, inverse uses $\text{type}=-1$.

???+ note "Implementation"
    ```cpp
    void And(ll *a, ll type) {
      for (ll x = 2; x <= n; x <<= 1) {
        ll k = x >> 1;
        for (ll i = 0; i < n; i += x) {
          for (ll j = 0; j < k; j++) {
            (a[i + j] += a[i + j + k] * type) %= P;
          }
        }
      }
    }
    ```

### XOR Operation

XOR convolution is based on the following principle:

If we let $x\circ y$ represent the parity of the number of 1s in $x\cap y$, i.e., $x\circ y=\text{popcnt}(x\cap y)\bmod 2$, then it's easy to have $(x\circ y)\oplus (x\circ z)=x\circ(y\oplus z)$.

The computation of $FWT[A]$ is also easy to obtain.

Let $FWT[A]_i=\sum_{i\circ j=0}A_j-\sum_{i\circ j=1}A_j$. Let's prove the correctness of $FWT[C] = FWT[A] \cdot FWT[B]$:

$$
\begin{aligned}
FWT[A]_iFWT[B]_i&=\left(\sum_{i\circ j=0}A_j-\sum_{i\circ j=1}A_j\right)\left(\sum_{i\circ k=0}B_k-\sum_{i\circ k=1}B_k\right) \\
&=\left(\sum_{i\circ j=0}A_j\sum_{i\circ k=0}B_k+\sum_{i\circ j=1}A_j\sum_{i\circ k=1}B_k\right)-\left(\sum_{i\circ j=0}A_j\sum_{i\circ k=1}B_k+\sum_{i\circ j=1}A_j\sum_{i\circ k=0}B_k\right) \\
&=\sum_{(j\oplus k)\circ i=0}A_jB_k-\sum_{(j\oplus k)\circ i=1}A_jB_k \\
&=FWT[C]_i
\end{aligned}
$$

Let's see how to quickly compute the values of $A,B$, still using divide-and-conquer:

For subsequence $FWT[A_0]$ where $i$'s current bit is 0, when performing $\circ$ operations, we find that computing with 0 and 1 both yield the same result (because $0\cap 0=0,0\cap1=0$), so in $FWT[A]=\sum_{i\circ j=0}A_j-\sum_{i\circ j=1}A_j$, we have $\sum_{i\circ j=1}A_j=0$.

For subsequence $A_1$ where $i$'s current bit is 1, when performing $\circ$ operations, we find that computing with 0 yields 0 and with 1 yields 1 (because $1\cap 0=0,1\cap1=1$).

In summary:

$$
FWT[A]=merge((FWT[A_0]+FWT[A_1])-0, FWT[A_0]-FWT[A_1])
$$

That is:

$$
FWT[A] = merge(FWT[A_0] + FWT[A_1], FWT[A_0] - FWT[A_1])
$$

The inverse is easy to obtain:

$$
UFWT[A'] = merge(\frac{UFWT[A_0'] + UFWT[A_1']}{2}, \frac{UFWT[A_0'] - UFWT[A_1']}{2})
$$

Here is the code: forward transform uses $\text{type}=1$, inverse uses $\text{type}=\frac{1}{2}$.

???+ note "Implementation"
    ```cpp
    void Xor(ll *a, ll type) {
      for (ll x = 2; x <= n; x <<= 1) {
        ll k = x >> 1;
        for (ll i = 0; i < n; i += x) {
          for (ll j = 0; j < k; j++) {
            (a[i + j] += a[i + j + k]) %= P;
            (a[i + j + k] = a[i + j] - a[i + j + k] * 2) %= P;
            (a[i + j] *= type) %= P;
            (a[i + j + k] *= type) %= P;
          }
        }
      }
    }
    ```

### XNOR Operation

By analogy with XOR operation, give the formula:

$FWT[A]_{i} = \sum_{C_1}A_{j} - \sum_{C_2}A_{j}$ ($C_1$ means $\text{popcnt}(x\cup y)\bmod 2$ is $0$, $C_2$ means $\text{popcnt}(x\cup y)\bmod 2$ is $1$)

$$
FWT[A] = merge(FWT[A_1] - FWT[A_0], FWT[A_1] + FWT[A_0])
$$

$$
UFWT[A'] = merge(\frac{UFWT[A_1'] - UFWT[A_0']}{2}, \frac{UFWT[A_1'] + UFWT[A_0']}{2})
$$

## FWT from Another Perspective

Let $c(i,j)$ be the contribution coefficient of $A_j$ to $FWT[A]_i$. We can describe the FWT transformation process as:

$$
FWT[A]_i = \sum_{j=0}^{n-1} c(i,j) A_j
$$

Because we have:

$$
FWT[A]_i\cdot FWT[B]_i=FWT[C]_i
$$

So we can easily prove: $c(i,j)c(i,k)=c(i,j\odot k)$. Where $\odot$ is any bitwise operation.

Also, the $c$ function has an important property—it can be processed bit by bit.

For example, when transforming:

$$
FWT[A]_i = \sum_{j=0}^{n-1} c(i,j) A_j
$$

This is not efficient. Let's split it:

$$
FWT[A]_i = \sum_{j=0}^{n/2-1} c(i,j) A_j+\sum_{j=n/2}^{n-1} c(i,j) A_j
$$

Considering the difference between the front and back parts of the formula for $i,j$, we find only the highest bit differs.

So we remove the highest bit from $i,j$, get $i',j'$, and denote $i_0$ as the highest bit of $i$:

$$
FWT[A]_i = c(i_0,0)\sum_{j=0}^{n/2-1} c(i',j') A_j+c(i_0,1)\sum_{j=n/2}^{n-1} c(i',j') A_j
$$

If $i_0=0$:

$$
FWT[A]_i = c(0,0)\sum_{j=0}^{n/2-1} c(i',j') A_j+c(0,1)\sum_{j=n/2}^{n-1} c(i',j') A_j
$$

If $i_0=1$:

$$
FWT[A]_i = c(1,0)\sum_{j=0}^{n/2-1} c(i',j') A_j+c(1,1)\sum_{j=n/2}^{n-1} c(i',j') A_j
$$

That is, we only need these four numbers:

$$
\begin{bmatrix}
c(0,0) & c(0,1) \\
c(1,0) & c(1,1)
\end{bmatrix}
$$

We call this matrix the bit matrix.

If we want to perform inverse transformation, we need the inverse matrix of the above bit matrix.

If the inverse matrix is $c^{-1}$, we can get the original numbers through similar operations:

$$
A_i = \sum_{j=0}^n c^{-1}(i,j) FWT[A]_j
$$

The inverse matrix may not exist—for example, if there is a row of 0 or a column of 0, the matrix has no inverse. We need to be careful when constructing.

### Bitwise OR

We can construct:

$$
\begin{bmatrix}
1 & 0 \\
1 & 1
\end{bmatrix}
$$

This satisfies $c(i,j)c(i,k)=c(i,j\cup k)$. We found this is exactly the same as $FWT[A]=\text{merge}(FWT[A_0], FWT[A_0]+FWT[A_1])$ derived earlier! Similarly, below is also a matrix satisfying this condition, but we generally use the above one:

$$
\begin{bmatrix}
1 & 1 \\
1 & 0
\end{bmatrix}
$$

Although the matrix below also satisfies $c(i,j)c(i,k)=c(i,j\cup k)$, this matrix has a row of 0, so no inverse exists and is not valid:

$$
\begin{bmatrix}
0 & 0 \\
1 & 1
\end{bmatrix}
$$

If we want to perform inverse transformation, we need to invert the matrix. Using the top matrix as example:

$$
\begin{bmatrix}
1 & 0 \\
-1 & 1
\end{bmatrix}
$$

Then substitute the inverse transformation matrix into the forward transformation method.

### Bitwise AND

We can construct:

$$
\begin{bmatrix}
1 & 1 \\
0 & 1
\end{bmatrix}
$$

This satisfies $c(i,j)c(i,k)=c(i,j\cap k)$.

Inverse matrix:

$$
\begin{bmatrix}
1 & -1 \\
0 & 1
\end{bmatrix}
$$

### Bitwise XOR

We can construct:

$$
\begin{bmatrix}
1 & 1 \\
1 & -1
\end{bmatrix}
$$

This satisfies $c(i,j)c(i,k)=c(i,j\oplus k)$.

Inverse matrix:

$$
\begin{bmatrix}
0.5 & 0.5 \\
0.5 & -0.5
\end{bmatrix}
$$

## FWT is Linear Transformation

FWT is a linear transformation. That is, it satisfies:

$$
FWT[A+B]=FWT[A]+FWT[B]
$$

And:

$$
FWT[c\cdot A]=c\cdot FWT[A]
$$

## K-Dimensional FWT

In fact, the essence of bitwise operations is operations on an $n$-dimensional $\{0,1\}$ vector. OR operation takes max for each dimension. AND operation takes min for each dimension. XOR operation adds corresponding dimensions and takes $\bmod 2$.

Bitwise operations have a characteristic: each dimension of the vector is independent.

We extend $\{0,1\}$ to $[0,K)\cap \mathbf{Z}$, that is, extend to $K$-ary. What do we get?

### Max Operation

We extend the $\cup$ operation to $K$-ary, defining $i\cup j$ as bitwise max:

$$
c(i,j)c(i,k)=c(i,j\cup k)
$$

If $j=k$, then the above is:

$$
c(i,j)c(i,j)=c(i,j)
$$

That is, in each row, 1s can only appear before 0s—if they appear after, it's invalid. Through manual exploration, we can find a valid construction:

$$
\begin{bmatrix}
1 & 0 & 0 & 0 \\
1 & 1 & 0 & 0 \\
1 & 1 & 1 & 0 \\
1 & 1 & 1 & 1
\end{bmatrix}
$$

Inverting gives:

$$
\begin{bmatrix}
1 & 0 & 0 & 0 \\
-1 & 1 & 0 & 0 \\
0 & -1 & 1 & 0 \\
0 & 0 & -1 & 1
\end{bmatrix}
$$

### Min Operation

We extend the $\cap$ operation to $K$-ary, defining $i\cap j$ as bitwise min:

$$
c(i,j)c(i,k)=c(i,j\cap k)
$$

If $j=k$, then the above is:

$$
c(i,j)c(i,j)=c(i,j)
$$

That is, in each row, 1s can only appear after 0s—if they appear before, it's invalid. Through manual exploration, we can find a valid construction:

$$
\begin{bmatrix}
1 & 1 & 1 & 1 \\
0 & 1 & 1 & 1 \\
0 & 0 & 1 & 1 \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

Inverting gives:

$$
\begin{bmatrix}
1 & -1 & 0 & 0 \\
0 & 1 & -1 & 0 \\
0 & 0 & 1 & -1 \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

The first two are used less; more commonly used is:

### Non-Carry Addition

We extend the $\oplus$ operation to $K$-ary, defining $i\oplus j$ as bitwise addition then $\bmod K$:

$$
c(i,j)c(i,k)=c(i,j\oplus k)
$$

We can construct $c(i,j)=\omega_{K}^j$ to satisfy:

$$
\omega_{K}^j\omega_{K}^k=\omega_{K}^{j\oplus k}
$$

But each row is the same matrix and has no inverse. So we can construct $c(i,j)=\omega_{K}^{(i-1)j}$.

We have the matrix:

$$
\begin{bmatrix}
1 & 1 & 1 & \cdots & 1 \\
1 & \omega_{K}^1 & \omega_{K}^2 & \cdots & \omega_{K}^{k-1} \\
1 & \omega_{K}^2 & \omega_{K}^4 & \cdots & \omega_{K}^{2(k-1)} \\
1 & \omega_{K}^3 & \omega_{K}^6 & \cdots & \omega_{K}^{3(k-1)} \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
1 & \omega_{K}^{k-1} & \omega_{K}^{2(k-1)} & \cdots & \omega_{K}^{(k-1)(k-1)}
\end{bmatrix}
$$

This is a [Vandermonde matrix](https://en.wikipedia.org/wiki/Vandermonde_matrix). Inverting gives:

$$
\frac{1}{K}\begin{bmatrix}
1 & 1 & 1 & \cdots & 1 \\
1 & \omega_{K}^{-1} & \omega_{K}^{-2} & \cdots & \omega_{K}^{-(k-1)} \\
1 & \omega_{K}^{-2} & \omega_{K}^{-4} & \cdots & \omega_{K}^{-2(k-1)} \\
1 & \omega_{K}^{-3} & \omega_{K}^{-6} & \cdots & \omega_{K}^{-3(k-1)} \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
1 & \omega_{K}^{-(k-1)} & \omega_{K}^{-2(k-1)} & \cdots & \omega_{K}^{-(k-1)(k-1)}
\end{bmatrix}
$$

If the modulus given in the problem has a root of unity, we can simply implement.

But **the root of unity may not exist under the modulus**, so we consider field extension—artificially define an $x$ such that $x^K=1$, then directly substitute $x$ for computation, so each number is a polynomial of degree $k-1$ in $x$. We only need to compute under $\bmod {x^K-1}$. Then the matrix can be represented as:

$$
\begin{bmatrix}
1 & 1 & 1 & \cdots & 1 \\
1 & x^1 & x^2 & \cdots & x^{k-1} \\
1 & x^2 & x^4 & \cdots & x^{2(k-1)} \\
1 & x^3 & x^6 & \cdots & x^{3(k-1)} \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
1 & x^{k-1} & x^{2(k-1)} & \cdots & x^{(k-1)(k-1)}
\end{bmatrix}
$$

However, doing this may have zero divisors—"one number has multiple representations", so we can't determine a number's true value.

We consider not using $\bmod {x^K-1}$, but $\bmod$ the cyclotomic polynomial $\Phi_{K}(x)$, which satisfies that $x$ has order $k$ and is irreducible over $\mathbb{Q}$. So we just need the above computation under $\bmod {\Phi_{K}(x)}$.

One more issue: $\bmod \Phi_{K}(x)$ has large constants (because $\Phi$ itself is a polynomial). But since $\Phi_{K}(x)\mid x^k-1$, we only need to compute under $\bmod x^k -1$ first, then take $\bmod \Phi_{K}(x)$ at the end.

## Example Problems

???+ note "[「CF 1103E」Radix sum](https://www.luogu.com.cn/problem/CF1103E)"
    Given a sequence of length $n$: $a_1,a_2,...,a_n$, for each $p \in [0,n-1]$, find the number of integer sequences $i_1,i_2,...,i_n$ satisfying the following conditions, modulo $2^{58}$:
    
    -   $\forall j \in [1,n] , i_j \in [1,n]$;
    -   $\sum\limits_{j=1}^n a_{i_j} = p$, where this addition is defined as non-carry decimal addition.
    
    $n\le10^5,a_i\le10^5$
    
    ??? note "Solution"
        We can think of DP: design state $f_{i,s}$ to represent considering the $i$-th number and the current addition state being $s$. Since FWT transform is linear, we can first transform to FWT point-value representation, then compute its $n$-th power, and finally transform back.
        
        The above is straightforward, but the problem gives modulus $2^{58}$. It is found that there is no root of unity, so we consider field extension.
        
        Here the cyclotomic polynomial $\Phi_{10}(x)=x^4-x^3+x^2-x+1$.
        
        However, we find that during UFWT, we need to divide by base 10, but we find that 10 has no inverse under $2^{58}$. Actually, we find that 5 has an inverse under $2^{58}$: $57646075230342349$. We just need to divide by another 2. Let the answer after dividing by 5 be $x$, and the real answer be $y$, i.e., $2^5y\equiv x\pmod{2^{64}}$. Obviously, $y\equiv \frac{x}{2^5}\pmod{2^{64-5}}$, that is, $y\equiv \frac{x}{2^5}\pmod{2^{59}}$. So just divide the final answer by $2^5$. Although the problem setter didn't know why they used $2^{58}$, just take the modulus again.

???+ note "['CF103329F','XXII Opencup, Grand Prix of XiAn']The Struggle](https://codeforces.com/gym/103329/problem/F)"
    Given an ellipse $E$, where all integer points have coordinates in $[1,4 \cdot 10^6]$. Find $\sum_{(x,y) \in E} (x \oplus y)^{33}x^{-2}y^{-1} \mod 10^9+7$.
    
    ??? note "Solution"
        This is a relatively non-trivial problem. The problem setter provided a detailed English solution. See [this link](https://codeforces.com/blog/entry/96518) for details.

## References

-   [Peach Sauce's Algorithm Notes](https://zhuanlan.zhihu.com/p/41867199)
-   [ZnPdCo's Blog](https://znpdco.github.io/算法/2024/05/07/FWT.html)

[^note1]: [Wikipedia](https://zh.wikipedia.org/zh-cn/%E6%B2%83%E7%88%BE%E4%BB%8A%E8%BD%89%E6%8F%9B)