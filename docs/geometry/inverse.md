author: hyp1231, 383494

## Introduction

Inversion is useful for problems involving tangency relationships among multiple circles or lines. By using the properties of inversion and solving the problem in the inverted space, the computation can often be greatly simplified.

## Definition

Given an inversion center $O$ and inversion radius $R$. If points $P$ and $P'$ on the plane satisfy:

-   Point $P'$ lies on ray $\overrightarrow{OP}$
-   $|OP| \cdot |OP'| = R^2$

then points $P$ and $P'$ are called inverse points of each other.

## Explanation

The figure below shows the inversion of a point $P$ on the plane:

![Inv1](./images/inverse1.png)

## Properties

1.  The inverse of a point outside circle $O$ lies inside circle $O$, and vice versa; the inverse of a point on circle $O$ is itself.

2.  For a circle $A$ not passing through point $O$, its inverted figure is also a circle not passing through point $O$.

    ![Inv2](./images/inverse2.png)

    -   Let the radius of circle $A$ be $r_1$, and the radius of its inverted circle $B$ be $r_2$. Then:

        $$
        r_2 = \frac{1}{2}\left(\frac{1}{|OA| - r_1} - \frac{1}{|OA| + r_1}\right) R^2
        $$

    ???+ note "Proof"
        ![Inv3](./images/inverse3.png)
        
        By the definition of inversion:
        
        $$
        \begin{aligned}
        |OC|\cdot|OC'| &= (|OA|+r_1)\cdot(|OB|-r_2) = R^2 \\
        |OD|\cdot|OD'| &= (|OA|-r_1)\cdot(|OB|+r_2) = R^2
        \end{aligned}
        $$
        
        Eliminate $|OB|$ and solve the equations.

    -   Let the coordinates of point $O$ be $(x_0, y_0)$, the coordinates of point $A$ be $x_1, y_1$, and the coordinates of point $B$ be $x_2, y_2$. Then:

        $$
        \begin{aligned}
        x_2 &= x_0 + \frac{|OB|}{|OA|} (x_1 - x_0) \\
        y_2 &= y_0 + \frac{|OB|}{|OA|} (y_1 - y_0)
        \end{aligned}
        $$

        Here $|OB|$ can be computed during the process above for finding $r_2$.

3.  For a circle $A$ passing through point $O$, its inverted figure is a line not passing through point $O$. This is because a point on circle $A$ that is infinitely close to point $O$ has an inverse point infinitely far from point $O$.

    ![Inv4](./images/inverse4.png)

4.  If two figures are tangent and their tangency point is not point $O$, then their inverted figures are also tangent.

## Example

### [ICPC 2013 Hangzhou Regional, Problem of Apollonius](https://acm.hdu.edu.cn/showproblem.php?pid=4773)

#### Problem Summary

Find all circles that pass through a point outside two given circles and are tangent to both circles.

#### Solution

First consider an analytic geometry solution; it seems difficult.

Consider using the point that the desired circle must pass through as the inversion center, with any inversion radius. The inverted figure of the desired circle is a line, by property $3$, and it is tangent to the inverted figures of the two given circles, by property $2$ and property $4$.

Thus after inversion, the problem becomes: find all common tangents of two circles.

After finding the common tangents, invert them back to the original plane.

