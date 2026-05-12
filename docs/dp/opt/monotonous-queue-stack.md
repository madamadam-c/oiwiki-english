author: liujiaxi123456, Marcythm, hsfzLZH1, Ir1d, greyqz, Anguei, billchenchina, Chrogeek, ChungZH

## Introduction

Prerequisites: [Monotone Queue](../../ds/monotonous-queue.md), [Monotone Stack](../../ds/monotonous-stack.md).

A monotone queue is mainly used to maintain range extrema when the two interval pointers are nondecreasing. A monotone stack is mainly used to maintain the first previous or next element greater or smaller than the current value.

???+ note "Note"
    -   To query minimum values, maintain a **monotonically increasing/nondecreasing** monotone queue or monotone stack; for maximum values, do the opposite.
    -   When maintaining strictly increasing/decreasing order, compare with **less than or equal to / greater than or equal to**. When maintaining nondecreasing/nonincreasing order, compare with **less than / greater than**.

## Concrete Steps for Monotone Queue Optimization

-   Add required elements: repeatedly add elements to the monotone queue until the current element reaches the right boundary of the queried interval. This ensures that all required elements are in the monotone queue.
-   Pop out-of-range front elements: a monotone queue essentially maintains the extremum of all inserted elements, but we usually want a range extremum. Therefore, pop elements outside the left boundary to ensure all elements in the monotone queue lie inside the queried interval.
-   Get the extremum: directly take the front of the queue as the answer.

## Concrete Steps for Monotone Stack Optimization

-   Pop invalid stack tops: compare the current element with the stack top, and pop stack tops that do not satisfy the monotone-stack property. For a monotonically increasing stack, meaning the stack top is the largest and it maintains minimum values, pop all elements in the stack that are greater than or equal to the current element.
-   Add the current element: push the current element onto the stack.

## Monotone Queue Optimization for Multiple Knapsack

???+ note "Problem Description"
    You have $n$ items. Item $i$ has weight $w_i$, value $v_i$, and quantity $k_i$. You have a knapsack with weight limit $W$. Choose items with total weight not exceeding the limit while maximizing total value. Find the maximum value.

If you are not familiar with knapsack DP, read [Knapsack DP](../knapsack.md) first. Let $f_{i,j}$ denote the maximum value when putting the first $i$ item types into a knapsack with capacity $j$. The naive transition is:

$$
f_{i,j}=\max_{k=0}^{k_i}(f_{i-1,j-k\times w_i}+v_i\times k)
$$

The time complexity is $O(W\sum k_i)$.

Consider optimizing the transition for $f_i$. For convenience, let $g_{x,y}=f_{i,x\times w_i+y}$ and $g'_{x,y}=f_{i-1,x\times w_i+y}$, where $0\le y<w_i$. Then the transition can be written as:

$$
g_{x,y}=\max_{k=0}^{k_i}(g'_{x-k,y}+v_i\times k)
$$

Let $G_{x,y}=g'_{x,y}-v_i\times x$. Then:

$$
g_{x,y}=\max_{k=0}^{k_i}(G_{x-k,y})+v_i\times x
$$

This transforms the problem into a classic monotone-queue optimization form. $G_{x,y}$ can be computed in $O(1)$, so for a fixed $y$, we can compute $g_{x,y}$ in $O\left(\left\lfloor\dfrac{W}{w_i}\right\rfloor\right)$ time. Therefore, computing all $g_{x,y}$ costs $O\left(\left\lfloor\dfrac{W}{w_i}\right\rfloor\right)\times O(w_i)=O(W)$. The total transition complexity is reduced to $O(nW)$.

In implementation, enumerate $y$ first so that when enumerating $x$, the monotone queue can be used for optimization. The monotone queue stores $x-k$, not $k$. Therefore, when using it, get the corresponding $G_{x-k,y}$ with `f[last][q.front() * w[i] + y] - q.front() * v[i]`. It is easy to see that $x-k\in[x-k_i,x]$, so when enumerating $x$, remove elements from the queue that are not in this range.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/dp/code/opt/monotonous-queue-stack/monotonous-queue-stack_2.cpp"
    ```

## Exercises

???+ note "Example Problem [CF372C Watching Fireworks is Fun](http://codeforces.com/problemset/problem/372/C)"
    Problem summary: a town has $n$ positions, and $m$ fireworks will be launched. The $i$-th firework is launched at time $t_i$ and position $a_i$. If you are at position $x$ when it is launched, you gain $b_i-|a_i-x|$ happiness.
    
    Initially, you may be at any position. In each unit of time, you can move at most $d$ units of distance. Maximize the happiness you can obtain.

Let $f_{i,j}$ denote the maximum happiness obtainable when the $i$-th firework is launched and your position is $j$.

The transition equation is $f_{i,j}=\max\{f_{i-1,k}+b_i-|a_i-j|\}$, where $j-(t_i-t_{i-1})\times d\le k\le j+(t_i-t_{i-1})\times d$.

Try transforming it:

Because the constant $b_i$ appears inside the $\max$, we can pull it out.

$f_{i,j}=\max\{f_{i-1,k}+b_i-|a_i-j|\}=\max\{f_{i-1,k}-|a_i-j|\}+b_i$

If $i$ and $j$ are fixed, then $|a_i-j|$ is also fixed and can also be pulled out.

The expression becomes:

$$
f_{i,j}=\max\{f_{i-1,k}-|a_i-j|\}+b_i=\max\{f_{i-1,k}\}-|a_i-j|+b_i
$$

Now consider monotone queue optimization. The $\max$ in the final expression only depends on the maximum value over a continuous segment of the previous state. Therefore, when computing the states for a new $i$, build a monotone queue from the old $f_{i-1}$ and maintain it so that $\max\{f_{i-1,k}\}$ can be computed in amortized $O(1)$ time, then compute $f_{i,j}$ from the formula.

The total time complexity is $O(nm)$.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/dp/code/opt/monotonous-queue-stack/monotonous-queue-stack_1.cpp"
    ```

-   [Luogu P1886 Sliding Window](https://loj.ac/problem/10175)
-   [NOI2005 Gorgeous Waltz](https://www.luogu.com.cn/problem/P2254)
-   [SCOI2010 Stock Trading](https://loj.ac/problem/10183)
