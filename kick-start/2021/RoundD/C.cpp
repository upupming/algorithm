#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

typedef long long LL;

int t, n, m;
LL s;
// key: 区间起点, value: 区间终点
map<LL, LL> intervals;

void add(LL a, LL b) {
    if (a <= b)
        intervals.insert({a, b});
}
void solve() {
    cin >> n >> m;
    intervals.clear();
    for (int i = 0; i < n; i++) {
        LL A, B;
        cin >> A >> B;
        intervals[A] = B;
    }
    for (int i = 0; i < m; i++) {
        cin >> s;
        auto it = intervals.upper_bound(s);
        auto [x, y] = *it;
        LL ch;
        if (it == intervals.begin()) {
            ch = x;
            intervals.erase(it);
            add(x + 1, y);
        } else {
            auto it1 = it;
            it1--;
            auto [l, r] = *it1;
            if (s <= r) {
                ch = s;
                intervals.erase(it1);
                add(l, s - 1);
                add(s + 1, r);
            } else {
                auto u = abs(r - s), v = abs(x - s);
                // 相等，选难度小的题目
                if (u <= v) {
                    ch = r;
                    intervals.erase(it1);
                    add(l, r - 1);
                } else {
                    ch = x;
                    intervals.erase(it);
                    add(x + 1, y);
                }
            }
        }
        cout << ch << " ";
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
