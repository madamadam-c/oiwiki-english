In algorithm competitions, [randomized algorithms](../../misc/rand-technique.md) are sometimes used. The correctness and time/space complexity of these algorithms typically rely on the premise that "certain random events occur with very small probability." For example, the complexity of quicksort depends on the event that "the selected `pivot` element is almost the smallest or largest element" occurring rarely.

This article will briefly introduce some tools for analyzing randomized algorithms and provide several simple application examples.

## Union Bound

Let $A_1, \cdots, A_m$ be random events, then

$$
P\left\{ \bigcup_{i=1}^m A_i \right\} \leq \sum_{i=1}^m P\{A_i\}
$$

That is: the probability that at least one of a set of events occurs does not exceed the sum of the probabilities of each event occurring.

In fact, this conclusion can be slightly strengthened:

-   The probability that at least one of a set of events occurs is **at least** the sum of the probabilities of each event, minus the sum of the probabilities of each pair occurring simultaneously.
-   The probability that at least one of a set of events occurs is **at most** the sum of the probabilities of each event, minus the sum of the probabilities of each pair occurring simultaneously, plus the sum of the probabilities of each triple occurring simultaneously.
-   ……

As the number of layers increases, the alternating upper and lower bounds become tighter. This series of conclusions is formally similar to the inclusion-exclusion principle, and the proof process is similar to that of inclusion-exclusion, so it is omitted here.

## Markov's Inequality

Let $X$ be a non-negative random variable, then for any positive real number $a$,

$$
P\{ X \geq a \} \leq \frac{EX}{a}
$$

In fact, since Markov's inequality itself does not use any information about the distribution of the random variable beyond its expectation, the bound obtained by directly applying this inequality is usually quite loose.

### Proof

Let $I$ be the indicator function of the event $X \geq a$, then

$$
I \leq \frac{X}{a}
$$

Consequently,

$$
P\{ X \geq a \} = EI \leq E \left[ \frac{X}{a} \right] = \frac{EX}{a}
$$

## Chebyshev's Inequality

Let $X$ be a random variable, then for any $a > 0$,

$$
P \{ |X - EX| \geq a \} \leq \frac{DX}{a^2}
$$

In particular, when $a$ takes the value $k\sigma$,

$$
P \{ |X - EX| \geq k\sigma \} \leq \frac{1}{k^2}
$$

where $\sigma$ is the standard deviation of $X$.

### Proof

From the given, we have

$$
P \{ |X - EX| \geq a \} = P \{ (X - EX)^2 \geq a^2 \}
$$

Noting that $(X - EX)^2$ is non-negative, by Markov's inequality,

$$
P \{ (X - EX)^2 \geq a^2 \} \leq \frac{E(X - EX)^2}{a^2} = \frac{DX}{a^2}
$$

## Chernoff Bound

A general Chernoff bound can be derived by directly applying Markov's inequality to the random variable $\mathrm{e}^{tX}$:

Let $X$ be a random variable, then for any $t > 0$,

$$
P\{ X \geq a \} = P\{ \mathrm{e}^{tX} > \mathrm{e}^{ta} \} \leq \frac{E \mathrm{e}^{tX}}{\mathrm{e}^{ta}}
$$

Similarly, when $t < 0$,

$$
P\{ X \leq a \} = P\{ \mathrm{e}^{tX} > \mathrm{e}^{ta} \} \leq \frac{E \mathrm{e}^{tX}}{\mathrm{e}^{ta}}
$$

### Chernoff Bound for Sum of Poisson Trials

The random variables involved in algorithm competitions are usually not so "general." We can describe them using Poisson trials in probability theory.

A Poisson trial refers to a random experiment with only two possible outcomes.

The outcome of a single Poisson trial can be described by a random variable $X$ taking values $0$ or $1$, with probability distribution

$$
P\{ X = i \} = \begin{cases}
    p_i, & i = 1 \\
    1 - p_1, & i = 0
\end{cases}
$$

