author: Estrella-Explore, H-J-Granger, orzAtalod, ksyx, Ir1d, Chrogeek, Enter-tainer, yiyangit, shuzhouliu, broken-paint, CarvingAn

This page mainly lists some common mistakes that many people make in contests.

## Errors caused by different environments

- Using the `%I64d` format specifier with `scanf` or `printf` may cause input/output format errors on Linux.

## Errors that cause CE

These errors are mostly lexical, syntax, and semantic errors. The causes are relatively simple, and they are easy to fix.

Examples:

- Misspelling `int main()` as `int mian()` or similar typos.

- Forgetting to write a semicolon after a `struct` or `class` definition.

- Declaring an overly large array, using illegal functions (e.g., multithreading) on an OJ, or declaring a function without defining it, which can cause linker errors.

- Function parameter type mismatch.

- Example: when using the `max` function from the `<algorithm>` header, passing an `int` parameter and a `long long` parameter.

```cpp
// query is a custom function that returns long long
printf("%lld\n", max(0, query(1, 1, n, l, r));

// Error: no overloaded function "std::max" matches the argument list
```

- Using `goto` or `switch-case` to skip the initialization of some local variables.

## Errors that cause Warnings but not CE

Programs with these errors can pass compilation, but will most likely produce incorrect runtime results. These errors can be pointed out by the compiler when compiling with the `-W{warningtype}` flag.

- Confusing the assignment operator `=` with the comparison operator `==`.

- Example:

```cpp
std::srand(std::time(nullptr));
int n = std::rand();
if (n = 1)
  printf("Yes");
else
  printf("No");

// No matter what value n gets from rand(), the output is definitely Yes
// Warning: incorrect operator: constant assignment in Boolean context. Consider using '==' instead.
```

- If you really want to use `=` where `==` should be used (e.g., `while (foo = bar)`) and don't want to receive a Warning, you can use **double parentheses**: `while ((foo = bar))`.

- Errors caused by operator precedence.

- Example:

```cpp
// Wrong
// std::cout << (1 << 1 + 1);
// Correct
std::cout << ((1 << 1) + 1);

// Warning: '<<': check if operator precedence might be wrong; use parentheses to clarify precedence
```

- Incorrect use of the `static` modifier.

- Forgetting to add the address-of operator `&` when using `scanf` to read input.

- Using `scanf` or `printf` with parameter types that don't match the format specifiers.

- Using bitwise operations and the logical operator `==` simultaneously without parentheses.
- Example: `(x >> j) & 3 == 2`

- `int` literal overflow.

- Example: `long long x = 0x7f7f7f7f7f7f7f7f`, `1<<62`.

- Uninitialized local variables.

???+ note "What happens with uninitialized variables"
Original: <https://loj.ac/d/3679> by @hly1204

For example, if we declare `int a;` in C++ without initializing it, we might sometimes think `a` is a "random" (though not truly random) value, but we might also assume it's a fixed value, which is actually not the case.

In this simple test code

<https://wandbox.org/permlink/T2uiVe4n9Hg4EyWT>

the code is:

```cpp
#include <iostream>

int main() {
  int a;
  std::cout << std::boolalpha << (a < 0 || a == 0 || a > 0);
  return 0;
}
```

With optimizations enabled on some compilers and environments, the output is false.

If you're interested, you can read <https://www.ralfj.de/blog/2019/07/14/uninit.html>. Although the experiments are done in Rust, the essence is the same.

- Local variables having the same name as global variables, causing global variables to be accidentally shadowed. (Compiling with `-Wshadow` can check for this type of error.)

- Output errors caused by operator overloading.
- Example:

```cpp
// Intent: the first << is the overloaded operator for output; the second << is the shift operator,
// meaning left-shift 1 by 1 bit. But due to forgetting parentheses, the compiler treats the
// second << as the output operator too, causing the output to differ from expectations.
// Wrong
std::cout << 1 << 1;
// Correct
std::cout << (1 << 1);
```

## Errors that cause neither CE nor Warnings

These errors cannot be detected by the compiler and must be found manually.

### Errors that cause WA

- After finishing processing one set of data, forgetting to clear the array before reading the next set.

- Read optimization not handling negative numbers.

