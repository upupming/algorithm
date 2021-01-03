/*
广度优先搜索
*/
#include <iostream>
#include <queue>
using namespace std;

struct rec {
    // lie = 0 表示长方体立在 (x, y)
    // lie = 1 表示长方体横着躺着，左半部分位置在 (x, y)
    // lie = 2 表示长方体竖着躺着，上半部分位置在 (x, y)
    int x, y, lie;
};
// 地图
char s[510][510];
// 起始状态和目标状态
rec st, ed;
// d 记录最少步数
int n, m, d[510][510][3];
// 四个不同方向
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

// 坐标在矩形区域内
bool valid(int x, int y) { return x >= 1 && x <= n && y >= 1 && y <= m; }
// 滚动是否合法
bool valid(rec next) {
    if (!valid(next.x, next.y)) return false;
    if (s[next.x][next.y] == '#') return false;
    if (next.lie == 0 && s[next.x][next.y] != '.') return false;
    if (next.lie == 1 && s[next.x][next.y + 1] == '#') return false;
    if (next.lie == 2 && s[next.x + 1][next.y] == '#') return false;
    return true;
}
// 计算起点和终点
void parse_st_ed() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == 'O')
                ed = {i, j, 0}, s[i][j] = '.';
            else if (s[i][j] == 'X') {
                // 看看能不能构成两个 X
                for (int k = 0; k < 4; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    if (valid(x, y) && s[x][y] == 'X') {
                        st = {min(i, x), min(j, y), k < 2 ? 1 : 2};
                        s[i][j] = s[x][y] = '.';
                        break;
                    }
                }
                if (s[i][j] == 'X') st = {i, j, 0};
            }
        }
    }
}
// 3 个不同 lie 情况（0, 1, 2，立, 横, 竖）下，朝上、右、下、左滚动后的坐标变化
const int next_x[3][4] = {
    {-2, 0, 1, 0},
    {-1, 0, 1, 0},
    {-1, 0, 2, 0}};
const int next_y[3][4] = {
    {0, 1, 0, -2},
    {0, 2, 0, -1},
    {0, 1, 0, -1}};
const int next_lie[3][4] = {
    {2, 1, 2, 1},
    {1, 0, 1, 0},
    {0, 2, 0, 2}};
int bfs() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // 3 种 lie 状态
            for (int k = 0; k < 3; k++) {
                d[i][j][k] = -1;
            }
        }
    }
    queue<rec> q;
    d[st.x][st.y][st.lie] = 0;
    q.push(st);
    while (q.size()) {
        rec now = q.front();
        q.pop();

        // 4 个方向滚动
        for (int i = 0; i < 4; i++) {
            rec next;
            next.x = now.x + next_x[now.lie][i];
            next.y = now.y + next_y[now.lie][i];
            next.lie = next_lie[now.lie][i];
            if (!valid(next)) continue;

            if (d[next.x][next.y][next.lie] == -1) {
                d[next.x][next.y][next.lie] =
                    d[now.x][now.y][now.lie] + 1;
                q.push(next);
                // 到达目标，广搜按照入队的选后顺序有层次单调性，第一次被入队时，就得到了从起始状态到达该状态的最少步数
                if (next.x == ed.x && next.y == ed.y && next.lie == ed.lie) return d[next.x][next.y][next.lie];
            }
        }
    }
    // 无解
    return -1;
}
int main() {
    while (cin >> n >> m, n || m) {
        for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
        parse_st_ed();
        int ans = bfs();
        if (ans == -1)
            puts("Impossible");
        else
            cout << ans << endl;
    }
    return 0;
}