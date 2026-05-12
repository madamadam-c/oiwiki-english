author: H-J-Granger, Chrogeek, countercurrent-time, Enter-tainer, Great-designer, iamtwz, Ir1d, ksyx, mao1t, Menci, NachtgeistW, Nanarikom, ShaoChenHeng, StudyingFather, SukkaW, Tiphereth-A, zyj-111

## Definition of Definite Integral

Simply put, the definite integral $\int_{l}^{r}f(x)\mathrm{d}x$ of a function $f(x)$ over the interval $[l,r]$ refers to the area between the curve $f(x)$ and the x-axis over the interval $[l,r]$ (where the part above the x-axis is positive and the part below is negative).

In many cases, we need to efficiently and accurately compute an approximate value of an integral. **Simpson's method**, introduced below, is such a method for numerical integration.

## Simpson's Method

The idea of this method is to divide the integration interval into several small segments, applying the quadratic function's integral formula to each segment.

??? note "Quadratic Function Integral Formula (Simpson's Formula)"
    For a quadratic function $f(x)=ax^2+bx+c$, we have:
    
    $$
    \int_l^r f(x) {\mathrm d}x = \frac{(r-l)(f(l)+f(r)+4 f(\frac{l+r}{2}))}{6}
    $$
    
    Derivation:
    For a quadratic function $f(x)=ax^2+bx+c$;
    Integrating gives $F(x)=\int_0^x f(x) {\mathrm d}x = \frac{a}{3}x^3+\frac{b}{2}x^2+cx+D$, where D is a constant. Then
    
    $$
    \begin{aligned}
    \int_l^r f(x) {\mathrm d}x &= F(r)-F(l) \\
    &= \frac{a}{3}(r^3-l^3)+\frac{b}{2}(r^2-l^2)+c(r-l) \\
    &=(r-l)(\frac{a}{3}(l^2+r^2+lr)+\frac{b}{2}(l+r)+c) \\
    &=\frac{r-l}{6}(2al^2+2ar^2+2alr+3bl+3br+6c)\\
    &=\frac{r-l}{6}((al^2+bl+c)+(ar^2+br+c)+4(a(\frac{l+r}{2})^2+b(\frac{l+r}{2})+c)) \\
    &=\frac{r-l}{6}(f(l)+f(r)+4f(\frac{l+r}{2}))
    \end{aligned}
    $$

Based on this Simpson's formula, we first introduce a standard Simpson integration method.

### Standard Simpson's Method

In 1743, this method was published in a paper by Thomas Simpson.

#### Description

Given a natural number $n$, divide the interval $[l, r]$ into $2n$ equal subintervals $x$.

$x_i = l + i h, ~~ i = 0 \ldots 2n,$ $h = \frac {r-l} {2n}.$

We can compute the integral value for each small interval $[x_{2i-2}, x_{2i}]$, $i = 1\ldots n$, and summing the integral values of all intervals gives the total integral.

For an interval $[x_{2i-2}, x_{2i}]$, $i = 1\ldots n$, selecting the three points $(x_{2i-2}, x_{2i-1}, x_{2i})$ can form a parabola, yielding a function $P(x)$, which exists and is unique. Computing the integral of the original function over this interval becomes computing the integral of the new quadratic function $P(x)$ over this segment. Thus we can use Simpson's formula to approximate the calculation.

