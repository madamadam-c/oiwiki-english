## Introduction

Simulated annealing is a randomized algorithm. When a problem has an enormous (or even infinite) number of solutions and is not a unimodal function, we often use simulated annealing to solve it.

## Explanation

From the process of [hill climbing](./hill-climbing.md), we see that for a non-optimal solution near the current best solution, hill climbing directly discards it. In many cases, however, we need to accept this non-optimal solution to jump out of a local optimum. This is simulated annealing.

??? note "What is annealing? (excerpted from [Baidu Baike](https://baike.baidu.com/item/%E9%80%80%E7%81%AB/1039313))"
    Annealing is a metal heat-treatment process: a metal is slowly heated to a certain temperature, kept there for enough time, and then cooled at a suitable speed. Its purposes are to reduce hardness, improve machinability, eliminate residual stress, stabilize dimensions, reduce deformation and cracking tendency, refine grains, adjust structure, and eliminate structural defects. Strictly speaking, annealing is a heat-treatment process for materials, including both metallic and non-metallic materials. The purpose of annealing new materials also has similarities and differences compared with traditional metal annealing.

Because the annealing rule introduces more randomness, the probability of obtaining the optimal solution increases significantly. Therefore, we can simulate this process and treat the objective function as an energy function.

### Process

In one sentence: if the new state's solution is better, update the answer; otherwise, accept the new state with a certain probability.

Define the current temperature as $T$, and the energy (value) difference between the new state $S'$ and the known state $S$ (where the new state is obtained randomly from the known state) as $\Delta E$ ($\Delta E\geqslant 0$). Then the probability of a state transition (updating the best solution) is

$$
P(\Delta E)=
\begin{cases}
1,                              & S' \text{ is better than } S,\\
\mathrm{e}^\frac{-\Delta E}{T}, & \text{otherwise}.
\end{cases}
$$

**Note**: Sometimes, to obtain a higher-quality solution, after simulated annealing ends, we randomly sample states near the obtained solution multiple times at the current temperature and try to get a better solution. This process is similar to simulated annealing.

### How to Anneal (Cool Down)

In simulated annealing, we have three parameters: initial temperature $T_0$, cooling coefficient $d$, and terminal temperature $T_k$. Here $T_0$ is a relatively large number, $d$ is a number very close to $1$ but less than $1$, and $T_k$ is a positive number close to $0$.

First set the temperature to $T=T_0$, then perform one transition attempt according to the steps above, and then set $T=d\cdot T$. When $T<T_k$, the simulated annealing process ends, and the current best solution is the final best solution.

Note that to make the answer more precise, we usually do not directly take the current solution as the answer; instead, we maintain the best value among all solutions encountered during annealing.

Here is an image from [Simulated annealing - Wikipedia](https://en.wikipedia.org/wiki/Simulated_annealing) (as the temperature decreases, jumps become less random, and the optimum becomes more stable).

![](./images/simulated-annealing.gif)

## Implementation

The code here uses [「BZOJ 3680」Beat XXX](https://hydro.ac/p/bzoj-P3680) (finding the weighted Fermat-like point of $n$ points) as an example.

```cpp
--8<-- "docs/misc/code/simulated-annealing/simulated-annealing_1.cpp"
```

## Some Techniques

### Blocked Simulated Annealing

Sometimes a function has many peaks, making it hard for simulated annealing to find the optimum.

In this case, divide the entire value domain into several segments, run simulated annealing once on each segment, and then take the best answer.

### Time-Limited Running

There is a `clock()` function that returns the program's running time.

You can replace `simulateAnneal();` in the main program with `while ((double)clock()/CLOCKS_PER_SEC < MAX_TIME) simulateAnneal();`. This keeps running simulated annealing until the elapsed time is about to exceed the time limit.

Here `MAX_TIME` is a custom value slightly smaller than the time limit (in seconds).

## Exercises

-   [「BZOJ 3680」Beat XXX](https://hydro.ac/p/bzoj-P3680)
-   [「JSOI 2016」Bomb Attack](https://loj.ac/problem/2076)
-   [「HAOI 2006」Equalizing Data](https://www.luogu.com.cn/problem/P2503)
