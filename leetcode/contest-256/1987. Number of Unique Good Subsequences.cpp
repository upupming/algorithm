#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int numberOfUniqueGoodSubsequences(string binary) {
        constexpr int md = 1000000007;
        // 只考虑以 1 开头的情况，dp[i] 是当前字符串以 i 结尾的话子串个数
        vector<int> dp{0, 1};
        long long ret = 0;
        for (auto c : binary) {
            int t = c - '0';
            // 以 t 结尾的字符串个数
            ret += dp[t];
            // 如果当前结尾是 1，接下来如果来一个 0，字符串个数是 dp[0] += dp[1]
            // 如果当前结尾是 0，接下来如果来一个 1，字符串个数是 dp[1] += dp[0]
            (dp[t ^ 1] += dp[t]) %= md;
        }
        // 一定包含一个子串 '0'
        if (binary != string(binary.size(), '1')) ret++;
        return ret % md;
    }
};
