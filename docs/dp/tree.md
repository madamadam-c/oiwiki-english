author: aaron20100919

Tree DP is dynamic programming performed on trees. Because trees have an inherent recursive structure, tree DP is usually implemented recursively.

## Basics

The following problem demonstrates the general process of tree DP.

???+ note "Example Problem [Luogu P1352 Party Without Boss](https://www.luogu.com.cn/problem/P1352)"
    A university has $n$ employees, numbered $1 \sim N$. There are superior-subordinate relationships among them, forming a tree rooted at the principal; the parent node of a node is that employee's direct superior. An anniversary banquet is being held. Inviting employee $i$ increases the happiness value by $a_i$. However, if an employee's direct superior attends the banquet, that employee will refuse to attend. Compute which employees should be invited to maximize the total happiness value, and output the maximum value.

Let $f(i,0/1)$ denote the optimal solution for the subtree rooted at $i$. The second dimension is $0$ if $i$ does not attend the banquet, and $1$ if $i$ does attend.

For each state, there are two decisions, where each $x$ below is a child of $i$:

-   If the superior does not attend, each subordinate may either attend or not attend, so $f(i,0) = \sum\max \{f(x,1),f(x,0)\}$.
-   If the superior attends, none of the subordinates attend, so $f(i,1) = \sum{f(x,0)} + a_i$.

We can use DFS and update the optimal solution for the current node when returning to the previous level.

```cpp
--8<-- "docs/dp/code/tree/tree_1.cpp"
```

Usually, the state in tree DP is the optimal solution for the current node. First use DFS to traverse all optimal solutions in the subtree, then pass them upward to the parent of the subtree for transitions. The value at the root is the required optimal solution.

### Exercises

-   [HDU 2196 Computer](https://acm.hdu.edu.cn/showproblem.php?pid=2196)

-   [POJ 1463 Strategic game](http://poj.org/problem?id=1463)

-   [\[POI2014\] FAR-FarmCraft](https://www.luogu.com.cn/problem/P3574)

## Tree Knapsack

Tree knapsack problems are, in simple terms, the combination of knapsack problems and tree DP.

???+ note "Example Problem [Luogu P2014 CTSC1997 Course Selection](https://www.luogu.com.cn/problem/P2014)"
    There are $n$ courses. The $i$-th course has credit value $a_i$. Each course has zero or one prerequisite course. A course with a prerequisite can only be taken after its prerequisite has been completed.
    
    A student wants to take $m$ courses. Find the maximum number of credits the student can obtain.
    
    $n,m \leq 300$.

The fact that each course has at most one prerequisite is similar to the fact that each node in a rooted tree has at most one parent.

Therefore, we can build a tree according to this property, so all courses form a forest. For convenience, add a new course with $0$ credits, numbered $0$, as the prerequisite of every course that has no prerequisite. This turns the forest into a tree rooted at course $0$.

Let $f(u,i,j)$ denote the maximum credits obtainable in the subtree rooted at node $u$, after processing the first $i$ child subtrees of node $u$ and selecting $j$ courses.

The transition combines tree DP with [knapsack DP](./knapsack.md). Enumerate every child node $v$ of $u$, and also enumerate how many courses are selected in the subtree rooted at $v$, then merge the subtree result into $u$.

Let $s_x$ be the number of children of node $x$, and let $\textit{siz}_x$ be the size of the subtree rooted at $x$. The transition equation is:

$$
f(u,i,j)=\max_{v,k \leq j,k \leq \textit{siz}_v} f(u,i-1,j-k)+f(v,s_v,k)
$$

Pay attention to the constraints in the transition equation above. These constraints ensure that meaningless states are not visited.

The second dimension of $f$ can easily be omitted with a rolling array. In that case, enumerate $j$ in descending order.

It can be proven that this approach has time complexity $O(nm)$[^note1].

??? note "Reference Code"
    ```cpp
    --8<-- "docs/dp/code/tree/tree_2.cpp"
    ```

### Exercises

-   [CTSC1997 Course Selection](https://www.luogu.com.cn/problem/P2014)

-   [JSOI2018 Infiltration](https://loj.ac/problem/2546)

-   [SDOI2017 Apple Tree](https://loj.ac/problem/2268)

-   [Codeforces Round 875 Div. 1 Problem D. Mex Tree](https://codeforces.com/contest/1830/problem/D)

## Rerooting DP

Rerooting DP in tree DP is also called a second scan. Usually, the root node is not fixed, and changing the root affects values such as sums of child depths and sums of node weights.

Usually two DFS passes are needed. The first DFS preprocesses information such as depths and sums of weights. The second DFS runs the rerooting dynamic programming.

The following examples introduce this topic.

???+ note "Example Problem [\[POI2008\] STA-Station](https://www.luogu.com.cn/problem/P3478)"
    Given a tree with $n$ nodes, find a node such that when this node is used as the root, the sum of depths of all nodes is maximized.

Let $u$ be the current node and $v$ be a child of the current node. First, use $s_i$ to denote the number of nodes in the subtree rooted at $i$, so $s_u=1+\sum s_v$. Clearly, one DFS is needed to compute all $s_i$. This DFS is preprocessing: it gives the total number of nodes in the subtree when a certain node is used as root.

Now consider the state transition. This is where "rerooting" appears. Let $f_u$ be the sum of depths of all nodes when $u$ is the root.

The transition $f_v\leftarrow f_u$ represents changing the root from $u$ to $v$. During this rerooting transition, depths of nodes in the subtrees change depending on whether the root is $v$ or $u$:

-   The depths of all nodes in the subtree of $v$ decrease by one, so the total depth sum decreases by $s_v$.

-   The depths of all nodes not in the subtree of $v$ increase by one, so the total depth sum increases by $n-s_v$.

From these two facts, the transition equation is $f_v = f_u - s_v + n - s_v=f_u + n - 2 \times s_v$.

Therefore, during the second DFS, traverse the whole tree and perform the transition $f_v=f_u + n - 2 \times s_v$. This computes the depth sum for every possible root. Finally, scan all root depth sums once to obtain the answer.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/dp/code/tree/tree_3.cpp"
    ```

### Exercises

-   [Atcoder Educational DP Contest, Problem V, Subtree](https://atcoder.jp/contests/dp/tasks/dp_v)

-   [Educational Codeforces Round 67, Problem E, Tree Painting](https://codeforces.com/contest/1187/problem/E)

-   [POJ 3585 Accumulation Degree](http://poj.org/problem?id=3585)

-   [\[USACO10MAR\] Great Cow Gathering G](https://www.luogu.com.cn/problem/P2986)

-   [CodeForce 708C Centroids](http://codeforces.com/problemset/problem/708/C)

## References and Notes

[^note1]: [Complexity proof for subtree-merge knapsack DP - LYD729's CSDN blog](https://blog.csdn.net/lyd_7_29/article/details/79854245)
