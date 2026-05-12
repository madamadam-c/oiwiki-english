author: StudyingFather, CCXXXI, Chrogeek, ChungZH, countercurrent-time, Early0v0, Enter-tainer, GavinZhengOI, Great-designer, H-J-Granger, henrytbtrue, HeRaNO, huayucaiji, iamtwz, Ir1d, ksyx, MegaOwIer, NachtgeistW, P-Y-Y, qwqAutomaton, shuzhouliu, shuzhouliu-bot, Siger Young, sshwy, SukkaW, Tiphereth-A, tsentau, WhenMelancholy, Xeonacid, Yukimaikoriya, Zhoier, zyj-111, qute-firefly-26710-zjyjoe-lg-592080

## Introduction

Gaussian elimination (Gauss–Jordan elimination) is a classic algorithm for solving linear equation systems. It holds an important position and value in modern mathematics and is a significant component of linear algebra coursework.

Besides solving linear equation systems, Gaussian elimination can also be used for determinant calculation, matrix inversion, and other applications in computing and engineering.

## Elimination Method and the Idea of Gaussian Elimination

### Definition

The elimination method involves expressing one unknown in an equation using an algebraic expression containing another unknown, and substituting it into another equation to eliminate one unknown and obtain a solution; or multiplying an equation by a constant and adding it to another equation to also eliminate one unknown. The elimination method is primarily used for solving systems of two linear equations in two unknowns.

### Explanation

Example 1: Using the elimination method to solve a system of two linear equations:

$$
\begin{cases}
4x+y&=100 \\
x-y&=100
\end{cases}
$$

Solution: Adding the two equations in the system eliminates $y$:

$$
5x = 200
$$

Solving gives:

$$
x = 40
$$

Substituting $x = 40$ into the second equation of the system gives:

$$
y = -60
$$

### Core Theory of the Elimination Method

The core theory of the elimination method is as follows:

-   Swapping two equations does not change the solution;
-   Multiplying an equation by a non-zero number $k$ does not change the solution;
-   Adding a multiple of one equation to another equation does not change the solution.

### Concept of Gaussian Elimination

The German mathematician Gauss analyzed the elimination method and arrived at the following conclusions:

-   In the elimination method, what participates in calculations and changes are the coefficients of the variables in the equations;
-   The variables themselves do not participate in calculations and do not change;
-   The positions of coefficients can be used to represent variables, thus omitting the variables;
-   During calculations, by simplifying and omitting variables, the solution to the equation remains unchanged.

Based on these conclusions, Gauss proposed Gaussian elimination. First, the augmented matrix of the equation system is transformed into reduced row echelon form using elementary row operations. Then, free variables are assigned values based on the criterion of linear independence. Finally, the general solution of the equation system is expressed.

## Five-Step Method of Gaussian Elimination

## Explanation

After transforming the augmented matrix to reduced row echelon form, assigning values to free variables requires knowledge of linear algebra, and the assignment involves human experience, making it somewhat difficult to learn. The five-step method divides Gaussian elimination into five steps, as follows:

1.  Transform the augmented matrix to reduced row echelon form using elementary row operations;

2.  Restore the linear equation system;

3.  Solve for the first variable;

4.  Supplement the free variables;

5.  Express the general solution in column form.

Let us further explain the algorithm's operation with an example.

## Process

Example 2: Using the five-step Gaussian elimination method to solve the linear equation system:

$$
\begin{cases}
2x_1+5x_3+6x_4&=9 \\
x_3+x_4&=-4 \\
2x_3+2x_4&=-8
\end{cases}
$$

### Transform Augmented Matrix to Reduced Row Echelon Form

The augmented matrix is a new matrix formed by combining the coefficient matrix $A$ of the equation system with the constant column $b$, i.e., $(A | b)$. Transforming the augmented matrix to reduced row echelon form uses the idea of Gaussian elimination, omitting variables and using the positions of coefficients to represent variables. In the augmented matrix, the vertical line separates the coefficient matrix from the constant column, representing the equals sign.

$$
\left(\begin{matrix}
2 & 0 & 5 & 6 \\
0 & 0 & 1 & 1 \\
0 & 0 & 2 & 2
\end{matrix} \middle|
\begin{matrix}
9 \\
-4 \\
-8
\end{matrix} \right)
$$

$$
\xrightarrow{r_3-2r_2}
\left(\begin{matrix}
2 & 0 & 5 & 6 \\
0 & 0 & 1 & 1 \\
0 & 0 & 0 & 0
\end{matrix} \middle|
\begin{matrix}
9 \\
-4 \\
0
\end{matrix} \right)
$$

