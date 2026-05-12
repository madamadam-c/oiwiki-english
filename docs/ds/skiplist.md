A skip list is a search data structure invented by William Pugh. It supports fast search, insertion, and deletion of data.

The expected space complexity of a skip list is $O(n)$, and the expected time complexity of search, insertion, and deletion is $O(\log n)$.

## Basic Idea

As the name suggests, a skip list is a data structure similar to a linked list. More precisely, it is an improvement over an ordered linked list.

For convenience, all ordered linked lists discussed below are assumed to be sorted in **ascending** order.

Searching in an ordered linked list means comparing nodes one by one from the head until the value of the current node is greater than or equal to the target value. Clearly, this operation has complexity $O(n)$.

A skip list introduces the concept of **layers** on top of an ordered linked list. First, every layer of a skip list is an ordered linked list; in particular, the bottom layer is the original ordered linked list. Each node on layer $i$ has probability $p$ of appearing on layer $i+1$, where $p$ is a constant.

In a skip list with $n$ nodes, let the layer expected to contain $\frac{1}{p}$ elements be layer $L(n)$. It is easy to obtain $L(n) = \log_{\frac{1}{p}}n$.

Searching in a skip list starts from layer $L(n)$, compares horizontally until the next node of the current node is greater than or equal to the target node, and then moves down one layer. This process is repeated until the first layer is reached and no further operation can be performed. At that point, if the next node is the target node, the search succeeds; otherwise, the element does not exist. In this way, unnecessary comparisons are skipped during the search, so searching in a skip list is faster than searching in an ordered linked list. It can be proved that the average complexity of skip-list search is $O(\log n)$.

## Complexity Proof

### Space Complexity

For a node, the probability that its highest level is $i$ is $p^{i-1}(1 - p)$. Therefore, the expected number of levels of a skip list is $\sum_{i\ge 1} ip^{i - 1}(1-p) = \frac{1}{1 - p}$. Since $p$ is a constant, the **expected space complexity** of a skip list is $O(n)$.

In the worst case, the ordered linked list on every layer is the same as the original ordered linked list, so the **worst-case space complexity** of a skip list is $O(n \log n)$.

### Time Complexity

Analyze the search path backward. This process can be divided into two parts: climbing from the bottom layer to layer $L(n)$, and the subsequent operations. During the analysis, assume that the detailed information of a node is unknown before it is visited.

Suppose we are currently on layer $i$ at a node $x$. We do not know the maximum level of $x$ or the maximum level of the node to the left of $x$; we only know that the maximum level of $x$ is at least $i$. If the maximum level of $x$ is greater than $i$, the next step should move upward, which happens with probability $p$; if the maximum level of $x$ equals $i$, the next step should move left, which happens with probability $1-p$.

Let $C(i)$ be the expected cost of climbing up $i$ layers in an infinite skip list. Then:

$$
\begin{aligned}
C(0) & = 0 \\
C(i) & = (1-p)(1+C(i)) + p(1+C(i-1))
\end{aligned}
$$

Solving gives $C(i)=\frac{i}{p}$.

Thus, in a skip list of length $n$, the expected number of steps to climb from the bottom layer to layer $L(n)$ has upper bound $\frac{L(n) - 1}{p}$.

It remains to analyze how many more steps are needed after reaching layer $L(n)$. After reaching layer $L(n)$, the number of left moves is at most the total number of nodes on layer $L(n)$ and higher layers, whose expectation is $\frac{1}{p}$. Therefore, after reaching layer $L(n)$, the expected number of left moves has upper bound $\frac{1}{p}$. Similarly, the expected number of upward moves after reaching layer $L(n)$ also has upper bound $\frac{1}{p}$.

Therefore, the expected number of search steps in a skip list is $\frac{L(n) - 1}{p} + \frac{2}{p}$. Since $L(n)=\log_{\frac{1}{p}}n$, the **expected time complexity** of skip-list search is $O(\log n)$.

In the worst case, the ordered linked list on every layer is the same as the original ordered linked list, and the search process is equivalent to searching the ordered linked list on the top layer. Thus, the **worst-case time complexity** of skip-list search is $O(n)$.

Insertion and deletion each perform one search, record the nodes that need modification along the way, and finally complete the modification. Each layer needs to modify at most one node, and the expected number of levels of a skip list is $\log_{\frac{1}{p}}n$, so the **expected time complexity** of insertion and modification is also $O(\log n)$.

## Implementation Details

### Getting the Maximum Level of a Node

Simulate adding one more level with probability $p$, then take the minimum with the upper bound.

