author: ouuan, Henry-ZHR, StudyingFather, ChungZH, xyf007, Cryflmind, oierlinch, xk2013awa

## Preparation Before Setting Problems

### Have a Certain Level of Skill

On the one hand, when setting problems alone, it is hard to create problems whose difficulty exceeds your own level. A certain level of OI skill helps you come up with higher-quality ideas and excellent solutions. On the other hand, OI skill to some extent reflects OI experience; contestants who have seen more problems will also have their own understanding of what makes a "good problem".

### Maintain a Serious and Responsible Attitude

Problems are made for others to solve. Rather than showing yourself off, problemsetting is more about serving others. Algorithm contests are contests among contestants, not battles between problem setters and solvers. Therefore, the goal of problemsetting should not be to stump contestants (of course, properly preventing AK and ensuring good differentiation are also very important), but to let contestants gain something from the contest. It is very important to spend enough time and effort learning how to set problems and to set them seriously and responsibly.

### Be Prepared to Spend a Lot of Time

If you want to set problems seriously, you will inevitably spend a lot of time. Without mental preparation, the contest may be prepared in a rush and fail to meet quality standards, or you may later regret not having spent that time on studying. But problemsetting can also bring many wonderful memories. If you are truly interested in problemsetting and are fully mentally prepared, the rewards from problemsetting can make up for the time spent.

### Read This Article Carefully

This article introduces the whole problemsetting process from two aspects: how to set problems and how to set good problems. For anyone who wants to set problems, reading this article carefully will certainly be very rewarding.

## Problem Content

When setting a problem, the idea, that is, the essential content of the problem, is the soul of the problem and also the first step in problemsetting.

### Sources of Ideas

1.  Inspiration from existing problems (but do not copy them or strengthen them meaninglessly, such as moving a sequence problem onto a cactus).
2.  Inspiration from knowledge points you have learned (but do not forcibly piece together unrelated knowledge points).
3.  Inspiration from life/games (but be careful not to turn a game into a big simulation problem).
4.  For no clear reason, you just think of a problem.

### What Kinds of Ideas Are Bad

#### About Duplicate Problems

Duplicate problems can roughly be divided into three types: completely identical, almost identical, and identical in solution.

-   Completely identical: the AC code for one problem can AC the other problem.
-   Almost identical: modifying the AC code for one problem into the AC code for the other can be done by someone who does not know the problem.
-   Identical in solution: the core idea and solution are identical, but there are differences in code implementation and less critical details.

These three types of duplicate problems form an inclusion relationship from bottom to top.

The following situations should not occur:

1.  Setting a duplicate problem while knowing that there is an "almost identical" original problem.
2.  Setting an "almost identical" duplicate problem because you did not use a search engine and therefore did not know the original existed.
3.  Setting a duplicate problem when an "identical in solution" original problem is widely known (for example, an original NOIP or NOI problem).
4.  Having an "identical in solution" original problem appear as a non-giveaway problem in a selection-oriented exam.

The following situations are best avoided:

1.  Setting a duplicate problem while knowing that there is an original problem that is at least "identical in solution".
2.  Setting an "identical in solution" duplicate problem because you did not use a search engine and therefore did not know the original existed.
3.  Setting an "almost identical" duplicate problem under any circumstances.

Exceptions where the requirements may be relaxed:

1.  In-school mock contests.
2.  Mock contests intended for topic-based training.
3.  Contests with low difficulty, or problems positioned as giveaways.

#### About Malignant Problems

"Malignant problem" is a very vague and subjective concept. Here we only quote some previous discussions on it and add some of our own understanding. This topic is very open, and everyone is welcome to express their views.

> A good problem should not be two problems stitched together. A good problem has its own idea, and it should highlight that idea without excessive packaging.
>
> A good problem should be novel. A truly good problem should be a good problem that inspires people to think of new good problems.
>
> --[vfk《UOJ 精神之源流》][1]

