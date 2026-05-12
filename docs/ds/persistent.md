author: morris821028

## Introduction

A persistent data structure can always preserve every historical version and supports immutable operations.

## Categories of Persistence

### Partially Persistent

All versions can be accessed, but only the newest version can be modified.

### Fully Persistent

All versions can both be accessed and modified.

If merging two historical versions is supported, the structure is also called confluently persistent.

## Practical Applications

### Computational Geometry

There are many offline algorithms in computational geometry. For example, a sweep-line algorithm can answer all queries in one pass and has excellent time complexity. However, if the problem is forced online, scanning once per query degrades query complexity from logarithmic time to linear time. Persistence gives another way to think about this situation: treat the sweep line's time axis as a changing parameter and persist the related structures. As long as queries can move through this time axis in logarithmic time, the original problem can be handled dynamically.

### String Processing

Persistence can achieve highly efficient merge operations and prevent performance degradation caused by generating large amounts of repeated strings, making many operations much faster than linear time. For example, C++ `rope` is a persistent data structure. This is not limited to string operations; whenever a processed type has many repeated parts, the idea of persistence can be useful.

### Version Rollback

This corresponds to redo/undo in most application software. If a database or operation changes use complex structures for efficiency (unlike `hash` or `set`, whose reverse operations may only need constant or logarithmic time), persistent structures reduce the cost of quickly rolling back changes.

The database itself may support constant-time rollback by recording only the changed parts. At the application layer, however, many implementations discard caches and recompute a new structure. If the rollback size is m, recomputing may cost n+m; when n and m differ greatly, repeated rollback feels very slow.

### Functional Programming

Functional programming requires special data structures that fit the language model, where immutability is especially important for parallel environments and debugging. For example, Java introduced stream classes after Java 8 in object-oriented programming, supporting functional-style syntax and special capabilities such as lazy evaluation and infinite domains.

## References

-   <https://en.wikipedia.org/wiki/Persistent_data_structure>
-   MIT course <https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-854j-advanced-algorithms-fall-2005/lecture-notes/persistent.pdf>
