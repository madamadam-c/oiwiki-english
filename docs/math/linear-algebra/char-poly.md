This section studies only square matrices, as linear transformations corresponding to a matrix $A$ map $n$ vectors to $n$ vectors.

In practical problems, we often consider repeated transformations. If we only describe that "the linear transformation corresponding to matrix $A$ maps the identity matrix $I$ to $A$", it becomes abstract. The best approach is to find "fixed points", i.e., parts that remain unchanged under the transformation.

However, in practice, the linear transformation corresponding to matrix $A$ may have no fixed points, so we settle for finding parts that are collinear or undergo simple deformations.

## Eigenvalues and Eigenvectors

Under the linear transformation corresponding to matrix $A$, some vectors do not change direction, only scale.

Let $V$ be a vector space over $F$, and $T$ be a linear transformation on $V$. If there exists $\lambda$ in $F$ and a **non-zero vector** $\xi$ in $V$ such that:

$$
T\xi=\lambda\xi
$$

then $\lambda$ is called an **eigenvalue** of $T$, and $\xi$ is called an **eigenvector of $T$ belonging to eigenvalue $\lambda$**.

Eigenvectors lie on the same line; under linear transformations, they maintain their direction (being compressed to zero is also considered as not changing direction). Eigenvectors are not unique; any vector collinear with an eigenvector is also an eigenvector. However, the zero vector is not an eigenvector. Vectors with direction are naturally non-zero. The eigenvalue of an eigenvector is the factor by which it is scaled.

In applications, for eigenvectors with the same eigenvalue, we typically select a basis as their representative set.

Let $\alpha_1,\alpha_2,\cdots,\alpha_n$ be a basis of $V$, and $T$ have matrix $A$ with respect to this basis, i.e.:

$$
T(\alpha_1,\alpha_2,\cdots,\alpha_n)=(\alpha_1,\alpha_2,\cdots,\alpha_n)A
$$

Let $\lambda_0$ be an eigenvalue of $T$, and $\xi$ be an eigenvector of $T$ belonging to $\lambda_0$. Let a non-zero vector $X$ satisfy:

$$
\xi=(\alpha_1,\alpha_2,\cdots,\alpha_n)X
$$

Then we have:

$$
T\xi=\lambda_0\xi
$$

$$
T(\alpha_1,\alpha_2,\cdots,\alpha_n)X=\lambda_0(\alpha_1,\alpha_2,\cdots,\alpha_n)X
$$

$$
(\alpha_1,\alpha_2,\cdots,\alpha_n)AX=\lambda_0(\alpha_1,\alpha_2,\cdots,\alpha_n)X
$$

$$
AX=\lambda_0X
$$

$$
(A-\lambda_0I)X=0
$$

Therefore, the corresponding determinant is also $0$.

## Characteristic Polynomial

Consider an $n \times n$ matrix $A$, where $n \geq 0 \land n \in \mathbb{Z}$. Let $\lambda$ be a parameter. The matrix $\lambda I - A$ is called the **characteristic matrix** of $A$.

The determinant of the characteristic matrix is called the **characteristic polynomial** of $A$. When expanded, it is an $n$-degree polynomial with roots equal to the eigenvalues of $A$, denoted $p_A(\lambda)$:

$$
p_A(\lambda)=\det(\lambda I_n-A)=\begin{vmatrix}
\lambda-a_{11} & -a_{12} &  \cdots & -a_{1n} \\
-a_{21} & \lambda-a_{22} &  \cdots & -a_{2n} \\
\vdots & \vdots &  & \vdots  \\
-a_{n1} & -a_{n2} &  \cdots & \lambda-a_{nn} \\
\end{vmatrix}
$$

where $I_n$ is an $n \times n$ identity matrix. Some sources define $p_A(\lambda)=\det(A-\lambda I_n)$, which differs from our definition by a sign $(-1)^n$, but using this definition ensures $p_A(\lambda)$ is always monic, whereas the other definition is monic only when $n$ is even. Note that the determinant of a $0 \times 0$ matrix is $1$, which is well-defined.

