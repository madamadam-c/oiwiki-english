author: Early0v0, frank-xjh, Great-designer, ksyx, qiqistyle, Tiphereth-A , Saisyc, shuzhouliu, Xeonacid, xyf007

This page briefly introduces enumeration algorithms.

## Introduction

Enumeration (English: Enumerate) is a problem-solving strategy that guesses answers based on existing knowledge.

The idea of enumeration is to continuously guess, try one by one from the set of possibilities, and then check whether the conditions of the problem are satisfied.

## Key Points

### Provide Solution Space

Establish a concise mathematical model.

When enumerating, think clearly: what are the possible cases? What elements need to be enumerated?

### Reduce Enumeration Space

What is the range of enumeration? Does all content need to be enumerated?

When using enumeration to solve problems, these two things must be thought through clearly, otherwise it will bring unnecessary time overhead.

### Choose Appropriate Enumeration Order

Depends on the problem. For example, in the example problem, if we are looking for the largest prime that satisfies the condition, naturally enumerating from large to small is more suitable.

## Example Problems

Below is an example of using enumeration to solve problems and optimizing the enumeration range.

??? note "Example Problem"
    Given an array where all elements are distinct and none are $0$. Find the number of pairs in the array whose sum is $0$.

??? note "Solution Idea"
    The code for enumerating two numbers can be easily written.
    
    === "C++"
        ```cpp
        for (int i = 0; i < n; ++i)
          for (int j = 0; j < n; ++j)
            if (a[i] + a[j] == 0) ++ans;
        ```
    
    === "Python"
        ```python
        for i in range(n):
            for j in range(n):
                if a[i] + a[j] == 0:
                    ans += 1
        ```
    
    === "Java"
        ```java
        for (int i = 0; i < n; ++i)
          for (int j = 0; j < n; ++j)
            if (a[i] + a[j] == 0) ++ans;
        ```
    
    Let's see how to optimize the enumeration range. Since the problem does not require the pair to be ordered, the answer is twice the ordered case (consider if `(a, b)` is an answer, then `(b, a)` is also an answer). For this situation, we only need to count the answer with order artificially required, and then multiply by $2$.
    
    Let's require the first number to appear in a later position. The code is as follows:
    
    === "C++"
        ```cpp
        for (int i = 0; i < n; ++i)
          for (int j = 0; j < i; ++j)
            if (a[i] + a[j] == 0) ++ans;
        ans *= 2;
        ```
    
    === "Python"
        ```python
        for i in range(n):
            for j in range(i):
                if a[i] + a[j] == 0:
                    ans += 1
        ans *= 2
        ```
    
    === "Java"
        ```java
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < i; ++j)
                if (a[i] + a[j] == 0) ++ans;
        ans *= 2;
        ```
    
    It is not difficult to see that the enumeration range of $j$ has been reduced here, reducing the time overhead of this code.
    
    We can further optimize on this basis.
    
    Must both numbers be enumerated? After enumerating one number, the condition of the problem has already determined the condition of other elements (the other number). If we can find a way to directly judge whether the number required by the problem exists, we can save the time of enumerating the second number. More advanced, when the data range allows, we can use a bucket[^1] to record the numbers we have traversed.
    
    === "C++"
        ```cpp
        --8<-- "docs/basic/code/enumerate/enumerate_1.cpp"
        ```
    
    === "Python"
        ```python
        met = [False] * (MAXN * 2 + 1)
        for i in range(n):
            if met[MAXN - a[i]]:
                ans += 1
            met[a[i] + MAXN] = True
        ans *= 2
        ```
    
    === "Java"
        ```java
        boolean[] met = new boolean[MAXN * 2 + 1];
        for (int i = 0; i < n; ++i) {
            if (met[MAXN - a[i]]) ++ans;
            met[MAXN + a[i]] = true;
        }
        ans *= 2;
        ```

### Complexity Analysis

-   Time Complexity Analysis: The requirement can be completed by traversing array $a$ once. When $n$ is large enough, the time complexity is $O(n)$.
-   Space Complexity Analysis: $O(n+\max\{|x|:x\in a\})$.

## Practice Problems

-   [2811: Lamp Off Problem - OpenJudge](http://bailian.openjudge.cn/practice/2811/)

## Footnotes

[^1]: [Bucket Sort](../basic/bucket-sort.md) and [Majority Element Problem](../misc/main-element.md#offline-algorithm) as well as [Explanation of bucket data structure on Stack Overflow](https://stackoverflow.com/questions/42399355/what-is-a-bucket-or-double-bucket-data-structure)