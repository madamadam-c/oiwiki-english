author: Tiphereth-A, ShaoChenHeng, Enter-tainer, ksyx, c-forrest, StudyingFather, H-J-Granger, iamtwz, imp2002, Ir1d, kenlig, LeBronGod, Marcythm, MegaOwIer, NachtgeistW, ouuan, Patchouliys, Soohti, TianKong-y, sun2snow

## Introduction

Probability DP is used to solve probability and expectation problems. It is recommended to first understand [probability and expectation](../math/probability/exp-var.md). In general, probability problems are solved with forward iteration, while expectation problems use reverse iteration. If the defined transition equation has aftereffects, [Gaussian elimination](../math/numerical/gauss.md) may be needed for optimization. Probability DP is also often combined with other techniques, such as [state compression](./state.md) and DP transitions on trees.

## Probability DP

This type of problem uses forward transitions, from the initial state toward the result. As with ordinary DP, the main difficulty is still describing the state transition equation; the difference is that these problems are wrapped in probability theory.

### Example Problem

???+ example "[Codeforces 148D Bag of mice](https://codeforces.com/problemset/problem/148/D)"
    A bag contains $w$ white mice and $b$ black mice. The princess and the dragon take turns drawing mice from the bag. Whoever first draws a white mouse wins. If the bag becomes empty and no one has drawn a white mouse, the dragon wins. The princess draws one mouse each turn. After the dragon draws one mouse, another mouse runs out. Each drawn mouse and escaping mouse is random. The princess goes first. Find the probability that the princess wins.

