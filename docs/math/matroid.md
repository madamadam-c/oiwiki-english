## Introduction

A **matroid** is an abstract algebraic structure proposed by Hassler Whitney in 1935, aimed at unifying and generalizing concepts of independence such as linear independence in linear algebra and acyclicity in graph theory.

Matroids provide a powerful theoretical tool for solving optimization problems related to independence, widely used in combinatorics, graph theory, algorithm design, and other fields. They play an important role in providing mathematical theoretical support for optimization methods such as greedy algorithms.

## Definition

### Matroid

A **matroid** can be denoted as $M = (E, \mathcal{I})$, where:

- $E$ is a finite set, called the **ground set**.
- $\mathcal{I}$ is a family of subsets of $E$, called the **family of independent sets**. The sets in $\mathcal{I}$ are called **independent sets** and satisfy three properties:

    - **Non-emptiness**: The empty set is independent, i.e., $\emptyset \in \mathcal{I}$.

    - **Heredity**: Any subset of an independent set is also independent. If $I \in \mathcal{I}$, then for any $I' \subseteq I$, we have $I' \in \mathcal{I}$.

    - **Exchange**: If $I, J \in \mathcal{I}$ and $|I| < |J|$, then there exists $j \in J \setminus I$ such that $I \cup \{j\} \in \mathcal{I}$.

If a structure of the form $(E, \mathcal{I})$ satisfies these three properties, it is called a matroid.

### Basis

A **basis** is a maximal independent set in a matroid, i.e., an independent set to which no more elements can be added while preserving independence. The set of all bases is called the **basis family**, denoted by $\mathcal{B}$.

**Properties**:

1. **Equal cardinality**: All bases have the same size, called the **rank** of the matroid.

2. **Exchange**: Any independent set can be extended to a basis by adding elements from a basis.

### Circuit

A **circuit** is the smallest dependent set in a matroid, i.e., all its proper subsets are independent, but it itself is not independent. There is no inclusion relationship between any two circuits.

### Rank

The **rank function** $r: 2^E \rightarrow \mathbb{Z}_{\geq 0}$ maps subsets of the ground set $E$ to nonnegative integers. For any $S \subseteq E$, $r(S)$ is defined as the size of the largest independent set in $S$, i.e.,

$$
r(S) = \max \{ |I| \mid I \subseteq S \wedge I \in \mathcal{I} \}.
$$

**Properties**:

1. **Non-negativity**: For any $S \subseteq E$, we have $0 \leq r(S) \leq |S|$.

2. **Monotonicity**: If $A \subseteq B \subseteq E$, then $r(A) \leq r(B)$.

3. **Submodularity**: For any $A, B \subseteq E$, we have $r(A \cup B) + r(A \cap B) \leq r(A) + r(B)$.

## Typical Examples

### 1. Uniform Matroid

**Definition**: Given a ground set $E$ and a nonnegative integer $k$, the independent set family of the uniform matroid $U_{k,E}$ consists of all subsets of size at most $k$, expressed as:

$$
\mathcal{I} = \{ I \subseteq E \mid |I| \leq k \}.
$$

- **Bases**: All subsets of size $k$.

- **Circuits**: All subsets of size $k + 1$.

- **Rank**: $r(E) = \min(k, |E|)$, i.e., an independent set can contain at most $k$ elements.

### 2. Graphical Matroid

**Definition**: Given an undirected graph $G = (V, E)$, the graphical matroid $M(G)$ has the edge set $E$ as its ground set, and its independent set family consists of all edge sets that contain no cycles, i.e., all forests.

- **Bases**: Spanning trees in the graph (in the case of a connected graph). A spanning tree is a maximal independent set; no more edges can be added without forming a cycle.

- **Circuits**: Simple cycles in the graph; removing any edge from a cycle leaves an independent set.

- **Rank**: $r(E) = |V| - c$, where $c$ is the number of connected components of the graph. For a connected undirected graph, its rank equals the number of vertices minus one, i.e., $|V| - 1$.

### 3. Linear Matroid

**Definition**: A linear matroid is based on a vector space. Given a vector space $V$, the ground set $E$ is a finite set of vectors in $V$, and its independent set family consists of all linearly independent subsets of $E$.

- **Bases**: Maximal linearly independent sets of vectors, whose size equals the dimension of the vector space.

- **Circuits**: The smallest linearly dependent set of vectors; any proper subset is independent, while the set itself is linearly dependent.

- **Rank**: The rank of a linear matroid $r(E) = \dim(V)$, i.e., the dimension of the vector space. The size of an independent set cannot exceed the dimension of the vector space.

