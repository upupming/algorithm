#include <climits>
#include <cstring>
#include <iostream>
using namespace std;

int a[510][510], dp[510][510], n, ans = INT_MIN;
int main() {
    cin >> n;
    memset(dp, 0x80, sizeof dp);
    dp[0][1] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cin >> a[i][j];
            if (j > 1)
                dp[i][j] = a[i][j] + max(dp[i - 1][j - 1], dp[i - 1][j]);
            else
                dp[i][j] = a[i][j] + dp[i - 1][j];
            if (i == n)
                ans = max(dp[i][j], ans);
        }
    }
    cout << ans << endl;
    return 0;
}