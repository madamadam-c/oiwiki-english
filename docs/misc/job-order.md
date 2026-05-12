You have $n$ jobs, and you need to find a minimum-cost order to execute them. The $i$-th job takes time $t_i$, and if the $i$-th job waits for time $t$, it incurs cost $f_i(t)$.

Formally, given $n$ functions $f_i$ and $n$ numbers $t_i$, find a permutation $p$ that minimizes

$$
F(p)=\sum_{i=1}^nf_{p_i}\left(\sum_{j=1}^{i-1}t_{p_j}\right)
$$

## Special Cost Functions

### Linear Cost Functions

First consider the case where all functions are linear, i.e. $f_i(x)=c_ix+d_i$, where $c_i$ is a nonnegative integer. Clearly, we can add all constant terms in advance, so the function is transformed into the form $f_i(x)=c_ix$.

Consider two permutations $p$ and $p'$, where $p'$ is obtained by swapping the numbers at positions $i$ and $i+1$ in $p$. Then

$$
\begin{aligned}
F(p')-F(p)&=c_{p'_i}\sum_{j=1}^{i-1}t_{p'_j}+c_{p'_{i+1}}\sum_{j=1}^{i}t_{p'_j}
-\left(c_{p_i}\sum_{j=1}^{i-1}t_{p_j}+c_{p_{i+1}}\sum_{j=1}^{i}t_{p_j}\right)\\
&=c_{p_i}t_{p_{i+1}}-c_{p_{i+1}}t_{p_i}
\end{aligned}
$$

Therefore, we can sort using the strategy of swapping whenever $c_{p_i}t_{p_{i+1}}-c_{p_{i+1}}t_{p_i}>0$. Written as $\dfrac{c_{p_i}}{t_{p_i}}>\dfrac{c_{p_{i+1}}}{t_{p_{i+1}}}$, this means sorting the permutation in ascending order of $\dfrac{c_i}{t_i}$.

Our approach to this problem is to consider how the cost changes under a small perturbation, then greedily choose the optimal order.

### Exponential Cost Functions

Consider cost functions of the form $f_i(x)=c_i\mathrm{e}^{ax}$, where $c_i\ge 0,a>0$.

Using the previous idea, consider the cost change caused by swapping the elements at positions $i$ and $i+1$. The resulting algorithm sorts the permutation in ascending order of $\dfrac{1-\mathrm{e}^{at_i}}{c_i}$.

### Identical Increasing Function

Consider the case where all $f_i(x)$ are the same increasing function. Then clearly we should sort the permutation in ascending order of $t_i$.

## Livshits-Kladov Theorem

The Livshits-Kladov theorem holds if and only if the cost functions are one of the following three cases:

-   Linear functions: $f_i(t) = c_it + d_i$, where $c_i\ge 0$;
-   Exponential functions: $f_i(t) = c_i \mathrm{e}^{a t} + d_i$, where $c_i,a>0$;
-   Identical increasing function: $f_i(t) = \phi(t)$, where $\phi(t)$ is an increasing function.

The theorem is proved under the assumption that the cost functions are sufficiently smooth (third derivatives exist). In these three cases, the optimal solution can be obtained by simple sorting in $O(n\log n)$ time.

**This page is mainly translated from the blog post [Задача Джонсона с одним станком](http://e-maxx.ru/algo/johnson_problem_1) and its English translation [Scheduling jobs on one machine](https://cp-algorithms.com/schedules/schedule_one_machine.html). The Russian version is licensed as Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
