author: Ir1d, ShadowsEpic, Fomalhauthmj, siger-young, MingqiHuang, Xeonacid, hsfzLZH1, orzAtalod, NachtgeistW

This page gives a brief introduction to binary lifting.

## Definition

Binary lifting, as the name suggests, means "doubling". When performing recurrence, if the state space is very large, the usual linear recurrence cannot meet the time and space complexity requirements. We can use the doubling method to only compute the values at positions that are integer powers of $k$ in the state space as representatives. When we need values at other positions, we use the property that "any integer can be represented as the sum of several powers of $k$" to combine the previously computed representative values to obtain the desired value. Therefore, using the binary lifting algorithm also requires that the state space of the problem has divisibility with respect to powers of $k$. Typically, $k$ is taken as $2$.[^ref1]

This method is applied in many algorithms, among which the most common are the RMQ problem and finding [LCA (Lowest Common Ancestor)](../graph/lca.md).

## Applications

### RMQ Problem

See also: [RMQ Topic](../topic/rmq.md)

RMQ stands for Range Maximum/Minimum Query, representing the maximum (minimum) value in a range. The method using binary lifting to solve RMQ problems is [Sparse Table](../ds/sparse-table.md).

### Binary Lifting on Trees for LCA

See also: [Lowest Common Ancestor](../graph/lca.md)

## Example Problems

### Problem 1

???+ note "Example Problem"
    How can we weigh all weights in the range $[0,31]$ using as few weights as possible? (Weights can only be placed on one side of the balance)

??? note "Solution Approach"
    The answer is to use the five weights 1, 2, 4, 8, 16, which can weigh all weights in the range $[0,31]$. Similarly, to weigh all weights in the range $[0,127]$, we can use the seven weights 1, 2, 4, 8, 16, 32, 64. Each time we choose a weight that is a power of 2, we can weigh any desired weight with very few weights.

    Why is it "very few"? Because to weigh all weights in the range $[0,1023]$, we only need 10 weights; to weigh all weights in the range $[0,1048575]$, we only need 20 weights. If our target weight range doubles, we only need to add 1 weight. This is called "logarithmic" growth rate, because the required number of weights is proportional to the logarithm of the target weight range.

### Problem 2

???+ note "Example Problem"
    Given a ring of length $n$ and a constant $k$, each step jumps from the $i$-th node to the $(i+k)\bmod n+1$-th node, for a total of $m$ jumps. Each node has a value denoted as $a_i$. Find the sum of the values at the starting nodes of the $m$ jumps, modulo $10^9+7$.

    Data range: $1\leq n\leq 10^6$, $1\leq m\leq 10^{18}$, $1\leq k\leq n$, $0\le a_i\le 10^9$.

??? note "Solution Approach"
    Obviously, we cannot simulate $m$ jumps by brute force here. Since $m$ can be as large as $10^{18}$, brute-force simulation would be too time-consuming.

    Therefore, we need to do some preprocessing to integrate information in advance, so that we can get results quickly during queries. Recording the results for every possible jump count would be impractical in terms of both time and space.

    So how should we preprocess? Let's look at the first example problem. Do you have any ideas now?

    Back to this problem. We need to preprocess some information, and then use this preprocessed information to quickly compute the answer. At the same time, the preprocessed information cannot be too much. So we can preprocess information in units of powers of 2, which means during preprocessing we only need to handle a small amount of information, and during integration we don't need much effort either.

    For this problem, we preprocess the results (ending node and node value sum) after jumping 1, 2, 4, 8, etc. steps from each starting node. Then, if we need to jump 13 steps, we just need to jump 1+4+8 steps. That is, first jump 1 step from the starting node, then jump 4 steps from the resulting node, and then jump 8 steps, while accumulating the preprocessed node value sums, so we can know the node value sum after jumping 13 steps.

    For $2^i$ steps starting from each node, we record `go[i][x]` to denote the ending node after node $x$ jumps $2^i$ steps, and `sum[i][x]` to denote the accumulated node value sum after node $x$ jumps $2^i$ steps. During preprocessing, with two nested loops, for the information of jumping $2^i$ steps, we can think of it as first jumping $2^{i-1}$ steps, then jumping $2^{i-1}$ steps again, because clearly $2^{i-1}+2^{i-1}=2^i$. That is, we have `sum[i][x] = sum[i-1][x]+sum[i-1][go[i-1][x]]`, and `go[i][x] = go[i-1][go[i-1][x]]`.

    Of course, there are some implementation details to pay attention to. To ensure completeness and no duplication in the accumulation, we generally preprocess the node value sums in a "left-closed, right-open" manner. That is, for jumping 1 step, we only record the node value sum of that node; for jumping 2 steps, we only record the node value sums of that node and its next node. In essence, we never include the ending node's value in the sum. This way, during preprocessing, we only need to directly add the two parts of the node value sums together, without worrying about the ending node of the first segment and the starting node of the second segment being counted twice.

    For this problem, $m\leq 10^{18}$, although it seems terrifying, we only need to preprocess $i$ up to 65 to solve it easily, which is much faster than brute-force enumeration. In technical terms, the [time complexity](./complexity.md) of this approach is $\Theta(n\log m)$ for preprocessing and $\Theta(\log m)$ per query.

??? note "Reference Code"
    ```cpp
    #include <cstdio>
    using namespace std;
    
    constexpr int mod = 1000000007;
    
    int modadd(int a, int b) {
      if (a + b >= mod) return a + b - mod;  // Subtraction instead of modulo to speed up
      return a + b;
    }
    
    int vi[1000005];
    
    int go[75][1000005];  // Make the array slightly larger to avoid overflow, smaller dimension first
    int sum[75][1000005];
    
    int main() {
      int n, k;
      scanf("%d%d", &n, &k);
      for (int i = 1; i <= n; ++i) {
        scanf("%d", vi + i);
      }
    
      for (int i = 1; i <= n; ++i) {
        go[0][i] = (i + k) % n + 1;
        sum[0][i] = vi[i];
      }
    
      int logn = 31 - __builtin_clz(n);  // A quick way to get the logarithm
      for (int i = 1; i <= logn; ++i) {
        for (int j = 1; j <= n; ++j) {
          go[i][j] = go[i - 1][go[i - 1][j]];
          sum[i][j] = modadd(sum[i - 1][j], sum[i - 1][go[i - 1][j]]);
        }
      }
    
      long long m;
      scanf("%lld", &m);
    
      int ans = 0;
      int curx = 1;
      for (int i = 0; m; ++i) {
        if (m & (1ll << i)) {  // See bitwise operations, checks if the i-th bit of m is 1
          ans = modadd(ans, sum[i][curx]);
          curx = go[i][curx];
          m ^= 1ll << i;  // Set the i-th bit to 0
        }
      }
    
      printf("%d\n", ans);
    }
    ```

[^ref1]: Quoted from Li Yudong's "Algorithm Competition Advanced Guide" 0x06. Binary Lifting section