Example: [「XR-1」柯南家族](https://www.luogu.com.cn/problem/P5346). The two halves of the solution are completely disconnected: the first half is [「模板」树上后缀排序](https://www.luogu.com.cn/problem/P5353), and the second half is a classic tree problem. Even if the weights of the tree nodes are input arbitrarily, the second part can still be solved; the two parts are unrelated.

> One type of OI problem is mainly mathematical. Both the statement and the solution have the characteristics of a math problem, and the solution contains no algorithm-related knowledge points. Such OI problems are collectively called pure mathematics problems.
>
> --[王天懿《论偏题的危害》][2]

Classic example: [NOIP2017 小凯的疑惑](https://uoj.ac/problem/329)

The difference between math problems in OI and other math problems, and also a characteristic that reflects the essence of OI, is that math problems in OI usually focus not on **what** the answer is, but on how to **speed up** the computation of the answer. If the focus of a problem is "how to calculate" rather than "how to calculate quickly", such a math problem is generally not suitable for OI.

> Some off-topic problems involve university physics, making contestants feel at a loss when facing physics knowledge points they have never encountered and creating a knowledge barrier.
>
> --[王天懿《论偏题的危害》][2]

Classic example: [「清华集训 2015」多边形下海](https://uoj.ac/problem/159)

Not only physics: OI problems should not involve too much knowledge from other disciplines. If they do, detailed explanations should be provided, and knowledge from other disciplines should not become a major obstacle to solving the problem.

> A good problem, regardless of difficulty, should have its own thinking difficulty and require contestants to think and discover some properties.
>
> A good problem's code may be long, but it must not become long through forced nesting or added conditions. It should be naturally long, making people feel that the code for this problem ought to be this long.
>
> --[王天懿《论偏题的危害》][2]

Classic examples: [「SDOI2010」猪国杀](https://loj.ac/problem/2885), [「集训队互测 2015」未来程序·改](https://uoj.ac/problem/98)

In ordinary OI contests, thinking difficulty should account for the main part. Of course, engineering problems such as those on THUWC/THUSC Day 2+ also have their reason to exist. After all, besides assessing contestants' algorithm design ability, the purpose of the experience camp also includes connecting with university study through engineering code and documentation learning ability. But in ordinary OI contests, what should be assessed more is still algorithm design and thinking ability.

## Statement

### Use LaTeX to Write Formulas

There are many LaTeX tutorials online, such as:

-   [Introduction to LaTeX](../tools/latex.md#图表)
-   [LaTeX 数学公式大全](https://www.luogu.com.cn/blog/IowaBattleship/latex-gong-shi-tai-quan)
-   [LaTeX 各种命令，符号](https://blog.csdn.net/anxiaoxi45/article/details/39449445)

When using it, please pay attention to the [format requirements for LaTeX formulas](../intro/format.md).

### Problem Background

The problem background should preferably be as concise as possible. When the background is long, it should be separated from the problem description.

It is absolutely necessary to avoid the problem background seriously affecting understanding of the problem meaning.

When necessary, you can provide two versions: a problem description combined with the background and a concise problem description.

### Problem Description

In short, the problem description needs to be **clear and easy to understand**.

Every definition in the statement that may not be understood should be explained; undefined concepts should not appear out of nowhere. For example, in [CF1172D Nauuo and Portals](https://codeforces.com/problemset/problem/1172/D), you must explain in the statement what a "portal" is.

Every concept involved in the statement should be described using a single term. For example, do not sometimes say "fee" and sometimes say "cost".

Do not use words with meanings different from their original or common meanings without explanation. For example, do not use "path" to refer to an edge without explanation.

You need to ensure that your statement does not contradict itself. For example, in [CF1173A Nauuo and Votes](https://codeforces.com/problemset/problem/1173/A), "?" is not treated as a kind of "result" because "?" means "there are more than one possible results".

You need to ensure that your statement cannot be misinterpreted in a self-consistent way, even if that interpretation is counterintuitive and no one would normally think of it. For example, in [CF1172D Nauuo and Portals](https://codeforces.com/problemset/problem/1172/D), the reason for laboriously defining "walk into" and distinguishing it from "teleport" is to prevent this interpretation: through a portal one can reach another portal, and upon reaching a portal one teleports, so one bounces back and forth repeatedly.

Reading the problem description in order should allow one to understand every sentence and understand the task and requirements of the problem. At least any confusion should be explained in the immediately following paragraph, rather than only several paragraphs later, or only after reading the input/output format, or even requiring the samples to guess the meaning. For example, in [「GuOJ Round #1」琪露诺的冰雪宴会](https://github.com/OI-wiki/problemset/blob/master/contest/online/GuOJ/OI%20Archive%20-%20GuOJ1171.pdf), the problem's goal, "the maximum amount of water that Misty Lake can finally receive", first appears only in the output format. Together with the misleading sentence "Reimu can of course quickly calculate the total cost of clearing all streams", this more easily causes people to misread the problem. This is undesirable; the goal of the problem should be stated in the problem description. (In this example there is also the problem that the background seriously affects understanding of the problem meaning.) The same mistake also appears in [CF1423(4)N Bubblesquare Tokens](https://codeforces.com/problemset/problem/1423/N), where the problem's goal, "friend pairs and number of tokens each of them gets on behalf of their friendship", first appears only in the output format.

### Input and Output Format

The input and output format only needs to be clear and **complete**; there are no rigid requirements. Personally, I suggest referring to CF problems when writing input and output formats. For details, see [Guidelines for CF problem setters][3].

For contestants' convenience, the input and output format should preferably explain the specific meaning of each variable, unless the meaning of a variable is too long to explain in one sentence (in which case you can say "see the problem description for its meaning").

It is especially important that, if the output contains decimals, you should try to use [SPJ](#special-judge) to restrict the allowed error, rather than requiring "keep x decimal places".

"Keep x decimal places" may impose infinite precision requirements. For example, if the requirement is to keep three decimal places and the actual answer is $0.0015$, then any error of any size that makes the computed answer less than $0.0015$ will cause a wrong output, even if the computed answer is $0.00149999\cdots$.

If SPJ cannot be used, make sure the precision requirement is finite. For example: please output the answer rounded to three digits after the decimal point. Let the standard answer be $ans$; the data guarantees that for any $x$ satisfying $\frac{|x-ans|}{\max(1,ans)}<10^{-9}$, the rounded result is the same as the rounded result of $ans$.

Some sentences for reference:

```latex
The first line of input contains three positive integers $n$, $m$, $k$ ($1\le n,m\le 2\cdot 10^5$, $1\le k\le 100$) -- $n$ denotes the length of the sequence, $m$ denotes the number of operations, and the meaning of $k$ is described in the problem statement.
```

```latex
The second line of input contains $n$ non-negative integers $a_1,a_2,\ldots,a_n$ ($1\le a_i\le 10^9$) -- the sequence given in the problem.
```

```latex
The $i$-th of the next $m$ lines contains two positive integers $l_i$ and $r_i$ ($1\le l_i\le r_i\le n$), indicating that the $i$-th operation is performed on the interval $[l_i,r_i]$.
```

```latex
Each of the next $n-1$ lines contains two positive integers $u$ and $v$ ($1\le u,v\le n$), indicating that there is an edge between $u$ and $v$.

It is guaranteed that the given edges form a tree.
```

```latex
The only line of input contains a non-empty string consisting of lowercase English letters, whose length does not exceed $10^6$.
```

```latex
The second line of input contains a real number $x$ with at most three digits after the decimal point ($-10^6\le x\le 10^6$); its meaning is described in the problem statement.
```

```latex
Output a real number. Your output is considered correct if the absolute or relative error between your output and the standard answer is less than $10^{-6}$.
```

```latex
The second line of output contains $n$ positive integers, representing one plan you construct -- the $i$-th number denotes the index of the $i$-th card you play.

If there are multiple valid answers, you may output any one of them.
```

???+ note "Generating input data with a random number generator inside contestant code"
    Some problems have very large input data. To prevent reading input from taking too long, they require contestants to generate the data inside their code using a given data generator, instead of reading data from standard input or files.
    
    This approach should be considered carefully, because it has many disadvantages:
    
    -   It may introduce data randomness that the intended solution does not need, or make constructing data difficult
    -   It may increase the difficulty of understanding the input format
    -   If the random number generator is not well encapsulated, understanding how to use the data generator itself may be difficult
    -   If contestants do not use the language recommended by the problem setter, they may need to write a data generator themselves
    
    This approach is generally used to prevent reading data from taking too long. Therefore, one possible alternative is to provide a sufficiently performant [input/output optimization](./io.md) template, so as to keep everyone's input-reading time as consistent as possible; in this way, even if reading takes a long time, it will not affect the time differences between contestants. Another solution is to package the problem as a function-call-style (rather than IO-style) interactive problem. Even if there is no interaction during the algorithm, an interactive problem can still unify input-reading time. IOI adopts the approach where all problems are interactive problems. However, both approaches restrict the languages contestants can use and require the problem setter to manually support every language allowed for contestants.
    
    Returning to the root of the issue, you can also consider whether overly large input data is necessary, whether smaller input data can achieve the goal, and whether it is necessary to hack solutions whose complexity is only slightly worse than the intended solution.

### Data Constraints

According to CF requirements, data constraints should be written in the input format, but in China, data constraints are often written at the end of the problem.

The most common mistake in data constraints is incompleteness. Every number and every string in the input should have a clear definition. The input/output format examples above include some correct ways to write data constraints.

Common omissions in data constraints:

1.  The word "integer".
2.  The statement only says "integer" and not "positive integer", while the data constraints give only an upper bound and no lower bound.
3.  The character set of a string is not specified.
4.  The number of digits after the decimal point for a real number is not specified.
5.  Some variables have no constraints.

You need to ensure that the standard solution can pass **any set of data** satisfying the constraints stated in the problem statement.

???+ note "About 'the data is guaranteed to be randomly generated'"
    Some problems "guarantee that the data is randomly generated". In many cases, such a restriction is not the optimal solution, because "randomly generated" does not clearly define the constraints on the data and makes it difficult to determine the exact data range or provide hack data.
    
    Generally speaking, "the data is guaranteed to be randomly generated" can be replaced by the data properties needed by the solution. For example, a randomly generated tree can often be replaced by a restriction on the tree height.
    
    If you must guarantee that the data is randomly generated, you should specify the exact random generation operation. For example, when generating a tree, say whether the parent node is chosen randomly or a Prüfer sequence is generated randomly.
    
    Note that nondeterministic algorithms and algorithms relying on data randomness are different. The former can obtain the correct solution with high probability for any data, while the latter can obtain the correct solution for most data but cannot obtain the correct solution for some specific data.

### Samples

Samples should have a certain strength and be able to catch some simple mistakes. People who misread the problem should be able to discover their misunderstanding through the samples.

For problems with multiple operations, every operation should appear in the samples.

For problems with multiple possible outputs (such as [CF1173A Nauuo and Votes](https://codeforces.com/problemset/problem/1173/A)), every output should appear in the samples. Exception: problems where having no solution is actually impossible but the statement asks contestants to determine whether a solution exists.

### Sample Explanation

The more complex and harder to understand the problem description is, the more detailed the sample explanation should be.

The simpler the problem difficulty is, the more detailed the sample explanation should be.

Detailed sample explanations may include images.

Large samples may omit sample explanations.

To accommodate people with color vision deficiency, colors should preferably not be necessary for understanding sample explanations. Color images may be used to beautify sample explanations, but if colors must be used to convey necessary information, it is best not to use red-yellow or red-green together.

## Time Limit, Memory Limit, and Partial Scores

The purpose of time and memory limits is to block solutions with incorrect complexity. (Of course, they also prevent judging from taking too long; for example, interactive problems that only limit the number of interactions but do not limit time complexity also have time limits.)

Therefore, in principle, the time limit should be chosen as large as possible while not allowing incorrect solutions to pass.

Generally, the time limit should satisfy the following requirements:

1.  It should be at least twice the running time of std in the worst case.
2.  If the contest allows Java, Java should be able to pass.
3.  It should not allow incorrect solutions to pass (unless you really cannot block them, or intentionally want to let some wrong solution pass).

To better allow solutions with large constants while blocking wrong solutions, one can generally increase both the data range and the time limit. But note that sometimes the intended solution (due to mysterious issues such as cache behavior) may have a huge constant increase when the data range grows. In this case, increasing the data range may not increase the running-time gap between the intended solution and wrong solutions.

In contest systems with partial scores, you can also set gradient data and data with slightly smaller ranges, so that better wrong solutions and intended solutions with large constants cannot pass fully while still obtaining relatively high partial scores.

Note that when the data range is less than $5\cdot 10^5$, you should consider whether it can be passed using [instruction sets](https://ouuan.github.io/post/n方过百万-暴力碾标算——指令集优化的基础使用).

In general, the memory limit should be set large enough, unless the solution with better space complexity is indeed very clever and worth using the memory limit to block high-space-complexity solutions. In this case, you can consider setting partial scores with looser memory limits. It is worth noting that if you do not want to block solutions with large memory consumption, data structure problems generally need larger memory limits.

> A good problem should have its selective nature and sufficient differentiation. There should be at least 4 levels of partial scores, so beginners can get points and experts can demonstrate their strength.
>
> --vfk《UOJ 精神之源流》

Partial scores are generally divided into two types: smaller data ranges and special properties.

Smaller data ranges should generally be set in multiple levels. Even if you cannot think of a solution with a certain complexity, you can still consider assigning one level of points to that complexity. Generally speaking, to avoid constant-factor hacking, you can set one partial-score level at half of the maximum data limit.

"Gradient data" is preferably replaced by multiple levels of partial scores.

The setting of partial scores for special properties depends on the specific problem. An ideal special-property partial score should guide contestants toward thinking about the intended solution. Unlike partial scores for smaller data ranges, if you do not know a solution for a certain special property, it is best not to assign a score level to that special property. For example, the $k=1$ partial score of [「CTS2019」随机立方体](https://loj.ac/problem/3119) was criticized by many people during the editorial talk, who said this partial score hindered thinking about the intended solution.

If the scoring method of the problem differs from the default method (for example, using bundled subtask tests in a normal OI-style contest), this must be stated in the problem statement.

It is not recommended to use statements like "XX percent of the data satisfies XX", especially when the data range has multiple variables. For example, "$30\%$ of the data satisfies $n \le 1000$" and "$40\%$ of the data satisfies $m \le 100$" may describe properties of $70\%$ of the data, or may describe properties of only $40\%$ of the data. Generally speaking, subtasks or data range tables are better choices.

## Generating Data

Data generation is a necessary step in the problemsetting process and is also required for stress testing. Mastering some data generation techniques can make the data generation process easier and produce stronger data.

### Generating Random Data

#### Generating Random Numbers

Please refer to the [random functions](../misc/random.md) page.

It is especially worth reminding that when generating numbers whose value range is larger than the return value range of the random function, please **do not** use code like `rand() * rand()`, because such code generates very non-uniform random numbers.

In addition, when setting problems, it is recommended to use [testlib](../tools/testlib/generator.md) to generate data. It can ensure that the same seed generates the same random numbers on different platforms, and the seed is automatically generated according to command-line parameters.

#### Generating Random Permutations

You can use the STL function `std::shuffle`, in the form `std::shuffle(a, a + n, rng)`, where `rng` is a random number generator, such as `std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count())`.

Please **do not** use `std::random_shuffle`; it was deprecated in C++14 and removed in C++17.

#### Generating Random Intervals

Common incorrect method: randomly generate the left endpoint $l$ in $[1,n]$, then randomly generate the right endpoint $r$ in $[l, n]$. The intervals generated this way will tend to be on the right.

A more correct method (recommended): randomly generate two numbers in $[1, n]$, take the smaller one as the left endpoint and the larger one as the right endpoint.

The truly uniform random method: generate a random number $x$ in $[0, n]$. If $x = 0$, generate another random number $y$ in $[1, n]$, and the interval is $[y, y]$; otherwise, generate it using the "more correct method".

#### Generating Random Trees

A commonly used method is to randomly choose a parent for each node $i$ from $2\sim n$ in $[1,i-1]$. The tree generated this way is not uniformly random, and its expected height is $O(\log n)$.

Another random method: randomly choose the parent of $i$ from $[i\cdot low, i\cdot high]$. If $low$ and $high$ are set properly, this can generate relatively strong trees.

The truly uniform random method is to use a [Prüfer sequence](../graph/prufer.md): first generate a random Prüfer sequence, then generate the tree from the sequence. With this method, the expected height of the tree is $O(\sqrt n)$.

In addition, you can randomize a permutation to relabel nodes or shuffle the order of edges.

### Constructing Data

#### Interval-Related Problems

Common constructions: very short lengths (especially all single-point intervals), and very long lengths (especially all intervals being the entire sequence).

#### Problems Requiring Factorization

Maximize the number of prime factors with multiplicity: powers of $2$.

Maximize the number of distinct prime factors: the product of the smallest several primes.

Maximize the number of divisors: you can refer to the [A002182](http://oeis.org/A002182) sequence on OEIS.

#### Problems Requiring the Greatest Common Divisor

Make the two numbers whose greatest common divisor needs to be found adjacent terms of the [Fibonacci sequence](../math/combinatorics/fibonacci.md), which can make the Euclidean algorithm reach its worst-case time complexity.

#### Tree Problems

Common constructions:

-   Chain
-   Star
-   Complete binary tree
-   Replace every node of a complete binary tree with a chain of length $\sqrt n$
-   Attach a chain to a star
-   Attach some single nodes to a chain
-   The root of a tree of height $d$ with $d>1$ has two children: the left subtree is a chain of length $d-1$, and the right subtree is such a tree of height $d-1$.

If not in an exam room, you can also use [Tree-Generator](https://github.com/ouuan/Tree-Generator) to generate all kinds of trees.

### Batch Data Generation

The author recommends using command-line arguments + bat/sh scripts.

For example:

`gen.cpp`:

```cpp
#include "testlib.h"

using namespace std;

int n, m, k;
vector<int> p;

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int i;

  n = atoi(argv[1]);
  m = atoi(argv[2]);
  k = rnd.next(1, n);

  for (i = 1; i <= n; ++i) p.push_back(i);

  shuffle(p.begin(), p.end());
  // Use rnd.next() for shuffle

  printf("%d %d %d\n", n, m, k);
  for (i = 0; i < n; ++i) {
    printf("%d%c", p[i], " \n"[i == n - 1]);
    // Using a string as an array, with spaces in the middle and a newline at the end, is a common trick when generating data
  }

  return 0;
}
```

`gen_scripts.bat`:

```bat
gen 10 10 > 1.in
gen 1 1 > 2.in
gen 100 200 > 3.in
gen 2000 1000 > 4.in
gen 100000 100000 > 5.in
```

The advantage of this approach is that for different data, you only need to write one generator, and you can conveniently modify the parameters of a certain test point.

### Requirements for Data Generation

The data should include the minimum and maximum values of every parameter.

The data should include various corner cases.

When using subtasks, the data (including input and output) should preferably cover every range in the value domain, rather than only the maximum values of the data ranges.

To prevent special-case checks targeting special constructions from passing, you can combine different constructions in one test point, or make most of the data constructed and mix in a small amount of randomness.

The data should include all kinds of constructions, even if you do not know what wrong solution will fail on this construction. (Handle this at your discretion in contest systems that score by test point.)

Of course, if you know of a wrong solution with correctness issues that a normal person could think of and write, you should try to hack it.

It is especially worth reminding that if integer overflow is possible, you must hack solutions that overflow. In contest systems with partial scores, contestants who do not use long long should not receive the same score as brute force or even a lower score.

If there are pretests, the pretests should be as strong as possible (while being as few as possible). In other words, you need to include all known pitfalls of the problem in the pretests using as few test cases as possible.

If you want there to be a small number of FSTs rather than none, you should still ensure the strength of the pretests, because many unexpected mistakes may appear in the actual contest, causing the number of FSTs to be far higher than expected.

### Data Format

Here are some general input data format requirements, which can serve as a general reference:

> 1.  Use the newline format of the testing environment.
> 2.  The last line of the file ends with a newline character; that is, the last character of the entire file needs to be `\n`.
> 3.  There are no whitespace characters at the beginning or end of any line.
> 4.  Consecutive spaces do not exceed 1.

Data generated in a Windows environment usually uses `\r\n` as its newline format, while mainstream judging systems all run in Linux environments and use `\n` as their newline format. If Windows-format newline data is read in a Linux environment, it may cause abnormal newline handling when reading strings, which can in turn cause different program results in different environments. If output generated in a Linux environment is compared with standard output generated in a Windows environment in Linux, differences may occur due to different newline formats. To keep program behavior consistent, the newline format of all data must be converted to the newline format of the program's running environment.

Generally, data with Linux-format newlines can be generated in the following ways:

1.  Generate data directly in a Linux environment.
2.  Use the [`dos2unix`](https://dos2unix.sourceforge.io/) tool to convert input and output files. This tool is included in toolchains such as Cygwin and MinGW.
3.  Open the output file in binary mode and use the `\n` newline format.
4.  Refer to the `dos2unix.cpp` code on [this page](https://help.luogu.com.cn/manual/luogu/problem/testcase-format#附录windows-环境下造数据注意事项) and write a tool yourself.

## Special Judge

[SPJ Writing Tutorial](../tools/special-judge.md)

Problems that output a construction and problems that output floating-point numbers are two common types of problems that need SPJ. Other problems may also need SPJ depending on the situation. On CF, all problems must use a testlib-based checker. For example, when the problem requires outputting several integers, use testlib's built-in ncmp checker; contestants may output whitespace arbitrarily (either spaces or newlines).

Checkers are generally written using testlib. Since a checker must handle all kinds of invalid output, it needs very strong robustness; without testlib, it is very hard to write a good checker.

Pay attention to the following two points when writing a checker:

1.  You need to handle all kinds of invalid output, so please check whether every variable read is within the valid range (`readInt(minvalue, maxvalue)`). For example, when reading a variable that will be used as an array index during checking, you must check its range; otherwise, it may cause an out-of-bounds array access, which sometimes leads to RE and sometimes may be judged as AC.
2.  In principle, a checker should not check whitespace characters (that is, it should not use `readSpace()`, `readEoln()`, or `readEof()`; it is worth mentioning that testlib automatically checks whether there is extra output).

## Editorial

The goal of an editorial is to let everyone expected to participate in the contest understand it. Therefore, the required level of detail for official editorials is higher than that for ordinary editorials.

### About Partial Scores

For problems with partial scores, the editorial can consider describing the partial-score solutions.

### About Knowledge Points

Knowledge points used in the solution should be clearly stated. For knowledge points whose difficulty is comparable to the problem difficulty, it is best to provide materials for learning them (such as a blog URL).

### About Definitions

Do not introduce concepts out of nowhere in the editorial.

For example, an editorial for a dp problem should clearly explain the definition of the states.

### About Details

If specific implementation details are clever, it is best to write them out. Otherwise, "see the code for details" is also acceptable. If you say "see the code for details", it is best to add some comments in the code.

### Standard Solution

Redundant parts should preferably be removed from the standard solution. For example, some editorials keep a complete define template (used to improve problem-solving speed, containing many defines and common functions, and often used in online contests such as CF), while a large part of it is unused. This is bad.

If there are implementation details not described in detail in the editorial, it is best to add an appropriate amount of comments.

## Contest

### Problem Difficulty in Contest Announcements Must Be Truthful

> Remember that authors tend to underestimate the difficulty of their problems.
>
> --Reminder on the Codeforces PROPOSE A PROBLEM page

Problem setters are very likely to misjudge the difficulty of their problems. Therefore, if you want to write the contest difficulty in the contest announcement, you need to consider it carefully, and it is best to ask others to test the problems and evaluate them in advance.

### Distribution of Problem Difficulty

In mock contests similar to domestic OI, it is usually enough for the overall difficulty of the three problems to match the contest difficulty.

In online contests similar to CF/ATC, you need to try to ensure increasing difficulty (although due to misestimation of difficulty this often cannot truly be achieved), and try to avoid large difficulty gaps. You can reduce a difficulty gap by splitting one problem into an easier problem and a harder problem (two subtasks). However, splitting into subtasks needs careful consideration, and many people dislike subtasks in the CF system ([Are subtasks evil?](https://codeforces.com/blog/entry/71700)), for reasons including but not limited to:

-   Because of the contest system, solving the easy version first and then the hard version may incur less penalty time and yield a higher total score
-   The scores assigned to subtasks are often not proportional to problem difficulty
-   In many cases, the easy version is not a qualified problem (not interesting)
-   In many cases, the solution to the easy version does not help with thinking about the intended solution of the hard version

### Distribution of Problem Knowledge Points

A contest should cover as broad a range of knowledge points as possible (topic-based training contests are of course excluded).

Classic counterexample: CTS2019, which covered dynamic programming, expectation, combinatorial counting, inclusion-exclusion, polynomials, and many other knowledge points.

> I have to choose six problems from five; I am helpless too.
>
> --Reason given by the CTS2019 problem selection team: they did not receive enough problem submissions

## Problemsetting Platforms

### Polygon

Polygon is a very powerful collaborative problemsetting platform. It can be the first choice for collaborative problemsetting on any website (using the package feature to export to websites that do not support Polygon), and it is also a good choice for solo problemsetting (especially when working on different devices). For usage, see [Introduction to Polygon](../tools/polygon.md).

### Codeforces

Codeforces is one of the world's most famous algorithm contest websites. Its problem quality is high, making it very suitable for problem setters who already have some problemsetting experience and want to further improve their problemsetting level or create a high-quality problemset. Its downside is slow review speed (usually several months), but you can also start preparing the problems during review (although there is a risk that a problem is rejected and the preparation is wasted).

#### Eligibility to Set Problems

-   Blue name and participation in at least 25 rated contests;
-   Violet name and participation in at least 15 rated contests;
-   Orange name and participation in at least 5 rated contests;
-   Red name or legendary grandmaster.

#### Submit a Contest Application

After obtaining problemsetting eligibility, you can see the [Propose a contest/problems](http://codeforces.com/proposals/new-contest) button in the sidebar.

After entering, first write a contest proposal (in PROPOSE A CONTEST), then write problem proposals and add them to the contest.

After the problems are decided, you can open the contest proposal to review (submit it for review).

#### Prepare Problems on Polygon

Refer to [Introduction to Polygon](../tools/polygon.md).

#### Contact with Coordinators

Contacting coordinators has two purposes:

1.  Speeding up the review.
2.  After entering the preparation stage, coordinators will provide suggestions and help.

The formal contact method is to submit an application in the proposal system as a proposal, and after coordinators start reviewing, discuss below the proposal in the form of comments.

In practice, if a proposal has not been approved for a long time, you can consider privately messaging a coordinator (CF actually says "Don't send private messages or emails to coordinators", but 300iq said in a [comment](http://codeforces.com/blog/entry/64077#comment-478933) that you can privately message him).

### Comet OJ

[Comet OJ link](https://www.cometoj.com/)

No longer active (as of November 2021, the last contest was in January 2020).

Problemsetting application: <https://info.cometoj.com/contests/Questionnaire_IssuerInfo/>

### CodeChef

An Indian algorithm contest platform with three contest formats: the 10-day Long Challenge with challenges, the 2.5h ICPC-style Cook-Off, and the 3h IOI-style LunchTime.

Problemsetting FAQ: <https://www.codechef.com/wiki/faq-problem-setters>

Problemsetting guide: <https://www.codechef.com/problemsetting>

### AtCoder

A Japanese algorithm contest platform. Problemsetting contact: <contest@atcoder.jp>.

### UOJ & LOJ

Domestic OJs with few contests.

### Luogu

Staff participating in problemsetting need a certain award certification level. After creating a contest, the responsible person submits an application in the [ticket system](https://www.luogu.com.cn/ticket).

Open contest standard: <https://help.luogu.com.cn/rules/academic/opencontest-standard>

## References

1.  [vfk《UOJ 精神之源流》][1]

2.  [王天懿《论偏题的危害》][2]

3.  [Guidelines for CF problem setters][3] ([image version accessible in China](https://github.com/OI-wiki/libs/blob/master/topic/rules.jpg))

4.  [CF 出题人的自我修养][4]

This article was moved by the author from [ouuan 的出题规范](https://ouuan.github.io/post/ouuan-的出题规范/) and modified and supplemented.

[1]: https://vfleaking.blog.uoj.ac/blog/909 "vfk《UOJ 精神之源流》"

[2]: https://github.com/OI-wiki/libs/blob/master/topic/7-%E7%8E%8B%E5%A4%A9%E6%87%BF-%E8%AE%BA%E5%81%8F%E9%A2%98%E7%9A%84%E5%8D%B1%E5%AE%B3.ppt "王天懿《论偏题的危害》"

[3]: https://docs.google.com/document/d/e/2PACX-1vRhazTXxSdj7JEIC7dp-nOWcUFiY8bXi9lLju-k6vVMKf4IiBmweJoOAMI-ZEZxatXF08I9wMOQpMqC/pub "CF 出题人须知"

[4]: https://github.com/OI-wiki/libs/blob/master/topic/CF%E5%87%BA%E9%A2%98%E4%BA%BA%E7%9A%84%E8%87%AA%E6%88%91%E4%BF%AE%E5%85%BB.md "CF 出题人的自我修养"
