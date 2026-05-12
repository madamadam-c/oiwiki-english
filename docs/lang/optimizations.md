author: inclyc

The commonly used programming language in OI is C++. Since this language is used, competitors inevitably deal with compilers and language standards. As everyone knows, C++ is extremely chaotic and evil. This article aims to provide practical compiler-related knowledge sufficient for contest use.

## Introduction to Compiler Optimization

### What Is Optimization?

According to the [as-if rule](https://en.cppreference.com/w/cpp/language/as_if), optimization improves program running speed or executable size while preserving semantics.

<!-- ### Which contests enable optimizations? -->

<!-- TODO: contests using O2 -->

## Common Compiler Optimizations

### Constant Folding

Constant folding, also called constant propagation, means that if an expression can be determined to be a constant, the constant may be propagated until its next definition.

```cpp
int x = 1;
int y = x;  // x = 1, => y = 1
x = 3;
int z = 2 * y;   // z => 2 * y = 2 * 1 = 2
int y2 = x * 2;  // x = 3, => y2 = 6
```

This code can be transformed at compile time into:

```cpp
int x = 1;
int y = 1;
x = 3;
int z = 2;
int y2 = 6;
```

Example: <https://godbolt.org/z/oEfY35TTd>

### Dead Code Elimination

As the name suggests, code that is not used is removed.

```cpp
int test() {
  int a = 233;
  int b = a * 2;
  int c = 234;
  return c;
}
```

will be transformed into:

```cpp
int test() { return 234; }
```

Note that this code first undergoes constant folding, making the return value determinable as 234. The variables `a` and `b` are inactive variables, so they are removed.

### Loop Rotate

This transforms a loop from `for` form into `do-while` form, with an extra condition check before it. This transformation mainly prepares for other transformations.

```cpp
for (int i = 0; i < n; ++i) {
  auto v = *p;
  use(v);
}
```

is transformed into:

```cpp
if (0 < n) {
  do {
    auto v = *p;
    use(v);
    ++i;
  } while (i < n);
}
```

### Loop Invariant Code Motion

Based on alias analysis, code in a loop that is proven to be invariant may be moved outside the loop. Such code may include memory access, load/store operations, so it depends on alias analysis. This reduces the amount of code inside the loop body.

```cpp
for (int i = 0; i < n; ++i) {
  auto v = *p;
  use(v);
}
```

Intuitively, this code can be moved out as:

```cpp
auto v = *p;
for (int i = 0; i < n; ++i) {
  use(v);
}
```

However, in reality, if `n <= 0`, the loop is never entered, but we have executed one extra instruction, which may have side effects. Therefore, loops are usually rotated into `do-while` form so a "loop guard" can be inserted conveniently. Loop invariant code motion is then performed.

```cpp
if (0 < n) {  // loop guard
  auto v = *p;
  do {
    use(v);
    ++i;
  } while (i < n);
}
```

### Loop Unroll

A loop contains the loop body and various branch statements, requiring modern CPUs to perform branch prediction. Directly unrolling the loop trades a certain amount of code size for running time.

```cpp
for (int i = 0; i < 3; i++) {
  a[i] = i;
}
```

is transformed into:

```cpp
a[0] = 0;
a[1] = 1;
a[2] = 2;
```

### Loop Unswitching

Loop unswitching moves a conditional expression inside a loop outside the loop, then places two loops under the two external branches. This can increase the possibility of loop vectorization and parallelization, since simple loops are usually easier to vectorize.

```cpp
// clang-format off
void before(int x) {
  for(;/* i in some range */;) {
    /* A */;
    if (/* condition */ x % 2) {
      /* B */;
    }
    /* C */;
  }
}

void after(int x) {
  if (/* condition */ x % 2) {
    for(;/* i in some range */;) {
      /* A */;
      /* B */; // directly execute B without checking inside the loop
      /* C */;
    }
  } else {
     for(;/* i in some range */;) {
      /* A */; 
               // do not execute B
      /* C */;
    }
  }
}
```

### Code Layout Optimizations

During execution, program paths can be divided into cold and hot paths. CPU jumps are almost always slower than direct sequential execution, which compiler authors usually call "fallthrough". Correspondingly, code that is frequently executed is hot code, while the opposite is cold code. In OI code, if a section is a special-case boundary check inside a loop, exception handling, or similar logic, then that section is cold code.

A basic block is the basic structure of control flow. A procedure consists of several basic blocks forming a directed graph. When generating an executable file, the compiler needs to arrange a layout for placing basic blocks, and how to arrange this layout is the focus of this optimization.

In principle, hot code should preferably be placed together, while cold code should be separated. This better utilizes the instruction cache, giving hot code better locality.

```cpp
// clang-format off
int hotpath; // <-- hot!
if (/* boundary condition */ false) {
    // <-- cold!
}
int hotpath_again;  // <-- hot!
```

#### Basic Block Placement

We use labels to express a kind of "pseudo machine code". This C++ program has two possible translations:

???+ note "Layout 1"
    ```cpp
    // clang-format off
    hotblock1:
        Stmts; // <-- hot!
        if (/* boundary condition does not hold */ true)
            goto hotblock2; // happens often! ------+
    coldblock:                           /*   |   */
        Stmt; // <- cold                       |
        Stmt; // <- cold                       |
        Stmt; // <- cold                       |  crosses many instructions; expensive!
        Stmt; // <- cold                       |
        Stmt; // <- cold                       |
        Stmt; // <- cold                       |
        Stmt; // <- cold                       |
    hotblock2:                          /*    |   */
        Stmts; // <- hot!           <----------+
    ```

Another layout is:

???+ note "Layout 2"
    ```cpp
    // clang-format off
    hotblock1:
        Stmts; // <-- hot!
        if (/* boundary condition */ false)
            goto coldblock; // rarely happens
    hotblock2:                         /*   |  low cost!  */
        Stmts; // <- hot!  <-----------------+
    coldblock:
        Stmt; // <- cold
        Stmt; // <- cold
        Stmt; // <- cold
        Stmt; // <- cold
        Stmt; // <- cold
    ```

We can see that in the latter layout, the two hot code blocks are placed together, resulting in better execution efficiency.

To tell the compiler whether a branch is likely to be executed, C++20 `[[likely]]` and `[[unlikely]]` can be used: <https://en.cppreference.com/w/cpp/language/attributes/likely>

If the contest does not use a standard above C++20, `__builtin_expect` (GNU Extension) can be used.

```cpp
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

if (unlikely(/* some boundary checks */ false)) {
  // cold code
}
```

#### Hot-Cold Splitting

A procedure may contain both hot and cold paths. When cold code is long, a better approach is to make the cold code a function call instead of blocking the hot path. This also reminds us not to be clever and make every function `inline`. Cold code can obstruct execution speed much more than a function call.

???+ note "Bad code layout"
    ```cpp
    // clang-format off
    void foo() {
          // clang-format off
    hotblock1:
        Stmts; // <-- hot!
        if (/* boundary condition does not hold */ true)
            goto hotblock2; // happens often! ------+
    coldblock:                           /*   |   */
        Stmt; // <- cold                       |
        Stmt; // <- cold                       |
        Stmt; // <- cold                       |  crosses many instructions; expensive!
        Stmt; // <- cold                       |
        Stmt; // <- cold                       |
        Stmt; // <- cold                       |
        Stmt; // <- cold                       |
    hotblock2:                          /*    |   */
        Stmts; // <- hot!           <----------+
    }
    ```

???+ note "Good code layout"
    ```cpp
    // clang-format off
    void foo() {
    hotblock1:
      Stmts;  // <-- hot!
      if (/* boundary condition */ false)
        coldBlock();  // split out cold code to make the hot path more cache-friendly
    hotblock2:
      Stmts;  // <- hot!
    }
    
    void coldBlock() {
      Stmt;  // <- cold
      Stmt;  // <- cold
      Stmt;  // <- cold
      Stmt;  // <- cold
      Stmt;  // <- cold
      Stmt;  // <- cold
      Stmt;  // <- cold
    }
    ```

Hot-cold splitting is essentially the reverse operation of function inlining. The existence of this optimization tells us that function inlining does not necessarily make a program run faster. If the inlined code is cold code, it may even make the program slower. Some compilers provide options for forced inlining, but they are not recommended. Inside the compiler, a static analysis process calculates the probability of each basic block and branch, as well as a cost model related to function calls, and uses this to decide whether to inline. Deciding whether to inline by yourself is not necessarily better than the compiler's decision.

In fact, without additional information, compilers usually assume that the probabilities of taking and not taking a branch are equal, then propagate the hotness or coldness of control-flow paths based on that. Part of PGO (Profile Guided Optimization) is to obtain actual branch probabilities in real environments through multiple performance tests and experiments. This information can make code layout better.

### Function Inlining

Function calls usually need registers and the stack to pass parameters. Both the caller and callee need to save some register state. This process is usually called the calling convention. A function call therefore introduces some time cost, and an inline function means writing the function directly into the caller's procedure without performing a real function call.

```cpp
int add(int x) { return x + 1; }

int foo() {
  int a = 1;
  a = add(a);
}
```

`add()` can be inlined into `foo()`:

```cpp
int foo() {
  int a = 1;
  a = a + 1;  // <-- body of add(), without parameter passing
}
```

#### `always_inline`,`__force_inline`

<https://clang.llvm.org/docs/AttributeReference.html#always-inline-force-inline>

Some compilers provide ways to manually inline function calls, such as adding `__attribute__((always_inline))` before a function. This usage is not necessarily faster than a function call. At this point, the compiler trusts that the programmer has sufficiently good judgment.

### Tail Call Optimization

When a function call is located at the end of a function body, this call is called a tail call. This special form of call can receive special optimization. Most architectures have a Frame Pointer (a.k.a. FP) and Stack Pointer (a.k.a. SP), which maintain a function's call frame. If the call is located at the tail of a function, the outer function's call record does not need to be preserved, and the inner function can directly replace it.

#### Replacing Function Calls with Jump Instructions

On most architectures, a function call needs to save the current program counter `$pc` and several caller-saved registers so execution can return to the call site. A tail call does not need this process and is translated directly into a jump instruction, because tail recursion never returns to the location where the function was running.

A simple example: <https://godbolt.org/z/e7b1safaW>

```cpp
int test(int a);

int tailCall(int x) { return test(x); }
```

```nasm
tailCall(int):                           ; @tailCall(int)
        jmp     test(int)@PLT                    ; TAILCALL
```

#### Automatic Tail Recursion Rewriting

If a function's tail call calls itself, the function is tail-recursive. Broadly speaking, indirect recursion, where two or more functions form recursion together and all calls are tail calls, also belongs to the category of tail recursion. Tail recursion can be optimized by the compiler into a non-recursive form, reducing extra stack overhead and function call cost. Many algorithm contest participants like writing non-recursive code. Without optimizations, this can greatly improve constants, but with optimizations enabled, the binary quality generated from recursive code is not much different from handwritten non-recursive code.

```cpp
int fac(int n) {
  if (n < 2) return 1;
  return /* use */ n * fac(n - 1); /* uses variable n, so tail recursion optimization cannot be done directly! */
}
```

Notice that this function is not tail-recursive, but it can be rewritten as:

```cpp
int fac(int acc, int n) {
  if (n < 2) return acc;
  return fac(acc * n, n - 1);
}
```

The new code is tail-recursive.

Modern compilers can automatically complete this process for you. If your code has a chance to be rewritten as tail recursion, the compiler can recognize this form and perform the rewrite.

#### Tail Recursion Elimination -Rpass=tailcallelim

Once a function is tail-recursive, the recursive statement can be directly removed. Through static analysis, the function can be converted directly into a non-recursive form. We will not examine in depth how compiler authors achieve this. From practical experience, for most OI code, if both recursive and non-recursive versions exist, the code can generally be automatically optimized into the non-recursive version. Here are some concrete examples:

???+ note "[GCD](https://godbolt.org/z/8Wb6WEnzv)"
    ```cpp
    int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
    ```

???+ note "[Fibonacci sequence](https://godbolt.org/z/4enof6Wcb)"
    ```cpp
    // Expand the fib(n - 2) term
    // fib(n - 1) cannot be transformed into non-recursive form, so the optimized code is still exponential
    int fib(int n) {
      if (n < 2) return 1;
      return fib(n - 1) + fib(n - 2);
    }
    ```

???+ note "[Factorial](https://godbolt.org/z/n64e75xrf)"
    ```cpp
    // Expand into a scalar loop, then perform auto-vectorization; the generated code is SIMD
    unsigned fac(unsigned n) {
      if (n < 2) return 1;
      return n * fac(n - 1);
    }
    ```

The optimized assembly of these functions is exactly the same as the non-recursive version; recursion is directly eliminated. For OI participants, when O2 is enabled, it is safe to write recursive versions of various algorithms, and they will not differ from non-recursive versions. If the function you write cannot itself be rewritten into a non-recursive form, then the compiler can do nothing.

### Strength Reduction

This is a common compiler optimization. The simplest example is turning `x * 2` into `x << 1`, and the second form is quite common in OI. Compilers automatically perform similar optimizations. With optimization options enabled, `x * 2` and `x << 1` are completely equivalent. Strength reduction converts high-cost instructions into low-cost instructions.

#### Scalar Operator Transformations

##### Shift Instead of Multiplication

```cpp
int a;
a = x * 2;   // bad!
a = x << 1;  // good!
```

Note that signed and unsigned numbers have significant differences in shifting and type promotion. The sign bit has special handling during shifts, including arithmetic shifts and logical shifts. This is especially prominent when writing binary search, segment trees, and other code with many divisions by two. Signed integer division cannot be directly optimized into a single right shift operation.

```cpp
int l, r;
/* codes */
int mid = (l + r) / 2; /* if the compiler cannot assume l and r are nonnegative, it generates worse code */
                       // cannot be optimized into
                       // mid = (l + r) >> 1
                       // counterexample:
                       // mid = -127
                       // mid / 2 = -63
                       // mid >> 1 = -64
```

```cpp
int mid = (l + r);
int sign = mid >> 31; /* logical right shift, obtaining the sign bit */
mid += sign;
mid >>= 1; /* arithmetic right shift */
```

Possible solutions:

-   Use `unsigned l, r;`, since indices should be unsigned in the first place.
-   Use shifts directly in the source code.

##### Multiplication Instead of Division

```cpp
int x = a / 3;
```

This process can be transformed into `x = a * 0x55555556 >> 32`. For details, see [this Zhihu answer](https://zhuanlan.zhihu.com/p/151038723) or the [original paper](https://dl.acm.org/doi/10.1145/773473.178249).

#### Induction Variable Strength Reduction (IndVars)

The compiler automatically identifies induction variables in loops and converts related high-cost processes into low-cost ones.

```cpp
int a = 0;
for (int i = 1; i < 10; i++) {
  a = 3 * i;  // bad!
  a = a + 3;  // good!
}
```

Using `a = 3 * i` directly is common in OI, but the compiler can automatically analyze that the equivalent transformation is `a = a + 3`, replacing multiplication with lower-cost addition. Analyzing the iteration process of loop variables is called SCEV (Scalar Evolution).

SCEV can also optimize some loops:

```cpp
int test(int n) {
  int ans = 1;
  for (int i = 0; i < n; i++) {
    ans += i * (i + 1);
  }
  return ans;
}
```

This function is optimized into an $O(1)$ summation formula. See <https://godbolt.org/z/ET8d89vvK>. This behavior currently appears only in LLVM-based compilers; GCC is more conservative.

```nasm
test(int):                               # @test(int)
        test    edi, edi
        jle     .LBB0_1
        lea     eax, [rdi - 1]
        lea     ecx, [rdi - 2]
        imul    rcx, rax
        lea     eax, [rdi - 3]
        imul    rax, rcx
        shr     rax
        imul    eax, eax, 1431655766
        and     ecx, -2
        lea     eax, [rax + 2*rcx]
        lea     eax, [rax + 2*rdi]
        dec     eax
        ret
.LBB0_1:
        mov     eax, 1
        ret
```

### Auto-Vectorization

Single instruction, multiple data is a good way to provide single-core parallelism. With such instructions, the CPU's SIMD registers can be used. They are wider than general-purpose registers, for example storing and computing four integers at once. OI participants do not need to understand the details of auto-vectorization. Generally speaking, Clang performs more aggressive auto-vectorization than GCC:

```cpp
// https://godbolt.org/z/h1hx5sWoE
void test(int *a, int *b, int n) {
  for (int i = 0; i < n; i++) {
    a[i] += b[i];
  }
}
```

#### `__restrict` type specifier (GNU, MSVC)

The regions corresponding to any two pointers may overlap, in which case special checks are needed to determine whether vector code can be used. The following figure shows an example of pointer overlap:

![](./images/overlap.png)

As a convention, `__restrict` makes the compiler assume that the memory regions pointed to by two pointers never overlap.

```cpp
void test(int* __restrict a, int* __restrict b, int n) {
  for (int i = 0; i < n; i++) {
    a[i] += b[i];
  }
}
```

`__restrict` is not part of the C++ standard, but it is available in major compilers. This keyword affects the code-generation quality of auto-vectorization and can be used in extreme constant-factor optimization cases.

## Common Language Misuses Related to Compiler Optimization

### inline

When O2 is enabled, function inlining is usually performed automatically by the compiler. `inline` in struct definitions is completely redundant. If the contest uses O2 optimization, there is no need to declare functions inline at all. If O2 is not enabled, using `inline` still will not make the compiler truly inline the function.

In modern C++, the `inline` keyword is treated as a semantic behavior related to linkage and exported symbols, not as a request for function inlining.

### register - Fake Register Advice

Modern compilers directly ignore your `register` keyword. The register allocation you imagine is generally not as smart as the compiler running a register allocation algorithm. This keyword was deprecated in C++11 and removed in C++17[^p0001r1].

<https://en.cppreference.com/w/cpp/keyword/register>

## Undefined Behavior and Compiler Optimization

The compiler may assume that a C++ program has no [undefined behavior](https://en.cppreference.com/w/cpp/language/ub) (UB). Therefore, when compiling a program that contains UB, the compiler may produce unexpected results. At the same time, under the assumption that no UB exists, the compiler can perform more aggressive and freer optimizations.

Common UB includes:

1.  [Signed overflow](https://users.cs.utah.edu/~regehr/papers/overflow12.pdf).
2.  Use of uninitialized variables.
3.  Out-of-bounds access.
4.  Null pointer dereference.
5.  Infinite loops with no side effects.

Other UB and examples can be learned from the extended reading.

### Signed Overflow

```cpp
int f(int x) { return x * 2 / 2; }
```

The compiler may assume that the program has no signed overflow, so this function may be optimized into:

```cpp
int f(int x) { return x; }
```

Examples: <https://godbolt.org/z/WKv3W5hvM>, <https://godbolt.org/z/qqE9nxP1j>.

This assumption can be disabled with the [`-fwrapv`](https://gcc.gnu.org/onlinedocs/gcc-13.2.0/gcc/Code-Gen-Options.html#index-fwrapv) option. Examples: <https://godbolt.org/z/5x3K5KGnr>, <https://godbolt.org/z/4r4a4EzMW>.

### Use of Uninitialized Variables

```cpp
int f(int x) {
  int a;
  if (x)  // either x nonzero or UB
    a = 42;
  return a;
}
```

The compiler may assume that the program does not use uninitialized variables, so `a` must be initialized, and this function may be optimized into:

```cpp
int f(int) { return 42; }
```

Examples: <https://godbolt.org/z/8WYMYYjdG>, <https://godbolt.org/z/qvGd1nvv9>.

### Out-of-Bounds Access

```cpp
int table[4] = {};

bool exists_in_table(int v) {
  // return true in one of the first 4 iterations or UB due to out-of-bounds
  // access
  for (int i = 0; i <= 4; i++)
    if (table[i] == v) return true;
  return false;
}
```

The compiler may assume that the program has no out-of-bounds access, so this function must return before out-of-bounds access occurs, and it may be optimized into:

```cpp
bool exists_in_table(int) { return true; }
```

Example: <https://godbolt.org/z/xfePeYsE3>.

### Null Pointer Dereference

```cpp
int f(int* p) {
  int x = *p;
  if (!p)
    return x;  // Either UB above or this branch is never taken
  else
    return 0;
}
```

The compiler may assume that the program has no null pointer dereference, making `!p` always `false`, and this function may be optimized into:

```cpp
int f(int*) { return 0; }
```

Examples: <https://godbolt.org/z/GY1jvsrb5>, <https://godbolt.org/z/4ronPsnxf>.

### Infinite Loops with No Side Effects

???+ note "Verifying Fermat's Last Theorem"
    By [Fermat's Last Theorem](https://en.wikipedia.org/wiki/Fermat%27s_Last_Theorem), the indeterminate equation $a^3=b^3+c^3$ has no positive integer solutions. The following program tries to enumerate integers in $[1,1000]$ to verify whether this equation holds. If it returns `true`, it means an integer solution was found in the range $[1,1000]$, so Fermat's Last Theorem would be false.
    
    ```cpp
    #include <iostream>
    
    bool fermat() {
      const int max_value = 1000;
    
      // Endless loop with no side effects is UB
      for (int a = 1, b = 1, c = 1; true;) {
        if (((a * a * a) == ((b * b * b) + (c * c * c))))
          return true;  // disproved :()
        a++;
        if (a > max_value) {
          a = 1;
          b++;
        }
        if (b > max_value) {
          b = 1;
          c++;
        }
        if (c > max_value) c = 1;
      }
    
      return false;  // not disproved
    }
    
    int main() {
      std::cout << "Fermat's Last Theorem ";
      fermat() ? std::cout << "has been disproved!\n"
               : std::cout << "has not been disproved.\n";
    }
    ```

The compiler may assume that the program has no infinite loops with no side effects, so it believes the `for` loop in `fermat()` must terminate at some point and return `true`. The final program may output:

```text
Fermat's Last Theorem has been disproved!
```

Examples: <https://godbolt.org/z/d834MK7bz>, <https://godbolt.org/z/Eov9nsKqf>.

## Sanitizer

A sanity protector. It checks at runtime whether your program has undefined behavior, array out-of-bounds access, null pointers, and similar issues.
In local debugging mode, enabling some sanitizers is recommended and can greatly shorten your debugging time. These sanitizers were developed by Google, and most can be used with GCC and Clang. Sanitizers are more mature in LLVM, so contestants are recommended to use the Clang compiler locally for related debugging.

### Address Sanitizer -fsanitize=address

<https://clang.llvm.org/docs/AddressSanitizer.html>

Both GCC and Clang support this sanitizer. It includes the following checks:

-   Out-of-bounds access
-   Use-after-free
-   Use-after-return
-   Double-free
-   Memory leaks
-   Use-after-scope

Applying this check makes your program about 2x slower.

### Undefined Behavior Sanitizer -fsanitize=undefined

<https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html>

Undefined Behavior Sanitizer (a.k.a. UBSan) is used to check undefined behavior in code. Both GCC and Clang support this sanitizer. It automatically checks whether your program has undefined behavior. UBSan checks include:

-   Shift overflow, such as left-shifting a 32-bit integer by 72 bits.
-   Signed integer overflow.
-   Overflow when converting floating-point numbers to integer data.

UBSan checks are optional. See the linked page for their impact on programs.

## Miscellaneous

### Compiler Explorer

Observe the behavior and assembly code of various compilers here: <https://godbolt.org>

## Extended Reading

1.  [The LLVM Project Blog: What Every C Programmer Should Know About Undefined Behavior #1/3](https://blog.llvm.org/2011/05/what-every-c-programmer-should-know.html)
2.  [The LLVM Project Blog: What Every C Programmer Should Know About Undefined Behavior #2/3](https://blog.llvm.org/2011/05/what-every-c-programmer-should-know_14.html)
3.  [The LLVM Project Blog: What Every C Programmer Should Know About Undefined Behavior #3/3](https://blog.llvm.org/2011/05/what-every-c-programmer-should-know_21.html)

## References and Notes

[^p0001r1]: [Remove Deprecated Use of the register Keyword (open-std.org)](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/p0001r1.html)
