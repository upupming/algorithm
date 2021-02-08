/*
只是检查一下合法性，比原来的搜索所有可能的解简单多了
相当于原来的搜索题里面的剪枝这个子步骤
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 6;
const int M = N * N;

int t, n, m, a;
// 36 位会爆 int
long long row[M], col[M], cell[M];
bool solve() {
    memset(row, 0, sizeof row);
    memset(col, 0, sizeof col);
    memset(cell, 0, sizeof cell);
    cin >> n;
    m = n * n;
    bool ok = true;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a;
            // 含有非法数字
            if (a < 1 || a > m)
                ok = false;
            row[i] |= 1ll << (a - 1);
            col[j] |= 1ll << (a - 1);
            cell[i / n * n + j / n] |= 1ll << (a - 1);
        }
        if (row[i] != (1ll << m) - 1)
            ok = false;
    }
    if (!ok) return false;
    for (int j = 0; j < m; j++) {
        if (col[j] != (1ll << m) - 1)
            return false;
    }
    // 遍历所有的 cell
    for (int i = 0; i < m; i++) {
        if (cell[i] != (1ll << m) - 1)
            return false;
    }
    return true;
}
int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        printf("Case #%d: %s\n", i, solve() ? "Yes" : "No");
    }
    return 0;
}