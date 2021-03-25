/*
k 元组 (a1, ..., ak) 表示每一行已安排的学生人数，用来描绘「已处理部分」的轮廓
k 元组描绘的轮廓内的合影方案总数就足以构成一个子问题
阶段：(a1, ..., ak)，属性：方案总数
转移：每次对学生的安排

注意，动态规划在转移的过程中，可以看当前状态可由那些状态转移过来，也可看每个状态可以转移到哪个状态，这是两种不同的方法，一般用什么方便就用什么
这道题就是典型的，看每种状态可以转移到什么状态更加简单一点
*/
#include <cstring>
#include <iostream>
using namespace std;
// 这种维度很多的题目，N 尽量不要开得太大，容易 TLE
const int K = 10, N = 35;

int k, n[K];
int main() {
    while (cin >> k && k) {
        memset(n, 0, sizeof n);
        for (int i = 1; i <= k; i++) {
            cin >> n[i];
        }
        // 不在外部初始化，减小数组大小，减小初始化开销
        long long f[n[1] + 1][n[2] + 1][n[3] + 1][n[4] + 1][n[5] + 1];
        memset(f, 0, sizeof f);

        // 一个人都不站，有 1 种方法
        f[0][0][0][0][0] = 1;
        for (int i = 0; i <= n[1]; i++) {
            for (int j = 0; j <= n[2]; j++) {
                for (int k = 0; k <= n[3]; k++) {
                    for (int l = 0; l <= n[4]; l++) {
                        for (int m = 0; m <= n[5]; m++) {
                            if (i < n[1])
                                f[i + 1][j][k][l][m] += f[i][j][k][l][m];
                            if (i > j && j < n[2])
                                f[i][j + 1][k][l][m] += f[i][j][k][l][m];
                            if (j > k && k < n[3])
                                f[i][j][k + 1][l][m] += f[i][j][k][l][m];
                            if (k > l && l < n[4])
                                f[i][j][k][l + 1][m] += f[i][j][k][l][m];
                            if (l > m && m < n[5])
                                f[i][j][k][l][m + 1] += f[i][j][k][l][m];
                        }
                    }
                }
            }
        }
        cout << f[n[1]][n[2]][n[3]][n[4]][n[5]] << endl;
    }

    return 0;
}
