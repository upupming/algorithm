#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 3e5 + 10;

int t, n, k, a[N], d[N], dp[N];
string s;

int solve(int d[]) {
    int finalAns = 2;

    for (int j = 3; j <= n; j++) {
        int diff = d[j - 1] - d[j];
        d[j] += diff, d[j + 1] -= diff;
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
        finalAns = max(finalAns, ans);
        d[j] -= diff, d[j + 1] += diff;
    }
    return finalAns;
}

int solve() {
    int ans = solve(d);
    reverse(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        d[i] = a[i] - a[i - 1];
        // cout << i << " " << a[i] << " " << d[i] << endl;
    }
    ans = max(ans, solve(d));
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
