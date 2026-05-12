## Prerequisites

The generalized suffix automaton is based on the following knowledge points:

-   [Trie (Trie tree)](./trie.md)
-   [Suffix Automaton](./sam.md)

Make sure you are very familiar with both of the above knowledge points before reading this article, especially understanding the **suffix links** in the **suffix automaton**.

## Introduction

### Origin

The generalized suffix automaton (GSA) is a structure proposed by Liu Yanyi in his 2015 national team paper "Extension of Suffix Automaton on Trie", which builds a suffix automaton directly on a trie.

> Most string problems that can be solved with suffix automaton can be extended to Trie trees. — Liu Yanyi

### Conventions

Refer to [String Conventions](./basic.md).

The number of strings is $k$, i.e., $S_1, S_2, S_3 \dots S_k$.

The root node of the trie and the generalized suffix automaton is node $0$.

### Overview

The suffix automaton (SAM) is a powerful tool for handling substring problems of a single string.

The generalized suffix automaton integrates the suffix automaton into a trie to solve substring problems for multiple strings.

## Common Pseudo-Generalized Suffix Automata

1.  Directly connecting multiple strings with special symbols, then building a SAM
2.  For each string, repeatedly building on the same SAM, setting the `last` pointer to zero before each build

Method 1 and method 2 are simple to implement and usually achieve the same correctness as the generalized suffix automaton when facing problems. So many people choose such approaches online. For example, the last application in the suffix automaton article uses method 1 [(original link)](./sam.md).

However, both method 1 and method 2 have dangerously high time complexity.

## Building a Generalized Suffix Automaton

According to the original paper, a trie should first be built on multiple strings, and then the generalized suffix automaton should be built on top of the trie.

### Using a Trie

First, create a trie for multiple strings. This is not difficult if you have mastered the prerequisites. Here, to unify the context code, we provide a possible trie implementation.

??? note "Implementation"
    ```cpp
    constexpr int MAXN = 2000000;
    constexpr int CHAR_NUM = 30;
    
    struct Trie {
      int next[MAXN][CHAR_NUM];  // transitions
      int tot;                   // total nodes: [0, tot)
    
      void init() { tot = 1; }
    
      int insertTrie(int cur, int c) {
        if (next[cur][c]) return next[cur][c];
        return next[cur][c] = tot++;
      }
    
      void insert(const string &s) {
        int root = 0;
        for (auto ch : s) root = insertTrie(root, ch - 'a');
      }
    };
    ```

Here we have a trie built based on the `next` array.

### Building the Suffix Automaton

If we directly consider such a tree as a suffix automaton, we can draw the following conclusions:

-   For node `i`, its `len[i]` is the same as its depth in the trie.
-   If we perform topological sort on the trie, we can obtain a sequence of nodes with non-decreasing `len`. The BFS result is the same.

During the construction of the suffix automaton, it can be viewed as continuously inserting values with strictly increasing `len` and a difference of $1$. So we can use the result of topological sorting on the trie as a queue, and then insert nodes into the suffix automaton in the order of this queue.

Since in a normal suffix automaton, the `len` value of the previous node is fixed, which is the `len` of the `last` node. However, in a generalized suffix automaton, the inserted queue is a non-strictly increasing sequence. So for each value, its `last` should be known and fixed, which in the trie is its parent node.

Since a pseudo-suffix automaton has already been built in the trie, we only need to perform certain processing on the entire trie structure to convert it into a generalized suffix automaton. We can update each node on the trie according to the queue order proposed earlier. Finally, we can obtain the generalized suffix automaton.

For the update operation of each node, we can slightly modify the insertion operation in SAM.

For the entire insertion process, note that since insertion is performed in non-decreasing order of `len`, during data copying after `clone`, we should not copy data whose `len` is less than the current `len`.

### Process

Based on the above logic, the entire construction process can be described as follows:

1.  Insert all strings into the trie.
2.  Start BFS from the root of the trie, recording the order and the parent node of each node.
3.  For each node in the BFS sequence, construct it on the original trie in order. Note that we should not operate on data whose `len` is less than the current `len`.

### Proof of Linear Number of Operations

Since we only process the sequence obtained from BFS, we can guarantee that all nodes in the trie are visited only once.

For the worst case, consider the maximum number of nodes in the trie itself, i.e., if any two strings have no common prefix, then the number of nodes is $\sum_{i=1}^{k}|S_i|$, which is the sum of all string lengths.

