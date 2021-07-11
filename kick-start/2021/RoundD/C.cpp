#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

typedef long long LL;

int t;
LL n, m, a, b;
LL diff[N], cnt[N];

void solve() {
    cin >> n >> m;
    memset(diff, 0, sizeof diff);
    for (int i = 1; i <= n; i++) {
        cin >> a >> b;
        // [a, b] 区间都 +1
        diff[a]++, diff[b + 1]--;
    }
    set<LL> s;
    for (int i = 1; i < N; i++) {
        cnt[i] = cnt[i - 1] + diff[i];
        if (cnt[i] == 1) {
            // cout << i << ", ";
            s.insert(i);
        }
    }
    // cout << endl;
    for (int i = 1; i <= m; i++) {
        // 二分查找
        LL x;
        cin >> x;
        auto it = s.lower_bound(x);
        auto it1 = it;
        LL a, b;
        if (it == s.end())
            a = 1e19;
        else
            a = *it;
        if (it == s.begin())
            b = -1e19;
        else {
            it1--;
            b = *it1;
        }
        if (abs(x - a) < abs(x - b)) {
            cout << a << " ";
            s.erase(a);
        } else {
            cout << b << " ";
            s.erase(b);
        }
    }
    cout << endl;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
