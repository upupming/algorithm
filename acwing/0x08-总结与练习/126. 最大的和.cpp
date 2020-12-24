/*
一维情况：f[i] 表示以 a[i] 结尾的最大和子串的和
若 f[i-1] > 0，f[i] = f[i-1] + a[i]，否则 f[i] = a[i]
二维情况：
暴力枚举起点和终点的行，然后在这些行上应用一维解法即可

O(n^3)
*/

#include <iostream>
using namespace std;

int n, a[110][110], s[110][110], f[110];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
        }
    }

    // 下标不要搞错了，是 1 开始
    int ans = a[1][1];
    for (int i1 = 1; i1 <= n; i1++) {
        for (int i2 = i1; i2 <= n; i2++) {
            // 行固定在 i1 - i2 之间的一维问题
            // 左上角坐标 (i1-1, j-1)，右下角坐标 (i2, j)
            // 注意左上角是第一个不能到的点，右下角是最后一个可以到的点，这个套路要熟悉
            int j = 1;
            f[1] = s[i2][j] - s[i2][j - 1] - s[i1 - 1][j] + s[i1 - 1][j - 1];
            // cout << i1 << " " << i2 << " " << f[1] << endl;
            for (j = 2; j <= n; j++) {
                int cur = s[i2][j] - s[i2][j - 1] - s[i1 - 1][j] + s[i1 - 1][j - 1];
                if (f[j - 1] > 0) {
                    f[j] = f[j - 1] + cur;
                } else {
                    f[j] = cur;
                }
                ans = max(ans, f[j]);
                // cout << j << ", " << f[j] << ", " << ans << endl;
            }
        }
    }
    cout << ans << endl;
    return 0;
}