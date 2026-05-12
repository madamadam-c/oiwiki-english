???+ note "Tip"
    This article is still being edited and discussed. You are welcome to add more advanced learning paths or share your ideas in the comments!

This article introduces a learning roadmap for competitive programming.

This roadmap serves both as a guide for beginners learning competitive programming and as a review checklist.

## 1 C++ Language Basics

Start with C++ syntax and take it step by step.

### 1.1 Hello, World!

Begin your competitive programming journey with `Hello, World!`.

At the same time, learn what the general structure of a C++ source program looks like.

-   [Hello, World!](../lang/helloworld.md)
-   [C++ Syntax Basics](../lang/basic.md)

### 1.2 Variables and Operations

Computers were originally created for computation. Therefore, let's first learn how to complete some simple computational tasks.

-   [Variables](../lang/var.md)
-   [Operations](../lang/op.md)

### 1.3 Flow Control

#### 1.3.1 Branching Structures

Sometimes we need to choose different statements to execute under different conditions. In such cases, we need branch statements.

-   [Branches](../lang/branch.md)

Branch statements include the following types:

-   if statements
-   if-else statements
-   if-elif-else statements
-   switch statements

#### 1.3.2 Loop Structures

Loop statements are needed when several statements must be executed repeatedly.

-   [Loops](../lang/loop.md)

Loop statements include the following types:

-   for statements
-   while statements
-   do-while statements

### 1.4 Arrays and Structs

Arrays are used to store large amounts of data of the same type, while structs can bundle several variables together.

-   [Arrays](../lang/array.md)
-   [Structs](../lang/struct.md)

### 1.5 Functions and Recursion

Use functions to modularize programs and reduce implementation cost.

Recursion is a hurdle for beginners. "Calling itself" may not sound easy to understand, but if you examine it carefully, you will find that "calling itself" is not fundamentally different from "calling something else".

-   [Functions](../lang/func.md)
-   [Recursion & Divide and Conquer](../basic/divide-and-conquer.md)

## 2 CSP-J Beginner Level

### 2.1 Enumeration and Simulation

From now on, you can already use C++ to complete some simple tasks, but this is far from enough.

To solve some simple problems correctly, you need to learn how to implement code by enumerating cases or simulating the logic in your mind. This may not seem very efficient, but it is sometimes very useful.

-   [Enumeration](../basic/enumerate.md)
-   [Simulation](../basic/simulate.md)

### 2.2 Recursion and Divide and Conquer

Recursion refers to a method in which a function repeatedly calls itself in its definition; divide and conquer repeatedly decomposes a problem into several subproblems, solves them, and then combines the results.

-   [Recursion & Divide and Conquer](../basic/divide-and-conquer.md)

### 2.3 Strings

When solving informatics problems, one data type you will often encounter is the string. You need to learn some STL functions for operating on strings. Of course, simulation is also a good way to solve string problems.

-   [String Basics](../string/basic.md)
-   [STL Functions](../string/lib-func.md)

### 2.4 Sorting

When you obtain a set of data, how to turn it from unordered to ordered is also an important question. When you have no idea how to proceed, consider sorting the array. This is also the foundation of many algorithms that follow.

There are quite a few sorting methods, but after understanding them, they are not hard to remember.

-   [Introduction to Sorting](../basic/sort-intro.md)
-   [Selection Sort](../basic/selection-sort.md)
-   [Bubble Sort](../basic/bubble-sort.md)
-   [Insertion Sort](../basic/insertion-sort.md)
-   [Counting Sort](../basic/counting-sort.md)
-   [Radix Sort](../basic/radix-sort.md)
-   [Quicksort](../basic/quick-sort.md)
-   [Merge Sort](../basic/merge-sort.md)
-   [Heapsort](../basic/heap-sort.md)
-   [Bucket Sort](../basic/bucket-sort.md)
-   [Sorting-related STL](../basic/stl-sort.md)

The NOI syllabus only requires beginners to learn three sorting algorithms: selection sort, bubble sort, and insertion sort. However, the others are not very difficult and may appear in the preliminary round, so they are listed together here.

### 2.5 Binary Search and Binary Lifting

Binary search is essentially an application of divide and conquer: it continuously reduces the size of the search range until the answer is found. Note, however, that this search method must be applied to an ordered data structure.

-   [Binary Search](../basic/binary.md)

Binary lifting is different: it repeatedly doubles values to transform processing in a linear range into logarithmic processing, greatly optimizing time complexity. (This topic requires some mathematical background, so it is fine to skip it for now.)

-   [Binary Lifting](../basic/binary-lifting.md)

### 2.6 Search

At the beginner level, search problems often appear as maze problems and usually involve map-like data. In addition, search is often used to efficiently enumerate and construct valid solutions, and can also be used to gain partial credit.

