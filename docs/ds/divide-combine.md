## Question about paragraph

We are introduced by a small and refreshing question:

> For an arrangement of $1-n$, we call an interval with a continuous range of values ​​a segment. Ask the number of segments in an arrangement. For example, the segments of $\{5 ,3 ,4, 1 ,2\}$ are: $[1,1],[2,2],[3,3],[4,4],[5,5],[2,3],[4,5],[1,3],[2,5],[1,5]$.

After seeing this thing, I feel that the complexity of maintaining the value range set of intervals seems quite unfriendly. The line segment tree can query whether a certain interval is a segment, but it cannot count the number of segments.

Here we introduce this magical data structure-the analysis tree!

## Continuous segment

Before introducing the analysis tree, we first make some prerequisite restrictions. Since the definitions given in the LCA courseware are not easy to understand, to facilitate readers' understanding, some less rigorous (but easier to understand) definitions are given here.

### Arrangements and Sequences

**Permutation**: Define a $n$ order permutation $P$ is a sequence of size $n$ such that $P_i$ takes $1,2,\cdots,n$. To put it more formally, the $n$ order arrangement $P$ is an ordered set that satisfies:

1.  $|P|=n$.
2.  $\forall i,P_i\in[1,n]$.
3.  $\nexists i,j\in[1,n],P_i=P_j$.

**Continuous segment**: For the arrangement $P$, define the continuous segment $(P,[l,r])$ to represent an interval $[l,r]$, and the value range of $P_{l\sim r}$ is required to be continuous. To put it more formally, for the permutation $P$, the continuous segment represents an interval $[l,r]$ that satisfies:

$$
(\nexists\ x,z\in[l,r],y\notin[l,r],\ P_x<P_y<P_z)
$$

In particular, when $l>r$, we think this is an empty continuous segment, denoted as $(P,\varnothing)$.

We call the set of all contiguous segments of permutation $P$ $I_P$, and we consider $(P,\varnothing)\in I_P$.

### Operations on consecutive segments

Continuous segments are defined dependent on intervals and ranges, so we can define the intersection and difference operations of continuous segments.

Define $A=(P,[a,b]),B=(P,[x,y])$, and $A,B\in I_P$. Therefore, the relations and operations of continuous segments can be expressed as:

1.  $A\subseteq B\iff x\le a\wedge b\le y$.
2.  $A=B\iff a=x\wedge b=y$.
3.  $A\cap B=(P,[\max(a,x),\min(b,y)])$.
4.  $A\cup B=(P,[\min(a,x),\max(b,y)])$.
5.  $A\setminus B=(P,\{i|i\in[a,b]\wedge i\notin[x,y]\})$.

In fact, these operations are just ordinary set intersections and differences placed on intervals.

### Properties of Continuous Segments

Some obvious properties of continuous segments. We define $A,B\in I_P,A \cap B \neq \varnothing,A \notin B,B \notin A$, then we have $A\cup B,A\cap B,A\setminus B,B\setminus A\in I_P$.

prove? The essence of the proof is the operation of intersection and difference of sets.

## analysis tree

Okay, now let’s get to the point. As you may have guessed, an analysis tree is a tree composed of consecutive segments. But we need to know that a permutation may have as many as $O(n^2)$ continuous segments, so we have to extract the more basic continuous segments to form an analysis tree.

### original paragraph

In fact, the full name of this definition is called **original continuous segment**. But I think the original paragraph is more concise.

For the permutation $P$, we consider that a primitive segment $M$ represents that in the set $I_P$, there is no continuous segment that intersects it and does not contain it. Defined formally, we believe that $X\in I_P$ satisfies $\forall A\in I_P,\ X\cap A= (P,\varnothing)\vee X\subseteq A\vee A\subseteq X$.

The set of all primitive segments is $M_P$. Obviously, $(P,\varnothing)\in M_P$.

Obviously, there are only separation or inclusion relationships between original segments. And you find that **a continuous segment can be composed of several mutually disjoint primitive segments**. The largest primitive segment is the entire arrangement itself, which includes all other primitive segments. Therefore, we believe that the primitive segment can form a tree structure. We call this structure an **resolution tree**. More strictly speaking, the analysis tree of permutation $P$ consists of **all primitive segments** of permutation $P$.

I have talked about so many definitions before, how can I do it without some pictures? Consider the permutation $P=\{9,1,10,3,2,5,7,6,8,4\}$. The analysis tree composed of its primitive segments is as follows:

