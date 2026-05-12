## Definition

The Palindromic Tree (EERTREE, also known as Palindromic Automaton) is an efficient data structure that can store all palindromic substrings of a string. It was first published by Mikhail Rubinchik and Arseny M. Shur in 2015. Its inspiration comes from string suffix data structures such as suffix trees. Using a palindromic tree, one can solve a series of problems involving palindromic strings simply and efficiently.

## Structure

A palindromic tree looks roughly like this

![](./images/pam1.png)

Similar to other automata, a palindromic tree consists of transition edges and suffix links (fail pointers), and each node can represent a palindromic substring.

Since palindrome lengths can be odd or even, we can, like in manacher, add a character not in the character set (such as '#') as a separator to make all palindrome lengths odd, but this is too cumbersome. Is there a better way?

The answer is yes. The better approach is to build two trees: one tree where nodes correspond to palindromic substrings of odd length, and another where nodes correspond to palindromic substrings of even length.

Like other automata, a node's fail pointer points to the node corresponding to the longest palindromic suffix of the palindrome represented by that node. However, the transition edge does not represent adding a character after the palindrome represented by the original node; instead, it represents adding the same character on both ends of the palindrome (not difficult to understand, since we need to ensure the stored string is a palindrome).

We also need to maintain the length len of the palindromic substring corresponding to each node. This information ensures we can easily construct the palindromic tree.

## Construction

The palindromic tree has two initial states, representing palindromes of length $-1$ and $0$ respectively. We can call them the odd root and even root. They do not represent any actual strings; they only exist as initial states, which is similar to root nodes in other automata.

The fail pointer of the even root points to the odd root, and we don't care about the fail pointer of the odd root because the odd root cannot fail to match (the next state from the odd root has length $1$, i.e., a single character, which is definitely a palindrome).

Similar to suffix automaton, we construct the palindromic tree incrementally.

Consider that after constructing the palindromic tree for the first $p-1$ characters, we add the character at position $p$ in the original string to the automaton.

We start from the node corresponding to the longest palindromic substring ending at this character, and keep following fail pointers until we find a node satisfying $s_{p}=s_{p-len-1}$, i.e., the character before the palindrome substring corresponding to this node is the same as the character to be added.

Here is the figure from the paper

![](./images/pam2.png)

We find the node corresponding to A by jumping fail pointers, then add 'X' on both sides to get the current palindrome (i.e., 'XAX'). Obviously, this node is the tree node corresponding to the longest palindromic substring ending at $p$. (At the same time, at this time the length $-1$ node shows its advantage: if there is no 'X' that can match the condition, it means the same position $s_p=s_p$, and we naturally get the node representing character 'X'.) At this point we need to check: if this node doesn't exist, we need to create it.

Then we also need to find the fail pointer of the newly created node. The specific method is similar to the above process: continuously jump fail pointers from 'A', and we can find the longest palindromic suffix 'XBX' of 'XAX', and set the corresponding node as the target of the fail pointer.

Obviously, this node does not need to be created. The first $len_B$ characters of 'A' and the last $len_B$ characters are both 'B', and the two ends of the first $len_B$ characters correspond to 'X' due to the palindrome relationship, and the later part is determined to be 'X', so this node 'XBX' must already be included.

If fail doesn't match, we connect it to the node of length $0$, which is obviously feasible (since it is the suffix of all nodes).

## Proof of Linear Number of States

### Theorem

For a string $s$, the number of distinct palindromic substrings is at most $|s|$.

### Proof

We use mathematical induction.

-   When $|s| = 1$, $s$ has only one character, and also only one substring, and this substring is a palindrome, so the conclusion holds.

-   When $|s| > 1$, let $t = s \cdot c$, where $t$ is the string formed by adding one character $c$ to the end of $s$. Assume the conclusion holds for $s$. Consider palindromic substrings ending with the last character $c$, and suppose their left endpoints sorted in ascending order are $l_1, l_2, \dots, l_k$. Since $t[l_1..|t|]$ is a palindrome, for all positions $l_1 \le p \le |t|$, we have $t[p..|t|]=t[l_1..l_1+|t|-p]$. Therefore, for $1 < i \le k$, $t[l_i..|t|]$ has already appeared in $t[1..|t|-1]$. Thus, each time we add one character, the number of distinct palindromic substrings increases by at most $1$.

By mathematical induction, the theorem holds.

Therefore, the number of states in the palindromic tree is $O(|s|)$. For each state, it actually represents only one distinct palindromic substring, i.e., the transition to that node is unique, so the total number of transitions is also $O(|s|)$.

