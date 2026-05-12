## Definition

Some [state compression DP](./state.md) problems require us to record connectivity information in the state. Such problems are commonly, and vividly, called plug DP, or connectivity state-compression DP. Examples include counting Hamiltonian paths on grid graphs, counting black-white colorings of a board in which cells of the same color form one connected component, and counting spanning trees of special graphs. These problems usually require encoding the connectivity of states and analyzing how connectivity changes during state transitions.

## Introduction

### Domino Tiling and Contour-Line DP

Before learning plug DP, it is useful to review a classic problem.

???+ note "Example [HDU 1400 - Mondriaan's Dream](https://acm.hdu.edu.cn/showproblem.php?pid=1400)"
    Problem statement: Tile an $N\times M$ board completely with $1\times 2$ or $2\times 1$ dominoes. Count the number of tilings.

When either $n$ or $m$ is small, this type of problem can be solved with [state compression DP](./state.md). If we divide stages by rows, let $dp(i,s)$ denote the number of ways after the first $i$ rows have been considered and the state of row $i$ is $s$. Each bit of state $s$ indicates whether the corresponding position has already been covered from the previous row.

![domino](./images/domino.svg)

Another way to divide stages is cell-by-cell DP, also called contour-line DP. Here $dp(i,j,s)$ denotes the number of ways after processing up to row $i$, column $j$, with current contour-line state $s$.

Although cell-by-cell DP adds one more dimension to the state, each transition takes only $O(1)$ time, so the overall time complexity is unchanged. Let $f_0$ denote the current-stage state array and $f_1$ the next-stage state array. Let $u = f_0(s)$ be the value of the currently enumerated state. Then the transitions are:

```cpp
if (s >> j & 1) {       // Already covered
  f1[s ^ 1 << j] += u;  // Place nothing
} else {                // Not yet covered
  if (j != m - 1 && (!(s >> j + 1 & 1))) f1[s ^ 1 << j + 1] += u;  // Place horizontally
  f1[s ^ 1 << j] += u;                                             // Place vertically
}
```

Observe that the equations for placing nothing and placing vertically can be merged.

??? note "Implementation"
    ```cpp
    #include <algorithm>
    #include <iostream>
    using namespace std;
    constexpr int N = 11;
    long long f[2][1 << N], *f0, *f1;
    int n, m;
    
    int main() {
      while (cin >> n >> m && n) {
        f0 = f[0];
        f1 = f[1];
        fill(f1, f1 + (1 << m), 0);
        f1[0] = 1;
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < m; ++j) {
            swap(f0, f1);
            fill(f1, f1 + (1 << m), 0);
    #define u f0[s]
            for (int s = 0; s < 1 << m; ++s)
              if (u) {
                if (j != m - 1 && (!(s >> j & 3))) f1[s ^ 1 << j + 1] += u;  // Place horizontally
                f1[s ^ 1 << j] += u;  // Place vertically or place nothing
              }
          }
        }
        cout << f1[0] << endl;
      }
    }
    ```

??? note "Exercise [SRM 671. Div 1 900 - BearDestroys](https://archive.topcoder.com/ProblemStatement/pm/14069)"
    Problem statement: Given an $n\times m$ matrix, each cell contains `E` or `S`.
    A scoring procedure is defined for a matrix. Scan cells in row-major order. If a cell has already been occupied by a domino, skip it.
    Otherwise, try to place a domino. If the placement direction goes outside the matrix or overlaps another domino, the placement fails; switch to the other option or skip.
    If the cell is `E`, first try to place a $1\times 2$ domino.
    If the cell is `S`, first try to place a $2\times 1$ domino.
    The score of a matrix is the number of dominoes finally placed.
    Find the sum of scores over all $2^{nm}$ matrices.

### Terminology

Stage: the order in which dynamic programming is performed. The result of a later stage depends only on previous stages, meaning there are no aftereffects. Many DP problems can be divided into stages in multiple ways. For example, in knapsack problems, we can usually divide stages by items or by capacity, depending on what the outer loop enumerates first. In domino tiling problems, stages may be divided by rows, columns, cells, diagonals, and so on.

Contour line: the boundary between decided states and undecided states.

![contour line](./images/contour_line.svg)

Plug: if a plug exists in a certain direction of a cell, it means this cell is connected to its adjacent cell in that direction.

![plug](./images/plug.svg)

## Path Model

### Multiple Cycles

#### Example

???+ note "Example [HDU 1693 - Eat the Trees](https://acm.hdu.edu.cn/showproblem.php?pid=1693)"
    Problem statement: Count the ways to cover an $N\times M$ board with several cycles, with some cells blocked.

Strictly speaking, the multiple-cycle problem is not really plug DP, because, as in the domino tiling problem above, we only need to record whether a plug exists and then merge and create plugs in pairs.

For a board of width $m$, the contour line has width $m+1$, because it contains $m$ upper plugs and $1$ left plug. Note that after finishing a row, the rightmost left plug is usually an illegal state. At the same time, we need to append the first left plug of the next row. This requires adjusting the current contour-line state, usually by left-shifting all states. We call this operation rolling, `roll()`.

