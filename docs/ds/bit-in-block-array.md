author: Backl1ght, Tiphereth-A, Enter-tainer, Ir1d, ksyx, leoleoasd, Xeonacid, aaron20100919

## Introduction

Blocked tree arrays can be used to do some of the same things that tree blocks can do under certain conditions, but compared to tree blocks, block block tree array code writing is shorter and easier to implement.

## simple example

A simple example is the query of the number of points in a matrix area in a two-dimensional plane.

???+ note "Rectangular area query"
    Given $n$ points $(x_i, y_i)$ in the two-dimensional plane, among which $1 \le i \le n, 1 \le x_i, y_i \le n, 1 \le n \le 10^5$ , the following operations are required:
    
    1.  Given $a, b, c, d$, ask for the number of points in the rectangular area with $(a, b)$ as the upper left corner and $c, d$ as the lower right corner.
    2.  Given $x, y$, change the ordinate of the point with abscissa $x$ to $y$.
    
    Title **Mandatory online**, guaranteed $x_i \ne x_j(1 \le i, j \le n, i \ne j)$.

For operation 1, it can be solved by converting it into four two-dimensional partial order queries through rectangular inclusion and exclusion. However, because it is forced to be online, offline algorithms such as CDQ divide and conquer cannot solve it, so I thought of a tree within a tree, such as a tree array within a Treap. This can indeed solve the problem, but the code is too long and not particularly easy to implement.

Notice that the question also guarantees $x_i \ne x_j(1 \le i, j \le n, i \ne j)$. At this time, it can be solved by using block-based tree arrays.

### initialization

First of all, one $x$ only corresponds to one $y$, so you can use an array to record this mapping relationship. For example, let $Y_i$ represent the ordinate of the point with the abscissa $i$.

Then, the abscissa is divided into blocks using $\sqrt n$ as the block size. Build a weight tree array for each block. Note that $T_i$ is the tree array corresponding to the $i$th block, and $T_{i, j}$ represents the number of points in block $i$ whose ordinate is within $(j - lowbit(j), j]$.

### Query

For operation 1, it is converted into four two-dimensional partial order queries. Now we only need to solve given $a, b$ and ask how many points satisfy $1 \le x_i \le a, 1\le y_i \le b$.

Now the range of the abscissa coordinate to be queried is $[1, a]$. Because there may be a section on the far right of the query range that is not a complete block, we violently scan this section to see if it meets $Y_i \le b$ and count the number of points that this section meets the requirements.

Now only the complete blocks need to be processed. Violently scan the previous blocks, query the number of values ​​in the tree array corresponding to each block that are less than $b$, and add them to the answer.

Is that all? No, notice that when processing a complete block, it is actually equivalent to querying the prefix sum of $T$. If you also use the tree array technique to process $T$ when modifying, the query complexity will be lower.

### Revise

The common approach is to first find the block where the point $x$ is located, then subtract one and add two weights to the tree array to modify the single point, and then set $Y_x$ to $y$.

If you use the optimization mentioned above, you will also go through a tree array modification process for $T$. Each modification is a single point modification of the tree array of one minus one plus two weights.

Make certain changes to the above steps, such as changing one minus and one plus to only subtraction, which means deleting points; changing it to only addition, means adding points. But it must be noted that one $x$ can only correspond to one $y$.

### space complexity

Blocking is divided into $\sqrt n$ blocks, each block has a space of tree array $O(n)$, so the space complexity is $O(n \sqrt n)$.

### time complexity

If querying, traverse the segment $O(\sqrt n)$ of the incomplete block. Then, a tree array query is performed for $T$, and a tree array query is also performed for each experienced $T_i$. This step is the complexity of $O(\log (\sqrt n) \log n)$. So the time complexity of the query is $O (\sqrt n + \log (\sqrt n) \log n)$ .

Modification is the same as query, and the complexity is $O (\sqrt n + \log (\sqrt n) \log n)$.

## Example 1

