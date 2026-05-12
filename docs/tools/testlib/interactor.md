Interactor, i.e., interactive program, is used for interactive problems to interact with the participant's program. For an introduction to interactive problems, see [Problem Type Introduction - Interactive Problems](../../contest/problems.md#).

???+ note "Note"
    Testlib only supports Codeforces-style interactive problems, i.e., two-program interaction. It does not support NOI-style where participants write functions that interact with other functions.

Please read [General](./general.md) before continuing.

Testlib provides a special stream `std::fstream tout` for interactor, which is a log stream. You can write to it in interactor and read it in checker with `ouf`.

In interactor, we read problem test data from `inf`, write the participant program's (and solution's) standard input to `stdout` (online), read participant output from `ouf` (online), read standard output from `ans` (online).

If the interactor returns the ok state, the checker (if there is one) will take over and check the answer validity.

## Usage

Windows:

```bat
interactor.exe <Input_File> <Output_File> [<Answer_File> [<Result_File> [-appes]]],
```

Linux:

```bash
./interactor.out <Input_File> <Output_File> [<Answer_File> [<Result_File> [-appes]]],
```

## Simple Example

???+ note "Problem"
    The interactor randomly selects an integer in $[1,10^9]$. You need to write a program to guess it. You can ask at most 50 questions about integers in $[1,10^9]$.
    
    The interactor will return:
    
    `1`: The guess is the same as the answer; your program should stop guessing.
    
    `0`: The guess is smaller than the answer.
    
    `2`: The guess is larger than the answer.

Note that in this problem we don't need `ans`, because we don't need to compare it with the standard output; but in other problems you may need to.

```cpp
int main(int argc, char** argv) {
  registerInteraction(argc, argv);
  int n = inf.readInt();  // Select number
  cout.flush();           // Flush buffer
  int left = 50;
  bool found = false;
  while (left > 0 && !found) {
    left--;
    int a = ouf.readInt(1, 1000000000);  // Ask
    if (a < n)
      cout << 0 << endl;
    else if (a > n)
      cout << 2 << endl;
    else
      cout << 1 << endl, found = true;
    cout.flush();
  }
  if (!found) quitf(_wa, "couldn't guess the number with 50 questions");
  ouf.readEof();
  quitf(_ok, "guessed the number with %d questions!", 50 - left);
}
```

**This article is mainly translated from [Interactors with testlib.h - Codeforces](https://codeforces.com/blog/entry/18455). The GitHub repository for `testlib.h` is [MikeMirzayanov/testlib](https://github.com/MikeMirzayanov/testlib).**