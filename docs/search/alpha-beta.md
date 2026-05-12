This page briefly introduces the Minimax algorithm and Alpha–Beta pruning.

## Minimax Algorithm

The Minimax algorithm, also called the minimax method, is an algorithm that minimizes the potential loss in the worst-case scenario (that is, the maximum loss).

### Process

In a two-player zero-sum game with deterministic positions, adversarial search is often needed. We build a search tree in which every node is a determined state. Odd-numbered layers are our turns, and even-numbered layers are the opponent's turns. Each leaf node in the search tree is assigned an evaluation value; the larger the value, the greater our winning chances. We seek a higher winning chance, while the opponent tries to reduce it. In the search tree, this means that odd-layer nodes (our nodes) always choose the child state with the largest winning chance, while even-layer nodes (opponent nodes) always choose the child state with the smallest winning chance for us.

In the Minimax algorithm, the search tree is traversed from top to bottom, and subtree information is used to update the answer during backtracking. The final value obtained at the root node is the maximum score we can obtain when both sides use optimal strategies.

### Example

Consider a simple example.

Call our side MAX and the opponent MIN, as shown below:

![](images/minimax-1.svg)

For example, in the following position, assume the search proceeds from left to right and the root node value represents our winning chance:

![](images/minimax-2.svg)

We should choose the middle route. If the left route is chosen, the worst winning chance is $3$; if the middle route is chosen, the worst winning chance is $15$; if the right route is chosen, the worst winning chance is $1$. Although the right route may offer a winning chance of $22$, a sufficiently rational opponent will make our winning chance only $1$. After weighing these outcomes, the middle route is clearly better.

![](images/minimax-3.svg)

In fact, when examining the right route, after discovering that the winning chance may be $1$, there is no need to examine the branches with winning chances $12$, $20$, and $22$. Compared with the winning chances of the two routes on the left, it is already certain that the right route is not the best.

The naive Minimax algorithm often needs to build a huge search tree, making both time and space complexity unacceptable. Alpha–Beta pruning is a method that uses upper and lower bounds on the players' scores at each node in the search tree to prune and optimize Minimax.

Note that for different problems, the value at each node of the search tree may have different meanings. It can be an evaluation value, a score, a winning probability, and so on. For convenience, the following text uniformly calls it a score.

## Alpha–Beta Pruning

Alpha–Beta pruning is search pruning for the Minimax algorithm.

### Process

In the Minimax algorithm, if the scores of all child nodes of a node are known, the score of that node can be computed: for a MAX node, take the maximum score; for a MIN node, take the minimum score.

When the search reaches a node but has not yet finished processing it, the score of that node cannot be computed, but the possible range of the players' scores **among the nodes searched so far** can be computed. During the search, maintain two variables $\alpha$ and $\beta$, which respectively represent, when the game reaches this node and **considering all nodes searched so far**, the lower and upper bounds on the scores that the Alpha player (the side seeking the maximum score) and the Beta player (the side seeking the minimum score) can guarantee.

The pruning strategy of Alpha–Beta pruning depends on the values of $\alpha$ and $\beta$ when searching the current node. If the current node is a MAX node, Alpha can continue searching its child nodes to raise the lower score bound $\alpha$. However, if after some search we already have $\alpha\ge\beta$, then this node cannot appear in an actual game: once this node is reached, the Alpha player can guarantee a score of at least $\alpha$; but the Beta player already knows that there exists a strategy (deviating from the current path) that can guarantee a score no greater than $\beta\le\alpha$, so the Beta player naturally will not allow the game to develop to the **current node**. Similarly, if the current node is a MIN node, and after searching one of its child nodes it is found that $\beta\le\alpha$ holds at this node, then there is likewise no need to continue searching other child nodes, because the Alpha player will not allow the game to enter the **current node**. Combining the two cases, when $\alpha \geq \beta$, the remaining branches of this node do not need to be searched further (that is, pruning can be performed). Note that pruning is also needed when $\alpha = \beta$, because there will be no better result, though there may be worse results.

During the search, there is no need to maintain node scores; maintaining only $\alpha$ and $\beta$ is enough. Initially, set $\alpha=-\infty,~\beta=+\infty$. When searching downward, pass the information of $\alpha$ and $\beta$ along with the recursion to record the two players' candidate strategies.

After a child node has been searched, the information at the current node must be updated. Suppose the current node $X$ is a MAX node, and its child node $Y$ has just been searched. Then the $\beta$ value at node $X$ does not change; only the $\alpha$ value needs to take the maximum with the score of child node $Y$. If child node $Y$ is a leaf node, directly use the score of child node $Y$ to update the $\alpha$ value at current node $X$; otherwise, it is enough to use the $\beta$ value of child node $Y$ to update the $\alpha$ value of current node $X$. At this point, there are three possibilities:

1.  The $\beta$ value of child node $Y$ lies strictly between the $\alpha$ and $\beta$ values of node $X$. Because child node $Y$ inherits the $\alpha$ value of node $X$ and does not update it, still having $\beta > \alpha$ after searching child node $Y$ means that no pruning occurred while searching child node $Y$. The final $\beta$ value of child node $Y$ is the minimum of the $\beta$ value it inherited from node $X$ and the scores of all its (child node $Y$'s) child nodes. Since this minimum is strictly less than the $\beta$ value of node $X$, it must be the minimum score among all child nodes of child node $Y$. Therefore, as a MIN node, the score of child node $Y$ is exactly this $\beta$ value. It is reasonable to use it to update the $\alpha$ value of node $X$.
2.  The $\beta$ value of child node $Y$ is exactly equal to the $\beta$ value of node $X$. As described above, this means that the scores of all child nodes of child node $Y$ are not less than the $\beta$ value of node $X$. This further indicates that the Beta player will not allow the game to enter node $X$: as long as the Alpha player chooses child node $Y$, the Beta player cannot obtain a score lower than $\beta$. Therefore, using the $\beta$ value of child node $Y$ to update the $\alpha$ value of node $X$ at this point is intended to make $\alpha=\beta$ at node $X$, triggering the pruning condition. Its effect is the same as updating the $\alpha$ value of node $X$ with the actual score at $Y$, which is a number greater than or equal to the $\beta$ value at node $X$.
3.  The $\beta$ value of child node $Y$ is less than or equal to the $\alpha$ value of node $X$. At this point, child node $Y$ has triggered the pruning condition. Its actual score will not exceed the $\beta$ value of child node $Y$, and certainly will not exceed the $\alpha$ value of node $X$. Updating the $\alpha$ value of node $X$ with the actual score of child node $Y$ will not change the $\alpha$ value. This has the same effect as updating the $\alpha$ value of node $X$ with the $\beta$ value of child node $Y$.

This analysis shows that after a child node has been searched, only in the first case does $\alpha$ (or $\beta$) accurately record the actual score of this child node as a MAX node (or MIN node). In the other cases, although it may not be an accurate score, the information it provides is sufficient to ensure correct pruning and therefore does not affect the score recorded at the root node.

### Example

This section analyzes an example to show how to update the $\alpha$ and $\beta$ values at each node during the search. During the process, the scores at the involved nodes are also computed, allowing us to observe the relationship between each node's actual score and the recorded $\alpha$ and $\beta$ values. However, note that when implementing this algorithm, the actual scores of these nodes are not computed.

For the following position, assume the search proceeds from left to right:

![](images/alpha-beta-1.svg)

Initially, set $\alpha = -\infty,~\beta = +\infty$, and pass this information down along the search path.

![](images/alpha-beta-2.svg)

When the search reaches node A, its left child has score $3$, and node A is a MIN node trying to find a move with a smaller score, so the $\beta$ value is changed to $3$, because $3$ is less than the current $\beta$ value ($\beta = +\infty$). Then the right child of node A has score $17$, so the $\beta$ value of node A is not changed, because $17$ is greater than the current $\beta$ value ($\beta = 3$). At this point, all child nodes of node A have been searched, so the score of node A can be computed as $3$, which is consistent with the $\beta$ value recorded at this node (case 1 above).

![](images/alpha-beta-3.svg)

Node A is a child of node B. After computing the score of node A, the $\alpha$ and $\beta$ values of node B can be updated. Since node B is a MAX node and tries to find a move with a larger score, the $\alpha$ value is changed to $3$, because the $\beta$ value at child node A ($\beta=3$) is greater than the current $\alpha$ value ($\alpha = -\infty$). Then search the right child C of node B, passing the $\alpha$ and $\beta$ values of node B to node C.

![](images/alpha-beta-4.svg)

For node C, its left child has score $2$, and node C is a MIN node, so the $\beta$ value is changed to $2$. Now $\alpha \geq \beta$, so the remaining child nodes of node C do not need to be searched, because it is certain that the Alpha player will not allow the game to develop to node C. At this point, node C is a MIN node, and its score is $2$, not exceeding the recorded $\beta$ value (case 3 above). Since all child nodes of node B have been searched, the score of node B can be computed as $3$, the same as the recorded $\alpha$ value (case 1 above).

![](images/alpha-beta-5.svg)

After computing the score of node B, node B is a child of node D, so the $\alpha$ and $\beta$ values of node D can be updated. Since node D is a MIN node, its $\beta$ value is changed to $3$. Then node D passes the $\alpha$ and $\beta$ values to node E, and node E passes them to node F. For node F, it has only one child with score $15$. Since $15$ is greater than the current $\beta$ value and node F is a MIN node, its $\beta$ value is not updated. Then the score of node F can be computed as $15$, which is greater than the recorded $\beta$ value (case 2 above).

![](images/alpha-beta-6.svg)

After computing the score of node F, node F is a child of node E, so the $\alpha$ and $\beta$ values of node E can be updated. Node E is a MAX node, so update the $\alpha$ value. At this point $\alpha \geq \beta$, so the remaining branch of node E (node G) can be pruned. Then, since node E is a MAX node, set the score of node E to $15$, which is strictly greater than the recorded $\alpha$ value (case 3 above). Using node E's $\alpha$ value to update node D's $\beta$ value still gives $3$. At this point, all child nodes of node D have been searched, so the score of node D can be computed as $3$, equal to the recorded $\beta$ value (case 1 above).

![](images/alpha-beta-7.svg)

After computing the score of node D, node D is a child of node H, so the $\alpha$ and $\beta$ values of node H can be updated. Node H is a MAX node, so update $\alpha$. Then, in search order, pass the $\alpha$ and $\beta$ values of node H to nodes I, J, and K in sequence. For node K, its left child has score $2$, and node K is a MIN node, so update $\beta$. At this point $\alpha \geq \beta$, so the remaining branches of node K can be pruned. Then set the score of node K to $2$, which is less than or equal to the recorded $\beta$ value (case 3 above).

![](images/alpha-beta-8.svg)

After computing the score of node K, node K is a child of node J, so the $\alpha$ and $\beta$ values of node J can be updated. Node J is a MAX node, so update $\alpha$; however, because the score of node K is less than $\alpha$, the $\alpha$ value of node J remains $3$. Then pass the $\alpha$ and $\beta$ values of node J to node L. Since node L is a MIN node, update $\beta = 3$. At this point $\alpha \geq \beta$, so the remaining branches of node L can be pruned. Since node L has no remaining branches, no actual pruning occurs here. Then set the score of node L to $3$, which is less than or equal to the recorded $\beta$ value (case 3 above).

![](images/alpha-beta-9.svg)

After computing the score of node L, node L is a child of node J, so the $\alpha$ and $\beta$ values of node J can be updated. Node J is a MAX node, so update $\alpha$; however, because the score of node L is less than or equal to $\alpha$, the $\alpha$ value of node J remains $3$. At this point, all child nodes of node J have been searched, so the score of node J can be computed as $3$, which is equal to the recorded $\alpha$ value (case 2 above).

After computing the score of node J, node J is a child of node I, so the $\alpha$ and $\beta$ values of node I can be updated. Node I is a MIN node, so update $\beta$. At this point $\alpha \geq \beta$, so the remaining branches of node I can be pruned. It is worth noting that because the right child exists, the actual score of node I is $2$, which is less than the recorded $\beta$ value (case 3 above).

After computing the score of node I, node I is a child of node H, so the $\alpha$ and $\beta$ values of node H can be updated. Node H is a MAX node, so update $\alpha$; however, because the score of node I is less than or equal to $\alpha$, the $\alpha$ value of node H remains $3$. At this point, all child nodes of node H have been searched, so the score of node H can be computed as $3$, which is equal to the recorded $\alpha$ value (case 1 above).

![](images/alpha-beta-10.svg)

This is the final result.

### Implementation

???+ example "Reference code"
    ```cpp
    int alpha_beta(int u, int alph, int beta, bool is_max) {
      if (!son_num[u]) return val[u];
      if (is_max) {
        for (int i = 0; i < son_num[u]; ++i) {
          int d = son[u][i];
          alph = max(alph, alpha_beta(d, alph, beta, !is_max));
          if (alph >= beta) break;
        }
        return alph;
      } else {
        for (int i = 0; i < son_num[u]; ++i) {
          int d = son[u][i];
          beta = min(beta, alpha_beta(d, alph, beta, !is_max));
          if (alph >= beta) break;
        }
        return beta;
      }
    }
    ```

## References and Notes

-   [Minimax Algorithm - Wikipedia](https://en.wikipedia.org/wiki/Minimax#Minimax_algorithm_with_alternate_moves)
-   [Alpha–beta pruning - Wikipedia](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning)

**This article partially quotes the blog post [Detailed explanation of the Minimax algorithm and alpha-beta pruning by wenjianmuran](https://blog.csdn.net/wenjianmuran/article/details/90633418), under the CC 4.0 BY-SA license. The content has been modified.**
