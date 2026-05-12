author: inkydragon, TravorLZH, YOYO-UIAT, wood3, shuzhouliu, Mr-Python-in-China, HeRaNO, weilycoder

## Prime Sieves

### Introduction

If we want to know how many primes are less than or equal to $n$?

A natural approach would be to perform a primality test on each number up to $n$. This brute-force approach clearly does not achieve optimal complexity.

### Sieve of Eratosthenes

#### Process

Consider the following: for any integer $n > 1$, its $x$-fold (where $x > 1$) is a composite number. Using this conclusion, we can avoid many unnecessary tests.

If we iterate through each number from smallest to largest and mark all (greater than itself) multiples of the current number as composite, then at the end of the execution, the unmarked numbers are primes.

#### Implementation

=== "C++"
    ```cpp
    vector<int> prime;
    bool is_prime[N];
    
    void Eratosthenes(int n) {
      is_prime[0] = is_prime[1] = false;
      for (int i = 2; i <= n; ++i) is_prime[i] = true;
      for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
          prime.push_back(i);
          if ((long long)i * i > n) continue;
          for (int j = i * i; j <= n; j += i)
            // Since we already sieved multiples from 2 to i - 1, 
            // we start directly from i's multiples to improve speed
            is_prime[j] = false;  // All multiples of i are not prime
        }
      }
    }
    ```

=== "Python"
    ```python
    prime = []
    is_prime = [False] * N
    
    
    def Eratosthenes(n):
        is_prime[0] = is_prime[1] = False
        for i in range(2, n + 1):
            is_prime[i] = True
        for i in range(2, n + 1):
            if is_prime[i]:
                prime.append(i)
                if i * i > n:
                    continue
                for j in range(i * i, n + 1, i):
                    is_prime[j] = False
    ```

The above is the **Sieve of Eratosthenes** (also called the Eratosthenes sieve), with time complexity $O(n\log\log n)$.

???+ note "Proof"
    Now let's examine the derivation process:
    
    If each array operation takes 1 unit of time, the time complexity is:
    
    $$
    O\left(\sum_{k=1}^{\pi(n)}{\frac{n}{p_k}}\right)=O\left(n\sum_{k=1}^{\pi(n)}{\frac{1}{p_k}}\right)
    $$
    
    Where $p_k$ denotes the $k$-th smallest prime, and $\pi(n)$ denotes the number of primes $\le n$. $\sum_{k=1}^{\pi(n)}$ represents the outer for loop, where the upper bound $\pi(n)$ is the number of times the condition `if (prime[i])` enters the true branch; $\frac{n}{p_k}$ represents the number of executions of the inner for loop.
    
    According to Mertens' second theorem, there exists a constant $B_1$ such that:
    
    $$
    \sum_{k=1}^{\pi(n)}{\frac{1}{p_k}}=\log\log n+B_1+O\left(\frac{1}{\log n}\right)
    $$
    
    Therefore, the time complexity of the **Sieve of Eratosthenes** is $O(n\log\log n)$. Next, we prove a weakened version of Mertens' second theorem $\sum_{k\le\pi(n)}1/p_k=O(\log\log n)$:
    
    According to $\pi(n)=\Theta(n/\log n)$, the size of the $n$-th prime is $\Theta(n\log n)$. Thus we have:
    
    $$
    \begin{aligned}
    \sum_{k=1}^{\pi(n)}{\frac{1}{p_k}}
    &=O\left(\sum_{k=2}^{\pi(n)}{\frac{1}{k\log k}}\right) \\
    &=O\left(\int_2^{\pi(n)}{\frac{\mathrm dx}{x\log x}}\right) \\
    &=O(\log\log\pi(n))=O(\log\log n)
    \end{aligned}
    $$
    
    Of course, the above approach is still not efficient enough; applying the following methods can slightly improve the algorithm's execution efficiency.

#### Sieve up to square root

Obviously, to find all primes up to $n$, it suffices to sieve only primes up to $\sqrt n$.

