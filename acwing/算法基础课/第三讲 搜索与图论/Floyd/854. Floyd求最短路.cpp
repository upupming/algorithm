/*
Floyd 可以处理负边
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 210;

int d[N][N], n, m, k;
int x, y, z;
int main() {
    cin >> n >> m >> k;
    memset(d, 0x3f, sizeof d);
    for (int i = 1; i <= n; i++) d[i][i] = 0;
    for (int i = 1; i <= m; i++) {
        cin >> x >> y >> z;
        d[x][y] = min(d[x][y], z);
    }
    // floyd 求任意两点间最短路径
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    while (k--) {
        cin >> x >> y;
        if (d[x][y] > 0x3f3f3f3f / 2)
            puts("impossible");
        else
            cout << d[x][y] << endl;
    }
    return 0;
}