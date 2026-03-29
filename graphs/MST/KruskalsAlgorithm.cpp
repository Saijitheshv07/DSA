// Kruskal's Algorithm
// Sort edges by weight and keep adding the smallest edge
// that does not create a cycle.
// DSU is used for cycle detection.
// TC: O(E log E)
// SC: O(V)

#include <bits/stdc++.h>
#include <numeric>
using namespace std;

struct Edge {
    int u, v, wt;
};

class DSU {
    vector<int> parent, size;

public:
    DSU(int n) {
        parent.resize(n);
        size.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }

    bool unionBySize(int u, int v) {
        u = findUPar(u);
        v = findUPar(v);

        if (u == v) return false;

        if (size[u] < size[v]) swap(u, v);
        parent[v] = u;
        size[u] += size[v];
        return true;
    }
};

pair<int, vector<Edge>> kruskalMST(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.wt < b.wt;
    });

    DSU dsu(V);
    int totalWeight = 0;
    vector<Edge> mstEdges;

    for (auto& edge : edges) {
        if (dsu.unionBySize(edge.u, edge.v)) {
            totalWeight += edge.wt;
            mstEdges.push_back(edge);
        }
    }

    return {totalWeight, mstEdges};
}