=== "C++"
    ```cpp
    vector<int> prime;
    bool is_prime[N];
    
    void Eratosthenes(int n) {
      is_prime[0] = is_prime[1] = false;
      for (int i = 2; i <= n; ++i) is_prime[i] = true;
      // i * i <= n means i <= sqrt(n)
      for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i])
          for (int j = i * i; j <= n; j += i) is_prime[j] = false;
      }
      for (int i = 2; i <= n; ++i)
        if (is_prime[i]) prime.push_back(i);
    }
    ```

=== "Python"
    ```python
    prime = []
    is_prime = [False] * N
    
    
    def Eratosthenes(n):
        is_prime[0] = is_prime[1] = False
        for i in range(2, n + 1):
            is_prime[i] = True
        # Let i loop to <= sqrt(n)
        for i in range(2, isqrt(n) + 1):  # `isqrt` is a new function in Python 3.8
            if is_prime[i]:
                for j in range(i * i, n + 1, i):
                    is_prime[j] = False
        for i in range(2, n + 1):
            if is_prime[i]:
                prime.append(i)
    ```

This optimization does not affect the asymptotic time complexity; repeating the above proof gives $n \ln \ln \sqrt n + o(n)$, which is asymptotically the same according to the properties of logarithms, but the number of operations is significantly reduced.

#### Sieve only odd numbers

Since all even numbers except 2 are composite, we can simply skip them and only care about odd numbers.

First, this halves our memory requirement; second, the required operations are approximately halved as well.

#### Reducing memory usage

We note that during sieving, we only need an array of type `bool`. A `bool` array element typically occupies 1 byte (i.e., 8 bits), but storing a boolean value requires only 1 bit.

We can use knowledge of [bit operations](../bit.md) to compress each boolean value into one bit, so we only need $n$ bits (i.e., $\dfrac{n}{8}$ bytes) instead of $n$ bytes, significantly reducing memory usage. This method is called "bit-level compression."

It is worth noting that there are data structures that automatically perform bit-level compression, such as `vector<bool>` and `bitset<>` in C++.

Furthermore, `vector<bool>` and `bitset<>` have constant optimizations for the program; the Sieve of Eratosthenes with $O(n\log\log n)$ time complexity, when optimized with `bitset<>` or `vector<bool>`, can even outperform the Euler sieve with $O(n)$ time complexity.

