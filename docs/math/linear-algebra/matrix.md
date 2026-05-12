This article introduces a very important content in linear algebra — matrices, mainly covering properties, operations, and some applications of matrix multiplication.

## Vectors and Matrices

In linear algebra, vectors are divided into column vectors and row vectors.

???+ warning "Warning"
    In Taiwan, the translations of "column" and "row" are opposite to those in mainland China. In **OI Wiki**, following mainland China's conventions, we use "column" and "row" consistently with mainland terminology.

The main research objects in linear algebra are column vectors, denoted with bold lowercase letters. When many vectors and matrices are involved in linear algebra, and when it does not cause confusion, the vector notation above letters can be omitted when writing by hand.

Vectors are also special matrices. If you want to represent a row vector, write the transpose symbol in the upper right of the bold lowercase letter. Row vectors generally represent equations in linear algebra.

## Introduction

The introduction of matrices comes from linear systems. Like vectors, matrices embody an idea of "packaging" data.

For example, for the linear system:

$$
\begin{equation}
    \begin{cases}
        7x_1+8x_2+9x_3=13 \\
        4x_1+5x_2+6x_3=12 \\
        x_1+2x_2+3x_3=11
    \end{cases}
\end{equation}
$$

Matrices are generally represented using parentheses or brackets. Extract the coefficients above to write it in matrix multiplication form:

$$
\begin{equation}
    \begin{pmatrix}
        7 & 8 & 9 \\
        4 & 5 & 6 \\
        1 & 2 & 3
    \end{pmatrix}\begin{pmatrix}
        x_1 \\ x_2 \\ x_3
    \end{pmatrix}=\begin{pmatrix}
      13 \\ 12 \\ 11
    \end{pmatrix}
\end{equation}
$$

Written succinctly as:

$$
Ax=b
$$

That is, the column vector of unknowns x left-multiplied by matrix A, gives the column vector b. This form can be considered the fundamental form of linear algebra.

The main operation model studied in linear algebra is the inner product. The inner product is first multiply then add: a row vector left-multiplies a column vector to get a scalar.

Matrix multiplication is an extension of the inner product. Matrix multiplication is equivalent to taking a row from the left matrix and a column from the right matrix, computing their inner product to get the corresponding element in the result matrix. The mnemonic is "left row, right column".

When the object of study is the column vector on the right, matrix multiplication corresponds to left-multiplying the column vector. From the left-multiplying perspective, a matrix is a transformation of column vectors: it transforms each column vector of the right matrix into the corresponding column vector in the result matrix.

A matrix can transform a single column vector, or a "packaged" group of column vectors, or even an entire space — i.e., the set of all column vectors. When a matrix is regarded as transforming the entire space, it leaves the space and becomes a pure transformation.

## Definitions

For a matrix $A$, the main diagonal refers to elements $A_{i,i}$.

The identity matrix is generally denoted by $I$, with 1's on the main diagonal and 0's elsewhere.

### Same-shaped Matrices

Two matrices with the same number of rows and columns are called same-shaped matrices.

### Square Matrix

A matrix with equal number of rows and columns is called a square matrix. A square matrix is a special type of matrix. The common expression "order $n$ matrix" actually refers to an $n \times n$ square matrix. Square matrices of the same order are same-shaped matrices.

When studying linear systems, vector sets, and matrix rank, general matrices are used. When studying eigenvalues and eigenvectors, and quadratic forms, square matrices are used.

#### Main Diagonal

Elements where row number equals column number in a square matrix form the main diagonal.

#### Symmetric Matrix

If elements of a square matrix are symmetric about the main diagonal, i.e., for any $i$ and $j$, the element at row $i$, column $j$ equals the element at row $j$, column $i$, then the square matrix is called a symmetric matrix.

#### Diagonal Matrix

A square matrix with all elements outside the main diagonal equal to $0$ is called a diagonal matrix, generally denoted:

$$
\operatorname{diag}\{\lambda_1,\cdots,\lambda_n\}
$$

where $\lambda_1,\cdots,\lambda_n$ are elements on the main diagonal.

A diagonal matrix is a symmetric matrix.

