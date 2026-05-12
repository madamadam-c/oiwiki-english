author: linehk, persdre

Time complexity and space complexity are important standards for measuring the efficiency of an algorithm.

## Basic Operation Count

The speed of the same algorithm running on different computers varies, and the actual running time is difficult to calculate theoretically. Measuring it practically is also cumbersome. Therefore, we usually consider not the actual time taken by an algorithm, but the number of basic operations that the algorithm needs to perform.

On a regular computer, operations such as addition, subtraction, multiplication, division, accessing variables (basic data type variables, same below), and assigning values to variables can all be considered basic operations.

Counting or estimating basic operations can serve as an indicator for judging an algorithm's execution time.

## Time Complexity

### Definition

When measuring how fast an algorithm is, the size of the data must be considered. The data scale generally refers to the number of input digits, the number of vertices and edges in an input graph, etc. Generally, the larger the data scale, the longer the algorithm takes. In competitive programming, when measuring an algorithm's efficiency, the most important factor is not its running time at a specific data scale, but the trend of how its running time grows with the data scale—namely, **time complexity**.

### Introduction

The main reasons for considering the trend of running time changing with data scale are as follows:

1.  Modern computers can perform hundreds of millions or more basic operations per second, so the data scale we handle is usually quite large. If algorithm A takes $100n$ time on data of scale $n$, while algorithm B takes $n^2$ time on data of scale $n$, algorithm B is faster when the data scale is less than $100$. However, within one second, algorithm A can process data of scale in the millions, while algorithm B can only process data of scale in the tens of thousands. When allowing longer execution times, the impact of time complexity on the data scale that can be processed becomes even more pronounced, far exceeding the impact of running time at the same data scale.
2.  We use the number of basic operations to represent an algorithm's running time, but different basic operations have different actual execution times. For example, addition and subtraction are much faster than division. Calculating time complexity while ignoring the differences between different basic operations, as well as the difference between one basic operation and ten basic operations, can eliminate the impact of varying execution times between basic operations.

Of course, an algorithm's running time is not entirely determined by the input scale—it also depends on the input content. Therefore, time complexity is divided into several types, such as:

1.  Worst-case time complexity, which is the time complexity corresponding to the input with the longest execution time for each input scale. In competitive programming, since inputs can be arbitrarily given within a specified data range, we usually consider the worst-case time complexity to ensure the algorithm can pass any data within a given range.
2.  Average (expected) time complexity, which is the complexity of the average execution time across all possible inputs for each input scale (the complexity of expected execution time for random inputs).

The so-called "trend of running time growing with data scale" is a vague concept. We need to use the **asymptotic notation** introduced below to formally represent time complexity.

## Asymptotic Notation

Asymptotic notation is a formal description of the order of a function. Simply put, asymptotic notation ignores the slowly growing parts of a function and the coefficients of each term (in time complexity analysis, coefficients are generally called "constants"), while retaining the important parts that can show the growth trend of the function.

A simple memory method: contains equals (non-strict) uses uppercase, does not contain equals (strict) uses lowercase. Equal is $\Theta$, less than is $O$, greater than is $\Omega$. Big $O$ and little $o$ were originally Greek letters Omicron. Due to the same character shape, they can also be understood as Latin uppercase $O$ and lowercase $o$.

In English, the roots "-micro-" and "-mega-" are often used to denote negative sixth power of 10 (one millionth) and sixth power (million), and also represent "small" and "large". Small and large are also common meanings of the Greek letters Omicron and Omega.

### Big Theta Notation

For functions $f(n)$ and $g(n)$, $f(n) = \Theta(g(n))$ if and only if $\exists c_1, c_2, n_0 > 0$ such that $\forall n \ge n_0, 0\le c_1\cdot g(n)\le f(n) \le c_2\cdot g(n)$.

That is, if $f(n) = \Theta(g(n))$, we can find two positive numbers $c_1, c_2$ such that $f(n)$ is sandwiched between $c_1\cdot g(n)$ and $c_2\cdot g(n)$.

For example, $3n^2+5n-3 = \Theta(n^2)$, where $c_1, c_2, n_0$ can be $2, 4, 100$ respectively. $n\sqrt {n} + n{\log^5 n} + m{\log m} +nm = \Theta(n\sqrt {n} + m{\log m} + nm)$, where $c_1, c_2, n_0$ can be $1, 2, 100$ respectively.

### Big O Notation

