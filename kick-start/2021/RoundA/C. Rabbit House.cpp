#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 310;
typedef long long LL;
typedef pair<int, int> PII;

int t, g[N][N], r, c, v[N][N];
int maxV = 0, maxI, maxJ;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool valid(int x, int y) {
    return x >= 0 && x < r && y >= 0 && y < c;
}

struct P {
    int x, y, val;
    bool operator<(P b) const {
        return val < b.val;
    }
};

priority_queue<P> q;
LL solve() {
    if (maxV == 0) return 0;
    LL ans = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            q.push({i, j, g[i][j]});
        }
    }
    int cnt = 0;
    while (q.size()) {
        auto now = q.top();
        q.pop();
        if (v[now.x][now.y]) continue;
        v[now.x][now.y] = 1;
        if (++cnt == r * c) return ans;
        for (int k = 0; k < 4; k++) {
            int x = now.x + dx[k];
            int y = now.y + dy[k];
            if (!valid(x, y)) continue;
            int goal = g[now.x][now.y] - 1;
            if (g[x][y] < goal) {
                ans += goal - g[x][y];
                g[x][y] = goal;
            }
            q.push({x, y, g[x][y]});
        }
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> r >> c;
        maxV = 0;
        memset(v, 0, sizeof v);
        q = priority_queue<P>();
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cin >> g[i][j];
                if (g[i][j] > maxV) {
                    maxI = i, maxJ = j;
                    maxV = g[i][j];
                }
            }
        }
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}
