author: Ir1d, cjsoft, Lans1ot

A **struct** can be regarded as a collection of elements called members.

It can also be regarded as a custom data type.

???+ note "Note"
    The `struct` described on this page is different from `struct` in C. In C++, `struct` is extended into a class specifier similar to [`class`](./class.md).

## Defining a Struct

```cpp
struct Object {
  int weight;
  int value;
} e[array_length];

const Object a;
Object b, B[array_length], tmp;
Object *c;
```

The example above defines a struct named `Object` with two members, `value` and `weight`, both of type `int`.

After `}`, it defines a constant `a`, variables `b` and `tmp`, an array `B`, and a pointer `c`, all with data type `Object`. For any existing type, you can use this method to define constants, variables, pointers, arrays, and so on.

*About pointers: you do not have to master them immediately.*

### Defining Pointers

If you are defining a pointer to a built-in type, define it the same way as usual.

If you are defining a pointer to a struct, use `StructName*` in the definition.

```cpp
struct Edge {
  /*
  ...
  */
  Edge* nxt;
};
```

The example above is only illustrative; do not worry about its practical meaning.

## Accessing/Modifying Members

You can access members with `variable_name.member_name`. For example, `cout << var.v` outputs the `v` member of `var`.

You can also access members with `pointer_name->member_name` or `(*pointer_name).member_name`. For example, `(*ptr).v = tmp` or `ptr->v = tmp` assigns `tmp` to the member `v` of the struct pointed to by the struct pointer `ptr`.

## Why Use Structs?

First, many roads lead to Rome: you can achieve the same effect without structs. However, structs can explicitly bind members (usually variables in algorithm competitions) together. For example, the `Object` struct in this page puts `value` and `weight` together; its practical meaning is to represent the weight and value of an item. One benefit is that it constrains how members are used.  
Imagine using two arrays, `value[]` and `Value[]`, without a struct. It is easy to mix them up. Using a struct can reduce the chance of using the wrong variable.

Also, different structs (struct types, such as `Object`) or different struct variables (instances of a struct, such as the array `e` above) can have members with the same name (such as `tmp.value` and `b.value`). Members with the same name are independent and have their own memory; for example, modifying `tmp.value` does not affect the value of `b.value`.  
This makes it possible to use identical or similar variable names to describe an object. For example, `Object` has a member variable `value`; we can also define a `Car` struct that also has a `value` member. Without structs, we might need arrays with different names such as `valueOfObject[]` and `valueOfCar[]` to distinguish them.

*If you want to describe something in more detail, you can also define member functions. See [classes](./class.md) for details.*

## More Operations?

See [classes](./class.md).

## Notes

To improve memory access efficiency, when the compiler lays out the actual storage of members in a struct, it may align members to certain byte positions. This means there may be padding inside the struct. Therefore, the space occupied by the struct may be larger than the total space occupied by all of its members.

## References

1.  [Classes - cppreference.com](https://en.cppreference.com/w/cpp/language/class)
2.  [Data structures - cplusplus.com](http://www.cplusplus.com/doc/tutorial/structures/)
3.  [Alignment - Microsoft Docs](https://learn.microsoft.com/en-us/cpp/cpp/alignment-cpp-declarations)
