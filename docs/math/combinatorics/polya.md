author: Wajov, Early0v0, Enter-tainer, Great-designer, iamtwz, Ir1d, MegaOwIer, mgt, StudyingFather, Tiphereth-A, warzone-oier, Xeonacid, c-forrest

Prerequisite: [Permutations and Combinations](../permutation.md)

## Introduction

The Pólya enumeration theorem is typically used to solve counting problems involving "essentially different" configurations.

???+ info "This article may involve related content from group theory"
    This article may involve content from group theory. This article will provide simple explanations of the relevant group theory concepts to help readers unfamiliar with this content understand and apply the Pólya enumeration theorem. For rigorous definitions and discussions of group theory, please refer to chapters such as [Basic Concepts of Abstract Algebra](../algebra/basic.md) and [Group Theory](../algebra/group-theory.md).

??? info ""Space Symmetry Group", "Symmetric Group", and "Permutation Group""
    This article will inevitably use these three types of group names simultaneously. Although this may easily cause confusion, they indeed refer to different concepts. Given a geometric structure, a symmetry operation on it refers to a geometric transformation that makes it coincide with itself, and the space symmetry group is the set of all such symmetry operations. The symmetric group is the set of all permutations on a given set. A permutation group is a subgroup of the symmetric group, i.e., a group formed by some (not necessarily all) permutations. Later, we will explain how to represent the space symmetry group of a given geometric structure as a permutation group for counting problems.

## Burnside's Lemma

