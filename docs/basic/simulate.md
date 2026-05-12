This page will briefly introduce simulation algorithms.

## Introduction

Simulation is using a computer to simulate the operations required by the problem.

Simulation problems typically have the characteristics of large code volume, many operations, and complex logic. Due to the large code volume, it is often difficult to find errors, which can be quite time-consuming in exams if written incorrectly.

## Tips

When writing simulation problems, following these suggestions may improve your problem-solving speed:

-   Before writing code, try to write out the process you need to implement on paper.
-   In your code, try to modularize each part, writing them as functions, structs, or classes.
-   For some concepts that may be used repeatedly, you can convert them uniformly for easier handling: for example, if a problem gives you "YY-MM-DD hour:minute", extracting it into a function and processing it into seconds will reduce concept confusion.
-   Debug in blocks. The benefit of modularization is that you can conveniently debug individual parts.
-   When writing code, be sure to have a clear thought process, don't write whatever comes to mind, write according to the steps laid out on paper.

In fact, the above steps are also very helpful when solving other types of problems.

## Example Problem

???+ note "[Climbing Worm](https://open.kattis.com/problems/climbingworm)"
    A worm of negligible length is at the bottom of a well that is $n$ inches deep. It climbs up $u$ inches each time, but must rest once before climbing again. During rest, it slides down $d$ inches. It then repeats the process of climbing and resting. How many climbs are needed at minimum for the worm to get out of the well? If the worm reaches exactly the top of the well after climbing, we also consider the worm as having exited the well.

??? note "Solution Idea"
    You can directly use a program to simulate the worm's climbing process. Use a loop to repeat the worm's climbing process, and exit when the climbing distance exceeds or equals the well's depth.

??? note "Reference Code"
    === "C++"
        ```cpp
        --8<-- "docs/basic/code/simulate/simulate_1.cpp"
        ```

    === "Python"
        ```python
        --8<-- "docs/basic/code/simulate/simulate_1.py"
        ```

    === "Java"
        ```java
        --8<-- "docs/basic/code/simulate/simulate_1.java"
        ```

## Practice Problems

-   [「NOIP2014」Rock Paper Scissors - Universal Online Judge](https://uoj.ac/problem/15)
-   [「OpenJudge 3750」World of Warcraft](http://bailian.openjudge.cn/practice/3750/)
-   [「SDOI2010」Pig Kill - LibreOJ](https://loj.ac/problem/2885)