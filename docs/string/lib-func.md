author: Frankaiyou, henrytbtrue, zymooll

## C Standard Library

The C standard library operates on character arrays `char[]`/`const char*`.

See: [fprintf](https://en.cppreference.com/w/c/io/fprintf), [fscanf](https://en.cppreference.com/w/c/io/fscanf), [Null-terminated byte string](https://en.cppreference.com/w/c/string/byte)

-   `printf("%s", s)`: Use `%s` to output a string (character array).
-   `scanf("%s", &s)`: Use `%s` to read in a string (character array).
-   `sscanf(const char *__source, const char *__format, ...)`: Read variables from the string `__source`, for example `sscanf(str,"%d",&a)`.
-   `sprintf(char *__stream, const char *__format, ...)`: Output the contents of the `__format` string to `__stream`, for example `sprintf(str,"%d",i)`.
-   `strlen(const char *str)`: Returns the number of characters from `str[0]` until `'\0'`. Note that when O2 optimization is not enabled, placing this operation in a loop condition has complexity $\Theta(N)$.
-   `strcmp(const char *str1, const char *str2)`: Compares `str1` and `str2` lexicographically. Returns a negative value if `str1` is lexicographically smaller, returns `0` if they are equal, and returns a positive value if `str1` is lexicographically larger. Note that the return value is not simply `0`, `1`, or `-1`; on different platforms, the return values follow positive/negative but are not necessarily `0`, `1`, or `-1`.
-   `strcpy(char *str, const char *src)`: Copies characters from `src` to `str`, both `str` and `src` are the head pointers of character arrays, returns `str` including the null terminator `'\0'`.
-   `strncpy(char *str, const char *src, int cnt)`: Copies at most `cnt` characters to `str`. If `src` terminates before reaching `cnt`, it writes null characters to `str` until a total of `cnt` characters have been written.
-   `strcat(char *str1, const char *str2)`: Appends `str2` to the end of `str1`, uses `*str2` to replace the `'\0'` at the end of `str1`, returns `str1`.
-   `strstr(char *str1, const char *str2)`: If `str2` is a substring of `str1`, returns the address of the first occurrence of `str2` in `str1`; if `str2` is not a substring of `str1`, returns `NULL`.
-   `strchr(const char *str, int c)`: Finds the first occurrence of character `c` in string `str` and returns the address of that position. Returns `NULL` if the character is not found.
-   `strrchr(const char *str, int c)`: Finds the last occurrence of character `c` in string `str` and returns the address of that position. Returns `NULL` if the character is not found.

## C++ Standard Library

The C++ standard library operates on string objects [`std::string`](../lang/csl/string.md), while also providing compatibility for character arrays.

See: [std::basic_string](https://en.cppreference.com/w/cpp/string/basic_string), [std::basic_string_view](https://en.cppreference.com/w/cpp/string/basic_string_view)

-   The assignment operator `+` is overloaded. When both sides of `+` are of type `string/char/char[]/const char*`, these two variables can be concatenated, returning the concatenated string (`string`).
-   The right side of the assignment operator `=` can be `const string/string/const char*/char*`.
-   The access operator `[cur]` returns a reference to the character at position `cur`.
-   The accessor functions `data()/c_str()` return a `const char*` pointer with content identical to that `string`.
-   The capacity function `size()` returns the number of characters in the string.
-   `find(ch, start = 0)` finds and returns the position of character `ch` starting from `start`; `rfind(ch)` starts from the end, finds and returns the first position of character `ch` (both start from `0`) (if not found, returns `-1`).
-   `substr(start, len)` extracts a string of length `len` starting from `start` (starting from `0`) (if `len` is omitted, it extracts to the end of the string).
-   `append(s)` appends `s` to the end of the string.
-   `append(s, pos, n)` appends `n` characters from string `s` starting at `pos` to the end of the current string.
-   `replace(pos, n, s)` deletes `n` characters starting from `pos`, then inserts string `s` at position `pos`.
-   `erase(pos, n)` deletes `n` characters starting from `pos`.
-   `insert(pos, s)` inserts string `s` at position `pos`.
-   `std::string` overloads comparison operators, with complexity $\Theta(N)$.