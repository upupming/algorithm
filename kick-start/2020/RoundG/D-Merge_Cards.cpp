/*
跟石子合并差不多，都是区间 dp，需要先求一下前缀和
但是这里我们 dp 表示的不再是最大/最小，而是平均值
dp 1  2  3
1  0  3  13 + (3+11)/2
2     0  11
3        0
直接转移的话，时间复杂度是 O(n^3)，肯定是过不了 test 3 的
但是从 dp 矩阵来看，每个点要加的值就是它左边所有的值和他下面所有的值，维护这个和即可
N * A = 5 * 10^2，爆 int
*/
#include <iostream>
#include <vector>
using namespace std;
const int N = 5e3 + 10;
typedef long long LL;

int t, n;
LL a[N], sum[N];
double dp[N][N], Left[N][N], down[N][N];

// 暴力解法
double solve_cubic() {
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            dp[i][j] = sum[j] - sum[i - 1];
            double tmp = 0, cnt = 0;
            for (int k = i; k + 1 <= j; k++) {
                tmp += dp[i][k] + dp[k + 1][j];
                cnt++;
            }
            dp[i][j] += tmp / cnt;
        }
    }
    return dp[1][n];
}

// 优化解法
double solve() {
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            dp[i][j] = sum[j] - sum[i - 1];
            double tmp = Left[i][j] + down[i][j];
            int cnt = j - i;
            dp[i][j] += tmp / cnt;
            Left[i][j + 1] = Left[i][j] + dp[i][j];
            down[i - 1][j] = down[i][j] + dp[i][j];
        }
    }
    return dp[1][n];
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            sum[i] = sum[i - 1] + a[i];
        }
        printf("Case #%d: %lf\n", i, solve());
    }
    return 0;
}
