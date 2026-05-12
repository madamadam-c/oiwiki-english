author: Ir1d, greyqz, yjl9903, partychicken, ChungZH, qq1010903229, Marcythm, Acfboy, shenshuaijie, Craneplayz

## Introduction

DFS stands for [Depth First Search](https://en.wikipedia.org/wiki/Depth-first_search), and is an algorithm used for traversing or searching trees or graphs. The term "depth first" means that we always try to go to deeper nodes first.

This algorithm is often discussed alongside BFS, but aside from both being able to traverse connected components of graphs, their uses are completely different, and there are few cases where the two algorithms can be used interchangeably.

DFS is often used to refer to search implemented with recursive functions, but they are actually different. For the search algorithm concept, please refer to [DFS (Search)](../search/dfs.md).

## Process

The most notable feature of DFS is its **recursive call to itself**. Similar to BFS, DFS marks visited nodes it has traversed, and when traversing the graph, it skips nodes that have already been marked to ensure **each node is visited only once**. A function that satisfies the above two rules is DFS in the broader sense.

Specifically, the general structure of DFS is as follows:

    DFS(v) // v can be a vertex in a graph, or an abstract concept such as a dp state
      mark v as visited
      for u in adjacent nodes of v
        if u has not been marked then
          DFS(u)
        end
      end
    end

The above code only contains the main structure necessary for DFS. Actual DFS will add some code on top of this to perform other operations using DFS properties.

## Properties

The time complexity of this algorithm is usually $O(n+m)$, and space complexity is $O(n)$, where $n$ represents the number of vertices and $m$ represents the number of edges. Note that the space complexity includes the stack space, and the stack space complexity is $O(n)$. This time complexity can only be achieved when traversing each edge in average $O(1)$ time, such as using forward stars or adjacency lists to store the graph; if using adjacency matrices, this complexity may not be achieved.

> Note: Currently, most programming competitions (including NOIP, most provincial selections, and events organized by CCF) support **unlimited stack space**, i.e., stack space is not separately limited, but the total memory space is still limited by the problem statement. However, most operating systems impose additional limits on stack space, so some methods are needed to remove the stack space limit when debugging locally.
>
> -   On Windows, the usual method is to add `-Wl,--stack=1000000000` in the **compilation options**, which means setting the stack space limit to 1000000000 bytes.
> -   On Linux, the usual method is to execute `ulimit -s unlimited` **in the terminal** before running the program, which means unlimited stack space. This only needs to be executed once for each terminal, and is effective for every subsequent program run.

## Implementation

### Stack Implementation

DFS can be implemented using a [Stack](../ds/stack.md) as a temporary container for nodes during traversal; this highly corresponds to BFS implemented using a [Queue](../ds/queue.md).

=== "C++"
    ```cpp
    vector<vector<int>> adj;  // adjacency list
    vector<bool> vis;         // record whether nodes have been traversed
    
    void dfs(int s) {
      stack<int> st;
      st.push(s);
      vis[s] = true;
    
      while (!st.empty()) {
        int u = st.top();
        st.pop();
    
        for (int v : adj[u]) {
          if (!vis[v]) {
            vis[v] = true;  // ensure no duplicate elements in the stack
            st.push(v);
          }
        }
      }
    }
    ```

=== "Python"
    ```python
    # adj : List[List[int]] adjacency list
    # vis : List[bool] record whether nodes have been traversed
    
    
    def dfs(s: int) -> None:
        stack = [s]  # use a list to simulate stack, add the starting point to the stack
        vis[s] = True  # the starting point is traversed
    
        while stack:  # continue while stack is not empty
            u = (
                stack.pop()
            )  # take and discard the last element (the top of the stack), can be understood as moving to this element
    
            for v in adj[u]:  # for each element v adjacent to u
                if not vis[v]:  # if v has not been visited before
                    vis[v] = True  # ensure no duplicate elements in the stack
                    stack.append(v)  # add v to the stack
    ```

### Recursive Implementation

The evaluation when a function calls itself recursively is like the order of adding and deleting elements from a stack. The virtual address space occupied by function calls is called the Call Stack. DFS can be implemented recursively.

Using [Adjacency List](./save.md#adjacency-list) as the graph storage method:

=== "C++"
    ```cpp
    vector<vector<int>> adj;  // adjacency list
    vector<bool> vis;         // record whether nodes have been traversed
    
    void dfs(const int u) {
      vis[u] = true;
      for (int v : adj[u])
        if (!vis[v]) dfs(v)
    }
    ```

=== "Python"
    ```python
    # adj : List[List[int]] adjacency list
    # vis : List[bool] record whether nodes have been traversed
    
    
    def dfs(u: int) -> None:
        vis[u] = True
        for v in adj[u]:
            if not vis[v]:
                dfs(v)
    ```

Using [Chain Forward Star](./save.md#chain-forward-star) as an example:

=== "C++"
    ```cpp
    void dfs(int u) {
      vis[u] = 1;
      for (int i = head[u]; i; i = e[i].x) {
        if (!vis[e[i].t]) {
          dfs(v);
        }
      }
    }
    ```

=== "Java"
    ```Java
    public void dfs(int u) {
        vis[u] = true;
        for (int i = head[u]; i != 0; i = e[i].x) {
            if (!vis[e[i].t]) {
                dfs(v);
            }
        }
    }
    ```

=== "Python"
    ```python
    def dfs(u):
        vis[u] = True
        i = head[u]
        while i:
            if vis[e[i].t] == False:
                dfs(v)
            i = e[i].x
    ```

### DFS Sequence

The DFS sequence is the sequence of node numbers visited during the DFS calls.

We observe that each subtree corresponds to a continuous segment (one interval) in the DFS sequence.

### Parenthesis Sequence

When entering a node during DFS, record a left parenthesis `(`. When exiting a node, record a right parenthesis `)`.

Each node appears twice. The depth difference between adjacent nodes is 1.

### DFS on General Graphs

For disconnected graphs, only the connected component containing the starting vertex can be accessed.

For connected graphs, the DFS sequence is generally not unique.

Note: The DFS sequence of a tree is also not unique.

During the DFS process, by recording which vertex each vertex was visited from, we can build a tree structure, called the DFS tree. The DFS tree is a spanning tree of the original graph.

[DFS Tree](./scc.md#dfs-tree) has many properties, such as being used to find [Strongly Connected Components](./scc.md).