## Definition

Memoized search is a way to implement search by recording information about states that have already been visited, thereby avoiding repeated traversal of the same state.

Because memoized search ensures that each state is visited only once, it is also a common way to implement dynamic programming.

## Introduction

???+ note "[\[NOIP2005\] Herb Gathering](https://www.luogu.com.cn/problem/P1048)"
    There are $M$ different herbs in a cave. Picking each herb takes some time $t_i$, and each herb also has its own value $v_i$. Given a time limit $T$, you may pick some herbs within this time. Maximize the total value of the herbs picked.
    
    $1 \leq T \leq 10^3$, $1 \leq t_i,v_i,M \leq 100$.

### Naive [DFS](../search/dfs.md) Approach

A naive search is easy to implement: during search, record three parameters: which item is currently being considered, how much time remains, and how much value has already been obtained. Then enumerate whether the current item is selected and transition to the corresponding state.

???+ note "Implementation"
    === "C++"
        ```cpp
        int n, t;
        int tcost[103], mget[103];
        int ans = 0;
        
        void dfs(int pos, int tleft, int tans) {
          if (tleft < 0) return;
          if (pos == n + 1) {
            ans = max(ans, tans);
            return;
          }
          dfs(pos + 1, tleft, tans);
          dfs(pos + 1, tleft - tcost[pos], tans + mget[pos]);
        }
        
        int main() {
          cin >> t >> n;
          for (int i = 1; i <= n; i++) cin >> tcost[i] >> mget[i];
          dfs(1, t, 0);
          cout << ans << endl;
          return 0;
        }
        ```
    
    === "Python"
        ```python
        tcost = [0] * 103
        mget = [0] * 103
        ans = 0
        
        
        def dfs(pos, tleft, tans):
            global ans
            if tleft < 0:
                return
            if pos == n + 1:
                ans = max(ans, tans)
                return
            dfs(pos + 1, tleft, tans)
            dfs(pos + 1, tleft - tcost[pos], tans + mget[pos])
        
        
        t, n = map(lambda x: int(x), input().split())
        for i in range(1, n + 1):
            tcost[i], mget[i] = map(lambda x: int(x), input().split())
        dfs(1, t, 0)
        print(ans)
        ```

This approach has exponential time complexity and cannot pass this problem.

### Optimization

Why is the approach above inefficient? Because the same state is visited many times.

If we store the information for a state after computing it, then the next time we need to visit that state we can directly use the previously computed result and avoid repeated computation. This fully uses the fact that many dynamic-programming problems contain numerous overlapping subproblems. It is the idea of "memoization", trading space for time.

For this problem specifically, we add an array `mem` on top of the naive DFS to record the return value of each `dfs(pos,tleft)`. Initially, every value in `mem` is set to `-1`, meaning it has not been solved. Whenever a state needs to be visited, if its value in `mem` is `-1`, recursively visit and compute that state. Otherwise, directly use the stored value in `mem`.

With this processing, each state is visited only once, so the algorithm has time complexity $O(TM)$.

