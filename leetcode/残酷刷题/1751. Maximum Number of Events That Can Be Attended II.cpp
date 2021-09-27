#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int maxValue(vector<vector<int>> &events, int k) {
        int n = events.size();
        sort(events.begin(), events.end(), [](auto &a, auto &b) {
            return a[1] < b[1];
        });
        vector<int> s;
        // 添加哨兵
        events.insert(events.begin(), {0, 0, 0});
        for (auto &e : events) s.push_back(e[1]);
        // f[0][1] ~f[0][k] 均为 0，表示前面可以选人一多，这样就使得最终真正在 1~n 里面选的总数可以小于 k 了
        vector<vector<int>> f(n + 1, vector<int>(k + 1));
        for (int i = 1; i <= n; i++) {
            int j = lower_bound(s.begin(), s.end(), events[i][0]) - 1 - s.begin();
            for (int t = 1; t <= k; t++) {
                f[i][t] = max(f[i - 1][t], f[j][t - 1] + events[i][2]);
            }
        }
        return f[n][k];
    }
};