The non-zero solution vectors $X$ of $(\lambda_0 I-A)X=0$ are called eigenvectors of $A$ belonging to $\lambda_0$.

The linear transformation $T$ has eigenvalue $\lambda_0$ if and only if matrix $A$ has eigenvalue $\lambda_0$.

The linear transformation $T$ has eigenvector $\xi$ if and only if matrix $A$ has eigenvector $X$, where:

$$
\xi=(\alpha_1,\cdots,\alpha_n)X
$$

By the fundamental theorem of algebra, the characteristic polynomial can be factored as:

$$
f(\lambda)=|\lambda I-A|={(\lambda-\lambda_1)}^{d_1}\cdots{(\lambda-\lambda_m)}^{d_m}
$$

$d_i$ is called the **algebraic multiplicity** of eigenvalue $\lambda_i$. The sum of all algebraic multiplicities equals the dimension of the space $n$.

### Finding All Eigenvalues and Eigenvectors of a Matrix

Follow these steps:

-   Compute the determinant $|\lambda I-A|$.
-   Find all roots of the polynomial $f(\lambda)=|\lambda I-A|$ in the field $F$, i.e., the eigenvalues of $A$.
-   For each eigenvalue $\lambda$ of $A$, solve the homogeneous linear system $(\lambda I-A)X=0$, and find a fundamental set of solutions $X_1,\cdots,X_t$. Then all eigenvectors of $A$ belonging to $\lambda$ are:

$$
k_1X_1+k_2X_2+\cdots+k_tX_t
$$

where not all $k_i$ are zero.

-   The eigenvectors of linear transformation $T$ belonging to $\lambda$ are:

$$
\xi_i=(\alpha_1,\cdots,\alpha_n)X_i
$$

Therefore, all eigenvectors belonging to $\lambda$ are:

$$
k_1\xi_1+k_2\xi_2+\cdots+k_t\xi_t
$$

where not all $k_i$ are zero.

The existence of eigenvalues and eigenvectors depends on the field of $V$.

## Similar Transformations

### Introduction

If an $n \times n$ matrix $A$ is an upper triangular matrix, such as:

$$
A=
\begin{bmatrix}
a_{1,1}&a_{1,2}&\cdots &a_{1,n}\\
&a_{2,2}&\cdots &a_{2,n}\\
&&\ddots &\vdots \\
&&&a_{n,n}
\end{bmatrix}
$$

Then

$$
\begin{aligned}
p_A(x)&=\det(xI_n-A)\\
&=
\begin{bmatrix}
x-a_{1,1}&-a_{1,2}&\cdots &-a_{1,n}\\
&x-a_{2,2}&\cdots &-a_{2,n}\\
&&\ddots &\vdots \\
&&&x-a_{n,n}
\end{bmatrix}
\\
&=\prod_{i=1}^n(x-a_{i,i})
\end{aligned}
$$

which can be easily obtained. Lower triangular matrices are similar. However, if $A$ is not one of these two types, we need to use similarity transformations to make the matrix easier for finding the characteristic polynomial.

### Definition

For $n \times n$ matrices $A$ and $B$, if there exists an invertible $n \times n$ matrix $P$ such that:

$$
B=P^{-1}AP
$$

then matrices $A$ and $B$ are similar. The transformation $A \mapsto P^{-1}AP$ is called a similarity transformation. Also, $A$ and $P^{-1}AP$ have the same characteristic polynomial.

Consider:

$$
\begin{aligned}
\det(xI_n-P^{-1}AP)&=\det(xP^{-1}I_nP-P^{-1}AP)\\
&=\det(P^{-1}xI_nP-P^{-1}AP)\\
&=\det(P^{-1})\cdot \det(P)\cdot \det(xI_n-A)\\
&=\det(xI_n-A)\\
&=p_A(x)
\end{aligned}
$$

