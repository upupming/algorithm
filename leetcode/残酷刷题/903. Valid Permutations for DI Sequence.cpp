/*
dp[i][j]: 0~i 且最后一位为 j 的排列，满足 s 的增减条件的数目
递增 I: dp[i][j] = dp[i-1][j-1] + dp[i-1][j-2] + ... + dp[i-1][0]
    注意特殊情况: xxxx2 可以由 2301 转移过来，因为将 >= 2 的数加 1 即可变成 34012
递减 D: dp[i][j] = dp[i-1][j] + dp[i-1][j+1] + ... + dp[i-1][i-1]
    注意特殊情况: xxxx2 可以由 0123 转移过来，因为将 >= 2 的数加 1 即可变成 12342
*/
const int P = 1e9 + 7, N = 210;
long long f[N][N], sum[N][N];
class Solution {
public:
    int naive(string s) {
        int n = s.length();
        memset(f, 0, sizeof f);
        f[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= i; j++) {
                if (s[i-1] == 'I') {
                    for (int k = 0; k < j; k++) f[i][j] += f[i-1][k], f[i][j] %= P;
                } else {
                    for (int k = j; k < i; k++) f[i][j] += f[i-1][k], f[i][j] %= P;
                }   
            }
        }
        int ans = 0;
        for (int j = 0; j <= n; j++) {
            ans = (ans + f[n][j]) % P;
        }
        return ans;
    }
    int optimized(string s) {
        int n = s.length();
        memset(f, 0, sizeof f);
        // sum[i][j] 表示 f[i][0] + ... + f[i][j-1]
        memset(sum, 0, sizeof sum);
        f[0][0] = 1, sum[0][1] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= i; j++) {
                if (s[i-1] == 'I') {
                    f[i][j] += sum[i-1][j], f[i][j] %= P;
                } else {
                    f[i][j] += sum[i-1][i] - sum[i-1][j] + P, f[i][j] %= P;
                }
                sum[i][j+1] = sum[i][j] + f[i][j], sum[i][j+1] %= P;
            }
        }
        int ans = 0;
        for (int j = 0; j <= n; j++) {
            ans = (ans + f[n][j]) % P;
        }
        return ans;
    }
    int numPermsDISequence(string s) {
        return optimized(s);
    }
};
