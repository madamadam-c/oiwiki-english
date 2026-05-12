## Introduction

In competitive programming, some problems can be solved with binary search. However, when such problems have many queries and directly binary searching for each query may lead to TLE, parallel binary search is useful. The main idea of parallel binary search is to solve multiple queries together. Therefore, it is an offline algorithm.

> Problems solvable by parallel binary search need to satisfy the following properties:
>
> 1.  The answer to each query is binary-searchable.
>
> 2.  **The contributions of modifications to answer checking are independent**, and modifications do not affect one another's effects.
>
> 3.  If a modification contributes to answer checking, its contribution is a fixed value independent of the checking criterion.
>
> 4.  Contributions satisfy commutativity and associativity, and are additive.
>
> 5.  The problem allows offline algorithms.
>
>     -- Xu Haoran, "A Brief Discussion on Several Non-classical Solutions to Data Structure Problems"

## Explanation

Let $[l,r]$ be the value range of the answer, and $[L,R]$ be the domain of the answer. In other words, when computing answers, we only consider operations and queries whose indices are in interval $[L,R]$, and the answers to these queries lie in $[l,r]$.

-   First store all operations in an array **in chronological order**, then start divide and conquer.
-   At each divide-and-conquer level, use a data structure (commonly a Fenwick tree) to determine the relation between the current query's answer and $mid$.
-   According to the relation between the queried answer and $mid$ (less than or equal to $mid$, or greater than $mid$), split the current operation sequence into two parts, $q1$ and $q2$, and process them recursively.
-   When $l=r$, the answer has been found. Record it and return.

Note that during parallel binary search, if the value range currently being processed is $[l,r]$, then queries whose final answers are not in $[l,r]$ will be handled at other times.

## Process

Notes:

1.  For readability, the code in this article may not use the common style used in actual contests.
2.  If some code is hard to understand, please first refer to the explanation of the previous problem, because content already explained is not repeated for brevity.

Start with ordinary binary search:

### Querying the Global k-th Smallest Value

> **Problem 1** Query the $k$-th smallest number in a sequence.

Of course, we can sort directly. What if we use binary search? Use a data structure to record how many numbers are in each value range, then guess with binary search and verify with the data structure.

> **Problem 2** Query the $k$-th smallest number in a sequence multiple times.

We can run a binary search for each query, but we can also binary search all queries together.

First consider the essence of binary search. Suppose we need to guess a number in $[l,r]$. After each guess, we know whether the guess is too large, too small, or exactly right. We could enumerate from $l$ to $r$, but a better method is binary search: guess that the answer is $m = \lfloor\frac{l + r}{2}\rfloor$, verify whether $m$ is correct, and then adjust the boundary. This gives $O(\log n)$ complexity per query. If there are $q$ queries, the time complexity is $O(q\log n)$.

Returning to all current queries, we can guess that every query's answer is $mid$, then verify one by one whether each query's answer should be less than or equal to $mid$ or greater than $mid$. Split the queries into two parts (not greater than / greater than), and continue binary searching each part. Note: if a query's answer is greater than $mid$, then before moving it to the right side, its $k$ must be updated. That is, if the current sequence has $t$ numbers less than or equal to $mid$, then after splitting, the query is actually asking for the $k - t$-th smallest number in the right interval. If a part reaches $l = r$, finish binary searching that part. Using segment-tree-related ideas, each time we divide the whole possible answer interval $[1,n]$ (assuming it has been discretized) into several parts. This division is performed $O(\log n)$ times, and each division processes the whole operation sequence once. If processing the whole sequence and supporting the corresponding queries takes $O(T)$ time, then the time complexity of parallel binary search is $O(T\log n)$.

Reference code:

