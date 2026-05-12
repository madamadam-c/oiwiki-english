author: SDLTF, Ethkuil

## Problem Introduction

Given a sequence with $n$ elements, guaranteed that some element $a$ appears **strictly more than**  $n/2$ times, find this element.

## Methods

### Offline Algorithm

If the entire sequence is known from the beginning, a natural idea is to count the number of occurrences of each element in the sequence. The element whose count is greater than $n/2$ is the majority element. We can create a bucket to count the occurrences of each element, then output the element whose count is greater than $n/2$.

However, the above method introduces a bucket for counting, so its space efficiency is not good. Clearly, if a majority element exists in the sequence, then after sorting, the $\lfloor n/2\rfloor+1$-th element must be the majority element. Using [`nth_element`](https://en.cppreference.com/w/cpp/algorithm/nth_element.html), we can find this element. Thus, without introducing extra space, we can find the majority element in linear time.

### Online Algorithm

In some cases, we need to process streaming data online. Then we need an algorithm that does not know all data in advance and instead gradually obtains the answer using only the currently given data. The **majority vote algorithm** [^ref1] is an algorithm that can solve the majority element problem online.

Because the majority element appears more than $n/2$ times, for a complete sequence, if we repeatedly cancel out one majority element and one element different from the majority element, the majority element must remain at the end. Using this observation, we can design an online algorithm that performs such cancellations. Let variables `val` and `cnt` represent the current majority-element candidate and how many of this candidate would remain after these cancellations. Initially set `cnt` to $0$. Each time an element is taken from the data stream, if the current `cnt` is $0$, it means the majority-element candidate has been completely eliminated, and the currently recorded `val` is definitely not the majority element, so set the current element as the majority-element candidate. Then check whether the current element is the majority-element candidate. If it is, increase `cnt` by $1$; otherwise, this element should be canceled together with one majority-element candidate, so decrease `cnt` by $1$. Repeat the process until the data stream is finished; `val` is the majority element.

???+ warning "Note"
    If the original data has no majority element, this algorithm gives an incorrect result. To determine whether the sequence has a majority element, read the data stream again, count the number of occurrences of `val`, and check whether it exceeds $n/2$.
    
    To read the data stream again, you can choose to reset the input position indicator, using library functions such as [`std::basic_istream<CharT,Traits>::seekg`](https://en.cppreference.com/w/cpp/io/basic_istream/seekg) (stream input) or [`rewind`](https://en.cppreference.com/w/c/io/rewind), [`fseek`](https://en.cppreference.com/w/c/io/fseek) (C-style input).

## Examples

???+ example "[Luogu P2397 yyy loves Maths VI (mode)](https://www.luogu.com.cn/problem/P2397)"
    Find the majority element of a given sequence.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/misc/code/main-element/main-element_1.cpp"
    ```

???+ example "[LeetCode 229. Majority Element II](https://leetcode.cn/problems/majority-element-ii)"
    Given an integer array of size $n$, find all elements that appear more than $\lfloor n/3\rfloor$ times.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/misc/code/main-element/main-element_2.cpp:core"
    ```

## References

[^ref1]: [Majority vote algorithm - Wikipedia](https://zh.wikipedia.org/zh-cn/%E5%A4%9A%E6%95%B0%E6%8A%95%E7%A5%A8%E7%AE%97%E6%B3%95)
