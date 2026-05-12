A **union** is a special class type that can hold only one of its non-static data members at a time.

Unions were officially added to the introductory level of the NOI syllabus in 2023.

## Defining a Union

The class specifier for declaring a union is similar to the declaration of a class or [struct](./struct.md):

```cpp
union MyUnion {
  int x;
  long long y;
} x;
```

The definition of a union is similar to that of a struct. With the definition above, `MyUnion` can also be used as a custom type. The name `MyUnion` may be omitted.

## Accessing/Modifying Members

As with structs, members can be accessed with `variable_name.member_name`.

The memory occupied by a union is **not smaller than** the size of its largest member, and all members **share the same memory space and address**. When one member is assigned, the other members in the union are overwritten because the memory is shared. In other words, a union can store the value of only one member at any given time.

For more uses of unions, see [cppreference: union declaration](https://en.cppreference.com/w/cpp/language/union).