The proof is complete. Similarly for $A \mapsto PAP^{-1}$. Also, $p_A(0)=(-1)^n\cdot \det(A)$, because $p_A(0)=\det(-1\cdot I_nA)=\det(-1\cdot I_n)\cdot \det(A)$, hence $\det(A)=\det(P^{-1}AP)$.

**Theorem:** Similar matrices have the same characteristic polynomial and eigenvalues, but not conversely.

This theorem states that the characteristic polynomial of the matrix of a linear transformation is independent of the choice of basis, and is directly determined by the linear transformation itself. Hence, it can be called the characteristic polynomial of the linear transformation.

The characteristic polynomial $f(\lambda)=|\lambda I-A|$ of matrix $A$ is monic. By Vieta's formulas, the coefficient of the $(n-1)$-th degree term is:

$$
-(\lambda_1+\cdots+\lambda_n)=-(a_{11}+\cdots+a_{nn})=-tr A
$$

where $tr A$ is called the trace of $A$, the sum of elements on the main diagonal.

By Vieta's formulas, the constant term of the characteristic polynomial is:

$$
{(-1)}^n|A|={(-1)}^n(\lambda_1\cdots\lambda_n)
$$

**Theorem:** Similar matrices have the same trace.

### Commutation Formula

**Theorem:** Regardless of whether matrices $A$ and $B$ are square or not, as long as multiplication is possible, the trace of $AB$ equals the trace of $BA$.

One proof is direct expansion, which completes the proof. Another proof uses the commutation formula.

**Theorem:** Let $A$ be an $m \times n$ matrix, and $B$ be an $n \times m$ matrix. Then:

$$
\lambda^n|\lambda I_m-AB|=\lambda^m|\lambda I_n-BA|
$$

This formula shows that $AB$ and $BA$ have the same non-zero eigenvalues.

### Schur's Lemma

Any $n \times n$ matrix $A$ is similar to an upper triangular matrix. That is, there exists a full-rank matrix $P$ such that $P^{-1}AP$ is an upper triangular matrix, with its main diagonal elements being all eigenvalues of $A$.

**Corollary:** Let the $n$ eigenvalues of $A$ be $\lambda_1,\cdots,\lambda_n$, and $\phi(x)$ be any polynomial. Then the $n$ eigenvalues of the matrix polynomial $\phi(A)$ are:

$$
\phi(\lambda_1),\cdots,\phi(\lambda_n)
$$

In particular, the eigenvalues of $kA$ are $k\lambda_1,\cdots,k\lambda_n$, and the eigenvalues of $A^m$ are ${\lambda_1}^m,\cdots,{\lambda_n}^m$.

### Similarity Transformations Using Gaussian Elimination

For an $n \times n$ matrix $B$, Gaussian elimination can be applied, with basic operations being elementary row operations.

Performing these operations on a matrix (left multiplication by elementary matrices) followed by right multiplication by their inverses is a similarity transformation. Left multiplication corresponds to row operations; similarly, right multiplication corresponds to column operations.

If a matrix can be transformed into an upper or lower triangular form via similarity transformations, then its characteristic polynomial can be easily obtained. However, if we apply the transformation $A\mapsto T_{ij}(k)AT_{ij}(-k)$ to elements on the subdiagonal, after eliminating element at row $i$, column $j$ of $A$ using $A\mapsto T_{ij}(k)A$, right multiplying by $T_{ij}(-k)$ will add $-k$ times column $i$ to column $j$, which may cause previously zeroed elements to become non-zero. This may prevent the matrix from being transformed into upper or lower triangular form.

Later, we will show that after applying transformations to elements on the subdiagonal, the resulting matrix can still easily yield the characteristic polynomial.

### Upper Hessenberg Matrix

For $n > 2$, matrices of the form:

