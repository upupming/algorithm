#include <bits/stdc++.h>
using namespace std;

/*
f[i][j] 表示 s[i..j] 是回文串
初始情况 f[i][i] = true
j > i, f[i][j] = (s[j] == s[i] && f[i+1][j-1])
因此，计算 f[i][j] 之前必须先计算 f[i][j-1]，
因此 i 倒序来做
*/

class Solution {
   public:
    bool checkPartitioning(string s) {
        int n = s.length();
        vector<vector<bool>> f(n, vector<bool>(n));
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (i == j)
                    f[i][j] = true;
                else if (i + 1 == j)
                    f[i][j] = s[i] == s[j];
                else {
                    f[i][j] = (s[i] == s[j]) && f[i + 1][j - 1];
                }
            }
        }

        // 枚举所有的划分点
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                // f[0...i], f[i+1...j], f[j...n-1]
                if (f[0][i] && f[i + 1][j] && f[j + 1][n - 1])
                    return true;
            }
        }
        return false;
    }
};