author: AntiLeaf

The Berlekamp-Massey algorithm is an algorithm for finding the shortest linear recurrence relation of a sequence. Given a sequence of length $n$, if the shortest linear recurrence relation has order $m$, then the Berlekamp-Massey algorithm can find the shortest linear recurrence relation for each prefix of the sequence in $O(nm)$ time. In the worst case $m = O(n)$, so the worst-case time complexity is $O(n^2)$.

### Definitions

Define a recurrence relation of a sequence $\{a_0 \dots a_{n - 1}\}$ as a sequence $\{r_0\dots r_m\}$ satisfying:

$\sum_{j = 0} ^ m r_j a_{i - j} = 0, \forall i \ge m$

where $r_0 = 1$. $m$ is called the **order** of the recurrence relation.

The shortest linear recurrence relation of sequence $\{a_i\}$ is the recurrence relation with the smallest order.

### Algorithm

Slightly different from the definition above, we define a new set of recurrence coefficients $\{f_0 \dots f_{m - 1}\}$ satisfying:

$a_i = \sum_{j = 0} ^ {m - 1} f_j a_{i - j - 1}, \forall i \ge m$

It is easy to see that $f_i = -r_{i + 1}$, and the order $m$ is the same as in the previous definition.

We can compute the recurrence relation incrementally by considering each element of $\{a_i\}$ in order and adjusting the recurrence coefficients $\{f_i\}$ whenever the recurrence result becomes incorrect. For convenience, denote the shortest recurrence relation of the first $i$ elements as $F_i = \{f_{i, j}\}$.

Obviously, initially $F_0 = \{\}$. Assuming the recurrence coefficients $F_{i - 1}$ hold for the first $i - 1$ elements of sequence $\{a_i\}$, there are two cases for the $i$-th element:

1.  The recurrence coefficients also hold for $a_i$, in which case no adjustment is needed and we can simply set $F_i = F_{i - 1}$.
2.  The recurrence coefficients do not hold for $a_i$, in which case we need to adjust $F_{i - 1}$ to get a new $F_i$.

Let $\Delta_i = a_i - \sum_{j = 0} ^ m f_{i - 1, j} a_{i - j - 1}$, which is the difference between $a_i$ and the recurrence result from $F_{i - 1}$.

If this is the first time modifying the recurrence coefficients, it means $a_i$ is the first non-zero element in the sequence. In this case, simply set $F_i$ to $i$ zeros, which is obviously a valid shortest recurrence relation.

