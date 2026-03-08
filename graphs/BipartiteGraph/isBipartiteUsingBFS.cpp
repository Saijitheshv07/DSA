#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    //Idea : Use node coloring, no two adjacent nodes should have same color.
    //The Trick here in the intial push to the queue, push all uncolored nodes, not just 0. 
    bool bfs(vector<vector<int>>& graph, vector<int>& color, int curr){
        queue<int> q;
        q.push(curr);
        while(!q.empty()){
            int node = q.front();
            q.pop();

            for(int nbr : graph[node]){
                if(color[nbr] != -1){
                    if(color[nbr] != 1-color[node]) return false;
                }
                else{
                    color[nbr] = 1-color[node];
                    q.push(nbr);
                }
            }
        }
        return true;
    }
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n,-1);
        for(int i=0;i<n;i++){
            if(color[i] == -1){
                color[i]=0;
                if(!bfs(graph,color,i)) return false;
            }
        }
        return true;
    }
};