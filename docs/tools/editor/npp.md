author: ouuan, CBW2007, partychicken, StudyingFather, Xeonacid, Henry-ZHR

## Software Introduction

Notepad++ is a text editor for Windows operating systems. It supports multiple languages, multiple encodings, and syntax highlighting and completion for multiple programming languages. Its logo is also very cute, a chameleon (![npp-logo](./images/npp-logo.webp))

Its functionality is much stronger than many other editing software. It is more stable when opening large files, and continuous undo won't cause problems. When closing, it doesn't need to save. It automatically saves for you in the buffer. (May need configuration) Moreover, it is very compact, only 10MB+, and can even be carried on a USB drive.

## Download and Installation

See [Getting started | Notepad++ User Manual](https://npp-user-manual.org/docs/getting-started/).

## Changing Interface Language

![npp-lang](./images/npp-lang.gif)

After changing the language, you can freely customize the editor!

## Basic Usage

Here are some basic and feature functions.

### Find and Replace

Click "(Menu Bar) Search" -> "Find" (shortcut `CTRL`+`F`) to open the "Find" page (as shown in the figure).

![npp-search](./images/npp-search.png)

Click "(Menu Bar) Search" -> "Replace" (shortcut `CTRL`+`H`) to open the "Replace" page (as shown in the figure).

![npp-replace](./images/npp-replace.png)

In fact, Find and Replace are the same window. Click the tab above to switch.

Its functions are similar to ordinary editors, but support more, such as:

1.  Strict match or case match
2.  Cross-document matching
3.  Escape characters, like '\r', '\n'
4.  Regular expressions
5.  Counting

### Periodic Backup

![npp-settings-1](./images/npp-settings-1.png)

With this function, you don't have to worry about code loss due to accidents!

However, this function only takes a snapshot of your file, not really saving it. So it is still recommended to have good saving habits. Or you can go to the built-in plugin store to install the "Auto Save" plugin (see [Advanced Usage -> Plugins](#plugins), same below)

### Bookmark Function

Press `Ctrl`+`F2` on the line you need to set/remove bookmarks. Lines with bookmarks have a blue dot in front.

Press `F2` to locate to the next bookmark.

If you find it inconvenient, you can go to the built-in plugin store to install the "Bookmarks" plugin

### Syntax Highlighting

Right-click "XXX file" in the bottom left corner to choose from many language highlighting options such as C, C++, PASCAL, Markdown, etc. You can even define your own highlighting!

If you think it's troublesome to change highlighting every time you open a file, you can modify the default highlighting in "Settings -> Preferences -> New -> Default Language".

If you need to render Markdown, you can go to the plugin store to install "Markdown Viewer", and there are many similar plugins waiting for you!

### Show All Characters

![npp-settings-2](./images/npp-settings-2.png)

Click the button circled in red, and you can show "space", "TAB", "newline" and other invisible characters very (chaotically) clearly.

### Auto-detect File Encoding and Line Endings

Notepad++ can automatically detect whether the current file encoding is `UTF-8` or `GB2312` or even others. No more worry about being messed up by garbled characters or seeing uninitialized memory.

If you want to use a different encoding to browse an article, click "(Menu Top Bar) Encoding" -> "Encode with XXX". If you want to change the file's character encoding, click "(Menu Top Bar) Encoding" -> "Convert to XXX Encoding".

It can also automatically detect whether line endings are `CR`, `LF`, or `CRLF`. Don't worry about downloaded data losing line breaks.

In the bottom status bar, you can see "Windows(CR LF)" and similar text. This is the current file's line ending. Right-click on it to change the current file's line ending. This operation is more intuitive when combined with "Show All Characters"!

## Advanced Usage

This is for users with higher needs.

### Macros

Macros can help you complete many repetitive tasks. For example, changing "abcde" in odd lines to "afce" takes two steps.

#### Recording Macro

![npp-macro-rec](./images/npp-macro-rec.gif)

#### Using Macro

![npp-macro-use](./images/npp-macro-use.gif)

#### Large-scale Processing, Repeated Use

What about more lines? The operation needs some change.

First, for recording, be sure to press the `HOME` or `END` key on the keyboard to move the cursor to the beginning or end of the line, then use arrow keys to adjust the horizontal position, then make changes. Finally, be sure to use arrow keys to move the cursor to the next line to process.

For the example above, first press the `END` key, then press in sequence `←`, `Backspace`, `←`, `Backspace`, `F`, and finally press `↓` twice, then stop recording.

Then for playback, first locate to the first line to process (line 3), then click "Macro" -> "Run Macro Multiple Times". In the popup window, set the macro to run (the one just recorded is generally the first one), set the number of times to run (or run directly to end of file), and click OK.

#### Saving Macro

Click "Macro" -> "Save Recorded Macro", set the name and shortcut, and it will be saved for later use.

### Plugins

#### Plugin Management

Open the "Plugins" button in the function bar. The list will show all plugins you have installed.

Then select "Plugin Management" to manage your plugins.

#### Installing Plugins (Store)

1.  Open the "Available" tab, check the plugin you want in the list
2.  Click the "Install" button in the upper right corner, and follow the prompts to restart the software.

#### Installing Plugins (Manually)

1.  Download the plugin (officially hosted by third parties: <https://sourceforge.net/projects/npp-plugins/>). Be sure to choose the plugin **with the same processor architecture as when you installed Notepad++**.
2.  Find a file named "XXX.dll" (usually named after the plugin).
3.  In the function bar of Notepad++, click Plugins and in the list click "Open Plugins Folder".
4.  Put the DLL file you just found into the folder, and restart Notepad++.
5.  [Optional] Delete the file you just copied, **but do not delete the generated folder!**

Tips: If it doesn't succeed multiple times, try creating a new folder with the same name as the plugin and put the ".dll" file into the created folder

#### Updating Plugins

In Plugin Management, select the "Update" tab, check the plugin to update, and click the "Update" button in the upper right corner.

#### Removing Plugins

Same in Plugin Management, select the "Installed" tab, check the plugin to remove, and click the "Remove" button in the upper right corner.

### Setting Up Development Environment

Not just an editor! "Notepad++" is like a god-level existence. It can compile code in a foolproof way, even replacing IDEs! Here's an example with C++

1.  Install the compiler and add its necessary directory to the PATH environment variable. (For C++ you need to add %APPPATH%\bin). When you type g++ in cmd and it no longer says 'g++' is not an internal or external command... it's ready (you may need to restart the computer). Recommended to [download ConsolePauser](https://sourceforge.net/projects/orwelldevcpp/files/Tools/ConsolePauser.exe/download) and put it anywhere and add its directory to environment variables (this is a Dev-C++ plugin, also found in Dev-C++ software root directory).

2.  In the menu bar, select "Run" -> "Run...", and open the "Run" window.

3.  Enter the following commands respectively:

    ```shell
    #Compile command:
    cmd /c g++.exe -o $(CURRENT_DIRECTORY)\$(NAME_PART).exe $(FULL_CURRENT_PATH)
    #Run command:
    cmd /c $(CURRENT_DIRECTORY)\$(NAME_PART).exe $(FULL_CURRENT_PATH) & pause
    #Debug command:
    cmd /c gdb $(CURRENT_DIRECTORY)\$(NAME_PART).exe

    #If you downloaded ConsolePauser, you can use the following code for a better program running experience! (Remember to add environment variables!)

    #Compile command:
    cmd /c (start ConsolePauser "g++.exe -o $(CURRENT_DIRECTORY)\$(NAME_PART).exe $(FULL_CURRENT_PATH)")
    #Run command:
    cmd /c (start ConsolePauser "$(CURRENT_DIRECTORY)\$(NAME_PART).exe")
    #Debug command:
    cmd /c (start ConsolePauser "gdb $(CURRENT_DIRECTORY)\$(NAME_PART).exe")
    ```

4.  Click "Save", you can name it yourself, such as "Compile", "Run", etc., then set your desired shortcut (choose easy-to-remember ones, like Dev-C++'s are `F9` and `F10` respectively).

5.  Enjoy it!

## Little Easter Eggs

1.  When running the installer, you will see this sentence at the bottom:

    > "The best things in life are free. Notepad++ is free. So Notepad++ is the best(.)"
    >
    > (The best things in life are free. Notepad++ is free. So Notepad++ is the best.)

    This boast, have to say, is quite confident.

2.  In a new page, type "random" and select it, then press `F1` and you will get a very interesting sentence.