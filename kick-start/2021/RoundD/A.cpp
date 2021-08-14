#include <bits/stdc++.h>
using namespace std;

int t, n, g[3][3];

int solve() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 1 && j == 1) continue;
            cin >> g[i][j];
        }
    }
    int ans = 0;
    if (g[0][0] + g[0][2] == 2 * g[0][1]) ans++;
    if (g[2][0] + g[2][2] == 2 * g[2][1]) ans++;
    if (g[0][0] + g[2][0] == 2 * g[1][0]) ans++;
    if (g[0][2] + g[2][2] == 2 * g[1][2]) ans++;

    map<int, int> s;
    // top left
    s[g[0][0] + g[2][2]]++;
    // 竖着
    s[g[0][1] + g[2][1]]++;
    // top right
    s[g[0][2] + g[2][0]]++;
    // 横着
    s[g[1][0] + g[1][2]]++;
    int tmp = 0;
    for (auto& x : s) {
        if (x.first % 2 == 0 && x.second > tmp) {
            tmp = x.second;
        }
    }
    return ans + tmp;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}
