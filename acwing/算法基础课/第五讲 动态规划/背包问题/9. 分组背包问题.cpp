/*
同一个组里面的物品只能选一个
对于第 i 组，要么选 0 个物品，要么从组里面所有物品中选择一个

时间复杂度：O(NVS)
*/
#include <iostream>
using namespace std;
const int N = 110;

int n, m;
int v[N][N], w[N][N], s[N];
int f[N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        for (int j = 0; j < s[i]; j++) {
            cin >> v[i][j] >> w[i][j];
        }
    }
    for (int i = 1; i <=n; i++) {
        for (int j = m; j >= 0; j--) {
            // 选 i 组中的第 k 个物品，特殊地，k = 0 表示不选
            for (int k = 0; k < s[i]; k++) {
                if (v[i][k] <= j) {
                    f[j] = max(f[j], f[j-v[i][k]] + w[i][k]);
                }
            }
        }
    }
    cout << f[m] << endl;
    return 0;
}
