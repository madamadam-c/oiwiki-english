author: i-Yirannn, Xeonacid, ouuan

## Introduction

`std::bitset` is a fixed-size standard-library container for storing `0/1` values. Strictly speaking, it is not part of STL.

??? note "bitset and STL"
    > The C++ standard library provides some special container classes, the so-called container adapters (stack, queue, priority queue). In addition, a few classes provide a container-like interface (for example, strings, bitsets, and valarrays). All these classes are covered separately.1 Container adapters and bitsets are covered in Chapter 12.
    >
    > The C++ standard library provides not only the containers for the STL framework but also some containers that fit some special needs and provide simple, almost self-explanatory, interfaces. You can group these containers into either the so-called container adapters, which adapt standard STL containers to fit special needs, or a bitset, which is a containers for bits or Boolean values. There are three standard container adapters: stacks, queues, and priority queues. In priority queues, the elements are sorted automatically according to a sorting criterion. Thus, the "next" element of a priority queue is the element with the "highest" value. A bitset is a bitfield with an arbitrary but fixed number of bits. Note that the C++ standard library also provides a special container with a variable size for Boolean values: vector.
    
    -- Excerpt from *The C++ Standard Library, 2nd Edition*
    
    From this perspective, `bitset` is not part of STL, but rather a "special container" in the standard library. In fact, as a container, it does not satisfy the requirements of STL containers. Nor is it an adapter, because it does not rely on another STL container as its underlying implementation.

Since memory addresses are addressed by byte rather than by bit, a variable of type `bool` occupies 1 byte of memory even though it can only represent `0/1`.

`bitset` uses fixed-size optimization so that the eight bits in one byte can separately store 8 `0/1` values.

Compared with a 4-byte `int` variable, when only storing `0/1`, `bitset` uses only $\frac{1}{32}$ of the space, and when computing some information, the required time may also be $\frac{1}{32}$.

In some cases, `bitset` can optimize program runtime efficiency. Whether it optimizes complexity or constant factors depends on how complexity is analyzed. Common notations for `bitset` complexity include the following, assuming the original complexity is $O(n)$:

1.  $O(n)$: this notation considers `bitset` to provide no complexity optimization.
2.  $O(\frac{n}{32})$: this notation is not rigorous, since constants should not appear in complexity, but it reflects that `bitset` can reduce the required time to $\frac{1}{32}$.
3.  $O(\frac n w)$, where $w=32$, the word size of the machine. This notation is more widely accepted.
4.  $O(\frac n {\log w})$ where $w$ is the size of an integer variable on the machine.

In addition, the specialization `vector<bool>` stores data in the same way as `bitset`. The difference is that it supports dynamic allocation, while `bitset`, like ordinary static arrays, is allocated at compile time. However, `bitset` provides useful library functions that are not only convenient, but can sometimes enable SIMD and reduce constants. Also, some behavior of `vector<bool>` differs from `vector`; for example, for `std::vector<bool> vec`, `&vec[0] + i` is not equal to `&vec[i]`. Therefore, `vector<bool>` is generally not used.

## Usage

