#include <bits/stdc++.h>
using namespace std;
const int N = 40;

int bx, by, dx, dy, v[N][N], cnt[N][N];
bool valid(int x, int y) { return x < N && y < N; }
bool equal(int x1, int y1, int x2, int y2) {
    return (x1 == x2) && (y1 == y2);
}
// 当前在 (cx, cy)， 可以走到的所有 (nx, ny)
void calc(int cx, int cy, vector<int> &nx, vector<int> &ny) {
    // 横着走
    if (!(equal(cx + 1, cy, bx, by)) && !(equal(cx + 1, cy, dx, dy)) && valid(cx + 2, cy + 1)) {
        nx.push_back(cx + 2);
        ny.push_back(cy + 1);
    }
    // 竖着走
    if (!(equal(cx, cy + 1, bx, by)) && !(equal(cx, cy + 1, dx, dy)) && valid(cx + 1, cy + 2)) {
        nx.push_back(cx + 1);
        ny.push_back(cy + 2);
    }
}
bool ok(int x, int y) {
    return (x == dx) && (y == dy);
}
bool canAttack(int x, int y) {
    return (!equal(bx + 1, by, dx, dy) && equal(bx + 2, by + 1, x, y)) ||
           (!equal(bx, by + 1, dx, dy) && equal(bx + 1, by + 2, x, y)) ||
           (!equal(bx - 1, by, dx, dy) && equal(bx - 2, by - 1, x, y)) ||
           (!equal(bx, by - 1, dx, dy) && equal(bx - 1, by - 2, x, y)) ||
           (!equal(bx, by - 1, dx, dy) && equal(bx + 1, by - 2, x, y)) ||
           (!equal(bx + 1, by, dx, dy) && equal(bx + 2, by - 1, x, y)) ||
           (!equal(bx - 1, by, dx, dy) && equal(bx - 2, by + 1, x, y)) ||
           (!equal(bx, by + 1, dx, dy) && equal(bx - 1, by + 2, x, y));
}
int dfs(int x, int y) {
    if (x >= 30 || y >= 30) return 0;
    if (canAttack(x, y)) return 0;
    // 之前访问过，已经记过数了，不再计数
    if (ok(x, y)) return 1;
    if (v[x][y]) return cnt[x][y];
    vector<int> nx, ny;
    calc(x, y, nx, ny);
    int ans = 0;
    for (int i = 0; i < nx.size(); i++) {
        ans += dfs(nx[i], ny[i]);
    }
    v[x][y] = 1;
    return cnt[x][y] = ans;
}
int main() {
    cin >> bx >> by >> dx >> dy;
    cout << dfs(0, 0) << endl;
    return 0;
}
/*
2 2 6 3
1 0 2 1
1 0 1 2
1 0 3 3
1 1 3 3
1 3 3 3
*/
