/*
只有 4 个方向，且是交替改变
*/
#include <iostream>
using namespace std;
const int N = 510;

int a[N][N], n;
bool valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> a[i][j];
    }

    int x = 0, y = 0;
    bool flag = true;
    while (x != n || y != n) {
        if (x < n && y < n) cout << a[x][y] << " ";
        if (flag)
            x--, y++;
        else
            x++, y--;
        if (x < 0) {
            x = 0;
            flag = !flag;
        }
        if (y < 0) {
            y = 0;
            flag = !flag;
        }
    }
    return 0;
}
