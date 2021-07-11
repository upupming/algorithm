#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;

typedef long long LL;

int t;
LL n, q, p, a[N], pos, val, s, l, r, cmd;

LL qpow(LL a, LL b) {
    LL ans = 1ll;
    while (b) {
        if (b & 1) ans = 1ll * ans * a;
        a = 1ll * a * a;
        b >>= 1;
    }
    return ans;
}

unordered_map<LL, LL> m1;
LL V(LL x) {
    cout << "x: " << x << endl;
    if (m1.count(x)) return m1[x];
    if (x == 0 || x % p != 0) {
        m1[x] = 0;
        return 0;
    }
    LL ans = 0;
    while (x > 0 && x % p == 0) {
        x /= p;
        ans++;
    }
    m1[x] = ans;
    return ans;
}

void solve() {
    cin >> n >> q >> p;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    m1.clear();
    unordered_map<LL, unordered_map<LL, LL>> mp;
    while (q--) {
        cin >> cmd;
        if (cmd == 1) {
            cin >> pos >> val;
            a[pos] = val;
        } else {
            cin >> s >> l >> r;
            LL ans = 0;
            for (int i = l; i <= r; i++) {
                if (!mp[s].count(a[i])) {
                    mp[s][a[i]] = V(
                        qpow(a[i], s) - qpow(a[i] % p, s));
                }
                ans += mp[s][a[i]];
            }
            cout << ans << " ";
        }
    }
    cout << endl;
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(false);
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