See [bitset: combined with Eratosthenes sieve](../../lang/csl/bitset.md#与埃氏筛结合).

#### Block sieving

From the optimization "sieve up to square root," we know we don't need to keep the entire `is_prime[1...n]` array at all times. To perform sieving, it suffices to keep primes up to $\sqrt n$, i.e., `prime[1...sqrt(n)]`. And divide the entire range into blocks, each block processed separately. This way, we don't need to keep multiple blocks in memory at the same time, and the CPU can better handle caching.

Let $s$ be a constant that determines the block size, then we have $\lceil {\frac n s} \rceil$ blocks, and block $k$ ($k = 0 \dots \lfloor {\frac n s} \rfloor$) contains numbers in the interval $[ks, ks + s - 1]$. We process blocks one by one; that is, for each block $k$, we iterate through all primes (from $1$ to $\sqrt n$) and use them for sieving.

It is worth noting that when processing the first number, we need to slightly modify the strategy: first, keep all primes in $[1, \sqrt n]$; second, numbers $0$ and $1$ should be marked as non-prime. When processing the last block, we should not forget that the last number $n$ is not necessarily at the end of the block.

The following implementation uses block sieving to count the number of primes less than or equal to $n$.

???+ note "Implementation"
    ```cpp
    int count_primes(int n) {
      constexpr static int S = 10000;
      vector<int> primes;
      int nsqrt = sqrt(n);
      vector<char> is_prime(nsqrt + 1, true);
      for (int i = 2; i <= nsqrt; i++) {
        if (is_prime[i]) {
          primes.push_back(i);
          for (int j = i * i; j <= nsqrt; j += i) is_prime[j] = false;
        }
      }
      int result = 0;
      vector<char> block(S);
      for (int k = 0; k * S <= n; k++) {
        fill(block.begin(), block.end(), true);
        int start = k * S;
        for (int p : primes) {
          int start_idx = (start + p - 1) / p;
          int j = max(start_idx, p) * p - start;
          for (; j < S; j += p) block[j] = false;
        }
        if (k == 0) block[0] = block[1] = false;
        for (int i = 0; i < S && start + i <= n; i++) {
          if (block[i]) result++;
        }
      }
      return result;
    }
    ```

The asymptotic time complexity of block sieving is the same as the Sieve of Eratosthenes (unless the blocks are very small), but the required memory is reduced to $O(\sqrt{n} + S)$, and it has better cache performance.
On the other hand, division must be performed for each pair of block and prime in $[1, \sqrt{n}]$, and for smaller blocks, this situation is much worse.
Therefore, a balance must be maintained when choosing the constant $S$.

The block size $S$ between $10^4$ and $10^5$ gives the best speed.

### Linear Sieve

The Sieve of Eratosthenes still has room for optimization; it marks a composite number multiple times. Is there a way to eliminate these meaningless steps? The answer is yes.

If each composite number can be marked only once, the time complexity can be reduced to $O(n)$.

???+ note "Implementation"
    === "C++"
        ```cpp
        vector<int> pri;
        bool not_prime[N];
        
        void pre(int n) {
          for (int i = 2; i <= n; ++i) {
            if (!not_prime[i]) {
              pri.push_back(i);
            }
            for (int pri_j : pri) {
              if (i * pri_j > n) break;
              not_prime[i * pri_j] = true;
              if (i % pri_j == 0) {
                // i % pri_j == 0
                // In other words, i was previously sieved by pri_j
                // Since primes in pri are in ascending order, i multiplied 
                // by other primes will definitely be sieved by pri_j's multiples,
                // so we don't need to sieve here; just break
                break;
              }
            }
          }
        }
        ```
    
    === "Python"
        ```python
        pri = []
        not_prime = [False] * N
        
        
        def pre(n):
            for i in range(2, n + 1):
                if not not_prime[i]:
                    pri.append(i)
                for pri_j in pri:
                    if i * pri_j > n:
                        break
                    not_prime[i * pri_j] = True
                    if i % pri_j == 0:
                        """
                        i % pri_j == 0
                        In other words, i was previously sieved by pri_j
                        Since primes in pri are in ascending order, i multiplied 
                        by other primes will definitely be sieved by pri_j's multiples,
                        so we don't need to sieve here; just break
                        """
                        break
        ```

The above **linear sieve** is also called the **Euler sieve**.

???+ note "Note"
    Note that while finding primes, we also obtain the smallest prime factor of each number.

## Sieve for Euler's Totient Function

Note that in the linear sieve, each composite number is sieved by its smallest prime factor. For example, let $p_1$ be the smallest prime factor of $n$, $n' = \frac{n}{p_1}$, then during the linear sieve, $n$ is sieved through $n' \times p_1$.

Observing the linear sieve process, we need to handle two parts; we discuss them by cases based on $n' \bmod p_1$.

If $n' \bmod p_1 = 0$, then $n'$ contains all prime factors of $n$.

$$
\begin{aligned}
\varphi(n) & = n \times \prod_{i = 1}^s{\frac{p_i - 1}{p_i}} \\\\
& = p_1 \times n' \times \prod_{i = 1}^s{\frac{p_i - 1}{p_i}} \\\\
& = p_1 \times \varphi(n')
\end{aligned}
$$

What if $n' \bmod p_1 \neq 0$? Then $n'$ and $p_1$ are coprime. According to the properties of Euler's totient function, we have:

$$
\begin{aligned}
\varphi(n) & = \varphi(p_1) \times \varphi(n') \\\\
& = (p_1 - 1) \times \varphi(n')
\end{aligned}
$$

### Implementation

=== "C++"
    ```cpp
    vector<int> pri;
    bool not_prime[N];
    int phi[N];
    
    void pre(int n) {
      phi[1] = 1;
      for (int i = 2; i <= n; i++) {
        if (!not_prime[i]) {
          pri.push_back(i);
          phi[i] = i - 1;
        }
        for (int pri_j : pri) {
          if (i * pri_j > n) break;
          not_prime[i * pri_j] = true;
          if (i % pri_j == 0) {
            phi[i * pri_j] = phi[i] * pri_j;
            break;
          }
          phi[i * pri_j] = phi[i] * phi[pri_j];
        }
      }
    }
    ```

=== "Python"
    ```python
    pri = []
    not_prime = [False] * N
    phi = [0] * N
    
    
    def pre(n):
        phi[1] = 1
        for i in range(2, n + 1):
            if not not_prime[i]:
                pri.append(i)
                phi[i] = i - 1
            for pri_j in pri:
                if i * pri_j > n:
                    break
                not_prime[i * pri_j] = True
                if i % pri_j == 0:
                    phi[i * pri_j] = phi[i] * pri_j
                    break
                phi[i * pri_j] = phi[i] * phi[pri_j]
    ```

## Sieve for Möbius Function

### Definition

According to the definition of the Möbius function, let $n$ be a composite number, $p_1$ be the smallest prime factor of $n$, $n'=\frac{n}{p_1}$, then:

$$
\mu(n)=
\begin{cases}
    0 & n' \bmod p_1 = 0\\\\
    -\mu(n') & \text{otherwise}
\end{cases}
$$

If $n$ is prime, then $\mu(n)=-1$.

### Implementation

=== "C++"
    ```cpp
    vector<int> pri;
    bool not_prime[N];
    int mu[N];
    
    void pre(int n) {
      mu[1] = 1;
      for (int i = 2; i <= n; ++i) {
        if (!not_prime[i]) {
          mu[i] = -1;
          pri.push_back(i);
        }
        for (int pri_j : pri) {
          if (i * pri_j > n) break;
          not_prime[i * pri_j] = true;
          if (i % pri_j == 0) {
            mu[i * pri_j] = 0;
            break;
          }
          mu[i * pri_j] = -mu[i];
        }
      }
    }
    ```

=== "Python"
    ```python
    pri = []
    not_prime = [False] * N
    mu = [0] * N
    
    
    def pre(n):
        mu[1] = 1
        for i in range(2, n + 1):
            if not not_prime[i]:
                mu[i] = -1
                pri.append(i)
            for pri_j in pri:
                if i * pri_j > n:
                    break
                not_prime[i * pri_j] = True
                if i % pri_j == 0:
                    mu[i * pri_j] = 0
                    break
                mu[i * pri_j] = -mu[i]
    ```

## Sieve for Number of Divisors

Let $d_i$ represent the number of divisors of $i$, and $num_i$ represent the exponent of the smallest prime factor of $i$.

### Divisor Count Theorem

Theorem: If $n=\prod_{i=1}^m p_i^{c_i}$ then $d_i=\prod_{i=1}^m (c_i+1)$.

Proof: We know that $p_i^{c_i}$ has $p_i^0,p_i^1,\dots ,p_i^{c_i}$ as divisors, totaling $c_i+1$ of them. By the multiplication principle, the number of divisors of $n$ is $\prod_{i=1}^m (c_i+1)$.

### Implementation

Since $d_i$ is a multiplicative function, we can use a linear sieve.

Here is a brief introduction to the implementation principle of linear sieve:

1. When $i$ is prime, $\textit{num}_i \gets 1,\textit{d}_i \gets 2$, and set $q = \left\lfloor \dfrac {i}{p} \right\rfloor$, where $p$ is the smallest prime factor of $i$.
2. When $p$ is a prime factor of $q$, $\textit{num}_i \gets \textit{num}_q + 1,\textit{d}_i \gets \dfrac{\textit{d}_q}{\textit{num}_i} \times (\textit{num}_i + 1)$.
3. When $p$ and $q$ are coprime, $\textit{num}_i \gets 1,\textit{d}_i \gets \textit{d}_q \times (\textit{num}_i+1)$.

=== "C++"
    ```cpp
    vector<int> pri;
    bool not_prime[N];
    int d[N], num[N];
    
    void pre(int n) {
      d[1] = 1;
      for (int i = 2; i <= n; ++i) {
        if (!not_prime[i]) {
          pri.push_back(i);
          d[i] = 2;
          num[i] = 1;
        }
        for (int pri_j : pri) {
          if (i * pri_j > n) break;
          not_prime[i * pri_j] = true;
          if (i % pri_j == 0) {
            num[i * pri_j] = num[i] + 1;
            d[i * pri_j] = d[i] / num[i * pri_j] * (num[i * pri_j] + 1);
            break;
          }
          num[i * pri_j] = 1;
          d[i * pri_j] = d[i] * 2;
        }
      }
    }
    ```

=== "Python"
    ```python
    pri = []
    not_prime = [False] * N
    d = [0] * N
    num = [0] * N
    
    
    def pre(n):
        d[1] = 1
        for i in range(2, n + 1):
            if not not_prime[i]:
                pri.append(i)
                d[i] = 2
                num[i] = 1
            for pri_j in pri:
                if i * pri_j > n:
                    break
                not_prime[i * pri_j] = True
                if i % pri_j == 0:
                    num[i * pri_j] = num[i] + 1
                    d[i * pri_j] = d[i] // num[i * pri_j] * (num[i * pri_j] + 1)
                    break
                num[i * pri_j] = 1
                d[i * pri_j] = d[i] * 2
    ```

## Sieve for Sum of Divisors

Let $f_i$ represent the sum of divisors of $i$, and $g_i$ represent $p^0+p^1+p^2+\dots p^k$ where $p$ is the smallest prime factor of $i$.

### Implementation

=== "C++"
    ```cpp
    vector<int> pri;
    bool not_prime[N];
    int g[N], f[N];
    
    void pre(int n) {
      g[1] = f[1] = 1;
      for (int i = 2; i <= n; ++i) {
        if (!not_prime[i]) {
          pri.push_back(i);
          g[i] = i + 1;
          f[i] = i + 1;
        }
        for (int pri_j : pri) {
          if (i * pri_j > n) break;
          not_prime[i * pri_j] = true;
          if (i % pri_j == 0) {
            g[i * pri_j] = g[i] * pri_j + 1;
            f[i * pri_j] = f[i] / g[i] * g[i * pri_j];
            break;
          }
          f[i * pri_j] = f[i] * f[pri_j];
          g[i * pri_j] = 1 + pri_j;
        }
      }
    }
    ```

=== "Python"
    ```python
    pri = []
    not_prime = [False] * N
    f = [0] * N
    g = [0] * N
    
    
    def pre(n):
        g[1] = f[1] = 1
        for i in range(2, n + 1):
            if not not_prime[i]:
                pri.append(i)
                g[i] = i + 1
                f[i] = i + 1
            for pri_j in pri:
                if i * pri_j > n:
                    break
                not_prime[i * pri_j] = True
                if i % pri_j == 0:
                    g[i * pri_j] = g[i] * pri_j + 1
                    f[i * pri_j] = f[i] // g[i] * g[i * pri_j]
                    break
                f[i * pri_j] = f[i] * f[pri_j]
                g[i * pri_j] = 1 + pri_j
    ```

## General Multiplicative Functions

If a [multiplicative function](./basic.md#积性函数) $f$ satisfies: for any prime $p$ and positive integer $k$, $f(p^k)$ can be computed in low-degree polynomial time with respect to $k$, then we can sieve out the values $f(1),f(2),\dots,f(n)$ in $O(n)$ time.

Let the prime factorization of a composite number $n$ be $\prod_{i=1}^k p_i^{\alpha_i}$, where $p_1<p_2<\dots<p_k$ are primes. We record $g_n=p_1^{\alpha_1}$ in the linear sieve. If $n$ is sieved by $x \cdot p$ (where $p$ is prime), then $g$ satisfies the following recurrence:

$$
g_n=
\begin{cases}
    g_x\cdot p & x\bmod p=0\\\\
    p & \text{otherwise}
\end{cases}
$$

If $n=g_n$, then $n$ is a power of some prime, and we can compute $f(n)$ in $O(1)$; otherwise, $f(n)=f(\frac{n}{g_n})\cdot f(g_n)$.

**Some content in this section is translated from the blog post [Решето Эратосфена](http://e-maxx.ru/algo/eratosthenes_sieve) and its English translation [Sieve of Eratosthenes](https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html). The Russian version is in the Public Domain with Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
