#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;

int t, d, n, k;
typedef long long LL;

void solve() {
    cin >> d >> n >> k;
    vector<vector<int>> add(d + 2, vector<int>());
    vector<vector<int>> remove(d + 2, vector<int>());
    for (int i = 0; i < n; i++) {
        int h, s, e;
        cin >> h >> s >> e;
        add[s].push_back(h);
        remove[e + 1].push_back(h);
    }
    LL ans = 0, sum = 0;
    multiset<int> s, t;
    for (int i = 1; i <= d; i++) {
        for (auto& r : remove[i]) {
            // 如果在 s 中，从 s 中删除后到 t 中拿一个最大的过来
            if (s.count(r)) {
                s.erase(s.find(r));
                sum -= r;
                if (t.size()) {
                    s.insert(*t.rbegin());
                    sum += *t.rbegin();
                    t.erase(--t.end());
                }
            } else {
                t.erase(r);
            }
        }
        for (auto& a : add[i]) {
            if (s.size() < k) {
                s.insert(a);
                sum += a;
            } else {
                if (a <= *s.begin()) {
                    t.insert(a);
                } else {
                    auto it = s.begin();
                    t.insert(*it);
                    sum -= *it;
                    s.erase(it);
                    s.insert(a);
                    sum += a;
                }
            }
        }
        ans = max(ans, sum);
        // cout << i << endl;
        // cout << "s: ";
        // for (auto it = s.begin(); it != s.end(); it++) {
        //     cout << *it << " ";
        // }
        // cout << endl;
        // cout << "t: ";
        // for (auto it = t.begin(); it != t.end(); it++) {
        //     cout << *it << " ";
        // }
        // cout << endl;
        // cout << "ans, sum " << ans << " " << sum << endl;
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