The $\Theta$ notation provides both upper and lower bounds of a function simultaneously. If only the asymptotic upper bound is known without knowing the asymptotic lower bound, the $O$ notation can be used. $f(n) = O(g(n))$ if and only if $\exists c, n_0$ such that $\forall n \ge n_0, 0\le f(n)\le c\cdot g(n)$.

When studying time complexity, the $O$ notation is usually used because we typically care about the upper bound of program execution time, not its lower bound.

It is important to note that "upper bound" and "lower bound" here refer to the function's trend of change, not the algorithm's. The upper bound of an algorithm's execution time corresponds to "worst-case time complexity," not the big $O$ notation. Therefore, using $\Theta$ notation to represent worst-case time complexity is perfectly acceptable—indeed, $\Theta$ is more precise than $O$. The main reason for using $O$ notation is: first, we can sometimes only prove the upper bound of time complexity without being able to prove its lower bound (this generally occurs in more complex algorithms and complexity analysis); second, $O$ is easier to type on a computer.

### Big Omega Notation

Similarly, we use $\Omega$ notation to describe the asymptotic lower bound of a function. $f(n) = \Omega(g(n))$ if and only if $\exists c, n_0$ such that $\forall n \ge n_0, 0\le c\cdot g(n)\le f(n)$.

### Little o Notation

If the $O$ notation is analogous to the less-than-or-equal sign, then the $o$ notation is analogous to the less-than sign.

The little $o$ notation is widely used in mathematical analysis. The Taylor expansion of a function at a point has a Peano remainder, using the little $o$ notation to represent strict inequality, thereby performing asymptotic analysis of equivalent infinitesimals.

$f(n) = o(g(n))$ if and only if for any given positive number $c$, $\exists n_0$ such that $\forall n \ge n_0, 0\le f(n)< c\cdot g(n)$.

### Little omega Notation

If the $\Omega$ notation is analogous to the greater-than-or-equal sign, then the $\omega$ notation is analogous to the greater-than sign.

$f(n) = \omega(g(n))$ if and only if for any given positive number $c$, $\exists n_0$ such that $\forall n \ge n_0, 0\le c\cdot g(n)< f(n)$.

![](images/order.png)

### Common Properties

-   $f(n) = \Theta(g(n))\iff f(n)=O(g(n))\land f(n)=\Omega(g(n))$
-   $f_1(n) + f_2(n) = O(\max(f_1(n), f_2(n)))$
-   $f_1(n) \times f_2(n) = O(f_1(n) \times f_2(n))$
-   $\forall a \neq 1, \log_a{n} = O(\log_2 n)$. From the change of base formula, it can be seen that any logarithmic function has the same growth rate regardless of its base, so the base of a logarithm is generally omitted in asymptotic time complexity.

## Simple Examples of Time Complexity Calculation

### `for` Loop

=== "C++"
    ```cpp
    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < m; ++k) {
          std::cout << "hello world\n";
        }
      }
    }
    ```

=== "Python"
    ```python
    n = int(input())
    m = int(input())
    for i in range(0, n):
        for j in range(0, n):
            for k in range(0, m):
                print("hello world")
    ```

=== "Java"
    ```java
    int n, m;
    n = input.nextInt();
    m = input.nextInt();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                System.out.println("hello world");
            }
        }
    }
    ```

If the values of $n$ and $m$ from the input are taken as the data scale, the time complexity of the code above is $\Theta(n^2m)$.

### DFS

When performing [DFS](../graph/dfs.md) on a graph with $n$ vertices and $m$ edges, since each vertex and each edge is visited only a constant number of times, the complexity is $\Theta(n+m)$.

## Which Quantities Are Constants?

When performing multiple operations, how do we determine whether these operations affect the time complexity? For example:

=== "C++"
    ```cpp
    constexpr int N = 100000;
    for (int i = 0; i < N; ++i) {
      std::cout << "hello world\n";
    }
    ```

=== "Python"
    ```python
    N = 100000
    for i in range(0, N):
        print("hello world")
    ```

=== "Java"
    ```java
    final int N = 100000;
    for (int i = 0; i < N; ++i) {
        System.out.println("hello world");
    }
    ```

If the size of $N$ is not considered as the input scale, then the time complexity of this code is $O(1)$.

When calculating time complexity, which variables are considered as the input scale is very important, and all quantities unrelated to the input scale are considered constants, which can be treated as $1$ when calculating complexity.

