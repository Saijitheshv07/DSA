# [5. Longest Common Prefix](https://leetcode.com/problems/longest-common-prefix/description/)

- Lexicographical Sorting and String Comparison   


### C++ Solution

```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        sort(strs.begin(),strs.end());
        string a=strs[0];
        string b=strs[strs.size()-1];
        string res="";
        for(int i=0;i<a.size();i++){
            if(a[i]==b[i]){
                res += a[i];
            }
            else{
                break;
            }
        }
        return res;
    }
};
```

### Java Solution

- For arrays it is arr.length, while for Strings it is str.length()

```java
//Using map
class Solution {
    public String longestCommonPrefix(String[] strs) {
        Arrays.sort(strs);
        StringBuilder ans = new StringBuilder();
        String first = strs[0];
        String last = strs[strs.length-1];

        for(int i=0;i<Math.min(first.length(),last.length());i++){
            if(first.charAt(i) != last.charAt(i)){
                return ans.toString();
            }
            ans.append(first.charAt(i));
        }
        return ans.toString();
    }
}
```
