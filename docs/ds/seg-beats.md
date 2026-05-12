This article explains the segment tree techniques for historical range extrema mentioned by jiangly in the [2016 National Training Team paper](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2016%E8%AE%BA%E6%96%87%E9%9B%86.pdf).

## Range Extrema

Broadly speaking, a range extremum operation means applying, to every number in an interval $[l,r]$, $x$ under $\max$ or $\min$, that is, $a_i=\max(a_i,x)$ or $a_i=\min(a_i,x)$.

???+ note "[HDU5306 Gorgeous Sequence](https://acm.hdu.edu.cn/showproblem.php?pid=5306)"
    Maintain a sequence $a$ and perform the following operations:
    
    1.  `0 l r t` $\forall l\le i\le r,~ a_i=\min(a_i,t)$.
    2.  `1 l r` output $\max\limits_{i=l}^r a_i$.
    3.  `2 l r` output $\sum\limits_{i=l}^r a_i$.
    
    Multiple test cases. It is guaranteed that $T\le 100,~\sum n,\sum m\le 10^6$.

Taking range $\min$ means only numbers greater than $t$ are changed. Therefore, the target of this operation is no longer the whole interval, but "the numbers in this interval that are greater than $t$". This leads to the following idea: for each node, maintain the maximum value $Max$, the second maximum value $Se$, the interval sum $Sum$, and the number of maximum values $Cnt$. Now consider applying $t$ under $\min$ to an interval.

1.  If $Max\le t$, this $t$ clearly has no effect, so return directly.
2.  If $Se<t < Max$, then $t$ can update the maximum values in the current interval. Add $Cnt(t-Max)$ to the interval sum, update $Max$ to $t$, and set a tag.
3.  If $t\le Se$, then we do not know how many numbers are involved in the update. Our strategy is to recursively go down by brute force, then push information back up.

What is the complexity of this algorithm? Potential analysis gives a complexity of $O(m\log n)$. See the paper for the detailed analysis.

```cpp
--8<-- "docs/ds/code/seg-beats/seg-beats_1.cpp"
```

???+ note "[BZOJ4695 The Fake Female Player](https://loj.ac/p/6565)"
    Maintain a sequence $a$ and perform the following operations:
    
    1.  `1 l r x` $\forall l\le i\le r,~ a_i=a_i+x$.
    2.  `2 l r x` $\forall l\le i\le r,~ a_i=\max(a_i,x)$.
    3.  `3 l r x` $\forall l\le i\le r,~ a_i=\min(a_i,x)$.
    4.  `4 l r` output $\sum\limits_{i=l}^r a_i$.
    5.  `5 l r` output $\max\limits_{i=l}^r a_i$.
    6.  `6 l r` output $\min\limits_{i=l}^r a_i$.
    
    $n,m\le 5\times 10^5,~|a_i|\le 10^8$. All type $1$ operations satisfy $|x|\le 10^3$, and the remaining operations satisfy $|x|\le10^8$.

Using the same method, maintain maximum, second maximum, maximum count, minimum, second minimum, minimum count, and interval sum. Besides this information, we also need to maintain tags for range $\max$, range $\min$, and range add. Compared with the previous problem, this involves the order of pushing down tags. We use the following strategy:

1.  The range-add tag has the highest priority; the other two tags have equal priority.
2.  When adding a tag $v$ to a node, besides using $v$ to update the satellite information and the node's range-add tag, use this v to update the range $\max$ and range $\min$ tags.
3.  When applying a node with $v$ under $\min$ (ignoring the brute-force search process here and assuming the tag satisfies the condition for being added), besides updating the satellite information, compare it with the range $\max$ tag. If $v$ is smaller than the range $\max$ tag, all numbers will eventually become v, so also change the range $\max$ tag to $v$. Otherwise, do nothing.
4.  Applying range v under $\max$ is analogous.

When maintaining information, if there is only one or two numbers, the maintained sets may overlap; for example, one number may be both the maximum and the second minimum, so special handling is needed.

```cpp
--8<-- "docs/ds/code/seg-beats/seg-beats_2.cpp"
```

jiangly proved that the complexity of this algorithm is $O(m\log^2 n)$.

???+ note "Mzl loves segment tree"
    There are two sequences $A,B$. Initially all numbers in $B$ are $0$. Maintain the following operations:
    
    1.  Apply range to $A$ under $\min$.
    2.  Apply range to $A$ under $\max$.
    3.  Apply range add to $A$.
    4.  Query the range sum of $B$.
    
    After each operation, if the value of $A_i$ changes, add to $B_i$ by $1$. $n,m\le 3\times 10^5$.

