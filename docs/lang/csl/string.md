author: johnvp22, Ir1d

## What Is `string`?

`std::string` is a class provided by the standard library `<string>` (note that this is not the C library `<string.h>`). It is essentially an alias for `std::basic_string<char>`.

## Why Use `string`?

C provides string operations, but strings can only be represented with character arrays. `string`, however, is a simple and easy-to-use class, and is widely used in OI contests. Compared with other STL containers, `string` has excellent constant factors, basically comparable to character arrays.

### `string` Can Allocate Space Dynamically

Like many STL containers, `string` can allocate space dynamically. This allows us to use `std::cin` directly for input, although it is also slower. It also means we generally do not need to worry about memory allocation.

### `string` Overloads Addition and Comparison Operators

The addition operator of `string` can directly concatenate two strings, or a string and a character. Similar to `std::vector`, `string` overloads comparison operators and compares lexicographically, so we can directly call `std::sort` to sort multiple strings.

## Usage

The following introduces basic `string` operations. For details, see the [C++ documentation](https://en.cppreference.com/w/cpp/string/basic_string).

### Declaration

```cpp
std::string s;
```

### Converting to a `char` Array

C also has many string functions, but their parameters are all `char` pointer types. For convenience, `string` has two member functions that can convert itself to a `char` pointer: `data()` and `c_str()`. They are almost the same, but it is best to use `c_str()`, because `c_str()` guarantees a terminating null character while `data()` does not. For example:

```cpp
printf("%s", s);          // Compilation error
printf("%s", s.data());   // Compiles, but is undefined behavior
printf("%s", s.c_str());  // Always outputs correctly
```

### Getting the Length

Many functions can return the length of a string:

```cpp
printf("The length of s is %zu", s.size());
printf("The length of s is %zu", s.length());
printf("The length of s is %zu", strlen(s.c_str()));
```

???+ note "Complexities of these functions"
    The complexity of `strlen()` is always linear in the string length.
    
    The complexity of `size()` and `length()` was not specified in C++98, and was specified as constant in C++11. On common compilers, these two functions have constant complexity even in C++98.

???+ warning "Warning"
    The return type of these three functions, as well as the `find` function mentioned below, is `size_t` (`unsigned long`). Therefore, these return values should not be directly compared or operated with negative numbers. Cast them when necessary.

### Finding the First Occurrence of a Character or String

The `find(str,pos)` function can be used to find the first occurrence of a character/string at or after `pos` in a string. If `pos` is omitted, it defaults to `0`. If no occurrence is found, it returns `string::npos`, which is defined as `-1` but still has type `size_t`/`unsigned long`.

Example:

```cpp
string s = "OI Wiki", t = "OI", u = "i";
int pos = 5;
printf("Character I first appears in s at position %lu\n", s.find('I'));
printf("Character a first appears in s at position %lu\n", s.find('a'));
printf("Character a first appears in s at position %d\n", s.find('a'));
printf("String t first appears in s at position %lu\n", s.find(t));
printf("Starting from position pos in s, string u first appears at position %lu", s.find(u, pos));
```

Output:

```text
Character I first appears in s at position 1
Character a first appears in s at position 18446744073709551615 // This is size_t(-1); the exact value depends on the platform.
Character a first appears in s at position -1 // Cast to int to output -1 normally
String t first appears in s at position 0
Starting from position pos in s, string u first appears at position 6
```

### Extracting a Substring

The `substr(pos, len)` function returns a string consisting of at most `len` characters starting from position `pos`. If the suffix starting at `pos` is shorter than `len`, it returns that suffix.

Example:

```cpp
string s = "OI Wiki", t = "OI";
printf("The substring of at most three characters starting from the fourth character of s is %s\n",
       s.substr(3, 3).c_str());
printf("The substring of at most three characters starting from the second character of t is %s",
       t.substr(1, 3).c_str());
```

Output:

```text
The substring of at most three characters starting from the fourth character of s is Wik
The substring of at most three characters starting from the second character of t is I
```

### Inserting/Deleting Characters or Strings

`insert(index,count,ch)` and `insert(index,str)` are common insertion functions. They respectively mean inserting character `ch` `count` times consecutively at `index`, and inserting string `str` at `index`.

The `erase(index,count)` function deletes `count` characters starting from position `index`, inclusive. If `count` is omitted, it deletes all characters from `index` onward.

Example:

```cpp
string s = "OI Wiki", t = " Wiki";
char u = '!';
s.erase(2);
printf("After deleting all characters from the third character of s, the resulting string is %s\n", s.c_str());
s.insert(2, t);
printf("After inserting string t at the third character of s, the resulting string is %s\n", s.c_str());
s.insert(7, 3, u);
printf("After inserting character u three times at the eighth character of s, the resulting string is %s",
       s.c_str());
```

Output:

```text
After deleting all characters from the third character of s, the resulting string is OI
After inserting string t at the third character of s, the resulting string is OI Wiki
After inserting character u three times at the eighth character of s, the resulting string is OI Wiki!!!
```

### Replacing Characters or Strings

`replace(pos,count,str)` and `replace(first,last,str)` are common replacement functions. They respectively mean replacing the substring of `count` characters starting from position `pos` with `str`, and replacing the substring starting at `first` inclusive and ending at `last` exclusive with `str`, where both `first` and `last` are iterators.

Example:

```cpp
string s = "OI Wiki";
s.replace(2, 5, "");
printf("After replacing characters 3 to 7 of s with an empty string, the resulting string is %s\n", s.c_str());
s.replace(s.begin(), s.begin() + 2, "NOI");
printf("After replacing the first two characters of s with NOI, the resulting string is %s", s.c_str());
```

Output:

```text
After replacing characters 3 to 7 of s with an empty string, the resulting string is OI
After replacing the first two characters of s with NOI, the resulting string is NOI
```
