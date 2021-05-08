#include <bits/stdc++.h>
using namespace std;

// 记忆化搜索所需要的数组，表示 f[cx][cy][mx][my][k] 下是老鼠赢(1) 还是猫赢 (0), -1 表示未初始化
// 维度分别为 猫的坐标、老鼠坐标、所走步数，步数超过 200 就可以认为是死循环了，可以提前返回
// 总共元素个数为 8 * 10*5
int f[8][8][8][8][200];
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

class Solution {
   public:
    vector<string> g;
    int n, m, cj, mj;

    int dp(int cx, int cy, int mx, int my, int k) {
        // 步数超过 200，可以认为是死循环了，猫赢
        if (k >= 200) return 0;
        auto& v = f[cx][cy][mx][my][k];
        if (v != -1) return v;

        // 猫走
        if (k & 1) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j <= cj; j++) {
                    int x = cx + dx[i] * j, y = cy + dy[i] * j;
                    if (x < 0 || x >= n || y < 0 || y >= m || g[x][y] == '#') break;
                    // 有一个状态赢，那么必赢
                    if (x == mx && y == my) return v = 0;
                    if (g[x][y] == 'F') return v = 0;
                    if (dp(x, y, mx, my, k + 1) == 0) return v = 0;
                }
            }
            // 不管怎么走都不能赢，那么必输
            return v = 1;
        } else {  // 老鼠走
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j <= mj; j++) {
                    int x = mx + dx[i] * j, y = my + dy[i] * j;
                    if (x < 0 || x >= n || y < 0 || y >= m || g[x][y] == '#') break;
                    // 有一个状态赢，那么必赢
                    if (g[x][y] == 'F') return v = 1;
                    if (dp(cx, cy, x, y, k + 1) == 1) return v = 1;
                }
            }
            // 不管怎么走都不能赢，那么必输
            return v = 0;
        }
    }

    bool canMouseWin(vector<string>& grid, int catJump, int mouseJump) {
        g = grid;
        n = g.size(), m = g[0].size(), cj = catJump, mj = mouseJump;
        int cx, cy, mx, my;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] == 'C')
                    cx = i, cy = j;
                else if (g[i][j] == 'M')
                    mx = i, my = j;
            }
        }
        memset(f, -1, sizeof f);
        return dp(cx, cy, mx, my, 0);
    }
};
