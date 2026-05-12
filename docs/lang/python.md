author: cmpute, Henry-ZHR, ranwen, abc1763613206, billchenchina, chinggg, ChungZH, CoelacanthusHex, countercurrent-time, Dong Tsing-hsuen, Early0v0, Enter-tainer, F1shAndCat, Great-designer, hensier, HeRaNO, Hszzzx, imba-tjd, Ir1d, ksyx, lingxier, LovelyBuggies, Marcythm, mgt, Mooos-MoSheng, NachtgeistW, ouuan, Rottenwooood, shawlleyw, shuzhouliu, sshwy, SukkaW, Suyun514, Tiphereth-A, tLLWtG, wineee, wxh06, Xeonacid, yusancky, zyouxam, zzjjbb, jiangmuran, CuriosityQiu

## About Python

Python is a widely used interpreted language. It provides efficient high-level data structures, supports simple and effective object-oriented programming, and can also be used in algorithm competitions.

### Advantages Of Python

-   Python is an **interpreted** language: it does not require compilation and linking, which reduces the number of operation steps to some extent.
-   Python is an **interactive** language: the Python interpreter supports interactive operation, so commands can be entered and executed directly in a terminal.
-   Python is **easy to learn and use**: it provides many data structures and also supports development of large programs.
-   Python is **highly compatible**: it supports Windows, macOS, and Unix operating systems.
-   Python is **practical**: from simple input/output to scientific computing and even large web applications, Python can be used to write suitable programs.
-   Python programs are **concise and readable**: Python code is usually shorter than code in other languages that implements the same function.
-   Python **supports extension**: Python is commonly implemented in C (CPython), and the interpreter can be linked with applications written in C so Python can extend and control those applications.

### Notes On Learning Python

