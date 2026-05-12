This page introduces some common states/objects/functions of Testlib checker/interactor/validator, some usage notes and precautions. Please read this page completely before reading other pages.

## Common States

| Result               | Testlib Alias   | Meaning                                                                                                                             |
| ------------------ | ------------ | ------------------------------------------------------------------------------------------------------------------------------- |
| Ok                 | `_ok`        | Answer is correct.                                                                                                                           |
| Wrong Answer       | `_wa`        | Answer is wrong.                                                                                                                           |
| Presentation Error | `_pe`        | Answer format is incorrect. Note that many OJs including Codeforces do not distinguish between PE and WA.                                                                                   |
| Partially Correct  | `_pc(score)` | Answer is partially correct. Only for test cases with partial scoring, where `score` is a positive integer from $0$ (no score) to $100$ (maximum possible score). (`quitf+_pc` only exists for compatibility with old pascal-testlib; if you want to output partial scores, use `quitp`[^1]) |
| Fail               | `_fail`      | In validator: input is invalid, fails validation.<br>In checker: internal program error, incorrect standard output, or participant output is better than standard output, requires attention from judge/problem setter. (This means the problem has an issue)                                          |

Usually the program's return value indicates the result, but there are also other methods: creating an output xml file, outputting information to stdout or other locations... All of these are done via the `quitf` function in the function table below.

## Common Objects

| Object    | Meaning    |
| ----- | ----- |
| `inf` | Input file stream |
| `ouf` | Participant output stream |
| `ans` | Reference output stream |

## Common Functions

Non-member functions:

| Call                                                                                              | Meaning                                                                                                                                          |
| ----------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------- |
| `void registerTestlibCmd(int argc, char* argv[])`                                               | Register program as a checker                                                                                                                               |
| `void registerInteraction(int argc, char* argv[])`                                              | Register program as an interactor                                                                                                                            |
| `void registerValidation()`/`void registerValidation(int argc, char* argv[])`                   | Register program as a validator                                                                                                                             |
| `void registerGen(int argc, char* argv[], int randomGeneratorVersion)`                          | Register program as a generator<br>`randomGeneratorVersion` is recommended to be `1`                                                                                         |
| `void quit(TResult verdict, string message)`/`void quitf(TResult verdict, string message, ...)` | End program, return `verdict`, output `message`                                                                                                              |
| `void quitif(bool condition, TResult verdict, string message, ...)`                             | If `condition` is true, call `quitf(verdict, message, ...)`                                                                                         |
| `void quitp(F points, string message, ...)`                                                     | End program, return partial score. For most OJs (like Luogu, UOJ), `points` should be a real number in $[0,1]$, representing the score percentage; for some OJs (like Lyrio), `points` should be a real number in $[0,100]$ (the OJ will automatically discard the decimal part), representing the test case score in percentage system |

Stream member functions:

| Call                                                                                                                                                                | Meaning                                                                                 |
| ----------------------------------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------- |
| `char readChar()`                                                                                                                                                 | Read a character                                                                             |
| `char readChar(char c)`                                                                                                                                           | Read a character, must be `c`                                                                     |
| `char readSpace()`                                                                                                                                                | Equivalent to `readChar(' ')`                                                                |
| `string readToken()`/`string readWord()`                                                                                                                          | Read a token, stops at whitespace (space, tab, EOLN, etc.)                                                       |
| `string readToken(string regex)`/`string readWord(string regex)`                                                                                                  | Read a token, must match `regex`                                                               |
| `long long readLong()`                                                                                                                                            | Read a 64-bit integer                                                                        |
| `long long readLong(long long L, long long R)`                                                                                                                    | Read a 64-bit integer, must be in $[L,R]$                                                         |
| `vector<long long> readLongs(int n, long long L, long long R)`                                                                                                    | Read $N$ 64-bit integers, all must be in $[L,R]$                                                    |
| `int readInt()`/`int readInteger()`                                                                                                                               | Read a 32-bit integer                                                                        |
| `int readInt(int L, int R)`/`int readInteger(L, R)`                                                                                                               | Read a 32-bit integer, must be in $[L,R]$                                                         |
| `vector<int> readInts(int n, int L, int R)`/`vector<int> readIntegers(int n, int L, int R)`                                                                       | Read $N$ 32-bit integers, all must be in $[L,R]$                                                    |
| `double readReal()`/`double readDouble()`                                                                                                                         | Read a double-precision floating-point number                                                                         |
| `double readReal(double L, double R)`/`double readDouble(double L, double R)`                                                                                     | Read a double-precision floating-point number, must be in $[L,R]$                                                          |
| `double readStrictReal(double L, double R, int minPrecision, int maxPrecision)`/`double readStrictDouble(double L, double R, int minPrecision, int maxPrecision)` | Read a double-precision floating-point number, must be in $[L,R]$, number of decimal places must be in $[minPrecision,maxPrecision]$, cannot use exponential notation or other abnormal formats |
| `string readString()`/`string readLine()`                                                                                                                         | Read a line (including newline), stream pointer points to the start of the next line                                                         |
| `string readString(string regex)`/`string readLine(string regex)`                                                                                                 | Read a line, must match `regex`                                                                |
| `void readEoln()`                                                                                                                                                 | Read EOLN (reads `LF` on Linux, `CR LF` on Windows)                                |
| `void readEof()`                                                                                                                                                  | Read EOF                                                                             |
| `void quit(TResult verdict, string message)`/`void quitf(TResult verdict, string message, ...)`                                                                   | End program; if `Stream` is `ouf`, return `verdict`, otherwise return `_fail`; output `message`                     |
| `void quitif(bool condition, TResult verdict, string message, ...)`                                                                                               | If `condition` is true, call `quitf(verdict, message, ...)`                                |

