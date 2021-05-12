/*
最长上升子序列问题
状态表示:
f[i][j]:
    集合: 只考虑前 i 个数，共删除了 j 个数且保留了第 i 个数的所有方案的集合
    属性: 最大收益
状态计算:
    倒数第 2 个数是第 u 个数，中间一共删除了 [u+1, i-1]，那么剩下的最优方案就是 f[u][j-(i-u-1)]，需要再加上 w[a_u][a_i]
利用反证法可证明第 1 个数和最后一个数一定会保留，可以省去边界判断
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 210;

int a[N], w[N][N], f[N][N], n, m, k;
int main() {
    cin >> n >> k >> m;
    for (int i = 1; i <= m; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> w[i][j];
        }
    }
    memset(f, -1, sizeof f);
    f[1][0] = 0;
    for (int i = 2; i <= m; i++) {
        for (int j = 0; j <= k && j <= i; j++) {
            for (int u = 0; u <= i - 1; u++) {
                if (j - (i - u - 1) >= 0)
                    f[i][j] = max(
                        f[i][j],
                        f[u][j - (i - u - 1)] + w[a[u]][a[i]]);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= k; i++) ans = max(ans, f[m][i]);
    cout << ans << endl;
    return 0;
}
