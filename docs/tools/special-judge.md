author: Xeonacid, NachtgeistW, 2014CAIS01, sshwy, Chrogeek, Menci, yzy-1

This page mainly introduces how to write spj for some judging tools/OJs.

## Introduction

**Special Judge** (abbreviated: spj, also known as checker) is a program used to determine whether an answer is valid when a problem has multiple valid solutions.

???+ warning "Warning"
    spj should also check for extra content at the end of the file and whether the output format is correct (e.g., the problem requires numbers separated by a single space, but the contestant uses newlines). However, currently only Testlib can conveniently do the former, and almost no one specifically checks the latter.

    Be careful with NaN when comparing floating-point numbers. An incorrect comparison method can lead to the situation where outputting NaN will result in AC.

    When reading the contestant's file, make sure to check whether the required content was read correctly to prevent runtime errors in the spj. (Some OJs treat spj runtime errors as system errors)

???+ note "Note"
    The following all use C++ as the programming language, and use "the standard answer and contestant's answer must differ by less than 1e-3, file name is num, full score for a single test case is 10 points" as an example.

## Testlib

See also: [Testlib/Introduction](./testlib/index.md), [Testlib/Checker](./testlib/checker.md)

Testlib is a C++ library used to help problem setters write algorithm competition problems in C++.

Judging tools/OJs that must use Testlib for spj: Codeforces, Luogu, UOJ, etc.

