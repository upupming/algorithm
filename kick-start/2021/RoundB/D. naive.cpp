#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 10, Q = 1e5 + 10;
typedef long long LL;

int t, n, q, pre[N];
vector<int> e[N];
unordered_map<int, unordered_map<int, LL>> L, A;

LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}

void dfs(int x, int fa) {
    pre[x] = fa;
    for (auto &y : e[x]) {
        if (y != fa) {
            dfs(y, x);
        }
    }
}

void solve() {
    memset(pre, -1, sizeof pre);
    dfs(1, -1);
    while (q--) {
        int c, w;
        cin >> c >> w;
        LL ans = 0;
        while (c != 1) {
            LL l = L[c][pre[c]], a = A[c][pre[c]];
            if (w >= l) {
                ans = gcd(ans, a);
            }
            c = pre[c];
        }
        cout << ans << " ";
    }
    cout << endl;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> q;
        for (int i = 1; i <= n; i++) e[i].clear();
        L.clear(), A.clear();
        for (int i = 0; i < n - 1; i++) {
            LL x, y, l, a;
            cin >> x >> y >> l >> a;
            e[x].push_back(y);
            e[y].push_back(x);
            L[x][y] = L[y][x] = l;
            A[x][y] = A[y][x] = a;
        }
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