- Insufficient bit width of the data type used, causing overflow.
- The scenario described by the saying "Three years of OI all for nothing, not using `long long` brings shame to your ancestors." A contestant fails to use `long long` in the right places (defining integers as `long long` type), leading to wrong answers and lost points.

- When storing a graph, node indices start from 0, but the edge endpoints given in the problem start from 1, and forgetting to subtract 1 when reading input.

- Writing greater-than/less-than signs incorrectly or in reverse.

- Mixing `scanf/printf` and `std::cin/std::cout` after executing `ios::sync_with_stdio(false);`, causing input/output disorder.

- Example:

```cpp
// This example illustrates the consequences of mixing two IO methods
// after disabling synchronization with stdio
// It is recommended to step through to observe the effect
#include <cstdio>
#include <iostream>

int main() {
  // After disabling synchronization, cin/cout will use an independent buffer
  // instead of syncing output to scanf/printf's buffer, reducing IO time
  std::ios::sync_with_stdio(false);
  // With cout, when using '\n' for newline, content is buffered and not immediately output
  std::cout << "a\n";
  // printf's '\n' will flush printf's buffer, causing output misalignment
  printf("b\n");
  std::cout << "c\n";
  // cout's buffer is only output when the program ends
  return 0;
}
```

- Errors caused by macro expansion without parentheses.

- Example: this macro does not return $4^2 = 16$ but $2+2\times 2+2 = 8$.

```cpp
#define square(x) x* x
printf("%d", square(2 + 2));
```

