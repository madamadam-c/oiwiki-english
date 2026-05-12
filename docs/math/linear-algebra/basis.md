author: cesonic, Enter-tainer, Great-designer, Ir1d, ksyx, lychees, MegaOwIer, RUIN-RISE, wjy-yy, rsdbkhusky, ouuan, Menci, Tiphereth-A

Recall the concept of basis vectors in solid geometry from high school mathematics. We can find a set of basis vectors $\boldsymbol{i}$, $\boldsymbol{j}$, $\boldsymbol{k}$ in three-dimensional Euclidean space, after which any vector in space can be expressed by these basis vectors. In other words, we can **describe an infinite three-dimensional space using finite basis vectors**, which demonstrates the importance of basis vectors.

Three-dimensional Euclidean space is a special [vector space](./vector-space.md). The basis vectors of three-dimensional Euclidean space are generalized to linear bases in vector spaces.

In OI, applications of linear bases generally involve only two types of vector spaces: the $n$-dimensional real vector space $\mathbf{R}^n$ and the $n$-dimensional [Boolean field](https://en.wikipedia.org/wiki/Boolean_domain) vector space $\mathbf{Z}_2^n$. We will introduce these in detail in the [Applications](#applications) section. If you are not familiar with linear algebra, it is recommended to start reading from the applications section.

The following will introduce linear bases from the perspective of general vector spaces and present common properties of linear bases.

Prerequisites: [Vector space](./vector-space.md).

A linear basis is a basis of a vector space and an important tool for studying vector spaces.

## Definition

A maximal linearly independent set of a vector space $V$ is called a set of **Hamel bases** or **linear bases**, or simply **bases**.

The basis of the vector space $\{\theta\}$ is defined as the empty set.

It can be proven that any vector space has a linear basis[^existence_basis]. We define the **dimension** of a vector space $V$ as the number of elements (or cardinality) in its linear basis, denoted as $\dim V$.

## Properties

1.  For a finite-dimensional vector space $V$, let its dimension be $n$, then:

    1.  Any $n+1$ vectors in $V$ are linearly dependent.

    2.  Any $n$ linearly independent vectors in $V$ form a basis of $V$.

    3.  If any vector in $V$ can be linearly expressed by the vector set $a_1,a_2,\dots,a_n$, then it is a basis of $V$.

        ???+ note "Proof"
            Take any basis $b_1,b_2,\dots,b_n$ in $V$. From the given conditions, the vector set $b_1,b_2,\dots,b_n$ can be linearly expressed by $a_1,a_2,\dots,a_n$, hence
            
            $$
            n=\operatorname{rank}\{b_1,b_2,\dots,b_n\}\leq\operatorname{rank}\{a_1,a_2,\dots,a_n\}\leq n
            $$
            
            Therefore $\operatorname{rank}\{a_1,a_2,\dots,a_n\}=n$

    4.  Any linearly independent vector set $a_1,a_2,\dots,a_m$ in $V$ can be extended to a basis of $V$ by inserting some vectors.

2.  (Subspace dimension formula) Let $V_1,V_2$ be finite-dimensional vector spaces over $\Bbb{P}$, and $V_1+V_2$ and $V_1\cap V_2$ are also finite-dimensional, then $\dim V_1+\dim V_2=\dim(V_1+V_2)+\dim(V_1\cap V_2)$

    ???+ note "Proof"
        Let $\dim V_1=n_1$,$\dim V_2=n_2$,$\dim(V_1\cap V_2)=m$.
        
        Take a basis $a_1,a_2,\dots,a_m$ of $V_1\cap V_2$ and extend it to bases of $V_1$ and $V_2$ respectively: $a_1,a_2,\dots,a_m,b_1,b_2,\dots,b_{n_1-m}$ and $a_1,a_2,\dots,a_m,c_1,c_2,\dots,c_{n_2-m}$.
        
        Next, we only need to prove that the vector set $a_1,a_2,\dots,a_m,b_1,b_2,\dots,b_{n_1-m},c_1,c_2,\dots,c_{n_2-m}$ is linearly independent.
        
        Let $\sum_{i=1}^m r_ia_i+\sum_{i=1}^{n_1-m} s_ib_i+\sum_{i=1}^{n_2-m} t_ic_i=\theta$.
        
        Then $\sum_{i=1}^{n_2-m} t_ic_i=-\sum_{i=1}^m r_ia_i-\sum_{i=1}^{n_1-m} s_ib_i$.
        
        Note that the left side is in $V_2$ and the right side is in $V_1$, so both sides are in $V_1\cap V_2$. Therefore $\sum_{i=1}^{n_2-m} t_ic_i=\sum_{i=1}^m k_ia_i$
        
        Hence $t_1=t_2=\dots=t_{n_2-m}=k_1=k_2=\dots=k_m=0$, and then $r_1=r_2=\dots=r_m=s_1=s_2=\dots=s_{n_1-m}=t_1=t_2=\dots=t_{n_2-m}=0$

3.  Let $V_1,V_2$ be finite-dimensional vector spaces over $\Bbb{P}$, and $V_1+V_2$ and $V_1\cap V_2$ are also finite-dimensional. Then the following are equivalent:

    1.  $V_1+V_2=V_1\oplus V_2$.

    2.  $\dim V_1+\dim V_2=\dim(V_1+V_2)$.

    3.  If $a_1,a_2,\dots,a_n$ is a basis of $V_1$, $b_1,b_2,\dots,b_m$ is a basis of $V_2$, then $a_1,a_2,\dots,a_n,b_1,b_2,\dots,b_m$ is a basis of $V_1+V_2$.

    ???+ note "Note"
        Properties 1 and 3 can be extended to infinite-dimensional vector spaces

## Examples

Consider bases of $\Bbb{R}^2$.

1.  As shown in the figure

    ![](./images/basis-1.svg)

    $u,v$ is a basis.

2.  As shown in the figure

    ![](./images/basis-2.svg)

    $u,v$ is a basis.

3.  As shown in the figure

    ![](./images/basis-3.svg)

    $u,v$ is not a basis because $u=-v$.

4.  As shown in the figure

    ![](./images/basis-4.svg)

    $u,v,w$ is not a basis because $u+4v+6w=\theta$.

## Orthogonal Bases and Orthonormal Bases

If a basis $B$ of a vector space $V$ satisfies $\forall b,b'\in B,~(b,b')\ne 0\iff b=b'$ (i.e., pairwise orthogonal), then this basis is called an **orthogonal basis**.

