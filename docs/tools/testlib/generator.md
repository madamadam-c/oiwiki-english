Generator, i.e., data generator. When the data is large and manually creating it would be exhausting, we need it to help us automatically generate data.

## Simple Example

Generate two integers in the range $[1,n]$:

```cpp
// clang-format off

#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  int n = atoi(argv[1]);
  cout << rnd.next(1, n) << " ";
  cout << rnd.next(1, n) << endl;
}
```

## Why Use Testlib?

Some say writing a generator doesn't need Testlib; it's not useful here. Actually, this is incorrect. A good generator should satisfy this: **for the same input, it produces the same output in any environment**. Writing a generator inevitably involves generating random values. The `rand()` we normally use or C++11's `mt19937/uniform_int_distribution` may produce different outputs when the operating system is different, compiled with different compilers, run at different times, etc. (For the very commonly used `srand(time(nullptr))`, this is obvious), and this brings uncertainty to data generation.

Note that once Testlib is used, you can no longer use `srand()`, `rand()`, or other random number functions from the standard library, otherwise compilation will fail. Therefore, **please make sure all random-related functions use Testlib instead of the standard library.**

The random value generation functions in Testlib guarantee the same output for the same call, regardless of the generator itself or the platform. Additionally, it provides great convenience for generating random values with various requirements. For example, `rnd.next("[a-z]{1,10}")` will generate a string with length in $[1,10]$, each character being `a` to `z`. Convenient, right?

## What Can Testlib Do?

Before everything, first execute `registerGen(argc, argv, 1)` to initialize Testlib (where `1` is the generator version, usually keep it unchanged). Then we can use the `rnd` object to generate random values. The random seed comes from the hash of command line arguments. For a generator `g.cpp`, `g 100` (Unix-like) and `g.exe "100"` (Windows) will have the same output, while `g 100 0` will be different from them.

The type of `rnd` object is `random_t`. You can create a new random value generation object, but usually you don't need to.

This object has many useful member functions. Here are some examples:

| Call                                           | Meaning                                                                                                                                                                                                                                                      |
| -------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `rnd.next(4)`                                | Generate an integer in $[0,4)$ with equal probability                                                                                                                                                                                                                                  |
| `rnd.next(4, 100)`                           | Generate an integer in $[4,100]$ with equal probability                                                                                                                                                                                                                                |
| `rnd.next(10.0)`                             | Generate a floating-point number in $[0,10.0)$ with equal probability                                                                                                                                                                                                                              |
| <code>rnd.next("one \| two \| three")</code> | Return one of `one`, `two`, `three` with equal probability                                                                                                                                                                                                                       |
| `rnd.wnext(4, t)`                            | `wnext()` is a function that generates non-uniform distribution (with shifted expectation)[^note1], $t$ represents the number of times `next()` is called, and takes the maximum of the generated values. For example, `rnd.wnext(3, 1)` is equivalent to `max({rnd.next(3), rnd.next(3)})`; `rnd.wnext(4, 2)` is equivalent to `max({rnd.next(4), rnd.next(4), rnd.next(4)})`. If $t<0$, call $-t$ times and take the minimum; if $t=0`, equivalent to `next()`. |
| `rnd.any(container)`                         | Return a reference to a randomly selected element in a container with random access iterator (like `std::vector` and `std::string`) with equal probability                                                                                                                                                                                           |

Note: Formal definition of `rnd.wnext(i,t)`:

$$
\operatorname{wnext}(i,t)=
\begin{cases}
\operatorname{next}(i) & t=0 \\
\max(\operatorname{next}(i),\operatorname{wnext}(i,t-1)) & t>0 \\
\min(\operatorname{next}(i),\operatorname{wnext}(i,t+1)) & t<0
\end{cases}
$$

Also, don't use `std::random_shuffle()`. Use `shuffle()` from Testlib instead; it also accepts a pair of iterators. It uses `rnd` to shuffle the sequence, satisfying the "good generator" requirement above.

## Example: Generate a Tree

Below is the main code to generate a tree. It accepts two parameters - the number of vertices and the spread degree. For example, when $n=10,t=1000$, it may generate a path; when $n=10,t=-1000$, it may generate a star.

```cpp
#define forn(i, n) for (int i = 0; i < int(n); i++)

