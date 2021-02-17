/*
f[i][j]: 合并第 i~j 堆的最小总代价
枚举所有的切开方式，先合并 i~k，再合并 k+1~j

时间复杂度：O(N^3)

See also: 479. 加分二叉树
*/
#include <iostream>
using namespace std;
const int N = 310;

int n, a[N], f[N][N], sum[N];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = a[i] + sum[i - 1];
    }

    // len = 1 的代价为 0，无需初始化
    // 枚举区间长度
    for (int len = 2; len <= n; len++) {
        for (int i = 1, j = i + len - 1; i <= n && j <= n; i++, j++) {
            // 枚举所有的合并点
            f[i][j] = 0x3f3f3f3f;
            for (int k = i; k + 1 <= j; k++) {
                f[i][j] = min(
                    f[i][j], f[i][k] + f[k + 1][j] + sum[j] - sum[i - 1]);
            }
            // cout << i << " " << j << " " << f[i][j] << endl;
        }
    }
    cout << f[1][n] << endl;
    return 0;
}
