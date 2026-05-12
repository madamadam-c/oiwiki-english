author: StudyingFather, NachtgeistW, countercurrent-time, Ir1d, H-J-Granger, Chrogeek, sshwy, Suyun514, hsfzLZH1, CBW2007, Xeonacid, kawa-yoiko, Konano

Algorithm competitions feature many different problem types.

## Traditional problems

**Traditional problems** are currently one of the more common problem types in algorithm competitions.

Contestants need to submit source code. The judging system uses prepared input data and the corresponding output data as test cases[^note1]. After compiling the submitted source code[^note2], it lets the contestant's program read the input data, then determines whether the program is correct by comparing the contestant's output with the prepared output. This judging method is called **black-box judging**[^note3].

A test case usually also has a time limit and a memory limit.

The time limit is the limit on the program's running time[^note4]. The running time of a contestant's program on a test case must not exceed the given time limit.

The memory limit is the limit on the amount of memory used by the program. The maximum memory occupied by a contestant's program while running must not exceed the given memory limit.

After the program terminates normally, the contestant's output is compared with the test case output. This comparison is usually a full-text comparison after filtering trailing newlines at the end of the file and trailing spaces at the end of each line. For some special problems, a [Special Judge](../tools/special-judge.md) is used for comparison.

After this process ends, the judging system gives different **verdicts** according to the program's running status[^note5]:

-   Accepted (AC): the contestant's program is accepted.
-   Compile Error (CE): the contestant's program cannot be compiled normally.
-   Wrong Answer (WA): the contestant's program terminates normally, but its output does not match the test case output.
-   Presentation Error (PE): the contestant's program terminates normally, but the format does not meet the requirements[^note6].
-   Runtime Error (RE): the contestant's program terminates abnormally (the return value when the program exits is nonzero).
-   Time Limit Exceeded (TLE): the running time of the contestant's program exceeds the given time limit.
-   Memory Limit Exceeded (MLE): the maximum memory occupied by the contestant's program exceeds the given memory limit.
-   Output Limit Exceeded (OLE): the amount of content output by the contestant's program exceeds the maximum limit.

In ICPC contests, your program must receive AC on all test cases of a problem before the problem is considered solved. In OI contests, receiving AC on a test case earns the score for that test case[^note7].

## Output-only problems

**Output-only problems** are problems where answers are submitted directly. Such problems generally provide input files and require submitting an archive, folder, or plain files containing `XXX1.out`, `XXX2.out`, `XXX3.out`...`XXXn.out`.

After the answers are submitted, the judging system compares the answer files with the standard answers and awards a certain score according to the quality of the contestant's answers and the degree of task completion.

Because output-only problems do not need to run source programs, they have no time or memory limits.

There are generally two ways to solve this kind of problem:

-   Solve it manually. This method is simple and direct, but it cannot handle large data.
-   Write a program to obtain the answer files.

## Interactive problems

**Interactive problems** are problems where the contestant's program must interact with a judging program to complete the task. One common situation is that the contestant's program sends queries to the judging program and receives feedback from it. The judging program may impose restrictions on the contestant's queries or adjust its response strategy to increase the number of queries as much as possible, which also gives the problem more variation.

For a more detailed explanation of interactive problems, see [interactive problems](./interaction.md).

There are mainly two interaction methods. Although they differ considerably in technical implementation, they have no practical difference in the essence of the algorithms being tested.

### STDIO interaction

