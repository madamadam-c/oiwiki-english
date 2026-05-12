Divisor block (also known as integer division block or floor division block) can quickly compute sums of the form

$$
\sum_{i=1}^nf(i)g\left(\left\lfloor\dfrac ni\right\rfloor\right)
$$

If $\sum_{i=l}^{r}f(i)$ can be computed in $O(1)$ time or the prefix sums of $f$ are already precomputed, then divisor block can compute the above sum in $O(\sqrt{n})$ time.

Divisor block is often used in conjunction with techniques like [Möbius inversion](./mobius.md).

## Idea

First, this article illustrates the idea of divisor block through a simple example. Suppose we need to count the number of integer points under the hyperbola shown in the figure:

![Integer points under hyperbola](./images/sqrt-decomposition.svg)

This is equivalent to computing the sum:

$$
\sum_{i=1}^{11}\left\lfloor\dfrac{11}{i}\right\rfloor.
$$

This is a special case of the previously shown sum when $f(k)=1$ and $g(k)=k$.

The simplest approach is to calculate each column one by one and sum them, but this requires calculating the number of integer points in each column for $i=1,2,\cdots,11$. Observing the figure, we can see that these columns can be divided into 5 blocks, and within each block, the column height is consistent, forming a rectangular point pattern. Therefore, as long as we know the width of these blocks, we can quickly complete the count by calculating the size of these rectangular blocks.

This is the basic idea of divisor block.

## Properties

This section discusses several conclusions about the blocks of integer points under the hyperbola $y = \dfrac{n}{x}$. Specifically, we need to divide the integers between $1$ and $n$ into several blocks based on the value of $\left\lfloor\dfrac{n}{i}\right\rfloor$. Let

$$
D(n) = \left\{\left\lfloor\dfrac{n}{i}\right\rfloor : 1 \le i \le n,~i\in\mathbf N_+\right\}.
$$

This is the set of all possible values of $\left\lfloor\dfrac{n}{i}\right\rfloor$.

First, there are only $O(\sqrt{n})$ different values. Therefore, the number of blocks obtained by divisor block is only $O(\sqrt{n})$.

???+ note "Property 1"
    $|D(n)|\le 2\sqrt{n}$.

??? note "Proof"
    Consider two cases:
    
    - When $i\le\sqrt{n}$, there are at most $\sqrt{n}$ possible values for $i$, so there are also at most $\sqrt{n}$ possible values for $\left\lfloor\dfrac{n}{i}\right\rfloor$.
    - When $i>\sqrt{n}$, $\left\lfloor\dfrac{n}{i}\right\rfloor \le\dfrac{n}{i} < \sqrt{n}$, which also has at most $\sqrt{n}$ possible values.
    
    Therefore, the total number of possible values $|D(n)|\le 2\sqrt{n}$.

Through more detailed analysis, the set $D(n)$ and its size can actually be precisely described.

???+ note "Property 2"
    Let $s = \lfloor\sqrt{n}\rfloor$. The elements of set $D(n)$ in ascending order are:
    
    $$
    1 < 2 < \cdots < s-1 < s \le \left\lfloor\dfrac{n}{s}\right\rfloor < \left\lfloor\dfrac{n}{s-1}\right\rfloor < \cdots < \left\lfloor\dfrac{n}{2}\right\rfloor < \left\lfloor\dfrac{n}{1}\right\rfloor = n.
    $$
    
    Moreover, $|D(n)| = \lfloor \sqrt{4n+1}\rfloor - 1$.

