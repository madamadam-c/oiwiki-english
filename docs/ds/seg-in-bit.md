author: Ir1d, sshwy, Enter-tainer, H-J-Granger, ouuan, GavinZhengOI, hsfzLZH1, xyf007

The problem of [static range k-th smallest value (POJ 2104 K-th Number)](http://poj.org/problem?id=2104) can be solved with a [value segment tree](./persistent-seg.md) in $O(n\log n)$ time.

What if the range becomes dynamic? That is, what should we do if we also need to support an operation that modifies the value at a single position?

??? note "Example Problem [Advanced Balanced Tree (Tree of Trees)](https://loj.ac/problem/106)"
    Maintain an ordered sequence that needs to support the following operations:

    -   Query the rank of $x$ in an interval;
    -   Query the value with rank $k$ in an interval;
    -   Modify the value at a position;
    -   Query the predecessor of $x$ in an interval (the predecessor is defined as the greatest number smaller than $x$);
    -   Query the successor of $x$ in an interval (the successor is defined as the smallest number greater than $x$).

??? note "Example Problem [Luogu P2617 Dynamic Rankings](https://www.luogu.com.cn/problem/P2617)"
    Given $n$ numbers forming a sequence $a_1,a_2 \dots a_n$, support two operations:
    
    -   `Q l r k` means to query, among indices in the interval $[l,r]$, the $k$-th smallest number
    -   `C x y` means to change $a_x$ to $y$

If we use the method discussed in [segment tree of balanced trees](./balanced-in-seg.md), that is, a segment tree where each node maintains a balanced tree for the interval represented by that node, and then binary search for the $k$-th smallest value, each query operation has to cover multiple intervals, that is, multiple nodes. However, balanced trees cannot search multiple values together, so the time complexity is $O(n\log^3 n)$, which is not optimal.

The optimization idea is to combine binary searching the answer with querying the number of values smaller than a given value, using a **segment tree of dynamically allocated value segment trees**. Since all segment trees have the same structure, we can perform segment-tree binary search on multiple trees simultaneously.

During a modification, first move from top to bottom on the segment tree to the point being modified. For every visited node, delete the old value from the dynamically allocated value segment tree it points to, and then insert the new value. This visits $O(\log n)$ nodes on the segment tree, and one modification on a dynamically allocated value segment tree costs $O(\log n)$, so the time complexity of a modification is $O(\log^2 n)$.

When querying the answer, first extract all nodes on the segment tree that cover the interval, and then use a method similar to the static range $k$-th smallest problem: move all these nodes to their left children or right children together. If the number of values stored in the left children of all these nodes is at least $k$, move left; otherwise move right. Since at most $O(\log n)$ nodes can be covered, at most that many nodes move downward each time, and the time complexity is $O(\log^2 n)$.

Because segment trees have a relatively large constant factor, implementations often use a **Fenwick tree**, which has a smaller constant factor and is more convenient for handling prefix sums. In addition, the space complexity is $O(n\log^2 n)$, so **pay attention to memory limits** when using this approach.

One implementation is given below:

??? note "Implementation"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <map>
    #include <set>
    #define LC o << 1
    #define RC o << 1 | 1
    using namespace std;
    constexpr int MAXN = 1000010;
    int n, m, a[MAXN], u[MAXN], x[MAXN], l[MAXN], r[MAXN], k[MAXN], cur, cur1, cur2,
        q1[MAXN], q2[MAXN], v[MAXN];
    char op[MAXN];
    set<int> ST;
    map<int, int> mp;
    
    struct segment_tree  // wrapped dynamically allocated value segment tree
    {
      int cur, rt[MAXN * 4], sum[MAXN * 60], lc[MAXN * 60], rc[MAXN * 60];
    
      void build(int& o) { o = ++cur; }
    
      void print(int o, int l, int r) {
        if (!o) return;
        if (l == r && sum[o]) printf("%d ", l);
        int mid = (l + r) >> 1;
        print(lc[o], l, mid);
        print(rc[o], mid + 1, r);
      }
    
      void update(int& o, int l, int r, int x, int v) {
        if (!o) o = ++cur;
        sum[o] += v;
        if (l == r) return;
        int mid = (l + r) >> 1;
        if (x <= mid)
          update(lc[o], l, mid, x, v);
        else
          update(rc[o], mid + 1, r, x, v);
      }
    } st;
    
    // Fenwick tree implementation
    namepace fenwick_impl {
      int lowbit(int o) { return (o & (-o)); }
    
      void upd(int o, int x, int v) {
        for (; o <= n; o += lowbit(o)) st.update(st.rt[o], 1, n, x, v);
      }
    
      void gtv(int o, int* A, int& p) {
        p = 0;
        for (; o; o -= lowbit(o)) A[++p] = st.rt[o];
      }
    
      int qry(int l, int r, int k) {
        if (l == r) return l;
        int mid = (l + r) >> 1, siz = 0;
        for (int i = 1; i <= cur1; i++) siz += st.sum[st.lc[q1[i]]];
        for (int i = 1; i <= cur2; i++) siz -= st.sum[st.lc[q2[i]]];
        // printf("j %d %d %d %d\n",cur1,cur2,siz,k);
        if (siz >= k) {
          for (int i = 1; i <= cur1; i++) q1[i] = st.lc[q1[i]];
          for (int i = 1; i <= cur2; i++) q2[i] = st.lc[q2[i]];
          return qry(l, mid, k);
        } else {
          for (int i = 1; i <= cur1; i++) q1[i] = st.rc[q1[i]];
          for (int i = 1; i <= cur2; i++) q2[i] = st.rc[q2[i]];
          return qry(mid + 1, r, k - siz);
        }
      }
    }
    using namespace fenwick_impl;
    
    // Segment tree implementation
    namespace segtree_impl {
    void build(int o, int l, int r) {
      st.build(st.rt[o]);
      if (l == r) return;
      int mid = (l + r) >> 1;
      build(LC, l, mid);
      build(RC, mid + 1, r);
    }
    
    void print(int o, int l, int r) {
      printf("%d %d:", l, r);
      st.print(st.rt[o], 1, n);
      printf("\n");
      if (l == r) return;
      int mid = (l + r) >> 1;
      print(LC, l, mid);
      print(RC, mid + 1, r);
    }
    
    void update(int o, int l, int r, int q, int x, int v) {
      st.update(st.rt[o], 1, n, x, v);
      if (l == r) return;
      int mid = (l + r) >> 1;
      if (q <= mid)
        update(LC, l, mid, q, x, v);
      else
        update(RC, mid + 1, r, q, x, v);
    }
    
    void getval(int o, int l, int r, int ql, int qr) {
      if (l > qr || r < ql) return;
      if (ql <= l && r <= qr) {
        q[++cur] = st.rt[o];
        return;
      }
      int mid = (l + r) >> 1;
      getval(LC, l, mid, ql, qr);
      getval(RC, mid + 1, r, ql, qr);
    }
    
    int query(int l, int r, int k) {
      if (l == r) return l;
      int mid = (l + r) >> 1, siz = 0;
      for (int i = 1; i <= cur; i++) siz += st.sum[st.lc[q[i]]];
      if (siz >= k) {
        for (int i = 1; i <= cur; i++) q[i] = st.lc[q[i]];
        return query(l, mid, k);
      } else {
        for (int i = 1; i <= cur; i++) q[i] = st.rc[q[i]];
        return query(mid + 1, r, k - siz);
      }
    }
    }  // namespace segtree_impl
    
    int main() {
      scanf("%d%d", &n, &m);
      for (int i = 1; i <= n; i++) scanf("%d", a + i), ST.insert(a[i]);
      for (int i = 1; i <= m; i++) {
        scanf(" %c", op + i);
        if (op[i] == 'C')
          scanf("%d%d", u + i, x + i), ST.insert(x[i]);
        else
          scanf("%d%d%d", l + i, r + i, k + i);
      }
      for (set<int>::iterator it = ST.begin(); it != ST.end(); it++)
        mp[*it] = ++cur, v[cur] = *it;
      for (int i = 1; i <= n; i++) a[i] = mp[a[i]];
      for (int i = 1; i <= m; i++)
        if (op[i] == 'C') x[i] = mp[x[i]];
      n += m;
      // build(1,1,n);
      for (int i = 1; i <= n; i++) upd(i, a[i], 1);
      // print(1,1,n);
      for (int i = 1; i <= m; i++) {
        if (op[i] == 'C') {
          upd(u[i], a[u[i]], -1);
          upd(u[i], x[i], 1);
          a[u[i]] = x[i];
        } else {
          gtv(r[i], q1, cur1);
          gtv(l[i] - 1, q2, cur2);
          printf("%d\n", v[qry(1, n, k[i])]);
        }
      }
      return 0;
    }
    ```
