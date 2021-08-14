#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

typedef long long LL;

int t, n, m;
LL c, l[N], r[N], a[4 * N], diff[4 * N], cnt[4 * N];

// 查询 x 映射为哪个 [0, m) 之间的整数
int query(LL x) {
    return lower_bound(a, a + m, x) - a;
}
LL solve() {
    cin >> n >> c;
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        a[4 * i] = l[i], a[4 * i + 1] = r[i];
        a[4 * i + 2] = l[i] + 1, a[4 * i + 3] = r[i] - 1;
    }
    // 离散化
    sort(a, a + 4 * n);
    m = unique(a, a + 4 * n) - a;
    for (int i = 0; i < m; i++) diff[i] = 0;
    // 预处理差分数组
    for (int i = 0; i < n; i++) {
        // 开区间 (L, R) 的覆盖次数都 +1
        diff[query(l[i] + 1)] += 1;
        diff[query(r[i])] -= 1;
    }
    // 差分数组求和得到每个点处的覆盖次数
    cnt[0] = diff[0];
    for (int i = 1; i < m; i++) {
        cnt[i] = cnt[i - 1] + diff[i];
    }
    // 按照覆盖次数从大到小对坐标进行排序
    vector<int> idx;
    for (int i = 0; i < m; i++) idx.push_back(i);
    sort(idx.begin(), idx.end(), [](int i, int j) {
        return cnt[i] > cnt[j];
    });
    LL ans = n;
    // 按照被区间覆盖次数从大到小来切
    for (int i = 0; i < m && c; i++) {
        int j = idx[i];
        if (j + 1 >= m) continue;
        // 左开右闭区间 [a[j], a[j+1])
        LL d = a[j + 1] - a[j];
        // 区间上每个点都可以切 1 次，获得 cnt[j] 个新区间
        LL tmp = min(d, c) * cnt[j];
        ans += tmp, c -= min(d, c);
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}
