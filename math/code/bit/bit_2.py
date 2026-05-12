# --8<-- [start:mul]
def mulPowerOfTwo(n, m):  # Compute n*(2^m)
    return n << m


def divPowerOfTwo(n, m):  # Compute n/(2^m)
    return n >> m


# --8<-- [end:mul]
# --8<-- [start:abs]
def Abs(n):
    return (n ^ (n >> 31)) - (n >> 31)
    """
    n>>31 obtains the sign of n: if n is positive, n>>31 equals 0;
    if n is negative, n>>31 equals -1.
    If n is positive, n^0=n, so the value is unchanged; if n is negative,
    n^(-1) is used. Compute the two's complements of n and -1, then XOR them.
    The result changes the sign of n and equals |n|-1; subtracting -1 gives |n|.
    """


# --8<-- [end:abs]
# --8<-- [start:minmax]
# If a >= b, (a - b) >> 31 is 0; otherwise it is -1.
def max(a, b):
    return b & ((a - b) >> 31) | a & (~(a - b) >> 31)


def min(a, b):
    return a & ((a - b) >> 31) | b & (~(a - b) >> 31)


# --8<-- [end:minmax]
# --8<-- [start:sgn]
# The case involving 0 is an exception.
def isSameSign(x, y):
    return (x ^ y) >= 0


# --8<-- [end:sgn]
# --8<-- [start:get_bit]
# Get the b-th bit of a, with the least significant bit numbered 0.
def getBit(a, b):
    return (a >> b) & 1


# --8<-- [end:get_bit]
# --8<-- [start:unset_bit]
# Set the b-th bit of a to 0, with the least significant bit numbered 0.
def unsetBit(a, b):
    return a & ~(1 << b)


# --8<-- [end:unset_bit]
# --8<-- [start:set_bit]
# Set the b-th bit of a to 1, with the least significant bit numbered 0.
def setBit(a, b):
    return a | (1 << b)


# --8<-- [end:set_bit]
# --8<-- [start:flap_bit]
# Flip the b-th bit of a, with the least significant bit numbered 0.
def flapBit(a, b):
    return a ^ (1 << b)


# --8<-- [end:flap_bit]


if __name__ == "__main__":
    a, b = map(int, input().split())

    for i in range(16):
        print(f"{mulPowerOfTwo(a, i)} {divPowerOfTwo(a, i)}")

    assert Abs(-a) == a
    assert Abs(a) == a

    assert max(a, b) == (a if a > b else b)
    assert min(a, b) == (a if a < b else b)

    print(int(isSameSign(a, b)))

    for i in range(32):
        print(f"{getBit(a, i)} {unsetBit(a, i)} {setBit(a, i)} {flapBit(a, i)}")