registerGen(argc, argv, 1);

int n = atoi(argv[1]);
int t = atoi(argv[2]);

vector<int> p(n);

/* Set parent for nodes 1..n-1 */
forn(i, n) if (i > 0) p[i] = rnd.wnext(i, t);

printf("%d\n", n);

/* Shuffle nodes 1..n-1 */
vector<int> perm(n);
forn(i, n) perm[i] = i;
shuffle(perm.begin() + 1, perm.end());

/* Add edges according to shuffled node order */
vector<pair<int, int>> edges;
for (int i = 1; i < n; i++)
  if (rnd.next(2))
    edges.push_back(make_pair(perm[i], perm[p[i]]));
  else
    edges.push_back(make_pair(perm[p[i]], perm[i]));

/* Shuffle edges */
shuffle(edges.begin(), edges.end());

for (int i = 0; i + 1 < n; i++)
  printf("%d %d\n", edges[i].first + 1, edges[i].second + 1);
```

## Generate Multiple Sets of Data at Once

Just like when writing without Testlib, redirect the output stream before each output. However, Testlib provides a helper function `startTest(test_index)` that helps you redirect the output stream to the `test_index` file.

## Some Precautions

-   Strictly follow the problem's format requirements, such as spaces and newlines. Note that there should be a newline at the end of the file.
-   For large data, prefer `printf` over `cout` for better performance. (It's not recommended to disable stream synchronization when using Testlib)
-   Don't use UB (Undefined Behavior). As in the example at the beginning of this article, if the output is written as `cout << rnd.next(1, n) << " " << rnd.next(1, n) << endl;`, the call order of `rnd.next()` is undefined.

## New Feature: Parse Command Line Arguments

Previously, we usually used code like `int n = atoi(argv[3]);`, but this is not good. Here are the reasons:

-   It is unsafe when the third command line argument doesn't exist;
-   The third command line argument may not be a valid 32-bit integer.

Now, you can write: `int n = opt<int>(3)`. At the same time, you can also use `int64_t m = opt<int64_t>(1);`, `bool t = opt<bool>(2);` and `string s = opt(4);`, etc.

Additionally, testlib also supports named arguments. If there are many parameters, `g 10 20000 a true` will be less readable than `g -n10 -m200000 -t=a -increment`.

In this case, you can now use the following code in the generator:

```cpp
int n = opt<int>("n");
long long n = opt<long long>("m");
string t = opt("t");
bool increment = opt<bool>("increment");
```

You can freely mix using arguments by index and by name.

Supported schemes for writing named arguments are:

-   `--key=value` or `-key=value`;
-   `--key value` or `-key value` - if `value` is not the start of a new argument (doesn't start with a hyphen or one/two hyphens followed by no letter);
-   `--k12345` or `-k12345` - if key `k` is a letter followed by a number;
-   `-prop` or `--prop` - enable bool property.

Here are some examples:

```text
g1 -n1
g2 --len=4 --s=oops
g3 -inc -shuffle -n=5
g4 --length 5 --total 21 -ord
```

## More Examples

Can be found at [GitHub](https://github.com/MikeMirzayanov/testlib/tree/master/generators).

**This article is mainly translated from [Генераторы на testlib.h - Codeforces](https://codeforces.com/blog/entry/18291). New feature translated from [Testlib: Opts—parsing command line options](https://codeforces.com/blog/entry/72702). The GitHub repository for `testlib.h` is [MikeMirzayanov/testlib](https://github.com/MikeMirzayanov/testlib).**

[^note1]: Actually, when `i` is a floating-point number, `rnd.wnext(i, t)` follows a [Beta distribution](https://en.wikipedia.org/wiki/Beta_distribution) on $[0,i)$: when $t>0$, it follows $i\cdot \mathrm{Beta}(t+1,1)$; when $t<0$, it follows $i\cdot \mathrm{Beta}(1,t+1)$.