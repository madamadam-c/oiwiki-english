???+ note "Note"
    This page focuses on introducing Git, a version control system. For GitHub-related content, please refer to [GitHub Help](https://docs.github.com) and [How to Contribute - OI Wiki](../intro/htc.md).

Git is one of the most widely used version control systems. **OI Wiki** also uses Git as its version control system.

## Installation

See [Git - Downloads](https://git-scm.com/downloads).

## Configuration

Based on the scope of configuration files, Git divides them into different levels. Two commonly used levels are:

1.  Global configuration file for the current user, which is consulted for all repositories on the system operated by that user.
2.  Configuration file for the current repository.

When multiple configuration files set the same option, local settings will automatically override global settings. Therefore, if you need to apply specific settings to a particular repository, you only need to change the settings in that repository without affecting global settings.

To modify configuration files, you need to use the `git config` command.

### Setting User Information

After installing Git, the first thing to do is set your username and email. This information is used for every commit.

```console
$ git config --global user.name "OI Wiki"
$ git config --global user.email oi-wiki@example.com
```

???+ note "Note"
    The username and email provided here are for demonstration only. When configuring according to the content on this page, remember to replace them with your own information.

The `--global` here indicates that the global configuration is being modified, meaning this setting applies to all repositories under the current user. If you don't add the `--global` option, the current repository's configuration file will be modified by default.

If you want to modify specific settings for a particular repository, simply run the command without `--global` in that repository.

### Configuring the Editor

```console
$ git config --global core.editor emacs
```

Running the above command changes the editor to [Emacs](./editor/emacs.md).

On Windows, Git's default editor can be selected during Git installation (see above). To modify it later, run the above command in Git Bash, replacing the editor name with the absolute path of your editor.

### Displaying Configuration

You can use `git config -l` to list all currently set configuration parameters. Using `git config --global -l` lists all global configurations.

## Repository Operations Basics

### Creating a New Git Repository

Creating a new Git repository is very simple. Just run the following command in the folder where you want to create the repository:

```console
$ git init
```

Git will create a `.git` folder in the current directory, and a repository is created.

If you want to clone a repository to your computer (for example, copying the **OI Wiki** code locally for editing), you can use the `git clone` command.

```console
$ git clone https://github.com/OI-wiki/OI-wiki
```

???+ note "Remote Repository Link"
    The repository link provided here is an HTTP(S) link, meaning we use HTTP(S) to connect to the remote repository.

    In fact, there are multiple ways to connect to a remote repository. Using SSH to connect to the remote repository is more convenient and secure. We will briefly introduce how to use SSH to connect to a remote repository in the "Managing Remote Repositories" section.

This way, the content of the cloned repository will be stored in a new folder with the same name as the repository in the current directory. In this example, a new folder named `OI-wiki` will appear in the current directory.

### Tracking Files

After making changes to the files in a repository, these changes need to be included in version control.

You can use the `git status` command to check the status of the repository's files.

For example, after adding a new `README.md` file to an empty repository, running the `git status` command produces the following result:

<!-- scripts.linter.preprocess.fix_details off -->

```console
$ git status
On branch master

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)

        README.md

nothing added to commit but untracked files present (use "git add" to track)
```

<!-- scripts.linter.preprocess.fix_details on -->

Here, Untracked files refers to files that Git has not included in version tracking. If a file is not tracked, changes to that file will not be recorded by Git.

Running the `git add <file>` command adds the specified file to version tracking.

<!-- scripts.linter.preprocess.fix_details off -->

```console
$ git add README.md # Add this file to version tracking
$ git status
On branch master

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)

        new file:   README.md
```

<!-- scripts.linter.preprocess.fix_details on -->

At this point, `README.md` has been added to version tracking and placed in the staging area. Now you only need to run the `git commit` command to commit this change.

But before doing this, let's make a small change to `README.md`.

<!-- scripts.linter.preprocess.fix_details off -->

```console
$ vim README.md # Make some changes
$ git status
On branch master

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)

        new file:   README.md

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore -- <file>..." to discard changes in working directory)

        modified:   README.md
```

<!-- scripts.linter.preprocess.fix_details on -->

You will find that `README.md` is in both the staging area and non-staging area. Actually, whether it's in the staging area applies to changes, not to files. So the first change to `README.md` has been staged, while the second change has not. If you run the `git commit` command at this time, only the staged changes will be committed, and the unstaged changes will not be committed.

Git gives a hint that running `git add README.md` will add the unstaged changes to the staging area.

???+ note "Staging All Changes at Once"
    The `git add` command puts the changes to the specified file into the staging area.

    In most cases, users prefer to stage all changes at once. In this case, you can use the `git add -A` command. This command puts all changes (including untracked files, but excluding ignored files) into the staging area.

    If you only need to update files that are already being tracked without adding untracked files to the staging area, you can use `git add -u`.

???+ note "Ignoring Files"
    Sometimes we don't want to include certain files (such as executable files) in version tracking. In this case, you can create a `.gitignore` file in the repository's root directory and write the files you want to ignore in it. Git will not include these files in version tracking.

    For example, `*.exe` will automatically ignore all files with the `.exe` extension in the repository.

Now add the unstaged file to the staging area and commit all changes together.

```console
$ git add README.md
$ git commit # An editor will pop up, you need to write the commit message
[master (root-commit) f992763] initial commit
 1 file changed, 2 insertions(+)
 create mode 100644 README.md
```

Now let's focus on the commit information.

`master` indicates that we are currently on the `master` branch (branch-related issues will be described in detail later), and `f992763` represents the first few digits of the SHA-1 checksum of this commit, followed by the commit message.

What deserves special attention is the SHA-1 checksum here. Each checksum corresponds to a snapshot of the repository at a certain point in time. Using this feature, we can access a snapshot of the repository at some point in history and make changes on that snapshot.

The next two lines detail the file changes involved in this update.

Additionally, there are several parameters that can be used to simplify the commit process:

-   `-a`: Before committing, put all changes to tracked files into the staging area. Note that untracked files (newly created files) will not be automatically added to the staging area and need to be manually added using the `git add` command.
-   `-m`: This parameter is followed by a commit message, indicating that the changes are committed with that message. For example, `git commit -m "fix: typo"` will create a commit with the title `fix: typo`.

### Viewing Commit History

You can use the `git log` command to view the commit history of the repository.

As you can see, the commit history records the SHA-1 checksum of each commit, the author of the commit, the commit time, and the commit message.

```console
$ git log
commit ae9dd3768a405b348bc6170c7acb8b6cb5fe333e (HEAD -> master)
Author: OI Wiki <oi-wiki@example.com>
Date:   Sun Sep 13 00:30:18 2020 +0800

    feat: update README.md

commit f99276362a3c260d439364c505a7a06859f34bf9
Author: OI Wiki <oi-wiki@example.com>
Date:   Sun Sep 13 00:06:07 2020 +0800

    initial commit
```

## Branch Management

Why do we need branch management in version control? There are two main reasons:

1.  Directly modifying the main branch will not only make the history messy but may also cause some dangerous consequences.
2.  Through branching, we can focus on the current work. If we need to do two different tasks, we just need to create two branches, and the work on the two branches will not interfere with each other.

In Git, simply put, a branch is a pointer to a certain snapshot. Every time you commit, Git creates a snapshot of that commit and moves the current branch's pointer to that snapshot.

Additionally, there is an HEAD pointer that points to the current branch.

The process of switching branches, simply put, is to change the HEAD pointer from pointing to the current branch to pointing to another branch. During this process, Git automatically updates the files, so that after switching branches, the state of the repository is consistent with the snapshot pointed to by the target branch.

### Creating a Branch

You can use the `git branch` command to create a branch, the `git switch` command to switch branches, and the `git switch -c` command to create a branch and switch to this new branch.

```console
$ git switch -c dev # Create a new branch called dev and switch to dev
Switched to branch 'dev'
$ git branch # View branch list
  master
* dev
```

The asterisk before `dev` indicates that the current branch of this repository is `dev`. All subsequent changes to this repository will be recorded on this branch.

Let's try creating a new file `aplusb.cpp`.

```console
$ vim aplusb.cpp
$ git add aplusb.cpp
$ git commit -m "feat: add A+B Problem code"
[dev 5da093b] feat: add A+B Problem code
 1 file changed, 7 insertions(+)
 create mode 100644 aplusb.cpp
```

Now switch back to the `master` branch. At this time, the `aplusb.cpp` file is no longer in the folder, and everything returns to the state when the `dev` branch was just created. At this point, you can continue working on other tasks on the `master` branch.

```console
$ git switch master
Switched to branch 'master'
$ vim README.md # Make some small changes to README
$ git commit -a -m "feat: update README.md"
[master 5ca15f0] feat: update README.md
 1 file changed, 1 insertion(+), 1 deletion(-)
```

Now let's use a diagram to explain the operation process.

![](./images/git1.svg)

The `master` branch is marked red, indicating that after these operations, it is the current branch (i.e., the position pointed to by HEAD).

-   Initially, `master` points to the snapshot `ae9dd37`.
-   Next, a new dev branch was created at the position where `master` is located. This branch initially points to the same position as master.
-   Some changes were made on the `dev` branch (created `aplusb.cpp`), and a commit was made. After this commit, the `dev` branch points to the snapshot `5da093b`.
-   After switching back to the `master` branch, because `master` still points to `ae9dd37` and hasn't created `aplusb.cpp` yet, this file is not in the repository.
-   Next, changes were made on the `master` branch (updated `README.md`), and a commit was made. The `master` branch now points to the snapshot `5ca15f0`.

### Merging Branches

When the work on one branch is complete, you can merge this work into another branch.

Continuing with the example above, the work on the `dev` branch is complete. You can use the `git merge` command to merge this branch into the current branch (`master`):

```console
$ git merge dev
Merge made by the 'recursive' strategy.
 aplusb.cpp | 7 +++++++
 1 file changed, 7 insertions(+)
 create mode 100644 aplusb.cpp
```

![](./images/git2.svg)

How exactly is this merge performed?

Before the merge, `master` points to `5ca15f0`, while `dev` points to `5da093b`. These two states are not on the same chain.

Git finds the most recent common ancestor of these two states (in the diagram above, it is `ae9dd37`) and merges these three snapshots. The result of the merge is used as a new snapshot, and the current branch points to this snapshot.

The merge process itself is also a commit, but unlike a regular commit, a merge commit has more than one parent commit. It's the result of merging multiple commit states.

After the merge is complete, the `dev` branch has completed its mission. At this point, you can use the following command to delete the `dev` branch:

```console
$ git branch -d dev # For unmerged branches, you can use the -D parameter to force deletion
```

However, the merge process is not always smooth. In some cases, conflicts may occur during the merge. This issue will be discussed next.

### Resolving Merge Conflicts

If two branches have made different changes to the same part of the same file, Git cannot automatically merge these two branches, meaning a merge conflict has occurred.

Continuing with the example above, suppose that based on the merged `master` branch, you created a new `readme-refactor` branch to rewrite the README. But due to some oversight, you changed the README on both the `readme-refactor` and `master` branches.

Initially, the README looked like this:

```markdown
# This is a test repo.

This repo includes some c++ codes.
```

The README on the `readme-refactor` branch looks like this:

```markdown
# Code Library

This repo includes some c++ codes.
```

The README on the `master` branch looks like this:

```markdown
# This is a code library.

This repo includes some c++ codes.
```

At this time, running the `git merge readme-refactor` command, Git reports a merge conflict.

Run the `git status` command to see which files caused the conflict.

<!-- scripts.linter.preprocess.fix_details off -->

```console
$ git status
On branch master
You have unmerged paths.
  (fix conflicts and run "git commit")

Unmerged paths:
  (use "git add <file>..." to mark resolution)

    both modified:      README.md

no changes added to commit (use "git add" and/or "git commit -a")
```

<!-- scripts.linter.preprocess.fix_details on -->

How to resolve conflicts? For each file with a merge conflict, Git adds standard conflict resolution markers to these files. For example, for the `README.md` file in this example, after opening it, it looks like this:

```markdown
<<<<<<< HEAD
# This is a code library.
=======
# Code Library
>>>>>>> readme-refactor

This repo includes some c++ codes.
```

The `======` acts as a boundary separating the contents of the two branches. The content between the `<<<<<<< HEAD` marker and `======` is the content of the HEAD pointer (the `master` branch), while the content between `======` and `>>>>>>> readme-refactor` is the content of the `readme-refactor` branch.

To resolve the conflict, edit the text, delete these conflict markers, save the file, add these files to the staging area, and then commit. This resolves the merge conflict.

```console
$ git add README.md # Add the conflicted file to the staging area
$ git commit
[master fe92c6b] Merge branch readme-refactor into master
```

### Other Merge Methods

By default, Git uses the Merge method to merge two branches. When using this method to merge branch B into branch A, all commits from branch B will be included in branch A's commit history.

In addition, Git provides two other ways to merge branches: Squash and Rebase.

#### Squash

When using Squash to merge branch B into branch A, all changes on branch B will be merged into one commit and submitted to branch A.

You can use the Squash method for branch merging by adding the `--squash` parameter to `git merge`.

```console
$ git merge <branch> --squash
```

It should be noted that after executing the above command, Git will only store all changes from branch B into branch A's staging area. After that, you still need to execute a `git commit` command to complete the merge.

Using Squash for merging can simplify the commit history, but you will lose information specific to each commit (such as the author of each commit, the changes in each commit, etc.). Only the information merged as a whole remains (the author of each commit will be listed in the commit message in the form of "Co-authored-by"). However, if you perform Squash and Merge on GitHub, all original information can be viewed in the Pull Request.

#### Rebase

When using Rebase to merge branch B into branch A, each commit on branch B will be individually added to branch A, rather than creating a merge commit to merge the contents of two branches like the Merge method.

First, switch to branch B, then rebase branch B onto branch A:

```console
$ git checkout B
$ git rebase A
```

Now switch back to branch A and run the `git merge` command again to complete merging the contents of branch B into branch A.

```console
$ git checkout A
$ git merge B
```

Using Rebase to complete the merge can linearize the commit history. Using Rebase correctly in appropriate scenarios can achieve better results than Merge. However, doing so changes the commit history. The likelihood of conflicts increases both during Rebase and when performing related merge operations after Rebase. If not done properly, it may make the commit history messy. Therefore, if you don't have a thorough understanding of Rebase operations, it is not recommended to use it.

## Managing Remote Repositories

After making changes locally, you may need to push these changes to GitHub or other Git repository hosting platforms. Repositories hosted on these platforms fall under the category of remote repositories—you can fetch information from these repositories and push your changes to remote repositories. Collaboration with others often relies on remote repositories, so learning to manage remote repositories is essential.

### Viewing Remote Repositories

You can use the `git remote` command to view the list of remote repositories for the current repository.

If the current repository is a clone, there should be a remote repository called origin, and its link is the link used for cloning.

```console
$ git remote
origin
```

If you want to view detailed information about a remote repository, you can do this:

```console
$ git remote show origin
* remote origin
  Fetch URL: git@github.com:OI-wiki/OI-wiki.git
  Push  URL: git@github.com:OI-wiki/OI-wiki.git
  HEAD branch: master
  Remote branches:
    git             tracked
    master          tracked
  ...
```

### Configuring Remote Repositories

Running `git remote add <name> <url>` adds a remote repository with the name `name` and the link `url`.

Running `git remote rename <oldname> <newname>` renames a remote repository from `oldname` to `newname`.

Running `git remote rm <name>` deletes a remote repository named `name`.

Running `git remote get-url <name>` views the link of a remote repository named `name`.

Running `git remote set-url <name> <newurl>` changes the link of a remote repository named `name` to `newurl`.

### Fetching Changes from Remote Repositories

In remote repositories, others may push some changes. Running the `git fetch` command fetches these changes to the local repository.

```console
$ git fetch <remote-name> # Fetch changes from <remote-name>
```

It should be noted that the `git fetch` command only fetches the changes from the remote repository and does not merge these changes into the local repository. If you need to merge these changes, you can use the `git pull` command. By default, `git pull` is equivalent to `git fetch` followed by `git merge FETCH_HEAD`.

```console
$ git pull <remote-name> <branch> # Fetch changes from <remote-name>, then merge these changes into HEAD
```

### Pushing Changes to Remote Repositories

When you have completed some changes, you can use the `git push` command to push these changes to the remote repository.

```console
$ git push <remote> <from>:<to> # Push changes from local <from> branch to <remote>'s <to> branch
```

Depending on the remote repository's requirements, you may need to enter the username and password for the remote repository account.

It should be noted that for your changes to be pushed successfully, two conditions must be met: you have write permission to this repository (branch), and your branch is newer than the corresponding branch on the remote repository (it can be understood that no one pushed during the time you made your changes). When the remote branch has new changes that the current branch doesn't have, you can run `git pull` to complete the merge first before pushing.

If you need to force push the local branch's changes to the remote repository, you can add the `-f` parameter. At this time, **the remote repository's commit history will be overwritten by the local commit history**, so this command should be used with caution. A better choice is to use the `--force-with-lease` parameter, which only overwrites when the remote repository hasn't been updated. It should be noted that "update" here is relative to the last fetch. If you use VS Code's Auto Fetch feature, you might not notice the update, making `--force-with-lease` just as dangerous as `-f`.

### Tracking Remote Branches

By setting a local branch to track a remote branch, you can conveniently see the difference between the local branch and the remote branch, and simplify operations when interacting with remote branches.

Before tracking, you need to run `git fetch <remote-name>` to fetch the remote repository's information to the local repository.

Next, running `git switch <remote-branch>` will automatically create a new local branch with the name `<remote-branch>` and set this branch to automatically track the corresponding remote branch.

???+ note "Note"
    Note that Git will only automatically create this branch and set it to track the corresponding remote branch when the local branch doesn't exist and there's exactly one remote branch with a matching name.

At this time, running the `git status` command will prompt the difference between the current branch and the remote branch.

Because the local branch is set to track a remote branch, the command to push to the remote branch is also simplified. You only need to run the `git command`, and changes made on the local branch can be pushed to the remote branch it tracks.

For existing local branches, setting their corresponding remote tracking branch is also easy. Just run `git branch -u <remote-name>/<remote-branch>` under the current branch to set the current local branch to track the remote branch `<remote-name>/<remote-branch>`.

### Using SSH Connection

Compared with HTTP(S), using SSH to connect to remote repositories is more convenient and secure.

Before using SSH to connect to a remote repository, you need to add an SSH key locally. Next, you need to upload the **public key** of the locally added SSH key to your remote repository account.

Considering that this article is mainly for **OI Wiki** contributors to provide a tutorial on using Git, here we directly provide [the tutorial from GitHub Docs](https://docs.github.com/en/github/authenticating-to-github/connecting-to-github-with-ssh) for your reference.

After completing the above steps, you can connect to the remote repository via SSH. Below is a command to clone the **OI Wiki** repository via SSH:

```console
$ git clone git@github.com:OI-wiki/OI-wiki.git
```

The process of pushing changes to the remote repository is similar to using HTTP(S). However, using SSH eliminates the need to verify the remote repository account password.

## Git GUI Tools

For those who are not familiar with the command line, the pure command-line Git may have a higher learning curve. Using GUI tools can reduce the difficulty of getting started with Git to some extent. Additionally, compared to the command line, GUI tools have a certain degree of improvement in experience when viewing diffs and logs.

Git itself comes with a GUI, and there are many excellent Git GUI tools available, such as TortoiseGit[^note3] for Windows users, Sourcetree[^note4] for Windows and Mac, etc.

Here we briefly introduce the usage of TortoiseGit. After downloading and installing TortoiseGit, in the local repository's directory, right-click with the mouse, and you can see Git's various functions in the right-click menu.

![TortoiseGit Example](images/git11.png)

Detailed usage instructions are not elaborated here. You can refer to the documentation on the official website or learn through search engines, for example, [TortoiseGit Manual](https://tortoisegit.org/docs/tortoisegit/index.html).

Many GUI tools have official Chinese support, such as Git Desktop and TortoiseGit. However, some translations may look awkward, so using the English version is recommended.

## External Links

-   [Git Reference](https://git-scm.com/docs)
-   [Pro Git Book](https://git-scm.com/book/en/v2)
-   [Learn Git Branching](https://learngitbranching.js.org/)

## References and Notes

[^note1]: In fact, Git also has a system-wide configuration file that applies to every user on the system and all repositories on the system. This configuration file has the widest scope and is at a level above the user configuration file. Since this configuration is rarely used in practice, it is not elaborated here.

[^note2]: The [Pro Git Book](https://git-scm.com/book/en/v2/Git-Branching-Rebasing) provides visual diagrams of the Rebase process. With the help of these diagrams, readers can better understand the mechanism of Rebase.

[^note3]: [TortoiseGit](https://tortoisegit.org/)

[^note4]: [Sourcetree](https://www.sourcetreeapp.com/)