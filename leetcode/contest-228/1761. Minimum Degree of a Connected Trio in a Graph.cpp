#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        int deg[440] = {0}, w[int(1e6)] = {0};
        for (auto& e : edges) {
            int a = e[0], b = e[1];
            deg[a]++, deg[b]++;
            // 小边放在高位，大边放在低位
            if (a > b) swap(a, b);
            w[a * 1000 + b] = 1;
        }
        int ans = INT_MAX;
        // i < j < k 的顺序去遍历
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (!w[i * 1000 + j]) continue;
                for (int k = j + 1; k <= n; k++) {
                    if (!w[i * 1000 + k] || !w[j * 1000 + k]) continue;

                    ans = min(ans, deg[i] + deg[j] + deg[k] - 6);
                }
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};
