/*
暴力搜索，每次枚举所有的颜色选择情况
剪枝：
估价：当前网格中不同颜色的格子的数量为 x，那么至少还需要 x - 1 步，如果可用步数不足 x，则剪枝
*/
#include <cstring>
#include <iostream>
#include <unordered_set>
using namespace std;
const int N = 10;
typedef pair<int, int> PII;

int n, a[N][N], e, v[N][N];
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
// 统计有多少不同的颜色
int cntColors() {
    int cnt[6] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (v[i][j] != 1) {
                cnt[a[i][j]] =1;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < 6; i++) ans += cnt[i];
    return ans;
}
// 把原来的图变成三色图，1 表示和 now 同色，2 表示不同色，0 表示不连通
void dfs(int now, int x, int y) {
    v[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int X = x + dx[i], Y = y + dy[i];
        if (X < 0 || X >= n || Y < 0 || y >=n || v[X][Y] == 1)
           continue;
        v[X][Y] = 2;
        if (a[X][Y] == now) dfs(now, X, Y);
    }
}
// 将 v 填充为左上角选择变色为 now 之后的情况
int fill(int now) {
    int p = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == now && v[i][j] == 2) {
                dfs(now, i, j), ++p;
            }
        }
    }
    return p;
}
bool idaStar(int dep, int now) {
    // cout << dep << endl;
    // 估价值
    int f = cntColors();
    // cout << f << endl;
    if (dep == e) {
        return f == 0;
    }
    // 提前剪枝
    if (dep + f > e) return false;

    int tmp[N][N];
    memcpy(tmp, v, sizeof v);
    // 枚举所有的变色情况
    for (int i = 0; i < 6; i++) {
        if (i == now) continue;

        if (fill(i) && idaStar(dep+1, i)) return true;
        memcpy(v, tmp, sizeof v);
    }

    return false;
}
int main() {
    while (cin >> n, n) {
        e = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> a[i][j];
            }
        }

        memset(v, 0, sizeof v);
        dfs(a[0][0], 0, 0);
        while (!idaStar(0, a[0][0])) e++;
        cout << e << endl;
    }
    return 0;
}