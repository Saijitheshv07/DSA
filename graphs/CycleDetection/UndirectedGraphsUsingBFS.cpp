class Solution {
  public:
    //using BFS parent and parent
    //Point to be remembered is in BFS marking should be done when pushing in the queue.
    bool bfs(int i, int parent, vector<vector<int>> &graph, vector<int>& vis){
        queue<pair<int,int>> q;
        
        q.push({i,parent});
        vis[i] = true;
        
        while(!q.empty()){
            auto [a,b] = q.front();
            q.pop();
            
            for(int nbr : graph[a]){
                if(!vis[nbr]){
                    vis[nbr] = true;
                    q.push({nbr,a});
                }
                else{
                    if(nbr != b) return true;
                }
            }
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
                if(bfs(i,-1,graph,vis)) return true;
            }
        }
        return false;
    }
};