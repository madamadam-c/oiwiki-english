This page briefly introduces two pointers.

## Introduction

Two pointers is a simple yet flexible technique and idea. Used alone, it can easily solve some specific problems; combined with other algorithms, it can also serve many different purposes.

As the name suggests, two pointers means using two pointers at the same time. In sequences and linked-list structures, they point to positions; in tree and graph structures, they point to nodes. By moving in the same direction or toward each other, they maintain and count information.

Next, we look at several specific uses of two pointers.

## Maintaining Interval Information

If not combined with other data structures, the simplest pattern for maintaining interval information with two pointers is to maintain information with some monotonicity, where adding and removing an element are both easy to handle, such as the sum of positive numbers or the product of positive integers.

### Example 1

???+ note "Example 1 [leetcode 713. Subarray Product Less Than K](https://leetcode-cn.com/problems/subarray-product-less-than-k/)"
    Given a positive integer array $\mathit{nums}$ of length $n$ and an integer $k$, find the number of contiguous subarrays whose product is less than $k$.
    
    Here, $1 \leq n \leq 3 \times 10^4, 1 \leq nums[i] \leq 1000, 0 \leq k \leq 10^6$.

#### Procedure

Let the two pointers be $l,r$, and set another variable $\mathit{tmp}$ to record the product of all numbers in $[l,r]$. Initially both $l,r$ are at the far left. First move $r$ to the right until the first time $\mathit{tmp}\geq k$ is found. Then fix $r$ and move $l$ to the right until $\mathit{tmp}\lt k$. For each $r$, $l$ is the left boundary it can extend to. Because of the monotonicity of the product of positive integers, the number of intervals ending at $r$ that satisfy the condition is $r-l+1$.

#### Implementation

```cpp
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
  long long ji = 1ll, ans = 0;
  int l = 0;
  for (int i = 0; i < nums.size(); ++i) {
    ji *= nums[i];
    while (l <= i && ji >= k) ji /= nums[l++];
    ans += i - l + 1;
  }
  return ans;
}
```

Using two pointers to maintain interval information can also be combined with other data structures such as difference arrays, monotonic queues, segment trees, persistent segment trees, and so on. Mo's algorithm also incorporates the two-pointer technique: after sorting queries offline, it usually uses two pointers to record the current interval to process, gradually updating interval information as the pointers move step by step.

### Example 2

Next, consider an example that uses two pointers on a tree together with tree difference:

???+ note "Example 2 [luogu P3066 Running Away From the Barn G](https://www.luogu.com.cn/problem/P3066)"
    Given a rooted tree with $n$ nodes. Edges have weights, nodes are numbered from 1 to $n$, and node 1 is the root. Given a parameter $t$, for every node $u$ in the tree, find how many nodes in the subtree of $u$ have distance to $u$ no greater than $t$. Data range: $1\leq n \leq 2\times 10^5,1 \leq t \leq 10^{18},1 \leq p_i \lt i,1 \leq w_i \leq 10^{12}$

#### Procedure

Traverse the whole tree with DFS from the root, using a stack to record the chain from the root to the current node. Let one pointer $u$ point to the current node, and another pointer $p$ point to the shallowest node among nodes whose distance to $u$ is at most $t$. Record the distance to the root, and use binary search each time to determine $p$. At this point, $u$ contributes to every node on the path from $p$ to $u$, which can be recorded using tree difference.
Do not move $p$ by brute force directly, otherwise the time complexity may degrade to $O(n^2)$.

### Exercises

