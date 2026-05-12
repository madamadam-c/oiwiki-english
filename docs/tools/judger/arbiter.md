author: Ir1d, HeRaNO, NachtgeistW, i-Yirannn, bear-good, ranwen, CoelacanthusHex, billchenchina, Tiger3018, Xeonacid, Cryflmind

## Arbiter

**Arbiter** is a judging tool developed by Beihang University for NOI Linux, now used for judging in major NOI series programming competitions. According to Lu Kaifeng's lecture "Next Generation Judging System" at the 2016 Winter Camp, Arbiter was developed by the Beihang University team (GAIT) under the leadership of Professor Yin Baolin.

After NOI Linux was updated to version 2.0, Arbiter was recompiled with Qt 5.12.8 and released as Arbiter 2.0. Since subsequent judging environments all use NOI Linux 2.0, the Arbiter version used in the following introduction is Arbiter 2.0 that comes with NOI Linux 2.0.

This judging software can only be found in NOI Linux. The binary file location is `/usr/local/arbiter/local/arbiter_local`.

### Usage

#### Configuring Programs

Configure the contestant source code folder and contestant list. Create contestant folders in NOIP format:

```text
players/
| -- day1
|    | -- <contestant_1's ID>
|    |     | -- <problem_1>
|    |     |   `-- <problem_1>.c/cpp/pas
|    |     | -- <problem_2>
|    |     |   `-- <problem_2>.c/cpp/pas
|    |     | ...
|    |     | -- <problem_x>
|    |        `-- <problem_x>.c/cpp/pas
|    | -- <contestant_2's ID>
|    |     | -- <problem_1>
|    |     | ...
|    | ...
| -- day2
|    | -- <contestant_1's ID>
|    |     | -- <problem_1>
|    |     |   `-- <problem_1>.c/cpp/pas
|    |     | -- <problem_2>
|    |     |   `-- <problem_2>.c/cpp/pas
|    |     | ...
|    |     | -- <problem_x>
|    |        `-- <problem_x>.c/cpp/pas
|    | -- <contestant_2's ID>
|    |     | -- <problem_1>
|    |     | ...
|    | ...
...
```

Here, `<x>` in `day<x>` is the session number, `<contestant_x's ID>` refers to the contestant ID, in the format `<province>-<number>`, such as HL-001, JL-125, etc.; `<problem_x>` refers to the problem name. During self-testing, you can use a combination of letters, hyphens (i.e., `-`), and numbers as the contestant ID.

The contestant list format is as follows:

```text
<contestant_1's ID>,<contestant_1's name>
<contestant_2's ID>,<contestant_2's name>
...
```

Here, `<contestant_x's name>` represents the contestant's name. Save this file as a plain text file or CSV file, using `UTF-8` encoding.

The contestant list can also be added manually after starting Arbiter.

Next, configure the test data. The naming format for each test file is as follows:

```text
<problem_x><y>.in <problem_x><y>.ans
```

Here, `<y>` is the data number, starting from 1. The default test data suffix is `.ans`, and the contestant output suffix is `.out` - do not confuse them.

If you need to convert previously generated out format files to ans format, you can use the `rename` command in batch in NOI Linux 2.0, while in Windows you can use the `ren` command in batch. We will introduce the usage of these commands later.

You don't need to put each problem's test data in its own folder - just put them all together.

Now start configuring the judging folder.

In the bottom-left corner, click "Show Applications" - "All" - "Arbiter\_local" to start Arbiter.

![Arbiter\_Home](./images/arbiter_home.png)

Click OPEN to open an existing competition, then select the `setup.cfg` file under the corresponding competition folder; click NEW to create a new competition and set the name and competition directory. Note that you need to create a folder in the **user's home directory** first, then select it as the competition directory - if you create the competition directory on the desktop, judging cannot be performed. If such a problem occurs, it is very likely because the competition folder path cannot contain Chinese characters.

![add\_problem](./images/arbiter_addproblem.png)

In the left problem summary, "Right-click" - "Add Exam", then "Right-click" on the exam tab - "Add Problem", and the new problem will be created.

Click the down arrow on the left side of the exam to show all problems. Click the problem tab to modify the problem name to the English name of the problem, and also modify the problem's time and memory limits and comparison method. It is highly recommended not to use "Full Text Direct Comparison" as the comparison method - it is very unfriendly for data created on Windows. You can choose a comparator according to the problem, but note that you must select a comparator, otherwise the judging result will be `No Score.`.

![problem\_list](./images/arbiter_problem.png)

Click "File" - "Save". This step cannot be omitted, otherwise the program will not generate the problem configuration file. Note that every modification to the problem configuration must be saved.

At this point, opening the exam folder will reveal the following contents:

```text
<name>/
| -- data
| -- evaldata
| -- filter
| -- final
| -- players
| -- result
| -- tmp
`-- day1.info
`-- player.info
`-- setup.cfg
`-- task1_1.info
`-- task1_2.info
`-- team.info
```

The `filter` folder contains some comparators; the `result` folder stores contestants' judging results; the `tmp` folder is the cache folder during judging. Here `day<x>.info` is the session configuration file, `<x>` is the session number; `task<x>_<y>.info` file is the problem configuration file, `<x>` is the session number, `<y>` is the problem number.

Place the already created contestant program folder under the `players/` directory. Note that the outermost layer should establish corresponding `day<x>` folders according to the exam day. Place all test data (not in folders) in `evaldata`. If using a custom checker, place the custom checker in `filter`.

#### Official Judging

Open the "Problem Judging" tab, and the following page will appear:

![Pretest](./images/arbiter_pretest.png)

