author: accelsao, Enter-tainer, guodong2005, StudyingFather, Backl1ght, Chrogeek, H-J-Granger, Henry-ZHR

The maximum weight matching in a bipartite graph refers to the matching with the maximum sum of edge weights.

## Hungarian Algorithm (Kuhn–Munkres Algorithm)

The Hungarian algorithm, also known as the **KM** algorithm, can find the **maximum weight perfect matching** in a bipartite graph in $O(n^3)$ time.

Considering that the two vertex sets in a bipartite graph do not always have the same size, to apply the KM algorithm to solve the maximum weight matching in a bipartite graph, we first need to do the following processing: add dummy vertices to the smaller set so that both sets have the same size, and set the weights of non-existent edges to 0. Under this transformation, the problem becomes a **maximum weight perfect matching problem**, which can be solved by the KM algorithm.

???+ note "Feasible Vertex Labels"
    Assign a weight $l(i)$ to each vertex $i$, such that for all edges $(u,v)$, we have $w(u,v) \leq l(u) + l(v)$.

???+ note "Equality Subgraph"
    Under a set of feasible vertex labels, the spanning subgraph of the original graph that contains all vertices but only edges $(u,v)$ satisfying $w(u,v) = l(u) + l(v)$.

???+ note "Theorem 1: For a set of feasible vertex labels, if its equality subgraph contains a perfect matching, then that matching is the maximum weight perfect matching of the original bipartite graph."
    Proof 1.

    Consider any perfect matching $M$ in the original bipartite graph, its total edge weight is

    $val(M) = \sum_{(u,v)\in M} {w(u,v)} \leq \sum_{(u,v)\in M} {l(u) + l(v)} \leq \sum_{i=1}^{n} l(i)$

    The total edge weight of a perfect matching $M'$ in the equality subgraph of any feasible vertex labels is

    $val(M') = \sum_{(u,v)\in M} {l(u) + l(v)} = \sum_{i=1}^{n} l(i)$

    That is, the total edge weight of any perfect matching is not greater than $val(M')$, so $M'$ is the maximum weight matching.

With Theorem 1, our goal is to continuously adjust the feasible vertex labels until the equality subgraph contains a perfect matching.

Since both sides have the same number of vertices, assuming there are $n$ vertices, let $lx(i)$ denote the label of the $i$-th vertex on the left side, $ly(i)$ denote the label of the $i$-th vertex on the right side, and $w(u,v)$ denote the weight between the $u$-th vertex on the left and the $v$-th vertex on the right.

First, initialize a set of feasible vertex labels, for example:

$lx(i) = \max_{1\leq j\leq n} \{ w(i, j)\},\, ly(i) = 0$

Then, select an unmatched vertex and, as in maximum matching, search for an augmenting path. If an augmenting path is found, augment it; otherwise, we obtain an alternating tree.

Let $S$ and $T$ denote the vertices on the left and right sides in the alternating tree respectively, and let $S'$ and $T'$ denote the vertices not in the alternating tree.

![bigraph-weight-match-1](./images/bigraph-weight-match-1.png)

In the equality subgraph:

-   Edges from $S$ to $T'$ do not exist, otherwise the alternating tree would grow.
-   Edges from $S'$ to $T$ must be unmatched edges, otherwise it would belong to $S$.

Suppose we subtract $a$ from the labels of vertices in $S$ and add $a$ to the labels of vertices in $T$. We can observe that:

-   Edges from $S$ to $T$ still exist in the equality subgraph.
-   Edges from $S'$ to $T'$ are unchanged.
-   For edges from $S$ to $T'$, $lx + ly$ decreases, so they may join the equality subgraph.
-   For edges from $S'$ to $T$, $lx + ly$ increases, so they cannot join the equality subgraph.

Therefore, the choice of $a$ must be the minimum edge weight among edges from $S$ to $T'$:

$a = \min \{ lx(u) + ly(v) - w(u,v) | u\in{S} , v\in{T'} \}$.

When a new edge $(u,v)$ joins the equality subgraph, there are two cases:

-   $v$ is an unmatched vertex, then we find an augmenting path.
-   $v$ is already matched with a vertex in $S'.

After modifying the labels at most $n$ times, we can find an augmenting path.

Each time we modify the labels, edges in the alternating tree do not leave the equality subgraph, so we can directly maintain this tree.

For each vertex $v$ in $T$, we maintain:

$slack(v) = \min \{ lx(u) + ly(v) - w(u,v) | u\in{S} \}$.

So we can compute the label modification value $a$ in $O(n)$:

$a = \min \{ slack(v) | v\in{T'} \}$

When a new vertex enters $S$ in the alternating tree, we need $O(n)$ to update $slack(v)$. Modifying the labels requires $O(n)$ to subtract $a$ from each $slack(v)$. As soon as the alternating tree finds an unmatched vertex, we have found an augmenting path.

We start by enumerating $n$ vertices to find augmenting paths. To find an augmenting path, we need to extend the alternating tree $n$ times, and each extension requires $n$ operations for maintenance, for a total of $O(n^3)$.

??? note "Reference Code"
    ```cpp
    template <typename T>
    struct hungarian {  // km
      int n;
      vector<int> matchx;  // matched vertex in left set
      vector<int> matchy;  // matched vertex in right set
      vector<int> pre;     // connecting left vertex to right set
      vector<bool> visx;   // visited array for left
      vector<bool> visy;   // visited array for right
      vector<T> lx;
      vector<T> ly;
      vector<vector<T>> g;
      vector<T> slack;
      T inf;
      T res;
      queue<int> q;
      int org_n;
      int org_m;

      hungarian(int _n, int _m) {
        org_n = _n;
        org_m = _m;
        n = max(_n, _m);
        inf = numeric_limits<T>::max();
        res = 0;
        g = vector<vector<T>>(n, vector<T>(n));
        matchx = vector<int>(n, -1);
        matchy = vector<int>(n, -1);
        pre = vector<int>(n);
        visx = vector<bool>(n);
        visy = vector<bool>(n);
        lx = vector<T>(n, -inf);
        ly = vector<T>(n);
        slack = vector<T>(n);
      }

      void addEdge(int u, int v, int w) {
        g[u][v] = max(w, 0);  // negative values are worse than not matching, so set to 0
      }

      bool check(int v) {
        visy[v] = true;
        if (matchy[v] != -1) {
          q.push(matcher[v]);
          visx[matchy[v]] = true;  // in S
          return false;
        }
        // found new unmatched vertex, update matching, pre array records the vertex connected by "unmatched edge"
        while (v != -1) {
          matchy[v] = pre[v];
          swap(v, matchx[pre[v]]);
        }
        return true;
      }

      void bfs(int i) {
        while (!q.empty()) {
          q.pop();
        }
        q.push(i);
        visx[i] = true;
        while (true) {
          while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < n; v++) {
              if (!visy[v]) {
                T delta = lx[u] + ly[v] - g[u][v];
                if (slack[v] >= delta) {
                  pre[v] = u;
                  if (delta) {
                    slack[v] = delta;
                  } else if (check(v)) {  // delta=0 means chance to join equality subgraph, find augmenting path
                                          // if found, return and rebuild alternating tree
                    return;
                  }
                }
              }
            }
          }
          // no augmenting path, modify labels
          T a = inf;
          for (int j = 0; j < n; j++) {
            if (!visy[j]) {
              a = min(a, slack[j]);
            }
          }
          for (int j = 0; j < n; j++) {
            if (visx[j]) {  // S
              lx[j] -= a;
            }
            if (visy[j]) {  // T
              ly[j] += a;
            } else {  // T'
              slack[j] -= a;
            }
          }
          for (int j = 0; j < n; j++) {
            if (!visy[j] && slack[j] == 0 && check(j)) {
              return;
            }
          }
        }
      }

      void solve() {
        // initialize labels
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
            lx[i] = max(lx[i], g[i][j]);
          }
        }

        for (int i = 0; i < n; i++) {
          fill(slack.begin(), slack.end(), inf);
          fill(visx.begin(), visx.end(), false);
          fill(visy.begin(), visy.end(), false);
          bfs(i);
        }

        // custom
        for (int i = 0; i < n; i++) {
          if (g[i][matchx[i]] > 0) {
            res += g[i][matchx[i]];
          } else {
            matchx[i] = -1;
          }
        }
        cout << res << "\n";
        for (int i = 0; i < org_n; i++) {
          cout << matchx[i] + 1 << " ";
        }
        cout << "\n";
      }
    };
    ```

## Dynamic Hungarian Algorithm

Original paper [The Dynamic Hungarian Algorithm for the Assignment Problem with Changing Costs](https://www.ri.cmu.edu/publications/the-dynamic-hungarian-algorithm-for-the-assignment-problem-with-changing-costs/)

A clearer pseudocode version [A Fast Dynamic Assignment Algorithm for Solving Resource Allocation Problems](https://www.researchgate.net/publication/352490780_A_Fast_Dynamic_Assignment_Algorithm_for_Solving_Resource_Allocation_Problems)

Related OJ problem [DAP](https://www.spoj.com/problems/DAP/)

???+ note "Algorithm Idea"
    1.  Modify the weights between a single vertex $u_i$ and all $v_j$, i.e., a row in the weight matrix
        -   Modify the label $lx(u_i) = max(w_{ij} - v_{j}), \forall j$
        -   Delete the matching related to $u_i$
    2.  Modify the weights between all $u_i$ and a single vertex $v_j$, i.e., a column in the weight matrix
        -   Modify the label $ly(v_j) = max(w_{ij} - u_{i}), \forall i$
        -   Delete the matching related to $v_j$
    3.  Modify the weight between a single $u_i$ and a single $v_j$, i.e., a single element in the weight matrix
        -   Either operation 1 or 2 works
    4.  Add or remove a single vertex $u_i$ or $v_j$, i.e., add or delete a row or column in the weight matrix
        -   Perform operation 1 or 2 accordingly. Note that adding a vertex here means simply adding the vertex, without setting additional weight values; the weights between the new vertex and other vertices are 0.

???+ note "Algorithm Proof"
    -   Let the original graph be G, with labels $\alpha^{i}$ and $\beta^{j}$ on the left and right sides respectively, and feasible labels be $l$. Then $G_l$ is a subgraph of G containing the vertices and edges in G that satisfy $w_{ij} = alpha_{i}+beta_{j}$.
    -   In the Hungarian algorithm section above, Theorem 1 proved: for a set of feasible vertex labels, if its equality subgraph contains a perfect matching, then that matching is the maximum weight perfect matching of the original bipartite graph.
    -   Assume the original optimal matching is $M^*$. When a modification occurs, we update the feasible labels according to the rules. Let the updated labels be $\alpha^{i^*}$ or $\beta^{j^*}$. The following cases arise:
        1.  An entire row of the weight matrix is modified. Let the modified row be $i^*$, i.e., all edges of $v_{i^*}$ are modified, so the original label of $v_{i^*}$ may not satisfy the condition, because we need $w_{i^{*}j} \leq alpha_{i^*}+beta_{j}$. However, for other $u_j$, except for edges related to $i^*$, their edge weights remain unchanged, so their labels are all valid. Therefore, the algorithm modifies the labels related to $v_{i^*}$ to make this set of labels a feasible set.
        2.  An entire column of the weight matrix is modified. Similarly, the algorithm modifies the labels to make this set of labels a feasible set.
        3.  Modifying a single element in the weight matrix. Modifying either label satisfies the label condition.
    -   Each time the weight matrix is modified, it involves a specific vertex, which could be on the left or right side. So we directly denote this vertex as $x$. This vertex was matched with some vertex $y$ in the original optimal matching. Each modification operation can unpair at most this pair of vertices. Therefore, we only need to run one iteration of the search in the Hungarian algorithm to get a new match. According to Theorem 1, the new match obtained is optimal.

The following code should be the code submitted by the authors of paper 2 (this code is the maximization version; the original paper minimizes cost)

??? note "Dynamic Hungarian Algorithm Reference Code"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/bigraph-weight-match/bigraph-weight-match_1.cpp"
    ```

## Conversion to Min-Cost Flow Model

Similar to [Maximum Matching in Bipartite Graphs](./bigraph-match.md), the maximum weight matching in bipartite graphs can also be solved by converting to a network flow problem.

First, add a source and a sink to the graph.

Connect an edge from the source to each left vertex in the bipartite graph with flow 1 and cost 0, and connect an edge from each right vertex to the sink with flow 1 and cost 0.

Then, for each edge connecting left vertex $u$ and right vertex $v$ in the bipartite graph with weight $w$, connect an edge from $u$ to $v$ with flow 1 and cost $w$.

Additionally, since in maximum weight matching, the number of matched edges may not equal the number in a maximum matching, for each left vertex, we also need to connect an edge to the sink with flow 1 and cost 0.

Solving the [maximum cost maximum flow](../flow/min-cost.md) on this network yields the answer. At this time, the maximum flow of the network must equal the number of left vertices, and the maximum cost under maximum flow corresponds to a maximum weight matching scheme.

## Practice Problems

??? note "[UOJ #80. Maximum Weight Matching in Bipartite Graphs](https://uoj.ac/problem/80)"
    Template problem
    
    ```cpp
    --8<-- "docs/graph/code/graph-matching/bigraph-weight-match/bigraph-weight-match_2.cpp"
    ```