## Definition

Trie, also known as a prefix tree. As the name suggests, it is a tree like a dictionary.

## Introduction

First, a diagram:

![trie1](./images/trie1.png)

We can see that this Trie uses edges to represent letters, and the path from the root node to a node on the tree represents a string. For example, $1\to4\to 8\to 12$ represents the string `caa`.

The structure of Trie is very easy to understand. We use $\delta(u,c)$ to represent the next node pointed to by character $c$ from node $u$, or the node representing the string formed by adding a character $c$ after the string represented by node $u$. (The range of $c$ depends on the size of the character set, not necessarily $0\sim 26$.)

Sometimes we need to mark which strings have been inserted into the Trie. We can simply mark the node representing this string after each insertion.

## Implementation

Here's a template using a struct:

=== "C++"
    ```cpp
    struct trie {
      int nex[100000][26], cnt;
      bool exist[100000];  // whether a string ends at this node
    
      void insert(char *s, int l) {  // insert string
        int p = 0;
        for (int i = 0; i < l; i++) {
          int c = s[i] - 'a';
          if (!nex[p][c]) nex[p][c] = ++cnt;  // if doesn't exist, add node
          p = nex[p][c];
        }
        exist[p] = true;
      }
    
      bool find(char *s, int l) {  // find string
        int p = 0;
        for (int i = 0; i < l; i++) {
          int c = s[i] - 'a';
          if (!nex[p][c]) return 0;
          p = nex[p][c];
        }
        return exist[p];
      }
    };
    ```

=== "Python"
    ```python
    class trie:
        def __init__(self):
            self.nex = [[0 for i in range(26)] for j in range(100000)]
            self.cnt = 0
            self.exist = [False] * 100000  # whether a string ends at this node
    
        def insert(self, s):  # insert string
            p = 0
            for i in s:
                c = ord(i) - ord("a")
                if not self.nex[p][c]:
                    self.cnt += 1
                    self.nex[p][c] = self.cnt  # if doesn't exist, add node
                p = self.nex[p][c]
            self.exist[p] = True
    
        def find(self, s):  # find string
            p = 0
            for i in s:
                c = ord(i) - ord("a")
                if not self.nex[p][c]:
                    return False
                p = self.nex[p][c]
            return self.exist[p]
    ```

=== "Java"
    ```java
    public class Trie {
        int[][] tree = new int[10000][26];
        int cnt = 0;
        boolean[] end = new boolean[10000];
        
        public void insert(String word) {
            int p = 0;
            char[] chars = word.toCharArray();
            for (int i = 0; i < chars.length; i++) {
                int c = chars[i] - 'a';
                if (tree[p][c] == 0) {
                    tree[p][c] = ++cnt;
                }
                p = tree[p][c];
            }
            end[p] = true;
        }
        
        public boolean find(String word) {
            int p = 0;
            char[] chars = word.toCharArray();
            for (int i = 0; i < chars.length; i++) {
                int c = chars[i] - 'a';
                if (tree[p][c] == 0) {
                    return false;
                }
                p = tree[p][c];
            }
            return end[p];
        }
    }
    ```

## Applications

### String Retrieval

The most basic application of Trie — finding whether a string exists in the "dictionary".

???+ note "[Thus His Incorrect Roll Call Begins](https://www.luogu.com.cn/problem/P2580)"
    You are given $n$ name strings, then perform $m$ roll calls. For each roll call, you need to answer one of: "name does not exist", "first time calling this name", "already called this name".
    
    $1\le n\le 10^4$, $1\le m\le 10^5$, all strings have length at most $50$.
    
    ??? note "Solution"
        Build a Trie for all names, then query in the Trie whether the string exists and whether the name has already been called. Mark as called on the first roll call.
    
    ??? note "Reference Code"
        ```cpp
        --8<-- "docs/string/code/trie/trie_1.cpp"
        ```

### AC Automaton

Trie is part of the [AC Automaton](./ac-automaton.md).

### Maintaining XOR Maximum

By treating the binary representation of numbers as a string, we can build a Trie with character set $\{0,1\}$.

