/*
f[i][j] 表示从 (i, j) 出发的最长轨迹
根据 > 关系，一定不会有循环依赖关系
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 310;

int a[N][N], r, c, f[N][N];
int dx[] = {-1, 0, 1, 0}, dy[] = {0, -1, 0, 1};
int dp(int i, int j) {
    if (f[i][j] != -1) return f[i][j];
    bool flag = false;
    for (int k = 0; k < 4; k++) {
        int x = i + dx[k], y = j + dy[k];
        if (x < 0 || x >= r || y < 0 || y >= c) continue;
        if (a[i][j] > a[x][y]) {
            flag = true;
            f[i][j] = max(f[i][j], dp(x, y) + 1);
        }
    }
    // 初始条件
    if (!flag) f[i][j] = 1;
    return f[i][j];
}
int main() {
    cin >> r >> c;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> a[i][j];
        }
    }
    int ans = 0;
    memset(f, -1, sizeof f);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            ans = max(ans, dp(i, j));
        }
    }
    cout << ans << endl;
    return 0;
}