Judging tools/OJs that can use Testlib for spj: LibreOJ ([Lyrio](https://github.com/lyrio-dev)), Lemon, NowCoder, etc.

The modified version of Testlib required for SYZOJ 2 is hosted on [pastebin](https://pastebin.com/3GANXMG7)[^1], but this modified version does not modify the interactive mode. A version of Testlib that can be used in interactive mode on SYZOJ 2 is hosted at [syzoj/testlib](https://github.com/syzoj/testlib).

The modified version of Testlib required for Lemon is hosted at [GitHub - GitPinkRabbit/Testlib-for-Lemons](https://github.com/GitPinkRabbit/Testlib-for-Lemons). Note that when registering a checker in this version of Testlib, use `registerLemonChecker()` instead of `registerTestlibCmd()`. This version is derived from [matthew99's old version](https://paste.ubuntu.com/p/JsTspHHnmB/) and adds some new features of Testlib. If you use LemonLime, you can use the native Testlib.

The modified version of Testlib required for DOMJudge is hosted at [cn-xcpc-tools/testlib-for-domjudge](https://github.com/cn-xcpc-tools/testlib-for-domjudge). This version of Testlib can serve as both a Special Judge checker and an interactor for interactive problems.

The modified version of Testlib required for Arbiter is hosted at [testlib-for-arbiter](https://github.com/HeRaNO/ChickenRibs/tree/master/testlib-for-arbiter).

Most other judging tools/OJs require modifying Testlib according to their spj writing format, and uploading testlib.h along with the spj; or placing testlib.h in the include directory.

```cpp
#include "testlib.h"
//
#include <cmath>

int main(int argc, char *argv[]) {
  /*
   * inf: input
   * ouf: contestant output
   * ans: standard output
   */
  registerTestlibCmd(argc, argv);

  double pans = ouf.readDouble(), jans = ans.readDouble();

  if (abs(pans - jans) < 1e-3)
    quitf(_ok, "Good job\n");
  else
    quitf(_wa, "Too big or too small, expected %f, found %f\n", jans, pans);
}
```

## Lemon

???+ note "Note"
    Lemon has a ready-made modified version of [Testlib](#testlib), and using Testlib is recommended.

    The latest version of LemonLime already supports writing checkers using the native Testlib. If you use LemonLime, it is recommended to use Testlib.

```cpp
#include <cmath>
#include <cstdio>

int main(int argc, char* argv[]) {
  /*
   * argv[1]: input
   * argv[2]: contestant output
   * argv[3]: standard output
   * argv[4]: score for a single test case
   * argv[5]: output final score (0 ~ argv[4])
   * argv[6]: output error report
   */
  FILE* fin = fopen(argv[1], "r");
  FILE* fout = fopen(argv[2], "r");
  FILE* fstd = fopen(argv[3], "r");
  FILE* fscore = fopen(argv[5], "w");
  FILE* freport = fopen(argv[6], "w");

  double pans, jans;
  fscanf(fout, "%lf", &pans);
  fscanf(fstd, "%lf", &jans);

  if (abs(pans - jans) < 1e-3) {
    fprintf(fscore, "%s", argv[4]);
    fprintf(freport, "Good job\n");
  } else {
    fprintf(fscore, "%d", 0);
    fprintf(freport, "Too big or too small, expected %f, found %f\n", jans,
            pans);
  }
}
```

## Cena

```cpp
#include <cmath>
#include <cstdio>

int main(int argc, char* argv[]) {
  /*
   * FILENAME.in: input
   * FILENAME.out: contestant output
   * argv[1]: score for a single test case
   * argv[2]: standard output
   * score.log: output final score (0 ~ argv[1])
   * report.log: output error report
   */
  FILE* fin = fopen("num.in", "r");
  FILE* fout = fopen("num.out", "r");
  FILE* fstd = fopen(argv[2], "r");
  FILE* fscore = fopen("score.log", "w");
  FILE* freport = fopen("report.log", "w");

  double pans, jans;
  fscanf(fout, "%lf", &pans);
  fscanf(fstd, "%lf", &jans);

  if (abs(pans - jans) < 1e-3) {
    fprintf(fscore, "%s", argv[1]);
    fprintf(freport, "Good job\n");
  } else {
    fprintf(fscore, "%d", 0);
    fprintf(freport, "Too big or too small, expected %f, found %f\n", jans,
            pans);
  }
}
```

## CCR

```cpp
#include <cmath>
#include <cstdio>

int main(int argc, char* argv[]) {
  /*
   * stdin: input
   * argv[2]: standard output
   * argv[3]: contestant output
   * stdout:L1: output final score ratio (0 ~ 1)
   * stdout:L2: output error report
   */
  FILE* fout = fopen(argv[3], "r");
  FILE* fstd = fopen(argv[2], "r");

  double pans, jans;
  fscanf(fout, "%lf", &pans);
  fscanf(fstd, "%lf", &jans);

  if (abs(pans - jans) < 1e-3) {
    printf("%d\n", 1);
    printf("Good job\n");
  } else {
    printf("%d\n", 0);
    printf("Too big or too small, expected %f, found %f\n", jans, pans);
  }
}
```

## Arbiter

```cpp
#include <cmath>
#include <cstdio>

int main(int argc, char* argv[]) {
  /*
   * argv[1]: input
   * argv[2]: contestant output
   * argv[3]: standard output
   * /tmp/_eval.score:L1: output error report
   * /tmp/_eval.score:L2: output final score
   */
  FILE* fout = fopen(argv[2], "r");
  FILE* fstd = fopen(argv[3], "r");
  FILE* fscore = fopen("/tmp/_eval.score", "w");

  double pans, jans;
  fscanf(fout, "%lf", &pans);
  fscanf(fstd, "%lf", &jans);

  if (abs(pans - jans) < 1e-3) {
    fprintf(fscore, "Good job\n");
    fprintf(fscore, "%d", 10);
  } else {
    fprintf(fscore, "Too big or too small, expected %f, found %f\n", jans,
            pans);
    fprintf(fscore, "%d", 0);
  }
}
```

## HUSTOJ

```cpp
#include <cmath>
#include <cstdio>

#define AC 0
#define WA 1

int main(int argc, char* argv[]) {
  /*
   * argv[1]: input
   * argv[2]: standard output
   * argv[3]: contestant output
   * exit code: return judging result
   */
  FILE* fin = fopen(argv[1], "r");
  FILE* fout = fopen(argv[3], "r");
  FILE* fstd = fopen(argv[2], "r");

  double pans, jans;
  fscanf(fout, "%lf", &pans);
  fscanf(fstd, "%lf", &jans);

  if (abs(pans - jans) < 1e-3)
    return AC;
  else
    return WA;
}
```

## QDUOJ

Compared with other platforms, QDUOJ is slightly more complicated. Problems with spj on QDUOJ do not have a standard output; instead, the std must be written into the spj, and the standard output is generated after running, then compared.

```cpp
#include <cmath>
#include <cstdio>

#define AC 0
#define WA 1
#define ERROR -1

double solve(...) {
  // std
}

int main(int argc, char* argv[]) {
  /*
   * argv[1]: input
   * argv[2]: contestant output
   * exit code: return judging result
   */
  FILE* fin = fopen(argv[1], "r");
  FILE* fout = fopen(argv[2], "r");

  double pans, jans;
  fscanf(fout, "%lf", &pans);

  jans = solve(...);
  if (abs(pans - jans) < 1e-3)
    return AC;
  else
    return WA;
}
```

## HDOJ

HDOJ is essentially similar to QDUOJ; it also needs to implement std in the spj and then compare with the contestant's output. However, unlike QDUOJ, HDOJ compares the answer with the content output to stdout by the spj to give the final result. Therefore, when uploading, you only need to upload the output from the spj when the answer is correct.

HDOJ requires uploading compiled binary files for Windows, not source code.

```cpp
#include <cmath>
#include <cstdio>

double solve(FILE* fin) {
  // std, read input from fin
}

int main(int argc, char* argv[]) {
  /*
   * argv[1]: input
   * stdin: contestant output
   */
  FILE* fin = fopen(argv[1], "r");

  double pans, jans;
  if (scanf("%lf", &pans) != 1) {
    printf("WA\n");
    goto finish;
  }

  jans = solve(fin);
  if (abs(pans - jans) < 1e-3)
    printf("AC\n");
  else
    printf("WA\n");

finish:
  fclose(fin);
  return 0;
}
```

The corresponding answer file is:

```text
AC
```

## SYZOJ 2

???+ note "Note"
    SYZOJ 2 has a ready-made modified version of [Testlib](#testlib), and using Testlib is recommended.

    The latest version of LibreOJ is no longer based on SYZOJ, but on [Lyrio](https://github.com/lyrio-dev/lyrio). Lyrio supports writing checkers using the native Testlib, which is more universal and recommended.

```cpp
#include <cmath>
#include <cstdio>

int main(int argc, char* argv[]) {
  /*
   * in: input
   * user_out: contestant output
   * answer: standard output
   * code: contestant code
   * stdout: output final score (0 ~ 100)
   * stderr: output error report
   */
  FILE* fin = fopen("input", "r");
  FILE* fout = fopen("user_out", "r");
  FILE* fstd = fopen("answer", "r");
  FILE* fcode = fopen("code", "r");

  double pans, jans;
  fscanf(fout, "%lf", &pans);
  fscanf(fstd, "%lf", &jans);

  if (abs(pans - jans) < 1e-3) {
    printf("%d", 100);
    fprintf(stderr, "Good job\n");
  } else {
    printf("%d", 0);
    fprintf(stderr, "Too big or too small, expected %f, found %f\n", jans,
            pans);
  }
}
```

## NowCoder

???+ note "Note"
    NowCoder has a ready-made modified version of [Testlib](#testlib), and using Testlib is recommended.

See also: [How to Create a Special Judge Programming Problem on NowCoder](https://www.nowcoder.com/discuss/84666)

```cpp
#include <cmath>
#include <cstdio>

#define AC 0
#define WA 1

int main(int argc, char* argv[]) {
  /*
   * input: input
   * user_output: contestant output
   * output: standard output
   * exit code: return judging result
   */
  FILE* fin = fopen("input", "r");
  FILE* fout = fopen("user_output", "r");
  FILE* fstd = fopen("output", "r");

  double pans, jans;
  fscanf(fout, "%lf", &pans);
  fscanf(fstd, "%lf", &jans);

  if (abs(pans - jans) < 1e-3)
    return AC;
  else
    return WA;
}
```

## DOMJudge

???+ note "Note"
    DOMJudge supports spj written in any language. See: [problemarchive.org output validator format](https://www.problemarchive.org/wiki/index.php/Output_validator).

    DOMJudge has a ready-made modified version of [Testlib](#testlib), and using Testlib is recommended.

Documentation for Testlib used by DOMJudge and how to import Polygon packages: <https://github.com/cn-xcpc-tools/testlib-for-domjudge>

DOMJudge's [default comparator](https://github.com/Kattis/problemtools/blob/master/support/default_validator/) has built-in floating-point comparison with tolerance; you only need to add `float_tolerance 1e-3` in the problem's `validator_flags`.

```cpp
#include <cmath>
#include <cstdio>

#define AC 42
#define WA 43
char reportfile[50];

int main(int argc, char* argv[]) {
  /*
   * argv[1]: input
   * argv[2]: standard output
   * argv[3]: folder for judging info output
   * stdin: contestant output
   */
  FILE* fin = fopen(argv[1], "r");
  FILE* fstd = fopen(argv[2], "r");
  sprintf(reportfile, "%s/judgemessage.txt", argv[3]);
  FILE* freport = fopen(reportfile, "w");

  double pans, jans;
  scanf("%lf", &pans);
  fscanf(fstd, "%lf", &jans);

  if (abs(pans - jans) < 1e-3) {
    fprintf(freport, "Good job\n");
    return AC;
  } else {
    fprintf(freport, "Too big or too small, expected %f, found %f\n", jans,
            pans);
    return WA;
  }
}
```

You can also use the header file [validate.h](https://github.com/Kattis/problemtools/blob/master/examples/different/output_validators/different_validator/validate.h) provided by Kattis Problem Tools to write more complex functionality.

## References

[^1]: [LibreOJ Now Supports Testlib Checker!](https://loj.ac/article/124)