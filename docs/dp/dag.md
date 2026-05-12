## Definition

DAG stands for [directed acyclic graph](../graph/dag.md). Many binary relations in practical problems can be modeled with DAGs, transforming those problems into longest- or shortest-path problems on a DAG.

## Explanation

Use the following problem as an example to analyze the DAG modeling process.

???+ note "Example Problem [UVa 437 The Tower of Babylon](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=378)"
    There are $n$ types of blocks ($n\leqslant 30$), and the three side lengths of each block are known. There are infinitely many blocks of each type. Choose some cuboids and stack them into a column as high as possible. Each block may choose any one of its sides as its height. For every block, both dimensions of its base must be strictly smaller than the corresponding base dimensions of the block below it. Find the maximum tower height.

## Process

### Building the DAG

Because both base dimensions of a block must be strictly smaller than those of the block below it, this relation can naturally be used as the basis for graph construction, and the problem becomes a longest-path problem.

That is, if block $j$ can be placed on block $i$, then there is an edge $(i,j)$, and the edge weight is the chosen height of block $j$.

Another issue is that each block has three possible choices for height. What is a suitable graph construction?

We can split each block into three stacking orientations: decompose one block into three blocks, each choosing a different side as its height.

The initial starting point is the ground. The ground has an infinitely large base, so it can reach any block. Of course, we do not need to explicitly write infinity in the program.

Suppose there are two blocks with side lengths $31, 41, 59$ and $33, 83, 27$. The whole DAG should look like the following figure.

![](./images/dag-babylon.png)

The blue solid boxes in the figure represent the group of blocks obtained by decomposing one original block. The base side lengths are written with $\{\}$ because once the height has been chosen, the base side lengths are unordered.

The yellow dashed boxes mark repeated computation, which can be avoided with [memoized search](./memo.md).

### Transition

The problem asks for the maximum tower height, which has been transformed into a longest-path problem. The starting point, as noted above, is the ground. What about the ending point? It is naturally determined: a block on top of which no other block can be stacked.

Now consider the transition equation.

Let $d(i,r)$ denote the maximum height when block $i$ is at the bottom and uses its $r$-th stacking orientation. Then the transition equation is:

$$
d(i, r) = \max\left\{d(j, r') + h\right\}
$$

Here, $j$ ranges over all blocks that can be placed on block $i$ when $i$ uses orientation $r$, $r'$ is the corresponding orientation of $j$, and $h$ is the height of block $i$ under orientation $r$.

??? note "Implementation"
    ```cpp
    --8<-- "docs/dp/code/dag/dag_1.cpp"
    ```