-   The currently common Python versions are Python 3.7 and later. Python 2 and Python 3.6 and earlier are [unsupported](https://devguide.python.org/versions/#unsupported-versions), although they may still appear in old systems and code. This article introduces newer Python versions. If you encounter Python 2 code, try using [`2to3`](https://docs.python.org/3/library/2to3.html) to convert it to Python 3.
-   Python's design philosophy and syntax differ greatly from many other languages. It hides many low-level details, which gives it a practical and elegant style.
-   Python is a highly dynamic interpreted language, so programs usually run relatively slowly, especially when using built-in `for` loops. When using Python, prefer built-in functions such as `filter` and `map`, or [list comprehensions](https://www.pythonforbeginners.com/basics/list-comprehensions-in-python), when they make the program clearer and faster.

## Environment Setup

See [Python 3](../tools/compiler.md#python-3), or use the following notes:

-   Windows: Python can also be obtained quickly and for free from Microsoft Store.
-   macOS/Linux: most Linux distributions already include Python. If you only want to learn Python syntax and have no other development needs, you usually do not need to install another Python.

    ???+ warning "Note"
        On some systems where Python is installed by default through a package manager, such as Unix systems, run `python3` in the terminal to open the Python 3 interpreter.[^ref1]

You can also use tools such as venv, conda, and Nix to manage Python toolchains and packages and create isolated virtual environments to avoid dependency problems.

As an interpreted language, Python runs differently from C++. This difference is often hidden when programming in an IDE, so it is worth emphasizing the different ways to run a program.

When you type `python3` on the command line, or just open IDLE, you enter an interactive programming environment called a REPL, the read-evaluate-print loop. Beginners can enter statements and immediately see results there, which makes it very easy to verify syntax. Many examples below use this form.

To write a complete program, create a text file, usually with the suffix `.py`, and run `python3 filename.py` on the command line.

### Python Versions Provided By Some Platforms

| System/version     | Python version              |
| ------------------ | --------------------------- |
| Noi Linux 2.0      | 3.8.0, includes requests    |
| Luogu judge        | 3.11.5, NumPy 1.25.2        |
| Hydro-based OJ     | 3.8.0+, includes NumPy      |
| Ubuntu 22.04 built-in | 3.10.4                  |
| Microsoft Store    | latest stable release       |

???+ warning "Note"
    This table was valid when this article was written (2025-01-15). Check the relevant platforms again before relying on it.

Mainland China mirrors for **source code** include the [Beijing Jiaotong University free and open-source software mirror](https://mirror.bjtu.edu.cn/python/) and the [Huawei open-source mirror](https://repo.huaweicloud.com/python/), where you can try downloading Python installers.

## Installing Third-Party Libraries With `pip`

Much of Python's vitality comes from its rich third-party libraries. Calling libraries is common when writing practical programs, and `pip` is the preferred program for installing third-party libraries. Since Python 3.4, it has been included by default in Python binary installers.

Third-party libraries used by `pip` are mainly stored on the [Python Package Index (PyPI)](https://pypi.org/), and users can specify other hosting platforms. For mirror usage, see help pages such as [PyPI mirror help - Tsinghua University open-source software mirror](https://mirrors.tuna.tsinghua.edu.cn/help/pypi/). More PyPI mirrors are listed on [MirrorZ](https://mirrorz.org/list/pypi).

???+ info "Install a package through the Tsinghua mirror"
    ```sh
    pip install -i https://mirrors.tuna.tsinghua.edu.cn/pypi/web/simple <some-package>
    ```

## Basic Syntax

Python syntax is concise and easy to understand, and there are many official and third-party documents and tutorials. This article only introduces language features that are useful to OIers. For more, see the [Python documentation](https://docs.python.org/3/) and the [Python Wiki](https://wiki.python.org/moin/).

### Comments

Adding comments does not affect code execution, but comments make code easier to understand and use.

```python
# Lines beginning with # are single-line comments.

"""
Multi-line strings use triple quotes
(three single quotes or three double quotes),
and are often used as comments.
"""
```

### Basic Data Types

#### Everything Is An Object

In Python, you do not need to declare a variable name or type in advance. Direct assignment creates variables of various types:

```pycon
>>> x = -3  # No semicolon is needed at the end of a statement.
>>> f = 3.1415926535897932384626; f  # Semicolons are allowed, but rarely needed.
3.141592653589793
>>> s1 = "O"
>>> b = 'A' == 65  # 'A' and 65 are not the same type.
>>> b
False
>>> True + 1 == 2 and not False != 0
True
```

This does not mean Python has no types. The interpreter infers types from assignments and operations. Use the built-in function `type()` to inspect them:

```pycon
>>> type(x)
<class 'int'>
>>> type(f)
<class 'float'>
>>> type(s1)  # Do not name a string variable str, or the str object will be shadowed.
<class 'str'>
>>> type(b)
<class 'bool'>
```

???+ note "What are [built-in functions](https://docs.python.org/3/library/functions.html)?"
    In C/C++, many common functions are distributed across different headers. Python's interpreter has many useful general-purpose functions built in, so you can use them directly. A small drawback is that many built-in function names are common words; avoid using the same names for your variables, or strange results may occur.

Python has built-in integer, floating-point, string, and Boolean types, similar to C++ `int`, `float`, `string`, and `bool`. There are clear differences: Python has no `char` type and no `double` type, although Python `float` corresponds to double precision in C. For more precise floating-point arithmetic, use the standard-library [decimal](https://docs.python.org/3/library/decimal.html) module. For complex numbers, Python has the built-in `complex` type.

These types all begin with `class`; this is key to Python's difference from C++. All data in a Python program is represented by objects or relationships between objects. Functions are objects, and types themselves are objects:

```pycon
>>> type(int)
<class 'type'>
>>> type(pow)  # Built-in exponentiation function.
<class 'builtin_function_or_method'>
>>> type(type)
<class 'type'>
```

These concepts may feel abstract at first. For now, remember that Python objects provide powerful methods, and Python code is often clearer when operations are organized around objects rather than procedures.

#### Numeric Operations

Python can be used as a powerful calculator. In interactive mode, enter expressions after `>>>` and use operators such as `+`, `-`, `*`, `/`, and `%`, together with parentheses. The examples below highlight differences from C++:

```pycon
>>> 5.0 * 6  # A calculation involving a float produces a float.
30.0
>>> 15 / 3  # Unlike C/C++, division always returns float.
5.0
>>> 5 / 100000
5e-05
>>> 5 // 3  # Integer division (floor division) rounds down.
1
>>> -5 // 3  # This differs from C/C++.
-2
>>> -5 % 3  # The modulo result for a negative number is non-negative.
1
>>> x = abs(-1e4)
>>> x += 1  # There are no increment/decrement operators.
>>> x
10001.0
```

Python uses `**` for exponentiation, and the built-in `pow(a, b, mod)` provides an efficient implementation of [binary exponentiation](../math/binary-exponentiation.md):

```pycon
>>> 3 ** 4
81
>>> pow(2, 512, int(1e4))  # Fast computation of 2**512 % 10000.
4096
>>> 0.1 + 0.1 + 0.1 - 0.3 == 0.  # Floating-point values should not be compared directly.
False
```

#### Type Checking

For a variable, `type(object)` returns its type. For example, `type(8)` is `<class 'int'>`, and `type('a')` is `<class 'str'>`.

#### [Basic Input And Output](https://docs.python.org/3/tutorial/inputoutput.html)

Python input/output is mainly done through the built-in functions `input()` and `print()`:

```pycon
>>> a = [1, 2, 3]; print(a[-1])  # print() adds a newline by default.
3
>>> print(1, 2)  # Multiple variables are separated by spaces by default.
1 2
>>> print(1, 2, end='')  # end='' avoids the trailing newline.
1 2>>>
>>> print(1, 2, sep=', ')  # sep changes the separator.
1, 2
```

`input()` is close to C++ `getline()`: it reads a whole line as a string, without the trailing newline.

```pycon
>>> s = input('Enter numbers: ')
Enter numbers: 1 2 3 4 5 6
```

#### Strings

Python 3 provides powerful [Unicode](https://docs.python.org/3/howto/unicode.html#unicode-howto)-based strings. They are similar to C++ `string`; escape characters, concatenation, indexing, repetition with `*`, and membership testing with `in` are all supported.

```pycon
>>> s1 = "OI-Wiki"
>>> 'OI' in s1
True
>>> len(s1)
7
>>> s2 = """ Thank you for reading
... Welcome to contribute!
... """
>>> print(s1 + s2)
OI-Wiki Thank you for reading
Welcome to contribute!
>>> s1[0] = 'o'
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: 'str' object does not support item assignment
```

Besides indexing, strings support *slicing*, written as `s[left-inclusive:right-exclusive:step]`:

```pycon
>>> s = 'OI-Wiki Thank you for reading\nWelcome to contribute!'
>>> s[:8]
'OI-Wiki '
>>> s[8:14]
'Thank '
>>> s[-4:]
'ute!'
>>> s[::-1]
'!etubirtnoc ot emocleW\ngnidaer rof uoy knahT ikiW-IO'
```

Python strings are Unicode strings.[^ref2] Use `ord()` to convert a Unicode character to its code point, and `chr()` for the reverse conversion. To convert numbers to strings, use `str()`; to convert strings to numbers, use `int()` or `float()`.

The string type provides many methods, such as finding indices and counts and changing case. See the [official documentation](https://docs.python.org/3/library/stdtypes.html#text-sequence-type-str) and prefer these methods over writing everything manually.

### Creating Arrays

Students coming from C++ may wonder how to create arrays in Python. This section introduces Python "array" syntax. More precisely, these are [sequence types](https://docs.python.org/3/library/stdtypes.html#iterator-types), which are fundamentally different from C arrays and closer to C++ `vector`.

#### Using `list`

The list (`list`) is probably Python's most common and most powerful sequence type. A list can contain elements of any type, including nested lists. Do not confuse it with C++ STL [`list`](./csl/sequence-container.md#list); this article calls it a "list".

```pycon
>>> []
[]
>>> nums = [0, 1, 2, 3, 5, 8, 13]
>>> nums[0] = 1
>>> nums.append(nums[-2] + nums[-1])
>>> nums.pop()
21
>>> nums.insert(0, 1)
>>> nums.remove(1)
>>> len(nums)
7
>>> nums.reverse()
>>> sorted(nums)
[1, 1, 2, 3, 5, 8, 13]
>>> nums.sort()
>>> nums.count(1)
2
>>> nums.index(1)
0
```

Common `vector` operations generally have corresponding list methods, although functions such as `len()` and `sorted()` are built-ins. See [More on Lists](https://docs.python.org/3/tutorial/datastructures.html#more-on-lists).

Lists are mutable sequences, so slicing can modify them flexibly:

```pycon
>>> lst = [1, '1'] + ["2", 3.0]
>>> 3 in lst
True
>>> lst[1:3] = [2, 3]
>>> lst[::-1]
[3.0, 3, 2, 1]
>>> lst *= 2
>>> del lst[4:]
```

[List comprehensions](https://docs.python.org/3/tutorial/datastructures.html#list-comprehensions) are often used to convert between strings and lists:

```pycon
>>> nums = list(range(65, 70))
>>> lst = [chr(x) for x in nums]
>>> ''.join(lst)
'ABCDE'
>>> list('ABCDE')
['A', 'B', 'C', 'D', 'E']
```

Be careful when creating two-dimensional lists:

```pycon
>>> vis = [[0] * 3] * 3
>>> vis[0][0] = 1
>>> vis
[[1, 0, 0], [1, 0, 0], [1, 0, 0]]
>>> vis1 = [[0] * 3 for _ in range(3)]
>>> vis1[0][0] = 1
>>> vis1
[[1, 0, 0], [0, 0, 0], [0, 0, 0]]
```

Assignment in Python passes references rather than creating new values. Lists are mutable, so modifying one reference to the same list affects all other references. Multiplication such as `[[0] * 3] * 3` repeats references to the same inner list. Use a list comprehension to create independent rows. For deep copying nested structures, use [`deepcopy`](https://docs.python.org/3/library/copy.html).

List comprehensions are introduced early because Python is highly dynamic and interpreted, so loops have considerable overhead. When performance matters, consider list comprehensions or built-ins such as `filter` and `map`, but decide based on the problem.

#### Using NumPy

??? note "What is NumPy"
    [NumPy](https://numpy.org/) is a famous Python scientific computing library that provides high-performance numerical and matrix operations. When testing algorithm prototypes, NumPy can avoid hand-written sorting, extrema, and similar operations. Its core data structure is `ndarray`, an n-dimensional fixed-length array stored contiguously in memory. NumPy is mainly written in C and is efficient, but it is not part of the standard library. Install it with `pip install numpy`; it may not be available in OI contest environments.

```pycon
>>> import numpy as np
>>> np.empty(3)
array([0.00000000e+000, 0.00000000e+000, 2.01191014e+180])
>>> np.zeros((3, 3))
array([[0., 0., 0.],
       [0., 0., 0.],
       [0., 0., 0.]])
>>> a1 = np.zeros((3, 3), dtype=int)
>>> a1[0, 0] = 1
>>> a1.shape
(3, 3)
>>> a1[:2, :2]
array([[1, 0],
       [0, 0]])
>>> np.max(a1)
1
>>> a1.flatten()
array([1, 0, 0, 0, 0, 0, 0, 0, 0])
```

#### Using `array`

[`array`](https://docs.python.org/3/library/array.html) is an efficient numeric array provided by the Python standard library. It compactly represents arrays of basic type values, but does not support nested arrays and is rarely used. Unless otherwise specified, "array" below means "list".

### [Input And Output](https://docs.python.org/3/tutorial/inputoutput.html)

Python input/output is mainly done through `input()` and `print()`. The basics were introduced earlier; this section covers more advanced usage.

#### Formatted Output

Algorithm competitions usually only require basic numeric and string output, so `print()` is generally enough. Formatting is needed when controlling floating-point digits. There are three methods: old `printf()`-style `%` formatting, the [`format` function](https://docs.python.org/3/library/string.html#formatstrings), and Python 3.6 [f-strings](https://docs.python.org/3/tutorial/inputoutput.html#formatted-string-literals). The following shows old-style formatting:

```pycon
>>> pi = 3.1415926; print('%.4f' % pi)
3.1416
>>> '%.4f - %8f = %d' % (pi, 0.1416, 3)
'3.1416 - 0.141600 = 3'
```

#### The `split()` Method

In competitions, one line often contains multiple numbers. Use the string method `split()` with a list comprehension:

```pycon
>>> s = input('Enter numbers: ')
Enter numbers: 1 2 3 4 5 6
>>> a = [int(x) for x in s.split()]
>>> sum(a) / len(a)
3.5
```

If every line contains a fixed number of values, use unpacking:

```pycon
>>> u, v, w = [int(x) for x in input().split()]
1 2 4
>>> print(u, v, w)
1 2 4
```

For multiple lines, sequence operations can often replace explicit loops:

```pycon
>>> N = 4; mat = [[int(x) for x in input().split()] for i in range(N)]
1 3 3
1 4 1
2 3 4
3 4 1
>>> u, v, w = map(list, zip(*mat))
>>> print(u, v, w)
[1, 1, 2, 3] [3, 4, 3, 4] [3, 1, 4, 1]
```

The program reads an $N \times 3$ matrix, transposes it to a $3 \times N$ matrix, and assigns the three lists to `u`, `v`, and `w`. Built-ins [`zip()`](https://docs.python.org/3/library/functions.html#zip) and [`map()`](https://docs.python.org/3/library/functions.html#map) return iterators in Python 3; wrap them in `list()` when a list is needed.

#### [File I/O](https://docs.python.org/3/reference/compound_stmts.html#the-with-statement)

Use the built-in [`open()`](https://docs.python.org/3/library/functions.html#open) for file I/O. To avoid files not being closed correctly after errors, prefer [`with`](https://docs.python.org/3/reference/compound_stmts.html#the-with-statement):

```python
a = []
with open("in.txt") as f:
    N = int(f.readline())
    a[len(a) :] = [[int(x) for x in f.readline().split()] for i in range(N)]

with open("out.txt", "w") as f:
    f.write("1\n")
```

There are many file I/O functions for different scenarios. Since OI contests generally do not support Python, they are omitted here.

### [Control Flow](https://docs.python.org/3/tutorial/controlflow.html)

Python code uses indentation instead of `{}` for block structure. Incorrect indentation, or mixing tabs and spaces, causes errors. Lines that start block structures, such as `if` and `for`, end with a colon `:`.

#### Loops

```python
u, v, w = ([] for i in range(3))
for i in range(4):
    _u, _v, _w = [int(x) for x in input().split()]
    u.append(_u), v.append(_v), w.append(_w)
print(u, v, w)
```

Python `for` loops differ greatly from C/C++. They are similar to C++11 [range-based for loops](./new.md#range-based-for-loops): they iterate over elements in a sequence. To traverse indices, iterate over `range(len(lst))`.

```python
u, v, w = [], [], []
s = input()
while s:
    u[len(u) :], v[len(v) :], w[len(w) :] = [[int(x)] for x in s.split()]
    s = input()

while s := input():
    u[len(u) :], v[len(v) :], w[len(w) :] = [[int(x)] for x in s.split()]
print(u, v, w)
```

The walrus operator `:=` was introduced in Python 3.8 and may not be available in all contest environments.

#### Branching

Python conditions are broadly similar to C/C++. Assignment is not allowed in conditional expressions, except for `:=` in Python 3.8+, and Python has [no switch statement](https://docs.python.org/3/faq/design.html#why-isn-t-there-a-switch-or-case-statement-in-python).

```python
if 4 >= 3 > 2 and 3 != 5 == 5 != 7:
    print("Comparison operators can be chained")
    x = None or [] or -2
    print("&&  ||  !", "and  or  not", "and or not", sep="\n")
    if not x:
        print("Negative numbers are also True")
    elif x & 1:
        print("Use elif instead of else if")
    else:
        print("Python also has conditional expressions") if x else print("Watch the structure")
```

#### Exception Handling

Python commonly uses the [EAFP](https://docs.python.org/3/glossary.html#term-eafp) style, so [`try-except`](https://docs.python.org/3/reference/compound_stmts.html#the-try-statement) often appears:

```python
s = "OI-wiki"
pat = "NOIP"
x = s.find(pat)
try:
    y = s.index(pat)
    print(y)
except ValueError:
    print("Not found")
    try:
        print(y)
    except NameError as e:
        print("Cannot output y")
        print("Reason:", e)
```

### Built-In Containers

Python has many powerful container types. Besides `list`, important built-ins include `tuple`, [`dict`](https://docs.python.org/3/library/stdtypes.html#mapping-types-dict), and `set`.

A tuple is an immutable list-like sequence. If a tuple contains a mutable object such as a list, that list can still be modified because the tuple stores a reference. Tuples have low overhead and are [hashable](https://docs.python.org/3/glossary.html), which is useful for dictionaries and sets.

```python
tup = tuple([[1, 2], 4])
tup[0].append(3)
print(tup)
a, b = 0, "I-Wiki"
b, a = a, b
```

Dictionaries are like C++ STL [`map`](./csl/associative-container.md#map), but do not confuse them with Python's built-in [`map()`](https://docs.python.org/3/library/functions.html#map). They store key-value pairs and resemble [JSON](https://docs.python.org/3/library/json.html), but dictionary keys can be any hashable object.

```python
dic = {"key": "value"}
dic = {chr(i): i for i in range(65, 91)}
dic = dict(zip([chr(i) for i in range(65, 91)], range(65, 91)))
dic = {v: k for k, v in dic.items()}
dic = {k: v for k, v in sorted(dic.items(), key=lambda x: -x[1])}

print(dic["A"])
dic["a"] = 97
if "b" in dic:
    print(dic["b"])
else:
    dic["b"] = 98

try:
    cnter[key] += 1
except KeyError:
    cnter[key] = 1
```

A set is like C++ STL [`set`](./csl/associative-container.md#set). It does not store duplicate elements and can be regarded as a dictionary that stores only keys. Note that `{}` creates an empty dictionary, not an empty set.

### Writing Functions

Python functions do not need parameter or return types, which reduces code length for OI users.

```python
def add(a, b):
    return a + b


def add_no_swap(a, b):
    print("in func #1:", id(a), id(b))
    a += b
    b, a = a, b
    print("in func #2:", id(a), id(b))
    return a, b
```

#### Default Parameters

Default parameters are convenient but can be dangerous when they are mutable:

```python
def append_to(element, to=[]):
    to.append(element)
    return to


lst1 = append_to(12)
lst2 = append_to(42)
print(lst1, lst2)
```

The output is `[12, 42] [12, 42]`, not `[12] [42]`, because the default argument is evaluated only once when the function is defined. Use `None` as a placeholder:

```python
def append_to(element, to=None):
    if to is None:
        to = []
    to.append(element)
    return to
```

#### Type Annotations

Python is dynamically typed: the interpreter checks types at runtime and variables can change type. Python 3.5 introduced type annotations for function parameters and return values, but they are hints rather than runtime restrictions. Static checkers such as [PyCharm](https://www.jetbrains.com/pycharm/) and [Mypy](http://mypy-lang.org/) can use them.

```python
def headline(
    text,  # type: str
    width=80,  # type: int
    fill_char="-",  # type: str
):  # type: (...) -> str
    return f"{text.title()}".center(width, fill_char)
```

Variables can also be annotated. `__annotations__` stores annotations:

```pycon
>>> nothing: str
>>> nothing
NameError: name 'nothing' is not defined
>>> __annotations__
{'nothing': <class 'str'>}
```

## Decorators

A decorator is a function that accepts a function or method as its only parameter and returns a new function or method with additional behavior. In short, it adds functionality without modifying the original function code. See the [official documentation](https://docs.python.org/3/glossary.html#term-decorator).

Some decorators are very practical in contests. For example, [`lru_cache`](https://docs.python.org/3/library/functools.html#functools.lru_cache) automatically memoizes a function, which is useful for recursive algorithms.

`@lru_cache(maxsize=128,typed=False)`

-   It has two parameters: `maxsize` and `typed`. If omitted, `maxsize` defaults to 128 and `typed` defaults to `False`.
-   `maxsize` is the LRU cache capacity, the maximum number of return results that can be cached. If it is `None`, unlimited results can be cached.
-   If `typed` is `True`, arguments of different types are cached separately; for example, `f(3)` and `f(3.0)` are cached twice.

Example: optimizing Fibonacci computation with `lru_cache`:

```python
@lru_cache(maxsize=None)
def fib(n):
    if n < 2:
        return n
    return fib(n - 1) + fib(n - 2)
```

## Common Built-In Libraries

Here are built-in libraries that may be useful for algorithms. Search for details or read the [official documentation](https://docs.python.org/3/library/index.html).

| Library                                                             | Use                                      |
| ------------------------------------------------------------------- | ---------------------------------------- |
| [`array`](https://docs.python.org/3/library/array.html)             | fixed-length arrays                      |
| [`argparse`](https://docs.python.org/3/library/argparse.html)       | command-line argument processing         |
| [`bisect`](https://docs.python.org/3/library/bisect.html)           | binary search                            |
| [`collections`](https://docs.python.org/3/library/collections.html) | ordered dictionaries, deques, and more   |
| [`fractions`](https://docs.python.org/3/library/fractions.html)     | rational numbers                         |
| [`heapq`](https://docs.python.org/3/library/heapq.html)             | heap-based priority queues               |
| [`io`](https://docs.python.org/3/library/io.html)                   | file streams and memory streams          |
| [`itertools`](https://docs.python.org/3/library/itertools.html)     | iterators                                |
| [`math`](https://docs.python.org/3/library/math.html)               | mathematical functions                   |
| [`os.path`](https://docs.python.org/3/library/os.html)              | system paths and related operations      |
| [`random`](https://docs.python.org/3/library/random.html)           | random numbers                           |
| [`re`](https://docs.python.org/3/library/re.html)                   | regular expressions                      |
| [`struct`](https://docs.python.org/3/library/struct.html)           | converting structs and binary data       |
| [`sys`](https://docs.python.org/3/library/sys.html)                 | system information                       |

## Comparing C++ And Python Through An Example

??? note "[Example: Luogu P4779 Shortest Path Template (Standard Version)](https://www.luogu.com.cn/problem/P4779)"
    Given a directed graph with $n(1 \leq n \leq 10^5)$ vertices and $m(1 \leq m \leq 2\times 10^5)$ non-negative weighted edges, compute the distance from $s$ to every vertex. The data guarantees that every vertex is reachable from $s$.

### Complete Code

=== "C++"
    ```cpp
    #include <cstdio>
    #include <cstring>
    #include <queue>
    #include <vector>
    using namespace std;
    constexpr int N = 1e5 + 5, M = 2e5 + 5;
    
    struct qxx {
      int nex, t, v;
    };
    
    qxx e[M];
    int h[N], cnt;
    
    void add_path(int f, int t, int v) { e[++cnt] = qxx{h[f], t, v}, h[f] = cnt; }
    
    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    int dist[N];
    
    void dijkstra(int s) {
      memset(dist, 0x3f, sizeof(dist));
      dist[s] = 0, q.push(make_pair(0, s));
      while (q.size()) {
        pii u = q.top();
        q.pop();
        if (dist[u.second] < u.first) continue;
        for (int i = h[u.second]; i; i = e[i].nex) {
          const int &v = e[i].t, &w = e[i].v;
          if (dist[v] <= dist[u.second] + w) continue;
          dist[v] = dist[u.second] + w;
          q.push(make_pair(dist[v], v));
        }
      }
    }
    
    int n, m, s;
    
    int main() {
      scanf("%d%d%d", &n, &m, &s);
      for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_path(u, v, w);
      }
      dijkstra(s);
      for (int i = 1; i <= n; i++) printf("%d ", dist[i]);
      return 0;
    }
    ```

=== "Python"
    ```python
    try:
        import Queue as pq
    except ImportError:
        import queue as pq
    
    N = int(1e5 + 5)
    M = int(2e5 + 5)
    INF = 0x3F3F3F3F
    
    class qxx:
        def __init__(self):
            self.nex = 0
            self.t = 0
            self.v = 0
    
    e = [qxx() for i in range(M)]
    h = [0 for i in range(N)]
    cnt = 0
    dist = [INF for i in range(N)]
    q = pq.PriorityQueue()
    
    def add_path(f, t, v):
        global cnt, e, h
        cnt += 1
        e[cnt].nex = h[f]
        e[cnt].t = t
        e[cnt].v = v
        h[f] = cnt
    
    def nextedgeid(u):
        i = h[u]
        while i:
            yield i
            i = e[i].nex
    
    def dijkstra(s):
        dist[s] = 0
        q.put((0, s))
        while not q.empty():
            u = q.get()
            if dist[u[1]] < u[0]:
                continue
            for i in nextedgeid(u[1]):
                v = e[i].t
                w = e[i].v
                if dist[v] <= dist[u[1]] + w:
                    continue
                dist[v] = dist[u[1]] + w
                q.put((dist[v], v))
    
    if __name__ == "__main__":
        n, m, s = map(int, input().split())
        for i in range(m):
            u, v, w = map(int, input().split())
            add_path(u, v, w)
        dijkstra(s)
        for i in range(1, n + 1):
            print(dist[i], end=" ")
        print()
    ```

## Reference Documents

1.  [Python Documentation](https://www.python.org/doc/)
2.  [The Python Tutorial](https://docs.python.org/3/tutorial/)
3.  [Learn Python3 In Y Minutes](https://learnxinyminutes.com/docs/python3/)
4.  [Real Python Tutorials](https://realpython.com/)
5.  [Liaoxuefeng's Python tutorial](https://www.liaoxuefeng.com/wiki/1016959663602400/)
6.  [GeeksforGeeks: Python Tutorials](https://www.geeksforgeeks.org/python-programming-language/)

## References And Notes

[^ref1]: [2. Using the Python Interpreter - Python 3 documentation](https://docs.python.org/3/tutorial/interpreter.html#using-the-python-interpreter)

[^ref2]: [Unicode HOWTO - Python 3 documentation](https://docs.python.org/3/howto/unicode.html#the-string-type)