$$
H=
\begin{bmatrix}
\alpha_{1}&h_{12}&\dots&\dots&h_{1n}\\
\beta_{2}&\alpha_{2}&h_{23}&\dots &\vdots \\
&\ddots &\ddots & \ddots &\vdots \\
& &\ddots &\ddots & h_{(n-1)n}\\
&&& \beta_{n}& \alpha_{n}
\end{bmatrix}
$$

are called upper Hessenberg matrices, where $\beta$ is the subdiagonal.

We use similarity transformations to zero out all elements below the subdiagonal to obtain an upper Hessenberg matrix. Computing the characteristic polynomial of an $n \times n$ upper Hessenberg matrix can be done in $O(n^3)$ time.

Let $H_i$ be the matrix consisting of only the first $i$ rows and first $i$ columns of $H$, and $p_i(x)=\det(xI_i-H_i)$. Then:

$$
H_0=
\begin{bmatrix}
\end{bmatrix},\quad
p_0(x)=1
$$

$$
H_1=
\begin{bmatrix}
\alpha_1
\end{bmatrix},\quad
p_1(x)=\det(x I_1-H_1)=x -\alpha_1
$$

$$
H_2=
\begin{bmatrix}
\alpha_1&h_{12}\\
\beta_2&\alpha_2
\end{bmatrix},\quad
p_2(x)=\det(xI_2-H_2)=(x-\alpha_2)p_1(x)-\beta_2h_{12}p_0(x)
$$

When computing determinants, we generally expand along the row or column with the most zeros. A minor is the matrix obtained by deleting the row and column of the selected element. Here, we choose to expand along the last row:

$$
\begin{aligned}
p_3(x)&=
\det(xI_3-H_3)\\
&=\begin{vmatrix}
x-\alpha_1&-h_{12}&-h_{13}\\
-\beta_2&x-\alpha_2&-h_{23}\\
&-\beta_3&x-\alpha_3
\end{vmatrix}\\
&=(x-\alpha_3)\cdot (-1)^{3+3}p_2(x)-\beta_3\cdot (-1)^{3+2}
\begin{vmatrix}
x-\alpha_1&-h_{13}\\
-\beta_2&-h_{23}
\end{vmatrix}\\
&=(x-\alpha_3)p_2(x)-\beta_3(h_{23}p_1(x)+\beta_2h_{13}p_0(x))
\end{aligned}
$$

By observation and induction, for $2\leq i\leq n$:

$$
p_i(x)=(x-\alpha_i)p_{i-1}(x)-
\sum_{m=1}^{i-1}h_{i-m,i}
\left(
\prod_{j=i-m+1}^{i}\beta_j
\right)
p_{i-m-1}(x)
$$

This completes the algorithm, commonly known as the Hessenberg algorithm.

## Cayley–Hamilton Theorem

For any $n \times n$ matrix $A$, with characteristic polynomial $f(\lambda)=|\lambda I-A|$, we have $f(A)=0$.

For a linear transformation $T$, there is a parallel result: if $f(\lambda)$ is the characteristic polynomial of $T$, then $f(T)$ is the zero transformation.

By this theorem, for any matrix $A$, there exists a polynomial that annihilates it.

## Minimal Polynomial

Let $V$ be an $n$-dimensional vector space. Since the matrix corresponding to a linear transformation has $n^2$ elements, all linear transformations form an $n^2$-dimensional vector space.

For a specific linear transformation $T$, from the 0-th application to the $n$-th application, there are $n^2+1$ linear transformations. Their corresponding matrices are necessarily linearly dependent. Thus, there exists a non-zero polynomial $f$ such that $f(T)$ is the zero transformation. We say transformation $T$ satisfies polynomial $f$. Among all polynomials $f$ that $T$ satisfies, there exists one of minimum degree.

The monic polynomial of minimum degree that annihilates matrix $A$ is called the minimal polynomial of $A$, denoted $m_A(\lambda)$.

