This page mainly answers some frequently asked questions.

## I Want to Ask Questions Related to This Wiki

Q: Why did you want to create this Wiki?

A: When you were learning **OI**, did you ever feel lost and helpless when facing the enormous body of knowledge? What **OI Wiki** wants to do may be something like "allowing more students with limited contest resources to conveniently access training resources". Of course, this wording is not complete. The motivation for creating the Wiki may also be very simple: just wanting to make a tiny contribution to the development of **OI**. XD

***

Q: I am very interested. How can I participate?

A: **OI Wiki** is now hosted on GitHub. You can directly visit this [repo](https://github.com/OI-wiki/OI-wiki) to see the latest progress. Ways to participate include opening [Issues](https://github.com/OI-wiki/OI-wiki/issues) or [Pull Requests](https://github.com/OI-wiki/OI-wiki/pulls) on GitHub, sharing your ideas in the discussion groups, or submitting content directly to administrators. The framework we currently use is [MkDocs](https://mkdocs.readthedocs.io), developed in Python. It supports Markdown format and also supports inserting mathematical formulas.

***

Q: But I am not very strong... I do not know what I can do.

A: Everything starts from passion. You can help others review and revise drafts, help us promote **OI Wiki**, and help create a good learning and communication atmosphere for the community!

***

Q: Who is mainly doing this now? It feels like a huge project. Can it really be done well?

A: At the beginning, it was mainly some retired veteran contestants doing this. Later, we met many like-minded friends: current contestants, retired players, and friends who have never participated in **OI**. Currently, this project is mainly maintained by the **OI Wiki** project team. Below is a group photo.

<a href="https://github.com/OI-wiki/OI-wiki/graphs/contributors"><img src="https://opencollective.com/oi-wiki/contributors.svg?width=890&button=false"/></a>

Of course, it is difficult to make this project perfect with only our own efforts, so we sincerely invite you to improve **OI Wiki** together.

***

Q: How do you ensure that the content we add will not suddenly disappear?

A: We host the content on [GitHub](https://github.com/OI-wiki/OI-wiki), so even if our server fails, the content will not be lost. In addition, we regularly back up everyone's hard work, so even if GitHub shuts down one day (?), our content will not be lost.

***

Q: **OI Wiki** seems to have empty pages!

A: Yes. Due to the project team's limits in ability and time, we cannot complete these empty pages for now. Therefore, we are soliciting contributions and recruiting here, hoping to meet friends with the same ideas so that we can improve **OI Wiki** together.

***

Q: Why not write on [Chinese Wikipedia](https://zh.wikipedia.org/) directly?

A: Because we hope to truly help more contestants and people interested in this content. Also, for well-known reasons, content on Chinese Wikipedia is not accessible without barriers.

## I Want to Participate!

Q: How can I communicate with the project team?

A: You can contact us through the [communication methods on the About page](./about.md#交流方式).

***

Q: How can I contribute code or content?

Please refer to the [How to Contribute](./htc.md) page.

***

Q: Where is the navigation?

A: The navigation is in the [mkdocs.yml](https://github.com/OI-wiki/OI-wiki/blob/master/mkdocs.yml#L17) file under the project root directory.

***

Q: How do I modify the content of a topic?

A: There is an edit button <i class="md-icon">edit</i> in the upper right of the corresponding page. Click it, confirm that you have read [How to Contribute](./htc.md), and you will be redirected to the corresponding file on GitHub.

Alternatively, you can read the navigation file [(mkdocs.yml)](https://github.com/OI-wiki/OI-wiki/blob/master/mkdocs.yml) yourself to find the file location.

***

Q: How do I add a topic?

A: There are two options:

-   Open an Issue and describe the content you want to add.
-   Open a Pull Request, add the new topic to the navigation [(mkdocs.yml)](https://github.com/OI-wiki/OI-wiki/blob/master/mkdocs.yml), and create an empty `.md` file at the corresponding location under the [docs](https://github.com/OI-wiki/OI-wiki/tree/master/docs) directory. For formatting details, refer to the [style guide](./format.md#贡献文档要求).

***

Q: I encountered difficulties when trying to access GitHub.

A: We recommend adding the following lines to your hosts file:[^ref1]

```text
# GitHub Start
140.82.114.25                 alive.github.com
140.82.113.5                  api.github.com
185.199.110.153               assets-cdn.github.com
185.199.111.133               avatars.githubusercontent.com
185.199.111.133               avatars0.githubusercontent.com
185.199.111.133               avatars1.githubusercontent.com
185.199.111.133               avatars2.githubusercontent.com
185.199.111.133               avatars3.githubusercontent.com
185.199.111.133               avatars4.githubusercontent.com
185.199.111.133               avatars5.githubusercontent.com
185.199.111.133               camo.githubusercontent.com
140.82.112.22                 central.github.com
185.199.111.133               cloud.githubusercontent.com
140.82.114.9                  codeload.github.com
185.199.111.133               desktop.githubusercontent.com
185.199.111.133               favicons.githubusercontent.com
140.82.112.3                  gist.github.com
52.216.163.147                github-cloud.s3.amazonaws.com
52.217.124.1                  github-com.s3.amazonaws.com
52.216.144.83                 github-production-release-asset-2e65be.s3.amazonaws.com
52.217.121.249                github-production-repository-file-5c1aeb.s3.amazonaws.com
52.217.206.57                 github-production-user-asset-6210df.s3.amazonaws.com
192.0.66.2                    github.blog
140.82.114.4                  github.com
140.82.113.18                 github.community
185.199.110.154               github.githubassets.com
151.101.1.194                 github.global.ssl.fastly.net
185.199.110.153               github.io
185.199.111.133               github.map.fastly.net
185.199.110.153               githubstatus.com
140.82.112.25                 live.github.com
185.199.111.133               media.githubusercontent.com
185.199.111.133               objects.githubusercontent.com
13.107.42.16                  pipelines.actions.githubusercontent.com
185.199.111.133               raw.githubusercontent.com
185.199.111.133               user-images.githubusercontent.com
13.107.253.40                 vscode.dev
140.82.112.21                 education.github.com
# GitHub End
```

You can learn the latest content and more information on [GitHub520](https://gitee.com/klmahuaw/GitHub520).

Linux and macOS users can try using [依云](https://github.com/lilydjwg/)'s [gh-check script](https://gist.github.com/lilydjwg/93d33ed04547e1b9f7a86b64ef2ed058) to get the fastest IP addresses. The `--hosts` parameter can directly update the hosts file. Use the `--help` parameter to get usage help. Before use, install Python3 and aiohttp with `pip install aiohttp -i https://pypi.tuna.tsinghua.edu.cn/simple/`. Blog introduction by 依云: [寻找最快的 GitHub IP](https://blog.lilydjwg.me/2019/8/16/gh-check.214730.html).

At the same time, you can use the [Gitclone](https://www.gitclone.com/) service to accelerate cloning. Read the instructions on its homepage.

If you only want to clone the **OI Wiki** repository:

```bash
git clone https://gitclone.com/github.com/OI-wiki/OI-wiki
```

If you need to contribute to **OI Wiki**, first fork the **OI Wiki** repository, then replace `username` with your username. Note that the example provided will make you connect to GitHub over SSH:[^only-ssh-connect]

```bash
git clone https://gitclone.com/github.com/username/OI-wiki
git remote set-url origin git@github.com:username/OI-wiki.git
```

***

Q: pip is too slow here!

A: You can switch to a mainland China mirror,[^ref2] or use:

```bash
pip install -U -r requirements.txt -i https://pypi.tuna.tsinghua.edu.cn/simple/
```

***

Q: I cloned this project with a client, but it is too slow.

A: If you have `git bash` installed, you can add some restrictions to reduce the download size.[^ref3]

```bash
git clone https://github.com/OI-wiki/OI-wiki.git --depth=1 -b master
```

***

Q: I have never installed Python 3.

A: You can visit the [official Python website](https://www.python.org/downloads/) for more information.

***

Q: It seems to tell me that my pip version is too low.

A: After entering cmd/shell, run the following command:

```bash
python -m pip install --upgrade pip
```

***

Q: Dependency installation failed.

A: Check: network? permissions? error message?

***

Q: I have already cloned it. Why can I not deploy it?

A: Check whether the dependencies are installed properly.

***

Q: I cloned the repo a long time ago. How do I update it to the new version?

A: Please refer to GitHub's official help page [Syncing a fork - GitHub Docs](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/syncing-a-fork).

***

Q: If I installed previous dependencies, how do I update them?

A: Enter the following command:

```bash
pip install -U -r requirements.txt
```

***

Q: Why is my markdown formatting messed up?

A: You can consult [cyent's notes](https://web.archive.org/web/20221103014610/https://cyent.github.io/markdown-with-mkdocs-material/) or [MkDocs usage instructions](https://github.com/ctf-wiki/ctf-wiki/wiki/Mkdocs-%E4%BD%BF%E7%94%A8%E8%AF%B4%E6%98%8E).

We currently use [remark-lint](https://github.com/remarkjs/remark-lint) to automatically fix formatting. Some [configuration](https://github.com/OI-wiki/OI-wiki/blob/master/.remarkrc) may still be imperfect, and feedback is welcome.

***

Q: Does GitHub not display my mathematical formulas?

A: Yes, GitHub's preview does not display mathematical formulas. But do not worry: MkDocs supports mathematical formulas and can use any syntax supported by MathJax normally.

***

Q: Why are my formulas garbled?

A: For display formulas（用的 `$$`），目前已知的问题是需要在 `$$` both sides to have blank lines, and `$$` must be placed **alone** on a line without preceding spaces. The format is as follows:

```text
// blank line
$$
a_i
$$
// blank line
```

***

Q: Why does my formula not display properly in the table of contents? It seems doubled.

A: Yes, this is a python-markdown bug and may be fixed soon.

If you want to avoid doubled formulas in the table of contents, refer to the table-of-contents style used for SAM under the [string category](https://github.com/OI-wiki/OI-wiki/blame/master/docs/string/sam.md#L73).

```text
结束位置 <script type="math/tex">endpos</script>
```

In the table of contents it becomes

```text
结束位置 endpos
```

Note: for now, please avoid introducing MathJax formulas into the table of contents as much as possible.

***

Q: How can I declare copyright information for a single page?

A: Add one line at the beginning of the page.[^ref4]

For example:

```text
copyright: SATA
```

Note: the defaults are CC BY-SA 4.0 and SATA.

***

Q: Why does the author statistics area not show my name?

A: If you find that you wrote part of a page but were not recorded in the author list, you can add your GitHub ID to the [author field](./htc.md#author-字段) at the top of the file.

***

Thank you for reading to the end. What we urgently need now is your help.

The **OI Wiki** project team

2018.8

## References and Notes

[^ref1]: [GitHub520](https://gitee.com/klmahuaw/GitHub520)

[^ref2]: [Change pip source to a mainland China mirror - L 瑜 - CSDN Blog](https://blog.csdn.net/lambert310/article/details/52412059)

[^ref3]: [GIT--- 看我一步步入门 (Windows Git Bash)](https://blog.csdn.net/FreeApe/article/details/46845555)

[^ref4]: [Metadata - Material for MkDocs](https://squidfunk.github.io/mkdocs-material/extensions/metadata/#usage)

[^only-ssh-connect]: GitHub has deprecated password-based HTTPS authentication. Connections must use SSH or a Personal Access Token. See [Which remote URL should I use?](https://docs.github.com/cn/github/using-git/which-remote-url-should-i-use), [Creating a personal access token](https://docs.github.com/cn/github/authenticating-to-github/creating-a-personal-access-token), and [Connecting to GitHub with SSH](https://docs.github.com/cn/github/authenticating-to-github/connecting-to-github-with-ssh).
