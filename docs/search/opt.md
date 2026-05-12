author: CBW2007, ChungZH, Marcythm, abc1763613206, Ir1d

## Preface

DFS (depth-first search) is a common algorithm. Most problems can be solved with DFS, but in most cases this is only a partial-score approach; very few problems have brute-force search as the intended full solution, because DFS usually has very high time complexity. (If you have not learned DFS, please make up this lesson yourself.)

Since it cannot be the intended solution, let us at least get more partial points. This article introduces some practical optimization techniques, commonly known as "pruning".

First, here is a DFS template. Later templates will be modified based on it.

```cpp
int ans = worst_case, now;  // now is the current answer

void dfs(input_value) {
  if (destination_reached) ans = choose_the_better_of_current_and_existing_solution;
  for (iterate_over_all_possibilities)
    if (feasible) {
      perform_operation;
      dfs(reduced_scale);
      undo_operation;
    }
}
```

Here, `ans` can also be a record of solutions, in which case choosing the better of the current and existing solution becomes outputting the solution.

## Pruning Methods

The three most common types of pruning are memoized search, optimality pruning, and feasibility pruning.

### Memoized Search

Because in search, the same input values often lead to the same solution, we can use an array for memoization. See [memoized search](../dp/memo.md) for details.

**Template:**

```cpp
int g[MAXN];  // define the memoization array
int ans = worst_case, now;

void dfs f(input_value) {
  if (g[scale] != invalid_value) return;  // or record the solution, depending on the situation
  if (destination_reached) ans = choose_the_better_of_current_and_existing_solution;  // or output the solution, depending on the situation
  for (iterate_over_all_possibilities)
    if (feasible) {
      perform_operation;
      dfs(reduced_scale);
      undo_operation;
    }
}

int main() {
  // ...
  memset(g, invalid_value, sizeof(g));  // initialize the memoization array
  // ...
}
```

### Optimality Pruning

Another reason search can be slow is continuing to search when the current solution is already worse than an existing solution. We only need to check whether the current solution is already worse than the existing one.

**Template:**

```cpp
int ans = worst_case, now;

void dfs(input_value) {
  if (now_is_worse_than_ans) return;
  if (destination_reached) ans = choose_the_better_of_current_and_existing_solution;
  for (iterate_over_all_possibilities)
    if (feasible) {
      perform_operation;
      dfs(reduced_scale);
      undo_operation;
    }
}
```

### Feasibility Pruning

Continuing to search when the current solution has already become unusable is also a cause of slow execution.

**Template:**

```cpp
int ans = worst_case, now;

void dfs(input_value) {
  if (current_solution_is_unusable) return;
  if (destination_reached) ans = choose_the_better_of_current_and_existing_solution;
  for (iterate_over_all_possibilities)
    if (feasible) {
      perform_operation;
      dfs(reduced_scale);
      undo_operation;
    }
}
```

## Pruning Ideas

There are many pruning ideas, most of which require analysis of the specific problem. Here we briefly introduce several common pruning ideas.

-   Extreme-case method: consider the extreme case. If even the most extreme (most ideal) case cannot satisfy the requirement, then the result found in the actual situation certainly will not be better.

-   Adjustment method: compare subtrees to prune duplicate subtrees and subtrees that are obviously not the most "promising".

-   Mathematical methods: for example, using connected components in graph theory, analyzing modular equations in number theory, or estimating lower bounds by relaxing inequalities.

## Examples

???+ note "Job Assignment Problem"
    There are $n$ ($1 \leq n \leq  15$) jobs to be assigned to $n$ people, with each person completing one job. The time taken by person $i$ to complete job $k$ is a positive integer $t_{i,k}$ ($1 \leq t_{i,k} \leq 10^4$), where $1 \leq i, k \leq n$. Determine an assignment that minimizes the total time needed to complete these $n$ jobs.

    Since every person must be assigned a job, we can build a two-dimensional array `time[i][j]` to represent the time person $i$ spends completing job $j$. Use a loop to assign jobs starting from person 1 until everyone has been assigned. When assigning a job to person $i$, loop through each job to check whether it has already been assigned. If not, assign it to person $i$; otherwise, check the next job. A one-dimensional array `is_working[j]` can be used to indicate whether job $j$ has been assigned: if it has not been assigned, `is_working[j]=0`; otherwise, `is_working[j]=1`. Using the idea of backtracking, after the worker loop ends, return to the previous worker, cancel the current job assignment, and try assigning the next job until an assignment is possible. By backtracking all the way to worker 1, all feasible solutions can be obtained.

    Checking a job assignment is essentially checking that, in a feasible solution, the first-dimension indices of the two-dimensional array are all different and the second-dimension indices are also all different. We want the minimum total time for completing these $n$ jobs, namely the feasible solution with the smallest total time, so we also define a global variable `cost_time_total_min` to represent the smallest total time among solutions found so far. Initially, `cost_time_total_min` is the sum of `time[i][i]`, that is, the sum of the diagonal job times. When all people have been assigned jobs, compare `count` with `cost_time_total_min`. If `count` is less than `cost_time_total_min`, an optimal solution has been found, so assign `count` to `cost_time_total_min`.

    Considering algorithm efficiency, there is one more pruning optimization to apply here. Each time the local cost variable `count` is computed, if `count` is already greater than `cost_time_total_min`, there is no need to continue assigning jobs, because any solution obtained from this point must not be optimal.

??? note "Reference code"
    ```cpp
    --8<-- "docs/search/code/opt/opt_1.cpp"
    ```
