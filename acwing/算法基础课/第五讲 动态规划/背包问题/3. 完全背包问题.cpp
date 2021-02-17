/*
f[i][j]:前i个物品，背包容量j下的最大价值

第 i 个物品选 k 个，k = 0, 1, ...
f[i-1][j-k*v[i]]+k*w[i]

朴素的做法时间复杂度为 O(NM*M) = O(NM^2)
观察：
f[i][j]   = max(f[i-1][j], f[i-1][j-v]+w, f[i-1][j-2v]+2w, ...)
f[i][j-v] =            max(f[i-1][j-v], f[i-1][j-2v]+w, f[i-1][j-3v]+2w, ...)
发现：
f[i][j] = max(f[i-1][j], f[i][j-v]+w)
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
