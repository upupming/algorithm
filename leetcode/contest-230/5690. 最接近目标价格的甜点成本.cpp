#include <bits/stdc++.h>
using namespace std;
class Solution {
    vector<int> b, tp;
    int n, m, t, ans;
    void dfs(int i, int j, int sum, bool flag) {
        // cout << sum << endl;
        if (sum - t > abs(ans - t)) return;

        if (i < n) {
            // 不选第 i 个
            dfs(i + 1, j, sum, flag);
            if (!flag)
                // 选第 i 个
                dfs(i + 1, j, sum + b[i], true);
        } else {
            if (!flag) return;
            if (j == m) {
                // cout << sum << endl;
                if (abs(sum - t) < abs(ans - t)) {
                    ans = sum;
                } else if (abs(sum - t) == abs(ans - t)) {
                    ans = min(ans, sum);
                }
                return;
            }

            // 看可以选多少第 j 个
            for (int k = 0; k <= 2; k++) {
                dfs(i, j + 1, sum + tp[j] * k, flag);
            }
        }
    }

   public:
    int closestCost(vector<int>& _b, vector<int>& _tp, int _t) {
        b = _b, tp = _tp, t = _t;
        n = b.size(), m = tp.size();
        ans = 0x3f3f3f3f;
        dfs(0, 0, 0, false);
        return ans;
    }
};