If all elements of a diagonal matrix are $1$, it's called the identity matrix, denoted $I$. As long as multiplication is possible, regardless of shape, any matrix multiplied by the identity matrix remains unchanged.

#### Triangular Matrix

If all elements below the main diagonal of a square matrix are $0$, it's called an upper triangular matrix. If all elements above the main diagonal are $0$, it's called a lower triangular matrix.

The product of two upper (lower) triangular matrices is still upper (lower) triangular. If all diagonal elements are non-zero, the upper (lower) triangular matrix is invertible, and its inverse is also upper (lower) triangular.

#### Unit Triangular Matrix

If the diagonal of an upper triangular matrix $A$ are all $1$, $A$ is called a unit upper triangular matrix. If the diagonal of a lower triangular matrix $A$ are all $1$, $A$ is called a unit lower triangular matrix.

The product of two unit upper (lower) triangular matrices is still unit upper (lower) triangular, and the inverse of a unit upper (lower) triangular matrix is also unit upper (lower) triangular.

## Operations

### Matrix Linear Operations

Matrix linear operations include addition/subtraction and scalar multiplication, which are element-wise. Only same-shaped matrices can be added or subtracted element-wise.

### Matrix Transpose

The transpose of a matrix is denoted with a "T" superscript, representing the interchange of rows and columns.

A symmetric matrix remains unchanged after transpose.

### Matrix Multiplication

Matrix multiplication is an extension of the inner product of vectors.

Matrix multiplication is only defined when the number of columns of the first matrix equals the number of rows of the second matrix.

Let $A$ be a $P \times M$ matrix, $B$ be an $M \times Q$ matrix, and $C$ be the product of $A$ and $B$.

The element at row $i$, column $j$ of matrix $C$ can be expressed as:

$$
C_{i,j} = \sum_{k=1}^MA_{i,k}B_{k,j}
$$

In matrix multiplication, the element at row $i$, column $j$ of the result matrix $C$ is obtained by **multiplying and then adding** the $M$ numbers from row $i$ of matrix $A$ with the $M$ numbers from column $j$ of matrix $B$. Here, "multiply and add" is the inner product of vectors. The element at row $i$, column $j$ of the product matrix is exactly the inner product of row vector $i$ of matrix $A$ and column vector $j$ of matrix $B$. The mnemonic is **left row, right column**.

The vectors in linear algebra are mostly column vectors. By this definition of matrix multiplication, we often study the left-multiplying operation of a matrix on column vectors. From this, we can also see the idea of "packaging": processing many vector inner products simultaneously.

Matrix multiplication satisfies the associative law, but not the general commutative law.

Using the associative law, matrix multiplication can be optimized using the idea of [binary exponentiation](../binary-exponentiation.md).

In contests, since linear recurrence relations can be expressed in matrix multiplication form, matrix exponentiation is often used to find a particular term of a linear recurrence sequence.

#### Optimization

First, for relatively small matrices, you can manually unroll the loops to reduce constants.

You can reorder loops to improve spatial locality. This optimization does not change the time complexity of matrix multiplication but yields constant-level improvements.

```cpp
// Instead of the following
mat operator*(const mat& T) const {
  mat res;
  for (int i = 0; i < sz; ++i)
    for (int j = 0; j < sz; ++j)
      for (int k = 0; k < sz; ++k) {
        res.a[i][j] += mul(a[i][k], T.a[k][j]);
        res.a[i][j] %= MOD;
      }
  return res;
}

// Use:
mat operator*(const mat& T) const {
  mat res;
  int r;
  for (int i = 0; i < sz; ++i)
    for (int k = 0; k < sz; ++k) {
      r = a[i][k];
      for (int j = 0; j < sz; ++j)
        res.a[i][j] += T.a[k][j] * r, res.a[i][j] %= MOD;
    }
  return res;
}
```

### Inverse of a Square Matrix

The inverse matrix $P$ of a square matrix $A$ is a matrix such that $A \times P = I$.

The inverse does not always exist. If it exists, it can be solved using [Gaussian elimination](../numerical/gauss.md).

### Determinant of a Square Matrix

The determinant is an operation on square matrices.

## Reference Code

Generally, you can use a 2D array to simulate a matrix.

