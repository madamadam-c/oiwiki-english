author: ChungZH, billchenchina, Chrogeek, Early0v0, ethan-enhe, HeRaNO, hsfzLZH1, iamtwz, Ir1d, konnyakuxzy, luoguojie, Marcythm, orzAtalod, StudyingFather, wy-luke, Xeonacid, CCXXXI, chenryang, chenzheAya, CJSoft, cjsoft, countercurrent-time, DawnMagnet, Enter-tainer, GavinZhengOI, Haohu Shen, Henry-ZHR, hjsjhn, hly1204, jaxvanyang, Jebearssica, kenlig, ksyx, megakite, Menci, moon-dim, NachtgeistW, onelittlechildawa, ouuan, shadowice1984, shawlleyw, shuzhouliu, SukkaW, Tiphereth-A, x2e6, Ycrpro, yifan0305, zeningc

Segment tree merging and splitting are common segment-tree techniques, often seen when a value segment tree maintains a multiset.

For example, suppose some nodes on a tree have several operations. If information needs to be passed upward from child nodes to parent nodes, and the information at each individual node is conveniently maintained with a segment tree, segment tree merging can be used to control the overall complexity.

## Segment Tree Merging

### Process

As the name suggests, segment tree merging means building a new segment tree whose every node is the result of merging the corresponding nodes of two original segment trees. It is often used to maintain information on trees or graphs.

Obviously, we cannot really build a full new segment tree every time, so we need to use the dynamically allocated segment tree described earlier.

The process of segment tree merging is essentially quite brute-force:

Suppose the two segment trees are A and B. We start recursively merging from node 1.

When recursing to a node, if the corresponding node in tree A or tree B is empty, directly return the corresponding node of the other tree. This uses the property of dynamically allocated segment trees.

If we recurse to a leaf node, merge the corresponding nodes of the two trees.

Finally, update the current node based on its children and return it.

???+ note "Complexity of Segment Tree Merging"
    Clearly, for two full segment trees, one merge operation has complexity $O(n)$. However, in practice, value segment trees are usually used, and the total number of nodes in all segment trees to be merged is usually not much larger than $n$. Also, a segment tree is generally not merged repeatedly, so the final number of added nodes is roughly on the order of $n\log n$. Thus, the total complexity of merging all segment trees is on the order of $O(n\log n)$. Of course, in some situations, a mergeable heap may be a better choice.

### Implementation

```cpp
int merge(int a, int b, int l, int r) {
  if (!a) return b;
  if (!b) return a;
  if (l == r) {
    // do something...
    return a;
  }
  int mid = (l + r) >> 1;
  tr[a].l = merge(tr[a].l, tr[b].l, l, mid);
  tr[a].r = merge(tr[a].r, tr[b].r, mid + 1, r);
  pushup(a);
  return a;
}
```

### Example

???+ note "[Luogu P4556 [Vani's Date] Tail of the Rainy Day / Template: Segment Tree Merging](https://www.luogu.com.cn/problem/P4556)"
    ??? note "Solution"
        This is a template problem for segment tree merging. Use difference on trees to transform path updates into point updates, then DFS upward and merge segment trees to count the answer.
    
    ??? note "Reference Code"
        ```cpp
        --8<-- "docs/ds/code/seg/seg_6.cpp"
        ```

## Segment Tree Splitting

### Process

Segment tree splitting is essentially the inverse process of segment tree merging. Segment tree splitting only applies to ordered sequences; it is meaningless for unordered sequences. It is commonly used with dynamically allocated value segment trees.

Note that when both splitting and merging exist, nodes must be recycled during merging to avoid possible repeated node occupation during splitting.

From a segment tree whose interval is $[1,N]$, split out $[l,r]$ and build a new tree:

Start recursive splitting from node 1. If the node does not exist, or the interval $[s,t]$ represented by the node has no intersection with $[l,r]$, return directly.

When $[s,t]$ intersects $[l,r]$, a new node needs to be allocated.

When $[s,t]$ is contained in $[l,r]$, directly attach the current node under the new tree and disconnect the old edge.

???+ note "Complexity of Segment Tree Splitting"
    We can see that at most $\log n$ edges are disconnected, so the final time complexity of each split is $O(\log⁡ n)$, equivalent to the complexity of an interval query.

### Implementation

```cpp
void split(int &p, int &q, int s, int t, int l, int r) {
  if (t < l || r < s) return;
  if (!p) return;
  if (l <= s && t <= r) {
    q = p;
    p = 0;
    return;
  }
  if (!q) q = New();
  int m = s + t >> 1;
  if (l <= m) split(ls[p], ls[q], s, m, l, r);
  if (m < r) split(rs[p], rs[q], m + 1, t, l, r);
  push_up(p);
  push_up(q);
}
```

### Example

???+ note "[P5494 Template: Segment Tree Splitting](https://www.luogu.com.cn/problem/P5494)"
    ??? note "Solution"
        This is a template problem for segment tree splitting. Split out $[x,y]$.
        
        -   Merge tree $t$ into tree $p$: one merge operation is enough.
        
        -   In tree $p$, insert $x$ copies of $q$: point update.
        
        -   Query the number of values in $[x,y]$: interval sum.
        
        -   Query the $k$-th smallest value.
    
    ??? note "Reference Code"
        ```cpp
        --8<-- "docs/ds/code/seg/seg_7.cpp"
        ```

## Exercises

-   [Luogu P4556 [Vani's Date] Tail of the Rainy Day / Template: Segment Tree Merging](https://www.luogu.com.cn/problem/P4556)
-   [Luogu P5494 Template: Segment Tree Splitting](https://www.luogu.com.cn/problem/P5494)
-   [Luogu P1600 Running Every Day](https://www.luogu.com.cn/problem/P1600)
-   [Luogu P4577 [FJOI2018] Leadership Group Problem](https://www.luogu.com.cn/problem/P4577)
-   [Luogu P2824 [HEOI2016/TJOI2016] Sorting](https://www.luogu.com.cn/problem/P2824)
