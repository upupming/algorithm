/*
差分之后求一下最长相等子数组
如果 d[i] == d[i-1]
dp[i] = dp[i-1] + 1
否则
dp[i] = 1
*/
#include <iostream>
using namespace std;
const int N = 2e5 + 10;

int t, a[N], n, d[N], dp[N];

int solve() {
    // 注意如果 d[1] == d[2] 的话，是不能让 dp[2] = 2 的，只能认为有一个相等的差，因此需要特判
    dp[2] = 1;
    int ans = 2;
    for (int i = 3; i <= n; i++) {
        if (d[i] == d[i - 1])
            dp[i] = dp[i - 1] + 1;
        else
            dp[i] = 1;
        // cout << i << " " << d[i] << " " << dp[i] << endl;
        // 加一是因为有 x 个相等的差，那么等差数列的长度是 x + 1
        ans = max(ans, dp[i] + 1);
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            d[i] = a[i] - a[i - 1];
        }
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}
