/*
状态表示和 LCS 和 LIS 类似
状态定义：
f[i][j] 表示 a[1~i] 与 b[1~j] 可以构成的以 b[j] 为结尾的 LCIS 的长度，注意这里是以 b[j] 结尾，但是不一定是以 a[i] 结尾，而是 a[i] 之前所有的数作为结尾的情况都包含
转移：
看一下 a[i] 是否包含在公共子序列中
a[i] != b[j]，f[i][j] = f[i-1][j]
a[i] == b[j]，f[i][j] = max(f[i][j], f[i-1][k] + 1)，所有满足条件的 k < j 且 b[k] < a[i]（b[j]）
    意思是：枚举 b 的所有结尾，以 b[k] 结尾与 a[1~i-1] 构成的最长 LCIS 的所有情况（枚举倒数第二个数是什么）

*/

/*
/*
暴力解法：

#include <iostream>
using namespace std;
const int N = 3010;

int f[N][N], n, a[N], b[N];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i] == b[j]) {
                for (int k = 0; k < j; k++) {
                    if (b[k] < a[i])
                        f[i][j] = max(f[i][j], f[i - 1][k] + 1);
                }
            } else {
                f[i][j] = f[i - 1][j];
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, f[n][i]);
    cout << ans << endl;
    return 0;
}

*/
#include <iostream>
using namespace std;
const int N = 3010;

int f[N][N], n, a[N], b[N];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    for (int i = 1; i <= n; i++) {
        // val 是决策集合 (si, sj) 中 f[i-1][k] 的最大值
        int val = 0;
        for (int j = 1; j <= n; j++) {
            if (a[i] == b[j]) {
                f[i][j] = val + 1;
            } else {
                f[i][j] = f[i - 1][j];
            }
            if (b[j] < a[i]) {
                // j 即将增大为 j+1，检查 j 能否进入新的决策集合
                val = max(val, f[i - 1][j]);
            }
        }
    }
    int ans = 0;
    for (int j = 1; j <= n; j++) ans = max(ans, f[n][j]);
    cout << ans << endl;
    return 0;
}
