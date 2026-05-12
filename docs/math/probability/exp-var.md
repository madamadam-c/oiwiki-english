This article introduces the expectation, variance, and other numerical characteristics of random variables.

## Expectation

### Definition

#### Discrete Random Variable

Let $X$ be a discrete random variable with probability distribution $p_i = P\{ X = x_i \}$. If the sum

$$
\sum x_i p_i
$$

converges absolutely, its value is called the **expectation** of $X$, denoted $EX$.

#### Continuous Random Variable

Let $X$ be a continuous random variable with density function $f(x)$. If the integral

$$
\int_{\mathbb{R}} xf(x) \text{d} x
$$

converges absolutely, its value is called the **expectation** of $X$, denoted $EX$.

#### Unified Definition

Let $X$ be a random variable with distribution function $F(x)$. If the [Stieltjes integral](https://en.wikipedia.org/wiki/Riemann%E2%80%93Stieltjes_integral)

$$
\int_{\mathbb{R}} x \text{d} F(x)
$$

converges absolutely, its value is called the **expectation** of $X$, denoted $EX$.

??? example "Example of Non-existent Expectation"
    Consider a discrete random variable $X$ with the following distribution
    
    $$
    P\left\{ X = (-1)^k \frac{2^k}{k} \right\} = \frac{1}{2^k}, \quad k = 1, 2, \cdots
    $$
    
    Although the sum $\sum x_i p_i$ converges to $- \ln 2$, since it does not converge absolutely, the expectation of $X$ does not exist.
    
    Consider a continuous random variable $Y$ with the following density function
    
    $$
    f(y) = \frac{1}{\pi} \cdot \frac{1}{1 + y^2}, \quad y \in (-\infty, +\infty)
    $$
    
    It is easy to verify that the expectation of $Y$ also does not exist.

### Properties of Expectation

#### Linearity

If random variables $X, Y$ have existing expectations, then

-   For any real numbers $a, b$, $E(aX + b) = a \cdot EX + b$.
-   $E(X + Y) = EX + EY$.

#### Expectation of Product of Random Variables

If random variables $X, Y$ have existing expectations and $X, Y$ are independent, then

$$
E(XY) = EX \cdot EY
$$

Note: The independence in the above property is **not** a necessary condition.

??? example "Counterexample"
    Consider random variables $X$ and $Y$, where $X$ follows a uniform distribution on $[-1, 1]$, and $Y = X^2$.

### Converting Expectation and Probability

For a random event $A$, consider its indicator function $I_A$:

$$
I_A(\omega) = \begin{cases}
    1, & \omega \in A \\
    0, & \omega \notin A
\end{cases}
$$

According to the definition, its expectation is $EI_A = P(A)$. This conversion is very common in practical applications.

??? example "Example"
    Suppose for a sequence $\{ a_i \}$ of length $n$, $a_k$ takes value $k$ with probability $p_k$, and takes value $0$ with probability $1 - p_k$. Consider how to find the expectation of $S = \sum_{i=1}^{n} a_i$.
    
    If we use the definition directly, we need to find the probability of $S$ at each possible value; this calculation process is quite tedious, so we will not elaborate.
    
    On the other hand, let $I_k$ be the indicator function of the random event $a_k = k$. Then
    
    $$
    S = \sum_{k=1}^{n} k \cdot I_k
    $$
    
    It follows that
    
    $$
    ES = E \left( \sum_{k=1}^{n} k \cdot I_k \right) = \sum_{k=1}^{n} k \cdot E[I_k] = \sum_{k=1}^{n} k \cdot p_k
    $$

## Conditional Distribution and Conditional Expectation

We have previously studied conditional probability; similarly, we can introduce the concept of conditional expectation.

### Definition

For two random variables $X, Y$, the probability distribution (density function) of $X$ given $Y = y$ is called the **conditional probability distribution (conditional probability density)**, denoted respectively as

$$
P( X = x_i | Y = y ) \qquad f_{X|Y}(x|y)
$$

Under this condition, the expectation of $X$ is called the **conditional expectation**, denoted $E[X|Y=y]$.

### Properties of Conditional Expectation

Many properties of conditional expectation can be derived from conditional probability, so they will not be elaborated here.

It is worth mentioning that $E[X | Y]$ is generally a function of the random variable $Y$, and this function is usually not linear. But in fact,

$$
E[E[X|Y]] = EX
$$

This is called the **law of total expectation**.

### Application

???+ example "[HDU 5984 Pocky](https://acm.hdu.edu.cn/showproblem.php?pid=5984)"
    There is a Pocky stick of length $L$. Each time it is randomly broken into two pieces. If the length of the right piece is not greater than $d$, stop; otherwise, repeat the above process on the right piece. Find the expected number of repetitions.

??? note "Solution"
    Let $f(x)$ denote the expected number of repetitions for a stick of length $x$. The case $x \leq d$ is trivial.
    
    When $x > d$, suppose the break point is at a distance $k$ from the right end. Then $k \sim U[0, x]$. The expected number of repetitions is
    
    $$
    g(k) = \begin{cases}
        1, & k \leq d \\
        1 + f(k), & k > d
    \end{cases}
    $$
    
    By the law of total expectation,
    
    $$
    f(x) = Eg(k) = 1 + \frac{1}{x} \cdot \int_{d}^{x} f(t) \text{d} t
    $$
    
    Solving this integral equation and substituting the initial condition gives
    
    $$
    f(x) = 1 + \ln \frac{x}{d}
    $$

## Variance

### Definition

Let the expectation $EX$ of random variable $X$ exist, and let the expectation

$$
E(X - EX)^2
$$

also exist. Then the value of the above expression is called the **variance** of random variable $X$, denoted $DX$ or $Var(x)$. The arithmetic square root of variance is called the **standard deviation**, denoted $\sigma(X) = \sqrt{DX}$.

### Properties of Variance

If the variance of random variable $X$ exists, then

-   For any constants $a, b$, $D(aX + b) = a^2 \cdot DX$
-   $DX = E(X^2) - (EX)^2$

## Covariance and Correlation Coefficient

In general, the equation $D(X + Y) = DX + DY$ does not hold. We naturally ask two questions:

-   What exactly is the difference between $D(X + Y)$ and $DX + DY$?
-   Under what circumstances are $D(X + Y)$ and $DX + DY$ equal?

For the first question, we introduce covariance as the answer.

### Definition of Covariance

For random variables $X, Y$, the quantity

$$
E((X - EX)(Y - EY))
$$

is called the **covariance** of $X$ and $Y$, denoted $\operatorname{Cov}(X, Y)$.

### Properties of Covariance

For random variables $X, Y, Z$:

-   $\operatorname{Cov}(X, Y) = \operatorname{Cov}(Y, X)$
-   For any constants $a, b$, $\operatorname{Cov}(aX + bY, Z) = a \cdot \operatorname{Cov}(X, Z) + b \cdot \operatorname{Cov}(Y, Z)$

Additionally, covariance and variance have the following relationship:

-   $DX = \operatorname{Cov}(X, X)$
-   $D(X + Y) = DX + 2 \operatorname{Cov}(X, Y) + DY$

??? note "About Covariance"
    You may notice that the properties of covariance are highly consistent in form with the operational properties of vector inner products.
    
    From the perspective of functional analysis, for a given probability space, all random variables on it form a linear space, and covariance is an inner product on this space. Standard deviation is the norm induced by this inner product.

For the second question raised earlier, it is easy to see that $D(X + Y) = DX + DY$ if and only if $\operatorname{Cov}(X, Y) = 0$. An intuitive sufficient condition is that $X$ and $Y$ are independent, because in this case,

$$
\operatorname{Cov}(X, Y) = E((X - EX)(Y - EY)) = E(X - EX) E(Y - EY) = 0
$$

But this condition is not sufficient. To describe the relationship between random variables $X, Y$ satisfying $\operatorname{Cov}(X, Y) = 0$, we introduce the correlation coefficient.

### Correlation Coefficient

For random variables $X, Y$, the quantity

$$
\frac{ \operatorname{Cov}(X, Y)}{ \sigma(X)\sigma(Y) }
$$

is called the **Pearson correlation coefficient** of $X$ and $Y$, denoted $\rho_{X,Y}$.

The Pearson correlation coefficient describes the strength of linear association between two random variables. The larger $|\rho_{X,Y}|$, the stronger the linear association between $X$ and $Y$. It can be easily proven that $|\rho_{X,Y}| \leq 1$, and $|\rho_{X,Y}| = 1$ can only occur in the following two situations:

-   When there exists a real number $a$ and a positive real number $b$ such that $P(X = a + bY) = 1$, we have $\rho_{X,Y} = 1$;
-   When there exists a real number $a$ and a negative real number $b$ such that $P(X = a + bY) = 1$, we have $\rho_{X,Y} = -1$.

When $\rho_{X,Y} = 0$, we say random variables $X$ and $Y$ are **uncorrelated**, meaning there is no linear relationship between $X$ and $Y$.

??? note "Uncorrelated vs. Independent"
    Two random variables being uncorrelated only indicates that there is no linear association between them, not that there are no other forms of relationship.
    
    Therefore, for two random variables $X, Y$, being uncorrelated is a **necessary but not sufficient** condition for them to be independent.

For the second question raised at the beginning of this section, we give the conclusion: the necessary and sufficient condition for $\operatorname{Cov}(X, Y) = 0$ is that one of $X, Y$ takes a constant value with probability $1$, or $X, Y$ are uncorrelated.