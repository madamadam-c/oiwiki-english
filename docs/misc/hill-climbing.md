## Introduction

Hill climbing is a local-greedy method that uses heuristics. It is an improvement over depth-first search and uses feedback information to help make decisions when generating solutions.

Put simply, when the current solution cannot directly reach the optimum, but we can judge which of two solutions is better, we generate a new possible solution based on some feedback information.

Therefore, each time, hill climbing searches for a new solution near the current best solution $x$. If this new solution $x'$ is better, it moves to $x'$; otherwise it stays unchanged.

This algorithm is clearly feasible for unimodal functions.

Q: If we already know it is a unimodal function, why not use ternary search?

A: The advantage of hill climbing is that when you do not know how to write the intended solution (common in difficult computational geometry and math problems), or when the state itself has many dimensions and it is hard to write divide and conquer (Example 2 can be solved correctly with binary search), you can obtain the optimum through very brute-force computation.

However, for most functions that need to be optimized, hill climbing can easily enter a local optimum, as shown below (the true optimum is $\color{green}{\Uparrow}$, while the optimum hill climbing may find is $\color{red}{\Downarrow}$).

![](./images/hill-climbing.png)

## Implementation Details

Hill climbing usually introduces a temperature parameter (similar to simulated annealing). By analogy, hill climbing is like a drunk rabbit jumping on a mountain. Each time it jumps toward what it thinks is higher ground (often only an inaccurate trend). Clearly, it may jump to the mountain top in one step, or it may overshoot and flip to the other side. But that is fine; after flipping over, the rabbit will jump back. Clearly this process is useless, and the rabbit will never find a way out, so during the process the rabbit calms down and becomes more cautious with each jump, jumping less, in order to reach a suitable optimum.

The process by which the rabbit gradually sobers up is the cooling process; that is, the temperature parameter keeps decreasing during hill climbing.

About cooling: the cooling parameter is a constant slightly less than $1$, usually chosen from $[0.985, 0.999]$.

## Examples

???+ example "[「JSOI2008」Spherical Space Generator](https://www.luogu.com.cn/problem/P4035)"
    Given $n + 1$ points in $n$-dimensional space, known to lie on the same $n$-dimensional sphere, find the sphere center. $n \leq 10$, and the absolute value of each coordinate does not exceed $20000$.

??? note "Solution"
    This is an obvious unimodal function and can be solved with hill climbing. The algorithm process for this problem:
    
    1.  Initialize the sphere center as the centroid of the given points (i.e., each coordinate is the average of the corresponding coordinates of all given points), reducing the amount of enumeration.
    2.  For the current sphere center, compute the average Euclidean distance from each known point to this center.
    3.  Iterate over all known points. Record a change value $\textit{cans}$ (separately for each dimension). For each point's Euclidean distance, if it is greater than the average, add the difference to the change value; otherwise subtract it. In fact, we do not need to compare the sizes; if we ignore absolute values, we can compute directly using coordinates. This process can be vividly interpreted as a new sphere center being pushed around in space: if it meets a point that is too far away, it is pulled slightly toward that point; if it meets a point that is too close, it is pushed slightly away from that point.
    4.  Multiply the recorded $\textit{cans}$ by the temperature, update the sphere center, and return to step 2.
    5.  End when the temperature is below a given threshold.
    
    Therefore, when updating the sphere center, we cannot directly add the change value; we must add the product of the change value and the temperature.
    
    Not every hill-climbing problem can specifically be solved with temperature; this is only one example.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/misc/code/hill-climbing/hill-climbing_1.cpp"
    ```

???+ example "[「BZOJ 3680」Beat XXX](https://hydro.ac/p/bzoj-P3680)"
    Find the weighted Fermat-like point of $n$ points.

??? note "Solution"
    The framework is similar and uses some physics knowledge.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/misc/code/hill-climbing/hill-climbing_2.cpp"
    ```

## Optimization

It is easy to think that, to obtain as good an answer as possible, we can run hill climbing multiple times. Methods include modifying the initial state, modifying the cooling parameter, or modifying the initial temperature, then keeping a global best answer. After each hill-climbing run ends, update the global optimum.

The possible problem with this approach is timeout. In official contests, please manually create large tests for parameter tuning.

## Disadvantage

The disadvantage of hill climbing has already been mentioned above: it easily falls into a local optimum. When the objective function is not unimodal, this disadvantage is fatal. Therefore, we introduce [**simulated annealing**](./simulated-annealing.md).
