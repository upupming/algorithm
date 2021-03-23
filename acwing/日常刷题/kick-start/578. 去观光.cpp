/*
题目比较复杂，就是一个 DP 问题，城市数量 N 比较小，但是时刻比较大，需要使用 N 来作为 DP 的状态
状态表示：
f[i][j] 所有在 1~i 中观光 j 个城市的方案的集合
属性：
所有方案所用的时间的最小值
状态计算：
考虑第 i 个城市观不观光：
观光：f[i-1][j-1] + 通勤时间 + 观光时间 Ts
不观光：f[i-1][j] + 通勤时间
通勤时间计算：
s[i-1] + x f[i-1] >= t
x = (t-s[i-1])/f[i-1] 向上取整

答案就是 f[n][k] <= tf 的最大的 k
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 2010;
typedef long long LL;

int n, ts, tf;
LL f[N][N];
struct Bus {
    int s, f, d;
} bus[N];

// t 时刻开始在 i-1 等车，到达 i 的时候是什么时间
LL get_off(int t, int i) {
    auto b = bus[i - 1];
    int x = (t - b.s + b.f - 1) / b.f;
    x = max(x, 0);

    LL go_on_t = b.s + (LL)x * b.f;
    // 上车时间 + 通勤时间 = 到达时间
    return go_on_t + b.d;
}

int solve() {
    cin >> n >> ts >> tf;
    for (int i = 1; i < n; i++) {
        cin >> bus[i].s >> bus[i].f >> bus[i].d;
    }
    memset(f, 0x3f, sizeof f);
    f[1][0] = 0, f[1][1] = ts;

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            // 不观光 i
            f[i][j] = get_off(f[i - 1][j], i);
            // 观光 i
            if (i < n) f[i][j] = min(f[i][j], get_off(f[i - 1][j - 1], i) + ts);
        }
    }

    int k = n - 1;
    while (k >= 0 && f[n][k] > tf) k--;
    return k;
}

int t;
int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int ans = solve();
        printf("Case #%d: %s\n", i, ans < 0 ? "IMPOSSIBLE" : to_string(ans).c_str());
    }
    return 0;
}
