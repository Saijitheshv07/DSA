#include <bits/stdc++.h>
using namespace std;
#include <unordered_set>
//Word Ladder Type Problem
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> s(wordList.begin(),wordList.end());
        queue<pair<string,int>> q;
        q.push({beginWord,1});

        while(!q.empty()){
            auto [word, steps] = q.front();
            q.pop();
            
            if(word == endWord) return steps;
            for(int i=0;i<word.size();i++){
                string original = word;
                for(char ch ='a'; ch <= 'z'; ch++){
                    word[i]=ch;
                    if(s.find(word) != s.end()){
                        s.erase(word);
                        q.push({word,steps+1});
                    }
                }
                word = original;
            }
            
        }
        return 0;
    }
};