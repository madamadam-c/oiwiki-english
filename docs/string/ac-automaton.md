author: Ir1d, Tiphereth-A, sshwy, ksyx, Marcythm, orzAtalod, Xeonacid, Enter-tainer, GavinZhengOI, Henry-ZHR, iamtwz, 383494, abc1763613206, aofall, Chrogeek, CoelacanthusHex, Dafenghh, DanJoshua, Gesrua, kenlig, lyccrius, Menci, opsiff, ouuan, partychicken, Persdre, Ruakker, shuzhouliu, StudyingFather, szdytom, XuYueming520, ZXyaang, alphagocc, c-forrest, Early0v0, GoodCoder666, HeRaNO, liangbob2023, qq2964, r-value, rickyxrc, Rickyxrc, shawlleyw, Unnamed2964, zica87, ZnPdCo, sun2snow

## Overview

The AC (Aho-Corasick) automaton is an automaton **based on the structure of Trie**, combined with **the idea of KMP**, used to solve multi-pattern matching and other tasks.

The AC automaton is essentially an automaton on a Trie.

Before reading this article, please first read [KMP](./kmp.md) and [Trie](./trie.md).

## Explanation

Simply put, building an AC automaton has two steps:

1.  Basic Trie structure: construct a Trie from all pattern strings;
2.  KMP's idea: construct fail pointers for all nodes in the Trie tree.

After construction, we can use it for multi-pattern matching.

## Trie Construction

When initializing, the AC automaton inserts several pattern strings into a Trie, and then builds the AC automaton on the Trie. This Trie is a normal Trie, built using the original method of constructing a Trie.

It should be noted that nodes in the Trie represent prefixes of some pattern strings. We also refer to them as states later. One node represents one state, and edges of the Trie are state transitions.

Formally, for several pattern strings $s_1,s_2,\cdots,s_n$, let $Q$ be the set of all states after constructing a Trie from them.

## Fail Pointers

The AC automaton uses a fail pointer to assist in multi-pattern string matching.

The fail pointer of state $u$ points to another state $v$, where $v \in Q$, and $v$ is the longest suffix of $u$ (i.e., the longest one among the suffix states is taken as the fail pointer).

Comparison between fail pointer and [KMP](./kmp.md)'s next pointer:

1.  Similarity: both are pointers used for jumping when mismatch occurs.
2.  Difference: the next pointer computes the longest Border (i.e., the longest identical prefix and suffix), while the fail pointer points to the longest suffix that matches a prefix among all pattern strings.

Since KMP matches only one pattern string, while the AC automaton matches multiple pattern strings. It is possible that the node pointed to by the fail pointer corresponds to another pattern string, and their prefixes are different.

In summary, the fail pointer of the AC automaton points to the longest suffix state of the current state.

Note: When matching with the AC automaton, multiple pattern strings can be matched at the same position.

### Building the Pointer

The **basic idea** of building fail pointers is described below:

Building fail pointers can refer to the idea of constructing next pointers in KMP.

Consider the current node $u$ in the Trie, whose parent node is $p$, and $p$ points to $u$ through character $c$, i.e., $\operatorname{trie}(p, c)=u$. Assume fail pointers of all nodes with depth less than $u$ have been obtained.

1.  If $\operatorname{trie}(\operatorname{fail}(p), c)$ exists: then let the fail pointer of $u$ point to $\operatorname{trie}(\operatorname{fail}(p), c)$. This is equivalent to adding a character $c$ after $p$ and $\operatorname{fail}(p)$ respectively, which correspond to $u$ and $\operatorname{fail}(u)$;
2.  If $\operatorname{trie}(\operatorname{fail}(p), c)$ does not exist: then we continue to find $\operatorname{trie}(\operatorname{fail}(\operatorname{fail}(p)), c)$. Repeat the judgment process, keep jumping fail pointers until the root node;
3.  If it still doesn't exist, let the fail pointer point to the root node.

This completes the construction of $\operatorname{fail}(u)$.

### Example

The following several GIF animations will demonstrate the process of building fail pointers for the Trie constructed from strings $\mathtt{i}$, $\mathtt{he}$, $\rtl{his}$, $\rtl{she}$, $\rtl{hers}$:

1.  Yellow node: the current node $u$.
2.  Green nodes: nodes that have been traversed by BFS.
3.  Orange edge: fail pointer.
4.  Red edge: the fail pointer currently being computed.

![AC\_automation\_gif\_b\_3.gif](./images/ac-automaton1.gif)

Let's focus on analyzing the construction of node $6$'s fail pointer:

![AC\_automation\_6\_9.png](./images/ac-automaton1.png)

Find node $6$'s parent node $5$, $\operatorname{fail}(5)=10$. However, node $10$ has no edge outgoing by letter $\rtl{s}$; continue jumping to the fail pointer of $10$, $\operatorname{fail}(10)=0$. Found that node $0$ has an edge outgoing by letter $\rtl{s}$, pointing to node $7$; therefore $\operatorname{fail}(6)=7$.

The figure below shows the state after construction is complete:

![finish](./images/ac-automaton4.png)

## Trie and Trie Graph

Focus on the `build` function. This function has two goals: one is to build fail pointers, and the other is to build the automaton. The related variable definitions are as follows:

1.  `tr[u].son[c]`: There are two ways to understand it. We can simply understand it as an edge on the Trie, i.e., $\operatorname{trie}(u, c)$; or we can understand it as the state (node) reached from state (node) $u$ by adding a character $c$, i.e., a state transition function $\operatorname{trans}(u, c)$. For convenience, we will use the second understanding in the following text.
2.  Queue `q`: used for BFS traversal of the Trie.
3.  `tr[u].fail`: the fail pointer of node $u$.

???+ note "Implementation"
    === "C++"
        ```cpp
        void build() {
          queue<int> q;
          for (int i = 0; i < 26; i++)
            if (tr[0].son[i]) q.push(tr[0].son[i]);
          while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
              if (tr[u].son[i]) {
                tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];
                q.push(tr[u].son[i]);
              } else
                tr[u].son[i] = tr[tr[u].fail].son[i];
            }
          }
        }
        ```
    
    === "Python"
        ```python
        def build():
            for i in range(0, 26):
                if tr[0][i] != 0:
                    q.append(tr[0][i])
            while q:
                u = q.pop(0)
                for i in range(0, 26):
                    if tr[u][i] != 0:
                        fail[tr[u][i]] = tr[fail[u]][i]
                        q.append(tr[u][i])
                    else:
                        tr[u][i] = tr[fail[u]][i]
        ```

### Explanation

The `build` function enqueues nodes in BFS order, and computes fail pointers in turn. Here the root node of the Trie is $0$, and we enqueue the children of the root node one by one. If we enqueue the root node, then during the first BFS, the fail pointer of the root's children would be marked as itself. Therefore, we enqueue the root's children instead of the root node.

Then we start BFS: each time we take out the node $u$ at the front of the queue ($\operatorname{fail}(u)$ has been obtained during the previous BFS process), and then traverse the character set (here $0 \sim 25$, corresponding to $\rtl{a} \sim \rtl{z}$, i.e., various child nodes of $u$):

1.  If $\operatorname{trans}(u, c)$ exists, we assign the fail pointer of $\operatorname{trans}(u, c)$ to $\operatorname{trans}(\operatorname{fail}(u), c)$. According to the previous description, we should use a `while` loop, keep jumping fail pointers, check whether a node corresponding to character $c$ exists, and then assign it. However, this is simplified by special handling here, which will be explained later;
2.  Otherwise, let $\operatorname{trans}(u, c)$ point to the state of $\operatorname{trans}(\operatorname{fail}(u), c)$.

The processing here modifies the structure of the Trie through the code in the `else` statement, linking non-existent Trie states to the corresponding states of the fail pointer. In the original Trie, each node represents a string $S$, which is a prefix of some pattern string. After modifying the Trie structure, although many transition relationships are added, the string represented by nodes (states) does not change.

