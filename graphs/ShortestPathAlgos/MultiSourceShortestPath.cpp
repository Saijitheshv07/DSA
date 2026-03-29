//Famously known as Floyd-Warshall Algorithm
//TC : O(V^3)
//SC : O(V^2)
#include <bits/stdc++.h>
using namespace std;
void floydWarshall(vector<vector<int>>& dist) {
    int n = dist.size();

    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {

                if(dist[i][k] == INT_MAX || dist[k][j] == INT_MAX)
                    continue;

                dist[i][j] = min(
                    dist[i][j],
                    dist[i][k] + dist[k][j]
                );
            }
        }
    }
}

//if dist[i][i] < 0 -> negative cycle exists

//BONUS
void checkIfReachable(vector<vector<int>>& graph) {
    int n = graph.size();

    vector<vector<bool>> reach(n, vector<bool>(n, false));

    // initialize
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(graph[i][j]) reach[i][j] = true;
        }
        reach[i][i] = true;
    }

    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
            }
        }
    }

    // reach[i][j] now tells if i can reach j
}