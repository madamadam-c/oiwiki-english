## Introduction

Permutations and combinations are the foundation of combinatorics. Permutations refer to selecting a certain number of elements from a given number of elements and arranging them; combinations refer to selecting a certain number of elements from a given number of elements without considering the order. The central problem of permutations and combinations is to study the total number of possible permutations and combinations that satisfy given requirements. Permutations and combinations are closely related to classical probability theory.

In high school elementary mathematics, permutations and combinations are mostly solved using methods such as listing and enumeration.

## Addition & Multiplication Principles

### Addition Principle

Completing a task can be done in $n$ categories of methods, where $a_i (1 \le i \le n)$ represents the number of methods in the $i$-th category. Then there are $S = a_1 + a_2 + \cdots + a_n$ different methods to complete the task.

### Multiplication Principle

Completing a task requires $n$ steps, where $a_i (1 \le i \le n)$ represents the number of different methods for the $i$-th step. Then there are $S = a_1 \times a_2 \times \cdots \times a_n$ different methods to complete the task.

## Basics of Permutations and Combinations

### Permutation Number

From $n$ different elements, select $m$ elements ($m \le n$, $m$ and $n$ are natural numbers) and arrange them in a certain order. This is called a permutation of $m$ elements from $n$ different elements. The number of all such permutations of $m$ elements from $n$ different elements is called the permutation number, denoted as $\mathrm{A}_n^m$ (or $\mathrm{P}_n^m$).

The formula for permutations is:

$$
\mathrm{A}_n^m = n(n-1)(n-2) \cdots (n - m + 1) = \frac{n!}{(n - m)!}
$$

$n!$ represents the factorial of $n$, i.e., $6! = 1 \times 2 \times 3 \times 4 \times 5 \times 6$.

The formula can be understood as: $n$ people, select $m$ to form a line ($m \le n$). The first position can have $n$ choices, the second position can have $n-1$ choices, and so on. The $m$-th (last) position can have $n-m+1$ choices. We get:

$$
\mathrm{A}_n^m = n(n-1)(n-2) \cdots (n - m + 1) = \frac{n!}{(n - m)!}
$$

Full permutation: $n$ people all form a line of length $n$. The first position can have $n$ choices, the second position can have $n-1$ choices, and so on. We get:

$$
\mathrm{A}_n^n = n(n-1)(n-2) \cdots 3 \times 2 \times 1 = n!
$$

Full permutation is a special case of permutation numbers.

### Combination Number

From $n$ different elements, select $m \le n$ elements to form a set. This is called a combination of $m$ elements from $n$ different elements. The number of all such combinations of $m$ elements from $n$ different elements is called the combination number, denoted as $\dbinom{n}{m}$, read as "$n$ choose $m$".

The combination number formula:

$$
\dbinom{n}{m} = \frac{\mathrm{A}_n^m}{m!} = \frac{n!}{m!(n - m)!}
$$

How to understand this formula? Consider selecting $m$ out of $n$ people ($m \le n$), without lining up, order doesn't matter. If order matters, it's $\mathrm{A}_n^m$; if order doesn't matter, we need to divide out the duplicates. How many duplicates are there? The $m$ selected people also need to be "fully arranged", which takes $m!$. So we get:

$$
\begin{aligned}
\dbinom{n}{m} \times m! &= \mathrm{A}_n^m\\
\dbinom{n}{m} &= \frac{\mathrm{A}_n^m}{m!} = \frac{n!}{m!(n-m)!}
\end{aligned}
$$

Combination numbers are also often denoted as $\mathrm{C}_n^m$, i.e., $\displaystyle \mathrm{C}_n^m = \binom{n}{m}$. The notation $\dbinom{n}{m}$ is now more commonly used in mathematics rather than $\mathrm{C}_n^m$.

Combination numbers are also called "binomial coefficients", and the connection will be explained in the binomial theorem below.

In particular, when $m > n$, we define $\mathrm{A}_n^m = \dbinom{n}{m} = 0$.

## Stars and Bars

Stars and bars (Stars and bars) is a technique used to find the number of ways to divide identical elements into groups, and can also be used to find the number of solutions to a class of linear Diophantine equations.

### Number of Compositions into Positive Integers

Problem 1: We have $n$ **completely identical** elements. We need to divide them into $k$ groups, ensuring each group has at least one element. How many ways are there?

Consider using $k - 1$ boards to insert into the $n - 1$ gaps formed by the $n$ elements.

Since the elements are identical, the answer is $\dbinom{n - 1}{k - 1}$.

The essence is finding the number of positive integer solutions to $x_1 + x_2 + \cdots + x_k = n$.

### Number of Compositions into Non-negative Integers

Problem 2: What if each group is allowed to be empty?