Further reading: [Burnside's Lemma](../algebra/group-theory.md#burnside-lemma)

The Pólya enumeration theorem is an application and generalization of Burnside's lemma. Before introducing the Pólya enumeration theorem, we need to briefly review Burnside's lemma.

To derive the general pattern, let's first consider a simple example.

???+ example "Necklace Coloring"
    Consider a necklace with 4 beads, where each bead can be colored either red or blue. How many essentially different colorings are there? (If two colorings can be made identical by rotating the necklace, they are considered the same.)

??? example "Solution and Analysis"
    This problem is simple enough to be solved by enumeration. There are 4 beads, each with 2 possible colors, so there are $2^4 = 16$ possible colorings in total. Grouping those that can be transformed into each other by rotation yields 6 groups, as shown in the figure. (Here, each coloring is encoded by the colors of beads starting from the bottom-left bead and going clockwise; B represents blue, R represents red; colorings in the same group have the same background color.)

    ![Necklace coloring](../images/necklaces.svg)

    From this example, we can see that to calculate the number of essentially different colorings, the key is to know how many different colorings correspond to each essentially identical coloring. In other words, we need to determine the size of each group in the figure above.

    Colorings that can be grouped together are those that can be transformed into each other by rotation. There are 4 possible rotations, namely

    $$
    G = \{r_0, r_1, r_2, r_3\},
    $$

    representing rotations by 0, 1, 2, and 3 positions respectively. Rotation by 0 positions means staying in place.

    First, consider the group containing the coloring $RRBB$. Applying these four operations yields

    $$
    RRBB, RBBR, BBRR, BRRB.
    $$

    These four colorings are all different, so this group has 4 elements.

    Now consider the group containing the coloring $BRBR$. Applying these four operations yields

    $$
    BRBR, RBRB, BRBR, RBRB.
    $$

    Here, the result of rotation by 2 positions is the same as no rotation, and the result of rotation by 3 positions is the same as rotation by 1 position. So this group has 2 elements.

    If we look at the groups containing $BBBB$ and $RRRR$, applying the four operations yields only themselves. Therefore, each group has only 1 element.

    Let $x$ represent a coloring, and $Gx$ represent the set of color encodings obtainable by applying operations to $x$. From the above example, we can summarize a pattern: the effect of operations in $G$ on $x$ exhibits some kind of "periodicity".

    Let $|G|$ represent the total number of operations. This "periodicity" means that if there are $m$ different operations in $G$ that map $x$ to itself, then the results of $x$ under these operations will repeat $m$ times. Therefore, under these operations, there are $|G|/m$ different results for $x$, which is exactly the size of the group containing $x$.

    In this example, only rotation by 0 positions ($r_0$) can map $RRBB$ to itself, so its group size is $4/1 = 4$. Both rotation by 0 positions ($r_0$) and rotation by 2 positions ($r_2$) can map $BRBR$ to itself, so its group size is $4/2 = 2$. No matter how many positions we rotate, $BBBB$ maps to itself, so its group size is $4/4 = 1$.

    In the following, let $G_x$ represent the number of operations that map $x$ to itself, so $|G_x|$ is $m$ from above. Then the group size of $X$ is $|G|/|G_x|$. To calculate the number of groups of colorings, we only need to enumerate all possible colorings $x \in X$, and for colorings with group size $|Gx|$, assign weight $1/|Gx|$. This allows us to express the number of groups as

    $$
    |X/G| = \sum_{x \in X}\frac{1}{|Gx|} = \sum_{x \in X}\frac{|G_x|}{|G|}.
    $$

    The current form of this formula is not convenient for application. Let $gx$ be the result of applying operation $g \in G$ to the coloring $x \in X$. Then the set $G_x$ described above is $\{g \in G: gx = x\}$. Changing the order of summation gives

    $$
    \begin{aligned}
    \sum_{x \in X}|G_x| 
    &= \sum_{x \in X}|\{g \in G: gx = x\}|\\
    &= \sum_{x \in X}\sum_{g \in G}[gx = x]\\
    &= \sum_{g \in G}\sum_{x \in X}[gx = x]\\
    &= \sum_{g \in G}|\{x \in X: gx = x\}|\\
    &= \sum_{g \in G}|X^g|.
    \end{aligned}
    $$

    Here, $[\cdot]$ is the Iverson bracket. In the result after changing the order of summation, $X^g = \{x \in X: gx = x\}$ is the set of colorings $x$ that remain unchanged under operation $g$. In other words, it consists of the fixed points of operation $g$.

    After these discussions, the number of groups can now be written as

    $$
    |X/G| = \frac{1}{|G|}\sum_{g \in G}|X^g|.
    $$

    That is, the number of groups equals the average number of fixed points of all rotation operations.

    As an application of this result, let's recalculate the number of essentially different colorings for the necklace. The fixed points of these rotation operations are listed below.

    |   Operation  |            Fixed Points             |
    | :---: | :-------------------------------: |
    | $r_0$ |               $X$                |
    | $r_1$ |        $\{BBBB, RRRR\}$        |
    | $r_2$ |   $\{BBBB, BRBR, RBRB, RRRR\}$  |
    | $r_3$ |        $\{BBBB, RRRR\}$        |

    Therefore, the number of groups equals

    $$
    \frac{16 + 2 + 4 + 2}{4} = 6.
    $$

    This matches our earlier result.

From this example, we can derive a general result for solving such counting problems. For the sake of discussion, we consider the scenario of coloring problems in this article, though it can also be applied to other scenarios, with examples provided at the end.

A coloring problem is: given some structure, coloring each of its vertices yields different coloring schemes. This structure has some symmetry such that seemingly different colorings can be transformed into each other through a series of symmetry operations. These mutually transformable colorings are called essentially identical. The problem asks for the number of essentially different colorings.

Based on the analysis in the example, to solve this problem, we first need to determine what symmetry operations the given structure has. The set of these symmetry operations $G$ is called the space symmetry group of the given structure. In practical applications, most of the time we don't need to understand the definition of groups; we only need to be able to discuss all space symmetry operations without omission. Later in this article, we analyze several common space symmetry group structures, where the definition of groups is explained.

The set of all colorings is denoted $X$, and an individual coloring is denoted $x$. The result of applying operation $g \in G$ to coloring $x \in X$ is $gx$. Then all results obtainable by applying some operation to coloring $x$ is $Gx = \{gx: g \in G\}$, which is called the orbit of $x$ under group $G$. Different colorings in the same orbit are what this problem calls "essentially identical". Therefore, the number of essentially different colorings is equivalent to the number of distinct orbits.

The analysis in the example can be generalized to general cases.

???+ note "Burnside's Lemma"
    Given a group $G$ acting on a set $X$, the number of distinct orbits is

    $$
    |X/G| = \frac{1}{|G|}\sum_{g \in G}|X^g|.
    $$

    Here, $X^g = \{x \in X: gx = x\}$ is the set of fixed points under the action of $g \in G$.

The proof is essentially a direct application of the analysis in the example above. However, the example used an observation: the results of the action of group $G$ on a single element $x$ have some kind of "periodicity", so the number of such period repetitions equals the number of operations that map $x$ to itself. This observation is correct in general cases, but because the structure of group $G$ may be complex, its "periodicity" may not be as straightforward as in the example. To state this observation rigorously, we need to use the orbit-stabilizer theorem from group theory.

In applications, as long as we can enumerate all symmetry operations and provide the number of fixed points for each symmetry operation, we can solve the corresponding counting problem. Below is a slightly more complex application.

???+ example "Cube Coloring"
    Color a cube using three colors. How many essentially different colorings are there? (Two colorings that become the same after spatial rotation are considered the same.)

??? example "Solution"
    Since the cube has 6 faces, each with 3 coloring methods, there are $3^6$ possible colorings in total, i.e., $|X| = 3^6$. Let the space symmetry group of the cube be $G$.

    ![](../images/cube.svg)

    Next, we need to analyze all operations in $G$. They can be divided into the following categories (for convenience, we call the six faces: front, back, top, bottom, left, right):

    -   Identity: since all direct coloring schemes remain unchanged under the identity transformation, it has $|X^g| = 3^6$;
    -   $90^\circ$ rotation about the axis through the centers of two opposite faces: there are 3 choices for the pair of opposite faces, and 2 choices for rotation direction, so there are 6 permutations in total. If we choose the axis through the centers of the front and back faces, then to remain unchanged after rotation, the top, bottom, left, and right faces must all have the same color. At this point, there are 3 independently colorable regions, so $|X^g| = 3^3$;
    -   $180^\circ$ rotation about the axis through the centers of two opposite faces: there are 3 choices for the pair of opposite faces, and the rotation direction doesn't matter, so there are 3 permutations in total. If we choose the axis through the centers of the front and back faces, then to remain unchanged after rotation, the top and bottom faces must have the same color, and the left and right faces must have the same color. At this point, there are 4 independently colorable regions, so $|X^g| = 3^4$;
    -   $180^\circ$ rotation about the axis through the midpoints of two opposite edges: there are 6 choices for the pair of opposite edges, and the rotation direction still doesn't matter, so there are 6 permutations in total. If we choose the edge between the front and top faces and the edge between the back and bottom faces as the pair of opposite edges, then to remain unchanged after rotation, the front and top faces must have the same color, the back and bottom faces must have the same color, and the left and right faces must have the same color. At this point, there are 3 independently colorable regions, so $|X^g| = 3^3$;
    -   $120^\circ$ rotation about the axis through two opposite vertices: there are 4 choices for the pair of opposite vertices, and 2 choices for rotation direction, so there are 8 permutations in total. If we choose the top-right corner of the front face and the bottom-left corner of the back face as the pair of opposite vertices, then to remain unchanged after rotation, the front, top, and right faces must all have the same color, and the back, bottom, and left faces must all have the same color. At this point, there are 2 independently colorable regions, so $|X^g| = 3^2$.

    Therefore, the number of essentially different colorings is

    $$
    \frac{1 \times 3^6 + 6 \times 3^3 + 3 \times 3^4 + 6 \times 3^3 + 8 \times 3^2}{1 + 6 + 3 + 6 + 8} = 57.
    $$

## Pólya Enumeration Theorem

In the statement of Burnside's lemma, the property that $X$ is the set of all colorings of some structure is not used. Actually, the application scope of Burnside's lemma is not limited to coloring counting problems. For coloring counting problems, the Pólya enumeration theorem provides a more precise calculation method. It can be seen as the application of the general Burnside's lemma to coloring counting problems.

Compared to Burnside's lemma, the improvement of the Pólya enumeration theorem is that it provides a specific calculation method for the size of the fixed point set $|X^g|$ in coloring counting problems.

This can be intuitively seen from the cube coloring example above. For various symmetry operations of the cube, the size of the fixed point set is always in the form $m^{c(g)}$, where $m$ is the number of colors, and $c(g)$ is the number of independently colorable regions under operation $g$. This observation also holds in general cases, but we need to further clarify how to calculate $c(g)$ for a given $g$.

Choosing a coloring scheme for a structure, mathematically, means choosing a mapping $f: X \rightarrow C$ from the set of colorable objects of this structure (such as beads in a necklace, faces of a cube, etc.) $X$ to the set of colors $C$. Therefore, the set of coloring schemes is $C^X$. The space symmetry group $G$ of the structure acts on the structure, and naturally also acts on the set $X$. This symmetry operation always corresponds to a bijection on set $X$, i.e., a **permutation**.

Now let's analyze the structure of the fixed point set $(C^X)^g$. Given $g$, treated as a permutation on $X$, following the analysis in the example, if a position $x$ in $X$ can move to position $y$ after finitely many repeated applications of $g$, then as a fixed point $f \in (C^X)^g$, it must satisfy $f(x) = f(y)$. In the language of orbits from the previous section, since positions $x$ and $y$ are in the same orbit under the action of $g$, they must be colored the same. In the language of permutations, in the cycle decomposition of $g$, positions $x$ and $y$ are in the same cycle, so they need to be colored the same. Different cycles in the cycle decomposition can be colored differently and independently, so the number of independently colorable regions is $c(g)$, i.e., the number of cycles in the cycle decomposition of $g$.

Thus, the number of fixed points of operation $g$ is $|C|^{c(g)}$. Substituting this into Burnside's lemma gives the unweighted version of the **Pólya enumeration theorem**.

???+ note "Pólya Enumeration Theorem (Unweighted Version)"
    Given a group $G$ acting on a set $X$ and a set of colors $C$, the number of distinct colorings is

    $$
    |C^X/G| = \frac{1}{|G|}\sum_{g \in G}m^{c(g)},
    $$

    where $m$ is the number of colors, and $c(g)$ is the number of cycles in the cycle decomposition of the permutation representation of $g \in G$.

??? info "About the meaning of group $G$"
    There is some abuse of notation here. If group $G$ acts on $X$, then the group action on the coloring scheme set $C^X$ needs to be redefined, which is not distinguished here.

As a simple application of the Pólya enumeration theorem, let's recalculate the previous example using the Pólya enumeration theorem.

??? example "Necklace Coloring Problem - Alternative Solution"
    Label the 4 beads $1 \sim 4$, then the elements in group $G$ from the example have the following permutation representations (all written in cycle decomposition form):

    -   Rotation by 0 positions $r_0 = (1)$, with 4 cycles in total (note that 1-cycles are omitted);
    -   Rotation by 1 position $r_1 = (1234)$, with 1 cycle in total;
    -   Rotation by 2 positions $r_2 = (13)(24)$, with 2 cycles in total;
    -   Rotation by 3 positions $r_3 = (1432)$, with 1 cycle in total.

    Therefore, the number of essentially different colorings is

    $$
    \frac{2^4 + 2^1 + 2^2 + 2^1}{4} = 6.
    $$

??? example "Cube Coloring Problem - Alternative Solution"
    Since the previous analysis essentially gave the cycle representations of various permutations, only not written explicitly with numeric symbols, we won't repeat the previous analysis here. Let's just consider the case of $180^\circ$ rotation about the axis through the midpoints of opposite edges as an example. Label the 6 faces as $1 \sim 6$: front, back, top, bottom, left, right. The corresponding permutation is $(13)(24)(56)$, so $c(g) = 3$. Other types of permutations can be analyzed similarly, and the final counting expression is exactly the same as above.

## Weighted Version Extension

The unweighted version of the Pólya enumeration theorem can only give the count of all essentially different coloring problems, but it cannot handle more refined problems. For example, if in the above coloring problem, we are given the number of each color that can be used, we cannot directly apply the Pólya enumeration formula above. To actually solve such problems, we need to derive again using Burnside's lemma; and summarizing these results in the form of generating functions gives the weighted version of the Pólya enumeration theorem.

???+ example "Necklace Coloring (with Restrictions)"
    Consider a necklace with 4 beads, each bead can be either red or blue. We have exactly 2 red beads and 2 blue beads available. How many essentially different colorings are there? (If two colorings can be made identical by rotating the necklace, they are considered the same.)

??? example "Solution and Analysis"
    Consider using Burnside's lemma. There are 2 red beads and 2 blue beads, totaling $\binom{4}{2} = 6$ coloring schemes. The space symmetry group $G = \{r_0, r_1, r_2, r_3\}$ corresponds to rotations 0~3 respectively. Their fixed point sets are analyzed as follows:

    -   Rotation by 0 positions $r_0 = (1)$, all 6 coloring schemes are fixed points;
    -   Rotation by 1 position $r_1 = (1234)$, fixed points require all beads to have the same color, so there are no fixed points;
    -   Rotation by 2 positions $r_2 = (13)(24)$, there are 2 independently colorable regions, each of size 2. They need to be colored with one red and one blue respectively, so the fixed point set has size 2;
    -   Rotation by 3 positions $r_3 = (1432)$, same as rotation by 1 position, there are no fixed points.

    Therefore, according to Burnside's lemma, the number of essentially different colorings is

    $$
    \frac{6 + 0 + 2 + 0}{4} = 2.
    $$

From this example, we can derive the following calculation method. For problems with restrictions on the number of different colors, we also need to color the cycles of each permutation in the space symmetry group, but we need to ensure that the number of colors used exactly equals the given number of colors. Such combinatorial problems usually don't have explicit solutions. Except for special cases that can be calculated using [combinatorics methods](../combinatorics/combination.md), they need to be treated as [knapsack problems](../../dp/knapsack.md).

This counting problem can be answered using generating functions. Given a permutation $g$, if its [type](../permutation.md#type-of-a-permutation) is $1^{\alpha_1}2^{\alpha_2}\cdots n^{\alpha_n}$, i.e., it has $\alpha_k$ cycles of length $k$, and for each cycle, it can be colored with one of $m$ colors, then in the generating function

$$
\prod_{k=1}^n\left(\sum_{i=1}^m x_i^k\right)^{\alpha_k},
$$

the coefficient of the monomial $x_1^{\beta_1}x_2^{\beta_2}\cdots x_m^{\beta_m}$ is the count where color $i$ is used $\beta_i$ times. The expression in parentheses, $\sum_{i=1}^m x_i^k$, has the combinatorial meaning: for a cycle of length $k$, if color $i$ is used $k$ times, the counting method is 1; for other cases, the count is 0; this precisely describes the requirement that positions in the same cycle have consistent coloring.

Applying Burnside's lemma to each monomial in the generating function for counting colorings under a given permutation gives the essentially different counts for various color combinations. Since the generating function is linear for each monomial, the generating function for the count of essentially different coloring schemes is

$$
\frac{1}{|G|}\sum_{g \in G}\prod_{k=1}^n\left(\sum_{i=1}^m x_i^k\right)^{\alpha_k}.
$$

Expanding this expression, the coefficient of each monomial gives the count of essentially different colorings for the given color combination.

In the above process, the generating function $\sum_{i=1}^m x_i^k$ for coloring each cycle has nothing special and can be replaced by other generating functions. Therefore, there is a general version of the Pólya enumeration theorem.

???+ note "Cycle Index of a Permutation Group"
    Given a permutation group $G$, the **cycle index** of group $G$, denoted $Z_G(t_1, t_2, \cdots, t_n)$, is defined as

    $$
    Z_G(t_1, t_2, \cdots, t_n) = \frac{1}{|G|}\sum_{g \in G}t_1^{c_1(g)}t_2^{c_2(g)}\cdots t_n^{c_n(g)},
    $$

    where $c_k(g)$ is the number of cycles of length $k$ in the cycle decomposition of permutation $g$, i.e., $1^{c_1(g)}2^{c_2(g)}\cdots n^{c_n(g)}$ is the type of permutation $g$.

???+ note "Pólya Enumeration Theorem (Weighted Version)"
    Given a group $G$ acting on a set $X$, where the coloring method for each point is given by a generating function $f(x_1, x_2, \cdots, x_m)$ of the count of coloring schemes, then the generating function for the count of essentially different coloring schemes of set $X$ is

    $$
    Z_G(f(x_1^1, x_2^1, \cdots, x_m^1), f(x_1^2, x_2^2, \cdots, x_m^2), \cdots, f(x_1^n, x_2^n, \cdots, x_m^n)),
    $$

    where $Z_G(t_1, t_2, \cdots, t_n)$ is the cycle index of group $G$.

Here, if the generating function for coloring a single position is $f(x_1, x_2, \cdots, x_m)$, then the generating function for coloring a cycle of length $k$ is $f(x_1^k, x_2^k, \cdots, x_m^k)$. This reflects that if a coloring scheme is a fixed point of a given permutation, all positions in the same cycle must be colored the same color. If we evaluate the generating function at $x_i = 1$, we obtain the unweighted version of the Pólya enumeration theorem.

The statement of the theorem uses the concept of the cycle index of a permutation group. It is independent of specific coloring problems. It describes the structure of the permutation group.

??? example "Restricted Necklace Coloring Problem - Alternative Solution"
    The cycle index of the rotational symmetry group is $\frac{1}{4}(t_1^4 + t_2^2 + 2t_4)$, and the generating function for single-point coloring is $r + b$. Therefore, the generating function for all coloring schemes is

    $$
    \begin{aligned}
    F(r, b) &= \frac{1}{4}\left((r+b)^4 + (r^2+b^2)^2 + 2(r^4+b^4)\right)\\
    &= r^4 + r^3b + 2r^2b^2 + rb^3 + b^4.
    \end{aligned}
    $$

    The desired count is the coefficient of $r^2b^2$, which is 2 essentially different colorings. Incidentally, this formula also gives counts under other restrictions.

### Applications

The weighted version of the Pólya enumeration theorem plays an important role in combinatorial counting problems. Here we briefly discuss its applications, and for more general discussions, refer to [Formal Methods for Combinatorial Problems](../poly/symbolic-method.md#finite-constructions).

???+ example "Diamond Necklace"
    Consider a necklace with 4 identical beads, where each bead can have several diamonds. If there are 4 diamonds in total, how many essentially different ways to set them? (If two ways can be made identical by rotating the necklace, they are considered the same.)

??? example "Solution and Analysis"
    The space symmetry group of the necklace is the same as described before. Without restrictions on the total number of diamonds, the generating function for the diamond-setting scheme at a single position is

    $$
    f(x) = 1 + x + x^2 + \cdots = \sum_{i=1}^\infty x^i = \frac{1}{1-x}.
    $$

    Applying the weighted version of the Pólya enumeration theorem, the generating function for all diamond-setting schemes is

    $$
    \begin{aligned}
    F(x) &= \frac{1}{4}\left(f(x)^4 + f(x^2)^2 + 2f(x^4)\right)\\
    &= 1 + x + 3x^2 + 5x^3 + 10x^4 + \cdots.
    \end{aligned}
    $$

    Therefore, the number of diamond-setting schemes is the coefficient of $x^4$, which is 10 schemes in total. For verification, by enumeration, they are

    $$
    4000, 3100, 3010, 3001, 2200, 2020, 2110, 2101, 2011, 1111.
    $$

    Here, each group of four numbers represents the number of diamonds on each bead.

This example shows that the weighted version of the Pólya enumeration theorem can solve problems far broader than just coloring counting problems. It provides a method to extend single-point counting to essentially different counting for the entire structure. Coloring problems are just a special case of such problems.

## Common Space Symmetry Groups

One of the difficulties in problems related to Pólya enumeration is analyzing the structure of permutation groups. Here, we briefly discuss the structures of common space symmetry groups and describe them using their cycle indices. It should be noted that for the same structure's space symmetry group, if the set of objects being acted upon is different, the corresponding group action is also different, and thus their permutation representations are different. For example, the space symmetry group of a cube acting on its vertices, edges, and faces respectively correspond to the vertex permutation group, edge permutation group, and face permutation group of the cube. The numbers of vertices, edges, and faces are different, so these permutation groups and their corresponding cycle indices are naturally different. Therefore, in solving specific problems, we cannot ignore the specification of the object of the group action.

??? info "Relationship between Space Symmetry Groups and Permutation Groups"
    Although the two concepts are very similar, they are not the same object. In the language of group theory, given a space symmetry group $G$ and its action on a set $X$, the permutation representation of the group action provides a homomorphism $\varphi$ from group $G$ to the symmetric group $S_X$. Moreover, this permutation representation is often faithful in the context of combinatorial counting, i.e., $\ker\varphi = \{e\}$, so homomorphism $\varphi$ is actually an embedding of group $G$ into group $S_X$. The permutation group in the text is precisely the image of this embedding, i.e., $\varphi(G)$, which is isomorphic to the original space symmetry group $G$. Therefore, for the same structure's space symmetry group $G$, different choices of group action will be isomorphic to different permutation groups $\varphi(G)$, and consequently have different cycle indices (isomorphic permutation groups do not necessarily have the same cycle indices).

Given a structure, its space symmetry group is the set of all operations that can map it to itself. It must satisfy the following conditions:

-   Applying two symmetry operations in succession to a given structure can be regarded as applying another symmetry operation, i.e., the set of symmetry operations is closed under composition;
-   The composition of symmetry operations satisfies the associative law;
-   There exists an identity symmetry operation, i.e., the given structure remaining unchanged itself is also considered an operation;
-   Every operation has its inverse operation, which can undo the effect of the given operation.

A [group](../algebra/basic.md#group) is an abstraction of all concepts satisfying these conditions. The discussion of group structures is the main content of [group theory](../algebra/group-theory.md). Our analysis here focuses on space symmetry groups, and the discussion of their structures mainly uses geometric perspectives. Here we provide common examples, and readers should derive common approaches to analyzing such problems from these.

### Cyclic Group

For a regular $n$-gon, all its rotation operations form a space symmetry group called the cyclic group, denoted $C_n$. Let the counterclockwise rotation by $(360/n)^\circ$ be denoted as $r$, then the elements of group $C_n$ can be written as

$$
C_n = \{e, r, r^2, \cdots, r^{n-1}\}.
$$

Here, $r^k$ refers to applying operation $r$ $k$ times, i.e., counterclockwise rotation by $(360k/n)^\circ$, and $e = r^0$ refers to the identity transformation.

Whether considering the action of the cyclic group on all vertices or all edges of a regular $n$-gon, its permutation representation is the same. Let's analyze the permutation representation of the group action by taking the set of all vertices as an example. Its cycle index is

$$
Z(C_n) = \frac{1}{n}\sum_{d \mid n}\varphi(d)t_d^{n/d}.
$$

Here, $\varphi(\cdot)$ is the [Euler's totient function](../number-theory/euler-totient.md) from number theory.

Considering only rotation operations, the space symmetry group of a necklace of length $n$ is $C_n$.

??? note "Analysis"
    Let the set of vertices be labeled in counterclockwise order as $\{0, 1, \cdots, n-1\}$, then $r^k(i) = i + k \pmod{n}$. The set of vertices in the cycle containing vertex $i$ is

    $$
    \{i + \ell k \pmod{n}: \ell \in \mathbf{Z}\}.
    $$

    Obviously, $i \equiv i + \ell k \pmod{n}$ if and only if

    $$
    \frac{n}{\gcd(k, n)} \mid \ell.
    $$

    This means that any vertex $i$ lies in a cycle of length $\frac{n}{\gcd(k, n)}$. Therefore, permutation $r^k$ has $\gcd(k, n)$ cycles of equal length. Considering merging like terms in the expression of the cycle index, for a given $d \mid n$, there are $\varphi(d)$ values of $k$ satisfying $\gcd(k, n) = n/d$, and their corresponding monomials are all of the form $t_d^{n/d}$. From this, we can derive the above cycle index expression.

### Dihedral Group

For a regular $n$-gon, all its rotation operations and reflections about symmetry axes also form a space symmetry group, called the dihedral group, denoted $D_{2n}$. Let the counterclockwise rotation by $(360/n)^\circ$ be denoted as $r$, and let the reflection about a given symmetry axis (such as the line through the center and a vertex) be denoted as $s$. Then the operations of group $D_{2n}$ can be written as

$$
D_{2n} = \{e, r, \cdots, r^{n-1}, s, sr, \cdots, sr^{n-1}\}.
$$

Here, $r^k$ is still a rotation operation, and although $sr^k$ means first rotating $k$ times and then reflecting about the given symmetry axis, it can equivalently be regarded as reflecting about another symmetry axis. Therefore, group $D_{2n}$ contains 1 identity transformation, $(n-1)$ rotation operations, and $n$ reflection operations. Its group actions on the vertex set and edge set also have the same permutation representation. Its cycle index is

$$
Z(D_{2n}) = \frac{1}{2}Z(C_n) +
\begin{cases}
\frac{1}{2}t_1 t_2^k, & n = 2k + 1,\\
\frac{1}{4}(t_1^2 t_2^{k-1} + t_2^k), & n = 2k.
\end{cases}
$$

??? note "Analysis"
    The analysis of rotation operations $r^k$ in group $D_{2n}$ (including the identity transformation) is exactly the same as that for cyclic group $C_n$. The key lies in the analysis of reflection operations. At this point, we need to classify according to the parity of the number of vertices $n$.

    When $n = 2k + 1$, all reflection axes are lines connecting a vertex to the midpoint of the opposite edge, totaling $n$ such axes. After each reflection, the vertex on the axis remains fixed, while other vertices are swapped in pairs. Therefore, there is 1 fixed point (1-cycle) and $k$ 2-cycles.

    When $n = 2k$, there are two types of symmetry axes. Half of them are axes connecting opposite vertices; reflecting about such an axis keeps the two vertices on the axis fixed while swapping the remaining vertices in pairs, so there are 2 fixed points (1-cycles) and $(k-1)$ 2-cycles. The other half are axes connecting the midpoints of opposite edges; reflecting about such an axis swaps all vertices in pairs, so there are $k$ 2-cycles.

    Based on this analysis, we can write the above cycle index expression.

### Symmetric Group

For a set of $n$ elements, all permutations on it form a group, called the symmetric group of degree $n$, denoted $S_n$. It describes all the symmetry these $n$ vertices can have. It is also the permutation representation of these symmetry operations acting on the vertex set.

According to the analysis in [Permutations and Combinations](../permutation.md#type-of-a-permutation), its cycle index is

$$
Z(S_n) = \sum_{\alpha_1 + 2\alpha_2 + \cdots + n\alpha_n = n}\frac{t_1^{\alpha_1}t_2^{\alpha_2}\cdots t_n^{\alpha_n}}{1^{\alpha_1}2^{\alpha_2}\cdots n^{\alpha_n}\alpha_1!\alpha_2!\cdots\alpha_n!}.
$$

Here, the number of permutations with type $1^{\alpha_1}2^{\alpha_2}\cdots n^{\alpha_n}$ is

$$
\frac{n!}{1^{\alpha_1}2^{\alpha_2}\cdots n^{\alpha_n}\alpha_1!\alpha_2!\cdots\alpha_n!}.
$$

It satisfies the recurrence relation

$$
Z(S_n) = \frac{1}{n}\sum_{k=1}^n t_k Z(S_{n-k}),
$$

with initial condition $Z(S_0) = 1$. The combinatorial meaning of this recurrence relation is: to construct a permutation of length $n$, first choose the length $k$ of the cycle containing point $n$, then construct the set of remaining $(n-k)$ vertices.

Given a complete graph with $n$ vertices, its space symmetry group is exactly $S_n$. The cycle index of its action on the set of all vertices is given by $Z(S_n)$ above. However, its permutation representation on the set of all edges is not the same. For example, the size of the set is different; the number of edges is $n(n-1)/2$. For the case of edges, additional analysis is needed. Here we give a simple example; for general cases, refer to the exercises.

???+ example "Undirected Simple Graph Counting"
    Count the number of undirected simple graphs with 4 vertices up to isomorphism.

??? example "Solution"
    This is equivalent to coloring the complete graph with 4 vertices with two colors, requiring the number of essentially different colorings. The space symmetry group is $S_4$. Now let's analyze the cycle index of its edge permutation group $S_4^{(2)}$.

    -   Identity transformation (1 type): edges also remain fixed, so the corresponding monomial is $t_1^6$;
    -   Swapping two vertices (6 types): suppose we swap $a$ and $b$, then edges 1 and 3 remain fixed, while edges 2 and 5 swap, and edges 4 and 6 swap, so the corresponding monomial is $6t_1^2t_2^2$;
    -   Cyclic permutation of three vertices (8 types): suppose the cycle is $(abc)$, then the edges between them, 1, 2, 5, also cycle accordingly, and the edges from them to the fourth point $d$, 4, 6, 3, also cycle accordingly, so the corresponding monomial is $8t_3^2$;
    -   Swapping two pairs of vertices (3 types): suppose vertex $a$ swaps with vertex $b$, and vertex $c$ swaps with vertex $d$, then edges 1 and 3 remain fixed, while edges 2 and 4 swap, and edges 5 and 6 swap, so the corresponding monomial is $3t_1^2t_2^2$;
    -   Cyclic permutation of four vertices (6 types): suppose the cycle is $(abcd)$, then the edges between adjacent vertices, 1, 2, 3, 4, also cycle accordingly, and the edges between opposite vertices, 5, 6, swap simultaneously, so the corresponding monomial is $6t_2t_4$.

    Therefore, the cycle index of the edge permutation group is

    $$
    Z(S_4^{(2)}) = \dfrac{1}{24}(t_1^6 + 9t_1^2t_2^2 + 8t_3^2 + 6t_2t_4).
    $$

    According to the Pólya enumeration theorem, the number of undirected simple graphs with 4 vertices up to isomorphism is

    $$
    \frac{2^6 + 9 \times 2^4 + 8 \times 2^2 + 6 \times 2^2}{24} = 11.
    $$

### Polyhedral Groups

A polyhedral group is the space symmetry group of a regular polyhedron. There are only five regular polyhedra: regular tetrahedron, cube, regular octahedron, regular dodecahedron, and regular icosahedron. If we keep the adjacency relations between vertices, edges, and faces but swap vertices and faces, we obtain the dual regular polyhedron. The regular tetrahedron is self-dual, the cube and octahedron are dual to each other, and the dodecahedron and icosahedron are dual to each other. Using the dual relationship, we can simplify the discussion of their space symmetry groups.

Considering only rotation operations in three-dimensional space, there are only three types of space symmetry groups.

-   Tetrahedral group, i.e., the space symmetry group of the regular tetrahedron:
    -   Identity transformation;
    -   Rotation by $120^\circ$ and $240^\circ$ about the axis through a vertex and the center of the opposite face;
    -   Rotation by $180^\circ$ about the axis through the midpoints of opposite edges.

    There are $1 + 2 \times 4 + 1 \times 3 = 12$ symmetry operations in total.

    The cycle indices of the corresponding permutation groups are as follows.

    -   Vertex permutation group and face permutation group: $\frac{1}{12}(t_1^4 + 8t_1t_3 + 3t_2^2)$;
    -   Edge permutation group: $\frac{1}{12}(t_1^6 + 8t_3^2 + 3t_1^2t_2^2)$.

-   Octahedral group, i.e., the space symmetry group of the cube (and regular octahedron):
    -   Identity transformation;
    -   Rotation by $120^\circ$ and $240^\circ$ about the axis through opposite vertices;
    -   Rotation by $180^\circ$ about the axis through the midpoints of opposite edges;
    -   Rotation by $90^\circ$, $180^\circ$, and $270^\circ$ about the axis through the centers of opposite faces.

    There are $1 + 2 \times 4 + 1 \times 6 + 3 \times 3 = 24$ symmetry operations in total.

    The cycle indices of the corresponding cube's permutation groups are as follows.

    -   Vertex permutation group: $\frac{1}{24}(t_1^8 + 8t_1^2t_3^2 + 9t_2^4 + 6t_4^2)$;
    -   Edge permutation group: $\frac{1}{24}(t_1^{12} + 8t_3^4 + 6t_1^2t_2^5 + 6t_4^3 + 3t_2^6)$;
    -   Face permutation group: $\frac{1}{24}(t_1^6 + 8t_3^2 + 6t_2^3 + 6t_1^2t_4 + 3t_1^2t_2^2)$.

    The permutation group of the regular octahedron is similar, just swapping the roles of vertices and faces.

-   Icosahedral group, i.e., the space symmetry group of the regular dodecahedron (and regular icosahedron):
    -   Identity transformation;
    -   Rotation by $120^\circ$ and $240^\circ$ about the axis through opposite vertices;
    -   Rotation by $180^\circ$ about the axis through the midpoints of opposite edges;
    -   Rotation by $72^\circ$, $144^\circ$, $216^\circ$, and $288^\circ$ about the axis through the centers of opposite faces.

    There are $1 + 2 \times 10 + 1 \times 15 + 6 \times 4 = 60$ symmetry operations in total.

    The cycle indices of the corresponding regular dodecahedron's permutation groups are as follows.

    -   Vertex permutation group: $\frac{1}{60}(t_1^{20} + 20t_1^2t_3^6 + 15t_2^{10} + 24t_5^4)$;
    -   Edge permutation group: $\frac{1}{60}(t_1^{30} + 20t_3^{10} + 15t_1^2t_2^{14} + 24t_5^6)$;
    -   Face permutation group: $\frac{1}{60}(t_1^{12} + 20t_3^4 + 15t_2^6 + 24t_1^2t_5^2)$.

    The permutation group of the regular icosahedron is similar, just swapping the roles of vertices and faces.

All of these are cycle indices of permutation groups acting separately on objects like vertices, edges, and faces. If we need to color different objects simultaneously, we need to write a combined cycle index.

## Exercises

### Coloring Problems

These problems only require analyzing the structure of permutation groups and applying the Pólya enumeration theorem.

-   [Luogu P4980【模板】Polya 定理](https://www.luogu.com.cn/problem/P4980)
-   [Luogu P2561 [AHOI2002] 黑白瓷砖](https://www.luogu.com.cn/problem/P2561)
-   [TRANSP - Transposing is Fun](https://www.spoj.com/problems/TRANSP/)
-   [TRANSP2 - Transposing is Even More Fun](https://www.spoj.com/problems/TRANSP2/)
-   [Luogu P3307 [SDOI2013] 项链](https://www.luogu.com.cn/problem/P3307)

When the available color combinations are restricted, we need to use knapsack DP or combinatorial methods to calculate the number of ways to color cycles.

-   [Luogu P1446 [HNOI2008] Cards](https://www.luogu.com.cn/problem/P1446)
-   [UVA10601 Cubes](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1542)
-   [Luogu P4916 [MtOI2018] 魔力环](https://www.luogu.com.cn/problem/P4916)

### Graph Enumeration

The Pólya enumeration theorem can be used for [graph enumeration](../combinatorics/graph-enumeration.md) problems, where the difficulty lies in enumerating the edge permutation group of graphs.

-   [SGU 282. Isomorphism](https://codeforces.com/problemsets/acmsguru/problem/99999/282)
-   [Luogu P4727 [HNOI2009] 图的同构计数](https://www.luogu.com.cn/problem/P4727)
-   [Luogu P4128 [SHOI2006] 有色图](https://www.luogu.com.cn/problem/P4128)

Another type of graph enumeration problem that can be solved using the Pólya enumeration theorem requires directly manipulating generating functions.

-   [LOJ 6538 烷基计数 加强版 加强版](https://loj.ac/p/6538)
-   [LOJ 6512「雅礼集训 2018」烷烃计数](https://loj.ac/p/6512)
-   [Luogu P6597 烯烃计数](https://www.luogu.com.cn/problem/P6597)
-   [Luogu P5818 [JSOI2011] 同分异构体计数](https://www.luogu.com.cn/problem/P5818)

## References and Notes

-   [Pólya enumeration theorem - Wikipedia](https://en.wikipedia.org/wiki/P%C3%B3lya_enumeration_theorem)
-   [Notes on Pólya's Enumeration Theorem](https://www.diva-portal.org/smash/get/diva2:324594/FULLTEXT01.pdf)
-   [Cycle index - Wikipedia](https://en.wikipedia.org/wiki/Cycle_index)

[^perm-group]: Therefore, the space symmetry group $G$ can be represented as a permutation group on set $X$, i.e., a subgroup of the symmetric group $S_X$.

[^g-act]: Strictly speaking, it's the action of the subgroup $\langle g\rangle \le G$.