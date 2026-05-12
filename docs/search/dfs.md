## Introduction

DFS is a concept in graph theory; see the [DFS (graph theory)](../graph/dfs.md) page for details. In **search algorithms**, this term often refers to algorithms that conveniently implement brute-force enumeration with recursive functions. They are somewhat similar to DFS in graph theory, but they are not exactly the same.

## Explanation

Consider this example:

???+ note "Example"
    Decompose the positive integer $n$ into $3$ positive integers, such as $6=1+2+3$. Each later number must be greater than or equal to the previous number. Output all solutions.

For this problem, what should we do if we do not know search? Naturally, use three nested loops. The reference code is as follows:

???+ note "Implementation"
    === "C++"
        ```cpp
        for (int i = 1; i <= n; ++i)
          for (int j = i; j <= n; ++j)
            for (int k = j; k <= n; ++k)
              if (i + j + k == n) printf("%d = %d + %d + %d\n", n, i, j, k);
        ```
    
    === "Python"
        ```python
        for i in range(1, n + 1):
            for j in range(i, n + 1):
                for k in range(j, n + 1):
                    if i + j + k == n:
                        print("%d = %d + %d + %d" % (n, i, j, k))
        ```
    
    === "Java"
        ```Java
        for (int i = 1; i < n + 1; i++) {
            for (int j = i; j < n + 1; j++) {
                for (int k = j; k < n + 1; k++) {
                    if (i + j + k == n) System.out.printf("%d = %d + %d + %d%n", n, i, j, k);
                }
            }
        }
        ```

What if we decompose it into four integers? Add another loop? What if we decompose it into at most $m$ integers?

This is where recursive search is needed. This type of search algorithm divides the target to be searched into several "levels". Each level makes decisions based on the states of previous levels until the target state is reached.

Consider the problem above: decompose the positive integer $n$ into the sum of no more than $m$ positive integers, where each later number must be greater than or equal to the previous number, and output all solutions.

Suppose a solution decomposes the positive integer $n$ into the sum of $k$ positive integers $a_1, a_2, \ldots, a_k$. We divide the problem into levels, where level $i$ decides $a_i$. To make the decision at level $i$, we need to record three state variables: $n-\sum_{j=1}^i{a_j}$, which represents the sum of all remaining positive integers; $a_{i-1}$, which represents the positive integer from the previous level and ensures the positive integers are nondecreasing; and $i$, which ensures that we output at most $m$ positive integers. To record a solution, we use the array `arr`, whose $i$-th entry represents $a_i$. Note that `arr` is essentially a stack of length $i$.

The code is as follows:

???+ note "Implementation"
    === "C++"
        ```cpp
        int m, arr[103];  // arr records the solution
        
        void dfs(int n, int i, int a) {
          if (n == 0) {
            for (int j = 1; j <= i - 1; ++j) printf("%d ", arr[j]);
            printf("\n");
          }
          if (i <= m) {
            for (int j = a; j <= n; ++j) {
              arr[i] = j;
              dfs(n - j, i + 1, j);  // Think carefully about what this line means.
            }
          }
        }
        
        // Main function
        scanf("%d%d", &n, &m);
        dfs(n, 1, 1);
        ```
    
    === "Python"
        ```python
        arr = [0] * 103  # arr records the solution
        
        
        def dfs(n, i, a):
            if n == 0:
                print(arr[1:i])
            if i <= m:
                for j in range(a, n + 1):
                    arr[i] = j
                    dfs(n - j, i + 1, j)  # Think carefully about what this line means.
        
        
        # Main function
        n, m = map(int, input().split())
        dfs(n, 1, 1)
        ```
    
    === "Java"
        ```Java
        static int m;
        
        // arr records the solution
        static int[] arr = new int[103];
        
        public static void dfs(int n, int i, int a) {
            if (n == 0) {
                for (int j = 1; j <= i - 1; j++) System.out.printf("%d ", arr[j]);
                System.out.println();
            }
            if (i <= m) {
                for (int j = a; j <= n; ++j) {
                    arr[i] = j;
                    dfs(n - j, i + 1, j); // Think carefully about what this line means.
                }
            }
        }
        
        // Main function
        final int N = new Scanner(System.in).nextInt();
        m = new Scanner(System.in).nextInt();
        dfs(N, 1, 1);
        ```

## Examples

???+ note "[Luogu P1706 Permutation Problem](https://www.luogu.com.cn/problem/P1706)"
    ```cpp
    --8<-- "docs/search/code/dfs/dfs_1.cpp"
    ```
