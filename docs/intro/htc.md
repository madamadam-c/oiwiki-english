Before the article begins, all members of the **OI Wiki** project team warmly welcome you to contribute pages to this project. It is thanks to hundreds of people like you that **OI Wiki** has become what it is today!

This article mainly describes the workflow for participating in **OI Wiki** writing. Before drafting or fixing Wiki pages, please read the following content carefully to help you produce higher-quality content.

## Contribution Guide

Before editing, please read the [OI Wiki contribution guide](https://github.com/OI-wiki/OI-wiki/blob/master/.github/CONTRIBUTING.md) and the [project policy](./about.md#项目方针) so that you can better cooperate and communicate with community contributors.

## Participating in Collaboration

???+ warning "Warning"
    Before writing a section, please check [Issues](https://github.com/OI-wiki/OI-wiki/issues) to confirm that no one else is doing the same work, then open a [new issue](https://github.com/OI-wiki/OI-wiki/issues/new) to record the content to be written.

???+ tip "Tip"
    Issues also contain many problems waiting to be fixed or resolved, especially our Iteration Plan. Getting a task from there is a great start!

To ensure the professionalism and accuracy of entries, we recommend considering the following points before editing:

1.  **Choose fields you are familiar with**: prioritize entries related to your expertise, learning background, or interests. This helps you create high-quality content.
2.  **Be cautious with new fields**: if you are still a beginner in a topic or do not know it well, we recommend first reading and studying to deepen your understanding, then editing once you are reasonably confident.
3.  **Consult relevant materials**: when adding content to or revising entries, we recommend checking authoritative literature and materials first to ensure accuracy. You are also welcome to ask questions in page comments or in our community and discuss them with other editors.

We value every contributor's enthusiasm and effort, and we also understand that everyone has a different level of expertise. Let us work together to care for this knowledge garden and help more readers with accurate, professional content. We look forward to your contributions! To quote Wikipedia:

> Do not be afraid to edit. Be bold in updating pages![^ref1]

### Editing on GitHub

Participating in **OI Wiki** writing **requires** a GitHub account. You can register on the [GitHub sign-up page](https://github.com/signup). However, it **does not require** advanced GitHub skills. Even if you are a beginner, you can still edit **very well** by following the steps below.

???+ tip "Tip"
    Before your changes are merged into the main **OI Wiki** repository, changes you make to **OI Wiki** content will not appear on the main **OI Wiki** site, so you do not need to worry about breaking the content currently displayed on **OI Wiki**.
    
    If you are still concerned, you can read [GitHub's official tutorials](https://skills.github.com/).

#### Editing Content in a Single Page

1.  Find the corresponding page on **OI Wiki**.
2.  Click the **"Edit this page"** (<i class="md-icon">edit</i>) button in the upper right of the article body, to the left of the table of contents. After confirming that you have read this page and the [style guide](./format.md), click the button and follow the prompts to edit on GitHub.
3.  Write the content you want to modify in the editor. During editing and the following submission process, please **turn off your automatic translation software**, because it may cause unnecessary trouble, such as incorrectly renaming the file and affecting the directory structure.
4.  After writing, scroll to the bottom of the page, fill in the commit message according to the [commit message format](#commit-信息格式规范) in this article, then click **Propose changes** to submit the modification. After you click the button, GitHub will automatically create a fork of the **OI Wiki** repository for you and add your commit to that fork.
5.  GitHub will automatically jump to your fork page. At this point, a green **Create pull request** button will appear near the top of the page. Click it, and GitHub will jump to a Pull Request creation page. Scroll down, check that your changes are correct, write the Pull Request information according to the [Pull Request message format](#pull-request-信息格式规范), then click the green **Create pull request** button to create the Pull Request.
6.  If nothing unexpected happens, your Pull Request will be submitted to the repository successfully, and you only need to wait for administrators to review it and merge it into the main repository.

While waiting for the merge, you can comment on, upvote, or downvote other people's Pull Requests. If there are new notifications, a prompt will appear in the upper right of the page, with email notifications depending on your personal notification settings.

#### Editing Content in Multiple Pages

If you need to edit multiple unrelated pages at the same time, follow the [editing content in a single page](#编辑单个页面内的内容) section above and modify all pages at once.

1.  Open the [OI-Wiki/OI-Wiki](https://github.com/OI-Wiki/OI-Wiki) repository and press <kbd>.</kbd> on the keyboard, or change `github.com` in the URL to `github.dev`, to enter GitHub's web-based VS Code editor.[^ref2]
2.  Make changes to the page source files in the editor. You can use the preview button in the upper right, or press the <kbd>Ctrl+K</kbd><kbd>V</kbd> shortcut, to open a preview on the right.
3.  After finishing the changes, use the Source Control tab on the left, fill in the commit message according to the [commit message format](#commit-信息格式规范), and commit. When prompted whether to create a fork of this repository, click the green **Fork Repository** button.
4.  After committing, a prompt will pop up at the top center of the page. Fill in the title in the first prompt and the branch name in your repository for this commit in the second prompt. Then a prompt like `Created Pull Request #1 for OI-Wiki/OI-Wiki.` will pop up in the lower right. Click the blue link to view the Pull Request.

#### Appending Changes to a Pull Request

1.  Open the [OI-Wiki Pull Request list](https://github.com/OI-wiki/OI-wiki/pulls), find your Pull Request, and click it.
2.  Under the Pull Request title, there will be text such as `<your ID> wants to merge x commits into OI-wiki:master from <your ID>:patch-1`. Click the `<your ID>:patch-1` part.
3.  You should be redirected to your fork, and the branch name in the upper left of the file list should be the branch name of your Pull Request, `patch-1` in this example.
4.  Make the changes you need.
    -   If you need to edit a single file or multiple unrelated pages, directly find the files you need and modify them. After finishing, scroll to the bottom of the page, fill in the commit message according to the [commit message format](#commit-信息格式规范), then click **Commit changes**.
    -   If you need to edit multiple files, press <kbd>.</kbd> on the keyboard, or change `github.com` in the URL to `github.dev`, to enter GitHub's web-based VS Code editor and make changes.[^ref2] Then use the Source Control tab on the left, fill in the commit message according to the [commit message format](#commit-信息格式规范), and commit the changes.
5.  Your changes will then be automatically appended to your Pull Request.

### Editing Locally with Git

???+ warning "Warning"
    For general users, we recommend using the GitHub web editor described above.

Although in most cases you can edit directly on GitHub, for special cases, such as requiring GPG signatures, we recommend editing locally with Git.

The general workflow is as follows:

1.  Fork the main repository to your own repository.
2.  Clone the forked repository locally.
3.  Make local changes and commit them.
4.  Push these changes to the forked repository you cloned.
5.  Submit a Pull Request to the main repository.

For detailed operations, refer to the [Git](../tools/git.md) page.

#### Appending Changes to a Pull Request

Continue modifying the locally cloned fork, then commit and push those changes. Your changes will be automatically appended to the Pull Request.

### Previewing Changes in the Built Site

At the bottom of the Pull Request page, you can find the test page. Click the Details link for netlify/oi-wiki/deploy-preview, as shown below, to enter an automatically built preview page generated from your changes.

![deploy\_preview](./images/deploy_preview.png)

### Changes to Navigation and References

Usually, if you need to add a new page or modify the link to an existing page in the navigation, you need to modify [`mkdocs.yml`](https://github.com/OI-wiki/OI-wiki/blob/master/mkdocs.yml).

To add a new page, refer to the existing format. However, unless you are refactoring or correcting terminology, **we do not recommend modifying existing page reference links**. Unnecessary changes in Pull Requests will also be rejected.

If you insist on modifying links, remember to update the author field and redirect file.

### author Field

The GitHub API cannot track statistics after file directory changes, so we manually maintain an author list at the top of each file to solve this problem. The author field is located at the very beginning of a Markdown file and looks like `author: Ir1d, cjsoft`, with adjacent IDs separated by a comma and a space. The ID is the GitHub username, that is, the GitHub profile address. For example, in <https://github.com/Ir1d>, the ID is `Ir1d`.

When modifying links, you need to fill the author field with each contributor of the current page.

### Redirect File

When modifying links, you need to modify the redirect file to avoid broken links from external references.

The [`_redirects`](https://github.com/OI-wiki/OI-wiki/blob/master/docs/_redirects) file is used to generate [Netlify configuration](https://docs.netlify.com/routing/redirects/#syntax-for-the-redirects-file) and [redirect files](https://github.com/OI-wiki/OI-wiki/blob/master/scripts/gen_redirect.py).

Each line represents one redirect rule, with the source and destination URLs, excluding the domain name:

```text
/path/to/src /path/to/desc
```

Note: all redirects are 301 redirects, and they only need to be modified when changing a URL in the navigation would cause a broken link.

<a id="commit-信息格式规范"></a>

### Commit Message Format

For commit messages, please follow these basic requirements:

1.  The commit summary should briefly describe the content changed in this commit. Note that the commit summary should not exceed 50 characters; excess content will automatically be placed in the body.
2.  If you need to further describe this commit, explain it in detail in the body.

For the commit summary, we recommend the following format:

```text
<change type>(<file name>): <changed content>
```

Change types are divided into the following categories:

-   `feat`: used when adding content.
-   `fix`: used when correcting errors in existing content.
-   `refactor`: used when refactoring a page, meaning larger-scale changes.
-   `revert`: used when reverting previous changes.

<a id="pull-request-信息格式规范"></a>

### Pull Request Message Format

For Pull Requests, please follow these requirements:

1.  The title should state the purpose of this PR, namely **what** work was done and **what** problem was fixed.
2.  The body should briefly describe the modifications. If it fixes an issue, add a `fix #xxxx` field in the body, where `xxxx` is the issue number.
3.  Please carefully read the [contribution guide](https://github.com/OI-wiki/OI-wiki/blob/master/.github/CONTRIBUTING.md) and the [community covenant](https://github.com/OI-wiki/OI-wiki/blob/master/CODE_OF_CONDUCT.md), then check the box in the PR template to indicate that you agree with the guide and covenant.

For Pull Request titles, we recommend the following format:

```plain
<change type>(<file name>): <changed content> (<corresponding issue number>)
```

Change types are divided into the following categories:

-   `feat`: used when adding content.
-   `fix`: used when correcting errors in existing content.
-   `refactor`: used when refactoring a page, meaning larger-scale changes.
-   `revert`: used when reverting previous changes.

Examples:

-   `fix(ds/persistent-seg): make code comments clearer`
-   `fix: tools/judger/index is not in the navigation (#3709)`
-   `feat(math/poly/fft): better proof`
-   `refactor(ds/stack): reorganize page content`

### Collaboration Workflow

1.  After a new Pull Request is received, GitHub sends an email to reviewers.
2.  At the same time, two sets of tests run on [GitHub Actions](https://github.com/OI-wiki/OI-wiki/actions) and [Netlify](https://app.netlify.com/sites/oi-wiki), and they synchronize progress at the bottom of the PR page. GitHub Actions mainly confirms that content changes in the PR do not affect the website build process. Netlify builds the updates in the PR so reviewers can inspect them. After the tests finish, click Details to learn more.
3.  Reviewers may find problems and submit `review` or `suggested changes`, shown as a gray icon, or `requested changes`, shown as a red icon and only available when the reviewer has write permission to the repo. In general, reviewers will also attach suggestions and required changes. At that point, you will need to append more changes to the Pull Request. For how to do this, refer to the `Appending Changes to a Pull Request` parts under `Editing on GitHub` or `Editing Locally with Git`.
4.  A PR can only be merged into the master branch after enough reviewers vote to approve it.
5.  After it is merged into the master branch, GitHub Actions rebuilds the website content and updates the gh-pages branch.
6.  Only then will the server pull updates from the gh-pages branch and redeploy the latest content.

## References and Notes

[^ref1]: [Wikipedia: Contributing to Wikipedia](https://zh.wikipedia.org/wiki/Wikipedia:%E6%96%B0%E6%89%8B%E5%85%A5%E9%96%80/%E7%B7%A8%E8%BC%AF)

[^ref2]: [Web-based editor - GitHub Codespaces - GitHub Docs](https://docs.github.com/en/codespaces/developing-in-codespaces/web-based-editor)
