A suffix tree is a data structure that maintains all suffixes of a string.

## Some Notation

Let $S$ be the string on which the suffix tree is built, with length $n$ and alphabet $\Sigma$.

Let $S[i]$ denote the $i$-th character in $S$, where $1 \le i \le n$.

Let $S[l, r]$ denote the string consisting of the $l$-th to $r$-th characters in $S$, called a substring of $S$.

Denote $S[i, n]$ as the suffix of $S$ starting at $i$, and $S[1, i]$ as the prefix of $S$ ending at $i$.

## Definition

Define the **suffix trie** of string $S$ as the trie obtained by inserting all suffixes of $S$ into a trie tree. In a suffix trie, the string corresponding to node $x$ is the string formed by concatenating the characters along the path from the root to $x$. Denote all nodes in the suffix trie that correspond to some suffix of $S$ as suffix nodes.

It is easy to see the superior property of the suffix trie: its non-root nodes can exactly accept all distinct non-empty substrings of $S$. However, the time and space complexity of building a suffix trie are both $O(n^2)$, which is often unacceptable, so we introduce the concept of a suffix tree.

If we take all nodes in the suffix trie that have more than one child and the suffix nodes as key points, and define the compressed trie formed by keeping only the key points and compressing the chains formed by non-key points into single edges as the **Suffix Tree**. If we only take all nodes in the suffix trie that have more than one child and leaf nodes as key points, and define the compressed trie formed by keeping only the key points as the **Implicit Suffix Tree**. It is easy to see that the implicit suffix tree is the result of further compression of the suffix tree.

In both the suffix tree and implicit suffix tree, each edge corresponds to a string; each non-root node $x$ corresponds to a set of strings, which are any non-empty prefix of the string formed by concatenating the string along the path from the root to the parent node $fa_x$ of $x$ with the string corresponding to the tree edge from $fa_x$ to $x$, called $str_x$. Also, in an implicit suffix tree, a suffix that does not correspond to any node is called an **implicit suffix**.

The following figure shows, from left to right, the suffix trie, suffix tree, and implicit suffix tree built on the string $\texttt{cabab}$ as the base string.

![suffix-tree\_cabab1.png](./images/suffix-tree1.png)

Consider inserting suffixes of $S$ into the suffix trie one by one. Starting from the second insertion, at most one node with more than one child and one suffix node are added each time, so the suffix tree has at most $2n$ nodes, which is excellent.

## Building a Suffix Tree

### Algorithm Supporting Dynamic Character Addition at the Front

The parent tree formed by building a SAM on the reversed string is exactly the suffix tree of that string. Therefore, we can simply add characters of the reversed string to the SAM one by one.

???+ note "Reference Implementation"
    ```cpp
    struct SuffixAutomaton {
      int tot, lst;
      int siz[N << 1];
      int buc[N], id[N << 1];
    
      struct Node {
        int len, link;
        int ch[26];
      } st[N << 1];
    
      SuffixAutomaton() : tot(1), lst(1) {}
    
      void extend(int ch) {
        int cur = ++tot, p = lst;
        lst = cur;
        siz[cur] = 1, st[cur].len = st[p].len + 1;
        for (; p && !st[p].ch[ch]; p = st[p].link) st[p].ch[ch] = cur;
        if (!p)
          st[cur].link = 1;
        else {
          int q = st[p].ch[ch];
          if (st[q].len == st[p].len + 1)
            st[cur].link = q;
          else {
            int pp = ++tot;
            st[pp] = st[q];
            st[pp].len = st[p].len + 1;
            st[cur].link = st[q].link = pp;
            for (; p && st[p].ch[ch] == q; p = st[p].link) st[p].ch[ch] = pp;
          }
        }
      }
    } SAM;
    ```

### Algorithm Supporting Dynamic Character Addition at the Back

The Ukkonen algorithm is an incremental construction algorithm. We insert each character of string $S$ into the tree one by one, and correctly maintain the current suffix tree after each insertion.

#### Naive Algorithm

First, let's introduce a more brute-force construction method. We use the string $\texttt{abbbc}$ to demonstrate the construction process.

Initially, establish a root node, called node $0$. Also, for each edge, we maintain an interval $[l,r]$ to indicate that the string on this edge is $S[l,r]$. Additionally, maintain $m$, the number of characters already inserted, initially $0$.

First, insert character $\texttt a$. Directly extend an edge from node $0$, labeled $[1,\infty]$, pointing to a newly created node. Here $\infty$ is a very large value, which can be understood as the end of the string. This way, when inserting new characters, this edge will automatically include the new characters.

![suffix-tree\_a.webp](./images/suffix-tree2.webp)

Next, we insert character $\texttt b$. Similarly, extend an edge from $0$, labeled $[2,\infty]$. Note that the meaning of the previously extended edge $[1,\infty]$ automatically changes. As the end of the string changes, the string it represents changes from $\texttt a$ to $\texttt {ab}$. This is correct because all previous suffixes already appear in the tree as leaf nodes, we just need to insert the current character at the end of all leaf nodes.

![suffix-tree\_ab.webp](./images/suffix-tree3.webp)

