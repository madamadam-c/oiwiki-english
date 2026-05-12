author: FFjet, ChungZH, frank-xjh, hsfzLZH1, Xarfa, AndrewWayne, hcx1204

This page briefly introduces two bidirectional search algorithms: "simultaneous bidirectional search" and "meet in the middle".

## Simultaneous Bidirectional Search

### Definition

The basic idea of simultaneous bidirectional search is to start [BFS](./bfs.md) or [DFS](./dfs.md) simultaneously from the start point and end point in the state graph.

If the two search fronts meet, a feasible solution can be considered to have been found.

### Process

The steps of bidirectional BFS are:

```text
Add the start node and target node to queue q
Mark the start node as 1
Mark the target node as 2
while (queue q is not empty)
{
  Expand s new nodes from q.front()
  
  If a newly expanded node has already been marked with the other number
    then the two search fronts have met
    then end the loop
  
  If the new s nodes were expanded from the start node
    then mark these s nodes as 1 and enqueue them into q
  
  If the new s nodes were expanded from the target node
    then mark these s nodes as 2 and enqueue them into q
}
```

### Examples

???+ note "Example [Eight Puzzle](https://www.luogu.com.cn/problem/P1379)"
    On a $3\times 3$ board, there are eight tiles, each labeled with one of the numbers from $1$ to $8$. One cell on the board is empty, represented by $0$. Tiles adjacent to the empty cell can be moved into it. The problem is: given an initial layout (initial state) and a target layout (to simplify the problem, the target state is set to $123804765$), find a movement method with the minimum number of steps to transform the initial layout into the target layout.

??? note "Solution idea"
    It is easy to think of brute-force BFS. Using brute-force BFS for this problem will not time out. However, here we use it as an example of simultaneous bidirectional search. We can use two BFS searches: one searches forward from the start state, and the other searches backward from the target state. Alternating between the two BFS searches greatly reduces the size of the search tree. When one BFS reaches a state already reached by the other BFS, the answer is obtained.

??? note "Reference code"
    ```cpp
    --8<-- "docs/search/code/bidirectional/bidirectional_1.cpp"
    ```

## Meet in the middle

???+ warning "Warning"
    This section does not introduce [**binary search**](../basic/binary.md) (another Chinese translation of binary search is "half-interval search").

### Introduction

The meet in the middle algorithm has no single official Chinese translation; common translations include "half search", "bidirectional search", and "meeting halfway".

It is suitable when the input size is small, but not small enough for direct brute-force search.

### Process

The main idea of meet in the middle is to split the whole search process into two halves, search them separately, and finally merge the results of the two halves.

### Properties

The complexity of brute-force search is often exponential, while using meet in the middle can halve the exponent in the complexity, reducing it from $O(a^b)$ to $O(a^{b/2})$.

### Examples

???+ note "Example [USACO09NOV Lights](https://www.luogu.com.cn/problem/P2962)"
    There are $n$ lights. Each light is connected to several other lights, and each light has a switch. If you press the switch on a light, the on/off state of that light and all lights connected to it will change. Initially, all lights are off. You need to turn on all lights and find the minimum number of switch presses.
    
    $1\le n\le 35$．

??? note "Solution idea"
    If brute-force DFS is used to find the light-switch states for this problem, the time complexity is $O(2^{n})$, which clearly times out. However, if we use meet in the middle, the time complexity can be optimized to $O(n2^{n/2})$. Meet in the middle means first finding half of the states, namely the states reachable using only switches numbered from $1$ to $\mathrm{mid}$, and then finding the states reachable using only the other half of the switches. If the lights turned on by the first half and the second half are complementary, merging these two parts gives a way to turn on all lights. In the concrete implementation, store the states of the first half and the minimum number of switch presses needed to reach each state in a map. When searching the second half, each time a solution is found, merge it with the complementary first-half solution to update the answer.

??? note "Reference code"
    ```cpp
    --8<-- "docs/search/code/bidirectional/bidirectional_2.cpp"
    ```

## External Links

-   [What is meet in the middle algorithm w.r.t. competitive programming? - Quora](https://www.quora.com/What-is-meet-in-the-middle-algorithm-w-r-t-competitive-programming)
-   [Meet in the Middle Algorithm - YouTube](https://www.youtube.com/watch?v=57SUNQL4JFA)
