author: pw384, s0cks5, Watersail2005, Xeonacid

The Matrix-Tree Theorem solves the problem of counting the number of spanning trees in a graph.

## Notation Declaration

In this article, for both undirected and directed graphs, multiple edges are allowed, but self-loops are not allowed by default.

??? note "Case with Self-Loops"
    Self-loops do not affect the number of spanning trees, nor the calculation of the Laplacian matrix below. Therefore, the Matrix-Tree Theorem still holds for graphs with self-loops. Self-loops need not be removed during calculation. If self-loops are removed, it will affect counting the number of Eulerian circuits in directed graphs when applying the Matrix-Tree Theorem using the BEST Theorem.

### Undirected Graph Case

Let $G$ be an undirected graph with $n$ vertices. Define the degree matrix $D(G)$ as

$$
D_{ii}(G) = \mathrm{deg}(i),\ D_{ij} = 0,\ i\neq j.
$$

Let $\#e(i,j)$ be the number of edges connecting vertex $i$ and vertex $j$, and define the adjacency matrix $A$ as

$$
A_{ij}(G)=A_{ji}(G)=\#e(i,j),\ i\neq j.
$$

Define the Laplacian matrix (also called Kirchhoff matrix) $L$ as

$$
L(G) = D(G) - A(G).
$$

Let $t(G)$ be the number of all spanning trees of graph $G$.

### Directed Graph Case

Let $G$ be a directed graph with $n$ vertices. Define the out-degree matrix $D^{out}(G)$ as

$$
D^\mathrm{out}_{ii}(G) = \mathrm{deg}^\mathrm{out}(i),\ D^\mathrm{out}_{ij} = 0,\ i\neq j.
$$

Similarly define the in-degree matrix $D^\mathrm{in}(G)$.

Let $\#e(i,j)$ be the number of directed edges from vertex $i$ to vertex $j$, and define the adjacency matrix $A$ as

$$
A_{ij}(G)=\#e(i,j),\ i\neq j.
$$

Define the out-degree Laplacian matrix $L^\mathrm{out}$ as

$$
L^\mathrm{out}(G) = D^\mathrm{out}(G) - A(G).
$$

Define the in-degree Laplacian matrix $L^\mathrm{in}$ as

$$
L^\mathrm{in}(G) = D^\mathrm{in}(G) - A(G).
$$

Let $t^\mathrm{root}(G,k)$ be the number of all rooted arborescences (directed spanning trees pointing toward the root) with root $k$ in graph $G$. A rooted arborescence means that the underlying undirected graph is a tree, and all edges point toward the parent.

Let $t^\mathrm{leaf}(G,k)$ be the number of all leaf-oriented arborescences (directed spanning trees pointing away from the root) with root $k$ in graph $G$. A leaf-oriented arborescence means that the underlying undirected graph is a tree, and all edges point toward the child.

## Theorem Statement

The Matrix-Tree Theorem has multiple forms.

Define $[n]=\{1,2,\cdots,n\}$, and the submatrix $A_{S,T}$ of matrix $A$ is the submatrix obtained by selecting elements $A_{i,j}$ for $i\in S, j\in T$.

???+ note "Theorem 1 (Matrix-Tree Theorem, Undirected Graph, Determinant Form)"
    For any undirected graph $G$ and any $k$,
    
    $$
    t(G) = \det L(G)_{[n]\setminus\{k\},[n]\setminus\{k\}}.
    $$
    
    That is, all $(n-1)$-order principal minors of the Laplacian matrix of an undirected graph are equal to each other, and all equal to the number of spanning trees of the graph.

???+ note "Corollary 1 (Matrix-Tree Theorem, Undirected Graph, Eigenvalue Form)"
    Let $\lambda_1\ge\lambda_2\ge\cdots\ge\lambda_{n-1}\ge\lambda_n=0$ be the $n$ eigenvalues of $L(G)$. Then
    
    $$
    t(G) = \frac{1}{n}\lambda_1\lambda_2\cdots\lambda_{n-1}.
    $$

???+ note "Theorem 2 (Matrix-Tree Theorem, Directed Graph Rooted Arborescence, Determinant Form)"
    For any directed graph $G$ and any $k$,
    
    $$
    t^\mathrm{root}(G,k) = \det L^\mathrm{out}(G)_{[n]\setminus\{k\},[n]\setminus\{k\}}.
    $$
    
    That is, the principal minor obtained by deleting the $k$-th row and $k$-th column of the out-degree Laplacian matrix of a directed graph equals the number of rooted arborescences with root $k$.

Therefore, to count all rooted arborescences of a graph, simply enumerate all possible roots $k$ and sum $t^\mathrm{root}(G,k)$.

???+ note "Theorem 3 (Matrix-Tree Theorem, Directed Graph Leaf-Oriented Arborescence, Determinant Form)"
    For any directed graph $G$ and any $k$,
    
    $$
    t^\mathrm{leaf}(G,k) = \det L^\mathrm{in}(G)_{[n]\setminus\{k\},[n]\setminus\{k\}}.
    $$
    
    That is, the principal minor obtained by deleting the $k$-th row and $k$-th column of the in-degree Laplacian matrix of a directed graph equals the number of leaf-oriented arborescences with root $k$.

