This page briefly introduces digit DP.

## Introduction

A digit means one position of a number after decomposing it into ones, tens, hundreds, thousands, and so on, focusing on the value at each position. For a decimal number, each digit is in $0\sim 9$; other bases are analogous.

Digit DP is used to solve a specific class of problems. These problems are usually easy to recognize and generally have the following characteristics:

1.  They ask for the number of integers satisfying certain conditions; that is, the final goal is counting.

2.  After transformation, these conditions can be understood and checked using the idea of digits.

3.  The input provides a numeric interval, or sometimes only an upper bound, as the range to count over.

4.  The upper bound is very large, for example $10^{18}$, so brute-force enumeration and checking would time out.

The basic principle of digit DP:

Consider how humans count. The most naive way to count is to start from small numbers and add one each time. But for numbers with many digits, this process contains many repeated parts. For example, counting from 7000 to 7999, from 8000 to 8999, and from 9000 to 9999 is very similar: the last three digits all go from 000 to 999, and only the thousands digit differs. Therefore, we can merge these processes and store the counting results they produce in a common array. The states of this array are designed according to the problem requirements, and transitions are performed by recurrence or DP.

Digit DP also commonly uses standard counting techniques, such as splitting the answer for an interval into the difference of two prefixes: $\mathit{ans}_{[l, r]} = \mathit{ans}_{[0, r]}-\mathit{ans}_{[0, l - 1]}$.

Once we have the common answer array, the next step is to count the answer. This can be done with memoized search or iterative recurrence. To count all answers not exceeding the upper bound without duplicates or omissions, enumerate each digit from high to low, consider which digits can be placed at each position, and finally use the common answer array to accumulate the result.

Next, let us look at several concrete problems.

## Example 1

???+ note "Example 1 [Luogu P2602: Digit Counting](https://www.luogu.com.cn/problem/P2602)"
    Problem summary: Given two positive integers $a,b$, find how many times each digit appears among all integers in $[a,b]$.

### Method 1

#### Explanation

For all full $i$-digit numbers, each digit appears the same number of times. Therefore, let array $\mathit{dp}_i$ denote how many times each digit appears among all full $i$-digit numbers, temporarily ignoring leading zeros. Then $\mathit{dp}_i=10 \times \mathit{dp}_{i-1}+10^{i-1}$. The first term is the contribution from the first $i-1$ digits, and the second term is the contribution from the $i$-th digit.

With the $\mathit{dp}$ array, consider how to count the answer. Split the upper bound into digits and enumerate from high to low. When we are not tight to the upper bound, the following digits can be chosen arbitrarily. When we are tight to the upper bound, the following digits are constrained by the upper bound. Compute the contribution in two parts. Finally handle leading zeros: when the $i$-th digit is a leading $0$, positions $1$ through $i-1$ are also all $0$, meaning the answer for filling $i-1$ digits was overcounted and must be subtracted.

#### Implementation

???+ note "Reference Code"
    ```cpp
    #include <cstdio>
    using namespace std;
    constexpr int N = 15;
    using ll = long long;
    ll l, r, dp[N], mi[N];
    ll ans1[N], ans2[N];
    int a[N];
    
    void solve(ll n, ll *ans) {
      ll tmp = n;
      int len = 0;
      while (n) a[++len] = n % 10, n /= 10;
      for (int i = len; i >= 1; --i) {
        for (int j = 0; j < 10; j++) ans[j] += dp[i - 1] * a[i];
        for (int j = 0; j < a[i]; j++) ans[j] += mi[i - 1];
        tmp -= mi[i - 1] * a[i], ans[a[i]] += tmp + 1;
        ans[0] -= mi[i - 1];
      }
    }
    
    int main() {
      scanf("%lld%lld", &l, &r);
      mi[0] = 1ll;
      for (int i = 1; i <= 13; ++i) {
        dp[i] = dp[i - 1] * 10 + mi[i - 1];
        mi[i] = 10ll * mi[i - 1];
      }
      solve(r, ans1), solve(l - 1, ans2);
      for (int i = 0; i < 10; ++i) printf("%lld ", ans1[i] - ans2[i]);
      return 0;
    }
    ```

### Method 2

#### Explanation

This problem can also be solved with memoized search. $\mathit{dp}_i$ denotes the answer for $i$ remaining digits when the search is not tight to the bound and has no leading zeros.

See the code comments for details.

#### Process

