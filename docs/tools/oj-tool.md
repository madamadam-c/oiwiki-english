This page introduces some OJ tools.

## cf-tool

cf-tool is a cross-platform (supporting Windows, Linux, macOS) command-line interface tool for Codeforces, supporting many common operations.

The source code is hosted at [xalanq/cf-tool](https://github.com/xalanq/cf-tool).

![cf-tool usage screenshot 1](./images/oj-tool-1.jpg)

![cf-tool usage screenshot 2](./images/oj-tool-2.jpg)

### Features

-   Supports all programming languages on Codeforces.
-   Supports Contests and Gym.
-   Submit code.
-   Dynamically refresh submission status.
-   Fetch problem samples.
-   Compile and test samples locally.
-   Fetch all code from a user.
-   Generate code from specified templates (including timestamp, author info, etc.).
-   List overall information for all problems in a contest.
-   Open problem pages, standings, submission pages, etc. in the default web browser.
-   Colorful command line interface.

### Download

Go to [cf-tool/releases](https://github.com/xalanq/cf-tool/releases) to download the latest version.

Subsequent updates can be obtained directly using the `upgrade` command.

### Usage

After placing the downloaded executable `cf` (or `cf.exe`) in an appropriate location (see FAQ question 2), open the command line and use the `cf config` command to configure your username, password, and code template.

### Usage Example

The following briefly simulates a contest workflow.

`cf race 1136`

Time to start contest 1136! The 1136 can be obtained from the contest link; for example, the contest link in this case is <https://codeforces.com/contest/1136>.

If the contest has not started yet, the command will count down. Once the contest has started or the countdown is finished, the tool will automatically open all problem pages of the contest in the default browser and fetch samples locally.

`cd 1136/a`

Enter the directory for problem A, which will contain the samples for that problem.

`cf gen`

Generate code from the default template, say `a.cpp`.

`vim a.cpp`

Write code using Vim (or use another editor or IDE).

`cf test`

Compile and test samples.

`cf submit`

Submit code.

`cf list`

View information about all problems in the current contest.

`cf stand`

Open the standings in the browser to check rankings.

### FAQ

1.  I double-clicked the program but nothing happened

    cf-tool is a command-line interface tool; you should run it in the terminal.

2.  I cannot use the `cf` command

    You should put the `cf` program in a path that has been added to the system variable PATH (for example, `/usr/bin/` on Linux).

    If you don't understand, search for "adding to PATH".

3.  How to add a new test case

    Create two additional test data files `inK.txt` and `ansK.txt` (K is a string containing 0\~9).

4.  How to enable tab completion in the terminal

    Use this tool [Infinidat/infi.docopt\_completion](https://github.com/Infinidat/infi.docopt_completion).

    Note: If a new version is released (especially with new commands), you should rerun `docopt-completion cf`.

## Codeforces Visualizer

Official website: [Codeforces Visualizer](https://cfviz.netlify.app)

The source code is hosted at [sjsakib/cfviz](https://github.com/sjsakib/cfviz/).

This website has three features:

-   Visualize various information about a user with cool charts (e.g., problem difficulty distribution).
-   Compare two users.
-   Calculate rating predictions for a contest.

## Competitive Companion

This tool is a browser extension used to parse test case data from web pages. It supports parsing almost all major OJ platforms (e.g., Codeforces, AtCoder). After using this extension, you never need to manually copy any test case data.

The source code is hosted at [jmerle/competitive-companion](https://github.com/jmerle/competitive-companion).

Usage:

-   Install the extension on Chrome or Firefox. The tool will send parsed test case data in JSON format to the specified port.
-   Install any tool on your local machine that can read data from port monitoring. See the [official example](https://github.com/jmerle/competitive-companion-example) for reference.

Demo:

![Competitive Companion demo](images/oj-tool-3.apng)

Demo created using [bytetools](https://github.com/zqxyz73/bytetools) by [zqxyz73](https://github.com/zqxyz73).

## ac-predictor

ac-predictor is an extension that lets you know the rating changes of a contest before AtCoder ratings are updated.

This tool is a Tampermonkey script, so you need to first install [Tampermonkey](https://www.tampermonkey.net/).

After that, go to [greasyfork](https://greasyfork.org/scripts/369954-ac-predictor) and click to install.

After installation, the contest standings page will display rating change predictions for each user.

This tool has a Chinese-translated version by [GoodCoder666](https://github.com/GoodCoder666), click [here](https://greasyfork.org/scripts/458528-ac-predictor-cn) to install.
