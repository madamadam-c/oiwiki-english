Prerequisite: [Linear Programming Basics](./linear-programming.md)

## Introduction

In programming contests, the simplex method is often used to solve linear programming problems. However, since most linear programming problems encountered in programming contests have more special structures and can often be transformed into network flow problems, the simplex method is not commonly used and its efficiency is not as good as algorithms specifically designed for network flow problems.

## Basic Concepts

Suppose we need to solve the following linear programming problem in [standard form](./linear-programming.md#standard-form) with $n$ decision variables and $m+n$ constraints:

$$
\begin{aligned}
\min_{x}\; & z = c^Tx \\
\text{subject to }& Ax = b, \\
& x \ge 0.
\end{aligned}
$$

Let us assume that the system of linear equations determined by these $m$ equality constraints has a solution, and $A$ is full rank, so $\operatorname{rank}A = m \le n$.

### An Example

Before rigorously describing the steps of the simplex method, this section first examines a specific example to facilitate understanding.

???+ example "Example"
    Consider the linear programming problem
    
    $$
    \begin{aligned}
    \max\; & 10 x_1 + 12 x_2 + 12 x_3 \\
    \text{subject to } & x_1 + 2 x_2 + 2x_3 \le 20, \\
    & 2x_1 + x_2 + 2x_3 \le 20, \\
    & 2x_1 + 2x_2 + x_3 \le 20,\\
    & x_1,x_2,x_3 \ge 0.
    \end{aligned}
    $$
    
    By adding slack variables, we obtain its standard form:
    
    $$
    \begin{aligned}
    \min\; & -10 x_1 - 12 x_2 - 12 x_3 \\
    \text{subject to } & x_1 + 2 x_2 + 2x_3 + x_4 = 20, \\
    & 2x_1 + x_2 + 2x_3 + x_5 = 20, \\
    & 2x_1 + 2x_2 + x_3 + x_6 = 20,\\
    & x_1,x_2,x_3,x_4,x_5,x_6 \ge 0.
    \end{aligned}
    $$
    
    Observing the equality constraints of this problem, they actually express the variables $x_4,x_5,x_6$ in terms of the variables $x_1,x_2,x_3$. Rearranging the original problem a bit, we have
    
    $$
    \begin{array}{rrrrrr}
    \min_{x_i\ge 0}  &  z  = &  0 &  -10x_1 &  -12x_2 &  -12x_3\;\\
    \text{subject to}& x_4 = & 20 &    -x_1 &   -2x_2 &   -2x_3, \\
                    & x_5 = & 20 &   -2x_1 &    -x_2 &   -2x_3, \\
                    & x_6 = & 20 &   -2x_1 &   -2x_2 &    -x_3. \\
    \end{array}
    $$
    
    From this form, we can clearly see that if we set $x_1=x_2=x_3=0$, we obtain a feasible solution to the original problem
    
    $$
    x = (0,0,0,20,20,20)^T.
    $$
    
    And its corresponding value is $z=0$. For convenience of description, the variables set to zero, $x_1,x_2,x_3$, are called non-basic variables, and the remaining variables $x_4,x_5,x_6$ are called basic variables.
    
    This feasible solution is clearly not optimal. As long as we appropriately increase the values of $x_1,x_2,x_3$ while keeping $x_4,x_5,x_6$ non-negative, the solution remains feasible. Moreover, because the coefficients of $x_1,x_2,x_3$ in the objective function are strictly negative, increasing their values will definitely decrease the value of the objective function. For example, we can choose to increase the value of $x_1$. To decrease the objective function value as much as possible, we need to increase $x_1$ as much as possible. However, to ensure the solution remains feasible, we need to keep $x_4,x_5,x_6\ge 0$. Therefore, $x_1$ can be increased to at most
    
    $$
    \min\left\{\dfrac{20}{1},\dfrac{20}{2},\dfrac{20}{2}\right\} = 10.
    $$
    
    At this point, the feasible solution becomes
    
    $$
    x = (10,0,0,10,0,0)^T.
    $$
    
    Because $x_1$ has become a basic variable, to return to the initial situation (i.e., the three basic variables expressed by three non-basic variables), we need to select a new non-basic variable. Since both $x_5$ and $x_6$ are zero, we can choose either of them as the non-basic variable and set it to zero. Let us choose $x_5$ as the non-basic variable. Moreover, substituting
    
    $$
    x_1 = 10 - 0.5x_5 - 0.5x_2 - x_3
    $$
    
    into the original problem, we can rewrite the problem as
    
    $$
    \begin{array}{rrrrrr}
    \min_{x_i\ge 0}  &   z = &-100&   +5x_5 &   -7x_2 &   -2x_3\;\\
    \text{subject to}& x_4 = & 10 & +0.5x_5 & -1.5x_2 &    -x_3, \\
                    & x_1 = & 10 & -0.5x_5 & -0.5x_2 &    -x_3, \\
                    & x_6 = &  0 &    +x_5 &    -x_2 &    +x_3. \\
    \end{array}
    $$
    
    This returns to the initial situation.
    
    Continue observing the current objective function. The coefficient of the non-basic variable $x_3$ is still negative. We can consider increasing the value of $x_3$. To keep $x_4,x_1,x_6\ge 0$, the variable $x_3$ can be increased to at most
    
    $$
    \min\left\{\dfrac{10}{1},\dfrac{10}{1}\right\} = 10.
    $$
    
    Note that because in the expression for $x_6$, the coefficient of $x_3$ is positive, no matter how much we increase $x_3$, $x_6$ will not become negative. This is why there are only two terms in this min operation. Since when $x_3$ increases to $10$, both $x_1$ and $x_4$ become zero, we can choose either as the new non-basic variable. Let us choose $x_4$. Then substituting
    
    $$
    x_3 = 10 + 0.5x_5 - 1.5x_2 - x_4
    $$
    
    into the above problem, the problem becomes
    
    $$
    \begin{array}{rrrrrr}
    \min_{x_i\ge 0}  &   z = &-120&   +4x_5 &   -4x_2 &   +2x_4\;\\
    \text{subject to}& x_3 = & 10 & +0.5x_5 & -1.5x_2 &    -x_4, \\
                    & x_1 = &  0 &    -x_5 &    +x_2 &    +x_4, \\
                    & x_6 = & 10 & +1.5x_5 & -2.5x_2 &    -x_4. \\
    \end{array}
    $$
    
    By setting $x_5=x_2=x_4=0$, we can read from this form that the current feasible solution is
    
    $$
    x = (0,0,10,0,0,10)^T,
    $$
    
    and its corresponding value is $z=-120$.
    
    Repeat the previous operation. Since the coefficient of $x_2$ is negative, we can increase its value; but to keep $x_3,x_6$ non-negative, it can only be increased to
    
    $$
    \min\left\{\dfrac{10}{1.5},\dfrac{10}{2.5}\right\} = 4.
    $$
    
    Because the minimum in the brackets appears in the expression for variable $x_6$, it becomes zero when $x_2=4$. Substituting the expression
    
    $$
    x_2 = 4 + 0.6x_5 - 0.4x_6 - 0.4x_4
    $$
    
    into the above problem, we can rewrite the original problem as
    
    $$
    \begin{array}{rrrrrr}
    \min_{x_i\ge 0}  &   z = &-136& +1.6x_5 & +1.6x_6 & +3.6x_4\;\\
    \text{subject to}& x_3 = &  4 & -0.4x_5 & +0.6x_6 & -0.4x_4, \\
                    & x_1 = &  4 & -0.4x_5 & -0.4x_6 & +0.6x_4, \\
                    & x_2 = &  4 & +1.5x_5 & -2.5x_6 &    -x_4. \\
    \end{array}
    $$
    
    Still setting the non-basic variables $x_5,x_6,x_4$ to zero, we obtain the current feasible solution as
    
    $$
    x = (4,4,4,0,0,0)^T.
    $$
    
    The corresponding value is $z=-136$.
    
    Because all coefficients of non-basic variables in the objective function are positive, we cannot continue the previous process to improve the objective function. Therefore, the current feasible solution is the optimal solution. The algorithm terminates.

In this example, the algorithm starts from a feasible solution and continuously improves the objective function until it cannot be improved further. This is the basic idea of the simplex method.

### Basic Feasible Solution

Since $A$ is full rank, we can always select a subset $B\subseteq\{1,2,\cdots,n\}$ of size $m$ such that $A_B$ is an invertible matrix. From this, we can express $x_B$ in terms of the remaining variables $x_N$:

$$
x_B = A_B^{-1}b - A_B^{-1}A_Nx_N.
$$

Here, $N=\{1,2,\cdots,n\}\setminus B$, matrices $A_B$ and $A_N$ are the submatrices composed of columns of $A$ with indices $i\in B$ and $i\in N$, respectively, and vectors $x_B$ and $x_N$ are the subvectors composed of components of $x$ with indices $i\in B$ and $i\in N$, respectively. If $i\in B$, then $x_i$ is called a **basic variable** (basic variable); otherwise, $x_i$ is called a **non-basic variable** (non-basic variable). The set of all basic variables is called a **basis** (basis), and this article uses the corresponding index set $B$ to represent a basis.

???+ tip "\"Basis\""
    The name "basis" can be understood from the perspective of linear algebra. Let $V$ be the linear space spanned by all column vectors of $A$. Then the column vectors corresponding to basis $B$ are a basis of space $V$.

Setting $x_N=0$ in the expression for the basic variables $x_B$, we obtain a solution to all equality constraints[^notation]

$$
x = (x_B,x_N) = (A_B^{-1}b,0).
$$

Such a solution is called a **basic solution** (basic solution) of the linear programming problem. If it also satisfies all non-negativity constraints, i.e., $x\ge 0$, then it is also a feasible solution to the original problem, also called a **basic feasible solution** (BFS). During the iteration of the simplex method, we need to always keep the current solution as a basic feasible solution.

### Pivoting

Each iteration of the simplex method is called a **pivoting** (pivoting). From the result, each pivoting always removes one old basic variable and adds a new basic variable, thereby improving the value of the objective function.

???+ tip "\"Pivoting\""
    The name "pivoting" can also be understood from the perspective of linear algebra. As mentioned above, the column vectors corresponding to basis $B$ are a basis of space $V$, and they correspond to a set of coordinate axes in the representation corresponding to that basis. Therefore, the pivoting process is the process of rotating some coordinate axis to a new position.

To determine which basic variable needs to be added, we can express the objective function in terms of non-basic variables:

$$
\begin{aligned}
c^Tx &= c^T_Bx_B + c^T_Nx_N \\
&= c_B^TA_B^{-1}b + (c_N^T - c_B^TA_B^{-1}A_N)x_N.
\end{aligned}
$$

Setting $x_N=0$, we obtain the value $z=c_B^TA_B^{-1}b$ of the objective function at the current basic feasible solution. The coefficient of the second term in the expression indicates how much the objective function changes when $x_N$ changes:

$$
\tilde c_N = \dfrac{\partial z}{\partial x_N} = c_N - A_N^T(A_B^{-1})^Tc_B.
$$

Note that $c_B - A_B^T(A_B^{-1})^Tc_B = 0$, so we can denote the vector

$$
\tilde c = (\tilde c_B^T,\tilde c_N^T)^T = c - A^T(A_B^{-1})^Tc_B
$$

as the **reduced cost** (reduced cost) of the linear programming problem at the feasible basic solution $x$. A component $\tilde c_i<0$ indicates that increasing the value of variable $x_i$ can improve the objective function of the original problem. Such a variable can only be a non-basic variable, and it is called the **entering variable** (entering variable) of this pivoting. Because after pivoting, $x_i$ will become a basic variable and will no longer be constantly set to zero (but it may still equal zero).

After selecting the entering variable, we also need to select which old basic variable needs to be removed. For this, we only need to determine which existing basic variable first becomes zero as we increase $x_i$. Substituting $x_N=(x_i,x_{N\setminus\{i\}})=(x_i,0)$ into the expression for $x_B$, we have

$$
x_B = A_B^{-1}b - A_B^{-1}A_ix_i.
$$

Therefore, the maximum amount by which $x_i$ can be increased is

$$
\theta = \min\left\{\dfrac{(A_B^{-1}b)_j}{(A_B^{-1}A_i)_j}:(A_B^{-1}A_i)_j>0\right\}.
$$

The variable that first becomes zero is the basic variable $x_{B_j}$ corresponding to the index $j$ that minimizes this expression. It is also the "bottleneck" in the process of increasing $x_i$—continuing to increase $x_i$ would make $x_{B_j}$ negative. This variable is the **leaving variable** (leaving variable) of this pivoting. The method for determining the leaving variable is called the **minimum ratio test** (minimum ratio test).

Suppose the entering variable is $x_i$ and the leaving variable is $x_{i'}$. After pivoting, the basic variables are $x_{B\setminus\{i\}\cup\{i'\}}$, and the non-basic variables are $x_{N\setminus\{i'\}\cup\{i\}}$.

### Termination Conditions

The simplex method is a process that starts from a basic feasible solution and continuously performs pivoting. The discussion of pivoting in the previous section is not complete; it ignores some special cases. Some special cases correspond to the termination of the algorithm, while others require additional handling.

First, the entering variable may not exist, i.e., $\tilde c\ge 0$. In this case, there is no way to further improve the optimal value, which means the current basic feasible solution is the optimal solution, and the algorithm terminates. To rigorously prove this, we need to use the [complementary slackness conditions](./linear-programming.md#complementary-slackness-conditions). Let $y=(A_B^{-1})^Tc_B$. Note that throughout the algorithm, we always keep $x$ as a feasible solution, and the complementary slackness condition holds, i.e.,

$$
x^T(c-A^Ty) = \tilde c^Tx = \tilde c_B^Tx_B + \tilde c_N^Tx_N = 0.
$$

Therefore, as long as $y$ is a feasible solution to the dual problem, i.e., $A^Ty\le c$, we can conclude that $x$ and $y$ are optimal solutions to the original and dual problems, respectively. This condition is $\tilde c\ge 0$, i.e., no entering variable exists.

???+ tip "\"Shadow Price\""
    The vector $y=(A_B^{-1})^Tc_B$ is often called the **dual vector** (dual vector). When the basic feasible solution corresponding to $B$ is the optimal solution to the original problem, vector $y$ is the optimal solution to the dual problem. Therefore, when using the simplex method to find the optimal solution to the original problem, we also obtain the optimal solution to the dual problem. Because vector $y$ is the partial derivative of the current value with respect to the constraint constants, i.e.,
    
    $$
    \dfrac{\partial(c^Tx)}{\partial b} = (A_B^{-1})^Tc_B = y,
    $$
    
    it is also called the **shadow price** (shadow price).

Second, the leaving variable may not exist, i.e., $A_B^{-1}A_i\le 0$. In this case, there is no "bottleneck" in the pivoting process; that is, we can continuously improve the objective function by increasing the value of $x_i$ until it equals $-\infty$. This indicates that the given linear programming problem is unbounded, and the algorithm terminates.

Finally, the selection of entering and leaving variables may not be unique. Inappropriate selection methods may lead to too many pivots, or even cause the algorithm to fall into a cycle and fail to terminate normally. The handling of such cases is slightly complex and requires applying some [pivot rules](#pivot-rules) to prevent cycling and reduce the number of pivots.

### Simplex Tableau

When actually implementing the pivoting process, we only need to maintain the coefficient matrix of the linear programming problem after each pivoting:

$$
\tilde T_B = 
\begin{pmatrix}
-z_B & \tilde c^T_N \\
x & A_B^{-1}A_N
\end{pmatrix}
=
\begin{pmatrix}
-c_B^TA_B^{-1}b & c^T - c_B^TA_B^{-1}A_N \\
A_B^{-1}b & A_B^{-1}A_N 
\end{pmatrix}.
$$

It corresponds to the linear programming problem:

$$
\begin{array}{rrrr}
\min_{x\ge 0}    &       & c_B^TA_B^{-1}b & + \tilde c_N^Tx_N\; \\
\text{subject to}& x_B = & A_B^{-1}b      & - A_B^{-1}A_Nx_N.
\end{array}
$$

The matrix $\tilde T_B$ is called the **condensed simplex tableau** (condensed simplex tableau) of the linear programming problem relative to basis $B$. The upper-left element $(\tilde T_B)_{00}$ is the (negation of the) value of the current solution, the element in row $0$ and column $i$ $(\tilde T_B)_{0i}$ is the reduced cost of the $i$-th non-basic variable $x_{N_i}$, the element in row $j$ and column $0$ $(\tilde T_B)_{j0}$ is the value of the $j$-th basic variable $x_{B_j}$, and $A_B^{-1}A_N$ is the coefficient in the expression of basic variables $x_B$ in terms of non-basic variables $x_N$.

It is easy to see that all information needed for pivoting can be directly obtained from the condensed simplex tableau. Specifically, using the condensed simplex tableau, a single pivoting includes the following operations:

1.  Select column $i=1,\cdots,n-m$ such that $(\tilde T_B)_{0i}<0$. If no such $i$ exists, then the current solution is the optimal solution, and $-(\tilde T_B)_{00}$ is the optimal value.
2.  Select row $j=1,\cdots,m$ such that $(\tilde T_B)_{ji}>0$ and $(\tilde T_B)_{j0}/(\tilde T_B)_{ji}$ is minimized. If no such $j$ exists, then the original problem is unbounded.
3.  Let variable $x_{N_i}$ enter the basis, variable $x_{B_j}$ leave the basis, and update the simplex tableau.

Now, let us specifically discuss how to update the simplex tableau. Before updating the simplex tableau, row $j$ represents the equality

$$
x_{B_j} = (\tilde T_B)_{j0} - \sum_{i=1}^{n-m}(\tilde T_B)_{ji}x_{N_i}.
$$

To update the simplex tableau, we need to express $x_{N_i}$ in terms of $x_{N\setminus\{N_i\}\cup\{B_j\}}$:

$$
x_{N_i} = \dfrac{(\tilde T_B)_{j0}}{(\tilde T_B)_{ji}} - \dfrac{1}{(\tilde T_B)_{ji}}x_{B_j} - \sum_{i'\neq i}\dfrac{(\tilde T_B)_{ji'}}{(\tilde T_B)_{ji}}x_{N_{i'}}.
$$

Substituting this into the other equations, we get

$$
x_{B_{j'}} = \left((\tilde T_B)_{j'0} - (\tilde T_B)_{j'i}\dfrac{(\tilde T_B)_{j0}}{(\tilde T_B)_{ji}}\right) + \dfrac{(\tilde T_B)_{j'i}}{(\tilde T_B)_{ji}}x_{B_j} - \sum_{i'\neq i}\left((\tilde T_B)_{j'i'}-(\tilde T_B)_{j'i}\dfrac{(\tilde T_B)_{ji'}}{(\tilde T_B)_{ji}}\right)x_{N_i}.
$$

The $0$-th row is similar, except that the left side becomes $-z$. Although the formula looks complex, in implementation, we only need to do it in two steps:

1.  Update row $j$, i.e., let $\alpha=(\tilde T_B)_{ji}$, then set the element in column $i$ to $1$, and divide all numbers in the entire row by $\alpha$;
2.  Update row $j'\neq j$, i.e., let $\beta=(\tilde T_B)_{j'i}$, then set the element in column $j$ to $0$, and subtract $\beta$ times row $j$ from all numbers in the row simultaneously.

???+ tip "\"Simplex Tableau\""
    The **simplex tableau** (simplex tableau) refers to the matrix
    
    $$
    T_B = 
    \begin{pmatrix}
    -z & \tilde c^T \\
    x & A_B^{-1}A 
    \end{pmatrix}
    =
    \begin{pmatrix}
    -c_B^TA_B^{-1}b & c^T - c_B^TA_B^{-1}A \\
    A_B^{-1}b & A_B^{-1}A 
    \end{pmatrix}.
    $$
    
    Compared to the condensed simplex tableau, it has $m$ more columns, corresponding to the $m$ basic variables; moreover, the column corresponding to the $j$-th basic variable must be $e_j$, i.e., the vector has value $1$ only in the $j$-th row and $0$ in all other rows. Because these columns do not provide additional information, they are often omitted when implementing the simplex method, which yields the condensed simplex tableau.
    
    The simplex tableau can be used to more conveniently understand the steps of updating the simplex tableau. Because all simplex tableaux $T_B$ can be obtained from the same matrix $T_0$ left-multiplied by an invertible matrix $L_B$ related to the basis, i.e.,
    
    $$
    T_B=
    \begin{pmatrix}
    -c_B^TA_B^{-1}b & c^T - c_B^TA_B^{-1}A \\
    A_B^{-1}b & A_B^{-1}A 
    \end{pmatrix}
    =
    \begin{pmatrix}
    1 & -c_B^TA_B^{-1} \\
    O & A_B^{-1}
    \end{pmatrix}
    \begin{pmatrix}
    0 & c^T \\
    b & A 
    \end{pmatrix}=L_BT_0,
    $$
    
    therefore, these simplex tableaux can be transformed into each other through several [elementary row operations](./linear-algebra/elementary-operations.md). Consequently, when updating the simplex tableau, we only need to perform elementary row operations so that the column corresponding to the entering variable becomes $e_j$. From this, the required operations, when transferred to the condensed simplex tableau, are exactly the steps given above.

A reference implementation for updating the condensed simplex tableau is as follows:

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/math/code/simplex/simplex_0.cpp:pivot"
    ```

From this implementation, we can see that the time complexity of a single update of the simplex tableau is $O(mn)$. When discussing [pivot rules](#pivot-rules) later, we will see that the complexity of determining the leaving and entering variables also does not exceed $O(mn)$. Therefore, the time complexity of a single pivoting is $O(mn)$.

To facilitate understanding, the detailed steps using the condensed simplex tableau for the example shown earlier are listed here.

???+ example "Example (continued)"
    Initially, the condensed simplex tableau is as follows:
    
    $$
    \begin{array}{|l|c|ccc|}
    \hline
        &    & x_1 & x_2 & x_3 \\
    \hline
        & 0  & -10 & -12 & -12 \\
    \hline
    x_4= & 20 &   1 & 2   &   2 \\
    x_5= & 20 &   2 & 1   &   2 \\
    x_6= & 20 &   2 & 2   &   1 \\
    \hline
    \end{array}
    $$
    
    According to the reduced costs in row $0$, we can choose $x_1,x_2,x_3$ as entering variables. Let $x_1$ enter the basis. Then, according to the minimum ratio test, we can choose $x_5,x_6$ as leaving variables. Let $x_5$ leave the basis. Accordingly, update the condensed simplex tableau as follows:
    
    $$
    \begin{array}{|l|c|ccc|}
    \hline
        &    & x_5 & x_2 & x_3 \\
    \hline
        &100 & 5   & -7  & -2  \\
    \hline
    x_4= & 10 &-0.5 & 1.5 &   1 \\
    x_1= & 10 & 0.5 & 0.5 &   1 \\
    x_6= &  0 & -1  & 1   &  -1 \\
    \hline
    \end{array}
    $$
    
    According to the reduced costs in row $0$, we can choose $x_2,x_3$ as entering variables. Let $x_3$ enter the basis. Then, according to the minimum ratio test, we can choose $x_4,x_1$ as leaving variables. Let $x_4$ leave the basis. Accordingly, update the condensed simplex tableau as follows:
    
    $$
    \begin{array}{|l|c|ccc|}
    \hline
        &    & x_5 & x_2 & x_4 \\
    \hline
        &120 & 4   & -4  & 2   \\
    \hline
    x_3= & 10 &-0.5 & 1.5 &  1  \\
    x_1= &  0 &  1  & -1  & -1  \\
    x_6= & 10 & -1.5& 2.5 &  1  \\
    \hline
    \end{array}
    $$
    
    According to the reduced costs in row $0$, we can only choose $x_2$ as the entering variable. Let $x_2$ enter the basis. Then, according to the minimum ratio test, we can only choose $x_6$ as the leaving variable. Let $x_6$ leave the basis. Using the elementary row operations described earlier, update the simplex tableau as follows:
    
    $$
    \begin{array}{|l|c|ccc|}
    \hline
        &    & x_5 & x_4  & x_6 \\
    \hline
        &136 & 1.6 & 3.6 & 1.6 \\
    \hline
    x_3= & 4  & 0.4 & 0.4 &-0.6 \\
    x_1= &  4 & 0.4 & -0.6& 0.4 \\
    x_2= &  4 & -0.6& 0.4 & 0.4 \\
    \hline
    \end{array}
    $$
    
    According to the reduced costs in row $0$, there is no entering variable. Therefore, the current solution
    
    $$
    x=(4,4,4,0,0,0)^T
    $$
    
    is the optimal solution, and the (minimization problem's) optimal value is $-136$.

In addition to implementing the simplex method using the simplex tableau, we can also use the revised simplex method, which further improves the algorithm's time and space complexity, reducing the complexity of a single update to $O(m^2)$, which is especially efficient when $m\ll n$ or $A$ is a sparse matrix.

## Geometric Background

This section introduces the geometric background of the simplex method.

For the feasible region of the linear programming problem

$$
\mathcal D = \{x\in\mathbf R^n : Ax = b,~ x\ge 0\}
$$

the [analysis](./linear-programming.md#feasible-region-and-problem-solutions) shows:

-   The optimal solution to a linear programming problem (if it exists) can always be chosen as a vertex of the feasible region $\mathcal D$. Solving the linear programming problem is transformed into finding the vertex with the best value function among all vertices.
-   The coordinates of each vertex can be obtained by solving the system of equations formed by $n$ tight constraints. For constraints in standard form, all $m$ equality constraints are definitely tight, and the remaining $n-m$ constraints can only be selected from the non-negativity constraints. Selecting these non-negativity constraints as tight constraints is equivalent to setting the corresponding decision variables $x_N$ to $0$; correspondingly, the system of equations $Ax = b$ degenerates into a linear system $A_Bx_B = b$ about the remaining $m$ decision variables $x_B$. As long as $A_B$ is invertible, we can solve $x_B = A_B^{-1}b$. This yields a solution $(x_B,x_N)=(A_B^{-1}b,0)$; if $x_B\ge 0$, this is the coordinates of a vertex of $\mathcal D$.

It is easy to see that the concept of vertex solutions is consistent with the basic feasible solutions defined earlier. Therefore, as long as we find the optimal one among all basic feasible solutions, we can obtain the optimal solution to the original problem. Although this greatly simplifies the problem, the number of vertices of the feasible region is exponential, so exhaustive search is not practical.

To solve this difficulty, we can consider moving along the [edges](./linear-programming.md#feasible-region-and-problem-solutions) of the feasible region, moving from one vertex to an adjacent vertex. Because adjacent vertices must lie on the same edge, they share at least $n-1$ tight constraints. That is, the tight constraints of adjacent vertices can differ by at most one. Therefore, for a basic feasible solution $x$, by replacing one of its basic variables with a non-basic variable, we can obtain an **adjacent** (adjacent) basic feasible solution $x'$. This is exactly the pivoting operation.

Therefore, the simplex method, starting from a basic feasible solution and continuously performing pivoting to improve the objective function, is actually, on the corresponding feasible region, starting from a vertex and continuously moving to adjacent vertices, thereby improving the objective function.

???+ example "Example (continued)"
    In the example discussed in this article, the feasible region is a three-dimensional polyhedron with five vertices, as shown in the figure below:
    
    ![](./images/simplex-geo.svg)
    
    From a geometric perspective, the solving process described above corresponds to the following path between the vertices of the polyhedron:
    
    $$
    (0,0,0) \rightarrow (0,0,10) \rightarrow (10,0,0) \rightarrow (4,4,4).
    $$

## Implementation Details

Using the simplex tableau, we can already solve many linear programming problems. However, for the most general case, there are still many details in the simplex method worth discussing in depth.

### Slack Form

The method for transforming a general linear programming problem into standard form has been discussed. However, to facilitate solving using the simplex method, we also need to ensure that the coefficient matrix $A$ has full rank. Although the method of first converting to standard form and then eliminating linearly dependent constraints is feasible, for simplicity of solution, the following strategy is usually adopted:

1.  Transform the linear programming problem into **inequality form** (inequality form), i.e., the form $\min\{c^Tx : Ax \le b,~ x \ge 0\}$;
2.  By adding slack variables $s$, transform the problem into standard form: $\min\{c^Tx : Ax + s = b,~ x\ge 0,~ s \ge 0\}$.

The benefit of doing this is that the resulting standard form's coefficient matrix $(A,I)$ always has full rank, and there always exists a (not necessarily feasible) basic solution $(x,s)=(0,b)$. This special standard form is also called **slack form** (slack form).

### Initial Basic Feasible Solution

The simplex method described earlier always assumes that a basic feasible solution is known. Sometimes, it is easy to find a basic feasible solution. For example, if in the slack form above $b\ge 0$, then $(x,s)=(0,b)$ is a basic feasible solution. This is the situation encountered in the numerical example earlier.

For the general case, we can use the **two-phase method** (two-phase method). In the two-phase method, we need to run the simplex method twice. The first phase solves a feasibility linear programming problem to obtain a basic feasible solution to the original problem. The second phase starts from this basic feasible solution and applies the simplex method to solve the original problem.

Suppose we have a problem in standard form $\min\{c^Tx : Ax = b \ge 0,~ x\ge 0\}$. In the first phase, we need to solve the problem

$$
\min\{1^Tx_a : Ax + x_a = b,~ x\ge 0,~ s\ge 0\}.
$$

This is essentially a feasibility linear programming problem, where the newly added variable $x_a$ is also called an **artificial variable** (artificial variable). It always has a basic feasible solution $(x,x_a)=(0,b)$, so we can directly use the simplex method to solve it. If the optimal value of this problem is strictly greater than $0$, then there is no $x\ge 0$ such that $Ax=b$, i.e., the original problem is infeasible. If the optimal value of this problem equals $0$, then in its optimal solution, artificial variables can only be zero. If some artificial variables are still basic variables, we can perform several pivots to move them out of the basis. Finally, when all artificial variables are non-basic variables, the basic solution obtained in the first phase can be used as the initial basic feasible solution for the second phase.

???+ note "Implementation of the first phase without explicitly introducing artificial variables"
    When implementing the first phase, there is no need to explicitly introduce artificial variables. For any initially selected basis $B$, we have
    
    $$
    x_B + A_B^{-1}A_Nx_N = A_B^{-1}b.
    $$
    
    If $(A_B^{-1}b)_j\ge 0$, then no artificial variable needs to be introduced; otherwise, we need to additionally introduce artificial variables $x^{-}_{B_j}$, i.e.,
    
    $$
    x_{B_j} - x^-_{B_j} + (A_B^{-1}A_N)_{(j)}x_N = (A_B^{-1}b)_j.
    $$
    
    Let the index set $L:=\{j:(A_B^{-1}b)_j<0\}$, then the simplex tableau for the first phase is obtained by several elementary row operations from the following simplex tableau:
    
    $$
    \begin{array}{|r|c|cccc|}
    \hline
                    &                       & x_N                      & x_{B_{\sim L}} & x_{B_L}  &x_{B_{L}}^- \\  
    \hline
                    & 0                     & 0^T                      & 0^T            & 0^T      & 1^T        \\
    \hline
    x_{B_{\sim L}}=  & (A_B^{-1}b)_{\sim L}  & (A_B^{-1}A_N)_{(\sim L)} & I              &  O       &  O         \\
    x_{B_{L}}^-=     & (A_B^{-1}b)_L         & (A_B^{-1}A_N)_{(L)}      & O              &  I       & -I         \\
    \hline
    \end{array}
    $$
    
    Similar to simplifying the simplex tableau to the condensed simplex tableau, it can be appropriately simplified: (multiply the $x_{B_{L}}^-$ row by $1^T$ and add it to row $0$, then omit the last three columns)
    
    $$
    \begin{array}{|r|c|cccc|}
    \hline
                    &                      & x_N                      \\  
    \hline
                    & 1^Tb_L               & 1^T(A_B^{-1}A_N)_L       \\
    \hline
    x_{B_{\sim L}}= & (A_B^{-1}b)_{\sim L} & (A_B^{-1}A_N)_{(\sim L)} \\
    -x_{B_{L}}=     & (A_B^{-1}b)_L        & (A_B^{-1}A_N)_L          \\
    \hline
    \end{array}
    $$
    
    This is mostly consistent with a normal condensed simplex tableau, except that the last row has a negative sign on the variable, indicating that this row still contains artificial variables, i.e., the original slack variables are still infeasible. Using this tableau, the pivoting process is as follows:
    
    1.  If $L=\varnothing$, the algorithm terminates.
    2.  Otherwise, select the entering variable $x_{N_i}$ according to the condition that the reduced cost in row $0$ is negative. If none exists, then the original problem is infeasible, and the algorithm terminates.
    3.  Then select the leaving variable $x_{B_j}$ according to column $i$. Still use the minimum ratio test, but require ensuring that current feasible variables remain feasible and current infeasible variables remain infeasible, i.e., select
    
        $$
        \arg\min_{j}\left\{\dfrac{(\tilde T_B)_{j0}}{(\tilde T_B)_{ji}}:(j\notin L\land(\tilde T_B)_{ji}>0)\lor(j\in L\land(\tilde T_B)_{ji}<0)\right\}
        $$
    
        as the row where the leaving variable is located. If there are multiple such leaving variables, prioritize the infeasible leaving variable.
    4.  Let $x_{N_i}$ enter the basis, $x_{B_j}$ leave the basis, and update the simplex tableau.
    5.  If $j\in L$, then remove $j$ from $L$ (i.e., remove the negative sign from that row), and add $1$ to $(\tilde T_B)_{0i}$.
    
    The reason we can omit the columns containing artificial variables is that if they are still basic variables, then their corresponding columns are $e_j$ and need not be recorded, and if they are no longer basic variables, they will not enter the basis again and need not be recorded. When an artificial variable leaves the basis, it needs to be replaced with the corresponding non-artificial variable, which is exactly the purpose of the last step in the above process.
    
    A reference implementation is as follows:
    
    ??? example "Reference Implementation"
        ```cpp
        --8<-- "docs/math/code/simplex/simplex_0.cpp:initialize"
        ```
    
    Before the start of phase 1, add an extra row to record the objective function of phase 1. When pivoting, pivot the entire tableau, including the objective function of phase 2. In this way, when phase 1 is completed, the objective function of phase 2 is also updated accordingly, and we can directly start the simplex method of phase 2.

The two-phase method can also be implemented in a single simplex method. By taking a sufficiently large positive number $M$, we can obtain the optimal solution to the original problem by directly solving the problem

$$
\min\{c^Tx + M1^Tx_a : Ax + x_a = b,~ x\ge 0,~ s\ge 0\}.
$$

In implementation, we do not assign a specific value to $M$, but treat it as an unknown sufficiently large positive number for computation. This method is called the **big M method** (big $M$ method).

???+ warning "The naive algorithm's actual efficiency is exponential"
    Because the slack form always has an initial basic solution, only it may not be feasible, a simple idea for finding an initial basic feasible solution is to start from an infeasible basic solution and repeatedly use pivoting operations to move infeasible basic variables out of the basis, and select the non-basic variable corresponding to the column that is also negative in the corresponding row as the entering variable, until all basic variables are non-negative. A reference implementation is as follows:
    
    ??? example "Reference Implementation"
        ```cpp
        --8<-- "docs/math/code/simplex/simplex_2.cpp:initialize"
        ```
    
    Although this is simple, compared to the two-phase method, it lacks an objective function describing the current degree of infeasibility of the basis, so it lacks a clear direction for improvement. Actual tests show that compared to the two-phase method or big M method, which usually only require $O(m)$ pivots, this naive algorithm typically requires $O(2^m)$ pivots, and when $n,m$ are large, it is easy to fall into a cycle. Although the constant in the number of pivots of the naive algorithm is small, it is only suitable for cases where $n,m<50$.

### Pivot Rules

When pivoting, if there are multiple optional entering or leaving variables, we need to use **pivot rules** (pivot rules) to decide which variable to choose as the entering or leaving variable. Using the simplex tableau, all rules discussed in this section can find the entering and leaving variables in $O(mn)$ time. Therefore, the time complexity of a single pivoting is still $O(mn)$.

The selection of the entering variable often determines the number of pivots before the algorithm terminates. Common rules are as follows:

-   Select the first entering variable found;
-   Select the entering variable with the smallest index; (part of Bland's rule)
-   Select the entering variable with the largest absolute reduced cost (i.e., $|c_i|$); (Dantzig's rule)
-   Select the entering variable with the largest improvement in the value function per pivot (i.e., $|c_i|\theta_i$);
-   Select the entering variable corresponding to the steepest edge, i.e., the one with the largest improvement in the value function per unit length moved along the edge (i.e., $|c_i|/\|A_B^{-1}A_i\|$);
-   Randomly select an entering variable.

In practice, the steepest edge rule has the highest efficiency[^steepest-edge]. It is generally believed that with appropriate pivot rules, most problems can be solved within approximately $2m$ pivots. However, for all currently known pivot rules, there are specially constructed examples[^klee-minty] that can push the number of pivots to exponential order. This is exactly why the simplex method has quite excellent practical running efficiency but has exponential worst-case theoretical complexity.

The selection of the leaving variable often determines whether the algorithm will fall into a cycle. If there are multiple basic feasible solutions with the same optimal value, the algorithm may cycle among these basic feasible solutions. Such cases are not common, so many implementations of the simplex method do not specify a rule for selecting the leaving variable. There are two common rules for avoiding cycling:

-   Bland's rule: always select the entering variable and leaving variable with the smallest index.
-   Lexicographic rule: always select the leaving variable $x_{B_j}$ corresponding to the row number $j$ that has $(A_B^{-1}A_i)_j>0$ and
    
    $$
    \left(\dfrac{(A_B^{-1}b)_j}{(A_B^{-1}A_i)_j},\dfrac{(A_B^{-1})_{j1}}{(A_B^{-1}A_i)_j},\cdots,\dfrac{(A_B^{-1})_{jm}}{(A_B^{-1}A_i)_j}\right)
    $$
    
    is lexicographically minimal. The selection of the entering variable is not important.
    
    Note that if the linear programming problem is in slack form, then these quantities can all be directly found from the simplex tableau $T_B$ described earlier; otherwise, after finding an initial basic solution (not necessarily feasible), we can use the coefficients of the columns corresponding to the basic variables in this initial basis (with fixed order) as the coefficients of $A_B^{-1}$.

Bland's rule is very inefficient because the rule itself has the same selection method for entering and leaving variables, which can easily cause the same variable to repeatedly enter and leave the basis. Relatively speaking, the lexicographic rule is more practical. The lexicographic rule is equivalent to slightly perturbing the parameters in the linear programming problem[^lexico], so that there are no basic feasible solutions with the same optimal value, and thus there is no possibility of cycling.

## Reference Implementation

This section provides a reference implementation of the two-phase simplex method based on the condensed simplex tableau.

??? example "[Luogu P13337 [Template] Linear Programming](https://www.luogu.com.cn/problem/P13337)"
    ```cpp
    --8<-- "docs/math/code/simplex/simplex_0.cpp:full-text"
    ```

## Example Problems

???+ example "[NOI2008] Volunteer Recruitment](https://www.luogu.com.cn/problem/P3980)"
    A total of $n$ days of activities require recruiting volunteers, where at least $b_i$ volunteers are needed on day $i$. There are always $m$ types of volunteers, where type $j$ volunteers can serve consecutive dates $[l_j,r_j]$, and the unit recruitment cost is $c_i$. Find the optimal recruitment plan to minimize the cost of recruiting volunteers.

??? note "Solution"
    Let $x_j$ be the number of type $j$ volunteers recruited. Then we can list the linear programming problem as
    
    $$
    \begin{align*}
    \max_{x}\; & \sum_{j=1}^mc_jx_j \\
    \text{subject to }& \sum_{i=1}^n a_{ij}x_j \ge b_i,~i=1,\cdots,n,\\
    & x_j\ge 0,~j=1,\cdots,m.
    \end{align*}
    $$
    
    where the coefficients
    
    $$
    a_{ij} = 
    \begin{cases}
    1,& l_j\le i\le r_j,\\
    0,& \text{otherwise.}
    \end{cases}
    $$
    
    The original problem does not have an obvious initial feasible solution. Therefore, consider its [dual problem](./linear-programming.md#dual-problems):
    
    $$
    \begin{align*}
    \min_{y}\; & \sum_{i=1}^n b_iy_i \\
    \text{subject to } & \sum_{j=1}^na_{ij}y_i \le c_j,~j=1,\cdots,m,\\
    & y_i\ge 0,~i=1,\cdots,n.
    \end{align*}
    $$
    
    By adding slack variables, it is easy to obtain an initial feasible solution, so we can skip phase 1 and directly use the simplex method to solve it. According to the duality principle, the solution obtained is the solution to the original problem.
    
    ```cpp
    --8<-- "docs/math/code/simplex/simplex_1.cpp"
    ```

## Exercises

-   [Luogu P13337 [Template] Linear Programming](https://www.luogu.com.cn/problem/P13337)
-   [UOJ#179. Linear Programming](https://uoj.ac/problem/179)
-   [Luogu P4232 Hiding Beyond Consciousness](https://www.luogu.com.cn/problem/P4232)
-   [Codeforces 1430 G. Yet Another DAG Problem](https://codeforces.com/problemset/problem/1430/G)
-   [AtCoder Beginner Contest 231 H - Minimum Coloring](https://atcoder.jp/contests/abc231/tasks/abc231_h)

## References

-   [Linear Programming Simplex Method [Detailed Explanation + Diagram]](https://www.cnblogs.com/ECJTUACM-873284962/p/7097864.html)
-   [2016 National Training Team Paper](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2016%E8%AE%BA%E6%96%87%E9%9B%86.pdf)
-   Introduction to Algorithms
-   Matoušek, Jiří, and Bernd Gärtner. Understanding and using linear programming. Vol. 1. Berlin: Springer, 2007.
-   Inayatullah, Syed, Nasir Touheed, and Muhammad Imtiaz. "A streamlined artificial variable free version of simplex method." PloS one 10, no. 3 (2015): e0116156.
-   Floudas, Christodoulos A., and Panos M. Pardalos, eds. Encyclopedia of optimization. Springer Science & Business Media, 2008.

[^notation]: In principle, since all vectors are column vectors by default, $(x_B,x_N)$ should be written as $(x_B^T,x_N^T)^T$. However, to simplify notation, this article writes all similar cases directly as $(x_B,x_N)$ and omits the transpose symbol.

[^steepest-edge]: For test results, see Forrest, John J., and Donald Goldfarb. "Steepest-edge simplex algorithms for linear programming." Mathematical programming 57, no. 1 (1992): 341-374.

[^klee-minty]: A classic counterexample can be found in Klee, Victor, and George J. Minty. "How good is the simplex algorithm." Inequalities 3, no. 3 (1972): 159-175.

[^lexico]: For a detailed explanation, see [this lecture note](https://misha.fish/archive/docs/3272-fall-2022/lecture8.pdf).