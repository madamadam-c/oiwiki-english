This page briefly introduces binary search, ternary search derived from binary search, and binary search on the answer.

## Binary Search

### Definition

Binary search (English: binary search), also known as half-interval search (English: half-interval search) or logarithmic search (English: logarithmic search), is an algorithm for finding a specific element in a sorted array.

### Process

Using the example of finding an element in a sorted ascending array:

It examines the middle element of the current portion of the array each time. If the middle element is exactly what we're looking for, the search ends; if the middle element is less than the search value, only elements in the right side could be the target, so we search there; if the middle element is greater than the search value, we search in the left side for the same reason.

### Properties

#### Time Complexity

The optimal time complexity of binary search is $O(1)$.

The average and worst-case time complexity of binary search are both $O(\log n)$. Because during the binary search process, the algorithm halves the search interval each time, for an array of length $n$, at most $O(\log n)$ searches are performed.

#### Space Complexity

The space complexity of the iterative version of binary search is $O(1)$.

The space complexity of the recursive version (without tail-call elimination) of binary search is $O(\log n)$.

### Implementation

```cpp
int binary_search(int start, int end, int key) {
  int ret = -1;  // returns -1 index if not found
  int mid;
  while (start <= end) {
    mid = start + ((end - start) >> 1);  // direct averaging may overflow, so we use this method
    if (arr[mid] < key)
      start = mid + 1;
    else if (arr[mid] > key)
      end = mid - 1;
    else {  // check for equality last because most searches are either greater or less than
      ret = mid;
      break;
    }
  }
  return ret;  // single return point
}
```

