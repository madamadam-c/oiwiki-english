author: mwsht, sshwy, ouuan, Ir1d, Henry-ZHR, hsfzLZH1

## Introduction

The hoverline method applies to a subset of monotonic-stack problems. Specifically, the hoverline method can be applied to problems satisfying the following conditions:

-   Monotonic information must be maintained while scanning a sequence;
-   The problem can be solved with a monotonic stack;
-   Binary search on the monotonic stack is not needed.

It may seem that the hoverline method can be replaced and is not very useful, but its concept is simpler than a monotonic stack and is more suitable for beginning OI contestants to understand and solve problems such as maximum submatrix.

## Examples

???+ note "[SPOJ HISTOGRA - Largest Rectangle in a Histogram](https://www.spoj.com/problems/HISTOGRA)"
    Summary: on a horizontal line there are $n$ rectangles of width $1$; find the area of the largest subrectangle contained in these rectangles.

A hoverline is a vertical line. This vertical line has two properties: initial position and height. It can move left and right as long as its upper endpoint does not exceed the height of the rectangle at the current position.

For a hoverline, under the premise that its upper endpoint does not exceed the current rectangle height and it does not move outside the boundary, we move it left and right to find the farthest positions it can expand to on both sides. The area swept by this hoverline is then the largest possible rectangle containing this hoverline. It is easy to see that the maximum subrectangle must contain a hoverline whose initial position is $i$ and whose height is $h_i$. Enumerating this process has time complexity $O(n ^ 2)$, but the hoverline method optimizes it to $O(n)$.

Consider how to quickly find the leftmost position a hoverline can reach.

### Procedure

Define $l_i$ as the current leftmost position to which the hoverline at position $i$ can expand. Clearly, $l_i$ is initially $i$, and we need to further determine whether it can continue expanding left.

-   If the current $l_i = 1$, it has already expanded to the boundary and cannot continue.
-   If the current $a_i > a_{l_i - 1}$, then the current expansion position of the hoverline cannot continue expanding left.
-   If the current $a_i \le a_{l_i - 1}$, then the current hoverline can continue expanding left, and any position reachable by the hoverline at $l_i - 1$ must also be reachable by the hoverline at position $i$. Therefore, we update $l_i$ to $l_{l_i - 1}$ and continue the check.

By amortized analysis, each $l_i$ is visited by other $l_j$ at most once, so the time complexity is $O(n)$.

### Implementation

??? note "Reference Code"
    ```cpp
    --8<-- "docs/misc/code/hoverline/hoverline_1.cpp"
    ```

???+ note "[UVa1619 Feel Good](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=4494)"
    For a sequence of length $n$, find a subinterval that maximizes the product of the minimum value in the subinterval and the sum of elements in the subinterval. Among intervals with maximum comfort value, minimize the length; among those, minimize the left endpoint index.

In this problem, we can enumerate the minimum value: treat the number $a_i$ at each position as the minimum, and expand from $i$ left and right to find the interval $[l, r]$ that expands as far as possible while satisfying $\min\limits _ {j = l} ^ r a_j = a_i$. This transforms the problem into the hoverline model.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/misc/code/hoverline/hoverline_2.cpp"
    ```

## Maximum Submatrix

???+ note "[P4147 Jade Palace](https://www.luogu.com.cn/problem/P4147)"
    Given an $n \times m$ matrix containing `'F'` and `'R'`, find the area of the largest submatrix $\times 3$ such that every value in the submatrix is `'F'`.

We will find that this problem's model is very similar to the first problem. After careful analysis, if each time we only consider all elements in one row and use the distance that the element at position $(x, y)$ can expand upward as the hoverline length at that position, then the maximum submatrix must be one of the largest possible rectangles obtained by expanding these hoverlines left and right.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/misc/code/hoverline/hoverline_3.cpp"
    ```

## Exercises

-   [P1169「ZJOI2007」Chessboard Making](https://www.luogu.com.cn/problem/P1169)
