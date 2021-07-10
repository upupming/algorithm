#include <iostream>
using namespace std;
const int N = 3e5 + 10, M = 2 * N;
typedef long long LL;

int head[N], ver[M], edge[M], Next[M], tot;
int n, w[N];
LL ans;

void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z;
    Next[tot] = head[x], head[x] = tot;
}

LL dfs(int x, int father) {
    LL d1 = 0, d2 = 0;
    for (int i = head[x]; i; i = Next[i]) {
        int y = ver[i], z = edge[i];
        if (y == father) continue;
        LL d = dfs(y, x) - z;
        if (d > d1)
            d2 = d1, d1 = d;
        else if (d > d2)
            d2 = d;
    }
    ans = max(ans, d1 + d2 + w[x]);
    return d1 + w[x];
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    for (int i = 1; i <= n - 1; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        add(u, v, c);
        add(v, u, c);
    }
    dfs(1, -1);
    cout << ans << endl;
    return 0;
}