To be continued...

## Minimal Regular Expressions

Some of the input functions above allow using the "Minimal Regular Expressions" feature, as follows:

-   Character sets. For example, `[a-z]` represents all lowercase English letters, `[^a-z]` represents any character except lowercase English letters.
-   Ranges. For example, `[a-z]{1,5}` represents a string with length in $[1,5]$ containing only lowercase English letters.
-   "Or" identifier. For example, `mike|john` represents either `mike` or `john`.
-   "Optional" identifier. For example, `-?[1-9][0-9]{0,3}` represents a non-zero integer in the range $[-9999,9999]$ (note the optional minus sign).
-   "Repeat" identifier. For example, `[0-9]*` represents zero or more digits, `[0-9]+` represents one or more digits.
-   Note that the regular expressions here are "greedy" (the "repeat" will match as much as possible). For example, `[0-9]?1` will not match `1` (because `[0-9]?` matches `1`, leaving the remaining `1` in the template string unable to match).

## Include testlib.h First

Make sure testlib.h is the **first** header file you include. Testlib will overwrite/disable (via name conflicts) some functions related to randomness (like `random()`), ensuring random results are independent of the environment. This is very important for generators; the [generator page](./generator.md) will explain this in detail.

## Use Item Aliases

It is recommended to add an extra `string` parameter at the end of constrained calls to `readInt/readInteger/readLong/readDouble/readWord/readToken/readString/readLine`, which is the alias of the currently read item, making errors easier to read. For example, use `inf.readInt(1, 100, "n")` instead of `inf.readInt(1, 100)`. The error message will be `FAIL Integer parameter [name=n] equals to 0, violates the range [1, 100]`.

## Use `ensuref/ensure()`

These two functions are used to check if a condition holds (similar to `assert()`). For example, to check $x_i \neq y_i$, we can use

```cpp
ensuref(x[i] != y[i], "Graph can't contain loops");
```

You can also use C-style placeholders like

```cpp
ensuref(s.length() % 2 == 0,
        "String 's' should have even length, but s.length()=%d",
        int(s.length()));
```

It has a simplified version `ensure()`. We can directly use `ensure(x > y)` without adding description content (adding description is also not supported). If the condition is not satisfied, the error will be `FAIL Condition failed: "x > y"`. In many cases, errors without additional description are not friendly, so we usually use `ensuref()` with description content instead of `ensure()`.

???+ warning "Warning"
    Note the difference between global and member `ensuref/ensure()`
    
    Global functions `::ensuref/ensure()` are mainly used in generators and validators. If the check fails, they will return `_fail`.
    
    Member functions `InStream::ensuref/ensure()` are generally used to check whether the participant's and reference program's outputs are valid. When `InStream` is `ouf`, return `_wa`; when it is `inf` (input data is generally not checked in checker, this should be done in validator) or `ans`, return `_fail`. See [Checker - Writing readAns function](./checker.md#good-implementation) for details.

**This article is mainly translated and compiled from [Testlib - Codeforces](https://codeforces.com/testlib). The GitHub repository for `testlib.h` is [MikeMirzayanov/testlib](https://github.com/MikeMirzayanov/testlib).**

[^1]: [issue link](https://github.com/MikeMirzayanov/testlib/issues/115#issuecomment-863414940)