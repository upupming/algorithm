#include <algorithm>
#include <iostream>

using namespace std;

int t, n;
long long d, x[1005];

long long solve() {
    long long ans = __LONG_LONG_MAX__;
    for (int i = n - 1; i >= 0; i--) {
        // 离 d 最近的 x[i] 的倍数
        x[i] = d / x[i] * x[i];
        ans = min(ans, x[i]);
        d = min(d, x[i]);
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> d;
        for (int i = 0; i < n; i++) {
            cin >> x[i];
        }
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}