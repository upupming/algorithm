/*
任何地区都不能连续七天或以上时间都不降雨。
在赶集和过节不允许降雨

如果可以保证整个时间段内，该下雨的地方下雨，不该下的地方不下，则输出1
如果不能保证则输出0，每个结果占一行。

性质：
1. 由于方格的大小固定为 4 * 4，而且云不能移出方格，所以只需要 4 个角落满足不连续 7 天无降雨，其他地方也一定满足不连续 7 天无降雨。

f(v 当前第几天, x, y, s0, s1, s2, s3)
(x, y): 云左上角的位置
(s0, s1, s2, s3): 四个角落格子连续几天没有下雨了
起点状态：f(1, 1, 1, 1, 1, 1, 1)（4个顶点都没有下雨）
终点状态：f(n, ...任意) 表示可以撑到第 n 天

状态数：365 * 9 * 7^4 = 10^6
算上转移：10^7
bfs 可以减少有效状态数
*/
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 400;

int n, g[N][4][4];
bool visited[N][3][3][7][7][7][7];
struct P {
    int day, x, y, s0, s1, s2, s3;
};
int dx[] = {-1, 0, 1, 0, 0}, dy[] = {0, 1, 0, -1, 0};
int bfs() {
    // 如果第 0 天就无法满足，直接返回 0
    if (g[0][1][1] || g[0][1][2] || g[0][2][1] || g[0][2][2])
        return 0;
    queue<P> q;
    memset(visited, 0, sizeof visited);
    q.push({1, 1, 1, 1, 1, 1, 1});
    visited[1][1][1][1][1][1][1] = true;

    while (q.size()) {
        auto now = q.front();
        q.pop();

        if (now.day == n) return 1;
        for (int i = 0; i < 5; i++) {
            for (int j = 1; j <= 2; j++) {
                int x = now.x + dx[i] * j;
                int y = now.y + dy[i] * j;
                // 越界
                if (x < 0 || x >= 3 || y < 0 || y >= 3)
                    continue;
                // 注意下一天是第 now.day + 1 天，但是下标索引是 now.day
                auto& s = g[now.day];
                // 不允许降雨
                if (s[x][y] || s[x][y + 1] || s[x + 1][y] || s[x + 1][y + 1])
                    continue;

                int s0 = now.s0, s1 = now.s1, s2 = now.s2, s3 = now.s3;
                if (x == 0 && y == 0)
                    s0 = 0;
                else if (++s0 == 7)
                    continue;
                if (x == 0 && y == 2)
                    s1 = 0;
                else if (++s1 == 7)
                    continue;
                if (x == 2 && y == 0)
                    s2 = 0;
                else if (++s2 == 7)
                    continue;
                if (x == 2 && y == 2)
                    s3 = 0;
                else if (++s3 == 7)
                    continue;

                if (visited[now.day + 1][x][y][s0][s1][s2][s3])
                    continue;
                visited[now.day + 1][x][y][s0][s1][s2][s3] = true;
                q.push({now.day + 1, x, y, s0, s1, s2, s3});
            }
        }
    }
    return 0;
}
int main() {
    while (cin >> n && n) {
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    cin >> g[k][i][j];
                }
            }
        }

        cout << bfs() << endl;
    }
    return 0;
}