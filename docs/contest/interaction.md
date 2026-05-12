author: countercurrent-time, StudyingFather

IOI from the last century already involved interactive problems. Although interactive problems have not appeared in provincial-level or lower competitions in recent years, in 2019, two interactive problems — "P5208[WC2019]I 君的商店" and "P5473[NOI2019]I 君的探险" — appeared consecutively in the NOI series of competitions, which may indicate that interactive problems are returning to the NOI series of competitions.

Interactive problems do not have high prerequisite algorithm requirements, and generally do not have strict time limits; the quality of a program often depends solely on the interaction count limit. Therefore, when learning interactive problems, it is recommended to proceed step by step according to difficulty. If you want to exercise algorithmic thinking rather than just purely learning algorithms, completing interactive problems is a very good method. Although interactive problems usually have low requirements for algorithms already mastered by the contestant, it is still recommended to have mastered a certain level of advanced and provincial selection algorithms before attempting interactive problems, because by that point your algorithmic thinking level and knowledge scope will have reached a certain standard.

For a basic introduction to interactive problems, you can refer to **OI Wiki**'s [Problem Types Introduction - Interactive Problems](./problems.md#交互题).

Special errors in interactive problems:

- Contestants need to flush the buffer after each output, otherwise it will cause an Idleness Limit Exceeded error. Additionally, if the problem contains multiple test cases and the program can determine the answer before reading all the data, you still need to read all the data, otherwise it will also cause an ILE due to input confusion (you can make multiple queries at once and receive all responses at once). Also, try not to use fast I/O.
- If the program makes too many queries, Codeforces will give a Wrong Answer verdict (though the judging system will explain the reason for the Wrong Answer), while UVa will give a Protocol Limit Exceeded (PLE) verdict.
- If the program's interaction format is incorrect, UVa will give a Protocol Violation (PV) verdict.

Since the input and output of interactive problems are relatively cumbersome, it is recommended to encapsulate input and output functions separately. During a competition, if the problem setter provides a grader header file (for debugging grader-style interactive problems) or a checker program (for debugging stdio-style interactive problems), debugging interactive problems is relatively simple, because creating a diff script for interactive problems is much more difficult than for regular problems. Without `testlib.h`, the stdio interaction library for a problem with many interaction details typically has around 3k lines of code, plus a diff script of around 3k lines, requiring at least an hour to implement. However, regardless of whether debugging programs are available, debugging interactive problem code often requires the contestant to simulate the interaction process with the program, so interactive problems require contestants to design high-quality programs, try to get it right in one attempt, and have strong static debugging skills.

Example problems:

- [CF679A Bear and Prime 100](https://codeforces.com/problemset/problem/679/A)
- [CF843B Interactive LowerBound](https://codeforces.com/problemset/problem/843/B)
- [UOJ206[APIO2016]Gap](http://uoj.ac/problem/206)
- [CF750F New Year and Finding Roots](https://codeforces.com/problemset/problem/750/F)
- [UVa12731 太空站之谜 Mysterious Space Station](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=823&page=show_problem&problem=4584)

## CF679A Bear and Prime 100

Every prime number has exactly two factors, so we directly enumerate the factors of the number to guess. Since the limit is at most 20 queries, and when trying to factorize larger numbers (such as 92), we find that we need to enumerate primes up to at most $\lfloor\frac{n}{2}\rfloor$. So we first sieve out the primes within 50, and ask about each of these numbers every time. Since diffing is relatively easy for this problem, we can directly try all numbers in the value range. We will find that the program cannot effectively handle squares of primes. So we need to include the squares of 2, 3, 5, 7, which are 4, 9, 25, 49, totaling 19 numbers, which satisfies the problem's requirements.

??? note "Reference Code"

```cpp
#include <cstdio>
constexpr int prime[] = {2, 3, 4, 5, 7, 9, 11, 13, 17, 19, 23, 25, 29, 31, 37, 41, 43, 47, 49};
int cnt = 0;
char res[5];
int main() {
  for (int i : prime) {
    printf("%d\n", i);
    fflush(stdout);
    scanf("%s", res);
    if (res[0] == 'y' && ++cnt == 2) return printf("composite"), 0;
  }
  printf("prime");
  return 0;
}
```

## CF843B Interactive LowerBound

The linked list has at most $5 \times 10 ^ 4$ elements, but we can only make $1999$ queries, and can only get the next element of a given element, so the ordinary method of traversing the entire linked list is not available.

There is only one way to directly approach the target element's position: random sampling. For $n < 2000$, we enumerate directly; for $n \ge 2000$, we randomly sample 1000 points. At this point, the expected distance between these points is very small, and we can directly start traversing backward from the largest value less than $x$. It can be proven that we will have obtained the answer before reaching the next point. During the traversal, once we find an element greater than or equal to $x$, we can directly output it.

Although the overall idea is simple, in practice, if you have not studied non-perfect random algorithms such as simulated annealing, it may be somewhat difficult to come up with this approach. Also, since Codeforces has a hack mechanism, many people will deliberately hack code that does not initialize the random seed, so you need `srand((size_t)new char)` before the `random_shuffle()` function.

??? note "Reference Code"

```cpp
#include <algorithm>
#include <cstdio>
#include <cstdlib>
constexpr int N = 50005;
int n, start, x;
int a[N];
int main() {
  scanf("%d%d%d", &n, &start, &x);
  if (n < 2000) {
    int ans = 2e9;
    for (int i = 1; i <= n; i++) {
      printf("? %d\n", i), fflush(stdout);
      int val, next;
      scanf("%d%d", &val, &next);
      if (val >= x) ans = std::min(ans, val);
    }
    if (ans == 2e9) ans = -1;
    printf("! %d", ans), fflush(stdout);
  } else {
    srand((size_t) new char);
    int p = start, ans = 0;
    for (int i = 1; i <= n; i++) a[i] = i;
    std::random_shuffle(a + 1, a + n + 1);
    for (int i = 1; i <= 1000; i++) {
      printf("? %d\n", a[i]), fflush(stdout);
      int val, next;
      scanf("%d%d", &val, &next);
      if (val < x && val > ans) p = a[i], ans = val;
    }
    while (p != -1 && ans < x) {
      printf("? %d\n", p), fflush(stdout);
      int val, next;
      scanf("%d%d", &val, &next);
      ans = val;
      p = next;
    }
    if (ans < x) ans = -1;
    printf("! %d", ans), fflush(stdout);
  }
  return 0;
}
```

## UOJ206[APIO2016]Gap

We discuss two subtasks:

1. Query count limit. We consider the first query. Since we don't know any numbers at the beginning, we need to query the range $[1, 10 ^ {18}]$ to get the maximum and minimum values. Since the query count limit is exactly $\frac{N + 1}{2}$, we consider how to obtain values not previously obtained in each query, so that we can roughly obtain all numbers in the sequence within the query limit. The method is also very simple: after each query of $[s, t]$, let the obtained values be $mn, mx$, then the next query is $[mn + 1, mx - 1]$.

2. Query interval size limit. Since the problem requires that the total number of elements in all queried intervals cannot exceed $3N$, we consider minimizing the queried intervals. The above method is no longer available, because the total number of elements in its queried intervals is of scale $O(N ^ 2)$. We could consider binary searching the value range, but this method is unreliable and could be forced to $O(N ^ 2)$ in the worst case. So we need a more effective way to partition the value range, avoiding repeatedly querying points within queried intervals and wasting opportunities. Considering that the answer will not be less than $\lfloor\frac{a_n - a_1}{N - 1}\rfloor$, we can consider partitioning the value range by this value. Let $i$ initially be 0, $ans$ initially be the above value, and each time query $[i, i + ans]$ and update $ans$, then increment $i$ by $ans$ as the step size. However, this method also cannot be applied well to subtask 1, because in the worst case, many queries' value ranges may contain no numbers at all.

??? note "Reference Code"

```cpp
#include <algorithm>
#include <cstdio>
#include "gap.h"
long long findGap(int T, int N) {
  static long long a[100005] = {}, ans = 0;
  long long s = 0, t = 1e18, s1, t1;
  if (T == 1) {
    int l = 1, r = N;
    while (l <= r) {
      MinMax(s, t, &s1, &t1);
      a[l++] = s1, a[r--] = t1;
      s = s1 + 1, t = t1 - 1;
    }
    for (int i = 2; i <= N; i++) ans = std::max(ans, a[i] - a[i - 1]);
  } else if (T == 2) {
    MinMax(s, t, &s1, &t1);
    ans = (t1 - s1) / (N - 1);
    long long l = s1 + 1, r = t1, last = s1;
    for (long long i = l; i <= r;) {
      MinMax(i, i + ans, &s1, &t1);
      i += ans + 1;
      if (s1 != -1) ans = std::max(ans, s1 - last), last = t1;
    }
  }
  return ans;
}
```

## CF750F New Year and Finding Roots

Seeing the strict requirements of $h \le 7$ and query count $\le 16$, we need to very strictly maximize the use of information obtained from each access.

When $h \le 4$, we can directly use brute force enumeration. However, when $h > 4$, a very efficient traversal algorithm is needed. Random sampling is not a good method, because random sampling cannot determine whether it is close enough to the root node, and with purely random sampling, the probability of hitting the root node at least once is $1 - (\frac{2 ^ h - 2}{2 ^ h - 1})$, which is still very small even after excluding duplicate samples.

Since $1 \le k \le 3$, and we don't know which direction is closer to the root node, we consider the worst case: if $k = 3$, the first two traversal directions are away from the root node, and the third traversal direction is toward the root node. So we must traverse in all three directions.

Consider BFS and DFS as two traversal methods. Since the BFS search tree can be very large, we prioritize DFS. Of course, if we know the current depth, and the current depth is small enough that the search tree size within the depth range is less than or equal to the remaining query count, we can directly use BFS. Knowing the current node's depth and the current traversal direction gives a great advantage. However, knowing whether we are traversing toward the root node or toward a leaf node is very difficult. If using DFS, we only know the current direction when we reach the root node ($k = 2$) or a leaf node ($k = 1$). So we need to know the current node's depth as much as possible, and cannot use methods like iterative deepening search where we stop in the middle of traversal.

Consider a random starting node; starting from it, we might encounter the worst case described above. If $k = 1$, we can directly know the current node's depth. If $k = 2$, the current node is the root node. If $k = 3$, we directly consider DFS in all three directions. Considering that two of the directions go directly toward leaf nodes with the same traversal path length; the other direction goes toward the root node, but might accidentally go toward a leaf node midway, resulting in a longer traversal path. At this point, we can calculate the current node's depth. When $k = 1$ or $k = 3$, we need to consider the longer traversal path. We can know the point with the minimum depth on the path (which must have a depth smaller than the starting node). If we mark visited nodes and don't traverse them again, starting from this node, there is only one traversal path. Although this path might still go toward a leaf node, there must also exist a node on this path with a depth smaller than the starting point, and we can continue repeating the above steps from this node. Of course, when we consider the worst case of $h = 7$ (each time moving only one step toward the root, then directly going toward a leaf), we find that if we only use DFS, the worst case requires $\frac{(1 + 7) \times 7}{2} = 28$ queries. However, we already know the starting node's depth, so we can calculate the depths of all traversed nodes, and based on our earlier discussion of BFS, determine whether we can directly BFS from the point with the minimum depth. At this point, we can calculate that the worst case requires 17 queries. So we consider removing one node from the search tree (based on the property that DFS can only traverse blindly, we consider BFS): when performing BFS at depth $k$, the search tree has at worst $2 ^ k - 1$ nodes, and it may require $2 ^ k - 1$ queries to determine which node has exactly 2 neighbors. However, if we have already queried $2 ^ k - 2$ nodes, we can know that the last node must be the root node. At this point, the optimal solution in the worst case is: when $h = 7$, starting DFS from a leaf node, each time moving only one step toward the root then directly going toward a leaf. After 10 queries, the depth of the currently known minimum-depth node is 4. Since its parent is known, we directly BFS from its parent (the search tree has depth 3 and $2 ^ 3 - 1 = 7$ nodes). After making $2 ^ 3 - 2 = 6$ queries during BFS, we determine that the last node in the BFS search tree is the root node. At this point, our algorithm can just fit within the worst case of 16 queries.

??? note "Reference Code"

```cpp
#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
constexpr int N = 256 + 5;
int T, h, chance;
bool ok;
vector<int> to[N], path;
bool read(int x) {
  if (to[x].empty()) {
    printf("? %d\n", x), fflush(stdout);
    int k, t;
    scanf("%d", &k);
    if (k == 0) exit(0);
    for (int i = 0; i < k; i++) {
      scanf("%d", &t);
      to[x].push_back(t);
    }
    if (k == 2) {
      printf("! %d\n", x), fflush(stdout);
      return ok = true;
    }
    chance--;
  }
  return false;
}
bool dfs(int x) {
  if (to[x].empty()) path.push_back(x);
  if (read(x)) return true;
  for (int i : to[x])
    if (to[i].empty()) return dfs(i);
  return false;
}
void bfs(int s, int k) {
  queue<int> q;
  for (int i : to[s])
    if (to[i].empty()) q.push(i);
  for (int i = 1; i < k; i++) {
    int x = q.front();
    q.pop();
    if (read(x)) return;
    for (int j : to[x])
      if (to[j].empty()) q.push(j);
  }
  for (int i = 1; i < k; i++) {
    int x = q.front();
    q.pop();
    if (read(x)) return;
  }
  printf("! %d\n", q.front()), fflush(stdout);
}
int main() {
  for (scanf("%d", &T); T--;) {
    ok = false;
    for (int i = 0; i < N; i++) to[i].clear();
    chance = 16;
    scanf("%d", &h);
    if (h == 0) exit(0);
    vector<int> long_path;
    if (read(1)) continue;
    int root, dep;
    if (to[1].size() == 1)
      root = 1, dep = h;
    else {
      for (int i : to[1]) {
        path.clear();
        if (dfs(i)) break;
        if (path.size() > long_path.size()) swap(path, long_path);
      }
      if (ok) continue;
      dep = h - (path.size() + long_path.size()) / 2;
      root = long_path.at((long_path.size() - (h - dep)) - 1);
    }
    while ((1 << (dep - 1)) - 2 > chance) {
      path.clear();
      if (dfs(root)) break;
      dep = h - (h - dep + path.size()) / 2;
      root = path.at((path.size() - (h - dep)) - 1);
    }
    if (!ok) bfs(root, 1 << (dep - 2));
  }
  return 0;
}
```

## UVa12731 太空站之谜 Mysterious Space Station

Since the only feedback is whether the robot hits a wall when moving, we should consider walking as close to the wall as possible without losing the robot. This has several advantages:

- When walking near a wall, it is easy to know whether we will hit a wall, obtaining as much information as possible.
- The cells along the wall are cells where teleporters cannot appear, which can prevent the robot from getting lost.

So, if we know that the robot might be at a certain position along the wall, to determine whether the robot is actually at this position, we can use the [Wall Follower algorithm](https://en.wikipedia.org/wiki/Maze_solving_algorithm) to confirm. According to topological principles, in a maze with walls on both sides, if you enter from the entrance and always keep one hand on the same wall, you are guaranteed to find the exit. Since the walls in this problem are closed, you only need to walk along the path next to the wall to guarantee returning to the starting point without hitting any wall. Additionally, since the path along the wall is the largest closed loop on the map, in actual code, there is no need to deliberately hit walls to ensure the robot is along the wall; you can use markers to indicate the wall-side path on the map. Moreover, once a wall is hit, you should quickly retrace your path, which both avoids losing the robot and reduces the number of steps.

From the above, we can infer a trial-and-error method to determine whether the robot is at a specific cell: walk the robot to the wall-side path without stepping onto unknown cells or known teleporters, then walk a full circle along the wall-side path. If no wall is hit during this process, we can confirm that the robot is indeed at the specific cell.

We can use the above method: first mark all unknown cells in the map, then determine whether each unknown cell is a teleporter from top to bottom, left to right. First walk to the cell above the unknown cell, then walk down and left. Then use the above method to determine whether the robot is to the left of the unknown cell. If not, it means the robot is not at the expected position, i.e., the unknown cell is a teleporter.

After finding the unknown cells, we need to determine the pairing relationship of the 2k unknown cells. The actual method is also very simple: just use brute-force pairing. Since $k \le 5$, at most only $9 + 7 + 5 + 3$ trial-and-error attempts are needed. In contrast, determining the status of all unknown cells in the map requires at most $121 - 40$ trial-and-error attempts.

Since the code below can only pass the UOJ mirror problem: [#247.【Rujia Liu's Present 7】Mysterious Space Station](http://uoj.ac/problem/247), but cannot pass the original UVa problem. Even after modifying Liu Rujia's reference solution on UOJ, it still cannot pass, and we are temporarily unable to contact Liu Rujia. So the code below is based on UOJ. However, Liu Rujia's reference solution is of much higher quality than the code below. You can view the [reference solution that passed the UOJ mirror problem](http://uoj.ac/submission/105789) on UOJ. Under the same test data, the reference solution uses significantly fewer moves.

??? note "Reference Code"

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#define Wall 0
#define Unknown 1
#define Space 2
#define Gate 3
#define Path 4
const int N = 20;
const int dir[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0},
                       {-1, 1}, {1, 1}, {1, -1}, {-1, -1}};
const char dirs[5] = "ESWN";
int n, m, k;
int a[N][N], id[N][N];
struct point {
  int x, y;
  point(int x = 0, int y = 0) : x(x), y(y) {}
  bool operator==(const point& tmp) const { return x == tmp.x && y == tmp.y; }
  bool operator!=(const point& tmp) const { return !(*this == tmp); }
  point side(int d) const { return point(x + dir[d][0], y + dir[d][1]); }
  int check(int d) { return a[x + dir[d][0]][y + dir[d][1]]; }
  int id() { return ::id[x][y]; }
} start;
std::vector<std::pair<point, int>> path;
std::pair<point, point> ans[N];
std::pair<point, bool> vis[N];
bool walk(int d) {
  printf("MoveRobot %c\n", dirs[d]);
  fflush(stdout);
  int ret;
  scanf("%d", &ret);
  return ret;
}
bool walk(int d, std::stack<int>& st) {
  if (walk(d)) {
    st.push(d);
    return true;
  }
  return false;
}
bool read() {
  if (scanf("%d%d%d", &n, &m, &k) != 3) return false;
  if (n == 0) return false;
  memset(a, 0, sizeof(a));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      char c;
      std::cin >> c;
      if (c == 'S') start = point(i, j);
      if (c == '*')
        a[i][j] = Wall;
      else
        a[i][j] = Unknown;
    }
  return true;
}
void answer() {
  for (int i = 0; i < k; i++)
    printf("Answer %d %d\n", ans[i].first.id(), ans[i].second.id());
  fflush(stdout);
}
// Wall follower method: since the Path along the wall is a maximal closed loop,
// we only need to not hit obstacles while walking along the Path
void wall_follower_init(point x, int last, int wallside, point s) {
  if (x == s && !path.empty()) return;
  if (x.check(wallside) == Path) {
    path.push_back(std::make_pair(x, wallside));
    wall_follower_init(x.side(wallside), wallside, last ^ 2, s);
  } else if (x.check(last) == Wall) {
    for (int i = 0; i < 4; i++)
      if (i != (last ^ 2) && x.check(i) != Wall) {
        path.push_back(std::make_pair(x, i));
        wall_follower_init(x.side(i), i, last, s);
        return;
      }
  } else {
    path.push_back(std::make_pair(x, last));
    wall_follower_init(x.side(last), last, wallside, s);
  }
}
void init() {
  int cnt = 1;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      if (a[i][j] == Unknown) {
        id[i][j] = cnt++;
        for (int k = 0; k < 8; k++)
          if (point(i, j).check(k) == Wall) {
            a[i][j] = Path;
            break;
          }
      } else
        id[i][j] = 0;
    }
  path.clear();
  int wallside = 0, last = 0;
  for (int i = 0; i < 4; i++)
    if (start.check(i) == Wall) {
      wallside = i;
      break;
    }
  for (int i = 0; i < 4; i++)
    if (start.check(i) == Path && i != (wallside ^ 2)) {
      last = i;
      break;
    }
  wall_follower_init(start, last, wallside, start);
}
void undo(std::stack<int>& st) {
  while (!st.empty()) walk(st.top() ^ 2), st.pop();
}
bool wall_follower(point x) {
  std::stack<int> st;
  bool ok = true;
  int i = 0;
  while (i < path.size() && path[i].first != x) i++;
  for (int j = i; ok && j < path.size(); j++) {
    if (walk(path[j].second))
      st.push(path[j].second);
    else
      ok = false;
  }
  for (int j = 0; ok && j < i; j++) {
    if (walk(path[j].second))
      st.push(path[j].second);
    else
      ok = false;
  }
  if (!ok) undo(st);
  return ok;
}
// Determine whether we are currently at x, using a
// cautious approach: just walk along directions that avoid obstacles,
// unknown cells, and teleporters until reaching a Path.
// Used when finding teleporters and pairing teleporters
void bfs(point s, point t, std::vector<int>& v) {
  static int map[N][N] = {};
  memset(map, -1, sizeof(map));
  std::queue<point> q;
  map[s.x][s.y] = 4;
  q.push(s);
  while (!q.empty()) {
    point x = q.front();
    q.pop();
    if (x == t) break;
    for (int i = 0; i < 4; i++) {
      point y = x.side(i);
      if ((x.check(i) == Path || x.check(i) == Space) && map[y.x][y.y] == -1) {
        map[y.x][y.y] = i;
        q.push(y);
      }
    }
  }
  for (point x = t; x != s; x = x.side(map[x.x][x.y] ^ 2)) {
    v.push_back(map[x.x][x.y]);
  }
  std::reverse(v.begin(), v.end());
}
bool move(point s, point t, std::stack<int>& st) {
  // Used when approaching a teleporter
  static std::vector<int> v;
  v.clear();
  bfs(s, t, v);
  for (int i : v)
    if (!walk(i, st)) return false;
  return true;
}
// Move toward the wall as quickly as possible
bool make_sure(point x, int last) {
  if (a[x.x][x.y] == Path) return wall_follower(x);
  for (int i = 0; i < 4; i++)
    if ((x.check(i) == Path || x.check(i) == Space) && i != (last ^ 2)) {
      if (!walk(i)) return false;
      bool ret = make_sure(x.side(i), i);
      walk(i ^ 2);
      return ret;
    }
  return false;
}
void find_gate() {
  int cnt = 0;
  std::stack<int> st;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (cnt == k * 2 && a[i][j] == Unknown)
        a[i][j] = Space;
      else if (a[i][j] == Unknown) {
        bool ok = true;
        if (!move(start, point(i - 1, j), st))
          ok = false;
        else if (!walk(1, st))
          ok = false;
        else if (!walk(2, st))
          ok = false;
        else if (!make_sure(point(i, j - 1), -1))
          ok = false;
        if (!ok) {
          vis[cnt++] = std::make_pair(point(i, j), false);
          a[i][j] = Gate;
          for (int k = 0; k < 8; k++) {
            point y = point(i, j).side(k);
            if (point(i, j).check(k) == Unknown) a[y.x][y.y] = Space;
          }
        } else
          a[i][j] = Space;
        undo(st);
      }
}
void make_gate_pair() {
  int cnt = 0;
  std::stack<int> st;
  for (int i = 0; i < k * 2; i++)
    if (!vis[i].second)
      for (int j = 0; !vis[i].second && j < k * 2; j++)
        if (j != i && !vis[j].second) {
          bool ok = true;
          if (!move(start, vis[i].first.side(2), st))
            ok = false;
          else if (!walk(0, st))
            ok = false;
          else if (!make_sure(vis[j].first.side(0), -1))
            ok = false;
          if (ok) {
            ans[cnt++] = std::make_pair(vis[i].first, vis[j].first);
            vis[i].second = vis[j].second = true;
          }
          undo(st);
        }
}
int main() {
  while (read()) {
    init();
    find_gate();
    make_gate_pair();
    answer();
  }
  return 0;
}
```

## Exercises

- [Liu Rujia's interactive problem special competition Rujia Liu's Present 7 is of very high quality, recommended to try.](https://onlinejudge.org/contests/328-9976a2e2/)
- [P5473[NOI2019]I 君的探险](https://www.luogu.com.cn/problem/P5473)
- [P5208[WC2019]I 君的商店](https://www.luogu.com.cn/problem/P5208)

## References and Further Reading

- [Implementing interactive problem functionality for online judges using Linux pipes](https://www.cnblogs.com/tsreaper/p/pipe-interactive.html)