??? note "Solution"
    Let $f_{i,j}$ be the probability that the princess wins when it is her turn and the bag contains $i$ white mice and $j$ black mice. Initialize the boundary values: $f_{0,j}=0$, because if there are no white mice the dragon wins; $f_{i,0}=1$, because drawing one mouse must draw a white mouse, so the princess wins.
    Consider transitions for $f_{i,j}$:
    
    -   The princess draws a white mouse and wins. The probability is $\dfrac{i}{i+j}$.
    -   The princess draws a black mouse, then the dragon draws a white mouse and wins. The probability is $\dfrac{j}{i+j}\cdot\dfrac{i}{i+j-1}$.
    -   The princess draws a black mouse, the dragon draws a black mouse, then a black mouse runs out, transitioning to $f_{i,j-3}$. The probability is $\dfrac{j}{i+j}\cdot\dfrac{j-1}{i+j-1}\cdot\dfrac{j-2}{i+j-2}$.
    -   The princess draws a black mouse, the dragon draws a black mouse, then a white mouse runs out, transitioning to $f_{i-1,j-2}$. The probability is $\dfrac{j}{i+j}\cdot\dfrac{j-1}{i+j-1}\cdot\dfrac{i}{i+j-2}$.
    
    When computing the probability that the princess wins, the second case does not contribute. The last two cases must also be valid, so the sizes of $i$ and $j$ need to be checked. The third case requires at least 3 black mice, and the fourth case requires at least 1 white mouse and 2 black mice.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/dp/code/probability/probability_1.cpp"
    ```

### Exercises

-   [POJ3071 Football](http://poj.org/problem?id=3071)
-   [CodeForces 768D Jon and Orbs](https://codeforces.com/problemset/problem/768/D)

## Expectation DP

### Example Problem

???+ example "[POJ2096 Collecting Bugs](http://poj.org/problem?id=2096)"
    A software system has $s$ subsystems and can produce $n$ types of bugs. Someone finds one bug per day. Each bug belongs to one bug category and one subsystem. The probability that a bug belongs to any subsystem is $\dfrac{1}{s}$, and the probability that it belongs to any bug category is $\dfrac{1}{n}$. Find the expected number of days needed to discover all $n$ bug categories and bugs in all $s$ subsystems.

??? note "Solution"
    Let $f_{i,j}$ be the expected number of days needed to reach the target state after already finding $i$ bug categories and bugs in $j$ subsystems. The target state is finding all $n$ bug categories and all $s$ subsystems. Thus $f_{n,s}=0$, because no additional days are needed after reaching the target state. We start the recurrence from the target state, and the answer is $f_{0,0}$.
    
    Consider transitions for $f_{i,j}$:
    
    -   $f_{i,j}$: the new bug belongs to one of the already found $i$ bug categories and one of the already found $j$ subsystems, with probability $p_1=\dfrac{i}{n}\cdot\dfrac{j}{s}$.
    -   $f_{i,j+1}$: the new bug belongs to an already found bug category but not an already found subsystem, with probability $p_2=\dfrac{i}{n}\cdot(1-\dfrac{j}{s})$.
    -   $f_{i+1,j}$: the new bug does not belong to an already found bug category but belongs to an already found subsystem, with probability $p_3=(1-\dfrac{i}{n})\cdot\dfrac{j}{s}$.
    -   $f_{i+1,j+1}$: the new bug belongs to neither an already found bug category nor an already found subsystem, with probability $p_4=(1-\dfrac{i}{n})\cdot(1-\dfrac{j}{s})$.
    
    By linearity of expectation, the transition equation is:
    
    $$
    \begin{aligned}
    f_{i,j} &= p_1\cdot f_{i,j}+p_2\cdot f_{i,j+1}+p_3\cdot f_{i+1,j}+p_4\cdot f_{i+1,j+1} + 1\\
    &= \dfrac{p_2\cdot f_{i,j+1}+p_3\cdot f_{i+1,j}+p_4\cdot f_{i+1,j+1}+1}{1-p_1}
    \end{aligned}
    $$

??? note "Reference Code"
    ```cpp
    --8<-- "docs/dp/code/probability/probability_2.cpp"
    ```

???+ example "[NOIP2016 Changing Classrooms](http://uoj.ac/problem/262)"
    Niuniu has classes in $n$ time slots. The class in the $i$-th time slot is in classroom $c_i$. He may apply to switch it to classroom $d_i$, and the application succeeds with probability $p_i$. He may apply to switch at most $m$ classes. After finishing the class in the $i$-th time slot, he must walk to the classroom for the $(i+1)$-th time slot. Given a graph with $v$ classrooms and $e$ roads, movement consumes stamina. Determine which classes to apply to switch so that the expected total stamina spent moving between classrooms is minimized; equivalently, find the minimum expected total path length.

??? note "Solution"
    For this undirected connected graph, first use Floyd-Warshall to compute all-pairs shortest paths, making later transitions convenient. Treat each move as a stage; moving from the $i$-th time slot to the $(i+1)$-th time slot is one move. At each step, there is probability $p_i$ of going to $d_i$, but at most $m$ of all $d_i$ can be chosen, and probability $1-p_i$ of going to $c_i$. We need the minimum expected total path length after $n$ stages.
    
    Define $f_{i,j,0/1}$ as the minimum expected total path length at the $i$-th time slot, after using $j$ classroom-switch opportunities including this time slot, where this time slot is switched (1) or not switched (0). The answer is $\min \{f_{n,i,0},f_{n,i,1}\}$ for $i\in[0,m]$. Note the boundary values $f_{1,0,0}=f_{1,1,1}=0$.
    
    Consider the transition for $f_{i,j,0/1}$:
    
    -   If this stage is not switched, i.e. $f_{i,j,0}$, it may transition from the previous state where the previous class was not switched, giving $f_{i-1,j,0}+w_{c_{i-1},c_i}$. It may also transition from the previous state where the previous class was switched. Using conditional probability and total probability gives $f_{i-1,j,1}+w_{d_{i-1},c_i}\cdot p_{i-1}+w_{c_{i-1},c_i}\cdot (1-p_{i-1})$. Thus:
    
    $$
    \begin{aligned}
    f_{i,j,0}=min(f_{i-1,j,0}+w_{c_{i-1},c_{i}},f_{i-1,j,1}+w_{d_{i-1},c_{i}}\cdot p_{i-1}+w_{c_{i-1},c_{i}}\cdot (1-p_{i-1}))
    \end{aligned}
    $$
    
    -   If this stage is switched, i.e. $f_{i,j,1}$, it may similarly transition from the previous non-switched state or previous switched state. When a class is not switched, multiply by $(1-p_i)$; when it is switched, multiply by $p_i$. Enumerate all possible cases and compute the result. The details are omitted here; after the previous example, the transition should be straightforward to write.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/dp/code/probability/probability_3.cpp"
    ```

