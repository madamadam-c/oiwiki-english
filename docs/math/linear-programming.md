author: Ir1d, YZircon, huhaoo, QAQAutoMaton, Enter-tainer, Marcythm, sshwy, partychicken, Konano, H-J-Granger, baker221, isdanni, ksyx

## Introduction

Linear programming (LP) is a general term for methods that study the extremal values of linear objective functions under linear constraints. It is a branch of operations research with applications in many fields. Some special cases of linear programming, such as network flow and multi-commodity flow problems, may appear in programming contest problems. In programming contests, problems that can only be solved by linear programming algorithms are extremely rare; most such problems can be solved more efficiently through network flow modeling and other methods.

### A Simple Example

For a problem to be expressed in the form of linear programming, there must be several linear constraints and a linear objective function.

Consider the following example:

???+ example "Example"
    The breakfast master can make a certain number of buns and fried dough sticks every day. These two breakfast items are very popular among customers. To maximize profit, the master wants to make as much breakfast as possible, but in actual operation, they are limited by various resources such as ingredients and time. To this end, the master recorded the ingredients needed, cooking time, and corresponding profit for each breakfast item as follows:
    
    | Breakfast | Vegetable Oil | Flour | Time | Profit |
    | :-: | :-: | :-: | :-: | :-: |
    | Bun | $4$ | $7$ | $8$ | $5$ |
    | Fried Dough | $7$ | $3$ | $6$ | $6$ |
    
    Suppose the master can purchase at most $66$ units of vegetable oil and $60$ units of flour per day, and can invest at most $96$ units of cooking time. Then, how should the master reasonably arrange the production quantities of buns and fried dough to maximize daily profit?

In mathematical terms, let $x_1$ and $x_2$ be the number of buns and fried dough sticks the master makes, respectively. Then, "total vegetable oil required does not exceed $66$ units" can be expressed as

$$
4x_1 + 7x_2 \le 66.
$$

Similarly, "total flour required does not exceed $60$ units" and "total time required does not exceed $96$ units" can be expressed as

$$
\begin{aligned}
7x_1 + 3x_2 &\le 60,\\
8x_1 + 6x_2 &\le 96.
\end{aligned}
$$

Additionally, the master cannot produce a negative number of breakfast items, so we also have

$$
x_1,x_2\ge 0.
$$

The master wants to maximize profit under these constraints:

$$
z = 5x_1 + 6x_2.
$$

This is a typical linear programming problem. Its objective function is a linear function of the decision variables, and its constraints consist of linear equalities or inequalities formed by the decision variables.

### Graphical Method

For linear programming problems with only two decision variables, the problem can be solved intuitively using the graphical method.

Consider the problem in this section

$$
\begin{aligned}
\max_{x_1,x_2}\;& z = 5x_1 + 6x_2 \\
\text{subject to } & 4x_1 + 7x_2 \le 66,\\
& 7x_1 + 3x_2 \le 60,\\
& 8x_1 + 6x_2 \le 96,\\
& x_1,x_2\ge 0
\end{aligned}
$$

The corresponding geometric figure. The last constraint means that all feasible points $(x_1,x_2)$ lie in the first quadrant, while the other three constraints mean that feasible points must lie below the lines $4x_1 + 7x_2 = 66$, $7x_1 + 3x_2 = 60$, and $8x_1 + 6x_2 = 96$. The intersection of these regions (the green region shown in the figure below) is the set of all feasible points:

![](images/linear-programming.svg)

Next, we need to maximize the value of $z=5x_1+6x_2$. If we consider this equation as representing the line $5x_1+6x_2=z$, then as $z$ changes, we get a family of parallel lines, and larger $z$ values move the line toward the upper right. Therefore, we only need to keep moving the line until it reaches a critical position where moving it slightly further to the upper right would make it no longer intersect with the region shown in the figure. The $z$ value corresponding to this line is the maximum value sought.

As shown in the figure, this situation occurs at the red point. It is the intersection of the line $4x_1 + 7x_2 = 66$ and the line $7x_1 + 3x_2 = 60$. Solving the two line equations simultaneously shows that its coordinates are $(6,6)$. This is the unique optimal solution for this problem. The breakfast master's maximum profit is $z=66$.

When the problem involves more than two decision variables, the graphical method is no longer applicable. However, some observations from this example still hold. Each inequality constraint in a linear programming problem describes a "half-plane", and the set of all feasible solutions is the intersection of these "half-planes", which is always a "convex polygon". The optimal solution to a programming problem can always be obtained at some "vertex" of this "convex polygon". The coordinates of these "vertices" can be obtained by solving the equations of the "boundaries" of these "half-planes" simultaneously. Extending these observations to higher dimensions leads to an efficient method for solving linear programming problems—the simplex method. This is also the most commonly applied method in programming contests.

Another noteworthy issue is that, in principle, the buns and fried dough sticks made by the master are not infinitely divisible and should be integers. Although this constraint was not explicitly stated in the solution process, since the final optimal solution is indeed an integer, the answer to this problem remains feasible even with the integer constraint. However, for many programming problems, the optimal solution may not be obtainable at integer points. These problems are actually a type of integer programming problem, not simple linear programming problems. This class of problems is briefly discussed at the end of this article.

## Basic Concepts

This section introduces the basic concepts of linear programming problems.

### Linear Programming Problem

A linear programming problem $P$ typically consists of two parts:

-   A linear objective function, i.e., a function of the form

    $$
    f(x_1,x_2,\cdots,x_n)=c_1x_1+c_2x_2+\cdots+c_nx_n
    $$

    where $c_i\in\mathbf R$ are constants;

