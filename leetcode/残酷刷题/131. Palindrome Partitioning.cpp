#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    bool is_palindrome(string s) {
        auto t = s;
        reverse(t.begin(), t.end());
        return s == t;
    }
    int dp[16][16], n;
    string s;
    // 回文串判定: 优化之后的解法，预处理 O(N^2)、查询 O(1)
    void init_dp() {
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
            if (i + 1 < n) dp[i][i + 1] = s[i] == s[i + 1];
        }
        // len 从 3 开始才不会出现 i + 1 > j - 1 的情况
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                if (s[i] == s[j] && dp[i + 1][j - 1]) dp[i][j] = 1;
            }
        }
    }
    // 枚举所有划分 + 回文判断: O(2^n * n)
    vector<vector<string>> partition(string _s) {
        s = _s, n = s.length();
        vector<vector<string>> ans;
        init_dp();
        for (int i = 0; i < 1 << (n - 1); i++) {
            vector<string> p;
            int last = 0, flag = 1;
            for (int j = 0; j < n - 1; j++) {
                if (i >> j & 1) {
                    if (!dp[last][j]) {
                        flag = 0;
                        break;
                    }
                    p.push_back(s.substr(last, j - last + 1));
                    last = j + 1;
                }
            }
            if (!flag || !dp[last][n - 1]) continue;
            p.push_back(s.substr(last, n - last));
            ans.push_back(p);
        }

        return ans;
    }
};
