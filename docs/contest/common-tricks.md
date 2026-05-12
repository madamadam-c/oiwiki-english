author: H-J-Granger, Ir1d, ChungZH, Marcythm, StudyingFather, billchenchina, Suyun514, Psycho7, greyqz, Xeonacid, partychicken

This page mainly lists some tips and tricks used in competitions.

## Exploiting Locality

Locality refers to the tendency of programs to reference data items that are near other recently referenced data items, or recently referenced data items themselves. Locality is divided into temporal locality and spatial locality.

For details, see [Loop Unroll](../lang/optimizations.md#循环展开-loop-unroll), [Code Layout Optimizations](../lang/optimizations.md#代码布局优化-code-layout-optimizations), etc.

## Loop Macro Definitions

The following code can be simplified using macro definitions:

```cpp
for (int i = 0; i < N; i++) {
  // loop body omitted
}

// Simplified using macros
#define f(x, y, z) for (int x = (y), __ = (z); x < __; ++x)

// Now loop code can be simplified to `f(i, 0, N)`. For example:
// a is a STL container
f(i, 0, a.size()) { ... }
```

Another useful macro definition:

```cpp
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
```

## Making Good Use of Namespaces

Using namespaces can improve program readability and make debugging easier.

??? note "Example Problem: NOI 2018 Dragon Slayer"
```cpp
// NOI 2018 Dragon Slayer 40-point partial score code
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
long long n, m, a[100005], p[100005], aw[100005], atk[100005];

namespace one_game {
// Variables can also be declared inside namespaces
void solve() {
  for (int y = 0;; y++)
    if ((a[1] + p[1] * y) % atk[1] == 0) {
      cout << (a[1] + p[1] * y) / atk[1] << endl;
      return;
    }
}
} // namespace one_game

namespace p_1 {
void solve() {
  if (atk[1] == 1) { // solve 1-2
    sort(a + 1, a + n + 1);
    cout << a[n] << endl;
    return;
  } else if (m == 1) { // solve 3-4
    long long k = atk[1], kt = ceil(a[1] * 1.0 / k);
    for (int i = 2; i <= n; i++)
      k = aw[i - 1], kt = max(kt, (long long)ceil(a[i] * 1.0 / k));
    cout << k << endl;
  }
}
} // namespace p_1

int main() {
  int T;
  cin >> T;
  while (T--) {
    memset(a, 0, sizeof(a));
    memset(p, 0, sizeof(p));
    memset(aw, 0, sizeof(aw));
    memset(atk, 0, sizeof(atk));
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int i = 1; i <= n; i++) cin >> aw[i];
    for (int i = 1; i <= m; i++) cin >> atk[i];
    if (n == 1 && m == 1)
      one_game::solve(); // solve 8-13
    else if (p[1] == 1)
      p_1::solve(); // solve 1-4 or 14-15
    else
      cout << -1 << endl;
  }
  return 0;
}
```

## Using Macros for Debugging

When testing locally, programmers often add some debugging statements. However, when submitting to an OJ, these debugging statements must be removed to prevent their output from affecting the judge's evaluation of the program's output, which can be time-consuming. In this case, you can save time by defining macros. The general program framework is as follows:

```cpp
#define DEBUG
#ifdef DEBUG
// do something when DEBUG is defined
#endif
// or
#ifndef DEBUG
// do something when DEBUG isn't defined
#endif
```

`#ifdef` checks whether the corresponding identifier defined by `#define` exists in the program, and if it is defined, the subsequent statements will be executed. `#ifndef` executes the subsequent statements when the corresponding identifier is not defined.

This way, you only need to write debugging code inside `#ifdef DEBUG` and the actual submission code inside `#ifndef DEBUG`, making local testing convenient. When submitting the program, simply comment out the `#define DEBUG` line. You can also avoid defining the identifier in the program itself and instead define the `DEBUG` identifier at compile time using the `-DDEBUG` compiler option. This way, you don't need to modify the program when submitting.

Many OJs enable the `-DONLINE_JUDGE` compiler option. Making good use of this feature can save a lot of time.

## Diff Testing

Diff testing is a method for verification or debugging, which checks the correctness of a program by comparing the output of two programs. You can compare your program's output with another program's output to determine whether your program is correct.

The diff testing process needs to be repeated multiple times, so batch processing is needed to automate it.

Specifically, diff testing requires a [data generator](../tools/testlib/generator.md) and two programs whose output results are to be compared.

Each time the data generator runs, it writes the generated data to an input file. The two programs read the data through redirection and write their output to specified files. Finally, the `fc` command on Windows (or the `diff` command on Linux) is used to compare the files and check the program's correctness. If an error is found, you can directly use the just-generated data for debugging.

The general framework for a diff testing program is as follows:

```cpp
#include <cstdio>
#include <cstdlib>

int main() {
  // For Windows
  // No file I/O during diff testing
  // Of course, this program can also be rewritten as a batch script
  while (true) {
    system("gen > test.in"); // Data generator writes generated data to input file
    system("test1.exe < test.in > a.out"); // Get program 1 output
    system("test2.exe < test.in > b.out"); // Get program 2 output
    if (system("fc a.out b.out")) {
      // This line compares the outputs
      // fc returns 0 when outputs match, otherwise there is a difference
      system("pause"); // Convenient for viewing differences
      return 0;
      // The input data is already stored in test.in, can be used directly for debugging
    }
  }
}
```

## Memory Pool

When dynamically allocating memory, frequent use of `new`/`malloc` consumes a significant amount of time and space, and can even generate a large number of memory fragments that degrade program performance, potentially causing an otherwise correct program to TLE/MLE.

In this case, the "memory pool" technique is needed: before actually using the memory, allocate a certain amount of memory in advance as a reserve. When dynamic allocation is needed, simply allocate a block from the reserved memory.

In most OI problems, you can pre-calculate the maximum memory needed and allocate it all at once.

Example:

```cpp
// Dynamically allocate a 32-bit signed integer array:
int* newarr(int sz) {
  static int pool[MAXN], *allocp = pool;
  return allocp += sz, allocp - sz;
}

// Segment tree dynamic node creation code:
Node* newnode() {
  static Node pool[MAXN << 1], *allocp = pool - 1;
  return ++allocp;
}
```

## References

[Luogu Daily #86](https://studyingfather.blog.luogu.org/some-coding-tips-for-oiers)

*Introduction to Algorithmic Competitions: Exercises and Solutions*