Transform to row echelon form

$$
\xrightarrow{\frac{r_1}{2}}
\left(\begin{matrix}
1 & 0 & 2.5 & 3 \\
0 & 0 & 1 & 1 \\
0 & 0 & 0 & 0
\end{matrix} \middle|
\begin{matrix}
4.5 \\
-4 \\
0
\end{matrix} \right)
$$

$$
\xrightarrow{r_1-r_2 \times 2.5}
\left(\begin{matrix}
1 & 0 & 0 & 0.5 \\
0 & 0 & 1 & 1 \\
0 & 0 & 0 & 0
\end{matrix} \middle|
\begin{matrix}
14.5 \\
-4 \\
0
\end{matrix} \right)
$$

Transform to reduced row echelon form

### Restore the Linear Equation System

$$
\begin{cases}
x_1+0.5x_4 &= 14.5\\
x_3+x_4 &= -4 \\
\end{cases}
$$

???+ note "Explanation"
    Restoring the linear equation system means rewriting the reduced row echelon form in the form of linear equations, assigning the coefficients at each position back to the variables, and replacing the vertical line with an equals sign.

### Solve for the First Variable

$$
\begin{cases}
x_1 = -0.5x_4+14.5\notag \\
x_3 = -x_4-4\notag
\end{cases}
$$

???+ note "Explanation"
    This means, for the restored linear equation system, expressing the first variable in each equation using other quantities. For example, the first variables $x_1$ and $x_3$ in the two equations of the system.

### Supplement the Free Variables

$$
\begin{cases}
x_1 = -0.5x_4+14.5 \\
x_2 = x_2 \\
x_3 = -x_4-4 \\
x_4 = x_4
\end{cases}
$$

???+ note "Explanation"
    In step 3, we solved for variables $x_1$ and $x_3$, which shows that the remaining variables $x_2$ and $x_4$ in the equation system are not constrained by the equation system and are free variables that can take any value. Therefore, we need to supplement the solution based on step 3. The supplementation method is $x_2 = x_2$, $x_4 = x_4$. This supplementation method conforms to the definition of free variables and is easy to understand. Since they are free variables and not constrained, they can only equal themselves.

### Express the General Solution in Column Form

$$
\begin{aligned}
\begin{pmatrix} x_1 \\ x_2 \\ x_3 \\ x_4 \end{pmatrix} &=
\begin{pmatrix} 0 \\ 1 \\ 0 \\ 0 \end{pmatrix} x_2+
\begin{pmatrix} -0.5 \\ 0 \\ -1 \\ 1 \end{pmatrix} x_4 +
\begin{pmatrix} 14.5 \\ 0 \\ -4 \\ 0 \end{pmatrix} \\
&= \begin{pmatrix} 0 \\ 1 \\ 0 \\ 0 \end{pmatrix} C_1+
\begin{pmatrix} -0.5 \\ 0 \\ -1 \\ 1 \end{pmatrix} C_2 +
\begin{pmatrix} 14.5 \\ 0 \\ -4 \\ 0 \end{pmatrix}
\end{aligned}
$$

where $C_1$ and $C_2$ are arbitrary constants.

???+ note "Explanation"
    That is, based on step 4, express the solution as a combination of column vectors. Since $x_2$ and $x_4$ are free variables that can take any value, we let them be arbitrary constants $C_1$ and $C_2$ on the right side of the solution, thus completing the solution of the equation system.

## Determinant Calculation

### Explanation

The determinant of an $N \times N$ square matrix can be understood as the signed volume of the geometric figure enclosed by all column vectors.

For example:

$$
\begin{vmatrix}
1 & 0 \\
0 & 1 \end{vmatrix} = 1
$$

$$
\begin{vmatrix}
1 & 2 \\
2 & 1 \end{vmatrix} = -3
$$

The determinant has the formula:

$$
\operatorname{det}(A)=\sum_{\sigma \in S_{n}} \operatorname{sgn}(\sigma) \prod_{i=1}^{n} a_{i, \sigma(i)}
$$

where $S_n$ is the set of all permutations of length $n$, and $\sigma$ is a permutation. If the number of inversions in $\sigma$ is even, then $\operatorname{sgn}(\sigma)=1$, otherwise $\operatorname{sgn}(\sigma)=-1$.

Understanding the invariance of the determinant through the volume concept is a simple approach:

-   Transposing the matrix does not change the determinant;
-   Swapping two rows (or columns) flips the sign of the determinant;
-   Adding or subtracting rows (or columns) does not change the determinant;
-   Multiplying all elements in a row (or column) by a scalar $k$ scales the determinant by a factor of $k$.

