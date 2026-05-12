This page briefly introduces heuristic search and its usage.

## Definition

Heuristic search is a search algorithm that introduces a heuristic function on top of an ordinary search algorithm.

The role of a heuristic function is to estimate every branch choice in the search based on known information, and then choose a branch. In simple terms, heuristic search analyzes both taking and not taking an option, then selects a better solution or removes invalid solutions.

## Examples

Because the concept is rather abstract, we explain it through an example.

???+ note "[NOIP2005 Junior Group - Herb Gathering](https://www.luogu.com.cn/problem/P1048)"
    Problem summary: There are $N$ kinds of items and a knapsack with capacity $W$. Each item has two attributes, weight $w_i$ and value $v_i$. Choose several items (each item can be chosen at most once) to put into the knapsack, maximizing the total value of the items in the knapsack while keeping their total weight no more than the knapsack capacity.

??? note "Solution idea"
    We write an evaluation function $f$ that can prune all invalid $0$ branches (that is, prune many useless branches where the item is not taken).
    
    The evaluation function $f$ works as follows:
    
    When taking an item, check whether the specified volume is exceeded (feasibility pruning). When not taking an item, check whether the total value of all remaining herbs plus the current value is greater than the best solution found so far (optimality pruning).

??? note "Sample code"
    ```cpp
    --8<-- "docs/search/code/heuristic/heuristic_1.cpp"
    ```