???+ note "Implementation"
    ```cpp
    struct Query {
      int id, k;  // The id of this query, and its k
    };
    
    int ans[N], a[N];  // ans[i] is the answer to query i; a is the original sequence
    int val[N], cnt[N];  // After discretization, record each value and its count
    
    // Return the number of elements in the original sequence whose values are in [l,r]
    int check(int l, int r) {
      int res = 0;
      for (int i = l; i <= r; i++) {
        res += cnt[i];
      }
      return res;
    }
    
    // Parallel binary search
    void solve(int l, int r, vector<Query> q) {
      int m = (l + r) / 2;
      if (l == r) {
        for (unsigned i = 0; i < q.size(); i++) ans[q[i].id] = val[l];
        return;
      }
      vector<Query> q1, q2;
      int t = check(l, m);
      for (unsigned i = 0; i < q.size(); i++) {
        if (q[i].k <= t)
          q1.push_back(q[i]);
        else
          q[i].k -= t, q2.push_back(q[i]);
      }
      solve(l, m, q1), solve(m + 1, r, q2);
      return;
    }
    ```

### Querying the Range k-th Smallest Value

> **Problem 3** Query the range $k$-th smallest number in a sequence multiple times.

When queries involve a specified interval, applying the previous binary search method makes the time complexity of the `check` function explode. Still consider the relation between a query and the midpoint $m$ of the value range. If there are $t$ numbers less than or equal to $m$ in the query interval, and the query asks for the $k$-th smallest number in the interval, then when $k \leq t$, the answer should be less than or equal to $m$; otherwise, it should be greater than $m$. Pay attention to boundary cases. Here we need to record the number of elements in an interval that are less than or equal to a given value, i.e. point add and range sum, which can be handled quickly with a Fenwick tree. To improve efficiency, only count numbers in the sequence whose values are in the current value interval $[l,r]$. That is, before recursing further, split not only the queries but also the currently processed numbers into two halves according to their value ranges.

Reference code (key part):

???+ note "Implementation"
    ```cpp
    struct Num {
      int p, x;
    };  // The value of the p-th element in the sequence is x
    
    struct Query {
      int l, r, k, id;
    };  // A query with id id asking for the k-th smallest number in [l,r]
    
    int ans[N];
    void add(int p, int x);  // Fenwick tree: add x at position p
    int query(int p);        // Fenwick tree: sum over [1,p]
    void clear();            // Fenwick tree: clear
    
    void solve(int l, int r, vector<Num> a, vector<Query> q)
    // a contains numbers from the given sequence whose values are in [l,r]
    {
      int m = (l + r) / 2;
      if (l == r) {
        for (unsigned i = 0; i < q.size(); i++) ans[q[i].id] = l;
        return;
      }
      vector<Num> a1, a2;
      vector<Query> q1, q2;
      for (unsigned i = 0; i < a.size(); i++)
        if (a[i].x <= m)
          a1.push_back(a[i]), add(a[i].p, 1);
        else
          a2.push_back(a[i]);
      for (unsigned i = 0; i < q.size(); i++) {
        int t = query(q[i].r) - query(q[i].l - 1);
        if (q[i].k <= t)
          q1.push_back(q[i]);
        else
          q[i].k -= t, q2.push_back(q[i]);
      }
      clear();
      solve(l, m, a1, q1), solve(m + 1, r, a2, q2);
      return;
    }
    ```

