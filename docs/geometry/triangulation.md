author: xehoth

In geometry, triangulation means subdividing a planar object into triangles and, by extension, subdividing higher-dimensional geometric objects into simplices.
For a given point set, there are many possible triangulations, for example:

![Three triangulations](./images/triangulation-0.svg)

In OI, triangulation mainly refers to perfect triangulation in two-dimensional geometry, namely two-dimensional Delaunay triangulation, abbreviated as DT.

## Delaunay Triangulation

### Definition

In mathematics and computational geometry, for a given discrete point set $P$ in the plane, its Delaunay triangulation DT($P$) satisfies:

1.  Empty circumcircle property: DT($P$) is **unique** if no four points are concyclic. In DT($P$), there is no other point inside the circumcircle of **any** triangle.
2.  Maximization of the minimum angle: among all possible triangulations of point set $P$, the minimum angle among the triangles formed by DT($P$) is maximized. In this sense, DT($P$) is the triangulation **closest to regular**. More specifically, for the diagonal of the convex quadrilateral formed by two adjacent triangles, after swapping the diagonal, the smaller of the two relevant interior angles no longer increases.

![A Delaunay triangulation showing circumcircles](./images/triangulation-1.png)

### Properties

1.  Nearest: triangles are formed by the nearest three points, and all segments, that is, triangle edges, do not intersect.
2.  Uniqueness: no matter where construction starts in the region, the final result is the same, assuming no four points in the point set are concyclic.
3.  Optimality: if the diagonal of the convex quadrilateral formed by any two adjacent triangles can be swapped, then the smallest angle among the six interior angles of the two triangles will not change.
4.  Most regular: if the minimum angle of each triangle in a triangulation is sorted in ascending order, the sequence obtained from the Delaunay triangulation is lexicographically largest.
5.  Locality: adding, deleting, or moving a vertex only affects nearby triangles.
6.  Convex hull boundary: the outermost boundary of the triangulation forms the hull of a convex polygon.

## Divide-and-Conquer Algorithm for Constructing DT

There are many algorithms for constructing DT. Among the $O(n \log n)$ construction algorithms, divide and conquer is the easiest to understand and implement.

The first step in constructing DT by divide and conquer is to sort the given point set by $x$ coordinate in **ascending** order. The figure below shows a sorted point set of size $10$.

![A sorted point set of size 10](./images/triangulation-2.svg)

Once the point set is ordered, we can repeatedly split it into two parts, using divide and conquer, until each subset has size at most $3$. These subsets can then be triangulated immediately as a triangle or a segment.

![Divide and conquer into point sets containing 2 or 3 points](./images/triangulation-3.svg)

Then, during the divide-and-conquer backtracking process, the already triangulated left and right subsets can be merged in order. The merged triangulation contains LL-edges, edges of the left subset; RR-edges, edges of the right subset; and LR-edges, new edges created by connecting the left and right triangulations. In the figure, LL-edges are gray, RR-edges are red, and LR-edges are blue. For the merged triangulation, to maintain the DT properties, we **may** need to delete some LL-edges and RR-edges, but during merging we **will not** add LL-edges or RR-edges.

![edge](./images/triangulation-4.svg)

The first step in merging the left and right triangulations is to insert the base LR-edge. The base LR-edge is the **bottommost** LR-edge that does not intersect **any** LL-edge or RR-edge.

![Merging left and right triangulations](./images/triangulation-5.svg)

Next, we need to determine the LR-edge **immediately above** the base LR-edge. For example, for the right point set, the possible endpoints of the next LR-edge, its right endpoint, are the other endpoints of RR-edges connected to the right endpoint of the base LR-edge, namely points $6, 7, 9$; the left endpoint is point $2$.

![Next LR-edge](./images/triangulation-6.svg)

For possible endpoints, we need to test them by the following two criteria:

1.  The angle between its corresponding RR-edge and the base LR-edge is less than $180$ degrees.
2.  The circle determined by the two endpoints of the base LR-edge and this possible point contains no other **possible point**.

![Testing possible points](./images/triangulation-7.svg)

As shown above, the green circle corresponding to possible point $6$ contains possible point $9$, while the purple circle corresponding to possible point $7$ contains no other possible point. Therefore, point $7$ is the right endpoint of the next LR-edge.

For the left point set, handle it symmetrically.

![Testing possible points on the left](./images/triangulation-8.svg)

