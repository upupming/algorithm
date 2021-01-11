#include <iostream>
using namespace std;
const int N = 110;

int n, m, a[N][N];
int d[4][2] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}};
int main() {
    cin >> n >> m;
    int x = 0, y = 0, dx = 0, dy = 1;
    for (int i = 1; i <= n * m; i++) {
        a[x][y] = i;
        if (dy == 1 && (y == m - 1 || a[x][y + 1] != 0)) dx = d[1][0], dy = d[1][1];
        if (dx == 1 && (x == n - 1 || a[x + 1][y] != 0)) dx = d[2][0], dy = d[2][1];
        if (dy == -1 && (y == 0 || a[x][y - 1] != 0)) dx = d[3][0], dy = d[3][1];
        if (dx == -1 && (x == 0 || a[x - 1][y] != 0)) dx = d[0][0], dy = d[0][1];

        x += dx, y += dy;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}
