author: Xarfa

## Introduction

A wavelet tree is a data structure for solving range $K$-th largest queries. Its constant factor and conceptual difficulty are much lower than a Chairman Tree's. At the same time, a wavelet tree is closely tied to "$K$-th largest", so it is a sorting-based data structure.

Prerequisite: [Chairman Tree](persistent-seg.md#chairman-tree)

## Process

### Building the Tree

Building a wavelet tree is relatively simple, but compared with other trees, it is still somewhat complex.

![](./images/dividing-1.svg)

As shown in the figure, each layer has an array that appears unordered. In fact, every number marked in red is **to be assigned to the left child**. What is the assignment rule? Compare with **the median of this layer**: if the value is less than or equal to the median, assign it to the left; otherwise assign it to the right. However, note that this is not strictly **less than or equal goes left, otherwise goes right**. This is because median values may be equal, and parity of $N$ also matters. The code below demonstrates a clever handling; you can refer to it.

We cannot sort every layer every time. Even ignoring constants, the theoretical complexity would not pass. Think about finding the median: one sort is enough. Why? For example, the median of $l,r$ is actually `num[mid]` after sorting.

Two key arrays:

`tree[log(N),N]`: the tree itself, storing all values, with space complexity $O(n\log n)$.
`toleft[log(N),n]`: for each layer, the number of values among positions 1 to i that enter the left child. This needs to be understood as a prefix sum.

???+ note "Implementation"
    ```pascal
    procedure Build(left,right,deep:longint); // left,right are interval endpoints; deep is the current layer
    var
      i,mid,same,ls,rs,flag:longint; // flag is used to balance counts on the two sides
    begin
      if left=right then exit; // bottom layer reached
      mid:=(left+right) >> 1;
      same:=mid-left+1;
      for i:=left to right do 
        if tree[deep,i]<num[mid] then
          dec(same);
      
      ls:=left; // first pointer assigned to the left child
      rs:=mid+1; // first pointer assigned to the right child
      for i:=left to right do
      begin
        flag:=0;
        if (tree[deep,i]<num[mid])or((tree[deep,i]=num[mid])and(same>0)) then // condition for assigning left
        begin
          flag:=1; tree[deep+1,ls]:=tree[deep,i]; inc(ls);
          if tree[deep,i]=num[mid] then // balance counts on the two sides
            dec(same);
        end
        else
        begin
          tree[deep+1,rs]:=tree[deep,i]; inc(rs);
        end;
        toleft[deep,i]:=toleft[deep,i-1]+flag;
      end;
      Build(left,mid,deep+1); // continue
      Build(mid+1,right,deep+1);
    end;
    ```

### Query

First recall Chairman Tree queries. When querying the interval $K$-th smallest value with a Chairman Tree, we use $K$ as a reference: go left if the answer is on the left; if going right, subtract the number of values going left. The same idea applies to wavelet trees.

The difficult part of querying is **shrinking the interval**. In the figure below, the query is from $3$ to $7$, so the next layer only needs to query from $2$ to $3$. We define $[\text{left},\text{right}]$ as the shrunk interval (target interval), while $[l,r]$ is still the interval of the current node. Why mark the target interval? Because it is the **reference for deciding whether the answer is on the left or right**.

![](./images/dividing-2.svg)

???+ note "Implementation"
    ```pascal
    function Query(left,right,k,l,r,deep:longint):longint;
    var
      mid,x,y,cnt,rx,ry:longint;
    begin
      if left=right then // writing l=r is also fine, because the target interval must contain an answer
        exit(tree[deep,left]);
      mid:=(l+r) >> 1;
      x:=toleft[deep,left-1]-toleft[deep,l-1]; // count going left from l to left
      y:=toleft[deep,right]-toleft[deep,l-1]; // count going left from l to right
      ry:=right-l-y; rx:=left-l-x; // ry is count going right from l to right; rx is count going right from l to left
      cnt:=y-x; // count going to the left child from left to right
      if cnt>=k then // standard Chairman Tree idea
        Query:=Query(l+x,l+y-1,k,l,mid,deep+1) // l+x shrinks the left boundary; l+y-1 shrinks the right boundary. In the figure above, nodes 1 and 2 are discarded.
      else
        Query:=Query(mid+rx+1,mid+ry+1,k-cnt,mid+1,r,deep+1); // same interval shrinking, but to the right. Remember to subtract cnt from k.
    end;
    ```

## Properties

Time complexity: one query only needs $O(\log n)$; for $m$ queries, the complexity is $O(m\log n)$.

Space complexity: only $O(n\log n)$ numbers need to be stored.

Measured result: Chairman Tree: $1482 \text{ms}$, wavelet tree: $889 \text{ms}$. (Non-recursive, with smaller constants.)

## Applications of Wavelet Trees

Example: [Luogu P3157 [CQOI2011] Dynamic Inversion Pairs](https://www.luogu.com.cn/problem/P3157)

> Problem summary: Given a permutation of $n$ elements ($n\leq 10^5$) and m queries ($m\leq 5\times 10^4$), each query deletes one number from the permutation and asks for the number of inversion pairs after deleting it.

This problem can be solved with CDQ divide and conquer in $\Theta(n\log^2n)$ time and $\Theta(n)$ space, and CDQ also has excellent constants.

If the problem is changed to forced online, the usual solution is a Fenwick tree plus Chairman Tree tree-of-tree approach, with time complexity $\Theta(n\log^2n)$ and space complexity $\Theta(n\log^2n)$. The constant is slightly large, but it can still pass.

Using a wavelet tree, the problem can be solved online in $\Theta(n\log^2n)$ time and $\Theta(n\log n)$ space, with a much smaller constant than the tree-of-tree solution (roughly comparable to CDQ).

???+ warning "Note"
    For implementation convenience, this article divides the large array into two small arrays by the middle position value. That is, the wavelet tree below is equivalent to the merge-sort process rather than the quicksort process. The top-level large array is sorted, and the bottom level is the original array.

For each node in the wavelet tree, we call it a right node if and only if it is assigned to the right child on the next layer, i.e. values whose positions are later in the original array. Left nodes can be defined similarly. If the top layer is sorted while building the tree, similar to counting inversion pairs with merge sort, we can see that the number of inversions in an array is the sum, over every left node, of the number of right nodes before it.

Now consider deletion. Deleting a left node reduces the total inversion count by the number of right nodes before it, while deleting a right node reduces the count by the number of left nodes after it. Therefore, dynamically maintain "the number of right nodes before each left node" and "the number of left nodes after each right node". This can be maintained simply with Fenwick trees.

Note that when using Fenwick trees, we can only count contributions inside the same block of the wavelet tree and cannot jump out of the block. There is a clever way to handle this for Fenwick trees.

Consider that every block's index range on the wavelet tree must be of the form $[c\times 2^k+1,(c+1)\times 2^k]$, listed below (because the code does not process the bottommost layer of the wavelet tree, only layers up to the second-to-last are enumerated):

    [0001 0010] [0011 0100] [0101 0110] [0111 1000] [1001 1010] [1011 1100] [1101 1110] [1111 10000]  lev=1
    [0001 0010 0011 0100]   [0101 0110 0111 1000]   [1001 1010 1011 1100]   [1101 1110 1111 10000]    lev=2
    [0001 0010 0011 0100 0101 0110 0111 1000]       [1001 1010 1011 1100 1101 1110 1111 10000]        lev=3
    [0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111 10000]                lev=4

Recall the principle of Fenwick trees: when jumping upward, we do `x += lowbit(x)` each time. If we can guarantee that upward jumps do not leave the block, then only values inside the block are affected. Upward queries are similar.

To ensure upward jumps do not leave the block, it is enough to require $lowbit(x)<2^{lev}$ while jumping.

Downward jumps are handled completely differently. If each block's index is represented as 0-indexed, it has the form $[c\times 2^k,(c+1)\times 2^k)$. Therefore, right-shifting an index by k gives the block it belongs to. During downward jumps, just check whether the jump leaves the block.

Note that a Fenwick tree implemented this way may access the nearest power of two not less than n, so the array size cannot be only n.

Since modifications are needed on $\log n$ layers, and modifying layer $k$ costs $\Theta(k)$, the final time complexity is $\Theta(n\log n+m\log^2n)$.

Code:

```cpp
--8<-- "docs/ds/code/dividing/dividing_1.cpp"
```

## Postscript

Reference blog post: [link](https://blog.csdn.net/littlewhite520/article/details/70250722).
