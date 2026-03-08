#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfs(int node, vector<vector<int>>& graph, vector<int>& vis, stack<int>& st){
        vis[node] = 1;

        for(int nbr : graph[node]){
            if(!vis[nbr]){
                dfs(nbr, graph, vis, st);
            }
        }

        st.push(node);
    }

    vector<int> topoSort(int V, vector<vector<int>>& graph) {
        vector<int> vis(V,0);
        stack<int> st;

        for(int i = 0; i < V; i++){
            if(!vis[i]){
                dfs(i, graph, vis, st);
            }
        }

        vector<int> res;

        while(!st.empty()){
            res.push_back(st.top());
            st.pop();
        }

        return res;
    }
};