#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;
//Word Ladder Type Problem 
class Solution {
public:
    char turnLeft(char c){
        return c == '0' ? '9' : c-1;
    }
    char turnRight(char c){
        return c == '9' ? '0' : c+1;
    }
    vector<string> nextOptions(string s){
        vector<string> res;
        for(int i=0;i<4;i++){
            string copy = s;
            copy[i] = turnLeft(s[i]);
            res.push_back(copy);
            copy[i] = turnRight(s[i]);
            res.push_back(copy);
        }
        return res;
    }
    int openLock(vector<string>& deadends, string target) {
        queue<pair<string,int>> q; //curr,moves
        q.push({"0000",0});
        unordered_set<string> s(deadends.begin(), deadends.end());
        if(s.find("0000") != s.end()) return -1;
        s.insert("0000");

        while(!q.empty()){
            auto [curr, moves] = q.front();
            q.pop();
            if(curr == target) return moves;
            vector<string> nextoptions = nextOptions(curr);
            for(auto it : nextoptions){
                if(s.find(it) != s.end()) continue;
                s.insert(it);
                q.push({it,1+moves});
            }
        }
        return -1;
    }
};