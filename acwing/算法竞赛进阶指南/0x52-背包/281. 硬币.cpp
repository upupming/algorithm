/*
多重背包：第 i 种物品有一个数量 C[i] 的限制
1. 把第 i 种物品看作独立的 C[i] 个物品，转化为共有 sum C[i] 个物品的 0/1 背包问题，时间复杂度为 O(M * sum C[i])，效率较低
*/
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 110, M = 1e5 + 10;

int n, m, a[N], c[N], f[M], v[N], w[N], p[N], r[N], used[M];

// 考虑到只需要求可行性的特殊性，我们采用 used 数组优化版本
// O(NM)
int main() {
    while (scanf("%d%d", &n, &m), n || m) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        for (int i = 1; i <= n; i++) {
            scanf("%d", &c[i]);
        }
        // 刚开始都不能拼成
        for (int i = 1; i <= m; i++) {
            f[i] = 0;
        }
        f[0] = 1;
        for (int i = 1; i <= n; i++) {
            // used[j] 表示 f[j] 在阶段 i 时为 true 至少需要用多少枚第 i 种硬币，尽量选择书中的第一类情况
            for (int j = 0; j <= m; j++) used[j] = 0;
            // 注意这是完全背包的循环顺序
            for (int j = a[i]; j <= m; j++) {
                if (!f[j] && f[j - a[i]] && used[j - a[i]] < c[i]) {
                    f[j] = true;
                    used[j] = used[j - a[i]] + 1;
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= m; i++) {
            ans += f[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}

// 二进制拆分法: 被卡时间，需要用单调队列优化
// O(NM log C)
int main_binary() {
    while (scanf("%d%d", &n, &m), n || m) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            v[i] = w[i] = a[i];
        }
        for (int i = 1; i <= n; i++) {
            scanf("%d", &c[i]);
            p[i] = log2(c[i] + 1) - 1;
            r[i] = c[i] - (pow(2, p[i] + 1) - 1);
        }
        // 刚开始都不能拼成
        for (int i = 1; i <= m; i++) {
            f[i] = 0;
        }
        f[0] = 1;
        // 两层循环枚举所有物品
        for (int i = 1; i <= n; i++) {
            for (int j = 1, val = v[i]; j <= p[i] + 2; j++, val *= 2) {
                if (j == p[i] + 2) {
                    val = r[i] * v[i];
                }

                // 枚举背包容量
                for (int k = m; k >= val; k--) {
                    f[k] =
                        // 不选物品 (i, j)，前一阶段必须可以拼成 k
                        f[k] ||
                        // 选物品 (i, j)，前一阶段可以拼成 k-val 就行
                        (f[k - val]);
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= m; i++) {
            ans += f[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}

// 暴力: 转化成 0/1 背包求解
// O(NMC)
int main_naive() {
    while (cin >> n >> m, n && m) {
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            v[i] = w[i] = a[i];
        }
        for (int i = 1; i <= n; i++)
            cin >> c[i];
        // 刚开始都不能拼成
        memset(f, 0, sizeof f);
        f[0] = 1;
        // 两层循环枚举所有物品
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= c[i]; j++) {
                // 枚举背包容量
                for (int k = m; k >= v[i]; k--) {
                    f[k] =
                        // 不选物品 (i, j)，前一阶段必须可以拼成 k
                        f[k] ||
                        // 选物品 (i, j)，前一阶段可以拼成 k-v[i] 就行
                        (f[k - v[i]]);
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= m; i++) {
            ans += f[i];
        }
        cout << ans << endl;
    }
    return 0;
}
