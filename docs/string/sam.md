author: GoodCoder666, abc1763613206, ksyx

## Some Notation

-   $\Sigma$: The character alphabet. The size of the alphabet is $|\Sigma| = k$.
-   $s$: A string. Its length is $|s| = n$, with indices starting from $0$.
-   $t_0$: The initial state.
-   $\operatorname{endpos}(t)$: The set of ending positions of substring $t$ in string $s$.
-   $\operatorname{link}(v)$: The suffix link of state $v$.
-   $\operatorname{len}(v)$: The length of the longest substring corresponding to state $v$.
-   $\operatorname{longest}(v)$: The longest substring corresponding to state $v$.
-   $\operatorname{minlen}(v)$: The length of the shortest substring corresponding to state $v$.
-   $\operatorname{shortest}(v)$: The shortest substring corresponding to state $v$.

## Suffix Automaton Overview

The **suffix automaton** (SAM) is a powerful data structure that can solve many string-related problems in linear time.

For example, the following string problems can be solved in linear time using SAM:

-   Find all occurrences of a pattern string in another string.
-   Count the number of distinct substrings in a given string.

Intuitively, the SAM of a string can be understood as a compressed form of **all substrings** of the given string. A notable fact is that SAM stores all this information in a highly compressed form. For a string of length $n$, its space complexity is only $O(n)$. Moreover, the construction time of SAM is also $O(n)$. Specifically, a SAM has at most $2n-1$ states and $3n-4$ transitions.

## Definition

