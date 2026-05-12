author: Anguei, sshwy, Xeonacid, Ir1d, MonkeyOliver, hsfzLZH1

Node splitting is a graph theory modeling technique, commonly used in [network flow](./flow.md), to handle **node weights or node flow limitations**, and is also commonly used in **layered graphs**.

## Maximum Flow with Node Capacity Limits

If we convert a node into an edge, then the problem can be solved using standard templates.

We consider converting a node with capacity limits into such a form: a component consisting of two nodes $u, v$ and an edge $\langle u, v \rangle$. Here, node $u$ receives all edges from other nodes in the original graph that go to the node in the original graph, and node $v$ originates all edges from the node in the original graph to other nodes in the original graph. The capacity limit of edge $\langle u, v \rangle$ is set to the capacity limit of the node in the original graph. Then we can use standard templates to solve the problem. This is the basic idea of node splitting.

If the original graph is like this:

![](./images/node.svg)

The graph after splitting looks like this:

![](./images/node-split.svg)

## Shortest Path on Layered Graphs

Layered graph shortest path problems, such as: given $k$ times to traverse a path with zero cost, find the minimum total cost. For such problems, we can use DP-related ideas. Let $\text{dis}_{i, j}$ represent the shortest path from the starting node $i$ after using $j$ free passage rights. Clearly, the $\text{dis}$ array can be transitioned as follows:

$\text{dis}_{i, j} = \min\{\min\{\text{dis}_{\text{from}, j - 1}\}, \min\{\text{dis}_{\text{from}, j} + w\}\}$

Here, $\text{from}$ represents the parent node of $i$, and $w$ represents the weight of the current edge. When $j - 1 \geq k$, $\text{dis}_{\text{from}, j} = \infty$.

In fact, this DP is equivalent to splitting each node into $k + 1$ nodes, where each new node represents the original node after arriving with different numbers of free passes. In other words, each node $u_i$ represents reaching node $u$ after using $i$ free passage rights.

??? note "[JLOI2011 Flight Route](https://www.luogu.com.cn/problem/P4568)"
    Problem: There is an undirected graph with $n$ nodes and $m$ edges. You can choose $k$ roads to traverse at zero cost. Find the minimum cost from $s$ to $t$.
    
    Reference core code:
    
    ```cpp
    struct State {    // Node structure for the priority queue
      int v, w, cnt;  // cnt represents how many times free passage has been used
    
      State() {}
    
      State(int v, int w, int cnt) : v(v), w(w), cnt(cnt) {}
    
      bool operator<(const State &rhs) const { return w > rhs.w; }
    };
    
    void dijkstra() {
      memset(dis, 0x3f, sizeof dis);
      dis[s][0] = 0;
      pq.push(State(s, 0, 0));  // At the start, no free passage used, distance is 0
      while (!pq.empty()) {
        const State top = pq.top();
        pq.pop();
        int u = top.v, nowCnt = top.cnt;
        if (done[u][nowCnt]) continue;
        done[u][nowCnt] = true;
        for (int i = head[u]; i; i = edge[i].next) {
          int v = edge[i].v, w = edge[i].w;
          if (nowCnt < k && dis[v][nowCnt + 1] > dis[u][nowCnt]) {  // Can use free passage
            dis[v][nowCnt + 1] = dis[u][nowCnt];
            pq.push(State(v, dis[v][nowCnt + 1], nowCnt + 1));
          }
          if (dis[v][nowCnt] > dis[u][nowCnt] + w) {  // Cannot use free passage
            dis[v][nowCnt] = dis[u][nowCnt] + w;
            pq.push(State(v, dis[v][nowCnt], nowCnt));
          }
        }
      }
    }
    
    int main() {
      n = read(), m = read(), k = read();
      // The author is accustomed to using 1 to n, but this problem uses 0 to n-1, so adjust
      s = read() + 1, t = read() + 1;
      while (m--) {
        int u = read() + 1, v = read() + 1, w = read();
        add(u, v, w), add(v, u, w);  // This problem uses bidirectional edges
      }
      dijkstra();
      int ans = std::numeric_limits<int>::max();  // Initialize ans to max int value
      for (int i = 0; i <= k; ++i)
        ans = std::min(ans, dis[t][i]);  // Take the optimal value for all cases reaching the destination
      println(ans);
    }
    ```