??? note "Proof"
    First, for $1 \le i \le s$, we can prove that $\left\lfloor\dfrac{n}{\lfloor n/i\rfloor}\right\rfloor = i$. Let $d = \left\lfloor\dfrac{n}{i}\right\rfloor$, and we need to prove $\left\lfloor\dfrac{n}{d}\right\rfloor = i$. Written as an inequality, this is equivalent to knowing $d \le \dfrac{n}{i} < d + 1$, and we need to prove $i \le \dfrac{n}{d} < i + 1$. The known condition can be written as $i\le\dfrac{n}{d} < i + \dfrac{i}{d}$, so we only need to prove $\dfrac{i}{d} \le 1$, i.e., $i \le d = \left\lfloor\dfrac{n}{i}\right\rfloor$. This is equivalent to $i \le \dfrac{n}{i}$, which holds for all $1 \le i \le s \le \sqrt{n}$.
    
    This result actually shows that the mapping $i \mapsto \left\lfloor\dfrac{n}{i}\right\rfloor$ forms a bijection between the set $\{i:1\le i \le s\}$ and the set $\left\{\left\lfloor\dfrac{n}{i}\right\rfloor: 1\le i\le s\right\}$. Since $i$ values are distinct, $\left\lfloor\dfrac{n}{i}\right\rfloor$ values are also distinct. The only element that could possibly be the same in the two sets is $s$ and $\left\lfloor\dfrac{n}{s}\right\rfloor$. Therefore, $|D(n)|=2s - \left[s = \lfloor n/s\rfloor\right]$.
    
    To obtain the final expression for $|D(n)|$, we need to examine when $s = \left\lfloor\dfrac{n}{s}\right\rfloor$ holds.
    
    - When $s = \left\lfloor\dfrac{n}{s}\right\rfloor$, we always have $s \le \dfrac{n}{s} < s + 1$, i.e., $s^2 \le n < s^2+s$. Then, $4s^2 + 1 \le 4n + 1 < 4s^2+4s+1 = (2s+1)^2$. Also, since $4n+1$ is always odd, the left side can be equivalently relaxed to $4s^2$. So this condition is equivalent to $2s \le \sqrt{4n+1} < 2s+1$, i.e., $\lfloor \sqrt{4n+1}\rfloor = 2s$.
    - When $s < \left\lfloor\dfrac{n}{s}\right\rfloor$, we always have $s + 1 \le \dfrac{n}{s}$, i.e., $s^2 + s\le n$. And since $n < (s+1)^2$, we have $s^2 + s\le n < (s+1)^2$. This is equivalent to $(2s+1)^2\le 4n+1 < 4(s+1)^2+1$. Using again that $4n+1$ is odd, the right side can be equivalently tightened to $4(s+1)^2$. So this condition is equivalent to $2s+1\le\sqrt{4n+1} < 2s+2$, i.e., $\lfloor \sqrt{4n+1}\rfloor = 2s+1$.
    
    Summarizing these two cases, we get $|D(n)| = \lfloor \sqrt{4n+1}\rfloor - 1$.

Then, the left and right endpoints of a single block are easy to determine.

???+ note "Property 3"
    For $d\in D(n)$, the range of all integers $i$ satisfying $\left\lfloor\dfrac{n}{i}\right\rfloor=d$ is:
    
    $$
    \left\lfloor\dfrac{n}{d+1}\right\rfloor + 1\le i \le \left\lfloor\dfrac{n}{d}\right\rfloor.
    $$

??? note "Proof"
    Since $\left\lfloor\dfrac{n}{i}\right\rfloor=d$ is equivalent to the inequality:
    
    $$
    d\le \dfrac{n}{i} < d+1.
    $$
    
    This is further equivalent to:
    
    $$
    \dfrac{n}{d+1} < i\le \dfrac{n}{d}.
    $$
    
    Using the fact that $i\in\mathbf N_+$, taking the floor of this inequality gives:
    
    $$
    \left\lfloor\dfrac{n}{d+1}\right\rfloor + 1 \le i\le \left\lfloor\dfrac{n}{d}\right\rfloor.
    $$

This property also reflects the symmetry of the graph: the set of right endpoints of each block (the green points in the figure) is exactly $D(n)$. This is easy to understand because the entire graph is symmetric about the line $y=x$.

In addition to these properties, the set $D(n)$ also has good recursive properties:

???+ note "Property 4"
    For $m\in D(n)$, we have $D(m)\subseteq D(n)$.

