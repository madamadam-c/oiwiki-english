Checker, also known as [Special Judge](../special-judge.md), is used to verify whether answers are valid. Using Testlib allows us to skip checking many things, making writing much simpler.

Checker reads the input filename, participant output filename, and standard output filename from command line arguments, determines whether the participant's output is correct, and returns a predefined result:

Please read [General](./general.md) before continuing.

## Simple Example

???+ note "Problem"
    Given two integers $a,b$ ($-1000 \le a,b \le 1000$), output their sum.

This problem obviously doesn't need a checker, but if you really want to write one:

```cpp
#include "testlib.h"

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  int pans = ouf.readInt(-2000, 2000, "sum of numbers");

  // Assume the standard output is correct, don't check its range
  // Later we will see this is not reasonable
  int jans = ans.readInt();

  if (pans == jans)
    quitf(_ok, "The sum is correct.");
  else
    quitf(_wa, "The sum is wrong: expected = %d, found = %d", jans, pans);
}
```

## Writing readAns Function

Suppose you have a problem with many input and output numbers, like: given a DAG, find the longest path from $s$ to $t$ and output the path (there may be multiple, output any one).

Below is an example of a **bad** checker.

### Bad Implementation

```cpp
#include "testlib.h"
//
#include <map>
#include <vector>
using namespace std;

map<pair<int, int>, int> edges;

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);
  int n = inf.readInt();  // No need for readSpace() or readEoln()
  int m = inf.readInt();  // Because we don't need to check standard input validity in checker
                          // (there's validator)
  for (int i = 0; i < m; i++) {
    int a = inf.readInt();
    int b = inf.readInt();
    int w = inf.readInt();
    edges[make_pair(a, b)] = edges[make_pair(b, a)] = w;
  }
  int s = inf.readInt();
  int t = inf.readInt();

  // Read standard output
  int jvalue = 0;
  vector<int> jpath;
  int jlen = ans.readInt();
  for (int i = 0; i < jlen; i++) {
    jpath.push_back(ans.readInt());
  }
  for (int i = 0; i < jlen - 1; i++) {
    jvalue += edges[make_pair(jpath[i], jpath[i + 1])];
  }

  // Read participant output
  int pvalue = 0;
  vector<int> ppath;
  vector<bool> used(n);
  int plen = ouf.readInt(2, n, "number of vertices");  // Must contain at least s and t
  for (int i = 0; i < plen; i++) {
    int v = ouf.readInt(1, n, format("path[%d]", i + 1).c_str());
    if (used[v - 1])  // Check if each edge is used only once
      quitf(_wa, "vertex %d was used twice", v);
    used[v - 1] = true;
    ppath.push_back(v);
  }
  // Check start and end points
  if (ppath.front() != s)
    quitf(_wa, "path doesn't start in s: expected s = %d, found %d", s,
          ppath.front());
  if (ppath.back() != t)
    quitf(_wa, "path doesn't finish in t: expected t = %d, found %d", t,
          ppath.back());
  // Check if there's an edge between adjacent vertices
  for (int i = 0; i < plen - 1; i++) {
    if (edges.find(make_pair(ppath[i], ppath[i + 1])) == edges.end())
      quitf(_wa, "there is no edge (%d, %d) in the graph", ppath[i],
            ppath[i + 1]);
    pvalue += edges[make_pair(ppath[i], ppath[i + 1])];
  }

  if (jvalue != pvalue)
    quitf(_wa, "jury has answer %d, participant has answer %d", jvalue, pvalue);
  else
    quitf(_ok, "answer = %d", pvalue);
}
```

This checker has two main problems:

1.  It assumes the standard output is correct. If the participant's output is better than the standard output, it will be judged as WA, which is not ideal. Also, if the standard output is invalid, it will also produce WA. For both cases, the correct action is to return the Fail state.
2.  The code for reading standard output and participant output is duplicated. In this problem, writing the read logic twice is not a big deal, only needing a `for` loop; but if a problem has very complex output, it will cause your checker structure to be messy. Duplicate code greatly reduces maintainability, making it difficult when debugging or modifying the format.

The way to read standard output and participant output is actually exactly the same, which is why we usually write a read function that takes a stream as a parameter.

### Good Implementation