## Proof of Correctness

Taking the figure above as an example, when adding the current character 'X', from the proof of linear number of states, we only need to find the longest palindromic suffix containing the last character 'X', which is 'XAX'. Continue to find the longest palindromic suffix of 'XAX', which is 'XBX', and establish the suffix link. The state corresponding to 'XBX' already appears in the palindromic tree. The palindromic suffixes containing the last character are 'XBX' itself and all ancestors of its corresponding state in the fail tree.

For constructing the palindromic tree of $s$, let $n = |s|$. Obviously, all operations except jumping fail pointers are $O(n)$.

When adding a character, on the basis of the previous one, after each jump of fail pointer, the corresponding node's depth in the fail tree decreases by $1$. After connecting fail, it is only depth + 1 (but when fail is $0$, i.e., it only matches at $-1$, the depth is equivalent to $+2$ on the basis of $-1$).

Since we only add $n$ characters, we only add depth $n$ times, and we jump fail pointers at most $2n$ times.

Therefore, the time complexity of constructing the palindromic tree of $s$ is $O(|s|)$.

## Applications

### Number of Distinct Palindromic Substrings

From the proof of linear number of states, it is easy to know that the number of distinct palindromic substrings of a string equals the number of states in the palindromic tree (excluding the odd root and even root).

### Number of Occurrences of Palindromic Substrings

Build the palindromic tree and use a method similar to counting occurrences in suffix automaton.

Since during the construction of the palindromic tree, nodes are inserted in topological order, we only need to enumerate all states in reverse order and add the occurrence count of the current state to the occurrence count of its fail pointer target.

