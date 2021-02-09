/*
w 越大，y 月越小，因此可以二分
先预处理所有满足 w 要求的前缀和，然后对于每个区间能够快速返回答案
*/
#include <iostream>
using namespace std;
const int N = 2e5 + 10;
typedef long long LL;

int n, m, w[N], v[N], l[N], r[N], cnt[N];
LL s, sum[N];
LL get_y(int mid) {
    // 预处理前缀和
    for (int i = 1; i <= n; i++) {
        cnt[i] = cnt[i - 1] + (w[i] >= mid);
        sum[i] = sum[i - 1] + (w[i] >= mid ? v[i] : 0);
    }
    // 求所有区间的 Y 值之和
    LL y = 0;
    for (int i = 1; i <= m; i++) {
        y += (cnt[r[i]] - cnt[l[i] - 1]) *
             (sum[r[i]] - sum[l[i] - 1]);
    }
    return y;
}
int main() {
    cin >> n >> m >> s;
    int mw = 0;
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> v[i];
        mw = max(w[i], mw);
    }
    for (int i = 1; i <= m; i++) {
        cin >> l[i] >> r[i];
    }
    // 可能全都不选，所以 r = mw + 1
    int l = 1, r = mw + 1;
    // cout << a << " " << b << endl;
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if (get_y(mid) < s)
            r = mid - 1;
        else
            l = mid;
    }
    // 两个候选值：小于 s 的最大值和大于等于 s 的最小值
    cout << min(abs(get_y(l) - s), abs(get_y(l + 1) - s)) << endl;

    return 0;
}