/*
LCA 模板题
预处理时间复杂度为 O(n log n)，每次询问的时间复杂度为 O(log n)
多次查询树上两点之间的距离，总时间复杂度为 O((n+m)log n)（预处理+询问）

两点 (x, y) 之间的距离 = (x, root) + (y, root) - 2 * (lca(x, y), root)

there is a unique simple path("simple" means you can't visit a place twice) between every two houses
两两之间一定有路，选谁当根节点来遍历整棵树都是等价的，对 LCA 算法求两点之间的距离不影响

不妨设 1 号节点为根，这个 N 个点 N-1 条边的无向图就可以看成是有根树了
*/
#include <cmath>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 4e4 + 10, M = 2 * N;

int dist[N], d[N], f[N][20];
int head[N], edge[M], ver[M], Next[M];
int t, n, m, tot, k;
void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, Next[tot] = head[x];
    head[x] = tot;
}
// 预处理
void bfs() {
    queue<int> q;
    q.push(1), d[1] = 1;
    while (q.size()) {
        int x = q.front();
        q.pop();
        for (int i = head[x]; i; i = Next[i]) {
            int y = ver[i];
            if (d[y]) continue;
            d[y] = d[x] + 1;
            dist[y] = dist[x] + edge[i];
            f[y][0] = x;
            for (int j = 1; j <= k; j++) {
                f[y][j] = f[f[y][j - 1]][j - 1];
            }
            q.push(y);
        }
    }
}
// 回答一个询问
int lca(int x, int y) {
    if (d[x] > d[y]) swap(x, y);
    for (int i = k; i >= 0; i--) {
        if (d[f[y][i]] >= d[x]) y = f[y][i];
    }
    if (x == y) return x;
    for (int i = t; i >= 0; i--) {
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    }
    return f[x][0];
}
int main() {
    cin >> t;
    while (t--) {
        memset(head, 0, sizeof head);
        memset(d, 0, sizeof d);
        tot = 0;
        cin >> n >> m;
        k = log(n) / log(2) + 1;
        for (int i = 1; i < n; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            add(x, y, z), add(y, x, z);
        }
        bfs();
        for (int i = 1; i <= m; i++) {
            int x, y;
            cin >> x >> y;
            cout << dist[x] + dist[y] - 2 * dist[lca(x, y)] << endl;
        }
    }
    return 0;
}
