#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;

typedef long long LL;
#define long long int;

int t;
LL n, c, a[N], b[N], l[N], r[N], m, diffCnt[N], sum[N];
vector<LL> b_i;

// 离散化
void discrete() {
    sort(a + 1, a + 2 * n + 1);
    for (int i = 1; i <= 2 * n; i++) {
        // 也可用 STL 的 unique 函数
        if (i == 1 || a[i] != a[i - 1])
            b[++m] = a[i];
    }
    for (int i = 1; i <= m; i++) {
        b_i.push_back(b[i]);
        if (i < m && b_i.back() + 1 < b[i + 1]) b_i.push_back(b_i.back() + 1);
    }
}
// 查询 x 映射为哪个 1-m 之间的整数
int query(LL x) {
    return lower_bound(b_i.begin(), b_i.end(), x) - b_i.begin();
}

LL solve() {
    cin >> n >> c;
    m = 0, b_i.clear();
    memset(diffCnt, 0, sizeof diffCnt);
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
        a[2 * i - 1] = l[i], a[2 * i] = r[i];
    }
    discrete();
    for (int i = 1; i <= n; i++) {
        int x = query(l[i]), y = query(r[i]);
        // [x+1, y-1] 都 +1
        diffCnt[x + 1]++, diffCnt[y]--;
    }
    sum[0] = diffCnt[0];
    for (int i = 1; i < b_i.size(); i++) {
        sum[i] = sum[i - 1] + diffCnt[i];
    }
    vector<int> idx;
    for (int i = 0; i < b_i.size(); i++) {
        idx.push_back(i);
    }
    sort(idx.begin(), idx.end(), [](auto i, auto j) {
        return sum[i] > sum[j];
    });
    LL ans = n;
    for (int i = 0; i < b_i.size() && c > 0; i++) {
        int j = idx[i] + 1;
        if (j >= b_i.size()) continue;
        LL len = b_i[j];
        len -= b_i[j - 1];

        LL times = min(c, len);
        c -= times;
        ans += sum[j - 1] * times;
    }
    return ans;
}

signed main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}