When neither the left nor right point set contains any possible point satisfying the criteria, the merge is complete. When a possible point satisfies the criteria, an LR-edge needs to be added. Delete any LL-edge or RR-edge that intersects the LR-edge being added.

When both the left and right point sets have possible points, check whether the circle corresponding to the left point contains the right point; if it does, it is invalid. Do the same check for the right point. Usually only one possible point satisfies the criteria, unless four points are concyclic.

![Next LR-edge](./images/triangulation-9.svg)

After this LR-edge is added, use it as the base LR-edge and repeat the steps above, adding the next edge until merging is complete.

![Merging](./images/triangulation-10.svg)

## Code

??? note "Implementation"
    ```cpp
    #include <algorithm>
    #include <cmath>
    #include <cstring>
    #include <list>
    #include <utility>
    #include <vector>
    
    constexpr double EPS = 1e-8;
    constexpr int MAXV = 10000;
    
    struct Point {
      double x, y;
      int id;
    
      Point(double a = 0, double b = 0, int c = -1) : x(a), y(b), id(c) {}
    
      bool operator<(const Point &a) const {
        return x < a.x || (fabs(x - a.x) < EPS && y < a.y);
      }
    
      bool operator==(const Point &a) const {
        return fabs(x - a.x) < EPS && fabs(y - a.y) < EPS;
      }
    
      double dist2(const Point &b) {
        return (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y);
      }
    };
    
    struct Point3D {
      double x, y, z;
    
      Point3D(double a = 0, double b = 0, double c = 0) : x(a), y(b), z(c) {}
    
      Point3D(const Point &p) { x = p.x, y = p.y, z = p.x * p.x + p.y * p.y; }
    
      Point3D operator-(const Point3D &a) const {
        return Point3D(x - a.x, y - a.y, z - a.z);
      }
    
      double dot(const Point3D &a) { return x * a.x + y * a.y + z * a.z; }
    };
    
    struct Edge {
      int id;
      std::list<Edge>::iterator c;
    
      Edge(int id = 0) { this->id = id; }
    };
    
    int cmp(double v) { return fabs(v) > EPS ? (v > 0 ? 1 : -1) : 0; }
    
    double cross(const Point &o, const Point &a, const Point &b) {
      return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
    }
    
    Point3D cross(const Point3D &a, const Point3D &b) {
      return Point3D(a.y * b.z - a.z * b.y, -a.x * b.z + a.z * b.x,
                     a.x * b.y - a.y * b.x);
    }
    
    int inCircle(const Point &a, Point b, Point c, const Point &p) {
      if (cross(a, b, c) < 0) std::swap(b, c);
      Point3D a3(a), b3(b), c3(c), p3(p);
      b3 = b3 - a3, c3 = c3 - a3, p3 = p3 - a3;
      Point3D f = cross(b3, c3);
      return cmp(p3.dot(f));  // check same direction, in: < 0, on: = 0, out: > 0
    }
    
    int intersection(const Point &a, const Point &b, const Point &c,
                     const Point &d) {  // seg(a, b) and seg(c, d)
      return cmp(cross(a, c, b)) * cmp(cross(a, b, d)) > 0 &&
             cmp(cross(c, a, d)) * cmp(cross(c, d, b)) > 0;
    }
    
    class Delaunay {
     public:
      std::list<Edge> head[MAXV];  // graph
      Point p[MAXV];
      int n, rename[MAXV];
    
      void init(int n, Point p[]) {
        memcpy(this->p, p, sizeof(Point) * n);
        std::sort(this->p, this->p + n);
        for (int i = 0; i < n; i++) rename[p[i].id] = i;
        this->n = n;
        divide(0, n - 1);
      }
    
      void addEdge(int u, int v) {
        head[u].push_front(Edge(v));
        head[v].push_front(Edge(u));
        head[u].begin()->c = head[v].begin();
        head[v].begin()->c = head[u].begin();
      }
    
      void divide(int l, int r) {
        if (r - l <= 2) {  // #point <= 3
          for (int i = l; i <= r; i++)
            for (int j = i + 1; j <= r; j++) addEdge(i, j);
          return;
        }
        int mid = (l + r) / 2;
        divide(l, mid);
        divide(mid + 1, r);
    
        std::list<Edge>::iterator it;
        int nowl = l, nowr = r;
    
        for (int update = 1; update;) {
          // find left and right convex, lower common tangent
          update = 0;
          Point ptL = p[nowl], ptR = p[nowr];
          for (it = head[nowl].begin(); it != head[nowl].end(); it++) {
            Point t = p[it->id];
            double v = cross(ptR, ptL, t);
            if (cmp(v) > 0 || (cmp(v) == 0 && ptR.dist2(t) < ptR.dist2(ptL))) {
              nowl = it->id, update = 1;
              break;
            }
          }
          if (update) continue;
          for (it = head[nowr].begin(); it != head[nowr].end(); it++) {
            Point t = p[it->id];
            double v = cross(ptL, ptR, t);
            if (cmp(v) < 0 || (cmp(v) == 0 && ptL.dist2(t) < ptL.dist2(ptR))) {
              nowr = it->id, update = 1;
              break;
            }
          }
        }
    
        addEdge(nowl, nowr);  // add tangent
    
        for (int update = 1; true;) {
          update = 0;
          Point ptL = p[nowl], ptR = p[nowr];
          int ch = -1, side = 0;
          for (it = head[nowl].begin(); it != head[nowl].end(); it++) {
            if (cmp(cross(ptL, ptR, p[it->id])) > 0 &&
                (ch == -1 || inCircle(ptL, ptR, p[ch], p[it->id]) < 0)) {
              ch = it->id, side = -1;
            }
          }
          for (it = head[nowr].begin(); it != head[nowr].end(); it++) {
            if (cmp(cross(ptR, p[it->id], ptL)) > 0 &&
                (ch == -1 || inCircle(ptL, ptR, p[ch], p[it->id]) < 0)) {
              ch = it->id, side = 1;
            }
          }
          if (ch == -1) break;  // upper common tangent
          if (side == -1) {
            for (it = head[nowl].begin(); it != head[nowl].end();) {
              if (intersection(ptL, p[it->id], ptR, p[ch])) {
                head[it->id].erase(it->c);
                head[nowl].erase(it++);
              } else {
                it++;
              }
            }
            nowl = ch;
            addEdge(nowl, nowr);
          } else {
            for (it = head[nowr].begin(); it != head[nowr].end();) {
              if (intersection(ptR, p[it->id], ptL, p[ch])) {
                head[it->id].erase(it->c);
                head[nowr].erase(it++);
              } else {
                it++;
              }
            }
            nowr = ch;
            addEdge(nowl, nowr);
          }
        }
      }
    
      std::vector<std::pair<int, int>> getEdge() {
        std::vector<std::pair<int, int>> ret;
        ret.reserve(n);
        std::list<Edge>::iterator it;
        for (int i = 0; i < n; i++) {
          for (it = head[i].begin(); it != head[i].end(); it++) {
            if (it->id < i) continue;
            ret.push_back(std::make_pair(p[i].id, p[it->id].id));
          }
        }
        return ret;
      }
    };
    ```

