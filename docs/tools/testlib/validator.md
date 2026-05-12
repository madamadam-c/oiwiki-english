Prerequisite: [General](./general.md)

This page briefly introduces the concept and usage of validator.

## Overview

Validator is used to check the validity of generated data. When data for a problem has been generated but there are concerns about the data being invalid (not meeting problem constraints: overflow, disconnected graph, not a tree, etc.), problem setters usually use validator to check.[^ref1]

Since Codeforces supports hacks, all problems on Codeforces must have validators. UOJ does as well. [Polygon](../polygon.md) has built-in support for validator.

## Usage

Simply input `./val` on the command line. Data is input via stdin. If you want to input from a file, you can `./val < a.in`.

If the data is valid, nothing will be output and it returns 0; otherwise, it outputs an error message and returns a non-zero value.

## Tips

-   When writing validator, you cannot make any assumptions about the data being validated, because it may contain anything. Therefore, problem setters must check for various invalid conditions (using Testlib greatly simplifies this process).
    -   For example, input a tree with $n$ vertices. The main work is to check whether $n$ is within range and whether the input is a tree. But after checking $n$'s range, don't forget to check the range of the start and end points of edges that follow, otherwise it may cause validator RE.
    -   Even if it won't cause RE, you shouldn't skip the check, as it will cause your error message to be incorrect. As in the example above, if you don't check, the error might be "not a tree", but the correct error should be "edge start/end not in $[1,n]$".
-   You cannot make any assumptions about how participants read input. Therefore, the data that passes validation must fully conform to the input format.
    -   For example, participants may read numbers character by character, reading only one space between numbers. So when writing validator, every whitespace character in the data must be explicitly read in validator (like spaces and newlines).
-   Don't forget `inf.readEof()` at the end.
-   If the problem allows hacking (that is, the validator's error message will be visible to others), please make the error message as friendly as possible.
    -   Use "item aliases" when reading variables.
    -   Use ensuref instead of ensure when the expression being checked is not easy to understand.

## Example

Below is the validator for [CF Gym 100541A - Stock Market](https://codeforces.com/gym/100541/problem/A):

```cpp
#include "testlib.h"

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  int testCount = inf.readInt(1, 10, "testCount");
  inf.readEoln();

  for (int i = 0; i < testCount; i++) {
    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    inf.readInt(1, 1000000, "w");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
      inf.readInt(1, 1000, "p_i");
      if (i < n - 1) inf.readSpace();
    }
    inf.readEoln();
  }

  inf.readEof();
}
```

## External Links

-   [More examples of validators](https://github.com/MikeMirzayanov/testlib/tree/master/validators)
-   [GitHub repository for `testlib.h`: MikeMirzayanov/testlib](https://github.com/MikeMirzayanov/testlib)

## References and Notes

[^ref1]: [Validators with testlib.h - Codeforces](https://codeforces.com/blog/entry/18426)