The complexity of the update operations in the suffix automaton has already been proven in [Suffix Automaton](./sam.md).

Therefore, it can be proven that its worst-case complexity is linear.

And usually, the average complexity of pseudo-generalized suffix automata is equal to the worst-case complexity of the generalized suffix automaton. When dealing with a large number of strings, the efficiency of pseudo-generalized suffix automata is far inferior to that of standard generalized suffix automata.

### Implementation

We can obtain the required function by making a few necessary modifications to the insert function.

??? note "Reference Code"
    ```cpp
    struct GSA {
      int len[MAXN];             // node length
      int link[MAXN];            // suffix link
      int next[MAXN][CHAR_NUM];  // transitions
      int tot;                   // total nodes: [0, tot)
    
      int insertSAM(int last, int c) {
        int cur = next[last][c];
        len[cur] = len[last] + 1;
        int p = link[last];
        while (p != -1) {
          if (!next[p][c])
            next[p][c] = cur;
          else
            break;
          p = link[p];
        }
        if (p == -1) {
          link[cur] = 0;
          return cur;
        }
        int q = next[p][c];
        if (len[p] + 1 == len[q]) {
          link[cur] = q;
          return cur;
        }
        int clone = tot++;
        for (int i = 0; i < CHAR_NUM; ++i)
          next[clone][i] = len[next[q][i]] != 0 ? next[q][i] : 0;
        len[clone] = len[p] + 1;
        while (p != -1 && next[p][c] == q) {
          next[p][c] = clone;
          p = link[p];
        }
        link[clone] = link[q];
        link[cur] = clone;
        link[q] = clone;
        return cur;
      }
    
      void build() {
        queue<pair<int, int>> q;
        for (int i = 0; i < CHAR_NUM; ++i)
          if (next[0][i]) q.push({i, 0});
        while (!q.empty()) {
          auto item = q.front();
          q.pop();
          auto last = insertSAM(item.second, item.first);
          for (int i = 0; i < CHAR_NUM; ++i)
            if (next[last][i]) q.push({i, last});
        }
      }
    }
    ```

-   Since the parent node is always changing during the entire BFS process, we don't need to save the `last` pointer.
-   In the insert operation, `int cur = next[last][c];` differs from the normal suffix automaton's `int cur = tot++;` because the nodes we insert already exist in the tree structure, so we can directly retrieve them.
-   In the data copy after `clone`, there is such a judgment `next[clone][i] = len[next[q][i]] != 0 ? next[q][i] : 0;` which differs from the normal suffix automaton's direct assignment `next[clone][i] = next[q][i];`. This is to avoid updating values whose `len` is greater than the current node's `len`. Since in the array, `len` is only assigned after the node is traversed by BFS and inserted into the suffix automaton.

## Properties

1.  The structure of the generalized suffix automaton is consistent with the suffix automaton. Most properties of the suffix automaton apply to the generalized suffix automaton ([Properties of Suffix Automaton](./sam.md)).
2.  After building the generalized suffix automaton, the trie structure is usually destroyed, meaning the generalized suffix automaton cannot usually be used to solve trie problems. Of course, you can choose to prepare double the space and build the suffix automaton in another space.

## Applications

### Number of Different Substrings Across All Characters

Based on the properties of the suffix automaton, the number of substrings ending at node $i$ equals $len[i] - len[link[i]]$.

So we can iterate through all nodes and sum them up.

Problem: [【Template】Generalized Suffix Automaton (Generalized SAM)](https://www.luogu.com.cn/problem/P6139)

??? note "Reference Code"
    ```cpp
    --8<-- "docs/string/code/general-sam/general-sam_1.cpp"
    ```

### Longest Common Substring Among Multiple Strings

We need to build an array `flag` of length $k$ for each node (for this problem, it can be just a marker array; if we need to find the number of such substrings, we need to change it to a counting array).

When inserting strings into the trie, count all nodes and store them in the array for the current string.

Then traverse in decreasing order of `len`, and merge the `flag` of the current node with other nodes through suffix links.

Traverse all nodes and find one with the maximum `len` such that for all $k$, its `flag` value is non-zero. The `len` of this node is the answer.

Problem: [SPOJ Longest Common Substring II](https://www.spoj.com/problems/LCS2/)

??? note "Reference Code"
    ```cpp
    --8<-- "docs/string/code/general-sam/general-sam_2.cpp"
    ```