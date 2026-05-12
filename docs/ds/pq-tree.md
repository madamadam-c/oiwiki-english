author: isdanni,xyf007

A PQ tree is a tree-based data structure that represents a family of permutations over a set of elements. It was discovered and named by Kellogg S. Booth and George S. Lueker in 1976, and is used to solve the following problem:

> Given $m$ sets $S_i$, find a permutation of $1\sim n$ such that the elements in every set are consecutive.

A PQ tree can be constructed in $O(n+\sum|S_i|)$ time. The construction method introduced here has time complexity $O(nm)$.

## Definition

A PQ tree has three kinds of nodes: **leaf nodes**, **P nodes**, and **Q nodes**. A leaf node represents one element in the permutation. A P node means its children may be permuted arbitrarily. A Q node means the order of its children may be reversed. Every non-leaf node is either a P node or a Q node. A P node has at least 2 children, and a Q node has at least 3 children.
By this definition, the PQ tree itself represents **all** valid solutions; its preorder traversal is one of them.
The following figure is a PQ tree.
![](https://gregable.com/2008/11/i/pq-tree.webp)
Its preorder traversal, 1,2,3,4,5, represents one valid solution. If the children of the P node are rearranged as 4,2,3, we obtain another valid solution, 1,4,2,3,5. If the order of children of the P node is kept and the children of the Q node are reversed, we obtain another valid solution, 5,3,2,4,1.

## Construction

**The PQ tree uses the child-sibling representation.**

We build a PQ tree incrementally.

First build a tree whose root is P and whose $n$ children are $1,2,\ldots,n$, representing the PQ tree with no restrictions. As restrictions are added, the tree is modified continuously.

When adding a new restricted set $S$, mark all leaf nodes in this set **black**, and all leaf nodes outside the set **white**. For every non-leaf node, if all children are black, mark it black; if all children are white, mark it white; otherwise mark it **gray**. In the figures below, black nodes, white nodes, and gray nodes are shown as black, gray, and half-black-half-gray respectively.

We require the nodes in the PQ tree to be ordered by color.

### Bottom-Up Method

The minimum subtree containing all black nodes is called the **pertinent subtree**, and its root, not necessarily the root of the whole tree, is called the **pertinent root**.

The process of adding a restriction is called reduction. A reduction has two phases: the bubbling phase and the reduction phase.

#### Bubbling Phase

The bubbling phase handles only the pertinent subtree. Mark all nodes in the pertinent subtree as black or gray, and compute for each node the number of pertinent children it has. To do this efficiently, process the pertinent subtree from leaves to root. This requires recording the parent of every point, but a point's parent is often modified during the reduction phase. To construct in linear time, only children of P nodes and the **last child of a Q node** always record the correct parent. For other children of a Q node, the bubbling phase updates their parent using the parent of the last child.

When encountering an internal node, check whether its sibling already has a valid parent. If not, mark it as **blocked**. If later its sibling obtains a valid parent, update this node's parent and remove the mark. If a consecutive segment of blocked nodes remains at the end of the bubbling phase, as in case Q3 below, a parentless dummy node becomes the parent of that block and is removed during the reduction phase.

#### Reduction Phase

The reduction phase processes nodes with a queue. First put all leaves in the restricted set into the queue. Each time, pop the front node $u$ and process it. If $u$'s parent is also inside the pertinent subtree, push $\mathit{fa}_u$ into the queue.
For every node $u$, discuss cases. If none applies, there is no solution.

##### Leaf Node

Mark $u$ black.

##### P Node

If all children are black, mark $u$ black.
![](https://gregable.com/2008/11/i/p1-template.png)
![](https://gregable.com/2008/11/i/p1-replacement.png)

If $u$ has black and white children and $u$ is the pertinent root, create a new P node $v$ as the root of all black children.
![](https://gregable.com/2008/11/i/p2-template.png)
![](https://gregable.com/2008/11/i/p2-replacement.png)

If $u$ has black and white children and $u$ is not the pertinent root, do the following:

-   Create a new P node $f$ as the root of all black children.
-   Create a new P node $e$ as the root of all white children.
-   If $e$ and/or $f$ has only one child, do not create a new node; directly set $e$ and/or $f$ to that child.
-   Change $u$ into a Q node, set its children to $e$ and $f$, and mark it gray.

Because Q nodes must have at least 3 children, this $u$ is treated as a dummy node and will be processed later.
![](https://gregable.com/2008/11/i/p3-template.png)
![](https://gregable.com/2008/11/i/p3-replacement.png)

If $u$ has one gray child $p$ and $u$ is the pertinent root, create a new P node $v$ as the root of all black children, set $v$'s sibling to the last black child of $p$, and set $v$ as the last child of $p$.
![](https://gregable.com/2008/11/i/p4-template.png)
![](https://gregable.com/2008/11/i/p4-replacement.png)

If $u$ has one gray child $p$ and $u$ is not the pertinent root, do the following:

-   Create a new P node $f$ as the root of all black children.
-   Create a new P node $e$ as the root of all white children.
-   If $e$ and/or $f$ has only one child, do not create a new node; directly set $e$ and/or $f$ to that child.
-   Set $e$'s sibling to the last white child of $p$, then set $e$ as the last child of $p$.
-   Set $f$'s sibling to the last black child of $p$, then set $f$ as the last child of $p$.

![](https://gregable.com/2008/11/i/p5-template.png)
![](https://gregable.com/2008/11/i/p5-replacement.png)

If $u$ has exactly two gray children $p_1,p_2$, do the following:

-   Create a new P node $f$ as the root of all black children.
-   If $f$ has only one child, do not create a new node; directly set $f$ to that child.
-   Set the sibling of the last black child of $p_1$ to $f$.
-   Set $f$'s sibling to the last black child of $p_2$.
-   Set the last child of $p_2$ to the last white child of $p_2$.

Then $p_2$ has been merged into $p_1$.
![](https://gregable.com/2008/11/i/p6-template.png)
![](https://gregable.com/2008/11/i/p6-replacement.png)

##### Q Node

If $u$ has only black children, mark $u$ black. The shape in the following figure is incorrect.
![](https://gregable.com/2008/11/i/q1-template.png)
![](https://gregable.com/2008/11/i/q1-replacement.png)

If $u$ has one gray child $p$ and all children with the same mark appear consecutively, do the following:

-   Let $p_f$ be the last black child of $p$, $p_e$ be the last white child of $p$, $f$ be a black sibling of $p$, and $e$ be a white sibling of $p$.
-   Set $f$'s sibling to $p_f$ and $e$'s sibling to $p_e$.
-   If $p$ has no white sibling or no black sibling, set the last child of $u$ to the last child of $p$.
-   Delete $p$.

![](https://gregable.com/2008/11/i/q2-template.png)
![](https://gregable.com/2008/11/i/q2-replacement.png)

If $u$ has exactly two gray children $p_1,p_2$, and all children with the same mark appear consecutively, perform the previous operation on both $p_1,p_2$.
![](https://gregable.com/2008/11/i/q3-template.png)
![](https://gregable.com/2008/11/i/q3-replacement.png)

This construction method is from the original paper, but it is inconvenient to implement.

### Top-Down Method

Most OI implementations use this method. It is similar to the previous one, and the following cases essentially correspond to cases above.

Since all black and white nodes already satisfy the condition after coloring, we **only need to process gray nodes**.

#### P Node

-   If $u$ has more than two gray children, there is no solution.
-   If $u$ has only one gray child and no black child, recursively process the gray child.
-   Otherwise, clear $u$'s children, then add all white children. Create a new Q node $q_1$ as a child of $u$. Put all gray children into $q_1$. Create a new P node $p$ as the root of all black children, and insert $p$ into the middle of $q_1$. This corresponds to all bottom-up P-node cases.

Because we require two gray nodes to have all white nodes on the left and all black nodes on the right, or the reverse, we need a split function `split`. It splits the subtree into white and black parts while preserving **all possible** resulting subtrees.

#### Q Node

-   Find the leftmost and rightmost non-white positions $l,r$. If there is any non-black node inside $[l+1,r-1]$, there is no solution.
-   If there is no black node and only one gray node, recursively process that gray node; otherwise, only split the nodes at positions $l$ and $r$.

#### Split Function

Let the node to split be $u$. We want to split $u$ into a forest where the left side is all white and the right side is all black. If $u$ is not gray, directly return the subtree. Consider only gray nodes.
If $u$ is a P node:

-   If $u$ has at least two gray children, there is no solution.
-   Otherwise, the left side is all white children, the middle recursively processes the gray child, and the right side is all black children. To preserve all possibilities, create two new P nodes as roots of the white and black children respectively. This corresponds to bottom-up case P4.
-   Delete $u$.

If $u$ is a Q node:

-   If neither the forward nor the reversed order satisfies white-gray-black, there is no solution.
-   If there are at least two gray children, there is also no solution.
-   Otherwise, recursively split the gray child.
-   Delete $u$.

Finally, delete all redundant nodes, i.e. nodes with only one child.

## Code Implementation

```cpp
class PQTree {
 public:
  PQTree() {}

  void Init(int n) {
    n_ = n, rt_ = tot_ = n + 1;
    for (int i = 1; i <= n; i++) g_[rt_].emplace_back(i);
  }

  void Insert(const std::string &s) {
    s_ = s;
    Dfs0(rt_);
    Work(rt_);
    while (g_[rt_].size() == 1) rt_ = g_[rt_][0];
    Remove(rt_);
  }

  std::vector<int> ans() {
    DfsAns(rt_);
    return ans_;
  }

  ~PQTree() {}

 private:
  int n_, rt_, tot_, pool_[100001], top_, typ_[100001] /* 0-P 1-Q */,
      col_[100001] /* 0-black 1-white 2-grey */;
  std::vector<int> g_[100001], ans_;
  std::string s_;

  void Fail() {
    std::cout << "NO\n";
    std::exit(0);
  }

  int NewNode(int ty) {
    int x = top_ ? pool_[top_--] : ++tot_;
    typ_[x] = ty;
    return x;
  }

  void Delete(int u) { g_[u].clear(), pool_[++top_] = u; }

  void Dfs0(int u) {  // get color of each node
    if (u >= 1 && u <= n_) {
      col_[u] = s_[u] == '1';
      return;
    }
    bool c0 = false, c1 = false;
    for (auto &&v : g_[u]) {
      Dfs0(v);
      if (col_[v]) c1 = true;
      if (col_[v] != 1) c0 = true;
    }
    if (c0 && !c1)
      col_[u] = 0;
    else if (!c0 && c1)
      col_[u] = 1;
    else
      col_[u] = 2;
  }

  bool Check(const std::vector<int> &v) {
    int p2 = -1;
    for (int i = 0; i < static_cast<int>(v.size()); i++)
      if (col_[v[i]] == 2) {
        if (p2 != -1) return false;
        p2 = i;
      }
    if (p2 == -1)
      for (int i = 0; i < static_cast<int>(v.size()); i++)
        if (col_[v[i]]) {
          p2 = i;
          break;
        }
    for (int i = 0; i < p2; i++)
      if (col_[v[i]]) return false;
    for (int i = p2 + 1; i < static_cast<int>(v.size()); i++)
      if (col_[v[i]] != 1) return false;
    return true;
  }

  std::vector<int> Split(int u) {
    if (col_[u] != 2) return {u};
    std::vector<int> ng;
    if (typ_[u]) {  // Q
      if (!Check(g_[u])) {
        std::reverse(g_[u].begin(), g_[u].end());
        if (!Check(g_[u])) Fail();
      }
      for (auto &&v : g_[u])
        if (col_[v] != 2) {
          ng.emplace_back(v);
        } else {
          auto s = Split(v);
          ng.insert(ng.end(), s.begin(), s.end());
        }
    } else {  // P
      std::vector<int> son[3];
      for (auto &&x : g_[u]) son[col_[x]].emplace_back(x);
      if (son[2].size() > 1) Fail();
      if (!son[0].empty()) {
        int n0 = NewNode(0);
        g_[n0] = son[0];
        ng.emplace_back(n0);
      }
      if (!son[2].empty()) {
        auto s = Split(son[2][0]);
        ng.insert(ng.end(), s.begin(), s.end());
      }
      if (!son[1].empty()) {
        int n1 = NewNode(0);
        g_[n1] = son[1];
        ng.emplace_back(n1);
      }
    }
    Delete(u);
    return ng;
  }

  void Work(int u) {
    if (col_[u] != 2) return;
    if (typ_[u]) {  // Q
      int l = 1e9, r = -1e9;
      for (int i = 0; i < static_cast<int>(g_[u].size()); i++)
        if (col_[g_[u][i]]) checkmin(l, i), checkmax(r, i);
      for (int i = l + 1; i < r; i++)
        if (col_[g_[u][i]] != 1) Fail();
      if (l == r && col_[g_[u][l]] == 2) {
        Work(g_[u][l]);
        return;
      }
      std::vector<int> ng;
      for (int i = 0; i < l; i++) ng.emplace_back(g_[u][i]);
      auto s = Split(g_[u][l]);
      ng.insert(ng.end(), s.begin(), s.end());
      for (int i = l + 1; i < r; i++) ng.emplace_back(g_[u][i]);
      if (l != r) {
        s = Split(g_[u][r]);
        std::reverse(s.begin(), s.end());
        ng.insert(ng.end(), s.begin(), s.end());
      }
      for (int i = r + 1; i < static_cast<int>(g_[u].size()); i++)
        ng.emplace_back(g_[u][i]);
      g_[u] = ng;
    } else {  // P
      std::vector<int> son[3];
      for (auto &&x : g_[u]) son[col_[x]].emplace_back(x);
      if (son[1].empty() && son[2].size() == 1) {
        Work(son[2][0]);
        return;
      }
      g_[u].clear();
      if (son[2].size() > 2) Fail();
      g_[u] = son[0];
      int n1 = NewNode(1);
      g_[u].emplace_back(n1);
      if (son[2].size() >= 1) {
        auto s = Split(son[2][0]);
        g_[n1].insert(g_[n1].end(), s.begin(), s.end());
      }
      if (son[1].size()) {
        int n2 = NewNode(0);
        g_[n1].emplace_back(n2);
        g_[n2] = son[1];
      }
      if (son[2].size() >= 2) {
        auto s = Split(son[2][1]);
        std::reverse(s.begin(), s.end());
        g_[n1].insert(g_[n1].end(), s.begin(), s.end());
      }
    }
  }

  void Remove(int u) {  // remove the nodes with only one child
    for (auto &&v : g_[u]) {
      int tv = v;
      while (g_[tv].size() == 1) {
        int t = tv;
        tv = g_[tv][0];
        Delete(t);
      }
      v = tv, Remove(v);
    }
  }

  void DfsAns(int u) {
    if (u >= 1 && u <= n_) {
      ans_.emplace_back(u);
      return;
    }
    for (auto &&v : g_[u]) DfsAns(v);
  }
} T;
```

## Exercises

-   [CF243E Matrix](https://codeforces.com/problemset/problem/243/E)
-   [CF1552I Organizing a Music Festival](https://codeforces.com/contest/1552/problem/I)

## References

-   Booth, Kellogg S. & Lueker, George S. (1976).["Testing for the consecutive ones property, interval graphs, and graph planarity using PQ-tree algorithms"](https://www.sciencedirect.com/science/article/pii/S0022000076800451?via%3Dihub).*[Journal of Computer and System Sciences](https://en.wikipedia.org/wiki/Journal_of_Computer_and_System_Sciences)*.**13**(3): 335–379.[doi](https://en.wikipedia.org/wiki/Doi_%28identifier%29):[10.1016/S0022-0000(76)80045-1](https://doi.org/10.1016%2FS0022-0000%2876%2980045-1).
-   [PQ Tree Algorithm and Consecutive Ones Problem](https://gregable.com/2008/11/pq-tree-algorithm.html)
-   [CF243E Matrix PQTree - RainAir's Blog](https://blog.aor.sd.cn/archives/1657/)