???+ note "Reference Code"
    ```cpp
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    using namespace std;
    using ll = long long;
    constexpr int N = 50005;
    ll a, b;
    ll f[15], ksm[15], p[15], now[15];
    
    ll dfs(int u, int x, bool f0,
           bool lim) {  // u is the number of digits; f0 means leading zeros; lim means tight to the bound.
      if (!u) {
        if (f0) f0 = false;
        return 0;
      }
      if (!lim && !f0 && (~f[u])) return f[u];
      ll cnt = 0;
      int lst = lim ? p[u] : 9;
      for (int i = 0; i <= lst; i++) {  // Enumerate the digit to place here.
        if (f0 && i == 0)
          cnt += dfs(u - 1, x, 1, lim && i == lst);  // Handle leading zeros.
        else if (i == x && lim && i == lst)
          cnt += now[u - 1] + 1 +
                 dfs(u - 1, x, 0,
                     lim && i == lst);  // The already enumerated prefix is tight to the given upper bound.
        else if (i == x)
          cnt += ksm[u - 1] + dfs(u - 1, x, 0, lim && i == lst);
        else
          cnt += dfs(u - 1, x, 0, lim && i == lst);
      }
      if ((!lim) && (!f0)) f[u] = cnt;  // Memoize only when not tight and without leading zeros.
      return cnt;
    }
    
    ll gans(ll d, int dig) {
      int len = 0;
      memset(f, -1, sizeof(f));
      while (d) {
        p[++len] = d % 10;
        d /= 10;
        now[len] = now[len - 1] + p[len] * ksm[len - 1];
      }
      return dfs(len, dig, 1, 1);
    }
    
    int main() {
      scanf("%lld%lld", &a, &b);
      ksm[0] = 1;
      for (int i = 1; i <= 12; i++) ksm[i] = ksm[i - 1] * 10ll;
      for (int i = 0; i < 9; i++) printf("%lld ", gans(b, i) - gans(a - 1, i));
      printf("%lld\n", gans(b, 9) - gans(a - 1, 9));
      return 0;
    }
    ```

## Example 2

???+ note "Example 2 [HDU 2089: Do Not 62](https://acm.hdu.edu.cn/showproblem.php?pid=2089)"
    Problem summary: Count how many numbers in an interval have neither digit 4 nor consecutive digits 62.

### Explanation

For the constraint of no digit 4, it is enough to check during enumeration and simply not enumerate 4, so this constraint does not need memoized state. For 62, two digits are involved: whether the previous digit is 6 or not leads to different counts, so the state must record these possibilities. $\mathit{dp}_{\mathit{pos},\mathit{sta}}$ denotes the number of ways at position $\mathit{pos}$ with the state indicating whether the previous digit is 6. Here $\mathit{sta}$ only needs values 0 and 1; all cases where the previous digit is not 6 can be treated identically because they do not affect the count.

### Implementation

???+ note "Reference Code"
    ```cpp
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    using namespace std;
    int x, y, dp[15][3], p[50];
    
    void pre() {
      memset(dp, 0, sizeof(dp));
      dp[0][0] = 1;
      for (int i = 1; i <= 10; i++) {
        dp[i][0] = dp[i - 1][0] * 9 - dp[i - 1][1];
        dp[i][1] = dp[i - 1][0];
        dp[i][2] = dp[i - 1][2] * 10 + dp[i - 1][1] + dp[i - 1][0];
      }
    }
    
    int cal(int x) {
      int cnt = 0, ans = 0, tmp = x;
      while (x) {
        p[++cnt] = x % 10;
        x /= 10;
      }
      bool flag = false;
      p[cnt + 1] = 0;
      for (int i = cnt; i; i--) {  // Enumerate digits from high to low.
        ans += p[i] * dp[i - 1][2];
        if (flag)
          ans += p[i] * dp[i - 1][0];
        else {
          if (p[i] > 4) ans += dp[i - 1][0];
          if (p[i] > 6) ans += dp[i - 1][1];
          if (p[i] > 2 && p[i + 1] == 6) ans += dp[i][1];
          if (p[i] == 4 || (p[i] == 2 && p[i + 1] == 6)) flag = true;
        }
      }
      return tmp - ans;
    }
    
    int main() {
      pre();
      while (~scanf("%d%d", &x, &y)) {
        if (!x && !y) break;
        if (x > y) swap(x, y);
        printf("%d\n", cal(y + 1) - cal(x));
      }
      return 0;
    }
    ```

## Example 3

???+ note "Example 3 [SCOI2009 Windy Numbers](https://loj.ac/problem/10165)"
    Problem summary: Given an interval $[l,r]$, count the numbers that satisfy **no leading $0$ and adjacent digits differ by at least $2$**.

### Explanation

First, transform the problem into a simpler form. Let $\mathit{ans}_i$ denote the number of valid integers in the interval $[1,i]$. Then the required answer is $\mathit{ans}_r-\mathit{ans}_{l-1}$.

For a number less than $n$, when read from high to low, there must be some digit whose value is smaller than the corresponding digit of $n$, while all previous digits are equal to those of $n$.

