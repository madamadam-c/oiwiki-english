author: sshwy

The ordinary generating function (OGF) of a sequence $a$ is defined as a formal power series:

$$
F(x)=\sum_{n}a_n x^n
$$

$a$ can be either a finite sequence or an infinite sequence. Common examples (assuming $a$ starts at 0):

1.  The ordinary generating function of sequence $a=\langle 1,2,3\rangle$ is $1+2x+3x^2$.
2.  The ordinary generating function of sequence $a=\langle 1,1,1,\cdots\rangle$ is $\sum_{n\ge 0}x^n$.
3.  The generating function of sequence $a=\langle 1,2,4,8,16,\cdots\rangle$ is $\sum_{n\ge 0}2^nx^n$.
4.  The generating function of sequence $a=\langle 1,3,5,7,9,\cdots\rangle$ is $\sum_{n\ge 0}(2n+1)x^n$.

In other words, if sequence $a$ has a general term formula, the coefficients of its ordinary generating function are that formula.

## Basic Operations

Consider two sequences $a,b$ with ordinary generating functions $F(x),G(x)$ respectively. Then:

$$
F(x)\pm G(x)=\sum_n (a_n\pm b_n)x^n
$$

Therefore, $F(x)\pm G(x)$ is the ordinary generating function of sequence $\langle a_n\pm b_n\rangle$.

Consider multiplication, which is convolution:

$$
F(x)G(x)=\sum_n x^n \sum_{i=0}^na_ib_{n-i}
$$

Therefore, $F(x)G(x)$ is the ordinary generating function of sequence $\langle \sum_{i=0}^n a_ib_{n-i} \rangle$.

## Closed Form

In the process of using generating functions, we will not always use the form of formal power series; we will transform to closed form when appropriate to simplify.

For example, for the ordinary generating function $F(x)=\sum_{n\ge 0}x^n$ of $\langle 1,1,1,\cdots\rangle$, we can find:

$$
F(x)x+1=F(x)
$$

Then solving this equation:

$$
F(x)=\frac{1}{1-x}
$$

This is the closed form of $\sum_{n\ge 0}x^n$.

Consider the generating function $F(x)=\sum_{n\ge 0}p^nx^n$ of the geometric progression $\langle 1,p,p^2,p^3,p^4,\cdots\rangle$:

$$
\begin{aligned}F(x)px+1 &=F(x)\\F(x) &=\frac{1}{1-px}\end{aligned}
$$

The closed form of a geometric progression and its expansion form are commonly used transformation techniques.

???+ note "Small Exercises"
    Find the ordinary generating functions (both in formal power series form and closed form) of the following sequences. The difficulty is progressive.
    
    1.  $a=\langle 0,1,1,1,1,\cdots\rangle$.
    2.  $a=\langle 1,0,1,0,1,\cdots \rangle$.
    3.  $a=\langle 1,2,3,4,\cdots \rangle$.
    4.  $a_n=\binom{m}{n}$ ($m$ is a constant, $n\ge 0$).
    5.  $a_n=\binom{m+n}{n}$ ($m$ is a constant, $n\ge 0$).

??? note "Answers"
    First:
    
    $$
    F(x)=\sum_{n\ge 1}x^n=\dfrac{x}{1-x}
    $$
    
    Second:
    
    $$
    \begin{aligned}
    F(x)&=\sum_{n\ge 0}x^{2n}\\
    &=\sum_{n\ge 0}(x^2)^{n}\\
    &=\frac{1}{1-x^2}
    \end{aligned}
    $$
    
    Third (via differentiation):
    
    $$
    \begin{aligned}F(x)&=\sum_{n\ge 0}(n+1)x^n\\&=\sum_{n\ge 1}nx^{n-1}\\&=\sum_{n\ge 0}(x^n)'\\&=\left(\frac{1}{1-x}\right)'\\&=\frac{1}{(1-x)^2}\end{aligned}
    $$
    
    Fourth (binomial theorem):
    
    $$
    F(x)=\sum_{n\ge 0}\binom{m}{n}x^n=(1+x)^m
    $$
    
    Fifth:
    
    $$
    F(x)=\sum_{n\ge 0}\binom{m+n}{n}x^n=\frac{1}{(1-x)^{m+1}}
    $$
    
    Can be proved by induction.
    
    First, when $m=0$, we have $F(x)=\dfrac{1}{1-x}$.
    
    And when $m>0$:
    
    $$
    \begin{aligned}
    \frac{1}{(1-x)^{m+1}}
    &=\frac{1}{(1-x)^m}\frac{1}{1-x}\\
    &=\left(\sum_{n\ge 0}\binom{m+n-1}{n}x^n \right)\left(\sum_{n\ge 0}x^n \right)\\
    &=\sum_{n\ge 0} x^n\sum_{i=0}^n \binom{m+i-1}{i}\\
    &=\sum_{n\ge 0}\binom{m+n}{n}x^n
    \end{aligned}
    $$