Next, we want to insert another character $\texttt b$. However, $\texttt b$ is a substring of the already inserted string, so the original tree already contains $\texttt b$. At this point, we do nothing and record that $k$ represents $S[k,m]$ as the longest implicit suffix.

![suffix-tree\_abb.webp](./images/suffix-tree4.webp)

Next, we insert another $\texttt b$. Since the previous $\texttt b$ was not successfully inserted, at this point $k=3$, representing the suffix to be inserted as $\texttt {bb}$. We start from the root and look for $\texttt {bb}$, and find it is also in the original tree. Similarly, we do nothing.

![suffix-tree\_abbb.webp](./images/suffix-tree5.webp)

Note that we did not handle the suffixes after $k$. Because if $S[k,m]$ is an implicit suffix, then for $l>k$, $S[l,m]$ are all implicit suffixes. Since we know from $S[k,m]$ being an implicit suffix that there exists a character $c$ such that $S[k, m] + c$ is a substring of $S$, so $S[l, m] + c$ is also a substring of $S$. By the definition of implicit suffix tree, $S[l, m]$ also does not appear as a leaf node.

Next, we insert $\texttt c$. At this point, $k=3$, so we need to find $\texttt {bbc}$ from the root. We find it is not in the original tree. We need to extend an edge labeled $[5,\infty]$ from the node representing $\texttt {bb}$. But we find this node doesn't actually exist; instead, it is contained in an edge. Therefore, we need to split this edge, create a new node, and then extend the desired edge from the created node. At this point, the insertion is successful. Let $k \to k+1$, because $S[k,m]$ is no longer an implicit suffix.

![suffix-tree\_abbbc1.webp](./images/suffix-tree6.webp)

