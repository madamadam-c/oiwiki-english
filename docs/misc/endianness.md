This page briefly introduces the concept and classification of byte order.

## Introduction

Byte order is the storage rule for program objects that span multiple bytes; it describes how an object's bytes are arranged.

## Classification

There are two byte orders: little endian and big endian.

For convenience, we use a variable located at `0x100`, with type `int` and hexadecimal value `0x01234567`, as an example. Here `0x01` is the most significant byte, and `0x67` is the least significant byte.

### Little Endian

Little endian means that the machine stores an object in memory from the **least** significant byte to the **most** significant byte.

The variable mentioned above is represented as follows:

| .... | 0x100 | 0x101 | 0x102 | 0x103 | .... |
| ---- | ----- | ----- | ----- | ----- | ---- |
| .... | 67    | 45    | 23    | 01    | .... |

### Big Endian

Big endian means that the machine stores an object in memory from the **most** significant byte to the **least** significant byte.

The variable mentioned above is represented as follows:

| .... | 0x100 | 0x101 | 0x102 | 0x103 | .... |
| ---- | ----- | ----- | ----- | ----- | ---- |
| .... | 01    | 23    | 45    | 67    | .... |

### Difference Between the Two Orders

In fact, neither byte order is inherently better than the other. The names "little endian" and "big endian" come from *Gulliver's Travels*. In the book, two factions in Lilliput are locked in conflict because they cannot agree on whether to crack eggs from the little end or the big end. Like the egg-cracking dispute, the choice of byte order is not a technical matter.

Of course, inconsistent byte order can cause binary data to be reversed when transmitted between different types of machines. To avoid this, network applications established a standard that ensures data is sent using an agreed-upon network standard rather than the internal representation of different machines.

## Common Order Choices

-   Little endian: x86, ARM processors running Android, iOS, and Windows

-   Big endian: Sun, PPC Mac, Internet