For Poisson trials, we have the following conclusion:

For $n$ independent Poisson trials $X_1, X_2, \cdots, X_n$, let $X = \sum_{i=1}^{n} X_i$ and $\mu = EX$, then for any $0 < \epsilon < 1$,

$$
P\left\{ |X - \mu| \geq \epsilon \mu \right\} \leq 2 \exp\left( - \frac{1}{3} \mu \epsilon^2 \right)
$$

## Hoeffding's Inequality

If $X_1, \cdots, X_n$ are independent real random variables and $X_i \in [a_i, b_i]$, and the random variable $X = \sum\limits_{i=1}^n X_i$, then

$$
P\{ |X - EX| \geq \epsilon \} \leq 2\exp \left( \frac {-2\epsilon^2}{\sum\limits_{i=1}^n (b_i-a_i)^2} \right)
$$

Both Chernoff bounds and Hoeffding's inequality bound the degree to which a random variable deviates from its expected value. The proofs of these two inequalities are relatively lengthy; interested readers may refer to the relevant chapters in the book "Probability and Computing."

Empirically, if $EX$ is not too close to $a_1 + \cdots + a_n$, the bound given by this inequality is usually relatively tight; if it is very close (for example, in [UOJ #72 New Approach](https://matthew99.blog.uoj.ac/blog/5511)), the bound is usually quite loose. In such cases, using Chernoff bounds is a better choice.

## Application Examples

### Example: Estimating Pi by Random Points

Consider the following algorithm to estimate the exact value of $\pi$:

Generate $n$ random points in the square region $[-1, 1]^2$. Let $m$ be the number of points falling inside the unit disk $x^2 + y^2 \leq 1$. Then $\dfrac{4m}{n}$ can be taken as an approximation of $\pi$.

Question: If we want to ensure that the above algorithm returns a result with relative error no more than $\epsilon$ with probability at least $(1 - \delta)$, how should $n$ be chosen?

??? note "Solution"
    Let $X_i$ denote the event "the i-th randomly generated point is inside the unit disk." Then the total number of points inside the disk $X = \sum_{i=1}^{n} X_i$. We need to find an appropriate $n$ such that
    
    $$
    P\left\{ \left| \frac{4X}{n} - \pi \right| \geq \epsilon \pi \right\} \leq \delta
    $$
    
    The above is equivalent to
    
    $$
    P\left\{ \left| X - \frac{\pi}{4}n \right| \geq \epsilon \cdot \frac{\pi}{4}n  \right\} \leq \delta
    $$
    
    According to Chernoff bounds, we just need to set
    
    $$
    2 \exp\left( - \frac{1}{3} \epsilon^2 \cdot \frac{\pi}{4}n \right) \leq \delta
    $$
    
    From this, we can solve for
    
    $$
    n \geq \frac{12}{\pi} \epsilon^{-2} \ln \frac{2}{\delta}
    $$
    
    That is, when $n = \Omega(\epsilon^{-2} \ln \frac{1}{\delta})$, the required accuracy can be achieved.

### Example: Prize Drawing Problem

A box contains $n$ balls, of which exactly $k$ balls correspond to grand prizes. You will perform several independent, equally probable random draws, with each ball being returned to the box after drawing. How many times must you draw to ensure with probability at least $(1 - \epsilon)$ that **every** prize ball has been drawn at least once?

??? note "Solution"
    If there is only one prize ball, then drawing $M = n \log \epsilon^{-1}$ times is sufficient to guarantee it, because the probability of missing all $M$ times is
    
    $$
    \Big(1 - \dfrac 1n\Big)^{n\log\epsilon^{-1}} \leq e^{\log\epsilon} = \epsilon
    $$
    
    Now with $k > 1$ prize balls, according to the Union Bound, we just need to ensure that the probability of missing each prize ball is no more than $\dfrac \epsilon k$. So the answer is $n \log \dfrac{k}{\epsilon}$.

### Example: Randomly Selecting Half the Elements

Give an algorithm to select an equally probable random subset of size $\dfrac{n}{2}$ from $n$ elements, with $n$ guaranteed to be even. The only random source you can use is a fair coin, and try to minimize the number of coin flips (not necessarily optimal).

??? note "Solution"
    First, consider this algorithm:
    
    -   By flipping $n$ coins, we can select an equally probable random subset from all subsets.
    -   Repeat this process until the selected subset has exactly $\dfrac{n}{2}$ elements.
        -   Note that subsets of size $\dfrac{n}{2}$ constitute at least $\dfrac{1}{n}$ of all subsets, so the expected number of repetitions is $\leq n$.
    
    This algorithm requires an expected $n^2$ coin flips.
    
    Another algorithm:
    
    -   We can implement random $n$-to-1 selection by flipping an expected $2\lceil\log_2 n\rceil$ coins.
        -   Specific method: randomly generate a $\lceil\log_2 n\rceil$-bit binary number; if it is greater than or equal to $n$, regenerate; otherwise, select the element with the corresponding index (index starting from 0) and end the process.
    -   Then select one element from all elements, then select one from the remaining elements, and so on, until $\dfrac{n}{2}$ elements are selected.
    
    This algorithm requires an expected $n\lceil\log_2 n\rceil$ coin flips.
    
    Combining the two algorithms:
    
    -   First, use the first algorithm to obtain a random subset.
    -   If the subset size is less than $\dfrac{n}{2}$, use the second algorithm to continuously add elements until the size reaches $\dfrac{n}{2}$.
    -   If the subset size exceeds $\dfrac{n}{2}$, use the second algorithm to continuously remove elements until the size is reduced to $\dfrac{n}{2}$.
    
    Now analyze the number of operations needed for steps 2 and 3 (i.e., the number of additions/removals of elements):
    
    -   Let indicator variable $X_i$ denote whether element $i$ is selected into the initial subset, and let $X := X_1 + \cdots + X_n$ denote the subset size. The number of operations needed in steps 2 and 3 equals $\big|X - \mathrm{E}[X]\big|$. Taking $t = c \cdot \sqrt{n}$ (where $c$ is any constant) in Hoeffding's inequality gives $\mathrm{Pr}\Big[\big|X - \mathrm{E}[X]\big| \geq t\Big] \leq 2\mathrm{e}^{-c^2}$. That is, by allowing a $\Theta(\sqrt{n})$-level deviation, we can achieve any desired constant-level failure probability.
    
    So far we have shown that this algorithm can with high probability guarantee the number of coin flips is within $n + \Theta(\sqrt{n}\log n)$.
    
    -   Here $n$ comes from the coin flips needed to obtain the initial subset; $\Theta(\sqrt{n}\log n)$ is the total overhead for $\Theta(\sqrt{n})$ additions/removals.
    
    ??? note "Expected Complexity Calculation"
        Let's analyze from another perspective, trying to calculate the expected number of coin flips for this algorithm.
        
        Use Hoeffding's inequality to find an upper bound on the expected number of operations in steps 2 and 3:
        
        $$
        E|X - EX| = \int_0^\infty P\{ |X - E[X]| \geq t \} \mathrm{d}t \leq 
        2 \int_0^\infty \exp \left(-\frac {t^2}{n}\right) \mathrm{d}t = \sqrt{\pi n}
        $$
        
        Thus the expected number of coin flips needed for steps 2 and 3 is $\sqrt{\pi n} \cdot 2\lceil\log_2 n\rceil$.
        
        In summary, this algorithm requires an expected $n + 2\sqrt{\pi n}\lceil\log_2 n\rceil$ coin flips.

### Exercise: Balls and Bins

$n$ balls are independently and randomly thrown into $n$ bins. Prove that with probability $1 - \dfrac{1}{n}$, the maximum number of balls in any bin is at least $\Omega \left( \dfrac{\log n}{\log \log n} \right)$.