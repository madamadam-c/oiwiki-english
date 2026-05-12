## Introduction

Given a positive integer $N \in \mathbf{N}_{+}$, we aim to quickly find one of its non-trivial factors.

Consider the naive algorithm: factors come in pairs, so all factors of $N$ can be divided into two groups: $[2, \sqrt N]$ and $[\sqrt N+1, N)$. We only need to iterate through numbers in $[2, \sqrt N]$ and use division to find at least two factors. This method has a time complexity of $O(\sqrt N)$.

When $N\ge10^{18}$, the running time of this algorithm is unacceptable. We desire a better algorithm. One idea is to use randomization to guess whether a number is a factor of $N$. If we are lucky, we can solve it in $O(1)$ time complexity, but for $N\ge10^{18}$, the probability of a successful guess is $\frac{1}{10^{18}}$, and the expected number of guesses is $10^{18}$. If we guess within $[2,\sqrt N]$, the success rate would be higher. We want a method to optimize the guessing.

## Naive Algorithm

The simplest algorithm is to iterate through $[2, \sqrt N]$.

=== "C++"
    ```cpp
    vector<int> breakdown(int N) {
      vector<int> result;
      for (int i = 2; i * i <= N; i++) {
        if (N % i == 0) {
          while (N % i == 0) N /= i;
          result.push_back(i);
        }
      }
      if (N != 1) {
        result.push_back(N);
      }
      return result;
    }
    ```

=== "Python"
    ```python
    def breakdown(N):
        result = []
        for i in range(2, int(sqrt(N)) + 1):
            if N % i == 0:
                while N % i == 0:
                    N //= i
                result.append(i)
        if N != 1:
            result.append(N)
        return result
    ```

We can prove that all elements in `result` are precisely the prime factors of `N`.

??? note "Proof that `result` contains all prime factors of $N$"
    First, examine the change in `N`. When the loop finishes iteration `i`, since we just executed `while(N % i == 0) N /= i`, `i` no longer divides `N`. Moreover, each time we divide out a factor, `N` still divides the original $N$. These two points guarantee that when the loop reaches `i`, the current `N` is a factor of the original $N$ and is not divisible by any integer smaller than `i`.
    
    Next, prove that all elements in `result` are factors of $N$. When the loop reaches `i`, the condition to store `i` in `result` is `N % i == 0`, which means `i` divides the current `N`, and we have already shown that the current `N` divides the original $N$. Therefore, `i` is a factor of the original $N`. When the loop for `i` ends, if `N` is not one, it is stored in `result`. According to the previous discussion, it is necessarily a factor of $N$.
    
    Next, prove that all elements in `result` are prime numbers. Suppose there exists a composite number $K$ in `result`. Then there exists an `i` no greater than $\sqrt K$ such that `i` is a factor of `K`. Such a $K$ could not have been stored as some `i` in the loop, because the first part already shows that when the loop reaches $K$, `N` is not divisible by any `i` smaller than $K$. Such a $K$ could not have been added after the loop either, because the loop exits when `i * i > N`. Hence we have iterated through all `i` no greater than $\sqrt K$, and by the above discussion, these `i` certainly do not divide the current `N`, which is $K$.
    
    Finally, prove that all prime factors of $N$ must appear in `result`. Suppose $p$ is a prime factor of $N$ but does not appear in `result`. According to the above discussion, $p$ cannot be an `i` that appeared in the loop. Let `i` be the last `i` before the loop exits; then `i` is strictly less than $p$, and the `N` after the loop exits is not divisible by any previous `i`. Therefore, $p$ divides this `N`. So the final `N` is greater than one. According to the previous discussion, it must be prime, so `N` equals $p` and will be added to `result` at the end, contradicting the assumption.

It is worth noting that if a prime table is pre-built, the time complexity drops from $O(\sqrt N)$ to $O(\frac {\sqrt{N}} {\ln N})$. See the sieve method for more information on precomputation.

