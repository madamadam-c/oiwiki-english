This chapter introduces the idea of offline algorithms, common algorithms, and optimizations.

Offline algorithms are designed under the assumption that **all data is known before solving**. They are suitable for problems with multiple queries. The counterpart is the [online algorithm](https://en.wikipedia.org/wiki/Online_algorithm).

For example, [selection sort](../basic/selection-sort.md) must know the global minimum element of the array before it can run, so it is an offline algorithm. In contrast, [insertion sort](../basic/insertion-sort.md) can dynamically receive data and sort it without requiring all data to be known beforehand, so it is an online algorithm.

For the same problem, offline algorithms are often easier to design than online algorithms. To prevent contestants from using offline algorithms, some problems use a "forced online" setting. Common examples require the answer to the previous query to obtain the parameters of the next query ([interactive problems](../contest/problems.md#交互题) and [communication problems](../contest/problems.md#通信题) also fall into this category).

Common ideas for offline algorithms include solving all queries together (such as [CDQ divide and conquer](./cdq-divide.md)) and deriving the answers to similar queries from one query's answer (such as [parallel binary search](./parallel-binsearch.md) and [Mo's algorithm](./mo-algo-intro.md)).

Because an offline algorithm is an idea rather than a specific algorithm, it is used together with many different data structures and algorithms, and related problem types are more diverse.
