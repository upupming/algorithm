/*
每个格子变换之后要么是左斜「/」，要么是右斜「\」
要求最少变换使得左上角能够到达右下角

将电路板上的每个格点看作无向图中的节点，两个节点 x, y 如果是某个小方格的两个对角，则在 x 与 y 之间连边。
若与标准件重合，距离为0，否则距离为1（表示需要旋转一次才能连上）
求出左上角到右下角的最短距离就是答案

双端队列广搜，边权为0的边从队头入队，边权为1的边从队尾入队，任意时刻广搜队列中节点对应距离仍然具有两段性和单调性
每个节点可能入队多次，但是第一次出队就是最短距离
*/
#include <cstring>
#include <deque>
#include <iostream>
using namespace std;
const int N = 510;

int t, r, c;
char s[N][N];
bool v[N][N];
struct P {
    int x, y, steps;
};
int d[2][4] = {
    {1, 1, -1, -1},
    {1, -1, 1, -1},
};
bool valid(int x, int y) {
    return x >= 0 && x <= r && y >= 0 && y <= c;
}
int main() {
    cin >> t;
    while (t--) {
        cin >> r >> c;
        for (int i = 0; i < r; i++) {
            cin >> s[i];
        }
        // BFS
        memset(v, 0, sizeof(v));
        deque<P> q;
        P start = {0, 0, 0};
        q.push_back(start);
        bool ok = false;
        while (q.size()) {
            auto now = q.front();
            q.pop_front();
            if (now.x == r && now.y == c) {
                ok = true;
                cout << now.steps << endl;
                break;
            }
            // 出队时标记为已访问
            v[now.x][now.y] = true;
            // 拓展
            for (int i = 0; i < 4; i++) {
                int x = now.x + d[0][i], y = now.y + d[1][i];
                if (!valid(x, y)) continue;
                if (v[x][y]) continue;
                int edge;
                if ((x < now.x && y < now.y) ||
                    (x > now.x && y > now.y)) {
                    edge = s[min(x, now.x)][min(y, now.y)] == '\\' ? 0 : 1;
                } else {
                    edge = s[min(x, now.x)][min(y, now.y)] == '/' ? 0 : 1;
                }
                if (edge == 0) {
                    q.push_front({x, y, now.steps});
                } else {
                    q.push_back({x, y, now.steps + 1});
                }
            }
        }
        if (!ok) cout << "NO SOLUTION" << endl;
    }
    return 0;
}