$\int_{x_ {2i-2}} ^ {x_ {2i}} f (x) ~dx \approx \int_{x_ {2i-2}} ^ {x_ {2i}} P (x) ~dx = \left(f(x_{2i-2}) + 4f(x_{2i-1})+(f(x_{2i})\right)\frac {h} {3}$

Summing over all segments yields:

$\int_l ^ r f (x) dx \approx \left(f (x_0) + 4 f (x_1) + 2 f (x_2) + 4f(x_3) + 2 f(x_4) + \ldots + 4 f(x_{2N-1}) + f(x_{2N}) \right)\frac {h} {3}$

#### Error

We directly give the conclusion: the error of standard Simpson's method is:

$$
-\tfrac{1}{90} \left(\tfrac{r-l}{2}\right)^5 f^{(4)}(\xi)
$$

where $\xi$ is some value in the interval $[l,r]$.

#### Implementation

=== "C++"
    ```cpp
    constexpr int N = 1000 * 1000;
    
    double simpson_integration(double a, double b) {
      double h = (b - a) / N;
      double s = f(a) + f(b);
      for (int i = 1; i <= N - 1; ++i) {
        double x = a + h * i;
        s += f(x) * ((i & 1) ? 4 : 2);
      }
      s *= h / 3;
      return s;
    }
    ```

=== "Python"
    ```python
    N = 1000 * 1000
    
    
    def simpson_integration(a, b):
        h = (b - a) / N
        s = f(a) + f(b)
        for i in range(1, N):
            x = a + h * i
            if i & 1:
                s = s + f(x) * 4
            else:
                s = s + f(x) * 2
        s = s * (h / 3)
        return s
    ```

### Adaptive Simpson's Method

The standard method, to ensure accuracy, is inevitably limited by $n$ in terms of time. We should find a more suitable method.

The only remaining problem is how to segment. If the number of segments is too few, the calculation error is large; if too many, the time efficiency is low. We need to find a balance between accuracy and efficiency.

Consider this: if a segment is already very close to a quadratic function, directly applying the formula to compute the integral yields high precision, and there is no need to further divide this segment.

Thus we have such a segmentation method: each time we check the similarity between the current segment and a quadratic function. If it is similar enough, we directly apply the formula to compute; otherwise, we recursively solve by dividing the current segment into left and right halves.

Now there is one remaining problem: how to determine if each segment is similar to a quadratic function?

We compute the integral of the current segment directly using the formula, then divide the current segment at its midpoint into two segments and compute their integrals using the formula. If the integral of the current segment and the sum of the integrals of the two divided segments differ only slightly, we can consider the current segment to be similar to a quadratic function and stop recursive segmentation.

The above is the idea of the adaptive Simpson's method. In the divide-and-conquer check, besides checking if the accuracy is correct, we generally also enforce a minimum number of iterations.

Reference code is as follows:

=== "C++"
    ```cpp
    double simpson(double l, double r) {
      double mid = (l + r) / 2;
      return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6;  // Simpson's formula
    }
    
    double asr(double l, double r, double eps, double ans, int step) {
      double mid = (l + r) / 2;
      double fl = simpson(l, mid), fr = simpson(mid, r);
      if (abs(fl + fr - ans) <= 15 * eps && step < 0)
        return fl + fr + (fl + fr - ans) / 15;  // similar enough, return directly
      return asr(l, mid, eps / 2, fl, step - 1) +
             asr(mid, r, eps / 2, fr, step - 1);  // otherwise divide and recurse
    }
    
    double calc(double l, double r, double eps) {
      return asr(l, r, eps, simpson(l, r), 12);
    }
    ```

=== "Python"
    ```python
    def simpson(l, r):
        mid = (l + r) / 2
        return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6  # Simpson's formula
    
    
    def asr(l, r, eps, ans, step):
        mid = (l + r) / 2
        fl = simpson(l, mid)
        fr = simpson(mid, r)
        if abs(fl + fr - ans) <= 15 * eps and step < 0:
            return fl + fr + (fl + fr - ans) / 15  # similar enough, return directly
        return asr(l, mid, eps / 2, fl, step - 1) + asr(
            mid, r, eps / 2, fr, step - 1
        )  # otherwise divide and recurse
    
    
    def calc(l, r, eps):
        return asr(l, r, eps, simpson(l, r), 12)
    ```

## Exercises

-   [Luogu4525 【Template】 Adaptive Simpson's Method 1](https://www.luogu.com.cn/problem/P4525)
-   [HDU1724 Ellipse](https://acm.hdu.edu.cn/showproblem.php?pid=1724)
-   [NOI2005 Lemon Tree Under the Moon](https://www.luogu.com.cn/problem/P4207)

## References

<https://doi.org/10.1145/321526.321537>: This article discusses improvements to the adaptive Simpson's method, detailing the origin and advantages of the constant `15` used in the code above.