???+ note "[BZOJ1954 Longest XOR Path](https://hydro.ac/p/bzoj-P1954)"
    Given a tree with edge weights, find $(u, v)$ such that the XOR sum of edge weights on the path from $u$ to $v$ is maximized, and output this maximum value. Here, the XOR sum refers to the XOR of all edge weights.
    
    The number of nodes does not exceed $10^5$, and edge weights are in $[0,2^{31})$.
    
    ??? note "Solution"
        Arbitrarily designate a root $root$. Let $T(u, v)$ represent the XOR sum of edge weights on the path between $u$ and $v$. Then $T(u,v)=T(root, u)\oplus T(root,v)$, because the parts above [LCA](../graph/lca.md) cancel out after XORing twice.
        
        Then, if we insert all $T(root, u)$ into a Trie, we can quickly find for each $T(root, u)$ the $T(root, v)$ that gives the maximum XOR sum with it:
        
        Starting from the root of the Trie, if we can move to a subtree whose bit is different from the current bit of $T(root, u)$, we move there; otherwise, we have no choice.
        
        Correctness of greedy: If we go this way, this bit is $1$; if we don't, this bit is $0$. And higher bits need to be made as large as possible first.
    
    ??? note "Reference Code"
        ```cpp
        --8<-- "docs/string/code/trie/trie_2.cpp"
        ```

### Maintaining XOR Sum

A 01-trie is a Trie with character set $\{0,1\}$. 01-trie can be used to maintain the XOR sum of some numbers, supporting modifications (deletion + reinsertion), and global addition (i.e., incrementing all maintained values by `1`, which is essentially a special modification operation).

To maintain XOR sum, we need to build the Trie from low bits to high bits.

**A convention**: in the text, when we say a node is **upward**, it refers to the path from the current node to the root; when we say a node is **downward**, it refers to the subtree of the current node.

#### Insertion & Deletion

To maintain XOR sum, we **only** need to know the **parity** of the count of `0` and `1` at each bit. That is, for the digit `1`, only when the count of digit `1` at this bit is odd, the digit at this bit is `1`. Please always keep this in mind: if we only maintain XOR sum, we only need to know the count of `1` at each bit, and we don't need to know which numbers the Trie actually maintains.

For each node, we need to record the following three values:

-   `ch[o][0/1]` refers to the two children of node `o`. `ch[o][0]` means the next bit is `0`, similarly `ch[o][1]` means the next bit is `1`.
-   `w[o]` refers to the count (weight) of values on the edge from node $o$ to its parent. When inserting a number $x$, the weights on the path of $x$'s binary decomposition in the Trie all increase by `+1`.
-   `xorv[o]` refers to the XOR sum maintained by the subtree rooted at $o`.

The specific code for maintaining nodes is as follows:

```cpp
void maintain(int o) {
  w[o] = xorv[o] = 0;
  if (ch[o][0]) {
    w[o] += w[ch[o][0]];
    xorv[o] ^= xorv[ch[o][0]] << 1;
  }
  if (ch[o][1]) {
    w[o] += w[ch[o][1]];
    xorv[o] ^= (xorv[ch[o][1]] << 1) | (w[ch[o][1]] & 1);
  }
  // w[o] = w[o] & 1;
  // only need to know parity, not the specific value. Of course, this line can be removed because we only use its parity above.
}
```

The code for insertion and deletion is very similar.

The points to note are:

-   Here, `MAXH` refers to the depth of the Trie, which forces every leaf node to have the same distance to the root. For some relatively small values, sometimes we don't need to build this deep (for example, if inserting the number `4`, after decomposing into binary as `100`, we only need to insert these three bits `001` from the root). However, we force the insertion of `MAXH` bits. The purpose of this is to facilitate handling carry during global `+1`. For example: if the original number is `3` (`11`), after incrementing it becomes `4` (`100`). If we only inserted 2 bits when inserting `3`, the carry here would be lost.
-   For insertion and deletion, we only need to modify the `w[]` of leaf nodes, and maintain them along the way during backtracking.

???+ note "Implementation"
    ```cpp
    namespace trie {
    constexpr int MAXH = 21;
    int ch[_ * (MAXH + 1)][2], w[_ * (MAXH + 1)], xorv[_ * (MAXH + 1)];
    int tot = 0;
    
    int mknode() {
      ++tot;
      ch[tot][1] = ch[tot][0] = w[tot] = xorv[tot] = 0;
      return tot;
    }
    
    void maintain(int o) {
      w[o] = xorv[o] = 0;
      if (ch[o][0]) {
        w[o] += w[ch[o][0]];
        xorv[o] ^= xorv[ch[o][0]] << 1;
      }
      if (ch[o][1]) {
        w[o] += w[ch[o][1]];
        xorv[o] ^= (xorv[ch[o][1]] << 1) | (w[ch[o][1]] & 1);
      }
      w[o] = w[o] & 1;
    }
    
    void insert(int &o, int x, int dp) {
      if (!o) o = mknode();
      if (dp > MAXH) return (void)(w[o]++);
      insert(ch[o][x & 1], x >> 1, dp + 1);
      maintain(o);
    }
    
    void erase(int o, int x, int dp) {
      if (dp > 20) return (void)(w[o]--);
      erase(ch[o][x & 1], x >> 1, dp + 1);
      maintain(o);
    }
    }  // namespace trie
    ```

#### Global Addition

Global addition means incrementing all values in this Trie by `1`.

Formally, let the values maintained in the Trie be $V_1, V_2, V_3 \dots V_n$. After global addition, the maintained values should become $V_1+1, V_2+1, V_3+1 \dots V_n+1$.

```cpp
void addall(int o) {
  swap(ch[o][0], ch[o][1]);
  if (ch[o][0]) addall(ch[o][0]);
  maintain(o);
}
```

##### Process

Let's think about how `+1` works in binary.

We only need to find the first `0` from low to high, change it to `1`, and then change all `1`s after this position to `0`.

Below are some examples to get a feel (the numbers in parentheses represent their corresponding decimal values):

    1000(8)  + 1 = 1001(9)  ;
    10011(19) + 1 = 10100(20) ;
    11111(31) + 1 = 100000(32);
    10101(21) + 1 = 10110(22) ;
    100000000111111(16447) + 1 = 100000001000000(16448);

Corresponding to Trie operations, it's just swapping its left and right children, and then recursively following the `0` edge after the swap.

Recall the definition of `w[o]`: `w[o]` refers to the count (weight) of values on the edge from node $o$ to its parent.

Does this definition feel a bit strange? If we store the edge weights from the parent node to its two children in the parent node, it might be closer to convention. But here, during swapping of left and right children, storing the distance from the child node to the parent is clearly more convenient.

### 01-trie Merging

This refers to merging the two 01-tries mentioned above, while merging the maintained information.

There might be relatively few articles about merging tries. In fact, merging tries is very similar to merging segment trees. You can search "merging segment trees" to learn how to merge tries.

Actually, merging tries is very simple. Consider that we have a function `int merge(int a, int b)` that takes two node numbers at the same relative position in two tries, and after merging, returns the merged node number.

#### Process

How to implement it?

Three cases:

-   If `a` doesn't have a node at this position, the newly merged node is `b`.
-   If `b` doesn't have a node at this position, the newly merged node is `a`.
-   If both `a` and `b` exist, we merge the information of `b` into `a`, and the newly merged node is `a`. Then we recursively handle the left and right children of `a`.

    **Hint**: If the required merge is to merge a and b into a new tree, we can create a new node and merge into this new node. The code here only merges the information of b into a.

#### Implementation

```cpp
int merge(int a, int b) {
  if (!a) return b;  // if a doesn't have a node at this position, return b
  if (!b) return a;  // if b doesn't have a node at this position, return a
  /*
    If both `a` and `b` exist,
    merge the information of `b` into `a`.
  */
  w[a] = w[a] + w[b];
  xorv[a] ^= xorv[b];
  /* Don't use maintain(),
     maintain() merges information of a's two children
     but here we need to merge information of a and b two nodes
   */
  ch[a][0] = merge(ch[a][0], ch[b][0]);
  ch[a][1] = merge(ch[a][1], ch[b][1]);
  return a;
}
```

In fact, all tries can be merged. In other words, trie merging is not limited to 01-trie.

???+ note "[【luogu-P6018】【Ynoi2010】Fusion tree](https://www.luogu.com.cn/problem/P6018)"
    You are given a tree with $n$ nodes, each node has a weight. There are $m$ operations.
    The following operations need to be supported:
    
    -   Add $1$ to the weights of all nodes at distance $1$ from a node $x$. Here, the distance between two nodes on a tree is defined as the number of edges on the shortest path from one node to the other.
    
    -   Subtract $v$ from the weight at a node $x$.
    
    -   Query the XOR sum of weights of all nodes at distance $1$ from a node $x$.
        For $100\%$ of the data, $1\le n \le 5\times 10^5$, $1\le m \le 5\times 10^5$, $0\le a_i \le 10^5$, $1 \le x \le n$, $opt\in\{1,2,3\}$.
        It is guaranteed that each node's weight is non-negative at any time.
    
    ??? note "Solution"
        Build a Trie at each node to maintain the weights of its children. The Trie should support global addition.
        Lazy tags can be used on each node to mark the increment of children's weights.
    
    ??? note "Reference Code"
        ```cpp
        --8<-- "docs/string/code/trie/trie_3.cpp"
        ```

???+ note "[【luogu-P6623】【Provincial Contest 2020 A Volume】Tree](https://www.luogu.com.cn/problem/P6623)"
    Given a rooted tree $T$ with $n$ nodes, nodes are numbered starting from $1$, and the root is node $1$. Each node has a positive integer weight $v_i$.
    Let the node numbers in the subtree of node $x$ (including $x$ itself) be $c_1, c_2, \dots, c_k$. Define the value of $x$ as:
    $val(x)=(v_{c_1}+d(c_1,x)) \oplus (v_{c_2}+d(c_2,x)) \oplus \cdots \oplus (v_{c_k}+d(c_k, x))$ where $d(x,y)$ represents the number of edges on the unique simple path between node $x$ and node $y$ on the tree, and $d(x,x) = 0$. $\oplus$ represents XOR operation.
    Please compute the result of $\sum\limits_{i=1}^n val(i)$.
    
    ??? note "Solution"
        Consider each node's contribution to all its ancestors.
        Build a Trie at each node, initially only storing that node's weight. Then merge the tries from each child node from bottom to top, then do global addition. After completion, count the answer.
    
    ??? note "Reference Code"
        ```cpp
        constexpr int _ = 526010;
        int n;
        int V[_];
        int debug = 0;
        
        namespace trie {
        constexpr int MAXH = 21;
        int ch[_ * (MAXH + 1)][2], w[_ * (MAXH + 1)], xorv[_ * (MAXH + 1)];
        int tot = 0;
        
        int mknode() {
          ++tot;
          ch[tot][1] = ch[tot][0] = w[tot] = xorv[tot] = 0;
          return tot;
        }
        
        void maintain(int o) {
          w[o] = xorv[o] = 0;
          if (ch[o][0]) {
            w[o] += w[ch[o][0]];
            xorv[o] ^= xorv[ch[o][0]] << 1;
          }
          if (ch[o][1]) {
            w[o] += w[ch[o][1]];
            xorv[o] ^= (xorv[ch[o][1]] << 1) | (w[ch[o][1]] & 1);
          }
          w[o] = w[o] & 1;
        }
        
        void insert(int &o, int x, int dp) {
          if (!o) o = mknode();
          if (dp > MAXH) return (void)(w[o]++);
          insert(ch[o][x & 1], x >> 1, dp + 1);
          maintain(o);
        }
        
        int merge(int a, int b) {
          if (!a) return b;
          if (!b) return a;
          w[a] = w[a] + w[b];
          xorv[a] ^= xorv[b];
          ch[a][0] = merge(ch[a][0], ch[b][0]);
          ch[a][1] = merge(ch[a][1], ch[b][1]);
          return a;
        }
        
        void addall(int o) {
          swap(ch[o][0], ch[o][1]);
          if (ch[o][0]) addall(ch[o][0]);
          maintain(o);
        }
        }  // namespace trie
        
        int rt[_];
        long long Ans = 0;
        vector<int> E[_];
        
        void dfs0(int o) {
          for (int i = 0; i < E[o].size(); i++) {
            int node = E[o][i];
            dfs0(node);
            rt[o] = trie::merge(rt[o], rt[node]);
          }
          trie::addall(rt[o]);
          trie::insert(rt[o], V[o], 0);
          Ans += trie::xorv[rt[o]];
        }
        
        int main() {
          n = read();
          for (int i = 1; i <= n; i++) V[i] = read();
          for (int i = 2; i <= n; i++) E[read()].push_back(i);
          dfs0(1);
          printf("%lld", Ans);
          return 0;
        }
        ```

### Persistent Trie

See [Persistent Trie](../ds/persistent-trie.md).