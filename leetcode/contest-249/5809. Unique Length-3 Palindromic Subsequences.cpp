#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int countPalindromicSubsequence(string s) {
        int n = s.length();
        vector<int> mi(26, INT_MAX), mx(26, INT_MIN);
        vector<vector<int>> cnt(26, vector<int>(n + 1));
        for (int i = 1; i <= n; i++) {
            int cur = s[i - 1] - 'a';
            for (int j = 0; j < 26; j++) {
                if (j == cur)
                    cnt[j][i] = cnt[j][i - 1] + 1;
                else
                    cnt[j][i] = cnt[j][i - 1];
            }
            mi[cur] = min(mi[cur], i);
            mx[cur] = max(mx[cur], i);
        }
        int ans = 0;
        for (int i = 0; i < 26; i++) {
            int a = mi[i], b = mx[i];
            if (a == INT_MAX || b == INT_MIN) continue;
            if (a + 1 >= b) continue;
            for (int j = 0; j < 26; j++) {
                if (cnt[j][b - 1] - cnt[j][a] > 0) {
                    // cout << i << " "
                    //      << a << " " << b << " " << j << endl;
                    ans++;
                }
            }
        }
        return ans;
    }
};