??? note "Proof"
    Let $m = \left\lfloor\dfrac{n}{k}\right\rfloor$. Then, since for all $i\in\mathbf N_+$, we have:
    
    $$
    \left\lfloor\dfrac{m}{i}\right\rfloor = \left\lfloor\dfrac{\lfloor n/k\rfloor}{i}\right\rfloor = \left\lfloor\dfrac{n}{ki}\right\rfloor \in D(n),
    $$
    
    so $D(m)\subseteq D(n)$. The second equality uses the property of the [floor function](./basic.md#取整函数) for nested fractions.

As mentioned earlier, $D(n)$ is both the set of values of $\left\.floor\dfrac{n}{i}\right\rfloor$ within each block and the set of right endpoints of blocks. This means that if we recursively apply divisor block (i.e., the function's value at $n$ depends on its values at $m\in D(n)\setminus\{n\}$), then the set of values and right endpoints involved in the entire computation are actually all in $D(n)$. A typical example is the [Du Jiao Sieve](./du.md).

## Process

Using the conclusions described in the previous section, we obtain the specific process of divisor block.

To compute the value of the sum

$$
\sum_{i=1}^nf(i)g\left(\left\lfloor\dfrac ni\right\rfloor\right)
$$

we can divide the indices $i=1,2,\cdots,n$ into blocks based on the value of $\left\lfloor\dfrac ni\right\rfloor$. Since indices with the same value of $\left\lfloor\dfrac ni\right\rfloor$ form a continuous integer interval $[l,r]$, the value of the sum for this block is:

$$
\left(\sum_{i=l}^rf(i)\right)\cdot g\left(\left\lfloor\dfrac nl\right\rfloor\right).
$$

To quickly compute this sum, we usually need to be able to quickly compute the sum of $f$ on the left side. Sometimes, the expression of this sum is known and can be computed in $O(1)$ time; sometimes, we can precompute its prefix sums, still allowing $O(1)$ time for a single query.

When sequentially calculating the left and right endpoints of each block, the left endpoint $l$ of the current block equals the right endpoint of the previous block plus 1, and the right endpoint of the current block equals $\left\lfloor\dfrac n{\lfloor n/l\rfloor}\right\rfloor$. From this, we get the following pseudocode:

$$
\begin{array}{l}
\textbf{Algorithm }\text{Sum}(f,g,n):\\
\textbf{Input. }n,~s(k)=\sum_{i=1}^kf(k),~g(k).\\
\textbf{Output. }S(n) = \sum_{i=1}^nf(i)g(\lfloor n/i\rfloor).\\
\textbf{Method.}\\
\begin{array}{ll}
1 & l \gets 1\\
2 & \textit{result} \gets 0 \\
3 & \textbf{while } l \leq n \textbf{ do}\\
4 & \qquad r \gets \left\lfloor \dfrac{n}{\lfloor n/l \rfloor} \right\rfloor\\
5 & \qquad \textit{result} \gets \textit{result} + (s(r)-s(l-1))\cdot g\left(\left\lfloor \dfrac{n}{l} \right\rfloor\right)\\
6 & \qquad l \gets r+1\\
7 & \textbf{end while}\\
8 & \textbf{return }\textit{result}
\end{array}
\end{array}
$$

Assuming the time complexity of a single computation of $s(\cdot)$ is $O(1)$, the overall time complexity is $O(\sqrt{n})$.

## Extensions

The previous section discussed the most common and basic form of divisor block. This section further discusses extended forms of divisor block.

### Ceiling Division Block

Divisor block can be used to compute sums involving ceiling division:

$$
\sum_{i=1}^nf(i)g\left(\left\lceil\dfrac ni\right\rceil\right).
$$

Since $\left\lceil\dfrac ni\right\rceil = \left\lfloor\dfrac {n-1}i\right\rfloor + 1$, this sum can be transformed into the floor division case:

$$
f(n)g(1) + \sum_{i=1}^{n-1}f(i)g\left(\left\lfloor\dfrac {n-1}i\right\rfloor + 1\right).
$$

Note that the upper limit of the summation has changed, and there is a separate term when $i=n$.

### Multi-dimensional Divisor Block

Divisor block can also handle sums with more than one division expression:

$$
\sum_{i=1}^{n}f(i)g\left(\left\lfloor\dfrac {n_1}i\right\rfloor,\left\lfloor\dfrac {n_2}i\right\rfloor,\cdots,\left\lfloor\dfrac {n_m}i\right\rfloor\right).
$$

To apply the idea of divisor block, we need to ensure that within each block, all division expressions $\left\lfloor\dfrac {n_1}i\right\rfloor,\left\lfloor\dfrac {n_2}i\right\rfloor,\cdots,\left\lfloor\dfrac {n_m}i\right\rfloor$ have constant values; that is, the multi-dimensional blocks should be the intersection of all one-dimensional blocks. Therefore, for a known left endpoint $l$, the corresponding right endpoint is:

$$
\min\left\{\left\lfloor\dfrac {n_1}{\lfloor n_1/l\rfloor}\right\rfloor,\left\lfloor\dfrac {n_2}{\lfloor n_2/l\rfloor}\right\rfloor,\cdots,\left\lfloor\dfrac {n_m}{\lfloor n_m/l\rfloor}\right\rfloor\right\}.
$$

In other words, we take the minimum of the right endpoints of all one-dimensional blocks as the right endpoint of the multi-dimensional block. This can be understood with the following figure:

![Multi-dimensional divisor block illustration](./images/n-dimension-sqrt-decomposition.svg)

The two-dimensional case is more common. In this case, the pseudocode's $r \gets \left\lfloor \dfrac{n}{\lfloor n/l \rfloor}\right\rfloor$ can be replaced with:

$$
r \gets \min\left\{\left\lfloor \dfrac{n_1}{\lfloor n_1/l \rfloor}\right\rfloor,\left\lfloor \dfrac{n_2}{\lfloor n_2/l \rfloor}\right\rfloor\right\}.
$$

### Arbitrary Exponent Divisor Block

Divisor block can be used to compute sums with arbitrary exponent division expressions:

$$
\sum_{i=1}^{\lfloor n^{\alpha/\beta}\rfloor}f(i)g\left(\left\lfloor\dfrac {n^\alpha}{i^\beta}\right\rfloor\right).
$$

Here, $\alpha$ and $\beta$ are positive real numbers. In the basic form discussed in this article, $\alpha=\beta=1$.

???+ note "Property"
    For positive integer $n$ and positive real numbers $\alpha, \beta$, let:
    
    $$
    D(n,\alpha,\beta) = \left\{\left\lfloor\dfrac{n^\alpha}{i^\beta}\right\rfloor: i=1,2,\cdots,\lfloor n^{\alpha/\beta}\rfloor\right\}.
    $$
    
    Then we have:
    
    1. $|D(n,\alpha,\beta)|\le 2n^{\alpha/(1+\beta)}$.
    2. For $d\in D(n,\alpha,\beta)$, the range of $i$ such that $\left\lfloor\dfrac{n^\alpha}{i^\beta}\right\rfloor=d$ is:
    
        $$
        \left\lfloor\dfrac{n^{\alpha/\beta}}{(d+1)^{1/\beta}}\right\rfloor + 1\le i \le \left\lfloor\dfrac{n^{\alpha/\beta}}{d^{1/\beta}}\right\rfloor.
        $$

??? note "Proof"
    For the first point, consider two cases:
    
    - When $i\le \dfrac{n^\alpha}{i^\beta}$, we have $i\le n^{\alpha/(1+\beta)}$, so $\left\lfloor\dfrac{n^\alpha}{i^\beta}\right\rfloor$ has at most $n^{\alpha/(1+\beta)}$ possible values.
    - When $i > \dfrac{n^\alpha}{i^\beta}$, we have $i> n^{\alpha/(1+\beta)}$, and then $\dfrac{n^\alpha}{i^\beta} < n^{\alpha/(1+\beta)}$, so $\left\lfloor\dfrac{n^\alpha}{i^\beta}\right\rfloor$ also has at most $n^{\alpha/(1+\beta)}$ possible values.
    
    Combining both cases, we have $|D(n,\alpha,\beta)|\le 2n^{\alpha/(1+\beta)}$.
    
    For the second point, $\left\lfloor\dfrac{n^\alpha}{i^\beta}\right\rfloor=d$ is equivalent to:
    
    $$
    d \le \dfrac{n^\alpha}{i^\beta} < d+1 \iff \dfrac{n^{\alpha/\beta}}{(d+1)^{1/\beta}} < i \le \dfrac{n^{\alpha/\beta}}{d^{1/\beta}}.
    $$
    
    Taking the floor of this inequality gives the second proposition.

Using these properties, arbitrary exponent divisor block can be implemented with time complexity $O(n^{\alpha/(1+\beta)})$.

???+ example "Example"
    For example, for the following sum when $\alpha=\beta=1/2$:
    
    $$
    \sum_{i=1}^nf(i)g\left(\left\lfloor\sqrt{\dfrac {n}{i}}\right\rfloor\right),
    $$
    
    it can be solved in $O(n^{1/3})$ time using divisor block. Given the left endpoint $l$ of a known block, the right endpoint can be calculated as $r=\left\lfloor\dfrac{n}{\lfloor\sqrt{n/l}\rfloor^2}\right\rfloor$.

## Example Problems

???+ example "[UVa11526 H(n)](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2521)"
    $T$ test cases, each with an integer $n$. For each test case, output $\sum_{i=1}^n\left\lfloor\dfrac ni\right\rfloor$.

??? note "Solution"
    According to the previous analysis, we can compute together for each block with the same $\left\lfloor\dfrac ni\right\rfloor$. The time complexity is $O(T\sqrt n)$.

??? note "Implementation"
    ```cpp
    --8<-- "docs/math/code/sqrt-decomposition/sqrt-decomposition_1.cpp"
    ```

???+ example "[Codeforces 1954E Chain Reaction](https://codeforces.com/contest/1954/problem/E)"
    There are $n$ monsters in a line, each with initial health $a_i$. An attack reduces the health of a consecutive segment of surviving monsters by $k$, and monsters with health $\le 0$ are considered dead. For all $k$, find the number of attacks needed to kill all monsters. Here $n,a_i\leq 10^5$.

??? note "Solution"
    Let $a_0=0$. Suppose killing all the first $(i-1)$ monsters requires $T(k,i-1)$ attacks, and the health of the $i$-th monster is $a_i$. Since when killing the $(i-1)$-th monster, it requires $\lceil a_{i-1}/k\rceil$ attacks, and these attacks can all extend to the $i$-th monster. Therefore, to kill the $i$-th monster, we only need $\max\{0,\lceil a_i/k\rceil-\lceil a_{i-1}/k\rceil\}$ more attacks. Thus, the total number of attacks is:
    
    $$
    T(k,n)=\sum_{i=1}^n\max\left(0,\left\lceil\dfrac{a_i}{k}\right\rceil-\left\lceil\dfrac{a_{i-1}}{k}\right\rceil\right).
    $$
    
    Since both $n$ and $k$ are large in this problem, computing this sum for each $k$ separately is not feasible. We can consider maintaining the sequence $\{T(k,i)\}_k$ for each $i=1,2,\cdots,n$. Initially, set $T(k,0)\equiv 0$. Assuming the sequence $\{T(k,i-1)\}_k$ is known, consider how to modify it to obtain $\{T(k,i)\}_k$. According to the previous analysis, we only need to add $\max\left(0,\left\lceil\dfrac{a_i}{k}\right\rceil-\left\lceil\dfrac{a_{i-1}}{k}\right\rceil\right)$ to the $k$-th term of the sequence. Using two-dimensional divisor block, this modification operation can be split into $O(\sqrt{a_{i-1}}+\sqrt{a_i})$ segment modification operations, and the value added on each segment is constant. The final sequence $\{T(k,n)\}_k$ is the answer.
    
    Since the problem involves a series of range addition operations, and queries only occur after all modifications are completed, we can maintain the difference sequence for range addition operations, and finally obtain the desired sequence through prefix sums. The total time complexity is $O(\sum\sqrt{a_i})$. There are other solutions to this problem as well.

??? note "Implementation"
    ```cpp
    --8<-- "docs/math/code/sqrt-decomposition/sqrt-decomposition_2.cpp"
    ```

## Practice Problems

-   [UVa11526 H(n)](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2521)
-   [Luogu P2261 CQOI2007 Remainder Sum](https://www.luogu.com.cn/problem/P2261)
-   [Luogu P3455 POI2007 ZAP-Queries](https://www.luogu.com.cn/problem/P3455)

## References

-   [Du Jiao Sieve time and space complexity analysis by riteme](https://riteme.site/blog/2018-9-11/time-space-complexity-dyh-algo.html)