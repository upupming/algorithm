/*
f[i][j] 表示前 i 个数，和是 j 的方案总数
0/1 背包
*/
#include <iostream>
using namespace std;
const int N = 110, M = 1e4 + 10;

int a[N], f[M], n, m;
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= a[i]; j--) {
            f[j] += f[j - a[i]];
        }
    }
    cout << f[m] << endl;
    return 0;
}
