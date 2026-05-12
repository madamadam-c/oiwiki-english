This page briefly introduces the concept and applications of backtracking.

## Introduction

Backtracking is a technique often used in [depth-first search (DFS)](./dfs.md) and [breadth-first search (BFS)](./bfs.md).

Its essence is: if a path does not work, go back.

## Process

1.  Construct the state-space tree.

2.  Traverse it.

3.  If a boundary condition is met, stop searching downward and switch to another branch.

4.  When the target condition is reached, output the result.

## Examples

???+ example "[USACO 1.5.4 Checker Challenge](https://www.luogu.com.cn/problem/P1219)"
    There is now a $6 \times 6$ checkerboard as shown below. Six pieces are placed on the board so that each row, each column, and each diagonal (including all diagonals parallel to the two main diagonals) contains at most one piece.
    
    ```plain
    0   1   2   3   4   5   6
      -------------------------
    1 |   | O |   |   |   |   |
      -------------------------
    2 |   |   |   | O |   |   |
      -------------------------
    3 |   |   |   |   |   | O |
      -------------------------
    4 | O |   |   |   |   |   |
      -------------------------
    5 |   |   | O |   |   |   |
      -------------------------
    6 |   |   |   |   | O |   |
      -------------------------
    ```
    
    The layout above can be described by the sequence $\{2,4,6,1,3,5\}$. The $i$-th number means that there is a piece in column $a_i$ of row $i$, as shown below.
    
    Row number $i$: $\{1,2,3,4,5,6\}$
    
    Column number $a_i$: $\{2,4,6,1,3,5\}$
    
    This is only one placement of the checkers. Write a program to find all solutions and output them using the serialization method above, in lexicographic order. You only need to output the first $3$ solutions and output the total number of solutions on the last line. Note especially that you need to optimize your program to ensure its efficiency on larger board sizes.

??? note "Reference code"
    ```cpp
    --8<-- "docs/search/code/backtracking/backtracking_1.cpp"
    ```

???+ example "[Maze](https://www.luogu.com.cn/problem/P1605)"
    There is a maze of size $N \times M$ with $T$ obstacles, and obstacle cells cannot be passed through. Given the start coordinates and the end coordinates, and with each cell allowed to be visited at most once, ask how many ways there are to go from the start coordinates to the end coordinates. In the maze, there are four movement directions: up, down, left, and right. Each move can move only one cell. The data guarantees that there is no obstacle on the starting cell.

??? note "Reference code"
    ```cpp
    --8<-- "docs/search/code/backtracking/backtracking_2.cpp"
    ```
