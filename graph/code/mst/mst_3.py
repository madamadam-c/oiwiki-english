class Edge:
    def __init__(self, u, v, w):
        self.u = u
        self.v = v
        self.w = w


fa = [0] * 1010  # Define parent
g = []


def add(u, v, w):
    g.append(Edge(u, v, w))


# Standard DSU
def findroot(x):
    if fa[x] == x:
        return x
    fa[x] = findroot(fa[x])
    return fa[x]


def Merge(x, y):
    x = findroot(x)
    y = findroot(y)
    fa[x] = y


# Kruskal algorithm
def kruskal():
    tot = 0  # Stores the number of selected edges
    ans = 0  # Stores the total cost
    for e in g:
        x = findroot(e.u)
        y = findroot(e.v)
        if x != y:  # If the parents are different
            fa[x] = y  # Merge
            tot += 1  # Increase edge count
            ans += e.w  # Increase cost
            if tot == n - k:  # Check whether the selected edge count satisfies k marshmallows
                print(ans)
                return
    print("No Answer")  # Cannot connect


if __name__ == "__main__":
    n, m, k = map(int, input().split())
    if n == k:  # Handle boundary case separately
        print("0")
        exit()
    for i in range(1, n + 1):  # Initialize
        fa[i] = i
    for i in range(1, m + 1):
        u, v, w = map(int, input().split())
        add(u, v, w)  # Add edge
    g.sort(key=lambda edge: edge.w)  # Sort by edge weight first
    kruskal()
