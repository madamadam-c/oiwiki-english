author: xingjiapeng, MingqiHuang

Geany is a lightweight and convenient editor, which is relatively friendly for beginners in Linux environments.

Like Dev-C++, it can compile and run single files.

However, it can run on Linux/Windows/macOS.

Its official website is: <https://geany.org/>

## Advantages and Disadvantages

### Advantages

1.  Lightweight;
2.  Can compile and run single files;
3.  Doesn't require much configuration;
4.  Cross-platform.

### Disadvantages

1.  Not many people use it;
2.  Has some permission issues on macOS Catalina[^1];
3.  When creating new files, there is no syntax highlighting by default. You need to manually switch the file type.

## Installation

See [Download | Geany](https://geany.org/download/)

## Usage Tips

### Switching File Type

Switch in *Document -> Set File Type*.

For C++ language, click *Document -> Set File Type -> Programming Languages -> C++ source file*, and you can see that the file has been converted to C++ syntax highlighting.

### Setting File Templates

Create a templates/files folder in the configuration file directory. Files created in it are template files. When you open Geany again, you can find it in *File -> New from Template*.

The configuration file directory can be found in the second and third lines of *Help -> Debugging Information*.

Here are the default template configuration directories for macOS and Linux:

-   System directory: `/usr/share/geany/templates/files/`
-   User directory: `~/.config/geany/templates/files/`[^2]

## Common Issues

### Compatible with Deepin Terminal

In *Preferences -> Tools -> Virtual Terminal*, modify the terminal command to:

```bash
deepin-terminal -x "/bin/sh" %c
```

Click the "Apply" button to finish.[^3]

## References and Notes

[^1]: See: <https://github.com/geany/geany/issues/2344>

[^2]: Source: <https://wiki.geany.org/config/templates>

[^3]: Source: Deepin Wiki <https://wiki.deepin.org/>