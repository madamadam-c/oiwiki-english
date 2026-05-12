author: ChungZH, billchenchina, Chrogeek, Early0v0, ethan-enhe, HeRaNO, hsfzLZH1, iamtwz, Ir1d, konnyakuxzy, luoguojie, Marcythm, orzAtalod, StudyingFather, wy-luke, Xeonacid, CCXXXI, chenryang, chenzheAya, CJSoft, cjsoft, countercurrent-time, DawnMagnet, Enter-tainer, GavinZhengOI, Haohu Shen, Henry-ZHR, hjsjhn, hly1204, jaxvanyang, Jebearssica, kenlig, ksyx, megakite, Menci, moon-dim, NachtgeistW, onelittlechildawa, ouuan, shadowice1984, shawlleyw, shuzhouliu, SukkaW, Tiphereth-A, x2e6, Ycrpro, yifan0305, zeningc, hcx2012Git

## Introduction

It is well known that segment trees can support fast queries for information over a certain interval, such as maximum subarray sum, interval sum, and matrix chain multiplication, etc.

However, there is a problem: the interval query of a regular segment tree may still be too slow in some problematic scenarios.

Simply put, when building a segment tree, we need to perform $O(n)$ merge operations, and each interval query requires $O(\log{n})$ merge operations. For queries like interval sum, this is acceptable, but when we need to query information with high merge complexity such as linear basis ($O(\log^2{w})$), even doing $O(\log{n})$ merge operations may sometimes be unacceptable in terms of time.

The so-called "Cat Tree" is a static segment tree that does not support modifications but supports fast interval queries.

Constructing such a static segment tree requires $O(n\log{n})$ merge operations, but the query complexity is accelerated to $O(1)$ merge operations.

When processing special information like linear basis, the complexity can even be reduced to $O(n\log^2{w})$.

## Principle

When querying the sum of information over the interval $[l,r]$, we find the LCA (Lowest Common Ancestor) of the nodes representing $[l,l]$ and $[r,r]$ on the segment tree. Let this node $p$ represent the interval $[L,R]$. We will discover some very interesting properties:

1. The interval $[L,R]$ must contain $[l,r]$. Obviously, because it is both an ancestor of $l$ and an ancestor of $r$.

2. The interval $[l,r]$ must cross the midpoint of $[L,R]$. Since $p$ is the LCA of $l$ and $r$, this means $p$'s left child is an ancestor of $l$ but not $r$, and $p$'s right child is an ancestor of $r$ but not $l$. Therefore, $l$ must lie in the interval $[L,\mathit{mid}]$, and $r$ must lie in $(\mathit{mid},R]$.

With these two properties, we can reduce the query complexity to $O(1)$.

## Implementation

Specifically, when building the tree, for a node on the segment tree representing the interval $(l,r]$:

Unlike a traditional segment tree that only stores the sum of $[l,r]$ in this node, we additionally store the suffix sum array of $(l,\mathit{mid}]$ and the prefix sum array of $(\mathit{mid},r]$.

This way, the construction complexity becomes $T(n)=2T(n/2)+O(n)=O(n\log{n})$, and similarly, the space complexity increases from the original $O(n)$ to $O(n\log{n})$.

Now comes the key part: the query.

If we query the interval $[l,r]$, we find the LCA of the nodes representing $[l,l]$ and $[r,r]$, denoted as $p$.

Based on the two properties above, $l,r$ lie within the interval contained by $p$ and must cross $p$'s midpoint.

This implies a very important fact: we can use the prefix and suffix sum arrays stored in $p$ to split $[l,r]$ into $[l,\mathit{mid}]+(\mathit{mid},r]$ and thus assemble $[l,r]$.

This process requires only $O(1)$ merge operations!

But it seems we have overlooked something?

It seems that the complexity of finding the LCA is still not $O(1)$; brute force is $O(\log{n})$, binary lifting is $O(\log{\log{n}})$, and converting to an Sparse Table is too costly...

## Heap-style Construction

Specifically, we extend this sequence to a power of $2$, then build a segment tree.

At this point, we find that the LCA index of two nodes on the segment tree is exactly the longest common prefix (LCP) of their binary representations.

After a little thought, we can discover that in binary, for $x$ and $y$, `lcp(x,y)=x>>digits[x^y]` (where `digits[x]` represents the number of bits in $x$'s binary representation, i.e., $\lfloor \log_2 x \rfloor+1$).

Thus, we can preprocess a `digits` array to easily accomplish the LCA task.

In this way, we have constructed a Cat Tree.

Since building the tree involves computing prefix and suffix sums, for linear basis information where merging is $O(\log^2{w})$ but prefix/suffix sum computation is $O(n\log{n})$, using a Cat Tree can optimize static interval linear basis from $O(n\log^2{w}+m\log^2{w}\log{n})$ to $O(n\log{n}\log{w}+m\log^2{w})$.

### References

-   [immortalCO's blog](https://immortalco.blog.uoj.ac/blog/2102)
-   [\[Kle77\]](http://ieeexplore.ieee.org/document/1675628/) V. Klee, "Can the Measure of be Computed in Less than O (n log n) Steps?," Am. Math. Mon., vol. 84, no. 4, pp. 284–285, Apr. 1977.
-   [\[BeW80\]](https://www.tandfonline.com/doi/full/10.1080/00029890.1977.11994336) Bentley and Wood, "An Optimal Worst Case Algorithm for Reporting Intersections of Rectangles," IEEE Trans. Comput., vol. C–29, no. 7, pp. 571–577, Jul. 1980.
