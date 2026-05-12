author: Marcythm, YZircon, Chaigidel, Tiger3018, voidge, H-J-Granger, ouuan, Enter-tainer, lcfsih, Xeonacid, Ir1d

This article introduces how to optimize stream-based I/O and C-style I/O.

???+ note "Note"
    The actual speed of stream-based I/O and C-style I/O varies with the environment, such as the compiler, operating system, and hardware specifications. For further analysis, rely on experimental results. However, pay attention to controlling variables in experiments to avoid incorrect conclusions caused by multiple variables.

## Stream-based I/O

For stream-based I/O, such as `std::cin` and `std::cout`, the most commonly used optimization methods are disabling synchronization with C streams and untieing the input and output streams.

### Disabling synchronization

Use the [`std::ios::sync_with_stdio(false)`](https://en.cppreference.com/w/cpp/io/ios_base/sync_with_stdio) function to disable synchronization with C streams. For compatibility with C, that is, to ensure that a program does not behave incorrectly when it uses both `printf` and `std::cout`, C++ synchronizes these two kinds of streams. Synchronized C++ streams are guaranteed to be thread-safe.

This is actually a conservative measure taken by C++ for compatibility. If synchronization is enabled, every I/O operation on a C++ stream is immediately applied to the corresponding C buffer. If the code does not involve C-style I/O, this operation is redundant. Therefore, synchronization with C streams can be disabled before performing I/O operations. After doing so, however, note that subsequent code must not use both `std::cin` and `scanf`, nor both `std::cout` and `printf`; using both `std::cin` and `printf`, or both `scanf` and `std::cout`, is allowed.

### Untieing streams

Use the [`tie()`](https://en.cppreference.com/w/cpp/io/basic_ios/tie) function to untie the input stream from the output stream.

By default, `std::cin` is tied to `&std::cout`, so `std::cout.flush()` is called to clear the output buffer every time formatted input is performed, increasing the I/O burden. You can untie them with `std::cin.tie(nullptr)` to further improve execution efficiency.

???+ warning "Note"
    When using it, do not omit the argument and write `std::cin.tie()`. That does not untie the stream; instead, it returns the output stream tied to `std::cin`. There is also no need to call `std::cout.tie(nullptr)`, because by default no other output stream is tied to `std::cout`.

### Code implementation

```cpp
std::ios::sync_with_stdio(false);
std::cin.tie(nullptr);
```

???+ note "Note"
    After performing both operations above, the program must manually `flush` to ensure that the content displayed by `std::cout` appears before `std::cin` each time. This is because, in this situation, calling `std::cin` will not automatically flush the `std::cout` buffer. For example:
    
    ```cpp
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << "Please input your name: "
              << std::flush;  // Or: std::endl;
                              // because every call to std::endl flushes the output buffer,
                              // while \n does not.
    // If std::flush is removed, the prompt will not be displayed before the name is input.
    std::cin >> name;
    ```

## C-style I/O

There is still room to improve the efficiency of `scanf` and `printf`. The improvement methods are all based on conversion between integers and strings.

???+ note "Note"
    The input and output optimizations introduced on this page are all for integer data. Optimizing floating-point input and output is very complex. For input-related optimization, refer to the [Bellerophon algorithm](https://dl.acm.org/doi/10.1145/93542.93557); for output-related optimization, refer to the [Ryū algorithm](https://dl.acm.org/doi/10.1145/3192366.3192369).

### Implementation design

???+ note "Note"
    The current optimization methods focus on faster I/O, while naive methods are used in the data conversion process and hardware features are not fully utilized. Nowadays, most x86 CPUs support the AVX2 instruction set, and SIMD can be used to accelerate conversion between integers and strings. Standard library functions do not use SIMD optimization. For example, the libstdc++ [implementation](https://github.com/gcc-mirror/gcc/blob/releases/gcc-14.3.0/libstdc%2B%2B-v3/include/bits/charconv.h#L81) converts two consecutive digits at a time and converts them to characters by table lookup, so optimizing the data conversion process may also bring benefits. However, in the context of programming contests, the optimization methods mentioned in this article are sufficient for most scenarios.

#### Input optimization

Each integer consists of a sign part and a digit part, and the sign must appear before the digit part, so the sign part is read first. For the sign part, the `+` of a positive integer is usually omitted and does not affect the value represented by the following digits, while `-` cannot be omitted and therefore must be checked. If the input does not contain negative integers, this check can be omitted. The digit part contains only digits from 0 to 9, so when a character that should not appear in an integer is read, usually a space, it can be determined that this integer has finished being read.

When reading, digits are read from left to right, which is exactly suitable for using Horner's method for integer conversion. Therefore, the entire conversion process can be combined with input.

When reading the digit part, it is necessary to determine whether the character read is a decimal digit character. This can be checked simply with the condition `ch >= '0' && ch <= '9'`, or by using the [`isdigit()`](https://en.cppreference.com/w/cpp/string/byte/isdigit) function.

#### Output optimization

When outputting, integers need to be converted to strings. A naive algorithm is generally used: directly compute each digit of the integer from low to high, convert it to a character, and then output the characters in reverse order.

### Implementation details

#### Integer overflow issues

Pay attention to integer overflow during implementation. For example, in output optimization, improperly negating a value can cause the minimum value of an integer type to exceed the maximum value representable by that type after negation, which may lead to incorrect output. Similar overflow may also occur when reading the minimum value of an integer type, but in this case it may not cause incorrect input data, because the overflowed value may be equal to the actual input value.

Signed integer overflow is undefined behavior. During implementation, the property in C that division of negative integers rounds toward zero can be used to avoid the above problems. However, if there is no need to input or output negative numbers, or if it is impossible to input or output the minimum value of this integer type, this problem will not occur.

#### Improving implementation generality

If a program uses integer variables of multiple types, it may be necessary to implement multiple input and output functions with different types but the same logic. In this case, C++ [`template`](https://en.cppreference.com/w/cpp/language/templates.html) can be used to implement input and output optimization for all integer types. For example, use the following under the C++11 standard:

```cpp
template <typename T>
typename std::enable_if<std::is_integral<T>::value &&
                        std::is_signed<T>::value>::type
read(T &x);
```

Or use the following under the C++20 standard:

```cpp
template <std::signed_integral T>
void read(T &x);
```

to define the function.

For readability, the implementations below assume that only integers of type `int` need to be read. These implementations are sufficient for most problems.

### Implementation

Mainstream implementations differ only in the input and output functions they use; the integer conversion logic is the same. The following introduces each implementation according to the input and output functions it uses.

#### Implementation using `getchar` and `putchar`

The core code is as follows.

```cpp
--8<-- "docs/contest/code/io/io_1.cpp:core"
```

#### Implementation using `fread` and `fwrite`

Faster input and output can be achieved with `fread` and `fwrite`. Their function signatures are as follows.

```cpp
std::size_t fread(void* buffer, std::size_t size, std::size_t count,
                  std::FILE* stream);
std::size_t fwrite(const void* buffer, std::size_t size, std::size_t count,
                   std::FILE* stream);
```

For example, `fread(Buf, 1, SIZE, stdin)` means reading `SIZE` data blocks of 1 byte each from standard input into `Buf`. The return value indicates how many bytes of data were successfully read.

Because `fread` and `fwrite` read and write whole blocks, they have a speed advantage over `getchar()` and `putchar()`. If the buffer is large enough, the entire file can be read at once. If the buffer is not large enough, multiple reads are needed to ensure that all input content is read. To implement this, only `getchar` needs to be redefined.

```cpp
char buf[1 << 20], *p1, *p2;
#define gc()                                                               \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) \
       ? EOF                                                               \
       : *p1++)
```

Output is similar to input: first put the output content into a buffer, and finally use `fwrite` to output the contents of the buffer all at once.

The core code is as follows.

```cpp
--8<-- "docs/contest/code/io/io_2.cpp:core"
```

When using this method, note the following:

-   When the debug switch is off, use `fread()` and `fwrite()`, and automatically call `fwrite()` through destruction on exit. When the debug switch is on, use `getchar()` and `putchar()` to make debugging easier.
-   If file input and output are needed, add `freopen()` before all reads and writes.

#### Implementation using `mmap`

`mmap` is a Linux system call that can map a file into memory all at once, similar to a memory region that can be referenced by pointers, and it can be faster in some scenarios. Its function signature is as follows:

```c
void *mmap(void addr[.length], size_t length, int prot, int flags, int fd,
           off_t offset);
```

???+ warning "Note"
    `mmap` cannot be used in Windows environments, such as the judging systems of CodeForces and HDU, and it is also not recommended for use in official contests. In practice, `fread` is already fast enough. Moreover, if `mmap` is used to repeatedly read a small file block, the overhead of performing a memory mapping and having the kernel handle page faults is much greater than the overhead of using `fread`.

First obtain the file descriptor `fd`, then obtain the file size with `fstat`, and then obtain the pointer `*pc` to the file mapped into memory through `mmap`. After that, `*pc++` can be used directly instead of `getchar()` to read the file.

If input needs to be read from standard input, `fd` can be set to `0`. **However, using mmap on standard input is extremely dangerous. It also cannot be used for terminal input; instead, redirect a file to standard input.**

???+ note "例题：[洛谷 P10815【模板】快速读入](https://www.luogu.com.cn/problem/P10815)"
    Read $n$ integers in the range $[-n, n]$, compute their sum, and output it. Here $n \leq 10^8$. The data guarantees that for any prefix of the sequence, the sum of that prefix is within the storage range of a $32$-bit signed integer.

The reference code is as follows.

```cpp
--8<-- "docs/contest/code/io/io_3.cpp"
```

## References

[cin.tie 与 sync\_with\_stdio 加速输入输出 - 码农场](https://www.hankcs.com/program/cpp/cin-tie-with-sync_with_stdio-acceleration-input-and-output.html)

[C++ 高速化 - Heavy Watal](https://heavywatal.github.io/cxx/speed.html)

['Re: mmap/mlock performance versus read' - MARC](https://marc.info/?l=linux-kernel&m=95496636207616&w=2)
