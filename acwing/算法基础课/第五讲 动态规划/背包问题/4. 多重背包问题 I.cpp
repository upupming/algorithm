/*
跟完全背包问题一样，但是只是多了一个第 i 种物品最多有 s[i] 件的限制

首先考虑暴力实现，时间复杂度为 O(NVS)

第 i 个物品选 k 个，k = 0, 1, ..., s[i]
f[i-1][j-k*v[i]]+k*w[i]
*/
#include <iostream>
using namespace std;
const int N = 110;

int f[N], v[N], w[N], s[N], n, m;
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> v[i] >> w[i] >> s[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 0; j--) {
            for (int k = 0; k <= s[i] && j >= k * v[i]; k++) {
                f[j] = max(f[j], f[j - k * v[i]] + k * w[i]);
            }
        }
    }
    cout << f[m] << endl;
    return 0;
}
