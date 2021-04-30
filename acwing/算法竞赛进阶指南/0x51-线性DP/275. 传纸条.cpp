/*
集合: 所有从左上到右下，走两遍的方案
属性: max
f[x1][y1][x2][y2]: 第一条路线走到 (x1, y1)，第二条路线走到 (x2, y2)
简化状态表示：
f[k, x1, x2]: k 表示 x1 + y1，也表示 x2 + y2，因为两条路线横纵坐标之和相等，都等于步数
集合：
所有第一条路线从 (1, 1) 走到 (x1, k-x1)，第二条路线从 (1, 1) 走到 (x2, k-x2) 的路线组合的集合
属性：
每个路线组合能取到的结果的最大值
状态计算：
将集合划分成若干个子集，分而治之
f[k, x1, x2] 按照最后一步走法划分成：
1. 第 1 条路线往右走，第 2 条路线往右走: f[k-1, x1, x2]
2. 第 1 条路线往右走，第 2 条路线往下走: f[k-1, x1, x2-1]
3. 第 1 条路线往下走，第 2 条路线往右走: f[k-1, x1-1, x2]
4. 第 1 条路线往下走，第 2 条路线往下走: f[k-1, x1-1, x2-1]
对于每种情况，需要加上一个新的得分 t
*/
#include <iostream>
using namespace std;
const int N = 55;

int n, m;
int g[N][N];
// 初始值为 0
int f[N * 2][N][N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> g[i][j];
        }
    }

    // 时间复杂度 O(n^3)
    for (int k = 2; k <= n + m; k++) {
        // i in [1, n], k-i in  [1, m], so i in [max(1, k-m), min(n, k-1)]
        for (int i = max(1, k - m); i <= min(n, k - 1); i++) {
            for (int j = max(1, k - m); j <= min(n, k - 1); j++) {
                // 枚举四种子集（右右、右下、下右、下下）
                for (int a = 0; a <= 1; a++) {
                    for (int b = 0; b <= 1; b++) {
                        int t = g[i][k - i];
                        // 没有出现冲突、或者是在左上和右下角的话
                        if (i != j || k == 2 || k == n + m) {
                            t += g[j][k - j];
                            f[k][i][j] = max(f[k][i][j], f[k - 1][i - a][j - b] + t);
                        }
                    }
                }
            }
        }
    }

    cout << f[n + m][n][n] << endl;
    return 0;
}