STDIO interaction (standard I/O interaction) is the interaction method used by online platforms such as Codeforces and AtCoder, and is also the standard in ICPC series contests. Codeforces provides a more concise [explanation (in English)](https://codeforces.com/blog/entry/45307).

???+ note "Example [LOJ #559.「LibreOJ Round #9」ZQC 的迷宫](https://loj.ac/problem/559)"
    Please note the added content at the bottom.
    
    This is an interactive problem.
    
    You are in a dark maze made up of $n \times m$ squares, and you need to reach the end of the maze to complete the maze challenge.
    
    Initially, you are at the maze's starting point, $(1,1)$, facing right, and the endpoint is at $(n,m)$. Any two squares in the maze are connected, and there is exactly one path between them. The distance between two adjacent (that is, four-connected in the up, down, left, and right directions) squares is one unit. There may be walls between two adjacent squares. The thickness of a wall is very small compared with a square and can be roughly ignored. The boundary of the maze is walled, and every wall is connected to the boundary. The maze is completely dark, which means you cannot obtain any information other than $(n,m)$.
    
    To avoid getting lost as much as possible in the dark, each time you move forward you can only start from the current cell, follow the wall on the left or right side, keep your left or right hand on the wall, and make the hand touching the wall move exactly one unit of distance. Note that if there is no wall on the left or right side, you cannot move in that direction.
    
    Staying in the dark for too long will make you afraid, so you need to get out of the maze as early as possible. If you do not leave the maze within the limited number of steps, the challenge will fail.

For this kind of problem, contestants only need to write queries to standard output as usual, **flush the output buffer**, and then read the result from standard input. Only after the contestant's program flushes the output buffer can the judging program connected to it through a pipe (called the interactor) receive this data immediately. In C/C++, `fflush(stdout)` and `std::cout << std::flush` can perform this operation (using `std::cout << std::endl` for a newline also automatically flushes the buffer, but `std::cout << '\n'` does not); in Pascal, use `flush(output)`.

### Grader interaction

Grader interaction is common in international OI contests such as IOI and APIO (especially contests on the CMS platform).

???+ note "Example [UOJ #206.【APIO2016】Gap](https://uoj.ac/problem/206)"
    There are $N$ strictly increasing nonnegative integers $a_1,a_2,\cdots,a_N (0\leq a_1<a2<\cdots<a_N\leq 10^{18})$. You need to find the maximum value among $a_{i+1}−a_i (0\leq i\leq N−1)$.
    
    Your program cannot directly read this integer sequence, but you can query information about the sequence through the given functions. For details about the query functions, refer to the implementation details section below according to the language you use.
    
    You need to implement a function that returns the maximum value of $a_{i+1}−a_i (0\leq i\leq N−1)$.

For this kind of problem, contestants only need to write a specific function to complete a task; it interacts by calling several given helper functions. To make local testing easier, the problem provides a header file and a reference judging program `grader.cpp` (for Pascal, a library `graderlib`). Contestants compile their own program together with `grader.cpp` to obtain an executable file.

```sh
g++ grader.cpp my_solution.cpp -o my_solution -Wall -O2
./my_solution   # Run the program
```

The compiled program behaves similarly to a traditional-problem program. It opens fixed files, reads data in a fixed format, calls the function written by the contestant, and displays the result and some information (such as the number of queries and whether the answer is correct) on standard output.

During actual judging, the contestant's program is compiled with a different `grader.cpp`. This `grader.cpp` calls the function written by the contestant in a similar way and records the score. Generally, all global symbols in this version of `grader.cpp` are set to `static`, so it cannot be hacked through conflicting names, but any attempt to bypass grader restrictions will result in disqualification.

### Differences

One obvious advantage of STDIO interaction is that it can support any programming language, but the time spent on input and output can easily become a bottleneck in problem design, sometimes making it impossible to distinguish differences in programs' time efficiency. Grader interaction is the opposite: because the overhead of function calls is small, it can often allow around $10^6$ queries, but language restrictions are its weakness.

If you design problems or host contests yourself, you need to weigh and compare the two carefully.

## Communication problems

**Communication problems** are problems where two contestant programs need to communicate and cooperate to complete a task. The first program receives the problem input and produces some output; the input of the second program is related to the output of the first program (sometimes unchanged as a parameter, and sometimes obtained after processing by the judging side), and it needs to produce the solution to the problem.

Examples of communication problems include [UOJ #178. 新年的贺电](https://uoj.ac/problem/178), [#454.【UER #8】打雪仗](https://uoj.ac/problem/454), and others.

Local testing methods vary widely depending on the problem settings. Common forms include:

-   Manual input
-   Writing a helper program to convert the output of the first program into the input of the second program
-   Connecting the standard input/output of the two programs with bidirectional pipes

Because judging platforms have limited support for communication problems, so far they are only common in IOI series contests and contests hosted by a few online platforms such as UOJ. This remains an area to be explored.

## Function-completion problems

**Function-completion problems** are problems where contestants need to complete a program. They can be understood as interactive problems where the problem provides the contestant code and asks the contestant to write helper functions.

They usually take the following forms:

-   Providing a program and specifying where the code block to be completed will be embedded.
-   Not providing a program, but using the input information as parameters of the function to be submitted.

This kind of problem is relatively common on [LeetCode](https://leetcode.com/) and [PTA - 拼题 A](https://pintia.cn/problem-sets).

## Other types

???+ note "Example [Quine](https://loj.ac/problem/4)"
    Write a program that can output its own source code.
    
    The code must contain at least ten visible characters.

This problem is very classic, but it is difficult to implement on most OJs.

??? note "Reference code"
    **Note**: the source code does not include the first line below (that is, `// clang-format off`).
    
    ```cpp
    // clang-format off
    #include<cstdio>
    
    char *s={"#include<cstdio>%cchar *s={%c%s%c};%cint main(){printf(s,10,34,s,34,10);return 0;}"};
    
    int main(){printf(s,10,34,s,34,10);return 0;}
    ```

## References and notes

[^note1]: Because of technical and resource limitations, the test cases of a problem usually cannot cover all data satisfying the constraints.

[^note2]: For interpreted languages such as Python, the program is interpreted and run directly by the interpreter.

[^note3]: In fact, the implementation of a judging system is far more complex than this; this is only a rough introduction to the judging process.

[^note4]: More precisely, this is generally the program's user-mode time.

[^note5]: Most of the verdicts here also apply to other types of problems.

[^note6]: Most judging systems classify the PE status as WA.

[^note7]: Some test cases may have partial scores. Contestants can receive a certain proportion of the score when they complete part of a test case's tasks, or when their output is correct but not optimal.