First consider the easiest operation, range add. As long as $x\neq 0$, every number in the whole interval changes, so we only need to apply one range add to B.

For range extrema operations, notice that setting tags and pushing down tags correspond one-to-one with the $B$ array. Essentially, you divide the values of the sequence into three classes: maximum values, minimum values, and non-extreme values, and maintain them separately. Although you do not explicitly build the sets of extrema, this does not prevent maintenance. Therefore, when setting a tag, update the information for $B$ at the same time. Note that this is not setting a tag on $B$, but updating information. When querying, query on $A$; when pushing down tags, update information for $B$ at the same time. After finding the needed node, return the information of $B$. In essence, this operation hands the extremum information over to $B$ for maintenance. The issue of overlapping sets still needs to be handled.

???+ note "[CTSN loves segment tree](https://www.luogu.com.cn/problem/U180387)"
    Maintain two sequences $a,b$ and perform the following operations:
    
    1.  `1 l r x` $\forall l\le i\le r,~ a_i=\min(a_i,x)$.
    2.  `2 l r x` $\forall l\le i\le r,~ b_i=\min(b_i,x)$.
    3.  `3 l r x` $\forall l\le i\le r,~ a_i=a_i+x$.
    4.  `4 l r x` $\forall l\le i\le r,~ b_i=b_i+x$.
    5.  `5 l r` output $\max\limits_{i=l}^r (a_i+b_i)$.
    
    $n,m\le 3\times 10^5,~|a_i|,|b_i|,|x|\le 10^9$.

Divide, in interval $[l,r]$, the candidate answers $A_i+B_i$ into four classes: neither $A_i,B_i$ is the interval maximum of sequences $A,B$; $A_i$ is the interval maximum of sequence $A$ but $B_i$ is not the interval maximum of sequence $B$; $A_i$ is not the interval maximum of sequence $A$ but $B_i$ is the interval maximum of sequence $B$; and both $A_i,B_i$ are interval maxima of sequences $A,B$. Denote them as $C_{0,0},C_{1,0},C_{0,1},C_{1,1}$ respectively. In addition, normally maintain the interval maximum and second maximum of sequences $A,B$. When pushing down range-add tags and $\min$ tags, the handling of $A,B$ maximum and second maximum values is the same as in the two examples above. A tag on $A$ under $\min$ affects $C_{1,1}$ and $C_{1,0}$, while a tag on $B$ affects $C_{1,1}$ and $C_{0,1}$. Additions on $A,B$ affect all of $C_{0,0},C_{1,0},C_{0,1},C_{1,1}$. Just pay attention to boundary cases where $C_{0,0},C_{1,0},C_{0,1}$ do not exist. For example, interval $[i,i]$ only has the maxima of $A,B$ and $C_{1,1}$.

Next, consider how to maintain $C_{0,0},C_{1,0},C_{0,1},C_{1,1}$ during `pushup`. After finishing the update of the maxima of $A,B$, discuss whether the maxima of the left and right children for $A,B$ are equal to the $A,B$ maxima of the current node. We explain using the left child; the right child is handled similarly:

-   If both the $A,B$ maxima of the left child are equal to the $A,B$ maxima of the current node, then the left child's $C_{0,0},C_{1,0},C_{0,1},C_{1,1}$ contribute to the current node's $C_{0,0},C_{1,0},C_{0,1},C_{1,1}$ respectively.
-   If the left child's $A$ maximum is equal to the current node's $A$ maximum, but its $B$ maximum is not equal, then the left child's $C_{1,0},C_{1,1}$ contribute to this node's $C_{1,0}$, and $C_{0,0},C_{0,1}$ contribute to this node's $C_{0,0}$.
-   If the left child's $A$ maximum is not equal to the current node's $A$ maximum, but its $B$ maximum is equal, then the left child's $C_{0,1},C_{1,1}$ contribute to this node's $C_{0,1}$, and $C_{0,0},C_{1,0}$ contribute to this node's $C_{0,0}$.
-   If both the $A,B$ maxima of the left child are not equal to the $A,B$ maxima of the current node, then the left child's $C_{0,0},C_{1,0},C_{0,1},C_{1,1}$ only contribute to this node's $C_{0,0}$.

The query answer for an interval is $\max(C_{0,0},C_{1,0},C_{0,1},C_{1,1})$.

Since range $\min$ and range add must both be maintained, the complexity is still $O(m\log^2 n)$.

