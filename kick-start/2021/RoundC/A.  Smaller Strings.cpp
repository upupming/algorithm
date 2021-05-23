#include <algorithm>
#include <iostream>
typedef long long LL;
const int P = 1e9 + 7;
const int N = 1e5 + 10;

using namespace std;

int t;
LL n, k, f[N];
string s;

void prework() {
    f[0] = 1;
    for (LL i = 1; i <= n; i += 2) {
        f[i] = f[i + 1] = f[i - 1] * k % P;
    }
}

LL dfs(int dep, bool ok) {
    bool newOk = (s[dep] < s[n - 1 - dep] || (s[dep] == s[n - 1 - dep] && ok));
    if (dep == (n - 1) / 2) {
        // 边界情况，s[dep] == s[dep + 1] 的话，才用上一个位置的 ok
        if (n % 2 == 0) {
            return s[dep] - 'a' + newOk;
        } else {
            return s[dep] - 'a' + ok;
        }
    }
    LL ans = 0;
    // 填 a~s[dep]-1
    if (n - 2 * (dep + 1) >= 0) {
        ans += (s[dep] - 'a') * f[n - 2 * (dep + 1)];
    }
    // 填 s[dep]
    ans += dfs(dep + 1, newOk);
    ans %= P;
    return ans;
}

LL solve() {
    prework();
    return dfs(0, false);
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> k >> s;
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}
