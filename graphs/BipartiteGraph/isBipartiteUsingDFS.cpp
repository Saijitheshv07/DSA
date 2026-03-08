#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    //Idea : Use node coloring, no par-child nodes should have same color.
    bool dfs(vector<vector<int>>& graph, vector<int>& color, int curr, int parent){
        if(parent == -1){
            color[curr] = 0;
        }
        else{
            color[curr] = 1-color[parent];
        }

        for(int nbr : graph[curr]){
            if(color[nbr] == -1){
                if(!dfs(graph,color,nbr,curr)) return false; //I forgot this line in first attempt, since I copied BFS code and converted it.
            }
            else{
                if(color[nbr] != 1-color[curr]) return false;
            }
        }
        return true;
    }
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n,-1);
        for(int i=0;i<n;i++){
            if(color[i] == -1){
                if(!dfs(graph,color,i,-1)) return false;
            }
        }
        return true;
    }
};