## Generating Function of Fibonacci Sequence

Now we derive the generating function of the Fibonacci sequence.

The Fibonacci sequence is defined as $a_0=0,a_1=1,a_n=a_{n-1}+a_{n-2}\;(n>1)$. Let its ordinary generating function be $F(x)$. According to its recurrence relation, we can similarly list an equation for $F(x)$:

$$
F(x)=xF(x)+x^2F(x)-a_0x+a_1x+a_0
$$

Solving:

$$
F(x)=\frac{x}{1-x-x^2}
$$

The next question is, how to find its expanded form?

### Expansion Method 1

Consider $x+x^2$ as a whole:

$$
\begin{aligned}
F(x) &= \dfrac{x}{1-(x+x^2)} \\
&= x\sum_{k=0}^{\infty}(x+x^2)^k \\
&= x\sum_{k=0}^{\infty}\sum_{i=0}^k\binom{k}{i}x^{k-i}(x^2)^i \\
&= \sum_{k=0}^{\infty}\sum_{i=0}^k\binom{k}{i}x^{k+i+1} \\
&= \sum_{n=1}^{\infty}\sum_{i=0}^{\lfloor(n-1)/2\rfloor}\binom{n-i-1}{i}x^n.
\end{aligned}
$$

In the last step, let $n=k+i+1$ and change the order of summation. From this, we can get the general term formula:

$$
a_n = \sum_{i=0}^{\lfloor(n-1)/2\rfloor}\binom{n-i-1}{i}.
$$

This is not the form we know involving the golden ratio.

### Expansion Method 2

Consider solving an equation with undetermined coefficients:

$$
\frac{A}{1-ax}+\frac{B}{1-bx}= \frac{x}{1-x-x^2}
$$

After combining denominators:

$$
\frac{A-Abx+B-aBx}{(1-ax)(1-bx)} = \frac{x}{1-x-x^2}
$$

Equating coefficients of corresponding terms:

$$
\begin{cases}
A+B=0\\
-Ab-aB=1\\
a+b=1\\
ab=-1
\end{cases}
$$

Solving:

$$
\begin{cases}
A=\frac{1}{\sqrt{5}}\\
B=-\frac{1}{\sqrt{5}}\\
a=\frac{1+\sqrt{5}}{2}\\
b=\frac{1-\sqrt{5}}{2}
\end{cases}
$$

Then, based on the expansion form of geometric progressions, we can get the general term formula of the Fibonacci sequence:

$$
\frac{x}{1-x-x^2}=\sum_{n\ge 0}x^n
\frac{1}{\sqrt{5}}\left( \left(\frac{1+\sqrt{5}}{2}\right)^n-\left(\frac{1-\sqrt{5}}{2}\right)^n \right)
$$

This is also called another closed form of the Fibonacci sequence ($\frac{x}{1-x-x^2}$ is a closed form).

For any polynomials $P(x),Q(x)$, the expanded form of the generating function $\dfrac{P(x)}{Q(x)}$ can be found using the above method. In practical application, we often first find the roots of $Q(x)$, express the denominator as $\prod (1-p_ix)^{d_i}$, and then find the numerator.

When there are repeated roots after factoring the denominator, we need one more partial fraction for each repeated root. Consider finding the general term formula for coefficients of the generating function

$$
G(x)=\frac{1}{(1-x)(1-2x)^2}
$$

We have:

$$
G(x)=\frac{c_0}{1-x}+\frac{c_1}{1-2x}+\frac{c_2}{(1-2x)^2}
$$

Solving:

$$
\begin{cases}
c_0&=1\\
c_1&=-2\\
c_2&=2
\end{cases}
$$

Then:

$$
[x^n]G(x)=1-2^{n+1}+(n+1)\cdot 2^{n+1}
$$

## Newton's Binomial Theorem

We redefine binomial coefficient operations:

$$
\binom{r}{k}=\frac{r^{\underline{k}}}{k!}\quad(r\in\mathbf{C},k\in\mathbf{N})
$$

Note that $r$ is in the complex field. In this case, for $\alpha\in\mathbf{C}$:

$$
(1+x)^{\alpha}=\sum_{n\ge 0}\binom{\alpha}{n}x^n
$$

The binomial theorem is actually a special case of Newton's binomial theorem.

## Generating Function of Catalan Numbers

