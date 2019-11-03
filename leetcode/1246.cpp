class Solution {
public:
    int minimumMoves(vector<int>& a) {
        int n = a.size();
        // dp[l][r] = n 表示 [l, r] 之间的子串需要 n 次
        vector<vector<int>> dp(n, vector<int>(n, n));
        for (int L = n - 1; L >= 0; --L) {
            for (int R = L; R < n; R++) {
                // L, R
                if (L == R) {
                    dp[L][R] = 1;
                    continue;
                }
                // L, X, R
                if (L + 1 == R) {
                    dp[L][R] = (a[L] == a[R]) ? 1 : 2;
                    continue;
                }
                // L, ..., R
                dp[L][R] = dp[L+1][R-1] + ((a[L] == a[R]) ? 0 : 2);
                for (int i = L; i < R; i++) {
                    dp[L][R] = min(dp[L][R], dp[L][i] + dp[i+1][R]);
                }
            }
        }
        return dp[0][n-1];
    }
};