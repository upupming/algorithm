/*
f[i][j]:前i个物品，背包容量j下的最大价值

选与不选第i个物品
选：f[i][j] = f[i-1][j-v[i]] + w[i]
不选：f[i][j] = f[i-1][j]
初始化：
f[0][0] = 0
*/
#include <iostream>
using namespace std;
const int N = 1010;

int n, m, v[N], w[N], g[N];

void loop_optimized() {
    for (int i = 1; i <= n; i++) {
        for (int j = v[i]; j <= m; j++) {
            g[j] = max(g[j], g[j - v[i]] + w[i]);
        }
    }
    cout << g[m] << endl;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> v[i] >> w[i];
    }

    loop_optimized();

    return 0;
}