???+ note "[Intersection of Permutations](https://codeforces.com/problemset/problem/1093/E)"
    Given two permutations $a$ and $b$ , the following two operations are required:
    
    1.  Given $l_a, r_a, l_b, r_b$, it is required to query the number of elements that appear in both $a[l_a ... r_a]$ and $b[l_b ... r_b]$.
    2.  Gives $x, y$ , $swap(b_x, b_y)$ .
    
    The sequence length $n$ satisfies $2 \le n \le 2 \cdot 10^5$, and the number of operations $q$ satisfies $1 \le q \le 2 \cdot 10^5$.

For each value $i$, let $x_i$ be its index in the array $b$ and $y_i$ be its index in the array $a$. In this way, operation 1 becomes an inquiry about the number of points in a rectangular area, and operation 2 can be regarded as two modification operations. And because it is an arrangement, it satisfies that one $x$ corresponds to one $y$, so this question can be written using a block tree array.

??? note "Reference code (blocked tree array - 1s)"
    ```cpp
    #include <cmath>
    #include <cstdio>
    using namespace std;
    constexpr int N = 2e5 + 5;
    constexpr int M = 447 + 5;  // sqrt(N) + 5
    
    int n, m, pa[N], pb[N];
    
    int nn, block_size, block_cnt, block_id[N], L[N], R[N], T[M][N];
    
    void build(int n) {
      nn = n;
      block_size = sqrt(nn);
      block_cnt = nn / block_size;
      for (int i = 1; i <= block_cnt; ++i) {
        L[i] = R[i - 1] + 1;
        R[i] = i * block_size;
      }
      if (R[block_cnt] < nn) {
        ++block_cnt;
        L[block_cnt] = R[block_cnt - 1] + 1;
        R[block_cnt] = nn;
      }
      for (int j = 1; j <= block_cnt; ++j)
        for (int i = L[j]; i <= R[j]; ++i) block_id[i] = j;
    }
    
    int lb(int x) { return x & -x; }
    
    void add(int p, int v, int d) {
      for (int i = block_id[p]; i <= block_cnt; i += lb(i))
        for (int j = v; j <= nn; j += lb(j)) T[i][j] += d;
    }
    
    int getsum(int p, int v) {
      if (!p) return 0;
      int res = 0;
      int id = block_id[p];
      for (int i = L[id]; i <= p; ++i)
        if (pb[i] <= v) ++res;
      for (int i = id - 1; i; i -= lb(i))
        for (int j = v; j; j -= lb(j)) res += T[i][j];
      return res;
    }
    
    void update(int x, int y) {
      add(x, pb[x], -1);
      add(y, pb[y], -1);
      swap(pb[x], pb[y]);
      add(x, pb[x], 1);
      add(y, pb[y], 1);
    }
    
    int query(int la, int ra, int lb, int rb) {
      int res = getsum(rb, ra) - getsum(rb, la - 1) - getsum(lb - 1, ra) +
                getsum(lb - 1, la - 1);
      return res;
    }
    
    int main() {
      scanf("%d %d", &n, &m);
      int v;
      for (int i = 1; i <= n; ++i) scanf("%d", &v), pa[v] = i;
      for (int i = 1; i <= n; ++i) scanf("%d", &v), pb[i] = pa[v];
    
      build(n);
      for (int i = 1; i <= n; ++i) add(i, pb[i], 1);
    
      int op, la, lb, ra, rb, x, y;
      for (int i = 1; i <= m; ++i) {
        scanf("%d", &op);
        if (op == 1) {
          scanf("%d %d %d %d", &la, &ra, &lb, &rb);
          printf("%d\n", query(la, ra, lb, rb));
        } else if (op == 2) {
          scanf("%d %d", &x, &y);
          update(x, y);
        }
      }
      return 0;
    }
    ```