Obviously, we can't directly use stars and bars at this point, because it's possible that many boards are inserted into the same gap, which is very difficult to calculate.

We consider creating conditions to transform it into the restricted Problem 1. First borrow $k$ elements. With $n + k$ elements, insert boards into the $n + k - 1$ gaps. The answer is:

$$
\binom{n + k - 1}{k - 1} = \binom{n + k - 1}{n}
$$

Although this is not directly the original problem, this formula is the answer to the original problem. This can be understood as:

Initially, we borrowed $k$ elements to ensure each group has at least one element. After inserting the boards, we remove these $k$ borrowed elements from the $k$ groups. Since the elements are identical, the transformed case and the case before transformation can be one-to-one correspond, so the answers are equal.

From this, we can derive the formula for stars and bars: $\dbinom{n + k - 1}{n}$.

The essence is finding the number of non-negative integer solutions to $x_1 + x_2 + \cdots + x_k = n$ (i.e., requiring $x_i \ge 0$).

### Number of Compositions with Different Lower Bounds

Problem 3: If we go one step further, requiring that group $i$ receives at least $a_i$ elements, where $\sum a_i \le n$?

The essence is finding the number of solutions to $x_1 + x_2 + \cdots + x_k = n$ where $x_i \ge a_i$.

By analogy with the unrestricted case, we borrow $\sum a_i$ elements to ensure group $i$ can receive at least $a_i$ elements. That is, let:

$$
x_i' = x_i - a_i
$$

We get the new equation:

$$
\begin{aligned}
(x_1' + a_1) + (x_2' + a_2) + \cdots + (x_k' + a_k) &= n\\
x_1' + x_2' + \cdots + x_k' &= n - a_1 - a_2 - \cdots - a_k\\
x_1' + x_2' + \cdots + x_k' &= n - \sum a_i
\end{aligned}
$$

where

$$
x_i' \ge 0
$$

Then Problem 3 transforms into Problem 2. Using the stars and bars formula, the answer is:

$$
\binom{n - \sum a_i + k - 1}{n - \sum a_i}
$$

### Non-adjacent Permutations

Among the $n$ natural numbers $1 \sim n$, select $k$ numbers such that no two selected numbers are adjacent. There are $\dbinom{n - k + 1}{k}$ ways.

## Binomial Theorem

Before entering the advanced topics of permutations and combinations, we introduce a theorem closely related to combination numbers—the binomial theorem.

The binomial theorem states the coefficients of an expansion:

$$
(a + b)^n = \sum_{i=0}^n \binom{n}{i} a^{n-i} b^i
$$

The proof can be done using mathematical induction, using $\dbinom{n}{k} + \dbinom{n}{k-1} = \dbinom{n+1}{k}$ for induction.

The binomial theorem can be easily extended to the multinomial form:

Let $n$ be a positive integer, $x_i$ be real numbers:

$$
(x_1 + x_2 + \cdots + x_t)^n = \sum_{\text{non-negative integer solutions } n_1 + \cdots + n_t = n} \binom{n}{n_1, n_2, \cdots, n_t} x_1^{n_1} x_2^{n_2} \cdots x_t^{n_t}
$$

Here, $\dbinom{n}{n_1, n_2, \cdots, n_t}$ is the multinomial coefficient, which has similar properties:

$$
\sum \binom{n}{n_1, n_2, \cdots, n_t} = t^n
$$

## Advanced Permutations and Combinations

Now we introduce some variants of permutations and combinations.

### Permutation Number of Multisets | Multiset Coefficient

Be sure to distinguish **multiset coefficient** from **permutation number of multisets**! They are completely different concepts!

A multiset is a generalized set containing repeated elements. Let $S = \{n_1 \cdot a_1, n_2 \cdot a_2, \cdots, n_k \cdot a_k\}$ represent a multiset consisting of $n_1$ copies of $a_1$, $n_2$ copies of $a_2$, ..., $n_k$ copies of $a_k$. The number of all permutations of $S$ is:

$$
\frac{n!}{\prod_{i=1}^k n_i!} = \frac{n!}{n_1! n_2! \cdots n_k!}
$$

This is equivalent to dividing out the permutations of identical elements. Specifically, you can think of having $k$ different types of balls, with each type having $n_1, n_2, \cdots, n_k$ balls respectively, and $n = n_1 + n_2 + \ldots + n_k$. The number of all permutations of these $n$ balls is the **permutation number of multisets**. It is often called the **multiset coefficient**. We can use the multiset coefficient notation to represent the formula above:

$$
\binom{n}{n_1, n_2, \cdots, n_k} = \frac{n!}{\prod_{i=1}^k n_i!}
$$

It can be seen that $\dbinom{n}{m}$ is equivalent to $\dbinom{n}{m, n-m}$, though the latter is more cumbersome and thus not used.

### Combination Number of Multisets 1

Let $S = \{n_1 \cdot a_1, n_2 \cdot a_2, \cdots, n_k \cdot a_k\}$ represent a multiset consisting of $n_1$ copies of $a_1$, $n_2$ copies of $a_2$, ..., $n_k$ copies of $a_k$. Then for an integer $r$ ($r < n_i, \forall i \in [1, k]$), the number of ways to select $r$ elements from $S$ to form a multiset is the **combination number of multisets**. This problem is equivalent to the number of non-negative integer solutions to $x_1 + x_2 + \cdots + x_k = r$, which can be solved using stars and bars. The answer is:

$$
\binom{r + k - 1}{k - 1}
$$

### Combination Number of Multisets 2

Consider this problem: Let $S = \{n_1 \cdot a_1, n_2 \cdot a_2, \cdots, n_k \cdot a_k,\}$ represent a multiset consisting of $n_1$ copies of $a_1$, $n_2$ copies of $a_2$, ..., $n_k$ copies of $a_k$. Then for a positive integer $r$, the number of ways to select $r$ elements from $S$ to form a multiset.

This limits the number of each type of element that can be selected. Similarly, we can transform this problem into a restricted linear equation solution:

$$
\forall i \in [1, k],\ x_i \le n_i,\ \sum_{i=1}^k x_i = r
$$

So we naturally think of the inclusion-exclusion principle. The inclusion-exclusion model is:

1.  Universal set: non-negative integer solutions to $\displaystyle \sum_{i=1}^k x_i = r$.
2.  Property: $x_i \le n_i$.

Thus, let $S_i$ be the set satisfying property $i$, and $\overline{S_i}$ be the set not satisfying property $i$, i.e., satisfying $x_i \ge n_i + 1$ (transforming to Problem 3 above with stars and bars). The answer is:

$$
\left|\bigcap_{i=1}^k S_i\right| = |U| - \left|\bigcup_{i=1}^k \overline{S_i}\right|
$$

According to the inclusion-exclusion principle:

$$
\begin{aligned}
\left|\bigcup_{i=1}^k \overline{S_i}\right|
=&\sum_i \left|\overline{S_i}\right|
-\sum_{i,j} \left|\overline{S_i} \cap \overline{S_j}\right|
+\sum_{i,j,k} \left|\overline{S_i} \cap \overline{S_j} \cap \overline{S_k}\right|
-\cdots\\
&+(-1)^{k-1} \left|\bigcap_{i=1}^k \overline{S_i}\right|\\
=&\sum_i \binom{k+r-n_i-2}{k-1}
-\sum_{i,j} \binom{k+r-n_i-n_j-3}{k-1} + \sum_{i,j,k} \binom{k+r-n_i-n_j-n_k-4}{k-1}
-\cdots\\
&+(-1)^{k-1} \binom{k+r-\sum_{i=1}^k n_i - k - 1}{k-1}
\end{aligned}
$$

Subtracting the universal set $\displaystyle |U| = \binom{k+r-1}{k-1}$ from above gives the combination number of multisets:

$$
\text{Ans} = \sum_{p=0}^k (-1)^p \sum_A \binom{k+r-1-\sum_A n_{A_i} - p}{k - 1}
$$

Here, $A$ plays the role of enumerating subsets, satisfying $|A| = p,\ A_i < A_{i+1}$.

### Circular Permutations

$n$ people all forming a circle. The number of all arrangements is denoted as $\mathrm{Q}_n^n$. Consider a circle that is already arranged; breaking it at different positions makes it different queues.

So we have:

$$
\mathrm{Q}_n^n \times n = \mathrm{A}_n^n \Longrightarrow \mathrm{Q}_n = \frac{\mathrm{A}_n^n}{n} = (n - 1)!
$$

From this, we get the formula for partial circular permutations:

$$
\mathrm{Q}_n^r = \frac{\mathrm{A}_n^r}{r} = \frac{n!}{r \times (n - r)!}
$$

## Combination Number Properties | Binomial Corollaries

Since combination numbers are very important in OI, here we introduce some properties of combination numbers.

$$
\binom{n}{m} = \binom{n}{n-m} \tag{1}
$$

This corresponds to taking the complement of the selected set from the universal set, so the value remains unchanged. (Symmetry)

$$
\binom{n}{k} = \frac{n}{k} \binom{n-1}{k-1} \tag{2}
$$

A recurrence formula derived from the definition.

$$
\binom{n}{m} = \binom{n-1}{m} + \binom{n-1}{m-1} \tag{3}
$$

The recurrence formula for combination numbers (the formula expression of Pascal's triangle). We can use this formula to derive combination numbers in $O(n^2)$ time complexity.

$$
\binom{n}{0} + \binom{n}{1} + \cdots + \binom{n}{n} = \sum_{i=0}^n \binom{n}{i} = 2^n \tag{4}
$$

This is a special case of the binomial theorem. Taking $a = b = 1$ gives the above formula.

$$
\sum_{i=0}^n (-1)^i \binom{n}{i} = [n = 0] \tag{5}
$$

Another special case of the binomial theorem, taking $a = 1, b = -1$. A special case of this formula is that when $n = 0$, the answer is $1$.

$$
\sum_{i=0}^k \binom{n}{i} \binom{m}{k-i} = \binom{m+n}{k} \tag{6}
$$

A formula for splitting combination numbers, which is useful when dealing with some data structure problems. It is called the Vandermonde identity.

$$
\sum_{i=0}^n \binom{n}{i}^2 = \binom{2n}{n} \tag{7}
$$

This is a special case of $(6)$, taking $n = k = m$.

$$
\sum_{i=0}^n i \binom{n}{i} = n 2^{n-1} \tag{8}
$$

A weighted sum formula, which can be proven by taking the derivative of the polynomial function corresponding to $(4)$.

$$
\sum_{i=0}^n i^2 \binom{n}{i} = n(n + 1)2^{n-2} \tag{9}
$$

Similar to the above, can be proven by taking the derivative of the polynomial function.

$$
\sum_{l=0}^n \binom{l}{k} = \binom{n+1}{k+1} \tag{10}
$$

Can be proven by combinatorial analysis, considering the number of $(k+1)$-subsets of $S = \{a_1, a_2, \cdots, a_{n+1}\}$. It is often used in identity proofs. It is called the hockey-stick identity.

$$
\binom{n}{r} \binom{r}{k} = \binom{n}{k} \binom{n-k}{r-k} \tag{11}
$$

Can be proven from the definition.

$$
\sum_{i=0}^n \binom{n-i}{i} = F_{n+1} \tag{12}
$$

Where $F$ is the Fibonacci sequence.

$$
\binom{n+k}{k}^2 = \sum_{j=0}^k \binom{k}{j}^2 \binom{n+2k-j}{2k} \tag{13}
$$

Can be proven using $(6)$. It is called the Li Shanlan identity.

## Binomial Inversion

Let $f_n$ represent the number of ways to form a specific structure using exactly $n$ different elements, and $g_n$ represent the total number of ways to form a specific structure by selecting $i \ge 0$ elements from $n$ different elements.

If we know $f_n$ to find $g_n$, then obviously:

$$
g_n = \sum_{i = 0}^{n} \binom{n}{i} f_i
$$

If we know $g_n$ to find $f_n$, then:

$$
f_n = \sum_{i = 0}^{n} \binom{n}{i} (-1)^{n-i} g_i
$$

The above process of finding $f_n$ from known $g_n$ is called **binomial inversion**.

### Proof

Expand $g_i$ in the inversion formula:

$$
\begin{aligned}
f_n &= \sum_{i = 0}^{n} \binom{n}{i} (-1)^{n-i} \left[\sum_{j = 0}^{i} \binom{i}{j} f_j\right] \\
&= \sum_{i = 0}^{n}\sum_{j = 0}^{i}\binom{n}{i}\binom{i}{j} (-1)^{n-i}f_j
\end{aligned}
$$

First enumerate $j$, then enumerate $i$:

$$
\begin{aligned}
f_n &= \sum_{j = 0}^{n}\sum_{i = j}^{n}\binom{n}{i}\binom{i}{j} (-1)^{n-i}f_j \\
&= \sum_{j = 0}^{n}f_j\sum_{i = j}^{n}\binom{n}{i}\binom{i}{j} (-1)^{n-i}
\end{aligned}
$$

Using formula (11) from "Combination Number Properties | Binomial Corollaries":

$$
\begin{aligned}
f_n &= \sum_{j = 0}^{n}f_j\sum_{i = j}^{n}\binom{n}{j}\binom{n - j}{i - j} (-1)^{n-i} \\
&= \sum_{j = 0}^{n}\binom{n}{j}f_j\sum_{i = j}^{n}\binom{n - j}{i - j} (-1)^{n-i}
\end{aligned}
$$

Let $k = i - j$. Then $i = k + j$, the formula becomes:

$$
f_n = \sum_{j = 0}^{n}\binom{n}{j}f_j\sum_{k = 0}^{n - j}\binom{n - j}{k} (-1)^{n-j-k}1^{k}
$$

Using formula (5) from "Combination Number Properties | Binomial Corollaries":

$$
f_n = \sum_{j = 0}^{n}\binom{n}{j}f_j[n = j] = f_n
$$

Q.E.D.
