/*
状态表示 f[i][j][k]:
    集合: 所有从前 i 个人中选择 j 个人，且差值是 k (可能为负数, -400~400) 的所有方案的集合
    属性: D+P 最大值
状态计算:
    不选第 i 个人, f[i-1][j][k]
    选第 i 个人，f[i-1][j-1][k-(p_i-d_i)] + (p_i+d_i)
    两个情况取一下 max 即可
*/
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 210, M = 810, base = 400;

int n, m;
int p[N], d[N];
int f[N][21][M];
int ans[N];
int main() {
    int t = 1;
    while (cin >> n >> m, n || m) {
        for (int i = 1; i <= n; i++) cin >> p[i] >> d[i];

        memset(f, -0x3f, sizeof f);
        // 注意 k 可能是负数，加一个 base 的偏移量
        f[0][0][base] = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                for (int k = 0; k < M; k++) {
                    // 不选第 i 个的情况
                    f[i][j][k] = f[i - 1][j][k];
                    int t = k - (p[i] - d[i]);
                    if (t < 0 || t >= M) continue;
                    if (j < 1) continue;
                    f[i][j][k] = max(
                        f[i][j][k],
                        f[i - 1][j - 1][t] + p[i] + d[i]);
                }
            }
        }

        // 差值的绝对值
        int v = 0;
        // 不存在差值为 -v 或者 +v 的方案
        while (f[n][m][base - v] < 0 && f[n][m][base + v] < 0) v++;

        if (f[n][m][base - v] > f[n][m][base + v])
            v = base - v;
        else
            v = base + v;

        int cnt = 0;
        int i = n, j = m, k = v;
        while (j) {
            if (f[i][j][k] == f[i - 1][j][k])
                i--;
            else {
                ans[cnt++] = i;
                k -= (p[i] - d[i]);
                i--, j--;
            }
        }

        int sp = 0, sd = 0;
        for (int i = 0; i < cnt; i++) {
            sp += p[ans[i]];
            sd += d[ans[i]];
        }
        printf("Jury #%d\n", t++);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", sp, sd);

        sort(ans, ans + cnt);
        for (int i = 0; i < cnt; i++) {
            cout << " " << ans[i];
        }
        cout << endl
             << endl;
    }
    return 0;
}
