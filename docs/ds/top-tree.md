author:F7487

## Self-Adjusting Top Tree

### Introduction

Self-Adjusting Top Tree is a data structure based on Top Tree theory that maintains a completely dynamic forest proposed by Tarjan and Werneck in their paper Self-Adjusting Top Trees in 2005, referred to as SATT.

Self-Adjusting Top Tree can implement operations such as chain modification/query, subtree modification/query, and non-local search of any tree in the forest.

Splay Tree is the basis of SATT, but the Splay Tree used by SATT is different from ordinary Splay in details (some extensions have been made).

### Problem introduction

Maintain a forest and support the following operations:

-   Delete and add an edge to ensure that there is still a forest before and after the operation.

-   Modify the weight of a simple path on a tree.

-   Modify the weight of the subtree rooted at a certain point.

-   Query the weight sum of a simple path on a certain tree.

-   Query the weight sum of the subtree rooted at a certain point.

### tree shrink

For any tree, we can use the **tree shrinkage** theory to shrink it into an edge.

Specifically, there are two basic operations for tree shrinkage: **Compress** and **Rake**. The Compress operation specifies a degree-$2$ point $x$. The two points adjacent to point $x$ are recorded as $y$ and $z$. We connect a new edge $yz$; connect the point $x$, edge $xz$, and edge The information of $xy$ is stored in $yz$ and deleted. As shown in the picture.

![](./images/top-tree1.svg)

The Rake operation specifies a degree-$1$ point $x$, and point $x$'s adjacent point $y$ must have degree greater than $1$. Let another neighbor of point $y$ be $z$. We put the information of point $x$ and edge $xy$ into edge $yz$ Save them in and delete them. As shown in the picture.

![](./images/top-tree2.svg)

It is not difficult to prove that any tree can be contracted to one edge using only the Compress operation and the Rake operation, as shown in the figure.

![](./images/top-tree3.svg)

### cluster

For convenience of expression, we record the original tree before any operation as $T$. The tree after performing some tree shrinking operations on $T$ (no operations are required) is recorded as $T_x$.

We study the information contained in an edge in a certain $T_x$.

In addition to carrying its own information (of course, if this edge does not exist in $T$, this edge has no information of its own), it may also contain information about other points and edges merged to it through Compress/Rake operations. We might as well select an edge from the tree shrinkage process in the figure below to see which points and edges the information it contains represents in $T$.

![](./images/top-tree4.svg)

As shown in the figure, the selected edge and the corresponding graph are circled in red.

It can be seen that the information contained in this edge is connected to the points and edges represented in $T$. We can infer that the information stored on any edge in any $T_x$ is generally represented as a connected subgraph in $T$. We call such a connected subgraph a cluster.

However, a cluster is an **incomplete subgraph** that contains edge vertices that are not contained by the cluster itself. So we call these endpoints the **Endpoint** of the cluster, the points it contains that connect the subgraph are called **Internal Node**, and the edges that connect the subgraph are called **Internal Edge**.

For any cluster, it has the following properties:

1.  Clusters only store and maintain information about interior points and interior edges.

2.  A cluster has two endpoints. These two endpoints are the two points in $T_x$ connected by the edges representing that cluster. The path between the two endpoints is called **Cluster Path**; remember the two endpoints of a cluster as $x$ and $y$. We will use $C(x,y)$ below to represent this cluster.

3.  Interior points are only connected to endpoints or interior points.

