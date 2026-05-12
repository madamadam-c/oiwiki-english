## Introduction

![](images/hashtable.svg)

A hash table, also called a hashtable, is a data structure that stores data in key-value form. Storing data in key-value form means that every key uniquely corresponds to some position in memory. Given the key to search for, its corresponding value can be found quickly. A hash table can be understood as an advanced array whose indices may be large integers, floating-point numbers, strings, or even structs.

## Hash Function

To map a key to a position in memory, we need to compute an index for the key, that is, determine where this piece of data should be placed. The function that computes an index from a key is called a hash function. For example, if the key is a person's ID number, the hash function could take the last four digits, or of course the first four digits. The commonly used "last digits of a phone number" in daily life is also a kind of hash function. In practical applications, keys may be more complex objects, such as floating-point numbers, strings, structs, and so on. In these cases, an appropriate hash function should be designed according to the specific situation. A hash function should be easy to compute and should make the computed indices as uniformly distributed as possible.

After we can compute an index for a key, we know where the value corresponding to each key should be placed. Suppose we use an array `a` to store data and the hash function is `f`; then the key-value pair `(key, value)` should be placed at `a[f(key)]`. Regardless of the key's type or range, `f(key)` is an integer within an acceptable range and can be used as an array index.

In OI, the most common case is probably when keys are integers. When the key range is small, the key can be used directly as an array index. But when the key range is large, for example integers in the range of $10^9$, a hash table is needed. Usually, the key modulo a relatively large prime is used as the index, that is, $f(x)=x \bmod M$ is used as the hash function.

Another common case is when the key is a string. Since strings cannot be used as array indices, and converting strings to numbers can also avoid repeated string comparisons, in OI we usually do not use strings directly as keys. Instead, we first compute the string's hash value and then insert that hash value as the key into the hash table. For string hashing, we usually use the idea of base conversion and imagine the string as a number in base $127$. Then, for every length-$n$ string $s$, we have:

$x = s_0 \cdot 127^0 + s_1 \cdot 127^1 + s_2 \cdot 127^2 + \dots + s_n \cdot 127^n$

We can take the resulting $x$ modulo $2^{64}$, which is the maximum value of `unsigned long long`. In this way, the natural overflow of `unsigned long long` is equivalent to a modulo operation, making implementation more convenient.

Although this method is simple, it is not perfect. Data can be constructed to make this method collide, meaning that two strings have the same value of $x$ after taking modulo $2^{64}$.
We can use double hashing: choose two large primes $a,b$. We consider two strings equal if and only if their hash values modulo both $a$ and $b$ are equal. This greatly reduces the probability of hash collisions.

## Collisions

If the hash function computes different indices for all keys, then we only need to place `(key, value)` at the corresponding position according to the index. In practice, however, two different keys often produce the same index through the hash function. In this case, we need methods to handle collisions. In OI, the most commonly used method is separate chaining.

### Separate Chaining

Separate chaining is also called open hashing.

Separate chaining creates a linked list at each place where data is stored. If multiple keys are indexed to the same place, we only need to put all of them into the linked list at that position. When querying, we need to scan the entire linked list at the corresponding position and compare each stored key with the queried key. If the index range is $1\ldots M$ and the hash table size is $N$, then one insertion/query needs an expected $O(\frac{N}{M})$ comparisons.

#### Implementation

=== "C++"
    ```cpp
    constexpr int SIZE = 1000000;
    constexpr int M = 999997;

    struct HashTable {
      struct Node {
        int next, value, key;
      } data[SIZE];

      int head[M], size;
    
      int f(int key) { return (key % M + M) % M; }
    
      int get(int key) {
        for (int p = head[f(key)]; p; p = data[p].next)
          if (data[p].key == key) return data[p].value;
        return -1;
      }
    
      int modify(int key, int value) {
        for (int p = head[f(key)]; p; p = data[p].next)
          if (data[p].key == key) return data[p].value = value;
      }
    
      int add(int key, int value) {
        if (get(key) != -1) return -1;
        data[++size] = Node{head[f(key)], value, key};
        head[f(key)] = size;
        return value;
      }
    };
    ```

=== "Python"
    ```python
    M = 999997
    SIZE = 1000000
    
    
    class Node:
        def __init__(self, next=None, value=None, key=None):
            self.next = next
            self.value = value
            self.key = key
    
    
    data = [Node() for _ in range(SIZE)]
    head = [0] * M
    size = 0
    
    
    def f(key):
        return key % M
    
    
    def get(key):
        p = head[f(key)]
        while p:
            if data[p].key == key:
                return data[p].value
            p = data[p].next
        return -1


    def modify(key, value):
        p = head[f(key)]
        while p:
            if data[p].key == key:
                data[p].value = value
                return data[p].value
            p = data[p].next


    def add(key, value):
        if get(key) != -1:
            return -1
        size = size + 1
        data[size] = Node(head[f(key)], value, key)
        head[f(key)] = size
        return value
    ```

Here is another wrapped template. It can be used like `map` and is relatively short.

```cpp
struct hash_map {  // hash table template

  struct data {
    long long u;
    int v, nex;
  };  // forward-star structure

  data e[SZ << 1];  // SZ is a const int indicating the size
  int h[SZ], cnt;

  int hash(long long u) { return (u % SZ + SZ) % SZ; }

  // The reason for using (u % SZ + SZ) % SZ instead of u % SZ is that
  // the % operator in C++ cannot convert negative numbers to positive ones.

  int& operator[](long long u) {
    int hu = hash(u);  // get the head pointer
    for (int i = h[hu]; i; i = e[i].nex)
      if (e[i].u == u) return e[i].v;
    return e[++cnt] = data{u, -1, h[hu]}, h[hu] = cnt, e[cnt].v;
  }

  hash_map() {
    cnt = 0;
    memset(h, 0, sizeof(h));
  }
};
```

Here, the `hash` function is designed for the key type and returns a linked-list head pointer for lookup. In this template, we write a hash table whose key-value pair type is `(long long, int)`, and it returns -1 when querying a key that does not exist. The function `hash_map()` is used for initialization when the object is defined.

### Closed Hashing

Closed hashing stores all records directly in the hash table. If a collision occurs, it continues probing according to some rule.

For example, in linear probing: if a collision occurs at `d`, then check `d + 1`, `d + 2`, and so on in order.

#### Implementation

```cpp
constexpr int N = 360007;  // N is the maximum number of elements that can be stored

class Hash {
 private:
  int keys[N];
  int values[N];

 public:
  Hash() { memset(values, 0, sizeof(values)); }

  int& operator[](int n) {
    // Return a reference to the corresponding Hash[Key]
    // A value of 0 is treated as empty; modify it to a nonzero value.
    int idx = (n % N + N) % N, cnt = 1;
    while (keys[idx] != n && values[idx] != 0) {
      idx = (idx + cnt * cnt) % N;
      cnt += 1;
    }
    keys[idx] = n;
    return values[idx];
  }
};
```

## Example Problems

[JLOI2011 Non-Repeating Numbers](https://www.luogu.com.cn/problem/P4305)