Using this property, define $f(i,st,op)$ as the number of valid numbers when the next digit to consider is the $i$-th digit from high to low, the current prefix state is $st$, and the relation between the prefix and the number being solved is $op$ ($op=1$ means equal, $op=0$ means smaller). In this problem, the prefix state is the value of the previous digit, because which values the current digit cannot take depends only on the previous digit. In other problems, this state may be the digit sum of the prefix, the $\gcd$ of all prefix digits, the prefix remainder modulo some number, or a combination of two or more such states.

The **state transition equation** is: $f(i,st,op)=\sum_{k=1}^{\mathit{maxx}} f(i+1,k,op=1~ \operatorname{and}~ k=\mathit{maxx} )\quad (|\mathit{st}-k|\ge 2)$

Here $k$ is the value of the next digit being enumerated, and $\mathit{maxx}$ is the largest digit currently allowed. If $\mathit{op}=1$, then the digit chosen here cannot exceed the corresponding digit of the number being solved; otherwise, there is no such restriction.

We observe that although the selected prefix states may differ, if the three arguments of $f$ are the same, the answer is the same. To avoid computing this answer multiple times, use [memoized search](./memo.md).

### Implementation

???+ note "Reference Code"
    ```cpp
    int dfs(int x, int st, int op)  // op=1 =; op=0 <
    {
      if (!x) return 1;
      if (!op && ~f[x][st]) return f[x][st];
      int maxx = op ? dim[x] : 9, ret = 0;
      for (int i = 0; i <= maxx; i++) {
        if (abs(st - i) < 2) continue;
        if (st == 11 && i == 0)
          ret += dfs(x - 1, 11, op & (i == maxx));
        else
          ret += dfs(x - 1, i, op & (i == maxx));
      }
      if (!op) f[x][st] = ret;
      return ret;
    }
    
    int solve(int x) {
      memset(f, -1, sizeof f);
      dim.clear();
      dim.push_back(-1);
      int t = x;
      while (x) {
        dim.push_back(x % 10);
        x /= 10;
      }
      return dfs(dim.size() - 1, 11, 1);
    }
    ```

## Example 4

???+ note "Example 4 [SPOJ MYQ10](https://www.spoj.com/problems/MYQ10/en/)"
    Problem summary: If all integers in $[n,m]$ are written by hand, how many look exactly the same in a mirror? ($n,m<10^{44}, T<10^5$)

### Explanation

Note: because mirror images are considered here, only $0,1,8$ are unchanged by reflection. Therefore, "exactly the same" here is not a palindrome in the traditional sense, but a palindrome consisting only of $0,1,8$.

First, during digit DP, only $0,1,8$ can be selected.

Second, since the values exceed the range of `long long`, $[n,m]=[1,m]-[1,n-1]$ is no longer convenient because high-precision comparison is cumbersome. Instead, check whether $n$ itself is valid and use $[n,m]=[1,m]-[1,n]+\mathrm{check}(n)$.

The mirror condition has been handled. How do we check whether the number is a palindrome?

Use a small array to record previous values. Before exceeding half the length, we only need to stay within the upper bound; after exceeding half the length, we also need to check whether the current digit equals its mirror-symmetric counterpart.

One more point: the memoized part of this problem cannot use `memset`, otherwise it will time out.

### Implementation

???+ note "Reference Code"
    ```cpp
    int check(char cc[]) {  // Special check for n.
      int strc = strlen(cc);
      for (int i = 0; i < strc; ++i) {
        if (!(cc[i] == cc[strc - i - 1] &&
              (cc[i] == '1' || cc[i] == '8' || cc[i] == '0')))
          return 0ll;
      }
      return 1ll;
    }
    
    // now: current digit; eff: effective length; fulc: tight to the bound; ful0: all zeros so far.
    int dfs(int now, int eff, bool ful0, bool fulc) {
      if (now == 0) return 1ll;
      if (!fulc && f[now][eff][ful0] != -1)  // Memoization.
        return f[now][eff][ful0];
    
      int res = 0, maxk = fulc ? dig[now] : 9;
      for (int i = 0; i <= maxk; ++i) {
        if (i != 0 && i != 1 && i != 8) continue;
        b[now] = i;
        if (ful0 && i == 0)  // All leading zeros.
          res += dfs(now - 1, eff - 1, 1, 0);
        else if (now > eff / 2)                                  // Not past the halfway point.
          res += dfs(now - 1, eff, 0, fulc && (dig[now] == i));  // Past the halfway point.
        else if (b[now] == b[eff - now + 1])
          res += dfs(now - 1, eff, 0, fulc && (dig[now] == i));
      }
      if (!fulc) f[now][eff][ful0] = res;
      return res;
    }
    
    char cc1[100], cc2[100];
    int strc, ansm, ansn;
    
    int get(char cc[]) {  // Wrapper for processing.
      strc = strlen(cc);
      for (int i = 0; i < strc; ++i) dig[strc - i] = cc[i] - '0';
      return dfs(strc, strc, 1, 1);
    }
    
    scanf("%s%s", cc1, cc2);
    printf("%lld\n", get(cc2) - get(cc1) + check(cc1));
    ```

