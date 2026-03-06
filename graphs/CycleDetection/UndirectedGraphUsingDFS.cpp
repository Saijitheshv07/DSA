class Solution {
  public:
    //using DFS and parent
    //Point to be remembered is in DFS marking should be done when processing the recursion request.
    bool dfs(int i, int parent, vector<vector<int>> &graph, vector<int>& vis){
        vis[i] = 1;
        
        for(auto &nbr : graph[i]){
            if(vis[nbr]){
                if(nbr != parent) return true;
            }
            else if(dfs(nbr,i,graph,vis)) return true;
        }
        return false;
    }
    bool isCycle(int V, vector<vector<int>>& edges) {
        vector<vector<int>> graph(V+1);
        for(auto &it: edges){
            int a = it[0];
            int b = it[1];
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        vector<int> vis(V+1,0);
        for(int i=0;i<V;i++){
            if(!vis[i]){
                if(dfs(i,-1,graph,vis)) return true;
            }
        }
        return false;
    }
};