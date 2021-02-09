/*
0-1背包
f[i][j]：前i个物品，背包容量j下的最大价值
选与不选第i个物品
选：f[i][j] = f[i-1][j-v[i]] + w[i]
不选：f[i][j] = f[i-1][j]
初始化：f[0][0] = 0
*/
#include <iostream>
using namespace std;
const int N = 3e4 + 10;
const int M = 30;

int n, m, v[M], p[M], f[M][N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> v[i] >> p[i];
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            f[i][j] = f[i - 1][j];
            if (j >= v[i])
                f[i][j] = max(
                    f[i][j],
                    f[i - 1][j - v[i]] + p[i] * v[i]);
        }
    }
    cout << f[m][n];
    return 0;
}