![p1](./images/div-com1.png)

We have not marked the original segment in the picture. In the figure, **each node represents a primitive segment**. We only indicate the range of each primitive segment. For example, the primitive segment represented by node $[5,8]$ is $(P,[6,9])=\{5,7,6,8\}$. So here is a question: **What is the analysis point and conjunction point? **

### Analysis points and convergence points

Here we give the definition directly and discuss its correctness later.

1.  **Value range interval**: For a node $u$, use $[u_l,u_r]$ to represent the value range interval of the node.
2.  **Son sequence**: For a node $u$ on the analysis tree, assume that its son node is an **ordered** sequence, which has a value range interval as its element (a single number $x$ can be understood as the interval of $[x,x]$). We call this sequence the son sequence. Recorded as $S_u$．
3.  **Son arrangement**: For a son sequence $S_u$, the arrangement formed after discretizing its elements into positive integers is called a son arrangement. For example, for node $[5,8]$, its son sequence is $\{[5,5],[6,7],[8,8]\}$, then if the interval sorting is marked with a number, its son sequence will be $\{1,2,3\}$; similarly, the son sequence of node $[4,8]$ will be $\{2,1\}$. The arrangement of the sons of node $u$ is recorded as $P_u$.
4.  **Joint**: We believe that the point where the sons are arranged in order or reverse order is the conjunction. Formally speaking, a point that satisfies $P_u=\{1,2,\cdots,|S_u|\}$ or $P_u=\{|S_u|,|S_u-1|,\cdots,1\}$ is called a conjunction. **The leaf node has no son arrangement, and we also think it is a conjunction**.
5.  **Analysis point**: If it is not a conjunction, it is an analysis point.

As can be seen from the figure, only $[1,10]$ is not a conjunction. Because the order of the sons of $[1,10]$ is $\{3,1,4,2\}$.

### Properties of analytic points and conjunctions

The names of analytic points and conjunctions come from their properties. First of all, we have a very obvious property: for any node $u$ in the analysis tree, the union of its son sequence intervals is the value range interval of the node $u$. That is $\bigcup_{i=1}^{|S_u|}S_u[i]=[u_l,u_r]$.

For a conjunction $u$: any **subinterval** of its son sequence forms a **continuous segment**. Formally speaking, $\forall S_u[l\sim r]$, there is $\bigcup_{i=l}^rS_u[i]\in I_P$.

For an analysis point $u$: any **length of its son sequence is greater than 1 (the length here refers to the number of elements in the child sequence, not the length of the subscript interval)** and the subintervals **do not** form a **continuous segment**. Formally speaking, $\forall S_u[l\sim r],l<r$, there is $\bigcup_{i=l}^rS_u[i]\notin I_P$.

The properties of chalaza are not difficult to prove. Because the children of the conjunction are arranged either in order or in reverse order, and the range intervals are also connected at the first place, so as long as it is a continuous subsequence (interval), it is a continuous segment.

Many readers may not be able to understand the nature of the analysis point: why **any** subintervals with a length greater than $1$ do not constitute a continuous segment?

Use proof by contradiction. Suppose that for a point $u$, there is a **longest** interval $S_u[l\sim r]$ in its son sequence, which forms a continuous segment. Then this $A=\bigcup_{i=l}^rS_u[i]\in I_P$ means that $A$ is a primitive segment! (Because $A$ is the longest in the child sequence, you cannot find a continuous segment that intersects and does not contain it.) So you do not use all the primitive segments to form this analysis tree. contradiction.

### The structure of the analysis tree

For the specific construction of the analysis tree, LCA provides a linear construction algorithm [^ref1]. A relatively easy-to-understand $O(n\log n)$ algorithm is given below.

#### incremental method

We consider the incremental method. Use a stack to maintain the disjunctive forest composed of the first $i-1$ elements. What needs to be emphasized here is that the analysis and conjunction forest means that at any time, the nodes in the stack are either analysis points or conjunctions. Now consider the current node $P_i$.

1.  We first determine whether it can become the son of the top node of the stack. If it can, it becomes the son of the top of the stack, and then takes the top of the stack as the current node. Repeat the above process until the stack is empty or cannot become the son of the top node of the stack.
2.  If it cannot become the son of the top of the stack, see if it can merge several consecutive nodes on the top of the stack into one node (the method of judging whether it can be merged will be later), and use the merged point as the current node.
3.  Repeat the above process until it is no longer possible. Then end this increment and directly push the current node onto the stack.

