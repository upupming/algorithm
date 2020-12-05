/*
感觉像是离散化
错，是二分
解是 x， <=x 的数的个数一定是奇数，后续 <= x + m 的数的个数也一定是偶数
*/
#include <algorithm>
#include <cstring>
#include <iostream>
#include <unordered_map>
using namespace std;

int t, n, s[200010], e[200010], d[200010];
// <= x 的数有多少个: O(n)
int cnt(int x) {
    // 10^8 限制的是 ans 的大小
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int diff = min(x, e[i]) - s[i];
        if (diff >= 0)
            ans += diff / d[i] + 1;
    }
    return ans;
}
int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> s[i] >> e[i] >> d[i];
        int l = 1, r = 0x3fffffff;
        bool noWeak = true;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (cnt(mid) % 2 == 0)
                l = mid + 1;
            else
                r = mid, noWeak = false;
        }
        if (noWeak)
            cout << "There's no weakness." << endl;
        else
            // 这里不用单独写 == x 的 cnt 函数了，直接前缀和差分得结果
            cout << l << " " << cnt(l) - cnt(l - 1) << endl;
    }
    return 0;
}

/*
int t, n, s, e, d, cnt[10000000], mp[10000000], m;
// 直接用 map 会 TLE
// unordered_map<int, int> cnt;
// 直接用离散化 10^8 内存不够
int query(int x) {
    return lower_bound(mp, mp + m, x) - mp;
}
int main() {
    cin >> t;
    while (t--) {
        // cnt.clear();
        memset(cnt, 0, sizeof(cnt));
        m = 0;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> s >> e >> d;
            for (int j = s; j <= e; j += d) {
                if (m == 0) {
                    mp[m] = j;
                    cnt[m] += 1;
                    m++;
                } else {
                    int k = query(j);
                    // cout << j << " " << k << " " << m << endl;
                    cnt[k] += 1;
                    // 没有查到，说明是新增加元素
                    if (k == m)
                        mp[k] = j, m++;
                }
            }
        }

        bool noWeak = true;
        for (int i = 0; i < m; i++) {
            if (cnt[i] % 2) {
                noWeak = false;
                cout << mp[i] << " " << cnt[i] << endl;
            }
        }

        // for (auto c : cnt) {
        //     if (c.second % 2) {
        //         noWeak = false;
        //         cout << c.first << " " << c.second << endl;
        //     }
        // }
        if (noWeak) cout << "There's no weakness." << endl;
    }

    return 0;
}
*/