See [std::bitset - cppreference.com](https://en.cppreference.com/w/cpp/utility/bitset).

### Header

```cpp
#include <bitset>
```

### Specifying Size

```cpp
std::bitset<1000> bs;  // a bitset with 1000 bits
```

### Constructors

-   `bitset()`: every bit is `false`.
-   `bitset(unsigned long val)`: sets the bits to the binary representation of `val`.
-   `bitset(const string& str)`: sets the bits to the $01$ string `str`.

### Operators

-   `operator []`: accesses a specific bit.

-   `operator ==`/`operator !=`: compares whether the contents of two `bitset`s are exactly the same.

-   `operator &`/`operator &=`/`operator |`/`operator |=`/`operator ^`/`operator ^=`/`operator ~`: performs bitwise AND/OR/XOR/NOT operations.

    Note: **`bitset` can only perform bitwise operations with another `bitset`**. To perform bitwise operations with an integer, first convert the integer to a `bitset`.

-   `operator <<`/`operator >>`/`operator <<=`/`operator >>=`: performs binary left/right shifts.

In addition, `bitset` supports C++ stream I/O, which means you can use `cin`/`cout` for input and output.

### Member Functions

-   `count()`: returns the number of `true` bits.
-   `size()`: returns the size of the `bitset`.
-   `test(pos)`: has the same role as `at()` in `vector`; unlike `[]`, it performs bounds checking.
-   `any()`: returns `true` if any bit is `true`, otherwise returns `false`.
-   `none()`: returns `true` if all bits are `false`, otherwise returns `false`.
-   `all()`: returns `true` if all bits are `true`, otherwise returns `false`.
-   1.  `set()`: sets the entire `bitset` to `true`.
    2.  `set(pos, val = true)`: sets one bit to `true`/`false`.
-   1.  `reset()`: sets the entire `bitset` to `false`.
    2.  `reset(pos)`: sets one bit to `false`, equivalent to `set(pos, false)`.
-   1.  `flip()`: flips every bit. ($0\leftrightarrow1$, equivalent to XOR with a `bitset` full of $1$s.)
    2.  `flip(pos)`: flips one bit.
-   `to_string()`: returns the string representation.
-   `to_ulong()`: returns the `unsigned long` representation. `long` is the same as `int` on NT and 32-bit POSIX systems, and the same as `long long` on 64-bit POSIX systems.
-   `to_ullong()`: since **C++11**, returns the `unsigned long long` representation.

In addition, libstdc++ has some useful internal member functions[^bitset1]:

-   `_Find_first()`: returns the index of the first `true` bit in the `bitset`; if there is no `true` bit, returns the size of the `bitset`.
-   `_Find_next(pos)`: returns the index of the first `true` bit after `pos`, meaning with index strictly greater than `pos`; if there is no `true` bit after `pos`, returns the size of the `bitset`.

## Applications

### [「LibreOJ β Round #2」贪心只能过样例](https://loj.ac/problem/515)

This problem can be solved with DP, and the transition equation is simple:

$f(i,j)$ indicates whether the sum of squares of the first $i$ numbers can be $j$. Then $f(i,j)=\bigvee\limits_{k=a}^bf(i-1,j-k^2)$, taking OR over the values.

But doing this directly is $O(n^5)$ and appears unable to pass.

We can optimize it with `bitset`: just shift left and OR:

??? note "Submission record: [std::bitset](https://loj.ac/submission/395274)"
    ```cpp
    #include <bitset>
    #include <cstdio>
    #include <iostream>
    
    using namespace std;
    
    constexpr int N = 101;
    
    int n, a[N], b[N];
    bitset<N * N * N> f[N];
    
    int main() {
      int i, j;
    
      cin >> n;
    
      for (i = 1; i <= n; ++i) cin >> a[i] >> b[i];
    
      f[0][0] = 1;
    
      for (i = 1; i <= n; ++i) {
        for (j = a[i]; j <= b[i]; ++j) {
          f[i] |= (f[i - 1] << (j * j));
        }
      }
    
      cout << f[n].count();
    
      return 0;
    }
    ```

Because the libstdc++ implementation packs `__CHAR_BIT__ * sizeof(unsigned long)` bits[^bitset2], which is $32$ on some platforms, we can handwrite a `bitset` that only needs to support left-shift-then-OR and pack $64$ bits (`__CHAR_BIT__ * sizeof(unsigned long long)`) for further optimization:

??? note "Submission record: [handwritten bitset](https://loj.ac/submission/395619)"
    ```cpp
    #include <cstdio>
    #include <iostream>
    
    using namespace std;
    
    constexpr int N = 101;
    constexpr int W = 64;
    
    struct Bitset {
      unsigned long long a[N * N * N >> 6];
    
      void shiftor(const Bitset &y, int p, int l, int r) {
        int t = p - p / W * W;
        int tt = (t == 0 ? 0 : W - t);
        int to = (r + p) / W;
        int qaq = (p + W - 1) / W;
    
        for (int i = (l + p) / W; i <= to; ++i) {
          if (i - qaq >= 0) a[i] |= y.a[i - qaq] >> tt;
    
          a[i] |= ((y.a[i - qaq + 1] & ((1ull << tt) - 1)) << t);
        }
      }
    } f[N];
    
    int main() {
      int n, a, b, l = 0, r = 0, ans = 0;
    
      scanf("%d", &n);
    
      f[0].a[0] = 1;
    
      for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &a, &b);
    
        for (int j = a; j <= b; ++j) f[i].shiftor(f[i - 1], j * j, l, r);
    
        l += a * a;
        r += b * b;
      }
    
      for (int i = l / W; i <= r / W; ++i)
        ans += __builtin_popcount(f[n].a[i] & 0xffffffffu) +
               __builtin_popcount(f[n].a[i] >> 32);
    
      printf("%d", ans);
    
      return 0;
    }
    ```

In addition, a brute-force solution with several pruning optimizations can also pass:

??? note "Submission record: [brute force with several pruning optimizations](https://loj.ac/submission/395673)"
    ```cpp
    #include <cstdio>
    #include <iostream>
    
    using namespace std;
    
    constexpr int N = 101;
    constexpr int W = 64;
    
    bool f[N * N * N];
    
    int main() {
      int n, i, j, k, a, b, l = 0, r = 0, ans = 0;
    
      scanf("%d", &n);
    
      f[0] = true;
    
      for (i = 1; i <= n; ++i) {
        scanf("%d%d", &a, &b);
        l += a * a;
        r += b * b;
    
        for (j = r; j >= l; --j) {
          f[j] = false;
    
          for (k = a; k <= b; ++k) {
            if (j - k * k < l - a * a) break;
    
            if (f[j - k * k]) {
              f[j] = true;
              break;
            }
          }
        }
      }
    
      for (i = l; i <= r; ++i) ans += f[i];
    
      printf("%d", ans);
    
      return 0;
    }
    ```

### [CF1097F Alex and a TV Show](https://codeforces.com/contest/1097/problem/F)

#### Statement

You are given $n$ multisets and four operations:

1.  Set a multiset to one number.
2.  Set a multiset to the sum of two other multisets.
3.  Set a multiset to the $\gcd$ of one number chosen from each of two other multisets, that is, $A=\{\gcd(x,y)|x\in B,y\in C\}$.
4.  Query the count of a number in a multiset, **modulo 2**.

There are $10^5$ multisets, $10^6$ operations, and the value range is $7000$.

#### Solution

Seeing "modulo $2$", we can think of using `bitset` to maintain each multiset.

Then operation $1$ is direct assignment, operation $2$ is XOR because it is modulo $2$, and operation $4$ is a direct lookup. But what about operation $3$?

We can try maintaining, for each multiset, the multiset formed by all divisors of its elements. Then operation $3$ becomes a direct bitwise AND.

We can preprocess the `bitset` formed by the divisors of each number in the value range, which solves operation $1$. Operation $2$ is still XOR.

The remaining problem is how to obtain the count of a number in the original multiset from the multiset formed by its divisors.

Let the original multiset be $A$, and let the multiset formed by its divisors be $A'$. To find the count of $x$ in $A$, use [Mobius inversion](../../math/number-theory/mobius.md):

$$
\begin{aligned}
&\sum_{i\in A}\left[\frac{i}{x}=1\right] \\
=&\sum_{i\in A}\sum_{d\mid\frac{i}{x}}\mu(d) \\
=&\sum_{d\in A',x\mid d}\mu\left(\frac{d}{x}\right)
\end{aligned}
$$

Since everything is modulo $2$, $-1$ and $1$ are the same, so we only need to check whether $\frac{d}{x}$ has square factors. Therefore, for each number in the value range, preprocess a `bitset` consisting of positions among its multiples where the quotient by it has no square factor. To answer a query, first take bitwise AND, then call `count()`.

Then the complexity of a single query is $O(\frac{v}{w})$, where $v=7000,\,w=32$.

For preprocessing, $O(v\sqrt v)$ or $O(v^2)$ methods are simple. The logarithmic preprocessing is shown in the code below; its complexity follows the harmonic series, so it is $O(v\log v)$.

??? note "Reference code"
    ```cpp
    #include <bitset>
    #include <cctype>
    #include <cmath>
    #include <cstdio>
    #include <iostream>
    
    using namespace std;
    
    int read() {
      int out = 0;
      char c;
      while (!isdigit(c = getchar()));
      for (; isdigit(c); c = getchar()) out = out * 10 + c - '0';
      return out;
    }
    
    constexpr int N = 100005;
    constexpr int M = 1000005;
    constexpr int V = 7005;
    
    bitset<V> pre[V], pre2[V], a[N], mu;
    int n, m, tot;
    char ans[M];
    
    int main() {
      int i, j, x, y, z;
    
      n = read();
      m = read();
    
      mu.set();
      for (i = 2; i * i < V; ++i) {
        for (j = 1; i * i * j < V; ++j) {
          mu[i * i * j] = 0;
        }
      }
      for (i = 1; i < V; ++i) {
        for (j = 1; i * j < V; ++j) {
          pre[i * j][i] = 1;
          pre2[i][i * j] = mu[j];
        }
      }
    
      while (m--) {
        switch (read()) {
          case 1:
            x = read();
            y = read();
            a[x] = pre[y];
            break;
          case 2:
            x = read();
            y = read();
            z = read();
            a[x] = a[y] ^ a[z];
            break;
          case 3:
            x = read();
            y = read();
            z = read();
            a[x] = a[y] & a[z];
            break;
          case 4:
            x = read();
            y = read();
            ans[tot++] = ((a[x] & pre2[y]).count() & 1) + '0';
            break;
        }
      }
    
      printf("%s", ans);
    
      return 0;
    }
    ```

### Combining with the Sieve of Eratosthenes

Because `bitset` has fast continuous read/write efficiency, it is very suitable for building prime tables together with the [Sieve of Eratosthenes](../../math/number-theory/sieve.md#埃拉托斯特尼筛法).

The usage is simple: just replace the boolean array in the Sieve of Eratosthenes with `bitset`.

??? note "Speed test"
    Tests were performed with [Quick C++ Benchmarks](https://quick-bench.com), using compiler `GCC 13.2` and compilation options `-std=c++20 -O2`.
    
    | Algorithm                                      | Function name            |
    | ---------------------------------------------- | ------------------------ |
    | Eratosthenes + C-style bool array, not storing primes | `Eratosthenes_CArray`    |
    | Eratosthenes + `vector<bool>`, not storing primes | `Eratosthenes_vector`    |
    | Eratosthenes + `bitset`, not storing primes       | `Eratosthenes_bitset`    |
    | Eratosthenes + C-style bool array, storing primes | `Eratosthenes_CArray_sp` |
    | Eratosthenes + `vector<bool>`, storing primes     | `Eratosthenes_vector_sp` |
    | Eratosthenes + `bitset`, storing primes           | `Eratosthenes_bitset_sp` |
    | Euler sieve + C-style bool array                  | `Euler_CArray`           |
    | Euler sieve + `vector<bool>`                      | `Euler_vector`           |
    | Euler sieve + `bitset`                            | `Euler_bitset`           |
    
    -   When the Sieve of Eratosthenes **stores** the primes it finds:
    
        -   [Test result](https://quick-bench.com/q/iQL9FhsZ6PVV81HKABsidRw8hB8) for $N=5 \times 10^7 + 1$:
    
            ![](./images/bitset-5e7sp.png)
        -   [Test result](https://quick-bench.com/q/pwEamEFUW-6nXeXEALRsYPd8FWI) for $N=10^8 + 1$:
    
            ![](./images/bitset-1e8sp.png)
    -   When the Sieve of Eratosthenes **does not store** the primes it finds:
    
        -   [Test result](https://quick-bench.com/q/rg2mCUxT02a44w9fWvHtZoNTJyU) for $N=5 \times 10^7 + 1$:
    
            ![](./images/bitset-5e7.png)
        -   [Test result](https://quick-bench.com/q/lusNWxWsR0VXoRBof7uBtqfvJuY) for $N=10^8 + 1$:
    
            ![](./images/bitset-1e8.png)
    
    From the test results:
    
    1.  The Sieve of Eratosthenes with time complexity $O(n \log \log n)$ can outperform the Euler sieve with time complexity $O(n)$ after optimization with `bitset` or `vector<bool>`.
    2.  Optimizing the Euler sieve with `bitset` or `vector<bool>` is not obvious in most cases.
    3.  The optimization effect of `bitset` is slightly stronger than that of `vector<bool>`.

??? note "Reference code"
    [google/benchmark](https://github.com/google/benchmark) must be installed.
    
    ```cpp
    #include <benchmark/benchmark.h>
    #include <bits/stdc++.h>
    using namespace std;
    using u32 = uint32_t;
    using u64 = uint64_t;
    
    #define ERATOSTHENES_STORAGE_PRIME
    #define ENABLE_EULER
    constexpr u32 N = 5e7 + 1;
    
    #ifndef ERATOSTHENES_STORAGE_PRIME
    
    void Eratosthenes_CArray(benchmark::State &state) {
      static bool is_prime[N];
      for (auto _ : state) {
        fill(is_prime, is_prime + N, true);
        is_prime[0] = is_prime[1] = false;
        for (u32 i = 2; (u64)i * i < N; ++i)
          if (is_prime[i])
            for (u32 j = i * i; j < N; j += i) is_prime[j] = false;
        benchmark::DoNotOptimize(0);
      }
    }
    
    BENCHMARK(Eratosthenes_CArray);
    
    void Eratosthenes_vector(benchmark::State &state) {
      static vector<bool> is_prime(N);
      for (auto _ : state) {
        fill(is_prime.begin(), is_prime.end(), true);
        is_prime[0] = is_prime[1] = false;
        for (u32 i = 2; (u64)i * i < N; ++i)
          if (is_prime[i])
            for (u32 j = i * i; j < N; j += i) is_prime[j] = false;
        benchmark::DoNotOptimize(0);
      }
    }
    
    BENCHMARK(Eratosthenes_vector);
    
    void Eratosthenes_bitset(benchmark::State &state) {
      static bitset<N> is_prime;
      for (auto _ : state) {
        is_prime.set();
        is_prime.reset(0);
        is_prime.reset(1);
        for (u32 i = 2; (u64)i * i < N; ++i)
          if (is_prime[i])
            for (u32 j = i * i; j < N; j += i) is_prime.reset(j);
        benchmark::DoNotOptimize(0);
      }
    }
    
    BENCHMARK(Eratosthenes_bitset);
    
    #else
    
    void Eratosthenes_CArray_sp(benchmark::State &state) {
      static bool is_prime[N];
      for (auto _ : state) {
        vector<u32> prime;
        fill(is_prime, is_prime + N, true);
        is_prime[0] = is_prime[1] = false;
        for (u32 i = 2; (u64)i * i < N; ++i)
          if (is_prime[i])
            for (u32 j = i * i; j < N; j += i) is_prime[j] = false;
        for (u32 i = 2; i < N; ++i)
          if (is_prime[i]) prime.push_back(i);
        benchmark::DoNotOptimize(prime);
      }
    }
    
    BENCHMARK(Eratosthenes_CArray_sp);
    
    void Eratosthenes_vector_sp(benchmark::State &state) {
      static vector<bool> is_prime(N);
      for (auto _ : state) {
        vector<u32> prime;
        fill(is_prime.begin(), is_prime.end(), true);
        is_prime[0] = is_prime[1] = false;
        for (u32 i = 2; (u64)i * i < N; ++i)
          if (is_prime[i])
            for (u32 j = i * i; j < N; j += i) is_prime[j] = false;
        for (u32 i = 2; i < N; ++i)
          if (is_prime[i]) prime.push_back(i);
        benchmark::DoNotOptimize(prime);
      }
    }
    
    BENCHMARK(Eratosthenes_vector_sp);
    
    void Eratosthenes_bitset_sp(benchmark::State &state) {
      static bitset<N> is_prime;
      for (auto _ : state) {
        vector<u32> prime;
        is_prime.set();
        is_prime.reset(0);
        is_prime.reset(1);
        for (u32 i = 2; (u64)i * i < N; ++i)
          if (is_prime[i])
            for (u32 j = i * i; j < N; j += i) is_prime.reset(j);
        for (u32 i = 2; i < N; ++i)
          if (is_prime[i]) prime.push_back(i);
        benchmark::DoNotOptimize(prime);
      }
    }
    
    BENCHMARK(Eratosthenes_bitset_sp);
    
    #endif
    
    #ifdef ENABLE_EULER
    
    void Euler_CArray(benchmark::State &state) {
      static bool not_prime[N];
      for (auto _ : state) {
        vector<u32> prime;
        fill(not_prime, not_prime + N, false);
        not_prime[0] = not_prime[1] = true;
        for (u32 i = 2; i < N; ++i) {
          if (!not_prime[i]) prime.push_back(i);
          for (u32 pri_j : prime) {
            if (i * pri_j >= N) break;
            not_prime[i * pri_j] = true;
            if (i % pri_j == 0) break;
          }
        }
        benchmark::DoNotOptimize(prime);
      }
    }
    
    BENCHMARK(Euler_CArray);
    
    void Euler_vector(benchmark::State &state) {
      static vector<bool> not_prime(N);
      for (auto _ : state) {
        vector<u32> prime;
        fill(not_prime.begin(), not_prime.end(), false);
        not_prime[0] = not_prime[1] = true;
        for (u32 i = 2; i < N; ++i) {
          if (!not_prime[i]) prime.push_back(i);
          for (u32 pri_j : prime) {
            if (i * pri_j >= N) break;
            not_prime[i * pri_j] = true;
            if (i % pri_j == 0) break;
          }
        }
        benchmark::DoNotOptimize(prime);
      }
    }
    
    BENCHMARK(Euler_vector);
    
    void Euler_bitset(benchmark::State &state) {
      static bitset<N> not_prime;
      for (auto _ : state) {
        vector<u32> prime;
        not_prime.reset();
        not_prime.set(0);
        not_prime.set(1);
        for (u32 i = 2; i < N; ++i) {
          if (!not_prime[i]) prime.push_back(i);
          for (u32 pri_j : prime) {
            if (i * pri_j >= N) break;
            not_prime.set(i * pri_j);
            if (i % pri_j == 0) break;
          }
        }
        benchmark::DoNotOptimize(prime);
      }
    }
    
    BENCHMARK(Euler_bitset);
    
    #endif
    
    static void Noop(benchmark::State &state) {
      for (auto _ : state) benchmark::DoNotOptimize(0);
    }
    
    BENCHMARK(Noop);
    BENCHMARK_MAIN();
    ```

### Combining with Tree Decomposition into Blocks

Combining `bitset` with tree decomposition into blocks can solve a class of problems that ask for the union of information on multiple paths in a tree. See [Data Structures / Tree Decomposition into Blocks](../../ds/tree-decompose.md) for details.

### Combining with Mo's Algorithm

See [Miscellaneous / Mo's Algorithm with bitset](../../misc/mo-algo-with-bitset.md) for details.

### Computing High-Dimensional Partial Orders

See [FHR slides](https://github.com/OI-wiki/libs/blob/master/lang/csl/FHR-分块bitset求高维偏序.pdf) for details.

## References and Notes

[^bitset1]: [libstdc++: SGI STL extensions](https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.4/a00994.html#g32541eb0d6581b915af48b5a51006dff)

[^bitset2]: [libstdc++: std::bitset<\_Nb> Class Template Reference](https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.4/a00219.html)