And $\operatorname{trans}(S, c)$ is equivalent to adding a character $c$ after $S$ to become another state $S'$. If $S'$ exists, it means there is a prefix of a pattern string that is $S'$. Otherwise, we let $\operatorname{trans}(S, c)$ point to $\operatorname{trans}(\operatorname{fail}(S), c)$. Since the string corresponding to $\operatorname{fail}(S)$ is a suffix of $S$, the string corresponding to $\operatorname{trans}(\operatorname{fail}(S), c)$ is also a suffix of $S'.

In other words, when jumping on the Trie, we only jump from $S$ to $S'$, which is equivalent to matching $S'$; but when jumping on the AC automaton, we jump from $S$ to a suffix of $S'$, which means we match a character $c$ and discard part of the prefix of $S$. Obviously, discarding the prefix can still match. At the same time, if the text string can match $S$, obviously it can also match a suffix of $S$, so the fail pointer also discards the prefix. The so-called fail pointer is actually a set of suffixes of $S$.

The child array `son` of Trie nodes has another simpler understanding: if we mismatch at position $u$, we jump to the position of $\operatorname{fail}(u)$. Note that this may cause us to jump along the fail array multiple times to reach the next position that can match. So we can use `son` to directly record the next position that can match, which ensures the time complexity of the program.

The modification of the Trie structure here can make the matching transition more complete. At the same time, it compresses the path of jumping fail pointers, turning what originally required many fail pointer jumps into just one jump.

### Process

Here are several GIF animations showing the construction process:

![AC\_automation\_gif\_b\_pro3.gif](./images/ac-automaton2.gif)

1.  Blue node: node $u$ traversed by BFS.
2.  Blue edge: edges added by the AC automaton modifying the Trie structure in the current node.
3.  Black edge: edges added by the AC automaton modifying the Trie structure.
4.  Red edge: fail pointer computed for the current node.
5.  Yellow edge: fail pointer.
6.  Gray edge: edge of the Trie.

We can find that many interleaved black edges turn the Trie into a **Trie graph**. The figure omits the black edges pointing to the root node (otherwise it would be even messier). Let's focus on analyzing the situation when traversing node $5$. We compute the fail pointer of $\operatorname{trans}(5, \rtl{s})=6$:

![AC\_automation\_b\_7.png](./images/ac-automaton2.png)

The original strategy was to find the fail pointer, so we jumped to $\operatorname{fail}(5)=10$ and found no Trie edge outgoing by $\rtl{s}$, so we jumped to $\operatorname{fail}(10)=0$, found $\operatorname{trie}(0, \rtl{s})=7$, so $\operatorname{fail}(6)=7$; but with black edges and blue edges, after jumping to $\operatorname{fail}(5)=10$, we directly go to $\operatorname{trans}(10, \rtl{s})=7$ and reach node $7$.

This is the two things completed by `build`: building fail pointers and establishing the Trie graph. This Trie graph also plays a key role during queries.

## Multi-Pattern Matching

Next, let's analyze the matching function `query`:

???+ note "Implementation"
    === "C++"
        ```cpp
        int query(const char t[]) {
          int u = 0, res = 0;
          for (int i = 1; t[i]; i++) {
            u = tr[u].son[t[i] - 'a'];
            for (int j = u; j && tr[j].cnt != -1; j = tr[j].fail) {
              res += tr[j].cnt, tr[j].cnt = -1;
            }
          }
          return res;
        }
        ```
    
    === "Python"
        ```python
        def query(t: str) -> int:
            u, res = 0, 0
            for c in t:
                u = tr[u][c - ord("a")]
                j = u
                while j and e[j] != -1:
                    res += e[j]
                    e[j] = -1
                    j = fail[j]
            return res
        ```

### Explanation

Here, $u$ is the current matched node on the Trie, and `res` is the answer returned. We iterate through the matching string, and $u$ tracks the current character on the Trie. Using the fail pointer, we find all matched pattern strings and accumulate them into the answer. Then we clear the occurrence count of the matched string so that we don't count the same string multiple times. As analyzed before, the Trie structure is actually a trans function, and after building this function, during the matching process of the string, we discard part of the prefix to achieve the minimum matching. The fail pointer points to more matching states. Finally, a diagram. For the automaton just now:

![AC\_automation\_b\_13.png](./images/ac-automaton3.png)

We start from the root node and try to match $\rtl{ushersheishis}$. Then the changes of $p$ will be:

![AC\_automation\_gif\_c.gif](./images/ac-automaton3.gif)

1.  Red node: node $p$.
2.  Pink arrow: the jump of $p$ on the automaton.
3.  Blue edge: successfully matched pattern strings.
4.  Blue node: the node (state) when jumping fail pointers.

## Efficiency Optimization

For the problem, please refer to Luogu [P5357【Template】AC Automaton](https://www.luogu.com.cn/problem/P5357).

Because in our AC automaton, during each match, we keep jumping along fail edges to find all matches, but this is inefficient and may time out on some problems.

So how to optimize? First, we need to understand a property of fail pointers: in an AC automaton, if we only keep fail edges, the remaining graph must be a tree.

This is obvious because fail does not form cycles and the depth must be lower than the current one, so it's proven.

Thus, the matching of the AC automaton can be transformed into a chain sum problem on the fail tree, and we only need to optimize this part.

Two approaches are provided here.

### Topological Sort Optimization

It is observed that the main time waste is in jumping fail every time. If we can pre-record them and sum them at the end, the efficiency will be optimized.

So we do a topological sort on the fail tree, which can compute the occurrence counts of all pattern strings at once.

The `build` function adds an indegree counting part on the original basis, preparing for topological sort.

???+ note "Construction"
    ```cpp
    void build() {
      queue<int> q;
      for (int i = 0; i < 26; i++)
        if (tr[0].son[i]) q.push(tr[0].son[i]);
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
          if (tr[u].son[i]) {
            tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];
            tr[tr[tr[u].fail].son[i]].du++;  // indegree count
            q.push(tr[u].son[i]);
          } else
            tr[u].son[i] = tr[tr[u].fail].son[i];
        }
      }
    }
    ```

Then during queries, we can just mark the `ans` of the found nodes, and finally use topological sort to compute the answer.

???+ note "Query"
    ```cpp
    void query(const char t[]) {
      int u = 0;
      for (int i = 1; t[i]; i++) {
        u = tr[u].son[t[i] - 'a'];
        tr[u].ans++;
      }
    }
    
    void topu() {
      queue<int> q;
      for (int i = 0; i <= tot; i++)
        if (tr[i].du == 0) q.push(i);
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        ans[tr[u].idx] = tr[u].ans;
        int v = tr[u].fail;
        tr[v].ans += tr[u].ans;
        if (!--tr[v].du) q.push(v);
      }
    }
    ```

Finally, the main function:

???+ note "Main Function"
    ```cpp
    int main() {
      // do_something();
      AC::build();
      scanf("%s", s + 1);
      AC::query(s);
      AC::topu();
      for (int i = 1; i <= n; i++) printf("%d\n", AC::ans[idx[i]]);
      // do_another_thing();
    }
    ```

??? note "Template Problem [Luogu P5357「Template」AC Automaton](https://www.luogu.com.cn/problem/P5357) Topological Sort Optimization Reference Code"
    ```cpp
    --8<-- "docs/string/code/ac-automaton/ac-automaton_topu.cpp"
    ```

### DFS Optimization

Similar to the idea of topological sort, we use DFS instead of topological sort. In fact, these two methods are essentially the same, both summing the subtrees of the fail tree.

For the complete code, see Summary Template 3.

## DP on AC Automaton

This section uses [P2292 [HNOI2004] L Language](https://www.www.luogu.com.cn/problem/P2292) as an example.

A naive idea comes to mind: build an AC automaton, transfer through all fail pointer substrings on the AC automaton, and finally take the maximum value to get the answer.

The main code is as follows. If you are not familiar with the type definitions in the code, you can first look at the complete code at the end:

???+ note "Main Code of Query Part"
    ```cpp
    int query(const char t[]) {
      int u = 0, len = strlen(t + 1);
      for (int i = 1; i <= len; i++) dp[i] = 0;
      for (int i = 1; i <= len; i++) {
        u = tr[u].son[t[i] - 'a'];
        for (int j = u; j; j = tr[j].fail) {
          if (tr[j].idx && (dp[i - tr[j].depth] || i - tr[j].depth == 0)) {
            dp[i] = dp[i - tr[j].depth] + tr[j].depth;
          }
        }
      }
      int ans = 0;
      for (int i = 1; i <= len; i++) ans = std::max(ans, dp[i]);
      return ans;
    }
    ```

However, the complexity of this idea is not linear (because we need to jump fail for each node), and it will time out on the second sub-task. So we need to optimize.

Looking at the special nature of the problem again, we find that all word lengths are only $20$, so we can think of state compression optimization.

We find that the main time bottleneck is in jumping fail pointers. If we can optimize this step to $O(1)$, we can ensure the entire problem is solved in strictly linear time.

We can store the possible substring lengths among the first $20$ bits, and compress them into the state, stored in each child node.

Then during `build`, we can write it like this:

???+ note "Building Fail Pointers"
    ```cpp
    void build() {
      queue<int> q;
      for (int i = 0; i < 26; i++)
        if (tr[0].son[i]) {
          q.push(tr[0].son[i]);
          tr[tr[0].son[i]].depth = 1;
        }
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        int v = tr[u].fail;
        // update of state is here
        tr[u].stat = tr[v].stat;
        if (tr[u].idx) tr[u].stat |= 1 << tr[u].depth;
        for (int i = 0; i < 26; i++) {
          if (tr[u].son[i]) {
            tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];
            tr[tr[u].son[i]].depth = tr[u].depth + 1;  // record depth
            q.push(tr[u].son[i]);
          } else
            tr[u].son[i] = tr[tr[u].fail].son[i];
        }
      }
    }
    ```

Then during query, we can remove the fail jumping loop, and simplify the code as follows:

???+ note "Query"
    ```cpp
    int query(const char t[]) {
      int u = 0, mx = 0;
      unsigned st = 1;
      for (int i = 1; t[i]; i++) {
        u = tr[u].son[t[i] - 'a'];
        st <<= 1;  // jumped one step, each bit's length increases by 1
        if (tr[u].stat & st) st |= 1, mx = i;
      }
      return mx;
    }
    ```

Our `tr[u].stat` maintains the set of lengths along the entire fail chain starting from node $u$ (since the set of lengths is less than $32$, it doesn't affect), and `st` maintains the set of lengths of the first $32$ bits of the query string so far (due to natural overflow of state compression).

After the `&` operation, if the result is non-zero, it means the intersection of the two length sets is non-empty. At this point, we found a match.

??? note "[P2292 [HNOI2004] L Language](https://www.luogu.com.cn/problem/P2292) Complete Code"
    ```cpp
    --8<-- "docs/string/code/ac-automaton/ac_automaton_luoguP2292.cpp"
    ```

## Summary

Time complexity: Let $|s_i|$ be the length of template string $i$, $|S|$ be the length of the text string, and $|\Sigma|$ be the size of the character set (a constant, generally $26$). If the Trie graph is connected, the time complexity is $O(\sum|s_i|+n|\Sigma|+|S|)$, where $n$ is the number of nodes in the AC automaton, and can reach $o(\sum|s_i|)$ at maximum. If the Trie graph is not connected, and during construction we avoid traversing empty children when building fail pointers, the time complexity is $O(\sum|s_i|+|S|)$.

??? note "Template Problem [Luogu P3808 AC Automaton (Simple Version)](https://www.luogu.com.cn/problem/P3808) Reference Code"
    ```cpp
    --8<-- "docs/string/code/ac-automaton/ac-automaton_1.cpp"
    ```

??? note "Template Problem [Luogu P3796 AC Automaton (Simple Version II)](https://www.luogu.com.cn/problem/P3796) Reference Code"
    ```cpp
    --8<-- "docs/string/code/ac-automaton/ac-automaton_2.cpp"
    ```

??? note "Template Problem [Luogu P5357「Template」AC Automaton](https://www.luogu.com.cn/problem/P5357) DFS Optimization Reference Code"
    ```cpp
    --8<-- "docs/string/code/ac-automaton/ac-automaton_3.cpp"
    ```