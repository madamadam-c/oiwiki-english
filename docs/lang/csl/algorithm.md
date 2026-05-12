STL provides about 100 template functions that implement algorithms. Most are in `<algorithm>`, and some are in `<numeric>` and `<functional>`. For a complete list of functions, [see the reference manual](https://en.cppreference.com/w/cpp/algorithm). For sorting-related content, see the [corresponding sorting page](../../basic/stl-sort.md).

-   `find`: sequential search. `find(v.begin(), v.end(), value)`, where `value` is the value to find.

-   `reverse`: reverses an array or string. `reverse(v.begin(), v.end())` or `reverse(a + begin, a + end)`.

-   `unique`: removes adjacent duplicate elements in a container. `unique(ForwardIterator first, ForwardIterator last)` returns an iterator pointing to the end of the container **after deduplication**; the original container size remains unchanged. Used with `sort`, it can deduplicate the whole container.

-   `random_shuffle`: randomly shuffles an array. `random_shuffle(v.begin(), v.end())` or `random_shuffle(v + begin, v + end)`.

    ???+ warning "The `random_shuffle` function has been removed from the latest C++ standards"
        `random_shuffle` has been deprecated since C++14 and removed since C++17.
        
        In C++11 and later standards, you can use `shuffle` instead of the original `random_shuffle`. Use it as `shuffle(v.begin(), v.end(), rng)`, where the last argument is the random number generator. Usually, use a Mersenne Twister pseudo-random number generator [`mt19937`](https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine) seeded by a true random number generator [`random_device`](https://en.cppreference.com/w/cpp/numeric/random/random_device).
        
        ```cpp
        // #include <random>
        std::mt19937 rng(std::random_device{}());
        std::shuffle(v.begin(), v.end(), rng);
        ```

-   `sort`: sorts. `sort(v.begin(), v.end(), cmp)` or `sort(a + begin, a + end, cmp)`, where `end` is one past the last element of the range to sort, and `cmp` is a custom comparison function.

-   `stable_sort`: stable sort, used the same way as `sort()`.

-   `nth_element`: partitions a specified range, that is, finds the $n$-th largest element in the sequence so that elements on its left are less than it and elements on its right are greater than it. `nth_element(v.begin(), v.begin() + n, v.end(), cmp)` or `nth_element(a + begin, a + begin + n, a + end, cmp)`.

-   `binary_search`: binary search. `binary_search(v.begin(), v.end(), value)`, where `value` is the value to find.

-   `merge`: **merges two sorted sequences in order** into an **insert iterator** of a third sequence. `merge(v1.begin(), v1.end(), v2.begin(), v2.end() ,back_inserter(v3))`.

-   `inplace_merge`: **merges in place into one sorted sequence** two ranges `[first,middle), [middle,last)` that have already been sorted by the less-than operator. `inplace_merge(v.begin(), v.begin() + middle, v.end())`.

-   `lower_bound`: performs binary search in a sorted sequence and returns an iterator pointing to the first element **greater than or equal to** $x$. If no such element exists, it returns the end iterator. `lower_bound(v.begin(),v.end(),x)`.

-   `upper_bound`: performs binary search in a sorted sequence and returns an iterator pointing to the first element **greater than** $x$. If no such element exists, it returns the end iterator. `upper_bound(v.begin(),v.end(),x)`.

    ???+ warning "Time complexity of `lower_bound` and `upper_bound`"
        In ordinary arrays, both functions have time complexity $O(\log n)$. However, for associative containers such as `set`, directly calling `lower_bound(s.begin(),s.end(),val)` has time complexity $O(n)$.
        
        Associative containers such as `set` already provide member functions such as `lower_bound`, for example `s.lower_bound(val)`, and calling them this way has time complexity $O(\log n)$.

-   `next_permutation`: changes the current permutation to the **next permutation in lexicographical order**. If the current permutation is already the **last permutation** (elements fully descending), the function returns `false` and changes it to the **first permutation** (elements fully ascending); otherwise it returns `true`. `next_permutation(v.begin(), v.end())` or `next_permutation(v + begin, v + end)`.

-   `prev_permutation`: changes the current permutation to the **previous permutation in lexicographical order**. Used the same way as `next_permutation`.

-   `partial_sum`: computes prefix sums. Let the source container be $x$ and the target container be $y$; then $y[i]=x[0]+x[1]+\dots+x[i]$. `partial_sum(src.begin(), src.end(), back_inserter(dst))`.

### Examples

-   Use `next_permutation` to generate all permutations of $1$ to $9$. Example problem: [Luogu P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)

    ???+ note "Implementation"
        ```cpp
        int N = 9, a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        do {
          for (int i = 0; i < N; i++) cout << a[i] << " ";
          cout << endl;
        } while (next_permutation(a, a + N));
        ```
-   Use `lower_bound` and `upper_bound` to find the boundaries between elements less than $x$, equal to $x$, and greater than $x$ in a sorted array $a$.

    ???+ note "Implementation"
        ```cpp
        int N = 10, a[] = {1, 1, 2, 4, 5, 5, 7, 7, 9, 9}, x = 5;
        int i = lower_bound(a, a + N, x) - a, j = upper_bound(a, a + N, x) - a;
        // a[0] ~ a[i - 1] are elements less than x, a[i] ~ a[j - 1] are elements equal to x,
        // a[j] ~ a[N - 1] are elements greater than x
        cout << i << " " << j << endl;
        ```
-   Use `partial_sum` to compute prefix sums of elements in $src$ and store them in $dst$.

    ???+ note "Implementation"
        ```cpp
        vector<int> src = {1, 2, 3, 4, 5}, dst;
        // Computes prefix sums of elements in src, dst[i] = src[0] + ... + src[i]
        // The back_inserter function acts on dst and provides an iterator
        partial_sum(src.begin(), src.end(), back_inserter(dst));
        for (unsigned int i = 0; i < dst.size(); i++) cout << dst[i] << " ";
        ```
-   Use `lower_bound` to find the element closest to $x$ in a sorted array $a$. Example problem: [UVa10487 Closest Sums](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1428)

    ???+ note "Implementation"
        ```cpp
        int N = 10, a[] = {1, 1, 2, 4, 5, 5, 8, 8, 9, 9}, x = 6;
        // lower_bound returns the address of the first element in a greater than or equal to x;
        // the computed i is its index
        int i = lower_bound(a, a + N, x) - a;
        // In the following two cases, a[i], the first element in a greater than or equal to x,
        // is the answer:
        // 1. the smallest element in a is greater than or equal to x;
        // 2. an element greater than or equal to x exists in a, and the first such element (a[i])
        // is closer to x than the first element less than x (a[i - 1]);
        // otherwise, a[i - 1], the first element in a less than x, is the answer
        if (i == 0 || (i < N && a[i] - x < x - a[i - 1]))
          cout << a[i];
        else
          cout << a[i - 1];
        ```
-   Use `sort` and `unique` to find the **$k$-th smallest distinct value** in array $a$. Note that repeated values are counted only once, so this is not asking for the $k$-th smallest element. Example problem: [Luogu P1138 第 k 小整数](https://www.luogu.com.cn/problem/P1138)

    ???+ note "Implementation"
        ```cpp
        int N = 10, a[] = {1, 3, 3, 7, 2, 5, 1, 2, 4, 6}, k = 3;
        sort(a, a + N);
        // unique returns the address after the last element of the deduplicated array;
        // the computed cnt is the length after deduplication
        int cnt = unique(a, a + N) - a;
        cout << a[k - 1];
        ```
