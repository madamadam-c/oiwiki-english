author: sshwy

A balanced bracket sequence is defined as a string consisting only of $($ and $)$ such that:

-   The empty string $\varepsilon$ is a balanced bracket sequence.
-   If $s$ is a balanced bracket sequence, then $(s)$ is also a balanced bracket sequence.
-   If both $s,t$ are balanced bracket sequences, then $st$ is also a balanced bracket sequence.

For example, $(())()$ is a balanced bracket sequence, while $)()$ is not.

Sometimes there are several different kinds of brackets, such as $[()]\{\}$. Such variants have definitions similar to the plain bracket sequence.

This article introduces classic problems related to bracket sequences.

Note: in English, a left bracket is usually called an opening bracket, while a right bracket is called a closing bracket.

## Checking Validity

The classic way to determine whether $s$ is a balanced bracket sequence is greedy. The same algorithm also works for variant bracket sequences.

Maintain a stack, and consider $i=1,2,\ldots,|s|$ in order:

-   If $s_i$ is a closing bracket, the stack is nonempty, and the top of the stack is the opening bracket corresponding to $s_i$, pop the stack top.
-   Otherwise, push $s_i$ onto the stack.

After traversing all of $s$, if the stack is empty, then $s$ is a balanced bracket sequence; otherwise it is not. The time complexity is $O(n)$.

## Counting Balanced Bracket Sequences

Consider balanced bracket sequences of length $2n$: for such a sequence $s$, let the number of them be $f_n$. Enumerate the position matched with $s_1$; suppose it is $2i+2$. This splits the whole sequence into two shorter balanced bracket sequences. Therefore,

$$
f_n=\sum_{i=0}^{n-1}f_if_{n-i-1}
$$

This is also the recurrence for the Catalan numbers. That is, $f_n=\frac{1}{n+1}\binom{2n}{n}$.

For counting variant balanced bracket sequences, the method is similar. If there are $k$ different types of brackets, then $f'_n=\frac{1}{n+1}\binom{2n}{n}k^n$.

## Lexicographic Successor

Given a balanced bracket sequence $s$, we want to find, among all balanced bracket sequences of length $|s|$ sorted in increasing lexicographic order, the next balanced bracket sequence after $s$. In this problem, we consider opening brackets to be lexicographically smaller than closing brackets, and we do not consider variant bracket sequences.

We need to find the largest $i$ such that $s_i$ is an opening bracket. Then change it into a closing bracket and reconstruct the suffix $s[i+1,|s|]$. In addition, $i$ must satisfy: in $s[1,i-1]$, the number of opening brackets is **greater than** the number of closing brackets.

Suppose that after changing $s_i$ into a closing bracket, the number of opening brackets in $s[1,i]$ exceeds the number of closing brackets by $k$. Then for $s$, make the last $k$ characters closing brackets, and fill $s[i+1,|s|-k]$ in the form $((\dots(())\dots))$, because this gives the lexicographically smallest filling.

The time complexity of this algorithm is $O(n)$.

??? note "Reference Implementation"
    ```cpp
    bool next_balanced_sequence(string& s) {
      int n = s.size();
      int depth = 0;
      for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '(')
          depth--;
        else
          depth++;
    
        if (s[i] == '(' && depth > 0) {
          depth--;
          int open = (n - i - 1 - depth) / 2;
          int close = n - i - 1 - open;
          string next =
              s.substr(0, i) + ')' + string(open, '(') + string(close, ')');
          s.swap(next);
          return true;
        }
      }
      return false;
    }
    ```

## Lexicographic Rank

Given a balanced bracket sequence $s$, we want to find its lexicographic rank.

For $s$, consider computing the number of bracket sequences $p$ that are lexicographically smaller.

Suppose $p_i<s_i$ and $\forall 1\le j<i,p_j=s_i$. Clearly, $p_i$ is an opening bracket and $s_i$ is a closing bracket. Enumerate $i$ (where $s_i$ is a closing bracket). Suppose that in $p[1,i]$, the number of opening brackets exceeds the number of closing brackets by $k$. Then we need to count bracket sequences of length $|s|-i$ with $k$ unmatched closing brackets and no unmatched opening brackets.

Let $f(i,j)$ denote the number of bracket sequences of length $i$ with $j$ unmatched closing brackets and no unmatched opening brackets.

By enumerating the first character of the bracket sequence, we get the transition for $f$: $f(i,j) = f(i-1,j-1)+f(i-1,j+1)$. Initially, $f(0,0)=1$. In fact, $f$ is [OEIS - A053121](http://oeis.org/A053121).

Thus we can compute the lexicographic rank in $O(|s|^2)$.

For variant bracket sequences, the method is similar, except that for each $s_i$ we need to consider all characters smaller than it (in the algorithm above, since no character is smaller than an opening bracket, we only considered positions where $s_i$ is a closing bracket).

In addition, using the $f$ array, we can also construct the balanced bracket sequence with lexicographic rank $k$.

**This page is mainly translated from the blog post <http://e-maxx.ru/algo/bracket_sequences> and its English translation [Balanced bracket sequences](https://cp-algorithms.com/combinatorics/bracket_sequences.html). The Russian version is licensed as Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
