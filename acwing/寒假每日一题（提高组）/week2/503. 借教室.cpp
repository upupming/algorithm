/*
输出第一个不能满足的订单
二分：一份订单不能满足，他后面的订单也全都无法满足
快速判断某个点前面所有的订单能否满足，每次将一个区间减去或者加上某个数
可以用差分来做

线段树只能处理 2 * 10^5，用线段树会超时（常数较大）
*/
#include <iostream>
using namespace std;
const int N = 1e6 + 10;

int n, m;
int r[N], d[N], s[N], t[N];
int b[N];
bool valid(int mid) {
    // 求差分数组
    for (int i = 1; i <= n; i++)
        b[i] = r[i] - r[i - 1];
    for (int i = 1; i <= mid; i++) {
        b[s[i]] -= d[i];
        b[t[i] + 1] += d[i];
    }
    for (int i = 1; i <= n; i++) {
        b[i] += b[i - 1];
        if (b[i] < 0) return false;
    }
    return true;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> r[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> d[i] >> s[i] >> t[i];
    }
    int l = 1, r = m;
    while (l < r) {
        int mid = l + r >> 1;
        if (valid(mid))
            l = mid + 1;
        else
            r = mid;
    }
    if (valid(m))
        puts("0");
    else
        cout << -1 << endl
             << r << endl;
    return 0;
}