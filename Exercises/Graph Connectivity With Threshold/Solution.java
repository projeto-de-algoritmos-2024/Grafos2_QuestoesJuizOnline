import java.util.*;

class UnionFind {
    private int[] parent;
    private int[] size;

    public UnionFind(int n) {
        parent = new int[n];
        size = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    public int find(int x) {
        if (x == parent[x]) {
            return x;
        }
        return parent[x] = find(parent[x]); // Path compression
    }

    public boolean union(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU == rootV) {
            return false;
        }
        if (size[rootU] > size[rootV]) { // Union by larger size
            size[rootU] += size[rootV];
            parent[rootV] = rootU;
        } else {
            size[rootV] += size[rootU];
            parent[rootU] = rootV;
        }
        return true;
    }
}

class Solution {
    public List<Boolean> areConnected(int n, int threshold, int[][] queries) {
        UnionFind uf = new UnionFind(n + 1);
        for (int z = threshold + 1; z <= n; z++) {
            for (int x = z * 2; x <= n; x += z) {
                uf.union(z, x);
            }
        }

        List<Boolean> results = new ArrayList<>();
        for (int[] query : queries) {
            results.add(uf.find(query[0]) == uf.find(query[1]));
        }
        return results;
    }
}