#### 2.6.1 Depth-First Search (DFS)

Depth-first search refers to an algorithm that conveniently implements brute-force enumeration using recursive functions. It has some similarities to DFS in graph theory, but they are not exactly the same.

-   [DFS (Search)](../search/dfs.md)

#### 2.6.2 Breadth-First Search (BFS)

By designing each state as a point in a graph, you can carry out an exhaustive layer-by-layer search.

-   [BFS (Search)](../search/bfs.md)

#### 2.6.3 Search Optimization

Many problems can be solved with DFS, but the complexity of this algorithm is often clearly too high to pass. Therefore, some optimizations are needed to make it run faster. Such optimizations reduce attempts that cannot possibly succeed and are called "pruning". BFS-related optimizations are more flexible, but the basic idea is the same.

-   [DFS Pruning Optimization](../search/opt.md)

### 2.7 Introduction to Data Structures

#### 2.7.1 Linear Data Structures

Arrays, linked lists, queues, and stacks are all linear structures. Making good use of these structures can make many tasks convenient.

-   [Stack](../ds/stack.md)
-   [Queue](../ds/queue.md)
-   [Linked List](../ds/linked-list.md)

#### 2.7.2 Complex Data Structures

-   [Trees and Binary Trees](../graph/tree-basic.md)
-   [Graph Concepts](../graph/concept.md)
-   [Graph Storage](../graph/save.md)

### 2.8 Introduction to Dynamic Programming

Dynamic programming (DP) is a method for solving complex problems by decomposing the original problem into relatively simple subproblems.

Because dynamic programming is not a specific algorithm, but rather a method for solving certain problems, it appears across many kinds of data structures, and the types of related problems are more varied.

-   [Introduction to Dynamic Programming](../dp/index.md)

#### 2.8.1 Knapsack Problem

That is, given a knapsack with limited capacity, choose several items with weights and values to put into it, and determine how to maximize the total value. This is the first hurdle for many OIers; from here on, algorithms start to become somewhat difficult to understand.

-   [Knapsack DP](../dp/knapsack.md)

#### 2.8.2 Linear Dynamic Programming

In dynamic programming, one of the hardest parts is designing states, which requires construction-related techniques. Once you have written the states and transition equations, completing a dynamic programming problem is not difficult.

-   [Construction](../basic/construction.md)
-   [Dynamic Programming Basics](../dp/basic.md)

Memoized search is a search implementation that records information about states that have already been visited, thereby avoiding repeated traversal of the same state. Some problems can also use memoized search to reduce the difficulty of reasoning.

Because memoized search ensures that each state is visited only once, it is also a common implementation of dynamic programming.

-   [Memoized Search](../dp/memo.md)

#### 2.8.3 Complex Dynamic Programming

Interval dynamic programming is an extension of linear dynamic programming. When it divides a problem into stages, it is closely related to the order in which elements appear in a stage and which elements from the previous stage are merged.

-   [Interval DP](../dp/interval.md)

### 2.9 Mathematics

#### 2.9.1 High-Precision Algorithms

What if even long long (or int64) is not enough? Use high-precision algorithms. In essence, they simulate the four arithmetic operations.

-   [High-Precision Computation](../math/bignum.md)

#### 2.9.2 Base Conversion

In computers, besides binary, octal and hexadecimal are also commonly used. Sometimes learning to use the correct base is very helpful for solving problems.

-   [Numeral Systems](../math/numeral-sys/base.md)

#### 2.9.3 Bit Operations

Bit operations are operations based on the binary representation of integers. Since computers store data internally in binary, bit operations are quite fast.

There are 6 basic bit operations: bitwise AND, bitwise OR, bitwise XOR, bitwise NOT, left shift, and right shift.

-   [Bit Operations](../math/bit.md)

#### 2.9.4 Number Theory

-   [Number Theory Basics](../math/number-theory/basic.md)
-   [Prime Numbers](../math/number-theory/prime.md)
-   [Sieving Methods](../math/number-theory/sieve.md)
-   [Greatest Common Divisor](../math/number-theory/gcd.md)
-   [Euler's Totient Function](../math/number-theory/euler-totient.md)
-   [Prime Factorization](../math/number-theory/pollard-rho.md)

#### 2.9.5 Combinatorial Counting

-   [Permutations and Combinations](../math/combinatorics/combination.md)
-   [Pigeonhole Principle](../math/combinatorics/drawer-principle.md)
-   [Inclusion-Exclusion Principle](../math/combinatorics/inclusion-exclusion-principle.md)

***

At this point, you have finished learning all algorithms within the beginner-level scope. However, to master them, you need to continue solving enough problems to consolidate the knowledge points you have learned.