```cpp
struct mat {
  LL a[sz][sz];

  mat() { memset(a, 0, sizeof a); }

  mat operator-(const mat& T) const {
    mat res;
    for (int i = 0; i < sz; ++i)
      for (int j = 0; j < sz; ++j) {
        res.a[i][j] = (a[i][j] - T.a[i][j]) % MOD;
      }
    return res;
  }

  mat operator+(const mat& T) const {
    mat res;
    for (int i = 0; i < sz; ++i)
      for (int j = 0; j < sz; ++j) {
        res.a[i][j] = (a[i][j] + T.a[i][j]) % MOD;
      }
    return res;
  }

  mat operator*(const mat& T) const {
    mat res;
    int r;
    for (int i = 0; i < sz; ++i)
      for (int k = 0; k < sz; ++k) {
        r = a[i][k];
        for (int j = 0; j < sz; ++j)
          res.a[i][j] += T.a[k][j] * r, res.a[i][j] %= MOD;
      }
    return res;
  }

  mat operator^(LL x) const {
    mat res, bas;
    for (int i = 0; i < sz; ++i) res.a[i][i] = 1;
    for (int i = 0; i < sz; ++i)
      for (int j = 0; j < sz; ++j) bas.a[i][j] = a[i][j] % MOD;
    while (x) {
      if (x & 1) res = res * bas;
      bas = bas * bas;
      x >>= 1;
    }
    return res;
  }
};
```

## Two Perspectives on Linear Systems

There are two perspectives on matrix A, or transformation A.

First perspective: View by rows, observe each row of A. Thus, A is viewed as a system of equations. This leads to the process of solving equations by elimination.

Second perspective: View by columns, observe each column of A. Matrix A is also composed of column vectors. At this point, we treat transformation A itself as a vector set, and x is unknown coefficients. We ask whether this set of column vectors in A can be combined with unknowns to form column vector b.

For example, the example at the beginning becomes:

$$
\begin{equation}
    \begin{pmatrix}
        7 \\ 4 \\ 1
    \end{pmatrix}x_1+\begin{pmatrix}
        8 \\ 5 \\ 2
    \end{pmatrix}x_2+\begin{pmatrix}
        9 \\ 6 \\ 3
    \end{pmatrix}x_3=\begin{pmatrix}
      13 \\ 12 \\ 11
    \end{pmatrix}
\end{equation}
$$

Solving the equation becomes studying whether by adjusting three coefficients x, we can combine the given three basis vectors to form the result vector.

Viewing by columns is more novel than viewing by rows. From the column perspective, we can study linear independence and dependence.

## Applications of Matrix Multiplication

### Matrix-Accelerated Recurrence

Take the [Fibonacci sequence](../combinatorics/fibonacci.md) as an example. In the Fibonacci sequence, $F_1 = F_2 = 1$, $F_i = F_{i - 1} + F_{i - 2}(i \geq 3)$.

If a problem asks for the $n$-th term of the Fibonacci sequence, the simplest method is direct recursion. But if $n$ reaches $10^{18}$ level, recursion won't work. At this point, we can consider matrix-accelerated recurrence.

According to the [matrix form of the Fibonacci recurrence formula](../combinatorics/fibonacci.md#matrix-form):

$$
\begin{bmatrix}
  F_{n-1} & F_{n-2}
\end{bmatrix} \begin{bmatrix}
  1 & 1 \\
  1 & 0
\end{bmatrix} = \begin{bmatrix}
  F_n & F_{n-1}
\end{bmatrix}
$$

Define initial matrix $\text{ans} = \begin{bmatrix}F_2 & F_1\end{bmatrix} = \begin{bmatrix}1 & 1\end{bmatrix}, \text{base} = \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}$. Then, $F_n$ equals the element at row 1, column 1 of matrix $\text{ans} \text{base}^{n-2}$, i.e., the element at row 1, column 1 of $\begin{bmatrix}1 & 1\end{bmatrix} \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}^{n-2}$.

???+ warning "Note"
    Matrix multiplication does not satisfy the commutative law, so it must not be written as the element at row 1, column 1 of $\begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}^{n-2} \begin{bmatrix}1 & 1\end{bmatrix}$. Also, for $n \leq 2$, directly output $1$; no matrix exponentiation is needed.

