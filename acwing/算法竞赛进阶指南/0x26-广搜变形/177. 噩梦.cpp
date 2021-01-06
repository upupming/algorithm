/*
双向 BFS，与双向 DFS 分成两半不同，只需要从起点和终点分别搜索即可
*/
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 810;
typedef pair<int, int> PII;

int t, n, m, v[2][N][N];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
char s[N][N];
int tt;
PII z[2], boy, girl;
int dist(PII a, PII b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}
bool valid(int x, int y) {
    bool validPos = x >= 0 && x < n && y >= 0 && y < m && s[x][y] != 'X';
    if (!validPos) return false;
    for (int i = 0; i < 2; i++) {
        if (dist({x, y}, z[i]) <= 2 * tt) return false;
    }
    return true;
}
void bfs() {
    memset(v, 0, sizeof(v));
    queue<PII> q1, q2;
    q1.push(boy), q2.push(girl);
    v[0][boy.first][boy.second] = 1;
    v[1][girl.first][girl.second] = 1;
    tt = 0;
    while (q1.size() || q2.size()) {
        tt++;
        // 第一次扩展
        int s1 = q1.size();
        for (int i = 0; i < s1; i++) {
            auto now = q1.front();
            q1.pop();
            if (!valid(now.first, now.second)) continue;
            for (int i = 0; i < 4; i++) {
                int x = now.first + dx[i];
                int y = now.second + dy[i];
                if (valid(x, y) && !v[0][x][y]) {
                    v[0][x][y] = 1;
                    q1.emplace(x, y);
                }
            }
        }
        // 第二次扩展
        s1 = q1.size();
        for (int i = 0; i < s1; i++) {
            auto now = q1.front();
            q1.pop();
            if (!valid(now.first, now.second)) continue;
            for (int i = 0; i < 4; i++) {
                int x = now.first + dx[i];
                int y = now.second + dy[i];
                if (valid(x, y) && !v[0][x][y]) {
                    v[0][x][y] = 1;
                    q1.emplace(x, y);
                }
            }
        }
        // 第三次扩展
        s1 = q1.size();
        for (int i = 0; i < s1; i++) {
            auto now = q1.front();
            q1.pop();
            if (!valid(now.first, now.second)) continue;
            for (int i = 0; i < 4; i++) {
                int x = now.first + dx[i];
                int y = now.second + dy[i];
                if (valid(x, y) && !v[0][x][y]) {
                    v[0][x][y] = 1;
                    q1.emplace(x, y);
                }
            }
        }

        int s2 = q2.size();
        for (int i = 0; i < s2; i++) {
            auto now = q2.front();
            q2.pop();
            if (!valid(now.first, now.second)) continue;
            for (int i = 0; i < 4; i++) {
                int x = now.first + dx[i];
                int y = now.second + dy[i];
                if (valid(x, y) && !v[1][x][y]) {
                    // 如果男孩之前也到了这个点
                    if (v[0][x][y]) {
                        cout << tt << endl;
                        return;
                    }
                    v[1][x][y] = 1;
                    q2.emplace(x, y);
                }
            }
        }
    }
    cout << -1 << endl;
}

int main() {
    cin >> t;
    while (t--) {
        int zCnt = 0;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            cin >> s[i];
            for (int j = 0; j < m; j++) {
                if (s[i][j] == 'Z') {
                    z[zCnt++] = {i, j};
                } else if (s[i][j] == 'M') {
                    boy = {i, j};
                } else if (s[i][j] == 'G') {
                    girl = {i, j};
                }
            }
        }

        bfs();
    }
    return 0;
}