It is important to note that during theoretical discussions related to time complexity, "the algorithm can solve problems of any scale" is a basic assumption (of course, in practice, due to limited time and storage space, problems that are too large cannot be solved). Therefore, solving a problem with limited data scale in constant time (for example, precomputing answers for every possible input within the data range) does not make an algorithm's time complexity become $O(1)$.

## Master Theorem

We can use the Master Theorem to quickly obtain the complexity of recursive algorithms.
The Master Theorem recurrence relation is as follows:

$$
T(n) = a T\left(\frac{n}{b}\right)+f(n)\qquad \forall n > b
$$

Then

$$
T(n) = \begin{cases}\Theta(n^{\log_b a}) & f(n) = O(n^{\log_b (a)-\epsilon}),\epsilon > 0 \\ \Theta(f(n)) & f(n) = \Omega(n^{\log_b (a)+\epsilon}),\epsilon\ge 0\\ \Theta(n^{\log_b a}\log^{k+1} n) & f(n)=\Theta(n^{\log_b a}\log^k n),k\ge 0 \end{cases}
$$

It should be noted that the second case also needs to satisfy the regularity condition, i.e., $a f(n/b) \leq c f(n)$, for some constant $c < 1$ and sufficiently large $n$.

The proof idea is to decompose a problem of scale $n$ into $a$ subproblems of scale $(\frac{n}{b})$, then merge them up to the highest level. Merging each subproblem requires $f(n)$ time.

??? note "Proof"
    Based on the proof idea mentioned above, the detailed proof process is as follows:
    
    For level $0$ (the highest level), merging subproblems requires $f(n)$ time.
    
    For level $1$ (subproblems first divided out), there are $a$ subproblems. Each subproblem merge requires $f\left(\frac{n}{b}\right)$ time, so merging in total requires $a f\left(\frac{n}{b}\right)$ time.
    
    Recursively, we can write out the recursion tree as follows:![](./images/master-theorem-proof.svg)
    
    The height of this tree is ${\log_b n}$, with a total of $n^{\log_b a}$ leaves. Thus $T(n) = \Theta(n^{\log_b a}) + g(n)$, where $g(n) = \sum_{j = 0}^{\log_{b}{n - 1}} a^{j} f(n / b^{j})$.
    
    For case 1: $f(n) = O(n^{\log_b a-\epsilon})$, therefore $g(n) = O(n^{\log_b a})$.
    
    For case 2: first, $g(n) = \Omega(f(n))$, and because $a f(\dfrac{n}{b}) \leq c f(n)$, as long as $c$ is a sufficiently small positive number and $n$ is sufficiently large, it follows that: $g(n) = O(f(n)$). The squeeze from both sides gives $g(n) = \Theta(f(n))$.
    
    For case 3: $f(n) = \Theta(n^{\log_b a})$, therefore $g(n) = O(n^{\log_b a} {\log n})$. The result of $T(n)$ follows easily after obtaining $g(n)$.

The following examples illustrate how to use the Master Theorem.

1.  $T(n) = 2T\left(\frac{n}{2}\right) + 1$, then $a=2, b=2, {\log_2 2} = 1$, so $\epsilon$ can take any value in $(0, 1]$, satisfying case 1, therefore $T(n) = \Theta(n)$.

2.  $T(n) = T\left(\frac{n}{2}\right) + n$, then $a=1, b=2, {\log_2 1} = 0$, so $\epsilon$ can take any value in $(0, 1]$, satisfying case 2, therefore $T(n) = \Theta(n)$.

3.  $T(n) = T\left(\frac{n}{2}\right) + {\log n}$, then $a=1, b=2, {\log_2 1}=0$, so $k$ can take the value $1$, satisfying case 3, therefore $T(n) = \Theta(\log^2 n)$.

4.  $T(n) = T\left(\frac{n}{2}\right) + 1$, then $a=1, b=2, {\log_2 1} = 0$, so $k$ can take the value $0$, satisfying case 3, therefore $T(n) = \Theta(\log n)$.

## Amortized Complexity

For details, see [Amortized Complexity](./amortized-analysis.md).

## Space Complexity

Similarly, the trend of how much space an algorithm uses changes with the input scale can be measured by **space complexity**.

## Computational Complexity

This article mainly introduces complexity from the perspective of algorithm analysis. If you are interested, you can learn more in [Computational Complexity](../misc/cc-basic.md).
