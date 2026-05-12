## Introduction

### What is LaTeX

LaTeX (pronounced /ˈlɑːtɛx/ or /ˈleɪtɛx/) is a typesetting system that makes your documents look more professional, rather than a word processor. It is especially suitable for handling long, well-structured documents, and is very good at handling mathematical expressions. It is free software and works on most operating systems.

LaTeX is based on TeX (a typesetting system designed by Donald Knuth in 1978 for digital typesetting). TeX is a low-level language that computers can process, but most people find it difficult to use. LaTeX was designed to make it easier to use. The current version of LaTeX is LaTeX 2ε.

If you are used to using Microsoft's Office Word to process documents, you will find the way LaTeX works unfamiliar. Word is a typical "what you see is what you get" editor, where you can see the final typesetting effect while editing the document. However, with LaTeX you cannot easily preview the final result, which allows you to focus on the content rather than the appearance.

A LaTeX document is a text file ending in `.tex`, which can be edited with any text editor, such as Notepad, but for most people, using a suitable LaTeX editor makes the editing process much easier. During editing, you can mark the structure of the document. When finished, you can compile it—which means converting it to another format. It supports many formats, but the most common is PDF format.

### Before You Start

The following notations are used in this document:

-   Operations you need to perform are marked with an arrow $\rightarrow$;
-   Characters you need to enter are placed in code blocks;
-   Menu commands and button names are marked as **bold**.

### Some Concepts

