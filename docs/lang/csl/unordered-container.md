## Overview

Since the C++11 standard, four unordered associative containers implemented with [hashing](../../ds/hash.md) have officially been included in the C++ Standard Template Library: `unordered_set`, `unordered_multiset`, `unordered_map`, and `unordered_multimap`.

??? note "Usage when the compiler does not support C++11"
    Before C++11, unordered associative containers were part of the C++ TR1 extension. Therefore, if the compiler does not support C++11, add the `tr1/` prefix to header names and use the `std::tr1` namespace. For example, `#include <unordered_map>` should be changed to `#include <tr1/unordered_map>`, and `std::unordered_map` should be changed to `std::tr1::unordered_map` (or `tr1::unordered_map` if `using namespace std;` is used).

They share many functions and features with the corresponding associative containers. The biggest difference is that ordinary associative containers are generally implemented with red-black trees and store elements in a specific order, while these unordered associative containers store elements by hashing. Their internal elements are not sorted in any specific order, so no access order is guaranteed when traversing them.

Hash-based storage allows unordered associative containers to complete most operations, including lookup, insertion, and deletion, in constant time **on average**, which is better than the logarithmic complexity of associative containers.

??? warning "Warning"
    In the worst case, operations such as insertion, deletion, and lookup on unordered associative containers have time complexity **linear in the container size**. This often happens when many hash collisions occur in the container.
    
    At the same time, operations on unordered associative containers often have large constant factors, so their efficiency is sometimes not much better than that of ordinary associative containers.
    
    Therefore, use unordered associative containers carefully and avoid abusing them, such as using `unordered_map<int, int>` as an ordinary array with unlimited space just to avoid discretization.

Because unordered associative containers share many use cases and operations with the corresponding associative containers, this page does not introduce their operations in detail. Readers can refer to [Associative Containers](./associative-container.md).

## Creating Hash Collisions

As mentioned above, in the worst case, some operations on unordered associative containers have time complexity linear in the container size.

When the hash function is fixed, data can be constructed to create many hash collisions in the container, causing the complexity to reach its upper bound.

In the standard library implementation, each element's hash value is obtained by taking the value modulo a prime number. More specifically, the prime is from [this list](https://github.com/gcc-mirror/gcc/blob/releases/gcc-8.1.0/libstdc%2B%2B-v3/src/shared/hashtable-aux.cc). For compilers g++ 6 and earlier, this prime is usually $126271$; for g++ 7 and later, it is usually $107897$.

Therefore, inserting multiples of these moduli into the container can create many hash collisions.

## Custom Hash Functions

Using a custom hash function can effectively avoid many hash collisions caused by constructed data.

To use a custom hash function, define a struct and overload the `()` operator in it, like this:

```cpp
struct my_hash {
  size_t operator()(int x) const { return x; }
};
```

Of course, to make sure the hash function cannot be quickly broken, for example by hacks against submissions using unordered associative containers on Codeforces, you can add some randomization, such as time, to the hash function to make it harder to attack.

For example, [this blog](https://codeforces.com/blog/entry/62393) gives the following hash function:

```cpp
struct my_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM =
        chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }

  // Hash function for std::pair<int, int> as the key type
  size_t operator()(pair<uint64_t, uint64_t> x) const {
    static const uint64_t FIXED_RANDOM =
        chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x.first + FIXED_RANDOM) ^
           (splitmix64(x.second + FIXED_RANDOM) >> 1);
  }
};
```

After writing the custom hash function, pass it to the container with definitions such as `unordered_map<int, int, my_hash> my_map;` or `unordered_map<pair<int, int>, int, my_hash> my_pair_map;`.
