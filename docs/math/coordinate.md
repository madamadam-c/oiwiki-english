author: Ir1d, HeRaNO, Chrogeek, abc1763613206, mxdyzmx

## Definition of Angles

In primary or middle school, the **static definition** of an angle is taught: a figure formed by two rays with a common endpoint.

However, this definition limits angles to $[0, 360^\circ]$, which brings difficulties for deeper study, and other issues cannot be explained clearly, such as: what does rotating $720^\circ$ mean?

In high school mathematics, the **dynamic definition** of an angle is introduced: a figure formed by a ray rotating around its endpoint in a plane from one position to another.

The starting position is called the **initial side**, and the ending position is called the **terminal side**. The conventions are:

-   Angles rotated **counterclockwise** are called **positive angles**, with positive measure;
-   Angles rotated **clockwise** are called **negative angles**, with negative measure;
-   Angles where the terminal side has no rotation relative to the initial side are called **zero angles**, with measure $0^\circ$.

This extends the concept of angles to **any angle**.

???+ note "Note"
    The initial and terminal sides of a zero angle coincide, but not all angles with coinciding initial and terminal sides are zero angles, such as angles with multiples of $360^\circ$.

## Radian Measure

In practical applications, angles often need to be converted to various parameters, and using radian measure to describe angles can reduce the use of coefficients. Therefore, let us introduce **radian measure**:

An angle subtended by an arc whose length equals the radius is called a **1 radian angle**, denoted by the symbol $\text{rad}$, read as: radian.

According to the conventions above, positive angles have positive radian measure, negative angles have negative radian measure, and zero angles have radian measure $0$. If the arc length subtended by the central angle $\alpha$ of a circle with radius $r$ is $l$, then:

$$
|\alpha|=\dfrac{l}{r}
$$

Using this formula, arc length and sector area formulas can also be derived, which are omitted here.

Thus, a $360^\circ$ angle has a radian measure of $2\pi$. With this correspondence, conversion between degree values and radian measure is possible:

$$
k \operatorname{rad} = \frac{\pi}{180^\circ} n^\circ
$$

Consider an angle; if we rotate its terminal side by another full circle, or even multiple circles, while the initial side remains fixed, the terminal side position is always the same. Such angles are called **coterminal angles**.

The set of angles coterminal with angle $\alpha$ is easily found to be $\{\varphi \mid \varphi = \alpha + 2k\pi, k \in \mathbf{Z}\}$.

This can be understood as: continuously adding a full rotation to this angle's sides keeps the terminal side position unchanged.

???+ note "$\pi$ and $\tau$: two mathematical constants"
    Currently, there is a viewpoint in Western mathematics that the "true circle constant" should be $2\pi$, denoted by the Greek letter $\tau$. Supporters of the new circle constant celebrate the "true" Pi Day on June 28.
    
    For example, in radian measure, a full circle is $2\pi$, and dividing $2\pi$ directly gives equal divisions of a full circle. Another example is the frequent appearance of $2\pi$ in complex analysis, and so on.
    
    To conform to the conventional usage in various regions of China, **OI Wiki** uses the parameter $\pi$ to represent the ratio of a circle's circumference to its diameter.

???+ note "Conventional representation of $\pi$ in programming"
    In C/C++, $\pi$ is generally taken as `acos(-1)`, as this value is the closest floating-point number to $\pi$. The $\pi$ written using `acos(-1)` or `4 * atan(1)` is $3.14159265358979310000$.
    
    Using other values, such as `acos(-1.0/2.0)`, `acos(1.0/2.0)`, `asin(1.0/2.0)`, etc., produces $\pi$ as $3.14159265358979360000$, which is not the closest floating-point number to $\pi$.
    
    If you can memorize it, you can also directly write $3.1415926535897932$.

## Rectangular Coordinate System in the Plane

A plane rectangular coordinate system (Rectangular Coordinates) consists of two perpendicular number axes in the same plane sharing a common origin.

