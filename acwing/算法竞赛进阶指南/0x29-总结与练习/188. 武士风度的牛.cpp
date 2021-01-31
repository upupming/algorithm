#include <iostream>
#include <queue>
using namespace std;
const int N = 150;
typedef pair<int, int> PII;

int r, c;
char g[N][N];
int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2}, dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
int wx[] = {-1, -1, 0, 0, 0, 0, 1, 1}, wy[] = {0, 0, -1, 1, -1, 1, 0, 0};
bool v[N][N];
struct P {
    int x, y, steps;
};
bool check(int i, int j) {
    if (i >= 0 && i < r && j >= 0 && j < c) return true;
    return false;
}
int main() {
    cin >> c >> r;
    PII e;
    queue<P> q;
    for (int i = 0; i < r; i++) {
        scanf("%s", g[i]);
        for (int j = 0; j < c; j++) {
            if (g[i][j] == 'K') {
                v[i][j] = true;
                q.push({i, j, 0});
            } else if (g[i][j] == 'H') {
                e = {i, j};
            }
        }
    }
    while (q.size()) {
        auto now = q.front();
        q.pop();
        for (int i = 0; i < 8; i++) {
            int x = now.x + dx[i];
            int y = now.y + dy[i];
            if (!check(x, y)) continue;
            if (v[x][y]) continue;
            int s = now.x + wx[i];
            int t = now.y + wy[i];
            if (g[s][t] == '*') continue;

            // 第一次入队时即为最小步数
            if (x == e.first && y == e.second) {
                cout << now.steps + 1 << endl;
                return 0;
            }
            v[x][y] = true;
            q.push({x, y, now.steps + 1});
        }
    }
    return 0;
}