### 4. Partition Matroid

**Definition**: The ground set $E$ is partitioned into disjoint subsets $E_1, E_2, \dots, E_m$, and each subset $E_i$ is assigned a nonnegative integer $k_i$. The independent set family of a partition matroid consists of subsets that satisfy the condition that the number of elements selected from each part does not exceed $k_i$, expressed as:

$$
\mathcal{I} = \left\{ I \subseteq E \mid \forall i,\, |I \cap E_i| \leq k_i \right\}.
$$

- **Bases**: An independent set satisfying $|I \cap E_i| = k_i$ is a basis of the partition matroid. Each basis selects exactly $k_i$ elements from each subset.

- **Circuits**: The circuits of a partition matroid are the smallest dependent sets, i.e., subsets that contain at least one element exceeding $k_i$.

- **Rank**: The rank of a partition matroid is $r(E) = \sum_{i=1}^m k_i$, i.e., the maximum size of an independent set equals the sum of the maximum number of elements allowed in each subset.

### 5. Colored Matroid

**Definition**: A colored matroid is a special form of a partition matroid where each element is assigned a color. Given a ground set $E$ and a color set $C$, each element $e \in E$ is associated with some color $c \in C$. A colored matroid's independent sets must not only satisfy the independence conditions of a ordinary matroid but also comply with color-specific constraints, such as selecting at most a certain number of elements of the same color in an independent set.

- **Bases**: The bases of a colored matroid are maximal independent sets that satisfy both the color constraints and the independence conditions.

- **Circuits**: Circuits are the smallest dependent sets containing at least one element that violates independence or color constraints.

- **Rank**: The rank of a colored matroid is the maximum size of an independent set under the color constraints. It depends both on the structure of the matroid and on the specific color constraints.

## Constructions and Operations

### Duality

Given a matroid $M = (E, \mathcal{I})$, its **dual matroid** $M^* = (E, \mathcal{I}^*)$ is defined as:

$$
\mathcal{I}^* = \{ I^* \subseteq E \mid \exists B \in \mathcal{I}, |B| = r(E), B \subseteq E \setminus I^* \}.
$$

**Properties**:

- **Bases**: The bases of the dual matroid $M^*$ are the complements of the bases of $M$ in the ground set $E$. In other words, if $B$ is a basis of $M$, then $E \setminus B$ is a basis of $M^*$.

- **Rank function**: The rank function of the dual matroid is $r^*(S) = |S| - r(E) + r(E \setminus S)$, where $S$ is a subset of $E$. This means the rank of the dual matroid can be calculated from the size of the ground set, the rank of the original matroid, and the rank after removing $S$ from the ground set.

- **Reflexivity**: The dual of the dual is the original matroid, i.e., $(M^*)^* = M$.

**Example**:

For an undirected graph $G = (V, E)$, the dual of the graphical matroid $M(G)$ is a matroid composed of the graph's cut sets. The bases of the graphical matroid $M(G)$ are the spanning trees in the graph, while the bases of its dual $M(G)^*$ are the complements of these spanning trees. The circuits of $M(G)^*$ are the minimal cut sets, i.e., the minimal edge sets that disconnect the graph.

For example, consider a simple triangle graph $G$ with edge set $E = \{e_1, e_2, e_3\}$. The bases of the graphical matroid $M(G)$ are sets of two edges (such as $\{e_1, e_2\}$), while the bases of the dual matroid $M(G)^*$ are single edge sets (such as $\{e_3\}$). The circuits of $M(G)^*$ are sets of two edges (i.e., minimal cut sets, such as $\{e_2, e_3\}$), because removing either edge disconnects the graph into two connected components.

### Deletion and Contraction

**Deletion**:

For $A \subseteq E$, deleting $A$ from matroid $M$ yields a new matroid $M \setminus A$, whose independent set family $\mathcal{I}'$ is defined as:

$$
\mathcal{I}' = \{ I \subseteq E \setminus A \mid I \in \mathcal{I} \}.
$$

As can be seen, deletion removes some elements from the matroid and retains the independent sets formed by the remaining elements, keeping the original independent sets unchanged except for the removed elements.

**Contraction**:

For $A \subseteq E$, contracting $A$ from matroid $M$ yields matroid $M / A$, whose independent set family $\mathcal{I}''$ is defined as:

$$
\mathcal{I}'' = \left\{ I \subseteq E \setminus A \,\bigg|\, \exists B \subseteq A,\, B \in \mathcal{I},\, r(B) = r(A),\, I \cup B \in \mathcal{I} \right\}
$$

