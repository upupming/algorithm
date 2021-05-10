#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;

int t, n, a[N], d[N];

int solve() {
    for (int i = 1; i <= n - 1; i++) {
        d[i] = a[i + 1] - a[i];
    }
    // 每一个子串的起始下标
    set<int> startPos;
    for (int i = 1; i <= n - 1; i++) {
        if (i == 1 || d[i] != d[i - 1]) {
            // i 是一个新的分段的起点
            startPos.insert(i);
        }
    }
    // 哨兵
    startPos.insert(n);

    // 枚举所有的子串，尝试修改后面的子串的第 1 个值
    int m = startPos.size(), ans = 0;
    for (auto it = startPos.begin(); it != startPos.end(); it++) {
        int i = *it, val = d[i];
        if (i > n - 1) break;
        auto it2 = it;
        it2++;

        // j 是下一个子串的开头
        int j = *it2;
        // 区间 [i, j)
        int tmp = j - i;
        // 区间 [i, j]
        if (j <= n - 1) tmp++;
        // 区间 [i, j+1]
        if (j + 1 <= n - 1 && d[j] + d[j + 1] == 2 * val) {
            tmp++;

            if (j + 2 <= n - 1 && d[j + 2] == val) {
                int k = *startPos.upper_bound(j + 2);
                // 区间 [i, k)
                assert(k <= n && d[k - 1] == val);
                tmp = k - i;
            }
        }
        ans = max(ans, tmp);
    }
    return ans + 1;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        int ans1 = solve();
        reverse(a + 1, a + 1 + n);
        int ans2 = solve();
        printf("Case #%d: %d\n", i, max(ans1, ans2));
    }
    return 0;
}
