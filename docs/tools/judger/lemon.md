author: Ir1d, HeRaNO, NachtgeistW, i-Yirannn, bear-good, ranwen, CoelacanthusHex, billchenchina, Tiger3018, Xeonacid

## Lemon

???+ warning "Warning"
    On macOS, Lemon may have inaccurate memory testing, because macOS lacks some Linux monitoring tools, and Lemon-Linux has not been optimized for macOS.

**Lemon** is an open-source judging tool written by zhipeng-jia, with source code hosted at [zhipeng-jia/project-lemon](https://github.com/zhipeng-jia/project-lemon).

### Ready-to-Run Versions

-   Ir1d provides a pre-compiled version for Linux, with source code hosted at [FreestyleOJ/Project\_lemon](https://github.com/FreestyleOJ/Project_lemon/tree/Built).
-   (No longer maintained) Menci provides an updated version, with source code hosted at [Menci/Lemon](https://github.com/Menci/Lemon/).
-   (No longer maintained) Dust1404 maintains a version that supports subfolders and single-problem testing, with source code hosted at [Dust1404/Project\_LemonPlus](https://github.com/Dust1404/Project_LemonPlus).
-   iotang and Coelacanthus maintain a version that supports subfolders and single-problem testing, with source code hosted at [Project-LemonLime/Project\_LemonLime](https://github.com/Project-LemonLime/Project_LemonLime).

### Compiling from Source

Ubuntu:

```bash
sudo apt update
sudo apt install qt5-default build-essential git -y
git clone --depth=1 https://github.com/Menci/Lemon.git
cd lemon
# You can modify the number after -j to adjust the number of make job threads
./make -j2
sudo install -Dm755 -t /usr/bin/ Lemon
```

To compile LemonLime, please refer to LemonLime's [Build Manual](https://github.com/Project-LemonLime/Project_LemonLime/blob/master/BUILD.md).

### Data Format

First open lemon and select "New Problem", then open the folder of the newly created problem.

The problems and data should be in the following format:

```text
├── data
│   ├── gendata.py
│   ├── product
│   │   ├── product100.in
│   │   ├── product100.out
│   │   ├── product10.in
│   │   ├── product10.out
│   │   ├── product11.in
...
```

When all problems have been added, go back to lemon and select "Auto Add Problems". At this point, the problems and test points will be displayed in lemon.