Contraction can be understood as shrinking the elements in set $A$ and considering the independent sets formed by the remaining elements together with the bases of $A$. The result of contraction depends on the bases of set $A$; the contracted independent sets are actually those obtained by reducing higher-rank subsets of the original matroid.

**Example - Graphical Matroid**:

- **Deletion**: In a graphical matroid, deletion means removing some edges from the graph. After deleting an edge from a graph $G$, we consider the independent sets formed by the remaining edges, i.e., those edge sets that contain no cycles. For example, if we delete one edge from a triangle graph, the remaining two edges still form a forest.

- **Contraction**: Contraction contracts an edge into a vertex. For a graphical matroid, contracting an edge is equivalent to merging the two endpoints of that edge into one vertex and deleting the edge. After merging vertices, the other edges in the graph can still form independent sets. For example, in a triangle graph, contracting any edge merges two vertices into one, and the remaining two edges form a new matroid.

## Matroids and Greedy

**Problem description**:

One application of matroids is to solve optimization problems in greedy algorithms. Specifically, given a matroid $M = (S, \mathcal{I})$, where $S$ is the ground set and $\mathcal{I}$ is the independent set family. For each element $x \in S$, assign a positive integer weight $w(x)$. The goal is to find the independent set with maximum weight, formalized as:

$$
\max_{A \in \mathcal{I}} w(A) = \max_{A \in \mathcal{I}} \sum_{x \in A} w(x)
$$

Obviously, a maximum-weight independent set must be a maximal independent set. If an independent set $A$ is not maximal, then there exists an element $x$ that can be added to $A$, and since $w(x) > 0$, adding this element would increase the weight, indicating that $A$ is not a maximum-weight independent set.

### Steps

The steps for the greedy algorithm to find the maximum-weight independent set are as follows:

1. **Sort elements**: Sort the ground set $S$ by weight in descending order, giving the sequence $e_1, e_2, \dots, e_n$.
2. **Initialize**: Let independent set $A = \emptyset$.
3. **Build independent set**: Consider the sorted elements $e_i$ one by one. If $A \cup \{ e_i \} \in \mathcal{I}$, update $A = A \cup \{ e_i \}$.
4. **Output result**: The final set $A$ is the maximum-weight independent set.

**Complexity analysis**:

Let $n = |S|$ be the size of the ground set, and $f(n)$ be the complexity of checking whether a set is independent. The time complexity of the greedy algorithm is:

$$
O(n \log n + n f(n))
$$

where $O(n \log n)$ is the complexity of sorting, and $O(n f(n))$ is the complexity of checking independence one by one.

???+ note "Note"
    - In graphical matroids, [disjoint set union](../ds/dsu.md) can be used to efficiently detect cycle formation, making $f(n)$ close to constant time.
    - In linear matroids, independence detection usually involves matrix operations, whose complexity depends on the specific implementation.

**Correctness proof**:

Let $M = (S, \mathcal{I})$ be a matroid, and $A \in \mathcal{I}$ be an independent set that is a subset of some maximum-weight independent set $T$. Define the set $P = \{ x \in S \setminus A \mid A \cup \{x\} \in \mathcal{I} \}$, i.e., all elements that can be added to $A$ while keeping $A$ independent.

Let $y$ be the element with maximum weight in $P$. Then $A' = A \cup \{ y \}$ is also a subset of some maximum-weight independent set, proven as follows:

Assume $A' = A \cup \{ y \}$ is not a subset of any maximum-weight independent set. Then there exists a maximum-weight independent set $T$ with $|A'| < |T|$.

Since $|A'| < |T|$, according to the **exchange property** of matroids, there exists $x \in T \setminus A'$ such that $A' \cup \{ x \} \in \mathcal{I}$.

Using the **exchange property** repeatedly, we can continuously add $x$ to $A'$ to eventually construct a new independent set $A''$ such that $|A''| = |T|$.

Let $K = A'' \cap T$. Then we have $x = T \setminus K$, $y = A'' \setminus K$. Since $y$ is the element with maximum weight in $P$, we have $w(x) \leq w(y)$.

Therefore, $w(A'') = w(K) + w(y) \geq w(K) + w(x) = w(T)$. At this point:

- If $w(A'') > w(T)$, then $T$ is not a maximum-weight independent set, contradicting the assumption.
- If $w(A'') = w(T)$, then $A''$ is a maximum-weight independent set, and $A'$ is its subset, contradicting the assumption that $A'$ is not a subset of any maximum-weight independent set.

