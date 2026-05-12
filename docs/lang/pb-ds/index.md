author: HeRaNO, Xeonacid, saffahyjp

The full name of the pb\_ds library is Policy-Based Data Structures.

The pb\_ds library wraps many data structures, such as hash tables, balanced binary trees, tries, heaps (priority queues), and so on.

Like `vector`, `set`, and `map`, its components conform to the relevant STL interface conventions. Some components, such as priority queues, include all functionality of the corresponding STL components while providing more features.

pb\_ds is available only with compilers that use libstdc++ as the standard library.

You can use `begin()` and `end()` to obtain iterators for traversal.

It supports `increase_key`, `decrease_key`, and deletion of individual elements.

Because the main contents of the pb\_ds library are in the `__gnu_pbds` namespace, whose name begins with underscores, its legality in NOI-series events had long been unclear. On September 1, 2021, according to the [Supplementary Explanation on Programming Language Restrictions in NOI-Series Events](https://www.noi.cn/xw/2021-09-01/735729.shtml), library functions or macros whose names begin with underscores are allowed, except for library functions and macros with explicitly prohibited operations. This provides documentary support for using pb\_ds in NOI-series events.

**Reference: [Applications of the C++ pb\_ds Library in OI](https://github.com/OI-Wiki/libs/blob/master/lang/pb-ds/C%2B%2B的pb_ds库在OI中的应用.pdf)**
