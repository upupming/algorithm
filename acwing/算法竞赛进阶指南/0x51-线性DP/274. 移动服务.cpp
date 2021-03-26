/*
f[i][x][y]
表示已经完成前 i 个请求，有一个在位置 p[i]，另外两个在 x, y 的情况
注意 p[i], x, y 必须是不相等的（不能有两个服务员在同一个位置）
属性：最小花费
*/
#include <cstring>
#include <iostream>
using namespace std;
const int L = 210, N = 1010;

int c[L][L], p[N], n, l, f[N][L][L];

bool ok(int i, int j, int k) {
    return p[i] != j && j != k && p[i] != k;
}

int main() {
    memset(f, 0x3f, sizeof f);
    cin >> l >> n;
    for (int i = 1; i <= l; i++) {
        for (int j = 1; j <= l; j++) {
            cin >> c[i][j];
        }
    }
    for (int i = 1; i <= n; i++) cin >> p[i];
    // 没有完成任何请求，服务员分别在 3, 1, 2 这三个位置
    p[0] = 3, f[0][1][2] = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 1; j <= l; j++) {
            for (int k = 1; k <= l; k++) {
                if (!ok(i, j, k)) continue;
                // cout << i << " " << j << " " << k << " " << f[i][j][k] << endl;
                // p[i] 位置的服务员移动到 p[i+1]
                if (ok(i + 1, j, k)) {
                    f[i + 1][j][k] = min(
                        f[i + 1][j][k],
                        f[i][j][k] + c[p[i]][p[i + 1]]);
                    // cout << f[i + 1][j][k] << endl;
                    // if (f[i + 1][j][k] == 0) return 0;
                }
                // j 位置的服务员移动到 i+1
                if (ok(i + 1, p[i], k)) {
                    f[i + 1][p[i]][k] = min(
                        f[i + 1][p[i]][k],
                        f[i][j][k] + c[j][p[i + 1]]);
                    // cout << f[i + 1][p[i]][k] << endl;
                    // if (f[i + 1][p[i]][k] == 0) return 0;
                }
                // k 位置的服务员移动到 i+1
                if (ok(i + 1, j, p[i])) {
                    f[i + 1][j][p[i]] = min(
                        f[i + 1][j][p[i]],
                        f[i][j][k] + c[k][p[i + 1]]);
                    // cout << f[i + 1][j][p[i]] << endl;
                    // if (f[i + 1][j][p[i]] == 0) return 0;
                }
            }
        }
    }
    int ans = 0x3f3f3f3f;
    for (int j = 1; j <= l; j++) {
        for (int k = 1; k <= l; k++) {
            ans = min(ans, f[n][j][k]);
        }
    }
    cout << ans << endl;
    return 0;
}
