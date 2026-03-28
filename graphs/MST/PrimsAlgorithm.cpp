// Prim's Algorithm
// Builds MST for a connected, weighted, undirected graph.
// Greedy choice: always pick the minimum weight edge that connects
// a visited node to an unvisited node.
// TC: O((V + E) log V)
// SC: O(V + E)

#include <bits/stdc++.h>
using namespace std;

struct MSTResult {
    int totalWeight;
    vector<pair<int, int>> edges;
};

MSTResult primMST(int V, vector<vector<pair<int, int>>>& adj, int start = 0) {
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    key[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [wt, node] = pq.top();
        pq.pop();

        if (inMST[node]) continue;
        inMST[node] = true;

        for (auto& [nbr, edgeWt] : adj[node]) {
            if (!inMST[nbr] && edgeWt < key[nbr]) {
                key[nbr] = edgeWt;
                parent[nbr] = node;
                pq.push({key[nbr], nbr});
            }
        }
    }

    int totalWeight = 0;
    vector<pair<int, int>> mstEdges;

    for (int node = 0; node < V; node++) {
        if (key[node] == INT_MAX) continue;
        totalWeight += key[node];
        if (parent[node] != -1) {
            mstEdges.push_back({parent[node], node});
        }
    }

    return {totalWeight, mstEdges};
}