??? note "Example Code"
    ```cpp
    --8<-- "docs/dp/code/plug/plug_1.cpp"
    ```

#### Exercises

??? note "Exercise [ZOJ 3466 - The Hive II](https://pintia.cn/problem-sets/91827364500/exam/problems/type/7?problemSetProblemId=91827368730)"
    Problem statement: Same as the previous problem, but the cells are hexagons.

### Single Cycle

#### Example

???+ note "Example [Andrew Stankevich Contest 16 - Problem F - Pipe Layout](https://codeforces.com/gym/100220)"
    Problem statement: Count the ways to cover an $N\times M$ board with one cycle.

In the state representation above, each time we merge a group of connected plugs, we create an independent cycle. Therefore, in this problem, we must also distinguish the connectivity between plugs. This has finally appeared! We need additional encoding for the state.

#### State Encoding

Common encoding schemes include bracket representation and minimal representation. Here we focus on minimal representation, which is more generally applicable. We use an integer array of length $m+1$ to record the state of each plug on the contour line. A value of $0$ means no plug exists, and connected plugs are marked with the same number.

The following two encodings represent the same state:

-   `0 3 1 0 1 3`
-   `0 1 2 0 2 1`

We map equivalent states to the lexicographically smallest representation. In the example above, `0 1 2 0 2 1` is the minimal representation.

We use array `b[]` to represent the plug states on the contour line. During minimal-representation encoding, `bb[]` records the smallest number each original number is mapped to. Note that $0$ means the plug does not exist and must not be mapped to another value.

??? note "Code Implementation"
    ```cpp
    int b[M + 1], bb[M + 1];
    
    int encode() {
      int s = 0;
      memset(bb, -1, sizeof(bb));
      int bn = 1;
      bb[0] = 0;
      for (int i = m; i >= 0; --i) {
    #define bi bb[b[i]]
        if (!~bi) bi = bn++;
        s <<= offset;
        s |= bi;
      }
      return s;
    }
    
    void decode(int s) {
      REP(i, m + 1) {
        b[i] = s & mask;
        s >>= offset;
      }
    }
    ```

Notice that plugs always appear and disappear in pairs. Therefore a state such as `0 1 2 0 1 2` is illegal. Legal states form a bracket sequence, and in practice legal states may be very sparse.

#### Handwritten Hash Table

