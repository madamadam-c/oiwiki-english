import java.util.Arrays;
import java.util.Scanner;

class Edge {
    int u;
    int v;
    int w;

    Edge(int u, int v, int w) {
        this.u = u;
        this.v = v;
        this.w = w;
    }
}

public class Main {
    static int[] parent = new int[1010];  // Define parent
    static int m, n, k;  // n is the number of vertices, m is the number of edges, k is the required number of marshmallows

    static Edge[] edges = new Edge[10010];
    static int l;

    static void addEdge(int u, int v, int w) {
        edges[++l] = new Edge(u, v, w);
    }

    // Standard DSU
    static int findroot(int x) {
        if (parent[x] != x) {
            parent[x] = findroot(parent[x]);
        }
        return parent[x];
    }

    static void Merge(int x, int y) {
        x = findroot(x);
        y = findroot(y);
        parent[x] = y;
    }

    static boolean cmp(Edge A, Edge B) {
        return A.w < B.w;
    }

    // Kruskal algorithm
    static void kruskal() {
        int tot = 0;  // Stores the number of selected edges
        int ans = 0;  // Stores the total cost

        for (int i = 1; i <= m; i++) {
            int xr = findroot(edges[i].u);
            int yr = findroot(edges[i].v);
            if (xr != yr) {   // If the parents are different
                Merge(xr, yr); // Merge
                tot++; // Increase edge count
                ans += edges[i].w; // Increase cost
                if (tot == n - k) {  // Check whether the selected edge count satisfies k marshmallows
                    System.out.println(ans);
                    return;
                }
            }
        }
        System.out.println("No Answer");  // Cannot connect
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        m = scanner.nextInt();
        k = scanner.nextInt();

        if (n == k) { // Handle boundary case separately
            System.out.println("0");
            return;
        }

        // Initialize
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
        for (int i = 1; i <= m; i++) {
            int u = scanner.nextInt();
            int v = scanner.nextInt();
            int w = scanner.nextInt();
            addEdge(u, v, w);  // Add edge
        }
        Arrays.sort(edges, 1, m + 1, (a, b) -> Integer.compare(a.w, b.w));  // Sort by edge weight first
        kruskal();
        scanner.close();
    }
}