```cpp
--8<-- "docs/ds/code/seg-beats/seg-beats_4.cpp"
```

### Summary

In this section, we introduced four example problems, explaining maintenance of basic range extrema operations, priority handling among multiple tags, the idea of classifying value sets, and maintaining multiple classes. In essence, the basic idea for handling range extrema is classified maintenance and efficient merging of set information. In the next section, we discuss historical range extrema problems.

## Historical Extrema Problems

### Historical Extrema Are Not Persistence

Note that the historical extrema problems discussed in this chapter are different from so-called persistent data structures. We call these special problems historical extrema problems. Historical extrema problems can be divided into three types.

#### Historical Maximum

Simply put, the historical maximum at a position is the maximum value that has ever appeared at the current position. Formally, define an auxiliary array $B$, initially identical to $A$. After every operation on $A$, take the $\max$ over the whole array:

$$
\forall i\in[1,n],\ B_i=\max(B_i,A_i)
$$

At this point, $B_i$ is called the historical maximum of this position.

#### Historical Minimum

The definition is similar to historical maximum. After every operation on $A$, take the $\min$ over the whole array. At this point, $B_i$ is called the historical minimum of this position.

#### Historical Version Sum

The auxiliary array $B$ is initially all $0$. After each operation, add the entire array $A$ to array $B$:

$$
\forall i\in[1,n], \ B_i=B_i+A_i
$$

We call $B_i$ the historical version sum at position $i$.

Next, we divide historical extrema problems into four classes for discussion.

### Problems That Can Be Handled with Tags

???+ note "[CPU Monitoring](https://www.luogu.com.cn/problem/P4314)"
    Sequences $A,B$ are initially the same:
    
    1.  Apply range assignment to $A$ with $x$.
    2.  Apply range add to $A$ by $x$.
    3.  Query $A$'s range $\max$.
    4.  Query $B$'s range $\max$.
    
    After each operation, we perform one update: $\forall i\in [1,n],\ B_i=\max(B_i,A_i)$. $n,m\le 10^5$.

First ignore operation 1. With only range add operations, maintain a tag $Add$ representing the value currently added to the interval; this tag can solve the range $\max$ problem. Now consider historical range $\max$. Define a tag $Pre$, whose meaning is: within the lifetime of this tag, the historical maximum value of the $Add$ tag.

This definition may be somewhat vague, so first explain the lifetime of a tag. A tag goes through the following process:

1.  It is created at node $u$.
2.  While node $u$ receives several new tags, it is merged with those new tags of the same type.
3.  The tag of node $u$ is pushed down to the children of $u$, and the tag of $u$ is cleared.

We regard the interval from step 1 to before step 3 as the lifetime of the tag at node $u$. After two tags merge into one tag, their lifetimes also merge, taking the earlier creation time as the beginning of the lifetime. Equivalently, this is the time interval from the last time this node's tag was pushed down to the current time.

Why define lifetime? With this concept, we can prove that within the lifetime of a node's tag, its child nodes do not change and retain the state they had before this lifetime. The reason is simple: during this period, no tag is pushed down.

Thus, the historical maximum of $Add$ within the current tag lifetime can be updated into the child nodes' tags and information, because the child nodes' tags and information have not changed during this time. When pushing the tag of $u$ down to its child $s$, it is easy to see that

$$
Pre_s=\max(Pre_s,Pre_u+Add_s),Add_s=Add_u+Add_s
$$

Updating information is similar: use the corresponding tags to update it.

Now consider operation 1.

A range assignment operation changes all numbers into one number. After that, whether we apply range addition/subtraction or assignment, all numbers in the whole interval remain the same, unless the current tag lifetime is ended by pushing the tag down. Therefore, all tags after the first range assignment can be treated as range assignment tags. In other words, the lifetime of a tag is roughly divided into two phases:

1.  Merging several addition/subtraction operation tags, without receiving any assignment tag.
2.  Assignment operation tags, with no so-called addition/subtraction tag because addition/subtraction tags have been converted into assignment tags.

Thus, split this node's `Pre` tag into $(P_1,P_2)$. $P_1$ represents the maximum addition/subtraction tag in the first phase; $P_2$ represents the maximum assignment tag in the second phase. With a similar method, we can perform tag pushdown and information updates. The time complexity is $O(m\log n)$. Note that this problem has no operation that takes range extrema with $x$.

```cpp
--8<-- "docs/ds/code/seg-beats/seg-beats_3.cpp"
```