If you need to write LaTeX documents, you need to install a "distribution". Common distributions include [TeX Live](http://tug.org/texlive/), [MikTeX](https://miktex.org/), and MacTeX for macOS users (which is actually the macOS version of TeX Live). [CTeX](http://www.ctex.org/) is no longer recommended. TeX Live and MacTeX come with almost all LaTeX packages; MikTeX only comes with a few essential packages, and other packages will be installed when needed.

Both TeX Live and MikTeX come with the TeXworks editor. You can also install the more feature-rich TeXstudio editor, or configure Visual Studio Code or Notepad++ yourself. The editor used below is TeXworks running on Windows 7.

Most distributions come with multiple engines, such as pdfTeX and XeTeX. For Chinese users, XeTeX is recommended for Unicode support.

TeX has multiple formats, such as Plain TeX and LaTeX. Generally, LaTeX format is used now. So you need to use the engine bundled with the format you are using. For pdfTeX, you need to use pdfLaTeX; for XeTeX, use XeLaTeX.

Extended reading: [Introduction to TeX Engine, Format, and Distribution](https://liam.page/2018/11/26/introduction-to-TeX-engine-format-and-distribution/).

### Environment Setup

For Windows users, you need to download TeX Live or MikTeX. Chinese users can use [Tsinghua University TUNA Mirror](https://mirrors.tuna.tsinghua.edu.cn/). Click the "Get Download Link" button on the right side of the page and select "TeX Typesetting System" under the "Applications" tab to download the TeX Live or MikTeX installer. The TeX Live installer is an ISO file, which needs to be mounted and then executed as administrator with `install-tl-advanced.bat`.

For macOS users, Tsinghua University TUNA Mirror also provides downloads for MacTeX and macOS version of MikTeX.

For Linux users, if using TeX Live, also download the ISO file and execute the `install-tl` script; if using MikTeX, follow the [official documentation](https://miktex.org/download#unx) for installation.

## Document Structure

### Basic Elements

$\rightarrow$ Open TeXworks.

A new document will be opened automatically.

$\rightarrow$ Go to the **Format** menu and select **Line Numbers**.

Line numbers are not essential, but they can help you compare code with screen information and find errors.

$\rightarrow$ Go to the **Format** menu, select **Syntax Coloring**, and then choose **LaTeX**.

Syntax highlighting highlights the code, making it more readable.

$\rightarrow$ Enter the following text:

```tex
\documentclass[a4paper, 12pt]{article}

\begin{document}
  A sentence of text.
\end{document}
```

The `\documentclass` command must appear at the beginning of every LaTeX document. The text in curly braces specifies the document type. The **article** document type is suitable for shorter articles, such as journal articles and short reports. Other document types include **report** (for longer multi-chapter documents, such as doctoral theses), **proc** (conference proceedings), **book**, and **beamer**. The text in square brackets specifies some options—in the example, it sets the paper size to A4 and the main text size to 12pt.

The `\begin{document}` and `\end{document}` commands wrap your text content. Any text before `\begin{document}` is considered a preamble command and affects the entire document. Any text after `\end{document}` is ignored.

Blank lines are not necessary, but they can make long documents more readable.

$\rightarrow$ Click the **Save** button; $\rightarrow$ Create a new folder named **LaTeX course** in **Libraries>Documents**; $\rightarrow$ Name your document **Doc1** and save it as a **TeX document** in this folder.

Putting different LaTeX documents in different directories and combining multiple files during compilation is a good idea.

$\rightarrow$ Make sure the typeset menu is set to **xeLaTeX**. $\rightarrow$ Click the **Typeset** button.

Your source file will be converted to a PDF document, which takes some time. After compilation finishes, TeXworks' PDF viewer will open and preview the generated file. The PDF file will be automatically saved in the same directory as the TeX document.

### Handling Problems

If there are errors in your document and TeXworks cannot create the PDF document, the **Typeset** button will turn into a red cross, and the terminal output at the bottom will remain expanded. At this point:

$\rightarrow$ Click the **Abort typesetting** button. $\rightarrow$ Read the terminal output; the last line may give a line number indicating where the error occurred. $\rightarrow$ Find the corresponding line in the document and fix the error. $\rightarrow$ Click the **Typeset** button again to try compiling the source file.

### Adding a Document Title

The `\maketitile` command creates a title for your document. You need to specify the document title. If no date is specified, the current date is used, and the author is optional.

$\rightarrow$ Immediately after the `\begin{document}` command, enter the following text:

```tex
\title{My First Document}
\author{My Name}
\date{\today}
\maketitle
```

Your document now looks like this:

```tex
\documentclass[a4paper, 12pt]{article}

\begin{document}
  \title{My First Document}
  \author{My Name}
  \date{\today}
  \maketitile

  A sentence of text.
\end{document}
```

$\rightarrow$ Click the **Typeset** button and check the generated PDF document.

Key notes:

-   `\today` is the command to insert the current date. You can also enter a different date, such as `\date{November 2013}`.
-   The body of an **article** document is typeset on the same page immediately after the title. **report** places the title on a separate page.

### Sections

If needed, you may want to divide your document into chapters, sections, and subsections. The following sectioning commands apply to **article** type documents:

-   `\section{...}`
-   `\subsection{...}`
-   `\subsubsection{...}`
-   `\paragraph{...}`
-   `\subparagraph{...}`

The text in curly braces represents the section title. For **report** and **book** type documents, we also support the `\chapter{...}` command.

$\rightarrow$ Replace "A sentence of text." with the following text:

```tex
\section{Introduction}
This is the introduction.

\section{Methods}

\subsection{Stage 1}
The first part of the methods.

\subsection{Stage 2}
The second part of the methods.

\section{Results}
Here are my results.
```

Your document becomes

```tex
\documentclass[a4paper, 12pt]{article}

\begin{document}
  \title{My First Document}
  \author{My Name}
  \date{\today}
  \maketitile

  \section{Introduction}
  This is the introduction.

  \section{Methods}

  \subsection{Stage 1}
  The first part of the methods.

  \subsection{Stage 2}
  The second part of the methods.

  \section{Results}
  Here are my results.
\end{document}
```

$\rightarrow$ Click the **Typeset** button and check the PDF document. It should look like this:

![p1](images/latex-for-beginners-1.png)

### Creating Labels

You can create labels for any section command so they can be referenced in other parts of the document. Use `\label{labelname}` to create a label for a section. Then enter `\ref{labelname}` or `\pageref{labelname}` to reference the corresponding section.

$\rightarrow$ On a new line after `\subsection{Stage 1}`, enter `\label{sec1}`. $\rightarrow$ In the **Results** section, enter `Referring to section \ref{sec1} on page \pageref{sec1}`.

Your document becomes:

```tex
\documentclass[a4paper, 12pt]{article}

\begin{document}
  \title{My First Document}
  \author{My Name}
  \date{\today}
  \maketitile

  \section{Introduction}
  This is the introduction.

  \section{Methods}

  \subsection{Stage 1}
  \label{sec1} The first part of the methods.

  \subsection{Stage 2}
  The second part of the methods.

  \section{Results}
  Here are my results. Referring to section \ref{sec1} on page \pageref{sec1}
\end{document}
```

$\rightarrow$ Compile and check the PDF document (you may need to compile twice):

![p2](images/latex-for-beginners-2.png)

### Generating a Table of Contents (TOC)

If you use sectioning commands, you can easily generate a table of contents. Use `\tableofcontents` to create a table of contents in the document. Usually we create the table of contents after the title.

You may also want to change the page numbers to Roman numerals (i, ii, iii). This ensures that the main body of the document starts from page 1. Page numbers can be switched between Arabic and Roman numerals using `\pagenumbering{...}`.

$\rightarrow$ Enter the following after `\maketitile`:

```tex
\pagenumbering{roman}
\tableofcontents
\newpage
\pagenumbering{arabic}
```

The `\newpage` command starts a new page so that we can see the effect of the `\pagenumbering` command. The first 14 lines of your document look like this:

```tex
\documentclass[a4paper, 12pt]{article}

\begin{document}

\title{My First Document}
\author{My Name}
\date{\today}
\maketitile

\pagenumbering{roman}
\tableofcontents
\newpage
\pagenumbering{arabic}
```

$\rightarrow$ Compile and check the document (may need multiple compilations, not repeated below).

The first page looks like this:

![p3](images/latex-for-beginners-3.png)

The second page:

![p4](images/latex-for-beginners-4.png)

## Text Processing

### Chinese Font Support

For those learning LaTeX by reading this document, the first thing to master is LaTeX's Chinese font support. In fact, there are many ways to make LaTeX support Chinese fonts. Here we only give the most **concise** solution: use the CTeX package. Simply add to the preamble section of the document:

```tex
\usepackage[UTF8]{ctex}
```

When compiling the document, use the `xelatex` command, as it supports Chinese fonts.

### Font Effects

LaTeX has various font effects. Here are some examples:

```tex
\textit{words in italics} \textsl{words slanted} \textsc{words in smallcaps} \textbf{words
in bold} \texttt{words in teletype} \textsf{sans serif words} \textrm{roman
words} \underline{underlined words}
```

The result looks like:

![p5](images/latex-for-beginners-5.png)

$\rightarrow$ Add more text to your document and try various font effects.

### Colored Text

To enable colored text in your document, you need to use a package. You can reference many packages to enhance LaTeX's typesetting effects. Package reference commands are placed in the preamble (i.e., before the `\begin{document}` command). Use `\usepackage[options]{package}` to reference a package, where **package** is the name of the package and **options** are some parameters specifying the package's features.

After using `\usepackage{color}`, we can call common colors:

![p6](images/latex-for-beginners-6.png)

The code for colored text is:

```tex
{\color{colorname}text}
```

Where **colorname** is the name of the color you want, and **text** is your colored text content. Note that the yellow and white in the example have text background colors, which we can also achieve using the `\colorbox` command from the Color package. The usage is:

```tex
\colorbox{colorname}{text}
```

$\rightarrow$ Enter `\usepackage{color}` before `\begin{document}`. $\rightarrow$ Enter `{\color{red}fire}` in the document content. $\rightarrow$ Compile and check the PDF document content.

The word "fire" should be red.

You can also add some parameters to call more colors, or even customize the colors you need. But this goes beyond the scope of this book. For more information about colored text, please read the Colors chapter in the LaTeX Wikibook.

### Font Size

Next, we list some LaTeX font size setting commands:

```tex
normal size words {\tiny tiny words} {\scriptsizepcriptsize words}
{\footnotesizepcriptsize words} {\small small words} {\large large words}
{\Large Large words} {\LARGE LARGE words} {\huge huge words}
```

The result looks like:

![p7](images/latex-for-beginners-7.png)

$\rightarrow$ Try adjusting the font size for your text.

### Paragraph Indentation

LaTeX indents the first line of the first paragraph of each section to the margin, and subsequent paragraphs are indented. If you want the paragraph to start at the margin, add the `\endoza` command before the paragraph. If you want all paragraphs to start at the margin, use `\setlength{\parindent}{0pt}` at some position in the document, after which all paragraphs will start at the margin.

### Lists

LaTeX supports two types of lists: ordered lists (enumerate) and unordered lists (itemize). List items are defined with `\item`. Lists can have sublists.

$\rightarrow$ Enter the following to create an ordered list with an unordered list:

```tex
\begin{enumerate}
  \item First thing

  \item Second thing
    \begin{itemize}
      \item A sub-thing

      \item Another sub-thing
    \end{itemize}

  \item Third thing
\end{enumerate}
```

$\rightarrow$ Compile and check the PDF document.

The list looks like:

![p8](images/latex-for-beginners-8.png)

You can use square bracket parameters to modify the bullet symbol for unordered lists. For example, `\item[-]` will use a dash as the bullet, or you can even use a word, such as `\item[One]`.

The following code:

```tex
\begin{itemize}
  \item[-] First thing

  \item[+] Second thing
    \begin{itemize}
      \item[Fish] A sub-thing

      \item[Plants] Another sub-thing
    \end{itemize}

  \item[Q] Third thing
\end{itemize}
```

Generates:

![p9](images/latex-for-beginners-9.png)

### Comments and Spaces

We use `%` to create a single-line comment. Everything on that line after this character is ignored until the next line starts.

The following code:

```tex
It is a truth universally acknowledged% Note comic irony
in the very first sentence , that a single man in possession of a good fortune,
must be in want of a wife.
```

Generates:

![p10](images/latex-for-beginners-10.png)

Multiple consecutive spaces in LaTeX are treated as one space. Multiple consecutive blank lines are treated as one blank line. The main function of blank lines is to start a new paragraph. Generally, LaTeX ignores blank lines and other whitespace characters; two backslashes (`\\`) can be used to break a line.

$\rightarrow$ Try adding comments and blank lines to your document.

If you want to add space in your document, you can use the `\vspace{...}` command. This adds vertical space, and the height can be specified. For example, `\vspace{12pt}` produces a space equal to the height of 12pt text.

### Special Characters

The following characters are special characters in LaTeX:

```text
# $ % ^ & _ { } ~ \
```

To use these characters, we need to escape them by adding a backslash before them:

```tex
\# \$ \% \^{} \& \_ \{ \} \~{}
```

Note that when using `^` and `~` characters, they need to be followed by a pair of closing curly braces, otherwise they will be interpreted as superscripts, just like `\^ e` becomes $\mathrm {\hat{e}}$. The code above generates:

![p11](images/latex-for-beginners-11.png)

Note that a backslash cannot be escaped by a backslash (otherwise it becomes a line break); use the `\textbackslash` command instead.

$\rightarrow$ Enter code to generate the following content in your document:

![p12](images/latex-for-beginners-12.png)

Consult an expert or check the [source code](https://github.com/OI-wiki/OI-wiki/blob/master/docs/tools/latex.md?plain=1) of this page for help.

## Tables

The tabular command is used for typesetting tables. LaTeX does not have horizontal or vertical lines by default—you need to set them manually if needed. LaTeX automatically sets the table width based on the content. The following code creates a table:

```tex
\begin{tabular}{...}
```

The ellipsis is replaced by code defining the table columns:

-   `l` represents a left-aligned column;
-   `r` represents a right-aligned column;
-   `c` represents a center-aligned column;
-   `|` represents a vertical line between columns.

For example, `{lll}` generates a three-column table, all left-aligned, without explicit vertical lines; `{|l|l|r|}` generates a three-column table, the first two columns left-aligned, the last column right-aligned, with explicit vertical lines between adjacent columns.

Table data is entered after `\begin{tabular}`:

-   `&` is used to separate columns;
-   `\\` is used to start a new row;
-   `\hline` represents inserting a horizontal line spanning all columns;
-   `\cline{1-2}` inserts a horizontal line between the first and second columns.

Finally, use `\end{tabular}` to end the table. Here are some examples:

```tex
\begin{tabular}{|l|l|}
  Apples       & Green  \\
  Strawberries & Red    \\
  Orange       & Orange \\
\end{tabular}

\begin{tabular}{rc}
  Apples              & Green  \\
  \hline
  Strawberries        & Red    \\
  \cline{1-1} Oranges & Orange \\
\end{tabular}

\begin{tabular}{|r|l|}
  \hline
  8              & here's \\
  \cline{2-2} 86 & stuff  \\
  \hline
  \hline
  2008           & now    \\
  \hline
\end{tabular}
```

The result looks like:

![p13](images/latex-for-beginners-13.png)

### Practice

Try to draw the following table:

![p14](images/latex-for-beginners-14.png)

## Figures

This chapter introduces how to insert figures in LaTeX documents. Here we need to introduce the **graphicx** package. Images should be PDF, PNG, JPEG, or GIF files. The following code inserts an image named myimage:

```tex
\begin{figure}[h]
  \centering
  \includegraphics[width=1\textwidth]{myimage}
  \caption{Here is my image}
  \label{image-myimage}
\end{figure}
```

`[h]` is the position parameter, **h** means place the figure approximately here (if it fits). Other options: **t** means place at the top of the page; **b** means place at the bottom of the page; **p** means place on a separate page. You can also add a **!** parameter to force placement at the specified position (although the typesetting result may not be ideal).

`\centering` centers the image on the page. Without this command, it defaults to left alignment. Using it gives good results because the figure caption is also centered.

The `\includegraphics{...}` command automatically places the figure in your document. The image file should be in the same directory as the TeX file.

`[width=1\textwidth]` is an optional parameter specifying the image width—equal to the text width. Width can also be specified in centimeters. You can also use `[scale=0.5]` to scale down the image proportionally (the example is scaled down by half).

`\caption{...}` defines the figure caption. If used, LaTeX adds a numbered "Figure" prefix to your figure. You can use `\listoffigures` to generate a list of figures.

`\label{...}` creates a label that you can reference.

### Practice

$\rightarrow$ Add `\usepackage{graphicx}` to the preamble of your document. $\rightarrow$ Find an image and place it in your **LaTeX course** folder. $\rightarrow$ Enter the following where you want to add the image:

```tex
\begin{figure}[h!]
  \centering
  \includegraphics[width=1\textwidth]{ImageFilename}
  \caption{My test image}
\end{figure}
```

Replace **ImageFilename** with your file name (without the extension). If your file name has spaces, use double quotes, for example `"screen 20"`.

$\rightarrow$ Compile and check the file.

## Formulas

One of the main reasons to use LaTeX is that it can easily typeset formulas. We use math mode to typeset formulas.

### Inserting Formulas

You can use a pair of `$` to enable math mode, which can be used for inline math formulas. For example, `$1+2=3$` produces $1+2=3$.

If you want a displayed formula, you can use `$$...$$` (now we recommend `\[...\]` because the former may produce bad spacing). For example, `$$1+2=3$$` produces

$$
1+2=3
$$

If you want a numbered formula, you can use `\begin{equation}...\end{equation}`. For example:

```tex
\begin{equation}
  1+2=3
\end{equation}
```

Produces:

![equation](images/latex-equation.svg)

The number 6 represents the section number, which only appears when your document has sections set up, such as in **report** type documents.

Use `\begin{aligned}...\end{aligned}` to write a set of numbered equations. For example:

```tex
\begin{aligned}
  a & = & b + c \\
  & = & y - z
\end{aligned}
```

Produces

![eqnarray](images/latex-eqnarray.svg)

To write an unnumbered formula, add a `*` after the environment name, such as `{equation*}`, `{aligned*}`.

??? warning "Warning"
    It can be found that when using `eqnarray`, there are problems like excessive spacing around the equals sign.
    
    You can use the `align` environment from the `amsmath` package:
    
    ```tex
    \usepackage{amsmath}
    ...
    \begin{align}
      a & = b + c \\
        & = y - z
    \end{align}
    ```
    
    Or use the `aligned` environment in displayed formulas. Their names followed by a star make the equations unnumbered.
    
    See "4.4 Multiline Formulas" in the first reference in [Further Reading](#further-reading).

### Math Symbols

Although some basic symbols can be typed directly, most special symbols need to be displayed using commands.

This book is only an introductory tutorial on math symbols. The Math Symbols chapter in the LaTeX Wikibook is another better and more complete tutorial. If you want to learn more about math symbols, please refer to it. If you want to find a specific symbol, you can use [Detexify](http://detexify.kirelabs.org), which can recognize handwritten characters.

#### Superscripts and Subscripts

Superscripts (Powers) use `^`, for example `$n^2$` produces $n^2$.

Subscripts (Indices) use `_`, for example `$2_a$` produces $2_a$.

If the superscript or subscript contains multiple characters, enclose them in curly braces. For example, `$b_{a-2}$` produces $b_{a-2}$.

#### Fractions

Fractions are inserted using the `\frac{numerator}{denominator}` command. For example, `$$\frac{a}{3}$$` produces

$$
\frac{a}{3}
$$

Fractions can be nested. For example, `$$\frac{y}{\frac{3}{x}+b}$$` produces

$$
\frac{y}{\frac{3}{x}+b}
$$

#### Square Roots

We use the `\sqrt{...}` command to insert square roots. The ellipsis is replaced by the content under the root. If you need to add the root index, enclose it in square brackets.

For example, `$$\sqrt{y^2}$$` produces

$$
\sqrt{y^2}
$$

And `$$\sqrt[x]{y^2}$$` produces

$$
\sqrt[x]{y^2}
$$

#### Summation and Integration

Use `\sum` and `\int` to insert summation and integral signs. For both symbols, the upper limit is represented by `^`, and the lower limit by `_`.

`$$\sum_{x=1}^5 y^z$$` produces

$$
\sum_{x=1}^5y^z
$$

And `$$\int_a^b f(x)$$` produces

$$
\int_a^b f(x)
$$

#### Greek Letters

We can use a backslash followed by the name of a Greek letter to represent a Greek letter. The case of the first letter determines the form of the Greek letter. For example

-   `$\alpha$`=$\alpha$
-   `$\beta$`=$\beta$
-   `$\delta, \Delta$`=$\delta, \Delta$
-   `$\pi, \Pi$`=$\pi, \Pi$
-   `$\sigma, \Sigma$`=$\sigma, \Sigma$
-   `$\phi, \Phi, \varphi$`=$\phi, \Phi, \varphi$
-   `$\psi, \Psi$`=$\psi, \Psi$
-   `$\omega, \Omega$`=$\omega, \Omega$

### Practice

$\rightarrow$ Write code to generate the following formulas:

![p15](images/latex-for-beginners-15.png)

If you need help, you can check the [source code](https://github.com/OI-wiki/OI-wiki/blob/master/docs/tools/latex.md?plain=1) of this page.

## Bibliography

### Introduction

LaTeX can easily insert bibliography and table of contents. This section will introduce how to use another BibTeX file to store references.

### BibTeX File Types

A BibTeX file contains all the references you want to cite in your document. Its file extension is `.bib`. Its name should be set to the name of your TeX document. `.bib` files are text files. You need to enter your references in the following format:

```text
@article{
    Birdetal2001,
    Author = {Bird, R. B. and Smith, E. A. and Bird, D. W.},
    Title = {The hunting handicap: costly signaling in human foraging strategies},
    Journal = {Behavioral Ecology and Sociobiology},
    Volume = {50},
    Pages = {9-19},
    Year = {2001} 
}
```

Each reference first declares its reference type. The example uses @article; other types include @book, @incollection for citing a chapter in a book, and @inproceedings for citing conference papers. More supported types can be found [here](http://en.wikibooks.org/wiki/LaTeX/Bibliography_Management).

In the following curly braces, a citation key must be listed first. You must ensure that the citation keys for your references are different. You can customize the key string, but using the first author's name plus the year is a clear choice.

The following several lines include some information about the reference, in the following format:

```text
Field name = {field contents},
```

You can use LaTeX commands to generate special text effects. For example, italic can be used with `\emph{Rattus norvegicus}`.

For letters that need to be capitalized, enclose them in curly braces. BibTeX will automatically replace all capital letters except the first letter in the title with lowercase. For example, `Dispersal in the contemporary United States` produces $\text{Dispersal in the contemporary united states}$, while `Dispersal in the contemporary {U}nited {S}tates` produces $\text{Dispersal in the contemporary United States}$.

You can write BibTeX files manually or use software to generate them.

### Inserting the Bibliography

Use the following commands to insert the bibliography at the current position in the document:

```tex
\bibliographystyle{plain}
\bibliography{references}
```

The references are written in `references.bib`.

### Bibliography Citations

Use `\cite{citationkey}` to insert a citation where you want to reference a source. If you do not want to insert a citation in the main text but still want it to appear in the bibliography, use the `\nocite{citationkey}` command.

To insert page information in a citation, use square brackets: `\cite[p. 215]{citationkey}`.

To cite multiple references, separate them with commas: `\cite{citation01,citation02,citation03}`.

### Citation Styles

#### Numbered Citations

LaTeX includes several in-text numbered citation styles:

**Plain** uses bracketed numbers, such as $[1]$. The bibliography is sorted alphabetically by first author's name. Each author's name is in full.

**Abbrv** is the same as **plain**, but author names are abbreviated.

**Unsrt** is the same as **plain**, but the bibliography is sorted by the order of citation in the text.

**Alpha** is the same as **plain**, but the citation label is the author's name and year combined, not a number, such as $[Kop10]$.

#### Author-Date Citations

If you want to use author-date citations, use the **natbib** package. It uses the `\citep{...}` command to generate a bracketed citation, such as $[Koppe,2010]$, and uses `\citet{...}` to generate a citation with only the year in brackets, such as $Koppe [2010]$. See its more detailed usage [here](http://mirror.ctan.org/macros/latex/contrib/natbib/natnotes.pdf).

The natbib package also has three styles: **plainnat**, **abbrvnat**, and **unsrtnat**, which have the same effect as **plain**, **abbrv**, and **unsrt**.

#### Other Citation Styles

If you need to use different styles, you need to create a style file (`.bst` file) in the same folder, and reference this style using its file name in the `\bibliographystyle{...}` command.

### Practice

$\rightarrow$ Create a BibTeX file with the same name in the same folder and enter the reference information in the correct format. $\rightarrow$ Switch to the TeX document and use `\cite`, `\bibliographystyle`, and `\bibliography` commands to cite references. $\rightarrow$ Compile the TeX file. $\rightarrow$ Switch to the BibTeX file and compile it (click the **Typeset** button). $\rightarrow$ Switch to the TeX file and compile it **twice**, then check the PDF document.

## Further Reading

-   A (Not So) Short Introduction to LaTeX 2ε <https://github.com/CTeX-org/lshort-zh-cn/releases/download/v6.02/lshort-zh-cn.pdf> or 112 Minutes to LaTeX 2ε.

-   LaTeX Project <http://www.latex-project.org/> Official website - has links to documentation, information about installing LaTeX on your own computer, and information about where to look for help.

-   LaTeX Wikibook <http://en.wikibooks.org/wiki/LaTeX/> Comprehensive and clearly written, although still a work in progress. A downloadable PDF is also available.

-   Comparison of TeX Editors on Wikipedia <http://en.wikipedia.org/wiki/Comparison_of_TeX_editors> Information to help you to choose which LaTeX editor to install on your own computer.

-   TeX Live <http://www.tug.org/texlive/> "An easy way to get up and running with the TeX document production system". Available for Unix and Windows (links to MacTeX for macOS users). Includes the TeXworks editor.

-   Workbook Source Files <http://edin.ac/17EQPM1> Download the .tex file and other files needed to compile this workbook.

**This document is translated from [http://www.docs.is.ed.ac.uk/skills/documents/3722/3722-2014.pdf](https://web.archive.org/web/20220309055041/http://www.docs.is.ed.ac.uk/skills/documents/3722/3722-2014.pdf)**, with modifications based on other references.