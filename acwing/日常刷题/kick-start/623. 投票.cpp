/*
f[i][j]:
A 有 i 票，B 有 j 票，并且 A 一直领先 B 的概率
初始情况 f[1][0] = 1
转移：
f[i][j] 可以转移到 f[i+1][j] 和 f[i][j+1]
转移的概率分别是：
(N-i)/(N+M-(i+j))
(M-j)/(N+M-(i+j))
*/
#include <cstring>
#include <iostream>
using namespace std;
const int N = 2010;

int n, m;
double f[N][N];
double solve() {
    cin >> n >> m;
    memset(f, 0, sizeof f);
    f[1][0] = 1.0 * n / (n + m);
    for (int i = 1; i <= n; i++) {
        // j 必须小于 i
        for (int j = 0; j < i; j++) {
            f[i + 1][j] += f[i][j] * (n - i) / (n + m - (i + j));
            f[i][j + 1] += f[i][j] * (m - j) / (n + m - (i + j));
        }
    }

    return f[n][m];
}

int t;
int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        printf("Case #%d: %.8lf\n", i, solve());
    }
    return 0;
}