??? note "Sample Code"
    ```cpp
    #include <algorithm>
    #include <cmath>
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    #include <vector>
    using namespace std;
    
    constexpr double EPS = 1e-8;   // precision coefficient
    const double PI = acos(-1.0);  // pi
    constexpr int N = 4;
    
    // Definition of a point
    struct Point {
      double x, y;
    
      Point(double x = 0, double y = 0) : x(x), y(y) {}
    
      bool operator<(Point A) const { return x == A.x ? y < A.y : x < A.x; }
    };
    
    // Definition of a vector
    using Vector = Point;
    
    // Vector addition
    Vector operator+(Vector A, Vector B) { return Vector(A.x + B.x, A.y + B.y); }
    
    // Vector subtraction
    Vector operator-(Vector A, Vector B) { return Vector(A.x - B.x, A.y - B.y); }
    
    // Scalar multiplication of a vector
    Vector operator*(Vector A, double p) { return Vector(A.x * p, A.y * p); }
    
    // Scalar division of a vector
    Vector operator/(Vector A, double p) { return Vector(A.x / p, A.y / p); }
    
    // Relation with 0
    int dcmp(double x) {
      if (fabs(x) < EPS) return 0;
      return x < 0 ? -1 : 1;
    }
    
    // Vector dot product
    double Dot(Vector A, Vector B) { return A.x * B.x + A.y * B.y; }
    
    // Vector length
    double Length(Vector A) { return sqrt(Dot(A, A)); }
    
    // Vector cross product
    double Cross(Vector A, Vector B) { return A.x * B.y - A.y * B.x; }
    
    // Projection of a point onto a line
    Point GetLineProjection(Point P, Point A, Point B) {
      Vector v = B - A;
      return A + v * (Dot(v, P - A) / Dot(v, v));
    }
    
    // Circle
    struct Circle {
      Point c;
      double r;
    
      Circle() : c(Point(0, 0)), r(0) {}
    
      Circle(Point c, double r = 0) : c(c), r(r) {}
    
      // Return point coordinates for a given polar angle
      Point point(double a) { return Point(c.x + cos(a) * r, c.y + sin(a) * r); }
    };
    
    // Common tangents of two circles. Return the number of tangents; -1 means infinitely many tangents
    // a[i] and b[i] are the tangency points of the i-th tangent on circles A and B respectively
    int getTangents(Circle A, Circle B, Point* a, Point* b) {
      int cnt = 0;
      if (A.r < B.r) {
        swap(A, B);
        swap(a, b);
      }
      double d2 =
          (A.c.x - B.c.x) * (A.c.x - B.c.x) + (A.c.y - B.c.y) * (A.c.y - B.c.y);
      double rdiff = A.r - B.r;
      double rsum = A.r + B.r;
      if (dcmp(d2 - rdiff * rdiff) < 0) return 0;  // contained internally
    
      double base = atan2(B.c.y - A.c.y, B.c.x - A.c.x);
      if (dcmp(d2) == 0 && dcmp(A.r - B.r) == 0) return -1;  // infinitely many tangents
      if (dcmp(d2 - rdiff * rdiff) == 0) {  // internally tangent, one tangent
        a[cnt] = A.point(base);
        b[cnt] = B.point(base);
        ++cnt;
        return 1;
      }
      // Has external common tangents
      double ang = acos(rdiff / sqrt(d2));
      a[cnt] = A.point(base + ang);
      b[cnt] = B.point(base + ang);
      ++cnt;
      a[cnt] = A.point(base - ang);
      b[cnt] = B.point(base - ang);
      ++cnt;
      if (dcmp(d2 - rsum * rsum) == 0) {  // one internal common tangent
        a[cnt] = A.point(base);
        b[cnt] = B.point(PI + base);
        ++cnt;
      } else if (dcmp(d2 - rsum * rsum) > 0) {  // two internal common tangents
        double ang = acos(rsum / sqrt(d2));
        a[cnt] = A.point(base + ang);
        b[cnt] = B.point(PI + base + ang);
        ++cnt;
        a[cnt] = A.point(base - ang);
        b[cnt] = B.point(PI + base - ang);
        ++cnt;
      }
      return cnt;
    }
    
    // Point O is outside circle A; find the inverted circle B of circle A. R is the inversion radius
    Circle Inversion_C2C(Point O, double R, Circle A) {
      double OA = Length(A.c - O);
      double RB = 0.5 * ((1 / (OA - A.r)) - (1 / (OA + A.r))) * R * R;
      double OB = OA * RB / A.r;
      double Bx = O.x + (A.c.x - O.x) * OB / OA;
      double By = O.y + (A.c.y - O.y) * OB / OA;
      return Circle(Point(Bx, By), RB);
    }
    
    // Invert a line into a circle B passing through point O. R is the inversion radius
    Circle Inversion_L2C(Point O, double R, Point A, Vector v) {
      Point P = GetLineProjection(O, A, A + v);
      double d = Length(O - P);
      double RB = R * R / (2 * d);
      Vector VB = (P - O) / d * RB;
      return Circle(O + VB, RB);
    }
    
    // Return true if points A and B are on the same side of the line
    bool theSameSideOfLine(Point A, Point B, Point S, Vector v) {
      return dcmp(Cross(A - S, v)) * dcmp(Cross(B - S, v)) > 0;
    }
    
    int main() {
      int T;
      scanf("%d", &T);
      while (T--) {
        Circle A, B;
        Point P;
        scanf("%lf%lf%lf", &A.c.x, &A.c.y, &A.r);
        scanf("%lf%lf%lf", &B.c.x, &B.c.y, &B.r);
        scanf("%lf%lf", &P.x, &P.y);
        Circle NA = Inversion_C2C(P, 10, A);
        Circle NB = Inversion_C2C(P, 10, B);
        Point LA[N], LB[N];
        Circle ansC[N];
        int q = getTangents(NA, NB, LA, LB), ans = 0;
        for (int i = 0; i < q; ++i)
          if (theSameSideOfLine(NA.c, NB.c, LA[i], LB[i] - LA[i])) {
            if (!theSameSideOfLine(P, NA.c, LA[i], LB[i] - LA[i])) continue;
            ansC[ans++] = Inversion_L2C(P, 10, LA[i], LB[i] - LA[i]);
          }
        printf("%d\n", ans);
        for (int i = 0; i < ans; ++i) {
          printf("%.8f %.8f %.8f\n", ansC[i].c.x, ansC[i].c.y, ansC[i].r);
        }
      }
    
      return 0;
    }
    ```

## Exercises

[ICPC 2017 Nanning Regional Online Contest, Finding the Radius for an Inserted Circle](https://vjudge.net/problem/%E8%AE%A1%E8%92%9C%E5%AE%A2-A1283)

[CCPC 2017 Online Contest, The Designer](https://acm.hdu.edu.cn/showproblem.php?pid=6158)

## References and Further Reading

-   [Inversive geometry - Wikipedia](https://en.wikipedia.org/wiki/Inversive_geometry)

-   [Circle Inversion - ACdreamers' Blog](https://blog.csdn.net/acdreamers/article/details/16966369)
