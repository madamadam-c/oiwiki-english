author: codewasp942

??? tip "Tip"
    This article has relatively little connection with other articles in the "Linear Algebra" category. However, the author believes it is necessary to discuss the essence of linear algebra, trace the origins and connections of concepts, and give readers a preliminary but systematic understanding of linear algebra.

As early as thousands of years ago, ancient people used systems of linear equations to solve problems, and today, linear algebra is still widely applied.

Linear algebra originates from people's observations. People discovered that many objects share similar properties, such as:

-   Force can be decomposed and combined.

-   For any $k,x_0$, $k \sin (x-x_0)$ can be decomposed into $k_1\sin x + k_2\cos x$.

These properties relate to **scaling**, **decomposition**, and **superposition** of the described objects. Linear algebra abstracts these properties from concrete objects and studies them as an independent discipline. In OI, linear algebra knowledge can be directly used to solve problems, or to optimize algorithms and data structures. For example:

-   Use tree decomposition to maintain a linear basis for finding the maximum XOR sum on a chain.

-   Use the Matrix-Tree Theorem to transform the problem of counting spanning trees in a graph into computing the determinant of a matrix.

-   Use matrix exponentiation to optimize recurrence relations.