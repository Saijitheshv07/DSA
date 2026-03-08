#include <bits/stdc++.h>
using namespace std;
//Approach 1 : DFS , but too many states to explore 0 - unvisited, 1 - visiting, 2 - visited and not safe, 4 - visited and safe. TC - O(N+E) SC - O(N)
// class Solution {
// public:
//     void dfs(int curr, vector<vector<int>>& graph, vector<int>& vis){
//         vis[curr] = 1;
//         int safecount = 0;
//         int nbrcount = graph[curr].size();
//         for(int nbr : graph[curr]){
//             if(!vis[nbr]){
//                 dfs(nbr,graph,vis);
//             }
//             if(vis[nbr] == 4){
//                 safecount++;
//             }
//         }

//         if(safecount == nbrcount) vis[curr] = 4;
//         else vis[curr] = 2;
//     }
//     vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
//         int n = graph.size();
//         vector<int> vis(n+1,0);
//         for(int i=0;i<n;i++){
//             if(!vis[i]){
//                 dfs(i, graph, vis);
//             }
//         }
//         vector<int> res;
//         for(int i=0;i<n;i++){
//             if(vis[i] == 4){
//                 res.push_back(i);
//             }
//         }
//         return res;
//     }
// };

//Approach 2 : DFS with cycle detection, if there is a cycle then all nodes in that cycle are not safe. TC - O(N+E) SC - O(N)
class Solution {
public:
    bool dfs(int curr, vector<vector<int>>& graph, vector<int>& vis){
        if(vis[curr] == 2) return false;
        if(vis[curr] == 1) return true;
        vis[curr] = 1;
        for(int nbr : graph[curr]){
            if(!vis[nbr]){
                if(dfs(nbr,graph,vis)) return true;
            }
            else if(vis[nbr] != 2){
                return true;
            }
        }

        vis[curr] = 2;
        return false;
    }
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> vis(n+1,0);
        vector<int> res;
        for(int i=0;i<n;i++){
            if(!dfs(i, graph, vis)){
                res.push_back(i);
            }
        }
        return res;
    }
};

//Approach 3 : Topological Sort, TC - O(N+E) SC - O(N), Honestly this is not intuitive, This is Kahn's Algo in reverse
class Solution { 
public: 
  vector<int> eventualSafeNodes(vector<vector<int>>& graph) { 
    int nodeCount = graph.size(); 
    vector<int> inDegree(nodeCount, 0); 
    vector<vector<int>> reversedGraph(nodeCount); 
    for (int node = 0; node < nodeCount; node++) { 
      for (int ne : graph[node]) { 
        reversedGraph[ne].push_back(node); 
        inDegree[node]++; 
      } 
    } 
    queue<int> q; 
    for (int node = 0; node < nodeCount; node++) { 
      if (inDegree[node] == 0) { 
        q.push(node); 
      } 
    } 
    vector<bool> isSafe(nodeCount, false); 
    while (!q.empty()) { 
      int currentNode = q.front(); 
      q.pop(); 
      isSafe[currentNode] = true; 
      for (int ne : reversedGraph[currentNode]) { 
        inDegree[ne]--; 
        if (inDegree[ne] == 0) { 
          q.push(ne); 
        } 
      } 
    } 
    vector<int> safeNodes; 
    for (int node = 0; node < nodeCount; node++) { 
      if (isSafe[node]) { 
        safeNodes.push_back(node); 
      } 
    } 
    return safeNodes; 
  } 
};
