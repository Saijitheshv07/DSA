# Graph Algorithms Quick Revision Notes

Compact A4 print version. Focus on:

- what the algorithm does
- when to use it
- TC / SC and why
- must-remember points
- short implementation

## 1. BFS Shortest Path in Unweighted Graph

### Concept

If every edge has equal cost, BFS gives shortest path in terms of number of edges.

### Use When

- graph is unweighted
- each move costs `1`
- need minimum steps from one source

### TC / SC

- `O(V + E)`: every node and edge is explored once
- `O(V)`: distance array + queue

### Remember

- BFS is valid only because all edges have equal weight
- first reach is shortest reach

```cpp
vector<int> shortestPath(int V, vector<vector<int>>& adj, int src) {
    vector<int> dist(V, INT_MAX);
    queue<int> q;
    dist[src] = 0;
    q.push(src);

    while(!q.empty()) {
        int node = q.front();
        q.pop();
        for(int nbr : adj[node]) {
            if(dist[node] + 1 < dist[nbr]) {
                dist[nbr] = dist[node] + 1;
                q.push(nbr);
            }
        }
    }
    return dist;
}
```

## 2. Dijkstra

### Concept

Greedy shortest path for graphs with non-negative weights. Always process the node with smallest current distance.

### Use When

- weighted graph
- all weights are `>= 0`
- single-source shortest path

### TC / SC

- `O((V + E) log V)`: heap operations during relaxations
- `O(V + E)`: graph + distance + heap

### Remember

- does not work for negative weights
- skip outdated heap entries

```cpp
vector<int> dijkstra(int V, vector<vector<pair<int,int>>>& adj, int src) {
    vector<int> dist(V, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while(!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();
        if(d > dist[node]) continue;

        for(auto &[nbr, wt] : adj[node]) {
            if(dist[node] + wt < dist[nbr]) {
                dist[nbr] = dist[node] + wt;
                pq.push({dist[nbr], nbr});
            }
        }
    }
    return dist;
}
```

## 3. Bellman-Ford

### Concept

Relax every edge `V - 1` times. Handles negative weights and detects negative cycles.

### Use When

- directed weighted graph
- negative edges exist
- need negative cycle detection

### TC / SC

- `O(VE)`: `V - 1` full edge relaxations
- `O(V)`: distance array

### Remember

- one extra edge pass checks negative cycle
- slower than Dijkstra, so use only when needed

```cpp
vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    for(int i = 1; i <= V - 1; i++) {
        for(auto &edge : edges) {
            int u = edge[0], v = edge[1], wt = edge[2];
            if(dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
            }
        }
    }

    for(auto &edge : edges) {
        int u = edge[0], v = edge[1], wt = edge[2];
        if(dist[u] != INT_MAX && dist[u] + wt < dist[v]) return {};
    }
    return dist;
}
```

## 4. Shortest Path in DAG

### Concept

Topological order guarantees we never need to come back, so one pass of relaxation is enough.

### Use When

- graph is DAG
- weights may even be negative

### TC / SC

- `O(V + E)`: topo sort + single relaxation pass
- `O(V)`: stack + visited + distance

### Remember

- fastest shortest path method for DAG
- works because no cycle exists

```cpp
void topoSort(int node, vector<vector<pair<int,int>>>& adj, vector<int>& vis, stack<int>& st) {
    vis[node] = 1;
    for(auto &[nbr, wt] : adj[node]) {
        if(!vis[nbr]) topoSort(nbr, adj, vis, st);
    }
    st.push(node);
}

vector<int> shortestPath(int V, vector<vector<pair<int,int>>>& adj, int src) {
    stack<int> st;
    vector<int> vis(V, 0), dist(V, INT_MAX);
    for(int i = 0; i < V; i++) if(!vis[i]) topoSort(i, adj, vis, st);

    dist[src] = 0;
    while(!st.empty()) {
        int node = st.top(); st.pop();
        if(dist[node] == INT_MAX) continue;
        for(auto &[nbr, wt] : adj[node]) {
            dist[nbr] = min(dist[nbr], dist[node] + wt);
        }
    }
    return dist;
}
```