By the Euclidean algorithm for polynomials, the minimal polynomial is unique and divides any polynomial that annihilates $A$. In particular, the minimal polynomial divides the characteristic polynomial.

**Theorem:** (not counting multiplicities) the characteristic polynomial $f(\lambda)$ and minimal polynomial $m_A(\lambda)$ of matrix $A$ have the same roots.

**Theorem:** Eigenvectors of matrix $A$ belonging to distinct eigenvalues are linearly independent.

## Applications

In informatics, we usually consider matrices over $(\mathbb{Z}/m\mathbb{Z})^{n\times n}$, where $m$ is often a prime. Performing similarity transformations is straightforward in this case. When $m$ is composite, we can consider a method similar to the Euclidean algorithm.

??? note "Implementation"
    ```cpp
    #include <cassert>
    #include <iostream>
    #include <random>
    #include <vector>
    
    using Matrix = std::vector<std::vector<int>>;
    using i64 = int64_t;
    
    Matrix to_upper_Hessenberg(const Matrix &M, int mod) {
      Matrix H(M);
      int n = H.size();
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if ((H[i][j] %= mod) < 0) H[i][j] += mod;
        }
      }
      for (int i = 0; i < n - 1; ++i) {
        int pivot = i + 1;
        for (; pivot < n; ++pivot) {
          if (H[pivot][i] != 0) break;
        }
        if (pivot == n) continue;
        if (pivot != i + 1) {
          for (int j = i; j < n; ++j) std::swap(H[i + 1][j], H[pivot][j]);
          for (int j = 0; j < n; ++j) std::swap(H[j][i + 1], H[j][pivot]);
        }
        for (int j = i + 2; j < n; ++j) {
          for (;;) {
            if (H[j][i] == 0) break;
            if (H[i + 1][i] == 0) {
              for (int k = i; k < n; ++k) std::swap(H[i + 1][k], H[j][k]);
              for (int k = 0; k < n; ++k) std::swap(H[k][i + 1], H[k][j]);
              break;
            }
            if (H[j][i] >= H[i + 1][i]) {
              int q = H[j][i] / H[i + 1][i], mq = mod - q;
              for (int k = i; k < n; ++k)
                H[j][k] = (H[j][k] + i64(mq) * H[i + 1][k]) % mod;
              for (int k = 0; k < n; ++k)
                H[k][i + 1] = (H[k][i + 1] + i64(q) * H[k][j]) % mod;
            } else {
              int q = H[i + 1][i] / H[j][i], mq = mod - q;
              for (int k = i; k < n; ++k)
                H[i + 1][k] = (H[i + 1][k] + i64(mq) * H[j][k]) % mod;
              for (int k = 0; k < n; ++k)
                H[k][j] = (H[k][j] + i64(q) * H[k][i + 1]) % mod;
            }
          }
        }
      }
      return H;
    }
    
    std::vector<int> get_charpoly(const Matrix &M, int mod) {
      Matrix H(to_upper_Hessenberg(M, mod));
      int n = H.size();
      std::vector<std::vector<int>> p(n + 1);
      p[0] = {1 % mod};
      for (int i = 1; i <= n; ++i) {
        const std::vector<int> &pi_1 = p[i - 1];
        std::vector<int> &pi = p[i];
        pi.resize(i + 1, 0);
        int v = mod - H[i - 1][i - 1];
        if (v == mod) v -= mod;
        for (int j = 0; j < i; ++j) {
          pi[j] = (pi[j] + i64(v) * pi_1[j]) % mod;
          if ((pi[j + 1] += pi_1[j]) >= mod) pi[j + 1] -= mod;
        }
        int t = 1;
        for (int j = 1; j < i; ++j) {
          t = i64(t) * H[i - j][i - j - 1] % mod;
          int prod = i64(t) * H[i - j - 1][i - 1] % mod;
          if (prod == 0) continue;
          prod = mod - prod;
          for (int k = 0; k <= i - j - 1; ++k)
            pi[k] = (pi[k] + i64(prod) * p[i - j - 1][k]) % mod;
        }
      }
      return p[n];
    }
    
    bool verify(const Matrix &M, const std::vector<int> &charpoly, int mod) {
      if (mod == 1) return true;
      int n = M.size();
      std::vector<int> randvec(n), sum(n, 0);
      std::mt19937 gen(std::random_device{}());
      std::uniform_int_distribution<int> dis(1, mod - 1);
      for (int i = 0; i < n; ++i) randvec[i] = dis(gen);
      for (int i = 0; i <= n; ++i) {
        int v = charpoly[i];
        for (int j = 0; j < n; ++j) sum[j] = (sum[j] + i64(v) * randvec[j]) % mod;
        std::vector<int> prod(n, 0);
        for (int j = 0; j < n; ++j) {
          for (int k = 0; k < n; ++k) {
            prod[j] = (prod[j] + i64(M[j][k]) * randvec[k]) % mod;
          }
        }
        randvec.swap(prod);
      }
      for (int i = 0; i < n; ++i)
        if (sum[i] != 0) return false;
      return true;
    }
    
    int main() {
      std::ios::sync_with_stdio(false);
      std::cin.tie(nullptr);
      int n, mod;
      std::cin >> n >> mod;
      Matrix M(n, std::vector<int>(n));
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) std::cin >> M[i][j];
      std::vector<int> charpoly(get_charpoly(M, mod));
      for (int i = 0; i <= n; ++i) std::cout << charpoly[i] << ' ';
      assert(verify(M, charpoly, mod));
      return 0;
    }
    ```