Why multiply by the $(n-2)$-th power of the $\text{base}$ matrix rather than the $n$-th power? Because $F_1, F_2$ can be obtained without matrix multiplication. That is, if we do only one multiplication, we have already computed $F_3$. If you don't quite understand why the exponent is $n-2$, it is recommended to calculate by hand.

Below is sample code for computing the $n$-th term of the Fibonacci sequence modulo $10^9+7$ (core part).

```cpp
constexpr int mod = 1000000007;

struct Matrix {
  int a[3][3];

  Matrix() { memset(a, 0, sizeof a); }

  Matrix operator*(const Matrix &b) const {
    Matrix res;
    for (int i = 1; i <= 2; ++i)
      for (int j = 1; j <= 2; ++j)
        for (int k = 1; k <= 2; ++k)
          res.a[i][j] = (res.a[i][j] + a[i][k] * b.a[k][j]) % mod;
    return res;
  }
} ans, base;

void init() {
  base.a[1][1] = base.a[1][2] = base.a[2][1] = 1;
  ans.a[1][1] = ans.a[1][2] = 1;
}

void qpow(int b) {
  while (b) {
    if (b & 1) ans = ans * base;
    base = base * base;
    b >>= 1;
  }
}

int main() {
  int n = read();
  if (n <= 2) return puts("1"), 0;
  init();
  qpow(n - 2);
  println(ans.a[1][1] % mod);
}
```

This is a slightly more complex example:

$$
\begin{gathered}
f_{1} = f_{2} = 0\\
f_{n} = 7f_{n-1}+6f_{n-2}+5n+4\times 3^n
\end{gathered}
$$

We find that $f_n$ depends on $f_{n-1}, f_{n-2}, n$. So we consider constructing a matrix to describe the state.

However, we find that if the matrix only contains these three elements $\begin{bmatrix}f_n& f_{n-1}& n\end{bmatrix}$, it's difficult to construct a transition equation, because power operations and $+1$ cannot be expressed by a matrix.

So we consider constructing a larger matrix:

$$
\begin{bmatrix}f_n& f_{n-1}& n& 3^n & 1\end{bmatrix}
$$

We want to construct a transition matrix that transforms to:

$$
\begin{bmatrix}
f_{n+1}& f_{n}& n+1& 3^{n+1} & 1
\end{bmatrix}
$$

The transition matrix is:

$$
\begin{bmatrix}
7 & 1 & 0 & 0 & 0\\
6 & 0 & 0 & 0 & 0\\
5 & 0 & 1 & 0 & 0\\
12 & 0 & 0 & 3 & 0\\
5 & 0 & 1 & 0 & 1
\end{bmatrix}
$$

### Matrix Expression for Modifications

???+ note "[「THUSCH 2017」Magician](https://loj.ac/p/2980)"
    Little L made $n$ magic crystal balls, each with energy values for water, fire, and earth. Little L arranged these $n$ crystal balls in a line from front to back, then began today's magic performance.
    
    We use $A_i,\ B_i,\ C_i$ to denote the water, fire, and earth energy values of the $i$-th crystal ball from the front (index starting from 1).
    
    Little L plans to cast $m$ spells. Each time, he chooses an interval $[l, r]$, then casts one of 3 types, 7 kinds of magic:
    
    1.  Magic excitation: Let the energy of a **specific attribute** of each crystal ball in the interval burst, thereby enhancing the energy of another **specific attribute**. Specifically, there are three possible forms:
    
        -   Fire excites water: Let $A_i = A_i + B_i$.
        -   Earth excites fire: Let $B_i = B_i + C_i$.
        -   Water excites earth: Let $C_i = C_i + A_i$.
    
            **Note that enhancing one attribute's energy does not change another attribute's energy, for example $A_i = A_i + B_i$ does not increase or decrease $B_i$.**
    2.  Magic enhancement: Little L waves his magic wand, consuming $v$ points of mana to change the energy of a **specific attribute** of each crystal ball in the interval. Specifically, there are three possible forms:
    
        -   Fire energy fixed enhancement: Let $A_i = A_i + v$.
        -   Water energy doubling enhancement: Let $B_i = B_i \cdot v$.
        -   Earth energy absorption and fusion: Let $C_i = v$.
    3.  Magic release: Little L gathers all the energy of crystal balls in the interval, fuses them into a new crystal ball, then gives it to the audience outside. The energy of each attribute of the generated crystal ball equals the algebraic sum of the corresponding energy values of all crystal balls in the interval. **Note that the magic release process does not actually change the energy of crystal balls in the interval.**
    
    It is worth mentioning that the crystal balls made and fused by Little L are custom-made from OI Factory crystals, so these crystal balls have an energy threshold $998244353$. When the energy of some attribute of a crystal ball is greater than or equal to this threshold, the energy value automatically takes the modulo of the threshold to avoid the crystal ball exploding.
    
    Little W is Little L's (only) audience, watching the entire performance, and received each crystal ball fused by Little L during the performance. Little W wants to know the energy values of the three attributes of these crystal balls.