In summary, the assumption is false, i.e., $A' = A \cup \{ y \}$ must be a subset of some maximum-weight independent set. Therefore, by repeatedly using the greedy strategy, we can eventually find the maximum-weight independent set.

### Examples

**Minimum spanning tree**:

Given a connected undirected graph $G = (V, E)$, each edge $e \in E$ has a weight $w(e)$. The goal is to find a spanning tree that contains all vertices with minimum total weight.

**Constructing the matroid**:

To formulate the minimum spanning tree problem as a matroid problem, we can construct the graphical matroid $M(G)$:

- **Ground set**: $S = E$, i.e., all edges in the graph.
- **Independent set family**: $\mathcal{I}$ is all edge sets that contain no cycles (i.e., all forests).

**Greedy algorithm**:

Within the framework of graphical matroids, [Kruskal's algorithm](../graph/mst.md#kruskal-算法) is a typical greedy algorithm based on matroid theory that can be used to construct a minimum spanning tree. Although [Prim's algorithm](../graph/mst.md#prim-算法) is also an effective greedy algorithm that can also find a minimum spanning tree, it does not strictly depend on the matroid greedy approach. Therefore, in discussions of matroid theory, Kruskal's algorithm is the main example of a greedy algorithm.

- **Kruskal's algorithm**:
    1. **Sort edges**: Sort all edges by weight in ascending order.
    2. **Select progressively**: Select edges with minimum weight in order. If adding an edge does not form a cycle, add it to the spanning tree.
    3. **Termination condition**: Repeat the above process until the spanning tree contains $|V| - 1$ edges.

- **Prim's algorithm**:
    - **Principle**: Prim's algorithm starts from a vertex and progressively expands the spanning tree, selecting the minimum-weight edge connecting the tree to outside at each step.
    - Although Prim's algorithm is also greedy, its selection strategy differs from other greedy algorithms based on the matroid exchange property. Therefore, in the strict sense of matroid theory, Prim's algorithm is not considered a typical matroid greedy algorithm.

## Matroid Intersection

For two matroids $M_1 = (S, \mathcal{I}_1)$ and $M_2 = (S, \mathcal{I}_2)$ defined on the same ground set $S$, if $\mathcal{I} = \mathcal{I}_1 \cap \mathcal{I}_2$ satisfies the three properties of a matroid independent set family, then $M = (S, \mathcal{I})$ is called the **intersection** of $M_1$ and $M_2$.

**Note**: The intersection of any two matroids is not necessarily a matroid. Only when the intersection of their independent set families satisfies the three properties in the definition of a matroid independent set family does the intersection form a matroid.

### Problem description

1. **Maximum independent set**: Find the largest independent set (i.e., the one with maximum cardinality) in $\mathcal{I}_1 \cap \mathcal{I}_2$.
2. **Weighted maximum independent set**: Given a weight function $w: S \to \mathbb{R}$, find the independent set with maximum total weight in $\mathcal{I}_1 \cap \mathcal{I}_2$.

### Algorithm

**Unweighted version**:

1. **Initialize**: Choose an initial independent set $I \in \mathcal{I}_1 \cap \mathcal{I}_2$, typically $I = \emptyset$.
2. **Iterate**:
    - **Build exchange graph**: Build the exchange graph $D_{M_1, M_2}(I)$ based on the current independent set $I$.
    - **Path selection**: In the exchange graph, find an augmenting path $P$ from source $s$ to sink $t$.
    - **Augment**: Traverse each node along path $P$ from $s$ to $t$:
        - If the node belongs to the left part (i.e., elements in $I$), remove that element from $I$.
        - If the node belongs to the right part (i.e., elements in $S \setminus I$), add that element to $I$.
    - **Repeat**: After updating independent set $I$, repeat the above steps until no new augmenting path can be found.
3. **Result**: The final independent set $I$ is a maximum independent set in the matroid intersection $M = M_1 \cap M_2$.

**Weighted version**:

To find the independent set with maximum total weight, the algorithm needs to optimize the selection of augmenting paths.

1. **Weight setting**: For each element $e \in S$, define its weight in the exchange graph $w'(e)$:
    - **Left part vertices** (elements in $I$): $w'(e) = -w(e)$.
    - **Right part vertices** (elements in $S \setminus I$): $w'(e) = w(e)$.
2. **Path selection**: In the exchange graph $D_{M_1, M_2}(I)$, find an **augmenting path** $P$ from source $s$ to sink $t$ such that after augmentation along the path, the total weight of independent set $I$ increases the most.
    - **Augmentation condition**: The sum of weights of elements added along path $P$ is greater than the sum of weights of elements removed, i.e., $\sum_{y \in \text{added elements}} w(y) > \sum_{x \in \text{removed elements}} w(x)$.
3. **Augmentation operation**: Traverse each node along path $P$ from $s$ to $t$:
    - If the node belongs to the left part (i.e., elements in $I$), remove that element from $I$.
    - If the node belongs to the right part (i.e., elements in $S \setminus I$), add that element to $I$.
4. **Iterate**: Repeat steps 1 to 3, continuously building exchange graphs and finding augmenting paths to progressively optimize the total weight of independent set $I$.
5. **Termination condition**: When no path satisfying the augmentation condition can be found in the exchange graph, the algorithm terminates.
6. **Result**: The final independent set $I$ is a **maximum-weight independent set** in the matroid intersection $M = M_1 \cap M_2$.

**Complexity**:

- **Number of augmentations**: Let the maximum ranks of the two matroids be $r_1$ and $r_2$. Then the maximum number of augmentations is $\min(r_1, r_2)$.

- **Complexity of each augmentation**:
    - The complexity of building the exchange graph is $O(n^2)$, where $n = |S|$.
    - The complexity of finding an augmenting path depends on the path search strategy, typically $O(n^2)$, e.g., using breadth-first search.

- **Total time complexity**: Overall time complexity is $O(r \cdot n^2)$, where $r = \min(r_1, r_2)$.

## Example Problems

**Minimum spanning tree**:

Given an undirected graph $G = (V, E)$, each edge $e \in E$ has a weight $w(e)$. Find a spanning tree that contains all vertices with minimum total weight.

- Detailed introduction: [Minimum spanning tree](../graph/mst.md).
- Problem template: [Luogu P3366 [Template] Minimum Spanning Tree](https://www.luogu.com.cn/problem/P3366).

??? note "Solution approach"
    Use Kruskal's algorithm: sort all edges by weight in ascending order, then progressively select edges. If adding an edge does not form a cycle, add it to the spanning tree. The final spanning tree is the minimum spanning tree.

**Colorful Graph**:

Given an undirected graph $G = (V, E)$ with multiple colors, each edge has a color attribute. Find the largest edge set such that:

1. The selected edges do not form any cycle.
2. The number of edges of each color does not exceed $k$ (where $k$ is a given positive integer).

??? note "Solution approach"
    1. **Matroid modeling**:
        - **Graph matroid ($M_1$)**: Defined as all edge sets that do not form cycles, i.e., independent set family $\mathcal{I}_1$ contains all edge sets that do not contain cycles.
        - **Color matroid ($M_2$)**: Defined as edge sets with at most $k$ edges of each color, i.e., independent set family $\mathcal{I}_2$ contains all edge sets satisfying that the number of edges of each color $\leq k$.
    2. **Solve matroid intersection**: By solving $M = M_1 \cap M_2$, find the largest edge set that neither forms cycles nor exceeds $k$ edges of any color.

**Constrained resource allocation problem**:

In a resource allocation problem, there is a set of resources $R = \{r_1, r_2, \dots, r_n\}$ and a set of projects $P = \{p_1, p_2, \dots, p_m\}$. Each project $p_i$ requires a certain amount of resources, and the total allocation of each resource cannot exceed its supply.

**Goal**: Find a resource allocation scheme that satisfies all project requirements and does not exceed resource supplies.

??? note "Solution approach"
    1. **Matroid modeling**:
        - **Demand matroid ($M_1$)**: Defined as allocation schemes that satisfy project resource requirements, i.e., independent set family $\mathcal{I}_1$ contains all resource allocation sets that satisfy project demands.
        - **Supply matroid ($M_2$)**: Defined as allocation schemes that do not exceed each resource's supply, i.e., independent set family $\mathcal{I}_2$ contains all resource allocation sets that satisfy resource supply limits.
    2. **Solve matroid intersection**: By solving $M = M_1 \cap M_2$, find a resource allocation scheme that satisfies all project requirements and does not exceed resource supplies.

## References and Notes

1. [Wikipedia - Matroid](https://en.wikipedia.org/wiki/Matroid)
2. [Baidu Baike - Matroid](https://baike.baidu.com/item/%E6%8B%9F%E9%98%B5)
3. [Luogu - Matroid and Optimization Problems](https://www.luogu.com.cn/article/87d02q9f)
4. [Luogu - From Matroid Basics to Shannon Switching Game](https://www.luogu.com.cn/article/fuj3x886)