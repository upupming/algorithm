#include <iostream>
using namespace std;
const int N = 310;
typedef long long LL;

int t, g[N][N], r, c;
LL sum;

LL solve() {
    for (int i = 0; i < r; i++) {
        for (int j = 1; j < c; j++) {
            g[i][j] = max(g[i][j], g[i][j - 1] - 1);
        }
        for (int j = c - 2; j >= 0; j--) {
            g[i][j] = max(g[i][j], g[i][j + 1] - 1);
        }
    }
    for (int j = 0; j < c; j++) {
        for (int i = 1; i < r; i++) {
            g[i][j] = max(g[i][j], g[i - 1][j] - 1);
        }
        for (int i = r - 2; i >= 0; i--) {
            g[i][j] = max(g[i][j], g[i + 1][j] - 1);
        }
    }
    LL now = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            now += g[i][j];
        }
    }
    return now - sum;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> r >> c;
        sum = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cin >> g[i][j];
                sum += g[i][j];
            }
        }
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}
