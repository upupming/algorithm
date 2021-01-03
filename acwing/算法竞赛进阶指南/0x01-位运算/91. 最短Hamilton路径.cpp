#include <cstring>
#include <iostream>
using namespace std;

// f[i][j] 表示 i 表示的二进制位的所有节点已经被访问，现在在节点 j 处
int n, a[25][25], f[1 << 20][25];
int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];

    memset(f, 0x3f, sizeof(f));
    // 从节点 0 开始，只有节点 0 被访问了
    f[1][0] = 0;
    // 逐渐访问全部的节点
    for (int i = 1; i < 1 << n; i++) {
        for (int j = 0; j < n; j++)
            // 当前所在的节点
            // i 的第 j 位必须为 1，否则不可能出现这种情况
            if (i >> j & 1)
                // 中间所有可能的连接点
                for (int k = 0; k < n; k++)
                    // k 必须满足第 k 位为 1，肯定也不是第 j 位
                    // 下面这句与这个等价：if ((i ^ 1 << j) >> k & 1)
                    if (k != j && i >> k & 1)
                        f[i][j] = min(f[i][j], f[i ^ 1 << j][k] + a[k][j]);
    }
    cout << f[(1 << n) - 1][n - 1] << endl;

    return 0;
}