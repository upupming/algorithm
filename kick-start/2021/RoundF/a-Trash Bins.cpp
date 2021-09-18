#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;

int t, l[N], r[N];
typedef long long LL;

void solve() {
    int n;
    string s;
    cin >> n >> s;
    l[0] = s[0] == '1' ? 0 : 1e6;
    for (int i = 1; i < n; i++) {
        if (s[i] == '1')
            l[i] = 0;
        else
            l[i] = l[i - 1] + 1;
    }
    r[n - 1] = s[n - 1] == '1' ? 0 : 1e6;
    for (int i = n - 2; i >= 0; i--) {
        if (s[i] == '1')
            r[i] = 0;
        else
            r[i] = r[i + 1] + 1;
    }
    LL ans = 0;
    for (int i = 0; i < n; i++) {
        // cout << i << " " << l[i] << " " << r[i] << endl;
        ans += min(l[i], r[i]);
    }
    cout << ans << endl;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
