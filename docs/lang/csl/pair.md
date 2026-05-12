author: sbofgayschool

`std::pair` is a class template defined in the standard library. It is used to associate two variables into a "pair", and the two variables may have different data types.

??? note "Class templates"
    A class template itself is not a class, but a "template" that can produce **different classes** for **different data types**.
    
    When used, the compiler generates the corresponding class according to the provided data types, and then creates the corresponding instance.
    
    Templates are a relatively advanced C++ language feature and almost never appear directly in informatics contests. If you are interested, you can read *C++ Primer* to learn deeper C++ knowledge.

By using `pair` flexibly, you can easily handle scenarios that **require associated data to be stored and processed together**.

??? note "Struct"
    Compared with a custom `struct`, `pair` does not require defining an additional structure or overloading operators, so it is simpler to use.
    
    However, variable names in a custom `struct` are often clearer. `pair` can only access its two stored variables through `first` and `second`. Also, if more than two variables need to be associated, a custom `struct` is more suitable.

## Usage

### Initialization

You can initialize a `pair` directly when defining it.

```cpp
pair<int, double> p0(1, 2.0);
```

You can also define it first and then assign values to initialize the `pair`.

```cpp
pair<int, double> p1;
p1.first = 1;
p1.second = 2.0;
```

You can also use the `std::make_pair` function. This function takes two variables and returns a `pair` made from them.

```cpp
pair<int, double> p2 = make_pair(1, 2.0);
```

A common method is to use the macro definition `#define mp make_pair` to shorten the somewhat verbose `make_pair` to `mp`.

In C++11 and later, `make_pair` can be used with `auto` to avoid explicitly declaring the data types.

```cpp
auto p3 = make_pair(1, 2.0);
```

For the use of `auto` in informatics contests, see the explanation in [Iterators](./iterator.md).

### Access

The two variables stored in a `pair` can be accessed through the members `first` and `second`.

```cpp
int i = p0.first;
double d = p0.second;
```

They can also be modified.

```cpp
p1.first++;
```

### Comparison

`pair` predefines all comparison operators, including `<`, `>`, `<=`, `>=`, `==`, and `!=`. Of course, this requires the data types of the two variables in the `pair` to define the `==` and/or `<` operators.

The four operators `<`, `>`, `<=`, and `>=` first compare the first variables of the two `pair`s, and if they are equal, compare the second variables.

```cpp
if (p2 >= p3) {
  cout << "do something here" << endl;
}
```

Because `pair` defines `<` and `==`, which are commonly used in STL, it works well with other STL functions or data structures. For example, `pair` can be used as the data type of a `priority_queue`.

```cpp
priority_queue<pair<int, double>> q;
```

### Assignment and Swapping

You can assign the value of a `pair` to another `pair` of the same type.

```cpp
p0 = p1;
```

You can also use the `swap` function to exchange the values of two `pair`s.

```cpp
swap(p0, p1);
p2.swap(p3);
```

## Example Applications

### Discretization

`pair` can easily implement discretization.

We can create an array of `pair`s, using the original data value as the first variable of each `pair` and the original position as the second variable. After sorting, assign each original value's rank, that is, its position after sorting, back to its original position.

```cpp
// a is the original data
pair<int, int> a[MAXN];
// ai is the discretized data
int ai[MAXN];
for (int i = 0; i < n; i++) {
  // first is the original value, second is the original position
  scanf("%d", &a[i].first);
  a[i].second = i;
}
// Sort
sort(a, a + n);
for (int i = 0; i < n; i++) {
  // Assign the value's rank to its original position
  ai[a[i].second] = i;
}
```

### Dijkstra

As mentioned above, `pair` can be used as the data type of a `priority_queue`.

Therefore, in the heap optimization of Dijkstra's algorithm, `pair` and `priority_queue` can be used to maintain nodes, with the current distance from the node to the source as the first variable and the node index as the second variable.

```cpp
priority_queue<pair<int, int>, std::vector<pair<int, int>>,
               std::greater<pair<int, int>>>
    q;
... while (!q.empty()) {
  // dis is the distance to the source when pushed; i is the node index
  int dis = q.top().first, i = q.top().second;
  q.pop();
  ...
}
```

### `pair` and `map`

`map` is a C++ data structure for storing key-value pairs. In many cases, the key-value pairs stored in a `map` are exposed externally through `pair`.

```cpp
map<int, double> m;
m.insert(make_pair(1, 2.0));
```

For more about `map`, see the relevant sections in [Associative Containers](./associative-container.md) and [Unordered Associative Containers](./unordered-container.md).
