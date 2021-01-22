/*
完全背包

f[i][j]:前i个货币，当前钱数为j下的方案数

选与不选第i个货币
选：f[i-1][j-v[i] * k]
不选：f[i-1][j]
初始化：
f[0][0] = 1
*/
#include <iostream>
using namespace std;
const int N = 10010;

long long n, m, v[N], w[N], g[N];

void loop_optimized() {
    g[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = v[i]; j <= m; j++) {
            g[j] += g[j - v[i]];
        }
    }
    cout << g[m] << endl;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    loop_optimized();

    return 0;
}