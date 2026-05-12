## Definition

Iterative deepening is a depth-first search that **limits the search depth each time**.

## Explanation

Iterative deepening search is still essentially depth-first search, except that the search carries a depth $d$ and returns when $d$ reaches the configured depth. It is generally used to find an optimal solution. If one search does not find a valid solution, increase the configured depth by one and restart from the root.

Since the goal is to find an optimal solution, why not use BFS? BFS is based on a queue, whose space complexity is large. When there are many states or each individual state is large, BFS with a queue shows its disadvantage. In fact, iterative deepening is similar to implementing BFS in a DFS style, and its space complexity is relatively small.

When the search tree has many branches, adding one more level causes the search complexity to explode exponentially. At that point, the cost of the repeatedly searched earlier parts is almost negligible, which is why iterative deepening can be approximately viewed as BFS.

## Process

First set a small depth as a global variable and run DFS. Each time DFS is entered, increase the current depth by one; when $d$ is found to be greater than the configured depth $\textit{limit}$, return. If an answer is found during the search, backtracking can begin, and the path can be recorded during backtracking. If no answer is found, return to the function entry point, increase the configured depth, and continue searching.

???+ note "Implementation (pseudocode)"
    ```text
    IDDFS(u,d)
        if d>limit
            return
        else
            for each edge (u,v)
                IDDFS(v,d+1)
    return
    ```

## Notes

In most problems, breadth-first search is still convenient and makes duplicate detection easy. When breadth-first search is not good enough in terms of space and the problem asks for an optimal solution, consider iterative deepening.
