author: chu-yuehan

SAT stands for Satisfiability problem. The general form is k-Satisfiability, or k-SAT. When $k > 2$, the problem is NP-complete. Therefore, we only study the case where $k = 2$.

## Definition

2-SAT, simply put, gives $n$ Boolean equations, each involving two variables, such as $a \vee b$, meaning at least one of variables $a, b$ is satisfied. Then we need to determine whether a feasible assignment exists. There may be multiple possible solutions, and generally problems only require finding one. Also, $\neg a$ represents the negation of $a$.

## Solution Approach

???+ example "[Luogu P4782 \"Template\" 2-SAT](https://www.luogu.com.cn/problem/P4782)"
    There are $n$ Boolean variables $x_1 \sim x_n$, and $m$ conditions that need to be satisfied. Each condition is in the form of "$x_i$ is `true`/`false` or $x_j$ is `true`/`false`". For example, "$x_1$ is true or $x_3$ is false", "$x_7$ is false or $x_2$ is false".
    
    The goal of 2-SAT is to assign each variable such that all conditions are satisfied.

Use Boolean equations to represent the above problem. Let $a$ denote $x_a$ is true (so $\neg a$ denotes $x_a$ is false). If someone proposes requirements $a$ and $b$ respectively, i.e., $(a \vee b)$ (at least one of variables $a, b$ is satisfied). Construct a directed graph for these variable relationships, where the establishment or non-establishment of $a$ is represented by nodes in the graph. $\neg a \to b$ and $\neg b \to a$ mean if $a$ **does not hold**, then $b$ **must hold**; similarly, if $b$ **does not hold**, then $a$ **must hold**. After constructing the graph, we can use the SCC algorithm to solve the 2-SAT problem.

|      Original Expression   |                Graph Construction               |
| :----------------: | :-----------------------------: |
|   $\neg a \vee b$  | $a \to b$ and $\neg b \to \neg a$ |
|     $a \vee b$     | $\neg a \to b$ and $\neg b \to a$ |
| $\neg a\vee\neg b$ | $a \to \neg b$ and $b \to \neg a$ |

Many 2-SAT problems require finding relationships like "if $a$ **does not hold**, then $b$ **holds**".

## Solving

Consider what it means if two nodes are in the same strongly connected component. According to the logical meaning of edges discussed earlier, if two nodes are in the same SCC, then the conditions represented by these two nodes **either both hold or both do not hold**.

After constructing the graph, we use [Tarjan's algorithm to find SCCs](./scc.md). For any Boolean variable $a$, check whether the node representing $a$ being true and the node representing $a$ being false are in the same SCC (a condition cannot both be satisfied and not satisfied, or both not satisfied and not not satisfied). If so, output "no solution", otherwise there is a solution.

When outputting a solution, the value of a variable can be determined by its topological order in the graph. If the topological order of variable $x$ comes after $\neg x$, then $x$ is true. Applying this to the SCCs from Tarjan's algorithm, when the SCC number of $x$ is before that of $\neg x$, take $x$ as true. Because Tarjan's algorithm uses a stack when finding SCCs, if the topological order after Tarjan's SCC compression is larger, it will be traversed later in Tarjan, popped from the stack earlier during compression, resulting in a smaller SCC number. Therefore, the SCC numbers obtained by Tarjan are equivalent to **reverse topological order**.

The algorithm traverses the entire graph. Since $n$ and $m$ are of the same order in this graph, the time complexity for computing the answer is $O(n)$. Therefore, the total complexity is $O(n)$.

??? note "Implementation"
    ```cpp
    --8<-- "docs/graph/code/2-sat/2-sat_3.cpp"
    ```

## Example Problems

### Example 1

???+ example "[HDU3062 Party](https://acm.hdu.edu.cn/showproblem.php?pid=3062)"
    There are $n$ couples invited to a party. Due to space limitations, only one person from each couple can attend. Among the $2n$ people, some people have conflicts (of course, couples have no conflicts). People with conflicts will not both appear at the party. Is it possible for $n$ people to attend simultaneously?

According to the analysis above, if the husband in couple $a_1$ and the wife in couple $a_2$ have a conflict, we connect the husband in $a_1$ with the husband in $a_2$, and the wife in $a_2$ with the wife in $a_1$. Then perform SCC compression and coloring to determine the solution.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/graph/code/2-sat/2-sat_1.cpp"
    ```

### Example 2

???+ example "[2018-2019 ACM-ICPC Asia Seoul Regional K TV Show Game](https://codeforces.com/gym/101987/problem/K)"
    There are $k$ lamps, each either red or blue, but the initial colors are unknown. There are $n$ people, each person selects three lamps and guesses their colors. A person wins a prize if they guess two or more lamps correctly. Determine whether there exists a coloring scheme such that everyone can win a prize. If yes, output one such coloring scheme.

Based on [Wu Yu - "Solving 2-SAT Problems by Symmetry"](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AF%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AF%E9%98%9F2003%E8%AE%BA%E6%96%87%E9%9B%86/%E4%BC%8D%E6%98%B1--%E7%94%B1%E5%AF%B9%E7%A7%B0%E6%80%A7%E8%A7%A32-SAT%E9%97%AE%E9%A2%98/%E4%BC%8D%E6%98%B1.ppt), we can conclude: to output a feasible solution for a 2-SAT problem, we only need to perform selection and deletion from bottom to top on the DAG obtained after Tarjan's SCC compression.

Specifically, this can be implemented by performing topological sort on the reverse graph of the DAG. Alternatively, based on the property that after Tarjan's SCC compression, nodes with smaller component numbers are closer to leaf nodes, we can prioritize selecting nodes with smaller component numbers.

The following gives the code for the second implementation method.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/graph/code/2-sat/2-sat_2.cpp"
    ```

## Practice Problems

-   [Luogu P5782 Peace Committee](https://www.luogu.com.cn/problem/P5782)
-   [POJ3683 Priest John's Busiest Day](http://poj.org/problem?id=3683)