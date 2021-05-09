#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    bool dfs(string& s, int start, int cnt, long long last) {
        if (start >= s.length()) return cnt >= 2;
        for (int i = start; i < s.length(); i++) {
            // 溢出不用考虑
            auto current = atoll(s.substr(start, i - start + 1).c_str());
            if (last == -1 || current == last - 1) {
                if (dfs(s, i + 1, cnt + 1, current))
                    return true;
            }
        }
        return false;
    }
    bool splitString(string s) {
        return dfs(s, 0, 0, -1);
    }
};