In particular, for each edge in $T$, it is an independent cluster (containing only the edge's own information). We call this cluster **Base Cluster**. For the final result obtained by shrinking $T$ to only one edge, namely $T_x$, the cluster represented by that edge contains the information of the entire tree $T$ except for the two endpoints. This cluster is called **Root Cluster**.

![](./images/top-tree5.svg)

As shown in the figure, the base cluster mentioned above has been marked with a red line.

Looking at the Compress/Rake operation from a cluster perspective, we find that these two operations will "merge two clusters into one", leaving a new cluster. Therefore, the process of tree shrinkage is also the process of merging all base clusters into one cluster.

So we can also get the following figure, which is another representation of a series of tree shrink operations.

![](./images/top-tree6.svg)

### Top Tree

We now want to represent the entire process of tree shrinkage for a certain tree.

We can use the above two methods to represent this process, but this is very troublesome. If the tree shrinkage proceeds $n$ steps, we have to use $n$ tree to represent the entire tree shrinkage.

To consider a simpler representation of performing a certain tree shrinkage on a certain tree, we introduce **Top Tree**.

![](./images/top-tree7.jpg)

As shown in the figure, it is a Top Tree based on the shrinkage method above and the original tree.

Top Tree has the following properties;

1.  A Top Tree corresponds to an original tree and a method for tree shrinkage. Each node of the Top Tree represents a certain edge in a certain $T_x$, that is, a certain cluster formed during the tree shrinkage process. The points in the shape of $N_x$ in the figure represent the clusters formed by the operation `compress(x)`.

2.  A node in the Top Tree has two sons (each representing a cluster). The cluster represented by this node is a new cluster obtained by merging the two clusters through the Compress or Rake operation.

3.  The leaf nodes of Top Tree are base clusters, and their root nodes are root clusters. Therefore, we layer according to the topological order of a Top Tree, and each layer of it represents a $T_x$.

### Implement information maintenance using three-dimensional Self-Adjusting Top Tree

#### principle

Top Tree greatly simplifies the tree shrinkage process, allowing us to see the possibility of maintaining the information on the tree by maintaining the tree shrinkage process. SATT maintains the information on the tree through this principle.

Note that the process of tree shrinkage is also a process of continuous addition of information on the tree. We execute `compress(x)` once, and the information at $x$ point begins to appear in a certain cluster from this moment on, affecting our statistical results.

If we now use Top Tree to maintain a certain tree $T$, each point and edge on the tree has a weight, and what we want to maintain is the weight sum of $T$.

Now, during maintenance, we need to modify the weight of a certain point in $T$, point $x$. Obviously, we need to change the node information of all cluster information in Top Tree including $x$. In this way, the single time complexity will be $O(n)$ level.

However, if we select a point with a very small number of nodes whose cluster information contains $x$ in the Top Tree, that is to say, add its information to the cluster as late as possible, the time complexity of our single operation will be greatly improved. As shown in the picture.

![](./images/top-tree8.jpg)

SATT maintains the information on the tree by modifying the order in which **a certain point/a certain path** is added to the cluster during the tree shrinkage process (to reduce its single time complexity when it is modified).

### actual structure

We first root an original tree $T$ hierarchically, and then we consider the root cluster of the Top Tree in a certain tree shrinkage order. It has two endpoints. We make one of the endpoints the root of the original tree, and the other endpoint is optional.

![](./images/top-tree9.jpg)

As shown in the figure, a set of endpoints is selected for the root cluster. The endpoints are also circled when labeling the cluster.

It can be seen from the basic operation of tree shrinkage that the information of the points and edges $(j,h,c,jh,hc)$ on the cluster path is finally added to $C(k,g)$ through the Compress operation, while the non-cluster path point $(a,b,i,f,g,e,ig,\cdots)$ is added to $C(k,g)$ through the Rake operation.

We separate the cluster path, which is a tree with a special shape (a chain), and we build a top tree for this tree (the tree it represents shrinks in any order).

![](./images/top-tree10.jpg)

We call this structure **Compress Tree**, because the two sons of any point in this Top Tree are merged into their father through the Compress operation.

The nodes in the Compress Tree are called **Compress Node**. Only considering the current cluster path, a non-leaf Compress Node represents a compress process, which means merging the left son and right son information, and then adding the point $x$ information stored in `compress(x)` itself. This Compress Tree maintains the $C(k,g)$ cluster path information.

In addition, in Compress Tree, we actually put some restrictions on the Top Tree used. Note that Compress Tree maintains a chain with two different depths of midpoints in $T$. We stipulate that the in-order traversal order of the base clusters in Compress Tree is consistent with the depth of the corresponding edges in $T$, and the smaller the in-order traversal, the shallower the depth. Similarly, the same is true for the relationship between `compress(x)` corresponding to each point $x$.

Now to maintain the information of those non-cluster paths, we assume that the points and edges on these non-cluster paths have formed maximal clusters, and these maximal clusters are formed by rake each other among the smaller clusters circled in blue. For the process of merging some smaller clusters to form a maximal cluster, we use a ternary tree to represent it. Similarly, we call this structure **Rake Tree**, and correspondingly the points in the Rake Tree are **Rake Node**. Each Rake Node represents a cluster, which is formed by rake its left son and right son to the smaller cluster represented by its son. Specifically, you can see the figure below. It can be seen that each point in Rake Tree represents a smaller cluster with the same endpoint in $T$.

![](./images/top-tree11.jpg)

As shown in the figure, the blue circles show large clusters, and the yellow circles show smaller clusters.

For those smaller clusters, we perform the same processing on them, select cluster paths for them, build Compress Tree,... By recursing in this way, we build many Compress Trees and Rake Trees that represent the tree shrinkage process.

![](./images/top-tree12.jpg)

The picture above shows the Rake-Compress Tree of the original tree (because each Rake Node is connected to a Compress Tree, it appears as a Rake Tree connected to many Compress Trees) and the Compress Tree representing the root cluster path.

Consider splicing these trees together in some way so that they form an ordered whole. Remember that the common endpoint of the set of minimal clusters represented by a Rake Tree is the point $x$. We add the other endpoint of non-$x$ to the middle son of these Rake Node (a Compress Tree collection), but still maintain the basic properties of middle-order traversal and Top Tree, as shown in the figure.

![](./images/top-tree13.jpg)

This step is equivalent to allowing the Rake operation to add a certain $T$ midpoint to occur directly in the Compress Tree. This not only allows us to correctly maintain the information of the Rake Node (just merge the three son information), but also makes the structure of our Compress Tree more complete. Next, we change the Compress Tree to a ternary tree. If the public endpoint of a Rake Tree is the point $x$, we will hang the Rake Tree at the middle son of `compress(x)`, as shown in the figure.

![](./images/top-tree14.jpg)

At this time, the meaning of the trifurcated `compress(x)` point is to first rake its son to the cluster path, and then count the information of the left and right sons and point $x$.

Finally, we deal with the Compress Tree of the root cluster path: consistent with all other Compress Trees, we add its two endpoints in in-order traversal, so that its root stores the entire $T$ information.

So we implemented the information maintenance of a tree using three-dimensional Self-Adjusting Top Tree.

![](./images/top-tree15.jpg)

To summarize, SATT has the following properties:

1.  SATT consists of Compress Tree and Rake Tree. Compress Tree is a special Top Tree; Rake Tree is a ternary tree. They both correspond to the process of tree shrinkage of a tree.

2.  A point in the Compress Tree has at most three sons. Compress Tree can perform rotation operations similar to Splay Tree (just ensure that the order traversal remains unchanged, and keep the children unchanged when rotating a point).

3.  The points in the Rake Tree must have a middle son. Rake Tree can perform rotation operations similar to Splay Tree (just ensure that the order traversal remains unchanged, and keep the children unchanged when rotating a point).

4.  The topological order of SATT reflects the tree shrinkage order of the original tree $T$.

What we mentioned above is "modify the order in which information is added to the cluster at a certain point/path during the tree shrinkage process." Can SATT be implemented? The answer is yes.

In SATT, there is an operation `access(x)`, its function is to make a certain point $x$ become a non-root endpoint of the root cluster, and at the same time make `compress(x)` become the root of SATT.

We can use the `access(x)` operation to evenly distribute the complexity of $O(\log n)$ so that the point representing `compress(x)` in SATT is rotated to the root of the entire SATT tree. According to the fourth property of SATT, we change the order of operations of `compress(x)` so that it is executed at the latest, and the information of point $x$ is also added last; in this way, when we want to modify the information of point $x$, we only need to update `compress(x)`.

### Code implementation

#### Push class function

First consider uploading information, that is, the `Pushup(x)` function. When considering maintaining information for a certain node in SATT, first discuss whether this point is in the Compress Tree or the Rake Tree. The reasons can be seen above and will not be repeated. The following is an example of maintaining the subtree size of a certain point.

```cpp
// ls(x) left son of x
// rs(x) right son of x
// ms(x) middle son of x
// type==0 is Compress Node
// type==1 is Rake Node
void pushup(int x, int type) {
  if (type == 0)
    size[x] = size[rs(x)] + size[ms(x)] + 1;
  else
    size[x] = size[rs(x)] + size[ms(x)] + size[ls(x)];
  return;
}
```

Query the size of the subtree of point $x$ and access it to the SATT root. The answer is the size of its son $+1$; because according to the above, after Access, the son is its true subtree.

Then consider transmitting information, that is, the `Pushdown(x)` function. If we want to make overall modifications to a certain subtree in the original tree, a natural idea is to directly access this node to the SATT root node and put a mark on its middle son. In the same way, when querying a subtree, directly Access and then query the middle child.

If we want to make overall modifications to a certain path in the original tree, we expose the two endpoints of the path, where `expose(x, y)` means point $x$ becomes the root node of $T$, and point $y$ becomes the other endpoint of the root cluster. Correspondingly on the SATT, the Compress Tree of the root cluster is exactly the path from $x$ to $y$. So just put a mark on the Compress Tree of the root cluster. Similarly, to query a chain, expose it and then query the root node.

So we know how to solve the problem introduced by the problem.

```cpp
void pushdown(int x, int type) {
  if (type == 0) {
    // processing chain
    chain[ls(x)] += chain[x] chain[rs(x)] += chain[x];
    val[ls(x)] += chain[x];
    val[rs(x)] += chain[x];
    // Processing subtrees
    subtree[ls(x)] += subtree[x];
    subtree[rs(x)] += subtree[x];
    subtree[ms(x)] += subtree[x];
    val[ls(x)] += subtree[x];
    val[rs(x)] += subtree[x];
    val[ms(x)] += subtree[x];
    subtree[x] = 0;
  } else {
    subtree[ls(x)] += subtree[x];
    subtree[rs(x)] += subtree[x];
    subtree[ms(x)] += subtree[x];
    val[ls(x)] += subtree[x];
    val[rs(x)] += subtree[x];
    val[ms(x)] += subtree[x];
    subtree[x] = 0;
  }
  return;
}

// Download tag
void pushall(int x, int type) {
  if (!isroot(x)) pushall(father[x], type);
  pushdown(x, type);
  return;
}
```

#### Splay class function

We know that both Rake Tree and Compress Tree in SATT can be rotated, which means they can be maintained using Splay. So we can write the following code:

```cpp
// Is the middle son of a node or has no father
// ls the left son of a SATT node
// rs the right son of a SATT node
// ms is the middle son of a SATT node
// type==1 in Rake Tree
// type==0 in Compress Tree
bool isroot(int x) { return rs(father[x]) != x && ls(father[x]) != x; }

bool direction(int x) { return rs(father[x]) == x; }

void rotate(int x, int type) {
  int y = father[x], z = father[y], d = direction(x), w = son[x][d ^ 1];
  if (z) son[z][ms(z) == y ? 2 : direction(y)] = x;
  son[x][d ^ 1] = y;
  son[y][d] = w;
  if (w) father[w] = y;
  father[y] = x;
  father[x] = z;
  pushup(y, type);
  pushup(x, type);
  return;
}

void splay(int x, int type, int goal = 0) {
  pushall(x, ty);  // Download tag
  for (int y; y = father[x], (!isroot(x)) && y != goal; rotate(x, ty)) {
    if (father[y] != goal && (!isroot(y))) {
      rotate(direction(x) ^ diretion(y) ? x : y, type);
    }
  }
  return;
}
```

It is worth noting that the functions `direction` and `isroot` are different from ordinary Splay. Because no matter how this point turns, the middle son of this point will not change.

#### Access class functions

The meaning of `access(x)` is: rotate point $x$ to the root of the entire SATT, so that point $x$ becomes one of the two endpoints of the root cluster (the other endpoint is the root node of $T$). At the same time, the structure of the original tree and the root of the original tree cannot be changed.

In order to realize `access(x)`, we first rotate it to the root of the Compress Tree where it is located, and then remove the right son of point $x$, so that point $x$ becomes the endpoint of the corresponding cluster of the Compress Tree where it is located.

```cpp
if (rs(x)) {
  int y = new_node();
  setfather(ms(x), y, 0);
  setfather(rs(x), y, 2);
  rs(x) = 0;
  setfather(y, x, 2);
  pushup(y, 1);
  pushup(x, 0);
}
```

If $x$ has reached the root at this point, exit; if not, perform the following steps to let it cross the Rake Tree above it:

1.  Spread its parent node (must be a Rake Node) to the root of its Rake Tree;

2.  Spread the parent node of $x$ (must be a Compress Node) to its Compress Tree root.

3.  If the parent node of $x$ has a right son, exchange point x with the right child of the parent node, update the information, and then exit.

4.  If the parent node has no right son, then let point $x$ become the right son of the parent node first. At this time, the original parent node of point $x$ has no middle son. According to the properties of Rake Node above, it cannot exist. So call the `Delete` function, delete it, and then exit.

The two steps 1 and 2 are collectively called **Local Splay**. The two steps 3 and 4 are collectively called **Splice**. But for our convenience, we write them all in the `Splice(x)` function.

The `Delete(x)` function mentioned above looks like this:

1.  Check whether the point $x$ to be deleted has a left son. If so, continue to rotate the subtree of the left son to below the point $x$ (become the new left son), and then change the right son (if any) into the right son of the left son. At this time, the left son of point $x$ replaces the point $x$. This is equivalent to Splay's merge operation.

2.  If there is no left son, directly let its right son replace $x$.

It is not difficult to find that `Splice(x)` changes the endpoint selection of some clusters in the original tree. After one splice is completed, we regard the parent node of point $x$ as the new point $x$ and perform the next splice.

In the end, we will find that the point $x$ we want to operate at the beginning must be at the right end of the Compress Tree of the root cluster. We only need to do the **Global Splay** one last time and twist it to the root of the SATT.

```cpp
// ls the left son of a SATT node
// rs the right son of a SATT node
// ms is the middle son of a SATT node
// son[x][0] ls
// son[x][1] rs
// son[x][2] ms
// type==1 in Rake Tree
// type==0 in Compress Tree
int new_node() {
  if (top) {
    top--;
    return Stack[top + 1];
  }
  return ++tot;
}

void setfather(int x, int fa, int type) {
  if (x) father[x] = fa;
  son[fa][type] = x;
}

void Delete(int x) {
  setfather(ms(x), father[x], 1);
  if (ls(x)) {
    int p = ls(x);
    pushdown(p, 1);
    while (rs(p)) p = rs(p), pushdown(p, 1);
    splay(p, 1, x);
    setfather(rs(x), p, 1);
    setfather(p, father[x], 2);
    pushup(p, 1);
    pushup(father[x], 0);
  } else
    setfather(rs(x), father[x], 2);
  Clear(x);
}

void splice(int x) {
  // local splay
  splay(x, 1);
  int y = father[x];
  splay(y, 0);
  pushdown(x, 1);
  // splice
  if (rs(y)) {
    swap(father[ms(x)], father[rs(y)]);
    swap(ms(x), rs(y));
  } else
    Delete(x);
  pushup(x, 1);
  pushup(y, 0);
}

void access(int x) {
  splay(x, 0);
  if (rs(x)) {
    int y = new_node();
    setfather(ms(x), y, 0);
    setfather(rs(x), y, 2);
    rs(x) = 0;
    setfather(y, x, 2);
    pushup(y, 1);
    pushup(x, 0);
  }
  while (father[x]) {
    splice(father[x]);
    x = father[x];
    pushup(x, 0);
  }
  splay(x, 0)  // global splay
}
```

If we want a point to become the root of the original tree, then we will access the point $x$ to the root node of SATT. It can be seen that at this time, the point $x$ is already an endpoint of the cluster in the final state. It can be seen from the in-order traversal properties of Compress Tree that if the Compress Tree where point $x$ is located is reversed (the left and right sons of all points are swapped), the point $x$ will become the root of the original tree. In the specific implementation, we mark the point $x$ with a flip mark and then pass it down to perform this process.

```cpp
void makeroot(int x) {
  access(x);
  push_rev(x);
}
```

So `expose(x, y)` is ready to come out:

```cpp
void expose(int x, int y) {
  makeroot(x);
  access(y);
}
```

### Link & Cut

Now we want to connect an edge between two disconnected points in the original tree. We first let one of the points $x$ become the root of the original tree, and then rotate the other point $y$ to the root. It can be seen that at this time, the point $y$ should become the right son of the point $x$. Then hang this edge on the right son of point $y$ (in SATT, which only needs to maintain the point, this step can be omitted).

```cpp
void Link(int x, int y, int z) {
  // z represents the edge connecting x, y
  access(x);
  makeroot(y);
  setfather(y, x, 1);
  setfather(z, y, 0);
  pushup(x, 0);
  pushup(y, 0);
}
```

`Cut` has similar principles to `Link`

```cpp
void cut(int x, int y) {
  expose(x, y);
  clear(rs(x));  // Delete the base cluster xy
  father[x] = ls(y) = rs(x);
  pushup(y, 0);
}
```

### Complete code

??? note "[Luogu P3690[Template]Dynamic Tree](https://www.luogu.com.cn/problem/P3690)"
    ```cpp
    --8<-- "docs/ds/code/top-tree/top-tree_1.cpp"
    ```

### Time complexity proof of SATT

Suppose in a SATT (the number of points is $n$), the potential energy function of its current state $x$ is

$$
\varphi(x)= \sum_{i=1}^{n} r(i)
$$

Among them $r(i) = \lceil \log_2 \text{siz}(i) \rceil$ . $\text{siz}(i)$ is the size of the subtree rooted at $i$.

Then the amortized complexity of SATT's splay is obviously still $3n\log n + 1$, even if SATT is a ternary tree.

Therefore, for SATT, as long as we prove that the Access function complexity is correct, we can prove the time complexity of SATT.

Let’s analyze the amortized complexity of Accese step by step.

We first need to rotate the point $x$ to the root of the Compress Tree where it is located, then the amortized complexity of this step

$$
a \leq  3\log n +1
$$

Then we need to make point $x$ have no right son, then the amortized complexity of this step

$$
a = 1 + r'(\gamma)- 0 \leq \log n +1
$$

![](./images/top-tree16.jpg)

As shown in the figure, it is the right son process of removing point $x$.

Then comes the process of Local Splay and Splice alternating. After several Splices, point $x$ is rotated to the root of SATT. We analyze one of the groups of Local Splay and Splice:

![](./images/top-tree17.jpg)

![](./images/top-tree18.jpg)

![](./images/top-tree19.jpg)

As shown in the figure, it reflects the process of doing a Splice on the point $x$, excluding the last left-handed point $x$.

For convenience of expression, let $r_x(i)$ be point $i$'s value in state $x$ of $r$.

From the figure, it is easy to know the amortized complexity of the operation from state 1 to state 2 (the Local Splay operation that rotates the parent of point $x$ to the root of its Rake Tree)

$$
a \leq  3(r_2(\gamma)- r_1(\gamma))+1
$$

From the figure, it is easy to know the amortized complexity of the operation from state 2 to state 3 (the Local Splay operation of rotating the parent node of point $x$ to the root of its Compress Tree)

$$
a \leq  3(r_3(B)- r_2(B))+1
$$

Focus on analyzing the operations from state 3 to state 4 (Splice)

$$
a = r_4(\gamma) -r_3(\gamma) +1
$$

Not hard to find $r_4(\gamma) \leq r_3(B)$

Therefore, the amortized complexity of this operation is

$$
\begin{aligned}
a &\leq r_3(B)- r_3(\gamma)+1\\
&\leq 3(r_3(B)- r_3(\gamma))+1\\
\end{aligned}
$$

Based on the above process, the complexity of one Splice is

$$
a\leq 3r_3(B)+3r_3(B)+3r_2(\gamma)-3r_3(\gamma)-3r_2(B)-3r_1(\gamma)+3
$$

Note that once Splice 's point $X$ (that is, point $B$ in state 4) has a $r$ value of $r'(X)$ , and note that $r_3(\gamma),r_1(\gamma) \ge r_1(X)$ , $r_3(B),r_2(\gamma) \leq r'(X)$ and $r_3(B)=r_2(B)$ , so

$$
a\leq  9(r'(X)-r(X))+3
$$

In addition to the above complexity, there may be additional amortized complexity caused by `delete(x)` in Splice. This part is recorded as $a' \leq 3\log n +1$.

Regardless of the $a'$ part, the $r'(X)$ of each Splice is equal to the next $r(X)$, and the $r(X)$ of the first Splice is equal to when we first rotate point $x$ to the root of its Compress Tree, the $r(X)$ then. Then for the complexity of one `access(x)` excluding `delete(x)`, we have:

$$
a \leq 9(r'(x)-r(x))+ 3k + 1
$$

Among them, $k$ is the number of Splice.

It seems that $a$ will bring a $3k+1$, which makes the amortized complexity impossible to analyze, but we have a way to deal with it. Note that the rotation of zig-zig/zig-zag can be amortized in this way.

$$
\begin{aligned}
a &\leq 3(r'(X)-r(X)) + q\\
&\leq 3(q-1)(r'(X)-r(X))
\end{aligned}
$$

If we can find enough zig-zig, zig-zag operations, we can spread this $3k+1$ evenly among these operations, thereby eliminating this $3k+1$.

We found that there are so many zig-zig in Globel Splay, zag-zig is for us to use, because the number of points in Globel Splay must be greater than $k$, and the number of points from point $x$ to the root path of Globel Splay must be no less than $k$, that is to say, there must be at least $\dfrac k2$ zig-zag operations in one `access(x)`, including Globel Splay The amortized complexity of $a \leq 3\log n +1$ , and the amortized complexity of `access(x)` without remembering `delete(x)` is

$$
\begin{aligned}
a&\leq 9(r'(X)-r(X)) + 3k + 1 + 18(r''(X)-r'(X)) -S+1 +3 \log n +1,S \ge 3k\\
a&\leq 18(r''(X)-r(X)) +2 +3\log n+1\\
a&\leq 21(r''(X)-r(X)) +3
\end{aligned}
$$

Now counting $a'$, list the total formula for performing $m$ operations on `access(x)`.

$$
\sum_{i=1}^m a_i' + \sum_{i=1}^m a_i = \sum_{i=1}^m c_i + \varphi(x_n) -\varphi(x_0)
$$

What we require is the actual complexity

$$
\begin{aligned}
\sum_{i=1}^m c_i &= \sum_{i=1}^m a_i +\sum_{i=1}^m a_i' - \varphi(x_n) +\varphi(x_0)\\
&\le \sum_{i=1}^m a_i' + 21m\log n +n\log n +3m
\end{aligned}
$$

Note that the essence of the `delete(x)` operation is to delete a Rake Node, but we will only add up to $m$ Rake Nodes in $m$ operations. According to the definition of Rake Node, we initially have at most $n$ Rake Nodes, which means that we will only do a total of $m+n$ times `delete(x)` operations, which can be seen from $a' \leq 3\log n +1$

$$
\sum_{i=1}^m c_i \leq 3(m+n)\log n + 21m\log n +n\log n +4m +n
$$

So we have proved the complexity of Access, and other functions are either based on Access or have a single time complexity of constant, so we have proved the complexity of SATT.

By the way, if you omit the Global Splay process like LCT, and instead directly rotate the point to be accessed every time Splice, the time complexity of this is also correct (actually measured, the version that omits Global Splay is much faster, and can run as fast as LCT on Luogu P3690).

### example

#### Example 1

???+ note "[CEOI 2019 Dynamic Diameter](https://loj.ac/p/3163)"
    Given a tree with $n$ nodes, each edge has an edge weight, there are $q$ updates, each time the edge weight of an edge is modified, and the diameter of the tree is asked. Forced online.

Maintain dynamic diameter. After building SATT, we only need to maintain the answer of each point in `Pushup(x)`, and finally query the answer of the root node (that is, the diameter of the entire tree).

```cpp
void pushup(int x, int op) {
  if (op == 0) {
    // Is Compress Node
    len[x] = len[ls(x)] + len[rs(x)];
    diam[x] = maxs[ls(x)][1] + maxs[rs(x)][0];
    diam[x] =
        max(diam[x], max(maxs[ls(x)][1], maxs[rs(x)][0]) + maxs[ms(x)][0]);
    diam[x] = max(diam[x], max(max(diam[ls(x)], diam[rs(x)]), diam[ms(x)]));
    maxs[x][0] =
        max(maxs[ls(x)][0], len[ls(x)] + max(maxs[ms(x)][0], maxs[rs(x)][0]));
    maxs[x][1] =
        max(maxs[rs(x)][1], len[rs(x)] + max(maxs[ms(x)][0], maxs[ls(x)][1]));
  } else {
    // Is Rake Node
    diam[x] = maxs[ls(x)][0] + maxs[rs(x)][0];
    diam[x] =
        max(diam[x], maxs[ms(x)][0] + max(maxs[ls(x)][0], maxs[rs(x)][0]));
    diam[x] = max(max(diam[x], diam[ms(x)]), max(diam[ls(x)], diam[rs(x)]));
    maxs[x][0] = max(maxs[ms(x)][0], max(maxs[ls(x)][0], maxs[rs(x)][0]));
  }
  return;
}
```

Where $diam$ is the answer to the current point (the diameter of the cluster represented by this point). $len$ represents the length of the cluster path where the current Compress Node is located, $maxs_{0/1}$ represents the maximum distance from the Compress Node to the unselected cluster path son/unselected father of the points and endpoints in the cluster (if it is a Rake Node, only the maximum distance $maxs_0$ from the selected upper endpoint of the current cluster to the points and endpoints in the cluster is stored). Just query the diam of the SATT root node every time, and the correctness is obvious.

Note some changes to `Pushrev(x)`.

```cpp
void pushrev(int x) {
  if (!x) return;
  r[x] ^= 1;
  swap(ls(x), rs(x));
  swap(maxs[x][0], maxs[x][1]);
}
```

#### Example 2

???+ note "[The center of gravity of the "CSP-S 2019" tree](https://loj.ac/p/3213)"
    Given a tree, find the sum of the centroid numbers of the two subtrees split after deleting each edge of the tree individually.

If we can dynamically maintain the center of gravity of the tree with $O(\log n)$, we can solve this problem.

SATT supports dynamic $O(\log n)$ maintenance of the center of gravity of the tree, which requires **Non-local Search**.

For a property on a tree, if a point/edge has this property in the entire tree and contains this property in all subtrees containing it, we call this property **local (Local)**, otherwise we call it **non-local (Non-local)**. Local information can generally be maintained through `pushup(x)`

For example, the minimum weight is local, because if a point/edge has the smallest weight in the entire tree, then it will also have the smallest weight in all subtrees containing it, and the second smallest weight is obviously non-local.

The $diam$ we maintained above is also partial information.

Back to the topic, the center of gravity is obviously a non-local information and cannot be maintained by simple `pushup(x)`. Let's consider searching on SATT:

Our search starts from the root node of SATT, that is, the root cluster. Note that the center of gravity has a very good property: if the number of points on one side of an edge is greater than or equal to the number of points on the other side, then there must be at least one center of gravity on this side of the edge (there may be two centers of gravity).

Note that $sum$ represents the number of points in a certain cluster, and $maxs$ is the maximum value of $sum$ among the sons of all Rake Nodes in a Rake Tree.

```cpp
void pushup(int x, int op) {
  if (op == 0) {
    // Is Compress Node
    sum[x] = sum[ls(x)] + sum[rs(x)] + sum[ms(x)] + 1;
  } else {
    // Is Rake Node
    maxs[x] = max(maxs[ls(x)], max(maxs[rs(x)], sum[ms(x)]));
    sum[x] = sum[ls(x)] + sum[rs(x)] + sum[ms(x)];
  }
}
```

![](./images/top-tree20.jpg)

As shown in the figure, it is the SATT and the corresponding original tree $T$ when performing Non-local Search.

We make the following comparison:

1.  Compare cluster $compress(Y)$'s $sum$ value with the union of cluster $compress(Z)$, cluster $A$ and point $X$ (we temporarily call it cluster $\alpha$)'s $sum$ value. If $compress(Y)$'s $sum$ value is greater than or equal to the latter, it means that at least one center of gravity is in the subtree of $compress(Y)$, and we recurse to $compress(Y)$ to search. (If equal is taken here, point $X$ is also a center of gravity and needs to be recorded)

2.  Compare cluster $compress(Z)$'s $sum$ value with the union of cluster $compress(Y)$, cluster $A$ and point $X$ (we temporarily call it cluster $\beta$)'s $sum$ value. If $compress(Z)$'s $sum$ value is greater than or equal to the latter, it means that at least one center of gravity is in the subtree of $compress(Z)$, and we recurse to $compress(Z)$ to search. (If equal is taken here, point $X$ is also a center of gravity and needs to be recorded)

3.  Compare, in point $x$'s Rake tree, the smaller cluster with the largest $sum$'s $sum$ value with the union of cluster $compress(Y)$ , cluster $A$ , point $X$ and other smaller clusters (we temporarily call it cluster $Y$ )'s $sum$ value; if that smaller cluster's $sum$ value is greater than or equal to the latter, indicating that there is at least one center of gravity in the subtree of that smaller cluster, and we recursively search for it. If equal is taken here, point $X$ is also a center of gravity and needs to be recorded.

4.  If none of the above comparisons are recursive, then point $X$ must be a center of gravity, record and exit.

The search in the first step is obviously correct. How should we search next?

If we recurse to $Y$, the information stored in $Y$ is incomplete because $compress(Y)$ only stores the information of its own cluster, and what we require is the center of gravity of the entire tree. The solution is to record the information of the previous cluster, and merge the information of the previous cluster with the own information of point $Y$ when comparing and calculating at point $Y$. The specific implementation is as follows:

```cpp
void non_local_search(int x, int lv, int rv, int op) {
  // lv and rv are the information of the previous cluster searched
  if (!x) return;
  psd(x, 0);
  if (op == 0) {
    if (maxs[ms(x)] >=
        sum[ms(x)] - maxs[ms(x)] + sum[rs(x)] + sum[ls(x)] + lv + 1 + rv) {
      if (maxs[ms(x)] ==
          sum[ms(x)] - maxs[ms(x)] + sum[rs(x)] + sum[ls(x)] + lv + 1 + rv) {
        if (ans1)
          ans2 = x;
        else
          ans1 = x;
      }
      non_local_search(
          ms(x),
          sum[ms(x)] - maxs[ms(x)] + sum[rs(x)] + sum[ls(x)] + 1 + lv + rv, 0,
          1);
      return;
    }
    if (ss[rs(x)] + rv >= ss[ms(x)] + ss[ls(x)] + lv + 1) {
      if (ss[rs(x)] + rv == ss[ms(x)] + ss[ls(x)] + lv + 1) {
        if (ans1)
          ans2 = x;
        else
          ans1 = x;
      }
      non_local_search(rs(x), sum[ms(x)] + 1 + sum[ls(x)] + lv, rv, 0);
      return;
    }
    if (sum[ls(x)] + lv >= sum[ms(x)] + sum[rs(x)] + 1 + rv) {
      if (sum[ls(x)] + lv == sum[ms(x)] + sum[rs(x)] + 1 + rv) {
        if (ans1)
          ans2 = x;
        else
          ans1 = x;
      }
      non_local_search(ls(x), lv, rv + sum[ms(x)] + 1 + sum[rs(x)], 0);
      return;
    }
  } else {
    if (maxs[ls(x)] == maxs[x]) {
      non_local_search(ls(x), lv, rv, 1);
      return;
    }
    if (maxs[rs(x)] == maxs[x]) {
      non_local_search(rs(x), lv, rv, 1);
      return;
    }
    non_local_search(ms(x), lv, rv, 0);
    return;
  }
  if (ans1)
    ans2 = x;
  else
    ans1 = x;
}
```

??? note "Sample code"
    ```cpp
    --8<-- "docs/ds/code/top-tree/top-tree_2.cpp"
    ```

### Reference

1.  Robert E. Tarjan and Renato F. Werneck. 2005. Self-adjusting top trees. In Proceedings of the sixteenth annual ACM-SIAM symposium on Discrete algorithms (SODA '05). Society for Industrial and Applied Mathematics, USA, 813–822. DOI 10.5555/1070432.1070547

2.  [negiizhao's blog](https://negiizhao.blog.uoj.ac/blog/4912)