Therefore, to count all leaf-oriented arborescences of a graph, simply enumerate all possible roots $k$ and sum $t^\mathrm{leaf}(G,k)$.

??? note "Note"
    Rooted arborescences are also called in-branching arborescences, but since rooted arborescences are computed using out-degree to avoid confusion between $\mathrm{in}$ and $\mathrm{out}$, we use the term "rooted" (or "branching toward root").

## Theorem Proof

Observe that the forms of the above theorems are very similar. Here we provide a unified proof and extend the previous conclusions to weighted graphs.

The general idea of the proof is as follows:

-   First, all cases can be transformed into the case of counting rooted arborescences in directed graphs.
-   Use matrix language to give necessary and sufficient conditions for a selected set of edges to form a rooted arborescence.
-   Connect the edge selection operation with the determinant of the Laplacian matrix using the Cauchy–Binet formula.
-   Finally, transform the determinant form conclusion into the eigenvalue form conclusion.

### Lemma: Cauchy–Binet Formula

???+ note "Lemma 1 (Cauchy–Binet)"
    Given an $n\times m$ matrix $A$ and an $m\times n$ matrix $B$, we have
    
    $$
    \det(AB)=\sum_{S\subset[m];~|S|=n}\det A_{[n],S}\det B_{S,[n]},
    $$
    
    where the summation means $S$ ranges over all subsets of $[m]$ of size $n$. If $n>m$, then $\det(AB)=0$.

