#include <bits/stdc++.h>
using namespace std;

/*
双向 DFS，两个方向的拼接
ACWing 171. 送礼物
*/

class Solution {
    int e;
    vector<int> a, s, t;

    void dfs(int k, int sum, vector<int>& s) {
        if (k >= e) {
            s.push_back(sum);
            return;
        }
        // 选第 k 个数
        dfs(k + 1, sum + a[k], s);
        // 不选第 k 个数
        dfs(k + 1, sum, s);
    }

   public:
    int minAbsDifference(vector<int>& nums, int goal) {
        a = nums;
        int n = a.size();
        // 向上取整
        e = (n + 1) / 2;
        dfs(0, 0, s);
        sort(s.begin(), s.end());
        unique(s.begin(), s.end());
        e = n;
        dfs((n + 1) / 2, 0, t);
        unique(t.begin(), t.end());
        int ans = INT_MAX;
        for (auto& v : t) {
            int l = 0, r = s.size() - 1;
            // cout << v << endl;
            while (l < r) {
                int mid = l + r + 1 >> 1;
                if (s[mid] + v - goal <= 0)
                    l = mid;
                else
                    r = mid - 1;
            }
            // cout << l << " " << s[l] << endl;
            ans = min(ans, abs(s[l] + v - goal));
            if (l + 1 < s.size()) {
                // cout << l + 1 << " " << s[l + 1] << endl;
                ans = min(ans, abs(s[l + 1] + v - goal));
            }
        }
        return ans;
    }
};