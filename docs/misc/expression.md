author: Ir1d, Anguei, hsfzLZH1, siger-young, HeRaNO, c8ef

Expression evaluation generally solves the problem of inputting an expression represented as a string and outputting its value. Of course, there are also variants, such as whether the expression contains parentheses, exponentiation, how many variables it contains, determining whether multiple expressions are equivalent, and so on.

Expressions usually need to be parsed (grammar parsing) before evaluation, though they can also be parsed and evaluated at the same time. The role of parsing is to check whether the input string is a valid expression, and this is usually handled by a parser.

An expression contains two types of characters: operands and operators. For an expression of length $n$, with a suitable parsing method, parsing and evaluation can be completed in $O(n)$ time complexity.

## Expression Trees and Reverse Polish Notation

One recursive way to parse an expression is to analyze it as ordinary grammar rules, split it into an expression tree as shown in the figure, and then compute on the tree structure from bottom to top. ![](./images/bet.png)

Performing [tree traversal](../graph/tree-basic.md#树的遍历) on an expression tree can produce different types of expressions. Arithmetic expressions are divided into three types: prefix expressions, infix expressions, and postfix expressions. Infix expressions are the most commonly used expressions in daily life; postfix expressions are easier for computers to understand.

-   Preorder traversal corresponds to prefix notation (Polish notation)
-   Inorder traversal corresponds to infix notation
-   Postorder traversal corresponds to postfix notation (Reverse Polish notation)

Reverse Polish notation (postfix notation) is a form of writing mathematical expressions in which an operator is placed after its operands. For example, the following expression:

$$
a+b*c*d+(e-f)*(g*h+i)
$$

can be written in Reverse Polish notation as:

$$
abc*d*+ef-gh*i+*+
$$

Therefore, Reverse Polish notation corresponds one-to-one with expression trees. Reverse Polish notation does not need parentheses, and its order of operations is uniquely determined.

The convenience of Reverse Polish notation is that it is easy to evaluate in linear time. For example, in the Reverse Polish expression $3~2~*~1~-$, first compute $3 \times 2 = 6$ (using the last operator, that is, the top operator on the stack), then compute $6 - 1 = 5$. We can see that for a Reverse Polish expression, we only need to **maintain a stack of numbers; whenever an operator is encountered, take the top two stack elements, compute the result, and push the result back onto the stack**. Finally, the only element in the stack is the value of the Reverse Polish expression. This algorithm has $O(n)$ time complexity.

Whether recursive parsing of an expression succeeds depends on whether the grammar rules are reasonably designed, that is, whether they can successfully produce the specified expression tree. For example:

$$
a+b*c
$$

Depending on the different precedence of addition and multiplication, this infix expression may be transformed into two different expression trees. It can be seen that the design of grammar rules depends heavily on operator precedence. Designing corresponding recursive grammar rules with the help of operator precedence is in fact not easy.

The method introduced below treats each operator together with its precedence as a whole, and uses a non-recursive approach to parse and evaluate expressions directly according to operator precedence.

## Parenthesized Expressions with Only Left-Associative Binary Operators

Consider a simplified problem. Suppose all operators are binary: every operator has two arguments. Also suppose all operators are left-associative: if operators have equal precedence, they are evaluated from left to right. Parentheses are allowed.

To evaluate this type of infix expression, we can convert it to a postfix expression and then evaluate it. Define two [stacks](../ds/stack.md) to store operators and operands respectively. Whenever a number is encountered, put it directly onto the operand stack. Each operator block corresponds to a pair of parentheses, and the operator stack is monotonic only inside an operator block. Whenever an operator is encountered, look at the elements in the topmost operator block of the operator stack. Within the operator block, pop operators appropriately in descending order of precedence, and compute the value of the corresponding subexpression while popping.

In the following, "output" means outputting to the postfix expression: either put the number onto the operand stack, or pop an operator and two operands, compute the result, and push it back onto the operand stack. Scan the infix expression from left to right:

1.  If a number is encountered, output it directly.
2.  If a left parenthesis is encountered, put it onto the operator stack.
3.  If a right parenthesis is encountered, keep outputting the top stack element until a left parenthesis is encountered, then pop the left parenthesis. In other words, execute all operators inside the pair of parentheses.
4.  If another operator is encountered, keep outputting all operators whose precedence is greater than or equal to that of the current operator. Finally, push the new operator onto the operator stack.
5.  After the whole string has been processed, some operators may still remain in the stack, so output the remaining symbols in the stack in order. The expression conversion is then complete.

The following is an implementation of this method for the four operators $+$, $-$, $*$, and $/$:

??? note "Sample code"
    ```cpp
    
    bool delim(char c) { return c == ' '; }
    
    bool is_op(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }
    
    int priority(char op) {
      if (op == '+' || op == '-') return 1;
      if (op == '*' || op == '/') return 2;
      return -1;
    }
    
    void process_op(stack<int>& st, char op) {  // Can also be used to evaluate postfix expressions
      int r = st.top();                         // Take the top stack element; note the order
      st.pop();
      int l = st.top();
      st.pop();
      switch (op) {
        case '+':
          st.push(l + r);
          break;
        case '-':
          st.push(l - r);
          break;
        case '*':
          st.push(l * r);
          break;
        case '/':
          st.push(l / r);
          break;
      }
    }
    
    int evaluate(string& s) {  // Can also be adapted to convert infix expressions to postfix expressions
      stack<int> st;
      stack<char> op;
      for (int i = 0; i < (int)s.size(); i++) {
        if (delim(s[i])) continue;
    
        if (s[i] == '(') {
          op.push('(');  // 2. If a left parenthesis is encountered, put it onto the operator stack
        } else if (s[i] == ')') {  // 3. If a right parenthesis is encountered, execute all operators inside the pair
          while (op.top() != '(') {
            process_op(st, op.top());
            op.pop();  // Keep outputting the top stack element until a left parenthesis is encountered
          }
          op.pop();                // Pop the left parenthesis
        } else if (is_op(s[i])) {  // 4. If another operator is encountered
          char cur_op = s[i];
          while (!op.empty() && priority(op.top()) >= priority(cur_op)) {
            process_op(st, op.top());
            op.pop();  // Keep outputting all operators whose precedence is at least that of the current operator
          }
          op.push(cur_op);  // Push the new operator onto the operator stack
        } else {            // 1. If a number is encountered, output it directly
          int number = 0;
          while (i < (int)s.size() && isalnum(s[i]))
            number = number * 10 + s[i++] - '0';
          --i;
          st.push(number);
        }
      }
    
      while (!op.empty()) {
        process_op(st, op.top());
        op.pop();
      }
      return st.top();
    }
    
    ```

The time complexity of this algorithm, which implicitly uses Reverse Polish notation to compute the expression value, is $O(n)$. With slight modifications to the above implementation, the Reverse Polish expression can also be obtained explicitly.

### Unary Operators and Right-Associative Operators

Now suppose the expression also contains unary operators, that is, operators with only one argument. Unary plus and unary minus are common examples of unary operators.

One difference in this case is that we need to determine whether the current operator is unary or binary.

Notice that before a unary operator there is usually another operator or an opening parenthesis, unless the unary operator is at the very beginning of the expression. Before a binary operator, there is always an operand or a closing parenthesis. Therefore, we can mark whether the next operator may be unary.

In addition, unary and binary operators need to be executed differently, and unary operators should have higher precedence than all binary operators. Note that some unary operators, such as unary plus and unary minus, are actually right-associative.

Right-associativity means that whenever precedence is equal, operators must be evaluated from right to left.

As mentioned above, unary operators are usually right-associative. Another example of a right-associative operator is exponentiation. For $a \wedge b \wedge c$, it is usually regarded as $a^{b^c}$ rather than $(a^b)^c$.

To handle this type of operator correctly, the corresponding change is to postpone popping the operator when precedence is equal.

The code that needs to be changed is as follows. Replace:

```cpp

while (!op.empty() && priority(op.top()) >= priority(cur_op)) 
```

with

```cpp

while (!op.empty() &&
       ((left_assoc(cur_op) && priority(op.top()) >= priority(cur_op)) ||
        (!left_assoc(cur_op) && priority(op.top()) > priority(cur_op))))

```

where left\_assoc is a function that determines whether an operator is left-associative.

Here is an implementation for the binary operators $+$, $-$, $*$, and $/$, and the unary operators $+$ and $-$:

??? note "Sample code"
    ```cpp
    
    bool delim(char c) { return c == ' '; }
    
    bool is_op(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }
    
    bool is_unary(char c) { return c == '+' || c == '-'; }
    
    int priority(char op) {
      if (op < 0)  // unary operator
        return 3;
      if (op == '+' || op == '-') return 1;
      if (op == '*' || op == '/') return 2;
      return -1;
    }
    
    void process_op(stack<int>& st, char op) {
      if (op < 0) {
        int l = st.top();
        st.pop();
        switch (-op) {
          case '+':
            st.push(l);
            break;
          case '-':
            st.push(-l);
            break;
        }
      } else {  // Take the top stack element; note the order
        int r = st.top();
        st.pop();
        int l = st.top();
        st.pop();
        switch (op) {
          case '+':
            st.push(l + r);
            break;
          case '-':
            st.push(l - r);
            break;
          case '*':
            st.push(l * r);
            break;
          case '/':
            st.push(l / r);
            break;
        }
      }
    }
    
    int evaluate(string& s) {
      stack<int> st;
      stack<char> op;
      bool may_be_unary = true;
      for (int i = 0; i < (int)s.size(); i++) {
        if (delim(s[i])) continue;
    
        if (s[i] == '(') {
          op.push('(');  // 2. If a left parenthesis is encountered, put it onto the operator stack
          may_be_unary = true;
        } else if (s[i] == ')') {  // 3. If a right parenthesis is encountered, execute all operators inside the pair
          while (op.top() != '(') {
            process_op(st, op.top());
            op.pop();  // Keep outputting the top stack element until a left parenthesis is encountered
          }
          op.pop();  // Pop the left parenthesis
          may_be_unary = false;
        } else if (is_op(s[i])) {  // 4. If another operator is encountered
          char cur_op = s[i];
          if (may_be_unary && is_unary(cur_op)) cur_op = -cur_op;
          while (!op.empty() &&
                 ((cur_op >= 0 && priority(op.top()) >= priority(cur_op)) ||
                  (cur_op < 0 && priority(op.top()) > priority(cur_op)))) {
            process_op(st, op.top());
            op.pop();  // Keep outputting all operators whose precedence is at least that of the current operator
          }
          op.push(cur_op);  // Push the new operator onto the operator stack
          may_be_unary = true;
        } else {  // 1. If a number is encountered, output it directly
          int number = 0;
          while (i < (int)s.size() && isalnum(s[i]))
            number = number * 10 + s[i++] - '0';
          --i;
          st.push(number);
          may_be_unary = false;
        }
      }
    
      while (!op.empty()) {
        process_op(st, op.top());
        op.pop();
      }
      return st.top();
    }
    
    ```

## References

**This page is mainly translated from the blog post [Разбор выражений. Обратная польская нотация](https://e-maxx.ru/algo/expressions_parsing) and its English translation [Expression parsing](https://cp-algorithms.com/string/expression_parsing.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**

## Further reading

1.  [Operator-precedence\_parser](https://en.wikipedia.org/wiki/Operator-precedence_parser)
2.  [Shunting yard algorithm](https://en.wikipedia.org/wiki/Shunting_yard_algorithm)

## Practice

1.  [NOIP2013 Junior Expression Evaluation](https://www.luogu.com.cn/problem/P1981)
2.  [Postfix Expression](https://www.luogu.com.cn/problem/P1449)
3.  [Transform the Expression](https://www.spoj.com/problems/ONP/)
