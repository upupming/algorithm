/*
「凸」的定义有点迷，直接按照题目的左右边界递增递减性质判断即可
状态表示:
f[i][j][l][r][x][y]:
    集合: 所有选完前 i 行，且一共选择了 j 个格子，且第 i 行选择的左边界是 l，右边界是 r，且左边界的递增/递减状态是 x，右边界的递增/递减状态是 y。
        递增递减状态是一个状态机模型，例如 x 在递减状态，合法的转换只能是变成递减状态
        对于 x: 递减只能由递减状态转移而来
        对于 y: 递增只能由递增状态转移而来
        x, y 统一规定: 1 表示递减，0 表示递增
    属性: max
状态计算:

f[i][j][l][r][1][0]:
x = 1 表示左边递减 (扩张)，y = 0 表示右边递增 (扩张)
将这个集合按照上一个状态进行分情况讨论:
对于左边界而言，上一个状态只能是递减 (1)
对于右边界而言，上一个状态只能是递增 (0)
f[i-1, j-(r-l+1), p, q, 1, 0], 其中 l <= p <= q <= r
f[i-1, j-(r-l+1), p, q, 1, 0] + (w[i, l] + ... + w[i, r])

---

f[i][j][l][r][1][1]:
x = 1 表示左边递减 (扩张)，y = 0 表示右边递减 (收缩)
l <= p <= r <= q (画下示意图就出来了)
        |-> 注意这里是因为上下两行必须是连通的
可由 (x, y) = (1, 1) 和 (1, 0) 转移过来
---
x = 0 左收缩, y = 0 右扩张
p <= l <= q <= r
可由 (x, y) = (0, 0) 和 (1, 0) 转移过来
---
x = 0 左收缩, y = 1 右收缩
p <= l <= r <= q
可由 (x, y) = (0, 1) 和 (0, 0) 和 (1, 0) 和 (1, 1)
转移过来

最后还需要求方案，需要记录从哪里来的
*/
#include <iostream>
using namespace std;
const int N = 16;

int n, m, k;
int w[N][N];
int f[N][N * N][N][N][2][2];

// 表示当前状态从哪个状态过来的
struct State {
    int i, j, l, r, x, y;
} g[N][N * N][N][N][2][2];

int main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> w[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            for (int l = 1; l <= m; l++) {
                for (int r = l; r <= m; r++) {
                    // 总共可以填的个数小于当前行的数量，是不可能的，相当于一个剪枝，避免后面的下标索引出现负数
                    if (j < r - l + 1) continue;

                    // 左扩张，右扩张 (x, y) = (1, 0)
                    {
                        auto &vf = f[i][j][l][r][1][0];
                        auto &vg = g[i][j][l][r][1][0];
                        // l <= p <= q <= r
                        for (int p = l; p <= r; p++) {
                            for (int q = p; q <= r; q++) {
                                int val = f[i - 1][j - (r - l + 1)][p][q][1][0];
                                if (vf < val) {
                                    vf = val;
                                    vg = {i - 1,
                                          j - (r - l + 1), p, q, 1, 0};
                                }
                            }
                        }
                        for (int u = l; u <= r; u++) vf += w[i][u];
                    }
                    // 左扩张，右收缩 (x, y) = (1, 1)
                    {
                        auto &vf = f[i][j][l][r][1][1];
                        auto &vg = g[i][j][l][r][1][1];
                        // l <= p <= r <= q
                        for (int p = l; p <= r; p++) {
                            for (int q = r; q <= m; q++) {
                                for (int y = 0; y <= 1; y++) {
                                    int val = f[i - 1][j - (r - l + 1)][p][q][1][y];
                                    if (vf < val) {
                                        vf = val;
                                        vg = {i - 1,
                                              j - (r - l + 1), p, q, 1, y};
                                    }
                                }
                            }
                        }
                        for (int u = l; u <= r; u++) vf += w[i][u];
                    }
                    // 左收缩，右扩张 (x, y) = (0, 0)
                    {
                        auto &vf = f[i][j][l][r][0][0];
                        auto &vg = g[i][j][l][r][0][0];
                        //p <= l <= q <= r
                        for (int p = 1; p <= l; p++) {
                            for (int q = l; q <= r; q++) {
                                for (int x = 0; x <= 1; x++) {
                                    int val = f[i - 1][j - (r - l + 1)][p][q][x][0];
                                    if (vf < val) {
                                        vf = val;
                                        vg = {i - 1,
                                              j - (r - l + 1), p, q, x, 0};
                                    }
                                }
                            }
                        }
                        for (int u = l; u <= r; u++) vf += w[i][u];
                    }
                    // 左收缩，右收缩 (x, y) = (0, 1)
                    {
                        auto &vf = f[i][j][l][r][0][1];
                        auto &vg = g[i][j][l][r][0][1];
                        // p <= l <= r <= q
                        for (int p = 1; p <= l; p++) {
                            for (int q = r; q <= m; q++) {
                                for (int x = 0; x <= 1; x++) {
                                    for (int y = 0; y <= 1; y++) {
                                        int val = f[i - 1][j - (r - l + 1)][p][q][x][y];
                                        if (vf < val) {
                                            vf = val;
                                            vg = {i - 1,
                                                  j - (r - l + 1), p, q, x, y};
                                        }
                                    }
                                }
                            }
                        }
                        for (int u = l; u <= r; u++) vf += w[i][u];
                    }
                }
            }
        }
    }

    int ans = 0;
    State state;
    for (int i = 1; i <= n; i++) {
        for (int l = 1; l <= m; l++) {
            for (int r = 1; r <= m; r++) {
                for (int x = 0; x <= 1; x++) {
                    for (int y = 0; y <= 1; y++) {
                        int val = f[i][k][l][r][x][y];
                        if (ans < val) {
                            ans = val;
                            state = {i, k, l, r, x, y};
                        }
                    }
                }
            }
        }
    }
    printf("Oil : %d\n", ans);
    while (state.j) {
        for (int i = state.l; i <= state.r; i++) printf("%d %d\n", state.i, i);
        state = g[state.i][state.j][state.l][state.r][state.x][state.y];
    }

    return 0;
}
