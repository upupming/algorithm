#include <bits/stdc++.h>
using namespace std;
const int N = 5010;

int n, val[3][N];
vector<int> w[N];

int dfs(int cur, int fa, int lastColor) {
    int ans = 0;
    for (int color = 0; color < 3; color++) {
        if (color == lastColor) continue;
        int tmp = val[color][cur];
        for (auto& y : w[cur]) {
            if (y == fa) continue;
            tmp += dfs(y, cur, color);
        }
        ans = max(ans, tmp);
    }
    return ans;
}
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> val[0][i] >> val[1][i] >> val[2][i];
    }
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        w[x].push_back(y);
    }

    cout << dfs(0, -1, -1) << endl;
    return 0;
}
/*
3
2 4 9
1 3 5
1 2 3
0 1
0 2
*/
