author: sshwy, FFjet, qz-cqy

## Introduction

The Euclidean-like algorithm was proposed by Hong Huadun during the 2016 winter camp exchange. It is commonly used to solve summation problems of sequences in the form:

$$
\left\lfloor\dfrac{ai+b}{c}\right\rfloor
$$

(indexed by $i$). Its main idea is to use the recursive structure of fractions to transform the problem into smaller ones and solve recursively. Because there is a direct [relationship](./continued-fraction.md#continued-fraction-algorithms) between the recursive structure of fractions and the [Euclidean algorithm](./gcd.md#euclidean-algorithm), this summation method is also called the Euclidean-like algorithm.

Since [continued fractions](./continued-fraction.md) and [Stern-Brocot trees](./stern-brocot.md) also describe the recursive structure of fractions, problems that can be solved using the Euclidean-like algorithm can usually be solved by these methods as well. Compared to these methods, the Euclidean-like algorithm is usually easier to understand, and its implementation is more straightforward.

## Euclidean-like Algorithm

The simplest example is the summation problem:

$$
f(a,b,c,n)=\sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor,
$$

where $a,b,c,n$ are all positive integers.

### Algebraic Solution

First, take $a,b$ modulo $c$ to simplify the problem, transforming it to the case $0\le a,b<c$:

$$
\begin{aligned}
f(a,b,c,n)&=\sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor\\
&=\sum_{i=0}^n\left\lfloor
\frac{\left(\left\lfloor\frac{a}{c}\right\rfloor c+(a\bmod c)\right)i+\left(\left\lfloor\frac{b}{c}\right\rfloor c+(b\bmod c)\right)}{c}\right\rfloor\\
&=\sum_{i=0}^n\left(\left\lfloor\frac{a}{c}\right\rfloor i+\left\lfloor\frac{b}{c}\right\rfloor+\left\lfloor\frac{\left(a\bmod c\right)i+\left(b\bmod c\right)}{c}
\right\rfloor\right)\\
&=\frac{n(n+1)}{2}\left\lfloor\frac{a}{c}\right\rfloor
+(n+1)\left\lfloor\frac{b}{c}\right\rfloor+f(a\bmod c,b\bmod c,c,n).
\end{aligned}
$$

Now consider the transformed problem. Let:

$$
m = \left\lfloor \frac{an+b}{c} \right\rfloor.
$$

Then the original problem can be written as a double summation:

$$
\sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor
=\sum_{i=0}^n\sum_{j=0}^{m-1}\left[j<\left\lfloor \frac{ai+b}{c} \right\rfloor\right].
$$

Swap the order of summation, which requires finding the range of $i$ that satisfies the condition for each $j$. For this, transform the condition:

$$
\begin{aligned}
&j<\left\lfloor \frac{ai+b}{c} \right\rfloor = \left\lceil \frac{ai+b+1}{c} \right\rceil-1\\
&\iff j + 1 < \left\lceil \frac{ai+b+1}{c} \right\rceil
\iff j+1< \frac{ai+b+1}{c} \\
&\iff \dfrac{cj+c-b-1}{a} < i
\iff \left\lfloor\dfrac{cj+c-b-1}{a}\right\rfloor < i.
\end{aligned}
$$

The transformation process uses the properties of [floor and ceiling functions](./basic.md#floor-and-ceiling-functions). Substituting the transformed condition, the original formula can be written as:

$$
\begin{aligned}
f(a,b,c,n)&=\sum_{j=0}^{m-1}
\sum_{i=0}^n\left[i>\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor \right]\\
&=\sum_{j=0}^{m-1}\left(n-\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor\right)\\
&=nm-f\left(c,c-b-1,a,m-1\right).
\end{aligned}
$$

Let $(a',b',c',n')=(c,c-b-1,a,m-1)$, which again falls into the case $a'>c'$ discussed earlier.

Combining these two transformations, we can find that in the process, $(a,c)$ continuously takes mod and exchanges positions until $a=0$. This is similar to performing Euclidean algorithm on $(a,c)$, which is how the Euclidean-like algorithm gets its name. Its time complexity is $O(\log\min\{a,c\})$.

During computation, the case $m=0$ might occur, which leads to inner recursion with $n=-1$. This does not affect the final result. However, if we terminate the algorithm when $m=0$ occurs, the time complexity can be improved to $O(\log\min\{a,c,n\})$.

??? note "Explanation of Complexity"
    Using the similarity with the Euclidean algorithm, it is easy to explain that its time complexity is $O(\log\min\{a,c\})$. Therefore, we only need to explain that if we terminate the algorithm when $m=0$, the time complexity is also $O(\log n)$.
    
    Let $m=\lfloor(an+b)/c\rfloor$, and denote $S=mn$, $k=m/n$, which respectively correspond to the area and slope of the geometric diagram (see the next section). For sufficiently large $n$, we have approximately $k\doteq a/c$.
    
    Observe the changes of $S$ and $k$ during the algorithm. In the first step of taking mod, $n$ remains unchanged, and $k$ changes from $a/c$ to $(a\bmod c)/c$, which is equivalent to the slope changing from $k$ to $k-\lfloor k\rfloor$, and $S$ also approximately becomes $(k-\lfloor k\rfloor)$ times its original value. In the second step of swapping coordinates, $S$ remains approximately unchanged, while $k$ becomes its reciprocal. Therefore, if after the two steps the pair $(k,S)$ becomes $(k',S')$, we have $k'=(k-\lfloor k\rfloor)^{-1}$ and $S'=(k-\lfloor k\rfloor)S$.
    
    Since $1\le\lfloor k'\rfloor\le k'<\lfloor k'\rfloor+1$, after two rounds of recursive computation, the product reduction ratio is at least
    
    $$
    (k'-\lfloor k'\rfloor)(k-\lfloor k\rfloor) = 1-\dfrac{\lfloor k'\rfloor}{k'} < 1-\dfrac{\lfloor k'\rfloor}{\lfloor k'\rfloor+1} = \dfrac{1}{\lfloor k'\rfloor+1}\le \dfrac{1}{2}.
    $$
    
    Therefore, after at most $O(\log S)$ rounds, the algorithm must terminate. Because from the second round onwards, the $S$ at the beginning of each round is never more than the $S$ after the mod-taking of the previous round, and the latter is roughly $kn^2$ with $k<1$, thus $O(\log S)\subseteq O(\log n)$. This gives the above conclusion.

The reference implementation for the template problem is as follows:

??? example "Template Problem Implementation (Library Checker - Sum of Floor of Linear)](https://judge.yosupo.jp/problem/sum_of_floor_of_linear)"
    ```cpp
    --8<-- "docs/math/code/euclidean/euclidean-0.cpp:full-text"
    ```

### Geometric Interpretation

This algorithm can also be understood geometrically. The problems that the Euclidean-like algorithm can solve are mainly integer point counting problems under a line.

As shown in the leftmost part of the figure below, this summation is equivalent to counting the number of lattice points under the line

$$
y = \dfrac{ax+b}{c}
$$

above the $x$-axis (not including the $x$-axis) and with $x$-coordinate in $[0,n]$.

![](./images/euclidean-1.svg)

First, remove the integer parts of the slope and intercept. This step corresponds to calculating the number of blue points in the middle part of the figure separately. When both the slope and intercept are integers, the blue points form a trapezoidal array, that is, the lattice points in different vertical columns form an arithmetic progression, so the number of these points is easy to calculate. After removing these points, the remaining lattice points are consistent with the red points in the rightmost part of the figure. The problem is transformed into the case where both the slope and intercept are less than one. Since the height of the trapezoid is $n+1$ and the lengths of the two bases are $\lfloor b/c\rfloor$ and $(\lfloor a/c\rfloor n+\lfloor b/c\rfloor)$, using the formula for the area of a trapezoid, this step can be summarized as:

$$
f(a,b,c,n) = f(a\bmod c,b\bmod c,c,n) + \dfrac{1}{2}(n+1)\left(\left\lfloor\dfrac{b}{c}\right\rfloor+\left(\left\lfloor\dfrac{a}{c}\right\rfloor n+\left\lfloor\dfrac{b}{c}\right\rfloor\right)\right).
$$

Then, flip the $x$ and $y$ axes. As shown in the leftmost part of the figure below, the red and blue points in the figure form a rectangular point array of horizontal length $n$ and vertical length $m=\lfloor(an+b)/c\rfloor$. To count the number of red points, we only need to count the number of blue points and subtract from the total of the rectangular point array. After flipping, the blue point array in the left part becomes the red point array under some line. Moreover, after flipping, the slope is greater than one, which again falls into the case already processed above.

![](./images/euclidean-2.svg)

The key is how to compute the equation of the line above the new red point array. Flipping the $x$ and $y$ axes of the leftmost part gives the middle part. The line above the red point array after flipping (the solid line in the middle part) does not correspond to the line before flipping (the solid line in the leftmost part), but is the result of shifting the line before flipping slightly up and to the left (the dashed line in the leftmost part). This is because if we directly flip the line (the solid line in the leftmost part), we get the dashed line in the middle part, but by definition, the lattice points under it include those exactly on the line, which would lead to double counting of points on the line. To avoid this, after flipping the line, we shift the line $y=(cx-b)/a$ downward slightly to get $y=(cx-b-1)/a$, so that the point array under it is exactly the blue point array before flipping.

There is another detail to handle. The intercept of the line in the middle part of the figure is negative, which means it has not yet returned to the initial case. To make the intercept non-negative, we only need to shift the line (the solid line in the middle part) left by one unit. This does not miss any lattice points because there are no points with zero $y$-coordinate in the blue point array before flipping, and after flipping, there are no points with zero $x$-coordinate. Finally, the line equation becomes $y=(cx+c-b-1)/a$; at the same time, the upper bound of the $x$-coordinate of the point array also changes from $m$ to $m-1$. This step can be summarized as:

$$
f(a,b,c,n) = mn - f(c,c-b-1,a,m-1).
$$

This recursive algorithm works for two main reasons:

-   First, the slope of the line continuously takes its fractional part and then takes its reciprocal, which is equivalent to the [continued fraction expansion](./continued-fraction.md#continued-fraction-algorithms) of the line slope $k=a/c$. Since the length of the continued fraction expansion of a rational number is $O(\log\min\{a,c\})$, this process must terminate after $O(\log\min\{a,c\})$ steps;
-   Second, because when flipping the axes each time, the slope of the line is less than one, so intuitively we should have $m<n$, that is, after such an iteration, the range of the $x$-coordinate is always shrinking. The complexity calculation in the previous section strictly shows that after every two iterations, $n$ is at most half of the original, so this process must terminate after $O(\log n)$ steps.

This is also the reason why the Euclidean-like algorithm has complexity $O(\log\min\{a,c,n\})$ when the slope is a rational number.

Using a similar geometric interpretation, the Euclidean-like algorithm can be extended to the case where the slope is an irrational number. For a detailed analysis, see the example problems later.

### Example Problems

???+ example "[Template Euclidean-like Algorithm](https://www.luogu.com.cn/problem/P5170)"
    Multiple queries. Given positive integers $a,b,c,n$, find:
    
    $$
    \begin{aligned}
    f(a,b,c,n) &= \sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor,\\
    g(a,b,c,n) &= \sum_{i=0}^ni\left\lfloor \frac{ai+b}{c} \right\rfloor,\\
    h(a,b,c,n) &= \sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor^2.
    \end{aligned}
    $$

??? note "Solution One"
    Similar to the derivation of $f$, we can get the recursive expressions for $g$ and $h$.
    
    First, using modulo to transform to $0\le a,b<c$:
    
    $$
    \begin{aligned}
    g(a,b,c,n)
    &=g(a\bmod c,b\bmod c,c,n)+\left\lfloor\frac{a}{c}\right\rfloor\frac{n(n+1)(2n+1)}{6}+\left\lfloor\frac{b}{c}\right\rfloor\frac{n(n+1)}{2}, \\
    h(a,b,c,n)&=h(a\bmod c,b\bmod c,c,n)\\
    &\quad+2\left\lfloor\frac{b}{c}\right\rfloor f(a\bmod c,b\bmod c,c,n)
    +2\left\lfloor\frac{a}{c}\right\rfloor g(a\bmod c,b\bmod c,c,n)\\
    &\quad+\left\lfloor\frac{a}{c}\right\rfloor^2\frac{n(n+1)(2n+1)}{6}+\left\lfloor\frac{b}{c}\right\rfloor^2(n+1)
    +\left\lfloor\frac{a}{c}\right\rfloor\left\lfloor\frac{b}{c}\right\rfloor n(n+1).
    \end{aligned}
    $$
    
    Then, by swapping the order of summation, we can further transform. Similarly, let:
    
    $$
    m = \left\lfloor \frac{an+b}{c} \right\rfloor.
    $$
    
    Then for the sum $g$:
    
    $$
    \begin{aligned}
    g(a,b,c,n)&=\sum_{i=0}^ni\left\lfloor \frac{ai+b}{c} \right\rfloor\\
    &=\sum_{i=0}^n \sum_{j=0}^{m-1}i
    \left[j<\left\lfloor\frac{ai+b}{c}\right\rfloor\right] \\
    &=\sum_{j=0}^{m-1}\sum_{i=0}^n i\left[i>\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor \right]\\
    &=\sum_{j=0}^{m-1}\dfrac{1}{2}\left(\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor+n+1\right)\left(n-\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor\right)\\
    &=\dfrac{1}{2}mn(n+1) - \dfrac{1}{2}\sum_{j=0}^{m-1}\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor - \dfrac{1}{2}\sum_{j=0}^{m-1}\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor^2\\
    &=\dfrac{1}{2}mn(n+1) - \dfrac{1}{2}f(c,c-b-1,a,m-1) - \dfrac{1}{2}h(c,c-b-1,a,m-1).
    \end{aligned}
    $$
    
    For the sum $h$:
    
    $$
    \begin{aligned}
    h(a,b,c,n)&=\sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor^2\\
    &=\sum_{i=0}^n\sum_{j=0}^{m-1}(2j+1)\left[j<\left\lfloor\frac{ai+b}{c}\right\rfloor\right]\\
    &=\sum_{j=0}^{m-1}\sum_{i=0}^n(2j+1)\left[i>\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor \right]\\
    &=\sum_{j=0}^{m-1}(2j+1)\left(n-\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor\right)\\
    &=nm^2 - \sum_{j=0}^{m-1}\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor - 2\sum_{j=0}^{m-1}j\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor\\
    &=nm^2 - f(c,c-b-1,a,m-1) - 2g(c,c-b-1,a,m-1).
    \end{aligned}
    $$
    
    From the geometric perspective, these nonlinear sums assign corresponding weights $w(i,j)$ to each point $(i,j)$ in the region. Apart from these weights, the rest of the computation process is exactly the same. For the choice of weights, in general:
    
    $$
    \sum_{i=0}^ni^r\left\lfloor \frac{ai+b}{c} \right\rfloor^s = \sum_{i=0}^n\sum_{j=0}^{m-1} i^r\left((j+1)^s-j^s\right)\left[j<\left\lfloor\frac{ai+b}{c}\right\rfloor\right].
    $$
    
    Another characteristic of this problem is that $g$ and $h$ intersect each other during recursive computation. Therefore, $(f,g,h)$ needs to be recursively computed as a triple.
    
    ```cpp
    --8<-- "docs/math/code/euclidean/euclidean-1.cpp"
    ```

???+ example "[Tsinghua Training 2014] Sum](https://www.luogu.com.cn/problem/P5172)"
    Multiple queries. Given positive integers $n$ and $r$, find:
    
    $$
    \sum_{d=1}^n(-1)^{\lfloor d\sqrt{r}\rfloor}.
    $$

??? note "Solution One"
    If $r$ is a perfect square, then when $\sqrt{r}$ is even, the sum is $n$; otherwise, the sum alternates between $0$ and $-1$ depending on the parity of $n$. Below we consider the case where $r$ is not a perfect square.
    
    To apply the Euclidean-like algorithm, first transform the summation into the familiar form:
    
    $$
    \begin{aligned}
    \sum_{d=1}^n(-1)^{\lfloor d\sqrt{r}\rfloor} &= \sum_{d=1}^n\left(1 - 2(\lfloor d\sqrt{r}\rfloor\bmod 2)\right)\\
    &= n - 2\sum_{d=1}^n\left(\lfloor d\sqrt{r}\rfloor - 2\left\lfloor\dfrac{\lfloor d\sqrt{r}\rfloor}{2}\right\rfloor\right) \\
    &= n - 2\sum_{d=1}^n\lfloor d\sqrt{r}\rfloor + 4 \sum_{d=1}^n\left\lfloor\dfrac{d\sqrt{r}}{2}\right\rfloor\\
    &= n - 2f(n,1,0,1) + 4f(n,1,0,2)
    \end{aligned}
    $$
    
    The function $f$ here has the form:
    
    $$
    f(a,b,c,n) = \sum_{i=1}^n\left\lfloor\dfrac{a\sqrt{r}+b}{c}i\right\rfloor.
    $$
    
    Different from the algorithm in the main text, the slope here is no longer a rational number. Let the slope be:
    
    $$
    k = \dfrac{a\sqrt{r}+b}{c}.
    $$
    
    Again, discuss in two cases. If $k\ge 1$, then:
    
    $$
    \begin{aligned}
    f(a,b,c,n) &= \sum_{i=1}^n \lfloor ki\rfloor = \sum_{i=1}^n \lfloor(k-\lfloor k\rfloor)i\rfloor + \lfloor k\rfloor \sum_{i=1}^ni\\
    &= \lfloor k\rfloor\dfrac{n(n+1)}{2} + f(a,b-c\lfloor k\rfloor,c,n).
    \end{aligned}
    $$
    
    The problem transforms to the case where the slope is less than one. If $k<1$, let $m=\lfloor nk\rfloor$:
    
    $$
    \begin{aligned}
    f(a,b,c,n) &= \sum_{i=1}^n \lfloor ki\rfloor = \sum_{i=1}^n\sum_{j=1}^m[j\le\lfloor ki\rfloor]\\
    &= \sum_{j=1}^m\sum_{i=1}^n[i>\lfloor k^{-1}j\rfloor] = nm - \sum_{j=1}^m\sum_{i=1}^n[i\le\lfloor k^{-1}j\rfloor].
    \end{aligned}
    $$
    
    In this derivation, the condition for swapping $i$ and $j$ is simpler than in the main text because there are no lattice points on the line $y=kx$ except the origin. The key is to write the summed expression after swapping in the form $f(a,b,c,n)$, which requires finding $a',b',c'$ satisfying:
    
    $$
    k^{-1} = \dfrac{a'\sqrt{r}+b'}{c'}.
    $$
    
    This is not difficult. By rationalizing the denominator:
    
    $$
    k^{-1} = \dfrac{c}{a\sqrt{r}+b} = \dfrac{ca\sqrt{r}-cb}{a^2r-b^2}.
    $$
    
    Therefore:
    
    $$
    a'=ca,~b'=-cb,~c'=a^2r-b^2.
    $$
    
    This shows:
    
    $$
    f(a,b,c,n) = nm - f(ca,-cb,a^2r-b^2,m).
    $$
    
    To avoid integer overflow, we need to divide $a,b,c$ by their greatest common divisor each time. Since this computation process is exactly the same as the process of computing the continued fraction of $k$, according to the [continued fraction theory](./continued-fraction.md#quadratic-irrational-numbers), as long as $\gcd(a,b,c)=1$, they are necessarily within the integer range during computation. Also, although $(a,b,c,n)$ will not overflow, in the data range of this problem, $f(a,b,c,n)$ may exceed the range of 64-bit integers, and natural overflow is fine; no special handling is needed, and the final result is definitely between $[-n,n]$.
    
    Although the slope does not become zero, the complexity is still $O(\log n)$, which is easy to see from the previous proof of algorithm complexity.
    
    ```cpp
    --8<-- "docs/math/code/euclidean/euclidean-2.cpp"
    ```

???+ example "[Fraction](https://www.luogu.com.cn/problem/P5179)"
    Given positive integers $a,b,c,d$, find the reduced fraction $p/q$ that satisfies $a/b<p/q<c/d$ and has the smallest lexicographic order $(q,p)$.

??? note "Solution"
    This problem is also a classic application of the [Stern-Brocot tree](./stern-brocot.md). The solution can be found at [there](./continued-fraction.md#fraction-tree). Since it only depends on the recursive structure of fractions, it can also be solved using the Euclidean-like algorithm method, so it can also be regarded as an application of the Euclidean-like algorithm.
    
    If there is at least one natural number between $a/b$ and $c/d$ (not including endpoints), we can directly take $(q,p)=(1,\lfloor a/b\rfloor+1)$. Otherwise, we necessarily have:
    
    $$
    \left\lfloor\dfrac{a}{b}\right\rfloor \le \dfrac{a}{b} <\dfrac{p}{q} <\dfrac{c}{d}\le\left\lfloor\dfrac{a}{b}\right\rfloor+1.
    $$
    
    From this inequality, the integer part of $p/q$ can be determined as $\lfloor a/b\rfloor$. Then eliminate this integer part and take the reciprocal to determine its fractional part. This is exactly the [basic method](./continued-fraction.md#continued-fraction-algorithms) for determining the continued fraction of $p/q$. If the final answer is $p/q$, the time complexity of the algorithm is $O(\log\min\{p,q\})$.
    
    Here, there is a detail problem: whether the fraction with the smallest lexicographic order after taking the reciprocal is the same as before taking the reciprocal. In other words, among fractions $p/q$ satisfying $a/b<p/q<c/d$, is the one with the smallest lexicographic order $(q,p)$ also the one with the smallest lexicographic order $(p,q)$? Suppose not. Let $p/q$ be the one with the smallest lexicographic order $(q,p)$, but $r/s\neq p/q$ is the one with the smallest lexicographic order $(r,s)$. This necessarily has $r<p$ and $q<s$. But this shows:
    
    $$
    \dfrac{a}{b} < \dfrac{r}{s} < \dfrac{r}{q} < \dfrac{p}{q} < \dfrac{c}{d}.
    $$
    
    Therefore, $r/q$ is strictly smaller than the current solution in whichever lexicographic order. This contradicts the assumption. Therefore, the above algorithm is correct.
    
    ```cpp
    --8<-- "docs/math/code/euclidean/euclidean-3.cpp"
    ```

## Universal Euclidean Algorithm

The derivation of the Euclidean-like algorithm discussed in the previous section is usually relatively cumbersome, and the summations it can solve are mainly summations that can be transformed into counting (weighted) integer points under a line. This section discusses a more general method that further abstracts the above process, so it can solve more problems. Therefore, this method is also called the Universal Euclidean Algorithm. It also uses the recursive structure of fractions to solve problems, but the way it reduces the problem is slightly different from the Euclidean-like algorithm.

Still consider the classic summation:

$$
f(a,b,c,n)=\sum_{i=1}^n\left\lfloor \frac{ai+b}{c} \right\rfloor,
$$

where $a,b,c,n$ are all positive integers.

### Problem Transformation

Define the segment with parameters $(a,b,c,n)$ as:

$$
y = \frac{ax+b}{c},~0< x\le n.
$$

For this segment, we can define a string composed of $U$ and $R$ as follows, also called the **operation sequence**:

-   The string consists of exactly $n$ $R$'s and $m=\lfloor(an+b)/c\rfloor$ $U$'s;
-   The number of $U$'s before the $i$-th $R$ is exactly $\lfloor(ai+b)/c\rfloor$, where $i=1,\cdots,n$.

From the geometric perspective, this is roughly equivalent to starting from the origin, writing an $R$ each time we cross a vertical grid line to the right, and writing a $U$ each time we cross a horizontal grid line upward. As shown in the figure:

![](./images/euclidean-universal.svg)

Of course, such a definition also needs to consider several special cases:

-   When passing through a lattice point (i.e., crossing up and right simultaneously), first write $U$ then $R$:
-   At the beginning of the string, in addition to the number of times crossing the grid line upward in the interval $(0,1]$, we need to additionally add $\lfloor b/c\rfloor$ $U$'s;
-   At the end of the string, there should be no extra $U$'s.

If the description of the geometric perspective is unclear, you can refer to the definition in the algebraic method above to assist understanding. The description of geometric perspective helps understand the algorithm process below.

The basic idea of the Universal Euclidean Algorithm is to treat both $U$ and $R$ in the operation sequence as elements of some [monoid](../algebra/basic.md#monoids), and treat the entire operation sequence as the product of elements in the monoid, with the final answer related to this product.

For example, in this problem, we can define the state vector $v = (1,y,\sum y)$, which represents the current state after starting from the origin and crossing several grid lines upward and rightward. Here, the first component is a constant, the second component is the $y$-coordinate, and the third component is the required sum. Initially, we have $v=(1,0,0)$. Each time we cross upward across a grid line, the $y$-coordinate increases by one, which is equivalent to multiplying the state vector on the right by the matrix:

$$
U = \begin{pmatrix}1 & 1 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1\end{pmatrix}.
$$

Each time we cross right across a grid line, the sum increases by the $y$-coordinate, which is equivalent to multiplying the state vector on the right by the matrix:

$$
R = \begin{pmatrix}1 & 0 & 0 \\ 0 & 1 & 1 \\ 0 & 0 & 1\end{pmatrix}.
$$

Therefore, the final state is the product $(1,0,0)S$, where $S$ is understood as the product of the above matrices. The answer we want is the third component of the final state.

In addition to defining elements in the monoid as matrices, we can also define the contribution of a segment of operation sequence to the final result, and then define the product of operations as the combination of the contributions of two segments of operation sequences.

In this problem, we can define the contribution of each segment of operation sequence as $(x,y,\sum y)$. To rigorously explain these notations, we can consider these components as functions of the operation sequence. That is, for an operation sequence $S$, its contribution can be written as $(x(S),y(S),(\sum y)(S))$. Here, $x(S)$ and $y(S)$ respectively correspond to the number of $R$'s and $U$'s in the operation sequence $S$, which is the number of times this segment crosses rightward and upward across grid lines. For the function $f$ on an operation sequence, we can define $(\sum f)(S)$, or write as $\sum_S f$, as the following expression:

$$
\sum_S f := \sum\{f(S_{[1,r]}):S_r=R\}.
$$

Here, $S_r$ is the $r$-th character in $S$, and $S_{[1,r]}$ is the prefix of the first $r$ characters in $S$. That is, this summation notation can be seen as the summation over all prefixes of $S$ ending with $R$. For example:

$$
\sum_S 1 = x,~ \sum_S x = \dfrac{1}{2}x(x+1).
$$

For another example, $\sum y$ is the accumulated number of times crossing upward across grid lines each time crossing rightward across a grid line. For the entire operation sequence, the values of $y$ at all prefixes ending with $R$ are exactly all the values $\lfloor(ai+b)/c\rfloor$ at $i=1,\cdots,n$. Therefore, computing $\sum y$ for the entire operation sequence is exactly the quantity required in this problem.

Initially, we have $U=(0,1,0)$, $R=(1,0,0)$. Moreover, we can define the product of two elements $(x_1,y_1,s_1)$ and $(x_2,y_2,s_2)$ as:

$$
(x_1,y_1,s_1)\cdot (x_2,y_2,s_2) = (x_1+x_2,y_1+y_2,s_1+s_2+x_2y_1).
$$

Here, the last term in the contribution of the combined result can be obtained by the following calculation:

$$
\sum_{S_1+S_2}y = \sum_{S_1}y + \sum_{S_2}(y+y_1) = \sum_{S_1}y + \sum_{S_2}y + y_1\sum_{S_2}1 = s_1+s_2+x_2y_1.
$$

It is easy to verify that this multiplication operation satisfies the associativity law, and the identity element is $(0,0,0)$, so these elements form a monoid under this multiplication operation. The answer we want is the third component of the product.

Both methods can get the correct results. However, because the matrix operation retains more redundant information and has a larger constant, the second method is more practical when dealing with actual problems.

### Algorithm Process

Different from the overall reduction of the Euclidean-like algorithm, the Universal Euclidean Algorithm reduces the problem by combining these operations in batches. Let the product of operations corresponding to the string be:

$$
F(a,b,c,n,U,R).
$$

The reduction process is as follows:

-   When $b\ge c$, at the beginning of the operation sequence, there are $\lfloor b/c\rfloor$ $U$'s. Directly compute their product, and remove these $U$'s from the operation sequence. At this time, the number of $U$'s before the $i$-th $R$ is:

    $$
    \left\lfloor\dfrac{ai+b}{c}\right\rfloor - \left\lfloor\dfrac{b}{c}\right\rfloor = \left\lfloor\dfrac{ai+(b\bmod c)}{c}\right\rfloor.
    $$

    This is equivalent to changing the segment parameters from $(a,b,c,n)$ to $(a,b\bmod c,c,n)$. So for this case:

    $$
    F(a,b,c,n,U,R) = U^{\lfloor b/c\rfloor}F(a,b\bmod c,c,n,U,R).
    $$

-   When $a\ge c$, in the operation sequence, each $R$ has at least $\lfloor a/c\rfloor$ $U$'s in front of it, which can be combined into $R$. That is, $R$ can be replaced by $U^{\lfloor a/c\rfloor}R$. In the combined string, the number of $U$'s before the $i$-th $R$ is:

    $$
    \left\lfloor\dfrac{ai+b}{c}\right\rfloor - \left\lfloor\dfrac{a}{c}\right\rfloor i = \left\lfloor\dfrac{(a\bmod c)i+b}{c}\right\rfloor.
    $$

    This is equivalent to changing the segment parameters from $(a,b,c,n)$ to $(a\bmod c,b,c,n)$. So for this case:

    $$
    F(a,b,c,n,U,R) = F(a\bmod c,b,c,n,U,U^{\lfloor a/c\rfloor}R).
    $$

-   For the remaining cases, we need to flip the $x$ and $y$ axes, which basically swaps $U$ and $R$, but the segment parameters after flipping need to be carefully calculated. Combined with the definition of the operation sequence, we need to determine coefficients $(a',b',c',n')$ such that in the operation sequence before flipping, the number of $R$'s before the $j$-th $U$ is exactly $\lfloor(a'j+b')/c'\rfloor$ and there are a total of $n'$ $U$'s. According to the definition:

    $$
    n'=\left\lfloor\dfrac{an+b}{c}\right\rfloor = m,
    $$

    And the number of $R$'s before the $j$-th $U$ is the largest $i$ such that:

    $$
    \begin{aligned}
    \left\lfloor\dfrac{ai+b}{c}\right\rfloor < j 
    &\iff \dfrac{ai+b}{c} < j \iff i < \dfrac{cj-b}{a} \\
    &\iff i < \left\lceil\dfrac{cj-b}{a}\right\rceil = \left\lfloor\dfrac{cj-b - 1}{a}\right\rfloor + 1.
    \end{aligned}
    $$

    Therefore, $i = \lfloor(cj-b-1)/a\rfloor$. This derivation process is similar to the derivation of the Euclidean-like algorithm above, and also uses the properties of floor and ceiling functions.

    There are two details to handle:

    -   The intercept term $-(b+1)/a$ is negative. Note that if we shift the segment left by one unit, the intercept term becomes positive because $(c-b-1)/a\ge 0$. Therefore, we can extract the first $R^{\lfloor(c-b-1)/a\rfloor}U$ and only swap $U$ and $R$ in the remaining operation sequence;
    -   After swapping $U$ and $R$, there are extra $U$'s at the end. Therefore, before swapping $U$ and $R$, we need to first extract the last $R$, and only swap $U$ and $R$ in the remaining operation sequence. The number of this segment of $R$ is $n-\lfloor(cm-b-1)/a\rfloor$.

    After removing several characters at the beginning and end, the number of $R$'s before the $j$-th $U$ becomes:

    $$
    \left\lfloor\dfrac{c(j+1)-b-1}{a}\right\rfloor - \left\lfloor\dfrac{c-b-1}{a}\right\rfloor = \left\lfloor\dfrac{cj+(c-b-1)\bmod a}{a}\right\rfloor.
    $$

    Recall that the number of $U$'s before flipping is $m = \lfloor(an+b)/c\rfloor$. And this shift by one unit requires that there is at least one $U$ before flipping, i.e., $m>0$. Using this condition, we can divide into two cases:

    -   For the case $m>0$, after handling the above two points, the operation sequence after swapping $U$ and $R$ is exactly the valid sequence corresponding to the segment with parameters $(c,(c-b-1)\bmod a,a,m-1)$. Therefore:

        $$
        F(a,b,c,n,U,R) = R^{\lfloor(c-b-1)/a\rfloor}UF(c,(c-b-1)\bmod a,a,m-1,R,U)R^{n-\lfloor(cm-b-1)/a\rfloor}.
        $$

    -   Especially for the case $m=0$, the operation sequence before swapping only contains $n$ $R$'s, and we can return directly:

        $$
        F(a,b,c,n,U,R) = R^n.
        $$

        Different from the Euclidean-like algorithm, this special case of the Universal Euclidean Algorithm needs to be handled separately, otherwise it cannot be calculated correctly due to involving negative exponents.

Using these discussions, the problem can be solved recursively.

Assume that the time complexity of a single multiplication of elements in the monoid is $O(1)$. Then, if all exponent calculations of these elements during the computation use [fast exponentiation](../binary-exponentiation.md), the final algorithm complexity is $O(\log\max\{a,c\}+\log(b/c))$[^complexity].

??? note "Explanation of Complexity"
    Comparing with the (Euclidean) Euclidean algorithm, the Universal Euclidean Algorithm just adds the step of fast exponentiation. The rest of the computation process has a complexity similar to the Euclidean-like algorithm, which has been shown to be $O(\log\min\{a,c,n\})$. Now we need to compute the total complexity of these fast exponentiations.
    
    Except for the first iteration, we have $b<c$, so each of these iterations involves three fast exponentiation calculations, with a total complexity of:
    
    $$
    O\left(\log\left\lfloor\dfrac{a}{c}\right\rfloor+\log\left\lfloor\dfrac{c-b_1-1}{a_1}\right\rfloor+\log\left(n-\left\lfloor\dfrac{cm-b_1-1}{a_1}\right\rfloor\right)\right),
    $$
    
    where $a_1=a\bmod c$, $b_1=b\bmod c$ and $m=\lfloor(a_1n+b_1)/c\rfloor$. For the latter two, we have estimates:
    
    $$
    \begin{aligned}
    \dfrac{c-b_1-1}{a_1} &\le \dfrac{c}{a_1},\\
    n-\left\lfloor\dfrac{cm-b_1-1}{a_1}\right\rfloor &\le n - \dfrac{cm-b_1-1}{a_1} + 1 \\
    &\le n - \dfrac{c((a_1n+b_1)/c-1)-b_1-1}{a_1} +1 \\
    &= \dfrac{c+1}{a_1}+1.
    \end{aligned}
    $$
    
    Therefore, the complexity of these two is $O(\log(c/a_1))$.
    
    In each iteration, the segment parameters change from $(a,\cdot,c,\cdot)$ to $(c,\cdot,a\bmod c,\cdot)$, and the total time complexity of the round is:
    
    $$
    O\left(\log\dfrac{a}{c}+\log\dfrac{c}{a\bmod c}\right).
    $$
    
    For all rounds of recursion, these terms can be canceled by splitting, so the total complexity is $O(\log a+\log c)=O(\log\max\{a,c\})$.
    
    Finally, plus the complexity of the first iteration of fast exponentiation $U^{\lfloor b/c\rfloor}$, which is $O(\log(b/c))$, we get the total complexity $O(\log\max\{a,c\}+\log(b/c))$.

The process of the Universal Euclidean Algorithm can be written as a unified template. When dealing with specific problems, we only need to change the implementation of the template type `T`.

???+ example "Reference Implementation"
    ```cpp
    --8<-- "docs/math/code/euclidean/euclidean-4.cpp:euclidean"
    ```

Using the Universal Euclidean Algorithm, we can get the implementation of the template problem as follows:

??? example "Template Problem Implementation (Library Checker - Sum of Floor of Linear)](https://judge.yosupo.jp/problem/sum_of-floor-of-linear)"
    ```cpp
    --8<-- "docs/math/code/euclidean/euclidean-4.cpp:full-text"
    ```

### Example Problems

???+ example "[Template Euclidean-like Algorithm](https://www.luogu.com.cn/problem/P5170)"
    Multiple queries. Given positive integers $a,b,c,n$, find:
    
    $$
    \begin{aligned}
    f(a,b,c,n) &= \sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor,\\
    g(a,b,c,n) &= \sum_{i=0}^ni\left\lfloor \frac{ai+b}{c} \right\rfloor,\\
    h(a,b,c,n) &= \sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor^2.
    \end{aligned}
    $$

??? note "Solution Two"
    To apply the Universal Euclidean Algorithm template, first extract the term for $i=0$ and consider it separately. For the rest, we can consider them as calculating $\sum y,\sum xy,\sum y^2$ for segments with parameters $(a,b,c,n)$. As mentioned in the main text, there are two ways to convert operation sequences into monoid elements.
    
    **Matrix Operation**: The state vector is defined as $(1,x,y,xy,y^2,\sum y,\sum xy,\sum y^2)$. The initial state is $(1,0,0,0,0,0,0,0)$. The two operations are respectively:
    
    $$
    U =
    \begin{pmatrix}
    1 & 0 & 1 & 0 & 1 & 0 & 0 & 0 \\
    0 & 1 & 0 & 1 & 0 & 0 & 0 & 0 \\
    0 & 0 & 1 & 0 & 2 & 0 & 0 & 0 \\
    0 & 0 & 0 & 1 & 0 & 0 & 0 & 0 \\
    0 & 0 & 0 & 0 & 1 & 0 & 0 & 0 \\
    0 & 0 & 0 & 0 & 0 & 1 & 0 & 0 \\
    0 & 0 & 0 & 0 & 0 & 0 & 1 & 0 \\
    0 & 0 & 0 & 0 & 0 & 0 & 0 & 1 
    \end{pmatrix},~
    R = 
    \begin{pmatrix}
    1 & 1 & 0 & 0 & 0 & 0 & 0 & 0 \\
    0 & 1 & 0 & 0 & 0 & 0 & 0 & 0 \\
    0 & 0 & 1 & 1 & 0 & 1 & 1 & 0 \\
    0 & 0 & 0 & 1 & 0 & 0 & 1 & 0 \\
    0 & 0 & 0 & 0 & 1 & 0 & 0 & 1 \\
    0 & 0 & 0 & 0 & 0 & 1 & 0 & 0 \\
    0 & 0 & 0 & 0 & 0 & 0 & 1 & 0 \\
    0 & 0 & 0 & 0 & 0 & 0 & 0 & 1 
    \end{pmatrix}.
    $$
    
    The final answer is the last three components of the vector obtained by multiplying the initial state by the product of these operation matrices.
    
    This method has huge constants and cannot pass this problem. The details are given here only to assist understanding.
    
    **Contribution Combination**: The contribution of a segment of operation sequence is defined as $(x,y,\sum y,\sum xy,\sum y^2)$. The two operations are respectively:
    
    $$
    U = (0,1,0,0,0),~ R = (1,0,0,0,0).
    $$
    
    When combining contributions:
    
    $$
    \begin{aligned}
    \sum_{S_1+S_2} y 
    &= \sum_{S_1}y + \sum_{S_2}(y+y_1) = \sum_{S_1}y + \sum_{S_2}y + x_2y_1,\\
    \sum_{S_1+S_2} xy
    &= \sum_{S_1}xy + \sum_{S_2}(x+x_1)(y+y_1) \\
    &= \sum_{S_1}xy + \sum_{S_2}xy + x_1\sum_{S_2}y + y_1\sum_{S_2}x + x_1y_1\sum_{S_2}1\\
    &= \sum_{S_1}xy + \sum_{S_2}xy + x_1\sum_{S_2}y + \dfrac{1}{2}x_2(x_2+1)y_1 + x_1x_2y_1,\\
    \sum_{S_1+S_2}y^2
    &= \sum_{S_1}y^2 + \sum_{S_2}(y+y_1)^2 \\
    &= \sum_{S_1}y^2 + \sum_{S_2}y^2 + 2y_1\sum_{S_2}y + y_1^2\sum_{S_2}1  \\
    &= \sum_{S_1}y^2 + \sum_{S_2}y^2 + 2y_1\sum_{S_2}y + x_2y_1^2.
    \end{aligned}
    $$
    
    This shows that the multiplication of operations should be defined as:
    
    $$
    \begin{aligned}
    &(x_1,y_1,s_1,t_1,u_1)\cdot(x_2,y_2,s_2,t_2,u_2)\\
    &= (x_1+x_2,y_1+y_2,s_1+s_2+x_2y_1,\\
    &\qquad t_1+t_2+x_1s_2+(1/2)x_2(x_2+1)y_1+x_1x_2y_1,\\
    &\qquad u_1+u_2+2y_1s_2+x_2y_1^2).
    \end{aligned}
    $$
    
    Although direct verification is relatively cumbersome, the contribution vector defined above does form a monoid under this multiplication, and the identity element is $(0,0,0,0,0)$.
    
    For the general case:
    
    $$
    \begin{aligned}
    \sum_{S_1+S_2}x^ry^s &= \sum_{S_1}x^ry^s + \sum_{S_2}(x+x_1)^r(y+y_1)^s \\
    &= \sum_{S_1}x^ry^s + \sum_{i=0}^r\sum_{j=0}^s\binom{r}{i}\binom{s}{j}x_1^{r-i}y_1^{s-j}\sum_{S_2}x^iy^j.
    \end{aligned}
    $$
    
    As long as we maintain contributions of all lower powers, we can compute the sums of general cases.
    
    ```cpp
    --8<-- "docs/math/code/euclidean/euclidean-5.cpp"
    ```

???+ example "[Tsinghua Training 2014] Sum](https://www.luogu.com.cn/problem/P5172)"
    Multiple queries. Given positive integers $n$ and $r$, find:
    
    $$
    \sum_{d=1}^n(-1)^{\lfloor d\sqrt{r}\rfloor}.
    $$

??? note "Solution Two"
    First, handle the case where $r$ is a perfect square separately, which is completely consistent with the above and is omitted. Here, we only consider the case where $r$ is not a perfect square.
    
    There are many ways to apply the Universal Euclidean Algorithm to this problem. For example, we can define a linear transformation for each operation:
    
    $$
    U(x) = -x,~ R(x) = x + 1.
    $$
    
    The multiplication of operations is defined as the composition of linear transformations. Then the final answer is the value at $x=0$ of the function obtained by composing the transformations corresponding to the operation sequence.
    
    We can also define the contribution of each segment of the operation sequence. The contribution can be defined as $((-1)^y,\sum(-1)^y)$. Then the two operations are respectively:
    
    $$
    U = (0,-1),~ R = (1,1).
    $$
    
    The combination of contributions is defined as:
    
    $$
    (u_1,v_1)\cdot(u_2,v_2) = (u_1u_2,v_1+u_1v_2).
    $$
    
    It is easy to verify that under this multiplication, all operations form a monoid, and the identity element is $(0,1)$. The final answer is the second component of the product of all elements.
    
    These two methods are consistent, because if the linear transformation is written as $f(x)=u+vx$, then the change of coefficients corresponding to the composition of linear transformations is exactly the multiplication of operations above. That is, these two monoids are isomorphic.
    
    In this problem, the segment parameters are $(k,n)$, where $k\in\mathbf R$ is the slope of the line. Let the product of the operation sequence be $F(k,n,U,R)$. Then we have the following recursive algorithm:
    
    -   If $k\ge 1$, then in the operation sequence, each $R$ has at least $\lfloor k\rfloor$ $U$'s in front of it. Therefore:
    
        $$
        F(k,n,U,R) = F(k-\lfloor k\rfloor,n,U,U^{\lfloor k\rfloor} R).
        $$
    
    -   If $k<1$, then swap $U$ and $R$ in the operation sequence and discard the trailing $U$'s (i.e., the $R$'s before swapping). Therefore:
    
        $$
        F(k,n,U,R) = F(k^{-1},m,R,U)R^{n-\lfloor k^{-1}m\rfloor}.
        $$
    
    In this algorithm, the iteration process of $k$ is actually the continued fraction expansion of $\sqrt{r}$. For this, we can apply the [PQa Algorithm](./pell-equation.md#pqa-algorithm). The process of finding the continued fraction and the iteration process of the Universal Euclidean Algorithm can be done simultaneously.
    
    Consistent with the case of the Euclidean-like algorithm, the complexity of this algorithm is still $O(\log n)$.
    
    ```cpp
    --8<-- "docs/math/code/euclidean/euclidean-6.cpp"
    ```

## Practice Problems

Template problems:

-   [Library Checker - Sum of Floor of Linear](https://judge.yosupo.jp/problem/sum_of_floor_of_linear)
-   [Luogu P5170 Template: Euclidean-like Algorithm](https://www.luogu.com.cn/problem/P5170)
-   [Luogu P5171 Earthquake](https://www.luogu.com.cn/problem/P5171)
-   [Luogu P5172 [Tsinghua Training 2014] Sum](https://www.luogu.com.cn/problem/P5172)
-   [Luogu P4132 [BJOI2012] Unsolvable Equation](https://www.luogu.com.cn/problem/P4132)
-   [LOJ 138. Euclidean-like Algorithm](https://loj.ac/p/138)
-   [LOJ 6440. Universal Euclidean](https://loj.ac/p/6440)
-   [Luogu P5179 Fraction](https://www.luogu.com.cn/problem/P5179)
-   [Codeforces 1182 F. Maximum Sine](https://codeforces.com/problemset/problem/1182/F)

Application problems:

-   [Luogu P4433 [COCI 2009/2010 #1] ALADIN](https://www.luogu.com.cn/problem/P4433)
-   [AtCoder Beginner Contest 372 G - Ax + By < C](https://atcoder.jp/contests/abc372/tasks/abc372_g)
-   [AtCoder Beginner Contest 313 G - Redistribution of Piles](https://atcoder.jp/contests/abc313/tasks/abc313_g)
-   [AtCoder Beginner Contest 283 Ex - Popcount Sum](https://atcoder.jp/contests/abc283/tasks/abc283_h)
-   [Codeforces 1098 E. Fedya the Potter](https://codeforces.com/problemset/problem/1098/E)
-   [Codeforces 868 G. El Toll Caves](https://codeforces.com/problemset/problem/868/G)

## References and Notes

[^complexity]: In problems usually considered, $b$ is of the same order as $a$, and $O(\log(b/c))$ can be ignored. Moreover, if before calling the Universal Euclidean Algorithm, we first perform a round of modulo reduction in the Euclidean-like algorithm to eliminate the impact of $b$, the complexity of fast exponentiation of this term can be avoided. This is because in usual problems, the initial form of $U$ is relatively special, and its powers have simpler forms and do not need to be calculated by fast exponentiation. For example, in the main text, the result of $U^{\lfloor b/a\rfloor}$ is obtained by replacing the $1$ not on the diagonal in $U$ with $\lfloor b/a\rfloor$, without using fast exponentiation.