[leetcode 1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit](https://leetcode-cn.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/)

## Subsequence Matching

???+ note "Example 3 [leetcode 524. Longest Word in Dictionary through Deleting](https://leetcode-cn.com/problems/longest-word-in-dictionary-through-deleting/)"
    Given a string $s$ and a string array $\mathit{dictionary}$ as a dictionary, find and return the longest string in the dictionary that can be obtained by deleting some characters from $s$.

### Procedure

This type of problem requires matching strings $s$ and $t$ to determine whether $t$ is a subsequence of $s$. To solve it, put one pointer $i$ at the start of $s$ and another pointer $j$ at the start of $t$. If $s[i]=t[j]$, then the $j$-th character of $t$ has found its first corresponding match in $s$, so we can continue checking the following part, and both $i$ and $j$ increase by one. If the equality does not hold, then the $j$-th character of $t$ has still not been matched, so only increment $i$ and continue searching in the later part of $s$. Finally, if $j$ has moved past the end position, the whole string can be matched, meaning $t$ is a subsequence of $s$; otherwise it is not.

### Implementation

```cpp
string findLongestWord(string s, vector<string>& dictionary) {
  sort(dictionary.begin(), dictionary.end());
  int mx = 0, r = 0;
  string ans = "";
  for (int i = dictionary.size() - 1; i >= 0; i--) {
    r = 0;
    for (int j = 0; j < s.length(); ++j) {
      if (s[j] == dictionary[i][r]) r++;
    }
    if (r == dictionary[i].length()) {
      if (r >= mx) {
        mx = r;
        ans = dictionary[i];
      }
    }
  }
  return ans;
}
```

This method, where two pointers point to different objects and compare step by step, can also be used in some DP problems.

## Using Sequence Order

Many times, two pointers can correctly achieve the goal on a sequence because of certain properties of the sequence. The most common property is sequence order.

???+ note "Example 4 [leetcode 167. Two Sum II - Input Array Is Sorted](https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/)"
    Given an integer array `numbers` sorted in **ascending order**, find two numbers in the array whose sum equals the target value `target`.

### Procedure

This is also a classic application of two pointers. Although binary search is also convenient, it adds an extra $\log{n}$ factor in time complexity, and the code is less concise.

Now introduce the two-pointer method. Since we need to find two numbers and they cannot be at the same position, their positions must be one on the left and one on the right. Since the sum of the two numbers is fixed, the larger the smaller number is, the smaller the larger number must be. Considering these properties, we can approach them from both ends.

First assume the answer is positions 1 and n. If $num[1]+num[n]\gt \mathit{target}$, it means one of the two elements must become smaller. Since $\mathit{num}[1]$ cannot become smaller, move the pointer at $n$ left by one to make the larger number smaller.

Similarly, if $num[1]+num[n]\lt \mathit{target}$, it means one of the two elements must become larger. Since $\mathit{num}[n]$ cannot become larger, move the pointer at 1 right by one to make the smaller number larger.

In the general case, suppose the two pointers are at $l,r$ and $l\lt r$. If $num[l]+num[r]\gt \mathit{target}$, decrease $r$ by one; if $num[l]+num[r]\lt \mathit{target}$, increase $l$ by one. In this way, $l$ keeps moving right and $r$ keeps moving left, and eventually the two pointers approach an answer.

### Implementation

```cpp
vector<int> twoSum(vector<int>& numbers, int target) {
  int r = numbers.size() - 1, l = 0;
  vector<int> ans;
  ans.clear();
  while (l < r) {
    if (numbers[l] + numbers[r] > target)
      r--;
    else if (numbers[l] + numbers[r] == target) {
      ans.push_back(l + 1), ans.push_back(r + 1);
      return ans;
    } else
      l++;
  }
  return ans;
}
```

In merge sort, merging two sorted arrays in $O(n+m)$ time is also a two-pointer method used under the condition that the arrays are ordered.

### Exercises

[leetcode 15. 3Sum](https://leetcode-cn.com/problems/3sum/)

## Finding a Cycle in a Singly Linked List

### Procedure

There are many ways to find a cycle in a singly linked list, but the fast-slow two-pointer method is one of the most concise. We introduce it below.

First, both pointers point to the head of the linked list. Let one pointer move one step at a time, and the other move two steps at a time. If they meet, there is a cycle; otherwise there is no cycle. The time complexity is $O(n)$.

If there is a cycle, how do we find the start of the cycle?

List the equations and observe. Suppose when the pointers meet, the slow pointer has walked $k$ steps in total and $l$ steps on the cycle (when the fast and slow pointers meet on the cycle, the slow pointer must not have completed a full cycle). The fast pointer has walked $2k$ steps. Let the cycle length be $C$. Then

$$
\begin{align}
& \ 2 k=n \times C+l+(k-l) \\
& \ k=n \times C \\
\end{align}
$$

At the first meeting, $n$ takes the minimum positive integer 1. That is, $k=C$. Using this equality, after the two pointers meet, move one pointer back to the head of the list, then let both pointers move one step at a time. The position where they meet again is the cycle start.

### Implementation

```cpp
--8<-- "docs/misc/code/two-pointer/two-pointer_1.cpp:core"
```

The time complexity is $O(n)$.