```cpp
int randomLevel() {
  int lv = 1;
  // MAXL = 32, S = 0xFFFF, PS = S * P, P = 1 / 4
  while ((rand() & S) < PS) ++lv;
  return min(MAXL, lv);
}
```

### Search

Search whether a node with key `key` exists in the skip list. In an implementation, two sentinel nodes can be used to reduce boundary-condition handling.

```cpp
V& find(const K& key) {
  SkipListNode<K, V>* p = head;

  // Find the last node on this layer whose key is less than key, then move down.
  for (int i = level; i >= 0; --i) {
    while (p->forward[i]->key < key) {
      p = p->forward[i];
    }
  }
  // It is still less than key, so move one more step forward.
  p = p->forward[0];

  // Successfully found the node.
  if (p->key == key) return p->value;

  // The node does not exist; return INVALID.
  return tail->value;
}
```

### Insertion

Insert node `(key, value)`. The insertion process first performs a search, records which nodes the new node should be inserted after, and finally performs the insertion. The last node on each layer whose key is less than `key` is the node that needs modification.

```cpp
void insert(const K &key, const V &value) {
  // Records the nodes that need modification.
  SkipListNode<K, V> *update[MAXL + 1];

  SkipListNode<K, V> *p = head;
  for (int i = level; i >= 0; --i) {
    while (p->forward[i]->key < key) {
      p = p->forward[i];
    }
    // The node to modify on layer i is p.
    update[i] = p;
  }
  p = p->forward[0];

  // If it already exists, modify it.
  if (p->key == key) {
    p->value = value;
    return;
  }

  // Get the maximum level of the new node.
  int lv = randomLevel();
  if (lv > level) {
    lv = ++level;
    update[lv] = head;
  }

  // Create a new node.
  SkipListNode<K, V> *newNode = new SkipListNode<K, V>(key, value, lv);
  // Insert the new node on layers 0 through lv.
  for (int i = lv; i >= 0; --i) {
    p = update[i];
    newNode->forward[i] = p->forward[i];
    p->forward[i] = newNode;
  }

  ++length;
}
```

### Deletion

Delete the node whose key is `key`. The deletion process first performs a search, records which nodes precede the node to delete, and finally performs the deletion. The last node on each layer whose key is less than `key` is the node that needs modification.

```cpp
bool erase(const K &key) {
  // Records the nodes that need modification.
  SkipListNode<K, V> *update[MAXL + 1];

  SkipListNode<K, V> *p = head;
  for (int i = level; i >= 0; --i) {
    while (p->forward[i]->key < key) {
      p = p->forward[i];
    }
    // The node to modify on layer i is p.
    update[i] = p;
  }
  p = p->forward[0];

  // The node does not exist.
  if (p->key != key) return false;

  // Delete from the bottom layer upward.
  for (int i = 0; i <= level; ++i) {
    // If this layer does not contain p, deletion is complete.
    if (update[i]->forward[i] != p) {
      break;
    }
    // Disconnect p.
    update[i]->forward[i] = p->forward[i];
  }

  // Reclaim memory.
  delete p;

  // Deleting a node may reduce the maximum level.
  while (level > 0 && head->forward[level] == tail) --level;

  // Skip-list length.
  --length;
  return true;
}
```

### Complete Code

The following code is a map implemented with a skip list. It has not been thoroughly tested and is for reference only.

