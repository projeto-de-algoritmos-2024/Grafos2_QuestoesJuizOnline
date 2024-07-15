import java.util.*;

class Solution {
    public int[][] modifiedGraphEdges(int n, int[][] edges, int source, int destination, int target) {
        int[][] adj = new int[n][n];
        for (int[] edge : edges) {
            int a = edge[0];
            int b = edge[1];
            int w = edge[2];
            adj[a][b] = w;
            adj[b][a] = w;
        }
        
        Pair shortestPath = findPath(adj, source, destination, target); 
        if (shortestPath == null) {
            return new int[][]{};
        } else if (shortestPath.w == target) {
            return fill(adj);
        } else {
            while (true) {
                int[] curr = findFirstModifiableIndex(shortestPath.parent, destination, source, adj);
                if (curr == null) {
                    return new int[][]{};
                }
                adj[curr[0]][curr[1]] = target - shortestPath.w + 1;
                adj[curr[1]][curr[0]] = target - shortestPath.w + 1;
                shortestPath = findPath(adj, source, destination, target);
                if (shortestPath.w == target) {
                    return fill(adj);
                } else if (shortestPath.w > target) {
                    return new int[][]{};
                }
            }
        }    
    }
    
    private int[] findFirstModifiableIndex(int[] parent, int dest, int source, int[][] adj) {
        List<Integer> path = new ArrayList<>();
        int curr = dest;
        while (curr != -1) {
            path.add(curr);
            curr = parent[curr];
        }
        Collections.reverse(path);
        for (int i = 0; i < path.size() - 1; i++) {
            int v1 = path.get(i);
            int v2 = path.get(i + 1);
            if (adj[v1][v2] == -1) {
                return new int[]{v1, v2};
            }
        }
        return null;
    }
    
    private int[][] fill(int[][] adj) {
        int n = adj.length;
        List<int[]> list = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (adj[i][j] != 0) {
                    int weight = adj[i][j] == -1 ? 1 : adj[i][j];
                    list.add(new int[]{i, j, weight});
                }
            }
        }
        int[][] result = new int[list.size()][3];
        for (int i = 0; i < list.size(); i++) {
            result[i] = list.get(i);
        }
        return result;
    }

    private Pair findPath(int[][] adj, int source, int destination, int target) {
        int n = adj.length;
        int[] dist = new int[n];
        int[] parent = new int[n];
        Arrays.fill(dist, Integer.MAX_VALUE);
        Arrays.fill(parent, -1);
        dist[source] = 0;
        parent[source] = -1;
        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[1]));
        pq.offer(new int[]{source, dist[source]});
        
        while (!pq.isEmpty()) {
            int[] curr = pq.poll();
            int node = curr[0], weight = curr[1];
            if (weight > target) {
                return null;
            }
            if (node == destination) {
                return new Pair(weight, parent);
            }
            for (int i = 0; i < n; i++) {
                if (adj[node][i] != 0) {
                    int newWeight = adj[node][i] == -1 ? 1 : adj[node][i];
                    if (weight + newWeight < dist[i]) {
                        dist[i] = weight + newWeight;
                        parent[i] = node;
                        pq.offer(new int[]{i, dist[i]});
                    }
                }
            }
        }
        return null;
    }

    private class Pair {
        int w;
        int[] parent;
        
        Pair(int w, int[] parent) {
            this.w = w;
            this.parent = parent;
        }
    }
}