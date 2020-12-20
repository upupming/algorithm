#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int maxResult(vector<int>& w, int k) {
        int n = w.size();
        vector<int> dp(n + 1, 0);
        deque<int> dqMax;
        dp[0] = w[0];
        dqMax.push_back(0);
        for (int i = 1; i < n; i++) {
            while (dqMax.size() && i - dqMax.front() > k) {
                // cout << i << " " << dqMax.front() << endl;
                dqMax.pop_front();
            }

            int maxIdx = dqMax.front();
            dp[i] = dp[maxIdx] + w[i];
            // cout << i << " " << maxIdx << " " << dp[maxIdx] << " " << dp[i] << endl;

            while (dqMax.size() && dp[dqMax.back()] <= dp[i]) {
                // cout << i << ", " << dqMax.back() << endl;
                dqMax.pop_back();
            }

            dqMax.push_back(i);
        }
        return dp[n - 1];
    }
};