-   Linear constraints, i.e., inequality or equality constraints of the form

    $$
    g_j(x_1,x_2,\cdots,x_n)=a_{j1}x_1+a_{j2}x_2+\cdots+a_{jn}x_n \le (=,\ge) b_j
    $$

    where $a_{ji},b_j\in\mathbf R$ are all constants.

A linear programming problem is to maximize or minimize the objective function subject to the given constraints. A solution $(x_1,x_2,\cdots,x_n)\in\mathbf R^n$ that satisfies the given constraints is called a **feasible solution**; among all feasible solutions, the one that achieves the extremal value of the objective function is called an **optimal solution**.

### Standard Form

To facilitate description and further processing, it is customary to specify a standard form for linear programming problems. Different literature may have different conventions. This article adopts the following standard form for linear programming:

$$
\begin{aligned}
\min_{\{x_i\}}\;& \sum_{i=1}^n c_ix_i \\
\text{subject to }& \sum_{i=1}^n a_{ji}x_i = b_i \ge 0,~j=1,\cdots,m,\\
& x_i \ge 0,~i = 1,\cdots,n.
\end{aligned}
$$

That is, the linear programming problem is a minimization problem, all decision variables have non-negativity constraints, and in addition, it contains only several equality constraints with non-negative right-hand side constants. This problem can be expressed more concisely using [matrices](./linear-algebra/matrix.md):

$$
\max\{c^Tx : Ax = b \ge 0,~ x\ge 0\}.
$$

Here, $x=(x_i)\in\mathbf R^n$ is the decision variable, $b=(b_j)\in\mathbf R^m$ and $A=(a_{ji})\in\mathbf R^{m\times n}$ are the constants involved in the constraints. The size of a linear programming problem refers to the number of its decision variables and the number of its constraints.

