/*
f[i][j] 表示合并 [i, j] 需要多少代价
初始: f[i][i] = 0
转移: f[i][j] = f[i][k] + f[k+1][j] + sum(i, ..., j)
需要先求一个前缀和
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 310;

int n, sum[N], f[N][N];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> sum[i];
        sum[i] += sum[i - 1];
    }
    memset(f, 0x3f, sizeof f);
    for (int i = 1; i <= n; i++) f[i][i] = 0;
    for (int len = 1; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            for (int k = i; k + 1 <= j; k++) {
                f[i][j] = min(
                    f[i][j],
                    f[i][k] + f[k + 1][j] + sum[j] - sum[i - 1]);
            }
        }
    }
    cout << f[1][n] << endl;
    return 0;
}
