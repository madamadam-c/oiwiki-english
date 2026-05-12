author: HeRaNO, JuicyMio, Xeonacid, sailordiary, ouuan, Pig-Eat-Earth

![](images/disjoint-set.svg)

## Introduction

A disjoint set union (DSU) is a data structure for maintaining which set each element belongs to. It is implemented as a forest: each tree represents one set, and each node in the tree represents an element of that set.

As the name suggests, DSU supports two operations:

-   Unite: merge the sets containing two elements, i.e. merge the corresponding trees.
-   Find: query the set containing an element, i.e. query the root of the corresponding tree. This can be used to determine whether two elements are in the same set.

With modifications, DSU can support deleting or moving a single element, or maintaining edge weights on the trees. A dynamic segment tree can also be used to implement [persistent DSU](./persistent-seg.md#extension-persistent-dsu-based-on-chairman-tree).

???+ warning "Warning"
    DSU cannot split a set with low complexity.

## Initialization

Initially, every element is in a separate set, represented by a tree with only a root. For convenience, set the parent of each root to itself.

???+ example "Implementation"
    === "C++"
        ```cpp
        struct dsu {
          vector<size_t> pa;
        
          explicit dsu(size_t size) : pa(size) { iota(pa.begin(), pa.end(), 0); }
        };
        ```
    
    === "Python"
        ```python
        class Dsu:
            def __init__(self, size):
                self.pa = list(range(size))
        ```

## Find

Move upward along the tree until the root is found.

![](images/disjoint-set-find.svg)

???+ example "Implementation"
    === "C++"
        ```cpp
        size_t dsu::find(size_t x) { return pa[x] == x ? x : find(pa[x]); }
        ```
    
    === "Python"
        ```python
        def find(self, x):
            return x if self.pa[x] == x else self.find(self.pa[x])
        ```

### Path Compression

Every element visited during a find operation belongs to the same set, so we can connect it directly to the root to speed up later queries.

![](images/disjoint-set-compress.svg)

???+ example "Implementation"
    === "C++"
        ```cpp
        size_t dsu::find(size_t x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }
        ```
    
    === "Python"
        ```python
        def find(self, x):
            if self.pa[x] != x:
                self.pa[x] = self.find(self.pa[x])
            return self.pa[x]
        ```

## Unite

To merge two trees, connect the root of one tree to the root of the other.

![](images/disjoint-set-merge.svg)

???+ example "Implementation"
    === "C++"
        ```cpp
        void dsu::unite(size_t x, size_t y) { pa[find(x)] = find(y); }
        ```
    
    === "Python"
        ```python
        def unite(self, x, y):
            self.pa[self.find(x)] = self.find(y)
        ```

### Union By Heuristic

When merging, the choice of which root becomes the new root affects the complexity of future operations. Connect the tree with fewer nodes or smaller depth to the other tree to avoid degeneration.

??? note "Detailed Complexity Discussion"
    The only required operations are merging and querying sets. When two sets must be merged, connecting either set below the other is correct, but different choices have different time costs. If the tree with fewer nodes and smaller depth is connected under a larger tree, later find operations are faster and the worst-case time complexity is better.
    
    Of course, we do not always encounter a set that is smaller in both node count and depth. Since both features are easy to maintain, we usually choose one of them as the heuristic. Either choice gives time complexity $O (m\alpha(m,n))$; see the papers cited in References for proofs.
    
    In competitive programming, even code without union by heuristic often passes within the time limit. Tarjan's paper[^tarjan1984worst] proves that using path compression only, without union by heuristic, has worst-case time complexity $O (m \log n)$. Yao's paper[^yao1985expected] proves that using path compression only has average-case complexity $O (m\alpha(m,n))$.
    
    If only union by heuristic is used, without path compression, the complexity is $O(m\log n)$. Because one path-compressed union may modify many nodes, path compression is sometimes unsuitable. For example, persistent DSU and segment-tree divide-and-conquer with DSU usually use only union by heuristic.

Reference implementation of union by size (note that the initialization must be adjusted):

???+ example "Implementation"
    === "C++"
        ```cpp
        struct dsu {
          vector<size_t> pa, size;
        
          explicit dsu(size_t size_) : pa(size_), size(size_, 1) {
            iota(pa.begin(), pa.end(), 0);
          }
        
          void unite(size_t x, size_t y) {
            x = find(x), y = find(y);
            if (x == y) return;
            if (size[x] < size[y]) swap(x, y);
            pa[y] = x;
            size[x] += size[y];
          }
        };
        ```
    
    === "Python"
        ```python
        class Dsu:
            def __init__(self, size):
                self.pa = list(range(size))
                self.size = [1] * size
        
            def unite(self, x, y):
                x, y = self.find(x), self.find(y)
                if x == y:
                    return
                if self.size[x] < self.size[y]:
                    x, y = y, x
                self.pa[y] = x
                self.size[x] += self.size[y]
        ```

## Reference Implementation

A complete DSU with path compression and union by size is shown below:

??? example "Template Problem [Luogu P3367 Template DSU](https://www.luogu.com.cn/problem/P3367) Reference Implementation"
    === "C++"
        ```cpp
        --8<-- "docs/ds/code/dsu/dsu_0.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/ds/code/dsu/dsu_0.py"
        ```

## Complexity

With both path compression and union by heuristic, every DSU operation has amortized time $O(\alpha(n))$. Here $\alpha$ is the inverse Ackermann function, which grows extremely slowly. In practice, the average time of one DSU operation can be treated as a very small constant. The proof is on [this page](./dsu-complexity.md).

???+ info "Inverse Ackermann Function"
    The [Ackermann function](https://en.wikipedia.org/wiki/Ackermann_function) $A(m, n)$ is defined as:
    
    $A(m, n) = \begin{cases}n+1&\text{if }m=0\\A(m-1,1)&\text{if }m>0\text{ and }n=0\\A(m-1,A(m,n-1))&\text{otherwise}\end{cases}$
    
    The inverse Ackermann function $\alpha(n)$ is the inverse of the Ackermann function, namely the largest integer $m$ such that $A(m, m) \leqslant n$.

The space complexity of DSU is clearly $O(n)$.

## Extensions

Starting from ordinary DSU, many modifications can support more operations or maintain more complex information.

### DSU With Deletion

Ordinary DSU cannot support deletion because deleting a node inevitably deletes all nodes in the subtree rooted at it. To solve this, a DSU with deletion can create virtual nodes so that all nodes storing actual data are always leaves. During initialization, create a virtual node for every data node and set the data node's parent to that virtual node. Since every merge only connects two set roots, only virtual nodes ever have children. This ensures that deleting one node does not accidentally delete other nodes.

After deleting a single node, rebuild a virtual node as its parent; otherwise later merge and delete operations cannot be performed correctly.

??? example "Template Problem [SPOJ JMFILTER - Junk-Mail Filter](https://www.spoj.com/problems/JMFILTER/) Reference Implementation"
    === "C++"
        ```cpp
        --8<-- "docs/ds/code/dsu/dsu_4.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/ds/code/dsu/dsu_4.py"
        ```

A similar method can move a single element between sets. See the example problems for details.

### Weighted DSU

We can define weights on DSU edges and specify how these weights are updated during path compression to solve more problems. For example, in the classic NOI2001 Food Chain problem, edge weights can maintain the additive group modulo $3$. For problems with small moduli, a point can also be split into several states; this special technique is also called species DSU or extended-domain DSU. The examples below illustrate these methods.

To maintain edge weights, store the edge weight in the child node. Thus each node stores the weight of the edge between it and its parent. The weight only needs adjustment when a node's parent changes, which usually happens during path compression and when merging two nodes. For example, if the edge weight is the distance between the current node and its parent, then during path compression, whenever the parent is replaced by the root, add the old parent's distance to the root to the current node's stored edge weight. Similarly, when merging two sets, compute the weight of the newly connected edge between the two roots.

??? example "Template Problem [Library Checker - Unionfind with Potential](https://judge.yosupo.jp/problem/unionfind_with_potential) Reference Implementation"
    === "C++"
        ```cpp
        --8<-- "docs/ds/code/dsu/dsu_5.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/ds/code/dsu/dsu_5.py"
        ```

## Example Problems

In competitive programming, problems that directly test DSU usually require designing a special structure for the statement.

???+ example "[UVa11987 Almost Union-Find](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3138)"
    Implement a DSU-like data structure supporting:
    
    1.  Merge the sets containing two elements.
    2.  Move a single element to the set containing another element.
    3.  Query the size and element sum of the set containing an element.

??? note "Solution"
    Operations 1 and 3 are easy; the difficulty is operation 2. Suppose element $x$ is moved to the set containing $y$. In an ordinary DSU, directly setting the parent of $x$ to the root of $y$'s set is incorrect because all elements in $x$'s subtree would be moved together. The solution is to ensure that $x$ has no children. When building the DSU, for each element $x$, create a virtual point $\tilde x$ and set $x$'s parent to $\tilde x$. During merges, one root is always connected to another root, and all roots are virtual points; therefore only virtual points have children, and real element nodes have no children. Then moving an element becomes easy.

??? note "Reference Implementation"
    === "C++"
        ```cpp
        --8<-- "docs/ds/code/dsu/dsu_1.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/ds/code/dsu/dsu_1.py"
        ```

???+ example "[Luogu P2024 NOI2011 Food Chain](https://www.luogu.com.cn/problem/P2024)"
    There are three kinds of animals $A,B,C$ in an animal kingdom. Their food chain forms a cycle: $A$ eats $B$, $B$ eats $C$, and $C$ eats $A$.
    
    There are $N$ animals numbered $1 \sim N$. Each animal is one of $A,B,C$, but its exact type is unknown.
    
    Someone describes the food-chain relations among these $N$ animals using two kinds of statements:
    
    -   `1 X Y` means $X$ and $Y$ are of the same kind.
    -   `2 X Y` means $X$ eats $Y$.
    
    For these $N$ animals, the person makes $K$ statements one by one. Some of these $K$ statements are true and some are false. A statement is false if one of the following holds; otherwise it is true.
    
    -   It conflicts with some previous true statement.
    -   $X$ or $Y$ is greater than $N$.
    -   It says $X$ eats $X$.
    
    Given $N$ and $K$ statements, output the total number of false statements.

??? note "Solution 1"
    Use weighted DSU to maintain food-chain information. If $x$ and $y$ are the same kind, then $x\equiv y\pmod 3$; if $x$ eats $y$, then $x - y \equiv 1 \pmod 3$. This converts the problem into the template above.
    
    For each statement, except for obvious false cases where $x>n$ or $y>n$, check whether $x$ and $y$ are already connected. If they are connected, compute their modular distance and compare it with the statement; otherwise connect them according to the statement. Apart from obvious cases, a statement is false iff the two mentioned nodes are already connected and the corresponding distance contradicts the statement.

??? note "Reference Implementation 1"
    === "C++"
        ```cpp
        --8<-- "docs/ds/code/dsu/dsu_6.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/ds/code/dsu/dsu_6.py"
        ```

??? note "Solution 2"
    Split each creature $x$ into three states. In implementation, directly treat the states as different elements:
    
    -   States in the same set as $x$ are the same species as $x$.
    -   States in the same set as $x+n$ can be eaten by $x$.
    -   States in the same set as $x+2n$ can eat $x$.
    
    For a statement:
    
    -   `1 x y` is false iff:
    
        1.  $x>N$ or $y>N$;
        2.  $y$ is in the same set as either $x+n$ or $x+2n$.
    -   `2 x y` is false iff:
    
        1.  $x>N$ or $y>N$;
        2.  $y$ is in the same set as either $x$ or $x+2n$.
    -   If the statement is true, merge the corresponding states.

??? note "Reference Implementation 2"
    === "C++"
        ```cpp
        --8<-- "docs/ds/code/dsu/dsu_2.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/ds/code/dsu/dsu_2.py"
        ```

???+ example "[ABC396E Min of Restricted Sum](https://atcoder.jp/contests/abc396/tasks/abc396_e)"
    Given integers $N, M$ and, each of length $M$, integer sequences $X=(X_1,X_2,\ldots,X_M)$, $Y=(Y_1,Y_2,\ldots,Y_M)$, and $Z=(Z_1,Z_2,\ldots,Z_M)$. All elements of $X$ and $Y$ are guaranteed to be in the range $1$ to $N$.
    
    Define a length-$N$ nonnegative integer sequence $A=(A_1,A_2,\ldots,A_N)$ to be a **good integer sequence** iff it satisfies:
    
    -   For every integer in the range $1 \leq i \leq M$, denoted $i$, we have $A_{X_i} \oplus A_{Y_i} = Z_i$, where $\oplus$ denotes bitwise XOR.
    
    Determine whether such a good integer sequence exists. If it exists, find and output one whose element sum $\displaystyle \sum_{i=1}^N A_i$ is minimum.

??? note "Solution"
    XOR is an equality-or-inequality relation on each binary bit. Split all binary bits of $A_i$, and the XOR relations can be maintained with weighted DSU or species DSU. Elements in the same connected component correspond to the same bit position of different numbers in $A$. When computing the answer, elements in one connected component are usually split into two groups with different values; assign $0$ to the larger group and $1$ to the other group to minimize the total weight.

??? note "Reference Implementation"
    === "C++"
        ```cpp
        --8<-- "docs/ds/code/dsu/dsu_3.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/ds/code/dsu/dsu_3.py"
        ```

## Exercises

-   [NOI2015 Program Automatic Analysis](https://uoj.ac/problem/127)
-   [JSOI2008 Planet Wars](https://www.luogu.com.cn/problem/P1197)
-   [NOIP2023 Ternary Logic](https://www.luogu.com.cn/problem/P9869)
-   [NOI2002 Legend of Galactic Heroes](https://www.luogu.com.cn/problem/P1196)

## Other Applications

Kruskal's algorithm in [minimum spanning tree algorithms](../graph/mst.md) and Tarjan's algorithm in [lowest common ancestor](../graph/lca.md) are based on DSU.

See [DSU applications](../topic/dsu-app.md) for related topics.

## References And Further Reading

1.  [Zhihu answer: Is there really a halving path-compression optimization in DSU?](https://www.zhihu.com/question/28410263/answer/40966441)
2.  Gabow, H. N., & Tarjan, R. E. (1985). A Linear-Time Algorithm for a Special Case of Disjoint Set Union. JOURNAL OF COMPUTER AND SYSTEM SCIENCES, 30, 209-221.[PDF](https://dl.acm.org/doi/pdf/10.1145/800061.808753)
3.  [CSDN: Extended-domain DSU & weighted DSU](https://blog.csdn.net/qqqqqwerttwtwe/article/details/145440100)

[^tarjan1984worst]: Tarjan, R. E., & Van Leeuwen, J. (1984). Worst-case analysis of set union algorithms. Journal of the ACM (JACM), 31(2), 245-281.[ResearchGate PDF](https://www.researchgate.net/profile/Jan_Van_Leeuwen2/publication/220430653_Worst-case_Analysis_of_Set_Union_Algorithms/links/0a85e53cd28bfdf5eb000000/Worst-case-Analysis-of-Set-Union-Algorithms.pdf)

[^yao1985expected]: Yao, A. C. (1985). On the expected performance of path compression algorithms.[SIAM Journal on Computing, 14(1), 129-133.](https://epubs.siam.org/doi/abs/10.1137/0214010?journalCode=smjcat)