Practice problem: [CF 1445C](https://codeforces.com/problemset/problem/1445/C)

## Pollard Rho Algorithm

### Introduction

Using the brute-force algorithm to obtain a non-trivial factor has a complexity of $O(p)=O(\sqrt N)$, where $p$ is the smallest prime factor of $N$. The Pollard-Rho algorithm introduced below is a randomized algorithm that can obtain a non-trivial factor in an expected complexity of $O(\sqrt p)=O(N^{1/4})$ (**note**: a non-trivial factor is not necessarily a prime factor).

The core idea is: for a random self-mapping $f: \mathbb Z_p \rightarrow \mathbb Z_p$, starting from any point $x_1$, iteratively computing $x_n = f(x_{n-1})$, the sequence will enter a cycle in $O(\sqrt p)$ expected time. If we can find $x_i \equiv x_j \pmod p$, then $p$ divides $\gcd(|x_i-x_j|, N)$, and this greatest common divisor is a non-trivial factor of $N$.

To understand why the expected time to enter a cycle is $O(\sqrt p)$, we can draw inspiration from the birthday paradox.

### Birthday Paradox

Without considering birth years (assuming 365 days per year), ask: how many people must be in a room for the probability that at least two share a birthday to reach $50\%$?

Solution: Assume a year has $n$ days, and there are $k$ people in the room, numbered $1, 2, \dots, k$. Assume each person's birthday is uniformly distributed over $n$ days, and the birthdays of two people are independent.

Let $A$ be the event that the $k$ people all have different birthdays. The probability of event $A$ is

$$
P(A)=\prod_{i=0}^{k-1}\frac{n-i}{n}
$$

The probability that at least two people share a birthday is $P(\overline A)=1-P(A)$. By the problem statement, $P(\overline A)\ge\frac{1}{2}$, so

$$
P(A)=\prod_{i=0}^{k-1}\frac{n-i}{n} \le \frac{1}{2}
$$

Using the inequality $1+x\le \mathrm{e}^x$, we get

$$
P(A) \le \prod_{i=1}^{k-1}\exp\left({-\frac{i}{n}}\right)=\exp \left({-\frac{k(k-1)}{2n}}\right)
$$

Therefore

$$
\exp\left({-\dfrac{k(k-1)}{2n}}\right) \le \frac{1}{2}\implies P(A) \le \frac{1}{2}
$$

Substituting $n=365$, we get $k\geq 23$. So at least 23 people in a room makes the probability of two sharing a birthday reach $50\%$, but this mathematical fact is highly counterintuitive, hence called a paradox.

When $k>56$ and $n=365$, the probability of two people sharing a birthday exceeds $99\%$. In a year with $n$ days, when the room has $\frac{1}{2}(\sqrt{8n\ln 2+1}+1)\approx \sqrt{2n\ln 2}$ people, the probability of at least two sharing a birthday is approximately $50\%$.

Similarly, one can calculate that when randomly selecting a sequence of birthdays, the expected number of people needed to first get a repeated birthday is also $O(\sqrt n)$. Let this number be $X$, then

$$
E(X) = \sum_{x=1}^{n+1}P(X\ge x+1) = \sum_{x=0}^n\frac{n!}{(n-x)!n^x} = \sqrt{\frac{\pi n}{2}}-\frac13+o(1).
$$

This inspires us that if we can randomly select a sequence of numbers, the expected sampling size needed to get a repeat is also $O(\sqrt n)$.

### Finding a Divisor via Greatest Common Divisor

In practice, constructing a truly random sequence modulo $p$ is not feasible because $p$ is what we are trying to find. Therefore, we generate a pseudorandom sequence $\{x_i\}$ using $f(x)=(x^2+c)\bmod N$: randomly pick an $x_1$, let $x_2=f(x_1),\ x_3=f(x_2),\ \dots,\ x_i=f(x_{i-1})$, where $c\in[1,N)$ is a randomly chosen constant.

The chosen function is easy to compute and often generates a fairly random sequence. However, it is not completely random. For example, let $n=50,\ c=6,\ x_1=1$. The sequence generated by $f(x)$ is

$$
1, 7, 5, 31, 17, 45, 31, 17, 45, 31,\dots
$$

We can see that after $x_4$, the data cycles among $31, 17, 45$. If we arrange these numbers as shown in the figure, the pattern resembles a $\rho$, hence the algorithm's name.

![pollard-rho](./images/pollard-rho.svg)

More importantly, such a function indeed provides a self-mapping on $\mathbb Z_p$. That is, it satisfies the property: if $x\equiv y\pmod p$, then $f(x)\equiv f(y)\pmod p$.

???+ note "Proof"
    If $x\equiv y\pmod p$, then $x^2+c\equiv y^2+c\pmod p$. Note that $f(x)=x^2+c-k_xN$, where $k_x$ is an integer depending on $x$, and $p|N$, so $f(x)=x^2+c\pmod p$, therefore $f(x)=f(y)\pmod p$.

As a pseudorandom self-mapping on $\mathbb Z_p$, the sequence $\{x_n\bmod p\}$ will have a repeat in $O(\sqrt p)$ expected time. As long as we observe such a repeat $x_i\equiv x_j\pmod p$, we can obtain a non-trivial factor of $N$ via $\gcd(|x_i-x_j|,N)$. Note that since $p$ is unknown, we cannot directly detect a repeat; a simple method is to check whether $\gcd(|x_i-x_j|,N)$ is strictly greater than one.

This algorithm does not always succeed, because $\gcd(|x_i-x_j|,N)$ may equal $N$. That is, $x_i\equiv x_j\pmod N$. In this case, when $\{x_n\bmod p\}$ first repeats, $\{x_n\}$ also repeats simultaneously. We did not obtain a non-trivial factor. Moreover, after $\{x_n\}$ starts cycling, continuing the iteration is meaningless because it will only repeat this cycle. The algorithm should output a failure and change the constant $c$ in $f(x)$ to factor again.

According to the analysis above, in theory, any function $f(x)$ satisfying $\forall x \equiv y \pmod p, f(x) \equiv f(y) \pmod p$ and guaranteeing some pseudorandomness (such as certain polynomial functions) can be used here. In practice, $f(x)=x^2+c\ (c\neq 0,-2)$ is mainly used.

### Implementation

We need to implement an algorithm that quickly detects whether $\{x_n\bmod p\}$ has repeated during iteration. Treating $f$ as edges in a directed graph with vertices $\mathbb Z_p$, what we actually need to implement is a cycle detection algorithm, where equality checking is replaced by checking whether $\gcd(|x_i-x_j|,N)$ is greater than one.

#### Floyd's Cycle Detection

Suppose two people are racing: A is fast and B is slow. After some time, A will definitely meet B, and the total distance A has run minus the total distance B has run is a multiple of the loop length.

Let $a=f(0), b=f(f(0))$. At each update, set $a=f(a), b=f(f(b))$. As long as we check during the update whether $a$ and $b$ are equal, if they are, a cycle has been found.

We calculate $d=\gcd(|x_i-x_j|,N)$ at each step and check whether $1< d< N$. If satisfied, we can return $d$ directly. If $d=N$, it means $\{x_i\}$ has already formed a cycle, and we cannot continue. We return $N$ itself and later adjust the random constant $c$ to factor again.

??? note "Pollard-Rho Algorithm Based on Floyd's Cycle Detection"
    === "C++"
        ```cpp
        ll Pollard_Rho(ll N) {
          if (N == 4) return 2;
          ll c = rand() % (N - 1) + 1;
          ll t = f(0, c, N);
          ll r = f(f(0, c, N), c, N);
          while (t != r) {
            ll d = gcd(abs(t - r), N);
            if (d > 1) return d;
            t = f(t, c, N);
            r = f(f(r, c, N), c, N);
          }
          return N;
        }
        ```
    
    === "Python"
        ```python
        import random
        
        def Pollard_Rho(N):
            if N == 4:
                return 2
            c = random.randint(1, N - 1)
            t = f(0, c, N)
            r = f(f(0, c, N), c, N)
            while t != r:
                d = gcd(abs(t - r), N)
                if d > 1:
                    return d
                t = f(t, c, N)
                r = f(f(r, c, N), c, N)
            return N
        ```

#### Brent's Cycle Detection

In fact, Floyd's cycle detection algorithm can be improved in terms of constants. Brent's cycle detection starts from $k=1$ and incrementally increases $k$. In the $k$-th round, A stays in place while B moves forward $2^k$ steps. If B encounters A during the process, a cycle has been found; otherwise, A is instantly moved to B's position and we continue to the next round.

It can be proven that the number of calls to $f$ needed before finding a cycle is never more than that of Floyd's cycle detection algorithm. The original paper's tests show that Brent's cycle detection reduces the average time by $24\%$ compared to Floyd's.

#### Multiplication Optimization

Whether using Floyd's or Brent's cycle detection, the number of iterations is $O(\sqrt p)$. However, using $\gcd$ at each iteration to check for a cycle slows down the algorithm. We can reduce the number of $\gcd$ computations by accumulating products.

Simply put, if $\gcd(a,N)>1$, then $\gcd(ab\bmod N,N)=\gcd(ab,N)>1$ for any $b\in\mathbb N_+$. That is, if we compute $\gcd(\prod |x_i-x_j| \bmod N,N)>1$, then there must be a pair $(x_i,x_j)$ among them such that $\gcd(|x_i-x_j|,N)>1$. If this product becomes zero at any point, the factorization fails; we exit and return $N$.

If we compute $\gcd$ once every $k$ pairs, the complexity becomes $O(\sqrt p+k^{-1}\sqrt p\log N)$, where $\log N$ is the cost of a single $\gcd$ computation. When $k$ and $\log N$ are roughly of the same order, we get an expected complexity of $O(\sqrt p)$. In practice, $k=128$ is commonly chosen.

Here is a Pollard-Rho implementation using Brent's cycle detection with multiplication optimization.

??? note "Implementation"
    === "C++"
        ```cpp
        ll Pollard_Rho(ll x) {
          ll t = 0;
          ll c = rand() % (x - 1) + 1;
          ll s = t;
          int step = 0, goal = 1;
          ll val = 1;
          for (goal = 1;; goal <<= 1, s = t, val = 1) {
            for (step = 1; step <= goal; ++step) {
              t = f(t, c, x);
              val = val * abs(t - s) % x;
              if (!val) return x;
              if (step % 127 == 0) {
                ll d = gcd(val, x);
                if (d > 1) return d;
              }
            }
            ll d = gcd(val, x);
            if (d > 1) return d;
          }
        }
        ```
    
    === "Python"
        ```python
        from random import randint
        from math import gcd
        
        def Pollard_Rho(x):
            c = randint(1, x - 1)
            s = t = f(0, c, x)
            goal = val = 1
            while True:
                for step in range(1, goal + 1):
                    t = f(t, c, x)
                    val = val * abs(t - s) % x
                    if val == 0:
                        return x
                    if step % 127 == 0:
                        d = gcd(val, x)
                        if d > 1:
                            return d
                d = gcd(val, x)
                if d > 1:
                    return d
                s = t
                goal <<= 1
                val = 1
        ```

#### Complexity

The expected number of iterations in Pollard-Rho is $O(\sqrt p)$, where $p$ is the smallest prime factor of $N$. Whether using Floyd's or Brent's cycle detection in concrete implementation, without multiplication optimization, the expected complexity is $O(\sqrt p\log N)$; with multiplication optimization, an expected complexity of $O(\sqrt p)$ can be approximately achieved.

It is worth mentioning that the preceding analysis is based on a completely random self-mapping function, but Pollard-Rho actually uses a pseudorandom function. Therefore, this algorithm lacks a rigorous complexity analysis and typically runs faster in practice.

#### Practice Problem: Finding the Largest Prime Factor of a Number

Problem: [P4718 Template Pollard-Rho Algorithm](https://www.luogu.com.cn/problem/P4718)

For a number $n$, first use the Miller-Rabin algorithm to check if it is prime. If so, return directly. Otherwise, use Pollard-Rho to find a factor $p$, and divide $n$ by $p$. Recursively factor $n$ and $p$, use Miller-Rabin to check for prime factors, and update with max_factor to find the largest prime factor. Since the data in this problem is extremely large, Floyd's cycle detection is insufficient; we use multiplication optimization instead.

??? note "Implementation"
    ```cpp
    --8<-- "docs/math/code/pollard-rho/pollard-rho_1.cpp"
    ```

## References and Links

[^ref1]: <https://en.wikipedia.org/wiki/Birthday_problem#Reverse_problem>

[^pseudo]: Menezes, Alfred J.; van Oorschot, Paul C.; Vanstone, Scott A. (2001). Handbook of Applied Cryptography. Section 3.11 and 3.12.

[^brent]: Brent, R. P. (1980), An improved Monte Carlo factorization algorithm, BIT Numerical Mathematics, 20(2): 176–184, doi:10.1007/BF01933190