Next we explain it in detail.

#### specific strategies

We believe that if the current point can become the son of the top node of the stack, then the top node of the stack is a conjunction. If it is an analysis point, then after you merge the analysis point, there will be a sub-continuous segment, which does not satisfy the properties of an analysis point. Therefore it must be the conjunction.

If it cannot become the son of the node on the top of the stack, then we will see if several consecutive points on the top of the stack can be merged with the current point. Let $l$ be the left endpoint of the interval where the current point is located. We calculate $L_i$ to represent, among continuous segments whose right endpoint subscript is $i$, the maximum left endpoint $< l$. The current node is $P_i$, and the top node of the stack is recorded as $t$.

1.  If $L_i$ does not exist, then obviously the current node cannot be merged;
2.  If $t_l=L_i$, then this is the merger of two nodes, and the merger is a **junction**;
3.  Otherwise, there must be a point $t'$ in the stack whose left endpoint is ${t'}_l=L_i$, then it must be merged from the current node to $t'$ to form an **analysis point**;

#### Determine whether to merge

Finally, we consider what to do with $L_i$. In fact, a continuous segment $(P,[l,r])$ is equivalent to the interval range equal to the interval length -1. Right now

$$
\max_{l\le i\le r}P_i-\min_{l\le i\le r}P_i=r-l
$$

And since P is a permutation, for any interval $[l,r]$

$$
\max_{l\le i\le r}P_i-\min_{l\le i\le r}P_i\ge r-l
$$

So we maintain $\max_{l\le i\le r}P_i-\min_{l\le i\le r}P_i-(r-l)$, then finding a continuous segment is equivalent to querying a minimum value!

With the above ideas, it is not difficult to think of such an algorithm. For the current $i$ during the increment process, we maintain an array $Q$ representing the range minus length of the interval $[j,i]$. Right now

$$
Q_j=\max_{j\le k\le i}P_k-\min_{j\le k\le i}P_k-(i-j),\ \ 0<j<i
$$

Now we want to know whether in $1\sim i-1$ there is a minimum $j$ such that $Q_j=0$. This is equivalent to finding the minimum value of $Q_{1\sim i-1}$. The smallest $j$ is found to be $L_i$. If not, then $L_i=i$.

But when the $i$th increment ends, we need to quickly update the $Q$ array to the i+1 situation. The original interval changes from $[j,i]$ to $[j,i+1]$. If it is $P_{i+1}>\max$ or $P_{i+1}<\min$, it will cause $Q_j$ to change. How? If $P_{i+1}>\max$, it is equivalent to us taking $Q_j$, subtracting $\max$, and then adding $P_{i+1}$ to complete the update of $Q_j$; similarly, $P_{i+1}<\min$ is equivalent to $Q_j=Q_j+\min-P_{i+1}$.

So what if for an interval $[x,y]$, the intervals $P_{x\sim i},P_{x+1\sim i},P_{x+2\sim i},\cdots,P_{y\sim i}$ all have the same $\max$? As you have discovered, it is equivalent to us doing an interval addition operation; similarly, when the intervals $P_{x\sim i},P_{x+1\sim i},\cdots,P_{y\sim i}$ all have the same $\min$, it is also an interval addition operation. At the same time, the updates of $\max$ and $\min$ are independent of each other, so they can be updated separately.

Therefore our maintenance of $Q$ can be described as follows:

1.  Find the largest $j$ such that $P_{j}>P_{i+1}$, then obviously, all the numbers in $P_{j+1\sim i}$ are less than $P_{i+1}$, so you need to update the maximum value of $Q_{j+1\sim i}$. Since $P_{i},\max(P_i,P_{i-1}),\max(P_i,P_{i-1},P_{i-2}),\cdots,\max(P_i,P_{i-1},\cdots,P_{j+1})$ is (non-strictly) monotonically increasing, the same update can be performed on each segment of the same $\max$, that is, interval addition operation.
2.  Update $\min$ in the same way.
3.  Subtract from each $Q_j$ the value $1$. Because the interval length is added to $1$.
4.  Query $L_i$: that is, query the **subscript** where the minimum value of $Q$ is located.

That’s right, we can maintain $Q$ using segment trees! Now there is another question: How to find the same paragraph so that their $\max/\min$ are the same? Use monotonic stack maintenance! Maintain two monotonic stacks to represent $\max/\min$ respectively. Obviously, the $\max/\min$ of the interval with two adjacent elements as endpoints in the stack are the same, so when maintaining the monotonic stack, just update the line segment tree.

