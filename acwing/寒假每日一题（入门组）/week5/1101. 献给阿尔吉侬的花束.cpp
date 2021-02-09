/*
BFS裸题
*/
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 210;
typedef pair<int, int> PII;

int t, r, c, d[N][N];
int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
char g[N][N];
PII st, ed;
int bfs() {
    queue<PII> q;
    q.push(st);
    d[st.first][st.second] = 0;
    while (q.size()) {
        auto now = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int x = now.first + dx[i];
            int y = now.second + dy[i];
            if (x < 0 || x >= r || y < 0 || y >= c)
                continue;
            if (g[x][y] == '#' || d[x][y] != -1) continue;

            d[x][y] = d[now.first][now.second] + 1;
            if (x == ed.first && y == ed.second)
                return d[x][y];
            q.emplace(x, y);
        }
    }
    return -1;
}
int main() {
    cin >> t;
    while (t--) {
        memset(d, 0xff, sizeof d);
        cin >> r >> c;
        for (int i = 0; i < r; i++) {
            cin >> g[i];
            for (int j = 0; j < c; j++) {
                if (g[i][j] == 'S')
                    st = {i, j};
                else if (g[i][j] == 'E')
                    ed = {i, j};
            }
        }

        int ans = bfs();
        if (ans == -1)
            puts("oop!");
        else
            cout << ans << endl;
    }
    return 0;
}