??? note "Reference Code"
    ```cpp
    #include <cassert>
    #include <climits>
    #include <ctime>
    #include <iostream>
    #include <map>
    using namespace std;
    
    template <typename K, typename V>
    struct SkipListNode {
      int level;
      K key;
      V value;
      SkipListNode **forward;
    
      SkipListNode() {}
    
      SkipListNode(K k, V v, int l, SkipListNode *nxt = NULL) {
        key = k;
        value = v;
        level = l;
        forward = new SkipListNode *[l + 1];
        for (int i = 0; i <= l; ++i) forward[i] = nxt;
      }
    
      ~SkipListNode() {
        if (forward != NULL) delete[] forward;
      }
    };
    
    template <typename K, typename V>
    struct SkipList {
      static constexpr int MAXL = 32;
      static constexpr int P = 4;
      static constexpr int S = 0xFFFF;
      static constexpr int PS = S / P;
      static constexpr int INVALID = INT_MAX;
    
      SkipListNode<K, V> *head, *tail;
      int length;
      int level;
    
      SkipList() {
        srand(time(nullptr));
    
        level = length = 0;
        tail = new SkipListNode<K, V>(INVALID, 0, 0);
        head = new SkipListNode<K, V>(INVALID, 0, MAXL, tail);
      }
    
      ~SkipList() {
        delete head;
        delete tail;
      }
    
      int randomLevel() {
        int lv = 1;
        while ((rand() & S) < PS) ++lv;
        return MAXL > lv ? lv : MAXL;
      }
    
      void insert(const K &key, const V &value) {
        SkipListNode<K, V> *update[MAXL + 1];
    
        SkipListNode<K, V> *p = head;
        for (int i = level; i >= 0; --i) {
          while (p->forward[i]->key < key) {
            p = p->forward[i];
          }
          update[i] = p;
        }
        p = p->forward[0];
    
        if (p->key == key) {
          p->value = value;
          return;
        }
    
        int lv = randomLevel();
        if (lv > level) {
          lv = ++level;
          update[lv] = head;
        }
    
        SkipListNode<K, V> *newNode = new SkipListNode<K, V>(key, value, lv);
        for (int i = lv; i >= 0; --i) {
          p = update[i];
          newNode->forward[i] = p->forward[i];
          p->forward[i] = newNode;
        }
    
        ++length;
      }
    
      bool erase(const K &key) {
        SkipListNode<K, V> *update[MAXL + 1];
        SkipListNode<K, V> *p = head;
    
        for (int i = level; i >= 0; --i) {
          while (p->forward[i]->key < key) {
            p = p->forward[i];
          }
          update[i] = p;
        }
        p = p->forward[0];
    
        if (p->key != key) return false;
    
        for (int i = 0; i <= level; ++i) {
          if (update[i]->forward[i] != p) {
            break;
          }
          update[i]->forward[i] = p->forward[i];
        }
    
        delete p;
    
        while (level > 0 && head->forward[level] == tail) --level;
        --length;
        return true;
      }
    
      V &operator[](const K &key) {
        V v = find(key);
        if (v == tail->value) insert(key, 0);
        return find(key);
      }
    
      V &find(const K &key) {
        SkipListNode<K, V> *p = head;
        for (int i = level; i >= 0; --i) {
          while (p->forward[i]->key < key) {
            p = p->forward[i];
          }
        }
        p = p->forward[0];
        if (p->key == key) return p->value;
        return tail->value;
      }
    
      bool count(const K &key) { return find(key) != tail->value; }
    };
    
    int main() {
      SkipList<int, int> L;
      map<int, int> M;
    
      clock_t s = clock();
    
      for (int i = 0; i < 1e5; ++i) {
        int key = rand(), value = rand();
        L[key] = value;
        M[key] = value;
      }
    
      for (int i = 0; i < 1e5; ++i) {
        int key = rand();
        if (i & 1) {
          L.erase(key);
          M.erase(key);
        } else {
          int r1 = L.count(key) ? L[key] : 0;
          int r2 = M.count(key) ? M[key] : 0;
          assert(r1 == r2);
        }
      }
    
      clock_t e = clock();
      cout << "Time elapsed: " << (double)(e - s) / CLOCKS_PER_SEC << endl;
      // about 0.2s
    
      return 0;
    }
    ```

## Random-Access Optimization for Skip Lists

Accessing the $k$-th node in a skip list is equivalent to accessing the $k$-th node in the original ordered linked list. Clearly, this operation has time complexity $O(n)$, which is not good enough.

The random-access optimization for skip lists maintains, for every forward pointer, the length of that forward pointer. Suppose $A$ and $B$ are both nodes in the skip list, where $A$ is the $a$-th node and $B$ is the $b$-th node $(a < b)$, and the forward pointer of $A$ on some layer points to $B$. Then the length of this forward pointer is $b - a$.

Now, to access the $k$-th node in the skip list, start from the top layer and traverse that layer horizontally until the current node's position plus the length of its forward pointer on that layer is greater than or equal to $k$, then move down one layer. Repeat this process until the first layer is reached and no further operation can be performed. At that point, the current node is the $k$-th node in the skip list.

This makes it possible to quickly access the $k$-th element of a skip list. It can be proved that this operation has time complexity $O(\log n)$.

## References

1.  [Skip Lists: A Probabilistic Alternative to Balanced Trees](https://15721.courses.cs.cmu.edu/spring2018/papers/08-oltpindexes1/pugh-skiplists-cacm1990.pdf)
2.  [Skip List](https://en.wikipedia.org/wiki/Skip_list)
3.  [A Skip List Cookbook](http://cglab.ca/~morin/teaching/5408/refs/p90b.pdf)
