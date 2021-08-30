#include <bits/stdc++.h>
using namespace std;
// f[i] = f[i & k,0] +

class Solution {
   public:
    int minSessions(vector<int>& tasks, int sessionTime) {
        sort(tasks.begin(), tasks.end());
        int n = tasks.size();
        vector<int> dp(1 << (n + 1), INT_MAX), h(1 << n);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            h[1 << i] = i;
        }
        for (int i = 1; i < 1 << n; i++) {
            int j = i;
            do {
                j = (j - 1) & i;
                int sum = 0;
                // 其实这里可以不用 lowbit，直接 dp[i] = min(dp[j] + dp[i-j]) 也可以
                int x = i - j;
                while (x) {
                    int k = h[x & -x];
                    sum += tasks[k];
                    if (sum > sessionTime) break;
                    x -= x & -x;
                }
                if (sum <= sessionTime)
                    dp[i] = min(dp[i], dp[j] + 1);
            } while (j != 0);
        }
        return dp[(1 << n) - 1];
    }
};
/*
class Solution {
public:
    int minSessions(vector<int>& tasks, int sessionTime) {
        const int N = tasks.size();
        vector<int> dp(1 << N, 1000);
        dp[0] = 0;
        for (int s = 1; s < 1 << N; s++) {
            int req = 0;
            for (int i = 0; i < N; i++) if ((s >> i) & 1) req += tasks[i];
            if (req <= sessionTime) dp[s] = 1;
            for (int t = s; ; t = (t - 1) & s) {
                if (dp[s] > dp[t] + dp[s - t]) dp[s] = dp[t] + dp[s - t];
                if (t == 0) break;
            }
        }
        return dp.back();
    }
};

*/
