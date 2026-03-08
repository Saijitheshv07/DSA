#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    //Idea : Use BFS to fill 4-adjacent fresh oranges with rotten oranges.
    //return ans == -1 ? 0 : ans; -> This Part is little tricky, one more solution is in queue maintain one more variable to check min time to rot that particular orange
    int orangesRotting(vector<vector<int>>& grid) {
        queue<pair<int,int>> q;
        int m = grid.size();
        int n = grid[0].size();
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j] == 2) q.push({i,j});
            }
        }

        int ans = -1;

        while(!q.empty()){
            int sz = q.size();
            cout << sz << endl;
            ans++;
            for(int k=0;k<sz;k++){
                auto [i,j] = q.front();
                q.pop();

                vector<vector<int>> val = {{-1,0}, {1,0}, {0,-1}, {0,1}};
                for(auto v : val){
                    if(i+v[0] < m && i+v[0] >= 0 && j+v[1] < n && j+v[1] >= 0 && grid[i+v[0]][j+v[1]] == 1){
                        grid[i+v[0]][j+v[1]] = 2;
                        q.push({i+v[0], j+v[1]});
                    }
                }

                
            }
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j] == 1) return -1;
            }
        }
        return ans == -1 ? 0 : ans;
    }
};