In some [state compression DP](./state.md) problems, the legal states may be sparse, as in this problem. To optimize time and space complexity, we can use a hash table to store legal DP states. C++ programmers can use [std::unordered\_map](http://www.cplusplus.com/reference/unordered_map/unordered_map/), or write one manually. A handwritten table also lets us flexibly encapsulate the state-transition function inside it.

???+ note "Code Implementation"
    ```cpp
    constexpr int MaxSZ = 16796, Prime = 9973;
    
    struct hashTable {
      int head[Prime], next[MaxSZ], sz;
      int state[MaxSZ];
      long long key[MaxSZ];
    
      void clear() {
        sz = 0;
        memset(head, -1, sizeof(head));
      }
    
      void push(int s) {
        int x = s % Prime;
        for (int i = head[x]; ~i; i = next[i]) {
          if (state[i] == s) {
            key[i] += d;
            return;
          }
        }
        state[sz] = s, key[sz] = d;
        next[sz] = head[x];
        head[x] = sz++;
      }
    
      void roll() { REP(i, sz) state[i] <<= offset; }
    } H[2], *H0, *H1;
    ```

In the code above:

-   `MaxSZ` is an upper bound on the number of legal states. It can be estimated, or a more accurate value can be precomputed.
-   `Prime` is a large prime smaller than `MaxSZ`.
-   `head[]` stores the head pointers.
-   `next[]` stores pointers to following states.
-   `state[]` stores the node states.
-   `key[]` stores the node keys; in this problem, these are numbers of ways.
-   `clear()` is the initialization function. As in a handwritten adjacency list, we only need to initialize the head pointers.
-   `push()` is the state-transition function. Here `d` is a global variable, used for convenience, representing the increment contributed by each transition. If the state is found, add with `+=`; otherwise create a new node with state `s` and key `d`.
-   `roll()` rolls the contour line after a whole row has been processed.

For complexity analysis of hash tables, and the difference between open hashing and closed hashing, see the chapters on hash tables in [Introduction to Algorithms](../contest/resources.md#%E4%B9%A6%E7%B1%8D).

#### State Transitions

???+ note "Code Implementation"
    ```cpp
    REP(ii, H0->sz) {
      decode(H0->state[ii]);                  // Fetch and decode the state
      d = H0->key[ii];                        // Obtain the increment delta
      int lt = b[j], up = b[j + 1];           // Left plug, upper plug
      bool dn = i != n - 1, rt = j != m - 1;  // Lower plug, right plug
      if (lt && up) {                         // Both left and upper plugs exist
        if (lt == up) {                       // They come from the same connected component
          if (i == n - 1 &&
              j == m - 1) {  // They can be merged and close the cycle only at the last cell.
            push(j, 0, 0);
          }
        } else {  // Otherwise, the two connected components must be merged because this problem requires cycle coverage
          REP(i, m + 1) if (b[i] == lt) b[i] = up;
          push(j, 0, 0);
        }
      } else if (lt || up) {  // Exactly one of the left and upper plugs exists
        int t = lt | up;      // Get this plug
        if (dn) {             // It can extend downward
          push(j, t, 0);
        }
        if (rt) {  // It can extend to the right
          push(j, 0, t);
        }
      } else {           // Neither the left nor upper plug exists
        if (dn && rt) {  // Create a new pair of plugs
          push(j, m, m);
        }
      }
    }
    ```

??? note "Example Code"
    ```cpp
    --8<-- "docs/dp/code/plug/plug_2.cpp"
    ```

#### Exercises

??? note "Exercise [Ural 1519 - Formula 1](https://acm.timus.ru/problem.aspx?space=1&num=1519)"
    Problem statement: Count the ways to cover an $N\times M$ board with one cycle, with some cells blocked.

??? note "Exercise [USACO 5.4.4 - Betsy's Tours](https://hydro.ac/d/USACO/p/USACO544)"
    Problem statement: Given an $N\times N$ square grid ($N\le 7$), count the paths that start at the upper-left corner, end at the lower-left corner, and visit every cell. Although this is a single path, the fixed endpoints allow it to be transformed into a single-cycle problem.

??? note "Exercise [POJ 1739 - Tony's Tour](http://poj.org/problem?id=1739)"
    Problem statement: Given an $N\times M$ board, count the paths that start at the lower-left corner, end at the lower-right corner, and visit every cell, with some cells blocked.

??? note "Exercise [USACO 6.1.1 - Postal Vans](https://vjudge.net/problem/UVALive-2738)"
    Problem statement: Count the ways to cover a $4\times N$ board with one directed cycle. Big integers are required.

??? note "Exercise [HNOI 2007 - Magic Amusement Park](https://www.luogu.com.cn/problem/P3190)"
    Problem statement: Given an $n\times m$ grid graph with a weight in each cell, find any cycle that maximizes the sum of weights it passes through.

??? note "Exercise [ProjectEuler 393 - Migrating ants](https://projecteuler.net/problem=393)"
    Problem statement: Cover an $n\times n$ square grid with multiple cycles. If a tiling has $m$ cycles, its contribution to the answer is $2^m$. Find the sum of contributions over all tilings.

### Single Path

#### Example

???+ note "Example [ZOJ 3213 - Beautiful Meadow](https://pintia.cn/problem-sets/91827364500/exam/problems/type/7?page=22&problemSetProblemId=91827367895)"
    Problem statement: Given an $N\times M$ square grid ($N,M\le 8$) with a weight at each grid point, find a path that maximizes the sum of weights of the grid points it covers.

This is a standard single-path problem. In single-path problems, the encoded state may also contain independent plugs that cannot be paired. The state-transition function must additionally handle the creation, merging, and disappearance of independent plugs. Creating and removing independent plugs corresponds to the endpoints of the path, so such events occur at most twice, either once for creation and once for disappearance, or twice for creation followed by one merge. Otherwise the final result must contain multiple connected components.

We need to record the total number of such events in the state. This information can be encoded into the state. Note that extra information like this does not need to be rolled when the contour line is adjusted. Alternatively, we can add an extra dimension outside the `hashTable` array. The sample program below uses the latter approach.

#### State Transitions

???+ note "Code Implementation"
    ```cpp
    REP(i, n) {
      REP(j, m) {
        checkMax(ans, A[i][j]);  // The single-cell case must be handled separately
        if (!A[i][j]) continue;  // If there is an obstacle, skip it; the state array does not need to be rolled here
        swap(H0, H1);
        REP(c, 3)
        H1[c].clear();  // c is the total number of creation/disappearance events, at most 2
        REP(c, 3) REP(ii, H0[c].sz) {
          decode(H0[c].state[ii]);
          d = H0[c].key[ii] + A[i][j];
          int lt = b[j], up = b[j + 1];
          bool dn = A[i + 1][j], rt = A[i][j + 1];
          if (lt && up) {
            if (lt == up) {  // In a single-path problem, we cannot merge identical plugs.
              // Cannot deploy here...
            } else {  // One of the two plugs being merged may be independent, but the same code fragment can handle it
              REP(i, m + 1) if (b[i] == lt) b[i] = up;
              push(c, j, 0, 0);
            }
          } else if (lt || up) {
            int t = lt | up;
            if (dn) {
              push(c, j, t, 0);
            }
            if (rt) {
              push(c, j, 0, t);
            }
            // Case where one plug disappears. If it is an independent plug, this means disappearance;
            // if it is a paired plug, this is equivalent to creating an independent plug.
            // In either case, c must be increased by 1.
            if (c < 2) {
              push(c + 1, j, 0, 0);
            }
          } else {
            d -= A[i][j];
            H1[c].push(H0[c].state[ii]);
            d += A[i][j];    // Skip plug creation; this problem does not require full coverage
            if (dn && rt) {  // Create a pair of plugs
              push(c, j, m, m);
            }
            if (c < 2) {  // Create an independent plug
              if (dn) {
                push(c + 1, j, m, 0);
              }
              if (rt) {
                push(c + 1, j, 0, m);
              }
            }
          }
        }
      }
      REP(c, 3) H1[c].roll();  // End of a row; adjust the contour line
    }
    ```

??? note "Example Code"
    ```cpp
    --8<-- "docs/dp/code/plug/plug_3.cpp"
    ```

#### Exercises

??? note "Exercise [BZOJ 2310 - ParkII](https://hydro.ac/p/bzoj-P2310)"
    Problem statement: Given an $m\times n$ board with a weight at each grid point, find a path cover that maximizes the sum of weights of the points on the path.

??? note "Exercise [NOI 2010 Day2 - Travel Route](https://www.luogu.com.cn/problem/P1933)"
    Problem statement: Given an $n\times m$ board, each cell has a 01 weight T\[x]\[y]. Find a path cover satisfying:
    
    -   The $i$-th visited grid point $(x, y)$ satisfies T\[x]\[y]= L\[i]
    -   One endpoint of the path lies on the boundary of the board
    
    Count the feasible solutions.

## Coloring Model

Besides path models, there is another common model: coloring a board, where adjacent nodes of the same color are considered connected. In path problems, state transitions enumerate the direction of the current path. In coloring problems, we enumerate the color assigned to the current node. In the coloring model, a connected component in the state may contain more than two nodes. Overall, however, the idea remains largely the same. Let us look at a classic example.

### Example: UVa 10572 - Black & White

???+ note "Example [UVa 10572 - Black & White](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1513)"
    Problem statement: Color the uncolored grid points of an $N\times M$ board black or white so that all black regions are connected and all white regions are connected, and no $2\times 2$ sub-rectangle has all cells of the same color (the situation in the figure below is illegal). Count the legal colorings and construct one legal coloring.
    
    ![black\_and\_white1](./images/black_and_white1.svg)

### State Encoding

First consider state encoding. If connectivity is ignored, this is [SGU 197. Nice Patterns Strike Back](https://codeforces.com/problemsets/acmsguru/problem/99999/197), which is easy to solve directly with [state compression DP](./state.md). Now we need the state to represent both color and connectivity. Looking at each position on the contour line, every `Offset` bits in the binary representation describe one position on the contour line. Since there are only two colors, we use the parity of the lowest bit to represent the color, and the remaining bits to represent connectivity.

For nodes above the first row and nodes to the left of the first column, we could introduce a third color to avoid special cases. Here, however, the connectivity information of these boundary states must be 0, so there is no need to encode a third color separately.

In path problems, the contour line consists of $m$ upper plugs and $1$ left plug. In this problem, because we also need to determine whether the $2\times 2$ sub-rectangle whose lower-right corner is the current grid point is legal, we need to record the color of the upper-left cell. Therefore, the contour line still has length $m+1$.

This encoding scheme still keeps a lot of redundant information: connected regions must have the same color, and the upper-left cell only needs color information rather than connectivity. But because we already use a hash table and minimal representation, the effect on time complexity is small. To reduce implementation burden, we do not refine it further.

In the worst case, for example when the first row alternates black and white, the connectivity information of every plug is distinct. Therefore, we need $4$ binary bits to store connectivity, plus the color bit, so `Offset` is $5$ bits in this problem.

???+ note "Code Implementation"
    ```cpp
    constexpr int Offset = 5, Mask = (1 << Offset) - 1;
    int c[N + 2];
    int b[N + 2], bb[N + 3];
    
    T_state encode() {
      T_state s = 0;
      memset(bb, -1, sizeof(bb));
      int bn = 1;
      bb[0] = 0;
      for (int i = m; i >= 0; --i) {
    #define bi bb[b[i]]
        if (!~bi) bi = bn++;
        s <<= Offset;
        s |= (bi << 1) | c[i];
      }
      return s;
    }
    
    void decode(T_state s) {
      REP(i, m + 1) {
        b[i] = s & Mask;
        c[i] = b[i] & 1;
        b[i] >>= 1;
        s >>= Offset;
      }
    }
    ```

### Handwritten Hash Table

Because we need to construct an arbitrary solution, the hash table here must add a `pre[]` field to record any predecessor of each state from the previous stage.

???+ note "Code Implementation"
    ```cpp
    constexpr int Prime = 9979, MaxSZ = 1 << 20;
    
    template <class T_state, class T_key>
    struct hashTable {
      int head[Prime];
      int next[MaxSZ], sz;
      T_state state[MaxSZ];
      T_key key[MaxSZ];
      int pre[MaxSZ];
    
      void clear() {
        sz = 0;
        memset(head, -1, sizeof(head));
      }
    
      void push(T_state s, T_key d, T_state u) {
        int x = s % Prime;
        for (int i = head[x]; ~i; i = next[i]) {
          if (state[i] == s) {
            key[i] += d;
            return;
          }
        }
        state[sz] = s, key[sz] = d, pre[sz] = u;
        next[sz] = head[x], head[x] = sz++;
      }
    
      void roll() { REP(ii, sz) state[ii] <<= Offset; }
    };
    
    hashTable<T_state, T_key> _H, H[N][N], *H0, *H1;
    ```

### Constructing a Solution

With the information above, we can construct a solution easily. First iterate through the states in the current hash table. If the number of connected components is at most $2$, add it to the answer. If the number of solutions is not $0$, use the `pre` array in reverse order to construct a solution. Note that at the end of each row, because we performed the `Roll()` operation, the color should be taken from `c[j+1]`.

???+ note "Code Implementation"
    ```cpp
    void print() {
      T_key z = 0;
      int u;
      REP(i, H1->sz) {
        decode(H1->state[i]);
        if (*max_element(b + 1, b + m + 1) <= 2) {
          z += H1->key[i];
          u = i;
        }
      }
      cout << z << endl;
      if (z) {
        DWN(i, n, 0) {
          B[i][m] = 0;
          DWN(j, m, 0) {
            decode(H[i][j].state[u]);
            int cc = j == m - 1 ? c[j + 1] : c[j];
            B[i][j] = cc ? 'o' : '#';
            u = H[i][j].pre[u];
          }
        }
        REP(i, n) puts(B[i]);
      }
      puts("");
    }
    ```

### State Transitions

Let:

-   `cc` be the color of the cell currently being colored
-   `lf` be the color of the cell on the left
-   `up` be the color of the cell above
-   `lu` be the color of the upper-left cell

We use $-1$ to indicate that a color does not exist. Next, consider the three transition cases: merging, inheriting, and creating.

???+ note "State Transitions - Code"
    ```cpp
    void trans(int i, int j, int u, int cc) {
      decode(H0->state[u]);
      int lf = j ? c[j - 1] : -1, lu = b[j] ? c[j] : -1,
          up = b[j + 1] ? c[j + 1] : -1;  // Absence of color is also a kind of color!
      if (lf == cc && up == cc) {         // Merge
        if (lu == cc) return;             // The 2x2 sub-rectangle has the same color
        int lf_b = b[j - 1], up_b = b[j + 1];
        REP(i, m + 1) if (b[i] == up_b) { b[i] = lf_b; }
        b[j] = lf_b;
      } else if (lf == cc || up == cc) {  // Inherit
        if (lf == cc)
          b[j] = b[j - 1];
        else
          b[j] = b[j + 1];
      } else {                                             // Create
        if (i == n - 1 && j == m - 1 && lu == cc) return;  // Special case
        b[j] = m + 2;
      }
      c[j] = cc;
      if (!ok(i, j, cc)) return;  // Check whether a newly closed connected component makes the state illegal
      H1->push(encode(), H0->key[u], u);
    }
    ```

For the last case, note that if a closed connected region has already been created, then we cannot use its color again; otherwise that color would have two connected components. It seems we need to record this event separately. We could follow the approach in [ZOJ 3213 - Beautiful Meadow](#example_2) and add another dimension for this event. However, using the special properties of this problem, we can also handle it with special cases.

???+ note "Special Case - Code"
    ```cpp
    bool ok(int i, int j, int cc) {
      if (cc == c[j + 1]) return true;
      int up = b[j + 1];
      if (!up) return true;
      int c1 = 0, c2 = 0;
      REP(i, m + 1) if (i != j + 1) {
        if (b[i] == b[j + 1]) {  // Same connectivity implies same color
          assert(c[i] == c[j + 1]);
        }
        if (c[i] == c[j + 1] && b[i] == b[j + 1]) ++c1;
        if (c[i] == c[j + 1]) ++c2;
      }
      if (!c1) {               // If a new closed connected component would be created
        if (c2) return false;  // If the contour line still contains the same color
        if (i < n - 1 || j < m - 2) return false;
      }
      return true;
    }
    ```

Now discuss the disappearance of connected components further. Each time we color a cell, if no other cell is connected to the cell above it, then a closed connected component is formed. This event can only happen in the last two columns of the last row. Otherwise, to avoid creating a same-color $2\times 2$ connected block later, this color must appear again, except in the following case:

    2 2
    o#
    #o

We handle this case specially. Thus in this problem, we can avoid recording whether a closed connected component has already been created.

??? note "Example Code"
    ```cpp
    --8<-- "docs/dp/code/plug/plug_4.cpp"
    ```

### Exercises

??? note "Exercise [Topcoder SRM 312. Div1 Hard - CheapestIsland](https://archive.topcoder.com/ProblemStatement/pm/6482)"
    Problem statement: Given a grid graph with a weight on each cell, find the connected component with minimum total weight.

??? note "Exercise [JLOI 2009 - Mysterious Creature](https://www.luogu.com.cn/problem/P3886)"
    Problem statement: Given a grid graph with a weight on each cell, find the connected component with maximum total weight.

??? note "Exercise [AtCoder Beginner Contest 211. Problem E - Red Polyomino](https://atcoder.jp/contests/abc211/tasks/abc211_e)"
    Problem statement: Given an $N\times N$ board where each cell is initially black or white, choose exactly $K$ white cells and color them red. Count the colorings in which the red cells form one connected component.

## Graph-Theoretic Model

???+ note "Example [NOI 2007 Day2 - Spanning Tree Count](https://www.luogu.com.cn/problem/P2109)"
    Problem statement: Count spanning trees of a certain special class of graphs, where each node is connected by edges to exactly the previous $k$ nodes.

???+ note "Example [2015 ACM-ICPC Asia Shenyang Regional Contest - Problem E - Efficient Tree](https://acm.hdu.edu.cn/showproblem.php?pid=5513)"
    Problem statement: Given an $N\times M$ grid graph and edge weights between adjacent 4-neighbor cells.
    For a spanning tree, the score of each node is 1+[there is an edge upward]+[there is an edge leftward].
    The score of the spanning tree is the product of the scores of all nodes.
    
    Find the minimum spanning tree edge-weight sum and the sum of scores over all minimum spanning trees.
    ($n\le 800,m\le 7$)

## Practice

### Example

???+ note "Example [HDU 4113 - Construct the Great Wall](https://acm.hdu.edu.cn/showproblem.php?pid=4113)"
    Problem statement: Construct a set of cycles inside an $N\times M$ board to separate all `x` cells from all `o` cells.

Some plug DP problems require us to build walls on a board to separate certain elements on the board. We may call these wall-building problems. They can be viewed either as coloring models or as path models.

![greatwall](./images/greatwall.svg)

In this problem, if we view it as a coloring model, we must additionally consider the perimeter of colored regions and detect illegal corner-touching cases (Figure 2). Also, unlike [UVa 10572 - Black & White](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1513), this problem requires the wall to be a simple polygon. Therefore, the ring-shaped case below is illegal in this problem.

    3 3
    ooo
    oxo
    ooo

Therefore, we use the path model and transform it into a [single-cycle](#single-cycle) problem.

We perform DP along the grid intersections, so both the height and width need to be increased by $1$. During each transition, we must ensure that all `x` cells are outside the cycle and all `o` cells are inside the cycle. Thus we also need to maintain whether the current position is inside the cycle. This information can be represented with an extra dimension, or computed directly by counting the parity of the number of downward plugs appearing on the contour line before this position, using the ray-casting method.

??? note "Example Code"
    ```cpp
    #include <cstring>
    #include <iostream>
    using namespace std;
    #define REP(i, n) for (int i = 0; i < n; ++i)
    
    template <class T>
    bool checkMin(T &a, const T b) {
      return b < a ? a = b, true : false;
    }
    
    constexpr int N = 10, M = N;
    constexpr int offset = 3, mask = (1 << offset) - 1;
    int n, m;
    int d;
    constexpr int INF = 0x3f3f3f3f;
    int b[M + 1], bb[M + 1];
    
    int encode() {
      int s = 0;
      memset(bb, -1, sizeof(bb));
      int bn = 1;
      bb[0] = 0;
      for (int i = m; i >= 0; --i) {
    #define bi bb[b[i]]
        if (!~bi) bi = bn++;
        s <<= offset;
        s |= bi;
      }
      return s;
    }
    
    void decode(int s) {
      REP(i, m + 1) {
        b[i] = s & mask;
        s >>= offset;
      }
    }
    
    constexpr int MaxSZ = 16796, Prime = 9973;
    
    struct hashTable {
      int head[Prime], next[MaxSZ], sz;
      int state[MaxSZ];
      int key[MaxSZ];
    
      void clear() {
        sz = 0;
        memset(head, -1, sizeof(head));
      }
    
      void push(int s) {
        int x = s % Prime;
        for (int i = head[x]; ~i; i = next[i]) {
          if (state[i] == s) {
            checkMin(key[i], d);
            return;
          }
        }
        state[sz] = s, key[sz] = d;
        next[sz] = head[x];
        head[x] = sz++;
      }
    
      void roll() { REP(i, sz) state[i] <<= offset; }
    } H[2], *H0, *H1;
    
    char A[N + 1][M + 1];
    
    void push(int i, int j, int dn, int rt) {
      b[j] = dn;
      b[j + 1] = rt;
      if (A[i][j] != '.') {
        bool bad = A[i][j] == 'o';
        REP(jj, j + 1) if (b[jj]) bad ^= 1;
        if (bad) return;
      }
      H1->push(encode());
    }
    
    int solve() {
      cin >> n >> m;
      int ti, tj;
      REP(i, n) {
        scanf("%s", A[i]);
        REP(j, m) if (A[i][j] == 'o') ti = i, tj = j;
        A[i][m] = '.';
      }
      REP(j, m + 1) A[n][j] = '.';
      ++n, ++m, ++ti, ++tj;
      H0 = H, H1 = H + 1;
      H1->clear();
      d = 0;
      H1->push(0);
      int z = INF;
      REP(i, n) {
        REP(j, m) {
          swap(H0, H1);
          H1->clear();
          REP(ii, H0->sz) {
            decode(H0->state[ii]);
            d = H0->key[ii] + 1;
            int lt = b[j], up = b[j + 1];
            bool dn = i != n - 1, rt = j != m - 1;
            if (lt && up) {
              if (lt == up) {
                int cnt = 0;
                REP(i, m + 1) if (b[i])++ cnt;
                if (cnt == 2 && i == ti && j == tj) {
                  checkMin(z, d);
                }
              } else {
                REP(i, m + 1) if (b[i] == lt) b[i] = up;
                push(i, j, 0, 0);
              }
            } else if (lt || up) {
              int t = lt | up;
              if (dn) {
                push(i, j, t, 0);
              }
              if (rt) {
                push(i, j, 0, t);
              }
            } else {
              --d;
              push(i, j, 0, 0);
              ++d;
              if (dn && rt) {
                push(i, j, m, m);
              }
            }
          }
        }
        H1->roll();
      }
      if (z == INF) z = -1;
      return z;
    }
    
    int main() {
      int T;
      cin >> T;
      for (int Case = 1; Case <= T; ++Case) {
        printf("Case #%d: %d\n", Case, solve());
      }
    }
    ```

### Exercises

??? note "Exercise [SCOI 2011 - Floor](https://www.luogu.com.cn/problem/P3272)"
    Problem statement: Some cells of an $r\times c$ board are blocked. Count the ways to tile all unblocked cells with L-shaped tiles.

??? note "Exercise [HDU 4796 - Winter's Coming](https://acm.hdu.edu.cn/showproblem.php?pid=4796)"
    Problem statement: Color the uncolored grid points of an $N\times M$ board black, white, or gray. All black regions and all white regions must be connected; black regions and white regions must be connected to the upper and lower borders of the board respectively; and black regions and white regions must not be adjacent. Each cell has a corresponding cost. Find a coloring that minimizes the cost of the gray region.
    
    ![4796](./images/4796.jpg)

??? note "Exercise [ZOJ 2125 - Rocket Mania](https://pintia.cn/problem-sets/91827364500/exam/problems/type/7?page=11&problemSetProblemId=91827365624)"
    Problem statement: On a $9\times6$ map, each cell contains a type of pipe (`-`, `T`, `L`, `+`, or none). Pipes can be rotated by 0, 90, 180, or 270 degrees. Find the maximum number of rows whose right boundary can be connected through pipes to the left boundary of row X.

??? note "Exercise [ZOJ 2126 - Rocket Mania Plus](https://pintia.cn/problem-sets/91827364500/exam/problems/type/7?page=11&problemSetProblemId=91827365625)"
    Problem statement: On a $9\times6$ map, each cell contains a type of pipe (`-`, `T`, `L`, `+`, or none). Pipes can be rotated by 0, 90, 180, or 270 degrees. Find the maximum number of rows whose right boundary can be connected through pipes to their left boundary.

??? note "Exercise [World Finals 2009/2010 Harbin - Channel](https://qoj.ac/problem/13134)"
    Problem statement: Given a grid map where `.` denotes empty land and `#` denotes rock, find the longest path satisfying:
    
    1.  The start is at the upper-left corner and the end is at the lower-right corner.
    2.  The path cannot pass through rocks.
    3.  The path itself cannot form a cycle under 8-connectivity, meaning it also cannot touch at corners.

??? note "Exercise [HDU 3958 - Tower Defence](https://acm.hdu.edu.cn/showproblem.php?pid=3958)"
    Problem statement: This can be transformed into finding the longest non-touching path from $\mathit{S}$ to $\mathit{T}$; touching at corners is allowed.

??? note "Exercise [UVa 10531 - Maze Statistics](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1472)"
    Problem statement: Given an $N\times M$ grid, each cell independently becomes an obstacle with probability $\mathit{p}$. You need to go from the upper-left corner of the maze to the lower-right corner. Find the probability that each cell is an obstacle in a **solvable maze, meaning the start and end are 4-connected**. ($N \le 5$, $M \le 6$)

??? note "Exercise [Aizu 2452 - Pipeline Plans](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2452)"
    Problem statement: There are 12 tile patterns in total, with a given quantity for each pattern. Tile a rectangular floor that can be viewed as an $R\times C$ grid graph, placing one tile in each cell, so that the center of the upper-left cell is connected to the center of the lower-right cell through the lines on the tile patterns. $(2 \le R \times C \le 15)$
    
    ![plug2](./images/plug2.png)

??? note "Exercise [SDOI 2014 - Circuit Board](https://www.luogu.com.cn/problem/P3314)"
    Problem statement: Given an $N\times M$ circuit board with some blocked positions where wires cannot pass, and $K$ pairs of cells. Each pair must be connected by a wire, and wires must not intersect. It is allowed for one wire to enter the current cell from the upper boundary and leave from the left boundary, while another wire enters from the lower boundary and leaves from the right boundary. Treat wires as undirected edges. Find the minimum total wire length satisfying the requirements and the number of such solutions.

??? note "Exercise [SPOJ CAKE3 - Delicious Cake](https://www.spoj.com/problems/CAKE3)"
    Problem statement: A cake can be viewed as an $N\times M$ grid. Cut the cake into several pieces along grid lines. Count the number of distinct cutting methods. Two cuts are considered the same if and only if every resulting piece has the same shape and is in the same position. ($\min(N,M) \le 5, \max(N,M) \le 130$)

## Notes

Plug DP problems are usually difficult to encode and require complex case analysis, so they are a relatively [niche area](https://github.com/OI-wiki/libs/blob/master/topic/7-%E7%8E%8B%E5%A4%A9%E6%87%BF-%E8%AE%BA%E5%81%8F%E9%A2%98%E7%9A%84%E5%8D%B1%E5%AE%B3.ppt) in OI/ACM. The most classic reference on this topic is the 2008 national training team paper by [Danqi Chen](https://www.cs.princeton.edu/~danqic/), [Dynamic Programming Problems Based on Connectivity State Compression](https://github.com/AngelKitty/review_the_national_post-graduate_entrance_examination/tree/master/books_and_notes/professional_courses/data_structures_and_algorithms/sources/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2008%E8%AE%BA%E6%96%87%E9%9B%86/%E9%99%88%E4%B8%B9%E7%90%A6%E3%80%8A%E5%9F%BA%E4%BA%8E%E8%BF%9E%E9%80%9A%E6%80%A7%E7%8A%B6%E6%80%81%E5%8E%8B%E7%BC%A9%E7%9A%84%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E9%97%AE%E9%A2%98%E3%80%8B). In addition, HDU user notonlysuccess wrote two progressive blog posts on this topic in 2011; they are also valuable resources, though now they need to be found through the Web Archive.

-   [notonlysuccess, Plug DP Special](https://web.archive.org/web/20110815044829/http://www.notonlysuccess.com/?p=625)
-   [notonlysuccess, Complete Plug DP](https://web.archive.org/web/20111007185146/http://www.notonlysuccess.com/?p=931)

### Domino Tiling

[HDU 1400 - Mondriaan's Dream](https://acm.hdu.edu.cn/showproblem.php?pid=1400) also appears in [The Training Guide for Algorithm Design and Programming Contests](../contest/resources.md#%E4%B9%A6%E7%B1%8D) as an example in the section on dynamic programming over contour lines. [Domino tiling](https://en.wikipedia.org/wiki/Domino_tiling) is a very classic class of mathematical problems. Slightly changing the constraints yields subproblems of different difficulty that require different algorithms.

When $m=2$, domino tiling is equivalent to the Fibonacci sequence. [Concrete Mathematics](https://www.csie.ntu.edu.tw/~r97002/temp/Concrete%20Mathematics%202e.pdf) uses this problem to introduce the Fibonacci sequence and derives its closed form in several ways.

When $m\le 10,n\le 10^9$, the transition equations can be preprocessed into matrix form and accelerated with [matrix multiplication](http://www.matrix67.com/blog/archives/276).

![domino\_v2\_transform\_matrix](./images/domino_v2_transform_matrix.svg)

When $n,m\le 100$, the [FKT Algorithm](https://en.wikipedia.org/wiki/FKT_algorithm) can be used to compute the number of perfect matchings in the corresponding planar graph.

-   [51nod 1031 - Domino Tiling](https://www.51nod.com/Html/Challenge/Problem.html#problemId=1031)
-   [51nod 1033 - Domino Tiling V2](https://www.51nod.com/Html/Challenge/Problem.html#problemId=1033)|[Vijos 1194 - Domino](https://vijos.org/p/1194)
-   [51nod 1034 - Domino Tiling V3](https://www.51nod.com/Html/Challenge/Problem.html#problemId=1034)|[Ural 1594 - Aztec Treasure](https://acm.timus.ru/problem.aspx?space=1&num=1594)
-   [Wolfram MathWorld, Chebyshev Polynomial of the Second Kind](https://mathworld.wolfram.com/ChebyshevPolynomialoftheSecondKind.html)

### Single Path

"Single path" is a special case of the [Hamiltonian Path](https://en.wikipedia.org/wiki/Hamiltonian_path) problem on [grid graphs](https://mathworld.wolfram.com/GridGraph.html). The decision version of Hamiltonian path is an important member of the [NP-complete](https://en.wikipedia.org/wiki/NP-completeness) family.
