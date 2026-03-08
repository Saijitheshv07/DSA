#include <bits/stdc++.h>
using namespace std;
//Also Known as Kahn's Algorithm, TC - O(N+E) SC - O(N)

//Detect Cyle using Kahn's Algo
// if(res.size() != V)
//     cout << "Cycle exists";

// Kahn’s algorithm removes nodes with no dependencies. If some nodes always have dependencies, they must be part of a cycle.
class Solution {
public:
    vector<int> topoSort(int V, vector<vector<int>>& graph) {

        vector<int> indegree(V,0);

        for(int i = 0; i < V; i++){
            for(int nbr : graph[i]){
                indegree[nbr]++;
            }
        }

        queue<int> q;

        for(int i = 0; i < V; i++){
            if(indegree[i] == 0){
                q.push(i);
            }
        }

        vector<int> res;

        while(!q.empty()){
            int node = q.front();
            q.pop();

            res.push_back(node);

            for(int nbr : graph[node]){
                indegree[nbr]--;

                if(indegree[nbr] == 0){
                    q.push(nbr);
                }
            }
        }

        return res;
    }
};