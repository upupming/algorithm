#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    vector<int> recoverArray(int n, vector<int>& sums) {
        int m = INT_MAX;
        for (auto& a : sums) m = min(m, a);
        for (auto& a : sums) a -= m;
        multiset<int> s(sums.begin(), sums.end());
        // 删除 0（空子数组）
        s.erase(s.begin());
        vector<int> ans;
        ans.push_back(*s.begin());

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < (1 << i); j++) {
                if (j >> (i - 1) & 1) {
                    int sum = 0;
                    for (int k = 0; k < i; k++) {
                        if (j >> k & 1) sum += ans[k];
                    }
                    s.erase(s.find(sum));
                }
            }

            ans.push_back(*s.begin());
        }

        for (int i = 0; i < 1 << n; i++) {
            int sum = 0;
            for (int j = 0; j < n; j++) {
                if (i >> j & 1) sum += ans[j];
            }
            if (sum == -m) {
                for (int j = 0; j < n; j++) {
                    if (i >> j & 1) ans[j] = -ans[j];
                }
                break;
            }
        }
        return ans;
    }
};