See the code for specific maintenance methods.

My friends must have been confused after talking so much dryly, so let’s start with the picture. Long picture warning!

![p2](./images/div-com2.jpg)

### accomplish

Finally, put an implementation code for reference. The code is transferred from [rice cake's blog](https://www.cnblogs.com/Paul-Guderian/p/11020708.html), with some comments added.

```cpp
#include <algorithm>
#include <cstdio>
using namespace std;
constexpr int N = 200010;

int n, m, a[N], st1[N], st2[N], tp1, tp2, rt;
int L[N], R[N], M[N], id[N], cnt, typ[N], bin[20], st[N], tp;

// The original title of this code should be CERC2017 Intrinsic Interval
// The a array is the corresponding arrangement in the original question
// st1 and st2 are two monotonic stacks respectively, tp1 and tp2 are the tops of the corresponding stacks, and rt is the root of the analysis tree.
// The L and R arrays represent the left and right endpoints of the analysis tree node. The role of the M array is mentioned in the construction of the analysis tree.
// id stores the node number corresponding to a certain position in the arrangement, and typ is used to mark the analysis point or conjunction point.
// st is the stack that stores the node number of the analysis tree, and tp is the top of the stack.
struct RMQ {  // Preprocessing RMQ (Max & Min)
  int lg[N], mn[N][17], mx[N][17];

  void chkmn(int& x, int y) {
    if (x > y) x = y;
  }

  void chkmx(int& x, int y) {
    if (x < y) x = y;
  }

  void build() {
    for (int i = bin[0] = 1; i < 20; ++i) bin[i] = bin[i - 1] << 1;
    for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= n; ++i) mn[i][0] = mx[i][0] = a[i];
    for (int i = 1; i < 17; ++i)
      for (int j = 1; j + bin[i] - 1 <= n; ++j)
        mn[j][i] = min(mn[j][i - 1], mn[j + bin[i - 1]][i - 1]),
        mx[j][i] = max(mx[j][i - 1], mx[j + bin[i - 1]][i - 1]);
  }

  int ask_mn(int l, int r) {
    int t = lg[r - l + 1];
    return min(mn[l][t], mn[r - bin[t] + 1][t]);
  }

  int ask_mx(int l, int r) {
    int t = lg[r - l + 1];
    return max(mx[l][t], mx[r - bin[t] + 1][t]);
  }
} D;

// Maintain L_i

struct SEG {  // Segment tree
#define ls (k << 1)
#define rs (k << 1 | 1)
  int mn[N << 1], ly[N << 1];  // Interval addition; interval minimum value

  void pushup(int k) { mn[k] = min(mn[ls], mn[rs]); }

  void mfy(int k, int v) { mn[k] += v, ly[k] += v; }

  void pushdown(int k) {
    if (ly[k]) mfy(ls, ly[k]), mfy(rs, ly[k]), ly[k] = 0;
  }

  void update(int k, int l, int r, int x, int y, int v) {
    if (l == x && r == y) {
      mfy(k, v);
      return;
    }
    pushdown(k);
    int mid = (l + r) >> 1;
    if (y <= mid)
      update(ls, l, mid, x, y, v);
    else if (x > mid)
      update(rs, mid + 1, r, x, y, v);
    else
      update(ls, l, mid, x, mid, v), update(rs, mid + 1, r, mid + 1, y, v);
    pushup(k);
  }

  int query(int k, int l, int r) {  // Ask for the location of 0
    if (l == r) return l;
    pushdown(k);
    int mid = (l + r) >> 1;
    if (!mn[ls])
      return query(ls, l, mid);
    else
      return query(rs, mid + 1, r);
    // If there is no position 0, it will automatically return to the current position you are querying.
  }
} T;

int o = 1, hd[N], dep[N], fa[N][18];

struct Edge {
  int v, nt;
} E[N << 1];

void add(int u, int v) {  // Add edges to tree structure
  E[o] = Edge{v, hd[u]};
  hd[u] = o++;
}

void dfs(int u) {
  for (int i = 1; bin[i] <= dep[u]; ++i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
  for (int i = hd[u]; i; i = E[i].nt) {
    int v = E[i].v;
    dep[v] = dep[u] + 1;
    fa[v][0] = u;
    dfs(v);
  }
}

int go(int u, int d) {
  for (int i = 0; i < 18 && d; ++i)
    if (bin[i] & d) d ^= bin[i], u = fa[u][i];
  return u;
}

int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  u = go(u, dep[u] - dep[v]);
  if (u == v) return u;
  for (int i = 17; ~i; --i)
    if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
  return fa[u][0];
}

// Determine whether the current interval is a continuous segment
bool judge(int l, int r) { return D.ask_mx(l, r) - D.ask_mn(l, r) == r - l; }

// make achievements
void build() {
  for (int i = 1; i <= n; ++i) {
    // monotonic stack
    // The minimum value in the interval [st1[tp1-1]+1,st1[tp1]] is a[st1[tp1]]
    // Now popping it off the stack means adding back the extra Min that was subtracted.
    // The leaf node position j of the line segment tree maintains the relationship from j to the current i
    // Max{j,i}-Min{j,i}-(i-j)
    // The interval plus is just a Tag.
    // The purpose of maintaining a monotonic stack is to assist in updating the segment tree from i-1 to i.
    // After updating to i, you only need to query the global minimum to know whether there is a solution

    while (tp1 && a[i] <= a[st1[tp1]])  // Monotonically increasing stack, maintaining Min
      T.update(1, 1, n, st1[tp1 - 1] + 1, st1[tp1], a[st1[tp1]]), tp1--;
    while (tp2 && a[i] >= a[st2[tp2]])
      T.update(1, 1, n, st2[tp2 - 1] + 1, st2[tp2], -a[st2[tp2]]), tp2--;

    T.update(1, 1, n, st1[tp1] + 1, i, -a[i]);
    st1[++tp1] = i;
    T.update(1, 1, n, st2[tp2] + 1, i, a[i]);
    st2[++tp2] = i;

    id[i] = ++cnt;
    L[cnt] = R[cnt] = i;  // Here, L and R refer to the left and right endpoints of the interval corresponding to the node.
    int le = T.query(1, 1, n), now = cnt;
    while (tp && L[st[tp]] >= le) {
      if (typ[st[tp]] && judge(M[st[tp]], i)) {
        // Determine whether you can become a son, and if so, do it
        R[st[tp]] = i, M[st[tp]] = L[now], add(st[tp], now), now = st[tp--];
      } else if (judge(L[st[tp]], i)) {
        typ[++cnt] = 1;  // The conjunction must have been built like this
        L[cnt] = L[st[tp]], R[cnt] = i, M[cnt] = L[now];
        // Here, the M array is the left endpoint of the rightmost son of the recorded node, which is used to determine whether the upper part can become a son.
        add(cnt, st[tp--]), add(cnt, now);
        now = cnt;
      } else {
        add(++cnt, now);  // Create a new node and add now as a son
        // If a continuous segment cannot be formed from the current node, merge it.
        // Until a node is found that can form a continuous segment. And we can definitely find this
        // A node.
        do add(cnt, st[tp--]);
        while (tp && !judge(L[st[tp]], i));
        L[cnt] = L[st[tp]], R[cnt] = i, add(cnt, st[tp--]);
        now = cnt;
      }
    }
    st[++tp] = now;  // The increment ends and the current point is pushed onto the stack.

    T.update(1, 1, n, 1, i, -1);  // Because the right endpoint of the interval moves backward one space, the overall value is -1
  }

  rt = st[1];  // The last remaining point in the stack is the root node
}

// Analyze lca as analytic or sum, here the leaves are regarded as analytic
void query(int l, int r) {
  int x = id[l], y = id[r];
  int z = lca(x, y);
  if (typ[z] & 1)
    l = L[go(x, dep[x] - dep[z] - 1)], r = R[go(y, dep[y] - dep[z] - 1)];
  // The reason why the conjunction is special here is because the conjunction is not necessarily the smallest continuous segment containing l and r.
  // Because the subintervals of the interval represented by the conjunction are also continuous segments, and we only need one segment of them.
  else
    l = L[z], r = R[z];
  printf("%d %d\n", l, r);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
  D.build();
  build();
  dfs(rt);
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    query(x, y);
  }
  return 0;
}

// 20190612
// analysis tree
```

## References and links

[Rice Cake's Blog -[Study Notes] Analytic Tree](https://www.cnblogs.com/Paul-Guderian/p/11020708.html)

[^ref1]: Liu Chengao． Simple continuous segment data structure. WC2019 camper exchange．