Example problem: [「APIO2014」Palindromes](https://www.luogu.com.cn/problem/P3649)

Define the "existence value" of a substring of $s$ as the number of times this substring appears in $s$ multiplied by its length. For a given string $s$, find the maximum existence value among all palindromic substrings.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/string/code/pam/pam_1.cpp"
    ```

### Minimum Palindromic Partition

> Given a string $s$ ($1\le |s| \le 10^5$), find the minimum $k$ such that there exist $s_1, s_2, \dots, s_k$, satisfying that $s_i$ ($1\le i \le k$) are all palindromic strings, and $s_1, s_2, \dots, s_k$ concatenated in order equals $s$.

Consider dynamic programming. Let $dp[i]$ represent the minimum number of partitions for the prefix of $s$ of length $i$. The transition only needs to enumerate all palindromic strings ending at the $i$-th character:

$$
dp[i]=1+\min_{ s[j+1..i] \text{ is a palindrome} } dp[j]
$$

Since a string can have at most $O(n^2)$ palindromic substrings, the time complexity of the above algorithm is $O(n^2)$, which is unacceptable. To optimize the transition process, we give some lemmas below.

Let the prefix of $s$ with length $i$ be $pre(s,i)$, and the suffix of $s$ with length $i$ be $suf(s,i)$.

Period: If $0 < p \le |s|$, $\forall 1 \le i \le |s|-p, s[i]=s[i+p]$, then $p$ is called a period of $s$.

Border: If $0 \le r < |s|$, $pre(s,r)=suf(s,r)$, then $pre(s,r)$ is called a border of $s$.

Relationship between period and border: $t$ is a border of $s$ if and only if $|s|-|t|$ is a period of $s$.

???+ note "Proof"
    If $t$ is a border of $s$, then $pre(s,|t|)=suf(s,|t|)$. Therefore, $\forall 1\le i \le |t|, s[i]=s[|s|-|t|+i]$, so $|s|-|t|$ is a period of $s$.
    
    If $|s|-|t|$ is a period of $s$, then $\forall 1 \le i \le |s|-(|s|-|t|)=|t|, s[i]=s[|s|-|t|+i]$. Therefore, $pre(s,|t|)=suf(s,|t|)$, so $t$ is a border of $s$.

#### Lemma 1

$t$ is a suffix of the palindromic string $s$, and $t$ is a border of $s$ if and only if $t$ is a palindrome.

???+ note "Proof"
    For $1 \le i \le |t|$, since $s$ and $t$ are palindromes, we have $s[i]=s[|s|-i+1]=s[|s|-|t|+i]$, so $t$ is a border of $s$.
    
    For $1 \le i \le |t|$, since $t$ is a border of $s$, we have $s[i]=s[|s|-|t|+i]$. Since $s$ is a palindrome, we have $s[i]=s[|s|-i+1]$. Therefore, $s[|s|-i+1]=s[|s|-|t|+i]$, so $t$ is a palindrome.

In the figure below, positions with the same color indicate corresponding characters.

![](./images/pam3.png)

#### Lemma 2

$t$ is a border of string $s$ ($|s|\le 2|t|$), $s$ is a palindrome if and only if $t$ is a palindrome.

???+ note "Proof"
    If $s$ is a palindrome, by Lemma 1, $t$ is also a palindrome.
    
    If $t$ is a palindrome, since $t$ is a border of $s$, we have $\forall 1 \le i \le |t|, s[i]=s[|s|-|t|+i]=s[|s|-i+1]$. Since $|s| \le 2|t|$, $s$ is also a palindrome.

#### Lemma 3

$t$ is a border of the palindromic string $s$. Then $|s|-|t|$ is a period of $s$. $|s|-|t|$ is the minimum period of $s$ if and only if $t$ is the longest proper palindromic suffix of $s$.

#### Lemma 4

$x$ is a palindrome, $y$ is the longest proper palindromic suffix of $x$, $z$ is the longest proper palindromic suffix of $y$. Let $u, v$ be strings satisfying $x=uy, y=vz$. Then the following three properties hold:

1.  $|u| \ge |v|$;

2.  If $|u| > |v|$, then $|u| > |z|$;

3.  If $|u| = |v|$, then $u=v$.

![](./images/pam4.png)

???+ note "Proof"
    1.  By the corollary of Lemma 3, $|u|=|x|-|y|$ is the minimum period of $x$, and $|v|=|y|-|z|$ is the minimum period of $y$. Consider proof by contradiction. Assume $|u| < |v|$. Since $y$ is a suffix of $x$, $u$ is both a period of $x$ and a period of $y$, but $|v|$ is the minimum period of $y$, a contradiction. So $|u| \ge |v|$.
    2.  Since $y$ is a border of $x$, $v$ is a prefix of $x$. Let string $w$ satisfy $x=vw$ (as shown in the figure below), where $z$ is a border of $w$. Consider proof by contradiction. Assume $|u| \le |z|$, then $|zu| \le 2|z|$. Therefore, by Lemma 2, $w$ is a palindrome. By Lemma 1, $w$ is a border of $x$. Since $|u| > |v|$, we have $|w| > |y|$, a contradiction. So $|u| > |z|$.
    3.  Both $u$ and $v$ are prefixes of $x$, and $|u|=|v|$, so $u=v$.
    
    ![](./images/pam5.png)

#### Corollary

All palindromic suffixes of $s$, when sorted by length, can be divided into $\log |s|$ arithmetic progressions.

???+ note "Proof"
    Let the lengths of all palindromic suffixes of $s$ sorted in ascending order be $l_1, l_2, \dots, l_k$. For any $2 \le i \le k-1$, if $l_{i}-l_{i-1}=l_{i+1}-l_{i}$, then $l_{i-1}, l_{i}, l_{i+1}$ form an arithmetic progression. Otherwise $l_{i}-l_{i-1}\neq l_{i+1}-l_{i}$. By Lemma 4, we have $l_{i+1}-l_{i}>l_{i}-l_{i-1}$, and $l_{i+1}-l_{i}>l_{i-1}$, $l_{i+1}>2l_{i-1}$. Therefore, if the difference between lengths of adjacent pairs of palindromic suffixes changes, the maximum length must double relative to the minimum length. Obviously, length doubling can occur at most $O(\log |s|)$ times, i.e., the lengths of palindromic suffixes of $s$ can be divided into $\log |s|$ arithmetic progressions.

This corollary can also be proved by using the weak period lemma, classifying all borders of the longest palindromic suffix of $s$ by length $x \in [2^0,2^1),[2^1,2^2),\dots,[2^k,n)$, and considering the longest border in each of these $\log |s|$ groups. For detailed proof, refer to Jin Ce's "Selected Topics in String Algorithms" and Chen Sunli's 2019 IOI National Team Candidate Paper "Related Algorithms for Substring Period Query Problems".

With this conclusion, we can now consider how to optimize the $dp$ transition.

#### Optimization

Each node $u$ in the palindromic tree needs to maintain two additional pieces of information: $diff[u]$ and $slink[u]$. $diff[u]$ represents the length difference between the palindrome string represented by node $u$ and the one represented by $fail[u]$, i.e., $len[u]-len[fail[u]]$. $slink[u]$ represents the first node $v$ we jump to along fail pointers upward such that $diff[v] \neq diff[u]$, i.e., the node with the smallest length in the arithmetic progression that $u$ belongs to.

According to the conclusion proved above, if we use $slink$ pointers to jump upward, each time we add a character, we only need to jump $O(\log |s|)$ times. Therefore, we can consider recording the sum of $dp$ values of all palindromic strings in an arithmetic progression (in the original problem, it means $\min$) on the node corresponding to the longest palindrome in that progression.

Let $g[v]$ represent the sum of $dp$ values of the arithmetic progression that $v$ belongs to, and $v$ is the node with the longest length in this arithmetic progression. Then $g[v]=\sum_{slink[x]=slink[v]} dp[i-len[x]]$, where $i$ is the currently enumerated index.

Next, we consider how to update the $g$ array and $dp$ array. Taking the figure below as an example, suppose we are currently at the $i$-th character, and the corresponding node in the palindromic tree is $x$. $g[x]$ is the sum of the $dp$ values of the three orange positions (the shortest palindrome $slink[x]$ is counted in the next arithmetic progression). The last occurrence position of $fail[x]$ is $i-diff[x]$ (ending at $i-diff[x]$), and $g[fail[x]]$ contains the $dp$ values at the blue positions. Therefore, $g[x]$ actually equals the sum of $g[fail[x]]$ and the $dp$ value at one additional position, which is $i-(len[slink[x]]+diff[x])$. Finally, we use $g[x]$ to update $dp[i]$, and the contribution of this arithmetic progression is calculated. Continuously jumping $slink[x]$ and repeating this process. For specific implementation, refer to the example code.

![](./images/pam6.png)

Finally, the correctness of the above method depends on: if $x$ and $fail[x]$ belong to the same arithmetic progression, then the last occurrence position of $fail[x]$ is $i-diff[x]$.

???+ note "Proof"
    According to Lemma 1, $fail[x]$ is a border of $x$, so it appears at $i-diff[x]$.
    
    Assume $fail[x]$ appears at position $j$ in $(i-diff[x], i)$. Since $x$ and $fail[x]$ belong to the same arithmetic progression, $2|fail[x]| \ge x$. The extra $fail[x]$ and the $fail[x]$ at $i-diff[x]$ have an intersection, denote it as $w$. Let string $u$ satisfy $uw=fail[x]$. Using a method similar to Lemma 1, we can prove that $w$ is a palindrome, and the prefix $s[i-len[x]+1..j]=uwu$ of $x$ is also a palindrome. This contradicts that $fail[x]$ is the longest palindromic prefix (suffix) of $x$.

Example problem: [Codeforces 932G Palindrome Partition](https://codeforces.com/problemset/problem/932/G)

Given a string $s$, we need to partition $s$ into $t_1, t_2, \dots, t_k$, where $k$ is even and $t_i = t_{k-i+1}$. Find the number of such partition schemes.

??? note "Solution"
    Construct string $t = s[0]s[n-1]s[1]s[n-2]s[2]s[n-3] \dots s[n/2-1]s[n/2]$. The problem is equivalent to finding the number of even palindrome partition schemes for $t$. We only need to change the above transition equation to summation form and update the $dp$ array only at even positions. Time complexity $O(n \log n)$, space complexity $O(n)$.

??? note "Reference Code"
    ```cpp
    --8<-- "docs/string/code/pam/pam_2.cpp"
    ```

## Example Problems

-   [Longest Double Palindrome](https://www.luogu.com.cn/problem/P4555)

-   [Cheerleading Rehearsal](https://www.luogu.com.cn/problem/P1659)

-   [「SHOI2011」Double Palindrome](https://www.luogu.com.cn/problem/P4287)

-   [HDU 5421 Victor and String](https://acm.hdu.edu.cn/showproblem.php?pid=5421)

-   [CodeChef Palindromeness](https://www.codechef.com/LTIME23/problems/PALPROB)

## Related Materials

-   [EERTREE: An Efficient Data Structure for Processing Palindromes in Strings](https://arxiv.org/pdf/1506.04862)

-   [Palindromic tree](http://adilet.org/blog/palindromic-tree/)

-   2017 IOI National Team Candidate Papers Collection Palindromic Tree and Its Applications Weng Wentao

-   2019 IOI National Team Candidate Papers Collection Related Algorithms for Substring Period Query Problems Chen Sunli

-   Selected Topics in String Algorithms Jin Ce

-   [A bit more about palindromes](https://codeforces.com/blog/entry/19193)

-   [A Subquadratic Algorithm for Minimum Palindromic Factorization](https://arxiv.org/pdf/1403.2431.pdf)