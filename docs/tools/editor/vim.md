author: Enter-tainer, ouuan, Xeonacid, Ir1d, partychicken, ChungZH, LuoshuiTianyi, Kewth, s0cks5, Doveqise, StudyingFather, SukkaW, SodaCris, SkyeYoung, 383494, danielqfmai

Vim - The ubiquitous text editor.

## Introduction

Vim is a text editor developed from vi. Its code completion, compilation, and error jumping functions are particularly rich and convenient for programming, making it widely used among programmers.

## Installation

Linux systems usually come with Vim pre-installed. Open the terminal and type `vim` to start it.

If you need to install it manually, Vim's [official website](https://www.vim.org/) provides [documentation](https://www.vim.org/download.php) for downloading. Follow the instructions to compile and install according to your needs.

## Vim Modes and Common Keybindings

Vim's basic operations will be taught in the tutorial that comes with Vim. Open the terminal and type `vimtutor` to enter the tutorial.

These operations usually take twenty to thirty minutes to become familiar with.

### Command Mode

This is the default mode after entering Vim.

In this state, keystrokes are recognized by Vim as commands rather than inputting characters. For example, pressing <kbd>i</kbd> at this time will not input a character; <kbd>i</kbd> is treated as a command.

Vim's direction keys are <kbd>↑</kbd>, <kbd>↓</kbd>, <kbd>←</kbd>, <kbd>→</kbd>, or <kbd>h</kbd>, <kbd>j</kbd>, <kbd>k</kbd>, <kbd>l</kbd>.

```text
        ↑(k)
        ^
(h)← <     > →(l)
        v
        ↓(j)
```

Here are commonly used commands in command mode:

-   `i` Switch to insert mode, start inputting text at the current cursor position. Press <kbd>Esc</kbd> to return to normal mode.
-   `x` Delete the character after the cursor.
-   `:` Switch to command-line mode to input commands on the bottom line.
-   `a` Switch to insert mode, start inputting text after the cursor.
-   `o` Switch to insert mode, insert a new line below the cursor; `O` Switch to insert mode, insert a new line above the cursor.
-   `p` Paste clipboard content below the cursor; `P` Paste clipboard content above the cursor.
-   `dd` Delete the entire line where the cursor is located.
-   `d` The delete command, usually used with other keys.
-   `u` Undo the last change to the text.
-   `y` The yank command can copy the selected area. You need to press `v` to enter visual mode to operate.
-   `yy` Yank (copy) the current line.
-   `Ctrl + r` Redo the last undone operation.
-   `:w` Save the file, often used together with `q` to save and quit.
-   `:q` Quit Vim.
-   `:q!` Force quit Vim without saving changes.

Some other commands:

-   `c` The change command, equivalent to `di`.
-   `=` The command to apply auto-indent to selected lines with default format.
-   `==` Auto-indent the current line.
-   `.` The command to repeat the last executed command.
-   `gg` command can jump to the beginning of the code; `G` command can jump to the beginning of the last line of the code; adding a number before `G` command can jump to the specified line.
-   `w` can jump to the beginning of the next word; `e` can jump to the end of the current word or next word; `b` can jump to the beginning of the current word or previous word; `0` can jump to the beginning of the line; `$` can jump to the end of the line. `w`, `e`, `0`, `$` can also be combined with other commands, for example `de`, `dw`, `d0`, and `d$` correspond to deleting to the end of word, deleting to the beginning of next word, deleting to the beginning of line, and deleting to the end of line respectively.

In command mode, press <kbd>/</kbd>, and a search box will appear below. Enter the characters to search for and press Enter to view the search results. If there are multiple search results, press <kbd>n</kbd> to jump to the next search result; press <kbd>N</kbd> to jump to the previous one.

In command mode, press <kbd>\*</kbd> to search for the word under the current cursor.

If you input a number n before entering a command, the command will be repeated n times.

### Insert Mode

In command mode, press <kbd>i</kbd> to enter insert mode. Press <kbd>Esc</kbd> to return to command mode.

In insert mode, you can use the following keys:

-   Character keys and <kbd>Shift</kbd> combinations to input characters
-   <kbd>ENTER</kbd>, the Enter key, for newlines
-   <kbd>BACK SPACE</kbd>, the Backspace key, delete the character before the cursor
-   <kbd>DEL</kbd>, the Delete key, delete the character after the cursor
-   Arrow keys, move the cursor in the text
-   <kbd>HOME/END</kbd>, move cursor to beginning/end of line
-   <kbd>Page Up/Page Down</kbd>, scroll up/down
-   <kbd>Insert</kbd>, switch cursor between insert/replace mode, cursor becomes vertical line/underscore
-   <kbd>ESC</kbd>, exit insert mode, switch to command mode

In insert mode, press <kbd>Ctrl</kbd>+<kbd>o</kbd> to enter "Insert - Command Mode". After executing one operation, it will automatically return to insert mode.

### Command-line Mode

In command mode, press <kbd>:</kbd> to enter command-line mode.

Command-line mode can input single or multiple character commands, and there are many available commands.

In command-line mode, basic commands include:

-   `:help`/`:h` View the English Vim online help documentation.
-   `:w` Save the file.
-   `:q` Quit Vim.
-   `:wq` Save the file and quit Vim.
-   `:q!`/`:!q` Force quit Vim without saving changes.
-   `:e filename` Can open the specified file in the current directory.
-   `:s` The substitute command.