???+ tip "Vector Inequality"
    This article will repeatedly encounter vector inequalities like $b \ge 0$. Generally, for vectors $x,y\in\mathbf R^n$, the inequality $x\le y$ means $\forall i(x_i\le y_i)$, i.e., a component-wise comparison in the real number sense. This relation is a [partial order relation](./order-theory.md#binary-relations) on the vector space, meaning that there exist two vectors that cannot be compared.

The choice of standard form is only for convenience of presentation and has no special significance, because any linear programming problem can be equivalently written in one of the following six forms:

$$
\begin{aligned}
&\min\{c^Tx : Ax = b,~ x\ge 0\},\\
&\min\{c^Tx : Ax \ge b\},\\
&\min\{c^Tx : Ax \ge b,~ x\ge 0\},\\
&\max\{c^Tx : Ax = b,~ x\ge 0\}, \\
&\max\{c^Tx : Ax \le b\},\\
&\max\{c^Tx : Ax \le b,~ x\ge 0\}.\\
\end{aligned}
$$

The following operations can transform any linear programming problem equivalently into one of these six forms:

1.  By adding a negative sign, i.e., changing $c$ to $-c$, maximization and minimization problems can be interchanged.
2.  By adding a negative sign, i.e., replacing $a_j^Tx \lesseqqgtr b_j$ with $-a_j^Tx \gtreqqless -b_j$, the two directions of inequality constraints can be interchanged, or the right-hand side constant of an equality constraint can be made non-negative.
3.  All equality constraints $a_j^Tx = b_j$ can be replaced by two opposite inequality constraints $a_j^Tx \ge b_j$ and $a_j^Tx \le b_j$.
4.  All inequality constraints $a_j^Tx \le(\ge) b_j$ can be converted to equality constraints $a_j^Tx +(-) s_j = b_j$ along with the corresponding non-negativity constraint $s_j\ge 0$ by adding non-negative slack variables $s_j$.
5.  If a decision variable $x_i$ has no non-negativity constraint, it can be replaced by the difference of two non-negative variables, i.e., $x_j = x^+_j - x^-_j$ with $x^+_j,x^-_j \ge 0$.

The size of the linear programming problem obtained through these transformations does not exceed twice the size of the original problem, and the feasible solutions and optimal solutions of these problems can be easily transformed into each other. Therefore, for general forms of linear programming problems, we can always first transform them into standard form (or one of the six forms above) before solving them.

??? example "Example"
    Consider the linear programming problem
    
    $$
    \begin{aligned}
    \max\;& 3x_1 - 2x_2 + x_3 \\
    \text{subject to }& 2x_1 + 3x_2 + 4x_3 \ge 1,\\
    & 3x_1 + 4x_2 \le 5,\\
    & 5x_2 - x_3 = -1, \\
    & x_1, x_2 \ge 0.
    \end{aligned}
    $$
    
    Through operations 1, 2, and 3, it can be transformed into the form $\min\{c^Tx : Ax \ge b\}$, i.e.,
    
    $$
    \begin{aligned}
    \min\;& -3x_1 + 2x_2 - x_3 \\
    \text{subject to }& 2x_1 + 3x_2 + 4x_3 \ge 1,\\
    & -3x_1 - 4x_2 \ge -5,\\
    & 5x_2 - x_3 \ge -1, \\
    & -5x_2 + x_3 \ge 1, \\
    & x_1 \ge 0,\\
    & x_2 \ge 0.
    \end{aligned}
    $$
    
    Through operations 4 and 5, it can be transformed into the form $\max\{c^Tx : Ax = b,~ x\ge 0\}$, i.e.,
    
    $$
    \begin{aligned}
    \max\;& 3x_1 - 2x_2 + x^+_3 - x^-_3 \\
    \text{subject to }& 2x_1 + 3x_2 + 4x^+_3 - 4x^-_3 - x_4 = 1,\\
    & 3x_1 + 4x_2 + x_5 = 5,\\
    & 5x_2 - x^+_3 + x^-_3 = -1, \\
    & x_1, x_2, x^+_3, x^-_3, x_4, x_5 \ge 0.
    \end{aligned}
    $$

### Feasible Region and Problem Solutions

The set of all feasible solutions $\mathcal D\subseteq\mathbf R^n$ is called the **feasible region** (feasible region) of the linear programming problem $P$. From a geometric perspective, each inequality constraint $a_j^T x \le b_j$ describes a half-space $\{x\in\mathbf R^n:a_j^T x \le b_j\}$, and each equality constraint $a^T_jx = b_j$ describes a hyperplane $\{x\in\mathbf R^n:a_j^Tx=b_j\}$. Therefore, the feasible region is always the intersection of a finite number of half-spaces and hyperplanes. In the optimization field[^poly-names], such geometric objects are usually called **polyhedra** (polyhedron) in $\mathbf R^n$. A polyhedron is always a closed convex set, but may not be bounded. A bounded polyhedron is also called a **polytope** (polytope). A polytope can be considered as the generalization of polygons in the plane to higher dimensions, and a polyhedron further extends this to possibly unbounded cases.

???+ example "Examples of Polyhedra"
    Some common polyhedra are listed here:
    
    1.  The empty set $\varnothing$, also called a **nullitope** (nullitope), with dimension defined as $-1$.
    2.  **Affine subspaces** (affine subspace), i.e., the intersection of several hyperplanes $\{x\in\mathbf R^n:Ax = b\}$. It is equivalent to the solution set of the system of linear equations $Ax = b$: when the system has no solution, it is the empty set; otherwise, it can always be written in the form $x_0+V$, where $x_0\in\mathbf R^n$ and $V\subseteq\mathbf R^n$ is a linear subspace of dimension $n-\operatorname{rank}(A)$. In particular, hyperplanes are also affine subspaces.
    3.  **Polyhedral cones** (polyhedral cone), i.e., the set of all non-negative linear combinations of a finite number of points $\{x_i\}$ in space $\{\sum_i\alpha_ix_i:\alpha_i\ge 0\}$. It is a convex cone with its vertex at the origin. Equivalently, it can be viewed as a polyhedron bounded by several hyperplanes passing through the origin, i.e., $\{x\in\mathbf R^n : Ax\le 0\}$. In particular, half-spaces are also polyhedral cones.
    4.  Polytopes, i.e., bounded polyhedra. In particular, polytopes of dimensions $-1$, $0$, $1$, $2$, and $3$ are the commonly known empty set, point, line segment, polygon, and (ordinary) polyhedron, respectively. A set is a polytope if and only if it is the convex hull of a finite number of points $\{x_i\}$ $\{\sum_i\alpha_ix_i:\alpha_i\ge 0,~\sum_i\alpha_i=1\}$. A $k$-dimensional polytope is at least the convex hull of $k+1$ points.
    5.  **Simplex** (simplex), i.e., a $k$-dimensional polytope generated by exactly $k+1$ points. It is the simplest $k$-dimensional polytope. In particular, polytopes of dimensions $-1$, $0$, $1$, $2$, and $3$ are the empty set, point, line segment, triangle, and tetrahedron, respectively. The simplest example of a $k$-dimensional simplex is $\{x\in\mathbf R^k:x_i\ge 0,~\sum_ix_i=1\}$. In fact, any $k$-dimensional simplex can be transformed into this special case through affine transformation (i.e., translation and scaling). It is worth noting that the simplex method is not actually performed on a simplex.

Any polyhedron can be viewed as the [Minkowski sum](../geometry/convex-hull.md#minkowski-sum) of a polyhedral cone and a polytope: the former describes the unbounded part of the polyhedron, and the latter describes the shape of the bounded part. This polyhedral cone is unique: the polyhedral cone obtained from decomposing the polyhedron $\{x\in\mathbf R^n:Ax\le b\}$ must be $\{x\in\mathcal R^n:Ax\le 0\}$.

The solutions of linear programming are closely related to the structure of polyhedra. For a polyhedron $\mathcal D\in\mathbf R^n$ and a vector $c\in\mathbf R^n\setminus\{0\}$, consider the following linear programming problem $P$ (the minimization case can be discussed similarly):

$$
\max\{c^Tx:x\in\mathcal D\}.
$$

From a geometric perspective, this is equivalent to moving the hyperplane $H:c^Tx = z$ along the direction of vector $c$ as far as possible while ensuring that it has at least one intersection with the feasible region $\mathcal{D}$. There are three possibilities:

-   The feasible region $\mathcal D$ is empty. This means problem $P$ has no feasible solution; some of its constraints are mutually contradictory. In this case, problem $P$ is called **infeasible** (infeasible), and its optimal value is defined as $-\infty$.

-   The feasible region $\mathcal D$ is non-empty, but it contains a ray with direction vector $c$, i.e., there exists $x_0\in\mathbf R^n$ such that $x_0+tc\in\mathcal D$ holds for all $t\ge 0$. Because the hyperplane $H$ can be continuously moved in the direction of vector $c$, and during the movement, the set $H\cap\mathcal D$ always contains at least one point on this ray and is therefore non-empty, the objective function $c^Tx = c^Tx_0 + tc^Tc$ can take arbitrarily large values. In this case, problem $P$ is called **unbounded** (unbounded), and its optimal value is defined as $+\infty$.

-   The feasible region $\mathcal D$ is non-empty and contains no ray with direction vector $c$. In this case, problem $P$ is called **bounded** (bounded). Let $z^*\in\mathbf R$ be the optimal value of problem $P$. The hyperplane $H^*:c^Tx = z^*$ is in a critical position: it intersects with the polyhedron $\mathcal D$, and $\mathcal D$ is contained in the half-space $\{x:c^Tx\le z^*\}$. Such a hyperplane is called a **supporting hyperplane** (supporting hyperplane) of the polyhedron $\mathcal D$. The optimal solution set of problem $P$ is $H^*\cap\mathcal D$. As the intersection of a supporting hyperplane and a polyhedron, the set $H^*\cap\mathcal D$ is always a polyhedron and is contained in the boundary of $\mathcal D$. It is called a **face** (face) of the polyhedron $\mathcal D$. Intuitively, a polyhedron is enclosed by these faces. In addition to the faces formed by the intersection of supporting hyperplanes and the polyhedron, a polyhedron generally has two more faces: the empty set and the polyhedron itself. All faces of a polyhedron form a [lattice](./order-theory.md#directed-sets-and-lattices) structure under set inclusion.

    A face of a $d$-dimensional polyhedron must have dimension between $0$ and $d$. A face of dimension $0$ (i.e., a point) is called a **vertex** (vertex) or **corner point** (corner point) of polyhedron $\mathcal D$, a face of dimension $1$ is called an **edge** (edge) of $\mathcal D$, and a face of dimension $d-1$ is called a **facet** (facet) of $\mathcal D$. However, not all polyhedra have vertices. Because a face of a polyhedron is still a face of the polyhedron, and only affine subspaces have no strictly smaller non-empty faces, all minimal faces of polyhedron $\mathcal D$ are affine subspaces. Moreover, the minimal faces of the same polyhedron have the same dimension; in particular, the minimal faces of polyhedron $\mathcal D=\{x\in\mathbf R^n:Ax\le b\}$ have dimension $n-\operatorname{rank}A$.

    Because a face of a polyhedron is exactly the solution set of a bounded linear programming problem, we need to understand how to determine the equations of faces of a polyhedron. Suppose polyhedron $\mathcal D$ is described by several constraints $a_j^Tx \lesseqqgtr b_j$, and $F$ is a face of $\mathcal D$. If a constraint attains equality at all $x\in F$, it is said to be **tight** (tight) on face $F$. Points on face $F$ obviously satisfy the system of equations obtained from these tight constraints taking equality, and the intersection of the affine subspace determined by this system of equations and the polyhedron $\mathcal D$ is face $F$. Conversely, by arbitrarily selecting a subset of constraints of $\mathcal D$, taking them as equalities, solving them simultaneously, and taking the intersection with $\mathcal D$, we obtain a face of $\mathcal D$. Moreover, the more tight constraints are selected, the smaller the resulting face is (under inclusion).

    In particular, for the feasible region $\mathcal D=\{x\in\mathbf R^n:Ax=b,~x\ge 0\}$ of a linear programming problem in standard form, the rank of the coefficient matrix $\begin{pmatrix}A\\ I\end{pmatrix}$ is $n$. Therefore, its minimal faces are its vertices. That is, if the problem is bounded, its optimal solution can always be chosen as some vertex. Moreover, this vertex can be obtained by selecting $n$ linearly independent tight constraints and solving them simultaneously. This is precisely the convenience of the standard form of linear programming.

???+ example "Example"
    In the figure below, $\mathcal D$ is the feasible region. When the coefficients in the objective function are $c_1$, $c_2$, and $c_3$, they correspond to the three cases of unique optimal solution, multiple optimal solutions, and unbounded, respectively. For the first two cases, the corresponding red thick solid lines are (one of) the supporting hyperplane(s) of the solution sets, and the optimal solution sets are the vertex $B$ and the edge $\overline{CD}$ of polyhedron $\mathcal D$, respectively. For the third case, because the feasible region $\mathcal D$ contains a ray in direction $c_3$, the hyperplane with normal vector $c_3$ can continuously move in direction $c_3$, and thus the problem is unbounded.
    
    ![](./images/lp-feasible.svg)

These discussions ignore the case where $c=0$. In this case, the linear programming problem obviously cannot be unbounded, so either the problem itself is infeasible, or the optimal value equals $0$, and the optimal solution set is $\mathcal D$ itself. This special type of linear programming is also called **feasibility linear programming** (feasibility linear programming).

It is worth noting that determining whether a linear programming problem is feasible or bounded, and finding feasible solutions for a system of inequalities, are all as difficult as solving the linear programming problem itself[^reducible]. For example, the proof of the strong duality theorem below shows that solving a bounded linear programming problem is equivalent to finding a feasible solution to a system of inequalities. Therefore, for tasks such as determining whether a system of inequalities has solutions or whether a system of equations has non-negative solutions, the most effective method is to solve the corresponding feasibility linear programming problem[^other-methods].

Additionally, if a constraint of a linear programming problem is not tight on any face of the feasible region, then this constraint is **redundant** (redundant). In the breakfast master example at the beginning of this article, the working time constraint is a redundant constraint. To determine whether an inequality $a_j^Tx\le b_j$ in a given system of inequalities is redundant, one can solve the linear programming problem $\max\{a_j^Tx:x\in\mathcal D\}$ and compare it with $b_j$.

## Common Algorithms

In programming contests, there are few problems that can only be solved by linear programming algorithms. Most problems that can be solved by linear programming methods can also be solved more efficiently and specifically through algorithms like network flow.

Common algorithms for solving linear programming problems are as follows:

-   [Simplex Method](./simplex.md)
-   Ellipsoid Method
-   Interior Point Method

Although the worst-case complexity of the simplex method is exponential, while that of the interior point method is polynomial, both types of algorithms perform very well in most practical problems. In contrast, although the theoretical complexity of the ellipsoid method is polynomial, it is usually slow in practice and not useful.

It is currently unknown whether there exists a strongly polynomial-time algorithm for linear programming problems.

## Dual Problems

Every linear programming problem has a corresponding dual problem. The solutions of the primal and dual problems are closely related. Through the dual problem, not only can we gain a deeper understanding of the problem's structure, but we can also often improve the efficiency of solving the original problem.

For the linear programming problem $P$ (all lowercase letter variables in the following are vectors)

$$
\begin{aligned}
\min_{x_1,x_2,x_3}\;& c_1^Tx_1 + c_2^Tx_2 + c_3^Tx_3 \\
\text{subject to }& A_{11}x_1 + A_{12}x_2 + A_{13}x_3 \ge b_1,\\
& A_{21}x_1 + A_{22}x_2 + A_{23}x_3 = b_2,\\
& A_{31}x_1 + A_{32}x_2 + A_{33}x_3 \le b_3,\\
& x_1\ge 0,~ x_3\le 0,
\end{aligned}
$$

its dual problem $D$ is the linear programming problem

$$
\begin{aligned}
\max_{y_1,y_2,y_3}\;&b_1^Ty_1+b_2^Ty_2+b_3^Ty_3 \\
\text{subject to }&A_{11}^Ty_1 + A_{21}^Ty_2 + A_{31}^Ty_3\le c_1,\\
&A_{12}^Ty_1 + A_{22}^Ty_2 + A_{32}^Ty_3 = c_2,\\
&A_{13}^Ty_1 + A_{23}^Ty_2 + A_{33}^Ty_3 \ge c_3,\\
&y_1\ge 0,~ y_3\le 0.
\end{aligned}
$$

Here, the dual variables $y_1,y_2,y_3$ are the Lagrange multipliers of the three types of constraints in the original problem; conversely, the decision variables $x_1,x_2,x_3$ of the original problem are also the Lagrange multipliers of the three types of constraints in the dual problem. It is easy to verify that the dual of the dual problem is the original problem.

The correspondence between the primal problem $P$ and the dual problem $D$ is as follows:

|  Minimization Problem |  Maximization Problem |
| :----: | :----: |
| Greater-than-or-equal-to constraint | Non-negative variable |
| Less-than-or-equal-to constraint | Non-positive variable |
|  Equality constraint  | Unrestricted variable |
|  Non-negative variable | Less-than-or-equal-to constraint |
|  Non-positive variable | Greater-than-or-equal-to constraint |
|  Unrestricted variable | Equality constraint  |
| Objective function coefficients | Right-hand side constants |
| Right-hand side constants | Objective function coefficients |

In particular, the dual problem of the linear programming problem in standard form

$$
\min\{c^Tx:Ax=b,~x\ge 0\}
$$

is

$$
\max\{b^Ty:A^Ty\le c\}.
$$

### Duality Principle

The primal and dual problems are not only mirror images of each other in form, but their solutions are also closely related. This is called the **duality principle** (duality principal). For the sake of clarity in stating and proving theorems, this section will use the standard form of the primal problem.

First, the **weak duality theorem** (weak duality theorem) states that the maximum value of the dual problem does not exceed the minimum value of the primal problem.

???+ note "Weak Duality Theorem"
    For all $A\in\mathbf R^{m\times n}$, $b\in\mathbf R^m$ and $c\in\mathbf R^n$, we always have
    
    $$
    \max\{b^Ty:A^Ty\le c\} \le \min\{c^Tx:Ax=b,~x\ge 0\}.
    $$

??? note "Proof"
    If either the primal or dual problem is infeasible, then this inequality is trivial. Suppose both problems are feasible. Then, for all feasible $x$ and $y$, we have
    
    $$
    b^Ty = x^TA^Ty \le x^Tc.
    $$
    
    Therefore, by taking the maximum on both sides, the weak duality theorem holds.

Based on the weak duality theorem, there are only four possible cases for the solutions of the primal and dual problems:

1.  Both the primal and dual problems are infeasible, i.e., $-\infty\le+\infty$;
2.  The primal problem is infeasible and the dual problem is unbounded, i.e., $+\infty\le+\infty$;
3.  The primal problem is unbounded and the dual problem is infeasible, i.e., $-\infty\le-\infty$;
4.  Both the primal and dual problems are bounded.

There are many corollaries of the weak duality theorem. For example, it actually provides a method to determine that the primal problem is unbounded by using the feasibility of the primal and dual problems.

???+ note "Corollary"
    A linear programming problem is unbounded if and only if it is feasible and its dual problem is infeasible.

Applying the weak duality theorem to feasibility linear programming problems yields Farkas' lemma (and its various variants).

???+ note "Farkas' Lemma"
    For $A\in\mathbf R^{m\times n}$ and $b\in\mathbf R^n$, exactly one of the following holds:
    
    1.  There exists $x\in\mathbf R^n$ such that $Ax=b$ and $x\ge 0$;
    2.  There exists $y\in\mathbf R^m$ such that $A^T y\ge 0$ and $b^Ty<0$.

??? note "Proof"
    Consider the linear programming problem $\max\{0:Ax=b,~x\ge 0\}$, whose dual problem is $\min\{b^Ty:A^Ty\ge 0\}$. The dual problem is clearly feasible because at least $0\in\mathbf R^m$ is a feasible solution. Therefore, according to the weak duality theorem, either the primal problem is feasible or the dual problem is unbounded, one must hold. The primal problem being feasible corresponds to case 1 in Farkas' lemma, and the dual problem being unbounded corresponds to case 2. This proves Farkas' lemma.

Farkas' lemma is actually a [hyperplane separation theorem](https://en.wikipedia.org/wiki/Hyperplane_separation_theorem). Case 1 states that point $b$ lies in the polyhedral cone $C$ generated by the column vectors of $A$. Therefore, Farkas' lemma states that point $b$ lies in this convex cone $C$ if and only if there exists a hyperplane $H:y^Tx = 0$ passing through the origin with normal vector $y$ that strongly separates point $b$ and the polyhedral cone $C$.

In fact, for the fourth case allowed by the weak duality theorem, a stronger conclusion holds: the optimal values of the primal and dual problems are equal. Combining the latter three cases yields the **strong duality theorem** (strong duality theorem): as long as either the primal or dual problem is feasible, their optimal values are necessarily equal.

???+ note "Strong Duality Theorem"
    For all $A\in\mathbf R^{m\times n}$, $b\in\mathbf R^m$ and $c\in\mathbf R^n$, we have
    
    $$
    \max\{b^Ty:A^Ty\le c\} = \min\{c^Tx:Ax=b,~x\ge 0\}.
    $$
    
    As long as one of the two sets is non-empty.

??? note "Proof"
    The only case not covered by the weak duality theorem is when both the primal and dual problems are feasible. In this case, consider the following feasibility linear programming problem $Q$:
    
    $$
    \max\{0:c^Tx \le b^Ty,~Ax=b,~x\ge 0,~A^Ty\le c\}.
    $$
    
    If problem $Q$ has a feasible solution $(x^*,y^*)\in\mathbf R^n\times\mathbf R^m$, then, by the weak duality theorem and optimality, we have
    
    $$
    b^Ty^* \le \max\{b^Ty:A^Ty\le c\} \le \min\{c^Tx:Ax=b,~x\ge 0\} \le c^Tx^*,
    $$
    
    but since $c^Tx^*\le b^Ty^*$, all these inequalities can attain equality. That is, not only does strong duality hold, but $x^*$ and $y^*$ are also optimal solutions to the primal and dual problems, respectively.
    
    Therefore, we only need to prove that problem $Q$ is feasible. Suppose not. Following the proof of Farkas' lemma, consider the dual problem $DQ$ of problem $Q$:
    
    $$
    \min\{c^T\mu - b^T\lambda : ct - A^T\lambda \ge 0,~ -bt + A\mu = 0,~t\ge 0,~\mu\ge 0\}.
    $$
    
    Because $(t,\lambda,\mu)=(0,0,0)$ is a feasible solution to the dual problem $DQ$, by the weak duality theorem, if problem $Q$ is infeasible, then the dual problem $DQ$ is unbounded, i.e., there exists $(t^*,\lambda^*,\mu^*)$ such that
    
    $$
    c^T\mu^* - b^T\lambda^* <0,~ ct^* - A^T\lambda^* \ge 0,~ -bt^* + A\mu^* = 0,~t^*\ge 0,~\mu^*\ge 0.
    $$
    
    In this case, if $t^*>0$, then these inequalities actually show that $(x,y)=(\mu^*/t^*,\lambda^*/t^*)$ is a feasible solution to the aforementioned problem, contradicting the assumption. So we must have $t^*=0$. This shows that
    
    $$
    c^T\mu^* < b^T\lambda^*,~ A^T\lambda^*\le 0,~ A\mu^*=0,~\mu^*\ge 0.
    $$
    
    However, since we have already assumed that the primal and dual problems in the theorem are both feasible, i.e., there exists $(x_0,y_0)$ such that
    
    $$
    Ax_0 = b,~ x_0\ge 0,~ A^Ty_0\le c
    $$
    
    holds, we have
    
    $$
    0 = (A\mu^*)^Ty_0 = (A^Ty_0)^T\mu^* \le c^T\mu^* < b^T\lambda^* = x_0^TA^T\lambda^* \le 0.
    $$
    
    This is clearly contradictory. This contradiction shows that problem $Q$ is feasible, which in turn shows that strong duality holds.

The following corollary can also be obtained from the proof process of the strong duality theorem:

???+ note "Corollary"
    Let $x^*$ and $y^*$ be feasible solutions to the primal and dual problems, respectively, satisfying strong duality, i.e., $c^Tx^* = b^Ty^*$. Then they are also optimal solutions to the primal and dual problems, respectively.

The strong duality theorem shows that for feasible linear programming problems, one only needs to solve its dual problem to obtain the optimal value of the original problem.

### Complementary Slackness Conditions

Like other optimization problems, complementary slackness conditions are part of the optimality conditions for linear programming problems. Moreover, because the objective function is linear, for linear programming problems, complementary slackness conditions are necessary and sufficient conditions for a feasible solution to be optimal.

The so-called **complementary slackness** (complementary slackness) condition means that only when a constraint in the original (dual) problem attains equality (i.e., the constraint is tight) can the corresponding variable in the dual (original) problem take a non-zero value. If taking a non-zero value for a variable is also considered a slack constraint, then this is equivalent to saying that the corresponding variables and constraints in the primal and dual problems cannot both be slack. Therefore, this condition is called the complementary slackness condition.

For linear programming problems in standard form, the following conclusion holds:

???+ note "Theorem"
    Suppose $x^*$ and $y^*$ are feasible solutions to the primal problem $\min\{c^Tx:Ax=b,~x\ge 0\}$ and the dual problem $\max\{b^Ty:A^Ty\le c\}$, respectively. Then, if and only if the complementary slackness condition holds, i.e.,
    
    $$
    x^T(A^Ty-c) = 0
    $$
    
    $x^*$ and $y^*$ are also optimal solutions to the primal and dual problems, respectively.

??? note "Proof"
    Because $x^*$ and $y^*$ are both feasible solutions, we have
    
    $$
    b^Ty^* - c^Tx^* = (x^*)^T(A^T y^* - c).
    $$
    
    Therefore, the complementary slackness condition holds if and only if $b^Ty^* = c^Tx^*$. According to the corollary of the strong duality theorem, this condition holds if and only if $x^*$ and $y^*$ are optimal solutions to the primal problem, respectively.

The standard form may be too special. A slightly more general form of this theorem is as follows:

???+ note "Theorem"
    Suppose $x^*$ and $y^*$ are feasible solutions to the primal problem $\min\{c^Tx:Ax\ge b,~x\ge 0\}$ and the dual problem $\max\{b^Ty:A^Ty\le c,~y\ge 0\}$, respectively. Then, if and only if the complementary slackness condition holds, i.e.,
    
    $$
    x^T(A^Ty-c) = y^T(Ax-b) = 0
    $$
    
    $x^*$ and $y^*$ are also optimal solutions to the primal and dual problems, respectively.

??? note "Proof"
    The proof is essentially the same as above, except this time the difference is written as
    
    $$
    b^Ty^* - c^Tx^* = (x^*)^T(A^T y^* - c) - (y^*)^T(Ax^*-b).
    $$

The complementary slackness conditions provide simple criteria for checking the optimality of feasible solutions to linear programming problems.

### Primal-Dual Method

The dual problem can assist in solving the primal problem. A commonly used method in solving linear programming problems is the **primal-dual method** (primal-dual method). It obtains the optimal solution to the original problem by solving a series of relatively simple auxiliary problems and progressively improving the solution to the dual problem.

For the primal problem in standard form

$$
(P)\qquad\min\{c^Tx : Ax=b\ge 0,~ x\ge 0\}
$$

and its dual problem

$$
(D)\qquad\max\{b^Ty : A^Ty\le c\},
$$

the previous section has shown that to find their optimal solutions, we only need to find a pair of feasible solutions to problems $(P)$ and $(D)$ that satisfy the complementary slackness condition $x^T(A^Ty-c)=0$. Therefore, consider the following process:

1.  Starting from a feasible solution $y$ to the dual problem $(D)$, compute the set of tight constraints of the dual problem

    $$
    I = \{i : (A^Ty - c)_i = 0\}.
    $$

2.  According to the complementary slackness condition, if there exists a feasible solution $x$ to problem $(P)$ such that $x_i>0$ only holds for $i\in I$, it means we have already found a pair of optimal solutions. Therefore, consider the linear programming problem

    $$
    (RP)\qquad
    \begin{aligned}
    \min_{x,s}\;& \mathbf 1^Ts \\
    \text{subject to } & Ax + s = b, \\
    & x_i \ge 0,~\forall i \in I,\\
    & x_i = 0,~\forall i \notin I,\\
    & s \ge 0.
    \end{aligned}
    $$

3.  If the minimum value of problem $(RP)$ is $0$, then the $x^*$ in the optimal solution $(x^*,0)$ is the optimal solution to the original problem $(P)$. Otherwise, we can find the solution $\bar y$ to its dual problem $(DRP)$:

    $$
    (DRP)\qquad
    \begin{aligned}
    \max_{y}\;& b^Ty \\
    \text{subject to }& \sum_{j}a_{ji}y_j \le 0,~\forall i\in I,\\
    & y \le 1.
    \end{aligned}
    $$

    According to the strong duality theorem, we have $b^T\bar y = 1^Ts^*>0$.

4.  Use the solution to problem $(DRP)$ to improve the feasible solution to the dual problem $(D)$. Let $y' = y + \varepsilon \bar y$, where $\varepsilon>0$. Then we must have $b^Ty' = b^Ty + \varepsilon b^T\bar y > b^Ty$. Therefore, as long as $y'$ remains a feasible solution to the dual problem $(D)$, we should choose the largest possible value of $\varepsilon$.

    For $i\in I$, we have

    $$
    \sum_ja_{ji}y'_j = \sum_ja_{ji}y_j + \varepsilon \sum_ja_{ji}\bar y_j \le c_i,
    $$

    so these constraints of problem $(D)$ can always be satisfied.

    For the remaining constraints, i.e., when $i\notin I$, we only need to take

    $$
    \varepsilon = \min\left\{\dfrac{c_i - \sum_{j}a_{ji}y_j}{\sum_{j}a_{ji}\bar y_j}:i\notin I,~\textstyle\sum_{j}a_{ji}\bar y_j>0\right\}
    $$

    to improve the solution to the dual problem as much as possible while ensuring feasibility, and then return to step 1 to continue iterating. In particular, if the set in the above formula is empty, i.e., $\varepsilon=+\infty$, then the dual problem $(D)$ is unbounded and the primal problem $(P)$ is infeasible.

In this process, only problem $(DRP)$ actually needs to be solved, and it is related to problem $(RP)$ through the strong duality theorem. Problem $(DRP)$ provides a direction to improve the solution to the dual problem, and compared to the dual problem $(D)$ itself, the form of problem $(DRP)$ is simpler. The feasibility of problem $(DRP)$ is guaranteed by Farkas' lemma, and the constraint $y\le 1$ is just a set of normalization conditions that ensure problem $(DRP)$ is bounded.

In programming contests, the primal-dual method is widely applied to various combinatorial optimization problems. For example, the [Hungarian algorithm](../graph/graph-matching/bigraph-weight-match.md#hungarian-algorithmkuhnmunkres-algorithm) for maximum weight matching in bipartite graphs, the [cycle-canceling algorithm](../graph/flow/min-cost.md) and [SSP algorithm (primal-dual algorithm)](../graph/flow/min-cost.md#ssp-algorithm) for minimum cost flow, Dijkstra's algorithm for shortest path, and the Ford-Fulkerson augmentation algorithm for maximum flow can all be viewed as direct applications of the primal-dual method.

## Integer Programming

**Integer programming** (integer programming) usually refers to **integer linear programming** (ILP). The standard form of integer linear programming is as follows:

$$
\begin{aligned}
\min_{x}\; & c^Tx \\
\text{subject to } & Ax = b \ge 0,\\
& x \ge 0,\\
& x \in \mathbf Z^n,
\end{aligned}
$$

where $A\in\mathbf R^{m\times n}$, $b\in\mathbf R^m$, $c\in\mathbf R^n$. That is, integer linear programming is obtained by adding the constraint that decision variables must be integers to the linear programming problem.

Integer constraints significantly increase the complexity of integer programming problems. Many combinatorial optimization problems, such as the knapsack problem, satisfiability problems, and many optimization problems in graph theory, can be expressed as integer programming models, and most of these problems have been proven to be NP-hard.

### Totally Unimodular Matrices

For this reason, for many large-scale integer optimization problems, sometimes we consider relaxing the integer constraints and instead solving a linear programming problem. Generally, the optimal value of the relaxed linear programming problem is only a lower bound estimate for the original integer programming problem (assuming the problem is a minimization problem). However, if the optimal solution of the relaxed linear programming problem happens to be an integer solution, then it is also the optimal solution to the original integer programming problem.

A natural question is whether there exists a condition that can guarantee that all optimal solutions to a linear programming problem are integer solutions. The concept of totally unimodular matrices provides such a condition.

???+ abstract "Totally Unimodular Matrix"
    If all subdeterminants of a matrix $A\in\mathbf R^{m\times n}$ are $0$ or $\pm 1$, then $A$ is called a **totally unimodular matrix** (totally unimodular matrix).

In particular, all elements of a totally unimodular matrix are $0$ or $\pm 1$. Using the concept of totally unimodular matrices, we can state the following conclusion:

???+ note "Theorem"
    For a totally unimodular matrix $A\in\mathbf Z^{m\times n}$, $b\in\mathbf Z^{m}$ and $c\in\mathbf Z^n$, the linear programming problem and its dual problem
    
    $$
    \min\{c^Tx : Ax=b,x\ge 0\} = \max\{b^Ty: A^Ty\le c\}
    $$
    
    both have integer optimal solutions, as long as they are bounded.

??? note "Proof"
    As previously shown, the optimal solution set of a linear programming problem can be taken as one of its minimal faces, which is the solution to a system of equations obtained by taking several linearly independent tight constraints as equalities:
    
    $$
    \{x\in\mathbf R^n : a_j^Tx = b_j,~\forall j\in J\}.
    $$
    
    Denote this system of equations as $A_Jx=b_J$, and let $A_J=(A_1,A_2)$, where $A_1$ is a full-rank square matrix with determinant $\pm 1$. Then, by Cramer's rule, the solution
    
    $$
    x = \begin{pmatrix}A_1^{-1}b_J \\ 0\end{pmatrix}
    $$
    
    is an integer solution on the minimal face.

In common graph theory models, the coefficient matrices of linear programming problems corresponding to network flow, shortest path, bipartite graphs, etc., are all totally unimodular matrices. Therefore, as long as these problems only involve integer parameters, their optimal solutions can be taken as integers, without worrying about the linear programming solution corresponding to fractional flow, fractional matching, etc. Therefore, problems such as [maximum flow](../graph/flow/max-flow.md), [minimum cut](../graph/flow/min-cut.md), [minimum cost flow](../graph/flow/min-cost.md), [shortest path](../graph/shortest-path.md), [difference constraints](../graph/diff-constraints.md), and [maximum (weighted) matching and minimum vertex cover in bipartite graphs](../graph/graph-matching/bigraph-match.md#linear-programming-form) can all be transformed into linear programming problems to solve. Moreover, maximum flow and minimum cut, shortest path and difference constraints, and maximum matching and minimum vertex cover in bipartite graphs are pairwise dual problems.

Additionally, there are some common graph theory models where all feasible solutions happen to be exactly all vertices of a polytope with integer vertices. Therefore, by cleverly selecting constraints, the solution to the corresponding combinatorial optimization problem can be exactly the optimal solution to some linear programming problem. For example, general graph matching and spanning tree models belong to this category, so problems like [general graph maximum (weighted) matching](../graph/graph-matching/general-weight-match.md) and [minimum spanning tree](../graph/mst.md) can also be transformed into linear programming problems.

## References and Notes

-   Schrijver, Alexander. Theory of linear and integer programming. John Wiley & Sons, 1998.
-   Papadimitriou, Christos H., and Kenneth Steiglitz. Combinatorial optimization: algorithms and complexity. Courier Corporation, 1998.
-   [Duality in linear programming. Part 1—definition and construction. by adamant - Codeforces blog](https://codeforces.com/blog/entry/105049)
-   [Duality in linear programming. Part 2—in competitive programming. by adamant - Codeforces blog](https://codeforces.com/blog/entry/105789)

[^poly-names]: Different literature may have different definitions for these two terms: some literature calls the bounded case "polyhedron" and the unbounded case "polytope"; some literature does not assume they are necessarily convex sets; some literature uses "polyhedron" to refer to polytopes in three-dimensional space. This article adopts the definition consistent with Schrijver (1998) and Boyd and Vandenberghe (2004).

[^reducible]: More precisely, they can be reduced to each other in polynomial time.

[^other-methods]: Other methods for solving systems of inequalities include the Fourier-Motzkin elimination method and the Agmon-Motzkin-Schoenberg relaxation method. They are more direct but often inefficient.