???+ note "Implementation"
    === "C++"
        ```cpp
        int n, t;
        int tcost[103], mget[103];
        int mem[103][1003];
        
        int dfs(int pos, int tleft) {
          if (mem[pos][tleft] != -1)
            return mem[pos][tleft];  // Already visited; return the recorded value.
          if (pos == n + 1) return mem[pos][tleft] = 0;
          int dfs1, dfs2 = -INF;
          dfs1 = dfs(pos + 1, tleft);
          if (tleft >= tcost[pos])
            dfs2 = dfs(pos + 1, tleft - tcost[pos]) + mget[pos];  // State transition.
          return mem[pos][tleft] = max(dfs1, dfs2);  // Store the value of the current state.
        }
        
        int main() {
          memset(mem, -1, sizeof(mem));
          cin >> t >> n;
          for (int i = 1; i <= n; i++) cin >> tcost[i] >> mget[i];
          cout << dfs(1, t) << endl;
          return 0;
        }
        ```
    
    === "Python"
        ```python
        tcost = [0] * 103
        mget = [0] * 103
        mem = [[-1 for i in range(1003)] for j in range(103)]
        
        
        def dfs(pos, tleft):
            if mem[pos][tleft] != -1:
                return mem[pos][tleft]
            if pos == n + 1:
                mem[pos][tleft] = 0
                return mem[pos][tleft]
            dfs1 = dfs2 = -INF
            dfs1 = dfs(pos + 1, tleft)
            if tleft >= tcost[pos]:
                dfs2 = dfs(pos + 1, tleft - tcost[pos]) + mget[pos]
            mem[pos][tleft] = max(dfs1, dfs2)
            return mem[pos][tleft]
        
        
        t, n = map(lambda x: int(x), input().split())
        for i in range(1, n + 1):
            tcost[i], mget[i] = map(lambda x: int(x), input().split())
        print(dfs(1, t))
        ```

## Relationship and Differences Compared with Recurrence

When solving dynamic-programming problems, memoized-search code and iterative recurrence code are often highly similar in form. This is because they use the same state representation and similar state transitions. For the same reason, the two implementations usually have the same time complexity.

The following is an iterative implementation. For easier comparison, rolling-array optimization is not used. Comparing the code shows the formal similarity between the two approaches.

```cpp
int n, t, w[105], v[105], f[105][1005];

int main() {
  cin >> n >> t;
  for (int i = 1; i <= n; i++) cin >> w[i] >> v[i];
  for (int i = 1; i <= n; i++)
    for (int j = 0; j <= t; j++) {
      f[i][j] = f[i - 1][j];
      if (j >= w[i])
        f[i][j] = max(f[i][j], f[i - 1][j - w[i]] + v[i]);  // State transition equation.
    }
  cout << f[n][t];
  return 0;
}
```

When solving dynamic-programming problems, both memoized search and iterative recurrence ensure that the same state is solved at most once. However, they do this in slightly different ways: iterative recurrence avoids repeated visits by setting an explicit visiting order, while memoized search does not explicitly prescribe a visiting order, but achieves the same goal by marking states that have already been visited.

Compared with iterative recurrence, memoized search is sometimes easier to implement because it does not require explicitly determining the visiting order, and it can handle boundary cases more conveniently. This is a major advantage of memoized search. At the same time, memoized search has difficulty using optimizations such as rolling arrays, and because it uses recursion, it is usually less efficient than iterative recurrence. Therefore, choose the implementation that better fits the problem.

## How to Write Memoized Search

### Method 1

1.  Write down the DP state and transition equation for the problem.
2.  Write a DFS function from them.
3.  Add a memoization array.

Example:

$dp_{i} = \max\{dp_{j}+1\}\quad (1 \leq j < i \land a_{j}<a_{i})$ (longest increasing subsequence)

Convert it to:

=== "C++"
    ```cpp
    int dfs(int i) {
      if (mem[i] != -1) return mem[i];
      int ret = 1;
      for (int j = 1; j < i; j++)
        if (a[j] < a[i]) ret = max(ret, dfs(j) + 1);
      return mem[i] = ret;
    }
    
    int main() {
      memset(mem, -1, sizeof(mem));
      // Input omitted.
      int ret = 0;
      for (int j = 1; j <= n; j++) {
        ret = max(ret, dfs(j));
      }
      cout << ret << endl;
    }
    ```

=== "Python"
    ```python
    def dfs(i):
        if mem[i] != -1:
            return mem[i]
        ret = 1
        for j in range(1, i):
            if a[j] < a[i]:
                ret = max(ret, dfs(j) + 1)
        mem[i] = ret
        return mem[i]
    ```

### Method 2

1.  Write a brute-force search program for the problem, preferably [DFS](../search/dfs.md).
2.  Modify this DFS into a DFS that does not need external variables.
3.  Add a memoization array.

Example: the "Herb Gathering" example in this article.