```vim
" Replace the first match of str1 with str2 on the current line
:s/str1/str2/
" Replace all str1 with str2 on the current line
:s/str1/str2/g
" Replace all str1 with str2 on the current line, ask before replacing
:s/str1/str2/gc
" Replace the first match of str1 with str2 in lines x1 to x2
:x1,x2 s/str1/str2/
" Replace all str1 with str2 in lines x1 to x2
:x1,x2 s/str1/str2/g
" Replace all str1 with str2 in lines x1 to x2, ask before replacing
:x1,x2 s/str1/str2/gc
" Replace the first match of str1 with str2 on all lines
:%s/str1/str2/
" Replace all str1 with str2 in the entire file
:%s/str1/str2/g
" Replace all str1 with str2 in the entire file, ask before replacing
:%s/str1/str2/gc
```

If the command form is `:! command`, the command will be executed in the bash terminal.

Press <kbd>Esc</kbd> to exit command-line mode.

### Visual Mode

Press `v` to enter visual mode, mostly used for selecting an area. Press `V` (`Shift+v`) to enter line visual mode, for selecting lines.

Press <kbd>Ctrl</kbd>+<kbd>v</kbd> or <kbd>Ctrl</kbd>+<kbd>q</kbd> to enter block visual mode.

After entering block visual mode, press <kbd>I</kbd> or <kbd>A</kbd> to enter insert mode (equivalent to `i` and `a`). After exiting insert mode, the changes made to this line will be applied to the same position in every selected line. Commonly used for batch adding comments.

After selection, input `y` or `d` to execute the corresponding command.

The three visual modes can be switched to each other via key presses.

## Vim Shortcuts

Refer to [The Ultimate Vim Cheat Sheet - From Beginner to Advanced](https://cenalulu.github.io/linux/all-vim-cheatsheat/)

## Advanced Knowledge

### The `.` Command

Vim users inevitably have to deal with repetitive text modifications, because Vim is destined to have two extra key presses compared to other editors - <kbd>Esc</kbd> and <kbd>i</kbd>. However, Vim provides the repeat command `.`, which applies to repetitive add, modify, and delete text operations.

The `.` command can repeat the last executed command. But this "command" is not limited to a single command; it can also be a combination of `number + command`; `enter insert mode + input text + Esc` is also a kind of command. Therefore, using the `.` command properly can achieve maximum efficiency.

For example, the following code is missing semicolons at the end of each line:

```text
int a, b
cin >> a >> b
cout << a + b
return 0
```

By using `.` combined with the move-to-end-of-line command `A`, you can efficiently add the missing semicolons.

```vim
A;<Esc>
" Repeat the following command
j.
```

Another example: in the following code, the array names of the last five assignment statements are all wrong:

```cpp
int check() {
  book[1] = 1, book[2] = 1, book[3] = 1, bok[1] = 1, bok[2] = 1, bok[3] = 1,
  bok[4] = 1, bok[5] = 1;
  return 0;
}
```

Changing them one by one is too troublesome, and the `s` command in command-line mode would change all of them.

The first method is to use it together with the `s` command in normal mode (delete the character at the cursor and enter insert mode). Go to the first letter of the wrong array name, press `3s`/`cw`, input the correct array name and exit. Then move the cursor one by one and use the `.` command.

The second method that saves more time is to use the search pattern for modification. Type `/bok`, then press Enter, and use the `n` key to go to the first letter of the wrong array name, type `3s new array name <Esc>`, finally repeat `n.`

The third method is the simple find command `f`. In normal mode on a line, `f + single character` can find this character appearing in the line and move the cursor to that character; press `;` to find the next one, `,` to find the previous one. So for the above code, just type `fb;;;` then enter insert mode to modify, then `;.` This method is suitable for situations where you only need to move within a line.

### Macros

Vim's macro function can repeat any length of command.

Before using macros, you need to "record", which is to record a series of key operations and then play them back, thus achieving the effect of repetition. The recording method is simple: in normal mode, press `q` to start recording. Next, assign an execution key for the recorded macro; you can press any of the 26 letters to specify. At this time, the bottom left will display "recording @the letter just selected". Then you can start recording commands. Similarly, in normal mode, press `q` to pause recording.

The usage method is to press `:` to enter command-line mode, type `@recorded letter`, and then the previously recorded commands will be invoked.

Combining `.` and macros, i.e., record macro → call macro → `.` repeat command → number + `.`, can achieve very high efficiency.

### The normal Command

This command is related to normal mode, and its effect is to repeat a command on specified lines.

Press `:` to enter command-line mode, input the following command:

```vim
:a,b normal command
```

Or:

```vim
:a,b norm command
```

The above commands mean executing `command` on lines a~b in normal mode.

Since the `normal` command can be repeated by the `.` command, and it is easy to understand, its usage frequency is even higher than macros.

### Number + `.` + Macro + normal

The above three commands can be combined. For example:

> I downloaded a book, and I need each of its chapters to become "titles" to facilitate converting to mobi format or generating a TOC directory jump, what should I do?

The following is the process of handling it with Vim:

1.  Press <kbd>/</kbd> to bring up the search box, enter a regular expression for searching;
2.  Use the `q` command to start recording a macro;
3.  Type the `I#` command, then press <kbd>ESC</kbd>;
4.  Use the `q` command to end macro recording;
5.  Type `normal n@letter` to go to the next location and repeat the previous step;
6.  Type `number + .` multiple times to repeat.

## External Links

-   [Vim Official Website](https://www.vim.org/)
-   [Author's Provided Configuration](https://github.com/LuoshuiTianyi/Vim-for-OIWiki)
-   [Vim Debugging: Getting Started with termdebug](https://fzheng.me/2018/05/28/termdebug/)
-   [Vim scripting cheatsheet](https://devhints.io/vimscript)
-   [Learn Vimscript the Hard Way](https://learnvimscriptthehardway.stevelosh.com)
-   [Linux vi/vim |菜鸟教程](https://www.runoob.com/linux/linux-vim.html)