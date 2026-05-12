author: Ir1d, cqnuljs, akakw1, MingqiHuang, Chrogeek, henrytbtrue, Planet6174, StudyingFather

## The Concept of Files

A file is a collection of related data gathered for a specific purpose. C/C++ treats every file as an ordered byte stream. Every file ends with an **end-of-file marker** (EOF). To operate on a file, a program should first open the file. Whenever a file is opened, remember to close it later; the file is associated with a stream, and this stream is essentially a byte sequence.

C/C++ divides files into text files and binary files. Text files are ordinary text files, which are the focus here. Binary files include files in special formats, executable code files, and so on.

## Steps for File Operations

1.  Open the file, point the file pointer to the file, and decide the file opening mode.  
2.  Read from or write to the file; these are the main operations used in contests, so other operations are omitted for now.  
3.  Close the file after using it.

## The `freopen` Function

### Function Introduction

This function redirects a specified input/output stream to a file in a specified mode. It is declared in the header `stdio.h (cstdio)`. It can change the input/output environment without changing the original structure of the code, but you should ensure that the stream is reliable when using it.

The main modes are reading, writing, and appending.

### Syntax

```cpp
FILE* freopen(const char* filename, const char* mode, FILE* stream);
```

### Parameter Description

-   `filename`: the name of the file to open
-   `mode`: the file opening mode, indicating the file access permissions
-   `stream`: a file pointer, usually a standard file stream (`stdin/stdout`) or the standard error stream (`stderr`)
-   Return value: a file pointer pointing to the opened file

### File Opening Modes (Optional)

-   `r`: open a file for reading only; the file must exist and only input is allowed **(commonly used)**
-   `r+`: open a file for reading/writing; the file must exist and both input and output are allowed
-   `rb`: open a binary file for reading only; the file must exist and only input is allowed
-   `rb+`: open a binary file for reading/writing; the file must exist and both input and output are allowed
-   `rt+`: open a text file for reading/writing; both input and output are allowed
-   `w`: open a file for writing only; create it if it does not exist, otherwise clear its contents; only output is allowed **(commonly used)**
-   `w+`: open a file for reading/writing; create it if it does not exist, otherwise clear its contents; both input and output are allowed
-   `wb`: open a binary file for writing only; create it if it does not exist, otherwise clear its contents; only output is allowed
-   `wb+`: open a binary file for reading/writing; create it if it does not exist, otherwise clear its contents; both input and output are allowed
-   `a`: open a file for writing only; create it if it does not exist; written data is appended to the end of the file (preserving the EOF marker)
-   `a+`: open a file for reading/writing; create it if it does not exist; written data is appended to the end of the file (not preserving the EOF marker)
-   `at+`: open a text file for reading/writing; written data is appended to the end of the file
-   `ab+`: open a binary file for reading/writing; written data is appended to the end of the file

### Usage

Read file contents:

```cpp
freopen("data.in", "r", stdin);
// data.in is the file to read; it should be in the same directory as the executable
```

Output to a file:

```cpp
freopen("data.out", "w", stdout);
// data.out is the output file; it is in the same directory as the executable
```

Close the standard input/output streams:

```cpp
fclose(stdin);
fclose(stdout);
```

??? note "Note"
    Functions such as `printf/scanf/cin/cout` use `stdin/stdout` by default. After redirecting `stdin/stdout`, these functions read from or write to the redirected files.

### Template

```cpp
#include <cstdio>
#include <iostream>

int main(void) {
  freopen("data.in", "r", stdin);
  freopen("data.out", "w", stdout);
  /*
  The code in the middle does not need to change; just use cin and cout directly
  */
  fclose(stdin);
  fclose(stdout);
  return 0;
}
```

## The `fopen` Function (Optional)

This function is roughly the same as `freopen`. It opens the specified file and returns a pointer to the opened file.

### Function Prototype

```cpp
FILE* fopen(const char* path, const char* mode)
```

The meanings of the parameters are the same as for `freopen`.

### Available Read/Write Functions (Basic)

-   `fread/fwrite`
-   `fgetc/fputc`
-   `fscanf/fprintf`
-   `fgets/fputs`

### Usage

```cpp
FILE *in, *out;  // Define file pointers
in = fopen("data.in", "r");
out = fopen("data.out", "w");
/*
do what you want to do
*/
fclose(in);
fclose(out);
```

## C++ `ifstream/ofstream` File Input/Output Streams

### Usage

Read file contents:

```cpp
ifstream fin("data.in");
// data.in is the relative or absolute path of the file to read
```

Output to a file:

```cpp
ofstream fout("data.out");
// data.out is the relative or absolute path of the output file
```

Close the standard input/output streams:

```cpp
fin.close();
fout.close();
```

### Template

```cpp
#include <fstream>
using namespace std;  // Both types are in the std namespace

ifstream fin("data.in");
ofstream fout("data.out");

int main(void) {
  /*
  In the code in the middle, just change cin to fin and cout to fout
  */
  fin.close();
  fout.close();
  return 0;
}
```

## References

1.  Informatics Olympiad: A Beginner's Guide