Below is a more contest-style implementation using parallel binary search for [【模板】可持久化线段树 2](https://www.luogu.com.cn/problem/P3834).

???+ note "Reference Code"
    ```cpp
    --8<-- "docs/misc/code/parallel-binsearch/parallel-binsearch_1.cpp"
    ```

### Range k-th Smallest with Modifications

> **Problem 4**  [Dynamic Rankings](https://pintia.cn/problem-sets/91827364500/exam/problems/91827365611) Given a sequence, support point modifications and range $k$-th smallest queries.

A modification can be understood as deleting a number from the original sequence and then adding another. For convenience, queries and modifications are collectively called "operations". Since later operations depend on previous operations, we cannot separate counting and query processing as in Problem 3. Therefore, store all operations in one array, distinguish their types with a flag, and process each operation in order. To handle the Fenwick tree conveniently, each modification can be split into an erase operation and an insert operation.

**Optimizations**

1.  Notice that each classification of operations only changes the operation order, so we can operate directly on the original array. In implementation, replace the arrays $q, a$ that record operations during binary search with one large global array. The recorded information during binary search becomes $L, R$, meaning which interval of the global array contains the currently processed operations. Use temporary arrays to record the current classification, then write the temporary array contents back to the original array before recursing further.
2.  Clearing the Fenwick tree every time causes the time complexity to explode. Instead, record the modified positions whenever the Fenwick tree is used (this is already implemented by the temporary arrays mentioned in 1), and after this operation finishes, add $-1$ at the original positions to clear quickly.
3.  The initial construction of the sequence can be simplified as insert operations.

Reference code (key part):

???+ note "Implementation"
    ```cpp
    struct Opt {
      int x, y, k, type, id;
      // For a query, type = 1; x and y are interval boundaries, k is the queried rank.
      // For a modification, type = 0; x is the modified position, y is the new value.
      // k indicates whether the current operation is insertion (1) or erasure (-1),
      // and is used when updating the Fenwick tree.
      // id records the original id of each operation, because binary search shuffles the order.
    };
    
    Opt q[N], q1[N], q2[N];
    // q stores all operations.
    // During binary search, operations assigned to the left are stored in q1,
    // and operations assigned to the right are stored in q2.
    int ans[N];
    void add(int p, int x);
    int query(int p);  // Fenwick tree function; meaning as in Problem 3
    
    void solve(int l, int r, int L, int R)
    // Current value range is [l,r], and the processed operation interval is [L,R]
    {
      if (l > r || L > R) return;
      int cnt1 = 0, cnt2 = 0, m = (l + r) / 2;
      // cnt1 and cnt2 are the numbers of operations assigned to the left and right
      if (l == r) {
        for (int i = L; i <= R; i++)
          if (q[i].type == 1) ans[q[i].id] = l;
        return;
      }
      for (int i = L; i <= R; i++)
        if (q[i].type == 1) {  // Query: classify it
          int t = query(q[i].y) - query(q[i].x - 1);
          if (q[i].k <= t)
            q1[++cnt1] = q[i];
          else
            q[i].k -= t, q2[++cnt2] = q[i];
        } else
          // Modification: update the Fenwick tree and classify it
          if (q[i].y <= m)
            add(q[i].x, q[i].k), q1[++cnt1] = q[i];
          else
            q2[++cnt2] = q[i];
      for (int i = 1; i <= cnt1; i++)
        if (q1[i].type == 0) add(q1[i].x, -q1[i].k);  // Clear the Fenwick tree
      for (int i = 1; i <= cnt1; i++) q[L + i - 1] = q1[i];
      for (int i = 1; i <= cnt2; i++)
        q[L + cnt1 + i - 1] = q2[i];  // Merge elements from temporary arrays back
      solve(l, m, L, L + cnt1 - 1), solve(m + 1, r, L + cnt1, R);
      return;
    }
    ```

### Optimization for Static Sequences

> **Problem 5**  [【模板】可持久化线段树 2](https://www.luogu.com.cn/problem/P3834) Given a sequence, query the range $k$-th smallest value.

Both tree-of-trees and parallel binary search solve the range $k$-th smallest problem with modifications in $O(n \log^2 n)$ time. However, the static range $k$-th smallest problem can be solved with a persistent segment tree in $O(n \log n)$ time, while almost all parallel-binary-search implementations for the static range $k$-th smallest problem run in $O(n \log^2 n)$ time, risking TLE on large data. Here we assume the value range and sequence length are of the same order; if they are not, discretization can transform them into the same order.

**Optimization**

1.  For each round of partitioning, if there are $t$ numbers less than or equal to $mid$ in the current sequence, then after partitioning, a query sent to the right interval is actually asking for the $k - t$-th smallest number. Thus, queries assigned to the right interval are modified. If the original answer value range is $[L,R]$ and the answer value range in some partition is $[l,r]$, then for the queries participating in this partition, the influence of all values in $[L,l)$ has already been eliminated earlier.
2.  Since each partition must depend only on the current answer value range $[l,r]$, the Fenwick tree needs to be loaded and cleared many times.

What if partitioning does not depend only on the current answer value range?

This leads to an optimization related to the global sequence: maintain a pointer $pos$ to track the $mid$ (divide-and-conquer center) of each partition. Set the indices corresponding to all elements $\leq pos$ to $1$ in the Fenwick tree, and set all other positions to $0$. Before each partition, move $pos$ and update the Fenwick tree. The number of moves of pointer $pos$ is on the same order as $n \log n$. During partitioning, query the corresponding interval in the Fenwick tree for each query. If it satisfies the condition, assign it to the left interval; otherwise assign it to the right interval. **No modification to query information is needed**.

Because the divide-and-conquer center needs to be tracked, $pos$ must accurately update the Fenwick tree. Before parallel binary search, sort the sequence by element value and record the corresponding indices. When the pointer moves, modify the corresponding indices in the Fenwick tree. For most **problems that can be solved by parallel binary search and have no modifications**, this optimization can be applied to greatly reduce data structure usage.

Because many Fenwick tree loading and clearing operations are removed, applying this optimization usually significantly improves the efficiency of parallel binary search, even if it is only a constant-factor optimization. For the static range $k$-th smallest problem, its efficiency is not worse than the persistent segment tree with better asymptotic complexity. It is worth noting that an $O(n \log n)$ parallel-binary-search implementation also exists for the static range $k$-th smallest problem.

Reference code (key part):

???+ note "Implementation"
    ```cpp
    struct Query {
      int i, l, r, k;
    };  // The i-th query asks for the k-th smallest value in [l,r]
    
    Query s[200005], t1[200005], t2[200005];
    int n, m, cnt, pos, p[200005], ans[200005];
    pair<int, int> a[200005];
    
    void add(int x, int y);  // Fenwick tree: add y at position x
    int sum(int x);          // Fenwick tree: prefix sum over [1,x]
    
    // Currently processed queries are [l,r], and the answer value range is [ql,qr]
    void overall_binary(int l, int r, int ql, int qr) {
      if (l > r) return;
      if (ql == qr) {
        for (int i = l; i <= r; i++) ans[s[i].i] = ql;
        return;
      }
      int cnt1 = 0, cnt2 = 0, mid = (ql + qr) >> 1;
      // Track the divide-and-conquer center; values in [1,pos] are loaded
      while (pos <= n - 1 && a[pos + 1].first <= mid)
        add(a[pos + 1].second, 1), ++pos;
      while (pos >= 1 && a[pos].first > mid) add(a[pos].second, -1), --pos;
    
      for (int i = l; i <= r; i++) {
        int now = sum(s[i].r) - sum(s[i].l - 1);
        if (s[i].k <= now)
          t1[++cnt1] = s[i];
        else
          t2[++cnt2] = s[i];  // Note: query information should not be modified
      }
      for (int i = 1; i <= cnt1; i++) s[l + i - 1] = t1[i];
      for (int i = 1; i <= cnt2; i++) s[l + cnt1 + i - 1] = t2[i];
    
      overall_binary(l, l + cnt1 - 1, ql, mid);
      overall_binary(l + cnt1, r, mid + 1, qr);
    }
    
    int main() {
      scanf("%d%d", &n, &m);
      for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i].first);
        a[i].second = i;
        p[++cnt] = a[i].first;
      }
      sort(a + 1, a + n + 1);  // Sort the sequence for discretization
      sort(p + 1, p + n + 1);
      cnt = unique(p + 1, p + n + 1) - p - 1;
      for (int i = 1; i <= n; i++)
        a[i].first = lower_bound(p + 1, p + cnt + 1, a[i].first) - p;
      // Reading queries is omitted
      overall_binary(1, m, 1, cnt);
      for (int i = 1; i <= n; i++) printf("%d\n", p[ans[i]]);
      return 0;
    }
    ```

### Range Predecessor and Successor

> **Problem 6** In a sequence, repeatedly query the predecessor of $k$ in an interval (the largest number strictly smaller than $k$) or the successor (the smallest number strictly greater than $k$). Such a number is guaranteed to exist.

Take predecessor as an example. A data-structure solution usually first queries how many numbers in the interval are strictly smaller than $k$ (let the count be $x$), then queries the interval's $x$-th smallest number. For successor, query how many numbers in the interval are not greater than $k$ (count $x$), then query the interval's $x+1$-th smallest number.

Consider using parallel binary search to solve this problem: parallel binary search is an efficient offline algorithm for range $k$-th smallest queries, and [CDQ divide and conquer](./cdq-divide.md) can efficiently compute ranks inside intervals offline. First run CDQ divide and conquer to compute ranks, then use parallel binary search to obtain predecessors and successors inside intervals.

This problem can also be solved offline in one pass using CDQ divide and conquer with a segment tree, but it is much less efficient than running CDQ divide and conquer plus parallel binary search in two passes.

### Constructing a Monotone Sequence

> **Problem 7**  [Sequence](https://www.luogu.com.cn/problem/P4597) Given a sequence, each operation may change one number by $+1$ or $−1$. The sequence must be made nondecreasing, and the modified sequence may only contain numbers that appeared before modification. Output the minimum number of operations.

This type of problem can also be solved with dynamic programming or regret greedy algorithms.

Under the premise of minimizing the number of operations, there must exist a solution such that every number in the final sequence appeared in the original sequence. This conclusion can be proved by mathematical induction. Since the problem does not require the final sequence itself, it becomes a problem of finding the minimum number of operations.

Since the final sequence must be nondecreasing, parallel binary search can be used. Each round of parallel binary search determines the value range of the final sequence interval $[l,r]$, where the current answer value range is $[ql,qr]$. Let $mid=\lfloor\frac{ql + qr}{2}\rfloor$. At the start of each binary search round, assume by default that all numbers are assigned to $[mid+1,qr]$ (the number assigned to $[ql,mid]$ is set to $0$), and set the initial cost to the number of operations needed to set the whole sequence interval $[l,r]$ to $mid+1$. Then enumerate each position $i$ in interval $[l,r]$ and compute the total cost of setting $[l,i]$ to $mid$ and $[i+1,r]$ to $mid+1$. If this is better than the previous cost, update the minimum cost and the number of values to assign to $[ql,mid]$.

The partitioning already ensures that the final sequence's monotonicity is not broken. Also, because the minimum operation count is chosen each time, for numbers finally assigned to the left interval, taking $mid$ must be better than taking $mid+1$. Therefore, the sequence obtained by parallel binary search is nondecreasing and has the minimum number of operations. Compute and output the operation count.

Reference code (key part):

???+ note "Implementation"
    ```cpp
    int a[500005], ans[500005];  // a: original sequence; ans: constructed sequence
    
    void overall_binary(int l, int r, int ql, int qr) {
      if (l > r) return;
      if (ql == qr) {
        for (int i = l; i <= r; i++) ans[i] = ql;
        return;
      }
      int cnt = 0,
          mid = ql + ((qr - ql) >> 1);  // Initially fill all with mid+1 and assign to right
      long long res = 0ll, sum = 0ll;
      for (int i = l; i <= r; i++) sum += abs(a[i] - (mid + 1));
      res = sum;
      for (int i = l; i <= r;
           i++) {  // Try changing [l,i] from mid+1 to mid and assigning it left
        sum -= abs(a[i] - (mid + 1));
        sum += abs(a[i] - mid);
        if (sum < res) cnt = i - l + 1, res = sum;  // [l,i] is better as mid; update
      }
      overall_binary(l, l + cnt - 1, ql, mid);
      overall_binary(l + cnt, r, mid + 1, qr);
    }
    ```

### Practice Problems

[「国家集训队」矩阵乘法](https://www.luogu.com.cn/problem/P1527)

[「POI2011 R3 Day2」流星 Meteors](https://loj.ac/p/2169)

[二逼平衡树](https://loj.ac/p/106)

[\[BalticOI 2004\] Sequence 数字序列](https://www.luogu.com.cn/problem/P4331)

## References

-   Xu Haoran, "A Brief Discussion on Several Non-classical Solutions to Data Structure Problems"
