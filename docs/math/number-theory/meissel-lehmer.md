author: Peanut-Tang, Early0v0, Vxlimo, GHLinZhengyu, 1196131597

The **Meissel-Lehmer algorithm** is an algorithm that can compute the number of primes between $1$ and $n$ in sub-linear time complexity.

## Notation

$\left[x\right]$ denotes the result of rounding down $x$.  
$p_k$ denotes the $k$-th prime, with $p_1=2$.  
$\pi\left(x\right)$ denotes the number of primes in the range $1\sim x$.  
$\mu\left(x\right)$ denotes the Möbius function.  
For a set $S$, $\# S$ denotes the size of set $S$.  
$\delta\left(x\right)$ denotes the smallest prime factor of $x$.  
$P^+\left(x\right)$ denotes the largest prime factor of $x$.

## Meissel-Lehmer Algorithm for Computing $\pi(x)$

Define $\phi\left(x,a\right)$ as the number of positive integers less than $x$ such that all their prime factors are greater than $p_a$, i.e.:

$$
\phi\left(x,a\right)=\#\big\{n\le x\mid n\bmod p=0 \implies p>p_a\big\}\tag{1}
$$

Define $P_k\left(x,a\right)$ as the number of positive integers less than $x$ that have exactly $k$ prime factors (with multiplicity) and all prime factors are greater than $p_a$, i.e.:

$$
P_k\left(x,a\right)=\#\big\{n\le x\mid n=q_1q_2\cdots q_k \implies \forall i,q_i>p_a\big\}\tag{2}
$$

In particular, we define: $P_0\left(x,a\right)=1$, so we have:

$$
\phi\left(x,a\right)=P_0\left(x,a\right)+P_1\left(x,a\right)+\cdots+P_k\left(x,a\right)+\cdots
$$

This infinite sum can actually be expressed as a finite sum, because when $p_a^k>x$, we have $P_k\left(x,a\right)=0$.

Let $y$ be an integer satisfying $x^{1/3}\le y\le x^{1/2}$, and let $a=\pi\left(y\right)$.

When $k\ge 3$, we have $P_1\left(x,a\right)=\pi\left(x\right)-a$ and $P_k\left(x,a\right)=0$, from which we can derive:

$$
\pi\left(x\right)=\phi\left(x,a\right)+a-1-P_2\left(x,a\right)\tag{3}
$$

Thus, computing $\pi\left(x\right)$ can be reduced to computing $\phi\left(x,a\right)$ and $P_2\left(x,a\right)$.

## Computing $P_2(x,a)$

From equation $(2)$, we can derive that $P_2\left(x,a\right)$ equals the number of prime pairs $(p,q)$ satisfying $y<p\le q$ and $pq\le x$.

First, we note that $p\in \left[y+1,\sqrt{x}\right]$. Moreover, for each $p$, we have $q\in\left[p,x/p\right]$. Therefore:

$$
P_2\left(x,a\right)=\sum_{y<p\le \sqrt{x}}{\left(\pi\left(\dfrac{x}{p}\right)-\pi\left(p\right)+1\right)}\tag{4}
$$

When $p\in \left[y+1,\sqrt{x}\right]$, we have $\dfrac{x}{p}\in \left[1,\dfrac{x}{y}\right]$. Therefore, we can sieve the interval $\left[1,\dfrac{x}{y}\right]$, and then compute $\pi\left(\dfrac{x}{p}\right)-\pi\left(p\right)+1$ for all primes $p\in \left[y+1,\sqrt{x}\right]$. To reduce the space complexity of the above algorithm, we can consider block sieving with block length $L$. If the block length $L=y$, we can compute $P_2\left(x,a\right)$ in $O\left(\dfrac{x}{y}\log{\log{x}}\right)$ time complexity and $O\left(y\right)$ space complexity.

## Computing $\phi(x,a)$

For $b\le a$, consider all positive integers not exceeding $x$ such that all their prime factors are greater than $p_{b-1}$. These numbers can be divided into two categories:

1.  Divisible by $p_b$;
2.  Not divisible by $p_b$.

The number of numbers in the first category is $\phi\left(\dfrac{x}{p_b},b-1\right)$, and the number in the second category is $\phi\left(x,b\right)$.

Therefore, we conclude:

> **Theorem 5.1:** The function $\phi$ satisfies the following properties
>
> $$
> \phi\left(u,0\right)=\left[u\right]\tag{5}
> $$
>
> $$
> \phi\left(x,b\right)=\phi\left(x,b-1\right)-\phi\left(\dfrac{x}{p_b},b-1\right)\tag{6}
> $$

