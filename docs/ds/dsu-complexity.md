author: orzAtalod

This section is reproduced and modified from [Time Complexity - A Brief Discussion of Potential Analysis](https://www.luogu.com.cn/blog/Atalod/shi-jian-fu-za-du-shi-neng-fen-xi-qian-tan), with permission from the original author.

## Definitions

### Ackermann Function

First, define $\alpha(n)$. To give this definition, first define $A_k(j)$.

Define $A_k(j)$ as:

$$
A_k(j)=\left\{
\begin{aligned}
&j+1& &k=0&\\
&A_{k-1}^{(j+1)}(j)& &k\geq1&
\end{aligned}
\right.
$$

This is the Ackermann function.

Here, $f^i(x)$ means applying $f$ to $x$ consecutively $i$ times, i.e. $f^0(x)=x$ and $f^i(x)=f(f^{i-1}(x))$.

Then define $\alpha(n)$ as the minimum integer value such that $A_{\alpha(n)}(1)\geq n$. Note that we previously described it as $A_{\alpha(n)}(\alpha(n))\geq n$; in any case, their growth rates are both very slow, and the value does not exceed 4.

### Basic Definitions

Every node has a rank. Here, rank is not the number of nodes, but depth. A node's initial rank is 0. During union, if two nodes have different ranks, merge the node with smaller rank into the node with larger rank, and do not update the rank of the larger node. Otherwise, merge one node into the other arbitrarily and increase the root's rank by 1. The root node's rank gives the height of the tree. Let the rank of x be $rnk(x)$, and similarly let the parent of x be $fa(x)$. We always have $rnk(x)+1\leq rnk(fa(x))$.

To define the potential function, first define an auxiliary function $level(x)$, where $level(x)=\max(k:rnk(fa(x))\geq A_k(rnk(x)))$. When $rnk(x)\geq1$, define another auxiliary function $iter(x)=\max(i:rnk(fa(x))\geq A_{level(x)}^i(rnk(x))$. These functions are defined for $x$ satisfying $rnk(x)>0$ and where $x$ is not the root of a tree.

The definitions above may be dizzying. Rephrased: for a pair of nodes $x$ and $fa(x)$, if $rnk(x)>0$, we can always find a pair $i,k$ such that $rnk(fa(x))\geq A_k^i(rnk(x))$. Then $level(x)=\max(k)$, and under this premise, $iter(x)=\max(i)$. $level$ describes the maximum iteration level of $A$, while $iter$ describes the maximum number of iterations at that maximum level.

For these two functions, $level(x)$ always increases or stays unchanged as operations proceed; if $level(x)$ does not increase, then $iter(x)$ also only increases or stays unchanged. They always satisfy the following two inequalities:

$$
0\leq level(x)<\alpha(n)
$$

$$
1\leq iter(x)\leq rnk(x)
$$

These are easy to prove by considering the definitions of $level(x)$, $iter(x)$, and $A_k^j$; we leave them to the reader to become familiar with the definitions.

Define the potential function $\Phi(S)=\sum\limits_{x\in S}\Phi(x)$, where $S$ denotes the whole DSU, and $x$ is a node in the DSU. Define $\Phi(x)$ as:

$$
\Phi(x)=
\begin{cases}
\alpha(n)\times \mathit{rnk}(x)& \mathit{rnk}(x)=0\ \text{或}\ x\ \text{为某棵树的根节点}\\
(\alpha(n)-\mathit{level}(x))\times \mathit{rnk}(x)-iter(x)& \text{otherwise}
\end{cases}
$$

Then we prove the amortized time complexity $\Theta(\alpha(n))$ by analyzing the potential changes caused by operations. Note that the $union(x,y)$ operation discussed here guarantees that both $x$ and $y$ are roots of some trees, so no additional $find(x)$ or $find(y)$ is needed.

We can see that the potential is always nonnegative. Also, at the beginning, the DSU's potential is $0$.

## Proof

### `union(x,y)` Operation

Its actual cost is $\Theta(1)$, so we consider the potential change it causes.

Assume $rnk(x)\leq rnk(y)$, i.e. $x$ is attached to $y$. Then the only nodes whose potential may increase are $x$ (from a root to a non-root), $y$ (rank may increase), and the children of $y$ before the operation (their parent's rank may increase). First prove that, before the operation, $y$'s child $c$ has potential that cannot increase, and if it decreases, it decreases by at least $1$.

Let the potential of $c$ before the operation be $\Phi(c)$, and after the operation be $\Phi(c')$. Here $c$ can be any non-root node with $rnk(c)>0$, and the operation can be any operation, including the find operation below. We discuss three cases.

1.  Neither $iter(c)$ nor $level(c)$ increases. Clearly, $\Phi(c)=\Phi(c')$.
2.  $iter(c)$ increases, while $level(c)$ does not. Here $iter(c)$ increases by at least one, so $\Phi(c')\leq \Phi(c)-1$; the potential decreases by at least 1.
3.  $level(c)$ increases, and $iter(c)$ may decrease. However, since $0<iter(c)\leq rnk(c)$, $iter(c)$ can decrease by at most $rnk(c)-1$, while $level(c)$ increases by at least $1$. From the definition $\Phi(c)=(\alpha(n)-level(c))\times rnk(c)-iter(c)$, we get $\Phi(c')\leq\Phi(c)-1$.
4.  Other cases. Since $rnk(c)$ is unchanged and $rnk(fa(c))$ does not decrease, such cases do not exist.

Thus, the only nodes whose potential may increase are $x$ or $y$. When $x$ changes from root to non-root, if $rnk(x)=0$, then $\Phi(x)=\Phi(x')=0$ always. Otherwise, we must have $\alpha(x)\times rnk(x)\geq(\alpha(n)-level(x))\times rnk(x)-iter(x)$. Therefore, $\Phi(x')\leq \Phi(x)$.

So the only node whose potential may increase is $y$. The potential of $y$ increases by at most $\alpha(n)$. Therefore, the amortized time complexity of the $union$ operation is $\Theta(\alpha(n))$.

### `find(a)` Operation

If the search path contains $\Theta(s)$ nodes, its actual time complexity is clearly $\Theta(s)$. If no node's potential increases due to the find operation, and at least $s-\alpha(n)$ nodes have potential decreased by at least $1$, then the time complexity of $find(a)$ can be proven to be $\Theta(\alpha(n))$. To avoid confusion, we use $a$ as the parameter, while every $x$ below refers generically to a node in the DSU.

First prove that no node's potential increases. This is obvious: we proved above that the potential of every non-root node does not increase, and the root's $rnk$ is unchanged, so no node's potential increases.

Next prove that at least $s-\alpha(n)$ nodes have potential decreased by at least $1$. We proved above that if $level(x)$ or $iter(x)$ changes, then the potential decreases by at least $1$. Therefore, it suffices to prove that for at least $s-\alpha(n)$ nodes, $level(x)$ or $iter(x)$ changes.

Recall the potential definition for non-root nodes: $\Phi(x)=(\alpha(n)-level(x))\times rnk(x)-iter(x)$, where $level(x)$ and $iter(x)$ are the maximum numbers satisfying $rnk(fa(x))\geq A_{level(x)}^{iter(x)}(rnk(x))$.

Thus, if $root_x$ denotes the root of the tree containing $x$, we only need to prove $rnk(root_x)\geq A_{level(x)}^{iter(x)+1}(rnk(x))$. By the definition of $A_k^i$, $A_{level(x)}^{iter(x)+1}(rnk(x))=A_{level(x)}(A_{level(x)}^{iter(x)}(rnk(x)))$.

Note that we may use $k(x)$ for $level(x)$ and $i(x)$ for $iter(x)$ to avoid overly long formulas. Here, this is $rnk(root_x)\geq A_{k(x)}(A_{k(x)}^{i(x)}(x))$.

If this looks incomprehensible, you may need to read it several times, or skip some content and return later.

Here we need an external $A_{k(x)}$, which means we may need to find another point $y$. Let $y$ be a point on the search path after $x$ such that $k(y)=k(x)$; here "after on the search path" means "an ancestor of $x$". Clearly, not every $x$ has such a $y$. It is easy to prove that such a $y$ is missing for $x$ among nodes numbering at most $\alpha(n)+2$, because only for each $k$ the last $x$, plus $a$ and $root_a$, lacks such a $y$.

Emphasizing again: $fa(x)$ refers to the parent of $x$ **before** path compression; after path compression, the parent of $x$ is always denoted by $root_x$. For each corresponding $y$ that exists for $x$, we always have $rnk(y)\geq rnk(fa(x))$. Also, $rnk(fa(x))\geq A_{k(x)}^{i(x)}(rnk(x))$. Since $k(x)=k(y)$, write it uniformly as $k$, giving $rnk(fa(x))\geq A_k^{i(x)}(rnk(x))$. We need to create an $A_k$, so we can ignore the value of $iter(y)$ and directly use the weakened statement $rnk(fa(y))\geq A_k(rnk(y))$.

Combining the inequalities gives the key result: $rnk(fa(y))\geq A_k^{i(x)+1}(rnk(x))$. That is, to iterate from $rnk(x)$ to $rnk(fa(y))$, we can iterate $A_k$ at least $i(x)+1$ times without exceeding $rnk(fa(y))$.

Clearly, $rnk(root_y)\geq rnk(fa(y))$, and $rnk(x)$ is unchanged during path compression. Therefore, $rnk(root_x)\geq A_k^{i(x)+1}(rnk(x))$, meaning $iter(x)$ increases by at least 1; if $rnk(x)$ does not increase, then $level(x)$ must have increased.

So $\Phi(x)$ decreases by at least 1. Since such $x$ nodes number at least $s-\alpha(n)-2$, the total $\Phi(S)$ decreases by at least $s-\alpha(n)-2$, and the amortized time complexity is $\Theta(\alpha(n)+2)=\Theta(\alpha(n))$.

## Why DSU Can Be Hacked

This asks: if we do not union by rank, which properties are broken and cause DSU time complexity to no longer be guaranteed as $\Theta(m\alpha(n))$?

If, during union, the node with larger $rnk$ is merged onto a node with smaller $rnk$, we set the node with smaller $rnk$'s $rnk$ to the other node's $rnk$ plus one. This still ensures $rnk(fa(x))\geq rnk(x)+1$, preventing properties from failing everywhere like compile errors.

Clearly, if we do this, the broken part is the statement in the proof of $union(x,y)$ that "the potential of y increases by at most $\alpha(n)$".

There exists a structure that degrades the time complexity of DSU with path compression to $\Omega(m\log_{1+\frac{m}{n}}n)$, defined as follows:

A binomial tree (actually somewhat different from an ordinary binomial tree), where j is a constant and $T_k$ is formed by taking one $T_{k-1}$ and adding one $T_{k-j}$ as a child of the root.

![Binomial tree](./images/dsu-complexity.svg)

Boundary condition: $T_1$ to $T_j$ are all single nodes.

Let $rnk(T_k)=r_k$. We have $r_k=(k-1)/j$ here (proof omitted). In each round of operations, attach it to a single node, then query the bottom $j$ nodes. That is, when attaching it to a single node, the potential of the single node increases by $(k-1)/j+1$. When $j=\lfloor\frac{m}{n}\rfloor$, $i=\lfloor\log_{j+1}\frac{n}{2}\rfloor$, and $k=ij$, the potential increase is:

$$
\alpha(n)\times((ij-1)/j+1)=\alpha(n)\times((\lfloor\log_{\lfloor\frac{m}{n}\rfloor+1}\frac{n}{2}\rfloor\times \lfloor\frac{m}{n}\rfloor-1)/\lfloor\frac{m}{n}\rfloor+1)
$$

After transforming this and removing all floor symbols, we get potential increase $\geq \alpha(n)\times(\log_{1+\frac{m}{n}}n-\frac{n}{m})$. Over m operations this is $\Omega(m\log_{1+\frac{m}{n}}n-n)=\Omega(m\log_{1+\frac{m}{n}}n)$.

## About Heuristic Merging

Since union by rank is harder to write than heuristic merging, many experts choose to implement DSU with heuristic merging. Specifically, maintain $size(x)$ for each root, and merge the smaller $size$ into the larger one each time.

So, can heuristic merging be hacked?

First, explain using the properties involving rank in the proof. If $size$ can replace the role of $rnk$, then heuristic merging can be used. Quickly summarizing, the proof uses the following three rank-related properties:

1.  In each union, at most one node's rank increases, and it increases by at most 1.
2.  We always have $rnk(fa(x))\geq rnk(x)+1$.
3.  A node's rank never decreases.

For the second and third properties, $siz$ clearly satisfies them. However, it does not satisfy the first property: if $x$ is merged into $y$, then $siz(y)$ increases by $siz(x)$.

Therefore, consider using $\log_2 siz(x)$ instead of $rnk(x)$.

For the first property, since a node's $siz$ at most doubles, $\log_2 siz(x)$ increases by at most 1. The second and third properties are relatively obvious, so the proof is omitted.

Thus, if you do not want to implement union by rank, use heuristic merging; the time complexity is still $\Theta(m\alpha(n))$.
