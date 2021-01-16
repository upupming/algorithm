/*
区间合并算法：
1. 将所有区间按左端点从小到大排序
2. 从左到右遍历每个区间 [L, R]
    l_i <= R, R = max(R, r_i)
    l_i > R, 将 [L, R] 存下来，令新的 [L, R] 为 [l_i, r_i]
遍历过程是线性的，主要时间花在了排序上
*/
#include <algorithm>
#include <iostream>
using namespace std;
const int M = 110;
typedef pair<int, int> PII;

int l, m;
PII seg[M];
int main() {
    cin >> l >> m;
    for (int i = 0; i < m; i++) cin >> seg[i].first >> seg[i].second;
    sort(seg, seg + m);

    int ans = 0;
    int L = seg[0].first, R = seg[0].second;
    for (int i = 1; i < m; i++) {
        if (seg[i].first <= R)
            R = max(R, seg[i].second);
        else {
            // 将区间长度计算到答案中
            ans += R - L + 1;
            L = seg[i].first, R = seg[i].second;
        }
    }
    ans += R - L + 1;
    // 原来的减去砍掉的等于现存的
    ans = l + 1 - ans;
    cout << ans << endl;
    return 0;
}