Typically, the two number axes are placed horizontally and vertically, with the directions to the right and upward being the positive directions of the two axes respectively. The horizontal number axis is called the $x$-axis (x-axis) or abscissa axis, and the vertical number axis is called the $y$-axis (y-axis) or ordinate axis. The $x$-axis and $y$-axis are collectively called the coordinate axes, and their common origin $O$ is called the **origin** of the plane rectangular coordinate system. A plane rectangular coordinate system with $O$ as the origin is denoted as the plane rectangular coordinate system $xOy$.

The $x$-axis and $y$-axis divide the coordinate plane into four **quadrants** (quadrant). The upper-right part is called the first quadrant, and the other three parts are called the second, third, and fourth quadrants in counterclockwise order. Quadrants are bounded by the number axes; points on the axes and the origin do not belong to any quadrant. In general, the $x$-axis and $y$-axis use the same unit length, but in special cases, different unit lengths can be used.

### Describing Positions in the Plane Rectangular Coordinate System

In a plane rectangular coordinate system, for any point in the plane, there is a unique ordered pair (the point's **coordinates**) corresponding to it. Conversely, for any ordered pair, there is a unique point in the plane corresponding to it.

For any point $C$ in the plane, draw perpendicular lines from $C$ to the $x$-axis and $y$-axis. The points $a$ and $b$, the projections on the $x$-axis and $y$-axis respectively, are called the **abscissa** and **ordinate** of point $C$. The ordered pair (ordered pair) $(a, b)$ is called the **rectangular coordinates** of point $C$. A point in different quadrants or on different axes has different coordinates.

## Polar Coordinate System in the Plane

Consider real situations, such as navigation: you might say "point $B$ is $30^\circ$ east of north from point $A$, at a distance of $100$ meters," rather than "establish a plane rectangular coordinate system with $A$ as the origin, $B(50,50\sqrt 3)$."

Thus:

1.  Choose a fixed point $O$ on the plane, called the **pole**;
2.  Draw a ray $Ox$ from the pole, called the **polar axis**;
3.  Choose a unit length (usually $1$ in mathematical problems), an angle unit (usually radians), and its positive direction (usually counterclockwise);

This establishes a **polar coordinate system**.

### Describing Positions in the Polar Coordinate System

Let $A$ be a point in the plane.

-   The distance $|OA|$ between the pole $O$ and $A$ is called the **polar radius**, denoted by $\rho$;
-   The angle $\angle xOA$ from the polar axis as the initial side to $OA$ as the terminal side is called the **polar angle**, denoted by $\varphi$;

Then the ordered pair $(\rho,\varphi)$ is the **polar coordinates** of $A$.

By the definition of coterminal angles, $(\rho,\varphi)$ and $(\rho,\varphi + 2k\pi)\ (k\in \mathbf{Z})$ actually represent the same point. In particular, the pole's polar coordinates are $(0,\varphi)\ (\varphi \in \mathbf{R})$, so a point in the plane can have infinitely many polar coordinate representations.

If we require $\rho \ge 0, 0 \le \varphi < 2\pi$, then except for the pole, every point in the plane can be represented by a unique ordered pair $(\rho,\varphi)$, and the point represented by polar coordinates $(\rho,\varphi)$ is uniquely determined.

### Conversion between Plane Rectangular and Polar Coordinate Systems

Of course, sometimes it is inconvenient to study figures in the polar coordinate system. To switch to the rectangular coordinate system for study, there are conversion formulas. The rectangular coordinates $(x,y)$ of point $A(\rho,\varphi)$ can be expressed as follows:

$$
\begin{aligned}
x &= \rho \cos \varphi \\
y &= \rho \sin \varphi
\end{aligned}
$$

From this, we have:

$$
\begin{aligned}
\rho^2 &= x^2 + y^2\\
\tan \varphi &= \frac{y}{x}\ \ \ \ (x\not =0)
\end{aligned}
$$

Thus $\rho = \sqrt{x^2+y^2}$.

However, $\tan\varphi$ with the same $\dfrac{y}{x}$ has two possible values for $\varphi$, so the direction needs to be determined based on the values of $x$ and $y$. Specifically, define the function:

$$
\operatorname{atan2}(y, x) = \begin{cases}
\arctan(\frac{y}{x}) & \text{if } x > 0 \\
\arctan(\frac{y}{x}) + \pi & \text{if } y \ge 0, x < 0 \\
\arctan(\frac{y}{x}) - \pi & \text{if } y < 0, x < 0 \\
\pi/2 & \text{if } y > 0, x = 0 \\
-\pi/2 & \text{if } y < 0, x = 0 \\
\text{any} & \text{if } y = 0, x = 0
\end{cases}
$$

Then $\varphi = \operatorname{atan2}(y, x)$. Note that the range of this function is $(-\pi, \pi]$.

The [function](https://en.cppreference.com/w/cpp/numeric/math/atan2) is defined in the `<math.h>` or `<cmath>` library in C/C++. Simply call `atan2(y, x)`.

## Spatial Rectangular Coordinate System

A spatial rectangular coordinate system is established as follows:

1.  Choose a point $O$ in space;
2.  Through point $O$, draw three mutually perpendicular number axes $\overrightarrow{Ox}, \overrightarrow{Oy}, \overrightarrow{Oz}$, called the $x$-axis (abscissa axis), $y$-axis (ordinate axis), and $z$-axis (applicate axis) respectively, collectively called the coordinate axes. Their positive directions follow the right-hand rule: curl your right hand around the $z$-axis such that your fingers curl from the positive $x$-axis toward the positive $y$-axis; your thumb points in the positive $z$-axis direction;
3.  Set the unit length on each axis, usually $1$.

This forms a spatial rectangular coordinate system, called the spatial rectangular coordinate system $O-xyz$. The fixed point $O$ is called the origin of this coordinate system.

Any two coordinate axes determine a plane, so three mutually perpendicular planes are determined, collectively called coordinate planes. The plane determined by the $x$-axis and $y$-axis is called the $xOy$ plane; similarly, there are the $yOz$ plane and $zOx$ plane. The three coordinate planes divide space into eight parts, each part called an **octant**.

### Describing Positions in the Spatial Rectangular Coordinate System

Once a spatial rectangular coordinate system $O-xyz$ is established, a one-to-one correspondence between points in space and ordered triples can be established.

Let $M$ be a point in space. Pass planes perpendicular to the $x$-axis, $y$-axis, and $z$-axis through $M$. Let the intersection points of the three planes with the $x$-axis, $y$-axis, and $z$-axis be $P, Q, R$ respectively. Points $P, Q, R$ are called the projections of point $M$ on the $x$-axis, $y$-axis, and $z$-axis respectively. Let the coordinates of points $P, Q, R$ on the $x$-axis, $y$-axis, and $z$-axis be $x, y, z$ respectively. Then point $M$ determines an ordered triple $(x, y, z)$.

Conversely, given an ordered triple $(x, y, z)$, take point $P$ on the $x$-axis with coordinate $x$, point $Q$ on the $y$-axis with coordinate $y$, and point $R$ on the $z$-axis with coordinate $z$. Then through points $P, Q, R$, draw three planes perpendicular to the $x$-axis, $y$-axis, and $z$-axis respectively. These three planes intersect at a point $M$ in space, which is the point determined by the ordered triple $(x, y, z)$.

In this way, a one-to-one correspondence is established between point $M$ in space and the ordered triple $(x, y, z)$. The ordered triple $(x, y, z)$ is called the coordinates of point $M$, denoted $M(x, y, z)$, where $x$ is called the abscissa, $y$ the ordinate, and $z$ the applicate.

## Spatial Cylindrical Coordinate System

The spatial cylindrical coordinate system extends the polar coordinate system to three dimensions: start with the polar coordinate system used in plane work, then add a $z$-axis passing through the pole $O$ perpendicular to the plane, directed upward.

To find the point described by cylindrical coordinates $(\rho, \varphi, z)$, first handle $\rho$ and $\varphi$ in the polar coordinate system, then move up or down along the $z$-axis according to the $z$ coordinate.

### Conversion between Cylindrical and Spatial Rectangular Coordinate Systems

The $z$ values are the same in both systems.

For mutual conversion between $(x,y)$ and $(\rho, \varphi)$, see [Conversion between Plane Rectangular and Polar Coordinate Systems](#conversion-between-plane-rectangular-and-polar-coordinate-systems) above.

## Spatial Spherical Coordinate System

Spherical coordinates can be determined as follows:

1.  Stand at the origin, facing the direction of the horizontal polar axis; the vertical axis points from your feet toward your head;
2.  Raise your arm, pointing in the direction of the vertical polar axis;
3.  Rotate counterclockwise by angle $\varphi$;
4.  Rotate your arm downward by angle $\vartheta$, so your arm points in the direction specified by $\varphi$ and $\vartheta$;
5.  Move a distance $r$ from the origin along this direction.

This reaches the point described by spherical coordinates $(r,\vartheta,\varphi)$. Here, $\vartheta$ is called the **zenith angle**, and $\varphi$ is called the **azimuth**.

???+ warning "Warning"
    For various reasons, some sources use $\phi$ for the zenith angle and $\theta$ for the azimuth. Be sure to pay attention to this when reading articles about spherical coordinates.
    
    Also, when writing articles, if spherical coordinates are used, it is recommended to clearly declare which symbols represent the zenith angle and azimuth.

### Conversion between Cylindrical and Spherical Coordinate Systems

The $\varphi$ values are the same in both systems.

From cylindrical to spherical coordinates:

$$
\begin{aligned}
r &= \sqrt{\rho^2 + z^2} \\
\vartheta &= \begin{cases}
\arctan\left(\frac{\rho}{z}\right) & \text{if }z > 0 \\
\pi/2 & \text{if }z = 0, \rho \not= 0 \\
\arctan\left(\frac{\rho}{z}\right) + \pi & \text{if }z < 0 \\
\end{cases}
\end{aligned}
$$

Note that for the point $(0,0,0)$ in cylindrical coordinates, the $\vartheta$ of its spherical coordinates is undefined.

From spherical to cylindrical coordinates:

$$
\begin{aligned}
\rho &= r \sin \vartheta \\
z &= r \cos \vartheta
\end{aligned}
$$

### Conversion between Spatial Rectangular and Spherical Coordinate Systems

You can combine [Conversion between Plane Rectangular and Polar Coordinate Systems](#conversion-between-plane-rectangular-and-polar-coordinate-systems) above with [Conversion between Cylindrical and Spherical Coordinate Systems](#conversion-between-cylindrical-and-spherical-coordinate-systems) above, or directly use the formulas below:

From spatial rectangular to spherical coordinates:

$$
\begin{aligned}
r &= \sqrt{x^2 + y^2 + z^2} \\
\vartheta &= \arccos\left(\frac{z}{\sqrt{x^2 + y^2 + z^2}}\right) \\
\varphi &= \operatorname{atan2}(y, x)
\end{aligned}
$$

where the definition of $\operatorname{atan2}$ is given in [Conversion between Plane Rectangular and Polar Coordinate Systems](#conversion-between-plane-rectangular-and-polar-coordinate-systems).

Note that for the point $(0,0,0)$ in spatial rectangular coordinates, the values of $\vartheta$ and $\varphi$ in its spherical coordinates are undefined.

From spherical to spatial rectangular coordinates:

$$
\begin{aligned}
x &= r \sin \vartheta \cos \varphi \\
y &= r \sin \vartheta \sin \varphi \\
z &= r \cos \vartheta
\end{aligned}
$$