#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    vector<bool> canEat(vector<int>& c, vector<vector<int>>& q) {
        int n = c.size(), m = q.size();
        vector<long long> sum(n + 1);
        vector<bool> ans(m);
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + c[i - 1];
        }

        for (int i = 0; i < m; i++) {
            auto x = sum[q[i][0]], y = sum[q[i][0] + 1];
            // 做的时候没看到天数也是以 0 开始！！，所以需要「+1」
            if (1ll * q[i][2] * (q[i][1] + 1) > x && (q[i][1] + 1) * 1 <= y) {
                ans[i] = true;
            } else {
                ans[i] = false;
            }
        }
        return ans;
    }
};