??? note "Proof (Combinatorial View)"
    Referring to the model in [「NOI2021」Path Intersections](https://loj.ac/p/3533), first consider the combinatorial meaning of the determinant. For an $n\times n$ matrix $C$, construct a directed acyclic graph $G=(V,E)$. The vertex set is $V=[2]\times[n]\subset\mathbb R^2$, that is, two columns of points in the plane. Denote the left column as $L=\{l_i=(1,i):i\in[n]\}$, and the right column as $R=\{r_i=(2,i):i\in[n]\}$. The directed edge set is $E=\{(l_i,r_j):i,j\in[n]\}$, and edge weights are assigned as $w(l_i,r_j)=C_{i,j}$. In this graph, a subset of edges of size $n$ called $E^\sigma\subset E$ is called a path system if its starting points are all distinct, and its ending points are all distinct. Obviously, path systems $E^\sigma$ correspond one-to-one with permutations $\sigma$ on $[n]$. Note that if we draw a path system on the plane, these edges may intersect pairwise, and the number of intersections (counted with multiplicity) equals the number of inversions in $\sigma$. This is because edge $(l_i,r_{\sigma(i)})$ and edge $(l_j,r_{\sigma(j)})$ intersect if and only if $(i-j)(\sigma(i)-\sigma(j))< 0$, which is exactly an inversion pair. For convenience, we call the parity of the number of inversions corresponding to a permutation, that is, the parity of the number of intersections in the path system, the parity of the path system. So, if we count these path systems by weight and subtract the number of path systems with odd intersections from those with even intersections, we get the Leibniz expansion of the determinant:
    
    $$
    \det(C)=\sum_{\sigma\in S_n}\mathrm{sgn}(\sigma)\prod_{i\in[n]}C_{i,\sigma(i)},
    $$
    
    where $S_n$ is the permutation group on $[n]$, and $\mathrm{sgn}(\sigma)$ is the sign of permutation $\sigma$ (equal to $1$ when the number of inversions is even, and $-1$ when odd).
    
    After understanding the combinatorial meaning of the determinant, we can prove the Cauchy–Binet formula using the following combinatorial model. For an $n\times m$ matrix $A$ and an $m\times n$ matrix $B$, construct a directed acyclic graph $G=(V,E)$. The vertex set is $V=L\cup D\cup R$, where $L=\{l_i=(1,i):i\in[n]\}$, $D=\{d_i=(2,i):i\in[m]\}$, and $R=\{r_i=(3,i):i\in[n]\}$. The directed edge set is $E=E_L\cup E_R$, where $E_L=\{(l_i,d_j):i\in[n],j\in[m]\}$ and $E_R=\{(d_j,r_i):j\in[m],i\in[n]\}$, with edge weights $w(l_i,d_j)=A_{i,j}$ and $w(d_j,r_i)=B_{j,i}$ respectively. Similarly consider path systems from $L$ through $D$ to $R$ (paths do not share vertices), count them by weight, and subtract the number of path systems with odd intersections from those with even intersections. Below we show that the two sides of the Cauchy–Binet formula calculate this quantity in two different ways.
    
    For the left side, based on the graph $G$ described above, construct a new graph $G'$ with vertex set $V'=L\cup R$, edge set $E'=\{(l_i,r_j):i,j\in[n]\}$, and for each edge $(l_i,r_j)$ assign weight $\sum_{k\in[m]}A_{i,k}B_{k,j}$, which is the weighted count of simple paths from $l_i$ to $r_j$ in the original graph $G$. This edge weight is exactly $(AB)_{i,j}$. This simplifies the three-layer graph to a two-layer graph. However, path systems in the two-layer graph $G'$ (counted by weight) do not correspond one-to-one with path systems in the three-layer graph $G$. Since each path in the two-layer graph corresponds to several simple paths in the three-layer graph, when counting path systems in the two-layer graph, we need to multiply the weights, which corresponds to pairing path collections in the three-layer graph. This inevitably causes situations where intermediate vertices are shared. However, such paths with shared intermediate vertices do not contribute to the final answer, because for $i_1 < i_2$ and $j_1 < j_2$ and any intermediate point $d$, there exist two simple path pairs $(l_{i_1}\rightarrow d\rightarrow r_{j_1}, l_{i_2}\rightarrow d\rightarrow r_{j_2})$ and $(l_{i_1}\rightarrow d\rightarrow r_{j_2}, l_{i_2}\rightarrow d\rightarrow r_{j_1})$, but the parity of the number of intersections of these two path pairs in the three-layer graph must be opposite, because if we only look at start and end points, the two path pairs swap the endpoints. So, when counting in the simplified two-layer graph, contributions from paths with shared intermediate vertices cancel out in pairs. For the remaining cases, given the start and end points of two paths, regardless of how intermediate points are chosen (as long as the same point is not chosen), the parity of the number of intersections between the two paths does not change. Therefore, all path systems in $G'$ correspond to path systems in the original graph $G$ having the same parity. Thus, $\det(AB)$ provides a calculation method for the difference in the number of path systems mentioned earlier.
    
    For the right side, it enumerates all possible sets of intermediate points. Given any set of intermediate points $S\subset D=[m]$ with $|S|=n$, consider path systems from $L$ to $S$ and from $S$ to $R$ separately, which can be connected to form a path system from $L$ to $R$. The permutation corresponding to the first two path systems is the composition of the permutations corresponding to those two path systems, which equals the permutation corresponding to the resulting path system. Therefore, the product of the parities of the first two path systems equals the parity of the resulting path system. So, the difference in the count of path systems with all intermediate point sets equal to $S$ is exactly the product of the difference in the count of path systems from $L$ to $S$ and from $S$ to $R$. Summing over all possible $S$, we get the right side, which is exactly the difference in the number of path systems mentioned earlier.

??? note "Proof (Algebraic View)"
    The combinatorial proof above can be translated word-for-word into an algebraic proof. Here we provide another more technical algebraic proof, but it uses several known results. When $m < n$, the determinant is zero because
    
    $$
    \mathrm{rank}(AB)\le \min\{\mathrm{rank}(A),\mathrm{rank}(B)\}\le m< n.
    $$
    
    When $m=n$, the Cauchy–Binet formula becomes: the determinant of the product of square matrices equals the product of the determinants.
    
    When $m>n$, note that
    
    $$
    x^{m-n}\det(xI_n+AB) = \det(xI_m+BA).
    $$
    
    It is known that in $\det(xI_n+C)$, the coefficient of $x^{n-k}$ is the sum of all $k$-order principal minors of $C$. Therefore, comparing coefficients on both sides of the equation above, we have
    
    $$
    \det(AB) = \sum_{S\subset[m];~|S|=n}\det(BA)_{S,S} = \sum_{S\subset[m];~|S|=n}\det(B)_{S,[n]}\det(A)_{[n],S} = \sum_{S\subset[m];~|S|=n}\det(A)_{[n],S}\det(B)_{S,[n]}.
    $$
    
    Here, the second equality uses the conclusion for the case $m=n$.

### Characterizing Graph Structure with Incidence Matrices

For a directed graph $G=(V,E)$ with $n$ vertices and $m$ edges, and each edge $e$ assigned a weight $w(e)$. Define the $m\times n$ out-incidence matrix

$$
M^\mathrm{out}_{ij}=\begin{cases}
\sqrt{w(e_i)},&\exists u(e_i=(v_j,u)),\\
0,&\textrm{otherwise},
\end{cases}
$$

and the $m\times n$ in-incidence matrix

$$
M^\mathrm{in}_{ij}=\begin{cases}
\sqrt{w(e_i)},&\exists u(e_i=(u,v_j)),\\
0,&\textrm{otherwise}.
\end{cases}
$$

Each row records an edge: the out-incidence matrix $M^\mathrm{out}$ records the starting point of the edge, and the in-incidence matrix $M^\mathrm{in}$ records the ending point of the edge.

Simple calculations show

$$
D^\mathrm{out}(G) = (M^\mathrm{out})^T M^\mathrm{out},\ A(G) = (M^\mathrm{out})^T M^\mathrm{in},\ D^\mathrm{in}(G) = (M^\mathrm{in})^T M^\mathrm{in}.
$$

Consequently,

$$
L^\mathrm{out}(G) = (M^\mathrm{out})^T (M^\mathrm{out}-M^\mathrm{in}),\ L^\mathrm{in}(G) = (M^\mathrm{in}-M^\mathrm{out})^T M^\mathrm{in}.
$$

The Cauchy–Binet formula mentioned earlier shows that principal minors of the Laplacian matrix are actually sums of substructures. Each substructure reflects the properties of the corresponding subgraph.

???+ note "Lemma 2"
    For a subgraph $(W,S)$ of $G$, if $|W|=|S|\le n$, then the subgraph $T=(V,S)$ is a rooted forest with root $V\setminus W$ if and only if
    
    $$
    \det(M^\mathrm{out}_{S,W})\det(M^\mathrm{out}_{S,W}-M^\mathrm{in}_{S,W})
    $$
    
    is non-zero. Moreover, when it is non-zero, it equals $\prod_{e\in S}w(e)$, denoted as $w(T)$.

??? note "Proof"
    Assume $w(e)=1$. This is because by multilinearity of determinants, each row of each determinant can extract a factor $\sqrt{w(e)}$, and the product of these factors is $w(T)$.
    
    First analyze when the two factors are zero. The first factor $\det(M^\mathrm{out}_{S,W})$ has at most one non-zero number (i.e., $+1$) in each row. If any row is all zeros, the determinant must be zero. Therefore, the determinant is non-zero if and only if each row has exactly one $+1$, that is, each vertex in $W$ is exactly the starting point of one edge in $S$, and no two edges share the same starting point. For $T$ to become a rooted forest with root $V\setminus W$, a necessary condition is that except for the root, all vertices have exactly one parent, which necessarily makes this factor non-zero; but the converse is not necessarily true because it cannot guarantee the absence of cycles, so the second factor needs to be examined. Note that the endpoints of $S$ may not be in $W$.
    
    Assuming the first factor is non-zero, then $T$ becomes a rooted forest if and only if $T$ has no cycles. At this time, the second factor $\det(M^\mathrm{out}_{S,W}-M^\mathrm{in}_{S,W})$ has a $+1$ in each row, but may have one or zero $-1$. For edges whose endpoints are also in $W$, if the endpoint of $e_i$ is the starting point of $e_j$, then adding the row corresponding to $e_j$ to the row corresponding to $e_i$ can eliminate the $-1$ in row $e_i$. It can be imagined that at this time, the row describes a simple path with $e_i$ and $e_j$ connected end to end. If a new $-1$ appears in this row, it means that the endpoint of $e_j$ is also within $W$, and the position of $-1$ is the endpoint of $e_j$. Then we can continue to find an edge whose starting point is the endpoint of $e_j$ and add it to the row. Such an edge always exists because the previous paragraph states that each vertex in $W$ is exactly the starting point of one edge in $S$. This process continues until no $-1$ appears in the row, which is equivalent to continuously adding new edges to the simple path $e_i\rightarrow e_j\rightarrow \cdots\rightarrow e_k$. At this time, if the row has only one $+1$ left, it means the endpoint of $e_k$ is not in the selected vertices $W$, and the process terminates; if the newly added edge exactly cancels the existing $+1$, that is, the row becomes zero, it means the endpoint of $e_k$ is the starting point of the first edge $e_i$, i.e., a cycle appears. Therefore, the necessary and sufficient condition for no cycles is that the determinant can be transformed into a form where each row has exactly one $+1$. Since the positions of these $+1$s are the starting points of the corresponding edges, the resulting matrix is actually $\det(M^\mathrm{out}_{S,W})$.
    
    In summary, if $T$ is not a rooted forest, either $\det(M^\mathrm{out}_{S,W})=0$ or $\det(M^\mathrm{out}_{S,W}-M^\mathrm{in}_{S,W})=0$; otherwise, both are non-zero, and their product equals $\left(\det(M^\mathrm{out}_{S,W})\right)^2=1$.

### Matrix-Tree Theorem for Weighted Directed Graphs

Now we can prove the main result of this article. All the Matrix-Tree theorems mentioned earlier are special cases of this theorem.

???+ note "Theorem 4 (Matrix-Tree Theorem, Weighted Directed Graph Rooted Arborescence, Determinant Form)"
    For any $k$,
    
    $$
    \sum_{T\in\mathcal T^\mathrm{root}(G,k)}w(T)=\det L^\mathrm{out}(G)_{[n]\setminus\{k\},[n]\setminus\{k\}}.
    $$
    
    Here, $\mathcal T^\mathrm{root}(G,k)$ is the set of rooted arborescences of $G$ with root $k$.

??? note "Proof"
    Let $W=[n]\setminus\{k\}$ be the set of vertices excluding vertex $k$. Then, by the Cauchy–Binet formula, the right side can be written as
    
    $$
    \det L^\mathrm{out}(G)_{W,W} = \sum_{S\subset[m];~|S|=n-1}\det(M^\mathrm{out}_{S,W})\det(M^\mathrm{out}_{S,W}-M^\mathrm{in}_{S,W}).
    $$
    
    By iterating through all $S$, by Lemma 2, the right side accumulates a $w(T)$ if and only if $T=(V,S)$ forms a rooted forest with root $V\setminus W=\{k\}$, that is, $T$ is a rooted arborescence with root $k$.
    
    When $w(e)=1$, each tree has weight $1$, so the left side is the count of all trees, which is $t^\mathrm{root}(G,k)$, giving Theorem 2. By analogy with the above, the conclusion can be directly extended to leaf-oriented arborescences, giving Theorem 3. Finally, to obtain the spanning tree count for undirected graphs, the following corollary can be applied.

???+ note "Corollary 4 (Matrix-Tree Theorem, Weighted Undirected Graph, Determinant Form)"
    For any undirected graph $G$ and any $k$,
    
    $$
    \sum_{T\in\mathcal T(G)}w(T) = \det L(G)_{[n]\setminus\{k\},[n]\setminus\{k\}}.
    $$
    
    Here, $\mathcal T(G)$ is the set of spanning trees of $G$. This also shows that all $(n-1)$-order principal minors of $L(G)$ are equal.

??? note "Proof"
    For an undirected graph $G=(V,E)$, we can construct a directed graph $G'=(V,E')$, where $E'=\{(v_i,v_j):(v_i,v_j)\in E\}\cup\{(v_j,v_i):(v_i,v_j)\in E\}$, that is, each undirected edge in $G$ is split into two directed edges in opposite directions in $G'$. For any $k$, the rooted arborescences with root $k$ in $G'$ correspond one-to-one to the spanning trees in $G$. From the former to the latter, we only need to remove the direction of edges and the choice of root; from the latter to the former, we only need to start from the selected root $k$ and select edges one by one with root direction as the edge direction. Therefore, at this time we have
    
    $$
    \sum_{T\in\mathcal T(G)}w(T) = \sum_{T\in\mathcal T^\mathrm{root}(G',k)}w(T) = \det L^\mathrm{out}(G')_{[n]\setminus\{k\},[n]\setminus\{k\}} = \det L(G)_{[n]\setminus\{k\},[n]\setminus\{k\}}.
    $$
    
    Here we use the conclusion $L^\mathrm{out}(G')=L(G)$, which can be verified directly.

### Eigenvalue Form

First consider the conclusion for directed graphs.

???+ note "Theorem 5"
    For a directed graph $G$, define the multivariate polynomial
    
    $$
    \chi(x_1,\cdots,x_n)=\det(\mathrm{diag}(x_1,\cdots,x_n)-L^\mathrm{out}(G)).
    $$
    
    Here, $\mathrm{diag}(x_1,\cdots,x_n)$ is the diagonal matrix with $x_1,\cdots,x_n$ as diagonal elements. Then
    
    $$
    (-1)^{n-r}[x_{k_1},\cdots,x_{k_r}]\chi(x_1,\cdots,x_n)
    $$
    
    equals the (weighted) count of rooted forests of $G$ with roots $\{k_1,\cdots,k_r\}$.

??? note "Proof"
    Following the proof of Theorem 4, note that if we let $W=[n]\setminus\{k_1,\cdots,k_r\}$, then the coefficient in the theorem is $\det L^\mathrm{out}(G)_{W,W}$ (this can be directly observed from the Leibniz expansion of the determinant). By the Cauchy–Binet formula, it equals
    
    $$
    \det L^\mathrm{out}(G)_{W,W} = \sum_{S\subset[m];~|S|=n-r}\det(M^\mathrm{out}_{S,W})\det(M^\mathrm{out}_{S,W}-M^\mathrm{in}_{S,W}).
    $$
    
    By iterating through all $S$, by Lemma 2, the right side accumulates a $w(T)$ if and only if $T=(V,S)$ forms a rooted forest with root $V\setminus W=\{k_1,\cdots,k_r\}$.
    
    Substituting all $x$'s with the same value, we obtain the characteristic polynomial of the Laplacian matrix
    
    $$
    P(x) = \det(xI-L^\mathrm{out}(G)) = \chi(x,\cdots,x).
    $$

???+ note "Lemma 3"
    The Laplacian matrix $L^\mathrm{out}(G)$ has at least one eigenvalue equal to zero.

??? note "Proof"
    We only need to prove its determinant is zero. Following the proofs of Theorem 4 and 5, let $W=\varnothing$. Then the size of this determinant should equal the number of rooted forests with zero trees. This does not exist, so the determinant equals zero.

???+ note "Corollary 5"
    For a directed graph $G$, the sum of the weights of all rooted forests consisting of $k$ trees equals the coefficient
    
    $$
    (-1)^{n-k}[x^k]P(x).
    $$

??? note "Proof"
    Sum over all possible choices of $k$ roots.

Define a $k$-spanning forest as a spanning subgraph of a graph that has $k$ connected components and no cycles.

???+ note "Corollary 6"
    Let $\mathcal T_k(G)$ be the set of $k$-spanning forests of an undirected graph $G$. Then
    
    $$
    \sum_{T\in\mathcal T_k(G)}w(T)Q(T) = (-1)^{n-k}[x^k]P(x).
    $$
    
    Here, $Q(T)$ is the product of the number of vertices in each connected component of forest $T$. In particular, when $k=1$, $Q(T)=n$, so
    
    $$
    n\sum_{T\in\mathcal T(G)}w(T) = \lambda_1\lambda_2\cdots\lambda_{n-1}.
    $$

??? note "Proof"
    Following the proof of Corollary 4, we can directly use the conclusion of Corollary 5. Each rooted forest consisting of $k$ trees in a directed graph corresponds to a $k$-spanning forest in an undirected graph. However, since each $k$-spanning forest $T$ has $Q(T)$ ways to choose roots, it appears in $Q(T)$ rooted forests of the directed graph.

## Applications

### Cayley's Formula

???+ note "Corollary 7 (Cayley)"
    There are $n^{n-2}$ labeled unrooted trees of size $n$.

??? note "Proof"
    Equivalently, we only need to find that the number of spanning trees of a complete graph with $n$ vertices is $n^{n-2}$. To do this, write the Laplacian matrix
    
    $$
    L(G) = \left(\begin{matrix} n-1 & -1 & \cdots & -1 \\ -1 & n-1 & \cdots & -1 \\ \vdots & \vdots & \ddots & \vdots \\ -1 & -1 & \cdots & n-1  \end{matrix}\right)_{n\times n}.
    $$
    
    Compute any principal minor:
    
    $$
    \det(nI_{n-1}-{\bf 1}{\bf 1}^T) = n^{n-1}\det(I_{n-1}-n^{-1}{\bf 1}{\bf 1}^T) = n^{n-1}(1-n^{-1}{\bf 1}^T{\bf 1}) = n^{n-1}(1-(n-1)/n) = n^{n-2}.
    $$
    
    Applying Theorem 1 yields the conclusion.

### BEST Theorem

Prerequisites: [Eulerian Graph](./euler.md)

This theorem connects the number of Eulerian circuits in a directed Eulerian graph with the number of rooted arborescences of that graph, thereby solving the counting problem of Eulerian circuits in directed graphs. Note that the counting problem of Eulerian circuits in undirected graphs is NP-complete.

When implementing this algorithm, we should first determine whether the given graph is an Eulerian graph, remove all zero-degree vertices, then construct the graph and calculate the number of rooted arborescences, and obtain the count of Eulerian circuits using the BEST Theorem. Note that if the number of Eulerian circuits is required to start from a given point, the answer should be multiplied by that point's out-degree, which is equivalent to enumerating the first edge of the circuit.

Before proving the BEST Theorem, we need to know the following conclusion.

???+ note "Property (Criterion for a Directed Graph to Have an Eulerian Circuit)"
    A directed graph has an Eulerian circuit if and only if all non-zero-degree vertices are strongly connected, and the out-degree equals the in-degree for all vertices.

For Eulerian graphs, since out-degree equals in-degree, we can omit the superscript and denote it as $\mathrm{deg}(v)$. The BEST Theorem can be stated as follows.

???+ note "Theorem 6 (BEST Theorem)"
    Let $G$ be a directed Eulerian graph, and $k$ be any vertex. Then the total number of distinct Eulerian circuits $\mathrm{ec}(G)$ of $G$ is
    
    $$
    \mathrm{ec}(G) = t^\mathrm{root}(G,k)\prod_{v\in V}(\deg (v) - 1)!.
    $$
    
    This also shows that for any two nodes $k, k'$ in Eulerian graph $G$, we have $t^\mathrm{root}(G,k)=t^\mathrm{root}(G,k')$.

??? note "Proof"
    The general idea of the proof is to establish a correspondence between Eulerian circuits starting at $k$ as the starting point, rooted arborescences rooted at $k$, and permutations of outgoing edges at each vertex. After specifying the vertices of the Eulerian circuit, the count to be proved should equal
    
    $$
    \mathrm{deg}(k)\mathrm{ec}(G) = t^\mathrm{root}(G,k)\deg(k)!\prod_{v\neq k}(\deg (v) - 1)!.
    $$
    
    The combinatorial meaning of this count corresponds to the following construction. For an Eulerian circuit starting at $k$, according to the order of appearance of each edge in the circuit, we can construct
    
    -   A rooted arborescence rooted at $k$, consisting of the last outgoing edge at each non-root vertex, i.e., $t^\mathrm{root}(G,k)$,
    -   The permutation order of all outgoing edges at the root $k$, i.e., $\mathrm{deg}(k)!$, and
    -   The permutation order of all other outgoing edges at non-root vertices $v \neq k$ except the last one, i.e., $(\mathrm{deg}(v)-1)!$.
    
    Below we show that this construction gives a bijective mapping.
    
    On one hand, given an Eulerian circuit, we need to prove that the last outgoing edge at each non-root vertex forms a rooted arborescence. According to the construction, each non-root vertex indeed has only one outgoing edge in the tree, so we only need to prove these outgoing edges do not form a cycle. Note that if we sort all vertices according to their last appearance order in the Eulerian circuit, then the last outgoing edge of a non-root vertex must point to a vertex strictly later in the order. If there is a cycle, there must be a vertex latest in the order in that cycle, and since it is in the cycle, it points to a vertex not late in the order, which contradicts the above. Therefore, the last outgoing edges of non-root vertices must form a rooted arborescence.
    
    On the other hand, given any rooted arborescence and the permutation order of the remaining outgoing edges, we can recover an Eulerian circuit such that the given rooted arborescence and the permutation order of the remaining outgoing edges can be obtained through the above construction. To do this, starting from the root $k$, whenever we reach a vertex, we select the earliest unused outgoing edge according to the given permutation order of that vertex as the current outgoing edge in the Eulerian circuit; if all outgoing edges in the permutation at that vertex have been used, we select the outgoing edge of that vertex in the rooted arborescence as the current outgoing edge in the Eulerian circuit. Since the graph is an Eulerian graph, the in-degree equals the out-degree at each vertex, so this process will not terminate at a non-root vertex, i.e., the resulting path is indeed a circuit. To prove that the resulting path is a valid Eulerian circuit, we only need to prove that this process can traverse all edges.
    
    If not, there must be some outgoing edge of some vertex $v$ that is not traversed. Consider vertex $v$. Vertex $v$ cannot be the root because we eventually terminate at the root; if there are remaining outgoing edges at the root, this contradicts the termination of the process. So $v$ must not be the root. According to the process described above, if a non-root vertex $v$ has any remaining outgoing edges, then the outgoing edge $e$ in the tree must also remain. Let $e=(v,u)$. Since some incoming edge of $u$ is not traversed, by the equality of out-degree and in-degree at $u$, there must be some outgoing edge of $u$ that is not traversed. Then we can similarly examine vertex $u$. This reasoning moves the examined vertex from $v$ to $u$, i.e., moving one step toward the root along the rooted arborescence. We can prove by induction that at this time some outgoing edge of the root $k$ is not traversed. It has been shown earlier that this is impossible, so we get a contradiction. This shows that the path obtained in the previous paragraph is indeed a valid Eulerian circuit.
    
    These mappings can be verified to be injective, so they must be bijections. The original proposition is proved.

## Implementation

Write the Laplacian matrix according to the graph, delete one row and one column, and compute the determinant of the resulting matrix. Gaussian elimination can be used to compute the determinant.

For example, the number of spanning trees of a square graph

$$
\begin{pmatrix}
2 & 0 & 0 & 0 \\
0 & 2 & 0 & 0 \\
0 & 0 & 2 & 0 \\
0 & 0 & 0 & 2 \end{pmatrix}-\begin{pmatrix}
0 & 1 & 0 & 1 \\
1 & 0 & 1 & 0 \\
0 & 1 & 0 & 1 \\
1 & 0 & 1 & 0 \end{pmatrix}=\begin{pmatrix}
2 & -1 & 0 & -1 \\
-1 & 2 & -1 & 0 \\
0 & -1 & 2 & -1 \\
-1 & 0 & -1 & 2 \end{pmatrix}
$$

$$
\begin{vmatrix}
2 & -1 & 0 \\
-1 & 2 & -1 \\
0 & -1 & 2 \end{vmatrix} = 4
$$

We can use Gaussian elimination to solve this, with time complexity $O(n^3)$.

??? note "Implementation"
    ```cpp
    #include <algorithm>
    #include <cassert>
    #include <cmath>
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    using namespace std;
    constexpr int MOD = 100000007;
    constexpr double eps = 1e-7;
    
    struct matrix {
      static constexpr int MAXN = 20;
      int n, m;
      double mat[MAXN][MAXN];
    
      matrix() { memset(mat, 0, sizeof(mat)); }
    
      void print() {
        cout << "MATRIX " << n << " " << m << endl;
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < m; j++) {
            cout << mat[i][j] << "\t";
          }
          cout << endl;
        }
      }
    
      void random(int n) {
        this->n = n;
        this->m = n;
        for (int i = 0; i < n; i++)
          for (int j = 0; j < n; j++) mat[i][j] = rand() % 100;
      }
    
      void initSquare() {
        this->n = 4;
        this->m = 4;
        memset(mat, 0, sizeof(mat));
        mat[0][1] = mat[0][3] = 1;
        mat[1][0] = mat[1][2] = 1;
        mat[2][1] = mat[2][3] = 1;
        mat[3][0] = mat[3][2] = 1;
        mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = -2;
        this->n--;  // delete one row
        this->m--;  // delete one column
      }
    
      double gauss() {
        double ans = 1;
        for (int i = 0; i < n; i++) {
          int sid = -1;
          for (int j = i; j < n; j++)
            if (abs(mat[j][i]) > eps) {
              sid = j;
              break;
            }
          if (sid == -1) continue;
          if (sid != i) {
            for (int j = 0; j < n; j++) {
              swap(mat[sid][j], mat[i][j]);
              ans = -ans;
            }
          }
          for (int j = i + 1; j < n; j++) {
            double ratio = mat[j][i] / mat[i][i];
            for (int k = 0; k < n; k++) {
              mat[j][k] -= mat[i][k] * ratio;
            }
          }
        }
        for (int i = 0; i < n; i++) ans *= mat[i][i];
        return abs(ans);
      }
    };
    
    int main() {
      srand(1);
      matrix T;
      // T.random(2);
      T.initSquare();
      T.print();
      double ans = T.gauss();
      T.print();
      cout << ans << endl;
    }
    ```

## Example Problems

???+ note "Example 1: [「HEOI2015」Little Z's Room](https://loj.ac/problem/2122)"
    **Solution** This is a direct application of the Matrix-Tree Theorem. Treat each empty room as a node, construct the graph according to the input, obtain the Laplacian matrix, delete any row and column $i$ from $L$, and compute the determinant of this submatrix. The method to compute the determinant is to perform Gaussian elimination to an upper triangular matrix and then compute the product of the diagonal. Additionally, this problem requires performing Gaussian elimination in the integer subring $\mathbb{Z}_k$ modulo $k$, which can be done using the Euclidean algorithm.

???+ note "Example 2: [「FJOI2007」Cyclovirus](https://www.luogu.com.cn/problem/P2144)"
    **Solution** There are many solutions to this problem, but using the Matrix-Tree Theorem is the most direct. When the input is $n$, it is easy to write its $(n+1)$-order Laplacian matrix as:
    
    $$
    L_n = \begin{bmatrix}
    n&  -1&  -1&  -1&  \cdots&  -1&  -1\\
    -1&  3&  -1&  0&  \cdots&  0&  -1\\
    -1&  -1&  3&  -1&  \cdots&  0&  0\\
    -1&  0&  -1&  3&  \cdots&  0&  0\\
    \vdots&  \vdots&  \vdots&  \vdots&  \ddots&  \vdots&  \vdots\\
    -1&  0&  0&  0&  \cdots&  3&  -1\\
    -1&  -1&  0&  0&  \cdots&  -1&  3\\
    \end{bmatrix}_{n+1}
    $$
    
    Compute the determinant of its $n$-order minor; the remaining task is just high-precision computation.

??? note "Example 2+"
    Strengthen the data from Example 2, requiring $n\leq 100000$, but the answer is taken modulo 1000007. (Solving this problem requires some linear algebra knowledge)
    
    **Solution** After deriving the recurrence formula, use matrix exponentiation to compute the answer.
    
    Derivation of the recurrence formula:
    
    Note that the matrix obtained by deleting the first row and first column of $L_n$ has a clear pattern, so we are actually computing the determinant of the matrix
    
    $$
    M_n = \begin{bmatrix}
    3&  -1&  0&  \cdots&  0&  -1\\
    -1&  3&  -1&  \cdots&  0&  0\\
    0&  -1&  3&  \cdots&  0&  0\\
    \vdots&  \vdots&  \vdots&  \ddots&  \vdots&  \vdots\\
    0&  0&  0&  \cdots&  3&  -1\\
    -1&  0&  0&  \cdots&  -1&  3\\
    \end{bmatrix}_{n}
    $$
    
    Expanding the determinant of $M_n$ along the first column, we get
    
    $$
    \det M_n = 3\det \begin{bmatrix}
    3&  -1&  \cdots&  0&  0\\
    -1&  3&  \cdots&  0&  0\\
    \vdots&  \vdots&  \ddots&  \vdots&  \vdots\\
    0&  0&  \cdots&  3&  -1\\
    0&  0&  \cdots&  -1&  3\\
    \end{bmatrix}_{n-1} + \det\begin{bmatrix}
    -1&  0&  \cdots&  0&  -1\\
    -1&  3&  \cdots&  0&  0\\
    \vdots&  \vdots&  \ddots&  \vdots&  \vdots\\
    0&  0&  \cdots&  3&  -1\\
    0&  0&  \cdots&  -1&  3\\
    \end{bmatrix}_{n-1} + (-1)^n \det\begin{bmatrix}
    -1&  0&  \cdots&  0&  -1\\
    3&  -1&  \cdots&  0&  0\\
    -1&  3&  \cdots&  0&  0\\
    \vdots&  \vdots&  \ddots&  \vdots&  \vdots\\
    0&  0&  \cdots&  3&  -1\\
    \end{bmatrix}_{n-1}
    $$
    
    Denote the determinants of these three matrices as $d_{n-1}, a_{n-1}, b_{n-1}$.  
    Note that $d_n$ is a tridiagonal determinant; using similar expansion methods, we can get $d_n=3d_{n-1}-d_{n-2}$. Similarly, using expansion we can get $a_{n-1}=-d_{n-2}-1$, and $(-1)^n b_{n-1}=-d_{n-2}-1$.  
    Substituting these recurrence formulas into the above formula, we get:
    
    $$
    \det M_n = 3d_{n-1}-2d_{n-2}-2
    $$
    
    $$
    d_n = 3d_{n-1}-d_{n-2}
    $$
    
    Therefore, we guess that $\det M_n$ is also a non-homogeneous second-order linear recurrence. Using the method of undetermined coefficients, we can obtain the final recurrence formula
    
    $$
    \det M_n = 3\det M_{n-1} - \det M_{n-2} + 2
    $$
    
    After rewriting as $(\det M_n+2) = 3(\det M_{n-1}+2) - (\det M_{n-2} + 2)$, we can use matrix exponentiation to compute the answer.

???+ note "Example 3: [「BZOJ3659」WHICH DREAMED IT](https://hydro.ac/p/bzoj-P3659)"
    **Solution** This problem is a direct application of the BEST Theorem. However, note that since the problem states "two ways to complete the task are considered different if and only if the order of using keys is different", for each Eulerian circuit, we can start from room 1 along any outgoing edge. Therefore, the answer needs to be multiplied by the out-degree of room 1.

???+ note "Example 4: [「Joint Provincial Selection 2020 A」Homework Problem](https://loj.ac/p/3304)"
    **Solution** First, we need to use Möbius inversion to transform into calculating the sum of edge weights of all spanning trees. Since this is not directly related to this article, it is omitted.
    
    Write each term of the determinant as $w_ix+1$. The final answer is the coefficient of the linear term, because the answer is actually the sum of spanning tree counts with a fixed edge times the sum of weights of that edge. Edges that are multiplied by the linear term coefficient are the fixed edges. At this point, terms higher than linear can be ignored, with complexity $O(n^3)$.
    
    [「Beijing Provincial Selection Training 2019」Spanning Tree Counting](https://www.luogu.com.cn/problem/P5296) is a more general case: computing the sum of the $k$-th power of spanning tree weights. We can construct the terms of the determinant similarly. For details, see the Luogu solution.

???+ note "Example 5: [AGC051D C4](https://atcoder.jp/contests/agc051/tasks/agc051_d)"
    **Solution** Counting Eulerian circuits in undirected graphs is an NPC problem, but this problem's graph is relatively simple. Once we determine how many edges from $S$ to $T$ among the $S-T$ edges are directed from $S$ to $T$, we can determine the direction scheme of the other three edges, and then directly apply the BEST Theorem to get an $O(a+b+c+d)$ solution.