## Example 5

???+ note "Example 5 [P3311: Counting](https://www.luogu.com.cn/problem/P3311)"
    Statement: A positive integer $x$ is called lucky if and only if its decimal representation does not contain any element of the string set $S$ as a substring. For example, when $S = \{22, 333, 0233\}$, $233233$ is lucky, while $23332333$, $2023320233$, and $32233223$ are not. Given $n$ and $S$, compute the number of lucky numbers not greater than $n$. The answer is taken modulo $10^9 + 7$.
    
    $1 \leq n<10^{1201}, 1 \leq m \leq 100, 1 \leq \sum_{i = 1}^m |s_i| \leq 1500, \min_{i = 1}^m |s_i| \geq 1$, where $|s_i|$ denotes the length of string $s_i$. $n$ has no leading $0$, but $s_i$ may have leading $0$.

### Explanation

Reading the statement, if we treat the number as a string, the task becomes multi-pattern matching, so the Aho-Corasick automaton naturally comes to mind. In ordinary digit DP, we enumerate digits from high to low and then enumerate what to place at each position. In this problem, we naturally transform this into enumerating how many digits have already been filled, then which node of the AC automaton we are currently on, and finally transitioning from the current node to one of its child nodes in the AC automaton.

Let $f(i,j,0/1)$ denote the state after filling $i$ digits from high to low, that is, after walking along $i$ edges in the AC automaton, currently stopped at the node numbered $j$, and whether the current prefix is exactly tight to the upper bound.

For the "does not contain" condition, simply mark every terminal node of a pattern string in the AC automaton. During the DP, skip the state whenever such a terminal node is reached.

The transition is straightforward; see the main function in the code.

### Implementation

???+ note "Reference Code"
    ```cpp
    #include <cstdio>
    #include <cstring>
    #include <queue>
    using namespace std;
    using ll = long long;
    constexpr int N = 1505;
    constexpr int mod = 1000000007;
    int n, m;
    char s[N], c[N];
    int ch[N][10], fail[N], ed[N], tot, len;
    
    void insert() {
      int now = 0;
      int L = strlen(s);
      for (int i = 0; i < L; ++i) {
        if (!ch[now][s[i] - '0']) ch[now][s[i] - '0'] = ++tot;
        now = ch[now][s[i] - '0'];
      }
      ed[now] = 1;
    }
    
    queue<int> q;
    
    void build() {
      for (int i = 0; i < 10; ++i)
        if (ch[0][i]) q.push(ch[0][i]);
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 10; ++i) {
          if (ch[u][i]) {
            fail[ch[u][i]] = ch[fail[u]][i], q.push(ch[u][i]),
            ed[ch[u][i]] |= ed[fail[ch[u][i]]];
          } else
            ch[u][i] = ch[fail[u]][i];
        }
      }
      ch[0][0] = 0;
    }
    
    ll f[N][N][2], ans;
    
    void add(ll &x, ll y) { x = (x + y) % mod; }
    
    int main() {
      scanf("%s", c);
      n = strlen(c);
      scanf("%d", &m);
      for (int i = 1; i <= m; ++i) scanf("%s", s), insert();
      build();
      f[0][0][1] = 1;
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= tot; ++j) {
          if (ed[j]) continue;
          for (int k = 0; k < 10; ++k) {
            if (ed[ch[j][k]]) continue;
            add(f[i + 1][ch[j][k]][0], f[i][j][0]);
            if (k < c[i] - '0') add(f[i + 1][ch[j][k]][0], f[i][j][1]);
            if (k == c[i] - '0') add(f[i + 1][ch[j][k]][1], f[i][j][1]);
          }
        }
      }
      for (int j = 0; j <= tot; ++j) {
        if (ed[j]) continue;
        add(ans, f[n][j][0]);
        add(ans, f[n][j][1]);
      }
      printf("%lld\n", ans - 1);
      return 0;
    }
    ```

This problem is a good aid for understanding the principles of digit DP.

## Exercises

[Ahoi2009 self Similar Distribution](https://www.luogu.com.cn/problem/P4127)

[Luogu P3413 SAC#1 - Cute Numbers](https://www.luogu.com.cn/problem/P3413)

[HDU 6148 Valley Number](https://acm.hdu.edu.cn/showproblem.php?pid=6148)

[CF55D Beautiful numbers](http://codeforces.com/problemset/problem/55/D)

[CF628D Magic Numbers](http://codeforces.com/problemset/problem/628/D)