Comparing these two problems, we can see that in expectation DP, whether the task is to compute a value or optimize a value affects how the transition equation is derived. However, whether we are computing probabilities or expectations with DP, the process always relies on probability knowledge and on writing and simplifying formulas. The details to consider when writing transition equations are similar.

### Exercises

-   [HDU3853 LOOPS](https://acm.hdu.edu.cn/showproblem.php?pid=3853)
-   [HDU4035 Maze](https://acm.hdu.edu.cn/showproblem.php?pid=4035)
-   [SCOI2008 Bonus Level](https://www.luogu.com.cn/problem/P2473)

## DP with Aftereffects

### Example Problem

???+ example "[CodeForces 24D Broken robot](https://codeforces.com/problemset/problem/24/D)"
    Given an $n\times m$ grid. A robot starts at row $x$, column $y$. At each step, the robot chooses uniformly at random to stay in place, move left one cell, move right one cell, or move down one cell. If the robot is on the boundary, it will not move outside the grid. Find the expected number of steps for the robot to reach the last row.

??? note "Solution"
    When $m=1$, at each step there is probability $\dfrac12$ of staying still and probability $\dfrac12$ of moving down one cell, so the answer is $2\cdot(n-x)$.
    Let $f_{i,j}$ be the expected number of steps for the robot to reach row $n$ starting from row $i$, column $j$. The final state is $f_{n,j}=0$.
    Since the robot chooses uniformly among staying still, moving left, moving right, and moving down, the transitions are:
    
    -   $f_{i,1}=\dfrac{1}{3}\cdot(f_{i+1,1}+f_{i,2}+f_{i,1})+1$
    -   $f_{i,j}=\dfrac{1}{4}\cdot(f_{i,j}+f_{i,j-1}+f_{i,j+1}+f_{i+1,j})+1$
    -   $f_{i,m}=\dfrac{1}{3}\cdot(f_{i,m}+f_{i,m-1}+f_{i+1,m})+1$
    
    Between rows, movement is only downward, so there is no aftereffect. Between columns, the robot may move left or right, and cycles may occur during movement, so the process has aftereffects.
    Rearranging the equations gives:
    
    -   $2f_{i,1}-f_{i,2}=3+f_{i+1,1}$
    -   $3f_{i,j}-f_{i,j-1}-f_{i,j+1}=4+f_{i+1,j}$
    -   $2f_{i,m}-f_{i,m-1}=3+f_{i+1,m}$
    
    Since this is a reverse recurrence, every $f_{i+1,j}$ is known.
    There are $m$ columns, so the right-hand side is equivalent to a column vector with $m$ rows, and the left-hand side is an $m\times m$ matrix. Using an augmented matrix gives an $m\times(m+1)$ matrix. Then [Gaussian elimination](../math/numerical/gauss.md) solves for the answer.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/dp/code/probability/probability_4.cpp"
    ```

### Exercises

-   [HDU 4418 Time Travel](https://acm.hdu.edu.cn/showproblem.php?pid=4418)
-   [HNOI2013 Wandering](https://loj.ac/problem/2383)

## References

[kuangbin's Probability DP Summary](https://www.cnblogs.com/kuangbin/archive/2012/10/02/2710606.html)