If the contestant list has already been created, directly select "Import List" on the right to import. If there are few contestants, you can select "Add Contestant" on the right to import.

The page after importing is as shown.

![Test](./images/arbiter_test.png)

The ID in the example is `HL-001`, and the program will automatically identify the "Affiliation" column. If it is not a NOIP-standard ID, it will not be recognized.

Change judging session 0 to session 1 (or other sessions). Then select "Select All" on the right (or select specified contestants), then select "Judge Selected Contestants" below, select the problems to be judged (or all problems), and wait for judging to finish.

Detailed information about test points needs to be viewed under the `result` folder. There will be contestants' result folders in the folder, and the result file suffix is `.result` - view it as plain text. If the error `No score file.` appears, you can check whether the `/tmp/_eval.score` file was generated during judging.

### Writing Custom Checkers

Decompiling other checkers reveals that the command to run a custom checker is `<problem>_e <in> <out> <ans>`. The last three parameters represent input, contestant output, and answer file respectively. The final score result must be written to the `/tmp/_eval.score` file. The first line is the judging information, the second line is the score, and 10 points is the full score.

The compiled custom checker must be named `<problem>_e`, where `<problem>` is the problem name. When configuring the problem, select the custom checker and then select the required custom checker.

In the problem management section, change the submission method from source code to answer file in the problem configuration, and then select the custom checker to test problem submissions.

### Precautions

Confirmed matters that need attention:

-   Pay attention to saving the competition in time, otherwise the program may crash during operation. To ensure it doesn't crash, try saving the competition multiple times, or save every time you make a modification.
-   Do not click the score statistics above if no judging has been performed, otherwise Arbiter will crash directly.
-   Due to Linux runtime stack limits, if you need to enable unlimited stack, first enter `ulimit -s unlimited` in the terminal before executing `arbiter_local` to open the judger, otherwise the problem `Exceeding memory limit` may occur.
-   For official judging, when preparing problems, ensure that all problems have the same memory limit. During judging, replace `unlimited` in the command with the problem's memory limit in kilobytes (KiB). For example, if the problem's memory limit is 512 MiB, the command is `ulimit -s $((512 * 1024))`. The main cause of this problem is that when Arbiter is started directly, its parent process is GNOME, and the child process inherits the parent process's stack space limit.
-   It is not recommended to include spaces in the software's working directory. If there are spaces, it is very likely that during competition creation, all default comparators cannot be copied into the filter directory (i.e., the filter directory is empty). At this time, judging will result in all scores being 0, and you can see the prompt `Compile Failed.` in the generated result files.
-   When viewing code, the prompt "Answer file not found" means the contestant's source code was not found.

Matters requiring further verification:

-   It is prone to freezing, such as moving the mouse during large-scale judging can cause freezing.
-   Random crashes (one reason is not saving the competition in time).
-   After modifying the comparison method, there is a chance that the modification fails, i.e., the comparison method modification is not applied.
-   Pay attention to permission issues during configuration, but ensure that the same user creates the competition, copies data, and performs judging, there will be no permission issues.

### Vulnerabilities

Due to long-term lack of maintenance, the system has some vulnerabilities, such as being able to use `#pragma G++ optimize("O2")` and `__attribute__((__optimize__("-O2")))` and so on. You can use [gcc-plugins-for-oi](https://github.com/xdu-icpc/gcc-plugins-for-oi) to implement detection of these commands at compile time.

### Evaluation

After Arbiter 1.0.2 was developed, there has been no substantial update, resulting in a very poor judging experience, and the UI is detached from modern aesthetics. In NOI Linux 1.4.1, like the GUIDE that comes with NOI Linux, it became an object of intense criticism from contestants and coaches. In NOI Linux 2.0, besides the comparator removing the source code and the software being recompiled using Qt 5, there are no major changes, and some stability issues remain unresolved.

??? note "Appendix: Usage of ren and rename commands"
    Windows operating system comes with a command to modify file names: `ren`.
    
    The command syntax is as follows:
    
    ```shell
    ren [<drive>:][<path>]<filename>1 <filename>2
    ```
    
    If we need to modify all files in the current working directory, for example, changing all out files to ans files, we can execute the following command:
    
    ```shell
    ren *.out *.ans
    ```
    
    If performing such modifications in the NOI Linux 2.0 environment, the `rename` command seems to be the better option currently, but it is not a command that comes with NOI Linux 2.0, so you need to install it first:
    
    ```shell
    sudo apt install rename
    ```
    
    Note: If after execution it prompts `E: Unable to locate package package_name`, you need to execute this command first: `sudo apt-get update`
    
    After installation is complete, you can use the `rename` command normally. The usage of the `rename` command is similar to direct text replacement. Its command syntax in the NOI Linux 2.0 environment is as follows:
    
    ```shell
    rename 's/<text before modification>/<text after modification>/' <filename>
    ```
    
    Here `<filename>` can use wildcard `*`, or specify one type of files (like `*.out`).
    
    Please note that there is a `/` at the end inside the quotes. If one `/` is missing, the `rename` command will report an error: `Substitution replacement not terminated at (user-supplied code)`.
    
    At this time, if we need to modify all files in the current working directory, for example, changing all out files to ans files, we can write it like this:
    
    ```shell
    rename 's/\.out/\.ans/' *
    ```
    
    Here `\.` means escaping the `.`.
    
    (Note: If `\.` is missed, for example, if you have a file named `outtest.out`, after executing this command, the file will be modified to `anstest.out`)
    
    Similarly, if you need to uniformly modify all files named `atmost<x>.ans` (where `<x>` represents the test point number), changing them all to `test<x>.ans`, you can write it like this:
    
    ```shell
    rename 's/atmost/test/' *.ans
    ```