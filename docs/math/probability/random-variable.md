## Related Concepts

### Random Variable

Given a probability space $(\Omega, \mathcal{F}, P)$, a function $X : \Omega \to \mathbb{R}$ defined on the sample space $\Omega$ is called a **random variable** if for any $t \in \mathbb{R}$,

$$
\{ \omega \in \Omega : X(\omega) \le t \} \in \mathcal{F}
$$

### Indicator Function

For an event $A$ on the sample space $\Omega$, define the random variable

$$
I_A(\omega) = \begin{cases}
    1, & \omega \in A \\
    0, & \omega \notin A
\end{cases}
$$

$I_A$ is called the **indicator function** of event $A$.

### Distribution Function

For a random variable $X$, the function

$$
F(x) = P( X \leq x )
$$

is called the **distribution function** of $X$. Denoted $X \sim F(x)$.

Distribution functions have the following properties:

-   **Right continuity**: $F(x) = F(x + 0)$
-   **Monotonicity**: monotonically non-decreasing on $\mathbb{R}$
-   $F(-\infty) = 0$, $F(+\infty) = 1$

At the same time, we can prove that any function satisfying the above requirements is the distribution function of some random variable. Therefore, there is a one-to-one correspondence between distribution functions and random variables.

## Classification of Random Variables

Random variables are classified into two types based on whether their range (according to the definition, a random variable is a function) is countable: **discrete** and **continuous**.

### Discrete Random Variable

Let $X$ be a discrete random variable with all possible values $x_1, x_2, \cdots$. Then we can describe $X$ using a series of equations of the form $P\{ X = x_i \} = p_i$. This is what we learned in high school textbooks as the **probability distribution table**.

### Continuous Random Variable

Let $X$ be a continuous random variable. Examining $P\{ X = x \}$ is often meaningless (because this probability is likely $0$).

??? note "Why is the probability 'likely' 0"
    Consider such a random variable $X$: it takes value $0$ with probability $\frac{1}{2}$, and follows a uniform distribution on the open interval $(0, 1)$ with probability $\frac{1}{2}$. Clearly, $X$ satisfies the definition of a continuous random variable.
    
    For any real number $r \in (0, 1)$, it is easy to obtain $P\{ X = r \} = 0$, but at the same time $P\{ X = 0 \} = \frac{1}{2}$.

On the other hand, let $X \sim F(x)$, then

$$
P( l < x \leq l + \Delta x ) = F(l + \Delta x) - F(l)
$$

A natural idea is to use the limit $\lim\limits_{\Delta x \to 0^+} \frac{F(l + \Delta x) - F(l)}{\Delta x}$ to describe the likelihood of $X$ taking the value $l$.

This expression is the familiar derivative. So the problem becomes finding a non-negative function $f(x)$ such that

$$
F(x) = \int_{-\infty}^{x} f(x) \text{d} x
$$

If such an $f(x)$ exists, it is called the **density function** of $X$.

## Independence of Random Variables

We previously discussed the independence of random events. Since random variables are closely related to random events, we can similarly give the definition of independence of random variables.

### Definition

If random variables $X, Y$ satisfy for any $x, y \in \mathbb{R}$,

$$
P( X \leq x, Y \leq y ) = P( X \leq x ) P( Y \leq y )
$$

then random variables $X, Y$ are said to be **independent**.

??? note "Note"
    Some students may notice that the definition of independence of random variables in high school textbooks uses probabilities of the form $P(X = \alpha)$. However, since continuous random variables typically have probability $0$ of taking specific values, using the distribution function for a more general definition is a wiser choice.

### Properties

If random variables $X, Y$ are independent, then for any functions $f, g$, random variables $f(X)$ and $g(Y)$ are independent.

??? warning "Caution"
    Sometimes we study the distribution of some function $f(X, Y)$ of independent random variables $X, Y$ (such as $XY^2$).
    
    Although $X$ and $Y$ are independent, we cannot assume that for a particular value $y$ of $Y$, $f(X, y)$ and $f(X, Y)$ follow the same distribution.