```cpp
// clang-format off

#include "testlib.h"
#include <map>
#include <vector>
using namespace std;

map<pair<int, int>, int> edges;
int n, m, s, t;

// This function accepts a stream, reads from it
// Checks path validity and returns the path length
// When stream is ans, all stream.quitf(_wa, ...)
// and failed readXxx() will return _fail instead of _wa
// That is, if output is invalid, for participant output stream it will return _wa,
// for standard output stream it will return _fail
int readAns(InStream& stream) {
  // Read output
  int value = 0;
  vector<int> path;
  vector<bool> used(n);
  int len = stream.readInt(2, n, "number of vertices");
  for (int i = 0; i < len; i++) {
    int v = stream.readInt(1, n, format("path[%d]", i + 1).c_str());
    if (used[v - 1]) {
      stream.quitf(_wa, "vertex %d was used twice", v);
    }
    used[v - 1] = true;
    path.push_back(v);
  }
  if (path.front() != s)
    stream.quitf(_wa, "path doesn't start in s: expected s = %d, found %d", s,
                 path.front());
  if (path.back() != t)
    stream.quitf(_wa, "path doesn't finish in t: expected t = %d, found %d", t,
                 path.back());
  for (int i = 0; i < len - 1; i++) {
    if (edges.find(make_pair(path[i], path[i + 1])) == edges.end())
      stream.quitf(_wa, "there is no edge (%d, %d) in the graph", path[i],
                   path[i + 1]);
    value += edges[make_pair(path[i], path[i + 1])];
  }
  return value;
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);
  n = inf.readInt();
  m = inf.readInt();
  for (int i = 0; i < m; i++) {
    int a = inf.readInt();
    int b = inf.readInt();
    int w = inf.readInt();
    edges[make_pair(a, b)] = edges[make_pair(b, a)] = w;
  }
  int s = inf.readInt();
  int t = inf.readInt();
  
  int jans = readAns(ans);
  int pans = readAns(ouf);
  if (jans > pans)
    quitf(_wa, "jury has the better answer: jans = %d, pans = %d\n", jans,
          pans);
  else if (jans == pans)
    quitf(_ok, "answer = %d\n", pans);
  else  // (jans < pans)
    quitf(_fail, ":( participant has the better answer: jans = %d, pans = %d\n",
          jans, pans);
}
```

Note that with this approach, we also check whether the standard output is valid. Writing the checker this way makes the program shorter and easier to understand and debug. This approach also applies to problems that output YES (and some solution), or NO.

???+ note "Note"
    Some checks can be implemented more concisely using `InStream::ensure/ensuref()`. For example, lines 23-25 above can also be equivalently written as:
    
    ```cpp
    stream.ensuref(!used[v - 1], "vertex %d was used twice", v);
    ```

???+ warning "Warning"
    Please avoid calling **global** functions `::ensure/ensuref()` in `readAns`, as this will cause `_fail` to be returned instead of `_wa` for some participant outputs that should be judged as WA, causing errors.

## Suggestions and Common Mistakes

-   Write a `readAns` function; it can really make your checker great.

-   Always specify ranges when reading participant output. If some variable forgets to specify a range and is used in some parameters, your checker may judge incorrectly or cause RE, etc.

    -   Bad example

    ```cpp
    // ....
    int k = ouf.readInt();
    vector<int> lst;
    for (int i = 0; i < k; i++)  // k = 0 and k = -5 have the same effect here (loop body won't execute)
      lst.push_back(ouf.readInt());
    // But we don't want to accept a list with length -5, do we?
    // ....
    int pos = ouf.readInt();
    int x = A[pos];
    // Someone might output -42, 2147483456 or some other illegal numbers causing checker RE
    ```

    -   Good example

    ```cpp
    // ....
    int k = ouf.readInt(0, n);  // Illegal length will immediately be judged WA, won't continue check and cause RE
    vector<int> lst;
    for (int i = 0; i < k; i++) lst.push_back(ouf.readInt());
    // ....
    int pos = ouf.readInt(0, (int)A.size() - 1);  // Prevent out of range
    int x = A[pos];
    // ....
    ```

-   Use item aliases.

-   Unlike validator, checker doesn't need to specifically check for non-empty characters. For example, for a checker that compares integers in order, we only need to check if the participant's output integers match the answer integers. Whether the participant outputs one integer per line or all integers on one line or other format issues, our checker doesn't need to care about.

## Usage

Usually we don't need to run it locally; the evaluation system/OJ will handle everything. But if needed, run it from the command line in the following format:

```bash
./checker <input-file> <output-file> <answer-file> [<report-file> [<-appes>]]
```

## Some Pre-built Checkers

Often our checker's work is simple (like checking if the output integer is correct, or if the output floating-point number meets precision requirements). [Testlib](https://github.com/MikeMirzayanov/testlib/tree/master/checkers) has already provided implementations of these checkers for us, which we can use directly.

Some commonly used checkers are:

-   ncmp: Compares 64-bit integers in order.
-   rcmp4: Compares floating-point numbers in order, maximum acceptable error (absolute error or relative error) does not exceed $10^{-4}$ (there are also rcmp6, rcmp9, etc. for different precision requirements; usage is similar to rcmp4).
-   wcmp: Compares strings in order (without spaces, newlines and other whitespace characters).
-   yesno: Compares YES and NO, case-insensitive.

    **This article is mainly translated from [Checkers with testlib.h - Codeforces](https://codeforces.com/blog/entry/18431). The GitHub repository for `testlib.h` is [MikeMirzayanov/testlib](https://github.com/MikeMirzayanov/testlib).**