Thus, after applying Gaussian elimination to a matrix, we can obtain a diagonal matrix, whose determinant is determined by the product of diagonal elements. Its sign can be determined by the number of row swaps (if odd, the sign of the determinant should be reversed). Therefore, we can compute the matrix determinant using Gaussian elimination in $O(n^3)$ time complexity.

Note that if at some point we cannot find a non-zero element in the current column, the algorithm should stop and return 0.

### Implementation

```cpp
constexpr double EPS = 1E-9;
int n;
vector<vector<double>> a(n, vector<double>(n));

double det = 1;
for (int i = 0; i < n; ++i) {
  int k = i;
  for (int j = i + 1; j < n; ++j)
    if (abs(a[j][i]) > abs(a[k][i])) k = j;
  if (abs(a[k][i]) < EPS) {
    det = 0;
    break;
  }
  swap(a[i], a[k]);
  if (i != k) det = -det;
  det *= a[i][i];
  for (int j = i + 1; j < n; ++j) a[i][j] /= a[i][i];
  for (int j = 0; j < n; ++j)
    if (j != i && abs(a[j][i]) > EPS)
      for (int k = i + 1; k < n; ++k) a[j][k] -= a[i][k] * a[j][i];
}

cout << det;
```

## Matrix Inversion

For a square matrix $A$, if there exists a matrix $A^{-1}$ such that $A \times A^{-1} = A^{-1} \times A = I$, then matrix $A$ is said to be invertible, and $A^{-1}$ is called its inverse matrix.

Given an $n \times n$ square matrix $A$, the method to find its inverse is as follows:

1.  Construct an $n \times 2n$ matrix $(A, I_n)$;
2.  Use Gaussian elimination to reduce it to the form $(I_n, A^{-1})$, thus obtaining the inverse matrix $A^{-1}$. If the left part of the final reduced form is not the identity matrix $I_n$, then matrix $A$ is not invertible.

The correctness proof of this method requires substantial linear algebra knowledge and is omitted here due to space constraints. Interested readers may consult relevant materials.

## Solving XOR Equation Systems with Gaussian Elimination

An XOR equation system is one of the form:

$$
\begin{cases}
a_{1,1}x_1 \oplus a_{1,2}x_2 \oplus \cdots \oplus a_{1,n}x_n &= b_1\\
a_{2,1}x_1 \oplus a_{2,2}x_2 \oplus \cdots \oplus a_{2,n}x_n &= b_2\\
\cdots &\cdots \\ a_{m,1}x_1 \oplus a_{m,2}x_2 \oplus \cdots \oplus a_{m,n}x_n &= b_m
\end{cases}
$$

where $\oplus$ denotes "bitwise XOR" (i.e., `xor` or `^` in C++), and all coefficients/constants in the equations (i.e., $a_{i,j}$ and $b_i$) are $0$ or $1$.

Since "XOR" satisfies the commutative and associative laws, we can use Gaussian elimination to progressively eliminate variables. Notably, we should use "XOR elimination" rather than "addition/subtraction elimination", and there is no need to multiply or divide coefficients (since they are all $0$ and $1$).

Note that the augmented matrix of an XOR equation system is a $01$ matrix (containing only $0$ and $1$), so we can use C++'s `std::bitset` for optimization, reducing the time complexity to $O(\dfrac{n^2m}{\omega})$, where $n$ is the number of variables, $m$ is the number of equations, and $\omega$ is typically $32$ (machine-dependent).

Reference implementation:

```cpp
std::bitset<1010> matrix[2010];  // matrix[1~n]: augmented matrix, position 0 is constants

std::vector<bool> GaussElimination(
    int n, int m)  // n is number of unknowns, m is number of equations, returns solution
                   // (multiple solutions/no solution returns an empty vector)
{
  for (int i = 1; i <= n; i++) {
    int cur = i;
    while (cur <= m && !matrix[cur].test(i)) cur++;
    if (cur > m) return std::vector<bool>(0);
    if (cur != i) swap(matrix[cur], matrix[i]);
    for (int j = 1; j <= m; j++)
      if (i != j && matrix[j].test(i)) matrix[j] ^= matrix[i];
  }
  std::vector<bool> ans(n + 1);
  for (int i = 1; i <= n; i++) ans[i] = matrix[i].test(0);
  return ans;
}
```

## Practice Problems

-   [Codeforces - Wizards and Bets](http://codeforces.com/contest/167/problem/E)
-   [Luogu - SDOI2010 Alien Millipede](https://www.luogu.com.cn/problem/P2447)