??? note "Reference code (tree array set Treap-TLE)"
    ```cpp
    #include <cstdio>
    #include <random>
    using namespace std;
    constexpr int N = 2e5 + 5;
    mt19937 rng(random_device{}());
    
    int n, m, pa[N], pb[N];
    
    // Treap
    struct Treap {
      struct node {
        node *l, *r;
        int sz, rnd, v;
    
        node(int _v) : l(NULL), r(NULL), sz(1), rnd(rng()), v(_v) {}
      };
    
      int get_size(node*& p) { return p ? p->sz : 0; }
    
      void push_up(node*& p) {
        if (!p) return;
        p->sz = get_size(p->l) + get_size(p->r) + 1;
      }
    
      node* root;
    
      node* merge(node* a, node* b) {
        if (!a) return b;
        if (!b) return a;
        if (a->rnd < b->rnd) {
          a->r = merge(a->r, b);
          push_up(a);
          return a;
        } else {
          b->l = merge(a, b->l);
          push_up(b);
          return b;
        }
      }
    
      void split_val(node* p, const int& k, node*& a, node*& b) {
        if (!p)
          a = b = NULL;
        else {
          if (p->v <= k) {
            a = p;
            split_val(p->r, k, a->r, b);
            push_up(a);
          } else {
            b = p;
            split_val(p->l, k, a, b->l);
            push_up(b);
          }
        }
      }
    
      void split_size(node* p, int k, node*& a, node*& b) {
        if (!p)
          a = b = NULL;
        else {
          if (get_size(p->l) <= k) {
            a = p;
            split_size(p->r, k - get_size(p->l), a->r, b);
            push_up(a);
          } else {
            b = p;
            split_size(p->l, k, a, b->l);
            push_up(b);
          }
        }
      }
    
      void ins(int val) {
        node *a, *b;
        split_val(root, val, a, b);
        a = merge(a, new node(val));
        root = merge(a, b);
      }
    
      void del(int val) {
        node *a, *b, *c, *d;
        split_val(root, val, a, b);
        split_val(a, val - 1, c, d);
        delete d;
        root = merge(c, b);
      }
    
      int qry(int val) {
        node *a, *b;
        split_val(root, val, a, b);
        int res = get_size(a);
        root = merge(a, b);
        return res;
      }
    
      int qry(int l, int r) { return qry(r) - qry(l - 1); }
    };
    
    // Fenwick Tree
    Treap T[N];
    
    int lb(int x) { return x & -x; }
    
    void ins(int x, int v) {
      for (; x <= n; x += lb(x)) T[x].ins(v);
    }
    
    void del(int x, int v) {
      for (; x <= n; x += lb(x)) T[x].del(v);
    }
    
    int qry(int x, int mi, int ma) {
      int res = 0;
      for (; x; x -= lb(x)) res += T[x].qry(mi, ma);
      return res;
    }
    
    int main() {
      scanf("%d %d", &n, &m);
      int v;
      for (int i = 1; i <= n; ++i) scanf("%d", &v), pa[v] = i;
      for (int i = 1; i <= n; ++i) scanf("%d", &v), pb[i] = pa[v];
      for (int i = 1; i <= n; ++i) ins(i, pb[i]);
    
      int op, la, lb, ra, rb, x, y;
      for (int i = 1; i <= m; ++i) {
        scanf("%d", &op);
        if (op == 1) {
          scanf("%d %d %d %d", &la, &ra, &lb, &rb);
          printf("%d\n", qry(rb, la, ra) - qry(lb - 1, la, ra));
        } else if (op == 2) {
          scanf("%d %d", &x, &y);
          del(x, pb[x]);
          del(y, pb[y]);
          swap(pb[x], pb[y]);
          ins(x, pb[x]);
          ins(y, pb[y]);
        }
      }
      return 0;
    }
    ```

## Example 2

???+ note "[Complicated Computations](https://codeforces.com/contest/1436/problem/E)"
    Given a sequence $a$, use the array composed of the MEX of all consecutive subsequences of $a$ as $b$, and ask the MEX of $b$. The MEX of a sequence is the smallest **positive integer** that has never appeared in the sequence.
    
    The length of the sequence $n$ satisfies $1 \le n \le 10^5$.

**Observation**: The MEX of a sequence is $mex$ if and only if the sequence contains $1$ to $mex-1$, but does not contain $mex$.

Determine in turn whether there is a continuous subsequence of MEX from $1$ to $n+1$. If there is no contiguous subsequence with MEX $i$, then the answer is $i$. If both exist, the answer is $n + 2$ .