Next, since $k$ has changed, we repeat this process until an implicit suffix appears again, or $k>m$ (in this example, it's the latter).

![suffix-tree\_abbbc2.webp](./images/suffix-tree7.webp)

The construction process ends.

In this algorithm, each brute-force search and insertion from the root has $O(n)$ worst-case complexity, so the total complexity is $O(n^2)$.

#### Suffix Links

The naive algorithm is slow mainly because each extend operation requires finding the insertion position of the longest implicit suffix from the root. So consider remembering this position. First, we use a pair $(now,rem)$ to describe the longest implicitly included suffix $S[k,m]$. Walking from node $now$ along the edge starting with $S[m-rem+1]$ for length $rem$ should uniquely represent a string. When inserting a new character, we only need to look up from the position described by $now$ and $rem$.

Now, we only need to update $(now,rem)$ when $k \to k + 1$. At this point, if $now = 0$, we only need to let $rem \to rem - 1$, because the next suffix to be inserted is the one with length -1 of the previously inserted one. Otherwise, let the substring corresponding to $str_{now}$ be $S[l,r]$. We need to find a node $now'$ corresponding to $S[l+1,r]$. Let $now \to now'$ is sufficient.

First, we have a lemma: for any non-leaf, non-root node $x$ in the implicit suffix tree, there exists another non-leaf node $y$ in the tree such that $str_y$ is the substring formed by deleting the first character from the substring corresponding to $str_x$.

Proof. Let $s$ be the string formed by deleting the first character from $str_x$. By the definition of implicit suffix tree, there exist two different characters $c_1,c_2$ such that $str_x + c_1$ and $str_x + c_2$ are both substrings of $S$. Therefore, $s + c_1$ and $s + c_2$ are also substrings of $S$. So $s$ also corresponds to a branching key point in the suffix trie, i.e., there exists $y$ in the implicit suffix trie such that $str_y = s$. $\square$

From this lemma, we define $\operatorname{Link}(x)=y$, called the **suffix link** of $x$. So $now'=\operatorname{Link}(now)$ must exist. Now we only need to find all $\operatorname{Link}$ values for all non-root, non-leaf nodes in the implicit suffix tree.

#### Ukkonen Algorithm

The overall process of the Ukkonen algorithm is as follows:

To build an implicit suffix tree, we add characters of $S$ from front to back. Suppose the root node is $0$, and we have already built the implicit suffix tree of $S[1, m]$ and maintained the suffix links. The longest implicit suffix of $S[1, m]$ is $S[k, m]$, and its position in the tree is $(now, rem)$. Let $S[m + 1] = x$. Now we need to add character $x$. At this point, every suffix of $S[1, m]$ needs to have character $x$ added at its end. Since all explicit suffixes correspond to some leaf node in the tree, and their right endpoint of the parent edge is $\infty$, no maintenance is needed. So now we only need to consider the effect on the tree's shape of adding $x$ at the end of implicit suffixes. First consider $S[k, m]$, there are two cases:

1.  There is already a transition of $x$ at position $(now, rem)$. In this case, the suffix tree shape does not change. Since $S[k, m+1]$ already appears in the suffix tree, for $l > k$, $S[l, m+1]$ will also appear in the suffix tree. At this point, we only need to set $rem \to rem + 1$ and make no other modifications.
2.  There is no transition of $x$ at position $(now, rem)$. If $(now, rem)$ is exactly a node in the tree, then this node gets a new outgoing edge $x$; otherwise, we need to split the node, add a new node at this position, and add an outgoing edge $x$ from the new node. At this point, for $l > k$, we don't know what effect $S[l, m]$ will have on the suffix tree shape. So we need to continue considering $S[k + 1, m]$. Consider how to find the position of $S[k + 1, m]$ in the suffix tree: if $now$ is not $0$, we can use the suffix link, letting $now = \operatorname{Link}(now)$; otherwise, let $rem \to rem - 1$. Finally, let $k \to k + 1$ and repeat this process.

Each step only takes constant time, and the algorithm stops after inserting all characters, so the time complexity is $O(n)$.

Since the Ukkonen algorithm can only output the implicit suffix tree of $S$, and the implicit suffix tree may be less powerful than the suffix tree for some problems, when needed, we can add a character that never appears at the end of $S$. At this point, all suffixes of $S$ can correspond one-to-one with all leaf nodes of the tree.

???+ note "Reference Implementation"
    ```cpp
    struct SuffixTree {
      int ch[M + 5][RNG + 1], st[M + 5], len[M + 5], link[M + 5];
      int s[N + 5];
      int now{1}, rem{0}, n{0}, tot{1};
    
      SuffixTree() { len[0] = inf; }
    
      int new_node(int s, int le) {
        ++tot;
        st[tot] = s;
        len[tot] = le;
        return tot;
      }
    
      void extend(int x) {
        s[++n] = x;
        ++rem;
        for (int lst{1}; rem;) {
          while (rem > len[ch[now][s[n - rem + 1]]])
            rem -= len[now = ch[now][s[n - rem + 1]]];
          int &v{ch[now][s[n - rem + 1]]}, c{s[st[v] + rem - 1]};
          if (!v || x == c) {
            lst = link[lst] = now;
            if (!v)
              v = new_node(n, inf);
            else
              break;
          } else {
            int u{new_node(st[v], rem - 1)};
            ch[u][c] = v;
            ch[u][x] = new_node(n, inf);
            st[v] += rem - 1;
            len[v] -= rem - 1;
            lst = link[lst] = v = u;
          }
          if (now == 1)
            --rem;
          else
            now = link[now];
        }
      }
    } Tree;
    ```

## Applications

Every path from a node to the root in a suffix tree is a non-empty substring of $S$, which is useful for handling many string problems.

The DFS order of the suffix tree is the suffix array. A subtree of the suffix tree corresponds to an interval in the suffix array. The longest common prefix of two suffixes in the suffix tree is the LCA of their corresponding leaf nodes. Therefore, the conclusion about height in the suffix array can be understood as the LCA of several nodes being equal to the LCA of the nodes with the smallest and largest DFS order.

## Example Problems

### [Luogu P3804【Template】Suffix Automaton (SAM)](https://www.luogu.com.cn/problem/P3804)

Problem description:

Given a string $S$ containing only lowercase letters.

Find the maximum value of (the number of occurrences of a substring) × (the length of that substring) for all substrings whose number of occurrences is not $1$.

??? note "Solution"
    Build an implicit suffix tree by inserting a terminator. Every path from the root in the tree forms a substring. The number of occurrences of an explicit suffix is exactly the number of leaf nodes in the subtree of the corresponding node. Implicit suffixes need not be considered, because the number of occurrences of an implicit suffix equals the number of occurrences of the first explicit suffix encountered when going downward, and it is always shorter than that explicit suffix. So traverse the entire tree, calculate the number of leaf nodes in each node's subtree and the length of the path from each node to the root. If the number of leaf nodes > 1, update the answer. Complexity $O(|S||\Sigma|)$.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/string/code/suffix-tree/suffix-tree_1.cpp"
    ```

### [CF235C Cyclical Quest](https://codeforces.com/problemset/problem/235/C)

Problem description: Given a lowercase main string $S$ and $n$ query strings. For each query string $x_i$, find the total number of occurrences of all its cyclic isomers in the main string.

??? note "Solution"
    Build an implicit suffix tree by inserting a terminator.
    
    Enumerate which cyclic segment we are currently at, and record how long a prefix can be found in the tree.
    
    Repeat a process similar to the Ukkonen algorithm, recording the current matched position $(now,rem)$. Each time try to insert the next character; if successful, continue inserting; otherwise, break out of the loop.
    
    If one cyclic segment was successfully matched and this cyclic segment hasn't appeared before, update the answer.
    
    Then when switching to the next cyclic segment, we need to delete the character at the beginning of the currently matched substring: this is exactly equivalent to letting $now \to \operatorname{Link}(now)$. Of course, if $now=1$, we can directly let $rem \to rem - 1$.
    
    Complexity $O(|S||\Sigma|+\sum|x_i|)$

??? note "Reference Code"
    ```cpp
    --8<-- "docs/string/code/suffix-tree/suffix-tree_2.cpp"
    ```

## References

1.  2021 National Team Paper "Construction of Suffix Trees" Dai Chenxin
2.  [Cool Suffix Tree Magic - EternalAlexander's Blog](https://www.luogu.com.cn/blog/EternalAlexander/xuan-ku-hou-zhui-shu-mo-shu)