## Introduction

Sublime Text (hereinafter ST, followed by a number as version distinction, if not, all versions apply) is a lightweight text editor that supports syntax highlighting and code completion for multiple languages. It has high extensibility and Vim mode, and the special hot startup mode greatly reduces the possibility of file loss.

The version supported in the new NOI Linux is ST3's last version 3.2.2[^ref1], so ST3 is mainly discussed here. Currently, ST4 official version has been released[^ref2]. If you still use ST3, it will prompt for an update.

Important differences between ST4 and ST3 will be additionally supplemented. If something is mentioned as already translated in ST3 in the introduction, Chinese is used; otherwise, it is English in ST4.

## Installation

For ST4 installation method, see [Sublime Text 4 download page](https://www.sublimetext.com/download).

For ST3 installation method, see [Sublime Text 3 download page](https://www.sublimetext.com/3).

???+ note "Purchase Prompt"
    ST is paid software, but it has an unlimited trial period. The trial will not cause any loss of functionality, but it will occasionally pop up a window prompting for activation.

## Plugins and Customization

### Chinese Localization

ST does not support Chinese by default. If you need Chinese, you need to install a Chinese localization plugin.

#### Installing Plugin Manager

After opening ST, press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd> to bring up the command palette, input `Install` and press Enter (the full command is `Install Package Control`, case-insensitive). At this time, you should see an `=` constantly moving left and right at the bottom left. After Package Control installation completes (or fails), there will be a popup prompt. The specific loading time depends on the network.

If the popup shows installation failure (related to network), you need to manually download [Package Control](https://packagecontrol.io/Package%20Control.sublime-package) and put the downloaded file into the `\Installed Packages` folder in ST's data directory. After a short wait, ST will automatically recognize the plugin (sometimes ST needs to be restarted).

???+ note "ST Data Directory Path"
    On Windows, if there is a `\data` folder under ST's **installation directory**, it will automatically use (or initialize) that folder as the data directory.
    
    The path for ST3 is generally `C:\Users\username\AppData\Roaming\Sublime Text 3`, and for ST4 it is generally `C:\Users\username\AppData\Roaming\Sublime Text`. ST will first look for the corresponding version's path. If it doesn't exist, it will look for lower version paths. If none exist, it will create and initialize a new one.
    
    In Ubuntu 20.04.1 used by NOI Linux, ST3's data directory is `$HOME/.config/sublime-text-3`, and ST4's data directory is `$HOME/.config/sublime-text`. The specific rules are the same as for the Windows environment.
    
    You can quickly view the path of the data folder's `\Packages` folder via `Preferences -> Browse Packages...`.

#### Installing Chinese Localization Plugin

Press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd> again, input `Install` and press Enter (the full command is `Package Control: Install Package`). Wait for loading to complete. The interface should look like this:

![](./images/sublime3-1.png)

Input `Chinese` and select ChineseLocalizations, press Enter, wait for installation to complete. After completion, the interface will automatically switch to Chinese (for ST4, because the Chinese plugin hasn't been updated, some new menu items will be missing, but it generally doesn't affect editing).

### Adjusting Fonts

Go to `Preferences -> Settings`, add a line `"font_face": "font name",` in the curly brackets in the user settings on the right. ST's settings are stored in JSON format. After modification, save it. If the system has the corresponding font installed, it will automatically switch.

Generally speaking, for Chinese display, Microsoft Yahei Consolas and Microsoft YaHei Mono are good choices.

???+ warning "Warning"
    Note that any settings (including plugin settings) should not be modified in the default settings on the left, even if possible. This is not recommended. If the software (or plugin) updates, the default settings will be reset.

### Installing Plugins and Themes

The method for installing plugins and themes is the same as installing the Chinese localization plugin.

Press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd>, input `Install` and press Enter, then search for plugins/themes/color schemes.

Recommended plugins:

-   BracketHighlighter: Enhances the original bracket highlighting, essential.
-   C++ Snippets: ST comes with C++ code completion, formatted with braces not on new lines. If you are not comfortable with the built-in brace-on-new-line code style, you can install this plugin, which also adds some completions.
-   C++ 11: Supports C++ 11 standard highlighting (not needed in ST4).
-   SublimeAstyleFormatter: Astyle, used for formatting code.
-   Diffy: Press <kbd>Ctrl</kbd>+<kbd>K</kbd>&<kbd>Ctrl</kbd>+<kbd>D</kbd> to quickly compare the differences between the first and second open windows. Comparison is done line by line.
-   ConvertToUTF8: Automatically identifies file encoding and supports encoding conversion.
-   SideBarEnhancements: Sidebar enhancement, quite recommended.
-   Transparency: Window transparency.

If you have other needs, you can try searching.

Some themes:[^ref3]

1337 (single color scheme), 3024 (single color scheme), Grandson-of-Obsidian (single color scheme), Seti\_UI (single theme, additionally includes highlighting for git and other formats, quite recommended), Material Theme, Predawn, Agila, Materialize.

If you want to edit your own color scheme, you can visit [tmTheme Editor](http://tmtheme-editor.herokuapp.com/).

For ST4, you can adjust the color scheme in `Preferences->Customize Color Scheme` or adjust the theme in `Preferences->Customize Scheme`.

### Enabling Vi Mode

ST's developer provides an optional plugin called Vintage for Vi users, which simulates most of Vi's functions.

#### Enabling Method

The Vintage plugin is disabled by default. You can go to `Preferences -> Settings` and in the user settings, delete `Vintage` from the `ignored_packages` item and save (do not delete the whole thing, just delete Vintage). The left side of ST's status bar will show `INSERT MODE`. At this point, the Vintage plugin is enabled.

Or press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd>, then input `Enable` and select `Package Control: Enable Package`, press Enter, and select Vintage. This method requires Package Control.

#### Related Configuration

If you want to disable the up/down/left/right keys, add the following in `Preferences -> Key Bindings`:

```JSON
{ "keys": ["left"], "command": ""},
{ "keys": ["right"], "command": ""},
{ "keys": ["up"], "command": ""},
{ "keys": ["down"], "command": ""},
```

If you want ST to start in command mode, add the following in `Preferences -> Settings`:

```json
"vintage_start_in_command_mode": true,
```

You can also set entering command mode to any key through shortcut settings (see [Setting Shortcuts](#setting-shortcuts) for details).

#### Differences from Vi

ST's Vintage plugin has some differences from Vi. Some are listed here:

-   In insert mode, selection will not enter visual mode. At this time, input will not be recognized as a command but will directly replace text. Visual mode can only be entered in command mode.
-   `r`, `R`, `zA`, `za`, `zi`, `z=`, `@` and commands using <kbd>\[</kbd>, <kbd>]</kbd> or <kbd>"</kbd> keys do not exist.
-   Shortcuts using <kbd>Ctrl</kbd>, <kbd>Shift</kbd> and <kbd>Alt</kbd> keys will remain as ST's shortcuts. For example, <kbd>Ctrl</kbd>+<kbd>V</kbd> will not enter visual mode but will paste normally.
-   Command-line mode only retains `:e`, `:0`, `:$`, `:s`.
-   Using `\` and `?` commands will automatically bring up the search box instead of directly typing words in the command for searching. At the same time, numbers will not work.
-   The `q` macro recording command will start ST's built-in macro recording. After pressing <kbd>Q</kbd>, you need to press another key to start recording, but the recorded macro will not be bound to that key. You need to press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>Q</kbd> to start recording. If you need to save, you need `Tools -> Save Macro`, and the shortcut needs to be set.
-   The combination of `number + .` cannot be used.

### Settings

#### Setting Up ST

Set it in `Preferences -> Settings`. Some useful options are listed here:

```JSON
{
  //Font size
  "font_size": 11,
  
  //Font, can be left unset, default is Consolas
  "font_face": "",
  
  //Tabs automatically converted to spaces
  "translate_tabs_to_spaces": true,
  
  //Indent width
  "tab_size": 4,
  
  //Line highlight
  "highlight_line": true,
  
  //Automatically add newline at end of file on save
  "trim_trailing_white_space_on_save": true,
  
  //When searching in selection, only search in selection range
  "auto_find_in_selection": true,
  
  //Disabled plugins unlikely to be used in OI, can adjust yourself
  "ignored_packages": [
    "ActionScript", "AppleScript", "ASP", "Batch File", "C#", 
    "Clojure", "CSS", "D", "Diff", "Erlang", "Git Formats", 
    "Go", "Graphviz", "Groovy", "Haskell", "HTML", "Java", 
    "LaTeX", "Lisp", "Lua", "Makefile", "Matlab", 
    "Objective-C", "OCaml", "Perl", "PHP", "Python", 
    "R","Rails", "RestructuredText", "Ruby", "Rust", 
    "Scala", "ShellScript", "SQL", "TCL", "Textile", "XML", 
  ],
  
  //Relative line numbers, can cooperate with Vintage plugin for quick jumps
  "relative_line_numbers": false,
}
```

#### Setting Shortcuts

Set it in `Preferences -> Key Bindings`. Find the function to modify on the left, then copy it to the right and modify the key.

For example, if you want to change the compile shortcut from <kbd>Ctrl</kbd>+<kbd>B</kbd> to <kbd>F9</kbd> (if you don't make the original shortcut invalid, it actually adds another trigger method), you can add in `Preferences -> Key Bindings`:

```JSON
//Change build command to f9
{ "keys": ["f9"], "command": "build" },

//Change original f9's line sorting function to shift+f9. Since this function is mostly not used, this line can also be omitted
{ "keys": ["shift+f9"], "command": "sort_lines", "args": {"case_sensitive": false} },
```

#### Setting Plugins

Plugin settings can be found in `Preferences -> Package Setting -> Plugin name`. When making modifications, be careful not to modify the default settings.

For example, here are some settings for BracketHighlighter, modify them in `Preferences -> Package Setting -> BracketHighlighter -> Bracket Setting`:

```JSON
{
  //Show a line at the beginning of lines between matched brackets, can quickly find bracket range
  "content_highlight_bar": true,
  
  //Show matched brackets in minimap
  "show_in_minimap": true,
  
  //Ignore match range limit
  "ignore_threshold": true,
  
  //style highlight style, bold is block highlight, underline is bold underline, outline is a circle around
  //color is color, all supported colors are already included in default settings
  //icon is the icon shown in sidebar
  "bracket_styles": {
    "default": {"icon": "dot", "color": "region.yellowish", "style": "bold",},
    "unmatched": {"icon": "question", "color": "region.redish", "style": "outline",},
    "curly": {"icon": "curly_bracket", "color": "region.purplish",},
    "round": {"icon": "round_bracket", "color": "region.yellowish",},
    "square": {"icon": "square_bracket", "color": "region.bluish",},
    "angle": {"icon": "angle_bracket", "color": "region.orangish",},
    "tag": {"icon": "tag", "color": "region.orangish",},
    "c_define": {"icon": "hash", "color": "region.yellowish",},
    "single_quote": {"icon": "single_quote", "color": "region.greenish",},
    "double_quote": {"icon": "double_quote", "color": "region.greenish",},
    "regex": {"icon": "star", "color": "region.greenish",}
  }
}
```

### Modifying and Adding

Sometimes, some aspects of plugins may not be satisfactory, or you may want to localize a plugin. In this case, you need to make some modifications to the plugin.

The location of plugins is the `\Installed Packages` folder in the data directory.

The files inside are suffixed with `.sublime-package`, actually in `.zip` format. You can use decompression software to open them.

For example, if you want to modify auto-completion, you can open the `\Snippets\*.sublime-snippet` files in the **installation directory** `\Packages\C++` plugin to modify. If you want to **add** auto-completion, you can install C++ Snippets and modify or add files in it (or create a new plugin, but you cannot directly add to the built-in C++ plugin, otherwise it won't be recognized). When saving any modifications, you **must** close ST, and please make a backup in advance, otherwise file loss may occur.

Of course, any additions can be placed in `\Packages\User\` under the data directory path, which is always supported.

For example, a file template completion can be written like this:

```XML
<snippet>
  <description>template_code</description> <!-- This content is the preview of completion -->
  <content><![CDATA[#include <cstdio>
using namespace std;

int main() {
  freopen("${1:file name}.in", "r", stdin);
  freopen("$1.out", "w", stdout);
  ${0:/* code */}
  fclose(stdin);
  fclose(stdout);
  return 0;
}]]></content>
  <tabTrigger>code</tabTrigger> <!-- This content is the trigger text for completion -->
  <scope>source.c++</scope> <!-- This content is the applicable language for completion -->
</snippet>
```

The following lists some file suffixes and their uses. For specific plugin development tutorials, see [Community Documentation](https://docs.sublimetext.io/guide/extensibility/plugins/) and [Official Documentation](https://www.sublimetext.com/docs/3/):

| Suffix                  | Use                             |
| -------------------- | ------------------------------ |
| .sublime-build       | Build system file                         |
| .sublime-completions | File name completion list (generally header files)                |
| .sublime-syntax      | Syntax highlighting file                         |
| .sublime-settings    | Settings file                           |
| .tmPreferences       | List file in preferences                      |
| .sublime-keymap      | Shortcut settings file                        |
| .sublime-snippet     | Code completion file                         |
| .sublime-commands    | Command definition file                         |
| .sublime-menu        | ST UI file, including sidebar and top menu bar (main object of localization) |

Since plugin updates directly overwrite original files, it is recommended to back up modified files.

## Editing

### Setting Syntax

Press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd> and input syntax, or click `Plain Text` at the bottom right and change to the required language. You can also set it in `View -> Syntax`.

![](images/sublime3-2.png)

### Shortcuts

ST has compound shortcuts. For example, <kbd>Ctrl</kbd>+<kbd>K</kbd>&<kbd>Ctrl</kbd>+<kbd>Backspace</kbd> means first press <kbd>Ctrl</kbd>+<kbd>K</kbd> then press <kbd>Ctrl</kbd>+<kbd>Backspace</kbd>.

Some shortcuts:

| Key                                                                         | Command                                                            |
| -------------------------------------------------------------------------- | ------------------------------------------------------------- |
| <kbd>Ctrl</kbd>+<kbd>X</kbd>                                               | Cut current line                                                         |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>K</kbd>                              | Delete line                                                           |
| <kbd>Ctrl</kbd>+<kbd>Enter</kbd>                                           | Insert line below                                                        |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>Enter</kbd>                          | Insert line above                                                        |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>Up</kbd>                             | Move line up                                                           |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>Down</kbd>                           | Move line down                                                           |
| <kbd>Ctrl</kbd>+<kbd>L</kbd>                                               | Select line, repeat to select multiple lines down                                                 |
| <kbd>Ctrl</kbd>+<kbd>D</kbd>                                               | Select word, repeat to select multiple same words, and enter multi-selection mode (for quick batch changes)                            |
| <kbd>Ctrl</kbd>+<kbd>M</kbd>                                               | Jump to matching bracket                                                      |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>M</kbd>                              | Select content inside brackets (not including brackets), repeat to include brackets                                       |
| <kbd>Ctrl</kbd>+<kbd>K</kbd>&<kbd>Ctrl</kbd>+<kbd>K</kbd>                  | Delete to end of line (compound shortcut, recommend using Vim mode instead)                                     |
| <kbd>Ctrl</kbd>+<kbd>K</kbd>&<kbd>Ctrl</kbd>+<kbd>Backspace</kbd>          | Delete to beginning of line (compound shortcut, recommend using Vim mode instead)                                     |
| <kbd>Ctrl</kbd>+<kbd>]</kbd>                                               | Indent current (selected) line                                                    |
| <kbd>Ctrl</kbd>+<kbd>\[</kbd>                                              | Un-indent current (selected) line                                                  |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd>                              | Copy current line, and insert in next line                                                 |
| <kbd>Ctrl</kbd>+<kbd>J</kbd>                                               | Merge next line with current line                                                     |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>V</kbd>                              | Paste and indent (for pasting entire code blocks)                                               |
| <kbd>Ctrl</kbd>+<kbd>K</kbd>&<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>V</kbd> | Paste from history (compound shortcut, recommend changing to <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>V</kbd>) |
| <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>Down</kbd>                             | Move cursor down, keep current line cursor (enter multi-selection mode)                                       |
| <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>Up</kbd>                               | Move cursor up, keep current line cursor (enter multi-selection mode)                                       |
| <kbd>Ctrl</kbd>+<kbd>R</kbd>                                               | Jump to any symbol in file (function or type definition)                                           |
| <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>R</kbd>                              | Jump to any symbol in project (function or type definition)                                           |
| <kbd>Ctrl</kbd>+<kbd>P</kbd>                                               | Jump to any file (previously opened or existing in project)                                      |
| <kbd>\~</kbd>                                                              | Toggle case of selection                                                    |

### Auto Completion

ST has rich completion functions. Possible completion content will be displayed below the cursor. Press <kbd>Tab</kbd> or <kbd>Enter</kbd> to complete (in ST4, if you do a non-Snippet type completion, pressing <kbd>Tab</kbd> again can continue selecting completions that contain this completion as a substring).

Snippet type completions generally have some edit blocks. After completion, the replacement text is automatically selected. If it's a complex completion like `for` with multiple edit blocks, press <kbd>Tab</kbd> again to complete the next edit block. At this time, to trigger completion in the edit block, you need to use <kbd>Enter</kbd> (in ST4, you can continue using <kbd>Tab</kbd>).

If auto completion doesn't work, fix it as follows:

1.  Check if the language is switched. ST defaults new files as Plain Text.

2.  Go to `Preferences -> Settings` and add two lines:

```JSON
"auto_complete": true,
"auto_match_enabled": true,
```

### Multi-Selection

Hold <kbd>Ctrl</kbd> and click to add cursors on the screen. <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>Up</kbd> or <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>Down</kbd> can add cursors directly between two adjacent lines. Any editing operation will be applied to all cursors simultaneously.

### Find and Replace

<kbd>Ctrl</kbd>+<kbd>F</kbd> is find, <kbd>F3</kbd> is find next, <kbd>Shift</kbd>+<kbd>F3</kbd> is find previous, <kbd>Ctrl</kbd>+<kbd>H</kbd> is replace.

The five find options are regular expression matching, case sensitivity, whole word match, wrap around, and find in selection.

It is recommended to set `"auto_find_in_selection"` to `true` in preferences. This way, when using find with more than one word selected, it will automatically search only in the selection.

## Demonstration

### Hot Start

Try typing something in ST, and directly close the entire ST. ST will close directly without any prompt. When you open ST again, as long as you don't restore the computer data, no data will be lost.

### Multi-Selection

If you want to change all `bok` to `book` in the following code, just place the cursor on any `bok`, hold <kbd>Ctrl</kbd>+<kbd>D</kbd> to quickly select.

```cpp
int check() {
  book[1] = 1, book[2] = 1, book[3] = 1, bok[1] = 1, bok[2] = 1, bok[3] = 1,
  bok[4] = 1, bok[5] = 1;
}
```

If you want to change everything after the equal sign in the following file to `"good"`, just place the cursor before the `aaa` in the first line, press <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>Down</kbd> five times, then press <kbd>Ctrl</kbd>+<kbd>D</kbd> and type `good`.

Or select `"a` and hold <kbd>Ctrl</kbd>+<kbd>D</kbd>, then press <kbd>Right</kbd>, <kbd>Ctrl</kbd>+<kbd>D</kbd>, then type.

```cpp
s[1] = "aaa";
s[2] = "aab";
s[3] = "aac";
s[4] = "good";
s[5] = "aae";
s[6] = "aaf";
```

If you want to add parentheses to all `a + b` below, just select one `a + b`, hold <kbd>Ctrl</kbd>+<kbd>D</kbd> and type <kbd>(</kbd> (if you select a certain area, pressing any left parenthesis key will add matching parentheses on both sides of that area).

```plain
a + b*a + b*a + b
```

### Find and Replace

If you want to change everything after the equal sign in the following file to `"good"`, you can also use <kbd>Ctrl</kbd>+<kbd>H</kbd> to use replace, open regex, input `".*"`, and replace with `"good"`.

```cpp
s[1] = "aaa";
s[2] = "aab";
s[3] = "aac";
s[4] = "good";
s[5] = "aae";
s[6] = "aaf";
```

If you want to add semicolons to the following code, just use selection replace, open regex, input `\n`, and replace with `;\n`.

```plain
int main() {  int a, b  cin >> a >> b  cout << a + b  return 0}
```

### Macro Recording

If you want to add semicolons to the following code, press <kbd>Ctrl</kbd>+<kbd>q</kbd> to start macro recording. Then press <kbd>End</kbd>, <kbd>;</kbd>, <kbd>Down</kbd> in sequence, then press <kbd>Ctrl</kbd>+<kbd>q</kbd> to end macro recording (during the process, the bottom left will not show "recording" the whole time, but it is indeed recording). Then repeat <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>q</kbd>.

```plain
int main() {
  int a, b
  cin >> a >> b
  cout << a + b
  return 0
}
```

??? note "If Vintage Plugin is Enabled"
    After executing <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>q</kbd> once, you can press <kbd>Esc</kbd> to enter command mode and input `..` (the `.` command can repeat ST3 commands)

For macro saving and key binding, see [Community Documentation](https://docs.sublimetext.io/guide/extensibility/macros.html).

## Compiling and Running

ST's compile environment is already configured and can be used directly.

On Windows, you need to add the directory where g++ is located to the environment variables and restart ST.

### Compiling

Press <kbd>Ctrl</kbd>+<kbd>B</kbd> to compile. On first use, you need to select a build system. Select `C++ Single File` (compile) or `C++ Single File - Run` (compile and run).

#### Modifying Compile Options

ST's default compile options are `g++ "${file}" -o "${file_path}/${file_base_name}"`. If you want to modify compile options, you can create a new build system.

Go to `Tools -> Build System -> New Build System...` and input in the middle of the curly brackets:

```JSON
//Compile options can be adjusted by yourself
//Compile and run
"shell_cmd": "g++ -Wall \"${file}\" -o \"${file_path}/${file_base_name}.exe\" && \"${file_path}/${file_base_name}.exe\"",

//This line allows ST3 to show errors graphically. If you are used to looking at g++ returned information, you can remove it
"file_regex": "^(..[^:]*):([0-9]+):?([0-9]+)?:? (.*)$",
```

After saving, press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> to switch build systems to use. This configuration compiles and runs in external CMD.

The saved file is under the data directory path as `\Packages\User\Build System Name.sublime-build` and can be modified repeatedly.

### Running

If you selected `C++ Single File - Run` (compile and then run) during compilation or configured auto-run, the compile information window that pops up below should not show any display (unless there are compile errors), because ST's compile information window is actually a terminal where you can directly input data.

After running finishes, it will prompt the program's running time. The timing is from pressing <kbd>Ctrl</kbd>+<kbd>B</kbd> to the end of all CMD command execution, which includes compile time, input time, and if running in external CMD, it also includes CMD start and close time.

???+ warning "Warning"
    This window cannot input <kbd>F6</kbd> or <kbd>Ctrl</kbd>+<kbd>Z</kbd>. If you run a program that reads to EOF, please use file input, or configure to run in external CMD.

### Debugging

You can install plugins to make ST support graphical gdb debugging, but it is not recommended to rely on plugins for gdb debugging.

A better approach is to add related commands to start gdb when configuring the build system, and do command-line debugging externally.

## Miscellaneous

-   Drag a folder into ST and press <kbd>Ctrl</kbd>+<kbd>K</kbd>&<kbd>Ctrl</kbd>+<kbd>B</kbd> to open the sidebar, for quickly switching files.
-   Make good use of jump functions, especially <kbd>Ctrl</kbd>+<kbd>P</kbd> for jumping between files and <kbd>Ctrl</kbd>+<kbd>R</kbd> for jumping between functions.
-   ST supports git[^ref4].
-   All ST configurations are stored in the data directory and can be freely packaged, but registration information cannot be used on multiple computers.

## External Links

-   [Using Command Line Debugging](../cmd.md)
-   [Sublime Text 3 Official Documentation](https://www.sublimetext.com/docs/3/)
-   [Sublime Text Community Documentation](https://docs.sublimetext.io/)

## References and Notes

[^ref1]: [NOI Linux 2.0 Released](https://www.noi.cn/gynoi/jsgz/2021-07-16/732450.shtml)

[^ref2]: [Sublime Text 4 Released](https://www.sublimetext.com/blog/articles/sublime-text-4)

[^ref3]: [Convenient and Fresh Text Editor sublime](https://www.luogu.com.cn/blog/acking/sublime)

[^ref4]: [Sublime Text Git Integration](https://www.sublimetext.com/docs/git_integration.html)