???+ note "Note"
    See [Compiler Optimizations #Shift Instead of Multiplication](../lang/optimizations.md#shift-instead-of-multiplication). For the case where $n$ is a signed number, when you can guarantee $n \ge 0$, `n >> 1` requires fewer instructions than `n / 2`.

### Minimizing the Maximum Value

Note that "sorted" here means in a generalized sense. If the left or right side of an array all satisfies a certain condition while the other side does not, this can also be considered sorted (if we treat satisfying the condition as $1$ and not satisfying as $0$, then at least for this condition, the array is sorted along this dimension). In other words, binary search can be used to find the maximum (minimum) value that satisfies a certain condition.

To find the minimum possible maximum value that satisfies a condition ("minimize the maximum"), the first approach is to enumerate this "maximum value" from smallest to largest, then check whether it is valid. If the answer is monotonic, we can use binary search to find the answer faster. Therefore, to use binary search to solve such "minimize the maximum" problems, the following three conditions must be satisfied:

1.  The answer lies within a fixed interval;
2.  Finding a value that satisfies the condition might not be easy, but it should be relatively easy to check whether a given value satisfies the condition;
3.  The feasible solutions satisfy some monotonicity over the interval. In other words, if $x$ satisfies the condition, then $x + 1$ or $x - 1$ also satisfies the condition. (This establishes the monotonicity mentioned above)

Of course, the opposite problem of "maximizing the minimum" is analogous.

### STL Binary Search

C++ standard library provides functions for finding the first element not less than a given value [`std::lower_bound`](https://en.cppreference.com/w/cpp/algorithm/lower_bound) and finding the first element greater than a given value [`std::upper_bound`](https://en.cppreference.com/w/cpp/algorithm/upper_bound), both defined in the header `<algorithm>`.

Both use binary search internally, so the elements must be sorted before calling these functions.

### bsearch

The bsearch function is a binary search implementation in the C standard library, defined in `<stdlib.h>`. In the C++ standard library, this function is defined in `<cstdlib>`. qsort and bsearch are the only two algorithm functions in C.

Compared to qsort (see [STL Sorting](./stl-sort.md)), which has four parameters, bsearch has an additional leftmost parameter: the address of the element to search for. The reason for passing it in address form is to easily reuse the same comparison function as qsort, enabling immediate lookup after sorting. Therefore, this parameter cannot directly accept a value; instead, the search value must first be stored in a variable, then the address of that variable is passed.

Thus, the bsearch function has five parameters in total: the address of the element to search for, the array name, the number of elements, the element size, and the comparison rule. The comparison rule is still implemented by specifying a comparison function. For details, see [STL Sorting](./stl-sort.md).

The return value of bsearch is the address of the found element, which is of void type.

Note: bsearch differs from lower_bound and upper_bound discussed above in two ways:

-   When there are multiple elements satisfying the condition, it returns the first element satisfying the condition during binary search, so this element might be located in the middle of the multiple identical elements.
-   When the element cannot be found, it returns NULL.

You can implement the same functionality as bsearch using lower_bound, so problems that pass with bsearch can also be solved by rewriting with lower_bound. However, due to the second difference mentioned above — for example, searching for 3 in the sequence 1, 2, 4, 5, 6 — implementing lower_bound's functionality with bsearch becomes difficult.

Is it absolutely impossible to implement lower_bound's functionality with bsearch? The answer is no; there are some tricky techniques. By leveraging how the compiler handles comparison functions: always pointing the first parameter to the element to search and the second parameter to elements in the array, you can also implement lower_bound and upper_bound with bsearch, as shown in the example below. However, this requires the search array to be a global array so that its starting address can be directly passed.

```cpp
int A[100005];  // example global array

// Find the address of the first element not less than the search element
int lower(const void *p1, const void *p2) {
  int *a = (int *)p1;
  int *b = (int *)p2;
  if ((b == A || compare(a, b - 1) > 0) && compare(a, b) > 0)
    return 1;
  else if (b != A && compare(a, b - 1) <= 0)
    return -1;  // uses address arithmetic, so element type must be specified
  else
    return 0;
}

// Find the address of the first element greater than the search element
int upper(const void *p1, const void *p2) {
  int *a = (int *)p1;
  int *b = (int *)p2;
  if ((b == A || compare(a, b - 1) >= 0) && compare(a, b) >= 0)
    return 1;
  else if (b != A && compare(a, b - 1) < 0)
    return -1;  // uses address arithmetic, so element type must be specified
  else
    return 0;
}
```

Since OI competitors rarely write pure C nowadays, and this method has limited use cases, it is not the focus. For beginners, it is recommended to faithfully follow the established method and use C++'s lower_bound and upper_bound functions.

### Binary Search on the Answer

When solving problems, we often consider enumerating the answer and then checking whether the enumerated value is correct. If monotonicity is satisfied, then binary search is applicable. Replacing the enumeration with binary search in this context becomes "binary search on the answer."

???+ note "[Luogu P1873 Cutting Trees](https://www.luogu.com.cn/problem/P1873)"
    Lumberjack Mirko needs to cut down $M$ meters of wood. This is an easy job for Mirko because he has a brand new woodcutting machine that can fell trees like wildfire. However, Mirko is only allowed to fell trees in a single row.
    
    Mirko's woodcutting machine works as follows: Mirko sets a height parameter $H$ (in meters), the machine raises a giant saw blade to height $H$, and cuts off all parts of trees that are higher than $H$ (of course, parts of trees not higher than $H$ meters remain unchanged). Mirko gets the cut-off parts of the trees.
    
    For example, if a row of trees has heights $20, 15, 10, 17$, and Mirko raises the saw blade to a height of $15$ meters, after cutting, the remaining heights of the trees will be $15, 15, 10, 15$, and Mirko will get $5$ meters of wood from the first tree and $2$ meters from the fourth tree, totaling $7$ meters of wood.
    
    Mirko is very concerned about ecological conservation, so he will not cut too much wood. That's why he sets the saw blade as high as possible. Your task is to help Mirko find the maximum integer height $H$ of the saw blade so that he can get at least $M$ meters of wood. That is, if the blade is raised by just $1$ meter, he will not get $M$ meters of wood.

??? note "Solution Approach"
    We could enumerate the answer between $1$ and $10^9$, but this naive approach will definitely not get full marks because enumerating from $1$ to $10^9$ is too time-consuming. We can perform binary search on the answer in the interval $[1, 10^9]$, then check the feasibility of each candidate answer (usually using a greedy approach). **This is binary search on the answer.**

??? note "Reference Code"
    ```cpp
    int a[1000005];
    int n, m;
    
    bool check(int k) {  // check feasibility, k is blade height
      long long sum = 0;
      for (int i = 1; i <= n; i++)       // check each tree
        if (a[i] > k)                    // if the tree is taller than blade height
          sum += (long long)(a[i] - k);  // accumulate the length of wood cut
      return sum >= m;                   // if minimum length is met, it's feasible
    }
    
    int find() {
      int l = 1, r = 1e9 + 1;   // since it's left-closed, right-open, 10^9 needs +1
      while (l + 1 < r) {       // if the two points are not adjacent
        int mid = (l + r) / 2;  // take the middle value
        if (check(mid))         // if feasible
          l = mid;              // increase blade height
        else
          r = mid;  // otherwise decrease blade height
      }
      return l;  // return the left value
    }
    
    int main() {
      cin >> n >> m;
      for (int i = 1; i <= n; i++) cin >> a[i];
      cout << find();
      return 0;
    }
    ```
    
    After looking at the code above, you probably have two questions:
    
    1. Why is the search interval left-closed, right-open?
    
        Because at the end of the search, it will look like this (using a valid maximum as example):
    
        ![](./images/binary-final-1.svg)
    
        Then it will be
    
        ![](./images/binary-final-2.svg)
    
        The valid minimum is the opposite.
    2. Why return the left value?
    
        Same as above.

## Ternary Search

### Introduction

Binary search can be used to approximately find the zero of a function. If you need to find the extremum point of a unimodal function, you typically need to use ternary search.

For a function $f(x)$, if there exists $x^*$ such that $f(x)$ is monotonically increasing for $x < x^*$ and $f(x)$ is monotonically decreasing for $x > x^*$, then $f(x)$ is called a unimodal function. Obviously, $x^*$ is its maximum point, and $f(x^*)$ is its maximum value.

??? note "Why not find the extremum point by finding the zero of the derivative?"
    Objectively, after finding the derivative, using binary search to find the zero of the derivative (since the function is unimodal, the zero of the derivative in the same range is unique) to obtain the extremum point of the unimodal function is feasible.
    
    But first, for some functions, the process and result of differentiation are quite complex.
    
    Second, in some problems, the unimodal function for which we need to find the extremum point is not a single function, but rather a function derived from multiple functions with special operations (such as finding the maximum of the minimum values of multiple linear functions with not entirely identical monotonicity). In this case, the derivative function may be a piecewise function, and the function may be non-differentiable at some points.

???+ warning "Note"
    Ternary search can find both the maximum of a unimodal function and the minimum of a "univalley function." For simplicity, unless otherwise specified, the following text uses finding the maximum of a unimodal function as an example.

### Process

The basic idea of ternary search is similar to binary search, but each operation requires selecting two points $lmid < rmid$ within the current interval $[l, r]$ (between the two orange points in the figure below, the two blue points in the figure). As shown in the figure below, if $f(lmid) < f(rmid)$, then in $[l, lmid)$ (the red portion in the figure below), the function must be monotonically increasing, and the maximum point (the green point in the figure below) is definitely not in this interval, so this interval can be discarded; however, the possibility that the maximum point is to the right of $rmid$ cannot be ruled out, so we cannot discard more. The same logic applies in reverse.

![](images/ternary.svg)

The correctness of ternary search does not depend on the choice of $lmid$ and $rmid$. Typically, the two trisection points can be chosen. However, their choice does affect the efficiency of ternary search. This is because each operation of ternary search discards one of the two intervals. To reduce the number of operations in ternary search, the two intervals should be as large as possible. Therefore, selecting $mid - \varepsilon$ and $mid + \varepsilon$ as $lmid$ and $rmid$ respectively in each operation is a good choice. In fact, the $mid \pm \varepsilon$ selection is equivalent to approximating the derivative $\dfrac{f(mid+\varepsilon)-f(mid-\varepsilon)}{2\varepsilon}$ at $mid$ to determine on which side of $mid$ the extremum point lies.

### Implementation

The pseudocode is as follows:

$$
\begin{array}{l}
\textbf{Algorithm}\operatorname{TernarySearch}(f,l,r):\\
\textbf{Input. } \text{A unimodal function } f(x) \text{ and its domain } [l,r].  \\
\textbf{Output. } \text{The maximizer }x^*\text{, up to an error of }\varepsilon\text{, and its value } f(x^*). \\
\textbf{Method. } \\
\begin{array}{ll}
1 & \textbf{while } r - l > \varepsilon\\
2 & \qquad mid\gets (l+r)/2\\
3 & \qquad lmid\gets mid - \varepsilon / 3 \\
4 & \qquad rmid\gets mid + \varepsilon / 3 \\
5 & \qquad \textbf{if } f(lmid) < f(rmid) \\
6 & \qquad \qquad l\gets lmid \\
7 & \qquad \textbf{else } \\
8 & \qquad \qquad r\gets rmid \\
9 & x^* \gets (l+r)/2 \\
10& \textbf{return } x^*,~ f(x^*)
\end{array}
\end{array}
$$

???+ tip "Selection of Split Points"
    In the code, the split points are selected as $mid \pm \varepsilon / 3$ to ensure that the split points are always between the current $l$ and $r$, thus avoiding getting stuck in an infinite loop.

???+ info "Integer Case"
    If the domain of $f(x)$ is integers, then the above ternary search and the golden-section search discussed below should terminate when $r - l$ becomes small. For cases where $r - l$ is small, the maximum point should be found by brute force.

### Optimization: Golden-Section Search

If the cost of a single call to $f(x)$ is very high, you need to further reduce the number of $f(x)$ calls. The golden-section search method can further improve the constant factor of ternary search. This is also an important part of the optimum-seeking method proposed by Hua Luogeng.

In ternary search, each iteration requires two function calls, and after a single iteration, the interval length is at most reduced to $1/2$ of its original length. This means that to achieve precision $\varepsilon$, at least

$$
2\log_2\dfrac{r-l}{\varepsilon}
$$

function calls are required. This is the best result ternary search can achieve. If other split points are chosen, such as trisection points, the number of calls will increase because the interval reduction per iteration is slower.

The improvement idea of golden-section search is to reuse the split points already calculated earlier. Thus, except for the first iteration which requires two function calls, all subsequent iterations only need one function call. Let the golden-section ratio be

$$
\phi = \dfrac{\sqrt{5}-1}{2} \approx 0.618.
$$

In each iteration, the selected split points are the left and right golden-section points:

$$
m^l = \phi l +(1-\phi)r,~m^r = (1-\phi)l+\phi r.
$$

Golden-section points divide a line segment with self-similarity. That is, $m^l$ is the left golden-section point of the segment $[l, r]$, and also the right golden-section point of the segment $[l, m^r]$. The benefit of this selection is that in the $k$-th iteration ($k > 1$), one of the selected split points must have been calculated before, so the previous computation result can be reused.

![](./images/golden-section-search.svg)

After selecting split points this way, to achieve precision $\varepsilon$, only

$$
1 + \log_{\phi^{-1}}\dfrac{r-l}{\varepsilon} \approx 1 + 1.44\log_2\dfrac{r-l}{\varepsilon}
$$

function calls are needed. Asymptotically, the number of function calls is fewer.

The pseudocode is as follows:

$$
\begin{array}{l}
\textbf{Algorithm}\operatorname{GoldenSectionSearch}(f,l,r):\\
\textbf{Input. } \text{A unimodal function } f(x) \text{ and its domain } [l,r].  \\
\textbf{Output. } \text{The maximizer }x^*\text{, up to an error of }\varepsilon\text{, and its value } f(x^*). \\
\textbf{Method. } \\
\begin{array}{ll}
1 & lmid \gets \phi l + (1-\phi)r \\
2 & rmid \gets (1-\phi)l + \phi r \\
3 & lval \gets f(lmid) \\
4 & rval \gets f(rmid) \\
5 & \textbf{while } r - l > \varepsilon \\
6 & \qquad \textbf{if } lval > rval \\
7 & \qquad \qquad r \gets rmid \\
8 & \qquad \qquad rmid \gets lmid \\
9 & \qquad \qquad rval \gets lval \\
10& \qquad \qquad lmid \gets \phi l + (1-\phi)r \\
11& \qquad \qquad lval \gets f(lmid) \\
12& \qquad \textbf{else} \\
13& \qquad \qquad l \gets lmid \\
14& \qquad \qquad lmid \gets rmid \\
15& \qquad \qquad lval \gets rval \\
16& \qquad \qquad rmid \gets (1-\phi)l + \phi r \\
17& \qquad \qquad rval \gets f(rmid) \\
18& x^* \gets (l+r)/2 \\
19& \textbf{return }x^*,~f(x^*)
\end{array}
\end{array}
$$

### Example Problems

???+ note "[Luogu P3382 - Ternary Search](https://www.luogu.com.cn/problem/P3382)"
    Given an $N$-th degree function and a range $[l, r]$, find the unique value $x$ such that the function is monotonically increasing on $[l, x]$ and monotonically decreasing on $[x, r]$.

??? note "Solution Approach"
    This problem requires finding the value of the independent variable when the $N$-th degree function achieves its maximum in $[l, r]$. Obviously, ternary search can be used.

??? note "Reference Code"
    === "C++"
        ```cpp
        --8<-- "docs/basic/code/binary/binary_1.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/basic/code/binary/binary_1.py"
        ```

### Practice Problems

-   [UVa 1476 - Error Curves](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4222)
-   [UVa 10385 - Duathlon](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1326)
-   [UOJ 162 - [Tsinghua Training 2015] Bulb Test](https://uoj.ac/problem/162)
-   [Luogu P7579 - [RdOI R2] Weighing](https://www.luogu.com.cn/problem/P7579)

## Fractional Programming

See: [Fractional Programming](../misc/frac-programming.md)

Fractional programming is typically described as the following problem: each item has two attributes $c_i$, $d_i$, and the goal is to select some items through a certain method such that $\frac{\sum{c_i}}{\sum{d_i}}$ is maximized or minimized.

Classic examples include the optimal ratio cycle and the optimal ratio spanning tree, etc.

Fractional programming can be solved using binary search.

## References

-   [Ternary search - Wikipedia](https://en.wikipedia.org/wiki/Ternary_search)
-   [Golden-section search - Wikipedia](https://en.wikipedia.org/wiki/Golden-section_search)
-   [Ternary search - CP Algortihms](https://cp-algorithms.com/num_methods/ternary_search.html)
