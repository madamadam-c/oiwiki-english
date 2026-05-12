## Building a Blocked Array

A blocked array divides an array into several blocks and stores aggregate information for each block. When a query touches incomplete blocks on the two ends, handle those parts by brute force. Usually, the block length is $O(\sqrt{n})$. For a detailed analysis, see Xu Mingkuan's paper *A Preliminary Study on Unconventional-Size Blocking Algorithms* in the 2017 National Training Team papers.

Here is one way to build a blocked array.

???+ note "Implementation"
    ```cpp
    num = sqrt(n);
    for (int i = 1; i <= num; i++)
      st[i] = n / num * (i - 1) + 1, ed[i] = n / num * i;
    ed[num] = n;
    for (int i = 1; i <= num; i++) {
      for (int j = st[i]; j <= ed[i]; j++) {
        belong[j] = i;
      }
      size[i] = ed[i] - st[i] + 1;
    }
    ```

Here `st[i]` and `ed[i]` are the start and end positions of a block, and `size[i]` is the size of the block.

## Storing and Modifying In-Block Information

### Example 1: [The Master's Magic](https://www.luogu.com.cn/problem/P2801)

There are two operations:

1.  For the interval $[x,y]$, add $z$ to every number.
2.  Query the number of elements in $[x,y]$ that are greater than or equal to $z$.

We need to query how many numbers in a block are at least a given value, so we use an array `t` to store the sorted values inside each block, while `a` is the original unsorted array. For whole-block modifications, use an approach similar to permanent lazy tags: the `delta` array records the value currently added to the entire block. Let $q$ be the total number of query and modification operations. The time complexity is $O(q\sqrt{n}\log n)$.

Use the `delta` array to record the whole-block addition for each block.

???+ note "Implementation"
    ```cpp
    void Sort(int k) {
      for (int i = st[k]; i <= ed[k]; i++) t[i] = a[i];
      sort(t + st[k], t + ed[k] + 1);
    }
    
    void Modify(int l, int r, int c) {
      int x = belong[l], y = belong[r];
      if (x == y)  // If the interval is inside one block, modify it directly
      {
        for (int i = l; i <= r; i++) a[i] += c;
        Sort(x);
        return;
      }
      for (int i = l; i <= ed[x]; i++) a[i] += c;     // Modify the starting fragment directly
      for (int i = st[y]; i <= r; i++) a[i] += c;     // Modify the ending fragment directly
      for (int i = x + 1; i < y; i++) delta[i] += c;  // Tag the middle whole blocks
      Sort(x);
      Sort(y);
    }
    
    int Answer(int l, int r, int c) {
      int ans = 0, x = belong[l], y = belong[r];
      if (x == y) {
        for (int i = l; i <= r; i++)
          if (a[i] + delta[x] >= c) ans++;
        return ans;
      }
      for (int i = l; i <= ed[x]; i++)
        if (a[i] + delta[x] >= c) ans++;
      for (int i = st[y]; i <= r; i++)
        if (a[i] + delta[y] >= c) ans++;
      for (int i = x + 1; i <= y - 1; i++)
        ans +=
            ed[i] - (lower_bound(t + st[i], t + ed[i] + 1, c - delta[i]) - t) + 1;
      // Use lower_bound to find the first value at least c in each middle whole block
      return ans;
    }
    ```

### Example 2: Ark on a Cold Night

There are two operations:

1.  Set every number in the interval $[x,y]$ to $z$.
2.  Query the number of elements in $[x,y]$ that are less than or equal to $z$.

Use the `delta` array to record the value to which the whole block is currently assigned. If a block has not been assigned as a whole, use a special value, such as `0x3f3f3f3f3f3f3f3fll`, to indicate that. For boundary blocks, call `pushdown` before querying to push the stored block information down to every element. Remember to `sort` again after assignment. Everything else is the same as in the previous problem.

???+ note "Implementation"
    ```cpp
    void Sort(int k) {
      for (int i = st[k]; i <= ed[k]; i++) t[i] = a[i];
      sort(t + st[k], t + ed[k] + 1);
    }
    
    void PushDown(int x) {
      if (delta[x] != 0x3f3f3f3f3f3f3f3fll)  // This value marks that the block has no whole-block assignment
        for (int i = st[x]; i <= ed[x]; i++) a[i] = t[i] = delta[x];
      delta[x] = 0x3f3f3f3f3f3f3f3fll;
    }
    
    void Modify(int l, int r, int c) {
      int x = belong[l], y = belong[r];
      PushDown(x);
      if (x == y) {
        for (int i = l; i <= r; i++) a[i] = c;
        Sort(x);
        return;
      }
      PushDown(y);
      for (int i = l; i <= ed[x]; i++) a[i] = c;
      for (int i = st[y]; i <= r; i++) a[i] = c;
      Sort(x);
      Sort(y);
      for (int i = x + 1; i < y; i++) delta[i] = c;
    }
    
    int Binary_Search(int l, int r, int c) {
      int ans = l - 1, mid;
      while (l <= r) {
        mid = (l + r) / 2;
        if (t[mid] <= c)
          ans = mid, l = mid + 1;
        else
          r = mid - 1;
      }
      return ans;
    }
    
    int Answer(int l, int r, int c) {
      int ans = 0, x = belong[l], y = belong[r];
      PushDown(x);
      if (x == y) {
        for (int i = l; i <= r; i++)
          if (a[i] <= c) ans++;
        return ans;
      }
      PushDown(y);
      for (int i = l; i <= ed[x]; i++)
        if (a[i] <= c) ans++;
      for (int i = st[y]; i <= r; i++)
        if (a[i] <= c) ans++;
      for (int i = x + 1; i <= y - 1; i++) {
        if (0x3f3f3f3f3f3f3f3fll == delta[i])
          ans += Binary_Search(st[i], ed[i], c) - st[i] + 1;
        else if (delta[i] <= c)
          ans += size[i];
      }
      return ans;
    }
    ```

## Practice

1.  [Point Updates and Range Queries](https://loj.ac/problem/130)
2.  [Range Updates and Range Queries](https://loj.ac/problem/132)
3.  [[Template] Segment Tree 2](https://www.luogu.com.cn/problem/P3373)
4.  [「Ynoi2019 Simulation Contest」Yuno loves sqrt technology III](https://www.luogu.com.cn/problem/P5048)
5.  [「Violet」Dandelion](https://www.luogu.com.cn/problem/P4168)
6.  [Writing Poems](https://www.luogu.com.cn/problem/P4135)
