class Solution {
  public:
    //using DFS and graph coloring
    bool dfs(int i, vector<vector<int>> &graph, vector<int>& vis){
        vis[i] = 1;
        
        for(auto &nbr : graph[i]){
            if(vis[nbr] == 1){
               return true;
            }
            else if(dfs(nbr,graph,vis)) return true;
        }
        vis[i] = 2;
        return false;
    }
    bool isCyclic(int V, vector<vector<int>>& edges) {
        vector<vector<int>> graph(V+1);
        for(auto &it: edges){
            int a = it[0];
            int b = it[1];
            graph[a].push_back(b);
        }
        vector<int> vis(V+1,0);
        for(int i=0;i<V;i++){
            if(vis[i] == 0){
                if(dfs(i,graph,vis)) return true;
            }
        }
        return false;
    }
};