When evaluating $i$, treat the sequence as multiple segments separated by zero or more $i$. If there is a segment that contains $1$ to $i - 1$ but does not contain $i$, then it means that there is a continuous subsequence with value $i$.

Use an array $Y_j$ to record the position of the previous element with a value of $a_j$, with $j$ as $x$, $Y_j$ as $y$, and $a_j$ as $z$. In this way, calculating whether the segment contains $1$ to $i - 1$ is a three-dimensional partial ordering problem. Formally speaking, judging whether the MEX value of segment $[l, r]$ is $i$ is to see whether the number of points satisfying $l \le j \le r, Y_j \le l - 1, a_j \le i - 1$ is $i-1$.

If the corresponding point is inserted after judging the element with value $i$, then because in $[l, r]$ there are only elements of $a_j \le i - 1$, the above three-dimensional partial ordering problem can be converted into a two-dimensional partial ordering problem.

??? note "Reference code (blocked tree array - 78ms)"
    ```cpp
    #include <cmath>
    #include <cstdio>
    #include <vector>
    using namespace std;
    constexpr int N = 1e5 + 5;
    constexpr int M = 316 + 5;  // sqrt(N) + 5
    
    // Chunking
    int nn, b[N], block_size, block_cnt, block_id[N], L[N], R[N], T[M][N];
    
    void build(int n) {
      nn = n;
      block_size = sqrt(nn);
      block_cnt = nn / block_size;
      for (int i = 1; i <= block_cnt; ++i) {
        L[i] = R[i - 1] + 1;
        R[i] = i * block_size;
      }
      if (R[block_cnt] < nn) {
        ++block_cnt;
        L[block_cnt] = R[block_cnt - 1] + 1;
        R[block_cnt] = nn;
      }
      for (int j = 1; j <= block_cnt; ++j)
        for (int i = L[j]; i <= R[j]; ++i) block_id[i] = j;
    }
    
    int lb(int x) { return x & -x; }
    
    // d = 1: add point (p, v)
    // d = -1: delete point (p, v)
    void add(int p, int v, int d) {
      for (int i = block_id[p]; i <= block_cnt; i += lb(i))
        for (int j = v; j <= nn; j += lb(j)) T[i][j] += d;
    }
    
    // Ask how many points there are in [1, r] whose ordinate is less than or equal to val
    int getsum(int p, int v) {
      if (!p) return 0;
      int res = 0;
      int id = block_id[p];
      for (int i = L[id]; i <= p; ++i)
        if (b[i] && b[i] <= v) ++res;
      for (int i = id - 1; i; i -= lb(i))
        for (int j = v; j; j -= lb(j)) res += T[i][j];
      return res;
    }
    
    // Ask how many points there are in [l, r] whose ordinate is less than or equal to val
    int query(int l, int r, int val) {
      if (l > r) return -1;
      int res = getsum(r, val) - getsum(l - 1, val);
      return res;
    }
    
    // Add point (p, v)
    void update(int p, int v) {
      b[p] = v;
      add(p, v, 1);
    }
    
    int n, a[N];
    vector<int> g[N];
    
    int main() {
      scanf("%d", &n);
    
      // In order to reduce discussion, a sentinel node was added
      // Because when adding a tree array, if it is 0, it may cause an infinite loop, so the whole thing is shifted to the right by one bit.
      // a_1 and a_{n+2} are sentinel nodes
      for (int i = 2; i <= n + 1; ++i) scanf("%d", &a[i]);
      for (int i = 2; i <= n + 1; ++i) g[a[i]].push_back(i);
    
      // Chunking
      build(n + 2);
    
      int ans = n + 2, lst, ok;
      for (int i = 1; i <= n + 1; ++i) {
        g[i].push_back(n + 2);
    
        lst = 1;
        ok = 0;
        for (int pos : g[i]) {
          if (query(lst + 1, pos - 1, lst) == i - 1) {
            ok = 1;
            break;
          }
          lst = pos;
        }
    
        if (!ok) {
          ans = i;
          break;
        }
    
        lst = 1;
        g[i].pop_back();
        for (int pos : g[i]) {
          update(pos, lst);
          lst = pos;
        }
      }
      printf("%d\n", ans);
      return 0;
    }
    ```