## 5. Floyd-Warshall

### Concept

All-pairs shortest path. Try each node as an intermediate node.

### Use When

- need distance between every pair
- graph is not too large

### TC / SC

- `O(V^3)`: triple nested loop
- `O(V^2)`: distance matrix

### Remember

- if `dist[i][i] < 0`, negative cycle exists
- file name in repo says multi-source, but implementation is Floyd-Warshall

```cpp
void floydWarshall(vector<vector<int>>& dist) {
    int n = dist.size();
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(dist[i][k] == INT_MAX || dist[k][j] == INT_MAX) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}
```

## 6. Bipartite Graph

### Concept

A graph is bipartite if it can be colored with two colors such that adjacent nodes have different colors.

### Use When

- two-group partitioning
- odd cycle check

### TC / SC

- `O(V + E)`: every node and edge checked once
- `O(V)`: color array + queue/recursion stack

### Remember

- disconnected graph means start from every uncolored node
- graph with odd cycle is not bipartite

```cpp
bool bfs(vector<vector<int>>& graph, vector<int>& color, int src) {
    queue<int> q;
    q.push(src);
    color[src] = 0;

    while(!q.empty()) {
        int node = q.front();
        q.pop();
        for(int nbr : graph[node]) {
            if(color[nbr] == -1) {
                color[nbr] = 1 - color[node];
                q.push(nbr);
            } else if(color[nbr] == color[node]) {
                return false;
            }
        }
    }
    return true;
}
```

## 7. Cycle Detection

### Undirected Graph

- use parent tracking
- visited neighbor other than parent means cycle
- BFS or DFS both work

### Directed Graph

- use DFS coloring
- `0 = unvisited`, `1 = in path`, `2 = processed`
- edge to state `1` means cycle

### TC / SC

- `O(V + E)`
- `O(V)`

```cpp
bool dfsDirected(int node, vector<vector<int>>& graph, vector<int>& vis) {
    vis[node] = 1;
    for(int nbr : graph[node]) {
        if(vis[nbr] == 1) return true;
        if(vis[nbr] == 0 && dfsDirected(nbr, graph, vis)) return true;
    }
    vis[node] = 2;
    return false;
}
```

## 8. Eventual Safe States

### Concept

Safe node means every path from it ends without entering a cycle.

### Use When

- directed graph safety/stability problems

### TC / SC

- `O(V + E)`
- `O(V)`

### Remember

- nodes in cycle or leading to cycle are unsafe
- can solve using DFS cycle states or reverse graph + Kahn

```cpp
bool dfs(int curr, vector<vector<int>>& graph, vector<int>& vis){
    if(vis[curr] == 2) return false;
    if(vis[curr] == 1) return true;
    vis[curr] = 1;
    for(int nbr : graph[curr]) {
        if(dfs(nbr, graph, vis)) return true;
    }
    vis[curr] = 2;
    return false;
}

vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> vis(n, 0), res;
    for(int i = 0; i < n; i++) {
        if(!dfs(i, graph, vis)) res.push_back(i);
    }
    return res;
}
```

## 9. Topological Sort

### Concept

Linear ordering of DAG nodes so every directed edge goes from left to right in the order.

### Methods

- DFS finishing order
- Kahn's algorithm using indegree

### TC / SC

- `O(V + E)`
- `O(V)`

### Remember

- topo sort exists only for DAG
- in Kahn's algorithm, if result size `< V`, a cycle exists

```cpp
vector<int> topoSort(int V, vector<vector<int>>& graph) {
    vector<int> indegree(V, 0), res;
    for(int i = 0; i < V; i++) {
        for(int nbr : graph[i]) indegree[nbr]++;
    }

    queue<int> q;
    for(int i = 0; i < V; i++) if(indegree[i] == 0) q.push(i);

    while(!q.empty()) {
        int node = q.front();
        q.pop();
        res.push_back(node);
        for(int nbr : graph[node]) {
            if(--indegree[nbr] == 0) q.push(nbr);
        }
    }
    return res;
}
```

## 10. State-Space BFS Patterns

