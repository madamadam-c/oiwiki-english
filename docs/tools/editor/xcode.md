author: shenyouran, Xeonacid, StudyingFather, CoelacanthusHex

## Introduction

Xcode is an integrated development tool (IDE) running on macOS, developed by Apple Inc.

## Installation

### Method 1

Open the built-in App Store on Apple computers (or try [quick link](https://apps.apple.com/cn/app/xcode/id497799835?mt=12)) to download Xcode. Click Get, then enter your Apple account password to start downloading and installing.

![](images/xcode-1.jpg)

### Method 2

Visit [Apple Developer Download Page](https://developer.apple.com/download/more/), log in with your Apple account, then find the latest stable version of Xcode (the latest version without Beta, here is 11.6):

![](images/xcode-2.jpg)

Click the blue filename in the popup to download. After getting the compressed package, decompress it using the system's built-in tool, then get the file Xcode.app. Move this file to the 【Applications】 folder to use it.

## Basic Configuration

When you first open Xcode, you may encounter the following popup window:

![](images/xcode-3.jpg)

This window is the installation wizard for Xcode components. Click `Install` and enter the current user's password to install.

After installation, the left side of the interface shows:

![](images/xcode-4.jpg)

Click `Create a new Xcode project` (create a new Xcode project), then select `macOS` in the top and `Command Line Tool` (command line tool), and click `Next` in the bottom right.

![](images/xcode-5.jpg)

Next, we can name the project, but the most important thing is to select the project language. According to our needs, we can select C or C++ at the bottom `Language`:

![](images/xcode-6.jpg)

The project directory can be chosen as needed. After creation, Xcode will automatically open this project and automatically create a `main` file (C language suffix is `.c`, C++ language suffix is `.cpp`).

Click this file to open the editing area:

![](images/xcode-7.jpg)

After writing code, you can press ⌘B to compile (Build), ⌘R to run (Run). After running, drag to get three parts:

![](images/xcode-8.jpg)

Generally, we only use the 【Editing Area】 and 【Running Area】. If the program has input, then input in the 【Running Area】, after which you can get the output. The interface display effect:

![](images/xcode-9.jpg)

Following this method, we can run any single C/C++ program.

## Using the Header File

During code writing, we may use many header files. The common solution is to use a header file.

We introduce the header file on the first line of the source code. However, during compilation, it prompts: `'bits/stdc++.h' file not found`. That is, the header file was not found.

![](images/xcode-10.jpg)

This is because macOS uses [libc++](https://libcxx.llvm.org/) as the C++ standard library implementation by default, while the header file `bits/stdc++.h` is unique to [GNU libstdc++](https://gcc.gnu.org/onlinedocs/libstdc++/).

However, we can manually write a header file to use.

### Step 1

Open Terminal (Terminal.app), go to the folder where Xcode stores header files, namely:

```bash
cd /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1
```

If Xcode version is greater than or equal to 12.5, then

```bash
cd /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/
```

### Step 2

Create `bits` folder and enter:

```bash
mkdir bits
cd bits
```

Create stdc++.h file with vim:

```bash
vim stdc++.h
```

The interface is as follows:

![](images/xcode-11.jpg)

Next, we need to edit the file with vim. Press i (insert) keyboard to enter insert/edit mode ( `-- INSERT --` appears at the bottom):

![](images/xcode-12.jpg)

Copy and paste the following code block into the terminal:

??? note "Header File Code Block"
    ```cpp
    // C++ includes used for precompiling -*- C++ -*-
    
    // Copyright (C) 2003-2020 Free Software Foundation, Inc.
    //
    // This file is part of the GNU ISO C++ Library.  This library is free
    // software; you can redistribute it and/or modify it under the
    // terms of the GNU General Public License as published by the
    // Free Software Foundation; either version 3, or (at your option)
    // any later version.
    
    // This library is distributed in the hope that it will be useful,
    // but WITHOUT ANY WARRANTY; without even the implied warranty of
    // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    // GNU General Public License for more details.
    
    // Under Section 7 of GPL version 3, you are granted additional
    // permissions described in the GCC Runtime Library Exception, version
    // 3.1, as published by the Free Software Foundation.
    
    // You should have received a copy of the GNU General Public License and
    // a copy of the GCC Runtime Library Exception along with this program;
    // see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
    // <http://www.gnu.org/licenses/>.
    
    /** @file stdc++.h
     *  This is an implementation file for a precompiled header.
     */
    
    // 17.4.1.2 Headers
    
    // C
    #ifndef _GLIBCXX_NO_ASSERT
    #include <cassert>
    #endif
    #include <cctype>
    #include <cerrno>
    #include <cfloat>
    #include <ciso646>
    #include <climits>
    #include <clocale>
    #include <cmath>
    #include <csetjmp>
    #include <csignal>
    #include <cstdarg>
    #include <cstddef>
    #include <cstdio>
    #include <cstdlib>
    #include <cstring>
    #include <ctime>
    #include <cwchar>
    #include <cwctype>
    
    #if __cplusplus >= 201103L
    #include <ccomplex>
    #include <cfenv>
    #include <cinttypes>
    #include <cstdbool>
    #include <cstdint>
    #include <ctgmath>
    /* https://stackoverflow.com/a/25892335/15125422 */
    #if defined(__GLIBCXX__) || defined(__GLIBCPP__)
    #include <cstdalign>
    #include <cuchar>
    #endif
    #endif
    
    // C++
    #include <algorithm>
    #include <bitset>
    #include <complex>
    #include <deque>
    #include <exception>
    #include <fstream>
    #include <functional>
    #include <iomanip>
    #include <ios>
    #include <iosfwd>
    #include <iostream>
    #include <istream>
    #include <iterator>
    #include <limits>
    #include <list>
    #include <locale>
    #include <map>
    #include <memory>
    #include <new>
    #include <numeric>
    #include <ostream>
    #include <queue>
    #include <set>
    #include <sstream>
    #include <stack>
    #include <stdexcept>
    #include <streambuf>
    #include <string>
    #include <typeinfo>
    #include <utility>
    #include <valarray>
    #include <vector>
    
    #if __cplusplus >= 201103L
    #include <array>
    #include <atomic>
    #include <chrono>
    #include <codecvt>
    #include <condition_variable>
    #include <forward_list>
    #include <future>
    #include <initializer_list>
    #include <mutex>
    #include <random>
    #include <ratio>
    #include <regex>
    #include <scoped_allocator>
    #include <system_error>
    #include <thread>
    #include <tuple>
    #include <type_traits>
    #include <typeindex>
    #include <unordered_map>
    #include <unordered_set>
    #endif
    
    #if __cplusplus >= 201402L
    #include <shared_mutex>
    #endif
    
    #if __cplusplus >= 201703L
    #include <any>
    #include <charconv>
    // #include <execution>
    #include <filesystem>
    #include <memory_resource>
    #include <optional>
    #include <string_view>
    #include <variant>
    #endif
    
    #if __cplusplus > 201703L
    #include <bit>
    #include <compare>
    #include <concepts>
    #include <numbers>
    #include <ranges>
    #include <span>
    #include <stop_token>
    // #include <syncstream>
    #include <version>
    #endif
    ```

This file comes from [libstdc++ version 10.2.0](https://github.com/gcc-mirror/gcc/blob/ee5c3db6c5b2c3332912fb4c9cfa2864569ebd9a/libstdc++-v3/include/precompiled/stdc++.h) and has been slightly modified to be compatible with libc++.

Press the <kbd>Esc</kbd> key in the top left corner to exit edit mode, then directly input `:wq` and press Enter to save the file.

### Step 3

Close the terminal and return to Xcode. Press ⌘B/⌘R again to compile. It is found that the compilation is successful:

![](images/xcode-13.jpg)

## Advantages and Disadvantages

Advantages: Developed by Apple, suitable for Mac users, interface is complete and beautiful.

Disadvantages: Xcode is mainly used for Apple program development. For competitions, the functions are redundant, the installation package is large, and it can only be used on Mac.