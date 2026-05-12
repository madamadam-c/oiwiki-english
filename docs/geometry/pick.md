## Pick's Theorem

Pick's theorem: given a simple polygon whose vertices are all lattice points, Pick's theorem describes the relationship between its area ${\displaystyle A}$, the number of interior lattice points ${\displaystyle i}$, and the number of lattice points on its boundary ${\displaystyle b}$: ${\displaystyle A=i+{\frac {b}{2}}-1}$.

For the proof, see [Pick's theorem](https://en.wikipedia.org/wiki/Pick%27s_theorem).

It has the following generalizations:

-   Take the area of the fundamental lattice cell as one unit. Pick's theorem still holds on a parallelogram lattice. On an arbitrary triangular lattice, Pick's theorem becomes ${\displaystyle A=2 \times i+b-2}$.
-   For a non-simple polygon ${\displaystyle P}$, Pick's theorem is ${\displaystyle A=i+{\frac {b}{2}}-\chi (P)}$, where ${\displaystyle \chi (P)}$ denotes the **Euler characteristic** of ${\displaystyle P}$.
-   Higher-dimensional generalization: Ehrhart polynomial.
-   Pick's theorem is equivalent to **Euler's formula** (${\displaystyle V-E+F=2}$).

## Example ([POJ 1265](http://poj.org/problem?id=1265))

### Problem Summary

In a Cartesian coordinate system, a robot starts from an arbitrary point and makes $\textit{n}$ moves. Each move goes $\textit{dx}$ to the right and $\textit{dy}$ upward. The path eventually forms a closed simple polygon on the plane. Find the number of points on the boundary, the number of points inside the polygon, and the area of the polygon.

### Solution

This problem uses the following three facts:

-   For a segment whose endpoints are lattice points, if both $\textit{dx}$ and $\textit{dy}$ are not $0$, the number of lattice points it passes through is $\gcd(\textit{dx}, \textit{dy}) + 1$. Of course, when counting an entire polygon, the extra endpoint will be counted by the previous edge, so it should not be added again. Therefore, the number of points covered by one edge is $\gcd(\textit{dx},\textit{dy})$, where $\textit{dx},\textit{dy}$ are the horizontal and vertical spans of the segment respectively. If $\textit{dx}$ or $\textit{dy}$ is $0$, the number of covered points is $\textit{dy}$ **or** $\textit{dx}$.
-   Pick's theorem: the area of a simple polygon on the plane whose vertices are lattice points = number of boundary points / 2 + number of interior points - 1.
-   The area of any polygon equals half the sum, in order, of the cross products of the vectors formed by each pair of adjacent vertices and the origin. This can also be derived by clockwise line integration.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/geometry/code/pick/pick_1.cpp"
    ```