??? note "Reference code (line segment tree set Treap-468ms)"
    ```cpp
    #include <cstdio>
    #include <random>
    #include <vector>
    using namespace std;
    constexpr int N = 1e5 + 5;
    
    vector<int> g[N];
    int n, a[N];
    
    mt19937 rng(random_device{}());
    
    struct Treap {
      struct node {
        node *l, *r;
        unsigned rnd;
        int sz, v;
    
        node(int _v) : l(NULL), r(NULL), rnd(rng()), sz(1), v(_v) {}
      };
    
      int get_size(node*& p) { return p ? p->sz : 0; }
    
      void push_up(node*& p) {
        if (!p) return;
        p->sz = get_size(p->l) + get_size(p->r) + 1;
      }
    
      node* root;
    
      node* merge(node* a, node* b) {
        if (!a) return b;
        if (!b) return a;
        if (a->rnd < b->rnd) {
          a->r = merge(a->r, b);
          push_up(a);
          return a;
        } else {
          b->l = merge(a, b->l);
          push_up(b);
          return b;
        }
      }
    
      void split_val(node* p, const int& k, node*& a, node*& b) {
        if (!p)
          a = b = NULL;
        else {
          if (p->v <= k) {
            a = p;
            split_val(p->r, k, a->r, b);
            push_up(a);
          } else {
            b = p;
            split_val(p->l, k, a, b->l);
            push_up(b);
          }
        }
      }
    
      void split_size(node* p, int k, node*& a, node*& b) {
        if (!p)
          a = b = NULL;
        else {
          if (get_size(p->l) <= k) {
            a = p;
            split_size(p->r, k - get_size(p->l), a->r, b);
            push_up(a);
          } else {
            b = p;
            split_size(p->l, k, a, b->l);
            push_up(b);
          }
        }
      }
    
      void insert(int val) {
        node *a, *b;
        split_val(root, val, a, b);
        a = merge(a, new node(val));
        root = merge(a, b);
      }
    
      int query(int val) {
        node *a, *b;
        split_val(root, val, a, b);
        int res = get_size(a);
        root = merge(a, b);
        return res;
      }
    
      int qry(int l, int r) { return query(r) - query(l - 1); }
    };
    
    // Segment Tree
    Treap T[N << 2];
    
    void insert(int x, int l, int r, int p, int val) {
      T[x].insert(val);
      if (l == r) return;
      int mid = (l + r) >> 1;
      if (p <= mid)
        insert(x << 1, l, mid, p, val);
      else
        insert(x << 1 | 1, mid + 1, r, p, val);
    }
    
    int query(int x, int l, int r, int L, int R, int val) {
      if (l == L && r == R) return T[x].query(val);
      int mid = (l + r) >> 1;
      if (R <= mid) return query(x << 1, l, mid, L, R, val);
      if (L > mid) return query(x << 1 | 1, mid + 1, r, L, R, val);
      return query(x << 1, l, mid, L, mid, val) +
             query(x << 1 | 1, mid + 1, r, mid + 1, R, val);
    }
    
    int query(int l, int r, int val) {
      if (l > r) return -1;
      return query(1, 1, n, l, r, val);
    }
    
    int main() {
      scanf("%d", &n);
      for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
      for (int i = 1; i <= n; ++i) g[a[i]].push_back(i);
    
      // a_0 and a_{n+1} are sentinel nodes
      int ans = n + 2, lst, ok;
      for (int i = 1; i <= n + 1; ++i) {
        g[i].push_back(n + 1);
    
        lst = 0;
        ok = 0;
        for (int pos : g[i]) {
          if (query(lst + 1, pos - 1, lst) == i - 1) {
            ok = 1;
            break;
          }
          lst = pos;
        }
    
        if (!ok) {
          ans = i;
          break;
        }
    
        lst = 0;
        g[i].pop_back();
        for (int pos : g[i]) {
          insert(1, 1, n, pos, lst);
          lst = pos;
        }
      }
      printf("%d\n", ans);
      return 0;
    }
    ```
