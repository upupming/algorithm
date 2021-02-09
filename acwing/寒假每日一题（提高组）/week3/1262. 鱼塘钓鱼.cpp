/*
在每个鱼塘钓的鱼的数量只取决于总时间
1. 枚举最远钓到的鱼塘，总钓鱼时间 t3 = 总时间 t1 - 在路上走的时间 t2
2. 取所有可能的鱼塘中中最大的 t3 个数即可（多路归并）
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 110;

// 首项, 公差, 距离
int a[N], d[N], l[N], spend[N], n, t;
// 获取第 k 个等差数列的下一项
int get(int k) {
    return max(0, a[k] - d[k] * spend[k]);
}
int work(int n, int cnt) {
    int ans = 0;
    memset(spend, 0, sizeof spend);
    // 拿出 cnt 个最大的数来
    for (int i = 0; i < cnt; i++) {
        int t = 1;
        for (int j = 1; j <= n; j++) {
            if (get(j) > get(t)) t = j;
        }
        ans += get(t);
        // spend 表示已经用去的项
        spend[t]++;
    }
    return ans;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> d[i];
    for (int i = 2; i <= n; i++) {
        cin >> l[i];
        l[i] += l[i - 1];
    }
    cin >> t;
    int ans = 0;
    // 枚举最远钓到的鱼塘
    for (int i = 1; i <= n; i++) {
        ans = max(ans, work(i, t - l[i]));
    }
    cout << ans << endl;
    return 0;
}