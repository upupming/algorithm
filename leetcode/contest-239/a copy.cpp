#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
class Solution {
   public:
    bool dfs(LL last, string s, int dep) {
        if (s == "" && dep > 1) return true;
        for (int i = 0; i < s.length(); i++) {
            LL now = atoll(s.substr(0, i + 1).c_str());
            if (now >= last) return false;
            if ((dep == 0 || now == last - 1) && dfs(now, s.substr(i + 1), dep + 1)) {
                // cout << now << endl;
                return true;
            }
        }
        return false;
    }
    bool splitString(string s) {
        return dfs(1e18, s, 0);
    }
};
