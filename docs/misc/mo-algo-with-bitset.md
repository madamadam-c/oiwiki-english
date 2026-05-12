author: StudyingFather, Backl1ght, countercurrent-time, Ir1d, greyqz, MicDZ, ouuan

`bitset` is often used for decision and counting problems that are hard to maintain with ordinary data structures, while Mo's algorithm can maintain range information that ordinary data structures cannot easily handle. Combining the two lets us use both advantages at the same time.

## Example [「Ynoi2016」Falling into a Rabbit Hole](https://www.luogu.com.cn/problem/P4688)

This problem exactly matches the characteristics above: Mo's algorithm plus `bitset`. It is not hard to think of storing all values that appear in each interval separately with `bitset`; the answer to one group of queries is the sum of all interval lengths minus the number of elements in the union of the three intervals $\times 3$.

However, using `bitset` inside Mo's algorithm also requires adapting the algorithm to `bitset`'s properties:

1.  `bitset` cannot handle multiple occurrences of the same value well. We can use the sum of the discretized value of the current element and its occurrence count in the current interval as the object inserted into the `bitset`.
2.  When using Mo's algorithm normally, we may not pay attention to the order of the four pointer moves, so during pointer movement the left endpoint may become greater than the right endpoint, making the interval length negative. This has no effect in many other cases, but in this problem the inserted `bitset` element is related to the element count, so we must pay attention to the order of the four pointer moves. Put the statements that move the left and right pointers outward first, avoiding insertion of negative numbers into the `bitset`.
3.  Although `bitset` uses little space, it still cannot handle a data scale of $10 ^ 5 \times 10 ^ 5$. Therefore, we need to divide the queries into a constant number of blocks and process them separately, ensuring that the space is just sufficient while the time complexity remains unchanged.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/misc/code/mo-algo-with-bitset/mo-algo-with-bitset_1.cpp"
    ```

## Exercises

-   [Fresh Scum's Wish](https://www.luogu.com.cn/problem/P3674)
-   [「Ynoi2017」Yuno's Cornfield](https://www.luogu.com.cn/problem/P5355)
-   [「Ynoi2011」WBLT](https://www.luogu.com.cn/problem/P5313)