Otherwise, let $k$ be the number of elements of $\{a_i\}$ that had been considered when the recurrence coefficients were last modified. If there exists a sequence $G = \{g_0 \dots g_{m' - 1}\}$ satisfying:

$\sum_{j = 0} ^ {m' - 1} g_j a_{i' - j - 1} = 0, \forall i' \in [m', i)$

and $\sum_{j = 0} ^ {m' - 1} g_j a_{i - j - 1} = \Delta_i$, then it is easy to see that adding $F_k$ and $G$ element-wise yields a valid recurrence coefficient $F_i$.

Consider how to construct $G$. One valid construction is

$G = \{0, 0, \dots, 0, \frac{\Delta_i}{\Delta_k}, -\frac{\Delta_i}{\Delta_k}F_{k-1}\}$

where there are $i - k - 1$ zeros at the beginning, and $-\frac{\Delta_i}{\Delta_k} F_{k-1}$ means multiplying each term of $F_{k-1}$ by $-\frac{\Delta_i}{\Delta_k}$ and appending it to the end of the sequence.

It is easy to verify that $\sum_{j = 0} ^ {m' - 1} g_j a_{i - j - 1} = \Delta_k \frac{\Delta_i}{\Delta_k} = \Delta_i$, so this construction yields a valid $G$. We can then set $F_i$ to the element-wise sum of $F_k$ and $G$.

If the recurrence relation $\{r_i\}$ from the original definition is needed, simply negate all $\{f_j\}$ and insert $r_0 = 1$ at the beginning.

From the algorithm described above, if the shortest linear recurrence relation of the sequence has order $m$, then the algorithm's complexity is $O(nm)$. In the worst case $m = O(n)$, so the worst-case complexity is $O(n^2)$.

When implementing the algorithm, since each adjustment of the recurrence coefficients only requires the recurrence coefficients from the previous adjustment $F_k$, if we only need to find the shortest recurrence relation for the entire sequence, we can just store the current recurrence coefficients and the recurrence coefficients from the last adjustment, giving a space complexity of $O(n)$.

??? note "Reference Implementation"
    ```cpp
    vector<int> berlekamp_massey(const vector<int> &a) {
      vector<int> v, last;  // v is the answer, 0-based, p is the module
      int k = -1, delta = 0;
    
      for (int i = 0; i < (int)a.size(); i++) {
        int tmp = 0;
        for (int j = 0; j < (int)v.size(); j++)
          tmp = (tmp + (long long)a[i - j - 1] * v[j]) % p;
    
        if (a[i] == tmp) continue;
    
        if (k < 0) {
          k = i;
          delta = (a[i] - tmp + p) % p;
          v = vector<int>(i + 1);
    
          continue;
        }
    
        vector<int> u = v;
        int val = (long long)(a[i] - tmp + p) * power(delta, p - 2) % p;
    
        if (v.size() < last.size() + i - k) v.resize(last.size() + i - k);
    
        (v[i - k - 1] += val) %= p;
    
        for (int j = 0; j < (int)last.size(); j++) {
          v[i - k + j] = (v[i - k + j] - (long long)val * last[j]) % p;
          if (v[i - k + j] < 0) v[i - k + j] += p;
        }
    
        if ((int)u.size() - i < (int)last.size() - k) {
          last = u;
          k = i;
          delta = a[i] - tmp;
          if (delta < 0) delta += p;
        }
      }
    
      for (auto &x : v) x = (p - x) % p;
      v.insert(v.begin(), 1);
    
      return v;  // $\forall i, \sum_{j = 0} ^ m a_{i - j} v_j = 0$
    }
    ```

The naive Berlekamp-Massey algorithm finds the shortest linear recurrence relation for a finite-length sequence. If the sequence to find the recurrence relation for has infinitely many terms but the upper bound of the order of the shortest recurrence relation is known, we only need to take the first $2m$ terms of the sequence to find the shortest recurrence relation for the entire sequence. (Proof omitted)

### Applications

Since the Berlekamp-Massey algorithm has relatively poor numerical stability, it is rarely used when dealing with real numbers. For the sake of exposition, we assume all operations are performed in the residue field of a prime $p$.

#### Finding the shortest linear recurrence relation for a vector sequence or matrix sequence

To find the shortest linear recurrence relation of a vector sequence $\boldsymbol{v}_i$, let the dimension of the vector be $n$. We can randomly select an $n$-dimensional row vector $\mathbf u^T$ and compute the shortest linear recurrence relation of the scalar sequence $\{\boldsymbol{u}^T\boldsymbol{v}_i\}$. By the Schwartz-Zippel lemma, the two shortest linear recurrence relations are the same with probability at least $1 - \frac n p$.

Finding the shortest linear recurrence relation for a matrix sequence $\{A_i\}$ is similar. Let the size of the matrix be $n \times m$. We only need to randomly select a $1 \times n$ row vector $\mathbf u^T$ and an $m \times 1$ column vector $\boldsymbol{v}$, and compute the shortest linear recurrence relation of the scalar sequence $\{\boldsymbol{u}^T A_i \boldsymbol{v}\}$. By the Schwartz-Zippel lemma, we can similarly obtain that the two are the same with probability at least $1 - \frac{n + m} p$.

#### Optimizing matrix exponentiation

Let $\boldsymbol{f}_i$ be an $n$-dimensional column vector, and the transition satisfies $\boldsymbol{f}_i = A \boldsymbol{f}_{i - 1}$. Then we can see that $\{\boldsymbol{f}_i\}$ is a linear recurrence vector sequence of order at most $n$. (Proof omitted)

We can directly compute $\boldsymbol{f}_0 \dots \boldsymbol{f}_{2n - 1}$ by brute force, then use the method described above to find the shortest linear recurrence relation of $\{\boldsymbol{f}_i\}$, and finally invoke [linear recurrence with constant coefficients](./poly/linear-recurrence.md).

If the vector we need is $\boldsymbol{f}_m$, the complexity of the algorithm is $O(n^3 + n\log n \log m)$. If $A$ is a sparse matrix with only $k$ non-zero entries, the complexity can be reduced to $O(nk + n\log n \log m)$. However, since the algorithm requires at least $O(nk)$ time for preprocessing, the linear recurrence algorithm with $O(n^2 \log m)$ can also be used when the pressure is not too high, and the complexity is still acceptable.

#### Finding the minimal polynomial of a matrix

The minimal polynomial of a square matrix $A$ is the polynomial $f$ with the smallest degree such that $f(A) = 0$.

In fact, the minimal polynomial is exactly the shortest linear recurrence relation of $\{A^i\}$, so we can directly call the Berlekamp-Massey algorithm. If $A$ is an $n \times n$ matrix, the degree of the minimal polynomial is obviously at most $n$.

The bottleneck is computing $A^i$, because if we directly perform matrix multiplication each time, the complexity reaches $O(n^4)$. However, considering that when finding the shortest linear recurrence relation of a matrix sequence, we are actually finding the shortest linear recurrence relation of $\{\boldsymbol{u}^T A^i \boldsymbol{v}\}$, we only need to compute $A^i \boldsymbol{v}$.

Assuming $A$ has $k$ non-zero entries, the complexity is $O(kn + n^2)$.

#### Finding the determinant of a sparse matrix

If we can find the characteristic polynomial of a square matrix $A$, then the constant term multiplied by $(-1)^n$ is the determinant. However, the minimal polynomial is not necessarily the characteristic polynomial.

In fact, if we multiply $A$ by a random diagonal matrix $B$, then the minimal polynomial of $AB$ is the characteristic polynomial with probability at least $1 - \frac {2n^2 - n} p$. Finally, we divide by $\text{det}\;B$.

Let $A$ be an $n \times n$ matrix with $k$ non-zero entries, then the complexity is $O(kn + n ^ 2)$.

#### Finding the rank of a sparse matrix

Let $A$ be an $n\times m$ matrix. First, randomly select an $n\times n$ diagonal matrix $P$ and an $m\times m$ diagonal matrix $Q$, then compute the minimal polynomial of $Q A P A^T Q$.

In fact, we do not need to call matrix multiplication, because when finding the minimal polynomial we need to multiply $Q A P A^T Q$ by a vector, so we can multiply these matrices onto the vector one by one. The answer is the degree of the minimal polynomial after removing all factors of $x$.

Let $A$ have $k$ non-zero entries and $n \le m$, then the complexity is $O(kn + n ^ 2)$.

#### Solving sparse systems of equations

**Problem**: Given $A \mathbf x = \mathbf b$, where $A$ is a **full-rank** $n \times n$ sparse matrix, $\mathbf b$ and $\mathbf x$ are $1\times n$ column vectors. $A, \mathbf b$ are known, and we need to solve for $x$ with complexity lower than $n^\omega$.

**Solution**: Obviously $\mathbf x = A^{-1} \mathbf b$. If we can find the shortest linear recurrence relation $\{r_0 \dots r_{m - 1}\}$ ($m \le n$) of $\{A^i \mathbf b\}$ ($i \ge 0$), then we have the conclusion

$A^{-1} \mathbf b = -\frac 1 {r_{m - 1}} \sum_{i = 0} ^ {m - 2} A^i \mathbf b r_{m - 2 - i}$

(Proof omitted)

Since $A$ is a sparse matrix, we can directly compute $\mathbf b \dots A^{2n - 1} \mathbf b$ by recurrence according to the definition.

Similarly, let $A$ have $k$ non-zero entries, then the complexity is $O(kn + n^2)$.

??? note "Reference Implementation"
    ```cpp
    vector<int> solve_sparse_equations(const vector<tuple<int, int, int>> &A,
                                       const vector<int> &b) {
      int n = (int)b.size();  // 0-based
    
      vector<vector<int>> f({b});
    
      for (int i = 1; i < 2 * n; i++) {
        vector<int> v(n);
        auto &u = f.back();
    
        for (auto [x, y, z] : A)  // [x, y, value]
          v[x] = (v[x] + (long long)u[y] * z) % p;
    
        f.push_back(v);
      }
    
      vector<int> w(n);
      mt19937 gen;
      for (auto &x : w) x = uniform_int_distribution<int>(1, p - 1)(gen);
    
      vector<int> a(2 * n);
      for (int i = 0; i < 2 * n; i++)
        for (int j = 0; j < n; j++) a[i] = (a[i] + (long long)f[i][j] * w[j]) % p;
    
      auto c = berlekamp_massey(a);
      int m = (int)c.size();
    
      vector<int> ans(n);
    
      for (int i = 0; i < m - 1; i++)
        for (int j = 0; j < n; j++)
          ans[j] = (ans[j] + (long long)c[m - 2 - i] * f[i][j]) % p;
    
      int inv = power(p - c[m - 1], p - 2);
    
      for (int i = 0; i < n; i++) ans[i] = (long long)ans[i] * inv % p;
    
      return ans;
    }
    ```

### Practice Problems

1.  [LibreOJ #163. Gaussian Elimination 2](https://loj.ac/p/163)
2.  [ICPC2021 Taipei Gym103443E. Composition with Large Red Plane, Yellow, Black, Gray, and Blue](https://codeforces.com/gym/103443/problem/E)
