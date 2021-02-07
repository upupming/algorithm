/*
IDA*: 估价函数：max(左下非白马的个数, 右上非黑马的个数)
每次选择一个马，和空位进行交换，记录下上次交换的位置，避免重复搜索
*/
#include <cassert>
#include <iostream>
using namespace std;
const int N = 10;

char g[N][N];
int n = 5, e, px, py;
int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
int dy[] = {2, -2, 2, -2, 1, -1, 1, -1};
// 估价函数
int f() {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // cout << g[i][j];
            if (i == j) {
                if (j == n / 2)
                    continue;
                else if (j < n / 2) {
                    ans += g[i][j] != '1';
                } else {
                    ans += g[i][j] != '0';
                }
            } else if (i > j)
                ans += g[i][j] != '0';
            else
                ans += g[i][j] != '1';
            // cout << i << " " << j << " " << ans << endl;
        }
        // cout << endl;
    }
    return ans;
}
bool idaStar(int dep, int x, int y) {
    int step = f();
    if (step == 0) return true;
    assert(step > 0);
    // cout << dep << ", " << step << endl;
    if (step + dep > e) return false;

    for (int i = 0; i < 8; i++) {
        int X = px + dx[i], Y = py + dy[i];
        if (X < 0 || X >= n || Y < 0 || Y >= n) continue;
        // 避免往复循环
        if (X == x && Y == y) continue;
        int s = px, t = py;
        swap(g[X][Y], g[px][py]);
        px = X, py = Y;
        assert(g[px][py] == '*');
        if (idaStar(dep + 1, s, t)) return true;
        // 还原现场
        px = s, py = t;
        swap(g[X][Y], g[px][py]);
    }
    return false;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        e = 0;
        for (int i = 0; i < n; i++) {
            cin >> g[i];
            for (int j = 0; j < n; j++) {
                if (g[i][j] == '*')
                    px = i, py = j;
            }
        }
        while (e <= 15 && !idaStar(0, -1, -1)) e++;
        cout << (e > 15 ? -1 : e) << endl;
    }
    return 0;
}