If an orthogonal basis $B$ of a vector space $V$ also satisfies $\forall b\in B,~|b|=\sqrt{(b,b)}=1$, then this basis is called an **orthonormal basis**.

Any basis of a finite-dimensional vector space $V$ can be transformed into an orthogonal basis through [Gram-Schmidt orthogonalization](https://en.wikipedia.org/wiki/Gram%E2%80%93Schmidt_process).

## Applications

Based on the previous content, we can use linear bases to:

1.  Find the rank of a given vector set.

2.  For a given vector set, find a maximal linearly independent set (or a basis of the vector space it spans).

3.  Insert some vectors into a given vector set, and find a maximal linearly independent set in the resulting vector set (or a basis of the vector space it spans).

4.  For a maximal linearly independent set (or basis) found, determine whether a certain vector can be linearly expressed by it.

5.  For a maximal linearly independent set (or basis) found, find special elements (such as maximum, minimum, etc.) in the vector space it spans.

In OI, we generally refer to the linear basis in the $n$-dimensional real vector space $\mathbf{R}^n$ as the **real linear basis**, and the linear basis in the $n$-dimensional Boolean field vector space $\mathbf{Z}_2^n$ as the **XOR linear basis**.

???+ tip "Tip"
    In $\mathbf{Z}_2$, addition is XOR and multiplication is AND. It can be proven that $\mathbf{Z}_2$ is a field.
    
    It can be proven that the algebraic system $(\mathbf{Z}_2^n,+,\cdot,\mathbf{Z}_2)$ is a vector space, where:
    
    $$
    (a_1,\dots,a_n)+(b_1,\dots,b_n):=(a_1+b_1,\dots,a_n+b_n),
    $$
    
    $$
    k\cdot(a_1,\dots,a_n):=(ka_1,\dots,ka_n).
    $$
    
    That is, addition is XOR and scalar multiplication is AND.

Taking the XOR linear basis as an example, we can construct an XOR linear basis $B=\{b_1,\dots,b_n\}$ from a given set of Boolean sequences $X=\{x_1,\dots,x_m\}$. This basis has the following properties:

1.  The XOR sum of any non-empty subset of $B$ is not $0$.

2.  For any element $x$ in $X$, there exist some elements in $B$ whose XOR sum is $x$.

3.  For any set $B'$ satisfying the above two properties, the number of elements in $B'$ is not less than the number of elements in $B$.

We can use the XOR linear basis to:

1.  Determine whether a number can be expressed as the XOR sum of a subset of a given number set.

2.  Find the number of ways to express a number as the XOR sum of a subset of a given number set.

3.  Find the maximum/minimum/$k$-th largest/$k$-th smallest XOR sum of a subset of a given number set.

4.  Find the rank of a number in the XOR sums of a subset of a given number set.

### Construction Methods

Since there is no essential difference between XOR linear bases and real linear bases, we will use XOR linear bases as an example. The code for real linear bases only requires minor modifications.

#### Greedy Method

For each number $p$ in the original set, convert to binary and scan from high to low. For bit $x$ that is $1$, if $a_x$ does not exist, then set $a_x \leftarrow p$ and end the scan. If it exists, set $p\leftarrow p~\text{xor}~a_x$.

To query the maximum XOR of any elements in the original set, scan the linear basis from high to low. If XORing with the current $a_x$ makes the answer larger, XOR the answer with $a_x$.

Why does this work? Because scanning from high to low, if we are at bit $i$, it means we can ensure bit $i$ of the answer is $1$, and there will be no opportunity to change bit $i$ later.

To query the minimum XOR of any elements in the original set, simply take the smallest element in the linear basis set.

To query whether a number can be XORed out, similar to insertion. If the final inserted number $p$ becomes $0$ through XOR, then it can be XORed out.

??? example "Code (Luogu P3812 [Template] Linear Basis)"
    ```cpp
    --8<-- "docs/math/code/basis/basis_1.cpp"
    ```

#### Gaussian Elimination Method

The Gaussian elimination method constructs a linear basis from the perspective of systems of linear equations. Its correctness is obvious.

??? example "Code (Luogu P3812 [Template] Linear Basis)"
    ```cpp
    --8<-- "docs/math/code/basis/basis_2.cpp"
    ```

### Properties

The linear basis constructed by the greedy method has the following properties:

-   The linear basis has no subset whose XOR sum is $0$.

-   The highest bits of the numbers in the linear basis are all different.

The linear basis constructed by the Gaussian elimination method satisfies the following properties:

-   The matrix after Gaussian elimination is a row-reduced echelon matrix.

    > This property includes the two properties satisfied by the linear basis constructed by the greedy method.

    If you don't understand the correctness of this property, you can refer to [Gaussian elimination](../numerical/gauss.md).

Example input:

```text
5
633 211 169 841 1008
```

Binary representation:

```text
1001111001
0011010011
0010101001
1101001001
1111110000
```

Linear basis from greedy method:

```text
1001111001
0100110000
0011010011
0001111010
0000000000
0000010000
0000000000
0000000000
0000000000
0000000000
```

Linear basis from Gaussian elimination:

```text
1000000011
0100100000
0010101001
0001101010
0000010000
0000000000
0000000000
0000000000
0000000000
0000000000
```

This is a very good property that helps us solve many problems more conveniently. For example: given some numbers, select some to XOR together to find the maximum XOR. If using the greedy method to construct a linear basis, we need to do another greedy pass: if the current bit of `ans` is `0`, then XORing will definitely improve it; if the current bit is `1`, then it will definitely not improve. However, after constructing the linear basis using Gaussian elimination, we can simply XOR all elements in the linear basis and output.

For other classic problems (such as querying whether a number can be XORed, querying the $k$-th largest number that can be XORed, etc.), the linear basis obtained by Gaussian elimination can also solve them more conveniently.

### Time Complexity

Let the vector length be $n$ and total count be $m$. The time complexity is $O(nm)$. The constant for Gaussian elimination is slightly larger.

For real linear bases, the time complexity is $O(n^2m)$.

### Merging Linear Bases

Merging linear bases can be done by brute force: insert one linear basis into another. The time complexity of a single merge is $O(n^2)$ for XOR linear bases or $O(n^3)$ for real linear bases.

### Intersection of Linear Bases

Strictly speaking, the intersection of linear bases is finding a linear basis of the intersection of the two vector spaces spanned by them. This section introduces two algorithms. Both algorithms have time complexity $O(n^2)$ for XOR linear bases or $O(n^3)$ for real linear bases.

#### Naive Algorithm

Let the linear bases to intersect be $\alpha$ and $\beta$. The algorithm for intersecting linear bases is just a modification of the brute-force merge algorithm (using XOR linear bases as an example):

-   Try to insert each vector $\beta_j$ from linear basis $\beta$ into $\alpha$ using the [greedy method](#greedy-method), and initialize the intersection linear basis $\gamma$ as the empty set.

-   During insertion, record the contribution of elements from linear basis $\beta$ in the vector being inserted. Specifically, maintain a new vector $b$, initialized as $\beta_j$. Moreover, if the vector being inserted is XORed with the vector at the $x$-th position of the linear basis, then contribution $b$ should also be XORed with the recorded contribution $b_x$ at position $x$.

-   If insertion succeeds and vector $\beta_j'$ is inserted at the $x$-th position of the linear basis, change the recorded $b_x$ at position $x$ to the contribution $b$ from linear basis $\beta$ obtained during the process of getting $\beta_j'$.

-   If insertion fails, insert the recorded contribution $b$ of linear basis $\beta$ into $\gamma$.

The linear basis $\gamma$ obtained this way is the desired intersection. Of course, this algorithm also finds the union of linear bases.

??? note "Explanation of the algorithm"
    Let the merged linear basis be $\{\alpha_1,\cdots,\alpha_m,\beta'_{j_1},\cdots,\beta'_{j_\ell}\}$, where $\beta'_{j_k}$ is the vector obtained from inserting $\beta_{j_k}$. Then $\{\alpha_1,\cdots,\alpha_m,\beta_{j_1},\cdots,\beta_{j_\ell}\}$ is also a merged linear basis. Let $\beta^+$ be the set $\{\beta_{j_1},\cdots,\beta_{j_\ell}\}$, then the merged basis can be written as $\alpha\cup\beta^+$. Moreover, every vector $c$ in the sum space can be uniquely represented as
    
    $$
    c = a\oplus b
    $$
    
    where $a\in\operatorname{span}\alpha$ and $b\in\operatorname{span}\beta^+$. The $b$ in this decomposition is what the algorithm **attempts** to record as "the contribution of elements in linear basis $\beta$". Strictly speaking, it is only the contribution of vectors that were successfully inserted from $\beta$.
    
    For successful insertions, the finally recorded $b$ is the $b$ term in this decomposition. Let $\beta_j\in\beta^+$. Initially, $\beta_j=0\oplus\beta_j$ is already the correct decomposition of $\beta_j$ on basis $\alpha\cup\beta^+$. When updating $\beta'_j=a\oplus b$ to $\beta'_j\oplus c_x$, because $\beta_j'\oplus c_x=(a\oplus a_x)\oplus(b\oplus b_x)$, we only need to update $b$ to $b\oplus b_x$ to ensure the decomposition remains correct. Therefore, by induction, when finally inserting $\beta'_j$ into the merged linear basis, the recorded contribution $b$ is the $b$ term in the above decomposition.
    
    For failed insertions, the variable to be finally inserted becomes $0$, and the contribution $b$ at this time should be inserted into $\gamma$. At this point, repeating the above argument still ensures that during the insertion process we always have $\beta_j'=a\oplus b$, and $a\in\operatorname{span}\alpha$, but $b$ is no longer in $\operatorname{span}\beta^+$. This is because initially $\beta_j=0\oplus\beta_j$ has $\beta_j\notin\beta^+$. In addition, the terms XORed during contribution updates all belong to $\operatorname{span}\beta^+$. So in fact, $b\oplus\beta_j\in\operatorname{span}\beta^+$.
    
    So why does inserting these $b$'s from failed insertions into $\gamma$ give a linear basis of the intersection space? First, insertion of $\beta_j$ fails, so finally we get $0=a\oplus b$, where $a\in\operatorname{span}\alpha$ and $b\in\operatorname{span}(\beta^+\cup\{\beta_j\})\subseteq\operatorname{span}\beta$. Therefore, $b=a$ must be in the intersection space $\operatorname{span}\alpha\cap\operatorname{span}\beta$. Conversely, let $c$ be any element in the intersection space. Since $c\in\operatorname{span}\beta$, $c$ can be expressed as a linear combination (XOR sum) of elements in $\beta$:
    
    $$
    c = \bigoplus_{\beta_j\in\beta}\lambda_j\beta_j,
    $$
    
    where $\lambda_j\in\{0,1\}$. For each $\beta_j\notin\beta^+$, denote the contribution inserted into $\gamma$ as $b_j$. Then
    
    $$
    c\oplus\bigoplus_{\beta_j\notin\beta^+}\lambda_jb_j = \bigoplus_{\beta_j\in\beta^+}\lambda_j\beta_j+\bigoplus_{\beta_j\notin\beta^+}\lambda_j(\beta_j\oplus b_j),
    $$
    
    Note that both $b_j$ and $c$ are in the intersection space, so the left side must also be in the intersection space. Hence the left side can be written as a linear combination of elements in $\alpha$. Meanwhile, on the right side, all terms either have $\beta_j\in\beta^+$ or have $\beta_j\notin\beta^+$ and $\beta_j\oplus b_j\in\beta^+$. So the right side is actually a linear combination of elements in $\beta^+$. But since $\alpha\cup\beta^+$ is linearly independent, all coefficients are $0$. That is, $c=\bigoplus_{\beta_j\notin\beta^+}\lambda_jb_j\in\operatorname{span}\{b_1,\cdots,b_j\}$. This shows that these contributions $b$ from failed insertions together span the intersection space.
    
    According to this explanation, the purpose of maintaining contribution $b$ in the process is actually to maintain the decomposition $a\oplus b$. Moreover, when finally inserting contributions into $\gamma$, we always have $a=b$. So regardless of maintaining contributions of elements in $\alpha$ or $\beta$ (i.e., maintaining $a$ or $b$), the result is correct. If we want to maintain the contribution of elements in linear basis $\alpha$, we only need to modify the initial values of the corresponding contributions: each vector $\alpha_i$ in $\alpha$ initially has contribution $\alpha_i$, and each inserted $\beta_j$ initially has contribution $0$.

Sample code:

??? example "Code (Library Checker [Intersection of $\mathbf F_2$ vector spaces])"
    ```cpp
    --8<-- "docs/math/code/basis/basis_intersect_1.cpp"
    ```

#### Zassenhaus Algorithm

Another equivalent approach is the Zassenhaus algorithm, which can also calculate both the union and intersection of two linear bases simultaneously. The complexity is exactly the same as above.

The specific steps are:

-   Initialize a linear basis $\gamma$ with vector length $2n$ as empty, where vectors are written in the form $(a,b)$, and both $a$ and $b$ have length $n$.

-   Insert elements of $\alpha$ into $\gamma$ in the form $(\alpha_i,\alpha_i)$.

-   Insert elements of $\beta$ into $\gamma$ in the form $(\beta_j,0)$.

-   Among all non-zero elements $(c_k,d_k)$ in the resulting linear basis $\gamma$, the collection of $c_k$ from vectors where $c_k\neq 0$ forms a basis of the union of $\alpha$ and $\beta$, and the collection of $d_k$ from vectors where $c_k=0$ forms a basis of the intersection of $\alpha$ and $\beta$.

The method for constructing linear bases in the algorithm can be the [greedy method](#greedy-method) or [Gaussian elimination method](#gaussian-elimination-method), as long as the linear basis in $\gamma$ forms a row echelon matrix.

Comparing the elimination steps in the Zassenhaus algorithm with the naive algorithm above, it is easy to find that the greedy-based Zassenhaus algorithm is equivalent to the naive algorithm that maintains contributions of $\alpha$ elements. If instead we first insert all $(\alpha_i,0)$, then insert all $(\beta_j,\beta_j)$, then the greedy-based Zassenhaus algorithm is equivalent to the naive algorithm that maintains contributions of $\beta$ elements. Based on the equivalence of elimination steps, the correctness of the Zassenhaus algorithm also holds.

Additionally, we can provide an independent and more general algebraic proof:

??? note "Correctness proof"
    Let $V$ be a vector space with subspaces $U=\operatorname{span}\alpha$ and $W=\operatorname{span}\beta$. The algorithm itself is equivalent to finding a basis $\gamma$ of
    
    $$
    H = \operatorname{span}(\{(\alpha_i,\alpha_i):\alpha_i\in\alpha\}\cup\{(\beta_j,0):\beta_j\in\beta\})
    $$
    
    by reducing to row echelon form. At the end of the algorithm, elements $(c_k,d_k)$ in $\gamma$ need to be divided into two categories according to whether $c_k\neq 0$. So consider the projection mapping $\pi:H\rightarrow V$ with $\pi(a,b)=a$. Then $\pi(H)=U+W$ and it is easy to verify
    
    $$
    \begin{aligned}
    \ker\pi &= H\cap(\{0\}\times V) = \{0\}\times(U\cap W).
    \end{aligned}
    $$
    
    According to [theorems on linear mappings](./linear-mapping.md#kernel-space-and-image-space-of-linear-mappings), $\dim H = \dim\pi(H)+\dim\ker\pi = \dim(U+W)+\dim(U\cap W)$.
    
    The first few columns of a row echelon matrix are still a row echelon matrix, so the number of rows where $c_k\neq 0$ exactly equals the row rank of $\alpha\cup\beta$, which is $\dim(U+W)$. Moreover, the set of $c_k$ from these rows forms a basis of $U+W$. The remaining non-zero rows exactly number $\dim(U\cap W)$, and all satisfy $c_k=0$. For $d_k$ in these rows, since $(0,d_k)\in\ker\pi$, we have $d_k\in U\cap W$. Moreover, $(0,d_k)$ as a row in a row echelon matrix must be linearly independent, which shows these $d_k$ are all linearly independent. Together, these $d_k$ form a linearly independent set of size $\dim(U\cap W)$ in the intersection space $U\cap W$, so they must also be a basis of this space.

Sample code:

??? example "Code (Library Checker [Intersection of $\mathbf F_2$ vector spaces])"
    ```cpp
    --8<-- "docs/math/code/basis/basis_intersect_2.cpp"
    ```

Note that when outputting, only consider vectors whose first $n$ bits are all zero.

### Extension: Prefix Linear Basis

This section only discusses the case of XOR linear bases, and assumes a single vector can be stored in $O(1)$ space, with single operation complexity always $O(1)$.

For cases requiring multiple queries of maximum XOR in intervals, one common approach is to use [Cat tree](../../ds/cat-tree.md) combined with linear basis, with time complexity $O(nm\log m+n^2q)$, where $n$ is vector length, $m$ is sequence length, $q$ is number of queries. Another viable approach is to use prefix linear bases (or timestamp linear bases), which can reduce complexity to $O(n(m+q))$.

A prefix linear basis maintains the linear basis of all suffixes for each prefix of the sequence, allowing us to query the linear basis of each interval. Note that the linear bases of all suffixes $[j,i]$ of a prefix $[1,i]$ are mutually contained: the linear basis of $[j,i]$ always contains the linear basis of $[j+1,i]$. Therefore, among these suffix linear bases, there are at most $n$ different types, and they can always be obtained by progressively adding new vectors to an empty set to get all these suffix linear bases from $[i,i]$ to $[1,i]$. Therefore, using this monotonicity, for each added vector $v$, we just need to mark its maximum index $t$, and we can store all suffix linear bases in $O(n)$ space. Moreover, when querying the linear basis corresponding to interval $[j,i]$, we only need to keep vectors with timestamp $t\ge j$ in the prefix linear basis at position $i$.

We can call the timestamp $t$ of each vector $v$ its timestamp. A vector $v$ in the linear basis can always be expressed as the XOR sum of some elements in the original sequence, for example $v_{i_1}\oplus v_{i_2}\oplus\cdots\oplus v_{i_k}$. Among all such possible representations, the maximum value of the minimum index is $t$, that is,

$$
t(v) = \max\{j:\exists i_1,\cdots,i_k\in[j,i]\text{ s.t. }v=v_{i_1}\oplus v_{i_2}\oplus\cdots\oplus v_{i_k}\}.
$$

This expression is just a formal way of writing the previous paragraph's description. What it gives us is that to maintain the timestamp of each vector $v$ in the linear basis, we just need to greedily select vectors as new as possible to replace old ones.

Based on the [greedy method](#greedy-method) mentioned above for constructing linear bases, the prefix linear basis makes the following adjustments during construction:

-   Save a timestamp $t_x$ for each retained vector $a_x$ in the linear basis, initially all set to $0$.

-   When adding the $i$-th vector $v$ from the sequence, still scan from high to low, but also record the current time $i$.

-   If bit $x$ of $v$ is $1$, compare the timestamp $t_x$ of the existing vector $a_x$ in the linear basis with the current time $i$:
    -   If $i>t_x$, that is, the vector to be added is newer, set $a_x$ to $v$, update the timestamp to $i$, and continue the addition process with the result $a_x\oplus v$ of XORing the old $a_x$ with $v$ using the recorded time $t_x$.
    -   If $i<t_x$, that is, the vector to be added is older, do not update $a_x$ and $t_x$, just XOR $v$ with $a_x$ and continue the addition.

In other words, if the current bit can be represented by a newer vector, directly use the newer vector; otherwise, keep the original vector. When updating the vector at position $x$, we cannot store the XOR result $a_x\oplus v$ at position $x$, because the timestamp of the XOR result $a_x\oplus v$ is $\min\{t(a_x)=t(v)\}=t(a_x)$, which is less than the timestamp $t(v)$ of the vector $v$ to be added. For the same reason, the [Gaussian elimination method](#gaussian-elimination-method) for constructing linear bases may destroy the timestamp property when updating upward during the process, so it is no longer suitable for constructing prefix linear bases.

Sample code:

??? example "Code (Codeforces 1100F Ivan and Burgers)"
    ```cpp
    --8<-- "docs/math/code/basis/prefix_basis.cpp"
    ```

If online queries are needed, we can also store the prefix linear basis at each prefix using $O(mn)$ space, then query. This can be considered a kind of "persistent" linear basis. If the properties of the linear basis obtained from Gaussian elimination are needed, they can be handled separately during queries.

### Practice Problems

-   [Luogu P3812 [Template] Linear Basis](https://www.luogu.com.cn/problem/P3812)
-   [Acwing 3164. Linear Basis](https://www.acwing.com/problem/content/description/3167)
-   [SGU 275 to xor or not xor](https://codeforces.com/problemsets/acmsguru/problem/99999/275)
-   [HDU 3949 XOR](https://acm.hdu.edu.cn/showproblem.php?pid=3949)
-   [HDU 6579 Operation](https://acm.hdu.edu.cn/showproblem.php?pid=6579)
-   [Luogu P4151 [WC2011] Maximum XOR Sum Path](https://www.luogu.com.cn/problem/P4151)
-   [Library Checker - Intersection of $\mathbf F_2$ vector spaces](https://judge.yosupo.jp/problem/intersection_of_f2_vector_spaces)
-   [AtCoder Grand Contest 045 A - Xor Battle](https://atcoder.jp/contests/agc045/tasks/agc045_a)
-   [Codeforces 1100F Ivan and Burgers](https://codeforces.com/problemset/problem/1100/F)
-   [Luogu P3292 [SCOI2016] Lucky Number](https://www.luogu.com.cn/problem/P3292)

## References and Notes

1.  Qiu Weisheng, Advanced Algebra (Vol. 2). Tsinghua University Press.
2.  [Basis (linear algebra) - Wikipedia](https://en.wikipedia.org/wiki/Basis_%28linear_algebra%29)
3.  [Vector Basis -- from Wolfram MathWorld](https://mathworld.wolfram.com/VectorBasis.html)
4.  [Zassenhaus algorithm - Wikipedia](https://en.wikipedia.org/wiki/Zassenhaus_algorithm)

[^existence_basis]: [Proof that every vector space has a basis](https://en.wikipedia.org/wiki/Basis_%28linear_algebra%29#Proof_that_every_vector_space_has_a_basis)