A simple method for computing $\phi\left(x,a\right)$ can be derived from this theorem: we repeatedly use equation $(7)$ until we finally get $\phi\left(u,0\right)$. This process can be viewed as creating a rooted binary tree starting from the root node $\phi\left(x,a\right)$. Figure 1 illustrates this process. Using this method, we obtain the following formula:

$$
\phi\left(x,a\right)=\sum_{\substack{1\le n\le x\\ P^+\left(n\right)\le y}}{\mu\left(n\right)\left[x/n\right]}
$$

$$
\begin{gathered}
\begin{matrix}&&\phi\left(x,a\right)&&\\
&\swarrow&&\searrow&\\
&\phi\left(x,a-1\right)&&-\phi\left(\frac{x}{p_a},a-1\right)&\\
\swarrow&\downarrow&&\downarrow&\searrow\\
\phi\left(x,a-2\right)&\phi\left(\frac{x}{p_{a-1}},a-2\right)&&-\phi\left(\frac{x}{p_a},a-2\right)&\phi\left(\frac{x}{p_ap_{a-1}},a-2\right)\end{matrix}\\
\vdots\\
\end{gathered}
$$

The figure above shows the binary tree for computing $\phi\left(x,a\right)$: the sum of the weights of leaf nodes is $\phi\left(x,a\right)$.

However, this requires computing too many things. Because $y\geq x^{1/3}$, simply computing the numbers that are products of at most $3$ primes not exceeding $y$ would have at least $\dfrac{x}{\log^3 x}$ terms using this method, which cannot meet our complexity requirements.

To limit the "growth" of this binary tree, we need to change the original termination condition. This is the original termination condition.

> **Termination condition 1:** If $b=0$, do not apply equation $(6)$ to the node $\mu\left(n\right)\phi\left(\dfrac xn,b\right)$.

We change it to a stronger termination condition:

> **Termination condition 2:** If either of the following 2 conditions is satisfied, do not apply equation $(6)$ to the node $\mu\left(n\right)\phi\left(\dfrac xn,b\right)$:
>
> 1.  $b=0$ and $n\le y$;
> 2.  $n>y$.

We classify the leaves on the original binary tree according to **Termination condition 2** into two types:

1.  If the leaf node $\mu\left(n\right)\phi\left(\dfrac xn,b\right)$ satisfies $n\le y$, we call such leaves **ordinary leaves**;
2.  If the leaf node $\mu\left(n\right)\phi\left(\dfrac xn,b\right)$ satisfies $n>y$ and $n=mp_b\left(m\le y\right)$, we call such nodes **special leaves**.

From this we conclude:

> **Theorem 5.2:** We have:
>
> $$
> \phi\left(x,a\right)=S_0+S\tag{7}
> $$
>
> where $S_0$ represents the contribution of **ordinary leaves**:
>
> $$
> S_0=\sum_{n\le y}{\mu\left(n\right)\left[\dfrac xn\right]}\tag{8}
> $$
>
> $S$ represents the contribution of **special leaves**:
>
> $$
> S=\sum_{n/\delta\left(n\right)\le y\le n}{\mu\left(n\right)\phi\left(\dfrac{x}{n},\pi\left(\delta\left(n\right)\right)-1 \right)}\tag{9}
> $$

Computing $S_0$ can obviously be solved in $O\left(y\log{\log x}\right)$ time complexity. Now we need to consider how to compute $S$.

## Computing $S$

We have:

$$
S=-\sum_{p\le y}{\ \sum_{\substack{\delta\left(m\right)>p\\ m\le y<mp}}{\mu\left(m\right)\phi\left(\dfrac{x}{mp},\pi\left(p\right)-1\right)}}\tag{10}
$$

We rewrite this equation as:

$$
S=S_1+S_2+S_3
$$

where:

$$
S_1=-\sum_{x^{1/3}<p\le y}{\ \sum_{\substack{\delta\left(m\right)>p\\ m\le y<mp}}{\mu\left(m\right)\phi\left(\dfrac{x}{mp},\pi\left(p\right)-1\right)}}
$$

$$
S_2=-\sum_{x^{1/4}<p\le x^{1/3}}{\ \sum_{\substack{\delta\left(m\right)>p\\ m\le y<mp}}{\mu\left(m\right)\phi\left(\dfrac{x}{mp},\pi\left(p\right)-1\right)}}
$$

