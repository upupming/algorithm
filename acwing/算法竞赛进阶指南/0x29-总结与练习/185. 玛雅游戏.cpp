/*
每一步枚举操作哪一个格子（7 * 5），再枚举像哪个方向移动，最多只需要枚举 5 步（题目要求）
剪枝 1：如果某种颜色只有1个或2个小方块，则直接回溯
剪枝 2：枚举向左移动时，如果左边有方块，则直接回溯
    因为 (x, y, -1) 和 (x-1, y, 1) 是等价的移动，但是 (x-1, y, 1) 字典序更小
*/
#include <cstring>
#include <iostream>
using namespace std;

struct Path {
    int x, y, d;
} path[5];
int n, cnt[11], g[5][7], st[5][7];
void move(int a, int b, int c) {
    swap(g[a][b], g[c][b]);

    while (true) {
        // true 表示不再有连续 3 个可以消除的
        bool flag = true;
        // 处理悬空方格
        for (int x = 0; x < 5; x++) {
            int z = 0;
            for (int y = 0; y < 7; y++) {
                // 把原来的列上的所有方格（可能悬空）从下往上重新排到列上
                if (g[x][y])
                    g[x][z++] = g[x][y];
            }
            while (z < 7) g[x][z++] = 0;
        }

        // st[x][y] = true 表示这个地方可被消除
        memset(st, 0, sizeof st);
        // 遍历所有坐标，看是不是在 3 个一行或 3 个一列的区域，设置 st
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 7; y++) {
                if (g[x][y]) {
                    // 向左、向右能够延伸到的最远区域
                    int l = x, r = x;
                    while (l - 1 >= 0 &&
                           g[l - 1][y] == g[x][y]) l--;
                    while (r + 1 < 5 &&
                           g[r + 1][y] == g[x][y]) r++;
                    if (r - l + 1 >= 3) {
                        st[x][y] = true;
                        flag = false;
                    } else {
                        l = r = y;
                        // 向上、向下能够延伸到的最远区域
                        while (l - 1 >= 0 &&
                               g[x][l - 1] == g[x][y]) l--;
                        while (r + 1 < 7 &&
                               g[x][r + 1] == g[x][y]) r++;
                        if (r - l + 1 >= 3) {
                            st[x][y] = true;
                            flag = false;
                        }
                    }
                }
            }
        }

        if (flag) break;
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 7; y++) {
                if (st[x][y]) {
                    cnt[0]--;
                    cnt[g[x][y]]--;
                    g[x][y] = 0;
                }
            }
        }
    }
}
// u 表示之前已经移动过的步数
bool dfs(int u) {
    // n 步正好所有格子全部消失就返回 true
    if (u == n) return !cnt[0];
    for (int i = 0; i < 10; i++) {
        // 剪枝 1
        if (cnt[i] == 1 || cnt[i] == 2)
            return false;
    }
    int bg[5][7], bcnt[11];
    memcpy(bg, g, sizeof(g));
    memcpy(bcnt, cnt, sizeof(cnt));
    // 枚举所有列
    for (int x = 0; x < 5; x++) {
        // 枚举所有行
        for (int y = 0; y < 7; y++) {
            // 如果这个位置有方格，那么枚举所有方向
            if (g[x][y]) {
                // 向右移动
                int nx = x + 1;
                if (nx < 5) {
                    path[u] = {x, y, 1};
                    move(x, y, nx);
                    if (dfs(u + 1)) return true;
                    // 还原现场
                    memcpy(g, bg, sizeof(g));
                    memcpy(cnt, bcnt, sizeof(cnt));
                }

                // 向左移动
                nx = x - 1;
                // 剪枝 2
                if (nx >= 0 && !g[nx][y]) {
                    path[u] = {x, y, -1};
                    move(x, y, nx);
                    if (dfs(u + 1)) return true;
                    // 还原现场
                    memcpy(g, bg, sizeof(g));
                    memcpy(cnt, bcnt, sizeof(cnt));
                }
            }
        }
    }
    return false;
}
int main() {
    cin >> n;
    // 每一列
    for (int x = 0; x < 5; x++) {
        int t, y = 0;
        while (cin >> t && t) {
            // 所有颜色的格子的总个数
            cnt[0]++;
            // 颜色为 t 的格子的总个数
            cnt[t]++;
            g[x][y++] = t;
        }
    }
    if (dfs(0)) {
        for (int i = 0; i < n; i++) {
            cout << path[i].x << " " << path[i].y << " " << path[i].d << endl;
        }
    } else {
        puts("-1");
    }
    return 0;
}