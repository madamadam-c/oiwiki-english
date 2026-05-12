The Josephus problem has a long history, and its solutions have been continuously improved. However, there is still no extremely efficient algorithm (within logarithmic time) for this problem.

## Problem Description

> n people are numbered $0,1,\cdots, n-1$ and stand in a circle counterclockwise. Starting from person $0$, each time count $k$ people counterclockwise from the current person, then eliminate that person. Ask who remains at the end.

This classic problem was proposed by Josephus in the 1st century AD, although he only considered the case $k=2$ at the time. Today, we can solve this problem with many efficient algorithms.

## Procedure

### Naive Algorithm

The most naive algorithm is direct simulation. Use a circular linked list to simulate the deletion process, repeat $n-1$ times, and obtain the answer. The complexity is $\Theta (n^2)$.

### Simple Optimization

The process of finding the next person can be optimized with a segment tree. Specifically, build a segment tree over $0,1,\cdots, n-1$ and record the number of remaining people in each interval. The current person's position and the following $k$-th person can be found by binary searching on the segment tree.

### Linear Algorithm

Let $J_{n,k}$ denote the answer to the Josephus problem with parameters $n,k$. We have the following recurrence:

$$
J_{n,k}=(J_{n-1,k}+k)\bmod n
$$

This is also easy to derive. Starting from $0$, count $k$ people and eliminate the $k-1$-th person, leaving $n-1$ people. After computing the answer among these $n-1$ people, add the relative offset $k$ to obtain the true answer. The complexity of this algorithm is clearly $\Theta (n)$.

???+ note "Implementation"
    ```cpp
    int josephus(int n, int k) {
      int res = 0;
      for (int i = 1; i <= n; ++i) res = (res + k) % i;
      return res;
    }
    ```

### Logarithmic Algorithm

For the case where $k$ is small and $n$ is large, this problem also has an algorithm with complexity $\Theta (k\log n)$.

Since we delete one person every time we walk $k$ people, within one full circle we can delete $\left\lfloor\frac{n}{k}\right\rfloor$ people, leaving $n-\left\lfloor\frac{n}{k}\right\rfloor$ people. At this point we are at the position of the $\left\lfloor\frac{n}{k}\right\rfloor\cdot k$-th person. Notice that this equals $n-n\bmod k$. We then continue recursively and restore the relative position after computing the answer. The basis for restoring the relative position is: each deletion removes the counted $k$-th person, and their indices are inherited one by one by the following people. Thus, when computing on the circle of $n-\left\lfloor\frac{n}{k}\right\rfloor$ people, $1$ position is missed every $k$ people. If the result is less than $0$, take modulo $n$ on the original circle where multiples of $k$ have not been removed, using $n$; if the result is at least $0$, multiply directly by $\frac{k}{k-1}$. This gives the following algorithm:

???+ note "Implementation"
    ```cpp
    int josephus(int n, int k) {
      if (n == 1) return 0;
      if (k == 1) return n - 1;
      if (k > n) return (josephus(n - 1, k) + k) % n;  // linear algorithm
      int res = josephus(n - n / k, k);
      res -= n % k;
      if (res < 0)
        res += n;  // mod n
      else
        res += res / (k - 1);  // restore position
      return res;
    }
    ```

It can be proved that this algorithm has complexity $\Theta (k\log n)$. Let the number of recursive calls in this process be $x$. Each time, the problem size roughly becomes $\displaystyle n\left(1-\frac{1}{k}\right)$, giving

$$
n\left(1-\frac{1}{k}\right)^x=1
$$

Solving this equation gives

$$
x=-\frac{\ln n}{\ln\left(1-\frac{1}{k}\right)}
$$

Now we prove that the algorithm has complexity $\Theta (k\log n)$.

???+ note "Proof"
    Consider $\displaystyle \lim _{k \rightarrow \infty} k \log \left(1-\frac{1}{k}\right)$. We have
    
    $$
    \begin{aligned}
    \lim _{k \rightarrow \infty} k \log \left(1-\frac{1}{k}\right)&=\lim _{k \rightarrow \infty} \frac{\log \left(1-\frac{1}{k}\right)}{1 / k}\\
    &=\lim _{k \rightarrow \infty} \frac{\frac{\mathrm d}{\mathrm d k} \log \left(1-\frac{1}{k}\right)}{\frac{\mathrm d}{\mathrm d k}\left(\frac{1}{k}\right)}\\
    &=\lim _{k \rightarrow \infty} \frac{\frac{1}{k^{2}\left(1-\frac{1}{k}\right)}}{-\frac{1}{k^{2}}}\\
    &=\lim _{k \rightarrow \infty}-\frac{k}{k-1}\\
    &=-\lim _{k \rightarrow \infty} \frac{1}{1-\frac{1}{k}}\\
    &=-1
    \end{aligned}
    $$
    
    Therefore $x \sim k \ln n, k\to \infty$, i.e. $-\dfrac{\ln n}{\ln\left(1-\frac{1}{k}\right)}= \Theta (k\log n)$.

**This page is mainly translated from the blog post [Задача Иосифа](https://e-maxx.ru/algo/joseph_problem) and its English translation [Josephus Problem](https://cp-algorithms.com/others/josephus_problem.html). The Russian version is licensed as Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
