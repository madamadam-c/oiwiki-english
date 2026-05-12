author: Xeonacid, sshwy

If you are using C++ to create an algorithm competition problem, Testlib is an excellent tool when writing related programs (generator, validator, checker, interactor). It is a must-have tool for problem setters in Russia and some other countries, and many competitions use it: ROI, ICPC regionals, all Codeforces rounds...

The Testlib library consists of only one file `testlib.h`, and to use it, you only need to add `#include "testlib.h"` at the beginning of your program.

Specific uses of Testlib:

-   Write [Generator](./generator.md), a data generator.
-   Write [Validator](./validator.md), a data validator, to check if generated data meets problem requirements such as data range, format, etc.
-   Write [Interactor](./interactor.md), an interactor for interactive problems.
-   Write [Checker](./checker.md), a [Special Judge](../special-judge.md).

Testlib is fully compatible with the [Polygon](https://polygon.codeforces.com/) problem creation platform developed by Codeforces.

`testlib.h` was ported from `testlib.pas` in 2005 and has been continuously updated. Testlib is compatible with most compilers like VC++ and GCC g++, and is compatible with C++11.

**This article is mainly translated from [Testlib - Codeforces](https://codeforces.com/testlib). The GitHub repository for `testlib.h` is [MikeMirzayanov/testlib](https://github.com/MikeMirzayanov/testlib).**