- Computation errors from not using `unsigned` when hashing.
- Right-shifting a negative number will fill the highest bit with 1. See: [Bitwise Operators](../lang/op.md#位操作符).

- Forgetting to remove or comment out debug output statements.

- Accidentally adding a `;`.

- Example:

```cpp
/* clang-format off */
while (1);
printf("OI Wiki!\n");
```

- Incorrectly set sentinel values. For example, node `0` in a balanced tree.

- When using `:` to initialize variables in a class or struct constructor, the variable declaration order does not match the dependency order during initialization.

- The initialization order of member variables is related to their declaration order in the class, not the order in the initializer list. See: [Constructors and member initializer lists](https://zh.cppreference.com/w/cpp/language/constructor) "Initialization order"
- Example:

```cpp
#include <iostream>

class Foo {
 public:
  int a, b;

  // a will be initialized before b, its value is indeterminate
  Foo(int x) : b(x), a(b + 1) {}
};

int main() {
  Foo bar(1, 2);
  std::cout << bar.a << ' ' << bar.b;
}

// Possible output: -858993459 1
```

- When merging sets in a Disjoint Set Union, not merging the ancestors of the two elements.

- Example:

```cpp
f[a] = b; // Wrong
f[find(a)] = find(b); // Correct
```

- Using `freopen` with `a` for append writing
- CCF's judging environment does not clear output files, so using `a` will cause the previous contestant's output to also be read by the judger, resulting in WA

#### Different newline characters

???+ warning "Warning"
In official competitions, efforts are made to ensure that the contestant's environment matches the final testing environment.

This section only applies to situations like mock contests, and we also recommend that problem setters make their data conform to [Data Format](problemsetting.md#数据的格式).

Different operating systems use different symbols to mark newlines. Here are the newline characters for several common systems:

- LF (represented by `\n`): `Unix` or `Unix`-compatible systems

- CR+LF (represented by `\r\n`): `Windows`

- CR (represented by `\r`): `Mac OS` version 9 and earlier

C/C++ uses the escape sequence `\n` for newlines, which may lead us to assume that newline characters in the input are also represented by `\n`, and thus only read one character to represent the newline. This causes us to not fully read the input file.

Solutions:

- Call `getchar()` multiple times until the desired character is read.

- Use `cin` to read input, **this may increase the code's constant factor**.

- Use `scanf("%s",str)` to read a string, then take `str[0]` as the read character.

- Use `scanf(" %c",&c)` to skip all whitespace characters.

### Errors that lead to unknown results

Undefined behavior leads to unknown results, which may be WA, RE, etc. Compilers typically assume your program does not exhibit undefined behavior, so code behavior may differ with and without O2 optimization.

- Division by 0 (finding the modular inverse of 0)

???+ warning "Example"
```cpp
cout << x / 0 << endl;
```

- Array (index) out of bounds

Examples:

- Not correctly setting the initial value of a loop, causing access to the value at index -1.

- Undirected graph edge list not allocated with 2x space.

- Segment tree not allocated with 4x space.

- Misreading the data range, missing a zero.

- Incorrectly estimating the space complexity of the algorithm.

- When writing a segment tree, calling `pushup` or `pushdown` on a leaf node.

Correct approach: don't go out of bounds, remember to check your code so that the accessed index `x` is within the defined index range.

- A function with a return value (other than main) reaches the end without executing any return statement

Even if one branch has a return value but other branches don't, the result is still undefined.

You can add `-Wall` to the compilation options to check if the compiler gives warnings about functions not returning.

- Attempting to modify a string literal

???+ warning "Example"
```cpp
char *p = "OI-wiki";
p[0] = 'o';
p[1] = 'i';
```

Attempting to modify a string literal like this causes **undefined behavior**. You should use other **appropriate** data types, such as `std::string` and `char[]`.

- Releasing/dereferencing a piece of memory multiple times or illegally

Examples:

- Dereferencing a pointer without initializing it.

- The memory area pointed to by the pointer has already been freed.

When using `erase`, `delete`, or `free` operations, be careful not to use them on the same address/object multiple times.

- Attempting to free a portion of memory allocated by `new []` as a whole

Example:

```cpp
object *pool = new object[POOL_SIZE];

object *pointer = pool + 10;

// Error!
delete pointer;
```

This is common when allocating a whole block of memory in advance using a memory pool, and then trying to use `delete` or `free()` to release a single object obtained from the memory pool.

- Dereferencing a null pointer/dangling pointer

For null pointers: you should check for null pointers first, using `p == nullptr` or `!p`.

For dangling pointers: when freeing a pointer, you can set it to `nullptr` to avoid issues.

- Signed integer overflow

For example, we have an expression `x+1 > x`.

The normal output should be `true`, but when `INT_MAX` is used as `x`, the output is `false`. This is called `signed integer overflow`.

You can use a larger data type (e.g., `long long` or `__int128`), or check for overflow. If you can guarantee no negative numbers, you can also use unsigned integer types.

Signed integer overflow may affect compiler optimization. For example, the code:

```cpp
int foo(int x) {
  if (x > x + 1) return 1;
  return 0;
}
```

May be directly optimized by the compiler to:

```cpp
int foo(int x) { return 0; }
```

Because the compiler can assume that signed integers never overflow, so `x > x + 1` is never true.

- Using uninitialized variables

???+ warning "Example"
```cpp
int foo(int a) {
  int t; /* not initialized */
  if (/* using */ t > 3) return a;
  return 0;
}
```

### Errors that cause RE

- Not removing file operations (on some OJs).

- Errors in comparison functions when sorting. `std::sort` requires the comparison function to be a strict weak ordering: `a<a` is `false`; if `a<b` is `true`, then `b<a` is `false`; if `a<b` is `true` and `b<c` is `true`, then `a<c` is `true`. Pay special attention to the second point.
If the above requirements are not met, sorting will very likely cause RE.
For example, when writing the odd-even sort for Mo's algorithm, this is wrong:

```cpp
bool operator<(const int a, const int b) {
  if (block[a.l] == block[b.l])
    return (block[a.l] & 1) ^ (a.r < b.r);
  else
    return block[a.l] < block[b.l];
}
```

In the above code, `(block[a.l]&1)^(a.r<b.r)` does not satisfy the second requirement.
Changing it to this is correct:

```cpp
bool operator<(const int a, const int b) {
  if (block[a.l] == block[b.l])
    // Wrong: does not satisfy strict weak ordering requirement
    // return (block[a.l] & 1) ^ (a.r < b.r);
    // Correct
    return (block[a.l] & 1) ? (a.r < b.r) : (a.r > b.r);
  else
    return block[a.l] < block[b.l];
}
```

- Insufficient stack space on Windows, causing stack overflow. Windows sends a SIGSEGV signal to the program, which terminates and returns 3221225725 (i.e., 0xC00000FD, NTSTATUS defined as `STATUS_STACK_OVERFLOW`).
If using the gcc compiler, you can add the command `-Wl,--stack=SIZE` during compilation to specify the stack space size limit, where `SIZE` is the stack space size in bytes.

Insufficient stack space on Linux, causing stack overflow. Linux will write `head_info` randomly into the stack heap, which in most cases causes the program to exit immediately, displaying messages like `segmentation fault (core dumped)`.
You can use `ulimit -s SIZE` in the terminal to modify the current terminal's stack space limit, where `SIZE` is the stack space size in kilobytes (KB).
**Please note that if you set the stack space limit too large, infinite recursion may cause the recursion stack to grow too large and crash the system.**

### Errors that cause TLE

- Divide and conquer without checking boundaries, causing infinite recursion.

- Infinite loops.

- Loop variable name collisions.

- Loop direction reversed.

- Not marking whether a state has been visited during BFS.

- Using macro expansion to write min/max

This error can greatly increase the program's running time, and may even directly affect the code's time complexity. This is especially common when beginners write segment trees.

A common incorrect way to write this:

```cpp
#define Min(x, y) ((x) < (y) ? (x) : (y))
#define Max(x, y) ((x) > (y) ? (x) : (y))
```

Although this is correct in terms of correctness, if you directly take the max of function return values, such as `a = Max(func1(), func2())`, and this function has a long running time, it will greatly affect the program's performance. This is because after macro expansion, it becomes `a = func1() > func2() ? func1() : func2()`, calling the function three times, which is one more call than a normal max function. Note that if `func1()` returns a different answer each time, this way of writing `max` will also cause errors. For example, if `func1()` is `return ++a;` where `a` is a global variable.

Example: the following code will be stuck at $\Theta(n)$ per query, causing TLE.

```cpp
#define max(x, y) ((x) > (y) ? (x) : (y))

int query(int t, int l, int r, int ql, int qr) {
  if (ql <= l && qr >= r) {
    ++ti[t]; // Record node access count for debugging
    return vi[t];
  }

  int mid = (l + r) >> 1;
  if (mid >= qr) return query(lt(t), l, mid, ql, qr);
  if (mid < ql) return query(rt(t), mid + 1, r, ql, qr);
  return max(query(lt(t), l, mid, ql, qr), query(rt(t), mid + 1, r, ql, qr));
}
```

- Using the + operator to append characters to a `std::string`

This error creates a temporary `string` variable, modifies it, and then assigns it back to the original variable. This error cannot be optimized by the compiler, and may cause time complexity degradation with large amounts of data.

Common incorrect way:

```cpp
std::string a;
char b = 'c';
a = a + b;
```

When executing this code, the program first creates a temporary `string` variable, then stores the value of `a` into the temporary variable, appends the value of `b` at the end, and finally stores it back into `a`.

From the [assembly result](https://godbolt.org/z/Eo9vn7or5), `a = a + b` calls three functions in `std::__cxx11::basic_string`: `operator+`, `operator=`, and variable creation.

The correct way should be:

```cpp
std::string a;
char b = 'c';
a += b;
```

[This approach](https://godbolt.org/z/eGh33Grf3) directly appends the character `b` to the string `a`, calling `operator+=` only once. For a more detailed performance comparison, see [Benchmark](https://quick-bench.com/q/JNDGl7HgOszNG-bo7AgVc42owv4).

- Not removing file operations (on some OJs).

- Repeatedly executing a function with non-$O(1)$ complexity inside a `for/while` loop. Strictly speaking, this may change the time complexity.

- Incorrect midpoint formula or termination condition during binary search.

### Errors that cause MLE

- Arrays that are too large.

??? note "Detailed explanation of memory usage metrics on Linux"
> TL;DR: If you declare a particularly large global static array during CCF series exams, you need to be very cautious. This is because the array declared by the program will be fully counted toward memory usage (unlike most online judging platforms that only count the actually used portion), and in some cases this may even cause the entire problem to MLE.

- About RSS and VSZ[^ref1][^ref2]

1. VSZ (Virtual Memory Size)[^ref3]

VSZ represents the **virtual memory size** of a process, which is the total size of the virtual address space the process can access, typically displayed in KB.

Virtual memory is a logical concept and is usually much larger than actual memory usage.

On Linux, you can use the `top` command to view the memory usage composition of a process, where the `VIRT` column represents the virtual memory it occupies.

Virtual memory generally includes address space allocated by the process but not actually used. In short, how much you requested is approximately how much virtual memory there is.

It is particularly important to note that common online judging platforms usually only count physical memory usage. But **CCF's judging environment counts virtual memory**, which means if you declare a large global static array, even if you only use a small part of it, it will still occupy a large amount of space.
2. RSS (Resident Set Size)[^ref4]

RSS represents the **physical memory size** actually occupied by a process, i.e., the size of page frames residing in RAM, typically displayed in KB.

Similarly, you can use `top` to view a process's physical memory in the `RES` column.

RSS generally only contains the portion actually loaded into physical memory, meaning however much is actually used is how much it is.
- Memory usage behavior analysis

Suppose the following array is declared:

```cpp
const int SIZE = 1e8;
int arr[SIZE]; // Space: 4 bytes * 100 million = 400 MB
```

This is a static array allocated in the global data segment. This array is not explicitly initialized and is typically allocated in the BSS segment (if explicitly initialized, e.g., all zeros or other values, it is allocated in the DATA segment).

- When the array is completely unused (assuming the compiler does not optimize away the array)

- Physical memory: If the array is not accessed, the demand paging mechanism means memory pages are not yet loaded into physical memory. Physical memory will not increase or will only increase slightly (some metadata pages may be loaded).
- Virtual memory: The size of the array is counted toward virtual memory (increased by `400MB`), because the entire virtual address space of the array has been allocated.
- When the array is partially used

Suppose only a small number of elements of the array are used, for example:

```cpp
arr[0] = 1;
arr[999999] = 2;
```

- Virtual memory: Virtual memory does not change, still `400MB`.
- Physical memory: Each time an element of the array is accessed, the corresponding virtual page is loaded into physical memory. Assuming a system page size of `4KB`, each page contains $4 \text{KB} ÷ 4 \text{B} = 1024$ `int` elements. Accessing the array twice may load 2 pages, i.e., increasing physical memory by about $2 \times 4 \text{KB} = 8 \text{KB}$.
- When most of the array is used

Suppose we assign values to the first $50,000,000$ elements of the array:

```cpp
for (int i = 0; i < 50000000; ++i) {
  arr[i] = i;
}
```

- Virtual memory (VSZ): VSZ is still `400MB` and does not change.
- Physical memory (RSS): At this point it is sequential access (the $50,000,000$ elements accessed are adjacent in memory addresses), the number of pages that need to be loaded is $\left\lceil \dfrac{50,000,000}{1024} \right\rceil = 48,828$ pages.

Assuming each page is `4KB`, the total is $48,828 \times 4 \text{KB} \approx 190 \text{MB}$, and physical memory increases to approximately `190MB`.

Note: If the array is assigned values with random indices, physical memory usage will differ significantly from predictions (because memory page loading is based on addresses, causing random assignments to load a large number of memory pages).

Brief summary: As the proportion of accessed parts increases, physical memory approaches virtual memory (assuming no page reclamation).
- Too many elements inserted into STL containers.

- Often caused by an infinite loop that inserts elements into an STL container.

- It could also be that you've been hacked.

### Errors that cause the constant factor to be too large

- Not defining the modulus as a constant.

- Example:

```cpp
// int mod = 998244353; // Wrong
const int mod = 998244353; // Correct, convenient for the compiler to treat as a constant
```

- Using unnecessary recursion (tail recursion is not included here).

- Introducing a lot of extra computation when converting recursion to iteration.

### Errors that only affect the program when running locally

- Possible errors with file operations:

- During comparison testing, not closing the file pointer `fclose(fp)` before calling `fp = fopen()` again. This causes the process to have a large number of dangling file pointers.

- Not adding `.in`/`.out` to the filename in `freopen()`.

- Forgetting to `delete` or `free` after using heap memory.

## References and Notes

[^ref1]: [What is RSS and VSZ in Linux memory management - Stack Overflow](https://stackoverflow.com/questions/7880784/what-is-rss-and-vsz-in-linux-memory-management)

[^ref2]: [Need explanation on Resident Set Size/Virtual Size - Stack Overflow](https://unix.stackexchange.com/questions/35129/need-explanation-on-resident-set-size-virtual-size)

[^ref3]: [虚拟内存](https://zh.wikipedia.org/wiki/%E8%99%9A%E6%8B%9F%E5%86%85%E5%AD%98)

[^ref4]: [常驻集大小](https://zh.wikipedia.org/wiki/%E5%B8%B8%E9%A9%BB%E9%9B%86%E5%A4%A7%E5%B0%8F)
