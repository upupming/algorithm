/*
因为都是正数，所以肯定是对角线所有元素之和
如果可能有负数的话，就需要用 Kadane's algorithm, 参考蓝书 P30

10^3 * 10^7 会爆 int
*/
#include <iostream>
using namespace std;
const int N = 1e3 + 10;
typedef long long LL;

int t, c[N][N], n;

LL solve() {
    LL ans = 0;
    for (int d = -(n - 1); d <= n - 1; d++) {
        LL sum = 0;
        for (int i = 0; i < n; i++) {
            int j = i + d;
            if (j < 0 || j >= n) continue;
            sum += c[i][j];
        }
        ans = max(sum, ans);
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> c[i][j];
            }
        }
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}