The above Hessenberg algorithm does not have numerical stability, so matrices over $\mathbb{R}^{n\times n}$ need to be adjusted using other algorithms or alternative numerically stable algorithms before use.

We can connect the characteristic polynomial with constant-coefficient homogeneous linear recurrences, and combine the Cayley–Hamilton theorem with polynomial modular arithmetic to accelerate algorithms for computing matrix powers over certain fields.

The Cayley–Hamilton theorem states:

$$
\begin{aligned}
p_A(A)&=A^n+c_1A^{n-1}+\cdots +c_{n-1}A+c_nI\\
&=O
\end{aligned}
$$

where $O$ is the $n \times n$ zero matrix, $A\in\mathbb{C}^{n\times n}$, and $p_A(x)=x^n+\sum_{i=1}^nc_ix^{n-i}\in\mathbb{C}[x]$ is the characteristic polynomial of $A$.

If we want to compute $A^K$ where $K$ is large, we can find $f(x)=x^K\bmod{p_A(x)}$ and then use $f(A)=A^K$.

Since $\deg(f(x))\lt n$. Let $f(x)=\sum_{i=0}^{n-1}f_ix^i$ and $n=km$. Then:

$$
\begin{aligned}
f_{km-1}x^{km-1}+\cdots +f_1x+f_0&=(\cdots (f_{km-1}x^{k-1}+\cdots +f_{k(m-1)})x^k\\
&+f_{k(m-1)-1}x^{k-1}+\cdots +f_{k(m-2)})x^k\\
&+\cdots\\
&+f_{k-1}x^{k-1}+\cdots +f_1x+f_0
\end{aligned}
$$

Let $k=\sqrt{n}$. We can see that computing $f(A)$ requires approximately $O(\sqrt{n})$ matrix-matrix multiplications.

## References

-   Rizwana Rehman, Ilse C.F. Ipsen. [La Budde's Method for Computing Characteristic Polynomials](https://ipsen.math.ncsu.edu/ps/charpoly3.pdf).
-   Marshall Law. [Computing Characteristic Polynomials of Matrices of Structured Polynomials](http://summit.sfu.ca/system/files/iritems1/17301/etd10125_.pdf).
-   Mike Paterson. [On the Number of Nonscalar Multiplications Necessary to Evaluate Polynomials](https://epubs.siam.org/doi/10.1137/0202007).