$$
S_3=-\sum_{p\le x^{1/4}}{\ \sum_{\substack{\delta\left(m\right)>p\\ m\le y<mp}}{\mu\left(m\right)\phi\left(\dfrac{x}{mp},\pi\left(p\right)-1\right)}}
$$

Note that the $m$ involved in the summations for computing $S_1$ and $S_2$ are all primes. The proof is as follows:

> If this were not the case, since $\delta\left(m\right)>p>x^{1/4}$, we would have $m>p^2>\sqrt{x}$, which contradicts $m\le y$. Therefore, the original proposition holds.

Furthermore, when $mp>x^{1/2}\ge y$, we have $y\le mp$. Therefore, we have:

$$
S_1=\sum_{x^{1/3}<p\le y}{\ \sum_{p<q\le y}{\phi\left(\dfrac{x}{pq},\pi\left(p\right)-1\right)}}
$$

$$
S_2=\sum_{x^{1/4}<p\le x^{1/3}}{\ \sum_{p<q\le y}{\phi\left(\dfrac{x}{pq},\pi\left(p\right)-1\right)}}
$$

### Computing $S_1$

Since:

$$
\dfrac{x}{pq}<x^{1/3}<p
$$

we have:

$$
\phi\left(\dfrac{x}{pq},\pi\left(p\right)-1\right)=1
$$

Therefore, all terms in the summation for computing $S_1$ are $1$. So we actually need to count the number of prime pairs $(p,q)$ satisfying: $x^{1/3}<p<q\le y$.

Therefore:

$$
S_1=\dfrac{\left(\pi\left(y\right)-\pi\left(x^{1/3}\right)\right)\left(\pi\left(y\right)-\pi\left(x^{1/3}\right)-1\right)}{2}
$$

With this equation, we can compute $S_1$ in $O\left(1\right)$ time.

### Computing $S_2$

We have:

$$
S_2=\sum_{x^{1/4}<p\le x^{1/3}}{\ \sum_{p<q\le y}{\phi\left(\dfrac{x}{pq},\pi\left(p\right)-1\right)}}
$$

We divide $S_2$ into two parts: $q>\dfrac x{p^2}$ and $q\le \dfrac x{p^2}$:

$$
S_2=U+V
$$

where:

$$
U=\sum_{x^{1/4}<p\le x^{1/3}}{\ \sum_{\substack{p<q<y\\q>x/p^2}}{\phi\left(\dfrac{x}{pq},\pi\left(p\right)-1 \right)}}
$$

$$
V=\sum_{x^{1/4}<p\le x^{1/3}}{\ \sum_{\substack{p<q<y\\q\le x/p^2}}{\phi\left(\dfrac{x}{pq},\pi\left(p\right)-1 \right)}}
$$

### Computing $U$

From $q>\dfrac x{p^2}$, we get $p^2>\dfrac xq\le \dfrac xy,p>\sqrt{\dfrac xy}$, therefore:

$$
U=\sum_{\sqrt{x/y}<p\le x^{1/3}}{\ \sum_{\substack{p<q\le y\\q>x/p^2}}{\phi\left(\dfrac{x}{pq},\pi\left(p\right)-1 \right)}}
$$

Therefore:

$$
U=\sum_{\sqrt{x/y}<p\le x^{1/3}}{\#\left\{q\mid \dfrac x{p^2}<q\le y \right\}}
$$

Therefore:

$$
U=\sum_{\sqrt{x/y}<p\le x^{1/3}}{\left(\pi\left(y\right)-\pi\left(\dfrac{x}{p^2} \right) \right)}
$$

Since $\dfrac x{p^2}<y$, we can precompute all $\pi\left(t\right)\left(t\le y\right)$, so we can compute $U$ in $O\left(y\right)$ time complexity.

### Computing $V$

For each term in the summation for computing $V$, we have $p\le \dfrac{x}{pq}<x^{1/2}<p^2$. Therefore:

$$
\phi\left(\dfrac{x}{pq},\pi\left(p\right)-1 \right)=1+\pi\left(\dfrac{x}{pq} \right)-\left(\pi\left(p\right)-1\right)=2-\pi\left(p\right)+\pi\left(\dfrac{x}{pq} \right)
$$

Therefore, $V$ can be expressed as:

$$
V=V_1+V_2
$$

where:

$$
V_1=\sum_{x^{1/4}<p\le x^{1/3}}{\ \sum_{p<q\le \min\left(x/p^2,y\right)}{\left(2-\pi\left(p\right)\right)}}
$$

$$
V_2=\sum_{x^{1/4}<p\le x^{1/3}}{\ \sum_{p<q\le \min\left(x/p^2,y\right)}{\pi\left(\dfrac{x}{pq} \right)}}
$$

After precomputing $\pi\left(t\right)\left(t\le y\right)$, we can compute $V_1$ in $O\left(x^{1/3}\right)$ time complexity.

Consider how to speed up the computation of $V_2$. We can break the contribution of $q$ into several intervals where $\pi\left(\dfrac{x}{pq} \right)$ is constant, so we only need to compute the length of each interval and the change of $\pi\left(\dfrac{x}{pq} \right)$ from one interval to the next.

More precisely, we first split $V_2$ into two parts, simplifying the complex condition $q\le \min\left(\dfrac x{p^2},y\right)$:

$$
V_2=\sum_{x^{1/4}<p\le \sqrt{x/y}}{\ \sum_{p<q\le y}{\pi\left(\dfrac{x}{pq} \right)}}+\sum_{\sqrt{x/y}<p\le x^{1/3}}{\ \sum_{p<q\le x/p^2}{\pi\left(\dfrac{x}{pq} \right)}}
$$

Then we rewrite this expression as:

$$
V_2=W_1+W_2+W_3+W_4+W_5
$$

where:

$$
W_1=\sum_{x^{1/4}<p\le x/y^2}{\ \sum_{p<q\le y}{\pi\left(\dfrac{x}{pq} \right)}}
$$

$$
W_2=\sum_{x/y^2<p\le \sqrt{x/y}}{\ \sum_{p<q\le \sqrt{x/p}}{\pi\left(\dfrac{x}{pq} \right)}}
$$

$$
W_3=\sum_{x/y^2<p\le \sqrt{x/y}}{\ \sum_{\sqrt{x/p}<q\le y}{\pi\left(\dfrac{x}{pq} \right)}}
$$

$$
W_4=\sum_{\sqrt{x/y}<p\le x^{1/3}}{\ \sum_{p<q\le \sqrt{x/p}}{\pi\left(\dfrac{x}{pq} \right)}}
$$

$$
W_5=\sum_{\sqrt{x/y}<p\le x^{1/3}}{\ \sum_{\sqrt{x/p}<q\le x/p^2}{\pi\left(\dfrac{x}{pq} \right)}}
$$

#### Computing $W_1$ and $W_2$

To compute these two values, we need to compute $\pi\left(\dfrac{x}{pq} \right)$ for $y<\dfrac{x}{pq}<x^{1/2}$. This can be done by block sieving in the interval $[1,\sqrt x]$. In each block, we sum $\pi\left(\dfrac x{pq}\right)$ for all $(p,q)$ satisfying the conditions.

#### Computing $W_3$

For each $p$, we divide $q$ into several intervals, each interval satisfying that their $\pi\left(\dfrac{x}{pq} \right)$ is constant, and we can compute its contribution in $O(1)$ time. When we obtain a new $q$, we use the lookup table for $\pi(t)$ ($t\leq y$) to compute $\pi\left(\dfrac{x}{pq}\right)$. The prime table within $y$ can give the $t$ such that $\pi(t)<\pi(t+1)=\pi\left(\dfrac{x}{pq}\right)$. Similarly, we can find the next $q$ where $\pi\left(\dfrac{x}{pq}\right)$ changes.

#### Computing $W_4$

Compared to $W_3$, in $W_4$, $q$ is smaller, so $\pi\left(\dfrac{x}{pq} \right)$ changes more rapidly. At this point, using the method for computing $W_3$ to compute $W_4$ has no advantage. Therefore, we directly enumerate the number pairs $(p,q)$ to compute $W_4$ by brute force.

#### Computing $W_5$

We compute $W_5$ in the same way as $W_3$.

## Computing $S_3$

We use all primes less than $x^{1/4}$ to sieve the interval $\left[1,\dfrac{x}{y}\right]$ once. When our sieve reaches $p_k$, we compute all values of $-\mu(m)\phi\left(\dfrac{x}{mp_k},k-1 \right)$ for all $m$ that are square-free and satisfy $\delta(m)>p_k$. This sieve is performed in blocks, and we maintain a binary tree in the sieve intervals to maintain the intermediate results for all primes sieved up to a given prime in real-time. In this way, we can compute the number of numbers not sieved when the sieve reaches a certain value in $O(\log x)$ time complexity.

## Time and Space Complexity of the Algorithm

The time and space complexity are affected by the following 3 processes:

1.  Computing $P_2\left(x,a\right)$;
2.  Computing $W_1,W_2,W_3,W_4,W_5$;
3.  Computing $S_3$.

### Complexity of Computing $P_2(x,y)$

We already know that this process has time complexity $O\left(\dfrac{x}{y}\log{\log x}\right)$ and space complexity $O\left(y\right)$.

### Complexity of Computing $W_1,W_2,W_3,W_4,W_5$

The block sieving with block length $y$ for computing $W_1$ and $W_2$ has time complexity $O\left(\sqrt{x}\log{\log x}\right)$ and space complexity $O\left(y\right)$.

The time complexity for computing $W_1$ is:

$$
\pi\left(\dfrac{x}{y^2} \right)\pi\left(y\right)=O\left(\dfrac{x}{y\log^2 x} \right)
$$

The time complexity for computing $W_2$ is:

$$
O\left(\sum_{x/y^2<p\le \sqrt{x/y}}{\pi\left(\sqrt{\dfrac xp}\right)} \right)=O\left(\dfrac{x^{3/4}}{y^{1/4}\log^2 x} \right)
$$

Therefore, the time complexity for computing $W_3$ is:

$$
O\left(\sum_{x/y^2<p\le \sqrt{x/y}}{\pi\left(\sqrt{\dfrac xp}\right)} \right)=O\left(\dfrac{x^{3/4}}{y^{1/4}\log^2 x} \right)
$$

The time complexity for computing $W_4$ is:

$$
O\left(\sum_{\sqrt{x/y}<p\le x^{1/3}}{\pi\left(\sqrt{\dfrac xp}\right)} \right)=O\left(\dfrac{x^{2/3}}{\log^2 x} \right)
$$

The time complexity for computing $W_5$ is:

$$
O\left(\sum_{\sqrt{x/y}<p\le x^{1/3}}{\pi\left(\sqrt{\dfrac xp}\right)} \right)=O\left(\dfrac{x^{2/3}}{\log^2 x} \right)
$$

### Complexity of Computing $S_3$

For preprocessing: since we need to quickly query the value of $\phi(u,b)$, we cannot use ordinary sieving to compute it in $O(1)$, but must maintain a data structure so that each query has time complexity $O(\log x)$. Therefore, the time complexity is $O\left(\dfrac{x}{y}\log x\log\log x\right)$.

For the summation: for each term in the summation for computing $S_3$, we query the above data structure, a total of $O\left(\log x\right)$ queries. We also need to compute the number of terms in the summation, i.e., the number of leaves in the binary tree. All leaves are of the form $\pm\phi\left(\dfrac{x}{mp_b},b-1\right)$, where $m\le y,b<\pi(x^{1/4})$. Therefore, the number of leaves is $O\left(y\pi\left(x^{1/4}\right)\right)$. So the total time complexity for computing $S_3$ is:

$$
O\left(\dfrac{x}{y}\log x\log\log x+yx^{1/4}\right)
$$

### Total Complexity

The space complexity of this algorithm is $O\left(y\right)$, and the time complexity is:

$$
O\left(\dfrac{x}{y}\log{\log x}+\dfrac{x}{y}\log x\log{\log x}+x^{1/4}y+\dfrac{x^{2/3}}{\log^2{x}} \right)
$$

If we set $y=x^{1/3}\log^3{x}\log{\log x}$, we get the optimal time complexity $O\left(\dfrac{x^{2/3}}{\log^2 x}\right)$ and space complexity $O\left(x^{1/3}\log^3{x}\log{\log x}\right)$.

## Some Improvements

Here we provide improvement methods to reduce the constants of the algorithm and improve its actual efficiency.

-   In **Termination condition 2**, we can use a $z$ to replace $y$, where $z>y$. We can prove that the time complexity for computing $S_3$ can be optimized to:

    $$
    O\left(\dfrac{x}{z}\log x\log{\log x}+\dfrac{yx^{1/4}}{\log x}+z^{3/2} \right)
    $$

    This also provides a good method for checking the computation by changing the value of $z$.

-   For clarity, when describing the algorithm, we chose to split at $x^{1/4}$ to compute the total sum $S$, but in fact we only need $p\le \dfrac{x}{pq}<p^2$ to compute. We can take advantage of this, and the asymptotic complexity remains unchanged.

-   Precomputing with the first few primes $2,3,5$ can save more time.

## References and Further Reading

This article was translated from: [Computing $\pi(x)$: the Meissel, Lehmer, Lagarias, Miller, Odlyzko method](https://dl.acm.org/doi/abs/10.1090/s0025-5718-96-00674-6)