### Open the Lock

- state is a 4-digit string
- every wheel turn creates a neighbor
- shortest operations => BFS

### Word Ladder

- state is current word
- one valid letter change is one edge
- shortest transformation => BFS

### Rotten Oranges

- multi-source BFS
- all rotten oranges start together at time `0`
- BFS layers = minutes

### TC Pattern

- BFS over reachable states: `O(states + transitions)`

```cpp
int orangesRotting(vector<vector<int>>& grid) {
    queue<pair<int,int>> q;
    int m = grid.size(), n = grid[0].size(), fresh = 0, minutes = 0;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(grid[i][j] == 2) q.push({i, j});
            if(grid[i][j] == 1) fresh++;
        }
    }

    vector<pair<int,int>> dir = {{1,0},{-1,0},{0,1},{0,-1}};
    while(!q.empty() && fresh) {
        int sz = q.size();
        minutes++;
        while(sz--) {
            auto [x, y] = q.front(); q.pop();
            for(auto [dx, dy] : dir) {
                int nx = x + dx, ny = y + dy;
                if(nx >= 0 && ny >= 0 && nx < m && ny < n && grid[nx][ny] == 1) {
                    grid[nx][ny] = 2;
                    fresh--;
                    q.push({nx, ny});
                }
            }
        }
    }
    return fresh ? -1 : minutes;
}
```

## 11. MST Overview

### Concept

Minimum Spanning Tree connects all vertices of a weighted undirected graph with minimum total edge weight.

### Remember

- only for weighted undirected graph
- MST has exactly `V - 1` edges
- MST is not shortest path tree

## 12. Prim's Algorithm

### Concept

Grow MST from one chosen start node. Each step picks the minimum edge connecting the current tree to a new node.

### TC / SC

- `O((V + E) log V)`: heap-based edge selection
- `O(V + E)`: graph + arrays + heap

### Use When

- adjacency list input
- want MST by growing one component

```cpp
int primMST(int V, vector<vector<pair<int,int>>>& adj) {
    vector<int> key(V, INT_MAX), vis(V, 0);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    key[0] = 0;
    pq.push({0, 0});

    int total = 0;
    while(!pq.empty()) {
        auto [wt, node] = pq.top();
        pq.pop();
        if(vis[node]) continue;
        vis[node] = 1;
        total += wt;

        for(auto &[nbr, edgeWt] : adj[node]) {
            if(!vis[nbr] && edgeWt < key[nbr]) {
                key[nbr] = edgeWt;
                pq.push({edgeWt, nbr});
            }
        }
    }
    return total;
}
```

## 13. Kruskal's Algorithm

### Concept

Sort edges globally by weight and keep adding the smallest safe edge. DSU prevents cycles.

### TC / SC

- `O(E log E)`: sorting dominates
- `O(V)`: DSU arrays

### Use When

- edge list input
- DSU based MST problem

```cpp
struct Edge { int u, v, wt; };

struct DSU {
    vector<int> p, sz;
    DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) return false;
        if(sz[a] < sz[b]) swap(a, b);
        p[b] = a; sz[a] += sz[b];
        return true;
    }
};

int kruskalMST(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), [](auto &a, auto &b) { return a.wt < b.wt; });
    DSU dsu(V);
    int total = 0;
    for(auto &e : edges) if(dsu.unite(e.u, e.v)) total += e.wt;
    return total;
}
```

## 14. 10-Second Recognition Sheet

- unweighted shortest path -> BFS
- positive weighted shortest path -> Dijkstra
- negative edge shortest path -> Bellman-Ford
- DAG shortest path -> Topo + Relaxation
- all-pairs shortest path -> Floyd-Warshall
- two-color check -> Bipartite
- detect cycle in undirected graph -> parent tracking
- detect cycle in directed graph -> DFS coloring
- ordering with prerequisites -> Topological Sort
- minimum cost to connect all nodes -> MST

## 15. Common Confusions

- shortest path tree is not MST
- topo sort is only for DAG
- Bellman-Ford is not the default choice for every weighted graph
- BFS is enough when each edge cost is same
