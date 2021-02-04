/*
八邻域
bfs、dfs 都可以
dfs 简单一些（超时，恢复现场之后会有重复搜素）
bfs 搜索范围更少
*/
#include <climits>
#include <iostream>
#include <queue>
#include <set>
using namespace std;
const int N = 110;
typedef pair<int, int> PII;

int x, y, mx, my;
char g[N][N];
set<PII> s;
bool allConquered() {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (g[i][j] == '.') return false;
        }
    }
    return true;
}
bool valid(int mx, int my) {
    return mx >= 0 && mx < x && my >= 0 && my < y;
}
void out() {
    for (int i = 0; i < y; i++) {
        cout << g[i] << endl;
    }
    cout << endl;
}
// dep: 当前星期数
// (mx, my): 当前坐标
int dfs(int dep, int mx, int my) {
    char tmp = g[my][mx];
    g[my][mx] = 'M';
    s.erase({my, mx});
    // cout << dep << ", " << mx << ", " << my << endl;
    // out();
    if (s.empty()) return dep;
    int ans = INT_MAX;
    // 遍历八邻域
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nx = mx + i, ny = my + j;
            if (!valid(nx, ny)) continue;
            if (g[ny][nx] == '*' || g[ny][nx] == 'M') continue;
            ans = min(ans, dfs(dep + 1, nx, ny));
        }
    }
    s.insert({my, mx});
    g[my][mx] = tmp;
    return ans;
}
struct P {
    int x, y, idx;
};
int main() {
    cin >> x >> y >> mx >> my;
    int cnt = 0;
    for (int i = 0; i < y; i++) {
        cin >> g[i];
        for (int j = 0; j < x; j++) {
            if (g[i][j] == '.')
                s.emplace(i, j);
            else
                cnt++;
        }
    }
    mx = mx - 1, my = y - my;
    // cout << mx << " " << my << endl;
    // dfs 超时
    // cout << dfs(-1, mx, my);

    queue<P> q;
    q.push({mx, my, 0});
    while (q.size()) {
        auto now = q.front();
        q.pop();

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int nx = now.x + i, ny = now.y + j;
                if (!valid(nx, ny)) continue;
                if (g[ny][nx] == '*' || g[ny][nx] == 'M')
                    continue;
                g[ny][nx] = 'M', cnt++;
                if (cnt == x * y) {
                    cout << now.idx + 1 << endl;
                    return 0;
                }
                q.push({nx, ny, now.idx + 1});
            }
        }
    }
    return 0;
}