Since the associative and distributive laws hold for matrices, point modifications can naturally be extended to intervals. That is, after deriving the matrix, simply maintain the interval matrix product using a segment tree.

Below are some examples.

The transition for $A_i = A_i + v$:

$$
\begin{bmatrix}
A & B & C & 1
\end{bmatrix}
\begin{bmatrix}
1 & 0 & 0 & 0\\
0 & 1 & 0 & 0\\
0 & 0 & 1 & 0\\
v & 0 & 0 & 1\\
\end{bmatrix}=
\begin{bmatrix}
A+v & B & C & 1\\
\end{bmatrix}
$$

The transition for $B_i = B_i \cdot v$:

$$
\begin{bmatrix}
A & B & C & 1
\end{bmatrix}
\begin{bmatrix}
1 & 0 & 0 & 0\\
0 & v & 0 & 0\\
0 & 0 & 1 & 0\\
0 & 0 & 0 & 1\\
\end{bmatrix}=
\begin{bmatrix}
A & B \cdot v & C & 1\\
\end{bmatrix}
$$

???+ note "[「LibreOJ 6208」Tree Queries](https://loj.ac/p/6208)"
    There is a tree with $n$ nodes, rooted at node 1. Each node has two values $k_i, t_i$, initially both 0.
    
    Three types of operations are given:
    
    1.  $\operatorname{Add}( x , d )$: Add $d$ to $k_i$ for all nodes on the path from $x$ to root.
    2.  $\operatorname{Mul}( x , d )$: Set $t_i \leftarrow t_i + d \times k_i$ for all nodes on the path from $x$ to root.
    3.  $\operatorname{Query}( x )$: Query the value $t_x$ of node $x$.
    
        $n,~m \leq 100000, ~-10 \leq d \leq 10$

If we think directly, distributing operations and maintaining information is not easy. But matrices can easily express it.

$$
\begin{aligned}
\begin{bmatrix}k & t & 1 \end{bmatrix}
\begin{bmatrix}
1 & 0 & 0 \\
0 & 1 & 0 \\
d & 0 & 1
\end{bmatrix}
&=
\begin{bmatrix}k+d & t & 1 \end{bmatrix}\\
\begin{bmatrix}k & t & 1 \end{bmatrix}
\begin{bmatrix}
1 & d & 0 \\
0 & 1 & 0 \\
0 & 0 & 1
\end{bmatrix}
&=
\begin{bmatrix}k & t+d \times k & 1 \end{bmatrix}
\end{aligned}
$$

### Counting Paths of Fixed Length

???+ note "Problem Description"
    Given an $n$-order directed graph, with all edges having weight 1, and an integer $k$. For all pairs of vertices $(u,v)$, find the number of paths of length $k$ from $u$ to $v$ (paths are not necessarily simple, i.e., vertices or edges may be visited multiple times).

We represent this directed graph with adjacency matrix $G$ (for edge $(u\to v)$, let $G[u,v]=1$, others are $0$. If there are multiple edges, let $G[u,v]$ be the number of multiple edges). The following algorithm also applies when the graph has self-loops.

Clearly, this adjacency matrix corresponds to the answer for $k=1$.

Assume we know the matrix of path counts of length $k$, denoted $C_k$. We want to find $C_{k+1}$. There is a DP transition:

$$
C_{k+1}[i,j] = \sum_{p = 1}^{n} C_k[i,p] \cdot G[p,j]
$$

We can view this as matrix multiplication, so the transition can be described as:

$$
C_{k+1} = C_k \cdot G
$$

Unfolding this recurrence gives:

$$
C_k = \underbrace{G \cdot G \cdots G}_{k \text{ times}} = G^k
$$

To compute this matrix power, we can use binary exponentiation in $O(n^3 \log k)$ time.

### Shortest Paths of Fixed Length

???+ note "Problem Description"
    Given an $n$-order weighted directed graph and an integer $k$. For each pair of vertices $(u,v)$, find the length of the shortest path from $u$ to $v$ containing exactly $k$ edges (paths are not necessarily simple, i.e., vertices or edges may be visited multiple times).

We construct the adjacency matrix $G$ of this graph, where $G[i,j]$ represents the edge weight from $i$ to $j$. If there is no edge between $i,j$, then $G[i,j]=\infty$ (for multiple edges, take the minimum edge weight).

Clearly, this matrix corresponds to the answer for $k=1$. We still assume we know the answer for $k$, denoted $L_k$. Now we want the answer for $k+1$. There is a transition:

$$
L_{k+1}[i,j] = \min_{1\le p \le n} \left\{L_k[i,p] + G[p,j]\right\}
$$

In fact, we can compare with matrix multiplication. You find that the transition only changes the sum in matrix multiplication to taking the minimum. So we define this operation as $\odot$:

$$
A \odot B = C~~\Longleftrightarrow~~C[i,j]=\min_{1\le p \le n}\left\{A[i,p] + B[p,j]\right\}
$$

Thus we get:

$$
L_{k+1} = L_k \odot G
$$

Unfolding the recurrence:

$$
L_k = \underbrace{G \odot \ldots \odot G}_{k\text{ times}} = G^{\odot k}
$$

We can still use matrix exponentiation to compute this, because it is clearly associative. Time complexity is $O(n^3 \log k)$.

### Counting/Shortest Paths with Bounded Length

The above algorithm only applies when the number of edges is fixed. However, we can improve the algorithm to solve the case where the number of edges is less than or equal to $k$. Specifically, consider:

???+ note "Problem Description"
    Given an $n$-order directed graph with edge weight 1, and an integer $k$. For each pair of vertices $(u,v)$, find the number of paths of length $\leq k$ from $u$ to $v$ (paths are not necessarily simple, i.e., vertices or edges may be visited multiple times).

For each vertex $v$, we create a dummy vertex $v'$ to record the answer, and add two edges $(v,v')$ and $(v',v')$ to the graph. Then for pair $(u,v)$, the number of paths from $u$ to $v$ with length $\leq k$ equals the number of paths from $u$ to $v'$ with exactly $k+1$ edges. This is because for any path of $m$ edges ($m \le k$) $(p_0=u)\to p_1\to p_2 \to \dots \to p_{m-1} \to (p_m=v)$, there is a one-to-one correspondence with a path of $k+1$ edges $(p_0=u)\to p_1 \to p_2 \to \dots \to p_{m-1} \to (p_m=v) \to v'  \to \dots \to v'$.

For finding the shortest path with $\leq k$ edges, simply add a self-loop with edge weight $0$ for each vertex.

## Exercises

-   [Luogu P1962 Fibonacci Sequence](https://www.luogu.com.cn/problem/P1962), which is the example above, also POJ3070
-   [Luogu P1349 Generalized Fibonacci Sequence](https://www.luogu.com.cn/problem/P1349), the $\text{base}$ matrix needs to be modified
-   [Luogu P1939【Template】Matrix Acceleration (Sequence)](https://www.luogu.com.cn/problem/P1939), the $\text{base}$ matrix becomes $3 \times 3$, and the derivation is similar to above.

**Part of this page is translated from the article [Кратчайшие пути фиксированной длины, количества путей фиксированной длины](http://e-maxx.ru/algo/fixed_length_paths) and its English translation [Number of paths of fixed length/Shortest paths of fixed length](https://cp-algorithms.com/graph/fixed_length_paths.html). The Russian version is in the Public Domain with Leave a Link; the English version is under CC-BY-SA 4.0.**