## Voronoi Diagram

A Voronoi diagram consists of continuous polygons formed by perpendicular bisectors of the lines connecting neighboring points. Given $n$ distinct seed points on the plane, it divides the plane into $n$ regions such that every point in a region is closer to that region's seed point than to any other region's seed point.

The Voronoi diagram is the dual graph of the Delaunay triangulation. We can use the divide-and-conquer algorithm for constructing Delaunay triangulation to obtain the triangulation, then use the leftmost-turn line algorithm to obtain its dual graph, constructing the Voronoi diagram in $O(n \log n)$ time.

## Problems

[SGU 383 Caravans](https://codeforces.com/problemsets/acmsguru/problem/99999/383) triangulation + binary lifting

[ContestHunter. Endless Destruction](http://noi-test.zzstep.com/contest/Beta%20Round%20%EF%BC%832%20%28%E6%96%B0%E7%96%86%E7%9C%81%E9%98%9F%E4%BA%92%E6%B5%8BWeek1-Day2%29/%E6%97%A0%E5%B0%BD%E7%9A%84%E6%AF%81%E7%81%AD) build the dual graph from triangulation to construct a Voronoi diagram

[Codeforces Gym 103485M. Constellation collection](https://codeforces.com/gym/103485/problem/M) build a graph after triangulation and run flood fill

## References and Further Reading

1.  [Wikipedia - Triangulation (geometry)](https://en.wikipedia.org/wiki/Triangulation_%28geometry%29)
2.  [Wikipedia - Delaunay triangulation](https://en.wikipedia.org/wiki/Delaunay_triangulation)
3.  Samuel Peterson -[Computing Constrained Delaunay Triangulations in 2-D (1997-98)](http://www.geom.uiuc.edu/~samuelp/del_project.html)