The SAM of a string $s$ is the minimal [DFA](../misc/fsm.md#deterministic-finite-automaton) that accepts all suffixes of $s$.

In other words:

-   SAM is a directed acyclic graph. Vertices are called **states**, edges are called **transitions**.
-   The graph has a source $t_0$, called the **initial state**, from which all other states can be reached.
-   Each **transition** is labeled with a character. All transitions from one state are **different**.
-   There are one or more **terminal states**. If we start from the initial state $t_0$ and eventually reach a terminal state, the concatenation of all transition labels along the path must be a suffix of string $s$. Conversely, every suffix of $s$ can be formed by a path from $t_0$ to some terminal state.
-   Among all automata satisfying the above conditions, SAM has the fewest states.

The key to SAM is precisely this minimality. In fact, building an [AC automaton](./ac-automaton.md) for all suffixes of string $s$ can also obtain a DFA accepting all suffixes of $s$. However, in the worst case, such an automaton has $\Theta(n^2$ states, which is unacceptable. As shown in the example below, many states are duplicated in the DFA obtained by building an AC automaton for all suffixes, and therefore can be merged. SAM takes state merging to the extreme, thus limiting the size of the resulting DFA to $O(n)$. In this sense, SAM is the "compressed" AC automaton of all suffixes of a string.

### Substrings and Paths

The simplest and most important property of SAM is that it contains information about all substrings of string $s$. Any path starting from the initial state $t_0$, if we write down all transition labels along the path, forms a **substring** of $s$. Conversely, every substring of $s$ corresponds to some path starting from $t_0$.

To simplify, we say that a substring **corresponds** to such a path (starting from $t_0$ where all transition labels along it form this substring). Conversely, we say that any path **corresponds** to the string formed by its labels.

There may be multiple paths reaching a state, so we say that a state corresponds to a set of strings, where each string corresponds to one of these paths.

### Simple Examples

We will show some suffix automatons for simple strings here.

The initial state is shown in blue, and terminal states are shown in green.

For string $s=\varnothing$:

![](./images/SAM/SA.svg)

For string $s=\texttt{a}$:

![](./images/SAM/SAa.svg)

For string $s=\texttt{aa}$:

![](./images/SAM/SAaa.svg)

For string $s=\texttt{ab}$:

![](./images/SAM/SAab.svg)

For string $s=\texttt{abb}$:

![](./images/SAM/SAabb.svg)

For string $s=\texttt{abbb}$:

![](./images/SAM/SAabbb.svg)

In this last example, one can see that if we directly build an AC automaton for all its suffixes, the paths $\texttt{bbb}$ and $\texttt{abbb}$ should lead to different states, but both states are terminal states, and no matter what character is added, no longer matching string can be obtained. This shows that the two states have the same behavior in terms of transitions in the automaton, so they can be merged into a single state. This yields the SAM shown in the figure. The following discussion extends this idea of merging states to all cases, showing that as long as states are merged properly, the resulting SAM has only $O(n)$ states and transitions.

## Linear-Time Construction Algorithm

Before describing the linear-time algorithm for constructing SAM, we need to introduce two concepts that are crucial for understanding the construction process and prove their properties. Among them, the end position $\operatorname{endpos}$ defines the states in SAM (i.e., gives the necessary and sufficient conditions for merging states), while the suffix link $\operatorname{link}$ is simply the natural counterpart of the [failure pointer](./ac-automaton.md#failure-pointer) in AC automaton in SAM.

### End Position `endpos`

Consider any non-empty substring $t$ of string $s$, and denote by $\operatorname{endpos}(t)$ the set of all ending positions of $t$ in string $s$ (assuming character indices in the string start from zero). For example, for string $\texttt{abcbc}$, we have $\operatorname{endpos}(\texttt{bc})=\{2,4\}$.

The end positions of two substrings $t_1$ and $t_2$ may be exactly the same: $\operatorname{endpos}(t_1)=\operatorname{endpos}(t_2)$. This defines an equivalence relation among substrings of string $s$. All non-empty substrings of $s$ can be divided into several **equivalence classes** based on their end position sets $\operatorname{endpos}$.

A fact is that each such equivalence class corresponds to a state of SAM[^state-endpos]. That is, as long as two substrings have the same end positions, their paths in SAM correspond to the same state. In other words, each non-initial state in SAM corresponds to one or more non-empty substrings with the same $\operatorname{endpos}$. In summary, states in SAM are all equivalence classes of non-empty substrings, plus the initial state.

For now, we accept this fact and will introduce the algorithm for constructing SAM based on it. We will also show that SAM satisfies all properties except minimality; the minimality can be derived from the [Myhill–Nerode theorem](../misc/fsm.md#myhill-nerode-theorem).

From the values of $\operatorname{endpos}$ we can derive some important conclusions that explain the relationship between different substrings corresponding to the same state.

???+ note "Lemma 1"
    For two non-empty substrings $u$ and $w$ of string $s$ (assuming $|u|\le |w|$), $\operatorname{endpos}(u)=\operatorname{endpos}(w)$ if and only if every occurrence of $u$ in $s$ exists as a suffix of $w$.

??? note "Proof"
    The lemma is obvious. If $u$ and $w$ have the same $\operatorname{endpos}$, then $u$ is a suffix of $w$, and in $s$ it only appears as a suffix of $w$. Conversely, by definition, if $u$ is a suffix of $w$ and appears only as a suffix of $w$ in $s$, then the two substrings have the same $\operatorname{endpos}$.

???+ note "Lemma 2"
    Consider two non-empty substrings $u$ and $w$ (assuming $|u|\le |w|$). Then either $\operatorname{endpos}(u)\cap \operatorname{endpos}(w)=\varnothing$, or $\operatorname{endpos}(w)\subseteq \operatorname{endpos}(u)$, depending on whether $u$ is a suffix of $w$:
    
    $$
    \begin{cases}
    \operatorname{endpos}(w) \subseteq \operatorname{endpos}(u), & \text{if } u \text{ is a suffix of } w, \\
    \operatorname{endpos}(w) \cap \operatorname{endpos}(u) = \varnothing, & \text{otherwise}.
    \end{cases}
    $$

??? note "Proof"
    If the sets $\operatorname{endpos}(u)$ and $\operatorname{endpos}(w)$ have at least one common element, then since strings $u$ and $w$ end at the same position, $u$ is a suffix of $w$. Therefore, at every occurrence of $w$, substring $u$ also occurs. Hence $\operatorname{endpos}(w)\subseteq \operatorname{endpos}(u)$.

???+ note "Lemma 3"
    Consider an equivalence class of substrings with the same $\operatorname{endpos}$, and sort all substrings in the class in non-increasing order of length. Then no substring is longer than its predecessor, and at the same time each substring is a suffix of its predecessor. In other words, for any two substrings in the same equivalence class, the shorter one is a suffix of the longer one, and the lengths of substrings in this equivalence class form a continuous interval, taking all integer values in some range.

??? note "Proof"
    If the equivalence class contains only one substring, the lemma obviously holds. Now we discuss equivalence classes with more than one element.

    By Lemma 1, among two different strings with the same $\operatorname{endpos}$, one must be longer, and the shorter one is always a proper suffix of the longer one. That is, there are no strings of equal length in the equivalence class.

    Let $w$ be the longest string in the equivalence class, and $u$ be the shortest. By Lemma 1, string $u$ is a proper suffix of string $w$. Now consider any suffix of $w$ with length in the range $[|u|,|w|]$. It is easy to see that this suffix is also in the same equivalence class, because this suffix can only exist in string $s$ as a suffix of $w$ (this is because the shorter suffix $u$ appears in $s$ only as a suffix of $w$). Therefore, by Lemma 1, this suffix has the same $\operatorname{endpos}$ as string $w$.

    In short, substrings corresponding to the same state have different lengths that form a consecutive set of natural numbers, where the shorter ones are always suffixes of the longer ones.

### Suffix Link `link`

Consider some state $v\neq t_0$ in SAM. We already know that state $v$ corresponds to an equivalence class of substrings with the same $\operatorname{endpos}$. If we define $w$ as the longest among these strings, then all other strings are suffixes of $w$.

We also know that the first few suffixes of string $w$ (considered in decreasing order of length) are all contained in this equivalence class, and other suffixes (at least one — the empty suffix) are in other equivalence classes. Let $t$ be the longest among the other suffixes, and connect the suffix link of $v$ to $t$.

In other words, the **suffix link** $\operatorname{link}(v)$ of $v$ connects to the state corresponding to the longest suffix of $w$ whose $\operatorname{endpos}$ set is different from $w$, which is also the longest suffix of $w$ that appears more frequently in $s$ than $w$.

For convenience, we stipulate that the equivalence class corresponding to the initial state $t_0$ contains only the empty string, and $\operatorname{endpos}(t_0)=\{-1,0,\ldots,|S|-1\}$.

???+ note "Lemma 4"
    All suffix links form a tree with root $t_0$.

??? note "Proof"
    Consider any state $v\neq t_0$. The state connected to by its suffix link $\operatorname{link}(v)$ corresponds to a strictly shorter string (by definition of suffix link and Lemma 3). Therefore, by following suffix links, we can always reach the initial state $t_0$ corresponding to the empty string.

???+ note "Lemma 5"
    The tree constructed with $\operatorname{endpos}$ sets as nodes and set inclusion as edges (i.e., each child's $\operatorname{endpos}$ set is contained in its parent's $\operatorname{endpos}$ set) is the same as the tree constructed from suffix links $\operatorname{link}$.

??? note "Proof"
    By Lemma 2, any two $\operatorname{endpos}$ sets in SAM form a tree (because two sets either have no intersection or one is a subset of the other).

    Now consider any state $v\neq t_0$ and its suffix link $\operatorname{link}(v)$. By the definition of suffix link and Lemma 2, we can obtain
    
    $$
    \operatorname{endpos}(v)\subsetneq \operatorname{endpos}(\operatorname{link}(v)).
    $$
    
    Note that it should be $\subsetneq$ rather than $\subseteq$, because if $\operatorname{endpos}(v)=\operatorname{endpos}(\operatorname{link}(v))$, then $v$ and $\operatorname{link}(v)$ should have been merged into one state.

    Combining with the previous lemmas: the tree formed by suffix links is essentially a tree formed by $\operatorname{endpos}$ sets.

    Below is an **example** of the suffix link tree generated when constructing the SAM for string $\texttt{abcbc}$, with nodes labeled by the longest substring in their equivalence class.

![](./images/SAM/SA_suffix_links.svg]

Having some understanding of the suffix automaton from the diagrams will be helpful for understanding its construction algorithm and applications below.

???+ example "Explanation of the Diagram"
    -   There exists a longest path on the SAM whose label is exactly the string $\texttt{abcbc}$ itself. This path starts from the initial state, and each state it passes corresponds to a prefix of string $\texttt{abcbc}$ ($\varnothing,\texttt{a},\texttt{ab},\texttt{abc},\texttt{abcb},\texttt{abcbc}$). These states are crucial in later [applications](#suffix-link-tree).
    -   The suffix link tree can be seen as the result of "compressing" the paths obtained by moving these "prefix states" along suffix links to the root (i.e., the initial state).
        
        -   Along each path, the set of strings corresponding to nodes forms a partition of all suffixes of the corresponding prefix. For example, the path of the state labeled $\texttt{abcbc}$ moving along suffix links to the root is $\texttt{abcbc}\rightarrow\texttt{bc}\rightarrow\varnothing$. Among them, state $\texttt{abcbc}$ actually corresponds to the string set $\{\texttt{abcbc},\texttt{bcbc},\texttt{cbc}\}$, state $\texttt{bc}$ corresponds to the string set $\{\texttt{bc},\texttt{c}\}$, and state $\varnothing$ corresponds to the empty string.
        -   Different paths may share the same node, which is why there is "compression". For example, paths $\texttt{abc}\rightarrow\texttt{bc}\rightarrow\varnothing$ and $\texttt{abcbc}\rightarrow\texttt{bc}\rightarrow\varnothing$ both share node $\texttt{bc}$. This is because $\operatorname{endpos}(\texttt{bc})=\{2,4\}$, and the string $\texttt{bc}$ ending at position $2$ is preceded by character $\texttt{a}$, while the string $\texttt{bc}$ ending at position $4$ is preceded by character $\texttt{c}$. Therefore, when adding characters in front (i.e., moving against suffix links), the end position set (i.e., the state) splits.
        -   The suffix link tree only needs to reasonably "compress" these suffix paths together, without considering other nodes. This is because all substrings are suffixes of some prefix, so they must appear in some such path. The construction algorithm below essentially adds characters one by one, and for each newly added prefix, constructs such a suffix path and "compresses" it into the existing paths (i.e., not reconstructing already existing states and transitions).
        -   Terminal states are exactly all nodes on the suffix path containing string $\texttt{abcbc}$ itself.
    -   Transitions arriving at the same state must have the same label, and the starting points of these transitions must lie on some (continuous) path on the suffix link tree. For example, there are two states that have transitions to state $\texttt{abcb}$: $\texttt{abc}$ and $\texttt{bc}$. They lie on the path $\texttt{abc}\rightarrow\texttt{bc}$ on the suffix tree. Note that they correspond to string sets $\{\texttt{abc}\}$ and $\{\texttt{bc},\texttt{c}\}$ respectively, and adding character $\texttt{b}$ after these strings yields the string set $\{\texttt{abcb},\texttt{bcb},\texttt{cb}\}$ corresponding to state $\texttt{abcb}$.
        
        -   After adding a character, different states may transition to the same state because the newly added character makes it more difficult for the end position to increase.
    -   On the suffix link tree, each node's $\operatorname{endpos}$ set is the union of its children's $\operatorname{endpos}$ sets, plus possibly one more position. This new position exists if and only if the node corresponds exactly to a prefix of the original string ending at that position. In the diagram, since non-root and non-leaf nodes of the suffix link tree do not correspond to prefixes of string $\texttt{abcbc}$, such a situation does not occur.

The suffix automaton stores information about all substrings of a string. This can be understood from two perspectives:

-   SAM itself can be seen as a compressed version of the AC automaton of all suffixes of a string. Therefore, it stores information about all prefixes of all suffixes of the string, which is equivalent to storing information about all substrings.
-   The suffix link tree of SAM can be seen as a compressed version of the suffix paths of all prefixes of a string. Therefore, it stores information about all suffixes of all prefixes, which is also equivalent to storing information about all substrings.

Both perspectives are useful when dealing with different problems.

### Summary

Before discussing the algorithm itself, let's summarize the previous content and introduce some auxiliary notation.

-   Substrings of $s$ can be divided into multiple equivalence classes based on their end position sets $\operatorname{endpos}$.

-   SAM consists of the initial state $t_0$ and one state for each $\operatorname{endpos}$ equivalence class (of non-empty substrings).

-   Each state $v$ matches one or more substrings. We denote $\operatorname{longest}(v)$ as the longest such string, and $\operatorname{len}(v)$ as its length. Similarly, denote $\operatorname{shortest}(v)$ as the shortest substring, with length $\operatorname{minlen}(v)$. Then all strings corresponding to this state are distinct suffixes of $\operatorname{longest}(v)$, and their lengths exactly cover every integer in the interval $[\operatorname{minlen}(v),\operatorname{len}(v)]$.

-   For any state $v\neq t_0$, the suffix link is defined as an edge connecting to the suffix of $\operatorname{longest}(v)$ with length $\operatorname{minlen}(v)-1$. Suffix links starting from the root $t_0$ form a tree. This tree also represents the inclusion relationships between $\operatorname{endpos}$ sets.

-   For any state $v\neq t_0$, $\operatorname{minlen}(v)$ can be expressed using the suffix link $\operatorname{link}(v)$:

    $$
    \operatorname{minlen}(v)=\operatorname{len}(\operatorname{link}(v))+1.
    $$

-   If we traverse from any state $v_0$ following suffix links, we will always reach the initial state $t_0$. In this case we obtain a sequence of disjoint intervals $[\operatorname{minlen}(v_i),\operatorname{len}(v_i)]$, and their union forms the continuous interval $[0,\operatorname{len}(v_0)]$.

### Algorithm

Now we can discuss the algorithm for constructing SAM. This algorithm is **online**: we can add characters to the string one by one, and maintain the SAM at each step.

Before discussing the detailed implementation, let's first get an intuitive understanding of what changes might occur in the SAM when adding a new character $c$.

???+ note "Understanding the Incremental Construction Process"
    Based on the SAM of string $s$, we can construct the SAM of string $s+c$. According to the previous explanation of the diagram, we only need to construct the suffix path of the newly added prefix (i.e., $s+c$) and compress it onto the existing paths. Moreover, according to the previous description, nodes on the new suffix path can all be reached from nodes on suffix paths of the original string $s$ via character $c$.

    First, let's consider what form the suffix path of the original string $s$ might have before adding the new character $c$, and how it might transition via character $c$. The most general case is shown in the following diagram:
    
    ![](./images/SAM/sam-suffix-path-1.svg]
    
    In the diagram, the suffix path of the original string $s$ is $p_0\rightarrow p_1\rightarrow\cdots\rightarrow p_6\rightarrow t_0$, with suffix links shown as red arrows. Some nodes (i.e., $p_2\sim p_6$) already have transitions via character $c$; since adding the same character to a continuous suffix string also yields a continuous suffix string, these transitions form another suffix path $q_1\rightarrow q_2\rightarrow q_3\rightarrow t_0$. At this point, there are two observations:
    
    -   On the suffix path of the original string $s$, the nodes without transitions via $c$ must be the initial few nodes. Starting from some node (like $p_2$ in the diagram), if there exists a transition via $c$, then all subsequent nodes also have transitions via $c$.
        
        **Explanation**: Let $s_2=\operatorname{longest}(p_2)$. All subsequent nodes correspond to suffixes of $s_2$, so if $s_2+c$ also appears in $s$, then adding $c$ to suffixes of $s_2$ also appears in $s$. Therefore, these nodes all have transitions via $c$.
    -   Although the nodes that can reach node $q_i$ via character $c$ must form a continuous segment on the suffix link tree, this continuous segment may not entirely lie on the suffix path from $p_0$ to the root. In particular, only the initial few nodes in the continuous segment corresponding to the first node $q_1$ **might** not be on this suffix path. For example, node $q_1$ in the diagram corresponds to nodes $p_1'\rightarrow p_2\rightarrow p_3$, where $p_1'$ is not on the suffix path of $p_0$.
        
        **Explanation**: Let $s_2=\operatorname{longest}(p_2)$, then $s_2+c$ corresponds to $q_1$, but clearly $s_2+c\neq\operatorname{longest}(q_1)$ in the diagram, because the latter is $\operatorname{longest}(p'_1)+c$. This shows that some strings corresponding to $q_1$ cannot be reached from $s_2$ and its suffixes via transitions. Conversely, strings in $q_2$ must be suffixes of $s_2+c$, so removing the trailing $c$ must be a suffix of $s_2$. That is, nodes that transition to $q_2$ via $c$ must lie on the suffix path starting from $p_2$. This is why only some nodes in the initial segment corresponding to $q_1$ might not be on the suffix path of $p_0$.
    
    For this diagram, if we add character $c$ to the end of the original string $s$ and construct the corresponding suffix path, what changes occur? The answer is shown in the following diagram:
    
    ![](./images/SAM/sam-suffix-path-2.svg]
    
    Because node $q_0$ is reached from node $p_0$ (corresponding to original string $s$) via character $c$, it corresponds to the new string $s+c$. Therefore, its suffix path $q_0\rightarrow q_1''\rightarrow q_2\rightarrow q_3\rightarrow t_0$ is the newly added suffix path. If a node $p_i$ on the original suffix path already had a transition via $c$, the new suffix path will also pass through the node reached by this transition, so the existing node can be reused. There is exactly one newly created node $q_0$ on the new suffix path, which is used to accept transitions from the initial nodes on the original suffix path that did not have transitions via $c$.
    
    Besides these obvious facts, we can also notice that the original node $q_1$ has undergone a copy, or more precisely, it has split into two nodes $q'_1\rightarrow q_1''$. This is because the new suffix path only partially overlaps with the existing path: among the strings corresponding to the original node $q_1$, only the shorter ones (i.e., those reachable from nodes $p_2$ and $p_3$) appear in the new suffix path, while the longer ones (i.e., those reachable from node $p_1'$) do not appear in the new suffix path. Therefore, the new suffix path can only pass through part of node $q_1$, which must split into two nodes to represent this situation. The same reasoning, explained earlier, shows that nodes $q_2$ and $q_3$ after $q_1$ cannot be reached from nodes not on the suffix path of $p_0$, so all strings corresponding to these nodes appear in the new suffix path and no splitting is needed.
    
    From the perspective of what states represent in SAM, each state is an $\operatorname{endpos}$ set. When extending the string, suppose the newly added end position is $i$. Then the new node $q_0$ corresponds to the end position set $\{i\}$, while the split nodes $q_1'$ and $q_1''$ correspond to sets $\operatorname{endpos}(q_1)$ and $\operatorname{endpos}(q_1)\cup\{i\}$ respectively, and nodes $q_2$ and $q_3$ actually have $i$ added to their original end position sets. That is, although $q_2$ and $q_3$ and their related transitions have not changed, their corresponding $\operatorname{endpos}$ sets have indeed expanded.
    
    The above describes the most complex and general case (i.e., **Case 3** below). In practice, node $p'_1$ may not exist, so no splitting is needed (i.e., **Case 2** below). To determine this case, we only need to check whether $\operatorname{longest}(q_1)=\operatorname{longest}(p_2)+c$, i.e., $\operatorname{len}(q_1)=\operatorname{len}(p_2)+1$. It is also possible that all nodes on the suffix path of $p_0$ have no transitions via $c$. In this case, we only need to create $q_0$ (i.e., **Case 1** below).

Having grasped the idea of adding new suffix paths, let's now discuss the specific steps of incremental construction.

#### Process

To ensure linear space complexity, we will only store the values of $\operatorname{len}$ and $\operatorname{link}$ for each state, along with a transition list for each state. We will not mark terminal states (but we will show how to assign these marks after constructing the SAM).

Initially, the SAM contains only one state $t_0$ with index $0$ (other states have indices $1,2,\ldots$). For convenience, for state $t_0$ we set $\operatorname{len}(t_0)=0$, $\operatorname{link}(t_0)=-1$ ($-1$ denotes a virtual state).

Now we only need to implement the process of adding a character $c$ to the current string. The algorithm flow is as follows:

???+ note "SAM Incremental Construction Process"
    -   Let $\textit{last}$ be the state corresponding to the entire string before adding character $c$ (initially we set $\textit{last}=0$, and update $\textit{last}$ at the last step of the algorithm).
    -   Create a new state $\textit{cur}$, and set $\operatorname{len}(\textit{cur}) = \operatorname{len}(\textit{last}) + 1$. At this point, the value of $\operatorname{link}(\textit{cur})$ is still unknown.
    -   Now we perform the following process: starting from state $\textit{last}$, if the current state does not have a transition labeled with character $c$, we add a transition via character $c$ to state $\textit{cur}$, and move the current state along the suffix link. If we encounter a state that already has a transition for character $c$, we stop and mark this state as $p$.
    -   **Case 1**: If we cannot find such a state $p$, we reach the virtual state $-1$. We set $\operatorname{link}(\textit{cur}) = 0$ and exit.
    -   Suppose we have found a state $p$ that can transition via character $c$. We mark the state reached by this transition as $q$. At this point, either $\operatorname{len}(p)+1 = \operatorname{len}(q)$, or $\operatorname{len}(p)+1 < \operatorname{len}(q)$.
    -   **Case 2**: If $\operatorname{len}(p)+1 = \operatorname{len}(q)$, we simply set $\operatorname{link}(\textit{cur}) = q$ and exit.
    -   **Case 3**: Otherwise, it becomes complex and we need to **copy** state $q$: we create a new state $\textit{clone}$, copying all information from $q$ except the value of $\operatorname{len}$ (suffix links and transitions). We set $\operatorname{len}(\textit{clone}) = \operatorname{len}(p)+1$.
        
        After copying, we set the suffix link from $\textit{cur}$ to point to $\textit{clone}$, and also set the suffix link from $q$ to point to $\textit{clone}$.
        
        Finally, we need to walk back along suffix links from state $p$, and for each state that has a transition to state $q$, we reconnect that transition to state $\textit{clone}$.
    -   After processing any of the above three cases, we update the value of $\textit{last}$ to state $\textit{cur}$.

If we also want to know which states are **terminal states** and which are not, we can find all terminal states after constructing the complete SAM for string $s$. To do this, we traverse suffix links starting from the state corresponding to the entire string (stored in variable $\textit{last}$) until we reach the initial state. We mark all states we traverse as terminal states. It is easy to understand that this will accurately mark all suffixes of string $s$, and these states are all terminal states.

Since we only create one or two new states for each character of $s$, the SAM contains only a **linear** number of states. The linear number of transitions in the SAM, as well as the overall linear running time of the algorithm, have not been clearly explained yet; they will be covered later.

#### Explanation

We will explain in detail the details of each step of the algorithm and explain its **correctness**.

???+ note "Detailed Explanation of the Algorithm"
    -   If a transition $(p,q)$ satisfies $\operatorname{len}(p)+1=\operatorname{len}(q)$, we call this transition **continuous**. Otherwise, when $\operatorname{len}(p)+1<\operatorname{len}(q)$, this transition is called **discontinuous**.
        
        As can be seen from the algorithm description, continuous and discontinuous transitions are handled differently in the algorithm. Continuous transitions are fixed and we won't change them. In contrast, when inserting a new character into the string, discontinuous transitions may change (the endpoints of transition edges may change).
    -   To avoid ambiguity, we denote the string before inserting current character $c$ into the SAM as $s$.
    -   The algorithm starts by creating a new state $\textit{cur}$, corresponding to the entire string $s+c$. The reason for creating a new node is clear. At the same time, we also create a new character and a new equivalence class.
    -   After creating a new state, we move from the state $\textit{last}$ corresponding to the entire string $s$ along suffix links. For each state we pass through, we try to add a transition via character $c$ to the new state $\textit{cur}$.
        
        However, we can only add transitions that don't conflict with existing ones. Therefore, as soon as we find an existing transition for $c$, we must stop.
    -   The simplest case is that we reach the virtual state $-1$. This means we have added transitions via $c$ for all suffixes of $s$. This also means character $c$ never appeared in string $s$. Therefore, the suffix link of $\textit{cur}$ is state $0$.
    -   In the second case, we find an existing transition $(p,q)$. This means we are trying to add a **already existing** string $x+c$ to the automaton (where $x$ is a suffix of $s$, and string $x+c$ has already appeared as a substring of $s$). Because we assume the construction of the automaton for string $s$ is correct, we should not add a new transition here.
        
        However, the difficulty is: to which state should the suffix link from state $\textit{cur}$ connect? We want to connect the suffix link to a state whose longest string is exactly $x+c$, i.e., the $\operatorname{len}$ of this state should be $\operatorname{len}(p)+1$. However, such a state may not exist, i.e., $\operatorname{len}(q) > \operatorname{len}(p)+1$. In this case, we must create such a state by splitting state $q$.
    -   Of course, if transition $(p,\,q)$ is continuous, then $\operatorname{len}(q)=\operatorname{len}(p)+1$. In this case, everything is simple. We only need to point the suffix link of $\textit{cur}$ to state $q$.
    -   Otherwise, the transition is discontinuous, i.e., $\operatorname{len}(q) > \operatorname{len}(p)+1$. This means state $q$ corresponds not only to the suffix $s+c$ of length $\operatorname{len}(p)+1$, but also to longer substrings of $s$. We have no choice but to split state $q$ into two substates, where the length of the first substate is $\operatorname{len}(p)+1$.
        
        How do we split a state? We **copy** state $q$, producing a state $\textit{clone}$, and set $\operatorname{len}(\textit{clone}) = \operatorname{len}(p)+1$. Since we don't want to change paths passing through $q$, we copy all transitions from $q$ to $\textit{clone}$. We also set the suffix link from $\textit{clone}$ to be the same as $q$'s suffix link, and set $q$'s suffix link to $\textit{clone}$.
        
        After splitting the state, we set the suffix link from $\textit{cur}$ to $\textit{clone}$.
        
        The final step is to reconnect some transitions that originally pointed to $q$ to point to $\textit{clone}$. Which transitions need to be modified? It suffices to reconnect transitions corresponding to all strings $w+c$ (where $w$ is the longest string corresponding to state $p$). That is, we need to continue moving along suffix links from node $p$ until we reach the virtual state $-1$, or the current state's transition via $c$ no longer points to state $q$.

### Linear Time Complexity

We assume the alphabet size is a **constant**, i.e., each operation of searching for a transition, adding a transition, and finding the next transition for a character takes $O(1)$ time. If we store each node's transitions in a length $|\Sigma|$ array (for fast lookup of transitions by label) and a dynamic list (for fast traversal of all available transitions), trading space for time, then the algorithm's time complexity[^time-complexity] is $O(n)$, and space complexity is $O(n|\Sigma|)$.

??? note "Proof"
    If we consider the various parts of the algorithm, there are three places where the time complexity is not obviously linear:
    
    -   The first is traversing all suffix links of state $\textit{last}$ and adding transitions for character $c$.
    -   The second is the process of copying transitions when state $q$ is copied to a new state $\textit{clone}$.
    -   The third is the process of modifying transitions pointing to $q$ and reconnecting them to $\textit{clone}$.
    
    We use the fact that the size of SAM (number of states and transitions) is **linear** (the proof of linearity for states is the algorithm itself, and the proof of linearity for transitions will be given after implementing the algorithm).
    
    Therefore, the total complexity of the **first and second** parts is obviously linear, because each single operation on average adds only one new transition to the automaton.
    
    We still need to estimate the total complexity of the **third** part. We reconnect transitions originally pointing to $q$ to $\textit{clone}$. Let $v = \operatorname{longest}(p)$, which is a suffix of string $s$. With each iteration, the length of $v$ decreases, so the starting position of $v$ as a suffix of $s$ must move backward. Therefore, the number of times $p$ moves along suffix links in the loop does not exceed the distance by which the starting position of $v$ as a suffix of $s$ moves backward. Because $p$ must move backward at least once to terminate the loop, and $p$ is at least the result of moving along suffix links from $\textit{last}$ once, when the loop terminates, the starting position of $v$ as a suffix of $s$ is not earlier than the string $\operatorname{longest}(\operatorname{link}(\operatorname{link}(\textit{last})))$. Moreover, when the loop terminates, the starting position of $v$ as a suffix of $s$ is exactly the starting position of $v+c$ as a suffix of $s+c$. As a suffix of $s+c$, the string $v+c$ is exactly $\operatorname{longest}(\operatorname{link}(\operatorname{link}(\textit{cur})))$. Because $\textit{cur}$ is the updated value of $\textit{last}$, the number of iterations in the loop does not exceed the distance by which $\operatorname{longest}(\operatorname{link}(\operatorname{link}(\textit{last})))$ moves backward as a suffix of the current string, plus one (the number of moves required to terminate the loop).
    
    Since the position of $\operatorname{longest}(\operatorname{link}(\operatorname{link}(\textit{last})))$ as a suffix of the current string monotonically increases[^monotone-loc] during the entire SAM construction, its total movement distance does not exceed $n$. This shows that the number of iterations in the loop that modifies transitions pointing to $q$ does not exceed $2n$. This is exactly what we needed to prove.

Of course, if the alphabet size is not constant, the time complexity of SAM is not linear. Transitions from a node need to be stored in a balanced tree that supports fast query and insertion. Therefore, if we denote $\Sigma$ as the alphabet and $|\Sigma|$ as the alphabet size, the asymptotic time complexity of the algorithm is $O(n\log|\Sigma|)$, and space complexity is $O(n)$.

### Implementation

First, we implement a data structure that stores all information of a transition. If needed, you can add a terminal marker here, or some other information. We will use a `map` to store the transition list, allowing us to process the entire string with $O(n)$ space complexity and $O(n\log|\Sigma|)$ time complexity. Of course, when the alphabet size is a small constant $K$ (e.g., 26), declaring `next` as `int[K]` is more convenient.

```cpp
struct state {
  int len, link;
  std::map<char, int> next;
};
```

The SAM itself will be stored in an array of `state` structures. We keep track of the current automaton size `sz` and the variable `last`, which corresponds to the state for the entire current string.

```cpp
constexpr int MAXLEN = 100000;
state st[MAXLEN * 2];
int sz, last;
```

We define a function to initialize the SAM (create a SAM with only the initial state).

```cpp
void sam_init() {
  st[0].len = 0;
  st[0].link = -1;
  sz++;
  last = 0;
}
```

Finally, we give the implementation of the main function: adding a character to the end of the current line, building the automaton accordingly.

???+ note "Implementation"
    ```cpp
    void sam_extend(char c) {
      int cur = sz++;
      st[cur].len = st[last].len + 1;
      int p = last;
      while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
      }
      if (p == -1) {
        st[cur].link = 0;
      } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
          st[cur].link = q;
        } else {
          int clone = sz++;
          st[clone].len = st[p].len + 1;
          st[clone].next = st[q].next;
          st[clone].link = st[q].link;
          while (p != -1 && st[p].next[c] == q) {
            st[p].next[c] = clone;
            p = st[p].link;
          }
          st[q].link = st[cur].link = clone;
        }
      }
      last = cur;
    }
    ```

As mentioned earlier, if you trade memory for time (with space complexity $O(n|\Sigma|)$, where $|\Sigma|$ is the alphabet size), you can construct SAM for any alphabet size in $O(n)$ time[^time-complexity]. However, this requires storing an array of size $|\Sigma|$ for each state (for quickly finding transitions by character) and a list of all available transitions (for quickly traversing all available transitions).

## More Properties

### Number of States

For a string $s$ of length $n$, the number of states in its SAM **does not exceed** $2n-1$ (assuming $n\ge 2$).

??? note "Proof"
    The algorithm itself proves this conclusion. Initially, the automaton contains one state. Only one node is created in the first and second iterations. In the remaining $n-2$ steps, at most 2 states are created per step.
    
    However, we can also **prove** this estimate **without using the algorithm**. Recall that the number of states equals the number of distinct $\operatorname{endpos}$ sets. These $\operatorname{endpos}$ sets form a tree (the parent's $\operatorname{endpos}$ set contains the child's $\operatorname{endpos}$ set). Consider slightly modifying this tree: whenever it has an internal node with only one child (which means the child's set misses at least one position from its parent's set), we create a set containing these missed positions as its child. Eventually, we obtain a tree where every internal node has degree greater than one, and the number of leaves does not exceed $n$. Such a tree has at most $2n-1$ nodes. Therefore, the original number of distinct $\operatorname{endpos}$ sets does not exceed $2n-1$.
    
    The string $\texttt{abbb} \cdots \texttt{bbb}$ reaches this upper bound for the number of states: starting from the third iteration, the algorithm splits a state in each iteration, eventually producing exactly $2n-1$ states.

### Number of Transitions

For a string $s$ of length $n$, the number of transitions in its SAM **does not exceed** $3n-4$ (assuming $n\ge 3$).

??? note "Proof"
    First, we estimate the number of continuous transitions. Consider the spanning tree formed by the longest paths from state $t_0$ to all states in the automaton. The spanning tree contains only continuous edges, so its number is less than the number of states, i.e., the number of edges does not exceed $2n-2$.
    
    Now we estimate the number of discontinuous transitions. Let the current discontinuous transition be $(p,\,q)$ with character $c$. We take its corresponding string $u+c+w$, where string $u$ corresponds to the longest path from the initial state to $p$, and $w$ corresponds to the longest path from $q$ to any terminal state. On one hand, each incomplete string corresponds to a different string of the form $u+c+w$ (because strings $u$ and $w$ consist only of complete transitions). On the other hand, by the definition of terminal states, each string of the form $u+c+w$ is a suffix of the entire string $s$. Since $s$ has only $n$ non-empty suffixes, and strings of the form $u+c+w$ do not contain $s$ (because the entire string contains only complete transitions), the total number of discontinuous transitions does not exceed $n-1$.
    
    Adding these two estimates, we get the upper bound $3n-3$. However, the maximum number of states can only occur in cases like $\texttt{abbb} \cdots \texttt{bbb}$, and at that time the number of transitions is clearly less than $3n-3$.
    
    Therefore, we can obtain a tighter upper bound for the number of transitions in SAM: $3n-4$. The string $\texttt{abbb} \cdots \texttt{bbbc}$ reaches this upper bound.

### Suffix Link Tree

Although constructing SAM is to obtain information about its states and transitions, the suffix links $\operatorname{link}$ recorded during construction and the length $\operatorname{len}$ of the longest substring corresponding to each state are often more important in applications than SAM's transitions, and can even be used without the transitions.

During the construction of SAM, we need to update the value of state $\textit{last}$. It corresponds to the string before (and after) each character is added, which is all prefixes of the entire string $s$. Let the state corresponding to the $i$-th prefix be $v_i$, giving us a total of $n$ states $v_0, v_1, \cdots, v_{n-1}$. Additionally, we define the initial state $t_0$ as $v_{-1}$, corresponding to the empty prefix. These states are temporarily called "prefix nodes".

As mentioned in Lemma 4, all states and all suffix links form a rooted tree with root $t_0$. This tree is also called the **suffix link tree** (domestic OI players often call it the **parent tree**). It records information about all suffixes of all prefixes of the string, i.e., information about all substrings.

The suffix link tree has the following properties:

-   The string corresponding to an ancestor node is always a suffix of the string corresponding to a descendant node.
-   The $\operatorname{endpos}$ set at each node is the set of indices $i$ of all "prefix nodes" $v_i$ in its subtree.
-   The $\operatorname{endpos}$ set of an ancestor node in the suffix link tree always strictly contains the $\operatorname{endpos}$ set of a descendant node.
-   The value of $\operatorname{len}$ at each node is the length of the longest common suffix of all prefixes corresponding to "prefix nodes" $v_i$ in its subtree.
-   Except for the root node $t_0$, the number of distinct substrings corresponding to each node is its $\operatorname{len}$ value minus its parent's $\operatorname{len}$ value, i.e., $\operatorname{len}(v)-\operatorname{len}(\operatorname{link}(v))$.

These properties have many applications. For example, the longest common suffix of the $i$-th prefix and the $j$-th prefix corresponds to the longest string corresponding to the LCA of $v_i$ and $v_j$.

Finally, the suffix link tree built for string $s$ has the same structure as the [suffix tree](./suffix-tree.md) built for its reverse $s_R$. This is often used for offline construction of suffix trees.

## Applications

Now we look at some problems that can be solved using SAM. For simplicity, we assume the alphabet size $k$ is a constant. This allows us to consider adding a character and traversal as constant-time operations.

### Checking if a String Occurs

???+ example "Problem"
    Given a text string $T$ and multiple pattern strings $P$, check whether string $P$ occurs as a substring of $T$.

??? note "Solution"
    We construct a suffix automaton for text string $T$ in $O(|T|)$ time. To check whether pattern $P$ occurs in $T$, we start from $t_0$ and follow transitions (edges) according to the characters of $P$. If at some point we cannot follow a transition, then pattern $P$ is not a substring of $T$. If we can process the entire string $P$ in this way, then the pattern occurs in $T$.
    
    For each string $P$, the algorithm's time complexity is $O(|P|)$. Moreover, this algorithm also finds the longest prefix of pattern $P$ that appears in the text string.

### Number of Distinct Substrings

???+ example "Problem"
    Given a string $S$, calculate the number of distinct substrings.

??? note "Solution 1"
    Construct a suffix automaton for string $S$.
    
    Each substring of $S$ corresponds to some path in the automaton. Therefore, the number of distinct substrings equals the number of distinct paths starting from $t_0$.
    
    Since SAM is a directed acyclic graph, the number of distinct paths can be calculated by dynamic programming. Let $d_v$ be the number of paths starting from state $v$ (including the path of length zero). Then we have the following recurrence:
    
    $$
    d_{v}=1+\sum_{w:(v,w,c)\in DAWG}d_{w}
    $$
    
    That is, $d_v$ can be expressed as the sum of $d_w$ over all transitions $(v,w,c)$ in the DAWG, where the triple $(v,w,c)$ indicates there exists a transition from $v$ via $c$ to $w$ in the suffix automaton.
    
    Therefore, the number of distinct substrings is $d_{t_0} - 1$ (because we need to exclude the empty substring).
    
    Total time complexity: $O(|S|)$.

??? note "Solution 2"
    Another method is to use the information of the suffix link tree after constructing the suffix automaton. The number of substrings corresponding to each node is $\operatorname{len}(v)-\operatorname{len}(\operatorname{link}(v))$. Summing over all nodes in the automaton gives the answer.
    
    Total time complexity is still: $O(|S|)$.

Example problems: [Template: Suffix Automaton](https://www.luogu.com.cn/problem/P3804), [SDOI2016 Generate Spell](https://loj.ac/problem/2033)

### Total Length of All Distinct Substrings

???+ example "Problem"
    Given a string $S$, calculate the total length of all distinct substrings.

??? note "Solution 1"
    This problem is similar to the previous one, but now we need to consider two parts in dynamic programming: the number of distinct substrings $d_v$ and their total length $ans_v$.
    
    We have already introduced how to calculate $d_v$ in the previous problem. The value of $ans_v$ can be calculated by the following recurrence:
    
    $$
    ans_{v}=\sum_{w:(v,w,c)\in DAWG}d_{w}+ans_{w}
    $$
    
    We take the answer for each adjacent node $w$, and add $d_w$ (because all substrings starting from state $v$ gain one character).
    
    The algorithm's time complexity is still $O(|S|)$.

??? note "Solution 2"
    We can also use the information of the suffix link tree. The total length of all suffixes of the longest substring corresponding to each node is
    
    $$
    \dfrac{\operatorname{len}(v)\times (\operatorname{len}(v)+1)}{2},
    $$
    
    and subtracting the corresponding value of its $\operatorname{link}$ node gives the net contribution of that node. Summing over all nodes in the automaton gives the answer.
    
    Total time complexity is still: $O(|S|)$.

### K-th Lexicographically Largest Substring

???+ example "Problem"
    Given a string $S$. Multiple queries, each query gives a number $K_i$, find the $K_i$-th lexicographically largest substring of $S$.

??? note "Solution"
    The solution approach can be developed from the solutions to the previous two problems. The $K$-th lexicographically largest substring corresponds to the $K$-th lexicographically largest path in SAM. Therefore, after calculating the number of paths for each state, we can easily find the $K$-th largest path starting from the root of SAM.
    
    Preprocessing time complexity is $O(|S|)$, and single query complexity is $O(|ans|\cdot|\Sigma|)$ (where $ans$ is the answer to the query, and $|\Sigma|$ is the size of the alphabet).

??? info "Note"
    Although this problem is a classic SAM problem, it is actually most conveniently solved using suffix arrays due to the lexicographic nature.

Example problems: [SPOJ - SUBLEX](https://www.spoj.com/problems/SUBLEX/), [TJOI2015 String Theory](https://loj.ac/problem/2102)

### Minimum Cyclic Shift

???+ example "Problem"
    Given a string $S$. Find the lexicographically smallest cyclic shift.

??? note "Solution"
    It is easy to find that string $S+S$ contains all cyclic shifts of string $S$ as substrings.
    
    Therefore, the problem reduces to finding the shortest path of length $|S|$ on the suffix automaton corresponding to $S+S$. This can be done in a straightforward way: starting from the initial state, greedily visit the smallest character.
    
    Total time complexity: $O(|S|)$.

### Number of Occurrences

???+ example "Problem"
    For a given text string $T$, there are multiple queries, each query gives a pattern string $P$, and we need to answer how many times pattern $P$ occurs as a substring in string $T$.

??? note "Solution 1"
    Using the information of the suffix link tree, we can perform a DFS to preprocess the size of each node's $\operatorname{endpos}$ set.
    
    All "prefix nodes" have initial set size 1, and non-"prefix nodes" have initial set size 0. Then, when backtracking from bottom to top along suffix links, we add each parent node's set size to all its children's set sizes (don't forget the parent node's own initial value). The value obtained at each node is the size of its $\operatorname{endpos}$ set. The reason we can directly sum the set sizes of different children is that the same $v_i$ appears in only one subtree, so there is no double counting when summing.
    
    For a query, we find the node corresponding to pattern $P$ on the automaton. If it exists, the answer is the size of that node's $\operatorname{endpos}$ set; if it doesn't exist, the answer is 0.
    
    Preprocessing time complexity: $O(|T|)$. Single query time complexity: $O(|P|)$.

??? note "Solution 2"
    Construct a suffix automaton for text string $T$.
    
    Next, perform preprocessing: for each state $v$ in the automaton, preprocess $cnt_v$ to equal the size of set $\operatorname{endpos}(v)$. In fact, all substrings corresponding to the same state $v$ occur the same number of times in text string $T$, which is equivalent to the number of positions in the set $\operatorname{endpos}$.
    
    However, we cannot explicitly construct the set $\operatorname{endpos}$, so we only consider their size $cnt$.
    
    To calculate these values, we perform the following operations. For each state, if it was not created by cloning (and it is not the initial state $t_0$), we initialize its $cnt$ to 1. Then we traverse all states in descending order of $\operatorname{len}$, and add the current value of $cnt_v$ to the state pointed to by its suffix link:
    
    $$
    cnt_{\operatorname{link}(v)}+=cnt_{v}
    $$
    
    This way, the answer for each state is correct.
    
    Why is this correct? There are exactly $|T|$ states that are not obtained by cloning, and the first $i$ of them are created when inserting the first $i$ characters. Therefore, for each such state, we calculate the number of positions they correspond to when they are processed. Thus we initially set the $cnt$ value of these states to 1, and the $cnt$ values of other states to 0.
    
    Next, for each $v$, we perform the following operation: $cnt_{\operatorname{link}(v)}+=cnt_{v}$. The meaning behind this is: if a string $v$ occurs $cnt_v$ times, then all its suffixes also end at exactly the same places, i.e., they also occur $cnt_v$ times.
    
    Why don't we double-count (i.e., count some positions twice) in this process? Because we only add a state's positions to **one** other state, so a state cannot have its positions repeatedly pointed to another state in two different ways.
    
    Therefore, we can calculate the $cnt$ values for all states in $O(|T|)$ time.
    
    To answer a query, we just need to look up the value $cnt_t$, where $t$ is the state corresponding to the pattern string. If the pattern does not exist, the answer is 0. Single query time complexity: $O(|P|)$.

### First Occurrence Position

???+ example "Problem"
    Given a text string $T$, multiple queries. Each query asks for the position where string $P$ first occurs in string $T$ (the starting position of $P$).

??? note "Solution 1"
    Using the information of the suffix link tree, we can perform a DFS to preprocess the minimum value in each node's $\operatorname{endpos}$ set.
    
    All "prefix nodes" $v_i$ have initial value $i$, and non-"prefix nodes" have initial value $\infty$. Then, when backtracking from bottom to top along suffix links, each parent node's value is compared with all its children's values, taking the minimum (don't forget the parent node's own initial value). The value obtained at each node is the minimum value in its $\operatorname{endpos}$ set.
    
    For a query, we find the node corresponding to pattern $P$ on the automaton. If it exists, the answer is that node's value minus $|P|-1$; if it doesn't exist, the answer does not exist.
    
    Preprocessing time complexity: $O(|T|)$. Single query time complexity: $O(|P|)$.

??? note "Solution 2"
    We construct a suffix automaton. We preprocess positions $\operatorname{firstpos}$ for all states in the SAM. That is, for each state $v$, we want to find the position of the first occurrence of this state's end position $\operatorname{firstpos}[v]$. In other words, we want to first find the smallest element in each $\operatorname{endpos}$ set (obviously we cannot explicitly maintain all $\operatorname{endpos}$ sets).
    
    To maintain these $\operatorname{firstpos}$ positions, we extend the function `sam_extend()`. When we create a new state $\textit{cur}$, we set:
    
    $$
    \operatorname{firstpos}(\textit{cur})=\operatorname{len}(\textit{cur})-1.
    $$
    
    When we copy node $q$ to $\textit{clone}$, we set:
    
    $$
    \operatorname{firstpos}(\textit{clone})=\operatorname{firstpos}(q).
    $$
    
    (Because the only other option, $\operatorname{firstpos}(\textit{cur})$, is clearly too large).
    
    Then the answer to the query is $\operatorname{firstpos}(t)-\left|P\right|+1$, where $t$ is the state corresponding to string $P$. Single query only takes $O(\left|P\right|)$ time.

### All Occurrence Positions

???+ example "Problem"
    Same as above, but this time we need to query all positions where pattern $P$ occurs in text string $T$.

??? note "Solution 1"
    After finding the node corresponding to pattern $P$, using the information of the suffix link tree, we traverse the subtree. Once we find a terminal node, we output it.
    
    Single query complexity: $O(|P|)+O(\textit{answer}(P))$, where $\textit{answer}(P)$ is the answer to this query. Following the reasoning in the [proof that the number of states is linear](#number-of-states), it can be shown that the subtree size of the suffix link tree does not exceed twice the size of that node's $\operatorname{endpos}$ set, so traversing the subtree has $O(\textit{answer}(P))$ complexity.

??? note "Solution 2"
    We also construct a suffix automaton for text string $T$. Similar to the previous problem, we calculate position $\operatorname{firstpos}$ for all states.
    
    If $t$ is the state corresponding to pattern $P$, then $\operatorname{firstpos}(t)$ is one of the answers. We have already found the state in the automaton corresponding to $P$. What other positions do we need to find? Exactly those corresponding to strings that have $P$ as a suffix. In other words, we need to find all states that can reach state $t$ via suffix links.
    
    To solve this problem, we need to maintain a list of reverse suffix links for each state. The answer to the query contains the $\operatorname{firstpos}$ values of all states that can be found from state $t$ using only reverse suffix links via DFS or BFS.
    
    Preprocessing complexity: $O(|T|)$, single query complexity: $O(|P|+\textit{answer}(P))$.
    
    We will not visit a state twice (because there is only one suffix link pointing to a state, so there are no two different paths pointing to the same state).
    
    We only need to consider two different states that might have the same $\operatorname{firstpos}$ value. This situation only occurs when one state is copied from another. However, this does not affect the complexity analysis. Following the reasoning in the [proof that the number of states is linear](#number-of-states), the total number of states with suffix $P$ does not exceed $2\textit{answer}(P)$.
    
    Moreover, we can remove duplicate positions by not considering the $\operatorname{firstpos}$ values of cloned nodes. In fact, for a state, if it can be reached through the cloned state, it can also be reached through the original state. Therefore, if we record a marker `is_clone` for each state to indicate whether this state was cloned, we can simply ignore cloned states and output the `firstpos` values of all other states.
    
    The following is a rough implementation:
    
    ```cpp
    struct state {
      bool is_clone;
      int first_pos;
      std::vector<int> inv_link;
      // some other variables
    };
    
    // After constructing SAM
    for (int v = 1; v < sz; v++) st[st[v].link].inv_link.push_back(v);
    
    // Output all occurrence positions
    void output_all_occurrences(int v, int P_length) {
      if (!st[v].is_clone) cout << st[v].first_pos - P_length + 1 << endl;
      for (int u : st[v].inv_link) output_all_occurrences(u, P_length);
    }
    ```

### Shortest String That Does Not Occur

???+ example "Problem"
    Given a string $S$ and a specific alphabet, find the shortest string that does not appear in $S$.

??? note "Solution"
    We perform dynamic programming on the suffix automaton of string $S$.
    
    Suppose we have processed part of the substring and are currently at state $v$. We want to find the minimum number of characters needed to add to reach a discontinuous transition. Let this quantity at node $v$ be $d_v$.
    
    Computing $d_v$ is very simple. If there is no transition using at least one character from the alphabet, then $d_v=1$. Otherwise, adding one character is not enough; we need to find the minimum among all transitions:
    
    $$
    d_{v}=1+\min_{w:(v,w,c)\in SAM}d_{w}
    $$
    
    The answer to the problem is $d_{t_0}$. The string can be recovered by backtracking through the computed array $d$.

### Longest Common Substring of Two Strings

???+ example "Problem"
    Given two strings $S$ and $T$, find the longest common substring. A common substring is defined as a string $X$ that appears as a substring in both $S$ and $T$.

??? note "Solution"
    We construct a suffix automaton for string $S$.
    
    Now we process string $T$, and for each prefix, find the longest suffix of this prefix that exists in $S$. In other words, for each position in string $T$, we want to find the length of the longest common substring ending at that position in $S$ and $T$.
    
    To achieve this, we use two variables: **current state** $v$ and **current length** $l$. These two variables describe the current matched part: its length and the state they correspond to.
    
    Initially $v=t_0$ and $l=0$, i.e., the match is empty.
    
    Now we describe how to add a character $T_{i}$ and recalculate the answer:
    
    -   If there is a transition from $v$ via character $T_{i}$, we just need to transition and increment $l$ by one.
    -   If such a transition does not exist, we need to shorten the current matched part, which means we need to transition via suffix links:
    
        $$
        v=\operatorname{link}(v)
        $$
    
        At the same time, we need to shorten the current length. Obviously we need to set $l$ to $\operatorname{len}(v)$, because after following this suffix link, the state we reach corresponds to a substring that is a suffix.
    -   If we still don't have a transition using this character, we continue following suffix links and decreasing $l$ until we find a transition or reach the virtual state $-1$ (which means character $T_{i}$ never appeared in $S$, so we set $v=l=0$).
    
    Obviously, the answer to the problem is the maximum value of all $l$.
    
    The time complexity of this part is $O(|T|)$, because in each move we either increase $l$ by one, or move along suffix links several times, each time decreasing $l$.

    Code implementation:
    
    ```cpp
    string lcs(const string &S, const string &T) {
      sam_init();
      for (int i = 0; i < S.size(); i++) sam_extend(S[i]);
    
      int v = 0, l = 0, best = 0, bestpos = 0;
      for (int i = 0; i < T.size(); i++) {
        while (v && !st[v].next.count(T[i])) {
          v = st[v].link;
          l = st[v].length;
        }
        if (st[v].next.count(T[i])) {
          v = st[v].next[T[i]];
          l++;
        }
        if (l > best) {
          best = l;
          bestpos = i;
        }
      }
      return T.substr(bestpos - best + 1, best);
    }
    ```

Example problem: [SPOJ Longest Common Substring](https://www.spoj.com/problems/LCS/en/)

### Longest Common Substring Among Multiple Strings

???+ example "Problem"
    Given $k$ strings $S_i$. We need to find their longest common substring, i.e., a string $X$ that appears as a substring in each string.

??? note "Solution 1"
    We concatenate all substrings into a longer string $T$, separating each string with a special character $D_i$ (one character per string):
    
    $$
    T=S_1+D_1+S_2+D_2+\cdots+S_k+D_k.
    $$
    
    Then we construct a suffix automaton for string $T$.
    
    Now we need to find a string that exists in all strings $S_i$ in the automaton. We can use the added special characters for this. If $S_j$ contains a substring $X$, then from the node $t$ corresponding to substring $X$, there must exist a path to $D_j$ that does not pass through any other special characters $D_1,\cdots,D_{j-1},D_{j+1},\cdots,D_k$. For a common substring $X$, such a path should exist for each special character $D_j$.
    
    Therefore, we need to compute reachability, i.e., for each state in the automaton and each character $D_i$, whether such a path exists. This can be easily computed by DFS or BFS along with dynamic programming. After that, the answer is the longest among the longest substrings $\operatorname{longest}(v)$ corresponding to all states that can reach all special characters.

??? note "Solution 2"
    Let $S_1$ be the **shortest** string, and construct SAM for it. Using the algorithm for finding the longest common substring of two strings, calculate the longest common substring length between each remaining string and $S_1$. During matching, each character from the string $S_j$ being matched causes a corresponding move on the SAM. Therefore, we can directly record, **during the matching process**, the length of the longest substring of $S_j$ that each state in the SAM can match.
    
    Because during the matching process, when we match to a state in SAM, we must also match to all its ancestor nodes on the suffix link tree, but the matching length information for ancestor nodes is not updated. Therefore, after completing the matching for string $S_j$, we need to update from bottom to top along suffix links, propagating the longest substring information matched by child nodes to their parent nodes. At this time, we need to note that the longest matching length recorded by the parent node cannot exceed its own $\operatorname{len}$ value. This way, we obtain the **actual** longest substring length of $S_j$ that each state on $S_1$'s SAM can match.
    
    Finally, after matching each $S_2,\cdots,S_k$, we take the minimum of the actual matched lengths recorded for each state on the SAM, which gives the longest common substring length between each state and $S_2,\cdots,S_k$. Then, by traversing all states on the SAM and taking the maximum, we obtain the longest common substring length of the $k$ strings.
    
    The algorithm's time complexity is $O(\sum_i |S_i|)$. Although the SAM of $S_1$ is traversed $k$ times, because $|S_1$ is the smallest, $k|S_1|\le \sum_i |S_i|$, so the main term of complexity is still the matching process traversing all substrings.

Example problem: [SPOJ Longest Common Substring II](https://www.spoj.com/problems/LCS2/)

## Practice Problems

-   [Template: Suffix Automaton](https://www.luogu.com.cn/problem/P3804)
-   [SDOI2016 Generate Spell](https://loj.ac/problem/2033)
-   [SPOJ - SUBLEX](https://www.spoj.com/problems/SUBLEX/)
-   [TJOI2015 String Theory](https://loj.ac/problem/2102)
-   [SPOJ Longest Common Substring](https://www.spoj.com/problems/LCS/en/)
-   [SPOJ Longest Common Substring II](https://www.spoj.com/problems/LCS2/)
-   [Codeforces 1037H Security](https://codeforces.com/problemset/problem/1037/H)
-   [Codeforces 666E Forensic Examination](https://codeforces.com/problemset/problem/666/E)
-   [HDU4416 Good Article Good sentence](https://acm.hdu.edu.cn/showproblem.php?pid=4416)
-   [HDU4436 str2int](https://acm.hdu.edu.cn/showproblem.php?pid=4436)
-   [HDU6583 Typewriter](https://acm.hdu.edu.cn/showproblem.php?pid=6583)
-   [Codeforces 235C Cyclical Quest](https://codeforces.com/problemset/problem/235/C)
-   [CTSC2012 Familiar Article](https://www.luogu.com.cn/problem/P4022)
-   [NOI2018 Your Name](https://uoj.ac/problem/395)

## Related Materials

We first give some of the earliest literature related to SAM:

-   A. Blumer, J. Blumer, A. Ehrenfeucht, D. Haussler, R. McConnell. Linear Size Finite Automata for the Set of All Subwords of a Word. An Outline of Results. [1983]
-   A. Blumer, J. Blumer, A. Ehrenfeucht, D. Haussler. The Smallest Automaton Recognizing the Subwords of a Text. [1984]
-   Maxime Crochemore. Optimal Factor Transducers. [1985]
-   Maxime Crochemore. Transducers and Repetitions. [1986]
-   A. Nerode. Linear automaton transformations. [1958]

Additionally, this topic can be found in more recent resources and many books on string algorithms:

-   Maxime Crochemore, Rytter Wowjcieh. Jewels of Stringology. [2002]
-   Bill Smyth. Computing Patterns in Strings. [2003]
-   Bill Smith. Methods and algorithms of calculations on lines. [2006]

Additionally, there are some materials:

-   "Suffix Automaton", Chen Lijie.
-   "Extension of Suffix Automaton on Trie", Liu Yanyi.
-   "Suffix Automaton and Its Applications", Zhang Tianyang.
-   <https://www.cnblogs.com/zinthos/p/3899679.html>
-   <https://codeforces.com/blog/entry/20861>
-   <https://zhuanlan.zhihu.com/p/25948077>

**This page is mainly translated from the article [Суффиксный автомат](http://e-maxx.ru/algo/suffix_automata) and its English translation [Suffix Automaton](https://cp-algorithms.com/string/suffix-automaton.html). The Russian version is in the public domain with a leave-a-link requirement; the English version is licensed under CC-BY-SA 4.0.**

[^state-endpos]: The reason each state should be taken as an $\operatorname{endpos}$ equivalence class is essentially the Myhill–Nerode theorem mentioned in this paragraph. Simply put, if two strings $t$ and $u$ have different $\operatorname{endpos}$ sets, they cannot correspond to the same state in SAM: paths from the same state to terminal states are always the same, which means appending characters to the ends of $t$ and $u$ to reach the end of $s$ is also the same. This precisely indicates that $t$ and $u$ have the same ending positions in string $s$. Conversely, as long as two strings $t$ and $u$ have the same $\operatorname{endpos}$ set, they can correspond to the same state in SAM. That this is feasible is exactly the content of the proof of Nerode's theorem, which we won't discuss further. However, at least from this discussion, we can believe that putting strings with the same $\operatorname{endpos}$ set into the same state yields a SAM that is definitely minimal, because further merging nodes is impossible.

[^time-complexity]: If we don't additionally use a list to record available transitions for the current state, but instead use an array to store all possible transitions (whether they exist or not) and directly copy them when copying nodes, then the time complexity is also $O(n|\Sigma|)$.

[^monotone-loc]: What the main text doesn't explain is whether the position of $\operatorname{longest}(\operatorname{link}(\operatorname{link}(\textit{last})))$ is also monotonically (weakly) increasing in cases 1 and 2. Case 1 is easy to verify: after the update, $\operatorname{longest}(\operatorname{link}(\operatorname{link}(\textit{last})))$ is the empty string, with its starting and ending positions at the end of string $s$. In case 2, the transition is continuous, indicating $\operatorname{longest}(q) = \operatorname{longest}(p)+c$. However, adding a new character to the end of a substring only makes it more difficult for that substring to appear in the string. That is, when the end position set of the suffix of $\operatorname{longest}(p)$ with length $\operatorname{len}(\operatorname{link}(p))$ strictly contains $\operatorname{endpos}(p)$, the end position set of the suffix of $\operatorname{longest}(q)$ with length $\operatorname{len}(\operatorname{link}(p))+1$ may still be the same as $\operatorname{endpos}(q)$. Therefore, $\operatorname{len}(\operatorname{link}(q)) < \operatorname{len}(\operatorname{link}(p))+1$, i.e., the starting position of $\operatorname{longest}(\operatorname{link}(p))$ as a suffix of $s$ is certainly not greater than the starting position of $\operatorname{longest}(\operatorname{link}(q))$ as a suffix of $s+c$. And when we find state $p$ that has a transition via $c$, we must have moved at least once, which indicates that the starting position of $\operatorname{longest}(\operatorname{link}(p))$ as a suffix of $s$ is not less than the starting position of $\operatorname{longest}(\operatorname{link}(\operatorname{link}(\textit{last})))$ as a suffix of $s$. Finally, $\operatorname{longest}(\operatorname{link}(q)) = \operatorname{longest}(\operatorname{link}(\operatorname{link}(\textit{cur})))$. This shows that in case 2, the position of $\operatorname{longest}(\operatorname{link}(\operatorname{link}(\textit{last})))$ is also monotonically increasing.