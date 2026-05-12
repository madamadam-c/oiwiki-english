author: minghu6

Prerequisites: [Prefix Function and KMP Algorithm](./kmp.md).

KMP algorithm exploits the information from prefix matching to the fullest.

The basic idea behind BM algorithm is to achieve faster character skipping by gaining more information from suffix matching than from prefix matching.

## Introduction

Imagine our pattern string $pat$ is placed at the leftmost head of text string $string$, aligning their first characters.

$$
\begin{aligned}
\textit{pat}:\qquad\qquad &\texttt{EXAMPLE} \\
\textit{string}:\qquad\quad &\texttt{HERE IS A SIMPLE EXAMPLE} \dots \\
&\qquad\ \ \ \, \, \Uparrow
\end{aligned}
$$

Here we define: the length of $pat$ is $patlen$, and especially for strings starting from 0, we define $patlastpos=patlen-1$ as the position of the last character of $pat$;

The length of $string$ is $stringlen$, $stringlastpos = stringlen-1$.

Suppose we know the $patlen$-th character of $string$ (aligned with the last character of $pat$), let's consider what information we can obtain:

### Observation 1

If we know that this character $char$ does not appear in $pat$, we don't need to consider the cases where $pat$ appears starting from the 1st, 2nd, ..., $patlen$-th character of $string$, and we can simply slide $pat$ down by $patlen$ characters.

### Observation 2

More generally, **if the position where $char$ appears at the end (i.e., rightmost) of $pat$ is $delta_1$ characters away from the end**,

Then we can skip directly by $delta_1$ characters: if the slide distance is less than $delta_1$, then only the character $char$ cannot match, and of course the pattern string $pat$ won't match.

Therefore, unless $char$ can match the last character of $pat$, $string$ must skip $delta_1$ characters (equivalent to sliding $pat$ backward by $delta_1$ characters). And we can obtain a function $delta_1(char)$ to calculate $delta_1$:

$$
\begin{array}{ll}
\textbf{int}\ delta1(\textbf{char}\ char) \\
\qquad \textbf{if}\ \text{char not in pat || char is the last character on pat} \\
\qquad\qquad\textbf{return}\ patlen \\
\qquad \textbf{else} \\
\qquad\qquad\textbf{return}\ patlastpos-i\quad\textbf{//}\ \text{i is the position where char appears at the rightmost end of pat, i.e., pat[i]=char}
\end{array}
$$

Note that this table clearly only needs to be calculated up to position $patlastpos-1$.

Now suppose $char$ matches the last character of $pat$, then let's see if the character before $char$ matches the second-to-last character of $pat$:

If it does, continue backing up until the entire pattern string $pat$ completes matching (at which point we've successfully found a match of $pat$ in $string$);

Or, we might mismatch after matching the $m$-th-to-last character of $pat$, at the $(m+1)$-th-to-last character. At this point, we want to slide $pat$ forward to the next position where a match might be possible, and of course we want to slide as far as possible.

### Observation 3(a)

In **Observation 2**, after matching the last $m$ characters of $pat$, if we mismatch at the $(m+1)$-th-to-last character, in order to align the mismatched character in $string$ with its corresponding character on $pat$,

We need to slide $pat$ backward by $k$ characters, meaning we should look at the subsequent $k+m$ characters (that is, look at the character aligned with $string$ after sliding $pat$ by $k$).

And $k=delta_1-m$,

So our attention should jump backward along $string$ by $delta_1-m+m = delta_1$ characters.

However, we have the opportunity to skip more characters—continue reading.

### Observation 3(b)

If we know that the next $m$ characters of $string$ match the last $m$ characters of $pat$, suppose this substring is $subpat$,

We also know that after the mismatched character $char$ in $string$ there is a substring matching $subpat$. And if there exists $subpat$ before the corresponding mismatched character on $pat$, we can slide $pat$ down by a distance,

So that the $subpat$ (plausible reoccurrence, abbreviated as pr) that appears before the corresponding character of the mismatched character $char$ on $pat$ aligns with the $subpat$ in $string$. If there are multiple $subpat$ on $pat$, take the first one according to the right-to-left suffix matching order (rightmost plausible reoccurrence, abbreviated as rpr).

Assume at this point $pat$ slides down by $k$ characters (i.e., the distance between the $subpat$ at the end of $pat$ and its rightmost plausible reoccurrence), then our attention should slide along $string$ by $k+m$ characters. This distance is called $delta_2(j)$:

Assume $rpr(j)$ is the position of the rightmost plausible reoccurrence of $subpat=pat[j+1\dots patlastpos]$ when mismatching at $pat[j]$, $rpr(j) < j$ (this is a simple definition; more precise discussion will be in the algorithm design section below), then obviously $k=j-rpr(j),\ m=patlastpos-j$.

So we have:

$$
\begin{array}{ll}
\textbf{int}\ delta2(\textbf{int}\ j) \quad\textbf{//}\ \text{j is the position of the character on pat corresponding to the mismatched character} \\
\qquad\qquad\textbf{return}\ patlastpos-rpr(j) \\
\end{array}
$$

Thus when mismatching, we can skip $\max(delta_1,delta_2)$ characters on $string$.

## Process

The arrow points to the mismatched character $char$:

$$
\begin{aligned}
\textit{pat}:\qquad\qquad &\texttt{AT-THAT} \\
\textit{string}:\ \ \ \dots\ &\texttt{WHICH-FINALLY-HALTS.--AT-THAT-POINT} \dots \\
&\qquad\ \ \ \, \, \Uparrow
\end{aligned}
$$

$\texttt{F}$ does not appear in $pat$. According to **Observation 1**, $pat$ directly moves down by $patlen$ characters, which is 7 characters:

$$
\begin{aligned}
\textit{pat}:\qquad\qquad &\qquad\quad\ \ \, \texttt{AT-THAT} \\
\textit{string}:\ \ \ \dots\ &\texttt{WHICH-FINALLY-HALTS.--AT-THAT-POINT} \dots \\
&\qquad\ \ \ \, \, \qquad\quad\ \ \ \Uparrow
\end{aligned}
$$

According to **Observation 2**, we need to move $pat$ down by 4 characters to align the hyphen character:

$$
\begin{aligned}
\textit{pat}:\qquad\qquad &\qquad\qquad\quad\ \ \, \texttt{AT-THAT} \\
\textit{string}:\ \ \ \dots\ &\texttt{WHICH-FINALLY-HALTS.--AT-THAT-POINT} \dots \\
&\qquad\ \ \ \; \qquad\qquad\qquad \Uparrow
\end{aligned}
$$

Now *char*:$\texttt{T}$ matches. Move the pointer on $string$ left one step to continue matching:

$$
\begin{aligned}
\textit{pat}:\qquad\qquad &\qquad\qquad\quad\ \ \, \texttt{AT-THAT} \\
\textit{string}:\ \ \ \dots\ &\texttt{WHICH-FINALLY-HALTS.--AT-THAT-POINT} \dots \\
&\qquad\ \ \ \; \qquad\qquad\quad\ \, \Uparrow
\end{aligned}
$$

According to **Observation 3(a)**, $\texttt{L}$ mismatches because $\texttt{L}$ is not in $pat$. So $pat$ moves down by $k=delta_1-m=7-1=6$ characters, and the pointer on $string$ moves down by $delta_1=7$ characters:

$$
\begin{aligned}
\textit{pat}:\qquad\qquad &\qquad\qquad\qquad\qquad\ \ \,\, \texttt{AT-THAT} \\
\textit{string}:\ \ \ \dots\ &\texttt{WHICH-FINALLY-HALTS.--AT-THAT-POINT} \dots \\
&\qquad\ \ \ \; \qquad\qquad\qquad\qquad\ \ \ \, \, \Uparrow
\end{aligned}
$$

Now $char$ again matches the last character $\texttt{T}$ of $pat$. The pointer on $string$ matches leftward, matches $\texttt{A}$, continues matching leftward, and finds a mismatch at character $\texttt{-}$:

$$
\begin{aligned}
\textit{pat}:\qquad\qquad &\qquad\qquad\qquad\qquad\ \ \,\, \texttt{AT-THAT} \\
\textit{string}:\ \ \ \dots\ &\texttt{WHICH-FINALLY-HALTS.--AT-THAT-POINT} \dots \\
&\qquad\ \ \ \; \qquad\qquad\qquad\quad\ \ \ \,\, \Uparrow
\end{aligned}
$$

Obviously, intuitively at this point, according to **Observation 3(b)**, moving $pat$ down by $k=5$ characters to align the suffix $\texttt{AT}$ gives the maximum slide distance for the $string$ pointer. At this time, $delta_2=k+patlastpos-j=5+6-4=7$, meaning the pointer on $string$ slides down by 7 characters.

And from formal logic, at this time, $delta_1=7-1-2=4,\ delta_2=7, \max(delta_1,delta_2)= 7$,
Thus from formal logic, we support the jump of **Observation 3(b)**:

$$
\begin{aligned}
\textit{pat}:\qquad\qquad &\qquad\qquad\qquad\qquad\qquad\quad \;\, \texttt{AT-THAT} \\
\textit{string}:\ \ \ \dots\ &\texttt{WHICH-FINALLY-HALTS.--AT-THAT-POINT} \dots \\
&\qquad\ \ \ \; \qquad\qquad\qquad\qquad\qquad\quad \ \ \; \Uparrow
\end{aligned}
$$

Now we find that every character on $pat$ equals its corresponding character on $string$. We've found a match of $pat$ in $string$. And it only required 14 references to $string$, where 7 were the comparison count necessary for a successful match ($patlen=7$), and the other 7 allowed us to skip 22 characters.

## Algorithm Design

### The Original Matching Algorithm

#### Explanation

Now let's look at this string matching algorithm using $delta_1$ and $delta_2$:

$$
\begin{array}{ll}
i \gets patlastpos. \\
j \gets patlastpos. \\
\textbf{loop}\\
\qquad \textbf{if}\ j < 0 \\
\qquad \qquad \textbf{return}\ i+1 \\
\\
\qquad \textbf{if}\ string[i]=pat[j] \\
\qquad \qquad j \gets j-1 \\
\qquad \qquad i \gets i-1 \\
\qquad \qquad \textbf{continue} \\
\\
\qquad i \gets i+max(delta_1(string[i]), delta_2(j)) \\
\\
\qquad \textbf{if}\ i > stringlastpos \\
\qquad \qquad \textbf{return}\ false \\
\qquad j \gets patlastpos \\
\end{array}
$$

If the above algorithm $\textbf{return}\ false$, it indicates that $pat$ is not in $string$; if it returns a number, it represents the position where $pat$ first appears from the left in $string$.

Now let's more precisely describe the $rpr(j)$ function used to calculate $delta_2$.

According to the earlier definition, $rpr(j)$ represents the position of the rightmost plausible reoccurrence of the substring $subpat=pat[j+1\dots patlastpos]$ in $pat[j]$ when mismatching at $pat(j)$.

That is, we need to find the best $k$ such that $pat[k\dots k+patlastpos-j-1]=pat[j+1\dots patlastpos]$, and we need to consider two special cases:

1. When $k<0$, it means we prepend a virtual prefix before $pat$, which actually also follows the principle of $delta_2$ jump.
2. When $k>0$, if $pat[k-1]=pat[j]$, then this $pat[k\dots k+patlastpos-j-1]$ cannot be a plausible reoccurrence of $subpat$.
   The reason is that $pat[j]$ itself is the mismatched character, so after sliding $pat$ down by $k$ characters, during the suffix matching process, it will still mismatch at $pat[k-1]$.

There are also two constraints:

1. $k < j$. Because when $k=j$, we have $pat[k]=pat[j]$, and the character that mismatches at $pat[j]$ will also mismatch at $pat[k]$.
2. Considering $delta_2(patlastpos)= 0$, we define $rpr(patlastpos) = patlastpos$.

#### Process

Since understanding $rpr(j)$ is the core of implementing the Boyer-Moore algorithm, we will explain it in detail with the following two examples:

$$
\begin{aligned}
\textit{j}:\qquad\qquad\quad\ \ &\texttt{0 1 2 3 4 5 6 7 8} \\
\textit{pat}:\qquad\qquad\ \  &\texttt{A B C X X X A B C} \\
\textit{rpr(j)}:\qquad\quad\  &\texttt{5 4 3 2 1 0 2 1 8} \\
\textit{sgn}:\qquad\qquad\ \   &\texttt{- - - - - - - - +}
\end{aligned}
$$

For $rpr(0)$, $subpat$ is $\texttt{BCXXXABC}$, and the rightmost plausible reoccurrence before $pat[0]$ can only be $\texttt{[(BCXXX)ABC]XXXABC}$, so the rightmost plausible reoccurrence position is -5, i.e., $rpr(j)=-5$;

For $rpr(1)$, $subpat$ is $\texttt{CXXXABC}$, and the rightmost plausible reoccurrence before $pat[1]$ is $\texttt{[(CXXX)ABC]XXXABC}$, so $rpr(j)=-4$;

For $rpr(2)$, $subpat$ is $\texttt{XXXABC}$, and the rightmost plausible reoccurrence before $pat[2]$ is $\texttt{[(XXX)ABC]XXXABC}$, so $rpr(j)=-3$;

For $rpr(3)$, $subpat$ is $\texttt{XXABC}$, and the rightmost plausible reoccurrence before $pat[3]$ is $\texttt{[(XX)ABC]XXXABC}$, so $rpr(j)=-2$;

For $rpr(4)$, $subpat$ is $\texttt{XABC}$, and the rightmost plausible reoccurrence before $pat[4]$ is $\texttt{[(X)ABC]XXXABC}$, so $rpr(j)=-1$;

For $rpr(5)$, $subpat$ is $\texttt{ABC}$, and the rightmost plausible reoccurrence before $pat[5]$ is $\texttt{[ABC]XXXABC}$, so $rpr(j)=0$;

For $rpr(6)$, $subpat$ is $\texttt{BC}$, and because $string[0]=string[6]$, i.e., $string[0]$ equals the mismatched character $string[6]$, so $string[0\dots 2]$ is not a qualified plausible reoccurrence of $subpat$. Therefore, the rightmost plausible reoccurrence is $\texttt{[(BC)]ABCXXXABC}$, so $rpr(j)=-2$;

For $rpr(7)$, $subpat$ is $\texttt{C}$, similarly because $string[7]=string[1]$, so $string[1\dots 2]$ is not a qualified plausible reoccurrence of $subpat$. The rightmost plausible reoccurrence is $\texttt{[(C)]ABCXXXABC}$, so $rpr(j)=-1$;

For $rpr(8)$, according to the $delta_2$ definition, $rpr(patlastpos)=patlastpos$, so $rpr(8)=8$.

Now let's look at another example:

$$
\begin{aligned}
\textit{j}:\qquad\qquad\quad\ \ &\texttt{0 1 2 3 4 5 6 7 8} \\
\textit{pat}:\qquad\qquad\ \ &\texttt{A B Y X C D E Y X} \\
\textit{rpr(j)}:\qquad\quad\  &\texttt{8 7 6 5 4 3 2 1 8} \\
\textit{sgn}:\qquad\qquad\ \   &\texttt{- - - - - - + - +}
\end{aligned}
$$

For $rpr(0)$, $subpat$ is $\texttt{BYXCDEYX}$, and the rightmost plausible reoccurrence before $pat[0]$ can only be $\texttt{[(BYXCDEYX)]ABYXCDEYX}$, i.e., the rightmost plausible reoccurrence position is -8, i.e., $rpr(j)=-8$;

For $rpr(1)$, $subpat$ is $\texttt{YXCDEYX}$, and the rightmost plausible reoccurrence before $pat[1]$ can only be $\texttt{[(YXCDEYX)]ABYXCDEYX}$, $rpr(j)=-7$;

For $rpr(2)$, $subpat$ is $\texttt{XCDEYX}$, and the rightmost plausible reoccurrence before $pat[2]$ can only be $\texttt{[(XCDEYX)]ABYXCDEYX}$, $rpr(j)=-6$;

For $rpr(3)$, $subpat$ is $\texttt{CDEYX}$, and the rightmost plausible reoccurrence before $pat[3]$ can only be $\texttt{[(CDEYX)]ABYXCDEYX}$, $rpr(j)=-5$;

For $rpr(4)$, $subpat$ is $\texttt{DEYX}$, and the rightmost plausible reoccurrence before $pat[4]$ can only be $\texttt{[(DEYX)]ABYXCDEYX}$, $rpr(j)=-4$;

For $rpr(5)$, $subpat$ is $\texttt{EYX}$, and the rightmost plausible reoccurrence before $pat[5]$ can only be $\texttt{[(EYX)]ABYXCDEYX}$, $rpr(j)=-3$;

For $rpr(6)$, $subpat$ is $\texttt{YX}$, because $string[2\dots 3]=string[7\dots 8]$ and $string[6]\neq string[1]$, so the rightmost plausible reoccurrence before $pat[6]$ is $\texttt{AB[YX]CDEYX}$, $rpr(j)=2$;

For $rpr(7)$, $subpat$ is $\texttt{X}$, although $string[3]=string[8]$ but because $string[2] = string[7]$, the rightmost plausible reoccurrence before $pat[7]$ is $\texttt{[X]ABYXCDEYX}$, $rpr(j)=-1$;

For $rpr(8)$, according to the $delta_2$ definition, $rpr(patlastpos)=patlastpos$, so $rpr(8)=8$.

### An Improvement to the Matching Algorithm

Finally, in practice, considering that about 80% of the search time is spent on the jump of **Observation 1**, that is, the process where $string[i]$ and $pat[patlastpos]$ don't match, and then skipping the entire $patlen$ for the next match.

So we can make a special optimization for this:

We define a $delta0$:

$$
\begin{array}{ll}
\textbf{int}\ delta0(\textbf{char}\ char) \\
\qquad \textbf{if}\ char=pat[patlastpos] \\
\qquad\qquad \textbf{return}\ large\ \ \text{// large is an integer, needs to satisfy large>stringlastpos+patlen} \\
\qquad \textbf{return}\ delta1(char)
\end{array}
$$

Using $delta0$ instead of $delta_1$, we get the improved matching algorithm:

$$
\begin{array}{ll}
i \gets patlastpos \\
\textbf{loop} \\
\qquad\textbf{if} \ i > stringlastpos \\
\qquad\qquad\textbf{return}\ false\\
\\
\qquad\textbf{while}\ i < stringlen \\
\qquad\qquad i \gets i+delta0(string(i)) \ \ \text{// unless string[i] matches the last character of pat, slide at most patlen downward }\\
\qquad\textbf{if}\ i \leqslant\ large \qquad\qquad\qquad\qquad \text{// at this point, no character on string matches the last character of pat}\\
\qquad\qquad\textbf{return}\ false\\
\\
\qquad i \gets i-large \\
\qquad j \gets patlastpos. \\
\qquad\textbf{while}\ j \geqslant\ 0 \ and \  string[i]=pat[j]\\
\qquad \qquad j \gets j-1 \\
\qquad \qquad i \gets i-1 \\
\\
\qquad \textbf{if}\ j < 0 \\
\qquad \qquad \textbf{return}\ i+1 \\
\qquad i \gets i+max(delta_1(string[i]), delta_2(j)) \\
\\
\end{array}
$$

Here $large$ serves multiple purposes: one is to perform fast bad character jumps similar to the Horspool algorithm introduced later, and the other is to assist in detecting whether the string search is complete.

After the improvement, compared to the original algorithm, when doing the **Observation 1** jump, we don't need to do the redundant calculation of $delta_2$ each time, which significantly improves the string search performance under normal character sets.

## Delta2 Construction Details

### Introduction

In the October 1977 issue of *Communications of the ACM*, Boyer and Moore's paper[^bm] only described the static $delta_2$ table.

The discussion of the specific implementation of constructing $delta_2$ appeared in the paper[^kmp] by Knuth, Morris, and Pratt officially publishing the KMP algorithm in the *SIAM Journal on Computing* in June 1977.

### Naive Algorithm

Before introducing Knuth's $delta_2$ construction algorithm, according to the definition, we have a naive algorithm suitable for small-scale problems:

1. For each position `i` in the range `[0, patlen)`, determine the range of its reappearance positions based on the length of `subpat`, which is `[-subpatlen, i]`;
2. Possible reappearance positions are compared character by character from right to left, searching for the rightmost reappearance position of $subpat$ that meets the $delta_2$ requirements;
3. Finally, don't forget to set $delta_2(lastpos)= 0$.

???+ note "Implementation"
    ```Rust
    use std::cmp::PartialEq;
    
    pub fn build_delta_2_table_naive(p: &[impl PartialEq]) -> Vec<usize> {
        let patlen = p.len();
        let lastpos = patlen - 1;
        let mut delta_2 = vec![];
        
        for i in 0..patlen {
            let subpatlen = (lastpos - i) as isize;
            
            if subpatlen == 0 {
                delta_2.push(0);
                break;
            }
            
            for j in (-subpatlen..(i + 1) as isize).rev() {
                // subpat matching
                if (j..j + subpatlen)
                .zip(i + 1..patlen)
                .all(|(rpr_index, subpat_index)| {
                    if rpr_index < 0 {
                        return true;
                    }
                    
                    if p[rpr_index as usize] == p[subpat_index] {
                        return true;
                    }
                    
                    false
                })
                && (j <= 0 || p[(j - 1) as usize] != p[i])
                {
                    delta_2.push((lastpos as isize - j) as usize);
                    break;
                }
            }
        }
        
        delta_2
    }
    ```

Specifically, necessary explanations of Rust language features, not repeated below:

-   `usize` and `isize` are unsigned and signed integers with the same number of bytes as memory pointers; on 32-bit machines they are equivalent to `u32` and `i32`, and on 64-bit machines they are equivalent to `u64` and `i64`.
-   When indexing arrays, vectors, and slices, use `usize` type numbers (because they are used for random access in memory and indices cannot be negative). So if we need to handle negative values, we use `isize`, but when indexing, we need to use `usize`. This is why we see the use of the `as` keyword for explicit conversion between them.
-   `impl PartialEq` is just for generics, and can simultaneously support `Unicode`-encoded `char` and binary `u8`.

Obviously, this brute-force algorithm has a time complexity of $O(n^3)$.

### Efficient Algorithm

Here we introduce an efficient algorithm with time complexity $O(n)$, but requiring additional $O(n)$ space complexity.

Although Knuth proposed this construction method in 1977, his original version of the construction algorithm has a flaw—it actually doesn't produce $delta_2$ that conforms to the definition for some $pat$.

Rytter published an article[^rytter] in 1980 in *SIAM Journal on Computing* proposing a correction. Below is the $delta_2$ construction algorithm:

First, considering the relatively complex definition of $delta_2$, we categorize according to the reappearance position of $subpat$, and handle each category separately—this is the key to efficient implementation.

According to the reappearance position from far to near, i.e., from large to small offset, we divide into the following categories:

1.  The reappearance position of the entire $subpat$ is completely to the left of $pat$, e.g., $\texttt{[(EYX)]ABYXCDEYX}$, at this time $delta_2(j) = patlastpos\times 2 - j$;

2.  Part of the reappearance of $subpat$ is to the left of $pat$, and part is the head of $pat$, e.g., $\texttt{[(XX)ABC]XXXABC}$, at this time $patlastpos < delta_2(j) < patlastpos\times 2 - j$;
    We also include the edge case where $subpat$ is completely in the head of $pat$ here (though according to implementation it can also be included below), e.g., $\texttt{[ABC]XXXABC}$, at this time $patlastpos = delta_2(j)$;

3.  The reappearance of $subpat$ is completely within $pat$, e.g., $\texttt{AB[YX]CDEYX}$, at this time $delta_2(j) < patlastpos$.

Now let's discuss how to efficiently calculate these three cases:

#### Case 1

This is the simplest case; only one traversal is needed, and we can also initialize $delta_2$ in passing.

#### Case 2

We observe when the reappearance of $subpat$ has part to the left of $pat$ and part is the head of $pat$. This should occur when some suffix of $subpat$ equals some prefix of $pat$,

For example:

$$
\begin{aligned}
\textit{j}:\qquad\qquad\quad\ \ &\texttt{0 1 2 3 4 5 6 7 8} \\
\textit{pat}:\qquad\qquad\ \  &\texttt{A B C X X X A B C} \\
\end{aligned}
$$

The reappearance of $delta_2(3)$ is $\texttt{[(XX)ABC]XXXABC}$, and among the suffixes of $subpat$ $\texttt{XXABC}$ and the prefixes of pat, the one that equals is $\texttt{ABC}$.

In fact, the key to calculating the second and third cases both requires the computation and application of the prefix function.

So as long as the value of $j$ makes $subpat$ contain this equal suffix, we can get the reappearance of $subpat$ in case 2. For the example, we only need $j \leqslant 5$,

And when $j = 5$, it is the edge case where $subpat$ is completely in the head of $pat$.

We can calculate $delta_2(j)$ at this time:

Let the length of this pair of equal prefix and suffix be $\textit{prefixlen}$. It can be seen that $subpatlen = patlastpos - j$, so the length of the part to the left of $pat$ is $subpatlen-\textit{prefixlen}$,

And $rpr(j) = -(subpatlen-\textit{prefixlen})$, so we get $delta_2(j) = patlastpos - rpr(j) = patlastpos \times 2 - j - \textit{prefixlen}$.

There may be multiple pairs of equal prefixes and suffixes afterwards, for example:

$$
\begin{aligned}
\textit{j}:\qquad\qquad\quad\ \ &\texttt{0 1 2 3 4 5 6 7 8 9} \\
\textit{pat}:\qquad\qquad\ \  &\texttt{A B A A B A A B A A} \\
\end{aligned}
$$

At $j\leq2$ there is $\texttt{ABAABAA}$, at $2< j \leq5$ there is $\texttt{ABAA}$, at $5<j\leq8$ there is $\texttt{A}$

The flaw in Knuth's algorithm is that it only considers the longest pair, but in fact we need to consider all cases where a suffix of $subpat$ equals a prefix of $pat$. This is equivalent to calculating all cases where a proper suffix of $pat$ equals a proper prefix, and calculating different $delta_2(j)$ for different $j$ intervals in order of descending length.

Using the prefix function and applying the state transition equation in reverse: $j^{(n)} = \pi[j^{(n-1)}-1]$, we can obtain all lengths of equal proper prefixes and proper suffixes of $pat$. Starting from $\pi[patlastpos]$ as the longest pair length, we use reverse state transition to get the next shorter equal proper prefix and suffix length.

This completes the calculation of $delta_2$ for case 2.

#### Case 3

The reappearance of $subpat$ is exactly within $pat$ (not including the head of $pat$), that is, searching for $subpat$ in $pat[0\dots patlastpos-1]$ from right to left.

If we use the BM algorithm to solve this, we get the third case of the recursive implementation of BM, and the ending condition is $patlen \leqslant  2$.

Moreover, according to the definition of $delta_2$, the next character (i.e., the left one) of the found reappearance of $subpat$ cannot be the same as the next character of $subpat$ as a suffix of $pat$.

This gives us a good hint: we can use a process similar to calculating the prefix function to calculate case 3, but it's a reversed prefix function:

-   Two pointers point to the left endpoint of the substring and the "prefix" position of the longest common prefix-suffix of the substring, moving from right to left. When the two characters pointed to are equal, continue moving. This is equivalent to the "prefix" getting larger;
-   When the two characters are not equal, the previously equal part satisfies the requirement of $delta_2$ for reappearance, and we backtrack the pointer pointing to the "prefix" position until new character equality is formed or we go out of bounds.

Like the prefix function, we need an auxiliary array for backtracking. We can use the space of the prefix array generated in case 2.

### Implementation

??? note "Implementation above"
    ```rust
    use std::cmp::PartialEq;
    use std::cmp::min;
    
    pub fn build_delta_2_table_improved_minghu6(p: &[impl PartialEq]) -> Vec<usize> {
        let patlen = p.len();
        let lastpos = patlen - 1;
        let mut delta_2 = Vec::with_capacity(patlen);
        
        // Case 1
        // delta_2[j] = lastpos * 2 - j
        for i in 0..patlen {
            delta_2.push(lastpos * 2 - i);
        }
        
        // Case 2
        // lastpos <= delata2[j] = lastpos * 2 - j
        let pi = compute_pi(p);  // compute prefix function
        let mut i = lastpos;
        let mut last_i = lastpos; // just for initialization
        while pi[i] > 0 {
            let start;
            let end;
            
            if i == lastpos {
                start = 0;
            } else {
                start = patlen - pi[last_i];
            }
            
            end = patlen - pi[i];
            
            for j in start..end {
                delta_2[j] = lastpos * 2 - j - pi[i];
            }
            
            last_i = i;
            i = pi[i] - 1;
        }
        
        // Case 3
        // delata2[j] < lastpos
        let mut j = lastpos;
        let mut t = patlen;
        let mut f = pi;
        loop {
            f[j] = t;
            while t < patlen && p[j] != p[t] {
                // use min function to ensure later possible backtrack doesn't overwrite earlier data
                delta_2[t] = min(delta_2[t], lastpos - 1 - j);
                t = f[t];
            }
            
            t -= 1;
            if j == 0 {
                break;
            }
            j -= 1;
        }
        
        // no actual meaning, just for complete definition
        delta_2[lastpos] = 0;
        
        delta_2
    }
    ```

## Galil Rule's Improvement to Worst-Case Scenario for Multiple Matches

### About the Multiple Match Problem of Suffix Matching Algorithms

The previous search algorithm only involves finding the first $pat$ match in $string$, but there are many different algorithmic approaches for finding all $pat$ matches in $string$. The core concern of this problem is: how to use the information from previously successfully matched characters to reduce the worst-case time complexity to linear.

After a successful match, simply sliding the $string$ pointer backward by $patlen$ distance and restarting suffix matching would lead to $O(mn)$ time complexity in the worst case (by convention, $m$ is $patlen$, $n$ is $stringlen$, same below).

For example, an extreme case: $pat$: $\texttt{AAA}$, $string$: $\texttt{AAAAA}\dots$.

Knuth proposed a method to use a "finite" set of states to record $patlen$-length characters. This algorithm guarantees that each character on $string$ is compared at most once, but the cost is that this "finite" set of states may not be small—for a $pat$ where all characters are different, it needs $\dfrac{1}{2}m^{2}+m$ states.

The simple algorithm without additional preprocessing overhead introduced below is the Galil algorithm[^galil-rule].

### Galil Rule

Assume a $pat$, it is a prefix of a string $UUUU\dots$ formed by repeating a substring $U$ n times. Then we call $U$ a period of $pat$.

For example, $pat: \texttt{ABCABCAB}$ is a prefix of $\texttt{ABC}$ repeated $\texttt{ABCABCABC}$, so the length of $\texttt{ABC}$, which is 3, is the period length of this $pat$, that is, $pat[i] = pat[i+3]$.

$pat$ has at least one period with length equal to itself. We define the shortest period as $k$, $k\leq patlen$.

During the search process, if our $pat$ successfully completes a match, then according to the characteristics of the period, we only need to slide $string$ backward by $k$ characters and compare these $k$ characters to directly determine whether there is another match of $pat$.

To calculate the length of the shortest period, assume we know a pair of equal prefix-suffix of $pat$, with length $\textit{prefixlen}$, then we have $pat[i] = pat[i+(patlen-\textit{prefixlen})]$. Thus we get a period of length $patlen-\textit{prefixlen}$,

When we know the longest equal prefix-suffix of $pat$, we get the shortest period of $pat$.

And the length of the longest equal prefix-suffix, $\pi[patlastpos]$, is already obtained during our calculation of $delta_2$, so we don't need additional preprocessing time and space to improve the worst-case time complexity of the suffix matching algorithm to linear.

??? note "Final implementation of BM search algorithm combined with the above optimization"
    ```rust
    #[cfg(target_pointer_width = "64")]
    const LARGE: usize = 10_000_000_000_000_000_000;
    
    #[cfg(not(target_pointer_width = "64"))]
    const LARGE: usize = 2_000_000_000;
    
    pub struct BMPattern<'a> {
        pat_bytes: &'a [u8],
        delta_1: [usize; 256],
        delta_2: Vec<usize>,
        k: usize  // shortest period length of pat
    }
    
    impl<'a> BMPattern<'a> {
        // ...
        
        pub fn find_all(&self, string: &str) -> Vec<usize> {
            let mut result = vec![];
            let string_bytes = string.as_bytes();
            let stringlen = string_bytes.len();
            let patlen = self.pat_bytes.len();
            let pat_last_pos = patlen - 1;
            let mut string_index = pat_last_pos;
            let mut pat_index;
            let l0 =  patlen - self.k;
            let mut l = 0;
            
            while string_index < stringlen {
                let old_string_index = string_index;
                
                while string_index < stringlen {
                    string_index += self.delta0(string_bytes[string_index]);
                }
                if string_index < LARGE {
                    break;
                }
                
                string_index -= LARGE;
                
                // If string_index has moved, it means there has been at least one failed match since the last successful match.
                // At this time, we need to reset the offset of the second match of Galil rule.
                if old_string_index < string_index {
                    l = 0;
                }
                
                pat_index = pat_last_pos;
                
                while pat_index > l && string_bytes[string_index] == self.pat_bytes[pat_index] {
                    string_index -= 1;
                    pat_index -= 1;
                }
                
                if pat_index == l && string_bytes[string_index] == self.pat_bytes[pat_index] {
                    result.push(string_index - l);
                    
                    string_index += pat_last_pos - l + self.k;
                    l = l0;
                } else {
                    l = 0;
                    string_index += max(
                        self.delta_1[string_bytes[string_index] as usize],
                        self.delta_2[pat_index],
                    );
                }
            }
            
            result
        }
    }
    ```

### Impact of Worst Case on Practical Performance

From a practical perspective, the theoretical worst case doesn't easily affect performance. Even with random text tests of very small alphabets of size 4, the impact of this worst case is too small to observe.

Therefore, if not well designed, using the Galil rule will slightly drag down average performance. But for some extreme special $pat$ and $string$ like in the example: $pat$: $\texttt{AAA}$, $string$: $\texttt{AAAAA}\dots$, the application of the Galil rule does improve performance several times over.

## Improved Algorithms

### Simplified Boyer-Moore Algorithm

The most complex part of the BM algorithm is the construction of the $delta_2$ table (i.e., the good suffix table). In practice, it was found that matching performance on general character sets relies mainly on the $delta_1$ table (i.e., the bad character table). Therefore, a simplified version of the BM algorithm using only the $delta_1$ table appeared, with usually little performance difference from the original.

### Boyer-Moore-Horspool Algorithm

The Horspool algorithm is also based on the bad character rule, applying $delta_1$ to the character aligned with the tail of $pat$. The effect is similar to the improvement to the original matching algorithm, and it usually performs better than the original version.

???+ note "Implementation"
    ```rust
    pub struct HorspoolPattern<'a> {
        pat_bytes: &'a [u8],
        bm_bc: [usize; 256],
    }
    
    impl<'a> HorspoolPattern<'a> {
        // ...
        pub fn find_all(&self, string: &str) -> Vec<usize> {
            let mut result = vec![];
            let string_bytes = string.as_bytes();
            let stringlen = string_bytes.len();
            let pat_last_pos = self.pat_bytes.len() - 1;
            let mut string_index = pat_last_pos;
            
            while string_index < stringlen {
                if &string_bytes[string_index-pat_last_pos..string_index+1] == self.pat_bytes {
                    result.push(string_index-pat_last_pos);
                }
                
                string_index += self.bm_bc[string_bytes[string_index] as usize];
            }
            
            result
        }
    }
    ```

### Boyer-Moore-Sunday Algorithm

The Sunday algorithm also uses the bad character rule, but unlike Horspool, it directly looks at the next character after the character aligned with the tail of $pat$.

Implementing it only requires slightly modifying the $delta_1$ table, equivalent to constructing on $pat$ of length $patlen+1$.

The Sunday algorithm is usually one of the simplest to implement in general cases and has the best average performance. It usually performs slightly better than Horspool and BM.

???+ note "Implementation"
    ```rust
    pub struct SundayPattern<'a> {
        pat_bytes: &'a [u8],
        sunday_bc: [usize; 256],
    }
    
    impl<'a> SundayPattern<'a> {
        // ...
        fn build_sunday_bc(p: &'a [u8]) -> [usize; 256] {
            let mut sunday_bc_table = [p.len() + 1; 256];
            
            for i in 0..p.len() {
                sunday_bc_table[p[i] as usize] = p.len() - i;
            }
            
            sunday_bc_table
        }
        
        pub fn find_all(&self, string: &str) -> Vec<usize> {
            let mut result = vec![];
            let string_bytes = string.as_bytes();
            let pat_last_pos = self.pat_bytes.len() - 1;
            let stringlen = string_bytes.len();
            let mut string_index = pat_last_pos;
            
            while string_index < stringlen {
                if &string_bytes[string_index - pat_last_pos..string_index+1] == self.pat_bytes {
                    result.push(string_index - pat_last_pos);
                }
                
                if string_index + 1 == stringlen {
                    break;
                }
                
                string_index += self.sunday_bc[string_bytes[string_index + 1] as usize];
            }
            
            result
        }
    }
    ```

### BMHBNFS Algorithm

This algorithm combines Horspool and Sunday. It is the algorithm used for `find` in the `stringlib` module when CPython implements it[^b5s], hereinafter referred to as B5S.

The basic idea of B5S is:

1.  Following the suffix matching approach, first compare whether the character at position $patlastpos$ is equal. If equal, compare whether the characters at positions $0\dots patlastpos-1$ are equal. If still equal, we've found a match;

2.  If any stage has a mismatch, enter the jump phase;

3.  In the jump phase, first check whether the next character after position $patlastpos$ is in $pat$. If not, slide directly to the right by $patlen+1$—this is the maximum use of the Sunday algorithm;
    If this character is in $pat$, use $delta_1$ at position $patlastpos$ for Horspool jump.

Depending on whether time saving or space saving is the primary goal, the algorithm has vastly different implementations.

#### Time-Saving Version

???+ note "Implementation"
    ```rust
    pub struct B5STimePattern<'a> {
        pat_bytes: &'a [u8],
        alphabet: [bool;256],
        bm_bc: [usize;256],
        k: usize
    }
    
    impl<'a> B5STimePattern<'a> {
        pub fn new(pat: &'a str) -> Self {
            assert_ne!(pat.len(), 0);
            
            let pat_bytes = pat.as_bytes();
            let (alphabet, bm_bc, k) = B5STimePattern::build(pat_bytes);
            
            B5STimePattern { pat_bytes, alphabet, bm_bc, k }
        }
        
        fn build(p: &'a [u8]) -> ([bool;256], [usize;256], usize)  {
            let mut alphabet = [false;256];
            let mut bm_bc = [p.len(); 256];
            let lastpos = p.len() - 1;
            
            for i in 0..lastpos {
                alphabet[p[i] as usize] = true;
                bm_bc[p[i] as usize] = lastpos - i;
            }
            
            alphabet[p[lastpos] as usize] = true;
            
            (alphabet, bm_bc, compute_k(p))
        }
        
        pub fn find_all(&self, string: &str) -> Vec<usize> {
            let mut result = vec![];
            let string_bytes = string.as_bytes();
            let pat_last_pos = self.pat_bytes.len() - 1;
            let patlen = self.pat_bytes.len();
            let stringlen = string_bytes.len();
            let mut string_index = pat_last_pos;
            let mut offset = pat_last_pos;
            let offset0 = self.k - 1;
            
            while string_index < stringlen {
                if string_bytes[string_index] == self.pat_bytes[pat_last_pos] {
                    if &string_bytes[string_index-offset..string_index] == &self.pat_bytes[pat_last_pos-offset..pat_last_pos] {
                        result.push(string_index-pat_last_pos);
                        
                        offset = offset0;
                        
                        // Galil rule
                        string_index += self.k;
                        continue;
                    }
                }
                
                if string_index + 1 == stringlen {
                    break;
                }
                
                offset = pat_last_pos;
                
                if !self.alphabet[string_bytes[string_index+1] as usize] {
                    string_index += patlen + 1;  // sunday
                } else {
                    string_index += self.bm_bc[string_bytes[string_index] as usize];  // horspool
                }
            }
            
            result
        }
    }
    ```

This version of B5S has very good performance and is usually the fastest among the suffix matching series algorithms introduced here.

#### Space-Saving Version

Also implemented in CPython `stringlib`, using two integers to approximate the role of the alphabet and $delta_1$, greatly saving space:

1.  Replace the alphabet with a simple Bloom filter

    ???+ note "Implementation"
        ```rust
        pub struct BytesBloomFilter {
            mask: u64,
        }
        
        impl BytesBloomFilter {
            pub fn new() -> Self {
                SimpleBloomFilter {
                    mask: 0,
                }
            }
            
            fn insert(&mut self, byte: &u8) {
                (self.mask) |= 1u64 << (byte & 63);
            }
            
            fn contains(&self, char: &u8) -> bool {
                (self.mask & (1u64 << (byte & 63))) != 0
            }
        }
        ```

    The Bloom filter is designed as a `Set` type data structure that sacrifices accuracy (and also running time) to greatly save storage space. Its characteristic is that it will incorrectly judge items not in the set as existing (False Positives, abbreviated as FP), but will not judge items in the set as not existing (False Negatives, abbreviated as FN). Therefore, using it might not get the maximum character jump due to FP, but will not skip characters that should match due to FN.

    Theoretically analyzing, for the above "Bloom filter" implementation, when $pat$ length is 50 bytes, the FP probability is about 0.5, and when $pat$ length is 10 bytes, the FP probability is about 0.15.

    Although this is not a standard Bloom filter, first it actually doesn't use a real hash function—it is actually just a character mapping, mapping bytes 0-255 to the number formed by its first six bits.

    But considering we're doing character search in memory, this simplification is very important. Even using the fastest known non-cryptographic hash algorithm [xxHash](https://cyan4973.github.io/xxHash/), the computation time is still an order of magnitude higher than this.

    Additionally, when $pat$ is below 30 bytes, to achieve the best FP probability, more than one hash function is needed. But this doesn't make much sense because an array with two `u128` numbers can already build a full character set for the alphabet.

2.  Use $delta_1(pat[patlastpos])$ instead of the entire $delta_1$

    Observing $delta_1$, the most common use is when the first character doesn't match in suffix matching—the most common mismatch case. So we let `skip = delta1(pat[patlastpos])`,

    In the first stage of mismatch, slide directly down by `skip` characters; but when the second stage mismatches, due to lacking the entire $delta_1$ information, we can only slide down by one character.

    ???+ note "Implementation"
        ```rust
        pub struct B5SSpacePattern<'a> {
            pat_bytes: &'a [u8],
            alphabet: BytesBloomFilter,
            skip: usize,
        }
        
        impl<'a> B5SSpacePattern<'a> {
            pub fn new(pat: &'a str) -> Self {
                assert_ne!(pat.len(), 0);
                
                let pat_bytes = pat.as_bytes();
                let (alphabet, skip) = B5SSpacePattern::build(pat_bytes);
                
                B5SSpacePattern { pat_bytes, alphabet, skip}
            }
            
            fn build(p: &'a [u8]) -> (BytesBloomFilter, usize)  {
                let mut alphabet = BytesBloomFilter::new();
                let lastpos = p.len() - 1;
                let mut skip = p.len();
                
                for i in 0..p.len()-1 {
                    alphabet.insert(&p[i]);
                    
                    if p[i] == p[lastpos] {
                        skip = lastpos - i;
                    }
                }
                
                alphabet.insert(&p[lastpos]);
                
                (alphabet, skip)
            }
            
            pub fn find_all(&self, string: &'a str) -> Vec<usize> {
                let mut result = vec![];
                let string_bytes = string.as_bytes();
                let pat_last_pos = self.pat_bytes.len() - 1;
                let patlen = self.pat_bytes.len();
                let stringlen = string_bytes.len();
                let mut string_index = pat_last_pos;
                
                while string_index < stringlen {
                    if string_bytes[string_index] == self.pat_bytes[pat_last_pos] {
                        if &string_bytes[string_index-pat_last_pos..string_index] == &self.pat_bytes[..patlen-1] {
                            result.push(string_index-pat_last_pos);
                        }
                        
                        if string_index + 1 == stringlen {
                            break;
                        }
                        
                        if !self.alphabet.contains(&string_bytes[string_index+1]) {
                            string_index += patlen + 1;  // sunday
                        } else {
                            string_index += self.skip;  // horspool
                        }
                    } else {
                        if string_index + 1 == stringlen {
                            break;
                        }
                        
                        if !self.alphabet.contains(&string_bytes[string_index+1]) {
                            string_index += patlen + 1;  // sunday
                        } else {
                            string_index += 1;
                        }
                    }
                
                }
                
                result
            }
        }
        ```

    This version of the algorithm is not as fast as the previous suffix matching algorithms, but the gap is not large. The performance is still better than KMP, thanks to its excellent space complexity with at most two `u64` integers.

## Theoretical Analysis

The following shows the performance of various algorithms under general character sets. The vertical axis is similar to execution cost (cost refers to the cost when failing after matching m characters successfully, skip refers to the probability of sliding k characters when a mismatch occurs). Smaller is better. The horizontal axis is the length of the pattern string pat:

![String search algorithm performance comparison](./images/BM/plot256.svg)

Performance in smaller character sets (DNA {A, C, T, G} base pair sequences):

![String search algorithm performance comparison under small character sets](./images/BM/plot4.svg)

In summary, in larger character sets, such as in everyday search, the Boyer-Moore series algorithms perform excellently, mainly relying on the $delta_1$ table for character jumps;

On the other hand, in smaller character sets, the role of $delta_1$ decreases, while the role of $delta_2$ becomes apparent.

If there is sufficient space available, the full Boyer-Moore algorithm with $O(m)$ space complexity is more general-purpose and has the best overall performance.

## References and Notes

[^bm]: [1977 Boyer-Moore Algorithm Paper](https://dl.acm.org/doi/10.1145/359842.359859)

[^kmp]: [1977 KMP Algorithm Paper](https://epubs.siam.org/doi/abs/10.1137/0206024)

[^rytter]: [1980 Rytter's Correction to Knuth's Paper](https://epubs.siam.org/doi/10.1137/0209037)

[^galil-rule]: [1979 Paper Introducing Galil Algorithm](https://doi.org/10.1145%2F359146.359148)

[^b5s]: [Introduction to B5S Algorithm](http://effbot.org/zone/stringlib.htm#BMHBNFS)