Refer to [Algebraic Derivation of Catalan Numbers](../combinatorics/catalan.md#algebraic-derivation).

## Applications

Now we provide some example problems to introduce the specific applications of generating functions in OI.

### Food

???+ note "[Food](https://hydro.ac/p/bzoj-P3028)"
    Choose $n$ items from many different types of food, with each type having the following restrictions:
    
    1.  Chengde Burger: even number
    2.  Cola: 0 or 1
    3.  Chicken Leg: 0, 1, or 2
    4.  Peach Juice: odd number
    5.  Chicken Nuggets: multiple of 4
    6.  Steamed Bun: 0, 1, 2, or 3
    7.  Fried Potato Slices: at most one
    8.  Bread: multiple of 3
    
    Each food is counted in "pieces", and as long as the total is $n$, it counts as one scheme. For the given $n$, calculate the number of schemes modulo $10007$.

    This is a classic generating function problem. For one type of food, we can let $a_n$ represent the number of schemes for choosing $n$ of that food, and find its generating function. The generating function for choosing $n$ items from two types of food is the convolution of their generating functions. The generating function for choosing $n$ items from multiple types of food is also the convolution of their generating functions.

    After understanding that the number of schemes can be represented by convolution, we can construct generating functions (the labels correspond to the food labels in the problem):

    1.  $\displaystyle\sum_{n\ge 0}x^{2n}=\dfrac{1}{1-x^2}$.
    2.  $1+x$.
    3.  $1+x+x^2=\dfrac{1-x^3}{1-x}$.
    4.  $\dfrac{x}{1-x^2}$.
    5.  $\displaystyle \sum_{n\ge 0}x^{4n}=\dfrac{1}{1-x^4}$.
    6.  $1+x+x^2+x^3=\dfrac{1-x^4}{1-x}$.
    7.  $1+x$.
    8.  $\dfrac{1}{1-x^3}$.

    Multiply them all together to get the generating function for the answer:

    $$
    F(x)=\frac{(1+x)(1-x^3)x(1-x^4)(1+x)}{(1-x^2)(1-x)(1-x^2)(1-x^4)(1-x)(1-x^3)}
    =\frac{x}{(1-x)^4}
    $$

    Then convert it to expanded form (using the fifth exercise in the closed form practice):

    $$
    F(x)=\sum_{n\ge 1}\binom{n+2}{n-1}x^n
    $$

    Therefore, the answer is $\dbinom{n+2}{n-1}=\dbinom{n+2}{3}$.

### Sweet

???+ note "[「CEOI2004」Sweet](https://hydro.ac/p/bzoj-P3027)"
    There are $n$ piles of candies. Different piles have different types of candies (i.e., candies in the same pile are of the same type, and candies in different piles are of different types). The $i$-th pile has $m_i$ candies. Now we need to eat at least $a$ candies but at most $b$. How many schemes are there?
    
    Two schemes are different if and only if the number of candies eaten is different, or for some type of candy, the number of candies eaten is different between the two schemes.
    
    $n\le 10,0\le a\le b\le 10^7,m_i\le 10^6$.

    For the $i$-th pile, the generating function for eating $j$ candies (obviously 1) is:

    $$
    F_i(x)=\sum_{j=0}^{m_i}x^j=\frac{1-x^{m_i+1}}{1-x}
    $$

    Therefore, the generating function for the total number of candies eaten $i$ is:

    $$
    G(x)=\prod_{i=1}^n F_i(x)=(1-x)^{-n}\prod_{i=1}^n(1-x^{m_i+1})
    $$

    Now we need to compute $\sum_{i=a}^b[x^i]G(x)$.

    Since $n\le 10$, we can brute-force expand $\prod_{i=1}^n(1-x^{m_i+1})$ (at most $2^n$ terms).

    Then apply Newton's binomial theorem to $(1-x)^{-n}$:

    $$
    \begin{aligned}
    (1-x)^{-n}
    &=\sum_{i\ge 0}\binom{-n}{i}(-x)^i\\
    &=\sum_{i\ge 0}\binom{n-1+i}{i}x^i
    \end{aligned}
    $$

    We enumerate the coefficient of $x^k$ in $\prod_{i=1}^n(1-x^{m_i+1})$, say $c_k$. Then its contribution to the answer when multiplied by $(1-x)^{-n}$ is:

    $$
    c_k\sum_{i=a-k}^{b-k}\binom{n-1+i}{i}=c_k\left(
    \binom{n+b-k}{b-k}-
    \binom{n+a-k-1}{a-k-1}
    \right)
    $$

    This allows us to compute the answer in $O(b)$ time.

    Time complexity $O(2^n+b)$.