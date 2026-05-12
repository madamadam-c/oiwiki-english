## C++ Standards

The first thing to introduce is the versions of C++ itself. Since C++ is only a language, and different compilers implement C++ in different ways, standardization is needed to constrain compiler implementations so that C++ code behaves consistently across compilers. Since C++ was created in 1985, the International Organization for Standardization (ISO) has published 7 official C++ standards: C++98, C++03, C++11 (also called C++0x), C++14 (also called C++1y), C++17 (also called C++1z), C++20 (also called C++2a), and C++23 (also called C++2b). C++ standard drafts are available on [open-std](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/), and the latest standardization progress can be viewed at [Current Status : Standard C++](https://isocpp.org/std/status). There are also supplementary standards, such as C++ TR1.

Each version of the C++ standard specifies not only C++ syntax and language features, but also the implementation requirements for a built-in C++ library: the C++ standard library. The C++ standard library contains implementations of many commonly used facilities, such as input/output, basic data structures, memory management, and multithreading support. Mastering the C++ standard library is a necessary step toward writing more modern C++ code. Detailed documentation for the C++ standard library is available on [cppreference](https://en.cppreference.com/), which describes the usage, efficiency, and caveats of standard-library types and functions. Make good use of it.

It should be noted that different online judges support different C++ versions. For example, the [latest ICPC contest rules](https://docs.icpc.global/worldfinals-programming-environment/) support the C++20 standard. According to the decision of the NOI Scientific Committee, since September 1, 2021, [NOI Linux 2.0](https://www.noi.cn/gynoi/jsgz/2021-07-16/732450.shtml) has been used as the standard environment for NOI-series contests and CSP-J/S activities. The g++ 9.3.0 specified by NOI Linux 2.0 [defaults](https://gcc.gnu.org/projects/cxx-status.html#cxx14) to C++14 and supports C++17, which meets the needs of most contestants. Therefore, when learning C++, pay attention to the standard supported by your contest to avoid compilation errors during competition.

## Standard Template Library (STL)

STL stands for Standard Template Library. It is part of the C++ standard library and contains templated, general-purpose data structures and algorithms. Because it is template-based, it can work with custom data types and avoids a great deal of reinventing the wheel. NOI and ICPC contests both allow the use of STL, so using STL appropriately can avoid writing unnecessary code and can take advantage of compiler optimizations for template libraries to improve efficiency. For detailed introductions to STL, see the corresponding pages: [STL Containers](./container.md) and [STL Algorithms](./algorithm.md).

??? note "What is reinventing the wheel?"
    Reinventing the wheel ([Reinventing\_the\_wheel](https://en.wikipedia.org/wiki/Reinventing_the_wheel)) means re-creating existing algorithms or rewriting already optimized code. It is usually time-consuming and labor-intensive, and the result is often not as good as existing solutions. However, for learning or practice, reinventing the wheel can be necessary.

## Boost Library

[Boost](https://www.boost.org/) is another renowned open-source C++ utility library besides the standard library. Its code is portable, high-quality, high-performance, and highly reliable. Boost contains a very large number of modules, provides comprehensive functionality, and has complete cross-platform support, so it is regarded as a quasi-standard library for C++. Many features in the C++ standard also originated from Boost, such as smart pointers, metaprogramming, and date/time utilities. Although Boost cannot be used in OI contests, it contains many useful implementations for verifying algorithms or stress testing. For example, Boost.Geometry provides an R-tree implementation, Boost.Graph provides graph algorithms, and Boost.Intrusive provides intrusive containers with usage similar to STL containers. Interested readers can search for tutorials online.

## References

1.  [C++ reference](https://en.cppreference.com/)
2.  [C++ reference](https://en.cppreference.com/)
3.  [Wikipedia - C++](https://en.wikipedia.org/wiki/C%2B%2B)
4.  [Boost official website](https://www.boost.org/)
5.  [Boost tutorial website](https://theboostcpplibraries.com/)
