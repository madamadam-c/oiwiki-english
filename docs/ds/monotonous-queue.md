author: Link-cute, Xeonacid, ouuan, Alphnia, Lyccrius

## Introduction

Before learning monotonic queues, let us first look at an example problem.

???+ note "Example"
    [Sliding Window](http://poj.org/problem?id=2823)
    
    The problem gives an array of length $n$ and asks you to output the maximum and minimum value among every $k$ consecutive numbers.

The brute-force idea is simple: for every segment $i \sim i+k-1$, compare elements one by one to find the maximum value (and the minimum value). The time complexity is about $O(n \times k)$.

Obviously, this does a lot of repeated work. Except for the first $k-1$ and last $k-1$ numbers, every number is compared $k$ times. Since $100\%$ of the data has $n \le 1000000$, this clearly TLEs when $k$ is moderately large.

This is where monotonic queues are used.

## Definition

As the name suggests, a monotonic queue has two key parts: "monotonic" and "queue".

"Monotonic" means that the elements follow a pattern: increasing (or decreasing).

"Queue" means elements can only be operated on from the front and back of the queue.

P.S. The "queue" in a monotonic queue is somewhat different from an ordinary queue; this will be mentioned later.

## Example Analysis

### Explanation

With the concept of a monotonic queue above, it is natural to optimize with one.

We need the maximum (minimum) value among every consecutive $k$ numbers. Clearly, when a number enters the range where we are "looking for" the maximum value, if this number is larger than numbers before it (which entered the queue earlier), those earlier numbers will leave the queue earlier and can no longer be the maximum.

That is, when the above condition is satisfied, the previous numbers can be "popped", and then the current number can truly be pushed to the back of the queue.

This is equivalent to maintaining a decreasing queue, which matches the definition of a monotonic queue and reduces repeated comparisons. Moreover, because the maintained queue is inside the query range and is decreasing, the front of the queue must be the maximum value in the query range, so we only need to output the front.

It is clear that in this algorithm, each number enters and leaves the queue exactly once, so the time complexity is reduced to $O(n)$.

Because the query interval length is fixed, a value outside the query range cannot be output no matter how large it is. Therefore, we also need an array recording the original position of the $i$-th number in the queue, so that out-of-range queue fronts can be popped.

### Process

For example, constructing an increasing monotonic queue works as follows.

Original sequence:

```text
1 3 -1 -3 5 3 6 7
```

Because we always maintain the queue as **increasing**, the following happens (assume $k = 3$):

| Operation | Queue state |
| --------- | ----------- |
| Enqueue 1 | `{1}` |
| 3 is greater than 1, enqueue 3 | `{1 3}` |
| -1 is smaller than every element in the queue, so clear the queue and enqueue -1 | `{-1}` |
| -3 is smaller than every element in the queue, so clear the queue and enqueue -3 | `{-3}` |
| 5 is greater than -3, enqueue directly | `{-3 5}` |
| 3 is smaller than 5, dequeue 5 and enqueue 3 | `{-3 3}` |
| -3 is already outside the window, so dequeue -3; 6 is greater than 3, enqueue 6 | `{3 6}` |
| 7 is greater than 6, enqueue 7 | `{3 6 7}` |

???+ note "Reference Code for the Example"
    ```cpp
    --8<-- "docs/ds/code/monotonous-queue/monotonous-queue_1.cpp"
    ```

P.S. A major difference between this "queue" and an ordinary queue is that operations can be performed at the back. The STL has a similar data structure: `deque`.

???+ note "Example 2 [Luogu P2698 Flowerpot S](https://www.luogu.com.cn/problem/P2698)"
    Given coordinates of $N$ water droplets, where $y$ is the height of a droplet and $x$ is the position where it falls onto the $x$-axis. Each droplet falls at a speed of 1 unit per second. You need to place a flowerpot somewhere on the $x$-axis such that the time difference between the first droplet caught by the pot and the last droplet caught by the pot is at least $D$.
    We consider a droplet caught as long as it lands on the $x$-axis aligned with the edge of the pot. Given coordinates of $N$ droplets and the value of $D$, compute the minimum width $W$ of the flowerpot. $1\leq N \leq 100000 , 1 \leq D \leq 1000000, 0 \leq x,y\leq 10^6$.

After sorting all droplets by $x$ coordinate, the problem can be transformed into finding an interval with minimum $x$-coordinate difference such that the difference between the maximum and minimum $y$ coordinates in the interval is at least $D$. This is similar to the previous example because both involve the maximum and minimum values in an interval, but here the interval size is not fixed, and the interval size itself is the answer we seek.

We can still use two monotonic queues, one increasing and one decreasing, and as $R$ keeps moving right, maintain the maximum and minimum values in $[L,R]$. At this point, if $L$ is fixed, the maximum value in $[L,R]$ only increases, and the minimum value only decreases. Therefore, if $f(R) = \max[L,R]-\min[L,R]$, then $f(R)$ is an increasing function of $R$, so $f(R)\geq D \implies f(r)\geq D,R\lt r \leq N$. This shows that for every fixed $L$, the first $R$ to the right that satisfies the condition gives the optimal answer for this L.
Thus the overall solution is: fix $L$, move $R$ from left to right, and use two monotonic queues to maintain the extrema of $[L,R]$. When the first valid $R$ is found, update the answer and move $L$ right as well. As $L$ moves right, both monotonic queues must pop their fronts in time. In this way, until $R$ reaches the end, every element still enters and leaves each queue once, ensuring $O(n)$ time complexity.

???+ note "Reference Code"
    ```cpp
    --8<-- "docs/ds/code/monotonous-queue/monotonous-queue_2.cpp"
    ```
